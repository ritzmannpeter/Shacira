/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVDISK.H
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
*     VERSION:    4.0                       DATUM:   10.04.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*     AUTOR(EN):  -MBa-  M. Bauernfeind     TELEFON: (07644) 78381
*
*  HISTORY:
*     10.04.92 -MBa-   Portierung des IQT-350 auf IQT-450
*                      QNX Floppys definiert
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     14.07.92 -TS-    Neues Fehlerkonzept
*     05.02.98 -TSchw- __WIN32__ -Aenderungen durchgefuehrt
*     12.03.98 -TSchw- DISK_OP_APPEND eingefuegt.
*     14.04.99 -TSchw- DISK_DRV_RAM eingefuegt.
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

#ifndef _devdisk
#define _devdisk

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/*********************************************************************
*  IN IQTDEV.H NACHZUTRAGENDE SPEZIALITAETEN (VORLAEUFIG)
*********************************************************************/

/*********************************************************************
*  DISK-Treiber: DATENTYPEN
*********************************************************************/

typedef struct {
   char * FileName;
   PARAMETER Drive;
   PARAMETER Mode;
   PARAMETER Date;
} DISK_PARAM_BLOCK;

typedef struct {
   ULONG DebugMask;
} DISK_INIT_BLOCK;

typedef struct {
   char FileName[13];
   PARAMETER Date;
   PARAMETER Size;
} DISK_DIR_STRUCT;


/*********************************************************************
*   DISK-Treiber: KONSTANTEN
*********************************************************************/

/* User EPROM */
#define USER_EPROM_START 0x000d8000L
#define USER_EPROM_END   0x000dffffL
#define USER_EPROM_SIZE  32*1024


#define DISK_OP_READ 1              /* Zugriffsmode */
#define DISK_OP_WRITE 2
#define DISK_OP_DELETE 4
#define DISK_OP_CREATE 8
#define DISK_OP_APPEND 32

#define DISK_FMT_LOW   0            /* Formatdichte */
#define DISK_FMT_HIGH  16

#define DISK_DRV_FLO1            0        /* Laufwerkskennung */
#define DISK_DRV_FLO2            1
#define DISK_DRV_EEP1            2
#define DISK_DRV_EEP2            3
#define DISK_DRV_KPROM           4
#define QNX_DISK_DRV_FLO1        5
#define QNX_DISK_DRV_FLO2        6
#define QNX_DISK_DRV_HDISK       7
#define DISK_CURRENT_DIRECTORY   8
#define DISK_DRV_RAM             9

#define DISK_DRV_EEP3           10 /* ??????????????????????? */

#define DISK_VERS_OLD  0x00         /* Versionskennung */
#define DISK_VERS_STD  0x10


/*********************************************************************
*   DISK-Treiber: ZUGRIFFSMACROS
*********************************************************************/

#define DISK_GET_YEAR( p )  ( (BYTE)((p)>>25 & 0x7F)+80 )
#define DISK_GET_MONTH( p ) ( (BYTE)((p)>>21 & 0x0F) )
#define DISK_GET_DAY( p )   ( (BYTE)((p)>>16 & 0x1F) )
#define DISK_GET_HOUR( p )  ( (BYTE)((p)>>11 & 0x1F) )
#define DISK_GET_MIN( p )   ( (BYTE)((p)>>5  & 0x3F) )
#define DISK_GET_SEC( p )   ( (BYTE)((p)<<1  & 0x3E) )

#define DISK_MAKE_DATE( day,month,year,hour,min,sec ) \
   ( (ULONG)(year-80) << 25 | (ULONG)month << 21 | (ULONG)day << 16 | \
     (UWORD)hour << 11 | (UWORD)min << 5 | sec >> 1 )

/*********************************************************************
*   DISK-Treiber: PARAMETER
*********************************************************************/

#define DISK_ID_MODE       0
#define DISK_ID_DRIVE      1
#define DISK_ID_DATE       2
#define DISK_ID_FILEPOS    3
#define DISK_ID_SIZE       4
#define DISK_ID_FREE_SPACE 5
#define DISK_ID_VERSION    6

/*********************************************************************
*   DISK-Treiber: DIAGNOSEFEHLERMELDUNGEN
*********************************************************************/

#endif /* ifndef _devdisk */

