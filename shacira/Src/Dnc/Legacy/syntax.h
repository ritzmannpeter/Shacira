

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


typedef unsigned long TIME;
typedef int SEMAPHORE;
#define DiagPutMsg(type, c1, c2, file, line) 	-1
#define MemAlloc(size)	calloc(1, size)
#define MemFree(buf)	free(buf)
#define SemInit(sem,size)
#define SemP(sem)
#define SemV(sem)
#define MIN(x1,x2) (x1 > x2) ? x2 : x1

typedef unsigned char unsigned_8;
typedef unsigned short unsigned_16;
typedef unsigned long unsigned_32;
typedef char signed_8;
typedef short signed_16;
typedef long signed_32;

#define HAlloc(size)	calloc(1, size)
#define HFree(buf)	free(buf)

#include "legacy.h"

#endif /* _syntax */

