/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DISKXY.H
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
*     01.04.92 -SF-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     05.05.93 -PR-    Funktionen Open und Close in DISKMOD eingefuehrt
*     07.05.93 -PR-    Makros FOFFS, BOFFS und FBLKS aus devdisk.c
*                      uebernommen.
*
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
*     Keine
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _diskxy
#define _diskxy

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
/*.EI.***********************************************************************/


/*********************************************************************
*  Einige Makros...
*********************************************************************/

#define FOFFS(o,fcb)   ( (USR_WORD)((o)/(fcb)->BlkSize) )
#define BOFFS(o,fcb)   ( (USR_WORD)((o)%(fcb)->BlkSize) )
#define FBLKS(l,fcb)   ( FOFFS((l)+(fcb)->BlkSize-1,(fcb)) )

/*********************************************************************
*  Einige Konstanten...
*********************************************************************/

#define MODE_INIT  0          /* Parameter fuer die Restore-Funktion */
#define MODE_SYNC  1
#define MODE_FLUSH 2

#define FLAG_EXISTS     2     /* Datei ist vorhanden */
#define FLAG_DIRECTORY  4     /* Katalogfunktion */
#define FLAG_NEWDATE    8     /* bei Write neues Datum bereits gesetzt */

#define COM_0   0             /* Index fuer die erste Schnittstelle */
#define NO_COM 0xff           /* Index fuer fehlende Schnittstellen */

#define CAR_DRV0  0           /* Datentraeger-Laufwerk 0 */
#define CAR_DRV1  1           /* Datentraeger-Laufwerk 1 */
#define CAR_DRV2  3           /* Datentraeger-Laufwerk 2 */
#define CAR_KPROM 2           /* Kunden-PROM-"Laufwerk" */

/*********************************************************************
*  Datentypen fuer Datentraeger
*********************************************************************/

typedef struct DISKMOD_ {
   FUNC_INT_PTR Init,      /* 1malig Initialisieren des Datentraegers */
                Restore,   /* Synchronisationsfunktion */
                Create,    /* Datei neu anlegen */
                Expand,    /* Datei erweitern */
                Read,      /* Block aus Datei lesen */
                Write,     /* Block in Datei schreiben */
                Delete,    /* Datei loeschen */
                Directory, /* Katalog des Datentraegers */
                SetDate,   /* Datum setzen */
                ReadDate,  /* Datum lesen */
                Status,    /* Freiraum auf dem Datentraeger */
                Format,    /* Datentraeger formatieren */
                Open,      /* Datei oeffnen */
                Close;     /* Datei schliessen */
} DISKMOD_TYP,*DISKMOD_PTR;

typedef struct DIR_ {
   USR_BYTE FileName[13];      /* Dateiname */
   USR_LONG Date;              /* Datum */
   USR_LONG Size;              /* Dateilaenge */
   USR_LONG Next;              /* Vorwaertszeiger fuer Extra-Speicher */
} DIR_TYP, *DIR_PTR;

typedef struct FCB_ {
   USR_BYTE FileName[13];      /* Dateiname */
   USR_BYTE ScratchName[16];   /* Temporaerer Puffer fuer Namensumwandlung */
   USR_BYTE Drive;             /* Laufwerkskennung */
   USR_BYTE Mode;              /* Zugriffsmodus */

   PARAMETER Date;         /* Dateidatum */
   USR_LONG FileSize;          /* Dateigroesse */
   USR_LONG FilePos;           /* Schreib/Lesezeiger in der Datei */

   USR_BYTE Flags;             /* Interne Zustandsmarkierungen */

   DISKMOD_TYP *DMod;       /* typspezifischer Treiberstuct */

   USR_HANDLE ComHnd;          /* Handle der benutzten Schnittstelle */
   USR_BYTE DriveNr;           /* Laufwerksnummer fuer das WP1000 */
   int Error;              /* interne Nummer des letzten Fehlers */

   USR_WORD DirEntries;        /* Maximalzahl der Directory-Eintraege */

   USR_BYTE Version;           /* Versionsnummer, 0 fuer kompat. Datentraeger */

   /*
   *  Die folgenden Eintraege werden von der Verwaltung der gepufferten
   *  Ein-/Ausgabe benoetigt:
   */

   USR_WORD BlkSize;           /* Groesse einer Uebertragungseinheit (Bytes) */
   USR_WORD BlkPos;            /* Position der gepufferten Uebertragungseinheit */
   USR_BYTE *BlkBuffer;        /* Zeiger auf Datenpuffer (oder NULL) */
   USR_BYTE BlkChanged;        /* Wurde der Datenpuffer geaendert? */

   /* Die letzten Eintraege hier wurden benoetigt, um das
    * DFS unter QNX einigermassen sauber verwenden zu koennen
    */

   int FileCode;           /* Filecode fuer direkte Operationen auf der Floppy */
} FCB_TYP,*FCB_PTR;


/*********************************************************************
*  HILFEN ZUR FEHLERSUCHE
*********************************************************************/

#ifdef DEBUG

#ifdef DEBUG_MAIN
USR_LONG DebugMask;         /* Maskenvariable nur in DevDisk definieren */
USR_HANDLE DebWnd;
const CRT_PARAM_BLOCK DebWndParam = {
   0,"KLOE12x14",
   CRT_ST_ACTIVE,CRT_MD_SCROLL,
   CRT_MAKE_CHR(0,0),
   CRT_MAKE_CHR(48,20),
   CRT_MAKE_COLOR(COLOR_WHITE,COLOR_RED,0) };
#else
extern USR_LONG DebugMask;  /* sonst nur deklarieren */
extern DebWnd;
#endif


#ifdef DEB
USR_LONG DebugMask;         /* Maskenvariable nur in DevDisk definieren */
USR_HANDLE DebWnd;
#endif

/*#include <stdio.h>*/

#define D_WPENT  1
#define D_SEND   2
#define D_REC    4
#define D_RCOM   8
#define D_WPALL  16

#define D_DEV    256
#define D_OPEN   512

#define D_ALL    0xffffL

#ifdef DEB
#define PUTS(m,t) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%s ",(t) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTSD(m,t,d) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%s %ld ",(t),(USR_LONG)(d) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTSH(m,t,h) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%s %lx ",(t),(USR_LONG)(h) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTD(m,d) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%ld ",(USR_LONG)(d) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTH(m,h) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%lx ",(USR_LONG)(h) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define DEBUGINIT(m) { DebugMask=(m); }
#else
#define PUTS(m,t)
#define PUTSD(m,t,d)
#define PUTSH(m,t,h)
#define PUTD(m,d)
#define PUTH(m,h)
#define DEBUGINIT(m)
#endif

#else

#define PUTS(m,s)
#define PUTSD(m,s,d)
#define PUTSH(m,s,h)
#define PUTD(m,d)
#define PUTH(m,h)
#define DEBUGINIT(m)

#endif

#endif /* ifndef _diskxy */
