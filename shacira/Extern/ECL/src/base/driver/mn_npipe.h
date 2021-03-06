// ===========================================================================
// base/driver/mn_npipe.h                                       ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cMsgNode
//     |
//     +--cMsgNodeNPIPE
// 
// ===========================================================================

#ifndef __ecl_mn_npipe__
#define __ecl_mn_npipe__


// Base class header
#include "base/driver/mn.h"


namespace ecl {


// Forward-Deklarationen
// ===========================================================================

class cNpServer;
class cNpClient;


// ===========================================================================
// Definition cMsgNodeNPIPE
// ---------------------------------------------------------------------------
//
// cBase
//  +--cMsgNode
//      +--cMsgNodeNPIPE
//
// ===========================================================================

class cMsgNodeNPIPE : public cMsgNode {

public:

   cMsgNodeNPIPE(cString name, int send_mode);

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

   cNpServer *server;
   cNpClient *client;

};

}; // namespace ecl


#endif // __ecl_mn_npipe__

