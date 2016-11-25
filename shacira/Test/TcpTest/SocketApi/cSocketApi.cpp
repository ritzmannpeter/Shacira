
#include "cSocketApi.h"
#include <stdio.h>
#include <stdarg.h>

///#define Trace printf
static char _Text[0x8000] = {0};
void Trace(const char * fmt, ...)
{
   if (cSocketApi::_Trace) {
      va_list args;
      va_start(args, fmt);
      try {
         vsprintf(_Text, fmt, args);
#ifdef lassma
         FILE * stream = fopen("tcpproto.log", "a");
         if (stream != NULL) {
            fprintf(stream, "%s", _Text);
            fclose(stream);
         }
         OutputDebugString(_Text);
#endif
         fprintf(stdout, "%s", _Text);
      } catch (...) {
      }
   }
}

bool cSocketApi::_Initialized = true;
bool cSocketApi::_Trace = false;
cSocketApi cSocketApi::_SocketApi;

cSocketApi::cSocketApi()
{
   if (StartSockets()) {
      _Initialized = true;
   }
}

cSocketApi::~cSocketApi()
{
   StopSockets();
}

SOCKET cSocketApi::Socket(int af, int type, int protocol)
{
   SOCKET s = socket(af, type, protocol);
   Trace("socket(%d,%d,%d) = %d\n", af, type, protocol, s);
   return s;
}

int cSocketApi::CloseSocket(SOCKET s)
{
#if defined(WIN32)
   int rc = shutdown(s, SD_BOTH);
   rc = closesocket(s);
#elif defined(__linux__)
   int rc = shutdown(s, SHUT_RDWR);
#else
NO_PLATFORM
#endif
   Trace("closesocket(%d) = %d\n", s, rc);
   return rc;
}

int cSocketApi::IoctlSocket(SOCKET s, long cmd, unsigned long * argp)
{
   int rc = ioctlsocket(s, cmd, argp);
   Trace("ioctlsocket(%d,%d,(%p,%d)) = %d\n", s, cmd, argp, *argp, rc);
   return rc;
}

int cSocketApi::Bind(SOCKET s, const struct sockaddr * addr, int addrlen)
{
   int rc = bind(s, addr, addrlen);
   Trace("bind(%d,%s) = %d\n", s, inet_ntoa(((struct sockaddr_in*)addr)->sin_addr), rc);
   return rc;
}

int cSocketApi::Connect(SOCKET s, const struct sockaddr * addr, int addrlen)
{
   Trace("connect(%d,%s)...", s, inet_ntoa(((struct sockaddr_in*)addr)->sin_addr));
   int rc = connect(s, addr, addrlen);
   Trace(" = %d:%d\n", rc, SocketError());
   return rc;
}

int cSocketApi::Listen(SOCKET s, int backlog)
{
   int rc = listen(s, backlog);
   Trace("listen(%d,%d) = %d\n", s, backlog, rc);
   return rc;
}

SOCKET cSocketApi::Accept(SOCKET s, struct sockaddr * addr, int * addrlen)
{
   Trace("accept(%d)...", s);
   SOCKET is = accept(s, addr, addrlen);
   Trace(" = %d (%s)\n", is, inet_ntoa(((struct sockaddr_in*)addr)->sin_addr));
   return is;
}

int cSocketApi::SetSockOpt(SOCKET s, int level, int optname, const char * optval, int optlen)
{
   int rc = setsockopt(s, level, optname, optval, optlen);
   Trace("setsockopt(%d,%d,%d,%d,%d) = %d\n", s, level, optname, (int)*(int*)optval, optlen, rc);
   return rc;
}

int cSocketApi::Send(SOCKET s, const char * buf, int len, int flags)
{
   int rc = send(s, buf, len, flags);
   Trace("send(%d,%p,%d,%d) = %d\n", s, buf, len, flags, rc);
   return rc;
}

int cSocketApi::SendTo(SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen)
{
   int rc = sendto(s, buf, len, flags, to, tolen);
   Trace("sendto(%d,%p,%d,%d,%s) = %d\n", s, buf, len, flags, inet_ntoa(((struct sockaddr_in*)to)->sin_addr), rc);
   return rc;
}

int cSocketApi::Recv(SOCKET s, char * buf, int len, int flags)
{
   Trace("recv(%d,%p,%d,%d)...", s, buf, len, flags);
   int rc = recv(s, buf, len, flags);
   Trace(" = %d:%d\n", rc, SocketError());
   return rc;
}

int cSocketApi::RecvFrom(SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen)
{
   Trace("recvfrom(%d,%p,%d)...", s, buf, len, flags);
   int rc = recvfrom(s, buf, len, flags, from, fromlen);
   Trace(" = %d\n", inet_ntoa(((struct sockaddr_in*)from)->sin_addr), rc);
   return rc;
}

int cSocketApi::SetReceiveTimeout(SOCKET socket, unsigned long msecs)
{
   int rc = SetSockOpt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&msecs, sizeof(msecs));
   return rc;
}

int cSocketApi::Ping(const char * spec, REACHABLE_FUNC_T function, unsigned long timeout)
{
   int rc = 0;
   /*
    *  send an icmp message to all ip addresses
    */
   SOCKET s = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
   if (s == INVALID_SOCKET) {
      return -1;
   }
   unsigned short seq_no = 0;
   int datasize = DEF_PACKET_SIZE;
   datasize += sizeof(IcmpHeader);
   char icmp_data[MAX_PACKET] = {0};
   fill_icmp_data(icmp_data, datasize);
	((IcmpHeader*)icmp_data)->i_cksum = 0;
	((IcmpHeader*)icmp_data)->timestamp = GetTickCount();
	((IcmpHeader*)icmp_data)->i_seq = seq_no++;
	((IcmpHeader*)icmp_data)->i_cksum = checksum((unsigned short*)icmp_data, datasize);
   struct sockaddr_in destination = {0};
   int c1 = 0, c1_start = 1, c1_end = 254;
   int c2 = 0, c2_start = 1, c2_end = 254;
   int c3 = 0, c3_start = 1, c3_end = 254;
   int c4 = 0, c4_start = 1, c4_end = 254;
   if (sscanf(spec, "%d.%d.%d.%d", &c1_start, &c2_start, &c3_start, &c4_start) == 4) {
      /*
       *  broadcast specification or ip address
       */
      if (c1_start == 255) {
         c1_start = 1;
         c1_end = 254;
      } else {
         c1_end = c1_start;
      }
      if (c2_start == 255) {
         c2_start = 1;
         c2_end = 254;
      } else {
         c2_end = c2_start;
      }
      if (c3_start == 255) {
         c3_start = 1;
         c3_end = 254;
      } else {
         c3_end = c3_start;
      }
      if (c4_start == 255) {
         c4_start = 1;
         c4_end = 254;
      } else {
         c4_end = c4_start;
      }
      /*
       *  pseudo broadcast
       */
      for (c1=c1_start; c1<=c1_end; c1++) {
         for (c2=c2_start; c2<=c2_end; c2++) {
            for (c3=c3_start; c3<=c3_end; c3++) {
               for (c4=c4_start; c4<=c4_end; c4++) {
                  char ip_addr[0x100] = {0};
                  unsigned long addr = 0;
                  sprintf(ip_addr, "%d.%d.%d.%d", c1, c2, c3, c4);
                  addr = inet_addr(ip_addr);
                  destination.sin_addr.s_addr = addr;
                  destination.sin_family = AF_INET;
                  int nwrite = sendto(s, icmp_data, datasize,0,(struct sockaddr*)&destination, sizeof(destination));
                  if (nwrite == SOCKET_ERROR) {
                     int dummy = 0;
                  } else {
                     int dummy = 0;
                  }
               }
            }
         }
      }
   } else {
      /*
       *  host name based request
       */
      struct hostent * host_entry = NULL;
      host_entry = gethostbyname(spec);
      if (host_entry != NULL) {
         destination.sin_family = AF_INET;
         memcpy((char *)&(destination).sin_addr,
                (char *)host_entry->h_addr,
                host_entry->h_length);
         int nwrite = sendto(s, icmp_data, datasize,0,(struct sockaddr*)&destination, sizeof(destination));
         if (nwrite == SOCKET_ERROR) {
            int dummy = 0;
         } else {
            int dummy = 0;
         }
      } else {
         CloseSocket(s);
         return 0;
      }
   }

   /*
    *  wait for incoming replies and handle them
    */
#if defined(WIN32)
   unsigned long t0 = GetTickCount();
#else
   unsigned long t0 = 0;
#endif
   rc = SetReceiveTimeout(s, timeout);
   if (rc == SOCKET_ERROR) {
      CloseSocket(s);
      return -1;
   }
   struct sockaddr_in from = {0};
   int fromlen = sizeof(from);
   char recvbuf[MAX_PACKET] = {0};
   int nread = 0;
   while (nread != -1) {
      nread = recvfrom(s, recvbuf, MAX_PACKET, 0,(struct sockaddr*)&from, &fromlen);
      if (nread == SOCKET_ERROR){
         CloseSocket(s);
         return -1;
      } else {
         const char * ip_addr = inet_ntoa(from.sin_addr);
         int c[4] = {0};
         if (nread == 0) {
            CloseSocket(s);
            return 0;
         }
         if (sscanf(ip_addr, "%d.%d.%d.%d", &c[0], &c[1], &c[2], &c[3]) == 4) {
#if defined(WIN32)
            unsigned long time = GetTickCount() - t0;
#else
            unsigned long time = 0;
#endif
            function(ip_addr, c[0], c[1], c[2], c[3], time);
         }
      }
   }
   CloseSocket(s);
   return 0;
}

int cSocketApi::SocketError()
{
#if defined(WIN32)
   return -WSAGetLastError();
#elif defined(__linux__)
   return -errno;
#else
NO_PLATFORM
#endif
}

bool cSocketApi::StartSockets()
{
#if defined(WIN32)
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      return false;
   }
/*
 *  check for the correct version of the winsock dll
 */
   if (LOBYTE(wsa_data.wVersion) != 2 ||
       HIBYTE(wsa_data.wVersion) != 2) {
      WSACleanup();
      return false;
   }
   return true;
#elif defined(__linux__)
   return true;
#else
NO_PLATFORM
#endif
}

void cSocketApi::StopSockets()
{
#if defined(WIN32)
   WSACleanup();
#endif
}

