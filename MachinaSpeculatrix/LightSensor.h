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

#ifndef _MachinaSpeculatrix__LightSensor_Header
#define _MachinaSpeculatrix__LightSensor_Header

#include "../I2P/Global.h"
#include "../I2P/TObject.h"
using namespace I2P;

namespace Robots
{
class LightSensor: public I2P::TObject
    #if _mbed
    , public AnalogIn
    #endif
    #if _Arduino
    #endif
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    LightSensor (const char* objectName
        #if _mbed
        , PinName mbedPin
        #endif
        );

    virtual ~LightSensor () {}

    virtual const char* Clone (Keypunch& tx);
    virtual const char* Clone (PunchCard& rx, Keypunch& tx);

    virtual const char* PickUp ();
    virtual const char* PutDown ();

    virtual const char* Members (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr);
    virtual const char* Objects (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr);

    virtual const char* Call (const char* name, PunchCard& rx, Keypunch& tx);
    virtual const char* Select (const char* name, PunchCard& rx, Keypunch& tx);

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    static TextInterface<uint8_t> iMembers,
        iOjbects;

    char* name;
};
}
#endif  //< _Debug
#endif  //< _MachinaSpeculatrix__LightSensor_Header
