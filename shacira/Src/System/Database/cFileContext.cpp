//## begin module%4113C8220271.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4113C8220271.cm

//## begin module%4113C8220271.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4113C8220271.cp

//## Module: cFileContext%4113C8220271; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFileContext.cpp

//## begin module%4113C8220271.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4113C8220271.additionalIncludes

//## begin module%4113C8220271.includes preserve=yes
//## end module%4113C8220271.includes

// cVarDef
#include "System/Database/cVarDef.h"
// cFileVariable
#include "System/Database/cFileVariable.h"
// cFileContext
#include "System/Database/cFileContext.h"
// cDevice
#include "Control/Device/cDevice.h"
//## begin module%4113C8220271.additionalDeclarations preserve=yes
//## end module%4113C8220271.additionalDeclarations


// Class cFileContext 

cFileContext::cFileContext()
  //## begin cFileContext::cFileContext%.hasinit preserve=no
  //## end cFileContext::cFileContext%.hasinit
  //## begin cFileContext::cFileContext%.initialization preserve=yes
  //## end cFileContext::cFileContext%.initialization
{
  //## begin cFileContext::cFileContext%.body preserve=yes
  //## end cFileContext::cFileContext%.body
}

cFileContext::cFileContext(const cFileContext &right)
  //## begin cFileContext::cFileContext%copy.hasinit preserve=no
  //## end cFileContext::cFileContext%copy.hasinit
  //## begin cFileContext::cFileContext%copy.initialization preserve=yes
  //## end cFileContext::cFileContext%copy.initialization
{
  //## begin cFileContext::cFileContext%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFileContext::cFileContext%copy.body
}


cFileContext::~cFileContext()
{
  //## begin cFileContext::~cFileContext%.body preserve=yes
  //## end cFileContext::~cFileContext%.body
}



//## Other Operations (implementation)
BOOL_T cFileContext::IsRemote ()
{
  //## begin cFileContext::IsRemote%1091815615.body preserve=yes
   return false;
  //## end cFileContext::IsRemote%1091815615.body
}

void cFileContext::Create ()
{
  //## begin cFileContext::Create%1091815619.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      STRING_T var_name = var_def->_VarName;
      cVariable * variable = new cFileVariable(var_def);
      var_def->_Variable = variable;
      i++;
   }
  //## end cFileContext::Create%1091815619.body
}

void cFileContext::CreateDynamic ()
{
  //## begin cFileContext::CreateDynamic%1091815620.body preserve=yes
  //## end cFileContext::CreateDynamic%1091815620.body
}

ULONG_T cFileContext::GetVarDefs (STRING_T &var_defs, ULONG_T if_type)
{
  //## begin cFileContext::GetVarDefs%1091815621.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      STRING_T var_spec;
      var_def->Unparse(var_spec, IGN_VALUES|IGN_UNIT_TEXT);
      var_defs += var_spec.c_str();
      i++;
   }
   return var_defs.size();
  //## end cFileContext::GetVarDefs%1091815621.body
}

// Additional Declarations
  //## begin cFileContext%4113C8220271.declarations preserve=yes
  //## end cFileContext%4113C8220271.declarations

//## begin module%4113C8220271.epilog preserve=yes
//## end module%4113C8220271.epilog
