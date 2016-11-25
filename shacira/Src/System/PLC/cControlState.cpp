//## begin module%3F38BB7C03B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BB7C03B9.cm

//## begin module%3F38BB7C03B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BB7C03B9.cp

//## Module: cControlState%3F38BB7C03B9; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlState.cpp

//## begin module%3F38BB7C03B9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F38BB7C03B9.additionalIncludes

//## begin module%3F38BB7C03B9.includes preserve=yes
//## end module%3F38BB7C03B9.includes

// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cStateVariable
#include "System/PLC/cStateVariable.h"
// cControlCondition
#include "System/PLC/cControlCondition.h"
// cControlState
#include "System/PLC/cControlState.h"
//## begin module%3F38BB7C03B9.additionalDeclarations preserve=yes
//## end module%3F38BB7C03B9.additionalDeclarations


// Class cControlState 







cControlState::cControlState()
  //## begin cControlState::cControlState%.hasinit preserve=no
      : _Condition(NULL), _VarDef(NULL)
  //## end cControlState::cControlState%.hasinit
  //## begin cControlState::cControlState%.initialization preserve=yes
  //## end cControlState::cControlState%.initialization
{
  //## begin cControlState::cControlState%.body preserve=yes
_ASSERT_UNCOND
  //## end cControlState::cControlState%.body
}

cControlState::cControlState(const cControlState &right)
  //## begin cControlState::cControlState%copy.hasinit preserve=no
      : _Condition(NULL), _VarDef(NULL)
  //## end cControlState::cControlState%copy.hasinit
  //## begin cControlState::cControlState%copy.initialization preserve=yes
  //## end cControlState::cControlState%copy.initialization
{
  //## begin cControlState::cControlState%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cControlState::cControlState%copy.body
}

cControlState::cControlState (CONST_STRING_T name, cControlCondition *condition)
  //## begin cControlState::cControlState%1060691300.hasinit preserve=no
      : _Condition(NULL), _VarDef(NULL)
  //## end cControlState::cControlState%1060691300.hasinit
  //## begin cControlState::cControlState%1060691300.initialization preserve=yes
  //## end cControlState::cControlState%1060691300.initialization
{
  //## begin cControlState::cControlState%1060691300.body preserve=yes
   _StateName = name;
   _Condition = condition;
  //## end cControlState::cControlState%1060691300.body
}


cControlState::~cControlState()
{
  //## begin cControlState::~cControlState%.body preserve=yes
  //## end cControlState::~cControlState%.body
}



//## Other Operations (implementation)
BOOL_T cControlState::Eval ()
{
  //## begin cControlState::Eval%1060691308.body preserve=yes
   return (_Condition->Eval());
  //## end cControlState::Eval%1060691308.body
}

cVarDef * cControlState::VarDef ()
{
  //## begin cControlState::VarDef%1060709189.body preserve=yes
   if (_VarDef == NULL) {
      CreateVar();
   }
   return _VarDef;
  //## end cControlState::VarDef%1060709189.body
}

void cControlState::CreateVar ()
{
  //## begin cControlState::CreateVar%1060709215.body preserve=yes
   cVarDef * var_def = new cVarDef(_StateName.c_str(), SH_CHAR, 0, 0);
   cVariable * variable = new cStateVariable(var_def, this);
   var_def->_Variable = variable;
   _VarDef = var_def;
  //## end cControlState::CreateVar%1060709215.body
}

// Additional Declarations
  //## begin cControlState%3F38BB7C03B9.declarations preserve=yes
  //## end cControlState%3F38BB7C03B9.declarations

//## begin module%3F38BB7C03B9.epilog preserve=yes
//## end module%3F38BB7C03B9.epilog
