
#include "cTCPServer.h"
#include "cServiceHandler.h"
#include "cFrameHandler.h"
#include "cService.h"
#include "cAlloc.h"
#include <stdio.h>

int cService::Request(const unsigned char * request, int request_len, unsigned char * & response, int & response_len)
{
   response = (unsigned char*)cAlloc::Alloc(request_len+1);
   response_len = request_len;
   memcpy(response, request, response_len);
   return response_len;
}

