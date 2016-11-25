
#ifdef lassma

#include "Client/GatewayInterface/cGatewayInterface.h"

static int _GatewayInitialized = 0;
static unsigned long _BufSize = 0x20000;
static char _CellName[0x200]; 

static void InitializeGatewayInterface()
{
   int err = 0;
   if (!_GatewayInitialized) {
      int err = GIInit(18001, 18000, "localhost");
      if (err >= 0 ||
          err == GATEWAY_INTERFACE_ALREADY_INITIALIZED) {
         _GatewayInitialized = 1;
      }
   }
}

#endif

#include "FirstHeader.h"
#include "System/ClientServer/cClient.h"
#include "System/ClientServer/cs.h"
#include "System/Sys/cSHFile.h"
#include "Client/GatewayInterface/cGatewayInterface.h"

#define REQUEST_TIMEOUT    1000

static void StartSockets()
{
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      throw cSocketError(err, "WSAStartup");
   }
   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */
   if (LOBYTE(wsa_data.wVersion) != 2 ||
       HIBYTE(wsa_data.wVersion) != 2) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      WSACleanup();
      throw cSocketError(-1, "invalid socket library");
   }
}

static char _Buf[0x50000] = {0};
static char _ResponseBuf[0x50000] = {0};
static STRING_T _FileBuf;
#define MSG_SIZE  499

int main(int argc, char ** argv)
{
   cSHFile file("e:\\temp\\client.txt");
   _FileBuf = file.ToString();
   int buf_size = _FileBuf.size();
   if (buf_size == 0) {
      return 0;
   } else {
      printf("buf size is %d\n", buf_size);
   }
   StartSockets();
   cClient client(20000, "winkie");
   int retries = 1000000;
   cStreamMsg req((void*)_FileBuf.c_str(), _FileBuf.size());
   cStreamMsg rep;
   for (int i=0; i<100000; i++) {
      int rc = client.Request(req, rep, i);
      if (rc == 0) {
         if (memcmp(rep.MsgBuf(), _FileBuf.c_str(), rep.MsgLen()) == 0) {
            printf("received %d bytes\n", rep.MsgLen());
            Sleep(10);
         } else {
            printf("verify error\n");
         }
      } else {
         printf("failed to request: %d\n", rc);
      }
   }
   printf("press any key\n");
   int dummy = getchar();
   return 0;
}

