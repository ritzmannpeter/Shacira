//## begin module%3F39224B03B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F39224B03B9.cm

//## begin module%3F39224B03B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F39224B03B9.cp

//## Module: cStateVariable%3F39224B03B9; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cStateVariable.cpp

//## begin module%3F39224B03B9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F39224B03B9.additionalIncludes

//## begin module%3F39224B03B9.includes preserve=yes
//## end module%3F39224B03B9.includes

// cStateVariable
#include "System/PLC/cStateVariable.h"
// cControlState
#include "System/PLC/cControlState.h"
//## begin module%3F39224B03B9.additionalDeclarations preserve=yes
//## end module%3F39224B03B9.additionalDeclarations


// Class cStateVariable 


cStateVariable::cStateVariable()
  //## begin cStateVariable::cStateVariable%.hasinit preserve=no
      : _State(NULL)
  //## end cStateVariable::cStateVariable%.hasinit
  //## begin cStateVariable::cStateVariable%.initialization preserve=yes
  //## end cStateVariable::cStateVariable%.initialization
{
  //## begin cStateVariable::cStateVariable%.body preserve=yes
_ASSERT_UNCOND
  //## end cStateVariable::cStateVariable%.body
}

cStateVariable::cStateVariable(const cStateVariable &right)
  //## begin cStateVariable::cStateVariable%copy.hasinit preserve=no
      : _State(NULL)
  //## end cStateVariable::cStateVariable%copy.hasinit
  //## begin cStateVariable::cStateVariable%copy.initialization preserve=yes
  //## end cStateVariable::cStateVariable%copy.initialization
{
  //## begin cStateVariable::cStateVariable%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cStateVariable::cStateVariable%copy.body
}

cStateVariable::cStateVariable (cVarDef *var_def, cControlState *state)
  //## begin cStateVariable::cStateVariable%1060709190.hasinit preserve=no
      : _State(NULL)
  //## end cStateVariable::cStateVariable%1060709190.hasinit
  //## begin cStateVariable::cStateVariable%1060709190.initialization preserve=yes
  , cVariable(var_def)
  //## end cStateVariable::cStateVariable%1060709190.initialization
{
  //## begin cStateVariable::cStateVariable%1060709190.body preserve=yes
   _State = state;
  //## end cStateVariable::cStateVariable%1060709190.body
}


cStateVariable::~cStateVariable()
{
  //## begin cStateVariable::~cStateVariable%.body preserve=yes
  //## end cStateVariable::~cStateVariable%.body
}



//## Other Operations (implementation)
ULONG_T cStateVariable::ValueSize ()
{
  //## begin cStateVariable::ValueSize%1071244257.body preserve=yes
   return 1;
  //## end cStateVariable::ValueSize%1071244257.body
}

void cStateVariable::Get (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709191.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709191.body
}

void cStateVariable::Get (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709192.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709192.body
}

void cStateVariable::Get (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709193.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709193.body
}

void cStateVariable::Get (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709194.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709194.body
}

void cStateVariable::Get (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709195.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709195.body
}

void cStateVariable::Get (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709196.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709196.body
}

void cStateVariable::Get (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709197.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709197.body
}

void cStateVariable::Get (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709198.body preserve=yes
   if (_State->Eval()) {
      value = 1;
   } else {
      value = 0;
   }
  //## end cStateVariable::Get%1060709198.body
}

void cStateVariable::Get (UCHAR_T *buf, ULONG_T buf_len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709199.body preserve=yes
  //## end cStateVariable::Get%1060709199.body
}

void cStateVariable::Get (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709200.body preserve=yes
   if (_State->Eval()) {
      value = "1";
   } else {
      value = "0";
   }
  //## end cStateVariable::Get%1060709200.body
}

void cStateVariable::Get (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1060709201.body preserve=yes
  //## end cStateVariable::Get%1060709201.body
}

void cStateVariable::Get (BUF_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1071244251.body preserve=yes
  //## end cStateVariable::Get%1071244251.body
}

void cStateVariable::Get (BUF_T &value, ULONG_T &size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
}

void cStateVariable::Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Get%1071244252.body preserve=yes
  //## end cStateVariable::Get%1071244252.body
}

void cStateVariable::Set (CHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709202.body preserve=yes
  //## end cStateVariable::Set%1060709202.body
}

void cStateVariable::Set (UCHAR_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709203.body preserve=yes
  //## end cStateVariable::Set%1060709203.body
}

void cStateVariable::Set (SHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709204.body preserve=yes
  //## end cStateVariable::Set%1060709204.body
}

void cStateVariable::Set (USHORT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709205.body preserve=yes
  //## end cStateVariable::Set%1060709205.body
}

void cStateVariable::Set (LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709206.body preserve=yes
  //## end cStateVariable::Set%1060709206.body
}

void cStateVariable::Set (ULONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709207.body preserve=yes
  //## end cStateVariable::Set%1060709207.body
}

void cStateVariable::Set (FLOAT_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709208.body preserve=yes
  //## end cStateVariable::Set%1060709208.body
}

void cStateVariable::Set (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709209.body preserve=yes
  //## end cStateVariable::Set%1060709209.body
}

void cStateVariable::Set (UCHAR_T *value, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709210.body preserve=yes
  //## end cStateVariable::Set%1060709210.body
}

void cStateVariable::Set (CHAR_T *value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709211.body preserve=yes
  //## end cStateVariable::Set%1060709211.body
}

void cStateVariable::Set (const CHAR_T *value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709212.body preserve=yes
  //## end cStateVariable::Set%1060709212.body
}

void cStateVariable::Set (WCHAR_T *value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709213.body preserve=yes
  //## end cStateVariable::Set%1060709213.body
}

void cStateVariable::Set (const WCHAR_T *value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1060709214.body preserve=yes
  //## end cStateVariable::Set%1060709214.body
}

void cStateVariable::Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::Set%1071244253.body preserve=yes
  //## end cStateVariable::Set%1071244253.body
}

void cStateVariable::GetMinimum (LONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cStateVariable::GetMinimum%1089103351.body preserve=yes
  //## end cStateVariable::GetMinimum%1089103351.body
}

void cStateVariable::GetMinimum (ULONG_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cStateVariable::GetMinimum%1089103352.body preserve=yes
  //## end cStateVariable::GetMinimum%1089103352.body
}

void cStateVariable::GetMinimum (FLOAT_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cStateVariable::GetMinimum%1089103353.body preserve=yes
  //## end cStateVariable::GetMinimum%1089103353.body
}

void cStateVariable::GetMinimum (DOUBLE_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cStateVariable::GetMinimum%1089103354.body preserve=yes
  //## end cStateVariable::GetMinimum%1089103354.body
}

void cStateVariable::GetMinimum (STRING_T &minimum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cStateVariable::GetMinimum%1089203194.body preserve=yes
  //## end cStateVariable::GetMinimum%1089203194.body
}

void cStateVariable::GetMaximum (LONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cStateVariable::GetMaximum%1089103355.body preserve=yes
  //## end cStateVariable::GetMaximum%1089103355.body
}

void cStateVariable::GetMaximum (ULONG_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, BOOL_T fixed_decimal_representation)
{
  //## begin cStateVariable::GetMaximum%1089103356.body preserve=yes
  //## end cStateVariable::GetMaximum%1089103356.body
}

void cStateVariable::GetMaximum (FLOAT_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cStateVariable::GetMaximum%1089103357.body preserve=yes
  //## end cStateVariable::GetMaximum%1089103357.body
}

void cStateVariable::GetMaximum (DOUBLE_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cStateVariable::GetMaximum%1089103358.body preserve=yes
  //## end cStateVariable::GetMaximum%1089103358.body
}

void cStateVariable::GetMaximum (STRING_T &maximum, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cStateVariable::GetMaximum%1089203195.body preserve=yes
  //## end cStateVariable::GetMaximum%1089203195.body
}

ULONG_T cStateVariable::GetObject (cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::GetObject%1238436642.body preserve=yes
   return 0;
  //## end cStateVariable::GetObject%1238436642.body
}

void cStateVariable::SetObject (const cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cStateVariable::SetObject%1238436643.body preserve=yes
  //## end cStateVariable::SetObject%1238436643.body
}

// Additional Declarations
  //## begin cStateVariable%3F39224B03B9.declarations preserve=yes
  //## end cStateVariable%3F39224B03B9.declarations

//## begin module%3F39224B03B9.epilog preserve=yes
//## end module%3F39224B03B9.epilog
