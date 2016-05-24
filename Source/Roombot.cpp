/** FreeI2P++
    @version    0.9
    @file       ~/I2P/Roombot
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

#include "Roombot.h"
using namespace I2P;

TextInterface<uint8_t>* Roombot::IMembers = nullptr;
TextInterface<uint8_t>* Roombot::IObjects = nullptr;

uint8_t* Roombot::Buffer () { return &Walls[0]; }

const char* Roombot::PickUp (TObject* newObject)
{
    if (device == nullptr) return "Not holding anything.";
    if (juggleIndex  >= ceilingHeight) return "Juggling too many object!";
    const char* insult = device->PutDown ();
    return insult != 0 ? insult : PickUp (newObject);
}

inline word_t Roombot::ObjectNumber (word_t index) { return index & (3 << ((sizeof (void*) * 8) - 2)); }

///#####################################################################################################################
/// protected:
///#####################################################################################################################

ChineseDoor* Roombot::doors = nullptr;
TObject* Roombot::device = nullptr;
volatile word_t Roombot::juggleIndex = 0;


inline void Roombot::Lock ()
{
    #if Using_mbed
    __disable_irq ();
    #endif
}

inline void Roombot::Unlock ()
{
    #if Using_mbed
    __enable_irq ();
    #endif
}
