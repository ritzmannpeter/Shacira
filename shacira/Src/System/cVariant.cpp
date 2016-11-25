//## begin module%3F4A3223032C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4A3223032C.cm

//## begin module%3F4A3223032C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F4A3223032C.cp

//## Module: cVariant%3F4A3223032C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cVariant.cpp

//## begin module%3F4A3223032C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F4A3223032C.additionalIncludes

//## begin module%3F4A3223032C.includes preserve=yes
//## end module%3F4A3223032C.includes

// cVariant
#include "System/cVariant.h"
//## begin module%3F4A3223032C.additionalDeclarations preserve=yes

#define SET_LVAL(value,type_code) \
switch (_DataType) { \
   case SH_VOID: break; \
   case SH_CHAR: \
   case SH_UCHAR: \
   case SH_SHORT: \
   case SH_USHORT: \
   case SH_LONG: \
   case SH_ULONG: \
      _LVal = (LONG_T)value; \
      return; \
   case SH_FLOAT: \
   case SH_DOUBLE: \
      _DVal = (DOUBLE_T)value; \
      return; \
   case SH_STRING: \
      break; \
   case SH_WSTRING: \
      break; \
   case SH_BYTE: break; \
      break; \
   } \
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(type_code).c_str(), TypeName(_DataType).c_str());

#define RETURN_LVAL(type,type_code) \
   switch (_DataType) { \
   case SH_VOID: break; \
   case SH_CHAR: \
   case SH_UCHAR: \
   case SH_SHORT: \
   case SH_USHORT: \
   case SH_LONG: \
   case SH_ULONG: \
      return (type)_LVal; \
   case SH_FLOAT: \
   case SH_DOUBLE: \
      return (type)_DVal; \
   case SH_STRING: \
      break; \
   case SH_WSTRING: \
      break; \
   case SH_BYTE: break; \
      break; \
   } \
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(type_code).c_str(), TypeName(_DataType).c_str());

//## end module%3F4A3223032C.additionalDeclarations


// Class cVariant 




cVariant::cVariant()
  //## begin cVariant::cVariant%.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%.hasinit
  //## begin cVariant::cVariant%.initialization preserve=yes
  //## end cVariant::cVariant%.initialization
{
  //## begin cVariant::cVariant%.body preserve=yes
  //## end cVariant::cVariant%.body
}

cVariant::cVariant(const cVariant &right)
  //## begin cVariant::cVariant%copy.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%copy.hasinit
  //## begin cVariant::cVariant%copy.initialization preserve=yes
  //## end cVariant::cVariant%copy.initialization
{
  //## begin cVariant::cVariant%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cVariant::cVariant%copy.body
}

cVariant::cVariant (CHAR_T value)
  //## begin cVariant::cVariant%1061986944.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986944.hasinit
  //## begin cVariant::cVariant%1061986944.initialization preserve=yes
  //## end cVariant::cVariant%1061986944.initialization
{
  //## begin cVariant::cVariant%1061986944.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_CHAR;
   SET_LVAL(value, SH_CHAR)
  //## end cVariant::cVariant%1061986944.body
}

cVariant::cVariant (UCHAR_T value)
  //## begin cVariant::cVariant%1061986945.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986945.hasinit
  //## begin cVariant::cVariant%1061986945.initialization preserve=yes
  //## end cVariant::cVariant%1061986945.initialization
{
  //## begin cVariant::cVariant%1061986945.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_UCHAR;
   SET_LVAL(value, SH_UCHAR)
  //## end cVariant::cVariant%1061986945.body
}

cVariant::cVariant (SHORT_T value)
  //## begin cVariant::cVariant%1061986946.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986946.hasinit
  //## begin cVariant::cVariant%1061986946.initialization preserve=yes
  //## end cVariant::cVariant%1061986946.initialization
{
  //## begin cVariant::cVariant%1061986946.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_SHORT;
   SET_LVAL(value, SH_SHORT)
  //## end cVariant::cVariant%1061986946.body
}

cVariant::cVariant (USHORT_T value)
  //## begin cVariant::cVariant%1061986947.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986947.hasinit
  //## begin cVariant::cVariant%1061986947.initialization preserve=yes
  //## end cVariant::cVariant%1061986947.initialization
{
  //## begin cVariant::cVariant%1061986947.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_SHORT;
   SET_LVAL(value, SH_USHORT)
  //## end cVariant::cVariant%1061986947.body
}

cVariant::cVariant (LONG_T value)
  //## begin cVariant::cVariant%1061824381.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061824381.hasinit
  //## begin cVariant::cVariant%1061824381.initialization preserve=yes
  //## end cVariant::cVariant%1061824381.initialization
{
  //## begin cVariant::cVariant%1061824381.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_LONG;
   SET_LVAL(value, SH_LONG)
  //## end cVariant::cVariant%1061824381.body
}

cVariant::cVariant (ULONG_T value)
  //## begin cVariant::cVariant%1061986948.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986948.hasinit
  //## begin cVariant::cVariant%1061986948.initialization preserve=yes
  //## end cVariant::cVariant%1061986948.initialization
{
  //## begin cVariant::cVariant%1061986948.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_ULONG;
   SET_LVAL(value, SH_ULONG)
  //## end cVariant::cVariant%1061986948.body
}

cVariant::cVariant (FLOAT_T value)
  //## begin cVariant::cVariant%1061829456.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061829456.hasinit
  //## begin cVariant::cVariant%1061829456.initialization preserve=yes
  //## end cVariant::cVariant%1061829456.initialization
{
  //## begin cVariant::cVariant%1061829456.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_FLOAT;
   SET_LVAL(value, SH_FLOAT)
  //## end cVariant::cVariant%1061829456.body
}

cVariant::cVariant (DOUBLE_T value)
  //## begin cVariant::cVariant%1061829457.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061829457.hasinit
  //## begin cVariant::cVariant%1061829457.initialization preserve=yes
  //## end cVariant::cVariant%1061829457.initialization
{
  //## begin cVariant::cVariant%1061829457.body preserve=yes
   if (_DataType == UNDEFINED) _DataType = SH_DOUBLE;
   SET_LVAL(value, SH_DOUBLE)
  //## end cVariant::cVariant%1061829457.body
}

cVariant::cVariant (STRING_T value)
  //## begin cVariant::cVariant%1061986955.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986955.hasinit
  //## begin cVariant::cVariant%1061986955.initialization preserve=yes
  //## end cVariant::cVariant%1061986955.initialization
{
  //## begin cVariant::cVariant%1061986955.body preserve=yes
  //## end cVariant::cVariant%1061986955.body
}

cVariant::cVariant (WSTRING_T value)
  //## begin cVariant::cVariant%1061986956.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986956.hasinit
  //## begin cVariant::cVariant%1061986956.initialization preserve=yes
  //## end cVariant::cVariant%1061986956.initialization
{
  //## begin cVariant::cVariant%1061986956.body preserve=yes
  //## end cVariant::cVariant%1061986956.body
}

cVariant::cVariant (CONST_WSTRING_T value)
  //## begin cVariant::cVariant%1061986957.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986957.hasinit
  //## begin cVariant::cVariant%1061986957.initialization preserve=yes
  //## end cVariant::cVariant%1061986957.initialization
{
  //## begin cVariant::cVariant%1061986957.body preserve=yes
  //## end cVariant::cVariant%1061986957.body
}

cVariant::cVariant (CONST_STRING_T value)
  //## begin cVariant::cVariant%1061986958.hasinit preserve=no
      : _DataType(UNDEFINED), _LVal(0), _DVal(0)
  //## end cVariant::cVariant%1061986958.hasinit
  //## begin cVariant::cVariant%1061986958.initialization preserve=yes
  //## end cVariant::cVariant%1061986958.initialization
{
  //## begin cVariant::cVariant%1061986958.body preserve=yes
  //## end cVariant::cVariant%1061986958.body
}


cVariant::~cVariant()
{
  //## begin cVariant::~cVariant%.body preserve=yes
  //## end cVariant::~cVariant%.body
}



//## Other Operations (implementation)
UCHAR_T cVariant::DataType ()
{
  //## begin cVariant::DataType%1061829452.body preserve=yes
   return _DataType;
  //## end cVariant::DataType%1061829452.body
}

void cVariant::DataType (UCHAR_T data_type)
{
  //## begin cVariant::DataType%1061829454.body preserve=yes
   _DataType = data_type;
  //## end cVariant::DataType%1061829454.body
}

cVariant::operator CHAR_T ()
{
  //## begin cVariant::operator CHAR_T%1061986949.body preserve=yes
   RETURN_LVAL(CHAR_T, SH_CHAR)
  //## end cVariant::operator CHAR_T%1061986949.body
}

cVariant::operator UCHAR_T ()
{
  //## begin cVariant::operator UCHAR_T%1061986950.body preserve=yes
   RETURN_LVAL(UCHAR_T, SH_UCHAR)
  //## end cVariant::operator UCHAR_T%1061986950.body
}

cVariant::operator SHORT_T ()
{
  //## begin cVariant::operator SHORT_T%1061986951.body preserve=yes
   RETURN_LVAL(SHORT_T, SH_SHORT)
  //## end cVariant::operator SHORT_T%1061986951.body
}

cVariant::operator USHORT_T ()
{
  //## begin cVariant::operator USHORT_T%1061986952.body preserve=yes
   RETURN_LVAL(USHORT_T, SH_USHORT)
  //## end cVariant::operator USHORT_T%1061986952.body
}

cVariant::operator LONG_T ()
{
  //## begin cVariant::operator LONG_T%1061829453.body preserve=yes
   RETURN_LVAL(LONG_T, SH_LONG)
  //## end cVariant::operator LONG_T%1061829453.body
}

cVariant::operator ULONG_T ()
{
  //## begin cVariant::operator ULONG_T%1061986953.body preserve=yes
   RETURN_LVAL(ULONG_T, SH_ULONG)
  //## end cVariant::operator ULONG_T%1061986953.body
}

cVariant::operator FLOAT_T ()
{
  //## begin cVariant::operator FLOAT_T%1061829458.body preserve=yes
   RETURN_LVAL(FLOAT_T, SH_FLOAT)
  //## end cVariant::operator FLOAT_T%1061829458.body
}

cVariant::operator DOUBLE_T ()
{
  //## begin cVariant::operator DOUBLE_T%1061986954.body preserve=yes
   RETURN_LVAL(DOUBLE_T, SH_DOUBLE)
  //## end cVariant::operator DOUBLE_T%1061986954.body
}

cVariant::operator STRING_T ()
{
  //## begin cVariant::operator STRING_T%1061986959.body preserve=yes
   return "?";
  //## end cVariant::operator STRING_T%1061986959.body
}

cVariant::operator WSTRING_T ()
{
  //## begin cVariant::operator WSTRING_T%1061986960.body preserve=yes
   return (WCHAR_T*)"??";
  //## end cVariant::operator WSTRING_T%1061986960.body
}

cVariant::operator CONST_WSTRING_T ()
{
  //## begin cVariant::operator CONST_WSTRING_T%1061986961.body preserve=yes
   return (WCHAR_T*)"??";
  //## end cVariant::operator CONST_WSTRING_T%1061986961.body
}

cVariant::operator CONST_STRING_T ()
{
  //## begin cVariant::operator CONST_STRING_T%1061986962.body preserve=yes
   return "?";
  //## end cVariant::operator CONST_STRING_T%1061986962.body
}

STRING_T cVariant::TypeName (UCHAR_T data_type)
{
  //## begin cVariant::TypeName%1061829455.body preserve=yes
   switch (data_type) {
   case UNDEFINED: return "undefined";
   case SH_VOID: return "void";
   case SH_CHAR: return "char";
   case SH_UCHAR: return "unsigned char";
   case SH_SHORT: return "short";
   case SH_USHORT: return "unsigned short";
   case SH_LONG: return "long";
   case SH_ULONG: return "unsigned long";
   case SH_BIT_8: return "unsigned char";
   case SH_BIT_16: return "unsigned short";
   case SH_BIT_32: return "unsigned long";
   case SH_FLOAT: return "float";
   case SH_DOUBLE: return "double";
   case SH_STRING: return "string";
   case SH_WSTRING: return "wstring";
   case SH_BYTE: return "byte";
   case SH_OBJECT: return "object";
   }
   return "unknown";
  //## end cVariant::TypeName%1061829455.body
}

ULONG_T cVariant::TypeSize (UCHAR_T data_type)
{
  //## begin cVariant::TypeSize%1061986963.body preserve=yes
return 0;
  //## end cVariant::TypeSize%1061986963.body
}

ULONG_T cVariant::StrLen (CONST_STRING_T str)
{
  //## begin cVariant::StrLen%1061986964.body preserve=yes
return 0;
  //## end cVariant::StrLen%1061986964.body
}

ULONG_T cVariant::StrLen (CONST_WSTRING_T str)
{
  //## begin cVariant::StrLen%1061986965.body preserve=yes
return 0;
  //## end cVariant::StrLen%1061986965.body
}

INT_T cVariant::StrCmp (CONST_STRING_T str1, CONST_STRING_T str2)
{
  //## begin cVariant::StrCmp%1061986966.body preserve=yes
return 0;
  //## end cVariant::StrCmp%1061986966.body
}

INT_T cVariant::StrCmp (CONST_WSTRING_T str1, CONST_WSTRING_T str2)
{
  //## begin cVariant::StrCmp%1061986967.body preserve=yes
return 0;
  //## end cVariant::StrCmp%1061986967.body
}

ULONG_T cVariant::MemSize (CONST_STRING_T str)
{
  //## begin cVariant::MemSize%1061986968.body preserve=yes
return 0;
  //## end cVariant::MemSize%1061986968.body
}

ULONG_T cVariant::MemSize (CONST_WSTRING_T str)
{
  //## begin cVariant::MemSize%1061986969.body preserve=yes
return 0;
  //## end cVariant::MemSize%1061986969.body
}

WSTRING_T cVariant::String2Wide (CONST_STRING_T str)
{
  //## begin cVariant::String2Wide%1061986970.body preserve=yes
return 0;
  //## end cVariant::String2Wide%1061986970.body
}

STRING_T cVariant::Wide2String (CONST_WSTRING_T str)
{
  //## begin cVariant::Wide2String%1061986971.body preserve=yes
return "";
  //## end cVariant::Wide2String%1061986971.body
}

DOUBLE_T cVariant::Real2Double (CONST_STRING_T str)
{
  //## begin cVariant::Real2Double%1061986972.body preserve=yes
return 0;
  //## end cVariant::Real2Double%1061986972.body
}

DOUBLE_T cVariant::Real2Double (CONST_WSTRING_T str)
{
  //## begin cVariant::Real2Double%1061986973.body preserve=yes
return 0;
  //## end cVariant::Real2Double%1061986973.body
}

FLOAT_T cVariant::Real2Float (CONST_STRING_T str)
{
  //## begin cVariant::Real2Float%1061986974.body preserve=yes
return 0;
  //## end cVariant::Real2Float%1061986974.body
}

FLOAT_T cVariant::Real2Float (CONST_WSTRING_T str)
{
  //## begin cVariant::Real2Float%1061986975.body preserve=yes
return 0;
  //## end cVariant::Real2Float%1061986975.body
}

LONG_T cVariant::Dec2Long (CONST_STRING_T str)
{
  //## begin cVariant::Dec2Long%1061986976.body preserve=yes
return 0;
  //## end cVariant::Dec2Long%1061986976.body
}

LONG_T cVariant::Dec2Long (CONST_WSTRING_T str)
{
  //## begin cVariant::Dec2Long%1061986977.body preserve=yes
return 0;
  //## end cVariant::Dec2Long%1061986977.body
}

void cVariant::Long2String (STRING_T &str, LONG_T value, UCHAR_T radix)
{
  //## begin cVariant::Long2String%1061986978.body preserve=yes
  //## end cVariant::Long2String%1061986978.body
}

void cVariant::Long2String (WSTRING_T &str, LONG_T value, UCHAR_T radix)
{
  //## begin cVariant::Long2String%1061986979.body preserve=yes
  //## end cVariant::Long2String%1061986979.body
}

void cVariant::Float2String (STRING_T &str, FLOAT_T value, UCHAR_T precision)
{
  //## begin cVariant::Float2String%1061986980.body preserve=yes
  //## end cVariant::Float2String%1061986980.body
}

void cVariant::Float2String (WSTRING_T &str, FLOAT_T value, UCHAR_T precision)
{
  //## begin cVariant::Float2String%1061986981.body preserve=yes
  //## end cVariant::Float2String%1061986981.body
}

void cVariant::Double2String (STRING_T &str, DOUBLE_T value, UCHAR_T precision)
{
  //## begin cVariant::Double2String%1061986982.body preserve=yes
  //## end cVariant::Double2String%1061986982.body
}

void cVariant::Double2String (WSTRING_T &str, DOUBLE_T value, UCHAR_T precision)
{
  //## begin cVariant::Double2String%1061986983.body preserve=yes
  //## end cVariant::Double2String%1061986983.body
}

// Additional Declarations
  //## begin cVariant%3F4A3223032C.declarations preserve=yes
  //## end cVariant%3F4A3223032C.declarations

//## begin module%3F4A3223032C.epilog preserve=yes
//## end module%3F4A3223032C.epilog
