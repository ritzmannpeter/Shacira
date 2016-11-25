//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH

#ifndef cBlockCache_h
#define cBlockCache_h 1

#define USE_DYNAMIC_BLOCK_OPTIMIZATION

#include "System/Database/cMapping.h"
#include "Control/Device/cDevice.h"
#include "Control/Device/cCache.h"

#define DEFAULT_ELEMENT_SIZE        2
#define DEFAULT_ELEMENT_COUNT       0x10000

typedef std::map<ULONG_T, TRANSFER_CONTROL_BLOCK *> BLOCK_MAP_T;

class cBlockBuffer
{
public:
   UCHAR_T _RefreshType;
   ULONG_T _RefreshValue;
   BLOCK_MAP_T _BlockMap;
public:
   cBlockBuffer(UCHAR_T refresh_type, ULONG_T refresh_value);
   BLOCK_MAP_T & BlockMap();
   BOOL_T Expired(ULONG_T elapsed);
private:
   LONG_T _Expired;
   ULONG_T _LastAccess;
};

typedef std::map<ULONG_T, cBlockBuffer*> BLOCK_BUFFER_MAP_T;

class __DLL_EXPORT__ cBlockCache : public cCache
{
public:
   static BOOL_T _DynamicBlockOptimization;
   cBlockCache();
   cBlockCache(const cBlockCache &right);
   cBlockCache(cDevice *device, CONST_STRING_T name, UCHAR_T element_size = DEFAULT_ELEMENT_SIZE, ULONG_T elements = DEFAULT_ELEMENT_COUNT);
   virtual ~cBlockCache();
   virtual BOOL_T SetCached(LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual BOOL_T SetCached(CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual BOOL_T SetBuffered(MAP_ITEM_T * map_item);
   virtual BOOL_T SetBuffered(LONG_T address, ULONG_T size);
   virtual BOOL_T SetBuffered(CONST_STRING_T name, ULONG_T size);
   virtual void Done();
   virtual void Read(LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size);
   virtual void Read(CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size);
   virtual void Read(CONST_STRING_T name, STRING_T &value);
   virtual void Write(LONG_T address, ULONG_T elements, void *buf);
   virtual void Write(CONST_STRING_T name, ULONG_T elements, void *buf);
   virtual void Write(CONST_STRING_T name, CONST_STRING_T value);
   virtual void Save(ULONG_T elapsed);
   virtual void Save(UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Load();
   virtual void Upload();
   virtual void Download();
   virtual void OptimizeBuffers();
   virtual ULONG_T MinIdleTime();
   UCHAR_T get_ElementSize() const;
   ULONG_T get_Elements() const;
   UCHAR_T * get_Memory() const;
protected:
   void AddBlock(BLOCK_MAP_T &blocks, TRANSFER_CONTROL_BLOCK *block);
   void Optimize(BLOCK_MAP_T &blocks);
   BOOL_T Optimize(BLOCK_MAP_T &blocks, TRANSFER_CONTROL_BLOCK *block);
   BLOCK_MAP_T OptimizedBlocks(const BLOCK_MAP_T & blocks);
   BLOCK_MAP_T BlockMapCopy(const BLOCK_MAP_T & source);
   void ClearBlockMap(BLOCK_MAP_T & block_map);
   BOOL_T BlockMapsAreEqual(const BLOCK_MAP_T & left, const BLOCK_MAP_T & right) const;
   void MarkAsCached(BLOCK_MAP_T &blocks);
   void MarkAsBuffered(BLOCK_MAP_T &blocks);

   UCHAR_T _ElementSize;
   ULONG_T _Elements;
   UCHAR_T *_Memory;
   ULONG_T _MemorySize;
   BLOCK_MAP_T _BufferedBlocks;
   BLOCK_MAP_T _OptimizedBufferedBlocks;
   BLOCK_BUFFER_MAP_T _BlockBuffers;
private:
   void Save(BLOCK_MAP_T &block_map, BOOL_T change_events = true);
   void Load(BLOCK_MAP_T &block_map);
   BLOCK_MAP_T & GetBlocks(UCHAR_T refresh_type, ULONG_T refresh_value);
   cBlockBuffer * GetBlockBuffer(UCHAR_T refresh_type, ULONG_T refresh_value);
   cMutexSem _OptimizationMutex;
};

#endif
