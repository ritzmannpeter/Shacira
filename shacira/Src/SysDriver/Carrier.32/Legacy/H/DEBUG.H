#ifndef _debug
#define _debug

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __platform__
#include <platform.h>
#define __platform__
#endif
/*.EI.***********************************************************************/

#define NO_DEBUG      0L
#define VERBOSE         0x00000001L
#define FAILURES        0x00000002L
#define DEBUG_CARIO     0x80000000L
#define DEBUG_DEVICES   0x40000000L

#define PRINTL		PrintLine(__FILE__, __LINE__);

GLOBAL int SetDebugMode (long debug_mode, char * output);
GLOBAL int DebugPrintf(long mode, char * fmtstr, ...);
GLOBAL void LogPrintf(char * filename, char * fmtstr, ...);
void PrintLine(const char * file, int line);
void PrintBox(const char * text, const char * title);

#undef DEBUG_HEAP
#ifdef DEBUG_HEAP
GLOBAL void * HeapAlloc(int size);
GLOBAL int HeapFree(char * ptr);
GLOBAL void ShowAlloc(void);
#else
#define HeapAlloc(size) malloc(size)
#define HeapFree(ptr)   free(ptr)
#define ShowAlloc()
#endif

#endif /* ifndef _debug */
