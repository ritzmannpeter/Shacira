
#ifndef _cTCPTransportHandler_h
#define _cTCPTransportHandler_h

#include "cTransportHandler.h"
#include "cSocketApi.h"

class cTCPTransportHandler : public cTransportHandler
{
public:
   cTCPTransportHandler(SOCKET s, bool free_resources);
   virtual ~cTCPTransportHandler();
   virtual int SendBuffer(const unsigned char * buffer, unsigned long buffer_length);
   virtual int ReceiveBuffer(unsigned char * buffer, unsigned long buffer_size, int timeout);
protected:
   SOCKET _Socket;
   bool _FreeResources;
};

#endif
