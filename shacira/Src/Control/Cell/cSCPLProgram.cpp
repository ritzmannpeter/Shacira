//## begin module%40F919FC035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40F919FC035B.cm

//## begin module%40F919FC035B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40F919FC035B.cp

//## Module: cSCPLProgram%40F919FC035B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cSCPLProgram.cpp

//## begin module%40F919FC035B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%40F919FC035B.additionalIncludes

//## begin module%40F919FC035B.includes preserve=yes
//## end module%40F919FC035B.includes

// cContext
#include "System/Database/cContext.h"
// cControlProcedure
#include "System/PLC/cControlProcedure.h"
// cSCPLProgram
#include "Control/Cell/cSCPLProgram.h"
//## begin module%40F919FC035B.additionalDeclarations preserve=yes
//## end module%40F919FC035B.additionalDeclarations


// Class cSCPLProgram 

cSCPLProgram::cSCPLProgram()
  //## begin cSCPLProgram::cSCPLProgram%.hasinit preserve=no
  //## end cSCPLProgram::cSCPLProgram%.hasinit
  //## begin cSCPLProgram::cSCPLProgram%.initialization preserve=yes
  //## end cSCPLProgram::cSCPLProgram%.initialization
{
  //## begin cSCPLProgram::cSCPLProgram%.body preserve=yes
  //## end cSCPLProgram::cSCPLProgram%.body
}

cSCPLProgram::cSCPLProgram(const cSCPLProgram &right)
  //## begin cSCPLProgram::cSCPLProgram%copy.hasinit preserve=no
  //## end cSCPLProgram::cSCPLProgram%copy.hasinit
  //## begin cSCPLProgram::cSCPLProgram%copy.initialization preserve=yes
  //## end cSCPLProgram::cSCPLProgram%copy.initialization
{
  //## begin cSCPLProgram::cSCPLProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSCPLProgram::cSCPLProgram%copy.body
}

cSCPLProgram::cSCPLProgram (cConfigurationObject *config_obj, cContext *context)
  //## begin cSCPLProgram::cSCPLProgram%1090067122.hasinit preserve=no
  //## end cSCPLProgram::cSCPLProgram%1090067122.hasinit
  //## begin cSCPLProgram::cSCPLProgram%1090067122.initialization preserve=yes
  : cProgram(config_obj, context)
  //## end cSCPLProgram::cSCPLProgram%1090067122.initialization
{
  //## begin cSCPLProgram::cSCPLProgram%1090067122.body preserve=yes
  //## end cSCPLProgram::cSCPLProgram%1090067122.body
}


cSCPLProgram::~cSCPLProgram()
{
  //## begin cSCPLProgram::~cSCPLProgram%.body preserve=yes
  //## end cSCPLProgram::~cSCPLProgram%.body
}



//## Other Operations (implementation)
void cSCPLProgram::LoadProgram (CONST_STRING_T source)
{
  //## begin cSCPLProgram::LoadProgram%1090067123.body preserve=yes
   _Context->ParseProgramFromString(source);
  //## end cSCPLProgram::LoadProgram%1090067123.body
}

cControlProcedure * cSCPLProgram::Procedure (CONST_STRING_T name)
{
  //## begin cSCPLProgram::Procedure%1090067638.body preserve=yes
   return _Context->Procedure(name);
  //## end cSCPLProgram::Procedure%1090067638.body
}

// Additional Declarations
  //## begin cSCPLProgram%40F919FC035B.declarations preserve=yes
  //## end cSCPLProgram%40F919FC035B.declarations

//## begin module%40F919FC035B.epilog preserve=yes
//## end module%40F919FC035B.epilog
