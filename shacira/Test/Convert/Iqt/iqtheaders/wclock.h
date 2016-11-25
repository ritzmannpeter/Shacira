/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     WCLOCK.H
*
*  BESCHREIBUNG:
*     ...
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   08.05.92
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*                      Neu entstanden
*     11.07.92 -SF-    Portierung des IQT-350 auf IQT-450
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Keine
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _wclock
#define _wclock

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqttsk.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Id's fuer WClock_SetParam()
****************************************************************************/
#define WCLOCK_ID_SET_TIME     0
#define WCLOCK_ID_SET_ON       1
#define WCLOCK_ID_SET_OFF      2

/****************************************************************************
X  Funktionen
****************************************************************************/

GLOBAL int WClock_Init(BOOL init_bbram);
GLOBAL PARAMETER WClock_Do(PARAMETER last_time);
GLOBAL int WClock_SetParam(int type, int param);

#endif /* ifndef _wclock */






