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

#ifndef _I2P__Console_Header
#define _I2P__Console_Header

#include "Global.h"
#include "Roombot.h"

namespace I2P
{   
/** Ring buffer of log entries.
    Devices can be sent that have logs that stream data TType.
    
    Example: ``[STX]<String>["This is a log message with the number "]<VInt32>[-7]<String>[" in it."][ETX]``
    
*/
class Console
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    static const word_t BufferSize = 1 * 1024;          //< The system log buffer size.

    Console ();                                         //< Default constructor.
    
    void Log (const char* log);                         //< Opens a log with a timestamp and a log entry.
    void Write (const char* log);                       //< Continues to write to the last entry.

    //< Continues to write to the last entry using sprintf.
    template <typename T>
    void Log (T value, const char* format, int32_t bufferSize = 24)
    {
        char result[bufferSize];
        sprintf (result, format, value);
        Log (result);
    }

    template <typename T, typename U>
    void Log (T valueA, U valueB, const char* format, int32_t bufferSize = 64)
    {
        char result[bufferSize];
        sprintf (result, format, valueA, valueB);
        Log (result);
    }
    void ClearLog ();                                   //< Clears the log.
    
    void Print ();                                      //< Prints the log to the debug stream.

    void Print (Keypunch* tx);                          //< Prints the log to a stream.

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    static const char* beginAddress,                    //< The beginning address of the buffer.
        * endAddress;                                   //< The end address of the buffer.

    volatile char* startAddress,                        //< The start address of the log.
        * stopAddress;                                  //< The stop address of the log.
    
    void DeleteFirstLog ();                             //< Removes the first log from the buffer.
};
}
#endif // _I2P__Console_Header
