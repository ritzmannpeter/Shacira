
#include "cTCPFrameHandler.h"

cTCPFrameHandler::cTCPFrameHandler(SOCKET socket)
{
   _Socket = socket;
}

cTCPFrameHandler::~cTCPFrameHandler()
{
}

bool cTCPFrameHandler::SendBuffer(const unsigned char * buffer, unsigned long buffer_length)
{
   int nsend = send(_Socket, (const char *)buffer, buffer_length, 0);
   return true;
}

bool cTCPFrameHandler::FrameReceived(const unsigned char * frame, unsigned long frame_length)
{
   return true;
}

