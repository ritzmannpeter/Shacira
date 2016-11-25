/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     G_CONST.H
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
*     02.09.03 -HA-     PAGE_UD_MOVEMENT eingefuegt.
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

#ifndef _g_const
#define _g_const

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/


#define BLANKS  "                                                                                 "

/* Kennung der Ausgabeseite */
#define SCREEN_NORMAL          0
#define SCREEN_PRINT           1
#define SCREEN_WINDOW          2
#define SCREEN_PRINT_WINDOW    3
#define SCREEN_HOST            4
#define SCREEN_OPEN_HOST      10
#define SCREEN_CLOSE_HOST     11

/* Kennung des Update */
#define FAST                   1
#define INJ                    2
#define SLOW                   3
#define EVENT                  4

#define  UP                   1
#define  DOWN                 2
#define  LEFT                 3
#define  RIGHT                4

#define VERS_IQTKERN "01.X4.X1.010"
#define SPEC_IQTKERN "QNX"

#define ON                    1
#define OFF                   0

#define  PRINT_SCREEN         1     /* fuer Task "PrintPage" */
#define  PRINT_CYCLE          2

#define  SCREEN_X_MAX        53     /* Bildschirmaufbau */
#define  SCREEN_Y_MAX        25

/* Um die Indizes fuer die Einspritztabellen bequem eingeben zu koennen, */
/* gibt es die folgenden beiden Makros. */
/* Die Makros werden als Index fuer die Tabellen benutzt. */
#define TAB_SU(S,U)    ( ((U) == 0 ? 0 : ((U)-1)) * MaxStat + (S) )
#define TAB_CUS(C,U,S) ( ((S) == 0 ? 0 : ((S)-1)) * MaxInjUnits * MaxInjCyc + \
                         ((U) == 0 ? 0 : ((U)-1)) * MaxInjCyc               + \
                         ((C) == 0 ? 0 : ((C)-1)) )




#define MAX_FREEOBJTAB 23

#ifndef FNULL
typedef UWORD  (* PFuncPtr) (UWORD);
typedef long  (* PConvPtr) (long, UWORD);
typedef char  (* FuncPtr) ();
#define FNULL ((FuncPtr) 0)
#endif

typedef ULONG TICKER;
#define TICKRATE 250       /* Fastreg-Zykluszeit in ms                  */


/* Folgende Konstante kann in der Datenstruktur als Null-Funktion verwendet  */
/* werden.                                                                   */
#define NOFUNC {0,0}

/* Funktionswerte der Dunkeltastungsfunktionen */
#define FREE_ELEMENT          0
#define RESTRICTED_ELEMENT    1
#define DARK_ELEMENT          2

/* Konstanten, die in Dunkeltastungsfunktionen benutzt werden */
#define NO_CHANGE          0
#define CHANGE_COLOR       1
#define CHANGE_POSITION    2
#define CHANGE_BOTH        3
#define CURSOR_MOVEMENT    4
#define SOLLINPUT          8
#define PAGE_UD_MOVEMENT  16

/* Funktionswerte der Userfunktion-1 */
#define OKAY                  0
#define NOT_OKAY              1


/* Funktionswerte der Userroutine 2:
   1. Wert zeigt an, ob das Register gesetzt werden soll.
   2. Wert zeigt an, ob eine andere Seite/Variablen-Nr. angezeigt werden soll.
   3. Wert zeigt an, ob ein Update aktiviert werden soll. */
#define  UEBERTRAGEN          0        /* 1. Wert */
#define  NICHT_UEBERTRAGEN    1
#define  ABBRECHEN            2
#define  WORK_DONE            3        /* Register schon in User2 gesetzt */
#define  U2_NO_GOTO           0        /* 2. Wert (Default = U2_NO_GOTO) */
#define  U2_GOTO_PAGE         1
#define  U2_GOTO_VAR          2
#define  U2_NO_UPDATE         0        /* 3. Wert (Default = U2_NO_UPDATE) */
#define  U2_FAST           FAST
#define  U2_INJ             INJ
#define  U2_SLOW           SLOW
#define  U2_EVENT         EVENT

/* Macro's zum Setzen der Funktionswerte der Userroutine-2, falls der zweite
   oder der dritte Wert nicht gleich dem Default-Wert ist. */
#define  SET_U2_RET(A,B,C)  (((A)|((B)<<4)|((C)<<8))&0x0fff)
#define  GET_U2_RET1(A)     ( (A)&0x000f )
#define  GET_U2_RET2(B)     ( ((B)&0x00f0)>>4 )
#define  GET_U2_RET3(C)     ( ((C)&0x0f00)>>8 )

/* Funktionswerte der Softkeyfunktionen und der Sollwerteingabe */
#define  ACT_KEY_CHANGED             0  /* nur fuer Sollwerteingabe */
#define  CHAR_NOT_FOR_SOLLINPUT      1  /* nur fuer Sollwerteingabe */
#define  CORRECT_INPUT               2  /* nur fuer Sollwerteingabe */
#define  INCORRECT_INPUT             3  /* nur fuer Sollwerteingabe */
#define  GOTO_PAGE                   4
#define  GOTO_VAR                    5
#define  END_INPUT                   6
#define  GOTO_WINDOW                 7
#define  WINDOW_UP                   8
#define  WINDOW_DOWN                 9
#define  SOFT_EVENT                 10
#define  SOFT_ACTIVATE_BUILDSCREEN  11
#define  GOTO_VAR_OR_PAGE           12
#define  DO_KLICK_MODE              13


#endif         /* ifndef _g_const */












