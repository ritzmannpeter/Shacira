//## begin module%3E003A1F00CC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E003A1F00CC.cm

//## begin module%3E003A1F00CC.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E003A1F00CC.cp

//## Module: cRemoteVar%3E003A1F00CC; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\RemoteDatabase\cRemoteVar.cpp

//## begin module%3E003A1F00CC.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E003A1F00CC.additionalIncludes

//## begin module%3E003A1F00CC.includes preserve=yes
//## end module%3E003A1F00CC.includes

// cCellProxy
#include "System/Process/cCellProxy.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
// cRemoteContext
#include "Client/RemoteDatabase/cRemoteContext.h"
// cRemoteVar
#include "Client/RemoteDatabase/cRemoteVar.h"
//## begin module%3E003A1F00CC.additionalDeclarations preserve=yes
//## end module%3E003A1F00CC.additionalDeclarations


// Class cRemoteVar 


cRemoteVar::cRemoteVar()
  //## begin cRemoteVar::cRemoteVar%.hasinit preserve=no
      : _CellProxy(NULL)
  //## end cRemoteVar::cRemoteVar%.hasinit
  //## begin cRemoteVar::cRemoteVar%.initialization preserve=yes
  //## end cRemoteVar::cRemoteVar%.initialization
{
  //## begin cRemoteVar::cRemoteVar%.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteVar::cRemoteVar%.body
}

cRemoteVar::cRemoteVar(const cRemoteVar &right)
  //## begin cRemoteVar::cRemoteVar%copy.hasinit preserve=no
      : _CellProxy(NULL)
  //## end cRemoteVar::cRemoteVar%copy.hasinit
  //## begin cRemoteVar::cRemoteVar%copy.initialization preserve=yes
  //## end cRemoteVar::cRemoteVar%copy.initialization
{
  //## begin cRemoteVar::cRemoteVar%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteVar::cRemoteVar%copy.body
}

cRemoteVar::cRemoteVar (cVarDef *var_def)
  //## begin cRemoteVar::cRemoteVar%1040202765.hasinit preserve=no
      : _CellProxy(NULL)
  //## end cRemoteVar::cRemoteVar%1040202765.hasinit
  //## begin cRemoteVar::cRemoteVar%1040202765.initialization preserve=yes
  , cVariable(var_def)
  //## end cRemoteVar::cRemoteVar%1040202765.initialization
{
  //## begin cRemoteVar::cRemoteVar%1040202765.body preserve=yes
   cRemoteContext * context = dynamic_cast<cRemoteContext*>(_VarDef->_Context);
   if (context != NULL) {
      _CellProxy = context->GetCellProxy();
   }
   if (_CellProxy == NULL) {
      ErrorPrintf("cell proxy is null in %s %d\n", __FILE__, __LINE__);
   }
  //## end cRemoteVar::cRemoteVar%1040202765.body
}


cRemoteVar::~cRemoteVar()
{
  //## begin cRemoteVar::~cRemoteVar%.body preserve=yes
  //## end cRemoteVar::~cRemoteVar%.body
}



//## Other Operations (implementation)
void cRemoteVar::Get (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244182.body preserve=yes
   LONG_T temp_val = 0;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = (CHAR_T)temp_val;
  //## end cRemoteVar::Get%1071244182.body
}

void cRemoteVar::Get (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244183.body preserve=yes
   LONG_T temp_val = 0;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = (UCHAR_T)temp_val;
  //## end cRemoteVar::Get%1071244183.body
}

void cRemoteVar::Get (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244184.body preserve=yes
   LONG_T temp_val = 0;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = (SHORT_T)temp_val;
  //## end cRemoteVar::Get%1071244184.body
}

void cRemoteVar::Get (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244185.body preserve=yes
   LONG_T temp_val = 0;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = (USHORT_T)temp_val;
  //## end cRemoteVar::Get%1071244185.body
}

void cRemoteVar::Get (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244186.body preserve=yes
   STRING_T temp_val;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = atol(temp_val.c_str());
  //## end cRemoteVar::Get%1071244186.body
}

void cRemoteVar::Get (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244187.body preserve=yes
   LONG_T temp_val = 0;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = (ULONG_T)temp_val;
  //## end cRemoteVar::Get%1071244187.body
}

void cRemoteVar::Get (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244188.body preserve=yes
   DOUBLE_T temp_val = 0;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = (FLOAT_T)temp_val;
  //## end cRemoteVar::Get%1071244188.body
}

void cRemoteVar::Get (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244189.body preserve=yes
   STRING_T temp_val;
   Get(temp_val, i1, i2, i3, i4, flags);
   value = atof(temp_val.c_str());
  //## end cRemoteVar::Get%1071244189.body
}

void cRemoteVar::Get (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244190.body preserve=yes
   if (_CellProxy == NULL) {
      int dummy = 0;
   } else {
	   _CellProxy->GetValue(VarName().c_str(), value, i1, i2, i3, i4, flags);
   }
  //## end cRemoteVar::Get%1071244190.body
}

void cRemoteVar::Get (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244191.body preserve=yes
   GetMemoryType(value, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Get%1071244191.body
}

void cRemoteVar::Get (BUF_T &buf_ptr, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244192.body preserve=yes
   GetMemoryType(buf_ptr, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Get%1071244192.body
}

void cRemoteVar::Get (BUF_T &buf_ptr, ULONG_T & size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
   GetMemoryType(buf_ptr, i1, i2, i3, i4, flags);
}

void cRemoteVar::Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Get%1071244193.body preserve=yes
   GetMemoryType(buf, len, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Get%1071244193.body
}

void cRemoteVar::Refresh (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Refresh%1133172777.body preserve=yes
 	_CellProxy->RefreshValue(VarName().c_str(), i1, i2, i3, i4, flags);
  //## end cRemoteVar::Refresh%1133172777.body
}

void cRemoteVar::Set (CHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244194.body preserve=yes
   LONG_T lvalue = value;
   Set(lvalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244194.body
}

void cRemoteVar::Set (UCHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244195.body preserve=yes
   LONG_T lvalue = value;
   Set(lvalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244195.body
}

void cRemoteVar::Set (SHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244196.body preserve=yes
   LONG_T lvalue = value;
   Set(lvalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244196.body
}

void cRemoteVar::Set (USHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244197.body preserve=yes
   LONG_T lvalue = value;
   Set(lvalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244197.body
}

void cRemoteVar::Set (LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244198.body preserve=yes
   char svalue[64] = {0};
   SafePrintf(svalue, sizeof(svalue), "%d", value);
   Set(svalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244198.body
}

void cRemoteVar::Set (ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244199.body preserve=yes
   LONG_T lvalue = value;
   Set(lvalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244199.body
}

void cRemoteVar::Set (FLOAT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244200.body preserve=yes
   char svalue[64] = {0};
   SafePrintf(svalue, sizeof(svalue), "%f", value);
   Set(svalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244200.body
}

void cRemoteVar::Set (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244201.body preserve=yes
   char svalue[64] = {0};
   SafePrintf(svalue, sizeof(svalue), "%f", value);
   Set(svalue, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244201.body
}

void cRemoteVar::Set (CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244202.body preserve=yes
 	_CellProxy->SetValue(VarName().c_str(), value, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244202.body
}

void cRemoteVar::Set (CONST_WSTRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244203.body preserve=yes
   SetMemoryType(value, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244203.body
}

void cRemoteVar::Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::Set%1071244204.body preserve=yes
   SetMemoryType(buf, len, i1, i2, i3, i4, flags);
  //## end cRemoteVar::Set%1071244204.body
}

void cRemoteVar::GetMinimum (LONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cRemoteVar::GetMinimum%1089103319.body preserve=yes
 	_CellProxy->GetMinimum(VarName().c_str(), minimum, i1, i2, i3, i4, fixed_decimal_representation);
  //## end cRemoteVar::GetMinimum%1089103319.body
}

void cRemoteVar::GetMinimum (ULONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cRemoteVar::GetMinimum%1089103320.body preserve=yes
   LONG_T _minimum = 0;
 	_CellProxy->GetMinimum(VarName().c_str(), _minimum, i1, i2, i3, i4, fixed_decimal_representation);
   minimum = (ULONG_T)_minimum;
  //## end cRemoteVar::GetMinimum%1089103320.body
}

void cRemoteVar::GetMinimum (FLOAT_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cRemoteVar::GetMinimum%1089103321.body preserve=yes
   DOUBLE_T _minimum = 0;
   GetMinimum(_minimum, i1, i2, i3, i4);
   minimum = (FLOAT_T)_minimum;
  //## end cRemoteVar::GetMinimum%1089103321.body
}

void cRemoteVar::GetMinimum (DOUBLE_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cRemoteVar::GetMinimum%1089103322.body preserve=yes
 	_CellProxy->GetMinimum(VarName().c_str(), minimum, i1, i2, i3, i4);
  //## end cRemoteVar::GetMinimum%1089103322.body
}

void cRemoteVar::GetMinimum (STRING_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cRemoteVar::GetMinimum%1089203190.body preserve=yes
 	_CellProxy->GetMinimum(VarName().c_str(), minimum, i1, i2, i3, i4);
  //## end cRemoteVar::GetMinimum%1089203190.body
}

void cRemoteVar::GetMaximum (LONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cRemoteVar::GetMaximum%1089103323.body preserve=yes
 	_CellProxy->GetMaximum(VarName().c_str(), maximum, i1, i2, i3, i4, fixed_decimal_representation);
  //## end cRemoteVar::GetMaximum%1089103323.body
}

void cRemoteVar::GetMaximum (ULONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cRemoteVar::GetMaximum%1089103324.body preserve=yes
   LONG_T _maximum = 0;
   GetMaximum(_maximum, i1, i2, i3, i4, fixed_decimal_representation);
   maximum = _maximum;
  //## end cRemoteVar::GetMaximum%1089103324.body
}

void cRemoteVar::GetMaximum (FLOAT_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cRemoteVar::GetMaximum%1089103325.body preserve=yes
   DOUBLE_T _maximum = 0;
   GetMaximum(_maximum, i1, i2, i3, i4);
   maximum = (FLOAT_T)_maximum;
  //## end cRemoteVar::GetMaximum%1089103325.body
}

void cRemoteVar::GetMaximum (DOUBLE_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cRemoteVar::GetMaximum%1089103326.body preserve=yes
 	_CellProxy->GetMaximum(VarName().c_str(), maximum, i1, i2, i3, i4);
  //## end cRemoteVar::GetMaximum%1089103326.body
}

void cRemoteVar::GetMaximum (STRING_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cRemoteVar::GetMaximum%1089203191.body preserve=yes
 	_CellProxy->GetMaximum(VarName().c_str(), maximum, i1, i2, i3, i4);
  //## end cRemoteVar::GetMaximum%1089203191.body
}

BOOL_T cRemoteVar::GetMemoryType (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::GetMemoryType%1092218358.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_WSTRING) {
      STRING_T svalue;
      Get(svalue, i1, i2, i3, i4, flags);
      ULONG_T size = ValueSize();
      BUF_T temp_buf = cSystemUtils::CachedAlloc(_VarDef->_VarName.c_str(),
                                                 i1, i2, i3, i4,
                                                 size);
      cConvUtils::String2Buf(svalue.c_str(), temp_buf, size);
      value = (CONST_WSTRING_T)temp_buf;
      return true;
   } else if (data_type == SH_STRING) {
      STRING_T svalue;
      Get(svalue, i1, i2, i3, i4, flags);
      value = cSHVariant::String2Wide(svalue.c_str());
      return true;
   }
   return false;
  //## end cRemoteVar::GetMemoryType%1092218358.body
}

BOOL_T cRemoteVar::GetMemoryType (BUF_T &buf_ptr, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::GetMemoryType%1092218355.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_BYTE ||
       data_type == SH_OBJECT) {
      STRING_T svalue;
      Get(svalue, i1, i2, i3, i4, flags);
      ULONG_T size = ValueSize();
      BUF_T temp_buf = cSystemUtils::CachedAlloc(_VarDef->_VarName.c_str(),
                                                 i1, i2, i3, i4,
                                                 size);
//      cConvUtils::String2Buf(svalue.c_str(), temp_buf, size);
      if (_CellProxy != NULL) {
         PTR_T mem_address = NULL;
         cConvUtils::String2Ptr(mem_address, svalue.c_str());
         if (mem_address != NULL) {
            _CellProxy->GetMemory(temp_buf, mem_address, size);
         }
      }
      buf_ptr = temp_buf;
      return true;
   }
   return false;
  //## end cRemoteVar::GetMemoryType%1092218355.body
}

BOOL_T cRemoteVar::GetMemoryType (BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::GetMemoryType%1092218356.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_BYTE ||
       data_type == SH_OBJECT) {
      STRING_T svalue;
      Get(svalue, i1, i2, i3, i4, flags);
      ULONG_T size = ValueSize();
      BUF_T temp_buf = (BUF_T)cSystemUtils::Alloc(size);
      cConvUtils::String2Buf(svalue.c_str(), temp_buf, size);
      memcpy(buf, temp_buf, _MIN_(size,len));
      cSystemUtils::Free(temp_buf);
      return true;
   }
   return false;
  //## end cRemoteVar::GetMemoryType%1092218356.body
}

BOOL_T cRemoteVar::SetMemoryType (CONST_WSTRING_T value, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::SetMemoryType%1092218357.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_WSTRING) {
      ULONG_T size = ValueSize();
      ULONG_T var_len = cSHVariant::StrLen(value) * sizeof(WCHAR_T);
      BUF_T buf = (BUF_T)value;
      STRING_T svalue;
      cConvUtils::Buf2String(svalue, buf, _MIN_(size,var_len));
      Set(svalue.c_str(), i1, i2, i3, i4, flags);
      return true;
   } else if (data_type == SH_STRING) {
      STRING_T svalue = cSHVariant::Wide2String(value);
      Set(svalue.c_str(), i1, i2, i3, i4, flags);
      return true;
   }
   return false;
  //## end cRemoteVar::SetMemoryType%1092218357.body
}

BOOL_T cRemoteVar::SetMemoryType (CONST_BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::SetMemoryType%1092218359.body preserve=yes
   UCHAR_T data_type = DataType();
   if (data_type == SH_BYTE ||
       data_type == SH_OBJECT) {
      STRING_T svalue;
      cConvUtils::Buf2String(svalue, (BUF_T)buf, len);
      Set(svalue.c_str(), i1, i2, i3, i4, flags);
      return true;
   }
   return false;
  //## end cRemoteVar::SetMemoryType%1092218359.body
}

ULONG_T cRemoteVar::GetObject (cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::GetObject%1238436648.body preserve=yes
   if (_CellProxy == NULL) {
      return 0;
   } else {
      return _CellProxy->GetObject(object, VarName().c_str(), i1, i2, i3, i4, flags);
   }
  //## end cRemoteVar::GetObject%1238436648.body
}

void cRemoteVar::SetObject (const cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cRemoteVar::SetObject%1238436649.body preserve=yes
   if (_CellProxy == NULL) {
      int dummy = 0;
   } else {
      _CellProxy->SetObject(object, VarName().c_str(), i1, i2, i3, i4, flags);
   }
  //## end cRemoteVar::SetObject%1238436649.body
}

// Additional Declarations
  //## begin cRemoteVar%3E003A1F00CC.declarations preserve=yes
  //## end cRemoteVar%3E003A1F00CC.declarations

//## begin module%3E003A1F00CC.epilog preserve=yes
//## end module%3E003A1F00CC.epilog
