
#ifndef _cFrameHandler_h
#define _cFrameHandler_h

#include "cChunkBuffer.h"
#define CHUNK_SIZE   0x100

class cFrameHandler
{
public:
   cFrameHandler()  : _ChunkBuffer(CHUNK_SIZE) {};
   virtual ~cFrameHandler() {};
   virtual bool Input(unsigned char * data, int data_len, unsigned char * & raw_data, int & raw_data_len);
   virtual unsigned char * Output(const unsigned char * data, int data_len, int & frame_len);
protected:
   void AddChunk(unsigned char * chunk, int chunk_size);
   cChunkBuffer _ChunkBuffer;
};

#endif
