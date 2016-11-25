//## begin module%42959917003F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42959917003F.cm

//## begin module%42959917003F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%42959917003F.cp

//## Module: cClient%42959917003F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cClient.cpp

//## begin module%42959917003F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%42959917003F.additionalIncludes

//## begin module%42959917003F.includes preserve=yes
//## end module%42959917003F.includes

// cClient
#include "System/ClientServer/cClient.h"
//## begin module%42959917003F.additionalDeclarations preserve=yes
//## end module%42959917003F.additionalDeclarations


// Class cClient 






cClient::cClient()
  //## begin cClient::cClient%.hasinit preserve=no
      : _ServerPort(0), _ServerHost("localhost"), _Socket(INVALID_SOCKET), _Connected(false)
  //## end cClient::cClient%.hasinit
  //## begin cClient::cClient%.initialization preserve=yes
  //## end cClient::cClient%.initialization
{
  //## begin cClient::cClient%.body preserve=yes
   Initialize();
  //## end cClient::cClient%.body
}

cClient::cClient(const cClient &right)
  //## begin cClient::cClient%copy.hasinit preserve=no
      : _ServerPort(0), _ServerHost("localhost"), _Socket(INVALID_SOCKET), _Connected(false)
  //## end cClient::cClient%copy.hasinit
  //## begin cClient::cClient%copy.initialization preserve=yes
  //## end cClient::cClient%copy.initialization
{
  //## begin cClient::cClient%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cClient::cClient%copy.body
}

cClient::cClient (USHORT_T server_port, CONST_STRING_T server_host)
  //## begin cClient::cClient%1117174981.hasinit preserve=no
      : _ServerPort(0), _ServerHost("localhost"), _Socket(INVALID_SOCKET), _Connected(false)
  //## end cClient::cClient%1117174981.hasinit
  //## begin cClient::cClient%1117174981.initialization preserve=yes
  //## end cClient::cClient%1117174981.initialization
{
  //## begin cClient::cClient%1117174981.body preserve=yes
   _ServerHost = server_host;
   _ServerPort = server_port;
   Initialize();
  //## end cClient::cClient%1117174981.body
}


cClient::~cClient()
{
  //## begin cClient::~cClient%.body preserve=yes
   cTCPComm::ShutDownSocket(_Socket);
  //## end cClient::~cClient%.body
}



//## Other Operations (implementation)
int cClient::Request (cStreamMsg &in_msg, cStreamMsg &out_msg, ULONG_T request_id)
{
  //## begin cClient::Request%1117174982.body preserve=yes
   int retries = 3;
   Connect();
   while (!_Connected && retries--) {
      Connect();
   }
   if (!_Connected) {
      return -1;
   } else {
      int nread = 0;
      int nsend = 0;
      if (in_msg.MsgLen() > 0 && in_msg.MsgBuf() != NULL) {
         nsend = cTCPComm::SendMsg(_Socket, in_msg, request_id);
         if (nsend < 0) {
            int last_error = LastError();
            if (last_error == WSAECONNRESET ||
                last_error == WSAECONNABORTED) {
               _Connected = false;
            }
            ErrorPrintf("client request: failed to send %d\n", last_error);
            return -1;
         }
      }
      nread = cTCPComm::ReceiveMsg(_Socket, out_msg, request_id);
      if (nread < 0) {
         int last_error = LastError();
         if (last_error == WSAECONNRESET ||
             last_error == WSAECONNABORTED) {
            _Connected = false;
         } else if (last_error == ERR_RECEIVED_MSG_TOO_SHORT) {
            int dummy = 0;
         }
         ErrorPrintf("client request: failed to receive %d\n", last_error);
         return -1;
      }
      return 0;
   }
  //## end cClient::Request%1117174982.body
}

void cClient::Initialize ()
{
  //## begin cClient::Initialize%1117174987.body preserve=yes
   struct protoent * protoentry = NULL;
   if ((protoentry = getprotobyname("tcp")) == NULL) {
      ErrorPrintf("failed to get protocol: %s\n", ErrorString(SocketError()).c_str());
   } else {
      if ((_Socket = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
	      ErrorPrintf("failed to get socket: %s\n", ErrorString(SocketError()).c_str());
      }
	}
  //## end cClient::Initialize%1117174987.body
}

INT_T cClient::Connect ()
{
  //## begin cClient::Connect%1117174983.body preserve=yes
   if (_Connected) {
      return 0;
   }
   struct hostent * host_entry = gethostbyname(_ServerHost.c_str());
   if (host_entry != NULL) {
      struct sockaddr_in server_address = {0};
      server_address.sin_family = AF_INET;
      server_address.sin_family = AF_INET;
      server_address.sin_port = htons(_ServerPort);
      server_address.sin_addr.s_addr = INADDR_ANY;
      memcpy((char *)&(server_address).sin_addr,
             (char *)host_entry->h_addr,
             host_entry->h_length);
      if (connect(_Socket, (struct sockaddr *)&server_address, sizeof(server_address)) != -1) {
         _Connected = true;
         return 0;
      } else {
         int err = SocketError();
         if (err == WSAEISCONN) {
            cTCPComm::ShutDownSocket(_Socket);
            struct protoent * protoentry = NULL;
            if ((protoentry = getprotobyname("tcp")) == NULL) {
	            ErrorPrintf("failed to get protocol for connection: %s\n", ErrorString(SocketError()).c_str());
               return -1;
            }
            if ((_Socket = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
               int err = SocketError();
	            ErrorPrintf("failed to get socket for reconnection: %s\n", ErrorString(err).c_str());
               return err;
            }
            return 0;
         }
         ErrorPrintf("failed to connect to host %s port %d: %s\n",
                    _ServerHost.c_str(), (int)_ServerPort, ErrorString(err).c_str());
         cSystemUtils::Suspend(1000);
         return err;
      }
   } else {
      int err = SocketError();
      ErrorPrintf("cannot resolve host name %s: %s\n",
                 _ServerHost.c_str(), ErrorString(err).c_str());
      return err;
   }
  //## end cClient::Connect%1117174983.body
}

//## Get and Set Operations for Class Attributes (implementation)

USHORT_T cClient::get_ServerPort () const
{
  //## begin cClient::get_ServerPort%42959AF000B8.get preserve=no
  return _ServerPort;
  //## end cClient::get_ServerPort%42959AF000B8.get
}

void cClient::set_ServerPort (USHORT_T value)
{
  //## begin cClient::set_ServerPort%42959AF000B8.set preserve=no
  _ServerPort = value;
  //## end cClient::set_ServerPort%42959AF000B8.set
}

STRING_T cClient::get_ServerHost () const
{
  //## begin cClient::get_ServerHost%42959B18015F.get preserve=no
  return _ServerHost;
  //## end cClient::get_ServerHost%42959B18015F.get
}

void cClient::set_ServerHost (STRING_T value)
{
  //## begin cClient::set_ServerHost%42959B18015F.set preserve=no
  _ServerHost = value;
  //## end cClient::set_ServerHost%42959B18015F.set
}

// Additional Declarations
  //## begin cClient%42959917003F.declarations preserve=yes
  //## end cClient%42959917003F.declarations

//## begin module%42959917003F.epilog preserve=yes
//## end module%42959917003F.epilog
