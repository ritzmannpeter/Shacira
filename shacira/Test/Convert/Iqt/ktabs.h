/*.SH.***********************************************************************
*
*  MODUL-NAME: 
*     KTABS.H - DARF  N U R   E I N M A L  EXISTIEREN     
*                                                                    
*  BESCHREIBUNG:                                                     
*     Dieses Headerfile enthaelt die Konstanten zu den Tabellen      
*     KIscosBitTab und KIscosRegTab.                                 
*     Die Konstanten fuer die Bits duerfen sich im Bereich zwischen  
*     1500 und 1999 bewegen, die Konstanten fuer die Register im     
*     Bereich zwischen 15000 und 18999.                              
*                                                                    
*  HISTORY:                                                          
*     09.08.90 -TSchw-  Implementierung                           
*     29.08.90 -TSchw-  KXSPEINR eingefuehrt                      
*     17.12.90 -TSchw-  KXDSUSEI, KXDRADS1, KXDEXRS, KXMSIGEX,    
*                       KXMSSZSP eingefuegt                       
*     25.01.91 -TSchw-  KXTKENG, KXTKWEIT, KXTKTHB eingefuegt     
*     28.02.91 -SF-     KXFMAUS eingebaut                         
*     13.05.91 -MB-     Implementierung Registerpaare             
*                       Aggregat 1 - Aggregat 2                   
*                       Phasenumschaltbits definiert:             
*                       AGG_WEGUMSCHALT_P1 - AGG_WEGUMSCHALT_P5   
*                       AGG_ZEITUMSCHALT_P1 - AGG_ZEITUMSCHALT_P6 
*                       AGG_DRUCKUMSCHALT_P1 - AGG_DRUCKUMSCHALT_P5
*                       fuer Toleranzueberwachung neu definiert:  
*                       AGG_PLAST_TIME_TOL                        
*                       AGG_SWITCH_PRES_TOL                       
*                       AGG_INJ_TIME_TOL                          
*                       AGG_SWITCH_POINT_TOL                      
*                       neu definiert fuer Trenddarstellung       
*                       AGG_PLASTWEG_REF, AGG_INJ_TIME_REF,       
*                       AGG_SWITCH_PRES_REF, AGG_SWITCH_POINT_REF 
*                       AGG_TOL_SELECT definiert                  
*     24.05.91 -SF-     AGG_MP_PLASTWEG neu definiert             
*     07.06.91 -TSchw-  KPROM_ERROR_REG erstellt                  
*     19.06.91 -TSchw-  KXKNUVER, KXKNUTYP eingefuegt             
*     24.06.91 -TSchw-  AGG_INJ_SPEED_MAX, AGG_INJ_SPEED_CONV eing
*     19.11.91 -PR-     Zusaetzliche Register fuer das 10-Stufen- 
*                       Spritzverfahren definiert bzw. vorhandene 
*                       umdefiniert                               
*     30.01.92 -TSchw-  AGG_MAX_SPRITZDRUCK und AGG_HEIZPARAM     
*                       eingefuegt                                
*     31.01.92 -TSchw-  REG_FORM_AUF definiert, damit fuer das    
*                       Register XSSFAUF (FXR) und XSSFOAU (FXA)  
*                       ein einheitlicher Name benutzt werden kann
*     04.02.92 -TSchw-  KXBXWE4R, KXEZHASC neu erstellt, um die   
*                       Doppelverwaltung von Modulen bei FXA zu   
*                       sparen (fuer Mangel 180)                  
*     05.03.92 -TSchw-  AGG_DUES_ANPRDR_MIN eingefuehrt           
*     06.03.92 -PR-     KINJTIME fuer 10-Stufenmodus eingefuehrt  
*     18.09.92 -TSchw-  AGG_WKZINN_IST, AGG_WKZINN_TOL neu ein-   
*                       gefuegt, da Werkzeuginnendruck-Maximalwert
*                       fuer beide Aggregate existiert, laut      
*                       Testbericht FM/2Farben von Herrn Rietsche 
*     21.09.92 -TSchw-  AGG_STAUDRUCK_HAND eingefuegt fuer        
*                       EIQT 01.06.92                             
*     29.09.92 -TSchw-  AGG_POLSTER eingefuegt fuer EIQT 255      
*     10.11.92 -TSchw-  REG_WKZ_POS eingefuegt, damit fuer        
*                       XXSWEG2 (FXR/FM) und XXSPLAT (FXA) ein    
*                       einheitlicher Name verwendet werden kann. 
*     17.11.92 -TSchw-  AGG_DWELL_PRES eingefuegt                 
*     17.11.92 -TSchw-  Die Konstante AGG_ANZ_PLAST_STUF aus dem  
*                       Block USE_ISCOSREG_KLOECK in den Block    
*                       USE_ISCOSREG_KERN verschoben ohne die     
*                       Nummer zu aendern, da dieses Register     
*                       jetzt auch im Kernprogramm verwendet wird.
*     11.01.93 -TSchw-  KXDINART eingefuegt                       
*     10.02.93 -TSchw-  Fuer 10-Stufen-Mode AGG_INJTIME eingefuegt
*     03.05.93 -TSchw-  10-Stufen: AGG_PUV eingefuegt             
*     17.02.94 -MBa-	   AGG_FILL_TIME u. KXMSTILL neu eingefuegt  
*     08.12.95 -HAns-	AGG_SRS_VORPL, AGG_SRV_VORPL,             
*                       AGG_SRS_NACHPL und AGG_SRV_NACHPL neu     
*                       eingefuegt.                               
*                    	AGG_SCREW_CHANGE neu eingefuegt.          
*     25.01.96 -HAns-	AGG_VERZ_VOR und AGG_VERZEINSPR eingef.   
*     12.01.96 -HAns-	AGG_ERHOEH_DREHM eingefuegt.              
*     29.02.96 -HAns-   Folgende Register neu eingefuegt, um die  
*                       Referenzistwert auf Datentr„ger speichern 
*                       zu k”nnen (Forderung Gehring, Rietsche):  
*                       AGG_PLASTZEIT_REF, AGG_WKZINN_REF         
*     20.03.96 -HAns-   AGG_DIAGSPR_SIST bis AGG_DIAGDOS_SPIST    
*                       neu eingefuegt.                           
*     16.04.96 -HAns-   AGG_ZEITAN_AGGRVOR, AGG_ZEITAN_EINSPR und 
*                       AGG_ZEITAN_DOS eingefuegt.                
*                       AGG_ZEITAN4-6 und AGG_ZEITANAVER4-6 einge.
*     30.04.96 -HAns-   Aggregat-Register fuer 87.0 eingefuegt.   
*     02.05.96 -HAns-   Sonderprogramm-Reg auf 87.0 auf Mehrfarbm.
*                       eingefuegt.                               
*     20.05.96 -HAns-   KZEITANREG_SPS, KZEITAN und KZEITANVER    
*                       eingefuegt.                               
*     20.06.96 -HAns-   INJ_PRES_SOLL, INJ_SPEED_SOLL,             
*                       SWITCH_POINT_SOLL, SWITCH_POINT_IST und    
*                       INJ_TIME_IST nicht mehr fuer 10-Stufen-Mode
*                       mit unterschiedlichen Zahlen definiert, da 
*                       dies zu Fehlern gefuehrt hat und sowieso   
*                       unnoetig und gefaehrlich war.              
*     19.07.96 -HAns-   AGG_SPRITZWAHL eingefuegt.
*     27.11.96 -HAns-   AGG_PLGENMOD bis AGG_PLIKDGEST eingefuegt
*     04.12.96 -HAns-   VOL_AGG_PLASTWEG_IST - VOL_SWITCH_POINT_IST und
*                       SPEC_AGG_STAUDRUCK - SPEC_PRES_IST eingefuegt.
*                       SWITCH_VOL_IST und SWITCH_VOL_SOLL herausgenommen,
*                       da nicht benutzt.
*     18.12.96 -TSchw-  Gillette-Sonderprogramm KTab-Register     
*                       GIL_SSONx_AGG eingefuegt.                 
*     24.01.97 -HAns-   VOL_AGG_DREHZAHL und VOL_AGG_DREHZAHL_2 eingefuegt.
*     28.01.97 -HAns-   VOL_AGG_SRV_VORPL, VOL_AGG_SRV_NACHPL und VOL_INJ_SPEED_SOLL
*                       eingefuegt.
*     07.02.97 -HAns-   VOL_AGG_SWITCH_POINT_REF, VOL_AGG_PLASTWEG_REF und 
*                       SPEC_AGG_SWITCH_PRES_REF eingefuegt.
*     06.03.97 -HAns-   AGG_PL_RAMPE eingefuegt.
*     24.07.97 -HAns-   AGG_DIAGDOS_SP2IST - AGG_DIAGSPRDOS_SPIST 
*                       eingefuegt.                               
*     04.02.98 -HAns-   GIL_SSON8_AGG, GIL_SSON9_AGG und GIL_SSONA_AGG
*                       eingefuegt.
*     26.06.98 -HAns-   AGG_DRVST_WEG_AG bis AGG_CONF_SPK_IST eingefuegt.
*     30.06.98 -HAns-   AGG_ACT_STAUDRUCK eingefuegt.
*     08.09.98 -HAns-   AGG_PROC_STEP_UNIT eingefuegt.
*     22.09.98 -GhG-    DWAHL_VERZ bis DWAHL_RAMPE_S5 fuer Airpress mit Rampen-
*                       zeiten eingefuegt.
*     09.02.99 -HAns-   AGG_LVSNEINNADEL_VD bis AGG_LVSTBLASNADEL_VD aufgenommen.
*     09.08.99 -HAns-   AGG_SENSORRANGE und AGG_AUTOSWITCHPOINT aufgenommen.
*     01.02.00 -HAns-   Fuer 6 Farbmaschine angepasst.
*     15.03.00 -HAns-   AGG_SEWEGPKTVOR bis AGG_SEWEGNULLPKT_IST aufgenommen.
*                       AGG_SEABGL_START,RESET und AGG_KPSE_WEG, AGG_MAXSE_WEG
*                       aufgenommen.
*     04.07.00 -GhG-    Erweiterung Airpress mit Rampenzeiten DWAHL_WKZDUES
*     24.10.00 -HAns-   AGG_DUESGEVOR2 eingefuegt.
*     22.11.00 -HAns-   AGG_SESVRAMPE1-9 und AGG_SESPRAMPE1-9 eingefuegt.
*     30.11.00 -HAns-   AGG_SERAMPE eingefuegt.
*     18.12.00 -HAns-   AGG_UMSCHALT_SENSOR eingefuegt.
*     12.02.01 -TSchw-  Register KSPSKEYS1-4 neu erstellt (siehe CLB2001).
*     13.03.01 -GhG-    VOL_INJ_SPEED2_SOLL, VOL_SWITCH_POINT2_SOLL,INJ_SPEED2_SOLL,
*                       SWITCH_POINT2_SOLL
*     29.03.01 -HAns-   ANF_INJ_PRES_SOLL bis ANF_SWITCH_POINT_SOLL eingefuegt.
*     27.04.01 -HAns-   KIWZM_HANF eingefuegt.
*     29.05.01 -HAns-   GIL_SSONB_AGG bis GIL_SSONF_AGG eingefuegt.
*     05.10.01 -HA-     AGG_WEGPUNKT_2, AGG_WEGPUNKT_3, AGG_STAUDRUCK_3, AGG_STAUDRUCK_4, AGG_DREHZAHL_3
*                       und AGG_DREHZAHL_4 eingefuegt.
*                       VOL_AGG_WEGPUNKT_2, _3, VOL_AGG_STAUDRUCK_3, _4 und VOL_AGG_DREHZAHL_3, _4 eingefuegt.
*     10.10.01 -HA-     AGG_INJ_MP03, AGG_SCR_MP01, AGG_SNG_UMDR und AGG_SNGDREHM eingefuegt.
*     11.10.01 -HA-     AGG_SESCHWENKEN eingefuegt.
*     12.10.01 -HA-     AGG_PLC_ANZPLASTSTUFE eingefuegt.
*     29.10.01 -HAns-   AGG_SESVRAMPEA-C und AGG_SESPRAMPEA-C eingefuegt.
*                       AGG_WEGUMSCHALT_P10-P12, AGG_ZEITUMSCHALT_P10-P12 und AGG_DRUCKUMSCHALT_P10-P12
*                       eingefuegt.
*     06.12.01 -HA-     AGG_SEABGL_TASTE eingefuegt.
*     08.02.02 -HA-     AGG_DUES_ANPRDR_IST eingefuegt.
*     14.05.02 -JG-     GIL_SSON10_AGG bis GIL_SSON16_AGG eingefuegt
*     15,05.02 -HA-     AGG_ZYLFG_VERZ_ACT eingefuegt
*     23.05.02 -HA-     KSPSKEYS12 bis KSPSKEYS42 eingefuegt, da KSPSKEYS1 bis KSPSKEYS4 im iqtreg-Bereich liegen.
*     20.08.02 -HA-     AGG_MIN_DUESANLAGEDRUCK und AGG_MAX_DUESANLAGEDRUCK eingefuegt.
*     26.09.02 -HA-     AGG_SNG_DURCHMESSER eingefuegt.
*     05.02.03 -HA-     AGG_PLASTWEG_ANFAHR und VOL_PLASTWEG_ANFAHR eingefuegt.
*     10.03.03 -HA-     INJ_PRES2_SOLL und SPEC_INJ_PRES2_SOLL eingefuegt.
*     03.06.03 -HA-     CYCLE_TIME_IST von 18300 auf 18201 verschoben, sowie AGG_TEXT_DRVMODUL bis AGG_DRVST_BUSSPG_PL
*                       eingefuegt.
*     26.06.03 -HA-     AGG_DIAGDOS2_PIST eingefuegt.
*     15.08.03 -HA-     AGG_DIAGSE_SIST, AGG_DIAGSE_PIST, AGG_DIAGSE_SPIST und AGG_DIAGSE2_SPIST eingefuegt.
*
*  VERSION:                                                          
*     VERSION:  1.0              AUTOR:       T.Schworer             
*     DATUM:    09.08.90         TELEFON 2i:  0721/25785             
*                                                                    
*  UMGEBUNG:                                                         
*     ZIELRECHNER:          Philips IQT-350                          
*     PROGRAMMIERSPRACHE:   C                                        
*                                                                    
*  BEMERKUNGEN:                                                      
*     Die in diesem H-File definierten Konstanten werden teilweise   
*     vom Kernprogramm benutzt. Aus diesem Grund duerfen fuer ALLE   
*     Sonderprogramme und Maschinenversionen KEINERLEI UNTERSCHIEDE  
*     in den Konstanten existieren. Dies kann am besten dadurch      
*     gewaehrleistet werden, dass dieses H-File nur ein einziges Mal 
*     existiert.                                                     
*     Sollte es dennoch noetig sein, in Sonderprogrammen die KTabs zu
*     erweitern, so muss im Sonderprogramm das File KTABS.H dieses   
*     File hier, das sich im COMMON befindet, per #include einbinden.
*     Dieses File hier darf nicht dupliziert werden. Im Sonderpro-   
*     gramm duerfen nur Konstanten definiert werden, die nicht im    
*     Kernprogramm verwendet werden.                                 
*     Um Ueberschreibungen der Standardversionen mit den Sonderpro-  
*     grammen zu vermeiden, sollten folgende Bereich in den Konstan- 
*     ten fuer Sonderprogramme reserviert bleiben:                   
*     Iscosbits:      1500 -  1999                                   
*     Iscosregister: 15000 - 18999                                   
*     Iqtregister:   30000 - 32767                                   
*                                                                    
*****************************************************************************
*                                                                    
*  FUNKTIONEN: keine                                                 
*                                                                    
**.EH.**********************************************************************/

#ifndef ktabs_
#define ktabs_

/*********************************************************************
*
*  Konstanten fuer KIscosBitTab
*
*********************************************************************/
#define KXMIHEIE    1500
#define KXMIMOTE    1501
#define KXMIEXT1    1502
#define KXMIEXT2    1503
#define KXMIHEIA    1504
#define KXMIMOTA    1505
#define KXMIEX1A    1506
#define KXMIEX2A    1507
#define KXMPAUSD    1508
#define KXMXSTDT    1509
#define KXMEINR     1510
#define KXMHAND     1511
#define KXMHALB     1512
#define KXMAUTO     1513
#define KXMI4B6     1514
#define KXMTOLUE    1515
#define KXMSUZER    1516
#define KXMEXTSI    1517
#define KXBXSOLL    1518
#define KXDSUSEI    1519    /* Sub. Schusszaehler ruecksetzen               */
#define KXDRADS1    1520    /* Add. Schusszaehler ruecksetzen               */
#define KXDEXRS     1521    /* Externes Signal reset neustart               */
#define KXMSIGEX    1522    /* Merker um Signal extern zu sperren           */
#define KXMSSZSP    1523    /* Merker um sub. Schusszaehler zu sperren      */
#define KXFMAUS     1524    /* aut. Maschinenabschaltung gesetzt            */
#define KXBXWE4R    1525    /* Blockbit fuer XSSAUS3 (bei FXA leer)         */
#define KXEZHASC    1526    /* Schnellkupplung fuer Auswerfer-Ruhelage HASCO*/
#define KXDINART    1527    /* Enable-Bit der Sollwertuebertragung          */
#define KXMSTILL    1528    /* Stillstandserkennung                         */
#define KIWZM_HANF  1529    /* Werkzeughoehenabgleich anfordern             */

#define AGG_SNEENDLAGE       1530  /* Schneckeendlageregelung               */
#define AGG_HYDRVERSCHLDUESE 1540  /* Hydr. Verschlussduese                 */
#define AGG_WEGUMSCHALT_P1   1550  /* Wegumschaltbit                        */
#define AGG_WEGUMSCHALT_P2   1560
#define AGG_WEGUMSCHALT_P3   1570
#define AGG_WEGUMSCHALT_P4   1580
#define AGG_WEGUMSCHALT_P5   1590
#define AGG_ZEITUMSCHALT_P1  1600  /* Zeitumschaltbit                       */
#define AGG_ZEITUMSCHALT_P2  1610
#define AGG_ZEITUMSCHALT_P3  1620
#define AGG_ZEITUMSCHALT_P4  1630
#define AGG_ZEITUMSCHALT_P5  1640
#define AGG_ZEITUMSCHALT_P6  1650
#define AGG_DRUCKUMSCHALT_P1 1660  /* Druckumschaltbit                      */
#define AGG_DRUCKUMSCHALT_P2 1670
#define AGG_DRUCKUMSCHALT_P3 1680
#define AGG_DRUCKUMSCHALT_P4 1690
#define AGG_DRUCKUMSCHALT_P5 1700
#define AGG_SCREW_CHANGE     1710  /* Schneckenwechsel                      */
#define AGG_ERHOEH_DREHM     1720  /* Erhoehtes Drehmoment                  */
#define AGG_SPRITZWAHL       1730  /* Aggregat Anwahl bei Mehrfarbmaschinen */
#define AGG_PL_RAMPE         1740  /* Plastifizierrampe Ein/Aus             */
/* ---------------- Wegumschaltbit fuer bis 9 Stufen ---------------------- */
#define AGG_WEGUMSCHALT_P6   1750
#define AGG_WEGUMSCHALT_P7   1760
#define AGG_WEGUMSCHALT_P8   1770
#define AGG_WEGUMSCHALT_P9   1780
/* ---------------- Zeitumschaltbit fuer bis 9 Stufen --------------------- */
#define AGG_ZEITUMSCHALT_P7  1790
#define AGG_ZEITUMSCHALT_P8  1800
#define AGG_ZEITUMSCHALT_P9  1810
/* ---------------- Druckumschaltbit fuer bis 9 Stufen -------------------- */
#define AGG_DRUCKUMSCHALT_P6 1820
#define AGG_DRUCKUMSCHALT_P7 1830
#define AGG_DRUCKUMSCHALT_P8 1840
#define AGG_DRUCKUMSCHALT_P9 1850
/* ------------------------------------------------------------------------ */
#define AGG_SEABGL_START     1860
#define AGG_SEABGL_TASTE     1865
#define AGG_SEABGL_RESET     1870
/* ------------------------------------------------------------------------ */
#define AGG_SERAMPE          1880
#define AGG_SESCHWENKEN      1890
/* ---------------- Wegumschaltbit fuer bis 12 Stufen ---------------------- */
#define AGG_WEGUMSCHALT_P10  1900
#define AGG_WEGUMSCHALT_P11  1910
#define AGG_WEGUMSCHALT_P12  1920
/* ---------------- Zeitumschaltbit fuer bis 12 Stufen --------------------- */
#define AGG_ZEITUMSCHALT_P10 1930
#define AGG_ZEITUMSCHALT_P11 1940
#define AGG_ZEITUMSCHALT_P12 1950
/* ---------------- Druckumschaltbit fuer bis 12 Stufen -------------------- */
#define AGG_DRUCKUMSCHALT_P10 1960
#define AGG_DRUCKUMSCHALT_P11 1970
#define AGG_DRUCKUMSCHALT_P12 1980
/* ------------------------------------------------------------------------ */

/*********************************************************************
*
*  Konstanten fuer KIscosRegTab
*
*********************************************************************/
#define KXXNWECO          15000
#define KXXNPASE          15001
#define KXZISSST          15002
#define KXXNSTEP          15003
#define KXSNPHMX          15004
#define KXXTZYKL          15005
#define KXSPEINR          15006
#define KPROM_ERROR_REG   15007
#define KXKNUVER          15008
#define KXKNUTYP          15009
#define KINJTIME          15010
#define KISSCMD           15011
/* ---------------- Register für Crashlogbuch (CLB2001) ------------------- */
#define KSPSKEYS12        15012
#define KSPSKEYS22        15013
#define KSPSKEYS32        15014
#define KSPSKEYS42        15015

/*========== Tabellen mit Heizungs-Fehlerregistern, eindimendional ==========*/
#define KXTKENG           15030
#define KXTKWEIT          15040
#define KXTKTHB           15050
#define AGG_PLASTWEG_ANFAHR 15060

/*======================== Spritzwerttabellen ===============================*/
#define INJ_PRES_SOLL      15100
#define INJ_SPEED_SOLL     15150
#define INJ_TIME_SOLL      15200
#define SWITCH_PRES_SOLL   15250
#define SWITCH_POINT_SOLL  15300
#define PRES_IST           15350
#define INJ_TIME_IST       15400
#define SWITCH_POINT_IST   15450
#define INJ_SPEED2_SOLL    15500
#define SWITCH_POINT2_SOLL 15550

/*======================== Anfahrschaltung ==================================*/
#define ANF_INJ_PRES_SOLL     15600
#define ANF_INJ_SPEED_SOLL    15650
#define ANF_INJ_TIME_SOLL     15700
#define ANF_SWITCH_PRES_SOLL  15750
#define ANF_SWITCH_POINT_SOLL 15800
#define AGG_ANF_PLASTWEG      15850
#define AGG_ANFAHRZYKLEN      15860
#define AGG_ZYLFG_VERZ_ACT    15870
#define INJ_PRES2_SOLL        15880

/* ---------------- SPS-Grenzwert fuer Schneckendurchmesser --------------- */ 
#define AGG_SNG_DURCHMESSER          15960
/* ---------------- Duesenanpressdruck IST -------------------------------- */ 
#define AGG_DUES_ANPRDR_IST          15970
/* ---------------- START Einspritzrampen --------------------------------- */ 
#define AGG_SESVRAMPEA               15980
#define AGG_SESVRAMPEB               15990
#define AGG_SESVRAMPEC               16000
#define AGG_SESPRAMPEA               16010
#define AGG_SESPRAMPEB               16020
#define AGG_SESPRAMPEC               16030
/* ---------------- END Einspritzrampen ----------------------------------- */ 
/* ---------------- Auf 4 Plastifizierstufen erweitert -------------------- */
#define AGG_WEGPUNKT_2               16040
#define AGG_WEGPUNKT_3               16050
#define AGG_DREHZAHL_3               16060
#define AGG_DREHZAHL_4               16070
#define AGG_STAUDRUCK_3              16080
#define AGG_STAUDRUCK_4              16090
/* ------------------------------------------------------------------------ */
#define AGG_PLASTWEG_IST             16100
#define AGG_WEGPUNKT                 16110
#define AGG_DREHZAHL                 16120
#define AGG_DREHZAHL_2               16130
#define AGG_STAUDRUCK                16140
#define AGG_STAUDRUCK_2              16150
#define AGG_RUECKWEG                 16160
#define AGG_RUECKGESCHW              16170
#define AGG_PLASTVERZ                16180
#define AGG_INTRUSION                16190
#define AGG_ANZ_PLAST_STUF           16200    /* Ist auch oben schon definiert */
#define AGG_PLASTWEG                 16210
#define AGG_UMSCHALT                 16220
#define AGG_FUEHL_EMPF               16230
#define AGG_DUESABH_NACH             16240
#define AGG_DUESABH_VERZ             16250
#define AGG_DUESABH_ZEIT             16260
#define AGG_DUES_ANPRDR              16270
#define AGG_PLASTZEITUEBERW          16280
#define AGG_SNERUECKZUG              16290
#define AGG_DUESGEVOR                16300
#define AGG_DUESGEZUR                16310
#define AGG_DUESE_VOR                16320
#define AGG_EINSPRITZEN              16330
#define AGG_DUESABH_80_ZEIT          16340
#define AGG_PLASTZEIT_IST            16350
#define AGG_DUESWEG                  16360
#define REG_FORM_AUF                 16370
#define REG_WKZ_POS                  16380
#define AGG_DUES_ANPRDR_MIN          16390
#define AGG_WKZINN_IST               16400
#define AGG_STAUDRUCK_HAND           16410
#define AGG_POLSTER                  16420

#ifdef MODE_10
	#define AGG_INJTIME              16430
#endif

/* ---------------- Diagnoseseite 17.1 ------------------------------------ */
#define AGG_ZEITAN_AGGRVOR           16440
#define AGG_ZEITAN_EINSPR            16450
#define AGG_ZEITAN_DOS               16460
/* ---------------- Diagnoseseite 17.2 ------------------------------------ */
#define AGG_DIAGSPR_SIST             16470
#define AGG_DIAGDOS_SIST             16480
#define AGG_DIAGSPR_PIST             16490
#define AGG_DIAGDOS_PIST             16500
#define AGG_DIAGSPR_SPIST            16510
#define AGG_DIAGDOS_SPIST            16520
/* ---------------- Diagnoseseite 17.1 ------------------------------------ */
#define KZEITANREG_SPS               16530
/* ---------------- Hier stehen 2-Farben-Register ------------------------- */
#define AGG_PUV                      16540
/* ---------------- Abgleichseite 89.3 ------------------------------------ */
#define AGG_PLGENMOD                 16550
/* ------------------------------------------------------------------------ */
#define AGG_PLSKRAMPE                16560
#define AGG_PLIKARAMPE               16570
#define AGG_PLIKDRAMPE               16580
/* ------------------------------------------------------------------------ */
#define AGG_PLSKGEST                 16590
#define AGG_PLIKAGEST                16600
#define AGG_PLIKDGEST                16610
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
/* ---------------- Diagnoseseite 87.0 ------------------------------------ */
#define AGG_DIAG_SEVOR_FG            16620
#define AGG_DIAG_SEVOR_ST            16630
#define AGG_DIAG_SEVOR_TC            16640
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_SP_FG               16650
#define AGG_DIAG_SP_ST               16660
#define AGG_DIAG_SP_TC               16670
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_IT_FG               16680
#define AGG_DIAG_IT_ST               16690
#define AGG_DIAG_IT_TC               16700
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_PL_FG               16710
#define AGG_DIAG_PL_ST               16720
#define AGG_DIAG_PL_TC               16730
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_SR_FG               16740
#define AGG_DIAG_SR_ST               16750
#define AGG_DIAG_SR_TC               16760
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_LGR_FG              16770
#define AGG_DIAG_LGR_ST              16780
#define AGG_DIAG_LGR_TC              16790
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_SEZUR_FG            16800
#define AGG_DIAG_SEZUR_ST            16810
#define AGG_DIAG_SEZUR_TC            16820
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_SCNW1_FG            16830
#define AGG_DIAG_SCNW1_ST            16840
#define AGG_DIAG_SCNW1_TC            16850
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_SCNW2_FG            16860
#define AGG_DIAG_SCNW2_ST            16870
#define AGG_DIAG_SCNW2_TC            16880
/* ------------------------------------------------------------------------ */
#define AGG_DIAG_SNPRG_FG            16890
#define AGG_DIAG_SNPRG_ST            16900
#define AGG_DIAG_SNPRG_TC            16910
/* ---------------- END Diagnoseseite 87.0 -------------------------------- */
/* ---------------- Diagnoseseite 17.2 ------------------------------------ */
#define AGG_DIAGDOS_SP2IST           16920
#define AGG_DIAGSPRDOS_SIST          16930
#define AGG_DIAGSPRDOS_PIST          16940
#define AGG_DIAGSPRDOS_SPIST         16950
/* ----------------- Drivezustaende Seite 17.2 ---------------------------- */
#define AGG_DRVST_WEG_AG             16960
#define AGG_DRVST_WEG_SP             16970
#define AGG_DRVST_WEG_PL             16980
/* ------------------------------------------------------------------------ */
#define AGG_DRVST_DLAST_AG           16990
#define AGG_DRVST_DLAST_SP           17000
#define AGG_DRVST_DLAST_PL           17010
/* ------------------------------------------------------------------------ */
#define AGG_DRVST_MLAST_AG           17020
#define AGG_DRVST_MLAST_SP           17030
#define AGG_DRVST_MLAST_PL           17040
/* ------------------------------------------------------------------------ */
#define AGG_DRVST_SOLL_AG            17050
#define AGG_DRVST_SOLL_SP            17060
#define AGG_DRVST_SOLL_PL            17070
/* ------------------------------------------------------------------------ */
#define AGG_CONF_SPS_SOLL            17080
#define AGG_CONF_SPS_AKT             17090
#define AGG_CONF_SPS_IST             17100
/* ------------------------------------------------------------------------ */
#define AGG_CONF_SPK_SOLL            17110
#define AGG_CONF_SPK_AKT             17120
#define AGG_CONF_SPK_IST             17130
/* ------------------------------------------------------------------------ */
#define AGG_ACT_STAUDRUCK            17140
/* ---------------- Seite 69.0 Nadelverschlussduese ----------------------- */
#define AGG_LVSNEINNADEL_VD          17150
#define AGG_LVSSPKTNADEL_VD          17160
#define AGG_LVSTVERZNADEL_VD         17170
#define AGG_LVSTBLASNADEL_VD         17180
/* ---------------- Seite 43.0 Kistler SmartAmp Typ 5049A ----------------- */
#define AGG_SENSORRANGE              17190
#define AGG_AUTOSWITCHPOINT          17200
/* ---------------- Seite 49.0 Wegmesssystem fuer Spritzeinheit ----------- */
#define AGG_SEWEGPKTVOR              17210
#define AGG_SEWEGPKTZUR              17220
#define AGG_SEWEGNULLPKT_SOLL        17230
#define AGG_SEWEGNULLPKT_IST         17240
#define AGG_DUESGEVOR2               17250
/* ---------------- Seite 43.0 mit mehreren Werkzeuginnendruckf}hlern ----- */
#define AGG_UMSCHALT_SENSOR          17260
/* ------------------------------------------------------------------------ */
#define AGG_SNG_UMDR                 17270
#define AGG_SNGDREHM                 17280
/* ---------------- Seite 40.0 Anzahl Plastifizierstufen ------------------ */
#define AGG_PLC_ANZPLASTSTUFE        17290
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
/* Spritz- und Nachdruckwerte  10-Stufen-Modus */
#define INJ_PRES_IST                 17300
#define POST_TIME_SOLL               17400
#define POST_PRES_SOLL               17500
#define POLSTER_IST                  17600
#define DOS_TIME_IST                 17700
#define DOS_WAY_IST                  17800
#define SWITCH_TIME_IST              17900
#define SWITCH_PRES_IST              18000
#define SWITCH_TOOL_PRES_IST         18100
#define SWITCH_TOOL_PRES_MAX_IST     18200
#define CYCLE_TIME_IST               18201
/* ---------------- END_MODE_10 ------------------------------------------- */
/* ---------------- Drivestatusseite fuer Evolution Seite 17.3 ------------ */
#define AGG_TEXT_DRVMODUL            18202
#define AGG_TEXT_DRVMOTOR            18208
#define AGG_TEXT_DRVSERIEN_NR        18214
#define AGG_DRVST_MOTORKT_SP         18220
#define AGG_DRVST_MOTORKT_PL         18226
#define AGG_DRVST_LUFTSP_SP          18232
#define AGG_DRVST_LUFTSP_PL          18238
#define AGG_DRVST_FUEHLER_SP         18244
#define AGG_DRVST_FUEHLER_PL         18250
#define AGG_DRVST_BERECH_SP          18256
#define AGG_DRVST_BERECH_PL          18262
#define AGG_DRVST_STROM_SP           18268
#define AGG_DRVST_STROM_PL           18274
#define AGG_DRVST_DREHM_SP           18280
#define AGG_DRVST_DREHM_PL           18286
#define AGG_DRVST_BUSSPG_SP          18292
#define AGG_DRVST_BUSSPG_PL          18298
/* ------------------------------------------------------------------------ */
#define AGG_DIAGDOS2_PIST            18304
#define AGG_DIAGSE_SIST              18310
#define AGG_DIAGSE_PIST              18316
#define AGG_DIAGSE_SPIST             18322
#define AGG_DIAGSE2_SPIST            18328

/* ------------------------------------------------------------------------ */
#define AGG_SRS_VORPL                18400
#define AGG_SRV_VORPL                18410
#define AGG_SRS_NACHPL               18420
#define AGG_SRV_NACHPL               18430
#define AGG_VERZ_VOR                 18440
#define AGG_VERZEINSPR               18450
/* Aggregat-indizierte Register fuer das Gillette Sonderprogramm: */
#define GIL_SSON0_AGG                18460
#define GIL_SSON1_AGG                18470
#define GIL_SSON2_AGG                18480
#define GIL_SSON3_AGG                18490
#define GIL_SSON4_AGG                18500
#define GIL_SSON5_AGG                18510
#define GIL_SSON6_AGG                18520
#define GIL_SSON7_AGG                18530
#define GIL_SSON8_AGG                18540
#define GIL_SSON9_AGG                18550
#define GIL_SSONA_AGG                18560
/* ---------------- Airpress mit Rampenzeiten (Sep. 98) ------------------- */
#define DWAHL_VERZ                   18570
#define DWAHL_AKTION_S1              18580
#define DWAHL_AKTION_S2              18590
#define DWAHL_AKTION_S3              18600
#define DWAHL_AKTION_S4              18610
#define DWAHL_AKTION_S5              18620
#define DWAHL_DRUCK_S1               18630
#define DWAHL_DRUCK_S2               18640
#define DWAHL_DRUCK_S3               18650
#define DWAHL_DRUCK_S4               18660
#define DWAHL_DRUCK_S5               18670
#define DWAHL_RAMPE_S1               18680
#define DWAHL_RAMPE_S2               18690
#define DWAHL_RAMPE_S3               18700
#define DWAHL_RAMPE_S4               18710
#define DWAHL_RAMPE_S5               18720
/* ---------------- END Airpress mit Rampenzeiten (Sep. 98) --------------- */
/* ---------------- Start Erweiterung Airpress mit Rampenzeiten (Juli 2000)- */ 
#define DWAHL_WKZDUES                18730
/* ---------------- END Erweiterung Airpress mit Rampenzeiten (Juli 2000)-- */ 
/* ---------------- START Einspritzrampen --------------------------------- */ 
#define AGG_SESVRAMPE1               18740
#define AGG_SESVRAMPE2               18750
#define AGG_SESVRAMPE3               18760
#define AGG_SESVRAMPE4               18770
#define AGG_SESVRAMPE5               18780
#define AGG_SESVRAMPE6               18790
#define AGG_SESVRAMPE7               18800
#define AGG_SESVRAMPE8               18810
#define AGG_SESVRAMPE9               18820
#define AGG_SESPRAMPE1               18830
#define AGG_SESPRAMPE2               18840
#define AGG_SESPRAMPE3               18850
#define AGG_SESPRAMPE4               18860
#define AGG_SESPRAMPE5               18870
#define AGG_SESPRAMPE6               18880
#define AGG_SESPRAMPE7               18890
#define AGG_SESPRAMPE8               18900
#define AGG_SESPRAMPE9               18910
/* ---------------- END Einspritzrampen ----------------------------------- */ 
#define GIL_SSONB_AGG                18920
#define GIL_SSONC_AGG                18930
#define GIL_SSOND_AGG                18940
#define GIL_SSONE_AGG                18950
#define GIL_SSONF_AGG                18960
#define GIL_SSON10_AGG               18965
#define GIL_SSON11_AGG               18970
#define GIL_SSON12_AGG               18975
#define GIL_SSON13_AGG               18980
#define GIL_SSON14_AGG               18985
#define GIL_SSON15_AGG               18990
#define GIL_SSON16_AGG               18995
/* ---------------- END ISCOS-REGISTER 18999 ------------------------------ */ 

/****************************************************************************
*
* Tabellen mit IQT-Registern fuer Multiplex-Register 
*
****************************************************************************/
#define AGG_REGZUSATZ                30000
#define AGG_FARBZUSATZ               30010
#define AGG_TREIBZUSATZ              30020
#define AGG_MATVORWAERMUNG           30030
#define AGG_MATVORWAERMZEIT          30040
#define AGG_FARBMISCHGER             30050
#define AGG_MATFOERDERGER            30060
#define AGG_SNEZYL                   30070
#define AGG_DUESRADIUS               30080
#define AGG_DUESBOHR                 30090
#define AGG_TAUCHDUES                30100
#define AGG_WECHSELRAD               30110
#define AGG_DRUCK_HYDRMOT            30120
#define AGG_SPRITZZYL                30130
#define AGG_SNEDREHZAHL              30140
#define AGG_GETRIEBE                 30150
#define AGG_SNEDURCHMESS             30160
#define AGG_ANZHEIZZONE              30170
#define AGG_ZYLAUSF                  30180
#define AGG_TEMPABSENKUNG            30190
#define AGG_ANZPLASTSTUFE            30200
#define AGG_FUEHLERART               30210
#define AGG_STIFTDURCHMESS           30220
#define AGG_FUEHLEREMPF              30230
#define AGG_AGGTYP                   30240
#define AGG_AGG_GROESSE              30250
#define AGG_MAX_SNEDREHZ             30260
#define AGG_ZAHNZ_KLEIN              30270
#define AGG_ZAHNZ_MITTEL             30280
#define AGG_ZAHNZ_GROSS              30290
#define AGG_SNEDM_KLEIN              30300
#define AGG_SNEDM_MITTEL             30310
#define AGG_SNEDM_GROSS              30320
#define AGG_PLASTWEG_TOL             30330
#define AGG_PLAST_TIME_TOL           30340
#define AGG_MAX_SPRITZDRUCK          30350
#define AGG_HEIZPARAM                30360
#define AGG_WKZINN_TOL               30370

#define AGG_SWITCH_PRES_TOL          30400
#define AGG_INJ_TIME_TOL             30450
#define AGG_SWITCH_POINT_TOL         30500
#define AGG_PLASTWEG_REF             30550
#define AGG_PLASTZEIT_REF            30560
#define AGG_WKZINN_REF               30570

#define AGG_SWITCH_PRES_REF          30600
#define AGG_INJ_TIME_REF             30650
#define AGG_SWITCH_POINT_REF         30700
#define AGG_TOL_SELECT               30750
#define AGG_MP_PLASTWEG              30760
#define AGG_INJ_SPEED_MAX            30770
#define AGG_FILL_TIME                30780
#define AGG_INJ_SPEED_CONV           30790
#define AGG_DWELL_PRES               30800
                                     
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
#define AGG_SPRKOLBFL                30810
#define AGG_SNEDURCHMESS_S           30820
#define AGG_SPRKOLBFL_S              30830
/* ---------------- END_MODE_10 ------------------------------------------- */
#define AGG_PROC_STEP_UNIT           30840
/* ---------------- Diagnoseseite 17.1 ------------------------------------ */
#define AGG_ZEITAN4                  30850
#define AGG_ZEITAN5                  30860
#define AGG_ZEITAN6                  30870
#define AGG_ZEITANAVER4              30880
#define AGG_ZEITANAVER5              30890
#define AGG_ZEITANAVER6              30900
#define KZEITAN                      30910
#define KZEITANVER                   30920
/* ---------------- END Diagnoseseite 17.1 -------------------------------- */
#define AGG_INJ_MP03                 30930
#define AGG_SCR_MP01                 30940


/* ---------------- Volumen Multiplexreg. --------------------------------- */
#define VOL_AGG_PLASTWEG_IST         31000
#define VOL_AGG_WEGPUNKT             31010
#define VOL_AGG_SRS_VORPL            31020
#define VOL_AGG_SRS_NACHPL           31030
/* ------------------------------------------------------------------------ */
#define VOL_SWITCH_POINT_SOLL        31040
#define VOL_AGG_PLASTWEG_TOL         31090
#define VOL_AGG_SWITCH_POINT_TOL     31140
#define VOL_AGG_PLASTWEG             31190
#define VOL_SWITCH_POINT_IST         31200
#define VOL_AGG_SWITCH_POINT_REF     31250
#define VOL_AGG_PLASTWEG_REF         31300
#define VOL_AGG_WEGPUNKT_2           31310
#define VOL_AGG_WEGPUNKT_3           31320
#define VOL_AGG_DREHZAHL_3           31330
#define VOL_AGG_DREHZAHL_4           31340
/* ---------------- End Volumen Multiplexreg. ----------------------------- */

/* ---------------- spezifische Multiplexreg. ----------------------------- */
#define SPEC_AGG_STAUDRUCK_3         31380
#define SPEC_AGG_STAUDRUCK_4         31390
#define SPEC_AGG_STAUDRUCK           31400
#define SPEC_AGG_STAUDRUCK_2         31410
#define SPEC_AGG_STAUDRUCK_HAND      31420
#define SPEC_INJ_PRES_SOLL           31450
#define SPEC_SWITCH_PRES_SOLL        31500
#define SPEC_AGG_SWITCH_PRES_TOL     31550
#define SPEC_PRES_IST                31600
#define SPEC_AGG_SWITCH_PRES_REF     31650
/* ------------------------------------------------------------------------ */
#define VOL_AGG_DREHZAHL             31700
#define VOL_AGG_DREHZAHL_2           31710
#define VOL_AGG_SRV_VORPL            31720
#define VOL_AGG_SRV_NACHPL           31730
#define VOL_INJ_SPEED_SOLL           31740
/* ---------------- End spezif. Multiplexreg. next is 31790---------------- */

/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
/* ---------------- Toleranzen und Referenzen im 10-Stufen-Modus ---------- */
#define INJ_PRES_REF                 31800
#define INJ_PRES_TOL                 31900
#define POLSTER_REF                  32000
#define POLSTER_TOL                  32010
#define DOS_TIME_REF                 32020
#define DOS_TIME_TOL                 32030
#define DOS_WAY_REF                  32040
#define DOS_WAY_TOL                  32050
#define SWITCH_POINT_REF             32060
#define SWITCH_POINT_TOL             32070
#define SWITCH_TIME_REF              32080
#define SWITCH_TIME_TOL              32090
#define SWITCH_PRES_REF              32100
#define SWITCH_PRES_TOL              32110
#define SWITCH_TOOL_PRES_REF         32120
#define SWITCH_TOOL_PRES_TOL         32130
#define SWITCH_TOOL_PRES_MAX_REF     32140
#define SWITCH_TOOL_PRES_MAX_TOL     32150
#define CYCLE_TIME_REF               32160
#define CYCLE_TIME_TOL               32170
/* ---------------- END_MODE_10 ------------------------------------------- */
/* ---------------- Spritzeinheit Abgleich -------------------------------- */
#define AGG_KPSE_WEG                 32180
#define AGG_MAXSE_WEG                32190
/* ---------------- Register für Crashlogbuch (CLB2001) ------------------- */
#define KSPSKEYS1                    32200
#define KSPSKEYS2                    32201
#define KSPSKEYS3                    32202
#define KSPSKEYS4                    32203
/* ---------------- Register für MIN/MAX Duesenanlagedruck ---------------- */
#define AGG_MIN_DUESANLAGEDRUCK      32204
#define AGG_MAX_DUESANLAGEDRUCK      32210

/* Weg-/Volumen-Register */
#define VOL_INJ_SPEED2_SOLL          32250
#define VOL_SWITCH_POINT2_SOLL       32300
#define VOL_PLASTWEG_ANFAHR          32350
#define SPEC_INJ_PRES2_SOLL           32360
/* Nexter Wert 32410 !!!??? */


#endif   /* #define ktabs_ */
