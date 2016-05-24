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

#ifndef _I2P__MachinaSpeculatrix_Header
#define _I2P__MachinaSpeculatrix_Header

#include "../I2P/Roombot.h"
#include "../I2P/ChineseDoor.h"
#include "../I2P/Keypunch.h"
#include "../I2P/Global.h"
#include "../I2P/TObject.h"
#include "../I2P/Sorters/SerialSorter.h"

#include "LightSensor.h"
#include "TouchSensor.h"
#include "Motor.h"

namespace Robots
{
class MachinaSpeculatrix : public I2P::Roombot
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    MachinaSpeculatrix ();
    
    virtual ~MachinaSpeculatrix () {}

    virtual const char* Clone (Keypunch& tx);
    virtual const char* Copy (PunchCard& rx, Keypunch& tx);

    virtual const char* RingBell ();
    virtual const char* OpenDoor (word_t doorNumber);
    virtual const char* CloseDoor ();

    virtual const char* Members (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr);
    virtual const char* Objects (word_t index, PunchCard* rx = nullptr, Keypunch* tx = nullptr);

    virtual const char* Call (const char* name, PunchCard* rx, Keypunch* tx);
    virtual const char* Select (const char* name, PunchCard* rx, Keypunch* tx);

    virtual const char* Main (bool& on, bool& awake, int argc = 0, const char* args = nullptr);

    void Listen (const char* aString);
    const char* Talk ();

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    static TextInterface<uint8_t> iMembers,
        iObjects;

    static const int NumChars = 16,
        numObjects = 4;

    //static const char responceFormat[] = "Hello world! I heard you say %s and the number %i.\n\r\0";

    char buffer[NumChars],
        responceText[NumChars];

    int number;
    
    //LightSensor lightSensor;
    //TouchSensor touchSensor;
    //Motor motor,
    //    steering;

    //static Serial slot1 (PTC16, PTC17);

    //static I2P::ChineseDoor debugDoor ("Debug", nullptr, debug);
        //appDoor (1, debugDoor, slot1)
};
}
#endif  //< _I2P__MachinaSpeculatrix_Header
#endif  //< _Debug
