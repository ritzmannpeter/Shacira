/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVCEN.H
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
*     VERSION:    4.0                       DATUM:   07.04.92
*     AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     07.04.92 -TS-    Implementierung
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
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


#ifndef _devcen
#define _devcen

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif
#ifndef _iqttsk
#include <iqttsk.h>
#define _iqttsk
#endif
/*.EI.***********************************************************************/


/*********************************************************************
*  CEN-Treiber: DATENTYPEN
*********************************************************************/

typedef struct CenControlBlock
{
   BYTE       CenID;       /* LPT_1 .. LPT_2 */ 
   IQT_HANDLE     Handle;
} CCB;

typedef struct CenParamBlock
{
        PARAMETER CenID;       /* LPT_1 .. LPT_2 */ 
}       CEN_PARAM_BLOCK, * CEN_PARAM_PTR;

typedef struct
{
   BYTE Dummy;  /* Momentan keine Funktionen */
} CEN_INIT_BLOCK;


#define CEN_NUM_DEVICES  1

/*********************************************************************
*   CEN-Treiber: FEHLERCODES
*********************************************************************/

#define CEN_ERR_BAD_ID              1  /* Parameterfehler */

#define CEN_ERR_EOF_DETECTED        6  /* Uebertragungsfehler */
#define CEN_ERR_EOS_DETECTED        7
#define CEN_ERR_TIME_OUT            8
#define CEN_ERR_BAD_CHECKSUM        9
#define CEN_ERR_BAD_DATA_PROTOCOLL  10
#define CEN_ERR_BAD_HARDWARE        11
#define CEN_ERR_WHILE_TRANSMISSION  -1 /* muss negativ sein */

#define CEN_ERR_ALLREADY_USED       12 /* sonstige Fehler */
#define CEN_ERR_UNKNOWN             13

/*********************************************************************
X  SCHNITTSTELLE ZUM HAUPTMODUL "IQTDEV.C"
*********************************************************************/

   int CenInit     ( void * initblock );
   int CenOpen     ( IQT_HANDLE hnd , CEN_PARAM_BLOCK * paramblk ,
                                     CCB * * ccb , MODULE_PTR * modul );
   int CenClose    ( CCB * ccb , int * done );
   int CenRead     ( CCB * ccb , char * buf , int buflen ,
                                     int * aktlen , TIME tmo );
   int CenWrite    ( CCB * ccb , char * buf , int buflen ,
                                     int * aktlen , TIME tmo );
   int CenControl  ( CCB * ccb , int cntrl , PARAMETER param );
   int CenExamine  ( CCB * ccb , char * byte , TIME tmo );
   int CenSetParam ( CCB * ccb , int id , PARAMETER param );
   int CenGetParam ( CCB * ccb , int id , PARAMETER * param );

#endif /* devcen */

