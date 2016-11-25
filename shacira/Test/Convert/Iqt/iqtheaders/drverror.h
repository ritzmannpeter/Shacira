/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DRVERROR.H
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
*     VERSION:    4.0                       DATUM:   06.07.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     11.03.02 -HA-    Von bde.h übernommen und angepasst.
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

#ifndef _drverror
#define _drverror

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Allgemeine Konstanten
****************************************************************************/
#include <packstart.h>
typedef struct {
   UWORD Id;                     /* Drive-Id */
   UWORD Code;                   /* Drive-Error-Code */
   ULONG Info;                   /* Drive-Error-Info */
   UWORD Par_ID;                 /* Drive-ParId */
   UWORD Jahr;                   /* Datum: Jahr */
   UWORD M_T_S;                  /* Datum: Monat Tag Stunde */
   UWORD M_S;                    /* Datum: Minute Sekunde */
} STRUCT_PACKED DRV_ERROR;
#include <packstop.h>

#define DRVERROR_INR    0 /* Iscos-Nummer des Registers */
#define DRVERROR_REGS   8 /* Anzahl der zu lesenden Register je Diag.Modul */

/****************************************************************************
X  Konstanten fuer DRVERR_PageScroll()
****************************************************************************/
#define DRVERR_SCROLL_UP               0
#define DRVERR_SCROLL_DOWN             1

/****************************************************************************
X  Id's fuer DRVERR_SetParam() und DRVERR_GetParam()
****************************************************************************/
#define DRVERR_ID_GET_STOP_MSG         0
#define DRVERR_ID_SET_ACT_VARNR        1
#define DRVERR_ID_NEW_STOP_MSG         2
#define DRVERR_ID_PRINT_ORDER          3
#define DRVERR_ID_PRINT_LEGEND         4
#define DRVERR_ID_CHANGE_PRINT_MODE    5
#define DRVERR_ID_CLEAR_BUFFER         6
#define DRVERR_ID_INC_MINUTES          7
#define DRVERR_ID_PRINT_TO_DISK        8


/****************************************************************************
X  Funktionen
****************************************************************************/
GLOBAL int DRVERR_Init (BOOL init_bbram);
GLOBAL int DRVERR_WriteHeader (void);
GLOBAL int DRVERR_GetErrMsg (DRV_ERROR *error);
GLOBAL int DRVERR_GetItem (void);
GLOBAL int DRVERR_Show (IQT_HANDLE hnd, ELEMENT* el_ptr, BYTE line, BYTE from);
GLOBAL int DRVERR_PageScroll (int dir);
GLOBAL int DRVERR_SetParam (int type, int par_int, long par_long );

#endif  /* ifndef _drverror */
