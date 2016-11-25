// ===========================================================================
// eb_event.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEventTarget         - Empfaenger von Events
//     |
//     +-cEventSource      - Erzeuger von Events
//
// ===========================================================================

#include "base/eb_event.hpp"
#include "base/eb_map.hpp"
#include "base/eb_list.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"

#endif /*__INTERFACE__*/




// Lokale Variablen
// ===========================================================================

static const char * EvFuncType[] = {
   "evUndef",
   "evFunc",  "evFuncP",  "evFuncPP",  "evFuncPI",  "evFuncI",  "evFuncII",
   "evFuncR", "evFuncRP", "evFuncRPP", "evFuncRPI", "evFuncRI", "evFuncRII"
};




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEventTarget
// ---------------------------------------------------------------------------
//
// Empfaenger von Events muessen von dieser Klasse abgeleitet werden.
//
// cEventTarget
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEventTarget {

public:

   // Typen von Event-Funktionen
   // ==========================

   // Definition aller Typen von Event-Funktionen
   enum EVFUNC_TYPE {
      evUndef,       // Undefinierte Funktion
      evFunc,        // void-Funktion ohne Parameter
      evFuncP,       // void-Funktion mit einem Zeiger-Parameter
      evFuncPP,      // void-Funktion mit zwei Zeiger-Parametern
      evFuncPI,      // void-Funktion mit Zeiger- und Integer-Parameter
      evFuncI,       // void-Funktion mit einem Integer-Parameter
      evFuncII,      // void-Funktion mit zwei Integer-Parametern
      evFuncR,       // int-Funktion ohne Parameter
      evFuncRP,      // int-Funktion mit einem Zeiger-Parameter
      evFuncRPP,     // int-Funktion mit zwei Zeiger-Parametern
      evFuncRPI,     // int-Funktion mit Zeiger- und Integer-Parameter
      evFuncRI,      // int-Funktion mit einem Integer-Parameter
      evFuncRII,     // int-Funktion mit zwei Integer-Parametern
   };


   // Prototypen fuer Event-Funktionen
   // ================================

   // void-Funktion ohne Parameter
   typedef void (cEventTarget::*EVFUNC)();
   // void-Funktion mit einem Zeiger-Parameter
   typedef void (cEventTarget::*EVFUNC_P)(void *);
   // void-Funktion mit zwei Zeiger-Parametern
   typedef void (cEventTarget::*EVFUNC_PP)(void *, void *);
   // void-Funktion mit Zeiger- und Integer-Parameter
   typedef void (cEventTarget::*EVFUNC_PI)(void *, int);
   // void-Funktion mit einem Integer-Parameter
   typedef void (cEventTarget::*EVFUNC_I)(int);
   // void-Funktion mit zwei Integer-Parametern
   typedef void (cEventTarget::*EVFUNC_II)(int, int);

   // int-Funktion ohne Parameter
   typedef int (cEventTarget::*EVFUNC_R)();
   // int-Funktion mit einem Zeiger-Parameter
   typedef int (cEventTarget::*EVFUNC_RP)(void *);
   // int-Funktion mit zwei Zeiger-Parametern
   typedef int (cEventTarget::*EVFUNC_RPP)(void *, void *);
   // int-Funktion mit Zeiger- und Integer-Parameter
   typedef int (cEventTarget::*EVFUNC_RPI)(void *, int);
   // int-Funktion mit einem Integer-Parameter
   typedef int (cEventTarget::*EVFUNC_RI)(int);
   // int-Funktion mit zwei Integer-Parametern
   typedef int (cEventTarget::*EVFUNC_RII)(int, int);

   // Allgemeiner Prototyp (konvertierbar zu den obigen Prototypen)
   typedef EVFUNC EVFUNC_PTR;


   // Allgemeiner Event
   // =================

   struct __ECL_DLLEXPORT__ EVENT {
      friend class cEventSource;

      EVENT()
         { obj = 0; func = 0; type = evUndef; }

      // WICHTIG: Die Konvertierung der Zielobjekte zu cEventTarget MUSS
      // ueber einen void* geschehen, da ansonsten bei mehrfach abgeleiteten
      // Klassen ein korrigierter (und damit falscher) Objektzeiger gespeichert
      // wird. (Der Parameter 'void *o' in den EVENT-Konstruktoren reicht aus.)

      EVENT(void *o, EVFUNC f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFunc; }
      EVENT(void *o, EVFUNC_P f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncP; }
      EVENT(void *o, EVFUNC_PP f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncPP; }
      EVENT(void *o, EVFUNC_PI f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncPI; }
      EVENT(void *o, EVFUNC_I f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncI; }
      EVENT(void *o, EVFUNC_II f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncII; }

      EVENT(void *o, EVFUNC_R f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncR; }
      EVENT(void *o, EVFUNC_RP f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncRP; }
      EVENT(void *o, EVFUNC_RPP f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncRPP; }
      EVENT(void *o, EVFUNC_RPI f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncRPI; }
      EVENT(void *o, EVFUNC_RI f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncRI; }
      EVENT(void *o, EVFUNC_RII f)
         { obj = (cEventTarget*)o; func = (EVFUNC_PTR)f; type = evFuncRII; }

   private:

      EVFUNC_TYPE type;          // Typ der Eventfunktion
      EVFUNC_PTR func;         // Zeiger auf Memberfunktion
      cEventTarget *obj;         // Zeiger auf Target-Objekt

   };

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cEventSource
// ---------------------------------------------------------------------------
//
// Erzeuger von Events muessen von dieser Klasse abgeleitet werden.
//
// cEventTarget
//  +--cEventSource
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEventSource : public cEventTarget {

public:

   // Konstruktor
   cEventSource() { event_map = 0; }
   // Copy-Konstruktor
   cEventSource(const cEventSource&) { event_map = 0; }
   // Zuweisungsoperator
   cEventSource& operator=(const cEventSource&) { return *this; }
   // Destruktor
   virtual ~cEventSource();

   // Definition von Event-IDs
   enum EVENTS {
      evtDestructingSource = -1, // (EVFUNC_P) cEventSource wird geloescht
      evtUser              = 0   // Ab hier: Benutzerdefinierte Events
   };

   // Eventfunktion registrieren
   // ==========================

   // void-Eventfunktion ohne Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC func);
   // void-Eventfunktion mit einem Zeiger-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_P func);
   // void-Eventfunktion mit zwei Zeiger-Parametern registrieren
   void addEvent(int event_id, void *obj, EVFUNC_PP func);
   // void-Eventfunktion mit Zeiger- und Integer-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_PI func);
   // void-Eventfunktion mit Integer-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_I func);
   // void-Eventfunktion mit zwei Integer-Parametern registrieren
   void addEvent(int event_id, void *obj, EVFUNC_II func);

/*
   // int-Eventfunktion ohne Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_R func);
   // int-Eventfunktion mit einem Zeiger-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_RP func);
   // int-Eventfunktion mit zwei Zeiger-Parametern registrieren
   void addEvent(int event_id, void *obj, EVFUNC_RPP func);
   // int-Eventfunktion mit Zeiger- und Integer-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_RPI func);
   // int-Eventfunktion mit Integer-Parameter registrieren
   void addEvent(int event_id, void *obj, EVFUNC_RI func);
   // int-Eventfunktion mit zwei Integer-Parametern registrieren
   void addEvent(int event_id, void *obj, EVFUNC_RII func);
*/


   // Eventfunktion deregistrieren
   // ============================

   // Alle Eventfunktionen zu einem Event deregistrieren
   void removeEvent(int event_id);
   // Alle Eventfunktionen eines Targets zu einem Event deregistrieren
   void removeEvent(int event_id, void *obj);
   // Alle Eventfunktionen eines Targets deregistrieren
   void removeEvent(void *obj);


   // Eventfunktion fuer nicht registrierte Events aufrufen
   // =====================================================

   // void-Eventfunktion ohne Parameter aufrufen
   static void callEvent(const EVENT& event);
   // void-Eventfunktion mit einem Zeiger-Parameter aufrufen
   static void callEvent(const EVENT& event, void *p1);
   // void-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   static void callEvent(const EVENT& event, void *p1, void *p2);
   // void-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   static void callEvent(const EVENT& event, void *p1, int p2);
   // void-Eventfunktion mit Integer-Parameter aufrufen
   static void callEvent(const EVENT& event, int p1);
   // void-Eventfunktion mit zwei Integer-Parametern aufrufen
   static void callEvent(const EVENT& event, int p1, int p2);

   // int-Eventfunktion ohne Parameter aufrufen
   static int callEventR(const EVENT& event);
   // int-Eventfunktion mit einem Zeiger-Parameter aufrufen
   static int callEventR(const EVENT& event, void *p1);
   // int-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   static int callEventR(const EVENT& event, void *p1, void *p2);
   // int-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   static int callEventR(const EVENT& event, void *p1, int p2);
   // int-Eventfunktion mit Integer-Parameter aufrufen
   static int callEventR(const EVENT& event, int p1);
   // int-Eventfunktion mit zwei Integer-Parametern aufrufen
   static int callEventR(const EVENT& event, int p1, int p2);


protected:

   // Eventfunktion fuer registrierte Events aufrufen
   // ===============================================

   // void-Eventfunktion ohne Parameter aufrufen
   void callEvent(int event_id);
   // void-Eventfunktion mit einem Zeiger-Parameter aufrufen
   void callEvent(int event_id, void *p1);
   // void-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   void callEvent(int event_id, void *p1, void *p2);
   // void-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   void callEvent(int event_id, void *p1, int p2);
   // void-Eventfunktion mit Integer-Parameter aufrufen
   void callEvent(int event_id, int p1);
   // void-Eventfunktion mit zwei Integer-Parametern aufrufen
   void callEvent(int event_id, int p1, int p2);

/*
   // void-Eventfunktion ohne Parameter aufrufen
   int callEventR(int event_id);
   // void-Eventfunktion mit einem Zeiger-Parameter aufrufen
   int callEventR(int event_id, void *p1);
   // void-Eventfunktion mit zwei Zeiger-Parametern aufrufen
   int callEventR(int event_id, void *p1, void *p2);
   // void-Eventfunktion mit Zeiger- und Integer-Parameter aufrufen
   int callEventR(int event_id, void *p1, int p2);
   // void-Eventfunktion mit Integer-Parameter aufrufen
   int callEventR(int event_id, int p1);
   // void-Eventfunktion mit zwei Integer-Parametern aufrufen
   int callEventR(int event_id, int p1, int p2);
*/

private:

   void * event_map;

   // Pruefen eines unregistrierten Events
   static bool checkEvent(const EVENT& event, EVFUNC_TYPE type);
   // Pruefen eines registrierten Events
   bool checkEvent(int event_id, EVFUNC_TYPE type, const EVENT& event) const;
   // Suchen der Event-Liste zu einem Event
   void *findEventList(int event_id) const;
   // Registrieren einer Eventfunktion zu einem Event
   void addEvent(int event_id, void *obj, EVFUNC func, EVFUNC_TYPE type);

};

#endif /*__INTERFACE__*/


// Implementierung cEventSource
// ===========================================================================

// Struktur eines Eintrags in die Event-Liste

// Typ def Event-Liste (LIST aus Event-Eintraegen)
typedef class cList<cEventSource::EVENT,const cEventSource::EVENT&> EVENT_LIST;
// Typ def Event-Map (MAP aus Event-Listen)
typedef class cMap<int,int,EVENT_LIST*,EVENT_LIST*> EVENT_MAP;


// Konstruktor, Destruktor
// =======================

cEventSource::~cEventSource()
{
   // Benachrichtigen aller interessierter Klassen, dass das
   // cEventSource-Objekt in Kuerze verschwindet

   callEvent(evtDestructingSource, this);

   // Anschliessend kann's ans Eingemachte gehen: Hau wech...

   EVENT_MAP *ev_map = (EVENT_MAP*)event_map;

   if ( ev_map != 0 ) {
      for ( IPOSITION pos = ev_map->getStartPosition() ; pos != 0 ; ) {
         EVENT_LIST *ev_list; int ev_id;
         ev_map->getNextAssoc(pos, ev_id, ev_list);
         delete ev_list;
      }
      delete ev_map;
   }
}


// Nicht registrierte Eventfunktion aufrufen
// =========================================

bool cEventSource::checkEvent(const EVENT& event, EVFUNC_TYPE type)
{
   if ( event.func == 0 || event.obj == 0 ) {
      // Keine Fehlermeldung, da voellig legaler Zustand...
      // cBase::DbgError(
      //    "EVENT: Cannot call unregistered event, because no value(s) for func and/or obj were given");
      return false;
   }

   if ( event.type != type ) {
      __ECL_ASSERT2__(0,
         ("EVENT: Cannot call unregistered event with type '%s', because it's defined with type '%s'",
         EvFuncType[type], EvFuncType[event.type]));
      return false;
   }

   return true;
}

// Aufrufen der void-Eventfunktionen
void cEventSource::callEvent(const EVENT& event)
{
   if ( checkEvent(event, evFunc) )
        (event.obj->*(EVFUNC)event.func)();
}
void cEventSource::callEvent(const EVENT& event, void *p1)
{
   if ( checkEvent(event, evFuncP) )
        (event.obj->*(EVFUNC_P)event.func)(p1);
}
void cEventSource::callEvent(const EVENT& event, void *p1, void *p2)
{
   if ( checkEvent(event, evFuncPP) )
        (event.obj->*(EVFUNC_PP)event.func)(p1, p2);
}
void cEventSource::callEvent(const EVENT& event, void *p1, int p2)
{
   if ( checkEvent(event, evFuncPI) )
        (event.obj->*(EVFUNC_PI)event.func)(p1, p2);
}
void cEventSource::callEvent(const EVENT& event, int p1)
{
   if ( checkEvent(event, evFuncI) )
        (event.obj->*(EVFUNC_I)event.func)(p1);
}
void cEventSource::callEvent(const EVENT& event, int p1, int p2)
{
   if ( checkEvent(event, evFuncII) )
        (event.obj->*(EVFUNC_II)event.func)(p1, p2);
}

// Aufrufen der int-Eventfunktionen
int cEventSource::callEventR(const EVENT& event)
{
   if ( checkEvent(event, evFuncR) )
        return (event.obj->*(EVFUNC_R)event.func)();
   return 0;
}
int cEventSource::callEventR(const EVENT& event, void *p1)
{
   if ( checkEvent(event, evFuncRP) )
        return (event.obj->*(EVFUNC_RP)event.func)(p1);
   return 0;
}
int cEventSource::callEventR(const EVENT& event, void *p1, void *p2)
{
   if ( checkEvent(event, evFuncRPP) )
        return (event.obj->*(EVFUNC_RPP)event.func)(p1, p2);
   return 0;
}
int cEventSource::callEventR(const EVENT& event, void *p1, int p2)
{
   if ( checkEvent(event, evFuncRPI) )
        return (event.obj->*(EVFUNC_RPI)event.func)(p1, p2);
   return 0;
}
int cEventSource::callEventR(const EVENT& event, int p1)
{
   if ( checkEvent(event, evFuncRI) )
        return (event.obj->*(EVFUNC_RI)event.func)(p1);
   return 0;
}
int cEventSource::callEventR(const EVENT& event, int p1, int p2)
{
   if ( checkEvent(event, evFuncRII) )
        return (event.obj->*(EVFUNC_RII)event.func)(p1, p2);
   return 0;
}


// Registrierte Eventfunktion aufrufen
// ===================================

void * cEventSource::findEventList(int event_id) const
{
   EVENT_LIST *ev_list = 0;

   if ( event_map == 0 )
      return 0; // Kein Fehler (Keine Event-Liste definiert)
   if ( !((EVENT_MAP*)event_map)->lookup(event_id, ev_list) )
      return 0; // Kein Fehler (Event von nirgendwo angefordert)

   return ev_list;
}

bool cEventSource::checkEvent(int event_id, EVFUNC_TYPE type, const EVENT& event) const
{
   if ( event.func == 0 || event.obj == 0 ) {
      __ECL_ASSERT2__(0,
         ("EVENT: Cannot call event %d, because no value(s) for func and/or obj were given",
         event_id));
      return false;
   }

   if ( event.type != type ) {
      __ECL_ASSERT2__(0,
         ("EVENT: Cannot call event %d with type '%s', because it's defined with type '%s'",
         event_id, EvFuncType[type], EvFuncType[event.type]));
      return false;
   }

   return true;
}

// Aufrufen der void-Eventfunktionen
void cEventSource::callEvent(int event_id)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFunc, event) )
            (event.obj->*(EVFUNC)event.func)();
      }
   }
}
void cEventSource::callEvent(int event_id, void *p1)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFuncP, event) )
            (event.obj->*(EVFUNC_P)event.func)(p1);
      }
   }
}
void cEventSource::callEvent(int event_id, void *p1, void *p2)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFuncPP, event) )
            (event.obj->*(EVFUNC_PP)event.func)(p1, p2);
      }
   }
}
void cEventSource::callEvent(int event_id, void *p1, int p2)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFuncPI, event) )
            (event.obj->*(EVFUNC_PI)event.func)(p1, p2);
      }
   }
}
void cEventSource::callEvent(int event_id, int p1)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFuncI, event) )
            (event.obj->*(EVFUNC_I)event.func)(p1);
      }
   }
}
void cEventSource::callEvent(int event_id, int p1, int p2)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFuncII, event) )
            (event.obj->*(EVFUNC_II)event.func)(p1, p2);
      }
   }
}

/*
// Aufrufen der int-Eventfunktionen
int cEventSource::callEventR(int event_id)
{
   EVENT event;
   if ( findEvent(event_id, evFuncR, event) )
        return (event.obj->*(EVFUNC_R)event.func)();
   return 0;
}
int cEventSource::callEventR(int event_id, void *p1)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRP, event) )
        return (event.obj->*(EVFUNC_RP)event.func)(p1);
   return 0;
}
int cEventSource::callEventR(int event_id, void *p1, void *p2)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRPP, event) )
        return (event.obj->*(EVFUNC_RPP)event.func)(p1, p2);
   return 0;
}
int cEventSource::callEventR(int event_id, void *p1, int p2)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRPI, event) )
        return (event.obj->*(EVFUNC_RPI)event.func)(p1, p2);
   return 0;
}
int cEventSource::callEventR(int event_id, int p1)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRI, event) )
        return (event.obj->*(EVFUNC_RI)event.func)(p1);
   return 0;
}
int cEventSource::callEventR(int event_id, int p1, int p2)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRII, event) )
        return (event.obj->*(EVFUNC_RII)event.func)(p1, p2);
   return 0;
}
*/


// Eventfunktion registrieren
// ==========================

void cEventSource::addEvent(int event_id,
                            void *obj, cEventSource::EVFUNC_PTR func, EVFUNC_TYPE type)
{
   EVENT event;
   event.type = type;
   event.func = func;
   event.obj = (cEventTarget*)obj;

   EVENT_MAP *ev_map = (EVENT_MAP*)event_map;
   if ( ev_map == 0 )
      event_map = ev_map = new0 EVENT_MAP;

   EVENT_LIST *ev_list = 0;
   if ( !ev_map->lookup(event_id, ev_list) )
      (*ev_map)[event_id] = ev_list = new0 EVENT_LIST;

   ev_list->addTail(event);
}

// Registrieren von Events mit void-Eventfunktionen
void cEventSource::addEvent(int event_id, void *obj, EVFUNC func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFunc); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_P func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncP); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_PP func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncPP); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_PI func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncPI); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_I func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncI); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_II func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncII); }

/*
// Registrieren von Events mit int-Eventfunktionen
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_R func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncR); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_RP func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRP); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_RPP func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRPP); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_RPI func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRPI); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_RI func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRI); }
void cEventSource::addEvent(int event_id, void *obj, EVFUNC_RII func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRII); }
*/


// Eventfunktion deregistrieren
// ============================

void cEventSource::removeEvent(int event_id)
{
   EVENT_MAP *ev_map = (EVENT_MAP*)event_map;

   if ( ev_map != 0 ) {
      EVENT_LIST *ev_list = 0;
      if ( ev_map->lookup(event_id, ev_list) ) {
         delete ev_list;
         (*ev_map)[event_id] = 0;
      }
   }
}

void cEventSource::removeEvent(int event_id, void *obj)
{
   EVENT_MAP *ev_map = (EVENT_MAP*)event_map;

   if ( ev_map != 0 ) {
      EVENT_LIST *ev_list = 0;
      if ( ev_map->lookup(event_id, ev_list) && ev_list != 0 ) {
         for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
            IPOSITION cur_pos = pos;
            EVENT event = ev_list->getNext(pos);
            if ( event.obj == obj )
               ev_list->removeAt(cur_pos);
         }
      }
   }
}

void cEventSource::removeEvent(void *obj)
{
   EVENT_MAP *ev_map = (EVENT_MAP*)event_map;

   if ( ev_map != 0 ) {
      for ( IPOSITION pos = ev_map->getStartPosition() ; pos != 0 ; ) {
         EVENT_LIST *ev_list; int ev_id;
         ev_map->getNextAssoc(pos, ev_id, ev_list);
         removeEvent(ev_id, obj);
      }
   }
}


