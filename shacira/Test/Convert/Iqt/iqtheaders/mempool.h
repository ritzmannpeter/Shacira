/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     xxxxxxxxx
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

#ifndef _mempool
#define _mempool

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

GLOBAL void* MemPoolInit    ( UWORD size, UWORD count );
GLOBAL int   MemPoolDeinit  ( void* _pool_ctrl_blk_ptr );
GLOBAL int   MemPoolSetFirst( void* _pool_ctrl_blk_ptr );
GLOBAL int   MemPoolRead    ( void* _pool_ctrl_blk_ptr, BYTE* dest_ptr );
GLOBAL void* MemPoolWrite   ( void* _pool_ctrl_blk_ptr, BYTE* src_ptr );
GLOBAL int   MemPoolRelease ( void* _pool_ctrl_blk_ptr );

#endif /* ifndef _mempool */





