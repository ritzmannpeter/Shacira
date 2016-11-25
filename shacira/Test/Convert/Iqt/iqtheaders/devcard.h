/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVCARD.H
*
*  BESCHREIBUNG:
*
*  UMGEBUNG:
*     ZIELRECHNER:          Industrie-PC (Provit 2001/5000)
*     BETRIEBSSYSTEM:       Windows NT / Linux
*     PROGRAMMIERSPRACHE:   VC 5 / gcc 
*
*  VERSION:
*     VERSION:  1.0              AUTOR:       T.Schwoerer
*     DATUM:    08.11.2000
*
*  HISTORY:
*     08.11.00 -TSchw- Implementierung
*     09.04.01 -TSchw- Lesen der kompletten Headerdaten ermöglicht.
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

#ifndef _devcard
#define _devcard


/*********************************************************************
*  DEVCARD-Device: KONSTANTEN UND ALLGEMEINE MAKROS
*********************************************************************/

#define CARD_ID_READER_ATTACHED            1
#define CARD_ID_CARD_INSERTED              2
#define CARD_ID_ACCESSCARD_INSERTED        3
#define CARD_ID_CARD_CHANGED               4
#define CARD_ID_KEYPOS                     5
#define CARD_ID_ACCESSMASK                 6
#define CARD_ID_PREPARE_RW_PERSNR          7
#define CARD_ID_PREPARE_RW_SUBFILE         8
#define CARD_ID_FORMAT                     9
#define CARD_ID_HOLD_REFRESH              10
#define CARD_ID_RUN_REFRESH               11
#define CARD_ID_HOLD_REFRESH_FOR_SEC      12
#define CARD_ID_PREPARE_RD_HDRDATA        13
#define CARD_ID_PREPARE_DIRECT_RD_HDRDATA 14

#define ACCESSCARD_PERSNR_LEN          15

typedef struct accesscard_header_data {
   signed short   AccessRight;                   // "Schlüsselschalterstellung"
   unsigned long  AccessMask;                    // Bitweise Zugangsberechtigung
   char           PersNr[ACCESSCARD_PERSNR_LEN]; // Personalnummer
} ACCESSCARD_HEADER_DATA;

#endif