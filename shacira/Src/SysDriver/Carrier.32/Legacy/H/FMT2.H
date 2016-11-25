#ifndef _fmt2
#define _fmt2

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

/* Kopf des alten Datentraegers */
 typedef struct {
   signed_8  ResOrFree[6];  /* reserviert fuer Cassette (0-2) / frei (3-5) */
   signed_16   TextLength;    /* max. Textlaenge (Seite 82-89) */
   signed_16   ProcNr;        /* Maschinentyp (Prozedur-Nr.) */
   signed_16   CarrierNr;     /* Carrier-KZ-Nr. */
   signed_16   CarrierLength; /* Carrier Laenge */
   unsigned_8  Id;            /* Kennung (Daten=1 / Grafik=2) */
   unsigned_8  CheckSum;      /* Carrier Check-Summe */
} OLD_DISK_HEADER;

/* Teildateikopf ds alten Datentraegers */
 typedef struct {
   signed_16   MashCode;      /* Maschinen-Code */
   signed_16   ProgNr;        /* Kernzugs-Nr. (Sonderprogramm-Nr.) */
   unsigned_8  Diameter;      /* Schneckendurchmesser */
   unsigned_8  PresConst;     /* Umrechnungskonstante fuer Druck */
   signed_16   MashSize;      /* Maschinen-Groesse */
   unsigned_8  Aggregat;      /* Aggregat Ausfuehrung */
   unsigned_8  HeatZoneCount; /* Anzahl Heizzonen */
   signed_32  MatNr;         /* Material-Nr. */
   signed_32  ToolNr;        /* Werkzeug-Nr. */
   signed_8  Date[5];       /* Datum (Jahr-Monat-Tag-Stunde-Minute) */
   unsigned_8  CheckSum;      /* Check-Summe */
} OLD_DISK_SUB_HEADER;

#define MAX_TEXT_LEN       2000
#define MAX_FILE_SIZE\
   (sizeof(OLD_DISK_HEADER) + sizeof(OLD_DISK_SUB_HEADER) +\
   DATA_SIZE + MAX_TEXT_LEN)
#define FMT2_REGS     (DATA_SIZE/2)

/* Adressen der Datentraeger-Datei */
#define  ADR_HEADER        0x0000L
#define  ADR_SUBHEADER_1   0x0010L
#define  ADR_SUBHEADER_2   0x0028L
#define  ADR_SUBHEADER_3   0x0040L
#define  ADR_LIST_1        0x0060L
#define  ADR_LIST_2        0x0440L
#define  ADR_LIST_3        0x0820L
#define  ADR_TEXT          0x0c00L
#define DATA_SIZE          ADR_LIST_2 - ADR_LIST_1
/* Maschinentypen des alten Datentraegers */
#define  OD_FM_V2       1001
#define  OD_FX_PU       1020
#define  OD_FX_SP       1030
#define  OD_FX_GER      1040

/* Identifikation fuer "ODGetFilePos" */
#define  ID_HEADER         0
#define  ID_SUBHEADER      1
#define  ID_LIST           2

GLOBAL const DRIVE_MODULE * FMT2_Module();
GLOBAL const FILE_MODULE * FMT2_FileModule();
GLOBAL const DRIVE_MODULE * FMT2_2F_Module();
GLOBAL const FILE_MODULE * FMT2_2F_FileModule();
GLOBAL const DRIVE_MODULE * FMT2_3F_Module();
GLOBAL const FILE_MODULE * FMT2_3F_FileModule();

/* Ergaenzungen fuer 2-und 3-Aggregat-Maschinen
 */
typedef struct {
   signed_16   MashCode;      /* Maschinen-Code */
   signed_16   ProgNr;        /* Kernzugs-Nr. (Sonderprogramm-Nr.) */
   unsigned_8  Diameter;      /* Schneckendurchmesser */
   unsigned_8  PresConst;     /* Umrechnungskonstante fuer Druck */
   signed_16   MashSize;      /* Maschinen-Groesse */
   unsigned_8  Aggregat;      /* Aggregat Ausfuehrung */
   unsigned_8  HeatZoneCount; /* Anzahl Heizzonen */
   signed_32  MatNr;         /* Material-Nr. */
   signed_32  ToolNr;        /* Werkzeug-Nr. */
   signed_8  Date[5];       /* Datum (Jahr-Monat-Tag-Stunde-Minute) */
   unsigned_8  CheckSum;      /* Check-Summe */
   unsigned_8 filler[0x30];
   unsigned_8  Diameter_2;
   unsigned_8  PresConst_2;
   unsigned_8  Aggregat_2;
   unsigned_8  HeatZoneCount_2;
} SUB_HEADER_2F;

typedef struct {
   signed_16   MashCode;      /* Maschinen-Code */
   signed_16   ProgNr;        /* Kernzugs-Nr. (Sonderprogramm-Nr.) */
   unsigned_8  Diameter;      /* Schneckendurchmesser */
   unsigned_8  PresConst;     /* Umrechnungskonstante fuer Druck */
   signed_16   MashSize;      /* Maschinen-Groesse */
   unsigned_8  Aggregat;      /* Aggregat Ausfuehrung */
   unsigned_8  HeatZoneCount; /* Anzahl Heizzonen */
   signed_32  MatNr;         /* Material-Nr. */
   signed_32  ToolNr;        /* Werkzeug-Nr. */
   signed_8  Date[5];       /* Datum (Jahr-Monat-Tag-Stunde-Minute) */
   unsigned_8  CheckSum;      /* Check-Summe */
   unsigned_8 filler[0x30];
   unsigned_8  Diameter_2;
   unsigned_8  PresConst_2;
   unsigned_8  Aggregat_2;
   unsigned_8  HeatZoneCount_2;
   unsigned_8  Diameter_3;
   unsigned_8  PresConst_3;
   unsigned_8  Aggregat_3;
   unsigned_8  HeatZoneCount_3;
} SUB_HEADER_3F;



/* Adressen der Datentraeger-Datei */
#define ADR_SUBHEADER_2F  ADR_SUBHEADER_1
#define ADR_SUBHEADER_3F  ADR_SUBHEADER_1
#define ADR_LIST_2F       0x0060L
#define ADR_LIST_3F       0x0060L
#define DATA_SIZE_2F      0x0500L
#define DATA_SIZE_3F      0x0580L

#endif /* ifndef _fmt2 */
