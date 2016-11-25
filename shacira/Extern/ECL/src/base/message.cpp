// ===========================================================================
// base/message.cpp                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/message.h"

// Other ECL headers
#include "base/base_ex.h"
#include "base/thread.h"
#include "base/bprintf.h"

#include "base/driver/mn_local.h"
#include "base/driver/mn_queue.h"
#include "base/driver/mn_npipe.h"
#include "base/driver/mn_mslot.h"

//#define __Use_Named_Pipes__ /* Definieren, wenn Named Pipes gewuenscht */




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ etc.
const unsigned long IPC_ERROR = cBase::dbgError | cBase::dbgIpc;
const unsigned long IPC_WARN  = cBase::dbgWarn  | cBase::dbgIpc;

// Implementierung cErrMsg
// ===========================================================================

cErrMsg::cErrMsg(int err, const char *name) :
   cErrBase(err)
{
   setParam(0, name);
}




// Implementierung cMsg
// ===========================================================================

#define MSG_MAGIC    0x42424242
#define MSG_UNMAGIC  0x00000000

cMsg::cMsg()
{
   msg = 0;
}

cMsg::cMsg(int msg_id)
{
   if ( alloc(0) != 0 )
      msg->id = msg_id;
}

cMsg::cMsg(int msg_id, int size, const void *data)
{
   init(msg_id, data, size);
}

cMsg::cMsg(int msg_id, cString str)
{
   init(msg_id, (const char *)str, str.getLength() + 1);
}

cMsg::cMsg(int msg_id, const char *fmt, ...)
{
   va_list ap;
   char buf[1024];
   va_start(ap, fmt);
   int size = vbprintf(buf, fmt, ap);
   if ( size >= 0 )
      init(msg_id, buf, size);
   va_end(ap);
}

cMsg::cMsg(int msg_id, const char *fmt, va_list ap)
{
   char buf[1024];
   int size = vbprintf(buf, fmt, ap);
   if ( size >= 0 )
      init(msg_id, buf, size);
}

cMsg::cMsg(const cMsg& other)
{
   msg = other.msg;
   if ( msg )
      __ECL_ATOMIC_INCREMENT__(msg->refc);
}

cMsg::cMsg(const MSGHDR *foreign_msg)
{
   if ( foreign_msg != 0 ) {
      init(foreign_msg->id, foreign_msg->d, foreign_msg->size);
      msg->magic = foreign_msg->magic;
      msg->prd1 = foreign_msg->prd1;
      msg->prd2 = foreign_msg->prd2;
   }
}

cMsg::~cMsg()
{
   dealloc(msg);
}

cMsg& cMsg::operator=(const cMsg& other)
{
   if ( &other != this ) {
      dealloc(msg);
      msg = other.msg;
      if ( msg )
         __ECL_ATOMIC_INCREMENT__(msg->refc);
   }
   return *this;
}

bool cMsg::isValid() const
{
   return msg == 0 || msg->magic == MSG_MAGIC;
}

bool cMsg::isEmpty() const
{
   return msg == 0;
}

cMsg::MSGHDR * cMsg::alloc(int len)
{
   msg = (MSGHDR *)malloc(sizeof *msg + len - 1);
   msg->magic = MSG_MAGIC;
   msg->size = len;
   __ECL_ATOMIC_SET__(msg->refc,0)
   msg->prd1 = 0;
   msg->prd2 = 0;
   return msg;
}

void cMsg::dealloc(MSGHDR *& data)
{
   if ( data ) {
      if ( __ECL_ATOMIC_DECREMENT__(data->refc) == -1 ) {
         data->magic = MSG_UNMAGIC;
         free(data);
      }
      data = 0;
   }
}

bool cMsg::init(int msg_id, const void *data, int size)
{
   if ( alloc(size) != 0 && data != 0 ) {
      msg->id = msg_id;
      memcpy(msg->d, data, size);
      return true;
   }
   return false;
}




// Implementierung cMsgRecipient
// ===========================================================================

cMsgRecipient::cMsgRecipient(int send_mode)
{
   node = new0 cMsgNodeLOCAL(send_mode);
}

cMsgRecipient::cMsgRecipient(cString address_name, int send_mode)
{
   init(address_name, false, send_mode);
}

cMsgRecipient::cMsgRecipient(cString address_name, bool maybe_anonymous, int send_mode)
{
   init(address_name, maybe_anonymous, send_mode);
}

cMsgRecipient::~cMsgRecipient()
{
   node->disconnectFromChannel();
   delete node;
}

void cMsgRecipient::init(cString address_name, bool maybe_anonymous, int send_mode)
{
   cString name = cMsgNode::getName(address_name);
   if ( !maybe_anonymous && name.isEmpty() )
      throw cErrMsg(cErrMsg::errNoAnonymousRecipient, address_name);

   cString protocol = cMsgNode::getProtocol(address_name);
   node = 0;

   if ( protocol == "private" ) {
      protocol = "local";
      address_name += cStringf("@%ld", cThread::getCurrentProcessId());
   }

   if ( protocol == "local" ) {
      node = new0 cMsgNodeLOCAL(address_name, send_mode);
   } else if ( protocol == "npipe" ) {
      #if defined __Use_Named_Pipes__
         node = new0 cMsgNodeNPIPE(address_name, send_mode);
      #else
         throw cErrMsg(cErrMsg::errUnsupportedProtocol, protocol);
      #endif
   } else if ( protocol == "queue" ) {
      #if defined __ECL_OS2__
         node = new0 cMsgNodeQUEUE(address_name, send_mode);
      #else
         throw cErrMsg(cErrMsg::errUnsupportedProtocol, protocol);
      #endif
   } else if ( protocol == "mslot" ) {
      #if defined __ECL_W32__
         node = new0 cMsgNodeMSLOT(address_name, send_mode);
      #else
         throw cErrMsg(cErrMsg::errUnsupportedProtocol, protocol);
      #endif
   } else {
      throw cErrMsg(cErrMsg::errInvalidProtocol, protocol);
   }
}

cString cMsgRecipient::getName() const
{
   return node->getName();
}

cString cMsgRecipient::getAddress() const
{
   return node->getAddress();
}

bool cMsgRecipient::ping()
{
   return node->ping();
}

void cMsgRecipient::send(cMsg msg)
{
   if ( msg.isEmpty() ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "Tried to send empty message");
      throw cErrMsg(cErrMsg::errSendEmptyMsg, getFullName());
   }

   node->sendMsg(msg);
}

cMsg cMsgRecipient::call(cMsg msg, int timeout)
{
   if ( msg.isEmpty() ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "Tried to call with empty message");
      throw cErrMsg(cErrMsg::errSendEmptyMsg, getFullName());
   }

   return node->callMsg(msg, timeout);
}

cString cMsgRecipient::getFullName() const
{
   return node->getFullName();
}




// Implementierung cMsgBox
// ===========================================================================

cMsgBox::cMsgBox(int msg_count, int msg_size, int send_mode) :
   cMsgRecipient(send_mode)
{
   node->createChannel(msg_count, msg_size);
}

cMsgBox::cMsgBox(cString name, int msg_count, int msg_size, int send_mode) :
   cMsgRecipient(name, true, send_mode)
{
   node->createChannel(msg_count, msg_size);
}

cMsgBox::~cMsgBox()
{
   node->closeChannel();
}

void cMsgBox::setWait(bool wait)
{
   node->setWait(wait);
}

bool cMsgBox::getWait() const
{
   return node->getWait();
}

cMsg cMsgBox::receive()
{
   return node->receiveMsg();
}

bool cMsgBox::mustReply(const cMsg& msg_to_reply) const
{
   return node->mustReplyMsg(msg_to_reply);
}

void cMsgBox::reply(const cMsg& msg_to_reply, cMsg reply_msg)
{
   node->replyMsg(msg_to_reply, reply_msg);
}



}; // namespace ecl

