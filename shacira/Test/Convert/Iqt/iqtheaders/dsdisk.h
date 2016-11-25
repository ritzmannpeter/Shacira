
#ifndef _dsdisk
#define _dsdisk

/*********************************************************************
*
*
*         DSDISK.H         - Datentraeger
*
*
*********************************************************************/

/*  *** HISTORY ***
*   12.02.90   -SF-     Implementierung
*   10.08.90   -SF-     typedefs hierher verlagert, da Pruefung in dsutil.c
*   15.08.90   -SF-     FILE_HEADER erweitert
*   17.08.90   -SF-     FILE_HEADER nochmals erweitert
*   11.09.90   -SF-     DO_CONVERT eingebaut
*   11.09.90   -SF-     FILE_HEADER um ScrewSuckBack und PlastWay erweitert
*   12.09.90   -SF-     MAX_MAT_NR von 8 auf 15 erweitert
*   18.09.90   -SF-     ToolNr doch wieder ein String
*    4.04.91   -SF-     Version 2.0 erstellt: Konfiguration des
*                       Lesens/Schreibens ist komplett neu
*   22.10.91   -TSchw-  USE_GREATEST_KEY definiert
*   09.12.91   -SF-     DISK_ID_FOT definiert
*   31.01.92   -TSchw-  FILE_HEADER erweitert fuer Version 57: 2. Aggregat,
*                       Stufe der Werkzeuginnendruckumschaltung
*   13.02.92   -SF-     DISK_ID_ABGL definiert
*   23.11.92   -TSchw-  GENERAL_FILE_TYPE definiert
*   04.03.96   -HAns-   FILE_HEADER nochmals erweitert (3/4F)
*   09.07.97   -TSchw-  Bei Portierung auf Neutrino alle int-Variablen
*                       (in Neutrino 32 Bit) in den Dateikoepfen auf 
*                       short int (16 Bit wie bisher) umgestellt zwecks
*                       Kompatibilitaet.
*   26.02.98   -TSchw-  DISK_ID_HEATTEXT und TAB_HEATTEXT eingefuegt
*   16.04.99   -TSchw-  TAB_PG_NEW, DISK_ID_PG_NEW, DISK_ID_PG_IQTREG und
*                       DISK_ID_PG_ISCOSREG eingefuegt.
*   23.04.99   -TSchw-  CORE: DISK_ID_CORE_IQTREG und DISK_ID_CORE_ISCOSREG
*								definiert alse neue Teildateien fuer die frei
*							   programmierbaren Kernzuege.
*  05.07.00    -TSchw-  Portierung auf Linux: Die Strukturen der Dateikoepfe
*                       muessen als gepackt deklariert werden (siehe
*                       STRUCT_PACKED)
*  01.02.01    -HAns-   FILE_HEADER nochmals erweitert (5/6F)
*  22.03.01    -TSchw-  DISK_ID_EM17_ROB eingefuegt, siehe EM17.
*/

/*********************************************************************
X  Konfigurations-Konstanten
*********************************************************************/

/* Alle zu durchsuchenden Tabellen */
#define  TAB_IQTREG           1
#define  TAB_ISCOSREG         2
#define  TAB_ISCOSBIT         3
#define  TAB_TEXT             4
#define  TAB_PG               5  /* Prozessgraphik Sollkurven alte Version	*/
#define  TAB_HEATTEXT         6  
#define  TAB_PG_NEW		      7  /* Prozessgraphik Sollkurven neue Version	*/
#define  TAB_EM17             8  /* EM17: Euromap 17 Datei                 */

/* Teildatei-Typen */
#define  DISK_ID_IQTREG          1
#define  DISK_ID_ISCOSREG        2
#define  DISK_ID_ISCOSBIT        3
#define  DISK_ID_TEXT            4
#define  DISK_ID_PG              5
#define  DISK_ID_ROB_REG         6
#define  DISK_ID_ROB_TEXT        7
#define  DISK_ID_SETUP          10
#define  DISK_ID_SETUP_TEXT     11
#define  DISK_ID_FOT            12
#define  DISK_ID_ABGL           13
#define  DISK_ID_HEATTEXT       14
#define  DISK_ID_PG_NEW         15
#define  DISK_ID_PG_IQTREG      16
#define  DISK_ID_PG_ISCOSREG    17
#define  DISK_ID_CORE_IQTREG   	18	/* CORE */
#define  DISK_ID_CORE_ISCOSREG 	19  /* CORE */
#define  DISK_ID_EM17_ROB        20 /* EM17: Euromap 17 Robotdaten (Wittmann) */
#define  DISK_ID_PTRTAB         99  /* wird stets gespeichert */

#define  CHECK_NO             0     /* nichts von beidem machen */
#define  CHECK_FIRST          1     /* Pre und PostCarrierRead aufrufen */
#define  CHECK_ALL            2     /* PostCarrierRead 2x aufrufen */

#define  DL_NO           0xffff     /* kein Download durchfuehren */

/* Return-Parameter bei DiskCheckPar (ausser USR_ERROR und USR_NO_ERROR) */
#define  DO_CONVERT           2     /* Konvertierung durchfuehren */

#define  USE_GREATEST_KEY  0xff     /* Wird diese Konstante in der         */
                                    /* DiskReadTab als Key definiert, so   */
                                    /* wird die groesste vorher definierte */
                                    /* Schluesselschalterstellung benutzt  */

#define  GENERAL_FILE_TYPE 0xff     /* Allgemeiner Dateityp mit beliebigem */
                                    /* Inhalt, nicht in den DSDISK-Tabellen*/
                                    /* vorhanden.                          */

/*********************************************************************
X  Konfigurations-Strukturen
*********************************************************************/

/* Teildateigruppen */
 typedef struct
   {
   BYTE           Id;            /* Id der Teildatei */
   BYTE           Tab;           /* zugehoerige Register- oder Text-Tabelle */
   TEXT_INDEX     Text;          /* auszugebender Text */
   } SUBFILE_TAB;

/* Teildateigruppen fuer's Lesen */
 typedef struct
   {
   BYTE           Option;        /* Option oder 0 */
   SUBFILE_TAB    *SubTab;       /* Teildateigruppe */
   } SUBFILE_RD_TAB;

/* Lese-Tabelle */
 typedef struct
   {
   BYTE           Key;           /* erlaubte Schluesselschalterstellung */
   BYTE           Check;         /* CHECK_NO, CHECK_FIRST oder CHECK_ALL */
   UWORD          DLFlag;        /* DL_NO oder Parameter fuer Download */
   BYTE           Option;        /* erlaubte Option bei Auswahl der Leseart */
   TEXT_INDEX     Text;          /* auszugebender Text */
   SUBFILE_RD_TAB *SubReadTab;   /* Teildateigruppe fuer's Lesen */
   } DISK_RD_TAB;

/* Teildateigruppen fuer's Schreiben */
 typedef struct
   {
   UWORD          Mode;          /* Kennung in Register und Text-Tabellen */
   BYTE           Option;        /* Option oder 0 */
   SUBFILE_TAB    *SubTab;       /* Teildateigruppe */
   } SUBFILE_WRT_TAB;

/* Schreib-Tabelle */
 typedef struct
   {
   BYTE           Key;        /* erlaubte Schluesselschalterstellung */
   BYTE           Option;     /* erlaubte Option bei Auswahl der Schreibart */
   TEXT_INDEX     Text;       /* auszugebender Text beim Schreiben */
   TEXT_INDEX     FileName;   /* Dateiname ohne Extension */
   TEXT_INDEX     KZ;         /* Kennzeichen des Dateityps */
   SUBFILE_WRT_TAB   *SubWriteTab;   /* Teildateigruppe fuer's Schreiben */
   } DISK_WRT_TAB;

/* Allgemeine Texte und Konfigurationen */
 typedef struct
   {
   BYTE           FormKey;       /* Schluesselschalterst. beim Formatieren */
   BYTE           DelKey;        /* Schluesselschalterst. beim Loeschen */
   TEXT_INDEX     FormText;      /* Text beim Formatieren */
   TEXT_INDEX     DelText;       /* Text beim Loeschen */
   TEXT_INDEX     DirText;       /* Text beim Erstellen des Inhaltsverz. */
   TEXT_INDEX     StatLineText;  /* Text in der Statuszeile */
   TEXT_INDEX     ErrText;       /* Text bei fehlerhaftem Lesen einer Datei */
   TEXT_INDEX     SumText;       /* Text beim Schreiben der Gesamt-Byte */
   TEXT_INDEX     ByteText;      /* Einheit bei Lesen/Schreiben */
   TEXT_INDEX     HeadText;      /* Text beim Schreiben des Dateikopfs */
   } DISK_HEAD_TAB;

/* Konfigurationstabelle */
 typedef struct
   {
   UWORD          RdInd;         /* Index-Register in RdTab oder 0 */
   UWORD          WrtInd;        /* Index-Register in WrtTab oder 0 */
   DISK_RD_TAB    *RdTab;        /* Lese-Tabelle */
   DISK_WRT_TAB   *WrtTab;       /* Schreib-Tabelle */
   DISK_HEAD_TAB  *HeadTab;      /* allgemeine Konfigurationen */
   } DISK_KONFIG_TAB;

/* Konvertierungs-Funktionen */
 typedef struct
   {
   REGISTER Reg;              /* Nummer (Name) eines Registers oder Bits */
   FUNCT    Umrechnung;       /* Zeiger auf Plaus- und Umrechnungsfunktion */
   } DISKTAB_TYPE;


/*********************************************************************
X  Dateikoepfe
*********************************************************************/

/* Typ der Register-Nr. */
#define  DISK_REGNR_WORD      0
#define  DISK_REGNR_LONG      1
#define  DISK_REGNR_STRING    2

/* Text-Groessen in FileHeader */
#define MAX_MASCH_TYPE  7
#define MAX_MAT_NR     15
#define MAX_TOOL_NR    15
#define MAX_INFO_TEXT  10
#define MAX_FILE_NAME  13

/* Kopf des neuen Datentraegers */
#include <packstart.h>
 typedef struct
   {
   BYTE        Version;                   /* Versions-Nr. */
   BYTE        HeaderSize;                /* Groesse des Dateiheaders */
   BYTE        FileType;                  /* Dateityp */
   ULONG       Date;                      /* Datum und Uhrzeit */
   BYTE        RegType;                   /* Typ der Register-Nr. */
   char        InfoText[MAX_INFO_TEXT];   /* freier Text */
   char        MashType[MAX_MASCH_TYPE];  /* Maschinentyp */
   char        MatNr[MAX_MAT_NR];         /* Material-Nummer */
   char        ToolNr[MAX_TOOL_NR];       /* Werkzeug-Nummer */
   short int   ProgNr;                    /* Sonderprogramm-Nr */
   short int   Diameter;                  /* Schneckendurchmesser */
   short int   PresConst;                 /* Umrechnungskonstante fuer Druck */
   short int   MashSize;                  /* Maschinen-Groesse */
   BYTE        Aggregat;                  /* Aggregat Ausfuehrung */
   BYTE        HeatZoneCount;             /* Anzahl Heizzonen */
   short int   ScrewSuckBack;             /* Auswahl Schneckenrueckzug */
   short int   PlastWay;                  /* Plastifizierweg */
   short int   MouldOpWay;                /* Werkzeugoeffnungsweg */
   BYTE        VersMash;                  /* Maschinen-Version */
   BYTE        VersStruct;                /* Datenstruktur-Version */
   BYTE        VersExtra;                 /* spezielle Versions-Nr. */
   short int   Reserved1;                 /* Reserve 1 */
   short int   Reserved2;                 /* Reserve 2 */
   /* Erweiterung des Fileheaders fuer Version 57                            */
   short int   MaxAgg;                    /* Anzahl der Aggregate (1, 2 etc.)*/
   short int   MouldInPres;               /* Stufe fuer Wkz-Innendruckumsch. */
   short int   MaxSpritzDruck;            /* Maximaler Einspritzdruck        */
   short int   MouldInPres2;              /* Stufe fuer Wkz-Innendruck. Agg2 */
   short int   MaxSpritzDruck2;           /* Maximaler Einspritzdruck   Agg2 */
   short int   Diameter2;                 /* Schneckendurchmesser       Agg2 */
   short int   PresConst2;                /* Umrechnungskonst. Druck    Agg2 */
   BYTE        Aggregat2;                 /* Aggregat Ausfuehrung       Agg2 */
   BYTE        HeatZoneCount2;            /* Anzahl Heizzonen           Agg2 */
   short int   ScrewSuckBack2;            /* Auswahl Schneckenrueckzug  Agg2 */
   short int   PlastWay2;                 /* Plastifizierweg            Agg2 */
   /* Erweiterung des Fileheaders fuer Version 60 (QNX-Version 202 3/4F)     */
   short int   MouldInPres3;              /* Stufe fuer Wkz-Innendruck. Agg3 */
   short int   MaxSpritzDruck3;           /* Maximaler Einspritzdruck   Agg3 */
   short int   Diameter3;                 /* Schneckendurchmesser       Agg3 */
   short int   PresConst3;                /* Umrechnungskonst. Druck    Agg3 */
   BYTE        Aggregat3;                 /* Aggregat Ausfuehrung       Agg3 */
   BYTE        HeatZoneCount3;            /* Anzahl Heizzonen           Agg3 */
   short int   ScrewSuckBack3;            /* Auswahl Schneckenrueckzug  Agg3 */
   short int   PlastWay3;                 /* Plastifizierweg            Agg3 */
   short int   MouldInPres4;              /* Stufe fuer Wkz-Innendruck. Agg4 */
   short int   MaxSpritzDruck4;           /* Maximaler Einspritzdruck   Agg4 */
   short int   Diameter4;                 /* Schneckendurchmesser       Agg4 */
   short int   PresConst4;                /* Umrechnungskonst. Druck    Agg4 */
   BYTE        Aggregat4;                 /* Aggregat Ausfuehrung       Agg4 */
   BYTE        HeatZoneCount4;            /* Anzahl Heizzonen           Agg4 */
   short int   ScrewSuckBack4;            /* Auswahl Schneckenrueckzug  Agg4 */
   short int   PlastWay4;                 /* Plastifizierweg            Agg4 */
   /* Erweiterung des Fileheaders fuer Version 61 (QNX-Version 107 5/6F)     */
   short int   MouldInPres5;              /* Stufe fuer Wkz-Innendruck. Agg5 */
   short int   MaxSpritzDruck5;           /* Maximaler Einspritzdruck   Agg5 */
   short int   Diameter5;                 /* Schneckendurchmesser       Agg5 */
   short int   PresConst5;                /* Umrechnungskonst. Druck    Agg5 */
   BYTE        Aggregat5;                 /* Aggregat Ausfuehrung       Agg5 */
   BYTE        HeatZoneCount5;            /* Anzahl Heizzonen           Agg5 */
   short int   ScrewSuckBack5;            /* Auswahl Schneckenrueckzug  Agg5 */
   short int   PlastWay5;                 /* Plastifizierweg            Agg5 */
   short int   MouldInPres6;              /* Stufe fuer Wkz-Innendruck. Agg6 */
   short int   MaxSpritzDruck6;           /* Maximaler Einspritzdruck   Agg6 */
   short int   Diameter6;                 /* Schneckendurchmesser       Agg6 */
   short int   PresConst6;                /* Umrechnungskonst. Druck    Agg6 */
   BYTE        Aggregat6;                 /* Aggregat Ausfuehrung       Agg6 */
   BYTE        HeatZoneCount6;            /* Anzahl Heizzonen           Agg6 */
   short int   ScrewSuckBack6;            /* Auswahl Schneckenrueckzug  Agg6 */
   short int   PlastWay6;                 /* Plastifizierweg            Agg6 */
   } STRUCT_PACKED FILE_HEADER;
#include <packstop.h>

/* Kopf des alten Datentraegers */
#include <packstart.h>
 typedef struct {
   char        ResOrFree[6];  /* reserviert fuer Cassette (0-2) / frei (3-5) */
   short int   TextLength;    /* max. Textlaenge (Seite 82-89) */
   short int   ProcNr;        /* Maschinentyp (Prozedur-Nr.) */
   short int   CarrierNr;     /* Carrier-KZ-Nr. */
   short int   CarrierLength; /* Carrier Laenge */
   BYTE        Id;            /* Kennung (Daten=1 / Grafik=2) */
   BYTE        CheckSum;      /* Carrier Check-Summe */
} STRUCT_PACKED OLD_DISK_HEADER;
#include <packstop.h>

/* Teildateikopf ds alten Datentraegers */
#include <packstart.h>
 typedef struct {
   short int   MashCode;      /* Maschinen-Code */
   short int   ProgNr;        /* Kernzugs-Nr. (Sonderprogramm-Nr.) */
   BYTE        Diameter;      /* Schneckendurchmesser */
   BYTE        PresConst;     /* Umrechnungskonstante fuer Druck */
   short int   MashSize;      /* Maschinen-Groesse */
   BYTE        Aggregat;      /* Aggregat Ausfuehrung */
   BYTE        HeatZoneCount; /* Anzahl Heizzonen */
   long        MatNr;         /* Material-Nr. */
   long        ToolNr;        /* Werkzeug-Nr. */
   char        Date[5];       /* Datum (Jahr-Monat-Tag-Stunde-Minute) */
   BYTE        CheckSum;      /* Check-Summe */
} STRUCT_PACKED OLD_DISK_SUB_HEADER;
#include <packstop.h>

#endif


