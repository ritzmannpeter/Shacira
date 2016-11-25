//## begin module%3AA34DAE0338.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AA34DAE0338.cm

//## begin module%3AA34DAE0338.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AA34DAE0338.cp

//## Module: cAsyncChannel%3AA34DAE0338; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Threads\cAsyncChannel.cpp

//## begin module%3AA34DAE0338.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AA34DAE0338.additionalIncludes

//## begin module%3AA34DAE0338.includes preserve=yes
//## end module%3AA34DAE0338.includes

// eb_msg
#include "base/eb_msg.hpp"
// cTransientObject
#include "System/Objects/cTransientObject.h"
// cAsyncChannel
#include "System/Threads/cAsyncChannel.h"
//## begin module%3AA34DAE0338.additionalDeclarations preserve=yes

#define ASYNC_QUEUE_SIZE	10

typedef struct
{
	INT_T msg_id;
	cTransientObject * object;
}	AsyncMessage;

#define MSG_ID_TERMINATE		-1
#define MSG_ID_OBJECT			1

//## end module%3AA34DAE0338.additionalDeclarations


// Class cAsyncChannel 


cAsyncChannel::cAsyncChannel()
  //## begin cAsyncChannel::cAsyncChannel%.hasinit preserve=no
      : _ReceiveBox(NULL)
  //## end cAsyncChannel::cAsyncChannel%.hasinit
  //## begin cAsyncChannel::cAsyncChannel%.initialization preserve=yes
  //## end cAsyncChannel::cAsyncChannel%.initialization
{
  //## begin cAsyncChannel::cAsyncChannel%.body preserve=yes
   _ReceiveBox = new cMsgBox(ASYNC_QUEUE_SIZE, sizeof(AsyncMessage));
  //## end cAsyncChannel::cAsyncChannel%.body
}

cAsyncChannel::cAsyncChannel(const cAsyncChannel &right)
  //## begin cAsyncChannel::cAsyncChannel%copy.hasinit preserve=no
      : _ReceiveBox(NULL)
  //## end cAsyncChannel::cAsyncChannel%copy.hasinit
  //## begin cAsyncChannel::cAsyncChannel%copy.initialization preserve=yes
  //## end cAsyncChannel::cAsyncChannel%copy.initialization
{
  //## begin cAsyncChannel::cAsyncChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cAsyncChannel::cAsyncChannel%copy.body
}


cAsyncChannel::~cAsyncChannel()
{
  //## begin cAsyncChannel::~cAsyncChannel%.body preserve=yes
   Stop();
   DELETE_OBJECT(cMsgBox, _ReceiveBox);
  //## end cAsyncChannel::~cAsyncChannel%.body
}



//## Other Operations (implementation)
void cAsyncChannel::Stop ()
{
  //## begin cAsyncChannel::Stop%983778327.body preserve=yes
   AsyncMessage msg_data = {0};
   msg_data.msg_id = MSG_ID_TERMINATE;
   msg_data.object = NULL;
   _ReceiveBox->send(cMsg(MSG_ID_TERMINATE, sizeof(msg_data), &msg_data));
   cControlThread::Stop();
  //## end cAsyncChannel::Stop%983778327.body
}

INT_T cAsyncChannel::MainFunc (void *extra)
{
  //## begin cAsyncChannel::MainFunc%983778329.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
   cMsg msg;
   while (true) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      msg = _ReceiveBox->receive();
      int msg_id = msg.getMsgId();
      if (msg_id == MSG_ID_TERMINATE) {
			break;
      } else if (msg_id == MSG_ID_OBJECT) {
			AsyncMessage * msg_data = (AsyncMessage*)msg.getData();
			cTransientObject * object = msg_data->object;
         if (object == NULL) {
				throw cError(ASYNC_CHANNEL_NULL_OBJECT, 0, _Name.c_str());
			} else if (object->IsInvalid()) {
				throw cError(ASYNC_CHANNEL_INVALID_OBJECT, 0, _Name.c_str());
			} else {
				MessageFunc(object);
			}
      } else {
			throw cError(ASYNC_CHANNEL_UNKNOWN_MSG_ID, 0, _Name.c_str(),
				          cConvUtils::StringValue(msg_id).c_str());
      }
MAINFUNC_LOOP_EPILOG
   }
   return 0;
MAINFUNC_EPILOG
  //## end cAsyncChannel::MainFunc%983778329.body
}

BOOL_T cAsyncChannel::Send (cTransientObject *object)
{
  //## begin cAsyncChannel::Send%983778336.body preserve=yes
	object->AddRef();
   AsyncMessage msg_data = {0};
   msg_data.msg_id = MSG_ID_OBJECT;
   msg_data.object = object;
   _ReceiveBox->send(cMsg(MSG_ID_OBJECT, sizeof(msg_data), &msg_data));
   return true;
  //## end cAsyncChannel::Send%983778336.body
}

// Additional Declarations
  //## begin cAsyncChannel%3AA34DAE0338.declarations preserve=yes
  //## end cAsyncChannel%3AA34DAE0338.declarations

//## begin module%3AA34DAE0338.epilog preserve=yes
//## end module%3AA34DAE0338.epilog
