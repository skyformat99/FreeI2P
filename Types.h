/** FreeIP2++
    @version    0.9
    @file       ~/I2P/Global.h
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

#ifndef _Types_h
#define _Types_h

#include "stdint.h"
#include "TType.h"

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Stuff you care about.
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define _Debug                      1

#define _I2P__IncludeHelpStrings    1
#define _I2P__UsingConsole          0
#define _I2P__IncludeLabels         1

#define _I2P__MaxSignatureLength    16

/* To change the CPU word size, ensure that only one of the following three are non-zero. */
#define _16Bit                      0
#define _32Bit                      1
#define _64Bit                      0

#define _mbed                       1

typedef uint32_t hash_t;

static const uint8_t MaxNameLength = 20;

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Stuff you probably don't care about.
///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdarg.h>

#ifndef nullptr
#define nullptr                     0
#endif

static const uint16_t MaxNumMembers = 0x1FFF;
static const uint32_t MaxNumObjects = 0x1FFFFFFF;
static const uint64_t MaxNumRooms   = 0x1FFFFFFFFFFFFFFF;

static const uint16_t MSb16 = 0x8000;
static const uint32_t MSb32 = 0x80000000;
static const uint64_t MSb64   = 0x8000000000000000;

static const uint16_t FWord16 = 0xFFFF;
static const uint32_t FWord32 = 0xFFFFFFFF;
static const uint64_t FWord64 = 0xFFFFFFFFFFFFFFFF;

#if _16Bit
typedef uint16_t word_t;
typedef int16_t sword_t;
static const uint8_t MS2bShift = 14;
static const word_t WordMS2bMask = ~(0b11 << MS2bShift);
static const word_t FWord = 0xFFFF;
#endif
#if _32Bit
typedef uint32_t word_t;
typedef int32_t sword_t;
static const uint8_t MS2bShift = 29;
static const word_t WordMS2bMask = ~(0b11 << MS2bShift);
static const word_t FWord = 0xFFFFFFFF;
#endif
#if _64Bit
typedef uint64_t word_t;
typedef int64_t sword_t;
static const uint8_t MS2bShift = 62;
static const word_t WordMS2bMask = ~(0b11 << MS2bShift);
static const word_t FWord = 0xFFFFFFFFFFFFFFFF;
#endif

typedef uint64_t ttimestamp_t;      //<

#endif // _Types_h
