
#ifndef __target__
#define __target__


/******************************************************************************
*  Dateiname : target.h
*
*  *** HISTORY ***
*  27.01.98 -TSchw-  History angelegt, Windows-spezifische Konstanten einge-
*                    tragen.
*  12.08.98 -TSchw-  __NT_DRIVER__ Spezifika eingetragen
*  22.05.01 -TSchw-  __QT__ eingetragen zusätzlich zu __WIN32__ und __LINUX__
*
*  Beschreibung :
*     Definition der Plattformkonstanten. Diese Konstanten werden zum Platt-  
*     formabhaengigen Uebersetzen benutzt.                                    
*     Bisher definiert: __QNX2__    : QNX 2                                   
*                       __QNX4__    : QNX 4                                   
*                       __QNXNTO__  : Neutrino                                
*                       __WIN32__   : Windos NT / Windows 95                  
*                       __LINUX__   : Linux
*                       __QT__      : Qt-Lib (zusätzlich zu Linux und NT)
******************************************************************************/


#ifdef __QNX__
#ifndef __QNXNTO__
#define __QNX4__
#endif
#define far
#elif defined __NT__
#define __WIN32__
#elif defined QNX
#define __QNX2__
#elif defined linux
#define __LINUX__
#define far
#endif

/* Unter Windows und Linux wird die Qt-Library benutzt */
#if defined (__WIN32__) || defined (__LINUX__)
#define __QT__
#endif

/* Definition einiger Plattformabhaengiger Konstanten */

typedef unsigned char  BYTE;
typedef unsigned short UWORD;
typedef unsigned long  ULONG;

#define USR_NO_ERROR 0
#define USR_ERROR    1


/* Unter Windows NT ist ULONG und BOOL bereits definiert, und zwar anders als*/
/* im IQT. Deshalb wird nur noch ULONG und UWORD benutzt. Ebenso ist ERROR  */
/* und NO_ERROR bereits (anders) definiert.                                 */

#ifdef __WIN32__
#ifndef NOSYSINCLUDES
#include <windows.h>
//#include <winbase.h>
#endif
#ifndef BOOL
typedef int BOOL;                             /* Bereits von NT definiert   */
#endif
#ifndef WORD
#define WORD UWORD                            /* alte Form von UWORD        */
#endif
#ifndef LONG
#define LONG ULONG                            /* alte Form von ULONG        */
#endif

#elif defined __NT_DRIVER__

#include <ntddk.h>
#ifndef BOOL
typedef int BOOL;                             /* Bereits von NT definiert   */
#endif

#else

#define WORD UWORD                            /* alte Form von UWORD        */
#define LONG ULONG                            /* alte Form von ULONG        */
typedef unsigned char BOOL;                   /* alte Form von BOOL         */

#define NO_ERROR USR_NO_ERROR                 /* alte Form von USR_NO_ERROR */
#define ERROR    USR_ERROR                    /* alte Form von USR_ERROR    */

#endif

#define BREAK_IT	*(int*)NULL = 0;

#if defined __LINUX__
#  define strnicmp strncasecmp
#endif


/******************************************************************************
*  Alignement
*
*  Linux:   Datei target.h
*           Unter Linux kann man zwar die Compileroption -Fpack_struct angeben,
*           um alle Strukturen ohne Löcher anzulegen, wie es vom IQT teileweise
*           zwingend vorgesehen ist (Datenträger, Host), doch dann werden auch
*           die Strukturen aus den Standardincludefiles so angeleget, während
*           sie von der C-Library ungepackt verwendet werden. Dies führt zu
*           schwer auffindbaren Fehlern. Leider gibt es auch keine Möglichkeit,
*           das Packen im einzelnen zu verhindern (__attribute((align)) wirkt
*           nicht auf die einzelnen Elemente einer Struktur.
*           Als Lösung bleibt nur, das IQT komplett ohne -Fpack_struct zu
*           übersetzen, und die einzelnen Strukturen als gepackt zu definieren,
*           wo dies erforderlich ist. Dies geschieht mit dem unten definierten
*           Makro STRUCT_PACKED.
*           Das Makro STRUCT_PACKED wirkt nur auf eine einzelne Struktur/Union
*           und wird unmittelbar nach der schließenden geschweiften Klammer der
*           Strukturdeklaration aufgerufen:
*              typedef struct {...} STRUCT_PACKED name;
*           STRUCT_PACKED wirkt nur auf die einzelnen Elemente einer Struktur
*           und nicht auf untergeordnete Strukturelemente. Enthält eine Sturktur
*           weitere structs, so müssen diese auch wieder mit STRUCT_PACKED
*           deklariert werden!
*
*  Windows: Dateien packstart.h, packstop.h
*           Unter Windows wird das Packen von Strukturen mit einem Compiler-
*           schalter (pragma) ein- und ausgeschaltet. Diese Compilerschalter 
*           müssen vor und nach der zu packenden Struktur aufgerufen werden.
*           Da sich das Pragma nicht in einem define verstecken lässt, muß
*           man zu diesem Zweck jeweils ein Includefile aufrufen, das das
*           pragma enthält:
*              include <packstart.h>
*              typedef struct {...} name;
*              include <packstop.h>
*
*  Das Ein- und Ausschalten des Packens von Strukturen geschieht also auf den
*  verschiedenen Systemem mit zwei unterschiedlichen Methoden. Einmal durch
*  eine Erweiterung der Deklaration von Strukturen (siehe Linux), das andere
*  mal durch Compilerschalter (siehe Windows). Um portabel zu bleiben, müssen
*  beide Methoden gleichzeitig angewendet werden, wobei alternativ nur die
*  jeweils passende davon eingeschaltet ist:
*              include <packstart.h>
*              typedef struct {...} STRUCT_PACKED name;
*              include <packstop.h>
*
******************************************************************************/

#if defined __LINUX__ || defined __QNXNTO__ || defined __QNX4__
#  define STRUCT_PACKED __attribute__ ((packed))
#else
#  define STRUCT_PACKED
#endif

#endif /*__target__*/



