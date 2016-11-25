
#include "FirstHeader.h"
#include "System/ClientServer/cUDPComm.h"
#include "System/ClientServer/cInetAddress.h"
#include "System/ClientServer/cs.h"
#include "cPPCDevice.h"
#include "stdio.h"
#include "string.h"

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

bool _Debug = false;

int main(int argc, char* argv[])
{
   unsigned short send_port = 19000;
   unsigned short receive_port = 19000;
   const char * server_host = NULL;
   for (ULONG_T arg=1; arg<argc; arg++) {
      if (strnicmp(argv[arg], "-r", 2) == 0) {
         receive_port = atol(&(argv[arg][2]));
      } else if (strnicmp(argv[arg], "-s", 2) == 0) {
         send_port = atol(&(argv[arg][2]));
      } else if (strnicmp(argv[arg], "-d", 2) == 0) {
         _Debug = true;
      } else if (stricmp(argv[arg], "-?") == 0) {
         printf("usage:\n\tppcserver options\n");
         printf("\toptions:\n");
         printf("\t-r<receive_port> port where the client is waiting for data (%d)\n", receive_port);
         printf("\t-s<send_port> port where the server is waiting for data (%d)\n", send_port);
         printf("\t-d switches to debug mode\n");
         printf("\t-? this text\n");
         return 0;
      }
   }
   printf("ppcserver at %d %d\n", send_port, receive_port);
   if (_Debug) printf("debug mode\n");
   try {
      StartSockets();
      cPPCDevice device(receive_port, send_port);
      device.Start();
      while (true) {
         Sleep(1000);
      }
      return 0;
   } catch (cSocketError e) {
      printf("socket error %d in function %s\n", e._SocketError, e._SocketFunction);
      return -1;
   } catch (...) {
      printf("unhandled exception\n");
      return -1;
   }
   return 0;
}
