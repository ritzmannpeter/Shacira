#include "FirstHeader.h"
#include "cPPCClient.h"
#include "cPPCDevice.h"
#include "System/ClientServer/cBlockQueue.h"

cPPCClient::cPPCClient (cPPCDevice * device, cCSComm * comm)
   : _Device(NULL), cClient(comm)
{
   _CSComm = comm;
   _Device = device;
}


cPPCClient::~cPPCClient()
{
}

void cPPCClient::Dispatch (cCSMsg *msg, cCSAddress *client_address)
{
   UCHAR_T block_buf[512] = {0};
   PTR_T block = msg->MsgBuf();
   ULONG_T block_size = msg->MsgLen();
   UCHAR_T iscos_no = 99;
   ULONG_T efflen = _Device->CheckBlock(block, block_size, block_buf, sizeof(block_buf), iscos_no);
   cBlockQueue * block_queue = BlockQueue(0);
   if (block_queue != NULL) {
      block_queue->SetBlock(block_buf, efflen);
   }
}


