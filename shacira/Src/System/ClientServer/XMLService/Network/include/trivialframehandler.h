
#ifndef _trivialframehandler_h
#define _trivialframehandler_h

#include "framehandler.h"

class COMM_EXPORT cTrivialFrameHandler : public cFrameHandler
{
public:
   cTrivialFrameHandler();
   virtual ~cTrivialFrameHandler();
   virtual bool add(const OCTET_T * input, LENGTH_T inputLength, cByteBuffer & frame);
   virtual bool pack(const OCTET_T * data, LENGTH_T dataLength, cByteBuffer & frame);
};

#endif // _trivialframehandler_h_
