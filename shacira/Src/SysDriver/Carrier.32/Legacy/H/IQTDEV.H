/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IQTDEV.H - Verwaltung der Geraetetreiber
*
*  BESCHREIBUNG:
*     Modulschnittstelle von IQTDEV.C.
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   30.03.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*     AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*
*  HISTORY:
*     01.04.92 -SF-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     14.07.92 -TS-    Neues Fehlerkonzept
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*     DevInit - Geraet einmalig initialisieren
*     DevOpen - Handle fuer ein Geraet ermitteln
*     DevClose - Handle fuer ein Geraet wieder freigeben
*     DevRead - String von einem Geraet lesen
*     DevWrite - String auf einem Geraet ausgeben
*     DevControl - Steuerfunktionen ausloessen
*     DevExamine - Zeichenvorausschau
*     DevSetParam - Geraeteparameter einstellen
*     DevGetParam - Geraeteparameter ermitteln
*
*  DATENTYPEN:
*     HANDLE -
*     PARAMETER -
*     MODUL_TYP - Funktionstabelle zu Subfunktionen (nur bei IQTDEV_MAIN)
*     MODUL_PTR - Zeiger auf MODUL_TYP (nur bei IQTDEV_MAIN)
*     FUNC_INT_PTR - Zeiger auf Funktion (nur bei IQTDEV_MAIN)
*
*
*.EH.***********************************************************************/

#ifndef _iqtdev
#define _iqtdev

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _stdarg
#include <stdarg.h>
#define _stdarg
#endif
#ifndef _iqttsk
#include <iqttsk.h>
#define _iqttsk
#endif
/*.EI.***********************************************************************/

/*********************************************************************
*  Allgemein: DEKLARATION DER HAUPTFUNKTIONEN   
*********************************************************************/

typedef int USR_HANDLE;
typedef unsigned long PARAMETER;

GLOBAL int DevInit(int devnr, void * initblock);
GLOBAL int DevOpen(USR_HANDLE * hnd, int devnr, void * paramblock);
GLOBAL int DevClose(USR_HANDLE hnd);
GLOBAL int DevRead(USR_HANDLE hnd, char * buf, int buflen, int * actlen, unsigned long tmo);
GLOBAL int DevWrite(USR_HANDLE hnd, char * buf, int buflen, int * actlen, unsigned long tmo);
GLOBAL int DevControl(USR_HANDLE hnd, int cntrl, PARAMETER param);  
GLOBAL int DevExamine(USR_HANDLE hnd, char * byte, unsigned long tmo);
GLOBAL int DevSetParam(USR_HANDLE hnd, int id, PARAMETER param);
GLOBAL int DevGetParam(USR_HANDLE hnd, int id, PARAMETER  * param);
GLOBAL int DevPrintf(USR_HANDLE hnd, char * fmtstr, ...);
GLOBAL int XDevPrintf(USR_HANDLE hnd, char * fmtstr, va_list args);

/*********************************************************************
*  Allgemein: GERAETENUMMERN   
*********************************************************************/
#define DEV_MAIN -1
#define DEV_KBD   0
#define DEV_CRT   1
#define DEV_HOST  2
#define DEV_ISCOS 3
#define DEV_DISK  4
#define DEV_PRN   5
#define DEV_RTC   6
#define DEV_COM   7
#define DEV_PORT  8
#define DEV_ROB   9
#define DEV_CEN   10 /* centronics */ 
#define DEV_MEASURE 11
#define DEV_STD_MEASURE 12

/*********************************************************************
*  Allgemein: HYPER-HANDLES FUER STEUERFUNKTIONEN
*********************************************************************/
#define DEV_KBD_HND   1
#define DEV_CRT_HND   2
#define DEV_HOST_HND  3
#define DEV_ISCOS_HND 4
#define DEV_DISK_HND  5
#define DEV_PRN_HND   6
#define DEV_RTC_HND   7
#define DEV_COM_HND   8
#define DEV_PORT_HND  9
#define DEV_ROB_HND  10
#define DEV_CEN_HND  11 /* centronics */ 
#define DEV_MEAS_HND 12
#define DEV_STD_MEAS_HND 13

/*********************************************************************
*  Allgemein: VERSCHIEDENE KONSTANTEN
*********************************************************************/
#define TIMEOUT_WAIT  -1     /* Timeout-Parameter */
#define TIMEOUT_READY  0

/*********************************************************************
*  Allgemein: KONTROLLCODES
*********************************************************************/
#define DEV_CTRL_NEWLINE  -1
#define DEV_CTRL_NEWPAGE  -2
#define DEV_CTRL_FLUSH    -3

/*********************************************************************
*  Allgemein: SCHNITTSTELLENPARAMETER  
*********************************************************************/
#define DEV_ID_ERROR      -1
#define DEV_ID_TERMINATOR -2

/*********************************************************************
*  Intern: DATENTYPEN DER SCHNITTSTELLE ZU DEN SUBMODULEN   
*********************************************************************/
   typedef int ( * FUNC_INT_PTR)();
   typedef struct {
      FUNC_INT_PTR Init,Open,Close,Read,Write,Control,
                   Examine,SetParam,GetParam;
   } MODULE_TYP, * MODULE_PTR;   
   
#define CLOSE_NOT_DONE  0     /* done-Konstanten bei Close */
#define CLOSE_DONE      1

#define DEV_ERROR       1

#endif   /*ifndef _iqtdev*/
