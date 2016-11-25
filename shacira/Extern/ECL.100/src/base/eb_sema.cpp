// ===========================================================================
// eb_sema.cpp                                   ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cOsBase
//        |
//        +-cSema             - Basisklasse fuer Semaphoren.
//        |  |
//        |  +-cMutexSem      - Mutual Exclusive Semaphore.
//        |  |
//        |  +-cEventSem      - Event Semaphore.
//        |
//        +-cMuxEventSem      - Multiple Event Semaphore.
//
// ===========================================================================

#include "base/eb_sema.hpp"

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

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"
#include "base/eb_list.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cSema
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Semaphoren
//
// cBase
//  +--cOsBase
//      +--cSema
//
// ===========================================================================

class __ECL_DLLEXPORT__ cSema : public cOsBase {

public:
   enum OPEN_MODE {
      semCreate,        // Semaphore erzeugen
      semOpen,          // Semaphore oeffnen (Verbindung herstellen)
      semOpenOrCreate   // Semaphore oeffnen (Erzeugen, falls nicht vorhanden)
   };

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cMutexSem
// ---------------------------------------------------------------------------
//
// Mutual exclusive Semaphore. Der Initialzustand kann beim Konstruktor ange-
// geben werden (realisiert ueber bool):
//
//    true  - Mutex belegt
//    false - Mutex nicht belegt
//
// cBase
//  +--cOsBase
//      +--cSema
//          +--cMutexSem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMutexSem : public cSema {

public:
   // Anonyme Mutex anlegen
   cMutexSem(bool init_state = false)
      { openAnonymous(init_state); }
   // Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   cMutexSem(cString name, OPEN_MODE mode, bool init_state = false)
      { openNamed(name, mode, init_state); }
   // Mutex freigeben
   ~cMutexSem()
      { close(); }

   // Mutex anfordern (liefert false bei Timeout oder Fehler)
   // ms_timeout: <0: Unendlich; =0: Sofortige Rueckkehr; >0: Timeout in ms
   bool request(int ms_timeout = -1);
   // Mutex freigeben
   void release();

private:
   // Anonyme Mutex oeffnen
   void openAnonymous(bool init_state);
   // Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   void openNamed(cString name, OPEN_MODE mode, bool init_state);
   // Mutex schliessen
   void close();

};

#endif /*__INTERFACE__*/


// Implementierung cMutexSem
// ===========================================================================

void cMutexSem::openAnonymous(bool init_state)
{
   #if defined __ECL_OS2__
      APIRET rc = DosCreateMutexSem(NULL, &handle, 0, init_state);
      __ECL_ASSERT2__(!rc, ("OS/2: Creation of mutex semaphore failed, rc = %d", rc));
   #elif defined __ECL_W32__
      handle = CreateMutex(NULL, init_state, NULL);
      __ECL_ASSERT2__(handle.isValid(), ("Win32: Creation of mutex semaphore failed, err = %d", GetLastError()));
   #endif
}

void cMutexSem::openNamed(cString name, OPEN_MODE mode, bool init_state)
{
   if ( name.isEmpty() ) {
      openAnonymous(init_state);
   } else {
      #if defined __ECL_OS2__
         APIRET rc;
         name = "\\sem32\\ecl\\" + name;
         if ( mode == semOpen || mode == semOpenOrCreate )
            rc = DosOpenMutexSem(name, &handle);
         if ( rc != NO_ERROR && mode != semOpen )
            rc = DosCreateMutexSem(name, &handle, 0, init_state);
         __ECL_ASSERT2__(!rc, ("OS/2: Creation of mutex semaphore %s failed, rc = %d", (const char *)name, rc));
      #elif defined __ECL_W32__
         name = "/sem/ecl/" + name;
         if ( mode == semOpen || mode == semOpenOrCreate )
            handle = OpenMutex(MUTEX_ALL_ACCESS, FALSE, name);
         if ( !handle.isValid() && mode != semOpen )
            handle = CreateMutex(NULL, init_state, name);
         __ECL_ASSERT2__(handle.isValid(), ("Win32: Creation of mutex semaphore %s failed, err = %d", (const char *)name, GetLastError()));
      #endif
   }
}

void cMutexSem::close()
{
   #if defined __ECL_OS2__
      DosCloseMutexSem(handle);
   #elif defined __ECL_W32__
      CloseHandle(handle);
   #endif
}

bool cMutexSem::request(int ms_timeout)
{
   #if defined __ECL_OS2__
      ULONG tmo = ms_timeout >= 0 ? (ULONG)ms_timeout : SEM_INDEFINITE_WAIT;
      APIRET rc = DosRequestMutexSem(handle, tmo);
      __ECL_ASSERT2__(!rc, ("OS/2: Requesting mutex failed, rc = %d", rc));
      return rc == NO_ERROR;
   #elif defined __ECL_W32__
      DWORD tmo = ms_timeout >= 0 ? (DWORD)ms_timeout : INFINITE;
      DWORD rc = WaitForSingleObject(handle, tmo);
      __ECL_ASSERT2__(rc != WAIT_FAILED, ("Win32: Waiting for event failed, rc = %d, err = %d", rc, GetLastError()));
      return rc == WAIT_OBJECT_0;
   #endif
}

void cMutexSem::release()
{
   #if defined __ECL_OS2__
      APIRET rc = DosReleaseMutexSem(handle);
      __ECL_ASSERT2__(!rc, ("OS/2: Releasing mutex failed, rc = %d", rc));
   #elif defined __ECL_W32__
      BOOL ok = ReleaseMutex(handle);
      __ECL_ASSERT2__(ok, ("Win32: Releasing mutex failed, err = %d", GetLastError()));
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEventSem
// ---------------------------------------------------------------------------
//
// Event Semaphore. Event-Status realisiert ueber bool:
//
//    true  - Event gesetzt
//    false - Event rueckgesetzt
//
// cBase
//  +--cOsBase
//      +--cSema
//          +--cEventSem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEventSem : public cSema {

public:
   // Anonymen Event anlegen
   cEventSem(bool init_state = false)
      { openAnonymous(init_state); }
   // Benannten Event oeffnen oder erzeugen (abhaengig von 'mode')
   cEventSem(cString name, OPEN_MODE mode, bool init_state = false)
      { openNamed(name, mode, init_state); }
   // Event freigeben
   ~cEventSem()
      { close(); }

   // Auf Eintreten des Events warten (liefert false bei Timeout oder Fehler)
   // ms_timeout: <0: Unendlich; =0: Sofortige Rueckkehr; >0: Timeout in ms
   bool wait(int ms_timeout = -1) const;

   // Event setzen
   void set();
   // Event ruecksetzen
   void reset();
   // Event setzen und wieder zuruecksetzen
   void pulse();
   // Eventstatus erfragen
   bool query() const;

   // Goodie: Operatoren zur Manipulation der Event-Semaphoren
   operator bool() const
      { return query(); }
   cEventSem& operator=(bool state)
      { if ( state ) set(); else reset();
        return *this; }

private:
   // Anonymen Event oeffnen
   void openAnonymous(bool init_state);
   // Benannten Event oeffnen oder erzeugen (abhaengig von 'mode')
   void openNamed(cString name, OPEN_MODE mode, bool init_state);
   // Event schliessen
   void close();

};

#if defined __ECL_ICC__
   inline void EclDestructElements(const cEventSem **elements, int count)
      { /* no destructor call needed */ }
#endif

#endif /*__INTERFACE__*/


// Implementierung cEventSem
// ===========================================================================

void cEventSem::openAnonymous(bool init_state)
{
   #if defined __ECL_OS2__
      APIRET rc = DosCreateEventSem(NULL, &handle, 0, init_state);
      __ECL_ASSERT2__(!rc, ("OS/2: Creation of event semaphore failed, rc = %d", rc));
   #elif defined __ECL_W32__
      handle = CreateEvent(NULL, TRUE, init_state, NULL);
      __ECL_ASSERT2__(handle.isValid(), ("Win32: Creation of event semaphore failed, err = %d", GetLastError()));
   #endif
}

void cEventSem::openNamed(cString name, OPEN_MODE mode, bool init_state)
{
   if ( name.isEmpty() ) {
      openAnonymous(init_state);
   } else {
      #if defined __ECL_OS2__
         APIRET rc;
         name = "\\sem32\\ecl\\" + name;
         if ( mode == semOpen || mode == semOpenOrCreate )
            rc = DosOpenEventSem(name, &handle);
         if ( rc != NO_ERROR && mode != semOpen )
            rc = DosCreateEventSem(name, &handle, 0, init_state);
         __ECL_ASSERT2__(!rc, ("OS/2: Creation of event semaphore %s failed, rc = %d", (const char *)name, rc));
      #elif defined __ECL_W32__
         name = "/sem/ecl/" + name;
         if ( mode == semOpen || mode == semOpenOrCreate )
            handle = OpenEvent(EVENT_ALL_ACCESS, FALSE, name);
         if ( !handle.isValid() && mode != semOpen )
            handle = CreateEvent(NULL, TRUE, init_state, name);
         __ECL_ASSERT2__(handle.isValid(), ("Win32: Creation of event semaphore %s failed, err = %d", (const char *)name, GetLastError()));
      #endif
   }
}

void cEventSem::close()
{
   #if defined __ECL_OS2__
      DosCloseEventSem(handle);
   #elif defined __ECL_W32__
      CloseHandle(handle);
   #endif
}

bool cEventSem::wait(int ms_timeout) const
{
   #if defined __ECL_OS2__
      ULONG tmo = ms_timeout >= 0 ? (ULONG)ms_timeout : SEM_INDEFINITE_WAIT;
      APIRET rc = DosWaitEventSem(handle, tmo);
      __ECL_ASSERT2__(!rc, ("OS/2: Waiting for event failed, rc = %d", rc));
      return rc == NO_ERROR;
   #elif defined __ECL_W32__
      DWORD tmo = ms_timeout >= 0 ? (DWORD)ms_timeout : INFINITE;
      DWORD rc = WaitForSingleObject(handle, tmo);
      __ECL_ASSERT2__(rc != WAIT_FAILED, ("Win32: Waiting for event failed, err = %d", GetLastError()));
      return rc == WAIT_OBJECT_0;
   #endif
}

void cEventSem::set()
{
   #if defined __ECL_OS2__
      APIRET rc = DosPostEventSem(handle);
      if ( rc == ERROR_ALREADY_POSTED ) return;
      __ECL_ASSERT2__(!rc, ("OS/2: Set event failed, rc = %d", rc));
   #elif defined __ECL_W32__
      BOOL ok = SetEvent(handle);
      __ECL_ASSERT2__(ok, ("Win32: Set event failed, err = %d", GetLastError()));
   #endif
}

void cEventSem::reset()
{
   #if defined __ECL_OS2__
      ULONG post_count;
      APIRET rc = DosResetEventSem(handle, &post_count);
      if ( rc == ERROR_ALREADY_RESET ) return;
      __ECL_ASSERT2__(!rc, ("OS/2: Reset event failed, rc = %d", rc));
   #elif defined __ECL_W32__
      BOOL ok = ResetEvent(handle);
      __ECL_ASSERT2__(ok, ("Win32: Reset event failed, err = %d", GetLastError()));
   #endif
}

void cEventSem::pulse()
{
   #if defined __ECL_W32__
      BOOL ok = PulseEvent(handle);
      __ECL_ASSERT2__(ok, ("Win32: Pulse event failed, err = %d", GetLastError()));
   #else
      set();
      reset();
   #endif
}

bool cEventSem::query() const
{
   #if defined __ECL_OS2__
      ULONG post_count;
      APIRET rc = DosQueryEventSem(handle, &post_count);
      __ECL_ASSERT2__(!rc, ("OS/2: Reset event failed, rc = %d", rc));
      return post_count != 0;
   #elif defined __ECL_W32__
      DWORD rc = WaitForSingleObject(handle, 0);
      __ECL_ASSERT2__(rc != WAIT_FAILED, ("Win32: Query event failed, err = %d", GetLastError()));
      return rc == WAIT_OBJECT_0;
   #endif
}



#ifdef __INTERFACE__

// ===========================================================================
// Definition cMuxEventSem
// ---------------------------------------------------------------------------
//
// Multiple Event Semaphores.
//
// cBase
//  +--cOsBase
//      +--cMuxEventSem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMuxEventSem : public cOsBase {

public:
   // Leere cMuxEventSem konstruieren
   cMuxEventSem()
      { }
   // cMuxEventSem mit einem Event konstruieren
   cMuxEventSem(const cEventSem& event)
      { addEvent(event); }
   // cMuxEventSem aus einem anderen konstruieren
   cMuxEventSem(const cMuxEventSem& other)
      { setEvents(other); }
   // cMuxEventSem freigeben
   ~cMuxEventSem()
      { }

   // Event-Semaphore setzen (bisherigen Inhalt loeschen)
   cMuxEventSem& setEvent(const cEventSem& event);
   // Event-Semaphore hinzufuegen
   cMuxEventSem& addEvent(const cEventSem& event);
   // cMuxEventSem setzen (bisherigen Inhalt loeschen)
   cMuxEventSem& setEvents(const cMuxEventSem& other);
   // cMuxEventSem hinzufuegen
   cMuxEventSem& addEvents(const cMuxEventSem& other);

   // Auf Eintreten von Events warten (liefert false bei Timeout oder Fehler)
   // wait_for_all: Bei true alle, bei false mindestens ein Event signalisiert
   // ms_timeout: <0: Unendlich; =0: Sofortige Rueckkehr; >0: Timeout in ms
   bool wait(int ms_timeout = -1, bool wait_for_all = false);

   // Auf Eintreten aller Events warten
   bool waitForAll(int ms_timeout = -1)
      { return wait(ms_timeout, true); }
   // Auf Eintreten mindestens eines Events warten
   bool waitForOne(int ms_timeout = -1)
      { return wait(ms_timeout, false); }

   // Zuweisung einer einzelnen Event-Semaphoren
   cMuxEventSem& operator=(const cEventSem& event)
      { return setEvent(event); }
   // Zuweisung einer anderen cMuxEventSem
   cMuxEventSem& operator=(const cMuxEventSem& other)
      { return setEvents(other); }

   // Konkatenation von Event-Semaphoren mit cMuxEventSem-Objekten
   inline friend cMuxEventSem operator+(const cEventSem& s1, const cEventSem& s2)
      { return cMuxEventSem(s1).addEvent(s2); }
   inline friend cMuxEventSem operator+(const cEventSem& s1, const cMuxEventSem& ms2)
      { return cMuxEventSem(s1).addEvents(ms2); }
   inline friend cMuxEventSem operator+(const cMuxEventSem& ms1, const cEventSem& s2)
      { return cMuxEventSem(ms1).addEvent(s2); }
   inline friend cMuxEventSem operator+(const cMuxEventSem& ms1, const cMuxEventSem& ms2)
      { return cMuxEventSem(ms1).addEvents(ms2); }

   // Hinzufuegen einer einzelnen Event-Semaphoren
   cMuxEventSem& operator+=(const cEventSem& event)
      { return addEvent(event); }
   // Hinzufuegen einer anderen cMuxEventSem
   cMuxEventSem& operator+=(const cMuxEventSem& other)
      { return addEvents(other); }

private:
   #if defined __ECL_VCPP__
      typedef class __ECL_DLLEXPORT__ cList<const cEventSem*, const cEventSem*> SEMP_LIST;
   #else
      typedef cList<const cEventSem*, const cEventSem*> SEMP_LIST;
   #endif
   SEMP_LIST semp_list;

};

#endif /*__INTERFACE__*/


// Implementierung cMuxEventSem
// ===========================================================================

cMuxEventSem& cMuxEventSem::setEvent(const cEventSem& event)
{
   semp_list.removeAll();
   semp_list.addTail(&event);
   return *this;
}

cMuxEventSem& cMuxEventSem::setEvents(const cMuxEventSem& other)
{
   semp_list.removeAll();
   for ( IPOSITION it = other.semp_list.getHeadPosition() ; it != NULL ; )
      semp_list.addTail(other.semp_list.getNext(it));
   return *this;
}

cMuxEventSem& cMuxEventSem::addEvent(const cEventSem& event)
{
   for ( IPOSITION it = semp_list.getHeadPosition() ; it != NULL ; ) {
      const cEventSem *ev = semp_list.getNext(it);
      if ( ev == &event )
         return *this;
   }

   semp_list.addTail(&event);
   return *this;
}

cMuxEventSem& cMuxEventSem::addEvents(const cMuxEventSem& other)
{
   for ( IPOSITION it = other.semp_list.getHeadPosition() ; it != NULL ; )
      semp_list.addTail(other.semp_list.getNext(it));
   return *this;
}

bool cMuxEventSem::wait(int ms_timeout, bool wait_for_all)
{
   int count = semp_list.getCount();
   if ( count < 1 )
      return true;

   #if defined __ECL_OS2__
      SEMRECORD *semrecs = new0 SEMRECORD[count];
      IPOSITION it = semp_list.getHeadPosition();
      for ( int i = 0 ; it != NULL ; i++ ) {
         const cEventSem *ev = semp_list.getNext(it);
         semrecs[i].hsemCur = (HSEM)(unsigned long)getHandleFrom(*ev);
         semrecs[i].ulUser = i;
      }
      ULONG tmo = ms_timeout >= 0 ? (ULONG)ms_timeout : SEM_INDEFINITE_WAIT;
      ULONG attrs = wait_for_all ? DCMW_WAIT_ALL : DCMW_WAIT_ANY;
      APIRET rc = DosCreateMuxWaitSem(NULL, &handle, count, semrecs, attrs);
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
      for ( int i = 0 ; it != NULL ; i++ ) {
         const cEventSem *ev = semp_list.getNext(it);
         handles[i] = getHandleFrom(*ev);
      }
      DWORD tmo = ms_timeout >= 0 ? (DWORD)ms_timeout : INFINITE;
      DWORD rc = WaitForMultipleObjects(count, handles, wait_for_all, tmo);
      __ECL_ASSERT2__(rc != WAIT_FAILED, ("Win32: Waiting for events failed, err = %d", GetLastError()));
      delete[] handles; // -TE- 02.03.2001 delete -> delete[]
      return rc == WAIT_OBJECT_0;
   #endif
}




#ifdef __Test_eb_sema__

   #include <iostream.h>
   #include "base/eb_thread.hpp"

   cEventSem ev1, ev2;

   class cThread2 : public cThread {
   public:
      int onMain(void *)
      {
         while ( 1 ) {
            cerr << "-2";
            sleep(500);
            ev1.reset();
            ev2.set();
            ev1.wait();
         }
      }
   };

   class cThreadM : public cThread {
   public:
      cThreadM() : cThread(0, NULL) { }
      int onMain(void *)
      {
         while ( 1 ) {
            cerr << "-1";
            sleep(1000);
            ev2 = false;
            ev1 = true;
            ev2.wait();
         }
      }
   };

   int main()
   {
      cThread2 t2; t2.start();
      cThreadM tm; tm.start();
      return 0;
   }

#endif

