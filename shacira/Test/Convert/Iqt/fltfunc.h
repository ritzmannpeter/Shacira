/****************************************************************************
*
*
*         FLTFUNC.H
*
*  HISTORY:
*     04.07.90 -TSchw-  PFlt_XSSAUSR entfernt
*      8.10.90 -SF-     Name dieser Datei umbenannt (flttab.h -> fltfunc.h)
*     03.12.90 -TSchw-  PFlt_XSNAUSW eingefuegt
*     11.12.90 -SF-     Roboter-Funktionen eingebaut
*     22.01.91 -SF-     Flt_ROB_MULT_FIX entfernt
*     18.02.91 -TSchw-  Flt_XRSON3_9 eingebaut
*     24.01.91 -SF-     Flt_ROB_ACT_STEP entfernt
*     26.03.91 -SF-     Flt_XSVZU1-2 und Flt_XSVAUF1-3 entfernt
*     29.05.91 -SF-     Flt_XREG777 entfernt
*                       Flt_XSSDOS2, Flt_XSNRUK2, Flt_XSSRUK2, Flt_XSNAGG2
*                       Flt_XSFAGG2, Flt_XSNPHM2, Flt_XREG775_2, Flt_XREG776_2,
*                       Flt_INJ_PRES_SOLL_2, Flt_SWITCH_PRES_TOL_2 sind neu
*     19.11.91 -PR-     Ergaenzugen fuer das 10-Stufen-Spritzverfahren ein-
*                       gebaut: Konstante fuer Filterfunktion InjTime definiert
*     11.12.91 -TSchw-  PFlt_XSNWKZS eingebaut
*     21.02.92 -PR-     EWIKON-Funktionen eingebaut
*     03.05.93 -TSchw-  PFlt_XSSUM21 eingebaut
*     15.04.94 -MBa-    PHeatOptmode u. POptmodeRegler  eingebaut
*     15.01.96 -HAns-   PFlt_XSNPHM3 und PFlt_XSNPHM4 eingebaut
*     22.01.96 -HAns-   PFlt_XREG775_3,4 und PFlt_XREG776_3,4 eingebaut
*     30.01.96 -HAns-   PFlt_INJ_PRES_SOLL_3,4 und PFlt_SWITCH_PRES_TOL_3,4
*                       eingebaut
*     13-09-96 -PR-     Filterfunktionsindices fuer die frei progr.baren 
*                       Kernzuege.
*     06.12.96 -HAns-   PFlt_NRM_WV_HS, PFlt_HydrToSpecSoll,PFlt_HydrToSpecIst
*                       und PFlt_SpecToHydrSoll eingebaut.
*                       PFlt_WayToVolSoll, PFlt_WayToVolIst und PFlt_VolToWaySoll
*                       eingebaut.
*     10.12.96 -HAns-   Flt_INJ_PRES_SOLL - Flt_INJ_PRES_SOLL4
*                       Flt_SWITCH_PRES_TOL - Flt_SWITCH_PRES_TOL4
*                       und Flt_INJ_SPEED_SOLL herausgenommen, da
*                       unnoetig.                                
*     17.01.97 -HAns-   PFlt_Blasluft100To10 und PFlt_Blasluft10To100 eingebaut.
*     24.01.97 -HAns-   PFlt_DnToDvSoll und PFlt_DvToDnSoll eingebaut.
*     17.02.97 -HAns-   Flt_WayToVolSoll in Flt_WHToVS_Soll und
*                       Flt_VolToWaySoll in Flt_VSToWH_Soll umbenannt, sowie
*                       Flt_HydrToSpecSoll und Flt_SpecToHydrSoll herausgenommen.
*     04.03.97 -HAns-   PFlt_POLSTER1 bis 4 eingebaut.
*     14.03.97 -HAns-   PFlt_MaxToolStroke eingebaut.
*     20.03.97 -HAns-   PFlt_ITKUHL herausgenommen, da nur in ISCOS-Datenstructur
*                       vorhanden.
*     27.11.97 -HAns-   PFlt_DMView aufgenommen.
*	  09.04.99 -TSchw-  PGAggregat und PGActCurves eingefuegt.
*	  20.04.99 -TSchw-  PFlt_XPG_YMAX eingefuegt.
*     28.07.99 -TSchw-  PFlt_ColorPalette eingefuegt
*
****************************************************************************/

/* Dieses H-File enthaelt Define's fuer alle Funktionen, die in der FltFuncTab
   vorhanden sind. Die Define's werden in den Registertabellen verwendet. */

#ifndef _fltfunc
#define _fltfunc

/* ehemalige Kernprogrammfunktionen */
#define PKlickFltFunc            1
#define PSPCFltFunc              2
#define PPGCursor                3
#define PPGXView                 4
#define PPGValue                 5
#define PPGMax                   6
#define PPhaseInjTime            7
#define PFlt_WClockSetTime       8
#define PFlt_WClockSwitch        9
#define PFlt_PRINT              10
#define PPGInfo                 11
#define PPGComp                 12
#define PHeatFltFunc            13
#define PFlt_XSFZUHK            14
#define PFlt_XSSAUS2            15
#define PFlt_XSSAUS3            16
#define PFlt_XSNPHMX            17
#define PFlt_XSNPHM2            18
#define PFlt_XREG775            19
#define PFlt_XREG775_2          20
#define PFlt_XREG776            21
#define PFlt_XREG776_2          22
#define PFlt_XSNLUF1            23
#define PFlt_XSNLUF2            24
#define PFlt_XSNLUF3            25
#define PFlt_XSNLUF4            26
#define PFlt_XSNAUSW            27
#define PFlt_XSNWKZS            28
#define PFlt_ROB_PAR            29
#define PFlt_ROB_READ           30
#define PFlt_ROB_WRITE          31
#define PTabs                   32
#define PHeatChanIst            33
#define PHeatOptmode            34
#define POptmodeRegler          35
#define PFlt_Production			  36
#define PFlt_XPOJSS				  37
#define PFlt_XPOJES				  38
#define PFlt_HOST_START_ORDER	  39
#define PFlt_HOST_STOP_ORDER	  40
#define PFlt_HOST_REJECTS       41
#define PFlt_XSNPHM3            42
#define PFlt_XSNPHM4            43
#define PFlt_XREG775_3          44
#define PFlt_XREG776_3          45
#define PFlt_XREG775_4          46
#define PFlt_XREG776_4          47

#define CORE_BASE_INDEX         48
#define PFlt_CoreLines			  (CORE_BASE_INDEX+0)
#define PFlt_ident				  (CORE_BASE_INDEX+1)
#define PFlt_number				  (CORE_BASE_INDEX+2)
#define PFlt_info					  (CORE_BASE_INDEX+3)
#define PFlt_p						  (CORE_BASE_INDEX+4)
#define PFlt_v						  (CORE_BASE_INDEX+5)
#define PFlt_S						  (CORE_BASE_INDEX+6)
#define PFlt_s1					  (CORE_BASE_INDEX+7)
#define PFlt_tA					  (CORE_BASE_INDEX+8)
#define PFlt_L						  (CORE_BASE_INDEX+9)
#define PFlt_tV					  (CORE_BASE_INDEX+10)
#define PFlt_s2					  (CORE_BASE_INDEX+11)
#define PFlt_M						  (CORE_BASE_INDEX+12)
#define PFlt_tR					  (CORE_BASE_INDEX+13)
#define PFlt_s3					  (CORE_BASE_INDEX+14)
#define PFlt_lineno				  (CORE_BASE_INDEX+15)
#define PFlt_Startconds			  (CORE_BASE_INDEX+16)
#define PFlt_Movements 			  (CORE_BASE_INDEX+17)
#define PFlt_Options   			  (CORE_BASE_INDEX+18)
#define PFltINIPOS				  (CORE_BASE_INDEX+19)
#define PFltENDPOS				  (CORE_BASE_INDEX+20)
#define PFlt_StartcondText		  (CORE_BASE_INDEX+21)
#define PFlt_MovementText		  (CORE_BASE_INDEX+22)
#define PFlt_OptionText			  (CORE_BASE_INDEX+23)
#define PFlt_Aggregat			  (CORE_BASE_INDEX+24)
#define PFlt_NRM_StartWork		  (CORE_BASE_INDEX+25)
#define PFlt_NRM_StopWork		  (CORE_BASE_INDEX+26)
#define PFlt_NRM_Cursor			  (CORE_BASE_INDEX+27)
#define PFlt_NRM_Xview			  (CORE_BASE_INDEX+28)
#define PFlt_NRM_Max				  (CORE_BASE_INDEX+29)
#define PFlt_NRM_Value			  (CORE_BASE_INDEX+30)
#define PFlt_NRM_Maxx			  (CORE_BASE_INDEX+31)
#define PFlt_NRM_Maxy			  (CORE_BASE_INDEX+32)
#define PFlt_NRM_WV_HS          (CORE_BASE_INDEX+33)
#define PFlt_WHToVS_Soll        (CORE_BASE_INDEX+34)
#define PFlt_VSToWH_Soll        (CORE_BASE_INDEX+35)
#define PFlt_WayToVolIst        (CORE_BASE_INDEX+36)
#define PFlt_HydrToSpecIst      (CORE_BASE_INDEX+37)
#define PFlt_Blasluft100To10    (CORE_BASE_INDEX+38)
#define PFlt_Blasluft10To100    (CORE_BASE_INDEX+39)
#define PFlt_DnToDvSoll         (CORE_BASE_INDEX+40)
#define PFlt_DvToDnSoll         (CORE_BASE_INDEX+41)
#define PFlt_POLSTER1           (CORE_BASE_INDEX+42)
#define PFlt_POLSTER2           (CORE_BASE_INDEX+43)
#define PFlt_POLSTER3           (CORE_BASE_INDEX+44)
#define PFlt_POLSTER4           (CORE_BASE_INDEX+45)
#define PFlt_MaxToolStroke      (CORE_BASE_INDEX+46)
#define PFlt_DMView             (CORE_BASE_INDEX+47)
#define PPGAggregat             (CORE_BASE_INDEX+48)
#define PPGActCurves            (CORE_BASE_INDEX+49)
#define PFlt_XPG_YMAX           (CORE_BASE_INDEX+50)

#define FILTER_BASE_INDEX (CORE_BASE_INDEX+51)
#define PFlt_ColorPalette       (FILTER_BASE_INDEX+0)

#define PFlt_NRM_HS_WkzInnen     0
#define PFlt_NRM_HS              0
#define PFlt_WayVol_PLIndName    0


#endif      /* #ifndef _fltfunc */
