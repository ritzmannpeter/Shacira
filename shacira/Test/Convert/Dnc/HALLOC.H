//---------------------------------------------------------------------------
#ifndef HAllocH
#define HAllocH
//---------------------------------------------------------------------------

#include "Legacy.h"

#ifdef __cplusplus
extern "C" {
#endif

void * HAlloc(unsigned_32 size);
int HFree(void * buf);
long AllocatedBlocks();

#ifdef __cplusplus
}
#endif

#endif
