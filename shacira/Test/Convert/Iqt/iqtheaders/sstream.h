
#ifndef __sstream__
#define __sstream__

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __WIN32__
#include <windows.h>
//#include <winbase.h>
#include <io.h>
#endif

GLOBAL int  SSTREAM_FlushDisk       (FILE *stream);
GLOBAL void SSTREAM_CutAtCurrentPos (FILE **stream, char *filename, 
                                     char *flags);
GLOBAL int  SSTREAM_CutAtBegin      (FILE **stream, long cutlen,
                                     char *filename, char *flags);

#endif /* __sstream__ */

