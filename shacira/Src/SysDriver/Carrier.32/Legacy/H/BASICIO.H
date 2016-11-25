/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _platform
#include <platform.h>
#define _platform
#endif
/*.EI.***********************************************************************/

#ifndef __basicio__
#define __basicio__

typedef struct IO_MODULE IO_MODULE_;
typedef struct io_module
{  long (*init)(IO_MODULE_ ** module, const char * path);
   long (*check)(void);
   long (*read)(USR_LONG pos, USR_LONG size, void * buffer);
   long (*write)(USR_LONG pos, USR_LONG size, void * buffer);
   long (*exit)(void);
}  IO_MODULE;

#define CARRIER_IO      1
#define DUMP_IO         2

GLOBAL int BASIC_Init(int io, int delay_size, char * path);
GLOBAL int BASIC_Check();
GLOBAL int BASIC_Read(USR_LONG address, USR_LONG size, void * buffer);
GLOBAL int BASIC_Write(USR_LONG address, USR_LONG size, void * buffer);
GLOBAL int BASIC_Exit(void);

#endif   /* basicio */

