/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DISK.H   - DISK_xxx - Funktionen (mit oder ohne DLL)
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
*     VERSION:    4.0                       DATUM:   15.06.92
*     AUTOR(EN):  -TS-   Th. Schoenig       TELEFON: (0761) 42257
*
*  HISTORY:
*     15.06.92 -SF-    Implementierung im Zuge der 
*                      Portierung des IQT-350 auf IQT-450
*     14.07.92 -TS-    Neues Fehlerkonzept
*     20.05.93 -TS-    Fehlerrueckgabe verfeinert @@1
*     29.08.97 -PR-    Wegen Namenskollision unter Neutrino,
*                      ( Die Datenstrukturen liegen auch in diesem
*                      Adressraum)
*                      DiskTab durch DisktabPtr und OldDiskTab1
*                      OldDiskTab1Ptr ersetzt.
*     04.03.98 -TSchw- Struktur WRITE_FILE_INFO und neue Funktion
*                      DISK_WriteFilePart angelegt; InfoWindow-Funktionen
*                      aus diskreg.c global deklariert.
*     10.03.98 -TSchw- Struktur WRITE_FILE_INFO um wait_window erweitert.
*     12.03.98 -TSchw- Struktur WRITE_FILE_INFO um append erweitert.
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     DISK_InitBBRam     - globale BBRAM-Variable initialisieren      *
*     DISK_Init          - globale Variable des Datentraeger initial. *
*     DISK_Dir           - 1. Seite des Directories anzeigen (Datens.)*
*     DISK_ScrollUp      - Eine Seite zurueckblaettern (Softkey)      *
*     DISK_ScrollDown    - Eine Seite weiterblaettern (Softkey)       *
*     DISK_Write         - Datei schreiben (User 2)                   *
*     DISK_Read          - Datei lesen     (Softkey)                  *
*     DISK_ReadToolFile  - Datei mit spezieller  Werkzeug-Nr. lesen   *
*     DISK_Delete        - Datei loeschen   (Softkey)                 *
*
*  DATENTYPEN:
*     Keine
*
*  VARIABLEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _disk
#define _disk

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <dstruct.h>
#include <dsdisk.h>
#include <sunichar.h>
/*.EI.***********************************************************************/

/*********************************************************************
*  KONSTANTEN
*********************************************************************/

/* Funktionsparameter */
#define DISK_INIT_BBRAM    1
#define DISK_INIT                               2
#define DISK_SCROLL_UP     3
#define DISK_SCROLL_DOWN   4

/*********************************************************************
*  TYPEN
*********************************************************************/

typedef struct {
   FILE_HEADER    Header;                    /* Zeiger auf Directory */
   PARAMETER      FileSize;                  /* Groesse der Dateien */
   char           FileName[MAX_FILE_NAME];   /* Dateinamen */
} DIR_INFO_TYPE;

extern UWORD DSMaxVarText;  /* def. in diskwork.c */

typedef struct {
   UWORD order;        /*  - 0 = Datei Oeffnen                               */
                       /*    1 = In Datei schreiben                          */ 
                       /*    2 = Datei schliessen                            */ 
   UWORD security;     /*  - 0 = Keine Sicherheitsabfrage                    */ 
                       /*    1 = Sicherheitsabfrage durchfuehren             */ 
                       /*    Nur relevant bei Open                           */ 
   UWORD wait_window;  /*  - 0 = Kein Warte-Infofenster                      */ 
                       /*    1 = Warte-Infofenster anzeigen                  */ 
                       /*    Nur relevant bei Open                           */ 
   UWORD searchname;   /*  - 0 = Name nicht suchen                           */ 
                       /*    1 = Name suchen                                 */ 
                       /*    Nur relevant bei Open.                          */ 
   UWORD append;       /*  - 0 = Nur in neue Datei schreiben                 */
                       /*    1 = Falls Datei existiert, Daten anhaengen      */
   char file[13];      /*  - Dateiname (8.3)                                 */ 
                       /*    Nur relevant bei Open                           */ 
   BYTE drive;         /*  - 1=EEPROM / 2=Floppy / 3=EE auf Interfacekarte   */
                       /*    Nur relevant bei Open                           */ 
   IQT_HANDLE filehnd; /*  - Handle der Datei, wird bei Open gesetzt und     */ 
                       /*    bei Write und Close benutzt.                    */ 
   IQT_HANDLE waithnd; /*  - Handle fuer Infofenster, wird bei Open gesetzt. */
   char *buffer;       /*  - Zeiger auf zu schreibende Daten                 */
   int   buflen;       /*  - Laenge der zu schreibenden Daten                */
} WRITE_FILE_INFO;

/*********************************************************************
*  DLL lokale FUNKTIONEN
*********************************************************************/

/* Allgemeine Hilfsfunktionen */
ULONG  DiskGetTimeDate   ( void  );

/* Dateien lesen und schreiben */
int   DiskWriteFile     ( IQT_HANDLE WrtHnd, IQT_HANDLE InfoHandle, int Ind,
                          BOOL read_vg );
int   DiskReadFile      ( IQT_HANDLE RdHnd,  IQT_HANDLE InfoHandle, int Ind,
                          BYTE OldDiskNr, BOOL read_vg, BOOL pre_post );

/* Zwischen-Pufferung beim Lesen */
int   DiskRd            ( IQT_HANDLE hnd , void * buf , int buflen );
int   DiskSetFilePos    ( IQT_HANDLE Hnd , PARAMETER Pos );
int   PutToReadBuffer   ( UWORD RegNr , long Value , UWORD Ind1 ,
                          UWORD Ind2 , UWORD Ind3 );

/* alter Datentraeger */
BOOL  OldDiskTest       ( IQT_HANDLE );
int   OldReadDir        ( BYTE Drive , IQT_HANDLE DirHandle );
int   OldDiskReadSetup  ( IQT_HANDLE ReadHandle , BYTE FileNr );
int   OldDiskReadAll    ( IQT_HANDLE ReadHandle , BYTE FileNr );


/* Info Window */
void InfoWindowInit ( IQT_HANDLE Hnd );
void InfoWindowStaText ( TEXT_INDEX * StaText , int YPos );
void InfoWindowString ( UNICHAR *Text , int YPos );
void InfoWindowByte ( int Len );


/*********************************************************************
*  Modulglobale Daten
*********************************************************************/

extern DISKTAB_TYPE * DiskTabPtr;
extern DISK_KONFIG_TAB * DiskConfigTab;
extern UWORD DiskTabEntries;
extern REGISTER * OldDiskTab1Ptr;

extern BOOL  DoConvertRegister;

extern DIR_INFO_TYPE * InfoPointer;
extern PARAMETER DiskFreeSpace;

extern UWORD AktDirRead;       /* Anzahl gelesener Header der Dateien */
extern BYTE DiskDirPage;      /* Seiten-Nr. */
extern UWORD MinDiskDirPage;   /* kleinste Nr. auf Anzeigeseite */
extern UWORD MaxDiskDirPage;   /* groesste Nr. auf Anzeigeseite */
extern UWORD DirSize;          /* @@@ Groesse des Directories */

/*********************************************************************
*  MACRO's
*********************************************************************/

#define  DISK_CLOSE(Hnd)    { int ret;                             \
            If ((ret = DevClose( Hnd )) == USR_ERROR ) Then         \
               DevError( Hnd , DEV_DISK , DEV_CLOSE );   \
            Endif }

#define  DISK_OPEN(Hnd,Par) { int ret;               \
            If ((ret = DevOpen( Hnd , DEV_DISK , Par)) == USR_ERROR) Then  \
               DevError( *Hnd , DEV_DISK ,DEV_OPEN );           \
               return USR_ERROR;                                    \
            Else                                                \
            Endif }

#define  DISK_WRT(Hnd,Str,Size) { int ret;    \
            If ((ret = DiskWrt ( Hnd , (void *) Str , Size )) == ERROR_DEV) Then \
               DevError( Hnd , DEV_DISK , DEV_WRITE ); /*@@1*/  \
               return ERROR_DEV;    \
            Endif }

#define  DISK_RD(Hnd,Str,Size)  { int ret;    \
            If ((ret = DiskRd ( Hnd , (void *) Str , Size )) == ERROR_DEV) Then \
               DevError( Hnd , DEV_DISK , DEV_READ ); /*@@1*/  \
               return ERROR_DEV;    \
            Endif }

GLOBAL int  DISK_Init( BOOL init_bbram );
GLOBAL int  DISK_Dir( BYTE ScreenType , ELEMENT *EP );
GLOBAL UWORD DISK_Scroll( int choice, UWORD Param );
GLOBAL UWORD DISK_Write( UWORD Param );
GLOBAL UWORD DISK_Read( UWORD Param );
GLOBAL int  DISK_WriteFile( char *file, UWORD ctrl, UWORD file_type, BYTE drive );
GLOBAL int  DISK_WriteFilePart( WRITE_FILE_INFO *fileinfo );
GLOBAL int  DISK_ReadFile( char *file, UWORD ctrl, UWORD file_type, BYTE drive );
GLOBAL int  DISK_ReadToolFile( UWORD ctrl, long tool_nr, UWORD file_type, BYTE drive,
                      UWORD bit_nr );
GLOBAL UWORD DISK_Delete( UWORD Param );

#endif /* _disk */

