//## begin module%4102741F004E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4102741F004E.cm

//## begin module%4102741F004E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4102741F004E.cp

//## Module: cCSComm%4102741F004E; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cCSComm.cpp

//## begin module%4102741F004E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4102741F004E.additionalIncludes

//## begin module%4102741F004E.includes preserve=yes
//## end module%4102741F004E.includes

// cUDPClient
#include "System/ClientServer/cUDPClient.h"
// cCSAddress
#include "System/ClientServer/cCSAddress.h"
// cCSComm
#include "System/ClientServer/cCSComm.h"
// cUDPServer
#include "System/ClientServer/cUDPServer.h"
//## begin module%4102741F004E.additionalDeclarations preserve=yes
//## end module%4102741F004E.additionalDeclarations


// Class cCSComm 






cCSComm::cCSComm()
  //## begin cCSComm::cCSComm%.hasinit preserve=no
      : _Server(NULL), _ReadAddress(NULL), _WriteAddress(NULL), _Client(NULL)
  //## end cCSComm::cCSComm%.hasinit
  //## begin cCSComm::cCSComm%.initialization preserve=yes
  //## end cCSComm::cCSComm%.initialization
{
  //## begin cCSComm::cCSComm%.body preserve=yes
  //## end cCSComm::cCSComm%.body
}

cCSComm::cCSComm(const cCSComm &right)
  //## begin cCSComm::cCSComm%copy.hasinit preserve=no
      : _Server(NULL), _ReadAddress(NULL), _WriteAddress(NULL), _Client(NULL)
  //## end cCSComm::cCSComm%copy.hasinit
  //## begin cCSComm::cCSComm%copy.initialization preserve=yes
  //## end cCSComm::cCSComm%copy.initialization
{
  //## begin cCSComm::cCSComm%copy.body preserve=yes
  //## end cCSComm::cCSComm%copy.body
}


cCSComm::~cCSComm()
{
  //## begin cCSComm::~cCSComm%.body preserve=yes
  //## end cCSComm::~cCSComm%.body
}


// Additional Declarations
  //## begin cCSComm%4102741F004E.declarations preserve=yes
  //## end cCSComm%4102741F004E.declarations

//## begin module%4102741F004E.epilog preserve=yes
//## end module%4102741F004E.epilog
