/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DSWORK.H   - DSWORK-Funktionen
*
*  BESCHREIBUNG:
*     Deklarationen und Definitionen der DSWORK Funktionen.
*
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   01.04.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     01.04.92 -SF-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     15.06.92 -SF-    CallConvFunc eingebaut
*     03.07.92 -SF-    GetVarNrText eingebaut
*     18.08.92 -SF-    DSWork_Init hat andere Aufrufparameter
*                      DSWORK_INIT_BLK entfaellt
*                      DSWork_NewLanguage() eingebaut
*     14.02.96 -TSchw- GET_PAGE_ERROR_DARK erstellt
*     03.08.99 -TSchw- Neutrino 2.0 Portierung: in PageNext Parametertyp
*                      von void * auf PAGEHANDLE * geaendert.
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

#ifndef _dswork
#define _dswork

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <sunichar.h>
/*.EI.***********************************************************************/

/*---------------------------------------------------------------------------
X Allgemeine Konstanten
---------------------------------------------------------------------------*/
/* Verwaltung der variablen Texte */
#define VTXT_DISK_INFO   0
#define VTXT_ROW_SIZE    1
#define VTXT_COL_SIZE    2
#define VTXT_SIZE        3
#define VTXT_MAX_TAB     4

/* Fuer 'ctrl' von CallTabFunc() */
#define CALL_DARK    0
#define CALL_USER1   1
#define CALL_USER2   2
#define CALL_SOFT    3

/* Unterscheidung Sollwert/Istwert */ 
#define NO_KLICK    0
#define SOLL_ELEM   1
#define IST_ELEM    2
#define OBJEKT      3

/* zusaetzliche Steuerparameter fuer die neue Funktion GetSollIst */
#define TEST_EXIST       0
#define TEST_PAGE     0x10
#define TEST_OBJECT   0x20
#define TEST_ELEMENT  0x40
#define TEST_ALL (TEST_PAGE|TEST_OBJECT|TEST_ELEMENT)

/* Zusaetzlicher Fehler fuer Returnwert von GetPage */
#define GET_PAGE_ERROR_DARK   2

#  ifdef PAGEPOINTERTAB   
      typedef PAGE **PAGEHANDLE;
#  else
      typedef PAGE *PAGEHANDLE;
#  endif

/* Initialisierung */
GLOBAL int DSWork_Init( int type, int language );

/* Sprachumschaltung */
GLOBAL int DSWork_NewLanguage( int language );

/* Lesen der festen Texte */
GLOBAL UNICHAR* GetFixText ( TEXT_INDEX* text_ind );
GLOBAL UNICHAR* GetBdeText ( UWORD bde_ind );
GLOBAL UNICHAR* GetIndText ( INDTEXT* i_ptr );
GLOBAL UNICHAR* GetDimText ( ELEMENT* el_ptr );
GLOBAL int GetVarNrText    ( char*    txt, long varnr );
GLOBAL int GetVarNrText_Uni( UNICHAR* txt, long varnr );

/* Verwaltung der variablen Texte */
GLOBAL int   VTxt_Init    ( BYTE init_bbram );
GLOBAL char* VTxt_Read    ( char* buffer, int size, UWORD ctrl, UWORD ind, int line );
GLOBAL char* VTxt_ElRead  ( char* buffer, int size, UWORD ctrl, ELEMENT* el_ptr );
GLOBAL int   VTxt_Write   ( char* buffer, int size, UWORD ctrl, UWORD ind, int line );
GLOBAL int   VTxt_ElWrite ( char* buffer, int size, UWORD ctrl, ELEMENT* el_ptr );
GLOBAL int   VTxt_GetParam( UWORD ctrl, UWORD ind );
GLOBAL char* VTxt_ReadRow(char * buffer, int textind, int row, int rows, int buflen);
GLOBAL char* VTxt_ElReadRow(char * buffer, ELEMENT * element, int buflen);
GLOBAL char* VTxt_WriteRow(char * buffer, int textind, int row, int rows, int buflen);
GLOBAL char* VTxt_ElWriteRow(char * buffer, ELEMENT * element, int buflen);
GLOBAL char* GetVarText   ( UWORD ind );

/* Bearbeitung der Datenstruktur */
GLOBAL ELEMENT* GetElementRelPtr ( ELEMENT* base, ELEMENT_PTR offset );
GLOBAL ELEMENT* GetElementNext   ( ELEMENT* el_ptr );
GLOBAL ELEMENT* GetElementName   ( ELEMENT* el_ptr );
GLOBAL ELEMENT* GetElementDim    ( ELEMENT* el_ptr );
GLOBAL void GetElementNameDim    ( ELEMENT* el_ptr, ELEMENT** pName, ELEMENT** pDim );
GLOBAL UNICHAR * GetElementText  ( UNICHAR * buffer, int size, ELEMENT* el_ptr );
GLOBAL int ValToString     ( char    * buf, long val, FORMAT format, BYTE ctrl );
GLOBAL int ValToString_Uni ( UNICHAR * buf, long val, FORMAT format, BYTE ctrl );
GLOBAL int NotDark     ( UWORD f, UWORD p, BYTE r );
GLOBAL int GetSollIst  ( UWORD ctrl, long var_nr, UWORD* page_ind_ptr, UWORD* obj_ind_ptr, ELEMENT** el_ptr_ptr );
GLOBAL int FirstSollIst( UWORD page_ind, BYTE soll_ist, UWORD* obj_ind_ptr, ELEMENT** el_ptr_ptr );
GLOBAL int NextSollIst ( UWORD page_ind, BYTE soll_ist, BYTE dir, UWORD* obj_ind_ptr, ELEMENT** el_ptr_ptr );
GLOBAL int FirstElement( UWORD page_ind, UWORD* obj_ind_ptr, ELEMENT** el_ptr_ptr );
GLOBAL int NextElement ( UWORD page_ind, UWORD* obj_ind_ptr, ELEMENT** el_ptr_ptr );
GLOBAL int FirstObject ( UWORD page_ind, UWORD* obj_ind_ptr );
GLOBAL int NextObject  ( UWORD page_ind, UWORD* obj_ind_ptr, BYTE dir );
GLOBAL OBJECT* GetObjP ( UWORD page_ind, UWORD obj_ind );
GLOBAL int GetPage     ( UWORD PageNr, UWORD* page_ind, UWORD* obj_ind_ptr, ELEMENT** el_ptr_ptr );
GLOBAL UWORD PageCount  ( void );
GLOBAL PAGE* PageFetch ( UWORD index );
GLOBAL PAGEHANDLE PageSearch( UWORD num );
GLOBAL UWORD PageNext   ( PAGEHANDLE * hnd_ptr );
GLOBAL void * DESC_Element(long variable);

#endif /* _dswork */



