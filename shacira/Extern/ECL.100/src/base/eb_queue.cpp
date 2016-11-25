// ===========================================================================
// eb_queue.cpp                                                 ______ /  ECL
// Autoren: Markus Wuertz, Thomas Epting                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cQueueBase              - Basisklasse zur Realisierung von Queues
//     |
//     +-cQueueRaw            - Untypisierte Queue (basierend auf void *)
//     |
//     +-cQueue<TYPE>         - Typsichere Queueverwaltung
//
// ===========================================================================

#include "base/eb_queue.hpp"
#include "base/eb_thread.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_ring.hpp"
#include "base/eb_sema.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Klasse cQueueBase
// ---------------------------------------------------------------------------
//
// Basisklasse zur Realisierung von Queues zwischen einem Empfaenger-Thread
// und einem oder mehreren Sender-Threads.
//
// Wird beim Konstruktor fuer benannte Queues count <= 0 oder size <= 0
// angegeben, wird die Queue im cSharedMem::memOpen-Modus geoeffnet (d.h.
// sie muss bereits erzeugt worden sein).
//
//  cQueueBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cQueueBase {

public:
   // Schreibverhalten bei voller Queue
   enum PUT_MODE {                              // Schreiben in volle Queue fuehrt zu:
      putError     = cRingBase::putError,       // - Fehler cErrBase::errOverflow
      putIgnore    = cRingBase::putIgnore,      // - Verlust der neuen Daten
      putOverwrite = cRingBase::putOverwrite,   // - Verlust der aeltesten Daten
      putBlock                                  // - Aktuellen Thread blockieren, bis Element frei
   };

   // Maximalzahl gleichzeitiger Zugriffe einstellen
   static void setMaxConcurrentAccess(int mca);
   // Maximalzahl gleichzeitiger Zugriffe erfragen
   static int getMaxConcurrentAccess();

   // Pruefen, ob eine bestimmte Queue bereits allokiert ist
   static bool isAllocated(cString name)
      { return cRingBase::isAllocated(name); }

protected:
   cQueueBase(PUT_MODE put_mode = putBlock);
   cQueueBase(cString name, PUT_MODE put_mode = putBlock);

   void protectOn()
      { if ( !mutex.request(1000) ) throw cErrBase(cErrBase::errTimeout); }
   void protectOff()
      { mutex.release(); }

   // put_mode in cRingBase-kompatiblen put_mode umwandeln
   cRingBase::PUT_MODE convPutMode(PUT_MODE put_mode) const
      { return put_mode != putBlock ? (cRingBase::PUT_MODE)put_mode : cRingBase::putError; }

   PUT_MODE put_mode;
   cEventSem first_elem_added;
   cEventSem last_elem_removed;

private:
   cMutexSem mutex;

   // Maximalzahl gleichzeitiger Zugriffe auf eine Queue
   static int max_concurrent_access;

};

#endif /*__INTERFACE__*/


// Implementierung cQueueBase
// ===========================================================================

int cQueueBase::max_concurrent_access = 100;

cQueueBase::cQueueBase(PUT_MODE put_mode) :
   mutex(),
   first_elem_added(),
   last_elem_removed()
{
   cQueueBase::put_mode = put_mode;
}

cQueueBase::cQueueBase(cString name, PUT_MODE put_mode) :
   mutex(name + "Mtx", cSema::semOpenOrCreate),
   first_elem_added(name + "Add", cSema::semOpenOrCreate),
   last_elem_removed(name + "Rem", cSema::semOpenOrCreate)
{
   cQueueBase::put_mode = put_mode;
}

void cQueueBase::setMaxConcurrentAccess(int mca)
{
   max_concurrent_access = mca;
}

int cQueueBase::getMaxConcurrentAccess()
{
   return max_concurrent_access;
}




#ifdef __INTERFACE__

// ===========================================================================
// Klasse cQueueRaw
// ---------------------------------------------------------------------------
//
// Realisiert eine untypisierte Queue zwischen einem Empfaenger-Thread und
// einem oder mehreren Sender-Threads.
//
//  cQueueBase
//   +--cQueueRaw
//
// ===========================================================================

class __ECL_DLLEXPORT__ cQueueRaw : public cQueueBase {

public:
   cQueueRaw(int count, int size, PUT_MODE put_mode = putBlock) :
      cQueueBase(put_mode),
      ring(count, size, convPutMode(put_mode))
      { }
   cQueueRaw(int count, int size, cString name, PUT_MODE put_mode = putBlock) :
      cQueueBase(name, put_mode),
      ring(count, size, name, convPutMode(put_mode))
      { }

   // Ist die Queue momentan leer?
   bool isEmpty() const
      { return ring.isEmpty(); }
   // Ist die Queue momentan voll?
   bool isFull() const
      { return ring.isFull(); }

   // Anzahl freier Queue-Eintraege
   int getFree() const
      { return ring.getFree(); }
   // Anzahl belegter Queue-Eintraege
   int getUsed() const
      { return ring.getUsed(); }
   // Maximalzahl Queue-Eintraege
   int getCount() const
      { return ring.getCount(); }
   // Groesse eines Queue-Eintrages
   int getSize() const
      { return ring.getSize(); }

   // Hole naechstes Element aus der Queue; Warte, wenn leer
   void *get(void *buf, int size);
   // Schreibe Element in die Queue; Warte, wenn voll
   cQueueRaw& put(const void *buf, int size);

private:
   cRingRaw ring;

};

#endif /*__INTERFACE__*/


// Implementierung cQueueRaw
// ===========================================================================

void *cQueueRaw::get(void *buf, int size)
{
   protectOn();
   int retries = getMaxConcurrentAccess();

   for ( ; ring.isEmpty() && retries > 0 ; retries-- ) {
      first_elem_added.reset();
      protectOff();
      first_elem_added.wait();
      protectOn();
   }

   if ( retries == 0 ) {
      protectOff();
      cBase::DbgError("QUEUE: Too many retries");
      throw cErrBase(cErrBase::errTimeout, "cQueueRaw::get");
   }

   bool previously_full = ring.isFull();
   void *value = ring.get(buf, size);

   if ( previously_full )
      last_elem_removed.set();

   protectOff();
   return value;
}

cQueueRaw& cQueueRaw::put(const void *buf, int size)
{
   protectOn();

   if ( ring.isFull() ) {

      if ( put_mode == putError ) {
         protectOff();
         throw cErrBase(cErrBase::errOverflow, "cQueueRaw");
      } else if ( put_mode == putIgnore ) {
         protectOff();
         return *this;
      } else if ( put_mode == putBlock ) {
         int retries = getMaxConcurrentAccess();

         for ( ; ring.isFull() && retries > 0 ; retries-- ) {
            last_elem_removed.reset();
            protectOff();
            last_elem_removed.wait();
            protectOn();
         }

         if ( retries == 0 ) {
            protectOff();
            cBase::DbgError("QUEUE: Too many retries");
            throw cErrBase(cErrBase::errTimeout, "cQueueRaw::put");
         }
      }
   }

   bool previously_empty = ring.isEmpty();
   ring.put(buf, size);

   if ( previously_empty )
      first_elem_added.set();

   protectOff();
   return *this;
}




#ifdef __INTERFACE__

// ===========================================================================
// Klasse cQueue<TYPE>
// ---------------------------------------------------------------------------
//
// Realisiert eine typsichere Queue zwischen einem Empfaenger-Thread und
// einem oder mehreren Sender-Threads.
//
//  cQueueBase
//   +--cQueue<TYPE>
//
// ===========================================================================

template<class TYPE>
class cQueue : public cQueueBase {

public:
   cQueue<TYPE>(int count, PUT_MODE put_mode = putBlock) :
      cQueueBase(put_mode),
      ring(count, convPutMode(put_mode))
      { }
   cQueue<TYPE>(int count, cString name, PUT_MODE put_mode = putBlock) :
      cQueueBase(name, put_mode),
      ring(count, name, convPutMode(put_mode))
      { }

   // Ist die Queue momentan leer?
   bool isEmpty() const
      { return ring.isEmpty(); }
   // Ist die Queue momentan voll?
   bool isFull() const
      { return ring.isFull(); }

   // Anzahl freier Queue-Eintraege
   int getFree() const
      { return ring.getFree(); }
   // Anzahl belegter Queue-Eintraege
   int getUsed() const
      { return ring.getUsed(); }
   // Maximalzahl Queue-Eintraege
   int getCount() const
      { return ring.getCount(); }
   // Groesse eines Queue-Eintrages
   int getSize() const
      { return ring.getSize(); }

   // Hole naechstes Element aus der Queue; Warte, wenn leer
   TYPE get();
   // Schreibe Element in die Queue; Warte, wenn voll
   cQueue<TYPE>& put(const TYPE& value);

private:
   cRing<TYPE> ring;

};


// Implementierung cQueue<TYPE>
// ===========================================================================

template<class TYPE>
TYPE cQueue<TYPE>::get()
{
   protectOn();
   int retries = getMaxConcurrentAccess();

   for ( ; ring.isEmpty() && retries > 0 ; retries-- ) {
      first_elem_added.reset();
      protectOff();
      first_elem_added.wait();
      protectOn();
   }

   if ( retries == 0 ) {
      protectOff();
      cBase::DbgError("QUEUE: Too many retries");
      throw cErrBase(cErrBase::errTimeout, "cQueue::get");
   }

   bool previously_full = ring.isFull();
   TYPE value = ring.get();

   if ( previously_full )
      last_elem_removed.set();

   protectOff();
   return value;
}

template<class TYPE>
cQueue<TYPE>& cQueue<TYPE>::put(const TYPE& value)
{
   protectOn();

   if ( ring.isFull() ) {

      if ( put_mode == putError ) {
         protectOff();
         throw cErrBase(cErrBase::errOverflow, "cQueue");
      } else if ( put_mode == putIgnore ) {
         protectOff();
         return *this;
      } else if ( put_mode == putBlock ) {
         int retries = getMaxConcurrentAccess();

         for ( ; ring.isFull() && retries > 0 ; retries-- ) {
            last_elem_removed.reset();
            protectOff();
            last_elem_removed.wait();
            protectOn();
         }

         if ( retries == 0 ) {
            protectOff();
            cBase::DbgError("QUEUE: Too many retries");
            throw cErrBase(cErrBase::errTimeout, "cQueue::put");
         }
      }
   }

   bool previously_empty = ring.isEmpty();
   ring.put(value);

   if ( previously_empty )
      first_elem_added.set();

   protectOff();
   return *this;
}

#endif /*__INTERFACE__*/




#ifdef __ENTFAELLT_GANZ__

// ===========================================================================
// Definition cIpcQueue
// ---------------------------------------------------------------------------
//
// Realisiert eine Queue zwischen einem Empfaenger-Thread und einem oder
// mehreren Sender-Threads ueber Prozessgrenzen hinweg. Es koennen jedoch
// nur void* uebertragen werden!
//
//  cBase
//   +--cOsBase
//       +--cIpcQueue
//
// ===========================================================================

class cIpcQueue : public cOsBase {

public:
   // Queue Server erzeugen
   cIpcQueue(cString name, int max_elems);
   // Client-Zugang oeffnen
   cIpcQueue(cString name);
   // Queue loeschen
   ~cIpcQueue();

   // Name der Queue erfragen
   cString getName() const
      { return name; }
   // Systemspezifischen Namen ermitteln
   cString getFullName() const;

   // Ist der Queue-Server noch am Leben?
   bool isAlive() const;
   // Reconnect mit Server versuchen
   bool reconnect();

   // Lesen von der Queue. Liefert false, wenn kein Element in der Queue
   bool read(void *& buf, bool wait = true);
   // Schreiben in die Queue. Liefert false, wenn Verbindung unterbrochen
   bool write(const void *buf, bool try_reconnect = false);

private:
   cString name;
   cEventSem *sync_sema;
   int pid_owner;

};


cIpcQueue::cIpcQueue(cString name, int max_elems)
{
   cIpcQueue::name = name;
   cIpcQueue::sync_sema = NULL;
   cIpcQueue::pid_owner = cThread::getProcessId();

   #if defined __ECL_OS2__
      name = "\\queues\\ecl\\" + name;
      APIRET rc = DosCreateQueue(&handle, QUE_FIFO, name);
      __ECL_ASSERT2__(!rc, ("OS/2: Creating queue %s failed, rc = %d", (const char *)name, rc))
      // if ( rc ) throw...
      sync_sema = new0 cEventSem();
   #elif defined __ECL_W32__
      // ...
      __ECL_ASSERT2__(0, ("Win32: Creating queue %s failed, err = %d", (const char *)name, GetLastError()))
   #endif
}

cIpcQueue::cIpcQueue(cString name)
{
   cIpcQueue::name = name;
   cIpcQueue::sync_sema = NULL;
   cIpcQueue::pid_owner = 0;

}

cIpcQueue::~cIpcQueue()
{
   #if defined __ECL_OS2__
      DosCloseQueue(handle);
   #elif defined __ECL_W32__
      // ...
   #endif

   delete sync_sema;
}

cString cIpcQueue::getFullName() const
{
   return "\\queues\\ecl\\" + name;
}

bool cIpcQueue::isAlive() const
{
   #if defined __ECL_OS2__
      ULONG dummy;
      if ( !handle.isValid() )
         return false;
      return DosQueryQueue(handle, &dummy) == NO_ERROR;
   #elif defined __ECL_W32__
      // ...
      return false;
   #endif
}

bool cIpcQueue::reconnect()
{
   if ( isAlive() )
      return true;

   #if defined __ECL_OS2__
      PID owner;
      APIRET rc = DosOpenQueue(&owner, &handle, getFullName());
      __ECL_ASSERT2__(!rc, ("OS/2: (Re-)connecting to queue %s failed, rc = %d", (const char *)getFullName(), rc))
      pid_owner = owner;
      return rc == NO_ERROR;
   #elif defined __ECL_W32__
      // ...
      __ECL_ASSERT2__(0, ("Win32: Opening queue %s failed, err = %d", (const char *)getFullName(), GetLastError()))
      return false;
   #endif
}

bool cIpcQueue::read(void *& buf, bool wait)
{
   #if defined __ECL_OS2__
      ULONG size; BYTE prio;
      REQUESTDATA request = { cThread::getProcessId(), 0 };
      if ( sync_sema == NULL )
         ; // throw...
      APIRET rc = DosReadQueue(handle, &request, &size, &buf, 0,
         wait ? DCWW_WAIT : DCWW_NOWAIT, &prio, getHandleFrom(*sync_sema));
      if ( rc == ERROR_QUE_EMPTY )
         return false;   // Legaler Zustand: Kein Eintrag vorhanden
      __ECL_ASSERT2__(!rc, ("OS/2: Reading from queue failed, rc = %d", rc))
      //if ( rc ) throw...
      return true;
   #elif defined __ECL_W32__
      // ...
      return false;
   #endif
}

bool cIpcQueue::write(const void *buf, bool try_reconnect)
{
   if ( try_reconnect && !reconnect() )
      return false;

   #if defined __ECL_OS2__
/*
      APIRET rc;
      if ( (rc = DosWriteQueue(handle, 0, size, buf, 0)) != NO_ERROR ) {
         DbgError("OS/2: DosWriteQueue returned %d\n", rc);
         throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
      }
*/
      return false;
   #elif defined __ECL_W32__
      // ...
      return false;
   #endif
}

#endif




#ifdef __Test_eb_queue__

   #include <conio.h>
   #include <iostream.h>
   #include "base/eb_thread.hpp"

   cQueue<char> Q(1, "Queue");

   void Client1()
   {
      while ( 1 ) {
         cThread::sleep(100);
         Q.put('*');
      }
   }

   void Client2()
   {
      while ( 1 ) {
         char ch = _getch();
         Q.put(ch);
      }
   }

   void Server()
   {
      while ( 1 ) {
         char ch = Q.get();
         cerr << ch;
      }
   }

   class cThread1 : public cThread {
   public:
      int onMain(void *) { Client1(); return 0; }
   };

   class cThread2 : public cThread {
   public:
      int onMain(void *) { Client2(); return 0; }
   };

   int main(int argc, char *argv[])
   {
      if ( argc < 2 ) {
         cThread1 t1; t1.start();
         cThread2 t2; t2.start();
         Server();
      } else if ( stricmp(argv[1], "c") == 0 ) {
         cThread1 t1; t1.start();
         Client2();
      } else if ( stricmp(argv[1], "s") == 0 ) {
         Server();
      }

      return 0;
   }

#endif

