/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     SPSDIAG.H
*
*  BESCHREIBUNG:
*     Defines fuer freiauswaehlbarer Diagnosemode.
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   21.11.97
*     AUTOR(EN):  -HAns-                    TELEFON: 338
*
*  HISTORY:
*     21.11.97 -HAns-   Implementiert
*                       SPS-CPU-Type Definitionen eingebaut.
*     25.11.97 -HAns-   Func. ReadAll_DMData aufgenommen.
*     05.12.97 -HAns-   "hw_datat.h" von der M.Steuerung aufgenommen.
*     25.10.01 -HA-     ANZ_WEGMS ff aufgenommen.
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Keine
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _spsdiag
#define _spsdiag


void ReadAll_DMData (void);
void SetDefaultFreeDM (UWORD Index);
long Get_DMDataInd (UWORD ctrl, UWORD RegID, UWORD Ind1, UWORD Ind2, UWORD Ind3);



typedef struct {
   UWORD diagsystyp; /* Systemtyp */
   UWORD diagbusnr;  /* BusNr     */
   UWORD diagmodnr;  /* ModulNr   */
   UWORD diagindtab; /* Index in den B&R-Modulkatalog */
} DM_DATA;

typedef struct {
   DM_DATA sps;     /* SPS-Values */
   UWORD diagpagenr; /* PageNr der Standardseiten */
} IQTDM_DATA;



#define DIAGSYSTYP_INR    0 /* Iscos-Nummer des Registers sktemp */
#define DM_REGS           4 /* Anzahl der zu lesenden Register je Diag.Modul */
#define MAX_DMTAB        72 /* Max. Anzahl von Diagnosemodule    */
#define USE_INDREG       -1 /* ACT_DIAGINDTAB benutzen           */
#define FREE_DIAGPAGENR 881 /* freiauswaehlbare Diagnoseseite */

/* Darstellung von Analogwerte */
#define DIAG_IST          0
#define DIAG_SOLL         1

/* SPS CPU Typen (32Bit: 1,2,4,8,16,32,64,128,256 usw.) */
#define NEW_CPU    0x0000
#define CP100      0x0001
#define CP151      0x0002
#define CP152      0x0004
#define CP200      0x0008
#define CP260      0x0010

/*********************************************************************
X  AUFBAU DES SPSWEGMTYP:
*
*  Bit:   15 14 13 12 11 10 09 08   07 06 05 04 03 02 01 00
*  Feld:  -Anzahl Wegmesssysteme-   ---Wegmesssystem-Typ---
*
*  ZUGRIFFSMACROS:
*
*
*  GET_ANZ_WEGMS( ctrl ) 
*  GET_WEGM_TYP ( ctrl ) 
*
*********************************************************************/
#define GET_ANZ_WEGMS(I)  ((I) & 0xff00)
#define GET_WEGM_TYP(I)   ((I) & 0x00ff)

/* Pruefauswahlfestlegung Darkfunktion  */
#define TYP 0
#define ANZ 1

/* SPS WegMess Typen (ANALOG, CAN usw.) */
#define ANALOG_WEGM 0x0000
#define CAN_WEGM    0x0001

/* SPS WegMess Typen (ANALOG, CAN usw.)  und Anzahl Wegmesssysteme */
#define ANZ_WEGMS_1 0x0100
#define ANZ_WEGMS_2 0x0200
#define ANZ_WEGMS_3 0x0300
#define ANZ_WEGMS_4 0x0400
#define ANZ_WEGMS_5 0x0500
#define ANZ_WEGMS_6 0x0600
#define ANZ_WEGMS_7 0x0700
#define ANZ_WEGMS_8 0x0800

#define AWMS1_ANALOG (ANZ_WEGMS_1 | ANALOG_WEGM)
#define AWMS2_ANALOG (ANZ_WEGMS_2 | ANALOG_WEGM)
#define AWMS3_ANALOG (ANZ_WEGMS_3 | ANALOG_WEGM)
#define AWMS4_ANALOG (ANZ_WEGMS_4 | ANALOG_WEGM)
#define AWMS5_ANALOG (ANZ_WEGMS_5 | ANALOG_WEGM)
#define AWMS6_ANALOG (ANZ_WEGMS_6 | ANALOG_WEGM)
#define AWMS7_ANALOG (ANZ_WEGMS_7 | ANALOG_WEGM)
#define AWMS8_ANALOG (ANZ_WEGMS_8 | ANALOG_WEGM)

#define AWMS1_CAN    (ANZ_WEGMS_1 | CAN_WEGM) 
#define AWMS2_CAN    (ANZ_WEGMS_2 | CAN_WEGM) 
#define AWMS3_CAN    (ANZ_WEGMS_3 | CAN_WEGM) 
#define AWMS4_CAN    (ANZ_WEGMS_4 | CAN_WEGM) 
#define AWMS5_CAN    (ANZ_WEGMS_5 | CAN_WEGM) 
#define AWMS6_CAN    (ANZ_WEGMS_6 | CAN_WEGM) 
#define AWMS7_CAN    (ANZ_WEGMS_7 | CAN_WEGM) 
#define AWMS8_CAN    (ANZ_WEGMS_8 | CAN_WEGM) 

/* Fuer Kanaltyp-Abfrage (Ein/Ausgang) usw. */
#define C_NONE     0
#define C_INPUT    1
#define C_OUTPUT   2

#endif /* _spsdiag */
