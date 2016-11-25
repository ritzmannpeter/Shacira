//## begin module%429AC0EF031C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429AC0EF031C.cm

//## begin module%429AC0EF031C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429AC0EF031C.cp

//## Module: cTCPComm%429AC0EF031C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cTCPComm.cpp

//## begin module%429AC0EF031C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%429AC0EF031C.additionalIncludes

//## begin module%429AC0EF031C.includes preserve=yes
//## end module%429AC0EF031C.includes

// cTCPComm
#include "System/ClientServer/cTCPComm.h"
//## begin module%429AC0EF031C.additionalDeclarations preserve=yes

ULONG_T cStreamMsg::_Total = 0;

//## end module%429AC0EF031C.additionalDeclarations


// Class cTCPComm 

//## begin cTCPComm::Error%429B38F60242.attr preserve=no  implementation: static int {U} 0
int cTCPComm::_Error = 0;
//## end cTCPComm::Error%429B38F60242.attr

cTCPComm::cTCPComm()
  //## begin cTCPComm::cTCPComm%.hasinit preserve=no
  //## end cTCPComm::cTCPComm%.hasinit
  //## begin cTCPComm::cTCPComm%.initialization preserve=yes
  //## end cTCPComm::cTCPComm%.initialization
{
  //## begin cTCPComm::cTCPComm%.body preserve=yes
  //## end cTCPComm::cTCPComm%.body
}

cTCPComm::cTCPComm(const cTCPComm &right)
  //## begin cTCPComm::cTCPComm%copy.hasinit preserve=no
  //## end cTCPComm::cTCPComm%copy.hasinit
  //## begin cTCPComm::cTCPComm%copy.initialization preserve=yes
  //## end cTCPComm::cTCPComm%copy.initialization
{
  //## begin cTCPComm::cTCPComm%copy.body preserve=yes
  //## end cTCPComm::cTCPComm%copy.body
}


cTCPComm::~cTCPComm()
{
  //## begin cTCPComm::~cTCPComm%.body preserve=yes
  //## end cTCPComm::~cTCPComm%.body
}



//## Other Operations (implementation)
int cTCPComm::SendMsg (SOCKET socket, cStreamMsg &msg, ULONG_T request_id)
{
  //## begin cTCPComm::SendMsg%1117436334.body preserve=yes
   STREAM_HEADER_T header = {0};
   header.signature = STREAM_SIGNATURE;
   header.request_id = request_id;
   header.data_size = msg.MsgLen();
   int nsend = send(socket, (const char *)&header, sizeof(header), 0);
   if (nsend < 0) {
      SetLastErr();
      return -1;
   }
   nsend = send(socket, (const char *)(msg.MsgBuf()), msg.MsgLen(), 0);
   if (nsend < 0) {
      SetLastErr();
      return -1;
   } else if ((ULONG_T)nsend != msg.MsgLen()) {
      SetLastErr(ERR_SENT_MSG_TOO_SHORT);
      return -1;
   }
   return 0;
  //## end cTCPComm::SendMsg%1117436334.body
}

int cTCPComm::ReceiveMsg (SOCKET socket, cStreamMsg &msg, ULONG_T &request_id)
{
  //## begin cTCPComm::ReceiveMsg%1117436335.body preserve=yes
   STREAM_HEADER_T header = {0};
   struct sockaddr_in remote_addr;
   socklen_t addr_size = sizeof(remote_addr);
   int nread = recvfrom(socket,
                        (char *)&header, sizeof(header), 0,
                        (struct sockaddr *)&remote_addr, &addr_size);
   if (nread < 0) {
      SetLastErr();
      return -1;
   }
   if (CheckHeader(nread, &header, request_id)) {
      msg.Allocate(header.data_size);
      nread = recvfrom(socket,
                       (char *)msg.MsgBuf(), msg.MsgLen(), 0,
                       (struct sockaddr *)&remote_addr, &addr_size);
      if (nread < 0) {
         SetLastErr();
         return -1;
      } else if ((ULONG_T)nread != msg.MsgLen()) {
         while ((ULONG_T)nread < msg.MsgLen()) {
            nread += recvfrom(socket,
                              (char *)(msg.MsgBuf())+nread, (msg.MsgLen()-nread), 0,
                              (struct sockaddr *)&remote_addr, &addr_size);
         }
         if ((ULONG_T)nread == msg.MsgLen()) {
            request_id = header.request_id;
            return 0;
         } else {
            SetLastErr(ERR_RECEIVED_MSG_TOO_SHORT);
            return -1;
         }
      } else {
         request_id = header.request_id;
         return 0;
      }
   } else {
      return -1;
   }
  //## end cTCPComm::ReceiveMsg%1117436335.body
}

int cTCPComm::ReceiveMsgFrom (SOCKET socket, cStreamMsg &msg, ULONG_T &request_id)
{
  //## begin cTCPComm::ReceiveMsgFrom%1117453525.body preserve=yes
   STREAM_HEADER_T header = {0};
   struct sockaddr_in remote_addr = {0};
   socklen_t addr_size = sizeof(remote_addr);
   int nread = recvfrom(socket,
                       (char *)&header, sizeof(header), 0,
                       (struct sockaddr *)&remote_addr, &addr_size);
   if (nread < 0) {
      SetLastErr();
      return -1;
   }
   if (CheckHeader(nread, &header, request_id)) {
      msg.Allocate(header.data_size);
      nread = recvfrom(socket,
		                 (char *)msg.MsgBuf(), msg.MsgLen(), 0,
                       (struct sockaddr *)&remote_addr, &addr_size);
      if (nread < 0) {
         SetLastErr();
         return -1;
      } else if ((ULONG_T)nread != msg.MsgLen()) {
         SetLastErr(ERR_RECEIVED_MSG_TOO_SHORT);
         return -1;
      } else {
         request_id = header.request_id;
         return 0;
      }
   } else {
      return -1;
   }
  //## end cTCPComm::ReceiveMsgFrom%1117453525.body
}

BOOL_T cTCPComm::CheckHeader (LONG_T nread, STREAM_HEADER_T *header, ULONG_T request_id)
{
  //## begin cTCPComm::CheckHeader%1117436330.body preserve=yes
   if (nread != sizeof(*header)) {
      SetLastErr(ERR_SIZE_MISMATCH);
      return false;
   }
   if (header->signature == 0 ||
       header->signature == STREAM_SIGNATURE) {
      return true;
   } else {
      SetLastErr(ERR_SIGNATURE_MISMATCH);
      return false;
   }
  //## end cTCPComm::CheckHeader%1117436330.body
}

void cTCPComm::ShutDownSocket (SOCKET &socket)
{
  //## begin cTCPComm::ShutDownSocket%1117436331.body preserve=yes
   if (socket != INVALID_SOCKET) {
#ifdef _WIN32
      shutdown(socket, SD_BOTH);
#endif
#ifdef UNIX
      shutdown(socket, SHUT_RDWR);
#endif
      socket = INVALID_SOCKET;
   }
  //## end cTCPComm::ShutDownSocket%1117436331.body
}

void cTCPComm::SetLastErr (int err_code)
{
  //## begin cTCPComm::SetLastErr%1117453523.body preserve=yes
   if (err_code == 0) {
      _Error = SocketErr();
   } else {
      _Error = err_code;
   }
  //## end cTCPComm::SetLastErr%1117453523.body
}

int cTCPComm::LastErr ()
{
  //## begin cTCPComm::LastErr%1117436332.body preserve=yes
   return _Error;
  //## end cTCPComm::LastErr%1117436332.body
}

int cTCPComm::SocketErr ()
{
  //## begin cTCPComm::SocketErr%1117453524.body preserve=yes
#ifdef _WIN32
   return WSAGetLastError();
#else
   return errno;
#endif
  //## end cTCPComm::SocketErr%1117453524.body
}

STRING_T cTCPComm::ErrString (int err_code)
{
  //## begin cTCPComm::ErrString%1117436333.body preserve=yes
   static char error_string[0x200] = {0};
   SafePrintf(error_string, sizeof(error_string), "socket error %d", err_code);
   return error_string;
  //## end cTCPComm::ErrString%1117436333.body
}

// Additional Declarations
  //## begin cTCPComm%429AC0EF031C.declarations preserve=yes
  //## end cTCPComm%429AC0EF031C.declarations

//## begin module%429AC0EF031C.epilog preserve=yes
//## end module%429AC0EF031C.epilog
