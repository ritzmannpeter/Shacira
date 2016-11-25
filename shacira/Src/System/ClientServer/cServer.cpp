//## begin module%4295992400CA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4295992400CA.cm

//## begin module%4295992400CA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4295992400CA.cp

//## Module: cServer%4295992400CA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cServer.cpp

//## begin module%4295992400CA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4295992400CA.additionalIncludes

//## begin module%4295992400CA.includes preserve=yes
//## end module%4295992400CA.includes

// cServerThread
#include "System/ClientServer/cServerThread.h"
// cServer
#include "System/ClientServer/cServer.h"
//## begin module%4295992400CA.additionalDeclarations preserve=yes
//## end module%4295992400CA.additionalDeclarations


// Class cServer 





cServer::cServer()
  //## begin cServer::cServer%.hasinit preserve=no
      : _ListenerPort(0), _MaxConnections(5), _Socket(INVALID_SOCKET)
  //## end cServer::cServer%.hasinit
  //## begin cServer::cServer%.initialization preserve=yes
  //## end cServer::cServer%.initialization
{
  //## begin cServer::cServer%.body preserve=yes
   Initialize();
  //## end cServer::cServer%.body
}

cServer::cServer(const cServer &right)
  //## begin cServer::cServer%copy.hasinit preserve=no
      : _ListenerPort(0), _MaxConnections(5), _Socket(INVALID_SOCKET)
  //## end cServer::cServer%copy.hasinit
  //## begin cServer::cServer%copy.initialization preserve=yes
  //## end cServer::cServer%copy.initialization
{
  //## begin cServer::cServer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cServer::cServer%copy.body
}

cServer::cServer (USHORT_T listener_port)
  //## begin cServer::cServer%1117174977.hasinit preserve=no
      : _ListenerPort(0), _MaxConnections(5), _Socket(INVALID_SOCKET)
  //## end cServer::cServer%1117174977.hasinit
  //## begin cServer::cServer%1117174977.initialization preserve=yes
  //## end cServer::cServer%1117174977.initialization
{
  //## begin cServer::cServer%1117174977.body preserve=yes
   _ListenerPort = listener_port;
   Initialize();
  //## end cServer::cServer%1117174977.body
}


cServer::~cServer()
{
  //## begin cServer::~cServer%.body preserve=yes
   cTCPComm::ShutDownSocket(_Socket);
  //## end cServer::~cServer%.body
}



//## Other Operations (implementation)
INT_T cServer::onMain (void *extra)
{
  //## begin cServer::onMain%1117174978.body preserve=yes
   if (listen(_Socket, _MaxConnections) == -1) {
      int err = LastError();
      ErrorPrintf("failed to listen to port %d\n", _ListenerPort);
      return -1;
   } else {
      SOCKET incoming_socket = INVALID_SOCKET;
      socklen_t addr_size = 0;
      struct sockaddr_in remote_addr = {0};
      addr_size = sizeof(remote_addr);
      while (1) {
   	   incoming_socket = accept(_Socket, (struct sockaddr *)&remote_addr, &addr_size);
   	   if (incoming_socket != INVALID_SOCKET) {
	   	   InfoPrintf("accepted connection from %s\n", inet_ntoa(remote_addr. sin_addr));
            cServerThread * thread = new cServerThread(this, incoming_socket);
            thread->start();
         } else {
   		   ErrorPrintf("failed to accept: %s\n", ErrorString(SocketError()).c_str());
         }
      }
   }
  //## end cServer::onMain%1117174978.body
}

void cServer::Request (cStreamMsg &in_msg, cStreamMsg &out_msg)
{
  //## begin cServer::Request%1117174979.body preserve=yes
   out_msg.Allocate(in_msg.MsgLen());
   memcpy(out_msg.MsgBuf(), in_msg.MsgBuf(), out_msg.MsgLen());
  //## end cServer::Request%1117174979.body
}

void cServer::Initialize ()
{
  //## begin cServer::Initialize%1117174993.body preserve=yes
   struct protoent * protoentry = NULL;
   if ((protoentry = getprotobyname("tcp")) == NULL) {
	   ErrorPrintf("failed to get protocol: %s\n", ErrorString(SocketError()).c_str());
   } else {
      if ((_Socket = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
	      ErrorPrintf("failed to get socket: %s\n", ErrorString(SocketError()).c_str());
      } else {
         struct sockaddr_in ownaddress = {0};
         ownaddress.sin_family = AF_INET;
         ownaddress.sin_port = htons(_ListenerPort);	/* network byte order des Ports */
         ownaddress.sin_addr.s_addr = INADDR_ANY;
         if (bind(_Socket, (struct sockaddr *)&ownaddress, sizeof(ownaddress)) == -1) {
	         ErrorPrintf("failed to bind to port %d: %s\n",
                       _ListenerPort, ErrorString(SocketError()).c_str());
         }
      }
	}
  //## end cServer::Initialize%1117174993.body
}

//## Get and Set Operations for Class Attributes (implementation)

USHORT_T cServer::get_ListenerPort () const
{
  //## begin cServer::get_ListenerPort%42959BDE0313.get preserve=no
  return _ListenerPort;
  //## end cServer::get_ListenerPort%42959BDE0313.get
}

void cServer::set_ListenerPort (USHORT_T value)
{
  //## begin cServer::set_ListenerPort%42959BDE0313.set preserve=no
  _ListenerPort = value;
  //## end cServer::set_ListenerPort%42959BDE0313.set
}

ULONG_T cServer::get_MaxConnections () const
{
  //## begin cServer::get_MaxConnections%4296F0AC01C5.get preserve=no
  return _MaxConnections;
  //## end cServer::get_MaxConnections%4296F0AC01C5.get
}

void cServer::set_MaxConnections (ULONG_T value)
{
  //## begin cServer::set_MaxConnections%4296F0AC01C5.set preserve=no
  _MaxConnections = value;
  //## end cServer::set_MaxConnections%4296F0AC01C5.set
}

// Additional Declarations
  //## begin cServer%4295992400CA.declarations preserve=yes
  //## end cServer%4295992400CA.declarations

//## begin module%4295992400CA.epilog preserve=yes
//## end module%4295992400CA.epilog
