/** FreeI2P++
    @version    0.9
    @file       ~/I2P/SerialSorter.cpp
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

#include "SerialSorter.h"
using namespace I2P;

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// Public
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

SerialSorter::SerialSorter (uint8_t* beginingAddress
    #if _mbed
    , Serial* doorSlot
    #endif
    #if _Windows
    , const char* thisPortName
    #endif
    , word_t aSlotSize, word_t talkbackSize
    ) : 
    CardSorter (beginingAddress, aSlotSize, talkbackSize)
{
    /// Nothing to do here!
}

void SerialSorter::LoopbackInterrupt ()
{
    //while (keypunch.IsReadable ()) cardSorter.StreamByte (keypunch.StreamByte ());
}

void SerialSorter::Feed ()
{
    #if _mbed
    //while (slot->writeable ()) slot->putc (tx.ReadByte ());
    #endif
}

void SerialSorter::Pull ()
{
    #if _mbed
    while (slot->readable ()) CardSorter::ReadByte (slot->getc ());
    #endif
}
