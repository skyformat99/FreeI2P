/** FreeI2P++
    @version    0.9
    @file       ~/I2P/CardSorter.h
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


#include "CardSorter.h"
using namespace I2P;
#include "Command.h"
#include "TTimestamp.h"

CardSorter::CardSorter (uint8_t* beginingAddress, word_t aSlotSize, word_t talkbackSize) :
    dataWidth (0),
    parserIndex (0),
    talkback (beginingAddress, talkbackSize),
    beginAddress (talkback.EndAddress ()),
    endAddress (beginAddress + aSlotSize),
    state0Address (&states[0]),
    stateNAddress (&states[MaxNumStates - 1]),
    //expression0Address (0),
    //expressionNAddress (0),
    lastTimeByteReceived (0),
    startAddress (0),
    openingAddress (0),
    stopAddress (0),
    stateAddress (0),
    errorMessage (0)
{
    ///
}

uint8_t* CardSorter::EndAddress ()
{
    return endAddress + sizeof (word_t) + 1;
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void CardSorter::ScanByte (uint8_t newByte)
{
    #if _Debug
    debug.printf ("%x", newByte);
    #endif
    switch ((uint8_t)state)
    {
        case CommandState:
        {
            //if (newByte & 0x80 == 0x80) { WriteByte (newByte); break; } //< It was a command.
            //EnterState ('&');
            break;
        }
        case ListState:                  { UnsupportedState (); return; }
        case CompositionState:
        {
            if (newByte == 0)
            {
                ExitState ();
                return;
            }
            return;
        }
        case EndCompositionState:       { UnsupportedState (); return; }
        case EOTState:                  { UnsupportedState (); return; }
        case ENQState:
        {
            //if (newByte == Command::ACK) EnterState (EnquerryResponseState);
            //else ExitState ();
            return;
        }
        case ACKState:
        {
            if (newByte == Command::ACK) EnterState (CommandState);
            else ExitState ();
            return;
        }
        case TypeState:
        {
            ScanType (newByte);
            return;
        }
        case PODTypeState:
        {
            if (++parserIndex >= dataWidth)
            {
                ExitState ();
                return;
            }
            return;
        }
        case ParsingAtomicState:        { UnsupportedState (); return; }
        case StructState:
        {
            /*
            if (newByte == Command::ENQ)
            {
                WriteEnquerry ();
                wait (0.1f);
                EnterState (EnquerrySentState);
            }
            */
            break;
        }
        case State11:                   { UnsupportedState (); return; }
        case State12:                   { UnsupportedState (); return; }
        case State13:                   { UnsupportedState (); return; }
        case State14:                   { UnsupportedState (); return; }
        case State15:                   { UnsupportedState (); return; }
        case DC1State:                  { UnsupportedState (); return; }
        case DC2State:                  { UnsupportedState (); return; }
        case DC3State:                  { UnsupportedState (); return; }
        case DC4State:                  { UnsupportedState (); return; }
        case NAKState:                  { UnsupportedState (); return; }
        case StreamState:               { UnsupportedState (); return; }
        case PacketState:               { UnsupportedState (); return; }
        case CancelState:               { UnsupportedState (); return; }
        case EMState:                   { UnsupportedState (); return; }
        case SubstituteState:           { UnsupportedState (); return; }
        case EscapeState:               { ScanCommand (newByte); return; }
        case FileState:                 { UnsupportedState (); return; }
        case ArrayState:                { UnsupportedState (); return; }
        case KeyValueState:             { UnsupportedState (); return; }
        case ObjectState:               { UnsupportedState (); return; }
        case PauseState:                { UnsupportedState (); return; }
        case ErrorState:                { UnsupportedState (); return; }
        case DoubleQuoteState:          { UnsupportedState (); return; }
        case '#':                       { UnsupportedState (); return; }
        case SudoState:                 { UnsupportedState (); return; }
        case ProcessState:              { UnsupportedState (); return; }
        case '&':                       { UnsupportedState (); return; }
        case '\'':                      { UnsupportedState (); return; }
        case '(':                       { UnsupportedState (); return; }
        case ')':                       { UnsupportedState (); return; }
        case '*':                       { UnsupportedState (); return; }
        case '+':                       { UnsupportedState (); return; }
        case ',':                       { UnsupportedState (); return; }
        case '-':                       { UnsupportedState (); return; }
        case '.':                       { UnsupportedState (); return; }
        case '/':                       { UnsupportedState (); return; }
        case ':':                       { UnsupportedState (); return; }
        case ';':                       { UnsupportedState (); return; }
        case '<':                       { UnsupportedState (); return; }
        case '=':                       { UnsupportedState (); return; }
        case '>':                       { UnsupportedState (); return; }
        case '?':                       { UnsupportedState (); return; }
        case '@':                       { UnsupportedState (); return; }
        case '[':                       { UnsupportedState (); return; }
        case '\\':                      { UnsupportedState (); return; }
        case ']':                       { UnsupportedState (); return; }
        case '^':                       { UnsupportedState (); return; }
        case '_':                       { UnsupportedState (); return; }
        case '`':                       { UnsupportedState (); return; }
        case '{':                       { UnsupportedState (); return; }
        case '|':                       { UnsupportedState (); return; }
        case '}':                       { UnsupportedState (); return; }
        case '~':                       { UnsupportedState (); return; }
        case 127:                       { UnsupportedState (); return; }
        default: return;
    }
}

void CardSorter::ScanType (uint8_t type)
{
    switch (type & 0x1F)
    {
        case _T::Null:              { ExitState (); return; }
        case _T::List:              { EnterState (_T::List); return; }
        case _T::Composition:       { EnterState (_T::Composition); return; }
        case _T::EndComposition:    { EnterState (_T::EndComposition); return; }
        case _T::Boolean:           { EnterState (PODTypeState); return; }
        case _T::UInt:              { EnterState (PODTypeState); return; }
        case _T::Int:               { EnterState (PODTypeState); return; }
        case _T::Float:             { EnterState (PODTypeState); return; }
        case _T::Backspace:         { EnterState (PODTypeState); return; }
        case _T::Atomic:            { UnsupportedType (type); return; }
        case _T::Return:            { EnterState (PODTypeState); return; }
        case _T::Timestamp:         { EnterState (PODTypeState); return; }
        case _T::Interrupt:         { EnterState (PODTypeState); return; }
        case _T::CloseExpression:   { EnterState (PODTypeState); return; }
        case _T::String16:          { EnterState (type); return; }
        case _T::String:            { EnterState (type); return; }
        case _T::Struct:            { EnterState (PODTypeState); return; }
        case _T::DC1:               { EnterState (PODTypeState); return; }
        case _T::DC2:               { EnterState (PODTypeState); return; }
        case _T::DC3:               { EnterState (PODTypeState); return; }
        case _T::DC4:               { EnterState (PODTypeState); return; }
        case _T::Error:             { EnterState (PODTypeState); return; }
        case _T::Stream:            { UnsupportedType (type); return; }
        case _T::Packet:            { UnsupportedType (type); return; }
        case _T::Cancel:            { CancelExpression (); return; }
        case _T::EM:                { UnsupportedType (type); return; return; }
        case _T::Substitution:      { CancelExpression (); return; }
        case _T::Expression:        { UnsupportedType (type); return; }
        case _T::File:              { UnsupportedType (type); return; }
        case _T::Array:             { UnsupportedType (type); return; }
        case _T::KeyValue:          { UnsupportedType (type); return; }
        case _T::Object:            { UnsupportedType (type); return; }
        default:                    { UnsupportedType (type); return; }
    }
}

void CardSorter::ScanCommand (int8_t newByte)
{
}

//////////////////////////////////////////////////// Read Functions ////////////////////////////////////////////////////

inline void CardSorter::WriteEnquerry ()
{
    talkback.WriteCommand (Command::ACK);
    talkback.WriteCommand (Command::ENQ);
    talkback.WriteTimestamp (TTimestamp::Now ());
}

inline void CardSorter::EnterState (uint8_t newState)
{
    if (newState >= MaxNumStates)
    {
        CancelExpression ();
        --stateAddress;
        #if _Debug
        debug.printf ("CardSorter::newState was greater than the number of states\n\r");
        #endif // Using_mbed
        return;
    }
    if (stateAddress == stateNAddress)
    {
        CancelExpression ();
        stateAddress = state0Address;
        #if _Debug
        debug.printf ("CardSorter::stateBuffer overflow!\n\r");
        #endif // Using_mbed
        return;
    }
    *(stateAddress++) = state;
    state = newState;
}

void CardSorter::ExitState ()
{
    if (stateAddress == state0Address)
    {
        #if _Debug
        debug.printf ("{/State}");
        #endif
        return;
    }

    state = *(--stateAddress);
}

void CardSorter::CloseExpression ()
{
     #if _Debug
     debug.printf ("</Expression>\n\r");
     #endif
}

void CardSorter::CancelExpression ()
{
    #if _Debug
    debug.printf ("\n\r[CAN]\n\r\n\r");
    #endif

     stopAddress = openingAddress;
}

//////////////////////////////////////////////////// Error Messages ////////////////////////////////////////////////////

void CardSorter::UnsupportedState ()
{
    #if _Debug
    debug.printf ("Error: Unsupported state %i encountered!\n\r", state);
    PrintState ();
    #endif
}

void CardSorter::ReadError (int error, const char* message)
{
    char messageWithStateInformation[60];
    sprintf (messageWithStateInformation, "Error: %s\n\rstate: %i\n\r", message, state);
    #if _Debug
    debug.printf ("%s", messageWithStateInformation);
    PrintState ();
    #endif

    #if UsingConsole
    talkback->LogKeypunch (messageWithStateInformation);
    #endif
}

const char* CardSorter::BufferUnderflow ()
{
    ReadError (BufferUnderflowError, "Buffer underflow in state %i.\n\r");
}

void CardSorter::ReadInvalidType (uint8_t type)
{
    char message[40];
    sprintf (message, "Error: Expected value type %s while reading\n\r", _T::GetName (type));
    ReadError (InvalidTypeError, message);
}

void CardSorter::DataReadError (uint8_t* cursor, uint8_t type)
{
    char message[40];
    sprintf (message, "Error: Read error while reading type %s at index %i\n\r", _T::GetName (type),
        (word_t)(cursor - beginAddress));
    ReadError (InvalidDataError, message);
}

void CardSorter::ReadError (uint8_t* cursor, uint8_t type, uint8_t expectedType)
{
    char message[40];
    sprintf (message, "Error: Expected value type %s while reading %s at index %i\n\r", _T::GetName (type),
        _T::GetName (expectedType), (word_t)(cursor - beginAddress));
    ReadError (InvalidDataError, message);
}

void CardSorter::UnsupportedType (uint8_t type)
{
    #if _Debug
    debug.printf ("Error in CardSorter: Unsupported type %i!\n\r", type);
    #endif
}
