
#ifndef _cTCPFrameHandler_h
#define _cTCPFrameHandler_h

#include "cFrameHandler.h"
#include <windows.h>

class cTCPFrameHandler : public cFrameHandler
{
public:
   cTCPFrameHandler(SOCKET socket);
   virtual ~cTCPFrameHandler();
   virtual bool SendBuffer(const unsigned char * buffer, unsigned long buffer_length);
   virtual bool FrameReceived(const unsigned char * frame, unsigned long frame_length);
private:
   SOCKET _Socket;
};

#endif
