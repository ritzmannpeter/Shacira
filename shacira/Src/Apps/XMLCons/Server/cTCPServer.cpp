
#include "cTCPServer.h"
#include "cServiceHandler.h"
#include "cService.h"
#include <stdio.h>

int cTCPServer::Start()
{
   SOCKET s;
   struct protoent * protoentry = NULL;
   printf("receiving on port %d\n", _Port);
   if ((protoentry = getprotobyname("tcp")) == NULL)	{
	   printf("failed to get protocol\n");
	   return 1;
	}
   if ((s = cSocketApi::Socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
	   printf("failed to get socket\n");
	   return 1;
	}
   int on = 1;
   if (cSocketApi::SetSockOpt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
	   printf("failed to reuse socket\n");
	   return(1);
   }
   struct sockaddr_in ownaddress = {0};
   ownaddress.sin_family = AF_INET;
   ownaddress.sin_port = htons(_Port);
   ownaddress.sin_addr.s_addr = INADDR_ANY;

	/* bind socket */
	printf("bind(%s)...\n", inet_ntoa(ownaddress.sin_addr));
	if (cSocketApi::Bind(s, (struct sockaddr *)&ownaddress, sizeof(ownaddress)) == -1) {
	   printf("failed to bind\n");
	   return(1);
	}
   printf("service succesfully bound to port %d\n", _Port);

	/* accept and recvfrom expect int-pointers ... */
	struct sockaddr_in remoteaddress = {0};
	int address_length = sizeof(remoteaddress);

	/* initialize remoteaddress */
	memset(&remoteaddress, 0, sizeof(remoteaddress));

	/* listen for connection attempts */
	if (cSocketApi::Listen(s, _MaxConnections) == -1) {
		printf("failed to listen\n");
		return 1;
   }
   printf("listening (max %d connections)\n", _MaxConnections);

   /* someone tries to connect */
   while (true) {
//   	printf("now accepting...\n");
      SOCKET incoming_socket = cSocketApi::Accept(s, (struct sockaddr *)&remoteaddress, &address_length);
   	if (incoming_socket > 0) {
//	   	printf("accepted connection from %s\n", inet_ntoa(remoteaddress.sin_addr));
         cServiceHandler * handler = new cServiceHandler(this, incoming_socket, _Service);
         if (!handler->Start()) {
      		printf("failed to start service\n");
         } else {
//      		printf("started service on %d\n", incoming_socket);
         }
      } else {
   		printf("failed to accept ...\n");
      }
   }
   cSocketApi::CloseSocket(s);
   while (42) {
      Sleep(1000);
   }
   return 0;
}

