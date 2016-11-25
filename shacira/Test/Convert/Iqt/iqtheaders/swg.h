/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     SWG.H
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
*     12.06.92 -SF-    Modul als DLL angelegt
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

#ifndef _swg
#define _swg

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/*---------------------------------------------------------------------------
X Verwendung von 'normalen' Funktionen
---------------------------------------------------------------------------*/
GLOBAL int SWG_Init( BOOL init_bbram );
GLOBAL IQT_HANDLE SWG_Draw( ELEMENT* el_ptr, BYTE line, BYTE from, BYTE screen );

#endif /* ifndef _swg */




