/** FreeI2P++
    @version    0.9
    @file       ~/I2P/Function.h
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

#ifndef _I2P__ChineseDoor_Header
#define _I2P__ChineseDoor_Header

#include "Global.h"
#include "Keypunch.h"
#include "CardSorter.h"

#if _Windows
#include <tchar.h>
#include <windows.h>
#include "Serial.h"
#endif

namespace I2P
{
/** An Chinese Door that connects two Chinese Rooms.
    A door is a a connection node between two machine that allows data to pass between two rooms.

    A door functions differently inside of a shared library then then it does in an application where the source is
    directly imported into the software/firmware. When using a shared library, there is no access to IO ports.  For
    this reason, the ChineseDoor object is now included in the shared library, but instead is manually copied into the
    target source directory.

    Stream Sources:
    ---------------
    * UART

    Future Stream Sources:
    ----------------------
    * SPI
    * I2C
    * Multi-UART
    * TCP/UDP
    * Bluetooth
    * CAN
*/
class ChineseDoor
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /** A Chinese door in a Chinese room. */
    ChineseDoor (const char* aRoomName, ChineseDoor* adjacentDoor
        #if _mbed
        , Serial* slot = nullptr
        #endif
        , word_t aSlotSize = 256, word_t aTalkbackSize = 256
        );

    const char* RoomName ();                    //< Gets the room name.

    Keypunch* Tx ();                            //< Gets the Tx port.
    CardSorter* Rx ();                          //< Gets the Rx port.

    ///#################################################################################################################
    protected:
    ///#################################################################################################################

    const char* roomName;                       //< The room name.

    Keypunch tx;                                //< The Tx Keypunch.
    CardSorter* rx;                             //< The Rx CardSorter.
};
}
#endif // _I2P__ChineseDoor_Header
