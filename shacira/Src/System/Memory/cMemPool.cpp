
#include "cMemPool.h"
#include <assert.h>

cMemPool::cMemPool(int capacity, int block_size)
   : _Capacity(capacity),
     _BlockSize(block_size),
     _MemoryPtr(NULL),
     _HeaderPtr(NULL),
     _DataPtr(NULL)
{
#if defined(_WIN32)
   if (!InitializeCriticalSectionAndSpinCount(&_MemoryLock, 0x00000400)) {
      assert(false);
   }
#endif
   int header_size = sizeof(MEMPOOL_HEADER_T) | 0xff;
   int total_size = (_Capacity * _BlockSize) + header_size;
   _MemoryPtr = calloc(1, total_size);
   _HeaderPtr = (MEMPOOL_HEADER_T*)_MemoryPtr;
   _DataPtr = (unsigned char*)_MemoryPtr + header_size;
   PrepareMemory();
}

cMemPool::~cMemPool()
{
}

void * cMemPool::AllocBlock(size_t size)
{
   if ((int)size > _BlockSize) {
      return NULL;
   }
   EnterCriticalSection(&_MemoryLock);
   unsigned char * mem = (unsigned char *)NextFreeBlock();
   if (mem != NULL) {
      *(int*)mem = (int)size;
      LeaveCriticalSection(&_MemoryLock);
      return mem + sizeof(int);
   }
   LeaveCriticalSection(&_MemoryLock);
   return NULL;
}

void cMemPool::FreeBlock(void * ptr)
{
   EnterCriticalSection(&_MemoryLock);
   unsigned char * mem_start = (unsigned char*)ptr - 4;
   memset(mem_start, 0, _BlockSize);
   *(int*)mem_start = (int)0xffffffff;
   _FreeList.push_back(ptr);
   LeaveCriticalSection(&_MemoryLock);
}

bool cMemPool::Check(std::string & result)
{
   return true;
}

void cMemPool::PrepareMemory()
{
   unsigned char * ptr = _DataPtr;
   int i = 0;
   for (i=0; i<_Capacity; i++) {
      _FreeList.push_front(ptr);
      *(unsigned int *)ptr = (int)0xffffffff;
      ptr += _BlockSize;
   }
}

void * cMemPool::NextFreeBlock(unsigned char * data)
{
   unsigned char * ptr = data;
   int i = 0;
   for (i=0; i<_Capacity; i++) {
      if (*(unsigned int *)ptr == 0xffffffff) {
         return ptr;
      }
      ptr += _BlockSize;
   }
   return NULL;
}

void * cMemPool::NextFreeBlock()
{
   void * ptr = NULL;
   std::list<void*>::const_iterator i = _FreeList.begin();
   if (i != _FreeList.end()) {
      ptr = (*i);
      _FreeList.pop_front();
   }
   return ptr;
}


