// ===========================================================================
// base/queue.cpp                                               ______ /  ECL
// Autoren: Markus Wuertz, Thomas Epting                       /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/queue.h"

// Other ECL headers
// #include "base/thread.h"

// Platform dependant headers
// #if defined __ECL_OS2__
//    #define INCL_PM
//    #define INCL_NLS
//    #define INCL_BASE
//    #include <os2.h>
// #elif defined __ECL_W32__
//    #include <windows.h>
// #endif




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ etc.
const unsigned long IPC_ERROR = cBase::dbgError | cBase::dbgIpc;
const unsigned long IPC_WARN  = cBase::dbgWarn  | cBase::dbgIpc;



#if USE_MAX_CONCURRENT_ACCESS

// Old implementation WITH max_concurrent_access variable
// ---------------------------------------------------------------------------

// Implementierung cQueueBase
// ===========================================================================

int cQueueBase::max_concurrent_access = 100;

cQueueBase::cQueueBase(PUT_MODE put_mode) :
   _mutex(),
   _first_elem_added(),
   _last_elem_removed(),
   _put_mode(put_mode)
{
}

cQueueBase::cQueueBase(cString name, PUT_MODE put_mode) :
   _mutex(name + "Mtx", cSema::semOpenOrCreate),
   _first_elem_added(name + "Add", cSema::semOpenOrCreate),
   _last_elem_removed(name + "Rem", cSema::semOpenOrCreate),
   _put_mode(put_mode)
{
}

void cQueueBase::setMaxConcurrentAccess(int mca)
{
   max_concurrent_access = mca;
}

int cQueueBase::getMaxConcurrentAccess()
{
   return max_concurrent_access;
}




// Implementierung cQueueRaw
// ===========================================================================

void *cQueueRaw::get(void *buf, int size)
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
      __ECL_RELEASE_TEXT__(IPC_ERROR, "QUEUE: Too many retries");
      throw cErrBase(cErrBase::errTimeout, "cQueueRaw::get");
   }

   bool previously_full = _ring.isFull();
   void *value = _ring.get(buf, size);

   if ( previously_full )
      _last_elem_removed.set();

   protectOff();
   return value;
}

cQueueRaw& cQueueRaw::put(const void *buf, int size)
{
   protectOn();

   if ( _ring.isFull() ) {

      if ( _put_mode == putError ) {
         protectOff();
         throw cErrBase(cErrBase::errOverflow, "cQueueRaw");
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
            __ECL_RELEASE_TEXT__(IPC_ERROR, "QUEUE: Too many retries");
            throw cErrBase(cErrBase::errTimeout, "cQueueRaw::put");
         }
      }
   }

   bool previously_empty = _ring.isEmpty();
   _ring.put(buf, size);

   if ( previously_empty )
      _first_elem_added.set();

   protectOff();
   return *this;
}

#else

// New implementation WITHOUT max_concurrent_access variable
// ---------------------------------------------------------------------------

// Implementierung cQueueBase
// ===========================================================================

cQueueBase::cQueueBase(PUT_MODE put_mode) :
   _put_mutex(),
   _all_mutex(),
   _first_elem_added(),
   _last_elem_removed(),
   _put_mode(put_mode)
{
}

cQueueBase::cQueueBase(cString name, PUT_MODE put_mode) :
   _put_mutex(name + "MtxPut", cSema::semOpenOrCreate),
   _all_mutex(name + "MtxAll", cSema::semOpenOrCreate),
   _first_elem_added(name + "EvtAdd", cSema::semOpenOrCreate),
   _last_elem_removed(name + "EvtRem", cSema::semOpenOrCreate),
   _put_mode(put_mode)
{
}




// Implementierung cQueueRaw
// ===========================================================================

void *cQueueRaw::get(void *buf, int size)
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

   return _ring.get(buf, size);
}

cQueueRaw& cQueueRaw::put(const void *buf, int size)
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

   _ring.put(buf, size);
   return *this;
}


#endif // USE_MAX_CONCURRENT_ACCESS




}; // namespace ecl


