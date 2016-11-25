//## begin module%429C6E310167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429C6E310167.cm

//## begin module%429C6E310167.cp preserve=no
//	Copyright © 2002 - 2010 by
//	2i Industrial Informatics GmbH
//## end module%429C6E310167.cp

//## Module: cGatewayServer%429C6E310167; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cGatewayServer.cpp

//## begin module%429C6E310167.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%429C6E310167.additionalIncludes

//## begin module%429C6E310167.includes preserve=yes
//## end module%429C6E310167.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cContext
#include "System/Database/cContext.h"
// cGatewayServer
#include "Control/Cell/cGatewayServer.h"
// cGateway
#include "Control/Cell/cGateway.h"
//## begin module%429C6E310167.additionalDeclarations preserve=yes
//## end module%429C6E310167.additionalDeclarations


// Class cGatewayServer 



cGatewayServer::cGatewayServer()
  //## begin cGatewayServer::cGatewayServer%.hasinit preserve=no
      : _Gateway(NULL), _Process(NULL)
  //## end cGatewayServer::cGatewayServer%.hasinit
  //## begin cGatewayServer::cGatewayServer%.initialization preserve=yes
  //## end cGatewayServer::cGatewayServer%.initialization
{
  //## begin cGatewayServer::cGatewayServer%.body preserve=yes
  //## end cGatewayServer::cGatewayServer%.body
}

cGatewayServer::cGatewayServer(const cGatewayServer &right)
  //## begin cGatewayServer::cGatewayServer%copy.hasinit preserve=no
      : _Gateway(NULL), _Process(NULL)
  //## end cGatewayServer::cGatewayServer%copy.hasinit
  //## begin cGatewayServer::cGatewayServer%copy.initialization preserve=yes
  //## end cGatewayServer::cGatewayServer%copy.initialization
{
  //## begin cGatewayServer::cGatewayServer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGatewayServer::cGatewayServer%copy.body
}

cGatewayServer::cGatewayServer (cGateway *gateway, USHORT_T listener_port, cSHProcess *process)
  //## begin cGatewayServer::cGatewayServer%1117548694.hasinit preserve=no
      : _Gateway(NULL), _Process(NULL)
  //## end cGatewayServer::cGatewayServer%1117548694.hasinit
  //## begin cGatewayServer::cGatewayServer%1117548694.initialization preserve=yes
  , cServer(listener_port)
  //## end cGatewayServer::cGatewayServer%1117548694.initialization
{
  //## begin cGatewayServer::cGatewayServer%1117548694.body preserve=yes
   _Gateway = gateway;
   _Process = process;
  //## end cGatewayServer::cGatewayServer%1117548694.body
}


cGatewayServer::~cGatewayServer()
{
  //## begin cGatewayServer::~cGatewayServer%.body preserve=yes
  //## end cGatewayServer::~cGatewayServer%.body
}



//## Other Operations (implementation)
void cGatewayServer::Request (cStreamMsg &in_msg, cStreamMsg &out_msg)
{
  //## begin cGatewayServer::Request%1117545272.body preserve=yes
   char cell_name[0x200] = {0};
   char var_spec[0x200] = {0};
   char request[0x200] = {0};
   if (sscanf((char*)in_msg.MsgBuf(), "get(%[^,],%[^)])", cell_name, var_spec) == 2) {
      STRING_T value;
      try {
         _Gateway->Get(var_spec, value);
         out_msg.Allocate(value.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), value.c_str(), value.size()+1);
         return;
      } catch (cError & e) {
         STRING_T msg = (const char*)e;
         out_msg.Allocate(msg.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
         return;
      } catch (...) {
         STRING_T msg = "unhandled exception";
         out_msg.Allocate(msg.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
         return;
      }
   } else if (sscanf((char*)in_msg.MsgBuf(), "getpage(%[^,],%[^)])", cell_name, request) == 2) {
      STRING_T value;
      try {
         _Gateway->GetPage(request, value);
         out_msg.Allocate(value.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), value.c_str(), value.size()+1);
         return;
      } catch (cError & e) {
         STRING_T msg = (const char*)e;
         out_msg.Allocate(msg.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
         return;
      } catch (...) {
         STRING_T msg = "unhandled exception";
         out_msg.Allocate(msg.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
         return;
      }
   } else if (sscanf((char*)in_msg.MsgBuf(), "request(%[^,],%[^)])", cell_name, request) == 2) {
      STRING_T response;
      try {
         _Gateway->Request(request, response);
         out_msg.Allocate(response.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), response.c_str(), response.size()+1);
         return;
      } catch (cError & e) {
         STRING_T msg = (const char*)e;
         out_msg.Allocate(msg.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
         return;
      } catch (...) {
         STRING_T msg = "unhandled exception";
         out_msg.Allocate(msg.size()+1);
         SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
         return;
      }
   } else if (sscanf((char*)in_msg.MsgBuf(), "clist%s", cell_name) == 1) {
      STRING_T msg;
      if (_Process != NULL) {
         STRING_LIST_T context_names;
         _Process->ContextNames(context_names, REMOTE_CONTEXTS);
         int contexts = context_names.size();
         if (context_names.size() > 0) {
            STRING_LIST_T::const_iterator i = context_names.begin();
            while (i != context_names.end()) {
               STRING_T context_name = (*i);
               msg += context_name.c_str();
               msg += ",";
               i++;
            }
         }
      }
      for (int j=0; j<100; j++) {
         char name[0x100] = {0};
         SafePrintf(name, sizeof(name), "m%d", j+1);
         msg += ",";
         msg += name;
      }
      out_msg.Allocate(msg.size()+1);
      SafeStrCpy((char*)out_msg.MsgBuf(), msg.c_str(), msg.size()+1);
      return;
   }
   out_msg.Allocate(20);
   SafeStrCpy((char*)out_msg.MsgBuf(), (char*)in_msg.MsgBuf(), 20);
  //## end cGatewayServer::Request%1117545272.body
}

// Additional Declarations
  //## begin cGatewayServer%429C6E310167.declarations preserve=yes
  //## end cGatewayServer%429C6E310167.declarations

//## begin module%429C6E310167.epilog preserve=yes
//## end module%429C6E310167.epilog
