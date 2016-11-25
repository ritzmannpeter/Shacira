
#include "HAlloc.h"
#include <malloc.h>
#include <stddef.h>

static long _Blocks = 0;

long AllocatedBlocks()
{
   return _Blocks;
}

void * HAlloc(unsigned_32 size)
{
   void * ptr = calloc(1, size);
   if (ptr != NULL) _Blocks++;
   return ptr;
}

int HFree(void * buf)
{
   free(buf);
   _Blocks--;
   return 0;
}


