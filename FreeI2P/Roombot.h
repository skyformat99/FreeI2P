/** FreeI2P++
    @version    0.9
    @file       ~/I2P/Roombot.h
    @author     Cale McCollough
    @copyright  Copyright 2015 © Blue Storm Engineering
    @license    Permission is hereby granted, free of charge, to any person obtaining a copy
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
#ifndef I2P__Roombot_Header
#define I2P__Roombot_Header

#include "Global.h"
#include "ChineseDoor.h"
#include "TObject.h"
#include "TextInterface.h"
#include "TapeDrive.h"

#define _I2P_RegisterRoombot \
if (rx == nullptr) return Signature (tx, Name, Description, Class);\
if (~rx == 0) return Clone (tx); else Copy (rx, tx);\
return 0;

namespace I2P
{
/** A Roombot that can be control from a Chinese Room.

    OS 3000:
    --------
    The Roombot is modeled after the Univac compuer systems from the 1960s through 1980s to nostalgic reasons. OS 3000
    is a language agnostic Inter-process operating system that runs using cross-platform function calls. While OS 3000
    is a

    Expression vs Operation:
    ------------------------
    An expression returns a value where an atomic task does not. Expressions can be used in place of data types.
*/
class Roombot : public TObject
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    static const word_t WallSize = 16 * 1024;           //< The buffer size for all of the doors and the roombot.

    static TextInterface<uint8_t>* IMembers;            //<
    static TextInterface<uint8_t>* IObjects;            //<

    static uint8_t Walls[WallSize];                     //< The walls in the Chinese Room (The buffer for everything).

    /** Default constructor for initializing static components.
    */
    Roombot ();

    /** Constructor.
    */
    Roombot (const char* botName, TObject* roomDevices, int32_t numDevicesRoom, int64_t numDoorsRoom,
        ChineseDoor* roomDoors, uint32_t aNumDoorsRoom);
    
    virtual ~Roombot () {}

    virtual const char* Clone (Keypunch& tx) = 0;
    virtual const char* Copy  (PunchCard& rx, Keypunch& tx) = 0;

    virtual const char* Members (uint16_t index, PunchCard* args, Keypunch* tx) = 0;
    virtual const char* Objects   (uint32_t index, PunchCard* args, Keypunch* tx) = 0;

    virtual const char* Call (const char* name, PunchCard& rx, Keypunch& tx) = 0;
    virtual const char* Select (const char* name, PunchCard& rx, Keypunch& tx) = 0;

    virtual const char* OpenDoor (word_t doorNumber) = 0;   //< Opens the door number.
    virtual const char* CloseDoor () = 0;                   //< Closes the door.

    virtual const char* Sudo (const char* username, const char* password) = 0;
    virtual const char* LogOff () = 0;

    static uint8_t* Buffer ();                              //< Returns the first byte in the Wall.

    const char* RoomLayout ();                              /*< Returns the room layout string.
                                                                String of the 32 devices in the room. */
    TObject* ControlDevice (uint8_t index);                 //< Selects one of the 32 devices.
    TObject* SelecTObject (word_t index);                   //< Selects one of the 32 devices.
    TObject* SelecTObject (uint16_t index);                 //< Selects one of the current object's nested objects.

    word_t NumDoors ();                                     //< The number of doors in the Roombot.
    const char* RoomName ();                                //< The door number of this Roombot.

    static void LogMessage (const char* message);           //< Logs a message the Console or debug stream.

    static const char* PickUp (TObject* newObject);

    static inline word_t ObjectNumber (word_t index);

    static inline void Lock ();                         //< Disables interrupts.
    static inline void Unlock ();                       //< Enables interrupts.

    ///#################################################################################################################
    protected:
    ///#################################################################################################################

    static const uint8_t ceilingHeight = 16;            //< The maximum depth of a object call stack.

    static const word_t numDevices = 0,                 //< The number of devices in the room.
        numDoors = 0;                                   //< The number of doors in the room.

    static ChineseDoor* doors;                          //< The doors in the Chinese Room.

    static TObject* device,                             //< The current device under control.
        * air[ceilingHeight];                           //< The stack of objects in the air.

    static TapeDrive stack,                             //< The instruction stack.
        irq1;                                           //< IRQ1

    static volatile word_t juggleIndex;             //< The index of the

    /** Writes the enquiry string to the the Keypunch. */
    inline void WriteEnquerry ();

    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    static const char* PutDownAndPickup (TObject* newObject)
    {
        return 0;
    }
};
}
#endif /// __I2P__ProcessScrubber_Header
