
#ifndef __halloc__
#define __halloc__

/*.SI.***********************************************************************/
#include <syntax.h>
#include <sys/types.h>
#include <stddef.h>
/*.EI.***********************************************************************/

GLOBAL void * SharedMemAlloc(size_t size, char * name);
GLOBAL void SharedMemFree(void * mem, char * name);
GLOBAL void * HAlloc(size_t size);
GLOBAL void HFree(void * ptr);
GLOBAL size_t HAvail(void);
GLOBAL size_t HUsed(void);
GLOBAL int HControl(void);

#endif /* __halloc__ */
