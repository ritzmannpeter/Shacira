
#include "cSocketApi.h"
#include "cTCPConnectionHandler.h"
#include "cFrameHandler.h"
#include "cEchoService.h"
#include <stdio.h>

int main(int argc, char **argv)
{
   bool connected = false;
   int i = 0;
   char buffer[0x200] = {0};
   cFrameHandler * fh = new cFrameHandler;
   cConnectionHandler * ch = new cTCPConnectionHandler(20000);
   cServiceHandler * sh = new cEchoService(ch, fh);
   while (true) {
      if (!connected) {
         sh->Connect();
         connected = true;
      }
      if (sh->Connect()) {
         char text[0x200] = {0};
         sprintf(text, "hallo %d", ++i);
         unsigned long in_length = 0;
         int rc = sh->Request(text, strlen(text), buffer, &in_length);
         if (rc > 0) {
//            printf("sent %s\n", text);
//            printf("got %s\n", buffer);
         } else {
            printf("failed %s:%d\n", text, rc);
            sh->Disconnect();
            connected = false;
         }
      }
   }
   return 0;
}

#ifdef lassma
   const char * ip_address = "127.0.0.1";
   if (argc == 2) {
      ip_address = argv[1];
   }
   int port = 20000;
   struct protoent *protoentry;
   int sockhandle;
   struct sockaddr_in address;
   int address_length;
   char buffer[1024];
   char read_buffer[1024];

#ifdef WIN32
   WORD wVersionRequested;
   WSADATA wsaData;
#endif

   address_length = sizeof(address);

/* Windows Sockets muessen explizit initialisiert werden */
#ifdef WIN32
   wVersionRequested = MAKEWORD( 2, 2 );
   if (WSAStartup( wVersionRequested, &wsaData ) != 0)	{
	   printf("failed to initialize winsock\n");
	   return(0);
	}
#endif


/* brauchen wir nachher fuer den Socket-Call */
   if ((protoentry = getprotobyname("tcp")) == NULL) {
	   printf("failed to get protocol: %s\n", ErrString(LastError()));
	   return(1);
	}

/* Socket anlegen */
   if ((sockhandle = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == -1) {
	   printf("failed to get socket: %s\n", ErrString(LastError()));
	   return(1);
	}

   address.sin_family = AF_INET;
   address.sin_port = htons(port);	/* network byte order des Ports */
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_addr.s_addr = inet_addr(ip_address);

   while (!Connect(sockhandle, &address)) {
   }

   /* Daten verschicken: interaktiv, kann auch per Umleitung erfolgen */
   cTCPFrameHandler handler(sockhandle);
   int count = 0;
   int nread = 0;
   struct sockaddr_in remoteaddress;
   int remote_length = sizeof(remoteaddress);
   while (1) {
	   memset(buffer, 0, 1024);
      sprintf(buffer, "%d", count);
      int length = strlen(buffer);
      handler.SendFrame((const unsigned char *)buffer, length);
      bool received = false;
      while (nread > 0 && !received) {
         nread = recvfrom(sockhandle,
                          read_buffer, length, 0,
                          (struct sockaddr *)&remoteaddress, &remote_length);
         received = handler.HandleInput((const unsigned char *)read_buffer, nread);
      }
      count++;
	}

/* schliessen */
#ifdef WIN32
   shutdown(sockhandle, SD_BOTH);
#endif
#ifdef UNIX
   shutdown(sockhandle, SHUT_RDWR);
#endif

/* Ende */
return(0);
}


#ifdef lassma

/*
ein TCP-Sender

$Date: 2004/08/29 15:07:53 $
$Revision: 1.1 $

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#ifdef WIN32
#include <winsock2.h>
#endif

int LastError()
{
#ifdef WIN32
   return WSAGetLastError();
#else
   return errno;
#endif
}

static char _ErrText[512];
static const char * ErrString(int err_code)
{
   sprintf(_ErrText, "e %d", err_code);
   return _ErrText;
}

#ifdef UNIX
#include <netdb.h>
#include <sys/socket.h>
#endif

static bool Connect(int socket, struct sockaddr_in * address)
{
   if (connect(socket, (struct sockaddr *)address, sizeof(*address)) == -1) {
	   printf("failed to connect: %s\n", ErrString(LastError()));
      Sleep(1000);
      return false;
   } else {
      return true;
   }
}

int main(int argc, char **argv)
{
   const char * ip_address = "127.0.0.1";
   if (argc == 2) {
      ip_address = argv[1];
   }
   int port = 20000;
   struct protoent *protoentry;
   int sockhandle;
   struct sockaddr_in address;
   int address_length;
   char buffer[1024];
   char read_buffer[1024];

#ifdef WIN32
   WORD wVersionRequested;
   WSADATA wsaData;
#endif

   address_length = sizeof(address);

/* Windows Sockets muessen explizit initialisiert werden */
#ifdef WIN32
   wVersionRequested = MAKEWORD( 2, 2 );
   if (WSAStartup( wVersionRequested, &wsaData ) != 0)	{
	   printf("failed to initialize winsock\n");
	   return(0);
	}
#endif


/* brauchen wir nachher fuer den Socket-Call */
   if ((protoentry = getprotobyname("tcp")) == NULL) {
	   printf("failed to get protocol: %s\n", ErrString(LastError()));
	   return(1);
	}

/* Socket anlegen */
   if ((sockhandle = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == -1) {
	   printf("failed to get socket: %s\n", ErrString(LastError()));
	   return(1);
	}

   address.sin_family = AF_INET;
   address.sin_port = htons(port);	/* network byte order des Ports */
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_addr.s_addr = inet_addr(ip_address);

   while (!Connect(sockhandle, &address)) {
   }

   /* Daten verschicken: interaktiv, kann auch per Umleitung erfolgen */
   int count = 0;
   int nread = 0;
   struct sockaddr_in remoteaddress;
   int remote_length = sizeof(remoteaddress);
   while (1) {
	   memset(buffer, 0, 1024);
      sprintf(buffer, "%d", count);
      int length = strlen(buffer);
      int nsend = send(sockhandle, buffer, length, 0);
      if (nsend == length) {
         memset(read_buffer, 0, sizeof(buffer));
         nread = recvfrom(sockhandle,
		                    read_buffer, length, 0,
                          (struct sockaddr *)&remoteaddress, &remote_length);
         if (nread == length) {
            if (memcmp(buffer, read_buffer, length) == 0) {
               printf("okay %s\n", buffer);
            } else {
               printf("verify failed\n");
            }
         } else {
            int err = WSAGetLastError();
            if (err != 0) {
         	   printf("failed to receive: %s\n", ErrString(LastError()));
               shutdown(sockhandle, SD_BOTH);
               if ((sockhandle = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == -1) {
	               printf("failed to get socket: %s\n", ErrString(LastError()));
	               return(1);
	            }
               while (!Connect(sockhandle, &address)) {
               }
            }
         }
      } else {
   	   printf("failed to send: %s\n", ErrString(LastError()));
         shutdown(sockhandle, SD_BOTH);
         if ((sockhandle = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == -1) {
            printf("failed to get socket: %s\n", ErrString(LastError()));
	         return(1);
	      }
         while (!Connect(sockhandle, &address)) {
         }

      }
//      Sleep(10);
      count++;
	}

/* schliessen */
#ifdef WIN32
   shutdown(sockhandle, SD_BOTH);
#endif
#ifdef UNIX
   shutdown(sockhandle, SHUT_RDWR);
#endif

/* Ende */
return(0);
}

#endif


#endif

