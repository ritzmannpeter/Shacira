//## begin module%42DE0A72037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42DE0A72037A.cm

//## begin module%42DE0A72037A.cp preserve=no
//	Copyright © 2002 - 2016 by
//	2i Industrial Informatics GmbH
//## end module%42DE0A72037A.cp

//## Module: cInternalBridge%42DE0A72037A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cInternalBridge.cpp

//## begin module%42DE0A72037A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%42DE0A72037A.additionalIncludes

//## begin module%42DE0A72037A.includes preserve=yes
//## end module%42DE0A72037A.includes

// eb_msg
#include "base/eb_msg.hpp"
// cCellProxy
#include "System/Process/cCellProxy.h"
// cDataChange
#include "System/Objects/cDataChange.h"
// cInternalBridge
#include "System/Channel/cInternalBridge.h"
// cClients
#include "Client/ClientData/cClients.h"
//## begin module%42DE0A72037A.additionalDeclarations preserve=yes

#define LOGIN_THRESHHOLD  20

//## end module%42DE0A72037A.additionalDeclarations


// Class cInternalBridge 








cInternalBridge::cInternalBridge()
  //## begin cInternalBridge::cInternalBridge%.hasinit preserve=no
      : _ClientId(0), _IsService(false), _ErrCount(0), _Synchronized(false), _CellProxy(NULL)
  //## end cInternalBridge::cInternalBridge%.hasinit
  //## begin cInternalBridge::cInternalBridge%.initialization preserve=yes
  //## end cInternalBridge::cInternalBridge%.initialization
{
  //## begin cInternalBridge::cInternalBridge%.body preserve=yes
_ASSERT_UNCOND
  //## end cInternalBridge::cInternalBridge%.body
}

cInternalBridge::cInternalBridge(const cInternalBridge &right)
  //## begin cInternalBridge::cInternalBridge%copy.hasinit preserve=no
      : _ClientId(0), _IsService(false), _Synchronized(false), _CellProxy(NULL)
  //## end cInternalBridge::cInternalBridge%copy.hasinit
  //## begin cInternalBridge::cInternalBridge%copy.initialization preserve=yes
  //## end cInternalBridge::cInternalBridge%copy.initialization
{
  //## begin cInternalBridge::cInternalBridge%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cInternalBridge::cInternalBridge%copy.body
}

cInternalBridge::cInternalBridge (CONST_STRING_T name)
  //## begin cInternalBridge::cInternalBridge%1121860894.hasinit preserve=no
      : _ClientId(0), _IsService(false), _ErrCount(0), _Synchronized(false), _CellProxy(NULL)
  //## end cInternalBridge::cInternalBridge%1121860894.hasinit
  //## begin cInternalBridge::cInternalBridge%1121860894.initialization preserve=yes
  , cLocalChannel(name)
  //## end cInternalBridge::cInternalBridge%1121860894.initialization
{
  //## begin cInternalBridge::cInternalBridge%1121860894.body preserve=yes
   _IsService = true;
  //## end cInternalBridge::cInternalBridge%1121860894.body
}

cInternalBridge::cInternalBridge (cCellProxy *cell_proxy, ULONG_T client_id, CONST_STRING_T name)
  //## begin cInternalBridge::cInternalBridge%1121845390.hasinit preserve=no
      : _ClientId(0), _IsService(false), _ErrCount(0), _Synchronized(false), _CellProxy(NULL)
  //## end cInternalBridge::cInternalBridge%1121845390.hasinit
  //## begin cInternalBridge::cInternalBridge%1121845390.initialization preserve=yes
  , cLocalChannel(name)
  //## end cInternalBridge::cInternalBridge%1121845390.initialization
{
  //## begin cInternalBridge::cInternalBridge%1121845390.body preserve=yes
_ASSERT_COND(cell_proxy != NULL)
   _IsService = false;
   _CellProxy = cell_proxy;
   _ClientId = client_id;
  //## end cInternalBridge::cInternalBridge%1121845390.body
}


cInternalBridge::~cInternalBridge()
{
  //## begin cInternalBridge::~cInternalBridge%.body preserve=yes
  //## end cInternalBridge::~cInternalBridge%.body
}



//## Other Operations (implementation)
INT_T cInternalBridge::MainFunc (void *extra)
{
  //## begin cInternalBridge::MainFunc%1121845391.body preserve=yes
   if (_IsService) {
MAINFUNC_PROLOG(_Name.c_str())
      cMsg msg;
      while (true) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
         msg = _MsgBox->receive();
         if (_Fill > 0) {
            // only approximated fill computation
            _Fill--;
         }
         int msg_id = msg.getMsgId();
         if (msg_id == MSG_ID_TERMINATE) {
   			break;
         } else if (msg_id == MSG_ID_OBJECT) {
			   AsyncMessage * msg_data = (AsyncMessage*)msg.getData();
			   cTransientObject * object = msg_data->object;
            if (object == NULL) {
               ErrorPrintf("null object in local channel %s (%d,%d)\n",
                           _Name.c_str(), _Size, _Fill);
            } else if (object->IsInvalid()) {
               ULONG_T object_type = UNDEFINED;
               try {
                  object_type = object->_Type;
               } catch (...) {
               }
               ErrorPrintf("invalid object %p of type %d ? in local channel %s (%d,%d)\n",
                           object, object_type, _Name.c_str(), _Size, _Fill);
			   } else {
               Deliver(object);
               object->Release();
		   	}
         } else {
   			throw cError(ASYNC_CHANNEL_UNKNOWN_MSG_ID, 0, _Name.c_str(),
		   		          cConvUtils::StringValue(msg_id).c_str());
         }
MAINFUNC_LOOP_EPILOG
      }
      return 0;
MAINFUNC_EPILOG
   } else {
MAINFUNC_PROLOG(_Name.c_str())
      while (Active()) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
         try {
            if (_CellProxy != NULL) {
               if (cClients::GetConnected()) {
                  _ErrCount++;
                  if (_ErrCount > LOGIN_THRESHHOLD ||
                      _ClientId == 0) {
                     cClients::SetConnected(false);
                  } else {
                     Synchronize();
                     cTransientObject * object = _CellProxy->GetEvent();
                     if (object != NULL) {
                        bool filter_object = false;
                        ULONG_T object_type = object->get_Type();
                        if (object_type == OT_DATA_CHANGE) {
                           cDataChange * data_change = (cDataChange*)object;
                           ULONG_T data_type = data_change->get_DataType();
                           if (data_type == SH_BYTE ||
                               data_type == SH_OBJECT) {
                              filter_object = true;
                              if (!filter_object) {
                                 STRING_T var_name = data_change->get_VarName();
                                 int i1 = data_change->get_Index1();
                                 int i2 = data_change->get_Index2();
                                 int i3 = data_change->get_Index3();
                                 int i4 = data_change->get_Index4();
                                 STRING_T svalue;
                                 _CellProxy->GetValue(var_name.c_str(), svalue, i1, i2, i3, i4);
                                 ULONG_T size = data_change->get_ValueSize();
                                 BUF_T cached_buf = cSystemUtils::CachedAlloc(var_name.c_str(),
                                                                           i1, i2, i3, i4,
                                                                           size);
                                 PTR_T mem_address = NULL;
                                 cConvUtils::String2Ptr(mem_address, svalue.c_str());
                                 if (mem_address != NULL) {
                                    _CellProxy->GetMemory(cached_buf, mem_address, size);
                                 }
                                 data_change->set_BufPtr(cached_buf);
                              }
                           }
                        }
                        if (object_type == OT_ALARM) {
                           int dummy = 0;
                        }
                        if (object_type == OT_INFO) {
                           int dummy = 0;
                        }
                        if (!filter_object) {
                           Emit(object);
                        }
                        object->Release();
                     } else {
                        cSystemUtils::Suspend(20);
                     }
                     _ErrCount = 0;
                     cClients::SetConnected(true);
                  }
               } else {
                  _ClientId = _CellProxy->Login(_UserName.c_str(), _Password.c_str());
                  InfoPrintf("client %d connected\n", _ClientId);
                  _ErrCount = 0;
                  cClients::SetConnected(true);
               }
            }
         } catch (cError & e) {
            ErrorPrintf("%s accessing server event queue in %s\n", (const char*)e, __thread_name__); \
         } catch (...) {
            ErrorPrintf("unhandled exception accessing server event queue in %s\n", __thread_name__); \
         }
MAINFUNC_LOOP_EPILOG
      }
      return 0;
MAINFUNC_EPILOG
   }
  //## end cInternalBridge::MainFunc%1121845391.body
}

void cInternalBridge::Deliver (cTransientObject *object)
{
  //## begin cInternalBridge::Deliver%1121845392.body preserve=yes
   if (_IsService) {
#ifdef RESTRICTED_DELIVERY
      /// restricted to data change, alarm and info events
      if (object->get_Type() == OT_DATA_CHANGE ||
          object->get_Type() == OT_ALARM ||
          object->get_Type() == OT_INFO) {
         cClients::AddObject(object);
      }
#else
      cClients::AddObject(object);
#endif
   }
  //## end cInternalBridge::Deliver%1121845392.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cInternalBridge::get_ClientId () const
{
  //## begin cInternalBridge::get_ClientId%42DE0E5202AF.get preserve=no
  return _ClientId;
  //## end cInternalBridge::get_ClientId%42DE0E5202AF.get
}

STRING_T cInternalBridge::get_UserName () const
{
  //## begin cInternalBridge::get_UserName%42DF919F01F4.get preserve=no
  return _UserName;
  //## end cInternalBridge::get_UserName%42DF919F01F4.get
}

void cInternalBridge::set_UserName (STRING_T value)
{
  //## begin cInternalBridge::set_UserName%42DF919F01F4.set preserve=no
  _UserName = value;
  //## end cInternalBridge::set_UserName%42DF919F01F4.set
}

STRING_T cInternalBridge::get_Password () const
{
  //## begin cInternalBridge::get_Password%42DF919F0203.get preserve=no
  return _Password;
  //## end cInternalBridge::get_Password%42DF919F0203.get
}

void cInternalBridge::set_Password (STRING_T value)
{
  //## begin cInternalBridge::set_Password%42DF919F0203.set preserve=no
  _Password = value;
  //## end cInternalBridge::set_Password%42DF919F0203.set
}

BOOL_T cInternalBridge::get_IsService () const
{
  //## begin cInternalBridge::get_IsService%42DE3C73004E.get preserve=no
  return _IsService;
  //## end cInternalBridge::get_IsService%42DE3C73004E.get
}

void cInternalBridge::Synchronize ()
{
   if (!_Synchronized) {
      ALARM_MAP_T alarms;
//      ULONG_T alarm_count = _Context->Alarms(0, alarms);
//      ULONG_T alarm_count = _CellProxy->GetValue(var_name.c_str(), svalue, i1, i2, i3, i4);

      _Synchronized = true;
   }
}

// Additional Declarations
  //## begin cInternalBridge%42DE0A72037A.declarations preserve=yes
  //## end cInternalBridge%42DE0A72037A.declarations

//## begin module%42DE0A72037A.epilog preserve=yes
//## end module%42DE0A72037A.epilog
