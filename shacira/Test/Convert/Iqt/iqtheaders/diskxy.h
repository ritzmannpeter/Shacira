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
*     12.06.97 -TSchw- Struktur FCB_: ScratchName groesser gemacht
*     05.02.98 -TSchw- FileCode als FILE* definiert und stdio.h included
*     13.03.98 -TSchw- In FCB_TYP StartPos eingetragen.
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
#ifndef _stdio
#include <stdio.h>
#define _stdio
#endif
/*.EI.***********************************************************************/


/*********************************************************************
*  Einige Makros...
*********************************************************************/

#define FOFFS(o,fcb)   ( (UWORD)((o)/(fcb)->BlkSize) )
#define BOFFS(o,fcb)   ( (UWORD)((o)%(fcb)->BlkSize) )
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
   BYTE FileName[13];      /* Dateiname */
   ULONG Date;              /* Datum */
   ULONG Size;              /* Dateilaenge */
   ULONG Next;              /* Vorwaertszeiger fuer Extra-Speicher */
} DIR_TYP, *DIR_PTR;

typedef struct FCB_ {
   BYTE FileName[13];      /* Dateiname */
   BYTE ScratchName[128];  /* Temporaerer Puffer fuer Namensumwandlung */
   BYTE Drive;             /* Laufwerkskennung */
   BYTE Mode;              /* Zugriffsmodus */

   PARAMETER Date;         /* Dateidatum */
   ULONG FileSize;          /* Dateigroesse */
   ULONG FilePos;           /* Schreib/Lesezeiger in der Datei */

   BYTE Flags;             /* Interne Zustandsmarkierungen */

   DISKMOD_TYP *DMod;       /* typspezifischer Treiberstuct */

   IQT_HANDLE ComHnd;          /* Handle der benutzten Schnittstelle */
   BYTE DriveNr;           /* Laufwerksnummer fuer das WP1000 */
   int Error;              /* interne Nummer des letzten Fehlers */

   UWORD DirEntries;        /* Maximalzahl der Directory-Eintraege */

   BYTE Version;           /* Versionsnummer, 0 fuer kompat. Datentraeger */

   /*
   *  Die folgenden Eintraege werden von der Verwaltung der gepufferten
   *  Ein-/Ausgabe benoetigt:
   */

   UWORD BlkSize;           /* Groesse einer Uebertragungseinheit (Bytes) */
   UWORD BlkPos;            /* Position der gepufferten Uebertragungseinheit */
   BYTE *BlkBuffer;        /* Zeiger auf Datenpuffer (oder NULL) */
   BYTE BlkChanged;        /* Wurde der Datenpuffer geaendert? */

   /* Die letzten Eintraege hier wurden benoetigt, um das
    * DFS unter QNX einigermassen sauber verwenden zu koennen
    */

   FILE *FileCode;         /* Filecode fuer direkte Operationen auf der Floppy */
   long StartPos;          /* Fuer APPEND: Filegroesse der existierenden Datei */
} FCB_TYP,*FCB_PTR;


/*********************************************************************
*  HILFEN ZUR FEHLERSUCHE
*********************************************************************/

#ifdef DEBUG

#ifdef DEBUG_MAIN
ULONG DebugMask;         /* Maskenvariable nur in DevDisk definieren */
IQT_HANDLE DebWnd;
const CRT_PARAM_BLOCK DebWndParam = {
   0,"KLOE12x14",
   CRT_ST_ACTIVE,CRT_MD_SCROLL,
   CRT_MAKE_CHR(0,0),
   CRT_MAKE_CHR(48,20),
   CRT_MAKE_COLOR(COLOR_WHITE,COLOR_RED,0) };
#else
extern ULONG DebugMask;  /* sonst nur deklarieren */
extern DebWnd;
#endif


#ifdef DEB
ULONG DebugMask;         /* Maskenvariable nur in DevDisk definieren */
IQT_HANDLE DebWnd;
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
#define PUTSD(m,t,d) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%s %ld ",(t),(ULONG)(d) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTSH(m,t,h) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%s %lx ",(t),(ULONG)(h) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTD(m,d) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%ld ",(ULONG)(d) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
#define PUTH(m,h) If (DebugMask & (m)) Then char buf[80]; sprintf( buf,"%lx ",(ULONG)(h) ); DevWrite(DebWnd,buf,0,NULL,0); Endif
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