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
   USR_LONG DebugMask;
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

#define DISK_FMT_LOW   0            /* Formatdichte */
#define DISK_FMT_HIGH  16

#define DISK_DRV_FLO1      0        /* Laufwerkskennung */
#define DISK_DRV_FLO2      1
#define DISK_DRV_EEP1      2
#define DISK_DRV_EEP2      3
#define DISK_DRV_KPROM     4
#define QNX_DISK_DRV_FLO1  5
#define QNX_DISK_DRV_FLO2  6
#define QNX_DISK_DRV_HDISK 7

#define DISK_DRV_EEP3      7 /* ??????????????????????? */

#define DISK_VERS_OLD  0x00         /* Versionskennung */
#define DISK_VERS_STD  0x10


/*********************************************************************
*   DISK-Treiber: ZUGRIFFSMACROS
*********************************************************************/

#define DISK_GET_YEAR( p )  ( (USR_BYTE)(((p)>>25) & 0x7F)+80 )
#define DISK_GET_MONTH( p ) ( (USR_BYTE)(((p)>>21) & 0x0F) )
#define DISK_GET_DAY( p )   ( (USR_BYTE)(((p)>>16) & 0x1F) )
#define DISK_GET_HOUR( p )  ( (USR_BYTE)(((p)>>11) & 0x1F) )
#define DISK_GET_MIN( p )   ( (USR_BYTE)(((p)>>5)  & 0x3F) )
#define DISK_GET_SEC( p )   ( (USR_BYTE)(((p)<<1)  & 0x3E) )

#define DISK_MAKE_DATE( day,month,year,hour,min,sec ) \
   ( (USR_LONG)(year-80) << 25 | (USR_LONG)month << 21 | (USR_LONG)day << 16 | \
     (USR_WORD)hour << 11 | (USR_WORD)min << 5 | sec >> 1 )

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


/*********************************************************************
X  TYPEN fuer eigene Task
*********************************************************************/
/* Meldungstypen */
typedef struct devdisk_message {
   USR_BYTE id;
	void * void_ptr1;
	void * void_ptr2;
	void * void_ptr3;
	int int_val1;
	int int_val2;
   int int_val3;
   int int_val4;
   int int_val5;
   int int_val6;
   long long_val1;
   long long_val2;
   } DevDisk_MESSAGE;

typedef struct devdisk_reply {
   int ret;
   void * ret_ptr;
   } DevDisk_REPLY;

#define DEVDISK_ID_DevInit         1
#define DEVDISK_ID_DevOpen         2
#define DEVDISK_ID_DevClose        3
#define DEVDISK_ID_DevRead         4
#define DEVDISK_ID_DevWrite        5
#define DEVDISK_ID_DevControl      6
#define DEVDISK_ID_DevExamine      7
#define DEVDISK_ID_DevSetParam     8
#define DEVDISK_ID_DevGetParam     9


#endif /* ifndef _devdisk */
