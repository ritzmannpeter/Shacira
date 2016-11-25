#define DEBUG_DSKx

/*.SM.****************************************************************
*                                                                     
*  MODUL-NAME:                                                        
*      DEVDISK                                                        
*                                                                     
*  BESCHREIBUNG:                                                      
*     Diskettentreiber fuers IQT ...                                  
*                                                                     
*  UMGEBUNG:                                                          
*     ZIELRECHNER:          IQT-450/QNX 2.15                                   
*     ENTWICKLUNGSRECHNER   PC-AT 386/QNX 2.15
*     UEBERSETZER:          Computer Inovations c86 V3.3                  
*     OPTIONEN:                                                       
*                                                                      
*                                                                     
*  VERSION:                                                           
*     VERSION:  2.0                     DATUM:       24.03.92         
*     AUTOR:    -MBa- M.Bauernfeind     TELEFON KFD: 07644/78381      
*/    const char Vers_DEVDISK[]   = "@(#)DEVDISK   2.0 24.03.92";/*
*                                                                     
*  HISTORY:                                                           
*     24.03.92 -MBa-   Portierung auf IQT 450                         
*     21.09.92 -PR-  Diskserver eliminiert
*     15.10.92 -PR-  Testausgaben entfernt
*
*     18.05.92 -TSchw- DskOpen: Klammerfehler beim Setzen des Datums *
*                      behoben. Fehler erst ab V.57 vorhanden. Er    *
*                      hat zur Folge, dass mit Version 57 erstellte  *
*                      Datentraeger nie nach Datum sortiert angezeigt*
*                      werden koennen. Hinweis SF.                   *
*
*     17.12.92 -TSchw- Wenn beim DskOpen nicht mehr genuegend        *
*                      Speicherplatz vorhanden ist, um den FCB zu    *
*                      allocieren, wird die Funktion korrekt abge-   *
*                      brochen. Wird danach aber das Device mit      *
*                      DskClose geschlossen, so wird mit dem Null-   *
*                      zeiger im FCB gearbeitet, was in der Regel    *
*                      einen Programmabbruch zur Folge hat. Deshalb  *
*                      wurde am Anfang von DskOpen der FCB-Pointer   *
*                      auf NULL abgefragt.                           *
*     20.05.93 -TS-    Fehlerrueckgabe verfeinert @@1
*     06.05.93 -PR-    Modul-spezifische Open- und Close-Funktionen
*                      eingefuehrt (Motivation siehe diskms.c).
*                      Zu diesem Zweck war die Einfuehrung des Filecodes
*                      im FCB notwendig.
*                      Abschliessendes BufExpand in DskClose auskommentiert,
*                      da es mir bis heute nicht sinnvoll erscheint.
*                      (kann sich ja noch aendern)
*     07.05.93 -PR-    Makros FOFFS, BOFFS und FBLKS in diskxy.h
*                      ausgelagert.
*     21.05.93 -PR-    Case-Insensitive Suche nach Files im Directory
*                      realisiert.
*     11.06.93 -PR-    fcb->BlkBuffer in DskClose nur freigeben wenn er
*                      vorher allokiert wurde.
*     16.03.96 -PR-    Portierung aus dem IQT fuers DNC.
*                      Folgende Erweiterungen bzw. Aenderungen:
*                      - Die EOF-Bedingung wird jetzt gesetzt, wenn
*                        versucht wird ueber das Dateiende hinaus zu lesen,
*                        nicht erst, wenn versucht wird hinter dem Dateiende
*                        zu lesen. Im IQT war dieses unsaubere Verhalten ohne
*                        Auswirkungen, da dort nie auf EOF abgefragt wird.
*                      - Rueckgabewert von Bufformat an die uebergeordneten
*                        Schichten weitergegeben werden.
*
*
*
*
*
*
*
*
*  BEMERKUNGEN:                                                       
*                                                                     
* ------------------------------------------------------------------  
*                                                                     
*  EXPORTSCHNITTSTELLE:
* 
*  FUNKTIONEN:
*     DskInit - Diskettentreiber einmalig initialisieren              
*     DskOpen - Handle fuer eine Datei ermitteln                      
*     DskClose - Handle fuer eine Datei wieder freigeben              
*     DskGetParam - Dateiparameter ermitteln                          
*     DskSetParam - Dateiparameter einstellen                         
*     DskWrite - String in eine Datei ausgeben                        
*     DskRead - String aus einer Datei lesen                          
*     DskExamine - Dummy-Funktion                                     
*     DskControl - Dummy-Funktion                                     
*
*  DATENTYPEN:
*
*  VARIABLEN:
*
**.EM.****************************************************************/

/*********************************************************************
X  INCLUDE-DATEIEN
*********************************************************************/

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
#ifndef _ctype 
#include <ctype.h>
#define _ctype
#endif
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _diskxy
#include <diskxy.h>
#define _diskxy
#endif
#ifndef _iqttsk
#include <iqttsk.h>
#define _iqttsk
#endif
#ifndef _iqtmem
#include <iqtmem.h>
#define _iqtmem
#endif
#ifndef _devdisk
#include <devdisk.h>
#define _devdisk
#endif
/*.EI.***********************************************************************/

/*********************************************************************
X  HILFEN ZUR FEHLERSUCHE
*********************************************************************/

static long MaxFileSize;

#define O_OPEN  1  
#define O_CLOSE  2  
#define O_READ  3  
#define O_WRITE  4  
#define BUFCREATE  5  
#define BUFEXPAND  6  
#define BUFREAD  7  
#define BUFWRITE  8  
#define BUFSTATUS  9  
#define BUFDELETE  10  
#define BUFFORMAT  11  
#define BUFRESTORE  12  
#define BUFDIRECTORY  13  
#define BUFOPEN  14  
#define BUFCLOSE  15
#define BUFRELOAD  16
#define BUFSAVE  17

#ifdef DEBUG_DSK

#define DEBUG_IT
#include <process.h>

typedef struct debug_table
{ char * name;
  int pos;
  int wait; } DEBUG_TABLE;

static const DEBUG_TABLE dtab [] =
{
{"",0, 0},
{"OPEN         ", 1, 0},
{"CLOSE        ", 2, 0},
{"READ         ", 3, 0},
{"WRITE        ", 4, 0},
{"BUFCREATE    ", 5, 0},
{"BUFEXPAND    ", 6, 0},
{"BUFREAD      ", 7, 0},
{"BUFWRITE     ", 8, 0},
{"BUFSTATUS    ", 9, 0},
{"BUFDELETE    ", 10, 0},
{"BUFFORMAT    ", 11, 0},
{"BUFRESTORE   ", 12, 0},
{"BUFDIRECTORY ", 13, 0},
{"BUFOPEN      ", 14, 0},
{"BUFCLOSE     ", 15, 0},
{"BUFRELOAD    ", 16, 0},
{"BUFSAVE      ", 16, 0}
};

#define IN  0
#define OUT 1

#ifdef QNX_BASED
LOCAL void dsk_debug (USR_BYTE type, int func, FCB_PTR fcb, int err)
{
    if (fcb != NULL) term_printf(0,54,0x40,"%5.5ld %5.5ld %5.5ld", MaxFileSize, fcb->FileSize, fcb->FilePos);
    If (type == IN) Then
       term_printf(dtab[func].pos,54,0x04,"%s ",dtab[func].name);
    Else
       term_printf(dtab[func].pos,54,0x40,"%s %4.4d",dtab[func].name, err);
    Endif
    term_cur(24,0);
    if (type == IN && dtab[func].wait) sleep(dtab[func].wait);
    return;
}
#else
LOCAL void dsk_debug (USR_BYTE type, int func, FCB_PTR fcb, int err)
{
    if (fcb != NULL) printf("max %5.5ld size %5.5ld pos %5.5ld\n", MaxFileSize, fcb->FileSize, fcb->FilePos);
    If (type == IN) Then
       printf("entry %s\n", dtab[func].name);
    Else
       printf("exit %s err %4.4d\n", dtab[func].name, err);
    Endif
    return;
}
#endif

#define __DEBUG_IN__(func,file) dsk_debug(IN,func,(file),err);

#define __DEBUG_OUT__(func,file)  dsk_debug(OUT,func,(file),err);

#else

#define __DEBUG_IN__(func,fcb) 
#define __DEBUG_OUT__(func,fcb) 

#endif

/*********************************************************************
X  EXTERNE VARIABLEN UND PROZEDURDEN
*********************************************************************/

/*
** Zeiger fuer die benoetigten Funktionen-Structe:
*/
extern const DISKMOD_TYP FloppyModule,CarrierModule;

const DISKMOD_TYP FloppyModule = {
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,
   NULL,NULL,NULL,NULL,NULL,NULL,NULL };

/*********************************************************************
X  MODULINTERNE KONSTANTEN
*********************************************************************/

/*
** Anzahl der unterstuetzten Laufwerke muss mit den in DEVDISK.H
** definierten Laufwerkskennungen (Indizes in DriveList) korrespondieren.
*/
#define DRIVE_COUNT 8      /* Anzahl der Laufwerke */

typedef struct DRIVE_ {    /* Hilfsdatentyp fuer die DriveList */
   DISKMOD_PTR DMod;       /* Laufwerkstyp: Zeiger auf Funktionen-Struct */
   USR_BYTE Com;               /* bei Floppy: Schnittstellennummer */
   USR_BYTE Nr;                /* bei Floppy: WP-spezifische Laufwerksnummer */
} DRIVE_TYP;

static const DRIVE_TYP DriveList[DRIVE_COUNT] = {
	{(DISKMOD_PTR)&FloppyModule, NO_COM, 1},           /* DISK_DRV_FLO1  */
	{(DISKMOD_PTR)&FloppyModule, NO_COM, 1},           /* DISK_DRV_FLO2  */
	{(DISKMOD_PTR)&CarrierModule, NO_COM, CAR_DRV0},    /* DISK_DRV_EEP1  */
	{(DISKMOD_PTR)&CarrierModule, NO_COM, CAR_DRV1},    /* DISK_DRV_EEP2  */
	{(DISKMOD_PTR)&CarrierModule, NO_COM, CAR_KPROM},    /* DISK_DRV_KPROM */
	{(DISKMOD_PTR)&FloppyModule, NO_COM, 1},           /* QNX_DISK_DRV_FLO1  */
	{(DISKMOD_PTR)&FloppyModule, NO_COM, 1},           /* QNX_DISK_DRV_FLO2  */
	{(DISKMOD_PTR)&FloppyModule, NO_COM, 1}             /* QNX_DISK_DRV_HDISK  */
};

/*********************************************************************
X  SCHNITTSTELLE ZUM HAUPTMODUL "IQTDEV.C"
*********************************************************************/

GLOBAL int DskInit(DISK_INIT_BLOCK * initblock);
GLOBAL int DskOpen(USR_HANDLE hnd, DISK_PARAM_BLOCK * paramblock,
                   FCB_PTR *fcb, MODULE_PTR * modul);
GLOBAL int DskClose(FCB_PTR fcb, int * done);
GLOBAL int DskRead(FCB_PTR fcb, char * buf, int buflen, int * aktlen, TIME tmo);
GLOBAL int DskWrite(FCB_PTR fcb, char * buf, int buflen, int * aktlen, TIME tmo);
GLOBAL int DskControl(FCB_PTR fcb, int cntrl, PARAMETER param);
GLOBAL int DskExamine(FCB_PTR fcb, char * byte, TIME tmo);
GLOBAL int DskSetParam(FCB_PTR fcb, int id, PARAMETER param);
GLOBAL int DskGetParam(FCB_PTR fcb, int id, PARAMETER * param);

GLOBAL const MODULE_TYP DiskModule = {
   DskInit,
   DskOpen,
   DskClose,
   DskRead,
   DskWrite,
   DskControl,
   DskExamine,
   DskSetParam,
   DskGetParam};


/*********************************************************************
X
X  MODULEIGENE HILFSFUNKTIONEN
X
*********************************************************************/


/*********************************************************************
X  VERWALTUNG EINER ALTERUNGSMATRIX NACH DEM LRU-VERFAHREN
*
*  int LruInit()
*     Initialisiert die LRU-Verwaltung.
*
*  LruClear(lru, items)
*     Initialisiert die durch den Zeiger 'lru' gegebene Alterungs-
*     matrix mit 'items' Elementen und liefert ein Fehlerflag zurueck.
*
*  int LruMark(lru, item)
*     Markiert 'item' der 'lru'-Matrix als benutzt, um so deren
*     Alterung verfolgen zu koennen.
*
*  int LruGetNext(lru)
*     Ermittelt den naechsten freien bzw. den aeltesten Eintrag in
*     der 'lru'-Matrix.
*
*********************************************************************/

#define LRUTYPE  USR_WORD
#define LRUITEMS (sizeof(LRUTYPE)*8)

typedef struct {
   int items;
   LRUTYPE matrix[LRUITEMS];
} LRU;

static SEMAPHORE LruSema;

LOCAL int /*err*/ LruInit(/*void*/)
{
   return SemInit(&LruSema, 10);
}

LOCAL void LruClear(LRU * lru, int items)
{
   SemP(&LruSema);
   lru->items = items;
   memset(lru->matrix, 0, sizeof(LRUTYPE)*items);
   SemV(&LruSema);
}

LOCAL void LruMark(LRU * lru, register int item)
{
   register LRUTYPE mask = ~(1<<item) & ((1<<item)-1);

   SemP(&LruSema);

   If (lru->matrix[item] != mask) Then
      lru->matrix[item] = mask;
      For (item=0 ; item<lru->items ; item++) Do
         lru->matrix[item] &= mask;
      Endfor
   Endif

   SemV(&LruSema);
}

LOCAL int /*item*/ LruGetNext(LRU * lru)
{	register int item;

	SemP(&LruSema);
	/* Freien oder aeltesten Eintrag suchen */
	For (item=0 ; item<lru->items && lru->matrix[item]!=0 ; item++) Do
		/* Nothing */ ;
	Endfor
	LruMark(lru, item);
	SemV(&LruSema);
	return item;
}


/*********************************************************************
X  GEPUFFERTE EIN-/AUSGABE
*
*  int BufInit()
*     Einmaliges Initialisieren der Pufferverwaltung sowie der
*     einzelnen Geraetetreiber.
*
*  int BufCreate(fcb, len)
*  int BufExpand(fcb, len, flush)
*     Anlegen/Erweitern einer Datei mit/auf eine(r) bestimmte(n)
*     Laenge. Bei Expand wird nur dann eine Aktion durchgefuehrt,
*     wenn sich die effektive Blocklaenge der Datei aendert oder
*     wenn flush=TRUE.
*
*  int BufRead(fcb, buffer, len, pos)
*  int BufWrite(fcb, buffer, len, pos)
*     Lesen von 'len' Bytes ab 'pos' in 'buffer' bzw. Schreiben von
*     'len' Bytes aus 'buffer' nach 'pos'.
*
*  int BufStatus(fcb, avail)
*     Ermitteln der Anzahl freier Bytes auf dem Datentraeger.
*
*  int BufDelete(fcb)
*  int BufFormat(fcb)
*  int BufSetDate(fcb, date, time)
*  int BufReadDate(fcb, date, time)
*  int BufRestore(fcb, mode)
*  int BufDirectory(fcb, mode)
*  int BufOpen(fcb)
*  int BufClose(fcb)
*     Diese Funktionen sind einfach aus Konsistenzgruenden da und
*     rufen lediglich die entsprechenden Geraetetreiber auf.
*
*  [MACRO] FOFFS(o,fcb)
*     Wandelt einen Byteoffset 'o' in einen Blockoffset.
*
*  [MACRO] BOFFS(o,fcb)
*     Berechnet aus einen Byteoffset 'o' den Blockrelativen Offset.
*
*  [MACRO] FBLKS(l,fcb)
*     Berechnet die Anzahl Bloecke fuer eine Datei der Laenge 'l'.
*
*  --- INTERNE FUNKTIONEN ---
*
*  int BufReload(fcb, pos)
*     Laedt den Block mit der Nummer 'pos' in den 'fcb'-Puffer, wenn
*     sich dieser noch nicht im Speicher befindet.  Falls sich ein als
*     geaendert markierter Puffer im Speicher befindet, wird dieser
*     zurueckgeschrieben.  Falls sich noch ueberhaupt kein Puffer im
*     Speicher befand, wird einer angelegt.
*  int BufAlloc(fcb)
*     Allokiert Speicher fuer einen Puffer.
*
*********************************************************************/

LOCAL int /*err*/ BufInit(/*void*/)
{
#ifdef QNX_BASED
   return ((*FloppyModule.Init)() || (*CarrierModule.Init)())
             ? ERROR : USR_NO_ERROR;
#else
	return (*CarrierModule.Init)();
#endif
}

LOCAL int /*err*/ BufCreate(FCB_PTR fcb, USR_LONG len)
{  int err = (*fcb->DMod->Create)(fcb, len);

__DEBUG_IN__(BUFCREATE,fcb)
__DEBUG_OUT__(BUFCREATE,fcb)

   return err;
}

LOCAL int /*err*/ BufExpand(FCB_PTR fcb, USR_LONG len, USR_BOOL flush)
{  int err = USR_NO_ERROR;

__DEBUG_IN__(BUFEXPAND,fcb)

   If (!flush && FBLKS(len,fcb) == FBLKS(fcb->FileSize, fcb)) Then
      err = USR_NO_ERROR;
   Else
      err = (*fcb->DMod->Expand)(fcb, len);
   Endif

__DEBUG_OUT__(BUFEXPAND,fcb)

   return err;

}

LOCAL int /*err*/ BufSave(FCB_PTR fcb)
{  int err = USR_NO_ERROR;

__DEBUG_IN__(BUFSAVE,fcb)

   If (fcb->BlkChanged) Then
      fcb->BlkChanged = FALSE;
      err = (*fcb->DMod->Write)(fcb, fcb->BlkBuffer, (USR_LONG)fcb->BlkSize, (USR_LONG)fcb->BlkPos*fcb->BlkSize);
   Endif

__DEBUG_OUT__(BUFSAVE,fcb)

   return err;
}

LOCAL int /*err*/ BufAlloc(FCB_PTR fcb)
{  int err = USR_NO_ERROR;

   If ((fcb->BlkBuffer = MemAlloc(fcb->BlkSize)) == NULL) Then
      err = DiagPutMsg(ERR_DRAM_ALLOC,0L,0,__FILE__,__LINE__);
   Endif

   return err;
}
   
LOCAL int /*err*/ BufReload(FCB_PTR fcb, USR_WORD pos)
{  int err = USR_NO_ERROR;

__DEBUG_IN__(BUFRELOAD,fcb)

   If (fcb->BlkBuffer == NULL && (err = BufAlloc(fcb)) != USR_NO_ERROR) Then
__DEBUG_OUT__(BUFRELOAD,fcb)
      return err;
   Endif

   If (fcb->BlkPos == pos) Then
      err =  USR_NO_ERROR;
__DEBUG_OUT__(BUFRELOAD,fcb)
      return err;
   Endif
   If ((err = BufSave(fcb)) != USR_NO_ERROR)  Then
__DEBUG_OUT__(BUFRELOAD,fcb)
      return err;
   Endif

   If ((err = (*fcb->DMod->Read)(fcb, fcb->BlkBuffer, (USR_LONG)fcb->BlkSize, (USR_LONG)pos*fcb->BlkSize)) == USR_NO_ERROR) Then
      fcb->BlkPos = pos;
   Endif

__DEBUG_IN__(BUFRELOAD,fcb)

   return err;
}

LOCAL int /*err*/ BufRead(FCB_PTR fcb, USR_BYTE *buffer, USR_LONG len, USR_LONG pos)
{  int err = USR_NO_ERROR;
   USR_WORD cpylen;
   USR_WORD blkpos = FOFFS(pos,fcb);
   USR_WORD blkoffs = BOFFS(pos,fcb);

__DEBUG_IN__(BUFREAD,fcb)

   While (len > 0) Do
      If ((err = BufReload(fcb, blkpos)) != USR_NO_ERROR) Then
__DEBUG_OUT__(BUFREAD,fcb)
         return err;
      Endif
      cpylen = MIN(len, fcb->BlkSize-blkoffs);
      memcpy(buffer, fcb->BlkBuffer+blkoffs, cpylen);
      buffer += cpylen;
      len -= cpylen;
      blkoffs = 0;
      blkpos++;
   Endwhile

__DEBUG_OUT__(BUFREAD,fcb)

   return err;
}

LOCAL int /*err*/ BufWrite(FCB_PTR fcb, USR_BYTE *buffer, USR_LONG len, USR_LONG pos)
{  int err = USR_NO_ERROR;
   USR_WORD cpylen;
   USR_WORD blkpos = FOFFS(pos,fcb);
   USR_WORD blkoffs = BOFFS(pos,fcb);

__DEBUG_IN__(BUFWRITE,fcb)

   If (!fcb->BlkBuffer) Then
      If ((err = BufAlloc(fcb)) != USR_NO_ERROR) Then
__DEBUG_OUT__(BUFWRITE,fcb)
         return err;
      Endif
   Endif

   While (len > 0) Do
      cpylen = MIN(len, fcb->BlkSize-blkoffs);
      If (cpylen < fcb->BlkSize) Then /* UP 28.06.91 */
         If ((err = BufReload(fcb, blkpos)) != USR_NO_ERROR) Then
__DEBUG_OUT__(BUFWRITE,fcb)
            return err;
         Endif
      Else
         If ((err = BufSave(fcb)) != USR_NO_ERROR) Then
__DEBUG_OUT__(BUFWRITE,fcb)
            return err;
         Endif
         fcb->BlkPos = blkpos;
      Endif
      memcpy(fcb->BlkBuffer+blkoffs, buffer, cpylen);
      fcb->BlkChanged = TRUE;
      buffer += cpylen;
      len -= cpylen;
      blkoffs = 0;
      blkpos++;
   Endwhile

__DEBUG_OUT__(BUFWRITE,fcb)

   return err;
}


/*
*  Jetzt noch die trivialen Funktionen:
*/

LOCAL int /*err*/ BufStatus(FCB_PTR fcb, USR_LONG *avail)
{  int err;

__DEBUG_IN__(BUFSTATUS,fcb)

   err = (*fcb->DMod->Status)(fcb, avail);

__DEBUG_OUT__(BUFSTATUS,fcb)

   return err;
}

LOCAL int /*err*/ BufDelete(FCB_PTR fcb)
{  int err;

__DEBUG_IN__(BUFDELETE,fcb)

   err = (*fcb->DMod->Delete)(fcb);

__DEBUG_OUT__(BUFDELETE,fcb)

   return err;
}

LOCAL int /*err*/ BufFormat(FCB_PTR fcb)
{ int err;

__DEBUG_IN__(BUFFORMAT,fcb)

  err = (*fcb->DMod->Format)(fcb);

__DEBUG_OUT__(BUFFORMAT,fcb)

   return err;
}

LOCAL int /*err*/ BufSetDate(FCB_PTR fcb, USR_WORD date, USR_WORD time)
{
   return (*fcb->DMod->SetDate)(fcb, date, time);
}

LOCAL int /*err*/ BufReadDate(FCB_PTR fcb, USR_WORD *date, USR_WORD *time)
{
   return (*fcb->DMod->ReadDate)(fcb, date, time);
}

LOCAL int /*err*/ BufRestore(FCB_PTR fcb, USR_BYTE mode)
{  int err;

__DEBUG_IN__(BUFRESTORE,fcb)

   err = (*fcb->DMod->Restore)(fcb, mode);

__DEBUG_OUT__(BUFRESTORE,fcb)

   return err;
}             

LOCAL int /*err*/ BufDirectory(FCB_PTR fcb, void (*callback)())
{ int err;

__DEBUG_IN__(BUFDIRECTORY,fcb)

  err = (*fcb->DMod->Directory)(fcb, callback);

__DEBUG_OUT__(BUFDIRECTORY,fcb)

  return err;
}

LOCAL int /*err*/ BufOpen(FCB_PTR fcb)
{  int err;

__DEBUG_IN__(BUFOPEN,fcb)

   err = (*fcb->DMod->Open)(fcb);

__DEBUG_OUT__(BUFOPEN,fcb)

   return err;
}

LOCAL int /*err*/ BufClose(FCB_PTR fcb)
{  int err;

__DEBUG_IN__(BUFCLOSE,fcb)

   err = (*fcb->DMod->Close)(fcb);

__DEBUG_OUT__(BUFCLOSE,fcb)

   return err;
}



/*********************************************************************
*  SPEICHERVERWALTUNG
*
*  FCB_PTR fcb = FcbAlloc()
*     Belegt Speicher fuer einen FCB, liefert NULL bei einem Fehler.
*
*  void = FcbFree(FCB_PTR fcb)
*     Speicher eines FCB wieder frei geben.
*
*********************************************************************/

#define FcbAlloc() ((FCB_PTR) MemAlloc(sizeof(FCB_TYP)))

#define FcbFree(f) MemFree(f)


/*********************************************************************
*  VERWALTUNG DER KATALOG-DATENSTRUKTUR
*
*  int DirLock(fcb)
*     Liest, falls noetig, das Directory des in 'fcb' angegebenen
*     Laufwerkes ein. Traegt Dateigroesse und Datum im 'fcb' ein.
*
*  int DirUnlock(fcb)
*     Screibt die FileSize vom 'fcb' ins Directory zurueck.
*     Gibt ein 'gelocktes' Directory wieder frei (falls moeglich).
*
*  int DirRead(fcb, pos, buf, buflen, actlen)
*     Liest den Inhalt des Directories des durch 'fcb' gegebenen
*     Laufwerkes ab Byteposition 'pos' in den Puffer ab 'buf' aus.
*     Die Puffergroesse wird durch 'buflen' angegeben. Die tatsaech-
*     liche Anzahl gelesener Bytes wird in 'actlen' zurueckgegeben.
*
*  --- INTERNE FUNKTIONEN ---
*
*  DirLockCallback(fcb, filename, filesize, Date, Time)
*     Wird von BufDirectory() fuer jeden Eintrag des Inhaltsver-
*     zeichnisses aufgerufen und traegt die so erhaltenen Daten
*     'filename' und 'filesize' in den eigenen Directory-Puffer ein.
*
*  DirSearch(dir, filename)
*     Sucht im durch 'dir' gegebenen Directory-Puffer den Dateinamen
*     'filename' und liefert die gefundene Position zurueck oder -1
*     falls nichts gefunden.
*
*********************************************************************/

typedef struct {
   int locks;
   int entries;
   DISK_DIR_STRUCT *buf;
} DRIVE_DIR;

static DRIVE_DIR DriveDir[DRIVE_COUNT];

LOCAL void InitDirLock()
{
   memset(DriveDir, 0, DRIVE_COUNT * sizeof(DRIVE_DIR));
}

LOCAL void DirLockCallback(FCB_PTR fcb, char *filename, USR_LONG filesize,
                           USR_WORD Date, USR_WORD Time)
{
   DRIVE_DIR * dir = &DriveDir[fcb->Drive];
   strncpy(dir->buf[dir->entries].FileName, filename, 13);
   dir->buf[dir->entries].Size = filesize;
   dir->buf[dir->entries].Date = ((PARAMETER)Date << 16) | (PARAMETER)Time;
   dir->entries++;
}

#define FILE_NAME_LEN 30

LOCAL int /*where*/ DirSearch(DRIVE_DIR * dir, char * filename)
{
   int i, j;
   char dir_filename[FILE_NAME_LEN],
        search_filename[FILE_NAME_LEN];

/* Hier musste ich eine Case-Insensitive Suche realisieren,
 * da es sonst mit dem DFS Probleme gibt. PR 21.05.93
 */

   strcpy(search_filename,filename);
   For (j=0; search_filename[j] != '\0' &&
             j < FILE_NAME_LEN; j++) Do
      search_filename[j] = tolower(search_filename[j]);
   Endfor

   For (i=0 ; i<dir->entries ; i++) Do
      strcpy(dir_filename,dir->buf[i].FileName);
      For (j=0; dir_filename[j] != '\0' &&
             j < FILE_NAME_LEN; j++) Do
         dir_filename[j] = tolower(dir_filename[j]);
      Endfor
      if (strcmp(dir_filename, search_filename) == 0) return i;
   Endfor

   return -1;
}

LOCAL int /*err*/ DirLock(FCB_PTR fcb)
{  int err = USR_NO_ERROR;
   int pos, bufsize;
   DRIVE_DIR * dir = &DriveDir[fcb->Drive];

   If (dir->locks == 0) Then
      bufsize = fcb->DirEntries * sizeof(DISK_DIR_STRUCT);
      If ((dir->buf = MemAlloc(bufsize)) == NULL) Then
         return DiagPutMsg(ERR_DRAM_ALLOC,0L,0,__FILE__,__LINE__);
      Endif
      dir->entries = 0;
      memset(dir->buf, 0, bufsize);
		err = BufDirectory(fcb, DirLockCallback);
   Endif

   if (err != USR_NO_ERROR) return err;

   If (fcb->FileName[0] == '\0') Then
      fcb->FileSize = dir->entries * sizeof(DISK_DIR_STRUCT);
   Else
      If ((pos = DirSearch(dir,fcb->FileName)) >= 0) Then
         fcb->Flags |= FLAG_EXISTS;
         fcb->FileSize = dir->buf[pos].Size;
         fcb->Date = dir->buf[pos].Date;
      Endif
   Endif

   dir->locks++;

   return err;
}


LOCAL int DirUnlock(FCB_PTR fcb)
{
   DRIVE_DIR * dir = &DriveDir[fcb->Drive];
   If (dir->locks > 0  &&  --dir->locks == 0) Then
      MemFree(dir->buf);
      return BufRestore(fcb, MODE_FLUSH);
   Endif
   return USR_NO_ERROR;
}

int DirRead(FCB_PTR fcb, int pos, char * buf, int buflen, int * actlen)
{
   DRIVE_DIR * dir = &DriveDir[fcb->Drive];

   *actlen = MIN(fcb->FileSize-pos, buflen);
   memcpy(buf, ((char*)dir->buf) + pos, *actlen);
   fcb->FilePos += *actlen; /* UP 28.06.91 */

   return USR_NO_ERROR;
}


/*********************************************************************
*  int err = ErrorReturn(FCB_PTR fcb)
*     Umrechnen eines internen Fehlers in fcb.Error in einen Rueck-
*     gabewert an die Schnittstelle nach aussen.
*********************************************************************/

LOCAL int /*err*/ ErrorReturn(FCB_PTR fcb)
{
   PUTSD(D_DEV,"#ERR",fcb->Error);
   return fcb->Error;
}


/*------------------------------------------------------------------*\
X
X  IMPLEMENTIERUNG DER HAUPTFUNKTIONEN
X
\*------------------------------------------------------------------*/


/*********************************************************************
*
*  FUNKTION: DskInit - Treiber initialisieren
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskInit (initblock)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlerflag (USR_NO_ERROR oder ERROR).
*     initblock IN [DISK_INIT_BLOCK*] - Initialisierungsparameter.
*
*  BEMERKUNGEN:
*     Die uebergeordnete Steuerschicht in IQTDEV.C garantiert, dass
*     diese Funktion nach erfolgreicher Initialisierung kein weiteres
*     Mal aufgerufen wird.
*
*********************************************************************/

GLOBAL int DskInit(DISK_INIT_BLOCK * initblock)
{
   DEBUGINIT(0xFFFFFFFFL);
   PUTS(D_DEV,"#DiskInit");
   InitDirLock ();

   return BufInit();
}


/*********************************************************************
*
*  FUNKTION: DskOpen - Verbindung zum Geraet herstellen
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskOpen (hnd, openblock, fcb, modul)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     hnd  IN  [USR_HANDLE] - Handle den das Geraet bekommen soll.
*     openblock  IN  [DISK_PARAM_BLOCK*] - Open-Parameter.
*     fcb  OUT  [FCB_PTR*] - FCB.
*     modul  OUT  [MODULE_PTR*] - Zeiger auf Treiberstruct.
*
*  BEMERKUNGEN:
*     Im Fehlerfall (err>0) markiert modul==NULL dass das Geraet nicht
*     geoeffnet wurde. Zeigt modul trotz Fehler auf einen Treiberstrukt,
*     so kann dennoch mit dem Geraet gearbeitet werden.
*
*********************************************************************/

GLOBAL int DskOpen(USR_HANDLE hnd, DISK_PARAM_BLOCK * paramblock, FCB_PTR * fcb,
                   MODULE_PTR * modul)
{  int err = USR_NO_ERROR;
   USR_BYTE dummybuf;
   *modul = (MODULE_PTR)&DiskModule;
   *fcb = NULL;

   MaxFileSize = 0;

__DEBUG_IN__(O_OPEN,*fcb)

   If ((*fcb = FcbAlloc())==NULL) Then
      err = ERR_DRAM_ALLOC;
__DEBUG_OUT__(O_OPEN,*fcb)
      return err;
   Endif

   memset(*fcb, 0, sizeof(FCB_TYP));

   (*fcb)->Drive = paramblock->Drive;
   (*fcb)->Mode = paramblock->Mode;
   (*fcb)->Date = ((paramblock->Mode & DISK_OP_WRITE) != 0L) ? paramblock->Date : 0; /*@@@*/
   (*fcb)->DMod = DriveList[(*fcb)->Drive].DMod;
   (*fcb)->ComHnd = DriveList[(*fcb)->Drive].Com;
   (*fcb)->DriveNr = DriveList[(*fcb)->Drive].Nr;
   (*fcb)->BlkPos = 0xffff;
   (*fcb)->FileCode = 0xffff;

   If (paramblock->FileName == NULL) Then
      (*fcb)->Flags |= FLAG_DIRECTORY;
      (*fcb)->FileName[0] = '\0';
      If ((*fcb)->Mode & DISK_OP_DELETE) Then
__DEBUG_OUT__(O_OPEN,*fcb)
          return err;
      Endif
   Else
      strncpy((char*)(*fcb)->FileName, paramblock->FileName, 12);
      (*fcb)->FileName[12] = '\0';
   Endif

   If ((err = BufRestore(*fcb,MODE_INIT)) == USR_NO_ERROR &&
         (err =  DirLock(*fcb)) == USR_NO_ERROR) Then
      If (! ((*fcb)->Flags & FLAG_DIRECTORY)) Then
         If ((*fcb)->Mode & DISK_OP_CREATE) Then
            If ((*fcb)->Flags & FLAG_EXISTS) Then
               err = ERR_MULTIPLE_FILE;
            Else
               err = BufOpen(*fcb);
               err = BufCreate(*fcb, (USR_LONG)(*fcb)->BlkSize);/*@@1*/
            Endif
         Else
            If (! ((*fcb)->Flags & FLAG_EXISTS)) Then
               err = ERR_FILE_NOT_FOUND;
            Else
               err = BufOpen(*fcb);
            Endif
         Endif
      Endif
   Endif

   If (err == USR_NO_ERROR) Then
      *modul = (MODULE_PTR)&DiskModule;
   Else
      *modul = NULL;
      DirUnlock(*fcb);
      FcbFree(*fcb);
   Endif

__DEBUG_OUT__(O_OPEN,*fcb)

   return err;
}


/*********************************************************************
*
*  FUNKTION: DskClose - Verbindung zum Geraet trennen
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskClose (fcb, done)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - FCB.
*     done OUT [int *] - Flag ob Close durchgefuehrt.
*
*********************************************************************/

GLOBAL int DskClose(FCB_PTR fcb, int * done)
{  int err = USR_NO_ERROR;

__DEBUG_IN__(O_CLOSE,fcb)
 
   If (!fcb) Then      /* TS 19-06-92 */  
      *done = CLOSE_DONE;
__DEBUG_OUT__(O_CLOSE,fcb)
      return err;
   Endif

   If (fcb->Mode & DISK_OP_WRITE) Then /* UP 19.07.91 */
      /* aktualisiere Dateigroesse */
      /* Bei der Floppy hat das die fatale Auswirkung, daá
       * der letzte Block mit Nullen ueberschrieben wird;
       * d. h. dieser Fall muss dort abgefangen werden !!
       */
      err = BufExpand(fcb, fcb->FileSize, TRUE);
   Endif

   err = DirUnlock(fcb);
   err = BufSave(fcb);

   If (fcb->Flags & FLAG_DIRECTORY && fcb->Mode & DISK_OP_DELETE) Then
      err = BufClose(fcb);
      If ((err = BufFormat(fcb)) == USR_NO_ERROR) Then
         err = BufRestore(fcb, MODE_FLUSH);
      Endif
   Elseif (fcb->Mode & DISK_OP_DELETE) Then
      err = BufClose(fcb);
      err = BufDelete(fcb);
      err = BufRestore(fcb, MODE_FLUSH); /* UP 28.6.91 */
   Else
      err = BufClose(fcb);
   Endif

   if (fcb->BlkBuffer) MemFree(fcb->BlkBuffer);
   MemFree(fcb);
   *done = CLOSE_DONE;

__DEBUG_OUT__(O_CLOSE,fcb)

   return err;
}

/*********************************************************************
*
*  FUNKTION: DskRead - Datenblock lesen
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskRead(fcb, buf, buflen, aktlen, tmo)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - FCB.
*     buf  IN  [char*] - Zeiger auf Datenpuffer.
*     buflen  IN  [int] - Groesse des Datenpuffers.
*     aktlen  OUT  [int*] - tatsaechlich gelesene Daten.
*     tmo  IN  [int] - Timeout-Parameter.
*
*********************************************************************/

GLOBAL int DskRead(FCB_PTR fcb, char * buf, int buflen,
                   int * aktlen, TIME tmo)
{  int err = USR_NO_ERROR;

FILE * stream;

__DEBUG_IN__(O_READ,fcb)

   If (!(fcb->Mode & DISK_OP_READ)) Then
      return DiagPutMsg(ERR_BAD_MODE,0L,0,__FILE__,__LINE__);
   Elseif (fcb->FilePos >= fcb->FileSize) Then
      *aktlen = 0;
      err = ERR_PAST_END;
__DEBUG_OUT__(O_READ,fcb)
      return err;
   Elseif (fcb->Flags & FLAG_DIRECTORY) Then
      err = DirRead(fcb, (int)fcb->FilePos, buf, buflen, aktlen);
__DEBUG_OUT__(O_READ,fcb)
      return err;
   Else
      long chars_to_read;
      long max_read_size = fcb->FileSize - fcb->FilePos;
      If (buflen > max_read_size) Then
         chars_to_read = max_read_size;
      Else
         chars_to_read = buflen;
      Endif
      err = BufRead(fcb, (USR_BYTE*)buf, chars_to_read, fcb->FilePos);
/*
      buflen = MIN(fcb->FileSize - fcb->FilePos, buflen);
      err = BufRead(fcb, (USR_BYTE*)buf, (USR_LONG)buflen, fcb->FilePos);
*/
      *aktlen = (err != USR_NO_ERROR) ? 0 : buflen;
      fcb->FilePos += *aktlen;
      if (chars_to_read < (USR_LONG)buflen) err = ERR_PAST_END;
__DEBUG_OUT__(O_READ,fcb)
      return err;
   Endif
}


/*********************************************************************
*
*  FUNKTION: DskWrite - Datenblock ausgeben
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskWrite(wcb,buf,buflen,aktlen,tmo)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - FCB.
*     buf IN [char*] - Zeiger auf Puffer mit Zeichen.
*     buflen IN [int] - Anzahl der Zeichen im Puffer.
*     aktlen OUT [int*] - Zahl der wirklich ausgegebenen Zeichen.
*     tmo IN [int] - Time-Out-Parameter.
*
*********************************************************************/


GLOBAL int DskWrite(FCB_PTR fcb, char * buf, int buflen,
                    int * aktlen, TIME tmo)
{  int err = USR_NO_ERROR;
   USR_LONG maxlen = fcb->FilePos+buflen;

__DEBUG_IN__(O_WRITE,fcb)

if (maxlen > MaxFileSize) MaxFileSize = maxlen;

   If (!(fcb->Mode & DISK_OP_WRITE) || (fcb->Flags & FLAG_DIRECTORY)) Then
      err = DiagPutMsg(ERR_BAD_MODE,0L,0,__FILE__,__LINE__);
__DEBUG_OUT__(O_WRITE,fcb)
      return err;
   Endif

   If (maxlen > fcb->FileSize) Then
      err = BufExpand(fcb, maxlen, FALSE);
      if (err == USR_NO_ERROR) fcb->FileSize = maxlen;
   Endif

   if (err == USR_NO_ERROR) err = BufWrite(fcb, (USR_BYTE*)buf, (USR_LONG)buflen, fcb->FilePos);

   If (err == USR_NO_ERROR && !(fcb->Flags & FLAG_NEWDATE)) Then
      err = BufSetDate(fcb, (USR_WORD)(fcb->Date>>16), (USR_WORD)fcb->Date);
      if (err == USR_NO_ERROR) fcb->Flags |= FLAG_NEWDATE;
   Endif

   fcb->FilePos += (*aktlen = (err != USR_NO_ERROR) ? 0 : buflen);

__DEBUG_OUT__(O_WRITE,fcb)

   return err;
}


/*********************************************************************
*
*  FUNKTION: DskControl - Kontrollfunktion
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskControl (fcb, cntrl, param)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - spez. Parameterblock.
*     cntrl  IN  [int] - Funktion.
*     param  IN  [PARAMETER] - Zusatzparameter.
*
*********************************************************************/

GLOBAL int DskControl(FCB_PTR fcb, int cntrl, PARAMETER param)
{
   return DiagPutMsg(ERR_NOT_AVAILABLE,0,0,__FILE__,__LINE__);
}


/*********************************************************************
*
*  FUNKTION: DskExamine - Zeichenvorausschau
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskExamine (fcb, byte, tmo)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - FCB.
*     byte  OUT  [char*] - naechstes Zeichen.
*     tmo  IN  [int] - Timeout-Parameter.
*
*********************************************************************/

GLOBAL int DskExamine(FCB_PTR fcb, char * byte, TIME tmo)
{
   return DiagPutMsg(ERR_NOT_AVAILABLE,0,0,__FILE__,__LINE__);
}


/*********************************************************************
*
*  FUNKTION: DskSetParam - Parameter setzen
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskSetPar(fcb, id, param)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - FCB.
*     id  IN  [int] - Identifier des Parameters.
*     param  IN  [PARAMETER] - neuer Parameterwert.
*
*********************************************************************/

GLOBAL int DskSetParam(FCB_PTR fcb, int id, PARAMETER param)
{

FILE * stream;

   /* Hyper-Handle nicht erlaubt */
   If  (fcb == NULL)  Then
      return DiagPutMsg(ERR_NOT_AVAILABLE,0,0,__FILE__,__LINE__);
   Endif

   Switch(id)
   Case DISK_ID_FILEPOS:

#ifdef TEST
If ((stream = fopen("disk.txt","a")) != NULL) Then
   fprintf(stream,"PAR %5.5ld \n",(long) param);
   fclose(stream);
Endif
#endif

      fcb->FilePos = (USR_LONG)param; break;
   Case DISK_ID_MODE:
   Case DISK_ID_DRIVE:
   Case DISK_ID_SIZE:
   Case DISK_ID_DATE:
   Case DISK_ID_FREE_SPACE:
   Case DISK_ID_VERSION:
      return ERR_READ_ONLY_ID;
   Default:
      return DiagPutMsg(ERR_BAD_ID,0,0,__FILE__,__LINE__);
   Endswitch

   return USR_NO_ERROR;
}


/*********************************************************************
*
*  FUNKTION: DskGetParam - Parameter ermitteln
*
*  BESCHREIBUNG:
*
*  AUFRUF:
*     err = DskGetPar(fcb, id, param)
*
*  PARAMETER:
*     err  RESULT  [int] - Fehlercode (USR_NO_ERROR oder >0).
*     fcb  IN  [FCB_PTR] - FCB.
*     id  IN  [int] - Identifier des zu ermittelnden Parameters.
*     param  OUT  [PARAMETER*] - aktueller Parameterwert.
*
*********************************************************************/

GLOBAL int DskGetParam(FCB_PTR fcb, int id, PARAMETER * param)
{  int err = USR_NO_ERROR;
   USR_WORD time,date;

   /* Hyper-Handle nicht erlaubt */
   If  (fcb == NULL)  Then
      return DiagPutMsg(ERR_NOT_AVAILABLE,0,0,__FILE__,__LINE__);
   Endif

   PUTS(D_DEV,"#DiskGetParam");

   Switch(id)
   Case DISK_ID_MODE: *param = (PARAMETER)fcb->Mode; break;
   Case DISK_ID_DRIVE: *param = (PARAMETER)fcb->Drive; break;
   Case DISK_ID_FILEPOS: *param = (PARAMETER)fcb->FilePos; break;
   Case DISK_ID_SIZE: *param = (PARAMETER)fcb->FileSize; break;
   Case DISK_ID_VERSION: *param = (PARAMETER)fcb->Version; break;
   Case DISK_ID_DATE:
      If (fcb->Date == 0 && !(fcb->Flags & FLAG_DIRECTORY) &&
           (err = BufReadDate(fcb, &date, &time))) Then
         fcb->Date = (PARAMETER)date<<16 | (PARAMETER)time;
      Endif
      *param = fcb->Date;
      return err;
   Case DISK_ID_FREE_SPACE:
      return BufStatus(fcb, (USR_LONG*)param);
   Default:
      return DiagPutMsg(ERR_BAD_ID,0,0,__FILE__,__LINE__);
   Endswitch

   return USR_NO_ERROR;
}

/*********************************************************************
*                                                                    *
*                  D E V D I S K   -   E  N  D  E                    *
*                                                                    *
*********************************************************************/
