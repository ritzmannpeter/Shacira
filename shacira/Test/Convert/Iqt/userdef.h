/*.SM.***********************************************************************
*
*  USERDEF.H
*
**********************************************************************
*
*  --- HISTORY ---
*  18.02.91   -PR-         Implementiert
*  24.05.91   -PR-         Erweiterung
*  19.11.91   -PR-         Fuer 10-Stufen-Spritzverfahren in Malterdingen
*                          uebernommen
*  21.02.92   -PR-         EWIKON-Definitionen eingebaut
*  25.02.98   -TSchw-      CONSTVAL in CONSTVAL umbenannt, da CONSTVAL in
*                          den Windows-Includefiles benutzt wird
*  14.02.01   -HAns-       Einzulesende Datentraegertyps eingefuegt.
*  31.01.02 -HA-     Define DOPTIONINVERT und DOPTION eingefuegt.
*                    Define REGLER_INTO_BLOCK und REGLER_OUT_BLOCK eingefuegt.
*                    Define HZDL_TO_PLC1 und HZDL_TO_PLC2 eingefuegt.
*                    Define PLC1 und PLC2 eingefuegt.
*  19.04.02 -HA-     Eintragungen fuer Darstellung PSI/BAR, WEG/VOUMEN usw. eingefuegt
*
*
*.EM.***********************************************************************/

#ifndef _userdef
#define _userdef

/* Definitionen fÅr den Zugriff auf die Parametertabelle
 */
extern const UWORD ParamTab [];
#define Par0_ ParamTab [ParamIndex+0]
#define Par1_ ParamTab [ParamIndex+1]
#define Par2_ ParamTab [ParamIndex+2]
#define Par3_ ParamTab [ParamIndex+3]
#define Par4_ ParamTab [ParamIndex+4]
#define Par5_ ParamTab [ParamIndex+5]
#define Par6_ ParamTab [ParamIndex+6]
#define Par7_ ParamTab [ParamIndex+7]
#define Par8_ ParamTab [ParamIndex+8]
#define Par9_ ParamTab [ParamIndex+9]
#define Par10_ ParamTab [ParamIndex+10]

/***********************************************************************/
/*                                                                     */
/* Erweitertes Parameterformat Extended Format (EF)                    */
/*                                                                     */
/*   15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0   BitNr           */
/*  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                  */
/*  |Parameter 4|Parameter 3|Parameter 2|Parameter 1|                  */
/*                                                                     */
/*  FÅr jeden Parameter:                                               */
/*                                                                     */
/*      | Bit 3   | Bit 2   | Bit 1   | Bit 0   |                      */
/*      | Vorz.   |Adress.  |Paramtab.| Frei    |                      */
/*                                                                     */
/*      0 pos.     0 direkt   0        frei ver-                       */
/*      1 neg.     1 indirekt 1 Param. fÅgbar                          */
/*                              tab.                                   */
/*                                                                     */
/***********************************************************************/
#define POSITIV    0x0000
#define NEG        0x0008
#define CONSTVAL   0x0000
#define REG        0x0004
#define PARAMTABLE 0x0002
#define STDFORMAT  0x0000  /*POSITIV,CONSTVAL*/

/*   Makros zum Setzen des Formats (aus EffizienzgrÅnden 4 verschiedene)
 */
/*   Set Extended Format SEF
 */
#define SEF1(W)  (W)
#define SEF2(W)  ((W)<<4)
#define SEF3(W)  ((W)<<8)
#define SEF4(W)  ((W)<<12)

/*   Makros zum Abfragen des Formats (aus EffizienzgrÅnden 4 verschiedene)
 */
/* Get Extended Format Sign GEFx_SIGN (x = 1,..,4)
 * Liefert das Vorzeichen fÅr den Parameter x 
 * GEFx_SIGN(W) Ó {POSITIV,NEG} (Bit 3)
 */
#define GEF1_SIGN(W)   (W&0x0008)
#define GEF2_SIGN(W)   ((W>>4)&0x0008)
#define GEF3_SIGN(W)   ((W>>8)&0x0008)
#define GEF4_SIGN(W)   ((W>>12)&0x0008)

/* Get Extended Format Indirection GEFx_ADDR (x = 1,..,4)
 * Liefert die Adressierungsart fÅr den Parameter x 
 * GEFx_ADDR(W) Ó {CONSTVAL,REG} (Bit 2)
 */
#define GEF1_ADDR(W)   (W&0x0004)
#define GEF2_ADDR(W)   ((W>>4)&0x0004)
#define GEF3_ADDR(W)   ((W>>8)&0x0004)
#define GEF4_ADDR(W)   ((W>>12)&0x0004)

/* Get Extended Format Tableadress GEFx_TABLEADDRESS (x = 1,..,4)
 * Liefert die Adressierungsart Parametertabelle fÅr den Parameter x 
 * GEFx_TABLEADDRESS(W) Ó {0x0000,TABLEADDRESS} (Bit 1)
 */
#define GEF1_TABLEADDRESS(W)  (W&0x0002)
#define GEF2_TABLEADDRESS(W)  ((W>>4)&0x0002)
#define GEF3_TABLEADDRESS(W)  ((W>>8)&0x0002)
#define GEF4_TABLEADDRESS(W)  ((W>>12)&0x0002)

/* Get Extended Format Free GEFx_FREE (x = 1,..,4)
 * Liefert den Wert des frei verfÅgbaren Formatbits fÅr den Parameter x 
 * GEFx_ADDR(W) Ó {0x0000,0x0001} (Bit 0)
 */
#define GEF1_FREE(W)   (W&0x0001)
#define GEF2_FREE(W)   ((W>>4)&0x0001)
#define GEF3_FREE(W)   ((W>>8)&0x0001)
#define GEF4_FREE(W)   ((W>>12)&0x0001)

/* Ende der Definitionen fÅr das erweiterte Parameterformat
 */


/***********************************************************************/
/*                                                                     */
/* Maschinenparameterformat                                            */
/*                                                                     */
/*   15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0   BitNr           */
/*  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                  */
/*  |  |a | bb  |   cccc    |       dddddddd        |                  */
/*                                                                     */
/*  a: Multiplexspezifikation                                          */
/*    MPX_CONST: Multiplexwert wird als konstanter Wert mit uebergeben */
/*               (in b)                                                */
/*    MPX_VAL:   Es wird der Multiplexwert des aktuellen Systemzustands*/
/*               verwendet (b hat in diesem Fall keine Bedeutung)      */
/*  b: Multiplexwert                                                   */
/*    Multiplexwert bei konstantem Zugriff                             */
/*  c: Tabellenindex                                                   */
/*    Identifikation der Parametertabelle auf die zugegriffen werden   */
/*    soll                                                             */
/*  d: Parmeterindex                                                   */
/*    Identifikation des Parameters auf den zugegriffen werden soll    */
/*                                                                     */
/***********************************************************************/
#define MPX_VAR      0x0000
#define MPX_CONST    0x4000

#define GET_MPXSPEC(W)  (W&MPX_CONST)
#define GET_MPXVAL(W)   ((W&0x3000)>>12)
#define GET_TABLEIND(W) ((W&0x0f00)>>8)
#define GET_PARAMIND(W) (W&0x00ff)

#define SET_MASHPARAM(MS,MV,PI,TI) (MS|(MV<<12)|(TI<<8)|PI)

/*  Setzen von High- und Lowbyte eines Worts
 */
/*   15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0   BitNr 
 *  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 *  |   High                |   Low                 |
 */
#define SET_WORD_2(High,Low)   ((High<<8)|Low)
#define GET_LOW_BYTE(W)      (W&0x00FF)
#define GET_HIGH_BYTE(W)     (W>>8)

/*  Setzen der vier Halb-Bytes eines Worts
 */
/*   15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0   BitNr 
 *  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 *  |  HB 3     |  HB 2     |  HB 1     |  HB 0     |
 */
#define SET_WORD_4(HB3,HB2,HB1,HB0)   ((HB3<<12)|(HB2<<8)|(HB1<<4)|HB0)
#define GET_HALF_BYTE0(W)                (W&0x000F)
#define GET_HALF_BYTE1(W)                ((W&0x00F0)>>4)
#define GET_HALF_BYTE2(W)                ((W&0x0F00)>>8)
#define GET_HALF_BYTE3(W)                ((W&0xF000)>>12)

/* Codierung der Returnwerte allgemeiner Dunkeltastungsfunktionen.
 * Die Makros ermîglichen die Codierung zweier RÅckgabewerte fÅr
 * die FÑlle True und False, d. h. der RÅckgabewert kann in einer
 * benutzerdefinierten Funktion z. Bsp. von einer Bedingung abhÑngig
 * gemacht werden.
 */
/*   15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0   BitNr 
 *  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 *  |   nicht benutzt       |R.Wert Fals|R.Wert True|
 */
#define SET_DARK_RET(Ret_True,Ret_False) (Ret_True|Ret_False<<4)
#define GET_DARK_RET_TRUE(Ret)           (Ret&0x000F)
#define GET_DARK_RET_FALSE(Ret)          (Ret>>4)

/* Setzen und Abfragen eines Bits
 */
#define SET_BIT_LONG(IND,VAR)     (((0x00000001L)<<IND)|VAR)
#define RESET_BIT_LONG(IND,VAR)   ((~(0x00000001L<<IND))&VAR)
#define GET_BIT_LONG(IND,VAR)     (0x00000001L&(VAR>>IND))


/* Codierung von Konstanten, die in verschiedenen benutzerdefinierten Modulen
 * Verwendung finden. (Typisch: öbergabeparameter benutzerdefinierter
 * Funktionen)
 */

/* Allgemein
 */
#define USR_NO_ERROR        0
#define GEN_ERROR      -1
#define OFF             0
#define ON              1
#define STATECHANGE  0xFF
#define DEFINED 0
#define UNDEFINED -1
#define EWIKON_ISCOS_NR 3
#define REGLER_INTO_BLOCK 1
#define REGLER_OUT_BLOCK  0

#define DOPTION       0x0100
#define DOPTIONINVERT 0x0200

/* Einzulesender Datentraegertyp */
#define NO_CARTYPE      0
#define ISCOS_CARTYPE   1
#define ELV1_CARTYPE    2
#define ELV2_CARTYPE    3

#define HZDL_TO_PLC1      1
#define HZDL_TO_PLC2      2
#define PLC1              1
#define PLC2              2

/* logische Operatoren
 */
#define OR  0
#define AND 1
#define NOT 2

/* relationale Operatoren
 */
#define EQ 0
#define GT 1
#define GE 2

/* Modul DSUTIL  */
#define CHANGE 1
#define FB_TX2 2
#define FX1_TB 3
#define FX1_TX2 4

/* Modul INJFUNC  */
#define CHANGED_STATE  0
#define CHANGED_PARAM  1
#define WAY 0L
#define VOLUME 1L
#define HYDRAULIC 0L
#define SPECIFIC 1L
#define PRESS 0L
#define FORCE 1L
#define CONVERT 0x0001
#define NO_CONVERT 0x0000

#define TYPE_UNKNOWN          0
#define WAY_TYPE              1
#define VELOCITY_TYPE         2
#define HYDR_PRESSURE_TYPE    3
#define PRESSURE_TYPE         4
#define TIME_TYPE             5

#define SCR_WAY        0
#define SCR_VOLUME     1
#define SCR_BAR        0
#define SCR_PSI        1
#define SCR_CELCIUS    0
#define SCR_FAHRENHEID 1

/* Modul TCONTROL  */
#define INIT_COUNT   0x0001
#define INIT_ERR     0x0002
#define INIT_ERR_STR 0x0004

#ifdef besser_aus_der_Malterdinger_Version_oder_gar_nicht
/* Modul HEATWORK  */
#define NOHEAT          0        /* Nummern der Heizungsgruppen */
#define INJHEAT         2        /* PR am 15.11.91 vertauscht   */
#define TOOLHEAT        1
#define TEMPHEAT        3
#define OILHEAT         4
#define GENHEAT         5
#define RESHEAT         6

#define FUNCTIONUNIT    0
#define HEATZONE        1
#define HEATGROUP       2

/* Indizes der Parametertabellen (Parametertabellenindizes)
 */
#define TOOLTAB_IND        0
#define TOOLTABISC_IND     1
#define INJUNITTAB_IND     2
#define INJUNITTABISC_IND  3
#define AGGTAB_IND         4
#define AGGTABISC_IND      5
#define EJECTTAB_IND       6
#define EJECTTABISC_IND    7
#define CORETAB_IND        8
#define CORETABISC_IND     9
#define GENTAB_IND         10
#define GENTABISC_IND      11

/* Indizes in die Parametertabellen (Parameterindizes)
 */
/* GenTabIsc
 */
#define   I_AKKU_MIN 1
#define   I_AKKU_MAX 2
#define   I_DRUCK_OELVW   18
#define   I_DRUCK_FORMFAHRT 19
#define   I_DRUCK_DRUEBERS_ZUR 20
#define   I_DRUCK_TUER_LANGSAM 21
#define   I_DRUCK_TUER_SCHNELL 22
#define   I_ANSTZ_DRUEB_Z    23
#define   I_ANSTZ_OEDRUEB_Z  24
#define   I_VERZZ_OELFILTER  25
#define   I_VERZZ_VFVENT_OEFF 26
#define   I_VERZZ_WKZ_OEFF   27
#define   I_VERZZ_DRUCK_AUFB 28
#define   I_VERZZ_DRUCK_2ST  29
#define   I_VERZZ_EINSPR  30
#define   I_VERZZ_SN_FREIG  31
#define   I_VERZZ_ABS_TEMP  32
#define   I_DUESE_OEFF_SCHL 33

/* PumpCombTab_2
 */
#define   I_PMP_OELVORW    1
#define   I_PMP_CLOSEPRES  2
#define   I_PMP_PRESCONV   3
#define   I_PMP_EJECTV     4
#define   I_PMP_EJECTZ     5
#define   I_PMP_SDOOR      6
#define   I_PMP_AGGV       7
#define   I_PMP_AGGZ       8
#define   I_PMP_DUESVER    9
#define   I_PMP_SCREWBACK 10
#define   I_PMP_CORES     11
#define   I_PMP_INTRUSION 12
#define   I_PMP_LOADACCU  13
#define   I_PMP_HELPFUNC  14
#define   I_PMP_SPECFUNC  15
#define   I_PMP_EINRICHT  16
#define   I_PMP_FSS       17
#define   I_PMP_DRUCKAB   18
#define   I_PMP_VORFUELL  19
#define   I_PMP_RES1      20
#define   I_PMP_RES2      21
#define   I_PMP_RES3      22
#define   I_PMP_RES4      23
#define   I_PMP_RES5      24
#define   I_PMP_RES6      25

/* GenTab
 */
#define I_NOOF_ISCOS          1
#define I_NOOF_MOT            2
#define I_NOOF_CORES          3
#define I_MAX_HYDRPRES        4
#define I_NOOF_AIR            5

/* ToolTabIsc
 */
#define I_K1_TOOL        1
#define I_K2_TOOL        2
#define I_WKZ_OEFF_BESCHL   3
#define I_WKZ_SCHL_BESCHL   4
#define I_WKZ_OEFF_VERZ     5
#define I_WKZ_SCHL_VERZ     6
#define I_WKZ_OEFF_ENDVERZ  7
#define I_WKZ_SCHL_ENDVERZ  8
#define I_WKZ_OEFF_VERST    9
#define I_WKZ_SCHL_VERST   10
#define I_WKZ_SCHL_VENTOFFS 11
#define I_WKZ_OEFF_VENTOFFS 12
#define I_EINR_GESCHW_OEFF 13
#define I_EINR_GESCHW_SCHL 14
#define I_MINIM_WKZ_GESCHW 15
#define I_STELLW_DRUCKAUFBAU 16
#define I_DRUCK_UEBERS_ZUR 17
#define I_FSS_GR_FL        18
#define I_UEBZ_SCHLIESSEN 19
#define I_UEBZ_OEFFNEN 20
#define I_UEBZ_SCHLD_AUFB 21
#define I_UEBZ_SCHLD_ABB 22
#define I_UEBZ_OEFFN_DRUCK 23
#define I_UEBZ_LICHTS_AUSFW 24
#define I_SCHL_DRUCK_ABBAU 25
#define I_UMSCHALT_2STUFE 26

/* ToolTab
 */
#define I_MASCH_TYP           1
#define I_SCHLFL_KLEIN        2
#define I_SCHLFL_GROSS        3
#define I_SCHLIESSKRAFT       4
#define I_WERKZEUGHUB         5
#define I_FORMMIN1            6
#define I_FORMMIN2            7
#define I_FORMMIN3            8
#define I_RINGFL_OEFFNEN      9
#define I_FORMMIN             10
#define I_DRUCK_MAX_SCHLDRUCK 12
#define I_WKZ_KAL_OFFSET     35
#define I_WKZ_GESCHW_AUF     44
#define I_WKZ_GESCHW_ZU      45
#define I_NOOF_TOOLHEATZONES 46
#define I_NOOF_TEMPHEATZONES 47

/* AggTabIsc
 */
#define I_K1_AGG        1
#define I_K2_AGG        2
#define I_DMPF_WEG_V    3
#define I_DMPF_WEG_Z    4
#define I_DMPF_GESCHW_V 5
#define I_DMPF_GESCHW_Z 6
#define I_DRUCK_V       7
#define I_DRUCK_Z       8
#define I_AGG_UEBERW_ZEIT 9

/* AggTab
 */
#define I_AGG_WEG_MAX      1
#define I_AGG_FL_VOR       2
#define I_AGG_FL_ZUR       3


#define I_AGG_STEIG_FAKTOR 6
#define I_AGG_OFFSET_B_VOR 7
#define I_AGG_OFFSET_B_ZUR 8
#define I_AGG_GESCHW_V     9
#define I_AGG_GESCHW_Z    10


#define I_AGG_KAL_OFFSET  14

/* EjectTab
 */
#define I_AUSW_HUB          1
#define I_AUSW_STEIG_FAKTOR 5
#define I_AUSW_OFFSET_B_VOR 6
#define I_AUSW_OFFSET_B_ZUR 7
#define I_AUSW_GESCHW_V     9
#define I_AUSW_GESCHW_Z    10
#define I_AUSW_DRUCK_V  11
#define I_AUSW_KAL_OFFSET  14
#define I_AUSW_DRUCK_Z  17

/* EjectTabIsc
 */
#define I_K1_EJECT      1
#define I_K2_EJECT      2
#define I_AUSW_UEBERW_ZEIT   3

/* InjUnitTabIsc
 */
#define I_K1_INJUNIT    1
#define I_K2_INJUNIT    2

/* InjUnitTab
 */
#define I_PLAST_WEG            1
#define I_SPRKOLB_FL           2
#define I_DREHZAHL_MAX         3
#define I_ANZ_ZAEHNE           4
#define I_SPRKOLB_RINGFL       5
#define I_VOL_HYDROMOT         6
#define I_SN_DURCHM            7
#define I_SPR_DRUCK_MAX        8
#define I_NOOF_CYLHEATZONES    9
#define I_NR_ENTGASUNGSZONE   10
#define I_SN_RUECK_GESCHW     11
#define I_SVMAX               12
#define I_AUSF_ZYL            13
#define I_STIFT_DURCHM        14
#define I_SPREINH_KAL_OFFSET  16
#define I_DREHZAHL_MIN        19

/*  PumpTabIsc
 */
#define I_DRUCK_MIN       1
#define I_DRUCK_MAX       2

/*  PumpTab
 */
#define I_DREINST_FOERDLSTG     1
#define I_DREINST_VENTANSTMIN   2
#define I_DREINST_VENTANSTMAX   3

/* InjUnitTab
 */
#define I_SN_DURCHM_S     1
#define I_SPRKOLB_FL_S    2
#define I_STIFT_DURCHM_S  3

#endif

/* Allgemein verwendbare Funktionen
 */
BYTE Response      (UWORD Bit, UWORD InitWait, UWORD Wait, UWORD TimeOut, UWORD ErrInd);
int  CheckInterval (long Von, long Bis);
void FormatParam   (UWORD ParamNo, long *Param , UWORD Format , UWORD Ind1,
                    UWORD Ind2,UWORD Ind3, UWORD IndInfo);


#endif /*_userdef*/

