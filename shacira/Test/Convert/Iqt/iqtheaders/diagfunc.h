/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DIAGFUNC.H
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
*     VERSION:    1.0                       DATUM:   15.06.92
*     AUTOR(EN):  -MBa-  M. Bauernfeind     TELEFON: (07644) 78381
*
*  HISTORY:
*     15.06.92 -MBa-   Einfuehrung der Header-Datei
*     17.07.92 -PR-    PrintStringLf mit uebernommen
*               13-09-96 -PR-    Definition der Diagnosefehlermeldungen geaendert.
*     11.03.98 -TSchw- DIAG_ERR_FILE_NOT_READY eingefuegt.
*
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*   PrintStringLf -  gibt einen String auf HCrtDiagOut aus
*   PrintString -  gibt einen String auf HCrtDiagOut aus
*   WaitForKey  -  warten auf einen Tastendruck
*   WriteError  -  Gibt eine Diagnose- oder ISCOS-Fehlermeldung mit der
*                  Fehlernummer 'error' im Fenster 'hCrt' aus.
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _diagfunc
#define _diagfunc

/*.SI.***********************************************************************/
#include <stddef.h>
#include <syntax.h>
#include <iqttsk.h>
#include <iqtdev.h>
#include <devkbd.h>
#include <sunichar.h>
/*.EI.***********************************************************************/

/* Diagnose-Mode Message-Id's
 */
#define START_DIAGNOSE 0x00

/* Diagnose-Mode Mode !?
 */
#define DIAG_MODE_KEYPOS 0x0000
#define DIAG_MODE_DIRECT 0x0001

/* Zeichen zur Darstellung eines Eingabecursors */
#define CURSOR_CHAR "_"

/* Maximale Laenge einer Eingabezeile */
#define MAX_LINELEN 79

/* Groesse des Ausgabefensters in Zeilen */
#define MAX_LINES 21 /* Maximale Zeilenanzahl fuer's Ausgabefenster */

/* Groesse des ISCOS-Kommunikationspuffers */
#define MAX_DBLKLEN 256

/* Anzahl Wiederholungsversuche fuer MsgRequest */
#define MAX_RETRIES 3

/* Interne Fehlermeldungen */
#define DIAG_NO_ERROR 0                 
#define DIAG_ERR_SYNTAX 10    /* Syntaxfehler */
#define DIAG_ERR_RANGE 11     /* Wert ausserhalb des zulaessigen Bereiches */
#define DIAG_ERR_PARAM 12     /* Fehlerhafte Anzahl Parameter */
#define DIAG_ERR_CMD 13       /* Fehlerhaftes Kommando, CmdBlock ausgefuellt */
#define DIAG_ERR_MEMORY 14    /* Speicher voll */
#define DIAG_ERR_UNIMPL 15    /* Funktion (noch) nicht implementiert */
#define DIAG_ERR_NOREG 16     /* Register nicht vorhanden */
#define DIAG_ERR_NOPRN 17     /* Drucker nicht betriebsbereit */
#define DIAG_ERR_TIMEOUT 18   /* Timeoutfehler (vgl. DEV_ERR_TIMEOUT) */
#define DIAG_ERR_INITMODE 19  /* Nur im InitMode verfuegbar */
#define DIAG_ERR_NO_EXTENSION 20 /* Nur im erweiterten Modus verfuegbar */
#define DIAG_ERR_NO_DIAGMSG 21 /* diagmsg konnte nicht gestartet werden */
#define DIAG_ERR_UNKNOWN_SYMBOL 22 /* Symbol unbekannt */
#define DIAG_ERR_NO_SPS_SUPPORT 23 /* Befehl auf der SPS nicht moeglich */
#define DIAG_ERR_BAD_EXIT_STATUS 24 /* Systembefehl liefert exit status != 0 */
#define DIAG_ERR_FILE_NOT_READY 25 /* Fehler beim Oeffnen der Datei */
#define DIAG_EXIT -1        /* Diagnosemode verlassen */

/* Timeout-Zeit fuer ISCOS-Kommunikation */
#define TIMEOUT     TIME_SET(TIME_TICK,4)  /* Timeout fuer normale Befehle */
#define TMO_SE      TIME_SET(TIME_TICK,4)   /* Timeout fuer SE-Befehl */
#define TMO_REQ     TIME_SET(TIME_TICK,4)   /* Timeout fuer MsgRequest */
#define TMO_PRN_ON  TIME_SET(TIME_SECS,15)   /* Wartezeit fuer Drucker Ein */
#define TMO_PRN_WR  TIME_SET(TIME_SECS,30)   /* Wartezeit fuer Druckerausgabe */

extern const FILTER filter;

GLOBAL void PrintStringLf     ( char    *str, int *lines, int swap );
GLOBAL void PrintStringLf_Uni ( UNICHAR *str, int *lines, int swap );
GLOBAL void PrintString       ( char    *str, int len, int *lines, int swap);
GLOBAL void PrintString_Uni   ( UNICHAR *str, int len, int *lines, int swap);
GLOBAL int WaitForKey (void);
GLOBAL void WriteError (IQT_HANDLE hCrt , int error);

#endif /* ifndef _diagnose */
