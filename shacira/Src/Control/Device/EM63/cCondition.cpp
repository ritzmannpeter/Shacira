//## begin module%43A694350009.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A694350009.cm

//## begin module%43A694350009.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A694350009.cp

//## Module: cCondition%43A694350009; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cCondition.cpp

//## begin module%43A694350009.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43A694350009.additionalIncludes

//## begin module%43A694350009.includes preserve=yes
//## end module%43A694350009.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cCondition
#include "Control/Device/EM63/cCondition.h"
//## begin module%43A694350009.additionalDeclarations preserve=yes
#include "Control/Device/EM63/cEM63Interface.h"
//## end module%43A694350009.additionalDeclarations


// Class cCondition 





cCondition::cCondition()
  //## begin cCondition::cCondition%.hasinit preserve=no
      : _ConditionType(EM63_UNDEFINED_CONDITION), _LogOp(EM63_ID), _Context(NULL), _VarRef(NULL)
  //## end cCondition::cCondition%.hasinit
  //## begin cCondition::cCondition%.initialization preserve=yes
  //## end cCondition::cCondition%.initialization
{
  //## begin cCondition::cCondition%.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cCondition::cCondition%.body
}

cCondition::cCondition(const cCondition &right)
  //## begin cCondition::cCondition%copy.hasinit preserve=no
      : _ConditionType(EM63_UNDEFINED_CONDITION), _LogOp(EM63_ID), _Context(NULL), _VarRef(NULL)
  //## end cCondition::cCondition%copy.hasinit
  //## begin cCondition::cCondition%copy.initialization preserve=yes
  //## end cCondition::cCondition%copy.initialization
{
  //## begin cCondition::cCondition%copy.body preserve=yes
   INCREMENT_OBJECT_COUNT()
  //## end cCondition::cCondition%copy.body
}


cCondition::~cCondition()
{
  //## begin cCondition::~cCondition%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
  //## end cCondition::~cCondition%.body
}



//## Other Operations (implementation)
BOOL_T cCondition::Eval ()
{
  //## begin cCondition::Eval%1134992989.body preserve=yes
   if (Condition()) {
      if (_LogOp == EM63_NOT) {
         return false;
      } else {
         return true;
      }
   } else {
      if (_LogOp == EM63_NOT) {
         return true;
      } else {
         return false;
      }
   }
  //## end cCondition::Eval%1134992989.body
}

BOOL_T cCondition::Process (cContext *context)
{
  //## begin cCondition::Process%1134992977.body preserve=yes
   _Context = context;
   return true;
  //## end cCondition::Process%1134992977.body
}

void cCondition::SetLogOp (int log_op)
{
  //## begin cCondition::SetLogOp%1134992987.body preserve=yes
  //## end cCondition::SetLogOp%1134992987.body
}

// Additional Declarations
  //## begin cCondition%43A694350009.declarations preserve=yes
  //## end cCondition%43A694350009.declarations

//## begin module%43A694350009.epilog preserve=yes
//## end module%43A694350009.epilog
