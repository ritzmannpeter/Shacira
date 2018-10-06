
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH


/// PR 03.03.08 - added mutex cBitOperatorMutex to protect bit operator access


#include "FirstHeader.h"
#include "System/Objects/cProgress.h"
#include "System/Memory/cPtrList.h"
#include "Control/Cell/cCell.h"
#include "Control/LocalDatabase/cLocalVariable.h"
#include "Control/Device/cDevice.h"
#include "Control/Device/cElementRefs.h"
#include "Control/Device/cCacheControl.h"
#include "Control/Device/cCache.h"
#include "Control/Device/cNullOperator.h"


#define LOCK_BIT_OPERATOR cObjectLock __lock__(&_BitOperatorMutex);
//#define LOCK_BIT_OPERATOR
#define CHECK_LOCK
//#define CHECK_LOCK \
//if (_Locked) { \
//   ErrorPrintf("locked\n"); \
//} \
//_Locked = true;
#define END_LOCK
//#define END_LOCK _Locked = false;


cDevice::cDevice()
      : _Verbose(false), _Simulated(false), _InterfaceMode(false), _TimingProtocol(false), _Buffered(false), _Cached(false), _Verify(false), _Active(false), _Started(false), _Connected(true), _CacheControlId(0), _Cell(NULL), _CacheControl(NULL), _BitOperator(NULL), _Locked(false)
{
   _DeviceControl = NULL;
   _TestMode = false;
   _TestState = 0;
}

cDevice::cDevice (cConfigurationObject *config_obj, cCell *cell)
      : cStaticObject(config_obj), _Verbose(false), _Simulated(false), _InterfaceMode(false), _TimingProtocol(false), _Buffered(false), _Cached(false), _Verify(false), _Active(false), _Started(false), _Connected(true), _CacheControlId(0), _Cell(NULL), _CacheControl(NULL), _BitOperator(NULL), _Locked(false), _DebugLevel(0)
{
_ASSERT_COND(config_obj != NULL)
   _Name = config_obj->get_Name();
   _Verbose = config_obj->PropertyValue("Verbose", _Verbose);
   _Simulated = config_obj->PropertyValue("Simulated", _Simulated);
   _Verify = config_obj->PropertyValue("Verify", _Verify);
   _TimingProtocol = config_obj->PropertyValue("TimingProtocol", _TimingProtocol);
   _DebugLevel  = (ULONG_T)config_obj->PropertyValue("DebugLevel", (ULONG_T)_DebugLevel);
   _BitOperator = new cNullOperator;
   _Cell = cell;
   _DeviceControl = NULL;
   _TestMode = false;
   _TestState = 0;
}


cDevice::~cDevice()
{
   DELETE_OBJECT(cBitOperator, _BitOperator)
   if (_DeviceControl != NULL) {
      _DeviceControl->Stop();
   }
}

void cDevice::Start ()
{
   if (_DeviceControl != NULL) {
      _DeviceControl->Start();
   }
}

void cDevice::Stop ()
{
   if (_DeviceControl != NULL) {
      _DeviceControl->Stop();
   }
}

void cDevice::Kill(bool wait)
{
    if (_DeviceControl != NULL) {
        _DeviceControl->kill(wait);
    }
}

void cDevice::Cache (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
}

void cDevice::Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
}

void cDevice::Buffer (MAP_ITEM_T * map_item)
{
   Buffer(map_item->buf_spec, map_item->address, map_item->size);
}

void cDevice::Buffer (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size)
{
}

void cDevice::Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size)
{
}

void cDevice::Read (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Write (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Process()
{
}

void cDevice::Control()
{
}

BOOL_T cDevice::GetBit (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T pos)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::SetBit (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T pos, BOOL_T state)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T &value, ULONG_T flags)
{
   Read(buf_spec, address, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, USHORT_T &value, ULONG_T flags)
{
   Read(buf_spec, address, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T &value, ULONG_T flags)
{
   Read(buf_spec, address, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, FLOAT_T &value, ULONG_T flags)
{
   Read(buf_spec, address, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T &value, ULONG_T flags)
{
   Read(buf_spec, address, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, STRING_T &value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Get (CONST_STRING_T buf_spec, ULONG_T address, WSTRING_T &value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T value, ULONG_T flags)
{
   Write(buf_spec, address, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, USHORT_T value, ULONG_T flags)
{
   Write(buf_spec, address, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T value, ULONG_T flags)
{
   Write(buf_spec, address, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, FLOAT_T value, ULONG_T flags)
{
   Write(buf_spec, address, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T value, ULONG_T flags)
{
   Write(buf_spec, address, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, CONST_STRING_T value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Set (CONST_STRING_T buf_spec, ULONG_T address, CONST_WSTRING_T value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags)
{
   Read(buf_spec, name, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T &value, ULONG_T flags)
{
   Read(buf_spec, name, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags)
{
   Read(buf_spec, name, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T &value, ULONG_T flags)
{
   Read(buf_spec, name, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags)
{
   Read(buf_spec, name, sizeof(value), &value, sizeof(value), flags);
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, WSTRING_T &value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags)
{
   Write(buf_spec, name, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T value, ULONG_T flags)
{
   Write(buf_spec, name, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags)
{
   Write(buf_spec, name, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T value, ULONG_T flags)
{
   Write(buf_spec, name, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags)
{
   Write(buf_spec, name, sizeof(value), &value, flags);
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_WSTRING_T value, ULONG_T flags)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cDevice::SetMemoryInfo (CONST_STRING_T buf_spec, UCHAR_T granularity, ULONG_T command, ULONG_T ident, cCache *cache, cCache *buffer)
{
   MEMORY_INFO * info = MemoryInfo(buf_spec);
   if (info == NULL) {
      info = (MEMORY_INFO*)cSystemUtils::Alloc(sizeof(*info));
      info->granularity = granularity;
      info->command = command;
      info->ident = ident;
      info->cache = cache;
      info->buffer = buffer;
      _InfoMap[buf_spec] = info;
   } else {
      info->granularity = granularity;
      info->command = command;
      info->ident = ident;
      info->cache = cache;
      info->buffer = buffer;
   }
}

MEMORY_INFO * cDevice::MemoryInfo (CONST_STRING_T buf_spec)
{
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.find(buf_spec);
   if (i == _InfoMap.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

cCache * cDevice::SelectCache (CONST_STRING_T buf_spec)
{
   MEMORY_INFO * info = MemoryInfo(buf_spec);
   if (info == NULL) {
      return NULL;
   } else {
      return info->cache;
   }
}

cCache * cDevice::SelectBuffer (CONST_STRING_T buf_spec)
{
   MEMORY_INFO * info = MemoryInfo(buf_spec);
   if (info == NULL) {
      return NULL;
   } else {
      return info->buffer;
   }
}

void cDevice::Changed (CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags)
{
   cPtrList * element_refs = GetVariables(buf_spec, address);
   if (element_refs != NULL) {
      Changed(element_refs, flags);
   }
}

void cDevice::Changed (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T flags)
{
   cPtrList * element_refs = GetVariables(buf_spec, name);
   if (element_refs != NULL) {
      Changed(element_refs, flags);
   }
}

void cDevice::Changed (cPtrList * element_refs, ULONG_T flags)
{
   cLocalVariable * variable = NULL;
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   cPtrList::cConstIterator i = element_refs->Begin();
   if (i.First()) {
      do {
         ELEMENT_REF_T * element_ref = (ELEMENT_REF_T*)i.Ptr();
         if (element_ref != NULL) {
            variable = element_ref->variable;
            i1 = element_ref->i1;
            i2 = element_ref->i2;
            i3 = element_ref->i3;
            i4 = element_ref->i4;
            try {
               variable->Save(i1, i2, i3, i4, flags);
            } catch (cError & e) {
               ErrorPrintf("%s saving variable value %s[%d][%d][%d][%d]\n",
                           (const char *)e,
                           variable->VarName().c_str(),
                           i1, i2, i3, i4);
            } catch (...) {
               ErrorPrintf("unhandled exception saving variable value %s[%d][%d][%d][%d]\n",
                           variable->VarName().c_str(),
                           i1, i2, i3, i4);
            }
         } else {
_ASSERT_UNCOND
         }
      } while (i.Next());
   }
}

void cDevice::SetVariable (MAP_ITEM_T *map_item, cLocalVariable *variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   CONST_STRING_T buf_spec = map_item->buf_spec;
   cElementRefs * element_refs = GetRefs(buf_spec);
   if (element_refs == NULL) {
      element_refs = new cElementRefs;
      _ElementRefs[buf_spec] = element_refs;
   }
   SetAddresses(buf_spec, element_refs, map_item, variable, i1, i2, i3, i4);
}

cPtrList * cDevice::GetVariables (CONST_STRING_T buf_spec, ULONG_T address)
{
   cElementRefs * element_refs = GetRefs(buf_spec);
   if (element_refs != NULL) {
      return element_refs->GetRefs(address);
   } else {
      return NULL;
   }
}

cPtrList * cDevice::GetVariables (CONST_STRING_T buf_spec, CONST_STRING_T name)
{
   cElementRefs * element_refs = GetRefs(buf_spec);
   if (element_refs != NULL) {
      return element_refs->GetRefs(name);
   } else {
      return NULL;
   }
}

cElementRefs * cDevice::GetRefs (CONST_STRING_T buf_spec)
{
   std::map<STRING_T,cElementRefs*>::const_iterator i = _ElementRefs.find(buf_spec);
   if (i == _ElementRefs.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, UCHAR_T &value)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   value = *_BitOperator;
END_LOCK
}

void cDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, USHORT_T &value)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   value = *_BitOperator;
END_LOCK
}

void cDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   value = *_BitOperator;
END_LOCK
}

void cDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, FLOAT_T &value)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   value = *_BitOperator;
END_LOCK
}

void cDevice::Cast (CONST_STRING_T buf_spec, UCHAR_T data_type, DOUBLE_T &value)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   value = *_BitOperator;
END_LOCK
}

ULONG_T cDevice::GetPattern (CONST_STRING_T buf_spec, UCHAR_T data_type, UCHAR_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T flags)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   if (start_pos == end_pos) {
      return _BitOperator->GetBit(start_pos, buf_spec);
   } else {
      return _BitOperator->GetPattern(start_pos, (end_pos - start_pos) + 1, buf_spec);
   }
END_LOCK
}

ULONG_T cDevice::GetPattern (CONST_STRING_T buf_spec, UCHAR_T data_type, USHORT_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T flags)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   if (start_pos == end_pos) {
      return _BitOperator->GetBit(start_pos, buf_spec);
   } else {
      return _BitOperator->GetPattern(start_pos, (end_pos - start_pos) + 1, buf_spec);
   }
END_LOCK
}

ULONG_T cDevice::GetPattern (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T flags)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   if (start_pos == end_pos) {
      return _BitOperator->GetBit(start_pos, buf_spec);
   } else {
      return _BitOperator->GetPattern(start_pos, (end_pos - start_pos) + 1, buf_spec);
   }
END_LOCK
}

void cDevice::SetPattern (CONST_STRING_T buf_spec, UCHAR_T data_type, UCHAR_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T pattern, ULONG_T flags)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   if (start_pos == end_pos) {
      if (pattern == 0) {
         _BitOperator->ResetBit(start_pos, buf_spec);
      } else {
         _BitOperator->SetBit(start_pos, buf_spec);
      }
   } else {
      _BitOperator->SetPattern(pattern, start_pos, (end_pos - start_pos) + 1, buf_spec);
   }
   value = *_BitOperator;
END_LOCK
}

void cDevice::SetPattern (CONST_STRING_T buf_spec, UCHAR_T data_type, USHORT_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T pattern, ULONG_T flags)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   if (start_pos == end_pos) {
      if (pattern == 0) {
         _BitOperator->ResetBit(start_pos, buf_spec);
      } else {
         _BitOperator->SetBit(start_pos, buf_spec);
      }
   } else {
      _BitOperator->SetPattern(pattern, start_pos, (end_pos - start_pos) + 1, buf_spec);
   }
   value = *_BitOperator;
END_LOCK
}

void cDevice::SetPattern (CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T pattern, ULONG_T flags)
{
LOCK_BIT_OPERATOR
   _BitOperator->SetValue(data_type, value);
CHECK_LOCK
   if (start_pos == end_pos) {
      if (pattern == 0) {
         _BitOperator->ResetBit(start_pos, buf_spec);
      } else {
         _BitOperator->SetBit(start_pos, buf_spec);
      }
   } else {
      _BitOperator->SetPattern(pattern, start_pos, (end_pos - start_pos) + 1, buf_spec);
   }
   value = *_BitOperator;
END_LOCK
}

void cDevice::SetAddresses (CONST_STRING_T buf_spec, cElementRefs *element_refs, MAP_ITEM_T *map_item, cLocalVariable *variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   MEMORY_INFO * info = MemoryInfo (buf_spec);
   ULONG_T map_element_size =
      (info == NULL) ?
      map_item->size : map_item->size / info->granularity;;
   ULONG_T address = map_item->address;
   UCHAR_T map_data_type = map_item->data_type;
   UCHAR_T bit_pos_b = map_item->bit_pos_b;
   UCHAR_T bit_pos_e = map_item->bit_pos_b;
   if (map_item->name == NULL) {
      // PR 31.01.05 ignore unused addresses
      if (address != UNUSED_ADDRESS) {
         if (bit_pos_b != UNUSED_BITPOS) {
LOCK_BIT_OPERATOR
            UCHAR_T byte_pos = _BitOperator->BytePos(map_data_type, bit_pos_b);
CHECK_LOCK
            element_refs->AddRef(address + byte_pos, variable, i1, i2, i3, i4);
END_LOCK
         } else {
            for (ULONG_T i=0; i<map_element_size; i++) {
               element_refs->AddRef(address + i, variable, i1, i2, i3, i4);
            }
         }
      }
   } else {
      element_refs->AddRef(map_item->name, variable, i1, i2, i3, i4);
   }
}

void cDevice::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.cbegin();
   while (i != _InfoMap.cend()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
         cache->Save(refresh_type, refresh_value);
      }
      i++;
   }
}

void cDevice::Download ()
{
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.cbegin();
   while (i != _InfoMap.cend()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
         cache->Download();
      }
      i++;
   }
}

void cDevice::Upload ()
{
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.cbegin();
   while (i != _InfoMap.cend()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
         cache->Upload();
      }
      i++;
   }
}

void cDevice::SetProgress (ULONG_T indicator, ULONG_T value)
{
   if (_Cell != NULL) {
      _Cell->SetProgress(indicator, value);
   }
}

BOOL_T cDevice::MappingValid (CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type)
{
   return true;
}

BOOL_T cDevice::MappingValid (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type)
{
   return true;
}

cMutexSem * cDevice::DeviceMutex ()
{
   return &_DeviceMutex;
}

void * cDevice::GetObject(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags)
{
   return NULL;
}

void * cDevice::GetObject(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T flags)
{
   return NULL;
}

void cDevice::OptimizeBuffers()
{
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.cbegin();
   while (i != _InfoMap.cend()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
         cache->OptimizeBuffers();
      }
      i++;
   }
}

void cDevice::OptimizeCaches()
{
   MEMORY_INFO_MAP_T::const_iterator i = _InfoMap.cbegin();
   while (i != _InfoMap.cend()) {
      MEMORY_INFO * info = (*i).second;
      cCache * cache = info->cache;
      if (cache != NULL) {
         cache->OptimizeCaches();
      }
      i++;
   }
}

DOUBLE_T cDevice::GetParameter(CONST_STRING_T parameter_id) const
{
   return 0;
}

STRING_T cDevice::GetParameterString(CONST_STRING_T parameter_id) const
{
   return STRING_T();
}

void cDevice::SetParameter(CONST_STRING_T parameter_id, DOUBLE_T value)
{
}

void cDevice::SetParameterString(CONST_STRING_T parameter_id, const STRING_T & value)
{
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cDevice::get_Verbose () const
{
  return _Verbose;
}

void cDevice::set_Verbose (BOOL_T value)
{
  _Verbose = value;
}

BOOL_T cDevice::get_Simulated () const
{
  return _Simulated;
}

void cDevice::set_Simulated (BOOL_T value)
{
  _Simulated = value;
}

BOOL_T cDevice::get_InterfaceMode () const
{
  return _InterfaceMode;
}

void cDevice::set_InterfaceMode (BOOL_T value)
{
  _InterfaceMode = value;
}

BOOL_T cDevice::get_Buffered () const
{
  return _Buffered;
}

void cDevice::set_Buffered (BOOL_T value)
{
  _Buffered = value;
}

BOOL_T cDevice::get_Cached () const
{
  return _Cached;
}

void cDevice::set_Cached (BOOL_T value)
{
  _Cached = value;
}

BOOL_T cDevice::get_Verify () const
{
  return _Verify;
}

void cDevice::set_Verify (BOOL_T value)
{
  _Verify = value;
}

ULONG_T cDevice::get_DebugLevel() const
{
   return _DebugLevel;
}
