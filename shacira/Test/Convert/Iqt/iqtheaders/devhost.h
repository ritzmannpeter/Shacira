/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVHOST.H
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

#ifndef _devhost
#define _devhost

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <timefunc.h>
/*.EI.***********************************************************************/

typedef struct HostParamBlock {
        IQT_HANDLE ComHnd;
} HOST_PARAM_BLOCK, * HOST_PARAM_PTR;

/*********************************************************************
*  HOST-Treiber: KONSTANTEN FUER DIE PARAMETER
*********************************************************************/

#define HOST_ID_COMHND      1
#define HOST_ID_STATUS      2

/*********************************************************************
*  HOST-Treiber: FEHLERCODES
*********************************************************************/

#define HOST_ERR_ETB_RECEIVED 97
#define HOST_ERR_ENQ_RECEIVED 98
#define HOST_ERR_EOT_RECEIVED 99

/*********************************************************************
*  HOST-Treiber: KONSTANTEN DER CONTROL-FUNKTION
*********************************************************************/

#define HOST_CTRL_FLUSH 1
#define HOST_TIMEOUT   TIME_SET(TIME_SECS,60)


#endif /* ifndef _devhost */