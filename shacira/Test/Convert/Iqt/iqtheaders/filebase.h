/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/

#ifndef __filebase__
#define __filebase__

#define MAX_HANDLES                             2

typedef long FILEBASE_ADDRESS;

typedef struct filebase_config
{       char * name;
        UWORD buffer_size;
}       FILEBASE_CONFIG;

GLOBAL int FILEBASE_Open(int channel, long size, FILEBASE_CONFIG * config);
GLOBAL int FILEBASE_Close(int handle);
GLOBAL long FILEBASE_Write(int handle, FILEBASE_ADDRESS dst, void * src, long size);
GLOBAL long FILEBASE_Read(int handle, void * dst, FILEBASE_ADDRESS src, long size);
GLOBAL long FILEBASE_Set(int handle, FILEBASE_ADDRESS dst, BYTE value, long size);
GLOBAL int FILEBASE_Default(int channel, FILEBASE_CONFIG ** config, BOOL verbose);

#define FILEBASE_NO_ERROR                                                               0
#define FILEBASE_UNABLE_TO_OPEN_FILE                                    -50
#define FILEBASE_NO_MORE_HANDLES                                                -51
#define FILEBASE_INVALID_SIZE                                                   -52
#define FILEBASE_NO_MORE_MEMORY                                                 -53
#define         FILEBASE_NO_MEMORY_DETECTED                                     -54
#define FILEBASE_NO_BANK_DESCRIPTION                                    -55

#endif  /* filebase */


