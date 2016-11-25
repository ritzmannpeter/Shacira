//## begin module%43808080026C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43808080026C.cm

//## begin module%43808080026C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43808080026C.cp

//## Module: cSetCmd%43808080026C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cSetCmd.cpp

//## begin module%43808080026C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43808080026C.additionalIncludes

//## begin module%43808080026C.includes preserve=yes
//## end module%43808080026C.includes

// cSetCmd
#include "Control/Device/EM63/cSetCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%43808080026C.additionalDeclarations preserve=yes
//## end module%43808080026C.additionalDeclarations


// Class cSetCmd 



cSetCmd::cSetCmd()
  //## begin cSetCmd::cSetCmd%.hasinit preserve=no
  //## end cSetCmd::cSetCmd%.hasinit
  //## begin cSetCmd::cSetCmd%.initialization preserve=yes
  //## end cSetCmd::cSetCmd%.initialization
{
  //## begin cSetCmd::cSetCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cSetCmd::cSetCmd%.body
}

cSetCmd::cSetCmd(const cSetCmd &right)
  //## begin cSetCmd::cSetCmd%copy.hasinit preserve=no
  //## end cSetCmd::cSetCmd%copy.hasinit
  //## begin cSetCmd::cSetCmd%copy.initialization preserve=yes
  //## end cSetCmd::cSetCmd%copy.initialization
{
  //## begin cSetCmd::cSetCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSetCmd::cSetCmd%copy.body
}

cSetCmd::cSetCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cSetCmd::cSetCmd%1136548771.hasinit preserve=no
  //## end cSetCmd::cSetCmd%1136548771.hasinit
  //## begin cSetCmd::cSetCmd%1136548771.initialization preserve=yes
  : cPresentationCmd(job, command_name)
  //## end cSetCmd::cSetCmd%1136548771.initialization
{
  //## begin cSetCmd::cSetCmd%1136548771.body preserve=yes
   _CommandType = EM63_SET_COMMAND;
   INCREMENT_OBJECT_COUNT()
   //## end cSetCmd::cSetCmd%1136548771.body
}


cSetCmd::~cSetCmd()
{
  //## begin cSetCmd::~cSetCmd%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cSetCmd::~cSetCmd%.body
}



//## Other Operations (implementation)
BOOL_T cSetCmd::Process (cContext *context)
{
  //## begin cSetCmd::Process%1135093199.body preserve=yes
   BOOL_T success = true;
   _Context = context;
   if (_Interface->ParamExists(_ParamId.c_str())) {
      if (!_Interface->ParamIsWriteable(_ParamId.c_str())) {
         Failed(SET_DENIED, _ParamId.c_str());
         success = false;
      }
   } else {
      Failed(UNKNOWN_SET_PARAMETER, _ParamId.c_str());
      success = false;
   }
   if (!success) {
      Terminated();
   }
   return success;
  //## end cSetCmd::Process%1135093199.body
}

BOOL_T cSetCmd::Start ()
{
  //## begin cSetCmd::Start%1135093200.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsStarted()) {
      Started();
      int err = _Interface->SetParamValue(_ParamId.c_str(), _ParamValue.c_str());
      Terminated();
      if (err == 0) {
         return true;
      } else {
         int err_code = _Interface->ParamError(err);
         Failed(err_code, _ParamId.c_str());
         return false;
      }
   } else {
      return false;
   }
  //## end cSetCmd::Start%1135093200.body
}

void cSetCmd::Stop ()
{
  //## begin cSetCmd::Stop%1135093201.body preserve=yes
  //## end cSetCmd::Stop%1135093201.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cSetCmd::get_ParamId () const
{
  //## begin cSetCmd::get_ParamId%43B2872400F1.get preserve=no
  return _ParamId;
  //## end cSetCmd::get_ParamId%43B2872400F1.get
}

void cSetCmd::set_ParamId (STRING_T value)
{
  //## begin cSetCmd::set_ParamId%43B2872400F1.set preserve=no
  _ParamId = value;
  //## end cSetCmd::set_ParamId%43B2872400F1.set
}

STRING_T cSetCmd::get_ParamValue () const
{
  //## begin cSetCmd::get_ParamValue%43B287420016.get preserve=no
  return _ParamValue;
  //## end cSetCmd::get_ParamValue%43B287420016.get
}

void cSetCmd::set_ParamValue (STRING_T value)
{
  //## begin cSetCmd::set_ParamValue%43B287420016.set preserve=no
  _ParamValue = value;
  //## end cSetCmd::set_ParamValue%43B287420016.set
}

// Additional Declarations
  //## begin cSetCmd%43808080026C.declarations preserve=yes
  //## end cSetCmd%43808080026C.declarations

//## begin module%43808080026C.epilog preserve=yes
//## end module%43808080026C.epilog
