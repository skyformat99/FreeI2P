/** FreeI2P++
    @file       ~/I2P/PunchCardStack.h
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

namespace I2P
{

/** A hopper that feeds punch-cards into the Roombot.

*/
class CardHopper
{
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    CardHopper (word_t aSize) :
        size (aSize),
        beginAddress (drive[0]),
        endAddress (drive[aSize - 1]),
        startAddress (0),
        stopAddress (0)
    {
        // Nothing to do here! :-)
    }

    word_t Cue (word_t startingAddress, word_t stopingAddress)
    {

    }

    word_t Cue (word_t beginingAddress, word_t endingAddress, word_t startingAddress,
        word_t stopingAddress);


    ///-----------------------------------------------------------------------------------------------------------------
    private:
    ///-----------------------------------------------------------------------------------------------------------------

    word_t size;                             //< The max number of PunchCard(s) in the hopper.

    PunchCard* beginAddress,                    //< The beginning address
        endAddress;                             //< The end address of the d

    volatile PunchCard* startAddress,
        stopAddress;

    PunchCard hopper[StackSize];                 //< The stack of PunchCard(s).
};
}
