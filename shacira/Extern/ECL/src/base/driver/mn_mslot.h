// ===========================================================================
// base/driver/mn_mslot.h                                       ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMsgNode
//     |
//     +--cMsgNodeMSLOT
// 
// ===========================================================================

#ifndef __ecl_mn_mslot__
#define __ecl_mn_mslot__


// Base class header
#include "base/driver/mn.h"


namespace ecl {


// ===========================================================================
// Definition cMsgNodeMSLOT
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeMSLOT
//
// ===========================================================================

class cMsgNodeMSLOT : public cMsgNode {

public:

   cMsgNodeMSLOT(cString name, int send_mode);

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

   void *_write_mslot;
   void *_read_mslot;

};

}; // namespace ecl


#endif // __ecl_mn_mslot__

