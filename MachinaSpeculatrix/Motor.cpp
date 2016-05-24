/** FreeI2P++
    @version    0.9
    @file       ~/MachinaSpeculatrix/Motor.cpp
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

#include "Motor.h"
using namespace Robots;
#include "../I2P/TObject.h"
#include "../I2P/TType.h"
using namespace I2P;

#include "stdint.h"

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// public:
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Motor::Motor (const char* motorName, PinName pWMPin, PinName forward, PinName reverse) :
    name (motorName),
    velocity (0.0f)
{
    name = motorName;
    pWM.period(0.001f);
    pWM = 0.0f;
    forward = 0;
    reverse = 0;
}

virtual const char* Motor::Clone (Keypunch& tx)
{
    tx.Write (name, MaxNameLength);
    tx.Write (velocity);
    return tx.Return ("Clone");
}

virtual const char* Motor::Clone (PunchCard& rx, Keypunch& tx)
{
    rx.Read (name, MaxNameLength);
    velocity = rx.ReadFloat ();
    return rx.Return ("Copy");
}

virtual const char* Motor::Members (word_t index, PunchCard* rx, Keypunch* tx)
{
    switch (index & (3 << 14))
    {
        case 0:
            if (rx == nullptr) return Signature (tx, "velocity", "Gets and sets the Motor velocity.", _T::FloatList);
            if (index < 0) { velocity = rx->ReadFloat (); return rx->Return (0); }
            tx->Write (name);
            return tx->Return (0);
    }
    return 1;
}

virtual const char* Motor::Objects (word_t index, PunchCard* rx, Keypunch* tx)
{
    switch (ObjectIndex (index))
    {
        case 0:
            if (rx == nullptr) return Signature (tx, name, "The name of the Motor.", "mbed.Motor");
            if (index < 0) { velocity = rx->ReadFloat (); return rx->Return (name); }
            tx->Write (name);
            return tx->Return (0);
    }
    return 0;
}

virtual const char* Motor::Call (const char* name, PunchCard& rx, Keypunch& tx)
{
    return Members ((self->*members)->Find (name), rx, tx);
}

virtual const char* Motor::Select (const char* name, PunchCard& rx, Keypunch& tx)
{
    return "This object has no sub-objects!";
}

#endif //< _Debug
