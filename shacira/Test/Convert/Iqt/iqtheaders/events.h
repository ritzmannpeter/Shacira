
#ifndef __events__
#define __events__

/*.SI.***********************************************************************/
#include <syntax.h>
#include <tasks.h>
/*.EI.***********************************************************************/

#if defined(__QNXNTO__) || defined(__QNX4__) || defined(__LINUX__)
typedef struct event_t
{	BOOL              condition;
	pthread_mutex_t   mutex;
	pthread_cond_t    condvar;
}	EVENT_T;
#elif defined __QNX2__
#elif defined __WIN32__
#include <windows.h>
//#include <winbase.h>

typedef struct event_t
{
   BOOL              condition;  // Für Simulation mittels Polling
   HANDLE            winevent;
}	EVENT_T;
#endif

GLOBAL int TskEventInit (EVENT_T * event);
GLOBAL int TskEventDeInit (EVENT_T * event);
GLOBAL int TskEventSet (EVENT_T * event);
GLOBAL int TskEventWait (EVENT_T * event);
GLOBAL int TskEventTimedWait (long timeout, EVENT_T *event);

#endif /* __events__ */
