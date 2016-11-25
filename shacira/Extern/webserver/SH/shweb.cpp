
#include "System/Sys/cExceptionHnd.h"
#include <stdio.h>

unsigned long _VirtualMemory = 0;
unsigned long _TransientObjects = 0;
cExceptionHnd _ExceptionHandler;

extern "C" {
void PrintMemStatistics(FILE * stream)
{
}
}
