/** FreeI2P++
    @file       ~/MachinaSpeculatrix/LightSensor.cpp
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

#include "LightSensor.h"
using namespace Robots;
using namespace I2P;

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// public:
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

LightSensor::LightSensor (const char* objectName
    #if _mbed
    PinName mbedPin
    #endif
    ) :
    AnalogIn (mbedPin),
    name ((char*)objectName)
{
    /// Nothing to do here!
}

virtual const char* LightSensor::Clone (Keypunch& tx)
{
    tx.Write (name);
    return tx.Return ("Clone");
}

virtual const char* LightSensor::Clone (PunchCard& rx, Keypunch& tx)
{
    rx->Read (name, MaxNameLength);
    return rx.Return ("Copy");
}

virtual const char* LightSensor::PickUp ()  { return 0; }
virtual const char* LightSensor::PutDown () { return 0; }

virtual const char* LightSensor::Members (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr)
{
    switch (AbsValue (index))
    {
        case 0:
            if (rx == nullptr) return Signature (tx, "state", "Reads the light sensor.", _T::VoidIntList);
            if (index < 0) { tx.Write (state); return tx.Return (Name); }
            return rx.ReadOnlyError (0);
    }
    return 1;
}

virtual const char* LightSensor::Objects (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr)
{
    int8_t objectCode = (int8_t)((index & (3 << ((sizeof (void*) * 8) - 2));

    switch (index & )
    {
        case 0:
            if (rx == nullptr)
                return Signature (tx, "LightSensor",
                    "A standard photosensor hooked up to an ADC pin of a microcontroller.",
                    "MachinaSpeculatrix.LightSensor");
            if (~((word_t)rx) == 0) return Clone (tx); if (~((word_t)tx) == 0) Copy (rx, tx);
            return PickUp (newObject);
        case 0:
            if (rx == nullptr)
                return Signature (tx, "LightSensor",
                    "A standard photosensor hooked up to an ADC pin of a microcontroller.",
                    "MachinaSpeculatrix.LightSensor");
            if (~((word_t)rx) == 0) return Clone (tx); if (~((word_t)tx) == 0) Copy (rx, tx);
            return PickUp (newObject);
    }
    return 0;
}


virtual const char* LightSensor::Call (const char* name, PunchCard& rx, Keypunch& tx)
{
    return Members ((self->*members)->Find (name), rx, tx);
}

virtual const char* LightSensor::Select (const char* name, PunchCard& rx, Keypunch& tx)
{
    return "This object has no sub-objects!";
}

#endif //< _Debug
