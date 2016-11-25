/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     CYLHIS.H
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
*     16.06.92 -SF-    Modul als DLL angelegt
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

#ifndef _cylhis
#define _cylhis

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Id's fuer CylHis_SetParam()
****************************************************************************/
#define CYLHIS_ID_SET_MAXIMUM         0
#define CYLHIS_ID_SHOW_SWITCH         1

GLOBAL int CylHis_Init( BOOL init_bbram );
GLOBAL int CylHis_SetParam( int type, long param );
GLOBAL IQT_HANDLE CylHis_Draw( ELEMENT* el_ptr, BYTE line, BYTE from, BYTE screen );

#endif /* ifndef _cylhis */







