/*.SM.***************************************************************************
*   B&R Version
*
*       MODUL-NAME:
*     ISCOSBIT.H
*
*       BESCHREIBUNG:
*     <Beschreibung>
*
*       UMGEBUNG:
*               Zielrechner         : Industrie-PC
*     Entwicklungsrechner : Industrie-PC
*     šbersetzer          : C-86
*     Optionen            : -keine-
*
*
*  VERSION:
*               VERSION   :  1.0                                                        DATUM   :
*               AUTOR(EN) :                      TELEFON :
*
*
*   HISTORY:
*     05.12.89 -SF-     - Neue Struktur der Include-Files eingebaut
*     05.06.90 -TSchw   - Bit XMSUZER eingebaut anstelle von Bit XBX3C9
*     05.07.90 -TSchw   - Bit XMEXTSI eingebaut anstelle von Bit XBX3BD
*     12.07.90 -TSchw-  - Bits XBX440 - XBX46f eingebaut
*     31.07.90 -JG-     - Abgleich der Bits
*     28.09.90 -SF-     - XEZ2E zu XDENTLU umbenannt
*     17.12.90 -TSchw-  - XDEND geloescht, da unbenutzt und doppelt da
*                       - XBX3C0 bis XBX3C4 ersetzt durch Bits
*                         XDSUSEI, XDRADS1, XDEXRS, XMSIGEX, XMSSZSP,
*                         dabei wurden die ersten drei Bits verschoben von
*                         XBX369,  XBX367,  XBX36A
*     18.02.91 -TSchw-  - XFKZAUS eingefuegt
*     04.03.91 -TSchw-  - Bits 545 bis 560 eingefuegt
*     13.04.91 -MB-     - Folgende Bits definiert:                  
*                         msum21 - msum25                           
*                         mtum21 - mtum26                           
*                         mpum21 - mpum25                           
*                         fa1ruh, fa2ruh, fe5_1
*     06.06.91 -TSchw-  - XBX367 umbenannt in XDSCHSP (lt. Gehring/Hueglin)
*     24.06.91 -TSchw-  - XBX369 umbenannt in XDSCHS2 (lt. Bockstahler)
*     26.06.91 -TSchw-  - XBX469 -> XFH469, XBX46A -> XFH46A
*     26.08.91 -TSchw-  - XBX468 -> XFPFAHR
*     18.11.91 -TSchw-  Mangel 205: XBX355 -> XBLUFT, XBX46B -> XFDIT
*     19.11.91 -PR-     - Zusaetzliche Bits fuer 10-Stufen-Verfahren eingefuegt
*     11.12.91 -TSchw-  Mangel 178: XBX36A -> XDOPT
*     05.03.92 -TSchw-  XBX2F4 -> XDAGR14, XBX2F5 -> XDAGR24
*     20.08.92 -TSchw-  MIQT 213: XBX3C5 -> XDWHTAB, XBX36F -> XFWHTAB,
*                       XBX3E0 -> XMABSWH
*     08.09.92 -TSchw-  MIQT282: XBX46C -> XFP1W1, XBX46D -> XFP1W2
*     08.09.92 -TSchw-  XMAGG2e eingefuegt wg. Testbericht FM/2Farben 
*                       vom 1.9.92 von Herrn Rietsche, abgesprochen 
*                       mit Herrn Bocksthaler
*     11.09.92 -TSchw-  XDPUMP -> XDNENTN, Forderung Feige/Bit lt. Schiller
*     02.02.93 -TSchw-  XBX45E -> XFSPMAX1, XBX45F -> XFSPMAX2
* 
*     17.06.93 -MBa-     von COMMON uebernommen und angepasst  
*
*     17.02.94 -TSchw-  IWZM_HANF neu eingefuegt
*     22.02.94 -PR-     Bits fuer Qualitaetskontrolle und 
*                       Selektierweiche eingefuegt
*     31.05.94 -MBa-    Bits fuer Heizungsdownload eingefuegt
*     26.07.95 -HAns-   XDWAGPS und XDWAGRF eingefuegt
*                       und XDHVWAL herausgenommen
*     27.07.95 -HAns-   XFK_DRS5_F2, XFK_DRSB707, XFK_DRSB708 und XF1B3
*                       eingefuegt (2 Farben).
*     01.08.95 -HAns-   XFK_AGM2VOR eingefuegt. 
*     14.08.95 -HAns-   XFK_PLM2AKT eingefuegt. 
*     17.08.95 -HAns-   IFORCE600 - IFORCE61F, IFORCE700 - IFORCE71F und
*                       IFORCE800 - IFORCE81F eingefuegt
*     22.08.95 -HAns-   XFSCHWE2 eingefuegt.
*     31.08.95 -HAns-   XIQSONBIT0 bis XIQSONBIT9 eingefuegt   
*     15.01.96 -HAns-   XDLAGR3,4 und XDDUES3,4 eingefuegt
*     25.01.96 -HAns-   XDWSP03 und XDWSP04 eingefuegt
*     26.01.96 -HAns-   XMSUM31 bis XDSCHW4 eingefuegt
*     09.02.96 -HAns-   XFK_FHMIN und XFK_FHMAX eingefuegt.
*     12.02.96 -HAns-   XSNM_ERHNM2-4 eingefuegt.
*                       XFAGSICH3 + 4, XFK_DRS5_F3+4, XFTDOS3+4, XFDOS3+4,
*                       XFK_PLM3AKT, XFK_PLM4AKT, XFSCHWE3+4, XFA3RUH, 
*                       XFA4RUH, XFAGSICH3+4, XFWEG12-4 eingefuegt.
*     13.02.96 -HAns-   XFK_DRB7208 und XFK_DRB7308 eingefuegt.
*                       XFK_AGM3VOR und XFK_AGM4VOR eingefuegt.
*     12.03.96 -HAns-   IFORCE900 - IFORCE91F, IFORCE3600 - IFORCE361F und
*                       IFORCE3900 - IFORCE391F eingefuegt
*     25.04.96 -HAns-   XFK_GK_AUFN und XFK_SN_AUFN eingefuegt.
*     07.05.96 -HAns-   XFK_POL0MM eingefuegt.
*     08.05.96 -HAns-   XFK_PLIV2AK eingefuegt.
*     25.07.96 -HAns-   XFTEMAB2 und XFNSEK2 eingefuegt.
*     13-09-96 -PR-     ISCOS-Bit-Nummern fuer frei progr.bare Kernzuege
*                                                               (IKEEINAUS).
*     06.12.96 -HAns-   XFTEMAB3,4 und XFNSEK3,4 eingefuegt.
*                       XFK_PLIV3AK und XFK_PLIV4AK eingefuegt.
*     19.12.96 -HAns-   XDOSFORCE01 - XDOSFORCE32 eingefuegt.
*     09.01.97 -TSchw-  Optionsbits GIL_OPTBIT.. und GIL_ISTBIT
*                       fuer Gillette eingefuegt
*     13.01.97 -TSchw-  Optionsbits GIL_OPTBIT16 - 31 eingefuegt
*     16.01.97 -HAns-   Fehlerbits XFK_WTABGEL, XFK_SPSDIAG und XFK_NOWZBEW
*                       eingefuegt.
*     17.01.97 -TSchw-  Sonderbits GIL_ISTBIT16 - 48 eingefuegt
*     05.02.97 -HAns-   Fehlerbits XFK_AWSFULL und XFK_AWS99F eingefuegt.
*     13.02.97 -HAns-   XOPTION_DV7 eingefuegt.
*     05.03.97 -HAns-   XFK_PMMIN und XPLS_RAMPE eingefuegt.
*     06.03.97 -HAns-   XPLS_RAMPE2 bis 4 eingefuegt.
*     21.04.97 -HAns-   XERRXB8, XFK_KEPOS1E bis XFK_KE_MOT und XFK_KE_OEL
*                       eingefuegt, da in Elektra V1 vorhanden.
*                       XFK_FSSAKT bis XFK_SCHUZ0 eingefuegt.
*     29.04.97 -GhG-    XFK_GKSCHM eingefuegt.
*     23.05.97 -GhG-    XSLD_MAXKR Not ™ffnung Kniehebel ein=1 aus=0
*                       nach Angabe von Herrn Bockstahler eingefuegt
*     18.06.97 -HAns-   XPOMFOERDER als Freigabebit fuer Seite 72.0 eingefuegt.
*     04.08.97 -GhG-    XFK_EDKALIB FK: Bitte Einspritzdruck kalibrieren, eingefuegt
*     27.10.97 -HAns-   XOPMF_PACK und XOPMFP_PACK fuer Fast- und FP Package
*                       eingefuegt.
*     03.12.97 -HAns-   XDOSFORCE01 bis XDOSFORCE32 herausgenommen, da nie benutzt
*                       und durch die neue freiauswaehlbare Diagnoseseite ersetzt
*                       wird.
*     18.06.98 -GhG-    ISNM_ERHNM2,  XFK_SNWECH2, XFK_IR2WEG3,
*                       XFK_IR2WEG1, XFK_AGM_TU2, XFK_SNIKOK2, XFK_AGMLER2, XFK_PLMLER2,
*                       XFK_SPMLER2, XFK_PLUTTI2, XFK_SEP_OF2, XFK_ZHTMPK2,
*                       XFK_SN_AUF2, XFK_SPKRAF2
*
*                       Fuer CD-Maschinen eingefuehrt:
*                       XFK_EXTNINI, XFK_EXTDAT, XFK_EXTEMP, XFK_CDWBLK, 
*                       XFK_CDHGNE, XFK_CDHGNV, XFK_CDHGNCD, XFK_CDHGNAG,
*                       XFK_CDFHGN, XFK_CDMWECH  
*                        
*     30.06.98 -HAns-   Erweiterungen fuer die Elektra 2f-Maschinen:
*                       XFK_IR2DREH, XFK_DR3ERR, XFK_PLSSEN2,
*                       XFK_AGM_VO2, XFK_PLM_AK2, XFK_SPREFE2, XFK_AGMSPO2 
*                       XFK_SPMSPO2, XFK_AG_VER2, XFK_SPRFER2, XFK_AGMLWR2 
*                       XFK_PLMLWR2, XFK_SPMLWR2, XFK_DR3TEMP
*     03.07.98 -HAns-   XFK_DR3FRG eingefuegt.
*     21.07.98 -HAns-   XFK_AGE_TU2 eingefuegt.
*     25.11.98 -HAns-   XWDMPENDLAG bis XWZA_CHKFSS eingefuegt.
*                       XFK_DTNREF bis XFK_DTBLOCK eingefuegt.
*                       XOP_WENDEN bis XOP_WKZAPV eingefuegt.
*     03.03.99 -HAns-   XUP_SPSTEXT eingefuegt.
*     31.03.99 -GhG-    MSSPINOK   Komunikationsbit fuer Anzahl geschmierte Nippel S.15 z.3
*                       MSGELEOK   Komunikationsbit fuer Anzahl geschmierte Nippel S.15 z.7 
*                       eingefuehrt
*     13.09.99 -JG-     XFK_AG2_Vor eingefuegt
*     18.01.00 -HAns-   XFMOTS2 eingefuegt.
*     11.02.00 -GhG-    IFK_SPSTELL "Spritzeinheit nicht in Stellung" eingefuegt
*     15.02.00 -GhG-    XFMOT132    "Motor 2 nicht im Dreieckbetrieb" eingefuegt
*     01.02.00 -HAns-   Bits fuer 5/6 Farbmaschinen eingetragen.
*     02.03.00 -HAns-   XFK_AWM1TUR und XFK_SGM1SS eingefuegt.    
*     15.03.00 -HAns-   XSEABGLST1 bis XSEABGLRS6 aufgenommen.
*     18.05.00 -HAns-   XOP_BEWPLAS eingefuegt.
*     07.08.00 -HAns-   XFK_SGM_BEW, XSLM_ENTL, IOM_AOIQT und OPM_PARAL vom NEW-IQT aufgenommen.
*                       XOB_AWS1ZUR, XFK_IOE_D1 bis D4, XSPS_OPTION1 bis 16 vom NEW-IQT
*                       aufgenommen und define-maessig verschoben.
*     11.08.00  -GhG-   Freigabebits fuer Viper eingefuegt
*                       XQUM_IQTFRD  71.0 SPS-Freigabebit Foerderband        
*                       XQUM_IQT720  72.0 SPS-Freigabebit Qualitaetskontrolle
*                       XQUM_IQT721  72.1 SPS-Freigabebit Selektierweiche    
*     02.10.00 -HAns-   XRDM_CARD eingefuegt.                   
*     09.10.00 -HAns-   XSEM_RAMPE eingefuegt.
*     19.10.00 -HAns-   XFMOT133,XFMOTS3,XFOELN2 und IFK_OELFIL3 eingefuegt.
*                       XFWEG22 bis XFWEG44 eingefuegt.
*     30.11.00 -HAns-   XSEM_RAMPE1,2,3,4 eingefuegt.
*     06.12.00 -HAnx-   XUPMAXPLCVL eingefuegt.#
*     12.12.00 -HAns-   XHEM2START bis XHZ2MXSTDT eingefuegt.
*     02.02.01 -GhG-    XFK_WS  Fehlerbit Mechanische Schlie~sperre   eingefuegt
*     15.03.01 -GhG-    XFK_XSM_ANF, XFK_XSM_AN2, XFK_SERINI, XFK_SERCOM, XFK_SEREXT
*                       und XFK_SERPRO eingefuegt
*     28.03.01 -GhG-    XOPM_IQT350, XOPM_IQT399 und XHXSNECHO eingefuegt
*     17.07.01 -HA-     XOPM_IQT710 bis XFK_AWSCHL eingefuegt.
*     26.09.01 -HA-     XFK_SGM2SS bis XFK_SG_QUIT eingefuegt.
*     27.09.01 -HA-     XFK_PNEUMES und XFK_AGENDL eingefuegt.
*     10.10.01 -HA-     XSESCHWENK1 bis 5 eingefuegt.
*     11.10.01 -HA-     XZSMDAUERB und ZSMDBFILPU eingefuegt.
*     11.10.01 -GhG-    XOPM_REGP2 eingefuegt
*     16.10.01 -HA-     XFK_SGTASTE eingefuegt
*     29.10.01 -HA-     XMSUM1A bis XMPUM1C eingefuegt (12 Einspritzstufen).
*     12.11.01 -HA-     XFK_KLEMT2, XFK_NC24V_1, XFK_NC24V_2 eingefuegt.
*     21.11.01 -HA-     XFK_B4068 und XFK_B4069 eingefuegt.
*     26.11.01 -HA-     XSLM_S1560 bis XSLM_NOHOLM eingefuegt.
*     28.11.01 -HA-     XOPMMMPPACK fuer MMP-Package eingefuegt.
*     29.11.01 -HA-     XFK_PLEDRIVE, XFK_PLEINIT und XFK_PLEWARN eingefuegt.
*                       XOPM_EPLAST eingefuegt.
*     06.12.01 -HA-     XSEABGLTASTE1 bis XSEABGLTASTE5 eingefuegt.
*     17.12.01 -HA-     XOPM_LUFT8 eingefuegt.
*     21.02.02 -JG-     XOPM_IQT800 eingefuegt
*     27.02.02 -HA-		XSES_PUEIN und XSES_DPBEIN eingefuegt.
*                       XFK_SEUEBWA eingefuegt.
*     19.03.02 -JG-     XSNECHO_2 eingefügt
*     21.03.02 -HA-     XFK_AGE2TUR eingefuegt.
*     04.04.02 -HA-     IOM_DIOIQT eingefuegt.
*     08.04.02 -HA-     XFK_NOABGLP eingefuegt.
*	  11.04.02 -JG-		XOM_AWPZUR eingefuegt.
*     16.04.02 -HA-     XFK_AG_AUFN eingefuegt.
*     22.04.02 -HA-     GIL_ISTBIT48 - 63 eingefuegt.
*     14.05.02 -HA-     XFK_PLETEMP, XFK_PLEPOWER und XFK_MOEOSHZ eingefuegt
*     26.05.02 -HA-     XFK_SL_QSTP bis XFK_SP_QSTP eingefuegt.
*     27.05.02 -HA-     XFK_ZSCHMIE eingefuegt.
*     29.05.02 -HA-     XWZI_HAKTIV eingefuegt.
*     03.06.02 -HA-     XFK_AW_VERR, XFK_SP_VERR, XFK_PL_VERR und XFK_NDPBEGR eingefuegt.
*     12.06.02 -HA-     XOPM_AIRPR, XOPM_APPROP, XOPM_APIP, XFK_APEAKTIV, XFK_APSTOER und XFK_APPESYST eingefuegt.
*     13.06.02 -HA-     XOPM_KARTON und XFK_KARTON1 eingefuegt.
*     17.06.02 -HA-     XFK_SNBLOCK eingefuegt.
*     19.06.02 -HA-     XFK_DR4ERR eingefuegt.
*     25.06.02 -HA-     XMOM_MOTON eingefuegt.
*     11.07.02 -HA-     XFK_SE1WEGM, XFK_SE1NACT, XFK_SE1WEGM und XFK_SE1NACT eingefuegt
*     13.08.02 -HA-     XFK_SE3WEGM bis XFK_SE6NACT eingefuegt.
*                       XSEABGLTASTE6 und XSEM_RAMPE6 eingefuegt.
*     27.08.02 -HA-     XFK_SG_QERR eingefuegt.
*     02.10.02 -HA-     XOP_WKZAUSW2 und XWZA2CHKVOR bis XFK_WZA2EPR eingefuegt.
*     20.11.02 -HA-     Fehlerbits XFK_TSTAGG2 bis XFK_WSWTDF eingefuegt.
*     06.12.02 -HA-     XSLS_ERHKRP eingefuegt.
*     22.01.03 -HA-     XOPS_FSSBLK und XOPM_FSSEND eingefuegt.
*     19.02.03 -HA-     XFK_DRB4409 und XOB_ERHSLKR eingefuegt.
*     12.03.03 -HA-     XOP_CANWINK und XFK_CANWINK eingefuegt.
*     05.06.03 -HA-     XOPM_AGBIRK, XOPM_SLSENS, XFK_SLVERR1 bis XFK_SLVERR3 und XFK_CABTEMP eingefuegt.
*     23.06.03 -HA-     XAGM_NOBIRK eingefuegt.
*     08.07.03 -HA-     XFK_DRB7001, 7003, 7101 und XFK_DRB7103 eingefuegt.
*     24.07.03 -HA-     XMSUM26 bis XMPUM2B eingefuegt.
*     03.09.03 -HA-     XNDS_DRBEG2 eingefuegt.
*
*                       
*       BEMERKUNGEN:         
*
*
* ---------------------------------------------------------------------------
*
*       EXPORTSCHNITTSTELLE:
*
*       FUNKTIONEN:
*               <Funktionsname>         - Kurze Beschreibung
*
*
*       DATENTYPEN:
*               <Typname>                               - Kurze Beschreibung
*
*
*       VARIABLEN:
*               <Variablenname>         - Kurze Beschreibung
*
*
*
**.EM.**********************************************************************/



#ifndef _iscosbit
#define _iscosbit

/* ------------------------------------------------------------------------- *
 |  Definitons fur die Register(Bit-)nummern der ISCOS-Bits                  |
 |  ISCOS-Bitnummern bewegen sich im Bereich zwischen 0 und 1499             |
 * ------------------------------------------------------------------------- */


#define XDDUMMI        0
#define XDDUMM2        1
#define XDRUK11        2
#define XDRUK12        3
#define XDLUF11        4
#define XDLUF12        5
#define XDLUF13        6
#define XDLUF14        7
#define XDLUF21        8
#define XDLUF22        9
#define XDLUF23       10
#define XDLUF24       11
#define XDLUF31       12
#define XDLUF32       13
#define XDLUF33       14
#define XDLUF34       15
#define XDLUF41       16
#define XDLUF42       17
#define XDLUF43       18
#define XDLUF44       19
#define XDKZON        20
#define XK1EION       21
#define XK1AUON       22
#define XK2EION       23
#define XK2AUON       24
#define XK1EPAR       25
#define XK1APAR       26
#define XK2EPAR       27
#define XK2APAR       28
#define XDAGR11       29
#define XDAGR12       30
#define XDAGR13       31
#define XDWSP01       32
#define XDWSP02       33
#define XDWSP12       34
#define XDWSPPS       35
#define XDWSPRF       36
#define XIQTSL1       37
#define XMKFCHG       38
#define XENLIN        39
#define XENPRQD       40
#define XMIHEIE       41
#define XMIMOTE       42
#define XMIEXT1       43
#define XMIEXT2       44
#define IROM_TYPE     45
#define IROM_AUSGRF   46
#define XBXSOLL       47
#define IROM_AUSHUB   48
#define IROM_BCAXIS   49
#define IROM_TCONTR   50
#define IROM_VAKUUM   51
#define IROM_ZANGE    52
#define IROM_SONDANG  53
#define IROM_SONDSCH  54
#define IROM_AN       55
#define XEP15         56
#define XEP67         57
#define XEP68         58
#define XEP69         59
#define XEP22         60
#define ISNM_ERHNM    61
#define IDIM_INIT     62
#define IDIM_CLEAR    63
#define XEZ300        64
#define XEZ308        65
#define XEZ542        66
#define XEZMASS       67
#define XEZ512        68
#define XEZWECO       69
#define XEZ143        70
#define XEZ144        71
#define XEZ476        72
#define XEZ549        73
#define XEZN549       74
#define XEZHASC       75
#define XEZ4B5        76
#define XEZ1D         77
#define XEZ1E         78
#define XEMACOD       79
#define XEZ20         80
#define XEZ21         81
#define XEZ22         82
#define XEZ23         83
#define XEZ24         84
#define XEZ25         85
#define XEZ26         86
#define XEZ27         87
#define XEZ28         88
#define XMIHEIA       89
#define XMIMOTA       90
#define XMIEX1A       91
#define XMIEX2A       92
#define XDGUMMI       93
#define XDENTLU       94
#define XDSCHWE       95
#define XDHVWAL       96
#define XDRUK21       97
#define XDRUK22       98
#define XBX2F3        99
#define XDAGR14      100
#define XDAGR24      101
#define XMSDRMX      102
#define XMASWNP      103
#define XZSVERR      104
#define XEBSDR       105
#define XSNRDOS      106
#define XMS10SY      107
#define XD4B5        108
#define XMTOLUE      109
#define XMTOMAX      110
#define XBX2FF       111
#define XBXWE1V      112
#define XBXWE1R      113
#define XBXWE2V      114
#define XBXWE2R      115
#define XBXWE3V      116
#define XBXWE3R      117
#define XBXWE4V      118
#define XBXWE4R      119
#define XBV1Y1       120
#define XBS1Y1       121
#define XBW1Y2       122
#define XBW1Y3       123
#define XBP1Y4       124
#define XBV1Y5       125
#define XBF1Y6       126
#define XBXDOS1      127
#define XBXSPR1      128
#define XBVA1Y5      129
#define XBVA2Y6      130
#define XBXSPR3      131
#define XBXDOS2      132
#define XBLUFT       133
#define XBX356       134
#define XBSTELL      135
#define XBSCHUS      136
#define XBBSON       137
#define XBXCOPY      138
#define XBBS66       139
#define XBBS67       140
#define XBBS69       141
#define XBXNWAL      142
#define XBXINI       143
#define XDINART      144
#define XDZYKLU      145
#define XDDOSU1      146
#define XDTOL1       147
#define XDNENTN      148
#define XDMAUS       149
#define XDOELHZ      150
#define XDSCHSP      151
#define XDRADS2      152
#define XDSCHS2      153
#define XDOPT        154
#define XDANF        155
#define XDLAGER      156
#define XDDUESE      157
#define XDAUSWR      158
#define XDLICHT      159
#define XDHOEHE      160
#define XDKEINZ      161
#define XDKAUSZ      162
#define XDK1EID      163
#define XDK2EID      164
#define XDK1AUD      165
#define XDK2AUD      166
#define XDNFEHL      167
#define XDFIN        168
#define XDSMIER      169
#define XDKERN       170
#define XDNSEXT      171
#define XDTEMAB      172
#define XDRUEK       173
#define XDAGGR       174
#define XDNNIDR      175
#define XDOEKRA      176
#define XDNAUSW      177
#define XDTAUS1      178
#define XDTAUS2      179
#define XDLUF1       180
#define XDLUF2       181
#define XDLUF3       182
#define XDLUF4       183
#define XDKEI2Z      184
#define XDKAU2Z      185
#define XDVWS1       186
#define XDVWS2       187
#define XDVWS3       188
#define XDVWS4       189
#define XDVWS5       190
#define XDSWP1       191
#define XDSWP2       192
#define XDSWP3       193
#define XDSWP4       194
#define XDSWP5       195
#define XDTZ1        196
#define XDTZ2        197
#define XDTZ3        198
#define XDTZ4        199
#define XDTZ5        200
#define XDINTR1      201
#define XDDSRAU      202
#define XDPSRAU      203
#define XDUSRAU      204
#define XBX39D       205
#define XBX39E       206
#define XENSDTR      207
#define XDSPSPR      208
#define XDPLAFO      209
#define IY9008SOLL   210
#define IY90081SOLL  211
#define IY9016SOLL   212
#define IY9017SOLL   213
#define IY9009SOLL   214
#define IY9025SOLL   215
#define IY90251SOLL  216
#define IY9026SOLL   217
#define XMSFAUC      218
#define XMSFAUD      219
#define XMSFAUE      220
#define XIQTSL2      221
#define XIQTSL3      222
#define XIQTSL4      223
#define XMSUZER      224
#define XDDOSU2      225
#define XDTD2        226
#define XDFIN2       227
#define XDRUEK2      228
#define XDLAGR2      229
#define XDDUES2      230
#define XDINTR2      231
#define XDAGGR2      232
#define XDAGR21      233
#define XDAGR22      234
#define XDAGR23      235
#define XENKRQD      236
#define XMEXTSI      237
#define XMTIANF      238
#define XQAUNUL      239
#define XAWS_DYNPLA  240    /* Dynamische Auswerferplattensicherung S.52    */
#define XDSUSEI      241    /* Sub. Schusszaehler ruecksetzen               */
#define XDRADS1      242    /* Add. Schusszaehler ruecksetzen               */
#define XDEXRS       243    /* Externes Signal reset neustart               */
#define XMSIGEX      244    /* Merker um Signal extern zu sperren           */
#define XMSSZSP      245    /* Merker um sub. Schusszaehler zu sperren      */
#define XDWHTAB      246    /* <>-0-Bit Temp.Absenkung Werkzeugheizung      */
#define IROM_GRDST   247    /* Handlinggeraet Grundstellung angefahren      */
#define IDIM_FOR     248    /* Diagnose Seite 88.0,88.1 Force Mode erlauben */
#define IDIM_FORON   249    /* Diagnose Seite 88.0,88.1 Force Mode Sollbit  */  
#define ISPM_DOWN    250    /* Download Anforderung von der SPS */
#define XOPTEND      251
#define XMFTRKS      252
#define XQISTED      253
#define XBX3CD       254
#define XQANFA       255
#define XMASWOK      256
#define XMSUM11      257
#define XMSUM12      258
#define XMSUM13      259
#define XMSUM14      260
#define XMSUM15      261
#define XMTUM11      262
#define XMTUM12      263
#define XMTUM13      264
#define XMTUM14      265
#define XMTUM15      266
#define XMTUM16      267
#define XMPUM11      268
#define XMPUM12      269
#define XMPUM13      270
#define XMPUM14      271
#define XMPUM15      272
#define XMABSWH      273      /* Anforderung Absenktemp. Werkzeugheizung */
#define XMATD        274
#define XMEINR       275
#define XMHAND       276
#define XMHALB       277
#define XMAUTO       278
#define XMMOTEI      279
#define XMHZEIN      280
#define XMPRINT      281
#define XMI4B6       282
#define XMIHOEH      283
#define XMPAUSD      284
#define XMIKABS      285
#define XMIKANF      286
#define XMXPDTR      287
#define XMXSTDT      288
#define XFPFISC      289
#define XFWEG1       290
#define XFWEG2       291
#define XFWEG3       292
#define XFWEG4       293
#define XFWEG        294
#define XFPUV        295
#define XFVEN        296
#define XFTEM        297
#define XFTEM2       298
#define XFTEM3       299
#define XFMACO       300
#define XFWECO       301
#define XFOELN       302
#define XFMOTS       303
#define XFSUS        304
#define XFTNOTA      305
#define XFATUR       306
#define XFSTUR       307
#define XFDTUR       308
#define XFSKMIN      309
#define XFPUV2       310
#define XFE6         311
#define XFE27        312
#define XFKZNRF      313
#define XFTFK        314
#define XFTSDR       315
#define XFBFORM      316
#define XFE4         317
#define XFE5         318
#define XFZ4B6       319
#define XFBLE10      320
#define XFMOT13      321
#define XFOELVW      322
#define XFTNIDR      323
#define XFNFSS       324
#define XFAUSW       325
#define XFHOEHE      326
#define XF4B21       327
#define XFKERN       328
#define XFWEGF       329
#define XFHEIAU      330
#define XFSNEK       331
#define XFTDOS2      332
#define XFANFLA      333
#define XFSP1AU      334
#define XFPROD       335
#define XFTZYKL      336
#define XFT2ZYK      337
#define XFWZKLE      338
#define XFTDOS1      339
#define XFLICHT      340
#define XFOELF       341
#define XFPFET       342
#define XFLFET       343
#define XFMAUS       344
#define XFDOS        345
#define XFAUSG       346
#define XFKMOT1      347
#define XFTEMAB      348
#define XFEXSTP      349
#define XFEXGER      350
#define XFEXSON      351
#define XFDOS2       352
#define XFA2RUH      353
#define XFE4_1       354
#define XFSON2       355
#define XFSON3       356
#define XFSON4       357
#define XFSON5       358
#define XFTEM4       359
#define XFTEM5       360
#define XFTEM6       361
#define XF1WWC       362
#define XFISOLA      363
#define XFSONB       364
#define XFSONC       365
#define XFSOND       366
#define XFSONE       367
#define XFSONF       368
#define XFSONP0      369
#define XFSONP1      370
#define XFSONP2      371
#define XFSONP3      372
#define XFSONP4      373
#define XFSONP5      374
#define XFSONP6      375
#define XFSONP7      376
#define XFSONP8      377
#define XFSONP9      378
#define XFSONPA      379
#define XFSONPB      380
#define XFSONPC      381
#define XFSONPD      382
#define XFSONPE      383
#define XFSONPF      384
#define XFTKER1      385
#define XFTKER2      386
#define XFBEND1      387
#define XFBEND2      388
#define XFK1POS      389
#define XFK2POS      390
#define XFKBLK1      391
#define XFKBLK2      392
#define XFKBLAU      393
#define XBX459       394
#define XBX45a       395
#define XBX45b       396
#define XBX45c       397
#define XBX45d       398
#define XFSPMAX1     399
#define XFSPMAX2     400
#define XFSERIO      401
#define XFFUNKT      402
#define XFSTART      403
#define XFENTLU      404
#define XFSCHWE      405
#define XFE5_1       406
#define XFKZAUS      407
#define XFA1RUH      408
#define XFPFAHR      409
#define XFH469       410
#define XFH46a       411
#define XFDIT        412
#define XFP1W1       413
#define XFP1W2       414
#define XBX46e       415
#define XFWHTAB      416    /* Fehler "Temp.Absenkung Wkz-Heizung laeuft" */
#define XFFELDKL     417    /* Fehler "Feldklemmenfehler Modul              " */  
#define XFMODUL      418    /* Fehler "]berlast in einem Modul              " */  
#define XFMODTEMP    419    /* Fehler "]bertemperatur in einem Modul        " */  
#define XFIOERR      420    /* Fehler "I/O Fehler in einem Modul            " */  
#define XFCONF1      421    /* Fehler "Config: EPROM voll                   " */  
#define XFCONF2      422    /* Fehler "Config: kein RAM Speicher verf}gbar  " */  
#define XFCONF3      423    /* Fehler "Config: Default Modul nicht vorhanden" */  
#define XFCONF4      424    /* Fehler "Config: Modul erzeugt, Init ausl|sen " */  
#define XFK_PLM2AKT  425    /* Fehler "Plastifizierweg Agg.2 nicht erreicht " */
#define XFSCHWE2     426    /* Fehler "Schneckenwechsel Agg.2" */
#define XFAGSICH1    427    /* Fehler "Sicherheitssch}tz Agg. 1 defekt      " */
#define XFAGSICH2    428    /* Fehler "Sicherheitssch}tz Agg. 2 defekt      " */
#define XFK_PLIV1AK  429    /* Fehler "Schneckendrehzahlmessung Agg.1 gestoert" */
#define XF1B3        430
#define IFK_AGM_VOR  431
#define IFK_PLM_AKT  432
#define IFK_OELFIL1  433
#define IFK_OELFIL2  434
#define IFK_SGE_VEN  435
#define IFK_AWD_NUL  436
#define IFK_KEPRF    437
#define XFK_PLIV2AK  438    /* Fehler "Schneckendrehzahlmessung Agg.2 gestoert" */
#define XFTEMAB2     439    /* Fehler "Temp.Absenkung Zyl.Heizung Agg.2 laeuft" */
#define XFSNEK2      440    /* Fehler "Schneckenfreigabe Agg.2 fehlt"           */
#define XFTEMAB3     441    /* Fehler "Temp.Absenkung Zyl.Heizung Agg.3 laeuft" */
#define XFSNEK3      442    /* Fehler "Schneckenfreigabe Agg.3 fehlt"           */
#define XFTEMAB4     443    /* Fehler "Temp.Absenkung Zyl.Heizung Agg.4 laeuft" */
#define XFSNEK4      444    /* Fehler "Schneckenfreigabe Agg.4 fehlt"           */
#define XFK_PMMIN    445    /* Fehler "Minimaler Pumpendruck nicht erreicht" */
#define IFK_SPSTELL  446    /* Fehler "Spritzeinheit nicht in Stellung" */
#define XOPMMMPPACK  447    /* SPS_IQT-Option MMP-Package (MMP-Maschine)     */
#define XERRXB8      448
#define XMAGG2E      449    /* Agg. 2 mit Endschalter, bei Aufstart lesen */
#define XMSUM21      450
#define XMSUM22      451
#define XMSUM23      452
#define XMSUM24      453
#define XMSUM25      454
#define XMTUM21      455
#define XMTUM22      456
#define XMTUM23      457
#define XMTUM24      458
#define XMTUM25      459
#define XMTUM26      460
#define XMPUM21      461
#define XMPUM22      462
#define XMPUM23      463
#define XMPUM24      464
#define XMPUM25      465
#define XDWAGPS      466
#define XDWAGRF      467
#define XDSCHW2      468
#define XIQSSONBIT0  469    /* Soll-Sonderbits */
#define XIQSSONBIT1  470
#define XIQSSONBIT2  471
#define XIQSSONBIT3  472
#define XIQSSONBIT4  473
#define XIQSSONBIT5  474
#define XIQSSONBIT6  475
#define XIQSSONBIT7  476
#define XIQSSONBIT8  477
#define XIQSSONBIT9  478
#define XZYITANALYS  479
#define XSLM_SDREIN  480     /* Schliesskraft im Einrichten moeglich        */
#define XAWS_SYNAUS  481     /* Synchrones Ausstossen S.52                  */
#define XMSM_ELTEST  482     /* Synchrones Ausstossen S.52                  */
#define XWSS_PEINR   483     /* Schliesskraft im Einrichten                 */
#define XSLDPSDREIN  484     /* Schlie~druck im Einrichten anfordern        */
#define XSNM_ERHNM2  485     /* Signal-Bit erhoehtes Drehmoment fuer Agg. 2 */
#define XOPTION_DV7  486     /* Optionsbit fuer DV7 wird der SPS gemeldet   */
#define XPLS_RAMPE   487     /* Plasifizierrampe umschalten 1.Agg           */
#define XPLS_RAMPE2  488     /* Plasifizierrampe umschalten 2.Agg           */
#define XPLS_RAMPE3  489     /* Plasifizierrampe umschalten 3.Agg           */
#define XPLS_RAMPE4  490     /* Plasifizierrampe umschalten 4.Agg           */
#define XSLD_MAXKR   491     /* Not ™ffnung Kniehebel ein=1 aus=0           */ 
#define XPOMFOERDER  492  /* Freigabebit fuer Seite 71.0 Foerderband        */
#define XOPMF_PACK   493  /* Optionsbit fuer  F-Package                     */
#define XOPMFP_PACK  494  /* Optionsbit fuer  FP-Package                    */
/* ---------------- Neue Bits fuer 3 Farben ------------------------------- */
#define XDLAGR3      495
#define XDDUES3      496
#define XDWSP03      497
#define XMSUM31      498
#define XMSUM32      499
#define XMSUM33      500
#define XMSUM34      501
#define XMSUM35      502
#define XMTUM31      503
#define XMTUM32      504
#define XMTUM33      505
#define XMTUM34      506
#define XMTUM35      507
#define XMTUM36      508
#define XMPUM31      509
#define XMPUM32      510
#define XMPUM33      511
#define XMPUM34      512
#define XMPUM35      513
#define XDSCHW3      514
#define XSNM_ERHNM3  515 /* FK: Signal-Bit erhoehtes Drehmoment fuer Agg. 3 */
#define XFK_DRS5_F3  516 /* FK: Druckschalter .5-F301 oeffnet nicht         */
#define XFTDOS3      517 /* FK: Plastifizierzeit Agg.3 }berschritten        */
#define XFDOS3       518 /* FK: Plastifizierweg Aggr.3 }berschritten        */
#define XFK_PLM3AKT  519 /* FK: Plastifizierweg Aggr.3 nicht erreicht       */
/* ------------------------------------------------------------------------ */
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
#define XDSPRST      520
#define XDSTUFEN     521
#define XMTELSOL     522
#define XFSPMAX      523
/* ---------------- END_MODE_10 ------------------------------------------- */
/* ---------------- Neue Bits fuer 4 Farben ------------------------------- */
#define XDLAGR4      524
#define XDDUES4      525
#define XDWSP04      526
#define XMSUM41      527
#define XMSUM42      528
#define XMSUM43      529
#define XMSUM44      530
#define XMSUM45      531
#define XMTUM41      532
#define XMTUM42      533
#define XMTUM43      534
#define XMTUM44      535
#define XMTUM45      536
#define XMTUM46      537
#define XMPUM41      538
#define XMPUM42      539
#define XMPUM43      540
#define XMPUM44      541
#define XMPUM45      542
#define XDSCHW4      543
#define XSNM_ERHNM4  544     /* Signal-Bit erhoehtes Drehmoment fuer Agg. 4 */
/* ------------------------------------------------------------------------ */
#define XENOPT       545
#define XMRGL10      546
#define XBX4F2       547
#define XBX4F3       548
#define XBX4F4       549
#define XBX4F5       550
#define XBX4F6       551
#define XBX4F7       552
#define XBX4F8       553
#define XBX4F9       554
#define XBX4FA       555
#define XBX4FB       556
#define XBX4FC       557
#define XBX4FD       558
#define XBX4FE       559
#define XBX4FF       560
#define XMFOHOE      561
#define IY9008IST    562
#define IY90081IST   563
#define IY9016IST    564
#define IY9017IST    565
#define IY9009IST    566
#define IY9025IST    567
#define IY90251IST   568
#define IY9026IST    569
#define IY9020IST    570
#define IY9010IST    571
#define IY9014IST    572
#define IY90141IST   573
#define IY9023IST    574
#define IY9011IST    575
#define I5F1IST      576
#define IY9002IST    577
#define IY9001IST    578
#define IY90011IST   579
#define IWAS_UEBV    580
#define IWAS_UEBZ    581
#define IWAS_FSS     582
#define IFK_ROE_WS   583  /* Fehler "Start Werkzeug schlie~en vom HG fehlt"        */
#define IFK_ROE_SI   584  /* Fehler "Freigabe Werkzeugbewegung vom HG fehlt"       */ 
#define IFK_ROE_AWV  585  /* Fehler "Freigabe Auswerfer-Vorbewegung vom HG fehlt"  */ 
#define IFK_ROE_AWZ  586  /* Fehler "Freigabe Auswerfer R}ckbewegung vom HG fehlt" */ 
#define IFK_ROE_WO   587  /* Fehler "Start Werkzeug |ffnen vom HG fehlt"           */ 
#define IFK_ROFRG    588  /* Fehler "Freigabe Sollwert Werkzeug schlie~en"         */ 
#define IWZM_HANF    589
/*------------------- Qualitaetskontrolle --------------------------------*/
#define IQUSNSUB     590  /* Subtrahierender Schusszaehler unterbrechen   */
#define IQUSNEXZ     591  /* Externer Zykl.zaehler unterbrechen           */
#define IQUSNINV     592  /* Inversbetrieb                                */
/*------------------ Selektierweiche -------------------------------------*/
#define IQUS_SPRANG  593  /* Spritzling selektieren                       */
#define IQUS_INVERS  594  /* Inversbetrieb                                */
/*------------------ Heizungsoptimierung ---------------------------------*/
#define IHEM_READY   595  /* Heizungsoptimierung fertig                   */
#define IHEM_START   596  /* Start Heizungsoptimierung                    */
#define IKZM_SOND    597  /* Kernzug Sonderseite                          */
#define IHEM_ABORT   598  /* Heizungsoptimierung abbrechen                */
/*------------------------------------------------------------------------*/
#define IFK_SKM2TUR  599  /* hintere Schutztuer offen                     */
#define XFK_DRS5_F2  600  /* Druckschalter .5-F201 oeffnet nicht          */
#define XFK_DRSB707  601  /* Druckfuehler B7107 ausser Toleranz           */
#define XFK_DRSB708  602  /* Druckfuehler B7108 ausser Toleranz           */
#define XFK_AGM2VOR  603  /* Duesenanlagedruck Aggregat 2 nicht erreicht  */
/*------------------- Error-message-bits Elektra V2.00 ---------------------*/
#define XFK_AGMSPOS  604  /* FK: Aggregat 1 nicht in Position               */ 
#define XFK_SPMSPOS  605  /* FK: Schnecke 1 nicht in Position               */ 
#define XFK_FHMSPOS  606  /* FK: Werkzeugh|he nicht in Position             */ 
#define XFK_SL_VERR  607  /* FK: Werkzeug-Verriegelungsfehler               */ 
#define XFK_AG_VERR  608  /* FK: Form-Verriegelungsfehler                   */ 
#define XFK_SLMSSPN  609  /* FK: Form auf Spannhubposition fahren           */ 
#define XFK_FH_BLCK  610  /* FK: Werkzeugh|henverstellung blockiert         */ 
#define XFK_FSS_REF  611  /* FK: Wkz-Sicherungs-Referenzzyklus fehlt        */ 
#define XFK_AWRFERR  612  /* FK: Auswerfer-Referenzschalterfehler           */ 
#define XFK_SLRFERR  613  /* FK: Schliessachse-Referenzschalterfehler       */ 
#define XFK_SPRFERR  614  /* FK: Einspritzachse-Referenzschalterfehler      */ 
#define XFK_AWMLWRN  615  /* FK: Erh|hte Leistung bei Auswerferachse        */ 
#define XFK_SLMLWRN  616  /* FK: Erh|hte Leistung bei Schlie~achse          */ 
#define XFK_AGMLWRN  617  /* FK: Erh|hte Leistung bei Aggregatachse 1       */ 
#define XFK_PLMLWRN  618  /* FK: Erh|hte Leistung bei Plastifizierachse 1   */ 
#define XFK_SPMLWRN  619  /* FK: Erh|hte Leistung bei Einspritzachse 1      */ 
#define XFK_AWMLERR  620  /* FK: ]berlastung der Auswerferachse             */ 
#define XFK_SLMLERR  621  /* FK: ]berlastung der Schlie~achse               */ 
#define XFK_AGMLERR  622  /* FK: ]berlastung der Aggregatachse 1            */ 
#define XFK_PLMLERR  623  /* FK: ]berlastung der Plastifizierachse 1        */ 
#define XFK_SPMLERR  624  /* FK: ]berlastung der Einspritzachse 1           */ 
#define XFK_DR1FRG   625  /* FK: Freigabest|rung im Schlie~drive            */ 
#define XFK_DR2FRG   626  /* FK: Freigabest|rung im Spritzdrive             */ 
#define XFK_DR1TEMP  627  /* FK: Motor}bertemperatur am Schlie~drive        */ 
#define XFK_DR2TEMP  628  /* FK: Motor}bertemperatur am Spritzdrive         */ 
#define XFK_SPS      629  /* FK: Keine g}ltigen Werte in der SPS            */ 
#define XFK_EINR     630  /* FK: Einrichten bet{tigen                       */ 
#define XFK_EINRHD   631  /* FK: Einrichten oder Handbetrieb anw{hlen       */ 
#define XFK_SIE_24V  632  /* FK: Spannungsunterbrechung 24V Versorgung      */
#define XFK_IR1WEG1  633  /* FK: Weggeber der Spritzachse 1 defekt          */
#define XFK_IR1WEG2  634  /* FK: Weggeber der Form defekt                   */
#define XFK_IR1WEG3  635  /* FK: Weggeber des Aggregates 1 defekt           */
#define XFK_IR1WEG4  636  /* FK: Weggeber des Auswerfers defekt             */
#define XFK_OELNIV   637  /* FK: Oelniveau der Schmierung zu niedrig        */
#define XFK_MOEISHZ  638  /* FK: Stoerung am Motor-Sicherheitsschuetz       */
#define XFK_SIE_NOT  639  /* FK: Not-Aus-Taste betaetigt                    */
#define XFK_AWE_TUR  640  /* FK: Auswerferschutz offen                      */
#define XFK_SGM_TUR  641  /* FK: Formschutztuere nicht geschlossen          */
#define XFK_AGE_TUR  642  /* FK: Duesenschutz nicht geschlossen             */
#define XFK_SLSDR80  643  /* FK: Schliesskraft ausserhalb Toleranz          */
#define XFK_DRUTAUF  644  /* FK: Schliessdruck Ueberwachungszeit            */
#define XFK_OELDR1   645  /* FK: Druckschalterfehler Gelenksystemschmierung */
#define XFK_OELDR2   646  /* FK: Druckschalterfehler Getriebeumlaufschmierung*/
#define XFK_KESNNR   647  /* FK: Kernzugnummer falsch                       */
#define XFK_DRUTAB   648  /* FK: Schliessdruck Ueberwachungszeit            */
#define XFK_SLM_STP  649  /* FK: Werkzeugbewegung blockiert                 */
#define XFK_AWE_ZUR  650  /* FK: Auswerferplattensicherung                  */
#define XFK_MOE_EIN  651  /* FK: Motoren nicht eingeschaltet                */
#define XFK_WSUTFSS  652  /* FK: Werkzeugsicherung                          */
#define XFK_FSSMAX   653  /* FK: Werkzeugsicherungswiederholung             */
#define XFK_AWSSZUR  654  /* FK: Auswerfer nicht in hinterer Lage           */
#define XFK_WSSSZU   655  /* FK: Werkzeughoehe nicht eingestellt            */
#define XFK_SLSSAUF  656  /* FK: Werkzeug nicht in Position                 */
#define XFK_KEPOS    657  /* FK: Kernposition fehlerhaft                    */
#define XFK_OPGSNO   658  /* FK: Wegpunkt S.67 falsch                       */
#define XFK_ZHA_AUS  659  /* FK: Zylinderheizungen nicht eingeschaltet      */
#define XFK_SNIKOK   660  /* FK: Schneckenfreigabe fehlt                    */
#define XFK_WHM_ANF  661  /* FK: Zylinderheizungen nicht eingeschaltet      */
#define XFK_QUM_TOL  662  /* FK: Produkt ausserhalb der Toleranz            */
#define XFK_ZYUTTI1  663  /* FK: Zykluszeit ueberschritten                  */
#define XFK_ZYUTTI2  664  /* FK: Zykluszeit zum 2. Mal ueberschritten       */
#define XFK_PLUTTIM  665  /* FK: Plast.-Zeit Agg. 1 ueberschritten          */
#define XFK_SIE_LSW  666  /* FK: Lichtschranke/Ausfallwaage                 */
#define XFK_OELSAUG  667  /* FK: Filterstoerung des Schmiersystems          */
#define XFK_MASCHAB  668  /* FK: Automatische Maschinenabschaltung laeuft   */
#define XFK_PLSSEND  669  /* FK: Plastifizierweg 1 ueberschritten           */
#define XFK_ZHM_ABS  670  /* FK: Temp.Absenkung Zyl.Heizung laeuft          */
#define XFK_ZYE_EXT  671  /* FK: Zyklusstop extern                          */
#define XFK_OPM_EXT  672  /* FK: Stoerung externes Geraet                   */
#define XFK_OPM_SON  673  /* FK: Sonderfehlermeldung                        */
#define XFK_SGMVTUR  674  /* FK: vordere Formschutztuere nicht geschlossen  */
#define XFK_SGMHTUR  675  /* FK: hintere Formschutztuere nicht geschlossen  */
#define XFK_AGM_VOR  676  /* FK: D}senanlagedruck nicht erreicht            */
#define XFK_PLM_AKT  677  /* FK: Plastifizierweg nicht erreicht             */
#define XFK_SLREFES  678  /* FK: Formweg-Referenzpunkt fehlt                */
#define XFK_AWREFES  679  /* FK: Auswerfer-Referenzpunkt fehlt              */
#define XFK_SPREFES  680  /* FK: Schnecken-Referenzpunkt fehlt              */
#define XFK_WHA_AUS  681  /* FK: Werkzeugheizung nicht eingeschaltet        */
#define XFK_WHIKOK   682  /* FK: Wkz Heizung Freigabe fehlt                 */
#define XFK_OELTEMP  683  /* FK: Temp. im Elektroschrank ist zu hoch        */
#define XFK_AGM_TUR  684  /* FK: Stoerung der Duesenschutztuer              */
#define XFK_SGM1TUR  685  /* FK: Stoerung der Formschutztuer                */
#define XFK_SL_DMS   686  /* FK: Schliesskraftsenor pruefen                 */
#define XFK_SOND     687  /* FK: Sonderbit                                  */
#define XFK_SONE     688  /* FK: Sonderbit                                  */
#define XFK_SONF     689  /* FK: Sonderbit                                  */
#define XFK_SONP0    690  /* FK: Sonderbit                                  */
#define XFK_SONP1    691  /* FK: Sonderbit                                  */
#define XFK_SONP2    692  /* FK: Sonderbit                                  */
#define XFK_SONP3    693  /* FK: Sonderbit                                  */
#define XFK_SONP4    694  /* FK: Sonderbit                                  */
#define XFK_SONP5    695  /* FK: Sonderbit                                  */
#define XFK_SONP6    696  /* FK: Sonderbit                                  */
#define XFK_SONP7    697  /* FK: Sonderbit                                  */
#define XFK_SONP8    698  /* FK: Sonderbit                                  */
#define XFK_SONP9    699  /* FK: Sonderbit                                  */
#define XFK_SONPA    700  /* FK: Sonderbit                                  */
#define XFK_SONPB    701  /* FK: Sonderbit                                  */
#define XFK_SONPC    702  /* FK: Sonderbit                                  */
#define XFK_SONPD    703  /* FK: Sonderbit                                  */
#define XFK_AWD_NUL  704  /* FK: Auswerfernullpunkt unterschritten          */
#define XFK_KEPRF    705  /* FK: Kernposition }berpr}fen                    */
#define XFK_KEKAKT1  706  /* FK: Kern 1 Bewegung nicht ausgefuehrt          */
#define XFK_KEKAKT2  707  /* FK: Kern 2 Bewegung nicht ausgefuehrt          */
#define XFK_KEBES1   708  /* FK: Kern 1 beide Endschalter betaetigt         */
#define XFK_KEBES2   709  /* FK: Kern 2 beide Endschalter betaetigt         */
#define XFK_KEFPOS1  710  /* FK: Kern 1 nicht in richtiger Stellung         */
#define XFK_KEFPOS2  711  /* FK: Kern 2 nicht in richtiger Stellung         */
#define XFK_AWBLKE1  712  /* FK: Auswerfer blockiert Kern 1                 */
#define XFK_AWBLKE2  713  /* FK: Auswerfer blockiert Kern 2                 */
#define XFK_KEBLAW   714  /* FK: Kerne blockieren Auswerfer                 */
#define XFK_ZYE_LOS  715  /* FK: Bitte Starttaste betaetigen                */ 
#define XFK_SNWECH   716  /* FK: Schneckenwechsel                           */
#define XFK_KEAUS    717  /* FK: Kernzug Seite 61 Zeile 2 ausschalten       */
#define XFK_WHM_ABS  718  /* FK: Werkzeug Temperaturabsenkung laeuft        */
#define XFK_FELDKL   719  /* FK: Feldklemmenfehler                          */
#define XFK_DOLOAD   720  /* FK: Ueberlast Modul                            */
#define XFK_DOTEMP   721  /* FK: Uebertemperatur                            */
#define XFK_IR1_IO   722  /* FK: I/O Error                                  */
#define XFK_IR1PAR   723  /* FK: Config: EPROM voll                         */
#define XFK_IR2PAR   724  /* FK: Config: kein RAM Speicher verfuegbar       */
#define XFK_ROE_WS   725  /* FK: Start Werkzeug schlie~en vom HG fehlt      */     
#define XFK_ROE_SI   726  /* FK: Freigabe Werkzeugbewegung vom HG fehlt     */ 
#define XFK_ROE_AWV  727  /* FK: Freigabe Auswerfer-Vorbewegung vom HG fehlt*/ 
#define XFK_ROE_AWZ  728  /* FK: Freigabe Auswerfer R}ckbewegung vom HG fehlt*/ 
#define XFK_ROE_WO   729  /* FK: Start Werkzeug |ffnen vom HG fehlt         */ 
#define XFK_ROFRG    730  /* FK: Freigabe Sollwert Werkzeug schlie~en       */ 
#define XFK_SGM2TUR  731  /* FK: hintere Schutztuer offen                   */
#define XFK_MOAHPTS  732  /* FK: Motoren ausschalten - dann Hauptschalter   */
#define XFK_MOA_NOT  733  /* FK: Motoren ausgeschaltet nach NOT-STOP        */
#define XFK_HZA_NOT  734  /* FK: Heizung ausgeschaltet nach NOT-STOP        */
#define XFK_AWS_WO   735  /* FK: Ausw.- Hub oder \\ffnungsweite falsch      */
#define XFK_TEMPFBR  736  /* FK: Temperaturf}hlerbruch Elektroschrank       */
#define XFK_SLKEINR  737  /* FK: Schlie~kraft im Einrichtbetrieb aktiv      */
#define XFK_REALTIM  738  /* FK: Echtzeituhr Fehler in der SPS              */
#define XFK_TSTZYKL  739  /* FK: Testzyklus aktiv                           */
#define XFK_ZHTMPKL  740  /* FK: Zylindertemperaturen unter 150 [C          */
#define XFK_GKK_OFF  741  /* FK: Gelenkkopfkraft Offset Fehler              */
#define XFK_SEP_OFF  742  /* FK: Einspritzdruck Offset Fehler               */
#define XFK_DR1ERR   743  /* FK: Stoerung im Drive der Schliesseinheit      */ 
#define XFK_DR2ERR   744  /* FK: Stoerung im Drive der Spritzeinheit        */ 
#define XFK_SPKRAFT  745  /* FK: Zu grosse Schneckenr}ckzugskraft           */
#define XFK_GK_WARN  746  /* FK: Erh|hte Reibung am Gelenksystem            */
#define XFK_GK_REIB  747  /* FK: Zu gro~e Reibung am Gelenksystem           */
#define XFK_SL_REIB  748  /* FK: Zu gro~e Reibung am Werkzeug               */
#define XFK_FHMIN    749  /* FK: Min. Werkzeugeinbauh|he unterschritten     */
#define XFK_FHMAX    750  /* FK: Max. Werkzeugeinbauh|he }berschritten      */
#define XFK_KEPOS1E  751  /* FK: Kern 1 nicht eingefahren                   */
#define XFK_KEPOS1A  752  /* FK: Kern 1 nicht ausgefahren                   */
#define XFK_KEPOS2E  753  /* FK: Kern 2 nicht eingefahren                   */
#define XFK_KEPOS2A  754  /* FK: Kern 2 nicht ausgefahren                   */
#define XFK_KE_DRV   755  /* FK: St|rung im Kernzug Drive                   */
#define XFK_KE_MOT   756  /* FK: Motor}bertermperatur Kernzug Drive         */
#define XFK_GK_AUFN  757  /* FK: Gelenkkopfkraft-Aufnehmer pr}fen           */
#define XFK_SN_AUFN  758  /* FK: Spritzkraft-Aufnehmer pr}fen               */
#define XFK_POL0MM   759  /* FK: Polster-Istwert 0 mm                       */
#define XFK_GKSCHM   760  /* FK: St|rung Gelenkschmiersystem                */
/* ---------------- END Errorbits Elektra V2.00 --------------------------- */ 
#define XFK_KE_OEL   761  /* FK: //lniveau Kernzugstation                   */
#define XFK_FSSAKT   762  /* FK: Wkz.-Sicherungs-Referenzzyklus aktiviert   */
#define XFK_TEMPTOH  763  /* FK: Erh|hte Temp. im Elektroschrank            */
#define XFK_MOEOSHZ  764  /* FK: Oelfilterpupe Ueberstromrelais ausgel|st  */
#define XFK_SCHUZ0   765  /* FK: Sub. Schu~zaehler = 0                      */
#define XFK_EDKALIB  766  /* FK: Bitte Einspritzdruck kalibrieren           */
/* ------------------------------------------------------------------------ */ 
#define XFK_AWM1TUR  767  /* FK: St|rung der Auswerferschutzt}r             */
#define XFK_SGM1SS   768  /* FK: Sicherheitssch}tz Bedienseite defekt       */
#define XFK_SGM_BEW  769  /* FK: Unerlaubte Werkzeugbewegung                */
#define XOB_AWS1ZUR  770  /* KP-Optionsbit Auswerferplattensicherung fuer SPS */
/* ------------------------------------------------------------------------ */ 
#define XFK_PLEDRIVE 771  /* FK: Plastifizierantrieb nicht betriebsbereit   */
#define XFK_PLEINIT  772  /* FK: Plastifizierantrieb Fehler Umrichter       */
#define XFK_PLEWARN  773  /* FK: Plastifizierantrieb }berlastet             */
#define XOPM_EPLAST  774  /* SPS_IQT-Option Elektrisches Plastifizieren     */
#define XOPM_LUFT8   775  /* SPS_IQT-Option 5 bis 8 Luftventil              */
/* ------------------------------------------------------------------------ */ 
#define XSES_PUEIN   776  /* Soll-Bit Spritzdruck}berwachung                */
#define XSES_DPBEIN  777  /* Soll-Bit dyn. Druckreglerbegrenzung            */
#define XFK_SEUEBWA  778  /* FK: Einspr. von Spritzdruck}berw. abgebrochen  */
#define XFK_AGE2TUR  779  /* FK: hinterer Duesenschutz nicht geschlossen    */
/* ---------------- Neue Bits fuer 3/4 Farben ----------------------------- */
#define XFK_DRS5_F4  780 /* FK: Druckschalter .5-F401 oeffnet nicht         */
#define XFTDOS4      781 /* FK: Plastifizierzeit Agg.4 }berschritten        */
#define XFDOS4       782 /* FK: Plastifizierweg Aggr.4 }berschritten        */
#define XFK_PLM4AKT  783 /* FK: Plastifizierweg Aggr.4 nicht erreicht       */
#define XFSCHWE3     784 /* FK: Schneckenwechsel Aggr.3                     */
#define XFSCHWE4     785 /* FK: Schneckenwechsel Aggr.4                     */
#define XFA3RUH      786 /* FK: Aggregat 3 nicht in hintere Lage            */
#define XFA4RUH      787 /* FK: Aggregat 4 nicht in hintere Lage            */
#define XFAGSICH3    788 /* FK: Sicherheitssch}tz Agg. 3 defekt             */
#define XFAGSICH4    789 /* FK: Sicherheitssch}tz Agg. 4 defekt             */
#define XFWEG12      790 /* FK: Wegmesssystem 3 Schnecke 2 defekt           */
#define XFWEG13      791 /* FK: Wegmesssystem 3 Schnecke 3 defekt           */
#define XFWEG14      792 /* FK: Wegmesssystem 3 Schnecke 4 defekt           */
#define XFK_DRB7208  793 /* FK: Druckfuehler B7208 ausser Toleranz          */
#define XFK_DRB7308  794 /* FK: Druckfuehler B7308 ausser Toleranz          */
#define XFK_AGM3VOR  795 /* FK: Duesenanlagedruck Aggregat 3 nicht erreicht */
#define XFK_AGM4VOR  796 /* FK: Duesenanlagedruck Aggregat 4 nicht erreicht */
#define XFK_PLIV3AK  797 /* FK: Schneckendrehzahlmessung Agg.3 gestoert     */
#define XFK_PLIV4AK  798 /* FK: Schneckendrehzahlmessung Agg.4 gestoert     */
/* ------------------------------------------------------------------------ */
#define XFK_WTABGEL  799 /* FK: Wochentagschaltuhr abgelaufen               */
#define XFK_SPSDIAG  800 /* FK: SPS in Betriebsart DIAGNOSE                 */
#define XFK_NOWZBEW  801 /* FK: Keine Werkzeugbewegung moeglich             */
#define XFK_AWS99F   802 /* FK: AWS - Speicherplatz zu 99% voll             */
#define XFK_AWSFULL  803 /* FK: AWS - Speicherplatz voll                    */
#define XOP_WENDEN   804 /* SPS-Optionsbit fuer Standard Wenden             */
#define XOP_WDGR_GS  805 /* SPS-Optionsbit fuer geregelt/gesteuertes Wenden */
#define XOP_WKZAUSW  806 /* SPS-Optionsbit fuer Werkzeugauswerfer           */
#define XOP_WKZAPV   807 /* SPS-Optionsbit fuer Auswerferdruck/geschwindigkeit */
#define XUP_SPSTEXT  808 /* Kommunikationsbit fuer SPS-Texte von SPS holen  */
#define XOP_BEWPLAS  809 /* SPS-Optionsbit fuer Parallel Plastifizieren     */
/* ---------------- Force-Bits fuer Karte 6 ------------------------------- */
#define IFORCE600    810  /* Force Bit                                    */
#define IFORCE601    811  /* Force Bit                                    */
#define IFORCE602    812  /* Force Bit                                    */
#define IFORCE603    813  /* Force Bit                                    */
#define IFORCE604    814  /* Force Bit                                    */
#define IFORCE605    815  /* Force Bit                                    */
#define IFORCE606    816  /* Force Bit                                    */
#define IFORCE607    817  /* Force Bit                                    */
#define IFORCE608    818  /* Force Bit                                    */
#define IFORCE609    819  /* Force Bit                                    */
#define IFORCE60A    820  /* Force Bit                                    */
#define IFORCE60B    821  /* Force Bit                                    */
#define IFORCE60C    822  /* Force Bit                                    */
#define IFORCE60D    823  /* Force Bit                                    */
#define IFORCE60E    824  /* Force Bit                                    */
#define IFORCE60F    825  /* Force Bit                                    */
#define IFORCE610    826  /* Force Bit                                    */
#define IFORCE611    827  /* Force Bit                                    */
#define IFORCE612    828  /* Force Bit                                    */
#define IFORCE613    829  /* Force Bit                                    */
#define IFORCE614    830  /* Force Bit                                    */
#define IFORCE615    831  /* Force Bit                                    */
#define IFORCE616    832  /* Force Bit                                    */
#define IFORCE617    833  /* Force Bit                                    */
#define IFORCE618    834  /* Force Bit                                    */
#define IFORCE619    835  /* Force Bit                                    */
#define IFORCE61A    836  /* Force Bit                                    */
#define IFORCE61B    837  /* Force Bit                                    */
#define IFORCE61C    838  /* Force Bit                                    */
#define IFORCE61D    839  /* Force Bit                                    */
#define IFORCE61E    840  /* Force Bit                                    */
#define IFORCE61F    841  /* Force Bit                                    */
/* ---------------- END Force-Bits fuer Karte 6 --------------------------- */
/* ---------------- Force-Bits fuer Karte 7 ------------------------------- */
#define IFORCE700    842  /* Force Bit                                    */
#define IFORCE701    843  /* Force Bit                                    */
#define IFORCE702    844  /* Force Bit                                    */
#define IFORCE703    845  /* Force Bit                                    */
#define IFORCE704    846  /* Force Bit                                    */
#define IFORCE705    847  /* Force Bit                                    */
#define IFORCE706    848  /* Force Bit                                    */
#define IFORCE707    849  /* Force Bit                                    */
#define IFORCE708    850  /* Force Bit                                    */
#define IFORCE709    851  /* Force Bit                                    */
#define IFORCE70A    852  /* Force Bit                                    */
#define IFORCE70B    853  /* Force Bit                                    */
#define IFORCE70C    854  /* Force Bit                                    */
#define IFORCE70D    855  /* Force Bit                                    */
#define IFORCE70E    856  /* Force Bit                                    */
#define IFORCE70F    857  /* Force Bit                                    */
#define IFORCE710    858  /* Force Bit                                    */
#define IFORCE711    859  /* Force Bit                                    */
#define IFORCE712    860  /* Force Bit                                    */
#define IFORCE713    861  /* Force Bit                                    */
#define IFORCE714    862  /* Force Bit                                    */
#define IFORCE715    863  /* Force Bit                                    */
#define IFORCE716    864  /* Force Bit                                    */
#define IFORCE717    865  /* Force Bit                                    */
#define IFORCE718    866  /* Force Bit                                    */
#define IFORCE719    867  /* Force Bit                                    */
#define IFORCE71A    868  /* Force Bit                                    */
#define IFORCE71B    869  /* Force Bit                                    */
#define IFORCE71C    870  /* Force Bit                                    */
#define IFORCE71D    871  /* Force Bit                                    */
#define IFORCE71E    872  /* Force Bit                                    */
#define IFORCE71F    873  /* Force Bit                                    */
/* ---------------- END Force-Bits fuer Karte 7 --------------------------- */
/* ---------------- Force-Bits fuer Karte 8 ------------------------------- */
#define IFORCE800    874  /* Force Bit                                    */
#define IFORCE801    875  /* Force Bit                                    */
#define IFORCE802    876  /* Force Bit                                    */
#define IFORCE803    877  /* Force Bit                                    */
#define IFORCE804    878  /* Force Bit                                    */
#define IFORCE805    879  /* Force Bit                                    */
#define IFORCE806    880  /* Force Bit                                    */
#define IFORCE807    881  /* Force Bit                                    */
#define IFORCE808    882  /* Force Bit                                    */
#define IFORCE809    883  /* Force Bit                                    */
#define IFORCE80A    884  /* Force Bit                                    */
#define IFORCE80B    885  /* Force Bit                                    */
#define IFORCE80C    886  /* Force Bit                                    */
#define IFORCE80D    887  /* Force Bit                                    */
#define IFORCE80E    888  /* Force Bit                                    */
#define IFORCE80F    889  /* Force Bit                                    */
#define IFORCE810    890  /* Force Bit                                    */
#define IFORCE811    891  /* Force Bit                                    */
#define IFORCE812    892  /* Force Bit                                    */
#define IFORCE813    893  /* Force Bit                                    */
#define IFORCE814    894  /* Force Bit                                    */
#define IFORCE815    895  /* Force Bit                                    */
#define IFORCE816    896  /* Force Bit                                    */
#define IFORCE817    897  /* Force Bit                                    */
#define IFORCE818    898  /* Force Bit                                    */
#define IFORCE819    899  /* Force Bit                                    */
#define IFORCE81A    900  /* Force Bit                                    */
#define IFORCE81B    901  /* Force Bit                                    */
#define IFORCE81C    902  /* Force Bit                                    */
#define IFORCE81D    903  /* Force Bit                                    */
#define IFORCE81E    904  /* Force Bit                                    */
#define IFORCE81F    905  /* Force Bit                                    */
/* ---------------- END Force-Bits fuer Karte 8 --------------------------- */
/* ---------------- Force-Bits fuer Karte 9 ------------------------------- */
#define IFORCE900    906  /* Force Bit                                    */
#define IFORCE901    907  /* Force Bit                                    */
#define IFORCE902    908  /* Force Bit                                    */
#define IFORCE903    909  /* Force Bit                                    */
#define IFORCE904    910  /* Force Bit                                    */
#define IFORCE905    911  /* Force Bit                                    */
#define IFORCE906    912  /* Force Bit                                    */
#define IFORCE907    913  /* Force Bit                                    */
#define IFORCE908    914  /* Force Bit                                    */
#define IFORCE909    915  /* Force Bit                                    */
#define IFORCE90A    916  /* Force Bit                                    */
#define IFORCE90B    917  /* Force Bit                                    */
#define IFORCE90C    918  /* Force Bit                                    */
#define IFORCE90D    919  /* Force Bit                                    */
#define IFORCE90E    920  /* Force Bit                                    */
#define IFORCE90F    921  /* Force Bit                                    */
#define IFORCE910    922  /* Force Bit                                    */
#define IFORCE911    923  /* Force Bit                                    */
#define IFORCE912    924  /* Force Bit                                    */
#define IFORCE913    925  /* Force Bit                                    */
#define IFORCE914    926  /* Force Bit                                    */
#define IFORCE915    927  /* Force Bit                                    */
#define IFORCE916    928  /* Force Bit                                    */
#define IFORCE917    929  /* Force Bit                                    */
#define IFORCE918    930  /* Force Bit                                    */
#define IFORCE919    931  /* Force Bit                                    */
#define IFORCE91A    932  /* Force Bit                                    */
#define IFORCE91B    933  /* Force Bit                                    */
#define IFORCE91C    934  /* Force Bit                                    */
#define IFORCE91D    935  /* Force Bit                                    */
#define IFORCE91E    936  /* Force Bit                                    */
#define IFORCE91F    937  /* Force Bit                                    */
/* ---------------- END Force-Bits fuer Karte 9 --------------------------- */
/* ---------------- Force-Bits fuer Karte 36 ------------------------------ */
#define IFORCE3600   938  /* Force Bit                                    */
#define IFORCE3601   939  /* Force Bit                                    */
#define IFORCE3602   940  /* Force Bit                                    */
#define IFORCE3603   941  /* Force Bit                                    */
#define IFORCE3604   942  /* Force Bit                                    */
#define IFORCE3605   943  /* Force Bit                                    */
#define IFORCE3606   944  /* Force Bit                                    */
#define IFORCE3607   945  /* Force Bit                                    */
#define IFORCE3608   946  /* Force Bit                                    */
#define IFORCE3609   947  /* Force Bit                                    */
#define IFORCE360A   948  /* Force Bit                                    */
#define IFORCE360B   949  /* Force Bit                                    */
#define IFORCE360C   950  /* Force Bit                                    */
#define IFORCE360D   951  /* Force Bit                                    */
#define IFORCE360E   952  /* Force Bit                                    */
#define IFORCE360F   953  /* Force Bit                                    */
#define IFORCE3610   954  /* Force Bit                                    */
#define IFORCE3611   955  /* Force Bit                                    */
#define IFORCE3612   956  /* Force Bit                                    */
#define IFORCE3613   957  /* Force Bit                                    */
#define IFORCE3614   958  /* Force Bit                                    */
#define IFORCE3615   959  /* Force Bit                                    */
#define IFORCE3616   960  /* Force Bit                                    */
#define IFORCE3617   961  /* Force Bit                                    */
#define IFORCE3618   962  /* Force Bit                                    */
#define IFORCE3619   963  /* Force Bit                                    */
#define IFORCE361A   964  /* Force Bit                                    */
#define IFORCE361B   965  /* Force Bit                                    */
#define IFORCE361C   966  /* Force Bit                                    */
#define IFORCE361D   967  /* Force Bit                                    */
#define IFORCE361E   968  /* Force Bit                                    */
#define IFORCE361F   969  /* Force Bit                                    */
/* ---------------- END Force-Bits fuer Karte 36 -------------------------- */
/* ---------------- Force-Bits fuer Karte 39 ------------------------------ */
#define IFORCE3900   970  /* Force Bit                                    */
#define IFORCE3901   971  /* Force Bit                                    */
#define IFORCE3902   972  /* Force Bit                                    */
#define IFORCE3903   973  /* Force Bit                                    */
#define IFORCE3904   974  /* Force Bit                                    */
#define IFORCE3905   975  /* Force Bit                                    */
#define IFORCE3906   976  /* Force Bit                                    */
#define IFORCE3907   977  /* Force Bit                                    */
#define IFORCE3908   978  /* Force Bit                                    */
#define IFORCE3909   979  /* Force Bit                                    */
#define IFORCE390A   980  /* Force Bit                                    */
#define IFORCE390B   981  /* Force Bit                                    */
#define IFORCE390C   982  /* Force Bit                                    */
#define IFORCE390D   983  /* Force Bit                                    */
#define IFORCE390E   984  /* Force Bit                                    */
#define IFORCE390F   985  /* Force Bit                                    */
#define IFORCE3910   986  /* Force Bit                                    */
#define IFORCE3911   987  /* Force Bit                                    */
#define IFORCE3912   988  /* Force Bit                                    */
#define IFORCE3913   989  /* Force Bit                                    */
#define IFORCE3914   990  /* Force Bit                                    */
#define IFORCE3915   991  /* Force Bit                                    */
#define IFORCE3916   992  /* Force Bit                                    */
#define IFORCE3917   993  /* Force Bit                                    */
#define IFORCE3918   994  /* Force Bit                                    */
#define IFORCE3919   995  /* Force Bit                                    */
#define IFORCE391A   996  /* Force Bit                                    */
#define IFORCE391B   997  /* Force Bit                                    */
#define IFORCE391C   998  /* Force Bit                                    */
#define IFORCE391D   999  /* Force Bit                                    */
#define IFORCE391E  1000  /* Force Bit                                    */
#define IFORCE391F  1001  /* Force Bit                                    */
/* ---------------- END Force-Bits fuer Karte 39 -------------------------- */
#define XSLM_ENTL   1002  /* Kommunikationsbit Schliesszylinder entlueften */
#define XFK_NOABGLP 1003  /* FK: Keine Abgleichparameter in der SPS vorhanden */
#define XFK_AG_AUFN 1004  /* FK: Gelenkkopfkraft-Aufnehmer pr}fen           */
#define XFK_SL_QSTP 1005  /* FK: St|rung Quick-Stop Schlie~einheit        */
#define XFK_AW_QSTP 1006  /* FK: St|rung Quick-Stop Auswerfer             */
#define XFK_PL_QSTP 1007  /* FK: St|rung Quick-Stop Plastifiziereinheit   */
#define XFK_SP_QSTP 1008  /* FK: St|rung Quick-Stop Spritzeinheit         */
#define XFK_ZSCHMIE 1009  /* FK: St|rung Zentralschmierung                */
#define IKEEINAUS   1010  /* Kernzug Schalter */
#define IKELINEACT  1011     /* Fuer die Ermittlung der Adresse des ersten */
                             /* Logikworts fuer den Programmzeiger         */
/* ---------------- Airpress ---------------------------------------------- */
#define XOPM_AIRPR   1012
#define XOPM_APPROP  1013
#define XOPM_APIP    1014
#define XFK_APEAKTIV 1015
#define XFK_APSTOER  1016
#define XFK_APPESYST 1017
/* ---------------- Kartonzaehler ----------------------------------------- */
#define XOPM_KARTON  1018
#define XFK_KARTON1  1019
/* ---------------- Werkzeug Wenden --------------------------------------- */
#define XWDMPENDLAG  1020
#define XWDM_FUNKRS  1021
/* ---------------- Werkzeug Drehteller-Parameter ------------------------- */
#define XDTSZSPUMK   1022
#define XDTIZSPUMK   1023
#define XDTSZDRUMK   1024
#define XDTIZDRUMK   1025
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define XWZA_CHKVOR  1026
#define XWZA_CHKZUR  1027
#define XWZA_CHKFSS  1028
/* ---------------- Spritzeinheiten Schwenken ----------------------------- */
#define XSESCHWENK1  1029
#define XSESCHWENK2  1030
#define XSESCHWENK3  1031
#define XSESCHWENK4  1032
#define XSESCHWENK5  1033
/* ---------------- Dauerbetrieb Zentralschmierung und Filterpumpe -------- */
#define XZSMDAUERB   1034
#define XZSMDBFILPU  1035
/* ---------------- Wegumschaltbit fuer 12 Spritzstufen ------------------- */
#define XMSUM1A      1036
#define XMSUM1B      1037
#define XMSUM1C      1038
/* ---------------- Zeitumschaltbit fuer 12 Spritzstufen ------------------ */
#define XMTUM1A      1039
#define XMTUM1B      1040
#define XMTUM1C      1041
/* ---------------- Druckumschaltbit fuer 12 Spritzstufen ----------------- */
#define XMPUM1A      1042
#define XMPUM1B      1043
#define XMPUM1C      1044
/* ---------------- Seite 87.1 Endschalter Klemmschalen ------------------- */
#define XSLM_S1560   1045
#define XSLM_S1561   1046
#define XSLM_S1562   1047
#define XSLM_S1563   1048
#define XSLM_S1564   1049
#define XSLM_S1565   1050
#define XSLM_S1566   1051
#define XSLM_S1567   1052
#define XSLM_S1634   1053
#define XSLM_S1643   1054
#define XSLM_NOHOLM  1055
#define XWZI_HAKTIV  1056
#define XFK_SNBLOCK  1057
#define XFK_DR4ERR   1058
#define XMOM_MOTON   1059
/*------------------- Optionsbits fuer Gillette-Sonderprogramm -----------*/
#define GIL_OPTBIT0  1060
#define GIL_OPTBIT1  1061
#define GIL_OPTBIT2  1062
#define GIL_OPTBIT3  1063
#define GIL_OPTBIT4  1064
#define GIL_OPTBIT5  1065
#define GIL_OPTBIT6  1066
#define GIL_OPTBIT7  1067
#define GIL_OPTBIT8  1068
#define GIL_OPTBIT9  1069
#define GIL_OPTBIT10 1070
#define GIL_OPTBIT11 1071
#define GIL_OPTBIT12 1072
#define GIL_OPTBIT13 1073
#define GIL_OPTBIT14 1074
#define GIL_OPTBIT15 1075
#define GIL_ISTBIT0  1076
#define GIL_ISTBIT1  1077
#define GIL_ISTBIT2  1078
#define GIL_ISTBIT3  1079
#define GIL_ISTBIT4  1080
#define GIL_ISTBIT5  1081
#define GIL_ISTBIT6  1082
#define GIL_ISTBIT7  1083
#define GIL_ISTBIT8  1084
#define GIL_ISTBIT9  1085
#define GIL_ISTBIT10 1086
#define GIL_ISTBIT11 1087
#define GIL_ISTBIT12 1088
#define GIL_ISTBIT13 1089
#define GIL_ISTBIT14 1090
#define GIL_ISTBIT15 1091
#define GIL_OPTBIT16 1092
#define GIL_OPTBIT17 1093
#define GIL_OPTBIT18 1094
#define GIL_OPTBIT19 1095
#define GIL_OPTBIT20 1096
#define GIL_OPTBIT21 1097
#define GIL_OPTBIT22 1098
#define GIL_OPTBIT23 1099
#define GIL_OPTBIT24 1100
#define GIL_OPTBIT25 1101
#define GIL_OPTBIT26 1102
#define GIL_OPTBIT27 1103
#define GIL_OPTBIT28 1104
#define GIL_OPTBIT29 1105
#define GIL_OPTBIT30 1106
#define GIL_OPTBIT31 1107
#define GIL_ISTBIT16 1108
#define GIL_ISTBIT17 1109
#define GIL_ISTBIT18 1110
#define GIL_ISTBIT19 1111
#define GIL_ISTBIT20 1112
#define GIL_ISTBIT21 1113
#define GIL_ISTBIT22 1114
#define GIL_ISTBIT23 1115
#define GIL_ISTBIT24 1116
#define GIL_ISTBIT25 1117
#define GIL_ISTBIT26 1118
#define GIL_ISTBIT27 1119
#define GIL_ISTBIT28 1120
#define GIL_ISTBIT29 1121
#define GIL_ISTBIT30 1122
#define GIL_ISTBIT31 1123
#define GIL_ISTBIT32 1124
#define GIL_ISTBIT33 1125
#define GIL_ISTBIT34 1126
#define GIL_ISTBIT35 1127
#define GIL_ISTBIT36 1128
#define GIL_ISTBIT37 1129
#define GIL_ISTBIT38 1130
#define GIL_ISTBIT39 1131
#define GIL_ISTBIT40 1132
#define GIL_ISTBIT41 1133
#define GIL_ISTBIT42 1134
#define GIL_ISTBIT43 1135
#define GIL_ISTBIT44 1136
#define GIL_ISTBIT45 1137
#define GIL_ISTBIT46 1138
#define GIL_ISTBIT47 1139
/* ---------------- Wegumschaltbit fuer 9 Spritzstufen -------------------- */
#define XMSUM16      1140
#define XMSUM17      1141
#define XMSUM18      1142
#define XMSUM19      1143
/* ---------------- Zeitumschaltbit fuer 9 Spritzstufen ------------------- */
#define XMTUM17      1144
#define XMTUM18      1145
#define XMTUM19      1146
/* ---------------- Druckumschaltbit fuer 9 Spritzstufen ------------------ */
#define XMPUM16      1147
#define XMPUM17      1148
#define XMPUM18      1149
#define XMPUM19      1150
/* ------------------------------------------------------------------------ */
#define ISNM_ERHNM2  1151
#define XFK_SNWECH2  1152  /* FK: Schneckenwechsel                           */           
#define XFK_IR2WEG3  1153  /* FK: Weggeber des Aggregates 2 defekt           */
#define XFK_IR2WEG1  1154  /* FK: Weggeber der Spritzachse 2 defekt          */
#define XFK_AGM_TU2  1155  /* FK: Stoerung der Duesenschutztuer  Agg. 2      */  
#define XFK_SNIKOK2  1156  /* FK: Schneckenfreigabe fehlt  Agg. 2            */             
#define XFK_AGMLER2  1157  /* FK: ]berlastung der Aggregatachse 2            */
#define XFK_PLMLER2  1158  /* FK: ]berlastung der Plastifizierachse 2        */
#define XFK_SPMLER2  1159  /* FK: ]berlastung der Einspritzachse 2           */   
#define XFK_PLUTTI2  1160  /* FK: Plast.-Zeit Agg. 2 ueberschritten          */
#define XFK_SEP_OF2  1161  /* FK: Einspritzdruck Offset Fehler Agg. 2        */
#define XFK_ZHTMPK2  1162  /* FK: Zylindertemperaturen unter 150 [C Agg. 2   */
#define XFK_SN_AUF2  1163  /* FK: Spritzkraft-Aufnehmer pr}fen Agg. 2        */
#define XFK_SPKRAF2  1164  /* FK: Zu grosse Schneckenr}ckzugskraft Agg. 2    */
#define XFK_EXTNINI  1165  /* FK: Schnittstelle Temp.Ger{t nicht initialisiert*/ 
#define XFK_EXTDAT   1166  /* FK: St|rung Datacom Temp.Ger{t                 */      
#define XFK_EXTEMP   1167  /* FK: St|rung ext. Temp.Ger{t                    */      
#define XFK_CDWBLK   1168  /* FK: Werkzeugbewegung von extern blockiert      */ 
#define XFK_CDHGNE   1169  /* FK: Entnahme-HG Kupplung nicht entriegelt      */      
#define XFK_CDHGNV   1170  /* FK: Entnahme-HG Kupplung nicht verriegelt      */      
#define XFK_CDHGNCD  1171  /* FK: Entnahme-HG hat CD nicht gegriffen         */      
#define XFK_CDHGNAG  1172  /* FK: Entnahme-HG hat Angu~ nicht gegriffen      */      
#define XFK_CDFHGN   1173  /* FK: Folge-HG hat CD nicht gegriffen            */ 
#define XFK_CDMWECH  1174  /* FK: Bitte Matrize wechseln                     */ 
#define XFK_IR2DREH  1175  /* FK: Drehzahlgeber der Plast. 2 defekt          */
#define XFK_DR3ERR   1176  /* */
#define XFK_PLSSEN2  1177  /* FK: Plastifizierweg Agg 2 }berschritten        */
#define XFK_AGM_VO2  1178  /* FK: D}senanlagedruck Agg 2 nicht erreicht      */
#define XFK_PLM_AK2  1179  /* FK: Plastifizierweg Agg 2 nicht erreicht       */
#define XFK_SPREFE2  1180  /* FK: Schnecken-Referenzpunkt Agg 2 fehlt        */
#define XFK_AGMSPO2  1181  /* FK: Aggregat 2 nicht in Position               */
#define XFK_SPMSPO2  1182  /* FK: Schnecke 2 nicht in Position               */
#define XFK_AG_VER2  1183  /* FK: Aggregat 2-Verriegelungsfehler             */
#define XFK_SPRFER2  1184  /* FK: Einspritzachse-Referenzschalterfehler Agg 2*/
#define XFK_AGMLWR2  1185  /* FK: Erhoehte Leistung bei Aggregatachse 2      */
#define XFK_PLMLWR2  1186  /* FK: Erhoehte Leistung bei Plastifizierachse 2  */
#define XFK_SPMLWR2  1187  /* FK: Erhoehte Leistung bei Einspritzachse 2     */
#define XFK_DR3TEMP  1188  /* FK: Motoruebertemperatur am Spritzdrive Agg 2  */
#define XFK_DR3FRG   1189  /* FK: Freigabest|rung im Spritzdrive 2           */ 
#define XFK_AGE_TU2  1190  /* FK: Duesenschutz nicht geschlossen Agg 2       */
#define XFK_DTNREF   1191  /* FK: Drehteller nicht referenziert              */
#define XFK_ENDWEND  1192  /* FK: Fehler Endlage Wenden                      */
#define XFK_BLWEND   1193  /* FK: Fehler Blockierung Wenden                  */
#define XFK_SPWEND   1194  /* FK: Fehler Startpunkt Wenden                   */
#define XFK_EPKOVER  1195  /* FK: Ziel }berfahren                            */
#define XFK_ELNFIX   1196  /* FK: Endlage nicht fixiert                      */
#define XFK_DTBLOCK  1197  /* FK: Drehteller blockiert                       */
#define XFK_WZAVBL   1198  /* FK: Werkzeugauswerfer vor blockiert            */
#define XFK_WZAZBL   1199  /* FK: Werkzeugauswerfer zur}ck blockiert         */
#define XFK_WZAECHK  1200  /* FK: Endlage Werkzeugauswerfer pr}fen           */
#define XFMOTS2      1201  /* FK: Motor 2 Ueberstromrelais ausgeloest        */
#define XFMOT132     1202  /* FK: Motor 2 nicht im Dreieckbetrieb            */
#define XFK_PLETEMP  1203  /* FK: Uebertemperatur Plastifiziergetriebe       */
#define XFK_AG2_VOR  1204  /* FK: Endlage Werkzeugauswerfer pr}fen           */
#define XFK_IOE_DI1  1205  /* FK: Freigabe von konf. Eingang 1 fehlt (A2461) */
#define XFK_IOE_DI2  1206  /* FK: Freigabe von konf. Eingang 2 fehlt (A2462) */
#define XFK_IOE_DI3  1207  /* FK: Freigabe von konf. Eingang 3 fehlt (A2463) */
#define XFK_IOE_DI4  1208  /* FK: Freigabe von konf. Eingang 4 fehlt (A2464) */
#define XFK_PLEPOWER 1209  /* FK: Hauptschalter Plastifizierantrieb ausgel|st */
/* ------------------------------------------------------------------------ */
/* fuer ELEKTRA 300 */
#define MSSPINOK  1210     /* Komunikationsbit fuer Anzahl geschmierte Nippel S.15 z.3*/
#define MSGELEOK  1211     /* Komunikationsbit fuer Anzahl geschmierte Nippel S.15 z.7*/
/* ------------------------------------------------------------------------ */
#define IOM_AOIQT 1212     /* Komunikation fuer SPS-freigabe der analogen Ausgaenge S. 66.2  */
#define OPM_PARAL 1213     /* Komunikation fuer SPS-freigabe der Auswerfer und Kern parallel */
/* ------------------------------------------------------------------------ */
#define XFMOT133     1214  /* FK: Motor 3 nicht im Dreieckbetrieb           */
#define XFMOTS3      1215  /* FK: Motor 3 Ueberstromrelais ausgeloest       */
#define XFOELN2      1216  /* FK: Oelniveau .8-F30 zu niedrig               */
#define IFK_OELFIL3  1217  /* FK: Druckfilter 3 verschmutzt                 */
#define IOM_DIOIQT   1218  /* Komunikation fuer SPS-freigabe der digitalen Ein/Ausgaenge S. 66.0,1 */
#define XOM_AWPZUR   1219  /* SPS-Freigabe fuer Auswerferdruck zurueck      */
/* ---------------- Neue Bits fuer 5/6 Farben ----------------------------- */
#define XDLAGR5      1220
#define XDDUES5      1221
#define XDWSP05      1222
#define XMSUM51      1223
#define XMSUM52      1224
#define XMSUM53      1225
#define XMSUM54      1226
#define XMSUM55      1227
#define XMTUM51      1228
#define XMTUM52      1229
#define XMTUM53      1230
#define XMTUM54      1231
#define XMTUM55      1232
#define XMTUM56      1233
#define XMPUM51      1234
#define XMPUM52      1235
#define XMPUM53      1236
#define XMPUM54      1237
#define XMPUM55      1238
#define XDSCHW5      1239
#define XSNM_ERHNM5  1240 /* FK: Signal-Bit erhoehtes Drehmoment fuer Agg. 5 */
#define XFK_DRS5_F5  1241 /* FK: Druckschalter .5-F501 oeffnet nicht         */
#define XPLS_RAMPE5  1242
#define XFTDOS5      1243 /* FK: Plastifizierzeit Agg.5 }berschritten        */
#define XFDOS5       1244 /* FK: Plastifizierweg Aggr.5 }berschritten        */
#define XFK_PLM5AKT  1245 /* FK: Plastifizierweg Aggr.5 nicht erreicht       */
/* ------------------------------------------------------------------------ */
#define XDLAGR6      1246
#define XDDUES6      1247
#define XDWSP06      1248
#define XMSUM61      1249
#define XMSUM62      1250
#define XMSUM63      1251
#define XMSUM64      1252
#define XMSUM65      1253
#define XMTUM61      1254
#define XMTUM62      1255
#define XMTUM63      1256
#define XMTUM64      1257
#define XMTUM65      1258
#define XMTUM66      1259
#define XMPUM61      1260
#define XMPUM62      1261
#define XMPUM63      1262
#define XMPUM64      1263
#define XMPUM65      1264
#define XDSCHW6      1265
#define XSNM_ERHNM6  1266 /* FK: Signal-Bit erhoehtes Drehmoment fuer Agg. 6 */
#define XFK_DRS5_F6  1267 /* FK: Druckschalter .5-F601 oeffnet nicht         */
#define XPLS_RAMPE6  1268
#define XFTDOS6      1269 /* FK: Plastifizierzeit Agg.6 }berschritten        */
#define XFDOS6       1270 /* FK: Plastifizierweg Aggr.6 }berschritten        */
#define XFK_PLM6AKT  1271 /* FK: Plastifizierweg Aggr.6 nicht erreicht       */
/* ------------------------------------------------------------------------ */
#define XFSCHWE5     1272 /* FK: Schneckenwechsel Aggr.5                     */
#define XFSCHWE6     1273 /* FK: Schneckenwechsel Aggr.6                     */
#define XFA5RUH      1274 /* FK: Aggregat 5 nicht in hintere Lage            */
#define XFA6RUH      1275 /* FK: Aggregat 6 nicht in hintere Lage            */
#define XFAGSICH5    1276 /* FK: Sicherheitssch}tz Agg. 5 defekt             */
#define XFAGSICH6    1277 /* FK: Sicherheitssch}tz Agg. 6 defekt             */
#define XFWEG15      1278 /* FK: Wegmesssystem 3 Schnecke 5 defekt           */
#define XFWEG16      1279 /* FK: Wegmesssystem 3 Schnecke 6 defekt           */
#define XFK_AGM5VOR  1280 /* FK: Duesenanlagedruck Aggregat 5 nicht erreicht */
#define XFK_AGM6VOR  1281 /* FK: Duesenanlagedruck Aggregat 6 nicht erreicht */
#define XFK_PLIV5AK  1282 /* FK: Schneckendrehzahlmessung Agg.5 gestoert     */
#define XFK_PLIV6AK  1283 /* FK: Schneckendrehzahlmessung Agg.6 gestoert     */
#define XFTEMAB5     1284 /* FK: Temp.Absenkung Zyl.Heizung Agg.5 laeuft     */
#define XFSNEK5      1285 /* FK: Schneckenfreigabe Agg.5 fehlt               */
#define XFTEMAB6     1286 /* FK: Temp.Absenkung Zyl.Heizung Agg.6 laeuft     */
#define XFSNEK6      1287 /* FK: Schneckenfreigabe Agg.6 fehlt               */
#define XFK_DRB7408  1288 /* FK: Druckfuehler B7408 ausser Toleranz          */
#define XFK_DRB7508  1289 /* FK: Druckfuehler B7508 ausser Toleranz          */
/* ------------------------------------------------------------------------ */
#define XSEABGLST1   1290    /* Komunikationsbit Start SE1 Abgleich */
#define XSEABGLST2   1291    /* Komunikationsbit Start SE2 Abgleich */
#define XSEABGLST3   1292    /* Komunikationsbit Start SE3 Abgleich */
#define XSEABGLST4   1293    /* Komunikationsbit Start SE4 Abgleich */
#define XSEABGLST5   1294    /* Komunikationsbit Start SE5 Abgleich */
#define XSEABGLST6   1295    /* Komunikationsbit Start SE6 Abgleich */
#define XSEABGLRS1   1296    /* Komunikationsbit Reset SE1 Abgleich */
#define XSEABGLRS2   1297    /* Komunikationsbit Reset SE2 Abgleich */
#define XSEABGLRS3   1298    /* Komunikationsbit Reset SE3 Abgleich */
#define XSEABGLRS4   1299    /* Komunikationsbit Reset SE4 Abgleich */
#define XSEABGLRS5   1300    /* Komunikationsbit Reset SE5 Abgleich */
#define XSEABGLRS6   1301    /* Komunikationsbit Reset SE6 Abgleich */
/* ------------------------------------------------------------------------ */
#define XSPS_OPTION1  1302  /* SPS-Option1 */
#define XSPS_OPTION2  1303  /* SPS-Option2 */
#define XSPS_OPTION3  1304  /* SPS-Option3 */
#define XSPS_OPTION4  1305  /* SPS-Option4 */
#define XSPS_OPTION5  1306  /* SPS-Option5 */
#define XSPS_OPTION6  1307  /* SPS-Option6 */
#define XSPS_OPTION7  1308  /* SPS-Option7 */
#define XSPS_OPTION8  1309  /* SPS-Option8 */
#define XSPS_OPTION9  1310  /* SPS-Option9 */
#define XSPS_OPTION10 1311  /* SPS-Option10 */
#define XSPS_OPTION11 1312  /* SPS-Option11 */
#define XSPS_OPTION12 1313  /* SPS-Option12 */
#define XSPS_OPTION13 1314  /* SPS-Option13 */
#define XSPS_OPTION14 1315  /* SPS-Option14 */
#define XSPS_OPTION15 1316  /* SPS-Option15 */
#define XSPS_OPTION16 1317  /* SPS-Option16 */  
/* ------------------------------------------------------------------------ */
#define XQUM_IQTFRD   1318  /* 71.0 SPS-Freigabebit Foerderband         */
#define XQUM_IQT720   1319  /* 72.0 SPS-Freigabebit Qualitaetskontrolle */
#define XQUM_IQT721   1320  /* 72.1 SPS-Freigabebit Selektierweiche     */
/* ------------------------------------------------------------------------ */
#define XRDM_CARD     1321  /* Card-Merker, d.h. Card wurde durchgezogen */
#define XOPM_IQT800   1322  /* SPS_IQT-Option Kuehlwasser-Abschaltung Seite80 */
/* ------------------------------------------------------------------------ */
#define XFWEG22       1323  /* FK: Wegmesssystem 1 2.NC-Modul Kanal1 defekt */
#define XFWEG23       1324  /* FK: Wegmesssystem 1 3.NC-Modul Kanal1 defekt */
#define XFWEG24       1325  /* FK: Wegmesssystem 1 4.NC-Modul Kanal1 defekt */
#define XFWEG32       1326  /* FK: Wegmesssystem 4 Spritzeinheit 2 defekt   */
#define XFWEG33       1327  /* FK: Wegmesssystem 4 Spritzeinheit 3 defekt   */
#define XFWEG34       1328  /* FK: Wegmesssystem 4 Spritzeinheit 4 defekt   */
#define XFWEG42       1329  /* FK: Wegmesssystem 2 2.NC-Modul Kanal4 defekt */
#define XFWEG43       1330  /* FK: Wegmesssystem 2 3.NC-Modul Kanal4 defekt */
#define XFWEG44       1331  /* FK: Wegmesssystem 2 4.NC-Modul Kanal4 defekt */
/* ------------------------------------------------------------------------ */
#define XSEM_RAMPE1   1332  /* Rampe1 ein/ausschalten */
#define XSEM_RAMPE2   1333  /* Rampe2 ein/ausschalten */
#define XSEM_RAMPE3   1334  /* Rampe3 ein/ausschalten */
#define XSEM_RAMPE4   1335  /* Rampe4 ein/ausschalten */
#define XSEM_RAMPE5   1336  /* Rampe5 ein/ausschalten */
/* ------------------------------------------------------------------------ */
#define XUPMAXPLCVL   1337  /* Kommunikationsbit fuer Max PLC-Values von SPS holen */
/* ---------------- Werkzeugheizung fuer 2.SPS ---------------------------- */
#define XHEM2START    1338  /* Start Heizungsoptimierung                    */
#define XHZ2DANF      1339  /* Einschaltbit Werkzeugheizung                 */
#define XHEM2ABORT    1340  /* Heizungsoptimierung abbrechen                */
#define XHEM2READY    1341  /* Heizungsoptimierung fertig                   */
#define XHZ2MXSTDT    1342  /* Anforderungsbit fuer Heizungsdownload        */
/* ------------------------------------------------------------------------ */
#define XFK_WS        1343  /* Fehlerbit Mechanische Schlie~sperre      */
#define XFK_XSM_ANF   1344  /* Fehlerbit Produktionsstart: Parameter aktiv */
#define XFK_XSM_AN2   1345  /* Fehlerbit Produktionsstart: WKZ-Sicherungsdruck aktiv */
#define XFK_SERINI    1346  /* Fehlerbit Serielle Schnittstelle nicht initialisiert */
#define XFK_SERCOM    1347  /* Fehlerbit St|rung Datacom externe Heizung */
#define XFK_SEREXT    1348  /* Fehlerbit St|rung externe Heizung */
#define XFK_SERPRO    1349  /* Fehlerbit Protokoll externe Heizung nicht verf]gbar */
/* ----------------------------------------------------------------------- */
#define XHXSNECHO     1350  /* Echobit S. 39.9 */
#define XOPM_IQT350   1351  /* Komunikation fuer SPS-freigabe der S. 35 */
#define XOPM_IQT399   1352  /* Komunikation fuer SPS-freigabe der S. 39.9 */
/* ----------------------------------------------------------------------- */
#define XOPM_IQT710   1353  /* Komunikation fuer SPS-freigabe der S. 71.0 */
#define XSGM_SETPOS   1354  /* Sollwert fuer elektr. Schutztuer   S. 71.0 */
#define XFK_SGERR1    1355  /* Fehlerbit St|rung vordere Schutzt}rantrieb */
#define XFK_SGERR2    1356  /* Fehlerbit Blockierung der vorderen Schutzt}r */
#define XFK_SGREF     1357  /* Fehlerbit Vordere Schutzt}r nicht referenziert */
#define XROS_AW1HUB   1358  /* Sollwert fuer Handling S.70.0 Zeile 5 */
#define XFK_AWSCHL    1359  /* Fehlerbit Auswerferbewegung bei offener Schutzt}r */
/* ------------------------------------------------------------------------ */
#define XFK_SGM2SS    1360  /* Sicherheitssch}tz 2-K0326 defekt */
#define XFK_B2190     1361  /* Druckf}hler B2190 au~er Toleranz */
#define XFK_MOE2SHZ   1362  /* Motor 2 ]berstromrelais ausgel|st */
#define XFK_MOE3SHZ   1363  /* Motor 3 ]berstromrelais ausgel|st */
#define XFK_MOE2EIN   1364  /* Motor 2 nicht im Dreiecksbetrieb */
#define XFK_MOE3EIN   1365  /* Motor 3 nicht im Dreiecksbetrieb */
#define XFK_AGEHINTEN 1366  /* D}senschutz hinten / Aggregatabsicherung */
#define XFK_PANHUB    1367  /* Schlie~kolbenweg }berschritten */
#define XFK_PANMAX    1368  /* Max. Schlie~kolbenweg erreicht */
#define XFK_PANPOS    1369  /* Schlie~kolbenposition falsch */
#define XFK_KLEMTIM   1370  /* ]berwachungszeit Klemmschalen schlie~en */
#define XFK_KLEMAUF   1371  /* Klemmschalen nicht offen */
#define XFK_KLEMZU    1372  /* Klemmschalen nicht geschlo~en */
#define XFK_KLEMPOS   1373  /* Nutposition Klemmschalen nicht ok */
#define XFK_F1613     1374  /* Keine Freigabe Schlie~kolben vor */
#define XFK_F1614     1375  /* Keine Freigabe Schlie~kolben zur}ck */
#define XFK_SGMATTE   1376  /* Trittmatte bet{tigt */
#define XFK_RO_NOTAUS 1377  /* Not-Aus von Handling-Ger{t */
#define XFK_SPSTELL   1378  /* Spritzeinheit ist ausgeschwenkt */
#define XFK_S0013     1379  /* Spritzeinheit nicht in hinterer Position */
#define XFK_SG_QUIT   1380  /* Bitte Quittiertaste hinteres SG bet{tigen */
#define XFK_PNEUMES   1381  /* St|rung pneumatische Schutzt}r */
#define XFK_AGENDL    1382  /* Spritzeinheit nicht in hinterer Endlage */
#define XOPM_REGP2    1383  /* Komunikation fuer SPS-freigabe Pumpe 2 ist eine Regelpumpe */
#define XFK_SGTASTE   1384  /* Bitte Taste 'Schutzgitter Auf' bet{tigen */
#define XFK_KLEMT2    1385  /* ]berwachungsz. 'Klemmschalen |ffnen' }berschritten */
#define XFK_NC24V_1   1386  /* Fehler Spannungsversorgung Weg-Modul 1 */
#define XFK_NC24V_2   1387  /* Fehler Spannungsversorgung Weg-Modul 2 */
#define XFK_B4068     1388  /* Druckf}hler B4068 au~er Toleranz */
#define XFK_B4069     1389  /* Druckf}hler B4069 au~er Toleranz */
/* ------------------------------------------------------------------------ */
#define XSEABGLTASTE1 1390  /* Komunikationsbit Agg-Taste SE1 Abgleich */
#define XSEABGLTASTE2 1391  /* Komunikationsbit Agg-Taste SE2 Abgleich */
#define XSEABGLTASTE3 1392  /* Komunikationsbit Agg-Taste SE3 Abgleich */
#define XSEABGLTASTE4 1393  /* Komunikationsbit Agg-Taste SE4 Abgleich */
#define XSEABGLTASTE5 1394  /* Komunikationsbit Agg-Taste SE5 Abgleich */
#define XHXSNECHO_2   1395  /* Echobit2 S. 39.9 */
#define GIL_ISTBIT48  1396
#define GIL_ISTBIT49  1397
#define GIL_ISTBIT50  1398
#define GIL_ISTBIT51  1399
#define GIL_ISTBIT52  1400
#define GIL_ISTBIT53  1401
#define GIL_ISTBIT54  1402
#define GIL_ISTBIT55  1403
#define GIL_ISTBIT56  1404
#define GIL_ISTBIT57  1405
#define GIL_ISTBIT58  1406
#define GIL_ISTBIT59  1407
#define GIL_ISTBIT60  1408
#define GIL_ISTBIT61  1409
#define GIL_ISTBIT62  1410
#define GIL_ISTBIT63  1411
/* ------------------------------------------------------------------------ */
#define XFK_NDPBEGR   1412  /* FK: Nachdruck wurde begrenzt                 */
#define XFK_AW_VERR   1413  /* FK: Auswerfer-Verriegelungsfehler            */
#define XFK_SP_VERR   1414  /* FK: Spritzeinheit-Verriegelungsfehler        */
#define XFK_PL_VERR   1415  /* FK: Plastifizier-Verriegelungsfehler         */
/* ------------------------------------------------------------------------ */
#define XFK_SE1WEGM   1416  /* FK: Wegmesssystem Spritzeinheit 1 defekt     */
#define XFK_SE1NACT   1417  /* FK: Nullpunktabgl. Spritzeinh.1 nicht aktiv  */
#define XFK_SE2WEGM   1418  /* FK: Wegmesssystem Spritzeinheit 2 defekt     */
#define XFK_SE2NACT   1419  /* FK: Nullpunktabgl. Spritzeinh.2 nicht aktiv  */
/* ------------------------------------------------------------------------ */
#define XNDS_DRBEGR   1420  /* Nachdruckbegrenzung ein=0 aus=1              */
/* ------------------------------------------------------------------------ */
#define XFK_SE3WEGM   1421  /* FK: Wegmesssystem Spritzeinheit 3 defekt     */
#define XFK_SE3NACT   1422  /* FK: Nullpunktabgl. Spritzeinh.3 nicht aktiv  */
#define XFK_SE4WEGM   1423  /* FK: Wegmesssystem Spritzeinheit 4 defekt     */
#define XFK_SE4NACT   1424  /* FK: Nullpunktabgl. Spritzeinh.4 nicht aktiv  */
#define XFK_SE5WEGM   1425  /* FK: Wegmesssystem Spritzeinheit 5 defekt     */
#define XFK_SE5NACT   1426  /* FK: Nullpunktabgl. Spritzeinh.5 nicht aktiv  */
#define XFK_SE6WEGM   1427  /* FK: Wegmesssystem Spritzeinheit 6 defekt     */
#define XFK_SE6NACT   1428  /* FK: Nullpunktabgl. Spritzeinh.6 nicht aktiv  */
/* ------------------------------------------------------------------------ */
#define XSEABGLTASTE6 1429  /* Komunikationsbit Agg-Taste SE6 Abgleich      */
#define XFK_SG_QERR   1430  /* FK: ]berwachungszeit Quittiertaste }berschritten */
/* ---------------- Werkzeugauswerfer ------------------------------------- */
#define XOP_WKZAUSW2  1431  /* SPS-Optionsbit fuer 2 Werkzeugauswerfer      */
#define XWZA2CHKVOR   1432 
#define XWZA2CHKZUR   1433
#define XWZA2CHKFSS   1434
#define XFK_WZA2VBL   1435  /* FK: Werkzeugauswerfer 2 vor blockiert    */
#define XFK_WZA2ZBL   1436  /* FK: Werkzeugauswerfer 2 zur}ck blockiert */ 
#define XFK_WZA2EPR   1437  /* FK: Endlage Werkzeugauswerfer 2 pr}fen   */
/* ------------------------------------------------------------------------ */
#define XFK_TSTAGG2   1438
#define XFK_AG2SICH   1439
#define XFK_PUEBERS   1440
#define XFK_WESMIRD   1441
#define XFK_QUIT      1442
#define XFK_QUITBGS   1443
#define XFK_QUTIBS    1444
#define XFK_NEHI      1445
#define XFK_SNIKOKM   1446
#define XFK_ZHMABNI   1447
#define XFK_ZHM_AUM   1448
#define XFK_ARRET     1449
#define XFK_MECHSSP   1450
#define XFK_MSPESDF   1451
#define XFK_EINRICH   1452
#define XFK_KEAWOST   1453
#define XFK_SPZYLNP   1454
#define XFK_BAP44PR   1455
#define XFK_MISCHK    1456
#define XFK_WPKTNPL   1457
#define XFK_UWWKZBW   1458
#define XFK_UWAWBEW   1459
#define XFK_PARPROD   1460
#define XFK_WSWTDF    1461
#define XSLS_ERHKRP   1462
#define XOPS_FSSBLK   1463
#define XOPM_FSSEND   1464
#define XFK_DRB4409   1465
#define XOB_ERHSLKR   1466
#define XOP_CANWINK   1467
#define XFK_CANWINK   1468
#define XOPM_AGBIRK   1470
#define XOPM_SLSENS   1471
#define XFK_SLVERR1   1472
#define XFK_SLVERR2   1473
#define XFK_SLVERR3   1474
#define XFK_CABTEMP   1475
#define XAGM_NOBIRK   1476
#define XFK_DRB7001   1477
#define XFK_DRB7003   1478
#define XFK_DRB7101   1479
#define XFK_DRB7103   1480
/* ---------------- Wegumschaltbit fuer 12 Spritzstufen ------------------- */
#define XMSUM26       1481
#define XMSUM27       1482
#define XMSUM28       1483
#define XMSUM29       1484
#define XMSUM2A       1485
#define XMSUM2B       1486
/* ---------------- Zeitumschaltbit fuer 12 Spritzstufen ------------------ */
#define XMTUM27       1487
#define XMTUM28       1488
#define XMTUM29       1489
#define XMTUM2A       1490
#define XMTUM2B       1491
#define XMTUM2C       1492
/* ---------------- Druckumschaltbit fuer 12 Spritzstufen ----------------- */
#define XMPUM26       1493
#define XMPUM27       1494
#define XMPUM28       1495
#define XMPUM29       1496
#define XMPUM2A       1497
#define XMPUM2B       1498
/* ------------------------------------------------------------------------ */
#define XNDS_DRBEG2   1499  /* Nachdruckbegrenzung Agg.2 ein=0 aus=1        */

#endif         /* #ifndef _iscosbit */


