/************************************************************************
*  Automatic Generation (Symgen):      Thu Mar 10 12:19:03 2005         *
************************************************************************/
/*.SS.***********************************************************************
*
*  BESCHREIBUNG:
*
*  HISTORY:
*     14.09.04 -HA-     SEstUeber, SEipUWMax and SEspUWMax included.
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
*  MODUL-NAME: SYMREG.H  - Definition der Registeradressen und -namen fuer die
*
*  BESCHREIBUNG:
*     ACHTUNG   ACHTUNG  ACHTUNG ACHTUNG  ACHTUNG   ACHTUNG   ACHTUNG
*        Diese Tabelle ist nur fuer die B & R -Steuerung gueltig
*
*  HISTORY:
*     21.10.93 -MBa-    alles nicht benoetigte rausgeschmissen fuer bur
*                       und Ordnung geschaffen
*     27.01.94 -MBa-    rson0 .. rsona Wkz-Auswerfer
*                       rsonb .. rsone Luftventil Programmschalter
*                       Airpress in den Standard
*     11.02.94 -TSchw-  IEndAdr von 0x460 auf 0x468 erhoeht. Durch die zu
*                       niedrige Endadresse wurde im elektrischen Spei-
*                       cherbereich nur Hex 460 Worte allociert. Die
*                       adressmaessig am Ende liegenden SPC-Texte reichen
*                       aber bis 0x468. Beim Lesen dieser Register
*                       (mittels BlockRead(5)) wurde entsprechend um 8
*                       Byte ueber den elektrischen Speicherbereich
*                       hinausgeschrieben. Der darauffolgende Speicher-
*                       block wurde ueberschrieben, was an ganz anderer
*                       Stelle zum Absturz fuehrte.
*     16.02.94 -TSchw-  Nach Rueckportierung vom IQT 450 ins IQT 353
*                       folgende Register neu eingefuegt:
*                       - Fuer Option Atmen und Praegen:
*                         APs_NrStuf und APssPWeg
*                       - Fuer Werkzeugschnellspannen:
*                         WZs_SnSp, xsnsp1 statt rfast1,
*                         xsnsp2 statt rfast2
*                       - Fuer Kernzuege Ausschrauben:
*                         KEs_Arl   KEstAVWo  KEstAVSa  KEstAAAu
*                         KEstAVSAu KEssAWSa  KEs_AZnS  KEs_AUeSb
*                         KEsvAusG  KEspAusD  KEspAusNd KEsvAEinG
*                         KEspAEinD KEspAEinNd
*     22.03.94 -MBa-    tabszyl2 wieder eingefuehrt
*                       HEs_BlOpt Blockoptimierungsreg.  definiert
*                       HEs_SngOpt Singleoptimierungsreg.  definiert
*     07.06.94 -MBa-    Variable fuer Heizung Modul und Kanalnummern
*     08.06.94 -MBa-    snspst neu definiert
*     23.07.96 -HAns-   Standardgrafik-Register definiert.
*     25.07.96 -HAns-   IText_5 neu definiert und Std-Grafik-Reg verschoben
*     29.07.96 -HAns-   IqtDummy, SRSsnach_1,2, SRSvnach_1,2, SRSsvor_1,2 und
*                       SRSvvor_1,2 eingefuegt.
*                       snruek, ssruk1 und svruk1 herausgenommen.
*     23.08.96 -HAns-   WZGenMod bis AWskZGain, sowie WSikOff bis AWikZGain
*                       (Seiten 89.1 bis 89.2) eingefuegt.
*     13-09-96 -PR-     Symboldefinition fuer frei progr.bare Kernzuege (KE..).
*     06.11.96 -HAns-   rinj9 - rinj15 eingefuegt.
*                       iqson30 - iqson68 eingefuegt.
*                       rfast1 -> WZisakt und rfast2 -> IqtSPSTxt umbenannt.
*                       rfast-Register fuer Mehrfarbmaschinen erweitert.
*     27.11.96 -HAns-   PLikARamp1 - PLikDGest2 und PL1GenMod - PLskGest2 
*                       eingefuegt.
*                       diagm37 bis diagm87 eingefuegt.
*                       Nur die FG-Woerter sind ULONG  
*                       (diagm2e, diagm31, diagm34,   
*                        diagm4c, diagm4f, diagm52)
*     28.11.96 -HAns-   SDRitAAufV - SDRitDAufB und SDRGenMod - SDRstAufB
*                       eingefuegt.
*     06.12.96 -HAns-   SEgpUst und SEgpUst2 neu definiert
*     19.12.96 -HAns-   DOsnCard und DOi_Akt neu definiert
*     30.12.96 -HAns-   DIsnCard bis AOsnFor16 und DIi_Akt bis AIinAkt16 definiert.
*     09.01.97 -TSchw-  Gillette-Sonderprogrammregister gil_xson und      
*                       gil_sson eingefuegt.                              
*     13.01.97 -HAns-   SEgpUst3-4, AWgweg, SNgdrehm1-4 eingefuegt.      
*     17.01.97 -HAns-   LVstVerz10 - LVstVerz40 und LVstBlas10 - LVstBlas40 
*                       eingefuegt.
*     30.01.97 -TSchw-  Airpress-Sonderregister /750 - /77d eingefuegt.
*     13.02.97 -TSchw-  Max. Hydraulikdruck eingefuegt und Iwkzschl bis Izykzeit
*                       in den TP_RD_INJ-Bereich verschoben.
*     18.02.97 -TSchw-  Standard/Prozessgrafikregister fuer 4 Farbmaschinen ausgelegt.
*     04.03.97 -HAns-   FPKZandFHK eingefuegt.
*     11.03.97 -HAns-   Iaggrvor2 bis Idos4 eingefuegt.
*     27.10.97 -HAns-   MssppumOff, MGenMod, AktOut8 und MSippumOff eingefuegt.
*                       PLgweg1 bis PLgweg4 und SNg_Umdr1 bis SNg_Umdr4 eingefuegt.
*                       PLsvMess und PLsvOben, sowie PLivAMess bis PLivDOben 
*                       eingefuegt.
*                       SPSCPUType eingefuegt und ClYear bis ClMin verlegt.
*     28.10.97 -HAns-   diagm167 bis diagm16a eingefuegt.
*     29.10.97 -PR-     Kernzug-Programmnummer KEprgno eingefuegt.
*     06.11.97 -PR-     Nummer des Schraubkerns KE_NrSchraub eingefuegt.
*                       Nummer des Wendekerns (KE_NrWend) und Sperrmaske
*                       (KE_SperrMaske) eingefuegt.
*     20.11.97 -HAns-   AktOut6,7,8 in AKT_Dval1,2,3 und AktInp4,5 und AKT_Dval4,5
*                       umbenannt.
*                       Force_6,7 in FOR_Dval1,2 umbenannt.
*                       DOsnCard,DOi_Akt,DIsnCard,DIi_Akt,AOinAkt01 bis 16,
*                       AOsnCard,AOsnFor01 bis 16,AIsnCard und AIinAkt01 bis 16
*                       herausgenommen.
*     25.11.97 -HAns-   DiagMaxMod - DiagModTyp, FDiagDAKT bis FDiagA_F16 aufgenommen.
*     28.11.97 -HAns-   Register der Seiten 87.1 und 87.2 herausgenommen:
*                       Iy8007soll, Iy7019soll, Iy8025soll, IY7008soll, IY8003soll
*                       Ib8007ist, I4b3ist, Iy8007ist, Ib8025ist, Iy7019ist,
*                       Iy8025ist, I5b5ist, Iy7008ist, I5b4ist, Iy8003ist
*                       Folgende Register wurden neu eingefuegt:
*                       FOR_Dval3 bis 7, FOR1Aval01 bis FOR1Aval16, FOR2Aval01
*                       bis FOR2Aval16, AKT_Dval6,7, AKT1Aval01 bis AKT1Aval16,
*                       AKT2Aval01 bis AKT2Aval16
*     05.12.97 -HAns-   DiagModTyp in DiagIndTab umbenannt.
*     26.01.98 -HAns-   OPm_SPSTxt aufgenommen.
*     30.04.98 -HAns-   Define von next_free von 0x700 nach 0x6d0 geaendert.
*     08.06.98 -GhG-    von KS 2.10 Uebernommen
*                       Anpassungen an Elektra
*                       Eingefuegte Register:
*
*                       WZifSichT  -  Wkz-Sicherungskraft Toleranz     
*                       SLipSDRmax -  Schliessdruckspitzenwert S.50                
*                       SPip1Aktue -  Feld 4: spez. Staudruck          Agg.1       
*                       SPip2Aktue -  Feld 4: spez. Staudruck          Agg.2       
*
*                       ZSmnSchmier - IST Schmierintervalle Seite 89.5      
*
*                       WSsbBeschl -  Beschleunigung Werkzeug schliessen S.50  
*                       WOsbBeschl -  Beschleunigung Werkzeug oeffnen S.51     
*                       AWsbVor    -  Beschleunigung Auswerfer vor S.52        
*                       AWsbZur    -  Beschleunigung Auswerfer zurueck S.52    
*                       SEssVerD1  -  40.0 Verschlussduese         SOLL        
*                       MSksSnDur1 -  aktueller Schneckendurchmesser           
*
*                       WOisaktuel -  Werkzeugoefnungsweite fuer Maschinenfaehigkeit
*                       AWisaktuel -  Auswerferweg fuer Maschinenfaehigkeit        
*                       KomMaschF  -  Kommunikations"bit" fuer Maschinenfaehigkeit 
*
*                       AKT3Aval01 -  Analogausgaenge Modul3                  
*                          .. bis ..
*                       AKT3Aval16 -  Analogausgaenge Modul3                  
*
*                       diagm140   -  Maschinenstatus 17.2 Elektra                 
*                          .. bis ..
*                       diagm14e   -  Maschinenstatus 17.2 Elektra                 
*
*                       ------- Diagnose - Register -Elektra ----------
*
*                       MSssOff1   -  89.5 Formoffset                 SOLL
*                       MSssOff2   -  89.5 Auswerferoffset            SOLL
*                       MSssOff3   -  89.5 Einspritzwegoffset 1.Agg   SOLL
*                       MSssOff4   -  89.5 Einspritzwegoffset 2.Agg   SOLL
*                       MSsfOffSP  -  89.5 Einspritzkraftoffset 1.Agg SOLL
*                       MSsfOffSP2 -  89.5 Einspritzkraftoffset 2.Agg SOLL
*                       MSsfOffGK  -  89.5 Gelenkkopfkraftoffset      SOLL
*                       MSskOffET  -  89.5 E-Schrank T.-Offset        SOLL
*                       MSsnHolm   -  89.5 Anzahl Holmdehnungss.      SOLL
*                       MSGenMod   -  89.5 default/RAM/PROM           SOLL
*
*                       ----------- Konfigurationsseite 89.5 ----------
*                       MSisOff1   -  IST Formwegoffset               
*                       MSisOff2   -  IST Auswerferoffset             
*                       MSisOff3   -  IST Einspritzwegoffset 1.Agg
*                       MSisOff4   -  IST Einspritzwegoffset 2.Agg
*                       MSifOffSP  -  IST Einspritzkraftoffset 1.Agg
*                       MSifOffSP2 -  IST Einspritzkraftoffset 2.Agg
*                       MSifOffGK  -  IST Gelenkopfkraftoffset        
*                       MSikOffET  -  IST E-Schrank T.-Offset         
*                       MSinHolm   -  IST Anzahl Holmdehnungss        
*                       SPikKraft  -  IST Einspritzkraftoffset 1.Agg
*                       SPikKraft2 -  IST Einspritzkraftoffset 2.Agg
*                       GKikKraft  -  IST Gelenkkopfkraftoffset       
*                       MSModus    -  Indizierte Texte fuer Justierung
*                       GKikProz   -  IST Gelenkkopfreibung Seite 17.2
*                                
*                       ----- Standarddiagnoseseiten -----------------
*                       AKT_Dval8  -  ULONG Digitaleingaenge  
*                       FOR_Dval8  -  ULONG 
*
*                       FOR3Aval01 -  Analogausgaenge Modul3                 
*                          .. bis ..
*                       FOR3Aval16 -  Analogausgaenge Modul3                 
*
*
*                       Geaenderte Register:
*                       snfetz in SLsnSchm - Einfahrschmierintervall    S.89
*
*                       
*                       Register entfernt:
*                       IMSssK11   -  89.0 Weg1 K1 Konstante ULONG  SOLL
*                       IMSssOff1  -  89.0 Weg1 Offset             SOLL
*                       IMSssK12   -  89.0 Weg2 K1 Konstante ULONG  SOLL
*                       IMSssOff2  -  89.0 Weg2 Offset             SOLL
*                       IMSssK13   -  89.0 Weg3 K1 Konstante ULONG  SOLL
*                       IMSssOff3  -  89.0 Weg3 Offset             SOLL
*                       IMSssK14   -  89.0 Weg4 K1 Konstante ULONG  SOLL
*                       IMSssOff4  -  89.0 Weg4 Offset             SOLL
*                       IDiagOut   -                                   
*                       IGenMod    -  89.0 default/RAM/PROM        SOLL
*                       
*                       IMSisK11   -  89.0 Weg1 K1 Konstante ULONG   IST
*                       IMSisOff1  -  89.0 Weg1 Offset              IST
*                       IMSisK12   -  89.0 Weg2 K1 Konstante ULONG   IST
*                       IMSisOff2  -  89.0 Weg2 Offset              IST
*                       IMSisK13   -  89.0 Weg3 K1 Konstante ULONG   IST
*                       IMSisOff3  -  89.0 Weg3 Offset              IST
*                       IMSisK14   -  89.0 Weg4 K1 Konstante ULONG   IST
*                       IMSisOff4  -  89.0 Weg4 Offset              IST
*                       IMSisAkt1  -  89.0 Weg1 Istwert             IST
*                       IMSisAkt2  -  89.0 Weg2 Istwert             IST
*                       IMSisAkt3  -  89.0 Weg3 Istwert             IST
*                       IMSisAkt4  -  89.0 Weg4 Istwert             IST
*                       IMSinAkt   -  89.0 default/RAM/PROM         IST
*                       IMSinStat  -  89.0 Status                   IST
*                                              
*     16.06.98 -GhG-    Anpassungen fuer zwei Farben
*                       
*                       xsph20     -  Plastifizierweg IST-Wert  Aggregat 2   S.81.1
*                        .. bis ..
*                       xsph25     -  Umschaltpunkt IST-Wert S.41 Agg.2  Stufe 5   
*
*                       xspol2     -  Umschaltpunkt IST-Wert S.41 Agg.2  Stufe 6   
*
*                       xtph21     -  Einspritzzeit IST-Wert S.41 Agg.2  Stufe 1   
*                         .. bis ..
*                       xtph26     -  Einspritzzeit IST-Wert S.41 Agg.2  Stufe 6   
*
*                       xpph21     -  Umschaltdruck IST-Wert S.41 Agg.2  Stufe 1   
*                         .. bis ..
*                       xpph26     -  Umschaltdruck IST-Wert S.41 Agg.2  Stufe 6   
*                                                                     
*
*
*                       stph21     -  Einspritzzeit  S.41  Aggregat 2  Stufe 1     
*                        .. bis ..
*                       stph26     -  Einspritzzeit  S.41  Aggregat 2  Stufe 6     
*                       
*                       ssph21     -  Umschaltpunkt  S.41  Aggregat 2  Stufe 1     
*                        .. bis ..
*                       ssph25     -  Umschaltpunkt  S.41  Aggregat 2  Stufe 5     
*                       
*                       ssum21     -  Wegpunkt  S.40  Aggreagt 2                   
*                       ssdos2     -  Plastifizierweg IST-Wert  S.40 Aggregat 2    
*                       swpl21     -  Drehzahl  S.40  Aggregat 2 Stufe 1           
*                       swpl22     -  Drehzahl  S.40  Aggregat 2 Stufe 2           
*                       spst21     -  Staudruck  S.40  Aggregat 2  Stufe 1         
*                       spst22     -  Staudruck  S.40  Aggregat 2  Stufe 2         
*                       kxempf2    -  Fuehlerempfundlichkeit    S.43   Aggregat 2  
*                       
*                       svph21     -  Einspritzgeschwindigkeit S.41 Agg.2  Stufe 1 
*                        .. bis ..
*                       svph26     -  Einspritzgeschwindigkeit S.41 Agg.2  Stufe 6 
*                       
*                       spum21     -  Umschaltdruck  S.41  Aggregat 2  Stufe 1     
*                        .. bis ..
*                       spum25     -  Umschaltdruck  S.41  Aggregat 2  Stufe 5     
*                       
*                       spph21     -  Einspritzdruck S.41 Aggregat 2 Stufe 1       
*                        .. bis ..
*                       spph26     -  Einspritzdruck S.41 Aggregat 2 Stufe 6       
*                       
*                       snphm2       Anzahl Spritzstufen  S.40  Aggregat 2        
*                       sfagg2       Duesenanpressdruck   S.49  Aggregat 2        
*                       snagg2       Duesenabhebung nach Einspritzen  S.49  Agg.2 
*                       stdues2      Duesenabhebezeit  S.49  Aggregat 2           
*                       svag2v       Duesengeschwindigkeit vor  S.49  Aggregat 2  
*                       svag2z       Duesengeschwindigkeit zurueck  S.49  Agg.2   
*                       
*                       snfin2       Umschaltung mit Wkz-Innendruck S.43  Agg.2   
*                       
*                       xpfi2m       Wkz-Innendruck max. IST-Wert Agg. 2    S.81.2
*                       
*                       SEssVerD2    40.0 Verschlussduese         SOLL  Agg.2 
*                       MSksSnDur2   aktueller Schneckendurchmesser     Agg.2 
*                       
*                       AGstVVer1    Verzoegerungszeit Aggregat 1 vor         
*                       AGstVVer2    Verzoegerungszeit Aggregat 2 vor         
*                       SPstVerz1    Verzoegerungszeit Aggregat 1 Einspritzen 
*                       SPstVerz2    Verzoegerungszeit Aggregat 2 Einspritzen 
*     19.06.98 -HAns-   Ueberarbeitung 
*     21.07.98 -HAns-   Heizungsregister verbessert.
*     21.05.01 -HAns-   KbA0Input - KbA3Input neu eingefuegt
*                       Fast-Register nach Aggregat-Zuordnung sortiert.
*     08.02.02 -HA-     SPif1Anpr, SPif2Anpr eingefuegt
*                       3 und 4 Farb-Register entfernt.
*     13.02.02 -HA-     xspindel, xkniegel, sspinnip, sknienip, AGabhzit und AWkraft eingefuegt.
*     19.02.02 -HA-     SDiagDFOR bis SDiagA_F16 und SDiagDAKT bis SDiagA_A16 eingefuegt.
*     21.02.02 -HA-     Drive-Fehlermeldungsregister aufgenommen.
*     25.03.02 -HA-     MSssOf11,21,31,MSssnPNr, MSinSta, MSinMld und MSisOff11,12,21,22,31,32 eingefuegt.                                         
*     02.04.02 -HA-     IOs_DIfkt1 bis SZinSUB eingefuegt.
*                       IOinAOist1 bis IOinAOist4  eingefuegt.
*     05.04.02 -HA-     Register der Seite 69.0 fuer 5-8 Luftventil eingefuegt.
*     08.04.02 -HA-     IOinDIist und IOinDOist eingefuegt
*     09.04.02 -HA-     BA_foer  Foerderband S. 71.0
*                       FBst     Laufzeit bei getaktetem Betrieb S 71.0 eingefuegt
*     12.04.02 -HA-     Register IqtSSAct eingefuegt.
*                       HZitMess1 bis 4 eingefuegt
*     17.04.02 -HA-     diagm1,4,7,a usw von WORD auf LONG geaendert.
*                       IText6,7 eingefuegt.
*                       WKZss_Vers und WKZis_Vers eingefuegt.
*                       FAST-Register fuer Mehrfarbmaschinen herausgenommen.
*     26.05.02 -HA-     Symboldefinition fuer frei progr.bare Kernzuege (KE..) eingefuegt.
*     27.05.02 -HA-     xspindel, xkniegel, sspinnip, sknienip herausgenommen, da autom. Schmierung eingefuegt.
*                       SLsnSchm als LONG-Register und soelvw herausgenommen.
*     03.06.02 -HA-     HZit_Verz1, HXsnIF, HXsnProto, HXsnBaud,HXsnDatBit,
*                       HXsnStpBit, HXsnParity, HZsnRegNr1 - HZsnRegNr4, HZsnWahl1 - HZsnWahl4
*                       eingefuegt.
*     05.06.02 -HA-     MSippumOff herausgenommen und HZit_Verz1 eingefuegt.
*     17.06.02 -HA-     OPinKarton, OPsnKarton, OPs_Neust eingefuegt.
*     23.07.02 -HA-     SZinSUB wurde verbessert (LONG-Register)
*     24.07.02 -HA-     APd_Type, APd_Mode, APspSysT und APipSysT eingefuegt.
*                       APitUeb1 bis APitUeb4 eingefuegt.
*                       APstRmp1D1 bis APstRmp5D4 und WKZDues_D1 bis WKZDues_D4 eingefuegt.
*     25.07.02 -HA-     WFmpRange1 eingefuegt.
*     23.01.03 -HA-     XSn_Anfa, ssdos1a, spph11a, svph11a, stph11a, ssph11a, spph12a,
*                       svph12a, stph12a, ssph12a, spph13a, svph13a, stph13a, XSn_Anf2a,
*                       spnidra, spnidr2A fuer Produktionsstart S. 40.2 eingefuegt
*     24.01.03 -HA-     ZHs_Wasser eingefuegt.
*     03.06.03 -HA-     TDrvModul11, TDrvModul12, TDrvMotor11, TDrvMotor12, TDrvSerNr11 und
*                       TDrvSerNr12 eingefuegt.
*     27.11.03 -HA-     WZisSich und WZsnFSSRef eingefuegt.
*                       Alte Airpress-Register OPs_XAir bis OPstNach herausgenommen.
*     29.01.04 -HA-     IOs_DIlgk1 bis IOs_DIlgk4 eingefuegt.
*     30.01.04 -HA-     free_reg7 bis free_reg9 herausgenommen.
*     30.06.04 -HA-     Register fuer die Seite 89.2 (KZVTypOffs,KZVenRDInd bis KZs_Vers2 und
*                       KZi_Offs1 bis KZi_Vers2) eingefuegt.
*                       MAi_Offs1 bis MAi_Vers2 eingefuegt.
*                       OPs_Mono bis ZH_Faktor2 eingefuegt.
*                       IqtMIUnit eingefuegt.
*     01.07.04 -HA-     Folgende Register heraugenommen, da der programmierbare Kernzug nicht mehr definiert ist:
*                       ssfzu3; sfzkpt; sfzstp, sfzkp2, ssfau9, sfakpt, sfastp, sfakp2,
*                       sk1ein, sk1aus, sk2ein, sk2aus, sk1eiv, sk1auv, sk2eiv, sk2auv,
*                       snk1ei, snk1au, snk2ei, snk2au, stk1ei, stk1au, stk2ei, stk2au,
*                       keinsi
*     02.07.04 -HA-     xpfi2m, xsph20-2c, xtph21-2c, xpph21-2c und
*                       Iaggrvor2, Ieinspr2, Idos2  entfernt.
*                       MSssOff8, MSisOff8 und MSisOff83 eingefuegt.
*     03.07.04 -HA-     OPm_HoSens eingefuegt (Optionbit in a new visu it's possible change it to symbit.h)
*     03.08.04 -HA-     SetStrPlst12 bis SetStrPlst15, SetSpdPlst13 bis SetSpdPlst15, 
*                       SetPrsPlst13 bis SetPrsPlst15 eingefügt.
*                       SetStrPlst22 bis SetStrPlst25, SetSpdPlst23 bis SetSpdPlst25, 
*                       SetPrsPlst23 bis SetPrsPlst25 eingefügt.
*     10.08.04 -HA-     xtkuhl eingefuegt, Symboltabellen fuer Mosaic angepasst.
*     11.08.04 -HA-     SetCntClpMoldProtectStages, SetStrClpMoldProtect2,3, SetFceClpMoldProtectTol2,3,
*                       SetCfgPlstStages1, SetStrPlst12, 13, 14, 15
*                       SetSpdPlst13, 14, 15, SetPrsPlst13, 14, 15, SetVelClpMoldProtect2,3 included
*                       SetCntEjeForwardStages und SetCntEjeBackStages included
*                       ActStrClpMoldProtect2,3, ActTimClpMoldProtect2,3, ActFceClpMoldProtectTol2,3,
*                       ActDescTempMod11 to ActDescTempMod83 included
*     12.08.04 -HA-     SetVelEjeBack2, SetStrEjeBack1,2 included
*     24.08.04 -HA-     ActStsMachKbA4 und ActStsMachA4Inp included
*	  20.01.05 -WT-		ActDescTempMod11 to ActDescTempMod83 removed,
*						HZs_CfgReg, HZi_CfgReg, HZmt_Conf, HZmh_Conf, HZmk_Conf added
*     04.03.05 -SE-     Iaggrzur,Inchdrck,Iwkzschl_st,Iwkzsich_st,Ischldraufb_st,Ieinspr_st,Idos_st, 
*                       Ikuehl_st, Iwkzoeffn_stIauswvor_st, Iauswzur_st, Ipauszeit_st,Iaggrzur_st, Inchdrck_st
*     09.03.05 -SE-     Ischldrabb_st, Ischldrabb_st
*     10.03.05 -HA-     LVis_Strt1-8 und LVis_End1-8 eingefuegt.
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
*  FUNKTIONEN: keine
*
**.EM.**********************************************************************/

/* ------------------------------------------------------------------------ */
/* $$$ schnelle Istwertregister (TP_RD_FAST)                                */
/* ------------------------------------------------------------------------ */
#define xsweg1     0x40   /*  Feld 1: Position Schnecke        Agg. 1 ULONG  */
#define xtdos1     0x42   /*  Feld 2: Plastifizierzeit S.81.1  Agg. 1 ULONG  */
#define xwdre1     0x44   /*  Feld 3: Schneckendrehzahl        Agg. 1       */
#define SPip1Aktue 0x45   /*  Feld 4: spez. Staudruck          Aggregat 1   */
#define xsweg2     0x46   /*  Feld 7: Position Form-platten           ULONG  */
#define xtzykl     0x48   /*  Zykluszeit     IST-Wert  S.81.2         ULONG  */
#define xnstep     0x4a   /*  Feld11: IST-Zyklusstepzaehler    Agg. 1       */
#define xnpase     0x4b   /*  Feld11: IST-Zyklusphasenzaehler  Agg. 1       */
#define xfzuhk     0x4c   /*  Schliesskraft  IST-Wert  S.50                 */
#define xsweg4     0x4d   /*  Nullpunktabgleich Auswerfer IST-Wert  S.52 ULONG  */
#define xnahub     0x4f   /*  Anzahl Auswerferhuebe  IST-Wert  S.52         */
#define ActTimClpMoldProtect1 0x50   /* Time Mold protect 1 */
#define ActTimClpMoldProtect2 0x51   /* Time Mold protect 2 */
#define ActTimClpMoldProtect3 0x52   /* Time Mold protect 3 */
#define xnfss      0x53   /*  Wiederholung Werkzeugsicherung  IST-Wert S.50 */
#define IqtSPSTxt  0x54   /*  SPSText Auswahlregister                       */
#define xtkuhl     0x55   /*  IST-Wert Kuehlzeit  S.40                      */
#define KbA0Input  0x56   /*  Kumulierte SPS-Tasten fuer Crashlogbuch       */
#define KbA1Input  0x57   /*  Kumulierte SPS-Tasten fuer Crashlogbuch       */
#define KbA2Input  0x58   /*  Kumulierte SPS-Tasten fuer Crashlogbuch       */
#define KbA3Input  0x59   /*  Kumulierte SPS-Tasten fuer Crashlogbuch       */
#define ActStsMachKbA4 0x5a   /*  Kumulierte SPS-Tasten fuer Crashlogbuch       */
#define IOinDIist  0x5b   /*  Aktwerte  S. 66.0  */
#define IOinDOist  0x5c   /*  Aktwerte  S. 66.1  */
#define IOinAOist1 0x5d   /*  Aktwerte  S. 66.2  */
#define IOinAOist2 0x5e   /*  Aktwerte  S. 66.2  */
#define IOinAOist3 0x5f   /*  Aktwerte  S. 66.2  */
#define IOinAOist4 0x60   /*  Aktwerte  S. 66.2  */
/* ------------------ Maschinenfaehigkeit --------------------------------- */
#define WOisaktuel 0x61   /*  Werkzeugoefnungsweite fuer Maschinenfaehigkeit */
/* ------------------ fuer Elektra ---------------------------------------- */
#define WZifSichT  0x62   /*  Wkz-Sicherungskraft Toleranz                  */
#define ActFceClpMoldProtectTol2 0x63   /* Force Clamp Mold protect 2 */
#define ActFceClpMoldProtectTol3 0x64   /* Force Clamp Mold protect 3 */
#define WZisSich   0x65   /*  Start Werkzeugsicherung 1                     */
#define ActStrClpMoldProtect2 0x66   /* Stroke Mold protect 2  */
#define ActStrClpMoldProtect3 0x67   /* Stroke Mold protect 3  */
#define SPif1Anpr  0x68   /*  S.49 Duesenanpresskraft          Aggregat 1   */
#define WKZis_Vers 0x69   /*  S.50 Werkzeughoehenverstellung                */
#define OPinKarton 0x6a   /*  S.71 Anzahl Teile pro Karton                  */
/* ------------------------------------------------------------------------ */
#define SEipUWMax  0x6b   /*      SPECIAL  Act monitoring ressure            */
/* ------------------------------------------------------------------------ */
#define xtnidr     0x6c   /*  Ueberwachungszeit Wkz-Sicherung IST-Wert S.50 */
#define xkoel      0x6d   /*  Feld 5: Oeltemperatur                         */
#define xnweco     0x6e   /*  Werkzeugnummer IST-Wert  S.21                 */
#define xnmaco     0x6f   /*  Maschinennummer an IQT                        */
#define xkperr     0x70   /*  Kundenpromfehlerregister                      */
#define WZisakt    0x71   /*  Werkzeugweg Istposition                       */
#define OPm_SPSTxt 0x72   /*  Options SPSTextauswahlregister                */
#define IqtSSAct   0x73   /*  Aktuelle Schluesselschalterstellung von der SPS  */
#define SEisNlpkt1 0x74   /*  Spritzeinheit 1 Wegpunkt Seite 49.0           */
#define SEipDAnpr1 0x75   /*  Spritzeinheit 1 Anpressdruck Seite 49.0       */
#define APipSysT   0x76   /*  Option Airpress Anlagedruck                   */
#define AWisaktuel 0x77   /*  Auswerferweg fuer Maschinenfaehigkeit         */
#define KomMaschF  0x78   /*  Kommunikationsbit fuer Maschinenfaehigkeit  */
#define SLipSDRmax 0x79   /*  Schliessdruckspitzenwert S.50                 */
/* ------------------------------------------------------------------------ */
#define rfast1     0x7a   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast2     0x7b   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast3     0x7c   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast4     0x7d   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast5     0x7e   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast6     0x7f   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast7     0x80   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast8     0x81   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast9     0x82   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast10    0x83   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast11    0x84   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast12    0x85   /*  Sonderregister fuer schnelle Istwerte         */
#define rfast13    0x86   /*  Sonderregister fuer schnelle Istwerte         */
#define ALIGNMENTREG1 0x87   /*  Reserve 1 (9 Register) */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
#define StartInjValues 0x90   /*  Start Injection Variables */
/* ------------------- ISTWERT Wkz-Innendruck S.81.2 ---------------------- */
#define xpfinm     0x90   /*  Aggregat 1                                    */
/* ------------------- ISTWERT Plastifizierweg S.41/S.42 ------------------ */
#define xsph10     0x91   /*  Aggregat 1                                    */
#define xsph11     0x92   /*  Aggregat 1  Stufe 1                           */
#define xsph12     0x93   /*  Aggregat 1  Stufe 2                           */
#define xsph13     0x94   /*  Aggregat 1  Stufe 3                           */
#define xsph14     0x95   /*  Aggregat 1  Stufe 4                           */
#define xsph15     0x96   /*  Aggregat 1  Stufe 5                           */
#define ActStrInj16 0x97   /*  Injection stroke unit 1 stage 6               */
#define ActStrInj17 0x98   /*  Injection stroke unit 1 stage 7               */
#define ActStrInj18 0x99   /*  Injection stroke unit 1 stage 8               */
#define ActStrInj19 0x9a   /*  Injection stroke unit 1 stage 9               */
#define ActStrInj1a 0x9b   /*  Injection stroke unit 1 stage 10              */
/* ------------------- ISTWERT Einspritzzeit S.41/S.42 -------------------- */
#define xtph11     0x9c   /*  Aggregat 1  Stufe 1                           */
#define xtph12     0x9d   /*  Aggregat 1  Stufe 2                           */
#define xtph13     0x9e   /*  Aggregat 1  Stufe 3                           */
#define xtph14     0x9f   /*  Aggregat 1  Stufe 4                           */
#define xtph15     0xa0   /*  Aggregat 1  Stufe 5                           */
#define xtph16     0xa1   /*  Aggregat 1  Stufe 6                           */
#define ActTimInj17 0xa2   /*  Injection time unit 1 stage 7                 */
#define ActTimInj18 0xa3   /*  Injection time unit 1 stage 8                 */
#define ActTimInj19 0xa4   /*  Injection time unit 1 stage 9                 */
#define ActTimInj1a 0xa5   /*  Injection time unit 1 stage 10                */
/* ------------------- ISTWERT Einspritzdruck S.41/S.42 ------------------- */
#define xpph11     0xa6   /*  Aggregat 1  Stufe 1                           */
#define xpph12     0xa7   /*  Aggregat 1  Stufe 2                           */
#define xpph13     0xa8   /*  Aggregat 1  Stufe 3                           */
#define xpph14     0xa9   /*  Aggregat 1  Stufe 4                           */
#define xpph15     0xaa   /*  Aggregat 1  Stufe 5                           */
#define xpph16     0xab   /*  Aggregat 1  Stufe 6                           */
#define ActPrsInj17 0xac   /*  Injection pressure unit 1 stage 7             */
#define ActPrsInj18 0xad   /*  Injection pressure unit 1 stage 8             */
#define ActPrsInj19 0xae   /*  Injection pressure unit 1 stage 9             */
#define ActPrsInj1a 0xaf   /*  Injection pressure unit 1 stage 10            */
/* ---------------- Cushion injection unit 1 ------------------------------ */
#define ActStrInjCushion1 0xb0   /*  Injection stroke cushion unit 1           */
/* ---------------- 15 Reserve - Register  mit TP_RD_INJ ------------------ */
#define rinj1      0xb1   /*  Reserveregister fuer Spritzistwerte           */
#define rinj2      0xb2   /*  Reserveregister fuer Spritzistwerte           */
#define rinj3      0xb3   /*  Reserveregister fuer Spritzistwerte           */
#define rinj4      0xb4   /*  Reserveregister fuer Spritzistwerte           */
#define rinj5      0xb5   /*  Reserveregister fuer Spritzistwerte           */
#define rinj6      0xb6   /*  Reserveregister fuer Spritzistwerte           */
#define rinj7      0xb7   /*  Reserveregister fuer Spritzistwerte           */
#define rinj8      0xb8   /*  Reserveregister fuer Spritzistwerte           */
#define rinj9      0xb9   /*  Reserveregister fuer Spritzistwerte           */
#define rinj10     0xba   /*  Reserveregister fuer Spritzistwerte           */
#define rinj11     0xbb   /*  Reserveregister fuer Spritzistwerte           */
#define rinj12     0xbc   /*  Reserveregister fuer Spritzistwerte           */
#define rinj13     0xbd   /*  Reserveregister fuer Spritzistwerte           */
#define rinj14     0xbe   /*  Reserveregister fuer Spritzistwerte           */
#define rinj15     0xbf   /*  Reserveregister fuer Spritzistwerte           */
/* ---------------- Qualitaetskontrolle ----------------------------------- */
#define QUinanz1   0xc0   /*  Ausschuss nach Automatikstart                 */
#define QUinanz2   0xc1   /*  Ausschuss nach Stoerung                       */
#define QUinanz3   0xc2   /*  Stichprobe                                    */
#define QUinanz4   0xc3   /*  Pruefteil nach Stoerung                       */
#define EndInjValues 0xc4   /*  End Injection Variables */
/* ---------------- Heizung Kanalbenennung -------------------------------- */
#define HZ_CurReg  0xc4   /*  aktueller Regler auf Seite 39.1               */
#define HZ_TempMod 0xc5   /*  Fuehler Modul                                 */
#define HZ_TempKan 0xc6   /*  Fuehler Kanal                                 */
#define HZ_HeizMod 0xc7   /*  Heizausgangsmodul                             */
#define HZ_HeizKan 0xc8   /*  Heizausgangskanal                             */
#define HZ_KuelMod 0xc9   /*  Kuehlausgangsmodul                            */
#define HZ_KuelKan 0xca   /*  Kuehlausgangskanal                            */
/* ------------------------------------------------------------------------ */
#define SPIpHydMax 0xcb   /*  Hydraulik Druck max. IST-Wert          S.81.2 */
/* ---------------- Airpress ---------------------------------------------- */
#define APitUeb1   0xcc   /*  Airpress Ueberwachungszeit 1                  */
#define APitUeb2   0xcd   /*  Airpress Ueberwachungszeit 2                  */
#define APitUeb3   0xce   /*  Airpress Ueberwachungszeit 3                  */
#define APitUeb4   0xcf   /*  Airpress Ueberwachungszeit 4                  */
/* ------------------------------------------------------------------------ */
#define Iwkzschl   0xd0   /*  Zeit Werkzeug schliessen IST             */
#define Iwkzsich   0xd1   /*  Zeit Werkzeug Sicherung  IST             */
#define Ischldraufb 0xd2   /*  Zeit Schliessdruckaufbau IST             */
#define Iaggrvor   0xd3   /*  Zeit Aggregat vor        IST             */
#define Ieinspr    0xd4   /*  Zeit Einspritzen         IST             */
#define Idos       0xd5   /*  Zeit Dosieren            IST             */
#define Ikuehl     0xd6   /*  Kuehlzeit                IST             */
#define Iwkzoeffn  0xd7   /*  Zeit Werkzeug oeffnen    IST             */
#define Iauswvor   0xd8   /*  Zeit Auswerfer vor       IST             */
#define Iauswzur   0xd9   /*  Zeit Auswerfer zurueck   IST             */
#define Ipauszeit  0xda   /*  Pausenzeit               IST             */
#define Izykzeit   0xdb   /*  Zykluszeit         ULONG  IST             */
#define Iaggrzur   0xdd   /*  Zeit Aggregat zurück     IST             */
#define Inchdrck   0xde   /*  Zeit Nachdruck           IST             */
#define Ischldrabb 0xdf   /*  Zeit Schließdruckabbau   IST             */
#define Iwkzschl_st 0xe0   /*  Zeit start Werkzeug schliessen IST       */
#define Iwkzsich_st 0xe1   /*  Zeit start Werkzeug Sicherung  IST       */
#define Ischldraufb_st 0xe2   /*  Zeit start Schliessdruckaufbau IST      */
#define Iaggrvor_st 0xe3   /*  Zeit start Aggregat vor        IST       */
#define Ieinspr_st 0xe4   /*  Zeit start Einspritzen         IST       */
#define Idos_st    0xe5   /*  Zeit start Dosieren            IST       */
#define Ikuehl_st  0xe6   /*  start Kuehlzeit                IST       */
#define Iwkzoeffn_st 0xe7   /*  Zeit start Werkzeug oeffnen    IST       */
#define Iauswvor_st 0xe8   /*  Zeit start Auswerfer vor       IST       */
#define Iauswzur_st 0xe9   /*  Zeit start Auswerfer zurueck   IST       */
#define Ipauszeit_st 0xea   /*  start Pausenzeit               IST       */
#define Iaggrzur_st 0xeb   /*  Zeit start Aggregat zurück     IST       */
#define Inchdrck_st 0xec   /*  Zeit start Nachdruck           IST       */
#define Ischldrabb_st 0xed   /* Zeit Schliesdruckabbau          IST       */
#define ALIGNMENTREG2 0xee   /*  Reserve 2 (2 Register) */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
#define xksr01     0xf0   /*  Stromistwert eines Temperaturreglers          */
#define xksr02     0xf1   /*  Stromistwert eines Temperaturreglers          */
#define xksr03     0xf2   /*  Stromistwert eines Temperaturreglers          */
#define xksr04     0xf3   /*  Stromistwert eines Temperaturreglers          */
#define xksr05     0xf4   /*  Stromistwert eines Temperaturreglers          */
#define xksr06     0xf5   /*  Stromistwert eines Temperaturreglers          */
#define xksr07     0xf6   /*  Stromistwert eines Temperaturreglers          */
#define xksr08     0xf7   /*  Stromistwert eines Temperaturreglers          */
#define xksr09     0xf8   /*  Stromistwert eines Temperaturreglers          */
#define xksr10     0xf9   /*  Stromistwert eines Temperaturreglers          */
#define xksr11     0xfa   /*  Stromistwert eines Temperaturreglers          */
#define xksr12     0xfb   /*  Stromistwert eines Temperaturreglers          */
#define xksr13     0xfc   /*  Stromistwert eines Temperaturreglers          */
#define xksr14     0xfd   /*  Stromistwert eines Temperaturreglers          */
#define xksr15     0xfe   /*  Stromistwert eines Temperaturreglers          */
#define xksr16     0xff   /*  Stromistwert eines Temperaturreglers          */
#define xker01     0x100  /*  ED-Wert eines Temperaturreglers               */
#define xker02     0x101  /*  ED-Wert eines Temperaturreglers               */
#define xker03     0x102  /*  ED-Wert eines Temperaturreglers               */
#define xker04     0x103  /*  ED-Wert eines Temperaturreglers               */
#define xker05     0x104  /*  ED-Wert eines Temperaturreglers               */
#define xker06     0x105  /*  ED-Wert eines Temperaturreglers               */
#define xker07     0x106  /*  ED-Wert eines Temperaturreglers               */
#define xker08     0x107  /*  ED-Wert eines Temperaturreglers               */
#define xker09     0x108  /*  ED-Wert eines Temperaturreglers               */
#define xker10     0x109  /*  ED-Wert eines Temperaturreglers               */
#define xker11     0x10a  /*  ED-Wert eines Temperaturreglers               */
#define xker12     0x10b  /*  ED-Wert eines Temperaturreglers               */
#define xker13     0x10c  /*  ED-Wert eines Temperaturreglers               */
#define xker14     0x10d  /*  ED-Wert eines Temperaturreglers               */
#define xker15     0x10e  /*  ED-Wert eines Temperaturreglers               */
#define xker16     0x10f  /*  ED-Wert eines Temperaturreglers               */
#define xkir01     0x110  /*  IST-Werte eines Temperaturreglers             */
#define xkir02     0x111  /*  IST-Werte eines Temperaturreglers             */
#define xkir03     0x112  /*  IST-Werte eines Temperaturreglers             */
#define xkir04     0x113  /*  IST-Werte eines Temperaturreglers             */
#define xkir05     0x114  /*  IST-Werte eines Temperaturreglers             */
#define xkir06     0x115  /*  IST-Werte eines Temperaturreglers             */
#define xkir07     0x116  /*  IST-Werte eines Temperaturreglers             */
#define xkir08     0x117  /*  IST-Werte eines Temperaturreglers             */
#define xkir09     0x118  /*  IST-Werte eines Temperaturreglers             */
#define xkir10     0x119  /*  IST-Werte eines Temperaturreglers             */
#define xkir11     0x11a  /*  IST-Werte eines Temperaturreglers             */
#define xkir12     0x11b  /*  IST-Werte eines Temperaturreglers             */
#define xkir13     0x11c  /*  IST-Werte eines Temperaturreglers             */
#define xkir14     0x11d  /*  IST-Werte eines Temperaturreglers             */
#define xkir15     0x11e  /*  IST-Werte eines Temperaturreglers             */
#define xkir16     0x11f  /*  IST-Werte eines Temperaturreglers             */
#define xkgwpw     0x120  /*  Toleranzfehler positiv weit, alle 16 Regler   */
#define xkgwpe     0x121  /*  Toleranzfehler positiv eng,  alle 16 Regler   */
#define xkgwne     0x122  /*  Toleranzfehler negativ eng,  alle 16 Regler   */
#define xkgwnw     0x123  /*  Toleranzfehler negativ weit, alle 16 Regler   */
#define tkxthb     0x124  /*  Fuehlerbruch, alle 16 Regler                  */
#define xkblnr     0x125  /*  Istwertblock-Nummer                           */
/* --------- Register fuer Seite 35.0 ------------------------------------ */
#define HZitMess1  0x126  /*  Messwert  */
#define HZitMess2  0x127  /*  Messwert  */
#define HZitMess3  0x128  /*  Messwert  */
#define HZitMess4  0x129  /*  Messwert  */
#define ALIGNMENTREG3 0x12a  /*  Reserve 3 (5 Register) */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
#define IOs_DIfkt1 0x130  /*  Sollwerte Funktion S. 66.0  */
#define IOs_DIfkt2 0x131  /*  Sollwerte Funktion S. 66.0  */
#define IOs_DIfkt3 0x132  /*  Sollwerte Funktion S. 66.0  */
#define IOs_DIfkt4 0x133  /*  Sollwerte Funktion S. 66.0  */
#define IOs_DIlgk1 0x134  /*  Sollwerte Freigabelogik S. 66.0  */
#define IOs_DIlgk2 0x135  /*  Sollwerte Freigabelogik S. 66.0  */
#define IOs_DIlgk3 0x136  /*  Sollwerte Freigabelogik S. 66.0  */
#define IOs_DIlgk4 0x137  /*  Sollwerte Freigabelogik S. 66.0  */
#define IOsnDIpar1 0x138  /*  Sollwerte Parameter S. 66.0  */
#define IOsnDIpar2 0x139  /*  Sollwerte Parameter S. 66.0  */
#define IOsnDIpar3 0x13a  /*  Sollwerte Parameter S. 66.0  */
#define IOsnDIpar4 0x13b  /*  Sollwerte Parameter S. 66.0  */
#define IOs_DOfkt1 0x13c  /*  Sollwerte Funktion S. 66.1  */
#define IOs_DOfkt2 0x13d  /*  Sollwerte Funktion S. 66.1  */
#define IOs_DOfkt3 0x13e  /*  Sollwerte Funktion S. 66.1  */
#define IOs_DOfkt4 0x13f  /*  Sollwerte Funktion S. 66.1  */
#define IOstDOakt1 0x140  /*  Sollwerte Aktionszeit S. 66.1  */
#define IOstDOakt2 0x141  /*  Sollwerte Aktionszeit S. 66.1  */
#define IOstDOakt3 0x142  /*  Sollwerte Aktionszeit S. 66.1  */
#define IOstDOakt4 0x143  /*  Sollwerte Aktionszeit S. 66.1  */
#define IOsnDOpar1 0x144  /*  Sollwerte Parameter S. 66.1  */
#define IOsnDOpar2 0x145  /*  Sollwerte Parameter S. 66.1  */
#define IOsnDOpar3 0x146  /*  Sollwerte Parameter S. 66.1  */
#define IOsnDOpar4 0x147  /*  Sollwerte Parameter S. 66.1  */
#define IOsnDOpa21 0x148  /*  Sollwerte Parameter 2 S. 66.1  */
#define IOsnDOpa22 0x149  /*  Sollwerte Parameter 2 S. 66.1  */
#define IOsnDOpa23 0x14a  /*  Sollwerte Parameter 2 S. 66.1  */
#define IOsnDOpa24 0x14b  /*  Sollwerte Parameter 2 S. 66.1  */
#define IOs_AOfkt1 0x14c  /*  Sollwerte Funktion S. 66.2  */
#define IOs_AOfkt2 0x14d  /*  Sollwerte Funktion S. 66.2  */
#define IOs_AOfkt3 0x14e  /*  Sollwerte Funktion S. 66.2  */
#define IOs_AOfkt4 0x14f  /*  Sollwerte Funktion S. 66.2  */
#define IOsnAOpar1 0x150  /*  Sollwerte Parameter S. 66.1  */
#define IOsnAOpar2 0x151  /*  Sollwerte Parameter S. 66.1  */
#define IOsnAOpar3 0x152  /*  Sollwerte Parameter S. 66.1  */
#define IOsnAOpar4 0x153  /*  Sollwerte Parameter S. 66.1  */
#define SZinSUB    0x154  /*  LONG subtrahierender Schusszaehler 1,14f  */
#define WKZss_Vers 0x156  /*  S.50 Werkzeughoehenverstellung                */
#define Ax0ec      0x157  /*  Anfahrdauer         S.32 Zeile 7              */
#define Ax0ed      0x158  /*  Anfahrtemperatur    S.32 Zeile 8              */
#define Ax0ee      0x159  /*  Leistungsbegrenzung S.32 Zeile 9              */
#define ssfzu1     0x15a  /*  Wegpunkt fuer Stufe 1      S.50               */
#define ssfzu2     0x15b  /*  Start Werkzeugsicherung 1  S.50               */
#define SetStrClpMoldProtect2 0x15c  /* Mold protect stage 2 */
#define SetStrClpMoldProtect3 0x15d  /* Mold protect stage 3 */
#define ssfzu      0x15e  /*  Werkzeugeinbauhoehe      S.50                 */
#define ssfau1     0x15f  /*  Wegpunkt Stufe 1         S.51                 */
#define ssfau2     0x160  /*  Wegpunkt Stufe 2         S.51                 */
#define ssfau3     0x161  /*  erhoehte Oeffnungskraft bei Wegpunkt  S.51    */
#define ssfau4     0x162  /*  Start Auswerfer vor                   S.52    */
#define ssfau5     0x163  /*  Wegpunkt Ventil Y9027     S.69                */
#define ssfau6     0x164  /*  Wegpunkt Ventil Y9028     S.69                */
#define ssfau7     0x165  /*  Wegpunkt Ventil Y9029     S.69                */
#define ssfau8     0x166  /*  Wegpunkt Ventil Y9030     S.69                */
#define ssfauf     0x167  /*  Werkzeugoeffnungsweg      S.51                */
#define SetCntEjeForwardStages 0x168  /*  Ejector forward stages  */
#define SetCntEjeBackStages 0x169  /*  Ejector back stages  */
#define ssaus1     0x16a  /*  Umschaltpunkt Stufe 1     S.52                */
#define ssaus2     0x16b  /*  Auswerferweg              S.52                */
#define ssaus3     0x16c  /*  Auswerferrueckweg bei Mehrfachhub  S.52       */
#define ssausr     0x16d  /*  Nullpunktabgleich Auswerfer        S.52       */
#define svzu1      0x16e  /*  Geschwindigkeit fuer Stufe 1  S.50            */
#define svzu2      0x16f  /*  Geschwindigkeit fuer Stufe 2  S.50            */
#define svauf1     0x170  /*  Geschwindigkeit fuer Stufe 1  S.51            */
#define svauf2     0x171  /*  Geschwindigkeit fuer Stufe 2  S.51            */
#define svauf3     0x172  /*  Geschwindigkeit fuer Stufe 3  S.51            */
#define svaus1     0x173  /*  Geschwindigkeit Stufe 1 vor      S.52         */
#define svaus2     0x174  /*  Geschwindigkeit Stufe 1 zurueck  S.52         */
#define svazur     0x175  /*  Geschwindigkeit Stufe 2 zurueck  S.52         */
#define SetVelEjeBack2 0x176  /* Velocity ejector back stage 2 */
#define SetStrEjeBack1 0x177  /* Stroke ejector back stage 1 */
#define SetStrEjeBack2 0x178  /* Stroke ejector back stage 2 */
#define spnidr     0x179  /*  Druck Werkzeugsicherung 1  S.50               */
#define SetFceClpMoldProtectTol2 0x17a  /*  Force clamp mold protect tolerance stage 2 */
#define SetFceClpMoldProtectTol3 0x17b  /*  Force clamp mold protect tolerance stage 3 */
#define sfzuhk     0x17c  /*  Schliesskraft  S.50  u. S.54.1                */
#define speinr     0x17d  /*  Einrichtdruck  S.50                           */
#define spspr      0x17e  /*  Start Einspritzen bei Schliesskraft  S.50     */
#define sfssed     0x17f  /*  Start Schliesskraftaufbau            S.50     */
#define SetCntClpMoldProtectStages 0x180  /* Stages for mold protect */
#define dhvwalr    0x181  /*  Aggregat 1 oder 2 usw. aktiv                  */
/* ------------------- SOLLWERT S.40 allgemein ---------------------------- */
#define stkuhl     0x182  /*  Kuehlzeit  S.40                               */
/* ------------------- SOLLWERT S.40 Aggregat 1 --------------------------- */
#define IqtDummy   0x183  /*      IQT-SPS-Dummy Register                    */
#define SetCfgPlstStages1 0x184  /*  plasticising stages unit 1                */
#define ssdos1     0x185  /*  Plastifizierweg                               */
#define ssum11     0x186  /*  Wegpunkt                                      */
#define SetStrPlst12 0x187  /*  Position unit 1 stage 2                       */
#define SetStrPlst13 0x188  /*  Position unit 1 stage 3                       */
#define SetStrPlst14 0x189  /*  Position unit 1 stage 4                       */
#define SetStrPlst15 0x18a  /*  Position unit 1 stage 5                       */
/* ------------------------------------------------------------------------ */
#define swpl11     0x18b  /*  Drehzahl  Stufe 1                             */
#define swpl12     0x18c  /*  Drehzahl  Stufe 2                             */
#define SetSpdPlst13 0x18d  /*  Speed unit 1 stage 3                          */
#define SetSpdPlst14 0x18e  /*  Speed unit 1 stage 4                          */
#define SetSpdPlst15 0x18f  /*  Speed unit 1 stage 5                          */
/* ------------------------------------------------------------------------ */
#define spst11     0x190  /*  Staudruck Stufe 1                             */
#define spst12     0x191  /*  Staudruck Stufe 2                             */
#define SetPrsPlst13 0x192  /*  Pressure unit 1 stage 3                       */
#define SetPrsPlst14 0x193  /*  Pressure unit 1 stage 4                       */
#define SetPrsPlst15 0x194  /*  Pressure unit 1 stage 5                       */
/* ------------------------------------------------------------------------ */
#define spsth1     0x195  /*  Staudruck im Handbetrieb                      */
#define SRSsvor_1  0x196  /*  Schneckenrueckzug vor Plastif.  Agg.1         */
#define SRSvvor_1  0x197  /*  Rueckzugsgeschw. vor Plastif.   Agg.1         */
#define SRSsnach_1 0x198  /*  Schneckenrueckzug nach Plastif. Agg.1         */
#define SRSvnach_1 0x199  /*  Rueckzugsgeschw. nach Plastif.  Agg.1         */
#define stvdos     0x19a  /*  Plastifizierverzoegerung                      */
#define stintr     0x19b  /*  Intrusion                                     */
/* ------------------- SOLLWERT S.41 allgemein ---------------------------- */
#define snphmx     0x19c  /*  Anzahl Spritzstufen  Aggregat 1               */
/* ------------------- SOLLWERT Einspritzdruck S.41/S.42 ------------------ */
#define spph11     0x19d  /*  Aggregat 1  Stufe 1                           */
#define spph12     0x19e  /*  Aggregat 1  Stufe 2                           */
#define spph13     0x19f  /*  Aggregat 1  Stufe 3                           */
#define spph14     0x1a0  /*  Aggregat 1  Stufe 4                           */
#define spph15     0x1a1  /*  Aggregat 1  Stufe 5                           */
#define spph16     0x1a2  /*  Aggregat 1  Stufe 6                           */
#define SetPrsInj17 0x1a3  /*  Injection pressure unit 1 stage 7             */
#define SetPrsInj18 0x1a4  /*  Injection pressure unit 1 stage 8             */
#define SetPrsInj19 0x1a5  /*  Injection pressure unit 1 stage 9             */
#define SetPrsInj1a 0x1a6  /*  Injection pressure unit 1 stage 10            */
/* ------------------- SOLLWERT Einspritzgeschwindigkeit S.41/S.42 -------- */
#define svph11     0x1a7  /*  Aggregat 1  Stufe 1                           */
#define svph12     0x1a8  /*  Aggregat 1  Stufe 2                           */
#define svph13     0x1a9  /*  Aggregat 1  Stufe 3                           */
#define svph14     0x1aa  /*  Aggregat 1  Stufe 4                           */
#define svph15     0x1ab  /*  Aggregat 1  Stufe 5                           */
#define svph16     0x1ac  /*  Aggregat 1  Stufe 6                           */
#define SetVelInj17 0x1ad  /*  Injection velocity unit 1 stage 7             */
#define SetVelInj18 0x1ae  /*  Injection velocity unit 1 stage 8             */
#define SetVelInj19 0x1af  /*  Injection velocity unit 1 stage 9             */
#define SetVelInj1a 0x1b0  /*  Injection velocity unit 1 stage 10            */
/* ------------------- SOLLWERT Einspritzzeit S.41/S.42 ------------------- */
#define stph11     0x1b1  /*  Aggregat 1  Stufe 1                           */
#define stph12     0x1b2  /*  Aggregat 1  Stufe 2                           */
#define stph13     0x1b3  /*  Aggregat 1  Stufe 3                           */
#define stph14     0x1b4  /*  Aggregat 1  Stufe 4                           */
#define stph15     0x1b5  /*  Aggregat 1  Stufe 5                           */
#define stph16     0x1b6  /*  Aggregat 1  Stufe 6                           */
#define SetTimInj17 0x1b7  /*  Injection time unit 1 stage 7                 */
#define SetTimInj18 0x1b8  /*  Injection time unit 1 stage 8                 */
#define SetTimInj19 0x1b9  /*  Injection time unit 1 stage 9                 */
#define SetTimInj1a 0x1ba  /*  Injection time unit 1 stage 10                */
/* ------------------- SOLLWERT Umschaltdruck S.41/S.42 ------------------- */
#define spum11     0x1bb  /*  Aggregat 1  Stufe 1                           */
#define spum12     0x1bc  /*  Aggregat 1  Stufe 2                           */
#define spum13     0x1bd  /*  Aggregat 1  Stufe 3                           */
#define spum14     0x1be  /*  Aggregat 1  Stufe 4                           */
#define spum15     0x1bf  /*  Aggregat 1  Stufe 5                           */
#define SetPrsInjSwOver16 0x1c0  /*  Injection switch over pressure unit 1 stage 6  */
#define SetPrsInjSwOver17 0x1c1  /*  Injection switch over pressure unit 1 stage 7  */
#define SetPrsInjSwOver18 0x1c2  /*  Injection switch over pressure unit 1 stage 8  */
#define SetPrsInjSwOver19 0x1c3  /*  Injection switch over pressure unit 1 stage 9  */
#define SetPrsInjSwOver1a 0x1c4  /*  Injection switch over pressure unit 1 stage 10  */
/* ------------------- SOLLWERT Umschaltpunkt S.41/S.42 ------------------- */
#define ssph11     0x1c5  /*  Aggregat 1  Stufe 1                           */
#define ssph12     0x1c6  /*  Aggregat 1  Stufe 2                           */
#define ssph13     0x1c7  /*  Aggregat 1  Stufe 3                           */
#define ssph14     0x1c8  /*  Aggregat 1  Stufe 4                           */
#define ssph15     0x1c9  /*  Aggregat 1  Stufe 5                           */
#define SetStrInj16 0x1ca  /*  Injection stroke unit 1 stage 6               */
#define SetStrInj17 0x1cb  /*  Injection stroke unit 1 stage 7               */
#define SetStrInj18 0x1cc  /*  Injection stroke unit 1 stage 8               */
#define SetStrInj19 0x1cd  /*  Injection stroke unit 1 stage 9               */
#define SetStrInj1a 0x1ce  /*  Injection stroke unit 1 stage 10              */
/* ------------------- SOLLWERT Nachdruck --------------------------------- */
#define SetCfgDwlStages1 0x1cf  /*  Number of dwell profile stages            */
/* ------------------------------------------------------------------------ */
#define SetPrsDwl11 0x1d0  /*  Dwell pressure unit 1 stage 1        */
#define SetPrsDwl12 0x1d1  /*  Dwell pressure unit 1 stage 2        */
#define SetPrsDwl13 0x1d2  /*  Dwell pressure unit 1 stage 3        */
#define SetPrsDwl14 0x1d3  /*  Dwell pressure unit 1 stage 4        */
#define SetPrsDwl15 0x1d4  /*  Dwell pressure unit 1 stage 5        */
#define SetPrsDwl16 0x1d5  /*  Dwell pressure unit 1 stage 6        */
#define SetPrsDwl17 0x1d6  /*  Dwell pressure unit 1 stage 7        */
#define SetPrsDwl18 0x1d7  /*  Dwell pressure unit 1 stage 8        */
#define SetPrsDwl19 0x1d8  /*  Dwell pressure unit 1 stage 9        */
#define SetPrsDwl1a 0x1d9  /*  Dwell pressure unit 1 stage 10       */
/* ------------------- SOLLWERT Nachdruck Geschwindigkeit ------------- */
#define SetVelDwl11 0x1da  /*  Dwell velocity unit 1 stage 1        */
#define SetVelDwl12 0x1db  /*  Dwell velocity unit 1 stage 2        */
#define SetVelDwl13 0x1dc  /*  Dwell velocity unit 1 stage 3        */
#define SetVelDwl14 0x1dd  /*  Dwell velocity unit 1 stage 4        */
#define SetVelDwl15 0x1de  /*  Dwell velocity unit 1 stage 5        */
#define SetVelDwl16 0x1df  /*  Dwell velocity unit 1 stage 6        */
#define SetVelDwl17 0x1e0  /*  Dwell velocity unit 1 stage 7        */
#define SetVelDwl18 0x1e1  /*  Dwell velocity unit 1 stage 8        */
#define SetVelDwl19 0x1e2  /*  Dwell velocity unit 1 stage 9        */
#define SetVelDwl1a 0x1e3  /*  Dwell velocity unit 1 stage 10       */
/* ------------------- SOLLWERT Nachdruck Zeit ------------------------ */
#define SetTimDwl11 0x1e4  /*  Dwell time unit 1 stage 1            */
#define SetTimDwl12 0x1e5  /*  Dwell time unit 1 stage 2            */
#define SetTimDwl13 0x1e6  /*  Dwell time unit 1 stage 3            */
#define SetTimDwl14 0x1e7  /*  Dwell time unit 1 stage 4            */
#define SetTimDwl15 0x1e8  /*  Dwell time unit 1 stage 5            */
#define SetTimDwl16 0x1e9  /*  Dwell time unit 1 stage 6            */
#define SetTimDwl17 0x1ea  /*  Dwell time unit 1 stage 7            */
#define SetTimDwl18 0x1eb  /*  Dwell time unit 1 stage 8            */
#define SetTimDwl19 0x1ec  /*  Dwell time unit 1 stage 9            */
#define SetTimDwl1a 0x1ed  /*  Dwell time unit 1 stage 10           */
/* ------------------- SOLLWERT Dwell switch over ------------------------- */
#define SetPrsDwlSwOver11 0x1ee  /*  Dwell switch over unit 1 stage 1         */
#define SetPrsDwlSwOver12 0x1ef  /*  Dwell switch over unit 1 stage 2         */
#define SetPrsDwlSwOver13 0x1f0  /*  Dwell switch over unit 1 stage 3         */
#define SetPrsDwlSwOver14 0x1f1  /*  Dwell switch over unit 1 stage 4         */
#define SetPrsDwlSwOver15 0x1f2  /*  Dwell switch over unit 1 stage 5         */
#define SetPrsDwlSwOver16 0x1f3  /*  Dwell switch over unit 1 stage 6         */
#define SetPrsDwlSwOver17 0x1f4  /*  Dwell switch over unit 1 stage 7         */
#define SetPrsDwlSwOver18 0x1f5  /*  Dwell switch over unit 1 stage 8         */
#define SetPrsDwlSwOver19 0x1f6  /*  Dwell switch over unit 1 stage 9         */
#define SetPrsDwlSwOver1a 0x1f7  /*  Dwell switch over unit 1 stage 10        */
/* ------------------- SOLLWERT Dwell stroke ------------------------------ */
#define SetStrDwl11 0x1f8  /*  Dwell stroke unit 1 stage 1                   */
#define SetStrDwl12 0x1f9  /*  Dwell stroke unit 1 stage 2                   */
#define SetStrDwl13 0x1fa  /*  Dwell stroke unit 1 stage 3                   */
#define SetStrDwl14 0x1fb  /*  Dwell stroke unit 1 stage 4                   */
#define SetStrDwl15 0x1fc  /*  Dwell stroke unit 1 stage 5                   */
#define SetStrDwl16 0x1fd  /*  Dwell stroke unit 1 stage 6                   */
#define SetStrDwl17 0x1fe  /*  Dwell stroke unit 1 stage 7                   */
#define SetStrDwl18 0x1ff  /*  Dwell stroke unit 1 stage 8                   */
#define SetStrDwl19 0x200  /*  Dwell stroke unit 1 stage 9                   */
#define SetStrDwl1a 0x201  /*  Dwell stroke unit 1 stage 10                  */
/* -------- Register fuer  S. 39.9 ------------------ */
#define HXsnIF     0x202  /*  Schnittstelle  */
#define HXsnProto  0x203  /*  Protokoll  */
#define HXsnBaud   0x204  /*  Baudrate  */
#define HXsnDatBit 0x205  /*  Datenbits  */
#define HXsnStpBit 0x206  /*  Stopbits  */
#define HXsnParity 0x207  /*  Parity  */
#define HXsnIF_2   0x208  /*  Schnittstelle  */
#define HXsnProto2 0x209  /*  Protokoll  */
#define HXsnBaud_2 0x20a  /*  Baudrate  */
#define HXsnDatBi2 0x20b  /*  Datenbits  */
#define HXsnStpBi2 0x20c  /*  Stopbits  */
#define HXsnParit2 0x20d  /*  Parity  */
/* -------- Register fuer S. 35.0 ------------------- */
#define HZsnRegNr1 0x20e  /*  Reglernummer  */
#define HZsnRegNr2 0x20f  /*  Reglernummer  */
#define HZsnRegNr3 0x210  /*  Reglernummer  */
#define HZsnRegNr4 0x211  /*  Reglernummer  */
#define HZsnWahl1  0x212  /*  Wahl des Zeitpunktes  */
#define HZsnWahl2  0x213  /*  Wahl des Zeitpunktes  */
#define HZsnWahl3  0x214  /*  Wahl des Zeitpunktes  */
#define HZsnWahl4  0x215  /*  Wahl des Zeitpunktes  */
/* ------------------- SOLLWERT S.43 -------------------------------------- */
#define snfin      0x216  /*  Umschaltung mit Wkz-Innendruck  Aggregat 1    */
#define kxempf     0x217  /*  Fuehlerempfundlichkeit          Aggregat 1    */
/* ------------------- SOLLWERT S.49 Aggregat 1 --------------------------- */
#define snaggr     0x218  /*  Duesenabhebung nach Einspritzen Aggregat 1    */
#define staggr     0x219  /*  Duesensbhebung verzoegert um    Aggregat 1    */
#define stdues1    0x21a  /*  Duesenabhebezeit                Aggregat 1    */
#define svag1v     0x21b  /*  Duesengeschwindigkeit vor       Aggregat 1    */
#define svag1z     0x21c  /*  Duesengeschwindigkeit zurueck   Aggregat 1    */
#define sfaggr     0x21d  /*  Duesenanpressdruck              Aggregat 1    */
#define sagpfo     0x21e  /*  Duesenanpressdruck bei offener Form Aggregat1 */
/* ------------------- SOLLWERT S.71 Kartonzaehler ------------------------ */
#define OPsnKarton 0x21f  /*  Anzahl Teile pro Karton                       */
#define OPs_Neust  0x220  /*  Neustart Kartonzaehler                        */
/* ------------------- SOLLWERT S.44 -------------------------------------- */
#define AGstVVer1  0x221  /*  Verzoegerungszeit Einspritzen  Aggr.1         */
#define AGstVVer2  0x222  /*  Verzoegerungszeit Einspritzen  Aggr.2         */
#define SPstVerz1  0x223  /*  Verzoegerungszeit Aggregat vor Aggr.1         */
#define SPstVerz2  0x224  /*  Verzoegerungszeit Aggregat vor Aggr.2         */
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define WAs_fkt    0x225  /*  Wahl Auswerfer vor,nach,parallel Masch.Ausw.  */
#define WAs_Wpvor  0x226  /*  Aktionsbeginn Wkz-Auswerfer                   */
#define WAs_Hubz   0x227  /*  Sollwert Hubzahl                              */
#define WAstVorne  0x228  /*  Wartezeit vorne                               */
#define WAstVor    0x229  /*  Aktionszeit Wkz-Auswerfer vor                 */
#define WAstZur    0x22a  /*  Aktionszeit Wkz-Auswerfer zurueck             */
#define KE_pAusfa  0x22b  /*  Druck Kern 1 aus                              */
#define KE_pEinfa0 0x22c  /*  Druck Kern 1 ein                              */
#define KE_vAusfa0 0x22d  /*  Geschw. 1 Kern aus                            */
#define KE_vAusfa1 0x22e  /*  Geschw. 2 Kern aus                            */
#define KE_vEinfa0 0x22f  /*  Geschw. 1 Kern ein                            */
#define tabswkz    0x230  /*  Temperaturabsenkung Werkzeugheizung           */
#define tabszyl1   0x231  /*  Temperaturabsenkung Zylinderheizung Agg. 1    */
#define stzykl     0x232  /*  Zyklusueberwachungszeit S.80                  */
#define stdos1     0x233  /*  Plastifizierzeitueberwachung Aggregat 1 S.80  */
#define stdos2     0x234  /*  Plastifizierzeitueberwachung Aggregat 2 S.80  */
#define stdos3     0x235  /*  Plastifizierzeitueberwachung Aggregat 3 S.80  */
#define stdos4     0x236  /*  Plastifizierzeitueberwachung Aggregat 4 S.80  */
#define stmota     0x237  /*  Motor-/Heizung Abschaltverzoegerung     S.80  */
#define stwasa     0x238  /*  Kuehlwasser-Abschaltverzoegerung        S.80  */
#define stnidr     0x239  /*  Ueberwachungszeit Wkz-Sicherung  S.50         */
#define SetVelClpMoldProtect2 0x23a  /* Velocity Mold protect 2 */
#define SetVelClpMoldProtect3 0x23b  /* Velocity Mold protect 3 */
#define stpaus     0x23c  /*  Pausenzeit  S.51                              */
#define staus1     0x23d  /*  Wartezeit am Umschaltpunkt vor  S.52          */
#define staus2     0x23e  /*  Wartezeit vorne  S.52                         */
#define SLsnSchm   0x23f  /*  LONG Einfahrschmierintervall    S.89          */
#define snkern     0x241  /*  Sonderprogrammnummer       S.21 und S.67      */
#define snnidr     0x242  /*  Wiederholung Werkzeugsicherung   S.50         */
#define snausw     0x243  /*  Anzahl Auswerferhuebe  S.52                   */
#define snvws1     0x244  /*  Programmschalter 1   S.67                     */
#define snvws2     0x245  /*  Programmschalter 2   S.67                     */
#define snvws3     0x246  /*  Programmschalter 3   S.67                     */
#define snvws4     0x247  /*  Programmschalter 4   S.67                     */
#define snvws5     0x248  /*  Programmschalter 5   S.67                     */
#define sswp1      0x249  /*  Wegpunkt 1           S.67                     */
#define sswp2      0x24a  /*  Wegpunkt 2           S.67                     */
#define sswp3      0x24b  /*  Wegpunkt 3           S.67                     */
#define sswp4      0x24c  /*  Wegpunkt 4           S.67                     */
#define sswp5      0x24d  /*  Wegpunkt 5           S.67                     */
#define stz1       0x24e  /*  Zeit 1               S.67                     */
#define stz2       0x24f  /*  Zeit 2               S.67                     */
#define stz3       0x250  /*  Zeit 3               S.67                     */
#define stz4       0x251  /*  Zeit 4               S.67                     */
#define stz5       0x252  /*  Zeit 5               S.67                     */
#define svk1ei     0x253  /*  Einfahrgeschwindigkeit   S.61                 */
#define spk1ei     0x254  /*  Einfahrdruck             S.61                 */
#define svk1au     0x255  /*  Ausfahrgeschwindigkeit   S.61.1               */
#define spk1au     0x256  /*  Ausfahrdruck             S.61.1               */
#define svk2ei     0x257  /*  Einfahrgeschwindigkeit   S.62                 */
#define spk2ei     0x258  /*  Einfahrdruck             S.62                 */
#define svk2au     0x259  /*  Ausfahrgeschwindigkeit   S.62.1               */
#define spk2au     0x25a  /*  Ausfahrdruck             S.62.1               */
#define knuver     0x25b  /*  Test beim Aufstarten: Programmversion         */
#define knutyp     0x25c  /*  Test beim Aufstarten: Maschinengroesse/typ    */
#define ssentn     0x25d  /*  Wegpunkt Start Entnahme ein   S.70            */
#define zissst     0x25e  /*  aktuelle Schluesselschalterposition           */
#define SSCmd      0x25f  /*  Parameter des SS-Kommandos im Diagnosemode    */
#define formmin    0x260  /*  minimale Formeinbauhoehe           */
/* ---------------- Robot-Handlinggeraet ---------------------------------- */
#define ROsnProgr  0x261  /*  Programmnummer fuer Robot                     */
#define ROs_Ablag  0x262  /*  Ablage auf/ueber Ablage;in SGM                */
#define ROstYSgm   0x263  /*  Zeit bis Y-Achse in SGM eingefahren           */
#define ROstXvor   0x264  /*  Zeit bis X-Achse vorgefahren                  */
#define ROstAwVor  0x265  /*  Zeit bis Auswerfer vorne                      */
#define ROstGrEin  0x266  /*  Zeit bis Greifer ein                          */
#define ROstGrAus  0x267  /*  Zeit bis Greifer aus                          */
#define ROstAwZur  0x268  /*  Zeit bis Auswerer zurueck                     */
#define ROstXzur   0x269  /*  Zeit bis X-Achse zurueck                      */
#define ROstB_C    0x26a  /*  Zeit fuer B_C Achse                           */
#define ROstYAbl   0x26b  /*  Zeit fuer Y-Achse zur Ablage                  */
#define ROstFormZu 0x26c  /*  Zeit fuer Form zu                             */
#define ROstBTakt  0x26d  /*  Zeit des Band Takt                            */
#define ROstABlas  0x26e  /*  Abblaszeit                                    */
#define ROstAusbis 0x26f  /*  Totzeit fuer Auswerfer                        */
#define ROstZuebw  0x270  /*  ?? Zeit                                       */
#define ROsnSoAbl  0x271  /*  Sonderfunktion Ablage                         */
#define SEgpUSt    0x272  /*  Max. Umschaltdruck 1.Agg                      */
#define SEgpUSt2   0x273  /*  Max. Umschaltdruck 2.Agg                      */
#define AWgweg     0x274  /*  Max. Auswerferweg                             */
#define SNgdrehm1  0x275  /*  Max. Schneckendrehmoment 1.Agg                */
#define SNgdrehm2  0x276  /*  Max. Schneckendrehmoment 2.Agg                */
/* ---------------- Luftventilseite 69.0 ---------------------------------- */
#define LVsnEin0   0x277  /*  Programmwahl                Ventil 1    */
#define LVsnEin1   0x278  /*  Programmwahl                Ventil 2    */
#define LVsnEin2   0x279  /*  Programmwahl                Ventil 3    */
#define LVsnEin3   0x27a  /*  Programmwahl                Ventil 4    */
#define LVsnEin4   0x27b  /*  Programmwahl                Ventil 5    */
#define LVsnEin5   0x27c  /*  Programmwahl                Ventil 6    */
#define LVsnEin6   0x27d  /*  Programmwahl                Ventil 7    */
#define LVsnEin7   0x27e  /*  Programmwahl                Ventil 8    */
#define LVssWegP5  0x27f  /*  Wegpunkt                    Ventil 5    */
#define LVssWegP6  0x280  /*  Wegpunkt                    Ventil 6    */
#define LVssWegP7  0x281  /*  Wegpunkt                    Ventil 7    */
#define LVssWegP8  0x282  /*  Wegpunkt                    Ventil 8    */
#define LVstVerz10 0x283  /*  Verzoegerungszeit in 1/100  Ventil 1    */
#define LVstVerz20 0x284  /*  Verzoegerungszeit in 1/100  Ventil 2    */
#define LVstVerz30 0x285  /*  Verzoegerungszeit in 1/100  Ventil 3    */
#define LVstVerz40 0x286  /*  Verzoegerungszeit in 1/100  Ventil 4    */
#define LVstVerz50 0x287  /*  Verzoegerungszeit in 1/100  Ventil 5    */
#define LVstVerz60 0x288  /*  Verzoegerungszeit in 1/100  Ventil 6    */
#define LVstVerz70 0x289  /*  Verzoegerungszeit in 1/100  Ventil 7    */
#define LVstVerz80 0x28a  /*  Verzoegerungszeit in 1/100  Ventil 8    */
#define LVstBlas10 0x28b  /*  Blaszeit          in 1/100  Ventil 1    */
#define LVstBlas20 0x28c  /*  Blaszeit          in 1/100  Ventil 2    */
#define LVstBlas30 0x28d  /*  Blaszeit          in 1/100  Ventil 3    */
#define LVstBlas40 0x28e  /*  Blaszeit          in 1/100  Ventil 4    */
#define LVstBlas50 0x28f  /*  Blaszeit          in 1/100  Ventil 5    */
#define LVstBlas60 0x290  /*  Blaszeit          in 1/100  Ventil 6    */
#define LVstBlas70 0x291  /*  Blaszeit          in 1/100  Ventil 7    */
#define LVstBlas80 0x292  /*  Blaszeit          in 1/100  Ventil 8    */
/* ------------------------------------------------------------------------ */
#define SEssFzu2   0x293  /*  3. Wegpunkt Wkz schliessen                    */
#define SEsvFzu3   0x294  /*  3. Geschwindigkeit Wkz schliessen             */
/* ---------------- SPS-Datum und Uhrzeit --------------------------------- */
#define ClYear     0x295  /*   Jahr                                         */
#define ClMonth    0x296  /*   Monat                                        */
#define ClMDay     0x297  /*   Tag                                          */
#define ClHour     0x298  /*   Stunde                                       */
#define ClMin      0x299  /*   Minute                                       */
/* ---------------- Diagnose - Register -Elektra -------------------------- */
#define MSssOff1   0x29a  /*  89.5 Formoffset                  SOLL         */
#define MSssOff2   0x29b  /*  89.5 Auswerferoffset             SOLL         */
#define MSssOff3   0x29c  /*  89.5 Einspritzwegoffset   1.Agg  SOLL         */
#define MSssOff4   0x29d  /*  89.5 Einspritzwegoffset   2.Agg  SOLL         */
#define MSsfOffSP  0x29e  /*  89.5 Einspritzkraftoffset 1.Agg  SOLL         */
#define MSsfOffSP2 0x29f  /*  89.5 Einspritzkraftoffset 2.Agg  SOLL         */
#define MSsfOffGK  0x2a0  /*  89.5 Gelenkkopfkraftoffset       SOLL         */
#define MSskOffET  0x2a1  /*  89.5 E-Schrank T.-Offset         SOLL         */
#define MSsnHolm   0x2a2  /*  89.5 Anzahl Holmdehnungss.       SOLL         */
#define MSGenMod   0x2a3  /*  89.5 default/RAM/PROM            SOLL         */
/* ---------------- Reserveregister fuer Sonderprogramme ------------------ */
#define iqson0     0x2a4  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1     0x2a5  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2     0x2a6  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3     0x2a7  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4     0x2a8  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5     0x2a9  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson6     0x2aa  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson7     0x2ab  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson8     0x2ac  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson9     0x2ad  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqsona     0x2ae  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqsonb     0x2af  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqsonc     0x2b0  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqsond     0x2b1  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqsone     0x2b2  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqsonf     0x2b3  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson10    0x2b4  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson11    0x2b5  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson12    0x2b6  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson13    0x2b7  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson14    0x2b8  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson15    0x2b9  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson16    0x2ba  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson17    0x2bb  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson18    0x2bc  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson19    0x2bd  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1a    0x2be  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1b    0x2bf  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1c    0x2c0  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1d    0x2c1  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1e    0x2c2  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson1f    0x2c3  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson20    0x2c4  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson21    0x2c5  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson22    0x2c6  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson23    0x2c7  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson24    0x2c8  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson25    0x2c9  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson26    0x2ca  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson27    0x2cb  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson28    0x2cc  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson29    0x2cd  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2a    0x2ce  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2b    0x2cf  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2c    0x2d0  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2d    0x2d1  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2e    0x2d2  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson2f    0x2d3  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson30    0x2d4  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson31    0x2d5  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson32    0x2d6  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson33    0x2d7  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson34    0x2d8  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson35    0x2d9  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson36    0x2da  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson37    0x2db  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson38    0x2dc  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson39    0x2dd  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3a    0x2de  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3b    0x2df  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3c    0x2e0  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3d    0x2e1  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3e    0x2e2  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson3f    0x2e3  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson40    0x2e4  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson41    0x2e5  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson42    0x2e6  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson43    0x2e7  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson44    0x2e8  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson45    0x2e9  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson46    0x2ea  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson47    0x2eb  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson48    0x2ec  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson49    0x2ed  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4a    0x2ee  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4b    0x2ef  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4c    0x2f0  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4d    0x2f1  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4e    0x2f2  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson4f    0x2f3  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson50    0x2f4  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson51    0x2f5  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson52    0x2f6  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson53    0x2f7  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson54    0x2f8  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson55    0x2f9  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson56    0x2fa  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson57    0x2fb  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson58    0x2fc  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson59    0x2fd  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5a    0x2fe  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5b    0x2ff  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5c    0x300  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5d    0x301  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5e    0x302  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson5f    0x303  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson60    0x304  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson61    0x305  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson62    0x306  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson63    0x307  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson64    0x308  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson65    0x309  /*      reserviert fuer IQT-Sonderprogramme       */
#define iqson66    0x30a  /*      reserviert fuer IQT-Sonderprogramme       */
#define SEstUeber  0x30b  /*      SPECIAL  pressure monitoring time         */
#define SEspUWMax  0x30c  /*      SPECIAL  monitoring ressure               */
/* ---------------- Atmen Praegen ----------------------------------------- */
#define APs_Wahl   0x30d  /*      Atmen/Praegen Programmwahl                */
#define APs_Stufen 0x30e  /*      Startpunkt nach Spritzstufe ?             */
#define APstVerz   0x30f  /*      Verzoegerungszeit                         */
#define APspLock1  0x310  /*      Schliesskraft F1                          */
#define APstAktio1 0x311  /*      Aktionszeit t1                            */
#define APspLock2  0x312  /*      Schliesskraft F2                          */
#define APstAktio2 0x313  /*      Aktionszeit t2                            */
#define APspLock3  0x314  /*      Schliesskraft F3                          */
#define APstAktio3 0x315  /*      Aktionszeit t3                            */
#define APspLock4  0x316  /*      Schliesskraft F4                          */
#define APssStart  0x317  /*      Startpunkt nach Schneckenposition         */
#define APs_NrStuf 0x318  /*      Anzahl Atmungs- bzw. Praegestufen         */
#define APssPWeg   0x319  /*      Atmungs- bzw. Praegeweg                   */
/* -------- Register fuer Produktionsstart S. 40.2 ------------------------ */
#define XSn_Anfa   0x31a  /*  Anzahl Anfahrzyklen  */
#define ssdos1a    0x31b  /*  Plastivizierweg      */
#define spph11a    0x31c  /*  Einspritzdruck p1    */
#define svph11a    0x31d  /*  Einspritzgeschw. v1  */
#define stph11a    0x31e  /*  Einspritzzeit t1     */
#define ssph11a    0x31f  /*  Umschaltpunkt s1     */
#define spph12a    0x320  /*  Einspritzdruck p2    */
#define svph12a    0x321  /*  Einspritzgeschw. v2  */
#define stph12a    0x322  /*  Einspritzzeit t2     */
#define ssph12a    0x323  /*  Umschaltpunkt s2     */
#define spph13a    0x324  /*  Einspritzdruck p3    */
#define svph13a    0x325  /*  Einspritzgeschw. v3  */
#define stph13a    0x326  /*  Einspritzzeit t3     */
#define XSn_Anf2a  0x327  /*  Anzahl Anfahrzyklen Wkz-Druck  */
#define spnidra    0x328  /*  Druck werkzeugsicherung1  */
#define spnidr2a   0x329  /*  Druck werkzeugsicherung2  */
/* ------------------------------------------------------------------------ */
#define ZHs_Wasser 0x32a  /*  Seite 80.0 Kuehlwasserabschaltung             */
#define WZsnFSSRef 0x32b  /*  Softkey Seite 50.0 FSS-Referenzkurve aufnehmen */
/* ---------------- Kernzug Sonderprogramme-------------------------------- */
#define KEsv3In1   0x32c  /*      Kernzug 3 Einfahrgeschwindigkeit 1        */
#define KEsv4In1   0x32d  /*      Kernzug 4 Einfahrgeschwindigkeit 1        */
#define KEsv1In2   0x32e  /*      Kernzug 1 Einfahrgeschwindigkeit 2        */
#define KEsv2In2   0x32f  /*      Kernzug 2 Einfahrgeschwindigkeit 2        */
#define KEsv3In2   0x330  /*      Kernzug 3 Einfahrgeschwindigkeit 2        */
#define KEsv4In2   0x331  /*      Kernzug 4 Einfahrgeschwindigkeit 2        */
#define KEsv3Ou1   0x332  /*      Kernzug 3 Ausfahrgeschwindigkeit 1        */
#define KEsv4Ou1   0x333  /*      Kernzug 4 Ausfahrgeschwindigkeit 1        */
#define KEsv1Ou2   0x334  /*      Kernzug 1 Ausfahrgeschwindigkeit 2        */
#define KEsv2Ou2   0x335  /*      Kernzug 2 Ausfahrgeschwindigkeit 2        */
#define KEsv3Ou2   0x336  /*      Kernzug 3 Ausfahrgeschwindigkeit 2        */
#define KEsv4Ou2   0x337  /*      Kernzug 4 Ausfahrgeschwindigkeit 2        */
#define KEsp3In1   0x338  /*      Kernzug 3 Einfahrdruck 1                  */
#define KEsp4In1   0x339  /*      Kernzug 4 Einfahrdruck 1                  */
#define KEsp1In2   0x33a  /*      Kernzug 1 Einfahrdruck 2                  */
#define KEsp2In2   0x33b  /*      Kernzug 2 Einfahrdruck 2                  */
#define KEsp3In2   0x33c  /*      Kernzug 3 Einfahrdruck 2                  */
#define KEsp4In2   0x33d  /*      Kernzug 4 Einfahrdruck 2                  */
#define KEsp3Ou1   0x33e  /*      Kernzug 3 Ausfahrdruck 1                  */
#define KEsp4Ou1   0x33f  /*      Kernzug 4 Ausfahrdruck 1                  */
#define KEsp1Ou2   0x340  /*      Kernzug 1 Ausfahrdruck 2                  */
#define KEsp2Ou2   0x341  /*      Kernzug 2 Ausfahrdruck 2                  */
#define KEsp3Ou2   0x342  /*      Kernzug 3 Ausfahrdruck 2                  */
#define KEsp4Ou2   0x343  /*      Kernzug 4 Ausfahrdruck 2                  */
/* ------------------------- Kernzueg Ausschrauben ------------------------- */
#define KEs_Arl    0x344  /*      Drehrichtung rechts=0 links=1             */
#define KEstAVWo   0x345  /*      Verzoegerungszeit bis Werkzeug oeffnen    */
#define KEstAVSa   0x346  /*      Verzoegerungszeit bis Start Ausschrauben  */
#define KEstAAAu   0x347  /*      Aktionszeit Ausschrauben                  */
#define KEstAVSAu  0x348  /*      Verzoegerungszeit bis Start Auswerfer     */
#define KEssAWSa   0x349  /*      Wegpunkt Start Ausschrauben               */
#define KEs_AZnS   0x34a  /*      Zustand nach Schrauben drucklos=0 Druck=1 */
#define KEs_AUeSb  0x34b  /*      Ueberw. Schraubbewegung  Endsch.=1 Zeit=2 */
#define KEsvAusG   0x34c  /*      Ausschraubgeschwindigkeit                 */
#define KEspAusD   0x34d  /*      Ausschraubdruck                           */
#define KEspAusNd  0x34e  /*      Ausschraubniederdruck                     */
#define KEsvAEinG  0x34f  /*      Einschraubgeschwindigkeit                 */
#define KEspAEinD  0x350  /*      Einschraubdruck                           */
#define KEspAEinNd 0x351  /*      Einschraubniederdruck                     */
/* ------------------------- Sonderprogramm Werkzeugschnellspannen --------- */
#define WZs_SnSp   0x352  /*      Wkz-Schnellspanneinrichtung  aus=0 ein=1  */
/* ------------------------- Qualitaetskontrolle --------------------------- */
#define QUsnasz    0x353  /*      Ausschuss nach Automatikstart             */
#define QUsnasst   0x354  /*      Ausschuss nach Stoerung                   */
#define QUsnptzy   0x355  /*      Stichprobe                                */
#define QUsnptst   0x356  /*      Pruefteil nach Stoerung                   */
#define QUstvwo    0x357  /*      Verz.zeit Werkz. oeffnen                  */
/* ------------------------- Selektierweiche ------------------------------- */
#define QUs_Selek  0x358  /*      Betriebsart Selektierweiche               */
#define QUs_Angus  0x359  /*      Umschaltkrit. Angusstrennung              */
#define QUstVerz   0x35a  /*      Verzoegerungszeit                         */
#define tabszyl2   0x35b  /*      Temperaturabsenkung 2. Aggregat           */
#define tabszyl3   0x35c  /*      Temperaturabsenkung 3. Aggregat           */
#define tabszyl4   0x35d  /*      Temperaturabsenkung 4. Aggregat           */
/* ------------------------- Heizungsoptimierung --------------------------- */
#define HEs_BlOpt  0x35e  /*      Heizung Blockoptimierung ULONG             */
#define HEs_BlOpt2 0x360  /*      Heizung Blockoptimierung ULONG             */
/* ----------------- Maschinenabgleichs-Seite: Ventile --------------------- */
#define Ventil_Mod 0x362  /*      Load RAM/ROM-Identifikation               */
#define MAs_VenInd 0x363  /*      89.1 Ventilindex                 SOLL     */
#define MAs_Offs1  0x364  /*      89.1 Offset 1                    SOLL     */
#define MAs_Offs2  0x365  /*      89.1 Offset 2                    SOLL     */
#define MAs_Vers1  0x366  /*      89.1 Verstaerkung 1              SOLL     */
#define MAs_Vers2  0x367  /*      89.1 Verstaerkung 2              SOLL     */
#define MAVenRDInd 0x368  /*      89.1 Ventilindex fuer Lesen               */
/* ---------------- END Abgleichseite 89.2 -------------------------------- */
#define PL1GenMod  0x369  /*      89.3 default/RAM/PROM Agg.1       SOLL    */
#define PLsvMess   0x36a  /*      89.3 Plastifizier Ist-Anzeige MessMax SOLL */
#define PLsvOben   0x36b  /*      89.3 Plastifizier Ist-Anzeige Oben    SOLL */
#define PLskRampe1 0x36c  /*      89.3 Plastifizierzeit-Rampe Agg.1 SOLL    */
#define PLskGest1  0x36d  /*      89.3 Plastifizierzeit gest. Agg.1 SOLL    */
#define PL2GenMod  0x36e  /*      89.3 default/RAM/PROM Agg.2       SOLL    */
#define PLskRampe2 0x36f  /*      89.3 Plastifizierzeit-Rampe Agg.2 SOLL    */
#define PLskGest2  0x370  /*      89.3 Plastifizierzeit gest. Agg.2 SOLL    */
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
/* ---------------- Diagnoseseite Schliessdruckaufbau 87.5 ---------------- */
#define SDRGenMod  0x371  /*      87.5 default/RAM/Reset            SOLL    */
#define SDRstAufV  0x372  /*      87.5 SDR-Aufbauverzoegerungszeit  SOLL    */
#define SDRstAufB  0x373  /*      87.5 SDR-Aufbauzeit               SOLL    */
/* ---------------- END Diagnoseseite Schliessdruckaufbau 87.5 ------------ */
/* ----------------- Maschinen-Abgleich-Seiten / KD ------------------------ */
#define MSsppumOff 0x374  /*      89.1 Offset-Y8007            SOLL         */
#define MGenMod    0x375  /*      89.1 default/RAM/PROM        SOLL         */
/* ---------------- END Maschinen-Abgleich-Seiten / KD -------------------- */
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
#define DiagRDInd  0x376  /*  ReadIndex in Diagnosemodul-Tabelle            */
#define DiagWRInd  0x377  /*  WriteIndex in Diagnosemodul-Tabelle           */
/* ------------------------------------------------------------------------ */
#define FDiagDFOR  0x378  /*  ULONG Digitalausgaenge der Seite 87.8          */
#define FDiagA_F01 0x37a  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F02 0x37b  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F03 0x37c  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F04 0x37d  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F05 0x37e  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F06 0x37f  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F07 0x380  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F08 0x381  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F09 0x382  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F10 0x383  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F11 0x384  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F12 0x385  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F13 0x386  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F14 0x387  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F15 0x388  /*       Analogausgaenge der Seite 87.8           */
#define FDiagA_F16 0x389  /*       Analogausgaenge der Seite 87.8           */
/* ---------------- Standard Diagnoseseite -------------------------------------- */
#define SDiagDFOR  0x38a  /*  LONG Digitalausgaenge der Seite 88.3          */
#define SDiagA_F01 0x38c  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F02 0x38d  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F03 0x38e  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F04 0x38f  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F05 0x390  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F06 0x391  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F07 0x392  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F08 0x393  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F09 0x394  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F10 0x395  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F11 0x396  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F12 0x397  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F13 0x398  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F14 0x399  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F15 0x39a  /*       Analogausgaenge der Seite 88.3           */
#define SDiagA_F16 0x39b  /*       Analogausgaenge der Seite 88.3       */
/* ---------------- Verknuepfung Handling mit Kern ------------------------ */
#define FPKZandFHK 0x39c  /*      Seite 70.0 FHK-Schnittstelle              */
/* ---------------- Max. Plastifizierweg ---------------------------------- */
#define PLgweg1    0x39d  /*  Max. Plastifizierweg 1.Agg                    */
/* ---------------- Max. Schneckenumdrehung ------------------------------- */
#define SNg_Umdr1  0x39e  /*  Max. Schneckenumdrehung 1.Agg                 */
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define WZA_BA     0x39f  /*  Betriebsart Werkzeugauswerfer                 */
#define WZA_Spktv  0x3a0  /*  Startpunkt Werkzeugauswerfer vor              */
#define WZA_Auswh  0x3a1  /*  Anzahl Auswerferhuebe                         */
#define WZA_Wzvor  0x3a2  /*  Wartezeit vor                                 */
#define WZA_Akzvor 0x3a3  /*  Aktionszeit Auswerfer vor                     */
#define WZA_Akzzur 0x3a4  /*  Aktionszeit Auswerfer zurueck                 */
#define WZApvor    0x3a5  /*  Auswerferdruck vor                            */
#define WZApzur    0x3a6  /*  Auswerferdruck zurueck                        */
#define WZAvvor1   0x3a7  /*  Auswerfergeschwindigkeit vor v1               */
#define WZAvvor2   0x3a8  /*  Auswerfergeschwindigkeit vor v2               */
#define WZAvzur    0x3a9  /*  Auswerfergeschwindigkeit zurueck              */
/* ---------------- Werkzeugauswerfer 2 ----------------------------------- */
#define WZA_BA2    0x3aa  /*  Betriebsart Werkzeugauswerfer                 */
#define WZA_Spktv2 0x3ab  /*  Startpunkt Werkzeugauswerfer vor              */
#define WZA_Auswh2 0x3ac  /*  Anzahl Auswerferhuebe                         */
#define WZA_Wzvor2 0x3ad  /*  Wartezeit vor                                 */
#define WZA_Akzvo2 0x3ae  /*  Aktionszeit Auswerfer vor                     */
#define WZA_Akzzu2 0x3af  /*  Aktionszeit Auswerfer zurueck                 */
#define WZApvor2   0x3b0  /*  Auswerferdruck vor                            */
#define WZApzur2   0x3b1  /*  Auswerferdruck zurueck                        */
#define WZAvvor12  0x3b2  /*  Auswerfergeschwindigkeit vor v1               */
#define WZAvvor22  0x3b3  /*  Auswerfergeschwindigkeit vor v2               */
#define WZAvzur2   0x3b4  /*  Auswerfergeschwindigkeit zurueck              */
#define WZA_BA_FHK 0x3b5  /*  Betriebsart Werkzeugauswerfer                 */
/* ------------------------- Elektra-Sonderregister ------------------------ */
#define WSsbBeschl 0x3b6  /*      Beschleunigung Werkzeug schliessen S.50   */
#define WOsbBeschl 0x3b7  /*      Beschleunigung Werkzeug oeffnen S.51      */
#define AWsbVor    0x3b8  /*      Beschleunigung Auswerfer vor S.52         */
#define AWsbZur    0x3b9  /*      Beschleunigung Auswerfer zurueck S.52     */
#define SEssVerD1  0x3ba  /*      40.0 Verschlussduese         SOLL  Agg.1  */
#define MSksSnDur1 0x3bb  /*      aktueller Schneckendurchmesser     Agg.1  */
/* ------------------------------------------------------------------------ */
#define AGabhzit   0x3bc  /*  Duesenabhebezeit Seite 49.0 Zeile 10          */
#define AWkraft    0x3bd  /*  Auswerferkraft Seite 52.0 Zeile 19            */
/* ---------------- Diagnose - Register -Elektra -------------------------- */
#define MSssOff11  0x3be  /*  89.x   */
#define MSssOff21  0x3bf  /*  89.x   */
#define MSssOff31  0x3c0  /*  89.x   */
#define MSssnPNr   0x3c1  /*  */
#define MSssOff8   0x3c2  /*  89.x  LONG  */
#define BA_foer    0x3c4  /*  Foerderband S. 71.0                           */
#define FBst       0x3c5  /*  Laufzeit bei getaktetem Betrieb S 71.0        */
#define WFmpRange1 0x3c6  /*  Wertebereichsumschaltung fuer Wkz-innendruck  */
/* ----------------- Maschinenabgleichs-Seite: Kernzug-Ventile ------------- */
#define KZVenRDInd 0x3c7  /*      89.2 KZ-Ventilindex fuer Lesen            */
/* ----------------- Maschinenabgleichs-Seite: Kernzug-Ventile ------------- */
#define KZVent_Mod 0x3c8  /*      Load RAM/ROM-Identifikation               */
#define KZs_VenInd 0x3c9  /*      89.1 Ventilindex                 SOLL     */
#define KZs_Offs1  0x3ca  /*      89.1 Offset 1                    SOLL     */
#define KZs_Offs2  0x3cb  /*      89.1 Offset 2                    SOLL     */
#define KZs_Vers1  0x3cc  /*      89.1 Verstaerkung 1              SOLL     */
#define KZs_Vers2  0x3cd  /*      89.1 Verstaerkung 2              SOLL     */
/* -------- Monosandwitch Register ------------------ */
#define OPs_Mono   0x3ce  /*  Monosandwitch ein/ausgeschaltet            */
#define OPstMono   0x3cf  /*  Verzoegerungszeit SRZ Seite 49.0, Z.11     */
/* -------- Anfahrschaltungs Register --------------- */
#define ZH_FueReg1 0x3d0  /*  */
#define ZH_Faktor1 0x3d1  /*  */
/* ------------------------------------------------------------------------------ */
#define AWspZur1   0x3d2  /*  Auswerferdruck zurueck Seite 52.0             */
#define AWssZur2   0x3d3  /*  XSSAUS4   S. 52.0  Auswerferrueckweg          */
#define AWsvZur2   0x3d4  /*  XSVAZUR2  S. 52.0  Auswerferrueckweg          */
#define AWspVor2   0x3d5  /*  XSFAUSF2  S. 52.0  Auswerferrueckweg          */
#define AWspZur2   0x3d6  /*  XAWSPZUR2 S. 52.0  Auswerferrueckweg          */
/* ---------------- Max. Aggregatweg -------------------------------------- */
#define MSksSEweg1 0x3d7  /*  Max. Aggregatweg 1.Agg                    */
/* ------------------- SOLLWERT S.49 Spritzeinheit mit Wegmesslineal ------ */
#define SEssVor11  0x3d8  /*  Wegpunkt vor SE1                              */
#define SEssZur11  0x3d9  /*  Wegpunkt zurueck SE1                          */
#define SEssNlpkt1 0x3da  /*  Nullpunkt-Wegpunkt SE1                        */
#define SEsvVor21  0x3db  /*  Geschwindigkeit 2 vor SE1                     */
/* ------------------------------------------------------------------------ */
#define IqtMIUnit  0x3dc  /*  Max. Injection Units                          */
/* ---------------- Optionbit in a new visu it's possible change it to symbit.h */
#define OPm_HoSens 0x3dd  /*  IQT/SPS-Optionsbit 1 = Mit Holmsensor  */
#define SetCntClpCloseStages 0x3de  /* Stages for clamp close */
#define SetCntClpOpenStages 0x3df  /* Stages for clamp open */
#define ALIGNMENTREG4 0x3e0  /*  Reserve 4 (0 Register) */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
#define snregl     0x3e0  /*  Reglernummer                                  */
#define sngrup     0x3e1  /*  Reglernummer                                  */
#define sktemp     0x3e2  /*  Temperatur-Sollwert                           */
#define skgwnw     0x3e3  /*  Toleranz negativ weit                         */
#define skgwne     0x3e4  /*  Toleranz negativ eng                          */
#define skgwpw     0x3e5  /*  Toleranz positiv weit                         */
#define skgwpe     0x3e6  /*  Toleranz positiv eng                          */
#define snmcw      0x3e7  /*  Mode Control Wort (unbenutzt)                 */
#define snxph      0x3e8  /*  XP Heizen                                     */
#define snxpk      0x3e9  /*  XP Kuehlen                                    */
#define sntn       0x3ea  /*  TN Nachstellzeit                              */
#define sntv       0x3eb  /*  TV Vorhaltezeit                               */
#define sntoh      0x3ec  /*  Schaltperiodendauer Heizen                    */
#define sntok      0x3ed  /*  Schaltperiodendauer Kuehlen                   */
#define snshy      0x3ee  /*  Schalthysterese                               */
#define sny        0x3ef  /*  Arbeitspunkt                                  */
#define snymin     0x3f0  /*  minimale Stellgroesse                         */
#define snymax     0x3f1  /*  maximale Stellgroesse                         */
#define sntm       0x3f2  /*  Motorzeitkonstante                            */
#define snspst     0x3f3  /*  Motorzeitkonstante                            */
#define snonof     0x3f4  /*  Heizung ein/aus (unbenutzt in Malterdingen)   */
#define snssol     0x3f5  /*  Strom Sollwert                                */
#define snstel     0x3f6  /*  Sollwert fuer Steller (frueher Strombegrenz.) */
#define snthty     0x3fb  /*  Thermoelement-Typ                             */
#define snmess     0x3fc  /*  Messung ein/aus                               */
#define snfunc     0x3fd  /*  Funktion (Steller, 2-, 3-Punkt-Regler)        */
#define snloop     0x3fe  /*  Schleifennummer (unbenutzt)                   */
#define sncnty     0x3ff  /*  Konvertertyp (unbenutzt)                      */


/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ---------------- Konfigurationsseite 89.5 ------------------------------ */
#define MSisOff1   0x400  /*  IST Formwegoffset                             */
#define MSisOff11  0x401  /*  IST Formwegoffset                             */
#define MSisOff12  0x402  /*  IST Formwegoffset                             */
#define MSisOff2   0x403  /*  IST Auswerferoffset                           */
#define MSisOff21  0x404  /*  IST Formwegoffset                             */
#define MSisOff22  0x405  /*  IST Formwegoffset                             */
#define MSisOff3   0x406  /*  IST Einspritzwegoffset 1.Agg                  */
#define MSisOff31  0x407  /*  IST Formwegoffset                             */
#define MSisOff32  0x408  /*  IST Formwegoffset                             */
#define MSisOff4   0x409  /*  IST Einspritzwegoffset 2.Agg                  */
#define MSisOff8   0x40a  /*  IST Seriennumer Wegmesslineal 1. Agg LONG     */
#define MSisOff83  0x40c  /*  IST Weg-Position 1.Agg LONG                   */
#define MSifOffSP  0x40e  /*  IST Einspritzkraftoffset 1.Agg                */
#define MSifOffSP2 0x40f  /*  IST Einspritzkraftoffset 2.Agg                */
#define MSifOffGK  0x410  /*  IST Gelenkopfkraftoffset                      */
#define MSikOffET  0x411  /*  IST E-Schrank T.-Offset                       */
#define MSinHolm   0x412  /*  IST Anzahl Holmdehnungss                      */
#define GKikKraft  0x413  /*  IST Gelenkkopfkraftoffset                     */
#define SPikKraft  0x414  /*  IST Einspritzkraftoffset                      */
#define GKikProz   0x415  /*  IST Gelenkkopfreibung Seite 17.2              */
/* ------------------------------------------------------------------------ */
#define MSinSta    0x416  /*  */
#define MSinMld    0x417  /*  */
/* ------------------------------------------------------------------------ */
#define ZSmnSchmier 0x418  /*  IST LONG Schmierintervalle Seite 89.5         */
#define HZit_Verz1 0x41a  /*  Schneckenfreigabeverz|gerungszeit Agg1  */
/* ----------------- Maschinen-Abgleich-Seiten ----------------------------- */
#define WSikGain   0x41b  /*  89.1 Werkzeug schliessen Gain   IST           */
#define WOikOff    0x41c  /*  89.1 Werkzeug oeffnen Offset    IST           */
#define WOikGain   0x41d  /*  89.1 Werkzeug oeffnen Gain      IST           */
/* ---------------- END Abgleichseite 89.1 -------------------------------- */
#define AWikVOff   0x41e  /*  89.2 Auswerfer vor Offset       IST           */
#define AWikVGain  0x41f  /*  89.2 Auswerfer vor Gain         IST           */
#define AWikZOff   0x420  /*  89.2 Auswerfer zurueck Offset   IST           */
#define AWikZGain  0x421  /*  89.2 Auswerfer zurueck Gain     IST           */
/* ---------------- END Abgleichseite 89.2 -------------------------------- */
#define PLivAMess  0x422  /*  89.3 Akt. Plastifizier Ist-Anzeige Mess IST   */
#define PLivDMess  0x423  /*  89.3 Def. Plastifizier Ist-Anzeige Mess IST   */
#define PLivAOben  0x424  /*  89.3 Akt. Plastifizier Ist-Anzeige Oben IST   */
#define PLivDOben  0x425  /*  89.3 Def. Plastifizier Ist-Anzeige Oben IST   */
#define PLikARamp1 0x426  /*  89.3 Akt. Plastifizier_Rampe Agg.1   IST      */
#define PLikDRamp1 0x427  /*  89.3 Def. Plastifizier_Rampe Agg.1   IST      */
#define PLikAGest1 0x428  /*  89.3 Akt. Plastifizieren gest. Agg.1 IST      */
#define PLikDGest1 0x429  /*  89.3 Def. Plastifizieren gest. Agg.1 IST      */
#define PLikARamp2 0x42a  /*  89.3 Akt. Plastifizier_Rampe Agg.2   IST      */
#define PLikDRamp2 0x42b  /*  89.3 Def. Plastifizier_Rampe Agg.2   IST      */
#define PLikAGest2 0x42c  /*  89.3 Akt. Plastifizieren gest. Agg.2 IST      */
#define PLikDGest2 0x42d  /*  89.3 Def. Plastifizieren gest. Agg.2 IST      */
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
/* ---------------- Diagnoseseite Schliessdruckaufbau 87.5 ---------------- */
#define SDRitAAufV 0x42e  /*  87.5 Akt. SDR-Aufbauverzoegerungszeit IST     */
#define SDRitDAufV 0x42f  /*  87.5 Def. SDR-Aufbauverzoegerungszeit IST     */
#define SDRitAAufB 0x430  /*  87.5 Akt. SDR-Aufbauzeit IST                  */
#define SDRitDAufB 0x431  /*  87.5 Def. SDR-Aufbauzeit IST                  */
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
#define FDiagDAKT  0x432  /*  ULONG Digitaleingaenge fuer Seite 87.8         */
#define FDiagA_A01 0x434  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A02 0x435  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A03 0x436  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A04 0x437  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A05 0x438  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A06 0x439  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A07 0x43a  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A08 0x43b  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A09 0x43c  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A10 0x43d  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A11 0x43e  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A12 0x43f  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A13 0x440  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A14 0x441  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A15 0x442  /*       Analogeingaenge fuer Seite 87.8          */
#define FDiagA_A16 0x443  /*       Analogeingaenge fuer Seite 87.8          */
/* ---------------- Standard Diagnoseseite -------------------------------------- */
#define SDiagDAKT  0x444  /*  LONG Digitaleingaenge fuer Seite 88.3         */
#define SDiagA_A01 0x446  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A02 0x447  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A03 0x448  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A04 0x449  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A05 0x44a  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A06 0x44b  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A07 0x44c  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A08 0x44d  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A09 0x44e  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A10 0x44f  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A11 0x450  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A12 0x451  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A13 0x452  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A14 0x453  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A15 0x454  /*       Analogeingaenge fuer Seite 88.3          */
#define SDiagA_A16 0x455  /*       Analogeingaenge fuer Seite 88.3          */
/* ---------------- Matrixtastatur ---------------------------------------- */
#define A0Input    0x456  /*  */
#define A1Input    0x457  /*  */
#define A2Input    0x458  /*  */
#define A3Input    0x459  /*  */
#define ActStsMachA4Inp 0x45a  /*  */
/* ---------------- SPS-CPU-Typ ------------------------------------------- */
#define SPSCPUType 0x45b  /*  SPS CPY-Type (z.B. CP100, CP151, CP152 usw.)  */
/* ---------------- WegMess-Typ ------------------------------------------- */
#define SPSWegMTyp 0x45c  /*  SPS Weg-Messtyp (Analog, CAN usw.)            */
#define DiagMaxMod 0x45d  /*  Anzahl der zu diagnostiziere Module           */
/* ---------------- Ventil-Auswahl ---------------------------------------- */
#define VenTypAusw 0x45e  /*  Ventil-Auswahl (verwendet/nicht verwendet)    */
#define VenTypOffs 0x45f  /*  Ventil Offset-Anzahl (1 Offset/2 Offset)      */
/* ---------------- Kernzug-Ventil-Auswahl -------------------------------- */
#define KZVTypOffs 0x460  /*  KZ-Ventil Offset-Anzahl (1 Offset/2 Offset)   */
/* ------------------------------------------------------------------------ */
#define HXinPageAW 0x461  /*  Anzeige-Auswahregister fuer die Einstellungsseite serielle Temperiergeraete  */
/* ------------------------------------------------------------------------ */
/* Register fuer Ventilabgleichseite                                        */
/* ------------------------------------------------------------------------ */
#define MAi_Offs1  0x462  /*  89.1 Offset 1                    IST    */
#define MAi_Offs2  0x463  /*  89.1 Offset 2                    IST    */
#define MAi_Vers1  0x464  /*  89.1 Verstaerkung 1              IST    */
#define MAi_Vers2  0x465  /*  89.1 Verstaerkung 2              IST    */
/* ------------------------------------------------------------------------ */
/* Register fuer Kernzug-Ventilabgleichseite                                */
/* ------------------------------------------------------------------------ */
#define KZi_Offs1  0x466  /*  89.2 Offset 1                    IST    */
#define KZi_Offs2  0x467  /*  89.2 Offset 2                    IST    */
#define KZi_Vers1  0x468  /*  89.2 Verstaerkung 1              IST    */
#define KZi_Vers2  0x469  /*  89.2 Verstaerkung 2              IST    */
/* ------------------------------------------------------------------------ */
/* Register fuer DM-Daten fuer Freiauswaehlbare Diagnoseseite               */
/* ------------------------------------------------------------------------ */
#define DiagSysTyp 0x46a  /*  Systemtyp                                     */
#define DiagBusNr  0x46b  /*  BusNr (Basisrueckwand, Erweiterung1,2,3,4)    */
#define DiagModNr  0x46c  /*  Modulnummer                                   */
#define DiagIndTab 0x46d  /*  Index in Diagnosetabelle                      */
/* ------------------------------------------------------------------------ */
/* Register fuer Drive-Fehlermeldungen                                      */
/* ------------------------------------------------------------------------ */
#define Drv_Id     0x46e  /*  WORD Drv_Id                                   */
#define DrvErrCode 0x46f  /*  WORD Err_Code                                 */
#define DrvErrInfo 0x470  /*  LONG Err_Info                                 */
#define DrvParId   0x472  /*  WORD Par_Id                                   */
#define DrvJahr    0x473  /*  WORD Jahr                                     */
#define DrvM_T_S   0x474  /*  WORD M_T_S Monat Tag Stunde                   */
#define DrvM_S     0x475  /*  WORD M_S Minute Sekunde                       */
/* -------------------- Register fuer die Diagnoseseiten ------------------- */
/* --------------------- Diagnoseseite 87.0 Aggregat 1 --------------------- */
#define diagm1     0x476  /*  Diagnoseseite ULONG                           */
#define diagm2     0x478  /*  Diagnoseseite                                 */
#define diagm3     0x479  /*  Diagnoseseite                                 */
#define diagm4     0x47a  /*  Diagnoseseite ULONG                           */
#define diagm5     0x47c  /*  Diagnoseseite                                 */
#define diagm6     0x47d  /*  Diagnoseseite                                 */
#define diagm7     0x47e  /*  Diagnoseseite ULONG                           */
#define diagm8     0x480  /*  Diagnoseseite                                 */
#define diagm9     0x481  /*  Diagnoseseite                                 */
#define diagma     0x482  /*  Diagnoseseite ULONG                           */
#define diagmb     0x484  /*  Diagnoseseite                                 */
#define diagmc     0x485  /*  Diagnoseseite                                 */
#define diagmd     0x486  /*  Diagnoseseite ULONG                           */
#define diagme     0x488  /*  Diagnoseseite                                 */
#define diagmf     0x489  /*  Diagnoseseite                                 */
#define diagm10    0x48a  /*  Diagnoseseite ULONG                           */
#define diagm11    0x48c  /*  Diagnoseseite                                 */
#define diagm12    0x48d  /*  Diagnoseseite                                 */
#define diagm13    0x48e  /*  Diagnoseseite ULONG                           */
#define diagm14    0x490  /*  Diagnoseseite                                 */
#define diagm15    0x491  /*  Diagnoseseite                                 */
#define diagm16    0x492  /*  Diagnoseseite ULONG                           */
#define diagm17    0x494  /*  Diagnoseseite                                 */
#define diagm18    0x495  /*  Diagnoseseite                                 */
#define diagm19    0x496  /*  Diagnoseseite ULONG                           */
#define diagm1a    0x498  /*  Diagnoseseite                                 */
#define diagm1b    0x499  /*  Diagnoseseite                                 */
#define diagm1c    0x49a  /*  Diagnoseseite ULONG                           */
#define diagm1d    0x49c  /*  Diagnoseseite                                 */
#define diagm1e    0x49d  /*  Diagnoseseite                                 */
#define diagm1f    0x49e  /*  Diagnoseseite ULONG                           */
#define diagm20    0x4a0  /*  Diagnoseseite                                 */
#define diagm21    0x4a1  /*  Diagnoseseite                                 */
#define diagm22    0x4a2  /*  Diagnoseseite ULONG                           */
#define diagm23    0x4a4  /*  Diagnoseseite                                 */
#define diagm24    0x4a5  /*  Diagnoseseite                                 */
#define diagm25    0x4a6  /*  Diagnoseseite ULONG                           */
#define diagm26    0x4a8  /*  Diagnoseseite                                 */
#define diagm27    0x4a9  /*  Diagnoseseite                                 */
#define diagm28    0x4aa  /*  Diagnoseseite ULONG                           */
#define diagm29    0x4ac  /*  Diagnoseseite                                 */
#define diagm2a    0x4ad  /*  Diagnoseseite                                 */
#define diagm2b    0x4ae  /*  Diagnoseseite ULONG                           */
#define diagm2c    0x4b0  /*  Diagnoseseite                                 */
#define diagm2d    0x4b1  /*  Diagnoseseite                                 */
#define diagm2e    0x4b2  /*  Diagnoseseite ULONG                           */
#define diagm2f    0x4b4  /*  Diagnoseseite                                 */
#define diagm30    0x4b5  /*  Diagnoseseite                                 */
#define diagm31    0x4b6  /*  Diagnoseseite ULONG                           */
#define diagm32    0x4b8  /*  Diagnoseseite                                 */
#define diagm33    0x4b9  /*  Diagnoseseite                                 */
#define diagm34    0x4ba  /*  Diagnoseseite ULONG                           */
#define diagm35    0x4bc  /*  Diagnoseseite                                 */
#define diagm36    0x4bd  /*  Diagnoseseite                                 */
/* --------------------- Diagnoseseite 17.2 -------------------------------- */
#define diagm140   0x4be  /*  Diagnoseseite                                 */
#define diagm141   0x4bf  /*  Diagnoseseite                                 */
#define diagm142   0x4c0  /*  Diagnoseseite                                 */
#define diagm143   0x4c1  /*  Diagnoseseite                                 */
#define diagm144   0x4c2  /*  Diagnoseseite                                 */
#define diagm145   0x4c3  /*  Diagnoseseite                                 */
#define diagm146   0x4c4  /*  Diagnoseseite                                 */
#define diagm147   0x4c5  /*  Diagnoseseite                                 */
#define diagm148   0x4c6  /*  Diagnoseseite                                 */
#define diagm149   0x4c7  /*  Diagnoseseite                                 */
#define diagm14a   0x4c8  /*  Diagnoseseite                                 */
#define diagm14b   0x4c9  /*  Diagnoseseite                                 */
#define diagm14c   0x4ca  /*  Diagnoseseite                                 */
#define diagm14d   0x4cb  /*  Diagnoseseite                                 */
#define diagm14e   0x4cc  /*  Diagnoseseite                                 */
#define diagm14f   0x4cd  /*  Diagnoseseite                                 */
#define diagm150   0x4ce  /*  Diagnoseseite                                 */
#define diagm151   0x4cf  /*  Diagnoseseite                                 */
#define diagm152   0x4d0  /*  Diagnoseseite                                 */
#define diagm153   0x4d1  /*  Diagnoseseite                                 */
#define diagm154   0x4d2  /*  Diagnoseseite                                 */
#define diagm155   0x4d3  /*  Diagnoseseite                                 */
#define diagm156   0x4d4  /*  Diagnoseseite                                 */
#define diagm157   0x4d5  /*  Diagnoseseite                                 */
#define diagm158   0x4d6  /*  Diagnoseseite                                 */
#define diagm159   0x4d7  /*  Diagnoseseite                                 */
#define diagm15a   0x4d8  /*  Diagnoseseite                                 */
#define diagm15b   0x4d9  /*  Diagnoseseite                                 */
#define diagm15c   0x4da  /*  Diagnoseseite                                 */
#define diagm15d   0x4db  /*  Diagnoseseite                                 */
#define diagm15e   0x4dc  /*  Diagnoseseite                                 */
#define diagm15f   0x4dd  /*  Diagnoseseite                                 */
#define diagm160   0x4de  /*  Diagnoseseite                                 */
#define diagm161   0x4df  /*  Diagnoseseite                                 */
#define diagm162   0x4e0  /*  Diagnoseseite                                 */
#define diagm163   0x4e1  /*  Diagnoseseite                                 */
#define diagm164   0x4e2  /*  Diagnoseseite                                 */
#define diagm165   0x4e3  /*  Diagnoseseite                                 */
#define diagm166   0x4e4  /*  Diagnoseseite                                 */
#define diagm167   0x4e5  /*  Diagnoseseite                                 */
#define diagm168   0x4e6  /*  Diagnoseseite                                 */
#define diagm169   0x4e7  /*  Diagnoseseite                                 */
#define diagm16a   0x4e8  /*  Diagnoseseite                                 */
#define diagm16b   0x4e9  /*  Diagnoseseite                                 */
/* ------------------------------------------------------------------------ */
#define formact    0x4ea  /*  Istwert fuer Formhoehenabgleich               */
/* ------------------------------------------------------------------------ */
#define xsnsp1     0x4eb  /*  Farbinformation Schnellspannseite 56          */
#define xsnsp2     0x4ec  /*  Farbinformation Schnellspannseite 56          */
/* ------------------- Diagnoseseite 87.0 Aggregat 2 ---------------------- */
#define diagm37    0x4ed  /*  Diagnoseseite                                 */
#define diagm38    0x4ee  /*  Diagnoseseite                                 */
#define diagm39    0x4ef  /*  Diagnoseseite                                 */
#define diagm3a    0x4f0  /*  Diagnoseseite                                 */
#define diagm3b    0x4f1  /*  Diagnoseseite                                 */
#define diagm3c    0x4f2  /*  Diagnoseseite                                 */
#define diagm3d    0x4f3  /*  Diagnoseseite                                 */
#define diagm3e    0x4f4  /*  Diagnoseseite                                 */
#define diagm3f    0x4f5  /*  Diagnoseseite                                 */
#define diagm40    0x4f6  /*  Diagnoseseite                                 */
#define diagm41    0x4f7  /*  Diagnoseseite                                 */
#define diagm42    0x4f8  /*  Diagnoseseite                                 */
#define diagm43    0x4f9  /*  Diagnoseseite                                 */
#define diagm44    0x4fa  /*  Diagnoseseite                                 */
#define diagm45    0x4fb  /*  Diagnoseseite                                 */
#define diagm46    0x4fc  /*  Diagnoseseite                                 */
#define diagm47    0x4fd  /*  Diagnoseseite                                 */
#define diagm48    0x4fe  /*  Diagnoseseite                                 */
#define diagm49    0x4ff  /*  Diagnoseseite                                 */
#define diagm4a    0x500  /*  Diagnoseseite                                 */
#define diagm4b    0x501  /*  Diagnoseseite                                 */
#define diagm4c    0x502  /*  Diagnoseseite ULONG                            */
#define diagm4d    0x504  /*  Diagnoseseite                                 */
#define diagm4e    0x505  /*  Diagnoseseite                                 */
#define diagm4f    0x506  /*  Diagnoseseite ULONG                            */
#define diagm50    0x508  /*  Diagnoseseite                                 */
#define diagm51    0x509  /*  Diagnoseseite                                 */
#define diagm52    0x50a  /*  Diagnoseseite ULONG                            */
#define diagm53    0x50c  /*  Diagnoseseite                                 */
#define diagm54    0x50d  /*  Diagnoseseite                                 */
/* ------------------------------------------------------------------------ */
#define HZs_CfgReg 0x50e  /* Heizungskonfiguration Reglernummer Sollwert */
#define HZi_CfgReg 0x50f  /* Heizungskonfiguration Reglernummer Istwert */
#define HZmt_Conf  0x510  /* Heizungskonfiguration IO-Belegung Thermocouple (Fuehler) */
#define HZmh_Conf  0x511  /* Heizungskonfiguration IO-Belegung Ausgang Heizen */
#define HZmk_Conf  0x512  /* Heizungskonfiguration IO-Belegung Ausgang Heizen */
/* ------------------------------------------------------------------------ */
#define LVis_Strt1 0x513  /* Clamp stroke start air ejector 1 */
#define LVis_Strt2 0x514  /* Clamp stroke start air ejector 2 */
#define LVis_Strt3 0x515  /* Clamp stroke start air ejector 3 */
#define LVis_Strt4 0x516  /* Clamp stroke start air ejector 4 */
#define LVis_Strt5 0x517  /* Clamp stroke start air ejector 5 */
#define LVis_Strt6 0x518  /* Clamp stroke start air ejector 6 */
#define LVis_Strt7 0x519  /* Clamp stroke start air ejector 7 */
#define LVis_Strt8 0x51a  /* Clamp stroke start air ejector 8 */
#define LVis_End1  0x51b  /* Clamp stroke end air ejector 1 */
#define LVis_End2  0x51c  /* Clamp stroke end air ejector 2 */
#define LVis_End3  0x51d  /* Clamp stroke end air ejector 3 */
#define LVis_End4  0x51e  /* Clamp stroke end air ejector 4 */
#define LVis_End5  0x51f  /* Clamp stroke end air ejector 5 */
#define LVis_End6  0x520  /* Clamp stroke end air ejector 6 */
#define LVis_End7  0x521  /* Clamp stroke end air ejector 7 */
#define LVis_End8  0x522  /* Clamp stroke end air ejector 8 */
/* ------------------- Text Strings die von der SPS gelesen werden koennnen */
/* ------------------- laenge je 26 Byte ---------------------------------- */
#define IText_1    0x523  /*  SPS Text 1                                    */
#define IText_2    0x53d  /*  SPS Text 2                                    */
#define IText_3    0x557  /*  SPS Text 3                                    */
#define IText_4    0x571  /*  SPS Text 4                                    */
#define IText_5    0x58b  /*  SPS Parameter-Kennungen                       */
#define IText_6    0x5a5  /*  SPS Drive-Kennungen 1                         */
#define IText_7    0x5bf  /*  SPS Drive-Kennungen 2                         */
/* ------------------- Text Strings Seite 17.3 die von der SPS gelesen werden */
/* ------------------- laenge je 70 Byte ---------------------------------- */
#define TDrvModul11 0x5d9  /*  DriveModultext                                */
#define TDrvModul12 0x5eb  /*  DriveModultext                                */
#define TDrvMotor11 0x5fd  /*  DriveMotortext                                */
#define TDrvMotor12 0x60f  /*  DriveMotortext                                */
#define TDrvSerNr11 0x621  /*  DriveMotortext                                */
#define TDrvSerNr12 0x633  /*  DriveMotortext                                */
/* ------------------------------------------------------------------------ */
/* END Istwert-Register die mit TP_RD_SPEC gelesen werden                   */
/* ------------------------------------------------------------------------ */


/* -------------------- Definitionen fuer frei progr. Kernzuege ----------  */
#define KEprgno    0x645  /*  Kernzug-Programmnummer                      */
#define KEeinricht 0x646  /*  Ueberwachung im Einrichten                  */
#define KEgrundst  0x647  /*  Grundstellung der Kerne                     */
#define KEpgmstat  0x648  /*  Aenderungszustand des Kernzugprogramms  0=aktuell, 1=geaendert, 2=geprueft */
#define KEparupd   0x649  /*  Anzeige der Parameteraenderungen 1=geaend. */
#define KEpgmlines 0x64a  /*  Zeilenanzahl des Kernzugprogramms        */
#define KEdlenable 0x64b  /*  download enable Register Bit 0 = 1 sperrt den Datenaustausch */
#define KEdlstat   0x64c  /*  Status der Datenuebertragung 0=okay         */
#define KEsync     0x64d  /*  Handshake-Register beim download            */
#define KEIst1     0x64e  /*  Ist-Stellung der Kerne 1 - 9                */
#define KEIst2     0x64f  /*  aus=0, eingef.=1, ausgef.=2, in Zw.pos.=3   */
#define KEIst3     0x650  /*  */
#define KEIst4     0x651  /*  */
#define KEIst5     0x652  /*  */
#define KEIst6     0x653  /*  */
#define KEIst7     0x654  /*  */
#define KEIst8     0x655  /*  */
#define KEIst9     0x656  /*  */
#define KEError1   0x657  /*  Fehler der Kerne 1 - 9 je 32 Bit   */
#define KEError2   0x659  /*  */
#define KEError3   0x65b  /*  */
#define KEError4   0x65d  /*  */
#define KEError5   0x65f  /*  */
#define KEError6   0x661  /*  */
#define KEError7   0x663  /*  */
#define KEError8   0x665  /*  */
#define KEError9   0x667  /*  */
#define KEError    0x669  /*  allgemeine Fehler im Kernzugprogramm  */
#define KEEvalid   0x66b  /*  Freigabe fuer Kernstellungen im Stepbetrieb    */
#define KEExpSoll1 0x66c  /*  Erwartete Stellung der Kerne im Stepbetrieb    */
#define KEExpSoll2 0x66d  /*  aus=0, eingef.=1, ausgef.=2, in Zw.pos.=3      */
#define KEExpSoll3 0x66e  /*  */
#define KEExpSoll4 0x66f  /*  */
#define KEExpSoll5 0x670  /*  */
#define KEExpSoll6 0x671  /*  */
#define KEExpSoll7 0x672  /*  */
#define KEExpSoll8 0x673  /*  */
#define KEExpSoll9 0x674  /*  */
#define KE_NrSchraub 0x675  /*  enth„lt Nummer des Kerns der zum Schrauben freigegeben ist */
#define KE_NrWend  0x676  /*  enth„lt Nummer des Kerns der zum Wendem freigegeben ist */
#define KE_SperrMaske 0x677  /*  maskiert (sperrt) Kerne Bit 0 = 1 -> Kern 1 gesperrt usw.            */

#define KELineNo   0x685  /*  Programmzeile mit Zeilennummern und 12 Parametern */

/* ------- Standard Prozessgrafik Bereich  -------------------------------- */
#define meas_event 0x745  /*  Messung laueft/fertig                         */
#define startrec   0x746  /*  Start Einzelmessung                           */
#define reqblk_ist 0x747  /*  Request-Block Istkurve                        */
#define ackblk_ist 0x749  /*  Acknowledge-Block                             */
#define pg_mode    0x74a  /*  Betriebsarten (Feld) [Funktion][Funktionseinheit]  */
#define meastime   0x74e  /*  Messzeiten [Funktion][Funktionseinheit]       */
#define delay      0x752  /*  Startverzoegerungen [Funktion][Funktionseinheit]  */
#define interval   0x756  /*  Messintervalle Zyklen [Funktion][Funktionseinheit]  */
#define pg_aggregat 0x75a  /*  Standardgrafik Aggregat fuer Mehrfarbmachinen  */
#define pg_splitind 0x75b  /*  Split index for injection/back and hold  */
#define datablk_ist 0x765  /*  Kommunikationsbereich Istkurve                */



/* die in der Standardgrafik nicht verwendeten Register werden in den IST  */
/* Datenblockbereich gelegt damit sie zumindest definiert sind             */
#define datablk_soll 0x765  /*  Kommunikationsbereich Sollkurve               */
#define status     0x765  /*  Status, Bit 0 = 0 Download enable             */
#define reqblk_soll 0x766  /*  Request-Block Sollkurve                       */
#define x_scale    0x767  /*  Maximale Weg fuer X-Achse [Funktion][Funktionseinheit]  */
#define tol_switch 0x76b  /*  Toleranz ein/aus (39 Werte) [Funktion][Funktionseinheit][Kurve]  */
#define tolerance  0x781  /*  Toleranzen in % (39 Werte) [Funktion][Funktionseinheit][Kurve]  */
#define modework   0x7b7  /*  Mode Arbeitsberechnung [Funktion][Funktionseinheit]  */
#define startwork  0x7bb  /*  Beginn Arbeitsberechnung [Funktion][Funktionseinheit]  */
#define stopwork   0x7bf  /*  Ende Arbeitsberechnung [Funktion][Funktionseinheit]  */
#define istwork    0x7c3  /*  Arbeit Istwert [Funktion][Funktionseinheit]   */
#define refwork    0x7c7  /*  Arbeit Referenz [Funktion][Funktionseinheit]  */
#define tolwork    0x7cb  /*  Arbeit Toleranz in % [Funktion][Funktionseinheit]  */
#define pres_area  0x7cf  /*  Schliesskolbenflaeche [Funktionseinheit]      */
#define yscal      0x7d3  /*  Y-Skalierung [Funktion][Funktionseinheit][Kurve]  */
#define ymax       0x7f9  /*  Messbereichsendwert [Kanal]!!!! d. h. 4 Register  */
#define tol_errs   0x7fd  /*  Anzahl der Toleranueberschreitungen in Folge  */
#define free_reg0  0x7fe  /*  zur freien Verwendung waehrend der Testzeit   */
#define free_reg1  0x7ff  /*  zur freien Verwendung waehrend der Testzeit   */
#define free_reg2  0x800  /*  zur freien Verwendung waehrend der Testzeit   */
#define free_reg3  0x801  /*  zur freien Verwendung waehrend der Testzeit   */
#define free_reg4  0x802  /*  zur freien Verwendung waehrend der Testzeit   */
#define free_reg5  0x803  /*  zur freien Verwendung waehrend der Testzeit   */
#define free_reg6  0x804  /*  zur freien Verwendung waehrend der Testzeit   */

#define next_free  0x815  /*  */
/* ------------------------- Sonderseite 48 Airpress neu ----------------- */
#define air_on     0x815  /*  Airpress Seite 48 (Sonderprogramm)  */
#define dues_zu    0x816  /*  */
#define stverz_d1  0x817  /*  */
#define stverz_d2  0x818  /*  */
#define stverz_d3  0x819  /*  */
#define stverz_d4  0x81a  /*  */
#define stact1_d1  0x81b  /*  */
#define stact1_d2  0x81c  /*  */
#define stact1_d3  0x81d  /*  */
#define stact1_d4  0x81e  /*  */
#define spres1_d1  0x81f  /*  */
#define spres1_d2  0x820  /*  */
#define spres1_d3  0x821  /*  */
#define spres1_d4  0x822  /*  */
#define stact2_d1  0x823  /*  */
#define stact2_d2  0x824  /*  */
#define stact2_d3  0x825  /*  */
#define stact2_d4  0x826  /*  */
#define spres2_d1  0x827  /*  */
#define spres2_d2  0x828  /*  */
#define spres2_d3  0x829  /*  */
#define spres2_d4  0x82a  /*  */
#define stact3_d1  0x82b  /*  */
#define stact3_d2  0x82c  /*  */
#define stact3_d3  0x82d  /*  */
#define stact3_d4  0x82e  /*  */
#define spres3_d1  0x82f  /*  */
#define spres3_d2  0x830  /*  */
#define spres3_d3  0x831  /*  */
#define spres3_d4  0x832  /*  */
#define stact4_d1  0x833  /*  */
#define stact4_d2  0x834  /*  */
#define stact4_d3  0x835  /*  */
#define stact4_d4  0x836  /*  */
#define spres4_d1  0x837  /*  */
#define spres4_d2  0x838  /*  */
#define spres4_d3  0x839  /*  */
#define spres4_d4  0x83a  /*  */
#define stact5_d1  0x83b  /*  */
#define stact5_d2  0x83c  /*  */
#define stact5_d3  0x83d  /*  */
#define stact5_d4  0x83e  /*  */
#define spres5_d1  0x83f  /*  */
#define spres5_d2  0x840  /*  */
#define spres5_d3  0x841  /*  */
#define spres5_d4  0x842  /*  Airpress Seite 48 (Sonderprogramm)  */
#define APd_Type   0x843  /*  */
#define APd_Mode   0x844  /*  */
#define APspSysT   0x845  /*  */
#define APstRmp1D1 0x846  /*  */
#define APstRmp1D2 0x847  /*  */
#define APstRmp1D3 0x848  /*  */
#define APstRmp1D4 0x849  /*  */
#define APstRmp1D5 0x84a  /*  */
#define APstRmp2D1 0x84b  /*  */
#define APstRmp2D2 0x84c  /*  */
#define APstRmp2D3 0x84d  /*  */
#define APstRmp2D4 0x84e  /*  */
#define APstRmp2D5 0x84f  /*  */
#define APstRmp3D1 0x850  /*  */
#define APstRmp3D2 0x851  /*  */
#define APstRmp3D3 0x852  /*  */
#define APstRmp3D4 0x853  /*  */
#define APstRmp3D5 0x854  /*  */
#define APstRmp4D1 0x855  /*  */
#define APstRmp4D2 0x856  /*  */
#define APstRmp4D3 0x857  /*  */
#define APstRmp4D4 0x858  /*  */
#define APstRmp4D5 0x859  /*  */
#define APstRmp5D1 0x85a  /*  */
#define APstRmp5D2 0x85b  /*  */
#define APstRmp5D3 0x85c  /*  */
#define APstRmp5D4 0x85d  /*  */
#define APstRmp5D5 0x85e  /*  */
#define WKZDues_D1 0x85f  /*  */
#define WKZDues_D2 0x860  /*  */
#define WKZDues_D3 0x861  /*  */
#define WKZDues_D4 0x862  /*  */
#define ALIGNMENTREG5 0x863  /*  Reserve 5 (2 Register) */

/* Permanente Register fuer das Gillette-Sonderprogramm         */
#define gil_xson0  0x865  /*  */
#define gil_xson1  0x866  /*  */
#define gil_xson2  0x867  /*  */
#define gil_xson3  0x868  /*  */
#define gil_xson4  0x869  /*  */
#define gil_xson5  0x86a  /*  */
#define gil_xson6  0x86b  /*  */
#define gil_xson7  0x86c  /*  */
#define gil_xson8  0x86d  /*  */
#define gil_xson9  0x86e  /*  */
#define gil_xson10 0x86f  /*  */
#define gil_xson11 0x870  /*  */
#define gil_xson12 0x871  /*  */
#define gil_xson13 0x872  /*  */
#define gil_xson14 0x873  /*  */
#define gil_xson15 0x874  /*  */
#define gil_sson0  0x875  /*  */
#define gil_sson1  0x876  /*  */
#define gil_sson2  0x877  /*  */
#define gil_sson3  0x878  /*  */
#define gil_sson4  0x879  /*  */
#define gil_sson5  0x87a  /*  */
#define gil_sson6  0x87b  /*  */
#define gil_sson7  0x87c  /*  */
#define gil_sson8  0x87d  /*  */
#define gil_sson9  0x87e  /*  */
#define gil_sson10 0x87f  /*  */
#define gil_sson11 0x880  /*  */
#define gil_sson12 0x881  /*  */
#define gil_sson13 0x882  /*  */
#define gil_sson14 0x883  /*  */
#define gil_sson15 0x884  /*  */
#define gil_sson16 0x885  /*  */
#define gil_sson17 0x886  /*  */
#define gil_sson18 0x887  /*  */
#define gil_sson19 0x888  /*  */
#define gil_sson20 0x889  /*  */
#define gil_sson21 0x88a  /*  */
#define gil_sson22 0x88b  /*  */
#define gil_sson23 0x88c  /*  */
#define gil_sson24 0x88d  /*  */
#define gil_sson25 0x88e  /*  */
#define gil_sson26 0x88f  /*  */
#define gil_sson27 0x890  /*  */
#define gil_sson28 0x891  /*  */
#define gil_sson29 0x892  /*  */
#define gil_sson30 0x893  /*  */
#define gil_sson31 0x894  /*  */
#define gil_sson32 0x895  /*  */
#define gil_sson33 0x896  /*  */
#define gil_sson34 0x897  /*  */
#define gil_sson35 0x898  /*  */
#define gil_sson36 0x899  /*  */
#define gil_sson37 0x89a  /*  */
#define gil_sson38 0x89b  /*  */
#define gil_sson39 0x89c  /*  */
#define gil_sson40 0x89d  /*  */
#define gil_sson41 0x89e  /*  */
#define gil_sson42 0x89f  /*  */
#define gil_sson43 0x8a0  /*  */
#define gil_sson44 0x8a1  /*  */
#define gil_sson45 0x8a2  /*  */
#define gil_sson46 0x8a3  /*  */
#define gil_sson47 0x8a4  /*  */
#define gil_sson48 0x8a5  /*  */
#define gil_sson49 0x8a6  /*  */
#define gil_sson50 0x8a7  /*  */
#define gil_sson51 0x8a8  /*  */
#define gil_sson52 0x8a9  /*  */
#define gil_sson53 0x8aa  /*  */
#define gil_sson54 0x8ab  /*  */
#define gil_sson55 0x8ac  /*  */
#define gil_sson56 0x8ad  /*  */
#define gil_sson57 0x8ae  /*  */
#define gil_sson58 0x8af  /*  */
#define gil_sson59 0x8b0  /*  */
#define gil_sson60 0x8b1  /*  */
#define gil_sson61 0x8b2  /*  */
#define gil_sson62 0x8b3  /*  */
#define gil_sson63 0x8b4  /*  */
#define gil_sson64 0x8b5  /*  */
#define gil_sson65 0x8b6  /*  */
#define gil_sson66 0x8b7  /*  */
#define gil_sson67 0x8b8  /*  */
#define gil_sson68 0x8b9  /*  */
#define gil_sson69 0x8ba  /*  */
#define gil_sson70 0x8bb  /*  */
#define gil_sson71 0x8bc  /*  */
#define gil_sson72 0x8bd  /*  */
#define gil_sson73 0x8be  /*  */
#define gil_sson74 0x8bf  /*  */
#define gil_sson75 0x8c0  /*  */
#define gil_sson76 0x8c1  /*  */
#define gil_sson77 0x8c2  /*  */
#define gil_sson78 0x8c3  /*  */
#define gil_sson79 0x8c4  /*  */
#define gil_sson80 0x8c5  /*  */
#define gil_sson81 0x8c6  /*  */
#define gil_sson82 0x8c7  /*  */
#define gil_sson83 0x8c8  /*  */
#define gil_sson84 0x8c9  /*  */
#define gil_sson85 0x8ca  /*  */
#define gil_sson86 0x8cb  /*  */
#define gil_sson87 0x8cc  /*  */
#define gil_sson88 0x8cd  /*  */
#define gil_sson89 0x8ce  /*  */
#define gil_sson90 0x8cf  /*  */
#define gil_sson91 0x8d0  /*  */
#define gil_sson92 0x8d1  /*  */
#define gil_sson93 0x8d2  /*  */
#define gil_sson94 0x8d3  /*  */
#define gil_sson95 0x8d4  /*  */
#define gil_sson96 0x8d5  /*  */
#define gil_sson97 0x8d6  /*  */
#define gil_sson98 0x8d7  /*  */
#define gil_sson99 0x8d8  /*  */
#define gil_sson100 0x8d9  /*  */
#define gil_sson101 0x8da  /*  */
#define gil_sson102 0x8db  /*  */
#define gil_sson103 0x8dc  /*  */
#define gil_sson104 0x8dd  /*  */
#define gil_sson105 0x8de  /*  */
#define gil_sson106 0x8df  /*  */
#define gil_sson107 0x8e0  /*  */
#define gil_sson108 0x8e1  /*  */
#define gil_sson109 0x8e2  /*  */
#define gil_sson110 0x8e3  /*  */
#define gil_sson111 0x8e4  /*  */
#define gil_sson112 0x8e5  /*  */
#define gil_sson113 0x8e6  /*  */
#define gil_sson114 0x8e7  /*  */
#define gil_sson115 0x8e8  /*  */
#define gil_sson116 0x8e9  /*  */
#define gil_sson117 0x8ea  /*  */
#define gil_sson118 0x8eb  /*  */
#define gil_sson119 0x8ec  /*  */

#define IEndAddr   0x8ed  /*  Ende des benutzten Adressraums     */

/*** symgen EOF: last=0x8ec, count=1, (B=285, R=4570) ***/
