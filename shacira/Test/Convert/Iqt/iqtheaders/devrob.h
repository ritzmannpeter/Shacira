/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVROB.H
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

#ifndef _devrob
#define _devrob

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
*  ROB-Treiber: DATENTYPEN
*********************************************************************/

typedef struct {
   IQT_HANDLE ControllerHnd;
   int ControllerChannel;
} ROB_PARAM_BLOCK;

typedef struct {
   BYTE Dummy;
} ROB_INIT_BLOCK;

/*********************************************************************
*  ROB-Treiber: VARIABLEN-TYPEN
*********************************************************************/

#define ROB_VAR_MK_PUNKT      0x00L
#define ROB_VAR_DEZ           0x01L
#define ROB_VAR_GANZ          0x02L

/*********************************************************************
*  ROB-Treiber: INDEX-VARIANTEN
*********************************************************************/

#define ROB_ARRAY_NO_INDEX    0x8000L

/*********************************************************************
*  ROB-Treiber: LESE-VARIANTEN
*********************************************************************/

#define ROB_READ_VAR          0x80 | 0x43
#define ROB_READ_RUNTIME_ERR  0x80 | 0x45
#define ROB_READ_POSITION     0x80 | 0x47
#define ROB_READ_IO           0x80 | 0x49
#define ROB_READ_USER_MSG     0x80 | 0x4d
#define ROB_READ_POLLING      0x80 | 0x4e


/*********************************************************************
*   ROB-Treiber: PARAMETER-ARTEN
*********************************************************************/

#define ROB_ID_FILENAME       0
#define ROB_ID_VAR_TYPE       1
#define ROB_ID_VAR_VAL1       2
#define ROB_ID_VAR_VAL2       3
#define ROB_ID_VAR_VAL3       4
#define ROB_ID_VAR_VAL4       5
#define ROB_ID_VAR_VAL5       6
#define ROB_ID_ARRAY_INDEX    7
#define ROB_ID_READ_MODE      8
#define ROB_ID_READ_PAR       9

/*********************************************************************
*   ROB-Treiber: FEHLERCODES
*********************************************************************/

#define ROB_ERR_VAR_TYPE      1

#endif /* ifndef _devrob */