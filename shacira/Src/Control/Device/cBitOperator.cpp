//## begin module%40A1F8F50157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A1F8F50157.cm

//## begin module%40A1F8F50157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40A1F8F50157.cp

//## Module: cBitOperator%40A1F8F50157; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cBitOperator.cpp

//## begin module%40A1F8F50157.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%40A1F8F50157.additionalIncludes

//## begin module%40A1F8F50157.includes preserve=yes
//## end module%40A1F8F50157.includes

// cBitOperator
#include "Control/Device/cBitOperator.h"
//## begin module%40A1F8F50157.additionalDeclarations preserve=yes

USHORT_T byte_to_word(USHORT_T word_value)
{
   return SWAP_WORD(word_value);
}

ULONG_T byte_to_long(ULONG_T long_value)
{
   USHORT_T high = HIGH_WORD(long_value);
   USHORT_T low = LOW_WORD(long_value);
   high = SWAP_WORD(high);
   low = SWAP_WORD(low);
   return MK_LONG(high,low);
}

ULONG_T word_to_long(ULONG_T long_value)
{
   return SWAP_DWORD(long_value);
}

FLOAT_T byte_to_float(FLOAT_T float_value)
{
   ULONG_T * long_value = (ULONG_T*)(&float_value);
   USHORT_T high = HIGH_WORD(*long_value);
   USHORT_T low = LOW_WORD(*long_value);
   high = SWAP_WORD(high);
   low = SWAP_WORD(low);
   *long_value = MK_LONG(high, low);
   return float_value;
}

DOUBLE_T byte_to_double(DOUBLE_T double_value)
{
   return double_value;
}


//## end module%40A1F8F50157.additionalDeclarations


// Class cBitOperator 









cBitOperator::cBitOperator()
  //## begin cBitOperator::cBitOperator%.hasinit preserve=no
      : _Granularity(1), _DataType(UNDEFINED), _CHAR_Value(0), _SHORT_Value(0), _LONG_Value(0), _FLOAT_Value(0), _DOUBLE_Value(0)
  //## end cBitOperator::cBitOperator%.hasinit
  //## begin cBitOperator::cBitOperator%.initialization preserve=yes
  //## end cBitOperator::cBitOperator%.initialization
{
  //## begin cBitOperator::cBitOperator%.body preserve=yes
  //## end cBitOperator::cBitOperator%.body
}

cBitOperator::cBitOperator(const cBitOperator &right)
  //## begin cBitOperator::cBitOperator%copy.hasinit preserve=no
      : _Granularity(1), _DataType(UNDEFINED), _CHAR_Value(0), _SHORT_Value(0), _LONG_Value(0), _FLOAT_Value(0), _DOUBLE_Value(0)
  //## end cBitOperator::cBitOperator%copy.hasinit
  //## begin cBitOperator::cBitOperator%copy.initialization preserve=yes
  //## end cBitOperator::cBitOperator%copy.initialization
{
  //## begin cBitOperator::cBitOperator%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cBitOperator::cBitOperator%copy.body
}

cBitOperator::cBitOperator (UCHAR_T granularity)
  //## begin cBitOperator::cBitOperator%1084360927.hasinit preserve=no
      : _Granularity(1), _DataType(UNDEFINED), _CHAR_Value(0), _SHORT_Value(0), _LONG_Value(0), _FLOAT_Value(0), _DOUBLE_Value(0)
  //## end cBitOperator::cBitOperator%1084360927.hasinit
  //## begin cBitOperator::cBitOperator%1084360927.initialization preserve=yes
  //## end cBitOperator::cBitOperator%1084360927.initialization
{
  //## begin cBitOperator::cBitOperator%1084360927.body preserve=yes
   _Granularity = granularity;
  //## end cBitOperator::cBitOperator%1084360927.body
}


cBitOperator::~cBitOperator()
{
  //## begin cBitOperator::~cBitOperator%.body preserve=yes
  //## end cBitOperator::~cBitOperator%.body
}



//## Other Operations (implementation)
void cBitOperator::SetValue (UCHAR_T data_type, UCHAR_T value)
{
  //## begin cBitOperator::SetValue%1084360911.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_BIT_8:
         _CHAR_Value = value;
         break;
      case SH_SHORT:
      case SH_USHORT:
         _SHORT_Value = byte_to_word(value);
         break;
      case SH_BIT_16:
         _SHORT_Value = value;
         break;
      case SH_LONG:
      case SH_ULONG:
         _LONG_Value = byte_to_long(value);
         break;
      case SH_BIT_32:
         _LONG_Value = value;
         break;
      default:
         throw cError(DEVICE_INVALID_DATATYPE, 0, 
                     cConvUtils::StringValue(_DataType).c_str());
      }
   } else if (_Granularity == 2) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 4) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 8) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   }
  //## end cBitOperator::SetValue%1084360911.body
}

void cBitOperator::SetValue (UCHAR_T data_type, USHORT_T value)
{
  //## begin cBitOperator::SetValue%1084360912.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_BIT_8:
         _CHAR_Value = (UCHAR_T)value;
         break;
      case SH_SHORT:
      case SH_USHORT:
         _SHORT_Value = byte_to_word(value);
         break;
      case SH_BIT_16:
         _SHORT_Value = value;
         break;
      case SH_LONG:
      case SH_ULONG:
         _LONG_Value = byte_to_long(value);
         break;
      case SH_BIT_32:
         _LONG_Value = value;
         break;
      default:
         throw cError(DEVICE_INVALID_DATATYPE, 0, 
                     cConvUtils::StringValue(_DataType).c_str());
      }
   } else if (_Granularity == 2) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 4) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 8) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   }
  //## end cBitOperator::SetValue%1084360912.body
}

void cBitOperator::SetValue (UCHAR_T data_type, ULONG_T value)
{
  //## begin cBitOperator::SetValue%1084360913.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_BIT_8:
         _CHAR_Value = (UCHAR_T)value;
         break;
      case SH_SHORT:
      case SH_USHORT:
         _SHORT_Value = byte_to_word((UCHAR_T)value);
         break;
      case SH_BIT_16:
         _SHORT_Value = (USHORT_T)value;
         break;
      case SH_LONG:
      case SH_ULONG:
         _LONG_Value = byte_to_long(value);
         break;
      case SH_BIT_32:
         _LONG_Value = value;
         break;
      default:
         throw cError(DEVICE_INVALID_DATATYPE, 0, 
                     cConvUtils::StringValue(_DataType).c_str());
      }
   } else if (_Granularity == 2) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 4) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 8) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   }
  //## end cBitOperator::SetValue%1084360913.body
}

void cBitOperator::SetValue (UCHAR_T data_type, CHAR_T value)
{
  //## begin cBitOperator::SetValue%1084360914.body preserve=yes
   SetValue(data_type, (UCHAR_T)value);
  //## end cBitOperator::SetValue%1084360914.body
}

void cBitOperator::SetValue (UCHAR_T data_type, SHORT_T value)
{
  //## begin cBitOperator::SetValue%1084360915.body preserve=yes
   SetValue(data_type, (USHORT_T)value);
  //## end cBitOperator::SetValue%1084360915.body
}

void cBitOperator::SetValue (UCHAR_T data_type, LONG_T value)
{
  //## begin cBitOperator::SetValue%1084360916.body preserve=yes
   SetValue(data_type, (UCHAR_T)value);
  //## end cBitOperator::SetValue%1084360916.body
}

void cBitOperator::SetValue (UCHAR_T data_type, FLOAT_T value)
{
  //## begin cBitOperator::SetValue%1110194499.body preserve=yes
   _FLOAT_Value = value;
  //## end cBitOperator::SetValue%1110194499.body
}

void cBitOperator::SetValue (UCHAR_T data_type, DOUBLE_T value)
{
  //## begin cBitOperator::SetValue%1110194500.body preserve=yes
   _DOUBLE_Value = value;
  //## end cBitOperator::SetValue%1110194500.body
}

cBitOperator::operator UCHAR_T ()
{
  //## begin cBitOperator::operator UCHAR_T%1084360917.body preserve=yes
   return _CHAR_Value;
  //## end cBitOperator::operator UCHAR_T%1084360917.body
}

cBitOperator::operator USHORT_T ()
{
  //## begin cBitOperator::operator USHORT_T%1084360918.body preserve=yes
   return _SHORT_Value;
  //## end cBitOperator::operator USHORT_T%1084360918.body
}

cBitOperator::operator ULONG_T ()
{
  //## begin cBitOperator::operator ULONG_T%1084360919.body preserve=yes
   return _LONG_Value;
  //## end cBitOperator::operator ULONG_T%1084360919.body
}

cBitOperator::operator CHAR_T ()
{
  //## begin cBitOperator::operator CHAR_T%1084360920.body preserve=yes
   return _CHAR_Value;
  //## end cBitOperator::operator CHAR_T%1084360920.body
}

cBitOperator::operator SHORT_T ()
{
  //## begin cBitOperator::operator SHORT_T%1084360921.body preserve=yes
   return _SHORT_Value;
  //## end cBitOperator::operator SHORT_T%1084360921.body
}

cBitOperator::operator LONG_T ()
{
  //## begin cBitOperator::operator LONG_T%1084360922.body preserve=yes
   return _LONG_Value;
  //## end cBitOperator::operator LONG_T%1084360922.body
}

cBitOperator::operator FLOAT_T ()
{
  //## begin cBitOperator::operator FLOAT_T%1110194501.body preserve=yes
   return _FLOAT_Value;
  //## end cBitOperator::operator FLOAT_T%1110194501.body
}

cBitOperator::operator DOUBLE_T ()
{
  //## begin cBitOperator::operator DOUBLE_T%1110194502.body preserve=yes
   return _DOUBLE_Value;
  //## end cBitOperator::operator DOUBLE_T%1110194502.body
}

void cBitOperator::SetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cBitOperator::SetBit%1084360923.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = SET_BIT_B(_CHAR_Value, pos);
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      _SHORT_Value = SET_BIT_W(_SHORT_Value, pos);
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      _LONG_Value = SET_BIT_DW(_LONG_Value, pos);
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
  //## end cBitOperator::SetBit%1084360923.body
}

void cBitOperator::ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cBitOperator::ResetBit%1084360924.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = RESET_BIT_B(_CHAR_Value, pos);
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      _SHORT_Value = RESET_BIT_W(_SHORT_Value, pos);
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      _LONG_Value = RESET_BIT_DW(_LONG_Value, pos);
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
  //## end cBitOperator::ResetBit%1084360924.body
}

UCHAR_T cBitOperator::GetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cBitOperator::GetBit%1084360966.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      return GET_BIT_B(_CHAR_Value, pos) > 0;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      return GET_BIT_W(_SHORT_Value, pos) > 0;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      return GET_BIT_DW(_LONG_Value, pos) > 0;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
  //## end cBitOperator::GetBit%1084360966.body
}

void cBitOperator::SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cBitOperator::SetPattern%1084360925.body preserve=yes
   UCHAR_T i;
   UCHAR_T set;
   UCHAR_T shift;
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      shift = 8 - length;
      pattern = (pattern << shift) >> shift;
      for (i=0; i<length; i++) {
         set = ((UCHAR_T)pattern & 1);
         if (set) {
            _CHAR_Value = SET_BIT_B(_CHAR_Value, pos+i);
         } else {
            _CHAR_Value = RESET_BIT_B(_CHAR_Value, pos+i);
         }
         pattern = pattern >> 1;
      }
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      shift = 16 - length;
      pattern = (pattern << shift) >> shift;
      for (i=0; i<length; i++) {
         set = ((UCHAR_T)pattern & 1);
         if (set) {
            _SHORT_Value = SET_BIT_W(_SHORT_Value, pos+i);
         } else {
            _SHORT_Value = RESET_BIT_W(_SHORT_Value, pos+i);
         }
         pattern = pattern >> 1;
      }
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      shift = 32 - length;
      pattern = (pattern << shift) >> shift;
      for (i=0; i<length; i++) {
         set = ((UCHAR_T)pattern & 1);
         if (set) {
            _LONG_Value = SET_BIT_DW(_LONG_Value, pos+i);
         } else {
            _LONG_Value = RESET_BIT_DW(_LONG_Value, pos+i);
         }
         pattern = pattern >> 1;
      }
      break;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
  //## end cBitOperator::SetPattern%1084360925.body
}

ULONG_T cBitOperator::GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cBitOperator::GetPattern%1084360926.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      {
         UCHAR_T pattern = 0xffff << (16 - length);
         pattern = pattern >> (16 - length);
         pattern = pattern << pos;
         return (_CHAR_Value & pattern) >> pos;
      }
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      {
         USHORT_T pattern = 0xffff << (16 - length);
         pattern = pattern >> (16 - length);
         pattern = pattern << pos;
         return (_SHORT_Value & pattern) >> pos;
      }
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      {
         ULONG_T pattern = 0xffff << (16 - length);
         pattern = pattern >> (16 - length);
         pattern = pattern << pos;
         return (_LONG_Value & pattern) >> pos;
      }
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
  //## end cBitOperator::GetPattern%1084360926.body
}

UCHAR_T cBitOperator::BytePos (UCHAR_T data_type, UCHAR_T bit_pos)
{
  //## begin cBitOperator::BytePos%1084360928.body preserve=yes
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      return 0;
   case SH_SHORT:
   case SH_USHORT:
      if (bit_pos < 8) {
         return 1;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 0;
      }
      break;
   case SH_BIT_16:
      if (bit_pos < 8) {
         return 0;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 1;
      }
      break;
   case SH_LONG:
   case SH_ULONG:
      if (bit_pos < 8) {
         return 3;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 2;         
      } else if (bit_pos > 15 && bit_pos < 24) {
         return 1;         
      } else if (bit_pos > 23 && bit_pos < 32) {
         return 0;         
      }
      break;
   case SH_BIT_32:
      if (bit_pos < 8) {
         return 0;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 1;         
      } else if (bit_pos > 15 && bit_pos < 24) {
         return 2;         
      } else if (bit_pos > 23 && bit_pos < 32) {
         return 3;         
      }
      break;
   }
   return 0;
  //## end cBitOperator::BytePos%1084360928.body
}

//## Get and Set Operations for Class Attributes (implementation)

UCHAR_T cBitOperator::get_Granularity () const
{
  //## begin cBitOperator::get_Granularity%40A1F98A0203.get preserve=no
  return _Granularity;
  //## end cBitOperator::get_Granularity%40A1F98A0203.get
}

void cBitOperator::set_Granularity (UCHAR_T value)
{
  //## begin cBitOperator::set_Granularity%40A1F98A0203.set preserve=no
  _Granularity = value;
  //## end cBitOperator::set_Granularity%40A1F98A0203.set
}

// Additional Declarations
  //## begin cBitOperator%40A1F8F50157.declarations preserve=yes
  //## end cBitOperator%40A1F8F50157.declarations

//## begin module%40A1F8F50157.epilog preserve=yes
//## end module%40A1F8F50157.epilog
