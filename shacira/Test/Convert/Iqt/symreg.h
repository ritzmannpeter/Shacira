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
*		                  diagm37 bis diagm87 eingefuegt.
*                       Nur die FG-Woerter sind ULONG  
*                       (diagm2e, diagm31, diagm34,   
*                        diagm4c, diagm4f, diagm52)
*     28.11.96 -HAns-   SDRitAAufV - SDRitDAufB und SDRGenMod - SDRstAufB
*                       eingefuegt.
*		06.12.96 -HAns-   SEgpUst und SEgpUst2 neu definiert
*		19.12.96 -HAns-   DOsnCard und DOi_Akt neu definiert
*		30.12.96 -HAns-   DIsnCard bis AOsnFor16 und DIi_Akt bis AIinAkt16 definiert.
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
*		29.10.97 -PR-     Kernzug-Programmnummer KEprgno eingefuegt.
*		06.11.97 -PR-     Nummer des Schraubkerns KE_NrSchraub eingefuegt.
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
*
*     03.12.98 -HAns-   ACHTUNG in der naechsten Unterversion muessen die
*                       Register tolerance (0x67c -> 0x64c) bis free_reg9 
*                       (0x6f2 -> 0x6c2) geaendert werden.
*                       Aufgrund dessen mussten die Register air_on (0x6d0 -> 0x700)
*                       bis gil_sson119 (0x787 -> 0x7b7) geaendert werden.
*     11.10.99 -HAns-   Fast-Register nach Aggregat-Zuordnung sortiert.
*                       tolerace bis gil_sson119 geaendert (s.o.)
*     12.04.01 -HAns-   KbA0Input - KbA3Input neu eingefuegt
*     05.07.02 -HA-     HZit_Verz1-6 eingefuegt.
*     10.07.02 -HA-     Register fuer Wenden und Werkzeugauswerfer eingefuegt.
*                       OPinKarton, OPsnKarton, OPs_Neust eingefuegt.
*                       SZinSUB eingefuegt.
*     12.07.02 -HA-     Register IqtSSAct, AWspZur eingefuegt.
*                       SEisNlpkt1,2 , SEssVor11 bis SEssNlpkt2 eingefuegt.
*                       ZHs_Wasser eingefuegt.
*                       HXsnIF, HXsnProto, HXsnBaud,HXsnDatBit, HXsnStpBit und 
*                       HXsnParity eingefuegt.
*                       IOinDIist, IOinDOist und IOinAOist1-4 eingefuegt
*                       IOs_DIfkt1 bis IOsnAOpar4 eingefuegt.
*                       Alte Airpress-Register OPxx herausgenommen.
*     15.07.02 -HA-     APd_Type, APd_Mode, APspSysT und APipSysT eingefuegt.
*                       APitUeb1 bis APitUeb4 eingefuegt.
*                       APstRmp1D1 bis APstRmp5D4 und WKZDues_D1 bis WKZDues_D4 eingefuegt.
*     20.08.02 -HA-     WSikOff2, WOikOff2, WSskOff2 und WOskOff2 eingefuegt.
*     22.08.02 -HA-     Ventil_Mod bis MAs_Vers2 und MAi_Offs1 bis MAi_Vers10 eingefuegt.
*     02.10.02 -HA-     WZA_BA2 bis WZA_BA_FHK eingefuegt.
*     28.10.02 -HA-     AKT3Aval01 bis AKT3Aval08 eingefuegt.
*     29.10.02 -HA-     MSksSnDur1 und MSksSnDur2 aktueller Schneckendurchmesser eingefuegt.
*     05.11.02 -HA-     xtkuhl eingefuegt
*     20.11.02 -HA-     HXinPageAW, GIL_SSON120 bis GIL_SSON181 eingefuegt
*     25.11.02 -HA-     HXsnIF_2, HXsnProto2, HXsnBaud_2, HXsnDatBi2, HXsnStpBi2, HXsnParit2 eingefuegt.
*     10.03.03 -HA-     XSn_Anfa, ssdos1a, spph11a, svph11a, stph11a, ssph11a, spph12a,
*                       svph12a, stph12a, ssph12a, spph13a, svph13a, stph13a, XSn_Anf2a,
*                       spnidra, spnidr2A fuer Produktionsstart S. 40.2 eingefuegt
*     12.03.03 -HA-     DTs_Num und DTi_Num eingefuegt.
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
#define xsweg1       0x040  /* Feld 1: Position Schnecke        Aggregat 1  */
#define xtdos1       0x041  /* Feld 2: Plastifizierzeit S.81.1  Aggregat 1  */
#define xwdre1       0x042  /* Feld 3: Schneckendrehzahl        Aggregat 1  */
#define xsweg2       0x043  /* Feld 7: Position Form-platten                */
#define xtzykl       0x044  /* Zykluszeit     IST-Wert  S.81.2              */
#define xnstep       0x045  /* Feld11: IST-Zyklusstepzaehler    Aggregat 1  */
#define xnpase       0x046  /* Feld11: IST-Zyklusphasenzaehler  Aggregat 1  */
#define xfzuhk       0x047  /* Schliesskraft  IST-Wert  S.50                */
#define xkoel        0x048  /* Feld 5: Oeltemperatur                        */
#define xnmaco       0x049  /* Maschinennummer an IQT                       */
#define xnweco       0x04a  /* Werkzeugnummer IST-Wert  S.21                */
#define xsweg4       0x04b  /* Nullpunktabgleich Auswerfer IST-Wert  S.52   */
#define xnahub       0x04c  /* Anzahl Auswerferhuebe  IST-Wert  S.52        */
#define xtnidr       0x04d  /* Ueberwachungszeit Wkz-Sicherung IST-Wert S.50*/
#define xnfss        0x04e  /* Wiederholung Werkzeugsicherung  IST-Wert S.50*/
#define xkperr       0x04f  /* Kundenpromfehlerregister                     */
#define WZisakt      0x050  /* Werkzeugweg Istposition                      */
#define IqtSPSTxt    0x051  /* SPSText Auswahlregister                      */
#define OPm_SPSTxt   0x052  /* Options SPSTextauswahlregister               */
#define xtkuhl       0x053  /* IST-Wert Kuehlzeit  S.40                     */
#define WDst         0x054  /* Wenden: Wendezeit                            */
#define KbA0Input    0x055  /* Kumulierte SPS-Tasten fuer Crashlogbuch      */
#define KbA1Input    0x056  /* Kumulierte SPS-Tasten fuer Crashlogbuch      */
#define KbA2Input    0x057  /* Kumulierte SPS-Tasten fuer Crashlogbuch      */
#define KbA3Input    0x058  /* Kumulierte SPS-Tasten fuer Crashlogbuch      */
#define OPinKarton   0x059  /* S.71 Anzahl Teile pro Karton                 */
#define IqtSSAct     0x05a  /* Aktuelle Schluesselschalterstellung von der SPS */
#define SEisNlpkt1   0x05b  /* Spritzeinheit 1 Wegpunkt Seite 49.0          */
#define IOinDIist    0x05c  /* Aktwerte  S. 66.0 */
#define IOinDOist    0x05d  /* Aktwerte  S. 66.1 */
#define IOinAOist1   0x05e  /* Aktwerte  S. 66.2 */
#define IOinAOist2   0x05f  /* Aktwerte  S. 66.2 */
#define IOinAOist3   0x060  /* Aktwerte  S. 66.2 */
#define IOinAOist4   0x061  /* Aktwerte  S. 66.2 */
#define APipSysT     0x062  /* Option Airpress Anlagedruck                  */
#define rfast1       0x063  /* Sonderregister fuer schnelle Istwerte        */
#define rfast2       0x064  /* Sonderregister fuer schnelle Istwerte        */
#define rfast3       0x065  /* Sonderregister fuer schnelle Istwerte        */
#define rfast4       0x066  /* Sonderregister fuer schnelle Istwerte        */
#define rfast5       0x067  /* Sonderregister fuer schnelle Istwerte        */
#define rfast6       0x068  /* Sonderregister fuer schnelle Istwerte        */
#define rfast7       0x069  /* Sonderregister fuer schnelle Istwerte        */
#define rfast8       0x06a  /* Sonderregister fuer schnelle Istwerte        */
#define rfast9       0x06b  /* Sonderregister fuer schnelle Istwerte        */
#define rfast10      0x06c  /* Sonderregister fuer schnelle Istwerte        */
#define rfast11      0x06d  /* Sonderregister fuer schnelle Istwerte        */
#define rfast12      0x06e  /* Sonderregister fuer schnelle Istwerte        */
#define rfast13      0x06f  /* Sonderregister fuer schnelle Istwerte        */
/* ---------------- Fast-Register fuer 2/3/4Farben-Maschinen -------------- */
#define xsweg3       0x070  /* Feld 1: Position Schnecke        Aggregat 2  */
#define xtdos2       0x071  /* Feld 2: Plastifizierzeit S.81.1  Aggregat 2  */
#define xwdre2       0x072  /* Feld 3: Schneckendrehzahl        Aggregat 2  */
#define xkoel2       0x073  /* Feld 5: Oeltemperatur            Aggregat 2  */
#define xnstep2      0x074  /* Feld11: IST-Zyklusstepzaehler    Aggregat 2  */
#define xnpas2       0x075  /* Feld11: IST-Zyklusphasenzaehler  Aggregat 2  */
#define SEisNlpkt2   0x076  /* Spritzeinheit 2 Wegpunkt Seite 49.0          */
#define xsweg13      0x077  /* Feld 1: Position Schnecke        Aggregat 3  */
#define xtdos3       0x078  /* Feld 2: Plastifizierzeit S.81.1  Aggregat 3  */
#define xwdre3       0x079  /* Feld 3: Schneckendrehzahl        Aggregat 3  */
#define xnstep3      0x07a  /* Feld11: IST-Zyklusstepzaehler    Aggregat 3  */
#define xnpas3       0x07b  /* Feld11: IST-Zyklusphasenzaehler  Aggregat 3  */
#define xsweg14      0x07c  /* Feld 1: Position Schnecke        Aggregat 4  */
#define xtdos4       0x07d  /* Feld 2: Plastifizierzeit S.81.1  Aggregat 4  */
#define xwdre4       0x07e  /* Feld 3: Schneckendrehzahl        Aggregat 4  */
#define xnstep4      0x07f  /* Feld11: IST-Zyklusstepzaehler    Aggregat 4  */
#define xnpas4       0x080  /* Feld11: IST-Zyklusphasenzaehler  Aggregat 4  */

/* ------------------------------------------------------------------------ */
/* $$$ Istwertregister  (TP_RD_INJ)                                         */          
/* ------------------------------------------------------------------------ */
#define xpfinm       0x090  /* Wkz-Innendruck max. IST-Wert           S.81.2*/
#define xsph10       0x091  /* Plastifizierweg IST-Wert  Aggregat 1   S.81.1*/
#define xsph11       0x092  /* Umschaltpunkt IST-Wert S.41 Agg.1  Stufe 1   */
#define xsph12       0x093  /* Umschaltpunkt IST-Wert S.41 Agg.1  Stufe 2   */
#define xsph13       0x094  /* Umschaltpunkt IST-Wert S.41 Agg.1  Stufe 3   */
#define xsph14       0x095  /* Umschaltpunkt IST-Wert S.41 Agg.1  Stufe 4   */
#define xsph15       0x096  /* Umschaltpunkt IST-Wert S.41 Agg.1  Stufe 5   */
#define xspol1       0x097  /* Umschaltpunkt IST-Wert S.41 Agg.1  Stufe 6   */
#define xtph11       0x098  /* Einspritzzeit IST-Wert S.41 Agg.1  Stufe 1   */
#define xtph12       0x099  /* Einspritzzeit IST-Wert S.41 Agg.1  Stufe 2   */
#define xtph13       0x09a  /* Einspritzzeit IST-Wert S.41 Agg.1  Stufe 3   */
#define xtph14       0x09b  /* Einspritzzeit IST-Wert S.41 Agg.1  Stufe 4   */
#define xtph15       0x09c  /* Einspritzzeit IST-Wert S.41 Agg.1  Stufe 5   */
#define xtph16       0x09d  /* Einspritzzeit IST-Wert S.41 Agg.1  Stufe 6   */
#define xpph11       0x09e  /* Umschaltdruck IST-Wert S.41 Agg.1  Stufe 1   */
#define xpph12       0x09f  /* Umschaltdruck IST-Wert S.41 Agg.1  Stufe 2   */
#define xpph13       0x0a0  /* Umschaltdruck IST-Wert S.41 Agg.1  Stufe 3   */
#define xpph14       0x0a1  /* Umschaltdruck IST-Wert S.41 Agg.1  Stufe 4   */
#define xpph15       0x0a2  /* Umschaltdruck IST-Wert S.41 Agg.1  Stufe 5   */
#define xpph16       0x0a3  /* Umschaltdruck IST-Wert S.41 Agg.1  Stufe 6   */
/* ---------------- 15 Reserve - Register  mit TP_RD_INJ ------------------ */
#define rinj1        0x0a4  /* Reserveregister fuer Spritzistwerte          */
#define rinj2        0x0a5  /* Reserveregister fuer Spritzistwerte          */
#define rinj3        0x0a6  /* Reserveregister fuer Spritzistwerte          */
#define rinj4        0x0a7  /* Reserveregister fuer Spritzistwerte          */
#define rinj5        0x0a8  /* Reserveregister fuer Spritzistwerte          */
#define rinj6        0x0a9  /* Reserveregister fuer Spritzistwerte          */
#define rinj7        0x0aa  /* Reserveregister fuer Spritzistwerte          */
#define rinj8        0x0ab  /* Reserveregister fuer Spritzistwerte          */
#define rinj9        0x0ac  /* Reserveregister fuer Spritzistwerte          */
#define rinj10       0x0ad  /* Reserveregister fuer Spritzistwerte          */
#define rinj11       0x0ae  /* Reserveregister fuer Spritzistwerte          */
#define rinj12       0x0af  /* Reserveregister fuer Spritzistwerte          */
#define rinj13       0x0b0  /* Reserveregister fuer Spritzistwerte          */
#define rinj14       0x0b1  /* Reserveregister fuer Spritzistwerte          */
#define rinj15       0x0b2  /* Reserveregister fuer Spritzistwerte          */
/* ---------------- Qualitaetskontrolle ----------------------------------- */
#define QUinanz1     0x0b3  /* Ausschuss nach Automatikstart                */
#define QUinanz2     0x0b4  /* Ausschuss nach Stoerung                      */
#define QUinanz3     0x0b5  /* Stichprobe                                   */
#define QUinanz4     0x0b6  /* Pruefteil nach Stoerung                      */
/* ---------------- Heizung Kanalbenennung -------------------------------- */
#define HZ_CurReg    0x0b7  /* aktueller Regler auf Seite 39.1              */
#define HZ_TempMod   0x0b8  /* Fuehler Modul                                */
#define HZ_TempKan   0x0b9  /* Fuehler Kanal                                */
#define HZ_HeizMod   0x0ba  /* Heizausgangsmodul                            */
#define HZ_HeizKan   0x0bb  /* Heizausgangskanal                            */
#define HZ_KuelMod   0x0bc  /* Kuehlausgangsmodul                           */
#define HZ_KuelKan   0x0bd  /* Kuehlausgangskanal                           */
/* ------------------------------------------------------------------------ */
#define SPIpHydMax   0x0be  /* Hydraulik Druck max. IST-Wert          S.81.2*/
/* ---------------- Airpress ---------------------------------------------- */
#define APitUeb1     0x0bf  /* Airpress Ueberwachungszeit 1                 */
#define APitUeb2     0x0c0  /* Airpress Ueberwachungszeit 2                 */
#define APitUeb3     0x0c1  /* Airpress Ueberwachungszeit 3                 */
#define APitUeb4     0x0c2  /* Airpress Ueberwachungszeit 4                 */
/* ------------------------------------------------------------------------ */
#define Iwkzschl     0x0c3  /* 17.1 Zeit Werkzeug schliessen IST            */
#define Iwkzsich     0x0c4  /* 17.1 Zeit Werkzeug Sicherung  IST            */
#define Ischldraufb  0x0c5  /* 17.1 Zeit Schliessdruckaufbau IST            */
#define Iaggrvor     0x0c6  /* 17.1 Zeit Aggregat vor        IST            */
#define Ieinspr      0x0c7  /* 17.1 Zeit Einspritzen         IST            */
#define Idos         0x0c8  /* 17.1 Zeit Dosieren            IST            */
#define Ikuehl       0x0c9  /* 17.1 Kuehlzeit                IST            */
#define Iwkzoeffn    0x0ca  /* 17.1 Zeit Werkzeug oeffnen    IST            */
#define Iauswvor     0x0cb  /* 17.1 Zeit Auswerfer vor       IST            */
#define Iauswzur     0x0cc  /* 17.1 Zeit Auswerfer zurueck   IST            */
#define Ipauszeit    0x0cd  /* 17.1 Pausenzeit               IST            */
#define Izykzeit     0x0ce  /* 17.1 Zykluszeit         ULONG  IST            */
#define Izykzeit_HW  0x0cf
#define Iaggrvor2    0x0d0  /* 17.1 Zeit Aggregat vor AGGR_2 IST            */
#define Ieinspr2     0x0d1  /* 17.1 Zeit Einspritzen  AGGR_2 IST            */
#define Idos2        0x0d2  /* 17.1 Zeit Dosieren     AGGR_2 IST            */
#define Iaggrvor3    0x0d3  /* 17.1 Zeit Aggregat vor AGGR_3 IST            */
#define Ieinspr3     0x0d4  /* 17.1 Zeit Einspritzen  AGGR_3 IST            */
#define Idos3        0x0d5  /* 17.1 Zeit Dosieren     AGGR_3 IST            */
#define Iaggrvor4    0x0d6  /* 17.1 Zeit Aggregat vor AGGR_4 IST            */
#define Ieinspr4     0x0d7  /* 17.1 Zeit Einspritzen  AGGR_4 IST            */
#define Idos4        0x0d8  /* 17.1 Zeit Dosieren     AGGR_4 IST            */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* $$$ Istwertregister  (TP_RD_SLOW) Beginn ab 0x0e0                        */
/* ------------------------------------------------------------------------ */
/* Register fuer Heizungs-Istwerte                                          */
/* ------------------------------------------------------------------------ */
#define xksr01       0x0e0  /* Stromistwert eines Temperaturreglers         */
#define xksr02       0x0e1  /* Stromistwert eines Temperaturreglers         */
#define xksr03       0x0e2  /* Stromistwert eines Temperaturreglers         */
#define xksr04       0x0e3  /* Stromistwert eines Temperaturreglers         */
#define xksr05       0x0e4  /* Stromistwert eines Temperaturreglers         */
#define xksr06       0x0e5  /* Stromistwert eines Temperaturreglers         */
#define xksr07       0x0e6  /* Stromistwert eines Temperaturreglers         */
#define xksr08       0x0e7  /* Stromistwert eines Temperaturreglers         */
#define xksr09       0x0e8  /* Stromistwert eines Temperaturreglers         */
#define xksr10       0x0e9  /* Stromistwert eines Temperaturreglers         */
#define xksr11       0x0ea  /* Stromistwert eines Temperaturreglers         */
#define xksr12       0x0eb  /* Stromistwert eines Temperaturreglers         */
#define xksr13       0x0ec  /* Stromistwert eines Temperaturreglers         */
#define xksr14       0x0ed  /* Stromistwert eines Temperaturreglers         */
#define xksr15       0x0ee  /* Stromistwert eines Temperaturreglers         */
#define xksr16       0x0ef  /* Stromistwert eines Temperaturreglers         */
#define xker01       0x0f0  /* ED-Wert eines Temperaturreglers              */
#define xker02       0x0f1  /* ED-Wert eines Temperaturreglers              */
#define xker03       0x0f2  /* ED-Wert eines Temperaturreglers              */
#define xker04       0x0f3  /* ED-Wert eines Temperaturreglers              */
#define xker05       0x0f4  /* ED-Wert eines Temperaturreglers              */
#define xker06       0x0f5  /* ED-Wert eines Temperaturreglers              */
#define xker07       0x0f6  /* ED-Wert eines Temperaturreglers              */
#define xker08       0x0f7  /* ED-Wert eines Temperaturreglers              */
#define xker09       0x0f8  /* ED-Wert eines Temperaturreglers              */
#define xker10       0x0f9  /* ED-Wert eines Temperaturreglers              */
#define xker11       0x0fa  /* ED-Wert eines Temperaturreglers              */
#define xker12       0x0fb  /* ED-Wert eines Temperaturreglers              */
#define xker13       0x0fc  /* ED-Wert eines Temperaturreglers              */
#define xker14       0x0fd  /* ED-Wert eines Temperaturreglers              */
#define xker15       0x0fe  /* ED-Wert eines Temperaturreglers              */
#define xker16       0x0ff  /* ED-Wert eines Temperaturreglers              */
#define xkir01       0x100  /* IST-Werte eines Temperaturreglers            */
#define xkir02       0x101  /* IST-Werte eines Temperaturreglers            */
#define xkir03       0x102  /* IST-Werte eines Temperaturreglers            */
#define xkir04       0x103  /* IST-Werte eines Temperaturreglers            */
#define xkir05       0x104  /* IST-Werte eines Temperaturreglers            */
#define xkir06       0x105  /* IST-Werte eines Temperaturreglers            */
#define xkir07       0x106  /* IST-Werte eines Temperaturreglers            */
#define xkir08       0x107  /* IST-Werte eines Temperaturreglers            */
#define xkir09       0x108  /* IST-Werte eines Temperaturreglers            */
#define xkir10       0x109  /* IST-Werte eines Temperaturreglers            */
#define xkir11       0x10a  /* IST-Werte eines Temperaturreglers            */
#define xkir12       0x10b  /* IST-Werte eines Temperaturreglers            */
#define xkir13       0x10c  /* IST-Werte eines Temperaturreglers            */
#define xkir14       0x10d  /* IST-Werte eines Temperaturreglers            */
#define xkir15       0x10e  /* IST-Werte eines Temperaturreglers            */
#define xkir16       0x10f  /* IST-Werte eines Temperaturreglers            */
#define xkgwpw       0x110  /* Toleranzfehler positiv weit, alle 16 Regler  */
#define xkgwpe       0x111  /* Toleranzfehler positiv eng,  alle 16 Regler  */
#define xkgwne       0x112  /* Toleranzfehler negativ eng,  alle 16 Regler  */
#define xkgwnw       0x113  /* Toleranzfehler negativ weit, alle 16 Regler  */
#define tkxthb       0x114  /* Fuehlerbruch, alle 16 Regler                 */
#define xkblnr       0x115  /* Istwertblock-Nummer                          */

/* ------------------------------------------------------------------------ */
/* $$$ Sollwert-Download Register                                           */
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
#define Ax0ec        0x120  /* Anfahrdauer         S.32 Zeile 7             */
#define Ax0ed        0x121  /* Anfahrtemperatur    S.32 Zeile 8             */
#define Ax0ee        0x122  /* Leistungsbegrenzung S.32 Zeile 9             */
#define ssfzu1       0x123  /* Wegpunkt fuer Stufe 1      S.50              */
#define ssfzu2       0x124  /* Start Werkzeugsicherung 1  S.50              */
#define ssfzu3       0x125  /* Wegpunkt Start Kern 1 ein  S.61              */
#define sfzkpt       0x126  /* Kontrollpunkt Maschine     S.61              */
#define sfzstp       0x127  /* Wegpunkt Start Kern ein  S.62                */
#define sfzkp2       0x128  /* Kontrollpunkt Maschine   S.62                */
#define ssfzu        0x129  /* Werkzeugeinbauhoehe      S.50                */
#define ssfau1       0x12a  /* Wegpunkt Stufe 1         S.51                */
#define ssfau2       0x12b  /* Wegpunkt Stufe 2         S.51                */
#define ssfau3       0x12c  /* erhoehte Oeffnungskraft bei Wegpunkt  S.51   */
#define ssfau4       0x12d  /* Start Auswerfer vor                   S.52   */
#define ssfau5       0x12e  /* Wegpunkt Ventil Y9027     S.69               */
#define ssfau6       0x12f  /* Wegpunkt Ventil Y9028     S.69               */
#define ssfau7       0x130  /* Wegpunkt Ventil Y9029     S.69               */
#define ssfau8       0x131  /* Wegpunkt Ventil Y9030     S.69               */
#define ssfau9       0x132  /* Wegpunkt Start Kern aus   S.61.1             */
#define sfakpt       0x133  /* Kontrollpunkt Maschine    S.61.1             */
#define sfastp       0x134  /* Wegpunkt Start Kern aus   S.62               */
#define sfakp2       0x135  /* Kontrollpunkt Maschine    S.62               */
#define ssfauf       0x136  /* Werkzeugoeffnungsweg      S.51               */
#define ssaus1       0x137  /* Umschaltpunkt Stufe 1     S.52               */
#define ssaus2       0x138  /* Auswerferweg              S.52               */
#define ssaus3       0x139  /* Auswerferrueckweg bei Mehrfachhub  S.52      */
#define ssausr       0x13a  /* Nullpunktabgleich Auswerfer        S.52      */
#define svzu1        0x13b  /* Geschwindigkeit fuer Stufe 1  S.50           */
#define svzu2        0x13c  /* Geschwindigkeit fuer Stufe 2  S.50           */
#define svauf1       0x13d  /* Geschwindigkeit fuer Stufe 1  S.51           */
#define svauf2       0x13e  /* Geschwindigkeit fuer Stufe 2  S.51           */
#define svauf3       0x13f  /* Geschwindigkeit fuer Stufe 3  S.51           */
#define svaus1       0x140  /* Geschwindigkeit Stufe 1 vor      S.52        */
#define svaus2       0x141  /* Geschwindigkeit Stufe 1 zurueck  S.52        */
#define svazur       0x142  /* Geschwindigkeit Stufe 2 zurueck  S.52        */
#define spnidr       0x143  /* Druck Werkzeugsicherung 1  S.50              */
#define sfzuhk       0x144  /* Schliesskraft  S.50  u. S.54.1               */
#define speinr       0x145  /* Einrichtdruck  S.50                          */
#define spspr        0x146  /* Start Einspritzen bei Schliesskraft  S.50    */
#define sfssed       0x147  /* Start Schliesskraftaufbau            S.50    */
#define stph11       0x148  /* Einspritzzeit  S.41  Aggregat 1  Stufe 1     */
#define stph12       0x149  /* Einspritzzeit  S.41  Aggregat 1  Stufe 2     */
#define stph13       0x14a  /* Einspritzzeit  S.41  Aggregat 1  Stufe 3     */
#define stph14       0x14b  /* Einspritzzeit  S.41  Aggregat 1  Stufe 4     */
#define stph15       0x14c  /* Einspritzzeit  S.41  Aggregat 1  Stufe 5     */
#define stph16       0x14d  /* Einspritzzeit  S.41  Aggregat 1  Stufe 6     */
#define ssph11       0x14e  /* Umschaltpunkt  S.41  Aggregat 1  Stufe 1     */
#define ssph12       0x14f  /* Umschaltpunkt  S.41  Aggregat 1  Stufe 2     */
#define ssph13       0x150  /* Umschaltpunkt  S.41  Aggregat 1  Stufe 3     */
#define ssph14       0x151  /* Umschaltpunkt  S.41  Aggregat 1  Stufe 4     */
#define ssph15       0x152  /* Umschaltpunkt  S.41  Aggregat 1  Stufe 5     */
#define ssum11       0x153  /* Wegpunkt  S.40  Aggreagt 1                   */
#define ssdos1       0x154  /* Plastifizierweg IST-Wert  S.40 Aggregat 1    */
#define swpl11       0x156  /* Drehzahl  S.40  Aggregat 1 Stufe 1           */
#define swpl12       0x157  /* Drehzahl  S.40  Aggregat 1 Stufe 2           */
#define spst11       0x158  /* Staudruck  S.40  Aggregat 1  Stufe 1         */
#define spst12       0x159  /* Staudruck  S.40  Aggregat 1  Stufe 2         */
#define ss1dos       0x15a  /* Kopie von ssdos1 Plastifizierweg S.40        */
#define kxempf       0x15b  /* Fuehlerempfundlichkeit    S.43   Aggregat 1  */
#define svph11       0x15d  /* Einspritzgeschwindigkeit S.41 Agg.1  Stufe 1 */
#define svph12       0x15e  /* Einspritzgeschwindigkeit S.41 Agg.1  Stufe 2 */
#define svph13       0x15f  /* Einspritzgeschwindigkeit S.41 Agg.1  Stufe 3 */
#define svph14       0x160  /* Einspritzgeschwindigkeit S.41 Agg.1  Stufe 4 */
#define svph15       0x161  /* Einspritzgeschwindigkeit S.41 Agg.1  Stufe 5 */
#define svph16       0x162  /* Einspritzgeschwindigkeit S.41 Agg.1  Stufe 6 */
#define spum11       0x163  /* Umschaltdruck  S.41  Aggregat 1  Stufe 1     */
#define spum12       0x164  /* Umschaltdruck  S.41  Aggregat 1  Stufe 2     */
#define spum13       0x165  /* Umschaltdruck  S.41  Aggregat 1  Stufe 3     */
#define spum14       0x166  /* Umschaltdruck  S.41  Aggregat 1  Stufe 4     */
#define spum15       0x167  /* Umschaltdruck  S.41  Aggregat 1  Stufe 5     */
#define spph11       0x168  /* Einspritzdruck S.41 Aggregat 1 Stufe 1       */
#define spph12       0x169  /* Einspritzdruck S.41 Aggregat 1 Stufe 2       */
#define spph13       0x16a  /* Einspritzdruck S.41 Aggregat 1 Stufe 3       */
#define spph14       0x16b  /* Einspritzdruck S.41 Aggregat 1 Stufe 4       */
#define spph15       0x16c  /* Einspritzdruck S.41 Aggregat 1 Stufe 5       */
#define spph16       0x16e  /* Einspritzdruck S.41 Aggregat 1 Stufe 6       */
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define WAs_fkt      0x16f  /* Wahl Auswerfer vor,nach,parallel Masch.Ausw. */
#define WAs_Wpvor    0x170  /* Aktionsbeginn Wkz-Auswerfer                  */
#define WAs_Hubz     0x171  /* Sollwert Hubzahl                             */
#define WAstVorne    0x172  /* Wartezeit vorne                              */
#define WAstVor      0x173  /* Aktionszeit Wkz-Auswerfer vor                */
#define WAstZur      0x174  /* Aktionszeit Wkz-Auswerfer zurueck            */
#define KE_pAusfa    0x175  /* Druck Kern 1 aus                             */
#define KE_pEinfa0   0x176  /* Druck Kern 1 ein                             */
#define KE_vAusfa0   0x177  /* Geschw. 1 Kern aus                           */
#define KE_vAusfa1   0x178  /* Geschw. 2 Kern aus                           */
#define KE_vEinfa0   0x179  /* Geschw. 1 Kern ein                           */
#define LVsnEin0     0x17a  /* Luftventil 1 Y9027 Programmwahl              */
#define LVsnEin1     0x17b  /* Luftventil 2 Y9028 Programmwahl              */
#define LVsnEin2     0x17c  /* Luftventil 3 Y9029 Programmwahl              */
#define LVsnEin3     0x17d  /* Luftventil 4 Y9030 Programmwahl              */
#define rsonf        0x17e  /* Sonderregister f                             */
#define tabswkz      0x17f  /* Temperaturabsenkung Werkzeugheizung          */
#define tabszyl1     0x180  /* Temperaturabsenkung Zylinderheizung Agg. 1   */
#define sk1ein       0x181  /* Start Kern 1 einfahren  S.61                 */
#define sk1aus       0x182  /* Start Kern 1 ausfahren  S.61.1               */
#define sk2ein       0x183  /* Start Kern 2 einfahren  S.62                 */
#define sk2aus       0x184  /* Start Kern 2 ausfahren  S.62.1               */
#define sk1eiv       0x185  /* Kernbewegung verzoegert   S.61               */
#define sk1auv       0x186  /* Kernbewegung verzoegert   S.61.1             */
#define sk2eiv       0x187  /* Kernbewegung verzoegert   S.62               */
#define sk2auv       0x188  /* Kernbewegung verzoegert   S.62.1             */
#define snk1ei       0x189  /* Kern 1 ein nach Kern ?  S.61                 */
#define snk1au       0x18a  /* Kern 1 ausfahren nach ? S.61.1               */
#define snk2ei       0x18b  /* Kern 2 ein nach Kern ?  S.62                 */
#define snk2au       0x18c  /* Kern 2 ausfahren nach ? S.62.1               */
#define stzykl       0x18d  /* Zyklusueberwachungszeit S.80                 */
#define stdos1       0x18e  /* Plastifizierzeitueberwachung Aggregat 1 S.80 */
#define stmota       0x18f  /* Motor-/Heizung Abschaltverzoegerung     S.80 */
#define stwasa       0x190  /* Kuehlwasser-Abschaltverzoegerung        S.80 */
#define stvdos       0x191  /* Plastifizierverzoegerung S.40 Aggregat 1     */
#define stintr       0x192  /* Intrusion  S.40  Aggregat 1                  */
#define stkuhl       0x193  /* Kuehlzeit  S.40                              */
#define staggr       0x194  /* Duesensbhebung verzoegert um  S.49  Agg.1    */
#define stnidr       0x195  /* Ueberwachungszeit Wkz-Sicherung  S.50        */
#define stpaus       0x196  /* Pausenzeit  S.51                             */
#define staus1       0x197  /* Wartezeit am Umschaltpunkt vor  S.52         */
#define staus2       0x198  /* Wartezeit vorne  S.52                        */
#define stk1ei       0x199  /* Kern 1 Einfahr-/Ueberwachungszeit  S.61      */
#define stk1au       0x19a  /* Kern 1 Ausfahr-/Ueberwachungszeit  S.61.1    */
#define stk2ei       0x19b  /* Kern 2 Einfahr-/Ueberwachungszeit  S.62      */
#define stk2au       0x19c  /* Kern 2 Ausfahr-/Ueberwachungszeit  S.62.1    */
#define soelvw       0x19d  /* Sollwert Oelvorwaermung (zusaetzliches Reg.) */
#define snfin        0x19e  /* Umschaltung mit Wkz-Innendruck S.43  Agg.1   */
#define snfetz       0x19f  /* Zentralschmierungsperiode  S.15              */
#define snkern       0x1a0  /* Sonderprogrammnummer       S.21 und S.67     */
#define snphmx       0x1a1  /* Anzahl Spritzstufen  S.40  Aggregat 1        */
#define sfaggr       0x1a2  /* Duesenanpressdruck   S.49  Aggregat 1        */
#define snaggr       0x1a3  /* Duesenabhebung nach Einspritzen  S.49  Agg.1 */
#define snnidr       0x1a4  /* Wiederholung Werkzeugsicherung   S.50        */
#define sfausf       0x1a5  /* Auswerferdruck  S.52                         */
#define snausw       0x1a6  /* Anzahl Auswerferhuebe  S.52                  */
#define snvws1       0x1a7  /* Programmschalter 1   S.67                    */
#define snvws2       0x1a8  /* Programmschalter 2   S.67                    */
#define snvws3       0x1a9  /* Programmschalter 3   S.67                    */
#define snvws4       0x1aa  /* Programmschalter 4   S.67                    */
#define snvws5       0x1ab  /* Programmschalter 5   S.67                    */
#define sswp1        0x1ac  /* Wegpunkt 1           S.67                    */
#define sswp2        0x1ad  /* Wegpunkt 2           S.67                    */
#define sswp3        0x1ae  /* Wegpunkt 3           S.67                    */
#define sswp4        0x1af  /* Wegpunkt 4           S.67                    */
#define sswp5        0x1b0  /* Wegpunkt 5           S.67                    */
#define stz1         0x1b1  /* Zeit 1               S.67                    */
#define stz2         0x1b2  /* Zeit 2               S.67                    */
#define stz3         0x1b3  /* Zeit 3               S.67                    */
#define stz4         0x1b4  /* Zeit 4               S.67                    */
#define stz5         0x1b5  /* Zeit 5               S.67                    */
#define stdues1      0x1b6  /* Duesenabhebezeit  S.49  Aggregat 1           */
#define svag1v       0x1b7  /* Duesengeschwindigkeit vor  S.49  Aggregat 1  */
#define svag1z       0x1b8  /* Duesengeschwindigkeit zurueck  S.49  Agg.1   */
#define sagpfo       0x1b9  /* Duesenanpressdruck bei offener Form  S.49    */
#define svk1ei       0x1ba  /* Einfahrgeschwindigkeit   S.61                */
#define spk1ei       0x1bb  /* Einfahrdruck             S.61                */
#define svk1au       0x1bc  /* Ausfahrgeschwindigkeit   S.61.1              */
#define spk1au       0x1bd  /* Ausfahrdruck             S.61.1              */
#define svk2ei       0x1be  /* Einfahrgeschwindigkeit   S.62                */
#define spk2ei       0x1bf  /* Einfahrdruck             S.62                */
#define svk2au       0x1c0  /* Ausfahrgeschwindigkeit   S.62.1              */
#define spk2au       0x1c1  /* Ausfahrdruck             S.62.1              */
#define knuver       0x1c2  /* Test beim Aufstarten: Programmversion        */
#define knutyp       0x1c3  /* Test beim Aufstarten: Maschinengroesse/typ   */
#define ssentn       0x1c4  /* Wegpunkt Start Entnahme ein   S.70           */
#define keinsi       0x1c5  /* Absicherung im Einrichten  S.61              */
#define zissst       0x1c6  /* aktuelle Schluesselschalterposition          */
#define spsth1       0x1c7  /* Staudruck im Handbetrieb Spritzeinheit 1     */
#define spsth2       0x1c8  /* Staudruck im Handbetrieb Spritzeinheit 2     */
#define SSCmd        0x1c9  /* Parameter des SS-Kommandos im Diagnosemode   */
#define formmin      0x1ca  /* minimale Formeinbauhoehe          */  
/* ---------------- Robot-Handlinggeraet ---------------------------------- */
#define ROsnProgr    0x1cb  /* Programmnummer fuer Robot                    */
#define ROs_Ablag    0x1cc  /* Ablage auf/ueber Ablage;in SGM               */
#define ROstYSgm     0x1cd  /* Zeit bis Y-Achse in SGM eingefahren          */
#define ROstXvor     0x1ce  /* Zeit bis X-Achse vorgefahren                 */
#define ROstAwVor    0x1cf  /* Zeit bis Auswerfer vorne                     */
#define ROstGrEin    0x1d0  /* Zeit bis Greifer ein                         */
#define ROstGrAus    0x1d1  /* Zeit bis Greifer aus                         */
#define ROstAwZur    0x1d2  /* Zeit bis Auswerer zurueck                    */
#define ROstXzur     0x1d3  /* Zeit bis X-Achse zurueck                     */
#define ROstB_C      0x1d4  /* Zeit fuer B_C Achse                          */
#define ROstYAbl     0x1d5  /* Zeit fuer Y-Achse zur Ablage                 */
#define ROstFormZu   0x1d6  /* Zeit fuer Form zu                            */
#define ROstBTakt    0x1d7  /* Zeit des Band Takt                           */
#define ROstABlas    0x1d8  /* Abblaszeit                                   */
#define ROstAusbis   0x1d9  /* Totzeit fuer Auswerfer                       */
#define ROstZuebw    0x1da  /* ?? Zeit                                      */
#define ROsnSoAbl    0x1db  /* Sonderfunktion Ablage                        */
#define SEgpUSt 	   0x1dc  /* Max. Umschaltdruck 1.Agg                     */
#define SEgpUSt2 	   0x1dd  /* Max. Umschaltdruck 2.Agg                     */
#define SEgpUSt3 	   0x1de  /* Max. Umschaltdruck 3.Agg                     */
#define SEgpUSt4 	   0x1df  /* Max. Umschaltdruck 4.Agg                     */
#define AWgweg       0x1e0  /* Max. Auswerferweg                            */
#define SNgdrehm1    0x1e1  /* Max. Schneckendrehmoment 1.Agg               */
#define SNgdrehm2    0x1e2  /* Max. Schneckendrehmoment 2.Agg               */
#define SNgdrehm3    0x1e3  /* Max. Schneckendrehmoment 3.Agg               */
#define SNgdrehm4    0x1e4  /* Max. Schneckendrehmoment 4.Agg               */
/* ---------------- Luftventilseite 69.0 ---------------------------------- */
#define LVstVerz10   0x1e5  /* Verzoegerungszeit in 1/100  Ventil Y9027 S.69*/
#define LVstVerz20   0x1e6  /* Verzoegerungszeit in 1/100  Ventil Y9028 S.69*/
#define LVstVerz30   0x1e7  /* Verzoegerungszeit in 1/100  Ventil Y9029 S.69*/
#define LVstVerz40   0x1e8  /* Verzoegerungszeit in 1/100  Ventil Y9030 S.69*/
#define LVstBlas10   0x1e9  /* Blaszeit          in 1/100  Ventil Y9027 S.69*/
#define LVstBlas20   0x1ea  /* Blaszeit          in 1/100  Ventil Y9028 S.69*/
#define LVstBlas30   0x1eb  /* Blaszeit          in 1/100  Ventil Y9029 S.69*/
#define LVstBlas40   0x1ec  /* Blaszeit          in 1/100  Ventil Y9030 S.69*/
/* ------------------------------------------------------------------------ */
#define SEssFzu2     0x1ed  /* 3. Wegpunkt Wkz schliessen                   */
#define SEsvFzu3     0x1ee  /* 3. Geschwindigkeit Wkz schliessen            */
/* ---------------- SPS-Datum und Uhrzeit --------------------------------- */
#define ClYear       0x1ef  /*  Jahr                                        */
#define ClMonth      0x1f0  /*  Monat                                       */
#define ClMDay       0x1f1  /*  Tag                                         */
#define ClHour       0x1f2  /*  Stunde                                      */
#define ClMin        0x1f3  /*  Minute                                      */
/* ---------------- Diagnose - Register ----------------------------------- */
#define IMSssK11     0x1f4  /* 89.0 Weg1 K1 Konstante ULONG  SOLL            */
#define IMSssK11_HW  0x1f5
#define IMSssOff1    0x1f6  /* 89.0 Weg1 Offset             SOLL            */
#define IMSssK12     0x1f7  /* 89.0 Weg2 K1 Konstante ULONG  SOLL            */
#define IMSssK12_HW  0x1f8
#define IMSssOff2    0x1f9  /* 89.0 Weg2 Offset             SOLL            */
#define IMSssK13     0x1fa  /* 89.0 Weg3 K1 Konstante ULONG  SOLL            */
#define IMSssK13_HW  0x1fb
#define IMSssOff3    0x1fc  /* 89.0 Weg3 Offset             SOLL            */
#define IMSssK14     0x1fd  /* 89.0 Weg4 K1 Konstante ULONG  SOLL            */
#define IMSssK14_HW  0x1fe
#define IMSssOff4    0x1ff  /* 89.0 Weg4 Offset             SOLL            */
#define IDiagOut     0x200  
#define IGenMod      0x201  /* 89.0 default/RAM/PROM        SOLL            */
/* ---------------- Reserveregister fuer Sonderprogramme ------------------ */
#define iqson0       0x202  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1       0x203  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2       0x204  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3       0x205  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4       0x206  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5       0x207  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson6       0x208  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson7       0x209  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson8       0x20a  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson9       0x20b  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqsona       0x20c  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqsonb       0x20d  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqsonc       0x20e  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqsond       0x20f  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqsone       0x210  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqsonf       0x211  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson10      0x212  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson11      0x213  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson12      0x214  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson13      0x215  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson14      0x216  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson15      0x217  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson16      0x218  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson17      0x219  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson18      0x21a  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson19      0x21b  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1a      0x21c  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1b      0x21d  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1c      0x21e  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1d      0x21f  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1e      0x220  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson1f      0x221  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson20      0x222  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson21      0x223  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson22      0x224  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson23      0x225  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson24      0x226  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson25      0x227  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson26      0x228  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson27      0x229  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson28      0x22a  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson29      0x22b  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2a      0x22c  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2b      0x22d  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2c      0x22e  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2d      0x22f  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2e      0x230  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson2f      0x231  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson30      0x232  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson31      0x233  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson32      0x234  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson33      0x235  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson34      0x236  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson35      0x237  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson36      0x238  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson37      0x239  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson38      0x23a  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson39      0x23b  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3a      0x23c  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3b      0x23d  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3c      0x23e  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3d      0x23f  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3e      0x240  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson3f      0x241  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson40      0x242  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson41      0x243  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson42      0x244  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson43      0x245  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson44      0x246  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson45      0x247  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson46      0x248  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson47      0x249  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson48      0x24a  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson49      0x24b  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4a      0x24c  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4b      0x24d  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4c      0x24e  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4d      0x24f  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4e      0x250  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson4f      0x251  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson50      0x252  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson51      0x253  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson52      0x254  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson53      0x255  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson54      0x256  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson55      0x257  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson56      0x258  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson57      0x259  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson58      0x25a  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson59      0x25b  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5a      0x25c  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5b      0x25d  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5c      0x25e  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5d      0x25f  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5e      0x260  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson5f      0x261  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson60      0x262  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson61      0x263  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson62      0x264  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson63      0x265  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson64      0x266  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson65      0x267  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson66      0x268  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson67      0x269  /*     reserviert fuer IQT-Sonderprogramme      */
#define iqson68      0x26a  /*     reserviert fuer IQT-Sonderprogramme      */
/* ---------------- Atmen Praegen ----------------------------------------- */
#define APs_Wahl     0x26b  /*     Atmen/Praegen Programmwahl               */
#define APs_Stufen   0x26c  /*     Startpunkt nach Spritzstufe ?            */
#define APstVerz     0x26d  /*     Verzoegerungszeit                        */
#define APspLock1    0x26e  /*     Schliesskraft F1                         */
#define APstAktio1   0x26f  /*     Aktionszeit t1                           */
#define APspLock2    0x270  /*     Schliesskraft F2                         */
#define APstAktio2   0x271  /*     Aktionszeit t2                           */
#define APspLock3    0x272  /*     Schliesskraft F3                         */
#define APstAktio3   0x273  /*     Aktionszeit t3                           */
#define APspLock4    0x274  /*     Schliesskraft F4                         */
#define APssStart    0x275  /*     Startpunkt nach Schneckenposition        */
#define APs_NrStuf   0x276  /*     Anzahl Atmungs- bzw. Praegestufen        */
#define APssPWeg     0x277  /*     Atmungs- bzw. Praegeweg                  */
/* -------- Register fuer  S. 66.0 ff --------------- */
#define IOs_DIfkt1   0x278  /* Sollwerte Funktion S. 66.0 */    
#define IOs_DIfkt2   0x279  /* Sollwerte Funktion S. 66.0 */                 
#define IOs_DIfkt3   0x27a  /* Sollwerte Funktion S. 66.0 */    
#define IOs_DIfkt4   0x27b  /* Sollwerte Funktion S. 66.0 */    
#define IOsnDIpar1   0x27c  /* Sollwerte Parameter S. 66.0 */   
#define IOsnDIpar2   0x27d  /* Sollwerte Parameter S. 66.0 */   
#define IOsnDIpar3   0x27e  /* Sollwerte Parameter S. 66.0 */   
#define IOsnDIpar4   0x27f  /* Sollwerte Parameter S. 66.0 */   
#define IOs_DOfkt1   0x280  /* Sollwerte Funktion S. 66.1 */    
#define IOs_DOfkt2   0x281  /* Sollwerte Funktion S. 66.1 */    
#define IOs_DOfkt3   0x282  /* Sollwerte Funktion S. 66.1 */    
#define IOs_DOfkt4   0x283  /* Sollwerte Funktion S. 66.1 */    
#define IOstDOakt1   0x284  /* Sollwerte Aktionszeit S. 66.1 */ 
#define IOstDOakt2   0x285  /* Sollwerte Aktionszeit S. 66.1 */ 
#define IOstDOakt3   0x286  /* Sollwerte Aktionszeit S. 66.1 */ 
#define IOstDOakt4   0x287  /* Sollwerte Aktionszeit S. 66.1 */ 
#define IOsnDOpar1   0x288  /* Sollwerte Parameter S. 66.1 */   
#define IOsnDOpar2   0x289  /* Sollwerte Parameter S. 66.1 */   
#define IOsnDOpar3   0x28a  /* Sollwerte Parameter S. 66.1 */   
#define IOsnDOpar4   0x28b  /* Sollwerte Parameter S. 66.1 */   
#define IOsnDOpa21   0x28c  /* Sollwerte Parameter 2 S. 66.1 */   
#define IOsnDOpa22   0x28d  /* Sollwerte Parameter 2 S. 66.1 */   
#define IOsnDOpa23   0x28e  /* Sollwerte Parameter 2 S. 66.1 */   
#define IOsnDOpa24   0x28f  /* Sollwerte Parameter 2 S. 66.1 */   
#define IOs_AOfkt1   0x290  /* Sollwerte Funktion S. 66.2 */    
#define IOs_AOfkt2   0x291  /* Sollwerte Funktion S. 66.2 */    
#define IOs_AOfkt3   0x292  /* Sollwerte Funktion S. 66.2 */    
#define IOs_AOfkt4   0x293  /* Sollwerte Funktion S. 66.2 */
#define IOsnAOpar1   0x294  /* Sollwerte Parameter S. 66.1 */   
#define IOsnAOpar2   0x295  /* Sollwerte Parameter S. 66.1 */   
#define IOsnAOpar3   0x296  /* Sollwerte Parameter S. 66.1 */   
#define IOsnAOpar4   0x297  /* Sollwerte Parameter S. 66.1 */   
/* ---------------- Kernzug Sonderprogramme-------------------------------- */
#define KEsv3In1     0x298  /*     Kernzug 3 Einfahrgeschwindigkeit 1       */
#define KEsv4In1     0x299  /*     Kernzug 4 Einfahrgeschwindigkeit 1       */
#define KEsv1In2     0x29a  /*     Kernzug 1 Einfahrgeschwindigkeit 2       */
#define KEsv2In2     0x29b  /*     Kernzug 2 Einfahrgeschwindigkeit 2       */
#define KEsv3In2     0x29c  /*     Kernzug 3 Einfahrgeschwindigkeit 2       */
#define KEsv4In2     0x29d  /*     Kernzug 4 Einfahrgeschwindigkeit 2       */
#define KEsv3Ou1     0x29e  /*     Kernzug 3 Ausfahrgeschwindigkeit 1       */
#define KEsv4Ou1     0x29f  /*     Kernzug 4 Ausfahrgeschwindigkeit 1       */
#define KEsv1Ou2     0x2a0  /*     Kernzug 1 Ausfahrgeschwindigkeit 2       */
#define KEsv2Ou2     0x2a1  /*     Kernzug 2 Ausfahrgeschwindigkeit 2       */
#define KEsv3Ou2     0x2a2  /*     Kernzug 3 Ausfahrgeschwindigkeit 2       */
#define KEsv4Ou2     0x2a3  /*     Kernzug 4 Ausfahrgeschwindigkeit 2       */
#define KEsp3In1     0x2a4  /*     Kernzug 3 Einfahrdruck 1                 */
#define KEsp4In1     0x2a5  /*     Kernzug 4 Einfahrdruck 1                 */
#define KEsp1In2     0x2a6  /*     Kernzug 1 Einfahrdruck 2                 */
#define KEsp2In2     0x2a7  /*     Kernzug 2 Einfahrdruck 2                 */
#define KEsp3In2     0x2a8  /*     Kernzug 3 Einfahrdruck 2                 */
#define KEsp4In2     0x2a9  /*     Kernzug 4 Einfahrdruck 2                 */
#define KEsp3Ou1     0x2aa  /*     Kernzug 3 Ausfahrdruck 1                 */
#define KEsp4Ou1     0x2ab  /*     Kernzug 4 Ausfahrdruck 1                 */
#define KEsp1Ou2     0x2ac  /*     Kernzug 1 Ausfahrdruck 2                 */
#define KEsp2Ou2     0x2ad  /*     Kernzug 2 Ausfahrdruck 2                 */
#define KEsp3Ou2     0x2ae  /*     Kernzug 3 Ausfahrdruck 2                 */
#define KEsp4Ou2     0x2af  /*     Kernzug 4 Ausfahrdruck 2                 */
/*------------------------- Kernzueg Ausschrauben ------------------------- */
#define KEs_Arl      0x2b0  /*     Drehrichtung rechts=0 links=1            */
#define KEstAVWo     0x2b1  /*     Verzoegerungszeit bis Werkzeug oeffnen   */
#define KEstAVSa     0x2b2  /*     Verzoegerungszeit bis Start Ausschrauben */
#define KEstAAAu     0x2b3  /*     Aktionszeit Ausschrauben                 */
#define KEstAVSAu    0x2b4  /*     Verzoegerungszeit bis Start Auswerfer    */
#define KEssAWSa     0x2b5  /*     Wegpunkt Start Ausschrauben              */
#define KEs_AZnS     0x2b6  /*     Zustand nach Schrauben drucklos=0 Druck=1*/
#define KEs_AUeSb    0x2b7  /*     Ueberw. Schraubbewegung  Endsch.=1 Zeit=2*/
#define KEsvAusG     0x2b8  /*     Ausschraubgeschwindigkeit                */
#define KEspAusD     0x2b9  /*     Ausschraubdruck                          */
#define KEspAusNd    0x2ba  /*     Ausschraubniederdruck                    */
#define KEsvAEinG    0x2bb  /*     Einschraubgeschwindigkeit                */
#define KEspAEinD    0x2bc  /*     Einschraubdruck                          */
#define KEspAEinNd   0x2bd  /*     Einschraubniederdruck                    */
/*------------------------- Sonderprogramm Werkzeugschnellspannen --------- */
#define WZs_SnSp     0x2be  /*     Wkz-Schnellspanneinrichtung  aus=0 ein=1 */
/*------------------------- Qualitaetskontrolle --------------------------- */
#define QUsnasz      0x2bf  /*     Ausschuss nach Automatikstart            */
#define QUsnasst     0x2c0  /*     Ausschuss nach Stoerung                  */
#define QUsnptzy     0x2c1  /*     Stichprobe                               */ 
#define QUsnptst     0x2c2  /*     Pruefteil nach Stoerung                  */
#define QUstvwo      0x2c3  /*     Verz.zeit Werkz. oeffnen                 */
/*------------------------- Selektierweiche ------------------------------- */
#define QUs_Selek    0x2c4  /*     Betriebsart Selektierweiche              */
#define QUs_Angus    0x2c5  /*     Umschaltkrit. Angusstrennung             */
#define QUstVerz     0x2c6  /*     Verzoegerungszeit                        */
#define tabszyl2     0x2c7  /*     Temperaturabsenkung 2. Aggregat          */
/*------------------------- Heizungsoptimierung --------------------------- */
#define HEs_BlOpt    0x2c8  /*     Heizung Blockoptimierung ULONG            */
#define HEs_BlOpt_HW 0x2c9
#define HEs_BlOpt2   0x2ca  /*     Heizung Blockoptimierung ULONG            */
#define HEs_BlOpt2HW 0x2cb
/*------------------------- Schneckenrueckzug vor und nach Plastifizieren - */
#define IqtDummy     0x2cc  /*     IQT-SPS-Dummy Register                   */
#define AWspZur      0x2cd  /* Auswerferdruck zurueck Seite 52.0            */
#define SRSsvor_1    0x2cf  /*     Schneckenrueckzug vor Plastif.  Agg.1    */
#define SRSsvor_2    0x2d0  /*     Schneckenrueckzug vor Plastif.  Agg.2    */
#define SRSvvor_1    0x2d1  /*     Rueckzugsgeschw. vor Plastif.   Agg.1    */
#define SRSvvor_2    0x2d2  /*     Rueckzugsgeschw. vor Plastif.   Agg.2    */
#define SRSsnach_1   0x2d3  /*     Schneckenrueckzug nach Plastif. Agg.1    */
#define SRSsnach_2   0x2d4  /*     Schneckenrueckzug nach Plastif. Agg.2    */
#define SRSvnach_1   0x2d5  /*     Rueckzugsgeschw. nach Plastif.  Agg.1    */
#define SRSvnach_2   0x2d6  /*     Rueckzugsgeschw. nach Plastif.  Agg.2    */
/*----------------- Maschinen-Abgleich-Seiten ----------------------------- */
#define WZGenMod     0x2d7  /*     89.1 default/RAM/PROM            SOLL    */
#define WSskOff      0x2d8  /*     89.1 Werkzeug schliessen Offset  SOLL    */
#define WSskGain     0x2d9  /*     89.1 Werkzeug schliessen Gain    SOLL    */
#define WOskOff      0x2da  /*     89.1 Werkzeug oeffnen Offset     SOLL    */
#define WOskGain     0x2db  /*     89.1 Werkzeug oeffnen Gain       SOLL    */
/* ---------------- END Abgleichseite 89.1 -------------------------------- */
#define AWGenMod     0x2dc  /*     89.2 default/RAM/PROM            SOLL    */
#define AWskVOff     0x2dd  /*     89.2 Auswerfer vor Offset        SOLL    */
#define AWskVGain    0x2de  /*     89.2 Auswerfer vor Gain          SOLL    */
#define AWskZOff     0x2df  /*     89.2 Auswerfer zurueck Offset    SOLL    */
#define AWskZGain    0x2e0  /*     89.2 Auswerfer zurueck Gain      SOLL    */
/* ---------------- END Abgleichseite 89.2 -------------------------------- */
#define PL1GenMod    0x2e1  /*     89.3 default/RAM/PROM Agg.1       SOLL   */
#define PLsvMess     0x2e2  /*     89.3 Plastifizier Ist-Anzeige MessMax SOLL*/
#define PLsvOben     0x2e3  /*     89.3 Plastifizier Ist-Anzeige Oben    SOLL*/
#define PLskRampe1   0x2e4  /*     89.3 Plastifizierzeit-Rampe Agg.1 SOLL   */
#define PLskGest1    0x2e5  /*     89.3 Plastifizierzeit gest. Agg.1 SOLL   */
#define PL2GenMod    0x2e6  /*     89.3 default/RAM/PROM Agg.2       SOLL   */
#define PLskRampe2   0x2e7  /*     89.3 Plastifizierzeit-Rampe Agg.2 SOLL   */
#define PLskGest2    0x2e8  /*     89.3 Plastifizierzeit gest. Agg.2 SOLL   */
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
/* ---------------- Diagnoseseite Schliessdruckaufbau 87.5 ---------------- */
#define SDRGenMod    0x2e9  /*     87.5 default/RAM/Reset            SOLL   */
#define SDRstAufV    0x2ea  /*     87.5 SDR-Aufbauverzoegerungszeit  SOLL   */
#define SDRstAufB    0x2eb  /*     87.5 SDR-Aufbauzeit               SOLL   */
/* ---------------- END Diagnoseseite Schliessdruckaufbau 87.5 ------------ */
/*----------------- Maschinen-Abgleich-Seiten / KD ------------------------ */
#define MSsppumOff   0x2ec  /*     89.1 Offset-Y8007            SOLL        */
#define WSskOff2     0x2ed  /*     89.1 Wkz schliessen Nullpunkt Ventil Y0488 SOLL */
#define WOskOff2     0x2ee  /*     89.1 Wkz oeffnen Nullpunkt Ventil Y0488 SOLL */
#define MGenMod      0x2ef  /*     89.1 default/RAM/PROM        SOLL        */
/* ---------------- END Maschinen-Abgleich-Seiten / KD -------------------- */
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
#define DiagRDInd    0x2f0  /* ReadIndex in Diagnosemodul-Tabelle           */
#define DiagWRInd    0x2f1  /* WriteIndex in Diagnosemodul-Tabelle          */
/* ------------------------------------------------------------------------ */
#define FDiagDFOR    0x2f2  /* ULONG Digitalausgaenge der Seite 87.8         */
#define FDiagDFOR_HW 0x2f3
#define FDiagA_F01   0x2f4  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F02   0x2f5  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F03   0x2f6  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F04   0x2f7  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F05   0x2f8  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F06   0x2f9  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F07   0x2fa  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F08   0x2fb  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F09   0x2fc  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F10   0x2fd  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F11   0x2fe  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F12   0x2ff  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F13   0x300  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F14   0x301  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F15   0x302  /*      Analogausgaenge der Seite 87.8          */
#define FDiagA_F16   0x303  /*      Analogausgaenge der Seite 87.8          */
/* ---------------- Standarddiagnoseseiten -------------------------------- */
#define FOR_Dval1    0x304  /* ULONG */
#define FOR_Dval1_HW 0x305
#define FOR_Dval2    0x306  /* ULONG */
#define FOR_Dval2_HW 0x307
#define FOR_Dval3    0x308  /* ULONG */
#define FOR_Dval3_HW 0x309
#define FOR_Dval4    0x30a  /* ULONG */
#define FOR_Dval4_HW 0x30b
#define FOR_Dval5    0x30c  /* ULONG */
#define FOR_Dval5_HW 0x30d
#define FOR_Dval6    0x30e  /* ULONG */
#define FOR_Dval6_HW 0x30f
#define FOR_Dval7    0x310  /* ULONG */
#define FOR_Dval7_HW 0x311
/* ------------------------------------------------------------------------ */
#define FOR1Aval01   0x312  /*      Analogausgaenge Modul1                  */
#define FOR1Aval02   0x313  /*      Analogausgaenge Modul1                  */
#define FOR1Aval03   0x314  /*      Analogausgaenge Modul1                  */
#define FOR1Aval04   0x315  /*      Analogausgaenge Modul1                  */
#define FOR1Aval05   0x316  /*      Analogausgaenge Modul1                  */
#define FOR1Aval06   0x317  /*      Analogausgaenge Modul1                  */
#define FOR1Aval07   0x318  /*      Analogausgaenge Modul1                  */
#define FOR1Aval08   0x319  /*      Analogausgaenge Modul1                  */
#define FOR1Aval09   0x31a  /*      Analogausgaenge Modul1                  */
#define FOR1Aval10   0x31b  /*      Analogausgaenge Modul1                  */
#define FOR1Aval11   0x31c  /*      Analogausgaenge Modul1                  */
#define FOR1Aval12   0x31d  /*      Analogausgaenge Modul1                  */
#define FOR1Aval13   0x31e  /*      Analogausgaenge Modul1                  */
#define FOR1Aval14   0x31f  /*      Analogausgaenge Modul1                  */
#define FOR1Aval15   0x320  /*      Analogausgaenge Modul1                  */
#define FOR1Aval16   0x321  /*      Analogausgaenge Modul1                  */
/* ------------------------------------------------------------------------ */
#define FOR2Aval01   0x322  /*      Analogausgaenge Modul2                  */
#define FOR2Aval02   0x323  /*      Analogausgaenge Modul2                  */
#define FOR2Aval03   0x324  /*      Analogausgaenge Modul2                  */
#define FOR2Aval04   0x325  /*      Analogausgaenge Modul2                  */
#define FOR2Aval05   0x326  /*      Analogausgaenge Modul2                  */
#define FOR2Aval06   0x327  /*      Analogausgaenge Modul2                  */
#define FOR2Aval07   0x328  /*      Analogausgaenge Modul2                  */
#define FOR2Aval08   0x329  /*      Analogausgaenge Modul2                  */
#define FOR2Aval09   0x32a  /*      Analogausgaenge Modul2                  */
#define FOR2Aval10   0x32b  /*      Analogausgaenge Modul2                  */
#define FOR2Aval11   0x32c  /*      Analogausgaenge Modul2                  */
#define FOR2Aval12   0x32d  /*      Analogausgaenge Modul2                  */
#define FOR2Aval13   0x32e  /*      Analogausgaenge Modul2                  */
#define FOR2Aval14   0x32f  /*      Analogausgaenge Modul2                  */
#define FOR2Aval15   0x330  /*      Analogausgaenge Modul2                  */
#define FOR2Aval16   0x331  /*      Analogausgaenge Modul2                  */
/* ------------------------------------------------------------------------ */
/* ---------------- Verknuepfung Handling mit Kern ------------------------ */
#define FPKZandFHK   0x332  /*     Seite 70.0 FHK-Schnittstelle             */
/* ---------------- Max. Plastifizierweg ---------------------------------- */
#define PLgweg1      0x333  /* Max. Plastifizierweg 1.Agg                   */
#define PLgweg2      0x334  /* Max. Plastifizierweg 2.Agg                   */
#define PLgweg3      0x335  /* Max. Plastifizierweg 3.Agg                   */
#define PLgweg4      0x336  /* Max. Plastifizierweg 4.Agg                   */
/* ---------------- Max. Schneckenumdrehung ------------------------------- */
#define SNg_Umdr1    0x337  /* Max. Schneckenumdrehung 1.Agg                */
#define SNg_Umdr2    0x338  /* Max. Schneckenumdrehung 2.Agg                */
#define SNg_Umdr3    0x339  /* Max. Schneckenumdrehung 3.Agg                */
#define SNg_Umdr4    0x33a  /* Max. Schneckenumdrehung 4.Agg                */
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define WZA_BA       0x33b  /* Betriebsart Werkzeugauswerfer                */
#define WZA_Spktv    0x33c  /* Startpunkt Werkzeugauswerfer vor             */
#define WZA_Auswh    0x33d  /* Anzahl Auswerferhuebe                        */
#define WZA_Wzvor    0x33e  /* Wartezeit vor                                */
#define WZA_Akzvor   0x33f  /* Aktionszeit Auswerfer vor                    */
#define WZA_Akzzur   0x340  /* Aktionszeit Auswerfer zurueck                */
#define WZApvor      0x341  /* Auswerferdruck vor                           */
#define WZApzur      0x342  /* Auswerferdruck zurueck                       */
#define WZAvvor1     0x343  /* Auswerfergeschwindigkeit vor v1              */
#define WZAvvor2     0x344  /* Auswerfergeschwindigkeit vor v2              */
#define WZAvzur      0x345  /* Auswerfergeschwindigkeit zurueck             */
/* ---------------- Werkzeugauswerfer 2 ----------------------------------- */
#define WZA_BA2      0x346  /* Betriebsart Werkzeugauswerfer                */
#define WZA_Spktv2   0x347  /* Startpunkt Werkzeugauswerfer vor             */
#define WZA_Auswh2   0x348  /* Anzahl Auswerferhuebe                        */
#define WZA_Wzvor2   0x349  /* Wartezeit vor                                */
#define WZA_Akzvo2   0x34a  /* Aktionszeit Auswerfer vor                    */
#define WZA_Akzzu2   0x34b  /* Aktionszeit Auswerfer zurueck                */
#define WZApvor2     0x34c  /* Auswerferdruck vor                           */
#define WZApzur2     0x34d  /* Auswerferdruck zurueck                       */
#define WZAvvor12    0x34e  /* Auswerfergeschwindigkeit vor v1              */
#define WZAvvor22    0x34f  /* Auswerfergeschwindigkeit vor v2              */
#define WZAvzur2     0x350  /* Auswerfergeschwindigkeit zurueck             */
#define WZA_BA_FHK   0x351  /* Betriebsart Werkzeugauswerfer                */
/* ---------------- Werkzeug Wenden --------------------------------------- */
#define WDm_Betart   0x352  /* Betriebsart Wenden                           */
#define WDm_Stapkt   0x353  /* Startpunkt Wenden                            */
#define WDstVerz     0x354  /* Zustand Endlage Wenden                       */
#define WDsv11       0x355  /* v11                                          */
#define WDsv12       0x356  /* v12                                          */
#define WDsv21       0x357  /* v21                                          */
#define WDsv22       0x358  /* v22                                          */
#define WDsp11       0x359  /* p11                                          */
#define WDsp12       0x35a  /* p12                                          */
#define WDsp21       0x35b  /* p21                                          */
#define WDsp22       0x35c  /* p22                                          */
#define WDsvEinrgr   0x35d  /* Einrichtgeschwindigkeit geregelt             */
#define WDsvgereg    0x35e  /* Wendegeschwindigkeit geregelt                */
/* ---------------- Drehteller-Parameter ---------------------------------- */
#define DTsaBeschl   0x35f  /* Beschleunigung                               */
#define DTstVerz     0x360  /* Verzoegerung                                 */
#define DTs_VOff1    0x361  /* Ventiloffset 1                               */
#define DTs_VOff2    0x362  /* Ventiloffset 2                               */
#define DTs_Skges    0x363  /* Skalierung gesteuert                         */
#define DTs_Skger    0x364  /* Skalierung geregelt                          */
#define DTs_Zielf    0x365  /* Zielfenster                                  */
#define DTs_Sweite   0x366  /* Schrittweite                                 */
#define DTGenMod     0x367  /* Softkeyregister Drehteller-Parameter erstellen */
#define DTs_Num      0x368  /* Seriennummer Winkelkodierer                  */
#define DTs_Num_HW   0x369  
/* ------------------- SOLLWERT S.71 Kartonzaehler ------------------------ */
#define OPsnKarton   0x36a  /* Anzahl Teile pro Karton                      */
#define OPs_Neust    0x36b  /* Neustart Kartonzaehler                       */
/* ------------------- SOLLWERT S.71 getaktes Foerderband ----------------- */
#define BA_foer      0x36c  /* Foerderband S. 71.0                          */
#define FBst         0x36d  /* Laufzeit bei getaktetem Betrieb S 71.0       */
#define SZinSUB      0x36e  /* LONG subtrahierender Schusszaehler (0x36e,0x36f) */
#define SZinSUB_HW   0x36f
/* ------------------- SOLLWERT S.49 Spritzeinheit mit Wegmesslineal ------ */
#define SEssVor11    0x370  /* Wegpunkt vor SE1                             */
#define SEssZur11    0x371  /* Wegpunkt zurueck SE1                         */
#define SEssNlpkt1   0x372  /* Nullpunkt-Wegpunkt SE1                       */
#define SEssVor12    0x373  /* Wegpunkt vor SE2                             */
#define SEssZur12    0x374  /* Wegpunkt zurueck SE2                         */
#define SEssNlpkt2   0x375  /* Nullpunkt-Wegpunkt SE2                       */
/* ------------------------------------------------------------------------ */
#define ZHs_Wasser   0x376  /* K}hlwasser-Abschaltung Seite 80.0            */
/* -------- Register fuer  S. 39.9 ------------------ */
#define HXsnIF       0x377  /* Schnittstelle */
#define HXsnProto    0x378  /* Protokoll */
#define HXsnBaud     0x379  /* Baudrate */
#define HXsnDatBit   0x37a  /* Datenbits */
#define HXsnStpBit   0x37b  /* Stopbits */
#define HXsnParity   0x37c  /* Parity */
#define HXsnIF_2     0x37d  /* Schnittstelle */
#define HXsnProto2   0x37e  /* Protokoll */
#define HXsnBaud_2   0x37f  /* Baudrate */
#define HXsnDatBi2   0x380  /* Datenbits */
#define HXsnStpBi2   0x381  /* Stopbits */
#define HXsnParit2   0x382  /* Parity */
/*----------------- Maschinenabgleichs-Seite: Ventile --------------------- */
#define Ventil_Mod   0x383  /*     Load RAM/ROM-Identifikation              */
#define MAs_VenInd   0x384  /*     89.1 Ventiloffset                SOLL    */
#define MAs_Offs1    0x385  /*     89.1 Offset 1                    SOLL    */
#define MAs_Offs2    0x386  /*     89.1 Offset 2                    SOLL    */
#define MAs_Vers1    0x387  /*     89.1 Verstaerkung 1              SOLL    */
#define MAs_Vers2    0x388  /*     89.1 Verstaerkung 2              SOLL    */
/* ------------------------------------------------------------------------ */
#define MSksSnDur1   0x389  /* aktueller Schneckendurchmesser     Agg.1     */
#define MSksSnDur2   0x38a  /* aktueller Schneckendurchmesser     Agg.2     */
/* -------- Register fuer Produktionsstart S. 40.2 ------------------------ */
#define XSn_Anfa     0x38b  /* Anzahl Anfahrzyklen */              
#define ssdos1a      0x38c  /* Plastivizierweg     */                  
#define spph11a      0x38d  /* Einspritzdruck p1   */                
#define svph11a      0x38e  /* Einspritzgeschw. v1 */              
#define stph11a      0x38f  /* Einspritzzeit t1    */                 
#define ssph11a      0x390  /* Umschaltpunkt s1    */                 
#define spph12a      0x391  /* Einspritzdruck p2   */                
#define svph12a      0x392  /* Einspritzgeschw. v2 */              
#define stph12a      0x393  /* Einspritzzeit t2    */                 
#define ssph12a      0x394  /* Umschaltpunkt s2    */                 
#define spph13a      0x395  /* Einspritzdruck p3   */                
#define svph13a      0x396  /* Einspritzgeschw. v3 */              
#define stph13a      0x397  /* Einspritzzeit t3    */                 
#define XSn_Anf2a    0x398  /* Anzahl Anfahrzyklen Wkz-Druck */    
#define spnidra      0x399  /* Druck werkzeugsicherung1 */         
#define spnidr2a     0x39a  /* Druck werkzeugsicherung2 */           

/* ------------------------------------------------------------------------ */
/*  $$$ Register fuer Heizungs-Sollwerte                                    */
/* ------------------------------------------------------------------------ */
#define snregl       0x3a0  /* Reglernummer                                 */
#define sngrup       0x3a1  /* Reglernummer                                 */
#define sktemp       0x3a2  /* Temperatur-Sollwert                          */
#define skgwnw       0x3a3  /* Toleranz negativ weit                        */
#define skgwne       0x3a4  /* Toleranz negativ eng                         */
#define skgwpw       0x3a5  /* Toleranz positiv weit                        */
#define skgwpe       0x3a6  /* Toleranz positiv eng                         */
#define snmcw        0x3a7  /* Mode Control Wort (unbenutzt)                */
#define snxph        0x3a8  /* XP Heizen                                    */
#define snxpk        0x3a9  /* XP Kuehlen                                   */
#define sntn         0x3aa  /* TN Nachstellzeit                             */
#define sntv         0x3ab  /* TV Vorhaltezeit                              */
#define sntoh        0x3ac  /* Schaltperiodendauer Heizen                   */
#define sntok        0x3ad  /* Schaltperiodendauer Kuehlen                  */
#define snshy        0x3ae  /* Schalthysterese                              */
#define sny          0x3af  /* Arbeitspunkt                                 */
#define snymin       0x3b0  /* minimale Stellgroesse                        */
#define snymax       0x3b1  /* maximale Stellgroesse                        */
#define sntm         0x3b2  /* Motorzeitkonstante                           */
#define snspst       0x3b3  /* Motorzeitkonstante                           */
#define snonof       0x3b4  /* Heizung ein/aus (unbenutzt in Malterdingen)  */
#define snssol       0x3b5  /* Strom Sollwert                               */
#define snstel       0x3b6  /* Sollwert fuer Steller (frueher Strombegrenz.)*/
#define snthty       0x3bb  /* Thermoelement-Typ                            */
#define snmess       0x3bc  /* Messung ein/aus                              */
#define snfunc       0x3bd  /* Funktion (Steller, 2-, 3-Punkt-Regler)       */
#define snloop       0x3be  /* Schleifennummer (unbenutzt)                  */
#define sncnty       0x3bf  /* Konvertertyp (unbenutzt)                     */

/* ------------------------------------------------------------------------ */
/* START Istwert-Register die mit TP_RD_SPEC gelesen werden                   */
/* ------------------------------------------------------------------------ */
#define IMSisK11     0x3c0  /* 89.0 Weg1 K1 Konstante ULONG   IST            */
#define IMSisK11_HW  0x3c1
#define IMSisOff1    0x3c2  /* 89.0 Weg1 Offset              IST            */
#define IMSisK12     0x3c3  /* 89.0 Weg2 K1 Konstante ULONG   IST            */
#define IMSisK12_HW  0x3c4
#define IMSisOff2    0x3c5  /* 89.0 Weg2 Offset              IST            */
#define IMSisK13     0x3c6  /* 89.0 Weg3 K1 Konstante ULONG   IST            */
#define IMSisK13_HW  0x3c7
#define IMSisOff3    0x3c8  /* 89.0 Weg3 Offset              IST            */
#define IMSisK14     0x3c9  /* 89.0 Weg4 K1 Konstante ULONG   IST            */
#define IMSisK14_HW  0x3ca
#define IMSisOff4    0x3cb  /* 89.0 Weg4 Offset              IST            */
#define IMSisAkt1    0x3cc  /* 89.0 Weg1 Istwert             IST            */
#define IMSisAkt2    0x3cd  /* 89.0 Weg2 Istwert             IST            */
#define IMSisAkt3    0x3ce  /* 89.0 Weg3 Istwert             IST            */
#define IMSisAkt4    0x3cf  /* 89.0 Weg4 Istwert             IST            */
#define IMSinAkt     0x3d0  /* 89.0 default/RAM/PROM         IST            */
#define IMSinStat    0x3d1  /* 89.0 Status                   IST            */
/*----------------- Maschinen-Abgleich-Seiten ----------------------------- */
#define WSikOff      0x3d2  /* 89.1 Werkzeug schliessen Offset IST          */
#define WSikGain     0x3d3  /* 89.1 Werkzeug schliessen Gain   IST          */
#define WOikOff      0x3d4  /* 89.1 Werkzeug oeffnen Offset    IST          */
#define WOikGain     0x3d5  /* 89.1 Werkzeug oeffnen Gain      IST          */
/* ---------------- END Abgleichseite 89.1 -------------------------------- */
#define AWikVOff     0x3d6  /* 89.2 Auswerfer vor Offset       IST          */
#define AWikVGain    0x3d7  /* 89.2 Auswerfer vor Gain         IST          */
#define AWikZOff     0x3d8  /* 89.2 Auswerfer zurueck Offset   IST          */
#define AWikZGain    0x3d9  /* 89.2 Auswerfer zurueck Gain     IST          */
/* ---------------- END Abgleichseite 89.2 -------------------------------- */
#define PLivAMess    0x3da  /* 89.3 Akt. Plastifizier Ist-Anzeige Mess IST  */
#define PLivDMess    0x3db  /* 89.3 Def. Plastifizier Ist-Anzeige Mess IST  */
#define PLivAOben    0x3dc  /* 89.3 Akt. Plastifizier Ist-Anzeige Oben IST  */
#define PLivDOben    0x3dd  /* 89.3 Def. Plastifizier Ist-Anzeige Oben IST  */
#define PLikARamp1   0x3de  /* 89.3 Akt. Plastifizier_Rampe Agg.1   IST     */
#define PLikDRamp1   0x3df  /* 89.3 Def. Plastifizier_Rampe Agg.1   IST     */
#define PLikAGest1   0x3e0  /* 89.3 Akt. Plastifizieren gest. Agg.1 IST     */
#define PLikDGest1   0x3e1  /* 89.3 Def. Plastifizieren gest. Agg.1 IST     */
#define PLikARamp2   0x3e2  /* 89.3 Akt. Plastifizier_Rampe Agg.2   IST     */
#define PLikDRamp2   0x3e3  /* 89.3 Def. Plastifizier_Rampe Agg.2   IST     */
#define PLikAGest2   0x3e4  /* 89.3 Akt. Plastifizieren gest. Agg.2 IST     */
#define PLikDGest2   0x3e5  /* 89.3 Def. Plastifizieren gest. Agg.2 IST     */
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
/* ---------------- Diagnoseseite Schliessdruckaufbau 87.5 ---------------- */
#define SDRitAAufV   0x3e6  /* 87.5 Akt. SDR-Aufbauverzoegerungszeit IST    */
#define SDRitDAufV   0x3e7  /* 87.5 Def. SDR-Aufbauverzoegerungszeit IST    */
#define SDRitAAufB   0x3e8  /* 87.5 Akt. SDR-Aufbauzeit IST                 */
#define SDRitDAufB   0x3e9  /* 87.5 Def. SDR-Aufbauzeit IST                 */
/* ---------------- END Diagnoseseite Schliessdruckaufbau 87.5 ------------ */
#define MSippumOff   0x3ea  /* 89.1 Offset-Y8007             IST            */
#define WSikOff2     0x3eb  /* 89.1 Wkz schliessen Nullpunkt Ventil Y0488 IST */
#define WOikOff2     0x3ec  /* 89.1 Wkz schliessen Nullpunkt Ventil Y0488 IST */
/*----------------- Maschinenabgleich-Seite Ventile ----------------------- */
#define MAi_Offs1    0x3ed  /* 89.1 Offset1  IST */
#define MAi_Offs2    0x3ee  /* 89.1 Offset2  IST */
#define MAi_Offs3    0x3ef  /* 89.1 Offset3  IST */
#define MAi_Offs4    0x3f0  /* 89.1 Offset4  IST */
#define MAi_Offs5    0x3f1  /* 89.1 Offset5  IST */
#define MAi_Offs6    0x3f2  /* 89.1 Offset6  IST */
#define MAi_Offs7    0x3f3  /* 89.1 Offset7  IST */
#define MAi_Offs8    0x3f4  /* 89.1 Offset8  IST */
#define MAi_Offs9    0x3f5  /* 89.1 Offset9  IST */
#define MAi_Offs10   0x3f6  /* 89.1 Offset10 IST */
#define MAi_Vers1    0x3f7  /* 89.1 Verstaerkung1  IST */
#define MAi_Vers2    0x3f8  /* 89.1 Verstaerkung2  IST */
#define MAi_Vers3    0x3f9  /* 89.1 Verstaerkung3  IST */
#define MAi_Vers4    0x3fa  /* 89.1 Verstaerkung4  IST */
#define MAi_Vers5    0x3fb  /* 89.1 Verstaerkung5  IST */
#define MAi_Vers6    0x3fc  /* 89.1 Verstaerkung6  IST */
#define MAi_Vers7    0x3fd  /* 89.1 Verstaerkung7  IST */
#define MAi_Vers8    0x3fe  /* 89.1 Verstaerkung8  IST */
#define MAi_Vers9    0x3ff  /* 89.1 Verstaerkung9  IST */
#define MAi_Vers10   0x400  /* 89.1 Verstaerkung10 IST */
/* ---------------- END Maschinen-Abgleich-Seiten / KD -------------------- */
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
#define FDiagDAKT    0x401  /* ULONG Digitaleingaenge fuer Seite 87.8        */
#define FDiagDAKT_HW 0x402
#define FDiagA_A01   0x403  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A02   0x404  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A03   0x405  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A04   0x406  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A05   0x407  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A06   0x408  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A07   0x409  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A08   0x40a  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A09   0x40b  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A10   0x40c  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A11   0x40d  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A12   0x40e  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A13   0x40f  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A14   0x410  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A15   0x411  /*      Analogeingaenge fuer Seite 87.8         */
#define FDiagA_A16   0x412  /*      Analogeingaenge fuer Seite 87.8         */
/* ---------------- Standarddiagnoseseiten -------------------------------- */
#define AKT_Dval1    0x413  /* ULONG Digitaleingaenge                        */
#define AKT_Dval1_HW 0x414
#define AKT_Dval2    0x415  /* ULONG Digitaleingaenge                        */
#define AKT_Dval2_HW 0x416
#define AKT_Dval3    0x417  /* ULONG Digitaleingaenge                        */
#define AKT_Dval3_HW 0x418
#define AKT_Dval4    0x419  /* ULONG Digitaleingaenge                        */
#define AKT_Dval4_HW 0x41a
#define AKT_Dval5    0x41b  /* ULONG Digitaleingaenge                        */
#define AKT_Dval5_HW 0x41c
#define AKT_Dval6    0x41d  /* ULONG Digitaleingaenge                        */
#define AKT_Dval6_HW 0x41e
#define AKT_Dval7    0x41f  /* ULONG Digitaleingaenge                        */
#define AKT_Dval7_HW 0x420
/* ------------------------------------------------------------------------ */
#define AKT1Aval01   0x421  /*      Analogausgaenge Modul1                  */
#define AKT1Aval02   0x422  /*      Analogausgaenge Modul1                  */
#define AKT1Aval03   0x423  /*      Analogausgaenge Modul1                  */
#define AKT1Aval04   0x424  /*      Analogausgaenge Modul1                  */
#define AKT1Aval05   0x425  /*      Analogausgaenge Modul1                  */
#define AKT1Aval06   0x426  /*      Analogausgaenge Modul1                  */
#define AKT1Aval07   0x427  /*      Analogausgaenge Modul1                  */
#define AKT1Aval08   0x428  /*      Analogausgaenge Modul1                  */
#define AKT1Aval09   0x429  /*      Analogausgaenge Modul1                  */
#define AKT1Aval10   0x42a  /*      Analogausgaenge Modul1                  */
#define AKT1Aval11   0x42b  /*      Analogausgaenge Modul1                  */
#define AKT1Aval12   0x42c  /*      Analogausgaenge Modul1                  */
#define AKT1Aval13   0x42d  /*      Analogausgaenge Modul1                  */
#define AKT1Aval14   0x42e  /*      Analogausgaenge Modul1                  */
#define AKT1Aval15   0x42f  /*      Analogausgaenge Modul1                  */
#define AKT1Aval16   0x430  /*      Analogausgaenge Modul1                  */
/* ------------------------------------------------------------------------ */
#define AKT2Aval01   0x431  /*      Analogausgaenge Modul2                  */
#define AKT2Aval02   0x432  /*      Analogausgaenge Modul2                  */
#define AKT2Aval03   0x433  /*      Analogausgaenge Modul2                  */
#define AKT2Aval04   0x434  /*      Analogausgaenge Modul2                  */
#define AKT2Aval05   0x435  /*      Analogausgaenge Modul2                  */
#define AKT2Aval06   0x436  /*      Analogausgaenge Modul2                  */
#define AKT2Aval07   0x437  /*      Analogausgaenge Modul2                  */
#define AKT2Aval08   0x438  /*      Analogausgaenge Modul2                  */
#define AKT2Aval09   0x439  /*      Analogausgaenge Modul2                  */
#define AKT2Aval10   0x43a  /*      Analogausgaenge Modul2                  */
#define AKT2Aval11   0x43b  /*      Analogausgaenge Modul2                  */
#define AKT2Aval12   0x43c  /*      Analogausgaenge Modul2                  */
#define AKT2Aval13   0x43d  /*      Analogausgaenge Modul2                  */
#define AKT2Aval14   0x43e  /*      Analogausgaenge Modul2                  */
#define AKT2Aval15   0x43f  /*      Analogausgaenge Modul2                  */
#define AKT2Aval16   0x440  /*      Analogausgaenge Modul2                  */
/* ------------------------------------------------------------------------ */
#define AKT3Aval01   0x441  /*      Analogausgaenge Modul2                  */
#define AKT3Aval02   0x442  /*      Analogausgaenge Modul2                  */
#define AKT3Aval03   0x443  /*      Analogausgaenge Modul2                  */
#define AKT3Aval04   0x444  /*      Analogausgaenge Modul2                  */
#define AKT3Aval05   0x445  /*      Analogausgaenge Modul2                  */
#define AKT3Aval06   0x446  /*      Analogausgaenge Modul2                  */
#define AKT3Aval07   0x447  /*      Analogausgaenge Modul2                  */
#define AKT3Aval08   0x448  /*      Analogausgaenge Modul2                  */
/* ---------------- Matrixtastatur ---------------------------------------- */
#define A0Input      0x449
#define A1Input      0x44a
#define A2Input      0x44b
#define A3Input      0x44c
/* ---------------- SPS-CPU-Typ ------------------------------------------- */
#define SPSCPUType   0x44d  /* SPS CPY-Type (z.B. CP100, CP151, CP152 usw.) */
/* ---------------- WegMess-Typ ------------------------------------------- */
#define SPSWegMTyp   0x44e  /* SPS Weg-Messtyp (Analog, CAN usw.)           */
#define DiagMaxMod   0x44f  /* Anzahl der zu diagnostiziere Module          */
/* ------------------------------------------------------------------------ */
#define HXinPageAW   0x450  /* Anzeige-Auswahregister fuer die Einstellungsseite serielle Temperiergeraete */
/* ------------------------------------------------------------------------ */
/* Register fuer DM-Daten fuer Freiauswaehlbare Diagnoseseite               */
/* ------------------------------------------------------------------------ */
#define DiagSysTyp   0x451  /* Systemtyp                                    */
#define DiagBusNr    0x452  /* BusNr (Basisrueckwand, Erweiterung1,2,3,4)   */
#define DiagModNr    0x453  /* Modulnummer                                  */
#define DiagIndTab   0x454  /* Index in Diagnosetabelle                     */
/*--------------------- Schneckenfreigabeverz|gerungszeit Seite 30.0 ------ */
#define HZit_Verz1   0x455  /* Agg1 */
#define HZit_Verz2   0x456  /* Agg2 */
#define HZit_Verz3   0x457  /* Agg3 */
#define HZit_Verz4   0x458  /* Agg4 */
/*-------------------- Register fuer die Diagnoseseiten ------------------- */
/*--------------------- Diagnoseseite 87.0 Aggregat 1 --------------------- */
#define diagm1       0x459  /* Diagnoseseite                                */
#define diagm2       0x45a  /* Diagnoseseite                                */
#define diagm3       0x45b  /* Diagnoseseite                                */
#define diagm4       0x45c  /* Diagnoseseite                                */
#define diagm5       0x45d  /* Diagnoseseite                                */
#define diagm6       0x45e  /* Diagnoseseite                                */
#define diagm7       0x45f  /* Diagnoseseite                                */
#define diagm8       0x460  /* Diagnoseseite                                */
#define diagm9       0x461  /* Diagnoseseite                                */
#define diagma       0x462  /* Diagnoseseite                                */
#define diagmb       0x463  /* Diagnoseseite                                */
#define diagmc       0x464  /* Diagnoseseite                                */
#define diagmd       0x465  /* Diagnoseseite                                */
#define diagme       0x466  /* Diagnoseseite                                */
#define diagmf       0x467  /* Diagnoseseite                                */
#define diagm10      0x468  /* Diagnoseseite                                */
#define diagm11      0x469  /* Diagnoseseite                                */
#define diagm12      0x46a  /* Diagnoseseite                                */
#define diagm13      0x46b  /* Diagnoseseite                                */
#define diagm14      0x46c  /* Diagnoseseite                                */
#define diagm15      0x46d  /* Diagnoseseite                                */
#define diagm16      0x46e  /* Diagnoseseite                                */
#define diagm17      0x46f  /* Diagnoseseite                                */
#define diagm18      0x470  /* Diagnoseseite                                */
#define diagm19      0x471  /* Diagnoseseite                                */
#define diagm1a      0x472  /* Diagnoseseite                                */
#define diagm1b      0x473  /* Diagnoseseite                                */
#define diagm1c      0x474  /* Diagnoseseite                                */
#define diagm1d      0x475  /* Diagnoseseite                                */
#define diagm1e      0x476  /* Diagnoseseite                                */
#define diagm1f      0x477  /* Diagnoseseite                                */
#define diagm20      0x478  /* Diagnoseseite                                */
#define diagm21      0x479  /* Diagnoseseite                                */
#define diagm22      0x47a  /* Diagnoseseite                                */
#define diagm23      0x47b  /* Diagnoseseite                                */
#define diagm24      0x47c  /* Diagnoseseite                                */
#define diagm25      0x47d  /* Diagnoseseite                                */
#define diagm26      0x47e  /* Diagnoseseite                                */
#define diagm27      0x47f  /* Diagnoseseite                                */
#define diagm28      0x480  /* Diagnoseseite                                */
#define diagm29      0x481  /* Diagnoseseite                                */
#define diagm2a      0x482  /* Diagnoseseite                                */
#define diagm2b      0x483  /* Diagnoseseite                                */
#define diagm2c      0x484  /* Diagnoseseite                                */
#define diagm2d      0x485  /* Diagnoseseite                                */
#define diagm2e      0x486  /* Diagnoseseite ULONG                           */
#define diagm2e_HW   0x487
#define diagm2f      0x488  /* Diagnoseseite                                */
#define diagm30      0x489  /* Diagnoseseite                                */
#define diagm31      0x48a  /* Diagnoseseite ULONG                           */
#define diagm31_HW   0x48b
#define diagm32      0x48c  /* Diagnoseseite                                */
#define diagm33      0x48d  /* Diagnoseseite                                */
#define diagm34      0x48e  /* Diagnoseseite ULONG                           */
#define diagm34_HW   0x48f
#define diagm35      0x490  /* Diagnoseseite                                */
#define diagm36      0x491  /* Diagnoseseite                                */
/* ------------------- Diagnoseseite 87.0 Aggregat 2 ---------------------- */
#define diagm37      0x492  /* Diagnoseseite                                */
#define diagm38      0x493  /* Diagnoseseite                                */
#define diagm39      0x494  /* Diagnoseseite                                */
#define diagm3a      0x495  /* Diagnoseseite                                */
#define diagm3b      0x496  /* Diagnoseseite                                */
#define diagm3c      0x497  /* Diagnoseseite                                */
#define diagm3d      0x498  /* Diagnoseseite                                */
#define diagm3e      0x499  /* Diagnoseseite                                */
#define diagm3f      0x49a  /* Diagnoseseite                                */
#define diagm40      0x49b  /* Diagnoseseite                                */
#define diagm41      0x49c  /* Diagnoseseite                                */
#define diagm42      0x49d  /* Diagnoseseite                                */
#define diagm43      0x49e  /* Diagnoseseite                                */
#define diagm44      0x49f  /* Diagnoseseite                                */
#define diagm45      0x4a0  /* Diagnoseseite                                */
#define diagm46      0x4a1  /* Diagnoseseite                                */
#define diagm47      0x4a2  /* Diagnoseseite                                */
#define diagm48      0x4a3  /* Diagnoseseite                                */
#define diagm49      0x4a4  /* Diagnoseseite                                */
#define diagm4a      0x4a5  /* Diagnoseseite                                */
#define diagm4b      0x4a6  /* Diagnoseseite                                */
#define diagm4c      0x4a7  /* Diagnoseseite ULONG                           */
#define diagm4c_HW   0x4a8
#define diagm4d      0x4a9  /* Diagnoseseite                                */
#define diagm4e      0x4aa  /* Diagnoseseite                                */
#define diagm4f      0x4ab  /* Diagnoseseite ULONG                           */
#define diagm4f_HW   0x4ac
#define diagm50      0x4ad  /* Diagnoseseite                                */
#define diagm51      0x4ae  /* Diagnoseseite                                */
#define diagm52      0x4af  /* Diagnoseseite ULONG                           */
#define diagm52_HW   0x4b0
#define diagm53      0x4b1  /* Diagnoseseite                                */
#define diagm54      0x4b2  /* Diagnoseseite                                */
/*--------------------- Diagnoseseite 17.2 -------------------------------- */
#define diagm15a     0x4b3  /* Diagnoseseite                                */
#define diagm15b     0x4b4  /* Diagnoseseite                                */
#define diagm15c     0x4b5  /* Diagnoseseite                                */
#define diagm15d     0x4b6  /* Diagnoseseite                                */
#define diagm15e     0x4b7  /* Diagnoseseite                                */
#define diagm15f     0x4b8  /* Diagnoseseite                                */
#define diagm160     0x4b9  /* Diagnoseseite                                */
#define diagm161     0x4ba  /* Diagnoseseite                                */
#define diagm162     0x4bb  /* Diagnoseseite                                */
#define diagm163     0x4bc  /* Diagnoseseite                                */
#define diagm164     0x4bd  /* Diagnoseseite                                */
#define diagm165     0x4be  /* Diagnoseseite                                */
#define diagm166     0x4bf  /* Diagnoseseite                                */
#define diagm167     0x4c0  /* Diagnoseseite                                */
#define diagm168     0x4c1  /* Diagnoseseite                                */
#define diagm169     0x4c2  /* Diagnoseseite                                */
#define diagm16a     0x4c3  /* Diagnoseseite                                */
#define diagm16b     0x4c4  /* Diagnoseseite                                */
/* ------------------------------------------------------------------------ */
#define formact      0x4c5  /* Istwert fuer Formhoehenabgleich              */
/* ------------------------------------------------------------------------ */
#define xsnsp1       0x4c6  /* Farbinformation Schnellspannseite 56         */
#define xsnsp2       0x4c7  /* Farbinformation Schnellspannseite 56         */
/* ------------------- Drehteller-Parameter Seite 53.1 -------------------- */
#define DTisAbs      0x4c8  /* Drehteller: Absolutposition                  */
#define DTisRela     0x4c9  /* Drehteller: Relativposition                  */
#define DTiaBeschl   0x4ca  /* Drehteller: Beschleunigung                   */
#define DTitVerz     0x4cb  /* Drehteller: Verzoegeurng                     */
#define DTi_VOff1    0x4cc  /* Drehteller: Ventiloffset1                    */
#define DTi_VOff2    0x4cd  /* Drehteller: Ventiloffset2                    */
#define DTi_Skges    0x4ce  /* Drehteller: Skalierung gesteuert             */
#define DTi_Skger    0x4cf  /* Drehteller: Skalierung geregelt              */
#define DTi_Zielf    0x4d0  /* Drehteller: Zielfenster                      */
#define DTi_Sweite   0x4d1  /* Drehteller: Schrittweite                     */
#define DTi_Num      0x4d2  /* Seriennummer Winkelkodierer                  */
#define DTi_Num_HW   0x4d3
/* ------------------- Text Strings die von der SPS gelesen werden koennnen */
#define IText_1      0x4d4  /* SPS Text 1                                   */
#define IText_2      0x4ee  /* SPS Text 2                                   */
#define IText_3      0x508  /* SPS Text 3                                   */
#define IText_4      0x522  /* SPS Text 4                                   */
#define IText_5      0x53c  /* SPS Parameter-Kennungen                      */
/* ------------------------------------------------------------------------ */
/* END  IText_5      0x556                                                  */
/* ------------------------------------------------------------------------ */
/* END Istwert-Register die mit TP_RD_SPEC gelesen werden                   */
/* ------------------------------------------------------------------------ */

/* -------------------- Definitionen fuer frei progr. Kernzuege ----------  */
#define KEprgno		0x560		/* Kernzug-Programmnummer							*/
#define KEeinricht	0x561		/* Ueberwachung im Einrichten						*/
#define KEgrundst 	0x562		/* Grundstellung der Kerne   						*/
#define KEpgmstat		0x563		/* Aenderungszustand des Kernzugprogramms		*/
										/* 0=aktuell, 1=geaendert, 2=geprueft			*/
#define KEparupd		0x564		/* Anzeige der Parameteraenderungen 1=geaend.*/
#define KEpgmlines	0x565		/* Zeilenanzahl des Kernzugprogramms			*/
#define KEdlenable	0x566		/* download enable Register Bit 0 = 1 sperrt */
										/* den Datenaustausch								*/
#define KEdlstat	 	0x567		/* Status der Datenuebertragung 0=okay			*/
#define KEsync   		0x568		/* Handshake-Register beim download				*/
										/* 1=DL-Anforderung vom IQT, 2=DL vom IQT		*/
										/* durchgefuehrt, 0=Quittung von der SPS		*/
										/* nach der Quittung steht das Ergebnis in	*/
										/* dlstat												*/
#define KEIst1		 	0x569		/* Ist-Stellung der Kerne 1 - 9					*/
#define KEIst2		 	0x56a		/* aus=0, eingef.=1, ausgef.=2, in Zw.pos.=3	*/
#define KEIst3		 	0x56b
#define KEIst4		 	0x56c
#define KEIst5		 	0x56d
#define KEIst6		 	0x56e
#define KEIst7		 	0x56f
#define KEIst8		 	0x570
#define KEIst9		 	0x571
#define KEError1	 	0x572		/* Fehler der Kerne 1 - 9 je 32 Bit	*/
#define KEError2	 	0x574
#define KEError3	 	0x576
#define KEError4	 	0x578
#define KEError5	 	0x57a
#define KEError6	 	0x57c
#define KEError7	 	0x57e
#define KEError8	 	0x580
#define KEError9	 	0x582
#define KEError	 	0x584		/* allgemeine Fehler im Kernzugprogramm */
#define KEEvalid	 	0x586		/* Freigabe fuer Kernstellungen im Stepbetrieb	*/
#define KEExpSoll1	0x587		/* Erwartete Stellung der Kerne im Stepbetrieb	*/
#define KEExpSoll2	0x588		/* aus=0, eingef.=1, ausgef.=2, in Zw.pos.=3		*/
#define KEExpSoll3	0x589
#define KEExpSoll4	0x58a
#define KEExpSoll5	0x58b
#define KEExpSoll6	0x58c
#define KEExpSoll7	0x58d
#define KEExpSoll8	0x58e
#define KEExpSoll9	0x58f
#define KE_NrSchraub 0x590		/* enth„lt Nummer des Kerns der zum Schrauben */
										/* freigegeben ist									 */
#define KE_NrWend    0x591		/* enth„lt Nummer des Kerns der zum Wendem    */
										/* freigegeben ist									 */
#define KE_SperrMaske 0x592	/* maskiert (sperrt) Kerne						    */
										/* Bit 0 = 1 -> Kern 1 gesperrt usw. 			 */

#define KELineNo     0x5a0	 /* Programmzeile mit Zeilennummern	*/
									 /* und 12 Parametern				   */
#undef  IEndAddr
#define IEndAddr	   0x660  /* Ende des benutzten Adressraums  */ 

/* ------- Standard Prozessgrafik Bereich  -------------------------------- */
#define meas_event   0x670  /* Messung laueft/fertig                        */
#define startrec     0x671	 /* Start Einzelmessung                          */
#define reqblk_ist   0x672	 /* Request-Block Istkurve                       */
#define ackblk_ist   0x674	 /* Acknowledge-Block                            */
#define pg_mode      0x675	 /* Betriebsarten (Feld) [Funktion][Funktionseinheit] */
#define meastime     0x679	 /* Messzeiten [Funktion][Funktionseinheit]      */
#define delay        0x67d	 /* Startverzoegerungen [Funktion][Funktionseinheit] */
#define interval     0x681	 /* Messintervalle Zyklen [Funktion][Funktionseinheit] */
#define pg_aggregat  0x685  /* Standardgrafik Aggregat fuer Mehrfarbmachinen */
#define datablk_ist  0x690	 /* Kommunikationsbereich Istkurve               */

#define next_free	   0x740

/* die in der Standardgrafik nicht vewrwendeten Register werden in den IST 
	Datenblockbereich gelegt damit sie zumindest definiert sind              */
#define status	      0x690  /* Status, Bit 0 = 0 Download enable            */
#define reqblk_soll  0x691  /* Request-Block Sollkurve                      */
#define x_scale      0x692  /* Maximale Weg fuer X-Achse [Funktion][Funktionseinheit] */
#define tol_switch   0x696  /* Toleranz ein/aus (39 Werte) [Funktion][Funktionseinheit][Kurve] */
#define tolerance    0x6bc  /* Toleranzen in % (39 Werte) [Funktion][Funktionseinheit][Kurve] */
#define modework     0x6e2  /* Mode Arbeitsberechnung [Funktion][Funktionseinheit] */
#define startwork    0x6e6  /* Beginn Arbeitsberechnung [Funktion][Funktionseinheit] */
#define stopwork     0x6ea  /* Ende Arbeitsberechnung [Funktion][Funktionseinheit] */
#define istwork      0x6ee  /* Arbeit Istwert [Funktion][Funktionseinheit]  */
#define refwork      0x6f2  /* Arbeit Referenz [Funktion][Funktionseinheit] */
#define tolwork      0x6f6  /* Arbeit Toleranz in % [Funktion][Funktionseinheit] */
#define pres_area    0x6fa  /* Schliesskolbenflaeche [Funktionseinheit]     */
#define yscal        0x6fe  /* Y-Skalierung [Funktion][Funktionseinheit][Kurve] */
#define ymax         0x724  /* Messbereichsendwert [Kanal]!!!! d. h. 4 Register */
#define tol_errs     0x728  /* Anzahl der Toleranueberschreitungen in Folge */
#define free_reg0    0x729  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg1    0x72a  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg2    0x72b  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg3    0x72c  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg4    0x72d  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg5    0x72e  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg6    0x72f  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg7    0x730  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg8    0x731  /* zur freien Verwendung waehrend der Testzeit  */
#define free_reg9    0x732  /* zur freien Verwendung waehrend der Testzeit  */

#define datablk_soll 0x690  /* Kommunikationsbereich Sollkurve              */

/*------------------------- Sonderseite 48 Airpress "neu" ----------------- */
#define air_on   		0x740   /* Airpress Seite 48 (Sonderprogramm) */
#define dues_zu  		0x741
#define stverz_d1		0x742
#define stverz_d2		0x743
#define stverz_d3		0x744
#define stverz_d4		0x745
#define stact1_d1		0x746
#define stact1_d2		0x747
#define stact1_d3		0x748
#define stact1_d4		0x749
#define spres1_d1		0x74a
#define spres1_d2		0x74b
#define spres1_d3		0x74c
#define spres1_d4		0x74d
#define stact2_d1		0x74e
#define stact2_d2		0x74f
#define stact2_d3		0x750
#define stact2_d4		0x751
#define spres2_d1		0x752
#define spres2_d2		0x753
#define spres2_d3		0x754
#define spres2_d4		0x755
#define stact3_d1		0x756
#define stact3_d2		0x757
#define stact3_d3		0x758
#define stact3_d4		0x759
#define spres3_d1		0x75a
#define spres3_d2		0x75b
#define spres3_d3		0x75c
#define spres3_d4		0x75d
#define stact4_d1		0x75e
#define stact4_d2		0x75f
#define stact4_d3		0x760
#define stact4_d4		0x761
#define spres4_d1		0x762
#define spres4_d2		0x763
#define spres4_d3		0x764
#define spres4_d4		0x765
#define stact5_d1		0x766
#define stact5_d2		0x767
#define stact5_d3		0x768
#define stact5_d4		0x769
#define spres5_d1		0x76a
#define spres5_d2		0x76b
#define spres5_d3		0x76c
#define spres5_d4		0x76d   /* Airpress Seite 48 (Sonderprogramm) */ 
#define APd_Type     0x76e
#define APd_Mode     0x76f
#define APspSysT     0x770
#define APstRmp1D1   0x771
#define APstRmp1D2   0x772
#define APstRmp1D3   0x773
#define APstRmp1D4   0x774
#define APstRmp1D5   0x775
#define APstRmp2D1   0x776
#define APstRmp2D2   0x777
#define APstRmp2D3   0x778
#define APstRmp2D4   0x779
#define APstRmp2D5   0x77a
#define APstRmp3D1   0x77b
#define APstRmp3D2   0x77c
#define APstRmp3D3   0x77d
#define APstRmp3D4   0x77e
#define APstRmp3D5   0x77f
#define APstRmp4D1   0x780
#define APstRmp4D2   0x781
#define APstRmp4D3   0x782
#define APstRmp4D4   0x783
#define APstRmp4D5   0x784
#define APstRmp5D1   0x785
#define APstRmp5D2   0x786
#define APstRmp5D3   0x787
#define APstRmp5D4   0x788
#define APstRmp5D5   0x789
#define WKZDues_D1   0x78a
#define WKZDues_D2   0x78b
#define WKZDues_D3   0x78c
#define WKZDues_D4   0x78d

/* Permanente Register fuer das Gillette-Sonderprogramm         */
#define gil_xson0    0x790
#define gil_xson1    0x791
#define gil_xson2    0x792
#define gil_xson3    0x793
#define gil_xson4    0x794
#define gil_xson5    0x795
#define gil_xson6    0x796
#define gil_xson7    0x797
#define gil_xson8    0x798
#define gil_xson9    0x799
#define gil_xson10   0x79a
#define gil_xson11   0x79b
#define gil_xson12   0x79c
#define gil_xson13   0x79d
#define gil_xson14   0x79e
#define gil_xson15   0x79f
#define gil_sson0    0x7a0
#define gil_sson1    0x7a1
#define gil_sson2    0x7a2
#define gil_sson3    0x7a3
#define gil_sson4    0x7a4
#define gil_sson5    0x7a5
#define gil_sson6    0x7a6
#define gil_sson7    0x7a7
#define gil_sson8    0x7a8
#define gil_sson9    0x7a9
#define gil_sson10   0x7aa
#define gil_sson11   0x7ab
#define gil_sson12   0x7ac
#define gil_sson13   0x7ad
#define gil_sson14   0x7ae
#define gil_sson15   0x7af
#define gil_sson16   0x7b0
#define gil_sson17   0x7b1
#define gil_sson18   0x7b2
#define gil_sson19   0x7b3
#define gil_sson20   0x7b4
#define gil_sson21   0x7b5
#define gil_sson22   0x7b6
#define gil_sson23   0x7b7
#define gil_sson24   0x7b8
#define gil_sson25   0x7b9
#define gil_sson26   0x7ba
#define gil_sson27   0x7bb
#define gil_sson28   0x7bc
#define gil_sson29   0x7bd
#define gil_sson30   0x7be
#define gil_sson31   0x7bf
#define gil_sson32   0x7c0
#define gil_sson33   0x7c1
#define gil_sson34   0x7c2
#define gil_sson35   0x7c3
#define gil_sson36   0x7c4
#define gil_sson37   0x7c5
#define gil_sson38   0x7c6
#define gil_sson39   0x7c7
#define gil_sson40   0x7c8
#define gil_sson41   0x7c9
#define gil_sson42   0x7ca
#define gil_sson43   0x7cb
#define gil_sson44   0x7cc
#define gil_sson45   0x7cd
#define gil_sson46   0x7ce
#define gil_sson47   0x7cf
#define gil_sson48   0x7d0
#define gil_sson49   0x7d1
#define gil_sson50   0x7d2
#define gil_sson51   0x7d3
#define gil_sson52   0x7d4
#define gil_sson53   0x7d5
#define gil_sson54   0x7d6
#define gil_sson55   0x7d7 
#define gil_sson56   0x7d8
#define gil_sson57   0x7d9
#define gil_sson58   0x7da
#define gil_sson59   0x7db
#define gil_sson60   0x7dc
#define gil_sson61   0x7dd
#define gil_sson62   0x7de
#define gil_sson63   0x7df
#define gil_sson64   0x7e0
#define gil_sson65   0x7e1
#define gil_sson66   0x7e2
#define gil_sson67   0x7e3
#define gil_sson68   0x7e4
#define gil_sson69   0x7e5
#define gil_sson70   0x7e6
#define gil_sson71   0x7e7
#define gil_sson72   0x7e8
#define gil_sson73   0x7e9
#define gil_sson74   0x7ea
#define gil_sson75   0x7eb
#define gil_sson76   0x7ec
#define gil_sson77   0x7ed
#define gil_sson78   0x7ee
#define gil_sson79   0x7ef
#define gil_sson80   0x7f0
#define gil_sson81   0x7f1
#define gil_sson82   0x7f2
#define gil_sson83   0x7f3
#define gil_sson84   0x7f4
#define gil_sson85   0x7f5
#define gil_sson86   0x7f6
#define gil_sson87   0x7f7
#define gil_sson88   0x7f8
#define gil_sson89   0x7f9
#define gil_sson90   0x7fa
#define gil_sson91   0x7fb
#define gil_sson92   0x7fc
#define gil_sson93   0x7fd
#define gil_sson94   0x7fe
#define gil_sson95   0x7ff
#define gil_sson96   0x800
#define gil_sson97   0x801
#define gil_sson98   0x802
#define gil_sson99   0x803
#define gil_sson100  0x804
#define gil_sson101  0x805
#define gil_sson102  0x806
#define gil_sson103  0x807
#define gil_sson104  0x808
#define gil_sson105  0x809
#define gil_sson106  0x80a
#define gil_sson107  0x80b
#define gil_sson108  0x80c
#define gil_sson109  0x80d
#define gil_sson110  0x80e
#define gil_sson111  0x80f
#define gil_sson112  0x810
#define gil_sson113  0x811
#define gil_sson114  0x812
#define gil_sson115  0x813
#define gil_sson116  0x814
#define gil_sson117  0x815
#define gil_sson118  0x816
#define gil_sson119  0x817
#define gil_sson120  0x818
#define gil_sson121  0x819
#define gil_sson122  0x81a
#define gil_sson123  0x81b
#define gil_sson124  0x81c
#define gil_sson125  0x81d
#define gil_sson126  0x81e
#define gil_sson127  0x81f
#define gil_sson128  0x820
#define gil_sson129  0x821
#define gil_sson130  0x822
#define gil_sson131  0x823
#define gil_sson132  0x824
#define gil_sson133  0x825
#define gil_sson134  0x826
#define gil_sson135  0x827
#define gil_sson136  0x828
#define gil_sson137  0x829
#define gil_sson138  0x82a
#define gil_sson139  0x82b
#define gil_sson140  0x82c
#define gil_sson141  0x82d
#define gil_sson142  0x82e
#define gil_sson143  0x82f
#define gil_sson144  0x830
#define gil_sson145  0x831
#define gil_sson146  0x832
#define gil_sson147  0x833
#define gil_sson148  0x834
#define gil_sson149  0x835
#define gil_sson150  0x836
#define gil_sson151  0x837
#define gil_sson152  0x838
#define gil_sson153  0x839
#define gil_sson154  0x83a
#define gil_sson155  0x83b
#define gil_sson156  0x83c
#define gil_sson157  0x83d
#define gil_sson158  0x83e
#define gil_sson159  0x83f
#define gil_sson160  0x840
#define gil_sson161  0x841
#define gil_sson162  0x842
#define gil_sson163  0x843
#define gil_sson164  0x844
#define gil_sson165  0x845
#define gil_sson166  0x846
#define gil_sson167  0x847
#define gil_sson168  0x848
#define gil_sson169  0x849
#define gil_sson170  0x84a
#define gil_sson171  0x84b
#define gil_sson172  0x84c
#define gil_sson173  0x84d
#define gil_sson174  0x84e
#define gil_sson175  0x84f
#define gil_sson176  0x850
#define gil_sson177  0x851
#define gil_sson178  0x852
#define gil_sson179  0x853
#define gil_sson180  0x854
#define gil_sson181  0x855
                 
#undef  IEndAddr
#define IEndAddr     0x856  /* Ende des benutzten Adressraums    */ 

