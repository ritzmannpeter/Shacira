/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     BG.H
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
*     VERSION:    4.0                       DATUM:   07.08.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*                      Neu entstanden
*     07.08.92 -SF-    Portierung des IQT-350 auf IQT-450
*     09.10.92 -PR-    Modul der DLL Util zugeordnet
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

#ifndef _bg
#define _bg

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtmem.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Allgemeine Macro's
****************************************************************************/
#define SET_FG    BBRAM_SetBank(BANKED_BBRAM,FOREGROUND)
#define SET_BG    BBRAM_SetBank(BANKED_BBRAM,BACKGROUND)

/****************************************************************************
X  Id's fuer BG_Write(), BG_SetParam() und BG_GetParam()
****************************************************************************/
#define BG_ID_COPY_FG_TO_BG         0
#define BG_ID_CHANGE_FGBG_SELECTIVE 1
#define BG_ID_CHANGE_FGBG_FULL      2
#define BG_ID_FG_EQUAL_BG           3
#define BG_ID_SET_FGBG_COMPARE      4
#define BG_ID_TOGGLE_OPTIMIZE       5
#define BG_ID_SWITCH_DATASET        6

/****************************************************************************
X  Funktionen
****************************************************************************/
GLOBAL int BG_Init( BOOL init_bbram );
GLOBAL int BG_Write( int type );
GLOBAL int BG_GetParam( int type );
GLOBAL int BG_SetParam( int type, int param );
GLOBAL BOOL BG_RegEqual( UWORD regnr, UWORD ind1, UWORD ind2, UWORD ind3,
                         BYTE info, long* fg_ptr, long* bg_ptr );

#endif /* ifndef _bg */





