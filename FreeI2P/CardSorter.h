/** FreeI2P++
    @file       ~/I2P/DoorSlot.h
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

#ifndef _I2P__DoorSlot_Header
#define _I2P__DoorSlot_Header

#include "Global.h"
#include "Keypunch.h"
#include "CardSorter.h"

namespace I2P
{
class PunchCard;

/** Sorts incoming PunchCard(s) into OperationCue and InterruptCue hoppers.
    Data comes in loosely pack, and is only scanned for correctness. There is a different CardSorter implementation
    for each communication interface protocol, but there are only three styles: Serial, Batch, and Loopback. The most
    expensive operations are memory read and write operations, so these different read-write strategies are used
    depending on the device.

    Serial Sorters:
    ---------------
    Serial sorters stream bytes one at a time. The most optimal way of reading a UART port is read x bytes (usually 16)
    at a time in a single interrupt.

    Batch Sorters:
    --------------
    This is Batch Scanning is where packages arrive in larger packets or complete programs. Bluetooth and TCP/UDP are
    good examples of batch scanners.
*/
class CardSorter
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    static const uint8_t CommandState   = 0,
        ListState                       = 1,
        CompositionState                = 2,
        EndCompositionState             = 3,
        EOTState                        = 4,
        ENQState                        = 5,
        ACKState                        = 6,
        TypeState                       = 7,
        PODTypeState                    = 8,
        ParsingAtomicState              = 9,
        StructState                     = 10,
        State11                         = 11,
        State12                         = 12,
        State13                         = 13,
        State14                         = 14,
        State15                         = 15,
        DLEState                        = 16,
        DC1State                        = 17,
        DC2State                        = 18,
        DC3State                        = 19,
        DC4State                        = 20,
        NAKState                        = 21,
        StreamState                     = 22,
        PacketState                     = 23,
        CancelState                     = 24,
        EMState                         = 25,
        SubstituteState                 = 26,
        EscapeState                     = 27,
        FileState                       = 28,
        ArrayState                      = 29,
        KeyValueState                   = 30,
        ObjectState                     = 31,
        PauseState                      = 32,
        ErrorState                      = 33,
        DoubleQuoteState                = 34,
        PoundState                      = 35,
        SudoState                       = 36,
        ProcessState                    = 37,
        AddressState                    = 38,
        SingleQuoteState                = 39,
        OpenExpressionState             = 40,
        CloseExpressionsState           = 41,
        StarType                        = 42,
        LogEntryState                   = 43,
        FunctionNumberState             = 44,
        State45                         = 45,
        NamedFunctionState              = 46,
        WriteNamedVariableState         = 47,
        ColonState                      = 58,
        SemicolonState                  = 59,
        ReadIndexedVariableState        = 60,
        State61                         = 61,
        WriteIndexedVariableState       = 62,
        HelpState                       = 63,
        AtState                         = 64,
        OpenSquareBracketState          = 90,
        ReadNamedVariableState          = 91,
        CloseSquareBracketState         = 92,
        CarrotState                     = 93,
        UnderscoreState                 = 94,
        TickState                       = 95,
        OpenCurlyBracketState           = 123,
        BarState                        = 124,
        CloseCurlyBracketState          = 125,
        Tildi                           = 126,
        Delete                          = 127,
        MaxNumStates                    = 128,

        DefaultSlotSize                 = 256,  //< The default size of a slot.
        MaxNumDevices                   = 32,
        MaxNestedLevel = MaxNumStates / 4,      //< The expression buffer size.
        DefaultSlotDistance             = 255,  //< The default talkback buffer size.

        InvalidCommandError             = 1,    //< Return Code: Command was not valid.
        BufferOverflowError             = 2,    //< Return Code: Buffer overflow while writing.
        BufferUnderflowError            = 3,    //< Return Code: Buffer overflow while reading.
        InvalidStateError               = 4,    //< Return Code: Invalid state.
        InvalidTypeError                = 5,    //< Return Code: Encountered an invalid type.
        InvalidDataError                = 6,    //< Return Code: The data was formatted incorrectly.
        FullBufferError                 = 7,    //< Return Code: Encountered a full buffer while writing.
        UnsupportedTypeError            = 8,
        MaxNumErrors                    = 127,  //< The maximum number of errors.
        TimeoutTime                     = 100;  //< The timeout time in microseconds.

    CardSorter (uint8_t* beginingAddress, word_t aSlotSize = DefaultSlotSize, word_t talkbackSize = DefaultSlotSize);

    virtual ~CardSorter () = 0;                 //< Virtual destructor.

    virtual void Feed () = 0;                   //< Feeds (Tx) PunchCard(s) through the slot.
    virtual void Pull () = 0;                   //< Pulls (Rx) PunchCard(s) through the slot.

    const char* Errors ();                      //< Returns the last error string.

    /** Reads and processes a byte from the slot.
        We do not parse the instruction into the buffer for performance considerations.
        @return Returns 1 if a signal has been loaded.
        @return Returns 0 if the current uint8_t processed successfully.
        @return Returns 1 if the buffer does not contain a valid control signal.
        @return Returns 2 if the buffer has overflow.
        @return Returns 3 if the current command is not supported.
        @return Returns 4 if the instruction is invalid.
        @return Returns 5 if the data type is invalid. */
    void ReadByte (uint8_t newByte);

    #if _Debug
    void PrintState ();                         //< Prints the state of this object to the debug stream.
    void PrintHex ();                           //< Prints the list to the debug stream in hex format.
    /** Runs a unit test on the Keypunch class.
        Test performs write operation on Keypunch class followed by read operation for each data type without using any
        communication ports. */
    static void RunTests ();
    #endif

    uint8_t* EndAddress ();                     //< Returns the end address plus the word-sized buffer.

    ///-----------------------------------------------------------------------------------------------------------------
    protected:
    ///-----------------------------------------------------------------------------------------------------------------

    uint8_t dataWidth,                          //< The width of the current POD being parsed.
        parserIndex;                            //< The index of the POD type being parsed.

    Keypunch talkback;                          //< The talkback port.

    uint8_t* beginAddress,                      //< Pointer to the first index of the keypunch's buffer in the door.
        * endAddress,                           //< Pointer to the last index of the keypunch's buffer in the door.
        * state0Address,                        //< Pointer to the first index of the states array.
        * stateNAddress;                        //< Pointer to the last index of the states array.

    //word_t* expression0Address,                //< Pointer to the first index in the expressions.
    //    * expressionNAddress;                  //< Pointer to the last index in the expressions.

    int32_t lastTimeByteReceived;               //< The last time a byte was received in microseconds.

    volatile uint8_t state;                     //< The current state the sorter is in.

    volatile uint8_t* startAddress,             //< Pointer to the first index in the Keypunch buffer.
        * openingAddress,                       //< Pointer to the start of the current open expression in the buffer.
        * stopAddress,                          //< Pointer to the last index in the Keypunch buffer.
        * stateAddress;                         //< Pointer to the state in the stateStack.

    char* errorMessage;                         //< The address of the last error message.

    uint8_t states[MaxNumStates];               //< An array of the previous states for returning from a state.

    //////////////////////////////////////////////////// Functions /////////////////////////////////////////////////////

    inline void VoidByte ();
    inline void WriteEnquerry ();
    inline void EnterState (uint8_t newState);
    void ExitState ();
    void CloseExpression ();
    void CancelExpression ();
    void UnsupportedState ();
    void ReadError (int error, const char* message);
    const char* BufferUnderflow ();
    void ReadInvalidType (uint8_t type);
    void DataReadError (uint8_t* cursor, uint8_t type);
    void ReadError (uint8_t* cursor, uint8_t type, uint8_t expectedType);

    void ScanByte (uint8_t newByte);            //< Scans a single byte from the slot.
    void ScanCommand (int8_t newByte);          //< Scans a command.
    void ScanType (uint8_t type);               //< Scans a type.

    void UnsupportedType (uint8_t type);        //< Reports an unsupported type.

    #if _mbed
    Timer timeoutTimer;                         //< The Keypunch timeout timer.
    #endif
};
}

#endif // _I2P__DoorSlot_Header
