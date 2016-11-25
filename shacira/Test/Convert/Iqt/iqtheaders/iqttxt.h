/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IQTTXT.H - Texttabellen
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
*     VERSION:    1.0                       DATUM:   13.08.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*
*  HISTORY:
*     13.08.92 -SF-    Implementierung
*     05.09.97 -TSchw- TXT_ID_ISINIT angelegt
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Txt_Init - Initialisieren einer Sprache
*     Txt_GetPtr - Zeiger auf Texttabellen holen
*     Txt_GetParam - Sonstige Parameter holen
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _iqttxt
#define _iqttxt

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/

/****************************************************************************
X  KONSTANTEN
****************************************************************************/
#define NOOF_LANGUAGES 3

/* Fuer Funktion Txt_GetPtr() */
#define TXT_ID_STATTAB           0
#define TXT_ID_BDETAB            1
#define TXT_ID_ITEXTTAB          2
#define TXT_ID_VERSTEXT          3
#define TXT_ID_SPECTEXT          4
#define TXT_ID_TIMETEXT          5
#define TXT_ID_TAB_TYPE          6
#define TXT_ID_ISINIT            7 

/* Fuer Funktion Txt_GetParam() */
#define TXT_ID_MAX_STATTAB      10
#define TXT_ID_MAX_BDETAB       11
#define TXT_ID_MAX_ITEXTTAB     12
#define TXT_ID_MAX_STATTABS     13    /* Anzahl Tabellen */
#define TXT_ID_MAX_HELPTABS     14    /* Anzahl Hilfetexttabellen */


#define TEXT_TAB   0
#define HELP_TAB   1




/****************************************************************************
X  Typdefineitionen
****************************************************************************/

typedef struct iqttxt_msg_type {
BYTE id;
union {
struct {int type;} Txt_Init; 
struct {int id; int index;} Txt_GetPtr; 
struct {int id; int index;} Txt_GetParam; 
}  Parameter;
} IQTTXT_MSG_TYPE;

/* Rueckgabetypen-Struktur fuer Datenstrukturtask
 */
typedef union iqttxt_rep_type {
int Txt_Init;
void * Txt_GetPtr;
int Txt_GetParam;
} IQTTXT_REP_TYPE;


#define TXT_INIT            0
#define TXT_GETPTR          1
#define TXT_GETPARAM        2


/*---------------------------------------------------------------------------
X Funktions - Prototypen
---------------------------------------------------------------------------*/

GLOBAL int Txt_Init( int lang, int type );
GLOBAL void* Txt_GetPtr( int lang, int id, int index );
GLOBAL int Txt_GetParam( int lang, int id, int index );


#endif /* _iqttxt */

