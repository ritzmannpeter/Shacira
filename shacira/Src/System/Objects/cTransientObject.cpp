//## begin module%3A6BF14C0281.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A6BF14C0281.cm

//## begin module%3A6BF14C0281.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A6BF14C0281.cp

//## Module: cTransientObject%3A6BF14C0281; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cTransientObject.cpp

//## begin module%3A6BF14C0281.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A6BF14C0281.additionalIncludes

//## begin module%3A6BF14C0281.includes preserve=yes

/// PR 01.09.05 - changes with respect to thread synchronization
/// PR 16.11.05 - removed bug in Release that leads to problems in thread
///               synchronization

//## end module%3A6BF14C0281.includes

// cInfo
#include "System/Objects/cInfo.h"
// cTransientObject
#include "System/Objects/cTransientObject.h"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cRequest
#include "System/Objects/cRequest.h"
// cProgress
#include "System/Objects/cProgress.h"
// cUserInfo
#include "System/Objects/cUserInfo.h"
// cProxy
#include "System/Objects/cProxy.h"
// cAlarm
#include "System/Objects/cAlarm.h"
// cJobEntry
#include "System/Objects/cJobEntry.h"
// cJobSpec
#include "System/Objects/cJobSpec.h"
// cDataChange
#include "System/Objects/cDataChange.h"
// cState
#include "System/Objects/cState.h"
// cStaticObject
#include "System/Objects/cStaticObject.h"
// cEvent
#include "System/Objects/cEvent.h"
// cCosEventChannelProxy
#include "Orb/cCosEventChannelProxy.h"
// cCorbaCellProxy
#include "Orb/cCorbaCellProxy.h"
//## begin module%3A6BF14C0281.additionalDeclarations preserve=yes
#if defined(_WIN32)
#include <assert.h>
#endif
#include "System/Memory/cMemPool.h"
#include "System/Memory/cGarbageCollector.h"
//## end module%3A6BF14C0281.additionalDeclarations


// Class cTransientObject 

//## begin cTransientObject::ObjectCount%3A9242F001F3.attr preserve=no  public: static ULONG_T {U} 0
ATOMIC_T cTransientObject::_ObjectCount = 0;
//## end cTransientObject::ObjectCount%3A9242F001F3.attr

//## begin cTransientObject::ObjectNo%3A9FEAA100E4.attr preserve=no  public: static ULONG_T {U} 0
ATOMIC_T cTransientObject::_ObjectNo = 0;
//## end cTransientObject::ObjectNo%3A9FEAA100E4.attr














//## begin cTransientObject::ConstructObjectFuncAddress%4310870E0207.attr preserve=no  implementation: static OBJECT_FACTORY_T {U} NULL
OBJECT_FACTORY_T cTransientObject::_ConstructObjectFuncAddress = NULL;
//## end cTransientObject::ConstructObjectFuncAddress%4310870E0207.attr


cTransientObject::cTransientObject()
  //## begin cTransientObject::cTransientObject%.hasinit preserve=no
      : _BeginPattern(BEGIN_PATTERN), _ObjectIdent(0), _Type(UNDEFINED), _SubType(UNDEFINED), _EventCode(UNDEFINED), _ObjectFlags(0), _EndPattern(END_PATTERN), _Source(NULL)
  //## end cTransientObject::cTransientObject%.hasinit
  //## begin cTransientObject::cTransientObject%.initialization preserve=yes
  //## end cTransientObject::cTransientObject%.initialization
{
  //## begin cTransientObject::cTransientObject%.body preserve=yes
   __ECL_ATOMIC_SET__(_Deleted,0);
   __ECL_ATOMIC_SET__(_RefCount,0);
   if (_GarbageCollector == NULL) {
      _GarbageCollector = new cGarbageCollector;
   }
   AddRef();
   __ECL_ATOMIC_INCREMENT__(_ObjectCount);
   __ECL_ATOMIC_INCREMENT__(_ObjectNo);
   _ObjectIdent = _ObjectNo;
   _TimeStamp.Now();
  //## end cTransientObject::cTransientObject%.body
}

cTransientObject::cTransientObject(const cTransientObject &right)
  //## begin cTransientObject::cTransientObject%copy.hasinit preserve=no
      : _BeginPattern(BEGIN_PATTERN), _ObjectIdent(0), _Type(UNDEFINED), _SubType(UNDEFINED), _EventCode(UNDEFINED), _ObjectFlags(0), _EndPattern(END_PATTERN), _Source(NULL)
  //## end cTransientObject::cTransientObject%copy.hasinit
  //## begin cTransientObject::cTransientObject%copy.initialization preserve=yes
  //## end cTransientObject::cTransientObject%copy.initialization
{
  //## begin cTransientObject::cTransientObject%copy.body preserve=yes
   __ECL_ATOMIC_SET__(_Deleted,0);
   __ECL_ATOMIC_SET__(_RefCount,0);
   if (_GarbageCollector == NULL) {
      _GarbageCollector = new cGarbageCollector;
   }
   AddRef();
   __ECL_ATOMIC_INCREMENT__(_ObjectCount);
   __ECL_ATOMIC_INCREMENT__(_ObjectNo);
   _ObjectIdent = _ObjectNo;
   _Type = right._Type;
   _SubType = right._SubType;
   _TimeStamp = right._TimeStamp;
   _SourceName = right._SourceName;
   _CellName = right._CellName;
  //## end cTransientObject::cTransientObject%copy.body
}

cTransientObject::cTransientObject (cStaticObject *source)
  //## begin cTransientObject::cTransientObject%985248929.hasinit preserve=no
      : _BeginPattern(BEGIN_PATTERN), _ObjectIdent(0), _Type(UNDEFINED), _SubType(UNDEFINED), _EventCode(UNDEFINED), _ObjectFlags(0), _EndPattern(END_PATTERN), _Source(NULL)
  //## end cTransientObject::cTransientObject%985248929.hasinit
  //## begin cTransientObject::cTransientObject%985248929.initialization preserve=yes
  //## end cTransientObject::cTransientObject%985248929.initialization
{
  //## begin cTransientObject::cTransientObject%985248929.body preserve=yes
   __ECL_ATOMIC_SET__(_Deleted,0);
   __ECL_ATOMIC_SET__(_RefCount,0);
   if (_GarbageCollector == NULL) {
      _GarbageCollector = new cGarbageCollector;
   }
   AddRef();
   __ECL_ATOMIC_INCREMENT__(_ObjectCount);
   __ECL_ATOMIC_INCREMENT__(_ObjectNo);
   _ObjectIdent = _ObjectNo;
   _TimeStamp.Now();
   _Source = source;
   if (_Source != NULL) {
      _SourceName = _Source->get_Name().c_str();
   }
  //## end cTransientObject::cTransientObject%985248929.body
}


cTransientObject::~cTransientObject()
{
  //## begin cTransientObject::~cTransientObject%.body preserve=yes
   __ECL_ATOMIC_DECREMENT__(_ObjectCount);
   return;
  //## end cTransientObject::~cTransientObject%.body
}



//## Other Operations (implementation)
void cTransientObject::AddRef ()
{
  //## begin cTransientObject::AddRef%982663969.body preserve=yes
   bool deleted = __ECL_ATOMIC_GET__(_Deleted);
   if (deleted != 0) {
      ErrorPrintf("::AddRef on deleted object (%d, %s)\n", _Type, _SourceName.c_str());
      exit(42);
      return;
   }
   if (_GarbageCollector != NULL) {
      _GarbageCollector->Clear();
   }
   __ECL_ATOMIC_INCREMENT__(_RefCount);
  //## end cTransientObject::AddRef%982663969.body
}

void cTransientObject::Release ()
{
  //## begin cTransientObject::Release%982663970.body preserve=yes
   bool deleted = __ECL_ATOMIC_GET__(_Deleted);
   if (deleted != 0) {
      ErrorPrintf("::Release on deleted object (%d, %s)\n", _Type, _SourceName.c_str());
      exit(42);
      return;
   }
   LONG_T ref_count = __ECL_ATOMIC_DECREMENT__(_RefCount);
   if (ref_count == 0) {
      __ECL_ATOMIC_SET__(_Deleted,1);
      if (_GarbageCollector != NULL) {
         _GarbageCollector->AddObject(this);
      } else {
         delete this;
      }
   }
  //## end cTransientObject::Release%982663970.body
}

STRING_T cTransientObject::Serialize ()
{
  //## begin cTransientObject::Serialize%1023780985.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cTransientObject::Serialize", "cTransientObject");
  //## end cTransientObject::Serialize%1023780985.body
}

BOOL_T cTransientObject::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cTransientObject::Construct%1023780986.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cTransientObject::Construct", "cTransientObject");
  //## end cTransientObject::Construct%1023780986.body
}

cTransientObject * cTransientObject::Parse (CONST_STRING_T serialized_obj)
{
  //## begin cTransientObject::Parse%1046160463.body preserve=yes
   INT_T object_type = cTransferObject::ObjectType(serialized_obj);
   cTransientObject * obj = NULL;
   if (object_type == OT_EVENT) {
      obj = new cEvent;
   } else if (object_type == OT_ALARM) {
      obj = new cAlarm;
   } else if (object_type == OT_INFO) {
      obj = new cInfo;
   } else if (object_type == OT_STATE) {
      obj = new cState;
   } else if (object_type == OT_DATA_CHANGE) {
      obj = new cDataChange;
   } else if (object_type == OT_REQUEST) {
      obj = new cRequest;
   } else if (object_type == OT_JOB_SPEC) {
      obj = new cJobSpec;
   } else if (object_type == OT_JOB_ENTRY) {
      obj = new cJobEntry;
#ifdef CONSTRUCT_PROXY_OBJECTS
// proxy objects must be constructed by a proxy receiver
// proxy objects are not intended to be transferred
// via standard channels
   } else if (object_type == OT_ORB_PROCESS_PROXY) {
      obj = new cCorbaProcessProxy;
   } else if (object_type == OT_ORB_CELL_PROXY) {
      obj = new cCorbaCellProxy;
   } else if (object_type == OT_COS_EVENTCHANNEL_PROXY) {
      obj = new cCosEventChannelProxy;
#endif
   } else {
      return ConstructObject(serialized_obj);
   }
	if (obj->Construct(serialized_obj)) {
      return obj;
   } else {
		return NULL;
	}
  //## end cTransientObject::Parse%1046160463.body
}

BOOL_T cTransientObject::IsInvalid ()
{
  //## begin cTransientObject::IsInvalid%1047469644.body preserve=yes
	if (_BeginPattern != BEGIN_PATTERN) return true;
	if (_EndPattern != END_PATTERN) return true;
	return false;
  //## end cTransientObject::IsInvalid%1047469644.body
}

cStaticObject * cTransientObject::Source ()
{
  //## begin cTransientObject::Source%1094030185.body preserve=yes
   return _Source;
  //## end cTransientObject::Source%1094030185.body
}

void cTransientObject::SerializeBase (cTransferObject &transfer_obj)
{
  //## begin cTransientObject::SerializeBase%1046095018.body preserve=yes
   transfer_obj.set_Type(_Type);
   transfer_obj.set_SubType(_SubType);
   transfer_obj.AddAttribute(0, _Type, ObjectHeader);
   transfer_obj.AddAttribute(1, _SubType, ObjectHeader);
   transfer_obj.AddAttribute(2, (ULONG_T)_ObjectIdent, ObjectHeader);
   transfer_obj.AddAttribute(3, _TimeStamp, ObjectHeader);
   transfer_obj.AddAttribute(4, _CellName.c_str(), ObjectHeader);
   transfer_obj.AddAttribute(5, _SourceName.c_str(), ObjectHeader);
   transfer_obj.AddAttribute(6, _Key.c_str(), ObjectHeader);
   transfer_obj.AddAttribute(7, _ObjectFlags, ObjectHeader);
   transfer_obj.AddAttribute(8, _EventCode, ObjectHeader);
  //## end cTransientObject::SerializeBase%1046095018.body
}

BOOL_T cTransientObject::ConstructBase (cTransferObject &transfer_obj)
{
  //## begin cTransientObject::ConstructBase%1046095019.body preserve=yes
   transfer_obj.GetAttribute(0, _Type, ObjectHeader);
   transfer_obj.GetAttribute(1, _SubType, ObjectHeader);
   ULONG_T ident = 0;
   transfer_obj.GetAttribute(2, ident, ObjectHeader);
   _ObjectIdent = ident;
   transfer_obj.GetAttribute(3, _TimeStamp, ObjectHeader);
   transfer_obj.GetAttribute(4, _CellName, ObjectHeader);
   transfer_obj.GetAttribute(5, _SourceName, ObjectHeader);
   transfer_obj.GetAttribute(6, _Key, ObjectHeader);
   transfer_obj.GetAttribute(7, _ObjectFlags, ObjectHeader);
   transfer_obj.GetAttribute(8, _EventCode, ObjectHeader);
   return true;
  //## end cTransientObject::ConstructBase%1046095019.body
}

cTransientObject * cTransientObject::ConstructObject (CONST_STRING_T serialized_obj)
{
  //## begin cTransientObject::ConstructObject%1125156840.body preserve=yes
   if (_ConstructObjectFuncAddress == NULL) {
      _ConstructObjectFuncAddress = cCustomFunctions::ConstructObjectFuncAddress();
   }
   if (_ConstructObjectFuncAddress == NULL) {
      return NULL;
   } else {
      cTransientObject * object = _ConstructObjectFuncAddress(serialized_obj);
      return object;
   }
  //## end cTransientObject::ConstructObject%1125156840.body
}

//## Get and Set Operations for Class Attributes (implementation)

ATOMIC_T cTransientObject::get_ObjectCount ()
{
  //## begin cTransientObject::get_ObjectCount%3A9242F001F3.get preserve=no
  return _ObjectCount;
  //## end cTransientObject::get_ObjectCount%3A9242F001F3.get
}

ATOMIC_T cTransientObject::get_ObjectNo ()
{
  //## begin cTransientObject::get_ObjectNo%3A9FEAA100E4.get preserve=no
  return _ObjectNo;
  //## end cTransientObject::get_ObjectNo%3A9FEAA100E4.get
}

ATOMIC_T cTransientObject::get_ObjectIdent () const
{
  //## begin cTransientObject::get_ObjectIdent%3A9FE9F80357.get preserve=no
  return _ObjectIdent;
  //## end cTransientObject::get_ObjectIdent%3A9FE9F80357.get
}

void cTransientObject::set_ObjectIdent (ATOMIC_T value)
{
  //## begin cTransientObject::set_ObjectIdent%3A9FE9F80357.set preserve=no
  _ObjectIdent = value;
  //## end cTransientObject::set_ObjectIdent%3A9FE9F80357.set
}

ULONG_T cTransientObject::get_Type () const
{
  //## begin cTransientObject::get_Type%3A6BFFAC02AB.get preserve=no
  return _Type;
  //## end cTransientObject::get_Type%3A6BFFAC02AB.get
}

void cTransientObject::set_Type (ULONG_T value)
{
  //## begin cTransientObject::set_Type%3A6BFFAC02AB.set preserve=no
  _Type = value;
  //## end cTransientObject::set_Type%3A6BFFAC02AB.set
}

ULONG_T cTransientObject::get_SubType () const
{
  //## begin cTransientObject::get_SubType%3FBF550A000F.get preserve=no
  return _SubType;
  //## end cTransientObject::get_SubType%3FBF550A000F.get
}

void cTransientObject::set_SubType (ULONG_T value)
{
  //## begin cTransientObject::set_SubType%3FBF550A000F.set preserve=no
  _SubType = value;
  //## end cTransientObject::set_SubType%3FBF550A000F.set
}

ULONG_T cTransientObject::get_EventCode () const
{
  //## begin cTransientObject::get_EventCode%3ED39DC901B5.get preserve=no
  return _EventCode;
  //## end cTransientObject::get_EventCode%3ED39DC901B5.get
}

void cTransientObject::set_EventCode (ULONG_T value)
{
  //## begin cTransientObject::set_EventCode%3ED39DC901B5.set preserve=no
  _EventCode = value;
  //## end cTransientObject::set_EventCode%3ED39DC901B5.set
}

cTimeObject cTransientObject::get_TimeStamp () const
{
  //## begin cTransientObject::get_TimeStamp%3AF412B0004B.get preserve=no
  return _TimeStamp;
  //## end cTransientObject::get_TimeStamp%3AF412B0004B.get
}

void cTransientObject::set_TimeStamp (cTimeObject value)
{
  //## begin cTransientObject::set_TimeStamp%3AF412B0004B.set preserve=no
  _TimeStamp = value;
  //## end cTransientObject::set_TimeStamp%3AF412B0004B.set
}

STRING_T cTransientObject::get_CellName () const
{
  //## begin cTransientObject::get_CellName%3BC1E82502B0.get preserve=no
  return _CellName;
  //## end cTransientObject::get_CellName%3BC1E82502B0.get
}

void cTransientObject::set_CellName (STRING_T value)
{
  //## begin cTransientObject::set_CellName%3BC1E82502B0.set preserve=no
  _CellName = value;
  //## end cTransientObject::set_CellName%3BC1E82502B0.set
}

STRING_T cTransientObject::get_SourceName () const
{
  //## begin cTransientObject::get_SourceName%3E5A63C3016F.get preserve=no
  return _SourceName;
  //## end cTransientObject::get_SourceName%3E5A63C3016F.get
}

void cTransientObject::set_SourceName (STRING_T value)
{
  //## begin cTransientObject::set_SourceName%3E5A63C3016F.set preserve=no
  _SourceName = value;
  //## end cTransientObject::set_SourceName%3E5A63C3016F.set
}

ULONG_T cTransientObject::get_ObjectFlags () const
{
  //## begin cTransientObject::get_ObjectFlags%419B0FC001F4.get preserve=no
  return _ObjectFlags;
  //## end cTransientObject::get_ObjectFlags%419B0FC001F4.get
}

void cTransientObject::set_ObjectFlags (ULONG_T value)
{
  //## begin cTransientObject::set_ObjectFlags%419B0FC001F4.set preserve=no
  _ObjectFlags = value;
  //## end cTransientObject::set_ObjectFlags%419B0FC001F4.set
}

STRING_T cTransientObject::get_Key () const
{
  //## begin cTransientObject::get_Key%3E5B7E9102F6.get preserve=no
  return _Key;
  //## end cTransientObject::get_Key%3E5B7E9102F6.get
}

void cTransientObject::set_Key (STRING_T value)
{
  //## begin cTransientObject::set_Key%3E5B7E9102F6.set preserve=no
  _Key = value;
  //## end cTransientObject::set_Key%3E5B7E9102F6.set
}

STRING_T cTransientObject::get_UserName () const
{
  //## begin cTransientObject::get_UserName%41AC6364000F.get preserve=no
  return _UserName;
  //## end cTransientObject::get_UserName%41AC6364000F.get
}

void cTransientObject::set_UserName (STRING_T value)
{
  //## begin cTransientObject::set_UserName%41AC6364000F.set preserve=no
  _UserName = value;
  //## end cTransientObject::set_UserName%41AC6364000F.set
}

ATOMIC_T cTransientObject::get_RefCount () const
{
  //## begin cTransientObject::get_RefCount%3A9242F00243.get preserve=no
  return _RefCount;
  //## end cTransientObject::get_RefCount%3A9242F00243.get
}

// Additional Declarations
  //## begin cTransientObject%3A6BF14C0281.declarations preserve=yes
  //## end cTransientObject%3A6BF14C0281.declarations

//## begin module%3A6BF14C0281.epilog preserve=yes

void cTransientObject::SynchronizationError()
{
   if (_SynchronizationError != NULL) {
      _SynchronizationError(this);
   }
}

cMemPool * cTransientObject::_MemPool = NULL;

cGarbageCollector * cTransientObject::_GarbageCollector = NULL;

SYNCHRONIZATION_ERROR_T cTransientObject::_SynchronizationError = NULL;

void cTransientObject::InitializeObjectManagement(cMemPool * pool)
{
   _MemPool = pool;
}

void cTransientObject::InitializeObjectManagement(cGarbageCollector * collector)
{
   if (_GarbageCollector != NULL) {
      GarbageLock __lock__(&_GarbageCollector->_GarbageMutex);
      cGarbageCollector * old_collector = _GarbageCollector;
      _GarbageCollector = NULL;
      old_collector->Clear();
//      delete old_collector;
   }
   if (collector != NULL) {
      GarbageLock __lock__(&collector->_GarbageMutex);
      _GarbageCollector = collector;
   }
}

bool cTransientObject::CheckObjectManagement(STRING_T & result)
{
   if (_MemPool != NULL) {
      return _MemPool->Check(result);
   }
   return true;
}

void cTransientObject::ClearGarbage()
{
   if (_GarbageCollector != NULL) {
      GarbageLock __lock__(&_GarbageCollector->_GarbageMutex);
      _GarbageCollector->Clear();
   }
}

void cTransientObject::SetSynchronizationError(SYNCHRONIZATION_ERROR_T error_function)
{
   _SynchronizationError = error_function;
}

void * cTransientObject::operator new(size_t size)
{
   if (_MemPool == NULL) {
      return calloc(1, size);
   } else {
      return _MemPool->AllocBlock(size);
   }
}

void cTransientObject::operator delete(void * memory)
{
   if (_MemPool == NULL) {
      free(memory);
   } else {
      _MemPool->FreeBlock(memory);
   }
}

//## end module%3A6BF14C0281.epilog
