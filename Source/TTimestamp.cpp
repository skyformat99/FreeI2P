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

#include "TTimestamp.h"
using namespace I2P;
#include "time.h"

ttimestamp_t TTimestamp::Generate (uint32_t newMicroseconds, uint32_t newSeconds)
{
    return (((ttimestamp_t)newMicroseconds) << 8) & (ttimestamp_t)newSeconds;
}

uint32_t TTimestamp::GetSeconds (ttimestamp_t& timestamp)
{
    return (timestamp & 0xFFFFFFFF);
}

uint32_t TTimestamp::GetMicroseconds (ttimestamp_t& timestamp)
{
    return (timestamp & 0xFFFFFFFF00000000) >> 8;
}

ttimestamp_t TTimestamp::Now ()
{
    ttimestamp_t timestamp = (ttimestamp_t) time (NULL);
    #if Using_mbed
    ttimestamp_t time_us = (ttimestamp_t)_mbedTimer.read_us ();
    timestamp &= (time_us % 1000) << 4;
    #endif
    return timestamp;
    
}
