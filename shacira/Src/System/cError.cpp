//## begin module%39AB9829007C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%39AB9829007C.cm

//## begin module%39AB9829007C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%39AB9829007C.cp

//## Module: cError%39AB9829007C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cError.cpp

//## begin module%39AB9829007C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%39AB9829007C.additionalIncludes

//## begin module%39AB9829007C.includes preserve=yes
#include "safefunctions.h"
//## end module%39AB9829007C.includes

// cStringUtils
#include "System/cStringUtils.h"
// cError
#include "System/cError.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
// cText
#include "System/Text/cText.h"
//## begin module%39AB9829007C.additionalDeclarations preserve=yes
//## end module%39AB9829007C.additionalDeclarations


// Class cError 










cError::cError()
  //## begin cError::cError%.hasinit preserve=no
      : _ErrCode(0), _NativeCode(0), _Params(0)
  //## end cError::cError%.hasinit
  //## begin cError::cError%.initialization preserve=yes
  //## end cError::cError%.initialization
{
  //## begin cError::cError%.body preserve=yes
   _ErrCode = 0;
   _NativeCode = 0;
   _Params = 0;
  //## end cError::cError%.body
}

cError::cError(const cError &right)
  //## begin cError::cError%copy.hasinit preserve=no
      : _ErrCode(0), _NativeCode(0), _Params(0)
  //## end cError::cError%copy.hasinit
  //## begin cError::cError%copy.initialization preserve=yes
  //## end cError::cError%copy.initialization
{
  //## begin cError::cError%copy.body preserve=yes
   _ErrCode = right._ErrCode;
   _Text = right._Text;
   _NativeCode = right._NativeCode;
   _Params = right._Params;
   _Param1 = right._Param1;
   _Param2 = right._Param2;
   _Param3 = right._Param3;
   _Param4 = right._Param4;
  //## end cError::cError%copy.body
}

cError::cError (LONG_T text_id, LONG_T native_code, CONST_STRING_T param1, CONST_STRING_T param2, CONST_STRING_T param3, CONST_STRING_T param4)
  //## begin cError::cError%967547765.hasinit preserve=no
      : _ErrCode(0), _NativeCode(0), _Params(0)
  //## end cError::cError%967547765.hasinit
  //## begin cError::cError%967547765.initialization preserve=yes
  //## end cError::cError%967547765.initialization
{
  //## begin cError::cError%967547765.body preserve=yes
   if (text_id == 0) {
      // this is a concession to the current usage of cError
      // and should be eliminated some time
      if (param1 != 0) {
         _Text = param1;
      }
   } else if (text_id > 0) {
      _ErrCode = -text_id;
   } else {
      _ErrCode = text_id;
   }
   _NativeCode = native_code;
   _Params = 0;
   if (param1 != NULL) {
      _Param1 = param1;
      _Params = 1;
   }
   if (param2 != NULL) {
      _Param2 = param2;
      _Params = 2;
   }
   if (param3 != NULL) {
      _Param3 = param3;
      _Params = 3;
   }
   if (param4 != NULL) {
      _Param4 = param4;
      _Params = 4;
   }
  //## end cError::cError%967547765.body
}

cError::cError (STRING_T text, LONG_T native_code, CONST_STRING_T param1, CONST_STRING_T param2, CONST_STRING_T param3, CONST_STRING_T param4)
  //## begin cError::cError%1111566664.hasinit preserve=no
      : _ErrCode(0), _NativeCode(0), _Params(0)
  //## end cError::cError%1111566664.hasinit
  //## begin cError::cError%1111566664.initialization preserve=yes
  //## end cError::cError%1111566664.initialization
{
  //## begin cError::cError%1111566664.body preserve=yes
   _Text = text;
   _NativeCode = native_code;
   _Params = 0;
   if (param1 != NULL) {
      _Param1 = param1;
      _Params = 1;
   }
   if (param2 != NULL) {
      _Param2 = param2;
      _Params = 2;
   }
   if (param3 != NULL) {
      _Param3 = param3;
      _Params = 3;
   }
   if (param4 != NULL) {
      _Param4 = param4;
      _Params = 4;
   }
  //## end cError::cError%1111566664.body
}


cError::~cError()
{
  //## begin cError::~cError%.body preserve=yes
  //## end cError::~cError%.body
}



//## Other Operations (implementation)
ULONG_T cError::TextIndex ()
{
  //## begin cError::TextIndex%1093344841.body preserve=yes
   if (_ErrCode < 0) {
      return -_ErrCode;
   } else {
      return _ErrCode;
   }
  //## end cError::TextIndex%1093344841.body
}

STRING_T cError::ErrMsg ()
{
  //## begin cError::ErrMsg%1014996956.body preserve=yes
   // temporal solution
   STRING_T msg;
   if (_ErrCode == 0) {
      msg = _Text;
   } else {
      msg = cText::GetText(-_ErrCode);
   }
   STRING_T msg_text = SubstParams(msg.c_str());
   if (_NativeCode != 0) {
      char native_code[0x50] = {0};
      SafePrintf(native_code, sizeof(native_code), " : %d", _NativeCode);
      msg_text += native_code;
   }
   return msg_text;
  //## end cError::ErrMsg%1014996956.body
}

cError::operator CONST_STRING_T ()
{
  //## begin cError::operator CONST_STRING_T%989323343.body preserve=yes
   _MsgText = ErrMsg();
   return _MsgText.c_str();
  //## end cError::operator CONST_STRING_T%989323343.body
}

STRING_T cError::SubstParams (CONST_STRING_T text)
{
  //## begin cError::SubstParams%1014996957.body preserve=yes
   STRING_T new_text = text;
   char native_code[32] = {0};
   ltoa(_NativeCode, native_code, 10);
   new_text = cStringUtils::Replace(new_text, "#0", native_code);
   new_text = cStringUtils::Replace(new_text, "#1", _Param1.c_str());
   new_text = cStringUtils::Replace(new_text, "#2", _Param2.c_str());
   new_text = cStringUtils::Replace(new_text, "#3", _Param3.c_str());
   new_text = cStringUtils::Replace(new_text, "#4", _Param4.c_str());
   return new_text;
  //## end cError::SubstParams%1014996957.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cError::get_ErrCode () const
{
  //## begin cError::get_ErrCode%39ABB5A40088.get preserve=no
  return _ErrCode;
  //## end cError::get_ErrCode%39ABB5A40088.get
}

void cError::set_ErrCode (INT_T value)
{
  //## begin cError::set_ErrCode%39ABB5A40088.set preserve=no
  _ErrCode = value;
  //## end cError::set_ErrCode%39ABB5A40088.set
}

LONG_T cError::get_NativeCode () const
{
  //## begin cError::get_NativeCode%3A914EC7003F.get preserve=no
  return _NativeCode;
  //## end cError::get_NativeCode%3A914EC7003F.get
}

void cError::set_NativeCode (LONG_T value)
{
  //## begin cError::set_NativeCode%3A914EC7003F.set preserve=no
  _NativeCode = value;
  //## end cError::set_NativeCode%3A914EC7003F.set
}

STRING_T cError::get_Text () const
{
  //## begin cError::get_Text%424129210109.get preserve=no
  return _Text;
  //## end cError::get_Text%424129210109.get
}

void cError::set_Text (STRING_T value)
{
  //## begin cError::set_Text%424129210109.set preserve=no
  _Text = value;
  //## end cError::set_Text%424129210109.set
}

ULONG_T cError::get_Params () const
{
  //## begin cError::get_Params%3A922DBF0094.get preserve=no
  return _Params;
  //## end cError::get_Params%3A922DBF0094.get
}

STRING_T cError::get_Param1 () const
{
  //## begin cError::get_Param1%39ABB5DF001F.get preserve=no
  return _Param1;
  //## end cError::get_Param1%39ABB5DF001F.get
}

void cError::set_Param1 (STRING_T value)
{
  //## begin cError::set_Param1%39ABB5DF001F.set preserve=no
  _Param1 = value;
  //## end cError::set_Param1%39ABB5DF001F.set
}

STRING_T cError::get_Param2 () const
{
  //## begin cError::get_Param2%3A914EFE00CA.get preserve=no
  return _Param2;
  //## end cError::get_Param2%3A914EFE00CA.get
}

void cError::set_Param2 (STRING_T value)
{
  //## begin cError::set_Param2%3A914EFE00CA.set preserve=no
  _Param2 = value;
  //## end cError::set_Param2%3A914EFE00CA.set
}

STRING_T cError::get_Param3 () const
{
  //## begin cError::get_Param3%3A914EFF0343.get preserve=no
  return _Param3;
  //## end cError::get_Param3%3A914EFF0343.get
}

void cError::set_Param3 (STRING_T value)
{
  //## begin cError::set_Param3%3A914EFF0343.set preserve=no
  _Param3 = value;
  //## end cError::set_Param3%3A914EFF0343.set
}

STRING_T cError::get_Param4 () const
{
  //## begin cError::get_Param4%3A914F010219.get preserve=no
  return _Param4;
  //## end cError::get_Param4%3A914F010219.get
}

void cError::set_Param4 (STRING_T value)
{
  //## begin cError::set_Param4%3A914F010219.set preserve=no
  _Param4 = value;
  //## end cError::set_Param4%3A914F010219.set
}

// Additional Declarations
  //## begin cError%39AB9829007C.declarations preserve=yes
  //## end cError%39AB9829007C.declarations

//## begin module%39AB9829007C.epilog preserve=yes
//## end module%39AB9829007C.epilog
