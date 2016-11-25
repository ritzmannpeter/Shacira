
#ifndef _cServiceHandler_h
#define _cServiceHandler_h

#include "cConnectionHandler.h"
#include "cFrameHandler.h"
#include "cTransportHandler.h"

class cServiceHandler
{
public:
   cServiceHandler(cConnectionHandler * ch, cFrameHandler * fh, bool hold_connection = false);
   virtual ~cServiceHandler();
   virtual bool Connect();
   virtual void Disconnect();
   virtual bool Start();
   virtual bool Stop();
   virtual bool ServiceRequests();
   virtual int HandleRequest(void * in_frame, unsigned long in_length,
                             void * out_frame, unsigned long * out_length) = 0;
   virtual int Request(void * out_frame, unsigned long out_length,
                       void * in_frame, unsigned long * in_length) = 0;
protected:
   bool _HoldConnection;
   cConnectionHandler * _ConnectionHandler;
   cTransportHandler * _TransportHandler;
   cFrameHandler * _FrameHandler;
};

#endif
