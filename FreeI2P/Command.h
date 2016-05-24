/** FreeI2P++
    @version    0.9
    @file       ~/I2P/Command.h
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

#ifndef _I2P_Command_Header
#define _I2P_Command_Header

#include "Global.h"

namespace I2P
{
/** @namesapce Command

*/
namespace Command
{

static const uint8_t Null = 0,      //<     "Null"
    SOH = 1,                        //<     "Start of header"
    STX = 2,                        //<     "Start of text"
    ETX = 3,                        //<     "End of text"
    EOT = 4,                        //<     "End of transmission"
    ENQ = 5,                        //<     "Enquiry"
    ACK = 6,                        //<     "Acknowledgment"
    BEL = 7,                        //<     "Bell"
    BS = 8,                         //<     "Backspace"
    HT = 9,                         //<     "Horizontal tab"
    LF = 10,                        //<     "Line feed"
    VT = 11,                        //<     "Vertical tab"
    FF = 12,                        //<     "Form feed"
    CR = 13,                        //<     "Carriage return"
    SO = 14,                        //<     "Shift out"
    SI = 15,                        //<     "Shift in"
    DLE = 16,                       //<     "Data link escape"
    DC1 = 17,                       //<     "Selected Device control (DC1)"
    DC2 = 18,                       //<     "Node Device control (DC2)"
    DC3 = 19,                       //<     "Safe Device control (DC3)"
    DC4 = 20,                       //<     "Global Device control (DC4)"
    NAK = 21,                       //<     "Negative acknowledge"
    SYN = 22,                       //<     "Synchronous idle"
    ETB = 23,                       //<     "End of transmission block"
    CAN = 24,                       //<     "Cancel",
    EM = 25,                        //<     "End of medium"
    SUB = 26,                       //<     "Substitute"
    ESC = 27,                       //<     "Escape"
    FS = 28,                        //<     "File separator"
    GS = 29,                        //<     "Group separator"
    RS = 30,                        //<     "Record separator"
    US = 31,                        //<     "Unit separator" Selects an objects
    NumCommands = 128,              //< The number of Commands.
    Length0 = 0,
    Length1 = 1 << 6,
    Length2 = 2 << 6,
    Length3 = 3 << 6;

/** Returns the name of one of the Commands. */
static const char* GetName (uint8_t command)
{
    #if _IncludeHelpLabels
    switch (command)
    {
        case SOH:           return "[SOH]";
        case STX:           return "[STX]";
        case ETX:           return "[ETX]";
        case EOT:           return "[EOT]";
        case ENQ:           return "[Enq]";
        case ACK:           return "[Ack]";
        case BEL:           return "[Bell]";
        case BS:            return "[Bs]";
        case HT:            return "[HT]";
        case LF:            return "[LF]";
        case VT:            return "[VT]";
        case FF:            return "[FF]";
        case CR:            return "[CR]";
        case SO:            return "[SO]";
        case SI:            return "[SI]";
        case DLE:           return "[DLE]";
        case DC1:           return "[DC1]";
        case DC2:           return "[DC2]";
        case DC3:           return "[DC3]";
        case DC4:           return "[DC4]";
        case NAK:           return "[NAck]";
        case SYN:           return "[Sync]";
        case ETB:           return "[ETB]";
        case CAN:           return "[Canl]";
        case EM:            return "[EM]";
        case SUB:           return "[Sub]";
        case ESC:           return "[ESC]";
        case FS:            return "[FS]";
        case GS:            return "[GS]";
        case RS:            return "[RS]";
        case US:            return "[US]";
        case ' ':           return "[ ]";
        case '!':           return "[!]";
        case '\"':          return "[\"]";
        case '#':           return "[#]";
        case ':':           return "[$]";
        case '%':           return "[%]";
        case '&':           return "[&]";
        case '\\':          return "[']";
        case '(':           return "[(]";
        case ')':           return "[)]";
        case '*':           return "[*]";
        case '+':           return "[+]";
        case ',':           return "[,]";
        case '-':           return "[-]";
        case '.':           return "[.]";
        case '/':           return "[/]";
        case ':':           return "[;]";
        case ';':           return "[;]";
        case '<':           return "[<]";
        case '=':           return "[=]";
        case '>':           return "[>]";
        case '?':           return "[?]";
        case '@':           return "[@]";
        case '[':           return "[[]";
        case '\\':          return "[\\]";
        case ']':           return "[]]";
        case '^':           return "[^]";
        case '_':           return "[_]";
        case '`':           return "[`]";
        case '{':           return "[{]";
        case '|':           return "[|]";
        case '}':           return "[}]";
        case '~':           return "[~]";
        case 127:           return "[Del]";
        default:            return "[Invalid]";
    }
    #else
    return "";
    #endif // _IncludeHelpLabels
}
}
}
#endif // _I2P_TCommand_header
