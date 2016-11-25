//## begin module%3AB6251201D9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB6251201D9.cm

//## begin module%3AB6251201D9.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3AB6251201D9.cp

//## Module: cStandardProgram%3AB6251201D9; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cStandardProgram.cpp

//## begin module%3AB6251201D9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AB6251201D9.additionalIncludes

//## begin module%3AB6251201D9.includes preserve=yes
//## end module%3AB6251201D9.includes

// cContext
#include "System/Database/cContext.h"
// cCell
#include "Control/Cell/cCell.h"
// cStandardProgram
#include "Control/Cell/Programs/cStandardProgram.h"
//## begin module%3AB6251201D9.additionalDeclarations preserve=yes
//## end module%3AB6251201D9.additionalDeclarations


// Class cStandardProgram 

cStandardProgram::cStandardProgram()
  //## begin cStandardProgram::cStandardProgram%.hasinit preserve=no
  //## end cStandardProgram::cStandardProgram%.hasinit
  //## begin cStandardProgram::cStandardProgram%.initialization preserve=yes
  //## end cStandardProgram::cStandardProgram%.initialization
{
  //## begin cStandardProgram::cStandardProgram%.body preserve=yes
_ASSERT_UNCOND
  //## end cStandardProgram::cStandardProgram%.body
}

cStandardProgram::cStandardProgram(const cStandardProgram &right)
  //## begin cStandardProgram::cStandardProgram%copy.hasinit preserve=no
  //## end cStandardProgram::cStandardProgram%copy.hasinit
  //## begin cStandardProgram::cStandardProgram%copy.initialization preserve=yes
  //## end cStandardProgram::cStandardProgram%copy.initialization
{
  //## begin cStandardProgram::cStandardProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cStandardProgram::cStandardProgram%copy.body
}

cStandardProgram::cStandardProgram (cCell *cell, cConfigurationObject *config_obj)
  //## begin cStandardProgram::cStandardProgram%985080213.hasinit preserve=no
  //## end cStandardProgram::cStandardProgram%985080213.hasinit
  //## begin cStandardProgram::cStandardProgram%985080213.initialization preserve=yes
  : cProgram(cell, config_obj)
  //## end cStandardProgram::cStandardProgram%985080213.initialization
{
  //## begin cStandardProgram::cStandardProgram%985080213.body preserve=yes
_ASSERT_COND(cell != NULL)
_ASSERT_COND(config_obj != NULL)
   _Cell = cell;
  //## end cStandardProgram::cStandardProgram%985080213.body
}


cStandardProgram::~cStandardProgram()
{
  //## begin cStandardProgram::~cStandardProgram%.body preserve=yes
  //## end cStandardProgram::~cStandardProgram%.body
}



//## Other Operations (implementation)
BOOL_T cStandardProgram::Start ()
{
  //## begin cStandardProgram::Start%1047387660.body preserve=yes
	return true;
  //## end cStandardProgram::Start%1047387660.body
}

BOOL_T cStandardProgram::Stop ()
{
  //## begin cStandardProgram::Stop%1047387661.body preserve=yes
	return true;
  //## end cStandardProgram::Stop%1047387661.body
}

void cStandardProgram::ProcessEvent (cTransientObject *object)
{
  //## begin cStandardProgram::ProcessEvent%1047387662.body preserve=yes
  //## end cStandardProgram::ProcessEvent%1047387662.body
}

// Additional Declarations
  //## begin cStandardProgram%3AB6251201D9.declarations preserve=yes
  //## end cStandardProgram%3AB6251201D9.declarations

//## begin module%3AB6251201D9.epilog preserve=yes
//## end module%3AB6251201D9.epilog
