/****************************************************************************
*
*
*         ISCOSREG.H
*
*  HISTORY:
*     07.07.93 -MBa-    neu angelegt fuer B&R                      
*                       EWIKON herausgenommen
*                       **** Achtung Aenderungen in FXR werden nicht **
*                       **** beruecksichtigt -MBa- ********************
*     27.01.94 -MBa-    XRSON0 - XRSONA MIT Wkz-Auswerfer belegt   
*                       Airpress in den Standard                 
*     16.02.94 -TSchw-  Folgende Register neu eingefuegt:        
*                       - Fuer Option Atmen und Praegen:         
*                         IAPS_NRSTUF und IAPSSPWEG              
*                       - Fuer Werkzeugschnellspannen:           
*                         IWZS_SNSP, XXSNSP1 statt XRFAST1,      
*                         XXSNSP2 statt XRFAST2                  
*                       - Fuer Kernzuege Ausschrauben:           
*                         IKES_ARL    IKESTAVWO   IKESTAVSA      
*                         IKESTAAAU   IKESTAVSAU  IKESSAWSA      
*                         IKES_AZNS   IKES_AUESB  IKESVAUSG      
*                         IKESPAUSD   IKESPAUSND  IKESVAEING     
*                         IKESPAEIND  IKESPAEINND                
*               18.02.94        -MBa-      - XRFAST1 in IWZISACTPOS umbenannt   
*                         XRFAST2 in IQTINSPSTXT umbenannt
*     22.02.94 -PR-     Register fuer Qualitaetskontrolle und 
*                       Selektierweiche eingefuegt
*     26.07.95 -HAns-   XDHVWALR eingefuegt
*     10.08.95 -HAns-   XSEGPUST und XSEGPUST2 eingefuegt
*     04.01.96 -HAns-   Defines von 4500 bis 4623 fuer 3/4 Farben 
*                       eingefuegt.
*     15.01.96 -HAns-   Defines von 4624 4653 fuer 3/4 Farben eingefuegt.
*                       XSEGPUST3 und XSEGPUST4 eingefuegt.
*     26.01.96 -HAns-   XAGSTVVER1-4 und XSPSTVERZ1-4 eingefuegt.
*     29.01.96 -HAns-   XTABSZYL3 und XTABSZYL4 eingefuegt.
*     06.02.96 -HAns-   XSESSVERD1, XSESSVERD2 und XMSKSSNDUR1 eingefuegt
*                       XDIAGM37 - XDIAGM3A definiert.
*                       XAKTOUTPUT8 - XGKIKPROZ eingefuegt.
*     09.02.96 -HAns-   IAKTINPUT3, IAKTOUTPUT5 und IFORCEOUTPUT5 eingefuegt
*     15.02.96 -HAns-   XSNAGG3,4 , XSTAGG3,4 , XSTDUES3,4 XSVAG3V, XSVAG4V
*                       XSVAG3Z, XSVAG4Z, XSFAGG3,4 , XSTDOS3,4 , XSAG3PFO 
*                       und XSAG4PFO eingefuegt.
*                                 XAX6C (3045) in XRFAST10 umbenannt (3/4F)
*                       XXPFI3M und XXPFI4M eingefuegt.
*     11.03.96 -HAns-   IAKTINPUT34 eingefuegt.
*     12.03.96 -HAns-   IAKTOUTPUT9,36,39 eingefuegt.
*     21.03.96 -MB-     Prozessgrafik-Register fuer 4Farben erweitert.
*     15.04.96 -HAns-   Zeitanalyseregister Seite 17.1 auf Mehrfarbenmasch.
*                       erweitert (IAGGRVOR2-IDOS4).
*     29.04.96 -HAns-   XRFAST11, XRFAST12 und XRFAST13 eingefuegt.
*     02.07.96 -WS-     46 exclusive Register fuer neues Airpress nach
*                       Dr.Jaroschek eingefuegt (XAIR_ON bis XSPRES5_D4)
*     23.08.96 -HAns-   XWZGENMOD bis XWOIKGAIN fuer Seite 89.1 (KS.01.03)
*                       eingefuegt.
*                       XAWGENMOD bis XAWIKZGAIN fuer Seite 89.2 (KS.01.03)
*                       eingefuegt.
*     13-09-96 -PR-        ISCOS-Registernummern fuer die
*                                                     frei progr.baren Kernzuege eingefuegt.
*     05.11.96 -HAns-   Neue Sonderregister XIQSON30 -XIQSON68 eingefuegt.
*     06.11.96 -HAns-   XRFAST10 in XRFAST1 umbenannt.
*                       XAX6D in XRFAST2 umbenannt.
*     19.11.96 -HAns-   XSRSSVOR_3 - XSRSVNACH_4 eingefuegt.
*     27.11.96 -HAns-   XPL1GENMOD - XPLIKGEST4 eingefuegt.
*     28.11.96 -HAns-   XSDRGENMOD - XSDRITDAUFB eingefuegt.
*     04.12.96 -HAns-   Folgende IST-Wert defines herausgenommen, da diese
*                       nicht benutzt werden :
*                       XXSVH10 - XXSVH15, XXSVOL1,
*                       XXSVH20 - XXSVH25, XXSVOL2,
*                       XXSVH30 - XXSVH35, XXSVOL3,
*                       XXSVH40 - XXSVH45, XXSVOL4,
*                       Folgende SOLL-Wert defines herausgenommen, da diese
*                       nicht benutzt werden :
*                       XSSVH10 - XSSVH15, XSSVH20 - XSSVH25,
*                       XSSVH30 - XSSVH35, XSSVH40 - XSSVH45,
*     18.12.96 -HAns-   XDOSNCARD und XDOI_AKT eingefuegt.
*     27.12.96 -HAns-   XDISNCARD und XDII_AKT eingefuegt.
*                       XAOSNCARD bis XAIINAKT16 eingefuegt.
*     09.01.96 -TSchw-  Sonderprogrammregister GIL_XSON und GIL_SSON 
*                       eingefuegt
*     13.01.97 -HAns-   XAWGWEG, XSNGDREHM1 - XSNGDREHM4 eingefuegt.
*     17.01.97 -HAns-   XLVSTVERZ10 - XLVSTBLAS40 eingefuegt.
*     13.02.97 -HAns-   XSPIPHYDMAX eingefuegt.
*     04.03.97 -HAns-   XFPKZANDFHK eingefuegt.
*     17.03.97 -HAns-   XSLSNSCHM eingefuegt.
*     02.06.97 -HAns-   XRFAST11 bis XRFAST13 herausgenommen und 
*                       XRINJ9 - XRINJ15 eingefuegt.
*     03.06.97 -HAns-   Vereinigung von ELEKTRAV1 und common.
*                       XLVSTVERZ50 und XLVSTBLAS50 eingefuegt.
*                       XSNBLAS5 bis XSTABLA5 eingefuegt.
*                       XSSFZU4 bis IQCLMAXSTRK eingefuegt.
*                       XQDM_BUGFIX eingefuegt.
*     04.06.97 -HAns-   XPG_SCDIA eingefuegt.
*     05.06.97 -HAns-   XPLGWEG1-4 eingefuegt.
*     19.06.97 -HAns-   XSNG_UMDR1-4 eingefuegt.
*                       XSLSNSCHM von 5244 nach 5290 verlegt, da 5244 schon
*                       vorhanden.
*     24.06.97 -GhG-    Maschinenfaehigkeit aus dem Sonderprogramm g15b.3
*                       in Standard uebernommen. Register eingefuegt:
*                       XWOISAKTUEL    3498   <- fuer Werkzeugoeffnungsweite
*                       XAWISAKTUEL    3499   <- fuer Auswerferweg 
*                       XKOMMASCHF     3500   <- als Kommunikations"bit" zur SPS, 
*                                                1 wenn Werte Gueltig
*                                                0 wenn Werte nicht Gueltig
*     08.07.97 -HAns-   XPLSVMESS bis XPLIDOBEN eingefuegt.
*     22.07.97 -HAns-   XRFAST10 bis XRFAST16 eingefuegt.
*     20.10.97 -HAns-   XSPSCPUTYPE eingefuegt.
*               29.10.97        -PR-     Kernzug-Programmnummer IKEPRGNO eingefuegt.
*               06.11.97 -PR-     IKE_NRSCHRAUB, IKE_NRWEND, IKE_SPERRMASKE eingefuegt.
*     25.11.97 -HAns-   XDIAGMAXMOD - XDIAGMODTYP, XFDIAGDAKT bis XFDIAGA_F16
*                       aufgenommen.
*     30.11.97 -HAns-   Folgende Register wurden neu eingefuegt:
*                       XAKT_DVAL1 - 10, XFOR_DVAL1 - 10, XAKT1AVAL01 - 16,
*                       XFOR1AVAL01 - 16, XAKT2AVAL01 - 16, XFOR2AVAL01 - 16,
*                       XAKT3AVAL01 - 16 und XFOR3AVAL01 - 16,
*     01.12.97 -HAns-   XDOSNCARD bis XAIINAKT16 herausgenommen, da nie benutzt
*                       und durch die neue freiauswaehlbare Diagnoseseite ersetzt
*                       wird.
*     02.12.97 -HAns-   XSPSWEGMTYP (WegMess-Type) aufgenommen.
*     05.12.97 -GhG-    Neue Register fuer 6. Blasluft  Seite 69.0
*                       XSNBLAS6, XSSBLAS6, XLVSTVERZ60, XLVSTBLAS60    
*     05.12.97 -HAns-   XDIAGMODTYP in XDIAGINDTAB umbenannt.
*     26.01.98 -HAns-   XOPM_SPSTXT aufgenommen.                                      
*     06.02.98 -HAns-   B/W-Register fuer Mehrfarbmaschinen aufgenommnen.
*                       (XXNSTEP2 bis XXNPAS4)
*     10.02.98 -HAns-   IFORCEOUTPUT9,36 und 39 aufgenommen.
*     23.03.98 -HAns-   XWZIFSICHT, XSLIPSDRMAX, XSPIP1AKTUE und XSPIP2AKTUE
*                       eingefuegt.
*     30.04.98 -GhG-    XZSMNSCHMIER --- Einfahrschmierintervall Istwert
*                       eingefuegt.
*     08.06.98 -HAns-   Register fuer 9 Einspritzstufen (XSPPH17 bis XXSPH19)
*                       eingefuegt.
*     26.06.98 -HAns-   XSPIKKRAFT2 eingefuegt
*     07.07.98 -GhG-    XMSKSSNDUR2 eingefuegt
*     22.09.98 -GhG-    Register fuer Rampenzeiten S. 48  XRAMPE1_D1 - XRAMPE5_D4
*                       eingefuegt
*     25.11.98 -HAns-   XWDM_BETART bis XWZAVZUR aufgenommen.
*     18.01.99 -HAns-   XAKT_DVAL11 bis XFOR8AVAL01 aufgenommen.
*     09.02.99 -HAns-   XIQTMIUNIT, XLVSNEIN31 bis XLVSTBLAS43 aufgenommen.
*     30.03.99 -GhG-    Register fuer Elektra 300 eingefuehrt
*                       MSSPINZ        6177  Ist  Zyklen seit letzter Schmierung S15 z2 
*                       MSSPINAN       6178  Soll Anzahl geschmierter Nippel S15 z3
*                       MSGELEZ        6179  Ist  Zyklen seit letzter Schmierung S15 z6 
*                       MSGELEAN       6180  Soll Anzahl geschmierter Nippel S15 z7   
*                       DUABHEBZ       6181  Soll Duesenabhebezeit S49 z10
*                       AWKRAFTE       6182  Soll Auswerferkraft S52 z19              
*     09.08.99 -HAns-   XWFMPRANGE1,2,3,4 und XWFM_ASWPT1,2,3,4 aufgenommen.
*     17.08.99 -HAns-   XSBS_BETR bis XSBITUBERW aufgenommen.
*     17.01.00 -HAns-   XMAI_OFFS1 bis XMAS_VERS2 aufgenommen.
*     02.02.00 -HAns-   Register fuer 5/6-Farbmaschine aufgenommen.
*     17.02.00 -HAns-   XIQTSSACT aufgenommen.
*     10.03.00 -HAns-   XDRGPUEBERS aufgenommen.
*     15.03.00 -HAns-   XSESSVOR1 bis XSEISNLPKT6 aufgenommen.
*     21.03.00 -HAns-   XPG_IST_WORK05 bis XPG_TOL_WORK06 aufgenommen.
*     18.05.00 -HAns-   XMAI_OFFS11 bis XMAI_VERS12 aufgenommen.
*     30.05.00 -HAns-   XWSSKOFF2 bis XWOIKOFF2 aufgenommen.
*                       XAWSN1ZUR aufgenommen
*     04.07.00 -GhG-    XWKZDUES_D1 bis XWKZDUES_D4 WKZ Duese schliessen fuer Airprass S. 48
*     10.08.00 -HAns-   XAWSPZUR aufgenommen.
*                       SZINSUB  subtrahierender Schusszaehler eingefuegt
*                       IOSDIFKT1 bis FBST eingefuegt.
*     02.10.00 -HAns-   XCARD_INFO eingefuegt.
*     09.10.00 -HAns-   XSESVRAMPE11 - 59 und XSESPRAMPE11 - 59 eingefuegt.
*     20.10.00 -HAns-   XXKOEL2 eingefuegt.
*     08.12.00 -HAns-   Register fuer 2.Heizungs-SPS eingefuegt (XHZ2....).
*                       XHES2BLOPT und XHES2BLOPT2 eingefuegt.
*     12.12.00 -HAns-   XHZ2CURREG bis XHZ2TABSWKZ eingefuegt.
*                       XHZ_MSTOSL bis XHZ2SLTOMS eingefuegt.
*     09.02.01 -GhG-    XSSAUS4, XSVAZUR2, XSFAUSF2 und  XAWSPZUR2 eingefuegt
*     13.02.01 -GhG-    IKBA0INPUT - IKBA3INPUT SPS-Tasten eingefuegt
*                       XSSFZU5, XSPNIDR2, XSTNIDR2,  XXTNIDR2  eingefuegt 
*     13.03.01 -GhG-    XXSN_ANFA, XSSDOS1A, XSPPH11A, XSVPH11A - XSVPH13A , XSTPH11A,
*                       XSSPH11A -  XSSPH19A, XSPPH12A, XSTPH12A,
*                       XSPPH13A, XSTPH13A, XXSN_ANF2A, XSPNIDRA,
*                       XSPNIDR2A  fuer Produktionsstart S. 40.2 eingefuegt
*     28.03.01 -GhG-    XHZITMESS1 - XHZITMESS4, XHXSNIF, XHXSNPROTO, XHXSNBAUD,XHXSNDATBIT, XHXSNSTPBIT,
*                       XHXSNPARITY, XHZSNREGNR1 - XHZSNREGNR4, XHZSNWAHL1 - XHZSNWAHL4
*                       eingefuegt.
*     30.08.01 -HA-     XSDIAGDAKT bis XSDIAGA_F16 eingefuegt.
*     01.10.01 -HA-     XMSSSK2_1 bis XMSISAKT8 eingefuegt.
*     05.10.01 -HA-     XSSUM12-42, XSSUM13-43, XSWPL13-43, XSWPL14-44, XSPST13-43 und XSPST14-44 eingefuegt.
*     10.10.01 -HA-     XAGGPDUESE1, XWSISHOEHE, XWZSSSKOLB und XWZISSKOLB eingefuegt.
*     12.10.01 -HA-     XPLS_ANZPL1 bis 5 eingefuegt.
*     25.10.01 -HA-     XIOI_DINP und XIOI_DOUT eingefuegt.
*     29.10.01 -HA-     XSPPH1A bis XXSPH1C eingefuegt.
*     31.10.01 -HA-     XSESVRAMPE1A - 5C und XSESPRAMPE1A - 5C eingefuegt.
*     20.11.01 -HA-     XVENTYPAUSW bis XMAI_VERS2 eingefuegt.
*                       XMAVENRDIND eingefuegt
*     26.11.01 -HA-     XSLSNHOLMNT und XSLINHOLMHT eingefuegt.
*     03.12.01 -HA-     XLVSNEIN4-7, XLVSSWEGP5-8, XLVSTVERZ70-80 und XLVSTBLAS70-80 eingefuegt.
*     05.12.01 -HA-     XWZGMAXPLAT eingefuegt.
*     17.12.01 -HA-     XWS_KLEMIT eingefuegt.
*     18.12.01 -HA-     XSLSS1NUT, XSLIS1NUT, XSLISNUTDIF, XSLSNMAXNUT, XSLSNDEFNUT, XSLINSDRMOD eingefuegt
*                       XSLSNPARKNT und XSLSNSDRMOD eingefuegt 
*     08.02.02 -HA-     XSPIF1ANPR und XSPIF2ANPR eingefuegt
*     27.02.02 -JG-     XZHS_WASSER eingefuegt                   
*     28.02.02 -HA-     XSESTUEBER, XSEIPUWMAX, XSESPUWMAX und XSESNBEGRFK eingefuegt.
*     18.03.02 -HA-     XDRVERROR_CODE und XDRVERROR_ID eingefuegt.
*     19.03.02 -JG-     XNSNPROTO_2,XSNIF_2,XSNBAUD_2,XSNSTPBIT_2,XSNDATBIT_2,
                        XSNECHO_2 für Seite 39.9 eingefügt
*     25.03.02 -HA-     XMSSSOFF11,21,31, XMSIOFF11,12,21,22,31,32, XMSSNPNR und XMSINSTA, XMSINMLD eingefuegt
*     02.04.02 -HA-     IOSNDOPA21 bis IOSNDOPA24 eingefuegt.
*                       IOSNDIPAR1 bis IOSNDIPAR4 eingefuegt.
*     08.04.02 -HA-     IOINDIIST, IOINDOIST eingefuegt.
*     17.04.02 -HA-     ITEXT6 und ITEXT7 eingefuegt.
*                       XWKZSS_VERS und XWKZIS_VERS eingefuegt.
*     13.05.02 -HA-     XSLITKLEMZU und XSLITKLEMAU eingefuegt.
*     14.05.02 -JG-     GILLETTE-Sonderregister GIL_SSON120 bis
*                       GIL_SSON181 eingefuegt 
*     15.05.02 -HA-     XHZIT_VERZ1 bis XHZIT_VERZ6 eingefuegt.
*     16.05.02 -HA-     XXTKUHL eingefuegt
*     12.06.02 -HA-     XAPD_TYPE, XAPD_MODE, XAPSPSYST und XAPIPSYST eingefuegt.
*                       XAPITUEB1 bis XAPITUEB4 eingefuegt.
*     13.06.02 -HA-     XOPS_NEUST, XOPSNKARTON un XOPINKARTON eingefuegt.
*     02.10.02 -HA-     XWZA_BA_FHK bis XWZAVZUR2 eingefuegt.
*     29.10.02 -HA-     XMSKSSNDUR3-6 eingefuegt
*     20.11.02 -HA-     XHXINPAGEAW eingefuegt.
*     03.02.02 -HA-     XSTKUHL2 eingefuegt.
*     12.03.03 -HA-     XDTS_NUM und XDTI_NUM eingefuegt.
*     03.06.03 -HA-     XDIAGM170 bis XDIAGM18F und XTEXT_DRVMODUL11 bis XTEXT_DRVSERIEN_NR22 eingefuegt.
*     26.06.03 -HA-     XSEIPDANPR1 bis 6 eingefuegt.
*     23.07.03 -HA-     Register fuer 12 Einspritzstufen (XSPPH27 bis XXSPH2C) eingefuegt.
*     24.07.03 -HA-     XSSDOS2A bis XSSPH29A eingefuegt.
*     13.08.03 -HA-     XSESVVOR21 bis XSESVVOR26 eingefuegt.
*     20.08.03 -HA-     XMSKSSEWEG1 bis XMSKSSEWEG6 eingefuegt.
*     03.09.03 -HA-     XMSSSOFF51 bis XMSISOFF62 eingefuegt.
*
****************************************************************************/
                        
#ifndef _iscosreg       
#define _iscosreg

/* ------------------------------------------------------------------------- *
 |  Definitons fur die Registernummern der ISCOS-Register                    |
 |  ISCOS-Registernummern bewegen sich im Bereich zwischen  3000 und 14999   |
 |  ISCOS-Registernummern bewegen sich im Bereich zwischen 19000 und 19999   |
 * ------------------------------------------------------------------------- */

#define XXSWEG1        3000
#define XXSWEG2        3001
#define XXTDOS1        3002
#define XXWDRE1        3003
#define XXNAD2M        3004
#define XXNAD2L        3005
#define XXNKERN        3006
#define XXTZYKL        3007
#define XXNSTEP        3008
#define XXNPASE        3009
#define XXFZUHK        3010
#define XXSNSP1        3011
#define XXSNSP2        3012
#define XXKOEL         3013
#define XXSON4E        3014
#define XXKPERR        3015
#define XXNMACO        3016
#define XXNWECO        3017
#define XXNCAR1        3018
#define XXNCAR2        3019
#define XKBNAUF        3020
#define XKBNZU         3021
#define XXSWEG3        3022
#define XXSWEG4        3023
#define XXNAHUB        3024
#define XXTNIDR        3025
#define XXNFSS         3026
#define XZNGUTT        3027
#define XXNSEXT        3028
#define XXTDOS2        3029
#define XXWDRE2        3030
#define XXNPAS2        3031
#define XXREG          3032
#define XAX60          3033
#define XAX61          3034
#define XAX62          3035
#define IWZISACTPOS    3036
#define IQTINSPSTXT    3037
/* ---------------- Schnelle Istwert-Register zu Reserve ------------------ */
#define XRFAST3        3038
#define XRFAST4        3039
#define XRFAST5        3040
#define XRFAST6        3041
#define XRFAST7        3042
#define XRFAST8        3043
#define XRFAST9        3044
#define XRFAST1        3045
#define XRFAST2        3046
/* ------------------------------------------------------------------------ */
#define XIDIA1         3047
#define XIDIA2         3048
#define XIDIA3         3049
#define XIDIA4         3050
#define XIDIA5         3051
#define XIDIA6         3052
#define XIDIA7         3053
#define XIDIA8         3054
#define XIDIA9         3055
#define XIDIA10        3056
#define XIDIA11        3057
#define XIDIA12        3058
#define XIDIA13        3059
#define XIDIA14        3060
#define XIDIA15        3061
#define XIDIA16        3062
#define XIDIA17        3063
#define XIDIA18        3064
#define XIDIA19        3065
#define XIDIA20        3066
#define XIDIA21        3067
#define XIDIA22        3068
#define XIDIA23        3069
#define XIDIA24        3070
#define XXPFINM        3071
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XXSPH10        3072
#define XXSPH11        3073
#define XXSPH12        3074
#define XXSPH13        3075
#define XXSPH14        3076
#define XXSPH15        3077
#define XXSPOL1        3078
#define XXSPH20        3079
#define XXSPH21        3080
#define XXSPH22        3081
#define XXSPH23        3082
#define XXSPH24        3083
#define XXSPH25        3084
#define XXSPOL2        3085
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XXTPH11        3086
#define XXTPH12        3087
#define XXTPH13        3088
#define XXTPH14        3089
#define XXTPH15        3090
#define XXTPH16        3091
#define XXTPH21        3092
#define XXTPH22        3093
#define XXTPH23        3094
#define XXTPH24        3095
#define XXTPH25        3096
#define XXTPH26        3097
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XXPPH11        3098
#define XXPPH12        3099
#define XXPPH13        3100
#define XXPPH14        3101
#define XXPPH15        3102
#define XXPPH16        3103
#define XXPPH21        3104
#define XXPPH22        3105
#define XXPPH23        3106
#define XXPPH24        3107
#define XXPPH25        3108
#define XXPPH26        3109
/* ------------------------------------------------------------------------ */
#define XXPFI2M        3110
#define XAX0AE         3111
#define XAX0AF         3112
#define XAX0B0         3113
#define XAX0B1         3114
#define XAX0B2         3115
#define XXNTRK         3116
#define XPNTRK         3117
#define XPNREGL        3118
#define XPNMCWP        3119
#define XPNMCWB        3120
#define XPNTN          3121
#define XPNTV          3122
#define XPNXPK         3123
#define XPNXPH         3124
#define XXTD101        3125
#define XXTD102        3126
#define XXTU101        3127
#define XXTU102        3128
/* ------------------------------------------------------------------------ */
#define XSESVVOR21     3129
#define XSESVVOR22     3130
#define XSESVVOR23     3131
#define XSESVVOR24     3132
#define XSESVVOR25     3133
#define XSESVVOR26     3134
/* ------------------------------------------------------------------------ */
#define XMSKSSEWEG1    3135
#define XMSKSSEWEG2    3136
#define XMSKSSEWEG3    3137
#define XMSKSSEWEG4    3138
#define XMSKSSEWEG5    3139
#define XMSKSSEWEG6    3140

#define XZKTST1        3153
#define XZKTST2        3154
#define XZKTST3        3155
#define XZKTST4        3156
#define XZKTST5        3157
#define XZKTST6        3158
#define XXKADRG        3159
#define XZKTST8        3160
#define XSREG          3161
#define XSKADRG        3162
#define XAX0E1         3163
#define XAX0E2         3164
#define XAX0E3         3165
#define XAX0E4         3166
#define XAX0E5         3167
#define XAX0E6         3168
#define XAX0E7         3169
#define XAX0E8         3170
#define XAX0E9         3171
#define XAX0EA         3172
#define XAX0EB         3173
#define XAX0EC         3174
#define XAX0ED         3175
#define XAX0EE         3176
#define XAX0EF         3177
#define XSSFZU1        3178
#define XSSFZ11        3179
#define XSSFZU2        3180
#define XSSFZU3        3181
#define XSFZKPT        3182
#define XSFZSO1        3183
#define XSFZSO2        3184
#define XSFZS16        3185
#define XSFZSTP        3186
#define XSFZKP2        3187
#define XSSFZU         3188
#define XSSFAU1        3189
#define XSSFAU2        3190
#define XSSFA11        3191
#define XSSFA12        3192
#define XSSFAU3        3193
#define XSSFAU4        3194
#define XSSFAU5        3195
#define XSSFAU6        3196
#define XSSFAU7        3197
#define XSSFAU8        3198
#define XSSFAU9        3199
#define XSFAKPT        3200
#define XSFASO1        3201
#define XSFASO2        3202
#define XSFASTP        3203
#define XSFAKP2        3204
#define XSSFAUF        3205
#define XSSAUS0        3206
#define XSSAUS1        3207
#define XSSAUS2        3208
#define XSAUKPV        3209
#define XSSAUS3        3210
#define XSSAUSR        3211
#define XSAUKPT        3212
#define XSVZU1         3213
#define XSVZU2         3214
#define XSVNIDR        3215
#define XSVAUF1        3216
#define XSVAUF2        3217
#define XSVAUF3        3218
#define XSVAUS1        3219
#define XSVAUS2        3220
#define XSVAZUR        3221
#define XSPFAHR        3222
#define XSPNIDR        3223
#define XSFZUHK        3224
#define XSPEINR        3225
#define XSPZUHK        3226
#define XSPZUMX        3227
#define XSTOPAU        3228
#define XSTOPZU        3229
#define XSPZMIN        3230
#define XSPSPR         3231
#define XSPSTH1        3232
#define XSPSTH2        3233
#define XSFSSED        3234
#define XAX129         3235
#define XSPRAG1        3236
#define XSTUFA1        3237
#define XSPRAG2        3238
#define XSTUFA2        3239
#define XINDEXT        3240
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XSTPH11        3241
#define XSTPH12        3242
#define XSTPH13        3243
#define XSTPH14        3244
#define XSTPH15        3245
#define XSTPH16        3246
#define XSTPH21        3247
#define XSTPH22        3248
#define XSTPH23        3249
#define XSTPH24        3250
#define XSTPH25        3251
#define XSTPH26        3252
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XSSPH10        3253
#define XSSPH11        3254
#define XSSPH12        3255
#define XSSPH13        3256
#define XSSPH14        3257
#define XSSPH15        3258
#define XSSPOL1        3259
#define XSSPH20        3260
#define XSSPH21        3261
#define XSSPH22        3262
#define XSSPH23        3263
#define XSSPH24        3264
#define XSSPH25        3265
#define XSSPOL2        3266
/* ------------------------------------------------------------------------ */
#define XSVUMD1        3267
#define XSSOND1        3268
#define XSVUMS1        3269
#define XSDOND1        3270
#define XSSUM11        3271
#define XSSDOS1        3272
#define XSSRUK1        3273
#define XSWPL11        3274
#define XSWPL12        3275
#define XSPST11        3276
#define XSPST12        3277
#define XSSWPUV        3278
#define XSSX2          3279
#define XSS1DOS        3280
#define XKXEMPF        3281
#define XSVRUK1        3282
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XSVPH11        3283
#define XSVPH12        3284
#define XSVPH13        3285
#define XSVPH14        3286
#define XSVPH15        3287
#define XSVPH16        3288
#define XSVPH21        3289
#define XSVPH22        3290
#define XSVPH23        3291
#define XSVPH24        3292
#define XSVPH25        3293
#define XSVPH26        3294
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XSPUM11        3295
#define XSPUM12        3296
#define XSPUM13        3297
#define XSPUM14        3298
#define XSPUM15        3299
#define XSPUMDD        3300
#define XSPUM21        3301
#define XSPUM22        3302
#define XSPUM23        3303
#define XSPUM24        3304
#define XSPUM25        3305
/* ---------------- indizierte Register Reihenfolge einhalten ------------- */
#define XSPPH11        3306
#define XSPPH12        3307
#define XSPPH13        3308
#define XSPPH14        3309
#define XSPPH15        3310
#define XSPPH16        3311
#define XSPPH21        3312
#define XSPPH22        3313
#define XSPPH23        3314
#define XSPPH24        3315
#define XSPPH25        3316
#define XSPPH26        3317
/* ------------------------------------------------------------------------- */
#define XSSPRPR        3318
#define XSXSTUF        3319
#define XSSVODO        3320
#define IWAS_FKT       3321
#define IWAS_WPVOR     3322
#define IWAS_HUBZ      3323
#define IWASTVORNE     3324
#define IWASTVOR       3325
#define IWASTZUR       3326
#define IKE_PAUSFA     3327
#define IKE_PEINFA0    3328
#define IKE_VAUSFA0    3329
#define IKE_VAUSFA1    3330
#define IKE_VEINFA0    3331
#define ILVSNEIN0      3332
#define ILVSNEIN1      3333
#define ILVSNEIN2      3334
#define ILVSNEIN3      3335
#define XRSONF         3336
#define XSSENTN        3337
#define XSK1EIN        3338
#define XSK1AUS        3339
#define XSK2EIN        3340
#define XSK2AUS        3341
#define XSK1EIV        3342
#define XSK1AUV        3343
#define XSK2EIV        3344
#define XSK2AUV        3345
#define XSNK1EI        3346
#define XSNK1AU        3347
#define XSNK2EI        3348
#define XSNK2AU        3349
#define XSTZYKL        3350
#define XSTDOS1        3351
#define XSTMOTA        3352
#define XSTWASA        3353
#define XSTVDOS        3354
#define XSTINTR        3355
#define XSTKUHL        3356
#define XSTAGGR        3357
#define XSTNIDR        3358
#define XSTPAUS        3359
#define XSTAUS1        3360
#define XSTAUS2        3361
#define XSTV1V         3362
#define XSTV1B         3363
#define XSTV2V         3364
#define XSTV2B         3365
#define XSTV3V         3366
#define XSTV3B         3367
#define XSTV4V         3368
#define XSTV4B         3369
#define XSTK1EI        3370
#define XSTK1AU        3371
#define XSTK2EI        3372
#define XSTK2AU        3373
#define XSOELVW        3374
#define XSNFIN         3375
#define XSNFETZ        3376
#define XSNKERN        3377
#define XSNSUSM        3378
#define XSNSUSL        3379
#define XSNSEXT        3380
#define XSNRUEK        3381
#define XSNPHMX        3382
#define XSFAGGR        3383
#define XSNAGGR        3384
#define XSNNIDR        3385
#define XSFAUSF        3386
#define XSNAUSW        3387
#define XSON1B6        3388
#define XSNRUK2        3389
#define XSNPHM2        3390
#define XSFAGG2        3391
#define XSNAGG2        3392
#define XSNKEIN        3393
#define XSNKAUS        3394
#define XSNVWS1        3395
#define XSNVWS2        3396
#define XSNVWS3        3397
#define XSNVWS4        3398
#define XSNVWS5        3399
#define XSSWP1         3400
#define XSSWP2         3401
#define XSSWP3         3402
#define XSSWP4         3403
#define XSSWP5         3404
#define XSTZ1          3405
#define XSTZ2          3406
#define XSTZ3          3407
#define XSTZ4          3408
#define XSTZ5          3409
#define XSNGRAF        3410
#define XSTDUES1       3411
#define XAX1CE         3412
#define XSVAG1V        3413
#define XSVAG1Z        3414
#define XSF80AG1       3415
#define XSAGPFO        3416
#define XAX1D3         3417
#define XAX1D4         3418
#define XZISSST        3419
#define XKNITV1        3420
#define XKNITV3        3421
#define XSTKULM        3422
#define XSVK1EI        3423
#define XSPK1EI        3424
#define XSVK1AU        3425
#define XSPK1AU        3426
#define XSVK2EI        3427
#define XSPK2EI        3428
#define XSVK2AU        3429
#define XSPK2AU        3430
#define XSTVFOA        3431
#define XSTVSRA        3432
#define XSTASRA        3433
#define XSTVASW        3434
#define XSSSRAU        3435
#define XSVSRE         3436
#define XSPSRE         3437
#define XSPNSRE        3438
#define XSVSRA         3439
#define XSPSRA         3440
#define XSPNSRA        3441
#define XZIMUEM        3442
#define XZIMUEL        3443
#define XAX1EE         3444
#define XAX1EF         3445
#define XKNUVER        3446
#define XKNUTYP        3447
#define XSLAENG        3448
#define XTPWEG1        3449
#define XTPPUV1        3450
#define XTPVK1         3451
#define XTPTRK1        3452
#define XTPPUV2        3453
#define XTPTRK2        3454
#define XINDEXR        3455
#define XRALT          3456
#define XXDMA          3457
#define XZXZAEL        3458
#define XAX1FC         3459
#define XAX1FD         3460
#define XAX1FE         3461
#define XAX1FF         3462
#define XAX200         3463
#define XSVUMD2        3464
#define XSSOND2        3465
#define XSVUMS2        3466
#define XSSUM21        3467
#define XSSDOS2        3468
#define XSSRUK2        3469
#define XSWPL21        3470
#define XSWPL22        3471
#define XSPST21        3472
#define XSPST22        3473
#define XSSWPV2        3474
#define XSSX22         3475
#define XKXEMP2        3476
#define XSVRUK2        3477
#define XSTDOS2        3478
#define XSTVDO2        3479
#define XSTINT2        3480
#define XKNITV2        3481
#define XKNITV4        3482
#define XSTAGG2        3483
#define XSNFIN2        3484
#define XSTDUES2       3485
#define XSVAG2V        3486
#define XSVAG2Z        3487
#define XSF80AG2       3488
#define XSAG2PFO       3489
#define XAX239         3490
#define XAX23A         3491
#define XAX23B         3492
#define XAX23C         3493
#define XAX23D         3494
#define XAX23E         3495
#define XAX23F         3496
/* ---------------- Heizungsregister Reglerparameterblock ----------------- */
#define XSNTRK         3497
/* ---------------- fuer Maschinenfaehigkeit ------------------------------ */
#define XWOISAKTUEL    3498
#define XAWISAKTUEL    3499
#define XKOMMASCHF     3500
/* ---------------- CPU-Type der SPS -------------------------------------- */
#define XSPSCPUTYPE    3501
/* ---------------- WegMess-Type der SPS ---------------------------------- */
#define XSPSWEGMTYP    3502
/* ---------------- 2.Oelregler ------------------------------------------- */
#define XXKOEL2        3503
/* ---------------- Ventil-Auswahlregister S.89.1 ------------------------- */
#define XVENTYPAUSW    3504
#define XVENTYPOFFS    3505
#define XMAVENRDIND    3506
/* ---------------- Diagnoseseite: Endschalter Klemmschalen Seite 50.1 ---- */
#define XSLSNHOLMNT    3507
#define XSLINHOLMNT    3508
/* ---------------- Max. Werkzeug-Plattenabstand -------------------------- */
#define XWZGMAXPLAT    3509
/* ---------------- Maschinen-Abgleich: Plastifizieren (KDE) -------------- */
#define XPLSVMESS      3510
#define XPLIVAMESS     3511
#define XPLIVDMESS     3512
#define XPLSVOBEN      3513
#define XPLIVAOBEN     3514
#define XPLIVDOBEN     3515
/* ---------------- END Maschinen-Abgleich: Plastifizieren (KDE) ---------- */
#define XAX253         3516
#define XXQUITRN       3517
#define XXSTOP         3518
#define XXSW2          3519
#define XAX257         3520
#define XAX258         3521
#define XAX259         3522
#define XAX25A         3523
#define XAX25B         3524
#define XAX25C         3525
#define XSNOPT         3526
#define XSMCWOP        3527
#define XSNCW2         3528
/* ---------------- Zeit fuer Verriegeln der Klemmschalen Seite 17.1 ------ */
#define XWS_KLEMIT     3529
/* ---------------- Spritzdruckueberwachung ------------------------------- */
#define XSESTUEBER     3530
#define XSEIPUWMAX     3531
#define XSESPUWMAX     3532
#define XSESNBEGRFK    3533
#define XSLITKLEMZU    3534
#define XSLITKLEMAU    3535
/* ---------------- nachtraglich definierte Kernzug-Register -------------- */
#define XHXINPAGEAW    3536
/* ---------------- nachtraglich definierte Kernzug-Register -------------- */
#define XSSORT1        3537
#define XSSORT2        3538
#define XSSORT3        3539
#define XSSORT4        3540
#define XSSORT5        3541
#define XSSORT6        3542
#define XSSORT7        3543
#define XSSORT8        3544
/* ---------------- Airpress ---------------------------------------------- */
#define XAPITUEB1      3545
#define XAPITUEB2      3546
#define XAPITUEB3      3547
#define XAPITUEB4      3548
#define XSTKUHL2       3549
/* ---------------- Register fuer Seite 50.1 ------------------------------ */
#define XSLSS1NUT      3550
#define XSLIS1NUT      3551
#define XSLISNUTDIF    3552
#define XSLSNMAXNUT    3553
#define XSLSNDEFNUT    3554
#define XSLSNPARKNT    3555
#define XSLSNSDRMOD    3556
#define XSLINSDRMOD    3557
#define XSPIF1ANPR     3558
#define XSPIF2ANPR     3559
#define XZHS_WASSER    3560
/* ------------------------------------------------------------------------ */
#define XMSSSOFF51     3561
#define XMSSSOFF61     3562
#define XMSISOFF51     3563
#define XMSISOFF52     3564
#define XMSISOFF61     3565
#define XMSISOFF62     3566

#define XSNBLAS5       3570
#define XSSBLAS5       3571
#define XSTVBLA5       3572
#define XSTABLA5       3573
#define XSESSVERD1     3574    /* von El-Ver. 01.06.0 (SSVDU1 u. SSVDU2) */
#define XSESSVERD2     3575    /* uebernommen */
#define XMSKSSNDUR1    3576    /* aktueller Schneckendurchmesser AGG. 1 */
#define XQDM_BUGFIX    3577    /* neu ab EL.01.06.0 */  
#define XSNBLAS6       3578
#define XSSBLAS6       3579
#define XMSKSSNDUR2    3580    /* aktueller Schneckendurchmesser AGG. 2*/
#define XMSKSSNDUR3    3581    /* aktueller Schneckendurchmesser AGG. 3*/
#define XMSKSSNDUR4    3582    /* aktueller Schneckendurchmesser AGG. 4*/
#define XMSKSSNDUR5    3583    /* aktueller Schneckendurchmesser AGG. 5*/
#define XMSKSSNDUR6    3584    /* aktueller Schneckendurchmesser AGG. 6*/

/* ---------------- nachtraglich definierte Register ---------------------- */
#define XXSWEG4_SHOW   3590
/* ---------------- Aggregat-Register fuer die Steuerung ------------------ */
#define XDHVWALR       3591
/* ---------------- Drive-Error Register ---------------------------------- */
#define XDRVERROR_CODE 3592    /* Error-Code                                */
#define XDRVERROR_ID   3593    /* Drive-ID                                  */
/* ------------------------------------------------------------------------ */
#define XSEIPDANPR1    3594 /* Spritzeinheit 1 Anpressdruck Seite 49.0      */
#define XSEIPDANPR2    3595 /* Spritzeinheit 1 Anpressdruck Seite 49.0      */
#define XSEIPDANPR3    3596 /* Spritzeinheit 1 Anpressdruck Seite 49.0      */
#define XSEIPDANPR4    3597 /* Spritzeinheit 1 Anpressdruck Seite 49.0      */
#define XSEIPDANPR5    3598 /* Spritzeinheit 1 Anpressdruck Seite 49.0      */
#define XSEIPDANPR6    3599 /* Spritzeinheit 1 Anpressdruck Seite 49.0      */
/* ---------------- Zusaetzliche Reserveregister -------------------------- */
#define XKEINSI        3600
#define XAX269         3601
#define XAX26A         3602
#define XAX26B         3603
#define XAX26C         3604
#define XAX26D         3605
#define XAX26E         3606
#define XAX26F         3607
#define XIQSON0        3608
#define XIQSON1        3609
#define XIQSON2        3610
#define XIQSON3        3611
#define XIQSON4        3612
#define XIQSON5        3613
#define XIQSON6        3614
#define XIQSON7        3615
#define XIQSON8        3616
#define XIQSON9        3617
#define XIQSONA        3618
#define XIQSONB        3619
#define XIQSONC        3620
#define XIQSOND        3621
#define XIQSONE        3622
#define XIQSONF        3623
/* ---------------- 32 Reserveregister exclusiv fuer Sonderprogramme ------ */
#define XIQSON10       3624
#define XIQSON11       3625
#define XIQSON12       3626
#define XIQSON13       3627
#define XIQSON14       3628
#define XIQSON15       3629
#define XIQSON16       3630
#define XIQSON17       3631
#define XIQSON18       3632
#define XIQSON19       3633
#define XIQSON1A       3634
#define XIQSON1B       3635
#define XIQSON1C       3636
#define XIQSON1D       3637
#define XIQSON1E       3638
#define XIQSON1F       3639
#define XIQSON20       3640
#define XIQSON21       3641
#define XIQSON22       3642
#define XIQSON23       3643
#define XIQSON24       3644
#define XIQSON25       3645
#define XIQSON26       3646
#define XIQSON27       3647
#define XIQSON28       3648
#define XIQSON29       3649
#define XIQSON2A       3650
#define XIQSON2B       3651
#define XIQSON2C       3652
#define XIQSON2D       3653
#define XIQSON2E       3654
#define XIQSON2F       3655
/* ---------------- Reserve - Register  mit TP_RD_INJ --------------------- */
#define XRINJ1         3656       
#define XRINJ2         3657
#define XRINJ3         3658 
#define XRINJ4         3659
#define XRINJ5         3660
#define XRINJ6         3661 
#define XRINJ7         3662
#define XRINJ8         3663
#define XRINJ9         3664
#define XRINJ10        3665
#define XRINJ11        3666
#define XRINJ12        3667
#define XRINJ13        3668
#define XRINJ14        3669
#define XRINJ15        3670
/* ---------------- 300 Register fuer die Diagnoseseiten ------------------ */
#define XDIAGM1        3671
#define XDIAGM2        3672
#define XDIAGM3        3673
#define XDIAGM4        3674
#define XDIAGM5        3675
#define XDIAGM6        3676
#define XDIAGM7        3677 
#define XDIAGM8        3678
#define XDIAGM9        3679
#define XDIAGMA        3680 
#define XDIAGMB        3681
#define XDIAGMC        3682
#define XDIAGMD        3683
#define XDIAGME        3684
#define XDIAGMF        3685
#define XDIAGM10       3686
#define XDIAGM11       3687
#define XDIAGM12       3688
#define XDIAGM13       3689
#define XDIAGM14       3690
#define XDIAGM15       3691
#define XDIAGM16       3692
#define XDIAGM17       3693
#define XDIAGM18       3694
#define XDIAGM19       3695
#define XDIAGM1A       3696
#define XDIAGM1B       3697
#define XDIAGM1C       3698
#define XDIAGM1D       3699
#define XDIAGM1E       3700
#define XDIAGM1F       3701
#define XDIAGM20       3702
#define XDIAGM21       3703
#define XDIAGM22       3704
#define XDIAGM23       3705
#define XDIAGM24       3706
#define XDIAGM25       3707
#define XDIAGM26       3708
#define XDIAGM27       3709
#define XDIAGM28       3710
#define XDIAGM29       3711
#define XDIAGM2A       3712
#define XDIAGM2B       3713
#define XDIAGM2C       3714
#define XDIAGM2D       3715
#define IDIAGM2E       3716
#define IDIAGM2F       3717
#define IDIAGM30       3718
#define IDIAGM31       3719
#define IDIAGM32       3720
#define IDIAGM33       3721
#define IDIAGM34       3722 
#define IDIAGM35       3723 
#define IDIAGM36       3724
#define XDIAGM37       3725
#define XDIAGM38       3726
#define XDIAGM39       3727
#define XDIAGM3A       3728
#define XDIAGM3B       3729
#define XDIAGM3C       3730
#define XDIAGM3D       3731
#define XDIAGM3E       3732
#define XDIAGM3F       3733
#define XDIAGM40       3734 
#define XDIAGM41       3735
#define XDIAGM42       3736 
#define XDIAGM43       3737
#define XDIAGM44       3738
#define XDIAGM45       3739
#define XDIAGM46       3740
#define XDIAGM47       3741
#define XDIAGM48       3742
#define XDIAGM49       3743
#define XDIAGM4A       3744
#define XDIAGM4B       3745
#define XDIAGM4C       3746
#define XDIAGM4D       3747
#define XDIAGM4E       3748
#define XDIAGM4F       3749
#define XDIAGM50       3750
#define XDIAGM51       3751
#define XDIAGM52       3752
#define XDIAGM53       3753
#define XDIAGM54       3754
#define XDIAGM55       3755
#define XDIAGM56       3756
#define XDIAGM57       3757
#define XDIAGM58       3758 
#define XDIAGM59       3759
#define XDIAGM5A       3760
#define XDIAGM5B       3761
#define XDIAGM5C       3762
#define XDIAGM5D       3763
#define XDIAGM5E       3764
#define XDIAGM5F       3765
#define XDIAGM60       3766
#define XDIAGM61       3767
#define XDIAGM62       3768
#define XDIAGM63       3769
#define XDIAGM64       3770
#define XDIAGM65       3771
#define XDIAGM66       3772
#define XDIAGM67       3773
#define XDIAGM68       3774
#define XDIAGM69       3775
#define XDIAGM6A       3776
#define XDIAGM6B       3777
#define XDIAGM6C       3778
#define XDIAGM6D       3779
#define XDIAGM6E       3780
#define XDIAGM6F       3781
#define XDIAGM70       3782 
#define XDIAGM71       3783
#define XDIAGM72       3784
#define XDIAGM73       3785
#define XDIAGM74       3786
#define XDIAGM75       3787
#define XDIAGM76       3788
#define XDIAGM77       3789
#define XDIAGM78       3790
#define XDIAGM79       3791
#define XDIAGM7A       3792
#define XDIAGM7B       3793
#define XDIAGM7C       3794
#define XDIAGM7D       3795
#define XDIAGM7E       3796
#define XDIAGM7F       3797
#define XDIAGM80       3798
#define XDIAGM81       3799
#define XDIAGM82       3800
#define XDIAGM83       3801
#define XDIAGM84       3802
#define XDIAGM85       3803
#define XDIAGM86       3804
#define XDIAGM87       3805
#define XDIAGM88       3806
#define XDIAGM89       3807
#define XDIAGM8A       3808
#define XDIAGM8B       3809
#define XDIAGM8C       3810
#define XDIAGM8D       3811
#define XDIAGM8E       3812
#define XDIAGM8F       3813
#define XDIAGM90       3814
#define XDIAGM91       3815
#define XDIAGM92       3816
#define XDIAGM93       3817
#define XDIAGM94       3818
#define XDIAGM95       3819 
#define XDIAGM96       3820
#define XDIAGM97       3821
#define XDIAGM98       3822
#define XDIAGM99       3823
#define XDIAGM9A       3824
#define XDIAGM9B       3825
#define XDIAGM9C       3826
#define XDIAGM9D       3827
#define XDIAGM9E       3828
#define XDIAGM9F       3829
#define XDIAGM100      3830
#define XDIAGM101      3831
#define XDIAGM102      3832
#define XDIAGM103      3833
#define XDIAGM104      3834
#define XDIAGM105      3835
#define XDIAGM106      3836
#define XDIAGM107      3837
#define XDIAGM108      3838
#define XDIAGM109      3839
#define XDIAGM10A      3840
#define XDIAGM10B      3841
#define XDIAGM10C      3842
#define XDIAGM10D      3843
#define XDIAGM10E      3844
#define XDIAGM10F      3845
#define XDIAGM110      3846
#define XDIAGM111      3847
#define XDIAGM112      3848
#define XDIAGM113      3849 
#define XDIAGM114      3850
#define XDIAGM115      3851
#define XDIAGM116      3852
#define XDIAGM117      3853
#define XDIAGM118      3854
#define XDIAGM119      3855
#define XDIAGM11A      3856
#define XDIAGM11B      3857
#define XDIAGM11C      3858
#define XDIAGM11D      3859
#define XDIAGM11E      3860
#define XDIAGM11F      3861
#define XDIAGM120      3862
#define XDIAGM121      3863
#define XDIAGM122      3864
#define XDIAGM123      3865
#define XDIAGM124      3866
#define XDIAGM125      3867
#define XDIAGM126      3868
#define XDIAGM127      3869
#define XDIAGM128      3870
#define XDIAGM129      3871
#define XDIAGM12A      3872
#define XDIAGM12B      3873
#define XDIAGM12C      3874
#define XDIAGM12D      3875
#define XDIAGM12E      3876
#define XDIAGM12F      3877
#define XDIAGM130      3878
#define XDIAGM131      3879
#define XDIAGM132      3880
#define XDIAGM133      3881
#define XDIAGM134      3882
#define XDIAGM135      3883
#define XDIAGM136      3884
#define XDIAGM137      3885
#define XDIAGM138      3886
#define XDIAGM139      3887
#define XDIAGM13A      3888
#define XDIAGM13B      3889
#define XDIAGM13C      3890
#define XDIAGM13D      3891
#define XDIAGM13E      3892
#define XDIAGM13F      3893
#define XDIAGM140      3894
#define XDIAGM141      3895
#define XDIAGM142      3896
#define XDIAGM143      3897
#define XDIAGM144      3898
#define XDIAGM145      3899
#define XDIAGM146      3900
#define XDIAGM147      3901
#define XDIAGM148      3902
#define XDIAGM149      3903
#define XDIAGM14A      3904
#define XDIAGM14B      3905
#define XDIAGM14C      3906
#define XDIAGM14D      3907
#define XDIAGM14E      3908
#define XDIAGM14F      3909
#define XDIAGM150      3910
#define XDIAGM151      3911
#define XDIAGM152      3912
#define XDIAGM153      3913
#define XDIAGM154      3914
#define XDIAGM155      3915
#define XDIAGM156      3916
#define XDIAGM157      3917
#define XDIAGM158      3918
#define XDIAGM159      3919
#define XDIAGM15A      3920
#define XDIAGM15B      3921
#define XDIAGM15C      3922
#define XDIAGM15D      3923
#define XDIAGM15E      3924
#define XDIAGM15F      3925
#define XDIAGM160      3926
#define XDIAGM161      3927
#define XDIAGM162      3928
#define XDIAGM163      3929
#define XDIAGM164      3930
#define XDIAGM165      3931
#define XDIAGM166      3932
#define XDIAGM167      3933
#define XDIAGM168      3934
#define XDIAGM169      3935
#define XDIAGM16A      3936
#define XDIAGM16B      3937
#define XDIAGM16C      3938
#define XDIAGM16D      3939
#define XDIAGM16E      3940
#define XDIAGM16F      3941
#define XFORMACT       3942
/* ---------------- neue zusaetzliche Sonderregister ---------------------- */
#define XIQSON30       3943
#define XIQSON31       3944
#define XIQSON32       3945
#define XIQSON33       3946
#define XIQSON34       3947
#define XIQSON35       3948
#define XIQSON36       3949
#define XIQSON37       3950
#define XIQSON38       3951
#define XIQSON39       3952
#define XIQSON3A       3953
#define XIQSON3B       3954
#define XIQSON3C       3955
#define XIQSON3D       3956
#define XIQSON3E       3957
#define XIQSON3F       3958
#define XIQSON40       3959
#define XIQSON41       3960
#define XIQSON42       3961
#define XIQSON43       3962
#define XIQSON44       3963
#define XIQSON45       3964
#define XIQSON46       3965
#define XIQSON47       3966
#define XIQSON48       3967
#define XIQSON49       3968
#define XIQSON4A       3969
#define XIQSON4B       3970
#define XIQSON4C       3971
#define XIQSON4D       3972
#define XIQSON4E       3973
#define XIQSON4F       3974
#define XIQSON50       3975
#define XIQSON51       3976
#define XIQSON52       3977
#define XIQSON53       3978
#define XIQSON54       3979
#define XIQSON55       3980
#define XIQSON56       3981
#define XIQSON57       3982
#define XIQSON58       3983
#define XIQSON59       3984
#define XIQSON5A       3985
#define XIQSON5B       3986
#define XIQSON5C       3987
#define XIQSON5D       3988
#define XIQSON5E       3989
#define XIQSON5F       3990
#define XIQSON60       3991
#define XIQSON61       3992
#define XIQSON62       3993
#define XIQSON63       3994
#define XIQSON64       3995
#define XIQSON65       3996
#define XIQSON66       3997
#define XIQSON67       3998
#define XIQSON68       3999
/* ---------------- Zusaetzlich definierte Schummelregister --------------- */
#define XXNAHUB_SOLL   4000     /* Sollwert eines eigentlich als Istwert    */
                                /* definierten Registers. Dient dazu, die   */
                                /* Registerschnittstelle zu betruegen, um   */
                                /* auch in den Istwert etwas schreiben zu   */
                                /* koennen.                04.12.90 TSchw   */
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
/* ---------------- Register die nur im 10-Stufen-Modus benutzt werden ---- */
#define XXTSEG1        4001
#define XXTSEG2        4002
#define XXTSEG3        4003
#define XXTSEG4        4004
#define XXTSEG5        4005
#define XXTSEG6        4006
#define XXTSEG7        4007
#define XXTSEG8        4008
#define XXTSEG9        4009
#define XXTSEG10       4010

#define XXPSEG1        4031
#define XXPSEG2        4032
#define XXPSEG3        4033
#define XXPSEG4        4034
#define XXPSEG5        4035
#define XXPSEG6        4036
#define XXPSEG7        4037
#define XXPSEG8        4038
#define XXPSEG9        4039
#define XXPSEG10       4040

#define XSSSEG1        4061
#define XSSSEG2        4062
#define XSSSEG3        4063
#define XSSSEG4        4064
#define XSSSEG5        4065
#define XSSSEG6        4066
#define XSSSEG7        4067
#define XSSSEG8        4068
#define XSSSEG9        4069
#define XSSSEG10       4070

#define XSVSEG1        4091
#define XSVSEG2        4092
#define XSVSEG3        4093
#define XSVSEG4        4094
#define XSVSEG5        4095
#define XSVSEG6        4096
#define XSVSEG7        4097
#define XSVSEG8        4098
#define XSVSEG9        4099
#define XSVSEG10       4100

#define XSPSEG1        4121
#define XSPSEG2        4122
#define XSPSEG3        4123
#define XSPSEG4        4124
#define XSPSEG5        4125
#define XSPSEG6        4126
#define XSPSEG7        4127
#define XSPSEG8        4128
#define XSPSEG9        4129
#define XSPSEG10       4130

/* ---------------- Nachdruckzeiten --------------------------------------- */
#define XSTNA1         4151
#define XSTNA2         4152
#define XSTNA3         4153
#define XSTNA4         4154
#define XSTNA5         4155
#define XSTNA6         4156
#define XSTNA7         4157
#define XSTNA8         4158
#define XSTNA9         4159
#define XSTNA10        4160

/* ---------------- Nachdrcke -------------------------------------------- */
#define XSPNA1         4181
#define XSPNA2         4182
#define XSPNA3         4183
#define XSPNA4         4184
#define XSPNA5         4185
#define XSPNA6         4186
#define XSPNA7         4187
#define XSPNA8         4188
#define XSPNA9         4189
#define XSPNA10        4190
/* ---------------- Airpress-Register ------------------------------------- */
#define XAPD_TYPE      4191
#define XAPD_MODE      4192
#define XAPSPSYST      4193
#define XAPIPSYST      4194
/* ------------------------------------------------------------------------ */
#define XWZIFSICHT     4195
#define XSLIPSDRMAX    4196
#define XSPIP1AKTUE    4197
#define XSPIP2AKTUE    4198
#define XOPM_SPSTXT    4199
#define XRFAST10       4200
#define XRFAST11       4201
#define XRFAST12       4202
#define XRFAST13       4203
#define XRFAST14       4204
#define XRFAST15       4205
#define XRFAST16       4206
#define XTEXT_DRVMODUL11 4207
#define XTEXT_DRVMODUL12 4208
#define XTEXT_DRVMODUL22 4209
#define XTEXT_DRVMOTOR11 4210
#define XTEXT_DRVMOTOR12 4211
#define XTEXT_DRVMOTOR22 4212
#define XTEXT_DRVSERIEN_NR11 4213
#define XTEXT_DRVSERIEN_NR12 4214
#define XTEXT_DRVSERIEN_NR22 4215
#define XXSSDOS1       4216
/* ---------------- B/W-Register fuer Mehrfarbmaschinen ------------------- */
#define XXNSTEP2       4217
#define XXSWEG13       4218
#define XXTDOS3        4219
#define XXWDRE3        4220
#define XXNSTEP3       4221
#define XXNPAS3        4222
#define XXSWEG14       4223
#define XXTDOS4        4224
#define XXWDRE4        4225
#define XXNSTEP4       4226
#define XXNPAS4        4227
#define XXSWEG15       4228
#define XXTDOS5        4229
#define XXWDRE5        4230
#define XXNSTEP5       4231
#define XXNPAS5        4232
#define XXSWEG16       4233
#define XXTDOS6        4234
#define XXWDRE6        4235
#define XXNSTEP6       4236
#define XXNPAS6        4237
/* neue zusaetzliche Gillette-Sonderegister */
#define GIL_SSON120    4238
#define GIL_SSON121    4239
#define GIL_SSON122    4240
#define GIL_SSON123    4241       
#define GIL_SSON124    4242
#define GIL_SSON125    4243
#define GIL_SSON126    4244
#define GIL_SSON127    4245
#define GIL_SSON128    4246
#define GIL_SSON129    4247
#define GIL_SSON130    4248
#define GIL_SSON131    4249
#define GIL_SSON132    4250
#define GIL_SSON133    4251       
#define GIL_SSON134    4252
#define GIL_SSON135    4253
#define GIL_SSON136    4254
#define GIL_SSON137    4255
#define GIL_SSON138    4256
#define GIL_SSON139    4257
#define GIL_SSON140    4258
#define GIL_SSON141    4259
#define GIL_SSON142    4260
#define GIL_SSON143    4261       
#define GIL_SSON144    4262
#define GIL_SSON145    4263
#define GIL_SSON146    4264
#define GIL_SSON147    4265
#define GIL_SSON148    4266
#define GIL_SSON149    4267
#define GIL_SSON150    4268
#define GIL_SSON151    4269
#define GIL_SSON152    4270
#define GIL_SSON153    4271       
#define GIL_SSON154    4272
#define GIL_SSON155    4273
#define GIL_SSON156    4274
#define GIL_SSON157    4275
#define GIL_SSON158    4276
#define GIL_SSON159    4277
#define GIL_SSON160    4278
#define GIL_SSON161    4279
#define GIL_SSON162    4280
#define GIL_SSON163    4281       
#define GIL_SSON164    4282
#define GIL_SSON165    4283
#define GIL_SSON166    4284
#define GIL_SSON167    4285
#define GIL_SSON168    4286
#define GIL_SSON169    4287
#define GIL_SSON170    4288
#define GIL_SSON171    4289
#define GIL_SSON172    4290
#define GIL_SSON173    4291       
#define GIL_SSON174    4292
#define GIL_SSON175    4293
#define GIL_SSON176    4294
#define GIL_SSON177    4295
#define GIL_SSON178    4296
#define GIL_SSON179    4297
#define GIL_SSON180    4298
#define GIL_SSON181    4299
#define XPGW3          4300
#define XSFOIDR        4301

#define XXXNACH        4303
#define XXXSEGM        4304
#define XXSNAC1        4305
#define XXXSEGM2       4306
#define XXTEINS1       4307


#define XSPSPUM        4320
#define XXPUM          4321

#define XSNSPST        4327
#define XSNNDST        4328
#define XXSPEUQL       4330
#define XHZIT_VERZ1    4331
#define XHZIT_VERZ2    4332
#define XHZIT_VERZ3    4333
#define XHZIT_VERZ4    4334
#define XHZIT_VERZ5    4335
#define XHZIT_VERZ6    4336
#define XXTKUHL        4337
#define XXTNACHD       4338

/* Zusaetzliche Register fuer Elektra */
#define XSSFZU4       4400
#define XSVZU3        4401
#define IQSCREWDIAM   4402
#define IQCOOK        4403
#define IQCONOTOK     4404
#define IQFRCOUNTER   4405
#define XOPS_NEUST    4406
#define IQCLMAXSTRK   4407
#define XOPSNKARTON   4408
#define XOPINKARTON   4409
/* ---------------- Register der Seite 69.0 fuer Luftventile 5 bis 8 --------*/
#define XLVSNEIN4      4410
#define XLVSNEIN5      4411
#define XLVSNEIN6      4412
#define XLVSNEIN7      4413
#define XLVSSWEGP5     4414
#define XLVSSWEGP6     4415
#define XLVSSWEGP7     4416
#define XLVSSWEGP8     4417
#define XLVSTVERZ70    4418
#define XLVSTVERZ80    4419
#define XLVSTBLAS70    4420
#define XLVSTBLAS80    4421

/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XSPPH31        4500
#define XSPPH32        4501
#define XSPPH33        4502
#define XSPPH34        4503
#define XSPPH35        4504
#define XSPPH36        4505
#define XSPPH41        4506
#define XSPPH42        4507
#define XSPPH43        4508
#define XSPPH44        4509
#define XSPPH45        4510
#define XSPPH46        4511
/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XSVPH31        4512
#define XSVPH32        4513
#define XSVPH33        4514
#define XSVPH34        4515
#define XSVPH35        4516
#define XSVPH36        4517
#define XSVPH41        4518
#define XSVPH42        4519
#define XSVPH43        4520
#define XSVPH44        4521
#define XSVPH45        4522
#define XSVPH46        4523
/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XSTPH31        4524
#define XSTPH32        4525
#define XSTPH33        4526
#define XSTPH34        4527
#define XSTPH35        4528
#define XSTPH36        4529
#define XSTPH41        4530
#define XSTPH42        4531
#define XSTPH43        4532
#define XSTPH44        4533
#define XSTPH45        4534
#define XSTPH46        4535
/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XSPUM31        4536
#define XSPUM32        4537
#define XSPUM33        4538
#define XSPUM34        4539
#define XSPUM35        4540
#define XSPUM41        4541
#define XSPUM42        4542
#define XSPUM43        4543
#define XSPUM44        4544
#define XSPUM45        4545
/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XSSPH30        4546
#define XSSPH31        4547
#define XSSPH32        4548
#define XSSPH33        4549
#define XSSPH34        4550
#define XSSPH35        4551
#define XSSPOL3        4552
#define XSSPH40        4553
#define XSSPH41        4554
#define XSSPH42        4555
#define XSSPH43        4556
#define XSSPH44        4557
#define XSSPH45        4558
#define XSSPOL4        4559

/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XXPPH31        4572
#define XXPPH32        4573
#define XXPPH33        4574
#define XXPPH34        4575
#define XXPPH35        4576
#define XXPPH36        4577
#define XXPPH41        4578
#define XXPPH42        4579
#define XXPPH43        4580
#define XXPPH44        4581
#define XXPPH45        4582
#define XXPPH46        4583
/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XXTPH31        4584
#define XXTPH32        4585
#define XXTPH33        4586
#define XXTPH34        4587
#define XXTPH35        4588
#define XXTPH36        4589
#define XXTPH41        4590
#define XXTPH42        4591
#define XXTPH43        4592
#define XXTPH44        4593
#define XXTPH45        4594
#define XXTPH46        4595
/* ---------------- indizierte Register Reihenfolge einhalten ---------------*/
#define XXSPH30        4596
#define XXSPH31        4597
#define XXSPH32        4598
#define XXSPH33        4599
#define XXSPH34        4600
#define XXSPH35        4601
#define XXSPOL3        4602
#define XXSPH40        4603
#define XXSPH41        4604
#define XXSPH42        4605
#define XXSPH43        4606
#define XXSPH44        4607
#define XXSPH45        4608
#define XXSPOL4        4609

#define XSF80AG3       4622
#define XSF80AG4       4623
#define XSSDOS3        4624
#define XSSUM31        4625
#define XSWPL31        4626
#define XSWPL32        4627
#define XSPST31        4628
#define XSPST32        4629
#define XSPSTH3        4630
#define XSNRUK3        4631
#define XSSRUK3        4632
#define XSVRUK3        4633
#define XSTVDO3        4634
#define XSTINT3        4635
#define XSSDOS4        4636
#define XSSUM41        4637
#define XSWPL41        4638
#define XSWPL42        4639
#define XSPST41        4640
#define XSPST42        4641
#define XSPSTH4        4642
#define XSNRUK4        4643
#define XSSRUK4        4644
#define XSVRUK4        4645
#define XSTVDO4        4646
#define XSTINT4        4647
#define XSNPHM3        4648
#define XSNPHM4        4649
#define XSNFIN3        4650
#define XSNFIN4        4651
#define XKXEMP3        4652
#define XKXEMP4        4653
#define XAGSTVVER1     4654
#define XAGSTVVER2     4655
#define XAGSTVVER3     4656
#define XAGSTVVER4     4657
#define XSPSTVERZ1     4658
#define XSPSTVERZ2     4659
#define XSPSTVERZ3     4660
#define XSPSTVERZ4     4661
#define XSNAGG3        4662
#define XSNAGG4        4663
#define XSTAGG3        4664
#define XSTAGG4        4665
#define XSTDUES3       4666
#define XSTDUES4       4667
#define XSVAG3V        4668
#define XSVAG4V        4669
#define XSVAG3Z        4670
#define XSVAG4Z        4671
#define XSFAGG3        4672
#define XSFAGG4        4673
#define XSTDOS3        4674
#define XSTDOS4        4675
#define XSAG3PFO       4676
#define XSAG4PFO       4677
#define XXPFI3M        4678
#define XXPFI4M        4679
/* ---------------- 5/6 Farbmaschine -------------------------------------- */
#define XSPPH51        4680
#define XSPPH52        4681
#define XSPPH53        4682
#define XSPPH54        4683
#define XSPPH55        4684
#define XSPPH56        4685
#define XSPPH61        4686
#define XSPPH62        4687
#define XSPPH63        4688
#define XSPPH64        4689
#define XSPPH65        4690
#define XSPPH66        4691
#define XSVPH51        4692
#define XSVPH52        4693
#define XSVPH53        4694
#define XSVPH54        4695
#define XSVPH55        4696
#define XSVPH56        4697
#define XSVPH61        4698
#define XSVPH62        4699
#define XSVPH63        4700
#define XSVPH64        4701
#define XSVPH65        4702
#define XSVPH66        4703
#define XSTPH51        4704
#define XSTPH52        4705
#define XSTPH53        4706
#define XSTPH54        4707
#define XSTPH55        4708
#define XSTPH56        4709
#define XSTPH61        4710
#define XSTPH62        4711
#define XSTPH63        4712
#define XSTPH64        4713
#define XSTPH65        4714
#define XSTPH66        4715
#define XSPUM51        4716
#define XSPUM52        4717
#define XSPUM53        4718
#define XSPUM54        4719
#define XSPUM55        4720
#define XSPUM61        4721
#define XSPUM62        4722
#define XSPUM63        4723
#define XSPUM64        4724
#define XSPUM65        4725
#define XSSPH51        4726
#define XSSPH52        4727
#define XSSPH53        4728
#define XSSPH54        4729
#define XSSPH55        4730
#define XSSPH61        4731
#define XSSPH62        4732
#define XSSPH63        4733
#define XSSPH64        4734
#define XSSPH65        4735
#define XXPPH51        4736
#define XXPPH52        4737
#define XXPPH53        4738
#define XXPPH54        4739
#define XXPPH55        4740
#define XXPPH56        4741
#define XXPPH61        4742
#define XXPPH62        4743
#define XXPPH63        4744
#define XXPPH64        4745
#define XXPPH65        4746
#define XXPPH66        4747
#define XXTPH51        4748
#define XXTPH52        4749
#define XXTPH53        4750
#define XXTPH54        4751
#define XXTPH55        4752
#define XXTPH56        4753
#define XXTPH61        4754
#define XXTPH62        4755
#define XXTPH63        4756
#define XXTPH64        4757
#define XXTPH65        4758
#define XXTPH66        4759
#define XXSPH51        4760
#define XXSPH52        4761
#define XXSPH53        4762
#define XXSPH54        4763
#define XXSPH55        4764
#define XXSPOL5        4765
#define XXSPH61        4766
#define XXSPH62        4767
#define XXSPH63        4768
#define XXSPH64        4769
#define XXSPH65        4770
#define XXSPOL6        4771
#define XSSDOS5        4772
#define XSSDOS6        4773
#define XSSUM51        4774
#define XSSUM61        4775
#define XSWPL51        4776
#define XSWPL61        4777
#define XSWPL52        4778
#define XSWPL62        4779
#define XSPST51        4780
#define XSPST61        4781
#define XSPST52        4782
#define XSPST62        4783
#define XSSRUK5        4784
#define XSSRUK6        4785
#define XSVRUK5        4786
#define XSVRUK6        4787
#define XSTVDO5        4788
#define XSTVDO6        4789
#define XSTINT5        4790
#define XSTINT6        4791
#define XSNPHM5        4792
#define XSNPHM6        4793
#define XXSPH50        4794
#define XXSPH60        4795
#define XSNFIN5        4796
#define XSNFIN6        4797
#define XKXEMP5        4798
#define XKXEMP6        4799
#define XSNAGG5        4800
#define XSNAGG6        4801
#define XSTAGG5        4802
#define XSTAGG6        4803
#define XSTDUES5       4804
#define XSTDUES6       4805
#define XSFAGG5        4806
#define XSFAGG6        4807
#define XSTDOS5        4808
#define XSTDOS6        4809
#define XSNRUK5        4810
#define XSNRUK6        4811
#define XSVAG5V        4812
#define XSVAG6V        4813
#define XSVAG5Z        4814
#define XSVAG6Z        4815
#define XSF80AG5       4816
#define XSF80AG6       4817
#define XSAG5PFO       4818
#define XSAG6PFO       4819
#define XXPFI5M        4820
#define XXPFI6M        4821
#define XSPSTH5        4822
#define XSPSTH6        4823
#define IAGGRVOR5      4824
#define IAGGRVOR6      4825
#define IEINSPR5       4826
#define IEINSPR6       4827
#define IDOS5          4828
#define IDOS6          4829
#define XPL5GENMOD     4830
#define XPL6GENMOD     4831
#define XPLSKRAMPE5    4832
#define XPLSKRAMPE6    4833
#define XPLIKARAMP5    4834
#define XPLIKARAMP6    4835
#define XPLIKDRAMP5    4836
#define XPLIKDRAMP6    4837
#define XPLSKGEST5     4838
#define XPLSKGEST6     4839
#define XPLIKAGEST5    4840
#define XPLIKAGEST6    4841
#define XPLIKDGEST5    4842
#define XPLIKDGEST6    4843
#define XSRSSVOR_5     4844
#define XSRSSVOR_6     4845
#define XSRSVVOR_5     4846
#define XSRSVVOR_6     4847
#define XSRSSNACH_5    4848
#define XSRSSNACH_6    4849
#define XSRSVNACH_5    4850
#define XSRSVNACH_6    4851
#define XAGSTVVER5     4852
#define XAGSTVVER6     4853
#define XSPSTVERZ5     4854
#define XSPSTVERZ6     4855
#define XTABSZYL5      4856
#define XTABSZYL6      4857
#define XSNGDREHM5     4858
#define XSNGDREHM6     4859
#define XSEGPUST5      4860
#define XSEGPUST6      4861
#define XPLGWEG5       4862
#define XPLGWEG6       4863
#define XSNG_UMDR5     4864
#define XSNG_UMDR6     4865

/* ---------------- Neue Sollregister fuer B&R/450 ------------------------ */
#define XTABSWKZ       4990
#define XTABSZYL1      4991
#define XTABSZYL2      4992
#define XFORMMIN       5000
#define IROSNPROGRAMM  5001
#define IROS_ABLAGE    5002      
#define IROSTYSGM      5003       
#define IROSTXVOR      5004       
#define IROSTAUSVOR    5005      
#define IROSTGRFEIN    5006      
#define IROSTGRFAUS    5007      
#define IROSTAUSZUR    5008      
#define IROSTXZUR      5009       
#define IROSTB_C       5010        
#define IROSTYABL      5011       
#define IROSTFORMZU    5012      
#define IROSTBANDTAKT  5013
#define IROSTABBLASEN  5014
#define IROSTAUSBIS    5015
#define IROSTZUEBW     5016
#define IROSNSONDABL   5017
#define IAKTOUTPUT6    5018
#define IFORCEOUTPUT6  5019
#define IAKTOUTPUT7    5020
#define IFORCEOUTPUT7  5021
#define IA0INPUT       5022
#define IA1INPUT       5023
#define IA2INPUT       5024
#define IA3INPUT       5025
#define IAKTINPUT4     5026
#define IAKTINPUT5     5027
#define ISESSFZU2      5028
#define ISESVFZU3      5029
/* ---------------- Register fuer Diagnosemode K-Maschinen eingefuegt ----- */
#define IWKZSCHL       5030  
#define IWKZSICH       5031  
#define ISCHLDRAUFB    5032  
#define IAGGRVOR       5033  
#define IEINSPR        5034  
#define IDOS           5035  
#define IKUEHL         5036  
#define IWKZOEFFN      5037  
#define IAUSWVOR       5038  
#define IAUSWZUR       5039  
#define IPAUSZEIT      5040  
#define IZYKZEIT       5041  
#define IB8007IST      5042  
#define I4B3IST        5043  
#define IY8007IST      5044  
#define IB8025IST      5045  
#define IY7019IST      5046  
#define IY8025IST      5047  
#define I5B5IST        5048  
#define IY7008IST      5049  
#define I5B4IST        5050  
#define IY8003IST      5051  
#define IY8007SOLL     5052  
#define IY7019SOLL     5053  
#define IY8025SOLL     5054  
#define IY7008SOLL     5055  
#define IY8003SOLL     5056  
#define IMSSSK11       5057  
#define IMSSSOFF1      5058
#define IMSSSK12       5059
#define IMSSSOFF2      5060
#define IMSSSK13       5061
#define IMSSSOFF3      5062
#define IMSSSK14       5063
#define IMSSSOFF4      5064
#define IMSISK11       5065
#define IMSISOFF1      5066
#define IMSISK12       5067
#define IMSISOFF2      5068
#define IMSISK13       5069
#define IMSISOFF3      5070
#define IMSISK14       5071
#define IMSISOFF4      5072
#define IMSISAKT1      5073
#define IMSISAKT2      5074
#define IMSISAKT3      5075
#define IMSISAKT4      5076
#define IMSINAKT       5077
#define IMSINSTAT      5078
#define IDIAGOUT       5079
#define IGENMOD        5080
#define ISSCMD         5081
#define IAPS_WAHL      5082
#define IAPS_STUFEN    5083
#define IAPSTVERZ      5084
#define IAPSPLOCK1     5085
#define IAPSTAKTIO1    5086
#define IAPSPLOCK2     5087
#define IAPSTAKTIO2    5088
#define IAPSPLOCK3     5089
#define IAPSTAKTIO3    5090
#define IAPSPLOCK4     5091
#define IAPSSSTART     5092
#define IAPS_NRSTUF    5093
#define IAPSSPWEG      5094
#define IOPS_XAIR      5095
#define IOPSTVAIR      5096
#define IOPSTVINJ      5097
#define IOPS_HYDU      5098
#define IOPSSHYDU      5099
#define IOPSPVOR       5100
#define IOPIPVOR       5101
#define IOPSPGAS1      5102
#define IOPIPGAS1      5103
#define IOPST1AIR      5104
#define IOPSPGAS2      5105
#define IOPIPGAS2      5106
#define IOPST2AIR      5107
#define IOPSPGAS3      5108
#define IOPIPGAS3      5109
#define IOPST3AIR      5110
#define IOPSPNACH      5111
#define IOPSTNACH      5113
#define ITEXT_6        5114
#define ITEXT_7        5115
#define IKESV3IN1      5116
#define IKESV4IN1      5117
#define IKESV1IN2      5118
#define IKESV2IN2      5119
#define IKESV3IN2      5120
#define IKESV4IN2      5121
#define IKESV3OU1      5122
#define IKESV4OU1      5123
#define IKESV1OU2      5124
#define IKESV2OU2      5125
#define IKESV3OU2      5126
#define IKESV4OU2      5127
#define IKESP3IN1      5128
#define IKESP4IN1      5129
#define IKESP1IN2      5130
#define IKESP2IN2      5131
#define IKESP3IN2      5132
#define IKESP4IN2      5133
#define IKESP3OU1      5134
#define IKESP4OU1      5135
#define IKESP1OU2      5136
#define IKESP2OU2      5137
#define IKESP3OU2      5138
#define IKESP4OU2      5139
#define IKES_ARL       5140
#define IKESTAVWO      5141
#define IKESTAVSA      5142
#define IKESTAAAU      5143
#define IKESTAVSAU     5144
#define IKESSAWSA      5145
#define IKES_AZNS      5146
#define IKES_AUESB     5147
#define IKESVAUSG      5148
#define IKESPAUSD      5149
#define IKESPAUSND     5150
#define IKESVAEING     5151
#define IKESPAEIND     5152
#define IKESPAEINND    5153
#define IWZS_SNSP      5154
/* ------------------------------------------------------------------------- */
#define ICLYEAR        5155
#define ICLMONTH       5156
#define ICLMDAY        5157
#define ICLHOUR        5158
#define ICLMIN         5159
#define IHES_BLOPT     5160
#define IHES_BLOPT2    5161
#define XSEGPUST       5162
#define XSEGPUST2      5163
#define XSEGPUST3      5164
#define XSEGPUST4      5165
#define XTABSZYL3      5166
#define XTABSZYL4      5167
#define IAKTOUTPUT8    5168
#define IFORCEOUTPUT8  5169
#define IAKTINPUT2     5170
#define XMSSFOFFSP     5171
#define XMSSFOFFGK     5172
#define XMSSKOFFET     5173
#define XMSSNHOLM      5174
#define XMSIFOFFSP     5175
#define XMSIFOFFGK     5176
#define XMSIKOFFET     5177
#define XMSINHOLM      5178
#define XSPIKKRAFT     5179
#define XGKIKKRAFT     5180
#define XMSMODUS       5181
#define XGKIKPROZ      5182
#define IAKTINPUT3     5183
#define IAKTOUTPUT5    5184
#define IFORCEOUTPUT5  5185
#define IAKTINPUT34    5186
#define IAKTOUTPUT9    5187
#define IAKTOUTPUT36   5188
#define IAKTOUTPUT39   5189
#define XAWGWEG        5190
#define XSNGDREHM1     5191
#define XSNGDREHM2     5192
#define XSNGDREHM3     5193
#define XSNGDREHM4     5194
#define XPLGWEG1       5195
#define XPLGWEG2       5196
#define XPLGWEG3       5197
#define XPLGWEG4       5198
/* ---------------- SPS Texte --------------------------------------------- */
#define ITEXT_5        5199
#define ITEXT_1        5200
#define ITEXT_2        5201
#define ITEXT_3        5202
#define ITEXT_4        5203
#define IENDADDR       5204
/* ---------------- Qualitaetskontrolle ----------------------------------- */
#define IQUSNASZ       5205 /*    Ausschuss nach Automatikstart             */
#define IQUSNASST      5206 /*    Ausschuss nach Stoerung                   */
#define IQUSNPTZY      5207 /*    Stichprobe                                */
#define IQUSNPTST      5208 /*    Pruefteil nach Stoerung                   */
#define IQUSTVWO       5209 /*    Verz.zeit Werkz. oeffnen                  */
#define IQUINANZ1      5210 /*    Ausschuss nach Automatikstart             */
#define IQUINANZ2      5211 /*    Ausschuss nach Stoerung                   */
#define IQUINANZ3      5212 /*    Stichprobe                                */  
#define IQUINANZ4      5213 /*    Pruefteil nach Stoerung                   */
/* ---------------- Selektierweiche --------------------------------------- */
#define IQUS_SELEK     5214 /*    Betriebsart Selektierweiche               */
#define IQUS_ANGUS     5215 /*    Umschaltkrit. Angusstrennung              */
#define IQUSTVERZ      5216 /*    Verzoegerungszeit                         */
/* ---------------- Heizung Kanalbenennung -------------------------------- */
#define IHZ_CURREG     5217 /*    aktueller Regler auf Seite 39.1           */
#define IHZ_TEMPMOD    5218 /*    Fuehler Modul                             */
#define IHZ_TEMPKAN    5219 /*    Fuehler Kanal                             */
#define IHZ_HEIZMOD    5220 /*    Heizausgangsmodul                         */
#define IHZ_HEIZKAN    5221 /*    Heizausgangskanal                         */
#define IHZ_KUELMOD    5222 /*    Kuehlausgangsmodul                        */
#define IHZ_KUELKAN    5223 /*    Kuehlausgangskanal                        */
/* ---------------- Schneckenrueckzug vor/nach (1. und 2. AGG) ------------ */
#define XSRSSVOR_1     5224 /* Schneckenrueckzug vor Plastifizieren Agg.1  */
#define XSRSSVOR_2     5225 /* Schneckenrueckzug vor Plastifizieren Agg.2  */
#define XSRSVVOR_1     5226 /* Rueckzugsgeschwindigk. vor Plastifizieren Agg.1 */
#define XSRSVVOR_2     5227 /* Rueckzugsgeschwindigk. vor Plastifizieren Agg.2 */
#define XSRSSNACH_1    5228 /* Schneckenrueckzug nach Plastifizieren Agg.1 */
#define XSRSSNACH_2    5229 /* Schneckenrueckzug nach Plastifizieren Agg.2 */
#define XSRSVNACH_1    5230 /* Rueckzugsgeschwindigk. nach Plastifizieren Agg.1 */
#define XSRSVNACH_2    5231 /* Rueckzugsgeschwindigk. nach Plastifizieren Agg.2 */
#define XMSSPPUMOFF    5232 /* Offset Sollwert Pumpendruck S.89.1 */ 
#define XMSIPPUMOFF    5233 /* Aktueller Offsetwert Pumpendruck S.89. */
#define XMGENMOD       5234 /* Reg fuer Maschinen-Abgleich-Parameter S.89.1 */
#define IAGGRVOR2      5235 /* SPS-Aggregat Zeitanalyseregister fuer Agg.2-4 */
#define IEINSPR2       5236  
#define IDOS2          5237  
#define IAGGRVOR3      5238  
#define IEINSPR3       5239  
#define IDOS3          5240  
#define IAGGRVOR4      5241  
#define IEINSPR4       5242  
#define IDOS4          5243
/* ---------------- Reg fuer Maschinen-Abgleich: Werkzeugbewegung S.89.1 -- */ 
#define XWZGENMOD      5244 /* Kommandoregister Werkzeugbewegung-Modul */
#define XWSSKOFF       5245 /* Soll-Offset Werkzeug schliessen */
#define XWSSKGAIN      5246 /* Soll-Gain Werkzeug schliessen   */
#define XWOSKOFF       5247 /* Soll-Offset Werkzeug oeffnen */
#define XWOSKGAIN      5248 /* Soll-Gain Werkzeug oeffnen   */
#define XWSIKOFF       5249 /* Ist-Offset Werkzeug schliessen */
#define XWSIKGAIN      5250 /* Ist-Gain Werkzeug schliessen   */
#define XWOIKOFF       5251 /* Ist-Offset Werkzeug oeffnen */
#define XWOIKGAIN      5252 /* Ist-Gain Werkzeug oeffnen   */
/* ---------------- Reg fuer Maschinen-Abgleich: Auswerferbewegung S.89.2 - */ 
#define XAWGENMOD      5253 /* Kommandoregister Auswerferbewegung-Modul */
#define XAWSKVOFF      5254 /* Soll-Offset Auswerfer vor */
#define XAWSKVGAIN     5255 /* Soll-Gain Auswerfer vor   */
#define XAWSKZOFF      5256 /* Soll-Offset Auswerfer zurueck */
#define XAWSKZGAIN     5257 /* Soll-Gain Auswerfer zurueck   */
#define XAWIKVOFF      5258 /* Ist-Offset Auswerfer vor */
#define XAWIKVGAIN     5259 /* Ist-Gain Auswerfer vor   */
#define XAWIKZOFF      5260 /* Ist-Offset Auswerfer zurueck */
#define XAWIKZGAIN     5261 /* Ist-Gain Auswerfer zurueck   */
/* ---------------- Abgleichseite 89.3 ------------------------------------ */
#define XPL1GENMOD     5262 /* Kommandoregister Plastifizieren Agg.1        */
#define XPL2GENMOD     5263 /* Kommandoregister Plastifizieren Agg.2        */
#define XPL3GENMOD     5264 /* Kommandoregister Plastifizieren Agg.3        */
#define XPL4GENMOD     5265 /* Kommandoregister Plastifizieren Agg.4        */
#define XPLSKRAMPE1    5266 /* Soll-Plastifizier-Rampe Agg.1                */
#define XPLSKRAMPE2    5267 /* Soll-Plastifizier-Rampe Agg.2                */
#define XPLSKRAMPE3    5268 /* Soll-Plastifizier-Rampe Agg.3                */
#define XPLSKRAMPE4    5269 /* Soll-Plastifizier-Rampe Agg.4                */
#define XPLSKGEST1     5270 /* Soll-Plastifizieren gestellt Agg.1           */
#define XPLSKGEST2     5271 /* Soll-Plastifizieren gestellt Agg.2           */
#define XPLSKGEST3     5272 /* Soll-Plastifizieren gestellt Agg.3           */
#define XPLSKGEST4     5273 /* Soll-Plastifizieren gestellt Agg.4           */
#define XPLIKARAMP1    5274 /* Ist-Akt-Plastifizier-Rampe Agg.1             */
#define XPLIKARAMP2    5275 /* Ist-Akt-Plastifizier-Rampe Agg.2             */
#define XPLIKARAMP3    5276 /* Ist-Akt-Plastifizier-Rampe Agg.3             */
#define XPLIKARAMP4    5277 /* Ist-Akt-Plastifizier-Rampe Agg.4             */
#define XPLIKDRAMP1    5278 /* Ist-Default-Plastifizier-Rampe Agg.1         */
#define XPLIKDRAMP2    5279 /* Ist-Default-Plastifizier-Rampe Agg.2         */
#define XPLIKDRAMP3    5280 /* Ist-Default-Plastifizier-Rampe Agg.3         */
#define XPLIKDRAMP4    5281 /* Ist-Default-Plastifizier-Rampe Agg.4         */
#define XPLIKAGEST1    5282 /* Ist-Akt-Plastifizier gestellt Agg.1          */
#define XPLIKAGEST2    5283 /* Ist-Akt-Plastifizier gestellt Agg.2          */
#define XPLIKAGEST3    5284 /* Ist-Akt-Plastifizier gestellt Agg.3          */
#define XPLIKAGEST4    5285 /* Ist-Akt-Plastifizier gestellt Agg.4          */
#define XPLIKDGEST1    5286 /* Ist-Default-Plastifizier gestellt Agg.1      */
#define XPLIKDGEST2    5287 /* Ist-Default-Plastifizier gestellt Agg.2      */
#define XPLIKDGEST3    5288 /* Ist-Default-Plastifizier gestellt Agg.3      */
#define XPLIKDGEST4    5289 /* Ist-Default-Plastifizier gestellt Agg.4      */
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
#define XSLSNSCHM      5290 /* Einfahrschmierintervall eingeschaltet */
/* ---------------- Schneckenrueckzug vor/nach (3. und 4. AGG) ------------ */
#define XSRSSVOR_3     5291 /* Schneckenrueckzug vor Plastifizieren Agg.3  */
#define XSRSSVOR_4     5292 /* Schneckenrueckzug vor Plastifizieren Agg.4  */
#define XSRSVVOR_3     5293 /* Rueckzugsgeschwindigk. vor Plastifizieren Agg.3 */
#define XSRSVVOR_4     5294 /* Rueckzugsgeschwindigk. vor Plastifizieren Agg.4 */
#define XSRSSNACH_3    5295 /* Schneckenrueckzug nach Plastifizieren Agg.3 */
#define XSRSSNACH_4    5296 /* Schneckenrueckzug nach Plastifizieren Agg.4 */
#define XSRSVNACH_3    5297 /* Rueckzugsgeschwindigk. nach Plastifizieren Agg.3 */
#define XSRSVNACH_4    5298 /* Rueckzugsgeschwindigk. nach Plastifizieren Agg.4 */
/* ------------------------------------------------------------------ */
#define XZSMNSCHMIER   5299 /* Einfahrschmierintervall Istwert */
/* ------------------------------------------------------------------ */
/* neues Airpress lt. Dr. Jaroschek-> 46 Register 01-07-96 WS  */
#define XAIR_ON        5300          /* Sonderseite 48 -> Airpress    */
#define XDUES_ZU       5301
#define XSTVERZ_D1     5302
#define XSTVERZ_D2     5303
#define XSTVERZ_D3     5304
#define XSTVERZ_D4     5305
#define XSTACT1_D1     5306
#define XSTACT1_D2     5307
#define XSTACT1_D3     5308
#define XSTACT1_D4     5309
#define XSPRES1_D1     5310
#define XSPRES1_D2     5311
#define XSPRES1_D3     5312
#define XSPRES1_D4     5313
#define XSTACT2_D1     5314
#define XSTACT2_D2     5315
#define XSTACT2_D3     5316
#define XSTACT2_D4     5317
#define XSPRES2_D1     5318
#define XSPRES2_D2     5319
#define XSPRES2_D3     5320
#define XSPRES2_D4     5321
#define XSTACT3_D1     5322
#define XSTACT3_D2     5323
#define XSTACT3_D3     5324
#define XSTACT3_D4     5325
#define XSPRES3_D1     5326
#define XSPRES3_D2     5327
#define XSPRES3_D3     5328
#define XSPRES3_D4     5329
#define XSTACT4_D1     5330
#define XSTACT4_D2     5331
#define XSTACT4_D3     5332
#define XSTACT4_D4     5333
#define XSPRES4_D1     5334
#define XSPRES4_D2     5335
#define XSPRES4_D3     5336
#define XSPRES4_D4     5337
#define XSTACT5_D1     5338
#define XSTACT5_D2     5339
#define XSTACT5_D3     5340
#define XSTACT5_D4     5341
#define XSPRES5_D1     5342
#define XSPRES5_D2     5343
#define XSPRES5_D3     5344
#define XSPRES5_D4     5345          /* Sonderseite 48 -> Airpress */    
/* ---------------- Diagnoseseite Schliessdruckaufbau 87.5 ---------------- */
#define XSDRGENMOD     5346 /* Kommandoregister Schliessdruckaufbau         */
#define XSDRSTAUFV     5347 /* Soll-SDR-Aufbauverzoegerungszeit             */
#define XSDRSTAUFB     5348 /* Soll-SDR-Aufbauzeit                          */
#define XSDRITAAUFV    5349 /* Ist-Akt-SDR-Aufbauverzoegerungzeit           */
#define XSDRITDAUFV    5350 /* Ist-Default-SDR-Aufbauverzoegungszeit        */
#define XSDRITAAUFB    5351 /* Ist-Akt-SDR-Aufbauzeit                       */
#define XSDRITDAUFB    5352 /* Ist-Default-SDR-Aufbauzeit                   */
/* ---------------- END Diagnoseseite Schliessdruckaufbau 87.5 ------------ */
#define IFORCEOUTPUT9  5353
#define IFORCEOUTPUT36 5354
#define IFORCEOUTPUT39 5355
#define XSPIKKRAFT2    5356
#define XMSSFOFFSP2    5357
#define XMSIFOFFSP2    5358
/* ------------------------------------------------------------------------ */
#define XIQTMIUNIT     5359
/* ---------------- Seite 69.0 Nadelverschlussduese ----------------------- */
#define XLVSNEIN31     5360
#define XLVSNEIN32     5361
#define XLVSNEIN33     5362
#define XLVSSPKT41     5363
#define XLVSSPKT42     5364
#define XLVSSPKT43     5365
#define XLVSTVERZ41    5366
#define XLVSTVERZ42    5367
#define XLVSTVERZ43    5368
#define XLVSTBLAS41    5369
#define XLVSTBLAS42    5370
#define XLVSTBLAS43    5371
/* ------------------------------------------------------------------------ */
#define XLVSNEIN34     5372
#define XLVSNEIN35     5373
#define XLVSSPKT44     5374
#define XLVSSPKT45     5375
#define XLVSTVERZ44    5376
#define XLVSTVERZ45    5377
#define XLVSTBLAS44    5378
#define XLVSTBLAS45    5379
/* ------------------------------------------------------------------------ */
#define XWSSKOFF2      5380 /* Werkzeug schliessen Nullpunkt Ventil SOLL */   
#define XWSIKOFF2      5381 /* Werkzeug schliessen Nullpunkt Ventil IST  */
#define XWOSKOFF2      5382 /* Werkzeug oeffnen Nullpunkt Ventil SOLL */   
#define XWOIKOFF2      5383 /* Werkzeug oeffnen Nullpunkt Ventil IST  */
/* ------------------------------------------------------------------------ */
#define XAWSPZUR       5384 /* Auswerferdruck zurueck SOLL */
/* ------------------------------------------------------------------------ */
#define XAGGPDUESE1    5385 /* Max. Duesenapressdruck */
#define XWSISHOEHE     5386 /* S.50, Z.3 Werkzeugeinbauhoehe SOLL */
#define XWZSSSKOLB     5387 /* S.50, Z.4 Schliesskolbenweg SOLL */
#define XWZISSKOLB     5388 /* S.50, Z.4 Schliesskolbenweg IST */
/* ------------------------------------------------------------------------ */
#define XPLS_ANZPL1    5389 /* S.40 Anzahl Plastifizierstufen 1.AGG */
#define XPLS_ANZPL2    5390 /* S.40 Anzahl Plastifizierstufen 2.AGG */
#define XPLS_ANZPL3    5391 /* S.40 Anzahl Plastifizierstufen 3.AGG */
#define XPLS_ANZPL4    5392 /* S.40 Anzahl Plastifizierstufen 4.AGG */
#define XPLS_ANZPL5    5393 /* S.40 Anzahl Plastifizierstufen 5.AGG */
/* ------------------------------------------------------------------------ */
#define XIOI_DINP      5394 /* S.66.0 AKT Digitale Eingaenge        */
#define XIOI_DOUT      5395 /* S.66.0 AKT Digitale Ausgaenge        */

/* ---------------- Seite 69.0 Blasluftzeiten in 1/100 sec ---------------- */
#define XLVSTVERZ10    5407
#define XLVSTVERZ20    5408
#define XLVSTVERZ30    5409
#define XLVSTVERZ40    5410
#define XLVSTBLAS10    5411
#define XLVSTBLAS20    5412
#define XLVSTBLAS30    5413
#define XLVSTBLAS40    5414
/* ---------------- END Seite 69.0 Blasluftzeiten in 1/100 sec ------------ */
/* ---------------- Max. hydraulik Druck ---------------------------------- */
#define XSPIPHYDMAX    5415
/* ---------------- Verknuefung Handling mit Kern ------------------------- */
#define XFPKZANDFHK    5416
/* ---------------- Seite 69.0 Blasluftzeiten in 1/100 sec ---------------- */
#define XLVSTVERZ50    5417
#define XLVSTBLAS50    5418
/* ---------------- END Seite 69.0 Blasluftzeiten in 1/100 sec ------------ */
/* ---------------- Max. Schneckenumdrehung ------------------------------- */
#define XSNG_UMDR1     5419
#define XSNG_UMDR2     5420
#define XSNG_UMDR3     5421
#define XSNG_UMDR4     5422
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
#define XDIAGMAXMOD    5423
#define XDIAGRDIND     5424
#define XDIAGWRIND     5425
#define XDIAGSYSTYP    5426
#define XDIAGBUSNR     5427
#define XDIAGMODNR     5428
#define XDIAGINDTAB    5429
/* ------------------------------------------------------------------------ */
#define XFDIAGDAKT     5430
#define XFDIAGDFOR     5431
/* ------------------------------------------------------------------------ */
#define XFDIAGA_A01    5432
#define XFDIAGA_A02    5433
#define XFDIAGA_A03    5434
#define XFDIAGA_A04    5435
#define XFDIAGA_A05    5436
#define XFDIAGA_A06    5437
#define XFDIAGA_A07    5438
#define XFDIAGA_A08    5439
#define XFDIAGA_A09    5440
#define XFDIAGA_A10    5441
#define XFDIAGA_A11    5442
#define XFDIAGA_A12    5443
#define XFDIAGA_A13    5444
#define XFDIAGA_A14    5445
#define XFDIAGA_A15    5446
#define XFDIAGA_A16    5447
/* ------------------------------------------------------------------------ */
#define XFDIAGA_F01    5448
#define XFDIAGA_F02    5449
#define XFDIAGA_F03    5450
#define XFDIAGA_F04    5451
#define XFDIAGA_F05    5452
#define XFDIAGA_F06    5453
#define XFDIAGA_F07    5454
#define XFDIAGA_F08    5455
#define XFDIAGA_F09    5456
#define XFDIAGA_F10    5457
#define XFDIAGA_F11    5458
#define XFDIAGA_F12    5459
#define XFDIAGA_F13    5460
#define XFDIAGA_F14    5461
#define XFDIAGA_F15    5462
#define XFDIAGA_F16    5463
/* ------------------------------------------------------------------------ */
#define XAKT_DVAL1     5464
#define XAKT_DVAL2     5465
#define XAKT_DVAL3     5466
#define XAKT_DVAL4     5467
#define XAKT_DVAL5     5468
#define XAKT_DVAL6     5469
#define XAKT_DVAL7     5470
#define XAKT_DVAL8     5471
#define XAKT_DVAL9     5472
#define XAKT_DVAL10    5473
/* ------------------------------------------------------------------------ */
#define XFOR_DVAL1     5474
#define XFOR_DVAL2     5475
#define XFOR_DVAL3     5476
#define XFOR_DVAL4     5477
#define XFOR_DVAL5     5478
#define XFOR_DVAL6     5479
#define XFOR_DVAL7     5480
#define XFOR_DVAL8     5481
#define XFOR_DVAL9     5482
#define XFOR_DVAL10    5483
/* ------------------------------------------------------------------------ */
#define XAKT1AVAL01    5484
#define XAKT1AVAL02    5485
#define XAKT1AVAL03    5486
#define XAKT1AVAL04    5487
#define XAKT1AVAL05    5488
#define XAKT1AVAL06    5489
#define XAKT1AVAL07    5490
#define XAKT1AVAL08    5491
#define XAKT1AVAL09    5492
#define XAKT1AVAL10    5493
#define XAKT1AVAL11    5494
#define XAKT1AVAL12    5495
#define XAKT1AVAL13    5496
#define XAKT1AVAL14    5497
#define XAKT1AVAL15    5498
#define XAKT1AVAL16    5499
/* ------------------------------------------------------------------------ */
#define XFOR1AVAL01    5500
#define XFOR1AVAL02    5501
#define XFOR1AVAL03    5502
#define XFOR1AVAL04    5503
#define XFOR1AVAL05    5504
#define XFOR1AVAL06    5505
#define XFOR1AVAL07    5506
#define XFOR1AVAL08    5507
#define XFOR1AVAL09    5508
#define XFOR1AVAL10    5509
#define XFOR1AVAL11    5510
#define XFOR1AVAL12    5511
#define XFOR1AVAL13    5512
#define XFOR1AVAL14    5513
#define XFOR1AVAL15    5514
#define XFOR1AVAL16    5515
/* ------------------------------------------------------------------------ */
#define XAKT2AVAL01    5516
#define XAKT2AVAL02    5517
#define XAKT2AVAL03    5518
#define XAKT2AVAL04    5519
#define XAKT2AVAL05    5520
#define XAKT2AVAL06    5521
#define XAKT2AVAL07    5522
#define XAKT2AVAL08    5523
#define XAKT2AVAL09    5524
#define XAKT2AVAL10    5525
#define XAKT2AVAL11    5526
#define XAKT2AVAL12    5527
#define XAKT2AVAL13    5528
#define XAKT2AVAL14    5529
#define XAKT2AVAL15    5530
#define XAKT2AVAL16    5531
/* ------------------------------------------------------------------------ */
#define XFOR2AVAL01    5532
#define XFOR2AVAL02    5533
#define XFOR2AVAL03    5534
#define XFOR2AVAL04    5535
#define XFOR2AVAL05    5536
#define XFOR2AVAL06    5537
#define XFOR2AVAL07    5538
#define XFOR2AVAL08    5539
#define XFOR2AVAL09    5540
#define XFOR2AVAL10    5541
#define XFOR2AVAL11    5542
#define XFOR2AVAL12    5543
#define XFOR2AVAL13    5544
#define XFOR2AVAL14    5545
#define XFOR2AVAL15    5546
#define XFOR2AVAL16    5547
/* ------------------------------------------------------------------------ */
#define XAKT3AVAL01    5548
#define XAKT3AVAL02    5549
#define XAKT3AVAL03    5550
#define XAKT3AVAL04    5551
#define XAKT3AVAL05    5552
#define XAKT3AVAL06    5553
#define XAKT3AVAL07    5554
#define XAKT3AVAL08    5555
#define XAKT3AVAL09    5556
#define XAKT3AVAL10    5557
#define XAKT3AVAL11    5558
#define XAKT3AVAL12    5559
#define XAKT3AVAL13    5560
#define XAKT3AVAL14    5561
#define XAKT3AVAL15    5562
#define XAKT3AVAL16    5563
/* ------------------------------------------------------------------------ */
#define XFOR3AVAL01    5564
#define XFOR3AVAL02    5565
#define XFOR3AVAL03    5566
#define XFOR3AVAL04    5567
#define XFOR3AVAL05    5568
#define XFOR3AVAL06    5569
#define XFOR3AVAL07    5570
#define XFOR3AVAL08    5571
#define XFOR3AVAL09    5572
#define XFOR3AVAL10    5573
#define XFOR3AVAL11    5574
#define XFOR3AVAL12    5575
#define XFOR3AVAL13    5576
#define XFOR3AVAL14    5577
#define XFOR3AVAL15    5578
#define XFOR3AVAL16    5579
/* ------------------------------------------------------------------------ */
/* ---------------- Seite 69.0  6. Blasluftzeit in 1/100 sec ---------------- */
#define XLVSTVERZ60    5580
#define XLVSTBLAS60    5581
/* ---------------- END Seite 69.0   6. Blasluftzeit in 1/100 sec ------------ */
#define XAKT_DVAL11    5582
#define XAKT_DVAL12    5583
#define XAKT_DVAL13    5584
#define XAKT_DVAL14    5585
#define XAKT_DVAL15    5586
/* ------------------------------------------------------------------------ */
#define XAKT4AVAL01    5587
#define XAKT4AVAL02    5588
#define XAKT4AVAL03    5589
#define XAKT4AVAL04    5590
#define XAKT4AVAL05    5591
#define XAKT4AVAL06    5592
#define XAKT4AVAL07    5593
#define XAKT4AVAL08    5594
#define XAKT4AVAL09    5595
#define XAKT4AVAL10    5596
#define XAKT4AVAL11    5597
#define XAKT4AVAL12    5598
#define XAKT4AVAL13    5599
#define XAKT4AVAL14    5600
#define XAKT4AVAL15    5601
#define XAKT4AVAL16    5602
/* ------------------------------------------------------------------------ */
#define XFOR4AVAL01    5603
#define XFOR4AVAL02    5604
#define XFOR4AVAL03    5605
#define XFOR4AVAL04    5606
#define XFOR4AVAL05    5607
#define XFOR4AVAL06    5608
#define XFOR4AVAL07    5609
#define XFOR4AVAL08    5610
#define XFOR4AVAL09    5611
#define XFOR4AVAL10    5612
#define XFOR4AVAL11    5613
#define XFOR4AVAL12    5614
#define XFOR4AVAL13    5615
#define XFOR4AVAL14    5616
#define XFOR4AVAL15    5617
#define XFOR4AVAL16    5618
/* ------------------------------------------------------------------------ */
#define XAKT5AVAL01    5619
#define XAKT5AVAL02    5620
#define XAKT5AVAL03    5621
#define XAKT5AVAL04    5622
#define XAKT5AVAL05    5623
#define XAKT5AVAL06    5624
#define XAKT5AVAL07    5625
#define XAKT5AVAL08    5626
#define XAKT5AVAL09    5627
#define XAKT5AVAL10    5628
#define XAKT5AVAL11    5629
#define XAKT5AVAL12    5630
#define XAKT5AVAL13    5631
#define XAKT5AVAL14    5632
#define XAKT5AVAL15    5633
#define XAKT5AVAL16    5634
/* ------------------------------------------------------------------------ */
#define XFOR5AVAL01    5635
#define XFOR5AVAL02    5636
#define XFOR5AVAL03    5637
#define XFOR5AVAL04    5638
#define XFOR5AVAL05    5639
#define XFOR5AVAL06    5640
#define XFOR5AVAL07    5641
#define XFOR5AVAL08    5642
#define XFOR5AVAL09    5643
#define XFOR5AVAL10    5644
#define XFOR5AVAL11    5645
#define XFOR5AVAL12    5646
#define XFOR5AVAL13    5647
#define XFOR5AVAL14    5648
#define XFOR5AVAL15    5649
#define XFOR5AVAL16    5650
/* ------------------------------------------------------------------------ */
#define XAKT6AVAL01    5651
#define XAKT6AVAL02    5652
#define XAKT6AVAL03    5653
#define XAKT6AVAL04    5654
#define XAKT6AVAL05    5655
#define XAKT6AVAL06    5656
#define XAKT6AVAL07    5657
#define XAKT6AVAL08    5658
#define XAKT6AVAL09    5659
#define XAKT6AVAL10    5660
#define XAKT6AVAL11    5661
#define XAKT6AVAL12    5662
#define XAKT6AVAL13    5663
#define XAKT6AVAL14    5664
#define XAKT6AVAL15    5665
#define XAKT6AVAL16    5666
/* ------------------------------------------------------------------------ */
#define XFOR6AVAL01    5667
#define XFOR6AVAL02    5668
#define XFOR6AVAL03    5669
#define XFOR6AVAL04    5670
#define XFOR6AVAL05    5671
#define XFOR6AVAL06    5672
#define XFOR6AVAL07    5673
#define XFOR6AVAL08    5674
#define XFOR6AVAL09    5675
#define XFOR6AVAL10    5676
#define XFOR6AVAL11    5677
#define XFOR6AVAL12    5678
#define XFOR6AVAL13    5679
#define XFOR6AVAL14    5680
#define XFOR6AVAL15    5681
#define XFOR6AVAL16    5682
/* ------------------------------------------------------------------------ */
#define XAKT7AVAL01    5683
#define XAKT7AVAL02    5684
#define XAKT7AVAL03    5685
#define XAKT7AVAL04    5686
#define XAKT7AVAL05    5687
#define XAKT7AVAL06    5688
#define XAKT7AVAL07    5689
#define XAKT7AVAL08    5690
#define XAKT7AVAL09    5691
#define XAKT7AVAL10    5692
#define XAKT7AVAL11    5693
#define XAKT7AVAL12    5694
#define XAKT7AVAL13    5695
#define XAKT7AVAL14    5696
#define XAKT7AVAL15    5697
#define XAKT7AVAL16    5698
/* ------------------------------------------------------------------------ */
#define XFOR7AVAL01    5699
#define XFOR7AVAL02    5700
#define XFOR7AVAL03    5701
#define XFOR7AVAL04    5702
#define XFOR7AVAL05    5703
#define XFOR7AVAL06    5704
#define XFOR7AVAL07    5705
#define XFOR7AVAL08    5706
#define XFOR7AVAL09    5707
#define XFOR7AVAL10    5708
#define XFOR7AVAL11    5709
#define XFOR7AVAL12    5710
#define XFOR7AVAL13    5711
#define XFOR7AVAL14    5712
#define XFOR7AVAL15    5713
#define XFOR7AVAL16    5714
/* ------------------------------------------------------------------------ */
#define XAKT8AVAL01    5715
#define XAKT8AVAL02    5716
#define XAKT8AVAL03    5717
#define XAKT8AVAL04    5718
#define XAKT8AVAL05    5719
#define XAKT8AVAL06    5720
#define XAKT8AVAL07    5721
#define XAKT8AVAL08    5722
#define XAKT8AVAL09    5723
#define XAKT8AVAL10    5724
#define XAKT8AVAL11    5725
#define XAKT8AVAL12    5726
#define XAKT8AVAL13    5727
#define XAKT8AVAL14    5728
#define XAKT8AVAL15    5729
#define XAKT8AVAL16    5730
/* ------------------------------------------------------------------------ */
#define XFOR8AVAL01    5731
#define XFOR8AVAL02    5732
#define XFOR8AVAL03    5733
#define XFOR8AVAL04    5734
#define XFOR8AVAL05    5735
#define XFOR8AVAL06    5736
#define XFOR8AVAL07    5737
#define XFOR8AVAL08    5738
#define XFOR8AVAL09    5739
#define XFOR8AVAL10    5740
#define XFOR8AVAL11    5741
#define XFOR8AVAL12    5742
#define XFOR8AVAL13    5743
#define XFOR8AVAL14    5744
#define XFOR8AVAL15    5745
#define XFOR8AVAL16    5746
/* ------------------------------------------------------------------------ */
#define XSDIAGDAKT     5747
#define XSDIAGDFOR     5748
/* ------------------------------------------------------------------------ */
#define XSDIAGA_A01    5749
#define XSDIAGA_A02    5750
#define XSDIAGA_A03    5751
#define XSDIAGA_A04    5752
#define XSDIAGA_A05    5753
#define XSDIAGA_A06    5754
#define XSDIAGA_A07    5755
#define XSDIAGA_A08    5756
#define XSDIAGA_A09    5757
#define XSDIAGA_A10    5758
#define XSDIAGA_A11    5759
#define XSDIAGA_A12    5760
#define XSDIAGA_A13    5761
#define XSDIAGA_A14    5762
#define XSDIAGA_A15    5763
#define XSDIAGA_A16    5764
/* ------------------------------------------------------------------------ */
#define XSDIAGA_F01    5765
#define XSDIAGA_F02    5766
#define XSDIAGA_F03    5767
#define XSDIAGA_F04    5768
#define XSDIAGA_F05    5769
#define XSDIAGA_F06    5770
#define XSDIAGA_F07    5771
#define XSDIAGA_F08    5772
#define XSDIAGA_F09    5773
#define XSDIAGA_F10    5774
#define XSDIAGA_F11    5775
#define XSDIAGA_F12    5776
#define XSDIAGA_F13    5777
#define XSDIAGA_F14    5778
#define XSDIAGA_F15    5779
#define XSDIAGA_F16    5780
/* ---------------- Wegmess-Parameter, Seite 89.0 ------------------------- */
#define XMSSSK2_1      5781  
#define XMSSSK2_2      5782  
#define XMSSSK2_3      5783  
#define XMSSSK2_4      5784  
#define XMSSSK2_5      5785  
#define XMSSSK2_6      5786  
#define XMSSSK2_7      5787  
#define XMSSSK2_8      5788  
#define XMSSSOFF4_2    5789
#define XMSSSOFF5      5790
#define XMSSSOFF6      5791
#define XMSSSOFF7      5792
#define XMSSSOFF8      5793
#define XMSISK2_1      5794  
#define XMSISK2_2      5795  
#define XMSISK2_3      5796  
#define XMSISK2_4      5797  
#define XMSISK2_5      5798  
#define XMSISK2_6      5799  
#define XMSISK2_7      5800  
#define XMSISK2_8      5801  
#define XMSISOFF4_2    5802
#define XMSISOFF5      5803
#define XMSISOFF6      5804
#define XMSISOFF7      5805
#define XMSISOFF8      5806
#define XMSISAKT4_2    5807
#define XMSISAKT5      5808
#define XMSISAKT6      5809
#define XMSISAKT7      5810
#define XMSISAKT8      5811

/* ---------------- Erweiterung auf 4 Plastifizierstufen ------------------ */
#define XSSUM12        5820
#define XSSUM22        5821
#define XSSUM32        5822
#define XSSUM42        5823
/* ------------------------------------------------------------------------ */
#define XSSUM13        5824
#define XSSUM23        5825
#define XSSUM33        5826
#define XSSUM43        5827
/* ------------------------------------------------------------------------ */
#define XSWPL13        5828
#define XSWPL23        5829
#define XSWPL33        5830
#define XSWPL43        5831
/* ------------------------------------------------------------------------ */
#define XSWPL14        5832
#define XSWPL24        5833
#define XSWPL34        5834
#define XSWPL44        5835
/* ------------------------------------------------------------------------ */
#define XSPST13        5836
#define XSPST23        5837
#define XSPST33        5838
#define XSPST43        5839
/* ------------------------------------------------------------------------ */
#define XSPST14        5840
#define XSPST24        5841
#define XSPST34        5842
#define XSPST44        5843
/* ------------------------------------------------------------------------ */
/* ---------------- Register fuer hydr./spec. Umschaltung (10-12 Spritzstufen)  */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define XSPPH1A        5844 /* Soll Einspritzdruck Agg1 Stufe 10*/
#define XSPPH1B        5845 /* Soll Einspritzdruck Agg1 Stufe 11*/
#define XSPPH1C        5846 /* Soll Einspritzdruck Agg1 Stufe 12*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XXPPH1A        5847 /* Ist  Einspritzdruck Agg1 Stufe 10*/
#define XXPPH1B        5848 /* Ist  Einspritzdruck Agg1 Stufe 11*/
#define XXPPH1C        5849 /* Ist  Einspritzdruck Agg1 Stufe 12*/
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define XSVPH1A        5850 /* Soll Geschwindigk. mm/s Agg1 Stufe10 */
#define XSVPH1B        5851 /* Soll Geschwindigk. mm/s Agg1 Stufe11 */
#define XSVPH1C        5852 /* Soll Geschwindigk. mm/s Agg1 Stufe12 */
/* ---------------- Soll Einspritzzeit ------------------------------------ */
#define XSTPH1A        5853 /* Soll Einspritzzeit Agg1 Stufe10 */
#define XSTPH1B        5854 /* Soll Einspritzzeit Agg1 Stufe11 */
#define XSTPH1C        5855 /* Soll Einspritzzeit Agg1 Stufe12 */
/* ---------------- Ist Einspritzzeit ------------------------------------- */
#define XXTPH1A        5856 /* Ist  Einspritzzeit Agg1 Stufe10 */
#define XXTPH1B        5857 /* Ist  Einspritzzeit Agg1 Stufe11 */
#define XXTPH1C        5858 /* Ist  Einspritzzeit Agg1 Stufe12 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define XSPUM1A        5859 /* Soll Umschaltdruck Agg1 Stufe 10*/ 
#define XSPUM1B        5860 /* Soll Umschaltdruck Agg1 Stufe 11*/ 
#define XSPUM1C        5861 /* Soll Umschaltdruck Agg1 Stufe 12*/ 
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define XSSPH1A        5862 /* Soll Umschaltpkt Agg1 Stufe10 */
#define XSSPH1B        5863 /* Soll Umschaltpkt Agg1 Stufe11 */
#define XSSPH1C        5864 /* Soll Umschaltpkt Agg1 Stufe12 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XXSPH1A        5865 /* Ist  Umschaltpkt Agg1 Stufe10 */
#define XXSPH1B        5866 /* Ist  Umschaltpkt Agg1 Stufe11 */
#define XXSPH1C        5867 /* Ist  Umschaltpkt Agg1 Stufe12 */
/* ---------------- Register fuer 7-12 Spritzstufen 2.Spritzeinheit */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define XSPPH27        5868 /* Soll Einspritzdruck Agg1 Stufe 7*/
#define XSPPH28        5869 /* Soll Einspritzdruck Agg1 Stufe 8*/
#define XSPPH29        5870 /* Soll Einspritzdruck Agg1 Stufe 9*/
#define XSPPH2A        5871 /* Soll Einspritzdruck Agg1 Stufe 10*/
#define XSPPH2B        5872 /* Soll Einspritzdruck Agg1 Stufe 11*/
#define XSPPH2C        5873 /* Soll Einspritzdruck Agg1 Stufe 12*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XXPPH27        5874 /* Ist  Einspritzdruck Agg1 Stufe 7*/
#define XXPPH28        5875 /* Ist  Einspritzdruck Agg1 Stufe 8*/
#define XXPPH29        5876 /* Ist  Einspritzdruck Agg1 Stufe 9*/
#define XXPPH2A        5877 /* Ist  Einspritzdruck Agg1 Stufe 10*/
#define XXPPH2B        5878 /* Ist  Einspritzdruck Agg1 Stufe 11*/
#define XXPPH2C        5879 /* Ist  Einspritzdruck Agg1 Stufe 12*/
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define XSVPH27        5880 /* Soll Geschwindigk. mm/s Agg1 Stufe7 */
#define XSVPH28        5881 /* Soll Geschwindigk. mm/s Agg1 Stufe8 */
#define XSVPH29        5882 /* Soll Geschwindigk. mm/s Agg1 Stufe9 */
#define XSVPH2A        5883 /* Soll Geschwindigk. mm/s Agg1 Stufe10 */
#define XSVPH2B        5884 /* Soll Geschwindigk. mm/s Agg1 Stufe11 */
#define XSVPH2C        5885 /* Soll Geschwindigk. mm/s Agg1 Stufe12 */
/* ---------------- Soll Einspritzzeit ------------------------------------ */
#define XSTPH27        5886 /* Soll Einspritzzeit Agg1 Stufe7 */
#define XSTPH28        5887 /* Soll Einspritzzeit Agg1 Stufe8 */
#define XSTPH29        5888 /* Soll Einspritzzeit Agg1 Stufe9 */
#define XSTPH2A        5889 /* Soll Einspritzzeit Agg1 Stufe10 */
#define XSTPH2B        5890 /* Soll Einspritzzeit Agg1 Stufe11 */
#define XSTPH2C        5891 /* Soll Einspritzzeit Agg1 Stufe12 */
/* ---------------- Ist Einspritzzeit ------------------------------------- */
#define XXTPH27        5892 /* Ist  Einspritzzeit Agg1 Stufe7 */
#define XXTPH28        5893 /* Ist  Einspritzzeit Agg1 Stufe8 */
#define XXTPH29        5894 /* Ist  Einspritzzeit Agg1 Stufe9 */
#define XXTPH2A        5895 /* Ist  Einspritzzeit Agg1 Stufe10 */
#define XXTPH2B        5896 /* Ist  Einspritzzeit Agg1 Stufe11 */
#define XXTPH2C        5897 /* Ist  Einspritzzeit Agg1 Stufe12 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define XSPUM26        5898 /* Soll Umschaltdruck Agg1 Stufe 6*/ 
#define XSPUM27        5899 /* Soll Umschaltdruck Agg1 Stufe 7*/ 
#define XSPUM28        5900 /* Soll Umschaltdruck Agg1 Stufe 8*/ 
#define XSPUM29        5901 /* Soll Umschaltdruck Agg1 Stufe 9*/ 
#define XSPUM2A        5902 /* Soll Umschaltdruck Agg1 Stufe 10*/ 
#define XSPUM2B        5903 /* Soll Umschaltdruck Agg1 Stufe 11*/ 
#define XSPUM2C        5904 /* Soll Umschaltdruck Agg1 Stufe 12*/ 
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define XSSPH26        5905 /* Soll Umschaltpkt Agg1 Stufe6 */
#define XSSPH27        5906 /* Soll Umschaltpkt Agg1 Stufe7 */
#define XSSPH28        5907 /* Soll Umschaltpkt Agg1 Stufe8 */
#define XSSPH29        5908 /* Soll Umschaltpkt Agg1 Stufe9 */
#define XSSPH2A        5909 /* Soll Umschaltpkt Agg1 Stufe10 */
#define XSSPH2B        5910 /* Soll Umschaltpkt Agg1 Stufe11 */
#define XSSPH2C        5911 /* Soll Umschaltpkt Agg1 Stufe12 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XXSPH26        5912 /* Ist  Umschaltpkt Agg1 Stufe6 */
#define XXSPH27        5913 /* Ist  Umschaltpkt Agg1 Stufe7 */
#define XXSPH28        5914 /* Ist  Umschaltpkt Agg1 Stufe8 */
#define XXSPH29        5915 /* Ist  Umschaltpkt Agg1 Stufe9 */
#define XXSPH2A        5916 /* Ist  Umschaltpkt Agg1 Stufe10 */
#define XXSPH2B        5917 /* Ist  Umschaltpkt Agg1 Stufe11 */
#define XXSPH2C        5918 /* Ist  Umschaltpkt Agg1 Stufe12 */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ---------------- Kommunikationsreg. fuer Master/Slave PLC -------------- */
#define XIQTSPSTXT2    5927
#define XHZ_MSTOSL     5928
#define XHZ_SLTOMS     5929
#define XHZ2MSTOSL     5930
#define XHZ2SLTOMS     5931
/* ---------------- Heizung Kanalbenennung fuer 2.SPS --------------------- */
#define XHZ2CURREG     5932
#define XHZ2TEMPMOD    5934
#define XHZ2TEMPKAN    5935
#define XHZ2HEIZMOD    5936
#define XHZ2HEIZKAN    5937
#define XHZ2KUELMOD    5938
#define XHZ2KUELKAN    5939
/* ------------------------ Anfahrseite 32.0 fuer 2.SPS ------------------- */
#define XHZ2AX0EC      5940
#define XHZ2AX0ED      5941
#define XHZ2AX0EE      5942
#define XHZ2TABSWKZ    5943
/* ---------------- Heizungsoptimierungsregister 2.SPS -------------------- */
#define XHES2BLOPT     5944
#define XHES2BLOPT2    5945
/* ------------------------------------------------------------------------ */
/* Einsprunge fur die 2.Heizungs-SPS-Fehlermeldungsregister.                 */
/* Es gibt drei Einsprunge fur Fuhlerbruch, enge und weite Toleranzregister. */
/* Alle drei werden als eindimensionale Registertabelle behandelt und zeigen */
/* auf das jeweils erste Register. Die Fehlerregister mussen also in der     */
/* IscosRegTab hintereinander stehen.                                        */
/* ---------------- Register fuer 2.SPS Heizungs-Istwerte ----------------- */
#define XHZ2XKSR01     5946
#define XHZ2XKSR02     5947
#define XHZ2XKSR03     5948
#define XHZ2XKSR04     5949
#define XHZ2XKSR05     5950
#define XHZ2XKSR06     5951
#define XHZ2XKSR07     5952
#define XHZ2XKSR08     5953
#define XHZ2XKSR09     5954
#define XHZ2XKSR10     5955
#define XHZ2XKSR11     5956
#define XHZ2XKSR12     5957
#define XHZ2XKSR13     5958
#define XHZ2XKSR14     5959
#define XHZ2XKSR15     5960
#define XHZ2XKSR16     5961
#define XHZ2XKER01     5962
#define XHZ2XKER02     5963
#define XHZ2XKER03     5964
#define XHZ2XKER04     5965
#define XHZ2XKER05     5966
#define XHZ2XKER06     5967
#define XHZ2XKER07     5968
#define XHZ2XKER08     5969
#define XHZ2XKER09     5970
#define XHZ2XKER10     5971
#define XHZ2XKER11     5972
#define XHZ2XKER12     5973
#define XHZ2XKER13     5974
#define XHZ2XKER14     5975
#define XHZ2XKER15     5976
#define XHZ2XKER16     5977
#define XHZ2XKIR01     5978
#define XHZ2XKIR02     5979
#define XHZ2XKIR03     5980
#define XHZ2XKIR04     5981
#define XHZ2XKIR05     5982
#define XHZ2XKIR06     5983
#define XHZ2XKIR07     5984
#define XHZ2XKIR08     5985
#define XHZ2XKIR09     5986
#define XHZ2XKIR10     5987
#define XHZ2XKIR11     5988
#define XHZ2XKIR12     5989
#define XHZ2XKIR13     5990
#define XHZ2XKIR14     5991
#define XHZ2XKIR15     5992
#define XHZ2XKIR16     5993
#define XHZ2XKGWPW     5994
#define XHZ2XKGWPE     5995
#define XHZ2XKGWNE     5996
#define XHZ2XKGWNW     5997
#define XHZ2TKXTHB     5998
#define XHZ2XKBLNR     5999
/* Einsprunge fur die Heizungs-Fehlermeldungsregister.                       */
/* Es gibt drei Einsprunge fur Fuhlerbruch, enge und weite Toleranzregister. */
/* Alle drei werden als eindimensionale Registertabelle behandelt und zeigen */
/* auf das jeweils erste Register. Die Fehlerregister mussen also in der     */
/* IscosRegTab hintereinander stehen.                                        */
/* ---------------- Register fuer Heizungs-Istwerte ------------------------ */
#define XXKSR01        6000
#define XXKSR02        6001
#define XXKSR03        6002
#define XXKSR04        6003
#define XXKSR05        6004
#define XXKSR06        6005
#define XXKSR07        6006
#define XXKSR08        6007
#define XXKSR09        6008
#define XXKSR10        6009
#define XXKSR11        6010
#define XXKSR12        6011
#define XXKSR13        6012
#define XXKSR14        6013
#define XXKSR15        6014
#define XXKSR16        6015
#define XXKER01        6016
#define XXKER02        6017
#define XXKER03        6018
#define XXKER04        6019
#define XXKER05        6020
#define XXKER06        6021
#define XXKER07        6022
#define XXKER08        6023
#define XXKER09        6024
#define XXKER10        6025
#define XXKER11        6026
#define XXKER12        6027
#define XXKER13        6028
#define XXKER14        6029
#define XXKER15        6030
#define XXKER16        6031
#define XXKIR01        6032
#define XXKIR02        6033
#define XXKIR03        6034
#define XXKIR04        6035
#define XXKIR05        6036
#define XXKIR06        6037
#define XXKIR07        6038
#define XXKIR08        6039
#define XXKIR09        6040
#define XXKIR10        6041
#define XXKIR11        6042
#define XXKIR12        6043
#define XXKIR13        6044
#define XXKIR14        6045
#define XXKIR15        6046
#define XXKIR16        6047
#define XXKGWPW        6048
#define XXKGWPE        6049
#define XXKGWNE        6050
#define XXKGWNW        6051
#define XTKXTHB        6052
#define XXKBLNR        6053

/* ---------------- Register fuer 2.SPS Heizungs-Sollwerte ---------------- */
#define XHZ2SNREGL     6070
#define XHZ2SNGRUP     6071
#define XHZ2SKTEMP     6072
#define XHZ2SKGWNW     6073
#define XHZ2SKGWNE     6074
#define XHZ2SKGWPW     6075
#define XHZ2SKGWPE     6076
#define XHZ2SNMCW      6077
#define XHZ2SNXPH      6078
#define XHZ2SNXPK      6079
#define XHZ2SNTN       6080
#define XHZ2SNTV       6081
#define XHZ2SNTOH      6082
#define XHZ2SNTOK      6083
#define XHZ2SNSHY      6084
#define XHZ2SNY        6085
#define XHZ2SNYMIN     6086
#define XHZ2SNYMAX     6087
#define XHZ2SNTM       6088
#define XHZ2SNSPDS     6089
#define XHZ2SNONOF     6090
#define XHZ2SNSSOL     6091
#define XHZ2SNSTEL     6092
#define XHZ2SNTHTY     6093
#define XHZ2SNMESS     6094
#define XHZ2SNFUNC     6095
#define XHZ2SNLOOP     6096
#define XHZ2SNCNTY     6097

/* ---------------- Register fuer Heizungs-Sollwerte ---------------------- */
#define XSNREGL        6100
#define XSNGRUP        6101
#define XSKTEMP        6102
#define XSKGWNW        6103
#define XSKGWNE        6104
#define XSKGWPW        6105
#define XSKGWPE        6106
#define XSNMCW         6107
#define XSNXPH         6108
#define XSNXPK         6109
#define XSNTN          6110
#define XSNTV          6111
#define XSNTOH         6112
#define XSNTOK         6113
#define XSNSHY         6114
#define XSNY           6115
#define XSNYMIN        6116
#define XSNYMAX        6117
#define XSNTM          6118
#define XSNSPDS        6119
#define XSNONOF        6120
#define XSNSSOL        6121
#define XSNSTEL        6122
#define XSNTHTY        6123
#define XSNMESS        6124
#define XSNFUNC        6125
#define XSNLOOP        6126
#define XSNCNTY        6127


/* ---------------- Register fuer hydr./spec. Umschaltung (9 Spritzstufen)  */
/* ---------------- Soll Einspritzdruck ----------------------------------- */
#define XSPPH17        6150 /* Soll Einspritzdruck Agg1 Stufe 7*/
#define XSPPH18        6151 /* Soll Einspritzdruck Agg1 Stufe 8*/
#define XSPPH19        6152 /* Soll Einspritzdruck Agg1 Stufe 9*/
/* ---------------- IST Einspritzdruck ------------------------------------ */
#define XXPPH17        6153 /* Ist  Einspritzdruck Agg1 Stufe 7*/
#define XXPPH18        6154 /* Ist  Einspritzdruck Agg1 Stufe 8*/
#define XXPPH19        6155 /* Ist  Einspritzdruck Agg1 Stufe 9*/
/* ---------------- Einspritzegeschwindigkeiten --------------------------- */
#define XSVPH17        6156 /* Soll Geschwindigk. mm/s Agg1 Stufe7 */
#define XSVPH18        6157 /* Soll Geschwindigk. mm/s Agg1 Stufe8 */
#define XSVPH19        6158 /* Soll Geschwindigk. mm/s Agg1 Stufe9 */
/* ---------------- Soll Einspritzzeit ------------------------------------ */
#define XSTPH17        6159 /* Soll Einspritzzeit Agg1 Stufe7 */
#define XSTPH18        6160 /* Soll Einspritzzeit Agg1 Stufe8 */
#define XSTPH19        6161 /* Soll Einspritzzeit Agg1 Stufe9 */
/* ---------------- Ist Einspritzzeit ------------------------------------- */
#define XXTPH17        6162 /* Ist  Einspritzzeit Agg1 Stufe7 */
#define XXTPH18        6163 /* Ist  Einspritzzeit Agg1 Stufe8 */
#define XXTPH19        6164 /* Ist  Einspritzzeit Agg1 Stufe9 */
/* ---------------- Soll Umschaltdruck ------------------------------------ */
#define XSPUM16        6165 /* Soll Umschaltdruck Agg1 Stufe 6*/ 
#define XSPUM17        6166 /* Soll Umschaltdruck Agg1 Stufe 7*/ 
#define XSPUM18        6167 /* Soll Umschaltdruck Agg1 Stufe 8*/ 
#define XSPUM19        6168 /* Soll Umschaltdruck Agg1 Stufe 9*/ 
/* ---------------- Soll Umschaltpunkt ------------------------------------ */
#define XSSPH16        6169 /* Soll Umschaltpkt Agg1 Stufe6 */
#define XSSPH17        6170 /* Soll Umschaltpkt Agg1 Stufe7 */
#define XSSPH18        6171 /* Soll Umschaltpkt Agg1 Stufe8 */
#define XSSPH19        6172 /* Soll Umschaltpkt Agg1 Stufe9 */
/* ---------------- Ist Umschaltpunkt ------------------------------------- */
#define XXSPH16        6173 /* Ist  Umschaltpkt Agg1 Stufe6 */
#define XXSPH17        6174 /* Ist  Umschaltpkt Agg1 Stufe7 */
#define XXSPH18        6175 /* Ist  Umschaltpkt Agg1 Stufe8 */
#define XXSPH19        6176 /* Ist  Umschaltpkt Agg1 Stufe9 */
/* ------------------------------------------------------------------------ */
/* ---------------- E300 -------------------------------------------------- */
#define MSSPINZ        6177 /* Ist  Zyklen seit letzter Schmierung S15 z2*/
#define MSSPINAN       6178 /* Soll Anzahl geschmierter Nippel S15 z3*/
#define MSGELEZ        6179 /* Ist  Zyklen seit letzter Schmierung S15 z6*/
#define MSGELEAN       6180 /* Soll Anzahl geschmierter Nippel S15 z7*/
#define DUABHEBZ       6181 /* Soll Duesenabhebezeit S49 z10*/
#define AWKRAFTE       6182 /* Soll Auswerferkraft S52 z19*/
/* ------------------------------------------------------------------------ */
#define XWFMPRANGE1    6183 /* Rangeumschaltung fuer Kistler SmartAmp 5049A AGG1 */
#define XWFMPRANGE2    6184 /* Rangeumschaltung fuer Kistler SmartAmp 5049A AGG2 */
#define XWFMPRANGE3    6185 /* Rangeumschaltung fuer Kistler SmartAmp 5049A AGG3 */
#define XWFMPRANGE4    6186 /* Rangeumschaltung fuer Kistler SmartAmp 5049A AGG4 */
#define XWFM_ASWPT1    6187 /* Automatische Umschaltpunkterkennung fuer Kistler SmartAmp 5049A AGG1 */
#define XWFM_ASWPT2    6188 /* Automatische Umschaltpunkterkennung fuer Kistler SmartAmp 5049A AGG2 */
#define XWFM_ASWPT3    6189 /* Automatische Umschaltpunkterkennung fuer Kistler SmartAmp 5049A AGG3 */
#define XWFM_ASWPT4    6190 /* Automatische Umschaltpunkterkennung fuer Kistler SmartAmp 5049A AGG4 */
/* ------------------------------------------------------------------------ */
#define XSBS_BETR      6191 /* Betriebsart Ein/Ausschrauben */
#define XSBS_BEIN      6192 /* Betriebsart Einschrauben */
#define XSBS_BAUS      6193 /* Betriebsart Auschrauben */
#define XSBSGWINK      6194 /* Schraubwinkel Soll */
#define XSBIGWINK      6195 /* Schraubwinkel Ist */
#define XSBSSAWEGP     6196 /* Ausschrauben bei Werkzeugposition */
#define XSBSGEIN1      6197 /* Winkel Ein1 */
#define XSBSGEIN2      6198 /* Winkel Ein2 */
#define XSBSGTEILW     6199 /* Winkel teilw. */
#define XSBSGAUS1      6200 /* Winkel Aus1 */
#define XSBSGAUS2      6201 /* Winkel Aus2 */
#define XSBSVEIN1      6202 /* Geschwindigkeit Ein1 */
#define XSBSVEIN2      6203 /* Geschwindigkeit Ein2 */
#define XSBSVTEILW     6204 /* Geschwindigkeit teilw. */
#define XSBSVAUS1      6205 /* Geschwindigkeit Aus1 */
#define XSBSVAUS2      6206 /* Geschwindigkeit Aus2 */
#define XSBSPEIN1      6207 /* Druck Ein1 */
#define XSBSPEIN2      6208 /* Druck Ein2 */
#define XSBSPTEILW     6209 /* Druck teilw. */
#define XSBSPAUS1      6210 /* Druck Aus1 */
#define XSBSPAUS2      6211 /* Druck Aus2 */
#define XSBSTUEIN1     6212 /* Ueberw.zeit Ein1 */
#define XSBSTUEIN2     6213 /* Ueberw.zeit Ein2 */
#define XSBSTUTEILW    6214 /* Ueberw.zeit teilw. */
#define XSBSTUAUS1     6215 /* Ueberw.zeit Aus1 */
#define XSBSTUAUS2     6216 /* Ueberw.zeit Aus2 */
#define XSBITUBERW     6217 /* Ueberw.zeit Ist */
/* ----------------- Seite 89.1 Maschinenabgleich von Ventilen ------------ */
#define XMAI_OFFS1     6218 /* Maschinenabgleich Ventiloffset 1 */
#define XMAI_OFFS2     6219 /* Maschinenabgleich Ventiloffset 2 */
#define XMAI_OFFS3     6220 /* Maschinenabgleich Ventiloffset 3 */
#define XMAI_OFFS4     6221 /* Maschinenabgleich Ventiloffset 4 */
#define XMAI_OFFS5     6222 /* Maschinenabgleich Ventiloffset 5 */
#define XMAI_OFFS6     6223 /* Maschinenabgleich Ventiloffset 6 */
#define XMAI_OFFS7     6224 /* Maschinenabgleich Ventiloffset 7 */
#define XMAI_OFFS8     6225 /* Maschinenabgleich Ventiloffset 8 */
#define XMAI_OFFS9     6226 /* Maschinenabgleich Ventiloffset 9 */
#define XMAI_OFFS10    6227 /* Maschinenabgleich Ventiloffset 10 */
#define XMAI_VERS1     6228 /* Maschinenabgleich Ventilverstaerkung 1 */
#define XMAI_VERS2     6229 /* Maschinenabgleich Ventilverstaerkung 2 */
#define XMAI_VERS3     6230 /* Maschinenabgleich Ventilverstaerkung 3 */
#define XMAI_VERS4     6231 /* Maschinenabgleich Ventilverstaerkung 4 */
#define XMAI_VERS5     6232 /* Maschinenabgleich Ventilverstaerkung 5 */
#define XMAI_VERS6     6233 /* Maschinenabgleich Ventilverstaerkung 6 */
#define XMAI_VERS7     6234 /* Maschinenabgleich Ventilverstaerkung 7 */
#define XMAI_VERS8     6235 /* Maschinenabgleich Ventilverstaerkung 8 */
#define XMAI_VERS9     6236 /* Maschinenabgleich Ventilverstaerkung 9 */
#define XMAI_VERS10    6237 /* Maschinenabgleich Ventilverstaerkung 10 */
#define XVENTIL_MOD    6238 /* SOLL Maschinenabgleich Ventiloffset 1 */
#define XMAS_VENIND    6239 /* SOLL Maschinenabgleich Ventiloffset 1 */
#define XMAS_OFFS1     6240 /* SOLL Maschinenabgleich Ventiloffset 1 */
#define XMAS_OFFS2     6241 /* SOLL Maschinenabgleich Ventiloffset 2 */
#define XMAS_VERS1     6242 /* SOLL Maschinenabgleich Ventilverstaerkung 8 */
#define XMAS_VERS2     6243 /* SOLL Maschinenabgleich Ventilverstaerkung 9 */
/* ------------------------------------------------------------------------ */
#define XMAI_OFFS11    6244 /* Maschinenabgleich Ventiloffset 11 */
#define XMAI_OFFS12    6245 /* Maschinenabgleich Ventiloffset 12 */
#define XMAI_VERS11    6246 /* Maschinenabgleich Ventilverstaerkung 11 */
#define XMAI_VERS12    6247 /* Maschinenabgleich Ventilverstaerkung 12 */
/* ------------------------------------------------------------------------ */
#define XMSSSOFF11     6248
#define XMSSSOFF21     6249
#define XMSSSOFF31     6250
#define XMSISOFF11     6251
#define XMSISOFF12     6252
#define XMSISOFF21     6253
#define XMSISOFF22     6254
#define XMSISOFF31     6255
#define XMSISOFF32     6256
#define XMSSNPNR       6257
#define XMSINSTA       6258
#define XMSINMLD       6259
#define XWKZSS_VERS    6260 /* Werkzeughoehenverstellung SOLL */
#define XWKZIS_VERS    6261 /* Werkzeughoehenverstellung IST */
/* ---------------- Drivestatusseite fuer Evolution Seite 17.3 ------------ */
#define XDIAGM170      6262
#define XDIAGM171      6263
#define XDIAGM172      6264
#define XDIAGM173      6265
#define XDIAGM174      6266
#define XDIAGM175      6267
#define XDIAGM176      6268
#define XDIAGM177      6269
#define XDIAGM178      6270
#define XDIAGM179      6271
#define XDIAGM17A      6272
#define XDIAGM17B      6273
#define XDIAGM17C      6274
#define XDIAGM17D      6275
#define XDIAGM17E      6276
#define XDIAGM17F      6277
#define XDIAGM180      6278
#define XDIAGM181      6279
#define XDIAGM182      6280
#define XDIAGM183      6281
#define XDIAGM184      6282
#define XDIAGM185      6283
#define XDIAGM186      6284
#define XDIAGM187      6285
#define XDIAGM188      6286
#define XDIAGM189      6287
#define XDIAGM18A      6288
#define XDIAGM18B      6289
#define XDIAGM18C      6290
#define XDIAGM18D      6291
#define XDIAGM18E      6292
#define XDIAGM18F      6293

/* ------------------------------------------------------------------------ */
#define XIQTSSACT      6300 /* Aktuelle IQT-Schluesselschalterpostion */
#define XDRGPUEBERS    6301 /* Druckuebersetzer Wert */
/* ----------------- Spritzeinheit mit Wegmesssystem ---------------------- */
#define XSESSVOR11     6302 /* Wegpunkt vor Aggregatbewegung 1        */
#define XSESSVOR12     6303 /* Wegpunkt vor Aggregatbewegung 2        */
#define XSESSVOR13     6304 /* Wegpunkt vor Aggregatbewegung 3        */
#define XSESSVOR14     6305 /* Wegpunkt vor Aggregatbewegung 4        */
#define XSESSVOR15     6306 /* Wegpunkt vor Aggregatbewegung 5        */
#define XSESSVOR16     6307 /* Wegpunkt vor Aggregatbewegung 6        */
#define XSESSZUR11     6308 /* Wegpunkt zurueck Aggregatbewegung 1    */
#define XSESSZUR12     6309 /* Wegpunkt zurueck Aggregatbewegung 2    */
#define XSESSZUR13     6310 /* Wegpunkt zurueck Aggregatbewegung 3    */
#define XSESSZUR14     6311 /* Wegpunkt zurueck Aggregatbewegung 4    */
#define XSESSZUR15     6312 /* Wegpunkt zurueck Aggregatbewegung 5    */
#define XSESSZUR16     6313 /* Wegpunkt zurueck Aggregatbewegung 5    */
#define XSESSNLPKT1    6314 /* NULLPUNKT SOLL Aggregat1               */
#define XSESSNLPKT2    6315 /* NULLPUNKT SOLL Aggregat2               */
#define XSESSNLPKT3    6316 /* NULLPUNKT SOLL Aggregat3               */
#define XSESSNLPKT4    6317 /* NULLPUNKT SOLL Aggregat4               */
#define XSESSNLPKT5    6318 /* NULLPUNKT SOLL Aggregat5               */
#define XSESSNLPKT6    6319 /* NULLPUNKT SOLL Aggregat6               */
#define XSEISNLPKT1    6320 /* NULLPUNKT  IST Aggregat1               */
#define XSEISNLPKT2    6321 /* NULLPUNKT  IST Aggregat2               */
#define XSEISNLPKT3    6322 /* NULLPUNKT  IST Aggregat3               */
#define XSEISNLPKT4    6323 /* NULLPUNKT  IST Aggregat4               */
#define XSEISNLPKT5    6324 /* NULLPUNKT  IST Aggregat5               */
#define XSEISNLPKT6    6325 /* NULLPUNKT  IST Aggregat6               */
/* ----------------- Spritzeinheit mit Wegmesssystem ---------------------- */
#define XAWSN1ZUR      6326 /* Auswerferplattensicherung              */
/* ----------------- Register fuer SPS-Tasten ----------------------- */
#define IKBA0INPUT     6327 /*  */  
#define IKBA1INPUT     6328 /*  */  
#define IKBA2INPUT     6329 /*  */
#define IKBA3INPUT     6330 /*  */  
/* -------- Register fuer 2. Werkzeugsicherungsphase  S. 52.0 ------- */
#define XSSFZU5        6331 /* Startpunkt2 */  
#define XSPNIDR2       6332 /* Druck2 */  
#define XSTNIDR2       6333 /* Ueberwachungszeit2 Soll*/  
#define XXTNIDR2       6334 /* Ueberwachungszeit2 Ist */  
/* -------- Register fuer Produktionsstart S. 40.2 ------------------ */
#define XXSN_ANFA      6335 /* Anzahl Anfahrzyklen */
#define XSSDOS1A       6336 /* Plastivizierweg */
#define XSPPH11A       6337 /* Einspritzdruck p1 */
#define XSTPH11A       6338 /* Einspritzzeit t1 */
#define XSPPH12A       6339 /* Einspritzdruck p2 */
#define XSTPH12A       6340 /* Einspritzzeit t2 */
#define XSPPH13A       6341 /* Einspritzdruck p3 */
#define XSTPH13A       6342 /* Einspritzzeit t3 */
#define XXSN_ANF2A     6343 /* Anzahl Anfahrzyklen Wkz-Druck */
#define XSPNIDRA       6344 /* Druck werkzeugsicherung1 */  
#define XSPNIDR2A      6345 /* Druck werkzeugsicherung2 */  
#define XSVPH11A       6346 /* Einspritzgeschw. v1 */ 
#define XSVPH12A       6347 /* Einspritzgeschw. v2 */
#define XSVPH13A       6348 /* Einspritzgeschw. v3 */ 
#define XSVPH14A       6349 /* Einspritzgeschw. v4 */ 
#define XSVPH15A       6350 /* Einspritzgeschw. v5 */
#define XSVPH16A       6351 /* Einspritzgeschw. v6 */ 
#define XSVPH17A       6352 /* Einspritzgeschw. v7 */ 
#define XSVPH18A       6353 /* Einspritzgeschw. v8 */
#define XSVPH19A       6354 /* Einspritzgeschw. v9 */ 

#define XSSPH11A       6360 /* Umschaltpunkt s1 */
#define XSSPH12A       6361 /* Umschaltpunkt s2 */
#define XSSPH13A       6362 /* Umschaltpunkt s3 */
#define XSSPH14A       6363 /* Umschaltpunkt s4 */
#define XSSPH15A       6364 /* Umschaltpunkt s5 */
#define XSSPH16A       6365 /* Umschaltpunkt s6 */
#define XSSPH17A       6366 /* Umschaltpunkt s7 */
#define XSSPH18A       6367 /* Umschaltpunkt s8 */
#define XSSPH19A       6368 /* Umschaltpunkt s9 */
#define XHZITMESS1     6369 /* Messwert */
#define XHZITMESS2     6370 /* Messwert */
#define XHZITMESS3     6371 /* Messwert */
#define XHZITMESS4     6372 /* Messwert */
#define XHXSNIF        6373 /* Schnittstelle */
#define XHXSNPROTO     6374 /* Protokoll */
#define XHXSNBAUD      6375 /* Baudrate */
#define XHXSNDATBIT    6376 /* Datenbits */
#define XHXSNSTPBIT    6377 /* Stopbits */
#define XHXSNPARITY    6378 /* Parity */
#define XHZSNREGNR1    6379 /* Reglernummer */
#define XHZSNREGNR2    6380 /* Reglernummer */
#define XHZSNREGNR3    6381 /* Reglernummer */
#define XHZSNREGNR4    6382 /* Reglernummer */
#define XHZSNWAHL1     6383 /* Wahl des Zeitpunktes */
#define XHZSNWAHL2     6384 /* Wahl des Zeitpunktes */
#define XHZSNWAHL3     6385 /* Wahl des Zeitpunktes */
#define XHZSNWAHL4     6386 /* Wahl des Zeitpunktes */
#define XHXSNIF_2      6387 /* Schnittstelle 2*/
#define XHXSNPROTO_2   6388 /* Protokoll 2 */
#define XHXSNBAUD_2    6389 /* Baudrate 2 */
#define XHXSNDATBIT_2  6390 /* Datenbits 2 */
#define XHXSNSTPBIT_2  6391 /* Stopbits 2 */
#define XHXSNPARITY_2  6392 /* Parity 2 */
/* -------- Register fuer Produktionsstart S. 40.2 fuer 2. Aggregat - */
#define XSSDOS2A       6393 /* Plastivizierweg */
#define XSPPH21A       6394 /* Einspritzdruck p1 */
#define XSTPH21A       6395 /* Einspritzzeit t1 */
#define XSPPH22A       6396 /* Einspritzdruck p2 */
#define XSTPH22A       6397 /* Einspritzzeit t2 */
#define XSPPH23A       6398 /* Einspritzdruck p3 */
#define XSTPH23A       6399 /* Einspritzzeit t3 */
#define XSVPH21A       6400 /* Einspritzgeschw. v1 */ 
#define XSVPH22A       6401 /* Einspritzgeschw. v2 */
#define XSVPH23A       6402 /* Einspritzgeschw. v3 */ 
#define XSVPH24A       6403 /* Einspritzgeschw. v4 */ 
#define XSVPH25A       6404 /* Einspritzgeschw. v5 */
#define XSVPH26A       6405 /* Einspritzgeschw. v6 */ 
#define XSVPH27A       6406 /* Einspritzgeschw. v7 */ 
#define XSVPH28A       6407 /* Einspritzgeschw. v8 */
#define XSVPH29A       6408 /* Einspritzgeschw. v9 */ 
#define XSSPH21A       6409 /* Umschaltpunkt s1 */
#define XSSPH22A       6410 /* Umschaltpunkt s2 */
#define XSSPH23A       6411 /* Umschaltpunkt s3 */
#define XSSPH24A       6412 /* Umschaltpunkt s4 */
#define XSSPH25A       6413 /* Umschaltpunkt s5 */
#define XSSPH26A       6414 /* Umschaltpunkt s6 */
#define XSSPH27A       6415 /* Umschaltpunkt s7 */
#define XSSPH28A       6416 /* Umschaltpunkt s8 */
#define XSSPH29A       6417 /* Umschaltpunkt s9 */                       


/* Registernummern fuer frei programmierbare Kernzuege  */
#define IKEPRGNO       10600
#define IKE_NRSCHRAUB  10601
#define IKE_NRWEND     10602
#define IKE_SPERRMASKE 10603

#define IKEEINRICHT    10700
#define IKEGRUNDST     10701
#define IKEPGMSTAT     10702
#define IKEPARUPD      10703
#define IKEPGMLINES    10704
#define IKEDLENABLE    10705
#define IKEDLSTAT      10706
#define IKESYNC        10707
#define IKEIST1        10708
#define IKEIST2        10709
#define IKEIST3        10710
#define IKEIST4        10711
#define IKEIST5        10712
#define IKEIST6        10713
#define IKEIST7        10714
#define IKEIST8        10715
#define IKEIST9        10716
#define IKELINENO      10717
#define IKEERROR1      10718
#define IKEERROR2      10719
#define IKEERROR3      10720
#define IKEERROR4      10721
#define IKEERROR5      10722
#define IKEERROR6      10723
#define IKEERROR7      10724
#define IKEERROR8      10725
#define IKEERROR9      10726
#define IKEERROR       10727
#define IKEEVALID      10728
#define IKEEPOS1       10729
#define IKEEPOS2       10730
#define IKEEPOS3       10731
#define IKEEPOS4       10732
#define IKEEPOS5       10734
#define IKEEPOS6       10735
#define IKEEPOS7       10736
#define IKEEPOS8       10737
#define IKEEPOS9       10738

/* ---------------- Register fuer neue Prozessgrafik, 4 Funktionseinheiten  */
#define XPG_WORK          10740
#define XPG_WORK01        10741
#define XPG_WORK02        10742
#define XPG_WORK03        10743
#define XPG_WORK04        10744
#define XPG_START_WORK    10745
#define XPG_START_WORK01  10746
#define XPG_START_WORK02  10747
#define XPG_START_WORK03  10748
#define XPG_START_WORK04  10749
#define XPG_STOP_WORK     10750
#define XPG_STOP_WORK01   10751
#define XPG_STOP_WORK02   10752
#define XPG_STOP_WORK03   10753
#define XPG_STOP_WORK04   10754
#define XPG_IST_WORK      10755
#define XPG_IST_WORK01    10756
#define XPG_IST_WORK02    10757
#define XPG_IST_WORK03    10758
#define XPG_IST_WORK04    10759
#define XPG_REFIST_WORK   10760
#define XPG_REFIST_WORK01 10761
#define XPG_REFIST_WORK02 10762
#define XPG_REFIST_WORK03 10763
#define XPG_REFIST_WORK04 10764
#define XPG_TOL_WORK      10765
#define XPG_TOL_WORK01    10766
#define XPG_TOL_WORK02    10767
#define XPG_TOL_WORK03    10768
#define XPG_TOL_WORK04    10769
#define XSTARTREC         10770

#define XPG_PRES_AREA     10780
#define XPG_PRES_AREA01   10781
#define XPG_PRES_AREA02   10782
#define XPG_PRES_AREA03   10783
#define XPG_PRES_AREA04   10784
#define XPG_PRES_AREA05   10785
#define XPG_PRES_AREA06   10786

/* ---------------- Register fuer 5/6 Farben ------------------------------ */
#define XPG_WORK05        10790
#define XPG_WORK06        10791
#define XPG_START_WORK05  10792
#define XPG_START_WORK06  10793
#define XPG_STOP_WORK05   10794
#define XPG_STOP_WORK06   10795
#define XPG_IST_WORK05    10796
#define XPG_IST_WORK06    10797
#define XPG_REFIST_WORK05 10798
#define XPG_REFIST_WORK06 10799
#define XPG_TOL_WORK05    10800
#define XPG_TOL_WORK06    10801

#define XPG_MODE          10860
#define XPG_MODE01        10861 
#define XPG_MODE02        10862 
#define XPG_MODE03        10863 
#define XPG_MODE04        10864 
#define XPG_MODE05        10865 
#define XPG_MODE06        10866 

#define XPG_MEASTIME             10870
#define XPG_MEASTIME01           10871
#define XPG_MEASTIME02           10872
#define XPG_MEASTIME03           10873
#define XPG_MEASTIME04           10874
#define XPG_MEASTIME05           10875
#define XPG_MEASTIME06           10876

#define XPG_INTERVAL             10880 
#define XPG_INTERVAL01           10881 
#define XPG_INTERVAL02           10882
#define XPG_INTERVAL03           10883
#define XPG_INTERVAL04           10884
#define XPG_INTERVAL05           10885
#define XPG_INTERVAL06           10886

#define XPG_DELAY                10890 
#define XPG_DELAY01              10891 
#define XPG_DELAY02              10892 
#define XPG_DELAY03              10893 
#define XPG_DELAY04              10894 
#define XPG_DELAY05              10895 
#define XPG_DELAY06              10896 

#define XPG_MAXX                 10950 
#define XPG_MAXX01               10951 
#define XPG_MAXX02               10952
#define XPG_MAXX03               10953
#define XPG_MAXX04               10954
#define XPG_MAXX05               10955
#define XPG_MAXX06               10956

#define XPG_COMPARE              11100
#define XPG_COMPARE01            11101 
#define XPG_COMPARE02            11102 
#define XPG_COMPARE03            11103 
#define XPG_COMPARE04            11104 
#define XPG_COMPARE05            11105 
#define XPG_COMPARE06            11106 
#define XPG_COMPARE07            11107 
#define XPG_COMPARE08            11108 
#define XPG_COMPARE09            11109 
#define XPG_COMPARE10            11110 
#define XPG_COMPARE11            11111 
#define XPG_COMPARE12            11112 
#define XPG_COMPARE13            11113 
#define XPG_COMPARE14            11114 
#define XPG_COMPARE15            11115 
#define XPG_COMPARE16            11116 
#define XPG_COMPARE17            11117 
#define XPG_COMPARE18            11118 
#define XPG_COMPARE19            11119 
#define XPG_COMPARE20            11120 
#define XPG_COMPARE21            11121 
#define XPG_COMPARE22            11122 
#define XPG_COMPARE23            11123 
#define XPG_COMPARE24            11124 
#define XPG_COMPARE25            11125 
#define XPG_COMPARE26            11126 
#define XPG_COMPARE27            11127 
#define XPG_COMPARE28            11128 
#define XPG_COMPARE29            11129 
#define XPG_COMPARE30            11130 
#define XPG_COMPARE31            11131 
#define XPG_COMPARE32            11132 
#define XPG_COMPARE33            11133 
#define XPG_COMPARE34            11134 
#define XPG_COMPARE35            11135 
#define XPG_COMPARE36            11136 
#define XPG_COMPARE37            11137 
#define XPG_COMPARE38            11138 
#define XPG_COMPARE39            11139 
#define XPG_COMPARE40            11140 
#define XPG_COMPARE41            11141 
#define XPG_COMPARE42            11142 
#define XPG_COMPARE43            11143 
#define XPG_COMPARE44            11144 
#define XPG_COMPARE45            11145 
#define XPG_COMPARE46            11146 
#define XPG_COMPARE47            11147 
#define XPG_COMPARE48            11148 
#define XPG_COMPARE49            11149 
#define XPG_COMPARE50            11150 
#define XPG_COMPARE51            11151 
#define XPG_COMPARE52            11152 
#define XPG_COMPARE53            11153 
#define XPG_COMPARE54            11154 
#define XPG_COMPARE55            11155 
#define XPG_COMPARE56            11156 
#define XPG_COMPARE57            11157 
#define XPG_COMPARE58            11158 
#define XPG_COMPARE59            11159 

#define XPG_TOLERANCE            11200
#define XPG_TOLERANCE01          11201
#define XPG_TOLERANCE02          11202
#define XPG_TOLERANCE03          11203
#define XPG_TOLERANCE04          11204
#define XPG_TOLERANCE05          11205
#define XPG_TOLERANCE06          11206
#define XPG_TOLERANCE07          11207
#define XPG_TOLERANCE08          11208
#define XPG_TOLERANCE09          11209
#define XPG_TOLERANCE10          11210
#define XPG_TOLERANCE11          11211
#define XPG_TOLERANCE12          11212
#define XPG_TOLERANCE13          11213
#define XPG_TOLERANCE14          11214
#define XPG_TOLERANCE15          11215
#define XPG_TOLERANCE16          11216
#define XPG_TOLERANCE17          11217
#define XPG_TOLERANCE18          11218
#define XPG_TOLERANCE19          11219
#define XPG_TOLERANCE20          11220
#define XPG_TOLERANCE21          11221
#define XPG_TOLERANCE22          11222
#define XPG_TOLERANCE23          11223
#define XPG_TOLERANCE24          11224
#define XPG_TOLERANCE25          11225
#define XPG_TOLERANCE26          11226
#define XPG_TOLERANCE27          11227
#define XPG_TOLERANCE28          11228
#define XPG_TOLERANCE29          11229
#define XPG_TOLERANCE30          11230
#define XPG_TOLERANCE31          11231
#define XPG_TOLERANCE32          11232
#define XPG_TOLERANCE33          11233
#define XPG_TOLERANCE34          11234
#define XPG_TOLERANCE35          11235
#define XPG_TOLERANCE36          11236
#define XPG_TOLERANCE37          11237
#define XPG_TOLERANCE38          11238
#define XPG_TOLERANCE39          11239
#define XPG_TOLERANCE40          11240
#define XPG_TOLERANCE41          11241
#define XPG_TOLERANCE42          11242
#define XPG_TOLERANCE43          11243
#define XPG_TOLERANCE44          11244
#define XPG_TOLERANCE45          11245
#define XPG_TOLERANCE46          11246
#define XPG_TOLERANCE47          11247
#define XPG_TOLERANCE48          11248
#define XPG_TOLERANCE49          11249
#define XPG_TOLERANCE50          11250
#define XPG_TOLERANCE51          11251
#define XPG_TOLERANCE52          11252
#define XPG_TOLERANCE53          11253
#define XPG_TOLERANCE54          11254
#define XPG_TOLERANCE55          11255
#define XPG_TOLERANCE56          11256
#define XPG_TOLERANCE57          11257
#define XPG_TOLERANCE58          11258
#define XPG_TOLERANCE59          11259

#define XPG_YSCAL                11300
#define XPG_YSCAL01              11301 
#define XPG_YSCAL02              11302 
#define XPG_YSCAL03              11303 
#define XPG_YSCAL04              11304 
#define XPG_YSCAL05              11305 
#define XPG_YSCAL06              11306 
#define XPG_YSCAL07              11307 
#define XPG_YSCAL08              11308 
#define XPG_YSCAL09              11309 
#define XPG_YSCAL10              11310 
#define XPG_YSCAL11              11311 
#define XPG_YSCAL12              11312 
#define XPG_YSCAL13              11313 
#define XPG_YSCAL14              11314 
#define XPG_YSCAL15              11315 
#define XPG_YSCAL16              11316 
#define XPG_YSCAL17              11317 
#define XPG_YSCAL18              11318 
#define XPG_YSCAL19              11319 
#define XPG_YSCAL20              11320 
#define XPG_YSCAL21              11321 
#define XPG_YSCAL22              11322 
#define XPG_YSCAL23              11323 
#define XPG_YSCAL24              11324 
#define XPG_YSCAL25              11325 
#define XPG_YSCAL26              11326 
#define XPG_YSCAL27              11327 
#define XPG_YSCAL28              11328 
#define XPG_YSCAL29              11329 
#define XPG_YSCAL30              11330 
#define XPG_YSCAL31              11331 
#define XPG_YSCAL32              11332 
#define XPG_YSCAL33              11333 
#define XPG_YSCAL34              11334 
#define XPG_YSCAL35              11335 
#define XPG_YSCAL36              11336 
#define XPG_YSCAL37              11337 
#define XPG_YSCAL38              11338 
#define XPG_YSCAL39              11339 
#define XPG_YSCAL40              11340 
#define XPG_YSCAL41              11341 
#define XPG_YSCAL42              11342 
#define XPG_YSCAL43              11343 
#define XPG_YSCAL44              11344 
#define XPG_YSCAL45              11345 
#define XPG_YSCAL46              11346 
#define XPG_YSCAL47              11347 
#define XPG_YSCAL48              11348 
#define XPG_YSCAL49              11349 
#define XPG_YSCAL50              11350 
#define XPG_YSCAL51              11351 
#define XPG_YSCAL52              11352 
#define XPG_YSCAL53              11353 
#define XPG_YSCAL54              11354 
#define XPG_YSCAL55              11355 
#define XPG_YSCAL56              11356 
#define XPG_YSCAL57              11357 
#define XPG_YSCAL58              11358 
#define XPG_YSCAL59              11359 

#define XPG_YMAX                 11400
#define XPG_YMAX01               11401
#define XPG_YMAX02               11402
#define XPG_YMAX03               11403
#define XPG_YMAX04               11404
#define XPG_TOL_ERRS             11405
#define XPG_FREE_REG0            11406
#define XPG_FREE_REG1            11407
#define XPG_FREE_REG2            11408
#define XPG_FREE_REG3            11409
#define XPG_FREE_REG4            11410
#define XPG_FREE_REG5            11411
#define XPG_FREE_REG6            11412
#define XPG_FREE_REG7            11413
#define XPG_FREE_REG8            11414
#define XPG_FREE_REG9            11415
#define XPG_AGGREGAT             11416
#define XPG_SCDIA                11417

/* Permanente Sonderprogrammregister                                       */
/* Diese Register werden exclusiv von einem "Standard"-Sonderprogramm      */
/* verwendet.                                                              */

/* Gillette-Sonderprogrammregister:                                        */
#define GIL_XSON0                 12000
#define GIL_XSON1                 12001
#define GIL_XSON2                 12002
#define GIL_XSON3                 12003
#define GIL_XSON4                 12004
#define GIL_XSON5                 12005
#define GIL_XSON6                 12006
#define GIL_XSON7                 12007
#define GIL_XSON8                 12008
#define GIL_XSON9                 12009
#define GIL_XSON10                12010
#define GIL_XSON11                12011
#define GIL_XSON12                12012
#define GIL_XSON13                12013
#define GIL_XSON14                12014
#define GIL_XSON15                12015
#define GIL_SSON0                 12016
#define GIL_SSON1                 12017
#define GIL_SSON2                 12018
#define GIL_SSON3                 12019
#define GIL_SSON4                 12020
#define GIL_SSON5                 12021
#define GIL_SSON6                 12022
#define GIL_SSON7                 12023
#define GIL_SSON8                 12024
#define GIL_SSON9                 12025
#define GIL_SSON10                12026
#define GIL_SSON11                12027
#define GIL_SSON12                12028
#define GIL_SSON13                12029
#define GIL_SSON14                12030
#define GIL_SSON15                12031
#define GIL_SSON16                12032
#define GIL_SSON17                12033
#define GIL_SSON18                12034
#define GIL_SSON19                12035
#define GIL_SSON20                12036
#define GIL_SSON21                12037
#define GIL_SSON22                12038
#define GIL_SSON23                12039
#define GIL_SSON24                12040
#define GIL_SSON25                12041
#define GIL_SSON26                12042
#define GIL_SSON27                12043
#define GIL_SSON28                12044
#define GIL_SSON29                12045
#define GIL_SSON30                12046
#define GIL_SSON31                12047
#define GIL_SSON32                12048
#define GIL_SSON33                12049
#define GIL_SSON34                12050
#define GIL_SSON35                12051
#define GIL_SSON36                12052
#define GIL_SSON37                12053
#define GIL_SSON38                12054
#define GIL_SSON39                12055
#define GIL_SSON40                12056
#define GIL_SSON41                12057
#define GIL_SSON42                12058
#define GIL_SSON43                12059
#define GIL_SSON44                12060
#define GIL_SSON45                12061
#define GIL_SSON46                12062
#define GIL_SSON47                12063
#define GIL_SSON48                12064
#define GIL_SSON49                12065
#define GIL_SSON50                12066
#define GIL_SSON51                12067
#define GIL_SSON52                12068
#define GIL_SSON53                12069
#define GIL_SSON54                12070
#define GIL_SSON55                12071
#define GIL_SSON56                12072
#define GIL_SSON57                12073
#define GIL_SSON58                12074
#define GIL_SSON59                12075
#define GIL_SSON60                12076
#define GIL_SSON61                12077
#define GIL_SSON62                12078
#define GIL_SSON63                12079
#define GIL_SSON64                12080
#define GIL_SSON65                12081
#define GIL_SSON66                12082
#define GIL_SSON67                12083
#define GIL_SSON68                12084
#define GIL_SSON69                12085
#define GIL_SSON70                12086
#define GIL_SSON71                12087
#define GIL_SSON72                12088
#define GIL_SSON73                12089
#define GIL_SSON74                12090
#define GIL_SSON75                12091
#define GIL_SSON76                12092
#define GIL_SSON77                12093
#define GIL_SSON78                12094
#define GIL_SSON79                12095
#define GIL_SSON80                12096
#define GIL_SSON81                12097
#define GIL_SSON82                12098
#define GIL_SSON83                12099
#define GIL_SSON84                12100
#define GIL_SSON85                12101
#define GIL_SSON86                12102
#define GIL_SSON87                12103
#define GIL_SSON88                12104
#define GIL_SSON89                12105
#define GIL_SSON90                12106
#define GIL_SSON91                12107
#define GIL_SSON92                12108
#define GIL_SSON93                12109
#define GIL_SSON94                12110
#define GIL_SSON95                12111
#define GIL_SSON96                12112
#define GIL_SSON97                12113
#define GIL_SSON98                12114
#define GIL_SSON99                12115
#define GIL_SSON100               12116
#define GIL_SSON101               12117
#define GIL_SSON102               12118
#define GIL_SSON103               12119
#define GIL_SSON104               12120
#define GIL_SSON105               12121
#define GIL_SSON106               12122
#define GIL_SSON107               12123
#define GIL_SSON108               12124
#define GIL_SSON109               12125
#define GIL_SSON110               12126
#define GIL_SSON111               12127
#define GIL_SSON112               12128
#define GIL_SSON113               12129
#define GIL_SSON114               12130
#define GIL_SSON115               12131
#define GIL_SSON116               12132
#define GIL_SSON117               12133
#define GIL_SSON118               12134
#define GIL_SSON119               12135
/* ---------------- Werkzeug Wenden --------------------------------------- */
#define XWDM_BETART               12136
#define XWDM_STAPKT               12137
#define XWDSTVERZ                 12138
#define XWDSV11                   12139
#define XWDSV12                   12140
#define XWDSV21                   12141
#define XWDSV22                   12142
#define XWDSP11                   12143
#define XWDSP12                   12144
#define XWDSP21                   12145
#define XWDSP22                   12146
#define XWDSVEINRGR               12147
#define XWDSVGEREG                12148
#define XWDST                     12149
/* ---------------- Werkzeug Drehteller-Parameter ------------------------- */
#define XDTISABS                  12150
#define XDTISRELA                 12151
#define XDTSABESCHL               12152
#define XDTIABESCHL               12153
#define XDTSTVERZ                 12154
#define XDTITVERZ                 12155
#define XDTS_VOFF1                12156
#define XDTI_VOFF1                12157
#define XDTS_VOFF2                12158
#define XDTI_VOFF2                12159
#define XDTS_SKGES                12160
#define XDTI_SKGES                12161
#define XDTS_SKGER                12162
#define XDTI_SKGER                12163
#define XDTS_ZIELF                12164
#define XDTI_ZIELF                12165
#define XDTS_SWEITE               12166
#define XDTI_SWEITE               12167
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define XWZA_BA                   12168
#define XWZA_SPKTV                12169
#define XWZA_AUSWH                12170
#define XWZA_WZVOR                12171
#define XWZA_AKZVOR               12172
#define XWZA_AKZZUR               12173
#define XWZAPVOR                  12174
#define XWZAPZUR                  12175
#define XWZAVVOR1                 12176
#define XWZAVVOR2                 12177
#define XWZAVZUR                  12178
#define XDTGENMOD                 12179
/* ---------------- Werkzeugauswerfer 2 ----------------------------------- */
#define XWZA_BA_FHK               12180
#define XWZA_BA2                  12181
#define XWZA_SPKTV2               12182
#define XWZA_AUSWH2               12183
#define XWZA_WZVOR2               12184
#define XWZA_AKZVOR2              12185
#define XWZA_AKZZUR2              12186
#define XWZAPVOR2                 12187
#define XWZAPZUR2                 12188
#define XWZAVVOR12                12189
#define XWZAVVOR22                12190
#define XWZAVZUR2                 12191
#define XDTS_NUM                  12192
#define XDTI_NUM                  12193


/* ---------------- Heizungsregister Zylinderheizung: --------------------- */
#define INJHEAT_SOLL             19000 /* Heizungs-Sollwert                  */
#define INJHEAT_TOL_WIDE_DOWN    19001 /* weite, untere Toleranzgrenze       */
#define INJHEAT_TOL_NARROW_DOWN  19002 /* enge, untere Toleranzgrenze        */
#define INJHEAT_TOL_WIDE_UP      19003 /* weite, obere Toleranzgrenze        */
#define INJHEAT_TOL_NARROW_UP    19004 /* enge, obere Toleranzgrenze         */
#define INJHEAT_MCW              19005 /* Modecontrolwort                    */
#define INJHEAT_XPH              19006 /* Einstellwert Regelstr. heizen      */
#define INJHEAT_XPK              19007 /* Einstellwert Regelstr. kuhlen      */
#define INJHEAT_TN               19008 /* Einstellwert Regelstr. Nachstellzeit */
#define INJHEAT_TV               19009 /* Einstellwert Regelstr. Vorhaltezeit */
#define INJHEAT_HEAT_PERIOD      19010 /* Schaltperiodendauer heizen         */
#define INJHEAT_COOL_PERIOD      19011 /* Schaltperiodendauer kuhlen         */
#define INJHEAT_HYST             19012 /* Schalthysterese                    */
#define INJHEAT_WORK_POINT       19013 /* Arbeitspunkt                       */
#define INJHEAT_MIN_STELL        19014 /* minimale Stellgroae                */
#define INJHEAT_MAX_STELL        19015 /* maximale Stellgroae                */
#define INJHEAT_MOTOR_TIME       19016 /* Motorzeitkonstante                 */
#define INJHEAT_STELL_PERIOD     19017 /* Schaltperiodendauer Steller        */
#define INJHEAT_ON_OFF           19018 /* Regler ein-/ausschalten            */
#define INJHEAT_CURRENT_SOLL     19019 /* Sollwert Strommessung              */
#define INJHEAT_SOLL_STELL       19020 /* Sollwert Steller                   */

#define INJHEAT_THERM_TYPE       19025 /* Thermoelementtyp  -> MCW           */
#define INJHEAT_MEASURE_SWITCH   19026 /* Messung ein / aus -> MCW           */
#define INJHEAT_FUNCTION         19027 /* Funktion          -> MCW           */
#define INJHEAT_LOOP_NUMBER      19028 /* Schleifenanzahl                    */
#define INJHEAT_CONVERTER_TYPE   19029 /* Wandlertyp                         */

#define INJHEAT_IST              19030 /* Heizungs-Istwert                   */
#define INJHEAT_ED               19031 /* ED-Wert, ebenfalls Istwert         */
#define INJHEAT_CURRENT_IST      19032 /* Istwert Strommessung               */

#define INJHEAT_OPTMODE          19099    /* Optimierung aus/einzeln/Block */
/* ---------------- Heizungsregister Werkzeugheizung: --------------------- */
#define TOOLHEAT_SOLL            19100    /* Heizungs-Sollwert */
#define TOOLHEAT_TOL_WIDE_DOWN   19101    /* weite, untere Toleranzgrenze */
#define TOOLHEAT_TOL_NARROW_DOWN 19102    /* enge, untere Toleranzgrenze */
#define TOOLHEAT_TOL_WIDE_UP     19103    /* weite, obere Toleranzgrenze */
#define TOOLHEAT_TOL_NARROW_UP   19104    /* enge, obere Toleranzgrenze */
#define TOOLHEAT_MCW             19105    /* Modecontrolwort */
#define TOOLHEAT_XPH             19106    /* Einstellwert Regelstr. heizen */
#define TOOLHEAT_XPK             19107    /* Einstellwert Regelstr. kuhlen */
#define TOOLHEAT_TN              19108    /* Einstellwert Regelstr. Nachstellzeit */
#define TOOLHEAT_TV              19109    /* Einstellwert Regelstr. Vorhaltezeit */
#define TOOLHEAT_HEAT_PERIOD     19110    /* Schaltperiodendauer heizen */
#define TOOLHEAT_COOL_PERIOD     19111   /* Schaltperiodendauer kuhlen */
#define TOOLHEAT_HYST            19112    /* Schalthysterese */
#define TOOLHEAT_WORK_POINT      19113    /* Arbeitspunkt */
#define TOOLHEAT_MIN_STELL       19114    /* minimale Stellgroae */
#define TOOLHEAT_MAX_STELL       19115    /* maximale Stellgroae */
#define TOOLHEAT_MOTOR_TIME      19116    /* Motorzeitkonstante */
#define TOOLHEAT_STELL_PERIOD    19117    /* Schaltperiodendauer Steller */
#define TOOLHEAT_ON_OFF          19118    /* Regler ein-/ausschalten */
#define TOOLHEAT_CURRENT_SOLL    19119    /* Sollwert Strommessung */
#define TOOLHEAT_SOLL_STELL      19120    /* Sollwert Steller */

#define TOOLHEAT_THERM_TYPE      19125    /* Thermoelementtyp  -> MCW */
#define TOOLHEAT_MEASURE_SWITCH  19126    /* Messung ein / aus -> MCW */
#define TOOLHEAT_FUNCTION        19127    /* Funktion          -> MCW */
#define TOOLHEAT_LOOP_NUMBER     19128    /* Schleifenanzahl */
#define TOOLHEAT_CONVERTER_TYPE  19129    /* Wandlertyp */

#define TOOLHEAT_IST             19130    /* Heizungs-Istwert */
#define TOOLHEAT_ED              19131    /* ED-Wert, ebenfalls Istwert */
#define TOOLHEAT_CURRENT_IST     19132    /* Istwert Strommessung */

#define TOOLHEAT_OPTMODE         19199    /* Optimierung aus/einzeln/Block */
                                           /* Pseudo-Heiungsregister        */
/* Heizungsregister Temperiergerate: */

#define TEMPHEAT_SOLL            19200    /* Heizungs-Sollwert */
#define TEMPHEAT_TOL_WIDE_DOWN   19201    /* weite, untere Toleranzgrenze */
#define TEMPHEAT_TOL_NARROW_DOWN 19202    /* enge, untere Toleranzgrenze */
#define TEMPHEAT_TOL_WIDE_UP     19203    /* weite, obere Toleranzgrenze */
#define TEMPHEAT_TOL_NARROW_UP   19204    /* enge, obere Toleranzgrenze */
#define TEMPHEAT_MCW             19205    /* Modecontrolwort */
#define TEMPHEAT_XPH             19206    /* Einstellwert Regelstr. heizen */
#define TEMPHEAT_XPK             19207    /* Einstellwert Regelstr. kuhlen */
#define TEMPHEAT_TN              19208    /* Einstellwert Regelstr. Nachstellzeit */
#define TEMPHEAT_TV              19209    /* Einstellwert Regelstr. Vorhaltezeit */
#define TEMPHEAT_HEAT_PERIOD     19210    /* Schaltperiodendauer heizen */
#define TEMPHEAT_COOL_PERIOD     19211   /* Schaltperiodendauer kuhlen */
#define TEMPHEAT_HYST            19212    /* Schalthysterese */
#define TEMPHEAT_WORK_POINT      19213    /* Arbeitspunkt */
#define TEMPHEAT_MIN_STELL       19214    /* minimale Stellgroae */
#define TEMPHEAT_MAX_STELL       19215    /* maximale Stellgroae */
#define TEMPHEAT_MOTOR_TIME      19216    /* Motorzeitkonstante */
#define TEMPHEAT_STELL_PERIOD    19217    /* Schaltperiodendauer Steller */
#define TEMPHEAT_ON_OFF          19218    /* Regler ein-/ausschalten */
#define TEMPHEAT_CURRENT_SOLL    19219    /* Sollwert Strommessung */
#define TEMPHEAT_SOLL_STELL      19220    /* Sollwert Steller */

#define TEMPHEAT_THERM_TYPE      19225    /* Thermoelementtyp  -> MCW */
#define TEMPHEAT_MEASURE_SWITCH  19226    /* Messung ein / aus -> MCW */
#define TEMPHEAT_FUNCTION        19227    /* Funktion          -> MCW */
#define TEMPHEAT_LOOP_NUMBER     19228    /* Schleifenanzahl */
#define TEMPHEAT_CONVERTER_TYPE  19229    /* Wandlertyp */

#define TEMPHEAT_IST             19230    /* Heizungs-Istwert */
#define TEMPHEAT_ED              19231    /* ED-Wert, ebenfalls Istwert */
#define TEMPHEAT_CURRENT_IST     19232    /* Istwert Strommessung */

#define TEMPHEAT_OPTMODE         19299    /* Optimierung aus/einzeln/Block */
                                           /* Pseudo-Heiungsregister        */

/* Heizungsregister Oelheizung (Oelvorwaermung): */

#define OILHEAT_SOLL             19300    /* Heizungs-Sollwert */
#define OILHEAT_TOL_WIDE_DOWN    19301    /* weite, untere Toleranzgrenze */
#define OILHEAT_TOL_NARROW_DOWN  19302    /* enge, untere Toleranzgrenze */
#define OILHEAT_TOL_WIDE_UP      19303    /* weite, obere Toleranzgrenze */
#define OILHEAT_TOL_NARROW_UP    19304    /* enge, obere Toleranzgrenze */
#define OILHEAT_MCW              19305    /* Modecontrolwort */
#define OILHEAT_XPH              19306    /* Einstellwert Regelstr. heizen */
#define OILHEAT_XPK              19307    /* Einstellwert Regelstr. kuhlen */
#define OILHEAT_TN               19308    /* Einstellwert Regelstr. Nachstellzeit */
#define OILHEAT_TV               19309    /* Einstellwert Regelstr. Vorhaltezeit */
#define OILHEAT_HEAT_PERIOD      19310    /* Schaltperiodendauer heizen */
#define OILHEAT_COOL_PERIOD      19311   /* Schaltperiodendauer kuhlen */
#define OILHEAT_HYST             19312    /* Schalthysterese */
#define OILHEAT_WORK_POINT       19313    /* Arbeitspunkt */
#define OILHEAT_MIN_STELL        19314    /* minimale Stellgroae */
#define OILHEAT_MAX_STELL        19315    /* maximale Stellgroae */
#define OILHEAT_MOTOR_TIME       19316    /* Motorzeitkonstante */
#define OILHEAT_STELL_PERIOD     19317    /* Schaltperiodendauer Steller */
#define OILHEAT_ON_OFF           19318    /* Regler ein-/ausschalten */
#define OILHEAT_CURRENT_SOLL     19319    /* Sollwert Strommessung */
#define OILHEAT_SOLL_STELL       19320    /* Sollwert Steller */

#define OILHEAT_THERM_TYPE       19325    /* Thermoelementtyp  -> MCW */
#define OILHEAT_MEASURE_SWITCH   19326    /* Messung ein / aus -> MCW */
#define OILHEAT_FUNCTION         19327    /* Funktion          -> MCW */
#define OILHEAT_LOOP_NUMBER      19328    /* Schleifenanzahl */
#define OILHEAT_CONVERTER_TYPE   19329    /* Wandlertyp */

#define OILHEAT_IST              19330    /* Heizungs-Istwert */
#define OILHEAT_ED               19331    /* ED-Wert, ebenfalls Istwert */
#define OILHEAT_CURRENT_IST      19332    /* Istwert Strommessung */

#define OILHEAT_OPTMODE          19399    /* Optimierung aus/einzeln/Block */
                                          /* Pseudo-Heiungsregister        */


/* Allgemeine Heizungsregister: mit diesen Registern kann man auf alle       */
/* Heizungsreglerparameter zugreifen, wobei man als ersten Index die         */
/* Reglernummer angeben muss. Die Zuordnungstabellen des Kundenproms werden   */
/* hiermit uebergangen. Dies stellt neben den obigen Registern eine zweiten   */
/* Zugang zu der Heizungsparametern dar und wird v.a. auf der Seite zur      */
/* Parameterisierung der Regler benutzt.                                     */

#define GENHEAT_SOLL             19400    /* Heizungs-Sollwert */
#define GENHEAT_TOL_WIDE_DOWN    19401    /* weite, untere Toleranzgrenze */
#define GENHEAT_TOL_NARROW_DOWN  19402    /* enge, untere Toleranzgrenze */
#define GENHEAT_TOL_WIDE_UP      19403    /* weite, obere Toleranzgrenze */
#define GENHEAT_TOL_NARROW_UP    19404    /* enge, obere Toleranzgrenze */
#define GENHEAT_MCW              19405    /* Modecontrolwort */
#define GENHEAT_XPH              19406    /* Einstellwert Regelstr. heizen */
#define GENHEAT_XPK              19407    /* Einstellwert Regelstr. kuhlen */
#define GENHEAT_TN               19408    /* Einstellwert Regelstr. Nachstellzeit */
#define GENHEAT_TV               19409    /* Einstellwert Regelstr. Vorhaltezeit */
#define GENHEAT_HEAT_PERIOD      19410    /* Schaltperiodendauer heizen */
#define GENHEAT_COOL_PERIOD      19411   /* Schaltperiodendauer kuhlen */
#define GENHEAT_HYST             19412    /* Schalthysterese */
#define GENHEAT_WORK_POINT       19413    /* Arbeitspunkt */
#define GENHEAT_MIN_STELL        19414    /* minimale Stellgroae */
#define GENHEAT_MAX_STELL        19415    /* maximale Stellgroae */
#define GENHEAT_MOTOR_TIME       19416    /* Motorzeitkonstante */
#define GENHEAT_STELL_PERIOD     19417    /* Schaltperiodendauer Steller */
#define GENHEAT_ON_OFF           19418    /* Regler ein-/ausschalten */
#define GENHEAT_CURRENT_SOLL     19419    /* Sollwert Strommessung */
#define GENHEAT_SOLL_STELL       19420    /* Sollwert Steller */

#define GENHEAT_THERM_TYPE       19425    /* Thermoelementtyp  -> MCW */
#define GENHEAT_MEASURE_SWITCH   19426    /* Messung ein / aus -> MCW */
#define GENHEAT_FUNCTION         19427    /* Funktion          -> MCW */
#define GENHEAT_LOOP_NUMBER      19428    /* Schleifenanzahl */
#define GENHEAT_CONVERTER_TYPE   19429    /* Wandlertyp */

#define GENHEAT_IST              19430    /* Heizungs-Istwert */
#define GENHEAT_ED               19431    /* ED-Wert, ebenfalls Istwert */
#define GENHEAT_CURRENT_IST      19432    /* Istwert Strommessung */

#define GENHEAT_OPTMODE          19499    /* Optimierung aus/einzeln/Block */
                                          /* Pseudo-Heiungsregister        */


/* Reserveheizungsgruppe: Diese Heizungsgruppe kann spaeter einmal verwendet */
/* werden. Sie wurde rein auf Verdacht hin angelegt und zwar so, daá sie wie */
/* eine Werkzeugheizung verwendet werden kann, d.h. es koennen fuer jede     */
/* Station verschiedene Regler verwendet werden.                             */
#define RESHEAT_SOLL             19500    /* Heizungs-Sollwert */
#define RESHEAT_TOL_WIDE_DOWN    19501    /* weite, untere Toleranzgrenze */
#define RESHEAT_TOL_NARROW_DOWN  19502    /* enge, untere Toleranzgrenze */
#define RESHEAT_TOL_WIDE_UP      19503    /* weite, obere Toleranzgrenze */
#define RESHEAT_TOL_NARROW_UP    19504    /* enge, obere Toleranzgrenze */
#define RESHEAT_MCW              19505    /* Modecontrolwort */
#define RESHEAT_XPH              19506    /* Einstellwert Regelstr. heizen */
#define RESHEAT_XPK              19507    /* Einstellwert Regelstr. kuhlen */
#define RESHEAT_TN               19508    /* Einstellwert Regelstr. Nachstellzeit */
#define RESHEAT_TV               19509    /* Einstellwert Regelstr. Vorhaltezeit */
#define RESHEAT_HEAT_PERIOD      19510    /* Schaltperiodendauer heizen */
#define RESHEAT_COOL_PERIOD      19511   /* Schaltperiodendauer kuhlen */
#define RESHEAT_HYST             19512    /* Schalthysterese */
#define RESHEAT_WORK_POINT       19513    /* Arbeitspunkt */
#define RESHEAT_MIN_STELL        19514    /* minimale Stellgroae */
#define RESHEAT_MAX_STELL        19515    /* maximale Stellgroae */
#define RESHEAT_MOTOR_TIME       19516    /* Motorzeitkonstante */
#define RESHEAT_STELL_PERIOD     19517    /* Schaltperiodendauer Steller */
#define RESHEAT_ON_OFF           19518    /* Regler ein-/ausschalten */
#define RESHEAT_CURRENT_SOLL     19519    /* Sollwert Strommessung */
#define RESHEAT_SOLL_STELL       19520    /* Sollwert Steller */

#define RESHEAT_THERM_TYPE       19525    /* Thermoelementtyp  -> MCW */
#define RESHEAT_MEASURE_SWITCH   19526    /* Messung ein / aus -> MCW */
#define RESHEAT_FUNCTION         19527    /* Funktion          -> MCW */
#define RESHEAT_LOOP_NUMBER      19528    /* Schleifenanzahl */
#define RESHEAT_CONVERTER_TYPE   19529    /* Wandlertyp */
#define RESHEAT_IST              19530    /* Heizungs-Istwert */
#define RESHEAT_ED               19531    /* ED-Wert, ebenfalls Istwert */
#define RESHEAT_CURRENT_IST      19532    /* Istwert Strommessung */

#define RESHEAT_OPTMODE          19599    /* Optimierung aus/einzeln/Block */
                                          /* Pseudo-Heiungsregister        */
/*-----------  Rampenzeiten fuer S. 48 -------------------*/
#define XRAMPE1_D1               19600    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE1_D2               19601    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE1_D3               19602    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE1_D4               19603    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE2_D1               19604    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE2_D2               19605    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE2_D3               19606    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE2_D4               19607    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE3_D1               19608    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE3_D2               19609    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE3_D3               19610    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE3_D4               19611    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE4_D1               19612    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE4_D2               19613    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE4_D3               19614    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE4_D4               19615    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE5_D1               19616    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE5_D2               19617    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE5_D3               19618    /* Rampenzeit fuer Airprass S. 48 */
#define XRAMPE5_D4               19619    /* Rampenzeit fuer Airprass S. 48 */

#define XWKZDUES_D1              19621    /* WKZ Duese schliessen fuer Airprass S. 48 */
#define XWKZDUES_D2              19622    /* WKZ Duese schliessen fuer Airprass S. 48 */
#define XWKZDUES_D3              19623    /* WKZ Duese schliessen fuer Airprass S. 48 */
#define XWKZDUES_D4              19624    /* WKZ Duese schliessen fuer Airprass S. 48 */

/*-- fuer S. 66.0 - 66.2 Konfigurierbare digitale/analoge  Ein-/Ausgaenge --*/
#define IOINDIIST                19628    /* Aktwerte  S. 66.0 */
#define IOINDOIST                19629    /* Aktwerte  S. 66.1 */
#define IOS_DIFKT1               19630    /* Sollwerte Funktion S. 66.0 */
#define IOS_DIFKT2               19631    /* Sollwerte Funktion S. 66.0 */
#define IOS_DIFKT3               19632    /* Sollwerte Funktion S. 66.0 */
#define IOS_DIFKT4               19633    /* Sollwerte Funktion S. 66.0 */
#define IOS_DOFKT1               19634    /* Sollwerte Funktion S. 66.1 */
#define IOS_DOFKT2               19635    /* Sollwerte Funktion S. 66.1 */
#define IOS_DOFKT3               19636    /* Sollwerte Funktion S. 66.1 */
#define IOS_DOFKT4               19637    /* Sollwerte Funktion S. 66.1 */
#define IOSTDOAKT1               19638    /* Sollwerte Aktionszeit S. 66.1 */
#define IOSTDOAKT2               19639    /* Sollwerte Aktionszeit S. 66.1 */
#define IOSTDOAKT3               19640    /* Sollwerte Aktionszeit S. 66.1 */
#define IOSTDOAKT4               19641    /* Sollwerte Aktionszeit S. 66.1 */
#define IOSNDOPAR1               19642    /* Sollwerte Parameter S. 66.1 */
#define IOSNDOPAR2               19643    /* Sollwerte Parameter S. 66.1 */
#define IOSNDOPAR3               19644    /* Sollwerte Parameter S. 66.1 */
#define IOSNDOPAR4               19645    /* Sollwerte Parameter S. 66.1 */
#define IOS_AOFKT1               19646    /* Sollwerte Funktion S. 66.2 */
#define IOS_AOFKT2               19647    /* Sollwerte Funktion S. 66.2 */
#define IOS_AOFKT3               19648    /* Sollwerte Funktion S. 66.2 */
#define IOS_AOFKT4               19649    /* Sollwerte Funktion S. 66.2 */
#define IOINAOIST1               19650    /* Aktwerte  S. 66.2 */
#define IOINAOIST2               19651    /* Aktwerte  S. 66.2 */
#define IOINAOIST3               19652    /* Aktwerte  S. 66.2 */
#define IOINAOIST4               19653    /* Aktwerte  S. 66.2 */
/*------ Ende ---------------------------------------------------------------*/
#define SZINSUB                  19654    /* subtrahierender Schusszaehler */
#define BA_FOER                  19655    /* Foerderband S. 71 BA_foer        */
#define FBST                     19656    /* Foerderband getaktet  S. 71 FBst */
#define XCARD_INFO               19657    /* Card-Info */
/*------------ Rampen fuer Einspritzstufen ---------------------------------*/
#define XSESVRAMPE11             19658    /* Geschwindigkeitsrampe Stufe 1 Agg.1 */
#define XSESVRAMPE12             19659    /* Geschwindigkeitsrampe Stufe 2 Agg.1 */
#define XSESVRAMPE13             19660    /* Geschwindigkeitsrampe Stufe 3 Agg.1 */
#define XSESVRAMPE14             19661    /* Geschwindigkeitsrampe Stufe 4 Agg.1 */
#define XSESVRAMPE15             19662    /* Geschwindigkeitsrampe Stufe 5 Agg.1 */
#define XSESVRAMPE16             19663    /* Geschwindigkeitsrampe Stufe 6 Agg.1 */
#define XSESVRAMPE17             19664    /* Geschwindigkeitsrampe Stufe 7 Agg.1 */
#define XSESVRAMPE18             19665    /* Geschwindigkeitsrampe Stufe 8 Agg.1 */
#define XSESVRAMPE19             19666    /* Geschwindigkeitsrampe Stufe 9 Agg.1 */
#define XSESVRAMPE21             19667    /* Geschwindigkeitsrampe Stufe 1 Agg.2 */
#define XSESVRAMPE22             19668    /* Geschwindigkeitsrampe Stufe 2 Agg.2 */
#define XSESVRAMPE23             19669    /* Geschwindigkeitsrampe Stufe 3 Agg.2 */
#define XSESVRAMPE24             19670    /* Geschwindigkeitsrampe Stufe 4 Agg.2 */
#define XSESVRAMPE25             19671    /* Geschwindigkeitsrampe Stufe 5 Agg.2 */
#define XSESVRAMPE26             19672    /* Geschwindigkeitsrampe Stufe 6 Agg.2 */
#define XSESVRAMPE27             19673    /* Geschwindigkeitsrampe Stufe 7 Agg.2 */
#define XSESVRAMPE28             19674    /* Geschwindigkeitsrampe Stufe 8 Agg.2 */
#define XSESVRAMPE29             19675    /* Geschwindigkeitsrampe Stufe 9 Agg.2 */
#define XSESVRAMPE31             19676    /* Geschwindigkeitsrampe Stufe 1 Agg.3 */
#define XSESVRAMPE32             19677    /* Geschwindigkeitsrampe Stufe 2 Agg.3 */
#define XSESVRAMPE33             19678    /* Geschwindigkeitsrampe Stufe 3 Agg.3 */
#define XSESVRAMPE34             19679    /* Geschwindigkeitsrampe Stufe 4 Agg.3 */
#define XSESVRAMPE35             19680    /* Geschwindigkeitsrampe Stufe 5 Agg.3 */
#define XSESVRAMPE36             19681    /* Geschwindigkeitsrampe Stufe 6 Agg.3 */
#define XSESVRAMPE37             19682    /* Geschwindigkeitsrampe Stufe 7 Agg.3 */
#define XSESVRAMPE38             19683    /* Geschwindigkeitsrampe Stufe 8 Agg.3 */
#define XSESVRAMPE39             19684    /* Geschwindigkeitsrampe Stufe 9 Agg.3 */
#define XSESVRAMPE41             19685    /* Geschwindigkeitsrampe Stufe 1 Agg.4 */
#define XSESVRAMPE42             19686    /* Geschwindigkeitsrampe Stufe 2 Agg.4 */
#define XSESVRAMPE43             19687    /* Geschwindigkeitsrampe Stufe 3 Agg.4 */
#define XSESVRAMPE44             19688    /* Geschwindigkeitsrampe Stufe 4 Agg.4 */
#define XSESVRAMPE45             19689    /* Geschwindigkeitsrampe Stufe 5 Agg.4 */
#define XSESVRAMPE46             19690    /* Geschwindigkeitsrampe Stufe 6 Agg.4 */
#define XSESVRAMPE47             19691    /* Geschwindigkeitsrampe Stufe 7 Agg.4 */
#define XSESVRAMPE48             19692    /* Geschwindigkeitsrampe Stufe 8 Agg.4 */
#define XSESVRAMPE49             19693    /* Geschwindigkeitsrampe Stufe 9 Agg.4 */
#define XSESVRAMPE51             19694    /* Geschwindigkeitsrampe Stufe 1 Agg.5 */
#define XSESVRAMPE52             19695    /* Geschwindigkeitsrampe Stufe 2 Agg.5 */
#define XSESVRAMPE53             19696    /* Geschwindigkeitsrampe Stufe 3 Agg.5 */
#define XSESVRAMPE54             19697    /* Geschwindigkeitsrampe Stufe 4 Agg.5 */
#define XSESVRAMPE55             19698    /* Geschwindigkeitsrampe Stufe 5 Agg.5 */
#define XSESVRAMPE56             19699    /* Geschwindigkeitsrampe Stufe 6 Agg.5 */
#define XSESVRAMPE57             19700    /* Geschwindigkeitsrampe Stufe 7 Agg.5 */
#define XSESVRAMPE58             19701    /* Geschwindigkeitsrampe Stufe 8 Agg.5 */
#define XSESVRAMPE59             19702    /* Geschwindigkeitsrampe Stufe 9 Agg.5 */
/*-------------------------------------------------------------------------------*/
#define XSESPRAMPE11             19703    /* Druckrampe Stufe 1 Agg.1 */
#define XSESPRAMPE12             19704    /* Druckrampe Stufe 2 Agg.1 */
#define XSESPRAMPE13             19705    /* Druckrampe Stufe 3 Agg.1 */
#define XSESPRAMPE14             19706    /* Druckrampe Stufe 4 Agg.1 */
#define XSESPRAMPE15             19707    /* Druckrampe Stufe 5 Agg.1 */
#define XSESPRAMPE16             19708    /* Druckrampe Stufe 6 Agg.1 */
#define XSESPRAMPE17             19709    /* Druckrampe Stufe 7 Agg.1 */
#define XSESPRAMPE18             19710    /* Druckrampe Stufe 8 Agg.1 */
#define XSESPRAMPE19             19711    /* Druckrampe Stufe 9 Agg.1 */
#define XSESPRAMPE21             19712    /* Druckrampe Stufe 1 Agg.2 */
#define XSESPRAMPE22             19713    /* Druckrampe Stufe 2 Agg.2 */
#define XSESPRAMPE23             19714    /* Druckrampe Stufe 3 Agg.2 */
#define XSESPRAMPE24             19715    /* Druckrampe Stufe 4 Agg.2 */
#define XSESPRAMPE25             19716    /* Druckrampe Stufe 5 Agg.2 */
#define XSESPRAMPE26             19717    /* Druckrampe Stufe 6 Agg.2 */
#define XSESPRAMPE27             19718    /* Druckrampe Stufe 7 Agg.2 */
#define XSESPRAMPE28             19719    /* Druckrampe Stufe 8 Agg.2 */
#define XSESPRAMPE29             19720    /* Druckrampe Stufe 9 Agg.2 */
#define XSESPRAMPE31             19721    /* Druckrampe Stufe 1 Agg.3 */
#define XSESPRAMPE32             19722    /* Druckrampe Stufe 2 Agg.3 */
#define XSESPRAMPE33             19723    /* Druckrampe Stufe 3 Agg.3 */
#define XSESPRAMPE34             19724    /* Druckrampe Stufe 4 Agg.3 */
#define XSESPRAMPE35             19725    /* Druckrampe Stufe 5 Agg.3 */
#define XSESPRAMPE36             19726    /* Druckrampe Stufe 6 Agg.3 */
#define XSESPRAMPE37             19727    /* Druckrampe Stufe 7 Agg.3 */
#define XSESPRAMPE38             19728    /* Druckrampe Stufe 8 Agg.3 */
#define XSESPRAMPE39             19729    /* Druckrampe Stufe 9 Agg.3 */
#define XSESPRAMPE41             19730    /* Druckrampe Stufe 1 Agg.4 */        
#define XSESPRAMPE42             19731    /* Druckrampe Stufe 2 Agg.4 */
#define XSESPRAMPE43             19732    /* Druckrampe Stufe 3 Agg.4 */
#define XSESPRAMPE44             19733    /* Druckrampe Stufe 4 Agg.4 */
#define XSESPRAMPE45             19734    /* Druckrampe Stufe 5 Agg.4 */
#define XSESPRAMPE46             19735    /* Druckrampe Stufe 6 Agg.4 */
#define XSESPRAMPE47             19736    /* Druckrampe Stufe 7 Agg.4 */
#define XSESPRAMPE48             19737    /* Druckrampe Stufe 8 Agg.4 */
#define XSESPRAMPE49             19738    /* Druckrampe Stufe 9 Agg.4 */
#define XSESPRAMPE51             19739    /* Druckrampe Stufe 1 Agg.5 */
#define XSESPRAMPE52             19740    /* Druckrampe Stufe 2 Agg.5 */
#define XSESPRAMPE53             19741    /* Druckrampe Stufe 3 Agg.5 */
#define XSESPRAMPE54             19742    /* Druckrampe Stufe 4 Agg.5 */
#define XSESPRAMPE55             19743    /* Druckrampe Stufe 5 Agg.5 */
#define XSESPRAMPE56             19744    /* Druckrampe Stufe 6 Agg.5 */
#define XSESPRAMPE57             19745    /* Druckrampe Stufe 7 Agg.5 */
#define XSESPRAMPE58             19746    /* Druckrampe Stufe 8 Agg.5 */
#define XSESPRAMPE59             19747    /* Druckrampe Stufe 9 Agg.5 */
/*-------------------------------------------------------------------------------*/
#define XSSAUS4                  19748    /* */
#define XSVAZUR2                 19749    /* */
#define XSFAUSF2                 19750    /* */
#define XAWSPZUR2                19751    /* */
/*-------------------------------------------------------------------------------*/
/*------------ Rampen fuer Einspritzstufen 10 bis 12 ----------------------------*/
#define XSESVRAMPE1A             19752    /* Geschwindigkeitsrampe Stufe 10 Agg.1 */
#define XSESVRAMPE1B             19753    /* Geschwindigkeitsrampe Stufe 11 Agg.1 */
#define XSESVRAMPE1C             19754    /* Geschwindigkeitsrampe Stufe 12 Agg.1 */
#define XSESVRAMPE2A             19755    /* Geschwindigkeitsrampe Stufe 10 Agg.2 */
#define XSESVRAMPE2B             19756    /* Geschwindigkeitsrampe Stufe 11 Agg.2 */
#define XSESVRAMPE2C             19757    /* Geschwindigkeitsrampe Stufe 12 Agg.2 */
#define XSESVRAMPE3A             19758    /* Geschwindigkeitsrampe Stufe 10 Agg.3 */
#define XSESVRAMPE3B             19759    /* Geschwindigkeitsrampe Stufe 11 Agg.3 */
#define XSESVRAMPE3C             19760    /* Geschwindigkeitsrampe Stufe 12 Agg.3 */
#define XSESVRAMPE4A             19761    /* Geschwindigkeitsrampe Stufe 10 Agg.4 */
#define XSESVRAMPE4B             19762    /* Geschwindigkeitsrampe Stufe 11 Agg.4 */
#define XSESVRAMPE4C             19763    /* Geschwindigkeitsrampe Stufe 12 Agg.4 */
#define XSESVRAMPE5A             19764    /* Geschwindigkeitsrampe Stufe 10 Agg.5 */
#define XSESVRAMPE5B             19765    /* Geschwindigkeitsrampe Stufe 11 Agg.5 */
#define XSESVRAMPE5C             19766    /* Geschwindigkeitsrampe Stufe 12 Agg.5 */
/*-------------------------------------------------------------------------------*/
#define XSESPRAMPE1A             19767    /* Druckrampe Stufe 10 Agg.1 */
#define XSESPRAMPE1B             19768    /* Druckrampe Stufe 11 Agg.1 */
#define XSESPRAMPE1C             19769    /* Druckrampe Stufe 12 Agg.1 */
#define XSESPRAMPE2A             19770    /* Druckrampe Stufe 10 Agg.2 */
#define XSESPRAMPE2B             19771    /* Druckrampe Stufe 11 Agg.2 */
#define XSESPRAMPE2C             19772    /* Druckrampe Stufe 12 Agg.2 */
#define XSESPRAMPE3A             19773    /* Druckrampe Stufe 10 Agg.3 */
#define XSESPRAMPE3B             19774    /* Druckrampe Stufe 11 Agg.3 */
#define XSESPRAMPE3C             19775    /* Druckrampe Stufe 12 Agg.3 */
#define XSESPRAMPE4A             19776    /* Druckrampe Stufe 10 Agg.4 */
#define XSESPRAMPE4B             19777    /* Druckrampe Stufe 11 Agg.4 */
#define XSESPRAMPE4C             19778    /* Druckrampe Stufe 12 Agg.4 */
#define XSESPRAMPE5A             19779    /* Druckrampe Stufe 10 Agg.5 */
#define XSESPRAMPE5B             19780    /* Druckrampe Stufe 11 Agg.5 */
#define XSESPRAMPE5C             19781    /* Druckrampe Stufe 12 Agg.5 */
/*-------------------------------------------------------------------------------*/
#define IOSNDOPA21               19782    /* Sollwerte Parameter 2 S. 66.1 */
#define IOSNDOPA22               19783    /* Sollwerte Parameter 2 S. 66.1 */
#define IOSNDOPA23               19784    /* Sollwerte Parameter 2 S. 66.1 */
#define IOSNDOPA24               19785    /* Sollwerte Parameter 2 S. 66.1 */
#define IOSNDIPAR1               19786    /* Sollwerte Parameter 1 S. 66.0 */
#define IOSNDIPAR2               19787    /* Sollwerte Parameter 1 S. 66.0 */
#define IOSNDIPAR3               19788    /* Sollwerte Parameter 1 S. 66.0 */
#define IOSNDIPAR4               19789    /* Sollwerte Parameter 1 S. 66.0 */
#define IOSNAOPAR1               19790    /* Sollwerte Parameter S. 66.2 */
#define IOSNAOPAR2               19791    /* Sollwerte Parameter S. 66.2 */
#define IOSNAOPAR3               19792    /* Sollwerte Parameter S. 66.2 */
#define IOSNAOPAR4               19793    /* Sollwerte Parameter S. 66.2 */

#endif         /* #ifndef _iscosreg */
