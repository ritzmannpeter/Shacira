/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     xxxxxxxxx
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
*     04.03.97 -TSchw- RTC_GET_YEAR gibt ein volles Wort zurueck nicht nur
*                      ein Byte, damit in Zukunft eine volle Jahreszahl
*                      uebergeben werden kann.
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

/*********************************************************************
*
*      DDD     EEEEE   V   V   RRRR    TTTTT    CCCC    H   H
*      D  D    E       V   V   R   R     T     C        H   H
*      D   D   EEEE    V   V   RRRR      T     C        HHHHH
*      D  D    E        V V    R  R      T     C        H   H
*      DDD     EEEEE     V     R   R     T      CCCC ## H   H
*
**********************************************************************
*
*  *** HISTORY ***
*  13.06.89   -MW-   Aufspaltung von IQTDEV.H in mehrere Dateien
*  21.03.90   -TE-   Einfuehrung des Parameters RTC_ID_WEEKDAY
*
*********************************************************************/

/*********************************************************************
*  IN IQTDEV.H NACHZUTRAGENDE SPEZIALITAETEN (VORLAEUFIG)
*********************************************************************/

/*********************************************************************
*  RTC-Treiber: KONSTANTEN UND ALLGEMEINE MAKROS
*********************************************************************/

#define SUNDAY      0
#define MONDAY      1
#define TUESDAY     2
#define WEDNESDAY   3
#define THURSDAY    4
#define FRIDAY      5
#define SATURDAY    6

/*********************************************************************
*  RTC-Treiber: ZUGRIFFSMACROS
*********************************************************************/

#define RTC_GET_HOUR( t )        ( (int)((t)>>16) & 0x00ff )
#define RTC_GET_MIN( t )         ( (int)(t)>>8 & 0x00ff )
#define RTC_GET_SEC( t )         ( (int)(t) & 0x00ff )
#define RTC_MAKE_TIME( h,m,s )   ( ((ULONG)h)<<16 | ((ULONG)m)<<8 | (ULONG)s )

#define RTC_GET_YEAR(d)          ( (int)((d)>>16) & 0xffff )
#define RTC_GET_MONTH(d)         ( (int)(d)>>8 & 0x00ff )
#define RTC_GET_DAY(d)           ( (int)d & 0x00ff )
#define RTC_MAKE_DATE( d,m,y )   ( ((ULONG)y)<<16 | ((ULONG)m)<<8 | (ULONG)d )

/*********************************************************************
*  RTC-Treiber: DATENTYPEN
*********************************************************************/

/*********************************************************************
*  RTC-Treiber: SCHNITTSTELLENPARAMETER
*********************************************************************/

#define RTC_ID_TIME    0
#define RTC_ID_DATE    1
#define RTC_ID_WEEKDAY 2

/*********************************************************************
*  RTC-Treiber: FEHLERCODES
*********************************************************************/

