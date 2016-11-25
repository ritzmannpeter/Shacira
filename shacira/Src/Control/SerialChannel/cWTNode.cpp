//## begin module%3CBBD3CA001E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CBBD3CA001E.cm

//## begin module%3CBBD3CA001E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CBBD3CA001E.cp

//## Module: cWTNode%3CBBD3CA001E; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cWTNode.cpp

//## begin module%3CBBD3CA001E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3CBBD3CA001E.additionalIncludes

//## begin module%3CBBD3CA001E.includes preserve=yes
//## end module%3CBBD3CA001E.includes

// cWTNode
#include "Control/SerialChannel/cWTNode.h"
//## begin module%3CBBD3CA001E.additionalDeclarations preserve=yes

#ifdef __linux__

typedef UCHAR_T UCHAR;

#endif

#define NODE_UNDEFINED     -1
#define NODE_REACHABLE     1
#define NODE_UNREACHABLE   2

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
#define ICMP_MIN 8 // minimum 8 byte icmp packet (just header)

//
// ICMP header
//
typedef struct _ihdr {
   unsigned char i_type;
   unsigned char i_code;
   unsigned short i_cksum;
   unsigned short i_id;
   unsigned short i_seq;
   /* This is not the std header, but we reserve space for time */
   unsigned long timestamp;
}  IcmpHeader;

/* The IP header */
typedef struct iphdr {
	unsigned int h_len:4;          // length of the header
	unsigned int version:4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl;
	unsigned char proto;           // protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum
	unsigned int sourceIP;
	unsigned int destIP;
}  IpHeader;

/*
	Helper function to fill in various stuff in our ICMP request.
*/
static void fill_icmp_data(char * icmp_data, int datasize)
{
   IcmpHeader *icmp_hdr;
   char *datapart;
   icmp_hdr = (IcmpHeader*)icmp_data;
   icmp_hdr->i_type = ICMP_ECHO;
   icmp_hdr->i_code = 0;
   icmp_hdr->i_id = (unsigned short)cSystemUtils::ProcessId();
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
   cksum = (cksum >> 16) + (cksum & 0xffff);
   cksum += (cksum >>16);
   return (unsigned short)(~cksum);
}


//## end module%3CBBD3CA001E.additionalDeclarations


// Class cWTNode 





cWTNode::cWTNode()
  //## begin cWTNode::cWTNode%.hasinit preserve=no
      : _State(-1)
  //## end cWTNode::cWTNode%.hasinit
  //## begin cWTNode::cWTNode%.initialization preserve=yes
  //## end cWTNode::cWTNode%.initialization
{
  //## begin cWTNode::cWTNode%.body preserve=yes
   memset(&_Address, 0, sizeof(_Address));
  //## end cWTNode::cWTNode%.body
}

cWTNode::cWTNode(const cWTNode &right)
  //## begin cWTNode::cWTNode%copy.hasinit preserve=no
      : _State(-1)
  //## end cWTNode::cWTNode%copy.hasinit
  //## begin cWTNode::cWTNode%copy.initialization preserve=yes
  //## end cWTNode::cWTNode%copy.initialization
{
  //## begin cWTNode::cWTNode%copy.body preserve=yes
_ASSERT_UNCOND
   memset(&_Address, 0, sizeof(_Address));
  //## end cWTNode::cWTNode%copy.body
}

cWTNode::cWTNode (CONST_STRING_T ip_address)
  //## begin cWTNode::cWTNode%1018942491.hasinit preserve=no
      : _State(-1)
  //## end cWTNode::cWTNode%1018942491.hasinit
  //## begin cWTNode::cWTNode%1018942491.initialization preserve=yes
  //## end cWTNode::cWTNode%1018942491.initialization
{
  //## begin cWTNode::cWTNode%1018942491.body preserve=yes
   memset(&_Address, 0, sizeof(_Address));
   _IPAddress = ip_address;
  //## end cWTNode::cWTNode%1018942491.body
}


cWTNode::~cWTNode()
{
  //## begin cWTNode::~cWTNode%.body preserve=yes
  //## end cWTNode::~cWTNode%.body
}



//## Other Operations (implementation)
BOOL_T cWTNode::Reachable ()
{
  //## begin cWTNode::Reachable%1018942492.body preserve=yes
   return (_State == NODE_REACHABLE) ? true : false;
  //## end cWTNode::Reachable%1018942492.body
}

void cWTNode::Refresh ()
{
  //## begin cWTNode::Refresh%1018942494.body preserve=yes
   int state;
   if (Ping(_IPAddress.c_str())) {
      state = NODE_REACHABLE;
   } else {
      state = NODE_UNREACHABLE;
   }
   if (state != _State) {
      if (state == NODE_REACHABLE) {
	     InfoPrintf("W&T Node %s reachable again\n", _IPAddress.c_str());
      } else if (state == NODE_UNREACHABLE) {
	     InfoPrintf("W&T Node %s not reachable\n", _IPAddress.c_str());
	  }
      _State = state;
   }
  //## end cWTNode::Refresh%1018942494.body
}

BOOL_T cWTNode::Ping (CONST_STRING_T address)
{
  //## begin cWTNode::Ping%1018942497.body preserve=yes
//printf("ping %s\n", address);
   struct sockaddr_in destination;
   memset(&destination, 0, sizeof(destination));
   unsigned long addr = inet_addr(address);
   destination.sin_addr.s_addr = addr;
   destination.sin_family = AF_INET;
   return Ping (&destination);
  //## end cWTNode::Ping%1018942497.body
}

BOOL_T cWTNode::Ping (SOCKADDR_IN *address)
{
  //## begin cWTNode::Ping%1018942496.body preserve=yes
#define DEF_PACKET_SIZE 32
#define MAX_PACKET 1024

int ret = 0;

   SOCKET sockRaw;
   struct sockaddr_in from;
   int bread = 0, datasize = 0;
   socklen_t fromlen = sizeof(from);
   char icmp_data[MAX_PACKET] = {0};
   char recvbuf[MAX_PACKET] = {0};
   unsigned short seq_no = 0;
	int bwrote = 0;
   long timeout = 200;
   sockRaw = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP);
   if (sockRaw == INVALID_SOCKET) {
//printf("%08x: %d: -1\n", address->sin_addr.s_addr, ret);
      return false;
   }
   bread = setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout, sizeof(timeout));
   if (bread < 0) {
      ret = closesocket(sockRaw);
//printf("%08x: %d: -2\n", address->sin_addr.s_addr, ret);
      return false;
   }
   bread = setsockopt(sockRaw,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout, sizeof(timeout));
   if (bread < 0) {
      closesocket(sockRaw);
//printf("%08x: %d: -3\n", address->sin_addr.s_addr, ret);
      return false;
   }
   datasize = DEF_PACKET_SIZE;
   datasize += sizeof(IcmpHeader);
   fill_icmp_data(icmp_data, datasize);
	((IcmpHeader*)icmp_data)->i_cksum = 0;
   ((IcmpHeader*)icmp_data)->timestamp = cSystemUtils::RealtimeOffset();
	((IcmpHeader*)icmp_data)->i_seq = seq_no++;
	((IcmpHeader*)icmp_data)->i_cksum = checksum((unsigned short*)icmp_data, datasize);
	bwrote = sendto(sockRaw, icmp_data, datasize,0, (struct sockaddr*)address, sizeof(*address));
	if (bwrote < 0) {
      ret = closesocket(sockRaw);
//printf("%08x: %d: -4\n", address->sin_addr.s_addr, ret);
      return false;
   }
   bread = recvfrom(sockRaw, recvbuf, MAX_PACKET, MSG_PEEK, (struct sockaddr*)&from, &fromlen);
   if (bread < 0){
      ret = closesocket(sockRaw);
//printf("%08x: %d: -5\n", address->sin_addr.s_addr, ret);
      return false;
   } else {
      if (address->sin_addr.s_addr != from.sin_addr.s_addr) {
         // 27.05.2002 -PR- Hier war wirklich ein Speicherleck weil der closesocket-Aufruf
         //                 gefehlt hat.
         ret = closesocket(sockRaw);
//printf("%08x: %d: -6\n", address->sin_addr.s_addr, ret);
         return false;
      } else {
      	bread = recvfrom(sockRaw, recvbuf, MAX_PACKET, 0, (struct sockaddr*)&from, &fromlen);
      }
   }
   closesocket(sockRaw);
//printf("%08x: %d: 0\n", address->sin_addr.s_addr, ret);
   return true;
  //## end cWTNode::Ping%1018942496.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cWTNode::get_IPAddress () const
{
  //## begin cWTNode::get_IPAddress%3CBBD987036A.get preserve=no
  return _IPAddress;
  //## end cWTNode::get_IPAddress%3CBBD987036A.get
}

void cWTNode::set_IPAddress (STRING_T value)
{
  //## begin cWTNode::set_IPAddress%3CBBD987036A.set preserve=no
  _IPAddress = value;
  //## end cWTNode::set_IPAddress%3CBBD987036A.set
}

// Additional Declarations
  //## begin cWTNode%3CBBD3CA001E.declarations preserve=yes
  //## end cWTNode%3CBBD3CA001E.declarations

//## begin module%3CBBD3CA001E.epilog preserve=yes
//## end module%3CBBD3CA001E.epilog
