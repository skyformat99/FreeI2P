/** FreeI2P++
    @version    0.9
    @file       ~/I2P/TTimestamp.h
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

#ifndef I2P__TTimestamp
#define I2P__TTimestamp

#include "Global.h"
#include "time.h"

namespace I2P
{
/** 32-52 bit microsecond-resolution timestamp.
    Unix time_t is a 32-bit stored in microseconds since the January 1, 1970. This is a universal time stamp. The
    competing timestamp format is NTP timestamp format. The problem with using NTP in software is that it requires
    a lot of CPU resources to convert too and from. Ethernet cards do this in hardware. Microcontrollers typically
    use microseconds for scheduling events and use a 32-bit RTC. For these reason, The IM2 timestamp format is 
    uses (Microseconds:UInt32)(SecondsSinceEpoch1970:UInt32) format with microsecondes being the MSBs. This format 
    lends it'self well to VUInt64 compression. Timesstamps in this format are gauranteed to transfer from between
    5-8 bytes using no additional code.
*/
class TTimestamp
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    static const word_t MaxDimensions = 256;      //< The maximum number of dimensions allowed in an array.

    /** Generates a timestamp from uint8_t buffer. */
    static ttimestamp_t Generate (uint32_t newMicroseconds, uint32_t newSeconds);
    
    /** Gets the seconds since January 1, 1970. */
    static uint32_t GetSeconds (ttimestamp_t& timestamp);
    
    /** Gets the microseconds. */
    static uint32_t GetMicroseconds (ttimestamp_t& timestamp);
    
    /** Default constructor creates a timestamp of the current time. */
    static ttimestamp_t Now ();
    
    static time_t startTime;                        //< The start time that corresponds to the start of the timer.
    
    #if Using_mbed
    /** Initializes the microsecond counter. */
    static void Initialize ();
    
    #endif
};
}
#endif // I2P__TTimestamp
