//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
#include "FirstHeader.h"
#include "Control/Device/cCache.h"
#include "Control/Device/cDevice.h"

cCache::cCache (cDevice *device, CONST_STRING_T name)
      : _CachedByAddress(NULL), _BufferedByAddress(NULL), _Buf(NULL), _BufSize(0x4000), _Device(NULL)
{
   _Device = device;
   _CacheName = name;
   _Name = device->get_Name();
   _Name += ".";
   _Name += name;
   _CachedByAddress = (UCHAR_T*)cSystemUtils::Alloc(MAX_ADDRESS_AREA);
   _BufferedByAddress = (UCHAR_T*)cSystemUtils::Alloc(MAX_ADDRESS_AREA);
   _Buf = cSystemUtils::Alloc(_BufSize);
}


cCache::~cCache()
{
   if (_Buf != NULL) {
      cSystemUtils::Free(_Buf);
   }
   if (_CachedByAddress != NULL) {
      cSystemUtils::Free(_CachedByAddress);
   }
   if (_BufferedByAddress != NULL) {
      cSystemUtils::Free(_BufferedByAddress);
   }
}

void cCache::Cache (LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   if (SetCached(address, size, refresh_type, refresh_value)) {
      SET_MAP(_CachedByAddress, address);
   }
}

void cCache::Cache (CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   if (SetCached(name, size, refresh_type, refresh_value)) {
      _CachedByName[name] = name;
   }
}

void cCache::Buffer (LONG_T address, ULONG_T size)
{
   if (SetBuffered(address, size)) {
      SET_MAP(_BufferedByAddress, address);
   }
}

void cCache::Buffer (MAP_ITEM_T * map_item)
{
   if (SetBuffered(map_item)) {
      SET_MAP(_BufferedByAddress, map_item->address);
   }
}

void cCache::Buffer (CONST_STRING_T name, ULONG_T size)
{
   if (SetBuffered(name, size)) {
      _BufferedByName[name] = name;
   }
}

BOOL_T cCache::SetCached (LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

BOOL_T cCache::SetCached (CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

BOOL_T cCache::SetBuffered (MAP_ITEM_T * map_item)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

BOOL_T cCache::SetBuffered (LONG_T address, ULONG_T size)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

BOOL_T cCache::SetBuffered (CONST_STRING_T name, ULONG_T size)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Done ()
{
}

BOOL_T cCache::Cached (LONG_T address, ULONG_T elements)
{
   return IS_SET(_CachedByAddress, address);
}

BOOL_T cCache::Cached (CONST_STRING_T name, ULONG_T elements)
{
   STRING_MAP_T::const_iterator i = _CachedByName.find(name);
   if (i == _CachedByName.cend()) {
      return false;
   } else {
      return true;
   }
}

BOOL_T cCache::Buffered (LONG_T address, ULONG_T elements)
{
   return IS_SET(_BufferedByAddress, address);
}

BOOL_T cCache::Buffered (CONST_STRING_T name, ULONG_T elements)
{
   STRING_MAP_T::const_iterator i = _BufferedByName.find(name);
   if (i == _BufferedByName.cend()) {
      return false;
   } else {
      return true;
   }
}

void cCache::Read (LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Read (CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Read (CONST_STRING_T name, STRING_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Write (LONG_T address, ULONG_T elements, void *buf)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Write (CONST_STRING_T name, ULONG_T elements, void *buf)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Write (CONST_STRING_T name, CONST_STRING_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (CHAR_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (UCHAR_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (SHORT_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (USHORT_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (LONG_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (ULONG_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (FLOAT_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (DOUBLE_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (STRING_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (WSTRING_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (BUF_T &value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Get (BUF_T buf, ULONG_T len, ULONG_T buf_size)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (CHAR_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (UCHAR_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (SHORT_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (USHORT_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (LONG_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (ULONG_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (FLOAT_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (DOUBLE_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (CONST_STRING_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (CONST_WSTRING_T value)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Set (CONST_BUF_T buf, ULONG_T len)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Save (ULONG_T elapsed)
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
}

void cCache::Load ()
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Upload ()
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::Download ()
{
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
}

void cCache::OptimizeBuffers()
{
}

void cCache::OptimizeCaches()
{
}

ULONG_T cCache::MinIdleTime ()
{
   return 1000;
}

void cCache::Reset()
{
}

STRING_T cCache::get_CacheName () const
{
   return _CacheName;
}

void cCache::set_CacheName (STRING_T value)
{
   _CacheName = value;
}

TRANSFER_CONTROL_BLOCK * cCache::AllocTransferBlock(cDevice * device, void *memory, CONST_STRING_T name, ULONG_T elements)
{
   TRANSFER_CONTROL_BLOCK * block = (TRANSFER_CONTROL_BLOCK*)cSystemUtils::Alloc(sizeof(TRANSFER_CONTROL_BLOCK));
   block->device = device;
   block->memory = memory;
   block->elements = elements;
   block->name = name;
   block->address = UNUSED_ADDRESS;
   block->map_item = NULL;
   return block;
}

TRANSFER_CONTROL_BLOCK * cCache::AllocTransferBlock(cDevice * device, void * memory, ULONG_T address, ULONG_T elements)
{
   TRANSFER_CONTROL_BLOCK * block = (TRANSFER_CONTROL_BLOCK*)cSystemUtils::Alloc(sizeof(TRANSFER_CONTROL_BLOCK));
   block->device = device;
   block->memory = memory;
   block->elements = elements;
   block->name = NULL;
   block->address = address;
   block->map_item = NULL;
   return block;
}

