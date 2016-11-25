//## begin module%3F3CC04F0109.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3CC04F0109.cm

//## begin module%3F3CC04F0109.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3CC04F0109.cp

//## Module: cActProgram%3F3CC04F0109; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cActProgram.cpp

//## begin module%3F3CC04F0109.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F3CC04F0109.additionalIncludes

//## begin module%3F3CC04F0109.includes preserve=yes
//## end module%3F3CC04F0109.includes

// cContext
#include "System/Database/cContext.h"
// cActProcedure
#include "System/PLC/cActProcedure.h"
// cActProgram
#include "System/PLC/cActProgram.h"
// cControlProgram
#include "System/PLC/cControlProgram.h"
//## begin module%3F3CC04F0109.additionalDeclarations preserve=yes
//## end module%3F3CC04F0109.additionalDeclarations


// Class cActProgram 




cActProgram::cActProgram()
  //## begin cActProgram::cActProgram%.hasinit preserve=no
      : _Program(NULL), _ActProcedure(NULL), _Context(NULL)
  //## end cActProgram::cActProgram%.hasinit
  //## begin cActProgram::cActProgram%.initialization preserve=yes
  //## end cActProgram::cActProgram%.initialization
{
  //## begin cActProgram::cActProgram%.body preserve=yes
_ASSERT_UNCOND
  //## end cActProgram::cActProgram%.body
}

cActProgram::cActProgram(const cActProgram &right)
  //## begin cActProgram::cActProgram%copy.hasinit preserve=no
      : _Program(NULL), _ActProcedure(NULL), _Context(NULL)
  //## end cActProgram::cActProgram%copy.hasinit
  //## begin cActProgram::cActProgram%copy.initialization preserve=yes
  //## end cActProgram::cActProgram%copy.initialization
{
  //## begin cActProgram::cActProgram%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cActProgram::cActProgram%copy.body
}

cActProgram::cActProgram (cContext *context, cControlProgram *program)
  //## begin cActProgram::cActProgram%1060946835.hasinit preserve=no
      : _Program(NULL), _ActProcedure(NULL), _Context(NULL)
  //## end cActProgram::cActProgram%1060946835.hasinit
  //## begin cActProgram::cActProgram%1060946835.initialization preserve=yes
  //## end cActProgram::cActProgram%1060946835.initialization
{
  //## begin cActProgram::cActProgram%1060946835.body preserve=yes
   _Context = context;
   _Program = program;
  //## end cActProgram::cActProgram%1060946835.body
}


cActProgram::~cActProgram()
{
  //## begin cActProgram::~cActProgram%.body preserve=yes
  //## end cActProgram::~cActProgram%.body
}



//## Other Operations (implementation)
cContext * cActProgram::Context ()
{
  //## begin cActProgram::Context%1060946836.body preserve=yes
   return _Context;
  //## end cActProgram::Context%1060946836.body
}

cControlProgram * cActProgram::Program ()
{
  //## begin cActProgram::Program%1060960059.body preserve=yes
   return _Program;
  //## end cActProgram::Program%1060960059.body
}

// Additional Declarations
  //## begin cActProgram%3F3CC04F0109.declarations preserve=yes
  //## end cActProgram%3F3CC04F0109.declarations

//## begin module%3F3CC04F0109.epilog preserve=yes
//## end module%3F3CC04F0109.epilog
