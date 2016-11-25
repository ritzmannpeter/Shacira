// ===========================================================================
// base/driver/mn_npipe.cpp                                     ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// 
// ===========================================================================


// Interface header
#include "base/driver/mn_npipe.h"

// Other ECL header
#include "base/namedpipe.h"





namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ etc.
const unsigned long IPC_ERROR = cBase::dbgError | cBase::dbgIpc;
const unsigned long IPC_WARN  = cBase::dbgWarn  | cBase::dbgIpc;

// Implementierung cMsgNodeNPIPE
// ===========================================================================

#define MAX_NAMEDPIPE_MSG_SIZE 512

cMsgNodeNPIPE::cMsgNodeNPIPE(cString name, int send_mode) :
   cMsgNode(name, send_mode)
{
   __ECL_STATISTIC__("cMsgNodeNPIPE")
   server = 0;
   client = 0;
}

bool cMsgNodeNPIPE::ping()
{
   __ECL_RELEASE_TEXT__(IPC_ERROR, "Win32: cMsgBox::ping() not implemented for Named Pipes");
   return true;
}

void cMsgNodeNPIPE::createChannel(int msg_count, int /*msg_size*/)
{
   server = new0 cNpServer(getFullName(), MAX_NAMEDPIPE_MSG_SIZE, msg_count);
}

void cMsgNodeNPIPE::closeChannel()
{
   delete server; server = 0;
}

void cMsgNodeNPIPE::connectToChannel()
{
   client = new0 cNpClient(getFullName());
}

void cMsgNodeNPIPE::disconnectFromChannel()
{
   delete client; client = 0;
}

cString cMsgNodeNPIPE::getFullName() const
{
   return getAddress() + ":" + getName();
}

void cMsgNodeNPIPE::sendMsg(cMsg msg)
{
   if ( client == 0 )
      connectToChannel();
   if ( client != 0 )
      client->write(getMsg(msg), getMsgLen(msg));
}

cMsg cMsgNodeNPIPE::callMsg(cMsg msg, int /*timeout*/)
{
   __ECL_RELEASE_TEXT__(IPC_WARN, "MSG: Warning: Ignoring cMsgRecipient::call() for Named Pipes");
   return cMsg();
}

cMsg cMsgNodeNPIPE::receiveMsg()
{
   char buf[MAX_NAMEDPIPE_MSG_SIZE];

   if ( server && server->read(buf, sizeof buf) < 0 )
      return cMsg();

   cMsg msg = newMsg(buf);

   if ( !msg.isValid() ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "NPipe: Received an invalid memory block");
      throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
   }

   return msg;
}

bool cMsgNodeNPIPE::mustReplyMsg(const cMsg& /*msg_to_reply*/)
{
   return false;
}

void cMsgNodeNPIPE::replyMsg(const cMsg& /*msg_to_reply*/, cMsg reply_msg)
{
   __ECL_RELEASE_TEXT__(IPC_WARN, "MSG: Warning: Ignoring cMsgBox::reply() for Named Pipes");
}




}; // namespace ecl

