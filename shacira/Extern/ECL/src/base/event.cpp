// ===========================================================================
// base/event.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/event.h"

// Other ECL headers
#include "base/map.h"
#include "base/list.h"


/**
* @defgroup event Events
* @ingroup baseclass
*/




namespace ecl {




// Lokale Variablen
// ===========================================================================

static const char * EvFuncType[] = {
   "evUndef",
   "evFuncVoid",  "evFuncP",  "evFuncPP",  "evFuncPI",  "evFuncI",  "evFuncII",
   "evFuncRVoid", "evFuncRP", "evFuncRPP", "evFuncRPI", "evFuncRI", "evFuncRII"
};




// Implementierung cEvent
// ===========================================================================

// Struktur eines Eintrags in die Event-Liste

// Typ def Event-Liste (LIST aus Event-Eintraegen)
typedef class cList<cEvent::EVENT,const cEvent::EVENT&> EVENT_LIST;
// Typ def Event-Map (MAP aus Event-Listen)
typedef class cMap<int,int,EVENT_LIST*,EVENT_LIST*> EVENT_MAP;


// Konstruktor, Destruktor
// =======================

cEvent::~cEvent()
{
   // Benachrichtigen aller interessierter Klassen, dass das
   // cEvent-Objekt in Kuerze verschwindet

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

bool cEvent::checkEvent(const EVENT& event, EVFUNC_TYPE type)
{
   if ( event.func == 0 || event.obj == 0 ) {
      // Keine Fehlermeldung, da voellig legaler Zustand...
      // cBase::DbgError(
      //    "EVENT: Cannot call unregistered event, because no value(s) for func and/or obj were given");
      return false;
   }

   if ( event.type != type ) {
      __ECL_DEBUG_PRINTF__(cBase::dbgError|cBase::dbgBase|cBase::dbgAssert,
         ("EVENT: Cannot call unregistered event with type '%s', because it's defined with type '%s'",
         EvFuncType[type], EvFuncType[event.type]));
      return false;
   }

   return true;
}

// Aufrufen der void-Eventfunktionen
void cEvent::callEvent(const EVENT& event)
{
   if ( checkEvent(event, evFuncVoid) )
        (event.obj->*(EVFUNC)event.func)();
}
void cEvent::callEvent(const EVENT& event, void *p1)
{
   if ( checkEvent(event, evFuncP) )
        (event.obj->*(EVFUNC_P)event.func)(p1);
}
void cEvent::callEvent(const EVENT& event, void *p1, void *p2)
{
   if ( checkEvent(event, evFuncPP) )
        (event.obj->*(EVFUNC_PP)event.func)(p1, p2);
}
void cEvent::callEvent(const EVENT& event, void *p1, int p2)
{
   if ( checkEvent(event, evFuncPI) )
        (event.obj->*(EVFUNC_PI)event.func)(p1, p2);
}
void cEvent::callEvent(const EVENT& event, int p1)
{
   if ( checkEvent(event, evFuncI) )
        (event.obj->*(EVFUNC_I)event.func)(p1);
}
void cEvent::callEvent(const EVENT& event, int p1, int p2)
{
   if ( checkEvent(event, evFuncII) )
        (event.obj->*(EVFUNC_II)event.func)(p1, p2);
}

// Aufrufen der int-Eventfunktionen
int cEvent::callEventR(const EVENT& event)
{
   if ( checkEvent(event, evFuncRVoid) )
        return (event.obj->*(EVFUNC_R)event.func)();
   return 0;
}
int cEvent::callEventR(const EVENT& event, void *p1)
{
   if ( checkEvent(event, evFuncRP) )
        return (event.obj->*(EVFUNC_RP)event.func)(p1);
   return 0;
}
int cEvent::callEventR(const EVENT& event, void *p1, void *p2)
{
   if ( checkEvent(event, evFuncRPP) )
        return (event.obj->*(EVFUNC_RPP)event.func)(p1, p2);
   return 0;
}
int cEvent::callEventR(const EVENT& event, void *p1, int p2)
{
   if ( checkEvent(event, evFuncRPI) )
        return (event.obj->*(EVFUNC_RPI)event.func)(p1, p2);
   return 0;
}
int cEvent::callEventR(const EVENT& event, int p1)
{
   if ( checkEvent(event, evFuncRI) )
        return (event.obj->*(EVFUNC_RI)event.func)(p1);
   return 0;
}
int cEvent::callEventR(const EVENT& event, int p1, int p2)
{
   if ( checkEvent(event, evFuncRII) )
        return (event.obj->*(EVFUNC_RII)event.func)(p1, p2);
   return 0;
}


// Registrierte Eventfunktion aufrufen
// ===================================

void * cEvent::findEventList(int event_id) const
{
   EVENT_LIST *ev_list = 0;

   if ( event_map == 0 )
      return 0; // Kein Fehler (Keine Event-Liste definiert)
   if ( !((EVENT_MAP*)event_map)->lookup(event_id, ev_list) )
      return 0; // Kein Fehler (Event von nirgendwo angefordert)

   return ev_list;
}

bool cEvent::checkEvent(int event_id, EVFUNC_TYPE type, const EVENT& event) const
{
   if ( event.func == 0 || event.obj == 0 ) {
      __ECL_DEBUG_PRINTF__(cBase::dbgError|cBase::dbgBase|cBase::dbgAssert,
         ("EVENT: Cannot call event %d, because no value(s) for func and/or obj were given",
         event_id));
      return false;
   }

   if ( event.type != type ) {
      __ECL_DEBUG_PRINTF__(cBase::dbgError|cBase::dbgBase|cBase::dbgAssert,
         ("EVENT: Cannot call event %d with type '%s', because it's defined with type '%s'",
         event_id, EvFuncType[type], EvFuncType[event.type]));
      return false;
   }

   return true;
}

// Aufrufen der void-Eventfunktionen
void cEvent::callEvent(int event_id)
{
   EVENT_LIST *ev_list;
   if ( (ev_list = (EVENT_LIST*)findEventList(event_id)) != 0 ) {
      for ( IPOSITION pos = ev_list->getHeadPosition() ; pos != 0 ; ) {
         EVENT event = ev_list->getNext(pos);
         if ( checkEvent(event_id, evFuncVoid, event) )
            (event.obj->*(EVFUNC)event.func)();
      }
   }
}
void cEvent::callEvent(int event_id, void *p1)
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
void cEvent::callEvent(int event_id, void *p1, void *p2)
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
void cEvent::callEvent(int event_id, void *p1, int p2)
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
void cEvent::callEvent(int event_id, int p1)
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
void cEvent::callEvent(int event_id, int p1, int p2)
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
int cEvent::callEventR(int event_id)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRVoid, event) )
        return (event.obj->*(EVFUNC_R)event.func)();
   return 0;
}
int cEvent::callEventR(int event_id, void *p1)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRP, event) )
        return (event.obj->*(EVFUNC_RP)event.func)(p1);
   return 0;
}
int cEvent::callEventR(int event_id, void *p1, void *p2)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRPP, event) )
        return (event.obj->*(EVFUNC_RPP)event.func)(p1, p2);
   return 0;
}
int cEvent::callEventR(int event_id, void *p1, int p2)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRPI, event) )
        return (event.obj->*(EVFUNC_RPI)event.func)(p1, p2);
   return 0;
}
int cEvent::callEventR(int event_id, int p1)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRI, event) )
        return (event.obj->*(EVFUNC_RI)event.func)(p1);
   return 0;
}
int cEvent::callEventR(int event_id, int p1, int p2)
{
   EVENT event;
   if ( findEvent(event_id, evFuncRII, event) )
        return (event.obj->*(EVFUNC_RII)event.func)(p1, p2);
   return 0;
}
*/


// Eventfunktion registrieren
// ==========================

void cEvent::addEvent(int event_id,
                            void *obj, cEvent::EVFUNC_PTR func, EVFUNC_TYPE type)
{
   EVENT event;
   event.type = type;
   event.func = func;
   event.obj = (cEvent*)obj;

   EVENT_MAP *ev_map = (EVENT_MAP*)event_map;
   if ( ev_map == 0 )
      event_map = ev_map = new0 EVENT_MAP;

   EVENT_LIST *ev_list = 0;
   if ( !ev_map->lookup(event_id, ev_list) )
      (*ev_map)[event_id] = ev_list = new0 EVENT_LIST;

   ev_list->addTail(event);
}

// Registrieren von Events mit void-Eventfunktionen
void cEvent::addEvent(int event_id, void *obj, EVFUNC func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncVoid); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_P func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncP); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_PP func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncPP); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_PI func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncPI); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_I func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncI); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_II func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncII); }

/*
// Registrieren von Events mit int-Eventfunktionen
void cEvent::addEvent(int event_id, void *obj, EVFUNC_R func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRVoid); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_RP func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRP); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_RPP func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRPP); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_RPI func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRPI); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_RI func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRI); }
void cEvent::addEvent(int event_id, void *obj, EVFUNC_RII func)
   {  addEvent(event_id, obj, (EVFUNC_PTR)func, evFuncRII); }
*/


// Eventfunktion deregistrieren
// ============================

void cEvent::removeEvent(int event_id)
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

void cEvent::removeEvent(int event_id, void *obj)
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

void cEvent::removeEvent(void *obj)
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




}; // namespace ecl


