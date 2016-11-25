
#include "FirstHeader.h"
#include "System/ClientServer/cUDPComm.h"
#include "System/ClientServer/cInetAddress.h"
#include "System/ClientServer/cs.h"
#include "System/ClientServer/cClient.h"
#include "stdio.h"
#include "string.h"

static char _InBuf[1024] = {0};
static char _OutBuf[1024] = {0};

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
   } else if (argc == 4) {
      send_port = atoi(argv[1]);
      receive_port = atoi(argv[2]);
      server_host = argv[3];
   } else {
      printf("usage:\n\tclient send_port [receive_port] [host]\n");
      return 0;
   }
   printf("client at %d %d %s\n", send_port, receive_port, server_host);
   try {
      StartSockets();
      cInetAddress send_address(send_port, server_host);
      cInetAddress sender_address;
      cUDPComm comm(receive_port, send_port);
      cClient client(&comm);
      client.Start();
      unsigned long i = 0;
      while (42) {
         memset(_InBuf, 0, sizeof(_InBuf));
         memset(_OutBuf, 0, sizeof(_OutBuf));
         sprintf(_OutBuf, "hallo is bins %d halt laenger als angenommen", i);
         cCSMsg send_msg(_OutBuf, sizeof(_OutBuf));
         send_msg.SetMsgLen(sizeof(_OutBuf) - (rand() % 500));
         client.Send(&send_msg, &send_address);
         ULONG_T msg_size = client.GetMessage(_InBuf, sizeof(_InBuf), 1000, 0);
         if (msg_size > 0) {   
printf("got %s %d bytes\n", _InBuf, msg_size);
         } else {
printf("timeout\n");
         }
Sleep(10);
         i++;
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
