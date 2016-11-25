/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     CLB.H
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
*     20.01.98 -TSchw- CLB_GetBuf1 mit neuen Parametern user und mark, sowie
*                      Konstanten CLB_USER1 - CLB_USER_NONE definiert fuer
*                      diese Parameter.
*                      Struktur CLB_BUF1 um Parameter Date erweitert.
*     12.02.01 -TSchw- CLBFastHook, CLBSlowHook, WriteCLBFileIqtKey sowie 
*                      CLB_SPSKEY eingefügt (siehe CLB2001).
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

#ifndef _clb
#define _clb

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <register.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Typen fuer Crashlogbuch
****************************************************************************/

/* Struktur fuer CLBGetBuf1 */
 typedef struct clb_buf1 {
   PARAMETER   Time;       /* Uhrzeit */
   PARAMETER   Date;       /* Datum */
   ELEMENT     *EP;        /* Adresse des Elements */
   long        VarNr;      /* Variablen-Nr. */
   union {
      long     Val;        /* neuer Wert des Registers */
      char     Txt[16];    /* neuer Text */
   } New;
   union {
      long     Val;        /* alter Wert des Registers */
      char     Txt[16];    /* neuer Text */
   } Old;
   BYTE        Station;    /* Stations-Nr. */
   BYTE        Aggregat;   /* Aggregat-Nr. */
   } CLB_BUF1;

/* Alle moeglichen Aufnahmetypen des Ringspeichers */
#define  CLB_REGSOLL       0
#define  CLB_REGIST        1
#define  CLB_START_ERR     2
#define  CLB_STOP_ERR      3
#define  CLB_ACTKEY        4
#define  CLB_TIMEDATE      5
#define  CLB_BITSOLL       6
#define  CLB_BITARRAY      7
#define  CLB_TEXTVAR       8
#define  CLB_SPSKEY        9  /* CLB2001 */

#define  CLB_USER1         0x80
#define  CLB_USER2         0x40
#define  CLB_USER3         0x20
#define  CLB_USER4         0x10
#define  CLB_USER_NONE     0x00

GLOBAL int CLBInit (BOOL init_bbram);
GLOBAL void CLBInsert (BYTE Id , long Newval , long Oldval , ELEMENT * EP);
GLOBAL int CLBGetBuf1 (CLB_BUF1 * Param , int Nr, UWORD user, UWORD mark);
GLOBAL void * CLBGetNextLine (int BufNr , int Nr);
GLOBAL void CLBFastHook ();               /* CLB2001 */
GLOBAL void CLBSlowHook ();               /* CLB2001 */
GLOBAL void WriteCLBFileIqtKey (int key); /* CLB2001 */

#endif /* ifndef _clb */




