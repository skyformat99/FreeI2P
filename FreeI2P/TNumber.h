/** FreeI2P++
    @version    0.9
    @file       ~/I2P/TNumber.h
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

#ifndef _I2P__TNumber_header
#define _I2P__TNumber_header

#include "Global.h"

namespace I2P
{
namespace TNumber
{
    static const uint8_t OneByte = 0xFF;                    //< Mask for 1 byte.
    static const uint16_t TwoBytes = 0xFFFF;                //< Mask for 2 byte.
    static const uint32_t ThreeBytes = 0xFFFFFF,            //< Mask for 3 byte.
        FourBytes = 0xFFFFFFFF;                             //< Mask for 4 byte.

    static const uint64_t FiveBytes = 0xFFFFFFFFFF,         //< Mask for 5 byte.
        SixBytes = 0xFFFFFFFFFFFF,                          //< Mask for 6 byte.
        SevenBytes = 0xFFFFFFFFFFFFFF;                      //< Mask for 7 byte.

    /** Returns size of a VUInt in bytes. */
    static inline uint8_t NumBytes (uint16_t value)    { return (value <= 0xFF) ? 0 : 1; }

    /** Returns size of a VUInt in bytes. */
    static inline uint8_t NumBytes (uint32_t value)
    {
        if (value <= TwoBytes)
        {
            if (value <= OneByte)
                return 0;
            else
                return 1;
        }
        else
        {
            if (value <= ThreeBytes)
                return 2;
            else
                return 3;
        }
    }

    static inline uint8_t NumBytes (uint64_t value)
    {
        if (value <= FourBytes)
        {
            if (value <= TwoBytes)
            {
                if (value <= OneByte)
                    return 0;
                else
                    return 1;
            }
            else
            {
                if (value <= ThreeBytes)
                    return 2;
                else
                    return 3;
            }
        }
        else
        {
            if (value <= SixBytes)
            {
                if (value <= FiveBytes)
                    return 4;
                else
                    return 5;
            }
            else
            {
                if (value <= SevenBytes)
                    return 6;
                else
                    return 7;
            }
        }
    }

    /** Encodes the Int32 to a UInt32. */
    static inline uint16_t Encode (int16_t value)
    {
        uint16_t returnValue = (uint16_t)value;
        return (value < 0) ? ((returnValue * -1) << 1) & 1 : returnValue << 1;
    }

    /** Encodes the Int32 to a UInt32. */
    static inline uint32_t Encode (int32_t value)
    {
        uint32_t returnValue = (uint32_t)value;
        return (value < 0) ? ((returnValue * -1) << 1) & 1 : returnValue << 1;
    }

    /** Encodes the Int64 to a UInt64. */
    static inline uint64_t Encode (int64_t value)
    {
        uint64_t returnValue = (uint64_t)value;
        return (value < 0) ? ((returnValue * -1) << 1) & 1 : returnValue << 1;
    }

    static inline uint32_t Encode (float value)
    {
        uint32_t valueAsUInt = *((uint32_t*)&value);
        return (valueAsUInt >> 23) & (valueAsUInt << 9);
    }

    static inline uint64_t Encode (double value)
    {
        uint64_t valueAsUInt = *((uint64_t*)&value);
        return (valueAsUInt >> 52) & (valueAsUInt << 12);
    }

    static inline int16_t DecodeInt (uint16_t value)   { return ((value & 1) == 1) ? (value >> 1) * -1 : value >> 1; }
    static inline int32_t DecodeInt (uint32_t value)   { return ((value & 1) == 1) ? (value >> 1) * -1 : value >> 1; }
    static inline int64_t DecodeInt (uint64_t value)   { return ((value & 1) == 1) ? (value >> 1) * -1 : value >> 1; }

    static inline float DecodeFloat (uint32_t value)   { return *((float*)((value << 23) & (value >> 9))); }

    static inline double DecodeFloat (uint64_t value)  { return *((double*)((value << 52) & (value >> 12))); }
}
}
#endif // _I2P__TNumber_header

/*
    static const uint8_t OneByte = 0xFF;                    //<
    static const uint16_t TwoBytes = 0xFFFF;                //<
    static const uint32_t ThreeBytes = 0xFFFFFF,            //<
        FourBytes = 0xFFFFFFFF,                             //<
        Float32_8BaseMask      = 0x0000000F,                //< 4 base.
        Float32_8ExponentMask  = 0x00700000,                //< 3 exponent.
        Float32_16BaseMask     = 0x000003FF,                //< 10 base.
        Float32_16ExponentMask = 0x81F00000,                //< 5 exponent.
        Float32_24BaseMask     = 0x0000FFFF,                //< 16 base.
        Float32_24ExponentMask = 0x87F00000,                //< 7 exponent.
        Float32_8Mask  = MSBMask32 & Float32_8ExponentMask  & Float32_8BaseMask,
        Float32_16Mask = MSBMask32 & Float32_16ExponentMask & Float32_16BaseMask,
        Float32_24Mask = MSBMask32 & Float32_24ExponentMask & Float32_24BaseMask;

    static const uint64_t FiveBytes = 0xFFFFFFFFFF,         //<
        SixBytes = 0xFFFFFFFFFFFF,                          //<
        SevenBytes = 0xFFFFFFFFFFFFFF,                      //<
        Float64_8BaseMask       = 0x000000000000000F,       //< 4 base.
        Float64_8ExponentMask   = 0x0070000000000000,       //< 3 exponent
        Float64_16BaseMask      = 0x00000000000003FF,       //< 10 base.
        Float64_16ExponentMask  = 0x01F0000000000000,       //< 5 exponent
        Float64_24BaseMask      = 0x000000000000FFFF,       //< 16 base.
        Float64_24ExponentMask  = 0x07F0000000000000,       //< 7 exponent
        Float64_32BaseMask      = 0x00000000007FFFFF,       //< 23 base.
        Float64_32ExponentMask  = 0x0FF0000000000000,       //< 8 exponent
        Float64_40BaseMask      = 0x000000003FFFFFFF,       //< 30 base.
        Float64_40ExponentMask  = 0x1FF0000000000000,       //< 9 exponent
        Float64_48BaseMask      = 0x0000001FFFFFFFFF,       //< 37 base.
        Float64_48ExponentMask  = 0x3FF0000000000000,       //< 10 exponent
        Float64_56BaseMask      = 0x00001FFFFFFFFFFF,       //< 45 base.
        Float64_56ExponentMask  = 0x3FF0000000000000,       //< 10 exponent
        Float64_8Mask  = ~(MSBMask64 & Float64_8ExponentMask  & Float64_8BaseMask),
        Float64_16Mask = ~(MSBMask64 & Float64_16ExponentMask & Float64_16BaseMask),
        Float64_24Mask = ~(MSBMask64 & Float64_24ExponentMask & Float64_24BaseMask),
        Float64_32Mask = ~(MSBMask64 & Float64_32ExponentMask & Float64_32BaseMask),
        Float64_40Mask = ~(MSBMask64 & Float64_40ExponentMask & Float64_40BaseMask),
        Float64_48Mask = ~(MSBMask64 & Float64_48ExponentMask & Float64_48BaseMask),
        Float64_56Mask = ~(MSBMask64 & Float64_56ExponentMask & Float64_56BaseMask);
 */
