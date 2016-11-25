#ifndef __tasks__
#define __tasks__

/*.SI.**********************************************************************/
#include <syntax.h>
#include <stypes.h>
/*.EI.**********************************************************************/

/***************************************************************************/
/****  Betriebssystemspezifische Deklarationen *****************************/
/***************************************************************************/

#if defined(__QNXNTO__) || defined(__QNX4__) || defined (__LINUX__)
/***************************************************************************/
/****  Neutrino, Posix 1003.1c  ********************************************/
/***************************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#ifdef __QNXNTO__
#include <pthread.h>
#include <sys/neutrino.h>
#endif
#ifdef __QNX4__
#include <posix/pthread.h>
#endif
#ifdef __LINUX__
#include <pthread.h>
#endif
#include <si86.h>             /* wegen Disable(), Enable()                 */

#define Disable() _disable()
#define Enable() _enable()  

typedef struct	_taskid 
{
	pthread_t		ThreadId;   /* handle of system thread_id                */
} TASKID;

typedef	struct	_task_key 
{
	pthread_key_t	Key;        /* handle of system key                      */
} TASKKEY;

typedef	struct	_task_mutex 
{	int               Type;    /* 0 = non-recursive : 1 = recursive         */
	int               LCnt;    /* number of locks acquired by owner of mutex*/
	pthread_t         Owner;   /* owner of mutex                            */
	pthread_mutex_t   Mutex;   /* handle of system mutex                    */
   ULONG             Magic;   /* to test initialized state                 */
   int               taskindex; /* Index der Task, die die Mutex besitzt   */
}	TASKMUTEX;

typedef	struct	_task_cond 
{	pthread_cond_t	Cond;       /* handle of system mutex                    */
}	TASKCOND;

#define	TASKONCEINIT PTHREAD_ONCE_INIT
typedef	pthread_once_t	TASKONCE; 

#elif defined __WIN32__
/***************************************************************************/
/****  Win 32 (Windows NT)  ************************************************/
/***************************************************************************/

#define MAXCOND      2
#define MANUAL_EVENT 0x00
#define AUTO_EVENT   0x01

#define	TASKONCEINIT {1,0}

typedef struct	_task_once 
{  long     lock;
   int      initialized;
}	TASKONCE;

typedef struct	_taskid 
{  int      DetachState;   /* handle closed                                */
   DWORD    ThreadId;      /* handle of system thread_id                   */
   HANDLE   ThreadHandle;  /* pseudo handle of thread                      */
}	TASKID;

typedef struct _task_mutex 
{  int      Type;          /* 0 = non-recursive : 1 = recursive            */
   int      LCnt;          /* number of locks acquired by owner of mutex   */
   DWORD    Owner;         /* owner of mutex                               */
   HANDLE   Mutex;         /* handle of system mutex                       */
   ULONG    Magic;         /* to test initialized state                    */
   int      taskindex;     /* Index der Task, die die Mutex besitzt        */
}	TASKMUTEX;

typedef	struct	_task_key 
{	DWORD    Key;           /* handle of system key                         */
}	TASKKEY;

typedef struct _task_cond 
{  int      nWaiters;
   HANDLE   hEvents[MAXCOND];
}	TASKCOND;

#endif

/***************************************************************************/
/****  Betriebssystemunabhaengige Deklarationen ****************************/
/***************************************************************************/


/****  Konstanten: *********************************************************/

/* MUTEX TYPES */
#define	TASK_NON_RECURSIVE_MUTEX 1
#define	TASK_RECURSIVE_MUTEX     2

#define	TASK_SUCCESS             0
#define	TASK_ER_SYSERR          -1
#define	TASK_ER_INTERNAL        -2
#define	TASK_ER_MEMORY          -4
#define	TASK_ER_NOT_IMPLEMENTED -5
#define	TASK_ER_DETACHED        -6
#define  TASK_ER_PRIO            -7
#define  TASK_ER_TOOMUCH         -8
#define  TASK_ER_ID              -9
#define  TASK_ER_INDEX           -10

/* MUTEX ERROR CODES */
#define	TASK_ER_MUTEX_CREATE    -40
#define	TASK_ER_MUTEX_LOCKED    -41
#define	TASK_ER_MUTEX_UNLOCKED  -42
#define	TASK_ER_MUTEX_NOTOWNER  -43
#define	TASK_ER_MUTEX_RELEASE   -44
#define	TASK_ER_MUTEX_NOTINIT   -45
#define	TASK_ER_MUTEX_NOTSUPORT -46

/* KEY ERROR CODES */
#define	TASK_ER_KEYBINDING      -50
#define	TASK_ER_KEYCAPACITY     -51
#define	TASK_ER_KEYINVALID      -52

/* TASKFLAG ERROR CODES */
#define  TASK_ER_FLAGID          -60


#define TASK_DEFAULT_STACKSIZE	0

#define TASK_SCHED_FIFO    0
#define TASK_SCHED_RR      1

#define TASK_MAX_NAME_LEN  30
#define MAX_TASKS	         256

#define TASK_MIN_PRIO      0
#define TASK_MAX_PRIO      31

/****  Typdefinitionen: ***************************************************/

/* Parameterstruktur fuer TaskStart:                                       */
typedef struct {
   long        StackSize;        /* Stackgroesse oder 0                    */
   int         Prio;             /* Prioritaet, 0 (hoechste) - 31(kleinste)*/
   int         DetachFlag;       /* 0 = joinable, 1 = detached             */
   int         Scheduling;       /* TASK_SCHED_FIFO: Prioritaetsbasiert    */
                                 /* TASK_SCHED_RR:   Prioritaetsbasiert mit*/
   /* Returnvariablen: */        /*                  Zeitscheiben          */
   TASKID      TaskId;           /* Task-ID Struktur                       */
} TASKINITDATA;


/****** Taskverwaltungsfunktionen: *****************************************/

/* Taskmanipulation */
GLOBAL int     TaskStart(void *(*task_routine)(void *), 
               char *name, void *arg, TASKINITDATA *initdata);
GLOBAL int     TaskStop (TASKID *task_id);
GLOBAL void    TaskExit (void* exit_code);
GLOBAL int     TaskJoin (TASKID *task_id, void **status);
GLOBAL void    TaskYield (void);
GLOBAL void    TaskOnce(void (*once_function)(), TASKONCE *once_variable);
GLOBAL int     TaskSuspend(long secs, long msecs);
GLOBAL int     TaskSetPriority(TASKID *task_id, int prio);

/* Taskinformation */
GLOBAL TASKID *TaskGetMyId (void);
GLOBAL int     TaskGetMyIndex (void);
GLOBAL char   *TaskGetMyName (void);
GLOBAL BOOL    TaskIsMyName (char *task_name);
GLOBAL int     TaskGetIndexByName (char *task_name);
GLOBAL TASKID *TaskGetId (int task_index);
GLOBAL char   *TaskGetName (int task_index);
GLOBAL int     TaskGetPrio (int task_index);
GLOBAL long    TaskGetStackSize (int task_index);
GLOBAL int     TaskGetDetachFlag (int task_index);
GLOBAL int     TaskGetScheduling (int task_index);

/* Taskflags */
GLOBAL int     TaskSetFlag (int flag_id);
GLOBAL int     TaskResetFlag (int flag_id);
GLOBAL BOOL    TaskGetFlag (int flag_id);

/* Taskstatus */
GLOBAL int     TaskSetState (int task_state);
GLOBAL int     TaskGetState ();

/* Taskspezifische Fehler */
GLOBAL int     TaskGetErrno ();
GLOBAL void    TaskSetErrno (int errval);


/****** Verwaltung Taskspezifischer Daten: *********************************/

GLOBAL int     TaskKeyCreate   (TASKKEY *task_key, void (*destructor_func)(),
                                int key_size);
GLOBAL int     TaskKeySetValue (TASKKEY *task_key, void *value);
GLOBAL void   *TaskKeyGetValue (TASKKEY *task_key);


/****** Mutex-Verwaltung: **************************************************/

GLOBAL int     TaskMutexCreate (TASKMUTEX *task_mutex, int mutex_type);
GLOBAL int     TaskMutexDestroy(TASKMUTEX *task_mutex);
GLOBAL int     TaskMutexLock   (TASKMUTEX *task_mutex);
GLOBAL int     TaskMutexUnlock (TASKMUTEX *task_mutex);


/****** Ereignisvariablen-Verwaltung: **************************************/

GLOBAL int     TaskCondCreate    (TASKCOND *task_cond);
GLOBAL int     TaskCondWait      (TASKCOND *task_cond, TASKMUTEX *task_mutex);
GLOBAL int     TaskCondBroadcast (TASKCOND *task_cond);


/****** Kompatibilitaets-Funktionen: ***************************************/

#define GetTid()  /* gibt's nicht mehr, nur noch als Parameter fur GetTind */
#define GetTind(dummy) TaskGetMyIndex()

#endif /* __tasks__ */
