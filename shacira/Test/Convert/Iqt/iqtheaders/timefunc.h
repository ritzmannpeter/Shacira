
#ifndef _timefunc
#define _timefunc

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/

/* Zeitbasis fuer Zeitangaben */
#define TIME_TICK  0      /* 50 ms */
#define TIME_SECS   1      /* Sekunden */
#define TIME_MINS   2      /* Minuten */
#define TIME_HRS    3      /* Stunden */
#define TIME_FAST1   4      /* 1  ms */
#define TIME_FAST2   5      /* 2  ms */
#define TIME_FAST5   6      /* 5  ms */
#define TIME_FAST10  7      /* 10 ms */
#define TIME_FAST25  8      /* 25 ms */
#define TIME_FAST50  9      /* 50 ms */
#ifdef __QNX2__
#define TIME_TICKS TIME_TICK     /* alte Form von TIME_TICK */
#endif

typedef ULONG TIME;  /* frueher UWORD */

/* Zeittyp TIME und Zugriffsfunktionen */
#define TIME_SET(B,T)      (TIME)( ((TIME) B) << 16 | ((TIME)T) & 0x0000ffff )
#define TIME_GET_BASE(P)   (UWORD)( ((TIME) P) >> 16 )
#define TIME_GET_TIME(P)   (UWORD)( ((TIME) P) & 0x0000ffff )

long MilliSecs(TIME time_spec);
void TimeRel(TIME time_spec, long * secs, long * millisecs);

#endif /* _timefunc */
























