/** FreeI2P++
    @version    0.9
    @file       ~/I2P/ChineseDoor.cpp
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

#include "ChineseDoor.h"
using namespace I2P;
#include "Roombot.h"

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// Public
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ChineseDoor::ChineseDoor (const char* aRoomName, ChineseDoor* adjacentDoor
    #if _mbed
    , Serial* aSlot
    #endif
    , word_t aSlotSize, word_t aTalkbackSize
    ) :
    roomName (aRoomName),
    tx ((adjacentDoor == nullptr ? &Roombot::Walls[0] : adjacentDoor->Rx ()->EndAddress ()), aSlotSize)
{
    //tx ()
    //rx = new SerialSorter (tx.EndAddress (), aSlot, aSlotSize, aTalkbackSize);
}

const char* ChineseDoor::RoomName ()    { return roomName; }

Keypunch* ChineseDoor::Tx ()    { return &tx; }

CardSorter* ChineseDoor::Rx ()  { return rx; }
