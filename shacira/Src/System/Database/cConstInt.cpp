//## begin module%3E00443301DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E00443301DA.cm

//## begin module%3E00443301DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E00443301DA.cp

//## Module: cConstInt%3E00443301DA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cConstInt.cpp

//## begin module%3E00443301DA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E00443301DA.additionalIncludes

//## begin module%3E00443301DA.includes preserve=yes
//## end module%3E00443301DA.includes

// cConstInt
#include "System/Database/cConstInt.h"
//## begin module%3E00443301DA.additionalDeclarations preserve=yes
//## end module%3E00443301DA.additionalDeclarations


// Class cConstInt 


cConstInt::cConstInt()
  //## begin cConstInt::cConstInt%.hasinit preserve=no
  //## end cConstInt::cConstInt%.hasinit
  //## begin cConstInt::cConstInt%.initialization preserve=yes
  //## end cConstInt::cConstInt%.initialization
{
  //## begin cConstInt::cConstInt%.body preserve=yes
_ASSERT_UNCOND
  //## end cConstInt::cConstInt%.body
}

cConstInt::cConstInt(const cConstInt &right)
  //## begin cConstInt::cConstInt%copy.hasinit preserve=no
  //## end cConstInt::cConstInt%copy.hasinit
  //## begin cConstInt::cConstInt%copy.initialization preserve=yes
  //## end cConstInt::cConstInt%copy.initialization
{
  //## begin cConstInt::cConstInt%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConstInt::cConstInt%copy.body
}

cConstInt::cConstInt (LONG_T arg)
  //## begin cConstInt::cConstInt%1040992362.hasinit preserve=no
  //## end cConstInt::cConstInt%1040992362.hasinit
  //## begin cConstInt::cConstInt%1040992362.initialization preserve=yes
  //## end cConstInt::cConstInt%1040992362.initialization
{
  //## begin cConstInt::cConstInt%1040992362.body preserve=yes
   _Value = arg;
   _DataType = SH_LONG;
  //## end cConstInt::cConstInt%1040992362.body
}


cConstInt::~cConstInt()
{
  //## begin cConstInt::~cConstInt%.body preserve=yes
  //## end cConstInt::~cConstInt%.body
}



//## Other Operations (implementation)
void cConstInt::GetValue (LONG_T &value)
{
  //## begin cConstInt::GetValue%1042654036.body preserve=yes
   value = _Value;
  //## end cConstInt::GetValue%1042654036.body
}

void cConstInt::GetValue (ULONG_T &value)
{
  //## begin cConstInt::GetValue%1088693716.body preserve=yes
   value = (ULONG_T)_Value;
  //## end cConstInt::GetValue%1088693716.body
}

void cConstInt::GetValue (FLOAT_T &value)
{
  //## begin cConstInt::GetValue%1088693717.body preserve=yes
   value = (FLOAT_T)_Value;
  //## end cConstInt::GetValue%1088693717.body
}

void cConstInt::GetValue (DOUBLE_T &value)
{
  //## begin cConstInt::GetValue%1042654037.body preserve=yes
   value = _Value;
  //## end cConstInt::GetValue%1042654037.body
}

void cConstInt::GetValue (STRING_T &value)
{
  //## begin cConstInt::GetValue%1042654035.body preserve=yes
   char buf[32] = {0};
   ltoa(_Value, buf, 10);
   value = buf;
  //## end cConstInt::GetValue%1042654035.body
}

void cConstInt::GetValue (WSTRING_T &value)
{
  //## begin cConstInt::GetValue%1088693718.body preserve=yes
  //## end cConstInt::GetValue%1088693718.body
}

void cConstInt::GetValue (PTR_T &value)
{
  //## begin cConstInt::GetValue%1088693719.body preserve=yes
  //## end cConstInt::GetValue%1088693719.body
}

// Additional Declarations
  //## begin cConstInt%3E00443301DA.declarations preserve=yes
  //## end cConstInt%3E00443301DA.declarations

//## begin module%3E00443301DA.epilog preserve=yes
//## end module%3E00443301DA.epilog
