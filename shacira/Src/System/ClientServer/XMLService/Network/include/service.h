
#ifndef _service_h
#define _service_h

#include "comm.h"
#include "framehandler.h"
#include "session.h"
#include "client.h"

class COMM_EXPORT cService
{
public:
   cService(cDriver * driver, cSession * session);
   cService(cDriver * driver, cClient * client);
   virtual ~cService();
   int send(const OCTET_T * output, LENGTH_T length);
   void handleInput(const OCTET_T * input, LENGTH_T inputLength);
   virtual void handleFrame(const cByteBuffer & buffer) = 0;
   virtual int request(const cByteBuffer & request, cByteBuffer & reply) = 0;
   inline cFrameHandler * frameHandler() const {return _frameHandler;};
   inline void setFrameHandler(cFrameHandler * frameHandler) {_frameHandler = frameHandler;};
protected:
   cFrameHandler * _frameHandler;
   cSession * _session;
   cClient * _client;
};

#endif // _service_h_
