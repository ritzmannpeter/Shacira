
#ifndef cSocketApi_h
#define cSocketApi_h 1

#if defined(WIN32)
#include <winsock2.h>
//#include <windows.h>
#elif defined(__linux__)
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

#else
NO_PLATFORM
#endif

/*!
 *  socket api abstraction class
 */

/*!
 *  ping callback function definition for reachable hosts
 */
typedef void (*REACHABLE_FUNC_T)(const char * ip_address, int c1, int c2, int c3, int c4, unsigned long time);

class cSocketApi 
{
public:
   virtual ~cSocketApi();
   static SOCKET Socket(int af, int type, int protocol);
   static int CloseSocket(SOCKET s);
   static int IoctlSocket(SOCKET s, long cmd, unsigned long * argp);
   static int Bind(SOCKET s, const struct sockaddr * addr, int addrlen);
   static int Connect(SOCKET s, const struct sockaddr * addr, int addrlen);
   static int Listen(SOCKET s, int backlog);
   static SOCKET Accept(SOCKET s, struct sockaddr * addr, int * addrlen);
   static int SetSockOpt(SOCKET s, int level, int optname, const char * optval, int optlen);
   static int Send(SOCKET s, const char * buf, int len, int flags);
   static int SendTo(SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen);
   static int Recv(SOCKET s, char * buf, int len, int flags);
   static int RecvFrom(SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen);

   static int SetReceiveTimeout(SOCKET socket, unsigned long msecs);
   /*!
    *  hosts and addresses
    */
   static int GetHostName(char * name, unsigned long name_length);
   static unsigned long IPAddress(const char * host_name);
   static int IPAddresses(const char * host_name,
                          unsigned long & a1,
                          unsigned long & a2,
                          unsigned long & a3,
                          unsigned long & a4);
   static int TranslateAddress(char * address, unsigned long address_length, unsigned long ip_addr);
   static unsigned long TranslateAddress(const char * address);
   /*!
    *  Ping method
    */
   static int Ping(const char * spec, REACHABLE_FUNC_T function, unsigned long timeout = 200);
   static int SocketError();
private:
   cSocketApi();
   static bool StartSockets();
   static void StopSockets();
private:
   static bool _Initialized;
   static bool _Trace;
   static cSocketApi _SocketApi;
};

/*!
 *  icmp specific type definitions used for Ping method
 */

/*!
 *  icmp commands
 */

#define ICMP_ECHO       8
#define ICMP_ECHOREPLY  0
#define ICMP_MIN        8

/*!
 *  icmp header
 */

typedef struct _ihdr {
   unsigned char i_type;
   unsigned char i_code;
   unsigned short i_cksum;
   unsigned short i_id;
   unsigned short i_seq;
   unsigned long timestamp;
}  IcmpHeader;

typedef struct iphdr {
	unsigned int h_len:4;          // length of the header
	unsigned int version:4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl;
	unsigned char proto;           // protocol(TCP, UDP etc)
	unsigned short checksum;       // IP checksum
	unsigned int sourceIP;
	unsigned int destIP;
}  IpHeader;

#define DEF_PACKET_SIZE    32
#define MAX_PACKET         1024

static void inline fill_icmp_data(char * icmp_data, int datasize)
{
   IcmpHeader *icmp_hdr;
   char * datapart;
   icmp_hdr =(IcmpHeader*)icmp_data;
   icmp_hdr->i_type = ICMP_ECHO;
   icmp_hdr->i_code = 0;
   icmp_hdr->i_id =(unsigned short)GetCurrentProcessId();
   icmp_hdr->i_cksum = 0;
   icmp_hdr->i_seq = 0;
   datapart = icmp_data + sizeof(IcmpHeader);
   //
   // Place some junk in the buffer.
   //
   memset(datapart,'E', datasize - sizeof(IcmpHeader));
}

static unsigned short checksum(unsigned short *buffer, int size)
{
   unsigned long cksum=0;
   while (size >1) {
	   cksum+=*buffer++;
	   size -=sizeof(unsigned short);
   }
   if (size ) {
	   cksum += *(UCHAR*)buffer;
   }
   cksum =(cksum >> 16) +(cksum & 0xffff);
   cksum +=(cksum >>16);
   return(unsigned short)(~cksum);
}

#endif
