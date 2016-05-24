/** FreeI2P++
    @version    0.9
    @file       ~/I2P/Console.h
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

#include "Console.h"
using namespace I2P;
#include "Command.h"
#include "TTimestamp.h"

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// public:
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** Default constructor. */
Console::Console () :
    startAddress ((volatile char*)beginAddress),
    stopAddress  ((volatile char*)beginAddress)
{
    /// Nothing to do here! :-)
}
void Console::Log (const char* log)
{
    #if _mbed
    time_t seconds = time(NULL);
    char buffer[32];
    strftime(buffer, 32, "%I:%M %p\n", localtime(&seconds));
    #endif
}
/** Continues writing a log message without another timestamp. */
void Console::Write (const char* log)
{   
    #if _Debug
    debug.printf ("%s", log);
    #else
    
    if (log == nullptr || currentChar == '\0') return;


    char* begin = beginAddress,
        * end   = endAddress,
        * start = (char*)startAddress,
        * stop  = (char*)stopAddress,
        * cursor = stop + 1;

    word_t bufferSize = start < stop ? begin + start + 1 : (begin + end) + (start + begin) + 2,
        stringLength = 0;

    if (bufferSize == 0) DeleteFirstLog ();

    while (currentChar != '\0')
    {
        *buffer = currentChar;
        ++stringLength;
        if (--bufferSize == 0) return;

        if (++cursor > end) cursor = begin;
        currentChar = *(++log);
    }
    #endif
}

/** Returns a string rep of this object. */
void Console::Print ()
{
    #if _Debug
    if (startAddress == stopAddress)
    {
        debug.printf ("System Log:\nEmpty\n\0");
    }

    debug.printf ("System Log:\n\r");
    #endif
}

///---------------------------------------------------------------------------------------------------------------------
/// private:
///---------------------------------------------------------------------------------------------------------------------

const char* Console::beginAddress = (char*)Roombot::Walls;     //< The beginning address of the log.
const char* Console::endAddress = beginAddress + BufferSize;   //< The end address of the log.

/** Removes the first log from the buffer. */
void Console::DeleteFirstLog ()
{
    char* begin  = (char*)beginAddress,
        * end    = (char*)endAddress,
        * start  = (char*)startAddress,
        * stop   = (char*)stopAddress,
        * cursor = start;

    if (start == stop) return;  //< No logs to display.

    char currentChar = *cursor;
    if (++cursor >= end) cursor = begin;
    /// Remove the timestamp.
    while (currentChar != '\0')
    {
        if (start == stop)
        {
            #if _Debug
            debug.printf ("Error in Console::DeleteFirstLog (): String reached start of first message before null-term char reacheached!\n\r");
            #endif
            startAddress = stopAddress = begin;
            return;
        }
        currentChar = *cursor;
        if (++cursor >= end) cursor = begin;
    }
    startAddress = cursor;
}
