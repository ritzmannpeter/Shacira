#ifndef _fmt1
#define _fmt1

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
/*.EI.***********************************************************************/

#define OLD_SIZE_FMT1     1024
#define FMT1_HEADERSIZE   68

#include "Pack_1"

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

#define FMT1_GET_DAY(date) ((USR_BYTE)date[2])
#define FMT1_GET_MONTH(date) ((USR_BYTE)date[1])
#define FMT1_GET_YEAR(date) \
	(((USR_BYTE)date[0] < 70) ? \
	((USR_BYTE)date[0] + 100) : (USR_BYTE)date[0])
#define FMT1_GET_SEC(date) (0)
#define FMT1_GET_HOUR(date) (0)
#define FMT1_GET_MIN(date) (0)

#define FMT1_SET_YEAR(year)	((year < 100) ? year : year - 100)

#include "Unpack"

#endif /* ifndef _fmt1 */
