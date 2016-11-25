
#include "cTCPTransportHandler.h"

cTCPTransportHandler::cTCPTransportHandler(SOCKET s, bool free_resources)
{
   _Socket = s;
   _FreeResources = free_resources;
}

cTCPTransportHandler::~cTCPTransportHandler()
{
   if (_FreeResources) {
      cSocketApi::CloseSocket(_Socket);
   }
}

int cTCPTransportHandler::SendBuffer(const unsigned char * buffer, unsigned long buffer_length)
{
   return cSocketApi::Send(_Socket, (const char *)buffer, buffer_length, 0);
}

int cTCPTransportHandler::ReceiveBuffer(unsigned char * buffer, unsigned long buffer_size, int timeout)
{
   int rc = cSocketApi::SetReceiveTimeout(_Socket, timeout);
   int nread = cSocketApi::Recv(_Socket, (char *)buffer, buffer_size, 0);
   if (nread > 0) {
      return nread;
   } else if (nread == 0) {
return -1;
      return nread;
   } else {
      return cSocketApi::SocketError();;
   }
}

