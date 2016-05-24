/** FreeI2P++
    @file       ~/MachinaSpeculatrix/TouchSensor.h
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

#ifndef _MachinaSpeculatrix__TouchSensor_Header
#define _MachinaSpeculatrix__TouchSensor_Header

#include "../I2P/TObject.h"
using namespace I2P;
#include "DigitalIn.h"

namespace Robots
{
class TouchSensor : public TObject
    #if _mbed
    , public DigitalIn
    #endif
    #if _Windows
      //: CSerial
    #endif
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    TouchSensor (const char* objectName
        #if _mbed
        , PinName mbedPin
        #endif
        );

    virtual ~TouchSensor () {}

    virtual const char* Name ();
    virtual const char* Class ();

    virtual const char* Clone (Keypunch& tx);
    virtual const char* Clone (PunchCard& rx, Keypunch& tx);

    virtual const char* PickUp ();
    virtual const char* PutDown ();

    virtual const char* Members (uint16_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr);
    virtual const char* Objects (uint32_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr);

    virtual const char* Call (const char* name, PunchCard& rx, Keypunch& tx);
    virtual const char* Select (const char* name, PunchCard& rx, Keypunch& tx);

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    static TextInterface<uint8_t> iMembers;

    const char* name;
};
}
#endif  //< _MachinaSpeculatrix__TouchSensor_Header
#endif  //< _Debug
