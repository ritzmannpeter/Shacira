//## begin module%41DBCB6503B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41DBCB6503B9.cm

//## begin module%41DBCB6503B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41DBCB6503B9.cp

//## Module: cNullOperator%41DBCB6503B9; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cNullOperator.cpp

//## begin module%41DBCB6503B9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41DBCB6503B9.additionalIncludes

//## begin module%41DBCB6503B9.includes preserve=yes
//## end module%41DBCB6503B9.includes

// cNullOperator
#include "Control/Device/cNullOperator.h"
//## begin module%41DBCB6503B9.additionalDeclarations preserve=yes
//## end module%41DBCB6503B9.additionalDeclarations


// Class cNullOperator 

cNullOperator::cNullOperator()
  //## begin cNullOperator::cNullOperator%.hasinit preserve=no
  //## end cNullOperator::cNullOperator%.hasinit
  //## begin cNullOperator::cNullOperator%.initialization preserve=yes
  : cBitOperator(1)
  //## end cNullOperator::cNullOperator%.initialization
{
  //## begin cNullOperator::cNullOperator%.body preserve=yes
  //## end cNullOperator::cNullOperator%.body
}

cNullOperator::cNullOperator(const cNullOperator &right)
  //## begin cNullOperator::cNullOperator%copy.hasinit preserve=no
  //## end cNullOperator::cNullOperator%copy.hasinit
  //## begin cNullOperator::cNullOperator%copy.initialization preserve=yes
  //## end cNullOperator::cNullOperator%copy.initialization
{
  //## begin cNullOperator::cNullOperator%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cNullOperator::cNullOperator%copy.body
}


cNullOperator::~cNullOperator()
{
  //## begin cNullOperator::~cNullOperator%.body preserve=yes
  //## end cNullOperator::~cNullOperator%.body
}



//## Other Operations (implementation)
void cNullOperator::SetValue (UCHAR_T data_type, UCHAR_T value)
{
  //## begin cNullOperator::SetValue%1104923575.body preserve=yes
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
         _SHORT_Value = value;
         break;
      case SH_BIT_16:
         _SHORT_Value = value;
         break;
      case SH_LONG:
      case SH_ULONG:
         _LONG_Value = value;
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
  //## end cNullOperator::SetValue%1104923575.body
}

void cNullOperator::SetValue (UCHAR_T data_type, USHORT_T value)
{
  //## begin cNullOperator::SetValue%1104923576.body preserve=yes
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
         _SHORT_Value = value;
         break;
      case SH_BIT_16:
         _SHORT_Value = value;
         break;
      case SH_LONG:
      case SH_ULONG:
         _LONG_Value = value;
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
  //## end cNullOperator::SetValue%1104923576.body
}

void cNullOperator::SetValue (UCHAR_T data_type, ULONG_T value)
{
  //## begin cNullOperator::SetValue%1104923577.body preserve=yes
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
         _SHORT_Value = (USHORT_T)value;
         break;
      case SH_BIT_16:
         _SHORT_Value = (USHORT_T)value;
         break;
      case SH_LONG:
      case SH_ULONG:
         _LONG_Value = value;
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
  //## end cNullOperator::SetValue%1104923577.body
}

void cNullOperator::SetValue (UCHAR_T data_type, CHAR_T value)
{
  //## begin cNullOperator::SetValue%1104923578.body preserve=yes
   SetValue(data_type, (UCHAR_T)value);
  //## end cNullOperator::SetValue%1104923578.body
}

void cNullOperator::SetValue (UCHAR_T data_type, SHORT_T value)
{
  //## begin cNullOperator::SetValue%1104923579.body preserve=yes
   SetValue(data_type, (USHORT_T)value);
  //## end cNullOperator::SetValue%1104923579.body
}

void cNullOperator::SetValue (UCHAR_T data_type, LONG_T value)
{
  //## begin cNullOperator::SetValue%1104923580.body preserve=yes
   SetValue(data_type, (ULONG_T)value);
  //## end cNullOperator::SetValue%1104923580.body
}

void cNullOperator::SetValue (UCHAR_T data_type, FLOAT_T value)
{
  //## begin cNullOperator::SetValue%1110194495.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_FLOAT:
         _FLOAT_Value = value;
         break;
      case SH_DOUBLE:
         _DOUBLE_Value = value;
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
  //## end cNullOperator::SetValue%1110194495.body
}

void cNullOperator::SetValue (UCHAR_T data_type, DOUBLE_T value)
{
  //## begin cNullOperator::SetValue%1110194496.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      switch (_DataType) {
      case SH_FLOAT:
         _FLOAT_Value = (FLOAT_T)value;
         break;
      case SH_DOUBLE:
         _DOUBLE_Value = value;
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
  //## end cNullOperator::SetValue%1110194496.body
}

cNullOperator::operator UCHAR_T ()
{
  //## begin cNullOperator::operator UCHAR_T%1104923581.body preserve=yes
   return _CHAR_Value;
  //## end cNullOperator::operator UCHAR_T%1104923581.body
}

cNullOperator::operator USHORT_T ()
{
  //## begin cNullOperator::operator USHORT_T%1104923582.body preserve=yes
   return _SHORT_Value;
  //## end cNullOperator::operator USHORT_T%1104923582.body
}

cNullOperator::operator ULONG_T ()
{
  //## begin cNullOperator::operator ULONG_T%1104923583.body preserve=yes
   return _LONG_Value;
  //## end cNullOperator::operator ULONG_T%1104923583.body
}

cNullOperator::operator CHAR_T ()
{
  //## begin cNullOperator::operator CHAR_T%1104923584.body preserve=yes
   return _CHAR_Value;
  //## end cNullOperator::operator CHAR_T%1104923584.body
}

cNullOperator::operator SHORT_T ()
{
  //## begin cNullOperator::operator SHORT_T%1104923585.body preserve=yes
   return _SHORT_Value;
  //## end cNullOperator::operator SHORT_T%1104923585.body
}

cNullOperator::operator LONG_T ()
{
  //## begin cNullOperator::operator LONG_T%1104923586.body preserve=yes
   return _LONG_Value;
  //## end cNullOperator::operator LONG_T%1104923586.body
}

cNullOperator::operator FLOAT_T ()
{
  //## begin cNullOperator::operator FLOAT_T%1110194505.body preserve=yes
   return _FLOAT_Value;
  //## end cNullOperator::operator FLOAT_T%1110194505.body
}

cNullOperator::operator DOUBLE_T ()
{
  //## begin cNullOperator::operator DOUBLE_T%1110194506.body preserve=yes
   return _DOUBLE_Value;
  //## end cNullOperator::operator DOUBLE_T%1110194506.body
}

void cNullOperator::SetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cNullOperator::SetBit%1104923587.body preserve=yes
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
  //## end cNullOperator::SetBit%1104923587.body
}

void cNullOperator::ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cNullOperator::ResetBit%1104923588.body preserve=yes
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
  //## end cNullOperator::ResetBit%1104923588.body
}

UCHAR_T cNullOperator::GetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cNullOperator::GetBit%1104923589.body preserve=yes
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
  //## end cNullOperator::GetBit%1104923589.body
}

void cNullOperator::SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cNullOperator::SetPattern%1104923590.body preserve=yes
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
  //## end cNullOperator::SetPattern%1104923590.body
}

ULONG_T cNullOperator::GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cNullOperator::GetPattern%1104923591.body preserve=yes
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
  //## end cNullOperator::GetPattern%1104923591.body
}

UCHAR_T cNullOperator::BytePos (UCHAR_T data_type, UCHAR_T bit_pos)
{
  //## begin cNullOperator::BytePos%1104923592.body preserve=yes
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
  //## end cNullOperator::BytePos%1104923592.body
}

// Additional Declarations
  //## begin cNullOperator%41DBCB6503B9.declarations preserve=yes
  //## end cNullOperator%41DBCB6503B9.declarations

//## begin module%41DBCB6503B9.epilog preserve=yes
//## end module%41DBCB6503B9.epilog
