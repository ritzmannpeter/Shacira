//## begin module%3E0044AA03D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0044AA03D0.cm

//## begin module%3E0044AA03D0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0044AA03D0.cp

//## Module: cFuncRefArg%3E0044AA03D0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFuncRefArg.cpp

//## begin module%3E0044AA03D0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0044AA03D0.additionalIncludes

//## begin module%3E0044AA03D0.includes preserve=yes
//## end module%3E0044AA03D0.includes

// cFuncRefArg
#include "System/Database/cFuncRefArg.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
//## begin module%3E0044AA03D0.additionalDeclarations preserve=yes
//## end module%3E0044AA03D0.additionalDeclarations


// Class cFuncRefArg 


cFuncRefArg::cFuncRefArg()
  //## begin cFuncRefArg::cFuncRefArg%.hasinit preserve=no
      : _FuncRef(NULL)
  //## end cFuncRefArg::cFuncRefArg%.hasinit
  //## begin cFuncRefArg::cFuncRefArg%.initialization preserve=yes
  //## end cFuncRefArg::cFuncRefArg%.initialization
{
  //## begin cFuncRefArg::cFuncRefArg%.body preserve=yes
_ASSERT_UNCOND
  //## end cFuncRefArg::cFuncRefArg%.body
}

cFuncRefArg::cFuncRefArg(const cFuncRefArg &right)
  //## begin cFuncRefArg::cFuncRefArg%copy.hasinit preserve=no
      : _FuncRef(NULL)
  //## end cFuncRefArg::cFuncRefArg%copy.hasinit
  //## begin cFuncRefArg::cFuncRefArg%copy.initialization preserve=yes
  //## end cFuncRefArg::cFuncRefArg%copy.initialization
{
  //## begin cFuncRefArg::cFuncRefArg%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFuncRefArg::cFuncRefArg%copy.body
}

cFuncRefArg::cFuncRefArg (cFuncRef *func_ref)
  //## begin cFuncRefArg::cFuncRefArg%1040992368.hasinit preserve=no
      : _FuncRef(NULL)
  //## end cFuncRefArg::cFuncRefArg%1040992368.hasinit
  //## begin cFuncRefArg::cFuncRefArg%1040992368.initialization preserve=yes
  //## end cFuncRefArg::cFuncRefArg%1040992368.initialization
{
  //## begin cFuncRefArg::cFuncRefArg%1040992368.body preserve=yes
_ASSERT_COND(func_ref != NULL)
   _FuncRef = func_ref;
   _DataType = _FuncRef->DataType();
  //## end cFuncRefArg::cFuncRefArg%1040992368.body
}


cFuncRefArg::~cFuncRefArg()
{
  //## begin cFuncRefArg::~cFuncRefArg%.body preserve=yes
  //## end cFuncRefArg::~cFuncRefArg%.body
}



//## Other Operations (implementation)
void cFuncRefArg::GetValue (LONG_T &value)
{
  //## begin cFuncRefArg::GetValue%1042654018.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1042654018.body
}

void cFuncRefArg::GetValue (ULONG_T &value)
{
  //## begin cFuncRefArg::GetValue%1088693704.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1088693704.body
}

void cFuncRefArg::GetValue (FLOAT_T &value)
{
  //## begin cFuncRefArg::GetValue%1088693705.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1088693705.body
}

void cFuncRefArg::GetValue (DOUBLE_T &value)
{
  //## begin cFuncRefArg::GetValue%1042654019.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1042654019.body
}

void cFuncRefArg::GetValue (STRING_T &value)
{
  //## begin cFuncRefArg::GetValue%1042654017.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1042654017.body
}

void cFuncRefArg::GetValue (WSTRING_T &value)
{
  //## begin cFuncRefArg::GetValue%1088693706.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1088693706.body
}

void cFuncRefArg::GetValue (PTR_T &value)
{
  //## begin cFuncRefArg::GetValue%1088693707.body preserve=yes
   _FuncRef->CallFunc(value);
  //## end cFuncRefArg::GetValue%1088693707.body
}

cFuncRef * cFuncRefArg::GetFuncRef ()
{
  //## begin cFuncRefArg::GetFuncRef%1089133000.body preserve=yes
   return _FuncRef;
  //## end cFuncRefArg::GetFuncRef%1089133000.body
}

// Additional Declarations
  //## begin cFuncRefArg%3E0044AA03D0.declarations preserve=yes
  //## end cFuncRefArg%3E0044AA03D0.declarations

//## begin module%3E0044AA03D0.epilog preserve=yes
//## end module%3E0044AA03D0.epilog
