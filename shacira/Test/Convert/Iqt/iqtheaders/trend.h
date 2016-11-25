/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     TREND.H
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
*     05.06.92 -SF-    Modul als DLL angelegt
*     28.09.98 -TSchw- TREND_NO von 10 auf 20 erhoeht und OLD_TREND_NO
*                      erstellt mit dem alten Wert 10, damit man auch
*                      alte Datenstrukturen mit dem neuen Kernprogramm
*                      bearbeiten kann. Makro ACT_TREND_NO erstellt,
*                      um herauszufinden, welche Version die Datenstruktur
*                      unterstuetzt.
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

#ifndef _trend
#define _trend

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
#include <register.h>
#include <iqtreg.h>
/*.EI.***********************************************************************/

typedef AXIS TREND;

/****************************************************************************
X  Allgemeine Konstanten
****************************************************************************/
#define TREND_TEST_SIZE  82       /* Anzahl Balken pro Diagramm */
#define TREND_NO         20
#define OLD_TREND_NO     10       /* zwecks Kompatibilitaet */

/* Das Makro ACT_TREND_NO ueberprueft, ob die Datenstruktur mit einer      */
/* Trendgraphikgroesse von 10 oder 20 arbeitet, indem das Register         */
/* AxisVarTab auf den passenden Typ ueberprueft wird.                      */
/* Man macht sich hier die Tatsache zu Nutze, das die Trendgraphikregister */
/* bisher mit REG_LONG10 definiert waren und bei Unterstuetzung der        */
/* erweiterten Groesse als REG_LONG20 definiert werden muessen.            */
#define ACT_TREND_NO                                                       \
   (((GET_REGTYPE(RegType(REGIND_UUU, AxisVarTab))) == REG_LONG20) ?       \
    TREND_NO : OLD_TREND_NO)

/****************************************************************************
X  Id's fuer Trend_SetParam()
****************************************************************************/
#define TREND_ID_CLEAR            0
#define TREND_ID_SET_ALL_REFVAL   1
#define TREND_ID_SET_REFVAL       2

 GLOBAL int Trend_Init(BOOL init_bbram);
 GLOBAL int Trend_GetItem(void);
 GLOBAL int Trend_NewTestVar(long var_nr, UWORD index,
                              UWORD ind1, UWORD ind2, UWORD ind3);
 GLOBAL int Trend_FltVar(UWORD ctrl, long var_nr, UWORD index, REGIST *ri_ptr);
 GLOBAL int Trend_SetParam(int type, int param);
 GLOBAL IQT_HANDLE Trend_Draw(ELEMENT* el_ptr, BYTE line, BYTE from, BYTE screen);

#endif /* ifndef _trend */







