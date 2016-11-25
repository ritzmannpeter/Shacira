
#include "cSocketApi.h"
#include "cBinaryFrameHandler.h"
#include "cAlloc.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

static char temp[0x1000] = {0};
const char * SocketErrorString(int err)
{
   if (err < 0) {
      err = -err;
   }
   switch (err) {
   case WSAEINTR: return "WSAEINTR";
   case WSAEBADF: return "WSAEBADF";
   case WSAEACCES: return "WSAEACCES";
   case WSAEFAULT: return "WSAEFAULT";
   case WSAEINVAL: return "WSAEINVAL";
   case WSAEMFILE: return "WSAEMFILE";
/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
   case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK";
   case WSAEINPROGRESS: return "WSAEINPROGRESS";
   case WSAEALREADY: return "WSAEALREADY";
   case WSAENOTSOCK: return "WSAENOTSOCK";
   case WSAEDESTADDRREQ: return "WSAEDESTADDRREQ";
   case WSAEMSGSIZE: return "WSAEMSGSIZE";
   case WSAEPROTOTYPE: return "WSAEPROTOTYPE";
   case WSAENOPROTOOPT: return "WSAENOPROTOOPT";
   case WSAEPROTONOSUPPORT: return "WSAEPROTONOSUPPORT";
   case WSAESOCKTNOSUPPORT: return "WSAESOCKTNOSUPPORT";
   case WSAEOPNOTSUPP: return "WSAEOPNOTSUPP";
   case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT";
   case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT";
   case WSAEADDRINUSE: return "WSAEADDRINUSE";
   case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL";
   case WSAENETDOWN: return "WSAENETDOWN";
   case WSAENETUNREACH: return "WSAENETUNREACH";
   case WSAENETRESET: return "WSAENETRESET";
   case WSAECONNABORTED: return "WSAECONNABORTED";
   case WSAECONNRESET: return "WSAECONNRESET";
   case WSAENOBUFS: return "WSAENOBUFS";
   case WSAEISCONN: return "WSAEISCONN";
   case WSAENOTCONN: return "WSAENOTCONN";
   case WSAESHUTDOWN: return "WSAESHUTDOWN";
   case WSAETOOMANYREFS: return "WSAETOOMANYREFS";
   case WSAETIMEDOUT: return "WSAETIMEDOUT";
   case WSAECONNREFUSED: return "WSAECONNREFUSED";
   case WSAELOOP: return "WSAELOOP";
   case WSAENAMETOOLONG: return "WSAENAMETOOLONG";
   case WSAEHOSTDOWN: return "WSAEHOSTDOWN";
   case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH";
   case WSAENOTEMPTY: return "WSAENOTEMPTY";
   case WSAEPROCLIM: return "WSAEPROCLIM";
   case WSAEUSERS: return "WSAEUSERS";
   case WSAEDQUOT: return "WSAEDQUOT";
   case WSAESTALE: return "WSAESTALE";
   case WSAEREMOTE: return "WSAEREMOTE";
/*
 * Extended Windows Sockets error constant definitions
 */
   case WSASYSNOTREADY: return "WSASYSNOTREADY";
   case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED";
   case WSANOTINITIALISED: return "WSANOTINITIALISED";
   case WSAEDISCON: return "WSAEDISCON";
/*
   case WSAENOMORE: return "";
   case WSAECANCELLED: return "";
   case WSAEINVALIDPROCTABLE: return "";
   case WSAEINVALIDPROVIDER: return "";
   case WSAEPROVIDERFAILEDINIT: return "";
   case WSASYSCALLFAILURE: return "";
   case WSASERVICE_NOT_FOUND: return "";
   case WSATYPE_NOT_FOUND: return "";
   case WSA_E_NO_MORE: return "";
   case WSA_E_CANCELLED: return "";
   case WSAEREFUSED: return "";
*/
   }
   sprintf(temp, "unknown socket error %d", err);
   return temp;
}

SOCKET CreateClientSocket(int * error)
{
   int on = 1;
   SOCKET client_socket = INVALID_SOCKET;
   struct protoent * protoentry = NULL;
   if ((protoentry = getprotobyname("tcp")) == NULL) {
      *error = -WSAGetLastError();
	   printf("failed to get protocol: %s\n", SocketErrorString(*error));
   } else {
      if ((client_socket = cSocketApi::Socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
         *error = -WSAGetLastError();
	      printf("failed to create client socket: %s\n", SocketErrorString(*error));
         return INVALID_SOCKET;
      } else {
         return client_socket;
      }
	}
   if (cSocketApi::SetSockOpt(client_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
      *error = -WSAGetLastError();
      printf("failed to set socket option SO_REUSEADDR: %s\n", SocketErrorString(*error));
      return INVALID_SOCKET;
   } else {
      return client_socket;
   }
}

SOCKET ConnectToHost(SOCKET client_socket, const char * host, unsigned short port, int * error)
{
   struct hostent * host_entry = NULL;
   SOCKET new_socket = INVALID_SOCKET;
   if (client_socket != INVALID_SOCKET) {
      return client_socket;
   } else {
      client_socket = CreateClientSocket(error);
   }
   host_entry = gethostbyname(host);
   if (host_entry != NULL) {
      struct sockaddr_in server_address = {0};
      server_address.sin_family = AF_INET;
      server_address.sin_family = AF_INET;
      server_address.sin_port = htons(port);
      server_address.sin_addr.s_addr = INADDR_ANY;
      memcpy((char *)&(server_address).sin_addr,
             (char *)host_entry->h_addr,
             host_entry->h_length);
      if (cSocketApi::Connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != -1) {
         return client_socket;
      } else {
         int err = WSAGetLastError();
         if (err == WSAEISCONN) {
            cSocketApi::CloseSocket(client_socket);
            if ((new_socket = CreateClientSocket(error)) == INVALID_SOCKET) {
	            printf("failed to get socket for reconnection: %s\n", SocketErrorString(*error));
            } else {
               return new_socket;
            }
         } else {
            *error = -err;
         }
         printf("failed to connect to host %s port %d: %s\n",
                host, (int)port, SocketErrorString(*error));
         return INVALID_SOCKET;
      }
   } else {
      *error = -WSAGetLastError();
      printf("cannot resolve host name %s: %s\n", host, SocketErrorString(*error));
      return INVALID_SOCKET;
   }
}

#define BUFFER_SIZE     0x400000 
static unsigned char _Text[BUFFER_SIZE] = {0};
static unsigned char _Temp[BUFFER_SIZE] = {0};
static unsigned char _Input[BUFFER_SIZE] = {0};

int main(int argc, char **argv)
{
   int result = _setmode(_fileno(stdout), _O_BINARY);
   cFrameHandler * frame_handler = new cBinaryFrameHandler;
   for (int i=0; i<BUFFER_SIZE; i++) {
      _Text[i] = (abs((rand() % 40)));
      if (_Text[i] == 0x07) {
//         _Text[i] = 0x06;
      }
//      _Text[i] = 0x11;
   }
   int image_size =  0;
   {
      unsigned char * buf_ptr = _Text;
      FILE * stream = fopen("image.png", "rb");
      if (stream != NULL) {
         int nread = fread(buf_ptr, 1, 0x200, stream);
         while (nread > 0) {
            image_size += nread;
            buf_ptr += nread;
            nread = fread(buf_ptr, 1, 0x200, stream);
         }
         fclose(stream);
      }

   }
   const unsigned char * request = NULL;
   int req_no = 0;
   SOCKET socket = INVALID_SOCKET;
   const char * host = "localhost";
   unsigned short port = 20000;
   if (argc > 1) {
      request = (unsigned char *)argv[1];
   }
#ifdef _DEBUG
   FILE * stream = fopen("request.log", "w+");
   if (stream != NULL) {
      fprintf(stream, "%d args: %s %s: request %s\n", argc, argv[0], argv[1], request);
      fclose(stream);
   }
#endif
   if (request != NULL) {   
      int error = 0;
      socket = ConnectToHost(socket, host, port, &error);
      if (socket == INVALID_SOCKET) {
         printf("failed to connect %d\n", cSocketApi::SocketError());
      } else {
         if (stricmp((const char*)request, "image") == 0) {
            unsigned char buf[0x200] = {0};
            FILE * out_stream = fopen("ti.jpg", "wb+");
            FILE * stream = fopen("testimage.jpg", "rb");
            if (stream != NULL && out_stream != NULL) {
               int nread = fread(buf, 1, sizeof(buf), stream);
               while (nread > 0) {
                  int nwrite = 0;
                  nwrite = fwrite(buf, 1, nread, stdout);
                  if (nread != nwrite) {
                     int dummy = 0;
                  }
                  nwrite = fwrite(buf, 1, nread, out_stream);
                  if (nread != nwrite) {
                     int dummy = 0;
                  }
                  nread = fread(buf, 1, sizeof(buf), stream);
               }
               fclose(stream);
               fclose(out_stream);
            }
            return 0;
         }
         int len = strlen((const char*)request);
         memset(_Temp, 0, sizeof(_Temp));
         sprintf((char*)_Temp, "%s", request);
         len = strlen((const char*)_Temp);
         int frame_size = 0;
         unsigned char * frame = frame_handler->Output((unsigned char*)_Temp, len, frame_size);
         int nsend = cSocketApi::Send(socket, (char*)frame, frame_size, 0);
         if (nsend == frame_size) {
            FILE * out_stream = fopen("image.png", "wb+");
            memset(_Input, 0, sizeof(_Input));
            int nread = cSocketApi::Recv(socket, (char*)_Input, sizeof(_Input), 0);
            while (nread > 0) {
               unsigned char * raw_data = NULL;
               int raw_data_size = 0;
               if (frame_handler->Input((unsigned char*)_Input, nread, raw_data, raw_data_size)) {
                  int nwrite = fwrite(raw_data, 1, raw_data_size, stdout);
                  if (out_stream != NULL) {
                     nwrite = fwrite(raw_data, 1, raw_data_size, out_stream);
                  }
                  break;
               }
               nread = cSocketApi::Recv(socket, (char*)_Input, sizeof(_Input), 0);
            }
            if (out_stream != NULL) {
               fclose(out_stream);
            }
         } else {
            printf("send failed (%d,%d): %d\n", nsend, (int)strlen((const char*)_Temp), cSocketApi::SocketError());
         }
      }
   } else {
      while (true) {
         int error = 0;
         socket = ConnectToHost(socket, host, port, &error);
         if (socket == INVALID_SOCKET) {
            printf("failed to connect %d\n", cSocketApi::SocketError());
         } else {
            int len = 0;
            if (image_size > 0) {
               len = image_size;
            } else {
               len = abs(rand() % 0x300000) * 50;
            }
            memset(_Temp, 0, sizeof(_Temp));
            memcpy(_Temp, _Text, len);
sprintf((char*)_Temp, "image:pqmCam1Act");
len = strlen((char*)_Temp);
            unsigned char * org_data = _Temp;
            int frame_size = 0;
            unsigned char * frame = frame_handler->Output((unsigned char*)_Temp, len, frame_size);
            int nsend = cSocketApi::Send(socket, (char*)frame, frame_size, 0);
            if (frame != NULL) {
               cAlloc::Free(frame);
            }
            if (nsend == frame_size) {
               memset(_Input, 0, sizeof(_Input));
               int nread = cSocketApi::Recv(socket, (char*)_Input, sizeof(_Input), 0);
               while (nread > 0) {
                  unsigned char * raw_data = NULL;
                  int raw_data_size = 0;
                  if (frame_handler->Input((unsigned char*)_Input, nread, raw_data, raw_data_size)) {
                     printf("received %d:\n", raw_data_size);
//                     fwrite(raw_data, 1, raw_data_size, stdout);
                     FILE * out_stream = fopen("imaget.png", "wb+");
                     if (out_stream != NULL) {
                        int nwrite = fwrite(raw_data, 1, raw_data_size, out_stream);
                        fclose(out_stream);
                     }
                     if (raw_data_size == len) {
                        for (int i=0; i<len; i++) {
                           unsigned char org = org_data[i];
                           unsigned char raw = raw_data[i];
                           if (org != raw) {
                              int dummy = 0;
                           } else {
                              int dummy = 0;
                           }
                        }
                     } else {
                        int dummy = 0;
                     }
                     if (raw_data != NULL) {
                        cAlloc::Free(raw_data);
                     }
                     break;
                  }
                  nread = cSocketApi::Recv(socket, (char*)_Input, sizeof(_Input), 0);
               }
            } else {
               printf("send failed (%d,%d): %d\n", nsend, len, cSocketApi::SocketError());
            }
         }
         cSocketApi::CloseSocket(socket);
         socket = INVALID_SOCKET;
         Sleep(1000);
         req_no++;
      }
   }
   return 0;
}

