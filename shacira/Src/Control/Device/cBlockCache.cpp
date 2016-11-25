//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH

/// PR 27.04.06 - introduced switchable exception on cache misses (PF_CACHE_EXCEPTION)
///             - introduced change maps to control data changes
/// HA 05.05.06 - fixed problem with change map (macro CHANGED and changed size from 0x200 -> 0x300)
/// PR 22.05.06 - introduced constant MAX_BLOCK_BUFFER_LEN and set it to 0x400
/// PR 16.01.07 - removed bug in block optimization:
///                   in case of full overlap block memory ptr not adjusted
/// PR 26.10.08 - approached precise cache timing
/// PR 29.04.09 - extended default size of cache and added checking of memory ranges
/// PR 07.03.14 - added dynamic block optimization

#include "FirstHeader.h"
#include "Control/Device/cBlockCache.h"

// macros for cache map management

#define LEFT_TOUCH      1
#define RIGHT_TOUCH     2
#define LEFT_OVERLAP    3
#define RIGHT_OVERLAP   4
#define FULL_OVERLAP    5
#define INCLUDE         6
#define LEFT_DISTINCT   7
#define RIGHT_DISTINCT  8

static UCHAR_T Relation(ULONG_T address1, ULONG_T right1, ULONG_T address2, ULONG_T right2)
{
   if (right1 + 1< address2) {
      return LEFT_DISTINCT;
   }
   if (right2 + 1 < address1) {
      return RIGHT_DISTINCT;
   }
   if (right1 + 1 == address2) {
      return LEFT_TOUCH;
   }
   if (right2 + 1 == address1) {
      return RIGHT_TOUCH;
   }
   if (address1 >= address2) {
      if (right1 > right2) {
         return RIGHT_OVERLAP;
      } else {
         return INCLUDE;
      }
   } else {
      if (right1 > right2) {
         return FULL_OVERLAP;
      } else {
         return LEFT_OVERLAP;
      }
   }
   return 0;
}

#define MEMORY_ADDRESS(size,address)   (size * address)
#define MEMORY_SIZE(size,elements)     (size * elements)

cBlockBuffer::cBlockBuffer(UCHAR_T refresh_type, ULONG_T refresh_value)
{   
   _RefreshType = refresh_type;
   _RefreshValue = refresh_value;
   _Expired = refresh_value;
   _LastAccess = cSystemUtils::RealtimeOffset();
}

BLOCK_MAP_T & cBlockBuffer::BlockMap()
{
   return _BlockMap;
}

BOOL_T cBlockBuffer::Expired(ULONG_T elapsed)
{
#define FORCE_EXACT_CACHE_TIMING
#ifdef FORCE_EXACT_CACHE_TIMING
   int t = cSystemUtils::RealtimeOffset();
   if ((int)(t - _LastAccess) >= _RefreshValue) {
//      DCPrintf("save check: refresh %d, diff time %d\n", _RefreshValue, t - _LastAccess); 
      _LastAccess = t;
      return true;
   } else {
      return false;
   }
#else
   _Expired -= elapsed;
   if (_Expired <= 0) {
      int t = cSystemUtils::RealtimeOffset();
      _Expired = _RefreshValue;
//      DCPrintf("save check: refresh %d, diff time %d\n", _RefreshValue, t - _LastAccess); 
      _LastAccess = t;
      return true;
   } else {
      return false;
   }
#endif
}

#define BLOCK_ID(rt,rv) ((rt << 24) | rv)

#define MAX_BLOCK_BUFFER_LEN  0x400
#define SET_CHANGED(m, pos)   m[pos/8] |= (1<<(pos%8));
#define CHANGED(m, pos)       (m[pos/8] & (1<<(pos%8)))  // HA 05052006

BOOL_T cBlockCache::_DynamicBlockOptimization = true;
//BOOL_T cBlockCache::_DynamicBlockOptimization = false;

cBlockCache::cBlockCache (cDevice *device, CONST_STRING_T name, UCHAR_T element_size, ULONG_T elements)
      : _ElementSize(2)
  , cCache(device, name)
{
   _ElementSize = element_size;
   _Elements = elements;
   _MemorySize = _Elements * _ElementSize;
   _Memory = (UCHAR_T*)cSystemUtils::Alloc(_MemorySize);
}

cBlockCache::~cBlockCache()
{
   if (_Memory != NULL) {
      cSystemUtils::Free(_Memory);
   }
}

BOOL_T cBlockCache::SetCached (LONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   void * memory = &(_Memory[MEMORY_ADDRESS(_ElementSize, address)]);
   ULONG_T elements_used = size / _ElementSize;
   TRANSFER_CONTROL_BLOCK * block = AllocTransferBlock(_Device, memory, address, elements_used);
   block->refresh_type = refresh_type;
   block->refresh_value = refresh_value;
   BLOCK_MAP_T & blocks = GetBlocks(refresh_type, refresh_value);
   AddBlock(blocks, block);
   return true;
}

BOOL_T cBlockCache::SetCached (CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "BOOL_T cBlockCache::SetCached (CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)");
}

BOOL_T cBlockCache::SetBuffered (MAP_ITEM_T * map_item)
{
   void * memory = &(_Memory[MEMORY_ADDRESS(_ElementSize, map_item->address)]);
   ULONG_T elements_used = map_item->size / _ElementSize;
   TRANSFER_CONTROL_BLOCK * block = AllocTransferBlock(_Device, memory, map_item->address, elements_used);
   block->map_item = map_item;
   AddBlock(_BufferedBlocks, block);
   return true;
}

BOOL_T cBlockCache::SetBuffered (LONG_T address, ULONG_T size)
{
   void * memory = &(_Memory[MEMORY_ADDRESS(_ElementSize, address)]);
   ULONG_T elements_used = size / _ElementSize;
   TRANSFER_CONTROL_BLOCK * block = AllocTransferBlock(_Device, memory, address, elements_used);
   AddBlock(_BufferedBlocks, block);
   return true;
}

BOOL_T cBlockCache::SetBuffered (CONST_STRING_T name, ULONG_T size)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "BOOL_T cBlockCache::SetBuffered (CONST_STRING_T name, ULONG_T size)");
}

void cBlockCache::Done ()
{
   if (_DynamicBlockOptimization) {
      OptimizeBuffers();
   } else {
      Optimize(_BufferedBlocks);
      MarkAsBuffered(_BufferedBlocks);
   }
   BLOCK_BUFFER_MAP_T::const_iterator i = _BlockBuffers.begin();
   while (i != _BlockBuffers.end()) {
      cBlockBuffer * buffer = (*i).second;
      BLOCK_MAP_T & blocks = buffer->BlockMap();
      Optimize(blocks);
      MarkAsCached(blocks);
      i++;
   }
}

void cBlockCache::Read (LONG_T address, ULONG_T elements, void *buf, ULONG_T buf_size)
{
   ULONG_T pos = MEMORY_ADDRESS(_ElementSize, address);
   ULONG_T size = MEMORY_SIZE(_ElementSize, elements);
   if (pos > _MemorySize ||
       pos + size > _MemorySize) {
      ErrorPrintf("invalid block cache access on cache %s address %08.08x size %d\n",
                  _Name.c_str(), address, size);
      return;
   }
   if (cResources::FlagSet(PF_CACHE_EXCEPTION)) {
      if (!Cached(address, elements)) {
         throw cError(CACHE_READ_UNCACHED, 0,
                      _CacheName.c_str(),
                      cConvUtils::StringValue(address).c_str());
      }
   }
   memcpy(buf, (void*)&(_Memory[MEMORY_ADDRESS(_ElementSize, address)]), MEMORY_SIZE(_ElementSize, elements));
}

void cBlockCache::Read (CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cBlockCache::Read (CONST_STRING_T name, ULONG_T elements, void *buf, ULONG_T buf_size)");
}

void cBlockCache::Read (CONST_STRING_T name, STRING_T &value)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cBlockCache::Read (CONST_STRING_T name, STRING_T &value)");
}

void cBlockCache::Write (LONG_T address, ULONG_T elements, void *buf)
{
   ULONG_T pos = MEMORY_ADDRESS(_ElementSize, address);
   ULONG_T size = MEMORY_SIZE(_ElementSize, elements);
   if (pos > _MemorySize ||
       pos + size > _MemorySize) {
      ErrorPrintf("invalid block cache access on cache %s address %08.08x size %d\n",
                  _Name.c_str(), address, size);
      return;
   }
   memcpy((void*)&(_Memory[MEMORY_ADDRESS(_ElementSize, address)]), buf, MEMORY_SIZE(_ElementSize, elements));
}

void cBlockCache::Write (CONST_STRING_T name, ULONG_T elements, void *buf)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cBlockCache::Write (CONST_STRING_T name, ULONG_T elements, void *buf)");
}

void cBlockCache::Write (CONST_STRING_T name, CONST_STRING_T value)
{
   throw cError(METHOD_NOT_SUPPORTED, 0, "void cBlockCache::Write (CONST_STRING_T name, CONST_STRING_T value)");
}

void cBlockCache::Save (ULONG_T elapsed)
{
   cObjectLock __lock__(&_CacheMutex);
   BLOCK_BUFFER_MAP_T::const_iterator i = _BlockBuffers.begin();
   while (i != _BlockBuffers.end()) {
      cBlockBuffer * buffer = (*i).second;
      if (buffer->_RefreshType == SH_REFRESH_INTERVAL &&
          buffer->Expired(elapsed)) {
         BLOCK_MAP_T & blocks = buffer->BlockMap();
         Save(blocks);
      }
      i++;
   }
}

void cBlockCache::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
   cObjectLock __lock__(&_CacheMutex);
   BLOCK_MAP_T & blocks = GetBlocks(refresh_type, refresh_value);
   Save(blocks);
}

void cBlockCache::Save (BLOCK_MAP_T &block_map, BOOL_T change_events)
{
   BLOCK_MAP_T::const_iterator i = block_map.begin();
   while (i != block_map.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      ULONG_T size = block->size;
      ULONG_T elements = block->elements;
      _Device->Read(_CacheName.c_str(),
                    block->address,
                    size,
                    _Buf,
                    _BufSize,
                    VF_DEVICE);
      switch (_ElementSize) {
      case 1:
         {
            UCHAR_T change_map[MAX_BLOCK_BUFFER_LEN] = {0};
            UCHAR_T * source = (UCHAR_T*)_Buf;
            UCHAR_T * destination = (UCHAR_T*)block->memory;
            ULONG_T j = 0;
            for (j=0; j<elements; j++) {
               if (source[j] != destination[j]) {
                  destination[j] = source[j];
                  if (change_events) {
                     SET_CHANGED(change_map, j);
                  }
               }
            }
            if (change_events) {
               for (j=0; j<elements; j++) {
                  if (CHANGED(change_map, j)) {
                     _Device->Changed(_CacheName.c_str(), block->address + j);
                  }
               }
            }
         }
         break;
      case 2:
         {
            UCHAR_T change_map[MAX_BLOCK_BUFFER_LEN] = {0};
            USHORT_T * source = (USHORT_T*)(void*)_Buf;
            USHORT_T * destination = (USHORT_T*)block->memory;
            ULONG_T j = 0;
            for (j=0; j<elements; j++) {
               if (source[j] != destination[j]) {
                  destination[j] = source[j];
                  if (change_events) {
                     SET_CHANGED(change_map, j);
                  }
               }
            }
            if (change_events) {
               for (j=0; j<elements; j++) {
                  if (CHANGED(change_map, j)) {
                     _Device->Changed(_CacheName.c_str(), block->address + j);
                  }
               }
            }
         }
         break;
      case 4:
         {
            UCHAR_T change_map[MAX_BLOCK_BUFFER_LEN] = {0};
            ULONG_T * source = (ULONG_T*)_Buf;
            ULONG_T * destination = (ULONG_T*)block->memory;
            ULONG_T j = 0;
            for (j=0; j<elements; j++) {
               if (source[j] != destination[j]) {
                  destination[j] = source[j];
                  if (change_events) {
                     SET_CHANGED(change_map, j);
                  }
               }
            }
            if (change_events) {
               for (j=0; j<elements; j++) {
                  if (CHANGED(change_map, j)) {
                     _Device->Changed(_CacheName.c_str(), block->address + j);
                  }
               }
            }
         }
         break;
      case 8:
         {
            UCHAR_T change_map[MAX_BLOCK_BUFFER_LEN] = {0};
            DOUBLE_T * source = (DOUBLE_T*)_Buf;
            DOUBLE_T * destination = (DOUBLE_T*)block->memory;
            ULONG_T j = 0;
            for (j=0; j<elements; j++) {
               if (source[j] != destination[j]) {
                  destination[j] = source[j];
                  if (change_events) {
                     SET_CHANGED(change_map, j);
                  }
               }
            }
            if (change_events) {
               for (j=0; j<elements; j++) {
                  if (CHANGED(change_map, j)) {
                     _Device->Changed(_CacheName.c_str(), block->address + j);
                  }
               }
            }
         }
         break;
      default:
         {
            void * source = _Buf;
            void * destination = block->memory;
            memcpy(destination, source, block->size);
         }
         break;
      }
      i++;
   }
}

void cBlockCache::Load ()
{
   if (_DynamicBlockOptimization) {
      Load(_OptimizedBufferedBlocks);
   } else {
      Load(_BufferedBlocks);
   }
}

static STRING_T LogFile(const STRING_T & cache_name)
{
   STRING_T log_file = "Log/";
   log_file += cache_name;
   log_file += ".txt";
   return log_file;
}
void cBlockCache::Load (BLOCK_MAP_T &block_map)
{
   if (_Device->get_DebugLevel())
      remove(LogFile(this->get_CacheName()).c_str());

   int size = block_map.size();
   int block_no = 0;
   BLOCK_MAP_T::const_iterator i = block_map.begin();
   while (i != block_map.end()) {
      block_no++;
      _Device->SetProgress(DEVICE_DOWNLOAD_PROGRESS, (100 * block_no) / size);
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      if (_Device->get_DebugLevel()) {
         FILE * stream = fopen(LogFile(this->get_CacheName()).c_str(), "a");
         if (stream != NULL) {
            fprintf(stream, "%s: %08.08d %d %p\n", _CacheName.c_str(), block->address, block->size, block->memory);
            fclose(stream);
         }
      }
      _Device->Write(_CacheName.c_str(),
                     block->address,
                     block->size,
                     block->memory);
      i++;
   }
}

void cBlockCache::Upload ()
{
   if (_DynamicBlockOptimization) {
      Save(_OptimizedBufferedBlocks, false);
   } else {
      Save(_BufferedBlocks, false);
   }
}

void cBlockCache::Download ()
{
#ifdef lassma
int i = 0;
for (i=0; i<100; i++) {
   OptimizeBuffers();
}
#endif
   Load();
}

void cBlockCache::OptimizeBuffers()
{
   cObjectLock __lock__(&_OptimizationMutex);
   ClearBlockMap(_OptimizedBufferedBlocks);
   _OptimizedBufferedBlocks = OptimizedBlocks(_BufferedBlocks);
   MarkAsBuffered(_OptimizedBufferedBlocks);
}

ULONG_T cBlockCache::MinIdleTime ()
{
   return 50;
}

void cBlockCache::AddBlock (BLOCK_MAP_T &blocks, TRANSFER_CONTROL_BLOCK *block)
{
   if (!IS_ADDRESS_MAPPED(block)) return;
   if (block->elements == 0) return;
   blocks[block->address] = block;   
}

void cBlockCache::Optimize (BLOCK_MAP_T &blocks)
{
#undef MIN_MAX_OPTIMIZATION
#ifdef MIN_MAX_OPTIMIZATION
   BLOCK_MAP_T temp_blocks = blocks;
   blocks.clear();
   LONG_T min = 0xf000000;
   LONG_T max = -1;
   BLOCK_MAP_T::iterator i = temp_blocks.begin();
   while (i != temp_blocks.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      LONG_T address = (LONG_T)block->address;
      LONG_T elements = (LONG_T)block->elements;
      if (address < min) {
         min = address;
      }
      if (address + elements > max) {
         max = address + elements;
      }
      i++;
   }
   if (max >= 0) {
      ULONG_T address = min;
      ULONG_T elements = (max - min) + 1; 
      void * memory = &(_Memory[MEMORY_ADDRESS(_ElementSize, address)]);
      TRANSFER_CONTROL_BLOCK * block = _Device->AllocAddressBlock(memory, address, elements);
      AddBlock(blocks, block);
   }
#else
   BOOL_T optimized = false;
   BOOL_T changed = true;
   while (changed) {
      changed = false;
      BLOCK_MAP_T::iterator i = blocks.begin();
      while (i != blocks.end()) {
         TRANSFER_CONTROL_BLOCK * block = (*i).second;
         optimized = Optimize(blocks, block);
         if (optimized) {
            changed = true;
            blocks.erase(i);
            break;
         }
         i++;
      }
   }
#endif
}

BOOL_T cBlockCache::Optimize (BLOCK_MAP_T &blocks, TRANSFER_CONTROL_BLOCK *block)
{
   BLOCK_MAP_T::const_iterator i = blocks.begin();
   while (i != blocks.end()) {
      TRANSFER_CONTROL_BLOCK * old_block = (*i).second;
      if (block != old_block) {
         ULONG_T address1 = block->address;
         ULONG_T elements1 = block->elements;
         ULONG_T right1 = address1 + elements1 - 1;
         ULONG_T address2 = old_block->address;
         ULONG_T elements2 = old_block->elements;
         ULONG_T right2 = address2 + elements2 - 1;
         UCHAR_T relation = Relation(address1, right1, address2, right2);
         switch (relation) {
         case LEFT_TOUCH:
            old_block->address = address1;
            old_block->elements = (right2 - address1) + 1;
            old_block->memory = block->memory;
            return true;
         case RIGHT_TOUCH:
            old_block->elements = (right1 - address2) + 1;
            return true;
         case LEFT_OVERLAP:
            old_block->address = address1;
            old_block->elements = (right2 - address1) + 1;
            old_block->memory = block->memory;;
            return true;
         case RIGHT_OVERLAP:
            old_block->elements = (right1 - address2) + 1;
            return true;
         case FULL_OVERLAP:
            old_block->address = address1;
            old_block->elements = elements1;
            old_block->memory = block->memory;;
            return true;
         case INCLUDE: return true;
         case LEFT_DISTINCT:
         case RIGHT_DISTINCT:
            break;
         default:
            break;
_ASSERT_UNCOND
         }
      }
      old_block->refresh_value = _MIN_(old_block->refresh_value,block->refresh_value);
      i++;
   }
   return false;
}

BLOCK_MAP_T cBlockCache::OptimizedBlocks(const BLOCK_MAP_T & blocks)
{
   int buf_size = DEFAULT_ELEMENT_COUNT;
   char * buffer = (char*)calloc(1, buf_size);
   BLOCK_MAP_T optimized_blocks;
   BLOCK_MAP_T::const_iterator i = blocks.begin();
   while (i != blocks.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      if (block->map_item == NULL || block->map_item->enabled) {
         int address = block->address;
         if (buffer != NULL) {
            int i = 0;
            for (i=0; i<block->elements; i++) {
               char * ptr = &(buffer[address+i]);
               *ptr = 0xaa;
               buffer[address+i] = 1;
            }
         }
         if (block->elements == 2) {
            int dummy = 0;
         } else if (block->elements > 2) {
            int dummy = 0;
         }
      } else {
         int dummy = 0;
      }
      i++;
   }
   char prevc = 0;
   char curc = 0;
   int start = buf_size;
   int end = 0;
   int addr = 0;
   int len = 0;
   for (addr=0; addr<buf_size; addr++) {
      curc = buffer[addr];
      if (prevc != curc) {
         if (curc == 0) {
            end = addr;
            len = end - start;
            void * memory = &(_Memory[MEMORY_ADDRESS(_ElementSize, start)]);
            TRANSFER_CONTROL_BLOCK * block = AllocTransferBlock(_Device, memory, start, len);
            optimized_blocks[start] = block;
            start = buf_size;
            end = 0;
         } else if (curc == 1) {
            start = addr;         
         }
      }
      prevc = curc;
   }
   BLOCK_MAP_T copy = BlockMapCopy(optimized_blocks);
   ClearBlockMap(optimized_blocks);
   free(buffer);
   return copy;
}

BLOCK_MAP_T cBlockCache::BlockMapCopy(const BLOCK_MAP_T & source)
{
   BLOCK_MAP_T copy;
   BLOCK_MAP_T::const_iterator i = source.begin();
   while (i != source.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      TRANSFER_CONTROL_BLOCK * block_copy = AllocTransferBlock((cDevice*)block->device, block->memory, block->address, block->elements);
      block_copy->map_item = block->map_item; 
      copy[block->address] = block_copy;
      i++;
   }
   return copy;
}

void cBlockCache::ClearBlockMap(BLOCK_MAP_T & block_map)
{
   BLOCK_MAP_T::const_iterator i = block_map.begin();
   while (i != block_map.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      cSystemUtils::Free(block);
      i++;
   }
   block_map.clear();
}

BOOL_T cBlockCache::BlockMapsAreEqual(const BLOCK_MAP_T & left, const BLOCK_MAP_T & right) const
{
   BLOCK_MAP_T::const_iterator li = left.begin();
   while (li != left.end()) {
      TRANSFER_CONTROL_BLOCK * left_block = (*li).second;
      BLOCK_MAP_T::const_iterator ri = right.find(left_block->address);
      if (ri == right.end()) {
         return false;
      }
      TRANSFER_CONTROL_BLOCK * right_block = (*ri).second;
      if (left_block->memory != right_block->memory) {
         return false;
      }
      if (left_block->device != right_block->device) {
         return false;
      }
      if (left_block->name != right_block->name) {
         return false;
      }
      if (left_block->refresh_type != right_block->refresh_type) {
         return false;
      }
      if (left_block->refresh_value != right_block->refresh_value) {
         return false;
      }
      if (left_block->address != right_block->address) {
         return false;
      }
      if (left_block->size != right_block->size) {
         return false;
      }
      if (left_block->elements != right_block->elements) {
         return false;
      }
      li++;
   }
   return true;
}

void cBlockCache::MarkAsCached (BLOCK_MAP_T &blocks)
{
   BLOCK_MAP_T::const_iterator i = blocks.begin();
   while (i != blocks.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      ULONG_T elements = block->elements;
      block->size = elements * _ElementSize;
      ULONG_T address = block->address;
      for (ULONG_T j=0; j<elements; j++) {
         ULONG_T addr = address + j;
         SET_MAP(_CachedByAddress, addr);
      }
      InfoPrintf("cache %s block: (%04.04x,%d %p %d)\n",
                 _Name.c_str(), block->address, block->elements, block->memory, block->refresh_value);
      i++;
   }
}

void cBlockCache::MarkAsBuffered (BLOCK_MAP_T &blocks)
{
   BLOCK_MAP_T::const_iterator i = blocks.begin();
   while (i != blocks.end()) {
      TRANSFER_CONTROL_BLOCK * block = (*i).second;
      ULONG_T elements = block->elements;
      block->size = elements * _ElementSize;
      ULONG_T address = block->address;
      for (ULONG_T j=0; j<elements; j++) {
         ULONG_T addr = address + j;
         SET_MAP(_BufferedByAddress, addr);
      }
      InfoPrintf("buffer %s block: (%04.04x,%d %p)\n",
                 _Name.c_str(), block->address, block->elements, block->memory);
      i++;
   }
}

BLOCK_MAP_T & cBlockCache::GetBlocks (UCHAR_T refresh_type, ULONG_T refresh_value)
{
   cBlockBuffer * buffer = GetBlockBuffer(refresh_type, refresh_value);
   return buffer->BlockMap();
}

cBlockBuffer * cBlockCache::GetBlockBuffer (UCHAR_T refresh_type, ULONG_T refresh_value)
{
   ULONG_T block_id = BLOCK_ID(refresh_type,refresh_value);
   BLOCK_BUFFER_MAP_T::const_iterator i = _BlockBuffers.find(block_id);
   if (i == _BlockBuffers.end()) {
      cBlockBuffer * buffer = new cBlockBuffer(refresh_type, refresh_value);
      _BlockBuffers[block_id] = buffer;
      return buffer;
   } else {
      return (*i).second;
   }
}

UCHAR_T cBlockCache::get_ElementSize () const
{
   return _ElementSize;
}

ULONG_T cBlockCache::get_Elements () const
{
   return _Elements;
}

UCHAR_T * cBlockCache::get_Memory () const
{
   return _Memory;
}

