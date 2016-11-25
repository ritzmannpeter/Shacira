
#include "cTCPConnectionHandler.h"
#include <stdio.h>

cTCPConnectionHandler::cTCPConnectionHandler(unsigned short port)
{
   _Port = port;
   _Socket = INVALID_SOCKET;
}

cTCPConnectionHandler::~cTCPConnectionHandler()
{
   CloseSocket();
}

cTransportHandler * cTCPConnectionHandler::Listen()
{
   if (NewSocket()) {
      struct sockaddr_in ownaddress = {0};
      ownaddress.sin_family = AF_INET;
      ownaddress.sin_port = htons(_Port);
      ownaddress.sin_addr.s_addr = INADDR_ANY;
      if (cSocketApi::Bind(_Socket, (struct sockaddr *)&ownaddress, sizeof(ownaddress)) == -1) {
         return NULL;
	   }
      struct sockaddr_in remoteaddress = {0};
      int address_length = sizeof(remoteaddress);
      if (cSocketApi::Listen(_Socket, 5) == -1) {
         return NULL;
      } else {
         SOCKET incoming_socket = cSocketApi::Accept(_Socket, (struct sockaddr *)&remoteaddress, &address_length);
         printf("new connection from %s\n", inet_ntoa(((struct sockaddr_in *)(&remoteaddress))->sin_addr));
         cTransportHandler * th = new cTCPTransportHandler(incoming_socket, true);
         return th;
      }
   } else {
      return NULL;
   }
}

cTransportHandler * cTCPConnectionHandler::Connect()
{
   if (NewSocket()) {
      struct sockaddr_in address = {0};
      int address_length = sizeof(address);
      address.sin_family = AF_INET;
      address.sin_port = htons(_Port);
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_addr.s_addr = inet_addr("127.0.0.1");
      if (cSocketApi::Connect(_Socket, (struct sockaddr *)&address, address_length) == -1) {
         return NULL;
      } else {
         printf("new connection\n");
         cTransportHandler * th = new cTCPTransportHandler(_Socket, false);
         return th;
      }
   } else {
      return NULL;
   }
}

void cTCPConnectionHandler::Disconnect()
{
   CloseSocket();
Sleep(10);
}

bool cTCPConnectionHandler::NewSocket()
{
   CloseSocket();
   struct protoent * protoentry = NULL;
   if ((protoentry = getprotobyname("tcp")) == NULL)	{
      return false;
   }
   if ((_Socket = cSocketApi::Socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
      return false;
	}
   int on = 1;
   if (cSocketApi::SetSockOpt(_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
      CloseSocket();
      return false;
   } else {
      return true;
   }
}

void cTCPConnectionHandler::CloseSocket()
{
   if (_Socket != INVALID_SOCKET) {
      cSocketApi::CloseSocket(_Socket);
      _Socket = INVALID_SOCKET;
   }
}


