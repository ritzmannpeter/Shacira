// ===========================================================================
// base/driver/mn_queue.h                                       ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMsgNode
//     |
//     +--cMsgNodeQUEUE
// 
// ===========================================================================

#ifndef __ecl_mn_queue__
#define __ecl_mn_queue__


// Base class header
#include "base/driver/mn.h"


namespace ecl {


// ===========================================================================
// Definition cMsgNodeQUEUE
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeQUEUE
//
// ===========================================================================

class cMsgNodeQUEUE : public cMsgNode {

public:

   cMsgNodeQUEUE(cString name, int send_mode);

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

   unsigned long write_queue;
   unsigned long read_queue;
   unsigned long sync_sema;

};


}; // namespace ecl


#endif // __ecl_mn_queue__

