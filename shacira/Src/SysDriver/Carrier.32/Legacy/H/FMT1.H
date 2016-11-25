#ifndef _fmt1
#define _fmt1

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __direct__
#include <direct.h>
#define __direct__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
/*.EI.***********************************************************************/

#define OLD_SIZE_FMT1     1024
#define FMT1_HEADERSIZE   68

/* Teildateikopf FMT1 */
 typedef struct {
   signed_16   ToolNr;        /* Werkzeug-Nr. */
   signed_16   MatNr;         /* Material-Nr. */
   signed_8  Date[4];       /* Datum (Jahr-Monat-Tag) */
   signed_16   ProcNr;        /* */
   signed_16   LenHeader;     /* 32 */
   signed_16   LenData;       /* */
   signed_16   LenProgFeld;
} OLD_FMT1_DISK_SUB_HEADER;

GLOBAL const DRIVE_MODULE * FMT1_Module();
GLOBAL const FILE_MODULE * FMT1_FileModule();

#endif /* ifndef _fmt1 */
