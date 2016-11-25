/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DISPATCH.H
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
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*                      Neu entstanden
*     02.07.92 -SF-    DSPReadText hat als Filter [BYTE*] statt [char*]
*     04.08.92 -SF-    Modul als DLL angelegt
*     13-09-96 -PR-    Aenderungen fuer den allgemeinen Klickmodus
*     06-05-98 -PR-    Work und Returnfilter-Zeiger in DSPReadChar und
*                      DSPReadText als const - Zeiger deklariert (Zur
*                      Beruhigung von Visual C++ 5.0).
*     09.02.00 -TSchw- Neue Softkeytasten 6+7 eingefuegt
*     06.08.01 -TSchw- ALLE_SONDER_TASTEN eingefügt
*
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

#ifndef _dispatch
#define _dispatch

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
/*.EI.***********************************************************************/

/****************************************************************************
X  Konstanten fuer DSPReadChar()
****************************************************************************/
#  define DSP_INP_DONE       0     /* Zeichen des 'work_flt' eingegeben */
#  define DSP_INP_BREAK      1     /* Zeichen des 'ret_flt' eingegeben */
#  define DSP_KEY_CHANGED    2     /* 'el_ptr' nicht mehr erlaubt */

/****************************************************************************
X  Konstanten fuer DSPShowPage()
****************************************************************************/
#  define DSP_NEW_PAGE       0     /* neue Seite anzeigen */
#  define DSP_ACT_PAGE       1     /* aktuelle Seite neu anzeigen */
#  define DSP_PAGE_UP        2     /* Eine Seite weiterblaettern */
#  define DSP_PAGE_DOWN      3     /* Eine Seite zurueckblaettern */
#  define DSP_UPD_PAGE       4     /* Seite wird aktualisiert */
#  define DSP_UPD_WINDOW     5     /* Window wird aktualisiert */
#  define DSP_NEW_WINDOW     6     /* neue Seite ins Window */

/****************************************************************************
X  Konstanten fuer DSPCheckActKey() und DSPReadChar()
****************************************************************************/
#  define DSP_FROM_DSP       0
#  define DSP_FROM_GETCHAR   1
#  define DSP_FROM_FASTREG   2

/****************************************************************************
X  Konstanten fuer INPInput()
****************************************************************************/
   /* Konstanten fuer die Funktion INPInput */
#  define INP_BREAK_ON       0     /* Sollwerteingabe abbrechen */
#  define INP_BREAK_OFF      1     /* Sollwerteingabe nicht abbrechen */

/****************************************************************************
X  Konstanten fuer INPGetParam()
****************************************************************************/
#  define INP_FORMAT         0

/****************************************************************************
X  Konstanten fuer DSPEvent
****************************************************************************/
#define DSP_ABORT      0x0001
#define DSP_NEWPAGE    0x0002
#define DSP_NEWWINDOW  0x0004

/****************************************************************************
X  Definitionen fur den Klick-Modus
****************************************************************************/
typedef int (* KLICK_SET_FUNC)(void * data, OBJECT * act_object);
typedef int (* KLICK_INIT_FUNC)(void);
typedef int (* KLICK_EXIT_FUNC)(void);

#define KLICK_WINDOW_ACTIVE             0x0001
#define KLICK_CLEAR                                     0x0002

#define  KFC_DELETE     KFC_SOFT2
#define  KFC_BACKSPACE  KFC_SOFT3
#define  KFC_INSERT     KFC_SOFT1
#define  KFC_RETURN     KFC_SOFT4
#define  KFC_LNUP       KFC_CRUP
#define  KFC_LNDWN      KFC_CRDWN
#define  KFC_LNLFT      KFC_CRLFT
#define  KFC_LNRGT      KFC_CRRGT

#define  ALLE_CURSOR_TASTEN      KFC_CRUP,   KFC_CRDWN,  KFC_CRLFT,  KFC_CRRGT

#define  ALLE_TEXT_TASTEN        KFC_LNUP,   KFC_LNDWN,  KFC_LNLFT,  KFC_LNRGT, \
                                 KFC_DELETE, KFC_BACKSPACE, KFC_INSERT, KFC_RETURN

#define  ALLE_SOFTKEY_TASTEN     KFC_SOFT1,  KFC_SOFT2,  KFC_SOFT3,  KFC_SOFT4, KFC_SOFT5, KFC_SOFT6, KFC_SOFT7

#define  ALLE_PROG_TASTEN        KFC_PROG1,  KFC_PROG2,  KFC_PROG3,  KFC_PROG4, \
                                 KFC_PROG5,  KFC_PROG6,  KFC_PROG7,  KFC_PROG8

#define  ALLE_QUICK_TASTEN       KFC_QUICK1, KFC_QUICK2, KFC_QUICK3, KFC_QUICK4, \
                                 KFC_QUICK5, KFC_QUICK6, KFC_QUICK7, KFC_QUICK8, \
                                 KFC_QUICK9, KFC_QUICK10,KFC_ALARM

#define  ALLE_SEITEN_TASTEN      KFC_PGUP,   KFC_PGDWN, \
                                 KFC_PAGE,   KFC_LINE,   KFC_ERASE,  KFC_PRINT, \
                                 KFC_HELP,   KFC_PRMODE, KFC_BKGND,  KFC_WINDOW, \
                                 KFC_ZOOM,   KFC_OBJECT, KFC_AGGR,   KFC_STATION

#define  ALLE_SONDER_TASTEN      KFC_LANGUAGE

#define  ALLE_FUNKTIONS_TASTEN   ALLE_SEITEN_TASTEN,  \
                                 ALLE_QUICK_TASTEN,   \
                                 ALLE_SOFTKEY_TASTEN, \
                                 ALLE_PROG_TASTEN,    \
                                 ALLE_SONDER_TASTEN

#define  ALLE_ZIFFERN            '0','1','2','3','4','5','6','7','8','9'


#define  ALLE_GROSS_BUCHSTABEN   'A','B','C','D','E','F','G', \
                                 'H','I','J','K','L','M','N', \
                                 'O','P','Q','R','S','T','U', \
                                 'V','W','X','Y','Z'

#define  ALLE_KLEIN_BUCHSTABEN   'a','b','c','d','e','f','g', \
                                 'h','i','j','k','l','m','n', \
                                 'o','p','q','r','s','t','u', \
                                 'v','w','x','y','z'

#define  ALLE_SONDERZEICHEN      ' ', ',', ';', ':', '_', '+', \
                                 '\'', '*', '%', '/', '\\', '!', '?', ')', '('

#define  SONSTIGE_TASTEN         KFC_ENTER, '.', KFC_CLEAR, '-'

GLOBAL UWORD Klick_Mode( UWORD from );

/****************************************************************************
X  globale Funktionen
****************************************************************************/
GLOBAL int  DSPDispatch( void );
GLOBAL int  DSPReadChar( const BYTE * ret_flt, const BYTE * work_flt, BYTE* inp_ptr, ELEMENT* el_ptr );
GLOBAL void DSPInterpret( BYTE inp, BYTE ctrl );
GLOBAL void DSPShowPage( UWORD ctrl, BYTE type, UWORD par2 );
GLOBAL void DSPShowLine( BYTE type, ELEMENT* el_ptr, OBJECT* obj_ptr );
GLOBAL int  DSPGetPageInfo( DSP_PAGE_INFO* info );
GLOBAL int  DSPReadText( char* txt, int len, int prompt, const BYTE * ret_flt, const BYTE * wrk_flt );
GLOBAL int  DSPCheckActKey( BYTE from, ELEMENT* el_ptr );
GLOBAL int  INPInput( BYTE flt_nr, OBJECT* obj_ptr, ELEMENT* el_ptr );
GLOBAL long INPGetParam( UWORD ctrl, UWORD param );

GLOBAL UWORD ExecKlickMode(int id, int text1, int text2, UWORD flags,
                                                                           BYTE * wrk_filter, BYTE * ret_filter,
                                                                                KLICK_INIT_FUNC init_func, KLICK_EXIT_FUNC exit_func,
                                                                                KLICK_SET_FUNC set_func);

#endif /* ifndef _dispatch */
