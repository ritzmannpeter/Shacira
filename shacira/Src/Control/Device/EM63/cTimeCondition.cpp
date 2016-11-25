//## begin module%43A6945802B8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A6945802B8.cm

//## begin module%43A6945802B8.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A6945802B8.cp

//## Module: cTimeCondition%43A6945802B8; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cTimeCondition.cpp

//## begin module%43A6945802B8.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43A6945802B8.additionalIncludes

//## begin module%43A6945802B8.includes preserve=yes
//## end module%43A6945802B8.includes

// cTimeCondition
#include "Control/Device/EM63/cTimeCondition.h"
//## begin module%43A6945802B8.additionalDeclarations preserve=yes
#include "Control/Device/EM63/cEM63Interface.h"
//## end module%43A6945802B8.additionalDeclarations


// Class cTimeCondition 



cTimeCondition::cTimeCondition()
  //## begin cTimeCondition::cTimeCondition%.hasinit preserve=no
      : _RelOp(EM63_GT)
  //## end cTimeCondition::cTimeCondition%.hasinit
  //## begin cTimeCondition::cTimeCondition%.initialization preserve=yes
  //## end cTimeCondition::cTimeCondition%.initialization
{
  //## begin cTimeCondition::cTimeCondition%.body preserve=yes
_ASSERT_UNCOND
  //## end cTimeCondition::cTimeCondition%.body
}

cTimeCondition::cTimeCondition(const cTimeCondition &right)
  //## begin cTimeCondition::cTimeCondition%copy.hasinit preserve=no
      : _RelOp(EM63_GT)
  //## end cTimeCondition::cTimeCondition%copy.hasinit
  //## begin cTimeCondition::cTimeCondition%copy.initialization preserve=yes
  //## end cTimeCondition::cTimeCondition%copy.initialization
{
  //## begin cTimeCondition::cTimeCondition%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTimeCondition::cTimeCondition%copy.body
}

cTimeCondition::cTimeCondition (int rel_op, int time)
  //## begin cTimeCondition::cTimeCondition%1134980240.hasinit preserve=no
      : _RelOp(EM63_GT)
  //## end cTimeCondition::cTimeCondition%1134980240.hasinit
  //## begin cTimeCondition::cTimeCondition%1134980240.initialization preserve=yes
  //## end cTimeCondition::cTimeCondition%1134980240.initialization
{
  //## begin cTimeCondition::cTimeCondition%1134980240.body preserve=yes
   _RelOp = rel_op;
   _Time = time;
   INCREMENT_OBJECT_COUNT()
   //## end cTimeCondition::cTimeCondition%1134980240.body
}


cTimeCondition::~cTimeCondition()
{
  //## begin cTimeCondition::~cTimeCondition%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cTimeCondition::~cTimeCondition%.body
}



//## Other Operations (implementation)
BOOL_T cTimeCondition::Condition ()
{
  //## begin cTimeCondition::Condition%1134980241.body preserve=yes
   cTimeObject _now;
   ULONG_T now = _now;
   ULONG_T cmp = _Time;
   switch (_RelOp) {
   case EM63_EQ: return (now == cmp);
   case EM63_GT: return (now > cmp);
   case EM63_LT: return (now < cmp);
   case EM63_GE: return (now >= cmp);
   case EM63_LE: return (now <= cmp);
   }
   return false;
  //## end cTimeCondition::Condition%1134980241.body
}

// Additional Declarations
  //## begin cTimeCondition%43A6945802B8.declarations preserve=yes
  //## end cTimeCondition%43A6945802B8.declarations

//## begin module%43A6945802B8.epilog preserve=yes
//## end module%43A6945802B8.epilog
