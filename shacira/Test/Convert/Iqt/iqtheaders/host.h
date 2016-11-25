/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     HOST.H
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
*     VERSION:    3.2                       DATUM:   07.06.95
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     29.08.91 -SF-     Neu-Implementierung (alles alte wurde entfernt)
*     17.10.91 -SF-     HOST_FMT eingebaut
*     05.11.91 -TSchw-  HOST_HEATERR_ eingebaut
*     19.12.91 -SF-     OPT in Kontrollwort aufgenommen
*     16.02.95 -TSchw-  Control-Parameter um den Eintrag AGG erweitert.
*                       In diesen 2 Bit wird codiert, ob die entsprechende
*                       Hostvariable mit dem AGGREGAT-Register indiziert
*                       ist und wenn ja, an welcher Position. Ist hier ein
*                       Index angegeben, so wird der entsprechende Index in
*                       der vom Leitrechner uebertragenen Variable bei den
*                       Dunkeltastungs-, Plausibilitaets- und Userfunktionen
*                       anstelle des AGGREGAT-Registers verwendet.
*     07.06.95 -PR-     Aus IQT 350 - Software nachintegriert
*     11.12.98 -TSchw-  HT_SetAGGREGAT, CheckOpt exportiert.
*     20.11.99 -TSchw-  GetHostEntryByVarNr eingefuegt.
*                       HostValToString eingefuegt.
*     28.01.99 -TSchw-  IUGetOperatingStatus, Host_BufDD, Host_BufUD global
*                       gemacht.
*     20.03.03 -HA-     HOSTPROTSlowHook eingefuegt (siehe HOSTPROT)
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

#ifndef _host
#define _host

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
/*.EI.***********************************************************************/

/*********************************************************************
X
X STRUKTUREN (fuer Host-Tabelle in Datenstruktur)
X
*********************************************************************/

#define HOST_NAME_SIZE     7     /* 6 Zeichen + Ascii-0 */
typedef struct host_tab_type {
   char  Name[HOST_NAME_SIZE];   /* Name der Variable */
   UWORD  RegNr;                  /* Registernummer */
   UWORD  Ctrl;                   /* Controlwort (siehe weiter unten) */
   BYTE  DimSize[3];               /* Groesse der Tabelle */
   void * Tab;                   /* verschiedene Tabellen */
   } HOST_TAB_TYPE;

typedef struct host_tab_type_1 {
   long  VarNr;                  /* Bildschirmbezogene Variablennummer */
   } HOST_TAB_TYPE_1;

typedef struct host_tab_type_2 {
   long  VarNr;                  /* Bildschirmbezogene Variablennummer */
   UWORD  RegNr;                  /* Register-Nummer */
   } HOST_TAB_TYPE_2;

typedef struct host_tab_type_3 {
   long  VarNr;                  /* Bildschirmbezogene Variablennummer */
   UWORD  RegNr;                  /* Multiplex-Register */
   } HOST_TAB_TYPE_3;


/*********************************************************************
X
X KONSTANTEN
X
*********************************************************************/

/* Statt der Variablen-Nr. wird direkt ein Format angegeben.
   Das HOST-Modul erkennt dies an den gesetzten Bits des HIGH-Word. */
#define HOST_FMT(w,p)    (((long)SET_FORMAT(w,p)) | 0xffff0000L)
#define HOST_TST_FMT(f)  (((f & 0xffff0000L) == 0xffff0000L) ? TRUE : FALSE)
#define HOST_GET_FMT(f)  ((FORMAT)(f & 0x0000ffffL))

/* Konstanten fuer Funktion HostHeatError, Parameter ErrType: */
#define HOST_HEATERR_KLEMM       10
#define HOST_HEATERR_SENSOR      11
#define HOST_HEATERR_TOL_NARROW  12
#define HOST_HEATERR_TOL_WIDE    13


/*********************************************************************
X
X FUNKTIONEN
X
*********************************************************************/

/* Diese Funktionen sind schon in FUNCTION.H deklariert
 void HostInitBBRam     ( );
 void HostStartError    ( UWORD Index );
 void HostStopError     ( UWORD Index );
 void HostHeatError     ( BOOL StartFlag, UWORD ErrIndex, int ErrType, 
                          int Group, int Zone, int Func );
 void WriteHostBuffer   ( );
*/

/*********************************************************************
X  AUFBAU DES CONTROL-PARAMETERS CTRL:
*
*  Bit:   15 14  13 12  11 10 09 08  07  06   05   04   03  02 01 00
*  Feld:  -----  AGG    OPT      MSG UDL IND3 Ind2 Ind1 TAB
*
*  BEDEUTUNG:
*     TAB (6 Bit) - Format der Registertabellen
*     IND (1 Bit) - Index-Information 
*     UDL (1 Bit) - Up-/Download
*     MSG (1 Bit) - Host-Meldung
*     OPT (3 Bit) - Optionen beruecksichtigen
*     AGG (2 Bit) - Position des Aggregatindex (1-3, 0 = kein Index)
*     
*
*  ZUGRIFFSMACROS:
*     GET_TABTYPE ( ctrl ) - Format der Registertabellen isolieren
*     GET_OFFSET (I, ctrl ) - Index-Information isolieren
*     GET_UDLTYPE ( ctrl ) - Up-/Download isolieren
*     GET_MSGTYPE ( ctrl ) - Host-Meldung isolieren
*     GET_OPTTYPE ( ctrl ) - Optionen isolieren
*     GET_AGGIND  ( ctrl ) - Aggregatindex isolieren
*
*********************************************************************/
/*********************************************************************
X  BITMASKEN FUER CTRL
*********************************************************************/

/* ---- Gruppe TAB: Format der Register-Tabellen */
#define TAB_NORMAL     0x0000  /* Normales Register (Kein Host-Index)        */
#define TAB_VAR        0x0001  /* Variablen-Nr. in separater Tabelle         */
#define TAB_VAR_REG    0x0002  /* Variablen-Nr. und Reg-Nr. in sep. Tabelle  */
#define TAB_VAR_MULT   0x0003  /* Variablen-Nr. und Multiplex-Reg. in sep. T.*/
#define TAB_TEXTVAR    0x0004  /* Textvariable                               */
#define TAB_GRAPHIC    0x0005  /* Prozessgrafikdaten                         */
#define TAB_STATLINE   0x0006  /* Blau-Weisser Balken                        */

/* ---- Gruppe IND: Index-Information */
#define OFFS_0        0x0000  /* Index beginnt bei 0                       */
#define OFFS1_1       0x0010  /* Index 1 beginnt bei 1                     */
#define OFFS2_1       0x0020  /* Index 2 beginnt bei 1                     */
#define OFFS3_1       0x0040  /* Index 3 beginnt bei 1                     */

/* ---- Gruppe UDL: Up/Download */
#define UDL_NONE       0x0000  /* Kein Up-/Download                          */
#define UDL_UD_DD      0x0080  /* Register gehoeren zum Up-/Download-Satz    */

/* ---- Gruppe MSG: Host-Meldung */
#define MSG_NONE       0x0000  /* Normale Variable                           */
#define MSG_SEND       0x0100  /* Meldung wurde an IQT gesendet              */

/* ---- Gruppe OPT: Optionen */
#define OPT_NONE       0x0000  /* Normale Variable                           */
#define OPT_PG         0x0200  /* nur bei Option Prozessgrafik               */
#define OPT_SPC        0x0400  /* nur bei Option SPC                         */
#define OPT_ROB        0x0600  /* nur bei Option Roboter                     */
#define OPT_PROG_CORES 0x0800  /* nur bei Option frei progr.bare Kernzuege   */

/* ---- Gruppe AGG: Aggregatindex */
#define AGG_NONE       0x0000  /* Variable ist nicht aggregatindiziert       */
#define AGG_1          0x1000  /* 1. Index ist AGGREGAT                      */
#define AGG_2          0x2000  /* 2. Index ist AGGREGAT                      */
#define AGG_3          0x3000  /* 3. Index ist AGGREGAT                      */


#define GET_TABTYPE(R)      ( (R) & 0x000f )
#define GET_OFFSET(I,R)     ( ((R) & (OFFS1_1<<(I-1)) ) >> (I+3) )
#define GET_UDLTYPE(R)      ( (R) & 0x0080 )
#define GET_MSGTYPE(R)      ( (R) & 0x0100 )
#define GET_OPTTYPE(R)      ( (R) & 0x0e00 )
#define GET_AGGIND(R)       ( (R) & 0x3000 )

/****************************************************************************
X  Id's fuer Host_SetParam()
****************************************************************************/
#define HOST_ID_UP_DOWN         0

/****************************************************************************
X  Funktionen
****************************************************************************/
GLOBAL int Host_Init(BOOL init_bbram);
GLOBAL int Host_Handler( void );
GLOBAL void Host_Error( BOOL start_flag, UWORD index );
GLOBAL void Host_HeatError( BOOL start_flag, UWORD err_ind, int err_type,
                            int group, int zone, int func );
GLOBAL void Host_WriteBuffer( void );
GLOBAL int Host_SetParam( int type, int param );
GLOBAL void HostStartError( UWORD Index );
GLOBAL void HostStopError( UWORD Index );

void HTSetAGGREGAT (UWORD Ctrl, int i1, int i2, int i3);
BOOL CheckOpt( UWORD ctrl );

GLOBAL int GetHostEntryByVarNr( long VarNr, char *name, UWORD *ctrl, 
                                UWORD *ind1, UWORD *ind2, UWORD *ind3,
                                HOST_TAB_TYPE **hp);
GLOBAL int HostValToString( char* buf, long val, int index1, 
                            FORMAT format, BYTE ctrl );
GLOBAL UWORD IUGetOperatingStatus( );

GLOBAL int Host_BufDD (char *buf, int buflen);
GLOBAL int Host_BufUD (char **buf, int *buflen);

GLOBAL void HOSTPROTSlowHook (); /* HOSTPROT */

#endif                                 /* _host */

