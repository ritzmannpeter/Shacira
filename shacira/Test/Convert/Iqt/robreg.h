/*********************************************************************
*                                                                    *
*  MODUL-NAME: ROBREG.H                                              *
*                                                                    *
*  BESCHREIBUNG:                                                     *
*     Roboter-Register                                               *
*                                                                    *
*  HISTORY:                                                          *
*     20.02.91   -SF-   Ende der Implementierung                     *
*      3.04.91   -SF-   ROB_MODE auf 21499 stat auf 21510 definiert  *
*                                                                    *
*********************************************************************/

#define ROB_MODE                 21499       /* Betriebsart (0-3) */
#define ROB_PAR_POINT1           21500       /* Parameter Punkt X */
#define ROB_PAR_POINT2           21501       /* Parameter Punkt Y */
#define ROB_PAR_POINT3           21502       /* Parameter Punkt Z */
#define ROB_PAR_POINT4           21503       /* Parameter Punkt 4.A */
#define ROB_PAR_POINT5           21504       /* Parameter Punkt 5.A */
#define ROB_PAR_V                21505       /* Parameter Geschw. */
#define ROB_PAR_D                21506       /* Parameter Dezimal */
#define ROB_PAR_G                21507       /* Parameter Ganz */

#define ROB_STEP_FLAG            21508       /* Stepbetrieb ein/aus */
#define ROB_SPEED                21509       /* red. Geschwindigkeit */

/* ACHTUNG: die folgenden 48 Register muessen durchgehend numeriert sein */
#define ROB_MACRO_STEP_M1        21511       /* x. Macro des jew. Programms */
#define ROB_MACRO_STEP_M2        21512
#define ROB_MACRO_STEP_M3        21513
#define ROB_MACRO_STEP_M4        21514
#define ROB_MACRO_STEP_M5        21515
#define ROB_MACRO_STEP_M6        21516
#define ROB_MACRO_STEP_M7        21517
#define ROB_MACRO_STEP_M8        21518
#define ROB_MACRO_STEP_M9        21519
#define ROB_MACRO_STEP_M10       21520
#define ROB_MACRO_STEP_M11       21521
#define ROB_MACRO_STEP_M12       21522

#define ROB_MACRO_STEP_P1_1      21523       /* 1. Parameter des x. Macros */
#define ROB_MACRO_STEP_P1_2      21524
#define ROB_MACRO_STEP_P1_3      21525
#define ROB_MACRO_STEP_P1_4      21526
#define ROB_MACRO_STEP_P1_5      21527
#define ROB_MACRO_STEP_P1_6      21528
#define ROB_MACRO_STEP_P1_7      21529
#define ROB_MACRO_STEP_P1_8      21530
#define ROB_MACRO_STEP_P1_9      21531
#define ROB_MACRO_STEP_P1_10     21532
#define ROB_MACRO_STEP_P1_11     21533
#define ROB_MACRO_STEP_P1_12     21534

#define ROB_MACRO_STEP_P2_1      21535       /* 2. Parameter des x. Macros */
#define ROB_MACRO_STEP_P2_2      21536
#define ROB_MACRO_STEP_P2_3      21537
#define ROB_MACRO_STEP_P2_4      21538
#define ROB_MACRO_STEP_P2_5      21539
#define ROB_MACRO_STEP_P2_6      21540
#define ROB_MACRO_STEP_P2_7      21541
#define ROB_MACRO_STEP_P2_8      21542
#define ROB_MACRO_STEP_P2_9      21543
#define ROB_MACRO_STEP_P2_10     21544
#define ROB_MACRO_STEP_P2_11     21545
#define ROB_MACRO_STEP_P2_12     21546

#define ROB_MACRO_STEP_P3_1      21547       /* 3. Parameter des x. Macros */
#define ROB_MACRO_STEP_P3_2      21548
#define ROB_MACRO_STEP_P3_3      21549
#define ROB_MACRO_STEP_P3_4      21550
#define ROB_MACRO_STEP_P3_5      21551
#define ROB_MACRO_STEP_P3_6      21552
#define ROB_MACRO_STEP_P3_7      21553
#define ROB_MACRO_STEP_P3_8      21554
#define ROB_MACRO_STEP_P3_9      21555
#define ROB_MACRO_STEP_P3_10     21556
#define ROB_MACRO_STEP_P3_11     21557
#define ROB_MACRO_STEP_P3_12     21558

/* Multiplex-Register */
#define ROB_MULT_PGM             21559       /* Programme multiplexen */
#define ROB_MULT_PAR_P           21560       /* Punkt-Parameter multiplexen */
#define ROB_MULT_FIX             21561       /* Fix-Parameter multiplexen */
#define ROB_INOUT_TYPE           21562       /* Typ der Ein-/Ausgaenge */

/* Istwerte */
#define ROB_ACT_P1               21563       /* Aktuelle Punkt X */
#define ROB_ACT_P2               21564       /* Aktuelle Punkt Y */
#define ROB_ACT_P3               21565       /* Aktuelle Punkt Z */
#define ROB_ACT_P4               21566       /* Aktuelle Punkt 4.A */
#define ROB_ACT_P5               21567       /* Aktuelle Punkt 5.A */
#define ROB_ACT_VAR              21568       /* Aktuelle Werte:
                                                Index 0 = Programmstand
                                                Index 1 = Betriebsart
                                                Index 2 = Satznummer
                                                Index 3 = Programm-Nr.
                                                Index 4 = Macro-Nr.  */

#define ROB_INOUT_BYTE1_16       21569       /* Byte 1-16 */
#define ROB_INOUT_BYTE17_32      21570       /* Byte 17-32 */
