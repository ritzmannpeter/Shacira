/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     BDE.H
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
*     VERSION:    4.0                       DATUM:   06.07.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     06.07.92 -SF-    Portierung des IQT-350 auf IQT-450
*                      - BDE_PTYPE ist jetzt UWORD (keine BankNr mehr)
*     02.03.98 -TSchw- BDE_ID_PRINT_TO_DISK angelegt.
*     15.03.02 -HA-     BDE_ShowNew aufgenommen.
*
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

#ifndef _bde
#define _bde

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Allgemeine Konstanten
****************************************************************************/
/* Anzahl der Prozessparameter */
#define BDENO                       8

/****************************************************************************
X  Konstanten fuer BDE_PageScroll()
****************************************************************************/
#define BDE_SCROLL_UP               0
#define BDE_SCROLL_DOWN             1

/****************************************************************************
X  Id's fuer BDE_SetParam() und BDE_GetParam()
****************************************************************************/
#define BDE_ID_GET_STOP_MSG         0
#define BDE_ID_SET_ACT_VARNR        1
#define BDE_ID_NEW_STOP_MSG         2
#define BDE_ID_PRINT_ORDER          3
#define BDE_ID_PRINT_LEGEND         4
#define BDE_ID_CHANGE_PRINT_MODE    5
#define BDE_ID_CLEAR_BUFFER         6
#define BDE_ID_INC_MINUTES          7
#define BDE_ID_PRINT_TO_DISK        8


/****************************************************************************
X  Funktionen
****************************************************************************/
GLOBAL int BDE_Init( BOOL init_bbram );
GLOBAL int BDE_NewTestVar( long var_nr, UWORD index, UWORD ind1, UWORD ind2, UWORD ind3 );
GLOBAL int BDE_FltVar( UWORD ctrl, long var_nr, UWORD index, REGIST* ri_ptr );
GLOBAL void BDE_GetSoll( UWORD page_nr, UWORD var_nr, BYTE format, long old_val, long new_val, ELEMENT* el_ptr );
GLOBAL int BDE_GetErrMsg( void );
GLOBAL int BDE_GetItem( void );
GLOBAL int BDE_Show( IQT_HANDLE hnd, ELEMENT* el_ptr, BYTE line, BYTE from );
GLOBAL int BDE_ShowNew (IQT_HANDLE hnd, ELEMENT* el_ptr, BYTE line, BYTE from, BYTE type);
GLOBAL int BDE_PageScroll( int dir );
GLOBAL int BDE_SetParam( int type, int par_int, long par_long );
GLOBAL long BDE_GetParam( int type );
GLOBAL int BDE_Print( int id, UWORD* bde_ptr );

#endif  /* ifndef _bde */
