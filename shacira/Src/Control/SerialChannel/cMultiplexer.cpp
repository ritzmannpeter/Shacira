//## begin module%3FBC9F5C033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBC9F5C033C.cm

//## begin module%3FBC9F5C033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBC9F5C033C.cp

//## Module: cMultiplexer%3FBC9F5C033C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cMultiplexer.cpp

//## begin module%3FBC9F5C033C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FBC9F5C033C.additionalIncludes

//## begin module%3FBC9F5C033C.includes preserve=yes
//## end module%3FBC9F5C033C.includes

// cMultiplexer
#include "Control/SerialChannel/cMultiplexer.h"
// cSerialBridge
#include "Control/SerialChannel/cSerialBridge.h"
//## begin module%3FBC9F5C033C.additionalDeclarations preserve=yes
//## end module%3FBC9F5C033C.additionalDeclarations


// Class cMultiplexer 


cMultiplexer::cMultiplexer()
  //## begin cMultiplexer::cMultiplexer%.hasinit preserve=no
  //## end cMultiplexer::cMultiplexer%.hasinit
  //## begin cMultiplexer::cMultiplexer%.initialization preserve=yes
  //## end cMultiplexer::cMultiplexer%.initialization
{
  //## begin cMultiplexer::cMultiplexer%.body preserve=yes
  //## end cMultiplexer::cMultiplexer%.body
}

cMultiplexer::cMultiplexer(const cMultiplexer &right)
  //## begin cMultiplexer::cMultiplexer%copy.hasinit preserve=no
  //## end cMultiplexer::cMultiplexer%copy.hasinit
  //## begin cMultiplexer::cMultiplexer%copy.initialization preserve=yes
  //## end cMultiplexer::cMultiplexer%copy.initialization
{
  //## begin cMultiplexer::cMultiplexer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cMultiplexer::cMultiplexer%copy.body
}


cMultiplexer::~cMultiplexer()
{
  //## begin cMultiplexer::~cMultiplexer%.body preserve=yes
  //## end cMultiplexer::~cMultiplexer%.body
}



//## Other Operations (implementation)
void cMultiplexer::AddBridge (CONST_STRING_T name, cSerialBridge *bridge)
{
  //## begin cMultiplexer::AddBridge%1069326591.body preserve=yes
   _Bridges[name] = bridge;
  //## end cMultiplexer::AddBridge%1069326591.body
}

// Additional Declarations
  //## begin cMultiplexer%3FBC9F5C033C.declarations preserve=yes
  //## end cMultiplexer%3FBC9F5C033C.declarations

//## begin module%3FBC9F5C033C.epilog preserve=yes
//## end module%3FBC9F5C033C.epilog
