
#ifndef _cBinaryFrameHandler_h
#define _cBinaryFrameHandler_h

#include "cFrameHandler.h"

class cBinaryFrameHandler : public cFrameHandler
{
public:
   cBinaryFrameHandler();
   virtual ~cBinaryFrameHandler();
   virtual bool Input(unsigned char * data, int data_len, unsigned char * & raw_data, int & raw_data_len);
   virtual unsigned char * Output(const unsigned char * data, int data_len, int & frame_len);
private:
   bool HandleInput(const unsigned char * input, unsigned long input_length);
private:
   int _State;
   unsigned long _BufferIndex;
   unsigned long _BufferSize;
   unsigned char _Buffer[CHUNK_SIZE];
};

#endif
