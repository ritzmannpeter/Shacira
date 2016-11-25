/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     SHOW.H   - Show_xxx - Funktionen (mit oder ohne DLL)
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
*     VERSION:    4.0                       DATUM:   01.04.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     22.04.92 -SF-    Implementierung im Zuge der 
*                      Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     04.09.92 -PR-    CHANGE_.. wieder eingefuehrt
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Show_Init - Initialisierung des Moduls SHOW
*     Show_Element - Ein Element anzeigen
*     Show_Softkey - Softkeytexte ausgeben
*     Show_SetParam - Parameter setzen
*
*  DATENTYPEN:
*     Keine
*
*  VARIABLEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _show
#define _show

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <sunichar.h>
/*.EI.***********************************************************************/

/*---------------------------------------------------------------------------
X Allgemeine Konstanten
---------------------------------------------------------------------------*/
   /* Parameter 'from' bei Show_Element() */
#  define NEWPAGE           1     /* Neuaufbau */
#  define REFRESH           2     /* Aktualisierung */
   /* Parameter 'obj_info' bei Show_Element() */
#  define FREE              0     /* Objekt erlaubt */
#  define DARK              1     /* Objekt dunkelgeschaltet */
   /* Parameter 'el_info' bei Show_Element() */
#  define SHOW              0     /* Element wird gerade angezeigt */
#  define NOT_SHOW          1     /* Element wird nicht angezeigt */

#  define CHANGE_ONLY_COLOR 0
#  define CHANGE_ALL        1

   /* Parameter 'col_info' bei Show_Element() */
#  define STANDARD          1     /* Standardfarbe verwenden */
#  define CURRENT_COLOR     2     /* Aktuelle Farbe verwenden */
#  define INPUT             3     /* Eingabefarbe verwenden */
#  define KLICK             4     /* Klickfarbe verwenden */
   /* Parameter 'id' bei Show_SetParam() */
#  define SHOW_ID_SCR_POWER     0
#  define SHOW_ID_SCR_MAXTIME   1
#  define SHOW_ID_SCR_INCTIME   2
#  define SHOW_ID_SCR_VISIBLE   3
#  define SHOW_ID_TEST_SCREEN   4
#  define SHOW_ID_STATLINE_VISIBLE 5
#  define SHOW_ID_STATLINE_DARK    6

/*---------------------------------------------------------------------------
X Verwendung von 'normalen' Funktionen
---------------------------------------------------------------------------*/
GLOBAL int Show_Init( BOOL init_bbram );
GLOBAL BYTE Show_Element( ELEMENT* el_ptr, OBJECT* obj_ptr, BYTE screen,
                          BYTE from, BYTE obj_info, BYTE el_info,
                          BYTE col_info );
GLOBAL void Show_Softkey( BYTE screen, int nr, int line, int col,
                          UNICHAR* txt_ptr );
GLOBAL int Show_SetParam( int id, int param );

#endif /* _show */

