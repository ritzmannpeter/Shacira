/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVISCOS.H
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
*               13-09-96 -PR-    Makro SPS_TIMEOUT(..) zum Testen auf Timeoutfehler
*                                                         eingefuehrt.
*     21.10.96 -PR-    Definitionen fuer erweiterte Parameterschnittstelle
*                                                         Schnittstelle eingefuehrt.
*               14-11-96 -PR-    Makro SPS_ERROR(..) zum Testen auf SPS-Fehler
*                                                         eingefuehrt.
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


/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
#ifndef _i60
#include <i60.h>
#define _i60
#endif
/*.EI.***********************************************************************/


/*********************************************************************
*  IN IQTDEV.H NACHZUTRAGENDE SPEZIALITAETEN (VORLAEUFIG)
*********************************************************************/

/*********************************************************************
*  ISCOS-Treiber: KONSTANTEN UND ALLGEMEINE MAKROS
*********************************************************************/
#define UNKNOWN_SPS             0
#define TEST_SPS                        1
#define BANDR_SPS                       2
#define ISCOS_SPS                       3

#define PROGRAM_STOPPED 0x0001
#define PROGRAM_ERROR   0x0002
#define POWER_FAIL              0x0004
#define FIRMWARE_ERROR  0x0008

#define ISCOS_LOG_CHANNELS    4        /* Anzahl logischer Iscoskanaele
                                        */
#define NR_ISCOS (PPC_CHANNELS*ISCOS_LOG_CHANNELS)   /* Anzahl Iscos */


#define LOG_CHANNEL(p)   (p%ISCOS_LOG_CHANNELS)
#define PHYS_CHANNEL(p)  (p/ISCOS_LOG_CHANNELS)

/* ISCOS-Kommunikationsadressen */
#define ISCOS_I0  0
#define ISCOS_I1  1
#define ISCOS_I2  2
#define ISCOS_I3  3

/* Spezialbefehle fuer ISCOS-Kommunikation */
#define ISCOS_GENERAL    0       /* Beliebiges ISCOS-Kommando */
#define ISCOS_LOGIC      1       /* Uebertragen von Logikwort-Bereichen */
#define ISCOS_REGISTER   2       /* Uebertragen von Registerbereichen */
#define ISCOS_SET_BIT    3       /* Setzen eines Bits */
#define ISCOS_RESET_BIT  4       /* Ruecksetzen eines Bits */
#define ISCOS_DATA_BLOCK 5       /* Uebertragen vonm Fkt.- und Datenblock */
#define ISCOS_VERSION    6       /* Version der PPCCOM Task lesen */
#define ISCOS_NEXT_DATA  7       /* Anforderung eines ewiteren Datenblocks */

/* ISCOS-Funktionen A-SET */
#define ICMD_MS   0x81     /* display module map/status */
#define ICMD_IB   0x82     /* input buffer */
#define ICMD_OB   0x83     /* output buffer */
#define ICMD_DR   0x84     /* display register */
#define ICMD_ER   0x85     /* enter register */
#define ICMD_DP   0x86     /* dump user module */
#define ICMD_SS   0x87     /* start/stop control action */

/* ISCOS-Funktionen B-SET */
#define ICMD_CM   0x88     /* create user module */
#define ICMD_DU   0x89     /* delete user module */
#define ICMD_LP   0x8a     /* list user module */
#define ICMD_SM   0x8b     /* set mode RAM/PROM */
#define ICMD_OA   0x8c     /* load PROM into RAM */
#define ICMD_AO   0x8d     /* load RAM into EEPROM */
#define ICMD_IS   0x8e     /* insert instruction(s) */
#define ICMD_CH   0x8f     /* change instruction(s) */
#define ICMD_DE   0x90     /* delete instruction(s) */
#define ICMD_SB   0x91     /* set breakpoint */
#define ICMD_NB   0x92     /* next breakpoint */
#define ICMD_RB   0x93     /* reset breakpoint */
#define ICMD_DG   0x94     /* declare "general" module */
#define ICMD_DC   0x95     /* declare "carrier" module */
#define ICMD_SE   0x96     /* search instruction(s) */
#define ICMD_CF   0x97     /* configuration list */

/* ISCOS-Funktionen C-SET */
#define ICMD_GI   0x9a     /* get ident */
#define ICMD_LU   0x9b     /* load user module */
#define ICMD_SU   0x9c     /* save user module */
#define ICMD_LC   0x9d     /* load carrier modules */
#define ICMD_SC   0x9e     /* save carrier modules */
#define ICMD_LL   0x9f     /* load logic buffer(s) */
#define ICMD_SL   0xa0     /* save logic buffer(s) */
#define ICMD_LR   0xa1     /* load register(s) */
#define ICMD_SR   0xa2     /* save register(s) */
#define ICMD_GM   0xa3     /* get message */

/* ISCOS-Funktionen C-SET */
#define ICMD_DM   0xa4     /* display memory */
#define ICMD_WM   0xa5     /* write memory */

/* Kennungen der ISCOS-Info-Bloecke */
#define INFO_OK_READY  0x00   /* OK/READY - Keine Parameter */
#define INFO_ERROR     0x01   /* ERROR - Fehlercode (16 Bit) */
#define INFO_NO_DATA   0x02   /* NO DATA - Keine Parameter */
#define INFO_LAST_DATA 0x03   /* LAST DATA - Max. 256 Bytes Daten */
#define INFO_DATA      0x04   /* DATA - Max. 256 Bytes Daten */
#define INFO_IDENT     0x05   /* IDENT -  Release-Nr * 100 of firmware */
#define INFO_ABORT     0x06   /* ABORT - Abort message */

/* Maximale Anzahl der Parameter im CMDBLOCK */
#define ICMD_MAX_PARAM  6

/*********************************************************************
*  ISCOS-Treiber: DATENTYPEN
*********************************************************************/

typedef struct {
        int channel;
   char * stty;
   long baud;
   char parity;
   char stop_bits;
   char data_bits;
   UWORD com_adr;
} ISCOS_PARAM_BLOCK;

typedef struct {
   char dummy;
} ISCOS_INIT_BLOCK;

typedef struct {
   BYTE cmdnum;                /* Kommandonummer ICMD_xx */
   BYTE params;                /* Anzahl Parameter 0..ICMD_MAX_PARAM */
   UWORD param[ICMD_MAX_PARAM]; /* Werte fuer Parameter */
} CMDBLOCK;

#define CHANNEL_ACTIVE          0
#define CHANNEL_INACTIVE        1

/*********************************************************************
*   ISCOS-Treiber: SCHNITTSTELLENPARAMETER
*********************************************************************/
#define ISCOS_ID_COMADR                 0
#define ISCOS_ID_TYPE                   1
#define ISCOS_ID_START                  2
#define ISCOS_ID_CMDPTR                 3
#define ISCOS_ID_INFO                   4
#define ISCOS_ID_CHANNEL                5
#define ISCOS_ID_SPS_TYPE               6
#define ISCOS_ID_SPS_VERSION    7
#define ISCOS_ID_SPS_STATE              8
#define ISCOS_ID_CHANNEL_STATE  9

/*********************************************************************
*   ISCOS-Treiber: FEHLERCODES
*********************************************************************/

#define SPS_TIMEOUT(err)                I60_TIMEOUT(err)
#define SPS_ERROR(err)                  I60_SPS_ERROR(err)

#define DEVISCOS_INVALID_COMADR         -1201
#define DEVISCOS_BAD_COMMAND                    -1202
#define DEVISCOS_OPEN                                   -1203
#define DEVISCOS_BIT                                            -1204
#define DEVISCOS_READ                                   -1205
#define DEVISCOS_PROTOCOL                               -1206
#define DEVISCOS_WRITE                                  -1207
#define DEVISCOS_DEVICE_NOT_OPEN                -1208
#define DEVISCOS_CLOSE                                  -1209
#define DEVISCOS_CHANNEL_INACTIVE       -1210

#define ISCOS_ERR_PARAM_COUNT       1
#define ISCOS_ERR_MOD_OUT_OF_RANGE  2
#define ISCOS_ERR_MOD_AREA_SIZE     3
#define ISCOS_ERR_MOD_NUMBER        4
#define ISCOS_ERR_MOD_NOT_PRESENT   5
#define ISCOS_ERR_TIMEOUT               6
/* ... usw. ... */
/* Wird bei Gelegenheit mal ergaenzt. Der Autor. */

