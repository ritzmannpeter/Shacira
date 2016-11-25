/******************************************************************************
*  Dateiname : stime.h
*
*  *** HISTORY ***
*  12.11.99 -HAns-  History angelegt, Struktur stime_t um DayOfWeek erweitert
*
*  Beschreibung :
*     Definition der Plattformkonstanten. Diese Konstanten werden zum Platt-  
*     formabhaengigen Uebersetzen benutzt.                                    
*     Bisher definiert: __QNX2__    : QNX 2                                   
*                       __QNX4__    : QNX 4                                   
*                       __QNXNTO__  : Neutrino                                
*                       __WIN32__   : Windos NT / Windows 95                  
******************************************************************************/


#ifndef __stime__
#define __stime__

typedef struct stime_t {
   int msec;      /* 0 - 999 */
   int sec;       /* 0 - 59 */
   int min;       /* 0 - 59 */
   int hour;      /* 0 - 23 */
   int day;       /* 1 - 31 */
   int month;     /* 1 - 12 */
   int year;      /* 4-stellige Jahreszahl, z.B. 1998 */
	int DayOfWeek; /* Sunday=0, Monday=1, and so on */
} STIME_T;

GLOBAL int STime_SetTime (STIME_T *time);
GLOBAL int STime_GetTime (STIME_T *time);

#endif /* __rtc__ */

