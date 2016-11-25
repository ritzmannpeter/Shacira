
#ifndef _FMFatFileH
#define _FMFatFileH

#include "FileBuffer.h"
#include "Legacy.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Legacy definitions
 */
typedef struct
{  unsigned_16 id;
   signed_32 offset;
}  FILE_SUBFILE_T;

typedef struct
{  unsigned_16 id;
   unsigned_8 cols;
   unsigned_8 rows;
   unsigned_16 length;
}  TEXT_IDENT;

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
   signed_16       ProgNr;                    /* Sonderprogramm-Nr */
   signed_16       Diameter;                  /* Schneckendurchmesser */
   signed_16       PresConst;                 /* Umrechnungskonstante fuer Druck */
   signed_16       MashSize;                  /* Maschinen-Groesse */
   unsigned_8      Aggregat;                  /* Aggregat Ausfuehrung */
   unsigned_8      HeatZoneCount;             /* Anzahl Heizzonen */
   signed_16       ScrewSuckBack;             /* Auswahl Schneckenrueckzug */
   signed_16       PlastWay;                  /* Plastifizierweg */
   signed_16       MouldOpWay;                /* Werkzeugoeffnungsweg */
   unsigned_8      VersMash;                  /* Maschinen-Version */
   unsigned_8      VersStruct;                /* Datenstruktur-Version */
   unsigned_8      VersExtra;                 /* spezielle Versions-Nr. */
   signed_16       Reserved1;                 /* Reserve 1 */
   signed_16       Reserved2;                 /* Reserve 2 */
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
   /* 4-Farben */
   signed_16         MouldInPres4;              /* Stufe fuer Wkz-Innendruck. Agg4 */
   signed_16         MaxSpritzDruck4;           /* Maximaler Einspritzdruck   Agg4 */
   signed_16         Diameter4;                 /* Schneckendurchmesser       Agg4 */
   signed_16         PresConst4;                /* Umrechnungskonst. Druck    Agg4 */
   unsigned_8        Aggregat4;                 /* Aggregat Ausfuehrung       Agg4 */
   unsigned_8        HeatZoneCount4;            /* Anzahl Heizzonen           Agg4 */
   signed_16         ScrewSuckBack4;            /* Auswahl Schneckenrueckzug  Agg4 */
   signed_16         PlastWay4;                 /* Plastifizierweg            Agg4 */
   /* 5-Farben */
   signed_16         MouldInPres5;              /* Stufe fuer Wkz-Innendruck. Agg5 */
   signed_16         MaxSpritzDruck5;           /* Maximaler Einspritzdruck   Agg5 */
   signed_16         Diameter5;                 /* Schneckendurchmesser       Agg5 */
   signed_16         PresConst5;                /* Umrechnungskonst. Druck    Agg5 */
   unsigned_8        Aggregat5;                 /* Aggregat Ausfuehrung       Agg5 */
   unsigned_8        HeatZoneCount5;            /* Anzahl Heizzonen           Agg5 */
   signed_16         ScrewSuckBack5;            /* Auswahl Schneckenrueckzug  Agg5 */
   signed_16         PlastWay5;                 /* Plastifizierweg            Agg5 */
   /* 6-Farben */
   signed_16         MouldInPres6;              /* Stufe fuer Wkz-Innendruck. Agg6 */
   signed_16         MaxSpritzDruck6;           /* Maximaler Einspritzdruck   Agg6 */
   signed_16         Diameter6;                 /* Schneckendurchmesser       Agg6 */
   signed_16         PresConst6;                /* Umrechnungskonst. Druck    Agg6 */
   unsigned_8        Aggregat6;                 /* Aggregat Ausfuehrung       Agg6 */
   unsigned_8        HeatZoneCount6;            /* Anzahl Heizzonen           Agg6 */
   signed_16         ScrewSuckBack6;            /* Auswahl Schneckenrueckzug  Agg6 */
   signed_16         PlastWay6;                 /* Plastifizierweg            Agg6 */
   /* 7-Farben */
   signed_16         MouldInPres7;              /* Stufe fuer Wkz-Innendruck. Agg7 */
   signed_16         MaxSpritzDruck7;           /* Maximaler Einspritzdruck   Agg7 */
   signed_16         Diameter7;                 /* Schneckendurchmesser       Agg7 */
   signed_16         PresConst7;                /* Umrechnungskonst. Druck    Agg7 */
   unsigned_8        Aggregat7;                 /* Aggregat Ausfuehrung       Agg7 */
   unsigned_8        HeatZoneCount7;            /* Anzahl Heizzonen           Agg7 */
   signed_16         ScrewSuckBack7;            /* Auswahl Schneckenrueckzug  Agg7 */
   signed_16         PlastWay7;                 /* Plastifizierweg            Agg7 */
   /* 8-Farben */
   signed_16         MouldInPres8;              /* Stufe fuer Wkz-Innendruck. Agg8 */
   signed_16         MaxSpritzDruck8;           /* Maximaler Einspritzdruck   Agg8 */
   signed_16         Diameter8;                 /* Schneckendurchmesser       Agg8 */
   signed_16         PresConst8;                /* Umrechnungskonst. Druck    Agg8 */
   unsigned_8        Aggregat8;                 /* Aggregat Ausfuehrung       Agg8 */
   unsigned_8        HeatZoneCount8;            /* Anzahl Heizzonen           Agg8 */
   signed_16         ScrewSuckBack8;            /* Auswahl Schneckenrueckzug  Agg8 */
   signed_16         PlastWay8;                 /* Plastifizierweg            Agg8 */
   } FILE_HEADER;

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
#define  TAB_PG               5  /* Prozessgraphik Sollkurven alte Version      */
#define  TAB_HEATTEXT         6
#define  TAB_PG_NEW           7  /* Prozessgraphik Sollkurven neue Version      */

/* Teildatei-Typen */
#define  DISK_ID_IQTREG          1
#define  DISK_ID_ISCOSREG        2
#define  DISK_ID_ISCOSBIT        3
#define  DISK_ID_TEXT            4
#define  DISK_ID_PG              5
#define  DISK_ID_ROB_REG         6
#define  DISK_ID_ROB_TEXT        7
#define  DISK_ID_SETUP           10
#define  DISK_ID_SETUP_TEXT      11
#define  DISK_ID_FOT             12
#define  DISK_ID_ABGL            13
#define  DISK_ID_HEATTEXT        14
#define  DISK_ID_PG_NEW          15
#define  DISK_ID_PG_IQTREG       16
#define  DISK_ID_PG_ISCOSREG     17
#define  DISK_ID_CORE_IQTREG     18        /* CORE */
#define  DISK_ID_CORE_ISCOSREG  19    /* CORE */
#define  DISK_ID_PTRTAB          99    /* wird stets gespeichert */

typedef struct
{
   unsigned_8 Id;      /* Id der Teildatei */
   unsigned_8 Tab;     /* zugehoerige Register- oder Text-Tabelle */
   const char * Text;  /* auszugebender Text */
}  SUBFILE_TAB;

#define START_ISCOS_BITS      0        /* ISCOS-Bits gehen ab 0 los */
#define START_ISCOS_BITS_KERN 1500     /* ISCOS-Kern-Bits gehen ab 1500 los */
#define START_IQT_BITS        2000     /* IQT-Bits gehen ab 2000 los */
#define START_ISCOS_REGS      3000     /* ISCOS-Register gehen ab 3000 los */
#define START_ISCOS_REGS_KERN 15000    /* ISCOS-Kern-Reg. gehen ab 15000 los */
#define START_REGLER_REGS     19000    /* Regler-Register gehen ab 19800 los */
#define START_IQT_REGS        20000    /* IQT-Register gehen ab 20000 los */
#define START_IQT_REGS_KERN   30000    /* IQT-Kern-Regs gehen ab 30000 los */

/* Die folgende Konstanten setzen die Grenzen der Registernummern fuer die
   einzelnen Registertypen fest. Die Registernummer eines Typs muss kleiner
   als ihr REGMAX und grosser oder gleich dem naechstunteren REGMAX sein. */
#define REGMAX_ISCOS_BIT      2000
#define REGMAX_IQT_BIT        3000
#define REGMAX_ISCOS_REG     19000
#define REGSTART_CYLHEAT_REG 19000
#define REGMAX_CYLHEAT_REG   19100
#define REGMAX_TOOLHEAT_REG  19200
#define REGMAX_TEMPHEAT_REG  19300
#define REGMAX_OILHEAT_REG   19400
#define REGMAX_GENHEAT_REG   19500
#define REGMAX_RESHEAT_REG   19600
#define REGMAX_HEAT_REG      20000
#define REGMAX_IQT_REG       32000

#define IS_HEATREG(id) ((id)>=REGSTART_CYLHEAT_REG && (id)<REGMAX_HEAT_REG)

/* additional semantic definitions
 */

#define  TEXTVAR_MASHINE          1
#define  TEXTVAR_ORDER            2
#define  TEXTVAR_PERSONAL         3
#define  TEXTVAR_MATERIAL         4
#define  TEXTVAR_TOOL             5
#define  TEXTVAR_ART              6
#define  TEXTVAR_FREEPAGE1        7
#define  TEXTVAR_FREEPAGE2        8
#define  TEXTVAR_DISK_INFO        9
#define  TEXTVAR_FREEPAGE3       10
#define  TEXTVAR_FREEPAGE4       11
#define  TEXTVAR_COLOR_TYPE      12
#define  TEXTVAR_COLOR           13
#define  TEXTVAR_MTYPE           14
#define  TEXTVAR_ROB_PGM         15
#define  TEXTVAR_ROB_MACRO       16
#define  TEXTVAR_ROB_PAR_TYPE    17
#define  TEXTVAR_ROB_PAR_NAME    18
#define  TEXTVAR_ROB_HEADPOINT   19
#define  TEXTVAR_VERSION         20
/* 21-30 Windsor specific */

#define  TEXTVAR_PASSWORD        31
#define  TEXTVAR_HEATCHANTYPE    32
#define  TEXTVAR_SPEC_PROG_LINE  33
#define  TEXTVAR_SPEC_PROG_NAME  34
#define  TEXTVAR_FREETEXT        35
#define  TEXTVAR_MOVEMENT        36
#define  TEXTVAR_FREEDIAG        37

/* Abnahmeprotokoll Texte: */
#define  TEXTVAR_RUNOFF          38

#define MAX_SUBFILES    30
#define MAX_TEXTS       50
#define MAX_REGS        3000

#define INJHEAT         19000    /* Zylinderheizung         */
#define TOOLHEAT        19100    /* Heisskanaele S. 33      */
#define TEMPHEAT        19200    /* Temperiergeraete S. 34  */
#define OILHEAT         19300    /* Oelheizung S. 15        */
#define RESHEAT         19400    /* Reserveheizung          */

typedef struct
{  unsigned_16 id;
   signed_16 subfiles;
   unsigned_32 buf_size;
   FILE_SUBFILE_T * subfile_buf;
}  SUBFILE_TAB_T;

typedef struct
{
   unsigned_16 subfile_id;
   void * buffer;
   unsigned_32 size;
   signed_32 offset;
   const char * description;
   unsigned_16 changes;
}  SUBFILE_T;

typedef struct
{
   unsigned_16 reg_no;
   unsigned_8 reg_type;
   unsigned_8 size;
   unsigned_8 value_size;
   void * buffer;
   unsigned_16 subfile_id;
}  REGISTER_T;
#define DIM(reg) (reg->size / reg->value_size)

typedef struct
{  unsigned_16 id;
   unsigned_8 cols;
   unsigned_8 rows;
   unsigned_16 length;
   unsigned_16 size;
   void * buffer;
   unsigned_16 subfile_id;
}  TEXT_T;
#define STARTPOS(text,row)       (((char*)text->buffer) + (row * text->cols))
#define ROW_WIDTH(text)          (text->cols)

typedef struct
{
   unsigned_16 zone_id;
   unsigned_16 unit_id;
   void * buffer;
}  ZONE_T;

#define MAX_ZONES       100
#define MAX_HEAT_GROUPS 10
typedef struct
{  unsigned_16 heatgroup;
   unsigned_8 reg_type;
   unsigned_16 reg_count;
   unsigned_16 stored_zones;
   unsigned_16 zone_count;
   unsigned_16 unit_count;
   ZONE_T * zone[MAX_ZONES];
   unsigned_16 subfile_id;
}  HEATGROUP_T;

typedef int (*GET_REG_VAL)(void * buf, unsigned_16 reg_no, long * val);
typedef int (*GET_REG_VAL_I)(void * buf, unsigned_16 reg_no, unsigned_16 index, long * val);
typedef int (*SET_REG_VAL)(void * buf, unsigned_16 reg_no, long val);
typedef int (*SET_REG_VAL_I)(void * buf, unsigned_16 reg_no, unsigned_16 index, long val);
typedef int (*GET_TEXT_ROW)(void * buf, unsigned_16 text_id, unsigned_16 row,
                            void * buffer, unsigned_32 buf_size);
typedef int (*SET_TEXT_ROW)(void * buf, unsigned_16 text_id, unsigned_16 row,
                            void * buffer, unsigned_32 buf_size);
typedef int (*GET_TEXT)(void * buf, unsigned_16 text_id, void * buffer, unsigned_32 buf_size);
typedef int (*SET_TEXT)(void * buf, unsigned_16 text_id, void * buffer, unsigned_32 buf_size);
typedef int (*GET_HEAT_PARAM)(void * buf, unsigned_16 group_id, unsigned_16 zone_id,
                              unsigned_16 unit_id, unsigned_16 param, long * val);
typedef int (*SET_HEAT_PARAM)(void * buf, unsigned_16 group_id, unsigned_16 zone_id,
                              unsigned_16 unit_id, unsigned_16 param, long val);
typedef int (*GET_REG_COUNT)(void * buf, unsigned_16 group_id, int * val);
typedef int (*GET_ZONE_COUNT)(void * buf, unsigned_16 group_id, int * val);
typedef int (*GET_UNIT_COUNT)(void * buf, unsigned_16 group_id, int * val);
typedef int (*GET_STORED_ZONES)(void * buf, unsigned_16 group_id, int * val);


typedef int (*GET_DATE)(void * buf, unsigned_32 * date);
typedef int (*SET_DATE)(void * buf, unsigned_32 date);
typedef int (*GET_VERSION)(void * buf, unsigned_8 * version);
typedef int (*SET_VERSION)(void * buf, unsigned_8 version);
typedef int (*GET_HEADER_SIZE)(void * buf, unsigned_8 * header_size);
typedef int (*SET_HEADER_SIZE)(void * buf, unsigned_8 header_size);
typedef int (*GET_FILE_TYPE)(void * buf, unsigned_8 * file_type);
typedef int (*SET_FILE_TYPE)(void * buf, unsigned_8 file_type);
typedef int (*GET_REG_TYPE)(void * buf, unsigned_8 * reg_type);
typedef int (*SET_REG_TYPE)(void * buf, unsigned_8 reg_type);
typedef int (*GET_PROG_NR)(void * buf, signed_16 * prog_nr);
typedef int (*SET_PROG_NR)(void * buf, signed_16 prog_nr);
typedef int (*GET_MAX_AGG)(void * buf, signed_16 * max_agg);
typedef int (*SET_MAX_AGG)(void * buf, signed_16 max_agg);
typedef int (*GET_MASH_SIZE)(void * buf, signed_16 * mash_size);
typedef int (*SET_MASH_SIZE)(void * buf, signed_16 mash_size);
typedef int (*GET_MOULD_OP_WAY)(void * buf, signed_16 * mould_op_way);
typedef int (*SET_MOULD_OP_WAY)(void * buf, signed_16 mould_op_way);
typedef int (*GET_VERS_MASH)(void * buf, unsigned_8 * vers_mash);
typedef int (*SET_VERS_MASH)(void * buf, unsigned_8 vers_mash);
typedef int (*GET_VERS_STRUCT)(void * buf, unsigned_8 * vers_struct);
typedef int (*SET_VERS_STRUCT)(void * buf, unsigned_8 vers_struct);
typedef int (*GET_VERS_EXTRA)(void * buf, unsigned_8 * vers_extra);
typedef int (*SET_VERS_EXTRA)(void * buf, unsigned_8 vers_extra);
typedef int (*GET_RESERVED1)(void * buf, signed_16 * reserved1);
typedef int (*SET_RESERVED1)(void * buf, signed_16 reserved1);
typedef int (*GET_RESERVED2)(void * buf, signed_16 * reserved2);
typedef int (*SET_RESERVED2)(void * buf, signed_16 reserved2);

typedef int (*GET_PLAST_WAY)(void * buf, signed_16 index, signed_16 * plast_way);
typedef int (*SET_PLAST_WAY)(void * buf, signed_16 index, signed_16 plast_way);
typedef int (*GET_HEAT_ZONE_COUNT)(void * buf, signed_16 index, unsigned_8 * heat_zone_count);
typedef int (*SET_HEAT_ZONE_COUNT)(void * buf, signed_16 index, unsigned_8 heat_zone_count);
typedef int (*GET_MAX_SPRITZ_DRUCK)(void * buf, signed_16 index, signed_16 * max_spritz_druck);
typedef int (*SET_MAX_SPRITZ_DRUCK)(void * buf, signed_16 index, signed_16 max_spritz_druck);
typedef int (*GET_MOULD_IN_PRES)(void * buf, signed_16 index, signed_16 * mould_in_press);
typedef int (*SET_MOULD_IN_PRES)(void * buf, signed_16 index, signed_16 mould_in_press);
typedef int (*GET_DIAMETER)(void * buf, signed_16 index, signed_16 * diameter);
typedef int (*SET_DIAMETER)(void * buf, signed_16 index, signed_16 diameter);
typedef int (*GET_PRES_CONST)(void * buf, signed_16 index, signed_16 * pres_const);
typedef int (*SET_PRES_CONST)(void * buf, signed_16 index, signed_16 pres_const);
typedef int (*GET_AGGREGAT)(void * buf, signed_16 index, unsigned_8 * aggregat);
typedef int (*SET_AGGREGAT)(void * buf, signed_16 index, unsigned_8 aggregat);
typedef int (*GET_SCREW_SUCK_BACK)(void * buf, signed_16 index, signed_16 * screw_suck_back);
typedef int (*SET_SCREW_SUCK_BACK)(void * buf, signed_16 index, signed_16 screw_suck_back);

typedef int (*GET_MASH_TYPE)(void * buf, void * buffer, signed_16 buf_size);
typedef int (*SET_MASH_TYPE)(void * buf, void * mash_type);
typedef int (*GET_MAT_NR)(void * buf, void * buffer, signed_16 buf_size);
typedef int (*SET_MAT_NR)(void * buf, void * mat_nr);
typedef int (*GET_TOOL_NR)(void * buf, void * buffer, signed_16 buf_size);
typedef int (*SET_TOOL_NR)(void * buf, void * tool_nr);
typedef int (*GET_INFO_TEXT)(void * buf, void * buffer, signed_16 buf_size);
typedef int (*SET_INFO_TEXT)(void * buf, void * info_text);


typedef FILE_HEADER FILE_HEADER_T;
typedef int (*HEADER_CALLBACK_T)(FILE_HEADER_T * header, void * object);
typedef int (*SUBFILE_TAB_CALLBACK_T)(SUBFILE_TAB_T * subfile_tab, void * object);
typedef int (*SUBFILE_CALLBACK_T)(SUBFILE_T * subfile, void * object);
typedef int (*REGISTER_CALLBACK_T)(REGISTER_T * reg, void * object);
typedef int (*TEXT_CALLBACK_T)(TEXT_T * text, void * object);
typedef int (*HEATGROUP_CALLBACK_T)(HEATGROUP_T * heatgroup, void * object);
typedef int (*ZONE_CALLBACK_T)(ZONE_T * zone, void * object);
typedef struct
{
   void * object;
   HEADER_CALLBACK_T Header;
   SUBFILE_TAB_CALLBACK_T SubfileTab;
   SUBFILE_CALLBACK_T Subfile;
   REGISTER_CALLBACK_T Register;
   TEXT_CALLBACK_T Text;
   HEATGROUP_CALLBACK_T Heatgroup;
   ZONE_CALLBACK_T Zone;
}  FMFAT_BUFFER_CALLBACK_MODULE_T;

typedef struct
{
   FILE_HEADER_T * header;
   SUBFILE_TAB_T * subfile_tab;
   SUBFILE_T * subfile[MAX_SUBFILES];
   TEXT_T * text[MAX_TEXTS];
   REGISTER_T * reg[MAX_REGS];
   HEATGROUP_T * heatgroup[MAX_HEAT_GROUPS];
   FMFAT_BUFFER_CALLBACK_MODULE_T * Module;
   GET_REG_VAL GetRegVal;
   GET_REG_VAL_I GetRegValI;
   SET_REG_VAL SetRegVal;
   SET_REG_VAL_I SetRegValI;
   GET_TEXT_ROW GetTextRow;
   SET_TEXT_ROW SetTextRow;
   GET_TEXT GetText;
   SET_TEXT SetText;
   GET_HEAT_PARAM GetHeatParam;
   SET_HEAT_PARAM SetHeatParam;
   GET_REG_COUNT GetRegCount;
   GET_ZONE_COUNT GetZoneCount;
   GET_UNIT_COUNT GetUnitCount;
   GET_STORED_ZONES GetStoredZones;
   GET_MASH_TYPE Get_MashType;
   SET_MASH_TYPE Set_MashType;
   GET_DATE Get_Date;
   SET_DATE Set_Date;
   GET_MAX_AGG Get_MaxAgg;
   SET_MAX_AGG Set_MaxAgg;
   GET_MASH_SIZE Get_MashSize;
   SET_MASH_SIZE Set_MashSize;
   GET_MOULD_OP_WAY Get_MouldOpWay;
   SET_MOULD_OP_WAY Set_MouldOpWay;
   GET_PLAST_WAY Get_PlastWay;
   SET_PLAST_WAY Set_PlastWay;
   GET_HEAT_ZONE_COUNT Get_HeatZoneCount;
   SET_HEAT_ZONE_COUNT Set_HeatZoneCount;
   GET_MAX_SPRITZ_DRUCK Get_MaxSpritzDruck;
   SET_MAX_SPRITZ_DRUCK Set_MaxSpritzDruck;
   GET_MAT_NR Get_MatNr;
   SET_MAT_NR Set_MatNr;
   GET_TOOL_NR Get_ToolNr;
   SET_TOOL_NR Set_ToolNr;
   GET_INFO_TEXT Get_InfoText;
   SET_INFO_TEXT Set_InfoText;   
   GET_MOULD_IN_PRES Get_MouldInPres;
   SET_MOULD_IN_PRES Set_MouldInPres;
   GET_DIAMETER Get_Diameter;
   SET_DIAMETER Set_Diameter;
   GET_PRES_CONST Get_PresConst;
   SET_PRES_CONST Set_PresConst;
   GET_AGGREGAT Get_Aggregat;
   SET_AGGREGAT Set_Aggregat;
   GET_SCREW_SUCK_BACK Get_ScrewSuckBack;
   SET_SCREW_SUCK_BACK Set_ScrewSuckBack;
   GET_VERSION Get_Version;
   SET_VERSION Set_Version;
   GET_HEADER_SIZE Get_HeaderSize;
   SET_HEADER_SIZE Set_HeaderSize;
   GET_FILE_TYPE Get_FileType;
   SET_FILE_TYPE Set_FileType;
   GET_REG_TYPE Get_RegType;
   SET_REG_TYPE Set_RegType;
   GET_PROG_NR Get_ProgNr;
   SET_PROG_NR Set_ProgNr;
   GET_VERS_MASH Get_VersMash;
   SET_VERS_MASH Set_VersMash;
   GET_VERS_STRUCT Get_VersStruct;
   SET_VERS_STRUCT Set_VersStruct;
   GET_VERS_EXTRA Get_VersExtra;
   SET_VERS_EXTRA Set_VersExtra;
   GET_RESERVED1 Get_Reserved1;
   SET_RESERVED1 Set_Reserved1;
   GET_RESERVED2 Get_Reserved2;
   SET_RESERVED2 Set_Reserved2;
}  FMFAT_BUFFER_T;

int GetLastErr();
int GetLine();
const char * FileName(int id);
int FileType(int id);

#define _CALLBACK_(buf, func, obj) \
   if (buf->Module != NULL) { \
      if (buf->Module->func != NULL) { \
         buf->Module->func(obj, buf->Module->object); \
      } \
   }

FMFAT_BUFFER_T * NewFatBuffer(FILE_BUFFER_T * fbuf, FMFAT_BUFFER_CALLBACK_MODULE_T * module);
int WriteFatBuffer(FMFAT_BUFFER_T * fmfat_buf, FILE_BUFFER_T * fbuf);
int DeleteFatBuffer(FMFAT_BUFFER_T * buffer);

#ifdef __cplusplus
}
#endif

#endif /* ifndef _FMFatFileH */




