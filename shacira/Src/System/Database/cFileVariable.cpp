//## begin module%4113C89D00AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4113C89D00AB.cm

//## begin module%4113C89D00AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4113C89D00AB.cp

//## Module: cFileVariable%4113C89D00AB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFileVariable.cpp

//## begin module%4113C89D00AB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4113C89D00AB.additionalIncludes

//## begin module%4113C89D00AB.includes preserve=yes

/// PR 12.08.05 - implemented Set methods for integer, string and real types

//## end module%4113C89D00AB.includes

// cVarDef
#include "System/Database/cVarDef.h"
// cFileVariable
#include "System/Database/cFileVariable.h"
// cVariableValues
#include "System/Database/cVariableValues.h"
//## begin module%4113C89D00AB.additionalDeclarations preserve=yes
//## end module%4113C89D00AB.additionalDeclarations


// Class cFileVariable 

cFileVariable::cFileVariable()
  //## begin cFileVariable::cFileVariable%.hasinit preserve=no
  //## end cFileVariable::cFileVariable%.hasinit
  //## begin cFileVariable::cFileVariable%.initialization preserve=yes
  //## end cFileVariable::cFileVariable%.initialization
{
  //## begin cFileVariable::cFileVariable%.body preserve=yes
  //## end cFileVariable::cFileVariable%.body
}

cFileVariable::cFileVariable(const cFileVariable &right)
  //## begin cFileVariable::cFileVariable%copy.hasinit preserve=no
  //## end cFileVariable::cFileVariable%copy.hasinit
  //## begin cFileVariable::cFileVariable%copy.initialization preserve=yes
  //## end cFileVariable::cFileVariable%copy.initialization
{
  //## begin cFileVariable::cFileVariable%copy.body preserve=yes
  //## end cFileVariable::cFileVariable%copy.body
}

cFileVariable::cFileVariable (cVarDef *var_def)
  //## begin cFileVariable::cFileVariable%1091815614.hasinit preserve=no
  //## end cFileVariable::cFileVariable%1091815614.hasinit
  //## begin cFileVariable::cFileVariable%1091815614.initialization preserve=yes
  : cVariable(var_def)
  //## end cFileVariable::cFileVariable%1091815614.initialization
{
  //## begin cFileVariable::cFileVariable%1091815614.body preserve=yes
  //## end cFileVariable::cFileVariable%1091815614.body
}


cFileVariable::~cFileVariable()
{
  //## begin cFileVariable::~cFileVariable%.body preserve=yes
  //## end cFileVariable::~cFileVariable%.body
}



//## Other Operations (implementation)
STRING_T cFileVariable::UnitText ()
{
  //## begin cFileVariable::UnitText%1111426862.body preserve=yes
   return "?";
  //## end cFileVariable::UnitText%1111426862.body
}

void cFileVariable::Get (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815650.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (CHAR_T)lval;
  //## end cFileVariable::Get%1091815650.body
}

void cFileVariable::Get (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815651.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (UCHAR_T)lval;
  //## end cFileVariable::Get%1091815651.body
}

void cFileVariable::Get (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815652.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (SHORT_T)lval;
  //## end cFileVariable::Get%1091815652.body
}

void cFileVariable::Get (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815653.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (USHORT_T)lval;
  //## end cFileVariable::Get%1091815653.body
}

void cFileVariable::Get (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815654.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   cVariableValues * values = _VarDef->_Values;
   if (values != NULL) {
      STRING_T svalue = values->GetValue(pos);
      value = atol(svalue.c_str());
   }
  //## end cFileVariable::Get%1091815654.body
}

void cFileVariable::Get (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815655.body preserve=yes
   LONG_T lval = 0;
   Get(lval, i1, i2, i3, i4, flags);
   value = (ULONG_T)lval;
  //## end cFileVariable::Get%1091815655.body
}

void cFileVariable::Get (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815656.body preserve=yes
   DOUBLE_T dval = 0;
   Get(dval, i1, i2, i3, i4, flags);
   value = (FLOAT_T)dval;
  //## end cFileVariable::Get%1091815656.body
}

void cFileVariable::Get (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815657.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   cVariableValues * values = _VarDef->_Values;
   if (values != NULL) {
      STRING_T svalue = values->GetValue(pos);
      value = atof(svalue.c_str());
   }
  //## end cFileVariable::Get%1091815657.body
}

void cFileVariable::Get (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815658.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   cVariableValues * values = _VarDef->_Values;
   if (values != NULL) {
      value = values->GetValue(pos);
      UCHAR_T data_type = DataType();
      if (data_type == SH_STRING) {
         ULONG_T size = ValueSize() * 2;
         STRING_BUF_T buf = (STRING_BUF_T)cSystemUtils::Alloc(size+1);
         int params = sscanf(value.c_str(), "bcd('%[^']')", buf);
         if (params == 1) {
            // this is a pre store conversion of strings containing non ascii
            // characters to display correct header informatiuons in this case
            BUF_T dst_buf = (BUF_T)cSystemUtils::Alloc(size+1);
            cConvUtils::BCD2Buf(buf, dst_buf, size);
            value = (CONST_STRING_T)dst_buf;
            cSystemUtils::Free(dst_buf);
         }
         cSystemUtils::Free((void*)buf);
      }
   }
  //## end cFileVariable::Get%1091815658.body
}

void cFileVariable::Get (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815659.body preserve=yes
  //## end cFileVariable::Get%1091815659.body
}

void cFileVariable::Get (BUF_T &buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815660.body preserve=yes
  //## end cFileVariable::Get%1091815660.body
}

void cFileVariable::Get (BUF_T &buf, ULONG_T &size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
}

void cFileVariable::Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Get%1091815661.body preserve=yes
  //## end cFileVariable::Get%1091815661.body
}

void cFileVariable::Set (CHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815662.body preserve=yes
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cFileVariable::Set%1091815662.body
}

void cFileVariable::Set (UCHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815663.body preserve=yes
   Set((ULONG_T)value, i1, i2, i3, i4, flags);
  //## end cFileVariable::Set%1091815663.body
}

void cFileVariable::Set (SHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815664.body preserve=yes
   Set((LONG_T)value, i1, i2, i3, i4, flags);
  //## end cFileVariable::Set%1091815664.body
}

void cFileVariable::Set (USHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815665.body preserve=yes
   Set((ULONG_T)value, i1, i2, i3, i4, flags);
  //## end cFileVariable::Set%1091815665.body
}

void cFileVariable::Set (LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815666.body preserve=yes
   Set((ULONG_T)value, i1, i2, i3, i4, flags);
  //## end cFileVariable::Set%1091815666.body
}

void cFileVariable::Set (ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815667.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   cVariableValues * values = _VarDef->_Values;
   if (values != NULL) {
      char buf[0x100] = {0};
      SafePrintf(buf, sizeof(buf), "%d", value);
      values->SetValue(pos, buf);
   } 
  //## end cFileVariable::Set%1091815667.body
}

void cFileVariable::Set (FLOAT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815668.body preserve=yes
   DOUBLE_T dval = value;
   Set(dval, i1, i2, i3, i4, flags);
  //## end cFileVariable::Set%1091815668.body
}

void cFileVariable::Set (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815669.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   cVariableValues * values = _VarDef->_Values;
   if (values != NULL) {
      char buf[0x100] = {0};
      SafePrintf(buf, sizeof(buf), "%f", value);
      values->SetValue(pos, buf);
   } 
  //## end cFileVariable::Set%1091815669.body
}

void cFileVariable::Set (CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815670.body preserve=yes
   ULONG_T pos = _VarDef->GetPos(i1, i2, i3, i4);
   cVariableValues * values = _VarDef->_Values;
   if (values != NULL) {
      values->SetValue(pos, value);
   } 
  //## end cFileVariable::Set%1091815670.body
}

void cFileVariable::Set (CONST_WSTRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815671.body preserve=yes
  //## end cFileVariable::Set%1091815671.body
}

void cFileVariable::Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::Set%1091815672.body preserve=yes
  //## end cFileVariable::Set%1091815672.body
}

void cFileVariable::GetMinimum (LONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cFileVariable::GetMinimum%1091815677.body preserve=yes
  //## end cFileVariable::GetMinimum%1091815677.body
}

void cFileVariable::GetMinimum (ULONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cFileVariable::GetMinimum%1091815678.body preserve=yes
  //## end cFileVariable::GetMinimum%1091815678.body
}

void cFileVariable::GetMinimum (FLOAT_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFileVariable::GetMinimum%1091815679.body preserve=yes
  //## end cFileVariable::GetMinimum%1091815679.body
}

void cFileVariable::GetMinimum (DOUBLE_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFileVariable::GetMinimum%1091815680.body preserve=yes
  //## end cFileVariable::GetMinimum%1091815680.body
}

void cFileVariable::GetMinimum (STRING_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFileVariable::GetMinimum%1091815681.body preserve=yes
  //## end cFileVariable::GetMinimum%1091815681.body
}

void cFileVariable::GetMaximum (LONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cFileVariable::GetMaximum%1091815682.body preserve=yes
  //## end cFileVariable::GetMaximum%1091815682.body
}

void cFileVariable::GetMaximum (ULONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cFileVariable::GetMaximum%1091815683.body preserve=yes
  //## end cFileVariable::GetMaximum%1091815683.body
}

void cFileVariable::GetMaximum (FLOAT_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFileVariable::GetMaximum%1091815684.body preserve=yes
  //## end cFileVariable::GetMaximum%1091815684.body
}

void cFileVariable::GetMaximum (DOUBLE_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFileVariable::GetMaximum%1091815685.body preserve=yes
  //## end cFileVariable::GetMaximum%1091815685.body
}

void cFileVariable::GetMaximum (STRING_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFileVariable::GetMaximum%1091815686.body preserve=yes
  //## end cFileVariable::GetMaximum%1091815686.body
}

ULONG_T cFileVariable::GetObject (cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::GetObject%1238436640.body preserve=yes
   return 0;
  //## end cFileVariable::GetObject%1238436640.body
}

void cFileVariable::SetObject (const cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFileVariable::SetObject%1238436641.body preserve=yes
  //## end cFileVariable::SetObject%1238436641.body
}

// Additional Declarations
  //## begin cFileVariable%4113C89D00AB.declarations preserve=yes
  //## end cFileVariable%4113C89D00AB.declarations

//## begin module%4113C89D00AB.epilog preserve=yes
//## end module%4113C89D00AB.epilog
