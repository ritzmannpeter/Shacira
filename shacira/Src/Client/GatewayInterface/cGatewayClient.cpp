//## begin module%429C5CE7035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429C5CE7035B.cm

//## begin module%429C5CE7035B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429C5CE7035B.cp

//## Module: cGatewayClient%429C5CE7035B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\GatewayInterface\cGatewayClient.cpp

//## begin module%429C5CE7035B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%429C5CE7035B.additionalIncludes

//## begin module%429C5CE7035B.includes preserve=yes
//## end module%429C5CE7035B.includes

// cClient
#include "System/ClientServer/cClient.h"
// cGatewayClient
#include "Client/GatewayInterface/cGatewayClient.h"
//## begin module%429C5CE7035B.additionalDeclarations preserve=yes
//## end module%429C5CE7035B.additionalDeclarations


// Class cGatewayClient 



cGatewayClient::cGatewayClient()
  //## begin cGatewayClient::cGatewayClient%.hasinit preserve=no
      : _ClientId(0), _Client(NULL)
  //## end cGatewayClient::cGatewayClient%.hasinit
  //## begin cGatewayClient::cGatewayClient%.initialization preserve=yes
  //## end cGatewayClient::cGatewayClient%.initialization
{
  //## begin cGatewayClient::cGatewayClient%.body preserve=yes
  //## end cGatewayClient::cGatewayClient%.body
}

cGatewayClient::cGatewayClient(const cGatewayClient &right)
  //## begin cGatewayClient::cGatewayClient%copy.hasinit preserve=no
      : _ClientId(0), _Client(NULL)
  //## end cGatewayClient::cGatewayClient%copy.hasinit
  //## begin cGatewayClient::cGatewayClient%copy.initialization preserve=yes
  //## end cGatewayClient::cGatewayClient%copy.initialization
{
  //## begin cGatewayClient::cGatewayClient%copy.body preserve=yes
  //## end cGatewayClient::cGatewayClient%copy.body
}

cGatewayClient::cGatewayClient (ULONG_T client_id, USHORT_T server_port, CONST_STRING_T server_host)
  //## begin cGatewayClient::cGatewayClient%1117544868.hasinit preserve=no
      : _ClientId(0), _Client(NULL)
  //## end cGatewayClient::cGatewayClient%1117544868.hasinit
  //## begin cGatewayClient::cGatewayClient%1117544868.initialization preserve=yes
  //## end cGatewayClient::cGatewayClient%1117544868.initialization
{
  //## begin cGatewayClient::cGatewayClient%1117544868.body preserve=yes
   _ClientId = client_id;
   _Client = new cClient(server_port, server_host);
  //## end cGatewayClient::cGatewayClient%1117544868.body
}


cGatewayClient::~cGatewayClient()
{
  //## begin cGatewayClient::~cGatewayClient%.body preserve=yes
   DELETE_OBJECT(cClient,_Client)
  //## end cGatewayClient::~cGatewayClient%.body
}



//## Other Operations (implementation)
int cGatewayClient::GetValue (CONST_STRING_T cell_name, CONST_STRING_T var_spec, CHAR_T *buf, ULONG_T buf_size)
{
  //## begin cGatewayClient::GetValue%1117544869.body preserve=yes
   char msg[0x500] = {0};
   SafePrintf(msg, sizeof(msg), "get(%s,%s)", cell_name, var_spec);
   cStreamMsg request(msg, strlen(msg) + 1);
   cStreamMsg reply;
   int rc = _Client->Request(request, reply);
   if (rc == 0) {
      memcpy(buf, reply.MsgBuf(), _MIN_(reply.MsgLen(), buf_size));
      return 0;
   } else {
      return rc;
   }
  //## end cGatewayClient::GetValue%1117544869.body
}

int cGatewayClient::SetValue (CONST_STRING_T cell_name, CONST_STRING_T var_spec, CONST_STRING_T value)
{
  //## begin cGatewayClient::SetValue%1117544870.body preserve=yes
return -1;
  //## end cGatewayClient::SetValue%1117544870.body
}

int cGatewayClient::GetPage (CONST_STRING_T cell_name, CONST_STRING_T page, CHAR_T *buf, ULONG_T buf_size)
{
  //## begin cGatewayClient::GetPage%1127151467.body preserve=yes
   char msg[0x500] = {0};
   SafePrintf(msg, sizeof(msg), "getpage(%s,%s)", cell_name, page);
   cStreamMsg request(msg, strlen(msg) + 1);
   cStreamMsg reply;
   int rc = _Client->Request(request, reply);
   if (rc == 0) {
      memcpy(buf, reply.MsgBuf(), _MIN_(reply.MsgLen(), buf_size));
      return 0;
   } else {
      return rc;
   }
  //## end cGatewayClient::GetPage%1127151467.body
}

int cGatewayClient::GetContextList (CHAR_T *buf, ULONG_T buf_size)
{
  //## begin cGatewayClient::GetContextList%1117544871.body preserve=yes
   char msg[0x500] = {0};
   SafePrintf(msg, sizeof(msg), "clist()");
   cStreamMsg request(msg, strlen(msg) + 1);
   cStreamMsg reply;
   int rc = _Client->Request(request, reply);
   if (rc == 0) {
      memcpy(buf, reply.MsgBuf(), _MIN_(reply.MsgLen(), buf_size));
      return 0;
   } else {
      return rc;
   }
  //## end cGatewayClient::GetContextList%1117544871.body
}

int cGatewayClient::Request (CONST_STRING_T cell_name, CONST_STRING_T request, CHAR_T *buf, ULONG_T buf_size)
{
  //## begin cGatewayClient::Request%1136191750.body preserve=yes
   char msg[0x500] = {0};
   SafePrintf(msg, sizeof(msg), "request(%s,%s)", cell_name, request);
   cStreamMsg request_msg(msg, strlen(msg) + 1);
   cStreamMsg reply;
   int rc = _Client->Request(request_msg, reply);
   if (rc == 0) {
      memcpy(buf, reply.MsgBuf(), _MIN_(reply.MsgLen(), buf_size));
      return 0;
   } else {
      return rc;
   }
  //## end cGatewayClient::Request%1136191750.body
}

// Additional Declarations
  //## begin cGatewayClient%429C5CE7035B.declarations preserve=yes
  //## end cGatewayClient%429C5CE7035B.declarations

//## begin module%429C5CE7035B.epilog preserve=yes
//## end module%429C5CE7035B.epilog
