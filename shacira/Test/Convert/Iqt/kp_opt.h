/*********************************************************************
*
*
*         KP_OPT.H
*
*         Index der Optionen in OptionTab als Konstanten
*
*
*********************************************************************/

/*  *** HISTORY ***
*   25.04.90   -TSchw-     Abtrennung von BBR_KP.H
*   13.09.90   -TSchw-     OPTIND_GRAPHIC_CARD wird zu OPTIND_FLOPPY
*   03.12.90   -TSchw-     OPTIND_M510         wird zu OPTIND_REST_POS
*                          OPTIND_SCREW_KERN   wird zu OPTIND_CENTRAL_LUB
*   13.12.90   -JG-        OPTIND_REG_MOTCONST Option 36  
*                          OPTIND_REG_SHYST    Option 37 neu eingetragen    
*   14.02.91   -TSchw-     OPTIND_HANDLING     Option 38 neu eingetragen
*   15.02.91   -TSchw-     OPTIND_PRAEGEN1     Option 39 und
*                          OPTIND_PRAEGEN2     Option 40 neu eingetragen
*   03.05.91   -MB-        Optionen 41-45 neu eingetragen fuer Aggregat 2
*   24.06.91   -TSchw-     Optionen neu augeteilt
*   12.09.91   -PR-        Mit Maintaler Version abgeglichen
*                          Man beachte in Zukunft den hierfuer reservierten
*                          Bereich sowie die Auswirkungen von Aenderungen bei
*                          den gemeinsam genutzten Optionen
*   05.12.91   -TSchw-     OPTIND_FHK           Option 32 neu eingetragen
*   05.03.92   -PR-        Mit Maintaler Version abgeglichen
*   30.11.92   -TSchw-     OPTIND_SPECPROG     Option 97 und
*   13.09.95   -HAns-      OPTIND_TERMINAL   Option 91 von common uebernommen
*   21.09.95   -HAns-      OPTIND_STD_PG eingefuegt
*   13.02.96   -HAns-      OPTIND_ENTRY_AGG3 bis OPTIND_SN_TEMP_AGG4 
*                          (Heizung fuer Aggregat 3 + 4) eingefuegt.
*   22.02.96   -HAns-      OPTIND_AGG_PRESS_AGG3+4 sowie OPTIND_JET_AGG3+4
*                          fuer 3+4.Aggregat eingefuegt.
*   13-09-96   -PR-        Optionen fuer frei progr.bare Kernzuege (OPTIND_PROG_CORES).
*	 17.09.96   -PR-			Option fuer verlaengerte Duese (OPTIND_EXTD_JET)
*	 13.02.97   -HAns-		Option fuer SPS-Freigabe (DV7) eingefuegt.
*	 27.03.97   -HAns-		Option fuer verlaengerte Duese (OPTIND_EXTD_JET)
*                          herausgenommen, da nirgends benutzt.
*   18.03.97   -HAns-      Option OPTIND_DUES_ANPR_MIN fuer KDE/KE eingefuegt.
*   10.07.97   -HAns-      Option OPTIND_STATE_AFTERCORE fuer KD (Zustand nach
*                          Kern ein- bzw. ausgefahren) eingefuegt.
*   06.10.97   -HAns-      Option OPTIND_SN_ENDLAGEREGEL fuer KD 
*                          (Seite 40, Zeile 14 Textaenderung von
*                          "Staudruckentlastung nach Plast. aus=0" nach
*                          "Schneckenendlageregelung aus = 0"  und
*   26.02.98   -HAns-      Option OPTIND_NOCHG_MDM fuer KE/KS eingefuegt.
*                          (kein erhoehtes Motordrehmoment)
*   09.02.00   -TSchw-     Option 8SOFTKEYS neu eingefuegt.
*   14.02.00   -HAns-      Option OPTION_ENTRY_AGG5 bis OPTION_MASS_TEMP_AGG6_
*                          eingefuegt.
*   15.03.00   -HAns-      Option OPTIND_AGG_WEGMESS eingefuegt.
*   07.08.00   -HAns-      Option OPTIND_PROG_4CORES eingefuegt.
*                          Option OPTIND_AWPLATTENSICH eingefuegt.
*   07.06.01   -HA-        Option OPTIND_FREE_BDETEXT eingefuegt.
*   14.01.02   -HA-        Option OPTIND_FREE_LVTEXT eingefuegt.
*   11.03.02 -HA-    Option OPTIND_BRDRV eingefuegt.
*   26.03.02 -HA-    Option OPTIND_BAR_PSI und OPTIND_CELCIUS_KELVIN eingefuegt.
*   13.06.02 -HA-    Option OPTIND_PSHOT_COUNTER eingefuegt.
*   06.12.02 -HA-    Option OPTIND_PRES_TRANS_OPEN_FORCE eingefuegt.
*   19.03.03 -HA-    Option OPTIND_HOSTPFILE eingefuegt.
*   05.06.03 -HA-    Option OPTIND_NEW_AGGSCHALTUNG und OPTIND_SLKRAFTREG_WITH_SENS eingefuegt.
*/

#ifndef _kp_opt
#define _kp_opt

                                 /* ------- Heizung Aggregat 1 --------------*/
#define OPTIND_ENTRY           0 /* Einzugszone (Trichterstuecktemp.) (Seite 30.0,Zone 0)  */
#define OPTIND_MASS_TEMP       1 /* Massetemperatur (Seite 30.0,Zone 21)                   */
#define OPTIND_SN_TEMP         2 /* Schneckentemeperierung (Seite 30.0 ,Zone 20)           */
#define OPTIND_REG_MOTCONST    3 /* Motorzeitkonstante (Seite 39.1 Zeile 18)               */
#define OPTIND_REG_SHYST       4 /* Schalthyst. und Arbeitspunkt (Seite 39.1 Zeilen 14,15) */
                                 /* ------- Wegmesssystem fuer Aggregate ----*/
#define OPTIND_AGG1_WEGMESS    5 /* Aggregat 1 erhaelt ein Wegmesssystem     */
#define OPTIND_AGG2_WEGMESS    6 /* Aggregat 2 erhaelt ein Wegmesssystem     */
#define OPTIND_AGG3_WEGMESS    7 /* Aggregat 3 erhaelt ein Wegmesssystem     */
#define OPTIND_AGG4_WEGMESS    8 /* Aggregat 4 erhaelt ein Wegmesssystem     */
#define OPTIND_AGG5_WEGMESS    9 /* Aggregat 5 erhaelt ein Wegmesssystem     */
                                 /* ------- Heizung Aggregat 2 --------------*/
#define OPTIND_ENTRY_AGG2     10 /* Einzugszone (Trichterstuecktemp.) Aggregat 2           */
#define OPTIND_MASS_TEMP_AGG2 11 /* Massetemperatur  Aggregat 2                            */
#define OPTIND_SN_TEMP_AGG2   12 /* Schneckentemperierung Aggregat 2                       */
                                 /* ------- Heizung Aggregat 3 --------------*/
#define OPTIND_ENTRY_AGG3     13 /* Einzugszone (Trichterstuecktemp.) Aggregat 3           */
#define OPTIND_MASS_TEMP_AGG3 14 /* Massetemperatur  Aggregat 3                            */
#define OPTIND_SN_TEMP_AGG3   15 /* Schneckentemperierung Aggregat 3                       */
                                 /* ------- Heizung Aggregat 4 --------------*/
#define OPTIND_ENTRY_AGG4     16 /* Einzugszone (Trichterstuecktemp.) Aggregat 4           */
#define OPTIND_MASS_TEMP_AGG4 17 /* Massetemperatur  Aggregat 4                            */
#define OPTIND_SN_TEMP_AGG4   18 /* Schneckentemperierung Aggregat 4                       */
                                 /* ------- Kernzug  ------------------------*/
#define OPTIND_PROG_4CORES    19 /* 4-fach progr.bare Kernzuege                            */
#define OPTIND_PROP_KERN      20 /* Proprotionalkernzug (S.61.0 bis S.62.1 je Z.17 u.18)   */
#define OPTIND_SCREW_NOT_E    21 /* Ausschrauben (S.68 ,Z.2 bis 11) NICHT mit E-Motor!     */
#define OPTIND_SCREW_PROP     22 /* Ausschrauben mit Prop.-Ventile (S.68 ,Z.14 bis 19)     */
#define OPTIND_PROG_CORES     23 /* progr.bare Kernzuege                                   */
                                 /* ------- Heizung Aggregat 5 --------------*/
#define OPTIND_ENTRY_AGG5     24 /* Einzugszone (Trichterstuecktemp.) Aggregat 5           */
#define OPTIND_MASS_TEMP_AGG5 25 /* Massetemperatur  Aggregat 5                            */
#define OPTIND_SN_TEMP_AGG5   26 /* Schneckentemperierung Aggregat 5                       */
                                 /* ------- Heizung Aggregat 6 --------------*/
#define OPTIND_ENTRY_AGG6     27 /* Einzugszone (Trichterstuecktemp.) Aggregat 6           */
#define OPTIND_MASS_TEMP_AGG6 28 /* Massetemperatur  Aggregat 6                            */
#define OPTIND_SN_TEMP_AGG6   29 /* Schneckentemperierung Aggregat 6                       */
                                 /* -------- ROBOT   ------------------------*/
#define OPTIND_ROBOT          30 /* CNC - Robot          ACHTUNG: OPTIONEN   */
#define OPTIND_HANDLING       31 /* Handlinggeraet       SCHLIESSEN SICH     */
#define OPTIND_FHK            32 /* FHK - Schnittstelle  GEGENSEITIG AUS !!! */
                                 /* -----------------------------------------*/
#define OPTIND_NOCHG_MDM      33 /* kein erhoehtes Motordrehmoment fuer KE/S */
                                 /* -------- DV7 fuer KS --------------------*/
#define OPTIND_SPS_DV7        34 /* SPS-Optionsbit fuer DV7 */
                                 /* -------- K-David-Maschine   -------------*/
#define OPTIND_DBPUMP         35 /* Doppel-Pumpe bei K-DavidE-Maschine */
#define OPTIND_STATE_AFTERCORE 36/* Zustand nach Kern ein- bzw. ausgefahren (S.61.0 bis 62.1)*/
#define OPTIND_SN_ENDLAGEREGEL 37/* "Staudruckentlastung nach Plast. aus=0" nach */
                                 /* "Schneckenendlageregelung aus=0" S.40,Z14*/

                                 /* -------- Auswerfer  ---------------------*/
#define OPTIND_AWPLATTENSICH  39 /* Auswerferplattensicherung (Seite 52.0,Zeile 18)        */
#define OPTIND_REST_POS       40 /* Ruhelage Ueberwachung ausschalten (Seite 52.0,Zeile 16)*/
#define OPTIND_EJECT0         41 /* Asw. relat. Nullpkt (Seite 52.0 ,Zeile 4 FXR STANDARD) */
#define OPTIND_EJ_POWER_IQT   42 /* Auswerferdruck Propventil (Seite 52.0 ,Zeile 12)       */
#define OPTIND_HASCO          43 /* Schnellkuppl. f. Asw.-Ruhelage Hasco (Bit EZHASC)      */
#define OPTIND_ADD_EJECT      44 /* Zusatzauswerfer (Seite 53)                             */
#define OPTIND_EJ_POWER_M     45 /* Auswerferkraft 'an Maschine einstellbar'(nur FM)       */
                                 /* -------- Duesenbewegung  ----------------*/
#define OPTIND_AGG_PRESS_AGG5 46 /* Duesenanpressdruck  Aggregat 5                         */
#define OPTIND_AGG_PRESS_AGG6 47 /* Duesenanpressdruck  Aggregat 6                         */
#define OPTIND_JET_AGG5       48 /* Duesengeschwindigkeit Aggregat 5                       */
#define OPTIND_JET_AGG6       49 /* Duesengeschwindigkeit Aggregat 6                       */
#define OPTIND_AGG_PRESS      50 /* Duesenanpressdruck Pg49 Line13 (ACHTUNG nur FXA !!!)   */
#define OPTIND_AGG_PRESS_AGG2 51 /* Duesenanpressdruck  Aggregat 2                         */
#define OPTIND_JET            52 /* Duesengeschw. (S.49 Line11+12; bei FXR+FM auch Line13) */
#define OPTIND_JET_AGG2       53 /* Duesengeschwindigkeit Aggregat 2                       */
#define OPTIND_SN_CHANGE      54 /* Schneckenwechsel (Seite 49 Zeile 14)  STANDARD FXR     */
#define OPTIND_AGG_PRESS_AGG3 55 /* Duesenanpressdruck  Aggregat 3                         */
#define OPTIND_AGG_PRESS_AGG4 56 /* Duesenanpressdruck  Aggregat 4                         */
#define OPTIND_JET_AGG3       57 /* Duesengeschwindigkeit Aggregat 3                       */
#define OPTIND_JET_AGG4       58 /* Duesengeschwindigkeit Aggregat 4                       */
#define OPTIND_DUES_ANPR_MIN  59 /* Duesenanpressdruck gemindert Pg49 Line14 (ACHTUNG nur KDE/KE !!!) */

                                 /* -------- Werkzeugbewegung ---------------*/
#define OPTIND_FSS            60 /* Fss-Wiederholung (Seite 50.0  Zeile 17)                */
#define OPTIND_PRES_TRANS_OPEN_FORCE 61 /* Druckuebersetzter fuer Erhoehte Oeffnungskraft Seite 51.0,Zeile 4 */

#define OPTIND_NEW_AGGSCHALTUNG 63     /* Kommunikation fuer SPS-Freigabe 0 = Standardschliesskraftregelung, 1 = Schliesskraftregelung mit Sensor */
#define OPTIND_SLKRAFTREG_WITH_SENS 64 /* Kommunikation fuer SPS-Freigabe 0 = alte Agregatschaltung, 1 = neue Aggregatschaltung */
                                 /* -------- Betriebsdaten ------------------*/
#define OPTIND_TOOLNR_IST     65 /* Werkzeugnummer-Istwert (Seite 21.0  Zeile 8)           */
#define OPTIND_BRDRV          66 /* BR-Drive (Fehlermeldungs-Seite usw.)                   */
#define OPTIND_PSHOT_COUNTER  67 /* Permaneter Schusszaehler (Seite 21.0, Zeile 18)        */

                                 /* -------- Werkzeug Schnellspannen --------*/
#define OPTIND_FAST_TOOL      70 /* Schnellspannvorrichtung (Seite 56)                     */

                                 /* -------- Schliesszylinder ---------------*/
#define OPTIND_CENTRAL_LUB    75 /* Zentralschmierungsperiode (Seite 15.0  Zeile 7)        */

                                 /* -------- Graphic ------------------------*/
#define OPTIND_PG             80 /* Prozessgraphik (Seite 45.0 bis Seite 47.1)             */
#define OPTIND_SPC            81 /* Statistischer Prozesskontrolle (Seite 90 bis Seite 94) */
#define OPTIND_STD_PG         82 /* Standardprozessgrafik											 */
#define OPTIND_HOSTPFILE      83 /* Leitrechner-Protokollfile (hp<maschinennr>.dat         */
                                 /* -------- Praegen ------------------------*/
#define OPTIND_PRAEGEN1       85 /* Atmen und Praegen (Seite 54.1 Zeilen 2 bis 10)         */
#define OPTIND_PRAEGEN2       86 /* gestaffeltem Schliessdruckaufbau (S.54.1 Line 11 b.19) */

#define OPTIND_BAR_PSI        88 /* 0=bar  1=psi                                           */
#define OPTIND_CELCIUS_KELVIN 89 /* 0=Grad Celcius  1=Grad Kelvin                          */
                                 /* -------- Leitrechner --------------------*/
#define OPTIND_HOST           90 /* Leitrechner-Anschluss (Seite 10  Zeile 11 und 15)      */
#define OPTIND_TERMINAL       91 /* VT-100-Terminal-Anschluss                              */
                                 /* -------- Sonderausstattung --------------*/
#define OPTIND_FREE_LVTEXT    92 /* freieingebare Luftventil-Text            */
#define OPTIND_FREE_BDETEXT   93 /* freieingebarer BDE-Text                  */
#define OPTIND_8SOFTKEYS      94 /* 8 Softkeys statt 6 (Viper)               */
#define OPTIND_FLOPPY         95 /* Floppy-Laufwerk                                        */
#define OPTIND_WEEKCLOCK      96 /* Wochentagsschaltuhr   (Seite 14)                       */
#define OPTIND_SPECPROG       97 /* mit Iscos-Sonderprogrammen auf Datentraeger            */
#define OPTIND_SELECTION_SWITCH 98 /* mit Selektierweiche            */
#define OPTIND_QUALITY_CONTROL  99 /* mit Qualitaetskontrolle        */
#define OPTIND_100       100 /* Freigabe der Hasco Kupplung         */
#define OPTIND_101       101 /* Auswerferplatensicherung            */
#define OPTIND_102       102 /* Ext. dig. Ausg. akt. waehrend Einspritzen */
#define OPTIND_103       103 /* Ext. dig. Ausg. akt. waehrend Plastifizieren */
#define OPTIND_104       104 /* Ausfallwaage, Lichtschranke         */
#define OPTIND_105       105 /* Kuehlwasserbatterie-Abschaltventil  */
#define OPTIND_106       106 /* Forminnendruckabhaengiges Umschalten*/
#define OPTIND_107       107 /* Auswerfer start bei Form oeffen von Hand aktivieren, nur im Handmode aktive */
#define OPTIND_108       108 /* Ext. Zyklusstop via dig. Eingang, nur im Automode aktive */
#define OPTIND_109       109 /* Ext. Aggregate 1,2 via Wochenschaltur Ein/Ausschalten */
#define OPTIND_110       110 /* Getacktetes Foerderband             */
#define OPTIND_111       111 /* Bei Ansprechung Werzeusicherung nicht auto. auffahren */
#define OPTIND_112       112 /* intelligente Gelenksystemschmierung */
#define OPTIND_113       113 /* Conair Peripheriegeraete */
#define OPTIND_114       114 /* Mit=0/ohne=1 Formhoehenzustellmotor */
#define OPTIND_115       115 /* Mit 5. Luftventil Seite 69 */
#define OPTIND_116       116 /* Mit Seite 67  */
#define OPTIND_117       117 /*  */
#define OPTIND_118       118 /*  */
#define OPTIND_119       119 /*  */

#define   OPTIND_EINSPRP    120
#define   OPTIND_START_AUSW 121
#define   OPTIND_AUSWEND    122
#define   OPTIND_BDE        123
#define   OPTIND_INDRUCK    124
#define   OPTIND_HYDRT      125
#define   OPTIND_DROPBAR    126
#define   OPTIND_BOSCH      127
#define   OPTIND_1TRIT      128 
#define   OPTIND_2TRIT      129
#define   OPTIND_AUSWPLAT   130
#define   OPTIND_AUSWMECH   131
#define   OPTIND_AUSWPVE    132
#define   OPTIND_TSS        133
#define   OPTIND_DREH       134
#define   OPTIND_INTRU      135
#define   OPTIND_STEINSPR   136
#define   OPTIND_ROBSTROKE  137
#define   OPTIND_CONVERSION 138
#define   OPTIND_AUSWPAGE   139
#define   OPTIND_KERN1      140
#define   OPTIND_KERN2      141
#define   OPTIND_KERN3      142
#define   OPTIND_KERN4      143
#define   OPTIND_KERN_ALL   144
#define   OPTIND_SCHNECK_ABS 145
#define   OPTIND_KASKADE    146
#define   OPTIND_KZAK       147
#define   OPTIND_FIL1       148
#define   OPTIND_FIL2       149
#define   OPTIND_HDFIL      150
#define   OPTIND_RUETTLER   151
#define   OPTIND_SPRPRAEG   152
#define   OPTIND_TRAEG      153      /* 13.11.92 */

#define   OPTIND_PLASTIWE   160      /* 27.11.92 Sonder AXO, HEBECO*/

/*Makros zum Zugriff auf die Kundenpromparameter aus der Datenstruktur heraus*/
#define OPTION_REST_POS_       (OptionTab[OPTIND_REST_POS])
#define OPTION_ENTRY_          (OptionTab[OPTIND_ENTRY])
#define OPTION_MASS_TEMP_      (OptionTab[OPTIND_MASS_TEMP])
#define OPTION_EJECT0_         (OptionTab[OPTIND_EJECT0])
#define OPTION_FSS_            (OptionTab[OPTIND_FSS])
#define OPTION_TOOLNR_IST_     (OptionTab[OPTIND_TOOLNR_IST])
#define OPTION_8SOFTKEYS_      (OptionTab[OPTIND_8SOFTKEYS])
#define OPTION_FLOPPY_         (OptionTab[OPTIND_FLOPPY])
#define OPTION_HOST_           (OptionTab[OPTIND_HOST])
#define OPTION_HOSTPFILE_      (OptionTab[OPTIND_HOSTPFILE])
#define OPTION_AGG_PRESS_      (OptionTab[OPTIND_AGG_PRESS])
#define OPTION_EJ_POWER_M_     (OptionTab[OPTIND_EJ_POWER_M])
#define OPTION_EJ_POWER_IQT_   (OptionTab[OPTIND_EJ_POWER_IQT])
#define OPTION_HASCO_          (OptionTab[OPTIND_HASCO])
#define OPTION_PROP_KERN_      (OptionTab[OPTIND_PROP_KERN])
#define OPTION_SCREW_NOT_E_    (OptionTab[OPTIND_SCREW_NOT_E])
#define OPTION_SCREW_PROP_     (OptionTab[OPTIND_SCREW_PROP])
#define OPTION_WEEKCLOCK_      (OptionTab[OPTIND_WEEKCLOCK])
#define OPTION_SN_TEMP_        (OptionTab[OPTIND_SN_TEMP])
#define OPTION_PG_             (OptionTab[OPTIND_PG])
#define OPTION_ADD_EJECT_      (OptionTab[OPTIND_ADD_EJECT])
#define OPTION_FAST_TOOL_      (OptionTab[OPTIND_FAST_TOOL])
#define OPTION_CENTRAL_LUB_    (OptionTab[OPTIND_CENTRAL_LUB])
#define OPTION_ROBOT_          (OptionTab[OPTIND_ROBOT])
#define OPTION_SPC_            (OptionTab[OPTIND_SPC])
#define OPTION_JET_            (OptionTab[OPTIND_JET])
#define OPTION_SN_CHANGE_      (OptionTab[OPTIND_SN_CHANGE])
#define OPTION_ENTRY_AGG2_     (OptionTab[OPTIND_ENTRY_AGG2])
#define OPTION_MASS_TEMP_AGG2_ (OptionTab[OPTIND_MASS_TEMP_AGG2])
#define OPTION_SN_TEMP_AGG2_   (OptionTab[OPTIND_SN_TEMP_AGG2])
#define OPTION_DBPUMP		    (OptionTab[OPTIND_DBPUMP])
#define OPTION_ENTRY_AGG3_     (OptionTab[OPTIND_ENTRY_AGG3])
#define OPTION_MASS_TEMP_AGG3_ (OptionTab[OPTIND_MASS_TEMP_AGG3])
#define OPTION_SN_TEMP_AGG3_   (OptionTab[OPTIND_SN_TEMP_AGG3])
#define OPTION_ENTRY_AGG4_     (OptionTab[OPTIND_ENTRY_AGG4])
#define OPTION_MASS_TEMP_AGG4_ (OptionTab[OPTIND_MASS_TEMP_AGG4])
#define OPTION_SN_TEMP_AGG4_   (OptionTab[OPTIND_SN_TEMP_AGG4])
#define OPTION_SPS_DV7_        (OptionTab[OPTIND_SPS_DV7])
#define OPTION_ENTRY_AGG5_     (OptionTab[OPTIND_ENTRY_AGG5])
#define OPTION_MASS_TEMP_AGG5_ (OptionTab[OPTIND_MASS_TEMP_AGG5])
#define OPTION_SN_TEMP_AGG5_   (OptionTab[OPTIND_SN_TEMP_AGG5])
#define OPTION_ENTRY_AGG6_     (OptionTab[OPTIND_ENTRY_AGG6])
#define OPTION_MASS_TEMP_AGG6_ (OptionTab[OPTIND_MASS_TEMP_AGG6])
#define OPTION_SN_TEMP_AGG6_   (OptionTab[OPTIND_SN_TEMP_AGG6])
#define OPTION_AGG1_WEGMESS_   (OptionTab[OPTIND_AGG1_WEGMESS])
#define OPTION_AGG2_WEGMESS_   (OptionTab[OPTIND_AGG2_WEGMESS])
#define OPTION_AGG3_WEGMESS_   (OptionTab[OPTIND_AGG3_WEGMESS])
#define OPTION_AGG4_WEGMESS_   (OptionTab[OPTIND_AGG4_WEGMESS])
#define OPTION_AGG5_WEGMESS_   (OptionTab[OPTIND_AGG5_WEGMESS])
#define OPTION_AWPLATTENSICH   (OptionTab[OPTIND_AWPLATTENSICH])
#define OPTION_FREE_BDETEXT    (OptionTab[OPTIND_FREE_BDETEXT])
#define OPTION_FREE_LVTEXT     (OptionTab[OPTIND_FREE_LVTEXT])
#define OPTION_BRDRV           (OptionTab[OPTIND_BRDRV])  
#define OPTION_BAR_PSI         (OptionTab[OPTIND_BAR_PSI])
#define OPTION_CELCIUS_KELVIN  (OptionTab[OPTIND_CELCIUS_KELVIN])
#define OPITON_PSHOT_COUNTER   (OptionTab[OPTIND_PSHOT_COUNTER])
#define OPTION_PRES_TRANS_OPEN_FORCE (OptionTab[OPTIND_PRES_TRANS_OPEN_FORCE])

#endif      /* #ifndef _kp_opt */

