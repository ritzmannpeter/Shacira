// ===========================================================================
// base/queue.h                                                 ______ /  ECL
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

#ifndef __ecl_queue__
#define __ecl_queue__


// Other ECL headers
#include "base/ring.h"
#include "base/semaphore.h"

               
namespace ecl {


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
// ===========================================================================

// Set to 0 to use the new implementation without the static (!) variable
// max_concurrent_access. The new implementation uses a seperate _put_mutex
// and works with any count of sender threads.
#define USE_MAX_CONCURRENT_ACCESS 0

class __ECL_DLLEXPORT__ cQueueBase {

public:
   // Schreibverhalten bei voller Queue
   enum PUT_MODE {                              // Schreiben in volle Queue fuehrt zu:
      putError     = cRingBase::putError,       // - Fehler cErrBase::errOverflow
      putIgnore    = cRingBase::putIgnore,      // - Verlust der neuen Daten
      putOverwrite = cRingBase::putOverwrite,   // - Verlust der aeltesten Daten
      putBlock                                  // - Aktuellen Thread blockieren, bis Element frei
   };

#if USE_MAX_CONCURRENT_ACCESS
   // Maximalzahl gleichzeitiger Zugriffe einstellen
   static void setMaxConcurrentAccess(int mca);
   // Maximalzahl gleichzeitiger Zugriffe erfragen
   static int getMaxConcurrentAccess();
#else
   // Static variable completely removed
#endif

   // Pruefen, ob eine bestimmte Queue bereits allokiert ist
   static bool isAllocated(cString name)
      { return cRingBase::isAllocated(name); }

protected:
   cQueueBase(PUT_MODE put_mode = putBlock);
   cQueueBase(cString name, PUT_MODE put_mode = putBlock);

   // There was an old implementation of protectOn() with a hard coded
   // timeout. That makes no sense and looks like a experimantal change or
   // workaround that have never been removed. If timeout is really required,
   // a new PUT_MODE like 'putTimeout' may be introduced, together with a new
   // attribute and the corresponding setTimeout() and getTimeout().
   //
   // Removed code:
   // void protectOn()
   // {
   //    if ( !mutex.request(1000) ) {
   //       __ECL_RELEASE_TEXT__(cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, "timeout exception in cQueueBase");
   //       throw cErrBase(cErrBase::errTimeout); 
   //    }
   // }

#if USE_MAX_CONCURRENT_ACCESS
   void protectOn()
      { _mutex.request(); }
   void protectOff()
      { _mutex.release(); }
private:
   cMutexSem _mutex;
protected:
#else
   cMutexSem _put_mutex; // serialization of multiple senders
   cMutexSem _all_mutex; // protection of the data structure
#endif

   // put_mode in cRingBase-kompatiblen put_mode umwandeln
   cRingBase::PUT_MODE convPutMode(PUT_MODE put_mode) const
      { return put_mode != putBlock ? (cRingBase::PUT_MODE)put_mode : cRingBase::putError; }

   PUT_MODE _put_mode;
   cEventSem _first_elem_added;
   cEventSem _last_elem_removed;

private:
   // cQueueBase nicht kopierbar (enthaelt cMutexSem)
   cQueueBase(const cQueueBase &other);
   cQueueBase &operator=(const cQueueBase &other);

#if USE_MAX_CONCURRENT_ACCESS
   // Maximalzahl gleichzeitiger Zugriffe auf eine Queue
   static int max_concurrent_access;
#endif

};


// ===========================================================================
// Klasse cQueueRaw
// ---------------------------------------------------------------------------
//
// Realisiert eine untypisierte Queue zwischen einem Empfaenger-Thread und
// einem oder mehreren Sender-Threads.
//
// ===========================================================================

class __ECL_DLLEXPORT__ cQueueRaw : public cQueueBase {

public:
   cQueueRaw(int count, int size, PUT_MODE put_mode = putBlock) :
      cQueueBase(put_mode),
      _ring(count, size, convPutMode(put_mode))
      { }
   cQueueRaw(int count, int size, cString name, PUT_MODE put_mode = putBlock) :
      cQueueBase(name, put_mode),
      _ring(count, size, name, convPutMode(put_mode))
      { }

   // Ist die Queue momentan leer?
   bool isEmpty() const
      { return _ring.isEmpty(); }
   // Ist die Queue momentan voll?
   bool isFull() const
      { return _ring.isFull(); }

   // Anzahl freier Queue-Eintraege
   int getFree() const
      { return _ring.getFree(); }
   // Anzahl belegter Queue-Eintraege
   int getUsed() const
      { return _ring.getUsed(); }
   // Maximalzahl Queue-Eintraege
   int getCount() const
      { return _ring.getCount(); }
   // Groesse eines Queue-Eintrages
   int getSize() const
      { return _ring.getSize(); }

   // Hole naechstes Element aus der Queue; Warte, wenn leer
   void *get(void *buf, int size);
   // Schreibe Element in die Queue; Warte, wenn voll
   cQueueRaw& put(const void *buf, int size);

private:
   // cQueueRaw nicht kopierbar (cQueueBase enthaelt cMutexSem)
   cQueueRaw(const cQueueRaw &other);
   cQueueRaw &operator=(const cQueueRaw &other);

   cRingRaw _ring;

};


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
      _ring(count, convPutMode(put_mode))
      { }
   cQueue<TYPE>(int count, cString name, PUT_MODE put_mode = putBlock) :
      cQueueBase(name, put_mode),
      _ring(count, name, convPutMode(put_mode))
      { }

   // Ist die Queue momentan leer?
   bool isEmpty() const
      { return _ring.isEmpty(); }
   // Ist die Queue momentan voll?
   bool isFull() const
      { return _ring.isFull(); }

   // Anzahl freier Queue-Eintraege
   int getFree() const
      { return _ring.getFree(); }
   // Anzahl belegter Queue-Eintraege
   int getUsed() const
      { return _ring.getUsed(); }
   // Maximalzahl Queue-Eintraege
   int getCount() const
      { return _ring.getCount(); }
   // Groesse eines Queue-Eintrages
   int getSize() const
      { return _ring.getSize(); }

   // Hole naechstes Element aus der Queue; Warte, wenn leer
   TYPE get();
   // Schreibe Element in die Queue; Warte, wenn voll
   cQueue<TYPE>& put(const TYPE& value);

private:
   // cQueue<TYPE> nicht kopierbar (cQueueBase enthaelt cMutexSem)
   cQueue<TYPE>(const cQueue<TYPE> &other);
   cQueue<TYPE> &operator=(const cQueue<TYPE> &other);

   cRing<TYPE> _ring;

};


// Implementierung cQueue<TYPE>
// ===========================================================================

#if USE_MAX_CONCURRENT_ACCESS

// Old implementation of get() and put() WITH max_concurrent_access variable

template<class TYPE>
TYPE cQueue<TYPE>::get()
{
   protectOn();
   int retries = getMaxConcurrentAccess();

   for ( ; _ring.isEmpty() && retries > 0 ; retries-- ) {
      _first_elem_added.reset();
      protectOff();
      _first_elem_added.wait();
      protectOn();
   }

   if ( retries == 0 ) {
      protectOff();
      __ECL_RELEASE_TEXT__(cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, "timeout exception in cQueue<TYPE>::get");
      throw cErrBase(cErrBase::errTimeout);
   }

   bool previously_full = _ring.isFull();
   TYPE value = _ring.get();

   if ( previously_full )
      _last_elem_removed.set();

   protectOff();
   return value;
}

template<class TYPE>
cQueue<TYPE>& cQueue<TYPE>::put(const TYPE& value)
{
   protectOn();

   if ( _ring.isFull() ) {

      if ( _put_mode == putError ) {
         protectOff();
         __ECL_RELEASE_TEXT__(cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, "overflow exception in cQueue<TYPE>::put");
         throw cErrBase(cErrBase::errOverflow);
      } else if ( _put_mode == putIgnore ) {
         protectOff();
         return *this;
      } else if ( _put_mode == putBlock ) {
         int retries = getMaxConcurrentAccess();

         for ( ; _ring.isFull() && retries > 0 ; retries-- ) {
            _last_elem_removed.reset();
            protectOff();
            _last_elem_removed.wait();
            protectOn();
         }

         if ( retries == 0 ) {
            protectOff();
            __ECL_RELEASE_TEXT__(cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, "timeout exception in cQueue<TYPE>::put");
            throw cErrBase(cErrBase::errTimeout);
         }
      }
   }

   bool previously_empty = _ring.isEmpty();
   _ring.put(value);

   if ( previously_empty )
      _first_elem_added.set();

   protectOff();
   return *this;
}

#else

// New implementation of get() and put() WITHOUT max_concurrent_access variable

template<class TYPE>
TYPE cQueue<TYPE>::get()
{
   cMutexGuard all_guard(_all_mutex);

   if (_ring.isEmpty()) {
      _first_elem_added.reset();
      _all_mutex.release();
      _first_elem_added.wait();
      _all_mutex.request();
   }

   if (_ring.isFull()) {
      _last_elem_removed.set();
   }

   return _ring.get();
}

template<class TYPE>
cQueue<TYPE>& cQueue<TYPE>::put(const TYPE& value)
{
   cMutexGuard put_guard(_put_mutex);
   cMutexGuard all_guard(_all_mutex);

   if ( _ring.isFull() ) {
      switch (_put_mode) {
      case putError:
         throw cErrBase(cErrBase::errOverflow, "cQueueRaw");
      case putIgnore:
         return *this;
      case putOverwrite:
         break;
      case putBlock:
      default:
         if (_ring.isFull()) {
            _last_elem_removed.reset();
            _all_mutex.release();
            _last_elem_removed.wait();
            _all_mutex.request();
         }
         break;
      }
   }

   if (_ring.isEmpty()) {
      _first_elem_added.set();
   }

   _ring.put(value);
   return *this;
}


#endif


}; // namespace ecl


#endif // __ecl_queue__

