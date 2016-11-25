
#ifndef _binaryframehandler_h
#define _binaryframehandler_h

#include "framehandler.h"
#include "chunkbuffer.h"

#define CHUNK_SIZE   0x2000

class COMM_EXPORT cBinaryFrameHandler : public cFrameHandler
{
public:
   cBinaryFrameHandler();
   virtual ~cBinaryFrameHandler();
   virtual bool add(const OCTET_T * input, LENGTH_T inputLength, cByteBuffer & frame);
   virtual bool pack(const OCTET_T * data, LENGTH_T dataLength, cByteBuffer & frame);
private:
   bool input(const OCTET_T * data, LENGTH_T dataLen, cByteBuffer & buffer);
   cByteBuffer output(const OCTET_T * data, LENGTH_T dataLen);
   bool handleInput(const OCTET_T * input, LENGTH_T inputLength);
private:
   int _state;
   unsigned long _bufferIndex;
   unsigned long _bufferSize;
   unsigned char _buffer[CHUNK_SIZE];
   cChunkBuffer _inputBuffer;
};

#endif // _binaryframehandler_h_
