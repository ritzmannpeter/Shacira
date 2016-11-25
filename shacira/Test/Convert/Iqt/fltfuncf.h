/****************************************************************************
*
*
*         FLTFUNCF.H
*
*  HISTORY:
*     8.10.90 -SF-     Implementierung
*    03.12.90 -TSchw-  Flt_XSNAUSW deklariert
*    11.12.90 -SF-     Roboter-Funktionen eingebaut
*    22.01.91 -SF-     Flt_ROB_MULT_FIX entfernt
*    24.01.91 -SF-     Flt_ROB_ACT_STEP entfernt
*    26.03.91 -SF-     Flt_XSVZU1-2 und Flt_XSVAUF1-3 entfernt
*    29.05.91 -SF-     Flt_XREG777 entfernt
*                      Flt_XSSDOS2, Flt_XSNRUK2, Flt_XSSRUK2, Flt_XSNAGG2
*                      Flt_XSFAGG2, Flt_XSNPHM2, Flt_XREG775_2, Flt_XREG776_2,
*                      Flt_INJ_PRES_SOLL_2, Flt_SWITCH_PRES_TOL_2 sind neu
*    19.11.91 -PR-     Ergaenzugen fuer das 10-Stufen-Spritzverfahren ein-
*                      gebaut: Filterfunktion InjTime
*                              Telegramm-Hook-Funktion SetActInjStage
*    11.12.91 -TSchw-  Flt_XSNWKZS eingebaut
*    21.02.92 -PR-     EWIKON-Funktionen eingebaut
*    03.05.93 -TSchw-  Flt_XSSUM21 eingebaut
*    15.04.94 -MBa-    HeatOptmode u. OptmodeRegler eingebaut
*    15.01.96 -HAns-   PFlt_XSNPHM3 und PFlt_XSNPHM4 eingebaut
*    22.01.96 -HAns-   PFlt_XREG775_3,4 und PFlt_XREG776_3,4 eingebaut
*    30.01.96 -HAns-   PFlt_INJ_PRES_SOLL_3,4 und PFlt_SWITCH_PRES_TOL_3,4
*                      eingebaut
*    13-09-96 -PR-     Filterfunktionsdeklarationen fuer die frei progr.baren
*                      Kernzuege.
*    05.12.96 -HAns-   PFlt_NRM_WV_HS, PFlt_HydrToSpec und PFlt_SpecToHydr
*                      eingebaut.
*                      PFlt_WayToVol und PFlt_VolToWay eingebaut.
*    10.12.96 -HAns-   PFlt_NRM_WV_HS, PFlt_HydrToSpecSoll,PFlt_HydrToSpecIst
*                      und PFlt_SpecToHydrSoll eingebaut.
*                      PFlt_WayToVolSoll, PFlt_WayToVolIst und PFlt_VolToWaySoll
*                      eingebaut.
*    10.12.96 -HAns-   Flt_INJ_PRES_SOLL - Flt_INJ_PRES_SOLL4
*                      Flt_SWITCH_PRES_TOL - Flt_SWITCH_PRES_TOL4
*                      und Flt_INJ_SPEED_SOLL herausgenommen, da
*                      unnoetig.                                
*    17.01.97 -HAns-   PFlt_Blasluft100To10 und PFlt_Blasluft10To100 eingebaut.
*    24.01.97 -HAns-   PFlt_DnToDvSoll und PFlt_DvToDnSoll eingebaut.
*    17.02.97 -HAns-   Flt_WayToVolSoll in Flt_WHToVS_Soll und
*                      Flt_VolToWaySoll in Flt_VSToWH_Soll umbenannt, sowie
*                      Flt_HydrToSpecSoll und Flt_SpecToHydrSoll herausgenommen.
*    04.03.97 -HAns-   PFlt_POLSTER1 bis 4 eingebaut.
*    13.03.97 -PR-     Funktion Flt_MaxToolStroke eingefuehrt
*    20.03.97 -HAns-   PFlt_ITKUHL herausgenommen, da nur in ISCOS-Datenstructur
*                      vorhanden.
*    27.11.97 -HAns-   PFlt_DMView aufgenommen.
*    07.01.98 -GhG-    Flt_WayVol_PLIndName aufgenommen.
*    06.02.98 -HAns-   Flt_EinParSer, Flt_EinReihenfolge, Flt_AggParSer,
*                      Flt_AggReihenfolge unc Flt_PGTolChan eingebaut.
*	 09.04.99 -TSchw-  PGAggregat und PGActCurves eingefuegt.
*    20.04.99 -TSchw-  Flt_XPG_YMAX eingefuegt.
*    28.07.99 -TSchw-  Flt_ColorPalette eingefuegt (aus color.c)
*    06.06.01 -HAns-   Flt_RegZero eingefuegt.
*    05.07.01 -HA-     Flt_XSSFAUF neu eingefügt
*    21.11.01 -HA-     PFlt_VentilNrLine eingefuegt.
*    22.11.01 -HA-     PFlt_VentilValueTyp eingefuegt.
*    23.04.02 -HA-     Flt_AnzPlaststufe1 und Flt_AnzPlaststufe2 eingefuegt.
*    26.06.02 -HA-     Flt_POLSTER5,6 ; Flt_XREG775_5,6 und Flt_XREG776_5,6 eingefuegt.
*    06.12.02 -HA-     Flt_OptInd61Check eingefuegt.
*    06.03.03 -HAns-   PFlt_NRM_HS eingefuegt.
*    08.05.03 -HAns-   PFlt_NRM_HS_WkzInnen eingefuegt.
*
****************************************************************************/

/* Alle Filterfunktions-Deklarationen */

#ifndef _fltfuncf
#define _fltfuncf

/* ehemalige Kernprogrammfunktionen */
extern int  KlickFltFunc      (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  SPCFltFunc        (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PGCursor          (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PGXView           (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PGValue           (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PGMax             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PhaseInjTime      (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  Flt_WClockSetTime (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  Flt_WClockSwitch  (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  Flt_PRINT         (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PGInfo            (UWORD, UWORD, long, UWORD, UWORD, UWORD);
extern int  PGComp            (UWORD, UWORD, long, UWORD, UWORD, UWORD);

int HeatFltFunc               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSFZUHK               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSSAUS2               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSSAUS3               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNPHMX               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNPHM2               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG775               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG775_2             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG776               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG776_2             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNLUF1               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNLUF2               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNLUF3               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNLUF4               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNAUSW               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNWKZS               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_ROB_PAR               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_ROB_READ              (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_ROB_WRITE             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int InjTime                   (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Tabs                      (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int HeatChanIst               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int HeatOptmode               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int OptmodeRegler             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_Production            (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XPOJSS                (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XPOJES                (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_HOST_START_ORDER      (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_HOST_STOP_ORDER       (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_HOST_REJECTS          (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNPHM3               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XSNPHM4               (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG775_3             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG776_3             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG775_4             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int Flt_XREG776_4             (UWORD, UWORD, long, UWORD, UWORD, UWORD);
int far Flt_CoreLines			(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_ident					(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_number				(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_info					(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_p						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_v						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_S						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_s1						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_tA						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_L						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_tV						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_s2						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_M						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_tR						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_s3						(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_lineno				(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_Startconds			(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_Movements			(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_Options				(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far FltINIPOS					(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far FltENDPOS					(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_StartcondText		(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_MovementText		(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_OptionText			(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_Aggregat				(UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_StartWork     (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_StopWork      (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_Cursor        (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_Xview         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_Max           (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_Value         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_Maxx          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_Maxy          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_WV_HS         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_WHToVS_Soll       (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_VSToWH_Soll       (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_WayToVolIst       (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_HydrToSpecIst     (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_Blasluft100To10   (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_Blasluft10To100   (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_DnToDvSoll        (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_DvToDnSoll        (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_POLSTER1          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_POLSTER2          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_POLSTER3          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_POLSTER4          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_MaxToolStroke     (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_DMView            (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far PGAggregat            (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far PGActCurves           (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XPG_YMAX          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_WayVol_PLIndName  (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_EinParSer         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_EinReihenfolge    (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_AggParSer         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_AggReihenfolge    (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_PGTolChan         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_ColorPalette      (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_RegZero           (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XSSFAUF           (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_VentilNrLine      (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_VentilValueTyp    (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_AnzPlaststufe1    (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_AnzPlaststufe2    (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_POLSTER5          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_POLSTER6          (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XREG775_5         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XREG776_5         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XREG775_6         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XREG776_6         (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XSNPHM5           (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_XSNPHM6           (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_OptInd61Check     (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_HS            (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);
int far Flt_NRM_HS_WkzInnen   (UWORD ctrl, UWORD id, long val, UWORD ind1, UWORD ind2, UWORD ind3);

#endif      /* #ifndef _fltfuncf */
