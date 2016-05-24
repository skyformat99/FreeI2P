/** FreeI2P++
    @version    0.9
    @file       ~/I2P/TArray.h
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

#ifndef _I2P__TArray
#define _I2P__TArray

#include "Global.h"

namespace I2P
{
/** TArray sruct  
    The way arrays work,
*/
struct TArray
{
    static const uint8_t MaxDimensions = 255;           //< The maximum number of dimensions allowed in an array.
    
    uint8_t NumDimensions;                              //< The number of dimensions in the array.
    uint32_t ElementSize;                               //< The size of an element in the array.
    
    uint8_t* Dimensions;                                //< Pointer to the dimensions 8-255 if there are any.
    void* Data;                                         //< pointer to the array data.
    
    /** Constructs an array with the given number of dimensions. */
    TArray (word_t anElementSize, uint8_t numDimensions, uint8_t* dimensions = nullptr, void* data = nullptr);
    
    uint32_t GetDimension (uint8_t index);              //< Gets the dimension at the given index. 
};
}
#endif // _I2P__TArray
