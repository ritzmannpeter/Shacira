/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     PG.H
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
*     VERSION:    4.0                       DATUM:   08.05.92
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*                      Neu entstanden
*     23.09.98 -TSchw- Die Konstante PGR_SOLL_LEN wurde geloescht, sie wird
*                      durch CURVE_VALUES ersetzt. PGR_SOLL_LEN stellte
*                      die Laenge eines Puffers fuer eine Sollwertkurve in
*                      Byte dar und war unter Zugrundelegung eines 16 Bit
*                      integers berechnet. Auf einem 32 Bit System war diese
*                      Konstante um die Haelfte zu klein, was zu einem
*                      schlimmen Ueberschreibfehler mit Programmabbruch
*                      fuehrte.
*     18.02.99 -TSchw- In den Strukturen MODE_INFO und SOLL_INFO wurden
*                      die int-Eintraege durch short int-Eintraeger ersetzt.
*                      Diese beiden Strukturen gehen auf den Datentraeger
*                      und muessen zwecks Kompatibilitaet mit der 16-Bit-Welt
*                      auch weiterhin nur 16 Bit gross sein.
*               01.04.99 -TSchw- PG_ResetZoom eingefuegt.
*               14.04.99 -TSchw- PG_WriteSollCurve, PG_ReadSollCurveXXX Funktionen
*                                                         eingefuegt.
*               21.04.99 -TSchw- TOL_ACTUATE und TOLMAX_ACTUATE neu eingefuegt.
*               22.04.99 -TSchw- CURVE_INFO_TOLERANCE neu eingefuegt.
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

#ifndef _pg
#define _pg

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <dstruct.h>
#include <curves.h>
/*.EI.***********************************************************************/

/* Parameter-Id's fuer Set- und GetParam
 */
#define CURSOR_ID        1
#define MEASURE_STATE    2
#define VALUE_IST_COLOR  3
#define SOFT_MEAS_TIME   4
#define SOLL_ACTUATE     5
#define CURVE_DOWNLOAD   6
#define TOL_ACTUATE      7
#define TOLMAX_ACTUATE   8

#define VISIBLE_CURVES 0
#define ALL_CURVES     1

#define SET_PG_PAGE    0
#define RESET_PG_PAGE  1

#define CURVE_INFO_CURVE_ID         0
#define CURVE_INFO_GROUP_ID         1
#define CURVE_INFO_CTRL             2
#define CURVE_INFO_VALUE_TYPE       3
#define CURVE_INFO_FACTOR_MEAS      4
#define CURVE_INFO_FACTOR_PHYS      5
#define CURVE_INFO_Y_MAX            6
#define CURVE_INFO_COLOR            7
#define CURVE_INFO_DATABUF_0        8
#define CURVE_INFO_DATABUF_1        9
#define CURVE_INFO_REQBLOCK_0      10
#define CURVE_INFO_REQBLOCK_1      12
#define CURVE_INFO_ACKBLOCK        13
#define CURVE_INFO_EVENTBUF        14
#define CURVE_INFO_NOOFUNITS       15
#define CURVE_INFO_TRANSFER_ERROR  16
#define CURVE_INFO_TOLERANCE       17

        
#define ACK_INFO_SIZE              30
#define ACK_INFO_MAX_X             31
#define ACK_INFO_MAX_Y             32
#define ACK_INFO_SCALE1            33
#define ACK_INFO_SCALE2            34
#define ACK_INFO_VALUE_TYPE        35
#define ACK_INFO_SHOT              36

/* Taskkommunikation
 */
#define MSG_ID_TRANSFER_REQUEST     1


/* Macros
 */
#define SET_CURVE_IND(cb_id,ca_ind)  \
  (((0x00000000L | (long)cb_id) << 16) | (0x0000ffffL & (long)ca_ind))
#define GET_CB_ID(p)                ((UWORD) (p >> 16))
#define GET_CA_IND(p)               ((UWORD) (p & 0x0000ffffL))

#define SET_CURVE_DESC(grp,fu,type) ((((UWORD)grp&0x00ff)<<8) | \
                                     (((UWORD)fu&0x000f)<<4) | \
                                     ((UWORD)type&0x000f) )
#define GET_CURVE_TYPE(cu)    ((UWORD)(cu&0x000f))
#define GET_GROUP(cu)         ((UWORD)((cu&0xff00)>>8))
#define GET_FUNCTION_UNIT(cu) ((UWORD)((cu&0x00f0)>>4))

/* Datentraegeroperationen 
 */
#define PG_READ_INIT     1 /* Init. der Leseoperation
                            */
#define PG_READ_NEXT     2 /* Naechste Sollkurve anfordern
                            */

typedef struct { /* Infos ueber die Sollkurven */
        long curve_ident; /* Kurven ID
                      */
        long FE;          /* Funktionseinheit
                      */    
        long FE_NR;       /* Nummer der Funktionseinheit
                      */  
        long count;       /* Anzahl der Kurven Integer-Werte
                      */
} PG_SOLL_INFO_NEU;

typedef struct {    /* Einstellung der Prozessgrafik */
    short int mode;           /* Betriebsart */
    short int delay;          /* Startverzoegerung */
    short int time;           /* Messzeit */
    short int mint;           /* Messintervall */
    short int vinter;         /* Geschw.intervall */
} MODE_INFO;

typedef struct { /* Infos ueber die Sollkurven */
    short int magic;
    MODE_INFO mode_info;
    short int soll_chan[2];
    short int soll_max[2];
    short int tol[2];
} SOLL_INFO;

#define SOLL_INFO_LEN   100 /* Laenge von "magic" + Info-Struktur + Luft   */
#define PGR_SOLL_LEN   2000 /* Groesse einer einzelnen Sollwertkurve in    */
                            /* Byte. Man geht hier fest von 1000 Werte aus,*/
                            /* wobei ein Wert in einem short integer (16   */
                            /* Byte) codiert ist. Dies laesst sich nicht   */
                            /* aendern, da auch alte Datentraeger noch ein-*/
                            /* gelesen werden muessen, die mit genau diesen*/
                            /* werden abgespeichert wurden.                */
#define PG_BUFFER_SIZE 4100 /* Groesse des gesamten PG-Puffers (2 Soll-    */
                            /* kurven). Diese Groessen muessen so bleiben, */
                            /* weil sie verwendet werden, um auch Puffer   */
                            /* von alten Datentraegern zu lesen, die nun   */
                            /* mal mit diesen Groessen geschrieben wurden. */


GLOBAL int PG_Init( BOOL init_bbram );
GLOBAL int PG_SetPage( BYTE ctrl, BYTE screen );
GLOBAL IQT_HANDLE PG_Draw( ELEMENT * el_ptr, BYTE line, BYTE from, BYTE screen );
GLOBAL int PG_MoveCursor( BYTE direction );
GLOBAL int PG_Zoom();
GLOBAL int PG_ResetZoom(UWORD clip_id);
GLOBAL int PG_SetParam(BYTE param_id, long param);
GLOBAL int PG_GetParam(BYTE param_id, long * param);
GLOBAL long PG_Value( UWORD cb_id, UWORD curve_access_ind, CUR_TYPE cursor_id);
GLOBAL long PG_Max( UWORD cb_id, UWORD curve_access_ind);
GLOBAL long PG_Cursor( UWORD cb_id, CUR_TYPE cursor_id);
GLOBAL long PG_XScale( UWORD cb_id, BYTE pos);
GLOBAL long PG_Info( UWORD ctrl, UWORD id, long val,
                     UWORD ind1, UWORD ind2, UWORD ind3);
GLOBAL int PG_TransReq (UWORD param, UWORD mode);
GLOBAL int PG_ReadSoll( void *buffer );
GLOBAL int PG_WriteSoll( void *buffer );
GLOBAL void *PG_ReadSollCurveInit ();
GLOBAL void  PG_ReadSollCurveDeInit (void *hnd);
GLOBAL UWORD PG_ReadSollCurve (void *hnd, BYTE **pbuf);
GLOBAL int   PG_WriteSollCurve (BYTE *buf, UWORD size);

#endif /* ifndef _pg */


