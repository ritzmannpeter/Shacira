//## begin module%3F38DCC301A5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38DCC301A5.cm

//## begin module%3F38DCC301A5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38DCC301A5.cp

//## Module: cControlCondition%3F38DCC301A5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlCondition.cpp

//## begin module%3F38DCC301A5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F38DCC301A5.additionalIncludes

//## begin module%3F38DCC301A5.includes preserve=yes
//## end module%3F38DCC301A5.includes

// cAtomicCondition
#include "System/PLC/cAtomicCondition.h"
// cControlCondition
#include "System/PLC/cControlCondition.h"
// cControlState
#include "System/PLC/cControlState.h"
//## begin module%3F38DCC301A5.additionalDeclarations preserve=yes
//## end module%3F38DCC301A5.additionalDeclarations


// Class cControlCondition 










cControlCondition::cControlCondition()
  //## begin cControlCondition::cControlCondition%.hasinit preserve=no
      : _LogOp(LOGOP_UNDEF), _Left(NULL), _Right(NULL), _State(NULL), _AtomicCondition(NULL)
  //## end cControlCondition::cControlCondition%.hasinit
  //## begin cControlCondition::cControlCondition%.initialization preserve=yes
  //## end cControlCondition::cControlCondition%.initialization
{
  //## begin cControlCondition::cControlCondition%.body preserve=yes
_ASSERT_UNCOND
  //## end cControlCondition::cControlCondition%.body
}

cControlCondition::cControlCondition(const cControlCondition &right)
  //## begin cControlCondition::cControlCondition%copy.hasinit preserve=no
      : _LogOp(LOGOP_UNDEF), _Left(NULL), _Right(NULL), _State(NULL), _AtomicCondition(NULL)
  //## end cControlCondition::cControlCondition%copy.hasinit
  //## begin cControlCondition::cControlCondition%copy.initialization preserve=yes
  //## end cControlCondition::cControlCondition%copy.initialization
{
  //## begin cControlCondition::cControlCondition%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cControlCondition::cControlCondition%copy.body
}

cControlCondition::cControlCondition (cAtomicCondition *atomic_condition)
  //## begin cControlCondition::cControlCondition%1060691303.hasinit preserve=no
      : _LogOp(LOGOP_UNDEF), _Left(NULL), _Right(NULL), _State(NULL), _AtomicCondition(NULL)
  //## end cControlCondition::cControlCondition%1060691303.hasinit
  //## begin cControlCondition::cControlCondition%1060691303.initialization preserve=yes
  //## end cControlCondition::cControlCondition%1060691303.initialization
{
  //## begin cControlCondition::cControlCondition%1060691303.body preserve=yes
   _AtomicCondition = atomic_condition;
  //## end cControlCondition::cControlCondition%1060691303.body
}

cControlCondition::cControlCondition (cControlCondition *left, cControlCondition *right, LogOps log_op)
  //## begin cControlCondition::cControlCondition%1060691304.hasinit preserve=no
      : _LogOp(LOGOP_UNDEF), _Left(NULL), _Right(NULL), _State(NULL), _AtomicCondition(NULL)
  //## end cControlCondition::cControlCondition%1060691304.hasinit
  //## begin cControlCondition::cControlCondition%1060691304.initialization preserve=yes
  //## end cControlCondition::cControlCondition%1060691304.initialization
{
  //## begin cControlCondition::cControlCondition%1060691304.body preserve=yes
   _Left = left;
   _LogOp = log_op;
   _Right = right;
  //## end cControlCondition::cControlCondition%1060691304.body
}

cControlCondition::cControlCondition (cControlCondition *cond)
  //## begin cControlCondition::cControlCondition%1060767922.hasinit preserve=no
      : _LogOp(LOGOP_UNDEF), _Left(NULL), _Right(NULL), _State(NULL), _AtomicCondition(NULL)
  //## end cControlCondition::cControlCondition%1060767922.hasinit
  //## begin cControlCondition::cControlCondition%1060767922.initialization preserve=yes
  //## end cControlCondition::cControlCondition%1060767922.initialization
{
  //## begin cControlCondition::cControlCondition%1060767922.body preserve=yes
   _Left = cond;
  //## end cControlCondition::cControlCondition%1060767922.body
}

cControlCondition::cControlCondition (cControlState *state)
  //## begin cControlCondition::cControlCondition%1060691305.hasinit preserve=no
      : _LogOp(LOGOP_UNDEF), _Left(NULL), _Right(NULL), _State(NULL), _AtomicCondition(NULL)
  //## end cControlCondition::cControlCondition%1060691305.hasinit
  //## begin cControlCondition::cControlCondition%1060691305.initialization preserve=yes
  //## end cControlCondition::cControlCondition%1060691305.initialization
{
  //## begin cControlCondition::cControlCondition%1060691305.body preserve=yes
   _State = state;
  //## end cControlCondition::cControlCondition%1060691305.body
}


cControlCondition::~cControlCondition()
{
  //## begin cControlCondition::~cControlCondition%.body preserve=yes
  //## end cControlCondition::~cControlCondition%.body
}



//## Other Operations (implementation)
BOOL_T cControlCondition::Eval ()
{
  //## begin cControlCondition::Eval%1060691310.body preserve=yes
   if (_AtomicCondition != NULL) {
      return (_AtomicCondition->Eval());
   } else if (_State != NULL) {
      return (_State->Eval());
   } else if (_LogOp == LOGOP_OR) {
      return (_Left->Eval() || _Right->Eval());
   } else if (_LogOp == LOGOP_AND) {
      return (_Left->Eval() && _Right->Eval());
   } else if (_LogOp == LOGOP_NOT) {
      return (!_Left->Eval());
   } else if (_LogOp == LOGOP_UNDEF) {
      return (_Left->Eval());
   } else {
_ASSERT_UNCOND
      return false;
   }
  //## end cControlCondition::Eval%1060691310.body
}

// Additional Declarations
  //## begin cControlCondition%3F38DCC301A5.declarations preserve=yes
  //## end cControlCondition%3F38DCC301A5.declarations

//## begin module%3F38DCC301A5.epilog preserve=yes
//## end module%3F38DCC301A5.epilog
