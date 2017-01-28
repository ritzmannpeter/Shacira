//## begin module%3EF2E1D8008C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EF2E1D8008C.cm

//## begin module%3EF2E1D8008C.cp preserve=no
//	Copyright © 2002 - 2010 by
//	2i Industrial Informatics GmbH
//## end module%3EF2E1D8008C.cp

//## Module: cSHVariant%3EF2E1D8008C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cSHVariant.cpp

//## begin module%3EF2E1D8008C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3EF2E1D8008C.additionalIncludes

//## begin module%3EF2E1D8008C.includes preserve=yes
//## end module%3EF2E1D8008C.includes

// cSHVariant
#include "System/Database/cSHVariant.h"
//## begin module%3EF2E1D8008C.additionalDeclarations preserve=yes

#define MAX_PRECISION      10

#define DOUBLE2LONG(dval,lval) \
{  char sval[0x40] = {0}; \
   SafePrintf(sval, sizeof(sval), "%0.0f", (DOUBLE_T)dval); \
   lval = strtol(sval, NULL, 10); \
}

//## end module%3EF2E1D8008C.additionalDeclarations


// Class cSHVariant 









cSHVariant::cSHVariant()
  //## begin cSHVariant::cSHVariant%.hasinit preserve=no
      : _DataType(UNDEFINED), _LONG_Value(0), _FLOAT_Value(0), _DOUBLE_Value(0), _BUF_Value(NULL)
  //## end cSHVariant::cSHVariant%.hasinit
  //## begin cSHVariant::cSHVariant%.initialization preserve=yes
  //## end cSHVariant::cSHVariant%.initialization
{
  //## begin cSHVariant::cSHVariant%.body preserve=yes
_ASSERT_UNCOND
  //## end cSHVariant::cSHVariant%.body
}

cSHVariant::cSHVariant(const cSHVariant &right)
  //## begin cSHVariant::cSHVariant%copy.hasinit preserve=no
      : _DataType(UNDEFINED), _LONG_Value(0), _FLOAT_Value(0), _DOUBLE_Value(0), _BUF_Value(NULL)
  //## end cSHVariant::cSHVariant%copy.hasinit
  //## begin cSHVariant::cSHVariant%copy.initialization preserve=yes
  //## end cSHVariant::cSHVariant%copy.initialization
{
  //## begin cSHVariant::cSHVariant%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSHVariant::cSHVariant%copy.body
}

cSHVariant::cSHVariant (UCHAR_T data_type)
  //## begin cSHVariant::cSHVariant%1071244309.hasinit preserve=no
      : _DataType(UNDEFINED), _LONG_Value(0), _FLOAT_Value(0), _DOUBLE_Value(0), _BUF_Value(NULL)
  //## end cSHVariant::cSHVariant%1071244309.hasinit
  //## begin cSHVariant::cSHVariant%1071244309.initialization preserve=yes
  //## end cSHVariant::cSHVariant%1071244309.initialization
{
  //## begin cSHVariant::cSHVariant%1071244309.body preserve=yes
   _DataType = data_type;
   switch (_DataType) {
   case UNDEFINED: break;
   case SH_VOID: break;
   case SH_CHAR: break;
   case SH_UCHAR: break;
   case SH_SHORT: break;
   case SH_USHORT: break;
   case SH_LONG: break;
   case SH_ULONG: break;
   case SH_BIT_8: break;
   case SH_BIT_16: break;
   case SH_BIT_32: break;
   case SH_FLOAT: break;
   case SH_DOUBLE: break;
   case SH_STRING: break;
   case SH_WSTRING: break;
   case SH_BYTE: break;
   case SH_OBJECT: break;
   }

  //## end cSHVariant::cSHVariant%1071244309.body
}


cSHVariant::~cSHVariant()
{
  //## begin cSHVariant::~cSHVariant%.body preserve=yes
  //## end cSHVariant::~cSHVariant%.body
}



//## Other Operations (implementation)
void cSHVariant::Get (CHAR_T &value)
{
  //## begin cSHVariant::Get%1071244133.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (CHAR_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = (CHAR_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (CHAR_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = (CHAR_T)Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = (CHAR_T)Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_CHAR).c_str());
  //## end cSHVariant::Get%1071244133.body
}

void cSHVariant::Get (UCHAR_T &value)
{
  //## begin cSHVariant::Get%1071244134.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (UCHAR_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = (UCHAR_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (UCHAR_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = (UCHAR_T)Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = (UCHAR_T)Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_UCHAR).c_str());
  //## end cSHVariant::Get%1071244134.body
}

void cSHVariant::Get (SHORT_T &value)
{
  //## begin cSHVariant::Get%1071244135.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (SHORT_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = (SHORT_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (SHORT_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = (SHORT_T)Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = (SHORT_T)Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_SHORT).c_str());
  //## end cSHVariant::Get%1071244135.body
}

void cSHVariant::Get (USHORT_T &value)
{
  //## begin cSHVariant::Get%1071244136.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (USHORT_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = (USHORT_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (USHORT_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = (USHORT_T)Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = (USHORT_T)Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_USHORT).c_str());
  //## end cSHVariant::Get%1071244136.body
}

void cSHVariant::Get (LONG_T &value)
{
  //## begin cSHVariant::Get%1071244137.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = _LONG_Value;
      return;
   case SH_FLOAT:
      value = (LONG_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (LONG_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_LONG).c_str());
  //## end cSHVariant::Get%1071244137.body
}

void cSHVariant::Get (ULONG_T &value)
{
  //## begin cSHVariant::Get%1071244138.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (ULONG_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = (ULONG_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (ULONG_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_ULONG).c_str());
  //## end cSHVariant::Get%1071244138.body
}

void cSHVariant::Get (FLOAT_T &value)
{
  //## begin cSHVariant::Get%1071244139.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (FLOAT_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = _FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = (FLOAT_T)_DOUBLE_Value;
      return;
   case SH_STRING:
      value = (FLOAT_T)Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = (FLOAT_T)Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_FLOAT).c_str());
  //## end cSHVariant::Get%1071244139.body
}

void cSHVariant::Get (DOUBLE_T &value)
{
  //## begin cSHVariant::Get%1071244140.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      value = (DOUBLE_T)_LONG_Value;
      return;
   case SH_FLOAT:
      value = (DOUBLE_T)_FLOAT_Value;
      return;
   case SH_DOUBLE:
      value = _DOUBLE_Value;
      return;
   case SH_STRING:
      value = (DOUBLE_T)Dec2Long(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = (DOUBLE_T)Dec2Long(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_DOUBLE).c_str());
  //## end cSHVariant::Get%1071244140.body
}

void cSHVariant::Get (STRING_T &value, UCHAR_T precision)
{
  //## begin cSHVariant::Get%1071244141.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_SHORT:
   case SH_LONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      Long2String(value, _LONG_Value);
      return;
   case SH_UCHAR:
   case SH_USHORT:
   case SH_ULONG:
      ULong2String(value, (ULONG_T)_LONG_Value);
      return;
   case SH_FLOAT:
      Float2String(value, _FLOAT_Value, precision);
      return;
   case SH_DOUBLE:
      Double2String(value, _DOUBLE_Value, precision);
      return;
   case SH_STRING:
      value = _STRING_Value;
      return;
   case SH_WSTRING:
      value = Wide2String(_WSTRING_Value.c_str());
      return;
   case SH_BYTE:
      value = _STRING_Value;
      return;
   case SH_OBJECT:
      value = _STRING_Value;
      return;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_STRING).c_str());
  //## end cSHVariant::Get%1071244141.body
}

void cSHVariant::Get (WSTRING_T &value, UCHAR_T precision)
{
  //## begin cSHVariant::Get%1071244142.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_SHORT:
   case SH_LONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      Long2String(value, _LONG_Value);
      return;
   case SH_UCHAR:
   case SH_USHORT:
   case SH_ULONG:
      ULong2String(value, (ULONG_T)_LONG_Value);
      return;
   case SH_FLOAT:
      Float2String(value, _FLOAT_Value, precision);
      return;
   case SH_DOUBLE:
      Double2String(value, _DOUBLE_Value, precision);
      return;
   case SH_STRING:
      value = String2Wide(_STRING_Value.c_str());
      return;
   case SH_WSTRING:
      value = _WSTRING_Value;
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_WSTRING).c_str());
  //## end cSHVariant::Get%1071244142.body
}

void cSHVariant::Get (BUF_T &buf)
{
  //## begin cSHVariant::Get%1071244143.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      buf = (BUF_T)&_LONG_Value;
      return;
   case SH_FLOAT:
      buf = (BUF_T)&_FLOAT_Value;
      return;
   case SH_DOUBLE:
      buf = (BUF_T)&_DOUBLE_Value;
      return;
   case SH_STRING:
      buf = (BUF_T)_STRING_Value.c_str();
      return;
   case SH_WSTRING:
      buf = (BUF_T)_WSTRING_Value.c_str();
      return;
   case SH_BYTE:
      buf = _BUF_Value;
      return;
   case SH_OBJECT:
      buf = _BUF_Value;
      return;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(_DataType).c_str(), TypeName(SH_WSTRING).c_str());
  //## end cSHVariant::Get%1071244143.body
}

void cSHVariant::Set (CHAR_T value)
{
  //## begin cSHVariant::Set%1071244145.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE: break;
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_CHAR).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244145.body
}

void cSHVariant::Set (UCHAR_T value)
{
  //## begin cSHVariant::Set%1071244146.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE: break;
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_UCHAR).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244146.body
}

void cSHVariant::Set (SHORT_T value)
{
  //## begin cSHVariant::Set%1071244147.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE: break;
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_SHORT).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244147.body
}

void cSHVariant::Set (USHORT_T value)
{
  //## begin cSHVariant::Set%1071244148.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE: break;
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_USHORT).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244148.body
}

void cSHVariant::Set (LONG_T value)
{
  //## begin cSHVariant::Set%1071244149.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE: break;
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_LONG).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244149.body
}

void cSHVariant::Set (ULONG_T value)
{
  //## begin cSHVariant::Set%1071244150.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE: break;
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_ULONG).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244150.body
}

void cSHVariant::Set (FLOAT_T value)
{
  //## begin cSHVariant::Set%1071244151.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      DOUBLE2LONG((DOUBLE_T)value, _LONG_Value);
//      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_FLOAT).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244151.body
}

void cSHVariant::Set (DOUBLE_T value)
{
  //## begin cSHVariant::Set%1071244152.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      DOUBLE2LONG((DOUBLE_T)value, _LONG_Value);
//      _LONG_Value = (LONG_T)value;
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)value;
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)value;
      return;
   case SH_STRING:
      break;
   case SH_WSTRING:
      break;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_DOUBLE).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244152.body
}

void cSHVariant::Set (CONST_STRING_T value)
{
  //## begin cSHVariant::Set%1071244153.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = Dec2Long(value);
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)Real2Float(value);
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)Real2Double(value);
      return;
   case SH_STRING:
      _STRING_Value = value;
      return;
   case SH_WSTRING:
      _WSTRING_Value = String2Wide(value);
      return;
   case SH_BYTE:
      _STRING_Value = value;
      return;
   case SH_OBJECT: break;
      _STRING_Value = value;
      return;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_STRING).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244153.body
}

void cSHVariant::Set (CONST_WSTRING_T value)
{
  //## begin cSHVariant::Set%1071244154.body preserve=yes
   switch (_DataType) {
   case SH_VOID: break;
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
      _LONG_Value = Dec2Long(value);
      return;
   case SH_FLOAT:
      _FLOAT_Value = (FLOAT_T)Real2Float(value);
      return;
   case SH_DOUBLE:
      _DOUBLE_Value = (DOUBLE_T)Real2Double(value);
      return;
   case SH_STRING:
      _STRING_Value = Wide2String(value);
      return;
   case SH_WSTRING:
      _WSTRING_Value = value;
      return;
   case SH_BYTE:
      break;
   case SH_OBJECT:
      break;
   }
   throw cError(VARIANT_CONVERSION_ERROR, 0, TypeName(SH_WSTRING).c_str(), TypeName(_DataType).c_str());
  //## end cSHVariant::Set%1071244154.body
}

void cSHVariant::Set (BUF_T buf)
{
  //## begin cSHVariant::Set%1073740506.body preserve=yes
   _BUF_Value = buf;
  //## end cSHVariant::Set%1073740506.body
}

STRING_T cSHVariant::TypeName (UCHAR_T data_type)
{
  //## begin cSHVariant::TypeName%1056195555.body preserve=yes
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
   char type_name[64] = {0};
   return type_name;
  //## end cSHVariant::TypeName%1056195555.body
}

WSTRING_T cSHVariant::String2Wide (CONST_STRING_T str)
{
  //## begin cSHVariant::String2Wide%1056375604.body preserve=yes
   ULONG_T len = StrLen(str);
   WCHAR_T * buf = (WCHAR_T*)cSystemUtils::Alloc((len+1) * sizeof(WCHAR_T));
   ULONG_T i;
   for (i = 0; i<len; i++) {
      buf[i] = str[i];
   }
   buf[i] = 0;
   WSTRING_T value = (CONST_WSTRING_T)buf;
   cSystemUtils::Free(buf);
   return value;
  //## end cSHVariant::String2Wide%1056375604.body
}

STRING_T cSHVariant::Wide2String (CONST_WSTRING_T str)
{
  //## begin cSHVariant::Wide2String%1056195556.body preserve=yes
   ULONG_T len = StrLen(str);
   CHAR_T * buf = (CHAR_T*)cSystemUtils::Alloc(len+1);
   ULONG_T i;
   for (i = 0; i<len; i++) {
      buf[i] = (CHAR_T)str[i];
   }
   buf[i] = 0;
   STRING_T value = (const char*)buf;
   cSystemUtils::Free(buf);
   return value;
  //## end cSHVariant::Wide2String%1056195556.body
}

DOUBLE_T cSHVariant::Real2Double (CONST_STRING_T str)
{
  //## begin cSHVariant::Real2Double%1056195557.body preserve=yes
   DOUBLE_T value = 0;
   sscanf(str, "%lf", &value);
   return (DOUBLE_T)value;
  //## end cSHVariant::Real2Double%1056195557.body
}

DOUBLE_T cSHVariant::Real2Double (CONST_WSTRING_T str)
{
  //## begin cSHVariant::Real2Double%1056375592.body preserve=yes
   DOUBLE_T value = 0;
   STRING_T temp_str = Wide2String(str);
   sscanf(temp_str.c_str(), "%lf", &value);
   return value;
  //## end cSHVariant::Real2Double%1056375592.body
}

FLOAT_T cSHVariant::Real2Float (CONST_STRING_T str)
{
  //## begin cSHVariant::Real2Float%1056375594.body preserve=yes
   FLOAT_T value = 0;
   sscanf(str, "%f", &value);
   return value;
  //## end cSHVariant::Real2Float%1056375594.body
}

FLOAT_T cSHVariant::Real2Float (CONST_WSTRING_T str)
{
  //## begin cSHVariant::Real2Float%1056375593.body preserve=yes
   FLOAT_T value = 0;
   STRING_T temp_str = Wide2String(str);
   sscanf(temp_str.c_str(), "%lf", &value);
   return value;
  //## end cSHVariant::Real2Float%1056375593.body
}

ULONG_T cSHVariant::Hex2Ulong (CONST_STRING_T str)
{
  //## begin cSHVariant::Hex2Ulong%1056375595.body preserve=yes
   ULONG_T value = 0;
   sscanf(str, "%x", &value);
   return value;
  //## end cSHVariant::Hex2Ulong%1056375595.body
}

ULONG_T cSHVariant::Hex2Ulong (CONST_WSTRING_T str)
{
  //## begin cSHVariant::Hex2Ulong%1056375596.body preserve=yes
   ULONG_T value = 0;
   STRING_T temp_str = Wide2String(str);
   sscanf(temp_str.c_str(), "%x", &value);
   return value;
  //## end cSHVariant::Hex2Ulong%1056375596.body
}

LONG_T cSHVariant::Dec2Long (CONST_STRING_T str)
{
  //## begin cSHVariant::Dec2Long%1056375599.body preserve=yes
   LONG_T value = 0;
   sscanf(str, "%d", &value);
   return value;
  //## end cSHVariant::Dec2Long%1056375599.body
}

LONG_T cSHVariant::Dec2Long (CONST_WSTRING_T str)
{
  //## begin cSHVariant::Dec2Long%1056375600.body preserve=yes
   LONG_T value = 0;
   STRING_T temp_str = Wide2String(str);
   sscanf(temp_str.c_str(), "%d", &value);
   return value;
  //## end cSHVariant::Dec2Long%1056375600.body
}

LONG_T cSHVariant::BCD2Long (CONST_STRING_T str)
{
  //## begin cSHVariant::BCD2Long%1056375605.body preserve=yes
_ASSERT_UNCOND
return 0;
  //## end cSHVariant::BCD2Long%1056375605.body
}

LONG_T cSHVariant::BCD2Long (CONST_WSTRING_T str)
{
  //## begin cSHVariant::BCD2Long%1056375606.body preserve=yes
_ASSERT_UNCOND
return 0;
  //## end cSHVariant::BCD2Long%1056375606.body
}

LONG_T cSHVariant::KMBCD2Long (CONST_STRING_T str)
{
  //## begin cSHVariant::KMBCD2Long%1056375607.body preserve=yes
_ASSERT_UNCOND
return 0;
  //## end cSHVariant::KMBCD2Long%1056375607.body
}

LONG_T cSHVariant::KMBCD2Long (CONST_WSTRING_T str)
{
  //## begin cSHVariant::KMBCD2Long%1056375608.body preserve=yes
_ASSERT_UNCOND
return 0;
  //## end cSHVariant::KMBCD2Long%1056375608.body
}

void cSHVariant::Long2String (STRING_T &str, LONG_T value, UCHAR_T radix)
{
  //## begin cSHVariant::Long2String%1056447736.body preserve=yes
   char buf[64] = {0};
   str = _ltoa(value, buf, radix);
  //## end cSHVariant::Long2String%1056447736.body
}

void cSHVariant::Long2String (WSTRING_T &str, LONG_T value, UCHAR_T radix)
{
  //## begin cSHVariant::Long2String%1056447737.body preserve=yes
   char buf[64] = {0};
   str = String2Wide(_ltoa(value, buf, radix));
  //## end cSHVariant::Long2String%1056447737.body
}

void cSHVariant::ULong2String (STRING_T &str, ULONG_T value, UCHAR_T radix)
{
  //## begin cSHVariant::ULong2String%1236356396.body preserve=yes
   char buf[64] = {0};
   str = _ultoa(value, buf, radix);
  //## end cSHVariant::ULong2String%1236356396.body
}

void cSHVariant::ULong2String (WSTRING_T &str, ULONG_T value, UCHAR_T radix)
{
  //## begin cSHVariant::ULong2String%1236356397.body preserve=yes
   char buf[64] = {0};
   str = String2Wide(_ultoa(value, buf, radix));
  //## end cSHVariant::ULong2String%1236356397.body
}

void cSHVariant::Float2String (STRING_T &str, FLOAT_T value, UCHAR_T precision)
{
  //## begin cSHVariant::Float2String%1056447738.body preserve=yes
   char buf[64] = {0};
   if ((precision >= 0) && (precision <= MAX_PRECISION)) {
      SafePrintf(buf, sizeof(buf), "%.*f", precision, value);
   } else {
      SafePrintf(buf, sizeof(buf), "%lf", value);
   }
   str = buf;
  //## end cSHVariant::Float2String%1056447738.body
}

void cSHVariant::Float2String (WSTRING_T &str, FLOAT_T value, UCHAR_T precision)
{
  //## begin cSHVariant::Float2String%1056447739.body preserve=yes
   char buf[64] = {0};
   if ((precision >= 0) && (precision <= MAX_PRECISION)) {
      SafePrintf(buf, sizeof(buf), "%.*f", precision, value);
   } else {
      SafePrintf(buf, sizeof(buf), "%lf", value);
   }
   str = String2Wide(buf);
  //## end cSHVariant::Float2String%1056447739.body
}

void cSHVariant::Double2String (STRING_T &str, DOUBLE_T value, UCHAR_T precision)
{
  //## begin cSHVariant::Double2String%1056447740.body preserve=yes
   char buf[64] = {0};

   if ((value >= 1.0e+30) || (value <= -1.0e+30)) {
      SafePrintf(buf, sizeof(buf), "%.*e", precision, value);
   }
   else {
      if ((precision >= 0) && (precision <= MAX_PRECISION)) {
         SafePrintf(buf, sizeof(buf), "%.*f", precision, value);
      } else {
         SafePrintf(buf, sizeof(buf), "%lf", value);
      }
   }
   str = buf;
  //## end cSHVariant::Double2String%1056447740.body
}

void cSHVariant::Double2String (WSTRING_T &str, DOUBLE_T value, UCHAR_T precision)
{
  //## begin cSHVariant::Double2String%1056447741.body preserve=yes
   char buf[64] = {0};

   if ((value >= 1.0e+30) || (value <= -1.0e+30)) {
      SafePrintf(buf, sizeof(buf), "%.*e", precision, value);
   }
   else {
      if ((precision >= 0) && (precision <= MAX_PRECISION)) {
         SafePrintf(buf, sizeof(buf), "%.*f", precision, value);
      } else {
         SafePrintf(buf, sizeof(buf), "%lf", value);
      }
   }
   str = String2Wide(buf);
  //## end cSHVariant::Double2String%1056447741.body
}

ULONG_T cSHVariant::StrLen (CONST_STRING_T str)
{
  //## begin cSHVariant::StrLen%1056195558.body preserve=yes
   return strlen(str);
  //## end cSHVariant::StrLen%1056195558.body
}

ULONG_T cSHVariant::StrLen (CONST_WSTRING_T str)
{
  //## begin cSHVariant::StrLen%1056195559.body preserve=yes
   ULONG_T i = 0;
   while (true) {
      if (str[i] == 0) return i + 1;
      i++;
   }
  //## end cSHVariant::StrLen%1056195559.body
}

INT_T cSHVariant::StrCmp (CONST_STRING_T str1, CONST_STRING_T str2)
{
  //## begin cSHVariant::StrCmp%1056621170.body preserve=yes
   return strcmp(str1, str2);
  //## end cSHVariant::StrCmp%1056621170.body
}

INT_T cSHVariant::StrCmp (CONST_WSTRING_T str1, CONST_WSTRING_T str2)
{
  //## begin cSHVariant::StrCmp%1056621171.body preserve=yes
   ULONG_T len = StrLen(str1);
   if (len != StrLen(str2)) return -1;
   for (ULONG_T i=0; i<len; i++) {
      if (str1[i] != str2[i]) return false;
   }
   return true;
  //## end cSHVariant::StrCmp%1056621171.body
}

ULONG_T cSHVariant::MemSize (CONST_STRING_T str)
{
  //## begin cSHVariant::MemSize%1056478821.body preserve=yes
   return StrLen(str) * sizeof(CHAR_T);
  //## end cSHVariant::MemSize%1056478821.body
}

ULONG_T cSHVariant::MemSize (CONST_WSTRING_T str)
{
  //## begin cSHVariant::MemSize%1056478822.body preserve=yes
   return StrLen(str) * sizeof(WCHAR_T);
  //## end cSHVariant::MemSize%1056478822.body
}

ULONG_T cSHVariant::TypeSize (UCHAR_T data_type)
{
  //## begin cSHVariant::TypeSize%1056478823.body preserve=yes
   switch (data_type) {
   case SH_VOID: return 0;
   case SH_CHAR: return sizeof(CHAR_T);
   case SH_UCHAR: return sizeof(UCHAR_T);
   case SH_SHORT: return sizeof(SHORT_T);
   case SH_USHORT: return sizeof(USHORT_T);
   case SH_LONG: return sizeof(LONG_T);
   case SH_ULONG: return sizeof(ULONG_T);
   case SH_BIT_8: return sizeof(UCHAR_T);
   case SH_BIT_16: return sizeof(USHORT_T);
   case SH_BIT_32: return sizeof(ULONG_T);
   case SH_FLOAT: return sizeof(FLOAT_T);
   case SH_DOUBLE: return sizeof(DOUBLE_T);
   case SH_STRING: return sizeof(CHAR_T);
   case SH_WSTRING: return sizeof(WCHAR_T);
   case SH_BYTE: return 1;
   case SH_OBJECT: return 1;
   default:
_ASSERT_UNCOND
      return 0;
   }
  //## end cSHVariant::TypeSize%1056478823.body
}

//## Get and Set Operations for Class Attributes (implementation)

UCHAR_T cSHVariant::get_DataType () const
{
  //## begin cSHVariant::get_DataType%3EF32B4F032C.get preserve=no
  return _DataType;
  //## end cSHVariant::get_DataType%3EF32B4F032C.get
}

void cSHVariant::set_DataType (UCHAR_T value)
{
  //## begin cSHVariant::set_DataType%3EF32B4F032C.set preserve=no
  _DataType = value;
  //## end cSHVariant::set_DataType%3EF32B4F032C.set
}

// Additional Declarations
  //## begin cSHVariant%3EF2E1D8008C.declarations preserve=yes
  //## end cSHVariant%3EF2E1D8008C.declarations

//## begin module%3EF2E1D8008C.epilog preserve=yes
//## end module%3EF2E1D8008C.epilog
