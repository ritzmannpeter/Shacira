
#ifndef _cFrameHandler_h
#define _cFrameHandler_h

#include <malloc.h>
#include <string.h>
#define ALLOC(size) calloc(1,size)
#define FREE(mem) free(mem)

#define BUFFER_SIZE 0x8000

#include "cTransportHandler.h"

class cFrameHandler
{
public:
   cFrameHandler(cTransportHandler * transport_handler = NULL);
   virtual ~cFrameHandler();
   int SendFrame(const unsigned char * frame, unsigned long frame_length);
   int GetFrame(unsigned char * frame, unsigned long buf_size);
   int HandleInput(const unsigned char * input, unsigned long input_length);
   int SendBuffer(const unsigned char * buffer, unsigned long buffer_length);
   int ReceiveBuffer(unsigned char * buffer, unsigned long buffer_size, int timeout);
   void SetTransportHandler(cTransportHandler * th);
protected:
   int _State;
   unsigned long _BufferIndex;
   unsigned long _BufferSize;
   unsigned char * _Buffer;
   cTransportHandler * _TransportHandler;
   void * _ActFrame;
   unsigned long _ActFrameLength;
private:
   void Received();
};

#endif
