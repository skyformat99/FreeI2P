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

#ifndef _I2P__Global_header
#define _I2P__Global_header

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

#if _mbed
#include "mbed.h"
static Timer _mbedTimer;
#endif // _mbed

#if _Debug
#include "mbed.h"

static DigitalOut redLED (LED_RED, 1),
    greenLED (LED_GREEN, 1),
    blueLED (LED_BLUE, 1);

static DigitalOut& statusLED = greenLED;

static Serial debug (USBTX, USBRX), // Tx, Rx
    uart1 (PTC16, PTC17);           //< For FRDM-K64F. Todo: Write easy-to-add-to macros for various dev boards.

static Ticker statusBlinker,
    assertionBlinker;
    
static void SetStatusLED (DigitalOut& newDigitalOut)
{
    redLED = 1;
    greenLED = 1;
    blueLED = 1;
    statusLED = newDigitalOut;
}

/** Blinks the status RGB LED on the mbed board. */
static void BlinkStatusLED ()
{
    static bool blinkOn = false;
        
    if (blinkOn)
    {
        statusLED = 0;
        blinkOn = false;
    }
    else
    {
        statusLED = 1;
        blinkOn = true;
    }
}

static void BlinkAssertLEDs ()
{
    static bool blinkOn = false;
        
    if (blinkOn)
    {
        redLED = 0;
        blueLED = 1;
        blinkOn = false;
    }
    else
    {
        redLED = 1;
        blueLED = 0;
        blinkOn = true;
    }
}

#define Assert(statement, message)\
{\
    if (!(statement))\
    {\
        statusBlinker.detach ();\
        redLED = 1;\
        greenLED = 1;\
        blueLED = 1;\
        assertionBlinker.attach (&BlinkAssertLEDs, 0.2f);\
        debug.printf("Assert: %s\n\r%s, line %d\n\r", #message, __FILE__, __LINE__);\
        while (true);\
    }\
}

/** Prints a line of tokens to the debug stream. */
static void PrintLine (char token)
{
    debug.putc ('\r');
    for (int i = 0; i < 80; ++i)
        debug.putc (token);
    debug.putc ('\n');
    debug.putc ('\r');
}
#endif // _Debug

static time_t _startTime;

static void InitializeTimer ()
{
    _startTime = time (NULL);
    #if __mbed
    _mbedTimer.start ();
    #endif
}
#endif // _I2P__Global_header
