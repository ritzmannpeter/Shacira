/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVMEAS.H
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
*     VERSION:    1.0                       DATUM:   05.01.93
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     05.01.93 -PR-  Implementierung
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
/*.EI.***********************************************************************/

/*********************************************************************
*   Messwert-Treiber: Schnittstellenparameter
*********************************************************************/
#define MEAS_ID_CHANNEL               1
#define MEAS_ID_LINE                  2 
#define MEAS_ID_MODE                  3
#define MEAS_ID_START_READ_CURVE      4
#define MEAS_ID_START_WRITE_CURVE     5
#define MEAS_ID_START_READ_REQ        6
#define MEAS_ID_START_WRITE_REQ       7
#define MEAS_ID_START_ACK             8
#define MEAS_ID_ACK_TIMEOUT           9
#define MEAS_ID_START_DATA           10
#define MEAS_ID_START_INFO           11
#define MEAS_ID_CTRL                 12
#define MEAS_ID_CONNECTION_ERROR     13

#define MEAS_ID_RREQ_SIZE            20
#define MEAS_ID_RREQ_FUNCTION        21
#define MEAS_ID_RREQ_FUNCTION_UNIT   22
#define MEAS_ID_RREQ_CURVE_TYPE      23
#define MEAS_ID_RREQ_CURVE_ID        24
#define MEAS_ID_RREQ_VALUE_TYPE      25
#define MEAS_ID_RREQ_SHOT            26
#define MEAS_ID_RREQ_8               28
#define MEAS_ID_RREQ_9               29
#define MEAS_ID_RREQ_10              30
#define MEAS_ID_RREQ_11              31
#define MEAS_ID_RREQ_12              32
#define MEAS_ID_RREQ_13              33
#define MEAS_ID_RREQ_14              34
#define MEAS_ID_RREQ_15              35

#define MEAS_ID_WREQ_SIZE            40
#define MEAS_ID_WREQ_FUNCTION        41
#define MEAS_ID_WREQ_FUNCTION_UNIT   42
#define MEAS_ID_WREQ_CURVE_TYPE      43
#define MEAS_ID_WREQ_CURVE_ID        44
#define MEAS_ID_WREQ_VALUE_TYPE      45
#define MEAS_ID_WREQ_SHOT            46
#define MEAS_ID_WREQ_8               48
#define MEAS_ID_WREQ_9               49
#define MEAS_ID_WREQ_10              50
#define MEAS_ID_WREQ_11              51
#define MEAS_ID_WREQ_12              52
#define MEAS_ID_WREQ_13              53
#define MEAS_ID_WREQ_14              54
#define MEAS_ID_WREQ_15              55

#define MEAS_ID_ACK_SIZE            60
#define MEAS_ID_ACK_MAX_X           61
#define MEAS_ID_ACK_MAX_Y           62
#define MEAS_ID_ACK_SCALE1          63
#define MEAS_ID_ACK_SCALE2          64
#define MEAS_ID_ACK_VALUE_TYPE      65
#define MEAS_ID_ACK_SHOT            66
#define MEAS_ID_ACK_8               68
#define MEAS_ID_ACK_9               69
#define MEAS_ID_ACK_10              70
#define MEAS_ID_ACK_11              71
#define MEAS_ID_ACK_12              72
#define MEAS_ID_ACK_13              73
#define MEAS_ID_ACK_14              74
#define MEAS_ID_ACK_15              75

#define MEAS_ID_INFO_EVENT          80
#define MEAS_ID_INFO_STATE          81

#define MEAS_READ_CURVE            1
#define MEAS_READ_REQBLOCK_READ    2
#define MEAS_READ_REQBLOCK_WRITE   3
#define MEAS_READ_ACKBLOCK         4
#define MEAS_READ_STATE            5
#define MEAS_READ_DATA             6
#define MEAS_WRITE_CURVE          10
#define MEAS_WRITE_REQBLOCK_READ  11
#define MEAS_WRITE_REQBLOCK_WRITE 12
#define MEAS_WRITE_DATA           13

#define MEASURE_COMADR  0

#define START_MEASURE     1
#define END_MEASURE       2
#define CONNECTION_ERROR  3

#define CURVE_DISABLED       0x0001
#define TOLERR_OCCURED       0x0002
#define TOLERR_WORK_OCCURED  0x0004

typedef struct {
   char dummy;
} MEAS_INIT_BLOCK;

/* Info-, Acknowledge- und aehnliche Bloecke
 */
typedef struct req_block {
UWORD size;
UWORD function;
UWORD function_unit;
UWORD curve_type;
UWORD curve_id;
UWORD value_type;
long shot;
UWORD reserved[8];
} REQ_BLOCK, *REQ_BLOCK_PTR;

typedef struct ack_block {
UWORD size;
UWORD max_x;
UWORD max_y;
UWORD scale1;
UWORD scale2;
UWORD value_type;
long shot;
UWORD reserved[8];
} ACK_BLOCK, *ACK_BLOCK_PTR;

typedef struct info_block {
UWORD event;
UWORD state;
} INFO_BLOCK, *INFO_BLOCK_PTR;

/* dasselbe fuer Standard-Prozessgrafik
 */
typedef struct std_req_block {
UWORD curve_id;
UWORD aggregat;
} STD_REQ_BLOCK, *STD_REQ_BLOCK_PTR;

typedef struct std_ack_block {
UWORD size;
} STD_ACK_BLOCK, *STD_ACK_BLOCK_PTR;

typedef struct std_info_block {
UWORD event;
} STD_INFO_BLOCK, *STD_INFO_BLOCK_PTR;

/*********************************************************************
*   Messwert-Treiber: Fehlercodes
*********************************************************************/
#define MEAS_ERR_NO_ACKNOWLEDGE                 -301
#define MEAS_ERR_INVALID_READ_MODE              -302
#define MEAS_ERR_NO_DOWNLOAD_ENABLE             -303
#define MEAS_ERR_INVALID_WRITE_MODE             -304
