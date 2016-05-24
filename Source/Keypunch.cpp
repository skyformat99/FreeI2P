/** FreeI2P++
    @file       ~/I2P/Keypunch.cpp
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
#include "Keypunch.h"
using namespace I2P;
#include "Command.h"
#include "TNumber.h"
#include "TFile.h"
#include "TTimestamp.h"

#include <stdio.h>
#include "string.h"

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// Public:
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Keypunch::Keypunch (uint8_t* beginingAddress, word_t aBufferSize) :
    lastTimeByteReceived (0),
    bufferSize     (aBufferSize),
    beginAddress   (beginingAddress + sizeof (word_t) + 1),
    endAddress     (beginAddress + aBufferSize + sizeof (word_t) + 1),
    startAddress   ((uint8_t*)beginAddress),
    openingAddress ((uint8_t*)beginAddress),
    stopAddress    ((uint8_t*)beginAddress),
    errorMessage (0)
{
}

bool Keypunch::IsReadable ()
{
    return Length () > 0;
}

word_t Keypunch::BufferSize ()     { return bufferSize + (2 * (sizeof (word_t) + 1)); }
uint8_t* Keypunch::BeginAddress () { return beginAddress - sizeof (word_t) - 1; }
uint8_t* Keypunch::EndAddress ()   { return endAddress + sizeof (word_t) + 1; }

void Keypunch::LogMessage (const char* logMessage)
{
    #if _Debug
    debug.printf ("%s", logMessage);
    #endif
}

void Keypunch::WriteCommand (uint8_t value)
{
    if (value > 127) { return; } //< "Error in Keypunch::WriteCommand: Invalid command!\n\r"

    Write8 (value);
}

void Keypunch::Write (const char* thisString, uint8_t type)
{
    if (thisString == nullptr) return;
    
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;
    
    if (type == _T::String)
    {
        if (bufferSpace < sizeof (word_t) + 2) { BufferOverflow (); return; }
        *cursor = type; if (++cursor > end) cursor = begin; 
    }
    else if (bufferSpace < sizeof (word_t) + 1) { BufferOverflow (); return; }
    
    char currentChar = *thisString;
    while (currentChar != '\0')
    {
        currentChar = *(++thisString);
        if (++cursor > end) cursor = begin; *cursor = currentChar;
    }
    stopAddress = (++cursor > end) ? begin : cursor;
}

void Keypunch::Write (bool value)        { Write8  (value ? 1 : 0, _T::Boolean); }
void Keypunch::Write (int8_t value)      { Write8  ((uint8_t)value, _T::Int); }
void Keypunch::Write (uint8_t value)     { Write8  (value, _T::UInt); }
void Keypunch::Write (int16_t value)     { Write16 ((uint16_t)(value * -1), _T::Int); }
void Keypunch::Write (uint16_t value)    { Write16 (value, _T::UInt); }
void Keypunch::Write (uint32_t value)    { Write32 (value, _T::UInt); }
void Keypunch::Write (int32_t value)     { Write32 ((uint32_t)value, _T::Int); }
void Keypunch::Write (float floatValue)  { Write32 (*((uint32_t*)&floatValue), _T::Float); }
void Keypunch::Write (int64_t value)     { Write64 ((uint64_t)value, _T::Int); }
void Keypunch::Write (uint64_t value)    { Write64 ((uint64_t)value, _T::UInt); }
void Keypunch::Write (double value)      { Write64 (*((uint64_t*)&value), _T::Float); }

void Keypunch::Write (void* value, word_t numBytes)
{

}

void Keypunch::WriteTimestamp (ttimestamp_t value)
{
    // Todo:
    Write64 ((uint64_t)value, _T::Timestamp);
}

void Keypunch::Write (void* array, uint8_t type, word_t typeWidth, uint32_t numDimensions, ...)
{
    if (numDimensions == 0) return;
    
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;
    word_t numBytes =  1;
    if (bufferSpace < sizeof (word_t) + numBytes) { BufferOverflow (); return; }
    *cursor = _T::Array;
    if (++cursor > end) cursor = begin;
    
    //uint32_t dimensions[numDimensions];
    va_list dimensionsList;
    va_start(dimensionsList, numDimensions); //Requires the last fixed parameter (to get the address)
    int32_t currentVector = va_arg(dimensionsList, int32_t),
        numCells = 0;
    for(uint32_t i = 1; i < numDimensions; ++i)
    {
        currentVector = va_arg(dimensionsList, int32_t);
        //dimensions[0] = currentVector;
        numCells += currentVector;
    }
    va_end(dimensionsList);
    word_t numBytesArray = typeWidth * numCells;
    if ((numBytesArray + (numDimensions + 1) * 4) > bufferSpace)
    {
        #if _Debug
        debug.printf ("Error in Keypunch::ReadArray: buffer overflow!\n\r");
        #endif
        return;
    }
    if (array == nullptr) array = new uint8_t*[numBytesArray];
    
}

void Keypunch::ReadByte (uint8_t newByte)
{
    /*
    /// Check for timeout condition or Synchronous Idle [SYN] instruction.
    #if _mbed
    timeoutTimer.stop ();
    int32_t timerTime_us = timeoutTimer.read_us (),
        timeDelta = (timerTime_us - (int32_t)lastTimeByteReceived);
    lastTimeByteReceived = timerTime_us;
    timeoutTimer.start ();
    #endif
    if (timeDelta > TimeoutTime)
    {
        if (newByte == Command::SYN) return; //< Tx Keypunch knows it's late.
        CancelExpression ();
        #if _Debug
        debug.printf ("Keypunch timeout!\n\r");
        #endif
    }
    uint8_t* start = (uint8_t*)startAddress,
            * stop = (uint8_t*)stopAddress;

    uint8_t* begin = beginAddress,
        * end = endAddress,
        * cursor = (uint8_t*)stopAddress;

    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;
    if (bufferSpace < sizeof (word_t) + 1) { BufferOverflow (); return; }
    *cursor = newByte;
    startAddress = (++cursor > end) ? begin : cursor;
    ReadByte (newByte);
    */
}

word_t Keypunch::Length ()
{
    uint8_t* start = (uint8_t*)startAddress,
        * open = (uint8_t*)openingAddress,
        * begin = beginAddress,
        * end = endAddress;
    
    return start < open ? open - start + 1 : (open - begin) + (end - start) + 2;
}

word_t Keypunch::BufferSpace ()
{
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress;
    
    return start < stop ? bufferSize - (stop - start + 1) : (start - stop) + 1;
}

bool Keypunch::IsWritable ()
{
    return BufferSpace () > 0;
}

uint8_t Keypunch::StreamByte ()
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * open = (uint8_t*)openingAddress,
        * cursor = (uint8_t*)startAddress;

    word_t KeypunchLength = start < open ? open - start + 1 : (end - start) + (open - begin) + 2;
    
    if (KeypunchLength < 1) { BufferOverflow (); return 0; }
    uint8_t byte = *cursor;
    stopAddress = (++cursor > end) ? begin : cursor;
    return byte;
}

///--------------------------------------------------------------------------------------------------------------------
/// Private
///--------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////// Write Functions ////////////////////////////////////////////////////

void Keypunch::Write8 (uint8_t value)
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;

    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;
    
    if (bufferSpace <0) { BufferOverflow (); return; }
    *cursor = value;
    stopAddress = (++cursor > end) ? begin : cursor;
}

void Keypunch::Write8 (uint8_t value, uint8_t type)
{
    Write16 ((((uint16_t)type) << 8) & ((uint16_t)value));
}

void Keypunch::Write16 (uint16_t value)
{
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress;
    uint8_t* begin = beginAddress,
        * end = endAddress,
        * cursor = stop;

    word_t bufferSpace;

    if (start < stop)
    {
        bufferSpace =  (start - begin) - (end - stop) + 2;
    }
    else
    {
        bufferSpace =  start - stop + 1;
    }
}

void Keypunch::Write16 (uint16_t value, uint8_t type)
{
    static const uint8_t NumBytes = 2;
    
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    
    word_t bufferSpace;

    if (start < stop)
    {
        bufferSpace =  (start - begin) - (end - stop) + 2;
    }
    else
    {
        bufferSpace =  start - stop + 1;
    }
}

void Keypunch::Write32 (uint32_t value, uint8_t type)
{
    static const uint8_t NumBytes = 4;
    
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    
    word_t bufferSpace;
    if (start < stop)
    {
        bufferSpace =  (start - begin) - (end - stop) + 2;
    }
    else
    {
        bufferSpace =  start - stop + 1;
    }
}

void Keypunch::Write64 (uint64_t value, uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    
    word_t bufferSpace;

    if (start < stop)
    {
        bufferSpace =  (start - begin) - (end - stop) + 2;
    }
    else
    {
        bufferSpace =  start - stop + 1;
    }
}

void Keypunch::WriteAddress (word_t value)
{

}

//////////////////////////////////////////////////// Error Keypunchs ///////////////////////////////////////////////////

void Keypunch::BufferOverflow ()
{
    ReadError (BufferOverflowError, "Buffer overflow in state %i.\n\r");
}


#if _Debug
void Keypunch::PrintState ()
{
    debug.printf ("Keypunch:\n\r");
    PrintLine ('-');
    /*
    uint8_t* begin = beginAddress,\
        * open = (uint8_t*)openingAddress,\
        * start = (uint8_t*)startAddress,\
        * stop = (uint8_t*)stopAddress;\

    word_t startIndex = (word_t)(start - begin),
        stopIndex     = (word_t)(stop  - begin);
    
    debug.printf ("state: %i\n\rdataWidth: %i\n\rparserIndex: %i\n\rstartIndex: %i\n\r"
        "stopIndex: %i\n\rstateAddress: %i\n\r%s\n\r",
        state, dataWidth, parserIndex, stateAddress, stopIndex, stateIndex, errorMessage);
    */
    PrintLine ('-');
    /// Print states
    if (errorMessage != 0)
    {
        debug.printf ("Error: %s\n\rStates: ", errorMessage);
        word_t i;
        for (i = 0; i < MaxNumStates - 1; ++i)
            debug.printf ("%i, ");
        debug.printf ("%i\n\r", states[i]);
    }
    else
    {
        debug.printf ("States\n\rNone\n\r");
    }
    PrintLine ('-');
    PrintHex ();
    PrintLine ('-');
}

/** Prints the list to the debug stream in hex format. */
void Keypunch::PrintHex ()
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* cursor = (uint8_t*)startAddress,
        * start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress;
        
    if (cursor == stop)
    {
        PrintLine ('-');
        return;
    }
        
    bool contiguous = cursor < stop;
    uint8_t* end1 = contiguous ? stop - 1 : end;
    
    for (uint8_t* i = start; i <= end1; ++i)
        debug.printf ("%x", *i);
    
    if (!contiguous)
        for (uint8_t* i = begin; i < stop; ++i)
            debug.printf ("%x", *i);
    
    debug.printf ("\n\r");
    
}
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#if _Debug
void Keypunch::RunTests ()
{
    Keypunch tx ();
    //LoopbackSorter rx ();
    //// ChineseDoor door
    
    //tx.Write (1.0f);
    //tx.PrintState ();
        
    //ByteStream loopback (tx, rx);
    //loopback.TxInterrupt ();
    
    //rx->PrintState ();
    //Assert (rx->ReadFloat32 () == 1.0f, "Invalid float.");
    //rx->PrintState ();
    
    //uint32_t int32Result = tx.ReadVInt32 ();
    //Assert (listA.ReadCommand () == 27, "Invalid instruction.");
    
}
#endif




/*

void Keypunch::UnsupportedType (uint8_t type)
{
    char message[40];
    sprintf (message, "Error: Encountered unsupported type %s\n\r", _T::GetName (type));
    if (++numErrors >= MaxNumErrors) return;
    ReadError (UnsupportedTypeError, message);
}
void Keypunch::WriteVUInt (uint16_t value, uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;
    uint8_t numBytes = TVUInt::NumBytes (value);

    if (type > _T::Number && type < _T::Timestamp)
    {
        if (bufferSpace < sizeof (word_t) + variableLength + 1) { BufferOverflow (); return; }
        *cursor = type; if (++cursor > end) cursor = begin;
        if (++cursor > end) cursor = begin;
    )

    uint16_t bitMask = 0x3F80,
        bitsToShift = 7,
        byte = ((uint8_t)value) & 0x7F;

    for (uint8_t i = 1; i < variableLength - 1; ++i)
    {
        *cursor = byte;
        if (++cursor > end) cursor = begin;
        bitsToShift += 7;
        bitMask = bitMask << 7;
        byte = (uint8_t)((value & bitMask) >> bitsToShift);
    }
    *cursor = byte & 0x80;
    stopAddress = (++cursor > end) ? begin : cursor;
}

void Keypunch::WriteVUInt (uint32_t value, uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;
    uint8_t numBytes = TVUInt::NumBytes (value);

    if (type > _T::Number && type < _T::Timestamp)
    {
        if (bufferSpace < sizeof (word_t) + variableLength + 1) { BufferOverflow (); return; }
        *cursor = type; if (++cursor > end) cursor = begin;
        if (++cursor > end) cursor = begin;
    )
    uint32_t bitMask = 0x3F80,
        bitsToShift = 7,
        byte = ((uint8_t)value) & 0x7F;

    for (uint8_t i = 1; i < variableLength - 1; ++i)
    {
        *cursor = byte;
        if (++cursor > end) cursor = begin;
        bitsToShift += 7;
        bitMask = bitMask << 7;
        byte = (uint8_t)((value & bitMask) >> bitsToShift);
    }
    *cursor = byte & 0x80;
    stopAddress = (++cursor > end) ? begin : cursor;
}
template <typename T>
void Keypunch::WriteVUInt (T value, uint8_t type)
{
    uint8_t* begin = beginAddress,
        * end = endAddress;
    uint8_t* start = (uint8_t*)startAddress,
        * stop = (uint8_t*)stopAddress,
        * cursor = (uint8_t*)stopAddress;
    word_t bufferSpace = start < stop ? (start - begin) - (end - stop) + 2: start - stop + 1;

    uint8_t numBytes = Keypunch::NumBytes (value);

    if (type > _T::Number && type < _T::Timestamp)
    {
        if (bufferSpace < sizeof (word_t) + numBytes + 1) { BufferOverflow (); return; }
        *cursor = type; if (++cursor > end) cursor = begin;
        if (++cursor > end) cursor = begin;
    }
    T bitMask = 0x3F80,
        bitsToShift = 7;
    uint8_t byte = ((uint8_t)value) & 0x7F;

    for (uint8_t i = 1; i < numBytes - 1; ++i)
    {
        *cursor = byte;
        if (++cursor > end) cursor = begin;
        bitsToShift += 7;
        bitMask = bitMask << 7;
        byte = (uint8_t)((value & bitMask) >> bitsToShift);
    }
    *cursor = byte & 0x80;
    stopAddress = (++cursor > end) ? begin : cursor;
}
*/
