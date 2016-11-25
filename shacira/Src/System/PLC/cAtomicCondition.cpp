//## begin module%3F38E3390222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38E3390222.cm

//## begin module%3F38E3390222.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38E3390222.cp

//## Module: cAtomicCondition%3F38E3390222; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cAtomicCondition.cpp

//## begin module%3F38E3390222.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F38E3390222.additionalIncludes

//## begin module%3F38E3390222.includes preserve=yes
//## end module%3F38E3390222.includes

// cArgument
#include "System/Database/cArgument.h"
// cAtomicCondition
#include "System/PLC/cAtomicCondition.h"
//## begin module%3F38E3390222.additionalDeclarations preserve=yes

#include "System/Sys/cFileSystemUtils.h"

BOOL_T _SCPLLog = false;
static char _LogBuffer[0x2000] = {0};
static const char * _LogFileName = "scpl.log";
void SCPLLog(const char * fmt_str, ...)
{
   if (_SCPLLog) {
      try {
         const char * file_name = "scpl.log";
         va_list args;
         va_start(args, fmt_str);
         _vsnprintf(_LogBuffer, sizeof(_LogBuffer)-1, fmt_str, args);
         char file[0x100] = {0};
         SafePrintf(file, sizeof(file), "Log\\%s", _LogFileName);
         FILE * stream = fopen(file, "a");
         if (stream != NULL) {
            fprintf(stream, "%s", _LogBuffer);
            fclose(stream);
         }
         va_end(args);
      } catch (...) {
      }
   }
}

void SCPLLogClear()
{
   try {
      char file[0x100] = {0};
      SafePrintf(file, sizeof(file), "Log\\%s", _LogFileName);
      cFileSystemUtils::RemoveFile(file);
   } catch (...) {
   }
}

static const char * Relop(RelOps relop)
{
   if (relop == RELOP_LT) {
      return "<";
   } else if (relop == RELOP_LE) {
      return "<=";
   } else if (relop == RELOP_GT) {
      return ">";
   } else if (relop == RELOP_GE) {
      return "<=";
   } else if (relop == RELOP_EQ) {
      return "==";
   } else if (relop == RELOP_NE) {
      return "!=";
   }
   return "?";
}

//## end module%3F38E3390222.additionalDeclarations


// Class cAtomicCondition 





cAtomicCondition::cAtomicCondition()
  //## begin cAtomicCondition::cAtomicCondition%.hasinit preserve=no
      : _RelOp(RELOP_UNDEF), _Argument2(NULL), _Argument1(NULL)
  //## end cAtomicCondition::cAtomicCondition%.hasinit
  //## begin cAtomicCondition::cAtomicCondition%.initialization preserve=yes
  //## end cAtomicCondition::cAtomicCondition%.initialization
{
  //## begin cAtomicCondition::cAtomicCondition%.body preserve=yes
_ASSERT_UNCOND
  //## end cAtomicCondition::cAtomicCondition%.body
}

cAtomicCondition::cAtomicCondition(const cAtomicCondition &right)
  //## begin cAtomicCondition::cAtomicCondition%copy.hasinit preserve=no
      : _RelOp(RELOP_UNDEF), _Argument2(NULL), _Argument1(NULL)
  //## end cAtomicCondition::cAtomicCondition%copy.hasinit
  //## begin cAtomicCondition::cAtomicCondition%copy.initialization preserve=yes
  //## end cAtomicCondition::cAtomicCondition%copy.initialization
{
  //## begin cAtomicCondition::cAtomicCondition%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cAtomicCondition::cAtomicCondition%copy.body
}

cAtomicCondition::cAtomicCondition (cArgument *argument1, RelOps rel_op, cArgument *argument2)
  //## begin cAtomicCondition::cAtomicCondition%1060691306.hasinit preserve=no
      : _RelOp(RELOP_UNDEF), _Argument2(NULL), _Argument1(NULL)
  //## end cAtomicCondition::cAtomicCondition%1060691306.hasinit
  //## begin cAtomicCondition::cAtomicCondition%1060691306.initialization preserve=yes
  //## end cAtomicCondition::cAtomicCondition%1060691306.initialization
{
  //## begin cAtomicCondition::cAtomicCondition%1060691306.body preserve=yes
   _Argument1 = argument1;
   _RelOp = rel_op;
   _Argument2 = argument2;
  //## end cAtomicCondition::cAtomicCondition%1060691306.body
}


cAtomicCondition::~cAtomicCondition()
{
  //## begin cAtomicCondition::~cAtomicCondition%.body preserve=yes
  //## end cAtomicCondition::~cAtomicCondition%.body
}



//## Other Operations (implementation)
BOOL_T cAtomicCondition::Eval ()
{
  //## begin cAtomicCondition::Eval%1060691309.body preserve=yes
   UCHAR_T data_type = _Argument1->_DataType;
   LONG_T lval1 = 0, lval2 = 0;
   DOUBLE_T dval1 = 0, dval2 = 0;
   STRING_T sval1, sval2;
   BOOL_T evaluation = false;
   switch (data_type) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
      _Argument1->GetValue(lval1);
      _Argument2->GetValue(lval2);
      if (_RelOp == RELOP_LT) {
         evaluation = (lval1 < lval2);
      } else if (_RelOp == RELOP_LE) {
         evaluation = (lval1 <= lval2);
      } else if (_RelOp == RELOP_GT) {
         evaluation = (lval1 > lval2);
      } else if (_RelOp == RELOP_GE) {
         evaluation = (lval1 >= lval2);
      } else if (_RelOp == RELOP_EQ) {
         evaluation = (lval1 == lval2);
      } else if (_RelOp == RELOP_NE) {
         evaluation = (lval1 != lval2);
      } else {
   _ASSERT_UNCOND
      }
      SCPLLog("int (%d %s %d) ? %s\n", lval1, Relop(_RelOp), lval2, evaluation ? "true" : "false");
      return evaluation;
   case SH_FLOAT:
   case SH_DOUBLE:
      _Argument1->GetValue(dval1);
      _Argument2->GetValue(dval2);
      if (_RelOp == RELOP_LT) {
         evaluation = (dval1 < dval2);
      } else if (_RelOp == RELOP_LE) {
         evaluation = (dval1 <= dval2);
      } else if (_RelOp == RELOP_GT) {
         evaluation = (dval1 > dval2);
      } else if (_RelOp == RELOP_GE) {
         evaluation = (dval1 >= dval2);
      } else if (_RelOp == RELOP_EQ) {
         evaluation = (dval1 == dval2);
      } else if (_RelOp == RELOP_NE) {
         evaluation = (dval1 != dval2);
      } else {
   _ASSERT_UNCOND
      }
      SCPLLog("float (%f %s %f) ? %s\n", dval1, Relop(_RelOp), dval2, evaluation ? "true" : "false");
      return evaluation;
   case SH_STRING:
      _Argument1->GetValue(sval1);
      _Argument2->GetValue(sval2);
      if (_RelOp == RELOP_LT) {
         evaluation = (strlen(sval1.c_str()) < strlen(sval2.c_str()));
      } else if (_RelOp == RELOP_LE) {
         evaluation = (strlen(sval1.c_str()) <= strlen(sval2.c_str()));
      } else if (_RelOp == RELOP_GT) {
         evaluation = (strlen(sval1.c_str()) > strlen(sval2.c_str()));
      } else if (_RelOp == RELOP_GE) {
         evaluation = (strlen(sval1.c_str()) >= strlen(sval2.c_str()));
      } else if (_RelOp == RELOP_EQ) {
         evaluation = !strcmp(sval1.c_str(), sval2.c_str());
      } else if (_RelOp == RELOP_NE) {
         evaluation = !strcmp(sval1.c_str(), sval2.c_str());
      } else {
   _ASSERT_UNCOND
      }
      SCPLLog("string (%s %s %s) ? %s\n", sval1.c_str(), Relop(_RelOp), sval2.c_str(), evaluation ? "true" : "false");
      return evaluation;
   }
_ASSERT_UNCOND
   return false;
  //## end cAtomicCondition::Eval%1060691309.body
}

// Additional Declarations
  //## begin cAtomicCondition%3F38E3390222.declarations preserve=yes
  //## end cAtomicCondition%3F38E3390222.declarations

//## begin module%3F38E3390222.epilog preserve=yes
//## end module%3F38E3390222.epilog
