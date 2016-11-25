
#ifndef _cTCPConnectionHandler_h
#define _cTCPConnectionHandler_h

#include "cConnectionHandler.h"
#include "cTCPTransportHandler.h"
#include "cSocketApi.h"

class cTCPConnectionHandler : public cConnectionHandler
{
public:
   cTCPConnectionHandler(unsigned short port);
   virtual ~cTCPConnectionHandler();
   virtual cTransportHandler * Listen();
   virtual cTransportHandler * Connect();
   virtual void Disconnect();
protected:
   unsigned short _Port;
   SOCKET _Socket;
protected:
   bool NewSocket();
   void CloseSocket();
};

#endif
