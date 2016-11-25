// ===========================================================================
// base/thread.h                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//! @file  base/thread.h
//! @brief Thread class
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cThread
//
// ===========================================================================

#ifndef __ecl_thread__
#define __ecl_thread__


// Base class header
#include "base/base.h"

// Other ECL headers
#include "base/error.h"
#include "base/semaphore.h"


// Forward declarations
class cException;


namespace ecl {


// ===========================================================================
// cThread
// ---------------------------------------------------------------------------
//
//! @class cThread thread.h "base/thread.h"
//! @brief Base class for thread implementation
//!
//! @ingroup system
//!
//! Jedes Thread-Objekt durchlaeuft folgende Zustaende in dieser Reihenfolge:
//!
//!   - \b tsCreated:    Thread-Objekt angelegt, Thread noch nicht gestartet
//!
//!   - \b tsStarted:    Thread gestartet, laeuft noch nicht
//!
//!   - \b tsRunning:    Thread laeuft (onEnter, onMain, onLeave)
//!
//! und landet schliesslich bei einem der folgenden Zustaende:
//!
//!   - \b tsTerminated: Thread normal zu Ende gelaufen
//!                      Kann bei Bedarf nochmal gestartet werden
//!
//!   - \b tsWaitForEnd: Thread-Objekt geloescht, bevor Thread zu Ende gelaufen
//!                      Destruktor wird bis zum Thread-Ende verzoegert. Der
//!                      Zustand tsWaitForEnd fuehrt unweigerlich zur Loeschung
//!                      des Thread-Objektes.
//!
//! Beispiele:
//!
//!  @code
//!    static cThread t; // Statisches Thread-Objekt
//!    void f1()
//!    {
//!       t.start(); // Thread starten
//!       ...
//!       // Thread laeuft irgendwann zu Ende (tsTerminated), t lebt noch.
//!       ...
//!       t.waitFor(); // Sicheres Warten auf Thread-Ende
//!       ...
//!       t.start(cThread::teEnd); // Thread nochmal starten (mit Blocking)
//!    }
//!
//!    void f2()
//!    {
//!       cThread t; // Automatisches Thread-Objekt
//!       t.start();
//!       ...
//!       // f2() wird blockiert, bis Thread terminiert (tsWaitForEnd)
//!       // ACHTUNG: Virtuelle Funktionen werden nicht mehr aufgerufen!!!
//!    }
//!
//!    void f3()
//!    {
//!       cThread t; // Automatisches Thread-Objekt
//!       t.start(cThread::teEnd); // Besser: Warten auf Thread-Ende
//!    }
//!
//!    void f4()
//!    {
//!       cThread *t = new cThread(cThread::tdAutoDel);
//!       t->start();
//!       // Tatsaechliches delete von t erst nach Thread-Ende
//!    }
//!  @endcode
//
// 
// cThread
//
// ===========================================================================

class __ECL_DLLEXPORT__ cThread {
   friend void __ECL_THREADLNK__ BaseThread(void *);
   friend class cwThread;

public:

   //! Moegliche Werte fuer Auto-Delete-Flag
   enum AUTO_DEL {
      tdAutoDel,     //!< Auto-Delete aktiv (nur bei dynamischen Objekten!!!)
      tdNoAutoDel    //!< Auto-Delete nicht aktiv
   };

   //! Konstruiere normalen (secondary) Thread
   cThread(AUTO_DEL auto_del = tdNoAutoDel);
   //! Konstruiere normalen (secondary) Thread mit Angabe der Stack-Groese
   cThread(int stacksize, AUTO_DEL auto_del = tdNoAutoDel);
   //! Destruktor
   virtual ~cThread();


   //! @name Allgemeines
   //  =================

   //! Moegliche Thread-Events
   enum THREAD_EVENT {
      teNone,           //!< Kein Event (d.h. nicht warten)
      teStart,          //!< Thread gestartet, onEnter durchlaufen, naechster Aufruf onMain
      teEnd             //!< Thread ist beendet, letzter Aufruf war onLeave
   };

   //! Start thread (with additional parameter)
   bool start(void *extra, THREAD_EVENT wait_event = teNone);
   //! Start thread (without additional parameter)
   bool start(THREAD_EVENT wait_event = teNone);

   //! Wait for thread event
   void waitFor(THREAD_EVENT wait_event = teEnd);

   //! Get the return code of onMain().
   int getRC() const;
   //! Return thread ID. The value is only valid if thread is running and
   //! undefined prior to start() and after thread termination.
   int getThreadId() const;

   //! Liefert die ID des aktuellen Threads
   static int getCurrentThreadId();
   //! Liefert die ID des aktuellen Prozesses
   static int getCurrentProcessId();


   //! @name Aktueller Zustand
   //  =======================

   //! Moegliche Zustaende des Thread-Objektes
   enum STATE {
      tsCreated,     //!< Thread-Objekt angelegt, Thread noch nicht gestartet
      tsStarted,     //!< Thread gestartet, laeuft noch nicht
      tsRunning,     //!< Thread laeuft (onEnter, onMain, onLeave)
      tsTerminated,  //!< Thread normal zu Ende gelaufen
      tsWaitForEnd   //!< Destruktor verzoegert bis zum Thread-Ende
   };

   //! Aktuellen Zustand erfragen
   STATE getState() const;
   //! Ist der Thread am Laufen?
   bool isRunning() const;


   //! @name Main-Thread
   //  =================

   //! Construct main thread object.
   cThread(int argc, char **argv);
   //! Test for main thread.
   bool isMainThread() const;
   //! Get pointer of the main thread.
   static cThread *getMainThread();
   //! Number of main thread arguments.
   int getArgCount() const;
   //! Get main thread argument.
   const char *getArgValue(int arg) const;


   /**
    * @name Phasen der Thread-Bearbeitung
    *  Die folgenden Methoden werden \b ausschliesslich von der
    *  Basisklasse aufgerufen, um bestimmte Phasen der Thread-Bearbeitung
    *  durchzufuehren.
    */

   //! Wird an onLeave() bei Abschuss des Threads uebergeben
   enum { RC_KILL = 99 };

   //! Bei diesem Event kann sich der Thread initialisieren. @a extra ist der
   //! bei start() uebergebene parameter. Wird als Funktionswert false zurueckgegeben,
   //! wird der Thread abgebrochen und onMain() und onLeave() werden nicht ausgefuehrt.
   virtual bool onEnter(void *extra);
   //! Kernfunktion des Threads. @a extra ist der bei start() uebergebene
   //! Parameter. Der Funktionswert ist der Returncode @a rc.
   virtual int onMain(void *extra);
   //! Bei diesem Event kann sich der Thread deinitialisieren. Der Parameter @a rc
   //! ist der von onMain() gelieferte Returncode.
   virtual void onLeave(int rc);


   /**
    * @name Ausnahmebehandlung
    *  Liefert onException() false, wird die Exception-Behandlung
    *  mit dem naechsten Handler fortgesetzt. Bei true werden keine
    *  weiteren Handler mehr aufgerufen
    */

   //! Wird bei auftretender Exception aufgerufen
   virtual bool onException(cException *exception);


   //! @name Prioritaet
   //  ================

   //! Moegliche Werte fuer Thread-Prioritaetsklasse
   enum CLASS { 
      pcNoChange, 
      pcIdle, 
      pcRegular, 
      pcCritical, 
      pcServer 
   };
   //! Moegliche Werte fuer Thread-Prioritaetsstufe
   enum LEVEL { 
      plNoChange, 
      plIdle, 
      plLow, 
      plBelowNormal, 
      plNormal, 
      plAboveNormal, 
      plHigh, 
      plTimeCritical 
   };

   //! Liefert die Prioritaetsstufe innerhalb der -Klasse
   LEVEL getPriority();
   //! Liefert die Prioritaetsklasse
   CLASS getPriorityClass();
   //! Setzt Prioritaetsstufe und Klasse
   bool setPriority(LEVEL lvl, CLASS cls = pcNoChange);


   //! @name Suspendierung
   //  ===================

   //! Aktuellen Thread fuer bestimmte Zeit suspendieren
   static bool sleep(int ms);
   //! Thread (gewaltsam) beenden
   bool kill(bool wait = false);


protected:

   //! @name Events
   //  ============

   //! Wird aufgerufen, um die Methode 'start' zu realisieren
   virtual bool onStart();
   //! Wird aufgerufen, um die Methode 'kill' zu realisieren
   virtual bool onKill();

   //! Wird aufgerufen, um die Thread-Initialisierung zu realisieren
   virtual void onThreadInit();
   //! Wird aufgerufen, um die eigentliche Thread-Funktion zu realisieren
   virtual int onThreadRun();
   //! Wird aufgerufen, um den Thread zu beenden
   static void onThreadExit(cThread *thread);


private:
   // Copying is not allowed!
   cThread(const cThread &other);
   cThread &operator=(const cThread &other);

   // Attribute (generisch)
   struct cPrivate;
   cPrivate *_private;


};


}; // namespace ecl


#endif // __ecl_thread__

