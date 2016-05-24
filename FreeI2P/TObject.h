/** FreeI2P++
    @file       ~/I2P/TObject.cpp
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

#ifndef _I2P__TObject_header
#define _I2P__TObject_header

#include "Global.h"
#include "PunchCard.h"
#include "Keypunch.h"

namespace I2P
{
class TObject;
typedef void (TObject::*InterfaceFunction)(word_t, PunchCard*, Keypunch*);

class TObject
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    virtual ~TObject () = 0;                            //< Virtual destructor.

    virtual const char* Clone (PunchCard* rx, Keypunch* tx) = 0;
    virtual const char* Clone (Keypunch* tx) = 0;       //< Clones an object.

    virtual const char* PickUp () = 0;                  //< Picks up an object.
    virtual const char* PutDown () = 0;                 //< Puts the object down.

    virtual const char* Members (word_t index, PunchCard* rx, Keypunch* tx) = 0;
    virtual const char* Objects (word_t index, PunchCard* rx, Keypunch* tx) = 0;

    virtual const char* Call (const char* name, PunchCard& rx, Keypunch& tx) = 0;
    virtual const char* Select (const char* name, PunchCard& rx, Keypunch& tx) = 0;
};

/** Returns one of the three elements of an I2P signature: name, description, or identifier. */
static inline const char* Signature (Keypunch* tx, const char* name, const char* description, const char* identifier)
{
    if (tx == nullptr) return name;
    return ((~(word_t)tx) == 0) ? description : identifier;
}
}
#endif // _I2P__TObject_header
