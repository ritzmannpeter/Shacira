// ===========================================================================
// base/semaphore.cpp                                           ______ /  ECL
// Autor: Thomas Epting, Markus Wuertz                         /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================

#define IMPLEMENT_MUTEX_AS_CRITICAL_SECTION

#define __OLD_STYLE_MUTEX__ 0


// Interface header
#include "base/osbase.h"
#include "base/semaphore.h"

// Platform dependant headers
#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #if defined __ECL_PTHREADS__
      // pthreads gehoeren unter Windows nicht zu den Systemheadern, sondern
      // kommen aus dem benutzerdefinierten 3rd_party Zweig. Damit der Header
      // gefunden werden kann, das #include mit "..." statt <...>
      #include "pthread.h"
   #endif
   #include <windows.h>
   #ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   #include <assert.h>
   #endif
#elif defined __ECL_LINUX__
   #include <sys/types.h>
   #include <sys/ipc.h>
   #include <sys/sem.h>
   #include <pthread.h>
   #include <errno.h>
#endif




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ (identifizieren Semaphore-Modul)
const unsigned long SEMA_ERROR = cBase::dbgAssert |cBase::dbgIpc | cBase::dbgError ;
const unsigned long SEMA_WARN  = cBase::dbgIpc | cBase::dbgWarn;
const unsigned long SEMA_INFO  = cBase::dbgIpc | cBase::dbgInfo;

// ===========================================================================
// Implementierung cMutexSem
// ===========================================================================

/**
@class   cMutexSem
@brief   Mutual exclusive seamphore
@ingroup ipc


<b>Normal mutex</b> A thread attempting to relock the same mutex wihtout
first unlocking it will deadlock.

<b>Recursive mutex</b>  A thread can lock the same mutex multiple times and
it will not be unlocked until a corresponding number of unlock() calls have 
been made.

<b>Windows 32</b> It is a recursive semaphore. Using another initial state then false
is dangerous if two different threads may create the mutex.
- Excerpt of API documentation: The thread that owns a mutex can specify the same mutex in repeated wait function calls without blocking its execution. Typically, you would not wait repeatedly for the same mutex, but this mechanism prevents a thread from deadlocking itself while waiting for a mutex that it already owns. However, to release its ownership, the thread must call ReleaseMutex once for each time that the mutex satisfied a wait.
- Excerpt of API documentation: Two or more processes can call CreateMutex to create the same named mutex. The first process actually creates the mutex, and subsequent processes open a handle to the existing mutex. This enables multiple processes to get handles of the same mutex, while relieving the user of the responsibility of ensuring that the creating process is started first. When using this technique, you should set the bInitialOwner flag to FALSE; otherwise, it can be difficult to be certain which process has initial ownership.

<b>Linux / pthreads</b> It is a normal semaphore.
*/

#if __OLD_STYLE_MUTEX__
// Private data
struct cMutexSem::cPrivate {
   #if defined __ECL_PTHREADS__
      #if defined __ECL_LINUX__
         cPrivate() : is_mutex_valid(false),key(0) { }
         ~cPrivate() { delete key; }
         cOsBase::cOsKey *key;
         int semid;
      #else
         cPrivate() : is_mutex_valid(false) { }
         ~cPrivate() { }
      #endif
      bool is_mutex_valid;
      pthread_mutex_t mutex;
   #elif defined __ECL_W32__ || defined __ECL_OS2__
      // cPrivate() { constructor not needed } 
      cOsBase::cOsHandle handle;
   #endif
};
#endif



// driver/sema.h -------------------------------------------------------------
class cMutexSem::iPrivate
{
public:
   virtual ~iPrivate() {};

   virtual bool request() = 0;
   virtual bool tryRequest() = 0;
   virtual bool request(unsigned int ms_timeout) = 0;

   virtual void release() = 0;
};




// driver/sema_win.h/cpp -----------------------------------------------------
#if defined __ECL_W32__

class cPrivateWin : public cMutexSem::iPrivate
{
public:
   cPrivateWin(bool init_state);
   cPrivateWin(const cString &name, cMutexSem::OPEN_MODE mode, bool init_state);
   virtual ~cPrivateWin();

   virtual bool request();
   virtual bool tryRequest();
   virtual bool request(unsigned int ms_timeout);
   virtual void release();

private:
   HANDLE _handle;
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   CRITICAL_SECTION _criticalSection; 
#endif
};

cPrivateWin::cPrivateWin(bool init_state)
   : _handle(0)
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   BOOL success = InitializeCriticalSectionAndSpinCount(&_criticalSection, 0x00000400);
   __ECL_ASSERT_PRINTF__(success, SEMA_ERROR, ("Win32: Creation of critical section failed, err = %d", GetLastError()));
#else
   _handle = CreateMutex(0, init_state, 0);
   __ECL_ASSERT_PRINTF__(_handle, SEMA_ERROR, ("Win32: Creation of mutex semaphore failed, err = %d", GetLastError()));
#endif
}

cPrivateWin::cPrivateWin(const cString &name0, cMutexSem::OPEN_MODE mode, bool init_state)
   : _handle(0)
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   BOOL success = InitializeCriticalSectionAndSpinCount(&_criticalSection, 0x00000400);
   __ECL_ASSERT_PRINTF__(success, SEMA_ERROR, ("Win32: Creation of critical section failed, err = %d", GetLastError()));
#else
   __ECL_ASSERT_PRINTF__( init_state == false || mode != cMutexSem::semOpenOrCreate, SEMA_WARN, ("Dangerous init_state for selected mode") );
   
   cString name = "/sem/ecl/" + name0;
   if ( mode == cMutexSem::semOpen || mode == cMutexSem::semOpenOrCreate )
      _handle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, name);
   if ( _handle == 0 && mode != cMutexSem::semOpen )
      _handle = CreateMutex(0, init_state, name);
   __ECL_ASSERT_PRINTF__(_handle, SEMA_ERROR, ("Win32: Creation of mutex semaphore %s failed, err = %d", (const char *)name, GetLastError()));
#endif
}

cPrivateWin::~cPrivateWin()
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   DeleteCriticalSection(&_criticalSection);
#else
   CloseHandle(_handle);
#endif
}

bool cPrivateWin::request()
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   EnterCriticalSection(&_criticalSection);
   return true;
#else
   DWORD rc = WaitForSingleObject(_handle, INFINITE);
   __ECL_ASSERT_PRINTF__(rc != WAIT_FAILED, SEMA_ERROR, ("Win32: Waiting for event failed, rc = %d, err = %d", rc, GetLastError()));
   return rc == WAIT_OBJECT_0;
#endif
}

bool cPrivateWin::tryRequest()
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   BOOL success = TryEnterCriticalSection(&_criticalSection);
   return success ? true : false;;
#else
   DWORD rc = WaitForSingleObject(_handle, 0);
   __ECL_ASSERT_PRINTF__(rc != WAIT_FAILED, SEMA_ERROR, ("Win32: Waiting for event failed, rc = %d, err = %d", rc, GetLastError()));
   return rc == WAIT_OBJECT_0;
#endif
}

bool cPrivateWin::request(unsigned int ms_timeout)
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   assert(false);
   EnterCriticalSection(&_criticalSection);
   return true;
#else
   DWORD rc = WaitForSingleObject(_handle, (DWORD)ms_timeout);
   __ECL_ASSERT_PRINTF__(rc != WAIT_FAILED, SEMA_ERROR, ("Win32: Waiting for event failed, rc = %d, err = %d", rc, GetLastError()));
   return rc == WAIT_OBJECT_0;
#endif
}

void cPrivateWin::release()
{
#ifdef IMPLEMENT_MUTEX_AS_CRITICAL_SECTION
   LeaveCriticalSection(&_criticalSection);
#else
   BOOL ok = ReleaseMutex(_handle);
   if (!ok) {
      LPVOID lpMsgBuf;
      FormatMessage( 
         FORMAT_MESSAGE_ALLOCATE_BUFFER | 
         FORMAT_MESSAGE_FROM_SYSTEM | 
         FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL,
         GetLastError(),
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         (LPTSTR) &lpMsgBuf,
         0,
         NULL 
      );
      LPTSTR s = (LPTSTR)lpMsgBuf;
   }
   __ECL_ASSERT_PRINTF__(ok, SEMA_ERROR, ("Win32: Releasing mutex failed, err = %d", GetLastError()));
#endif
}

#endif // defined __ECL_W32__


// driver/sema_pthread.h/cpp -------------------------------------------------
#if defined __ECL_PTHREADS__

class pt_init {
public:
   pt_init() {
int rc = 0;
int type = 0;
//      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
//      int rc = pthread_mutexattr_init(&attr);
      mutex_attributes = &attr;
      printf("mutexes initialized %d,%d\n", rc, errno);
   };
   static pthread_mutexattr_t attr;
   static const pthread_mutexattr_t * mutex_attributes;
};
pthread_mutexattr_t pt_init::attr = {PTHREAD_MUTEX_RECURSIVE_NP};
const pthread_mutexattr_t * pt_init::mutex_attributes = 0;
static pt_init init;

class cPrivatePthreadAnonym : public cMutexSem::iPrivate
{
public:
   cPrivatePthreadAnonym(bool init_state);
   virtual ~cPrivatePthreadAnonym();

   virtual bool request();
   virtual bool tryRequest();
   virtual bool request(unsigned int ms_timeout);
   virtual void release();

private:
   pthread_mutex_t _mutex;
};

cPrivatePthreadAnonym::cPrivatePthreadAnonym(bool init_state)
{
   int err = pthread_mutex_init(&_mutex, pt_init::mutex_attributes);
   if (__ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_init failed: %s(%d)",strerror(err),err)) && init_state) {
      err = pthread_mutex_lock(&_mutex); 
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_lock (init_state) failed: %s(%d)",strerror(err),err));
   }
}

cPrivatePthreadAnonym::~cPrivatePthreadAnonym()
{
   int err = pthread_mutex_destroy(&_mutex); 
   __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_destroy failed: %s(%d)",strerror(err),err));
}

bool cPrivatePthreadAnonym::request()
{
   int err = pthread_mutex_lock(&_mutex); 
   return __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_lock failed: %s(%d)",strerror(err),err));
}

bool cPrivatePthreadAnonym::tryRequest()
{
   int err = pthread_mutex_trylock(&_mutex);
   if (err == EBUSY) {
      return false;
   } else {
      return __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_trylock failed: %s(%d)",strerror(err),err));
   }
}

bool cPrivatePthreadAnonym::request(unsigned int ms_timeout)
{
   __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of timed pthread mutex"); // TBD
   return request();
}

void cPrivatePthreadAnonym::release()
{
   int err = pthread_mutex_unlock(&_mutex); 
   __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_unlock failed: %s(%d)",strerror(err),err));
}

#endif // defined __ECL_PTREADS__




// driver/sema_linux.h/cpp ---------------------------------------------------
#if defined __ECL_LINUX__

class cPrivateLinuxNamed : public cMutexSem::iPrivate
{
public:
   cPrivateLinuxNamed(const cString &name, cMutexSem::OPEN_MODE mode, bool init_state);
   virtual ~cPrivateLinuxNamed();

   virtual bool request();
   virtual bool tryRequest();
   virtual bool request(unsigned int ms_timeout);
   virtual void release();

private:
   cOsBase::cOsKey *_key;
   int _semid;
   // Mit sem_flg = SEM_UNDO werden die Wirkungen eines Prozesses auf eine
   // Semaphore bei PROZESSENDE wieder "neutralisiert". Wenn request() und 
   // release() symmetrisch erfolgen und das abweichende IPC_NOWAIT bei
   // tryRequest() auch beachtet wird, sollten beim (unvorhergesehenen)
   // Prozessende belegte Semaphoren wieder freigegeben werden.
   int _release_sem_flg;
};

cPrivateLinuxNamed::cPrivateLinuxNamed(const cString &name0, cMutexSem::OPEN_MODE mode, bool init_state)
{
   cString name = "sema_" + name0;
   _key = new0 cOsBase::cOsKey(name, mode);
   if (__ECL_ASSERT_PRINTF__(_key->isValid(), SEMA_ERROR, ("Linux: No key for semaphore %s with mode %d: %s", _key->getName().ccp(), mode, strerror(errno)))) {
      _semid = semget(_key->getKey(), 1, _key->getFlags());
      if (__ECL_ASSERT_PRINTF__(_semid != -1, SEMA_ERROR, ("Linux: Can't get id for semaphore %s with mode %d: %s", _key->getName().ccp(), mode, strerror(errno)))) {
         int err = semctl(_semid, 0, SETVAL, 1);
         __ECL_ASSERT_PRINTF__(err != -1, SEMA_ERROR, ("Can't initialize semaphore %s with mode %d", _key->getName().ccp(), mode, strerror(errno)));
      }
   }
}

cPrivateLinuxNamed::~cPrivateLinuxNamed()
{
   if (_key->hasCreated()) {
      __ECL_ASSERT_PRINTF__(semctl(_semid, 0, IPC_RMID, 0) != -1, SEMA_ERROR, ("Linux: Destroying semaphore %s failed: %s", _key->getName().ccp(), strerror(errno)));
   }
   delete _key;
}

bool cPrivateLinuxNamed::request()
{
   struct sembuf sb[1];
   sb[0].sem_num = 0;
   sb[0].sem_op = -1;
   sb[0].sem_flg = _release_sem_flg = SEM_UNDO;
   return __ECL_ASSERT_PRINTF__(semop(_semid, sb,1) != -1, SEMA_ERROR, ("Linux: Requesting semaphore %s failed: %s(%d)", _key->getName().ccp(), strerror(errno),errno));
}

bool cPrivateLinuxNamed::tryRequest()
{
   //__ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of timed named mutex"); // TBD
   //return false;
   struct sembuf sb[1];
   sb[0].sem_num = 0;
   sb[0].sem_op = -1;
   sb[0].sem_flg = _release_sem_flg = IPC_NOWAIT;
   if (semop(_semid, sb, 1) != -1) {
      return true;
   } else {
      return __ECL_ASSERT_PRINTF__(errno == EAGAIN, SEMA_ERROR, ("Linux: Requesting semaphore %s failed: %s(%d)", _key->getName().ccp(), strerror(errno),errno));
   }
}

bool cPrivateLinuxNamed::request(unsigned int ms_timeout)
{
   __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of timed named mutex"); // TBD
   return request();
}

void cPrivateLinuxNamed::release()
{
   struct sembuf sb[1];
   sb[0].sem_num = 0;
   sb[0].sem_op = 1;
   sb[0].sem_flg = _release_sem_flg;
   __ECL_ASSERT_PRINTF__(semop(_semid, sb,1) != -1, SEMA_ERROR, ("Linux: Releasing semaphore %s failed: %s(%d)", _key->getName().ccp(), strerror(errno),errno));
}

#endif // defined __ECL_LINUX__




// ---------------------------------------------------------------------------
// Konstruktion & Destruktion (alte und neue Variante)
// ---------------------------------------------------------------------------

#if __OLD_STYLE_MUTEX__

   // Anonyme Mutex anlegen
   cMutexSem::cMutexSem(bool init_state) :
      _data(new0 cPrivate)
   {
      __ECL_STATISTIC__("cMutexSem(anonym)")
      openAnonymous(init_state);
   }

   // Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   cMutexSem::cMutexSem(const cString &name, OPEN_MODE mode, bool init_state) :
      _data(new cPrivate)
   {
      __ECL_STATISTIC__("cMutexSem(named)")
      openNamed(name, mode, init_state); 
   }

   // Mutex freigeben
   cMutexSem::~cMutexSem()
   { 
      close();
      delete _data;
   }

   bool cMutexSem::tryRequest() 
   { 
      return _request(0); 
   }

   bool cMutexSem::request() 
   { 
      return _request(-1); 
   }

   bool cMutexSem::request(unsigned int ms_timeout) 
   {
      return _request((int)ms_timeout); 
   }

#else // not __OLD_STYLE_MUTEX__

   cMutexSem::cMutexSem(bool init_state)
   {
      __ECL_STATISTIC__("cMutexSem(anonym)")
   #if defined __ECL_PTHREADS__
      _p = new0 cPrivatePthreadAnonym(init_state);
   #elif defined __ECL_W32__
      _p = new0 cPrivateWin(init_state);
   #else
      _p = 0;
      __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem(anonym) not supported");
   #endif
   }

   // Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   cMutexSem::cMutexSem(const cString &name, OPEN_MODE mode, bool init_state)
   {
      if (name.isEmpty()) {
         __ECL_STATISTIC__("cMutexSem(anonym)")
         #if defined __ECL_PTHREADS__
            _p = new0 cPrivatePthreadAnonym(init_state);
         #elif defined __ECL_W32__
            _p = new0 cPrivateWin(init_state);
         #else
            _p = 0;
            __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem(anonym) not supported");
         #endif
      } else {
         __ECL_STATISTIC__("cMutexSem(named)")
         #if defined __ECL_W32__
            _p = new0 cPrivateWin(name, mode, init_state);
         #elif defined __ECL_LINUX__
            _p = new0 cPrivateLinuxNamed(name, mode, init_state);
         #else
            _p = 0;
            __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem(named) not supported");
         #endif
      }
   }

   // Mutex freigeben
   cMutexSem::~cMutexSem()
   { 
      delete _p;
   }

   bool cMutexSem::tryRequest() 
   { 
      return _p->tryRequest(); 
   }

   bool cMutexSem::request() 
   { 
      return _p->request(); 
   }

   bool cMutexSem::request(unsigned int ms_timeout) 
   {
      return (ms_timeout > 0) ? _p->request(ms_timeout) : _p->tryRequest(); 
   }

   void cMutexSem::release()
   {
      _p->release();
   }

#endif // __OLD_STYLE_MUTEX__




// ---------------------------------------------------------------------------
// Implementierung (alte Variante)
// ---------------------------------------------------------------------------

#if __OLD_STYLE_MUTEX__
   
   void cMutexSem::openAnonymous(bool init_state)
   {
      __ECL_STATISTIC__("cMutexSem")

      #if defined __ECL_PTHREADS__

         int err = pthread_mutex_init(&_p->mutex, pt_init::mutex_attributes);
         _p->is_mutex_valid = (err == 0);
         if (__ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_init failed: %s(%d)",strerror(err),err)) && init_state) {
            err = pthread_mutex_lock(&_p->mutex); 
            __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_lock (init_state) failed: %s(%d)",strerror(err),err));
         }

      #elif defined __ECL_OS2__
         #error redesign of OS/2 handles not done
         APIRET rc = DosCreateMutexSem(0, &handle, 0, init_state);
         __ECL_ASSERT2__(!rc, ("OS/2: Creation of mutex semaphore failed, rc = %d", rc));
      #elif defined __ECL_W32__
         _p->handle = CreateMutex(0, init_state, 0);
         __ECL_ASSERT2__(_p->handle.isValid(), ("Win32: Creation of mutex semaphore failed, err = %d", GetLastError()));
      #endif
   }

   void cMutexSem::openNamed(const cString &name0, OPEN_MODE mode, bool init_state)
   {
      if ( name0.isEmpty() ) {
         openAnonymous(init_state);
      } else {
         __ECL_STATISTIC__("cMutexSem(named)")

         #if defined __ECL_LINUX__

            cString name = "sema_" + name0;
            _p->key = new0 cOsBase::cOsKey(name, mode);
            if (__ECL_ASSERT_PRINTF__(_p->key->isValid(), SEMA_ERROR, ("Linux: No key for semaphore %s with mode %d: %s", _p->key->getName().ccp(), mode, strerror(errno)))) {
               _p->semid = semget(_p->key->getKey(), 1, _p->key->getFlags());
               if (__ECL_ASSERT_PRINTF__(_p->semid != -1, SEMA_ERROR, ("Linux: Can't get id for semaphore %s with mode %d: %s", _p->key->getName().ccp(), mode, strerror(errno)))) {
                  int err = semctl(_p->semid, 0, SETVAL, 1);
                  __ECL_ASSERT_PRINTF__(err != -1, SEMA_ERROR, ("Can't initialize semaphore %s with mode %d", _p->key->getName().ccp(), mode, strerror(errno)));
               }
            }

         #elif defined __ECL_OS2__
            #error redesign of OS/2 handles not done
            APIRET rc;
            name = "\\sem32\\ecl\\" + name;
            if ( mode == semOpen || mode == semOpenOrCreate )
               rc = DosOpenMutexSem(name, &handle);
            if ( rc != NO_ERROR && mode != semOpen )
               rc = DosCreateMutexSem(name, &handle, 0, init_state);
            __ECL_ASSERT2__(!rc, ("OS/2: Creation of mutex semaphore %s failed, rc = %d", (const char *)name, rc));
         #elif defined __ECL_W32__ && !defined __ECL_PTHREADS__
            __ECL_ASSERT_PRINTF__( init_state == false || mode != semOpenOrCreate, SEMA_WARN, ("Dangerous init_state for selected mode") );

            cString name = "/sem/ecl/" + name0;
            if ( mode == semOpen || mode == semOpenOrCreate )
               _p->handle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, name);
            if ( !_p->handle.isValid() && mode != semOpen )
               _p->handle = CreateMutex(0, init_state, name);
            __ECL_ASSERT2__(_p->handle.isValid(), ("Win32: Creation of mutex semaphore %s failed, err = %d", (const char *)name, GetLastError()));
         #else

            __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of named mutex semaphores"); // TBD

         #endif
      }
   }

   void cMutexSem::close()
   {
      #if defined __ECL_PTHREADS__

         if (_p->is_mutex_valid) {
            int err = pthread_mutex_destroy(&_p->mutex); 
            __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_destroy failed: %s(%d)",strerror(err),err));
         }
         #if defined __ECL_LINUX__
            else if (_p->key) {
               if (_p->key->hasCreated()) {
                  __ECL_ASSERT_PRINTF__(semctl(_p->semid, 0, IPC_RMID, 0) != -1, SEMA_ERROR, ("Linux: Destroying semaphore %s failed: %s", _p->key->getName().ccp(), strerror(errno)));
               }
            }
         #endif

      #elif defined __ECL_OS2__
         #error redesign of OS/2 handles not done
         DosCloseMutexSem(handle);
      #elif defined __ECL_W32__
         CloseHandle(_p->handle);
      #endif
   }


   bool cMutexSem::_request(int ms_timeout)
   {
      #if defined __ECL_LINUX__
         if (_p->key) {
            if (ms_timeout < 0) { // unendlich warten
               struct sembuf sb[1];
               sb[0].sem_num = 0;
               sb[0].sem_op = -1;
               sb[0].sem_flg = SEM_UNDO;
               return __ECL_ASSERT_PRINTF__(semop(_p->semid, sb,1) != -1, SEMA_ERROR, ("Linux: Requesting semaphore %s failed: %s(%d)", _p->key->getName().ccp(), strerror(errno),errno));
            } else if (ms_timeout == 0) { // sofortige Rueckkehr nicht unterstuetzt
               __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of named mutex check"); // TBD
            } else { // timeout nicht unterstuetzt
               __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of timed named mutex"); // TBD
            }
         } else {
            if (_p->is_mutex_valid == false) {
               __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: request on invalid pthread mutex");
               return false;
            } else if (ms_timeout < 0) { // unendlich warten
               int err = pthread_mutex_lock(&_p->mutex); 
               __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_lock failed: %s(%d)",strerror(err),err));
               return err == 0;
            } else if (ms_timeout == 0) { // sofortige Rückkehr
               int err = pthread_mutex_trylock(&_p->mutex);
               if (err == EBUSY) {
                  return false;
               } else {
                  return __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_trylock failed: %s(%d)",strerror(err),err));
               }
            } else { // timeout nicht unterstützt
               __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: no support of timed pthread mutex"); // TBD
               return false;
            }
         }

      #elif defined __ECL_OS2__
         #error redesign of OS/2 handles not done
         ULONG tmo = ms_timeout >= 0 ? (ULONG)ms_timeout : SEM_INDEFINITE_WAIT;
         APIRET rc = DosRequestMutexSem(handle, tmo);
         __ECL_ASSERT2__(!rc, ("OS/2: Requesting mutex failed, rc = %d", rc));
         return rc == NO_ERROR;

      #elif defined __ECL_W32__
         DWORD tmo = ms_timeout >= 0 ? (DWORD)ms_timeout : INFINITE;
         DWORD rc = WaitForSingleObject(_p->handle, tmo);
         __ECL_ASSERT2__(rc != WAIT_FAILED, ("Win32: Waiting for event failed, rc = %d, err = %d", rc, GetLastError()));
         return rc == WAIT_OBJECT_0;
      #endif
   }

   void cMutexSem::release()
   {
      #if defined __ECL_LINUX__

         if (_p->key) {
            struct sembuf sb[1];
            sb[0].sem_num = 0;
            sb[0].sem_op = 1;
            sb[0].sem_flg = SEM_UNDO;
            __ECL_ASSERT_PRINTF__(semop(_p->semid, sb,1) != -1, SEMA_ERROR, ("Linux: Releasing semaphore %s failed: %s(%d)", _p->key->getName().ccp(), strerror(errno),errno));
         } else {
            if (_p->is_mutex_valid == false) {
               __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMutexSem: release on invalid pthread mutex");
            } else {
               int err = pthread_mutex_unlock(&_p->mutex); 
               __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cMutexSem: pthread_mutex_unlock failed: %s(%d)",strerror(err),err));
            }
         }

      #elif defined __ECL_OS2__
         #error redesign of OS/2 handles not done
         APIRET rc = DosReleaseMutexSem(handle);
         __ECL_ASSERT2__(!rc, ("OS/2: Releasing mutex failed, rc = %d", rc));
      #elif defined __ECL_W32__
         BOOL ok = ReleaseMutex(_p->handle);
         __ECL_ASSERT2__(ok, ("Win32: Releasing mutex failed, err = %d", GetLastError()));
      #endif
   }

#endif // __OLD_STYLE_MUTEX__




// ===========================================================================
// Implementierung cEventSem
// ===========================================================================

// Private data
class cEventSem::iPrivate 
{
public:
   #if defined __ECL_PTHREADS__
      pthread_cond_t cond;
      pthread_mutex_t mutex;
      pthread_mutex_t dummy_mutex;
      bool event_state;
   #elif defined __ECL_W32__ || defined __ECL_OS2__
      // cPrivate() { nothing needed } 
      cOsBase::cOsHandle handle;
   #endif
};

// TBD: Haesslicher Workaround :-(
const cOsBase::cOsHandle cEventSem::getHandle() const
{
   #if defined __ECL_PTHREADS__
      __ECL_DEBUG_TEXT__(SEMA_ERROR, "pthreads: no support of cOsHandle in cEventSem");
      return cOsBase::cOsHandle();
   #elif defined __ECL_W32__ || defined __ECL_OS2__
      // cPrivate() { nothing needed } 
      return _p->handle;
   #else
      return cOsBase::cOsHandle();
   #endif
}


// Anonymen Event anlegen
cEventSem::cEventSem(bool init_state) :
   _p(new iPrivate)
{ 
   openAnonymous(init_state); 
}

// Benannten Event oeffnen oder erzeugen (abhaengig von 'mode')
cEventSem::cEventSem(const cString &name, OPEN_MODE mode, bool init_state) :
   _p(new iPrivate)
{ 
   openNamed(name, mode, init_state); 
}

// Event freigeben
cEventSem::~cEventSem()
{ 
   close();
   delete _p;
}

   
void cEventSem::openAnonymous(bool init_state)
{
   __ECL_STATISTIC__("cEventSem(anonym)")

   #if defined __ECL_PTHREADS__

      int err = pthread_mutex_init(&_p->dummy_mutex, pt_init::mutex_attributes);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_mutex_init (dummy) failed: %s(%d)",strerror(err),err));
      err = pthread_mutex_lock(&_p->dummy_mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_mutex_lock (dummy) failed: %s(%d)",strerror(err),err));
      err = pthread_mutex_init(&_p->mutex, pt_init::mutex_attributes);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_mutex_init failed: %s(%d)",strerror(err),err));      
      err = pthread_cond_init(&_p->cond, 0);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_cond_init failed: %s(%d)",strerror(err),err));
      _p->event_state = init_state;

   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      APIRET rc = DosCreateEventSem(0, &handle, 0, init_state);
      __ECL_ASSERT2__(!rc, ("OS/2: Creation of event semaphore failed, rc = %d", rc));
   #elif defined __ECL_W32__
      _p->handle = CreateEvent(0, TRUE, init_state, 0);
      __ECL_ASSERT_PRINTF__(_p->handle.isValid(), SEMA_ERROR, ("Win32: Creation of event semaphore failed, err = %d", GetLastError()));
   #endif
}

void cEventSem::openNamed(const cString &name0, OPEN_MODE mode, bool init_state)
{
   if ( name0.isEmpty() ) {
      openAnonymous(init_state);
   } else {
      __ECL_STATISTIC__("cEventSem(named)")

      #if defined __ECL_PTHREADS__

         __ECL_DEBUG_TEXT__(SEMA_ERROR, "cEventSem: no support of named event semaphores"); // TBD
         // Signale? Abbildung auf Semaphore?
      
      #elif defined __ECL_OS2__
         #error redesign of OS/2 handles not done
         APIRET rc;
         name = "\\sem32\\ecl\\" + name;
         if ( mode == semOpen || mode == semOpenOrCreate )
            rc = DosOpenEventSem(name, &handle);
         if ( rc != NO_ERROR && mode != semOpen )
            rc = DosCreateEventSem(name, &handle, 0, init_state);
         __ECL_ASSERT2__(!rc, ("OS/2: Creation of event semaphore %s failed, rc = %d", (const char *)name, rc));
      #elif defined __ECL_W32__
         cString name = "/sem/ecl/" + name0;
         if ( mode == semOpen || mode == semOpenOrCreate )
            _p->handle = OpenEvent(EVENT_ALL_ACCESS, FALSE, name);
         if ( !_p->handle.isValid() && mode != semOpen )
            _p->handle = CreateEvent(0, TRUE, init_state, name);
         __ECL_ASSERT_PRINTF__(_p->handle.isValid(), SEMA_ERROR, ("Win32: Creation of event semaphore %s failed, err = %d", (const char *)name, GetLastError()));
      #endif
   }
}

void cEventSem::close()
{
   #if defined __ECL_PTHREADS__

      int err = pthread_cond_destroy(&_p->cond);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_cond_destroy failed: %s(%d)",strerror(err),err));
      err = pthread_mutex_destroy(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_mutex_destroy failed: %s(%d)",strerror(err),err));
      err = pthread_mutex_unlock(&_p->dummy_mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_mutex_unlock (dummy) failed: %s(%d)",strerror(err),err));
      err = pthread_mutex_destroy(&_p->dummy_mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem: pthread_mutex_destroy (dummy) failed: %s(%d)",strerror(err),err));
   
   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      DosCloseEventSem(handle);
   #elif defined __ECL_W32__
      CloseHandle(_p->handle);
   #endif
}

bool cEventSem::wait(int ms_timeout) const
{
   #if defined __ECL_PTHREADS__
      
      int err; bool result = false;
      err = pthread_mutex_lock(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::wait: pthread_mutex_lock failed: %s(%d)",strerror(err),err));

      if (_p->event_state == true || ms_timeout == 0) {
         result = _p->event_state;
      } else if (ms_timeout < 0) {
         while (_p->event_state == false && !err) {
            err = pthread_cond_wait(&_p->cond, &_p->mutex);
            __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::wait: pthread_cond_wait failed: %s(%d)",strerror(err),err));
         }
         result = _p->event_state;
      } else {
         __ECL_DEBUG_TEXT__(SEMA_ERROR, "cEventSem::wait: timed variant not implemented yet"); // TBD
      }
      
      err = pthread_mutex_unlock(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::wait: pthread_mutex_unlock failed: %s(%d)",strerror(err),err));
      return result;

   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      ULONG tmo = ms_timeout >= 0 ? (ULONG)ms_timeout : SEM_INDEFINITE_WAIT;
      APIRET rc = DosWaitEventSem(handle, tmo);
      __ECL_ASSERT2__(!rc, ("OS/2: Waiting for event failed, rc = %d", rc));
      return rc == NO_ERROR;
   #elif defined __ECL_W32__
      DWORD tmo = ms_timeout >= 0 ? (DWORD)ms_timeout : INFINITE;
      DWORD rc = WaitForSingleObject(_p->handle, tmo);
      __ECL_ASSERT_PRINTF__(rc != WAIT_FAILED, SEMA_ERROR, ("Win32: Waiting for event failed, err = %d", GetLastError()));
      return rc == WAIT_OBJECT_0;
   #endif
}

void cEventSem::set()
{
   #if defined __ECL_PTHREADS__

      int err;
      err = pthread_mutex_lock(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::set: pthread_mutex_lock failed: %s(%d)",strerror(err),err));
      
      _p->event_state = true;
      err = pthread_cond_broadcast(&_p->cond);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::set: pthread_cond_broadcast failed: %s(%d)",strerror(err),err));

      err = pthread_mutex_unlock(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::set: pthread_mutex_unlock failed: %s(%d)",strerror(err),err));
   
   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      APIRET rc = DosPostEventSem(handle);
      if ( rc == ERROR_ALREADY_POSTED ) return;
      __ECL_ASSERT2__(!rc, ("OS/2: Set event failed, rc = %d", rc));
   #elif defined __ECL_W32__
      BOOL ok = SetEvent(_p->handle);
      __ECL_ASSERT_PRINTF__(ok, SEMA_ERROR, ("Win32: Set event failed, err = %d", GetLastError()));
   #endif
}

void cEventSem::reset()
{
   #if defined __ECL_PTHREADS__

      int err;
      err = pthread_mutex_lock(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::reset: pthread_mutex_lock failed: %s(%d)",strerror(err),err));
      
      _p->event_state = false;
      err = pthread_cond_broadcast(&_p->cond);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::reset: pthread_cond_broadcast failed: %s(%d)",strerror(err),err));

      err = pthread_mutex_unlock(&_p->mutex);
      __ECL_ASSERT_PRINTF__(!err, SEMA_ERROR, ("cEventSem::reset: pthread_mutex_unlock failed: %s(%d)",strerror(err),err));
   
   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      ULONG post_count;
      APIRET rc = DosResetEventSem(handle, &post_count);
      if ( rc == ERROR_ALREADY_RESET ) return;
      __ECL_ASSERT2__(!rc, ("OS/2: Reset event failed, rc = %d", rc));
   #elif defined __ECL_W32__
      BOOL ok = ResetEvent(_p->handle);
      __ECL_ASSERT_PRINTF__(ok, SEMA_ERROR, ("Win32: Reset event failed, err = %d", GetLastError()));
   #endif
}

void cEventSem::pulse()
{
   #if defined __ECL_PTHREADS__

      set();
      reset();

   #elif defined __ECL_W32__
      BOOL ok = PulseEvent(_p->handle);
      __ECL_ASSERT_PRINTF__(ok, SEMA_ERROR, ("Win32: Pulse event failed, err = %d", GetLastError()));
   #else
      set();
      reset();
   #endif
}

bool cEventSem::query() const
{
   #if defined __ECL_PTHREADS__

      // TBD: braucht lesen der einen Variablen einen Mutex?
      return _p->event_state;

   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      ULONG post_count;
      APIRET rc = DosQueryEventSem(handle, &post_count);
      __ECL_ASSERT2__(!rc, ("OS/2: Reset event failed, rc = %d", rc));
      return post_count != 0;
   #elif defined __ECL_W32__
      DWORD rc = WaitForSingleObject(_p->handle, 0);
      __ECL_ASSERT_PRINTF__(rc != WAIT_FAILED, SEMA_ERROR, ("Win32: Query event failed, err = %d", GetLastError()));
      return rc == WAIT_OBJECT_0;
   #endif
}



// Implementierung cMuxEventSem
// ===========================================================================

// Konstruktoren / Destruktor
cMuxEventSem::cMuxEventSem()
{
   __ECL_STATISTIC__("cMuxEventSem")
}

cMuxEventSem::cMuxEventSem(const cEventSem& event)
{ 
   __ECL_STATISTIC__("cMuxEventSem")
   addEvent(event); 
}

cMuxEventSem::cMuxEventSem(const cMuxEventSem& other)
{ 
   // Copy-Konstruktor wird nicht gezaehlt
   // __ECL_STATISTIC__("cMuxEventSem")
   setEvents(other); 
}

// cMuxEventSem::~cMuxEventSem() { }


cMuxEventSem& cMuxEventSem::setEvent(const cEventSem& event)
{
   semp_list.removeAll();
   semp_list.addTail(&event);
   return *this;
}

cMuxEventSem& cMuxEventSem::setEvents(const cMuxEventSem& other)
{
   semp_list.removeAll();
   for ( IPOSITION it = other.semp_list.getHeadPosition() ; it != 0 ; )
      semp_list.addTail(other.semp_list.getNext(it));
   return *this;
}

cMuxEventSem& cMuxEventSem::addEvent(const cEventSem& event)
{
   for ( IPOSITION it = semp_list.getHeadPosition() ; it != 0 ; ) {
      const cEventSem *ev = semp_list.getNext(it);
      if ( ev == &event )
         return *this;
   }

   semp_list.addTail(&event);
   return *this;
}

cMuxEventSem& cMuxEventSem::addEvents(const cMuxEventSem& other)
{
   for ( IPOSITION it = other.semp_list.getHeadPosition() ; it != 0 ; )
      semp_list.addTail(other.semp_list.getNext(it));
   return *this;
}

bool cMuxEventSem::wait(int ms_timeout, bool wait_for_all)
{
   int count = semp_list.getCount();
   if ( count < 1 )
      return true;

   #if defined __ECL_PTHREADS__

      __ECL_DEBUG_TEXT__(SEMA_ERROR, "cMuxEventSem: no support of multiple event semaphores"); // TBD
      return false;

   #elif defined __ECL_OS2__
      #error redesign of OS/2 handles not done
      SEMRECORD *semrecs = new0 SEMRECORD[count];
      IPOSITION it = semp_list.getHeadPosition();
      for ( int i = 0 ; it != 0 ; i++ ) {
         const cEventSem *ev = semp_list.getNext(it);
         semrecs[i].hsemCur = (HSEM)(unsigned long)getHandleFrom(*ev);
         semrecs[i].ulUser = i;
      }
      ULONG tmo = ms_timeout >= 0 ? (ULONG)ms_timeout : SEM_INDEFINITE_WAIT;
      ULONG attrs = wait_for_all ? DCMW_WAIT_ALL : DCMW_WAIT_ANY;
      APIRET rc = DosCreateMuxWaitSem(0, &handle, count, semrecs, attrs);
      if ( rc == NO_ERROR ) {
         ULONG value;
         rc = DosWaitMuxWaitSem(handle, tmo, &value);
         DosCloseMuxWaitSem(handle);
      }
      __ECL_ASSERT2__(!rc, ("OS/2: Waiting for events failed, rc = %d", rc));
      delete[] semrecs; // -TE- 02.03.2001 delete -> delete[]
      return rc == NO_ERROR;
   #elif defined __ECL_W32__
      HANDLE *handles = new0 HANDLE[count];
      IPOSITION it = semp_list.getHeadPosition();
      for ( int i = 0 ; it != 0 ; i++ ) {
         const cEventSem *ev = semp_list.getNext(it);
         handles[i] = ev->getHandle();
      }
      DWORD tmo = ms_timeout >= 0 ? (DWORD)ms_timeout : INFINITE;
      DWORD rc = WaitForMultipleObjects(count, handles, wait_for_all, tmo);
      __ECL_ASSERT_PRINTF__(rc != WAIT_FAILED, SEMA_ERROR, ("Win32: Waiting for events failed, err = %d", GetLastError()));
      delete[] handles; // -TE- 02.03.2001 delete -> delete[]
      return rc == WAIT_OBJECT_0;
   #endif
}




}; // namespace ecl

