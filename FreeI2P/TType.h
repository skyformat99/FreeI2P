/** FreeI2P++
    @version    0.9
    @file       ~/I2P/TType.h
    @author     Cale McCollough
    @copyright  Copyright 2015 © Ae Eye
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

#ifndef _I2P__TType_header
#define _I2P__TType_header

#include "Global.h"

namespace I2P
{
    
namespace _T
{
    static const uint8_t
        NumStandardTType = 32,          //< Number of standard data TType.
        MaxNumDataTType = 254,          //< The maximum number of data TType.
        NumTypes = 32,
        /// List of TType with UIDs.
        Null = 0,
        Void = 0,
        List = 1,
        Composition = 2,
        EndComposition = 3,
        Boolean = 4,
        UInt = 5,
        Int = 6,
        Float = 7,
        Backspace = 8,
        Atomic = 9,
        Return = 10,
        Timestamp = 11,
        Interrupt = 12,
        CloseExpression = 13,
        String16 = 14,
        String = 15,
        Struct = 16,
        DC1 = 17,
        DC2 = 18,
        DC3 = 19,
        DC4 = 20,
        Error = 21,
        Stream = 22,
        Packet = 23,
        Cancel = 24,
        EM = 25,
        Substitution = 26,
        Expression = 27,
        File = 28,
        Array = 29,
        KeyValue = 30,
        Object = 31,
        VArgsList = 128,
        Invalid = 32;

    const char VoidList[]           = { _T::Void, 0 },
        ListList[]                  = { _T::List, 0 },
        CompositionList[]           = { _T::Composition, 0 },
        EndCompositionList[]        = { _T::EndComposition, 0 },
        BooleanList[]               = { _T::Boolean, 0 },
        UIntList[]                  = { _T::UInt, 0 },
        IntList[]                   = { _T::Int, 0 },
        FloatList[]                 = { _T::Float, 0 },
        BackspaceList[]             = { _T::Backspace, 0 },
        AtomicList[]                = { _T::Atomic, 0 },
        ReturnList[]                = { _T::Return, 0 },
        TimestampList[]             = { _T::Timestamp, 0 },
        InterruptList[]             = { _T::Interrupt, 0 },
        CloseExpressionList[]       = { _T::CloseExpression, 0 },
        String16List[]              = { _T::String16, 0 },
        StringList[]                = { _T::String, 0 },
        StructList[]                = { _T::Struct, 0 },
        DC1List[]                   = { _T::DC1, 0 },
        DC2List[]                   = { _T::DC2, 0 },
        DC3List[]                   = { _T::DC3, 0 },
        DC4List[]                   = { _T::DC4, 0 },
        ErrorList[]                 = { _T::Error, 0 },
        StreamList[]                = { _T::Stream, 0 },
        PacketList[]                = { _T::Packet, 0 },
        CancelList[]                = { _T::Cancel, 0 },
        EMList[]                    = { _T::EM, 0 },
        SubstitutionList[]          = { _T::Substitution, 0 },
        ExpressionList[]            = { _T::Expression, 0 },
        FileList[]                  = { _T::File, 0 },
        ArrayList[]                 = { _T::Array, 0 },
        KeyValueList[]              = { _T::KeyValue, 0 },
        ObjectList[]                = { _T::Object, 0 },
        VoidVoidList[]              = { _T::Void, _T::Void, 0 },
        VoidListList[]              = { _T::Void, _T::List, 0 },
        VoidCompositionList[]       = { _T::Void, _T::Composition, 0 },
        VoidEndCompositionList[]    = { _T::Void, _T::EndComposition, 0 },
        VoidBooleanList[]           = { _T::Void, _T::Boolean, 0 },
        VoidUIntList[]              = { _T::Void, _T::UInt, 0 },
        VoidIntList[]               = { _T::Void, _T::Int, 0 },
        VoidFloatList[]             = { _T::Void, _T::Float, 0 },
        VoidBackspaceList[]         = { _T::Void, _T::Backspace, 0 },
        VoidAtomicList[]            = { _T::Void, _T::Atomic, 0 },
        VoidReturnList[]            = { _T::Void, _T::Return, 0 },
        VoidTimestampList[]         = { _T::Void, _T::Timestamp, 0 },
        VoidInterruptList[]         = { _T::Void, _T::Interrupt, 0 },
        VoidCloseExpressionList[]   = { _T::Void, _T::CloseExpression, 0 },
        VoidString16List[]          = { _T::Void, _T::String16, 0 },
        VoidStringList[]            = { _T::Void, _T::String, 0 },
        VoidStructList[]            = { _T::Void, _T::Struct, 0 },
        VoidDC1List[]               = { _T::Void, _T::DC1, 0 },
        VoidDC2List[]               = { _T::Void, _T::DC2, 0 },
        VoidDC3List[]               = { _T::Void, _T::DC3, 0 },
        VoidDC4List[]               = { _T::Void, _T::DC4, 0 },
        VoidErrorList[]             = { _T::Void, _T::Error, 0 },
        VoidStreamList[]            = { _T::Void, _T::Stream, 0 },
        VoidPacketList[]            = { _T::Void, _T::Packet, 0 },
        VoidCancelList[]            = { _T::Void, _T::Cancel, 0 },
        VoidEMList[]                = { _T::Void, _T::EM, 0 },
        VoidSubstitutionList[]      = { _T::Void, _T::Substitution, 0 },
        VoidExpressionList[]        = { _T::Void, _T::Expression, 0 },
        VoidFileList[]              = { _T::Void, _T::File, 0 },
        VoidArrayList[]             = { _T::Void, _T::Array, 0 },
        VoidKeyValueList[]          = { _T::Void, _T::KeyValue, 0 },
        VoidObjectList[]            = { _T::Void, _T::Object, 0 };

    inline uint8_t Width (uint8_t type, uint8_t width)  { return type & (width << 5); }

    /** Returns true if the type is a valid list type. */
    inline bool IsValid (uint8_t type)
    {
        static const uint8_t MaxWidths[] =
        {
            0,                  //< Void
            0,                  //< List
            0,                  //< Composition
            0,                  //< ETX
            1,                  //< Boolean
            8,                  //< UInt
            8,                  //< Int
            8,                  //< Float
            0,                  //< Backspace
            0,                  //< Reserved9
            8,                  //< LF
            8,                  //< Timestamp
            0,                  //< Interrupt
            8, //sizeof (word_t), //< Return
            0,                  //< String16
            0,                  //< String
            8,                  //< Struct
            0,                  //< DC1
            0,                  //< DC2
            0,                  //< DC3
            0,                  //< DC4
            8,                  //< Exception
            0,                  //< Stream
            0,                  //< Packet
            0,                  //< Cancel
            8,                  //< EM
            1,                  //< Substtution
            4,//sizeof (word_t), //< Expression
            0,                  //< File
            0,                  //< Array
            0,                  //< KeyValue
            1                   //< Object
        };

        //return (type & 0x1F) & (maxWidth << 5);
        return (type >> 5) <= MaxWidths [type & 0x1F];
    }
    
    /** Returns the name of the given list type. */
    static const char* GetName (uint8_t type)
    {
        //uint8_t length = (type & 0xE0) >> 5;
        #if IncludeHelpLables
        switch (type)
        {
            case Void:          return "Void";
            case List:          return "List";
            case Composition:   return "Composition";
            case ETX:           return "/Composition";
            case Boolean:       return "Boolean";
            case UInt:          return "UInt";
            case Int:           return "Int";
            case Float:         return "Float";
            case Backspace:     return "Backspace";
            case Reserved9:     return "Reserved9";
            case LF:            return "CloseExpression";
            case Timestamp:     return "Timestamp";
            case Interrupt:     return "Interrupt";
            case Return:        return "Return";
            case String16:      return "String16";
            case String:        return "String";
            case Struct:        return "Struct";
            case DC1:           return "DC1";
            case DC2:           return "DC2";
            case DC3:           return "DC3";
            case DC4:           return "DC4";
            case Exception:     return "Exception";
            case Stream:        return "Stream";
            case Packet:        return "Packet";
            case Cancel:        return "Cancel";
            case EM:            return "EM";
            case Substtution:   return "Substitution";
            case Expression:    return "Expression";
            case File:          return "File";
            case Array:         return "Array";
            case KeyValue:      return "KeyValue";
            case Object:        return "Object";
            default:            return "Invalid";
        }
        #else
        return "";
        #endif // IncludeHelpLabels
    }
}
}
#endif // _I2P__TType_header

