/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     PRINT.H
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
*     05.03.97 -TSchw- Konstante PRINT_NO_PAGE von 0xffff auf 0xfff
*                      geaendert, aus folgendem Grund.
*                      Die Konstante PRINT_NO_PAGE wird bei Erteilung
*                      eines Druckauftrags im Long-Parameter der Meldung
*                      codiert, und zwar in dem Teilparameter "WINHELP".
*                      Bis zum 4.10.96 war dieser Parameter 16 Bit gross,
*                      aber zu diesem Zeitpunkt wurde er auf 12 Bit ver-
*                      kleinert (siehe util.h). Am 25.02.97 wurde das
*                      Makro GET_PRINT_WINHELP nachtraeglich angepasst,
*                      d.h. auf 12 Bit begrenzt (siehe util.h). Ab diesem
*                      Zeitpunkt konnte die Konstante PRINT_NO_PAGE nie
*                      mehr ausgewertet werden. Der Fehler aeusserte sich,
*                      indem bei jedem Drucken die Fehlemeldung "Seite
*                      nicht vorhanden" kam.
*     16.03.98 -TSchw- PRINT_HANDLE von QNX2 uebernommen
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

#ifndef _print
#define _print

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
#include <disk.h>
#ifndef _dstruct
#include <dstruct.h>
#define _dstruct
#endif
/*.EI.***********************************************************************/

#define PRINT_NO_PAGE      0xfff      /* keine Seite drucken */

/* Struktur fuer den wahlweisen Ausdruck auf Drucker bzw. Floppydatei      */
#define PRINT_ERROR   0
#define PRINT_PRINTER 1
#define PRINT_FILE    2
typedef struct {
  UWORD dest;              /* PRINT_PRINTER/FILE, von PrintOpen gesetzt    */
  IQT_HANDLE prnhnd;       /* PrintHandle fuer Drucker                     */
  WRITE_FILE_INFO finfo;   /* "Handle"-Struktur fuer Dateiausgabe          */
  char text_lf[10];        /* Zeilenvorschubstring fuer Datei              */
  char ff[10];             /* Seitenvorschubstring fuer Datei              */
} PRINT_HANDLE;

#endif /* ifndef _print */




