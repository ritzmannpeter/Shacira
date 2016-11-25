/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVKBD.H
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
*     AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     01.04.92 -TS-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     01.02.93 -MBa-   KFC_HARDCOPY eingefuegt
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

#ifndef _devkbd
#define _devkbd

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
#ifndef _iqkbdkey
#include <iqkbdkey.h>      /* IQT Tastaturcodes */
#define _iqkbdkey
#endif
/*.EI.***********************************************************************/


/*********************************************************************
*  IN IQTDEV.H NACHZUTRAGENDE SPEZIALITAETEN (VORLAEUFIG)
*********************************************************************/

/*********************************************************************
*  KBD-Treiber: KONSTANTEN UND ALLGEMEINE MAKROS
*********************************************************************/

#define InFilter(f,k)  ( *((BYTE*)(f)+(((k)&0xff)>>3)) & 1<<((k)&0x07) )


/*********************************************************************
*  KBD-Treiber: DATENTYPEN
*********************************************************************/

typedef BYTE FILTER [32];

typedef struct {
   FILTER * Filter;
   IQT_HANDLE EchoWindow;
   int BufSize;
} KBD_PARAM_BLOCK;

typedef struct {
   char dummy;
} KBD_INIT_BLOCK;

/*********************************************************************
*   KBD-Treiber: KONTROLLCODES
*********************************************************************/

#define KBD_CTRL_LAMP_ON   1
#define KBD_CTRL_LAMP_OFF  2

/*********************************************************************
*   KBD-Treiber: SCHNITTSTELLENPARAMETER
*********************************************************************/

#define KBD_ID_FILTER 0
#define KBD_CTRL_LOCK   1
#define KBD_CTRL_UNLOCK 2

/*********************************************************************
*   KBD-Treiber: FEHLERCODES
*********************************************************************/

#define KBD_ERR_NO_ACCESS 1

#define ERR_DEVKBD_MEMORY_ALLOC_DEVKBD    2
#define ERR_DEVKBD_MEMORY_ALLOC_DEVKBDAT  3
#define ERR_DEVKBD_MEMORY_LINK_DEVKBD     4
#define ERR_DEVKBD_MEMORY_LINK_DEVKBDAT   5

/*********************************************************************
*   KBD-Treiber: FEHLERCODES FUER DIAGNOSE-MELDUNGEN
*********************************************************************/

#define DM_KBD_INITTAST  1L
#define DM_KBD_RKEYREA   2L
#define DM_KBD_RPORTR   13L
#define DM_KBD_RPORTW   14L

/*********************************************************************
*  MODULINTERNE KONSTANTEN
*********************************************************************/

#define MAX_FIFOSIZE 48    /* Maximale Grae des Tastaturpuffers */

#define KBDH_NOERROR    0  /* Rckmeldung bei fehlerfreiem Arbeiten        */
#define KBDH_ERROR      1  /* Fehlerrckmeldung                            */
#define KBDH_PUTKEY     2  /* Tastencode (wparam) in Puffer schreiben      */
#define KBDH_GETKEY     3  /* Tastencode (wparam) aus Puffer lesen, warten */
#define KBDH_KEYPRESSED 4  /* Nchster Tastencode (wparam) oder 0          */
#define KBDH_CLEARBUF   5  /* Type-ahead-Puffer lschen                    */
#define KBDH_SHOWBUF    6  /* Aktuellen Stand des Type-ahead-Puffers anz.  */
#define KBDH_SETFILTER  7  /* Zeiger auf Filter (lparam) als akt. setzen   */
#define KBDH_LOGIN      8  /* Neue Inst: EchoWnd(wparam), BufSize(lparam)  */
#define KBDH_LOGOFF     9  /* Instanz verlassen                            */

/* LOGIN liefert in wparam ein Handle zurck, das Instanz-Kennung dient    */
/* GETKEY,KEYPRESSED,CLEARBUF,SETFILTER,LOGOFF erhalten in wparam das Hnd  */

#define MAX_INSTANCES  8   /* Maximale Anzahl Handles fr KbdHandler       */

#endif

