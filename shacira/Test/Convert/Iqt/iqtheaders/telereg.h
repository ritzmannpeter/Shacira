/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     TELEREG.H
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

#ifndef _telereg
#define _telereg

/*.SI.***********************************************************************/
#include <syntax.h>
#include <g_const.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Fehlerkonstanten
****************************************************************************/
#define TLG_ERR_TASK_START   1 
#define TLG_ERR_2MANYSLOW    2
#define TLG_ERR_2MANYFAST    3
#define TLG_ERR_2MANYINJ     4
#define TLG_ERR_INVALID_ATTR 5
#define TLG_ERR_NO_ENDMARK   6
#define TLG_ERR_DMA_ADDR     7

typedef struct {
   UWORD *   pElVal;        /* Zeiger in el. Pufferbereich des 1. Registers */
   TICKER   LastTrans;     /* Zeitpunkt der letzten Uebertragung           */
} TLGADR_TYPE;

GLOBAL int  TlgInit        ( void );
GLOBAL UWORD * TlgGetRegAddr  ( int tlg_ind, int tlg_pos );
GLOBAL int  TlgRequest     ( int tlg_ind, BOOL wait );
GLOBAL void TlgFastRequest ( void );
GLOBAL void TlgInjRequest  ( void );
GLOBAL void TlgSlowRequest ( void );
GLOBAL int  DownLoadTlgs   ( void );
GLOBAL int  TlgSend ( int tlg_ind );
GLOBAL int  TlgReceive ( int tlg_ind );

#endif /* ifndef _telereg */
