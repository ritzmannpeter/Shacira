//## begin module%3E00444D03D6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E00444D03D6.cm

//## begin module%3E00444D03D6.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E00444D03D6.cp

//## Module: cConstReal%3E00444D03D6; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cConstReal.cpp

//## begin module%3E00444D03D6.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E00444D03D6.additionalIncludes

//## begin module%3E00444D03D6.includes preserve=yes
//## end module%3E00444D03D6.includes

// cConstReal
#include "System/Database/cConstReal.h"
//## begin module%3E00444D03D6.additionalDeclarations preserve=yes
//## end module%3E00444D03D6.additionalDeclarations


// Class cConstReal 


cConstReal::cConstReal()
  //## begin cConstReal::cConstReal%.hasinit preserve=no
  //## end cConstReal::cConstReal%.hasinit
  //## begin cConstReal::cConstReal%.initialization preserve=yes
  //## end cConstReal::cConstReal%.initialization
{
  //## begin cConstReal::cConstReal%.body preserve=yes
_ASSERT_UNCOND
  //## end cConstReal::cConstReal%.body
}

cConstReal::cConstReal(const cConstReal &right)
  //## begin cConstReal::cConstReal%copy.hasinit preserve=no
  //## end cConstReal::cConstReal%copy.hasinit
  //## begin cConstReal::cConstReal%copy.initialization preserve=yes
  //## end cConstReal::cConstReal%copy.initialization
{
  //## begin cConstReal::cConstReal%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConstReal::cConstReal%copy.body
}

cConstReal::cConstReal (DOUBLE_T arg)
  //## begin cConstReal::cConstReal%1040992361.hasinit preserve=no
  //## end cConstReal::cConstReal%1040992361.hasinit
  //## begin cConstReal::cConstReal%1040992361.initialization preserve=yes
  //## end cConstReal::cConstReal%1040992361.initialization
{
  //## begin cConstReal::cConstReal%1040992361.body preserve=yes
   _Value = arg;
   _DataType = SH_DOUBLE;
  //## end cConstReal::cConstReal%1040992361.body
}


cConstReal::~cConstReal()
{
  //## begin cConstReal::~cConstReal%.body preserve=yes
  //## end cConstReal::~cConstReal%.body
}



//## Other Operations (implementation)
void cConstReal::GetValue (LONG_T &value)
{
  //## begin cConstReal::GetValue%1042654030.body preserve=yes
   value = (LONG_T)_Value;
  //## end cConstReal::GetValue%1042654030.body
}

void cConstReal::GetValue (ULONG_T &value)
{
  //## begin cConstReal::GetValue%1088693712.body preserve=yes
   value = (ULONG_T)_Value;
  //## end cConstReal::GetValue%1088693712.body
}

void cConstReal::GetValue (FLOAT_T &value)
{
  //## begin cConstReal::GetValue%1088693713.body preserve=yes
   value = (FLOAT_T)_Value;
  //## end cConstReal::GetValue%1088693713.body
}

void cConstReal::GetValue (DOUBLE_T &value)
{
  //## begin cConstReal::GetValue%1042654031.body preserve=yes
   value = _Value;
  //## end cConstReal::GetValue%1042654031.body
}

void cConstReal::GetValue (STRING_T &value)
{
  //## begin cConstReal::GetValue%1042654029.body preserve=yes
   char buf[32] = {0};
   SafePrintf(buf, sizeof(buf), "%f", _Value);
   value = buf;
  //## end cConstReal::GetValue%1042654029.body
}

void cConstReal::GetValue (WSTRING_T &value)
{
  //## begin cConstReal::GetValue%1088693714.body preserve=yes
  //## end cConstReal::GetValue%1088693714.body
}

void cConstReal::GetValue (PTR_T &value)
{
  //## begin cConstReal::GetValue%1088693715.body preserve=yes
  //## end cConstReal::GetValue%1088693715.body
}

// Additional Declarations
  //## begin cConstReal%3E00444D03D6.declarations preserve=yes
  //## end cConstReal%3E00444D03D6.declarations

//## begin module%3E00444D03D6.epilog preserve=yes
//## end module%3E00444D03D6.epilog
