/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     ERROR.H
*
*  BESCHREIBUNG:
*     ...
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   08.05.92
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*                      Neu entstanden
*     05.06.92 -SF-    Modul als DLL angelegt
*     14.05.97 -TSchw- Returnwert von Err_GetActInfo auf UWORD verbessert.
*     08.01.03 -HA-    ERRPAGE_LENGTH eingefuegt.
*     11.04.03 -HA-    Err_GetPossible eingefuegt.
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

#ifndef _error
#define _error

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <dstruct.h>
#include <sunichar.h>
/*.EI.***********************************************************************/

/*---------------------------------------------------------------------------
X Allgemeine Konstanten
---------------------------------------------------------------------------*/
/* Parameter bei Err_PageScroll() */
#define ERR_SCROLL_UP     0
#define ERR_SCROLL_DOWN   1

/* Sortierkriterium fuer Fehler aus Fehlerindex und -id aufbauen */
#define SETSORT(IND,ID)         (((long) (IND) << 16) | (UWORD)(ID))

#define NOBIT       0x7fff

/* Unterscheidung, in welchem Dev-Aufruf der Fehler aufgetreten ist */
#define DEV_INIT        1        /* fuer Aufruf von DevError */
#define DEV_OPEN        2
#define DEV_CLOSE       3
#define DEV_WRITE       4
#define DEV_READ        5
#define DEV_SET         6
#define DEV_GET         7
#define DEV_EXAMINE     8

#define ERR_LENGTH     44       /* Laenge der Fehlermeldungen */
#define ERRPAGE_LENGTH 53       /* Laenge der Fehlermeldungen auf der Fehlermeldungsseite*/

typedef struct SPEC_ERRORX
   {
   int   ErrInd;
   int   Id;
   UNICHAR  *ErrStr;
   struct SPEC_ERRORX *next;
   } SPEC_ERROR;                 /* Typ der Sonderfehlertabelle */

/*---------------------------------------------------------------------------
X Verwendung von 'normalen' Funktionen
---------------------------------------------------------------------------*/
GLOBAL int Err_Init( BOOL init_bbram );
GLOBAL UWORD Err_GetBit( UWORD err_ind );
GLOBAL int Err_GetText( UNICHAR * buf_ptr, UWORD err_ind, int max_len );
GLOBAL UWORD Err_GetHostText( char* buf_ptr, UWORD err_ind, int max_len );
GLOBAL int WriteErrStr( UWORD err_ind );
GLOBAL int WriteErrStrStr( UWORD err_ind, char* str_ptr );
GLOBAL int WriteErrStrStr_Uni( UWORD ErrInd, UNICHAR *Str );
GLOBAL int DevError( IQT_HANDLE err_hnd, int dev_type, int dev_func );
GLOBAL void Err_ClearInputErr( int time );
GLOBAL void Err_ShowInputErr( void );
GLOBAL UWORD Err_GetActInputErr( void );
GLOBAL BOOL Err_Exist( void );
GLOBAL UWORD Err_GetPossible(void);

GLOBAL int Err_DrawErrLines( IQT_HANDLE hnd );
GLOBAL void Err_DrawStatLines( IQT_HANDLE hnd, BYTE line, BYTE type, BYTE prn_flag );
GLOBAL int Err_PageShow( BYTE from, BYTE screen, COLOR col, BYTE line, BYTE len );
GLOBAL void Err_PageScroll( int dir );

GLOBAL int Err_SpecMakeUni( int ErrInd, int Id, UNICHAR *str );
GLOBAL int Err_SpecMake( int err_ind, int id, char* mask_ptr, BYTE with_err_tab );
GLOBAL int Err_SpecDel( int err_ind, int id );
GLOBAL SPEC_ERROR* Err_SpecGetFirst( void );
GLOBAL SPEC_ERROR* Err_SpecGetNext( SPEC_ERROR* act_ptr );

GLOBAL void Err_SetErrors( void );
GLOBAL BOOL Err_GetNextErr( int *err_ind_ptr, int *id_ptr, UNICHAR *buf_ptr, int max_len );
GLOBAL BOOL Err_GetLastErr( int* err_ind_ptr, int* id_ptr );

GLOBAL int  WriteInfoStr( UWORD err_ind );
GLOBAL int  WriteInfoPStr( UWORD bde_ind );
GLOBAL void Err_ClearInfo( void );
GLOBAL UWORD Err_GetActInfo( void );
GLOBAL int Err_IscosStatus( int flag );

#endif /* ifndef _error */





