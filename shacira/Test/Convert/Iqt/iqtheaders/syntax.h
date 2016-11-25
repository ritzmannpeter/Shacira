#ifndef __syntax__
#define __syntax__

/******************************************************************************
*  Dateiname : Syntax.H
*
*  *** HISTORY ***
*  23.05.89   -MW/TE-   Am Anbeginn schufen -MW/TE- die History
*  21.06.89   -MW-      MIN und MAX als Macros eingebaut
*  09.02.90   -TSchw-   MIN, MAX, ABS, SGN in Macros.H ausgelagert
*  12.03.90   -SF-      "Void" durch char ersetzt, da void * Name[] nicht geht
*  01.04.92   -SF-      ERROR, NO_ERROR definiert
*                       MIN und MAX neu angelegt, da c86 dumm
*  22.04.97   -PR-      Nur das Notwendigste hat ueberlebt
*
*  Beschreibung :
*     Programmiervereinbarungen zur besseren Lesbarkeit der C - Programme
*     mittels  C - Praeprozessor und einiger Datentypen.
******************************************************************************/

#include <target.h>

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

#define LOCAL static
#define GLOBAL

#define MIN(a,b)	((a)<(b) ? (a) : (b))
#define MAX(a,b)	((a)>(b) ? (a) : (b))

#define SYSTEM_ERR_BASE									-300
#define SYSTEM_ERROR(err)	((short)err > 0 ? SYSTEM_ERR_BASE - (short)err : (short)err)

#define far
#ifdef lassma
#define TASKID int
#define TASKONCE int
#define TASKKEY int
#define TASKMUTEX int
#define TASKCOND int
#endif

#endif /*__syntax__*/

