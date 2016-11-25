#include "FirstHeader.h"
#include "System/ClientServer/cInetAddress.h"
#include "System/ClientServer/cCSComm.h"
#include "cStreamServer.h"

cStreamServer::cStreamServer (cCSComm *comm)
   : cServer(comm)
{
   _CSComm = comm;
}


cStreamServer::~cStreamServer()
{
}


void cStreamServer::Request (cCSMsg *msg, cCSAddress *client_address)
{
   PTR_T block = msg->MsgBuf();
   ULONG_T block_len = msg->MsgLen();
   Reply(msg, client_address);
}

