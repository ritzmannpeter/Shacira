//## begin module%3F3A35F501F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3A35F501F4.cm

//## begin module%3F3A35F501F4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3A35F501F4.cp

//## Module: cProcedureLine%3F3A35F501F4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cProcedureLine.cpp

//## begin module%3F3A35F501F4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F3A35F501F4.additionalIncludes

//## begin module%3F3A35F501F4.includes preserve=yes
//## end module%3F3A35F501F4.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cArgument
#include "System/Database/cArgument.h"
// cActProcedure
#include "System/PLC/cActProcedure.h"
// cActLine
#include "System/PLC/cActLine.h"
// cProcedureLine
#include "System/PLC/cProcedureLine.h"
// cControlCondition
#include "System/PLC/cControlCondition.h"
//## begin module%3F3A35F501F4.additionalDeclarations preserve=yes
//## end module%3F3A35F501F4.additionalDeclarations


// Class cProcedureLine 


















cProcedureLine::cProcedureLine()
  //## begin cProcedureLine::cProcedureLine%.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%.hasinit
  //## begin cProcedureLine::cProcedureLine%.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%.initialization
{
  //## begin cProcedureLine::cProcedureLine%.body preserve=yes
   _Type = END_LINE_STMT;
  //## end cProcedureLine::cProcedureLine%.body
}

cProcedureLine::cProcedureLine(const cProcedureLine &right)
  //## begin cProcedureLine::cProcedureLine%copy.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%copy.hasinit
  //## begin cProcedureLine::cProcedureLine%copy.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%copy.initialization
{
  //## begin cProcedureLine::cProcedureLine%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProcedureLine::cProcedureLine%copy.body
}

cProcedureLine::cProcedureLine (Statements type, CONST_STRING_T proc_name, INT_T depth)
  //## begin cProcedureLine::cProcedureLine%1060779899.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%1060779899.hasinit
  //## begin cProcedureLine::cProcedureLine%1060779899.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%1060779899.initialization
{
  //## begin cProcedureLine::cProcedureLine%1060779899.body preserve=yes
   _Type = type;
   _Depth = depth;
   _ProcName = proc_name;
  //## end cProcedureLine::cProcedureLine%1060779899.body
}

cProcedureLine::cProcedureLine (Statements type, cFuncRef *func_ref, INT_T depth)
  //## begin cProcedureLine::cProcedureLine%1060779900.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%1060779900.hasinit
  //## begin cProcedureLine::cProcedureLine%1060779900.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%1060779900.initialization
{
  //## begin cProcedureLine::cProcedureLine%1060779900.body preserve=yes
   _Type = type;
   _Depth = depth;
   _FuncRef = func_ref;
  //## end cProcedureLine::cProcedureLine%1060779900.body
}

cProcedureLine::cProcedureLine (Statements type, cVarRef *var_ref, cArgument *arg, INT_T depth)
  //## begin cProcedureLine::cProcedureLine%1060779901.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%1060779901.hasinit
  //## begin cProcedureLine::cProcedureLine%1060779901.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%1060779901.initialization
{
  //## begin cProcedureLine::cProcedureLine%1060779901.body preserve=yes
   _Type = type;
   _Depth = depth;
   _VarRef = var_ref;
   _Argument = arg;
  //## end cProcedureLine::cProcedureLine%1060779901.body
}

cProcedureLine::cProcedureLine (Statements type, cVarRef *var_ref, CONST_STRING_T param_name, INT_T depth)
  //## begin cProcedureLine::cProcedureLine%1060779902.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%1060779902.hasinit
  //## begin cProcedureLine::cProcedureLine%1060779902.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%1060779902.initialization
{
  //## begin cProcedureLine::cProcedureLine%1060779902.body preserve=yes
   _Type = type;
   _Depth = depth;
   _VarRef = var_ref;
   _ParamName = param_name;
  //## end cProcedureLine::cProcedureLine%1060779902.body
}

cProcedureLine::cProcedureLine (Statements type, cControlCondition *cond, INT_T depth)
  //## begin cProcedureLine::cProcedureLine%1060779903.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%1060779903.hasinit
  //## begin cProcedureLine::cProcedureLine%1060779903.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%1060779903.initialization
{
  //## begin cProcedureLine::cProcedureLine%1060779903.body preserve=yes
   _Type = type;
   _Depth = depth;
   _Condition = cond;
  //## end cProcedureLine::cProcedureLine%1060779903.body
}

cProcedureLine::cProcedureLine (Statements type, INT_T depth)
  //## begin cProcedureLine::cProcedureLine%1090397995.hasinit preserve=no
      : _SourceLine(-1), _Line(-1), _Depth(-1), _Type(UNDEF_STMT), _FuncRef(NULL), _NextLine(NULL), _NotCondLine(NULL), _CondLine(NULL), _ParentLine(NULL), _Condition(NULL), _Argument(NULL), _VarRef(NULL)
  //## end cProcedureLine::cProcedureLine%1090397995.hasinit
  //## begin cProcedureLine::cProcedureLine%1090397995.initialization preserve=yes
  //## end cProcedureLine::cProcedureLine%1090397995.initialization
{
  //## begin cProcedureLine::cProcedureLine%1090397995.body preserve=yes
   _Type = type;
   _Depth = depth;
  //## end cProcedureLine::cProcedureLine%1090397995.body
}


cProcedureLine::~cProcedureLine()
{
  //## begin cProcedureLine::~cProcedureLine%.body preserve=yes
//   DELETE_OBJECT(cProcedureLine, _NotCondLine);
//   DELETE_OBJECT(cProcedureLine, _CondLine);
   DELETE_OBJECT(cArgument, _Argument);
   DELETE_OBJECT(cVarRef, _VarRef);
   DELETE_OBJECT(cFuncRef, _FuncRef);
   DELETE_OBJECT(cControlCondition, _Condition);
  //## end cProcedureLine::~cProcedureLine%.body
}



//## Other Operations (implementation)
void cProcedureLine::NextLine (cProcedureLine *line)
{
  //## begin cProcedureLine::NextLine%1060779905.body preserve=yes
   _NextLine = line;
  //## end cProcedureLine::NextLine%1060779905.body
}

cProcedureLine * cProcedureLine::NextLine ()
{
  //## begin cProcedureLine::NextLine%1060779909.body preserve=yes
   return _NextLine;
  //## end cProcedureLine::NextLine%1060779909.body
}

void cProcedureLine::CondLine (cProcedureLine *line)
{
  //## begin cProcedureLine::CondLine%1060779906.body preserve=yes
   _CondLine = line;
  //## end cProcedureLine::CondLine%1060779906.body
}

cProcedureLine * cProcedureLine::CondLine ()
{
  //## begin cProcedureLine::CondLine%1060779911.body preserve=yes
   return _CondLine;
  //## end cProcedureLine::CondLine%1060779911.body
}

void cProcedureLine::NotCondLine (cProcedureLine *line)
{
  //## begin cProcedureLine::NotCondLine%1060779907.body preserve=yes
   _NotCondLine = line;
  //## end cProcedureLine::NotCondLine%1060779907.body
}

cProcedureLine * cProcedureLine::NotCondLine ()
{
  //## begin cProcedureLine::NotCondLine%1060779912.body preserve=yes
   return _NotCondLine;
  //## end cProcedureLine::NotCondLine%1060779912.body
}

void cProcedureLine::ParentLine (cProcedureLine *line)
{
  //## begin cProcedureLine::ParentLine%1060849352.body preserve=yes
   _ParentLine = line;
  //## end cProcedureLine::ParentLine%1060849352.body
}

cProcedureLine * cProcedureLine::ParentLine ()
{
  //## begin cProcedureLine::ParentLine%1060849353.body preserve=yes
   return _ParentLine;
  //## end cProcedureLine::ParentLine%1060849353.body
}

void cProcedureLine::Resolve ()
{
  //## begin cProcedureLine::Resolve%1060849354.body preserve=yes
   if (_Type == UNDEF_STMT) {
   } else if (_Type == END_LINE_STMT) {
      if (_ParentLine != NULL) {
         if (_ParentLine->_Type == WHILE_STMT) {
            NextLine(_ParentLine);
         } else {
            if (_NextLine == NULL) {
               NextLine(_ParentLine->NextLine());
            }
         }
      }
   } else if (_Type == EXEC_STMT) {
   } else if (_Type == CALL_STMT) {
   } else if (_Type == PARAM_ASSIGN_STMT) {
   } else if (_Type == ARG_ASSIGN_STMT) {
   } else if (_Type == WHILE_STMT) {
   } else if (_Type == IF_STMT) {
   } else if (_Type == IF_ELSE_STMT) {
   } else {
   }
  //## end cProcedureLine::Resolve%1060849354.body
}

INT_T cProcedureLine::Execute (cActLine *act_line)
{
  //## begin cProcedureLine::Execute%1060849350.body preserve=yes
   if (_Type == UNDEF_STMT) {
   } else if (_Type == END_LINE_STMT) {
   } else if (_Type == EXEC_STMT) {
      try {
         cContext * context = act_line->Context();
         cControlProcedure * proc = context->Procedure(_ProcName.c_str());
         if (proc == NULL) {
            ErrorPrintf("no definition for procedure %s\n", _ProcName.c_str());
         } else {
            cActProcedure act_proc(context, proc, NULL);
            act_proc.Execute();
         }
      } catch (cError & e) {
         ErrorPrintf("%s\n", (const char*) e);
      } catch (...) {
         ErrorPrintf("Unhandled exception in ExecuteProgcedure\n");
      }
   } else if (_Type == CALL_STMT) {
      UCHAR_T data_type = _VarRef->DataType();
      LONG_T lval = 0;
      DOUBLE_T dval = 0;
      STRING_T sval;
      switch (data_type) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_SHORT:
      case SH_USHORT:
      case SH_LONG:
      case SH_ULONG:
         _FuncRef->CallFunc(lval);
         _VarRef->SetValue(lval);
         break;
      case SH_FLOAT:
      case SH_DOUBLE:
         _FuncRef->CallFunc(dval);
         _VarRef->SetValue(dval);
         break;
      case SH_STRING:
         _FuncRef->CallFunc(sval);
         _VarRef->SetValue(sval.c_str());
         break;
      default:
_ASSERT_UNCOND
      }
   } else if (_Type == PARAM_ASSIGN_STMT) {
   } else if (_Type == ARG_ASSIGN_STMT) {
      UCHAR_T data_type = _VarRef->DataType();
      LONG_T lval = 0;
      DOUBLE_T dval = 0;
      STRING_T sval;
      switch (data_type) {
      case SH_CHAR:
      case SH_UCHAR:
      case SH_SHORT:
      case SH_USHORT:
      case SH_LONG:
      case SH_ULONG:
         _Argument->GetValue(lval);
         _VarRef->SetValue(lval);
         break;
      case SH_FLOAT:
      case SH_DOUBLE:
         _Argument->GetValue(dval);
         _VarRef->SetValue(dval);
         break;
      case SH_STRING:
         _Argument->GetValue(sval);
         _VarRef->SetValue(sval.c_str());
         break;
      default:
_ASSERT_UNCOND
      }
   } else if (_Type == WHILE_STMT) {
      if (_Condition->Eval()) {
         if (_CondLine) {
            act_line->Line(_CondLine);
            return 0;
         }
      } else {
         if (_NotCondLine) {
            act_line->Line(_NotCondLine);
            return 0;
         }
      }
   } else if (_Type == IF_STMT) {
      if (_Condition->Eval()) {
         if (_CondLine) {
            act_line->Line(_CondLine);
            return 0;
         }
      } else {
         if (_NotCondLine) {
            act_line->Line(_NotCondLine);
            return 0;
         }
      }
   } else if (_Type == IF_ELSE_STMT) {
      if (_Condition->Eval()) {
         if (_CondLine) {
            act_line->Line(_CondLine);
            return 0;
         }
      } else {
         if (_NotCondLine) {
            act_line->Line(_NotCondLine);
            return 0;
         }
      }
   } else if (_Type == RETURN_STMT) {
      act_line->Line(NULL);
      return 0;
_ASSERT_UNCOND
   } else {
_ASSERT_UNCOND
   }
   act_line->Line(_NextLine);
   return 0;
  //## end cProcedureLine::Execute%1060849350.body
}

STRING_T cProcedureLine::Description ()
{
  //## begin cProcedureLine::Description%1060779904.body preserve=yes
   STRING_T description = TypeName().c_str();
   if (_Type == UNDEF_STMT) {
   } else if (_Type == END_LINE_STMT) {
   } else if (_Type == EXEC_STMT) {
      description += " ";
      description += _ProcName.c_str();
   } else if (_Type == CALL_STMT) {
      description += " ";
      description += _FuncRef->_Name.c_str();
   } else if (_Type == PARAM_ASSIGN_STMT) {
      description += _ParamName.c_str();
   } else if (_Type == ARG_ASSIGN_STMT) {
   } else if (_Type == IF_STMT) {
   } else if (_Type == IF_ELSE_STMT) {
   } else if (_Type == WHILE_STMT) {
   } else if (_Type == RETURN_STMT) {
   } else {
   }
   return description;
  //## end cProcedureLine::Description%1060779904.body
}

STRING_T cProcedureLine::TypeName ()
{
  //## begin cProcedureLine::TypeName%1060849355.body preserve=yes
   if (_Type == UNDEF_STMT) {
      return "undefined";
   } else if (_Type == END_LINE_STMT) {
      return "blkend";
   } else if (_Type == EXEC_STMT) {
      return "execute";
   } else if (_Type == CALL_STMT) {
      return "call";
   } else if (_Type == PARAM_ASSIGN_STMT) {
      return "assignp";
   } else if (_Type == ARG_ASSIGN_STMT) {
      return "assigna";
   } else if (_Type == IF_STMT) {
      return "if";
   } else if (_Type == IF_ELSE_STMT) {
      return "ifelse";
   } else if (_Type == WHILE_STMT) {
      return "while";
   } else if (_Type == RETURN_STMT) {
      return "return";
   } else {
      return "unknown";
   }
  //## end cProcedureLine::TypeName%1060849355.body
}

Statements cProcedureLine::Type ()
{
  //## begin cProcedureLine::Type%1060965461.body preserve=yes
   return _Type;
  //## end cProcedureLine::Type%1060965461.body
}

STRING_T cProcedureLine::ProcName ()
{
  //## begin cProcedureLine::ProcName%1060965462.body preserve=yes
   return _ProcName;
  //## end cProcedureLine::ProcName%1060965462.body
}

STRING_T cProcedureLine::ParamName ()
{
  //## begin cProcedureLine::ParamName%1060965463.body preserve=yes
   return _ParamName;
  //## end cProcedureLine::ParamName%1060965463.body
}

cControlCondition * cProcedureLine::Condition ()
{
  //## begin cProcedureLine::Condition%1060965464.body preserve=yes
   return _Condition;
  //## end cProcedureLine::Condition%1060965464.body
}

cVarRef * cProcedureLine::VarRef ()
{
  //## begin cProcedureLine::VarRef%1060965465.body preserve=yes
   return _VarRef;
  //## end cProcedureLine::VarRef%1060965465.body
}

cFuncRef * cProcedureLine::FuncRef ()
{
  //## begin cProcedureLine::FuncRef%1060965466.body preserve=yes
   return _FuncRef;
  //## end cProcedureLine::FuncRef%1060965466.body
}

cArgument * cProcedureLine::Argument ()
{
  //## begin cProcedureLine::Argument%1060965467.body preserve=yes
   return _Argument;
  //## end cProcedureLine::Argument%1060965467.body
}

// Additional Declarations
  //## begin cProcedureLine%3F3A35F501F4.declarations preserve=yes
  //## end cProcedureLine%3F3A35F501F4.declarations

//## begin module%3F3A35F501F4.epilog preserve=yes
//## end module%3F3A35F501F4.epilog
