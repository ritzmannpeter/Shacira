//## begin module%43A6B4F80119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A6B4F80119.cm

//## begin module%43A6B4F80119.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A6B4F80119.cp

//## Module: cCyclicCondition%43A6B4F80119; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cCyclicCondition.cpp

//## begin module%43A6B4F80119.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43A6B4F80119.additionalIncludes

//## begin module%43A6B4F80119.includes preserve=yes
//## end module%43A6B4F80119.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cCyclicCondition
#include "Control/Device/EM63/cCyclicCondition.h"
//## begin module%43A6B4F80119.additionalDeclarations preserve=yes
#include "Control/Device/EM63/cEM63Interface.h"
//## end module%43A6B4F80119.additionalDeclarations


// Class cCyclicCondition 





cCyclicCondition::cCyclicCondition()
  //## begin cCyclicCondition::cCyclicCondition%.hasinit preserve=no
      : _ShotParamId("ActCntMachAdd"), _Shot(0), _ActShot(0), _PrevShot(0)
  //## end cCyclicCondition::cCyclicCondition%.hasinit
  //## begin cCyclicCondition::cCyclicCondition%.initialization preserve=yes
  //## end cCyclicCondition::cCyclicCondition%.initialization
{
  //## begin cCyclicCondition::cCyclicCondition%.body preserve=yes
_ASSERT_UNCOND
  //## end cCyclicCondition::cCyclicCondition%.body
}

cCyclicCondition::cCyclicCondition(const cCyclicCondition &right)
  //## begin cCyclicCondition::cCyclicCondition%copy.hasinit preserve=no
      : _ShotParamId("ActCntMachAdd"), _Shot(0), _ActShot(0), _PrevShot(0)
  //## end cCyclicCondition::cCyclicCondition%copy.hasinit
  //## begin cCyclicCondition::cCyclicCondition%copy.initialization preserve=yes
  //## end cCyclicCondition::cCyclicCondition%copy.initialization
{
  //## begin cCyclicCondition::cCyclicCondition%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCyclicCondition::cCyclicCondition%copy.body
}

cCyclicCondition::cCyclicCondition (int shot, CONST_STRING_T shot_param_id)
  //## begin cCyclicCondition::cCyclicCondition%1134992985.hasinit preserve=no
      : _ShotParamId("ActCntMachAdd"), _Shot(0), _ActShot(0), _PrevShot(0)
  //## end cCyclicCondition::cCyclicCondition%1134992985.hasinit
  //## begin cCyclicCondition::cCyclicCondition%1134992985.initialization preserve=yes
  //## end cCyclicCondition::cCyclicCondition%1134992985.initialization
{
  //## begin cCyclicCondition::cCyclicCondition%1134992985.body preserve=yes
   _Shot = shot;
   _ShotParamId = shot_param_id;
   INCREMENT_OBJECT_COUNT()
   //## end cCyclicCondition::cCyclicCondition%1134992985.body
}


cCyclicCondition::~cCyclicCondition()
{
  //## begin cCyclicCondition::~cCyclicCondition%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cCyclicCondition::~cCyclicCondition%.body
}



//## Other Operations (implementation)
BOOL_T cCyclicCondition::Condition ()
{
  //## begin cCyclicCondition::Condition%1134992983.body preserve=yes
   RefreshShot();
   if (_ActShot != _PrevShot) {
      if (_ActShot == _PrevShot + 1) {
         _PrevShot = _ActShot;
         if (_Shot == 0) {
            return true;
         } else {
            if ((_ActShot % _Shot) == 0) {
               return true;
            } else {
               return false;
            }
         }
      } else {
         _PrevShot = _ActShot;
         return false;
      }
   } else {
      return false;
   }
  //## end cCyclicCondition::Condition%1134992983.body
}

BOOL_T cCyclicCondition::Process (cContext *context)
{
  //## begin cCyclicCondition::Process%1134992984.body preserve=yes
   _Context = context;
   _VarRef = _Context->VarRef(_ShotParamId.c_str());
   if (_VarRef == NULL) {
      return false;
   } else {
      return true;
   }
  //## end cCyclicCondition::Process%1134992984.body
}

void cCyclicCondition::RefreshShot ()
{
  //## begin cCyclicCondition::RefreshShot%1134992995.body preserve=yes
   if (_VarRef != NULL) {
      _VarRef->GetValue(_ActShot);
   }
  //## end cCyclicCondition::RefreshShot%1134992995.body
}

// Additional Declarations
  //## begin cCyclicCondition%43A6B4F80119.declarations preserve=yes
  //## end cCyclicCondition%43A6B4F80119.declarations

//## begin module%43A6B4F80119.epilog preserve=yes
//## end module%43A6B4F80119.epilog
