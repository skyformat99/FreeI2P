/** FreeI2P++
    @file       ~/I2P/PunchCard.h
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

#ifndef _I2P__PunchCard_Header
#define _I2P__PunchCard_Header

#include "Global.h"
#include "TArray.h"

namespace I2P
{    
/** A punch card for a single atomic task or expression with commands and data.
    Atomic tasks are defined as when multiple objects are required to be manipulated in a specific order without
    interruption or else errors will occur. This is not to be confused with atomic functions, which are user-coded for
    each .

    PunchCard vs Tape:
    ------------------
    PunchCard(s) are read from the door buffer. The door buffer is sized such that the Roombot will start overwriting
    that section of the buffer comfortably after that card has bee executed.

    Address Encoding:
    -----------------
    The Members and Objects TObject functions roll the function call code in with the name, description, and signature
    of the member.
*/
class PunchCard
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /** Default constructor creates a blank punch card. */
    PunchCard ();

    void Punch (uint8_t* startingAddress, uint8_t* stopingAddress);

    void Punch (uint8_t* beginingAddress, uint8_t* endingAddress, uint8_t* startingAddress,
        uint8_t* stopingAddress);

    bool IsReadable ();                                 //< Is readeable.

    uint8_t ReadCommand ();
    /** Reads a String from the card and return non-zero upon success. */
    const char* Read (char* returnString, word_t bufferSize, uint8_t type);
    bool      ReadBoolean ();                           //< Reads the next Boolean from the card.
    int8_t    ReadInt8 ();                              //< Reads the next Int8 from the card.
    uint8_t   ReadUInt8 ();                             //< Reads the next UInt8 from the card.
    short     ReadInt16 ();                             //< Reads the next Int16 from the card.
    uint16_t  ReadUInt16 ();                            //< Reads the next UInt16 from the card.
    int32_t   ReadInt32 ();                             //< Reads the next Int32 from the card.
    uint32_t  ReadUInt32 ();                            //< Reads the next UInt32 from the card.
    float     ReadFloat ();                             //< Reads the next float from the card.
    int64_t   ReadInt64 ();                             //< Reads the next Int64 from the card.
    uint64_t  ReadUInt64 ();                            //< Reads the next UInt64 from the card.
    double    ReadDouble ();                            //< Reads the next double from the card.
    void      Read (void* value, word_t numBytes);      //< Reads the next Struct from the card.
    uint64_t  ReadTimestamp ();                         //< Reads the next Timestamp from the card.

    /** Reads an array from the card. */
    int Read (TArray* array, uint8_t* byteArray = nullptr);

    void Load (uint8_t* beginingAddress, uint8_t* endingAddress, uint8_t* startingAddress,
        uint8_t* stopingAddress);

    const char* Return (const char* name);              //< Returns from a function.

    const char* WriteOnlyError (const char* source);    //< Trigger when attempting to write to a read-only variable.
    const char* ReadOnlyError (const char* sourc);      //< Trigger when attempting to read from a write-only variable.

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    inline uint8_t ReadByte ();                         //< Reads the next byte from the card.
    inline word_t ReadWord ();                          //< Reads the next word from the card.

    uint8_t* beginAddress,                              //< Pointer to the first index of the card.
        * endAddress,                                   //< Pointer to the last index of the card.
        * startAddress,                                 //< Pointer to the first index in the card.
        * stopAddress;                                  //< Pointer to the last index in the card.

    const char* errorMessage;                           //< The address of the last error message.

    //////////////////////////////////////////////////// Functions /////////////////////////////////////////////////////

    /** Reads the next address from the card.
    template <typename T>
    T ReadAddress (uint8_t type)
    {
        uint8_t* begin = beginAddress,
            * end = endAddress;
        uint8_t* start = (uint8_t*)startAddress,
            * cursor = (uint8_t*)startAddress;

        word_t PunchCardLength = (word_t) (start < end ? end - start + 1 : (end - start) + (end - begin) + 2);

        if ((type > _T::Number) && (type < _T::Timestamp))
        {
            if (PunchCardLength < 2) { BufferUnderflow (); return 0; }

            /// CheckType
            uint8_t typeRead = *cursor;
            if (type != typeRead) { ReadError (cursor, type, typeRead); return 0; }
        }
        else if (PunchCardLength < 1)
        {
            BufferUnderflow ();
            return 0;
        }
        if (++cursor > end) cursor = begin;
        uint8_t bitsToShift = 7,
            byte;
        uint64_t value;
        for (uint8_t i = 0; i < 9; ++i)
        {
            byte = *cursor;
            if (byte > 128) break;
            if (++cursor > end) cursor = begin;
            value &= byte << bitsToShift;
            bitsToShift += 7;
        }
        if (byte & 0x80 == 0)
        {

            return 0;
        }
        value &= (byte & 0x7F) << bitsToShift;
        startAddress = (++cursor > end) ? begin : cursor;
        return value;
    }
 */
    uint8_t  Read8  (uint8_t type);                     //< Reads the next uint8_t  from the card.
    uint16_t Read16 (uint8_t type);                     //< Reads the next uint16_t from the card.
    uint32_t Read32 (uint8_t type);                     //< Reads the next uint32_t from the card.
    uint64_t Read64 (uint8_t type);                     //< Reads the next uint64_t from the card.

    //void Read (Function& function);                   //< Reads the next function from the card.

    ////////////////////////////////////////////////// Error Messages //////////////////////////////////////////////////

    void ReadError (int error, const char* errorMessage);  //< Reports an error message.
    void BufferUnderflow ();                            //< Reports buffer underflow.
    void WriteBufferFull ();                    /*< Reports full buffer, dumps the current expression, and sends an
                                                    error Keypunch.*/
    void ReadInvalidType (uint8_t type);        //< Reports invalid type scrubed.

    /** s incorrectly formatted data has been found when scrubbing the input stream at the given index. */
    void DataReadError (uint8_t* cursor, uint8_t type);
    void UnsupportedState ();                   //<  an invalid state.
    void UnsupportedType (uint8_t type);        //<  an unsupported type.

    void ReadError (uint8_t* cursor, uint8_t type, uint8_t expectedType);  //< Reports a type-mismatch error.
};
}

#endif // _I2P__PunchCard_Header
