/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IQKBDKEY.H
*
*  BESCHREIBUNG:
*     Enthaelt die Defintion der IQT Tastaturcodes
*
*  UMGEBUNG:
*
*  HISTORY:
*     17.11.98 -TSchw-  Implementierung, Definition aus devkbd.h entnommen.
*     09.02.00 -TSchw-  KFC_SOFT6 und KFC_SOFT7 neu definiert, daher
*                       verschiebt sich der Wert von KFC_ALARM.
*     06.08.01 -TSchw-  KFC_LANGUAGE eingefügt für interne Zwecke (Sprach-
*                       umschaltung über Alt-L).
*
*  BEMERKUNGEN:
*
*.EH.***********************************************************************/

#ifndef _iqkbdkey
#define _iqkbdkey


#define KFC_PGUP     1     /* Naechste bzw. vorige Seite anzeigen        */
#define KFC_PGDWN    2

#define KFC_CRLFT    8     /* Cursor innerhalb einer Seite von Sollwert */
#define KFC_CRDWN    10    /* zu Sollwert bewegen                       */
#define KFC_CRUP     11
#define KFC_CRRGT    12

#define KFC_LINE     3     /* Direkte Seiten- bzw. Zeileneingabe        */
#define KFC_PAGE     4

#define KFC_ENTER    13    /* Bestaetigung von Eingaben                  */

#define KFC_CLEAR    5     /* Loeschen von Sollwerteingaben bzw. Fehler- */
#define KFC_ERASE    6     /* meldungen                                 */

#define KFC_BKGND    7     /* Umschalten auf Hintergrunddatensatz       */

#define KFC_HELP     9     /* Hilfetaste                                */

#define KFC_WINDOW   14    /* Anzeigen der verkleinerten Seite          */

#define KFC_ZOOM     15    /* Vergroessern/verkleinern der Window-Seite   */

#define KFC_PRMODE   16    /* Umschalten zwischen Druckoptionen         */

#define KFC_OBJECT   17    /* Objektauswahl fuer frei konfig. Seite      */

#define KFC_PRINT    18    /* Ausdrucken von Bildschirmseiten           */

#define KFC_AGGR     19    /* Aggregate und Stationen anwaehlen          */
#define KFC_STATION  20

#ifdef AMI_TASTARUR
#define KFC_CAE      91    /* Umlaute und 'ss'                           */
#define KFC_COE      92
#define KFC_CUE      93
#define KFC_AE       123
#define KFC_OE       124
#define KFC_UE       125
#define KFC_SS       126
#else
#define KFC_CAE      0x8e  /* Umlaute und 'ss'                           */
#define KFC_COE      0x99
#define KFC_CUE      0x9a
#define KFC_AE       0x84
#define KFC_OE       0x94
#define KFC_UE       0x81
#define KFC_SS       0xe1
#endif

#define KFC_QUICK1   128   /* 10 Schnellwahltasten                       */
#define KFC_QUICK2   129
#define KFC_QUICK3   130
#define KFC_QUICK4   131
#define KFC_QUICK5   132
#define KFC_QUICK6   133
#define KFC_QUICK7   134
#define KFC_QUICK8   135
#define KFC_QUICK9   136
#define KFC_QUICK10  137

#define KFC_PROG1    138   /* 8 frei programmierbare Tasten             */
#define KFC_PROG2    139
#define KFC_PROG3    140
#define KFC_PROG4    141
#define KFC_PROG5    142
#define KFC_PROG6    143
#define KFC_PROG7    144
#define KFC_PROG8    145

#define KFC_SOFT1    146   /* 5 Softkeytasten                           */
#define KFC_SOFT2    147
#define KFC_SOFT3    148
#define KFC_SOFT4    149
#define KFC_SOFT5    150
#define KFC_SOFT6    151
#define KFC_SOFT7    152

#define KFC_ALARM    153
#define KFC_HARDCOPY 175
#define KFC_LANGUAGE 176

#define KFC_KEY0    	180
#define KFC_KEY1    	181
#define KFC_KEY2    	182
#define KFC_KEY3    	183
#define KFC_KEY4    	184
#define KFC_KEY5    	185
#define KFC_KEY6    	186
#define KFC_KEY7    	187
#define KFC_KEY8    	188
#define KFC_KEY9    	189

#endif

