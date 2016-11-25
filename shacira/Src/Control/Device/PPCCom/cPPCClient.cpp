//## begin module%4108980A01F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4108980A01F4.cm

//## begin module%4108980A01F4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4108980A01F4.cp

//## Module: cPPCClient%4108980A01F4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCClient.cpp

//## begin module%4108980A01F4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4108980A01F4.additionalIncludes

//## begin module%4108980A01F4.includes preserve=yes
//## end module%4108980A01F4.includes

// cPPCClient
#include "Control/Device/PPCCom/cPPCClient.h"
// cPPCDevice
#include "Control/Device/PPCCom/cPPCDevice.h"
//## begin module%4108980A01F4.additionalDeclarations preserve=yes
//## end module%4108980A01F4.additionalDeclarations


// Class cPPCClient 


cPPCClient::cPPCClient()
  //## begin cPPCClient::cPPCClient%.hasinit preserve=no
      : _Device(NULL)
  //## end cPPCClient::cPPCClient%.hasinit
  //## begin cPPCClient::cPPCClient%.initialization preserve=yes
  //## end cPPCClient::cPPCClient%.initialization
{
  //## begin cPPCClient::cPPCClient%.body preserve=yes
_ASSERT_UNCOND
  //## end cPPCClient::cPPCClient%.body
}

cPPCClient::cPPCClient(const cPPCClient &right)
  //## begin cPPCClient::cPPCClient%copy.hasinit preserve=no
      : _Device(NULL)
  //## end cPPCClient::cPPCClient%copy.hasinit
  //## begin cPPCClient::cPPCClient%copy.initialization preserve=yes
  //## end cPPCClient::cPPCClient%copy.initialization
{
  //## begin cPPCClient::cPPCClient%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPPCClient::cPPCClient%copy.body
}

cPPCClient::cPPCClient (cCSComm *comm, cPPCDevice *device)
  //## begin cPPCClient::cPPCClient%1091082168.hasinit preserve=no
      : _Device(NULL)
  //## end cPPCClient::cPPCClient%1091082168.hasinit
  //## begin cPPCClient::cPPCClient%1091082168.initialization preserve=yes
  , cUDPClient(comm)
  //## end cPPCClient::cPPCClient%1091082168.initialization
{
  //## begin cPPCClient::cPPCClient%1091082168.body preserve=yes
   _Device = device;
  //## end cPPCClient::cPPCClient%1091082168.body
}


cPPCClient::~cPPCClient()
{
  //## begin cPPCClient::~cPPCClient%.body preserve=yes
  //## end cPPCClient::~cPPCClient%.body
}



//## Other Operations (implementation)
void cPPCClient::Dispatch (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cPPCClient::Dispatch%1091082165.body preserve=yes
   UCHAR_T block_buf[MAX_BLOCK_LEN + REQUEST_ID_SIZE] = {0};
   PTR_T block = msg->AppData();
   ULONG_T block_size = msg->AppDataSize();
   UCHAR_T iscos_no = 0;
   LONG_T block_len = _Device->CheckBlock((BUF_T)block, block_size, block_buf, sizeof(block_buf), iscos_no);
   if (block_len > 0) {
      cBlockQueue * block_queue = BlockQueue(iscos_no);
      if (block_queue != NULL) {
         block_queue->SetBlock(block_buf, (ULONG_T)block_len);
      }
   }
   else {
      ErrorPrintf("Dispatch, CheckBlock error %d", block_len);
   }
  //## end cPPCClient::Dispatch%1091082165.body
}

// Additional Declarations
  //## begin cPPCClient%4108980A01F4.declarations preserve=yes
  //## end cPPCClient%4108980A01F4.declarations

//## begin module%4108980A01F4.epilog preserve=yes
//## end module%4108980A01F4.epilog
