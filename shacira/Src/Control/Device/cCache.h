//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH

#ifndef cCache_h
#define cCache_h 1

#include "System/Objects/cObjectLock.h"
#include "System/Objects/cProgress.h"
#include "System/Objects/cStaticObject.h"
#include "System/Memory/cMemoryPtr.h"
#include "System/Database/cMapping.h"

class __DLL_EXPORT__ cDevice;

#define MAX_ADDRESS_AREA            0x8000
#define MAP_SIZE(elements)          ((elements) / 0x08)
#define ELEMENT_ADDR(address)       ((address) / 0x08)
#define MAP_POS(address)            ((address) % 0x08)
#define IS_SET(map, address)        (map[ELEMENT_ADDR(address)] >>((MAP_POS(address))) & 0x0001)
#define SET_MAP(map, address)        map[ELEMENT_ADDR(address)] |=(0x0001 << MAP_POS(address))

#define IS_NAME_MAPPED(block)(block->name != NULL)
#define IS_ADDRESS_MAPPED(block)(block->address != UNUSED_ADDRESS)
typedef struct transfer_control_block {
   void * memory;
   void * device;
   MAP_ITEM_T * map_item;
   CONST_STRING_T name;
   UCHAR_T refresh_type;
   ULONG_T refresh_value;
   ULONG_T address;
   ULONG_T size;
   ULONG_T elements;
}  TRANSFER_CONTROL_BLOCK;

class __DLL_EXPORT__ cCache : public cStaticObject
{
public:
   cCache(cDevice *device, CONST_STRING_T name);
   virtual ~cCache();
   virtual void Cache(LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Cache(CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Buffer(LONG_T address, ULONG_T size);
   virtual void Buffer(MAP_ITEM_T * map_item);
   virtual void Buffer(CONST_STRING_T name, ULONG_T size);
   virtual BOOL_T SetCached(LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual BOOL_T SetCached(CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual BOOL_T SetBuffered(MAP_ITEM_T * map_item);
   virtual BOOL_T SetBuffered(LONG_T address, ULONG_T size);
   virtual BOOL_T SetBuffered(CONST_STRING_T name, ULONG_T size);
   virtual void Done();
   virtual BOOL_T Cached(LONG_T address, ULONG_T elements = 1);
   virtual BOOL_T Cached(CONST_STRING_T name, ULONG_T elements = 1);
   virtual BOOL_T Buffered(LONG_T address, ULONG_T elements = 1);
   virtual BOOL_T Buffered(CONST_STRING_T name, ULONG_T elements = 1);
   virtual void Read(LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size);
   virtual void Read(CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size);
   virtual void Read(CONST_STRING_T name, STRING_T &value);
   virtual void Write(LONG_T address, ULONG_T elements, void *buf);
   virtual void Write(CONST_STRING_T name, ULONG_T elements, void *buf);
   virtual void Write(CONST_STRING_T name, CONST_STRING_T value);
   virtual void Get(CHAR_T &value);
   virtual void Get(UCHAR_T &value);
   virtual void Get(SHORT_T &value);
   virtual void Get(USHORT_T &value);
   virtual void Get(LONG_T &value);
   virtual void Get(ULONG_T &value);
   virtual void Get(FLOAT_T &value);
   virtual void Get(DOUBLE_T &value);
   virtual void Get(STRING_T &value);
   virtual void Get(WSTRING_T &value);
   virtual void Get(BUF_T &value);
   virtual void Get(BUF_T buf, ULONG_T len, ULONG_T buf_size);
   virtual void Set(CHAR_T value);
   virtual void Set(UCHAR_T value);
   virtual void Set(SHORT_T value);
   virtual void Set(USHORT_T value);
   virtual void Set(LONG_T value);
   virtual void Set(ULONG_T value);
   virtual void Set(FLOAT_T value);
   virtual void Set(DOUBLE_T value);
   virtual void Set(CONST_STRING_T value);
   virtual void Set(CONST_WSTRING_T value);
   virtual void Set(CONST_BUF_T buf, ULONG_T len);
   virtual void Save(ULONG_T elapsed);
   virtual void Save(UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Load();
   virtual void Upload();
   virtual void Download();
   virtual void OptimizeBuffers();
   virtual void OptimizeCaches();
   virtual ULONG_T MinIdleTime();
   virtual void Reset();
   STRING_T get_CacheName() const;
   void set_CacheName(STRING_T value);
   cMutexSem _CacheMutex;
protected:
   TRANSFER_CONTROL_BLOCK * AllocTransferBlock(cDevice * device, void * memory, ULONG_T address, ULONG_T elements);
   TRANSFER_CONTROL_BLOCK * AllocTransferBlock(cDevice * device, void * memory, CONST_STRING_T name, ULONG_T elements);
protected:
   STRING_T _CacheName;
   UCHAR_T *_CachedByAddress;
   UCHAR_T *_BufferedByAddress;
   STRING_MAP_T _CachedByName;
   STRING_MAP_T _BufferedByName;
   PTR_T _Buf;
   ULONG_T _BufSize;
   cDevice *_Device;
};

#endif
