
#ifndef _framehandler_h
#define _framehandler_h

#include "comm.h"
#include "bytebuffer.h"

class COMM_EXPORT cFrameHandler
{
public:
   cFrameHandler();
   virtual ~cFrameHandler();
   virtual bool add(const OCTET_T * input, LENGTH_T inputLength, cByteBuffer & frame) = 0;
   virtual bool pack(const OCTET_T * data, LENGTH_T dataLength, cByteBuffer & frame) = 0;
};

#endif // _framehandler_h_
