//## begin module%3F82FE2F0157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F82FE2F0157.cm

//## begin module%3F82FE2F0157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F82FE2F0157.cp

//## Module: cLocalChannel%3F82FE2F0157; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cLocalChannel.cpp

//## begin module%3F82FE2F0157.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F82FE2F0157.additionalIncludes

//## begin module%3F82FE2F0157.includes preserve=yes
//## end module%3F82FE2F0157.includes

// eb_msg
#include "base/eb_msg.hpp"
// cTransientObject
#include "System/Objects/cTransientObject.h"
// cLocalChannel
#include "System/Channel/cLocalChannel.h"
// cAdapter
#include "System/Channel/cAdapter.h"
//## begin module%3F82FE2F0157.additionalDeclarations preserve=yes
//## end module%3F82FE2F0157.additionalDeclarations


// Class cLocalChannel 

//## begin cLocalChannel::Size%42D22FA401E4.attr preserve=no  public: static ULONG_T {U} 0x4000
ULONG_T cLocalChannel::_Size = 0xFFFF;
//## end cLocalChannel::Size%42D22FA401E4.attr




cLocalChannel::cLocalChannel()
  //## begin cLocalChannel::cLocalChannel%.hasinit preserve=no
      : _MsgBox(NULL)
  //## end cLocalChannel::cLocalChannel%.hasinit
  //## begin cLocalChannel::cLocalChannel%.initialization preserve=yes
  //## end cLocalChannel::cLocalChannel%.initialization
{
  //## begin cLocalChannel::cLocalChannel%.body preserve=yes
   _Type = "LocalChannel";
   _MsgBox = new cMsgBox(_Size, sizeof(AsyncMessage));
  //## end cLocalChannel::cLocalChannel%.body
}

cLocalChannel::cLocalChannel(const cLocalChannel &right)
  //## begin cLocalChannel::cLocalChannel%copy.hasinit preserve=no
      : _MsgBox(NULL)
  //## end cLocalChannel::cLocalChannel%copy.hasinit
  //## begin cLocalChannel::cLocalChannel%copy.initialization preserve=yes
  //## end cLocalChannel::cLocalChannel%copy.initialization
{
  //## begin cLocalChannel::cLocalChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cLocalChannel::cLocalChannel%copy.body
}

cLocalChannel::cLocalChannel (CONST_STRING_T channel_name)
  //## begin cLocalChannel::cLocalChannel%1065547486.hasinit preserve=no
      : _MsgBox(NULL)
  //## end cLocalChannel::cLocalChannel%1065547486.hasinit
  //## begin cLocalChannel::cLocalChannel%1065547486.initialization preserve=yes
  , cChannel(channel_name)
  //## end cLocalChannel::cLocalChannel%1065547486.initialization
{
  //## begin cLocalChannel::cLocalChannel%1065547486.body preserve=yes
   _Type = "LocalChannel";
   _Name = channel_name;
   _MsgBox = new cMsgBox(_Size, sizeof(AsyncMessage));
  //## end cLocalChannel::cLocalChannel%1065547486.body
}


cLocalChannel::~cLocalChannel()
{
  //## begin cLocalChannel::~cLocalChannel%.body preserve=yes
   Stop();
   DELETE_OBJECT(cMsgBox, _MsgBox);
  //## end cLocalChannel::~cLocalChannel%.body
}



//## Other Operations (implementation)
void cLocalChannel::Start ()
{
  //## begin cLocalChannel::Start%1072724216.body preserve=yes
   cChannel::Start();
  //## end cLocalChannel::Start%1072724216.body
}

void cLocalChannel::Stop ()
{
  //## begin cLocalChannel::Stop%1072724217.body preserve=yes
   AsyncMessage msg_data = {0};
   msg_data.msg_id = MSG_ID_TERMINATE;
   msg_data.object = NULL;
   _MsgBox->send(cMsg(MSG_ID_TERMINATE, sizeof(msg_data), &msg_data));
   cChannel::Stop();
  //## end cLocalChannel::Stop%1072724217.body
}

BOOL_T cLocalChannel::ObjectGetParam (CONST_STRING_T name, STRING_T &value)
{
  //## begin cLocalChannel::ObjectGetParam%1075904923.body preserve=yes
   return false;
  //## end cLocalChannel::ObjectGetParam%1075904923.body
}

BOOL_T cLocalChannel::ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value)
{
  //## begin cLocalChannel::ObjectSetParam%1075904924.body preserve=yes
   return false;
  //## end cLocalChannel::ObjectSetParam%1075904924.body
}

INT_T cLocalChannel::MainFunc (void *extra)
{
  //## begin cLocalChannel::MainFunc%1065547489.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
   cMsg msg;
   while (true) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      msg = _MsgBox->receive();
      int msg_id = msg.getMsgId();
      if (msg_id == MSG_ID_TERMINATE) {
			break;
      } else if (msg_id == MSG_ID_OBJECT) {
			AsyncMessage * msg_data = (AsyncMessage*)msg.getData();
         cTransientObject * object = msg_data->object;
         Emit(object);
         object->Release();
         __ECL_ATOMIC_DECREMENT__(_Fill);
      } else {
			throw cError(ASYNC_CHANNEL_UNKNOWN_MSG_ID, 0, _Name.c_str(),
				          cConvUtils::StringValue(msg_id).c_str());
      }
MAINFUNC_LOOP_EPILOG
   }
   return 0;
MAINFUNC_EPILOG
  //## end cLocalChannel::MainFunc%1065547489.body
}

void cLocalChannel::Listen ()
{
  //## begin cLocalChannel::Listen%1065703995.body preserve=yes
  //## end cLocalChannel::Listen%1065703995.body
}

void cLocalChannel::StopListen ()
{
  //## begin cLocalChannel::StopListen%1065629499.body preserve=yes
  //## end cLocalChannel::StopListen%1065629499.body
}

void cLocalChannel::Send (cTransientObject *object)
{
  //## begin cLocalChannel::Send%1065547487.body preserve=yes
	object->AddRef();
   AsyncMessage msg_data = {0};
   msg_data.msg_id = MSG_ID_OBJECT;
   msg_data.object = object;
   cObjectLock __lock__(&_SendMutex);
   _MsgBox->send(cMsg(MSG_ID_OBJECT, sizeof(msg_data), &msg_data));
   __ECL_ATOMIC_INCREMENT__(_Fill);
  //## end cLocalChannel::Send%1065547487.body
}

ULONG_T cLocalChannel::Size ()
{
  //## begin cLocalChannel::Size%1124211832.body preserve=yes
   return _Size;
  //## end cLocalChannel::Size%1124211832.body
}

// Additional Declarations
  //## begin cLocalChannel%3F82FE2F0157.declarations preserve=yes
  //## end cLocalChannel%3F82FE2F0157.declarations

//## begin module%3F82FE2F0157.epilog preserve=yes
//## end module%3F82FE2F0157.epilog
