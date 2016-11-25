//## begin module%3F38BC14031C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BC14031C.cm

//## begin module%3F38BC14031C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BC14031C.cp

//## Module: cControlProcedure%3F38BC14031C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlProcedure.cpp

//## begin module%3F38BC14031C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F38BC14031C.additionalIncludes

//## begin module%3F38BC14031C.includes preserve=yes
//## end module%3F38BC14031C.includes

// cContext
#include "System/Database/cContext.h"
// cActLine
#include "System/PLC/cActLine.h"
// cProcedureLine
#include "System/PLC/cProcedureLine.h"
// cControlProcedure
#include "System/PLC/cControlProcedure.h"
//## begin module%3F38BC14031C.additionalDeclarations preserve=yes
//## end module%3F38BC14031C.additionalDeclarations


// Class cControlProcedure 






cControlProcedure::cControlProcedure()
  //## begin cControlProcedure::cControlProcedure%.hasinit preserve=no
  //## end cControlProcedure::cControlProcedure%.hasinit
  //## begin cControlProcedure::cControlProcedure%.initialization preserve=yes
  //## end cControlProcedure::cControlProcedure%.initialization
{
  //## begin cControlProcedure::cControlProcedure%.body preserve=yes
_ASSERT_UNCOND
  //## end cControlProcedure::cControlProcedure%.body
}

cControlProcedure::cControlProcedure(const cControlProcedure &right)
  //## begin cControlProcedure::cControlProcedure%copy.hasinit preserve=no
  //## end cControlProcedure::cControlProcedure%copy.hasinit
  //## begin cControlProcedure::cControlProcedure%copy.initialization preserve=yes
  //## end cControlProcedure::cControlProcedure%copy.initialization
{
  //## begin cControlProcedure::cControlProcedure%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cControlProcedure::cControlProcedure%copy.body
}

cControlProcedure::cControlProcedure (CONST_STRING_T name)
  //## begin cControlProcedure::cControlProcedure%1060779895.hasinit preserve=no
  //## end cControlProcedure::cControlProcedure%1060779895.hasinit
  //## begin cControlProcedure::cControlProcedure%1060779895.initialization preserve=yes
  //## end cControlProcedure::cControlProcedure%1060779895.initialization
{
  //## begin cControlProcedure::cControlProcedure%1060779895.body preserve=yes
   _Name = name;
  //## end cControlProcedure::cControlProcedure%1060779895.body
}


cControlProcedure::~cControlProcedure()
{
  //## begin cControlProcedure::~cControlProcedure%.body preserve=yes
   ULONG_T lines = _Lines.size();
   for (ULONG_T i=0; i<lines; i++) {
      cProcedureLine * line = _Lines[i];
      DELETE_OBJECT(cProcedureLine, line)
   }
  //## end cControlProcedure::~cControlProcedure%.body
}



//## Other Operations (implementation)
STRING_T cControlProcedure::Name ()
{
  //## begin cControlProcedure::Name%1060960060.body preserve=yes
   return _Name;
  //## end cControlProcedure::Name%1060960060.body
}

void cControlProcedure::AddLine (cProcedureLine *line)
{
  //## begin cControlProcedure::AddLine%1060779896.body preserve=yes
   int size = _Lines.size();
   _Lines.resize(size + 1);
   _Lines[size] = line;
  //## end cControlProcedure::AddLine%1060779896.body
}

INT_T cControlProcedure::Execute (cContext *context)
{
  //## begin cControlProcedure::Execute%1060849351.body preserve=yes
   int size = _Lines.size();
   if (size > 0) {
      cProcedureLine * line = _Lines[0];
      cActLine act_line(context, line, NULL);
      printf("execute %s\n", Name().c_str());
      act_line.Execute();
      printf("%s terminated\n", Name().c_str());
   }
   return 0;
  //## end cControlProcedure::Execute%1060849351.body
}

void cControlProcedure::PrintLines ()
{
  //## begin cControlProcedure::PrintLines%1060960062.body preserve=yes
   printf("procedure %s:\n", Name().c_str());
   int size = _Lines.size();
   for (int i=0; i<size; i++) {
      cProcedureLine * line = _Lines[i];
      printf("line %d (%s) ", line->_Line, line->TypeName().c_str());
      if (line->ParentLine() != NULL) {
         printf("%d ", line->ParentLine()->_Line);
      } else {
         printf("%d ", (int)-1);
      }
      if (line->CondLine() != NULL) {
         printf("%d ", line->CondLine()->_Line);
      } else {
         printf("%d ", (int)-1);
      }
      if (line->NotCondLine() != NULL) {
         printf("%d ", line->NotCondLine()->_Line);
      } else {
         printf("%d ", (int)-1);
      }
      if (line->NextLine() != NULL) {
         printf("%d ", line->NextLine()->_Line);
      } else {
         printf("%d ", (int)-1);
      }
      printf("\n");   
   }
   printf("\n");   
  //## end cControlProcedure::PrintLines%1060960062.body
}

cProcedureLine * cControlProcedure::FirstLine ()
{
  //## begin cControlProcedure::FirstLine%1060965468.body preserve=yes
   if (_Lines.size() > 0) {
      return _Lines[0];
   } else {
      return NULL;
   }
  //## end cControlProcedure::FirstLine%1060965468.body
}

// Additional Declarations
  //## begin cControlProcedure%3F38BC14031C.declarations preserve=yes
  //## end cControlProcedure%3F38BC14031C.declarations

//## begin module%3F38BC14031C.epilog preserve=yes
//## end module%3F38BC14031C.epilog
