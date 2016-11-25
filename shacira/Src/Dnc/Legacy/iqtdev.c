/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     IQTDEV.C   - Verwaltung der Geraetetreiber
*
*  BESCHREIBUNG:
*     Allgemeine Verwaltungsschicht zur Verwaltung der verschiedenen
*     Geraetetreiber. Enthaelt die Auswahl der spezifischen Module
*     und die allgemeine Fehlerbehandlung.
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
*                 -MBa-  M.Bauernfeind               (07644) 78381
*/    const char Vers_IQTDEV[]   = "@(#)IQTDEV   4.0 30.03.92";/*
*
*  HISTORY:
*     30.03.92 -SF-    Portierung des IQT-350 auf IQT-450
*     15.04.92 -TS-    Ergaenzt um Centronics Treiber DEVCEN
*     14.05.92 -PR-     Umstellung Include-Mechanismus
*     10.06.92 -MBa-   RtcModule implementiert
*     22.06.92 -PR-    Start von comsrv nach InitCom verlagert
*     23.06.92 -TS-    PortModule eingefuegt
*     16.07.92 -PR-    Vermisstes DevPrintf wieder implementiert
*     13.10.92 -SF-    Bei Fehler und PROTO_DEVNR das Devicekuerzel
*                      protokollieren
*     15.10.92 -PR-    Testausgaben entfernt und Protokollierung des
*                      Fehlerkuerzels etwas veraendert
*     14.06.93 -PR-    Verwendung eines temporaeren Handles in DevOpen.
*     06.07.95 -PR-    DevPrintf verbessert.
*                      
*
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*     Siehe Modulkopf von IQTDEV.H
*
*.EM.***********************************************************************/


/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _string
#include <string.h>
#define _string
#endif
#ifndef _stdio
#include <stdio.h>
#define _stdio
#endif
#ifndef _stdlib
#include <stdlib.h>
#define _stdlib
#endif
#ifndef _stddef
#include <stddef.h>
#define _stddef
#endif
#ifndef _stdarg
#include <stdarg.h>
#define _stdarg
#endif
#ifndef _errcode
#include <errcode.h>
#define _errcode
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
#ifndef _devdisk
#include <devdisk.h>
#define _devdisk
#endif
#ifndef _diskxy
#include <diskxy.h>
#define _diskxy
#endif
/*.EI.***********************************************************************/


/*********************************************************************
X  MODULINTERNE KONSTANTEN
*********************************************************************/
/* Definition des Intervalls in dem die Handles vergeben werden: */
#define FIRSTUSR_HANDLE   1       /* erstes Handle ueberhaupt */

#define MAXUSR_HANDLES    200     /* @@@ Zahl der folgenden freien Handles */

/*********************************************************************
X  IMPEMENTIERUNG DES DIAGNOSELOGBUCHS IN DER TREIBERSCHICHT
*
*  Grundsaetzlich kann jeder Treiber frei entscheiden, welche Diagnose-
*  meldungen er benutzt und vor allem wie der Zusatzparameter (USR_LONG)
*  belegt wird. Um eine konsistente Behandlung innerhalb der Treiber-
*  schicht zu erreichen wird empfohlen, sich an die folgenden Normen
*  zu halten:
*
*  Diagnosemeldungen - es werden nur die in IQTTSK.H definierten Kon-
*     stanten DM_IQTDEV bzw. DM_DEVxxx benutzt (xxx entsprechend dem
*     jeweiligen Modul, bei Bedarf neu zu definieren).
*
*  Zusatzparamter - im USR_LONG-Wert werden drei Informationen kodiert:
*
*     Bits 31..24 -- Kennung der Funktion die den Fehler meldet. Die
*        Kennungen 0..8 sind dabei immer die Hauptfunktionen xxxInit,
*        xxxOpen, usw. (vgl. Definition in DEVCRT.H). Dies fuer den
*        Fall, dass die Steuerschicht in IQTDEV einmal bei jedem
*        Fehler fuer jedes Modul automatisch einen DiagnoseEingtrag
*        vornimmt. Die Nummern bis 15 sind noch reserviert und ab
*        16 koennen modulspezifische Funktionskennungen vergeben werden.
*
*     Bits 23..16 -- auf ein USR_BYTE reduzierte Nummer des Handles, das
*        von dem Fehler betroffen ist.
*
*     Bits 15..0 -- frei verfuegbar. Falls mehrere Fehlerquellen in
*        einer Funktion vorhanden sind sollten diese durchnummeriert
*        und die laufende Fehlernummer hier eingetragen werden.
*
*  Das Modul DEVCRT unterstuetzt Diagnosemeldungen und kann anderen
*  Modulen in dieser Hinsicht als Vorlage dienen.
*
*********************************************************************/

/*********************************************************************
X  Dummy-Funktionen fuer nicht vorhandene Schnittstellen.
*********************************************************************/
 extern const MODULE_TYP DumModule;
 LOCAL int DumInit( void* initblock )
   { return USR_NO_ERROR; }
 LOCAL int DumOpen( USR_HANDLE hnd, void* param, void** wcb, MODULE_PTR* modul )
   { *modul = (MODULE_PTR)&DumModule; return USR_NO_ERROR; }
 LOCAL int DumClose( void* wcb, int* done )
   { return USR_NO_ERROR; }
 LOCAL int DumRead( void* wcb, char* buf, int buflen, int* aktlen, TIME tmo )
   { return USR_NO_ERROR; }
 LOCAL int DumWrite( void* wcb, char* buf, int buflen, int* aktlen, TIME tmo )
   { return USR_NO_ERROR; }
 LOCAL int DumControl( void* wcb, int cntrl, PARAMETER param )
   { return USR_NO_ERROR; }
 LOCAL int DumExamine( void* wcb, char* byte, TIME tmo )
   { return USR_NO_ERROR; }
 LOCAL int DumSetParam( void* wcb, int id, PARAMETER param )
   { return USR_NO_ERROR; }
 LOCAL int DumGetParam( void* wcb, int id, PARAMETER* param )
   { *param=1L; return USR_NO_ERROR; }

GLOBAL const MODULE_TYP DumModule = {
   DumInit,
   DumOpen,
   DumClose,
   DumRead,
   DumWrite,
   DumControl,
   DumExamine,
   DumSetParam,
   DumGetParam};

/*********************************************************************
X  SCHNITTSTELLE ZU DEN UNTERMODULEN
*
*  Die Geraetenummern sind die Indizes fuer die Tabelle DevModul[]:
*
*        0 <= DEV_XXX < MODULE_COUNT
*
*  Analog dazu sind die Hyper-Handles in folgendem Bereich definiert:
*
*        FIRSTUSR_HANDLE <= DEV_XXX_HND < FIRSTUSR_HANDLE + MODULE_COUNT
*
*  Hyper-Handles sind nur bei den Funktionen DevControl, DevSetParam
*  und DevGetParam moeglich
*
*********************************************************************/
/* Deklaration der Untermoduladressen: */
#define MODULE_COUNT 13

#define CrtModule DumModule
#define KbdModule DumModule
#define IscosModule DumModule
#define RtcModule DumModule
#define PrnModule DumModule
#define HostModule DumModule
#define PortModule DumModule
#define RobModule DumModule
#define ComModule DumModule
#define MeasModule DumModule
#define StdMeasModule DumModule

extern const MODULE_TYP CrtModule,KbdModule,IscosModule,RtcModule,
                  PrnModule,ComModule,DiskModule,HostModule,
                  PortModule,RobModule,ComModule,MeasModule,StdMeasModule;

LOCAL const MODULE_PTR DevModul[] = {
   &KbdModule,          /* KBD: Tastatur */
   &CrtModule,          /* CRT: Bildschirm */
   &HostModule,         /* HOST: Hostschnittstelle */
   &IscosModule,        /* ISCOS: ISCOS-Schnittstelle */
   &DiskModule,         /* DISK: Datentraeger */
   &PrnModule,          /* PRN: Drucker */
   &RtcModule,          /* RTC: Real Time Clock */
   &ComModule,          /* COM: Communication Driver */
   &PortModule,         /* PORT: Port auf Tastaturkarte */
   &RobModule,          /* ROB: Roboter */
   &ComModule,          /* CEN: Centronics */
   &MeasModule,         /* MEAS: Messwerterfassung */
   &StdMeasModule       /* STDMEAS: Messwerterfassung Standard*/
 };

/* Geraetetreiber bereits fehlerfrei initialisiert? */
 LOCAL USR_BYTE DevInitDone[MODULE_COUNT];


/*********************************************************************
X  USR_HANDLEORGANISATION
*
*  Handles sind Indizes fuer einen Vektor mit Zeigern auf ein
*  Struct mit den Adressen der einzelnen Funktionen eines Moduls.
*  Weitere Vektoren die mit dem gleichen Index angesprochen werden
*  enthalten einen Zeiger auf einen untermodulspezifischen Parameter-
*  bereich, Flags ob das Handle noch frei ist und die Nummer des
*  jeweils zuletzt aufgetretenen Fehlers.
*
*  MAXUSR_HANDLES legt zusammen mit MODULE_COUNT (fuer die Hyper-Handles)
*  die Laenge des Vektors fest und FIRSTUSR_HANDLE die Nummer des ersten
*  Elementes, damit die Zaehlung nicht mit Null beginnen muss 
*  (FISTUSR_HANDLE >= 1, da 0 eine Fehlermarkierung!).
*
*  HND_BAD( hnd ) - Ueberprueft ob ein Handle im erlaubten Bereich
*     liegt und auch belegt ist. ACHTUNG: Dieses Macro veraendert
*     hnd so, dass es als direkter Index fuer die Handle-indizierten
*     Tabellen benutzt werden kann (Hyper-Handles werden NIE belegt,
*     erzeugen daher mit diesem Macro immer einen Fehler).
*
*  HND_HYPER( hnd ) - Ueberprueft ob es sich bei einem Handle um ein
*     sogenanntes Hyper-Handle fuer Steuerfunktionen handelt (hnd
*     bereits direkter Index, vgl. HND_BAD).
*
*  ERR( hnd,err ) - Setzt die Fehlernummer err fuer das Handle hnd,
*     falls diese nicht 0 ist. Liefert das Flag DEV_ERROR oder USR_NO_ERROR
*     zurueck (hnd bereits direkter Index, vgl. HND_BAD).
*
*********************************************************************/
/*
*  ACHTUNG!
*  Vor Benutzung dieses Macros stets obigen Kommentar durchlesen!
*  Danke! (Einer, der darauf hereingefallen ist)
*/
#define HND_BAD( h )    (  ((h)-=FIRSTUSR_HANDLE) < 0  || \
                           (h) >= (MAXUSR_HANDLES+MODULE_COUNT)  || \
                           !HndUsed[h])

#define HND_HYPER( h )    (  ((h) >= 0) && ((h) < MODULE_COUNT)  )

/* Handle benutzt? */
 LOCAL USR_BYTE HndUsed[MAXUSR_HANDLES + MODULE_COUNT];

/* Adressen der jeweiligen Untermodultreiber: */
 LOCAL MODULE_PTR HndModul[MAXUSR_HANDLES + MODULE_COUNT];

/* Adressen der jeweiligen untermodulspezifischen Parameterbloecke */
 LOCAL char* HndParam[MAXUSR_HANDLES + MODULE_COUNT];

/* letzter Fehlercode */
 LOCAL int HndErr[MAXUSR_HANDLES + MODULE_COUNT];

#define ERR( h,e ) ((e) ? (HndErr[h]= (e), DEV_ERROR) : (USR_NO_ERROR))
    
/*********************************************************************
*
*  FUNKTION: Init - Init der DLL
*
*  BESCHREIBUNG:
*     Wird vom DLL Manager dyna aufgerufen.
*
*  AUFRUF:
*     entfaellt
*
*********************************************************************/

void Init (int new_tid)
{
}

/*********************************************************************
X  INTERNES FEHLERMODUL
*
*  Dieses Modul wird ausgewaehlt, wenn ein Fehler bei DevOpen auf-
*  getreten ist. Es besteht aus einer Anzahl Dummy-Funktionen und
*  kann nur dazu verwendet werden, mit DevGetParam und DevSetParam
*  die allgemeine Fehlerbehandlung zu benutzen. Die einzige Funktion
*  die sonst nicht immer einen Fehler liefert ist DevClose.
*
*********************************************************************/
LOCAL int ErrNoError()
{
   return USR_NO_ERROR;
}

LOCAL int ErrNotAvailable()
{
   return ERR_NOT_AVAILABLE;
}

LOCAL int ErrBadId()
{
   return ERR_BAD_ID;
}

static /*const!!*/ MODULE_TYP ErrModule = {
   ErrNotAvailable,     /* ErrInit - wird nicht benoetigt */
   ErrNotAvailable,     /* ErrOpen - dito */
   ErrNoError,          /* ErrClose - meldet als einziges kein Fehler */
   ErrNotAvailable,     /* ErrRead - gibt keinen Sinn */
   ErrNotAvailable,     /* ErrWrite - dito */
   ErrNotAvailable,     /* ErrControl - dito */
   ErrNotAvailable,     /* ErrExamine - dito */
   ErrBadId,            /* ErrSetParam - keine weiteren Parameter */
   ErrBadId};           /* ErrGetParam - dito */


/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevInit - Geraet einmalig initialisieren
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevInit( devnr, initblock )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag (DEV_ERROR oder USR_NO_ERROR).
*     devnr IN [int] - Geraetetyp (DEV_MAIN initialisiert die zentrale
*                      Steuerschicht).
*     initblock IN [void*] - Initialisierungsparameter.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Die Funktion darf mit DEV_MAIN nur ein einziges Mal aufgerufen
*     werden. Die Initialisierungen der einzelnen Treiber koennen be-
*     liebig oft aufgerufen werden, sobald eine Initialisierung aber
*     einmal fehlerfrei mit USR_NO_ERROR beendet wurde, werden alle
*     weiteren Aufrufe ignoriert.
*
**.EF.***********************************************************************/

GLOBAL int DevInit(int devnr, void * initblock)
{  int ret;
   
   If (devnr == DEV_MAIN) Then
      int i;                           

      /* Steuerschicht initialisieren */
      For ( i=0; i<MAXUSR_HANDLES+MODULE_COUNT; i++) Do
         /* Alle Handles frei und ohne Fehler */
         HndUsed[i] = FALSE;
         HndErr[i] = USR_NO_ERROR;
      Endfor
      For ( i=0; i<MODULE_COUNT; i++) Do
         /* Den Hyper-Handles ihre Module zuordnen */
         HndModul[i] = DevModul[i]; 
         HndParam[i] = NULL;
         /* Ansonsten ist keiner der Treiber initialisiert */
         DevInitDone[i] = FALSE;
      Endfor
      return USR_NO_ERROR;
   Elseif (devnr < 0 || devnr >= MODULE_COUNT) Then
      return DEV_ERROR;                    /* Geraetetyp ist falsch */
   Elseif (DevInitDone[devnr]) Then
      return USR_NO_ERROR;                 /* bereits initialisiert */
   Else
      ret = (*DevModul[devnr]->Init)( initblock );
      If (ret) Then
         return DEV_ERROR;                 /* Initialisierungsfehler */
      Endif
      DevInitDone[devnr] = TRUE;       /* Initialisierung ok */
      return USR_NO_ERROR;
   Endif
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevOpen - Handle fuer ein Geraet ermitteln
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevOpen( hnd, devnr, paramblock )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag (DEV_ERROR oder USR_NO_ERROR).
*     hnd OUT [USR_HANDLE*] - Handlenummer.
*     devnr IN [int] - Geraetenummer.
*     paramblock IN [void*] - Geraetespezifischer Parameter.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Falls DEV_ERROR zurueckgemeldet wird, sind folgende Faelle moeglich:
*     *hnd == 0  -->  es sind keine freien Handles mehr verfuegbar
*     *hnd != 0  -->  das Geraet konnte geoeffnet werden und MUSS
*                     irgendwann auch wieder geschlossen werden. Hier
*                     sind intern zwei weitere Faelle moeglich:
*
*                     a) Trotz des Fehlers kann mit dem Geraet noch
*                        gearbeitet werden.
*                     b) Ein sinnvolles Arbeiten ist nicht moeglich,
*                        es wurde nur ein Dummy-Fehler-Geraet geoeffnet,
*                        das als weitere Operationen nur den Zugriff
*                        auf den Parameter DEV_ID_ERROR und DevClose
*                        erlaubt.
*
**.EF.***********************************************************************/
GLOBAL int DevOpen(USR_HANDLE * hnd, int devnr, void * paramblock)
{
   int err;
   USR_HANDLE handle;
   USR_HANDLE temp_handle;

   For (handle=MODULE_COUNT; handle<MAXUSR_HANDLES+MODULE_COUNT; handle++) Do
      If (!HndUsed[handle]) Then
         temp_handle = handle + FIRSTUSR_HANDLE;
         HndModul[handle] = NULL;

         If (devnr<0 || devnr>=MODULE_COUNT) Then
            err = ERR_ILLEGAL_DEVICE;
         Else
            If (DevModul[devnr]==NULL) Then
               err = ERR_ILLEGAL_DEVICE;
            Else
               err = (*DevModul[devnr]->Open)(temp_handle,paramblock,
                                     &HndParam[handle],&HndModul[handle]);
            Endif
         Endif
         /*
         ** Wenn die spezifische xxxOpen-Funktion als Modul-Zeiger NULL
         ** zurueckliefert ist kein sinnvolles weiterarbeiten moeglich,
         ** das Geraet wurde nicht geoeffnet und muss auch nicht mehr
         ** mit xxxClose geschlossen werden. In dem Fall wird das Dummy-
         ** Fehler-Modul von dieser Steuerschicht weiter verwendet.
         */
         If (err && HndModul[handle]==NULL) Then
            HndModul[handle] = (MODULE_PTR)&ErrModule;
         Endif
         err = ERR( handle,err );
         HndUsed[handle] = TRUE;
         *hnd = temp_handle;
         return err;
      Endif
   Endfor
   *hnd = 0;
   return DEV_ERROR;
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevClose - Handle fuer ein Geraet wieder freigeben
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevClose( hnd )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag (DEV_ERROR oder USR_NO_ERROR).
*     hnd IN [USR_HANDLE] - Handle.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Wenn ein Fehler aufgetreten ist kann in jedem Fall noch die
*     Fehlernummer mit DEV_ID_ERROR gelesen werden und es MUSS ein
*     weiteres DevClose gemacht werden (bis USR_NO_ERROR gemeldet wird).
*     Nach einem Fehler bei DevClose kann auch das Dummy-Fehler-Geraet
*     aktiv sein und keine weitere Funktion mehr verfuegbar sein.
*
**.EF.***********************************************************************/
GLOBAL int DevClose(USR_HANDLE hnd)
{
   int err;
   int done;
   
   If (HND_BAD(hnd)) Then
      return DEV_ERROR;
   Else
      If ((err = (*HndModul[hnd]->Close)(HndParam[hnd],&done)) == USR_NO_ERROR) Then
         HndUsed[hnd] = FALSE;
      Elseif ( done == CLOSE_DONE ) Then
         HndModul[hnd] = (MODULE_PTR)&ErrModule;
      Endif
   Endif
   return ERR(hnd,err);
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevRead - String von einem Geraet lesen
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevRead( hnd, buf, buflen, actlen, tmo )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     buf IN [void*] - Zeiger auf Datenpuffer.
*     buflen IN [int] - Groesse des Datenpuffers.
*     actlen OUT [int*] - Zahl der tatsaechlich gelesenen Zeichen.
*     tmo IN [TIME] - Timeout-Parameter.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Um den Aufruf zu vereinfachen sind zwei Sonderbehandlungen da:
*     buflen == 0  &&  buf != NULL  -->  als buflen wird die Laenge
*                                        des Strings ab buf benutzt.
*     aktlen == NULL  -->  es wird keine Laengenangabe zurueckgegeben
*                          und eine interne Dummy-Variable benutzt.
*
**.EF.***********************************************************************/
GLOBAL int DevRead(USR_HANDLE hnd, char * buf, int buflen, int * actlen, TIME tmo)
{
   int err;
   int dummylen;
   
   If (!buflen && buf !=NULL) Then buflen = strlen( buf ); Endif
   If (actlen == NULL) Then actlen = &dummylen; Endif
   
   If (HND_BAD(hnd)) Then
      return DEV_ERROR;
   Else
      err = (*HndModul[hnd]->Read)(HndParam[hnd],buf,buflen,actlen,tmo);
      return ERR(hnd,err);
   Endif
}

/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevWrite - String auf einem Geraet ausgeben
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevWrite( hnd, buf, buflen, actlen, tmo )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     buf IN [void*] - Zeiger auf Datenpuffer.
*     buflen IN [int] - Groesse des Datenpuffers.
*     actlen OUT [int*] - Zahl der tatsaechlich ausgegebenen Zeichen.
*     tmo IN [TIME] - Timeout-Parameter.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Um den Aufruf zu vereinfachen sind zwei Sonderbehandlungen da:
*     buflen == 0  &&  buf != NULL  -->  als buflen wird die Laenge
*                                        des Strings ab buf benutzt.
*     aktlen == NULL  -->  es wird keine Laengenangabe zurueckgegeben
*                          und eine interne Dummy-Variable benutzt.
*
**.EF.***********************************************************************/
GLOBAL int DevWrite(USR_HANDLE hnd, char * buf, int buflen, int * actlen, TIME tmo)
{
   int err;
   int dummylen;


   If (!buflen && buf != NULL) Then buflen = strlen( buf ); Endif
   If (actlen == NULL) Then actlen = &dummylen; Endif
   
   If (HND_BAD(hnd)) Then
      return DEV_ERROR;
   Else
      err = (*HndModul[hnd]->Write)(HndParam[hnd],buf,buflen,actlen,tmo);
      return ERR(hnd,err);
   Endif
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevControl - Steuerfunktion ausloessen
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevControl( hnd, cntrl, param )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     cntrl IN [int] - Kontrollbefehl
*     param IN [PARAMETER] - Zusatzparameter
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Diese Funktion kann auch mit einem Hyper-Handle aufgerufen
*     werden. In diesem Falle wird der untergeordnete Treiber mit
*     NULL als Zeiger fuer den spez. Parameterblock aufgerufen.
*
**.EF.***********************************************************************/
GLOBAL int DevControl(USR_HANDLE hnd, int cntrl, PARAMETER param)
{
   int err;
   
   If ( HND_BAD(hnd) && !HND_HYPER(hnd) ) Then
      return DEV_ERROR;
   Else
      err = (*HndModul[hnd]->Control)(HndParam[hnd],cntrl,param);
      return ERR(hnd,err);
   Endif
}


/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevExamine - Zeichenvorausschau
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevExamine( hnd, byte, tmo )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     byte OUT [char*] - naechstes Zeichen im Puffer.
*     tmo IN [TIME] - Timeout-Parameter.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     ...
*
**.EF.***********************************************************************/
GLOBAL int DevExamine(USR_HANDLE hnd, char * byte, TIME tmo)
{
   int err;
   
   If (HND_BAD(hnd)) Then
      return DEV_ERROR;
   Else
      err = (*HndModul[hnd]->Examine)(HndParam[hnd],byte,tmo);
      return ERR(hnd,err);
   Endif
}

/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevSetParam - Geraeteparameter einstellen
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevSetParam( hnd, id, param )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     id IN [int] - Parameterkennung.
*     param IN [PARAMETER] - zu setzender Parameterwert.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Diese Funktion kann auch mit einem Hyper-Handle aufgerufen
*     werden. In diesem Falle wird der untergeordnete Treiber mit
*     NULL als Zeiger fuer den spez. Parameterblock aufgerufen.
*     Der Parameter DEV_ID_ERROR wird bereits in dieser Steuerschicht
*     beruecksichtigt und nicht nach unten weitergegeben.
*
**.EF.***********************************************************************/
GLOBAL int DevSetParam(USR_HANDLE hnd, int id, PARAMETER param)
{
   int err;
   
   If (HND_BAD(hnd) && !HND_HYPER(hnd)) Then
      return DEV_ERROR;
   Elseif (id==DEV_ID_ERROR) Then
      If ((int)param == USR_NO_ERROR) Then
         HndErr[hnd] = USR_NO_ERROR;
         return USR_NO_ERROR;
      Else
         return ERR(hnd,ERR_BAD_PARAMETERS);
      Endif
   Else
      err = (*HndModul[hnd]->SetParam)(HndParam[hnd],id,param);
      return ERR(hnd,err);
   Endif
}

/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevGetParam - Geraeteparameter ermitteln
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevGetParam( hnd, id, param )
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     id IN [int] - Parameterkennung.
*     param OUT [PARAMETER*] - gelesener Parameterwert.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*     Diese Funktion kann auch mit einem Hyper-Handle aufgerufen
*     werden. In diesem Falle wird der untergeordnete Treiber mit
*     NULL als Zeiger fuer den spez. Parameterblock aufgerufen.
*     Der Parameter DEV_ID_ERROR wird bereits in dieser Steuerschicht
*     beruecksichtigt und nicht nach unten weitergegeben.
*
**.EF.***********************************************************************/
GLOBAL int DevGetParam(USR_HANDLE hnd, int id, PARAMETER * param)
{
   int err;
   
   If (HND_BAD(hnd) && !HND_HYPER(hnd)) Then
      return DEV_ERROR;
   Elseif (id==DEV_ID_ERROR) Then
      /*TE* 14.08.89 Vorzeichenbehaftete Umwandlung */
      *param = (int) (HndErr[hnd]);
      return USR_NO_ERROR;
   Else
      err = (*HndModul[hnd]->GetParam)(HndParam[hnd],id,param);
      return ERR(hnd,err);
   Endif
}

/*.SF.***********************************************************************
*
*  FUNKTION:
*     DevPrintf - Ausgabe eines formatierten String auf ein beliebiges Geraet
*
*  BESCHREIBUNG:
*     ...
*
*  AUFRUF:
*     err = DevPrintf(hnd, fmtstr, ...) 
*
*  PARAMETER:
*     err RESULT [int] - Fehlerflag.
*     hnd IN [USR_HANDLE] - Handle.
*     fmtstr IN [char *] - Format-Spezifikation.
*
*  FEHLER:
*     ...
*
*  REFERENZEN:
*     ...
*
*  BEMERKUNGEN:
*
**.EF.***********************************************************************/
#define PRINTF_BUFLEN 256
LOCAL USR_BYTE PrintfBuf[PRINTF_BUFLEN];

GLOBAL int DevPrintf(USR_HANDLE hnd, char * fmtstr, ...)
{  int ret;
   va_list args;
   va_start(args, fmtstr);
   ret = XDevPrintf(hnd, fmtstr, args);
   va_end(args);
   return ret;
}

GLOBAL int XDevPrintf(USR_HANDLE hnd, char * fmtstr, va_list args)
{ int n;
  char * buf = PrintfBuf;

  If ((n = vsprintf(buf, fmtstr, args)) > PRINTF_BUFLEN) Then
      return ERR_BAD_PARAMETERS;
  Endif
  DevWrite(hnd, buf, n, NULL, 0);
  return USR_NO_ERROR;
}


/*********************************************************************
*                                                                    *
*              I  Q  T  D  E  V   -   E  N  D  E                     *
*                                                                    *
*********************************************************************/
