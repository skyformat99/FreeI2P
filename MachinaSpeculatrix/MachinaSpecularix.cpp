/** FreeI2P++
    @file       ~/MachinaSpeculatrix/MachinaSpeculatrix.h
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

#include "MachinaSpeculatrix.h"
using namespace Robots;
using namespace I2P;

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// public:
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MachinaSpeculatrix::MachinaSpeculatrix () :
    number (0),
    lightSensor (),
    touchSensor (),
    motor (),
    steering ()
{
    buffer[0] = '\0';
    responceText[0] = '\0';
    slot1.baud (9600);

}

virtual const char* MachinaSpeculatrix::Clone (Keypunch& tx)
{
    tx.Write (buffer);
    tx.Write (responceText);
    tx.Write (number);
    const char* error;
    error = lightSensor.Clone (tx); if (error != 0) return error;
    error = touchSensor.Clone (tx); if (error != 0) return error;
    error = motor.Clone (tx);       if (error != 0) return error;
    return steering.Clone (tx);     if (error != 0) return error;
}

virtual const char* MachinaSpeculatrix::Copy (PunchCard& rx, Keypunch& tx)
{
    rx->Read (buffer, NumChars);
    rx->Read (responceText, NumChars);
    number = rx->ReadInt32 ();
    return rx.Return ("Copy");
    error = HBridgeMotor.Copy (tx, tx);        if (error != 0) return error;
    return steering.Copy (tx, tx);      if (error != 0) return error;
}

virtual const char* MachinaSpeculatrix::RingBell ()                         { return 0; }
virtual const char* MachinaSpeculatrix::OpenDoor (const char* doorNumber)   { return 0; }
virtual const char* MachinaSpeculatrix::CloseDoor ()                        { return 0; }

void MachinaSpeculatrix::Listen (const char* aString) { LogMessage (aString); }

const char* MachinaSpeculatrix::Talk () { sprintf (responceText, response, buffer, number); return responceText; }

virtual const char* MachinaSpeculatrix::Members (word_t index, PunchCard* rx, Keypunch* tx)
{
    switch (index & (3 << 14))
    {
        case 0:
            static const char Parameters[] = { _T::Void, _T::String, _T::Integer,  0 };
            if (rx == nullptr) return Signature (tx, "Talk", "Returns the Talk () function.", Parameters);
            tx.Write (Talk ());
            return rx.Return (0);
        case 1:
            if (rx == nullptr) return Signature (tx, "Listen",
                "Records a reads a string and number from the PunchCard.", _T::StringList);
            Listen (rx.Read (buffer, NumChars), rx.ReadInt32 ());
            return rx.Return (1);
        case 2:
            if (rx == nullptr) return Signature (tx, "BufferSize", "Returns the buffer size", _T::StringList);
            if (index < 0) { rx.Read (buffer, BufferSize); return rx.Return (Name); }
            return ReadOnlyError (2);
        case 3:
            if (rx == nullptr) return Signature (tx, "responceText", "Reads or writes to the buffer.", _T::StringList);
            if (index < 0) { rx.Read (responceText, BufferSize); return rx.Return (Name); }
            tx.Write (responceText);
            return tx.Return (3);
        case 4:
            if (rx == nullptr) return Signature (tx, "number", "Reads or writes the an int.", _T::IntList);
            if (index < 0) { number = rx.ReadInt32 (); return rx.Return (Name); }
            tx.Write (number);
            return tx.Return (4);
        default:
            return 5;
    }
}

virtual const char* MachinaSpeculatrix::Objects (word_t index, PunchCard* rx, Keypunch* tx)
{
    switch (ObjectNumber(index))
    {
        case 0:
            if (rx == nullptr) return Signature (tx, "Machina Speculatrix",
                "The Machina Speculatrix was the first robot in the world. It was invented between "
                "1948-9 by William Grey Walter. It consists of a light sensor, a touch sensor, and H-bridge motor for "
                "front-back movement, and another for left-right steering.\0", "I2P.Roombot");
            if (~rx == 0) return Clone (tx); if (~tx == 0) Copy (rx, tx);
            return PickUp (newObject);
        case 1:
            if (rx == nullptr) return Signature (tx, "lightSensor", "A light sensor.",
                "MachinaSpeculatrix.LightSensor");
            if (~rx == 0) return Clone (tx); if (~tx == 0) Copy (rx, tx);
            return PickUp (lightSensor);
        case 2:
            if (rx == nullptr) return Signature (tx, "touchSensor",
                "A momentary switch on the front of the robot to detect collisions.", "MachinaSpeculatrix.LightSensor");
            if (~rx == 0) return Clone (tx); if (~tx == 0) Copy (rx, tx);
            return PickUp (touchSensor);
        case 3:
            if (rx == nullptr) return Signature (tx, "motor", "The front-back motor.", "MachinaSpeculatrix.Motor");
            if (~rx == 0) return Clone (tx); if (~tx == 0) Copy (rx, tx);
            return PickUp (HBridgeMotor);
        case 4:
            if (rx == nullptr) return Signature (tx, "steering", "The left-right steering motor.",
                "MachinaSpeculatrix.Motor");
            if (rx + tx == FWord) return ~rx == 0 ? Clone (tx) : Copy (rx, tx);
            return PickUp (steering);
        default: return 5;
    }
}


virtual const char* Motor::Call (const char* name, PunchCard& rx, Keypunch& tx)
{
    return Members ((self->*members)->Find (name), rx, tx);
}

virtual const char* Motor::Select (const char* name, PunchCard& rx, Keypunch& tx)
{
    return Objects ((self->*objects)->Find (name), rx, tx);
}

virtual const char* MachinaSpeculatrix::Main (bool& on, bool& awake, int argc = 0, const char* args = nullptr)
{
    /// Wake up code.
    if (argc > 0)
    {
        if (args == nullptr) return "Main: argc > 0 && args == nullptr!";

        /// Process args.
    }
    while (on && awake)
    {
        /// Main loop.
    }
    if (on)
    {
        /// Go to sleep code.
    }
    return 0;
}

#endif //< _Debug
