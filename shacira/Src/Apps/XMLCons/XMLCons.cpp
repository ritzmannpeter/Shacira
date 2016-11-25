
#include "FirstHeader.h"
#include "cSocketApi.h"
#include "cTCPServer.h"
#include "cService.h"
#include "cXMLService.h"
#include "cBinaryFrameHandler.h"
#include "cProcessWrapper.h"
#include "System/Database/cBinaryObject.h"

#undef test_bin
#ifdef test_bin
static char test_data[0x20000] = "zum testen";
static void new_obj1(cBinaryObject & obj)
{
   cBinaryObject o((unsigned char*)test_data, strlen(test_data));
   obj = o;
}

cBinaryObject new_obj2()
{
   cBinaryObject o((unsigned char*)test_data, strlen(test_data));
   return o;
}
#endif

int main(int argc, char **argv)
{
#ifdef test_bin
   int ocount = 0;
   {
      cBinaryObject o1((BINARY_OBJECT_T)(&main), 55);
      ocount = _BinaryObjects;
      cBinaryObject o2 = o1;
      ocount = _BinaryObjects;
      cBinaryObject o3((BINARY_OBJECT_T)(&main), 50);
      ocount = _BinaryObjects;
      o2 = o3;
      ocount = _BinaryObjects;
      new_obj1(o2);
      ocount = _BinaryObjects;
      o2 = new_obj2();
      ocount = _BinaryObjects;
      cBinaryObject * objs[2000] = {0};
      for (int i=0; i<2000; i++) {
         objs[i] = new cBinaryObject((unsigned char*)test_data+i, i+1);
      }
      for (i=0; i<2000; i++) {
         cBinaryObject o = *objs[i];
         char * data = (char*)o.Data();
         int dummy = 0;
      }
      for (i=0; i<2000; i++) {
         delete objs[i];
      }
   }
   ocount = _BinaryObjects;
   return 0;
#else
   cProcessWrapper::_Argc = argc;
   cProcessWrapper::_Argv = argv;
   cProcessWrapper::Start();
   unsigned short port = 20000;
   int max_connections = 10;
   cService * service = new cXMLService;
   cFrameHandler * frame_handler = new cBinaryFrameHandler;
   service->SetFrameHandler(frame_handler);
   cTCPServer server(port, max_connections, service);
   service->SetServer(&server);
   int rc = server.Start();
   return rc;
#endif
}


