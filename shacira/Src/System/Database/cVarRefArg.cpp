//## begin module%3E0044830329.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0044830329.cm

//## begin module%3E0044830329.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0044830329.cp

//## Module: cVarRefArg%3E0044830329; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVarRefArg.cpp

//## begin module%3E0044830329.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0044830329.additionalIncludes

//## begin module%3E0044830329.includes preserve=yes
//## end module%3E0044830329.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cVarRefArg
#include "System/Database/cVarRefArg.h"
//## begin module%3E0044830329.additionalDeclarations preserve=yes
//## end module%3E0044830329.additionalDeclarations


// Class cVarRefArg 


cVarRefArg::cVarRefArg()
  //## begin cVarRefArg::cVarRefArg%.hasinit preserve=no
      : _VarRef(NULL)
  //## end cVarRefArg::cVarRefArg%.hasinit
  //## begin cVarRefArg::cVarRefArg%.initialization preserve=yes
  //## end cVarRefArg::cVarRefArg%.initialization
{
  //## begin cVarRefArg::cVarRefArg%.body preserve=yes
_ASSERT_UNCOND
  //## end cVarRefArg::cVarRefArg%.body
}

cVarRefArg::cVarRefArg(const cVarRefArg &right)
  //## begin cVarRefArg::cVarRefArg%copy.hasinit preserve=no
      : _VarRef(NULL)
  //## end cVarRefArg::cVarRefArg%copy.hasinit
  //## begin cVarRefArg::cVarRefArg%copy.initialization preserve=yes
  //## end cVarRefArg::cVarRefArg%copy.initialization
{
  //## begin cVarRefArg::cVarRefArg%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cVarRefArg::cVarRefArg%copy.body
}

cVarRefArg::cVarRefArg (cVarRef *var_ref)
  //## begin cVarRefArg::cVarRefArg%1040992369.hasinit preserve=no
      : _VarRef(NULL)
  //## end cVarRefArg::cVarRefArg%1040992369.hasinit
  //## begin cVarRefArg::cVarRefArg%1040992369.initialization preserve=yes
  //## end cVarRefArg::cVarRefArg%1040992369.initialization
{
  //## begin cVarRefArg::cVarRefArg%1040992369.body preserve=yes
_ASSERT_COND(var_ref != NULL)
   _VarRef = var_ref;
   _DataType = _VarRef->DataType();
  //## end cVarRefArg::cVarRefArg%1040992369.body
}


cVarRefArg::~cVarRefArg()
{
  //## begin cVarRefArg::~cVarRefArg%.body preserve=yes
  //## end cVarRefArg::~cVarRefArg%.body
}



//## Other Operations (implementation)
void cVarRefArg::GetValue (LONG_T &value)
{
  //## begin cVarRefArg::GetValue%1042654024.body preserve=yes
   _VarRef->GetValue(value);
  //## end cVarRefArg::GetValue%1042654024.body
}

void cVarRefArg::GetValue (ULONG_T &value)
{
  //## begin cVarRefArg::GetValue%1088693708.body preserve=yes
   _VarRef->GetValue(value);
  //## end cVarRefArg::GetValue%1088693708.body
}

void cVarRefArg::GetValue (FLOAT_T &value)
{
  //## begin cVarRefArg::GetValue%1088693709.body preserve=yes
   _VarRef->GetValue(value);
  //## end cVarRefArg::GetValue%1088693709.body
}

void cVarRefArg::GetValue (DOUBLE_T &value)
{
  //## begin cVarRefArg::GetValue%1042654025.body preserve=yes
   _VarRef->GetValue(value);
  //## end cVarRefArg::GetValue%1042654025.body
}

void cVarRefArg::GetValue (STRING_T &value)
{
  //## begin cVarRefArg::GetValue%1042654023.body preserve=yes
   _VarRef->GetValue(value);
  //## end cVarRefArg::GetValue%1042654023.body
}

void cVarRefArg::GetValue (WSTRING_T &value)
{
  //## begin cVarRefArg::GetValue%1088693710.body preserve=yes
//   _VarRef->GetValue(value);
  //## end cVarRefArg::GetValue%1088693710.body
}

void cVarRefArg::GetValue (PTR_T &value)
{
  //## begin cVarRefArg::GetValue%1088693711.body preserve=yes
  //## end cVarRefArg::GetValue%1088693711.body
}

// Additional Declarations
  //## begin cVarRefArg%3E0044830329.declarations preserve=yes
  //## end cVarRefArg%3E0044830329.declarations

//## begin module%3E0044830329.epilog preserve=yes
//## end module%3E0044830329.epilog
