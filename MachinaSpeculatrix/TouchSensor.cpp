/** FreeI2P++
    @file       ~/MachinaSpeculatrix/TouchSensor.cpp
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

#if _Debug

#include "TouchSensor.h"
using namespace Robots;
using namespace I2P;

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// public:
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TouchSensor::TouchSensor (const char* objectName
    #if _mbed
    , PinName mbedPin
    #endif
    ) :
    #if _mbed
    DigitalIn (mbedPin)
    #endif
    , name (objectName)
{
    /// Nothing to do here!
}

virtual const char* TouchSensor::Clone (Keypunch& tx)
{
    tx.Write (name);
    return tx.Return ("Clone");
}

virtual const char* TouchSensor::Clone (PunchCard& rx, Keypunch& tx)
{
    rx.Read (name, MaxNameLength);
    return rx.Return ("Copy");
}

virtual const char* TouchSensor::PickUp ()  { return 0; }
virtual const char* TouchSensor::PutDown () { return 0; }

virtual const char* TouchSensor::Members (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr)
{
    switch (MemberIndex (index))
    {
        case 0:
            static const char Parameters[] = { _T::Void, _T::Int,  0 };
            if (rx == nullptr) return Signature (tx, "state", "Returns the touch sensor state.\0", Parameters);
            if (index < 0) { tx.Write (read ()); return tx.Return (0); }
            return rx->ReadOnlyError (Name);
    }
    return 1;
}

virtual const char* TouchSensor::Objects (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr) { return 0; }


virtual const char* TouchSensor::Call (const char* name, PunchCard& rx, Keypunch& tx)
{
    return Members ((self->*members)->Find (name), rx, tx);
}

virtual const char* TouchSensor::Select (const char* name, PunchCard& rx, Keypunch& tx)
{
    return "This object has no sub-objects!";
}

#endif //< _Debug
