/** FreeI2P++
    @file       ~/I2P/PunchCard.cpp
    @author     Cale McCollough
    @copyright  Copyright 2015 © Blue Storm Engineering
    @license    Licensed under the Apache License, Version 2.0 (the "License");
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in
        all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
        THE SOFTWARE.   
*/

#include "PunchCard.h"
using namespace I2P;
#include "Command.h"
#include "TType.h"
#include "PunchCard.h"
#include "TTimestamp.h"
#include "TArray.h"
#include "TFile.h"

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// Public
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PunchCard::PunchCard () :
    beginAddress (0),
    endAddress   (0),
    startAddress (0),
    stopAddress  (0),
    errorMessage (0)
{

}

void PunchCard::Load (uint8_t* beginingAddress, uint8_t* endingAddress, uint8_t* startingAddress,
    uint8_t* stopingAddress)
{
    beginAddress = beginingAddress;
    endAddress   = endingAddress;
    startAddress = startingAddress;
    stopAddress  = stopingAddress;
    errorMessage = 0;
}

uint8_t PunchCard::ReadCommand ()
{
    return ReadByte ();
}

const char* PunchCard::Read (char* result, word_t bufferSize, uint8_t type)
{
    if (result == nullptr || bufferSize == 0) return false;

    uint8_t* begin = beginAddress,
        * end = endAddress;

    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress;

    word_t bufferLength = start < stop ? stop - start + 1 : (end - start) + (stop - begin) + 2;

    if (type == _T::String)
    {
        /// Check length
        if (bufferLength < 2) { BufferUnderflow (); }
        /// Check type
        uint8_t typeRead = *start; if (type != typeRead) { ReadError (start, type, typeRead); return 0; }
    }
    else if (bufferLength < 1) { BufferUnderflow (); return "Buffer Underflow"; }

    char value;



    if (value == '\0')
    {
        *result = '\0';
        return 0;
    }
    word_t i = 0;
    while (value != '\0')
    {
        result[i] = value;
        if (++i >= bufferSize)
        {
            #if _Debug
            return "Error in PunchCard::Read (char*, word_t): buffer overflow!\n\r";
            #else
            return 1;
            #endif
        }
        if (++start > end) start = begin;
        value = *start;
    }
    startAddress = (start < end) ? start : begin;
    return 0;
}

bool     PunchCard::ReadBoolean ()      { return Read8  (_T::Boolean) != 0;     }
int8_t   PunchCard::ReadInt8 ()         { return Read8  (_T::Int   & (1 << 5)); }
uint8_t  PunchCard::ReadUInt8 ()        { return Read8  (_T::UInt  & (1 << 5)); }
int16_t  PunchCard::ReadInt16 ()        { return Read16 (_T::Int   & (2 << 5)); }
uint16_t PunchCard::ReadUInt16 ()       { return Read16 (_T::UInt  & (2 << 5)); }
uint32_t PunchCard::ReadUInt32 ()       { return Read32 (_T::UInt  & (4 << 5)); }
int32_t  PunchCard::ReadInt32 ()        { return Read32 (_T::Int   & (4 << 5)); }
float    PunchCard::ReadFloat ()        { return Read32 (_T::Float & (4 << 5)); }
int64_t  PunchCard::ReadInt64 ()        { return Read64 (_T::UInt  & (8 << 5)); }
uint64_t PunchCard::ReadUInt64 ()       { return Read64 (_T::UInt  & (8 << 5)); }
double   PunchCard::ReadDouble ()       { return Read64 (_T::Float & (8 << 5)); }

void PunchCard::Read (void* value, word_t numBytes)
{

}

uint64_t PunchCard::ReadTimestamp ()
{
    return Read64 (_T::Timestamp);
}

const char* PunchCard::Return (const char* name)
{
    return name;
}

int PunchCard::Read (TArray* array, uint8_t* byteArray)
{
    return 1;
}

const char* PunchCard::ReadOnlyError (const char* name)
{
    return name;
}

///---------------------------------------------------------------------------------------------------------------------
/// Private
///---------------------------------------------------------------------------------------------------------------------

uint8_t PunchCard::ReadByte ()
{
    uint8_t* start = startAddress,
    * stop = stopAddress;

    if (start == stop) { BufferUnderflow (); return 0; }

    uint8_t* begin = beginAddress,
        * end = endAddress;

    uint8_t value = *start;
    startAddress = (++start > end) ? begin : start;
    return value;
}

uint8_t PunchCard::Read8 (uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress,
        * start = startAddress,
        * stop = stopAddress;
    
    uint8_t typeRead,
        value;

    if (start > stop)
    {
        uint8_t* topBytes = (end - start) + 1;
        word_t bufferLength = topBytes + (stop - begin) + 1;
        if (bufferLength < 2) { BufferUnderflow (); return 0; }

        if (topBytes < 2)    /// Then we need to load from the top and bottom
        {
            uint8_t typeRead = *end;
            if (typeRead != type) { ReadError (start, type, typeRead); return 0; }
            startAddress = begin + 1;
            return *begin;
        }
    }
    else
    {
        word_t bufferLength = stop - start + 1;
        if (bufferLength < 2) { BufferUnderflow (); return 0; }
    }

    word_t data = *start;
    typeRead = (uint8_t)data;
    if (typeRead != typeRead) { ReadError (start, type, typeRead); return 0; }
    value = (uint8_t)(data >> 8);
    startAddress = start + 2;
    return value;
}

uint16_t PunchCard::Read16 (uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress,
        * start = startAddress,
        * stop = stopAddress;

    uint8_t typeRead,
        value;

    if (start > stop)
    {
        uint8_t* topBytes = (end - start) + 1;
        word_t bufferLength = topBytes + (stop - begin) + 1;
        if (bufferLength < 3) { BufferUnderflow (); return 0; }

        if (topBytes < 3)    /// Then we need to load from the top and bottom
        {
            uint16_t data = *start;
            if (((uint8_t)data) != type) { ReadError (start, type, ((uint8_t)data)); return 0; }
            uint16_t beginData = *begin;
            if (start != end)
            {
                startAddress = begin + 2;
                return beginData;
            }
            /// Else we have to shift the data byte one byte into the LSB, and and it with
            startAddress = begin + 1;
            return (data >> 8) & (beginData << 8);
        }
    }
    else
    {
        word_t bufferLength = stop - start + 1;
        if (bufferLength < 2) { BufferUnderflow (); return 0; }
    }

    word_t data = *start;
    typeRead = (uint8_t)data;
    if (typeRead != typeRead) { ReadError (start, type, typeRead); return 0; }
    value = (uint8_t)(data >> 8);
    startAddress = start + 2;
    return value;
}

uint32_t PunchCard::Read32 (uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress,
        * start = startAddress,
        * stop = stopAddress;

    uint8_t typeRead,
        value;

    if (start < stop)
    {
        word_t bufferLength = stop - start + 1;
        if (bufferLength < 5) { BufferUnderflow (); return 0; }

        uint8_t typeRead = *start;
        if (type != typeRead) { ReadError (start, type, typeRead); return 0; }
        uint32_t data = *(start + 1);
        startAddress = start + 5;
        return value;
    }
/*
    uint8_t* topBytes = (end - start) + 1;

    if (topBytes > 4)   /// Then load similar to if (start < stop) but error checking is redundant.
    {
        uint8_t typeRead = *start;
        if (type != typeRead) { ReadError (start, type, typeRead); return 0; }
        uint32_t data = *(start + 1);
        startAddress = start + 5;
        return value;
    }

    word_t bufferLength = topBytes + (stop - begin) + 1;
    if (bufferLength < 5) { BufferUnderflow (); return 0; }

    uint8_t typeRead = *(start++);
    if (type != typeRead) { ReadError (start, type, typeRead); return 0; }

    #if _16Bit
    uint32_t data = ((*(begin - 2)) << (topBytes << 3)) & (*(start + 1));
    startAddress = begin + (5 - topBytes);
    #else
    uint32_t data = ((*(begin - 4)) << (topBytes << 4)) & (*(start + 1));
    startAddress = begin + (5 - topBytes);
    #endif
    return data;
    */ return 0;
}

uint64_t PunchCard::Read64 (uint8_t type)
{
    return 0;
}
