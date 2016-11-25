/*.SS.***********************************************************************
*
*  BESCHREIBUNG:
*
*  HISTORY:
*
*  VERSION:
*     VERSION:  1.3              AUTOR:
*     DATUM:    14.12.95         TELEFON:
*
*  BEMERKUNGEN:
* 
**.ES.**********************************************************************/

/*.SM.***********************************************************************
*
*  MODUL-NAME: 
*     IQTREG.C
*
*  BESCHREIBUNG:
*     Definition der Tabelle IqtRegTab, die alle IQT-Register
*     beschreibt, und Belegen der Tabelle mit Werten.
*     Die Endekennung {0xffff} muss immer da sein.
*
*  HISTORY:
*     02.04.93  -JG-    Register fuer Zeitanalyse eingefuegt
*     10.05.93  -TSchw- Neu von Common uebernommen fuer B&R
*     07.02.94  -TSchw- Vom IQT 450 wieder uebernommen fuer das IQT
*                       353, saemtliche BDE-, SPC- und Prozess-
*                       graphikregister entfernt (siehe #define
*                       NOT_USED_IN_IQT_353), PFlt_WClock umbenannt
*                       in Flt_WClock, PFlt_PRINT umbenannt in
*                       Flt_PRINT
*     08.02.94  -TSchw- XPOJSS, XPOJES eingefuegt fuer Leitrechner,
*                       ebenso HOST_START_ORDER, HOST_STOP_ORDER,
*                       HOST_CANCEL_ORDER, HOST_REJECTS,
*                       HOST_GOOD_PARTS eingeuegt mit Filterfkt.
*                       FILL_TIME1/2 angelegt. In diese Register
*                       wird die Fuellzeit (Einspritzzeit ohne
*                       Nachdruck) des 6-Stufen-Mode geschrieben.
*                       Sie wird berechnet aus den Einspritzzeiten
*                       aller aktiven Spritzphasen. Diese Register
*                       werden speziell fuer den Leitrechner ange-
*                       legt. Wunsch Kury.
*     16.02.94 -TSchw-  XNUL-Register eingefuegt als Muelleimer
*     25.02.94  -PR-    Register SCHICHTx_BEGIN, SCHICHTx_END,
*                       WKZ_CODE, XSNSUS, BDEProcDataSwitch,
*                       BDENrDocCycles, BDENrNotDocCycles,
*                       BDEStartIntx, BDEStopIntx, BDEContSwitch,
*                       TOL_SELECT und TOL_SELECT_2 sind ab jetzt
*                       auch im Hintergrund definiert.
*                       Register HOST_PAUSE_CYCLES eingefuehrt.
*     01.03.94 -MBa-    Schichtzaehler u. Wkz.Code auch im
*                       Hintergrund definiert
*     11-01-96 -WS-     FltFunkt. fuer PG21.1-Werte eingefuehrt
*     28.06.96 -HAns-   Folgende Register neu eingefuegt zur Ab-
*                       speicherung der Referenzistwerte auf dem
*                       Datentraeger; Forderung Rietsche, Gehring:
*                       XXTDOS1_REF, XXTDOS2_REF, XXPFINM_REF und
*                       XXPFI2M_REF sowie XXTZYKL_REF
*                       Bei XREG618, U2SNSUS, U2SNKAV wurde schon
*                       seit laengerem die Filterfunktion
*                       Flt_Production eingefuegt. (im ISCOS-
*                       Directory seit 17.05.93)
*                       Filterfunktionen der Register XSNLUF1 bis
*                       XSNLUF4 herausgenommen.
*     30.07.96 -HAns-   ISRSSVOR eingefuegt.
*     22.08.96 -HAns-   IFK_DEVICE, IFK_DATA_BITS, IFK_STOP_BITS, IFK_PARITY
*                       und IFK_BAUDRATE von INT20 nach TP_LNG20 geaendert.
*     13-09-96 -PR- 		IQT-Registerbeschreibung fuer frei progr. Kernzuege 
*							   eingefuehrt (ICO...).
*     26.09.96 -HAns-   ISVPH11 - ISVPH15 eingefuegt.
*     27.09.96 -HAns-   ICHGWAY_VOL eingefuegt.
*     30.09.96 -HAns-   ISVPH21 bis ISRSVOLNACH_2 eingefuegt.
*		04.11.96 -TSchw-  Weg-/Volumenregister eingefuehrt zum indizierten
*							   Zugriff auf Weg und Volumen (siehe WV_)
*		15.11.96 -HAns-   XTSPH11 - XTSPH15 und XTSPOL1 herausgenommen, da diese
*                       nicht mehr benutzt werden.
*                       ITVPH10 und ITVPH20 eingefuegt.
*                       SWITCH_VOL_TOL11-16 und SWITCH_VOL_TOL21-26
*                       eingefuegt.
*		19.11.96 -HAns-   IXVPH11 - IXVPOL2 eingefuegt.
*                       AWV_PLASTWEG, AWV_PLASTWEG_TOL,AWV_SWITCH_POINT_IST und
*								AWV_SWITCH_POINT_TOL eingefuegt.
*                       IXVPH10 - IXVPH20 eingefuegt.
*     02.12.96 -PR-     Darstellungsunabhaengige Prozessgrafikregister
*                       (NRM_...) eingetragen.
*		04.12.96 -HAns-   AWV_PLASTWEG, AWV_PLASTWEG_TOL,AWV_SWITCH_POINT_IST und
*								AWV_SWITCH_POINT_TOL eingefuegt.
*								Flt_NRM_WV_HS an AWV_ und AHS_-Register angefuegt.
*		05.12.96 -HAns-   ISPEC_-Register eingefuegt.
*		10.12.96 -HAns-   Flt_SWITCH_PRES_SOLL an SWITCH_PRES_TOLxx durch
*                       Flt_HydrToSpecSoll ersetzt.
*     23.01.97 -HAns-   Fuer Leitrechner: HOST_AGGREGAT und    
*                       HOST_ACT_REGLER_NR eingefuegt fuer alle
*                       Maschinentypen                         
*     24.01.97 -HAns-   AWV_DREHZAHL und AWV_DREHZAHL_2 eingefuegt.
*                       SWPL11_VOL - SWPL41_VOL und SWPL12_VOL - SWPL42_VOL
*                       eingefuegt.
*     27.01.97 -HAns-   AWV_SRV_VORPL, AWV_SRV_NACHPL und AWV_INJ_SPEED_SOLL
*                       eingefuegt.
*                       SRSVVOR_1_VOL bis SRSVVOR_4_VOL, SRSVNACH_1_VOL bis
*                       SRSNACH_4_VOL und SVPH11_VOL bis SVPH46_VOL eingefuegt.
*     04.02.97 -HAns-   Namensgebung fuer Volumenregister neu festgelegt.
*     07.02.97 -HAns-   AHS_SWITCH_PRES_REF, AWV_SWITCH_POINT_REF und AWV_PLASTWEG_REF
*                       eingefuegt.
*     12.02.97 -HAns-   SWITCH_PRES_REF11_SPEC bis SWITCH_PRES_REF46_SPEC,
*                       SWITCH_POINT_REF11_VOL bis SWITCH_POINT_REF11_VOL und
*                       XTSPH10_REF_VOL bis XTSPH40_REF_VOL eingefuegt.
*     17.02.97 -HAns-   PG_YSCAL_VOLSPEC bis PG_YSCAL_VOLSPEC39 und NRM_PG_YSCAL eingefuegt.
*                       AWV_ -Register und NRM_-Register verlegt.
*                       Flt_WayToVolSoll in Flt_WHToVS_Soll und
*                       Flt_VolToWaySoll in Flt_VSToWH_Soll umbenannt, sowie
*                       Flt_HydrToSpecSoll und Flt_SpecToHydrSoll herausgenommen.
*     11.03.97 -HAns-   XZEITAN4_2,3,4 ,XZEITAN5_2,3,4 ,XZEITAN6_2,3,4*
*                       XZEITANAVER4_2,3,4 , XZEITANAVER5_2,3,4 und  *
*                       XZEITANAVER6_2,3,4 eingefuegt.               *
*     13.03.97 -PR-     Register ICO_MaxToolStroke eingefuehrt
*     11.06.97 -HAns-   Flt_Production an XSNSUS angefuegt.
*     24.11.97 -HAns-   ACT_DIAGSYSTYP bis ACT_DIAGMODTYP, ACT_DIAGMODULTYP
*                       fuer freiauswaehlbare Diagnoseseite eingefuegt.
*     01.04.98 -TSchw-  REG_SPECTAB eingefuegt bei allen Registern mit
*                       Filterfunktion Tabs oder Flt_NRM_WV_HS
*                       Mehrfarbmaschinenregister eingetragen.
*     05.08.99 -TSchw-  ACT_PALETTE eingetragen.
*	  07.04.99 -TSchw-  Register PG_NR_ACT_CURVES eingefuegt.
*	  09.04.99 -TSchw-  Bei PG_NR_ACT_CURVES die Filterfunktion PPGActCurves
*						eingefuegt.
*	  16.04.99 -TSchw-  PG_OPMODE_SOLL mit TP_PGDSK_BG markiert,
*                       XPG_SOLLIST1 und 2 mit TP_INT10_PGDSK markiert,
*						damit diese Prozessgraphikregister in eine eigene
*						Teildatei auf dem Datentraeger geschrieben werden.
*	  23.04.99 -TSchw-  Die ICOPROGLINExx-Register mit REG_DISK_CORE
*						markiert, damit die Kernzugsregister in eine
*						eigene Teildatei gespeichert werden koennen.
*     06.03.00 -TSchw-  ACT_SYSPRINTER eingefuegt fuer SYSPRN
*     13.11.00 -TSchw-  ACCCARD_NEW_KEYCODE eingefuegt (siehe MEMCARD)
*     09.04.01 -HAns-   IqtRegTab mit ifdef MODE_10 versehen.
*     03.07.01 -HA-     RegType von ICHGWAY_VOL (Weg/Volumen-Umschaltung)
*                       von TP_BG nach TP_STD geaendert.
*     04.07.02 -HAns-   BTCOUNTER_IST_HH und BTCOUNTER_IST_MM eingefuegt.
*                       Register fuer 9 Einspritzstufen 
*                       (SPPH17_SPEC bis SWITCH_POINT_REF19_VOL) eingefuegt.
*                       MAX_INJCYC aufgenommen
*                       AWV_SWITCH_POINT2_SOLL, AWV_INJ_SPEED2_SOLL fuer
*                       Produktionsstart Weg-/Volumenumschaltung S 40.2
*                       MLD_MP01 bis MLD_MP10, INJ_MP01 bis INJ_MP10 und SCR_MP01 bis SCR_MP10
*                       sowie INJ_MP01_2 bis INJ_MP10_5 und SCR_MP01_2 bis SCR_MP10_5 eingefuegt.
*                       IVENTIL_IND bis IMAS_VERS2 aufgenommen.
*                       AWV_WEGPUNKT_2, AWV_WEGPUNKT_3, AHS_STAUDRUCK_3, AHS_STAUDRUCK_4, AWV_DREHZAHL_3
*                       und AWV_DREHZAHL_4 eingefuegt.
*                       SSUM12_VOL bis SPST44_SPEC eingefuegt.
*                       IPLASTSTUFE eingefuegt.
*                       Register fuer 10-12 Einspritzstufen 
*                       (SPPH1A_SPEC bis SWITCH_POINT_REF1C_VOL) eingefuegt.
*                       IVENTIL_NR bis IVENTIL_VERS2 und IMAX_VENTIL eingefuegt.
*                       IZEITAND und IZEITANAVERD eingefuegt.
*     08.07.02 -HA-     PSHOT_COUNTER eingefuegt.
*     11.07.02 -HA-     XMP16_2 bis 4 aufgenommen.
*                       MAX_SE1_WEG bis MAX_SE2_WEG aufgenommen.
*     15.07.02 -HA-     APST_TOL1 bis APST_TOL4, APIT_REF1 bis APIT_REF4 eingefuegt.
*                       DUES_WAHL_SPEC eingefuegt fuer S. 48
*     22.08.02 -HA-     IVENTIL_IND bis IMAS_VERS2 aufgenommen.
*     26.02.03 -HA-     AWV_ANZ_PLAST_STUF  eingefuegt fuer verbesserte Weg/Volumen-Darstellung
*     06.03.03 -HA-     Filterfunktion der AHS_-Register von Flt_NRM_WV_HS in Flt_NRM_HS geaendert.
*     10.03.03 -HA-     Soll Einspritzgeschwindigkeit fuer Anfahrzyklen,
*                       Soll Umschaltpunkt und Soll Einspritzdruck fuer Anfahrzyklen eingefuegt.
*                       AWV_PLASTWEG_ANFAHR und SSDSOS1A_VOL eingefuegt.
*                       AHS_INJ_PRES2_SOLL eingefuegt
*     04.04.03 -HA-     AxisVarTab, AxisRegInd1,2,3 und AxisAggregat von INT10 bzw. LNG10 in
*                       INT20 bzw. LNG20 geaendert.
*     08.05.03 -HA-     Flt_NRM_HS_WkzInnen an AHS_SWITCH_PRES_SOLL, AHS_PRES_IST, 
*                       AHS_SWITCH_PRES_TOL und AHS_SWITCH_PRES_REF angefuegt.
*
*  VERSION:
*     VERSION:  1.3              AUTOR:    H.Anselm
*     DATUM:    14.12.95         TELEFON:  338
*
*  UMGEBUNG:
*     ZIELRECHNER:          Industrie-PC
*     PROGRAMMIERSPRACHE:   C
*
*  BEMERKUNGEN:
*
*****************************************************************************
*
*  FUNKTIONEN:
*
**.EM.**********************************************************************/

/*.SI.**********************************************************************/

#include <syntax.h>

#define USE_ALL_IQTREG
#define IMPORT_NOT_GLOBAL
#define IMPORT_FLTFUNC

#include <iqtdstr.h>

/*.EI.**********************************************************************/


/* Abkuerzungen fuer Konstanten (TP = Type) */
#define TP_STD             REG_INT
#define TP_BG              REG_INT|REG_BG
#define TP_DSK             REG_INT|REG_DISK_TOOL
#define TP_DSK_BG          REG_INT|REG_DISK_TOOL|REG_BG
#define TP_SETUP_BG        REG_INT|REG_DISK_SETUP|REG_BG
#define TP_ROB_BG          REG_INT|REG_DISK_ROB|REG_BG
#define TP_PGDSK_BG        REG_INT|REG_DISK_PG|REG_BG

#define TP_INT10           REG_INT10
#define TP_INT10_BG        REG_INT10|REG_BG
#define TP_INT10_DSK       REG_INT10|REG_DISK_TOOL
#define TP_INT10_DSK_BG    REG_INT10|REG_DISK_TOOL|REG_BG
#define TP_INT10_ROB_BG    REG_INT10|REG_DISK_ROB|REG_BG
#define TP_INT10_PGDSK     REG_INT10|REG_DISK_PG

#define TP_INT20           REG_INT20
#define TP_INT20_DSK_BG    REG_INT20|REG_DISK_TOOL|REG_BG

#define TP_LNG             REG_LONG
#define TP_LNG_BG          REG_LONG|REG_BG
#define TP_LNG_DSK_BG      REG_LONG|REG_DISK_TOOL|REG_BG

#define TP_LNG10           REG_LONG10
#define TP_LNG10_DSK_BG    REG_LONG10|REG_DISK_TOOL|REG_BG
#define TP_LNG10_ROB_BG    REG_LONG10|REG_DISK_ROB|REG_BG

#define TP_LNG20           REG_LONG20
#define TP_LNG20_DSK_BG    REG_LONG20|REG_DISK_TOOL|REG_BG
#define TP_LNG20_FOT_BG    REG_LONG20|REG_DISK_FOT|REG_BG
#define TP_LNG20_ROB_BG    REG_LONG20|REG_DISK_ROB|REG_BG


/*
ACHTUNG:
Die Tabelle IqtRegTab mua nach Registernummern aufsteigend geordnet sein.
Dies ist zwingend vorgeschrieben. Ist dies nicht der Fall, so fhrt dies zu
Fehlern beim Zugriff auf die Register.
*/

const IQTREG_TYPE IqtRegTab [] = {
/*RegNr        RegType        FltFunc */
{XCUSWTL,      TP_STD,        0},                
{XCUSWTM,      TP_STD,        0},
{XBODUMMY,     TP_STD,        0},
{IDHOEHE,      TP_STD,        0},
{XNUL,         TP_STD,        0},
                              
{XMAXFAUF,     TP_BG,         0},
{XIQWEG2,      TP_BG,         0},
{XFORMZU,      TP_BG,         0},
{XITKUHL,      TP_DSK_BG,     0},
{XSNWKZS,      TP_DSK_BG,     PFlt_XSNWKZS},

{XMP02,        TP_BG,         0},
{XMP03,        TP_BG,         0},
{XMP04,        TP_BG,         0},
{XMP05,        TP_BG,         0},
{XMP06,        TP_BG,         0},
{XMP07,        TP_BG,         0},
{XMP08,        TP_BG,         0},
{XMP09,        TP_BG,         0},
{XMP10,        TP_BG,         0},
{XMP11,        TP_BG,         0},
{XMP12,        TP_BG,         0},
{XMP13,        TP_BG,         0},
{XMP14,        TP_BG,         0},
{XMP15,        TP_BG,         0},
{XMP16,        TP_BG,         0},
{XMP17,        TP_BG,         0},
{XMP18,        TP_BG,         0},
{XMP19,        TP_BG,         0},
{XMP20,        TP_BG,         0},
{XMP21,        TP_BG,         0},
{XMP22,        TP_BG,         0},
{XMP23,        TP_BG,         0},
{XMP24,        TP_BG,         0},
{XMP25,        TP_BG,         0},
{XMP26,        TP_BG,         0},
{XMP27,        TP_BG,         0},
{XMP28,        TP_BG,         0},
{XMP29,        TP_BG,         0},
{XMP30,        TP_BG,         0},
{XMP31,        TP_BG,         0},
{XMP32,        TP_BG,         0},
{XTABWKZ,      TP_DSK_BG,     0},
{AGGPOS,       TP_BG,         0}, /* Spritzzylinder auf Position */
{XMP19_KP,     TP_STD,        0},          /* Speicher fuer KP19          */
{XMP20_22,     TP_BG,         0}, /* akt. Wert von MP20 - MP22   */
{XMP25_1,      TP_STD,        0},          /* MP25 aus Schneckentabelle 1 */
{XMP25_2,      TP_STD,        0},          /* MP25 aus Schneckentabelle 2 */
{XMP25_3,      TP_STD,        0},          /* MP25 aus Schneckentabelle 3 */

/* Register fuer erweiterte Werkzeug, Aggregat und Schneckentabelle */
{MLD_MP01,     TP_BG,         0},
{MLD_MP02,     TP_BG,         0},
{MLD_MP03,     TP_BG,         0},
{MLD_MP04,     TP_BG,         0},
{MLD_MP05,     TP_BG,         0},
{MLD_MP06,     TP_BG,         0},
{MLD_MP07,     TP_BG,         0},
{MLD_MP08,     TP_BG,         0},
{MLD_MP09,     TP_BG,         0},
{MLD_MP10,     TP_BG,         0},
{INJ_MP01,     TP_BG,         0},
{INJ_MP02,     TP_BG,         0},
{INJ_MP03,     TP_BG,         0},
{INJ_MP04,     TP_BG,         0},
{INJ_MP05,     TP_BG,         0},
{INJ_MP06,     TP_BG,         0},
{INJ_MP07,     TP_BG,         0},
{INJ_MP08,     TP_BG,         0},
{INJ_MP09,     TP_BG,         0},
{INJ_MP10,     TP_BG,         0},
{SCR_MP01,     TP_BG,         0},
{SCR_MP02,     TP_BG,         0},
{SCR_MP03,     TP_BG,         0},
{SCR_MP04,     TP_BG,         0},
{SCR_MP05,     TP_BG,         0},
{SCR_MP06,     TP_BG,         0},
{SCR_MP07,     TP_BG,         0},
{SCR_MP08,     TP_BG,         0},
{SCR_MP09,     TP_BG,         0},
{SCR_MP10,     TP_BG,         0},

{XREG608,      TP_DSK_BG,     0},
{XREG609,      TP_DSK_BG,     0},
{XREG610,      TP_DSK_BG,     0},
{XREG611,      TP_DSK_BG,     0},
{XREG613,      TP_LNG,        0},
{XREG614,      TP_LNG,        0},
{XREG615,      TP_LNG,        0},
{XREG616,      TP_LNG,        0},
{XREG617,      TP_DSK_BG,     0},
{XREG618,      TP_DSK_BG,     PFlt_Production},
{XREG633,      TP_LNG_DSK_BG, 0},
{PSHOT_COUNTER,TP_LNG,        0},
{XREG637,      TP_STD,        0},
{XREG638,      TP_LNG,        0},
{XREG640,      TP_SETUP_BG,   0},
{XREG641,      TP_SETUP_BG,   0},
{XREG642,      TP_SETUP_BG,   0},
{XREG643,      TP_SETUP_BG,   0},
{XREG644,      TP_SETUP_BG,   0},
{XREG645,      TP_SETUP_BG,   0},
{XREG646,      TP_SETUP_BG,   0},
{XREG647,      TP_SETUP_BG,   0},
{XREG648,      TP_SETUP_BG,   0},
{XREG649,      TP_SETUP_BG,   0},
{XREG650,      TP_SETUP_BG,   0},
{XREG651,      TP_SETUP_BG,   0},
{XREG652,      TP_SETUP_BG,   0},
{XREG653,      TP_SETUP_BG,   0},
{XREG654,      TP_SETUP_BG,   0},
{XREG655,      TP_SETUP_BG,   0},
{XREG656,      TP_SETUP_BG,   0},
{XREG657,      TP_SETUP_BG,   0},
{XREG658,      TP_SETUP_BG,   0},
{XREG659,      TP_SETUP_BG,   0},
{XREG660,      TP_SETUP_BG,   0},
{XREG661,      TP_SETUP_BG,   0},
{XREG662,      TP_SETUP_BG,   0},
{XREG663,      TP_SETUP_BG,   0},
{XREG664,      TP_SETUP_BG,   0},
{XREG665,      TP_SETUP_BG,   0},
{XREG666,      TP_SETUP_BG,   0},
{XREG667,      TP_SETUP_BG,   0},
{XREG668,      TP_SETUP_BG,   0},
{XREG669,      TP_SETUP_BG,   0},
{XREG670,      TP_SETUP_BG,   0},
{XREG671,      TP_SETUP_BG,   0},
{XREG672,      TP_SETUP_BG,   0},
{XREG673,      TP_SETUP_BG,   0},
{XREG674,      TP_SETUP_BG,   0},
{XREG675,      TP_SETUP_BG,   0},
{XREG676,      TP_SETUP_BG,   0},
{XREG677,      TP_SETUP_BG,   0},
{XREG678,      TP_SETUP_BG,   0},
{XREG679,      TP_SETUP_BG,   0},
{XREG680,      TP_SETUP_BG,   0},
{XREG681,      TP_SETUP_BG,   0},
{XREG682,      TP_SETUP_BG,   0},
{XREG683,      TP_SETUP_BG,   0},
{XREG684,      TP_SETUP_BG,   0},
{XREG685,      TP_SETUP_BG,   0},
{XREG686,      TP_SETUP_BG,   0},
{XREG687,      TP_SETUP_BG,   0},
{XREG688,      TP_SETUP_BG,   0},
{XREG689,      TP_SETUP_BG,   0},
{XREG690,      TP_SETUP_BG,   0},
{XREG691,      TP_SETUP_BG,   0},

{XREG775,      TP_DSK_BG,     PFlt_XREG775},
{XREG776,      TP_DSK_BG,     PFlt_XREG776},
{XREG777,      TP_DSK_BG,     PFlt_XREG776},
/* ---------------- Airpress ---------------------------------------------- */
{APST_TOL1,    TP_DSK_BG,     0},
{APST_TOL2,    TP_DSK_BG,     0},
{APST_TOL3,    TP_DSK_BG,     0},
{APST_TOL4,    TP_DSK_BG,     0},
{APIT_REF1,    TP_DSK_BG,     0},
{APIT_REF2,    TP_DSK_BG,     0},
{APIT_REF3,    TP_DSK_BG,     0},
{APIT_REF4,    TP_DSK_BG,     0},
/* ------------------------------------------------------------------------ */
{XREG841,      TP_STD,        0},
{XREG842,      TP_STD,        0},
{XREG843,      TP_STD,        0},
{XREG985,      TP_DSK_BG,     0},

{XREG989,      TP_DSK_BG,     0},
{XREG990,      TP_DSK_BG,     0},
{XREG991,      TP_DSK_BG,     0},
{XREG992,      TP_DSK_BG,     0},
{XREG993,      TP_DSK_BG,     0},
{XREG994,      TP_DSK_BG,     0},

{MAX_SE1_WEG,  TP_STD,        0},
{MAX_SE2_WEG,  TP_STD,        0},
{MAX_SE3_WEG,  TP_STD,        0},
{MAX_SE4_WEG,  TP_STD,        0},

{WOISAKTUEL_TOL, TP_DSK_BG,   0}, /* Tol Max. Werkzeugoeffnungsweg */
{WOISAKTUEL_REF, TP_DSK_BG,   0}, /* Ref Max. Werkzeugoeffnungsweg */ 
{AWISAKTUEL_TOL, TP_DSK_BG,   0}, /* Tol Max. Auswerferweg */
{AWISAKTUEL_REF, TP_DSK_BG,   0}, /* Ref Max. Auswerferweg */

{XRPFINM,      TP_DSK_BG,     0},
{XRPPH11,      TP_DSK_BG,     0},
{XRPPH12,      TP_DSK_BG,     0},
{XRPPH13,      TP_DSK_BG,     0},
{XRPPH14,      TP_DSK_BG,     0},
{XRPPH15,      TP_DSK_BG,     0},

{XSKANF1,      TP_DSK_BG,     0},
{XSKOEL,       TP_DSK_BG,     0},
{XSKTEMA,      TP_DSK_BG,     0},
{XSNARGR,      TP_DSK_BG,     0},
{XSNFEHL,      TP_DSK_BG,     0},
{XSNGRUM,      TP_DSK_BG,     0},
{XSNKAV,       TP_DSK_BG,     PFlt_Production},
{XSNLUF1,      TP_DSK_BG,     0},
{XSNLUF2,      TP_DSK_BG,     0},
{XSNLUF3,      TP_DSK_BG,     0},
{XSNLUF4,      TP_DSK_BG,     0},

{XSSBOLZ,      TP_BG,         0},
{XSTANF1,      TP_DSK_BG,     0},
{XSTOLWA,      TP_DSK_BG,     0},
{XSYBED1,      TP_DSK_BG,     0},

{XTPFINM,      TP_DSK_BG,    0},
{XTPPH11,      TP_DSK_BG,    0},
{XTPPH12,      TP_DSK_BG,    0},
{XTPPH13,      TP_DSK_BG,    0},
{XTPPH14,      TP_DSK_BG,    0},
{XTPPH15,      TP_DSK_BG,    0},
{XTSPH10,      TP_DSK_BG,    PFlt_WHToVS_Soll},
{XTTPH11,      TP_DSK_BG,    0},
{XTTPH12,      TP_DSK_BG,    0},
{XTTPH13,      TP_DSK_BG,    0},
{XTTPH14,      TP_DSK_BG,    0},
{XTTPH15,      TP_DSK_BG,    0},
{XTTPH16,      TP_DSK_BG,    0},

{XXNPM11,      TP_DSK_BG,    0},
{XXNPM12,      TP_DSK_BG,    0},
{XXNPM21,      TP_DSK_BG,    0},
{XXNPM22,      TP_LNG,       0},

/* ---------------- spez.-Register fuer hydr./spec. Umschaltung (9 Spritzstufen) */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
{SPPH17_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 7 */
{SPPH18_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 8 */
{SPPH19_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 9 */
/* ---------------- IST Einspritzdruck ------------------------------------ */
{XPPH17_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 7*/
{XPPH18_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 8*/
{XPPH19_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 9*/
/* ---------------- Soll Einspritzgeschwindigkeit ------------------------- */
{SVPH17_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Einspritzges. Agg1 Stufe7 */
{SVPH18_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Einspritzges. Agg1 Stufe8 */
{SVPH19_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Einspritzges. Agg1 Stufe9 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
{SPUM16_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 7*/
{SPUM17_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 8*/
{SPUM18_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 9*/
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
{SSPH16_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe6 */
{SSPH17_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe7 */
{SSPH18_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe8 */
{SSPH19_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe9 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
{XSPH16_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe6 */
{XSPH17_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe7 */
{XSPH18_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe8 */
{XSPH19_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe9 */
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
{SWITCH_PRES_TOL17,       TP_DSK_BG,      PFlt_WHToVS_Soll}, /* hydr. Tol Einspritzdr. Agg1 Stufe 7*/ 
{SWITCH_PRES_TOL18,       TP_DSK_BG,      PFlt_WHToVS_Soll}, /* hydr. Tol Einspritzdr. Agg1 Stufe 8*/ 
{SWITCH_PRES_TOL19,       TP_DSK_BG,      PFlt_WHToVS_Soll}, /* hydr. Tol Einspritzdr. Agg1 Stufe 9*/ 
/* ---------------- Soll Toleranz Einspritzdruck spec.--------------------- */
{SWITCH_PRES_TOL17_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 7*/
{SWITCH_PRES_TOL18_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 8*/
{SWITCH_PRES_TOL19_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 9*/
/* ---------------- Soll Toleranz Einspritzzeit --------------------------- */
{INJ_TIME_TOL17,          TP_DSK_BG,      0}, /* Tol Einspritzzeit Agg1 Stufe 7*/ 
{INJ_TIME_TOL18,          TP_DSK_BG,      0}, /* Tol Einspritzzeit Agg1 Stufe 8*/ 
{INJ_TIME_TOL19,          TP_DSK_BG,      0}, /* Tol Einspritzzeit Agg1 Stufe 9*/ 
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
{SWITCH_POINT_TOL17,      TP_DSK_BG,      PFlt_WHToVS_Soll}, /* Tol Um.Point Agg1 Stufe 7*/ 
{SWITCH_POINT_TOL18,      TP_DSK_BG,      PFlt_WHToVS_Soll}, /* Tol Um.Point Agg1 Stufe 8*/ 
{SWITCH_POINT_TOL19,      TP_DSK_BG,      PFlt_WHToVS_Soll}, /* Tol Um.Point Agg1 Stufe 9*/ 
/* ---------------- Soll Toleranz Umschaltpunkt volume -------------------- */
{SWITCH_POINT_TOL17_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe7 */
{SWITCH_POINT_TOL18_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe8 */
{SWITCH_POINT_TOL19_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe9 */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
{SWITCH_PRES_REF17,       TP_DSK_BG,      0}, /* hydr.Einspritzdruck Agg1 Stufe7 */
{SWITCH_PRES_REF18,       TP_DSK_BG,      0}, /* hydr.Einspritzdruck Agg1 Stufe8 */
{SWITCH_PRES_REF19,       TP_DSK_BG,      0}, /* hydr.Einspritzdruck Agg1 Stufe9 */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
{SWITCH_PRES_REF17_SPEC,  TP_BG,          PFlt_HydrToSpecIst}, /* spec.Einspritzdruck Agg1 Stufe7 */
{SWITCH_PRES_REF18_SPEC,  TP_BG,          PFlt_HydrToSpecIst}, /* spec.Einspritzdruck Agg1 Stufe8 */
{SWITCH_PRES_REF19_SPEC,  TP_BG,          PFlt_HydrToSpecIst}, /* spec.Einspritzdruck Agg1 Stufe9 */
/* ---------------- REF Einspritzzeit ------------------------------------- */
{INJ_TIME_REF17,          TP_DSK_BG,      0}, /* Einspritzzeit Agg1 Stufe7 */
{INJ_TIME_REF18,          TP_DSK_BG,      0}, /* Einspritzzeit Agg1 Stufe8 */
{INJ_TIME_REF19,          TP_DSK_BG,      0}, /* Einspritzzeit Agg1 Stufe9 */
/* ---------------- REF Umschaltpunkte ------------------------------------ */
{SWITCH_POINT_REF17,      TP_DSK_BG,      0}, /* Umschaltpunkt Agg1 Stufe7 */
{SWITCH_POINT_REF18,      TP_DSK_BG,      0}, /* Umschaltpunkt Agg1 Stufe8 */
{SWITCH_POINT_REF19,      TP_DSK_BG,      0}, /* Umschaltpunkt Agg1 Stufe9 */
/* ---------------- REF Umschaltpunkte ------------------------------------ */
{SWITCH_POINT_REF17_VOL,  TP_BG,          PFlt_WayToVolIst}, /* Umschaltvolumen Agg1 Stufe7 */
{SWITCH_POINT_REF18_VOL,  TP_BG,          PFlt_WayToVolIst}, /* Umschaltvolumen Agg1 Stufe8 */
{SWITCH_POINT_REF19_VOL,  TP_BG,          PFlt_WayToVolIst}, /* Umschaltvolumen Agg1 Stufe9 */
/* ------------------------------------------------------------------------ */
/* ---------------- spez.-Register fuer hydr./spec. Umschaltung (10-12 Spritzstufen) */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
{SPPH1A_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 10*/
{SPPH1B_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 11*/
{SPPH1C_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 12*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
{XPPH1A_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 10*/
{XPPH1B_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 11*/
{XPPH1C_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 12*/
/* ---------------- Soll Einspritzgeschwindigkeit ------------------------- */
{SVPH1A_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Einspritzges. Agg1 Stufe10 */
{SVPH1B_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Einspritzges. Agg1 Stufe11 */
{SVPH1C_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Einspritzges. Agg1 Stufe12 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
{SPUM19_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe  9*/
{SPUM1A_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 10*/
{SPUM1B_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 11*/
{SPUM1C_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 12*/
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
{SSPH1A_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe10 */
{SSPH1B_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe11 */
{SSPH1C_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Vol Agg1 Stufe12 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
{XSPH1A_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe10 */
{XSPH1B_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe11 */
{XSPH1C_VOL,              TP_STD,         PFlt_WayToVolIst}, /* Umschaltpkt Vol Agg1 Stufe12 */
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
{SWITCH_PRES_TOL1A,       TP_DSK_BG,      PFlt_WHToVS_Soll}, /* hydr. Tol Einspritzdr. Agg1 Stufe 10*/ 
{SWITCH_PRES_TOL1B,       TP_DSK_BG,      PFlt_WHToVS_Soll}, /* hydr. Tol Einspritzdr. Agg1 Stufe 11*/ 
{SWITCH_PRES_TOL1C,       TP_DSK_BG,      PFlt_WHToVS_Soll}, /* hydr. Tol Einspritzdr. Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Einspritzdruck spec.--------------------- */
{SWITCH_PRES_TOL1A_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 10*/
{SWITCH_PRES_TOL1B_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 11*/
{SWITCH_PRES_TOL1C_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 12*/
/* ---------------- Soll Toleranz Einspritzzeit --------------------------- */
{INJ_TIME_TOL1A,          TP_DSK_BG,      0}, /* Tol Einspritzzeit Agg1 Stufe 10*/ 
{INJ_TIME_TOL1B,          TP_DSK_BG,      0}, /* Tol Einspritzzeit Agg1 Stufe 11*/ 
{INJ_TIME_TOL1C,          TP_DSK_BG,      0}, /* Tol Einspritzzeit Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
{SWITCH_POINT_TOL1A,      TP_DSK_BG,      PFlt_WHToVS_Soll}, /* Tol Um.Point Agg1 Stufe 10*/ 
{SWITCH_POINT_TOL1B,      TP_DSK_BG,      PFlt_WHToVS_Soll}, /* Tol Um.Point Agg1 Stufe 11*/ 
{SWITCH_POINT_TOL1C,      TP_DSK_BG,      PFlt_WHToVS_Soll}, /* Tol Um.Point Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Umschaltpunkt volume -------------------- */
{SWITCH_POINT_TOL1A_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe10 */
{SWITCH_POINT_TOL1B_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe11 */
{SWITCH_POINT_TOL1C_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe12 */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
{SWITCH_PRES_REF1A,       TP_DSK_BG,      0}, /* hydr.Einspritzdruck Agg1 Stufe10 */
{SWITCH_PRES_REF1B,       TP_DSK_BG,      0}, /* hydr.Einspritzdruck Agg1 Stufe11 */
{SWITCH_PRES_REF1C,       TP_DSK_BG,      0}, /* hydr.Einspritzdruck Agg1 Stufe12 */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
{SWITCH_PRES_REF1A_SPEC,  TP_BG,          PFlt_HydrToSpecIst}, /* spec.Einspritzdruck Agg1 Stufe10 */
{SWITCH_PRES_REF1B_SPEC,  TP_BG,          PFlt_HydrToSpecIst}, /* spec.Einspritzdruck Agg1 Stufe11 */
{SWITCH_PRES_REF1C_SPEC,  TP_BG,          PFlt_HydrToSpecIst}, /* spec.Einspritzdruck Agg1 Stufe12 */
/* ---------------- REF Einspritzzeit ------------------------------------- */
{INJ_TIME_REF1A,          TP_DSK_BG,      0}, /* Einspritzzeit Agg1 Stufe10 */
{INJ_TIME_REF1B,          TP_DSK_BG,      0}, /* Einspritzzeit Agg1 Stufe11 */
{INJ_TIME_REF1C,          TP_DSK_BG,      0}, /* Einspritzzeit Agg1 Stufe12 */
/* ---------------- REF Umschaltpunkte ------------------------------------ */
{SWITCH_POINT_REF1A,      TP_DSK_BG,      0}, /* Umschaltpunkt Agg1 Stufe10 */
{SWITCH_POINT_REF1B,      TP_DSK_BG,      0}, /* Umschaltpunkt Agg1 Stufe11 */
{SWITCH_POINT_REF1C,      TP_DSK_BG,      0}, /* Umschaltpunkt Agg1 Stufe12 */
/* ---------------- REF Umschaltpunkte ------------------------------------ */
{SWITCH_POINT_REF1A_VOL,  TP_BG,          PFlt_WayToVolIst}, /* Umschaltvolumen Agg1 Stufe10 */
{SWITCH_POINT_REF1B_VOL,  TP_BG,          PFlt_WayToVolIst}, /* Umschaltvolumen Agg1 Stufe11 */
{SWITCH_POINT_REF1C_VOL,  TP_BG,          PFlt_WayToVolIst}, /* Umschaltvolumen Agg1 Stufe12 */
/* ------------------------------------------------------------------------ */

/* Register zur IQT-internen Verwaltung der Schusszaehler.           */
/* Diese IQT-Register ersetzen alte ISCOS-Register.                  */
{XNADD,                   TP_LNG,         0}, /* Addierender Schusszaehler     */
{XNSUB,                   TP_LNG,         0}, /* Subtrahierender Schusszaehler */
{XSNSUS,                  TP_LNG_BG,      PFlt_Production}, /* Produktionsmenge in Stueck */
{HOST_AGGREGAT,           TP_STD,         0}, /* AggNr. fuer UserFkt. bei Hostzugriff  */
{HOST_ACT_REGLER_NR,      TP_STD,         0}, /* akt. Reglernr ...                     */

/* ---------------- IQT-Einspritzregister --------------------------------- */
{WKZINN_TOL_AGG2,         TP_DSK_BG,      0},
{WKZINN_TOL,              TP_DSK_BG,      0},
{ZYKZEIT_TOL,             TP_DSK_BG,      0},
{PLAST_TIME_TOL,          TP_DSK_BG,      0},
{DWELL_PRES1,             TP_STD,         0}, /* Istwert Nachdruckstufe Agg.1 fuer Host*/
{DWELL_PRES2,             TP_STD,         0}, /* Istwert Nachdruckstufe Agg.2 fuer Host*/
{FILL_TIME1,              TP_STD,         0}, /* Istwert Fuellzeit Agg.1 fuer Host     */
{FILL_TIME2,              TP_STD,         0}, /* Istwert Fuellzeit Agg.2 fuer Host     */
{TOL_SELECT,              TP_BG,          0},
{TOL_NR_INJ_CYC1,         TP_BG,          0},
{INJ_WORK,                TP_LNG,         0}, /* Einspritzarbeit            */

/* ----- Var. Einpritzgeschwindigkeiten S.41/42 abh. von Kundenprompar. --- */
{INJ_SPEED_MAX1,          TP_STD,         0},
{INJ_SPEED_MAX2,          TP_STD,         0},
{INJ_SPEED_MAX3,          TP_STD,         0},
{INJ_SPEED_CONV1,         TP_STD,         0},
{INJ_SPEED_CONV2,         TP_STD,         0},
{INJ_SPEED_CONV3,         TP_STD,         0},
/* ---------------- sonstige IQT-Register --------------------------------- */
{EJECT_HASCO,             TP_STD,         0},
{WKZ_CODE,                TP_BG,          0},
{AGGREGAT0,               TP_STD,         0},
{AGGREGAT,                TP_STD,         0},
{STATION,                 TP_STD,         0},
{IQT_DUMMY_REG,           TP_STD,         0},
{HOST_UPDOWN_REG,         TP_STD,         0},
{FGBG_DATASET_EQUAL,      TP_STD,         0},
{NR_PLAST,                TP_STD,         0},
{ACT_SN_PARAM_TAB,        TP_STD,         0},
{MAX_TEMPHEAT,            TP_STD,         0},
{MAX_HEATCHAN,            TP_STD,         0},
{XSSFZU_SHOW,             TP_STD,         0},
{MAX_INJUNITS,            TP_STD,         0},
/* ---------------- stat. Prozesskontrolle -------------------------------- */
{SPCVarTab,               TP_LNG10_DSK_BG,PKlickFltFunc},
{SPCRegInd1,              TP_INT10_DSK_BG,0},
{SPCRegInd2,              TP_INT10_DSK_BG,0},
{SPCIndex,                TP_DSK_BG,      0},
{SPCTestSize,             TP_DSK_BG,      PSPCFltFunc},
{SPCTestBreakSize,        TP_DSK_BG,      0},
{SPCNrPreTests,           TP_DSK_BG,      PSPCFltFunc},
{SPCMSkaleEnd,            TP_LNG10_DSK_BG,0},
{SPCMSkaleBegin,          TP_LNG10_DSK_BG,0},
{SPCSSkaleEnd,            TP_LNG10_DSK_BG,0},
{SPCSSkaleBegin,          TP_LNG10_DSK_BG,0},
{SPCRSkaleEnd,            TP_LNG10_DSK_BG,0},
{SPCRSkaleBegin,          TP_LNG10_DSK_BG,0},
{SPCMUEG,                 TP_LNG10,       0},
{SPCMOEG,                 TP_LNG10,       0},
{SPCSUEG,                 TP_LNG10,       0},
{SPCSOEG,                 TP_LNG10,       0},
{SPCRUEG,                 TP_LNG10,       0},
{SPCROEG,                 TP_LNG10,       0},
{SPCMUEGm,                TP_LNG10_DSK_BG,0},
{SPCMOEGm,                TP_LNG10_DSK_BG,0},
{SPCSUEGm,                TP_LNG10_DSK_BG,0},
{SPCSOEGm,                TP_LNG10_DSK_BG,0},
{SPCRUEGm,                TP_LNG10_DSK_BG,0},
{SPCROEGm,                TP_LNG10_DSK_BG,0},
{SPCOSGcm,                TP_LNG10_DSK_BG,0},
{SPCUSGcm,                TP_LNG10_DSK_BG,0},
{SPCPreTestSwitch,        TP_STD,         0},
{SPCAutoSwitch,           TP_STD,         0},
{SPCManualSwitch,         TP_STD,         0},
{SPCTimeSwitch,           TP_STD,         0},
{SPCTestCount,            TP_STD,         0},
{SPCBreakCount,           TP_STD,         0},
{SPCM,                    TP_LNG10,       0},
{SPCS,                    TP_LNG10,       0},
{SPCMpS,                  TP_LNG10,       0},
{SPCMmS,                  TP_LNG10,       0},
{SPCcm,                   TP_LNG10,       0},
{SPCcmk,                  TP_LNG10,       0},
{SPCcp,                   TP_LNG10,       0},
{SPCcpk,                  TP_LNG10,       0},
{SPCMMRegTab,             TP_LNG10,       0},
{SPCMSRegTab,             TP_LNG10,       0},
{SPCMRRegTab,             TP_LNG10,       0},
{SPCPreTestCount,         TP_STD,         0},
{SPCOSGcp,                TP_LNG10_DSK_BG,0},
{SPCUSGcp,                TP_LNG10_DSK_BG,0},
{SPCRegInd3,              TP_INT10_DSK_BG,0},
{SPCAggregat,             TP_INT10_DSK_BG,0},
/* ---------------- Betriebsdatenerfassung -------------------------------- */
{BDEAggregat,             TP_INT10_DSK_BG,0},
{BDERegInd3,              TP_INT10_DSK_BG,0},
{BDEVarTab,               TP_LNG10_DSK_BG,PKlickFltFunc},
{BDERegInd1,              TP_INT10_DSK_BG,0},
{BDERegInd2,              TP_INT10_DSK_BG,0},
{BDENrDocCycles,          TP_BG,          0},
{BDENrNotDocCycles,       TP_BG,          0},
{BDEProcDataSwitch,       TP_BG,          0},
{BDEErrMsgSwitch,         TP_STD,         0},
{BDEStopTimeSwitch,       TP_STD,         0},
{BDESollDataSwitch,       TP_STD,         0},
{BDEContSwitch,           TP_BG,          0},
{BDEStartInt1,            TP_BG,          0},
{BDEStopInt1,             TP_BG,          0},
{BDEStartInt2,            TP_BG,          0},
{BDEStopInt2,             TP_BG,          0},
{BDEStartInt3,            TP_BG,          0},
{BDEStopInt3,             TP_BG,          0},
{BDEPrintMode,            TP_STD,         0},
{BDEStartPrint,           TP_STD,         0},
{BDEStartClearBuffer,     TP_STD,         0},
{BDEStartPrintLegend,     TP_STD,         0},
{BDECycleInt,             TP_STD,         0},
/* ---------------- Trenddarstellung -------------------------------------- */
{AxisVarTab,              TP_LNG20_DSK_BG,PKlickFltFunc},
{AxisRegInd1,             TP_INT20_DSK_BG,0},
{AxisRegInd2,             TP_INT20_DSK_BG,0},
{AxisRegInd3,             TP_INT20_DSK_BG,0},
{AxisAggregat,            TP_INT20_DSK_BG,0},

/* ---------------- Register fuer Realtime-Clock -------------------------- */
{TIME_IST_HH,             TP_STD,         0},
{TIME_IST_MM,             TP_STD,         0},
{TIME_IST_SS,             TP_STD,         0},
{DATE_IST_DD,             TP_STD,         0},
{DATE_IST_MM,             TP_STD,         0},
{DATE_IST_YY,             TP_STD,         0},
{TIME_SOLL_HH,            TP_STD,         0},
{TIME_SOLL_MM,            TP_STD,         0},
{TIME_SOLL_SS,            TP_STD,         0},
{DATE_SOLL_DD,            TP_STD,         0},
{DATE_SOLL_MM,            TP_STD,         0},
{DATE_SOLL_YY,            TP_STD,         0},

/* ----- Multiplex-Register fuer Heizzonen, spez. fuer Reglerparameter ---- */
{ACT_CYL_HEAT_ZONE,       TP_STD,         0},
{ACT_TOOL_HEAT_ZONE,      TP_STD,         0},
{ACT_TEMP_HEAT_ZONE,      TP_STD,         0},
{ACT_REGLER_NR,           TP_STD,         0},

/* ---------------- Zusaetzliche Register fr die Heizzonen ---------------- */
{INJHEAT_ABS_NORM,        TP_DSK_BG,      0}, /* Temperaturabsenkung Zylinder normal */
{INJHEAT_ABS_IN,          TP_STD,         0}, /* Temperaturabsenkung Zylinder Einzug */
{TOOLHEAT_ABS,            TP_STD,         0}, /* Temperaturabsenkung Werkzeug */
{TEMPHEAT_ABS,            TP_STD,         0}, /* Temperaturabsenkung Temperiergerte */
{INJHEAT_ANF_NORM,        TP_STD,         0}, /* Anfahrschaltung Zylinder normal */
{INJHEAT_ANF_IN,          TP_STD,         0}, /* Anfahrschaltung Zylinder Einzug */
{TOOLHEAT_ANF,            TP_STD,         0}, /* Anfahrschaltung Werkzeug */
{TEMPHEAT_ANF,            TP_STD,         0}, /* Anfahrschaltung Temperiergeraete */
{HEAT_OPTMODE,            TP_STD,         PHeatOptmode},  /* Optimierungsart eines Reglers */
{OPTMODEREGLER,           TP_STD,         POptmodeRegler},/* x-ter Regler im Optimierungsblock */
/* ---------------- Datentraeger ------------------------------------------ */
{DISK_FILE_TYPE,          TP_STD,         0},
{EXT_COUNT_MAX,           TP_DSK_BG,      0},
{EXT_COUNT_ACT,           TP_STD,         0},

/* ---------------- Frei konfigurierbare Seiten --------------------------- */
{REG_FOT_PAGE_1,          TP_LNG20_FOT_BG,PKlickFltFunc},
{REG_FOT_PAGE_2,          TP_LNG20_FOT_BG,PKlickFltFunc},
{REG_FOT_PAGE_3,          TP_LNG20_FOT_BG,PKlickFltFunc},

{XSSAUS3_INVERS,          TP_STD,         0},   /* Anzeige Auswerferrueckweg S.52 */

/* ---------------- Leitrechner Seite 21.1 -------------------------------- */
{HOST_START_ORDER,        TP_STD,         PFlt_HOST_START_ORDER},/* Auftragsstart      */
{HOST_STOP_ORDER,         TP_STD,         PFlt_HOST_STOP_ORDER}, /* Auftragsende       */
{HOST_CANCEL_ORDER,       TP_STD,         PFlt_HOST_STOP_ORDER}, /* Auftragsabbruch    */
{HOST_REJECTS,            TP_STD,         PFlt_HOST_REJECTS},    /* Ausschussteile eing*/
{HOST_GOOD_PARTS,         TP_STD,         PFlt_HOST_REJECTS},    /* Gutteile zurueckf. */
{HOST_PAUSE_CYCLES,       TP_STD,         0 },                   /* Pausenzyklen       */

/* ---------------- Register fr die Prozessgraphik ------------------------ */
{PG_OPMODE,               TP_STD,         0},       /* Istwertregister fuer Betriebsart */
{PG_MTIME,                TP_DSK_BG,      PPGComp}, /* Meazeit in sec */
{PG_DELAY,                TP_DSK_BG,      PPGComp}, /* Startverzgerung in 1/10 sec */
{PG_XRIGHT,               TP_STD,         0},       /* rechte X-Skal.in 1/10 sec: MTIME*10+DELAY */
{PG_MINT,                 TP_DSK_BG,      PPGComp}, /* Messintervall */
{PG_MAXX,                 TP_DSK_BG,      PPGComp}, /* Maximalwert fuer x-Achse Arbeitsgr. */
{PG_MAXY,                 TP_INT10_DSK_BG,PPGComp}, /* Maximalwert Y-Skalierung 1-8 */
{PG_SKALY,                TP_INT10_DSK_BG,PPGComp}, /* Skalierendwert der Y-Achse 1-8 */
{PG_SOLLIST,              TP_INT10_DSK_BG,PPGComp}, /* Nr der Kanle fr Soll-Ist-Vergl. 1-4 */
{PG_TOL,                  TP_INT10_DSK_BG,PPGComp}, /* Toleranzen in Prozent fr obige Kanle*/
{PG_WORK,                 TP_LNG_DSK_BG,  PPGComp}, /* Arbeitsber., 0=nein, 1=ja, 2=mit Ueb. */
{PG_START_WORK,           TP_LNG_DSK_BG,  PPGComp}, /* Startwert des Arbeitsintegrals */
{PG_STOP_WORK,            TP_LNG_DSK_BG,  PPGComp}, /* Endpunkt des Arbeitsintegrals */
{PG_IST_WORK,             TP_LNG,         PPGComp}, /* Istwert der Arbeit */
{PG_REFIST_WORK,          TP_LNG,         PPGComp}, /* Referenzistwert der Arbeit */
{PG_TOL_WORK,             TP_LNG_DSK_BG,  PPGComp}, /* Tol. in % fuer Arbeitsueberwachung */
{PG_CUR1,                 TP_LNG,         0}, /* Istwert: Position des Cursors 1 */
{PG_CUR2,                 TP_LNG,         0}, /* Istwert: Position des Cursors 2 */
{PG_MAX_IST,              TP_INT10,       0}, /* Istwert: Maximalwerte der Istkurven */
{PG_CUR1_IST,             TP_INT10,       0}, /* Istwert: Werte der Istkurven bei Cur1 */
{PG_CUR2_IST,             TP_INT10,       0}, /* Istwert: Werte der Istkurven bei Cur2 */
{PG_TOLUP_MAX_IST,        TP_STD,         0}, /* Istwert: Maximum der oberen Tol. */
{PG_TOLDOWN_MAX_IST,      TP_STD,         0}, /* Istwert: Maximum der unteren Tol. */
{PG_SOLL_MAX_IST,         TP_STD,         0}, /* Istwert: Maximum der Sollkurve */
{PG_TOLUP_CUR1_IST,       TP_STD,         0}, /* Istwert: Wert der oberen Tol bei Cur1 */
{PG_TOLDOWN_CUR1_IST,     TP_STD,         0}, /* Istwert: Wert der unteren Tol bei Cur1*/
{PG_SOLL_CUR1_IST,        TP_STD,         0}, /* Istwert: Wert der Sollkurve bei Cur1 */
{PG_TOLUP_CUR2_IST,       TP_STD,         0}, /* Istwert: Wert der oberen Tol bei Cur2 */
{PG_TOLDOWN_CUR2_IST,     TP_STD,         0}, /* Istwert: Wert der unteren Tol bei Cur2*/
{PG_SOLL_CUR2_IST,        TP_STD,         0}, /* Istwert: Wert der Sollkurve bei Cur2 */
{PG_XLEFT,                TP_STD,         0}, /* links X-Skal.in 1/10 sec: MTIME*10+DELAY */
{PG_OPMODE_SOLL,          TP_PGDSK_BG,    0}, /* Sollwertregister fuer Betriebsart */
{PG_XNADD,                TP_LNG,         0}, /* Sicherung Schusszaehler fuer PG */

/* ---------------- Register fuer die Wochentagsschaltuhr ----------------- */
{WCLOCK_DATE_DD,          TP_DSK_BG,      0},                 /* Schaltuhr ueber Datum, Tag          */
{WCLOCK_DATE_MM,          TP_DSK_BG,      0},                 /* Schaltuhr ueber Datum, Monat        */
{WCLOCK_DATE_YY,          TP_DSK_BG,      0},                 /* Schaltuhr ueber Datum, Jahr         */
{WCLOCK_START,            TP_INT10_DSK_BG,PFlt_WClockSetTime},/* Ein-, Ausschaltzeiten, hh.mm,       */
{WCLOCK_STOP,             TP_INT10_DSK_BG,PFlt_WClockSetTime},/* Index 1 - 7 benutzt fuer Mo - So    */
{WCLOCK_MOTOR_START_DELAY,TP_DSK_BG,      PFlt_WClockSetTime},/* Einschaltverzoegerung Motor         */
{WCLOCK_HEAT_START_DELAY, TP_DSK_BG,      PFlt_WClockSetTime},/* Einschaltverzoegerung Heizung       */
{WCLOCK_EXT1_START_DELAY, TP_DSK_BG,      PFlt_WClockSetTime},/* Einschaltverzoegerung ext. Geraet 1 */
{WCLOCK_EXT2_START_DELAY, TP_DSK_BG,      PFlt_WClockSetTime},/* Einschaltverzoegerung ext. Geraet 2 */
{WCLOCK_MOTOR_STOP_DELAY, TP_DSK_BG,      PFlt_WClockSetTime},/* Ausschaltverzoegerung Motor         */
{WCLOCK_HEAT_STOP_DELAY,  TP_DSK_BG,      PFlt_WClockSetTime},/* Ausschaltverzoegerung Heizung       */
{WCLOCK_EXT1_STOP_DELAY,  TP_DSK_BG,      PFlt_WClockSetTime},/* Ausschaltverzoegerung ext. Geraet 1 */
{WCLOCK_EXT2_STOP_DELAY,  TP_DSK_BG,      PFlt_WClockSetTime},/* Ausschaltverzoegerung ext. Geraet 2 */
{WCLOCK_EXT1_SWITCH,      TP_DSK_BG,      PFlt_WClockSwitch}, /* Schaltuhr auf ext. Geraet 1 anwenden*/
{WCLOCK_EXT2_SWITCH,      TP_DSK_BG,      PFlt_WClockSwitch}, /* Schaltuhr auf ext. Geraet 2 anwenden*/
{WCLOCK_MOTOR_SWITCH,     TP_DSK_BG,      0},                 /* Schaltuhr auf Motor anwenden        */
{WCLOCK_HEAT_SWITCH,      TP_DSK_BG,      0},                 /* Schaltuhr auf Heizung anwenden      */

/* ---------------- Register fuer das Drucken ----------------------------- */
{PRINT_MODE,              TP_DSK_BG,      PFlt_PRINT},/* Druck-Modus        */
{PRINT_PAGE,              TP_INT10_DSK_BG,0},         /* zu druckende Seiten          */
{PRINT_ERROR_PAGE,        TP_DSK_BG,      0},         /* Fehlermeldungseite drucken ? */
{PRINT_TIME_INT,          TP_DSK_BG,      PFlt_PRINT},/* Zeit-Intervall                   */
{PRINT_CYCLE_INT,         TP_DSK_BG,      PFlt_PRINT},/* Zyklus-Intervall                 */
{PRINT_AUT_MASH_STOP,     TP_DSK_BG,      0},         /* Drucken bei autom. Maschinenstop */
{PRINT_PRINTER_TYPE,      TP_DSK_BG,      0},         /* Druckertyp */
{PRINT_STATUS_LINE,       TP_DSK_BG,      0},         /* Statuszeilen ausgeben ? */
{PRINT_SOFTKEYS,          TP_DSK_BG,      0},         /* Softkeys ausgeben ?     */
{PRINT_LINES_PER_PAGE,    TP_DSK_BG,      0},         /* Anzahl Zeilen pro Seite */
{PRINT_MRGN_TOP,          TP_DSK_BG,      0},         /* Randabstand oben  */
{PRINT_MRGN_BOTTOM,       TP_DSK_BG,      0},         /* Randabstand unten */
{PRINT_PAGE_AGGREGAT,     TP_INT10_DSK_BG,0},         /* Spritzeinh. der zu dr. Seiten */

/* Register fuer die Schnittstellen-Konfiguration */
{IFK_DEVICE,              TP_LNG20,       0}, /* Zuordnung zu Geraet */
{IFK_DATA_BITS,           TP_LNG20,       0}, /* Anzahl Datenbits */
{IFK_STOP_BITS,           TP_LNG20,       0}, /* Anzahl Stopbits */
{IFK_PARITY,              TP_LNG20,       0}, /* Parity */
{IFK_BAUDRATE,            TP_LNG20,       0}, /* Baudrate */

/* ---------------- Register fuer den Leitrechner ------------------------- */
{XPOJSS,                  TP_STD,         PFlt_XPOJSS}, /* Auftragsstart fuer Leitrechner*/
{XPOJES,                  TP_STD,         PFlt_XPOJES}, /* Auftragsende  fuer Leitrechner*/

/* ---------------- Register fuer die Schichtzaehler ---------------------- */
{SCHICHT1_BEGIN,          TP_BG,          0},           /* Schicht 1 Beginn */
{SCHICHT1_END,            TP_BG,          0},           /* Schicht 1 Ende   */
{SCHICHT2_BEGIN,          TP_BG,          0},           /* Schicht 2 Beginn */
{SCHICHT2_END,            TP_BG,          0},           /* Schicht 2 Ende   */
{SCHICHT3_BEGIN,          TP_BG,          0},           /* Schicht 3 Beginn */
{SCHICHT3_END,            TP_BG,          0},           /* Schicht 3 Ende   */
{AUSSCHUSS_SCHICHT,       TP_LNG_BG,      0},       /* Ausschuss pro Schicht*/
{AUSSCHUSS_GESAMT,        TP_LNG_BG,      0},       /* Ausschuss gesamt     */
{GUTTEILE_SCHICHT,        TP_LNG_BG,      0},       /* Gutteile pro Schicht */

/* ---------------- Register fuer Gutteile und Schlechtteile pro Schicht -- */
{SCHICHT1_GOOD,           TP_LNG_BG,      0},    /* Schicht 1 Gutteile      */
{SCHICHT1_BAD,            TP_LNG_BG,      0},    /* Schicht 1 Schlechtteile */
{SCHICHT2_GOOD,           TP_LNG_BG,      0},    /* Schicht 2 Gutteile      */
{SCHICHT2_BAD,            TP_LNG_BG,      0},    /* Schicht 2 Schlechtteile */
{SCHICHT3_GOOD,           TP_LNG_BG,      0},    /* Schicht 3 Gutteile      */
{SCHICHT3_BAD,            TP_LNG_BG,      0},    /* Schicht 3 Schlechtteile */

/* ---------------- Register fuer Betriebsstundenzaehler --------------- -- */
{BTCOUNTER_IST_HH,        TP_LNG_BG,      0}, /* Betriebsstundenzaehler IST in Stunden */
{BTCOUNTER_IST_MM,        TP_BG,          0}, /* Betriebsstundenzaehler IST in Minuten */
{BTCOUNTER_SOLL_HH,       TP_LNG,         0}, /* Betriebsstundenzaehler SOLL in Stunden */
{BTCOUNTER_SOLL_MM,       TP_STD,         0}, /* Betriebsstundenzaehler SOLL in Minuten */

{ACT_PALETTE,             TP_STD,         PFlt_ColorPalette}, /* Farbumschaltung */
{ACT_SYSPRINTER,          TP_STD,         0},    /* Systemdrucker SYSPRN    */

/* An dieser Stelle fuegen die Sub- und Sonderversionen ihre Register ein */


/* ---------------- Sonderregister B&R fuer Zeitanalyse ------------------- */
{IZEITAND,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{IZEITANAVERD,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN1,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN2,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN3,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN4,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN5,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN6,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN7,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN8,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN9,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANA,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANB,                TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANC,                TP_LNG,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER1,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER2,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER3,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER4,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER5,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER6,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER7,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER8,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER9,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVERA,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVERB,            TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVERC,            TP_LNG,         0},      /* S. 17.1 Zeitananalyse */
{XZYLINDERHUB,            TP_STD,         0},      /* XMP05 - XMP06 default */

{XZEITAN4_2,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN4_3,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN4_4,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN5_2,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN5_3,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN5_4,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN6_2,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN6_3,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITAN6_4,              TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER4_2,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER4_3,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER4_4,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER5_2,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER5_3,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER5_4,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER6_2,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER6_3,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */
{XZEITANAVER6_4,          TP_STD,         0},      /* S. 17.1 Zeitananalyse */

{ISRSSVOR,                TP_INT10_BG,    0}, /* Schummelregister-Array fuer Schneckenr. */
{IPLASTSTUFE,             TP_INT10_BG,    0}, /* Schummelregister-Array fuer 2/4 Plastifizierstufen */

/* ---------------- Register fuer den Roboter ----------------------------- */
{ROB_MODE,                TP_ROB_BG,      0},

{ROB_PAR_POINT1,          TP_LNG20_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_POINT2,          TP_LNG20_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_POINT3,          TP_LNG20_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_POINT4,          TP_LNG20_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_POINT5,          TP_LNG20_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_V,               TP_INT10_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_D,               TP_LNG10_ROB_BG,PFlt_ROB_PAR},
{ROB_PAR_G,               TP_INT10_ROB_BG,PFlt_ROB_PAR},

{ROB_STEP_FLAG,           TP_BG,          PFlt_ROB_WRITE},
{ROB_SPEED,               TP_ROB_BG,      PFlt_ROB_WRITE},

{ROB_MACRO_STEP_M1,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M2,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M3,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M4,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M5,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M6,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M7,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M8,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M9,       TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M10,      TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M11,      TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_M12,      TP_INT10_ROB_BG,0},

{ROB_MACRO_STEP_P1_1,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_2,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_3,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_4,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_5,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_6,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_7,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_8,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_9,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_10,    TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_11,    TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P1_12,    TP_INT10_ROB_BG,0},

{ROB_MACRO_STEP_P2_1,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_2,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_3,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_4,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_5,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_6,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_7,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_8,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_9,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_10,    TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_11,    TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P2_12,    TP_INT10_ROB_BG,0},

{ROB_MACRO_STEP_P3_1,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_2,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_3,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_4,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_5,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_6,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_7,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_8,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_9,     TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_10,    TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_11,    TP_INT10_ROB_BG,0},
{ROB_MACRO_STEP_P3_12,    TP_INT10_ROB_BG,0},

{ROB_MULT_PGM,            TP_STD,         0},
{ROB_MULT_PAR_P,          TP_STD,         0},
{ROB_MULT_FIX,            TP_STD,         0},
{ROB_INOUT_TYPE,          TP_STD,         0},

{ROB_ACT_P1,              TP_LNG,         PFlt_ROB_READ},
{ROB_ACT_P2,              TP_LNG,         PFlt_ROB_READ},
{ROB_ACT_P3,              TP_LNG,         PFlt_ROB_READ},
{ROB_ACT_P4,              TP_LNG,         PFlt_ROB_READ},
{ROB_ACT_P5,              TP_LNG,         PFlt_ROB_READ},
{ROB_ACT_VAR,             TP_INT10,       PFlt_ROB_READ},

{ROB_INOUT_BYTE1_16,      TP_INT20,       PFlt_ROB_READ},
{ROB_INOUT_BYTE17_32,     TP_INT20,       PFlt_ROB_READ},

/* ---------------- Register fuer die Heizungs-Selbstoptimierung ---------- */
{HEATOPT_REGLER,          TP_STD,         0}, /* Multiplexregister der Seite 39   */
{LAST_HEATOPT_REGLER,     TP_STD,         0}, /* Letzter Wert von HEATOPT_REGLER, */
                                              /* der <>0 war; Ist HEATOPT_REGLER>0*/
                                              /* so sind beide Register identisch */
{HEATOPT_DUMMY,           TP_STD,         0}, /* Ausgabe der Block-Reglernummern. */
{OPTHEAT_TN,              TP_STD,         0}, /* Die folgenden Register enthalten */
{OPTHEAT_TV,              TP_STD,         0}, /* die Werte des aktuellen Reglers, */
{OPTHEAT_XPH,             TP_STD,         0}, /* wie sie auf der Temperaturkarte  */
{OPTHEAT_XPK,             TP_STD,         0}, /* stehen. Sie werden per speziellem*/
{OPTHEAT_HEAT_PERIOD,     TP_STD,         0}, /* Datacom vom Iscos geholt fuer die*/
{OPTHEAT_COOL_PERIOD,     TP_STD,         0}, /* Anzeige auf Seite 39.            */

/* ---------------- Register fuer Maschinenabgleichs Seite 89.1 ----------- */
{IVENTIL_IND,             TP_STD,         0}, /* Ventil-Index               */
{IMAS_OFFS1,              TP_STD,         0}, /* Offset 1                   */
{IMAS_OFFS2,              TP_STD,         0}, /* Offset 2                   */
{IMAS_VERS1,              TP_STD,         0}, /* Verst{rkung 1              */
{IMAS_VERS2,              TP_STD,         0}, /* Verst{rkung 2              */

/* Register fuer erweiterte Aggregattabelle, Aggregat 2-5 */
{INJ_MP01_2,   TP_BG,         0},
{INJ_MP02_2,   TP_BG,         0},
{INJ_MP03_2,   TP_BG,         0},
{INJ_MP04_2,   TP_BG,         0},
{INJ_MP05_2,   TP_BG,         0},
{INJ_MP06_2,   TP_BG,         0},
{INJ_MP07_2,   TP_BG,         0},
{INJ_MP08_2,   TP_BG,         0},
{INJ_MP09_2,   TP_BG,         0},
{INJ_MP10_2,   TP_BG,         0},
{INJ_MP01_3,   TP_BG,         0},
{INJ_MP02_3,   TP_BG,         0},
{INJ_MP03_3,   TP_BG,         0},
{INJ_MP04_3,   TP_BG,         0},
{INJ_MP05_3,   TP_BG,         0},
{INJ_MP06_3,   TP_BG,         0},
{INJ_MP07_3,   TP_BG,         0},
{INJ_MP08_3,   TP_BG,         0},
{INJ_MP09_3,   TP_BG,         0},
{INJ_MP10_3,   TP_BG,         0},
{INJ_MP01_4,   TP_BG,         0},
{INJ_MP02_4,   TP_BG,         0},
{INJ_MP03_4,   TP_BG,         0},
{INJ_MP04_4,   TP_BG,         0},
{INJ_MP05_4,   TP_BG,         0},
{INJ_MP06_4,   TP_BG,         0},
{INJ_MP07_4,   TP_BG,         0},
{INJ_MP08_4,   TP_BG,         0},
{INJ_MP09_4,   TP_BG,         0},
{INJ_MP10_4,   TP_BG,         0},
{INJ_MP01_5,   TP_BG,         0},
{INJ_MP02_5,   TP_BG,         0},
{INJ_MP03_5,   TP_BG,         0},
{INJ_MP04_5,   TP_BG,         0},
{INJ_MP05_5,   TP_BG,         0},
{INJ_MP06_5,   TP_BG,         0},
{INJ_MP07_5,   TP_BG,         0},
{INJ_MP08_5,   TP_BG,         0},
{INJ_MP09_5,   TP_BG,         0},
{INJ_MP10_5,   TP_BG,         0},
/* Register fuer erweiterte Schneckentabelle, Aggregat 2-5 */
{SCR_MP01_2,   TP_BG,         0},
{SCR_MP02_2,   TP_BG,         0},
{SCR_MP03_2,   TP_BG,         0},
{SCR_MP04_2,   TP_BG,         0},
{SCR_MP05_2,   TP_BG,         0},
{SCR_MP06_2,   TP_BG,         0},
{SCR_MP07_2,   TP_BG,         0},
{SCR_MP08_2,   TP_BG,         0},
{SCR_MP09_2,   TP_BG,         0},
{SCR_MP10_2,   TP_BG,         0},
{SCR_MP01_3,   TP_BG,         0},
{SCR_MP02_3,   TP_BG,         0},
{SCR_MP03_3,   TP_BG,         0},
{SCR_MP04_3,   TP_BG,         0},
{SCR_MP05_3,   TP_BG,         0},
{SCR_MP06_3,   TP_BG,         0},
{SCR_MP07_3,   TP_BG,         0},
{SCR_MP08_3,   TP_BG,         0},
{SCR_MP09_3,   TP_BG,         0},
{SCR_MP10_3,   TP_BG,         0},
{SCR_MP01_4,   TP_BG,         0},
{SCR_MP02_4,   TP_BG,         0},
{SCR_MP03_4,   TP_BG,         0},
{SCR_MP04_4,   TP_BG,         0},
{SCR_MP05_4,   TP_BG,         0},
{SCR_MP06_4,   TP_BG,         0},
{SCR_MP07_4,   TP_BG,         0},
{SCR_MP08_4,   TP_BG,         0},
{SCR_MP09_4,   TP_BG,         0},
{SCR_MP10_4,   TP_BG,         0},
{SCR_MP01_5,   TP_BG,         0},
{SCR_MP02_5,   TP_BG,         0},
{SCR_MP03_5,   TP_BG,         0},
{SCR_MP04_5,   TP_BG,         0},
{SCR_MP05_5,   TP_BG,         0},
{SCR_MP06_5,   TP_BG,         0},
{SCR_MP07_5,   TP_BG,         0},
{SCR_MP08_5,   TP_BG,         0},
{SCR_MP09_5,   TP_BG,         0},
{SCR_MP10_5,   TP_BG,         0},


/* ---------------- Register fuer 2tes Aggregat --------------------------- */
{XREG666_2,               TP_SETUP_BG,    0},
{XREG664_2,               TP_SETUP_BG,    0},
{XREG672_2,               TP_SETUP_BG,    0},
{XREG673_2,               TP_SETUP_BG,    0},
{XREG663_2,               TP_SETUP_BG,    0},
{XREG658_2,               TP_SETUP_BG,    0},
{XREG657_2,               TP_SETUP_BG,    0},
{XREG682_2,               TP_SETUP_BG,    0},
{XREG683_2,               TP_SETUP_BG,    0},
{XREG691_2,               TP_SETUP_BG,    0},
{XREG684_2,               TP_SETUP_BG,    0},
{XREG689_2,               TP_SETUP_BG,    0},
{XREG690_2,               TP_SETUP_BG,    0},
{AGGPOS_2,                TP_STD,         0},
{XMP19_2,                 TP_BG,          0},
{XMP20_22_2,              TP_STD,         0},
{XMP25_AGG2,              TP_STD,         0},
{XMP28_2,                 TP_BG,          0},
{XMP27_2,                 TP_BG,          0},
{INJHEAT_ABS_NORM_2,      TP_DSK_BG,      0},
{NR_PLAST_2,              TP_STD,         0},
{XREG775_2,               TP_DSK_BG,      PFlt_XREG775_2},
{XREG777_2,               TP_DSK_BG,      PFlt_XREG776_2},
{XREG776_2,               TP_DSK_BG,      PFlt_XREG776_2},
{XMP23_2,                 TP_BG,          0},
{XMP24_2,                 TP_BG,          0},
{XMP19_KP_2,              TP_STD,         0},
{XMP20_2,                 TP_BG,          0},
{XMP21_2,                 TP_BG,          0},
{XMP22_2,                 TP_BG,          0},
{XMP25_1_2,               TP_STD,         0},
{XMP25_2_2,               TP_STD,         0},
{XMP25_3_2,               TP_STD,         0},
{XTSPH20,                 TP_DSK_BG,      0},
{PLAST_TIME_TOL_2,        TP_DSK_BG,      0},
{INJ_TIME_TOL11,          TP_DSK_BG,      0},
{INJ_TIME_TOL12,          TP_DSK_BG,      0},
{INJ_TIME_TOL13,          TP_DSK_BG,      0},
{INJ_TIME_TOL14,          TP_DSK_BG,      0},
{INJ_TIME_TOL15,          TP_DSK_BG,      0},
{INJ_TIME_TOL16,          TP_DSK_BG,      0},
{INJ_TIME_TOL21,          TP_DSK_BG,      0},
{INJ_TIME_TOL22,          TP_DSK_BG,      0},
{INJ_TIME_TOL23,          TP_DSK_BG,      0},
{INJ_TIME_TOL24,          TP_DSK_BG,      0},
{INJ_TIME_TOL25,          TP_DSK_BG,      0},
{INJ_TIME_TOL26,          TP_DSK_BG,      0},
{SWITCH_PRES_TOL11,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL12,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL13,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL14,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL15,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL16,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL21,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL22,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL23,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL24,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL25,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_PRES_TOL26,       TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL11,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL12,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL13,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL14,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL15,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL16,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL21,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL22,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL23,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL24,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL25,      TP_DSK_BG,      PFlt_WHToVS_Soll},
{SWITCH_POINT_TOL26,      TP_DSK_BG,      PFlt_WHToVS_Soll},

#ifdef MODE_10 /*BEGIN_MODE_10*/  
   {XXTPOLSREF2,             TP_DSK_BG,      0},
   {XXTPOLSTOL2,             TP_DSK_BG,      0},
   {XXTPLASREF2,             TP_DSK_BG,      0},
   {XXTPLASTOL2,             TP_DSK_BG,      0},
   {XSSPLASREF2,             TP_DSK_BG,      0},
   {XSSPLASTOL2,             TP_DSK_BG,      0},
   {XSSINJREF2,              TP_DSK_BG,      0},
   {XSSINJTOL2,              TP_DSK_BG,      0},
   {XSTINJREF2,              TP_DSK_BG,      0},
   {XSTINJTOL2,              TP_DSK_BG,      0},
   {XSPINJREF2,              TP_DSK_BG,      0},
   {XSPINJTOL2,              TP_DSK_BG,      0},
   {XSPTINREF2,              TP_DSK_BG,      0},
   {XSPTINTOL2,              TP_DSK_BG,      0},
   {XSPTINMAXREF2,           TP_DSK_BG,      0},
   {XSPTINMAXTOL2,           TP_DSK_BG,      0},
   {XSTCYCREF2,              TP_DSK_BG,      0},
   {XSTCYCTOL2,              TP_DSK_BG,      0},
#endif /*MODE_10*/ /*END_MODE_10*/ 
{XMP16_2,                 TP_BG,          0},

{BETR_EINSPR,             TP_DSK_BG,      0},
{REIH_EINSPR,             TP_DSK_BG,      0},
{BETR_AGG_BEW,            TP_DSK_BG,      0},
{REIH_AGG_BEW,            TP_DSK_BG,      0},

/* ---------------- Register fuer Referenzwerte Trenddarstellung ---------- */
{XTSPH10_REF,             TP_DSK_BG,      0},
{XTSPH20_REF,             TP_DSK_BG,      0},
{INJ_TIME_REF11,          TP_DSK_BG,      0},
{INJ_TIME_REF12,          TP_DSK_BG,      0},
{INJ_TIME_REF13,          TP_DSK_BG,      0},
{INJ_TIME_REF14,          TP_DSK_BG,      0},
{INJ_TIME_REF15,          TP_DSK_BG,      0},
{INJ_TIME_REF16,          TP_DSK_BG,      0},
{INJ_TIME_REF21,          TP_DSK_BG,      0},
{INJ_TIME_REF22,          TP_DSK_BG,      0},
{INJ_TIME_REF23,          TP_DSK_BG,      0},
{INJ_TIME_REF24,          TP_DSK_BG,      0},
{INJ_TIME_REF25,          TP_DSK_BG,      0},
{INJ_TIME_REF26,          TP_DSK_BG,      0},
{SWITCH_PRES_REF11,       TP_DSK_BG,      0},
{SWITCH_PRES_REF12,       TP_DSK_BG,      0},
{SWITCH_PRES_REF13,       TP_DSK_BG,      0},
{SWITCH_PRES_REF14,       TP_DSK_BG,      0},
{SWITCH_PRES_REF15,       TP_DSK_BG,      0},
{SWITCH_PRES_REF16,       TP_DSK_BG,      0},
{SWITCH_PRES_REF21,       TP_DSK_BG,      0},
{SWITCH_PRES_REF22,       TP_DSK_BG,      0},
{SWITCH_PRES_REF23,       TP_DSK_BG,      0},
{SWITCH_PRES_REF24,       TP_DSK_BG,      0},
{SWITCH_PRES_REF25,       TP_DSK_BG,      0},
{SWITCH_PRES_REF26,       TP_DSK_BG,      0},
{SWITCH_POINT_REF11,      TP_DSK_BG,      0},
{SWITCH_POINT_REF12,      TP_DSK_BG,      0},
{SWITCH_POINT_REF13,      TP_DSK_BG,      0},
{SWITCH_POINT_REF14,      TP_DSK_BG,      0},
{SWITCH_POINT_REF15,      TP_DSK_BG,      0},
{SWITCH_POINT_REF16,      TP_DSK_BG,      0},
{SWITCH_POINT_REF21,      TP_DSK_BG,      0},
{SWITCH_POINT_REF22,      TP_DSK_BG,      0},
{SWITCH_POINT_REF23,      TP_DSK_BG,      0},
{SWITCH_POINT_REF24,      TP_DSK_BG,      0},
{SWITCH_POINT_REF25,      TP_DSK_BG,      0},
{SWITCH_POINT_REF26,      TP_DSK_BG,      0},
{XXTDOS1_REF,             TP_DSK_BG,      0},
{XXTDOS2_REF,             TP_DSK_BG,      0},
{XXPFINM_REF,             TP_DSK_BG,      0},
{XXPFI2M_REF,             TP_DSK_BG,      0},
{XXTZYKL_REF,             TP_DSK_BG,      0},
{XXTDOS3_REF,             TP_DSK_BG,      0},
{XXTDOS4_REF,             TP_DSK_BG,      0},
{XXPFI3M_REF,             TP_DSK_BG,      0},
{XXPFI4M_REF,             TP_DSK_BG,      0},

{TOL_SELECT_2,            TP_BG,          0},

{XMP17_2,                 TP_BG,          0},
{XMP18_2,                 TP_BG,          0},
{XMP26_2,                 TP_BG,          0},
{XMP29_2,                 TP_BG,          0},

/* ---------------- BEGIN_EWIKON ------------------------------------------ */
{XHC_MODE,                TP_STD|REG_SPECTAB,         PTabs},
{XHC_STATUS,              TP_STD|REG_SPECTAB,         PTabs},
{XHC_CURRENT_TEMP,        TP_STD|REG_SPECTAB,         PTabs},

{XHC_IST,                 TP_STD,                     PHeatChanIst},
{XHC_ABS,                 TP_STD|REG_SPECTAB,         PTabs},
{XHC_FUNCTION,            TP_STD|REG_SPECTAB,         PTabs},

{XHC_FUNCTION1,           TP_STD,         0},
{XHC_FUNCTION2,           TP_STD,         0},
{XHC_FUNCTION3,           TP_STD,         0},
{XHC_FUNCTION4,           TP_STD,         0},
{XHC_FUNCTION5,           TP_STD,         0},
{XHC_FUNCTION6,           TP_STD,         0},
{XHC_FUNCTION7,           TP_STD,         0},
{XHC_FUNCTION8,           TP_STD,         0},
{XHC_FUNCTION9,           TP_STD,         0},
{XHC_FUNCTION10,          TP_STD,         0},
{XHC_FUNCTION11,          TP_STD,         0},
{XHC_FUNCTION12,          TP_STD,         0},
{XHC_FUNCTION13,          TP_STD,         0},
{XHC_FUNCTION14,          TP_STD,         0},
{XHC_FUNCTION15,          TP_STD,         0},
{XHC_FUNCTION16,          TP_STD,         0},
{XHC_FUNCTION17,          TP_STD,         0},
{XHC_FUNCTION18,          TP_STD,         0},
{XHC_FUNCTION19,          TP_STD,         0},
{XHC_FUNCTION20,          TP_STD,         0},
{XHC_FUNCTION21,          TP_STD,         0},
{XHC_FUNCTION22,          TP_STD,         0},
{XHC_FUNCTION23,          TP_STD,         0},
{XHC_FUNCTION24,          TP_STD,         0},
{XHC_FUNCTION25,          TP_STD,         0},
{XHC_FUNCTION26,          TP_STD,         0},
{XHC_FUNCTION27,          TP_STD,         0},
{XHC_FUNCTION28,          TP_STD,         0},
{XHC_FUNCTION29,          TP_STD,         0},
{XHC_FUNCTION30,          TP_STD,         0},
{XHC_FUNCTION31,          TP_STD,         0},
{XHC_FUNCTION32,          TP_STD,         0},

#ifdef MODE_10 /*BEGIN_MODE_10*/  
   {XSPREF21,                TP_DSK_BG,      0},
   {XSPREF22,                TP_DSK_BG,      0},
   {XSPREF23,                TP_DSK_BG,      0},
   {XSPREF24,                TP_DSK_BG,      0},
   {XSPREF25,                TP_DSK_BG,      0},
   {XSPREF26,                TP_DSK_BG,      0},
   {XSPREF27,                TP_DSK_BG,      0},
   {XSPREF28,                TP_DSK_BG,      0},
   {XSPREF29,                TP_DSK_BG,      0},
   {XSPREF2A,                TP_DSK_BG,      0},
   {XSPTOL21,                TP_DSK_BG,      0},
   {XSPTOL22,                TP_DSK_BG,      0},
   {XSPTOL23,                TP_DSK_BG,      0},
   {XSPTOL24,                TP_DSK_BG,      0},
   {XSPTOL25,                TP_DSK_BG,      0},
   {XSPTOL26,                TP_DSK_BG,      0},
   {XSPTOL27,                TP_DSK_BG,      0},
   {XSPTOL28,                TP_DSK_BG,      0},
   {XSPTOL29,                TP_DSK_BG,      0},
   {XSPTOL2A,                TP_DSK_BG,      0},
#endif /*MODE_10*/ /*END_MODE_10*/ 

/* ---------------- Zusaetzliche Register Agg.3 --------------------------- */
{XREG666_3,               TP_SETUP_BG,    0},
{XREG664_3,               TP_SETUP_BG,    0},
{XREG672_3,               TP_SETUP_BG,    0},
{XREG673_3,               TP_SETUP_BG,    0},
{XREG663_3,               TP_SETUP_BG,    0},
{XREG658_3,               TP_SETUP_BG,    0},
{XREG657_3,               TP_SETUP_BG,    0},
{XREG682_3,               TP_SETUP_BG,    0},
{XREG683_3,               TP_SETUP_BG,    0},
{XREG691_3,               TP_SETUP_BG,    0},
{XREG684_3,               TP_SETUP_BG,    0},
{XREG689_3,               TP_SETUP_BG,    0},
{XREG690_3,               TP_SETUP_BG,    0},
{AGGPOS_3,                TP_STD,         0},
{XMP19_3,                 TP_BG,          0},
{XMP20_22_3,              TP_STD,         0},
{XMP25_AGG3,              TP_STD,         0},
{XMP28_3,                 TP_BG,          0},
{XMP27_3,                 TP_BG,          0},

{NR_PLAST_3,              TP_STD,         0},
{XREG775_3,               TP_DSK_BG,      PFlt_XREG775_3},
{XREG777_3,               TP_DSK_BG,      PFlt_XREG776_3},
{XREG776_3,               TP_DSK_BG,      PFlt_XREG776_3},
{XMP23_3,                 TP_BG,          0},
{XMP24_3,                 TP_BG,          0},
{XMP19_KP_3,              TP_STD,         0},
{XMP20_3,                 TP_BG,          0},
{XMP21_3,                 TP_BG,          0},
{XMP22_3,                 TP_BG,          0},
{XMP25_1_3,               TP_STD,         0},
{XMP25_2_3,               TP_STD,         0},
{XMP25_3_3,               TP_STD,         0},
{XTSPH30,                 TP_DSK_BG,      0},
{PLAST_TIME_TOL_3,        TP_DSK_BG,      0},
{XTSPH30_REF,             TP_DSK_BG,      0},
{TOL_SELECT_3,            TP_STD,         0},
{XMP17_3,                 TP_BG,          0},
{XMP18_3,                 TP_BG,          0},
{XMP26_3,                 TP_BG,          0},
{XMP29_3,                 TP_BG,          0},
{WKZINN_TOL_AGG3,         TP_DSK_BG,      0},
{SWITCH_PRES_TOL31,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL32,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL33,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL34,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL35,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL36,       TP_DSK_BG,      0},
{INJ_TIME_TOL31,          TP_DSK_BG,      0},
{INJ_TIME_TOL32,          TP_DSK_BG,      0},
{INJ_TIME_TOL33,          TP_DSK_BG,      0},
{INJ_TIME_TOL34,          TP_DSK_BG,      0},
{INJ_TIME_TOL35,          TP_DSK_BG,      0},
{INJ_TIME_TOL36,          TP_DSK_BG,      0},
{SWITCH_POINT_TOL31,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL32,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL33,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL34,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL35,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL36,      TP_DSK_BG,      0},
{SWITCH_PRES_REF31,       TP_DSK_BG,      0},
{SWITCH_PRES_REF32,       TP_DSK_BG,      0},
{SWITCH_PRES_REF33,       TP_DSK_BG,      0},
{SWITCH_PRES_REF34,       TP_DSK_BG,      0},
{SWITCH_PRES_REF35,       TP_DSK_BG,      0},
{SWITCH_PRES_REF36,       TP_DSK_BG,      0},
{INJ_TIME_REF31,          TP_DSK_BG,      0},
{INJ_TIME_REF32,          TP_DSK_BG,      0},
{INJ_TIME_REF33,          TP_DSK_BG,      0},
{INJ_TIME_REF34,          TP_DSK_BG,      0},
{INJ_TIME_REF35,          TP_DSK_BG,      0},
{INJ_TIME_REF36,          TP_DSK_BG,      0},
{SWITCH_POINT_REF31,      TP_DSK_BG,      0},
{SWITCH_POINT_REF32,      TP_DSK_BG,      0},
{SWITCH_POINT_REF33,      TP_DSK_BG,      0},
{SWITCH_POINT_REF34,      TP_DSK_BG,      0},
{SWITCH_POINT_REF35,      TP_DSK_BG,      0},
{SWITCH_POINT_REF36,      TP_DSK_BG,      0},
{FILL_TIME3,              TP_STD,         0}, /* Istwert Fuellzeit Agg.3 fuer Host     */
{DWELL_PRES3,             TP_STD,         0}, /* Istwert Nachdruckstufe Agg.3 fuer Host*/

#ifdef MODE_10 /*BEGIN_MODE_10*/  
   {XSPREF31,                TP_DSK_BG,      0},
   {XSPREF32,                TP_DSK_BG,      0},
   {XSPREF33,                TP_DSK_BG,      0},
   {XSPREF34,                TP_DSK_BG,      0},
   {XSPREF35,                TP_DSK_BG,      0},
   {XSPREF36,                TP_DSK_BG,      0},
   {XSPREF37,                TP_DSK_BG,      0},
   {XSPREF38,                TP_DSK_BG,      0},
   {XSPREF39,                TP_DSK_BG,      0},
   {XSPREF3A,                TP_DSK_BG,      0},
   {XSPTOL31,                TP_DSK_BG,      0},
   {XSPTOL32,                TP_DSK_BG,      0},
   {XSPTOL33,                TP_DSK_BG,      0},
   {XSPTOL34,                TP_DSK_BG,      0},
   {XSPTOL35,                TP_DSK_BG,      0},
   {XSPTOL36,                TP_DSK_BG,      0},
   {XSPTOL37,                TP_DSK_BG,      0},
   {XSPTOL38,                TP_DSK_BG,      0},
   {XSPTOL39,                TP_DSK_BG,      0},
   {XSPTOL3A,                TP_DSK_BG,      0},
   {XXTPOLSREF3,             TP_DSK_BG,      0},
   {XXTPOLSTOL3,             TP_DSK_BG,      0},
   {XXTPLASREF3,             TP_DSK_BG,      0},
   {XXTPLASTOL3,             TP_DSK_BG,      0},
   {XSSPLASREF3,             TP_DSK_BG,      0},
   {XSSPLASTOL3,             TP_DSK_BG,      0},
   {XSSINJREF3,              TP_DSK_BG,      0},
   {XSSINJTOL3,              TP_DSK_BG,      0},
   {XSTINJREF3,              TP_DSK_BG,      0},
   {XSTINJTOL3,              TP_DSK_BG,      0},
   {XSPINJREF3,              TP_DSK_BG,      0},
   {XSPINJTOL3,              TP_DSK_BG,      0},
   {XSPTINREF3,              TP_DSK_BG,      0},
   {XSPTINTOL3,              TP_DSK_BG,      0},
   {XSPTINMAXREF3,           TP_DSK_BG,      0},
   {XSPTINMAXTOL3,           TP_DSK_BG,      0},
   {XSTCYCREF3,              TP_DSK_BG,      0},
   {XSTCYCTOL3,              TP_DSK_BG,      0},
#endif /*MODE_10*/ /*END_MODE_10*/ 
{XMP16_3,                 TP_BG,          0},

/* ---------------- Zusaetzliche Register Agg.4 --------------------------- */
{XREG666_4,               TP_SETUP_BG,    0},
{XREG664_4,               TP_SETUP_BG,    0},
{XREG672_4,               TP_SETUP_BG,    0},
{XREG673_4,               TP_SETUP_BG,    0},
{XREG663_4,               TP_SETUP_BG,    0},
{XREG658_4,               TP_SETUP_BG,    0},
{XREG657_4,               TP_SETUP_BG,    0},
{XREG682_4,               TP_SETUP_BG,    0},
{XREG683_4,               TP_SETUP_BG,    0},
{XREG691_4,               TP_SETUP_BG,    0},
{XREG684_4,               TP_SETUP_BG,    0},
{XREG689_4,               TP_SETUP_BG,    0},
{XREG690_4,               TP_SETUP_BG,    0},
{AGGPOS_4,                TP_STD,         0},
{XMP19_4,                 TP_BG,          0},
{XMP20_22_4,              TP_STD,         0},
{XMP25_AGG4,              TP_STD,         0},
{XMP28_4,                 TP_BG,          0},
{XMP27_4,                 TP_BG,          0},

{NR_PLAST_4,              TP_STD,         0},
{XREG775_4,               TP_DSK_BG,      PFlt_XREG775_4},
{XREG777_4,               TP_DSK_BG,      PFlt_XREG776_4},
{XREG776_4,               TP_DSK_BG,      PFlt_XREG776_4},
{XMP23_4,                 TP_BG,          0},
{XMP24_4,                 TP_BG,          0},
{XMP19_KP_4,              TP_STD,         0},
{XMP20_4,                 TP_BG,          0},
{XMP21_4,                 TP_BG,          0},
{XMP22_4,                 TP_BG,          0},
{XMP25_1_4,               TP_STD,         0},
{XMP25_2_4,               TP_STD,         0},
{XMP25_3_4,               TP_STD,         0},
{XTSPH40,                 TP_DSK_BG,      0},
{PLAST_TIME_TOL_4,        TP_DSK_BG,      0},
{XTSPH40_REF,             TP_DSK_BG,      0},
{TOL_SELECT_4,            TP_STD,         0},
{XMP17_4,                 TP_BG,          0},
{XMP18_4,                 TP_BG,          0},
{XMP26_4,                 TP_BG,          0},
{XMP29_4,                 TP_BG,          0},
{WKZINN_TOL_AGG4,         TP_DSK_BG,      0},
{SWITCH_PRES_TOL41,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL42,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL43,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL44,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL45,       TP_DSK_BG,      0},
{SWITCH_PRES_TOL46,       TP_DSK_BG,      0},
{INJ_TIME_TOL41,          TP_DSK_BG,      0},
{INJ_TIME_TOL42,          TP_DSK_BG,      0},
{INJ_TIME_TOL43,          TP_DSK_BG,      0},
{INJ_TIME_TOL44,          TP_DSK_BG,      0},
{INJ_TIME_TOL45,          TP_DSK_BG,      0},
{INJ_TIME_TOL46,          TP_DSK_BG,      0},
{SWITCH_POINT_TOL41,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL42,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL43,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL44,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL45,      TP_DSK_BG,      0},
{SWITCH_POINT_TOL46,      TP_DSK_BG,      0},
{SWITCH_PRES_REF41,       TP_DSK_BG,      0},
{SWITCH_PRES_REF42,       TP_DSK_BG,      0},
{SWITCH_PRES_REF43,       TP_DSK_BG,      0},
{SWITCH_PRES_REF44,       TP_DSK_BG,      0},
{SWITCH_PRES_REF45,       TP_DSK_BG,      0},
{SWITCH_PRES_REF46,       TP_DSK_BG,      0},
{INJ_TIME_REF41,          TP_DSK_BG,      0},
{INJ_TIME_REF42,          TP_DSK_BG,      0},
{INJ_TIME_REF43,          TP_DSK_BG,      0},
{INJ_TIME_REF44,          TP_DSK_BG,      0},
{INJ_TIME_REF45,          TP_DSK_BG,      0},
{INJ_TIME_REF46,          TP_DSK_BG,      0},
{SWITCH_POINT_REF41,      TP_DSK_BG,      0},
{SWITCH_POINT_REF42,      TP_DSK_BG,      0},
{SWITCH_POINT_REF43,      TP_DSK_BG,      0},
{SWITCH_POINT_REF44,      TP_DSK_BG,      0},
{SWITCH_POINT_REF45,      TP_DSK_BG,      0},
{SWITCH_POINT_REF46,      TP_DSK_BG,      0},
{INJ_SPEED_MAX4,          TP_STD,         0},
{FILL_TIME4,              TP_STD,         0},  /* Istwert Fuellzeit Agg.4 fuer Host     */
{DWELL_PRES4,             TP_STD,         0},  /* Istwert Nachdruckstufe Agg.4 fuer Host*/
{XMP25_4_S,               TP_STD,         0},
{XMP18_4_S,               TP_STD,         0},

#ifdef MODE_10 /*BEGIN_MODE_10*/  
   {XSPREF41,                TP_DSK_BG,      0},
   {XSPREF42,                TP_DSK_BG,      0},
   {XSPREF43,                TP_DSK_BG,      0},
   {XSPREF44,                TP_DSK_BG,      0},
   {XSPREF45,                TP_DSK_BG,      0},
   {XSPREF46,                TP_DSK_BG,      0},
   {XSPREF47,                TP_DSK_BG,      0},
   {XSPREF48,                TP_DSK_BG,      0},
   {XSPREF49,                TP_DSK_BG,      0},
   {XSPREF4A,                TP_DSK_BG,      0},
   {XSPTOL41,                TP_DSK_BG,      0},
   {XSPTOL42,                TP_DSK_BG,      0},
   {XSPTOL43,                TP_DSK_BG,      0},
   {XSPTOL44,                TP_DSK_BG,      0},
   {XSPTOL45,                TP_DSK_BG,      0},
   {XSPTOL46,                TP_DSK_BG,      0},
   {XSPTOL47,                TP_DSK_BG,      0},
   {XSPTOL48,                TP_DSK_BG,      0},
   {XSPTOL49,                TP_DSK_BG,      0},
   {XSPTOL4A,                TP_DSK_BG,      0},
   {XXTPOLSREF4,             TP_DSK_BG,      0},
   {XXTPOLSTOL4,             TP_DSK_BG,      0},
   {XXTPLASREF4,             TP_DSK_BG,      0},
   {XXTPLASTOL4,             TP_DSK_BG,      0},
   {XSSPLASREF4,             TP_DSK_BG,      0},
   {XSSPLASTOL4,             TP_DSK_BG,      0},
   {XSSINJREF4,              TP_DSK_BG,      0},
   {XSSINJTOL4,              TP_DSK_BG,      0},
   {XSTINJREF4,              TP_DSK_BG,      0},
   {XSTINJTOL4,              TP_DSK_BG,      0},
   {XSPINJREF4,              TP_DSK_BG,      0},
   {XSPINJTOL4,              TP_DSK_BG,      0},
   {XSPTINREF4,              TP_DSK_BG,      0},
   {XSPTINTOL4,              TP_DSK_BG,      0},
   {XSPTINMAXREF4,           TP_DSK_BG,      0},
   {XSPTINMAXTOL4,           TP_DSK_BG,      0},
   {XSTCYCREF4,              TP_DSK_BG,      0},
   {XSTCYCTOL4,              TP_DSK_BG,      0},
#endif /*MODE_10*/ /*END_MODE_10*/ 
{XMP16_4,                 TP_BG,          0},

/* ---------------- Darstellungsreg. Weg/Volumen -------------------------- */
{AWV_PLASTWEG_IST,        TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Plastifizierweg */
{AWV_WEGPUNKT,            TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Wegpunkte */
{AWV_SRS_VORPL,           TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Schneckenrueckzug vor */
{AWV_SRS_NACHPL,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Schneckenrueckzug nach */
{AWV_SWITCH_POINT_SOLL,   TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Einspritzwege */
{AWV_PLASTWEG,            TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* IST  Plastifizierweg */
{AWV_PLASTWEG_TOL,        TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* SOLL Tol.Plastifizierweg */
{AWV_PLASTWEG_REF,        TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* REF  Plastifizierweg */
{AWV_SWITCH_POINT_IST,    TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* IST  Einspritzwege */
{AWV_SWITCH_POINT_TOL,    TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* SOLL Tol.Einspritzwege */
{AWV_SWITCH_POINT_REF,    TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* REF  Einspritzwege */
/* ---------------- Darstellungsreg. hyd./spec. --------------------------- */
{AHS_STAUDRUCK,           TP_BG|REG_SPECTAB,          PFlt_NRM_HS},  /* SOLL 1.Staudruck */
{AHS_STAUDRUCK_2,         TP_BG|REG_SPECTAB,          PFlt_NRM_HS},  /* SOLL 2.Staudruck */
{AHS_STAUDRUCK_HAND,      TP_BG|REG_SPECTAB,          PFlt_NRM_HS},  /* SOLL Staudruck-Hand */
{AHS_INJ_PRES_SOLL,       TP_BG|REG_SPECTAB,          PFlt_NRM_HS},  /* SOLL Einspritzdruck */
{AHS_SWITCH_PRES_SOLL,    TP_BG|REG_SPECTAB,          PFlt_NRM_HS_WkzInnen}, /* SOLL Umschaltdruck */
{AHS_PRES_IST,            TP_BG|REG_SPECTAB,          PFlt_NRM_HS_WkzInnen}, /* IST  Einspritzdruck */
{AHS_SWITCH_PRES_TOL,     TP_BG|REG_SPECTAB,          PFlt_NRM_HS_WkzInnen}, /* SOLL Tol.Umschaltdruck */
{AHS_SWITCH_PRES_REF,     TP_BG|REG_SPECTAB,          PFlt_NRM_HS_WkzInnen}, /* REF  Umschaltdruck */
/* ---------------- Darstellungsreg. mm/s / ccm/s bzw. 1/min / mm/s ------- */
{AWV_DREHZAHL,            TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll 1. Drehzahl */
{AWV_DREHZAHL_2,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll 2. Drehzahl */
{AWV_SRV_VORPL,           TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Rueckzuggeschw. vor Pl. */
{AWV_SRV_NACHPL,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Rueckzuggeschw. nach Pl. */
{AWV_INJ_SPEED_SOLL,      TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Einspritzgeschwindigkeiten */
/* ---------------- Darstellungsreg. mm/s / ccm/s bzw. 1/min / mm/s ------- */
/* ---------------- fuer Produktionsstart S. 40.2 ------------------------- */
{AWV_SWITCH_POINT2_SOLL,  TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Einspritzwege */
{AWV_INJ_SPEED2_SOLL,     TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Einspritzgeschwindigkeiten */
{AWV_PLASTWEG_ANFAHR,     TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll Plastifizierweg */
{AHS_INJ_PRES2_SOLL,      TP_BG|REG_SPECTAB,          PFlt_NRM_HS},     /* SOLL Einspritzdruck */
/* ---------------- Darstellungsreg. fuer erweiterte Anzahl Plastifizierstufen */
/* ---------------- Darstellungsreg. Weg/Volumen -------------------------- */
{AWV_WEGPUNKT_2,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll 2.Wegpunkte */
{AWV_WEGPUNKT_3,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll 3.Wegpunkte */
/* ---------------- Darstellungsreg. hyd./spec. --------------------------- */
{AHS_STAUDRUCK_3,         TP_BG|REG_SPECTAB,          PFlt_NRM_HS},  /* SOLL 3.Staudruck */
{AHS_STAUDRUCK_4,         TP_BG|REG_SPECTAB,          PFlt_NRM_HS},  /* SOLL 4.Staudruck */
/* ---------------- Darstellungsreg. mm/s / ccm/s bzw. 1/min / mm/s ------- */
{AWV_DREHZAHL_3,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll 3. Drehzahl */
{AWV_DREHZAHL_4,          TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},  /* Soll 4. Drehzahl */

/* ---------------- Darstellungsreg. Prozessgrafik ------------------------ */
{NRM_PG_YSCAL,            TP_BG|REG_SPECTAB,          PFlt_NRM_WV_HS},
{NRM_START_WORK,          TP_STD,         PFlt_NRM_StartWork},
{NRM_STOP_WORK,           TP_STD,         PFlt_NRM_StopWork},
{NRM_CURSOR,              TP_STD,         PFlt_NRM_Cursor},
{NRM_XVIEW,               TP_STD,         PFlt_NRM_Xview},
{NRM_MAX,                 TP_STD,         PFlt_NRM_Max},
{NRM_VALUE,               TP_STD,         PFlt_NRM_Value},
{NRM_MAXX,                TP_STD,         PFlt_NRM_Maxx},
{NRM_MAXY,                TP_STD,         PFlt_NRM_Maxy},
/* ------------------------------------------------------------------------ */
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
{XMP25_1_S,               TP_STD,          0},
{XMP25_2_S,               TP_STD,          0},
{XMP25_3_S,               TP_STD,          0},
{XMP18_1_S,               TP_STD,          0},
{XMP18_2_S,               TP_STD,          0},
{XMP18_3_S,               TP_STD,          0},
{POST_PRES_DURATION,      TP_DSK_BG,       0},     
{XDOSQU,                  TP_DSK_BG,       0},                 
{XPRTYPE,                 TP_DSK_BG,       0},
{XDOSQU_S,                TP_STD,          0},
{XPRTYPE_S,               TP_STD,          0},
/* ------------------------------------------------------------------------ */
/* ---------------- Volumen-Register fuer Weg-Volumen Umschaltung --------- */
{ICHGWAY_VOL,             TP_STD,         0},             /* Change-Reg fuer Way/Vol-Umschaltung */
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
{SSPH11_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe1 */
{SSPH12_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe2 */
{SSPH13_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe3 */
{SSPH14_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe4 */
{SSPH15_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe5 */
{SSPH21_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg2 Stufe1 */
{SSPH22_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg2 Stufe2 */
{SSPH23_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg2 Stufe3 */
{SSPH24_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg2 Stufe4 */
{SSPH25_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg2 Stufe5 */
{SSPH31_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg3 Stufe1 */
{SSPH32_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg3 Stufe2 */
{SSPH33_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg3 Stufe3 */
{SSPH34_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg3 Stufe4 */
{SSPH35_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg3 Stufe5 */
{SSPH41_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg4 Stufe1 */
{SSPH42_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg4 Stufe2 */
{SSPH43_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg4 Stufe3 */
{SSPH44_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg4 Stufe4 */
{SSPH45_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg4 Stufe5 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
{XSPH11_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg1 Stufe1 */
{XSPH12_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg1 Stufe2 */
{XSPH13_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg1 Stufe3 */
{XSPH14_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg1 Stufe4 */
{XSPH15_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg1 Stufe5 */
{XSPH21_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg2 Stufe1 */
{XSPH22_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg2 Stufe2 */
{XSPH23_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg2 Stufe3 */
{XSPH24_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg2 Stufe4 */
{XSPH25_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg2 Stufe5 */
{XSPH31_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg3 Stufe1 */
{XSPH32_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg3 Stufe2 */
{XSPH33_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg3 Stufe3 */
{XSPH34_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg3 Stufe4 */
{XSPH35_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg3 Stufe5 */
{XSPH41_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg4 Stufe1 */
{XSPH42_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg4 Stufe2 */
{XSPH43_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg4 Stufe3 */
{XSPH44_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg4 Stufe4 */
{XSPH45_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Umschaltpkt Vol Agg4 Stufe5 */
/* ---------------- Ist Polster ------------------------------------------- */
{XSPOL1_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Polster Vol Agg1 */
{XSPOL2_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Polster Vol Agg2 */
{XSPOL3_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Polster Vol Agg3 */
{XSPOL4_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Polster Vol Agg4 */
/* ---------------- Ist Plastifizierweg ----------------------------------- */
{XSPH10_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Plastifizierweg Vol Agg1 */
{XSPH20_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Plastifizierweg Vol Agg2 */
{XSPH30_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Plastifizierweg Vol Agg3 */
{XSPH40_VOL,              TP_STD,         PFlt_WayToVolIst}, /* IST Plastifizierweg Vol Agg4 */
/* ---------------- Soll Plastifizierweg ---------------------------------- */
{SSDOS1_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Plastweg Vol-Reg Agg1 */
{SSDOS2_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Plastweg Vol-Reg Agg2 */
{SSDOS3_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Plastweg Vol-Reg Agg3 */
{SSDOS4_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Plastweg Vol-Reg Agg4 */
/* ---------------- Soll Dosierwegpunkt ----------------------------------- */
{SSUM11_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg1 */
{SSUM21_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg2 */
{SSUM31_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg3 */
{SSUM41_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg4 */
/* ---------------- Soll Schneckrueckzug vor Plastifizieren --------------- */
{SRSSVOR_1_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg1 */
{SRSSVOR_2_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg2 */
{SRSSVOR_3_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg3 */
{SRSSVOR_4_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg4 */
/* ---------------- Soll Schneckrueckzug nach Plastifizieren -------------- */
{SRSSNACH_1_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg1 */
{SRSSNACH_2_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg2 */
{SRSSNACH_3_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg3 */
{SRSSNACH_4_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg4 */
/* ---------------- Soll Toleranz Plastifizierweg ------------------------- */
{XTSPH10_VOL,             TP_BG,          PFlt_VSToWH_Soll}, /* Tol Vol-Reg Agg1 */
{XTSPH20_VOL,             TP_BG,          PFlt_VSToWH_Soll}, /* Tol Vol-Reg Agg2 */
{XTSPH30_VOL,             TP_BG,          PFlt_VSToWH_Soll}, /* Tol Vol-Reg Agg3 */
{XTSPH40_VOL,             TP_BG,          PFlt_VSToWH_Soll}, /* Tol Vol-Reg Agg4 */
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
{SWITCH_POINT_TOL11_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe1 */
{SWITCH_POINT_TOL12_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe2 */
{SWITCH_POINT_TOL13_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe3 */
{SWITCH_POINT_TOL14_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe4 */
{SWITCH_POINT_TOL15_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg1 Stufe5 */
{SWITCH_POINT_TOL16_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Polster Tol Vol-Reg Agg1 */
{SWITCH_POINT_TOL21_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg2 Stufe1 */
{SWITCH_POINT_TOL22_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg2 Stufe2 */
{SWITCH_POINT_TOL23_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg2 Stufe3 */
{SWITCH_POINT_TOL24_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg2 Stufe4 */
{SWITCH_POINT_TOL25_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg2 Stufe5 */
{SWITCH_POINT_TOL26_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Polster Tol Vol-Reg Agg2 */
{SWITCH_POINT_TOL31_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg3 Stufe1 */
{SWITCH_POINT_TOL32_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg3 Stufe2 */
{SWITCH_POINT_TOL33_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg3 Stufe3 */
{SWITCH_POINT_TOL34_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg3 Stufe4 */
{SWITCH_POINT_TOL35_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg3 Stufe5 */
{SWITCH_POINT_TOL36_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Polster Tol Vol-Reg Agg3 */
{SWITCH_POINT_TOL41_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg4 Stufe1 */
{SWITCH_POINT_TOL42_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg4 Stufe2 */
{SWITCH_POINT_TOL43_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg4 Stufe3 */
{SWITCH_POINT_TOL44_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg4 Stufe4 */
{SWITCH_POINT_TOL45_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Umschaltpkt Tol Vol-Reg Agg4 Stufe5 */
{SWITCH_POINT_TOL46_VOL,  TP_BG,          PFlt_VSToWH_Soll}, /* Polster Tol Vol-Reg Agg4 */
/* ---------------- spez.-Register fuer hydr./spec. Umschaltung ----------- */
/* ---------------- Soll 1.Staudruck -------------------------------------- */
{SPST11_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 1.Staudruck Agg1 */
{SPST21_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 1.Staudruck Agg2 */
{SPST31_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 1.Staudruck Agg3 */
{SPST41_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 1.Staudruck Agg4 */
/* ---------------- Soll 2.Staudruck -------------------------------------- */
{SPST12_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 2.Staudruck Agg1 */
{SPST22_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 2.Staudruck Agg2 */
{SPST32_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 2.Staudruck Agg3 */
{SPST42_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 2.Staudruck Agg4 */
/* ---------------- Soll Staudruckhand ------------------------------------ */
{SPSTH1_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Staudruckhand Agg1 */
{SPSTH2_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Staudruckhand Agg2 */
{SPSTH3_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Staudruckhand Agg3 */
{SPSTH4_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Staudruckhand Agg4 */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
{SPPH11_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 1 */
{SPPH12_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 2 */
{SPPH13_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 3 */
{SPPH14_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 4 */
{SPPH15_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 5 */
{SPPH16_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg1 Stufe 6 */
{SPPH21_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg2 Stufe 1 */
{SPPH22_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg2 Stufe 2 */
{SPPH23_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg2 Stufe 3 */
{SPPH24_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg2 Stufe 4 */
{SPPH25_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg2 Stufe 5 */
{SPPH26_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg2 Stufe 6 */
{SPPH31_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg3 Stufe 1 */
{SPPH32_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg3 Stufe 2 */
{SPPH33_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg3 Stufe 3 */
{SPPH34_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg3 Stufe 4 */
{SPPH35_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg3 Stufe 5 */
{SPPH36_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg3 Stufe 6 */
{SPPH41_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg4 Stufe 1 */
{SPPH42_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg4 Stufe 2 */
{SPPH43_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg4 Stufe 3 */
{SPPH44_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg4 Stufe 4 */
{SPPH45_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg4 Stufe 5 */
{SPPH46_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Einspritzdruck Agg4 Stufe 6 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
{SPUM11_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 1*/
{SPUM12_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 2*/
{SPUM13_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 3*/
{SPUM14_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 4*/
{SPUM15_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg1 Stufe 5*/
{SPUM21_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg2 Stufe 1*/
{SPUM22_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg2 Stufe 2*/
{SPUM23_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg2 Stufe 3*/
{SPUM24_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg2 Stufe 4*/
{SPUM25_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg2 Stufe 5*/
{SPUM31_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg3 Stufe 1*/
{SPUM32_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg3 Stufe 2*/
{SPUM33_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg3 Stufe 3*/
{SPUM34_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg3 Stufe 4*/
{SPUM35_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg3 Stufe 5*/
{SPUM41_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg4 Stufe 1*/
{SPUM42_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg4 Stufe 2*/
{SPUM43_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg4 Stufe 3*/
{SPUM44_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg4 Stufe 4*/
{SPUM45_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Umschaltdruck Agg4 Stufe 5*/
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
{SWITCH_PRES_TOL11_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 1*/
{SWITCH_PRES_TOL12_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 2*/
{SWITCH_PRES_TOL13_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 3*/
{SWITCH_PRES_TOL14_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 4*/
{SWITCH_PRES_TOL15_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 5*/
{SWITCH_PRES_TOL16_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg1 Stufe 6*/
{SWITCH_PRES_TOL21_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg2 Stufe 1*/
{SWITCH_PRES_TOL22_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg2 Stufe 2*/
{SWITCH_PRES_TOL23_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg2 Stufe 3*/
{SWITCH_PRES_TOL24_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg2 Stufe 4*/
{SWITCH_PRES_TOL25_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg2 Stufe 5*/
{SWITCH_PRES_TOL26_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg2 Stufe 6*/
{SWITCH_PRES_TOL31_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg3 Stufe 1*/
{SWITCH_PRES_TOL32_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg3 Stufe 2*/
{SWITCH_PRES_TOL33_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg3 Stufe 3*/
{SWITCH_PRES_TOL34_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg3 Stufe 4*/
{SWITCH_PRES_TOL35_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg3 Stufe 5*/
{SWITCH_PRES_TOL36_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg3 Stufe 6*/
{SWITCH_PRES_TOL41_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg4 Stufe 1*/
{SWITCH_PRES_TOL42_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg4 Stufe 2*/
{SWITCH_PRES_TOL43_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg4 Stufe 3*/
{SWITCH_PRES_TOL44_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg4 Stufe 4*/
{SWITCH_PRES_TOL45_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg4 Stufe 5*/
{SWITCH_PRES_TOL46_SPEC,  TP_BG,          PFlt_VSToWH_Soll}, /* specifisch Tol Einspritzdr. Agg4 Stufe 6*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
{XPPH11_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 1*/
{XPPH12_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 2*/
{XPPH13_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 3*/
{XPPH14_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 4*/
{XPPH15_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 5*/
{XPPH16_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg1 Stufe 6*/
{XPPH21_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg2 Stufe 1*/
{XPPH22_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg2 Stufe 2*/
{XPPH23_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg2 Stufe 3*/
{XPPH24_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg2 Stufe 4*/
{XPPH25_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg2 Stufe 5*/
{XPPH26_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg2 Stufe 6*/
{XPPH31_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg3 Stufe 1*/
{XPPH32_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg3 Stufe 2*/
{XPPH33_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg3 Stufe 3*/
{XPPH34_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg3 Stufe 4*/
{XPPH35_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg3 Stufe 5*/
{XPPH36_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg3 Stufe 6*/
{XPPH41_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg4 Stufe 1*/
{XPPH42_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg4 Stufe 2*/
{XPPH43_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg4 Stufe 3*/
{XPPH44_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg4 Stufe 4*/
{XPPH45_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg4 Stufe 5*/
{XPPH46_SPEC,             TP_STD,         PFlt_HydrToSpecIst}, /* specifisch Einspritzdruck Agg4 Stufe 6*/
/* ---------------- Volumen-Register fuer Weg-Volumen Umschaltung (Geschw.) */
/* ---------------- Soll 1. Plastifizierdrehzahl -------------------------- */
{SWPL11_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg1 */
{SWPL21_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg2 */
{SWPL31_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg3 */
{SWPL41_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg4 */
/* ---------------- Soll 2. Plastifizierdrehzahl -------------------------- */
{SWPL12_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg1 */
{SWPL22_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg2 */
{SWPL32_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg3 */
{SWPL42_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg4 */
/* ---------------- Soll Rueckzugsgeschwindigkeit vor Pl. ----------------- */
{SRSVVOR_1_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg1 */
{SRSVVOR_2_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg2 */
{SRSVVOR_3_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg3 */
{SRSVVOR_4_VOL,           TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg4 */
/* ---------------- Soll Rueckzugsgeschwindigkeit nach Pl. ---------------- */
{SRSVNACH_1_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg1 */
{SRSVNACH_2_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg2 */
{SRSVNACH_3_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg3 */
{SRSVNACH_4_VOL,          TP_BG,          PFlt_VSToWH_Soll}, /* Geschwindigkeits-Reg Agg4 */
/* ---------------- Soll Einspritzgeschwindigkeit ------------------------- */
{SVPH11_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe1 */
{SVPH12_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe2 */
{SVPH13_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe3 */
{SVPH14_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe4 */
{SVPH15_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe5 */
{SVPH16_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe6 */
{SVPH21_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg2 Stufe1 */
{SVPH22_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg2 Stufe2 */
{SVPH23_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg2 Stufe3 */
{SVPH24_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg2 Stufe4 */
{SVPH25_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg2 Stufe5 */
{SVPH26_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg2 Stufe6 */
{SVPH31_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg3 Stufe1 */
{SVPH32_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg3 Stufe2 */
{SVPH33_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg3 Stufe3 */
{SVPH34_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg3 Stufe4 */
{SVPH35_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg3 Stufe5 */
{SVPH36_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg3 Stufe6 */
{SVPH41_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg4 Stufe1 */
{SVPH42_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg4 Stufe2 */
{SVPH43_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg4 Stufe3 */
{SVPH44_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg4 Stufe4 */
{SVPH45_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg4 Stufe5 */
{SVPH46_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg4 Stufe6 */
/* ---------------- Volumen-Register fuer Referenzwerte ------------------- */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
{SWITCH_PRES_REF11_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF12_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF13_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF14_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF15_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF16_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF21_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF22_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF23_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF24_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF25_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF26_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF31_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF32_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF33_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF34_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF35_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF36_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF41_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF42_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF43_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF44_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF45_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
{SWITCH_PRES_REF46_SPEC,  TP_BG,          PFlt_HydrToSpecIst},
/* ---------------- REF Umschaltpunkte ------------------------------------ */
{SWITCH_POINT_REF11_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF12_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF13_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF14_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF15_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF16_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF21_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF22_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF23_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF24_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF25_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF26_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF31_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF32_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF33_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF34_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF35_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF36_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF41_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF42_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF43_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF44_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF45_VOL,  TP_BG,          PFlt_WayToVolIst},
{SWITCH_POINT_REF46_VOL,  TP_BG,          PFlt_WayToVolIst},
/* ---------------- REF Plastifizierwege ---------------------------------- */
{XTSPH10_REF_VOL,         TP_BG,          PFlt_WayToVolIst},
{XTSPH20_REF_VOL,         TP_BG,          PFlt_WayToVolIst},
{XTSPH30_REF_VOL,         TP_BG,          PFlt_WayToVolIst},
{XTSPH40_REF_VOL,         TP_BG,          PFlt_WayToVolIst},
/* ------------------------------------------------------------------------ */
{PG_YSCAL_VOLSPEC,        TP_STD|REG_SPECTAB,         PTabs},
{PG_YSCAL_VOLSPEC01,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC02,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC03,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC04,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC05,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC06,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC07,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC08,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC09,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC10,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC11,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC12,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC13,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC14,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC15,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC16,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC17,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC18,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC19,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC20,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC21,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC22,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC23,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC24,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC25,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC26,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC27,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC28,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC29,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC30,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC31,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC32,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC33,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC34,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC35,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC36,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC37,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC38,      TP_BG,          PFlt_VSToWH_Soll},
{PG_YSCAL_VOLSPEC39,      TP_BG,          PFlt_VSToWH_Soll},

/* ---------------- Erweiterung fuer 4 Plastifizierstufen ----------------- */
/* ---------------- Soll 2.Plastifizierwegpunkt --------------------------- */
{SSUM12_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg1 */
{SSUM22_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg2 */
{SSUM32_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg3 */
{SSUM42_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg4 */
/* ---------------- Soll 3.Plastifizierwegpunkt --------------------------- */
{SSUM13_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg1 */
{SSUM23_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg2 */
{SSUM33_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg3 */
{SSUM43_VOL,              TP_BG,          PFlt_VSToWH_Soll}, /* Vol-Reg Agg4 */
/* ---------------- Soll 3. Plastifizierdrehzahl -------------------------- */
{SWPL13_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg1 */
{SWPL23_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg2 */
{SWPL33_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg3 */
{SWPL43_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg4 */
/* ---------------- Soll 4. Plastifizierdrehzahl -------------------------- */
{SWPL14_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg1 */
{SWPL24_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg2 */
{SWPL34_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg3 */
{SWPL44_VOL,              TP_BG,          PFlt_DvToDnSoll}, /* Geschwindigkeits-Reg Agg4 */
/* ---------------- Soll 3.Staudruck -------------------------------------- */
{SPST13_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 3.Staudruck Agg1 */
{SPST23_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 3.Staudruck Agg2 */
{SPST33_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 3.Staudruck Agg3 */
{SPST43_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 3.Staudruck Agg4 */
/* ---------------- Soll 4.Staudruck -------------------------------------- */
{SPST14_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 4.Staudruck Agg1 */
{SPST24_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 4.Staudruck Agg2 */
{SPST34_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 4.Staudruck Agg3 */
{SPST44_SPEC,             TP_BG,          PFlt_VSToWH_Soll}, /* specifisch 4.Staudruck Agg4 */

#ifdef MODE_10 /*BEGIN_MODE_10*/  
   /* ---------------- Toleranz-und Referenzregister Agg.1 ------------------ */
   {XSPREF11,                TP_DSK_BG,      0},
   {XSPREF12,                TP_DSK_BG,      0},
   {XSPREF13,                TP_DSK_BG,      0},
   {XSPREF14,                TP_DSK_BG,      0},
   {XSPREF15,                TP_DSK_BG,      0},
   {XSPREF16,                TP_DSK_BG,      0},
   {XSPREF17,                TP_DSK_BG,      0},
   {XSPREF18,                TP_DSK_BG,      0},
   {XSPREF19,                TP_DSK_BG,      0},
   {XSPREF1A,                TP_DSK_BG,      0},
   {XSPTOL11,                TP_DSK_BG,      0},
   {XSPTOL12,                TP_DSK_BG,      0},
   {XSPTOL13,                TP_DSK_BG,      0},
   {XSPTOL14,                TP_DSK_BG,      0},
   {XSPTOL15,                TP_DSK_BG,      0},
   {XSPTOL16,                TP_DSK_BG,      0},
   {XSPTOL17,                TP_DSK_BG,      0},
   {XSPTOL18,                TP_DSK_BG,      0},
   {XSPTOL19,                TP_DSK_BG,      0},
   {XSPTOL1A,                TP_DSK_BG,      0},
   {XXTPOLSREF1,             TP_DSK_BG,      0},
   {XXTPOLSTOL1,             TP_DSK_BG,      0},
   {XXTPLASREF1,             TP_DSK_BG,      0},
   {XXTPLASTOL1,             TP_DSK_BG,      0},
   {XSSPLASREF1,             TP_DSK_BG,      0},
   {XSSPLASTOL1,             TP_DSK_BG,      0},
   {XSSINJREF1,              TP_DSK_BG,      0},
   {XSSINJTOL1,              TP_DSK_BG,      0},
   {XSTINJREF1,              TP_DSK_BG,      0},
   {XSTINJTOL1,              TP_DSK_BG,      0},
   {XSPINJREF1,              TP_DSK_BG,      0},
   {XSPINJTOL1,              TP_DSK_BG,      0},
   {XSPTINREF1,              TP_DSK_BG,      0},
   {XSPTINTOL1,              TP_DSK_BG,      0},
   {XSPTINMAXREF1,           TP_DSK_BG,      0},
   {XSPTINMAXTOL1,           TP_DSK_BG,      0},
   {XSTCYCREF1,              TP_DSK_BG,      0},
   {XSTCYCTOL1,              TP_DSK_BG,      0},
#endif /*MODE_10*/ /*END_MODE_10*/ 
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
{ACT_DIAGSYSTYP,          TP_STD,         0},
{ACT_DIAGBUSNR,           TP_STD,         0},
{ACT_DIAGMODNR,           TP_STD,         0},
{ACT_DIAGINDTAB,          TP_STD,         0},
{ACT_DIAGMODULTYP,        TP_STD,         PFlt_DMView},
/* ---------------- Dummy-Register fuer indizierten Text (Weg/Volumen) ---- */
{AWV_ANZ_PLAST_STUF,      TP_BG,          PFlt_WayVol_PLIndName},
/* ---------------- Prozessgraphik Register ------------------------------- */
{NOOF_AGGREGATES,         TP_STD,         0},
{CURVE_NO,                TP_STD,         0},
{PGCONFIG,                TP_INT20,       0},
{STDCURV1,                TP_STD,         0},
{STDCURV2,                TP_STD,         0},

{XPG_SOLLIST1,            TP_INT10_PGDSK, 0},
{XPG_SOLLIST2,            TP_INT10_PGDSK, 0},

{XPG_CURSOR,              TP_STD,         PPGCursor },            /* Cursor */
/* ---------------- Index: Clipboard ID; left/right ----------------------- */
{XPG_XVIEW,               TP_STD,         PPGXView }, /* x_Darstellungsbereich */
/* ---------------- Index: Clipboard ID; left/right ----------------------- */
{XPG_MAX,                 TP_STD,         PPGMax },        /* Kurvenmaximum */
/* ---------------- Index: Clipboard ID; Clipboard Kurvenindex ------------ */
{XPG_VALUE,               TP_STD,         PPGValue }, /* Kurvenwerte bei Cursorposition */
/* ---------------- Index: Clipboard ID; Clipboard Kurvenindex; left/right  */
{XPG_SI1,                 TP_STD,         0 }, /* fuer Soll/Ist Vergleich */
{XPG_SI2,                 TP_STD,         0 }, /* fuer Soll/ist Vergleich */
{PHASEINJTIME,            TP_STD,         PPhaseInjTime}, /* (Teil-)Summe der Einspritzzeiten ueber die Einspritzphasen */
{PG_ACK_INFO,             TP_STD,         PPGInfo },
{PG_CURVE_INFO,           TP_STD,         PPGInfo },
{PG_ACK_INFO_DIRECT,      TP_STD,         PPGInfo },
{PG_CURVE_INFO_DIRECT,    TP_STD,         PPGInfo },
{PG_NR_ACT_CURVES,        TP_STD,			PPGActCurves }, /* Anzahl gespeicherter Istkurven */

{ ICO_ident, REG_INT, PFlt_ident},
{ ICO_number, REG_INT, PFlt_number},
{ ICO_info, REG_INT, PFlt_info},
{ ICO_p, REG_INT, PFlt_p},
{ ICO_v, REG_INT, PFlt_v},
{ ICO_s1, REG_INT, PFlt_s1},
{ ICO_tA, REG_INT, PFlt_tA},
{ ICO_tV, REG_INT, PFlt_tV},
{ ICO_s2, REG_INT, PFlt_s2},
{ ICO_M, REG_INT, PFlt_M},
{ ICO_tR, REG_INT, PFlt_tR},
{ ICO_s3, REG_INT, PFlt_s3},
{ ICO_S, REG_INT, PFlt_S},
{ ICO_L, REG_INT, PFlt_L},
{ ICO_Startconds, REG_INT, PFlt_Startconds},
{ ICO_Movements, REG_INT, PFlt_Movements},
{ ICO_Options, REG_INT, PFlt_Options},
{ ICO_lineno, REG_INT, PFlt_lineno},
{ ICO_StartcondText, REG_INT, PFlt_StartcondText},
{ ICO_MovementText, REG_INT, PFlt_MovementText},
{ ICO_OptionText, REG_INT, PFlt_OptionText},
{ ICO_MaxToolStroke, REG_INT, PFlt_MaxToolStroke},

{ ICOINIPOS, REG_INT, PFltINIPOS},
{ ICOENDPOS, REG_INT, PFltENDPOS},

{ ICOPROGLINE0, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE1, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE2, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE3, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE4, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE5, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE6, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE7, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE8, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE9, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE10, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE11, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE12, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE13, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE14, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE15, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE16, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE17, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE18, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE19, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE20, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE21, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE22, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE23, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE24, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE25, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE26, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE27, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE28, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE29, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE30, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE31, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE32, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE33, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE34, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE35, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE36, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE37, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE38, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE39, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE40, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE41, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE42, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE43, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE44, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE45, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE46, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE47, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE48, REG_INT20|REG_DISK_CORE|REG_BG, 0},
{ ICOPROGLINE49, REG_INT20|REG_DISK_CORE|REG_BG, 0},

{DUES_WAHL_SPEC,          TP_STD,            0},  /* aktuell ausgewaehlte Duese S. 48 */

/* Register für den Kartenleser */
{ACCCARD_NEW_KEYCODE,   REG_INT, 0},                              /* MEMCARD */

/*  Register für Anzahl Spritzstufen aus dem KProm */
{MAX_INJCYC                   , REG_INT,  0}, /* */

/* ---------------- Soll Einspritzgeschwindigkeit fuer Anfahrzyklen ----------------- */
{SVPH11A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe1 */
{SVPH12A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe2 */
{SVPH13A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe3 */
{SVPH14A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe4 */
{SVPH15A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe5 */
{SVPH16A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe6 */
{SVPH17A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe7 */
{SVPH18A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe8 */
{SVPH19A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzges. Agg1 Stufe9 */
/* ---------------- Soll Umschaltpunkt fuer Anfahrzyklen ---------------------------- */
{SSPH11A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe1 */
{SSPH12A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe2 */
{SSPH13A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe3 */
{SSPH14A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe4 */
{SSPH15A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe5 */
{SSPH16A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe6 */
{SSPH17A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe7 */
{SSPH18A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe8 */
{SSPH19A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Umschaltpkt Vol Agg1 Stufe9 */
/* ---------------- Soll Plastifizierweg fuer Anfahrzyklen -------------------------- */
{SSDOS1A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Plastweg Vol-Reg Agg1 */
/* ---------------- Soll Einspritzdruck fuer Anfahrzyklen --------------------------- */
{SPPH11A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe1 */
{SPPH12A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe2 */
{SPPH13A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe3 */
{SPPH14A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe4 */
{SPPH15A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe5 */
{SPPH16A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe6 */
{SPPH17A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe7 */
{SPPH18A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe8 */
{SPPH19A_VOL,    TP_BG,          PFlt_VSToWH_Soll}, /* Soll Einspritzdruck Vol Agg1 Stufe9 */

{0xffff} /* ENDEKENNUNG: muss IMMER da sein */
};
