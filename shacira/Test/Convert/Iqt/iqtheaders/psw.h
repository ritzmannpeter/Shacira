/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     PSW.H
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
*     13.07.92 -SF-    Portierung des IQT-350 auf IQT-450
*     29.03.01 -TSchw- Konstanten xxx_GEN_FREEPAGE eingefuegt, siehe MCARD_FOT.
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

#ifndef _psw
#define _psw

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Id's fuer PSW_SetParam()
****************************************************************************/
#define PSW_SET_TIME       0           /* Zeitdauer setzen */
#define PSW_INC_TIME       1           /* Zeitdauer erhoehen */
#define PSW_SET_GEN_FREEPAGE        2  /* MCARD_FOT: Seite generell freigeben */
#define PSW_RESET_GEN_FREEPAGE      3  /* MCARD_FOT: Seite nicht mehr freigeben */
#define PSW_RESETALL_GEN_FREEPAGE   4  /* MCARD_FOT: Alle Seiten nicht mehr freigeben */

/****************************************************************************
X  Funktionen
****************************************************************************/
GLOBAL int PSW_Init( BOOL init_bbram );
GLOBAL int PSW_Set( UWORD txt_ind, UWORD txt_line, BYTE inp_len,
                    BYTE ss_set_val, BYTE ss_inp_val, UWORD page_nr,
                    UWORD time );
GLOBAL int PSW_Read( UWORD txt_ind, UWORD txt_line, BYTE inp_len );
GLOBAL int PSW_Check( UWORD page_nr );
GLOBAL int PSW_SetParam( UWORD ctrl, UWORD param );

#endif /* ifndef _psw */








