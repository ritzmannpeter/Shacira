
#ifndef _cAlloc_h
#define _cAlloc_h

#include <malloc.h>

class cAlloc
{
public:
   static inline void * Alloc(size_t size)
   {
      _AllocatedBlocks++;
      return calloc(1, size);
   }
   static inline void Free(void * memory)
   {
      _AllocatedBlocks--;
      free(memory);
   }
   static int _AllocatedBlocks;
};

#endif
