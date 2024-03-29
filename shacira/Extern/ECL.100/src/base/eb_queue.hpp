/*.SH.*/

/*
 *  Headerfile for module eb_queue
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_queue.cpp on Tuesday April 02 2002  16:21:53
 */

#ifndef __eb_queue__
#define __eb_queue__


// Headerfiles
// ===========================================================================

#include "base/eb_ring.hpp"
#include "base/eb_sema.hpp"


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
// PR 31.05.05 timed out waiting causes problems
//   { if ( !mutex.request(1000) ) throw cErrBase(cErrBase::errTimeout); }
   { if ( !mutex.request() ) throw cErrBase(cErrBase::errTimeout); }
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


#endif

/*.EH.*/
