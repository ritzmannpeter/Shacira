/*********************************************************************
*                                                                    *
*  MODUL-NAME: DISKCAR                                               *
*                                                                    *
*  BESCHREIBUNG:                                                     *
*     Treiber zur Ansteuerung eines Kloeckner-Datentraegermoduls...  *
*                                                                    *
*  HISTORY:                                                          *
*     15.09.89   -TE-      Rahmen geschaffen                         *
*     23.01.90   -TE-      Anpassung an MWC-Compiler durchgefuehrt   *
*     18.04.90   -TE-      Kompatibler Datentraeger und Kunden-      *
*                          PROM beruecksichtigt                      *
*     08.05.90   -TE-      KPROM in Bank 31 (nur LOW-Byte) lokiert   *
*     15.05.90   -TE-      redcar, wricar durch Monitor-Aufruf ers.  *
*     08.06.90   -TE-      Unterstuetzung fuer Datentraeger auf der  *
*                          Tastaturkarte eingebaut                   *
*     22.06.90   -TE-      Ueberarbeitung zwecks gepufferter I/O     *
*     30.07.90   -UP-      KPROM-zugriff differenziert gebankt/test  *
*                          bedingte šbersetzung mit NOBANK-Switch    *
*     14.08.90   -SF-      Alter Datentraeger hat nur 4096 BYTE Platz*
*     27.08.90   -TSchw-   DIAGNOSE-Makro eingefuehrt                *
*     20.09.90   -NB-      Erkennung versch. EPROM-Typen eingebaut   *
*     27.09.90   -NB-      Beschraenkung auf 32K-Carrier entfernt    *
*     19.06.91   -SF-      BUF_LEN auf 1024 Byte erhoeht             *
*     24.06.91   -SF-      CarDirectory: In Callback-Funktion Datum  *
*                          und Uhrzeit zurueckgeben                  *
*     01.07.91   -UP-    - Laengen- und Positionsparameter von USR_WORD  *
*                          auf USR_LONG geaendert. Einheit der Parameter *
*                          von Block# auf Byte# geaendert.           *
*                        - FlushCarrier: Konstante fuer reserv.      *
*                          Kassetteninterface eingefuehrt.           *
*     12.06.91   -SF/MW-   KPROM-Bank im IQT353 auch vorgesehen      *
*     07.08.91   -UP-    - Integration in Version 5.5                *
*     06.09.91   -TSchw- - ReadKPROM ausgelagert in DISKCAR1.C wegen *
*                          Overlayhandling                           *
*     20.09.91   -SF-      Makro GetNextSector geaendert             *
*     21.10.91   -TSchw-   ReleaseFile: Aenderung nach Diktat von SF,*
*                          da bisher Speicher nicht freigegeben wurde*
*     06.11.91   -TSchw-   FileSize: Sicherheitsabfrage eingebaut,   *
*                          telefonisch mit SF                        *
*     20.12.91   -TSchw-   strict: Parameter 2 von MakeFile und      *
*                          ChangeFileSize auf int gecastet;          *
*                          car_ptr != NULL                           *
*     13.02.92 -SF-    --- VERSION 3.0 ----------------------------- *
*                      Neu: CAR_DRV2 (Beschreiben des E-Quadrat auf  *
*                      der Interfacekarte) ==> CarFormat um Eintrag  *
*                      mit 16 KByte erweitert                        *
*     11.11.92 -TSchw- --- VERSION 3.1 ----------------------------- *
*                      CarReadDate entfernt, da nun in DEVDISK intern*
*                      programmiert                                  *
*     08.12.92 -TSchw- CarrierIO global gemacht und in DISKCAR.H     *
*                      extern deklariert. Diese Funktion wird in     *
*                      DISKWORK.C benoetigt, um abseits des Dateien- *
*                      handling auf den Datentraeger zugreifen zu    *
*                      koennen, um Iscos-Sonderprogramm aus dem auf  *
*                      dem Datentraeger befindlichen EProm lesen zu  *
*                      koennen.
*     16.03.96 -PR-    Portierung aus dem IQT fuers DNC.             *
*                      Folgende Erweiterungen:                       *
*                      - In CarDelete BufModify und fc->Update       *
*                        gesetzt, da dem Loeschen nicht zwangslaeufig*
*                        ein CarDirectory-Aufruf vorausgeht.         *
*     25.03.96 -PR-    Umstellung von DATACAR_..-Funktionen auf      * 
*                      BASIC-Funktionen.                             *
*                                                                    *
*                                                                    *
*                                                                    *
*                                                                    *
*                                                                    *
*                                                                    *
*                                                                    *
*                                                                    *
*  VERSION:                                                          *
*     VERSION:  3.0              AUTOR:       Th.Epting              *
*     DATUM:    13.02.92         TELEFON 2i:  0721/25785             *
*                                                                    *
*  UMGEBUNG:                                                         *
*     ZIELRECHNER:          IQT-350/353                              *
*     PROGRAMMIERSPRACHE:   C (MWC 4.0.3)                            *
*                                                                    *
*  BEMERKUNGEN:                                                      *
*                                                                    *
**********************************************************************
*                                                                    *
*  PROZEDUREN/FUNKTIONEN:                                            *
*     CarCreate - Anlegen einer Datei                                *
*     CarExpand - Vergroessern einer Datei                           *
*     CarRead - Lesen eines Teils einer Datei                        *
*     CarWrite - Schreiben eines Teils einer Datei                   *
*     CarDelete - Loeschen einer Datei                               *
*     CarDirectory - Lesen des Diskettenkatalogs                     *
*     CarStatus - Freien Diskettenplatz ermitteln                    *
*     CarFormat - Formattieren eines Datentraegers                   *
*     CarSetDate - Datum fuer eine Datei setzen                      *
*     CarReadDate - Datum einer Datei lesen                          *
*     CarOpen -  Oeffnen einer Datei                                 *
*     CarClose -  Schliessen einer Datei                             *
*                                                                    *
*********************************************************************/

/*.SI.***********************************************************************/
#ifndef _stddef
#include <stddef.h>
#define _stddef
#endif
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _stdlib
#include <stdlib.h>
#define _stdlib
#endif
#ifndef _stdio
#include <stdio.h>
#define _stdio
#endif
#ifndef _ctype
#include <ctype.h>
#define _ctype
#endif
#ifndef _string
#include <string.h>
#define _string
#endif
#ifndef _errcode
#include <errcode.h>
#define _errcode
#endif
#ifndef _diskxy
#include <diskxy.h>
#define _diskxy
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

/*********************************************************************
X  EXTERNE VARIABLEN UND PROZEDURDEN
*********************************************************************/

/*********************************************************************
X  MODULINTERNE KONSTANTEN
*********************************************************************/

#define LEN_FNAME   8   /* Max. Laenge eines Dateinamens */
#define LEN_EXTEN   3   /* Max. Laenge einer Dateierweiterung */

#define BUF_LEN  1024   /* Puffergroesse fuer ersten Sektor */

#define OFFS_HEADER 3   /* Offset fuer Datentraeger-Header */
#define OFFS_SECCNT 3   /* Anzahl Sektoren dieser Partition */
#define OFFS_SPINFO 4   /* Sektorgroesse und Partitionsinformation */
#define OFFS_DIRCNT 5   /* Anzahl Directory-Eintraege */
#define OFFS_DISKID 8   /* Disk-ID */

#define CERR_INVALID_DISKID 0x0080   /* Adressierungsfehler */
#define CERR_INVALID_SPINFO 0x0040   /* Adressierungsfehler */
#define CERR_ADDRESS      0x0020   /* Adressierungsfehler */
#define CERR_NO_EEPROM    0x0010   /* Kein EE-Prom ? */
#define CERR_NO_DIR_ENTRY 0x0800   /* Kein Directoryeintrag frei */
#define CERR_FILE_EXISTS  0x0400   /* Anzulegende Datei existiert schon */
#define CERR_PAST_EOF     0x0200   /* Dateiende ueberschritten (Read/Write) */
#define CERR_NO_FILE      0x0100   /* Datei nicht gefunden */
#define CERR_NO_DEVICE    0x8000   /* Kein Datentraeger angeschlossen */
#define CERR_WRITE_FAULT  0x4000   /* Fehler beim Schreiben */
#define CERR_PROG_PULSE   0x2000   /* Programmier-Impuls zu lang */
#define CERR_HARDWARE     0x1000   /* Hardwarefehler */
#define CERR_WRONG_FORMAT 0x0008   /* Falsches Datentraeger-Format */
#define CERR_DIR_FULL     0x0004   /* Kein freier Platz im Directory */
#define CERR_DISK_FULL    0x0002   /* Kein freier Platz auf Datentraeger */
#define CERR_MEMORY_FULL  0x0001   /* Kein freier (interner) Speicherplatz */

/* MACRO UM DIAGNOSE-MELDUNGEN ZU SICHERN
**
** UEBERNIMMT: (BYTE) err - ein DEVDISK-typischer Fehlercode
**             (BYTE) hnd - das Handle des betroffenen Fensters
**             (USR_WORD) num - spezifischer Zusatzparameter
**
** ... und so werden die drei Informationen im USR_LONG-Parameter kodiert:
**             +-----------+-----------+----------+
**             |31  err  24|23  hnd  16|15  num  0|
**             +-----------+-----------+----------+
*/
/*********************************************************************
*  CARF_INIT - Prolog-Code einer externen Carrier-Funktion
*  CARF_EXIT - Epilog-Code einer externen Carrier-Funktion
*********************************************************************/

#define CARF_INIT   int _err; SemP(&CarrierSema); CarError=USR_NO_ERROR; {
#define CARF_EXIT   } _err=CarError; SemV(&CarrierSema); return CarHandleError(fcb,_err);

/* Die ersten 3 Bytes nicht schreiben! (Interface fuer Cassetten-   *
 * Cassettenrecorder)                                               */
#define CASSOFFS 3 /* 0 */

/*********************************************************************
X  MODULINTERNEN DATENTYPEN
*********************************************************************/

/* #pragma noalign("_h") */

#include "Pack_1"

typedef struct _h {/* = HEADER EINES DATENTRAEGERS ================ */
   USR_BYTE seccnt;      /* Anzahl der Sektoren (1..254)                */
   USR_BYTE spinfo;      /* Sektorgroesse und Partitionsinformationen   */
	USR_BYTE dircnt;      /* Anzahl der Verzeichniseintraege (1..255)    */
   USR_WORD reserved;    /* Reserviert fuer Erweiterungen...            */
   USR_WORD diskid;      /* ID des Datentraegers (Bit15,14=10)          */
} HEADER;

typedef struct { /* === PARTITIONS-INFORMATIONEN ================== */
	USR_WORD StartAdr;    /* Startadresse der Partition im Datentraeger  */
	short SectorSize;   /* Groesse eines Sektors der Partition         */
	short Sectors;      /* Anzahl Sektoren in der Partition            */
	short DirEntries;   /* Anzahl Directory-Eintraege in der Partition */
	short DiskID;       /* Bits 0..13 des DISKID-Feldes                */
	USR_BOOL LastPart;    /* Ist dies die letzte Partition des Carriers? */
} PARTINFO;

typedef struct { /* === VERWALTUNGSSTRUKTUR FUER FAT ============== */
   PARTINFO Part;    /* Zeiger auf Partitionsinformation            */
   USR_BYTE *Fat;        /* Zeiger auf Speicherbereich fuer FAT         */
   USR_BOOL Update;      /* Flag, ob FAT-Update notwendig               */
} FAT;

typedef struct _d {/* = DIRECTORY-EINTRAG ========================= */
   char Name[8];     /* Dateiname (rechtsbuendig Leerstellen)       */
   char Ext[3];      /* Dateierweiterung (rechtsbuendig Leerst.)    */
   USR_WORD Date;        /* Datum der letzten Aenderung                 */
   USR_WORD Time;        /* Uhrzeit der letzten Aenderung               */
   USR_BYTE Start;       /* Erster benutzter Sektor                     */
	short Length;      /* Laenge des letzten Sektors                  */
} DIRENTRY;

typedef struct { /* === VERWALTUNGSSTRUKTUR FUER DATEIEN ========== */
   FAT     *Fat;     /* Zeiger auf FAT-Bereich                      */
   DIRENTRY Dir;     /* Bereich fuer Directory-Eintrag              */
	short     Offs;    /* Offset des Directory-Eintrages in Partition */
	short     Sector;  /* Nummer des aktuellen Sektors                */
	USR_BOOL     Update;  /* Flag, ob Dir-Update notwendig               */
} FILECTRL;

#include "Unpack"

/*********************************************************************
X  MODULINTERNE VARIABLEN
*********************************************************************/
/* Zu einem Zeitpunkt darf nur ein Task rumwurschteln */
 static SEMAPHORE CarrierSema;

/* Aktuelle Fehlernummer. Nur in geschuetzten Abschnitten benutzt! */
 static int CarError;

/* Spezifische Laufwerksnummer */
 static int CarDrive;

/* Pufferung des ersten Sektors */
 static int BufDrive;
 static int BufModify;
 static char BufSector[BUF_LEN];


/*********************************************************************
X  MODULINTERNE PROZEDURDEKLARATIONEN
*********************************************************************/

#define STATIC static
#define NEW_FORMAT      /* Alte, geringfuegig abgeaenderte Formatroutine *NB*/
 STATIC int CarHandleError( FCB_PTR fcb , int err );
        int CarrierIO( int order , USR_BYTE * buf , USR_WORD n , USR_WORD offs );
 STATIC int ReadDrv2( USR_BYTE * buf, USR_WORD n, USR_WORD offs );
 STATIC int WriteDrv2( USR_BYTE * buf, USR_WORD n, USR_WORD offs );
 STATIC int SelectCarrier( void );
 STATIC int FlushCarrier( void );
 STATIC int ReadCarrier( char * buf , USR_WORD n , USR_WORD offs );

/*********************************************************************
*  VERBINDUNG ZUM ELTER-MODUL DEVDISK
*********************************************************************/

 int /*errflag*/ CarCreate( FCB_PTR fcb , USR_LONG len );
 int /*errflag*/ CarExpand( FCB_PTR fcb , USR_LONG len );
 int /*errflag*/ CarRead( FCB_PTR fcb , USR_BYTE *buffer , USR_LONG len , USR_LONG pos );
 int /*errflag*/ CarWrite( FCB_PTR fcb , USR_BYTE *buffer , USR_LONG len , USR_LONG pos );
 int /*errflag*/ CarDelete( FCB_PTR fcb );
 int /*errflag*/ CarStatus( FCB_PTR fcb , USR_LONG *avail );
 int /*errflag*/ CarFormat( FCB_PTR fcb );
 int /*errflag*/ CarSetDate( FCB_PTR fcb , USR_WORD date , USR_WORD time );
 int /*errflag*/ CarReadDate( FCB_PTR fcb , USR_WORD *date , USR_WORD *time );
 int /*errflag*/ CarDirectory( FCB_PTR fcb , void (*callback)() );
 int /*errflag*/ CarInit();
 int /*errflag*/ CarRestore( FCB_PTR fcb , USR_BYTE mode );
 int /*errflag*/ CarOpen( FCB_PTR fcb );
 int /*errflag*/ CarClose( FCB_PTR fcb );

 const DISKMOD_TYP CarrierModule = {
   CarInit,CarRestore,CarCreate,CarExpand,CarRead,CarWrite,CarDelete,
   CarDirectory,CarSetDate,CarReadDate,CarStatus,CarFormat,CarOpen,CarClose };


/*********************************************************************
X  FEHLERBEHANDLUNG
*
*  int CarHandleError(fcb,err) - Wertet den internen Fehlercode 'err'
*     aus und wandelt den Fehlercode in den externen Fehler um, der
*     in 'fcb' abgelegt wird. Abhaengig vom Fehlerstatus wird ERROR
*     oder USR_NO_ERROR zurueckgeliefert.
*
*********************************************************************/

STATIC int CarHandleError( FCB_PTR fcb , int err )
{
   If (err <= 0 ) Then
      return err;
   Else
      If ( err & CERR_MEMORY_FULL ) Then return ERR_DRAM_ALLOC;
      Elseif ( err & CERR_INVALID_SPINFO ) Then return ERR_INVALID_SPINFO;
      Elseif ( err & CERR_INVALID_DISKID ) Then return ERR_INVALID_DISKID;
		Elseif ( err & CERR_NO_DEVICE ) Then return ERR_NO_DEVICE;
      Elseif ( err & CERR_PROG_PULSE ) Then return ERR_HARDWARE;
      Elseif ( err & CERR_HARDWARE ) Then return ERR_HARDWARE;
      Elseif ( err & CERR_WRONG_FORMAT ) Then return ERR_CAR_WRONG_FORMAT;
      Elseif ( err & CERR_NO_EEPROM ) Then return ERR_CAR_NO_EEPROM;
      Elseif ( err & CERR_WRITE_FAULT ) Then return ERR_WRITE;
      Elseif ( err & CERR_ADDRESS ) Then return ERR_CAR_ADDRESS;
      Elseif ( err & CERR_DISK_FULL ) Then return ERR_DEVICE_FULL;
      Elseif ( err & CERR_NO_DIR_ENTRY ) Then return ERR_DIR_FULL;
      Elseif ( err & CERR_DIR_FULL ) Then return ERR_DIR_FULL;
      Elseif ( err & CERR_FILE_EXISTS ) Then return ERR_MULTIPLE_FILE;
      Elseif ( err & CERR_NO_FILE ) Then return ERR_FILE_NOT_FOUND;
      Elseif ( err & CERR_PAST_EOF ) Then return ERR_PAST_END;
      Else return ERR_UNKNOWN;
      Endif
   Endif
}

/* Ein paar Konstanten fuer die Datentraegererkennung *NB*/
#define CAR_AUTO_SELECT 0     /* Bestimmen des Carrier-Typs durch Philips (schluck) */
#define SELECT_CARRIER  0x10  /* Order-Nummer */

/*********************************************************************
X  BASIC-I/O ZUM DATENTRAEGER
*
*  Die ersten BUF_LEN Bytes eines Datentraegers werden zusaetzlich ge-
*  puffert (zwecks Performance-Steigerung).
*
*  int ReadCarrier(buf,n,offs) - Liest einen Datenblock der Laenge 'n'
*     ab der relativen Position 'offs' nach Adresse 'buf'.
*
*  int WriteCarrier(buf,n,offs) - Schreibt einen Datenblock der
*     Laenge 'n' von Adresse 'buf' zu der relativen Position 'offs'.
*
*  int FlushCarrier() - Schreibt den gepufferten ersten Sektor auf den
*     Datentraeger zurueck (falls geaendert).
*
*  --- INTERN ---
*
*
*  int CarrierIO(order,buf,n,offs) - Fuellt einen MRB-Block fuer
*     Datentraeger-IO aus. Order gibt an, ob eine Lese- (0) oder eine
*     Schreiboperation (1) durchgefuehrt werden soll. Neuerdings kann
*     durch Angabe von Order 2 der Datentraeger ueber die neue Tasta-
*     turkarte gelesen bzw. bei Order 3 beschrieben werden.
*
*  int ReadDrv2(buf,n,offs) - Liest einen Bereich aus dem E-Quadrat
*     der Interfacekarte (Beim IQT353 handelt es sich um "gelochte"
*     Daten (nur HIGH-Bytes sind gueltig)).
*
*  int WriteDrv2(buf,n,offs) - Schreibt einen Bereich in das E-Quadrat
*     der Interfacekarte (Beim IQT353 handelt es sich um "gelochte"
*     Daten (nur HIGH-Bytes sind gueltig)).
*
*  int ReadKPROM(buf,n,offs,ctrl) - Liest einen Bereich aus dem "gelochten"
*     Kunden-PROM (ctrl=0 ==> LOW-Bytes / ctrl=1 ==> HIGH-Bytes).
*     Ausgelagert in DISKCAR1.C wegen Overlayhandling (06.09.91 TSchw)
*
*********************************************************************/

#define DATACAR_CHECK           0x01
#define DATACAR_READ            0x02
#define DATACAR_WRITE           0x03

int BASIC_Check(void);
int BASIC_Read(long address, long size, void * buffer);
int BASIC_Write(long address, long size, void * buffer);

int CarrierIO( int order , USR_BYTE * buf , USR_WORD n , USR_WORD offs )
{  int status = USR_NO_ERROR, retries = 4;

   Switch ( order )
   Case 0:
      status = BASIC_Read(offs, n, buf);
      If (status == 0) Then
           status = USR_NO_ERROR;
      Endif
      break;
   Case 1:
      For (status=-1; retries && (status < 0); retries--) Do
         status = BASIC_Write(offs, n, buf);
         If (status == 0) Then
            status = USR_NO_ERROR;
         Endif
      Endfor
      break;
    Case SELECT_CARRIER:
    Case SELECT_CARRIER+2:
      status = BASIC_Check();
      If (status > 0) Then
         *buf = (USR_BYTE) (status); /* 4,8,16,32,64 KB */
         status = USR_NO_ERROR;
      Else
         *buf = 0;
      Endif
      break;
   Endswitch
#ifdef lassma
      Switch (status)
      Case      DCAR_BAD_TYP:
         status = CERR_WRONG_FORMAT;
         break;
      Case      DCAR_NOT_FOUND:
         status = CERR_NO_DEVICE;
         break;
      Case      DCAR_VERIFY_ERROR:
         status = CERR_WRITE_FAULT;
         break;
      Case      DCAR_NO_EEPROM  :
         status = CERR_NO_EEPROM;
         break;
      Case      DCAR_NOT_READY  :
         status = CERR_NO_DEVICE;
         break;
      Case      DCAR_ADR_ERROR  :
         status = CERR_ADDRESS;
         break;
   Endswitch
#endif
   return status;
}

STATIC int SelectCarrier( /*void*/ )
/*
 * Stellt via CarrierIO den Datentraegertyp fest
 *
 *NB*/
{
   USR_BYTE length;

   Switch( CarDrive )
      Case CAR_DRV0:
      Case CAR_DRV1:
         CarError |= CarrierIO( SELECT_CARRIER, &length, CAR_AUTO_SELECT, 0 );
         break;
      Case CAR_DRV2:
         length = 16;
			break;
      Default:
         length = 0;
         break;
   Endswitch

   return length;
}


STATIC int FlushCarrier( /*void*/ )
{
   int err = USR_NO_ERROR;

   If ( BufDrive >= 0 && BufModify ) Then
      int olddrive = CarDrive;
      CarDrive = BufDrive;
      err = CarrierIO(1, BufSector+CASSOFFS , BUF_LEN-CASSOFFS , CASSOFFS );
      BufModify = 0;
      CarDrive = olddrive;
   Endif

   return err;
}

STATIC int ReadCarrier( char * buf , USR_WORD n , USR_WORD offs )
{
   int err = USR_NO_ERROR;
	int cpylen;

   If ( offs < BUF_LEN ) Then
      If ( CarDrive != BufDrive ) Then
         err  = FlushCarrier( );
         SelectCarrier();
         err |= CarrierIO(0, BufSector , BUF_LEN , 0 );
         BufDrive = (err==USR_NO_ERROR) ? CarDrive : -1;
      Endif
      cpylen = MIN( n , BUF_LEN-offs );
      memcpy( buf , BufSector+offs , cpylen );
      buf += cpylen;
      offs += cpylen;
      n -= cpylen;
   Endif

   err = ( err==USR_NO_ERROR && n>0 ) ? CarrierIO(0, buf , n , offs ) : err;
   return err;

}

STATIC int WriteCarrier( char * buf , USR_WORD n , USR_WORD offs )
{
	int err = USR_NO_ERROR;
   int cpylen;

   If ( offs < BUF_LEN ) Then
      If ( CarDrive != BufDrive ) Then
         err  = FlushCarrier( );
         err |= CarrierIO(0, BufSector , BUF_LEN , 0 );
         BufDrive = (err==USR_NO_ERROR) ? CarDrive : -1;
      Endif
      BufModify = 1;
      cpylen = MIN( n , BUF_LEN-offs );
      memcpy( BufSector+offs , buf , cpylen );
      buf += cpylen;
      offs += cpylen;
      n -= cpylen;
   Endif

   return ( err==USR_NO_ERROR && n>0 ) ? CarrierIO( 1, buf , n , offs ) : err;
}


/*********************************************************************
X  LOW-LEVEL-I/O
*
*  Diese Funktionen liefern einen Fehlercode ungleich 0 zurueck, wenn
*  kein oder kein gueltiger Datentraeger vorhanden ist, wenn die Par-
*  tition nicht bekannt ist oder ein Schreib-/Lesefehler aufgetreten
*  ist. Der Fehlercode ist in der globalen Variablen 'CarError' ge-
*  speichert.
*
*  int ReadBlock(ppinfo,offs,buf,n) - liest einen Datenblock von 'n'
*     Bytes aber der relativen Position 'offs' der 'ppinfo'-Partition
*     in den Puffer 'buf' ein.
*
*  int WriteBlock(ppinfo,offs,buf,n) - schreibt einen Datenblock von
*     'n' Bytes aus dem Puffer 'buf' an die relative Position 'offs'
*     der 'ppinfo'-Partition.
*
*  int GetPartInfo(p,ppinfo) - ermittelt die Werte einer Partition
*     Partition 'p' in 'ppinfo'.
*
*********************************************************************/

#define ReadBlock( ppinfo , offs , buf , n )  \
   ( CarError |= ReadCarrier(((char*)buf),(n),(ppinfo)->StartAdr+(offs)) )

#define WriteBlock( ppinfo , offs , buf , n )  \
   ( CarError |= WriteCarrier(((char*)buf),(n),(ppinfo)->StartAdr+(offs)) )

STATIC int /*err*/ GetPartInfo( int p , PARTINFO * ppinfo )
{
   HEADER header;

   ppinfo->SectorSize = 256;
   ppinfo->DirEntries = 1;

	if (CarError |= ReadCarrier(&header, sizeof(HEADER), OFFS_HEADER)) return CarError;
// PR 12.09.2001 Die Ueberpruefung der Disk Id ist unzuverlaessig, wenn keine
// Partitionen verwendet werden. Dann werden alle weiteren Informationen des
// Worts nicht benoetigt und nicht belegt.
//   if ( (header.diskid & 0xc000) != 0x8000 ) return (CarError |= CERR_INVALID_DISKID);
   if (header.diskid != 0x8000) return (CarError |= CERR_INVALID_DISKID);

   ppinfo->DiskID     = header.diskid & 0x3fff;
   ppinfo->StartAdr   = 0;
   ppinfo->SectorSize = 256 << (header.spinfo & 0x03);

   While ( p-- ) Do
      If ( p > 0 ) Then
         ppinfo->StartAdr += header.seccnt * (USR_WORD) ppinfo->SectorSize
            + ((header.seccnt+header.dircnt*sizeof(DIRENTRY)+271)/ppinfo->SectorSize)
                * ppinfo->SectorSize;
         if ( (header.spinfo & 0x80) != 0x00 ) return (CarError |= CERR_INVALID_SPINFO);
         if ( ReadBlock(ppinfo,OFFS_HEADER,&header,sizeof(HEADER)) != USR_NO_ERROR ) return CarError;
         ppinfo->SectorSize = 256 << (header.spinfo & 0x03);
      Endif
   Endwhile

   ppinfo->Sectors    = header.seccnt;
   ppinfo->DirEntries = header.dircnt;
   ppinfo->LastPart   = (header.spinfo & 0x80) == 0x80 ? TRUE : FALSE;

   return USR_NO_ERROR;
}


/*********************************************************************
X  VERWALTUNG DER FILE ALLOCATION TABLE (FAT)
*
*  FAT * LockFat(ppinfo) - Allokiert Speicherplatz fuer die FAT der
*     Partition 'ppinfo' und laedt die FAT. Wenn kein Speicherplatz
*     zur Verfuegung stand, wird NULL zurueckgegeben.
*
*  int ReleaseFat(pfat) - Schreibt die FAT zurueck (falls Update not-
*     wendig) und gibt den belegten Speicherplatz wieder frei. Wenn
*     die Schreiboperation nicht geklappt hat, wird ERROR gemeldet.
*
*  int AllocFatEntry(pfat,n) - Belegt den naechsten freien Eintrag der
*     FAT 'pfat', liefert dessen Nummer zurueck und fuehrt die Ver-
*     kettung zum Vorgaengereintrag 'n' durch. Wenn 'n' == 0, wird
*     keine Verkettung durchgefuehrt. Wenn der Rueckgabewert == 0,
*     war kein Platz mehr vorhanden.
*
*  int FreeFatEntry(pfat,n) - Gibt den 'n'-ten Eintrag der FAT 'pfat'
*     wieder frei. Wenn der freizugebende FAT-Eintrag in einer Ver-
*     kettung stand, wird diese aufgehoben. Diese Funktion liefert
*     die Nummer des Nachfolgers in der Verkettung oder 0xff, falls
*     kein solcher vorhanden war.
*
*  int PartSpace(pfat) - ermittelt die Anzahl freier Bytes, die durch
*     eine neue Datei belegt werden kann, innerhalb einer durch die
*     FAT 'pfat' gegebenen Partition.
*
*  int GetNextSector(pfat,sec) - Ermittelt den in der FAT-Verkettung
*     der FAT 'pfat' dem Sektor 'sec' folgenden Sektor.
*
*********************************************************************/
 STATIC FAT * /*pfat*/ LockFat( PARTINFO * ppinfo );
 STATIC int /*err*/ ReleaseFat( FAT * pfat );
 STATIC int /*entry*/ AllocFatEntry( FAT * pfat , int n );
 STATIC int FreeFatEntry( FAT * pfat , int n );
 STATIC USR_WORD PartSpace( FAT * pfat );


STATIC FAT * /*pfat*/ LockFat( PARTINFO * ppinfo )
{
   FAT * fat = (FAT*)MemAlloc( sizeof(FAT) );

   If ( fat != NULL ) Then
      If ( (fat->Fat=(USR_BYTE*)MemAlloc(ppinfo->Sectors)) == NULL ) Then
         MemFree( fat );
         CarError |= CERR_MEMORY_FULL;
         return NULL;
      Endif
      If ( ReadBlock( ppinfo , ppinfo->DirEntries*sizeof(DIRENTRY)+16 ,
             fat->Fat , ppinfo->Sectors ) != USR_NO_ERROR ) Then
         MemFree( fat->Fat ); MemFree( fat );
         return NULL;
      Endif
      fat->Update = FALSE;
      memcpy( &fat->Part , ppinfo , sizeof(PARTINFO) );
   Else
      CarError |= CERR_MEMORY_FULL;
   Endif

   return fat;
}

STATIC int /*err*/ ReleaseFat( FAT * pfat )
{
   If ( pfat->Update ) Then
      WriteBlock( &pfat->Part ,
           pfat->Part.DirEntries*sizeof(DIRENTRY)+16 ,
           pfat->Fat , pfat->Part.Sectors );
   Endif

   MemFree( pfat->Fat );
   MemFree( pfat );

   return CarError;
}

STATIC int /*entry*/ AllocFatEntry( FAT * pfat , int n )
{
   int i;
   USR_BYTE * fat = pfat->Fat;

   For ( i=1 ; i<=pfat->Part.Sectors ; i++,fat++ ) Do
      If ( *fat == 0 ) Then
         If ( n != 0xff ) Then
            *fat = pfat->Fat[n-1];
            pfat->Fat[n-1] = i;
			Else
            *fat = 0xff;
         Endif
         pfat->Update = TRUE;
         return i;
      Endif
   Endfor

   return 0;
}

STATIC int FreeFatEntry( FAT * pfat , int n )
{
   int i;
   int next = 0xff;
   USR_BYTE * fat = pfat->Fat;

   If ( n <= pfat->Part.Sectors ) Then
      For ( i=0 ; i<=pfat->Part.Sectors ; i++,fat++ ) Do
         If ( *fat == n ) Then
            *fat = pfat->Fat[n-1];
         Endif
      Endfor
      next = pfat->Fat[n-1];
      pfat->Fat[n-1] = 0;
      pfat->Update = TRUE;
   Endif

	return next;
}

STATIC USR_WORD PartSpace( FAT * pfat )
{
   int i;
   USR_WORD space = 0;
   int sectors = pfat->Part.Sectors;
   USR_BYTE * fat = pfat->Fat;

   For ( i=0 ; i<sectors ; i++ ) Do
      If ( *fat++ == 0 ) Then space++; Endif
   Endfor

   return space * pfat->Part.SectorSize;
}

#define GetNextSector( pfat , sec )\
   ( (sec)==0 || (sec)==0xff ? 0xff : (pfat)->Fat[(sec)-1] )

/*********************************************************************
X  VERWALTUNG VON DIRECTORIES (ALLGEMEIN)
*
*  char * CfnCopyExtInt(extfn,intfn,n) - Interne Hilfsfunktion. Ko-
*     piert max. n Zeichen von extfn nach intfn. '.', '*' und '\0'
*     brechen den Kopiervorgang ab. Abhaengig vom Abbruchzeichen wird
*     der Rest mit '?' oder mit ' ' aufgefuellt. Ausserdem wird der
*     Zeiger auf den nachfolgenden Teil des Dateinamens oder auf '\0'
*     zurueckgegeben
*
*  void CfnExtInt(extfn,intfn) - Wandelt einen externen Dateinamen
*     (Schreibweise mit '*' und '.') in einen internen Dateinamen um.
*     Interne Dateinamen sind genau 11 Bytes lang und haben ein ' '-
*     Zeichen an unbenutzen und ein '?'-Zeichen an Wildcard-Stellen.
*     Ausserdem sind Kleinbuchstaben in internen Dateinamen verboten.
*     'intfn' zeigt auf einen mind. 12 Bytes grossen Block.
*
*  void CfnIntExt(intfn,extfn) - Wandelt einen internen Dateinamen
*     int einen externen Dateinamen um. 'extfn' zeigt auf einen mind.
*     13 Bytes grossen Block.
*
*  USR_BOOL MatchFileName(fn1,fn2) - 'fn1' und 'fn2' sind Stringzeiger
*     auf je 11 Zeichen lange, nicht notwendigerweise Nullterminierte
*     Strings in der internen Dateinamenkonvention. Wenn die Datei-
*     namen-Muster passen, wird TRUE, ansonsten FALSE zurueckgegeben.
*
*  USR_BOOL FileDeleted(fchar) - Prueft anhand des ersten Zeichens 'fchar'
*     des Dateinamens, ob es sich um eine geloeschte Datei handelt
*     (TRUE) oder nicht (FALSE).
*
*********************************************************************/
 STATIC char * CfnCopyExtInt( char * extfn , char * intfn , int n );
 STATIC void CfnExtInt( char * extfn , char * intfn );
 STATIC void CfnIntExt( char * intfn , char * extfn );
 STATIC USR_BOOL MatchFileName( char * fn1 , char * fn2 );

STATIC char * CfnCopyExtInt( char * extfn , char * intfn , int n )
{
	int fill_rest = 0;

	While ( n > 0  &&  fill_rest == 0 ) Do
		Switch ( *extfn )
		 Case '\0': Case '.': fill_rest = ' '; break;
		 Case '*':            fill_rest = '?'; break;
		 Default:
			 *intfn++ = islower(*extfn) ? toupper(*extfn) : *extfn;
			 extfn++;
          n--;
      Endswitch
   Endwhile

   While ( n-- > 0 ) Do
      *intfn++ = fill_rest;
   Endwhile

   While ( *extfn != '.'  &&  *extfn != '\0' ) Do
      extfn++;
   Endwhile

   return *extfn=='.' ? extfn+1 : extfn;
}

STATIC void CfnExtInt( char * extfn , char * intfn )
{
   If ( extfn==NULL || *extfn=='\0' ) Then extfn = "*.*"; Endif
   extfn = CfnCopyExtInt( extfn , intfn , LEN_FNAME );
   CfnCopyExtInt( extfn , intfn+LEN_FNAME , LEN_EXTEN );
   intfn[LEN_FNAME+LEN_EXTEN] = '\0';
}

STATIC void CfnIntExt( char * intfn , char * extfn )
{
   int i;

   For ( i=0 ; i<LEN_FNAME ; i++,intfn++ ) Do
      If ( *intfn != ' ' ) Then
         *extfn++ = *intfn;
      Endif
   Endfor

   *extfn++ = '.';

   For ( i=0 ; i<LEN_EXTEN ; i++,intfn++ ) Do
      If ( *intfn != ' ' ) Then
         *extfn++ = *intfn;
      Endif
   Endfor

   *extfn = '\0';
}

STATIC USR_BOOL MatchFileName( char * fn1 , char * fn2 )
{
   int i;

   For ( i=0 ; i<LEN_FNAME+LEN_EXTEN ; i++,fn1++,fn2++ ) Do
      If ( *fn1 != '?'  &&  *fn2 != '?'  &&  *fn1 != *fn2 ) Then
         return FALSE;
      Endif
   Endfor

   return TRUE;
}

#define FileDeleted( fchar ) \
   ( ((unsigned char)fchar) < 33 || ((unsigned char)fchar) > 127  ?  TRUE  :  FALSE )

/*********************************************************************
X  VERWALTUNG DES DIRECTORIES EINER PARTITION
*
*  int SearchFile1p(ppinfo,intfn) - Sucht im Directory der Partition
*     'ppinfo' die Datei mit internem Dateinamen 'intfn'. Liefert
*     den Offset des Verzeichniseintrages innerhalb der Partition,
*     falls Datei gefunden, oder den negativen Offset eines freien
*     Eintrages, falls Datei nicht gefunden, oder 0, falls kein
*     Eintrag mehr frei.
*
*********************************************************************/
STATIC int SearchFile1p( PARTINFO * ppinfo , char * intfn )
{
   int i;
   int first_free = 0;
   DIRENTRY dir;

   For ( i=0 ; i<ppinfo->DirEntries ; i++ ) Do
      ReadBlock( ppinfo , 16+i*sizeof(DIRENTRY) , &dir , sizeof(DIRENTRY) );
      If ( first_free==0 && FileDeleted(dir.Name[0]) ) Then
         first_free = -(16+i*(int)sizeof(DIRENTRY));
      Elseif ( MatchFileName( &dir.Name[0] , intfn ) ) Then
         return 16+i*sizeof(DIRENTRY);
      Endif
   Endfor

   return first_free;
}

/*********************************************************************
X  VERWALTUNG DER DIRECTORIES ALLER PARTITION
*
*  int SearchFile(ppinfo,intfn) - Durchsucht alle Partitions-Direc-
*     tories nach einer Datei 'intfn'. Falls gefunden, wird ein Off-
*     set innerhalb einer Partition, inclusive deren Partitions-
*     info-Record zurueckgeliefert. Anderenfalls wird 0 zurueckge-
*     geben.
*
*  USR_BOOL FindSpace(pfat,n) - Durchsucht alle Partitionen danach, ob
*     ein allokierbarer Platz von 'n' Bytes in einer beschreib-
*     baren Partition vorhanden sind. Wenn gefunden, wird TRUE zu-
*     geliefert und 'pfat' enthaelt den Zeiger auf die FAT-Struktur.
*     Ansonsten wird FALSE geliefert.
*
*  long FreeSpace() - Ermittelt die Anzahl ungenutzter Bytes aller
*     Partitionen. Diese Zahl errechnet sich aus der Anzahl unbe-
*     legter Sektoren innerhalb der einzelnen Partitionen.
*
*********************************************************************/
 STATIC int SearchFile( PARTINFO * ppinfo , char * intfn );
 STATIC USR_BOOL FindSpace( FAT * * pfat , USR_WORD n );
 STATIC long FreeSpace(void);

STATIC int SearchFile( PARTINFO * ppinfo , char * intfn )
{
   int pos = 0;
   int part = 0;

   Repeat
      If ( GetPartInfo( part++ , ppinfo ) == USR_NO_ERROR ) Then
         pos = SearchFile1p( ppinfo , intfn );
      Endif
   Until ( CarError  ||  ppinfo->LastPart  ||  pos > 0 );

   return ( pos > 0 )  ?  pos  :  0;
}

STATIC USR_BOOL FindSpace( FAT * * pfat , USR_WORD n )
{
   int part = 0;
   PARTINFO ppinfo;

   Repeat
      If ( GetPartInfo( part++ , &ppinfo ) == USR_NO_ERROR ) Then
         If ( (*pfat=LockFat( &ppinfo )) == NULL ) Then
            return FALSE;
         Elseif ( PartSpace( *pfat ) >= n ) Then
            return TRUE;
         Else
            ReleaseFat( *pfat );
         Endif
      Endif
   Until ( CarError  ||  ppinfo.LastPart );

   return FALSE;
}

STATIC long FreeSpace( )
{
   int part = 0;
   long space = 0L;
   FAT *fat;
   PARTINFO ppinfo;

   Repeat
      If ( GetPartInfo( part++ , &ppinfo ) == USR_NO_ERROR ) Then
         If ( (fat=LockFat( &ppinfo )) == NULL ) Then
            return 0L;
         Endif
         space += (long)PartSpace( fat );
         ReleaseFat( fat );
      Elseif ( CarError & CERR_WRONG_FORMAT ) Then
         CarError &= ~CERR_WRONG_FORMAT;
         return 4096L; /* Laenge kompatibler Datentraeger */
      Endif
   Until ( CarError  ||  ppinfo.LastPart );

   return space;
}

/*********************************************************************
X  VERWALTUNG VON DATEIEN
*
*  FILECTRL * FindFile(extfn) - Durchsucht alle Partitionen nach
*     einer Datei mit dem Namen 'extfn'.
*
*  FILECTRL * MakeFile(extfn,len) - Durchsucht alle beschreibbaren
*     Partitionen nach einem Freiraum der Laenge 'len' und legt
*     falls gefunden) dort eine Datei mit dem Namen 'extfn' an.
*     Wenn eine Datei dieses Namens bereits existiert, wird sie
*     entsprechend erweitert/verkuerzt.
*
*  Anmerkung:
*     Obige Funktionen liefern im Erfolgsfall einen Zeiger auf eine
*     FILECTRL-Struktur, die nach Beendigung der Arbeit mittels
*     ReleaseFile() freigegeben werden muss. Bei Misserfolg wird
*     NULL geliefert.
*
*  int ReleaseFile(fc) - Gibt alle mit 'fc' verbundenen Ressourcen
*     wieder frei. Diese Funktion schreibt (falls noetig) den Ver-
*     zeichniseintrag bzw. die FAT auf den Datentraeger (zurueck).
*     ERROR wird gemeldet, wenn einer dieser Schreibvorgaenge nicht
*     ordnungsgemaess durchgefuehrt werden konnte.
*
*  int FileSize(fc) - Liefert die Laenge der Datei in Bytes.
*
*  int ChangeFileSize(fc,len) - Veraendert die Groesse einer Datei
*     auf 'len' Bytes. ERROR wird zurueckgegeben, wenn diese Aen-
*     derung nicht durchgefuehrt werden konnte.
*
*  RemoveFile(fc) - Loescht den Verzeichniseintrag durch Setzen
*     des ersten Zeichens des Dateinamens auf SPACE (32 Dezimal).
*
*  PosFile(fc,pos) - Positioniert die Datei 'fc' auf den Sektor 'pos',
*     wobei der erste Sektor die Nummer 0 hat.
*
*  ReadFile(fc,buf,off,len) - Liest ab dem Offset 'off' des aktuellen
*     Sektors der Datei 'fc' genau 'len' Bytes in den Puffer 'buf'.
*
*  WriteFile(fc,buf,off,len) - Schreibt 'len' Bytes aus dem Puffer
*     'buf' in die Datei 'fc' auf den aktuellen Sektor ab 'off'.
*
*********************************************************************/
 STATIC FILECTRL * FindFile( char * extfn );
 STATIC FILECTRL * MakeFile( char * extfn , int len );
 STATIC int ReleaseFile( FILECTRL * fc );
 STATIC int FileSize( FILECTRL * fc );
 STATIC int ChangeFileSize( FILECTRL * fc , int newlen );
 STATIC void PosFile( FILECTRL * fc , int pos );


STATIC FILECTRL * FindFile( char * extfn )
{
   int pos;
   FILECTRL * fc;
   PARTINFO ppinfo;
   char intfn[LEN_FNAME+LEN_EXTEN+1];

   CfnExtInt( extfn , intfn );

   If ( (pos=SearchFile(&ppinfo,intfn)) == 0  ||
        (fc=(FILECTRL*)MemAlloc(sizeof(FILECTRL))) == NULL ) Then
      return NULL;
   Elseif ( (fc->Fat=LockFat(&ppinfo)) == NULL ) Then
      MemFree( fc );
      return NULL;
   Endif

   ReadBlock( &fc->Fat->Part , pos , &fc->Dir , sizeof(DIRENTRY) );
   fc->Update = FALSE;
   fc->Offs   = pos;
   fc->Sector = 0;

   return fc;
}

STATIC FILECTRL * MakeFile( char * extfn , int len )
{
//   int i;
   int err = USR_NO_ERROR;
   char intfn[LEN_FNAME+LEN_EXTEN+1];
   FILECTRL * fc;
   PARTINFO ppinfo;

   If ( (fc=FindFile(extfn)) != NULL ) Then

      ChangeFileSize( fc , len );

   Elseif ( (fc=(FILECTRL*)MemAlloc(sizeof(FILECTRL))) != NULL ) Then

      CfnExtInt( extfn , intfn );
      memcpy( fc->Dir.Name , intfn , LEN_FNAME+LEN_EXTEN );

      If ( SearchFile(&ppinfo,intfn) > 0 ) Then
         CarError |= CERR_FILE_EXISTS;
         err = DEV_ERROR;
      Elseif ( ! FindSpace(&fc->Fat,len) ) Then
         CarError |= CERR_DISK_FULL;
         err = DEV_ERROR;
      Else
         fc->Sector = 0;
         fc->Offs   = - SearchFile1p( &fc->Fat->Part , intfn );
         If ( fc->Offs > 0 ) Then
            fc->Dir.Date = fc->Dir.Time = 0;
            fc->Dir.Start = 0xff;
            fc->Dir.Length = 0;
            fc->Update = TRUE;
            ChangeFileSize( fc , len );
         Else
            CarError |= CERR_NO_DIR_ENTRY;
            err = DEV_ERROR;
         Endif
      Endif

   Endif

   If ( err == DEV_ERROR  &&  fc != NULL ) Then
      MemFree( fc );
      fc = NULL;
   Endif

   return fc;
}

STATIC int ReleaseFile( FILECTRL * fc )
{
   int err = USR_NO_ERROR;

   If ( fc->Update ) Then
      err = WriteBlock( &fc->Fat->Part , fc->Offs , &fc->Dir , sizeof(DIRENTRY) );
   Endif
   If ( ReleaseFat(fc->Fat)!=USR_NO_ERROR) Then
     err = DEV_ERROR;
   Endif
   MemFree (fc);

   return (err == USR_NO_ERROR) ? USR_NO_ERROR : DEV_ERROR;
}

STATIC int FileSize( FILECTRL * fc )
{
   int seccnt = 0;
   int secnum = fc->Dir.Start;

   While ( (secnum != 0xff) && (seccnt < 1000) ) Do
      secnum = GetNextSector( fc->Fat , secnum );
      seccnt++;
   Endwhile

   return ((seccnt==0) || (seccnt >= 1000)) ? 0 : (seccnt-1) * fc->Fat->Part.SectorSize + fc->Dir.Length;
}

STATIC int ChangeFileSize( FILECTRL * fc , int newlen )
{
   int oldlen = FileSize( fc );
   int newsec = newlen==0 ? 0 : (newlen-1) / fc->Fat->Part.SectorSize + 1;
   int oldsec = oldlen==0 ? 0 : (oldlen-1) / fc->Fat->Part.SectorSize + 1;
   int secnum = fc->Dir.Start;
   int presec = 0xff;
   int seccnt;
   USR_BOOL first = (secnum == 0xff);

   If ( newlen != oldlen ) Then
      If ( newsec != oldsec ) Then
         If ( newlen < oldlen ) Then
            /* Bis zum newsec-ten Sektor vorstossen ... */
            For ( seccnt=0 ; seccnt<newsec ; seccnt++ ) Do
               secnum = GetNextSector( fc->Fat , secnum );
            Endfor
            If ( newsec == 0 ) Then
               fc->Dir.Start = 0xff;
            Endif
            /* ... und alle weiteren Sektoren loeschen */
            While ( secnum != 0xff ) Do
               secnum = FreeFatEntry( fc->Fat , secnum );
            Endwhile
         Else
            /* Letzten Sektor suchen ... */
            While ( secnum != 0xff ) Do
               presec = secnum;
               secnum = GetNextSector( fc->Fat , secnum );
            Endwhile
            /* ... und (newsec-oldsec) neue Sektoren anhaengen */
            For ( seccnt=0 ; seccnt<newsec-oldsec ; seccnt++ ) Do
               secnum = presec = AllocFatEntry( fc->Fat , presec );
               If ( secnum == 0 ) Then
                  CarError |= CERR_DISK_FULL;
                  fc->Update = FALSE;
                  return DEV_ERROR;
               Elseif ( first ) Then
                  first = FALSE;
                  fc->Dir.Start = secnum;
               Endif
            Endfor
         Endif
      Endif
      fc->Dir.Length = newlen==0 ? 0 : (newlen-1) % fc->Fat->Part.SectorSize + 1;
      fc->Update     = TRUE;
   Endif

   return USR_NO_ERROR;
}

#define RemoveFile( fc ) \
   (fc)->Dir.Name[0] = ' '

STATIC void PosFile( FILECTRL * fc , int pos )
{
   int sec = fc->Dir.Start;

   While ( pos-- > 0  &&  sec != 0xff ) Do
      sec = GetNextSector( fc->Fat , sec );
   Endwhile

   fc->Sector = sec;
}

#define ReadFile( fc , buf , off , len ) \
   ReadBlock( &(fc)->Fat->Part , \
              (fc)->Sector*(fc)->Fat->Part.SectorSize+(off) , \
              (buf) , (len) )

#define WriteFile( fc , buf , off , len ) \
   WriteBlock( &(fc)->Fat->Part , \
               (fc)->Sector*(fc)->Fat->Part.SectorSize+(off) , \
               (buf) , (len) )

/*********************************************************************
X  IMPLEMENTIERUNG KOMPLETTER CARRIER-FUNKTIONEN
*********************************************************************/

/*********************************************************************
*
*  FUNKTION: CarInit - Initialisieren des DISKCAR-Moduls
*
*  AUFRUF:
*     err = CarInit( )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag (ERROR oder USR_NO_ERROR).
*
*********************************************************************/

int /*errflag*/ CarInit( )
{
   BufModify = 0;
   BufDrive = -1;
/* 25.03.96
        DATACAR_Init(1);
        DATACAR_Config(1, NULL);
 */
   return SemInit( &CarrierSema , 10 );
}

/*********************************************************************
*
*  FUNKTION: CarRestore - Ruecksetzen des DISKCAR-Moduls
*
*  AUFRUF:
*     err = CarRestore( FCB_PTR fcb , USR_BYTE mode )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag (ERROR oder USR_NO_ERROR).
*     fcb IN [FCB_PTR] - File Control Block.
*     mode IN [USR_BYTE] - Restore-Mode.
*
*********************************************************************/

int /*errflag*/ CarRestore( FCB_PTR fcb , USR_BYTE mode )
{ CARF_INIT

   PARTINFO ppinfo;

   CarDrive = fcb->DriveNr;

   Switch ( mode )
    Case MODE_INIT:
      GetPartInfo( 0 , &ppinfo );
      fcb->BlkSize    = ppinfo.SectorSize;
      fcb->DirEntries = ppinfo.DirEntries;
      break;
    Case MODE_FLUSH:
      CarError |= FlushCarrier( );
      BufDrive = -1;
      break;
    Case MODE_SYNC:
      /* Nix */
      break;
   Endswitch

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarCreate - Anlegen einer Datei
*
*  AUFRUF:
*     err = CarCreate( fcb , len )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag (ERROR oder USR_NO_ERROR).
*     fcb IN [FCB_PTR] - File Control Block.
*     len IN [USR_LONG] - Dateilaenge in Bytes.
*
*********************************************************************/

int /*errflag*/ CarCreate( FCB_PTR fcb , USR_LONG len )
{ CARF_INIT

   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=MakeFile((char*)&fcb->FileName[0],(int)len)) != NULL ) Then
      ReleaseFile( fc );
   Else
      CarError |= CERR_DISK_FULL;
   Endif

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarExpand - Vergroessern einer Datei
*
*  AUFRUF:
*     err = CarExpand( fcb , len )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag (ERROR oder USR_NO_ERROR).
*     fcb IN [FCB_PTR] - FCB.
*     len IN [USR_LONG] - neue Gesamtdateilaenge.
*
*********************************************************************/

int /*errflag*/ CarExpand( FCB_PTR fcb , USR_LONG len )
{ CARF_INIT

   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=FindFile((char*)&fcb->FileName[0])) != NULL ) Then
      ChangeFileSize( fc , (int)len );
      ReleaseFile( fc );
   Else
      CarError |= CERR_DISK_FULL;
   Endif

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarRead - Lesen eines Teils einer Datei
*
*  AUFRUF:
*     err = CarRead( fcb , buffer , len , pos )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*     buffer IN [char*] - Adresse des Datenpuffers.
*     len IN [USR_LONG] - Anzahl der zu lesenden Zeichen.
*     pos IN [USR_LONG] - Startposition in Datei.
*
*  BEMERKUNGEN:
*     Es wird immer mindestens ein Sektor gelesen, auch wenn
*     len kleiner ist. buffer muss dafuer ausreichend bemessen sein.
*
*********************************************************************/

int /*errflag*/ CarRead( FCB_PTR fcb , USR_BYTE *buffer , USR_LONG len , USR_LONG pos )
{ CARF_INIT

   int sector, offset;
   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=FindFile((char*)&fcb->FileName[0])) != NULL ) Then
      int blocklen = fc->Fat->Part.SectorSize;
      int reallen = FileSize( fc ) - (int)pos;
      If ((int)len<reallen) Then
         reallen = len;
      Elseif (reallen < (int)len) Then
         If (0>=reallen) CarError |= CERR_PAST_EOF; 
         reallen = blocklen;
      Endif
      sector = pos / fc->Fat->Part.SectorSize;
      offset = pos % fc->Fat->Part.SectorSize;
      While ( reallen > 0 ) Do
         PosFile( fc , sector++ );
         ReadFile( fc , buffer , offset , blocklen );
         offset = 0;
         reallen -= blocklen;
         buffer += blocklen;
      Endwhile
      ReleaseFile( fc );
   Elseif ( CarError & CERR_WRONG_FORMAT ) Then
      CarError &= ~CERR_WRONG_FORMAT;
      CarError |= ReadCarrier( buffer , (USR_WORD)len , (USR_WORD)pos );
   Else
      CarError |= CERR_NO_FILE;
   Endif

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarWrite - Schreiben eines Teils einer Datei
*
*  AUFRUF:
*     err = CarWrite( fcb , buffer , len , pos )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*     buffer IN [char*] - Adresse des Datenpuffers.
*     len IN [USR_LONG] - Anzahl der zu schreibenden Zeichen.
*     pos IN [USR_LONG] - Startposition in Datei.
*
*  BEMERKUNGEN:
*     Es wird immer mindestens ein Sektor geschrieben, auch wenn
*     len kleiner ist.
*********************************************************************/

int /*errflag*/ CarWrite( FCB_PTR fcb , USR_BYTE *buffer , USR_LONG len , USR_LONG pos )
{ CARF_INIT

   int sector, offset;
   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=FindFile((char*)&fcb->FileName[0])) != NULL ) Then
      int blocklen = fc->Fat->Part.SectorSize;
      int reallen = FileSize( fc ) - (int)pos;
      If (len<reallen) Then
         reallen = len;
      Elseif (reallen < len) Then
         If (0==reallen) CarError |= CERR_PAST_EOF; 
         reallen = blocklen;
      Endif
      sector = pos / fc->Fat->Part.SectorSize;
      offset = pos % fc->Fat->Part.SectorSize;
      While ( reallen > 0 ) Do
         PosFile( fc , sector++ );
         WriteFile( fc , buffer , offset , blocklen );
         offset = 0;
         reallen -= blocklen;
         buffer += blocklen;
      Endwhile
      ReleaseFile( fc );
   Elseif ( CarError & CERR_WRONG_FORMAT ) Then
      CarError &= ~CERR_WRONG_FORMAT;
      CarError |= WriteCarrier( buffer , (USR_WORD)len , (USR_WORD)pos );
   Else
      CarError |= CERR_NO_FILE;
   Endif

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarDelete - Loeschen einer Datei.
*
*  AUFRUF:
*     err = CarDelete( FCB_PTR fcb )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*
*********************************************************************/

int /*errflag*/ CarDelete( FCB_PTR fcb )
{ CARF_INIT

   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=FindFile((char*)&fcb->FileName[0])) != NULL ) Then
      ChangeFileSize( fc , 0 );
      RemoveFile( fc );
      BufModify = 1;
      fc->Update = TRUE;
      ReleaseFile( fc );
   Else
      CarError |= CERR_NO_FILE;
   Endif

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarStatus - freien Speicherplatz auf Carrier ermitteln
*
*  AUFRUF:
*     err = CarStatus( fcb , &avail )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*     avail OUT [USR_LONG*] - freier Diskettenplatz.
*
*********************************************************************/

int /*errflag*/ CarStatus( FCB_PTR fcb , USR_LONG *avail )
{ CARF_INIT

   CarDrive = fcb->DriveNr;

   *avail = FreeSpace( );

 CARF_EXIT }


#ifndef NEW_FORMAT /*NB*/

/*********************************************************************
*
*  FUNKTION: CarFormat - Formatieren eines Datentr„gers
*
*  BESCHREIBUNG:
*     Formatiert einen Datentraeger. Momentan wird eine feste Groesse
*     von 8K angenommen, und es werden 31 Sektoren a 256 Byte und 11
*     Verzeichniseintraege angelegt. Die DISKID wird korrekt gesetzt,
*     der frei verwendbare Teil dieses Feldes ist jedoch 0.
*
*  AUFRUF:
*     err = CarFormat( FCB_PTR fcb )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*
*********************************************************************/

#define SECTORS 31

int /*errflag*/ CarFormat( FCB_PTR fcb )
{ CARF_INIT

   int i;
   USR_BYTE dummy[SECTORS];
   HEADER header;

   CarDrive = fcb->DriveNr;

   /* Feste Werte fuer 8K Datentraeger */

   header.seccnt   = SECTORS; /* 31 Sektoren (+ 1 Directory-Sektor) */
   header.spinfo   = 0x80;    /* Sektorgroesse 256, Letzte Partiton */
   header.dircnt   = 11;      /* 11 Directory-Eintraege */
   header.reserved = 0;       /* Reservierter Eintrag */
   header.diskid   = 0x8000;  /* Kennung neuer Datentraeger */

   CarError |= WriteCarrier( &header , sizeof(HEADER) , OFFS_HEADER );

   memset( (void*)dummy , 0 , header.seccnt );
   CarError |= WriteCarrier( dummy , header.seccnt ,
                  16 + header.dircnt*sizeof(DIRENTRY) );

   For ( i=0 ; i<header.dircnt ; i++ ) Do
      CarError |= WriteCarrier( &dummy[0] , 1 , 16+i*sizeof(DIRENTRY) );
   Endfor

 CARF_EXIT }

#else /* NEW_FORMAT *NB*/


/*********************************************************************
*
*  FUNKTION: CarFormat - Formatieren eines Datentr„gers
*
*  BESCHREIBUNG:
*     Stellt den Datentraegertyp fest und formatiert dann mit einem
*     einigermassen sinnvollen Satz an Einstellungen.
*
*  AUFRUF:
*     err = CarFormat( FCB_PTR fcb )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*
*********************************************************************/

int /*errflag*/ CarFormat( FCB_PTR fcb )
{
   typedef struct {
      int length, secsize, seccnt, dirsecs, dircnt, partcnt;
   } CAR_INFO;

   CARF_INIT

   static const CAR_INFO car_info[] = {
      /* Length, Secsize, Seccnt, DirSecs, Dircnt, Partcnt */
      {  4, 0,  15, 1, 12, 1 }, /* 1 DirSec  a 256 Bytes */
      {  8, 0,  30, 2, 25, 1 }, /* 2 DirSecs a 256 Bytes */
      { 16, 1,  31, 1, 24, 1 }, /* 1 DirSec  a 512 Bytes */
      { 32, 1,  63, 1, 24, 1 }, /* 1 DirSec  a 512 Bytes */
      { 64, 1, 126, 2, 49, 1 }, /* 2 DirSecs a 512 Bytes */
      { 0 } /* Das war's */
   };
   register int i;
   USR_BYTE *dummy;
   CAR_INFO *car_ptr;
   HEADER header;
   USR_WORD car_len;

   CarDrive = fcb->DriveNr;

   /* Datentraegertyp feststellen */

   /* Fehler sollte eigentlich nur 0 sein, aber auch 1 wird ab und zu geliefert *NB*/
   If( (car_len = SelectCarrier()) < 4 ) Then
      CarError = CERR_NO_DEVICE;
   Else
      For( car_ptr = car_info; ; car_ptr++ ) Do
         If( car_len == car_ptr->length ) Then
            break;
         Elseif( !car_ptr->length ) Then
            /* Ende der Liste, festgestellter Typ wird nicht unterstuetzt */
            car_ptr = NULL;
            CarError |= CERR_NO_EEPROM;
            break;
         Endif
      Endfor

      If( (car_ptr != NULL) && !CarError ) Then
         header.seccnt   = car_ptr->seccnt;
         header.spinfo   = 0x80 | car_ptr->secsize;
         header.dircnt   = car_ptr->dircnt;
         header.reserved = 0;       /* Reservierter Eintrag */
         header.diskid   = 0x8000;  /* Kennung neuer Datentraeger */

         CarError |= WriteCarrier( &header , sizeof(HEADER) , OFFS_HEADER );
         dummy = (USR_BYTE *) MemAlloc( header.seccnt );
         memset( (void*)dummy , 0 , header.seccnt );

         /* Directory loeschen */
         For ( i=0 ; i<header.dircnt ; i++ ) Do
            CarError |= WriteCarrier( dummy, 1 , 16+i*sizeof(DIRENTRY) );
         Endfor

         /*
          * Hat eine Partition mehr als einen Directory-Sektor, muss jeder
          * zusaetzliche Sektor durch einen 0xff-Eintrag in der FAT gekennzeichnet
          * werden.
          */
         /* Fat loeschen (Directotysektoren belegt) */
         for( i=0; i < car_ptr->dirsecs-1; i++ ) dummy[i] = 0xFF;
         CarError |= WriteCarrier( dummy, header.seccnt, 16 + header.dircnt*sizeof(DIRENTRY) );

         MemFree( dummy );
     Endif
   Endif

 CARF_EXIT }

#endif /* NEW_FORMAT *NB*/


/*********************************************************************
*
*  FUNKTION: CarSetDate - Setzen von Datum und Uhrzeit einer Datei
*
*  AUFRUF:
*     err = CarSetDate( fcb , date , time )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*     date IN [USR_WORD] - Datum.
*     time IN [USR_WORD] - Zeit.
*
*********************************************************************/

int /*errflag*/ CarSetDate( FCB_PTR fcb , USR_WORD date , USR_WORD time )
{ CARF_INIT

   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=FindFile((char*)&fcb->FileName[0])) != NULL ) Then
      fc->Dir.Date = date;
      fc->Dir.Time = time;
      fc->Update   = TRUE;
      ReleaseFile( fc );
   Else
      CarError |= CERR_NO_FILE;
   Endif

 CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarReadDate - Datum und Uhrzeit einer Datei lesen
*
*  AUFRUF:
*     err = CarReadDate( fcb , date , time )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*     date OUT [USR_WORD*] - Datum.
*     time OUT [USR_WORD*] - Zeit.
*
*********************************************************************/

int /*errflag*/ CarReadDate( FCB_PTR fcb , USR_WORD *date , USR_WORD *time ) {return 0;}
/* Wird nicht mehr benutzt, da in DEVDISK intern programmiert
{ CARF_INIT

   FILECTRL * fc;

   CarDrive = fcb->DriveNr;

   If ( (fc=FindFile((char*)&fcb->FileName[0])) != NULL ) Then
      *date = fc->Dir.Date;
      *time = fc->Dir.Time;
      ReleaseFile( fc );
   Elseif ( CarError & CERR_WRONG_FORMAT ) Then
      CarError &= ~CERR_WRONG_FORMAT;
      *date = *time = 0;
   Else
      CarError |= CERR_NO_FILE;
   Endif

 CARF_EXIT }
*/

/*********************************************************************
*
*  FUNKTION: CarDirectory - Diskettenkatalog einlesen
*
*  AUFRUF:
*     err = CarDirectory( FCB_PTR fcb , callback )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*     callback IN [void*] - Adresse einer Callback-Funktion mit der
*        folgenden Schnittstelle, die fuer jede Datei aufgerufen wird.
*        void CallBack( FCB_PTR fcb , char *filename , USR_LONG filesize ,
*                       USR_WORD Date , USR_WORD Time )
*
*********************************************************************/

int /*errflag*/ CarDirectory( FCB_PTR fcb , void (*callback)() )
{ CARF_INIT

   int i;
   int part = 0;
   PARTINFO pinfo;
   DIRENTRY dir;
   FILECTRL * fc;
   char intfn[LEN_FNAME+LEN_EXTEN+1];
   char extfn[LEN_FNAME+LEN_EXTEN+2];

   CarDrive = fcb->DriveNr;

   CfnExtInt( (char*)fcb->FileName , intfn );

   Repeat
      If ( GetPartInfo( part++ , &pinfo ) == USR_NO_ERROR ) Then
         fcb->Version = DISK_VERS_STD;
         For ( i=0 ; i<pinfo.DirEntries ; i++ ) Do
            ReadBlock( &pinfo , 16+i*sizeof(DIRENTRY) , &dir , sizeof(DIRENTRY) );
            If ( ! FileDeleted(dir.Name[0]) && MatchFileName(&dir.Name[0],intfn) ) Then
               CfnIntExt( &dir.Name[0] , extfn );
               fc = FindFile( extfn );  /* Thats what i call 'inefficient' */
               If (fc == NULL) Then
						CarError |= CERR_NO_FILE;
					Else
						(*callback)( fcb , extfn , (long)FileSize(fc) ,
										 fc->Dir.Date , fc->Dir.Time );
						ReleaseFile( fc );
					Endif
				Endif
			Endfor
		Elseif ( CarError & CERR_WRONG_FORMAT ) Then
			/* Trivial fuer kompatiblen Datentraeger */
			fcb->Version = DISK_VERS_OLD;
			(*callback)( fcb , "CARRIER.OLD" , 4096L , 0 , 0 );
			CarError &= ~CERR_WRONG_FORMAT;
			pinfo.LastPart = 1;
		Endif
	Until ( CarError  ||  pinfo.LastPart );

 CARF_EXIT }


/*********************************************************************
*
*  FUNKTION: CarOpen - Oeffnen einer Datei
*
*  AUFRUF:
*     err = CarOpen( fcb )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*
*  BEMERKUNGEN:
*********************************************************************/

int /*errflag*/ CarOpen( FCB_PTR fcb )
{ CARF_INIT

  CARF_EXIT }

/*********************************************************************
*
*  FUNKTION: CarClose - Oeffnen einer Datei
*
*  AUFRUF:
*     err = CarClose( fcb )
*
*  PARAMETER:
*     errflag RESULT [int] - Fehlerflag.
*     fcb IN [FCB_PTR] - FCB.
*
*  BEMERKUNGEN:
*********************************************************************/

int /*errflag*/ CarClose( FCB_PTR fcb )
{ CARF_INIT

 CARF_EXIT }

/*********************************************************************
*                                                                    *
*                  D I S K C A R   -   E  N  D  E                    *
*                                                                    *
*********************************************************************/


/*@ Thu Oct 19 16:50:38 1989 */
/*@ Mon Oct 23 18:28:34 1989 */
/*@ Wed Apr 18 16:04:55 1990 */
/*@ Wed Apr 18 16:12:56 1990 */
/*@ Thu Apr 19 00:36:38 1990 */
/*@ Thu Apr 19 15:17:07 1990 */
/*@ Thu Apr 19 16:21:30 1990 */
/*@ Fri Apr 20 12:44:38 1990 */
/*@ Wed Apr 25 12:48:04 1990 */
/*@ Tue May 08 10:21:44 1990 */
/*@ Mon May 14 14:57:53 1990 */
/*@ Tue May 15 10:00:39 1990 */
/*@ Tue May 15 14:47:27 1990 */
/*@ Tue May 15 17:21:07 1990 */
/*@ Wed May 16 09:32:19 1990 */
/*@ Fri Jun 08 16:00:35 1990 */
/*@ Thu Jun 21 16:05:06 1990 */
/*@ Fri Jun 22 16:21:55 1990 */
/*@ Tue Jun 26 13:17:14 1990 */
/*@ Fri Jun 29 17:18:19 1990 */
/*@ Wed Jul 04 12:14:21 1990 */
/*@ Thu Jul 05 17:01:55 1990 */
/*@ Fri Jul 06 10:36:35 1990 */
/*@ Fri Jul 06 16:19:13 1990 */
/*@ Wed Jul 11 10:51:25 1990 */
/*@ Thu Jul 12 15:28:04 1990 */
/*@ Thu Jul 12 17:39:28 1990 */
/*@ Thu Jul 26 11:24:42 1990 */
/*@ Thu Jul 26 12:18:55 1990 */
/*@ Thu Jul 26 14:32:58 1990 */
/*@ Mon Jul 30 09:43:31 1990 */
/*@ Wed Aug 01 13:35:26 1990 */
/*@ Thu Aug 16 09:42:39 1990 */
/*@ Thu Aug 16 10:05:38 1990 */
/*@ Mon Aug 27 16:40:59 1990 */
/*@ Tue Aug 28 16:52:45 1990 */
/*@ Wed Aug 29 08:54:37 1990 */
/*@ Tue Sep 04 14:09:49 1990 */
/*@ Tue Sep 11 15:17:22 1990 */
/*@ Thu Sep 13 12:23:16 1990 */

/*@ Thu Sep 20 15:33:22 1990 */
/*@ Thu Sep 20 15:41:29 1990 */
/*@ Thu Sep 20 17:18:04 1990 */
/*@ Mon Sep 24 11:55:40 1990 */
/*@ Mon Sep 24 12:00:41 1990 */
/*@ Tue Sep 25 13:38:48 1990 */
/*@ Thu Sep 27 12:51:07 1990 */
/*@ Fri Sep 28 13:43:41 1990 */
/*@ Fri Sep 28 15:24:58 1990 */
/*@ Tue Nov 13 15:36:06 1990 */
/*@ Wed Dec 19 13:14:28 1990 */
/*@ Thu Dec 20 14:20:31 1990 */
/*@ Mon Jul 08 11:26:49 1991 */
/*@ Mon Sep 02 15:39:46 1991 */
/*@ Fri Sep 06 13:54:20 1991 */
/*@ Tue Oct 22 09:13:45 1991 */
/*@ Thu Oct 24 14:20:46 1991 */
/*@ Wed Nov 06 10:38:46 1991 */
/*@ Fri Dec 06 15:15:48 1991 */
/*@ Thu Dec 19 15:11:37 1991 */
/*@ Fri Dec 20 12:54:16 1991 */
/*@ Thu Feb 13 09:05:20 1992 */
/*@ Thu Jun 25 16:06:51 1992 */
/*@ Tue Aug 25 13:43:56 1992 */
/*@ Thu Nov 12 08:15:17 1992 */
/*@ Thu Nov 19 09:17:08 1992 */
/*@ Tue Dec 08 15:24:57 1992 */
/*@ Mon Jan 25 13:29:14 1993 */
