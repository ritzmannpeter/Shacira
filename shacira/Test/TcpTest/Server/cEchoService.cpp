
#include "cEchoService.h"
#include <stdio.h>

cEchoService::cEchoService(cConnectionHandler * ch, cFrameHandler * fh)
   : cServiceHandler(ch, fh)
{
}

cEchoService::~cEchoService()
{
}

static int requests = 0;

int cEchoService::HandleRequest(void * in_frame, unsigned long in_length,
                                void * out_frame, unsigned long * out_length)
{
if (requests++ % 100 == 0) {
   printf("%d\n", requests);
}
   int nbytes = in_length;
   memcpy(out_frame, in_frame, nbytes);
   *out_length = in_length;
   return 0;
}

int cEchoService::Request(void * out_frame, unsigned long out_length,
                          void * in_frame, unsigned long *in_length)
{
if (requests++ % 100 == 0) {
   printf("%d\n", requests);
}
   int rc = _FrameHandler->SendFrame((unsigned char *)out_frame, out_length);
   if (rc == 0) {
      rc = _FrameHandler->GetFrame((unsigned char *)in_frame, out_length);
      *in_length = rc;
   }
   return rc;
}





