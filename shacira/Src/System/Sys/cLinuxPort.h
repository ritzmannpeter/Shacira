
#ifndef _cLinuxPort_h_
#define _cLinuxPort_h_

#if defined(__linux__)

// macros

// system

typedef long * HANDLE;
typedef unsigned long DWORD;
typedef unsigned short * LPWSTR;
typedef void _EXCEPTION_POINTERS;
#define __stdcall

// sockets

#include	<errno.h>
#include	<netdb.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
typedef int SOCKET;
typedef sockaddr SOCKADDR;
typedef sockaddr_in SOCKADDR_IN;
#define INVALID_SOCKET  ENOTSOCK
#define WSAECONNRESET   ECONNRESET
#define WSAECONNABORTED ECONNABORTED
#define WSAEISCONN      EISCONN
#define WSAETIMEDOUT    ETIMEDOUT
#define WSAEHOSTUNREACH EHOSTUNREACH
#define WSAECONNREFUSED ECONNREFUSED
#define WSAENETUNREACH  ENETUNREACH
#define WSAGetLastError() errno
#define GetLastError() errno
#define closesocket(s) close(s)
#define TIMED_OUT(ec) (ec == WSAETIMEDOUT || ec == 11)

#ifdef ERRROR_DOC
EBADF 
The file descriptor is not a valid index in the descriptor table. 
EFAULT 
The socket structure address is outside the users address space. 
ENOTSOCK 
The file descriptor is not associated with a socket. 
EISCONN 
The socket is already connected. 
ECONNREFUSED 
No one listening on the remote address. 
ETIMEDOUT 
Timeout while attempting connection. The server may be too busy to accept new connections. Note that for IP sockets the timeout may be very long when syncookies are enabled on the server. 
ENETUNREACH 
Network is unreachable. 
EADDRINUSE 
Local address is already in use. 
EINPROGRESS 
The socket is non-blocking and the connection cannot be completed immediately. It is possible to select(2) or poll(2) for completion by selecting the socket for writing. After select indicates writability, use getsockopt(2) to read the SO_ERROR option at level SOL_SOCKET to determine whether connect completed successfully (SO_ERROR is zero) or unsuccessfully (SO_ERROR is one of the usual error codes listed here, explaining the reason for the failure). 
EALREADY 
The socket is non-blocking and a previous connection attempt has not yet been completed. 
EAGAIN 
No more free local ports or insufficient entries in the routing cache. For PF_INET see the net.ipv4.ip_local_port_range sysctl in ip(7) on how to increase the number of local ports. 
EAFNOSUPPORT 
The passed address didnt have the correct address family in its sa_family field. 
EACCES, EPERM 
The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a 
#endif

// standard

#ifndef stricmp
#define stricmp strcasecmp
#endif
#ifndef strnicmp
#define strnicmp strncasecmp
#endif

extern "C" {

char* ltoa(long, char*, int);
char* itoa(int, char*, int);
void strupr(char *s);

}

/// perhaps needed by applications
#define TRUE true
#define FALSE false
#define LONG LONG_T
#define ULONG ULONG_T
#define SHORT SHORT_T
#define USHORT USHORT_T
#define INT INT_T
#define UINT UINT_T
#define FLOAT FLOAT_T
#define DOUBLE DOUBLE_T
typedef char TCHAR;

#endif

#endif
