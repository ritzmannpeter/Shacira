//## begin module%3F3BA40902DE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3BA40902DE.cm

//## begin module%3F3BA40902DE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3BA40902DE.cp

//## Module: cActLine%3F3BA40902DE; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cActLine.cpp

//## begin module%3F3BA40902DE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F3BA40902DE.additionalIncludes

//## begin module%3F3BA40902DE.includes preserve=yes
//## end module%3F3BA40902DE.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cActProcedure
#include "System/PLC/cActProcedure.h"
// cActLine
#include "System/PLC/cActLine.h"
// cProcedureLine
#include "System/PLC/cProcedureLine.h"
// cControlCondition
#include "System/PLC/cControlCondition.h"
//## begin module%3F3BA40902DE.additionalDeclarations preserve=yes
//## end module%3F3BA40902DE.additionalDeclarations


// Class cActLine 




cActLine::cActLine()
  //## begin cActLine::cActLine%.hasinit preserve=no
      : _ActProcedure(NULL), _Line(NULL), _Context(NULL)
  //## end cActLine::cActLine%.hasinit
  //## begin cActLine::cActLine%.initialization preserve=yes
  //## end cActLine::cActLine%.initialization
{
  //## begin cActLine::cActLine%.body preserve=yes
_ASSERT_UNCOND
  //## end cActLine::cActLine%.body
}

cActLine::cActLine(const cActLine &right)
  //## begin cActLine::cActLine%copy.hasinit preserve=no
      : _ActProcedure(NULL), _Line(NULL), _Context(NULL)
  //## end cActLine::cActLine%copy.hasinit
  //## begin cActLine::cActLine%copy.initialization preserve=yes
  //## end cActLine::cActLine%copy.initialization
{
  //## begin cActLine::cActLine%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cActLine::cActLine%copy.body
}

cActLine::cActLine (cContext *context, cProcedureLine *line, cActProcedure *act_procedure)
  //## begin cActLine::cActLine%1060849356.hasinit preserve=no
      : _ActProcedure(NULL), _Line(NULL), _Context(NULL)
  //## end cActLine::cActLine%1060849356.hasinit
  //## begin cActLine::cActLine%1060849356.initialization preserve=yes
  //## end cActLine::cActLine%1060849356.initialization
{
  //## begin cActLine::cActLine%1060849356.body preserve=yes
   _Context = context;
   _Line = line;
  //## end cActLine::cActLine%1060849356.body
}


cActLine::~cActLine()
{
  //## begin cActLine::~cActLine%.body preserve=yes
  //## end cActLine::~cActLine%.body
}



//## Other Operations (implementation)
INT_T cActLine::Execute ()
{
  //## begin cActLine::Execute%1060849357.body preserve=yes
//   cSystemUtils::Suspend(1);
#define EXECUTE_INTERNAL
#ifdef EXECUTE_INTERNAL
   return _Line->Execute(this);
#else
   Statements type = _Line->Type();
   if (type == UNDEF_STMT) {
   } else if (type == END_LINE_STMT) {
   } else if (type == EXEC_STMT) {
      try {
         cContext * context = _Context;
         cControlProcedure * proc = context->Procedure(_Line->ProcName().c_str());
         if (proc == NULL) {
            ErrorPrintf("no definition for procedure %s\n", _Line->ProcName().c_str());
         } else {
            cActProcedure act_proc(context, proc, NULL);
            act_proc.Execute();
         }
      } catch (cError & e) {
         ErrorPrintf("%s\n", (const char*) e);
      } catch (...) {
         ErrorPrintf("Unhandled exception in ExecuteProgcedure\n");
      }
   } else if (type == CALL_STMT) {
   } else if (type == PARAM_ASSIGN_STMT) {
   } else if (type == ARG_ASSIGN_STMT) {
      UCHAR_T data_type = _Line->VarRef()->_VarDef->_DataType;
      LONG_T lval = 0;
      DOUBLE_T dval = 0;
      switch (data_type) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_SHORT:
      case SH_USHORT:
      case SH_LONG:
      case SH_ULONG:
         _Line->Argument()->GetValue(lval);
         _Line->VarRef()->SetValue(lval);
         break;
      case SH_FLOAT:
      case SH_DOUBLE:
         _Line->Argument()->GetValue(dval);
         _Line->VarRef()->SetValue(dval);
         break;
      default:
_ASSERT_UNCOND
      }
   } else if (type == WHILE_STMT) {
      if (_Line->Condition()->Eval()) {
         if (_Line->CondLine() != NULL) {
            _Line = _Line->CondLine();
            return 0;
         }
      } else {
         if (_Line->NotCondLine()) {
            _Line = _Line->NotCondLine();
            return 0;
         }
      }
   } else if (type == IF_STMT) {
      if (_Line->Condition()->Eval()) {
         if (_Line->CondLine() != NULL) {
            _Line = _Line->CondLine();
            return 0;
         }
      } else {
         if (_Line->NotCondLine()) {
            _Line = _Line->NotCondLine();
            return 0;
         }
      }
   } else if (type == IF_ELSE_STMT) {
      if (_Line->Condition()->Eval()) {
         if (_Line->CondLine() != NULL) {
            _Line = _Line->CondLine();
            return 0;
         }
      } else {
         if (_Line->NotCondLine()) {
            _Line = _Line->NotCondLine();
            return 0;
         }
      }
   } else {

   }
   _Line = _Line->NextLine();
   return 0;
#endif
  //## end cActLine::Execute%1060849357.body
}

void cActLine::Line (cProcedureLine *line)
{
  //## begin cActLine::Line%1060849358.body preserve=yes
   _Line = line;
  //## end cActLine::Line%1060849358.body
}

cProcedureLine * cActLine::Line ()
{
  //## begin cActLine::Line%1060849359.body preserve=yes
   return _Line;
  //## end cActLine::Line%1060849359.body
}

cContext * cActLine::Context ()
{
  //## begin cActLine::Context%1060946834.body preserve=yes
   return _Context;
  //## end cActLine::Context%1060946834.body
}

// Additional Declarations
  //## begin cActLine%3F3BA40902DE.declarations preserve=yes
  //## end cActLine%3F3BA40902DE.declarations

//## begin module%3F3BA40902DE.epilog preserve=yes
//## end module%3F3BA40902DE.epilog
