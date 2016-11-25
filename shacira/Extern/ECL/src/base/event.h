// ===========================================================================
// base/event.h                                                 ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//   cEclObject
//    |
//    +--cEvent     - ECL-Objekt mit Faehigkeit zum Empfangen
//                    und Erzeugen von Events
//
// ===========================================================================

#ifndef __ecl_event__
#define __ecl_event__


// Other ECL headers
#include "base/object.h"

 
namespace ecl {


// ===========================================================================
// Definition cEvent
// ---------------------------------------------------------------------------
//
//! Erzeuger von Events muessen von dieser Klasse abgeleitet werden.
//! @ingroup event
//
// cEclObject
//  +--cEvent
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEvent : public cEclObject {
    ECL_DECLARE(cEvent,cEclObject)

public:

   //! Konstruktor
   cEvent() { event_map = 0; }
   //! Copy-Konstruktor
   cEvent(const cEvent&) { event_map = 0; }
   //! Zuweisungsoperator
   cEvent& operator=(const cEvent&) { return *this; }
   //! Destruktor
   virtual ~cEvent();


   //! Definition von Event-IDs
   enum EVENTS {
      evtDestructingSource = -1, //!< (EVFUNC_P) cEvent wird geloescht
      evtUser              = 0   //!< Ab hier: Benutzerdefinierte Events
   };


   //! @name Typen von Event-Funktionen
   // =================================

   //! Definition aller Typen von Event-Funktionen
   enum EVFUNC_TYPE {
      evUndef,       //!< Undefinierte Funktion
      evFuncVoid,    //!< void-Funktion ohne Parameter
      evFuncP,       //!< void-Funktion mit einem Zeiger-Parameter
      evFuncPP,      //!< void-Funktion mit zwei Zeiger-Parametern
      evFuncPI,      //!< void-Funktion mit Zeiger- und Integer-Parameter
      evFuncI,       //!< void-Funktion mit einem Integer-Parameter
      evFuncII,      //!< void-Funktion mit zwei Integer-Parametern
      evFuncRVoid,   //!< int-Funktion ohne Parameter
      evFuncRP,      //!< int-Funktion mit einem Zeiger-Parameter
      evFuncRPP,     //!< int-Funktion mit zwei Zeiger-Parametern
      evFuncRPI,     //!< int-Funktion mit Zeiger- und Integer-Parameter
      evFuncRI,      //!< int-Funktion mit einem Integer-Parameter
      evFuncRII,     //!< int-Funktion mit zwei Integer-Parametern
   };


   //! @name Prototypen fuer Event-Funktionen
   //  ======================================

   //! void-Funktion ohne Parameter
   typedef void (cEvent::*EVFUNC)();
   //! void-Funktion mit einem Zeiger-Parameter
   typedef void (cEvent::*EVFUNC_P)(void *);
   //! void-Funktion mit zwei Zeiger-Parametern
   typedef void (cEvent::*EVFUNC_PP)(void *, void *);
   //! void-Funktion mit Zeiger- und Integer-Parameter
   typedef void (cEvent::*EVFUNC_PI)(void *, int);
   //! void-Funktion mit einem Integer-Parameter
   typedef void (cEvent::*EVFUNC_I)(int);
   //! void-Funktion mit zwei Integer-Parametern
   typedef void (cEvent::*EVFUNC_II)(int, int);

   //! int-Funktion ohne Parameter
   typedef int (cEvent::*EVFUNC_R)();
   //! int-Funktion mit einem Zeiger-Parameter
   typedef int (cEvent::*EVFUNC_RP)(void *);
   //! int-Funktion mit zwei Zeiger-Parametern
   typedef int (cEvent::*EVFUNC_RPP)(void *, void *);
   //! int-Funktion mit Zeiger- und Integer-Parameter
   typedef int (cEvent::*EVFUNC_RPI)(void *, int);
   //! int-Funktion mit einem Integer-Parameter
   typedef int (cEvent::*EVFUNC_RI)(int);
   //! int-Funktion mit zwei Integer-Parametern
   typedef int (cEvent::*EVFUNC_RII)(int, int);

   //! Allgemeiner Prototyp (konvertierbar zu den obigen Prototypen)
   typedef EVFUNC EVFUNC_PTR;


   // Allgemeiner Event
   // =================

   //! Allgemeiner Event.
   //! @ingroup event
   //!
   //! @note WICHTIG: Die Konvertierung der Zielobjekte zu cEvent MUSS
   //! ueber einen void* geschehen, da ansonsten bei mehrfach abgeleiteten
   //! Klassen ein korrigierter (und damit falscher) Objektzeiger gespeichert
   //! wird. (Der Parameter 'void *o' in den EVENT-Konstruktoren reicht aus.)

   struct __ECL_DLLEXPORT__ EVENT {
      friend class cEvent;

      EVENT()
         { obj = 0; func = 0; type = evUndef; }

      EVENT(void *o, EVFUNC f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncVoid; }
      EVENT(void *o, EVFUNC_P f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncP; }
      EVENT(void *o, EVFUNC_PP f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncPP; }
      EVENT(void *o, EVFUNC_PI f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncPI; }
      EVENT(void *o, EVFUNC_I f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncI; }
      EVENT(void *o, EVFUNC_II f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncII; }

      EVENT(void *o, EVFUNC_R f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncRVoid; }
      EVENT(void *o, EVFUNC_RP f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncRP; }
      EVENT(void *o, EVFUNC_RPP f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncRPP; }
      EVENT(void *o, EVFUNC_RPI f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncRPI; }
      EVENT(void *o, EVFUNC_RI f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncRI; }
      EVENT(void *o, EVFUNC_RII f)
         { obj = (cEvent*)o; func = (EVFUNC_PTR)f; type = evFuncRII; }

   private:

      EVFUNC_TYPE type;          //!< Typ der Eventfunktion
      EVFUNC_PTR func;           //!< Zeiger auf Memberfunktion
      cEvent *obj;         //!< Zeiger auf Target-Objekt

   };


   //! @name Eventfunktion registrieren
   //  ================================

   //! void-Eventfunktion ohne Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC func);
   //! void-Eventfunktion mit einem Zeiger-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_P func);
   //! void-Eventfunktion mit zwei Zeiger-Parametern registrieren
   void addEvent(int event_id, void *obj, EVFUNC_PP func);
   //! void-Eventfunktion mit Zeiger- und Integer-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_PI func);
   //! void-Eventfunktion mit Integer-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_I func);
   //! void-Eventfunktion mit zwei Integer-Parametern registrieren
   void addEvent(int event_id, void *obj, EVFUNC_II func);


   //! @name Eventfunktion deregistrieren
   //  ==================================

   //! Alle Eventfunktionen zu einem Event deregistrieren
   void removeEvent(int event_id);
   //! Alle Eventfunktionen eines Targets zu einem Event deregistrieren
   void removeEvent(int event_id, void *obj);
   //! Alle Eventfunktionen eines Targets deregistrieren
   void removeEvent(void *obj);


   //! @name Eventfunktion fuer nicht registrierte Events aufrufen
   //  ===========================================================

   //! void-Eventfunktion ohne Parameter aufrufen
   static void callEvent(const EVENT& event);
   //! void-Eventfunktion mit einem Zeiger-Parameter aufrufen
   static void callEvent(const EVENT& event, void *p1);
   //! void-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   static void callEvent(const EVENT& event, void *p1, void *p2);
   //! void-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   static void callEvent(const EVENT& event, void *p1, int p2);
   //! void-Eventfunktion mit Integer-Parameter aufrufen
   static void callEvent(const EVENT& event, int p1);
   //! void-Eventfunktion mit zwei Integer-Parametern aufrufen
   static void callEvent(const EVENT& event, int p1, int p2);

   //! int-Eventfunktion ohne Parameter aufrufen
   static int callEventR(const EVENT& event);
   //! int-Eventfunktion mit einem Zeiger-Parameter aufrufen
   static int callEventR(const EVENT& event, void *p1);
   //! int-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   static int callEventR(const EVENT& event, void *p1, void *p2);
   //! int-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   static int callEventR(const EVENT& event, void *p1, int p2);
   //! int-Eventfunktion mit Integer-Parameter aufrufen
   static int callEventR(const EVENT& event, int p1);
   //! int-Eventfunktion mit zwei Integer-Parametern aufrufen
   static int callEventR(const EVENT& event, int p1, int p2);


protected:

   //! @name Eventfunktion fuer registrierte Events aufrufen
   //  =====================================================

   //! void-Eventfunktion ohne Parameter aufrufen
   void callEvent(int event_id);
   //! void-Eventfunktion mit einem Zeiger-Parameter aufrufen
   void callEvent(int event_id, void *p1);
   //! void-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   void callEvent(int event_id, void *p1, void *p2);
   //! void-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   void callEvent(int event_id, void *p1, int p2);
   //! void-Eventfunktion mit Integer-Parameter aufrufen
   void callEvent(int event_id, int p1);
   //! void-Eventfunktion mit zwei Integer-Parametern aufrufen
   void callEvent(int event_id, int p1, int p2);


private:

   void * event_map;

   //! Pruefen eines unregistrierten Events
   static bool checkEvent(const EVENT& event, EVFUNC_TYPE type);
   //! Pruefen eines registrierten Events
   bool checkEvent(int event_id, EVFUNC_TYPE type, const EVENT& event) const;
   //! Suchen der Event-Liste zu einem Event
   void *findEventList(int event_id) const;
   //! Registrieren einer Eventfunktion zu einem Event
   void addEvent(int event_id, void *obj, EVFUNC func, EVFUNC_TYPE type);

};


}; // namespace ecl


#endif // __ecl_event__

