//## begin module%43A694880122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A694880122.cm

//## begin module%43A694880122.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A694880122.cp

//## Module: cParamCondition%43A694880122; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cParamCondition.cpp

//## begin module%43A694880122.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43A694880122.additionalIncludes

//## begin module%43A694880122.includes preserve=yes
//## end module%43A694880122.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cParamCondition
#include "Control/Device/EM63/cParamCondition.h"
//## begin module%43A694880122.additionalDeclarations preserve=yes
#include "Control/Device/EM63/cEM63Interface.h"
//## end module%43A694880122.additionalDeclarations


// Class cParamCondition 







cParamCondition::cParamCondition()
  //## begin cParamCondition::cParamCondition%.hasinit preserve=no
      : _RelOp(EM63_EQ), _ConditionType(EM63_CYCLE)
  //## end cParamCondition::cParamCondition%.hasinit
  //## begin cParamCondition::cParamCondition%.initialization preserve=yes
  //## end cParamCondition::cParamCondition%.initialization
{
  //## begin cParamCondition::cParamCondition%.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cParamCondition::cParamCondition%.body
}

cParamCondition::cParamCondition(const cParamCondition &right)
  //## begin cParamCondition::cParamCondition%copy.hasinit preserve=no
      : _RelOp(EM63_EQ), _ConditionType(EM63_CYCLE)
  //## end cParamCondition::cParamCondition%copy.hasinit
  //## begin cParamCondition::cParamCondition%copy.initialization preserve=yes
  //## end cParamCondition::cParamCondition%copy.initialization
{
  //## begin cParamCondition::cParamCondition%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cParamCondition::cParamCondition%copy.body
}

cParamCondition::cParamCondition (CONST_STRING_T param_id, int rel_op, CONST_STRING_T value)
  //## begin cParamCondition::cParamCondition%1134980246.hasinit preserve=no
      : _RelOp(EM63_EQ), _ConditionType(EM63_CYCLE)
  //## end cParamCondition::cParamCondition%1134980246.hasinit
  //## begin cParamCondition::cParamCondition%1134980246.initialization preserve=yes
  //## end cParamCondition::cParamCondition%1134980246.initialization
{
  //## begin cParamCondition::cParamCondition%1134980246.body preserve=yes
   _ParamId = param_id;
   _RelOp = rel_op;
   _CmpValue = value;
   _ConditionType = EM63_PARAM_COND;
   INCREMENT_OBJECT_COUNT()
   //## end cParamCondition::cParamCondition%1134980246.body
}

cParamCondition::cParamCondition (CONST_STRING_T param_id, int cond_type)
  //## begin cParamCondition::cParamCondition%1135258640.hasinit preserve=no
      : _RelOp(EM63_EQ), _ConditionType(EM63_CYCLE)
  //## end cParamCondition::cParamCondition%1135258640.hasinit
  //## begin cParamCondition::cParamCondition%1135258640.initialization preserve=yes
  //## end cParamCondition::cParamCondition%1135258640.initialization
{
  //## begin cParamCondition::cParamCondition%1135258640.body preserve=yes
   _ParamId = param_id;
   _ConditionType = cond_type;
   INCREMENT_OBJECT_COUNT()
   //## end cParamCondition::cParamCondition%1135258640.body
}


cParamCondition::~cParamCondition()
{
  //## begin cParamCondition::~cParamCondition%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cParamCondition::~cParamCondition%.body
}



//## Other Operations (implementation)
BOOL_T cParamCondition::Condition ()
{
  //## begin cParamCondition::Condition%1134980244.body preserve=yes
   RefreshValue();
   if (_ConditionType == EM63_PARAM_CHANGED) {
      if (_PrevValue != _ActValue) {
         _PrevValue = _ActValue;
         return true;
      } else {
         return false;
      }
   } else if (_ConditionType == EM63_PARAM_COND) {
      double act_val = atof(_ActValue.c_str());
      double cmp_val = atof(_CmpValue.c_str());
      switch (_RelOp) {
      case EM63_EQ: return (act_val == cmp_val);
      case EM63_GT: return (act_val > cmp_val);
      case EM63_LT: return (act_val < cmp_val);
      case EM63_GE: return (act_val >= cmp_val);
      case EM63_LE: return (act_val <= cmp_val);
      }
   }
   return false;
  //## end cParamCondition::Condition%1134980244.body
}

BOOL_T cParamCondition::Process (cContext *context)
{
  //## begin cParamCondition::Process%1134992978.body preserve=yes
   BOOL_T success = false;
   _Context = context;
   if (_stricmp(_ParamId.c_str(), "DATE") == 0) {
      success = true;
   } else if (_stricmp(_ParamId.c_str(), "TIME") == 0) {
      success = true;
   } else if (_stricmp(_ParamId.c_str(), "COUNT") == 0) {
      success = true;
   } else {
      try {
         _VarRef = _Context->VarRef(_ParamId.c_str());
         success = true;
      } catch (cError & e) {
      } catch (...) {
      }
   }
   return success;
  //## end cParamCondition::Process%1134992978.body
}

void cParamCondition::RefreshValue ()
{
  //## begin cParamCondition::RefreshValue%1134992976.body preserve=yes
   if (_stricmp(_ParamId.c_str(), "DATE") == 0) {
   } else if (_stricmp(_ParamId.c_str(), "TIME") == 0) {
   } else if (_stricmp(_ParamId.c_str(), "COUNT") == 0) {
   } else {
      if (_VarRef != NULL) {
         _VarRef->GetValue(_ActValue);
      }
   }
  //## end cParamCondition::RefreshValue%1134992976.body
}

// Additional Declarations
  //## begin cParamCondition%43A694880122.declarations preserve=yes
  //## end cParamCondition%43A694880122.declarations

//## begin module%43A694880122.epilog preserve=yes
//## end module%43A694880122.epilog
