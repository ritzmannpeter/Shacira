//## begin module%3C7E425B0200.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7E425B0200.cm

//## begin module%3C7E425B0200.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7E425B0200.cp

//## Module: cArgument%3C7E425B0200; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cArgument.cpp

//## begin module%3C7E425B0200.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C7E425B0200.additionalIncludes

//## begin module%3C7E425B0200.includes preserve=yes
//## end module%3C7E425B0200.includes

// cFuncRef
#include "System/Database/cFuncRef.h"
// cArgument
#include "System/Database/cArgument.h"
//## begin module%3C7E425B0200.additionalDeclarations preserve=yes
//## end module%3C7E425B0200.additionalDeclarations


// Class cArgument 





cArgument::cArgument()
  //## begin cArgument::cArgument%.hasinit preserve=no
      : _DataType(UNDEFINED)
  //## end cArgument::cArgument%.hasinit
  //## begin cArgument::cArgument%.initialization preserve=yes
  //## end cArgument::cArgument%.initialization
{
  //## begin cArgument::cArgument%.body preserve=yes
  //## end cArgument::cArgument%.body
}

cArgument::cArgument(const cArgument &right)
  //## begin cArgument::cArgument%copy.hasinit preserve=no
      : _DataType(UNDEFINED)
  //## end cArgument::cArgument%copy.hasinit
  //## begin cArgument::cArgument%copy.initialization preserve=yes
  //## end cArgument::cArgument%copy.initialization
{
  //## begin cArgument::cArgument%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cArgument::cArgument%copy.body
}


cArgument::~cArgument()
{
  //## begin cArgument::~cArgument%.body preserve=yes
  //## end cArgument::~cArgument%.body
}



//## Other Operations (implementation)
cFuncRef * cArgument::GetFuncRef ()
{
  //## begin cArgument::GetFuncRef%1089133001.body preserve=yes
   return NULL;
  //## end cArgument::GetFuncRef%1089133001.body
}

UCHAR_T cArgument::DataType ()
{
  //## begin cArgument::DataType%1061805339.body preserve=yes
   return _DataType;
  //## end cArgument::DataType%1061805339.body
}

// Additional Declarations
  //## begin cArgument%3C7E425B0200.declarations preserve=yes
  //## end cArgument%3C7E425B0200.declarations

//## begin module%3C7E425B0200.epilog preserve=yes
//## end module%3C7E425B0200.epilog
