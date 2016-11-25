// ===========================================================================
// base/thread.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Todo-List: Pthreads & andere
// - auto_del: darf der calling thread den Destruktor aufrufen oder nicht?
// - detach <-> joinable
// - Sporadische Memory-Leaks bei pthreads: Mögliche Ursache: wenn der Destructor bereits
//   beendet ist, ein detached pthread aber noch nicht sein cleanup gemacht hat???
//   -> pthreads immer mit join abschliessen
// - thread restart, wait-events bei start


// Interface header
#include "base/thread.h"

// Platform dependant header
#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #define INCL_DOSPROCESS       /* DosSetPriority */
   #include <os2.h>
#elif defined __ECL_W32__
   #include <process.h>
   #include <windows.h>
   #if defined __ECL_PTHREADS__
      #include <sys/timeb.h>
      // pthreads gehoeren unter Windows nicht zu den Systemheadern, sondern
      // kommen aus dem benutzerdefinierten 3rd_party Zweig. Damit der Header
      // gefunden werden kann, das #include mit "..." statt <...>
      #include "pthread.h"
   #endif
#elif defined __ECL_LINUX__
   #include <sys/time.h>
   #include <pthread.h>
#endif




// Die Klasse cExceptionHandler ("Exception-Handler fuer Threads") scheint
// ein Relikt aus alten OS/2 Tagen zu sein (siehe "base/obsolete/eb_except.*").
// Für Win32 gibt's nur eine Dummy-Implementierung weswegen -TE- wohl schon
// laenger per Compiler-Schalter die Nutzung unterbunden hat. Ich habe den
// Compiler-Schalter jetzt auf *alle* ueberfluessigen Code-Teile ausgeweitet!
// -MW- 2005-11-04
#undef __Use_Exception_Handler__




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ (identifizieren cThread-Modul)
const unsigned long THREAD_ERROR = cBase::dbgIpc | cBase::dbgError | cBase::dbgAssert;
const unsigned long THREAD_WARN  = cBase::dbgIpc | cBase::dbgWarn;
const unsigned long THREAD_INFO  = cBase::dbgIpc | cBase::dbgInfo;


// ===========================================================================
// Private data
// ===========================================================================

// Data structure
struct cThread::cPrivate {
   cPrivate(int stacksize, AUTO_DEL auto_del, int argc, char **argv);
   ~cPrivate();

   static cThread *main_thread;
   
   int argc;                     //!< Anzahl Kommandozeilen-Argumente (Main-Thread)
   char **argv;                  //!< Zeiger auf Argument-Vektor (Main-Thread)

   int tid;                      //!< Thread-ID dieses Threads
   STATE state;                  //!< Aktueller Zustand des Threads
   AUTO_DEL auto_del;            //!< Automatisches delete bei Thread-Ende?
#ifdef __Use_Exception_Handler__
   int guard_count;              //!< Zaehlt Anzahl der 'Guard Page Violations'
#endif
   int rc;                       //!< Returncode von onMain

   int stacksize;                //!< Stackgroesse
   void *init_data;              //!< Initialisierungsdaten (Parameter von start())

   cEventSem sync_start;         //!< Wartesemaphore fuer Thread-Start
   cEventSem sync_end;           //!< Wartesemaphore fuer Thread-Beendigung

   #if defined __ECL_PTHREADS__
      pthread_t pt_id;
   #elif defined __ECL_OS2__
      // not needed
   #elif defined __ECL_W32__
      HANDLE hnd;
   #endif
};


cThread::cPrivate::cPrivate (int ss, AUTO_DEL ad, int ac, char **av)
{
   // *** STATECHANGE ***
   state = tsCreated;

   stacksize = ss;   // set to 0 to use default stack size. This value is
                     // valid for __ECL_W32__ and __ECL_PTHREADS__
   auto_del = ad;
   argc = ac; 
   argv = av;

   tid = -1; 
   rc = 0;
#ifdef __Use_Exception_Handler__
   guard_count = 0;
#endif
   init_data = 0;

   #if defined __ECL_PTHREADS__
      // Keine pthread_t initialisierung fuer pt_id
   #elif defined __ECL_W32__
      hnd = 0;
   #else
      #error initialization for this platform not explicit covered
      // Den folgenden "Defaultwert" habe ich aus dem alten Originalcode
      // uebernommen. Er war (vermutlich) fuer OS/2 gueltig, das nicht mehr
      // unterstuetzt wird.
      // if (ss == 0) stacksize = 16384;
   #endif

}

cThread::cPrivate::~cPrivate ()
{
}



/**
*  During onEnter() and onMain() this function returns 0. The value becomes
*  valid when onLeave() is called.
*/
int cThread::getRC() const
{
   return _private->rc; 
}

/**
*  This value is unique and valid while the thread is running. As soon as it
*  terminates another thread may be started with the same id.
*/
int cThread::getThreadId() const
{ 
   return _private->tid; 
}

cThread::STATE cThread::getState() const
{ 
   return _private->state; 
}

bool cThread::isRunning() const
{ 
   return _private->state != tsCreated && _private->state != tsTerminated; 
}





// ===========================================================================
// Platformabhaengige Hilfsfunktionen
// ===========================================================================

#if defined __ECL_PTHREADS__
   
// pthread_t in int umwandeln
static int pthread_id_to_int(pthread_t pid)
{
   #if defined __ECL_W32__
      // mit ptheads-win32 vom 2004-11-03 ist pthread_t selbst kein in
      // ein int umwandelbarer Zeiger mehr, sondern ein struct. Daher:
      const int pthread_t_is_pointer = (sizeof(pthread_t) == sizeof(void*));
      #if pthread_t_is_pointer
         return (int)pid;
      #else
         return (int)(pid.p);
      #endif
   #else
      return (int)pid;
   #endif
}


// Thread bis zu absoluter Endzeit warten lassen 
static void pthread_sleep( struct timespec *abstime )
{ 
   pthread_cond_t cond;
   pthread_cond_init(&cond, 0);
   pthread_mutex_t mutex;
   pthread_mutex_init(&mutex, 0);

   pthread_mutex_lock( &mutex );
   pthread_cond_timedwait( &cond, &mutex, abstime );
   pthread_mutex_unlock( &mutex );

   pthread_mutex_destroy( &mutex );
   pthread_cond_destroy( &cond );
}
 

// Relativzeit in absolute Endzeit jetzt+msec umrechnen
static struct timespec *pthread_ms_to_timespec(int msec, struct timespec *abstime)
{
   #if defined __ECL_W32__
      //MinGW / Windows
      struct _timeb current_time;
      _ftime( &current_time );

      abstime->tv_sec = current_time.time + msec / 1000;
      abstime->tv_nsec = (current_time.millitm + msec % 1000) * 1000000;
      if ( abstime->tv_nsec > 1000000000 ) {
         abstime->tv_nsec -= 1000000000;
         abstime->tv_sec++;
      }
   #else
      // GnuC / Linux
      struct timeval tval;
      gettimeofday( &tval, 0 );

      abstime->tv_nsec = ( tval.tv_usec + ( msec % 1000 ) * 1000 ) * 1000;
      abstime->tv_sec = tval.tv_sec + ( msec / 1000 ) + ( abstime->tv_nsec / 1000000000 );
      abstime->tv_nsec %= 1000000000;
   #endif
   
   return abstime;
}


#endif // defined __ECL_PTHREADS__




// ===========================================================================
// Implementierung cThread
// ===========================================================================

// TBD: fuer was waren die EYE_CATCHER mal gedacht? Werden jedenfalls nicht
// (mehr) benutzt und ich hab sie auskommentiert:
//
// #define EYE_CATCHER_STATIC    0x53544154  /*STAT*/
// #define EYE_CATCHER_DYNAMIC   0x44594e41  /*DYNA*/

cThread::cThread(AUTO_DEL auto_del) :
   _private(new0 cPrivate(0, auto_del, 0, 0))
{
   __ECL_STATISTIC__("cThread")
}

cThread::cThread(int stacksize, AUTO_DEL auto_del) :
   _private(new0 cPrivate(stacksize, auto_del, 0, 0))
{
   __ECL_STATISTIC__("cThread(stacksize)")
}


cThread::~cThread()
{
   if ( isRunning() ) {
      // *** STATECHANGE ***
      _private->state = tsWaitForEnd;
      waitFor(teEnd);
   }

   #if defined __ECL_W32__ && !defined __ECL_PTHREADS__
      if ( _private->hnd != 0 ) {
         CloseHandle(_private->hnd);
      }
   #endif

   delete _private;
}




// BaseThread
// ==========

void __ECL_THREADLNK__ BaseThread(void *data)
{
   cThread *thread = (cThread *)data;

   if ( thread != 0 ) {
      thread->onThreadInit();
      thread->onThreadRun();
      cThread::onThreadExit(thread);
   } else {
      __ECL_RELEASE_TEXT__(THREAD_ERROR, "cThread: Cannot start thread without thread object");
   }
}

#if defined __ECL_PTHREADS__
   void *__ECL_THREADLNK__ VoidPtrBaseThread(void *data)
   {
      BaseThread(data);
      return 0;
   }
#endif


// Allgemeines
// ===========

/**
* Starts the thread. @a extra is passed to onEnter() and onMain().
* @a wait_event is used for synchronisation of the calling thread with
* the new thread:
* - teNone: default is no synchronisation, start() returns immediately. The new thread is possibly not already running.
* - teStart: calling thread is blocked until onEnter() of the new thread is completed, it is ensured that the new thread is running.
* - teEnd: calling thread is blocked until onLeave() of the new thread is completed, the new thread may already be terminated.
*
* The function returns false if the new thread has not been started.
*/
bool cThread::start(void *extra, THREAD_EVENT wait_event)
{
   if ( isRunning() )
      return false;

   // *** STATECHANGE ***
   _private->state = tsStarted;

   _private->init_data = extra;
   _private->sync_start.reset();
   _private->sync_end.reset();

   if ( isMainThread() ) {
      BaseThread((void *)this);
      return true;
   }

   if ( !onStart() )
      return false;

   // Evtl. Warten auf Event
   // TBD: Pruefen, ob das warten bei auto_del-Threads nicht gefaehrlich ist. Der Thread koennte
   // das aktuelle cThread-Objekt (*this) zerstoeren, bevor diese Funktion hier beendet ist.
   switch ( wait_event ) {
      case teStart:  
         _private->sync_start.wait(); 
         return isRunning();
      case teEnd:    
         _private->sync_end.wait();  
         break;
      case teNone:
      default:
         break;
   }

   return true;
}

/**
* This is an overloaded member function, provided for convenience. It behaves
* essentially like the above function. 0 is passed for missing @a extra.
*/
bool cThread::start(THREAD_EVENT wait_event)
{
   return start(0, wait_event);
}


/**
* Used for thread synchronisation. Depending on @a wait_event:
* - teNone: ignored, function returns immediately.
* - teStart: calling thread is blocked until onEnter() is completed. This is as well the case if onMain() is currently running.
* - teEnd: calling thead is blocked until onLeave() is completed. This is as well the case it the thead is terminated.
*/
void cThread::waitFor(THREAD_EVENT wait_event)
{
   switch ( wait_event ) {
      case teStart:
         _private->sync_start.wait();
         break;
      case teEnd:
         _private->sync_end.wait();
         break;
      case teNone:
      default:
         break;
   }
}

// static member
int cThread::getCurrentThreadId()
{
   #if defined __ECL_PTHREADS__
      return  pthread_id_to_int(pthread_self());
   #elif defined __ECL_OS2__
      return -1; // ???
   #elif defined __ECL_W32__
      return GetCurrentThreadId();
   #endif
}

// static member
int cThread::getCurrentProcessId()
{
   #if defined __ECL_LINUX__
      return getpid();
   #elif defined __ECL_OS2__
      PPIB ppib = 0; DosGetInfoBlocks(0, &ppib);
      return ppib ? ppib->pib_ulpid : 0;
   #elif defined __ECL_W32__
      return (int)GetCurrentProcessId();
   #endif
}


// Main-Thread
// ===========

cThread * cThread::cPrivate::main_thread = 0;

/**
*  This constructor is used to associate the current thread with a cThread
*  object. start() does @b not launch a new thread and onEnter(), onMain()
*  and onLeave() are executed in the context of the calling thread of start().
*
*  Example: 
*  @code
*     class cMainThread : cThread
*     {
*        // ...
*     };
*
*     int main(int argc, char *argv[])
*     {
*        cMainThread mt(argc, argv);
*        mt.start();   // blocks until onEnter, onMain, and onLeave are completed.
*        return mt.getRC();
*     }
*  @endcode
*/
cThread::cThread(int argc, char **argv) :
   _private(new0 cPrivate(-1, tdNoAutoDel, argc, argv))
{
   __ECL_STATISTIC__("cThread(main)")

   __ECL_ASSERT_PRINTF__(!_private->main_thread, THREAD_ERROR, ("cThread: Multiple main threads"));

   // Main Thread in statischer Variablen merken
   _private->main_thread = this;

   // Thread-Id des Main-Thread ermitteln
   #if defined __ECL_PTHREADS__
      _private->tid =  pthread_id_to_int(pthread_self());
   #elif defined __ECL_OS2__
      _private->tid = 1;
   #elif defined __ECL_W32__
      _private->tid = GetCurrentThreadId();
   #endif
}


/**
*  Only valid for the main thread object. 0 is returned on any other thread.
*/
int cThread::getArgCount() const
{ 
   return _private->argc; 
}

/**
* Only valid for the main thread object. 0 is returned on any other thread
* or if @a arg exceeds the the argument count passed during construction.
*/ 
const char *cThread::getArgValue(int arg) const
{ 
   return (arg >= 0 && arg < _private->argc) ? _private->argv[arg] : 0; 
}

bool cThread::isMainThread() const
{
   #if defined __ECL_PTHREADS__
      if ( _private->main_thread == 0 )
         return false;
      return _private->main_thread->_private->tid == _private->tid;
   #elif defined __ECL_OS2__
      return _private->tid == 1;
   #elif defined __ECL_W32__
      if ( _private->main_thread == 0 )
         return false;
      return _private->main_thread->_private->tid == _private->tid;
   #else
      // ...
   #endif
}

/**
*  May be 0 if no main thread object has been defined.
*/
cThread * cThread::getMainThread()
{
   return cThread::cPrivate::main_thread;
}


// Phasen der Thread-Bearbeitung
// =============================

bool cThread::onEnter(void *) // bool onEnter(void *extra)
{
   return true;
}

int cThread::onMain(void *) // int onMain(void *extra)
{
   return 0;
}

void cThread::onLeave(int) // void onLeave(int rc)
{
}


// Prioritaet
// ==========

#if defined __ECL_OS2__
   static int PrioLevels[] = {
      -31, -20, -5, 0, 5, 20, 31
   };
   static int PrioClasses[] = {
      PRTYC_NOCHANGE,
      PRTYC_IDLETIME,
      PRTYC_REGULAR,
      PRTYC_TIMECRITICAL,
      PRTYC_FOREGROUNDSERVER
   };
#elif defined __ECL_W32__
   static int PrioLevels[] = {
      THREAD_PRIORITY_IDLE,
      THREAD_PRIORITY_LOWEST,
      THREAD_PRIORITY_BELOW_NORMAL,
      THREAD_PRIORITY_NORMAL,
      THREAD_PRIORITY_ABOVE_NORMAL,
      THREAD_PRIORITY_HIGHEST,
      THREAD_PRIORITY_TIME_CRITICAL
   };
   static int PrioClasses[] = {
      IDLE_PRIORITY_CLASS,
      NORMAL_PRIORITY_CLASS,
      HIGH_PRIORITY_CLASS,
      REALTIME_PRIORITY_CLASS
   };
#else
   // ...
#endif

cThread::LEVEL cThread::getPriority()
{
   #if defined __ECL_PTHREADS__
      __ECL_DEBUG_TEXT__(THREAD_ERROR, "cThread: getPriority() not implemented"); // TBD
      return plNormal;
   #elif defined __ECL_OS2__
      PTIB ptib = 0; DosGetInfoBlocks(&ptib, 0);
      int lvl = ptib ? ((ptib->tib_ptib2->tib2_ulpri) & 0x001F) : 0;
      for ( int i = 0 ; i < sizeof PrioLevels / sizeof PrioLevels[0] ; i++ ) {
         if ( lvl == PrioLevels[i] )
            return LEVEL(i+1);
      }
      return plNormal;
   #elif defined __ECL_W32__
      int lvl = GetThreadPriority(_private->hnd);
      for ( int i = 0 ; i < sizeof PrioLevels / sizeof PrioLevels[0] ; i++ ) {
         if ( lvl == PrioLevels[i] )
            return LEVEL(i+1);
      }
      return plNormal;
   #else
      // ...
   #endif
}

cThread::CLASS cThread::getPriorityClass()
{
   #if defined __ECL_PTHREADS__
      __ECL_DEBUG_TEXT__(THREAD_ERROR, "cThread: getPriorityClass() not implemented"); // TBD
      return pcRegular;
   #elif defined __ECL_OS2__
      PTIB ptib = 0; DosGetInfoBlocks(&ptib, 0);
      int cls = ptib ? ((ptib->tib_ptib2->tib2_ulpri) >> 8) & 0x00FF : 0;
      for ( int i = 0 ; i < sizeof PrioClasses / sizeof PrioClasses[0] ; i++ ) {
         if ( cls == PrioClasses[i] )
            return CLASS(i+1);
      }
      return pcRegular;
   #elif defined __ECL_W32__
      //int cls = GetPriorityClass(hnd);
      //for ( int i = 0 ; i < sizeof PrioClasses / sizeof PrioClasses[0] ; i++ ) {
      //   if ( cls == PrioClasses[i] )
      //      return CLASS(i+1);
      //}
      return pcRegular;
   #else
      // ...
   #endif
}

bool cThread::setPriority(LEVEL lvl, CLASS cls)
{
   if ( isRunning() ) {
      #if defined __ECL_PTHREADS__
         __ECL_DEBUG_TEXT__(THREAD_ERROR, "cThread: setPriority() not implemented"); // TBD
      #elif defined __ECL_OS2__
         if ( lvl == plNoChange )
            return true;
         return 0 == DosSetPriority(PRTYS_THREAD, PrioClasses[cls], PrioLevels[lvl-1], tid);
      #elif defined __ECL_W32__
         if ( cls != pcNoChange /*&& !SetPriorityClass(hnd, PrioClasses[cls-1])*/ ) {
            __ECL_RELEASE_TEXT__(THREAD_ERROR, "Win32: Could set priority class");
            //return false;
         }
         if ( lvl != plNoChange && !SetThreadPriority(_private->hnd, PrioLevels[lvl-1]) ) {
            __ECL_RELEASE_PRINTF__(THREAD_ERROR, ("Win32: Could set priority level, err = %lu", GetLastError()));
            return false;
         }
      #else
         // ...
      #endif
   }
   return false;
}


// Suspendierung
// =============

bool cThread::sleep(int ms)
{
   #if defined __ECL_PTHREADS__
      struct timespec timeout;
      pthread_sleep(pthread_ms_to_timespec(ms, &timeout));
      return true;
   #elif defined __ECL_OS2__
      return 0 == DosSleep(ms);
   #elif defined __ECL_W32__
      Sleep(ms);
      return true;
   #else
      // ...
   #endif
}


// Terminierung
// ============

bool cThread::kill(bool wait)
{
   if ( onKill() ) {
      if ( wait )
         waitFor();
      return true;
   }

   return false;
}


// Events
// ======

bool cThread::onStart()
{
   #if defined __ECL_PTHREADS__
      int err;

      // Thread Attribute initialisieren
      pthread_attr_t pat;
      err = pthread_attr_init(&pat);
      __ECL_ASSERT_PRINTF__(!err, THREAD_ERROR, ("cThread: pthread_attr_init failed, err = %d",err));
      err = pthread_attr_setdetachstate(&pat, PTHREAD_CREATE_DETACHED);
      __ECL_ASSERT_PRINTF__(!err, THREAD_ERROR, ("cThread: pthread_attr_setdetachstate failed, err = %d",err));
      if (_private->stacksize > 0) {
         err = pthread_attr_setstacksize(&pat, _private->stacksize);
         __ECL_ASSERT_PRINTF__(!err, THREAD_ERROR, ("cThread: pthread_attr_setstacksize failed, err = %d",err));
      }

      // Thread erzeugen
      err = pthread_create(&_private->pt_id, &pat, VoidPtrBaseThread, (void *)this);
      __ECL_ASSERT_PRINTF__(!err, THREAD_ERROR, ("cThread: pthread_create failed, err = %d",err));

      // Attribute aufraeumen
      err = pthread_attr_destroy(&pat);
      __ECL_ASSERT_PRINTF__(!err, THREAD_ERROR, ("cThread: pthread_attr_destroy failed, err = %d",err));
      
      return err == 0;
   #elif defined __ECL_OS2__
      int rc;
      rc = tid = _beginthread(BaseThread, 0, _private->stacksize, (void *)this);
      return rc != -1;
   #elif defined __ECL_W32__
      int rc = _beginthread(BaseThread, _private->stacksize, (void *)this);
      return rc != -1;
   #else
      // ...
   #endif
}

bool cThread::onKill()
{
   #if defined __ECL_PTHREADS__
      // TBD
      __ECL_DEBUG_TEXT__(THREAD_ERROR, "cThread: onKill() not implemented"); // TBD
      return false;
   #elif defined __ECL_OS2__
      APIRET rc;
      if ( 0 != (rc = DosKillThread(tid)) ) {
         cBase::DbgError("OS/2: Could not kill thread %d, rc=%lu", tid, rc);
         return false;
      } else {
         return true;
      }
   #elif defined __ECL_W32__
      if ( !TerminateThread(_private->hnd, 0) ) {
         __ECL_RELEASE_PRINTF__(THREAD_ERROR, ("Win32: Could not kill thread %d, err=%lu", _private->tid, GetLastError()));
         return false;
      } else {
         return true;
      }
   #else
      // ...
   #endif
}

void cThread::onThreadInit()
{
   #if defined __ECL_PTHREADS__
      _private->tid = pthread_id_to_int(pthread_self());
      // Plausibilitaetskontrolle: die bei pthread_create() zurueckgegebene
      // Thread-id muss der aktuellen Thread-Id von pthread_self() entsprechen.
      //__ECL_ASSERT_PRINTF__( pthread_equal(pthread_self(), _private->pt_id), THREAD_ERROR, ("different id's from pthread_create()=%d and pthread_self()=%d",pthread_id_to_int(_private->pt_id), _private->tid));
   #elif defined __ECL_W32__
      _private->tid = GetCurrentThreadId();
      DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
         GetCurrentProcess(), &_private->hnd, 0, FALSE, DUPLICATE_SAME_ACCESS );
   #endif
}

int cThread::onThreadRun()
{
   bool init_successful = false;

#ifdef __Use_Exception_Handler__
   bool async_terminate = false;
   // onException-Schutz aktivieren (gueltig bis Ende von BaseThread)
   cExceptionHandler x(this);
#endif
   
   // *** STATECHANGE ***
   _private->state = tsRunning;
   
   try {
      _private->rc = 0;
      if ( onEnter(_private->init_data) ) {
         // Signalisiere Thread-Start
         _private->sync_start.set();
         init_successful = true;
         
         _private->rc = onMain(_private->init_data);
         onLeave(_private->rc);
         
         if ( _private->rc != 0 ) {
            __ECL_RELEASE_PRINTF__(THREAD_INFO,("Thread 0x%x: returned with code %d (0x%x)",_private->tid,_private->rc,_private->rc));
            //std::cerr << "BaseThread: Thread " << _private->tid
            //     << " returned with rc=" << _private->rc << std::endl;
         }
#ifdef __Use_Exception_Handler__
         if ( _private->guard_count ) {
            __ECL_RELEASE_PRINTF__(THREAD_INFO,("Thread 0x%x: raised %d guard page violation(s)",_private->tid,_private->guard_count));
            //std::cerr << "BaseThread: Thread " << _private->tid
            //     << " raised " << _private->guard_count << " guard page violation(s)" << std::endl;
         }
#endif
      }
   } catch ( const cErrBase& err ) {
      char errbuf[1024];
      __ECL_RELEASE_PRINTF__(THREAD_ERROR,("Thread 0x%x: catched unhandled ecl exception: %s",getThreadId(),err.getString(errbuf, sizeof(errbuf))));
      _private->rc = -1;
#ifdef __Use_Exception_Handler__
      async_terminate = true;
#endif
      #if __ECL_DEBUG__ > 0
         // Exception im Debug-Build weiterwerfen, im Visual Studio Debugger kann
         // so über den Kontext / Call-Stack die Fehlerposition gefunden werden!
         throw;
      #endif
   } catch ( const std::exception &e ) {
      __ECL_RELEASE_PRINTF__(THREAD_ERROR,("Thread 0x%x: catched unhandled std exception: %s",getThreadId(),e.what()));
      _private->rc = -1;
#ifdef __Use_Exception_Handler__
      async_terminate = true;
#endif
      #if __ECL_DEBUG__ > 0
         // Exception im Debug-Build weiterwerfen, im Visual Studio Debugger kann
         // so über den Kontext / Call-Stack die Fehlerposition gefunden werden!
         throw;
      #endif
   } catch ( ... ) {
      __ECL_RELEASE_PRINTF__(THREAD_ERROR,("Thread 0x%x: catched unhandled exception",getThreadId()));
      _private->rc = -1;
#ifdef __Use_Exception_Handler__
      async_terminate = true;
#endif
      #if __ECL_DEBUG__ > 0
         // Exception im Debug-Build weiterwerfen, im Visual Studio Debugger kann
         // so über den Kontext / Call-Stack die Fehlerposition gefunden werden!
         throw;
      #endif
   }
   
#if defined __Use_Exception_Handler__
   if ( async_terminate )
      x.raiseAsyncTerminate();
#endif
   
   // *** STATECHANGE ***
   _private->state = tsTerminated;
   
   if ( !init_successful )
      _private->sync_start.set();
   
   return _private->rc;
}

void cThread::onThreadExit(cThread *thread)
{
   // 04.04.2001 -TE- tdAutoDel-Wunsch merken, da cThread-Objekt im tdNoAutoDel-
   // Fall nach der Rueckkehr von sync_end.set() womoeglich schon nicht mehr
   // existent sein kann... (-> Zugriff auf ungueltigen Speicherbereich!)
   bool auto_del = thread->_private->auto_del == cThread::tdAutoDel;

   // Signalisiere Thread-Ende
   thread->_private->sync_end.set();
   
   // Selbstzerstoerung
   if ( auto_del )
      delete thread;
}


// onException-Behandlung

#ifdef __Use_Exception_Handler__
bool cThread::onException(cException * exception)
{
   // Stack-Verfehlungen abpruefen,
   // Ausgaben waeren hierbei toedlich
   switch ( exception->getId() ) {
      case cException::xGuardPageViolation:
         _private->guard_count++;
         // weiter im Text
      case cException::xUnableToGrowStack:
         return false;
   }

   cBase::DbgInfo(">>> Thread %d received exception %d", tid, exception->getId());

   switch ( exception->getId() ) {
      case cException::xAsyncProcessTerminate:
         cBase::DbgInfo("Thread %d killed", _private->tid);
         onLeave(RC_KILL);
         break;
      case cException::xProcessTerminate:
         // DbgInfo("Process terminates");
         // Hier ist alles zu spaet
         break;
   }
   return false;
}
#else
bool cThread::onException(cException *)
{
   return false;
}
#endif






}; // namespace ecl

