/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/

#ifndef __pcmciaj__
#define __pcmciaj__

#define MAX_HANDLES                             2

typedef long PCMCIAJ_ADDRESS;

#define MODE_DIRECT             1
#define MODE_INVERT             2

typedef struct pcmciaj_config
{       char * name;
        UWORD base_io_addr;
        long base_addr;
        long page_offset;
        long page_size;
        BYTE pcmcia_segment;
        UWORD pages_per_segment;
        BYTE pcmcia_mode;
}       PCMCIAJ_CONFIG;

#define PAGE(ptr, offset, size)         ((UWORD)((ptr / size) + offset))
#define OFFSET(ptr, size)                               ((UWORD)(ptr % size))

GLOBAL int PCMCIAJ_Open(int channel, long size, PCMCIAJ_CONFIG * config);
GLOBAL int PCMCIAJ_Close(int handle);
GLOBAL long PCMCIAJ_Write(int handle, PCMCIAJ_ADDRESS dst, void * src, long size);
GLOBAL long PCMCIAJ_Read(int handle, void * dst, PCMCIAJ_ADDRESS src, long size);
GLOBAL long PCMCIAJ_Set(int handle, PCMCIAJ_ADDRESS dst, BYTE value, long size);
GLOBAL int PCMCIAJ_Default(int channel, PCMCIAJ_CONFIG ** config, BOOL verbose);

#define PCMCIAJ_NO_ERROR                                                                0

#define PCMCIAJ_NO_ACCESS_TO_NAMED_MEMORY               -60
#define PCMCIAJ_INVALID_SIZE                                                    -61
#define PCMCIAJ_NO_MORE_HANDLES                                         -62
#define         PCMCIAJ_NO_MEMORY_DETECTED                                      -63
#define PCMCIAJ_NO_BANK_DESCRIPTION                             -64

#endif  /* pcmciaj */

