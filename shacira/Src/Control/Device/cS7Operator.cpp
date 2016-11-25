//## begin module%40A20C7702AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A20C7702AF.cm

//## begin module%40A20C7702AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40A20C7702AF.cp

//## Module: cS7Operator%40A20C7702AF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cS7Operator.cpp

//## begin module%40A20C7702AF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%40A20C7702AF.additionalIncludes

//## begin module%40A20C7702AF.includes preserve=yes
//## end module%40A20C7702AF.includes

// cS7Operator
#include "Control/Device/cS7Operator.h"
//## begin module%40A20C7702AF.additionalDeclarations preserve=yes
//## end module%40A20C7702AF.additionalDeclarations


// Class cS7Operator 

cS7Operator::cS7Operator()
  //## begin cS7Operator::cS7Operator%.hasinit preserve=no
  //## end cS7Operator::cS7Operator%.hasinit
  //## begin cS7Operator::cS7Operator%.initialization preserve=yes
  : cBitOperator(1)
  //## end cS7Operator::cS7Operator%.initialization
{
  //## begin cS7Operator::cS7Operator%.body preserve=yes
  //## end cS7Operator::cS7Operator%.body
}

cS7Operator::cS7Operator(const cS7Operator &right)
  //## begin cS7Operator::cS7Operator%copy.hasinit preserve=no
  //## end cS7Operator::cS7Operator%copy.hasinit
  //## begin cS7Operator::cS7Operator%copy.initialization preserve=yes
  //## end cS7Operator::cS7Operator%copy.initialization
{
  //## begin cS7Operator::cS7Operator%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cS7Operator::cS7Operator%copy.body
}


cS7Operator::~cS7Operator()
{
  //## begin cS7Operator::~cS7Operator%.body preserve=yes
  //## end cS7Operator::~cS7Operator%.body
}



//## Other Operations (implementation)
void cS7Operator::SetValue (UCHAR_T data_type, UCHAR_T value)
{
  //## begin cS7Operator::SetValue%1084360930.body preserve=yes
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
  //## end cS7Operator::SetValue%1084360930.body
}

void cS7Operator::SetValue (UCHAR_T data_type, USHORT_T value)
{
  //## begin cS7Operator::SetValue%1084360931.body preserve=yes
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
  //## end cS7Operator::SetValue%1084360931.body
}

void cS7Operator::SetValue (UCHAR_T data_type, ULONG_T value)
{
  //## begin cS7Operator::SetValue%1084360932.body preserve=yes
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
  //## end cS7Operator::SetValue%1084360932.body
}

void cS7Operator::SetValue (UCHAR_T data_type, CHAR_T value)
{
  //## begin cS7Operator::SetValue%1084360933.body preserve=yes
   SetValue(data_type, (UCHAR_T)value);
  //## end cS7Operator::SetValue%1084360933.body
}

void cS7Operator::SetValue (UCHAR_T data_type, SHORT_T value)
{
  //## begin cS7Operator::SetValue%1084360934.body preserve=yes
   SetValue(data_type, (USHORT_T)value);
  //## end cS7Operator::SetValue%1084360934.body
}

void cS7Operator::SetValue (UCHAR_T data_type, LONG_T value)
{
  //## begin cS7Operator::SetValue%1084360935.body preserve=yes
   SetValue(data_type, (ULONG_T)value);
  //## end cS7Operator::SetValue%1084360935.body
}

void cS7Operator::SetValue (UCHAR_T data_type, FLOAT_T value)
{
  //## begin cS7Operator::SetValue%1110194497.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_FLOAT:
         _FLOAT_Value = byte_to_float(value);
         break;
      case SH_DOUBLE:
         _DOUBLE_Value = byte_to_float(value);
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
  //## end cS7Operator::SetValue%1110194497.body
}

void cS7Operator::SetValue (UCHAR_T data_type, DOUBLE_T value)
{
  //## begin cS7Operator::SetValue%1110194498.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_FLOAT:
         _FLOAT_Value = (FLOAT_T)byte_to_double(value);
         break;
      case SH_DOUBLE:
         _DOUBLE_Value = byte_to_double(value);
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
  //## end cS7Operator::SetValue%1110194498.body
}

cS7Operator::operator UCHAR_T ()
{
  //## begin cS7Operator::operator UCHAR_T%1084360936.body preserve=yes
   return _CHAR_Value;
  //## end cS7Operator::operator UCHAR_T%1084360936.body
}

cS7Operator::operator USHORT_T ()
{
  //## begin cS7Operator::operator USHORT_T%1084360937.body preserve=yes
   return _SHORT_Value;
  //## end cS7Operator::operator USHORT_T%1084360937.body
}

cS7Operator::operator ULONG_T ()
{
  //## begin cS7Operator::operator ULONG_T%1084360938.body preserve=yes
   return _LONG_Value;
  //## end cS7Operator::operator ULONG_T%1084360938.body
}

cS7Operator::operator CHAR_T ()
{
  //## begin cS7Operator::operator CHAR_T%1084360939.body preserve=yes
   return _CHAR_Value;
  //## end cS7Operator::operator CHAR_T%1084360939.body
}

cS7Operator::operator SHORT_T ()
{
  //## begin cS7Operator::operator SHORT_T%1084360940.body preserve=yes
   return _SHORT_Value;
  //## end cS7Operator::operator SHORT_T%1084360940.body
}

cS7Operator::operator LONG_T ()
{
  //## begin cS7Operator::operator LONG_T%1084360941.body preserve=yes
   return _LONG_Value;
  //## end cS7Operator::operator LONG_T%1084360941.body
}

cS7Operator::operator FLOAT_T ()
{
  //## begin cS7Operator::operator FLOAT_T%1110194507.body preserve=yes
   return _FLOAT_Value;
  //## end cS7Operator::operator FLOAT_T%1110194507.body
}

cS7Operator::operator DOUBLE_T ()
{
  //## begin cS7Operator::operator DOUBLE_T%1110194508.body preserve=yes
   return _DOUBLE_Value;
  //## end cS7Operator::operator DOUBLE_T%1110194508.body
}

void cS7Operator::SetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cS7Operator::SetBit%1084360942.body preserve=yes
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
  //## end cS7Operator::SetBit%1084360942.body
}

void cS7Operator::ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cS7Operator::ResetBit%1084360943.body preserve=yes
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
  //## end cS7Operator::ResetBit%1084360943.body
}

UCHAR_T cS7Operator::GetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cS7Operator::GetBit%1084360965.body preserve=yes
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
  //## end cS7Operator::GetBit%1084360965.body
}

void cS7Operator::SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cS7Operator::SetPattern%1084360944.body preserve=yes
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
  //## end cS7Operator::SetPattern%1084360944.body
}

ULONG_T cS7Operator::GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cS7Operator::GetPattern%1084360945.body preserve=yes
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
  //## end cS7Operator::GetPattern%1084360945.body
}

UCHAR_T cS7Operator::BytePos (UCHAR_T data_type, UCHAR_T bit_pos)
{
  //## begin cS7Operator::BytePos%1084360946.body preserve=yes
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
  //## end cS7Operator::BytePos%1084360946.body
}

// Additional Declarations
  //## begin cS7Operator%40A20C7702AF.declarations preserve=yes
  //## end cS7Operator%40A20C7702AF.declarations

//## begin module%40A20C7702AF.epilog preserve=yes
//## end module%40A20C7702AF.epilog
