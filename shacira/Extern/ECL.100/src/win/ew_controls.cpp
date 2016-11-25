// ===========================================================================
// ew_controls.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwControl     - Basisklasse fuer alle ECL-Controls
//
// Nomenklatur der Control-Klassen:
//
//    cw<typ>Ctl        - Basisklasse fuer einen Control-Typ
//
//    cw<typ>Field      - Einfaches Feld (z.B. cwEditField)
//
//    cw<typ>Box        - Komplexes Feld (z.B. cwEditBox, cwListBox)
//
//    cw<subtyp><typ>   - Untertyp des Control-Typs (z.B. cwPushButton)
//
// ===========================================================================

#include "win/ew_controls.hpp"
#include "base/eb_thread.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_store.hpp"
#include "store/es_query.hpp"
#include "win/ew_windows.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwControl
// ---------------------------------------------------------------------------
//
// Ein cwControl kann nicht direkt erzeugt werden, dies ist nur ueber eine
// der abgeleiteten Klassen wie cwButton oder cwEntry moeglich.
//
// cBase
//  +--cwWindow
//      +--cwControl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwControl : public cwWindow {
   ELO_DECLARE(cwControl,cwWindow)

public:

   // Allgemeines
   // ===========

   // Destruktor
   virtual ~cwControl();

   // Mit bestehendem Fenster verknuepfen
   void attach(cwWindow *parent, int id, csStorage *store = 0, csQuery *query = 0);


   // window-Flags
   // ============

   // Flags
   enum FLAGS { wflStart = cwWindow::wflUser,
      wflHasChanged     = wflStart << 0,  // Feldinhalt hat sich geaendert
      wflIsReadOnly     = wflStart << 1,  // Feldinhalt ist schreibgeschuetzt
      wflInsertMode     = wflStart << 2,  // Merker-Flag fuer Insert-Mode
      wflDelStorage     = wflStart << 3,  // Storage-Objekt loeschen?
      wflDelQuery       = wflStart << 4,  // Abfrageobjekt loeschen?
      wflInQuery        = wflStart << 5,  // Abfrage momentan aktiv?
      wflQueryStarted   = wflStart << 6,  // Abfrage aktiv und gestartet?
      wflInhValShown    = wflStart << 7,  // Defaultwert angezeigt?
      wflInhValMark     = wflStart << 8,  // Defaultwert-Markierung aktiv?
      wflErrFormat      = wflStart << 9,  // Format-Fehler? (Kein Store moeglich)
      wflEatEnterKey    = wflStart << 10, // Taste ENTER verschlucken (jedoch: Event erzeugen)
      wflEatEscKey      = wflStart << 11, // Taste ESC verschlucken (jedoch: Event erzeugen)
      wflEatNavKeys     = wflStart << 12, // Navigationstasten verschlucken (jedoch: Event erzeugen)
      wflUser           = wflStart << 13  // Benutzerdefinierte Flags
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwWindow::evtUser,
      evtHelpRequested,       // (EVFUNC)   Kontexthilfe angefordert (F1)
      evtDetailRequested,     // (EVFUNC)   Detailauswahl angefordert (F2)
      evtStorageModified,     // (EVFUNC_P) Inhalt der Storage geaendert
      evtStorageSet,          // (EVFUNC_P) Neue Storage gesetzt
      evtStorageRemoved,      // (EVFUNC_P) Bisherige Storage entfernt
      evtEnterKeyPressed,     // (EVFUNC)   Enter-Taste gedrueckt
      evtEscKeyPressed,       // (EVFUNC)   Escape-Taste gedrueckt
      evtNavKeyPressed,       // (EVFUNC_I) Navigations-Taste gedrueckt
      evtUser                 // Ab hier benutzerdefinierte Events
   };


   // Fehlerverarbeitung
   // ==================

   enum DATAERR {
      derrNone,         // Kein Fehler
      derrNotNull,      // Feld darf nicht leer sein
      derrFormat,       // Fehlerhaftes Format
      derrRead,         // Lesefehler
      derrWrite         // Schreibfehler
   };


   // Gebundene Daten
   // ===============

   // Hat Control ein csStorage zugeordnet?
   inline bool hasStorage() const
      { return store != 0; }
   // Liefert das zugeordnete Datenobjekt
   inline csStorage *getStorage() const
      { return store; }

   // Gebundenes Datenobjekt wechseln
   void setStorage(csStorage *store);
   // Bindung an Datenobjekt entfernen
   void removeStorage();

   // Typ des gebundenen Datenobjektes erfragen
   inline csStorage::TYPE getStorageType() const
      { return store ? store->getType() : csStorage::tNone; }
   // Ist das gebundene Datenobjekt Read-Only (keine Aenderungen moeglich)?
   bool isStorageReadOnly() const;

   // Ist das NULL-Flag des gebundenen Datenobjektes gesetzt?
   inline bool isStorageNull() const
      { return store ? store->isNull() : false; }
   // NULL-Flag des gebundenen Datenobjektes setzen
   inline void setStorageNull()
      { if ( store ) store->setNull(); }

   // Ermittelt den int-Wert
   inline bool getStorageVal(int& buf) const
      { return store ? store->get(buf) : false; }
   // Ermittelt den double-Wert
   inline bool getStorageVal(double& buf) const
      { return store ? store->get(buf) : false; }
   // Ermittelt den cTime-Wert
   inline bool getStorageVal(cTime& buf) const
      { return store ? store->get(buf) : false; }
   // Ermittelt den cDate-Wert
   inline bool getStorageVal(cDate& buf) const
      { return store ? store->get(buf) : false; }
   // Ermittelt den char-Wert
   inline bool getStorageVal(char& buf) const
      { return store ? store->get(buf) : false; }
   // Ermittelt den cString-Wert
   inline bool getStorageVal(cString& buf) const
      { return store ? store->get(buf) : false; }
   // Wert in anderes csStorage-Objekt uebernehmen
   bool getStorageVal(csStorage *other) const;

   // int-Wert schreiben
   inline bool putStorageVal(int buf)
      { return store ? store->put(buf) : false; }
   // double-Wert schreiben
   inline bool putStorageVal(double buf)
      { return store ? store->put(buf) : false; }
   // cTime-Wert schreiben
   inline bool putStorageVal(cTime buf)
      { return store ? store->put(buf) : false; }
   // cDate-Wert schreiben
   inline bool putStorageVal(cDate buf)
      { return store ? store->put(buf) : false; }
   // char-Wert schreiben
   inline bool putStorageVal(char buf)
      { return store ? store->put(buf) : false; }
   // cString-Wert schreiben
   inline bool putStorageVal(const char *buf)
      { return store ? store->put(buf) : false; }
   // Wert aus anderem csStorage-Objekt uebernehmen
   bool putStorageVal(const csStorage *other);


   // Abfrage
   // =======

   // Hat das Control eine csQuery zugeordnet?
   inline bool hasQuery() const
      { return query != 0; }
   // Wird die Abfrage gerade bearbeitet?
   inline bool inQuery() const
      { return !!getFlags(wflInQuery); }
   // Liefert die zugeordnete Abfrage
   inline csQuery *getQuery() const
      { return query; }
   // Abfrage erneut durchfuehren
   inline bool requery()
      { return onRequery(); }

   // Abfrage wechseln
   void setQuery(csQuery *query);
   // Abfrage entfernen
   void removeQuery();


   // Ererbte Werte
   // =============
   // Der ererbte Wert eines Controls wird immer dann angezeigt, wenn das
   // Control einen entsprechenden 'undefinierten' Zustand hat. Dies ist
   // z.B. bei einem Eingabefeld der Fall, wenn das Feld leer ist, bei einer
   // CheckBox, wenn sie den Zustand 'Indeterminiert' hat. Die Erkennung
   // dieses Zustands sowie die Art und Weise der Visualisierung des er-
   // erbten Wertes bleibt dem jeweiligen Control ueberlassen.

   // Hat das Control einen ererbten Wert?
   bool hasInheritedValue() const;
   // Liefert den zugeordneten ererbten Wert
   cString getInheritedValue() const;
   // Ist die (optische) Markierung eingeschaltet?
   bool isMarkedAsInheritedValue() const;
   // Anzeige des ererbten Wertes aktualisieren
   void refreshInheritedValue(bool force_refresh = false);

   // Setzt den zugeordneten ererbten cString-Wert
   void setInheritedValue(cString val);
   // Setzt den zugeordneten ererbten Wert auf den Wert des csStorage-Objektes
   void setInheritedValue(csStorage *val);
   // Setzt den zugeordneten ererbten char-Wert
   void setInheritedValue(char val);
   // Setzt den zugeordneten ererbten int-Wert
   void setInheritedValue(int val, bool thsnd_sep = true);
   // Setzt den zugeordneten ererbten double-Wert
   void setInheritedValue(double val, int prec = -1, bool thsnd_sep = true);
   // Loescht den zugeordneten ererbten Wert
   void clearInheritedValue();


   // Sonstiges
   // =========

   // Changed-Flag loeschen (Control als unveraendert markieren)
   inline void clearChanged()
      { onClearChanged(); }
   // Zustand des Changed-Flags erfragen
   inline bool getChanged() const
      { return onGetChanged(); }
   // ReadOnly-Zustand setzen
   inline void setReadOnly(bool ro_state)
      { onSetReadOnly(ro_state); }
   // ReadOnly-Zustand erfragen
   inline bool getReadOnly() const
      { return onGetReadOnly(); }


protected:

   // Zusaetzliche Events
   // ===================

   // Kontexthilfe zum Control wurde angefordert
   virtual void onHelpRequest();
   // Detailauswahl zum Control wurde angefordert
   virtual void onDetailRequest();
   // Die Enter-Taste wurde gedrueckt
   virtual void onEnterKey();
   // Die Escape-Taste wurde gedrueckt
   virtual void onEscapeKey();
   // Eine Navigationstaste wurde gedrueckt
   virtual void onNavKey(int vk_code);

   // Wird aufgerufen, wenn die Storage geloescht wird
   virtual void onEventDestructStorage(void *p1);
   // Wird aufgerufen, wenn die Query geloescht wird
   virtual void onEventDestructQuery(void *p1);
   // Wird aufgerufen, wenn sich das gebundene Datenobjekt geaendert hat
   virtual void onEventModified();

   // Wird aufgerufen bei derrNotNull
   virtual bool onErrorNotNull();
   // Wird aufgerufen bei derrFormat
   virtual bool onErrorFormat();
   // Wird aufgerufen bei derrRead
   virtual bool onErrorRead();
   // Wird aufgerufen bei derrWrite
   virtual bool onErrorWrite();
   // Feld als ungueltig markieren
   virtual void onErrorMark(bool mark);

   // Daten des Controls refreshen
   virtual bool onRefreshCtl(csStorage *store);
   // Abfrage des Controls erneut durchfuehren
   virtual bool onRequeryCtl(csQuery *query);
   // Daten des Controls pruefen
   virtual DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   virtual DATAERR onStoreCtl(csStorage *store);

   // Wird aufgerufen, nachdem das Storage-Objekt gesetzt wurde
   virtual void onSetStorage(csStorage *store);
   // Wird aufgerufen, bevor das Storage-Objekt entfernt wird
   virtual void onRemoveStorage(csStorage *store);

   // Wird aufgerufen, nachdem das Query-Objekt gesetzt wurde
   virtual void onSetQuery(csQuery *query);
   // Wird aufgerufen, bevor das Query-Objekt entfernt wird
   virtual void onRemoveQuery(csQuery *query);
   // Wird aufgerufen, um die Abfrage erneut durchzufuehren
   virtual bool onRequery();

   // Wird aufgerufen, um die (optische) Markierung fuer ererbte Werte einzuschalten
   virtual void onShowInheritedMark();
   // Wird aufgerufen, um die (optische) Markierung fuer ererbte Werte auszuschalten
   virtual void onHideInheritedMark();
   // Wird aufgerufen, um den aktuellen ererbten Wert anzuzeigen
   virtual void onShowInheritedVal();
   // Wird aufgerufen, um die Anzeige des ererbten Wertes zu beenden
   virtual void onHideInheritedVal();
   // Wird aufgerufen um festzustellen, ob das Control einen ueberschriebenen Wert hat
   virtual bool onIsInheritedValOverridden();

   // Changed-Flag loeschen (Control als unveraendert markieren)
   virtual void onClearChanged();
   // Zustand des Changed-Flags erfragen
   virtual bool onGetChanged() const;

   // ReadOnly-Zustand setzen
   virtual void onSetReadOnly(bool ro_state);
   // ReadOnly-Zustand erfragen
   virtual bool onGetReadOnly() const;


   // Ueberschriebene Events
   // ======================

   // Inhalt refreshen (false -> Abbruch)
   bool onRefresh(); // war: RefreshEvt()
   // Inhalt speichern (false -> Abbruch)
   bool onStore(); // war: StoreEvt()
   // Taste gedrueckt
   void onChar(cwCmdChar& cmd);
   // Blaettern zu Sibling erlauben?
   bool onAllowTurn(); // war: AllowTurnEvt()
   // Abbruch mit Speichern erlauben?
   bool onAllowStore(); // war: AllowStoreEvt()
   // Wird aufgerufen, wenn Fenster den Focus erhaelt
   void onGainFocus();
   // Wird aufgerufen, wenn Fenster den Focus verliert
   void onLoseFocus();

   // Entscheiden, ob das cwCmdChar-Kommando weiterverteilt werden soll
   bool onDispatchChar(const cwCmdChar& cmd);


   // Verzoegerte Ausfuehrung
   // =======================

   enum  { ediStart = cwWindow::ediUser,
      ediSetQuery,      // Verzoegerte Ausfuehrung von setQuery
      ediUser,          // ab hier Erweiterungen
   };

   // Verzoegertes Ausfuehren einer Operation
   void onExecDelayed(int id, void *data);


protected:

   // Interner Konstruktor
   cwControl(void *wnd);
   // Control erzeugen (Intern)
   void create(cwWindow *parent, int id, csStorage *store = 0, csQuery *query = 0);


private:

   csStorage *store;    // Gebundenes Datenobjekt
   csQuery *query;      // Zugeordnete Abfrage
   cString defval;      // Standardwert ("inherited value")

   // Intern: Verzoegerte Ausfuehrung von setQuery
   void execSetQuery(csQuery *query);

};

#endif /*__INTERFACE__*/


// Implementierung cwControl
// ===========================================================================

cwControl::cwControl(void *wnd) :
   cwWindow(wnd)
{
   cwControl::store = 0;
   cwControl::query = 0;
}

cwControl::~cwControl()
{
   removeStorage();
   removeQuery();
}

void cwControl::create(cwWindow *parent, int /*id*/, csStorage *store, csQuery *query)
{
   __ECL_ASSERT1__(_wnd != 0);
   __ECL_ASSERT1__(parent != 0);

   setStorage(store);
   setQuery(query);

   cwWindow::create(parent);
}

void cwControl::attach(cwWindow *parent, int id, csStorage *store, csQuery *query)
{
   __ECL_ASSERT1__(_wnd != 0);
   __ECL_ASSERT1__(parent != 0);

   setStorage(store);
   setQuery(query);

   cwWindow::attach(parent, id);
}


// Gebundene Daten
// ===============

void cwControl::setStorage(csStorage *store)
{
   removeStorage();

   if ( (cwControl::store = store) != 0 ) {
      store->addEvent(csStorage::evtDestructingSource, this, (EVFUNC_P)onEventDestructStorage);
      store->addEvent(csStorage::evtValueModified, this, (EVFUNC)onEventModified);
      setFlags(wflDelStorage, !store->isPermanent());
      // Nach dem Setzen das Control benachrichtigen
      onSetStorage(store);
      refresh();
   } else {
      setFlags(wflDelStorage, false);
   }
}

void cwControl::removeStorage()
{
   if ( store ) {
      // Vor dem Entfernen das Control benachrichtigen
      onRemoveStorage(store);
      store->removeEvent(this);
      if ( getFlags(wflDelStorage) )
         delete store;
      store = 0;
   }
}

bool cwControl::isStorageReadOnly() const
{
   if ( isEnabled() ) {
      return store ? store->isReadOnly() : true;
   } else {
      return false;
   }
}

bool cwControl::getStorageVal(csStorage *other) const
{
   if ( other != 0 ) {
      cString buf;
      if ( store != 0 && !store->isNull() && store->get(buf) ) {
         return other->put(buf);
      } else {
         other->setNull();
         return true;
      }
   }

   return false;
}

bool cwControl::putStorageVal(const csStorage *other)
{
   if ( store != 0 ) {
      cString buf;
      if ( other != 0 && !other->isNull() && other->get(buf) ) {
         return putStorageVal(buf);
      } else {
         setStorageNull();
         return true;
      }
   }

   return false;
}


// Zugeordnete Abfrage
// ===================

void cwControl::setQuery(csQuery *query)
{
   // Wenn Abfrage bereits laeuft, dann STOP erzwingen
   if ( inQuery() /*getFlags(wflQueryStarted)*/ ) {
      getQuery()->stop();
      // Wenn moeglich, setQuery stark verzoegert ausfuehren
      execDelayed(ediSetQuery, query);
      return;
   }

   // Wenn moeglich, setQuery verzoegert ausfuehren
   execDelayed(ediSetQuery, query);
}

void cwControl::execSetQuery(csQuery *query)
{
   if ( !inQuery() ) {

      removeQuery();

      if ( (cwControl::query = query) != 0 ) {
         query->requestLock();
         query->addEvent(csQuery::evtDestructingSource, this, (EVFUNC_P)onEventDestructQuery);
         setFlags(wflDelQuery, !query->isPermanent());
         // Basis-Elementbeschreibung der Query uebernehmen
         setElemDescr(query->getBaseDescription());
         // Nach dem Setzen das Control benachrichtigen...
         onSetQuery(query);
         // ... und ein Requery veranlassen
         requery();
      } else {
         setFlags(wflDelQuery, false);
      }

   } else if ( query != 0 ) {

      // Die Query kann nicht gesetzt werden, da noch eine andere laeuft.
      // Also freigeben, wenn noetig. TBD: Die bisherige Query unterbrechen
      // waere schon irgendwie besser...

      cBase::DbgError("setQuery failed, cause current query still running");
      query->removeEvent(this);
      query->releaseLock(!!getFlags(wflDelQuery));

   }
}

void cwControl::removeQuery()
{
   if ( query ) {
      // Vor dem Entfernen das Control benachrichtigen
      onRemoveQuery(query);
      query->removeEvent(this);
      query->releaseLock(!!getFlags(wflDelQuery));
      query = 0;
   }
}

bool cwControl::onRequery()
{
   if ( query == 0 )
      return true;

   bool ok = false;

   try {
      ok = onRequeryCtl(query);
   } catch ( const cErrBase& err ) {
      showError(err);
   }

   return ok;
}


// Ererbte Werte
// =============

bool cwControl::hasInheritedValue() const
{
   return !defval.isEmpty();
}

cString cwControl::getInheritedValue() const
{
   return defval;
}

bool cwControl::isMarkedAsInheritedValue() const
{
   return !!getFlags(wflInhValMark);
}

void cwControl::refreshInheritedValue(bool force_refresh)
{
   if ( !hasInheritedValue()
     || onIsInheritedValOverridden()
     || getFlags(wflHasFocus) )
   {

      if ( force_refresh || getFlags(wflInhValShown|wflInhValMark) != 0 ) {

         //setRedraw(false);

         if ( force_refresh || getFlags(wflInhValShown) ) {
            onHideInheritedVal();
            setFlags(wflInhValShown, false);
         }

         if ( force_refresh || getFlags(wflInhValMark) ) {
            onHideInheritedMark();
            setFlags(wflInhValMark, false);
         }

         //setRedraw(true);
      }

   } else {

      if ( force_refresh || getFlags(wflInhValShown|wflInhValMark) != (wflInhValShown|wflInhValMark) ) {

         //setRedraw(false);

         if ( force_refresh || !getFlags(wflInhValShown) ) {
            onShowInheritedVal();
            setFlags(wflInhValShown, true);
         }

         if ( force_refresh || !getFlags(wflInhValMark) ) {
            onShowInheritedMark();
            setFlags(wflInhValMark, true);
         }

         //setRedraw(true);
      }

   }
}

void cwControl::setInheritedValue(cString val)
{
   defval = val;
   refreshInheritedValue(true);
}

void cwControl::setInheritedValue(csStorage *val)
{
   if ( val && !val->isNull() ) {
      cString buf;
      val->get(buf);
      setInheritedValue(buf);
   } else {
      clearInheritedValue();
   }
}

void cwControl::setInheritedValue(char val)
{
   setInheritedValue(cStringf("%c", val));
}

void cwControl::setInheritedValue(int val, bool thsnd_sep)
{
   char temp[128];
   csBaseStorage::formatValue(temp, val, 0, 0, thsnd_sep, false);
   setInheritedValue(temp);
}

void cwControl::setInheritedValue(double val, int prec, bool thsnd_sep)
{
   char temp[128];
   csBaseStorage::formatValue(temp, val, 0, prec, thsnd_sep, false);
   setInheritedValue(temp);
}

void cwControl::clearInheritedValue()
{
   setInheritedValue(cString());
}


// Zusaetzliche Events
// ===================

void cwControl::onHelpRequest()
{
   cBase::DbgTrcWin("cwControl::onHelpRequest()");
}

void cwControl::onDetailRequest()
{
   cBase::DbgTrcWin("cwControl::onDetailRequest()");
}

void cwControl::onEnterKey()
{
   // Diese Methode wird aufgerufen, wenn die ENTER- oder die RETURN-Taste
   // gedrueckt wird, waehrend das Control den Eingabefocus hat. Anschliessend
   // wird das Event evtEnterKeyPressed ausgeloest. Ist das Flag wflEatEnterKey
   // gesetzt, wird der Tastendruck nicht an das Control weitergereicht.

   cBase::DbgTrcWin("cwControl::onEnterKey()");
}

void cwControl::onEscapeKey()
{
   // Diese Methode wird aufgerufen, wenn die ESCAPE-Taste gedrueckt wird,
   // waehrend das Control den Eingabefocus hat. Anschliessend wird das Event
   // evtEscKeyPressed ausgeloest. Ist das Flag wflEatEscKey gesetzt,
   // wird der Tastendruck nicht an das Control weitergereicht.

   cBase::DbgTrcWin("cwControl::onEscapeKey()");
}

void cwControl::onNavKey(int vk_code)
{
   // Diese Methode wird aufgerufen, wenn eine Navigationstaste gedrueckt wird,
   // waehrend das Control den Eingabefocus hat. Welche Taste als Navigations-
   // taste gilt, ist abhaengig vom jeweiligen Control. Diese Basisklasse inter-
   // pretiert TAB und BACKTAB als Navigationstasten. Anschliessend wird das Event
   // evtNavKeyPressed ausgeloest. Ist das Flag wflEatNavKey gesetzt,
   // wird der Tastendruck nicht an das Control weitergereicht.

   cBase::DbgTrcWin("cwControl::onNavKey(%d)", vk_code);
}

void cwControl::onEventDestructStorage(void *)
{
   cBase::DbgTrcWin("cwControl::onEventDestructStorage()");

   // Hier wird die praegnante Kurzform von removeStorage angewandt. Da die
   // Storage sowieso gerade dabei ist, zerstoert zu werden, wenn dieser
   // Event generiert wird, bleibt auch nicht viel anderes uebrig...

   store = 0;
}

void cwControl::onEventDestructQuery(void *)
{
   cBase::DbgTrcWin("cwControl::onEventDestructQuery()");

   // Hier wird die praegnante Kurzform von removeQuery angewandt. Da die
   // Query sowieso gerade dabei ist, zerstoert zu werden, wenn dieser
   // Event generiert wird, bleibt auch nicht viel anderes uebrig...

   query = 0;
}

void cwControl::onEventModified()
{
   cBase::DbgTrcWin("cwControl::onEventModified()");
   if ( store != 0 )
      callEvent(evtStorageModified, store);
   refresh();
}

bool cwControl::onErrorNotNull()
{
   onErrorMark(true);
   showError("Dieses Feld darf nicht leer sein!");
   onErrorMark(false);
   setFocus();
   return false;
}

bool cwControl::onErrorFormat()
{
   onErrorMark(true);
   showError("Die eingegebenen Daten in diesem Feld sind fehlerhaft!");
   onErrorMark(false);
   setFocus();
   return false;
}

bool cwControl::onErrorRead()
{
   onErrorMark(true);
   showError("Fehler beim Lesen des Feldes!");
   onErrorMark(false);
   setFocus();
   return false;
}

bool cwControl::onErrorWrite()
{
   onErrorMark(true);
   showError("Fehler beim Schreiben des Feldes!");
   onErrorMark(false);
   setFocus();
   return false;
}

void cwControl::onErrorMark(bool mark)
{
   if ( mark ) {
      setPresParam(ppBkgndColor, cdColor(cdColor::Red));
   } else {
      removePresParam(ppBkgndColor);
   }
}

bool cwControl::onRefreshCtl(csStorage * /*store*/)
{
   setReadOnly(isStorageReadOnly());
   return true;
}

bool cwControl::onRequeryCtl(csQuery * /*query*/)
{
   return true;
}

cwControl::DATAERR cwControl::onCheckCtl(csStorage * /*store*/)
{
   return getFlags(wflErrFormat) ? derrFormat : derrNone;
}

cwControl::DATAERR cwControl::onStoreCtl(csStorage * /*store*/)
{
   return getFlags(wflErrFormat) ? derrFormat : derrNone;
}

void cwControl::onSetStorage(csStorage *store)
{
   if ( store != 0 )
      callEvent(evtStorageSet, store);
}

void cwControl::onRemoveStorage(csStorage *store)
{
   if ( store != 0 )
      callEvent(evtStorageRemoved, store);
}

void cwControl::onSetQuery(csQuery * /*query*/)
{
}

void cwControl::onRemoveQuery(csQuery * /*query*/)
{
}

// ---

void cwControl::onShowInheritedMark()
{
   setPresParam(ppFgndColor, cdColor(cdColor::Blue));
}

void cwControl::onHideInheritedMark()
{
   removePresParam(ppFgndColor);
}

void cwControl::onShowInheritedVal()
{
   setText(getInheritedValue());
}

void cwControl::onHideInheritedVal()
{
   setText(cString());
}

bool cwControl::onIsInheritedValOverridden()
{
   return !isStorageNull();
}

// ---

void cwControl::onClearChanged()
{
   setFlags(wflHasChanged, false);
}

bool cwControl::onGetChanged() const
{
   return !!getFlags(wflHasChanged);
}

void cwControl::onSetReadOnly(bool ro_state)
{
   if ( !!ro_state != !!getFlags(wflIsReadOnly) ) {
      setEnable(!ro_state);
      setFlags(wflIsReadOnly, ro_state);
   }
}

bool cwControl::onGetReadOnly() const
{
   return !!getFlags(wflIsReadOnly);
}


// Ueberschriebene Events
// ======================

bool cwControl::onRefresh()
{
   if ( store ) {
      if ( !store->refetch() )
         return false;
      if ( !onRefreshCtl(store) )
         return false;
   }

   return cwWindow::onRefresh();
}

bool cwControl::onStore()
{
   // 16.07.2001 -TE- Storage nur speichern, wenn Control
   // geaendert wurde (Aufruf von getChanged() neu)

   if ( store && getChanged() ) {
      switch ( onStoreCtl(store) ) {
      case derrNotNull: return onErrorNotNull();
      case derrFormat:  return onErrorFormat();
      }
   }

   return cwWindow::onStore();
}

void cwControl::onChar(cwCmdChar& cmd)
{
   if ( cmd.isVirt() && cmd.isKeyDown()  ) {
      switch ( cmd.getVirt() ) {
      case cwCmdChar::vkF1:
         onHelpRequest();
         callEvent(evtHelpRequested);
         break;
      case cwCmdChar::vkF2:
         onDetailRequest();
         callEvent(evtDetailRequested);
         break;
      case cwCmdChar::vkF5:
         refresh();
         break;
/*
      case cwCmdChar::vkEnter:
      case cwCmdChar::vkReturn:
         onEnterKey();
         callEvent(evtEnterKeyPressed);
         if ( getFlags(wflEatEnterKey) )
            cmd.killMsg();
         break;
      case cwCmdChar::vkEsc:
         onEscapeKey();
         callEvent(evtEscKeyPressed);
         if ( getFlags(wflEatEscKey) )
            cmd.killMsg();
         break;
      case cwCmdChar::vkTab:
      case cwCmdChar::vkBackTab:
         onNavKey(cmd.getVirt());
         callEvent(evtNavKeyPressed, cmd.getVirt());
         if ( getFlags(wflEatNavKeys) )
            cmd.killMsg();
         break;
*/
      default: break;
      }
   }

   cwWindow::onChar(cmd);
}

bool cwControl::onDispatchChar(const cwCmdChar& cmd)
{
   if ( cmd.isVirt() && cmd.isKeyDown()  ) {
      switch ( cmd.getVirt() ) {
      case cwCmdChar::vkEnter:
      case cwCmdChar::vkReturn:
         onEnterKey();
         callEvent(evtEnterKeyPressed);
         if ( getFlags(wflEatEnterKey) )
            return false;
         break;
      case cwCmdChar::vkEsc:
         onEscapeKey();
         callEvent(evtEscKeyPressed);
         if ( getFlags(wflEatEscKey) )
            return false;
         break;
      case cwCmdChar::vkTab:
      case cwCmdChar::vkBackTab:
         onNavKey(cmd.getVirt());
         callEvent(evtNavKeyPressed, cmd.getVirt());
         if ( getFlags(wflEatNavKeys) )
            return false;
         break;
      default: break;
      }
   }

   return cwWindow::onDispatchChar(cmd);
}

bool cwControl::onAllowTurn()
{
   if ( store ) {
      switch ( onCheckCtl(store) ) {
      case derrNotNull: return onErrorNotNull();
      case derrFormat:  return onErrorFormat();
      }
   }

   return cwWindow::onAllowTurn();
}

bool cwControl::onAllowStore()
{
   if ( store ) {
      switch ( onCheckCtl(store) ) {
      case derrNotNull: return onErrorNotNull();
      case derrFormat:  return onErrorFormat();
      }
   }

   return cwWindow::onAllowStore();
}

void cwControl::onGainFocus()
{
   setFlags(wflHasFocus);
   refreshInheritedValue();

   if ( store && store->forceOverwrite() )
      setFlags(wflInsertMode, setInsertMode(FALSE));

   clearChanged();

   cwWindow::onGainFocus();
}

void cwControl::onLoseFocus()
{
   if ( store && store->forceOverwrite() )
      setInsertMode(!!getFlags(wflInsertMode));

   cwWindow::onLoseFocus();
   refreshInheritedValue();
}


// Verzoegerte Ausfuehrung
// =======================

void cwControl::onExecDelayed(int id, void *data)
{
   switch ( id ) {
   case ediSetQuery:
      execSetQuery((csQuery*)data);
      break;
   }

   cwWindow::onExecDelayed(id, data);
}

