/*.SH.***********************************************************************
*
* HEADER-DATEI-NAME:
*    IQTTSK.H 
*
* BESCHREIBUNG:
*    ...
*
* UMGEBUNG:
*    ZIELRECHNER:           IQT-450
*    ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*    UEBERSETZER:           c86 v3.3
*    OPTIONEN:              ...
*
* VERSION:
*    VERSION:    4.0                       DATUM:   01.04.92
*    AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*    AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*    AUTOR(EN):  -TS-   T. Schoenig        TELEFON: (0761) 42257
*
* HISTORY:
*    10.03.92 -TS-    Portierung des IQT-350 auf IQT-450
*    08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*    14.07.92 -TS-    Neues Fehlerkonzept
*    29.10.92 -TS-    Makros fuer set_priority() eingefuehrt.
*                                                    Diese ersetzen cli() und sti(), die nur task-lokal wirken.
*    06.04.93 -PR-    TskGetTaskName entfernt
*    06.07.93 -PR-    Module tskstat und iqttsk in iqttsk integriert
*                     Neue Funktionalitaet zur Protokollierung von Taskzustaenden
*                     und deren Darstellung ergaenzt.
*    08.10.97 -TSchw- TaskName eingetragen.
*    21.11.97 -TSchw- TSK_EVENT, TskSetEvent und TskWaitEvent entfernt, da
*                     die Eventflagfunktionalitaet jetzt in eventflg.c im
*                     Systembereich verwaltet wird. Ueberall, wo Eventflags
*                     verwendet werden, die neuen Funktionen und Typen
*                     eingetragen (siehe event).
*    26.11.97 -TSchw- IqtMsgPortDeInit eingetragen.
*    03.12.97 -TSchw- Umstellen auf neue Taskschnittstelle:
*                     TskStop, TaskId, TaskName, TskCycWait ersatzlos 
*                     geloescht; In der Struktur Semaphore die tskid
*                     durch tskind ersetzt, da nur der Index, nicht mehr
*                     die Id der Task definitiv ein Skalar ist.
*    20.03.98 -TSchw- TaskMutexDestroy eingefuegt
*    08.04.99 -TSchw- FifoRelease eingefuegt, in den Strukturen FIFO und
*                     FLAT_FIFO den Eintrag size von BYTE auf UWORD geaendert,
*                     in FifoInit, FifoInitPtr und FLAT_FifoInit den Parameter
*                     size von BYTE auf UWORD geaendert.
*    11.04.02 -HA-    DIAG_MESSAGE_LEN von 54 auf 60 erhoeht damit das Datum eingetragen werden kann.
*
*
*
*
*
* BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
* EXPORTSCHNITTSTELLE:
*
* PROTOTYPEN:
*    Keine
*
* DATENTYPEN:
*    Keine
*
*.EH.***********************************************************************/

#ifndef _iqttsk
#define _iqttsk

/*.SI.***********************************************************************/
#include <syntax.h>
#include <stdarg.h>
#include <timefunc.h>
#include <si86.h>
#include <errcode.h>
#include <stypes.h>
#include <iqtmem.h>
#include <events.h>
#include <tasks.h>
/*.EI.***********************************************************************/

/* ------------------------------------------------------------------------- *
 |                     F I F O - V e r w a l t u n g                         |
 * ------------------------------------------------------------------------- */

typedef struct {
   UWORD size;             /* Groesse eines Eintrages */
   int  maxnum;            /* Maximalzahl der Eintraege */
   int  actnum;            /* Aktuelle Anzahl der Eintraege */
   int  read;              /* Index des Lesezeigers */
   int  write;             /* Index des Schreibzeigers */
   BYTE memtype;           /* Speichertyp */
   void *fifo;                          /* Adresse der Fifo-Liste */
} FIFO;

typedef struct {
   UWORD size;             /* Groesse eines Eintrages */
   int  maxnum;            /* Maximalzahl der Eintraege */
   int  actnum;            /* Aktuelle Anzahl der Eintraege */
   int  read;              /* Index des Lesezeigers */
   int  write;             /* Index des Schreibzeigers */
   BYTE memtype;           /* Speichertyp */
   MEMORY_ADDRESS fifo; /* Adresse der Fifo-Liste */
} FLAT_FIFO;

/* Deklaration von Prototypen fuer Funktionen */

FIFO * FifoInitStruct(FIFO * ptr, void * buf, int num, UWORD size, int type, BOOL init);
FIFO * FifoInit(int mem_type, int num, UWORD size, BOOL init);
FIFO * FifoInitPtr(int mem_type, void * p, int num, UWORD size, BOOL init);
int  FifoRelease(FIFO * ptr);
void FifoFree(FIFO * ptr);
int  FifoPeek(FIFO * ptr, void * entryf, int n);
int  FifoChange(FIFO * ptr, void * entryf, int n);
int  FifoGet(FIFO * ptr, void * entryf);
int  FifoPut(FIFO * ptr, void * entryf);
int  FifoClear(FIFO * ptr, int n);

MEMORY_ADDRESS FLAT_FifoInit(BYTE segment, int num, UWORD size);
int FLAT_FifoPeek(MEMORY_ADDRESS fifo_addr, void * entryf, int n);
int FLAT_FifoChange(MEMORY_ADDRESS fifo_addr, void * entryf, int n);
int FLAT_FifoGet(MEMORY_ADDRESS fifo_addr, void * entryf);
int FLAT_FifoPut(MEMORY_ADDRESS fifo_addr, void * entryf);
int FLAT_FifoClear(MEMORY_ADDRESS fifo_addr, int n);
int FLAT_FifoLength(MEMORY_ADDRESS fifo_addr);

/* Als Macro implementierte Funktionen */
#define FifoSize(f)   ((f)->maxnum)
#define FifoLength(f) ((f)->actnum)
#define FifoEmpty(f)  (FifoLength(f) == 0)
#define FifoFull(f)   (FifoLength(f) == FifoSize(f))

/* ------------------------------------------------------------------------- *
 |                V e r w a l t e n   v o n   T a s k s                      |
 * ------------------------------------------------------------------------- */

/* Betriebsarten einer Task */
#define TSK_NORMAL  0      /* Normal (wird einmalig gestartet) */
#define TSK_TIMER   1      /* An Timer gebunden (Beenden mit TskStop) */

GLOBAL int TskStart(char * tname, int mode);
GLOBAL int TskWait(TIME wait);

/* ------------------------------------------------------------------------- *
 |                          S e m a p h o r e n                              |
 * ------------------------------------------------------------------------- */

#define USE_TASK_MUTEX
#ifdef  USE_TASK_MUTEX

#define SEMAPHORE TASKMUTEX
#define SemInit(sema, qsize)       TaskMutexCreate (sema, TASK_RECURSIVE_MUTEX)
#define SemInitPtr(sema, qsize, p) TaskMutexCreate (sema, TASK_RECURSIVE_MUTEX)
#define SemFree(sema)              TaskMutexDestroy (sema)
#define SemP(sema)                 TaskMutexLock (sema)
#define SemV(sema)                 TaskMutexUnlock (sema)
/* Bei Benutzung der TaskMutex-Funktionen sind die Count-Funktionen     */
/* leider prinzipiell nicht verfuegbar, da hier eine andere Task die    */
/* Semaphore freigeben kann als diejenige, die sie urspruenglich belegt */
/* hat. Und das ist bei TaskMutex nicht erlaubt!                        */
/* Statt den Count-Funktionen muessen deshalb die normalen Semaphoren-  */
/* Funktionen benutzt werden!                                           */
#define SemPCount(sema,count)      TaskMutexLock (sema)   
#define SemVCount(sema,count)      TaskMutexUnlock (sema) 

#else /* ! USE_TASK_MUTEX */

typedef struct {
        BYTE sem;                       /* Eigentliche Semaphorenvariable */
        FIFO * queue;      /* Zeiger auf Warteschlange */
        int  tskind;            /* Index der Task im kritischen Abschnitt */
        BYTE tskcount;          /* Zaehler fuer tskind */
}       SEMAPHORE;
/* Deklaration von Prototypen fuer Funktionen */

GLOBAL int SemInit(SEMAPHORE * sema, int queue_size);
GLOBAL int SemInitPtr(SEMAPHORE * sema, int queue_size, void * p);
GLOBAL void SemFree(SEMAPHORE * sema);
GLOBAL void SemP(SEMAPHORE * sema);
GLOBAL void SemV(SEMAPHORE * sema);
GLOBAL void SemPCount(SEMAPHORE * sema, int * count);
GLOBAL void SemVCount(SEMAPHORE * sema, int * count);

#endif

/* ------------------------------------------------------------------------- *
 |                           M e l d u n g e n                               |
 * ------------------------------------------------------------------------- */

/* Konstanten fuer den Meldungsfilter */
#define MSG_MIN 0x00       /* Erste moegliche Meldungs-ID */
#define MSG_MAX 0xff       /* Letzte moegliche Meldungs-ID */

/* Parameter beim Aufruf von IqtMsgSend */
#define MSG_NOWAIT      0               /* Keine Antwort abwarten */
#define MSG_WAIT        1               /* Auf Antwort warten */

typedef struct {
        EVENT_T event;       /* (fuer Betriebssystem) */
   SEMAPHORE sema;      /* Schutz fuer die Queue-Bearbeitung */
        int count;                              /* Anzahl der eingetroffenen Meldungen */
        void * first;                   /* Zeiger auf ersten Msg-Knoten */
        void * last;                    /* Zeiger auf letzten Msg-Knoten */
}       MSGPORT;

typedef struct message {
        struct message * next;  /* Naechste Meldung am MsgPort */
        MSGPORT * sender;               /* Adresse des Absender-Ports */
        MSGPORT * receiver;             /* Adresse des Empfaenger-Ports */
        BYTE id;                                /* Kennung der Meldung */
        UWORD wparam;                   /* 1. Parameter: 16 Bit */
        ULONG lparam;                   /* 2. Parameter: 32 Bit */
}       MESSAGE;

GLOBAL void IqtMsgPortInit(MSGPORT * mport);
GLOBAL void IqtMsgPortDeInit(MSGPORT * msgport);
GLOBAL int IqtMsgSend(MESSAGE * msg, int wait);
GLOBAL int IqtMsgPeek(MSGPORT * mport, BYTE flo, BYTE fhi);
GLOBAL MESSAGE * IqtMsgGet(MSGPORT * mport, BYTE flo, BYTE fhi);
GLOBAL MESSAGE * IqtMsgFetch(MSGPORT * mport, BYTE flo, BYTE fhi);

/* Als Macro implementierte Funktionen */
#define IqtMsgCount(p)  ((p)->count)
#define IqtMsgReply(m)  TskEventSet(&(m)->sender->event)

/* ------------------------------------------------------------------------- *
 |                 S p e i c h e r v e r w a l t u n g                       |
 * ------------------------------------------------------------------------- */

/* Speichertypen */
#define MEM_DRAM  0        /* Normales dynamisches RAM */
#define MEM_BBRAM 1        /* Battery backup RAM */
#define MEM_EXP_BBRAM 2    /* Erweitertes Battery backup RAM */

/* ------------------------------------------------------------------------- *
 |                            T a s k f l a g s                              |
 * ------------------------------------------------------------------------- */

/*------------------------------------------------------------------*
 | Makros zum Bearbeiten der Bitleisten                             |
 *------------------------------------------------------------------*/

/* Die folgenden drei Makros koennen zum Setzen, Rcksetzen und Abfragen einer*/
/* beliebigen Bitleiste verwendet werden. Die Bitleiste mua als BYTE-Array  */
/* definiert sein.                                                          */
/* A = Anfangsadresse der Bitleiste                                         */
/* N = Index des zu bearbeitenden Bits in der Bitleiste                     */

#define  GET_BIT(A,N)     ((A)[(N)>>3] & 1<<((N)&7) ? 1 : 0)
#define  RESET_BIT(A,N)   ((A)[(N)>>3] &= ~(1<<((N)&7)))
#define  SET_BIT(A,N)     ((A)[(N)>>3] |= 1<<((N)&7))

typedef BYTE TASKFLAGS;

GLOBAL int TskGetFlag(TASKFLAGS * flags);
GLOBAL void TskSetFlag(TASKFLAGS * flags, int val);

#define FLAG_PRIVATE            0x00000001L

GLOBAL int TskSetMode(ULONG mode);
GLOBAL int TskResetMode(ULONG mode);
GLOBAL BOOL TskMode(ULONG mode);

 /* ------------------------------------------------------------------------- *
 |                     D i a g n o s e l o g b u c h                         |
 * ------------------------------------------------------------------------- */

typedef struct {
        int  diag;                      /* Nummer der Diagnosemeldung */
        ULONG param;            /* Beliebiger Parameter */
        UWORD task;              /* Kennung (TaskIndex) des aufrufenden Tasks */
}       DIAG_MSG;

#define DIAG_MESSAGE_LEN  60
typedef struct {
        char diag_msg[DIAG_MESSAGE_LEN];
}       DIAG_MESSAGE;

GLOBAL int DiagBufInit(BOOL init_bbram);
GLOBAL int DiagPutMsg(int diag, ULONG param, UWORD tid, char * mname, int l_no); 
GLOBAL int DiagPeekMsg(char * diag_msg, int n);
GLOBAL int DiagPrintMsg(int diag, char * fmtstr, ...);
GLOBAL int XDiagPrintMsg(int diag, char * fmtstr, va_list args);

/*------------------------------------------------------------------*
 | Task-Verwaltungsfunktionen                                       |
 *------------------------------------------------------------------*/


#endif /* _iqttsk */
























