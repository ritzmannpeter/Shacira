//## begin module%3E0043B201E8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0043B201E8.cm

//## begin module%3E0043B201E8.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0043B201E8.cp

//## Module: cConstString%3E0043B201E8; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cConstString.cpp

//## begin module%3E0043B201E8.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0043B201E8.additionalIncludes

//## begin module%3E0043B201E8.includes preserve=yes
//## end module%3E0043B201E8.includes

// cConstString
#include "System/Database/cConstString.h"
//## begin module%3E0043B201E8.additionalDeclarations preserve=yes
//## end module%3E0043B201E8.additionalDeclarations


// Class cConstString 


cConstString::cConstString()
  //## begin cConstString::cConstString%.hasinit preserve=no
  //## end cConstString::cConstString%.hasinit
  //## begin cConstString::cConstString%.initialization preserve=yes
  //## end cConstString::cConstString%.initialization
{
  //## begin cConstString::cConstString%.body preserve=yes
_ASSERT_UNCOND
  //## end cConstString::cConstString%.body
}

cConstString::cConstString(const cConstString &right)
  //## begin cConstString::cConstString%copy.hasinit preserve=no
  //## end cConstString::cConstString%copy.hasinit
  //## begin cConstString::cConstString%copy.initialization preserve=yes
  //## end cConstString::cConstString%copy.initialization
{
  //## begin cConstString::cConstString%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cConstString::cConstString%copy.body
}

cConstString::cConstString (CONST_STRING_T arg)
  //## begin cConstString::cConstString%1040992363.hasinit preserve=no
  //## end cConstString::cConstString%1040992363.hasinit
  //## begin cConstString::cConstString%1040992363.initialization preserve=yes
  //## end cConstString::cConstString%1040992363.initialization
{
  //## begin cConstString::cConstString%1040992363.body preserve=yes
   _Value = arg;
   _DataType = SH_STRING;
  //## end cConstString::cConstString%1040992363.body
}


cConstString::~cConstString()
{
  //## begin cConstString::~cConstString%.body preserve=yes
  //## end cConstString::~cConstString%.body
}



//## Other Operations (implementation)
void cConstString::GetValue (LONG_T &value)
{
  //## begin cConstString::GetValue%1042654042.body preserve=yes
   value = atol(_Value.c_str());
  //## end cConstString::GetValue%1042654042.body
}

void cConstString::GetValue (ULONG_T &value)
{
  //## begin cConstString::GetValue%1088693720.body preserve=yes
   value = strtoul(_Value.c_str(), NULL, 0);
  //## end cConstString::GetValue%1088693720.body
}

void cConstString::GetValue (FLOAT_T &value)
{
  //## begin cConstString::GetValue%1088693721.body preserve=yes
   value = (FLOAT_T)atof(_Value.c_str());
  //## end cConstString::GetValue%1088693721.body
}

void cConstString::GetValue (DOUBLE_T &value)
{
  //## begin cConstString::GetValue%1042654043.body preserve=yes
   value = (DOUBLE_T)atof(_Value.c_str());
  //## end cConstString::GetValue%1042654043.body
}

void cConstString::GetValue (STRING_T &value)
{
  //## begin cConstString::GetValue%1042654041.body preserve=yes
   value = _Value;
  //## end cConstString::GetValue%1042654041.body
}

void cConstString::GetValue (WSTRING_T &value)
{
  //## begin cConstString::GetValue%1088693722.body preserve=yes
  //## end cConstString::GetValue%1088693722.body
}

void cConstString::GetValue (PTR_T &value)
{
  //## begin cConstString::GetValue%1088693723.body preserve=yes
  //## end cConstString::GetValue%1088693723.body
}

// Additional Declarations
  //## begin cConstString%3E0043B201E8.declarations preserve=yes
  //## end cConstString%3E0043B201E8.declarations

//## begin module%3E0043B201E8.epilog preserve=yes
//## end module%3E0043B201E8.epilog
