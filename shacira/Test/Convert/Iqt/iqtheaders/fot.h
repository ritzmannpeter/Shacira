/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     FOT.H
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
*     23.06.92 -SF-    FOT-Funktionen als DLL angelegt
*     30.03.01 -TSchw- Konstanten aus fot.c hierher verlagert (siehe MCARD_FOT)
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

#ifndef _fot
#define _fot

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
/*.EI.***********************************************************************/

#define FOT_OBJNR_BLANK    -1L   /* Objekt-Nr. der Leerzeile   (MCARD_FOT) */
#define FOT_OBJNR_END      -2L   /* Objekt-Nr. der Endekennung (MCARD_FOT) */

GLOBAL int FOT_Init( BOOL init_bbram );
GLOBAL int FOT_FltFunc( UWORD ctrl, long obj_nr, UWORD id, UWORD index );
GLOBAL int FOT_InsObj( OBJECT* start_obj_ptr, UWORD obj_ind, OBJECT* new_obj_ptr, UWORD page_nr );
GLOBAL int FOT_DelObj( OBJECT* start_obj_ptr, UWORD obj_ind, OBJECT* del_obj_ptr );

#endif /* ifndef _fot */







