//## begin module%40A20CD9032C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A20CD9032C.cm

//## begin module%40A20CD9032C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40A20CD9032C.cp

//## Module: cPPCOperator%40A20CD9032C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCOperator.cpp

//## begin module%40A20CD9032C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%40A20CD9032C.additionalIncludes

//## begin module%40A20CD9032C.includes preserve=yes
//## end module%40A20CD9032C.includes

// cPPCOperator
#include "Control/Device/PPCCom/cPPCOperator.h"
//## begin module%40A20CD9032C.additionalDeclarations preserve=yes

#define GET_PPC_BIT(w_val,pos)   (w_val & (0x8000 >> (pos)))
#define SET_PPC_BIT(w_val,pos)   (w_val | (0x8000 >> (pos)))
#define RESET_PPC_BIT(w_val,pos)   ((w_val) & ~(0x8000 >> (pos)))

//## end module%40A20CD9032C.additionalDeclarations


// Class cPPCOperator 

cPPCOperator::cPPCOperator()
  //## begin cPPCOperator::cPPCOperator%.hasinit preserve=no
  //## end cPPCOperator::cPPCOperator%.hasinit
  //## begin cPPCOperator::cPPCOperator%.initialization preserve=yes
  : cBitOperator(2)
  //## end cPPCOperator::cPPCOperator%.initialization
{
  //## begin cPPCOperator::cPPCOperator%.body preserve=yes
  //## end cPPCOperator::cPPCOperator%.body
}

cPPCOperator::cPPCOperator(const cPPCOperator &right)
  //## begin cPPCOperator::cPPCOperator%copy.hasinit preserve=no
  //## end cPPCOperator::cPPCOperator%copy.hasinit
  //## begin cPPCOperator::cPPCOperator%copy.initialization preserve=yes
  //## end cPPCOperator::cPPCOperator%copy.initialization
{
  //## begin cPPCOperator::cPPCOperator%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPPCOperator::cPPCOperator%copy.body
}


cPPCOperator::~cPPCOperator()
{
  //## begin cPPCOperator::~cPPCOperator%.body preserve=yes
  //## end cPPCOperator::~cPPCOperator%.body
}



//## Other Operations (implementation)
void cPPCOperator::SetValue (UCHAR_T data_type, UCHAR_T value)
{
  //## begin cPPCOperator::SetValue%1084360948.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 2) {
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
  //## end cPPCOperator::SetValue%1084360948.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, USHORT_T value)
{
  //## begin cPPCOperator::SetValue%1084360949.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 2) {
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
  //## end cPPCOperator::SetValue%1084360949.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, ULONG_T value)
{
  //## begin cPPCOperator::SetValue%1084360950.body preserve=yes
   _DataType = data_type;
   if (_Granularity == 1) {
      throw cError(DEVICE_INVALID_GRANULARITY, 0, 
                   cConvUtils::StringValue(_Granularity).c_str());
   } else if (_Granularity == 2) {
      switch (_DataType) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_BIT_8:
         _CHAR_Value = (UCHAR_T)value;
         break;
      case SH_SHORT:
      case SH_USHORT:
      case SH_BIT_16:
         _SHORT_Value = (USHORT_T)value;
         break;
      case SH_LONG:
      case SH_ULONG:
      case SH_BIT_32:
//         _LONG_Value = word_to_long(value);
// PR 17.05.40
         _LONG_Value = value;
         break;
      default:
         throw cError(DEVICE_INVALID_DATATYPE, 0, 
                     cConvUtils::StringValue(_DataType).c_str());
      }
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
  //## end cPPCOperator::SetValue%1084360950.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, CHAR_T value)
{
  //## begin cPPCOperator::SetValue%1084360951.body preserve=yes
   SetValue(data_type, (UCHAR_T)value);
  //## end cPPCOperator::SetValue%1084360951.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, SHORT_T value)
{
  //## begin cPPCOperator::SetValue%1084360952.body preserve=yes
   SetValue(data_type, (USHORT_T)value);
  //## end cPPCOperator::SetValue%1084360952.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, LONG_T value)
{
  //## begin cPPCOperator::SetValue%1084360953.body preserve=yes
   SetValue(data_type, (ULONG_T)value);
  //## end cPPCOperator::SetValue%1084360953.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, FLOAT_T value)
{
  //## begin cPPCOperator::SetValue%1110194503.body preserve=yes
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
  //## end cPPCOperator::SetValue%1110194503.body
}

void cPPCOperator::SetValue (UCHAR_T data_type, DOUBLE_T value)
{
  //## begin cPPCOperator::SetValue%1110194504.body preserve=yes
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
  //## end cPPCOperator::SetValue%1110194504.body
}

cPPCOperator::operator UCHAR_T ()
{
  //## begin cPPCOperator::operator UCHAR_T%1084360954.body preserve=yes
   return _CHAR_Value;
  //## end cPPCOperator::operator UCHAR_T%1084360954.body
}

cPPCOperator::operator USHORT_T ()
{
  //## begin cPPCOperator::operator USHORT_T%1084360955.body preserve=yes
   return _SHORT_Value;
  //## end cPPCOperator::operator USHORT_T%1084360955.body
}

cPPCOperator::operator ULONG_T ()
{
  //## begin cPPCOperator::operator ULONG_T%1084360956.body preserve=yes
   return _LONG_Value;
  //## end cPPCOperator::operator ULONG_T%1084360956.body
}

cPPCOperator::operator CHAR_T ()
{
  //## begin cPPCOperator::operator CHAR_T%1084360957.body preserve=yes
   return _CHAR_Value;
  //## end cPPCOperator::operator CHAR_T%1084360957.body
}

cPPCOperator::operator SHORT_T ()
{
  //## begin cPPCOperator::operator SHORT_T%1084360958.body preserve=yes
   return _SHORT_Value;
  //## end cPPCOperator::operator SHORT_T%1084360958.body
}

cPPCOperator::operator LONG_T ()
{
  //## begin cPPCOperator::operator LONG_T%1084360959.body preserve=yes
   return _LONG_Value;
  //## end cPPCOperator::operator LONG_T%1084360959.body
}

cPPCOperator::operator FLOAT_T ()
{
  //## begin cPPCOperator::operator FLOAT_T%1110194509.body preserve=yes
   return _FLOAT_Value;
  //## end cPPCOperator::operator FLOAT_T%1110194509.body
}

cPPCOperator::operator DOUBLE_T ()
{
  //## begin cPPCOperator::operator DOUBLE_T%1110194510.body preserve=yes
   return _DOUBLE_Value;
  //## end cPPCOperator::operator DOUBLE_T%1110194510.body
}

void cPPCOperator::SetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cPPCOperator::SetBit%1084360960.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = SET_BIT_B(_CHAR_Value, pos);
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      if (buf_spec != NULL &&
          strcmp(buf_spec, "register") == 0) {
         _SHORT_Value = SET_BIT_W(_SHORT_Value, pos);
      } else {
         _SHORT_Value = SET_PPC_BIT(_SHORT_Value, pos);
      }
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
  //## end cPPCOperator::SetBit%1084360960.body
}

void cPPCOperator::ResetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cPPCOperator::ResetBit%1084360961.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      _CHAR_Value = RESET_BIT_B(_CHAR_Value, pos);
      break;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      if (buf_spec != NULL &&
          strcmp(buf_spec, "register") == 0) {
         _SHORT_Value = RESET_BIT_W(_SHORT_Value, pos);
      } else {
         _SHORT_Value = RESET_PPC_BIT(_SHORT_Value, pos);
      }
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
  //## end cPPCOperator::ResetBit%1084360961.body
}

UCHAR_T cPPCOperator::GetBit (UCHAR_T pos, CONST_STRING_T buf_spec)
{
  //## begin cPPCOperator::GetBit%1084360967.body preserve=yes
   switch (_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      return GET_BIT_B(_CHAR_Value, pos) > 0;
   case SH_SHORT:
   case SH_USHORT:
   case SH_BIT_16:
      if (buf_spec != NULL &&
          strcmp(buf_spec, "register") == 0) {
         return GET_BIT_W(_SHORT_Value, pos) > 0;
      } else {
         return GET_PPC_BIT(_SHORT_Value, pos) > 0;
      }
      break;
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_32:
      return GET_BIT_DW(_LONG_Value, pos) > 0;
   default:
      throw cError(DEVICE_INVALID_DATATYPE, 0, 
                   cConvUtils::StringValue(_DataType).c_str());
   }
  //## end cPPCOperator::GetBit%1084360967.body
}

void cPPCOperator::SetPattern (ULONG_T pattern, UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cPPCOperator::SetPattern%1084360962.body preserve=yes
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
      if (buf_spec != NULL &&
          strcmp(buf_spec, "register") == 0) {
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
      } else {
         shift = 16 - length;
         pattern = (pattern << shift) >> shift;
         for (i=0; i<length; i++) {
            set = ((UCHAR_T)pattern & 1);
            if (set) {
               _SHORT_Value = SET_PPC_BIT(_SHORT_Value, pos+i);
            } else {
               _SHORT_Value = RESET_PPC_BIT(_SHORT_Value, pos+i);
            }
            pattern = pattern >> 1;
         }
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
  //## end cPPCOperator::SetPattern%1084360962.body
}

ULONG_T cPPCOperator::GetPattern (UCHAR_T pos, UCHAR_T length, CONST_STRING_T buf_spec)
{
  //## begin cPPCOperator::GetPattern%1084360963.body preserve=yes
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
  //## end cPPCOperator::GetPattern%1084360963.body
}

UCHAR_T cPPCOperator::BytePos (UCHAR_T data_type, UCHAR_T bit_pos)
{
  //## begin cPPCOperator::BytePos%1084360964.body preserve=yes
   // PR 31.01.05 actually this method is not clearly defined
   // added temporary workarouns in advance to clearly define
   // this method.
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_BIT_8:
      return 0;
   case SH_SHORT:
   case SH_USHORT:
      // this is not as intended
      return 0;
      if (bit_pos < 8) {
         return 1;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 0;
      }
   case SH_BIT_16:
      // this is not as intended
      return 0;
      if (bit_pos < 8) {
         return 0;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 1;
      }
   case SH_LONG:
   case SH_ULONG:
      // this is not as intended
      return 0;
      if (bit_pos < 16) {
         return 0;
      } else {
         return 1;         
      }
      if (bit_pos < 8) {
         return 3;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 2;         
      } else if (bit_pos > 15 && bit_pos < 24) {
         return 1;         
      } else if (bit_pos > 23 && bit_pos < 32) {
         return 0;         
      }
   case SH_BIT_32:
      // this is not as intended
      return 0;
      if (bit_pos < 16) {
         return 0;
      } else {
         return 1;         
      }
/* dead code !?
      if (bit_pos < 8) {
         return 0;
      } else if (bit_pos > 7 && bit_pos < 16) {
         return 1;         
      } else if (bit_pos > 15 && bit_pos < 24) {
         return 2;         
      } else if (bit_pos > 23 && bit_pos < 32) {
         return 3;         
      }
*/
   }
   return 0;
  //## end cPPCOperator::BytePos%1084360964.body
}

// Additional Declarations
  //## begin cPPCOperator%40A20CD9032C.declarations preserve=yes
  //## end cPPCOperator%40A20CD9032C.declarations

//## begin module%40A20CD9032C.epilog preserve=yes
//## end module%40A20CD9032C.epilog
