/** FreeI2P++
    @file       ~/I2P/Keypunch.h
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

#ifndef _I2P__Keypunch_Header
#define _I2P__Keypunch_Header

#include "Global.h"
#include "TType.h"
#include "TArray.h"
#include <cstdarg>

namespace I2P
{
/** An I2P Keypunch that for making PunchCard(s).
    A keypunch can on write packed punch cards. Keypunches cannot read PunchCards. Keypunches can be hooked up to output
    streams have their buffer be sent through a slot to another room. On the other side of the room is a
    CardSorter that scans the packed punch card, unpacks and word-aligns instructions, and has another Keypunch
    for automated talkback responses when errors occur, or when making connections (probably some other places too.).

    A Keypunch gets it's memory from the Roombot. This allows for a single statically allocated array to be split up
    between all of the doors in the room.
*/
class Keypunch
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    static const int BufferOverflowError = 1;       //< Reached end of buffer before closing expression.

    /** Default constructor. */
    Keypunch (uint8_t* beginingAddress, word_t aBufferSize);

    bool IsReadable ();                         //< Returns true if the Rx buffer contains any data.
    
    word_t BufferSize ();                           //< Returns the buffer size.
    uint8_t* BeginAddress ();                       //< The beginning of the slot.
    uint8_t* EndAddress ();                         //< The end of the slot.

    void LogMessage (const char* logMessage);

    /** Writes an command to the buffer. */
    void WriteCommand (uint8_t command);
    
    void LogKeypunch (const char* logKeypunch);     //< Writes a Keypunch log to the System Log or debug console.

    //void Write (Function& function);              //< Writes a Function to the list.

    /** Writes a String to the buffer. */
    void Write (const char* value, uint8_t type);
    void Write (bool value);                        //< Writes a Boolean to the buffer.
    void Write (int8_t value);                      //< Writes a Int8 to the buffer.
    void Write (uint8_t value);                     //< Writes a Int8 to the buffer.
    void Write (short value);                       //< Writes a Int16 to the buffer.
    void Write (uint16_t value);                    //< Writes a UInt16 to the buffer.
    void Write (int32_t value);                     //< Writes a Int32 to the buffer.
    void Write (uint32_t value);                    //< Writes a UInt32 to the buffer.
    void Write (float value);                       //< Writes a Float32 to the buffer.
    void Write (int64_t value);                     //< Writes a Int64 to the buffer.
    void Write (uint64_t value);                    //< Writes a UInt64 to the buffer.
    void Write (double value);                      //< Writes a Float64 to the buffer.
    void Write (void* value, word_t numBytes);      //< Writes a Struct to the buffer.
    void WriteTimestamp (ttimestamp_t value);       //< Writes a Timestamp to the buffer.
    
    /** Writes an array to the buffer. */
    void Write (void* array, uint8_t type, word_t typeWidth, uint32_t numDimensions, ...);
    
    /** Streams a byte from the beginning of the list to the start of the 0-level expression.
        For nested TType, the level of nesting increases the expression level. Expressions behave like stacks, and when
        an expression has reach it's final byte, . */
    uint8_t Stream ();
    
    word_t Length ();                               //< Returns the length of the Keypunch in bytes.
    word_t BufferSpace ();                          //< Returns the free buffer space in bytes.
    
    bool IsWritable ();                             //< Returns true if the Tx buffer contains any data.

    #if _Debug
    void PrintState ();                             //< Prints the state of this object to the debug stream.
    void PrintHex ();                               //< Prints the list to the debug stream in hex format.
    /** Runs a unit test on the Keypunch class.
        Test performs write operation on Keypunch class followed by read operation for each data type without using any
        communication ports. */
    static void RunTests ();
    #endif
    
    char* LastError ();                             //< Returns the last error message.
    const char* Return (const char* name);          //< Returns the error.

    void ReadByte (uint8_t newByte);
    uint8_t StreamByte ();

    void Feed ();

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------
    
    static const int32_t TimeoutTime = 50;

    static const uint8_t MaxNumStates = 16;         /*< The maximum  number of nested states.
        This might change to  combination of static and dynamic memory. */
    int32_t lastTimeByteReceived;                   //< The last time a byte was received in microseconds.

    word_t bufferSize;                              //< The buffer size in bytes.

    uint8_t* beginAddress,                          //< Pointer to the first index of the keypunch's buffer in the door.
        * endAddress;                               //< Pointer to the last index of the keypunch's buffer in the door.
    
    uint8_t* expression0Address,                    //< Pointer to the first index in the expressions.
        * expressionNAddress;                       //< Pointer to the last index in the expressions.
    
    volatile uint8_t* startAddress,                 //< Pointer to the first index in the Keypunch buffer.
        * openingAddress,                           //< Pointer to the opening of the current expression in the buffer.
        * stopAddress,                              //< Pointer to the last index in the Keypunch buffer.
        * stateAddress;                             //< Pointer to the state in the stateStack.

    char* errorMessage;                             //< The address of the last error message.
    
    uint8_t states[MaxNumStates];                   //< An array of the previous states for returning from a state.
    
    //////////////////////////////////////////////////// Functions /////////////////////////////////////////////////////
    
    inline void Write8 (uint8_t value);          //< Writes a single byte to the slot.
    void Write8  (uint8_t  value, uint8_t type);    //< Writes the value to the buffer.
    void Write16 (uint16_t value);                  //< Writes the value to the buffer.
    void Write16 (uint16_t value, uint8_t type);    //< WriteserrorMessage the value to the buffer.
    void Write32 (uint32_t value);                  //< Writes the value to the buffer.
    void Write32 (uint32_t value, uint8_t type);    //< Writes the value to the buffer.
    void Write64 (uint64_t value);                  //< Writes the value to the buffer.
    void Write64 (uint64_t value, uint8_t type);    //< Writes the value to the buffer.

    void WriteAddress (word_t value);               //< Writes the value to the buffer.
    
    void ReadError (int error, const char* errorKeypunch);  //< Reports an error.
    void BufferOverflow ();                         //< Reports buffer overflow.
    void BufferUnderflow ();                        //< Reports buffer underflow.
    void WriteBufferFull ();                        /*< Reports full buffer, dumps the current expression, and sends an
                                                        error Keypunch.*/
    void ReadInvalidType (uint8_t type);            //< Reports invalid type scrubbed.
    
    /** s incorrectly formatted data has been found when scrubbing the input stream at the given index. */
    void DataReadError (uint8_t* cursor, uint8_t type);
    void UnsupportedState ();            	        //< An invalid state.
    void UnsupportedType (uint8_t type);            //< An unsupported type.
    
    void ReadError (uint8_t* cursor, uint8_t type, uint8_t expectedType);  //< Reports a type-mismatch error.

    const char* WriteOnlyError (const char* name);
    const char* ReadOnlyError (const char* name);
};
}
#endif // _I2P__Keypunch_Header
