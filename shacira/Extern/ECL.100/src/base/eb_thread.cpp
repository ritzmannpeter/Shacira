// ===========================================================================
// eb_thread.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cThread          -
//
// ===========================================================================

#include "base/eb_thread.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #define INCL_DOSPROCESS       /* DosSetPriority */
   #include <os2.h>
#elif defined __ECL_W32__
   #include <process.h>
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_err.hpp"
#include "base/eb_except.hpp"
#include "base/eb_sema.hpp"
#include "base/eb_store.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cThread
// ---------------------------------------------------------------------------
//
// Jedes Thread-Objekt durchlaeuft folgende Zustaende in dieser Reihenfolge:
//
//    tsCreated      - Thread-Objekt angelegt, Thread noch nicht gestartet
//
//    tsStarted      - Thread gestartet, laeuft noch nicht
//
//    tsRunning      - Thread laeuft (onEnter, onMain, onLeave)
//
// und landet schließlich bei einem der folgenden Zustaende:
//
//    tsTerminated   - Thread normal zu Ende gelaufen
//                     Kann bei Bedarf nochmal gestartet werden
//
//    tsWaitForEnd   - Thread-Objekt geloescht, bevor Thread zu Ende gelaufen
//                     Destruktor wird bis zum Thread-Ende verzoegert
//
// Beispiele:
//
//    static cThread t; // Statisches Thread-Objekt
//    void f1()
//    {
//       t.start(); // Thread starten
//       ...
//       // Thread laeuft irgendwann zu Ende (tsTerminated), t lebt noch.
//       ...
//       t.waitFor(); // Sicheres Warten auf Thread-Ende
//       ...
//       t.start(cThread::teEnd); // Thread nochmal starten (mit Blocking)
//    }
//
//    void f2()
//    {
//       cThread t; // Automatisches Thread-Objekt
//       t.start();
//       ...
//       // f2() wird blockiert, bis Thread terminiert (tsWaitForEnd)
//       // ACHTUNG: Virtuelle Funktionen werden nicht mehr aufgerufen!!!
//    }
//
//    void f3()
//    {
//       cThread t; // Automatisches Thread-Objekt
//       t.start(cThread::teEnd); // Besser: Warten auf Thread-Ende
//    }
//
//    void f4()
//    {
//       cThread *t = new cThread(cThread::tdAutoDel);
//       t->start();
//       // Tatsaechliches delete von t erst nach Thread-Ende
//    }
//
// Der Zustand tsWaitForEnd fuehrt unweigerlich zur Loeschung des Thread-
// Objektes.
//
// cBase
//  +--cThread
//
// ===========================================================================

class __ECL_DLLEXPORT__ cThread : public cBase {
   friend void __ECL_THREADLNK__ BaseThread(void *);
   friend class cwThread;

public:

   // Konstruktoren
   // =============

   enum AUTO_DEL {   // Auto-Delete
      tdAutoDel,     //  - Auto-Delete aktiv (nur bei dynamischen Objekten!!!)
      tdNoAutoDel    //  - Auto-Delete nicht aktiv
   };

   // Konstruiere normalen (secondary) Thread
   cThread(AUTO_DEL _auto_del = tdNoAutoDel);
   // Konstruiere normalen (secondary) Thread mit Angabe der Stack-Groese
   cThread(int _stacksize, AUTO_DEL _auto_del = tdNoAutoDel);
   // Konstruiere Main-Thread
   cThread(int _argc, char **_argv);
   // Destruktor
   virtual ~cThread();


   // Allgemeines
   // ===========

   enum EVENT {      // Moegliche Thread-Events:
      teNone,        //  - Kein Event (d.h. nicht warten)
      teStart,       //  - Thread gestartet, onEnter durchlaufen, naechster Aufruf onMain
      teEnd          //  - Thread ist beendet, letzter Aufruf war onLeave
   };

   // Thread starten mit Parameteruebergabe
   bool start(void *extra, EVENT wait_event = teNone);
   // Thread starten ohne Parameteruebergabe
   bool start(EVENT wait_event = teNone);

   // Auf Event warten
   void waitFor(EVENT event = teEnd);

   // Liefert den Returncode von onMain
   int getRC() const
      { return rc; }
   // Liefert die ID des Threads
   inline int getThreadId() const
      { return tid; }

   // Liefert die ID des aktuellen Threads
   static int getCurrentThreadId();
   // Liefert die ID des aktuellen Prozesses
   static int getCurrentProcessId();


   // Aktueller Zustand
   // =================

   enum STATE {      // Zustaende des Thread-Objektes:
      tsCreated,     //  - Thread-Objekt angelegt, Thread noch nicht gestartet
      tsStarted,     //  - Thread gestartet, laeuft noch nicht
      tsRunning,     //  - Thread laeuft (onEnter, onMain, onLeave)
      tsTerminated,  //  - Thread normal zu Ende gelaufen
      tsWaitForEnd   //  - Destruktor verzoegert bis zum Thread-Ende
   };

   // Aktuellen Zustand erfragen
   STATE getState() const
      { return state; }
   // Ist der Thread am Laufen?
   bool isRunning() const
      { return state != tsCreated && state != tsTerminated; }


   // Main-Thread
   // ===========

   // Ist dieser Thread der Haupt-Thread des Prozesses?
   bool isMainThread() const;
   // Zeiger auf Main-Thread des Prozesses liefern
   static cThread *getMainThread();
   // Anzahl Kommandozeilenargumente
   int getArgCount() const
      { return argc; }
   // Zeiger auf Kommoandozeilenargument
   const char *getArgValue(int arg) const
      { return arg < argc ? argv[arg] : NULL; }


   // Phasen der Thread-Bearbeitung
   // =============================
   // Die folgenden Methoden werden _ausschliesslich_ von der Basisklasse aufge-
   // rufen, um bestimmte Phasen der Thread-Bearbeitung durchzufuehren.

   enum { RC_KILL = 99 };    // Wird an onLeave() bei Abschuss des Threads uebergeben

   // Bei diesem Event kann sich der Thread initialisieren
   virtual bool onEnter(void *extra);
   // onMain-Funktion des Threads
   virtual int onMain(void *extra);
   // Bei diesem Event kann sich der Thread deinitialisieren
   virtual void onLeave(int rc);


   // Exceptions
   // ==========
   // Liefert onException false, wird die Exception-Behandlung mit dem naechsten
   // Handler fortgesetzt. Bei true werden keine weiteren Handler mehr aufgerufen

   // Wird bei auftretender Exception aufgerufen
   virtual bool onException(cException *exception);


   // Prioritaet
   // ==========

   enum CLASS { pcNoChange, pcIdle, pcRegular, pcCritical, pcServer };
   enum LEVEL { plNoChange, plIdle, plLow, plBelowNormal, plNormal, plAboveNormal, plHigh, plTimeCritical };

   // Liefert die Prioritaetsstufe innerhalb der -Klasse
   LEVEL getPriority();
   // Liefert die Prioritaetsklasse
   CLASS getPriorityClass();
   // Setzt Prioritaetsstufe und Klasse
   bool setPriority(LEVEL lvl, CLASS cls = pcNoChange);


   // Suspendierung
   // =============

   // Aktuellen Thread fuer bestimmte Zeit suspendieren
   static bool sleep(int ms);
   // Thread (gewaltsam) beenden
   bool kill(bool wait = false);


protected:

   // Events
   // ======

   // Wird aufgerufen, um die Methode 'start' zu realisieren
   virtual bool onStart(void *extra, int stacksize);
   // Wird aufgerufen, um die Methode 'kill' zu realisieren
   virtual bool onKill();

   // Wird aufgerufen, um die Thread-Initialisierung zu realisieren
   virtual void onThreadInit();
   // Wird aufgerufen, um die eigentliche Thread-Funktion zu realisieren
   virtual int onThreadRun();
   // Wird aufgerufen, um den Thread zu beenden
   static void onThreadExit(cThread *thread);


private:

   static cThread *main_thread;
   int argc;                     // Anzahl Kommandozeilen-Argumente (Main-Thread)
   char **argv;                  // Zeiger auf Argument-Vektor (Main-Thread)

   int tid;                      // Thread-ID dieses Threads
   STATE state;                  // Aktueller Zustand des Threads
   AUTO_DEL auto_del;            // Automatisches delete bei Thread-Ende?
   int guard_count;              // Zaehlt Anzahl der 'Guard Page Violations'
   int rc;                       // Returncode von onMain

   int stacksize;                // Stackgroesse
   void *init_data;              // Initialisierungsdaten (Parameter von start())

   cEventSem sync_start;         // Wartesemaphore fuer Thread-Start
   cEventSem sync_end;           // Wartesemaphore fuer Thread-Beendigung

   #if defined __ECL_OS2__
      // not needed
   #elif defined __ECL_W32__
      void *hnd;
   #endif

};

#endif /*__INTERFACE__*/


// Implementierung cThread
// ===========================================================================

#define EYE_CATCHER_STATIC    0x53544154  /*STAT*/
#define EYE_CATCHER_DYNAMIC   0x44594e41  /*DYNA*/

cThread::cThread(AUTO_DEL _auto_del)
{
   // *** STATECHANGE ***
   state = tsCreated;

   auto_del = _auto_del;
   tid = -1; rc = 0;
   argc = 0; argv = NULL;
   guard_count = 0;

   #if defined __ECL_W32__
      hnd = 0;
      stacksize = 0; // Win32: use default value for stack size
   #else
      stacksize = 16384;
   #endif
}

cThread::cThread(int _stacksize, AUTO_DEL _auto_del)
{
   // *** STATECHANGE ***
   state = tsCreated;

   auto_del = _auto_del;
   stacksize = _stacksize;
   tid = -1; rc = 0;
   argc = 0; argv = NULL;
   guard_count = 0;

   #if defined __ECL_W32__
      hnd = 0;
   #endif
}

cThread::cThread(int _argc, char **_argv)
{
   // *** STATECHANGE ***
   state = tsCreated;

   auto_del = tdNoAutoDel;
   stacksize = -1; rc = 0;
   argc = _argc; argv = _argv;
   guard_count = 0;
   main_thread = this;

   #if defined __ECL_OS2__
      tid = 1;
   #elif defined __ECL_W32__
      tid = GetCurrentThreadId();
   #endif

   #if defined __ECL_W32__
      hnd = 0;
   #endif
}

cThread::~cThread()
{
   if ( isRunning() ) {
      // *** STATECHANGE ***
      state = tsWaitForEnd;
      waitFor(teEnd);
   }

   #if defined __ECL_W32__
      if ( hnd != NULL ) {
         CloseHandle((HANDLE)hnd);
         hnd = NULL;
      }
   #endif
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
      cBase::DbgError("BaseThread: Cannot start thread without thread object");
   }

/*
   cThread *thread = (cThread *)data;
   bool async_terminate = false;
   bool init_successful = false;

   if ( !thread ) {
      cerr << "BaseThread: Cannot start thread without thread object" << endl;
      return;
   }

   #define __Use_Exception_Handler__
   #if defined __Use_Exception_Handler__
      // onException-Schutz aktivieren (gueltig bis Ende von BaseThread)
      cExceptionHandler x(thread);
   #endif

   #if defined __ECL_W32__
      thread->tid = GetCurrentThreadId();
      DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
         GetCurrentProcess(), &thread->hnd, 0, FALSE, DUPLICATE_SAME_ACCESS );
   #endif

   // *** STATECHANGE ***
   thread->state = cThread::tsRunning;

   try {
      if ( thread->onEnter(thread->init_data) ) {
         // Signalisiere Thread-Start
         thread->sync_start.set();
         init_successful = true;

         int rc = thread->rc = thread->onMain(thread->init_data);
         thread->onLeave(rc);

         if ( rc != 0 )
            cerr << "BaseThread: Thread " << thread->tid
                 << " returned with rc=" << rc << endl;
         if ( thread->guard_count )
            cerr << "BaseThread: Thread " << thread->tid
                 << " raised " << thread->guard_count << " guard page violation(s)" << endl;
      }
   } catch ( const cErrBase& err ) {
      cerr << "Thread " << thread->getThreadId() << ": catched unhandled exception: " << err << endl;
      async_terminate = true;
      #if __ECL_DEBUG__ > 0
         cerr << " ... throwing exception cause __ECL_DEBUG__ > 0" << endl;
         throw;
      #endif
   } catch ( ... ) {
      cerr << "Thread " << thread->getThreadId() << ": catched unhandled system exception" << endl;
      async_terminate = true;
      #if __ECL_DEBUG__ > 0
         cerr << " ... throwing exception cause __ECL_DEBUG__ > 0" << endl;
         throw;
      #endif
   }

   #if defined __Use_Exception_Handler__
      if ( async_terminate )
         x.raiseAsyncTerminate();
   #endif

   // *** STATECHANGE ***
   thread->state = cThread::tsTerminated;

   if ( !init_successful )
      thread->sync_start.set();

   // 04.04.2001 -TE- tdAutoDel-Wunsch merken, da cThread-Objekt im tdNoAutoDel-
   // Fall nach der Rueckkehr von sync_end.set() womoeglich schon nicht mehr
   // existent sein kann... (-> Zugriff auf ungueltigen Speicherbereich!)
   bool auto_del = thread->auto_del == cThread::tdAutoDel;

   // Signalisiere Thread-Ende
   thread->sync_end.set();

   // Selbstzerstoerung
   if ( auto_del )
      delete thread;
*/
}


// Allgemeines
// ===========

bool cThread::start(void *extra, EVENT wait_event)
{
   if ( isRunning() )
      return false;

   // *** STATECHANGE ***
   state = tsStarted;

   init_data = extra;
   sync_start.reset();
   sync_end.reset();

   if ( isMainThread() ) {
      BaseThread((void *)this);
      return true;
   }

   if ( !onStart(extra, stacksize) )
      return false;

   // Evtl. Warten auf Event
   switch ( wait_event ) {
      case teStart:  sync_start.wait(); return isRunning();
      case teEnd:    sync_end.wait();   break;
   }

   return true;
}

bool cThread::start(EVENT wait_event)
{
   return start(NULL, wait_event);
}

void cThread::waitFor(EVENT event)
{
   switch ( event ) {
      case teStart:
         sync_start.wait();
         break;
      case teEnd:
         sync_end.wait();
         break;
      default:
         break;
   }
}

int cThread::getCurrentThreadId()
{
   #if defined __ECL_OS2__
      return -1; // ???
   #elif defined __ECL_W32__
      return GetCurrentThreadId();
   #endif
}

int cThread::getCurrentProcessId()
{
   #if defined __ECL_OS2__
      PPIB ppib = NULL; DosGetInfoBlocks(NULL, &ppib);
      return ppib ? ppib->pib_ulpid : 0;
   #elif defined __ECL_W32__
      return (int)GetCurrentProcessId();
   #endif
}


// Main-Thread
// ===========

cThread * cThread::main_thread = NULL;

bool cThread::isMainThread() const
{
   #if defined __ECL_OS2__
      return tid == 1;
   #elif defined __ECL_W32__
      if ( main_thread == NULL )
         return false;
      return main_thread->tid == tid;
   #else
      // ...
   #endif
}

cThread * cThread::getMainThread()
{
   return main_thread;
}


// Phasen der Thread-Bearbeitung
// =============================

bool cThread::onEnter(void * /*extra*/)
{
   return true;
}

int cThread::onMain(void * /*extra*/)
{
   return 0;
}

void cThread::onLeave(int /*rc*/)
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
   #if defined __ECL_OS2__
      PTIB ptib = NULL; DosGetInfoBlocks(&ptib, NULL);
      int lvl = ptib ? ((ptib->tib_ptib2->tib2_ulpri) & 0x001F) : 0;
      for ( int i = 0 ; i < sizeof PrioLevels / sizeof PrioLevels[0] ; i++ ) {
         if ( lvl == PrioLevels[i] )
            return LEVEL(i+1);
      }
      return plNormal;
   #elif defined __ECL_W32__
      int lvl = GetThreadPriority(hnd);
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
   #if defined __ECL_OS2__
      PTIB ptib = NULL; DosGetInfoBlocks(&ptib, NULL);
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
      #if defined __ECL_OS2__
         if ( lvl == plNoChange )
            return true;
         return 0 == DosSetPriority(PRTYS_THREAD, PrioClasses[cls], PrioLevels[lvl-1], tid);
      #elif defined __ECL_W32__
         if ( cls != pcNoChange /*&& !SetPriorityClass(hnd, PrioClasses[cls-1])*/ ) {
            DbgError("Win32: Could set priority class");
            //return false;
         }
         if ( lvl != plNoChange && !SetThreadPriority(hnd, PrioLevels[lvl-1]) ) {
            DbgError("Win32: Could set priority level, err = %lu", GetLastError());
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
   #if defined __ECL_OS2__
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

bool cThread::onStart(void * /*extra*/, int stacksize)
{
   int rc = -1;

   #if defined __ECL_OS2__
      rc = tid = _beginthread(BaseThread, NULL, stacksize, (void *)this);
   #elif defined __ECL_W32__
      rc = _beginthread(BaseThread, stacksize, (void *)this);
   #else
      // ...
   #endif

   return rc != -1;
}

bool cThread::onKill()
{
   #if defined __ECL_OS2__
      APIRET rc;
      if ( 0 != (rc = DosKillThread(tid)) ) {
         DbgError("OS/2: Could not kill thread %d, rc=%lu", tid, rc);
         return false;
      }
   #elif defined __ECL_W32__
      if ( !TerminateThread(hnd, 0) ) {
         DbgError("Win32: Could not kill thread %d, err=%lu", tid, GetLastError());
         return false;
      }
   #else
      return false;
   #endif

   return true;
}

void cThread::onThreadInit()
{
   #if defined __ECL_W32__
      tid = GetCurrentThreadId();
      DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
         GetCurrentProcess(), &hnd, 0, FALSE, DUPLICATE_SAME_ACCESS );
   #endif
}

int cThread::onThreadRun()
{
   bool async_terminate = false;
   bool init_successful = false;

   #define __Use_Exception_Handler__
   #if defined __Use_Exception_Handler__
      // onException-Schutz aktivieren (gueltig bis Ende von BaseThread)
      cExceptionHandler x(this);
   #endif

   // *** STATECHANGE ***
   state = tsRunning;

   try {
      if ( onEnter(init_data) ) {
         // Signalisiere Thread-Start
         sync_start.set();
         init_successful = true;

         rc = onMain(init_data);
         onLeave(rc);

         if ( rc != 0 )
            cerr << "BaseThread: Thread " << tid
                 << " returned with rc=" << rc << endl;
         if ( guard_count )
            cerr << "BaseThread: Thread " << tid
                 << " raised " << guard_count << " guard page violation(s)" << endl;
      }
   } catch ( const cErrBase& err ) {
      cerr << "Thread " << getThreadId() << ": catched unhandled exception: " << err << endl;
      async_terminate = true;
      #if __ECL_DEBUG__ > 0
         cerr << " ... throwing exception cause __ECL_DEBUG__ > 0" << endl;
         throw;
      #endif
   } catch ( ... ) {
      cerr << "Thread " << getThreadId() << ": catched unhandled system exception" << endl;
      async_terminate = true;
      #if __ECL_DEBUG__ > 0
         cerr << " ... throwing exception cause __ECL_DEBUG__ > 0" << endl;
         throw;
      #endif
   }

   #if defined __Use_Exception_Handler__
      if ( async_terminate )
         x.raiseAsyncTerminate();
   #endif

   // *** STATECHANGE ***
   state = tsTerminated;

   if ( !init_successful )
      sync_start.set();

   return rc;
}

void cThread::onThreadExit(cThread *thread)
{
   // 04.04.2001 -TE- tdAutoDel-Wunsch merken, da cThread-Objekt im tdNoAutoDel-
   // Fall nach der Rueckkehr von sync_end.set() womoeglich schon nicht mehr
   // existent sein kann... (-> Zugriff auf ungueltigen Speicherbereich!)
   bool auto_del = thread->auto_del == cThread::tdAutoDel;

   // Signalisiere Thread-Ende
   thread->sync_end.set();

   // Selbstzerstoerung
   if ( auto_del )
      delete thread;
}


// onException-Behandlung

bool cThread::onException(cException *exception)
{
   // Stack-Verfehlungen abpruefen,
   // Ausgaben waeren hierbei toedlich
   switch ( exception->getId() ) {
      case cException::xGuardPageViolation:
         guard_count++;
         // weiter im Text
      case cException::xUnableToGrowStack:
         return false;
   }

   DbgInfo(">>> Thread %d received exception %d", tid, exception->getId());

   switch ( exception->getId() ) {
      case cException::xAsyncProcessTerminate:
         DbgInfo("Thread %d killed", tid);
         onLeave(RC_KILL);
         break;
      case cException::xProcessTerminate:
         // DbgInfo("Process terminates");
         // Hier ist alles zu spaet
         break;
   }

   return false;
}




#ifdef __Test_eb_thread__

   #include <stdio.h>

   class cWaiterThread : public cThread {
   public:
      cWaiterThread() : cThread() { }

      bool onEnter(void *extra)
      {
         cerr << "Waiter thread running with TID " << getThreadId() << endl;
         return cThread::onEnter(extra);
      }

      int onMain(void *extra)
      {
         getchar();
         char *p0 = 0; *p0 = 0;
         //getMainThread()->kill();
         return 0;
      }

      void onLeave(int rc)
      {
         cerr << "Waiter thread leaving with rc = " << rc << endl;
         cThread::onLeave(rc);
      }

   };

   class cTertiaryThread : public cThread {
   public:
      cTertiaryThread() : cThread() { }

      bool onEnter(void *extra)
      {
         cerr << "Secondary thread running with TID " << getThreadId() << endl;
         return cThread::onEnter(extra);
      }

      int onMain(void *extra)
      {
         cerr << "Tertiary thread running" << endl;
         while ( 1 ) {
            sleep(100);
            cerr << ".";
         }
         return 0;
      }

      void onLeave(int rc)
      {
         cerr << "Secondary thread leaving with rc = " << rc << endl;
         cThread::onLeave(rc);
      }

   };

   class cSecondaryThread : public cThread {
      char name[50];

   public:
      cSecondaryThread(const char *_name, AUTO_DEL auto_del = tdNoAutoDel) : cThread(auto_del)
      {
         strcpy(name, _name);
         cerr << "Secondary thread " << name << " created" << endl;
      }

      ~cSecondaryThread()
      {
         cerr << "Secondary thread " << name << " deleted" << endl;
      }

      bool onEnter(void *extra)
      {
         cerr << "Secondary thread " << name << " running with TID " << getThreadId() << endl;
         return cThread::onEnter(extra);
      }

      int onMain(void *extra)
      {
         getchar();
         /*cTertiaryThread third_thread;
         third_thread.start();

         cWaiterThread waiter_thread;
         waiter_thread.start();

         cerr << "Secondary thread running" << endl;
         while ( 1 ) {
            sleep(500);
            cerr << " -plick- ";
         }*/
         return 0;
      }

      void onLeave(int rc)
      {
         cerr << "Secondary thread " << name << " leaving with rc = " << rc << endl;
         cThread::onLeave(rc);
      }

   };

   class cMainThread : public cThread {

   public:
      cMainThread(int argc, char *argv[]) : cThread(argc, argv) { }

      bool onEnter(void *extra)
      {
         cerr << "Main thread running with TID " << getThreadId() << endl;
         return cThread::onEnter(extra);
      }

      int onMain(void *extra)
      {
         cSecondaryThread *t1 = new0 cSecondaryThread("t1", cThread::tdAutoDel);
         t1->start();

         cSecondaryThread t2("t2");
         t2.start(cThread::teEnd);

         cSecondaryThread *t3 = new0 cSecondaryThread("t3");
         t3->start(cThread::teEnd);
         delete t3;

         return 0;
      }

      void onLeave(int rc)
      {
         cerr << "Main thread leaving with rc = " << rc << endl;
         cThread::onLeave(rc);
      }

   };

   int main(int argc, char *argv[])
   {
      cMainThread app(argc, argv);
      app.start();
      return app.getRC();
   }

#endif

