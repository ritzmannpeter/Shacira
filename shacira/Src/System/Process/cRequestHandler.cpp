//## begin module%43141D1003BE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43141D1003BE.cm

//## begin module%43141D1003BE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43141D1003BE.cp

//## Module: cRequestHandler%43141D1003BE; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cRequestHandler.cpp

//## begin module%43141D1003BE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43141D1003BE.additionalIncludes

//## begin module%43141D1003BE.includes preserve=yes
//## end module%43141D1003BE.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cRequestHandler
#include "System/Process/cRequestHandler.h"
//## begin module%43141D1003BE.additionalDeclarations preserve=yes
//## end module%43141D1003BE.additionalDeclarations


// Class cRequestHandler 




cRequestHandler::cRequestHandler()
  //## begin cRequestHandler::cRequestHandler%.hasinit preserve=no
      : _Type(0), _Process(NULL)
  //## end cRequestHandler::cRequestHandler%.hasinit
  //## begin cRequestHandler::cRequestHandler%.initialization preserve=yes
  //## end cRequestHandler::cRequestHandler%.initialization
{
  //## begin cRequestHandler::cRequestHandler%.body preserve=yes
  //## end cRequestHandler::cRequestHandler%.body
}

cRequestHandler::cRequestHandler(const cRequestHandler &right)
  //## begin cRequestHandler::cRequestHandler%copy.hasinit preserve=no
      : _Type(0), _Process(NULL)
  //## end cRequestHandler::cRequestHandler%copy.hasinit
  //## begin cRequestHandler::cRequestHandler%copy.initialization preserve=yes
  //## end cRequestHandler::cRequestHandler%copy.initialization
{
  //## begin cRequestHandler::cRequestHandler%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cRequestHandler::cRequestHandler%copy.body
}

cRequestHandler::cRequestHandler (cSHProcess *process, CONST_STRING_T handler_name)
  //## begin cRequestHandler::cRequestHandler%1125391950.hasinit preserve=no
      : _Type(0), _Process(NULL)
  //## end cRequestHandler::cRequestHandler%1125391950.hasinit
  //## begin cRequestHandler::cRequestHandler%1125391950.initialization preserve=yes
  //## end cRequestHandler::cRequestHandler%1125391950.initialization
{
  //## begin cRequestHandler::cRequestHandler%1125391950.body preserve=yes
_ASSERT_COND(_Process == NULL)
   _Process = process;
   _Name = handler_name;
  //## end cRequestHandler::cRequestHandler%1125391950.body
}


cRequestHandler::~cRequestHandler()
{
  //## begin cRequestHandler::~cRequestHandler%.body preserve=yes
  //## end cRequestHandler::~cRequestHandler%.body
}


//## Get and Set Operations for Class Attributes (implementation)

STRING_T cRequestHandler::get_Name () const
{
  //## begin cRequestHandler::get_Name%43141EB1032D.get preserve=no
  return _Name;
  //## end cRequestHandler::get_Name%43141EB1032D.get
}

void cRequestHandler::set_Name (STRING_T value)
{
  //## begin cRequestHandler::set_Name%43141EB1032D.set preserve=no
  _Name = value;
  //## end cRequestHandler::set_Name%43141EB1032D.set
}

UCHAR_T cRequestHandler::get_Type () const
{
  //## begin cRequestHandler::get_Type%43141ECD030E.get preserve=no
  return _Type;
  //## end cRequestHandler::get_Type%43141ECD030E.get
}

void cRequestHandler::set_Type (UCHAR_T value)
{
  //## begin cRequestHandler::set_Type%43141ECD030E.set preserve=no
  _Type = value;
  //## end cRequestHandler::set_Type%43141ECD030E.set
}

// Additional Declarations
  //## begin cRequestHandler%43141D1003BE.declarations preserve=yes
  //## end cRequestHandler%43141D1003BE.declarations

//## begin module%43141D1003BE.epilog preserve=yes
//## end module%43141D1003BE.epilog
