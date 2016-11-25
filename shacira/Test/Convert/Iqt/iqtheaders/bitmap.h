/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IQT_BITMAP.H
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
*     VERSION:    4.0                       DATUM:   19.08.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*
*  HISTORY:
*     21.08.92 -SF-    Modul als DLL angelegt
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

#ifndef _bitmap
#define _bitmap

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Id's fuer Bitmap_GetParam()
****************************************************************************/
#define BITMAP_ID_GET_SIZE            0

GLOBAL int Bitmap_Init(BOOL init_bbram);
GLOBAL int Bitmap_GetParam(int type, void* par_ptr, int par_int);
GLOBAL IQT_HANDLE Bitmap_Draw(ELEMENT* el_ptr, BYTE line, BYTE from, BYTE screen);
GLOBAL IQT_HANDLE Bitmap_DirectDraw( int index, int x, int y, BYTE line, 
                                     BYTE from, BYTE screen );

#endif /* ifndef _bitmap */

