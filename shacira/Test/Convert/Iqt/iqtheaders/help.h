/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     HELP.H
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
*     02.07.92 -SF-    Help-Funktionen in DLL <D_UTIL> angelegt
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

#ifndef _help
#define _help

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Allgemeine Konstanten
****************************************************************************/
#define HELP_PAGE_INIT     0
#define HELP_SCROLL_UP     1
#define HELP_SCROLL_DOWN   2
#define HELP_BUILD_SHOW    3
#define HELP_ACT_SHOW      4

#define  HELP_BREAK_ON     0  /* Aufbau des Hilftextes unterbrechbar */
#define  HELP_BREAK_OFF    1  /* Aufbau des Hilfetextes nicht unterbrechbar */

/****************************************************************************
X  Typen fuer Hilfetexte
****************************************************************************/
typedef struct help_hnd {
   TEXT_INDEX PageText;    /* Akt. Text der Seite */
   TEXT_INDEX ElemText;    /* Akt. Text des Elements */
   BYTE       State;       /* 0=Kein Text, 1=Seitentext, 2=Elementtext */
   } HELP_HND;

GLOBAL int Help_Init( BOOL init_bbram, int lang );
GLOBAL int Help_Show( int ctrl, HELP_HND* help_hnd_ptr, IQT_HANDLE crt_hnd, ELEMENT* el_ptr, int page_ind, BYTE brk );

#endif /* ifndef _help */




