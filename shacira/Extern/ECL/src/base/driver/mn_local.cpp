// ===========================================================================
// base/driver/mn_local.cpp                                     ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// 
// ===========================================================================


// Interface header
#include "base/driver/mn_local.h"




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ etc.
const unsigned long IPC_ERROR = cBase::dbgError | cBase::dbgIpc;
const unsigned long IPC_WARN  = cBase::dbgWarn  | cBase::dbgIpc;

// Implementierung cMsgNodeLOCAL
// ===========================================================================

cSharedMem cMsgNodeLOCAL::cnt_mem("eclMSGCntMem", cSharedMem::memOpenOrCreate, sizeof(unsigned long));
cMutexSem cMsgNodeLOCAL::cnt_sem("eclMSGCntSem", cMutexSem::semOpenOrCreate);

cMsgNodeLOCAL::cMsgNodeLOCAL(int send_mode) :
   cMsgNode(send_mode)
{
   __ECL_STATISTIC__("cMsgNodeLOCAL(anonym)")
   queue = 0;
   reply_queue = 0;
   reply_id = 0;
}

cMsgNodeLOCAL::cMsgNodeLOCAL(cString name, int send_mode) :
   cMsgNode(name, send_mode)
{
   __ECL_STATISTIC__("cMsgNodeLOCAL")
   queue = 0;
   reply_queue = 0;
   reply_id = 0;
}

cMsgNodeLOCAL::~cMsgNodeLOCAL()
{
   delete reply_queue;
   delete queue;
}

bool cMsgNodeLOCAL::ping()
{
   if ( !isAnonymous() ) {
      return cQueueRaw::isAllocated(getFullName());
   } else {
      return true;
   }
}

void cMsgNodeLOCAL::createChannel(int msg_count, int msg_size)
{
   cQueueBase::PUT_MODE put_mode;

   switch ( getModeFull() ) {
   case cMsgRecipient::modeFullError:     put_mode = cQueueBase::putError; break;
   case cMsgRecipient::modeFullIgnore:    put_mode = cQueueBase::putIgnore; break;
   case cMsgRecipient::modeFullOverwrite: put_mode = cQueueBase::putOverwrite; break;
   default:                               put_mode = cQueueBase::putBlock; break;
   }

   switch ( getModeAlive() ) {
   case cMsgRecipient::modeAliveCreate:
      msg_count = max(msg_count, 16);
      msg_size = max(msg_size, 128);
      break;
   case cMsgRecipient::modeAliveIgnore:
      // Eventueller Fehler wird in connectToChannel() gefangen
      break;
   case cMsgRecipient::modeAliveError:
   default:
      // Default-Verhalten
      break;
   }

   cMsg empty_msg(0, 0, 0);
   if ( msg_size >= 0 )
      msg_size += getMsgLen(empty_msg);

   try {
      if ( isAnonymous() ) {
         queue = new0 cQueueRaw(msg_count, msg_size, put_mode);
      } else {
         queue = new0 cQueueRaw(msg_count, msg_size, getFullName(), put_mode);
      }
   } catch ( cErrBase ) {
      throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
   }
}

void cMsgNodeLOCAL::closeChannel()
{
   delete queue;
   queue = 0;
}

void cMsgNodeLOCAL::connectToChannel()
{
   if ( !queue ) {
      try {
         createChannel(-1, -1);
      } catch ( cErrBase ) {
         if ( getModeAlive() != cMsgRecipient::modeAliveIgnore )
            throw cErrMsg(cErrMsg::errOpenChannel, getFullName());
      }
   }
}

void cMsgNodeLOCAL::disconnectFromChannel()
{
   if ( queue )
      closeChannel();
}

cString cMsgNodeLOCAL::getFullName() const
{
   if ( isAnonymous() ) {
      return "<<Anonymous>>";
   } else {
      return "eclMQ" + getName();
   }
}

void cMsgNodeLOCAL::sendMsg(cMsg msg)
{
   if ( !queue )
      connectToChannel();
   if ( !queue && getModeAlive() == cMsgRecipient::modeAliveIgnore )
      return;
   sendMsgToQueue(queue, msg);
}

cMsg cMsgNodeLOCAL::callMsg(cMsg msg, int timeout)
{
   if ( !queue )
      connectToChannel();
   if ( !queue && getModeAlive() == cMsgRecipient::modeAliveIgnore )
      return cMsg();

   if ( timeout > 0 )
      __ECL_RELEASE_TEXT__(IPC_WARN, "MSG: Warning: Ignoring timeout parameter in cMsgRecipient::call()");

   if ( !isAnonymous() ) {
      if ( reply_id == 0 || reply_queue == 0 ) {
         reply_id = createUniqueId();
         reply_queue = new0 cQueueRaw(1, queue->getSize(), "eclRQ" + Str((int)reply_id));
      }
      setPrd1(msg, 1); // Kennung fuer benannte MsgBox
      setPrd2(msg, reply_id);
   } else {
      if ( reply_queue == 0 ) {
         reply_queue = new0 cQueueRaw(1, queue->getSize());
      }
      setPrd1(msg, 2); // Kennung fuer anonyme MsgBox
      setPrd2(msg, (int)(void *)reply_queue);
   }

   sendMsgToQueue(queue, msg);
   return receiveMsgFromQueue(reply_queue);
}

cMsg cMsgNodeLOCAL::receiveMsg()
{
   if ( !getWait() && queue->isEmpty() )
      return cMsg();
   return receiveMsgFromQueue(queue);
}

bool cMsgNodeLOCAL::mustReplyMsg(const cMsg& msg_to_reply)
{
   return getPrd1(msg_to_reply) != 0;
}


void cMsgNodeLOCAL::replyMsg(const cMsg& msg_to_reply, cMsg reply_msg)
{
   setPrd1(reply_msg, 0);
   setPrd2(reply_msg, 0);

   switch ( getPrd1(msg_to_reply) ) {
   case 1:
      {
         cQueueRaw reply_queue(-1, -1, "eclRQ" + Str(getPrd2(msg_to_reply)));
         sendMsgToQueue(&reply_queue, reply_msg);
      }
      break;
   case 2:
      sendMsgToQueue((cQueueRaw *)getPrd2(msg_to_reply), reply_msg);
      break;
   }
}

unsigned long cMsgNodeLOCAL::createUniqueId() const
{
   cnt_sem.request();
   unsigned long id = ++(*((unsigned long *)cnt_mem.getAdr()));
   cnt_sem.release();
   return id;
}

void cMsgNodeLOCAL::sendMsgToQueue(cQueueRaw *queue, cMsg msg)
{
   if ( queue == 0 ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "MSG: Tried to send to a non-opend queue");
      throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
   }

   int msg_len = getMsgLen(msg);
   if ( msg_len > queue->getSize() ) {
      __ECL_RELEASE_PRINTF__(IPC_ERROR, ("MSG: Tried to send a %d byte msg to a %d byte queue", msg_len, queue->getSize()));
      throw cErrMsg(cErrMsg::errMsgTooLong, getFullName());
   }

   queue->put(getMsg(msg), getMsgLen(msg));
}

cMsg cMsgNodeLOCAL::receiveMsgFromQueue(cQueueRaw *queue)
{
   char mem[1024];
   queue->get(mem, sizeof mem);

   cMsg msg = newMsg(mem);
   if ( !msg.isValid() ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "MSG: Received an invalid memory block");
      throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
   }

   return msg;
}




}; // namespace ecl

