#ifndef _fmfat
#define _fmfat

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __direct__
#include <direct.h>
#define __direct__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
/*.EI.***********************************************************************/

/* Text-Groessen in FileHeader */
#define MAX_MASCH_TYPE  7
#define MAX_MAT_NR     15
#define MAX_TOOL_NR    15
#define MAX_INFO_TEXT  10
#define MAX_FILE_NAME  13

/* Kopf des neuen Datentraegers */
 typedef struct
   {
   unsigned_8      Version;                   /* Versions-Nr. */
   unsigned_8      HeaderSize;                /* Groesse des Dateiheaders */
   unsigned_8      FileType;                  /* Dateityp */
   unsigned_32     Date;                      /* Datum und Uhrzeit */
   unsigned_8      RegType;                   /* Typ der Register-Nr. */
   signed_8        InfoText[MAX_INFO_TEXT];   /* freier Text */
   signed_8        MashType[MAX_MASCH_TYPE];  /* Maschinentyp */
   signed_8        MatNr[MAX_MAT_NR];         /* Material-Nummer */
   signed_8        ToolNr[MAX_TOOL_NR];       /* Werkzeug-Nummer */
   signed_16         ProgNr;                    /* Sonderprogramm-Nr */
   signed_16         Diameter;                  /* Schneckendurchmesser */
   signed_16         PresConst;                 /* Umrechnungskonstante fuer Druck */
   signed_16         MashSize;                  /* Maschinen-Groesse */
   unsigned_8        Aggregat;                  /* Aggregat Ausfuehrung */
   unsigned_8        HeatZoneCount;             /* Anzahl Heizzonen */
   signed_16         ScrewSuckBack;             /* Auswahl Schneckenrueckzug */
   signed_16         PlastWay;                  /* Plastifizierweg */
   signed_16         MouldOpWay;                /* Werkzeugoeffnungsweg */
   unsigned_8        VersMash;                  /* Maschinen-Version */
   unsigned_8        VersStruct;                /* Datenstruktur-Version */
   unsigned_8        VersExtra;                 /* spezielle Versions-Nr. */
   signed_16         Reserved1;                 /* Reserve 1 */
   signed_16         Reserved2;                 /* Reserve 2 */
   /* Erweiterung des Fileheaders fuer Version 57                            */
   signed_16         MaxAgg;                    /* Anzahl der Aggregate (1, 2 etc.)*/
   signed_16         MouldInPres;               /* Stufe fuer Wkz-Innendruckumsch. */
   signed_16         MaxSpritzDruck;            /* Maximaler Einspritzdruck        */
   signed_16         MouldInPres2;              /* Stufe fuer Wkz-Innendruck. Agg2 */
   signed_16         MaxSpritzDruck2;           /* Maximaler Einspritzdruck   Agg2 */
   signed_16         Diameter2;                 /* Schneckendurchmesser       Agg2 */
   signed_16         PresConst2;                /* Umrechnungskonst. Druck    Agg2 */
   unsigned_8        Aggregat2;                 /* Aggregat Ausfuehrung       Agg2 */
   unsigned_8        HeatZoneCount2;            /* Anzahl Heizzonen           Agg2 */
   signed_16         ScrewSuckBack2;            /* Auswahl Schneckenrueckzug  Agg2 */
   signed_16         PlastWay2;                 /* Plastifizierweg            Agg2 */
   /* Erweiterung des Fileheaders fuer Version 60 (QNX-Version 202 3/4F)     */
   signed_16         MouldInPres3;              /* Stufe fuer Wkz-Innendruck. Agg3 */
   signed_16         MaxSpritzDruck3;           /* Maximaler Einspritzdruck   Agg3 */
   signed_16         Diameter3;                 /* Schneckendurchmesser       Agg3 */
   signed_16         PresConst3;                /* Umrechnungskonst. Druck    Agg3 */
   unsigned_8        Aggregat3;                 /* Aggregat Ausfuehrung       Agg3 */
   unsigned_8        HeatZoneCount3;            /* Anzahl Heizzonen           Agg3 */
   signed_16         ScrewSuckBack3;            /* Auswahl Schneckenrueckzug  Agg3 */
   signed_16         PlastWay3;                 /* Plastifizierweg            Agg3 */
   signed_16         MouldInPres4;              /* Stufe fuer Wkz-Innendruck. Agg4 */
   signed_16         MaxSpritzDruck4;           /* Maximaler Einspritzdruck   Agg4 */
   signed_16         Diameter4;                 /* Schneckendurchmesser       Agg4 */
   signed_16         PresConst4;                /* Umrechnungskonst. Druck    Agg4 */
   unsigned_8        Aggregat4;                 /* Aggregat Ausfuehrung       Agg4 */
   unsigned_8        HeatZoneCount4;            /* Anzahl Heizzonen           Agg4 */
   signed_16         ScrewSuckBack4;            /* Auswahl Schneckenrueckzug  Agg4 */
   signed_16         PlastWay4;                 /* Plastifizierweg            Agg4 */
   } FILE_HEADER;

GLOBAL const DRIVE_MODULE * FMFAT_Module();
GLOBAL const FILE_MODULE * FMFAT_FileModule();

#define DISK_ID_END   0xffff        /* Ende einer Teildatei */

/* ---- Typgruppe REG: Registertyp                                         */
#define REG_NOTYPE   0x0000  /* Kein Typ (Fehler)                          */
#define REG_INT      0x0001  /* Integer-Register                           */
#define REG_DINT     0x0002  /* DoubleInt-Register (nur ISCOS)             */
#define REG_LONG     0x0003  /* Long-Register (nur IQT)                    */
#define REG_INT10    0x0004  /* Integer-Tab mit 10 Eintraegen (nur IQT)    */
#define REG_INT20    0x0005  /* Integer-Tab mit 20 Eintraegen (nur IQT)    */
#define REG_LONG10   0x0006  /* Long-Tab. mit 10 Eintraegen (nur IQT)      */
#define REG_LONG20   0x0007  /* Long-Tab. mit 20 Eintraegen (nur IQT)      */
#define REG_INJTAB   0x0008  /* Int-ISCOS-Reg-Tab. mit Spritzindizes       */
                             /* RegTab [MaxInjCyc] [MaxInjUnits] [MaxStat] */

#define GET_REG_TYPE(rt)        ((rt) & 0x3f)

/* Alle zu durchsuchenden Tabellen */
#define  TAB_IQTREG           1
#define  TAB_ISCOSREG         2
#define  TAB_ISCOSBIT         3
#define  TAB_TEXT             4
#define  TAB_PG               5

/* Teildatei-Typen */
#define  DISK_ID_IQTREG       1
#define  DISK_ID_ISCOSREG     2
#define  DISK_ID_ISCOSBIT     3
#define  DISK_ID_TEXT         4
#define  DISK_ID_PG           5
#define  DISK_ID_ROB_REG      6
#define  DISK_ID_ROB_TEXT     7
#define  DISK_ID_SETUP       10
#define  DISK_ID_SETUP_TEXT  11
#define  DISK_ID_FOT         12
#define  DISK_ID_ABGL        13
#define  DISK_ID_PTRTAB      99     /* wird stets gespeichert */

#define START_ISCOS_BITS      0        /* ISCOS-Bits gehen ab 0 los */
#define START_ISCOS_BITS_KERN 1500     /* ISCOS-Kern-Bits gehen ab 1500 los */
#define START_IQT_BITS        2000     /* IQT-Bits gehen ab 2000 los */
#define START_ISCOS_REGS      3000     /* ISCOS-Register gehen ab 3000 los */
#define START_ISCOS_REGS_KERN 15000    /* ISCOS-Kern-Reg. gehen ab 15000 los */
#define START_REGLER_REGS     19000    /* Regler-Register gehen ab 19800 los */
#define START_IQT_REGS        20000    /* IQT-Register gehen ab 20000 los */
#define START_IQT_REGS_KERN   30000    /* IQT-Kern-Regs gehen ab 30000 los */

GLOBAL int FMFAT_Repair(char * path);

#define TEXTVAR_MASHINE       1
#define TEXTVAR_MATERIAL      4
#define TEXTVAR_TOOL          5
#define TEXTVAR_ART           6

#endif /* ifndef _fmfat */
