
#ifndef _alloc_h
#define _alloc_h

#include <malloc.h>
#include "comm.h"

class COMM_EXPORT cAlloc
{
public:
   static inline void * allocbuffer(size_t size)
   {
      _allocatedBlocks++;
#if (_MSC_VER >= 1300)
      return std::calloc(1, size);
#else
      return calloc(1, size);
#endif
   }
   static inline void freebuffer(void * memory)
   {
      _allocatedBlocks--;
#if (_MSC_VER >= 1300)
      std::free(memory);
#else
      free(memory);
#endif
   }
   static int _allocatedBlocks;
};

#endif
