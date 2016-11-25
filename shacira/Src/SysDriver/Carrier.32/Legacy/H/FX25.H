#ifndef _fx25
#define _fx25

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

#define OLD_SIZE_FX      1024
#define FX25_HEADERSIZE  68

/* Teildateikopf FX25 */
 typedef struct {
   signed_16  ToolNr;        /* Werkzeug-Nr. */
   signed_16  MatNr;         /* Material-Nr. */
   signed_8  Date[4];       /* Datum (Jahr-Monat-Tag) */
   signed_16  ProcNr;        /* */
   signed_16  LenHeader;     /* 32 */
   signed_16  LenData;       /* */
   signed_16  LenProgFeld;
} OLD_FX25_DISK_SUB_HEADER;

GLOBAL const DRIVE_MODULE * FX25_Module();
GLOBAL const FILE_MODULE * FX25_FileModule();

#endif /* ifndef _fx25 */
