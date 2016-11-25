//## begin module%41E6A80D000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41E6A80D000F.cm

//## begin module%41E6A80D000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41E6A80D000F.cp

//## Module: cCustomFunctions%41E6A80D000F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\cCustomFunctions.cpp

//## begin module%41E6A80D000F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41E6A80D000F.additionalIncludes

//## begin module%41E6A80D000F.includes preserve=yes
//## end module%41E6A80D000F.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"
//## begin module%41E6A80D000F.additionalDeclarations preserve=yes
//## end module%41E6A80D000F.additionalDeclarations


// Class cCustomFunctions 

//## begin cCustomFunctions::GUIFuncFactoryAddress%41E6BACC01B5.attr preserve=no  implementation: static FUNC_FACTORY_T {U} NULL
FUNC_FACTORY_T cCustomFunctions::_GUIFuncFactoryAddress = NULL;
//## end cCustomFunctions::GUIFuncFactoryAddress%41E6BACC01B5.attr

//## begin cCustomFunctions::GUIInitFuncAddress%41E6BB05004E.attr preserve=no  implementation: static GUI_INIT_FUNC_T {U} NULL
GUI_INIT_FUNC_T cCustomFunctions::_GUIInitFuncAddress = NULL;
//## end cCustomFunctions::GUIInitFuncAddress%41E6BB05004E.attr

//## begin cCustomFunctions::MdlFuncFactoryAddress%41E6BB17036B.attr preserve=no  implementation: static FUNC_FACTORY_T {U} NULL
FUNC_FACTORY_T cCustomFunctions::_MdlFuncFactoryAddress = NULL;
//## end cCustomFunctions::MdlFuncFactoryAddress%41E6BB17036B.attr

//## begin cCustomFunctions::MdlInitFuncAddress%41E6BB2A0196.attr preserve=no  implementation: static MDL_INIT_FUNC_T {U} NULL
MDL_INIT_FUNC_T cCustomFunctions::_MdlInitFuncAddress = NULL;
//## end cCustomFunctions::MdlInitFuncAddress%41E6BB2A0196.attr

//## begin cCustomFunctions::GetCustomTextFuncAddress%41E6BB3F01D4.attr preserve=no  implementation: static GET_CUSTOM_TEXT_FUNC_T {U} NULL
GET_CUSTOM_TEXT_FUNC_T cCustomFunctions::_GetCustomTextFuncAddress = NULL;
//## end cCustomFunctions::GetCustomTextFuncAddress%41E6BB3F01D4.attr

//## begin cCustomFunctions::DeviceCreatorFuncAddress%41E6BB5601D4.attr preserve=no  implementation: static DEV_FACTORY_T {U} NULL
DEV_FACTORY_T cCustomFunctions::_DeviceCreatorFuncAddress = NULL;
//## end cCustomFunctions::DeviceCreatorFuncAddress%41E6BB5601D4.attr

//## begin cCustomFunctions::ProgramCreatorFuncAddress%41E6BB6C029F.attr preserve=no  implementation: static PROG_FACTORY_T {U} NULL
PROG_FACTORY_T cCustomFunctions::_ProgramCreatorFuncAddress = NULL;
//## end cCustomFunctions::ProgramCreatorFuncAddress%41E6BB6C029F.attr

//## begin cCustomFunctions::ShareAppframeFuncAddress%41EE621F03C8.attr preserve=no  implementation: static SHARE_APPFRAME_FUNC_T {U} NULL
SHARE_APPFRAME_FUNC_T cCustomFunctions::_ShareAppframeFuncAddress = NULL;
//## end cCustomFunctions::ShareAppframeFuncAddress%41EE621F03C8.attr

//## begin cCustomFunctions::ConstructObjectFuncAddress%43108B3B0216.attr preserve=no  implementation: static OBJECT_FACTORY_T {U} NULL
OBJECT_FACTORY_T cCustomFunctions::_ConstructObjectFuncAddress = NULL;
//## end cCustomFunctions::ConstructObjectFuncAddress%43108B3B0216.attr

//## begin cCustomFunctions::VarDefFilterFuncAddress%43875E930025.attr preserve=no  implementation: static VARDEF_FILTER_T {U} NULL
VARDEF_FILTER_T cCustomFunctions::_VarDefFilterFuncAddress = NULL;
//## end cCustomFunctions::VarDefFilterFuncAddress%43875E930025.attr

cCustomFunctions::cCustomFunctions()
  //## begin cCustomFunctions::cCustomFunctions%.hasinit preserve=no
  //## end cCustomFunctions::cCustomFunctions%.hasinit
  //## begin cCustomFunctions::cCustomFunctions%.initialization preserve=yes
  //## end cCustomFunctions::cCustomFunctions%.initialization
{
  //## begin cCustomFunctions::cCustomFunctions%.body preserve=yes
  //## end cCustomFunctions::cCustomFunctions%.body
}

cCustomFunctions::cCustomFunctions(const cCustomFunctions &right)
  //## begin cCustomFunctions::cCustomFunctions%copy.hasinit preserve=no
  //## end cCustomFunctions::cCustomFunctions%copy.hasinit
  //## begin cCustomFunctions::cCustomFunctions%copy.initialization preserve=yes
  //## end cCustomFunctions::cCustomFunctions%copy.initialization
{
  //## begin cCustomFunctions::cCustomFunctions%copy.body preserve=yes
  //## end cCustomFunctions::cCustomFunctions%copy.body
}


cCustomFunctions::~cCustomFunctions()
{
  //## begin cCustomFunctions::~cCustomFunctions%.body preserve=yes
  //## end cCustomFunctions::~cCustomFunctions%.body
}



//## Other Operations (implementation)
FUNC_FACTORY_T cCustomFunctions::GUIFuncFactoryAddress ()
{
  //## begin cCustomFunctions::GUIFuncFactoryAddress%1105635916.body preserve=yes
   return _GUIFuncFactoryAddress;
  //## end cCustomFunctions::GUIFuncFactoryAddress%1105635916.body
}

GUI_INIT_FUNC_T cCustomFunctions::GUIInitFuncAddress ()
{
  //## begin cCustomFunctions::GUIInitFuncAddress%1105635917.body preserve=yes
   return _GUIInitFuncAddress;
  //## end cCustomFunctions::GUIInitFuncAddress%1105635917.body
}

FUNC_FACTORY_T cCustomFunctions::MdlFuncFactoryAddress ()
{
  //## begin cCustomFunctions::MdlFuncFactoryAddress%1105635918.body preserve=yes
   return _MdlFuncFactoryAddress;
  //## end cCustomFunctions::MdlFuncFactoryAddress%1105635918.body
}

MDL_INIT_FUNC_T cCustomFunctions::MdlInitFuncAddress ()
{
  //## begin cCustomFunctions::MdlInitFuncAddress%1105635919.body preserve=yes
   return _MdlInitFuncAddress;
  //## end cCustomFunctions::MdlInitFuncAddress%1105635919.body
}

GET_CUSTOM_TEXT_FUNC_T cCustomFunctions::GetCustomTextFuncAddress ()
{
  //## begin cCustomFunctions::GetCustomTextFuncAddress%1105635920.body preserve=yes
   return _GetCustomTextFuncAddress;
  //## end cCustomFunctions::GetCustomTextFuncAddress%1105635920.body
}

DEV_FACTORY_T cCustomFunctions::DeviceCreatorFuncAddress ()
{
  //## begin cCustomFunctions::DeviceCreatorFuncAddress%1105635921.body preserve=yes
   return _DeviceCreatorFuncAddress;
  //## end cCustomFunctions::DeviceCreatorFuncAddress%1105635921.body
}

PROG_FACTORY_T cCustomFunctions::ProgramCreatorFuncAddress ()
{
  //## begin cCustomFunctions::ProgramCreatorFuncAddress%1105635922.body preserve=yes
   return _ProgramCreatorFuncAddress;
  //## end cCustomFunctions::ProgramCreatorFuncAddress%1105635922.body
}

SHARE_APPFRAME_FUNC_T cCustomFunctions::ShareAppframeFuncAddress ()
{
  //## begin cCustomFunctions::ShareAppframeFuncAddress%1106141849.body preserve=yes
   return _ShareAppframeFuncAddress;
  //## end cCustomFunctions::ShareAppframeFuncAddress%1106141849.body
}

OBJECT_FACTORY_T cCustomFunctions::ConstructObjectFuncAddress ()
{
  //## begin cCustomFunctions::ConstructObjectFuncAddress%1125156841.body preserve=yes
   return _ConstructObjectFuncAddress;
  //## end cCustomFunctions::ConstructObjectFuncAddress%1125156841.body
}

VARDEF_FILTER_T cCustomFunctions::VarDefFilterFuncAddress ()
{
  //## begin cCustomFunctions::VarDefFilterFuncAddress%1132945090.body preserve=yes
   return _VarDefFilterFuncAddress;
  //## end cCustomFunctions::VarDefFilterFuncAddress%1132945090.body
}

void cCustomFunctions::GUIFuncFactoryAddress (FUNC_FACTORY_T address)
{
  //## begin cCustomFunctions::GUIFuncFactoryAddress%1105635923.body preserve=yes
   _GUIFuncFactoryAddress = address;
  //## end cCustomFunctions::GUIFuncFactoryAddress%1105635923.body
}

void cCustomFunctions::GUIInitFuncAddress (GUI_INIT_FUNC_T address)
{
  //## begin cCustomFunctions::GUIInitFuncAddress%1105635924.body preserve=yes
   _GUIInitFuncAddress = address;
  //## end cCustomFunctions::GUIInitFuncAddress%1105635924.body
}

void cCustomFunctions::MdlFuncFactoryAddress (FUNC_FACTORY_T address)
{
  //## begin cCustomFunctions::MdlFuncFactoryAddress%1105635925.body preserve=yes
   _MdlFuncFactoryAddress = address;
  //## end cCustomFunctions::MdlFuncFactoryAddress%1105635925.body
}

void cCustomFunctions::MdlInitFuncAddress (MDL_INIT_FUNC_T address)
{
  //## begin cCustomFunctions::MdlInitFuncAddress%1105635926.body preserve=yes
   _MdlInitFuncAddress = address;
  //## end cCustomFunctions::MdlInitFuncAddress%1105635926.body
}

void cCustomFunctions::GetCustomTextFuncAddress (GET_CUSTOM_TEXT_FUNC_T address)
{
  //## begin cCustomFunctions::GetCustomTextFuncAddress%1105635927.body preserve=yes
   _GetCustomTextFuncAddress = address;
  //## end cCustomFunctions::GetCustomTextFuncAddress%1105635927.body
}

void cCustomFunctions::DeviceCreatorFuncAddress (DEV_FACTORY_T address)
{
  //## begin cCustomFunctions::DeviceCreatorFuncAddress%1105635928.body preserve=yes
   _DeviceCreatorFuncAddress = address;
  //## end cCustomFunctions::DeviceCreatorFuncAddress%1105635928.body
}

void cCustomFunctions::ProgramCreatorFuncAddress (PROG_FACTORY_T address)
{
  //## begin cCustomFunctions::ProgramCreatorFuncAddress%1105635929.body preserve=yes
   _ProgramCreatorFuncAddress = address;
  //## end cCustomFunctions::ProgramCreatorFuncAddress%1105635929.body
}

void cCustomFunctions::ShareAppframeFuncAddress (SHARE_APPFRAME_FUNC_T address)
{
  //## begin cCustomFunctions::ShareAppframeFuncAddress%1106141850.body preserve=yes
   _ShareAppframeFuncAddress = address;
  //## end cCustomFunctions::ShareAppframeFuncAddress%1106141850.body
}

void cCustomFunctions::ConstructObjectFuncAddress (OBJECT_FACTORY_T address)
{
  //## begin cCustomFunctions::ConstructObjectFuncAddress%1125156842.body preserve=yes
   _ConstructObjectFuncAddress = address;
  //## end cCustomFunctions::ConstructObjectFuncAddress%1125156842.body
}

void cCustomFunctions::VarDefFilterFuncAddress (VARDEF_FILTER_T address)
{
  //## begin cCustomFunctions::VarDefFilterFuncAddress%1132945091.body preserve=yes
   _VarDefFilterFuncAddress = address;
  //## end cCustomFunctions::VarDefFilterFuncAddress%1132945091.body
}

// Additional Declarations
  //## begin cCustomFunctions%41E6A80D000F.declarations preserve=yes
  //## end cCustomFunctions%41E6A80D000F.declarations

//## begin module%41E6A80D000F.epilog preserve=yes
//## end module%41E6A80D000F.epilog
