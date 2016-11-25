/******************************** SBB **********************************
**
** Project      :       Multiple-Threaded Library (MTL)
**
** Author       :       Zhang Xiangyang
**
** Date         :       November 4, 1996
**
** Version      :       1.0
**              :       Copyright (C) 1996, Zhang Xiangyang
**                
** File name    :       pthread.c
**
** Description  :
**
**      This file is part of pthread Library, which provides the thread 
**      interface compatible with POSIX 1003.4a Reference.
**
**      Report problems and direct all questions to:
**       zhangx@sebb.bel.alcatel.be
**
********************************HISTORY*********************************
**   DATE    INITIALS	COMMENTS		
**   ----    --------	--------
** 04/11/96  XZHANG     Creation for version 1 only
**
************************************************************************/

#ifndef _PTHREAD_H_INCLUDED
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <setjmp.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>  /* needed for struct timeval */

#ifndef TRUE             
#define TRUE                          1	
#endif

#ifndef FALSE
#define FALSE                         0
#endif

#ifndef _POSIX_DATAKEYS_MAX
#define _POSIX_DATAKEYS_MAX           8
#endif

#ifndef _POSIX_TIMER_MAX
#define _POSIX_TIMER_MAX              32
#endif

/* contentionscope attribute values */
#define PTHREAD_SCOPE_GLOBAL            0
#define PTHREAD_SCOPE_LOCAL             1

/* delivery modes */
#define PTHREAD_PROCSYNC                0
#define PTHREAD_PROCASYNC               1

#define MUTEX_FAST                      0
#define MUTEX_RECURSIVE                 1
#define MUTEX_NORECURSIVE               2

/* inheritsched attribute values */
#define PTHREAD_INHERIT_SCHED           0
#define PTHREAD_DEFAULT_SCHED           1

#define SCHED_FIFO                      0
#define SCHED_RR                        1
#define SCHED_FG_NP                     2
#define SCHED_OTHER                     SCHED_FG_NP	

#define CANCEL_OFF                      0
#define CANCEL_ON                       1

typedef void                            * any_t;

/************************************************************/
/*
 * Mutex objects.
 */
/************************************************************/

typedef int        pthread_protocol_t;
typedef signed int pthread_key_t;

                  
typedef struct 
{
  char                          lock;
  pthread_key_t                 owner;
  int                           flags;
  int                           prio_ceiling;
  pthread_protocol_t            protocol;
  int                           prev_max_ceiling_prio;
} pthread_mutex_t;

typedef struct 
{
  int                           flags;
  int                           prio_ceiling;
  pthread_protocol_t            protocol;
} pthread_mutexattr_t;

/************************************************************/
/*
 * Once Objects.
 */
/************************************************************/

typedef struct 
{
  short                          init;
  short                          exec;
  pthread_mutex_t                mutex;
} pthread_once_t;

#define PTHREAD_ONCE_INIT {FALSE, FALSE, 0, };

/*
 * Condition variables.
 */
typedef struct 
{
  int                          flags;
  int                          waiters;
  pthread_mutex_t              * mutex;
} pthread_cond_t;

typedef struct 
{
  int                          flags;
} pthread_condattr_t;

/************************************************************/
/*
 * Threads.
 */
/************************************************************/

typedef any_t (* pthread_func_t) (int __arg);
typedef void (* pthread_sighandler_t) (int);

typedef struct 
{
    int             flags;
    int             stacksize;
    int             contentionscope;
    int             inheritsched;
    int             detachstate;
    int             sched;
    int             prio;  		/* (Active) priority of Thread */
    struct timespec starttime;
    struct timespec deadline; 
    struct timespec period;
} pthread_attr_t;

struct cleanup {
  void (*func)();
  any_t arg;
  struct cleanup *next;
};

typedef struct cleanup            * cleanup_t;

typedef pthread_key_t             pthread_t;

#ifdef __cplusplus
extern "C" {
#endif


/************************************************************/
/* Mutex Attributes Functions */
/*       Mutex Functions      */
/************************************************************/

extern int pthread_mutex_lock     (pthread_mutex_t *__mutex);
extern int pthread_mutex_trylock  (pthread_mutex_t *__mutex);
extern int pthread_mutex_unlock   (pthread_mutex_t *__mutex);
extern int pthread_mutex_init     (pthread_mutex_t *__mutex,
                                   pthread_mutexattr_t *__attr);
extern int pthread_mutex_destroy  (pthread_mutex_t *__mutex);

extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_getkind_np (pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_setkind_np (pthread_mutexattr_t *__attr,
                                         int __kind);

/************************************************************/
/*      Condition Functions    */
/*Condition Attribute Functions*/
/************************************************************/

 
extern int pthread_cond_destroy     (pthread_cond_t *__cond);
extern int pthread_cond_init        (pthread_cond_t *__cond,
                                     pthread_condattr_t *__attr);
extern int pthread_cond_wait        (pthread_cond_t *__cond,
                                     pthread_mutex_t *__mutex);
extern int pthread_cond_timedwait   (pthread_cond_t *__cond,
                                     pthread_mutex_t *__mutex,
                                     struct timespec *__timeout);
extern int pthread_cond_signal      (pthread_cond_t *__cond);
extern int pthread_cond_broadcast   (pthread_cond_t *__cond);
extern int pthread_condattr_init    (pthread_condattr_t *__attr);
extern int pthread_condattr_destroy (pthread_condattr_t *__attr);


/************************************************************/
/*      Thread Functions      */
/* Thread Attribute Functions */
/************************************************************/

extern void pthread_init                (void);
extern pthread_t pthread_self           (void);

extern int pthread_cancel               (pthread_t *__thread);
extern int pthread_setcancel            (int __state);
extern void pthread_testcancel           (void);

extern int pthread_create               (pthread_t *__thread,
                                         pthread_attr_t *__attr,
                                         pthread_func_t __func(),
                                         int __arg);
extern int pthread_detach               (pthread_t *__thread);
extern int pthread_join                 (pthread_t * __thread, int * __status);
extern void pthread_exit                (int __status);
extern void pthread_yield               (void);

extern int pthread_getprio              (pthread_t *__thread);
extern int pthread_setprio              (pthread_t *__thread, int priority);


extern int pthread_getscheduler         (pthread_t *__thread);
extern int pthread_setscheduler         (pthread_t *__thread, int scheduler,
                                         int priority);
extern int pthread_attr_init            (pthread_attr_t *__attr);
extern int pthread_attr_destroy         (pthread_attr_t *__attr);
extern int pthread_attr_getstacksize    (pthread_attr_t *__attr,
										 size_t * __stacksize);
extern int pthread_attr_setstacksize    (pthread_attr_t *__attr, 
										 size_t __stacksize);
extern int pthread_attr_getscope        (pthread_attr_t *__attr);
extern int pthread_attr_setscope        (pthread_attr_t *__attr,
                                         int __contentionscope);
extern int pthread_attr_getinheritsched (pthread_attr_t *__attr);
extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
                                         int __inherit);
extern int pthread_attr_getsched        (pthread_attr_t *__attr);
extern int pthread_attr_setsched        (pthread_attr_t *__attr,
                                         int __scheduler);
extern int pthread_attr_getprio         (pthread_attr_t *__attr);
extern int pthread_attr_setprio         (pthread_attr_t *__attr,
                                         int __priority);
extern int pthread_get_priority_max     (void);
extern int pthread_get_priority_min     (void);

extern int pthread_key_create           (pthread_key_t *__key,
                                         void (*__func) (int __value));
extern int pthread_setspecific          (pthread_key_t __key,
                                         int __value);
extern int pthread_getspecific          (pthread_key_t __key,
                                         int *__value);
extern int pthread_cleanup_pop          (int __execute);
extern int pthread_cleanup_push         (void (*__func) (any_t __value),
                                         any_t __arg);

extern int pthread_once                 (pthread_once_t *__once_c,
                                         void (*__func) (any_t __value));

extern int pthread_delay_np             (struct timespec * interval);
extern void pthread_lock_global_np      (void);
extern void pthread_unlock_global_np    (void);



#ifdef __cplusplus
} /* extern "C" */
#endif

/*  DEFINED BY ZHANG XIANGYANG
extern int pthread_get_nthread(void);
extern int pthread_set_maxthread(int maxnumber);
extern int pthread_get_maxthread(void);
extern int pthread_perror(char *__string, int errno);

not included in the file:
extern int nThreads;
extern int maxThreads;
*/

#define _PTHREAD_H_INCLUDED
#endif /* !_PTHREAD_H_INCLUDED */
