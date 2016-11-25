//## begin module%3F3CC0B9001F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3CC0B9001F.cm

//## begin module%3F3CC0B9001F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3CC0B9001F.cp

//## Module: cActProcedure%3F3CC0B9001F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cActProcedure.cpp

//## begin module%3F3CC0B9001F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F3CC0B9001F.additionalIncludes

//## begin module%3F3CC0B9001F.includes preserve=yes
//## end module%3F3CC0B9001F.includes

// cContext
#include "System/Database/cContext.h"
// cActProcedure
#include "System/PLC/cActProcedure.h"
// cActProgram
#include "System/PLC/cActProgram.h"
// cActLine
#include "System/PLC/cActLine.h"
// cProcedureLine
#include "System/PLC/cProcedureLine.h"
// cControlProcedure
#include "System/PLC/cControlProcedure.h"
//## begin module%3F3CC0B9001F.additionalDeclarations preserve=yes
//## end module%3F3CC0B9001F.additionalDeclarations


// Class cActProcedure 





cActProcedure::cActProcedure()
  //## begin cActProcedure::cActProcedure%.hasinit preserve=no
      : _Procedure(NULL), _ActProgram(NULL), _ActLine(NULL), _Context(NULL)
  //## end cActProcedure::cActProcedure%.hasinit
  //## begin cActProcedure::cActProcedure%.initialization preserve=yes
  //## end cActProcedure::cActProcedure%.initialization
{
  //## begin cActProcedure::cActProcedure%.body preserve=yes
_ASSERT_UNCOND
  //## end cActProcedure::cActProcedure%.body
}

cActProcedure::cActProcedure(const cActProcedure &right)
  //## begin cActProcedure::cActProcedure%copy.hasinit preserve=no
      : _Procedure(NULL), _ActProgram(NULL), _ActLine(NULL), _Context(NULL)
  //## end cActProcedure::cActProcedure%copy.hasinit
  //## begin cActProcedure::cActProcedure%copy.initialization preserve=yes
  //## end cActProcedure::cActProcedure%copy.initialization
{
  //## begin cActProcedure::cActProcedure%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cActProcedure::cActProcedure%copy.body
}

cActProcedure::cActProcedure (cContext *context, cControlProcedure *procedure, cActProgram *act_program)
  //## begin cActProcedure::cActProcedure%1060946837.hasinit preserve=no
      : _Procedure(NULL), _ActProgram(NULL), _ActLine(NULL), _Context(NULL)
  //## end cActProcedure::cActProcedure%1060946837.hasinit
  //## begin cActProcedure::cActProcedure%1060946837.initialization preserve=yes
  //## end cActProcedure::cActProcedure%1060946837.initialization
{
  //## begin cActProcedure::cActProcedure%1060946837.body preserve=yes
   _Context = context;
   _Procedure = procedure;
  //## end cActProcedure::cActProcedure%1060946837.body
}


cActProcedure::~cActProcedure()
{
  //## begin cActProcedure::~cActProcedure%.body preserve=yes
  //## end cActProcedure::~cActProcedure%.body
}



//## Other Operations (implementation)
cContext * cActProcedure::Context ()
{
  //## begin cActProcedure::Context%1060946838.body preserve=yes
   return _Context;
  //## end cActProcedure::Context%1060946838.body
}

cControlProcedure * cActProcedure::Procedure ()
{
  //## begin cActProcedure::Procedure%1060960058.body preserve=yes
   return _Procedure;
  //## end cActProcedure::Procedure%1060960058.body
}

INT_T cActProcedure::Execute ()
{
  //## begin cActProcedure::Execute%1060965459.body preserve=yes
   cProcedureLine * first_line = _Procedure->FirstLine();
   if (first_line != NULL) {
      cActLine act_line(_Context, first_line, this);
      while (act_line.Line() != NULL) {
         printf("%s: line %d\n", Procedure()->Name().c_str(), act_line.Line()->_Line);
         act_line.Execute();
      }
   }
   return 0;
  //## end cActProcedure::Execute%1060965459.body
}

// Additional Declarations
  //## begin cActProcedure%3F3CC0B9001F.declarations preserve=yes
  //## end cActProcedure%3F3CC0B9001F.declarations

//## begin module%3F3CC0B9001F.epilog preserve=yes
//## end module%3F3CC0B9001F.epilog
