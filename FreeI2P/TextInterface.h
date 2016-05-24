/** FreeI2P++
    @file       ~/I2P/Interface.h
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
#ifndef _I2P__TextInterface_header
#define _I2P__TextInterface_header

#include "Global.h"
#include "Keypunch.h"
#include "PunchCard.h"
#include "TObject.h"

namespace I2P
{
/** A text hash interface.

*/
template <typename T>
class TextInterface
{

    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public:
    ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    TextInterface (InterfaceFunction thisMembers, TObject* thisObject)
    {
        if (thisObject == nullptr)
        {
            self = nullptr;
            members = nullptr;
            numMembers = 0;
            indexes = nullptr;
            hashes = nullptr;
            return;
        }
        word_t thisNumMembers = (word_t) (thisObject->*thisMembers) (FWord, nullptr, nullptr);

        if (thisNumMembers == 0)
        {
            self = nullptr;
            members = nullptr;
            numMembers = 0;
            indexes = nullptr;
            hashes = nullptr;
            return;
        }
        self = thisObject;
        members = thisMembers;
        numMembers = thisNumMembers;
        hashes     = new hash_t[numMembers];
        indexes    = new T[numMembers];

        for (int i = 0; i < thisNumMembers; ++i)
            Insert ((thisObject->*thisMembers) (i, nullptr, nullptr));
    }

    /** Inserts the member into the hash table.
        @return     Returns 0 upon success and a pointer to a string upon failure.
        @warning    Member assumes index is positive! */
    const char* Insert (const char* name)
    {
        uint16_t localNumMembers = numMembers;
        if (localNumMembers >= MaxNumMembers)
        {
            #if _Debug
            return "Error in void Interface::InsertMember (const Member&, uint16_t): numMembers == "
                "MaxNumMembers!\n\r";
            #else
            return "";
            #endif
        }

        uint32_t newHash = HashString (name);

        if (localNumMembers == 1)
        {
            hashes[1] = newHash;
            indexes[numMembers++] = 1;
            return 0;
        }

        /// We are going to start at the end and work our way back because we are moving everything up one space.
        /// We are guaranteed that the both hashes[i + 1] and indexes[i + 1] will be an empty element.
        int i;
        for (i = localNumMembers - 1; i > 0; --i)
        {
            uint32_t currentHash = hashes[i];

            if (newHash > currentHash)
            {
                hashes[i + 1] = newHash;
                indexes[i + 1] = index;
            }
            else if (currentHash == newHash)
            {
                /// We might have a collision so we need to progress down and either copy up or insert here based on the
                /// string comparison.
                //char* compareString =
                int comparison = 0;//strcmp (name);
                if (comparison > 0)
                {
                    /// Insert above here
                    hashes[i + 1] = newHash;
                    indexes[i + 1] = index;
                    ++numMembers;
                }
                else if (comparison < 0)
                {
                hashes[i + 1] = hashes[i];
                indexes[i + 1] = indexes[i];
                }
                else
                {
                    #if _Debug
                    return "Error in Interface::InsertIntoHashTable (const Member&, intruction_t): Table  "
                        "already contains member!";
                    #endif
                    return "";
                }
            }
            else
            {
                hashes[i] = hashes[i + 1];
            }
        }
        return 0;
    }

    T Find (const char* aName)
    {
        if (aName == nullptr)
            return 0;

        /// Perform a binary search to find the first instance of the hash the binary search yields.

        uint32_t hash = HashString (aName);

        T index,
            low = 0,
            localNumMebmers = numMembers,
            high = localNumMebmers - 1;

        while (low <= high)
        {
            T mid = (low + high) / 2;

            hash_t currentHash = hashes[mid];
            if (currentHash == hash)
            {
                index = mid;
                    /// Check for collisions
                while (true)
                {
                    int comparison = strcmp (aName, members (index));
                    if (comparison == 0)
                        return index;
                    if (comparison < 0)
                    {
                        if (index == 0 || hashes[index - 1] != hash)
                            return 0;
                        --index;
                    }
                    else
                    {
                        if (index + 1 >= numMembers || hashes[index + 1] != hash)
                            return 0;
                        ++index;
                    }
                }
            }
            else if (currentHash < hash)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return 0;
    }

    /** Returns a hash of the input string. */
    static uint32_t HashString (const char stringToHash[], uint32_t seed = 0)
    {
        uint32_t hash = seed;
        while (*stringToHash)
        {
            hash = hash * 101  +  *stringToHash++;
        }
        return hash;
    }

    ///#################################################################################################################
    protected:
    ///#################################################################################################################

    TObject* self;
    InterfaceFunction members;

    T numMembers;
    T* indexes;
    hash_t* hashes;
};
}
#endif // _I2P__TextInterface_header
