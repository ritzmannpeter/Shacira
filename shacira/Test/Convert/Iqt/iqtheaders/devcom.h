/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVCOM.H
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
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*     AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*
*  HISTORY:
*     01.04.92 -TS-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     15.07.92 -PR-    MAX_CEN_ID auf 4 erhoeht
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

#ifndef _devcom
#define _devcom

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
*  COM-Treiber: DATENTYPEN
*********************************************************************/

typedef struct ComParamBlock
{
   PARAMETER  ComID;       /* COM_LPT_1, COM_1 .. COM_4 (0-4) */
   PARAMETER  BaudRate;    /* BAUD_110, _300, _600, _1200, _2400, _4800, _9600 */
   PARAMETER  NumStopBits; /* STOP_1, STOP_1_5, STOP_2 */
   PARAMETER  Parity;      /* PARITY_NO, _ODD, _EVEN */
   PARAMETER  CharLength;  /* CHAR_5, _6, _7, _8 */
} COM_PARAM_BLOCK, * COM_PARAM_PTR;

typedef struct
{
   BYTE Dummy;  /* Momentan keine Funktionen */
} COM_INIT_BLOCK;

/*********************************************************************
*  COM-Treiber: ZUGRIFFSMACROS FUER DIE PARAMETER
*********************************************************************/

/*********************************************************************
*  COM-Treiber: KONSTANTEN FUER DIE PARAMETER
*********************************************************************/

#define COM_ID_DEV_NR      1
#define COM_ID_BAUD_RATE   2
#define COM_ID_STOP_BITS   3
#define COM_ID_PARITY      4
#define COM_ID_CHAR_LEN    5
#define COM_ID_IN_ORDER    6
#define COM_ID_OUT_ORDER   7
#define COM_ID_STATUS      8
#define COM_ID_FILECODE    9
#define COM_ID_CHARS_PENDING  10

/*********************************************************************
*   COM-Treiber: FEHLERCODES
*********************************************************************/

#define COM_ERR_BAD_ID              1  /* Parameterfehler */
#define COM_ERR_BAD_BAUD_RATE       2
#define COM_ERR_BAD_STOP_NUM        3
#define COM_ERR_BAD_PARITY          4
#define COM_ERR_BAD_CHAR_LEN        5

#define COM_ERR_EOF_DETECTED        6  /* Uebertragungsfehler */
#define COM_ERR_EOS_DETECTED        7
#define COM_ERR_TIME_OUT            8
#define COM_ERR_BAD_CHECKSUM        9
#define COM_ERR_BAD_DATA_PROTOCOLL  10
#define COM_ERR_BAD_HARDWARE        11
#define COM_ERR_WHILE_TRANSMISSION  -1 /* muss negativ sein */

#define COM_ERR_ALLREADY_USED       12 /* sonstige Fehler */
#define COM_ERR_UNKNOWN             13

/*********************************************************************
*   COM-Treiber: KONSTANTEN FUER DIE INITIALISIERUNG
*********************************************************************/

#define COM_BAUD_110     110  /* zulaessige Werte fuer die Einstellung der */
#define COM_BAUD_300     300  /* Baudrate */
#define COM_BAUD_600     600
#define COM_BAUD_1200   1200
#define COM_BAUD_2400   2400
#define COM_BAUD_4800   4800
#define COM_BAUD_9600   9600
#define COM_BAUD_19200 19200
#define COM_BAUD_38400 38400
#define COM_BAUD_57600 57600

#define COM_STOP_1         1  /* Zur Einstellung der Stopbits */
#define COM_STOP_1_5       1  /* 1,5 gibts nicht !!!! bei QNX */
#define COM_STOP_2         2

#define COM_PARITY_NONE    0
#define COM_PARITY_ODD     1  /* Fuer die Paritaetsbearbeitung */
#define COM_PARITY_EVEN    3
#define COM_PARITY_MARK    5
#define COM_PARITY_SPACE   7

#define COM_CHAR_5         5  /* Anzahl Bits pro Zeichen */
#define COM_CHAR_6         6
#define COM_CHAR_7         7
#define COM_CHAR_8         8

#define COM_LPT_1   0
#define COM_1   1               
#define COM_2   2   
#define COM_3   3
#define COM_4   4


/* Anzahl der Schnittstellen */
#define COM_NUM_DEVICES  5

/*********************************************************************
*   COM-Treiber: Zulaessige Werte fuer die Fileorders
*********************************************************************/

#define COM_ORDER_BASIC_READ   0x01L   /* Standard READ ohne Protokoll */
#define COM_ORDER_BASIC_WRITE  0x05L   /* Standard WRITE ohne Protokoll */
#define COM_ORDER_ISCOS_READ   0x0aL   /* Lesen mit DATACOM-Protokoll */
#define COM_ORDER_ISCOS_WRITE  0x0bL   /* Schreiben mit DATACOM-Protokoll */
#define COM_ORDER_OPEN_HOST    0x32L   /* Initialisiere HOST-Kommuniaktion */
#define COM_ORDER_READ_HOST    0x33L   /* Lese mit HOST-Protokoll */
#define COM_ORDER_WRITE_HOST   0x34L   /* Schreibe mit HOST-Protokoll */
#define COM_ORDER_FLUSH_HOST   0x35L   /* Signalisiere HOST Uebertragungsende */
#define COM_ORDER_CLOSE_HOST   0x36L   /* Beende HOST-Kommunikation */

#endif /* ifndef _devcom */
