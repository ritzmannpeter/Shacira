#include "FirstHeader.h"
#include "System/ClientServer/cInetAddress.h"
#include "System/ClientServer/cCSComm.h"
#include "cPPCServer.h"

cPPCServer::cPPCServer (cPPCDevice * device, cCSComm *comm)
   : _Device(NULL), cServer(comm)
{
   _CSComm = comm;
   _Device = device;
}


cPPCServer::~cPPCServer()
{
}


void cPPCServer::Request (cCSMsg *msg, cCSAddress *client_address)
{
   PTR_T block = msg->MsgBuf();
   ULONG_T block_len = msg->MsgLen();
   Reply(msg, client_address);
}

