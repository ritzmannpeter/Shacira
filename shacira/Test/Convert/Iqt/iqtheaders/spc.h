/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     SPC.H
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
*     10.06.92 -SF-    Portierung der SPC-Funktionen
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

#ifndef _spc
#define _spc

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Allgemeine Konstanten
****************************************************************************/
#define  SPCNO        5             /* Anzahl moeglicher Regelkarten */
#define  SPCTEST     50             /* Anzahl Stichproben (25x2 Intervalle */

/****************************************************************************
X  globale Daten
****************************************************************************/
extern BYTE SPCUsedTab[SPCNO];
extern long SPCPreStdAbw[SPCNO];
extern long SPCTimeDate[SPCTEST];
extern long SPCAddCounter[SPCTEST];
extern BYTE SPCChange[SPCTEST];
extern UWORD SPCLastItem;
extern UWORD SPCLastPreTestItem;
extern BYTE SPCActInt;
extern BYTE SPCUsedInt;

extern long* SPCValuePTab[SPCNO];
extern long* SPCPreTestValuePTab[SPCNO];
extern long* SPCMTab[SPCNO];
extern long* SPCSTab[SPCNO];
extern long* SPCRTab[SPCNO];

/****************************************************************************
X  Id's fuer SPC_SetParam()
****************************************************************************/
#define SPC_ID_CHANGE_OSG_USG         0
#define SPC_ID_CHANGE_BREAK_SIZE      1
#define SPC_ID_SELECT_INTERVALL       2
#define SPC_ID_TIME_SWITCH            3
#define SPC_ID_START_PRETEST          4
#define SPC_ID_STARTEND_AUTO_MODE     5
#define SPC_ID_START_MANUAL_MODE      6
#define SPC_ID_MULTIPLEX              7
#define SPC_ID_CHANGE_PRETEST_SIZE    8
#define SPC_ID_CHANGE_TEST_SIZE       9

GLOBAL int SPC_Init( BOOL init_bbram );
GLOBAL int SPC_GetItem( void );
GLOBAL int SPC_NewTestVar( long var_nr, UWORD index,
                           UWORD ind1, UWORD ind2, UWORD ind3 );
GLOBAL int SPC_FltVar( UWORD ctrl, long var_nr, UWORD index, REGIST* ri_ptr );
GLOBAL int SPC_SetParam( int type, int par_int, long par_long );
GLOBAL IQT_HANDLE SPC_Draw( ELEMENT* el_ptr, BYTE line, BYTE from, BYTE screen );

#endif /* ifndef _spc */





