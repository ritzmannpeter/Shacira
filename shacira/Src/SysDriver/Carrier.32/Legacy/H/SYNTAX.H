

#ifndef _syntax
#define _syntax

/******************************************************************************
*  Dateiname : Syntax.H
*
*  *** HISTORY ***
*  23.05.89   -MW/TE-   Am Anbeginn schufen -MW/TE- die History
*  21.06.89   -MW-      MIN und MAX als Macros eingebaut
*  09.02.90   -TSchw-   MIN, MAX, ABS, SGN in Macros.H ausgelagert
*  12.03.90   -SF-      "Void" durch char ersetzt, da void * Name[] nicht geht
*
*  Beschreibung :
*     Programmiervereinbarungen zur besseren Lesbarkeit der C - Programme
*     mittels  C - Praeprozessor und einiger Datentypen.
******************************************************************************/
#ifndef __platform__
#include <platform.h>
#define __platform__
#endif

#define LOCAL static
#define GLOBAL

typedef unsigned short USR_WORD;
typedef unsigned char USR_BYTE;
typedef unsigned long USR_LONG;
typedef unsigned char USR_BOOL;
#define FALSE 0
#define TRUE  1

#define If if
#define Then {
#define Else } else {
#define Elseif } else if
#define Endif }

#define For for
#define Do {
#define Endfor }

#define While while
#define Endwhile }

#define Repeat do {
#define Until(COND) } while(! (COND) )

#define Switch(X) switch(X) {
#define Case case
#define Default default
#define Endswitch }

#define USR_NO_ERROR        0

#endif /* _syntax */

