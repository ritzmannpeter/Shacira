
#ifndef cSocketApi_h
#define cSocketApi_h 1

#if defined(WIN32)
#include <winsock2.h>
#elif defined(__linux__)
#include <netdb.h>
#include <sys/socket.h>
#include <errno.h>
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
    *  Ping method
    */
   static int Ping(const char * spec, REACHABLE_FUNC_T function, unsigned long timeout = 200);
   static int SocketError();
public:
   static bool _Trace;
private:
   cSocketApi();
   static bool StartSockets();
   static void StopSockets();
private:
   static bool _Initialized;
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
