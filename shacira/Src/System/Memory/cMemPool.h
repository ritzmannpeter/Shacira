
#ifndef _cMemPool_h_
#define _cMemPool_h_ 1

#include <stddef.h>
#include <malloc.h>
#include <string>
#include <list>
#include <windows.h>

#define DEFAULT_CAPACITY      100000
#define DEFAULT_BLOCK_SIZE    1024

typedef struct header {
   int capacity;
   int block_size;
} MEMPOOL_HEADER_T;

class cMemPool {
public:
   cMemPool(int capacity = DEFAULT_CAPACITY, int block_size = DEFAULT_BLOCK_SIZE);
   virtual ~cMemPool();
   void * AllocBlock(size_t size);
   void FreeBlock(void * ptr);
   bool Check(std::string & result);
protected:
   void PrepareMemory();
   void * NextFreeBlock(unsigned char * data);
   void * NextFreeBlock();
protected:
   int _Capacity;
   int _BlockSize;
   void * _MemoryPtr;
   MEMPOOL_HEADER_T * _HeaderPtr;
   unsigned char * _DataPtr;
   CRITICAL_SECTION _MemoryLock;
   std::list<void*> _FreeList;
};

#endif // _cMemPool_h_
