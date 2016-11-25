
#include "trivialframehandler.h"

cTrivialFrameHandler::cTrivialFrameHandler()
{
}

cTrivialFrameHandler::~cTrivialFrameHandler()
{
}

bool cTrivialFrameHandler::add(const OCTET_T * input, LENGTH_T inputLength, cByteBuffer & frame)
{
   cByteBuffer buffer(input, inputLength);
   frame = buffer;
   return true;
}

bool cTrivialFrameHandler::pack(const OCTET_T * data, LENGTH_T dataLength, cByteBuffer & frame)
{
   frame = cByteBuffer(data, dataLength);
   return true;
}




