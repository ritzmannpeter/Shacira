//## begin module%410898950261.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410898950261.cm

//## begin module%410898950261.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%410898950261.cp

//## Module: cPPCServer%410898950261; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCServer.cpp

//## begin module%410898950261.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%410898950261.additionalIncludes

//## begin module%410898950261.includes preserve=yes
//## end module%410898950261.includes

// cPPCServer
#include "Control/Device/PPCCom/cPPCServer.h"
// cPPCDevice
#include "Control/Device/PPCCom/cPPCDevice.h"
//## begin module%410898950261.additionalDeclarations preserve=yes
//## end module%410898950261.additionalDeclarations


// Class cPPCServer 


cPPCServer::cPPCServer()
  //## begin cPPCServer::cPPCServer%.hasinit preserve=no
      : _Device(NULL)
  //## end cPPCServer::cPPCServer%.hasinit
  //## begin cPPCServer::cPPCServer%.initialization preserve=yes
  //## end cPPCServer::cPPCServer%.initialization
{
  //## begin cPPCServer::cPPCServer%.body preserve=yes
  //## end cPPCServer::cPPCServer%.body
}

cPPCServer::cPPCServer(const cPPCServer &right)
  //## begin cPPCServer::cPPCServer%copy.hasinit preserve=no
      : _Device(NULL)
  //## end cPPCServer::cPPCServer%copy.hasinit
  //## begin cPPCServer::cPPCServer%copy.initialization preserve=yes
  //## end cPPCServer::cPPCServer%copy.initialization
{
  //## begin cPPCServer::cPPCServer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPPCServer::cPPCServer%copy.body
}

cPPCServer::cPPCServer (cCSComm *comm, cPPCDevice *device)
  //## begin cPPCServer::cPPCServer%1091082167.hasinit preserve=no
      : _Device(NULL)
  //## end cPPCServer::cPPCServer%1091082167.hasinit
  //## begin cPPCServer::cPPCServer%1091082167.initialization preserve=yes
  , cUDPServer(comm)
  //## end cPPCServer::cPPCServer%1091082167.initialization
{
  //## begin cPPCServer::cPPCServer%1091082167.body preserve=yes
   _Device = device;
  //## end cPPCServer::cPPCServer%1091082167.body
}


cPPCServer::~cPPCServer()
{
  //## begin cPPCServer::~cPPCServer%.body preserve=yes
  //## end cPPCServer::~cPPCServer%.body
}



//## Other Operations (implementation)
void cPPCServer::Dispatch (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cPPCServer::Dispatch%1091082166.body preserve=yes
//   PTR_T block = msg->AppData();
//   ULONG_T block_len = msg->AppDataSize();
   Reply(msg, client_address);
  //## end cPPCServer::Dispatch%1091082166.body
}

// Additional Declarations
  //## begin cPPCServer%410898950261.declarations preserve=yes
  //## end cPPCServer%410898950261.declarations

//## begin module%410898950261.epilog preserve=yes
//## end module%410898950261.epilog
