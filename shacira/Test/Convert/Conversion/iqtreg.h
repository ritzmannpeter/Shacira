/****************************************************************************
*
*
*         IQTREG.H
*
*
*  HISTORY:
*     05.12.89 -SF-     Neue Struktur der Include-Files eingebaut
*     02.04.90 -TSchw-  BDECycleInt eingefuehrt
*     05.07.90 -TSchw-  EXT_COUNT_MAX und _ACT eingefuehrt
*     14.07.90 -TSchw-  AGGPOS bis XMP25_3 eingefuehrt
*     24.09.90 -TSchw-  XSSFZU_SHOW eingefuehrt
*     07.12.90 -TSchw-  PG_OPMODE_SOLL eingefuehrt
*     11.12.90 -SF-     Roboter-Register eingefuehrt
*      6.02.91 -SF-     SPCUSG/OSG ersetzt durch SPCUSG/OSGcm und
*                       SPCUSG/OSGcp eingebaut
*     28.02.91 -TSchw-  Register fuer Heizungs-Selbstoptimierung eingebaut
*     13.05.91 -MB-     Register fuer Aggregat 2 eingefuehrt      
*                       Register fuer Seite 44 definiert
*                       SPRITZ_WAHL, BETR_EINSPR, REIH_EINSPR
*                       folgende Register neu implementiert:
*                       XTSPH20, PLAST_TIME_TOL_2
*                       SWITCH_PRES_TOL, INJ_TIME_TOL, SWITCH_POINT_TOL
*                       neu definiert fuer Aggregat 2:            
*                       SWITCH_PRES_REF, INJ_TIME_REF,            
*                       SWITCH_POINT_REF, XTSPH20_REF             
*                       TOL_SELECT_2 definiert
*     24.05.91 -SF-     XMP17_2 eingefuehrt
*     03.06.91 -TSchw-  MAX_INJUNITS eingefuehrt
*     06.06.91 -TSchw-  INJ_SPEED_MAX, INJ_SPEED_CONV eingefuehrt
*     24.06.91 -TSchw-  INJ_SPEED_MAX1, 2, 3, _CONV1, 2, 3 eingefuehrt
*     25.06.91 -TSchw-  AGGREGAT0 eingefuegt
*     19.11.91 -PR-     Zusaetzliche Register fuer 10-Stufen-Spritzverfahren
*                       definiert
*     03.12.91 -TSchw-  WCLOCK_EXT1_SWITCH und WCLOCK_EXT2_SWITCH einge-
*                       fuegt; diese beiden Register waren frueher
*                       Iqtbits
*     09.12.91 -SF-     xxxAggregatTab / xxxStationTab in xxxRegInd1 / 2 
*                       geaendert und xxRegInd3 eingefuehrt
*                       REG_FOT_PAGE_x eingefuegt
*     11.12.91 -TSchw-  XSNWKZS definiert fuer alle Maschinentypen;
*                       damit entfaellt die bisherige Spezialdefinition
*                       in der FXA
*     18.12.91 -TSchw-  XSSAUS3_INVERS eingefuegt fuer Mangel 137
*     27.01.92 -TSchw-  XMP18_2 eingefuehrt
*     30.01.92 -TSchw-  XMP26_2 und XMP29_2 neu eingefuehrt
*     04.02.92 -TSchw-  WKZ_CODE neu erstellt fuer Host
*     04.02.92 -TSchw-  EJECT_HASCO neu erstellt fuer Mangel 180
*     21.02.92 -PR-     EWIKON-Nummern eingefuehrt
*     24.02.92 -TSchw-  PG_XNADD eingefuegt
*     18.09.92 -TSchw-  WKZINN_TOL_AGG2 eingefuegt
*     29.09.92 -SF-     SPC,BDE und AxisAggregat eingefuehrt
*     17.11.92 -TSchw-  DWELL_PRES1/2 eingefuegt, Wunsch Kury
*     03.12.92 -TSchw-  WCLOCK_MOTOR_SWITCH und WCLOCK_HEAT_SWITCH einge-
*                       fuegt; diese beiden Register waren frueher
*                       Iqtbits
*     08.02.94 -TSchw-  XPOJSS, XPOJES eingefuegt fuer Leitrechner,
*                       ebenso HOST_START_ORDER, HOST_STOP_ORDER,
*                       HOST_CANCEL_ORDER, HOST_REJECTS, HOST_GOOD_PARTS,
*                       FILL_TIME1/2
*     16.02.94 -TSchw-  XNUL-Register eingefuegt als Muelleimer
*     26.07.93 -TSchw-  PRINT_PAGE_AGGREGAT eingefuegt
*     28.07.93 -TSchw-  XSWEG_FIXSHOW eingefuegt als Kurzspeicheranzeige
*                       fuer den Auswerferweg S.52; der groesste Wert
*                       des schnellen Iscosregisters XXSWEG4_SHOW wird
*                       darin fuer ca. 2 Sekunden festgehalten.
*     16.09.93 -TSchw-  BDEStopTimeType eingefuehrt, um den Typ der
*                       Stillstandsmeldungen zu definieren:
*                       Bit=0 - normal, Bit=1 - erweiterter Stillstand
*                       Bit 0 - Stillstand Zeile 4 S.24, Bit 16 - Zeile 19
*     16.02.95 -Tschw-  Fuer Leitrechner: HOST_AGGREGAT und 
*                       HOST_ACT_REGLER_NR eingefuegt fuer alle
*                       Maschinentypen
*     17.05.95 -TSchw-  Folgende Register neu eingefuegt zur Abspeicherung
*                       der Referenzistwerte auf dem Datentraeger;
*                       Forderung Rietsche, Gehring:
*                       XXTDOS1_REF, XXTDOS2_REF, XXPFINM_REF, 
*                       XXPFI2M_REF, XXTZYKL_REF 
*     18.01.96 -HAns-   STDCURV1 und STDCURV2 eingefuegt
*                       Register fuer Seite 44 definiert (KD2F)
*                       BETR_AGG_BEW, REIH_AGG_BEW
*     26.01.96 -HAns-   Register fuer 3.Agg (23000 - 23117) und 
*                       4.Agg (23200 - 23320) sowie 2.Agg (22071 - 22088)
*                       eingefuegt
*     29.01.96 -HAns-   INJ_SPEED_CONV4 eingefuegt.
*                       Register fuer 2.Agg (22900 - 22919) eingefuegt.
*     16.02.96 -HAns-   XSPS_HVER bis XDM_BUGFIX eingefuegt.
*     29.02.96 -HAns-   Folgende Register neu eingefuegt zur Abspeicherung
*                       der Referenzistwerte auf dem Datentraeger;
*                       Forderung Rietsche, Gehring:
*                       XXTDOS3_REF, XXTDOS4_REF, XXPFI3M_REF, XXPFI4M_REF
*     21.03.96 -HAns-   XPG_SI1,2 und XPG_SOLLIST3,4 fuer Prozessgrafik 
*                       Mehrfarben eingefuegt.
*     16.04.96 -HAns-   XZEITAN4_2,3,4 , XZEITAN5_2,3,4 , XZEITAN6_2,3,4
*                       XZEITANAVER4_2,3,4 , XZEITANAVER5_2,3,4 und 
*                       XZEITANAVER6_2,3,4 eingefuegt.
*     15.05.96 -HAns-   ISRSSVOR eingefuegt.
*     13-09-96 -PR-     IQT-Register-Nummern fuer frei progr.bare Kernzuege (ICO..).
*     26.09.96 -HAns-   ISVPH11 - ISVPH15, ISVPH21 - ISVPH25,
*                       ISVPH31 - ISVPH35, ISVPH41 - ISVPH45 eingefuegt.
*     27.09.96 -HAns-   ICHGWAY_VOL
*     30.09.96 -HAns-   ISVDOS1 bis ISRSVOLNACH4 (Seite 40.0) eingefuegt.
*		04.11.96 -TSchw-  Weg-/Volumenregister eingefuehrt zum indizierten
*                       Zugriff auf Weg und Volumen (siehe AWV_)
*		15.11.96 -HAns-   AWV_PLASTWEG_TOL und AWV_SWITCH_POINT_TOL eingefuegt.
*		                  XTSPH11 - XTSPH15 und XTSPOL1 herausgenommen, da diese
*                       nicht mehr benutzt werden.
*                       ITVPH10, ITVPH20, ITVPH30 und ITVPH40 eingefuegt.
*                       SWITCH_VOL_UMP_TOL11-16, SWITCH_VOL_UMP_TOL21-26,
*                       SWITCH_VOL_UMP_TOL31-36, SWITCH_VOL_UMP_TOL41-46 eingefuegt.
*		18.11.96 -HAns-   IXVPH11 - IXVPOL4 eingefuegt.
*                       AWV_PLASTWEG und AWV_SWITCH_POINT_IST eingefuegt.
*                       IXVPH10 - IXVPH40 eingefuegt.
*		29.11.96 -HAns-   AHS_STAUDRUCK, AHS_STAUDRUCK_2, AHS_STAUDRUCK_HAND
*								AHS_INJ_PRES_SOLL, AHS_SWITCH_PRES_SOLL, AHS_PRES_IST,
*								und AHS_SWITCH_PRES_TOL eingefuegt.
*     02.12.96 -PR-     Registernummern fuer darstellungsunabhaengige
*                       Prozessgrafikregister eingefuehrt.
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
*                       SWITCH_PRES_REF11_SPEC bis SWITCH_PRES_REF46_SPEC,
*                       SWITCH_POINT_REF11_VOL bis SWITCH_POINT_REF11_VOL und
*                       XTSPH10_REF_VOL bis XTSPH40_REF_VOL eingefuegt.
*     17.02.97 -HAns-   PG_YSCAL_VOLSPEC bis PG_YSCAL_VOLSPEC39 und NRM_PG_YSCAL eingefuegt.
*                       AWV_ -Register und NRM_-Register verlegt.
*     13.03.97 -PR-     Registernummer ICO_MaxToolStroke eingefuehrt
*     21.11.97 -HAns-   ACT_DIAGSYSTYP bis ACT_DIAGMODTYP,ACT_DIAGMODULTYP
*                       fuer freiauswaehlbare Diagnoseseite eingefuegt.
*     08.12.97 -HAns-   ACT_DIAGMODTYP in ACT_DIAGINDTAB unbenannt.
*     07.01.98 -GhG-    AWV_ANZ_PLAST_STUF eingefuegt.
*     08.06.98 -HAns-   Register fuer 9 Einspritzstufen 
*                       (SPPH17_SPEC bis SWITCH_POINT_REF19_VOL) eingefuegt.
*     08.09.98 -HAns-   SELECT_PROCESS_STEPS bis PROC_STEP_UNIT4 fuer
*                       Toleranzueberwachugn: Auswahl der Prozessschritte eingefuegt.
*     21.09.98 -GhG-    DUES_WAHL_SPEC eingefuegt fuer S. 48                                                               
*     29.10.98 -HAns-   TRENDVARIND1 bis 10 eingefuegt.
*     04.11.98 -HAns-   TRENDVARSTART und TRENDVAREND eingefuegt.
*		07.04.99 -TSchw-  PG_NR_ACT_CURVES eingefuegt.
*     04.10.99 -GhG-    PLgs_Umschaltpunkt eingefuegt fuer CD-Maschine 
*     17.01.00 -HAns-   IVENTIL_IND bis IMAS_VERS2 aufgenommen.
*		02.02.00 -HAns-   Register fuer 5/6-Farben eingefuegt.
*     06.03.00 -TSchw-  ACT_SYSPRINTER eingefuegt fuer SYSPRN
*     27.04.00 -TSchw-  Register fuer Abnahmeprotokoll (AP_...) eingefuegt
*     02.05.00 -HAns-   BTCOUNTER_IST_MM und BTCOUNTER_SOLL_HH eingefuegt fuer Betriebsstundenzaehler
*     15.03.00 -HAns-   XMP16_2 bis 6 aufgenommen.
*                       MAX_SE1_WEG bis MAX_SE2_WEG aufgenommen.
*     06.12.00 -HAns-   WOISAKTUEL_TOL,REF und AWISAKTUEL_TOL,REF aufgenommen.
*     12.12.00 -TSchw-  Namenänderung (x = 1,2,3):
*                       AP_SWGx_TOLLOW_ZEIT  -> AP_SWGx_TOLLOW_ZEIT_OEFF
*                       AP_SWGx_TOLHIGH_ZEIT -> AP_SWGx_TOLHIGH_ZEIT_OEFF    
*                       AP_SWGx_REF_ZEIT     -> AP_SWGx_REF_ZEIT_OEFF
*                       Neue Register (x = 1,2,3):
*                       AP_SWGx_TOLLOW_ZEIT_SCHL
*                       AP_SWGx_TOLHIGH_ZEIT_SCHL    
*                       AP_SWGx_REF_ZEIT_SCHL
*                       AP_SV14_V14_MESS
*                       AP_ED100_IQT
*                       AP_ED100_MAX_MESS
*                       AP_ED100_MAX_TOL
*                       AP_DAKRAFT_IQT
*                       AP_DAKRAFT_MESS
*                       AP_DAKRAFT_TOL
*                       AP_SCHLKRAFT_MAX_DRUCK_REF
*                       AP_AGx_S52_DRUCK_VOR
*                       AP_AGx_S52_DRUCK_ZURUECK
*                       Geänderte Registernummern (geht nicht auf Datenträger):
*                       AP_WKZOFFNW_MAX_IQT
*                       AP_WKZOFFNW_MAX_MESS
*                       AP_WKZOFFNW_MAX_TOL
*     13.11.00 -TSchw-  ACCCARD_NEW_KEYCODE eingefuegt (siehe MEMCARD)
*     26.01.01 -TSchw-  AP_ED100_EINRICHTDRUCK neu eingefuegt
*                       AP_TEST_ACTIVE neu eingefuegt
*     12.02.01 -HAns-   HOST-DUMMY eingefuegt.
*     23.02.01 -GhG-    MAX_INJCYC aufgenommen
*     13.03.01 -GhG-    AWV_SWITCH_POINT2_SOLL, AWV_INJ_SPEED2_SOLL fuer
*                       Produktionsstart Weg-/Volumenumschaltung S 40.2
*     05.04.01 -HAns-   AP_AG1_S52_V4 fuer Test1, 2, 3 eingefuegt
*     06.04.01 -JG-     AP_AGx_S52_DRUCK_VOR2 und AP_AGx_S52_DRUCK_ZURUECK2
*                       für Test 1 , 2 ,3 eingefügt
*     25.09.01 -HA-     MLD_MP01 bis MLD_MP10, INJ_MP01 bis INJ_MP10 und SCR_MP01 bis SCR_MP10
*                       sowie INJ_MP01_2 bis INJ_MP10_5 und SCR_MP01_2 bis SCR_MP10_5 eingefuegt.^
*     05.10.01 -HA-     AWV_WEGPUNKT_2, AWV_WEGPUNKT_3, AHS_STAUDRUCK_3, AHS_STAUDRUCK_4, AWV_DREHZAHL_3
*                       und AWV_DREHZAHL_4 eingefuegt.
*                       SSUM12_VOL bis SPST44_SPEC eingefuegt.
*     15.10.01 -HA-     IPLASTSTUFE eingefuegt.
*     29.10.01 -HA-     SPPH1A_SPEC bis SWITCH_POINT_REF1C_VOL eingefuegt.
*     20.11.01 -HA-     IVENTIL_NR, IVENTIL_OFF1, IVENTIL_VERS1, IVENTIL_OFF2 und IVENTIL_VERS2 eingefuegt.
*                       IMAX_VENTIL eingefuegt.
*     17.12.01 -HA-     IZEITAND und IZEITANAVERD eingefuegt.
*     12.06.02 -HA-     APST_TOL1 bis APST_TOL4, APIT_REF1 bis APIT_REF4 eingefuegt.
*     13.06.02 -HA-     PSHOT_COUNTER eingefuegt.
*     13.08.02 -HA-     SCR_MP01_6 bis SCR_MP10_6 und INJ_MP02_6 bis INJ_MP10_6
*     05.02.03 -HA-     AWV_PLASTWEG_ANFAHR und SSDSOS1A_VOL eingefuegt.
*     10.03.03 -HA-     AHS_INJ_PRES2_SOLL eingefuegt
*                       SPPH11A_VOL - SPPH19A_VOL eingefuegt
*     23.07.03 -HA-     Register fuer 7-12 Einspritzstufen des 2.Aggregats 
*                       (SPPH17_SPEC bis SWITCH_POINT_REF1C_VOL) eingefuegt.
*                       SVPH21A_VOL bis SPPH29A_VOL eingefuegt.
*
****************************************************************************/

#ifndef _iqtreg
#define _iqtreg

/* ------------------------------------------------------------------------- *
 |  Definitons fur die Registernummern der IQT-Register                      |
 |  IQT-Registernummern bewegen sich im Bereich zwischen 20000 und 29999     |
 |                                                                           |
 |  Wenn _USE_NOT_KLOECK_IQTREG gesetzt ist, werden die von Klockner         |
 |  definierten Iqtbits nicht eingebunden.                                   |
 * ------------------------------------------------------------------------- */


#define XCUSWTL  20001    /* customer switch   least */
#define XCUSWTM  20002    /* customer switch   most  */
#define XBODUMMY 20003    /* Hilfsregister Druckbolzen  */
#define IDHOEHE  20004    /* Druckbolzen Hoehenverstellung  */
#define XNUL     20005    /* nul-Register, was hier hineingeschrieben wird, */
                          /* ist auf ewig verloren.                         */
#define XMAXFAUF 20185
#define XIQWEG2  20186    /* copy of xsweg2    */
#define XFORMZU  20187    /* xsweg2 nach Formhoehenabgleich (Hilfsregister) */
#define XITKUHL  20188    /* register kuehlzeit      */
#define XSNWKZS  20189    /* Seite 80 Zeile 16 "Lichtschranke/Ausfallwaage" */
#define HOST_DUMMY 20190  /* HOST-DUMMY fuer hosttab.c, darf sonst nirgends verwendet werden */

#define XMP02    20243      /* Maschinenparameter      */
#define XMP03    20244
#define XMP04    20245
#define XMP05    20246
#define XMP06    20247
#define XMP07    20248
#define XMP08    20249
#define XMP09    20250
#define XMP10    20251
#define XMP11    20252
#define XMP12    20253
#define XMP13    20254
#define XMP14    20255
#define XMP15    20256
#define XMP16    20257
#define XMP17    20258
#define XMP18    20259
#define XMP19    20260
#define XMP20    20261
#define XMP21    20262
#define XMP22    20263
#define XMP23    20264
#define XMP24    20265
#define XMP25    20266
#define XMP26    20267
#define XMP27    20268
#define XMP28    20269
#define XMP29    20270
#define XMP30    20271
#define XMP31    20272
#define XMP32    20273
#define XTABWKZ  20274    /* Temperaturabsenkung WKZ */
#define AGGPOS   20275    /* Spritzzylinder auf Position */
#define XMP19_KP 20276    /* Speicher fuer KP19          */
#define XMP20_22 20277    /* akt. Wert von MP20 - MP22   */
#define XMP25_1  20278    /* MP25 aus Schneckentabelle 1 */
#define XMP25_2  20279    /* MP25 aus Schneckentabelle 2 */
#define XMP25_3  20280    /* MP25 aus Schneckentabelle 3 */
/* Register fuer erweiterte Werkzeug, Aggregat und Schneckentabelle */
#define MLD_MP01 20281
#define MLD_MP02 20282
#define MLD_MP03 20283
#define MLD_MP04 20284
#define MLD_MP05 20285
#define MLD_MP06 20286
#define MLD_MP07 20287
#define MLD_MP08 20288
#define MLD_MP09 20289
#define MLD_MP10 20290
#define INJ_MP01 20291
#define INJ_MP02 20292
#define INJ_MP03 20293
#define INJ_MP04 20294
#define INJ_MP05 20295
#define INJ_MP06 20296
#define INJ_MP07 20297
#define INJ_MP08 20298
#define INJ_MP09 20299
#define INJ_MP10 20300
#define SCR_MP01 20301
#define SCR_MP02 20302
#define SCR_MP03 20303
#define SCR_MP04 20304
#define SCR_MP05 20305
#define SCR_MP06 20306
#define SCR_MP07 20307
#define SCR_MP08 20308
#define SCR_MP09 20309
#define SCR_MP10 20310

#define XREG608  20339       /* 10%soll zykluszeit      */
#define XREG609  20340       /* 10%soll palstfizierzeit */
#define XREG610  20341       /* 10%soll forminnendruck  */
#define XREG611  20342       /* gebrauch nicht sicher   */
#define XREG613  20343       /* S. 21 menge rest     */
#define XREG614  20344       /* S. 21 menge rest     */
#define XREG615  20345       /* S. 21 dauer soll     */
#define XREG616  20346       /* S. 21 dauer ist      */
#define XREG617  20347       /* S. 21 dauer rest     */
#define XREG618  20348       /* zykluszeit S.21      */

#define XREG633  20362       /* werkzeugnummer long     */
#define PSHOT_COUNTER 20363  /* Stueckzaehler, der nie zurueckgesetzt wird */
#define XREG637  20364       /* S.21 ??        */
#define XREG638  20365       /* S.21 ??        */
#define XREG640  20366       /* Einrichtinformation        */
#define XREG641  20367       /* Einrichtinformation        */
#define XREG642  20368       /* Einrichtinformation        */
#define XREG643  20369       /* Einrichtinformation        */
#define XREG644  20370       /* Einrichtinformation        */
#define XREG645  20371       /* Einrichtinformation        */
#define XREG646  20372       /* Einrichtinformation        */
#define XREG647  20373       /* Einrichtinformation        */
#define XREG648  20374       /* Einrichtinformation        */
#define XREG649  20375       /* Einrichtinformation        */
#define XREG650  20376       /* Einrichtinformation        */
#define XREG651  20377       /* Einrichtinformation        */
#define XREG652  20378       /* Einrichtinformation        */
#define XREG653  20379       /* Einrichtinformation        */
#define XREG654  20380       /* Einrichtinformation        */
#define XREG655  20381       /* Einrichtinformation        */
#define XREG656  20382       /* Einrichtinformation        */
#define XREG657  20383       /* Einrichtinformation        */
#define XREG658  20384       /* Einrichtinformation        */
#define XREG659  20385       /* Einrichtinformation        */
#define XREG660  20386       /* Einrichtinformation        */
#define XREG661  20387       /* Einrichtinformation        */
#define XREG662  20388       /* Einrichtinformation        */
#define XREG663  20389       /* Einrichtinformation        */
#define XREG664  20390       /* Einrichtinformation        */
#define XREG665  20391       /* Einrichtinformation        */
#define XREG666  20392       /* Einrichtinformation        */
#define XREG667  20393       /* Einrichtinformation        */
#define XREG668  20394       /* Einrichtinformation        */
#define XREG669  20395       /* Einrichtinformation        */
#define XREG670  20396       /* Einrichtinformation        */
#define XREG671  20397       /* Einrichtinformation        */
#define XREG672  20398       /* Einrichtinformation        */
#define XREG673  20399       /* Einrichtinformation        */
#define XREG674  20400       /* Einrichtinformation        */
#define XREG675  20401       /* Einrichtinformation        */
#define XREG676  20402       /* Einrichtinformation        */
#define XREG677  20403       /* Einrichtinformation        */
#define XREG678  20404       /* Einrichtinformation        */
#define XREG679  20405       /* Einrichtinformation        */
#define XREG680  20406       /* Einrichtinformation        */
#define XREG681  20407       /* Einrichtinformation        */
#define XREG682  20408       /* Einrichtinformation        */
#define XREG683  20409       /* Einrichtinformation        */
#define XREG684  20410       /* Einrichtinformation        */
#define XREG685  20411       /* Einrichtinformation        */
#define XREG686  20412       /* Einrichtinformation        */
#define XREG687  20413       /* Einrichtinformation        */
#define XREG688  20414       /* Einrichtinformation        */
#define XREG689  20415       /* Einrichtinformation        */
#define XREG690  20416       /* Einrichtinformation        */
#define XREG691  20417       /* Einrichtinformation        */


#define XREG775  20460       /* Fuehler art S.40.1            */
#define XREG776  20461       /* Fuehler empf. S.40.1          */
#define XREG777  20462       /* Stiftdurchmesser S.40.1    */
/* ---------------- Airpress ---------------------------------------------- */
#define APST_TOL1 20463      /* TOL Zeitueberwachung 1 */
#define APST_TOL2 20464      /* TOL Zeitueberwachung 2 */
#define APST_TOL3 20465      /* TOL Zeitueberwachung 3 */
#define APST_TOL4 20466      /* TOL Zeitueberwachung 4 */
#define APIT_REF1 20467      /* REF Zeitueberwachung 1 */
#define APIT_REF2 20468      /* REF Zeitueberwachung 2 */
#define APIT_REF3 20469      /* REF Zeitueberwachung 3 */
#define APIT_REF4 20470      /* REF Zeitueberwachung 4 */
/* ------------------------------------------------------------------------ */

#define XREG841  20471       /* Datentraeger-typ S.10      */
#define XREG842  20472       /* Datenuebertragung S.10     */
#define XREG843  20473       /* Datenuebertr. Leitrechner S.10   */
#define XREG985  20474       /* dyn. Wegpunkteingabe    */

#define XREG989  20476       /* Wochenagschaltuhr    */
#define XREG990  20477       /* Wochenagschaltuhr    */
#define XREG991  20478       /* Wochenagschaltuhr    */
#define XREG992  20479       /* Wochenagschaltuhr    */
#define XREG993  20480       /* Wochenagschaltuhr    */
#define XREG994  20481       /* Wochenagschaltuhr    */
#define MAX_SE1_WEG 20482    /* Max. Spritzeinheit-Weg Agg1 */
#define MAX_SE2_WEG 20483    /* Max. Spritzeinheit-Weg Agg2 */
#define MAX_SE3_WEG 20484    /* Max. Spritzeinheit-Weg Agg3 */
#define MAX_SE4_WEG 20485    /* Max. Spritzeinheit-Weg Agg4 */
#define MAX_SE5_WEG 20486    /* Max. Spritzeinheit-Weg Agg5 */
#define MAX_SE6_WEG 20487    /* Max. Spritzeinheit-Weg Agg6 */
#define WOISAKTUEL_TOL 20488 /* 81.2 Tol. Max Werkzeugoeffnungsweg */
#define WOISAKTUEL_REF 20489 /* 81.2 Ref. Max Werkzeugoeffnungsweg */
#define AWISAKTUEL_TOL 20490 /* 81.2 Tol. Max Auswerferweg */
#define AWISAKTUEL_REF 20491 /* 81.2 Ref. Max Auswerferweg */

#define XRPFINM  20517       /* Referenz Forminnendruck */
#define XRPPH11  20518       /* Spritzdruck agg1 phase1 */
#define XRPPH12  20519       /* Spritzdruck agg1 phase2 */
#define XRPPH13  20520       /* Spritzdruck agg1 phase3 */
#define XRPPH14  20521       /* Spritzdruck agg1 phase4 */
#define XRPPH15  20522       /* Spritzdruck agg1 phase5 */


#define XSKANF1  20596       /* anfahrtemp.       */
#define XSKOEL   20597       /* oeltemp.       */
#define XSKTEMA  20598       /* absenktemperatur     */
#define XSNARGR  20599
#define XSNFEHL  20600       /* max. Anzahl Schlechtteile  */
#define XSNGRUM  20601
#define XSNKAV   20602       /* Anzahl Kavitaeten    */
#define XSNLUF1  20603       /* Bildschirmwert Luftprogramm   */
#define XSNLUF2  20604       /* Bildschirmwert Luftprogramm   */
#define XSNLUF3  20605       /* Bildschirmwert Luftprogramm   */
#define XSNLUF4  20606       /* Bildschirmwert Luftprogramm   */

#define XSSBOLZ  20612       /* Druckbolzenlaenge       */
#define XSTANF1  20613       /* anfahrdauer in minuten  */
#define XSTOLWA  20614       /* Toleranzwahl polster /alle */
#define XSYBED1  20633       /* Leistungsbegrenzung in Prozent */

#define XTPFINM  20690       /* toleranz forminnendruck */
#define XTPPH11  20691       /* Spritzdruck phase 1     */
#define XTPPH12  20692       /* Spritzdruck phase 2     */
#define XTPPH13  20693       /* Spritzdruck phase 3     */
#define XTPPH14  20694       /* Spritzdruck phase 4     */
#define XTPPH15  20695       /* Spritzdruck phase 5     */
#define XTSPH10  20696       /* plasitfizierweg      */

#define XTTPH11  20703       /* Spritzzeit  phase 1     */
#define XTTPH12  20704       /* Spritzzeit  phase 2     */
#define XTTPH13  20705       /* Spritzzeit  phase 3     */
#define XTTPH14  20706       /* Spritzzeit  phase 4     */
#define XTTPH15  20707       /* Spritzzeit  phase 5     */
#define XTTPH16  20708       /* Spritzzeit  phase 6     */

#define XXNPM11  20788       /* S.21 Produktionsmenge1  */
#define XXNPM12  20789       /* S.21 Produktionsmenge1  */
#define XXNPM21  20790       /* S.21 Produktionsmenge2  */
#define XXNPM22  20791       /* S.21 Produktionsmenge2  */

/* ---------------- spez.-Register fuer hydr./spec. Umschaltung (9 Spritzstufen) */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define SPPH17_SPEC              20800  /* Soll specifisch Einspritzdruck Agg1 Stufe 7*/
#define SPPH18_SPEC              20801  /* Soll specifisch Einspritzdruck Agg1 Stufe 8*/
#define SPPH19_SPEC              20802  /* Soll specifisch Einspritzdruck Agg1 Stufe 9*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XPPH17_SPEC              20803  /* Ist specifisch Einspritzdruck Agg1 Stufe 7*/
#define XPPH18_SPEC              20804  /* Ist specifisch Einspritzdruck Agg1 Stufe 8*/
#define XPPH19_SPEC              20805  /* Ist specifisch Einspritzdruck Agg1 Stufe 9*/
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define SVPH17_VOL               20806  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe7 */
#define SVPH18_VOL               20807  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe8 */
#define SVPH19_VOL               20808  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe9 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define SPUM16_SPEC              20809  /* Soll specifisch Umschaltdruck Agg1 Stufe 6*/
#define SPUM17_SPEC              20810  /* Soll specifisch Umschaltdruck Agg1 Stufe 7*/
#define SPUM18_SPEC              20811  /* Soll specifisch Umschaltdruck Agg1 Stufe 8*/
#define SPUM19_SPEC              20812  /* Soll specifisch Umschaltdruck Agg1 Stufe 9*/
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define SSPH16_VOL               20813  /* Soll Vol-Umschaltpkt Agg1 Stufe6 */
#define SSPH17_VOL               20814  /* Soll Vol-Umschaltpkt Agg1 Stufe7 */
#define SSPH18_VOL               20815  /* Soll Vol-Umschaltpkt Agg1 Stufe8 */
#define SSPH19_VOL               20816  /* Soll Vol-Umschaltpkt Agg1 Stufe9 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XSPH16_VOL               20817  /* Ist Vol-Umschaltpkt Agg1 Stufe6 */
#define XSPH17_VOL               20818  /* Ist Vol-Umschaltpkt Agg1 Stufe7 */
#define XSPH18_VOL               20819  /* Ist Vol-Umschaltpkt Agg1 Stufe8 */
#define XSPH19_VOL               20820  /* Ist Vol-Umschaltpkt Agg1 Stufe9 */
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
#define SWITCH_PRES_TOL17        20821  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 7*/ 
#define SWITCH_PRES_TOL18        20822  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 8*/ 
#define SWITCH_PRES_TOL19        20823  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 9*/ 
/* ---------------- Soll Toleranz Einspritzdruck spec.--------------------- */
#define SWITCH_PRES_TOL17_SPEC   20824  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 7*/
#define SWITCH_PRES_TOL18_SPEC   20825  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 8*/
#define SWITCH_PRES_TOL19_SPEC   20826  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 9*/
/* ---------------- Soll Toleranz Einspritzzeit --------------------------- */
#define INJ_TIME_TOL17           20827  /* Soll Tol Einspritzzeit Agg1 Stufe 7*/ 
#define INJ_TIME_TOL18           20828  /* Soll Tol Einspritzzeit Agg1 Stufe 8*/ 
#define INJ_TIME_TOL19           20829  /* Soll Tol Einspritzzeit Agg1 Stufe 9*/ 
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
#define SWITCH_POINT_TOL17       20830  /* Soll Tol Um.Point Agg1 Stufe 7*/
#define SWITCH_POINT_TOL18       20831  /* Soll Tol Um.Point Agg1 Stufe 8*/
#define SWITCH_POINT_TOL19       20832  /* Soll Tol Um.Point Agg1 Stufe 9*/
/* ---------------- Soll Toleranz Umschaltpunkt volume -------------------- */
#define SWITCH_POINT_TOL17_VOL   20833  /* Soll Vol Tol Um.Point Agg1 Stufe 7*/
#define SWITCH_POINT_TOL18_VOL   20834  /* Soll Vol Tol Um.Point Agg1 Stufe 8*/ 
#define SWITCH_POINT_TOL19_VOL   20835  /* Soll Vol Tol Um.Point Agg1 Stufe 9*/ 
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF17        20836  /* hydr.Einspritzdruck Agg1 Stufe7 */
#define SWITCH_PRES_REF18        20837  /* hydr.Einspritzdruck Agg1 Stufe8 */ 
#define SWITCH_PRES_REF19        20838  /* hydr.Einspritzdruck Agg1 Stufe9 */ 
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF17_SPEC   20839  /* spec.Einspritzdruck Agg1 Stufe7 */
#define SWITCH_PRES_REF18_SPEC   20840  /* spec.Einspritzdruck Agg1 Stufe8 */ 
#define SWITCH_PRES_REF19_SPEC   20841  /* spec.Einspritzdruck Agg1 Stufe9 */ 
/* ---------------- REF Einspritzzeit ------------------------------------- */
#define INJ_TIME_REF17           20842  /* Einspritzzeit Agg1 Stufe7 */
#define INJ_TIME_REF18           20843  /* Einspritzzeit Agg1 Stufe8 */ 
#define INJ_TIME_REF19           20844  /* Einspritzzeit Agg1 Stufe9 */ 
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF17       20845  /* Umschaltpunkt Agg1 Stufe7 */
#define SWITCH_POINT_REF18       20846  /* Umschaltpunkt Agg1 Stufe8 */ 
#define SWITCH_POINT_REF19       20847  /* Umschaltpunkt Agg1 Stufe9 */ 
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF17_VOL   20848  /* Umschaltvolumen Agg1 Stufe7 */
#define SWITCH_POINT_REF18_VOL   20849  /* Umschaltvolumen Agg1 Stufe8 */
#define SWITCH_POINT_REF19_VOL   20850  /* Umschaltvolumen Agg1 Stufe9 */
/* ------------------------------------------------------------------------ */
/* ---------------- spez.-Register fuer hydr./spec. Umschaltung (10 - 12 Spritzstufen) */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define SPPH1A_SPEC              20851  /* Soll specifisch Einspritzdruck Agg1 Stufe 10*/
#define SPPH1B_SPEC              20852  /* Soll specifisch Einspritzdruck Agg1 Stufe 11*/
#define SPPH1C_SPEC              20853  /* Soll specifisch Einspritzdruck Agg1 Stufe 12*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XPPH1A_SPEC              20854  /* Ist specifisch Einspritzdruck Agg1 Stufe 10*/
#define XPPH1B_SPEC              20855  /* Ist specifisch Einspritzdruck Agg1 Stufe 11*/
#define XPPH1C_SPEC              20856  /* Ist specifisch Einspritzdruck Agg1 Stufe 12*/
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define SVPH1A_VOL               20857  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe 10 */
#define SVPH1B_VOL               20858  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe 11 */
#define SVPH1C_VOL               20859  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe 12 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define SPUM1A_SPEC              20860  /* Soll specifisch Umschaltdruck Agg1 Stufe 10*/
#define SPUM1B_SPEC              20861  /* Soll specifisch Umschaltdruck Agg1 Stufe 11*/
#define SPUM1C_SPEC              20862  /* Soll specifisch Umschaltdruck Agg1 Stufe 12*/
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define SSPH1A_VOL               20863  /* Soll Vol-Umschaltpkt Agg1 Stufe 10 */
#define SSPH1B_VOL               20864  /* Soll Vol-Umschaltpkt Agg1 Stufe 11 */
#define SSPH1C_VOL               20865  /* Soll Vol-Umschaltpkt Agg1 Stufe 12 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XSPH1A_VOL               20866  /* Ist Vol-Umschaltpkt Agg1 Stufe 10 */
#define XSPH1B_VOL               20867  /* Ist Vol-Umschaltpkt Agg1 Stufe 11 */
#define XSPH1C_VOL               20868  /* Ist Vol-Umschaltpkt Agg1 Stufe 12 */
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
#define SWITCH_PRES_TOL1A        20869  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 10*/ 
#define SWITCH_PRES_TOL1B        20870  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 11*/ 
#define SWITCH_PRES_TOL1C        20871  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Einspritzdruck spec.--------------------- */
#define SWITCH_PRES_TOL1A_SPEC   20872  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 10*/
#define SWITCH_PRES_TOL1B_SPEC   20873  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 11*/
#define SWITCH_PRES_TOL1C_SPEC   20874  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 12*/
/* ---------------- Soll Toleranz Einspritzzeit --------------------------- */
#define INJ_TIME_TOL1A           20875  /* Soll Tol Einspritzzeit Agg1 Stufe 10*/ 
#define INJ_TIME_TOL1B           20876  /* Soll Tol Einspritzzeit Agg1 Stufe 11*/ 
#define INJ_TIME_TOL1C           20877  /* Soll Tol Einspritzzeit Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
#define SWITCH_POINT_TOL1A       20878  /* Soll Tol Um.Point Agg1 Stufe 10*/
#define SWITCH_POINT_TOL1B       20879  /* Soll Tol Um.Point Agg1 Stufe 11*/
#define SWITCH_POINT_TOL1C       20880  /* Soll Tol Um.Point Agg1 Stufe 12*/
/* ---------------- Soll Toleranz Umschaltpunkt volume -------------------- */
#define SWITCH_POINT_TOL1A_VOL   20881  /* Soll Vol Tol Um.Point Agg1 Stufe 10*/
#define SWITCH_POINT_TOL1B_VOL   20882  /* Soll Vol Tol Um.Point Agg1 Stufe 11*/ 
#define SWITCH_POINT_TOL1C_VOL   20883  /* Soll Vol Tol Um.Point Agg1 Stufe 12*/ 
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF1A        20884  /* hydr.Einspritzdruck Agg1 Stufe 10 */
#define SWITCH_PRES_REF1B        20885  /* hydr.Einspritzdruck Agg1 Stufe 11 */ 
#define SWITCH_PRES_REF1C        20886  /* hydr.Einspritzdruck Agg1 Stufe 12 */ 
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF1A_SPEC   20887  /* spec.Einspritzdruck Agg1 Stufe 10 */
#define SWITCH_PRES_REF1B_SPEC   20888  /* spec.Einspritzdruck Agg1 Stufe 11 */ 
#define SWITCH_PRES_REF1C_SPEC   20889  /* spec.Einspritzdruck Agg1 Stufe 12 */ 
/* ---------------- REF Einspritzzeit ------------------------------------- */
#define INJ_TIME_REF1A           20890  /* Einspritzzeit Agg1 Stufe 10 */
#define INJ_TIME_REF1B           20891  /* Einspritzzeit Agg1 Stufe 11 */ 
#define INJ_TIME_REF1C           20892  /* Einspritzzeit Agg1 Stufe 12 */ 
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF1A       20893  /* Umschaltpunkt Agg1 Stufe 10 */
#define SWITCH_POINT_REF1B       20894  /* Umschaltpunkt Agg1 Stufe 11 */ 
#define SWITCH_POINT_REF1C       20895  /* Umschaltpunkt Agg1 Stufe 12 */ 
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF1A_VOL   20896  /* Umschaltvolumen Agg1 Stufe 10 */
#define SWITCH_POINT_REF1B_VOL   20897  /* Umschaltvolumen Agg1 Stufe 11 */
#define SWITCH_POINT_REF1C_VOL   20898  /* Umschaltvolumen Agg1 Stufe 12 */
/* ------------------------------------------------------------------------ */

/* ---------------- spez.-Register fuer hydr./spec. Umschaltung (9 Spritzstufen) */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define SPPH27_SPEC              20900  /* Soll specifisch Einspritzdruck Agg1 Stufe 7*/
#define SPPH28_SPEC              20901  /* Soll specifisch Einspritzdruck Agg1 Stufe 8*/
#define SPPH29_SPEC              20902  /* Soll specifisch Einspritzdruck Agg1 Stufe 9*/
#define SPPH2A_SPEC              20903  /* Soll specifisch Einspritzdruck Agg1 Stufe 10*/
#define SPPH2B_SPEC              20904  /* Soll specifisch Einspritzdruck Agg1 Stufe 11*/
#define SPPH2C_SPEC              20905  /* Soll specifisch Einspritzdruck Agg1 Stufe 12*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XPPH27_SPEC              20906  /* Ist specifisch Einspritzdruck Agg1 Stufe 7*/
#define XPPH28_SPEC              20907  /* Ist specifisch Einspritzdruck Agg1 Stufe 8*/
#define XPPH29_SPEC              20908  /* Ist specifisch Einspritzdruck Agg1 Stufe 9*/
#define XPPH2A_SPEC              20909  /* Ist specifisch Einspritzdruck Agg1 Stufe 10*/
#define XPPH2B_SPEC              20910  /* Ist specifisch Einspritzdruck Agg1 Stufe 11*/
#define XPPH2C_SPEC              20911  /* Ist specifisch Einspritzdruck Agg1 Stufe 12*/
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define SVPH27_VOL               20912  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe7 */
#define SVPH28_VOL               20913  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe8 */
#define SVPH29_VOL               20914  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe9 */
#define SVPH2A_VOL               20915  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe 10 */
#define SVPH2B_VOL               20916  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe 11 */
#define SVPH2C_VOL               20917  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe 12 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define SPUM26_SPEC              20918  /* Soll specifisch Umschaltdruck Agg1 Stufe 6*/
#define SPUM27_SPEC              20919  /* Soll specifisch Umschaltdruck Agg1 Stufe 7*/
#define SPUM28_SPEC              20920  /* Soll specifisch Umschaltdruck Agg1 Stufe 8*/
#define SPUM29_SPEC              20921  /* Soll specifisch Umschaltdruck Agg1 Stufe 9*/
#define SPUM2A_SPEC              20922  /* Soll specifisch Umschaltdruck Agg1 Stufe 10*/
#define SPUM2B_SPEC              20923  /* Soll specifisch Umschaltdruck Agg1 Stufe 11*/
#define SPUM2C_SPEC              20924  /* Soll specifisch Umschaltdruck Agg1 Stufe 12*/
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define SSPH26_VOL               20925  /* Soll Vol-Umschaltpkt Agg1 Stufe6 */
#define SSPH27_VOL               20926  /* Soll Vol-Umschaltpkt Agg1 Stufe7 */
#define SSPH28_VOL               20927  /* Soll Vol-Umschaltpkt Agg1 Stufe8 */
#define SSPH29_VOL               20928  /* Soll Vol-Umschaltpkt Agg1 Stufe9 */
#define SSPH2A_VOL               20929  /* Soll Vol-Umschaltpkt Agg1 Stufe 10 */
#define SSPH2B_VOL               20930  /* Soll Vol-Umschaltpkt Agg1 Stufe 11 */
#define SSPH2C_VOL               20931  /* Soll Vol-Umschaltpkt Agg1 Stufe 12 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XSPH26_VOL               20932  /* Ist Vol-Umschaltpkt Agg1 Stufe6 */
#define XSPH27_VOL               20933  /* Ist Vol-Umschaltpkt Agg1 Stufe7 */
#define XSPH28_VOL               20934  /* Ist Vol-Umschaltpkt Agg1 Stufe8 */
#define XSPH29_VOL               20935  /* Ist Vol-Umschaltpkt Agg1 Stufe9 */
#define XSPH2A_VOL               20936  /* Ist Vol-Umschaltpkt Agg1 Stufe 10 */
#define XSPH2B_VOL               20937  /* Ist Vol-Umschaltpkt Agg1 Stufe 11 */
#define XSPH2C_VOL               20938  /* Ist Vol-Umschaltpkt Agg1 Stufe 12 */
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
#define SWITCH_PRES_TOL27        20939  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 7*/ 
#define SWITCH_PRES_TOL28        20940  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 8*/ 
#define SWITCH_PRES_TOL29        20941  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 9*/ 
#define SWITCH_PRES_TOL2A        20942  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 10*/ 
#define SWITCH_PRES_TOL2B        20943  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 11*/ 
#define SWITCH_PRES_TOL2C        20944  /* Soll hydr. Tol Einspritzdr. Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Eispritzdruck spec.--------------------- */
#define SWITCH_PRES_TOL27_SPEC   20945  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 7*/
#define SWITCH_PRES_TOL28_SPEC   20946  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 8*/
#define SWITCH_PRES_TOL29_SPEC   20947  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 9*/
#define SWITCH_PRES_TOL2A_SPEC   20948  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 10*/
#define SWITCH_PRES_TOL2B_SPEC   20949  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 11*/
#define SWITCH_PRES_TOL2C_SPEC   20950  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 12*/
/* ---------------- Soll Toleranz Einspritzzeit --------------------------- */
#define INJ_TIME_TOL27           20951  /* Soll Tol Einspritzzeit Agg1 Stufe 7*/ 
#define INJ_TIME_TOL28           20952  /* Soll Tol Einspritzzeit Agg1 Stufe 8*/ 
#define INJ_TIME_TOL29           20953  /* Soll Tol Einspritzzeit Agg1 Stufe 9*/ 
#define INJ_TIME_TOL2A           20954  /* Soll Tol Einspritzzeit Agg1 Stufe 10*/ 
#define INJ_TIME_TOL2B           20955  /* Soll Tol Einspritzzeit Agg1 Stufe 11*/ 
#define INJ_TIME_TOL2C           20956  /* Soll Tol Einspritzzeit Agg1 Stufe 12*/ 
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
#define SWITCH_POINT_TOL27       20957  /* Soll Tol Um.Point Agg1 Stufe 7*/
#define SWITCH_POINT_TOL28       20958  /* Soll Tol Um.Point Agg1 Stufe 8*/
#define SWITCH_POINT_TOL29       20959  /* Soll Tol Um.Point Agg1 Stufe 9*/
#define SWITCH_POINT_TOL2A       20960  /* Soll Tol Um.Point Agg1 Stufe 10*/
#define SWITCH_POINT_TOL2B       20961  /* Soll Tol Um.Point Agg1 Stufe 11*/
#define SWITCH_POINT_TOL2C       20962  /* Soll Tol Um.Point Agg1 Stufe 12*/
/* ---------------- Soll Toleranz Umschaltpunkt volume -------------------- */
#define SWITCH_POINT_TOL27_VOL   20963  /* Soll Vol Tol Um.Point Agg1 Stufe 7*/
#define SWITCH_POINT_TOL28_VOL   20964  /* Soll Vol Tol Um.Point Agg1 Stufe 8*/ 
#define SWITCH_POINT_TOL29_VOL   20965  /* Soll Vol Tol Um.Point Agg1 Stufe 9*/ 
#define SWITCH_POINT_TOL2A_VOL   20966  /* Soll Vol Tol Um.Point Agg1 Stufe 10*/
#define SWITCH_POINT_TOL2B_VOL   20967  /* Soll Vol Tol Um.Point Agg1 Stufe 11*/ 
#define SWITCH_POINT_TOL2C_VOL   20968  /* Soll Vol Tol Um.Point Agg1 Stufe 12*/
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF27        20969  /* hydr.Einspritzdruck Agg1 Stufe7 */
#define SWITCH_PRES_REF28        20970  /* hydr.Einspritzdruck Agg1 Stufe8 */ 
#define SWITCH_PRES_REF29        20971  /* hydr.Einspritzdruck Agg1 Stufe9 */ 
#define SWITCH_PRES_REF2A        20972  /* hydr.Einspritzdruck Agg1 Stufe 10 */
#define SWITCH_PRES_REF2B        20973  /* hydr.Einspritzdruck Agg1 Stufe 11 */ 
#define SWITCH_PRES_REF2C        20974  /* hydr.Einspritzdruck Agg1 Stufe 12 */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF27_SPEC   20975  /* spec.Einspritzdruck Agg1 Stufe7 */
#define SWITCH_PRES_REF28_SPEC   20976  /* spec.Einspritzdruck Agg1 Stufe8 */ 
#define SWITCH_PRES_REF29_SPEC   20977  /* spec.Einspritzdruck Agg1 Stufe9 */ 
#define SWITCH_PRES_REF2A_SPEC   20978  /* spec.Einspritzdruck Agg1 Stufe 10 */
#define SWITCH_PRES_REF2B_SPEC   20979  /* spec.Einspritzdruck Agg1 Stufe 11 */ 
#define SWITCH_PRES_REF2C_SPEC   20980  /* spec.Einspritzdruck Agg1 Stufe 12 */
/* ---------------- REF Einspritzzeit ------------------------------------- */
#define INJ_TIME_REF27           20981  /* Einspritzzeit Agg1 Stufe7 */
#define INJ_TIME_REF28           20982  /* Einspritzzeit Agg1 Stufe8 */ 
#define INJ_TIME_REF29           20983  /* Einspritzzeit Agg1 Stufe9 */ 
#define INJ_TIME_REF2A           20984  /* Einspritzzeit Agg1 Stufe 10 */
#define INJ_TIME_REF2B           20985  /* Einspritzzeit Agg1 Stufe 11 */ 
#define INJ_TIME_REF2C           20986  /* Einspritzzeit Agg1 Stufe 12 */
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF27       20987  /* Umschaltpunkt Agg1 Stufe7 */
#define SWITCH_POINT_REF28       20988  /* Umschaltpunkt Agg1 Stufe8 */ 
#define SWITCH_POINT_REF29       20989  /* Umschaltpunkt Agg1 Stufe9 */ 
#define SWITCH_POINT_REF2A       20990  /* Umschaltpunkt Agg1 Stufe 10 */
#define SWITCH_POINT_REF2B       20991  /* Umschaltpunkt Agg1 Stufe 11 */ 
#define SWITCH_POINT_REF2C       20992  /* Umschaltpunkt Agg1 Stufe 12 */
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF27_VOL   20993  /* Umschaltvolumen Agg1 Stufe7 */
#define SWITCH_POINT_REF28_VOL   20994  /* Umschaltvolumen Agg1 Stufe8 */
#define SWITCH_POINT_REF29_VOL   20995  /* Umschaltvolumen Agg1 Stufe9 */
#define SWITCH_POINT_REF2A_VOL   20996  /* Umschaltvolumen Agg1 Stufe 10 */
#define SWITCH_POINT_REF2B_VOL   20997  /* Umschaltvolumen Agg1 Stufe 11 */
#define SWITCH_POINT_REF2C_VOL   20998  /* Umschaltvolumen Agg1 Stufe 12 */
/* ------------------------------------------------------------------------ */

/* Register zur IQT-internen Verwaltung der Schusszaehler.           */
/* Diese IQT-Register ersetzen alte ISCOS-Register.                  */
#define XNADD              21000    /* Addierender Schusszaehler     */
#define XNSUB              21001    /* Subtrahierender Schusszaehler */
#define XSNSUS             21002    /* Produktionsmenge in Stueck    */
#define HOST_AGGREGAT      21003    /* AggNr. fuer UserFkt. bei Hostzugriff  */
#define HOST_ACT_REGLER_NR 21004    /* akt. Reglernr ...                     */

/* IQT-Einspritzregister */
#define WKZINN_TOL_AGG2    21007
#define WKZINN_TOL         21008
#define ZYKZEIT_TOL        21009
#define PLAST_TIME_TOL     21010
#define DWELL_PRES1        21011    /* Istwert Nachdruckstufe Agg.1 wg. Host */
#define DWELL_PRES2        21012    /* Istwert Nachdruckstufe Agg.2 wg. Host */
#define FILL_TIME1         21013    /* Istwert Fuellzeit (ohne Nachdruck)    */
#define FILL_TIME2         21014    /* Istwert Fuellzeit (ohne Nachdruck)    */
#define TOL_SELECT         21015
#define TOL_NR_INJ_CYC1    21018
#define INJ_WORK           21019    /* Einspritzarbeit */  
/* Variable Einpritzgeschwindigkeiten S.41/42 abh. von Kundenpromparametern */
#define INJ_SPEED_MAX1     21020    /* Max-Plaus fuer Spritzgeschw. Agg. 1  */
#define INJ_SPEED_MAX2     21021    /* Max-Plaus fuer Spritzgeschw. Agg. 2  */
#define INJ_SPEED_MAX3     21022    /* Max-Plaus fuer Spritzgeschw. Agg. 3  */
#define INJ_SPEED_CONV1    21023    /* Konvertierungsfaktor Agg. 1          */
#define INJ_SPEED_CONV2    21024    /* Konvertierungsfaktor Agg. 2          */
#define INJ_SPEED_CONV3    21025    /* Konvertierungsfaktor Agg. 3          */
#define INJ_SPEED_CONV4    21026    /* Konvertierungsfaktor Agg. 4          */
#define EJECT_HASCO        21027    /* 0 - nichts aktiv               */
                                    /* 1 - Auswerfer aktiv            */
                                    /* 2 - Kupplung aktiv             */
#define WKZ_CODE             21028  /* IQT-Register nur fuer Host     */
#define AGGREGAT0            21029
#define AGGREGAT             21030
#define STATION              21031
#define IQT_DUMMY_REG        21032
#define HOST_UPDOWN_REG      21033  /* Starten des Host Up-/Downloads */
#define FGBG_DATASET_EQUAL   21034  /* Markiert Datensatz-Gleichheit  */
#define NR_PLAST             21035  /* Anzahl Plastifizierstufen      */
#define ACT_SN_PARAM_TAB     21036  /* akt. KProm-Schneckentab (1,2,3)*/
#define MAX_TEMPHEAT         21037  /* max. Temperiergeraete aus KProm */
#define MAX_HEATCHAN         21038  /* max. Heisskanaele aus KProm     */
#define XSSFZU_SHOW          21039  /* zum Anzeigen von XSSFZU         */
#define MAX_INJUNITS         21040  /* fuer Dunkeltastungsroutinen     */
/* stat. Prozesskontrolle */
#define SPCVarTab            21041
#define SPCRegInd1           21042
#define SPCRegInd2           21043
#define SPCIndex             21044
#define SPCTestSize          21045
#define SPCTestBreakSize     21046
#define SPCNrPreTests        21047
#define SPCMSkaleEnd         21048
#define SPCMSkaleBegin       21049
#define SPCSSkaleEnd         21050
#define SPCSSkaleBegin       21051
#define SPCRSkaleEnd         21052
#define SPCRSkaleBegin       21053
#define SPCMUEG              21054
#define SPCMOEG              21055
#define SPCSUEG              21056
#define SPCSOEG              21057
#define SPCRUEG              21058
#define SPCROEG              21059
#define SPCMUEGm             21060
#define SPCMOEGm             21061
#define SPCSUEGm             21062
#define SPCSOEGm             21063
#define SPCRUEGm             21064
#define SPCROEGm             21065
#define SPCOSGcm             21066
#define SPCUSGcm             21067
#define SPCPreTestSwitch     21068
#define SPCAutoSwitch        21069
#define SPCManualSwitch      21070
#define SPCTimeSwitch        21071
#define SPCTestCount         21072
#define SPCBreakCount        21073
#define SPCM                 21074
#define SPCS                 21075
#define SPCMpS               21076
#define SPCMmS               21077
#define SPCcm                21078
#define SPCcmk               21079
#define SPCcp                21080
#define SPCcpk               21081
#define SPCMMRegTab          21082
#define SPCMSRegTab          21083
#define SPCMRRegTab          21084
#define SPCPreTestCount      21085
#define SPCOSGcp             21086
#define SPCUSGcp             21087
#define SPCRegInd3           21088
#define SPCAggregat          21089

/* Betriebsdatenerfassung */
#define BDEStopTimeType      21097
#define BDEAggregat          21098
#define BDERegInd3           21099
#define BDEVarTab            21100
#define BDERegInd1           21101
#define BDERegInd2           21102
#define BDENrDocCycles       21103
#define BDENrNotDocCycles    21104
#define BDEProcDataSwitch    21105
#define BDEErrMsgSwitch      21106
#define BDEStopTimeSwitch    21107
#define BDESollDataSwitch    21108
#define BDEContSwitch        21109
#define BDEStartInt1         21110
#define BDEStopInt1          21111
#define BDEStartInt2         21112
#define BDEStopInt2          21113
#define BDEStartInt3         21114
#define BDEStopInt3          21115
#define BDEPrintMode         21116
#define BDEStartPrint        21117
#define BDEStartClearBuffer  21118
#define BDEStartPrintLegend  21119
#define BDECycleInt          21120
/* Istwertverfolgung im Achsenkreuz */
#define AxisVarTab           21121
#define AxisRegInd1          21122
#define AxisRegInd2          21123
#define AxisRegInd3          21124
#define AxisAggregat         21125


/* Register fur Realtime-Clock */
#define TIME_IST_HH          21130
#define TIME_IST_MM          21131
#define TIME_IST_SS          21132
#define DATE_IST_DD          21133
#define DATE_IST_MM          21134
#define DATE_IST_YY          21135
#define TIME_SOLL_HH         21136
#define TIME_SOLL_MM         21137
#define TIME_SOLL_SS         21138
#define DATE_SOLL_DD         21139
#define DATE_SOLL_MM         21140
#define DATE_SOLL_YY         21141


/* Multiplex-Register fr Heizzonen, speziell fr Reglerparameter-Seiten */
#define ACT_CYL_HEAT_ZONE    21150
#define ACT_TOOL_HEAT_ZONE   21151
#define ACT_TEMP_HEAT_ZONE   21152
#define ACT_REGLER_NR        21153

/* Zusaetzliche Register fuer die Heizzonen */
#define INJHEAT_ABS_NORM     21160 /* Temperaturabsenkung Zylinder normal*/
#define INJHEAT_ABS_IN       21161 /* Temperaturabsenkung Zylinder Einzug*/
#define TOOLHEAT_ABS         21162 /* Temperaturabsenkung Werkzeug */
#define TEMPHEAT_ABS         21163 /* Temperaturabsenkung Temperierger.*/
#define INJHEAT_ANF_NORM     21164 /* Anfahrschaltung Zylinder normal */
#define INJHEAT_ANF_IN       21165 /* Anfahrschaltung Zylinder Einzug */
#define TOOLHEAT_ANF         21166 /* Anfahrschaltung Werkzeug */
#define TEMPHEAT_ANF         21167 /* Anfahrschaltung Temperiergeraete */
#define HEAT_OPTMODE			  21168 /* Optimierungsart eines Reglers */
#define OPTMODEREGLER		  21169 /* x- ter Regler im Optimierungsblock */
#define DISK_FILE_TYPE       21170 /* Dateityp */
#define EXT_COUNT_MAX        21171 /* Sollwert fuer Kartonverschiebung */
#define EXT_COUNT_ACT        21172 /* Istwert fuer Kartonverschiebung */

#define REG_FOT_PAGE_1       21180 /* Zustand der frei konf. Seite 1 */
#define REG_FOT_PAGE_2       21181 /* Zustand der frei konf. Seite 2 */
#define REG_FOT_PAGE_3       21182 /* Zustand der frei konf. Seite 3 */

#define XSSAUS3_INVERS       21185 /* Anzeige Auswerferrueckweg S.52 */

#define HOST_START_ORDER     21190 /* S.21.1 Auftragsstart   anfordern   */
#define HOST_STOP_ORDER      21191 /* S.21.1 Auftragsende    anfordern   */
#define HOST_CANCEL_ORDER    21192 /* S.21.1 Auftragsabbruch anfordern   */
#define HOST_REJECTS         21193 /* S.21.1 Ausschuss eingeben          */
#define HOST_GOOD_PARTS      21194 /* S.21.1 Gutteile zurueckfuehren     */
#define HOST_PAUSE_CYCLES    21195 /* S      Pausenzyklen fuer TB-Prot.  */


/* Register fuer Prozessgraphik */
#define PG_OPMODE            21200 /* Istwertregister fuer Betriebsart */
#define PG_MTIME             21201 /* Meazeit */
#define PG_DELAY             21202 /* Startverzgerung */
#define PG_XRIGHT            21203 /* rechte X-Skal.in 1/10 sec: MTIME*10+DELAY */
#define PG_MINT              21204 /* Messintervall */
#define PG_MAXX              21205 /* Maximalwert fuer x-Achse Arbeitsgr.*/
#define PG_MAXY              21206 /* Maximalwert Y-Skalierung 1-8 */
#define PG_SKALY             21207 /* Skalierendwert der Y-Achse 1-8 */
#define PG_SOLLIST           21208 /* Nr der Kan. fr Soll-Ist-Vergl. 1-4*/
#define PG_TOL               21209 /* Toleranzen in % fr obige Kanaele */
#define PG_WORK              21210 /* Arbeitsber., 0=nein,1=ja,2=mit Ueb.*/
#define PG_START_WORK        21211 /* Startwert des Arbeitsintegrals */
#define PG_STOP_WORK         21212 /* Endpunkt des Arbeitsintegrals */
#define PG_IST_WORK          21213 /* Istwert der Arbeit */
#define PG_REFIST_WORK       21214 /* Referenzistwert der Arbeit */
#define PG_TOL_WORK          21215 /* Tol. in % fuer Arbeitsueberwachung */
#define PG_CUR1              21216 /* Position des Cursors 1 */
#define PG_CUR2              21217 /* Position des Cursors 2 */
#define PG_MAX_IST           21218 /* Ist: Maximalwerte der Istkurven */
#define PG_CUR1_IST          21219 /* Ist: Werte der Istkurven bei Cur1 */
#define PG_CUR2_IST          21220 /* Ist: Werte der Istkurven bei Cur2 */
#define PG_TOLUP_MAX_IST     21221 /* Istwert: Maximum der oberen Tol. */
#define PG_TOLDOWN_MAX_IST   21222 /* Istwert: Maximum der unteren Tol. */
#define PG_SOLL_MAX_IST      21223 /* Istwert: Maximum der Sollkurve */
#define PG_TOLUP_CUR1_IST    21224 /* Istwert: Wert der oberen Tol bei Cur1 */
#define PG_TOLDOWN_CUR1_IST  21225 /* Istwert: Wert der unteren Tol bei Cur1*/
#define PG_SOLL_CUR1_IST     21226 /* Istwert: Wert der Sollkurve bei Cur1 */
#define PG_TOLUP_CUR2_IST    21227 /* Istwert: Wert der oberen Tol bei Cur2 */
#define PG_TOLDOWN_CUR2_IST  21228 /* Istwert: Wert der unteren Tol bei Cur2*/
#define PG_SOLL_CUR2_IST     21229 /* Istwert: Wert der Sollkurve bei Cur2 */
#define PG_XLEFT             21230 /* linke X-Skal.in 1/10 sec: MTIME*10+DELAY */
#define PG_OPMODE_SOLL       21231 /* Sollwertregister fuer Betriebsart */
#define PG_XNADD             21232 /* Sicherung Schusszaehler fuer PG */

/* Register fuer Prozessgraphik */
#define WCLOCK_DATE_DD           21240 /* Schaltuhr ueber Datum, Tag         */
#define WCLOCK_DATE_MM           21241 /* Schaltuhr ueber Datum, Monat       */
#define WCLOCK_DATE_YY           21242 /* Schaltuhr ueber Datum, Jahr        */
#define WCLOCK_START             21243 /* Ein-, Ausschaltzeiten, hh.mm,     */
#define WCLOCK_STOP              21244 /* Index 1 - 7 benutzt fuer Mo - So   */
#define WCLOCK_MOTOR_START_DELAY 21245 /* Einschaltverzoegerung Motor        */
#define WCLOCK_HEAT_START_DELAY  21246 /* Einschaltverzoegerung Heizung      */
#define WCLOCK_EXT1_START_DELAY  21247 /* Einschaltverzoegerung ext. Geraet 1 */
#define WCLOCK_EXT2_START_DELAY  21248 /* Einschaltverzoegerung ext. Geraet 2 */
#define WCLOCK_MOTOR_STOP_DELAY  21249 /* Ausschaltverzoegerung Motor        */
#define WCLOCK_HEAT_STOP_DELAY   21250 /* Ausschaltverzoegerung Heizung      */
#define WCLOCK_EXT1_STOP_DELAY   21251 /* Ausschaltverzoegerung ext. Geraet 1 */
#define WCLOCK_EXT2_STOP_DELAY   21252 /* Ausschaltverzoegerung ext. Geraet 2 */
#define WCLOCK_EXT1_SWITCH       21253 /* Schaltuhr auf ext. Geraet 1 anwenden*/
#define WCLOCK_EXT2_SWITCH       21254 /* Schaltuhr auf ext. Geraet 2 anwenden*/
#define WCLOCK_MOTOR_SWITCH      21255 /* Schaltuhr auf Motor anwenden        */
#define WCLOCK_HEAT_SWITCH       21256 /* Schaltuhr auf Heizung anwenden      */


/* Register fuer das Drucken */
#define PRINT_MODE               21260   /* Druck-Modus */
#define PRINT_PAGE               21261   /* zu druckende Seiten */
#define PRINT_ERROR_PAGE         21262   /* Fehlermeldungsseite drucken */
#define PRINT_TIME_INT           21263   /* Zeit-Intervall */
#define PRINT_CYCLE_INT          21264   /* Zyklus-Intervall */
#define PRINT_AUT_MASH_STOP      21265   /* Drucken bei autom. Maschinenstop */
#define PRINT_PRINTER_TYPE       21266   /* Druckertyp */
#define PRINT_STATUS_LINE        21267   /* Statuszeilen ausgeben ? */
#define PRINT_SOFTKEYS           21268   /* Softkeys ausgeben ? */
#define PRINT_LINES_PER_PAGE     21269   /* Anzahl Zeilen pro Seite */
#define PRINT_MRGN_TOP           21270   /* Randabstand oben */
#define PRINT_MRGN_BOTTOM        21271   /* Randabstand unten */
#define PRINT_PAGE_AGGREGAT      21272   /* Spritzeinh. der zu dr. Seiten */

/* Register fuer die Schnittstellen-Konfiguration */
#define IFK_DEVICE               21280   /* Zuordnung zu Geraet */
#define IFK_DATA_BITS            21281   /* Anzahl Datenbits */
#define IFK_STOP_BITS            21282   /* Anzahl Stopbits */
#define IFK_PARITY               21283   /* Parity */
#define IFK_BAUDRATE             21284   /* Baudrate */

/* Register fuer den Leitrechner */
#define XPOJSS                   21290   /* Auftragsstart fuer Leitrechner  */
#define XPOJES                   21291   /* Auftragsende  fuer Leitrechner  */


/* Register fuer die Schichtzaehler */
#define SCHICHT1_BEGIN           21300  /* Schicht 1 Beginn */
#define SCHICHT1_END             21301  /* Schicht 1 Ende   */
#define SCHICHT2_BEGIN           21302  /* Schicht 2 Beginn */
#define SCHICHT2_END             21303  /* Schicht 2 Ende   */
#define SCHICHT3_BEGIN           21304  /* Schicht 3 Beginn */
#define SCHICHT3_END             21305  /* Schicht 3 Ende   */
#define AUSSCHUSS_SCHICHT        21306  /* Ausschuss pro Schicht IST  */
#define AUSSCHUSS_GESAMT         21307  /* Ausschuss gesammt IST      */
#define GUTTEILE_SCHICHT         21308  /* Gutteile pro Schicht IST  */

/* Register fuer Gutteile und Schlechtteile pro Schicht */
#define SCHICHT1_GOOD            21310  /* Schicht 1 Gutteile        */
#define SCHICHT1_BAD             21311  /* Schicht 1 Schlechtteile   */
#define SCHICHT2_GOOD            21312  /* Schicht 2 Gutteile        */
#define SCHICHT2_BAD             21313  /* Schicht 2 Schlechtteile   */
#define SCHICHT3_GOOD            21314  /* Schicht 3 Gutteile        */
#define SCHICHT3_BAD             21315  /* Schicht 3 Schlechtteile   */
#define BTCOUNTER_IST_HH         21316  /* Betriebsstundenzaehler IST in Stunden */
#define BTCOUNTER_IST_MM         21317  /* Betriebsstundenzaehler IST in Minuten */
#define BTCOUNTER_SOLL_HH        21318  /* Betriebsstundenzaehler SOLL in Stunden */
#define BTCOUNTER_SOLL_MM        21319  /* Betriebsstundenzaehler SOLL in Minuten */
#define ACT_PALETTE              21320  /* Aktuelle Farbpalette      */
#define ACT_SYSPRINTER           21321  /* Aktueller Systemdrucker SYSPRN */

/* Register fuer Zeitanalyse */
#define IZEITAND             21399  /* S.17.1 Zeitanalyse  */
#define IZEITANAVERD         21400  /* S.17.1 Zeitanalyse  */
#define XZEITAN1             21401  /* S.17.1 Zeitanalyse  */
#define XZEITAN2             21402  /* S.17.1 Zeitanalyse  */
#define XZEITAN3             21403  /* S.17.1 Zeitanalyse  */
#define XZEITAN4             21404  /* S.17.1 Zeitanalyse  */
#define XZEITAN5             21405  /* S.17.1 Zeitanalyse  */
#define XZEITAN6             21406  /* S.17.1 Zeitanalyse  */
#define XZEITAN7             21407  /* S.17.1 Zeitanalyse  */
#define XZEITAN8             21408  /* S.17.1 Zeitanalyse  */
#define XZEITAN9             21409  /* S.17.1 Zeitanalyse  */
#define XZEITANA             21410  /* S.17.1 Zeitanalyse  */
#define XZEITANB             21411  /* S.17.1 Zeitanalyse  */
#define XZEITANC             21412  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER1         21413  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER2         21414  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER3         21415  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER4         21416  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER5         21417  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER6         21418  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER7         21419  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER8         21420  /* S.17.1 Zeitanalyse  */
#define XZEITANAVER9         21421  /* S.17.1 Zeitanalyse  */
#define XZEITANAVERA         21422  /* S.17.1 Zeitanalyse  */
#define XZEITANAVERB         21423  /* S.17.1 Zeitanalyse  */
#define XZEITANAVERC         21424  /* S.17.1 Zeitanalyse  */
#define XZYLINDERHUB         21425  /* XM05 -XMP06         */ 
/* Register fuer SPS-Software-Version Elektra-Procontrol */
#define XSPS_HVER            21426  /* S.17.0 SPS-Software-Version  */
#define XSPS_UVER            21427  /* S.17.0 SPS-Software-Version  */
#define XSPS_BUGFIX          21428  /* S.17.0 SPS-Software-BugFix   */
/* Register fuer DatenModul-Software-Version ab EL.01.06.0 Elektra-Proc. */
#define XDM_HVER             21429  /* S.17.0 DM-Software-Version  */
#define XDM_UVER             21430  /* S.17.0 DM-Software-Version  */
#define XDM_BUGFIX           21431  /* S.17.0 DM-Software-BugFix   */
/* Register fuer Zeitanalyse Agg2-6 */
#define XZEITAN4_2           21432  /* S.17.1 Zeitanalyse (N-1) Aggregat 2 vor */
#define XZEITAN4_3           21433  /* S.17.1 Zeitanalyse (N-1) Aggregat 3 vor */
#define XZEITAN4_4           21434  /* S.17.1 Zeitanalyse (N-1) Aggregat 4 vor */
#define XZEITAN5_2           21435  /* S.17.1 Zeitanalyse (N-1) Einspritzen Agg.2 vor */
#define XZEITAN5_3           21436  /* S.17.1 Zeitanalyse (N-1) Einspritzen Agg.3 vor */
#define XZEITAN5_4           21437  /* S.17.1 Zeitanalyse (N-1) Einspritzen Agg.4 vor */
#define XZEITAN6_2           21438  /* S.17.1 Zeitanalyse (N-1) Dosieren Agg.2 */
#define XZEITAN6_3           21439  /* S.17.1 Zeitanalyse (N-1) Dosieren Agg.3 */
#define XZEITAN6_4           21440  /* S.17.1 Zeitanalyse (N-1) Dosieren Agg.4 */
#define XZEITANAVER4_2       21441  /* S.17.1 Zeitanalyse (D) Aggregat 2 vor */
#define XZEITANAVER4_3       21442  /* S.17.1 Zeitanalyse (D) Aggregat 3 vor */
#define XZEITANAVER4_4       21443  /* S.17.1 Zeitanalyse (D) Aggregat 4 vor */
#define XZEITANAVER5_2       21444  /* S.17.1 Zeitanalyse (D) Einspritzen Agg. 2 vor */
#define XZEITANAVER5_3       21445  /* S.17.1 Zeitanalyse (D) Einspritzen Agg. 3 vor */
#define XZEITANAVER5_4       21446  /* S.17.1 Zeitanalyse (D) Einspritzen Agg. 4 vor */
#define XZEITANAVER6_2       21447  /* S.17.1 Zeitanalyse (D) Dosieren Agg.2 */
#define XZEITANAVER6_3       21448  /* S.17.1 Zeitanalyse (D) Dosieren Agg.3 */
#define XZEITANAVER6_4       21449  /* S.17.1 Zeitanalyse (D) Dosieren Agg.4 */
#define ISRSSVOR             21450  /* Schummelregister-Array fuer Schneckenr. */
#define XZEITAN4_5           21451  /* S.17.1 Zeitanalyse (N-1) Aggregat 5 vor */
#define XZEITAN4_6           21452  /* S.17.1 Zeitanalyse (N-1) Aggregat 6 vor */
#define XZEITAN5_5           21453  /* S.17.1 Zeitanalyse (N-1) Einspritzen Agg.5 vor */
#define XZEITAN5_6           21454  /* S.17.1 Zeitanalyse (N-1) Einspritzen Agg.6 vor */
#define XZEITAN6_5           21455  /* S.17.1 Zeitanalyse (N-1) Dosieren Agg.5 */
#define XZEITAN6_6           21456  /* S.17.1 Zeitanalyse (N-1) Dosieren Agg.6 */
#define XZEITANAVER4_5       21457  /* S.17.1 Zeitanalyse (D) Aggregat 5 vor */
#define XZEITANAVER4_6       21458  /* S.17.1 Zeitanalyse (D) Aggregat 6 vor */
#define XZEITANAVER5_5       21459  /* S.17.1 Zeitanalyse (D) Einspritzen Agg. 5 vor */
#define XZEITANAVER5_6       21460  /* S.17.1 Zeitanalyse (D) Einspritzen Agg. 6 vor */
#define XZEITANAVER6_5       21461  /* S.17.1 Zeitanalyse (D) Dosieren Agg.5 */
#define XZEITANAVER6_6       21462  /* S.17.1 Zeitanalyse (D) Dosieren Agg.6 */
#define IPLASTSTUFE          21463  /* Schummelregister-Array fuer 2/4 Plastifizierstufen */

#include "robreg.h"  /* 21499 - 21570 */

/* Register fuer die Heizungs-Selbstoptimierung */
#define HEATOPT_REGLER           21600  /* Multiplexregister der Seite 39    */
#define LAST_HEATOPT_REGLER      21601  /* Letzter Wert von HEATOPT_REGLER,  */
                                        /* der <> 0 war; Ist HEATOPT_REGLER>0*/
                                        /* so sind beide Register identisch  */
#define HEATOPT_DUMMY            21602  /* Ausgabe der Block-Reglernummern.  */
#define OPTHEAT_TN               21604  /* Die folgenden Register enthalten  */
#define OPTHEAT_TV               21605  /* die Werte des aktuellen Reglers,  */
#define OPTHEAT_XPH              21606  /* wie sie auf der Temperaturkarte   */
#define OPTHEAT_XPK              21607  /* stehen. Sie werden per speziellem */
#define OPTHEAT_HEAT_PERIOD      21608  /* Datacom vom Iscos geholt fuer die */
#define OPTHEAT_COOL_PERIOD      21609  /* Anzeige auf Seite 39.             */


/* ---------------- Register fuer den Maschinenabgleich von Ventilen --------- */
#define IMAX_VENTIL          21699  /* Max. Ventile         */
#define IVENTIL_IND          21700  /* Ventil-Index         */
#define IMAS_OFFS1           21701  /* Ventiloffset 1       */
#define IMAS_OFFS2           21702  /* Ventiloffset 2       */
#define IMAS_VERS1           21703  /* Ventilverstaerkung 1 */
#define IMAS_VERS2           21704  /* Ventilverstaerkung 2 */
#define IVENTIL_NR           21705  /* IQT-Ventil-Nummer        */
#define IVENTIL_OFF1         21706  /* IQT-Ventil-Offset1       */
#define IVENTIL_VERS1        21707  /* IQT-Ventil-Verstaerkung1 */
#define IVENTIL_OFF2         21708  /* IQT-Ventil-Offset2       */
#define IVENTIL_VERS2        21709  /* IQT-Ventil-Verstaerkung2 */
/* --------------------------------------------------------------------------- */
#define TRENDVARIND1         21710  /* Index1  in die Trenddarstellungstabelle */
#define TRENDVARIND2         21711  /* Index2  in die Trenddarstellungstabelle */
#define TRENDVARIND3         21712  /* Index3  in die Trenddarstellungstabelle */
#define TRENDVARIND4         21713  /* Index4  in die Trenddarstellungstabelle */
#define TRENDVARIND5         21714  /* Index5  in die Trenddarstellungstabelle */
#define TRENDVARIND6         21715  /* Index6  in die Trenddarstellungstabelle */
#define TRENDVARIND7         21716  /* Index7  in die Trenddarstellungstabelle */
#define TRENDVARIND8         21717  /* Index8  in die Trenddarstellungstabelle */
#define TRENDVARIND9         21718  /* Index9  in die Trenddarstellungstabelle */
#define TRENDVARIND10        21719  /* Index10 in die Trenddarstellungstabelle */
#define TRENDVARSTART        21720  /* Beginn der Trenddarstellungstabelle */
#define TRENDVAREND          21721  /* End der Trenddarstellungstabelle */

/* Register fuer erweiterte Aggregattabelle, Aggregat 2-5 */
#define INJ_MP01_2           21730
#define INJ_MP02_2           21731
#define INJ_MP03_2           21732
#define INJ_MP04_2           21733
#define INJ_MP05_2           21734
#define INJ_MP06_2           21735
#define INJ_MP07_2           21736
#define INJ_MP08_2           21737
#define INJ_MP09_2           21738
#define INJ_MP10_2           21739
#define INJ_MP01_3           21740
#define INJ_MP02_3           21741
#define INJ_MP03_3           21742
#define INJ_MP04_3           21743
#define INJ_MP05_3           21744
#define INJ_MP06_3           21745
#define INJ_MP07_3           21746
#define INJ_MP08_3           21747
#define INJ_MP09_3           21748
#define INJ_MP10_3           21749
#define INJ_MP01_4           21750
#define INJ_MP02_4           21751
#define INJ_MP03_4           21752
#define INJ_MP04_4           21753
#define INJ_MP05_4           21754
#define INJ_MP06_4           21755
#define INJ_MP07_4           21756
#define INJ_MP08_4           21757
#define INJ_MP09_4           21758 
#define INJ_MP10_4           21759
#define INJ_MP01_5           21760
#define INJ_MP02_5           21761
#define INJ_MP03_5           21762
#define INJ_MP04_5           21763
#define INJ_MP05_5           21764
#define INJ_MP06_5           21765
#define INJ_MP07_5           21766
#define INJ_MP08_5           21767
#define INJ_MP09_5           21768
#define INJ_MP10_5           21769
/* Register fuer erweiterte Schneckentabelle, Aggregat 2-6 */
#define SCR_MP01_2           21770
#define SCR_MP02_2           21771
#define SCR_MP03_2           21772
#define SCR_MP04_2           21773
#define SCR_MP05_2           21774
#define SCR_MP06_2           21775
#define SCR_MP07_2           21776
#define SCR_MP08_2           21777
#define SCR_MP09_2           21778
#define SCR_MP10_2           21779
#define SCR_MP01_3           21780
#define SCR_MP02_3           21781
#define SCR_MP03_3           21782
#define SCR_MP04_3           21783
#define SCR_MP05_3           21784
#define SCR_MP06_3           21785
#define SCR_MP07_3           21786
#define SCR_MP08_3           21787
#define SCR_MP09_3           21788
#define SCR_MP10_3           21789
#define SCR_MP01_4           21790
#define SCR_MP02_4           21791
#define SCR_MP03_4           21792
#define SCR_MP04_4           21793
#define SCR_MP05_4           21794
#define SCR_MP06_4           21795
#define SCR_MP07_4           21796
#define SCR_MP08_4           21797
#define SCR_MP09_4           21798
#define SCR_MP10_4           21799
#define SCR_MP01_5           21800
#define SCR_MP02_5           21801
#define SCR_MP03_5           21802
#define SCR_MP04_5           21803
#define SCR_MP05_5           21804
#define SCR_MP06_5           21805
#define SCR_MP07_5           21806
#define SCR_MP08_5           21807
#define SCR_MP09_5           21808
#define SCR_MP10_5           21809
#define SCR_MP01_6           21810
#define SCR_MP02_6           21811
#define SCR_MP03_6           21812
#define SCR_MP04_6           21813
#define SCR_MP05_6           21814
#define SCR_MP06_6           21815
#define SCR_MP07_6           21816
#define SCR_MP08_6           21817
#define SCR_MP09_6           21818
#define SCR_MP10_6           21819
/* Register fuer erweiterte Aggregattabelle, Aggregat 6 */
#define INJ_MP01_6           21820
#define INJ_MP02_6           21821
#define INJ_MP03_6           21822
#define INJ_MP04_6           21823
#define INJ_MP05_6           21824
#define INJ_MP06_6           21825
#define INJ_MP07_6           21826
#define INJ_MP08_6           21827
#define INJ_MP09_6           21828
#define INJ_MP10_6           21829


/* Register fuer 2tes Aggregat */
#define XREG666_2                22000  /* Regenerationszusatz             */
#define XREG664_2                22001  /* Farbmittelzusatz                */
#define XREG672_2                22002  /* Treibmittelzusatz               */
#define XREG673_2                22003  /* Materialvorwaermung             */
#define XREG663_2                22004  /* Materialvorwaermzeit            */
#define XREG658_2                22005  /* Farbmischgeraet                 */
#define XREG657_2                22006  /* Materialfoerdergeraet           */
#define XREG682_2                22007  /* Schneckenzylinder               */
#define XREG683_2                22008  /* Duesenradius/Duesenlaenge       */
#define XREG691_2                22009  /* Duesenbohrung                   */
#define XREG684_2                22010  /* Tauchduese                      */
#define XREG689_2                22011  /* Wechselraeder/Hydromotor        */
#define XREG690_2                22012  /* Druck am Hydromotor             */
#define AGGPOS_2                 22013  /* Spritzzylinder                  */
#define XMP19_2                  22014  /* Schneckendrehzahl               */
#define XMP20_22_2               22015  /* Getriebe/Zaehnezahl             */
#define XMP25_AGG2               22016  /* Schneckendurchmesser            */
#define XMP28_2                  22017  /* Anzahl Heizzonen                */
#define XMP27_2                  22018  /* Zylinder-Ausfuehrung            */
#define INJHEAT_ABS_NORM_2       22019  /* Temperaturabsenkung             */
#define NR_PLAST_2               22020  /* Anzahl Plastfizierstufen        */
#define XREG775_2                22021  /* Fuehlerart                      */
#define XREG777_2                22022  /* Stiftdurchmesser                */
#define XREG776_2                22023  /* Fuehlerempfindlichkeit          */
#define XMP23_2                  22024  /* Aggregattyp fuer Aggregat 2     */
#define XMP24_2                  22025  /* Aggregatgroesse fuer Aggregat 2 */
#define XMP19_KP_2               22026  /* Schneckendrehzahl max. Agg. 2   */
#define XMP20_2                  22027  /* Zaehnezahl klein fuer Agg. 2    */
#define XMP21_2                  22028  /* Zaehnezahl mittel fuer Agg.2    */
#define XMP22_2                  22029  /* Zaehnezahl gross fuer Agg.2     */
#define XMP25_1_2                22030  /* Snedurchmesser kleine Schnecke  */
#define XMP25_2_2                22031  /* Snedurchmesser mittlere Schnecke*/
#define XMP25_3_2                22032  /* Snedurchmesser grosse Schnecke  */
#define XTSPH20                  22033  /* plasitfizierweg Aggregat 2      */
#define PLAST_TIME_TOL_2         22034  /* Plastifizierzeit Toleranz Agg 2 */
#define INJ_TIME_TOL11           22035
#define INJ_TIME_TOL12           22036
#define INJ_TIME_TOL13           22037
#define INJ_TIME_TOL14           22038
#define INJ_TIME_TOL15           22039
#define INJ_TIME_TOL16           22040
#define INJ_TIME_TOL21           22041
#define INJ_TIME_TOL22           22042
#define INJ_TIME_TOL23           22043
#define INJ_TIME_TOL24           22044
#define INJ_TIME_TOL25           22045
#define INJ_TIME_TOL26           22046
#define SWITCH_PRES_TOL11        22047
#define SWITCH_PRES_TOL12        22048
#define SWITCH_PRES_TOL13        22049
#define SWITCH_PRES_TOL14        22050
#define SWITCH_PRES_TOL15        22051
#define SWITCH_PRES_TOL16        22052
#define SWITCH_PRES_TOL21        22053
#define SWITCH_PRES_TOL22        22054
#define SWITCH_PRES_TOL23        22055
#define SWITCH_PRES_TOL24        22056
#define SWITCH_PRES_TOL25        22057
#define SWITCH_PRES_TOL26        22058
#define SWITCH_POINT_TOL11       22059
#define SWITCH_POINT_TOL12       22060
#define SWITCH_POINT_TOL13       22061
#define SWITCH_POINT_TOL14       22062
#define SWITCH_POINT_TOL15       22063
#define SWITCH_POINT_TOL16       22064
#define SWITCH_POINT_TOL21       22065
#define SWITCH_POINT_TOL22       22066
#define SWITCH_POINT_TOL23       22067
#define SWITCH_POINT_TOL24       22068
#define SWITCH_POINT_TOL25       22069
#define SWITCH_POINT_TOL26       22070
#define XXTPOLSREF2              22071
#define XXTPOLSTOL2              22072
#define XXTPLASREF2              22073
#define XXTPLASTOL2              22074
#define XSSPLASREF2              22075
#define XSSPLASTOL2              22076
#define XSSINJREF2               22077
#define XSSINJTOL2               22078
#define XSTINJREF2               22079
#define XSTINJTOL2               22080
#define XSPINJREF2               22081
#define XSPINJTOL2               22082
#define XSPTINREF2               22083
#define XSPTINTOL2               22084
#define XSPTINMAXREF2            22085
#define XSPTINMAXTOL2            22086
#define XSTCYCREF2               22087
#define XSTCYCTOL2               22088
#define XMP16_2                  22089

/* Register fuer Seite 44 */
#define SPRITZ_WAHL              22100  /* Wahl Spritzeinheit              */
#define BETR_EINSPR              22101  /* Betriebsart Einspritzen         */
#define REIH_EINSPR              22102  /* Reihenfolge Einspritzen         */
#define BETR_AGG_BEW             22103  /* Betriebsart Aggregatbewegung    */
#define REIH_AGG_BEW             22104  /* Reihenfolge Aggregatbewegung    */

/* Register fuer Referenzwerte Trenddarstellung */
#define XTSPH10_REF              22200  /* Referenzwert Plastifizierweg */
#define XTSPH20_REF              22201  /* Referenzwert Plastweg Aggregat 2 */
#define INJ_TIME_REF11           22202  /* Referenzwert Einspritzzeit */
#define INJ_TIME_REF12           22203
#define INJ_TIME_REF13           22204
#define INJ_TIME_REF14           22205
#define INJ_TIME_REF15           22206
#define INJ_TIME_REF16           22207
#define INJ_TIME_REF21           22208
#define INJ_TIME_REF22           22209
#define INJ_TIME_REF23           22210
#define INJ_TIME_REF24           22211
#define INJ_TIME_REF25           22212
#define INJ_TIME_REF26           22213
#define SWITCH_PRES_REF11        22214  /* Referenzwert Umschaltdruck */
#define SWITCH_PRES_REF12        22215
#define SWITCH_PRES_REF13        22216
#define SWITCH_PRES_REF14        22217
#define SWITCH_PRES_REF15        22218
#define SWITCH_PRES_REF16        22219
#define SWITCH_PRES_REF21        22220
#define SWITCH_PRES_REF22        22221
#define SWITCH_PRES_REF23        22222
#define SWITCH_PRES_REF24        22223
#define SWITCH_PRES_REF25        22224
#define SWITCH_PRES_REF26        22225
#define SWITCH_POINT_REF11       22226  /* Referenzwert Umschaltpunkt */
#define SWITCH_POINT_REF12       22227
#define SWITCH_POINT_REF13       22228
#define SWITCH_POINT_REF14       22229
#define SWITCH_POINT_REF15       22230
#define SWITCH_POINT_REF16       22231
#define SWITCH_POINT_REF21       22232
#define SWITCH_POINT_REF22       22233
#define SWITCH_POINT_REF23       22234
#define SWITCH_POINT_REF24       22235
#define SWITCH_POINT_REF25       22236
#define SWITCH_POINT_REF26       22237
#define XXTDOS1_REF              22238
#define XXTDOS2_REF              22239
#define XXPFINM_REF              22240
#define XXPFI2M_REF              22241
#define XXTZYKL_REF              22242
#define XXTDOS3_REF              22243
#define XXTDOS4_REF              22244
#define XXPFI3M_REF              22245
#define XXPFI4M_REF              22246


#define TOL_SELECT_2             22250

#define  XMP17_2                 22260  /* Plastifizierweg */
#define  XMP18_2                 22261  /* Spritzkolbenflaeche Aggregat 2 */
#define  XMP26_2                 22262  /* Max. Spritzdruck Aggregat 2 */
#define  XMP29_2                 22263  /* Heizungsparametersatz Aggregat 2*/

/*BEGIN_EWIKON*/
#define XHC_MODE                 22270
#define XHC_STATUS               22271
#define XHC_CURRENT_TEMP         22272
#define XHC_TEMP                 22273
#define XHC_CURRENT              22274
#define XHC_IST                  22273
#define XHC_ABS                  22275
#define XHC_FUNCTION             22276

#define XHC_FUNCTION1            22281
#define XHC_FUNCTION2            22282
#define XHC_FUNCTION3            22283
#define XHC_FUNCTION4            22284
#define XHC_FUNCTION5            22285
#define XHC_FUNCTION6            22286
#define XHC_FUNCTION7            22287
#define XHC_FUNCTION8            22288
#define XHC_FUNCTION9            22289
#define XHC_FUNCTION10           22290
#define XHC_FUNCTION11           22291
#define XHC_FUNCTION12           22292
#define XHC_FUNCTION13           22293
#define XHC_FUNCTION14           22294
#define XHC_FUNCTION15           22295
#define XHC_FUNCTION16           22296
#define XHC_FUNCTION17           22297
#define XHC_FUNCTION18           22298
#define XHC_FUNCTION19           22299
#define XHC_FUNCTION20           22300
#define XHC_FUNCTION21           22301
#define XHC_FUNCTION22           22302
#define XHC_FUNCTION23           22303
#define XHC_FUNCTION24           22304
#define XHC_FUNCTION25           22305
#define XHC_FUNCTION26           22306
#define XHC_FUNCTION27           22307
#define XHC_FUNCTION28           22308
#define XHC_FUNCTION29           22309
#define XHC_FUNCTION30           22310
#define XHC_FUNCTION31           22311
#define XHC_FUNCTION32           22312
/*END_EWIKON*/

/* ---------------- Register fuer 5. Aggregat ---------------------------- */
#define XREG666_5                22350  /* Regenerationszusatz             */
#define XREG664_5                22351  /* Farbmittelzusatz                */
#define XREG672_5                22352  /* Treibmittelzusatz               */
#define XREG673_5                22353  /* Materialvorwaermung             */
#define XREG663_5                22354  /* Materialvorwaermzeit            */
#define XREG658_5                22355  /* Farbmischgeraet                 */
#define XREG657_5                22356  /* Materialfoerdergeraet           */
#define XREG682_5                22357  /* Schneckenzylinder               */
#define XREG683_5                22358  /* Duesenradius/Duesenlaenge       */
#define XREG691_5                22359  /* Duesenbohrung                   */
#define XREG684_5                22360  /* Tauchduese                      */
#define XREG689_5                22361  /* Wechselraeder/Hydromotor        */
#define XREG690_5                22362  /* Druck am Hydromotor             */
#define AGGPOS_5                 22363  /* Spritzzylinder                  */
#define XMP19_5                  22364  /* Schneckendrehzahl               */
#define XMP20_22_5               22365  /* Getriebe/Zaehnezahl             */
#define XMP25_AGG5               22366  /* Schneckendurchmesser            */
#define XMP28_5                  22367  /* Anzahl Heizzonen                */
#define XMP27_5                  22368  /* Zylinder-Ausfuehrung            */

#define NR_PLAST_5               22370  /* Anzahl Plastfizierstufen        */
#define XREG775_5                22371  /* Fuehlerart                      */
#define XREG777_5                22372  /* Stiftdurchmesser                */
#define XREG776_5                22373  /* Fuehlerempfindlichkeit          */
#define XMP23_5                  22374  /* Aggregattyp fuer Aggregat 5     */
#define XMP24_5                  22375  /* Aggregatgroesse fuer Aggregat 5 */
#define XMP19_KP_5               22376  /* Schneckendrehzahl max. Agg. 5   */
#define XMP20_5                  22377  /* Zaehnezahl klein fuer Agg. 5    */
#define XMP21_5                  22378  /* Zaehnezahl mittel fuer Agg.5    */
#define XMP22_5                  22379  /* Zaehnezahl gross fuer Agg.5     */
#define XMP25_1_5                22380  /* Snedurchmesser kleine Schnecke  */
#define XMP25_2_5                22381  /* Snedurchmesser mittlere Schnecke*/
#define XMP25_3_5                22382  /* Snedurchmesser grosse Schnecke  */
#define XTSPH50                  22383  /* plasitfizierweg Aggregat 5      */
#define PLAST_TIME_TOL_5         22384  /* Plastifizierzeit Toleranz Agg 5 */
#define XTSPH50_REF              22385  /* Referenzwert Plastweg     Agg.5 */
#define TOL_SELECT_5             22386
#define XMP17_5                  22387  /* Plastifizierweg                 */
#define XMP18_5                  22388  /* Spritzkolbenflaeche       Agg.5 */
#define XMP26_5                  22389  /* Max. Spritzdruck          Agg.5 */
#define XMP29_5                  22390  /* Heizungsparametersatz     Agg.5 */
#define WKZINN_TOL_AGG5          22391
#define SWITCH_PRES_TOL51        22392
#define SWITCH_PRES_TOL52        22393
#define SWITCH_PRES_TOL53        22394
#define SWITCH_PRES_TOL54        22395
#define SWITCH_PRES_TOL55        22396
#define SWITCH_PRES_TOL56        22397
#define INJ_TIME_TOL51           22398
#define INJ_TIME_TOL52           22399
#define INJ_TIME_TOL53           22400
#define INJ_TIME_TOL54           22401
#define INJ_TIME_TOL55           22402
#define INJ_TIME_TOL56           22403
#define SWITCH_POINT_TOL51       22404
#define SWITCH_POINT_TOL52       22405
#define SWITCH_POINT_TOL53       22406
#define SWITCH_POINT_TOL54       22407
#define SWITCH_POINT_TOL55       22408
#define SWITCH_POINT_TOL56       22409
#define SWITCH_PRES_REF51        22410  /* Referenzwert Umschaltdruck */
#define SWITCH_PRES_REF52        22411
#define SWITCH_PRES_REF53        22412
#define SWITCH_PRES_REF54        22413
#define SWITCH_PRES_REF55        22414
#define SWITCH_PRES_REF56        22415
#define INJ_TIME_REF51           22416  /* Referenzwert Einspritzzeit */
#define INJ_TIME_REF52           22417
#define INJ_TIME_REF53           22418
#define INJ_TIME_REF54           22419
#define INJ_TIME_REF55           22420
#define INJ_TIME_REF56           22421
#define SWITCH_POINT_REF51       22422  /* Referenzwert Umschaltpunkt */
#define SWITCH_POINT_REF52       22423
#define SWITCH_POINT_REF53       22424
#define SWITCH_POINT_REF54       22425
#define SWITCH_POINT_REF55       22426
#define SWITCH_POINT_REF56       22427
#define FILL_TIME5               22428  /* Istwert Fuellzeit (ohne Nachdruck) */
#define DWELL_PRES5              22429  /* Istwert Nachdruckstufe Agg.5 wg. Host */
#define XSPREF51                 22430
#define XSPREF52                 22431
#define XSPREF53                 22432
#define XSPREF54                 22433
#define XSPREF55                 22434
#define XSPREF56                 22435
#define XSPREF57                 22436
#define XSPREF58                 22437
#define XSPREF59                 22438
#define XSPREF5A                 22439
#define XSPTOL51                 22440
#define XSPTOL52                 22441
#define XSPTOL53                 22442
#define XSPTOL54                 22443
#define XSPTOL55                 22444
#define XSPTOL56                 22445
#define XSPTOL57                 22446
#define XSPTOL58                 22447
#define XSPTOL59                 22448
#define XSPTOL5A                 22449 
#define XXTPOLSREF5              22450
#define XXTPOLSTOL5              22451
#define XXTPLASREF5              22452
#define XXTPLASTOL5              22453
#define XSSPLASREF5              22454
#define XSSPLASTOL5              22455
#define XSSINJREF5               22456
#define XSSINJTOL5               22457
#define XSTINJREF5               22458
#define XSTINJTOL5               22459
#define XSPINJREF5               22460
#define XSPINJTOL5               22461
#define XSPTINREF5               22462
#define XSPTINTOL5               22463
#define XSPTINMAXREF5            22464
#define XSPTINMAXTOL5            22465
#define XSTCYCREF5               22466
#define XSTCYCTOL5               22467
#define XXTDOS5_REF              22468
#define XXPFI5M_REF              22469
#define INJ_SPEED_MAX5           22470  /* Max-Plaus fuer Spritzgeschw. Agg.5 */
#define INJ_SPEED_CONV5          22471  /* Konvertierungsfaktor Agg. 5        */
#define XMP25_5_S                22472
#define XMP18_5_S                22473
#define PROC_STEP_UNIT5          22474  /* Proze~schritte-Zuordnung Spritzeinheit 5 */
#define SSDOS5_VOL               22475  /* Soll Vol Plastifizierweg Agg5   */
#define SSUM51_VOL               22476  /* Soll Vol Dosierwegpunkt Agg5    */
#define SRSSVOR_5_VOL            22477  /* Soll Vol Schn.rueckzug vor Plast. Agg5 */
#define SRSSNACH_5_VOL           22478  /* Soll Vol Schn.rueckzug nach Plast. Agg5 */
#define SSPH51_VOL               22479  /* Soll Vol-Umschaltpkt Agg5 Stufe1 */
#define SSPH52_VOL               22480  /* Soll Vol-Umschaltpkt Agg5 Stufe2 */
#define SSPH53_VOL               22481  /* Soll Vol-Umschaltpkt Agg5 Stufe3 */
#define SSPH54_VOL               22482  /* Soll Vol-Umschaltpkt Agg5 Stufe4 */
#define SSPH55_VOL               22483  /* Soll Vol-Umschaltpkt Agg5 Stufe5 */
#define XTSPH50_VOL              22484  /* Soll Vol Tol Plast.weg Agg5 */
#define SWITCH_POINT_TOL51_VOL   22485  /* Soll Vol Tol Um.Point Agg1 Stufe 1*/
#define SWITCH_POINT_TOL52_VOL   22486  /* Soll Vol Tol Um.Point Agg1 Stufe 2*/ 
#define SWITCH_POINT_TOL53_VOL   22487  /* Soll Vol Tol Um.Point Agg1 Stufe 3*/ 
#define SWITCH_POINT_TOL54_VOL   22488  /* Soll Vol Tol Um.Point Agg1 Stufe 4*/ 
#define SWITCH_POINT_TOL55_VOL   22489  /* Soll Vol Tol Um.Point Agg1 Stufe 5*/ 
#define SWITCH_POINT_TOL56_VOL   22490  /* Soll Vol Tol Um.Point Agg1 Polster*/ 
#define XSPH50_VOL               22491  /* Ist Vol-Plastifizierweg Agg5    */
#define XSPH51_VOL               22492  /* Ist Vol-Umschaltpkt Agg5 Stufe1 */
#define XSPH52_VOL               22493  /* Ist Vol-Umschaltpkt Agg5 Stufe2 */
#define XSPH53_VOL               22494  /* Ist Vol-Umschaltpkt Agg5 Stufe3 */
#define XSPH54_VOL               22495  /* Ist Vol-Umschaltpkt Agg5 Stufe4 */
#define XSPH55_VOL               22496  /* Ist Vol-Umschaltpkt Agg5 Stufe5 */
#define XSPOL5_VOL               22497  /* Ist Vol-Polster Agg5 Stufe6 */
#define SWITCH_POINT_REF51_VOL   22498  /* Umschaltpunkt Agg5 Stufe1 */
#define SWITCH_POINT_REF52_VOL   22499  /* Umschaltpunkt Agg5 Stufe2 */
#define SWITCH_POINT_REF53_VOL   22500  /* Umschaltpunkt Agg5 Stufe3 */
#define SWITCH_POINT_REF54_VOL   22501  /* Umschaltpunkt Agg5 Stufe4 */
#define SWITCH_POINT_REF55_VOL   22502  /* Umschaltpunkt Agg5 Stufe5 */
#define SWITCH_POINT_REF56_VOL   22503  /* Umschaltpunkt Agg5 Stufe6 */
#define XTSPH50_REF_VOL          22504  /* Plastifizierweg Agg5 */
#define SPST51_SPEC              22505  /* Soll specifisch 1.Staudruck Agg5 */
#define SPST52_SPEC              22506  /* Soll specifisch 2.Staudruck Agg5 */
#define SPSTH5_SPEC              22507  /* Soll specifisch Staudruckhand Agg5 */
#define SPPH51_SPEC              22508  /* Soll specifisch Einspritzdruck Agg5 Stufe 1*/
#define SPPH52_SPEC              22509  /* Soll specifisch Einspritzdruck Agg5 Stufe 2*/
#define SPPH53_SPEC              22510  /* Soll specifisch Einspritzdruck Agg5 Stufe 3*/
#define SPPH54_SPEC              22511  /* Soll specifisch Einspritzdruck Agg5 Stufe 4*/
#define SPPH55_SPEC              22512  /* Soll specifisch Einspritzdruck Agg5 Stufe 5*/
#define SPPH56_SPEC              22513  /* Soll specifisch Einspritzdruck Agg5 Stufe 6*/
#define SPUM51_SPEC              22514  /* Soll specifisch Umschaltdruck Agg5 Stufe 1*/
#define SPUM52_SPEC              22515  /* Soll specifisch Umschaltdruck Agg5 Stufe 2*/
#define SPUM53_SPEC              22516  /* Soll specifisch Umschaltdruck Agg5 Stufe 3*/
#define SPUM54_SPEC              22517  /* Soll specifisch Umschaltdruck Agg5 Stufe 4*/
#define SPUM55_SPEC              22518  /* Soll specifisch Umschaltdruck Agg5 Stufe 5*/
#define SWITCH_PRES_TOL51_SPEC   22519  /* Soll specifisch Tol Einspritzdr. Agg5 Stufe 1*/
#define SWITCH_PRES_TOL52_SPEC   22520  /* Soll specifisch Tol Einspritzdr. Agg5 Stufe 2*/
#define SWITCH_PRES_TOL53_SPEC   22521  /* Soll specifisch Tol Einspritzdr. Agg5 Stufe 3*/
#define SWITCH_PRES_TOL54_SPEC   22522  /* Soll specifisch Tol Einspritzdr. Agg5 Stufe 4*/
#define SWITCH_PRES_TOL55_SPEC   22523  /* Soll specifisch Tol Einspritzdr. Agg5 Stufe 5*/
#define SWITCH_PRES_TOL56_SPEC   22524  /* Soll specifisch Tol Einspritzdr. Agg5 Stufe 6*/
#define XPPH51_SPEC              22525  /* Ist specifisch Einspritzdruck Agg5 Stufe 1*/
#define XPPH52_SPEC              22526  /* Ist specifisch Einspritzdruck Agg5 Stufe 2*/
#define XPPH53_SPEC              22527  /* Ist specifisch Einspritzdruck Agg5 Stufe 3*/
#define XPPH54_SPEC              22528  /* Ist specifisch Einspritzdruck Agg5 Stufe 4*/
#define XPPH55_SPEC              22529  /* Ist specifisch Einspritzdruck Agg5 Stufe 5*/
#define XPPH56_SPEC              22530  /* Ist specifisch Einspritzdruck Agg5 Stufe 6*/
#define SWITCH_PRES_REF51_SPEC   22531  /* Einspritzdruck Agg5 Stufe1 */ 
#define SWITCH_PRES_REF52_SPEC   22532  /* Einspritzdruck Agg5 Stufe2 */ 
#define SWITCH_PRES_REF53_SPEC   22533  /* Einspritzdruck Agg5 Stufe3 */ 
#define SWITCH_PRES_REF54_SPEC   22534  /* Einspritzdruck Agg5 Stufe4 */ 
#define SWITCH_PRES_REF55_SPEC   22535  /* Einspritzdruck Agg5 Stufe5 */ 
#define SWITCH_PRES_REF56_SPEC   22536  /* Einspritzdruck Agg5 Stufe6 */ 
#define SWPL51_VOL               22537  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL52_VOL               22538  /* Soll Volumen Geschwindigk. mm/s  */
#define SRSVVOR_5_VOL            22539  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVNACH_5_VOL           22540  /* Soll Volumen Geschwindigk. ccm/s  */
#define SVPH51_VOL               22541  /* Soll Vol-Geschwindigk. ccm/s Agg5 Stufe1 */
#define SVPH52_VOL               22542  /* Soll Vol-Geschwindigk. ccm/s Agg5 Stufe2 */
#define SVPH53_VOL               22543  /* Soll Vol-Geschwindigk. ccm/s Agg5 Stufe3 */
#define SVPH54_VOL               22544  /* Soll Vol-Geschwindigk. ccm/s Agg5 Stufe4 */
#define SVPH55_VOL               22545  /* Soll Vol-Geschwindigk. ccm/s Agg5 Stufe5 */
#define SVPH56_VOL               22546  /* Soll Vol-Geschwindigk. ccm/s Agg5 Stufe6 */
#define XMP16_5                  22547

/* ---------------- Register fuer 6. Aggregat ---------------------------- */
#define XREG666_6                22550  /* Regenerationszusatz             */
#define XREG664_6                22551  /* Farbmittelzusatz                */
#define XREG672_6                22552  /* Treibmittelzusatz               */
#define XREG673_6                22553  /* Materialvorwaermung             */
#define XREG663_6                22554  /* Materialvorwaermzeit            */
#define XREG658_6                22555  /* Farbmischgeraet                 */
#define XREG657_6                22556  /* Materialfoerdergeraet           */
#define XREG682_6                22557  /* Schneckenzylinder               */
#define XREG683_6                22558  /* Duesenradius/Duesenlaenge       */
#define XREG691_6                22559  /* Duesenbohrung                   */
#define XREG684_6                22560  /* Tauchduese                      */
#define XREG689_6                22561  /* Wechselraeder/Hydromotor        */
#define XREG690_6                22562  /* Druck am Hydromotor             */
#define AGGPOS_6                 22563  /* Spritzzylinder                  */
#define XMP19_6                  22564  /* Schneckendrehzahl               */
#define XMP20_22_6               22565  /* Getriebe/Zaehnezahl             */
#define XMP25_AGG6               22566  /* Schneckendurchmesser            */
#define XMP28_6                  22567  /* Anzahl Heizzonen                */
#define XMP27_6                  22568  /* Zylinder-Ausfuehrung            */

#define NR_PLAST_6               22570  /* Anzahl Plastfizierstufen        */
#define XREG775_6                22571  /* Fuehlerart                      */
#define XREG777_6                22572  /* Stiftdurchmesser                */
#define XREG776_6                22573  /* Fuehlerempfindlichkeit          */
#define XMP23_6                  22574  /* Aggregattyp fuer Aggregat 6     */
#define XMP24_6                  22575  /* Aggregatgroesse fuer Aggregat 6 */
#define XMP19_KP_6               22576  /* Schneckendrehzahl max. Agg. 6   */
#define XMP20_6                  22577  /* Zaehnezahl klein fuer Agg. 6    */
#define XMP21_6                  22578  /* Zaehnezahl mittel fuer Agg.6    */
#define XMP22_6                  22579  /* Zaehnezahl gross fuer Agg.6     */
#define XMP25_1_6                22580  /* Snedurchmesser kleine Schnecke  */
#define XMP25_2_6                22581  /* Snedurchmesser mittlere Schnecke*/
#define XMP25_3_6                22582  /* Snedurchmesser grosse Schnecke  */
#define XTSPH60                  22583  /* plasitfizierweg Aggregat 6      */
#define PLAST_TIME_TOL_6         22584  /* Plastifizierzeit Toleranz Agg 6 */
#define XTSPH60_REF              22585  /* Referenzwert Plastweg     Agg.6 */
#define TOL_SELECT_6             22586
#define XMP17_6                  22587  /* Plastifizierweg                 */
#define XMP18_6                  22588  /* Spritzkolbenflaeche       Agg.6 */
#define XMP26_6                  22589  /* Max. Spritzdruck          Agg.6 */
#define XMP29_6                  22590  /* Heizungsparametersatz     Agg.6 */
#define WKZINN_TOL_AGG6          22591
#define SWITCH_PRES_TOL61        22592
#define SWITCH_PRES_TOL62        22593
#define SWITCH_PRES_TOL63        22594
#define SWITCH_PRES_TOL64        22595
#define SWITCH_PRES_TOL65        22596
#define SWITCH_PRES_TOL66        22597
#define INJ_TIME_TOL61           22598
#define INJ_TIME_TOL62           22599
#define INJ_TIME_TOL63           22600
#define INJ_TIME_TOL64           22601
#define INJ_TIME_TOL65           22602
#define INJ_TIME_TOL66           22603
#define SWITCH_POINT_TOL61       22604
#define SWITCH_POINT_TOL62       22605
#define SWITCH_POINT_TOL63       22606
#define SWITCH_POINT_TOL64       22607
#define SWITCH_POINT_TOL65       22608
#define SWITCH_POINT_TOL66       22609
#define SWITCH_PRES_REF61        22610  /* Referenzwert Umschaltdruck */
#define SWITCH_PRES_REF62        22611
#define SWITCH_PRES_REF63        22612
#define SWITCH_PRES_REF64        22613
#define SWITCH_PRES_REF65        22614
#define SWITCH_PRES_REF66        22615
#define INJ_TIME_REF61           22616  /* Referenzwert Einspritzzeit */
#define INJ_TIME_REF62           22617
#define INJ_TIME_REF63           22618
#define INJ_TIME_REF64           22619
#define INJ_TIME_REF65           22620
#define INJ_TIME_REF66           22621
#define SWITCH_POINT_REF61       22622  /* Referenzwert Umschaltpunkt */
#define SWITCH_POINT_REF62       22623
#define SWITCH_POINT_REF63       22624
#define SWITCH_POINT_REF64       22625
#define SWITCH_POINT_REF65       22626
#define SWITCH_POINT_REF66       22627
#define FILL_TIME6               22628  /* Istwert Fuellzeit (ohne Nachdruck) */
#define DWELL_PRES6              22629  /* Istwert Nachdruckstufe Agg.6 wg. Host */
#define XSPREF61                 22630
#define XSPREF62                 22631
#define XSPREF63                 22632
#define XSPREF64                 22633
#define XSPREF65                 22634
#define XSPREF66                 22635
#define XSPREF67                 22636
#define XSPREF68                 22637
#define XSPREF69                 22638
#define XSPREF6A                 22639
#define XSPTOL61                 22640
#define XSPTOL62                 22641
#define XSPTOL63                 22642
#define XSPTOL64                 22643
#define XSPTOL65                 22644
#define XSPTOL66                 22645
#define XSPTOL67                 22646
#define XSPTOL68                 22647
#define XSPTOL69                 22648
#define XSPTOL6A                 22649 
#define XXTPOLSREF6              22650
#define XXTPOLSTOL6              22651
#define XXTPLASREF6              22652
#define XXTPLASTOL6              22653
#define XSSPLASREF6              22654
#define XSSPLASTOL6              22655
#define XSSINJREF6               22656
#define XSSINJTOL6               22657
#define XSTINJREF6               22658
#define XSTINJTOL6               22659
#define XSPINJREF6               22660
#define XSPINJTOL6               22661
#define XSPTINREF6               22662
#define XSPTINTOL6               22663
#define XSPTINMAXREF6            22664
#define XSPTINMAXTOL6            22665
#define XSTCYCREF6               22666
#define XSTCYCTOL6               22667
#define XXTDOS6_REF              22668
#define XXPFI6M_REF              22669
#define INJ_SPEED_MAX6           22670  /* Max-Plaus fuer Spritzgeschw. Agg.6 */
#define INJ_SPEED_CONV6          22671  /* Konvertierungsfaktor Agg. 6        */
#define XMP25_6_S                22672
#define XMP18_6_S                22673
#define PROC_STEP_UNIT6          22674  /* Proze~schritte-Zuordnung Spritzeinheit 6 */
#define SSDOS6_VOL               22675  /* Soll Vol Plastifizierweg Agg6   */
#define SSUM61_VOL               22676  /* Soll Vol Dosierwegpunkt Agg6    */
#define SRSSVOR_6_VOL            22677  /* Soll Vol Schn.rueckzug vor Plast. Agg6 */
#define SRSSNACH_6_VOL           22678  /* Soll Vol Schn.rueckzug nach Plast. Agg6 */
#define SSPH61_VOL               22679  /* Soll Vol-Umschaltpkt Agg6 Stufe1 */
#define SSPH62_VOL               22680  /* Soll Vol-Umschaltpkt Agg6 Stufe2 */
#define SSPH63_VOL               22681  /* Soll Vol-Umschaltpkt Agg6 Stufe3 */
#define SSPH64_VOL               22682  /* Soll Vol-Umschaltpkt Agg6 Stufe4 */
#define SSPH65_VOL               22683  /* Soll Vol-Umschaltpkt Agg6 Stufe5 */
#define XTSPH60_VOL              22684  /* Soll Vol Tol Plast.weg Agg6 */
#define SWITCH_POINT_TOL61_VOL   22685  /* Soll Vol Tol Um.Point Agg6 Stufe 1*/
#define SWITCH_POINT_TOL62_VOL   22686  /* Soll Vol Tol Um.Point Agg6 Stufe 2*/ 
#define SWITCH_POINT_TOL63_VOL   22687  /* Soll Vol Tol Um.Point Agg6 Stufe 3*/ 
#define SWITCH_POINT_TOL64_VOL   22688  /* Soll Vol Tol Um.Point Agg6 Stufe 4*/ 
#define SWITCH_POINT_TOL65_VOL   22689  /* Soll Vol Tol Um.Point Agg6 Stufe 5*/ 
#define SWITCH_POINT_TOL66_VOL   22690  /* Soll Vol Tol Um.Point Agg6 Polster*/ 
#define XSPH60_VOL               22691  /* Ist Vol-Plastifizierweg Agg6    */
#define XSPH61_VOL               22692  /* Ist Vol-Umschaltpkt Agg6 Stufe1 */
#define XSPH62_VOL               22693  /* Ist Vol-Umschaltpkt Agg6 Stufe2 */
#define XSPH63_VOL               22694  /* Ist Vol-Umschaltpkt Agg6 Stufe3 */
#define XSPH64_VOL               22695  /* Ist Vol-Umschaltpkt Agg6 Stufe4 */
#define XSPH65_VOL               22696  /* Ist Vol-Umschaltpkt Agg6 Stufe5 */
#define XSPOL6_VOL               22697  /* Ist Vol-Polster Agg6 Stufe6 */
#define SWITCH_POINT_REF61_VOL   22698  /* Umschaltpunkt Agg6 Stufe1 */
#define SWITCH_POINT_REF62_VOL   22699  /* Umschaltpunkt Agg6 Stufe2 */
#define SWITCH_POINT_REF63_VOL   22700  /* Umschaltpunkt Agg6 Stufe3 */
#define SWITCH_POINT_REF64_VOL   22701  /* Umschaltpunkt Agg6 Stufe4 */
#define SWITCH_POINT_REF65_VOL   22702  /* Umschaltpunkt Agg6 Stufe5 */
#define SWITCH_POINT_REF66_VOL   22703  /* Umschaltpunkt Agg6 Stufe6 */
#define XTSPH60_REF_VOL          22704  /* Plastifizierweg Agg6 */
#define SPST61_SPEC              22705  /* Soll specifisch 1.Staudruck Agg6 */
#define SPST62_SPEC              22706  /* Soll specifisch 2.Staudruck Agg6 */
#define SPSTH6_SPEC              22707  /* Soll specifisch Staudruckhand Agg6 */
#define SPPH61_SPEC              22708  /* Soll specifisch Einspritzdruck Agg6 Stufe 1*/
#define SPPH62_SPEC              22709  /* Soll specifisch Einspritzdruck Agg6 Stufe 2*/
#define SPPH63_SPEC              22710  /* Soll specifisch Einspritzdruck Agg6 Stufe 3*/
#define SPPH64_SPEC              22711  /* Soll specifisch Einspritzdruck Agg6 Stufe 4*/
#define SPPH65_SPEC              22712  /* Soll specifisch Einspritzdruck Agg6 Stufe 5*/
#define SPPH66_SPEC              22713  /* Soll specifisch Einspritzdruck Agg6 Stufe 6*/
#define SPUM61_SPEC              22714  /* Soll specifisch Umschaltdruck Agg6 Stufe 1*/
#define SPUM62_SPEC              22715  /* Soll specifisch Umschaltdruck Agg6 Stufe 2*/
#define SPUM63_SPEC              22716  /* Soll specifisch Umschaltdruck Agg6 Stufe 3*/
#define SPUM64_SPEC              22717  /* Soll specifisch Umschaltdruck Agg6 Stufe 4*/
#define SPUM65_SPEC              22718  /* Soll specifisch Umschaltdruck Agg6 Stufe 5*/
#define SWITCH_PRES_TOL61_SPEC   22719  /* Soll specifisch Tol Einspritzdr. Agg6 Stufe 1*/
#define SWITCH_PRES_TOL62_SPEC   22720  /* Soll specifisch Tol Einspritzdr. Agg6 Stufe 2*/
#define SWITCH_PRES_TOL63_SPEC   22721  /* Soll specifisch Tol Einspritzdr. Agg6 Stufe 3*/
#define SWITCH_PRES_TOL64_SPEC   22722  /* Soll specifisch Tol Einspritzdr. Agg6 Stufe 4*/
#define SWITCH_PRES_TOL65_SPEC   22723  /* Soll specifisch Tol Einspritzdr. Agg6 Stufe 5*/
#define SWITCH_PRES_TOL66_SPEC   22724  /* Soll specifisch Tol Einspritzdr. Agg6 Stufe 6*/
#define XPPH61_SPEC              22725  /* Ist specifisch Einspritzdruck Agg6 Stufe 1*/
#define XPPH62_SPEC              22726  /* Ist specifisch Einspritzdruck Agg6 Stufe 2*/
#define XPPH63_SPEC              22727  /* Ist specifisch Einspritzdruck Agg6 Stufe 3*/
#define XPPH64_SPEC              22728  /* Ist specifisch Einspritzdruck Agg6 Stufe 4*/
#define XPPH65_SPEC              22729  /* Ist specifisch Einspritzdruck Agg6 Stufe 5*/
#define XPPH66_SPEC              22730  /* Ist specifisch Einspritzdruck Agg6 Stufe 6*/
#define SWITCH_PRES_REF61_SPEC   22731  /* Einspritzdruck Agg6 Stufe1 */ 
#define SWITCH_PRES_REF62_SPEC   22732  /* Einspritzdruck Agg6 Stufe2 */ 
#define SWITCH_PRES_REF63_SPEC   22733  /* Einspritzdruck Agg6 Stufe3 */ 
#define SWITCH_PRES_REF64_SPEC   22734  /* Einspritzdruck Agg6 Stufe4 */ 
#define SWITCH_PRES_REF65_SPEC   22735  /* Einspritzdruck Agg6 Stufe5 */ 
#define SWITCH_PRES_REF66_SPEC   22736  /* Einspritzdruck Agg6 Stufe6 */ 
#define SWPL61_VOL               22737  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL62_VOL               22738  /* Soll Volumen Geschwindigk. mm/s  */
#define SRSVVOR_6_VOL            22739  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVNACH_6_VOL           22740  /* Soll Volumen Geschwindigk. ccm/s  */
#define SVPH61_VOL               22741  /* Soll Vol-Geschwindigk. ccm/s Agg6 Stufe1 */
#define SVPH62_VOL               22742  /* Soll Vol-Geschwindigk. ccm/s Agg6 Stufe2 */
#define SVPH63_VOL               22743  /* Soll Vol-Geschwindigk. ccm/s Agg6 Stufe3 */
#define SVPH64_VOL               22744  /* Soll Vol-Geschwindigk. ccm/s Agg6 Stufe4 */
#define SVPH65_VOL               22745  /* Soll Vol-Geschwindigk. ccm/s Agg6 Stufe5 */
#define SVPH66_VOL               22746  /* Soll Vol-Geschwindigk. ccm/s Agg6 Stufe6 */
#define XMP16_6                  22747


/* ---------------- Register fuer 2. Aggregat ---------------------------- */
#define XSPREF21                 22900
#define XSPREF22                 22901
#define XSPREF23                 22902
#define XSPREF24                 22903
#define XSPREF25                 22904
#define XSPREF26                 22905
#define XSPREF27                 22906
#define XSPREF28                 22907
#define XSPREF29                 22908
#define XSPREF2A                 22909
#define XSPTOL21                 22910
#define XSPTOL22                 22911
#define XSPTOL23                 22912
#define XSPTOL24                 22913
#define XSPTOL25                 22914
#define XSPTOL26                 22915
#define XSPTOL27                 22916
#define XSPTOL28                 22917
#define XSPTOL29                 22918
#define XSPTOL2A                 22919 

/* ---------------- Register fuer 3. Aggregat ---------------------------- */
#define XREG666_3                23000  /* Regenerationszusatz             */
#define XREG664_3                23001  /* Farbmittelzusatz                */
#define XREG672_3                23002  /* Treibmittelzusatz               */
#define XREG673_3                23003  /* Materialvorwaermung             */
#define XREG663_3                23004  /* Materialvorwaermzeit            */
#define XREG658_3                23005  /* Farbmischgeraet                 */
#define XREG657_3                23006  /* Materialfoerdergeraet           */
#define XREG682_3                23007  /* Schneckenzylinder               */
#define XREG683_3                23008  /* Duesenradius/Duesenlaenge       */
#define XREG691_3                23009  /* Duesenbohrung                   */
#define XREG684_3                23010  /* Tauchduese                      */
#define XREG689_3                23011  /* Wechselraeder/Hydromotor        */
#define XREG690_3                23012  /* Druck am Hydromotor             */
#define AGGPOS_3                 23013  /* Spritzzylinder                  */
#define XMP19_3                  23014  /* Schneckendrehzahl               */
#define XMP20_22_3               23015  /* Getriebe/Zaehnezahl             */
#define XMP25_AGG3               23016  /* Schneckendurchmesser            */
#define XMP28_3                  23017  /* Anzahl Heizzonen                */
#define XMP27_3                  23018  /* Zylinder-Ausfuehrung            */

#define NR_PLAST_3               23020  /* Anzahl Plastfizierstufen        */
#define XREG775_3                23021  /* Fuehlerart                      */
#define XREG777_3                23022  /* Stiftdurchmesser                */
#define XREG776_3                23023  /* Fuehlerempfindlichkeit          */
#define XMP23_3                  23024  /* Aggregattyp fuer          Agg.3 */
#define XMP24_3                  23025  /* Aggregatgroesse fuer      Agg.3 */
#define XMP19_KP_3               23026  /* Schneckendrehzahl max.    Agg.3 */
#define XMP20_3                  23027  /* Zaehnezahl klein fuer     Agg.3 */
#define XMP21_3                  23028  /* Zaehnezahl mittel fuer    Agg.3 */
#define XMP22_3                  23029  /* Zaehnezahl gross fuer     Agg.3 */
#define XMP25_1_3                23030  /* Snedurchmesser kleine Schnecke  */
#define XMP25_2_3                23031  /* Snedurchmesser mittlere Schnecke*/
#define XMP25_3_3                23032  /* Snedurchmesser grosse Schnecke  */
#define XTSPH30                  23033  /* plasitfizierweg           Agg.3 */
#define PLAST_TIME_TOL_3         23034  /* Plastifizierzeit Toleranz Agg 3 */
#define XTSPH30_REF              23035  /* Referenzwert Plastweg     Agg.3 */
#define TOL_SELECT_3             23036
#define XMP17_3                  23037  /* Plastifizierweg                 */
#define XMP18_3                  23038  /* Spritzkolbenflaeche       Agg.3 */
#define XMP26_3                  23039  /* Max. Spritzdruck          Agg.3 */
#define XMP29_3                  23040  /* Heizungsparametersatz     Agg.3 */
#define WKZINN_TOL_AGG3          23041
#define SWITCH_PRES_TOL31        23042
#define SWITCH_PRES_TOL32        23043
#define SWITCH_PRES_TOL33        23044
#define SWITCH_PRES_TOL34        23045
#define SWITCH_PRES_TOL35        23046
#define SWITCH_PRES_TOL36        23047
#define INJ_TIME_TOL31           23048
#define INJ_TIME_TOL32           23049
#define INJ_TIME_TOL33           23050
#define INJ_TIME_TOL34           23051
#define INJ_TIME_TOL35           23052
#define INJ_TIME_TOL36           23053
#define SWITCH_POINT_TOL31       23054
#define SWITCH_POINT_TOL32       23055
#define SWITCH_POINT_TOL33       23056
#define SWITCH_POINT_TOL34       23057
#define SWITCH_POINT_TOL35       23058
#define SWITCH_POINT_TOL36       23059
#define SWITCH_PRES_REF31        23060  /* Referenzwert Umschaltdruck */
#define SWITCH_PRES_REF32        23061
#define SWITCH_PRES_REF33        23062
#define SWITCH_PRES_REF34        23063
#define SWITCH_PRES_REF35        23064
#define SWITCH_PRES_REF36        23065
#define INJ_TIME_REF31           23066  /* Referenzwert Einspritzzeit */
#define INJ_TIME_REF32           23067
#define INJ_TIME_REF33           23068
#define INJ_TIME_REF34           23069
#define INJ_TIME_REF35           23070
#define INJ_TIME_REF36           23071
#define SWITCH_POINT_REF31       23072  /* Referenzwert Umschaltpunkt */
#define SWITCH_POINT_REF32       23073
#define SWITCH_POINT_REF33       23074
#define SWITCH_POINT_REF34       23075
#define SWITCH_POINT_REF35       23076
#define SWITCH_POINT_REF36       23077
#define FILL_TIME3               23078  /* Istwert Fuellzeit (ohne Nachdruck) */
#define DWELL_PRES3              23079  /* Istwert Nachdruckstufe Agg.3 wg. Host */
#define XSPREF31                 23080
#define XSPREF32                 23081
#define XSPREF33                 23082
#define XSPREF34                 23083
#define XSPREF35                 23084
#define XSPREF36                 23085
#define XSPREF37                 23086
#define XSPREF38                 23087
#define XSPREF39                 23088
#define XSPREF3A                 23089
#define XSPTOL31                 23090
#define XSPTOL32                 23091
#define XSPTOL33                 23092
#define XSPTOL34                 23093
#define XSPTOL35                 23094
#define XSPTOL36                 23095
#define XSPTOL37                 23096
#define XSPTOL38                 23097
#define XSPTOL39                 23098
#define XSPTOL3A                 23099 
#define XXTPOLSREF3              23100
#define XXTPOLSTOL3              23101
#define XXTPLASREF3              23102
#define XXTPLASTOL3              23103
#define XSSPLASREF3              23104
#define XSSPLASTOL3              23105
#define XSSINJREF3               23106
#define XSSINJTOL3               23107
#define XSTINJREF3               23108
#define XSTINJTOL3               23109
#define XSPINJREF3               23110
#define XSPINJTOL3               23111
#define XSPTINREF3               23112
#define XSPTINTOL3               23113
#define XSPTINMAXREF3            23114
#define XSPTINMAXTOL3            23115
#define XSTCYCREF3               23116
#define XSTCYCTOL3               23117
#define XMP16_3                  23118

                                  
/* ---------------- Register fuer 4. Aggregat ---------------------------- */
#define XREG666_4                23200  /* Regenerationszusatz             */
#define XREG664_4                23201  /* Farbmittelzusatz                */
#define XREG672_4                23202  /* Treibmittelzusatz               */
#define XREG673_4                23203  /* Materialvorwaermung             */
#define XREG663_4                23204  /* Materialvorwaermzeit            */
#define XREG658_4                23205  /* Farbmischgeraet                 */
#define XREG657_4                23206  /* Materialfoerdergeraet           */
#define XREG682_4                23207  /* Schneckenzylinder               */
#define XREG683_4                23208  /* Duesenradius/Duesenlaenge       */
#define XREG691_4                23209  /* Duesenbohrung                   */
#define XREG684_4                23210  /* Tauchduese                      */
#define XREG689_4                23211  /* Wechselraeder/Hydromotor        */
#define XREG690_4                23212  /* Druck am Hydromotor             */
#define AGGPOS_4                 23213  /* Spritzzylinder                  */
#define XMP19_4                  23214  /* Schneckendrehzahl               */
#define XMP20_22_4               23215  /* Getriebe/Zaehnezahl             */
#define XMP25_AGG4               23216  /* Schneckendurchmesser            */
#define XMP28_4                  23217  /* Anzahl Heizzonen                */
#define XMP27_4                  23218  /* Zylinder-Ausfuehrung            */

#define NR_PLAST_4               23220  /* Anzahl Plastfizierstufen        */
#define XREG775_4                23221  /* Fuehlerart                      */
#define XREG777_4                23222  /* Stiftdurchmesser                */
#define XREG776_4                23223  /* Fuehlerempfindlichkeit          */
#define XMP23_4                  23224  /* Aggregattyp fuer          Agg.4 */
#define XMP24_4                  23225  /* Aggregatgroesse fuer      Agg.4 */
#define XMP19_KP_4               23226  /* Schneckendrehzahl max.    Agg.4 */
#define XMP20_4                  23227  /* Zaehnezahl klein fuer     Agg.4 */
#define XMP21_4                  23228  /* Zaehnezahl mittel fuer    Agg.4 */
#define XMP22_4                  23229  /* Zaehnezahl gross fuer     Agg.4 */
#define XMP25_1_4                23230  /* Snedurchmesser kleine Schnecke  */
#define XMP25_2_4                23231  /* Snedurchmesser mittlere Schnecke*/
#define XMP25_3_4                23232  /* Snedurchmesser grosse Schnecke  */
#define XTSPH40                  23233  /* plasitfizierweg           Agg.4 */
#define PLAST_TIME_TOL_4         23234  /* Plastifizierzeit Toleranz Agg.4 */
#define XTSPH40_REF              23235  /* Referenzwert Plastweg     Agg.4 */
#define TOL_SELECT_4             23236
#define XMP17_4                  23237  /* Plastifizierweg                 */
#define XMP18_4                  23238  /* Spritzkolbenflaeche       Agg.4 */
#define XMP26_4                  23239  /* Max. Spritzdruck          Agg.4 */
#define XMP29_4                  23240  /* Heizungsparametersatz     Agg.4 */
#define WKZINN_TOL_AGG4          23241
#define SWITCH_PRES_TOL41        23242
#define SWITCH_PRES_TOL42        23243
#define SWITCH_PRES_TOL43        23244
#define SWITCH_PRES_TOL44        23245
#define SWITCH_PRES_TOL45        23246
#define SWITCH_PRES_TOL46        23247
#define INJ_TIME_TOL41           23248
#define INJ_TIME_TOL42           23249
#define INJ_TIME_TOL43           23250
#define INJ_TIME_TOL44           23251
#define INJ_TIME_TOL45           23252
#define INJ_TIME_TOL46           23253
#define SWITCH_POINT_TOL41       23254
#define SWITCH_POINT_TOL42       23255
#define SWITCH_POINT_TOL43       23256
#define SWITCH_POINT_TOL44       23257
#define SWITCH_POINT_TOL45       23258
#define SWITCH_POINT_TOL46       23259
#define SWITCH_PRES_REF41        23260  /* Referenzwert Umschaltdruck */
#define SWITCH_PRES_REF42        23261
#define SWITCH_PRES_REF43        23262
#define SWITCH_PRES_REF44        23263
#define SWITCH_PRES_REF45        23264
#define SWITCH_PRES_REF46        23265
#define INJ_TIME_REF41           23266  /* Referenzwert Einspritzzeit */
#define INJ_TIME_REF42           23267
#define INJ_TIME_REF43           23268
#define INJ_TIME_REF44           23269
#define INJ_TIME_REF45           23270
#define INJ_TIME_REF46           23271
#define SWITCH_POINT_REF41       23272  /* Referenzwert Umschaltpunkt */
#define SWITCH_POINT_REF42       23273
#define SWITCH_POINT_REF43       23274
#define SWITCH_POINT_REF44       23275
#define SWITCH_POINT_REF45       23276
#define SWITCH_POINT_REF46       23277
#define INJ_SPEED_MAX4           23278  /* Max-Plaus fuer Spritzgeschw. Agg.4*/
#define FILL_TIME4               23279  /* Istwert Fuellzeit (ohne Nachdruck) */
#define DWELL_PRES4              23280  /* Istwert Nachdruckstufe Agg.4 wg. Host */
#define XMP25_4_S                23281
#define XMP18_4_S                23282
#define XSPREF41                 23283
#define XSPREF42                 23284
#define XSPREF43                 23285
#define XSPREF44                 23286
#define XSPREF45                 23287
#define XSPREF46                 23288
#define XSPREF47                 23289
#define XSPREF48                 23290
#define XSPREF49                 23291
#define XSPREF4A                 23292
#define XSPTOL41                 23293
#define XSPTOL42                 23294
#define XSPTOL43                 23295
#define XSPTOL44                 23296
#define XSPTOL45                 23297
#define XSPTOL46                 23298
#define XSPTOL47                 23299
#define XSPTOL48                 23300
#define XSPTOL49                 23301
#define XSPTOL4A                 23302 
#define XXTPOLSREF4              23303
#define XXTPOLSTOL4              23304
#define XXTPLASREF4              23305
#define XXTPLASTOL4              23306
#define XSSPLASREF4              23307
#define XSSPLASTOL4              23308
#define XSSINJREF4               23309
#define XSSINJTOL4               23310
#define XSTINJREF4               23311
#define XSTINJTOL4               23312
#define XSPINJREF4               23313
#define XSPINJTOL4               23314
#define XSPTINREF4               23315
#define XSPTINTOL4               23316
#define XSPTINMAXREF4            23317
#define XSPTINMAXTOL4            23318
#define XSTCYCREF4               23319
#define XSTCYCTOL4               23320
#define XMP16_4                  23321
                                   

/* ---------------- Darstellungsreg. Weg/Volumen -------------------------- */
#define AWV_PLASTWEG_IST         23330
#define AWV_WEGPUNKT             23331
#define AWV_SRS_VORPL            23332
#define AWV_SRS_NACHPL           23333
#define AWV_SWITCH_POINT_SOLL    23334
#define AWV_PLASTWEG             23335
#define AWV_PLASTWEG_TOL         23336
#define AWV_PLASTWEG_REF         23337
#define AWV_SWITCH_POINT_IST     23338
#define AWV_SWITCH_POINT_TOL     23339
#define AWV_SWITCH_POINT_REF     23340
/* ---------------- Darstellungsreg. hydr./spez. -------------------------- */
#define AHS_STAUDRUCK				23341
#define AHS_STAUDRUCK_2				23342
#define AHS_STAUDRUCK_HAND			23343
#define AHS_INJ_PRES_SOLL        23344
#define AHS_SWITCH_PRES_SOLL     23345
#define AHS_PRES_IST             23346
#define AHS_SWITCH_PRES_TOL      23347
#define AHS_SWITCH_PRES_REF      23348
/* ---------------- Darstellungsreg. mm/s -> ccm/s bzw. 1/min -> mm/s ----- */
#define AWV_DREHZAHL 				23349
#define AWV_DREHZAHL_2				23350
#define AWV_SRV_VORPL            23351
#define AWV_SRV_NACHPL           23352
#define AWV_INJ_SPEED_SOLL       23353
/* ------------------------------------------------------------------------ */
#define AWV_SWITCH_POINT2_SOLL   23354
#define AWV_INJ_SPEED2_SOLL      23355
/* ---------------- Darstellungsreg. Weg/Volumen -------------------------- */
#define AWV_WEGPUNKT_2           23356
#define AWV_WEGPUNKT_3           23357
/* ---------------- Darstellungsreg. hydr./spez. -------------------------- */
#define AHS_STAUDRUCK_3          23358
#define AHS_STAUDRUCK_4          23359
/* ---------------- Darstellungsreg. mm/s -> ccm/s bzw. 1/min -> mm/s ----- */
#define AWV_DREHZAHL_3           23360
#define AWV_DREHZAHL_4           23361
/* ------------------------------------------------------------------------ */
#define AWV_PLASTWEG_ANFAHR      23362
#define AHS_INJ_PRES2_SOLL       23363

/* ---------------- Darstellungsreg. der Prozessgrafik -------------------- */
#define NRM_PG_YSCAL             23370
#define NRM_START_WORK				23371 
#define NRM_STOP_WORK				23372 
#define NRM_CURSOR					23373 
#define NRM_XVIEW						23374
#define NRM_MAX						23375
#define NRM_VALUE						23376
#define NRM_MAXX						23377
#define NRM_MAXY						23378
/* ------------------------------------------------------------------------ */

/*BEGIN_MODE_10*/
#define XMP25_1_S                23781
#define XMP25_2_S                23782
#define XMP25_3_S                23783
#define XMP18_1_S                23784
#define XMP18_2_S                23785
#define XMP18_3_S                23786

#define INJTIME                  24319
#define POST_PRES_DURATION       24320
#define XDOSQU                   24321
#define XPRTYPE                  24322
#define XDOSQU_S                 24323
#define XPRTYPE_S                24324
/* ---------------- Volumen-Register fuer Weg-Volumen Umschaltung --------- */
#define ICHGWAY_VOL              24325  /* Change-Register fuer Weg/Vol-Umschaltung */
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define SSPH11_VOL               24326  /* Soll Vol-Umschaltpkt Agg1 Stufe1 */
#define SSPH12_VOL               24327  /* Soll Vol-Umschaltpkt Agg1 Stufe2 */
#define SSPH13_VOL               24328  /* Soll Vol-Umschaltpkt Agg1 Stufe3 */
#define SSPH14_VOL               24329  /* Soll Vol-Umschaltpkt Agg1 Stufe4 */
#define SSPH15_VOL               24330  /* Soll Vol-Umschaltpkt Agg1 Stufe5 */
#define SSPH21_VOL               24331  /* Soll Vol-Umschaltpkt Agg2 Stufe1 */
#define SSPH22_VOL               24332  /* Soll Vol-Umschaltpkt Agg2 Stufe2 */
#define SSPH23_VOL               24333  /* Soll Vol-Umschaltpkt Agg2 Stufe3 */
#define SSPH24_VOL               24334  /* Soll Vol-Umschaltpkt Agg2 Stufe4 */
#define SSPH25_VOL               24335  /* Soll Vol-Umschaltpkt Agg2 Stufe5 */
#define SSPH31_VOL               24336  /* Soll Vol-Umschaltpkt Agg3 Stufe1 */
#define SSPH32_VOL               24337  /* Soll Vol-Umschaltpkt Agg3 Stufe2 */
#define SSPH33_VOL               24338  /* Soll Vol-Umschaltpkt Agg3 Stufe3 */
#define SSPH34_VOL               24339  /* Soll Vol-Umschaltpkt Agg3 Stufe4 */
#define SSPH35_VOL               24340  /* Soll Vol-Umschaltpkt Agg3 Stufe5 */
#define SSPH41_VOL               24341  /* Soll Vol-Umschaltpkt Agg4 Stufe1 */
#define SSPH42_VOL               24342  /* Soll Vol-Umschaltpkt Agg4 Stufe2 */
#define SSPH43_VOL               24343  /* Soll Vol-Umschaltpkt Agg4 Stufe3 */
#define SSPH44_VOL               24344  /* Soll Vol-Umschaltpkt Agg4 Stufe4 */
#define SSPH45_VOL               24345  /* Soll Vol-Umschaltpkt Agg4 Stufe5 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XSPH11_VOL               24346  /* Ist Vol-Umschaltpkt Agg1 Stufe1 */
#define XSPH12_VOL               24347  /* Ist Vol-Umschaltpkt Agg1 Stufe2 */
#define XSPH13_VOL               24348  /* Ist Vol-Umschaltpkt Agg1 Stufe3 */
#define XSPH14_VOL               24349  /* Ist Vol-Umschaltpkt Agg1 Stufe4 */
#define XSPH15_VOL               24350  /* Ist Vol-Umschaltpkt Agg1 Stufe5 */
#define XSPH21_VOL               24351  /* Ist Vol-Umschaltpkt Agg2 Stufe1 */
#define XSPH22_VOL               24352  /* Ist Vol-Umschaltpkt Agg2 Stufe2 */
#define XSPH23_VOL               24353  /* Ist Vol-Umschaltpkt Agg2 Stufe3 */
#define XSPH24_VOL               24354  /* Ist Vol-Umschaltpkt Agg2 Stufe4 */
#define XSPH25_VOL               24355  /* Ist Vol-Umschaltpkt Agg2 Stufe5 */
#define XSPH31_VOL               24356  /* Ist Vol-Umschaltpkt Agg3 Stufe1 */
#define XSPH32_VOL               24357  /* Ist Vol-Umschaltpkt Agg3 Stufe2 */
#define XSPH33_VOL               24358  /* Ist Vol-Umschaltpkt Agg3 Stufe3 */
#define XSPH34_VOL               24359  /* Ist Vol-Umschaltpkt Agg3 Stufe4 */
#define XSPH35_VOL               24360  /* Ist Vol-Umschaltpkt Agg3 Stufe5 */
#define XSPH41_VOL               24361  /* Ist Vol-Umschaltpkt Agg4 Stufe1 */
#define XSPH42_VOL               24362  /* Ist Vol-Umschaltpkt Agg4 Stufe2 */
#define XSPH43_VOL               24363  /* Ist Vol-Umschaltpkt Agg4 Stufe3 */
#define XSPH44_VOL               24364  /* Ist Vol-Umschaltpkt Agg4 Stufe4 */
#define XSPH45_VOL               24365  /* Ist Vol-Umschaltpkt Agg4 Stufe5 */
/* ---------------- Ist Polster ------------------------------------------- */
#define XSPOL1_VOL               24366  /* Ist Vol-Polster Agg1 Stufe6 */
#define XSPOL2_VOL               24367  /* Ist Vol-Polster Agg1 Stufe6 */
#define XSPOL3_VOL               24368  /* Ist Vol-Polster Agg1 Stufe6 */
#define XSPOL4_VOL               24369  /* Ist Vol-Polster Agg1 Stufe6 */
/* ---------------- Ist Plastifizierweg ----------------------------------- */
#define XSPH10_VOL               24370  /* Ist Vol-Plastifizierweg Agg1    */
#define XSPH20_VOL               24371  /* Ist Vol-Plastifizierweg Agg2    */
#define XSPH30_VOL               24372  /* Ist Vol-Plastifizierweg Agg3    */
#define XSPH40_VOL               24373  /* Ist Vol-Plastifizierweg Agg4    */
/* ---------------- Soll Plastifizierweg ---------------------------------- */
#define SSDOS1_VOL               24374  /* Soll Vol Plastifizierweg Agg1   */
#define SSDOS2_VOL               24375  /* Soll Vol Plastifizierweg Agg2   */
#define SSDOS3_VOL               24376  /* Soll Vol Plastifizierweg Agg3   */
#define SSDOS4_VOL               24377  /* Soll Vol Plastifizierweg Agg4   */
/* ---------------- Soll Dosierwegpunkt ----------------------------------- */
#define SSUM11_VOL               24378  /* Soll Vol Dosierwegpunkt Agg1    */
#define SSUM21_VOL               24379  /* Soll Vol Dosierwegpunkt Agg2    */
#define SSUM31_VOL               24380  /* Soll Vol Dosierwegpunkt Agg3    */
#define SSUM41_VOL               24381  /* Soll Vol Dosierwegpunkt Agg4    */
/* ---------------- Soll Schneckrueckzug vor Plastifizieren --------------- */
#define SRSSVOR_1_VOL            24382  /* Soll Vol Schn.rueckzug vor Plast. Agg1*/
#define SRSSVOR_2_VOL            24383  /* Soll Vol Schn.rueckzug vor Plast. Agg2*/
#define SRSSVOR_3_VOL            24384  /* Soll Vol Schn.rueckzug vor Plast. Agg3*/
#define SRSSVOR_4_VOL            24385  /* Soll Vol Schn.rueckzug vor Plast. Agg4*/
/* ---------------- Soll Schneckrueckzug nach Plastifizieren -------------- */
#define SRSSNACH_1_VOL           24386  /* Soll Vol Schn.rueckzug nach Plast. Agg1*/
#define SRSSNACH_2_VOL           24387  /* Soll Vol Schn.rueckzug nach Plast. Agg2*/
#define SRSSNACH_3_VOL           24388  /* Soll Vol Schn.rueckzug nach Plast. Agg3*/
#define SRSSNACH_4_VOL           24389  /* Soll Vol Schn.rueckzug nach Plast. Agg4*/
/* ---------------- Soll Toleranz Plastifizierweg ------------------------- */
#define XTSPH10_VOL              24390  /* Soll Vol Tol Plast.weg Agg1 */
#define XTSPH20_VOL              24391  /* Soll Vol Tol Plast.weg Agg2 */
#define XTSPH30_VOL              24392  /* Soll Vol Tol Plast.weg Agg3 */
#define XTSPH40_VOL              24393  /* Soll Vol Tol Plast.weg Agg4 */
/* ---------------- Soll Toleranz Umschaltpunkt --------------------------- */
#define SWITCH_POINT_TOL11_VOL   24394  /* Soll Vol Tol Um.Point Agg1 Stufe 1*/
#define SWITCH_POINT_TOL12_VOL   24395  /* Soll Vol Tol Um.Point Agg1 Stufe 2*/ 
#define SWITCH_POINT_TOL13_VOL   24396  /* Soll Vol Tol Um.Point Agg1 Stufe 3*/ 
#define SWITCH_POINT_TOL14_VOL   24397  /* Soll Vol Tol Um.Point Agg1 Stufe 4*/ 
#define SWITCH_POINT_TOL15_VOL   24398  /* Soll Vol Tol Um.Point Agg1 Stufe 5*/ 
#define SWITCH_POINT_TOL16_VOL   24399  /* Soll Vol Tol Um.Point Agg1 Polster*/ 
#define SWITCH_POINT_TOL21_VOL   24400  /* Soll Vol Tol Um.Point Agg2 Stufe 1*/ 
#define SWITCH_POINT_TOL22_VOL   24401  /* Soll Vol Tol Um.Point Agg2 Stufe 2*/ 
#define SWITCH_POINT_TOL23_VOL   24402  /* Soll Vol Tol Um.Point Agg2 Stufe 3*/ 
#define SWITCH_POINT_TOL24_VOL   24403  /* Soll Vol Tol Um.Point Agg2 Stufe 4*/ 
#define SWITCH_POINT_TOL25_VOL   24404  /* Soll Vol Tol Um.Point Agg2 Stufe 5*/ 
#define SWITCH_POINT_TOL26_VOL   24405  /* Soll Vol Tol Um.Point Agg2 Polster*/ 
#define SWITCH_POINT_TOL31_VOL   24406  /* Soll Vol Tol Um.Point Agg3 Stufe 1*/ 
#define SWITCH_POINT_TOL32_VOL   24407  /* Soll Vol Tol Um.Point Agg3 Stufe 2*/ 
#define SWITCH_POINT_TOL33_VOL   24408  /* Soll Vol Tol Um.Point Agg3 Stufe 3*/ 
#define SWITCH_POINT_TOL34_VOL   24409  /* Soll Vol Tol Um.Point Agg3 Stufe 4*/ 
#define SWITCH_POINT_TOL35_VOL   24410  /* Soll Vol Tol Um.Point Agg3 Stufe 5*/ 
#define SWITCH_POINT_TOL36_VOL   24411  /* Soll Vol Tol Um.Point Agg3 Polster*/ 
#define SWITCH_POINT_TOL41_VOL   24412  /* Soll Vol Tol Um.Point Agg4 Stufe 1*/ 
#define SWITCH_POINT_TOL42_VOL   24413  /* Soll Vol Tol Um.Point Agg4 Stufe 2*/ 
#define SWITCH_POINT_TOL43_VOL   24414  /* Soll Vol Tol Um.Point Agg4 Stufe 3*/ 
#define SWITCH_POINT_TOL44_VOL   24415  /* Soll Vol Tol Um.Point Agg4 Stufe 4*/ 
#define SWITCH_POINT_TOL45_VOL   24416  /* Soll Vol Tol Um.Point Agg4 Stufe 5*/ 
#define SWITCH_POINT_TOL46_VOL   24417  /* Soll Vol Tol Um.Point Agg4 Polster*/ 
/* ---------------- spez.-Register fuer hydr./spec. Umschaltung ----------- */
/* ---------------- Soll 1.Staudruck -------------------------------------- */
#define SPST11_SPEC              24418  /* Soll specifisch 1.Staudruck Agg1 */
#define SPST21_SPEC              24419  /* Soll specifisch 1.Staudruck Agg2 */
#define SPST31_SPEC              24420  /* Soll specifisch 1.Staudruck Agg3 */
#define SPST41_SPEC              24421  /* Soll specifisch 1.Staudruck Agg4 */
/* ---------------- Soll 2.Staudruck -------------------------------------- */
#define SPST12_SPEC              24422  /* Soll specifisch 2.Staudruck Agg1 */
#define SPST22_SPEC              24423  /* Soll specifisch 2.Staudruck Agg2 */
#define SPST32_SPEC              24424  /* Soll specifisch 2.Staudruck Agg3 */
#define SPST42_SPEC              24425  /* Soll specifisch 2.Staudruck Agg4 */
/* ---------------- Soll Staudruckhand ------------------------------------ */
#define SPSTH1_SPEC              24426  /* Soll specifisch Staudruckhand Agg1 */
#define SPSTH2_SPEC              24427  /* Soll specifisch Staudruckhand Agg2 */
#define SPSTH3_SPEC              24428  /* Soll specifisch Staudruckhand Agg3 */
#define SPSTH4_SPEC              24429  /* Soll specifisch Staudruckhand Agg4 */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define SPPH11_SPEC              24430  /* Soll specifisch Einspritzdruck Agg1 Stufe 1*/
#define SPPH12_SPEC              24431  /* Soll specifisch Einspritzdruck Agg1 Stufe 2*/
#define SPPH13_SPEC              24432  /* Soll specifisch Einspritzdruck Agg1 Stufe 3*/
#define SPPH14_SPEC              24433  /* Soll specifisch Einspritzdruck Agg1 Stufe 4*/
#define SPPH15_SPEC              24434  /* Soll specifisch Einspritzdruck Agg1 Stufe 5*/
#define SPPH16_SPEC              24435  /* Soll specifisch Einspritzdruck Agg1 Stufe 6*/
#define SPPH21_SPEC              24436  /* Soll specifisch Einspritzdruck Agg2 Stufe 1*/
#define SPPH22_SPEC              24437  /* Soll specifisch Einspritzdruck Agg2 Stufe 2*/
#define SPPH23_SPEC              24438  /* Soll specifisch Einspritzdruck Agg2 Stufe 3*/
#define SPPH24_SPEC              24439  /* Soll specifisch Einspritzdruck Agg2 Stufe 4*/
#define SPPH25_SPEC              24440  /* Soll specifisch Einspritzdruck Agg2 Stufe 5*/
#define SPPH26_SPEC              24441  /* Soll specifisch Einspritzdruck Agg2 Stufe 6*/
#define SPPH31_SPEC              24442  /* Soll specifisch Einspritzdruck Agg3 Stufe 1*/
#define SPPH32_SPEC              24443  /* Soll specifisch Einspritzdruck Agg3 Stufe 2*/
#define SPPH33_SPEC              24444  /* Soll specifisch Einspritzdruck Agg3 Stufe 3*/
#define SPPH34_SPEC              24445  /* Soll specifisch Einspritzdruck Agg3 Stufe 4*/
#define SPPH35_SPEC              24446  /* Soll specifisch Einspritzdruck Agg3 Stufe 5*/
#define SPPH36_SPEC              24447  /* Soll specifisch Einspritzdruck Agg3 Stufe 6*/
#define SPPH41_SPEC              24448  /* Soll specifisch Einspritzdruck Agg4 Stufe 1*/
#define SPPH42_SPEC              24449  /* Soll specifisch Einspritzdruck Agg4 Stufe 2*/
#define SPPH43_SPEC              24450  /* Soll specifisch Einspritzdruck Agg4 Stufe 3*/
#define SPPH44_SPEC              24451  /* Soll specifisch Einspritzdruck Agg4 Stufe 4*/
#define SPPH45_SPEC              24452  /* Soll specifisch Einspritzdruck Agg4 Stufe 5*/
#define SPPH46_SPEC              24453  /* Soll specifisch Einspritzdruck Agg4 Stufe 6*/
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define SPUM11_SPEC              24454  /* Soll specifisch Umschaltdruck Agg1 Stufe 1*/
#define SPUM12_SPEC              24455  /* Soll specifisch Umschaltdruck Agg1 Stufe 2*/
#define SPUM13_SPEC              24456  /* Soll specifisch Umschaltdruck Agg1 Stufe 3*/
#define SPUM14_SPEC              24457  /* Soll specifisch Umschaltdruck Agg1 Stufe 4*/
#define SPUM15_SPEC              24458  /* Soll specifisch Umschaltdruck Agg1 Stufe 5*/
#define SPUM21_SPEC              24459  /* Soll specifisch Umschaltdruck Agg2 Stufe 1*/
#define SPUM22_SPEC              24460  /* Soll specifisch Umschaltdruck Agg2 Stufe 2*/
#define SPUM23_SPEC              24461  /* Soll specifisch Umschaltdruck Agg2 Stufe 3*/
#define SPUM24_SPEC              24462  /* Soll specifisch Umschaltdruck Agg2 Stufe 4*/
#define SPUM25_SPEC              24463  /* Soll specifisch Umschaltdruck Agg2 Stufe 5*/
#define SPUM31_SPEC              24464  /* Soll specifisch Umschaltdruck Agg3 Stufe 1*/
#define SPUM32_SPEC              24465  /* Soll specifisch Umschaltdruck Agg3 Stufe 2*/
#define SPUM33_SPEC              24466  /* Soll specifisch Umschaltdruck Agg3 Stufe 3*/
#define SPUM34_SPEC              24467  /* Soll specifisch Umschaltdruck Agg3 Stufe 4*/
#define SPUM35_SPEC              24468  /* Soll specifisch Umschaltdruck Agg3 Stufe 5*/
#define SPUM41_SPEC              24469  /* Soll specifisch Umschaltdruck Agg4 Stufe 1*/
#define SPUM42_SPEC              24470  /* Soll specifisch Umschaltdruck Agg4 Stufe 2*/
#define SPUM43_SPEC              24471  /* Soll specifisch Umschaltdruck Agg4 Stufe 3*/
#define SPUM44_SPEC              24472  /* Soll specifisch Umschaltdruck Agg4 Stufe 4*/
#define SPUM45_SPEC              24473  /* Soll specifisch Umschaltdruck Agg4 Stufe 5*/
/* ---------------- Soll Toleranz Einspritzdruck -------------------------- */
#define SWITCH_PRES_TOL11_SPEC   24474  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 1*/
#define SWITCH_PRES_TOL12_SPEC   24475  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 2*/
#define SWITCH_PRES_TOL13_SPEC   24476  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 3*/
#define SWITCH_PRES_TOL14_SPEC   24477  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 4*/
#define SWITCH_PRES_TOL15_SPEC   24478  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 5*/
#define SWITCH_PRES_TOL16_SPEC   24479  /* Soll specifisch Tol Einspritzdr. Agg1 Stufe 6*/
#define SWITCH_PRES_TOL21_SPEC   24480  /* Soll specifisch Tol Einspritzdr. Agg2 Stufe 1*/
#define SWITCH_PRES_TOL22_SPEC   24481  /* Soll specifisch Tol Einspritzdr. Agg2 Stufe 2*/
#define SWITCH_PRES_TOL23_SPEC   24482  /* Soll specifisch Tol Einspritzdr. Agg2 Stufe 3*/
#define SWITCH_PRES_TOL24_SPEC   24483  /* Soll specifisch Tol Einspritzdr. Agg2 Stufe 4*/
#define SWITCH_PRES_TOL25_SPEC   24484  /* Soll specifisch Tol Einspritzdr. Agg2 Stufe 5*/
#define SWITCH_PRES_TOL26_SPEC   24485  /* Soll specifisch Tol Einspritzdr. Agg2 Stufe 6*/
#define SWITCH_PRES_TOL31_SPEC   24486  /* Soll specifisch Tol Einspritzdr. Agg3 Stufe 1*/
#define SWITCH_PRES_TOL32_SPEC   24487  /* Soll specifisch Tol Einspritzdr. Agg3 Stufe 2*/
#define SWITCH_PRES_TOL33_SPEC   24488  /* Soll specifisch Tol Einspritzdr. Agg3 Stufe 3*/
#define SWITCH_PRES_TOL34_SPEC   24489  /* Soll specifisch Tol Einspritzdr. Agg3 Stufe 4*/
#define SWITCH_PRES_TOL35_SPEC   24490  /* Soll specifisch Tol Einspritzdr. Agg3 Stufe 5*/
#define SWITCH_PRES_TOL36_SPEC   24491  /* Soll specifisch Tol Einspritzdr. Agg3 Stufe 6*/
#define SWITCH_PRES_TOL41_SPEC   24492  /* Soll specifisch Tol Einspritzdr. Agg4 Stufe 1*/
#define SWITCH_PRES_TOL42_SPEC   24493  /* Soll specifisch Tol Einspritzdr. Agg4 Stufe 2*/
#define SWITCH_PRES_TOL43_SPEC   24494  /* Soll specifisch Tol Einspritzdr. Agg4 Stufe 3*/
#define SWITCH_PRES_TOL44_SPEC   24495  /* Soll specifisch Tol Einspritzdr. Agg4 Stufe 4*/
#define SWITCH_PRES_TOL45_SPEC   24496  /* Soll specifisch Tol Einspritzdr. Agg4 Stufe 5*/
#define SWITCH_PRES_TOL46_SPEC   24497  /* Soll specifisch Tol Einspritzdr. Agg4 Stufe 6*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XPPH11_SPEC              24498  /* Ist specifisch Einspritzdruck Agg1 Stufe 1*/
#define XPPH12_SPEC              24499  /* Ist specifisch Einspritzdruck Agg1 Stufe 2*/
#define XPPH13_SPEC              24500  /* Ist specifisch Einspritzdruck Agg1 Stufe 3*/
#define XPPH14_SPEC              24501  /* Ist specifisch Einspritzdruck Agg1 Stufe 4*/
#define XPPH15_SPEC              24502  /* Ist specifisch Einspritzdruck Agg1 Stufe 5*/
#define XPPH16_SPEC              24503  /* Ist specifisch Einspritzdruck Agg1 Stufe 6*/
#define XPPH21_SPEC              24504  /* Ist specifisch Einspritzdruck Agg2 Stufe 1*/
#define XPPH22_SPEC              24505  /* Ist specifisch Einspritzdruck Agg2 Stufe 2*/
#define XPPH23_SPEC              24506  /* Ist specifisch Einspritzdruck Agg2 Stufe 3*/
#define XPPH24_SPEC              24507  /* Ist specifisch Einspritzdruck Agg2 Stufe 4*/
#define XPPH25_SPEC              24508  /* Ist specifisch Einspritzdruck Agg2 Stufe 5*/
#define XPPH26_SPEC              24509  /* Ist specifisch Einspritzdruck Agg2 Stufe 6*/
#define XPPH31_SPEC              24510  /* Ist specifisch Einspritzdruck Agg3 Stufe 1*/
#define XPPH32_SPEC              24511  /* Ist specifisch Einspritzdruck Agg3 Stufe 2*/
#define XPPH33_SPEC              24512  /* Ist specifisch Einspritzdruck Agg3 Stufe 3*/
#define XPPH34_SPEC              24513  /* Ist specifisch Einspritzdruck Agg3 Stufe 4*/
#define XPPH35_SPEC              24514  /* Ist specifisch Einspritzdruck Agg3 Stufe 5*/
#define XPPH36_SPEC              24515  /* Ist specifisch Einspritzdruck Agg3 Stufe 6*/
#define XPPH41_SPEC              24516  /* Ist specifisch Einspritzdruck Agg4 Stufe 1*/
#define XPPH42_SPEC              24517  /* Ist specifisch Einspritzdruck Agg4 Stufe 2*/
#define XPPH43_SPEC              24518  /* Ist specifisch Einspritzdruck Agg4 Stufe 3*/
#define XPPH44_SPEC              24519  /* Ist specifisch Einspritzdruck Agg4 Stufe 4*/
#define XPPH45_SPEC              24520  /* Ist specifisch Einspritzdruck Agg4 Stufe 5*/
#define XPPH46_SPEC              24521  /* Ist specifisch Einspritzdruck Agg4 Stufe 6*/
/* ---------------- Volumen-Register fuer Weg-Volumen Umschaltung (Geschw.) */
/* ---------------- 1. Plastifizierdrehzahl ------------------------------- */
#define SWPL11_VOL               24522  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL21_VOL               24523  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL31_VOL               24524  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL41_VOL               24525  /* Soll Volumen Geschwindigk. mm/s  */
/* ---------------- 2. Plastifizierdrehzahl ------------------------------- */
#define SWPL12_VOL               24526  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL22_VOL               24527  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL32_VOL               24528  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL42_VOL               24529  /* Soll Volumen Geschwindigk. mm/s  */
/* ---------------- Rueckzugsgeschw. vor Plastifizieren ------------------- */
#define SRSVVOR_1_VOL            24530  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVVOR_2_VOL            24531  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVVOR_3_VOL            24532  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVVOR_4_VOL            24533  /* Soll Volumen Geschwindigk. ccm/s  */
/* ---------------- Rueckzugsgeschw. nach Plastifizieren ------------------ */
#define SRSVNACH_1_VOL           24534  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVNACH_2_VOL           24535  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVNACH_3_VOL           24536  /* Soll Volumen Geschwindigk. ccm/s  */
#define SRSVNACH_4_VOL           24537  /* Soll Volumen Geschwindigk. ccm/s  */
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define SVPH11_VOL               24538  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe1 */
#define SVPH12_VOL               24539  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe2 */
#define SVPH13_VOL               24540  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe3 */
#define SVPH14_VOL               24541  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe4 */
#define SVPH15_VOL               24542  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe5 */
#define SVPH16_VOL               24543  /* Soll Vol-Geschwindigk. ccm/s Agg1 Stufe6 */
#define SVPH21_VOL               24544  /* Soll Vol-Geschwindigk. ccm/s Agg2 Stufe1 */
#define SVPH22_VOL               24545  /* Soll Vol-Geschwindigk. ccm/s Agg2 Stufe2 */
#define SVPH23_VOL               24546  /* Soll Vol-Geschwindigk. ccm/s Agg2 Stufe3 */
#define SVPH24_VOL               24547  /* Soll Vol-Geschwindigk. ccm/s Agg2 Stufe4 */
#define SVPH25_VOL               24548  /* Soll Vol-Geschwindigk. ccm/s Agg2 Stufe5 */
#define SVPH26_VOL               24549  /* Soll Vol-Geschwindigk. ccm/s Agg2 Stufe6 */
#define SVPH31_VOL               24550  /* Soll Vol-Geschwindigk. ccm/s Agg3 Stufe1 */
#define SVPH32_VOL               24551  /* Soll Vol-Geschwindigk. ccm/s Agg3 Stufe2 */
#define SVPH33_VOL               24552  /* Soll Vol-Geschwindigk. ccm/s Agg3 Stufe3 */
#define SVPH34_VOL               24553  /* Soll Vol-Geschwindigk. ccm/s Agg3 Stufe4 */
#define SVPH35_VOL               24554  /* Soll Vol-Geschwindigk. ccm/s Agg3 Stufe5 */
#define SVPH36_VOL               24555  /* Soll Vol-Geschwindigk. ccm/s Agg3 Stufe6 */
#define SVPH41_VOL               24556  /* Soll Vol-Geschwindigk. ccm/s Agg4 Stufe1 */
#define SVPH42_VOL               24557  /* Soll Vol-Geschwindigk. ccm/s Agg4 Stufe2 */
#define SVPH43_VOL               24558  /* Soll Vol-Geschwindigk. ccm/s Agg4 Stufe3 */
#define SVPH44_VOL               24559  /* Soll Vol-Geschwindigk. ccm/s Agg4 Stufe4 */
#define SVPH45_VOL               24560  /* Soll Vol-Geschwindigk. ccm/s Agg4 Stufe5 */
#define SVPH46_VOL               24561  /* Soll Vol-Geschwindigk. ccm/s Agg4 Stufe6 */
/* ---------------- Volumen-Register fuer Referenzwerte ------------------- */
/* ---------------- REF Einspritzdruecke ---------------------------------- */
#define SWITCH_PRES_REF11_SPEC   24562  /* Einspritzdruck Agg1 Stufe1 */
#define SWITCH_PRES_REF12_SPEC   24563  /* Einspritzdruck Agg1 Stufe2 */ 
#define SWITCH_PRES_REF13_SPEC   24564  /* Einspritzdruck Agg1 Stufe3 */ 
#define SWITCH_PRES_REF14_SPEC   24565  /* Einspritzdruck Agg1 Stufe4 */ 
#define SWITCH_PRES_REF15_SPEC   24566  /* Einspritzdruck Agg1 Stufe5 */ 
#define SWITCH_PRES_REF16_SPEC   24567  /* Einspritzdruck Agg1 Stufe6 */ 
#define SWITCH_PRES_REF21_SPEC   24568  /* Einspritzdruck Agg2 Stufe1 */ 
#define SWITCH_PRES_REF22_SPEC   24569  /* Einspritzdruck Agg2 Stufe2 */ 
#define SWITCH_PRES_REF23_SPEC   24570  /* Einspritzdruck Agg2 Stufe3 */ 
#define SWITCH_PRES_REF24_SPEC   24571  /* Einspritzdruck Agg2 Stufe4 */ 
#define SWITCH_PRES_REF25_SPEC   24572  /* Einspritzdruck Agg2 Stufe5 */ 
#define SWITCH_PRES_REF26_SPEC   24573  /* Einspritzdruck Agg2 Stufe6 */ 
#define SWITCH_PRES_REF31_SPEC   24574  /* Einspritzdruck Agg3 Stufe1 */
#define SWITCH_PRES_REF32_SPEC   24575  /* Einspritzdruck Agg3 Stufe2 */ 
#define SWITCH_PRES_REF33_SPEC   24576  /* Einspritzdruck Agg3 Stufe3 */ 
#define SWITCH_PRES_REF34_SPEC   24577  /* Einspritzdruck Agg3 Stufe4 */ 
#define SWITCH_PRES_REF35_SPEC   24578  /* Einspritzdruck Agg3 Stufe5 */ 
#define SWITCH_PRES_REF36_SPEC   24579  /* Einspritzdruck Agg3 Stufe6 */ 
#define SWITCH_PRES_REF41_SPEC   24580  /* Einspritzdruck Agg4 Stufe1 */ 
#define SWITCH_PRES_REF42_SPEC   24581  /* Einspritzdruck Agg4 Stufe2 */ 
#define SWITCH_PRES_REF43_SPEC   24582  /* Einspritzdruck Agg4 Stufe3 */ 
#define SWITCH_PRES_REF44_SPEC   24583  /* Einspritzdruck Agg4 Stufe4 */ 
#define SWITCH_PRES_REF45_SPEC   24584  /* Einspritzdruck Agg4 Stufe5 */ 
#define SWITCH_PRES_REF46_SPEC   24585  /* Einspritzdruck Agg4 Stufe6 */ 
/* ---------------- REF Umschaltpunkte ------------------------------------ */
#define SWITCH_POINT_REF11_VOL   24586  /* Umschaltpunkt Agg1 Stufe1 */
#define SWITCH_POINT_REF12_VOL   24587  /* Umschaltpunkt Agg1 Stufe2 */
#define SWITCH_POINT_REF13_VOL   24588  /* Umschaltpunkt Agg1 Stufe3 */
#define SWITCH_POINT_REF14_VOL   24589  /* Umschaltpunkt Agg1 Stufe4 */
#define SWITCH_POINT_REF15_VOL   24590  /* Umschaltpunkt Agg1 Stufe5 */
#define SWITCH_POINT_REF16_VOL   24591  /* Umschaltpunkt Agg1 Stufe6 */
#define SWITCH_POINT_REF21_VOL   24592  /* Umschaltpunkt Agg2 Stufe1 */
#define SWITCH_POINT_REF22_VOL   24593  /* Umschaltpunkt Agg2 Stufe2 */
#define SWITCH_POINT_REF23_VOL   24594  /* Umschaltpunkt Agg2 Stufe3 */
#define SWITCH_POINT_REF24_VOL   24595  /* Umschaltpunkt Agg2 Stufe4 */
#define SWITCH_POINT_REF25_VOL   24596  /* Umschaltpunkt Agg2 Stufe5 */
#define SWITCH_POINT_REF26_VOL   24597  /* Umschaltpunkt Agg2 Stufe6 */
#define SWITCH_POINT_REF31_VOL   24598  /* Umschaltpunkt Agg3 Stufe1 */
#define SWITCH_POINT_REF32_VOL   24599  /* Umschaltpunkt Agg3 Stufe2 */
#define SWITCH_POINT_REF33_VOL   24600  /* Umschaltpunkt Agg3 Stufe3 */
#define SWITCH_POINT_REF34_VOL   24601  /* Umschaltpunkt Agg3 Stufe4 */
#define SWITCH_POINT_REF35_VOL   24602  /* Umschaltpunkt Agg3 Stufe5 */
#define SWITCH_POINT_REF36_VOL   24603  /* Umschaltpunkt Agg3 Stufe6 */
#define SWITCH_POINT_REF41_VOL   24604  /* Umschaltpunkt Agg4 Stufe1 */
#define SWITCH_POINT_REF42_VOL   24605  /* Umschaltpunkt Agg4 Stufe2 */
#define SWITCH_POINT_REF43_VOL   24606  /* Umschaltpunkt Agg4 Stufe3 */
#define SWITCH_POINT_REF44_VOL   24607  /* Umschaltpunkt Agg4 Stufe4 */
#define SWITCH_POINT_REF45_VOL   24608  /* Umschaltpunkt Agg4 Stufe5 */
#define SWITCH_POINT_REF46_VOL   24609  /* Umschaltpunkt Agg4 Stufe6 */
/* ---------------- REF Plastifizierwege ---------------------------------- */
#define XTSPH10_REF_VOL          24610  /* Plastifizierweg Agg1 */
#define XTSPH20_REF_VOL          24611  /* Plastifizierweg Agg2 */
#define XTSPH30_REF_VOL          24612  /* Plastifizierweg Agg3 */
#define XTSPH40_REF_VOL          24613  /* Plastifizierweg Agg4 */
/* ---------------- Volumen-Register fuer Prozessgrafik ------------------- */
#define PG_YSCAL_VOLSPEC         24614  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC01       24615  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC02       24616  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC03       24617  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC04       24618  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC05       24619  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC06       24620  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC07       24621  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC08       24622  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC09       24623  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC10       24624  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC11       24625  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC12       24626  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC13       24627  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC14       24628  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC15       24629  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC16       24630  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC17       24631  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC18       24632  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC19       24633  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC20       24634  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC21       24635  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC22       24636  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC23       24637  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC24       24638  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC25       24639  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC26       24640  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC27       24641  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC28       24642  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC29       24643  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC30       24644  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC31       24645  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC32       24646  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC33       24647  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC34       24648  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC35       24649  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC36       24650  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC37       24651  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC38       24652  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC39       24653  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC40       24654  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC41       24655  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC42       24656  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC43       24657  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC44       24658  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC45       24659  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC46       24660  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC47       24661  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC48       24662  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC49       24663  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC50       24664  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC51       24665  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC52       24666  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC53       24667  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC54       24668  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC55       24669  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC56       24670  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC57       24671  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC58       24672  /* Skalierendwerte S.45.1 */
#define PG_YSCAL_VOLSPEC59       24673  /* Skalierendwerte S.45.1 */
/* ---------------- Erweiterung fuer 4 Plastifizierstufen ----------------- */
/* ---------------- Soll 2. Plastifizierwegpunkt -------------------------- */
#define SSUM12_VOL               24674  /* Soll Vol Dosierwegpunkt Agg1    */
#define SSUM22_VOL               24675  /* Soll Vol Dosierwegpunkt Agg2    */
#define SSUM32_VOL               24676  /* Soll Vol Dosierwegpunkt Agg3    */
#define SSUM42_VOL               24677  /* Soll Vol Dosierwegpunkt Agg4    */
/* ---------------- Soll 3. Plastifizierwegpunkt -------------------------- */
#define SSUM13_VOL               24678  /* Soll Vol Dosierwegpunkt Agg1    */
#define SSUM23_VOL               24679  /* Soll Vol Dosierwegpunkt Agg2    */
#define SSUM33_VOL               24680  /* Soll Vol Dosierwegpunkt Agg3    */
#define SSUM43_VOL               24681  /* Soll Vol Dosierwegpunkt Agg4    */
/* ---------------- 3. Plastifizierdrehzahl ------------------------------- */
#define SWPL13_VOL               24682  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL23_VOL               24683  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL33_VOL               24684  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL43_VOL               24685  /* Soll Volumen Geschwindigk. mm/s  */
/* ---------------- 4. Plastifizierdrehzahl ------------------------------- */
#define SWPL14_VOL               24686  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL24_VOL               24687  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL34_VOL               24688  /* Soll Volumen Geschwindigk. mm/s  */
#define SWPL44_VOL               24689  /* Soll Volumen Geschwindigk. mm/s  */
/* ---------------- Soll 3.Staudruck -------------------------------------- */
#define SPST13_SPEC              24690  /* Soll specifisch 3.Staudruck Agg1 */
#define SPST23_SPEC              24691  /* Soll specifisch 3.Staudruck Agg2 */
#define SPST33_SPEC              24692  /* Soll specifisch 3.Staudruck Agg3 */
#define SPST43_SPEC              24693  /* Soll specifisch 3.Staudruck Agg4 */
/* ---------------- Soll 4.Staudruck -------------------------------------- */
#define SPST14_SPEC              24694  /* Soll specifisch 4.Staudruck Agg1 */
#define SPST24_SPEC              24695  /* Soll specifisch 4.Staudruck Agg2 */
#define SPST34_SPEC              24696  /* Soll specifisch 4.Staudruck Agg3 */
#define SPST44_SPEC              24697  /* Soll specifisch 4.Staudruck Agg4 */

/* ---------------- Toleranz- und Referenzregister ------------------------ */
#define XSPREF11                 24701
#define XSPREF12                 24702
#define XSPREF13                 24703
#define XSPREF14                 24704
#define XSPREF15                 24705
#define XSPREF16                 24706
#define XSPREF17                 24707
#define XSPREF18                 24708
#define XSPREF19                 24709
#define XSPREF1A                 24710
#define XSPTOL11                 24731
#define XSPTOL12                 24732
#define XSPTOL13                 24733
#define XSPTOL14                 24734
#define XSPTOL15                 24735
#define XSPTOL16                 24736
#define XSPTOL17                 24737
#define XSPTOL18                 24738
#define XSPTOL19                 24739
#define XSPTOL1A                 24740 
#define XXTPOLSREF1              24755  
#define XXTPOLSTOL1              24758  
#define XXTPLASREF1              24761  
#define XXTPLASTOL1              24764  
#define XSSPLASREF1              24767  
#define XSSPLASTOL1              24770  
#define XSSINJREF1               24773  
#define XSSINJTOL1               24776  
#define XSTINJREF1               24779  
#define XSTINJTOL1               24782  
#define XSPINJREF1               24785  
#define XSPINJTOL1               24788  
#define XSPTINREF1               24791  
#define XSPTINTOL1               24794  
#define XSPTINMAXREF1            24797  
#define XSPTINMAXTOL1            24800  
#define XSTCYCREF1               24803  
#define XSTCYCTOL1               24806  
/*END_MODE_10*/
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
#define ACT_DIAGSYSTYP           24807
#define ACT_DIAGBUSNR            24808
#define ACT_DIAGMODNR            24809
#define ACT_DIAGINDTAB           24810
#define ACT_DIAGMODULTYP         24811
/* ------------------------------------------------------------------------ */
#define AWV_ANZ_PLAST_STUF       24812
#define PLgs_Umschaltpunkt       24813


/* Register fuer neue Prozessgrafik
   2 Funktionseinheiten
 */
#define NOOF_AGGREGATES           24850
#define CURVE_NO                  24851
#define PGCONFIG                  24852
#define STDCURV1                  24853
#define STDCURV2                  24854
#define XPG_TOLCHAN               24855

#define XPG_SOLLIST1              24900
#define XPG_SOLLIST2              24901
#define XPG_SOLLIST3              24902
#define XPG_SOLLIST4              24903

#define XPG_CURSOR                24905 
#define XPG_XVIEW                 24906 
#define XPG_MAX                   24907 
#define XPG_VALUE                 24908
#define XPG_SI1		             24909
#define XPG_SI2              		 24910
#define PHASEINJTIME              25099
#define PG_ACK_INFO               25100
#define PG_CURVE_INFO             25101
#define PG_ACK_INFO_DIRECT        25102
#define PG_CURVE_INFO_DIRECT      25103
#define PG_NR_ACT_CURVES          25104

#define ICOY9030						25119
#define ICO_ident						25120
#define ICO_number					25121
#define ICO_info						25122
#define ICO_p							25123
#define ICO_v							25124
#define ICO_s1							25125
#define ICO_tA							25126
#define ICO_tV							25127
#define ICO_s2							25128
#define ICO_M							25129
#define ICO_tR							25130
#define ICO_s3							25131

#define ICO_S							25140
#define ICO_L							25141
#define ICO_Startconds				25142
#define ICO_Movements				25143
#define ICO_Options					25144
#define ICO_lineno					25145
#define ICO_StartcondText			25146
#define ICO_MovementText			25147
#define ICO_OptionText				25148
#define ICO_MaxToolStroke			25149
#define ICOINIPOS						25150
#define ICOENDPOS						25151

#define ICOPROGLINE0					25160
#define ICOPROGLINE1					25161
#define ICOPROGLINE2					25162
#define ICOPROGLINE3					25163
#define ICOPROGLINE4					25164
#define ICOPROGLINE5					25165
#define ICOPROGLINE6					25166
#define ICOPROGLINE7					25167
#define ICOPROGLINE8					25168
#define ICOPROGLINE9					25169
#define ICOPROGLINE10				25170
#define ICOPROGLINE11				25171
#define ICOPROGLINE12				25172
#define ICOPROGLINE13				25173
#define ICOPROGLINE14				25174
#define ICOPROGLINE15				25175
#define ICOPROGLINE16				25176
#define ICOPROGLINE17				25177
#define ICOPROGLINE18				25178
#define ICOPROGLINE19				25179
#define ICOPROGLINE20				25180
#define ICOPROGLINE21				25181
#define ICOPROGLINE22				25182
#define ICOPROGLINE23				25183
#define ICOPROGLINE24				25184
#define ICOPROGLINE25				25185
#define ICOPROGLINE26				25186
#define ICOPROGLINE27				25187
#define ICOPROGLINE28				25188
#define ICOPROGLINE29				25189
#define ICOPROGLINE30				25190
#define ICOPROGLINE31				25191
#define ICOPROGLINE32				25192
#define ICOPROGLINE33				25193
#define ICOPROGLINE34				25194
#define ICOPROGLINE35				25195
#define ICOPROGLINE36				25196
#define ICOPROGLINE37				25197
#define ICOPROGLINE38				25198
#define ICOPROGLINE39				25199
#define ICOPROGLINE40				25200
#define ICOPROGLINE41				25201
#define ICOPROGLINE42				25202
#define ICOPROGLINE43				25203
#define ICOPROGLINE44				25204
#define ICOPROGLINE45				25205
#define ICOPROGLINE46				25206
#define ICOPROGLINE47				25207
#define ICOPROGLINE48				25208
#define ICOPROGLINE49				25209

#define SELECT_PROCESS_STEPS     25300 /* Anzahl der Proze~schritte */
#define PROC_STEP_UNIT1          25301 /* Proze~schritte-Zuordnung Spritzeinheit 1 */
#define PROC_STEP_UNIT2          25302 /* Proze~schritte-Zuordnung Spritzeinheit 2 */ 
#define PROC_STEP_UNIT3          25303 /* Proze~schritte-Zuordnung Spritzeinheit 3 */ 
#define PROC_STEP_UNIT4          25304 /* Proze~schritte-Zuordnung Spritzeinheit 4 */ 
#define DUES_WAHL_SPEC           25305 /* @SONDER Aktuell ausgewaehlte Duese S. 48  */ 

/* Register fuer das Abnahmeprotokoll */
#define AP_MASHNR                   25500 /* Maschinennummer                           */
#define AP_SACHNR_PUMPE             25501 /* Pumpe Sachnummer                          */
#define AP_SACHNR_EMOTOR            25502 /* E-Motor Sachnummer                        */
#define AP_SACHNR_STEUERUNG         25503 /* Steuerung Sachnummer                      */
#define AP_SACHNR_TERMINAL          25504 /* Terminal Sachnummer                       */
#define AP_SACHNR_WEGMESS1_WKZ      25505 /* Wegmesseinrichtung 1 Werkzeug Sachnummer  */
#define AP_SACHNR_WEGMESS2_AUSW     25506 /* Wegmesseinrichtung 2 Auswerfer Sachnummer */
#define AP_SACHNR_WEGMESS3_SPR      25507 /* Wegmesseinrichtung 3 Spritzen Sachnummer  */
#define AP_SACHNR_DRUCKAUFN1        25508 /* Druckaufnehmer1 Sachnummer                */
#define AP_SACHNR_DRUCKAUFN2        25509 /* Druckaufnehmer2 Sachnummer                */
#define AP_OFFSET_DRUCKAUFN1        25510 /* Druckaufnehmer1 Offset                    */
#define AP_OFFSET_DRUCKAUFN2        25511 /* Druckaufnehmer2 Offset                    */
#define AP_MV_DRUCKAUFN1            25512 /* Druckaufnehmer1 mV                        */
#define AP_MV_DRUCKAUFN2            25513 /* Druckaufnehmer2 mV                        */
#define AP_SACHNR_PLATTENSATZ       25514 /* Plattensatz Sachnummer                    */
#define AP_SACHNR_ZENTR_WAB         25515 /* Zentrierung WAB Sachnummer                */
#define AP_SACHNR_ZENTR_WAF         25516 /* Zentrierung WAB Sachnummer                */
#define AP_SOLL_ZENTR_WAB           25517 /* Zentrierung WAB Soll                      */
#define AP_SOLL_ZENTR_WAF           25518 /* Zentrierung WAB Soll                      */
#define AP_SOLL_AUSWERFERWEG        25519 /* Auswerferweg Soll                         */
#define AP_SOLL_MIN_WKZEINBAUH      25520 /* Minimale Werkzeugeinbauhoehe Soll         */
#define AP_SOLL_MAX_OEFFNUNGSW      25521 /* Maximale Oeffnungsweite Soll              */
#define AP_IST_MIN_WKZEINBAUH       25522 /* Minimale Werkzeugeinbauhoehe Ist          */
#define AP_IST_MAX_OEFFNUNGSW       25523 /* Maximale Oeffnungsweite Ist               */
#define AP_WAB_UHOLME_MAX           25524 /* WAB untere Holme max Oeff.                Max.    */
#define AP_WAF_UHOLME_MAX           25525 /* WAF untere Holme.                         Max.    */
#define AP_FEINH_RUE45_MAX          25526 /* Fuehrungseinheit RUE 45                   Max.    */
#define AP_WAB_UHOLME_QUER_MAX      25527 /* WAB untere Holme quer max Oeff.           Max.    */
#define AP_WAF_UHOLME_QUER_MAX      25528 /* WAF untere Holme quer                     Max.    */
#define AP_WAB_FEINH_RUE45_QUER_MAX 25529 /* Fuehrungseinheit RUE 45 quer WAB          Max.    */
#define AP_WAF_FEINH_RUE45_QUER_MAX 25530 /* Fuehrungseinheit RUE 45 quer WAF          Max.    */
#define AP_WAB_MAXOEFF_RAHMEN_MAX   25531 /* WAB max Oeff Rahmenwasserwaage            Max.    */
#define AP_WAB_MINOEFF_RAHMEN_MAX   25532 /* WAB min Oeff Rahmenwasserwaage            Max.    */
#define AP_WAF_RAHMEN_MAX           25533 /* WAB Rahmenwasserwaage                     Max.    */
#define AP_PLATTENAB_MAXOFFU_MAX    25534 /* Plattenabstand max oeff unten Innenmikrom.Max.    */
#define AP_PLATTENAB_MAXOFFO_MAX    25535 /* Plattenabstand max oeff oben Innenmikrom. Max.    */
#define AP_PLATTENAB_MINOFFU_MAX    25536 /* Plattenabstand min oeff unten Innenmikrom.Max.    */
#define AP_PLATTENAB_MINOFFO_MAX    25537 /* Plattenabstand min oeff oben Innenmikrom. Max.    */
#define AP_WAB_UHOLME_B             25538 /* WAB untere Holme max Oeff.                B-Seite */
#define AP_WAF_UHOLME_B             25539 /* WAF untere Holme.                         B-Seite */
#define AP_FEINH_RUE45_B            25540 /* Fuehrungseinheit RUE 45                   B-Seite */
#define AP_WAB_UHOLME_QUER_B        25541 /* WAB untere Holme quer max Oeff.           B-Seite */
#define AP_WAF_UHOLME_QUER_B        25542 /* WAF untere Holme quer                     B-Seite */
#define AP_WAB_FEINH_RUE45_QUER_B   25543 /* Fuehrungseinheit RUE 45 quer WAB          B-Seite */
#define AP_WAF_FEINH_RUE45_QUER_B   25544 /* Fuehrungseinheit RUE 45 quer WAF          B-Seite */
#define AP_WAB_MAXOEFF_RAHMEN_B     25545 /* WAB max Oeff Rahmenwasserwaage            B-Seite */
#define AP_WAB_MINOEFF_RAHMEN_B     25546 /* WAB min Oeff Rahmenwasserwaage            B-Seite */
#define AP_WAF_RAHMEN_B             25547 /* WAB Rahmenwasserwaage                     B-Seite */
#define AP_PLATTENAB_MAXOFFU_B      25548 /* Plattenabstand max oeff unten Innenmikrom.B-Seite */
#define AP_PLATTENAB_MAXOFFO_B      25549 /* Plattenabstand max oeff oben Innenmikrom. B-Seite */
#define AP_PLATTENAB_MINOFFU_B      25550 /* Plattenabstand min oeff unten Innenmikrom.B-Seite */
#define AP_PLATTENAB_MINOFFO_B      25551 /* Plattenabstand min oeff oben Innenmikrom. B-Seite */
#define AP_WAB_UHOLME_H             25552 /* WAB untere Holme max Oeff.                H-Seite */
#define AP_WAF_UHOLME_H             25553 /* WAF untere Holme.                         H-Seite */
#define AP_FEINH_RUE45_H            25554 /* Fuehrungseinheit RUE 45                   H-Seite */
#define AP_WAB_MAXOEFF_RAHMEN_H     25555 /* WAB max Oeff Rahmenwasserwaage            H-Seite */
#define AP_WAB_MINOEFF_RAHMEN_H     25556 /* WAB min Oeff Rahmenwasserwaage            H-Seite */
#define AP_WAF_RAHMEN_H             25557 /* WAF Rahmenwasserwaage                     H-Seite */
#define AP_PLATTENAB_MAXOFFU_H      25558 /* Plattenabstand max oeff unten Innenmikrom.H-Seite */
#define AP_PLATTENAB_MAXOFFO_H      25559 /* Plattenabstand max oeff oben Innenmikrom. H-Seite */
#define AP_PLATTENAB_MINOFFU_H      25560 /* Plattenabstand min oeff unten Innenmikrom.H-Seite */
#define AP_PLATTENAB_MINOFFO_H      25561 /* Plattenabstand min oeff oben Innenmikrom. H-Seite */
#define AP_SACHNR_INT_GROESSE       25562 /* Sachnummer int. Groesse                           */
#define AP_SACHNR_DOSMOT_HYD        25563 /* Sachnummer Dosiermotor hyd.                       */
#define AP_SACHNR_DOSMOT_ELEKT      25564 /* Sachnummer Dosiermotor elekt.                     */
#define AP_SACHNR_SNZYL             25565 /* Sachnummer Schneckenzylinder                      */
#define AP_SACHNR_SN                25566 /* Sachnummer Schnecke                               */
#define AP_SACHNR_VERSCHLDUESE      25567 /* Sachnummer Verschussduese                         */
#define AP_SACHNR_OFFENE_DUESE      25568 /* Sachnummer Offene Duese                           */
#define AP_SACHNR_DUESENKOPF        25569 /* Sachnummer Duesenkopf                             */
#define AP_SACHNR_MASSETEMPFUEHLER  25570 /* Sachnummer Massetemperaturfuehler                 */
#define AP_SNZYL_MM                 25571 /* Schneckenyzlinder (mm)                            */

#define AP_LINEARF_VENDE_MAX        25572 /* Linearfuehrung vorderes Ende Wasserwaage  Max.    */
#define AP_LINEARF_HENDE_MAX        25573 /* Linearfuehrung hinteres Ende Wasserwaage  Max.    */
#define AP_LINEARF_MITTE_MAX        25574 /* Linearfuehrung Mitte         Wasserwaage  Max.    */
#define AP_LINEARF_VENDE_QUER       25575 /* Linearfuehrung vorderes Ende Wasserwaage  Quer    */
#define AP_LINEARF_HENDE_QUER       25576 /* Linearfuehrung hinteres Ende Wasserwaage  Quer    */
#define AP_LINEARF_MITTE_B          25577 /* Linearfuehrung Mitte         Wasserwaage  B-Seite */
#define AP_LINEARF_MITTE_H          25578 /* Linearfuehrung Mitte         Wasserwaage  H-Seite */
#define AP_DUESENSP_BOHR_ZENTR_B    25579 /* Duesenspitze Abstand Bohrung Zentrierung  B-Seite */
#define AP_DUESENSP_BOHR_ZENTR_H    25580 /* Duesenspitze Abstand Bohrung Zentrierung  H-Seite */
#define AP_DUESENSP_BOHR_ZENTR_O    25581 /* Duesenspitze Abstand Bohrung Zentrierung  Oben    */
#define AP_DUESENSP_BOHR_ZENTR_U    25582 /* Duesenspitze Abstand Bohrung Zentrierung  Unten   */

#define AP_TEST_ACTIVE              25588 /* 1 wenn Test aktiv, sonst 0                        */
#define AP_SELECTED_TEST            25589 /* Ausgewaehlter Test                                */

/* Werte fuer Test "Druckregelung Ohne Polster", VG=Vorgabe, M=Messwerte */
#define AP_VGDROP_ANZSTUFEN         25590 /* Anzahl Spritzstufen                               */
#define AP_VGDROP_INJPRES1          25591 /* Sollwert Spritzdruck Agg.1 Stufe 1-6              */
#define AP_VGDROP_SWITCHPRES1       25592 /* Sollwert Umschaltdruck Agg.1 Stufe 1-5            */
#define AP_VGDROP_INJSPEED1         25593 /* Sollwert Spritzgeschwindigkeit Agg.1 Stufe 1-6    */
#define AP_VGDROP_INJSTROKE1        25594 /* Sollwert Umschaltpunkt Agg.1 Stufe 1-5            */
#define AP_VGDROP_INJTIME1          25595 /* Sollwert Spritzzeit Agg.1 Stufe 1-6               */
#define AP_VGDROP_PLASTWEG          25596 /* Plastifizierweg                                   */
#define AP_VGDROP_WEG1              25597 /* S.40 Weg1                                         */
#define AP_VGDROP_DREHZAHL1         25598 /* S.40 Drehzahl 1                                   */
#define AP_VGDROP_DREHZAHL2         25599 /* S.40 Drehzahl 2                                   */
#define AP_VGDROP_STAUDRUCK1        25600 /* S.40 Staudruck 1                                  */
#define AP_VGDROP_STAUDRUCK2        25601 /* S.40 Staudruck 2                                  */
#define AP_VGDROP_STAUDRUCKHAND     25602 /* S.40 Staudruck im Handbetrieb                     */
#define AP_VGDROP_SNRUECKZUGVOR_S   25603 /* S.40 Schneckenrueckzug vor Plastifizieren         */
#define AP_VGDROP_SNRUECKZUGVOR_V   25604 /* S.40 Rueckzugsgeschwindigkeit vor Plastifizieren  */
#define AP_VGDROP_SNRUECKZUGNACH_S  25605 /* S.40 Schneckenrueckzug nach Plastifizieren        */
#define AP_VGDROP_SNRUECKZUGNACH_V  25606 /* S.40 Rueckzugsgeschwindigkeit nach Plastifizieren */
#define AP_VGDROP_STAUDRUCKENTLAST  25607 /* S.40 Staudruckentlastung nach Plastifizieren      */
#define AP_VGDROP_VERSCHLUSSDUESE   25608 /* S.40 Verschlussduese                              */
#define AP_VGDROP_PLASTVERZ         25609 /* S.40 Plastifizierverzoegerung                     */
#define AP_VGDROP_INTRUSION         25610 /* S.40 Intrusion                                    */
#define AP_VGDROP_KUEHLZEIT         25611 /* S.40 Kuehlzeit                                    */
#define AP_VGDROP_ZYL1_ZONE         25612 /* S.30 Zylindertemperatur Zone 0-8 (0=Einzug)       */
#define AP_VGDROP_TOL_INJPRESIST    25613 /* Toleranz Istwert Spritzdruck +/- in bar           */
#define AP_MDROP_INJPRESIST1        25614 /* Istwert Spritzdruck Agg.1 Stufe 1-6               */

/* Werte fuer Test "Druckregelung Mit Polster", VG=Vorgabe, M=Messwerte */
#define AP_VGDRMP_ANZSTUFEN         25620 /* Anzahl Spritzstufen                               */
#define AP_VGDRMP_INJPRES1          25621 /* Sollwert Spritzdruck Agg.1 Stufe 1-6              */
#define AP_VGDRMP_SWITCHPRES1       25622 /* Sollwert Umschaltdruck Agg.1 Stufe 1-5            */
#define AP_VGDRMP_INJSPEED1         25623 /* Sollwert Spritzgeschwindigkeit Agg.1 Stufe 1-6    */
#define AP_VGDRMP_INJSTROKE1        25624 /* Sollwert Umschaltpunkt Agg.1 Stufe 1-5            */
#define AP_VGDRMP_INJTIME1          25625 /* Sollwert Spritzzeit Agg.1 Stufe 1-6               */
#define AP_VGDRMP_PLASTWEG          25626 /* Plastifizierweg                                   */
#define AP_VGDRMP_WEG1              25627 /* S.40 Weg1                                         */
#define AP_VGDRMP_DREHZAHL1         25628 /* S.40 Drehzahl 1                                   */
#define AP_VGDRMP_DREHZAHL2         25629 /* S.40 Drehzahl 2                                   */
#define AP_VGDRMP_STAUDRUCK1        25630 /* S.40 Staudruck 1                                  */
#define AP_VGDRMP_STAUDRUCK2        25631 /* S.40 Staudruck 2                                  */
#define AP_VGDRMP_STAUDRUCKHAND     25632 /* S.40 Staudruck im Handbetrieb                     */
#define AP_VGDRMP_SNRUECKZUGVOR_S   25633 /* S.40 Schneckenrueckzug vor Plastifizieren         */
#define AP_VGDRMP_SNRUECKZUGVOR_V   25634 /* S.40 Rueckzugsgeschwindigkeit vor Plastifizieren  */
#define AP_VGDRMP_SNRUECKZUGNACH_S  25635 /* S.40 Schneckenrueckzug nach Plastifizieren        */
#define AP_VGDRMP_SNRUECKZUGNACH_V  25636 /* S.40 Rueckzugsgeschwindigkeit nach Plastifizieren */
#define AP_VGDRMP_STAUDRUCKENTLAST  25637 /* S.40 Staudruckentlastung nach Plastifizieren      */
#define AP_VGDRMP_VERSCHLUSSDUESE   25638 /* S.40 Verschlussduese                              */
#define AP_VGDRMP_PLASTVERZ         25639 /* S.40 Plastifizierverzoegerung                     */
#define AP_VGDRMP_INTRUSION         25640 /* S.40 Intrusion                                    */
#define AP_VGDRMP_KUEHLZEIT         25641 /* S.40 Kuehlzeit                                    */
#define AP_VGDRMP_ZYL1_ZONE         25642 /* S.30 Zylindertemperatur Zone 0-8 (0=Einzug)       */
#define AP_VGDRMP_TOL_INJPRESIST    25643 /* Toleranz Istwert Spritzdruck +/- in bar           */
#define AP_MDRMP_INJPRESIST1        25644 /* Istwert Spritzdruck Agg.1 Stufe 1-6               */

/* Test "Handabspritzen 85 Bar" */
#define AP_HANDABSPR_TOL            25650 /* Toleranz +- in Bar                                */
#define AP_HANDABSPR_IQT            25651 /* Wert aus IQT-Register                             */
#define AP_HANDABSPR_MANOMETER      25652 /* gemessener Wert                                   */

/* Werte fuer Test "Geschwindigkeitsregelung", VG=Vorgabe, M=Messwerte */
#define AP_VGGR_ANZSTUFEN           25660 /* Anzahl Spritzstufen                               */
#define AP_VGGR_INJPRES1            25661 /* Sollwert Spritzdruck Agg.1 Stufe 1-6              */
#define AP_VGGR_SWITCHPRES1         25662 /* Sollwert Umschaltdruck Agg.1 Stufe 1-5            */
#define AP_VGGR_INJSPEED1           25663 /* Sollwert Spritzgeschwindigkeit Agg.1 Stufe 1-6    */
#define AP_VGGR_INJSTROKE1          25664 /* Sollwert Umschaltpunkt Agg.1 Stufe 1-5            */
#define AP_VGGR_INJTIME1            25665 /* Sollwert Spritzzeit Agg.1 Stufe 1-6               */
#define AP_VGGR_PLASTWEG            25666 /* Plastifizierweg                                   */
#define AP_VGGR_WEG1                25667 /* S.40 Weg1                                         */
#define AP_VGGR_DREHZAHL1           25668 /* S.40 Drehzahl 1                                   */
#define AP_VGGR_DREHZAHL2           25669 /* S.40 Drehzahl 2                                   */
#define AP_VGGR_STAUDRUCK1          25670 /* S.40 Staudruck 1                                  */
#define AP_VGGR_STAUDRUCK2          25671 /* S.40 Staudruck 2                                  */
#define AP_VGGR_STAUDRUCKHAND       25672 /* S.40 Staudruck im Handbetrieb                     */
#define AP_VGGR_SNRUECKZUGVOR_S     25673 /* S.40 Schneckenrueckzug vor Plastifizieren         */
#define AP_VGGR_SNRUECKZUGVOR_V     25674 /* S.40 Rueckzugsgeschwindigkeit vor Plastifizieren  */
#define AP_VGGR_SNRUECKZUGNACH_S    25675 /* S.40 Schneckenrueckzug nach Plastifizieren        */
#define AP_VGGR_SNRUECKZUGNACH_V    25676 /* S.40 Rueckzugsgeschwindigkeit nach Plastifizieren */
#define AP_VGGR_STAUDRUCKENTLAST    25677 /* S.40 Staudruckentlastung nach Plastifizieren      */
#define AP_VGGR_VERSCHLUSSDUESE     25678 /* S.40 Verschlussduese                              */
#define AP_VGGR_PLASTVERZ           25679 /* S.40 Plastifizierverzoegerung                     */
#define AP_VGGR_INTRUSION           25680 /* S.40 Intrusion                                    */
#define AP_VGGR_KUEHLZEIT           25681 /* S.40 Kuehlzeit                                    */
#define AP_VGGR_ZYL1_ZONE           25682 /* S.30 Zylindertemperatur Zone 0-8 (0=Einzug)       */
#define AP_VGGR_REF_INJTIMEIST      25683 /* Referenzwerte fuer Istwert Spritzzeiten           */
#define AP_VGGR_TOLLOW_INJTIMEIST   25684 /* Untere Toleranz Istwert Spritzzeiten              */
#define AP_VGGR_TOLHIGH_INJTIMEIST  25685 /* Obere  Toleranz Istwert Spritzzeiten              */
#define AP_VGGR_TOL_INJPRESISTPH6   25686 /* Toleranz Istwert Spritzdruck Stufe 6              */
#define AP_MGR_INJTIMEIST1          25687 /* Istwert Spritzzeiten Agg.1 Stufe 1-6              */
#define AP_MGR_INJPRESIST1          25688 /* Istwert Spritzdruecke Agg.1 Stufe 1-6             */

/* Test "Plastifizierweg max" */
#define AP_PLASTMAX_TOL             25690 /* Toleranz +- in mm                                 */
#define AP_PLASTMAX_IQT             25691 /* Wert aus IQT-Register                             */
#define AP_PLASTMAX_MESS            25692 /* gemessener Wert                                   */

/* Werte fuer Test "Plastifizieren/Schneckenrueckzug/Staudruck 1" */
/* Staudruckentlastung=0, ohne Schneckenrueckzug, Staudruck 0Bar  */
#define AP_PSS1_PLASTWEG            25700 /* Plastifizierweg                                   */
#define AP_PSS1_DREHZAHL1           25701 /* S.40 Drehzahl 1                                   */
#define AP_PSS1_DREHZAHL2           25702 /* S.40 Drehzahl 2                                   */
#define AP_PSS1_STAUDRUCK1          25703 /* S.40 Staudruck 1                                  */
#define AP_PSS1_STAUDRUCK2          25704 /* S.40 Staudruck 2                                  */
#define AP_PSS1_SNRUECKZUGVOR_S     25705 /* S.40 Schneckenrueckzug vor Plastifizieren         */
#define AP_PSS1_SNRUECKZUGVOR_V     25706 /* S.40 Rueckzugsgeschwindigkeit vor Plastifizieren  */
#define AP_PSS1_SNRUECKZUGNACH_S    25707 /* S.40 Schneckenrueckzug nach Plastifizieren        */
#define AP_PSS1_SNRUECKZUGNACH_V    25708 /* S.40 Rueckzugsgeschwindigkeit nach Plastifizieren */
#define AP_PSS1_STAUDRUCKENTLAST    25709 /* S.40 Staudruckentlastung nach Plastifizieren      */
#define AP_PSS1_PLASTVERZ           25710 /* S.40 Plastifizierverzoegerung                     */
#define AP_PSS1_KUEHLZEIT           25711 /* S.40 Kuehlzeit                                    */
#define AP_PSS1_TOLLOW_PLASTWEG     25712 /* Toleranz unten Plastifizierweg ist                */
#define AP_PSS1_TOLHIGH_PLASTWEG    25713 /* Toleranz oben  Plastifizierweg ist                */
#define AP_PSS1_PLASTWEG_IST        25714 /* Plastifizierweg Ist IQT-Wert                      */
#define AP_PSS1_ZEIT_IST            25715 /* Zeit Ist IQT-Wert                                 */
#define AP_PSS1_STAUDRUCK_IST       25716 /* Staudruck Ist gemessener Wert                     */
#define AP_PSS1_DREHZAHL_IST        25717 /* Drehzahl Ist IQT-Wert                             */

/* Werte fuer Test "Plastifizieren/Schneckenrueckzug/Staudruck 2" */
/* Staudruckentlastung=1, ohne Schneckenrueckzug, Staudruck 0Bar  */
#define AP_PSS2_PLASTWEG            25720 /* Plastifizierweg                                   */
#define AP_PSS2_DREHZAHL1           25721 /* S.40 Drehzahl 1                                   */
#define AP_PSS2_DREHZAHL2           25722 /* S.40 Drehzahl 2                                   */
#define AP_PSS2_STAUDRUCK1          25723 /* S.40 Staudruck 1                                  */
#define AP_PSS2_STAUDRUCK2          25724 /* S.40 Staudruck 2                                  */
#define AP_PSS2_SNRUECKZUGVOR_S     25725 /* S.40 Schneckenrueckzug vor Plastifizieren         */
#define AP_PSS2_SNRUECKZUGVOR_V     25726 /* S.40 Rueckzugsgeschwindigkeit vor Plastifizieren  */
#define AP_PSS2_SNRUECKZUGNACH_S    25727 /* S.40 Schneckenrueckzug nach Plastifizieren        */
#define AP_PSS2_SNRUECKZUGNACH_V    25728 /* S.40 Rueckzugsgeschwindigkeit nach Plastifizieren */
#define AP_PSS2_STAUDRUCKENTLAST    25729 /* S.40 Staudruckentlastung nach Plastifizieren      */
#define AP_PSS2_PLASTVERZ           25730 /* S.40 Plastifizierverzoegerung                     */
#define AP_PSS2_KUEHLZEIT           25731 /* S.40 Kuehlzeit                                    */
#define AP_PSS2_TOLLOW_PLASTWEG     25732 /* Toleranz unten Plastifizierweg ist                */
#define AP_PSS2_TOLHIGH_PLASTWEG    25733 /* Toleranz oben  Plastifizierweg ist                */
#define AP_PSS2_PLASTWEG_IST        25734 /* Plastifizierweg Ist IQT-Wert                      */
#define AP_PSS2_ZEIT_IST            25735 /* Zeit Ist IQT-Wert                                 */
#define AP_PSS2_STAUDRUCK_IST       25736 /* Staudruck Ist gemessener Wert                     */
#define AP_PSS2_DREHZAHL_IST        25737 /* Drehzahl Ist IQT-Wert                             */

/* Werte fuer Test "Plastifizieren/Schneckenrueckzug/Staudruck 3" */
/* Staudruckentlastung=1, mit  Schneckenrueckzug, Staudruck 3Bar  */
#define AP_PSS3_PLASTWEG            25740 /* Plastifizierweg                                   */
#define AP_PSS3_DREHZAHL1           25741 /* S.40 Drehzahl 1                                   */
#define AP_PSS3_DREHZAHL2           25742 /* S.40 Drehzahl 2                                   */
#define AP_PSS3_STAUDRUCK1          25743 /* S.40 Staudruck 1                                  */
#define AP_PSS3_STAUDRUCK2          25744 /* S.40 Staudruck 2                                  */
#define AP_PSS3_SNRUECKZUGVOR_S     25745 /* S.40 Schneckenrueckzug vor Plastifizieren         */
#define AP_PSS3_SNRUECKZUGVOR_V     25746 /* S.40 Rueckzugsgeschwindigkeit vor Plastifizieren  */
#define AP_PSS3_SNRUECKZUGNACH_S    25747 /* S.40 Schneckenrueckzug nach Plastifizieren        */
#define AP_PSS3_SNRUECKZUGNACH_V    25748 /* S.40 Rueckzugsgeschwindigkeit nach Plastifizieren */
#define AP_PSS3_STAUDRUCKENTLAST    25749 /* S.40 Staudruckentlastung nach Plastifizieren      */
#define AP_PSS3_PLASTVERZ           25750 /* S.40 Plastifizierverzoegerung                     */
#define AP_PSS3_KUEHLZEIT           25751 /* S.40 Kuehlzeit                                    */
#define AP_PSS3_TOLLOW_PLASTWEG     25752 /* Toleranz unten Plastifizierweg ist                */
#define AP_PSS3_TOLHIGH_PLASTWEG    25753 /* Toleranz oben  Plastifizierweg ist                */
#define AP_PSS3_PLASTWEG_IST        25754 /* Plastifizierweg Ist IQT-Wert                      */
#define AP_PSS3_ZEIT_IST            25755 /* Zeit Ist IQT-Wert                                 */
#define AP_PSS3_STAUDRUCK_IST       25756 /* Staudruck Ist gemessener Wert                     */
#define AP_PSS3_DREHZAHL_IST        25757 /* Drehzahl Ist IQT-Wert                             */

/* Werte fuer Test 1 "Schliesseinheit Werkzeuggeschwindigkeit geregelter Betrieb"               */
/* 20 mm/sec, 100 mm                                                                            */
#define AP_SWG1_EINRICHTDRUCK        25760 /* S.50 Einrichtdruck                                */
#define AP_SWG1_WS_S2                25761 /* S.50 Weg 2                                        */
#define AP_SWG1_WS_S3                25762 /* S.50 Weg 3                                        */
#define AP_SWG1_WS_V1                25763 /* S.50 Geschwindigkeit 1                            */
#define AP_SWG1_WS_V2                25764 /* S.50 Geschwindigkeit 2                            */
#define AP_SWG1_WS_V3                25765 /* S.50 Geschwindigkeit 3                            */
#define AP_SWG1_START_WKZSICH        25766 /* S.50 Start Werkzeugsicherung 1                    */
#define AP_SWG1_DRUCK_WKZSICH        25767 /* S.50 Druck Werkzeugsicherung 1                    */
#define AP_SWG1_UEBERW_WKZSICH       25768 /* S.50 Ueberwachaungszeit Werkzeugsicherung 1       */
#define AP_SWG1_START_SCHLKR_AUFB    25769 /* S.50 Start Schliesskraftaufbau                    */
#define AP_SWG1_SCHLIESSKRAFT        25770 /* S.50 Schliesskraft                                */
#define AP_SWG1_WKZ_OEFFN_WEG        25771 /* S.51 Werkzeugoeffnungsweg                         */
#define AP_SWG1_ERHOE_OEFN_KRAFT     25772 /* S.51 Erhoehte Oeffnungskraft bei Wegpunkt         */
#define AP_SWG1_WOE_S1               25773 /* S.51 Weg 1                                        */
#define AP_SWG1_WOE_S2               25774 /* S.51 Weg 2                                        */
#define AP_SWG1_WOE_V1               25775 /* S.51 Geschwindigkeit 1                            */
#define AP_SWG1_WOE_V2               25776 /* S.51 Geschwindigkeit 2                            */
#define AP_SWG1_WOE_V3               25777 /* S.51 Geschwindigkeit 3                            */
#define AP_SWG1_PAUSENZEIT           25778 /* S.51 Pausenzeit                                   */
#define AP_SWG1_TOLLOW_WEG           25779 /* Toleranz unten Weg                                */
#define AP_SWG1_TOLHIGH_WEG          25780 /* Toleranz oben  Weg                                */
#define AP_SWG1_TOLLOW_ZEIT_OEFF     25781 /* Toleranz unten Zeit Wkz. oeffnen                  */
#define AP_SWG1_TOLHIGH_ZEIT_OEFF    25782 /* Toleranz oben  Zeit Wkz. oeffnen                  */
#define AP_SWG1_REF_ZEIT_OEFF        25783 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */
#define AP_SWG1_WKZ_OEFFN_WEG_IST    25784 /* IST Werkzeugoeffnungsweg                          */
#define AP_SWG1_WKZ_OEF_ZEIT_IST     25785 /* IST Zeit Werkzeug oeffnen                         */
#define AP_SWG1_WKZ_SCHL_ZEIT_IST    25786 /* IST Zeit Werkzeug schliessen                      */
#define AP_SWG1_TOLLOW_ZEIT_SCHL     25787 /* Toleranz unten Zeit Wkz. schliessen               */
#define AP_SWG1_TOLHIGH_ZEIT_SCHL    25788 /* Toleranz oben  Zeit Wkz. schliessen               */
#define AP_SWG1_REF_ZEIT_SCHL        25789 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */

/* Werte fuer Test 2 "Schliesseinheit Werkzeuggeschwindigkeit geregelter Betrieb"               */
/* 200 mm/sec, 500 mm                                                                           */
#define AP_SWG2_EINRICHTDRUCK        25790 /* S.50 Einrichtdruck                                */
#define AP_SWG2_WS_S2                25791 /* S.50 Weg 2                                        */
#define AP_SWG2_WS_S3                25792 /* S.50 Weg 3                                        */
#define AP_SWG2_WS_V1                25793 /* S.50 Geschwindigkeit 1                            */
#define AP_SWG2_WS_V2                25794 /* S.50 Geschwindigkeit 2                            */
#define AP_SWG2_WS_V3                25795 /* S.50 Geschwindigkeit 3                            */
#define AP_SWG2_START_WKZSICH        25796 /* S.50 Start Werkzeugsicherung 1                    */
#define AP_SWG2_DRUCK_WKZSICH        25797 /* S.50 Druck Werkzeugsicherung 1                    */
#define AP_SWG2_UEBERW_WKZSICH       25798 /* S.50 Ueberwachaungszeit Werkzeugsicherung 1       */
#define AP_SWG2_START_SCHLKR_AUFB    25799 /* S.50 Start Schliesskraftaufbau                    */
#define AP_SWG2_SCHLIESSKRAFT        25800 /* S.50 Schliesskraft                                */
#define AP_SWG2_WKZ_OEFFN_WEG        25801 /* S.51 Werkzeugoeffnungsweg                         */
#define AP_SWG2_ERHOE_OEFN_KRAFT     25802 /* S.51 Erhoehte Oeffnungskraft bei Wegpunkt         */
#define AP_SWG2_WOE_S1               25803 /* S.51 Weg 1                                        */
#define AP_SWG2_WOE_S2               25804 /* S.51 Weg 2                                        */
#define AP_SWG2_WOE_V1               25805 /* S.51 Geschwindigkeit 1                            */
#define AP_SWG2_WOE_V2               25806 /* S.51 Geschwindigkeit 2                            */
#define AP_SWG2_WOE_V3               25807 /* S.51 Geschwindigkeit 3                            */
#define AP_SWG2_PAUSENZEIT           25808 /* S.51 Pausenzeit                                   */
#define AP_SWG2_TOLLOW_WEG           25809 /* Toleranz unten Weg                                */
#define AP_SWG2_TOLHIGH_WEG          25810 /* Toleranz oben  Weg                                */
#define AP_SWG2_TOLLOW_ZEIT_OEFF     25811 /* Toleranz unten Zeit Wkz. oeffnen                  */
#define AP_SWG2_TOLHIGH_ZEIT_OEFF    25812 /* Toleranz oben  Zeit Wkz. oeffnen                  */
#define AP_SWG2_REF_ZEIT_OEFF        25813 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */
#define AP_SWG2_WKZ_OEFFN_WEG_IST    25814 /* IST Werkzeugoeffnungsweg                          */
#define AP_SWG2_WKZ_OEF_ZEIT_IST     25815 /* IST Zeit Werkzeug oeffnen                         */
#define AP_SWG2_WKZ_SCHL_ZEIT_IST    25816 /* IST Zeit Werkzeug schliessen                      */
#define AP_SWG2_TOLLOW_ZEIT_SCHL     25817 /* Toleranz unten Zeit Wkz. schliessen               */
#define AP_SWG2_TOLHIGH_ZEIT_SCHL    25818 /* Toleranz oben  Zeit Wkz. schliessen               */
#define AP_SWG2_REF_ZEIT_SCHL        25819 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */

/* Werte fuer Test 3 "Schliesseinheit Werkzeuggeschwindigkeit geregelter Betrieb"               */
/* 1000 mm/sec, 500 mm                                                                          */
#define AP_SWG3_EINRICHTDRUCK        25820 /* S.50 Einrichtdruck                                */
#define AP_SWG3_WS_S2                25821 /* S.50 Weg 2                                        */
#define AP_SWG3_WS_S3                25822 /* S.50 Weg 3                                        */
#define AP_SWG3_WS_V1                25823 /* S.50 Geschwindigkeit 1                            */
#define AP_SWG3_WS_V2                25824 /* S.50 Geschwindigkeit 2                            */
#define AP_SWG3_WS_V3                25825 /* S.50 Geschwindigkeit 3                            */
#define AP_SWG3_START_WKZSICH        25826 /* S.50 Start Werkzeugsicherung 1                    */
#define AP_SWG3_DRUCK_WKZSICH        25827 /* S.50 Druck Werkzeugsicherung 1                    */
#define AP_SWG3_UEBERW_WKZSICH       25828 /* S.50 Ueberwachaungszeit Werkzeugsicherung 1       */
#define AP_SWG3_START_SCHLKR_AUFB    25829 /* S.50 Start Schliesskraftaufbau                    */
#define AP_SWG3_SCHLIESSKRAFT        25830 /* S.50 Schliesskraft                                */
#define AP_SWG3_WKZ_OEFFN_WEG        25831 /* S.51 Werkzeugoeffnungsweg                         */
#define AP_SWG3_ERHOE_OEFN_KRAFT     25832 /* S.51 Erhoehte Oeffnungskraft bei Wegpunkt         */
#define AP_SWG3_WOE_S1               25833 /* S.51 Weg 1                                        */
#define AP_SWG3_WOE_S2               25834 /* S.51 Weg 2                                        */
#define AP_SWG3_WOE_V1               25835 /* S.51 Geschwindigkeit 1                            */
#define AP_SWG3_WOE_V2               25836 /* S.51 Geschwindigkeit 2                            */
#define AP_SWG3_WOE_V3               25837 /* S.51 Geschwindigkeit 3                            */
#define AP_SWG3_PAUSENZEIT           25838 /* S.51 Pausenzeit                                   */
#define AP_SWG3_TOLLOW_WEG           25839 /* Toleranz unten Weg                                */
#define AP_SWG3_TOLHIGH_WEG          25840 /* Toleranz oben  Weg                                */
#define AP_SWG3_TOLLOW_ZEIT_OEFF     25841 /* Toleranz unten Zeit Wkz. oeffnen                  */
#define AP_SWG3_TOLHIGH_ZEIT_OEFF    25842 /* Toleranz oben  Zeit Wkz. oeffnen                  */
#define AP_SWG3_REF_ZEIT_OEFF        25843 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */
#define AP_SWG3_WKZ_OEFFN_WEG_IST    25844 /* IST Werkzeugoeffnungsweg                          */
#define AP_SWG3_WKZ_OEF_ZEIT_IST     25845 /* IST Zeit Werkzeug oeffnen                         */
#define AP_SWG3_WKZ_SCHL_ZEIT_IST    25846 /* IST Zeit Werkzeug schliessen                      */
#define AP_SWG3_TOLLOW_ZEIT_SCHL     25847 /* Toleranz unten Zeit Wkz. schliessen               */
#define AP_SWG3_TOLHIGH_ZEIT_SCHL    25848 /* Toleranz oben  Zeit Wku. schliessen               */
#define AP_SWG3_REF_ZEIT_SCHL        25849 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */

/* Werte fuer Test "Schliesseinheit Einstellung V14"                                            */
#define AP_SV14_EINRICHTDRUCK        25850 /* S.50 Einrichtdruck                                */
#define AP_SV14_WS_S2                25851 /* S.50 Weg 2                                        */
#define AP_SV14_WS_S3                25852 /* S.50 Weg 3                                        */
#define AP_SV14_WS_V1                25853 /* S.50 Geschwindigkeit 1                            */
#define AP_SV14_WS_V2                25854 /* S.50 Geschwindigkeit 2                            */
#define AP_SV14_WS_V3                25855 /* S.50 Geschwindigkeit 3                            */
#define AP_SV14_START_WKZSICH        25856 /* S.50 Start Werkzeugsicherung 1                    */
#define AP_SV14_DRUCK_WKZSICH        25857 /* S.50 Druck Werkzeugsicherung 1                    */
#define AP_SV14_UEBERW_WKZSICH       25858 /* S.50 Ueberwachaungszeit Werkzeugsicherung 1       */
#define AP_SV14_START_SCHLKR_AUFB    25859 /* S.50 Start Schliesskraftaufbau                    */
#define AP_SV14_SCHLIESSKRAFT        25860 /* S.50 Schliesskraft                                */
#define AP_SV14_WKZ_OEFFN_WEG        25861 /* S.51 Werkzeugoeffnungsweg                         */
#define AP_SV14_ERHOE_OEFN_KRAFT     25862 /* S.51 Erhoehte Oeffnungskraft bei Wegpunkt         */
#define AP_SV14_WOE_S1               25863 /* S.51 Weg 1                                        */
#define AP_SV14_WOE_S2               25864 /* S.51 Weg 2                                        */
#define AP_SV14_WOE_V1               25865 /* S.51 Geschwindigkeit 1                            */
#define AP_SV14_WOE_V2               25866 /* S.51 Geschwindigkeit 2                            */
#define AP_SV14_WOE_V3               25867 /* S.51 Geschwindigkeit 3                            */
#define AP_SV14_PAUSENZEIT           25868 /* S.51 Pausenzeit                                   */
#define AP_SV14_V14_IST              25869 /* Istwert V14 (Kopie von S.17.2 4-B0249)            */
#define AP_SV14_V14_MESS             25870 /* Messwert V14 (Handeintragung)                     */

/* Werte fuer Maximalen Werkzeugoeffnungsweg                                                    */
#define AP_WKZOFFNW_MAX_IQT          25875 /* Werkzeugoeffnungsweg max. IQT-Wert                */
#define AP_WKZOFFNW_MAX_MESS         25876 /* Werkzeugoeffnungsweg max. gemessener Wert         */
#define AP_WKZOFFNW_MAX_TOL          25877 /* Werkzeugoeffnungsweg max. Toleranz                */

/* Werte fuer Test "Schliesskraft Maximalwert"                                                  */
/* Als Vorgabewerte werden die Werte des Tests Werkzeuggeschwindigkeit verwendet                */
#define AP_SCHLKRAFT_MAX_DRUCK_IQT   25880 /* Druck bei maximaler Schliesskraft IQT-Wert        */
#define AP_SCHLKRAFT_MAX_DRUCK_MESS  25881 /* Druck bei maximaler Schliesskraft gemessener Wert */
#define AP_SCHLKRAFT_MAX_DRUCK_TOL   25882 /* Toleranz fuer Druck                               */
#define AP_SCHLKRAFT_MAX_ZEIT_IQT    25883 /* Schliesskraftaufbauzeit IQT-Wert                  */
#define AP_SCHLKRAFT_MAX_ZEIT_REF    25884 /* Schliesskraftaufbauzeit Referenzwert              */
#define AP_SCHLKRAFT_MAX_ZEIT_TOL    25885 /* Toleranz fuer Schliesskraftaufbauzeit             */
#define AP_SCHLKRAFT_MAX_DRUCK_REF   25886 /* Referenzwert fuer Druck                           */

/* Werte fuer Test "Aggregatbewegung"                                                           */
#define AP_AGGBEW_DUESENABH_WAHL     25890 /* S.49 Wahl Duesenabhebung                          */
#define AP_AGGBEW_DUESENABH_VERZ     25891 /* S.49 Duesenabhebung verzoegert um                 */
#define AP_AGGBEW_DUESENABH_ZEIT     25892 /* S.49 Duesenabhebezeit                             */
#define AP_AGGBEW_DUESENGESCHW_VOR   25893 /* S.49 Duesengeschwindigkeit vor in %               */
#define AP_AGGBEW_DUESENGESCHW_ZUR   25894 /* S.49 Duesengeschwindigkeit zurueck in %           */
#define AP_AGGBEW_DUESENANPRESSDR    25895 /* S.49 Duesenanpressdruck                           */
#define AP_AGGBEW_AGGVOR_ZEIT_REF    25896 /* Zeit Aggregat vor Referenzwert                    */
#define AP_AGGBEW_AGGVOR_ZEIT_TOL    25897 /* Zeit Aggregat vor Toleranz                        */
#define AP_AGGBEW_WEG_REF            25898 /* Aggregatbewegung Referenzwert                     */
#define AP_AGGBEW_WEG_TOL            25899 /* Aggregatbewegung Toleranz                         */
#define AP_AGGBEW_AGGVOR_ZEIT_IQT    25900 /* Zeit Aggregat vor IQT-Wert                        */
#define AP_AGGBEW_WEG_MESS           25901 /* Aggregatbewegung gemessener Weg                   */

/* Werte fuer Test 1 "Auswerfer im geregelten Betrieb"                                          */
/* 20 mm/sec, 100 mm                                                                            */
#define AP_AG1_AUSWERFERWEG          25910 /* S.52 Auswerferweg                                 */
#define AP_AG1_AUSW_GERASTET         25911 /* S.52 Auswerfer gerastet ja/nein                   */
#define AP_AG1_AUSWHUEBE             25912 /* S.52 Anzahl Auswerferhuebe                        */
#define AP_AG1_AUSW_RUECKWEG         25913 /* S.52 Auswerferrueckweg bei Mehrfachhub            */
#define AP_AG1_S52_S1                25914 /* S.52 s 1                                          */
#define AP_AG1_S52_V1                25915 /* S.52 v 1                                          */
#define AP_AG1_S52_V2                25916 /* S.52 v 2 vor                                      */
#define AP_AG1_S52_V3                25917 /* S.52 v 3 zurueck                                  */
#define AP_AG1_WARTEZEIT_UMSCH       25918 /* S.52 Wartezeit am Umschaltpunkt vor               */
#define AP_AG1_WARTEZEIT_VORNE       25919 /* S.52 Wartezeit vorne                              */
#define AP_AG1_TOLLOW_WEG            25920 /* Toleranz unten Weg                                */
#define AP_AG1_TOLHIGH_WEG           25921 /* Toleranz oben  Weg                                */
#define AP_AG1_TOLLOW_ZEIT           25922 /* Toleranz unten Zeit                               */
#define AP_AG1_TOLHIGH_ZEIT          25923 /* Toleranz oben  Zeit                               */
#define AP_AG1_REF_ZEIT              25924 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */
#define AP_AG1_AW_ZURUECK_WEG_IST    25925 /* IST Auswerferweg                                  */
#define AP_AG1_AW_VOR_ZEIT_IST       25926 /* IST Zeit Auswerfer vor                            */
#define AP_AG1_AW_ZURUECK_ZEIT_IST   25927 /* IST Zeit Auswerfer zurueck                        */
#define AP_AG1_S52_DRUCK_VOR         25928 /* S.52 p vor                                        */
#define AP_AG1_S52_DRUCK_ZURUECK     25929 /* S.52 p zurück                                     */

/* Werte fuer Test 2 "Auswerfer im geregelten Betrieb"                                          */
/* 100 mm/sec, 100 mm                                                                            */
#define AP_AG2_AUSWERFERWEG          25930 /* S.52 Auswerferweg                                 */
#define AP_AG2_AUSW_GERASTET         25931 /* S.52 Auswerfer gerastet ja/nein                   */
#define AP_AG2_AUSWHUEBE             25932 /* S.52 Anzahl Auswerferhuebe                        */
#define AP_AG2_AUSW_RUECKWEG         25933 /* S.52 Auswerferrueckweg bei Mehrfachhub            */
#define AP_AG2_S52_S1                25934 /* S.52 s 1                                          */
#define AP_AG2_S52_V1                25935 /* S.52 v 1                                          */
#define AP_AG2_S52_V2                25936 /* S.52 v 2 vor                                      */
#define AP_AG2_S52_V3                25937 /* S.52 v 3 zurueck                                  */
#define AP_AG2_WARTEZEIT_UMSCH       25938 /* S.52 Wartezeit am Umschaltpunkt vor               */
#define AP_AG2_WARTEZEIT_VORNE       25939 /* S.52 Wartezeit vorne                              */
#define AP_AG2_TOLLOW_WEG            25940 /* Toleranz unten Weg                                */
#define AP_AG2_TOLHIGH_WEG           25941 /* Toleranz oben  Weg                                */
#define AP_AG2_TOLLOW_ZEIT           25942 /* Toleranz unten Zeit                               */
#define AP_AG2_TOLHIGH_ZEIT          25943 /* Toleranz oben  Zeit                               */
#define AP_AG2_REF_ZEIT              25944 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */
#define AP_AG2_AW_ZURUECK_WEG_IST    25945 /* IST Auswerferweg                                  */
#define AP_AG2_AW_VOR_ZEIT_IST       25946 /* IST Zeit Auswerfer vor                            */
#define AP_AG2_AW_ZURUECK_ZEIT_IST   25947 /* IST Zeit Auswerfer zurueck                        */
#define AP_AG2_S52_DRUCK_VOR         25948 /* S.52 p vor                                        */
#define AP_AG2_S52_DRUCK_ZURUECK     25949 /* S.52 p zurück                                     */

/* Werte fuer Test 3 "Auswerfer im geregelten Betrieb"                                          */
/* 300 mm/sec, 100 mm                                                                            */
#define AP_AG3_AUSWERFERWEG          25950 /* S.52 Auswerferweg                                 */
#define AP_AG3_AUSW_GERASTET         25951 /* S.52 Auswerfer gerastet ja/nein                   */
#define AP_AG3_AUSWHUEBE             25952 /* S.52 Anzahl Auswerferhuebe                        */
#define AP_AG3_AUSW_RUECKWEG         25953 /* S.52 Auswerferrueckweg bei Mehrfachhub            */
#define AP_AG3_S52_S1                25954 /* S.52 s 1                                          */
#define AP_AG3_S52_V1                25955 /* S.52 v 1                                          */
#define AP_AG3_S52_V2                25956 /* S.52 v 2 vor                                      */
#define AP_AG3_S52_V3                25957 /* S.52 v 3 zurueck                                  */
#define AP_AG3_WARTEZEIT_UMSCH       25958 /* S.52 Wartezeit am Umschaltpunkt vor               */
#define AP_AG3_WARTEZEIT_VORNE       25959 /* S.52 Wartezeit vorne                              */
#define AP_AG3_TOLLOW_WEG            25960 /* Toleranz unten Weg                                */
#define AP_AG3_TOLHIGH_WEG           25961 /* Toleranz oben  Weg                                */
#define AP_AG3_TOLLOW_ZEIT           25962 /* Toleranz unten Zeit                               */
#define AP_AG3_TOLHIGH_ZEIT          25963 /* Toleranz oben  Zeit                               */
#define AP_AG3_REF_ZEIT              25964 /* Referenzwert fuer Toleranzueberpruefung der Zeit  */
#define AP_AG3_AW_ZURUECK_WEG_IST    25965 /* IST Auswerferweg                                  */
#define AP_AG3_AW_VOR_ZEIT_IST       25966 /* IST Zeit Auswerfer vor                            */
#define AP_AG3_AW_ZURUECK_ZEIT_IST   25967 /* IST Zeit Auswerfer zurueck                        */
#define AP_AG3_S52_DRUCK_VOR         25968 /* S.52 p vor                                        */
#define AP_AG3_S52_DRUCK_ZURUECK     25969 /* S.52 p zurück                                     */

/* Werte fuer Auswerfer Maximalweg (S.103.3)                                                    */
#define AP_AUSW_MAX_IQT              25970 /* Auswerferweg max. IQT-Wert                        */
#define AP_AUSW_MAX_MESS             25971 /* Auswerferweg max. gemessener Wert                 */
#define AP_AUSW_MAX_TOL              25972 /* Auswerferweg max. Toleranz                        */

/* Werte fuer Auswerfer Maximalweg (S.103.3)                                                    */
#define AP_AG1_S52_V4                25973 /* Test1 S.52 v 4 zurueck                            */
#define AP_AG2_S52_V4                25974 /* Test2 S.52 v 4 zurueck                            */
#define AP_AG3_S52_V4                25975 /* Test3 S.52 v 4 zurueck                            */


/* Werte fuer Einrichtdruck 100 bar (S.103.2)                                                   */
#define AP_ED100_IQT                 25980 /* Einrichtdruck 100 bar IQT-Wert                    */
#define AP_ED100_MESS                25981 /* Einrichtdruck 100 bar gemessener Wert             */
#define AP_ED100_TOL                 25982 /* Einrichtdruck 100 bar Toleranz                    */
#define AP_ED100_EINRICHTDRUCK       25983 /* Einrichtdruck 100 bar Sollwert Vorgabe            */

/* Werte fuer Düsenanlagekraft (S.103.2)                                                        */
#define AP_DAKRAFT_IQT               25990 /* Einrichtdruck 100 bar IQT-Wert                    */
#define AP_DAKRAFT_MESS              25991 /* Einrichtdruck 100 bar gemessener Wert             */
#define AP_DAKRAFT_TOL               25992 /* Einrichtdruck 100 bar Toleranz                    */

/* Werte fuer Auswerfer Maximaldruck (S.103.3) */
#define AP_AG1_S52_DRUCK_VOR2        25993 /* S.52 p vor 2     Test 1                           */
#define AP_AG1_S52_DRUCK_ZURUECK2    25994 /* S.52 p zurück 2  Test 1                           */
#define AP_AG2_S52_DRUCK_VOR2        25995 /* S.52 p vor 2     Test 2                           */
#define AP_AG2_S52_DRUCK_ZURUECK2    25996 /* S.52 p zurück 2  Test 2                           */
#define AP_AG3_S52_DRUCK_VOR2        25997 /* S.52 p vor 2     Test 3                           */
#define AP_AG3_S52_DRUCK_ZURUECK2    25998 /* S.52 p zurück 2  Test 3                           */

/* Register für den Kartenleser                                                                 */
#define ACCCARD_NEW_KEYCODE          26100 /* MEMCARD: Schlüsselschalterstellung für neue Karte */

/* Register für Anzahl Spritzstufen aus dem KProm */
#define MAX_INJCYC                   26101 /*   */      
/* Register fuer Werg-/Volumenumschaltung Produktionsstart S. 40.2  */
#define SVPH11A_VOL                  26102                                        
#define SVPH12A_VOL                  26103                                        
#define SVPH13A_VOL                  26104                                        
#define SVPH14A_VOL                  26105                                        
#define SVPH15A_VOL                  26106                                        
#define SVPH16A_VOL                  26107                                        
#define SVPH17A_VOL                  26108                                        
#define SVPH18A_VOL                  26109                                        
#define SVPH19A_VOL                  26110
#define SSPH11A_VOL                  26111                                        
#define SSPH12A_VOL                  26112
#define SSPH13A_VOL                  26113
#define SSPH14A_VOL                  26114
#define SSPH15A_VOL                  26115
#define SSPH16A_VOL                  26116
#define SSPH17A_VOL                  26117
#define SSPH18A_VOL                  26118
#define SSPH19A_VOL                  26119
#define SSDOS1A_VOL                  26120
#define SPPH11A_VOL                  26121                                        
#define SPPH12A_VOL                  26122
#define SPPH13A_VOL                  26123
#define SPPH14A_VOL                  26124
#define SPPH15A_VOL                  26125
#define SPPH16A_VOL                  26126
#define SPPH17A_VOL                  26127
#define SPPH18A_VOL                  26128
#define SPPH19A_VOL                  26129
#define SVPH21A_VOL                  26130                                        
#define SVPH22A_VOL                  26131                                        
#define SVPH23A_VOL                  26132                                        
#define SVPH24A_VOL                  26133                                        
#define SVPH25A_VOL                  26134                                        
#define SVPH26A_VOL                  26135                                        
#define SVPH27A_VOL                  26136                                        
#define SVPH28A_VOL                  26137                                        
#define SVPH29A_VOL                  26138
#define SSPH21A_VOL                  26139                                        
#define SSPH22A_VOL                  26140
#define SSPH23A_VOL                  26141
#define SSPH24A_VOL                  26142
#define SSPH25A_VOL                  26143
#define SSPH26A_VOL                  26144
#define SSPH27A_VOL                  26145
#define SSPH28A_VOL                  26146
#define SSPH29A_VOL                  26147
#define SSDOS2A_VOL                  26148
#define SPPH21A_VOL                  26149                                        
#define SPPH22A_VOL                  26150
#define SPPH23A_VOL                  26151
#define SPPH24A_VOL                  26152
#define SPPH25A_VOL                  26153
#define SPPH26A_VOL                  26154
#define SPPH27A_VOL                  26155
#define SPPH28A_VOL                  26156
#define SPPH29A_VOL                  26157

#endif         /* #ifndef _iqtreg */
