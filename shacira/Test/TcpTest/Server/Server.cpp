
#include "cSocketApi.h"
#include "cTCPConnectionHandler.h"
#include "cFrameHandler.h"
#include "cEchoService.h"
#include <stdio.h>

int main(int argc, char **argv)
{
   cFrameHandler * fh = new cFrameHandler;
   cConnectionHandler * ch = new cTCPConnectionHandler(20000);
   cServiceHandler * sh = new cEchoService(ch, fh);
   sh->Start();
   

#ifdef lassma
   unsigned short port = 20000;
   SOCKET s;
   struct protoent * protoentry = NULL;
   printf("receiver on port %d\n", port);
   if ((protoentry = getprotobyname("tcp")) == NULL)	{
	   printf("failed to get protocol\n");
	   return 1;
	}
   if ((s = cSocketApi::Socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
	   printf("failed to get socket+\n");
	   return 1;
	}
   int on = 1;
   if (cSocketApi::SetSockOpt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
	   printf("failed to reuse socket\n");
	   return(1);
   }
   struct sockaddr_in ownaddress = {0};
   ownaddress.sin_family = AF_INET;
   ownaddress.sin_port = htons(port);
   ownaddress.sin_addr.s_addr = INADDR_ANY;

   /* Socket an unsere eigene Adresse haengen */
   printf("bind(%s)...\n", inet_ntoa(ownaddress.sin_addr));
   if (cSocketApi::Bind(s, (struct sockaddr *)&ownaddress, sizeof(ownaddress)) == -1) {
	   printf("failed to bind\n");
	   return(1);
	}

   /* da accept und recvfrom int-Pointer verwenden ... */
   struct sockaddr_in remoteaddress = {0};
   int address_length = sizeof(remoteaddress);

   /* vorbelegen */
   memset(&remoteaddress, 0, sizeof(remoteaddress));

/* abhoeren: genau eine Verbindung */
	printf("listen()...\n");
   if (cSocketApi::Listen(s, 5) == -1) {
		printf("failed to listen\n");
		return 1;
   }

/* da will einer rein */
   while (1) {
   	printf("now accepting...\n");
      SOCKET incoming_socket = cSocketApi::Accept(s, (struct sockaddr *)&remoteaddress, &address_length);
   	if (incoming_socket > 0) {
	   	printf("accepted connection from %s\n", inet_ntoa(remoteaddress.sin_addr));
//         cWorkerThread * thread = new cWorkerThread(incoming_socket);
//         thread->start();
      } else {
   		printf("failed to accept\n");
      }
   }
   cSocketApi::CloseSocket(s);
   while (42) {
      Sleep(1000);
   }
#endif
   return 0;
}

