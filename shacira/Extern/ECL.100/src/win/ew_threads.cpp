// ===========================================================================
// ew_threads.cpp                                ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cThread
//        |
//        +-cwThread
//
// ===========================================================================

#include "win/ew_threads.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_thread.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cwThread
// ---------------------------------------------------------------------------
//
// cBase
//  +--cThread
//      +--cwThread
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwThread : public cThread {
   friend unsigned int WinThread(void *);

public:

   // Konstruiere normalen (secondary) Thread
   cwThread(AUTO_DEL auto_del = tdNoAutoDel) : cThread(auto_del) { init(); }
   // Konstruiere normalen (secondary) Thread mit Angabe der Stack-Groese
   cwThread(int stacksize, AUTO_DEL auto_del = tdNoAutoDel) : cThread(stacksize, auto_del) { init(); }
   // Konstruiere Main-Thread
   cwThread(int argc, char **argv) : cThread(argc, argv) { init(); }
   // Destruktor
   virtual ~cwThread();


protected:

   // Events
   // ======

   // Wird aufgerufen, um die Methode 'start' zu realisieren
   bool onStart(void *extra, int stacksize);


private:

   // Initialisierung der cwThread-Klasse
   void init();
   // Starten der eigentlichen Thread-Funktion
   static int run(cwThread *thread);
   // Zeiger auf systemspezifisches Thread-Objekt
   void *_thread;

};

#endif /*__INTERFACE__*/


// Implementierung cwThread
// ===========================================================================

void cwThread::init()
{
   _thread = 0;
}

cwThread::~cwThread()
{
}


// WinThread
// =========

unsigned int WinThread(void *data)
{
   cwThread *thread = (cwThread *)data;

   if ( thread != 0 ) {
      return cwThread::run(thread);
   } else {
      cBase::DbgError("BaseThread: Cannot start thread without thread object");
   }

   return 1000;
}

int cwThread::run(cwThread *thread)
{
   thread->onThreadInit();
   int rc = thread->onThreadRun();
   cThread::onThreadExit(thread);
   return rc;
}


// Events
// ======

bool cwThread::onStart(void * /*extra*/, int stacksize)
{
   #if defined __ECL_W32__
      _thread = AfxBeginThread(WinThread, (LPVOID)this, THREAD_PRIORITY_NORMAL, stacksize, 0, NULL);
      return _thread != 0;
   #else
      return cThread::onStart(extra, stacksize);
   #endif
}

