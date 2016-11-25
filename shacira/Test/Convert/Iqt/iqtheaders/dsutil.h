/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DSUTIL.H
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
*   13.12.02   -HA-     GetAggTabAddIndex, GetSnTabAddIndex eingebaut
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

#ifndef _dsutil
#define _dsutil

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

/* logische Operatoren
 */
#define OR  0
#define AND 1
#define NOT 2

/* relationale Operatoren
 */
#define EQ 0
#define GT 1
#define GE 2

/* sonstige Konstanten
 */
#define CHANGE 1
#define FB_TX2 2
#define FX1_TB 3
#define FX1_TX2 4


GLOBAL UWORD Check99           (void);
GLOBAL UWORD SoftWkzEinbau     (UWORD param);
GLOBAL void GetConstReg1      (long * ConstReg , UWORD Format);
GLOBAL void GetConstReg2      (long * ConstReg , UWORD Format);
GLOBAL int  CheckWkzOkay      (void);
GLOBAL int  GetAggTabIndex    (int res, int agg, int par);
GLOBAL int  GetSnTabIndex     (int res, int agg, int par);
GLOBAL int  GetAggTabAddIndex (int res, int agg, int par);
GLOBAL int  GetSnTabAddIndex  (int res, int agg, int par);

#endif /* ifndef _dsutil */




