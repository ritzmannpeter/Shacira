// ===========================================================================
// base/semaphore.h                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                              /_____
//! @file  base/semaphore.h
//! @brief Semaphore classes
// 
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cSema             - Basisklasse fuer Semaphoren.
//     |
//     +-cMutexSem      - Mutual Exclusive Semaphore.
//     |
//     +-cEventSem      - Event Semaphore.
//
//    cMuxEventSem      - Multiple Event Semaphore.
//
// ===========================================================================

#ifndef __semaphore__
#define __semaphore__


// Base class header
#include "base/base.h"
#include "base/osbase.h" // for ugly workaround

// Other ECL headers
#include "base/string.h"
#include "base/list.h"


namespace ecl {


// ===========================================================================
// Definition cSema
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Semaphoren
//
// ===========================================================================

class __ECL_DLLEXPORT__ cSema 
{
public:
   enum OPEN_MODE {
      semCreate,        // Semaphore erzeugen
      semOpen,          // Semaphore oeffnen (Verbindung herstellen)
      semOpenOrCreate   // Semaphore oeffnen (Erzeugen, falls nicht vorhanden)
   };

};


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
// ===========================================================================

class __ECL_DLLEXPORT__ cMutexSem : public cSema 
{
public:
   //! Anonyme Mutex anlegen
   cMutexSem(bool init_state = false);
   //! Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   cMutexSem(const cString &name, OPEN_MODE mode, bool init_state = false);
   //! Mutex freigeben
   ~cMutexSem();

   //! Mutex anfordern (liefert false bei Timeout oder Fehler)
   //! ms_timeout: <0: Unendlich; =0: Sofortige Rueckkehr; >0: Timeout in ms
   bool _request(int ms_timeout = -1);
   //! Mutex freigeben
   void release();

   // Preliminary (um die echte Timeout-Variante einzugrenzen)
   bool tryRequest();
   bool request();
   bool request(unsigned int ms_timeout);

private:
   // Copying is not allowed!
   cMutexSem(const cMutexSem &other);
   cMutexSem &operator=(const cMutexSem &other);

   // Anonyme Mutex oeffnen
   void openAnonymous(bool init_state);
   // Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   void openNamed(const cString &name, OPEN_MODE mode, bool init_state);
   // Mutex schliessen
   void close();

public:
   // Spezielle Implementierungen
   class iPrivate;
   iPrivate *_p;
};


// ===========================================================================
// Definition cMutexNull
// ---------------------------------------------------------------------------
//
// Mutual exclusive Semaphore die in Wirklichkeit keine ist (funktionslos).
//
// Anmerkung: die Variablen in den Dummy-Implementierungen dienen nur dazu,
// im Visual Studio "warning C4100:Unreferenzierter formaler Parameter"
// zu verhindern. Igitt.
//
// Autor: Markus Wuertz :-)
// ===========================================================================

class cMutexNull {

public:
   // Anonyme Mutex anlegen
   inline cMutexNull(bool init_state = false) { init_state; }
   // Benannte Mutex oeffnen oder erzeugen (abhaengig von 'mode')
   inline cMutexNull(const cString &name, cSema::OPEN_MODE mode, bool init_state = false) { name; mode; init_state; }

   // Mutex anfordern (liefert false bei Timeout oder Fehler)
   inline bool _request(int ms_timeout = -1) { ms_timeout; return true; }
   
   inline bool tryRequest() { return true; }
   inline bool request() { return true; }
   inline bool request(unsigned int ms_timeout) { ms_timeout; return true; }
   
   // Mutex freigeben
   inline void release() { }

};


// ===========================================================================
// Definition cMutexGuard
// ---------------------------------------------------------------------------
//
// Guard-Klasse mit Mutual exclusive Semaphore. Im Konstruktor wird die
// per Referenz uebergebene cMutexSem belegt, im Destruktor automatisch
// freigegeben.
//
// cMutexGuard
//
// Autor: Markus Wuertz :-)
// ===========================================================================

class __ECL_DLLEXPORT__ cMutexGuard {
public:
   // Konstruktor / Destruktor
   cMutexGuard(cMutexSem &mutex) : _mutex(mutex) { _mutex.request(); };
   ~cMutexGuard() { _mutex.release(); };

private: 
   // Kopieren verboten!
   cMutexGuard(const cMutexGuard &rhs);
   cMutexGuard &operator=(const cMutexGuard &rhs);

   // Mutexobjekt
   cMutexSem &_mutex;
};


// ===========================================================================
// Definition cEventSem
// ---------------------------------------------------------------------------
//
// Event Semaphore. Event-Status realisiert ueber bool:
//
//    true  - Event gesetzt
//    false - Event rueckgesetzt
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEventSem : public cSema {

public:
   // Anonymen Event anlegen
   cEventSem(bool init_state = false);
   // Benannten Event oeffnen oder erzeugen (abhaengig von 'mode')
   cEventSem(const cString &name, OPEN_MODE mode, bool init_state = false);
   // Event freigeben
   ~cEventSem();

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

   // TBD: Haesslicher Workaround / ugly workaround :-(
   // (Wird intern von cMuxEventSem benoetigt)
   const cOsBase::cOsHandle getHandle() const;

private:
   // Copying is not allowed!
   cEventSem(const cEventSem &other);
   cEventSem &operator=(const cEventSem &other);

   // Anonymen Event oeffnen
   void openAnonymous(bool init_state);
   // Benannten Event oeffnen oder erzeugen (abhaengig von 'mode')
   void openNamed(const cString &name, OPEN_MODE mode, bool init_state);
   // Event schliessen
   void close();

   // Spezielle Implementierungen
   class iPrivate;
   iPrivate *_p;

};

#if defined __ECL_ICC__
   inline void EclDestructElements(const cEventSem **elements, int count)
      { /* no destructor call needed */ }
#endif


// ===========================================================================
// Definition cMuxEventSem
// ---------------------------------------------------------------------------
//
// Multiple Event Semaphores.
//
// ===========================================================================

class __ECL_DLLEXPORT__ cMuxEventSem {

public:
   // Leere cMuxEventSem konstruieren
   cMuxEventSem();
   // cMuxEventSem mit einem Event konstruieren
   cMuxEventSem(const cEventSem& event);
   // cMuxEventSem aus einem anderen konstruieren
   cMuxEventSem(const cMuxEventSem& other);
   // cMuxEventSem freigeben
   // ~cMuxEventSem();

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

   // Spezielle Implementierungen
   //class iPrivate;
   //iPrivate *_p;

};

}; // namespace ecl


#endif // __semaphore__

