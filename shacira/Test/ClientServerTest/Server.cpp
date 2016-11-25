
#include "FirstHeader.h"
#include "System/ClientServer/cUDPComm.h"
#include "System/ClientServer/cInetAddress.h"
#include "System/ClientServer/cs.h"
#include "System/ClientServer/cServer.h"
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

int main(int argc, char* argv[])
{
   unsigned short send_port = 19000;
   unsigned short receive_port = 19001;
   const char * server_host = "localhost";
   if (argc == 2) {
      send_port = atoi(argv[1]);
      receive_port = send_port;
   } else if (argc == 3) {
      send_port = atoi(argv[1]);
      receive_port = atoi(argv[2]);
   } else {
      printf("usage:\n\tserver send_port [receive_port]\n");
      return 0;
   }
   printf("server at %d %d\n", send_port, receive_port);
   try {
      StartSockets();
      cInetAddress sender_address;
      cUDPComm comm(receive_port, send_port, server_host);
      cServer server(&comm);
      server.Start();
      while (!server.get_Terminated()) {
         Sleep(100);
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
