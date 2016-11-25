// ===========================================================================
// base/driver/mn_local.h                                       ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMsgNode
//     |
//     +--cMsgNodeLOCAL
// 
// ===========================================================================

#ifndef __ecl_mn_local__
#define __ecl_mn_local__


// Base class header
#include "base/driver/mn.h"

// Other ECL header
#include "base/queue.h"
#include "base/sharedmem.h"
#include "base/semaphore.h"


namespace ecl {


// ===========================================================================
// Definition cMsgNodeLOCAL
// ---------------------------------------------------------------------------
//
// Verwendung der protokollspezifischen Zusatzdaten bei benanntem MsgNode:
//
//  - prd1 ist 1
//  - prd2 enthält die eindeutige ID einer Reply-Queue, wenn eine Antwort
//    auf diese Meldung erwartet wird. Die Reply-Queue hat den generischen
//    Namen "ecl_rq<id>" (wobei <id> die Dezimalform der Queue-ID ist).
//    Wenn keine Antwort erwartet wird, ist prd1 = 0
//
// Verwendung der protokollspezifischen Zusatzdaten bei anonymem MsgNode:
//
//  - prd1 ist 2
//  - prd2 ist ein Zeiger auf die anonyme Reply-Queue.
//
// cMsgNode
//  +--cMsgNodeLOCAL
//
// ===========================================================================

class cMsgNodeLOCAL : public cMsgNode {

public:

   cMsgNodeLOCAL(int send_mode);
   cMsgNodeLOCAL(cString name, int send_mode);
   ~cMsgNodeLOCAL();

   virtual bool ping();
   virtual void createChannel(int msg_count, int msg_size);
   virtual void closeChannel();
   virtual void connectToChannel();
   virtual void disconnectFromChannel();
   virtual cString getFullName() const;
   virtual void sendMsg(cMsg msg);
   virtual cMsg callMsg(cMsg msg, int timeout);
   virtual cMsg receiveMsg();
   virtual bool mustReplyMsg(const cMsg& msg_to_reply);
   virtual void replyMsg(const cMsg& msg_to_reply, cMsg reply_msg);

private:

   unsigned long createUniqueId() const;
   void sendMsgToQueue(cQueueRaw *queue, cMsg msg);
   cMsg receiveMsgFromQueue(cQueueRaw *queue);

private:

   cQueueRaw *queue;
   cQueueRaw *reply_queue;
   unsigned long reply_id;

   static cSharedMem cnt_mem;    // Zaehler fuer rechnerweit eindeutige ID
   static cMutexSem cnt_sem;     // Schutzsemaphore fuer obigen Zaehler

};

}; // namespace ecl


#endif // __ecl_mn_local__

