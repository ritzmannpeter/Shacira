
#ifndef __ipc__
#define __ipc__

/*.SI.***********************************************************************/
#include <syntax.h>
#include <stypes.h>
/*.EI.***********************************************************************/

GLOBAL CID_T CreateConnection(const char * name, int channel, int msg_size,
                              void * data, SIZE_T data_len);
GLOBAL CID_T Connect(const char * name, int channel, int msg_size,
                     void * data, SIZE_T data_len);
GLOBAL int DisConnect(CID_T cid);
GLOBAL int SendMsg(CID_T cid, void * send_msg, SIZE_T msg_len,
                   void * reply_msg, SIZE_T reply_len);
GLOBAL int ReceiveMsg(CID_T cid, void * rcv_msg, SIZE_T rcv_len);
GLOBAL int ReplyMsg(CID_T cid, void * reply_msg, SIZE_T reply_len);

#endif /* __ipc__ */
