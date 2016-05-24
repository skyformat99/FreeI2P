/** FreeI2P++
    @version    0.9
    @file       ~/I2P/SerialSorter.h
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

#ifndef _I2P__Door_header
#define _I2P__Door_header

#include "../Global.h"
#include "../CardSorter.h"

#if UsingWindows
#include <tchar.h>
#include <windows.h>
#include "Serial.h"
#endif

namespace I2P
{
/** Sorts PunchCard(s) into the primary cue and into delayed procedure calls.

    Sorter Sources:
    ---------------
    * UART
    * SPI
    * I2C
    * Multi-UART
    * TCP/UDP
    * Bluetooth
    * CAN
*/
class SerialSorter : public CardSorter
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /** Constructor creates a loopback port. */
    SerialSorter (uint8_t* beginingAddress
        #if _mbed
        , Serial* doorSlot
        #endif
        , word_t aBufferSize = CardSorter::DefaultSlotSize, word_t talkbackSize = CardSorter::DefaultSlotSize
        );

    /** Hooks up the rx and tx slot ends. */
    virtual void HookUp (Keypunch* tx, PunchCard* rx);

    virtual void Feed ();                       //< Feeds (Tx) PunchCard(s) through the slot.
    virtual void Pull ();                       //< Pulls (Rx) PunchCard(s) through the slot.

    void LoopbackInterrupt ();                  //< IRQ for testing without a communication link.

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    #if _mbed
    Serial* slot;
    #endif
    #if _Windows
    //CSerial
    #endif
};
}

#endif // _I2P__Door_header
