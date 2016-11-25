// ===========================================================================
// ew_windows.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow         - Basisklasse fuer alle ECL-Windows
//
// TBD: (To be done)
//
//    - Window-Styles aller von cwWindow abgeleiteten Klassen zusammenfassen
//      und einheitlich ueber getStyles und modifyStyles zugaenglich machen
//
// ===========================================================================

#include "win/ew_windows.hpp"
#include "win/ew_application.hpp"
#include "win/ew_menus.hpp"
#include "draw/ed_font.hpp"
#include "base/eb_list.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_elo.hpp"
#include "base/eb_event.hpp"
#include "base/eb_err.hpp"
#include "win/ew_commands.hpp"


// Forward-Deklarationen
// ===========================================================================

class cwMenu;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwWindow
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloElement
//      +--cwWindow
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwWindow : public cEloElement, public cEventSource {
   ELO_DECLARE(cwWindow,cEloElement)
   friend class ccwWindow;

public:

   enum { NOVAL = -2147483647 };


   // Allgemeines
   // ===========

   // Destruktor
   virtual ~cwWindow();

   // Mit bestehendem Fenster verknuepfen
   void attach(cwWindow *parent, int id);
   // Zerstoeren des Fensters
   void destroy();

   // Fenster-ID ermitteln
   int getId() const;
   // Ist das Fenster angelegt?
   bool isCreated() const;

   // Parent des Fensters setzen
   void setParent(cwWindow *new_parent);
   // Parent des Fensters ermitteln (oder 0)
   cwWindow *getParent() const;

   // Zugeordnetes Menu setzen
   void setMenu(cwMenu *new_menu);
   // Zugeordnetes Menu ermitteln (oder 0)
   cwMenu *getMenu() const;

   // Aktives Kindfenster ermitteln (oder 0)
   cwWindow *getActiveChild() const;


   // window-Flags
   // ============

   // Flags
   enum FLAGS {
      wflNone           = 0x00000000,   // Kein Flag
      wflAutoDelete     = 0x00000001,   // Objekt automatisch 'delete'en?
      wflInNotebook     = 0x00000002,   // In Notizbuch eingefuegt?
      wflWasRefreshed   = 0x00000004,   // Refresh erfolgreich durchgefuehrt?
      wflWasAttached    = 0x00000008,   // cwWindow per Attach erzeugt?
      wflIsAView        = 0x00000010,   // Ist aktuelles Fenster ein cwView?
      wflHasFocus       = 0x00000020,   // Hat das Fenster momentan den Eingabefocus?
      wflUser           = 0x00000040,   // Offset fuer benutzerdef. Flags
      //
      // Alte Bezeichner, nicht mehr verwenden!
      wflIsSource       = 0x00000000,   // Source-Emphasis aktiviert?
      wflIsTarget       = 0x00000000,   // Target-Emphasis aktiviert?
      wflIsFrameCtl     = 0x00000000,   // Als Frame-Control eingefuegt?
      wflInClose        = 0x00000000,   // Fenster schliessen aktiv?
      wflForceRefresh   = 0x00000000,   // Refresh unbedingt notwendig?
      wflWasStored      = 0x00000000    // Store erfolgreich durchgefuehrt?
   };

   // Alle aktuellen Window-Flags ermitteln
   inline int getFlags() const
      { return flags; }
   // Bestimmte aktuelle Window-Flags ermitteln
   inline int getFlags(int mask) const
      { return flags & mask; }
   // Bestimmte Window-Flags setzen
   inline void setFlags(int mask, bool set = true)
      { onSetFlags(mask, set); }


   // window-Styles
   // =============

   // Styles
   enum STYLES {
      wsNone            = 0x00000000,  // Kein Style
      wsDisabled        = 0x00000001,  // Fenster gesperrt (keine Eingaben moeglich)
      wsVisible         = 0x00000002,  // Fenster sichtbar
      wsChild           = 0x00000004,  // Verwendung als Kind eines anderen Fensters
      wsPopup           = 0x00000008,  // Verwendung als eigenstaendiges Fensters
      wsScrollHorz      = 0x00000010,  // Fenster hat horizontalen Scrollbar
      wsScrollVert      = 0x00000020,  // Fenster hat vertikalen Scrollbar
      wsBorder          = 0x00000040,  // Fenster hat duennen Rahmen
      wsBorderThick     = 0x00000080,  // Fenster hat dicken Rahmen
      wsBorderSize      = 0x00000100,  // Fenster hat Rahmen zum Aendern der Groesse
      wsTabStop         = 0x00000200,  // Fenster hat vertikalen Scrollbar
      wsReserved1       = 0x00000400,  // Reserviert fuer Erweiterungen
      wsReserved2       = 0x00000800,  // Reserviert fuer Erweiterungen
      wsDockLeft        = 0x00001000,  // Docken links erlaubt
      wsDockRight       = 0x00002000,  // Docken rechts erlaubt
      wsDockTop         = 0x00004000,  // Docken oben erlaubt
      wsDockBottom      = 0x00008000,  // Docken unten erlaubt
      wsUser            = 0x00010000,  // Offset fuer benutzerdef. Styles
      //
      // Kombinationen:
      wsDockNone        = 0,                          // Keine Andockfenster erlaubt
      wsDockHorz        = wsDockLeft|wsDockRight,     // Docken horizontal erlaubt
      wsDockVert        = wsDockTop|wsDockBottom,     // Docken Vertikal erlaubt
      wsDockAny         = wsDockHorz|wsDockVert       // Docken ueberall erlaubt
   };

   // Aktuelle Window-Styles ermitteln
   int getStyles(int mask = ~0) const;
   // Bestimmte Window-Styles setzen (add) und ruecksetzen (remove)
   void modifyStyles(int add, int remove);


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cEventSource::evtUser,
      evtFocusGained,         // (EVFUNC)    Tastaturfokus erhalten
      evtFocusLost,           // (EVFUNC)    Tastaturfokus verloren
      evtWindowCreated,       // (EVFUNC)    Fenster erzeugt
      evtWindowDestroyed,     // (EVFUNC)    Fenster zerstoert
      evtWindowRefreshed,     // (EVFUNC)    Fensterinhalt aktualisiert
      evtWindowStored,        // (EVFUNC)    Fensterinhalt gespeichert
      evtWindowDiscarded,     // (EVFUNC)    Fensterinhalt verworfen
      evtContextMenu,         // (EVFUNC_II) Kontextmenu anzeigen
      evtUser                 // Ab hier benutzerdefinierte Events
   };

   // Benutzerdefinierte Kennung
   // ==========================

   // Setzt die benutzerdefinierte Fenster-Kennung
   void setUserId(int id);
   // Liest die benutzerdefinierte Fenster-Kennung
   int getUserId() const;


   // Window-Text
   // ===========

   // Fenstertext setzen (flacker-optimiert)
   void setText(const cString& text);
   // Fenstertext ermitteln
   cString getText() const;


   // Position/Groesse
   // ================

   // Fenster mittig zu anderem Fenster oder bildschirmmittig plazieren
   void center(cwWindow *other = NULL); // war: Center()

   // Groesse des Fensters ermitteln
   cdSize getSize() const;
   // Groesse des Arbeitsbereichs (Client) ermitteln
   cdSize getClientSize() const;

   // Position des Fensters relativ zum Screen ermitteln
   cdRect getRect() const;
   // Position des Arbeitsbereichs (Client) relativ zum Rahmen ermitteln
   cdRect getClientRect() const;

   // Groesse des Fensters aendern (Startpunkt bleibt erhalten)
   void setSize(const cdSize& size);
   // Position und Groesse des Fensters aendern
   void setRect(const cdRect& rect);


   // "Angeklebte" Fenster
   // ====================
   // Anmerkung: Momentan max. ein Fenster erlaubt und nur an stpTop

   enum STICK_POS {
      stpTop,           // Fremdfenster oben anhaengen
      stpBottom,        // - reserviert -
      stpLeft,          // - reserviert -
      stpRight          // - reserviert -
   };

   // Fenster 'win' an Position 'pos' des aktuellen Fensters "ankleben"
   void setSticky(cwWindow *win, STICK_POS pos = stpTop);
   // Zuletzt an Position 'pos' angeklebtes Fenster ermitteln
   cwWindow *getSticky(STICK_POS pos = stpTop) const;


   // Koordinaten
   // ===========

   // Punkt von Fenster- in Schirmkoordinaten umrechnen
   void convWin2Screen(cdPoint& point);
   // Rechteck von Fenster- in Schirmkoordinaten umrechnen
   void convWin2Screen(cdRect& rect);

   // Punkt von Schirm- in Fensterkoordinaten umrechnen
   void convScreen2Win(cdPoint& point);
   // Rechteck von Schirm- in Fensterkoordinaten umrechnen
   void convScreen2Win(cdRect& rect);


   // Presentation Parameter
   // ======================

   enum PPARAMS {
      ppFont,
      ppFgndColor,
      ppBkgndColor
   };

   // Presentation-Parameter (Color) setzen
   void setPresParam(PPARAMS pp, cdColor value);
   // Presentation-Parameter (String) setzen
   void setPresParam(PPARAMS pp, cString value);
   // Presentation-Paramter vom Fenster loeschen
   void removePresParam(PPARAMS pp);

   // Prueft, ob ein Presentation-Paramter gesetzt ist
   bool isPresParamSet(PPARAMS pp) const;
   // Presentation-Parameter (Color) erfragen; liefert false, falls nicht gesetzt
   bool getPresParam(PPARAMS pp, cdColor& value) const;
   // Presentation-Parameter (String) erfragen; liefert false, falls nicht gesetzt
   bool getPresParam(PPARAMS pp, cString& value) const;


   // Erlaubnisfunktionen
   // ===================
   // Liefert ein Fenster bei onAllowClose() false zurueck, wird der laufende
   // Vorgang des Schliessens unterbrochen. Durch Aufrufen der onResumeClose-
   // Methode des durch den notify-Zeiger gegebenen Fensters kann der unter-
   // brochene Vorgang fortgesetzt werden

   // Blaettern zu Sibling erlauben?
   bool allowTurn();
   // Abbruch mit Speichern erlauben?
   bool allowStore();
   // Abbruch ohne Speichern erlauben?
   bool allowDiscard();
   // Schliessen des Fensters erlauben?
   bool allowClose(cwWindow *notify);


   // Inhalt aktualisieren/speichern
   // ==============================
   // Die refresh bzw. store-Methoden der Basisklassen rufen den entspr.
   // Event onRefresh bzw. onStore aller Kindfenster auf. Falls alle
   // Kindfenster true liefern, wird das wasRefreshed- bzw. wasStored-
   // Flag gesetzt.

   // Fensterinhalt aktualisieren (false -> Abbruch)
   bool refresh();
   // Fensterinhalt (zurueck)speichern (false -> Abbruch)
   bool store();
   // Fensterinhalt verwerfen (false -> Abbruch)
   bool discard();


   // Timer
   // =====

   // Timer 'id' starten (0 < id < 10000)
   bool startTimer(int id, int ms);
   // Timer 'id' anhalten (0 < id < 10000)
   void stopTimer(int id);


   // Scrolling
   // =========

   enum BAR {
      barHorz  = cwCmdScroll::barHorz, // Kennzeichnet den horizontalen Standard-Scrollbalken
      barVert  = cwCmdScroll::barHorz  // Kennzeichnet den vertikalen Standard-Scrollbalken
   };

   // Aktuelle Position, Scrollbereich und Seitengroesse von Scrollbalken 'bar' erfragen
   bool getScrollBarInfo(BAR bar, int *pos = 0, int *min = 0, int *max = 0, int *page = 0, int *track = 0) const;
   // Scrollbereich, Seitengroesse und aktuelle Position von Scrollbalken 'bar' einstellen
   void setScrollBarInfo(BAR bar, int pos = NOVAL, int min = NOVAL, int max = NOVAL, int page = NOVAL, bool redraw = true);

   // Aktuelle statische Position des Scrollbalken 'bar' ermitteln
   inline int getScrollPos(BAR bar) const
      { int pos = 0; getScrollBarInfo(bar, &pos); return pos; }
   // Aktuelle Position des Scrollbalkens 'bar' waehrend der Benutzerinteraktion ermitteln
   inline int getScrollTrackPos(BAR bar) const
      { int track_pos = 0; getScrollBarInfo(bar, 0, 0, 0, 0, &track_pos); return track_pos; }
   // Aktuellen Minimalwert des Scrollbereichs von Scrollbalken 'bar' ermitteln
   inline int getScrollRangeMin(BAR bar) const
      { int min = 0; getScrollBarInfo(bar, 0, &min); return min; }
   // Aktuellen Maximalwert des Scrollbereichs von Scrollbalken 'bar' ermitteln
   inline int getScrollRangeMax(BAR bar) const
      { int max = 0; getScrollBarInfo(bar, 0, 0, &max); return max; }
   // Aktuellen Seitengroesse bezueglich des Scrollbereichs von Scrollbalken 'bar' ermitteln
   inline int getScrollPageSize(BAR bar) const
      { int page = 0; getScrollBarInfo(bar, 0, 0, 0, &page); return page; }

   // Statische Position von Scrollbalken 'bar' einstellen
   inline void setScrollPos(BAR bar, int pos, bool redraw = true)
      { setScrollBarInfo(bar, pos, NOVAL, NOVAL, NOVAL, redraw); }
   // Scrollbereich von Scrollbalken 'bar' einstellen
   inline void setScrollRange(BAR bar, int min, int max, bool redraw = true)
      { setScrollBarInfo(bar, NOVAL, min, max, NOVAL, redraw); }
   // Seitengroesse bezeuglich des Scrollbereichs von Scrollbalken 'bar' einstellen
   inline void setScrollPageSize(BAR bar, int page, bool redraw = true)
      { setScrollBarInfo(bar, NOVAL, NOVAL, NOVAL, page, redraw); }

   // Scrollbalken 'bar' anzeigen
   inline void showScrollBar(BAR bar)
      { setScrollBarVisible(bar, true); }
   // Scrollbalken 'bar' verbergen
   inline void hideScrollBar(BAR bar)
      { setScrollBarVisible(bar, false); }

   // Sichtbarkeit der Scrollbalken steuern (true = anzeigen; false = verbergen)
   void setScrollBarVisible(int bar_mask, bool on = true);
   // Freigabestatus der Scrollbalken steuern (true = freigeben; false = sperren)
   void setScrollBarEnable(int bar_mask, bool enable = true);

   // Client-Bereich des Fenster um 'dx' und 'dy' (in Geraetekoordinaten) scrollen
   // Scrollrichtungen: fuer 'dx': Links < 0 < Rechts, fuer 'dy': Oben < 0 < Unten
   // 'rect': Zeiger auf optionalen Scrollbereich (in Geraetekoordinaten)
   // 'clip_rect': Zeiger auf optionalen Clip-Bereich (in Geraetekoordinaten)
   void scrollWindow(int dx, int dy, const cdRect *rect = 0, const cdRect *clip_rect = 0);
   // Client-Bereich um 'dx' und 'dy' scrollen (wie oben, jedoch mit cdRect-Referenzen)
   void scrollWindow(int dx, int dy, const cdRect& rect, const cdRect& clip_rect);


   // Elemente und Operationen (ELO)
   // ==============================

   // Ermoeglicht das Fenster eine ELO-Element-Selektion?
   bool hasWindowElemSelection() const;
   // Aktuelle ELO-Element-Selektion des Fensters in 'selection' ermitteln
   // Liefert false, falls keine Selektion ermittelt werden kann
   bool updateWindowElemSelection(cEloSelection& selection) const;
   // Aktuelle ELO-Element-Selektion des Fensters in eigenes Selektionsobjekt ermitteln
   // Liefert false, falls keine Selektion ermittelt werden kann
   bool updateWindowElemSelection();
   // Zeiger auf ein aktuelles ELO-Selektionsobjekt liefern
   // Liefert 0, wenn kein eigenes Selektionsobjekt vorhanden ist
   cEloSelection *getWindowElemSelection();
   // Zeiger auf die ELO-Aktionsbeschreibung liefern
   cEloActionDescription *getWindowActionDescription(const cEloSelection *selection) const;


   // Systeminformation
   // =================

   // Groesse des Bildschirms (Aufloesung) erfragen
   static cdRect getScreenRect();
   // Groesse des Desktops (nutzbarer Bereich des Bildschirms) erfragen
   static cdRect getDesktopRect();


   // Sonstiges
   // =========
   // Die folgenden Funktionen wirken auf das aktuelle Fenster oder
   // wahlweise auf ein (direktes) Kindfenster, gegeben ueber 'child_id'

   // Fenster anzeigen
   void show(int child_id = -1);
   // Fenster verbergen
   void hide(int child_id = -1);
   // Fenster invalidieren (Neuzeichnen erzwingen)
   void invalidate(int child_id = -1, bool erase_bkgnd = true);
   // Rechteckigen Bereich (in Client-Koordinaten) invalidieren
   void invalidate(const cdRect& rect, bool erase_bkgnd = true);
   // Update ausloesen (wenn noetig)
   void update(int child_id = -1);
   // Update erzwingen (invalidate + update)
   void forceUpdate(int child_id = -1, bool erase_bkgnd = true);
   // Update auf recteckigem Bereich (in Client-Koordinaten) erzwingen
   void forceUpdate(const cdRect& rect, bool erase_bkgnd = true);
   // Fenster aktivieren
   void activate(int child_id = -1);
   // Tastaturfokus setzen und evtl. Fenster aktivieren
   void setFocus(int child_id = -1);

   // Fenstersichtbarkeit steuern (true = anzeigen; false = verbergen)
   void setVisible(bool on = true, int child_id = -1);
   // Freigabestatus steuern (true = freigeben; false = sperren)
   void setEnable(bool enable = true, int child_id = -1);
   // Redraw-Status steuern (true = zeichnen; false = nicht zeichnen)
   void setRedraw(bool redraw = true, int child_id = -1);

   // Enable-Flag erfragen
   bool isEnabled(int child_id = -1) const;
   // ??? In OS/2-Doku nachlesen!
   bool isShowing(int child_id = -1) const;
   // ??? In OS/2-Doku nachlesen!
   bool isVisible(int child_id = -1) const;

   // Kommando synchron senden
   int sendCommand(const cwCmd& cmd);
   // Kommando asynchron senden
   bool postCommand(const cwCmd& cmd);

   // Aktueller Zustand "Einfuege-Modus" (Insert-Taste) erfragen
   static bool getInsertMode();
   // Zustand fuer "Einfuege-Modus" (Insert-Taste) setzen
   static bool setInsertMode(bool value);


   // Message-Boxen
   // =============

   // Art der Message-Box
   enum MB_STYLE {
      mbsQuery,      // Fehler (Yes, No, Cancel)
      mbsInfo,       // Information (Ok)
      mbsWarning,    // Warnung (Ok)
      mbsError,      // Fehler (Ok)
      mbsErrRetry,   // Fehler (Retry, Ignore, Cancel)
      mbsFatal       // Fehler (Ok)
   };

   // Ergebnis der Message-Box-Abfrage
   enum MB_RES {
      mbrOk,         // Ok (Meldung akzeptieren)
      mbrCancel,     // Cancel (Vorgang abbrechen)
      mbrRetry,      // Retry (Vorgang wiederholen)
      mbrIgnore,     // Ignore (Fehler ignorieren, Vorgang fortsetzen)
      mbrYes,        // Yes (Frage positiv beantworten)
      mbrNo          // No (Frage negativ beantworten)
   };

   // Allgemeine Messagebox (statische Variante)
   static MB_RES showMsg(const cwWindow *owner, const cString& title, const cString& text, MB_STYLE style);
   // Information anzeigen (statische Variante)
   static MB_RES showInfo(const cwWindow *owner, const cString& text);
   // Warnung anzeigen (statische Variante)
   static MB_RES showWarning(const cwWindow *owner, const cString& text);
   // Fehlermeldung des cErrBase-Objektes anzeigen (statische Variante)
   static MB_RES showError(const cwWindow *owner, const cErrBase& err, const cString& add_info = 0);
   // Fehler anzeigen (statische Variante)
   static MB_RES showError(const cwWindow *owner, const cString& text);
   // Fatalen Fehler anzeigen (statische Variante)
   static MB_RES showFatal(const cwWindow *owner, const cString& text);
   // Rueckfrage anzeigen (statische Variante)
   static MB_RES showQuery(const cwWindow *owner, const cString& text);

   // Allgemeine Messagebox (fenstergebundene Variante)
   inline MB_RES showMsg(const cString& title, const cString& text, MB_STYLE style) const
      { return showMsg(this, title, text, style); }
   // Information anzeigen (fenstergebundene Variante)
   inline MB_RES showInfo(const cString& text) const
      { return showInfo(this, text); }
   // Warnung anzeigen (fenstergebundene Variante)
   inline MB_RES showWarning(const cString& text) const
      { return showWarning(this, text); }
   // Fehlermeldung des cErrBase-Objektes anzeigen (statische Variante)
   inline MB_RES showError(const cErrBase& err, const cString& add_info = 0)
      { return showError(this, err, add_info); }
   // Fehler anzeigen (fenstergebundene Variante)
   inline MB_RES showError(const cString& text) const
      { return showError(this, text); }
   // Fatalen Fehler anzeigen (fenstergebundene Variante)
   inline MB_RES showFatal(const cString& text) const
      { return showFatal(this, text); }
   // Rueckfrage anzeigen (fenstergebundene Variante)
   inline MB_RES showQuery(const cString& text) const
      { return showQuery(this, text); }


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, um bestimmte Window-Flags zu setzen
   virtual void onSetFlags(int mask, bool set);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   virtual int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   virtual void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   virtual void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);

   // Fenster wird erzeugt
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   virtual bool onCreate();
   // Fenstererzeugung wird vorbereitet
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   virtual bool onPreCreate(void *add_data);
   // Attach mit Wrapper-Objekt durchfuehren
   virtual void onAttach(int id, void *wnd);
   // Fenster wird zerstoert
   virtual void onDestroy();
   // Groesse geaendert
   virtual void onSize(int cx, int cy);
   // Taste gedrueckt
   virtual void onChar(cwCmdChar& cmd);
   // Maustaste gedrueckt
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   virtual bool onMouseClick(const cwCmdMouse& cmd);
   // Mausbewegung
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   virtual bool onMouseMove(const cwCmdMouse& cmd);
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   virtual bool onCommand(const cwCmdEvt& cmd); // war:
   // Update Benutzerschnittstelle
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   virtual bool onCommandUI(cwCmdUI& cmd);
   // Kontextmenu anzeigen
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   virtual bool onContextMenu(const cwCmdPosition& cmd);
   // Wird aufgerufen, wenn eine Aktion an einem Scrollbar ausgeloest wurde
   virtual void onScroll(const cwCmdScroll& cmd);

   // Entscheiden, ob das cwCmdChar-Kommando weiterverteilt werden soll
   virtual bool onDispatchChar(const cwCmdChar& cmd);
   // Entscheiden, ob das cwCmdMouse-Kommando weiterverteilt werden soll
   virtual bool onDispatchMouseClick(const cwCmdMouse& cmd);

   // Wird aufgerufen, wenn Fenster den Focus erhaelt
   virtual void onGainFocus();
   // Wird aufgerufen, wenn Fenster den Focus verliert
   virtual void onLoseFocus();

   // Wird aufgerufen, wenn ein Kindfenster den Focus erhaelt
   virtual void onChildActivated(cwWindow *win);

   // Inhalt refreshen (false -> Abbruch)
   virtual bool onRefresh(); // war: RefreshEvt()
   // Inhalt speichern (false -> Abbruch)
   virtual bool onStore(); // war: StoreEvt()
   // Inhalt verwerfen (false -> Abbruch)
   virtual bool onDiscard();
   // Beenden eines unterbrochenen "Schliessen"-Vorgangs
   virtual void onResumeClose(); // war: ResumeClose

   // Blaettern zu Sibling erlauben?
   virtual bool onAllowTurn(); // war: AllowTurnEvt()
   // Abbruch mit Speichern erlauben?
   virtual bool onAllowStore(); // war: AllowStoreEvt()
   // Abbruch ohne Speichern erlauben?
   virtual bool onAllowDiscard(); // war: AllowDiscardEvt()
   // Schliessen des Fensters erlauben?
   virtual bool onAllowClose(cwWindow *notify); // war: AllowCloseEvt()

   // Wird aufgerufen, wenn Timer 'id' ablaeuft (true -> Timer anhalten)
   virtual bool onTimer(int id);

   // Wird aufgerufen, wenn eine Drag-Operation das Fenster erreicht
   virtual bool onDragEnter(cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation ueber dem Fenster ablaeuft
   virtual bool onDragOver(cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Scroll-Operation ueber dem Fenster ablaeuft
   virtual bool onDragScroll(cwCmdDrag& cmd);
   // Wird aufgerufen, wenn eine Drag-Operation das Fenster verlaesst
   virtual bool onDragLeave();
   // Wird aufgerufen, wenn ein Drop ueber dem Fenster veranlasst wurde
   virtual bool onDrop(cwCmdDrop& cmd);

   // Wird aufgerufen, wenn sich der Presentation-Parameter 'pp' geaendert hat
   virtual void onPresParamChanged(PPARAMS pp);
   // Wird aufgerufen, wenn der Presentation-Parameter 'pp' entfernt wurde
   virtual void onPresParamRemoved(PPARAMS pp);

   // Wird aufgerufen, um zu erfragen, ob eine Element-Selektion moeglich ist
   virtual bool onHasWindowElemSelection() const;
   // Wird aufgerufen, um die aktuelle Element-Selektion zu ermitteln
   virtual bool onUpdateWindowElemSelection(cEloSelection& selection) const;
   // Wird aufgerufen, um den Zeiger auf ein aktuelles Selektionsobjekt zu ermitteln
   virtual cEloSelection *onGetWindowElemSelection();
   // Wird aufgerufen, um den Zeiger auf die ELO-Aktionsbeschreibung zu ermitteln
   virtual cEloActionDescription *onGetWindowActionDescription(const cEloSelection *selection) const;


   // Verzoegerte Ausfuehrung
   // =======================

   enum  { ediStart = 0,
      ediUser,          // ab hier Erweiterungen
   };

   // Operation verzoegert ausfuehren (0 <= id < 10000)
   void execDelayed(int id, void *data = 0, int ms_delay = -1);
   // Verzoegertes Ausfuehren einer Operation
   virtual void onExecDelayed(int id, void *data);


protected:
   void *_wnd;       // Zeiger auf Wrapper-Objekt


   // ECL/win Internas
   // ================
   // Die 'create'- bzw. 'attach'-Methoden aller abgeleiteten Klassen
   // muessen diese Basisvarianten in cwWindow aufrufen!

   // Interner Konstruktor
   cwWindow(void *wnd);
   // Erzeugen des Fensters (Intern)
   void create(cwWindow *parent);

   // Trennen vom Wrapper
   void __disconnect();
   // Eigenen Zeiger auf Wrapper-Objekt ermitteln
   void *__getWnd();
   const void *__getWnd() const;
   // Zeiger auf Wrapper-Objekt ermitteln
   static void *__getWnd(cwWindow *window);
   static const void *__getWnd(const cwWindow *window);

   // Verzoegertes Attachieren...
   void __attachDelayed();
   // Presentation Parameter erfragen
   void *__getPresParam();
   // Aktives Kindfenster setzen
   void __setActive(cwWindow *wnd);


private:

   // Aktuelle Window-Flags
   int flags;

   // Zusatzinformationen
   struct ADD_INFO;
   ADD_INFO *info;


public:

   // Alter Bezeichner fuer getRect, nicht mehr benutzen!
   inline cdRect getPos() const { return getRect(); }
   // Alter Bezeichner fuer getClientRect, nicht mehr benutzen!
   inline cdRect getClientPos() const { return getClientRect(); }
   // Alter Bezeichner fuer setRect, nicht mehr benutzen!
   inline void setPos(const cdRect& rect) { setRect(rect); }

};

#endif /*__INTERFACE__*/


// Implementierung cwWindow
// ===========================================================================

#define __Trace_Win_Calls__
#if defined __Trace_Win_Calls__ && __ECL_DEBUG__ > 0
   #define TRACEWIN(p) cBase::DbgTrcWin p
   #define IGN(p) p
#else
   #define TRACEWIN(p)
   #define IGN(p)
#endif

struct ATTACH { int id; cwWindow *child; };
typedef cList<ATTACH,const ATTACH&> ATTACH_LIST;

struct cwWindow::ADD_INFO {
   ADD_INFO();             // Konstruktor
   ~ADD_INFO();            // Destruktor

   int extra_id;           // Benutzerdefinierte Kennung
   ATTACH_LIST attaches;   // Liste der verzoegerten Attaches
   cwWindow *parent;       // Zeiger auf das Parent-Fenster (oder 0)
   cwWindow *active;       // Zeiger auf das aktive Kind-Fenster (oder 0)
   cwWindow *sticky;       // "Angeklebtes" Fenster
   cwMenu *menu;           // Zugeordnetes Menu
#if defined __ECL_W32__
   ccwWindow::PP pp;       // Presentation Parameter
   cString pp_font;        // PP Fontname
#endif
};

cwWindow::ADD_INFO::ADD_INFO()
{
   extra_id = 0;
   parent = active = sticky = 0;
   menu = 0;
   #if defined __ECL_W32__
      pp.mask = 0;
   #endif
}

cwWindow::ADD_INFO::~ADD_INFO()
{
   delete menu; menu = 0;
}

// ---

cwWindow::cwWindow(void *wnd)
{
   flags = 0;
   _wnd = wnd;
   info = new ADD_INFO;
}

cwWindow::~cwWindow()
{
   setFlags(wflAutoDelete, false);  // Jetzt ist es zu spaet fuer ein Auto-Delete...
   info->attaches.removeAll();  // ... und auch zu spaet zum Attachieren
   info->parent = 0;
   info->active = 0;
   info->sticky = 0;

   if ( _wnd && !getFlags(wflWasAttached) )
      destroy();

   #if defined __ECL_W32__
      // Cast zu (CObject*), damit _free_dbg() den korrekten Blocktyp erkennt
      delete (CObject*)_wnd;
   #elif defined __ECL_OS2__
      delete _wnd;
   #endif

   delete info;
   info = 0;
}

void cwWindow::create(cwWindow *parent)
{
   __ECL_ASSERT1__(parent != 0);
   info->parent = parent;
}

void cwWindow::attach(cwWindow *parent, int id)
{
   __ECL_ASSERT1__(_wnd != 0);
   __ECL_ASSERT1__(parent != 0);

   info->parent = parent;

   bool delay_attach = false;
   setFlags(wflWasAttached);

   #if defined __ECL_W32__

      WCWnd *wp = (WCWnd*)parent->_wnd;

      if ( wp->m_hWnd == 0 ) {
         delay_attach = true;
      } else {
         // Nach dem Attachieren noch onCreate aufrufen, damit das Fenster aus ECL-
         // Sicht einen moeglichst "natuerlichen" Erzeugungsvorgang durchlaeuft:
         onAttach(id, wp);
         onCreate();
      }

   #elif defined __ECL_OS2__

      // ???

   #endif

   // Noch kein create() beim Parent durchgefuehrt?
   // Dann attach() verzoegern...

   if ( delay_attach ) {
      ATTACH at; at.id = id; at.child = this;
      parent->info->attaches.addHead(at);
   }
}

void cwWindow::__attachDelayed()
{
   __ECL_ASSERT1__(_wnd != 0);

   for ( IPOSITION pos = info->attaches.getHeadPosition() ; pos ; ) {
      ATTACH at = info->attaches.getNext(pos);

      #if defined __ECL_W32__
         // Nach dem Attachieren noch onCreate aufrufen, damit das Fenster aus ECL-
         // Sicht einen moeglichst "natuerlichen" Erzeugungsvorgang durchlaeuft:
         at.child->onAttach(at.id, _wnd);
         at.child->onCreate();
      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   info->attaches.removeAll();
}

void cwWindow::onAttach(int id, void *wnd)
{
   #if defined __ECL_W32__
      WCWnd *wcwnd = (WCWnd*)wnd;
      BOOL ok = ((WCWnd*)_wnd)->SubclassDlgItem(id, wcwnd);
      __ECL_ASSERT2__(ok, ("Could not subclass control %d", id));
   #elif defined __ECL_OS2__
   #endif
}

void cwWindow::destroy()
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      if ( isCreated() ) {
         BOOL ok = ((WCWnd*)_wnd)->DestroyWindow();
         __ECL_ASSERT2__(ok, ("Could not destroy window"));
      }
   #elif defined __ECL_OS2__
   #endif
}

int cwWindow::getId() const
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      return ((CWnd *)_wnd)->GetDlgCtrlID();
   #elif defined __ECL_OS2__
      return ...;
   #endif
}

bool cwWindow::isCreated() const
{
   #if defined __ECL_W32__
      return _wnd != 0 && ((WCWnd *)_wnd)->m_hWnd != 0;
   #elif defined __ECL_OS2__
      return ...;
   #endif
}

void cwWindow::setParent(cwWindow *new_parent)
{
   info->parent = new_parent;

   if ( _wnd != 0 ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = (CWnd*)_wnd;
         CWnd *mfc_parent = (CWnd*)cwWindow::__getWnd(new_parent);
         if ( mfc_wnd && mfc_wnd->m_hWnd && mfc_parent && mfc_parent->m_hWnd ) {
            mfc_wnd->SetParent(mfc_parent);
         }
      #else
         // ...
      #endif
   }
}

cwWindow * cwWindow::getParent() const
{
   return info != 0 ? info->parent : 0;
}

cwWindow * cwWindow::getActiveChild() const
{
   return info != 0 ? info->active : 0;
}

void cwWindow::__setActive(cwWindow *wnd)
{
   info->active = wnd;
}

void cwWindow::setMenu(cwMenu *new_menu)
{
   // Abfrage verhindert das Loeschen des zu setztenden Menus, falls Neu == Alt

   if ( new_menu != info->menu ) {
      delete info->menu;
      info->menu = new_menu;
   }
}

cwMenu * cwWindow::getMenu() const
{
   return info->menu;
}


// window-Styles
// =============

int cwWindow::getStyles(int mask) const
{
   return onGetStyles(mask);
}

void cwWindow::modifyStyles(int add, int remove)
{
   #if defined __ECL_W32__

      // Win32: Index: 0 = Window Style, 1 = Window Style Ex
      int os_add[2] = { 0, 0 };
      int os_remove[2] = { 0, 0 };

      onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // OS2: Index 0 = Window Style
      int os_add[1] = { 0 };
      int os_remove[1] = { 0 };

      onModifyStyles(add, remove, os_add, os_remove);

   #endif
}


// Benutzerdefinierte Kennung
// ==========================

void cwWindow::setUserId(int id)
{
   info->extra_id = id;
}

int cwWindow::getUserId() const
{
   return info->extra_id;
}


// Text
// ====

void cwWindow::setText(const cString& text)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {

      #if defined __ECL_W32__

         if ( ((WCWnd*)_wnd)->m_hWnd != 0 ) {

            int prev = 0;
            int curr = text.getPos("\n");

            if ( curr < 0 ) {
               ((WCWnd*)_wnd)->SetWindowText(text);
            } else {
               // String enthaelt Newlines. Fuer das eher DOS-orientierte
               // Windows(r)(tm) muessen diese in die klassischen CRLF-
               // Sequenzen umgewandelt werden.
               // TBD: Das kann man sicher auch effizienter machen!
               cString new_text;
               do {
                  if ( curr == 0 ) {
                     new_text = "\r\n";
                  } else if ( text[curr-1] == '\r' ) {
                     new_text += text.getSubstr(prev, curr);
                  } else {
                     new_text += text.getSubstr(prev, curr-1) + "\r\n";
                  }
                  prev = curr + 1;
                  curr = text.getPos("\n", prev);
               } while ( curr >= 0 );
               ((WCWnd*)_wnd)->SetWindowText(new_text + text.getMid(prev));
            }

         }

      #elif defined __ECL_OS2__

         if ( !text )
            text = "";

         char old_text[1024];

         old_text[0] = '\0'; /* fuer Fehlerfaelle */
         GetText(old_text, sizeof old_text);

         if ( strcmp(text, old_text) != 0 )
            WinSetWindowText(hwnd, text);

      #endif

   }
}

cString cwWindow::getText() const
{
   cString text;

   if ( __ECL_ASSERT1__(_wnd != 0) ) {

      #if defined __ECL_W32__

         if ( ((WCWnd*)_wnd)->m_hWnd != 0 ) {

            int text_len = ((WCWnd*)_wnd)->GetWindowTextLength();

            char *strbuf = text.lockBuffer(text_len);
            ((WCWnd*)_wnd)->GetWindowText(strbuf, text_len + 1);
            text.unlockBuffer();

            int curr = text.getPos("\r\n");

            if ( curr >= 0 ) {
               // String enthaelt CRLF-Sequenzen. Fuer die eher Unix-orientierte
               // ECL muessen diese in Newlines zurueckgewandelt werden.
               // TBD: Das kann man sicher auch effizienter machen!
               do {
                  text = text.del(curr, 1);
                  curr = text.getPos("\r\n", curr);
               } while ( curr > 0 );
            }

         }

      #elif defined __ECL_OS2__

         size_t text_len = GetTextLength();

         char *strbuf = text.lockBuffer(text_len);
         GetText(strbuf, text_len + 1);
         text.unlockBuffer();

      #endif

   }

   return text;
}


// Position/Groesse
// ================

void cwWindow::center(cwWindow *other)
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      ((WCWnd*)_wnd)->CenterWindow(other ? (CWnd*)other->__getWnd() : (CWnd*)0);
   #elif defined __ECL_OS2__
      // ???
   #endif
}

cdSize cwWindow::getSize() const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         RECT rect;
         ((WCWnd*)_wnd)->GetWindowRect(&rect);
         return cdSize(rect.right - rect.left, rect.bottom - rect.top);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   return cdSize();
}

cdSize cwWindow::getClientSize() const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         RECT rect;
         ((WCWnd*)_wnd)->GetClientRect(&rect);
         return cdSize(rect.right - rect.left, rect.bottom - rect.top);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   return cdSize();
}

cdRect cwWindow::getRect() const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         RECT rect;
         ((WCWnd*)_wnd)->GetWindowRect(&rect);
         return cdRect(rect.left, rect.bottom, rect.right, rect.top);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   return cdRect();
}

cdRect cwWindow::getClientRect() const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         RECT rect;
         ((WCWnd*)_wnd)->GetClientRect(&rect);
         return cdRect(rect.left, rect.bottom, rect.right, rect.top);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   return cdRect();
}

void cwWindow::setSize(const cdSize& /*size*/)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         __ECL_ASSERT2__(0, ("cwWindow::setSize() not yet implemented"));
      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::setRect(const cdRect& rect)
{
   cdRect new_rect = rect;

   if ( info->sticky != 0 ) {
      cdRect s_rect = info->sticky->getRect();
      int height = s_rect.getHeight();
      s_rect.lb.x = rect.lb.x;
      s_rect.rt.x = rect.rt.x;
      s_rect.lb.y = rect.rt.y + height;
      s_rect.rt.y = rect.rt.y;
      cBase::DbgOut(0, "setRect/st: rect=(left=%d right=%d top=%d bottom=%d)", s_rect.lb.x, s_rect.rt.x, s_rect.rt.y, s_rect.lb.y);
      info->sticky->setPos(s_rect);
      new_rect.rt.y = rect.rt.y + height + 1;
      cBase::DbgOut(0, "setRect:    rect=(left=%d right=%d top=%d bottom=%d)", new_rect.lb.x, new_rect.rt.x, new_rect.rt.y, new_rect.lb.y);
   }

   if ( __ECL_ASSERT1__(_wnd != 0) ) {

      #if defined __ECL_W32__
         CRect mfc_rect(CPoint(new_rect.lb.x, new_rect.rt.y), CPoint(new_rect.rt.x, new_rect.lb.y));
         if ( new_rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;
         ((CWnd*)_wnd)->MoveWindow(mfc_rect);
      #elif defined __ECL_OS2__
         // ???
      #endif

   }

}


// "Angeklebte" Fenster
// ====================

void cwWindow::setSticky(cwWindow *win, STICK_POS)
{
   cdSize win_size = getSize();
   if ( info->sticky != 0 )
      win_size.cy += info->sticky->getSize().cy;

   cwWindow *parent = getParent();

   info->sticky = win;
   info->sticky->setParent(parent);

   cdRect win_pos = getRect();
   if ( parent != 0 )
      parent->convScreen2Win(win_pos);

   win_pos.rt.x = win_pos.lb.x + win_size.cx - 1;
   win_pos.lb.y = win_pos.rt.y + win_size.cy - 1;

   setRect(win_pos);
}

cwWindow * cwWindow::getSticky(STICK_POS) const
{
   return info->sticky;
}


// Koordinaten
// ===========

void cwWindow::convWin2Screen(cdPoint& point)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         POINT mfc_point = { point.x, point.y };
         ((WCWnd*)_wnd)->ClientToScreen(&mfc_point);
         point.x = mfc_point.x;
         point.y = mfc_point.y;
      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::convWin2Screen(cdRect& rect)
{
   convWin2Screen(rect.lb);
   convWin2Screen(rect.rt);
}

void cwWindow::convScreen2Win(cdPoint& point)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         POINT mfc_point = { point.x, point.y };
         ((WCWnd*)_wnd)->ScreenToClient(&mfc_point);
         point.x = mfc_point.x;
         point.y = mfc_point.y;
      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::convScreen2Win(cdRect& rect)
{
   convScreen2Win(rect.lb);
   convScreen2Win(rect.rt);
}


// Presentation Parameter
// ======================

void cwWindow::setPresParam(PPARAMS pp, cdColor value)
{
   #if defined __ECL_W32__
      switch ( pp ) {
      case ppFgndColor:    info->pp.fg_col = value.getOsValRGB(); break;
      case ppBkgndColor:   info->pp.bg_col = value.getOsValRGB(); break;
      default:             cBase::DbgError("Unsupported PP %d\n", pp); return;
      }
      info->pp.mask |= (1 << pp);
      onPresParamChanged(pp);
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwWindow::setPresParam(PPARAMS pp, cString value)
{
   #if defined __ECL_W32__
      if ( pp == ppFont ) {
         info->pp.mask |= (1 << pp);
         info->pp_font = value;
         onPresParamChanged(pp);
      } else {
         cBase::DbgError("Unsupported PP %d\n", pp); return;
      }
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwWindow::removePresParam(PPARAMS pp)
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      if ( isPresParamSet(pp) ) {
         info->pp.mask &= ~(1 << pp);
         onPresParamRemoved(pp);
      }
   #elif defined __ECL_OS2__
      // ...
   #endif
}

bool cwWindow::isPresParamSet(PPARAMS pp) const
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      return !!(info->pp.mask & (1 << pp));
   #elif defined __ECL_OS2__
      // ...
   #endif
}

bool cwWindow::getPresParam(PPARAMS pp, cdColor& value) const
{
   __ECL_ASSERT1__(_wnd != 0);

   if ( isPresParamSet(pp) ) {
      #if defined __ECL_W32__
         unsigned long rgb;
         switch ( pp ) {
         case ppFgndColor:    rgb = info->pp.fg_col; break;
         case ppBkgndColor:   rgb = info->pp.bg_col; break;
         default:             cBase::DbgError("Unsupported PP %d\n", pp); return false;
         }
         value = cdColor(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
      #elif defined __ECL_OS2__
         // ...
      #endif

      return true;
   }

   return false;
}

bool cwWindow::getPresParam(PPARAMS pp, cString& value) const
{
   __ECL_ASSERT1__(_wnd != 0);

   if ( isPresParamSet(pp) ) {
      #if defined __ECL_W32__
         if ( pp == ppFont ) {
            value = info->pp_font;
            return true;
         } else {
            cBase::DbgError("Unsupported PP %d\n", pp);
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   return false;
}

void * cwWindow::__getPresParam()
{
   #if defined __ECL_W32__
      return &info->pp;
   #else
      return 0;
   #endif
}


// Erlaubnisfunktionen
// ===================

bool cwWindow::allowTurn()
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      bool ok = true;
      ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_ALLOW_TURN, 0, (LONG)&ok);
      return ok;
   #elif defined __ECL_OS2__
      // ???
      return true;
   #endif
}

bool cwWindow::allowStore()
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      bool ok = true;
      ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_ALLOW_STORE, 0, (LONG)&ok);
      return ok;
   #elif defined __ECL_OS2__
      // ???
      return true;
   #endif
}

bool cwWindow::allowDiscard()
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      bool ok = true;
      ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_ALLOW_DISCARD, 0, (LONG)&ok);
      return ok;
   #elif defined __ECL_OS2__
      // ???
      return true;
   #endif
}

bool cwWindow::allowClose(cwWindow * /*notify*/)
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      bool ok = true;
      ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_ALLOW_CLOSE, 0, (LONG)&ok);
      return ok;
   #elif defined __ECL_OS2__
      // ???
      return true;
   #endif
}


// Inhalt aktualisieren/speichern
// ==============================

bool cwWindow::refresh()
{
   bool ok = true;

   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         if ( ((CWnd*)_wnd)->m_hWnd != 0 ) { // Refresh-Versuch vor 'attach' abfangen
            #ifdef __Vor_2001_07_15__
               ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_REFRESH, 0, (LONG)&ok);
               if ( ok ) ok = onRefresh();
            #elif defined __Vor_2001_08_12__
               ok = onRefresh();
               if ( ok ) ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_REFRESH, 0, (LONG)&ok);
            #else
               // SendNotify, da Refresh-Versuch auch aus nicht hWnd-Thread moeglich!
               SendNotifyMessage(((WCWnd*)_wnd)->m_hWnd, WM_ECL_REFRESH, 0, 0);
            #endif
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   if ( ok )
      callEvent(evtWindowRefreshed);

   return ok;
}

bool cwWindow::store()
{
   bool ok = true;

   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_STORE, 0, (LONG)&ok);
         if ( ok ) ok = onStore();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   if ( ok )
      callEvent(evtWindowStored);

   return ok;
}

bool cwWindow::discard()
{
   bool ok = true;

   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((CWnd*)_wnd)->SendMessageToDescendants(WM_ECL_DISCARD, 0, (LONG)&ok);
         if ( ok ) ok = onDiscard();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   if ( ok )
      callEvent(evtWindowDiscarded);

   return ok;
}


// Timer
// =====

bool cwWindow::startTimer(int id, int ms)
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      return ((WCWnd*)_wnd)->SetTimer(id, ms, 0) != 0;
   #elif defined __ECL_OS2__
      return false;
   #endif
}

void cwWindow::stopTimer(int id)
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      ((WCWnd*)_wnd)->KillTimer(id);
   #elif defined __ECL_OS2__
      return false;
   #endif
}


// Scrolling
// =========

bool cwWindow::getScrollBarInfo(BAR bar, int *pos, int *min, int *max, int *page, int *track) const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__

         WCWnd *wnd = (WCWnd*)_wnd;
         SCROLLINFO si; memset(&si, 0, sizeof si);

         if ( pos != 0 )
            si.fMask |= SIF_POS;
         if ( min != 0 && max != 0 )
            si.fMask |= SIF_RANGE;
         if ( page != 0 )
            si.fMask |= SIF_PAGE;
         if ( track != 0 )
            si.fMask |= SIF_TRACKPOS;

         if ( wnd->GetScrollInfo(bar == barHorz ? SB_HORZ : SB_VERT, &si, si.fMask) ) {
            if ( pos != 0 )
               *pos = si.nPos;
            if ( min != 0 )
               *min = si.nMin;
            if ( max != 0 )
               *max = si.nMax;
            if ( page != 0 )
               *page = si.nPage;
            if ( track != 0 )
               *track = si.nTrackPos;
            return true;
         }

      #elif defined __ECL_OS2__
         // ???
      #endif
   }

   return false;
}

void cwWindow::setScrollBarInfo(BAR bar, int pos, int min, int max, int page, bool redraw)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__

         WCWnd *wnd = (WCWnd*)_wnd;
         SCROLLINFO si; memset(&si, 0, sizeof si);
         si.cbSize = sizeof si;

         if ( min != NOVAL && max != NOVAL ) {
            si.nMin = min; si.nMax = max;
            si.fMask |= SIF_RANGE;
         }

         if ( page != NOVAL ) {
            si.nPage = page;
            si.fMask |= SIF_PAGE;
         }

         if ( pos != NOVAL ) {
            si.nPos = pos;
            si.fMask |= SIF_POS;
         }

         wnd->SetScrollInfo(bar == barHorz ? SB_HORZ : SB_VERT, &si, redraw);

      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::setScrollBarVisible(int bar_mask, bool on)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCWnd *wnd = (WCWnd*)_wnd;
         UINT mfc_mask = 0;
         if ( bar_mask & barHorz )
            mfc_mask |= SB_HORZ;
         if ( bar_mask & barVert )
            mfc_mask |= SB_VERT;
         wnd->ShowScrollBar(mfc_mask, on);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::setScrollBarEnable(int bar_mask, bool enable)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCWnd *wnd = (WCWnd*)_wnd;
         if ( bar_mask & barHorz )
            wnd->EnableScrollBar(SB_HORZ, enable);
         if ( bar_mask & barVert )
            wnd->EnableScrollBar(SB_VERT, enable);
      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::scrollWindow(int dx, int dy, const cdRect *rect, const cdRect *clip_rect)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__

         WCWnd *wnd = (WCWnd*)_wnd;
         bool has_rect, has_clip;
         RECT mfc_rect, mfc_clip;

         if ( (has_rect = rect != 0) != false ) {
            mfc_rect.left   = rect->lb.x;
            mfc_rect.bottom = rect->lb.y;
            mfc_rect.right  = rect->rt.x;
            mfc_rect.top    = rect->rt.y;
         }

         if ( (has_clip = clip_rect != 0) != false ) {
            mfc_clip.left   = clip_rect->lb.x;
            mfc_clip.bottom = clip_rect->lb.y;
            mfc_clip.right  = clip_rect->rt.x;
            mfc_clip.top    = clip_rect->rt.y;
         }

         wnd->ScrollWindow(dx, dy, has_rect ? &mfc_rect : NULL, has_clip ? &mfc_clip : NULL);

      #elif defined __ECL_OS2__
         // ???
      #endif
   }
}

void cwWindow::scrollWindow(int dx, int dy, const cdRect& rect, const cdRect& clip_rect)
{
   scrollWindow(dx, dy, &rect, &clip_rect);
}


// Elemente und Operationen (ELO)
// ==============================

bool cwWindow::hasWindowElemSelection() const
{
   return onHasWindowElemSelection();
}

bool cwWindow::updateWindowElemSelection(cEloSelection& selection) const
{
   return onUpdateWindowElemSelection(selection);
}

bool cwWindow::updateWindowElemSelection()
{
   cEloSelection *selection = getWindowElemSelection();
   return selection != 0 ?
      updateWindowElemSelection(*selection)
    : false;
}

cEloSelection * cwWindow::getWindowElemSelection()
{
   return onGetWindowElemSelection();
}

cEloActionDescription * cwWindow::getWindowActionDescription(const cEloSelection *selection) const
{
   return onGetWindowActionDescription(selection);
}


// Systeminformation
// =================

cdRect cwWindow::getScreenRect()
{
   #if defined __ECL_W32__
      return cdRect(0, GetSystemMetrics(SM_CYFULLSCREEN)-1, GetSystemMetrics(SM_CXFULLSCREEN)-1, 0);
   #elif defined __ECL_OS2__
      return cdRect();
   #endif
}

cdRect cwWindow::getDesktopRect()
{
   #if defined __ECL_W32__
      RECT rect;
      SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
      return cdRect(rect.left, rect.bottom, rect.right, rect.top);
   #elif defined __ECL_OS2__
      return cdRect();
   #endif
}


// Sonstiges
// =========

void cwWindow::show(int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
            CFrameWnd *mfc_frame = mfc_wnd->GetParentFrame();
            if ( mfc_wnd->IsKindOf(RUNTIME_CLASS(CControlBar)) && mfc_frame != 0 ) {
               CControlBar *mfc_bar = DYNAMIC_DOWNCAST(CControlBar, mfc_wnd);
               mfc_frame->ShowControlBar(mfc_bar, TRUE, FALSE);
            } else {
               mfc_wnd->ShowWindow(SW_SHOW);
            }
         }
      #elif defined __ECL_OS2__
         WinShowWindow(hwnd, true);
      #endif
   }
}

void cwWindow::hide(int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
            CFrameWnd *mfc_frame = mfc_wnd->GetParentFrame();
            if ( mfc_wnd->IsKindOf(RUNTIME_CLASS(CControlBar)) && mfc_frame != 0 ) {
               CControlBar *mfc_bar = DYNAMIC_DOWNCAST(CControlBar, mfc_wnd);
               mfc_frame->ShowControlBar(mfc_bar, FALSE, FALSE);
            } else {
               mfc_wnd->ShowWindow(SW_HIDE);
            }
         }
      #elif defined __ECL_OS2__
         WinShowWindow(hwnd, false);
      #endif
   }
}

void cwWindow::invalidate(int child_id, bool erase_bkgnd)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) )
            mfc_wnd->Invalidate(erase_bkgnd);
      #elif defined __ECL_OS2__
         WinInvalidateWindow(hwnd);
      #endif
   }
}

void cwWindow::invalidate(const cdRect& rect, bool erase_bkgnd)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = (CWnd*)_wnd;
         CRect mfc_rect(rect.lb.x, rect.rt.y, rect.rt.x, rect.lb.y);
         mfc_wnd->InvalidateRect(mfc_rect, erase_bkgnd);
      #elif defined __ECL_OS2__
         WinInvalidateWindow(hwnd);
      #endif
   }
}

void cwWindow::update(int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) )
            mfc_wnd->UpdateWindow();
      #elif defined __ECL_OS2__
         WinUpdateWindow(hwnd);
      #endif
   }
}

void cwWindow::forceUpdate(int child_id, bool erase_bkgnd)
{
   invalidate(child_id, erase_bkgnd);
   update(child_id);
}

void cwWindow::forceUpdate(const cdRect& rect, bool erase_bkgnd)
{
   invalidate(rect, erase_bkgnd);
   update();
}

void cwWindow::activate(int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) )
            mfc_wnd->SetActiveWindow();
      #elif defined __ECL_OS2__
         if ( WinQueryActiveWindow(HWND_DESKTOP) != hwnd )
            WinSetActiveWindow(HWND_DESKTOP, hwnd);
         #define __Use_PostMsg_In_SetActive__
         #ifdef __Use_PostMsg_In_SetActive__
            return PostMsg(WM_ACTIVATE, 1, hwnd);
         #else
            return TRUE;
         #endif
      #endif
   }
}

void cwWindow::setFocus(int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) )
            mfc_wnd->SetFocus();
      #elif defined __ECL_OS2__
         if ( WinQueryFocus(HWND_DESKTOP) != hwnd )
            WinSetFocus(HWND_DESKTOP, hwnd);
      #endif
   }
}

void cwWindow::setVisible(bool on, int child_id)
{
   if ( on) {
      show(child_id);
   } else {
      hide(child_id);
   }
}

void cwWindow::setEnable(bool enable, int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) )
            mfc_wnd->EnableWindow(enable);
      #elif defined __ECL_OS2__
         WinEnableWindow(hwnd, enable);
      #endif
   }
}

void cwWindow::setRedraw(bool redraw, int child_id)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         if ( __ECL_ASSERT1__(mfc_wnd != 0) )
            mfc_wnd->SetRedraw(redraw);
      #elif defined __ECL_OS2__
         WinEnableWindowUpdate(hwnd, update);
      #endif
   }
}

bool cwWindow::isEnabled(int child_id) const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         return mfc_wnd != 0 ?
            !!mfc_wnd->IsWindowEnabled()
          : false;
      #elif defined __ECL_OS2__
         return WinIsWindowEnabled(hwnd);
      #endif
   }

   return false;
}

bool cwWindow::isShowing(int child_id) const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         return mfc_wnd != 0 ?
            !!mfc_wnd->IsWindowVisible()
          : false;
      #elif defined __ECL_OS2__
         return WinIsWindowShowing(hwnd);
      #endif
   }

   return false;
}

bool cwWindow::isVisible(int child_id) const
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         CWnd *mfc_wnd = child_id < 0 ? (CWnd*)_wnd : ((CWnd*)_wnd)->GetDlgItem(child_id);
         return mfc_wnd != 0 ?
            !!mfc_wnd->IsWindowVisible()
          : false;
      #elif defined __ECL_OS2__
         return WinIsWindowVisible(hwnd);
      #endif
   }

   return false;
}

// ---

int cwWindow::sendCommand(const cwCmd& cmd)
{
   // Kann notfalls auch ueber this == 0 aufgerufen werden!

   if ( __ECL_ASSERT1__(this != 0 && _wnd != 0) ) {
      ccwCmd c(cmd);
      #if defined __ECL_W32__
         if ( __ECL_ASSERT1__(((WCWnd*)_wnd)->m_hWnd != 0) )
            return (int)((WCWnd*)_wnd)->SendMessage(c.getMsg(), c.getParam1(), c.getParam2());
      #elif defined __ECL_OS2__
         return (int)SendMessage(hwnd, c.getMsg(), c.getParam1(), c.getParam2());
      #endif
   }

   return 0;
}

bool cwWindow::postCommand(const cwCmd& cmd)
{
   // Kann notfalls auch ueber this == 0 aufgerufen werden!

   if ( __ECL_ASSERT1__(this != 0 && _wnd != 0) ) {
      ccwCmd c(cmd);
      #if defined __ECL_W32__
         if ( __ECL_ASSERT1__(((WCWnd*)_wnd)->m_hWnd != 0) )
            return !!((WCWnd*)_wnd)->PostMessage(c.getMsg(), c.getParam1(), c.getParam2());
      #elif defined __ECL_OS2__
         return !PostMessage(hwnd, c.getMsg(), c.getParam1(), c.getParam2());
      #endif
   }

   return false;
}

bool cwWindow::getInsertMode()
{
   #if defined __ECL_W32__
      // ???
      return false;
   #elif defined __ECL_OS2__
      return GetSysValue(SV_INSERTMODE);
   #endif
}

bool cwWindow::setInsertMode(bool /*value*/)
{
   #if defined __ECL_W32__
      // Nervig: cBase::DbgError("Cannot set InsertMode(%d)", value);
      return false;
   #elif defined __ECL_OS2__
      return SetSysValue(SV_INSERTMODE, value);
   #endif
}


// Message-Boxen
// =============

cwWindow::MB_RES cwWindow::showMsg(const cwWindow *owner, const cString& title, const cString& text, MB_STYLE style)
{
   cwWindow *main_win = cwApplication::getMainWindow();

   #if defined __ECL_W32__

      int win_rc, win_style = 0;

      switch ( style ) {
      case mbsInfo:     win_style = MB_ICONINFORMATION|MB_OK /*MB_OKCANCEL*/; break;
      case mbsWarning:  win_style = MB_ICONWARNING|MB_OK /*MB_OKCANCEL*/; break;
      case mbsError:    win_style = MB_ICONERROR|MB_OK; break;
      #ifdef MB_CANCELTRYCONTINUE
      case mbsErrRetry: win_style = MB_ICONERROR|MB_CANCELTRYCONTINUE; break;
      #else
      case mbsErrRetry: win_style = MB_ICONERROR|MB_ABORTRETRYIGNORE; break;
      #endif
      case mbsFatal:    win_style = MB_ICONERROR|MB_OK; break;
      case mbsQuery:    win_style = MB_ICONQUESTION|MB_YESNOCANCEL; break;
      }

      WCWnd *wnd = owner ? (WCWnd*)owner->__getWnd(owner) : (WCWnd*)__getWnd(main_win);
      if ( wnd == 0 || wnd->m_hWnd == NULL ) wnd = (WCWnd*)__getWnd(main_win);
      win_rc = ::MessageBox(wnd ? wnd->m_hWnd : NULL, text, title, win_style);

      switch ( win_rc ) {
      case IDOK:           return mbrOk;
      case IDCANCEL:       return mbrCancel;
      case IDABORT:        return mbrCancel;
      case IDRETRY:        return mbrRetry;
      #ifdef IDTRYAGAIN
         case IDTRYAGAIN:  return mbrRetry;
      #endif
      case IDIGNORE:       return mbrIgnore;
      case IDYES:          return mbrYes;
      case IDNO:           return mbrNo;
      default:             return mbrOk; // ???
      }

   #elif defined __ECL_OS2__

      int pm_rc, pm_style = 0;

      switch ( style ) {
      case mbsInfo:     pm_style = MB_INFORMATION|MB_OK; break;
      case mbsWarning:  pm_style = MB_WARNING|MB_OK; break;
      case mbsError:    pm_style = MB_ERROR|MB_OK; break;
      case mbsErrRetry: pm_style = MB_ERROR|MB_OK; break;
      case mbsFatal:    pm_style = MB_ERROR|MB_OK; break;
      case mbsQuery:    pm_style = MB_QUERY|MB_YESNOCANCEL; break;
      }

      pm_rc = WinMessageBox(
         HWND_DESKTOP,
         owner ? owner->GetHandle() : NULLHANDLE,
         text, title, 0, MB_MOVEABLE|style
      );

      switch ( pm_rc ) {
      case MBID_OK:     return mbrOk;
      case MBID_CANCEL: return mbrCancel;
      case MBID_ABORT:  return mbrCancel;
      case MBID_RETRY:  return mbrRetry;
      case MBID_IGNORE: return mbrIgnore;
      case MBID_YES:    return mbrYes;
      case MBID_NO:     return mbrNo;
      default:          return mbrOk; // ???
      }

   #endif
}

cwWindow::MB_RES cwWindow::showInfo(const cwWindow *owner, const cString& text)
{
   return showMsg(owner, "Information", text, mbsInfo);
}

cwWindow::MB_RES cwWindow::showWarning(const cwWindow *owner, const cString& text)
{
   return showMsg(owner, "Warnung", text, mbsWarning);
}

cwWindow::MB_RES cwWindow::showError(const cwWindow *owner, const cErrBase& err, const cString& add_info)
{
   char text[2048]; err.getString(text, sizeof text, add_info);
   return showError(owner, text);
}

cwWindow::MB_RES cwWindow::showError(const cwWindow *owner, const cString& text)
{
   return showMsg(owner, "Fehler", text, mbsError);
}

cwWindow::MB_RES cwWindow::showFatal(const cwWindow *owner, const cString& text)
{
   return showMsg(owner, "Fataler Fehler", text, mbsFatal);
}

cwWindow::MB_RES cwWindow::showQuery(const cwWindow *owner, const cString& text)
{
   return showMsg(owner, "Bestätigung", text, mbsQuery);
}


// Zusaetzliche Events
// ===================

// Flags
// -----

void cwWindow::onSetFlags(int mask, bool set)
{
   if ( set ) {
      flags |= mask;
   } else {
      flags &= ~mask;
   }
}


// Styles
// ------

int cwWindow::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();
      DWORD ex_style = ((CWnd*)_wnd)->GetExStyle();

      if ( (mask & wsDisabled) && (style & WS_DISABLED) )
         rc |= wsDisabled;
      if ( (mask & wsVisible) && (style & WS_VISIBLE) )
         rc |= wsVisible;
      if ( (mask & wsChild) && (style & WS_CHILD) )
         rc |= wsChild;
      if ( (mask & wsPopup) && (style & WS_POPUP) )
         rc |= wsPopup;
      if ( (mask & wsScrollHorz) && (style & WS_HSCROLL) )
         rc |= wsScrollHorz;
      if ( (mask & wsScrollVert) && (style & WS_VSCROLL) )
         rc |= wsScrollVert;
      if ( (mask & wsBorder) && (style & WS_BORDER) )
         rc |= wsBorder;
      if ( (mask & wsBorderThick) && (style & WS_DLGFRAME) )
         rc |= wsBorderThick;
      if ( (mask & wsBorderSize) && (style & WS_THICKFRAME) )
         rc |= wsBorderSize;
      if ( (mask & wsTabStop) && (style & WS_TABSTOP) )
         rc |= wsTabStop;

      if ( (mask & wsReserved1) && (ex_style & WS_EX_CLIENTEDGE) )
         rc |= wsReserved1;
      if ( (mask & wsReserved2) && (ex_style & WS_EX_WINDOWEDGE) )
         rc |= wsReserved2;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc;
}

void cwWindow::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      os_styles[0] = os_styles[1] = 0;

      if ( styles & wsDisabled )
         os_styles[0] |= WS_DISABLED;
      if ( styles & wsVisible )
         os_styles[0] |= WS_VISIBLE;
      if ( styles & wsChild )
         os_styles[0] |= WS_CHILD;
      if ( styles & wsPopup )
         os_styles[0] |= WS_POPUP;
      if ( styles & wsScrollHorz )
         os_styles[0] |= WS_HSCROLL;
      if ( styles & wsScrollVert )
         os_styles[0] |= WS_VSCROLL;
      if ( styles & wsBorder )
         os_styles[0] |= WS_BORDER;
      if ( styles & wsBorderThick )
         os_styles[0] |= WS_DLGFRAME;
      if ( styles & wsBorderSize )
         os_styles[0] |= WS_THICKFRAME;
      if ( styles & wsTabStop )
         os_styles[0] |= WS_TABSTOP;

      if ( styles & wsReserved1 )
         os_styles[1] |= WS_EX_CLIENTEDGE;
      if ( styles & wsReserved2 )
         os_styles[1] |= WS_EX_WINDOWEDGE;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwWindow::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   // In dieser Funktion (und nur hier!) werden alle kummulierten 'add' und 'remove'
   // Styles tatsaechlich durchgefuehrt.

   #if defined __ECL_W32__

      if ( add & wsDisabled )
         os_add[0] |= WS_DISABLED;
      if ( add & wsVisible )
         os_add[0] |= WS_VISIBLE;
      if ( add & wsChild )
         os_add[0] |= WS_CHILD;
      if ( add & wsPopup )
         os_add[0] |= WS_POPUP;
      if ( add & wsScrollHorz )
         os_add[0] |= WS_HSCROLL;
      if ( add & wsScrollVert )
         os_add[0] |= WS_VSCROLL;
      if ( add & wsBorder )
         os_add[0] |= WS_BORDER;
      if ( add & wsBorderThick )
         os_add[0] |= WS_DLGFRAME;
      if ( add & wsBorderSize )
         os_add[0] |= WS_THICKFRAME;
      if ( add & wsTabStop )
         os_add[0] |= WS_TABSTOP;

      if ( add & wsReserved1 )
         os_add[1] |= WS_EX_CLIENTEDGE;
      if ( add & wsReserved2 )
         os_add[1] |= WS_EX_WINDOWEDGE;

      if ( remove & wsDisabled )
         os_remove[0] |= WS_DISABLED;
      if ( remove & wsVisible )
         os_remove[0] |= WS_VISIBLE;
      if ( remove & wsChild )
         os_remove[0] |= WS_CHILD;
      if ( remove & wsPopup )
         os_remove[0] |= WS_POPUP;
      if ( remove & wsScrollHorz )
         os_remove[0] |= WS_HSCROLL;
      if ( remove & wsScrollVert )
         os_remove[0] |= WS_VSCROLL;
      if ( remove & wsBorder )
         os_remove[0] |= WS_BORDER;
      if ( remove & wsBorderThick )
         os_remove[0] |= WS_DLGFRAME;
      if ( remove & wsBorderSize )
         os_remove[0] |= WS_THICKFRAME;
      if ( remove & wsTabStop )
         os_remove[0] |= WS_TABSTOP;

      if ( remove & wsReserved1 )
         os_remove[1] |= WS_EX_CLIENTEDGE;
      if ( remove & wsReserved2 )
         os_remove[1] |= WS_EX_WINDOWEDGE;

      if ( os_add[0] != 0 || os_remove[0] != 0 ) {
         if ( __ECL_ASSERT1__(((WCWnd*)_wnd)->m_hWnd != NULL) )
            ((WCWnd*)_wnd)->ModifyStyle(os_remove[0], os_add[0], 0);
      }
      if ( os_add[1] != 0 || os_remove[1] != 0 ) {
         if ( __ECL_ASSERT1__(((WCWnd*)_wnd)->m_hWnd != NULL) )
            ((WCWnd*)_wnd)->ModifyStyleEx(os_remove[1], os_add[1], 0);
      }

   #elif defined __ECL_OS2__

      // ...

   #endif
}

bool cwWindow::onCreate()
{
   TRACEWIN(("onCreate()"));
   callEvent(evtWindowCreated);
   return true;
}

bool cwWindow::onPreCreate(void * /*add_data*/)
{
   TRACEWIN(("onPreCreate()"));
   return true;
}

void cwWindow::onDestroy()
{
   TRACEWIN(("onDestroy()"));
   callEvent(evtWindowDestroyed);

   // Schmutziger kleiner Trick, damit ~cwWindow nicht nochmal destroy() aufruft:
   setFlags(wflWasAttached);

   if ( info )
      info->active = 0;
}

void cwWindow::onSize(int IGN(cx), int IGN(cy))
{
   TRACEWIN(("onSize(%d,%x)", cx, cy));

   if ( info->sticky != 0 ) {
      cdRect rect = getRect();
      // cBase::DbgOut(0, "getRect():  rect=(left=%d right=%d top=%d bottom=%d)", rect.lb.x, rect.rt.x, rect.rt.y, rect.lb.y);
      if ( getParent() )
         getParent()->convScreen2Win(rect);
      // cBase::DbgOut(0, "corrected: rect=(left=%d right=%d top=%d bottom=%d)", rect.lb.x, rect.rt.x, rect.rt.y, rect.lb.y);
      rect.lb.y = rect.rt.y - 1;
      rect.rt.y = rect.rt.y - info->sticky->getSize().cy - 1;
      // cBase::DbgOut(0, "sticky:    rect=(left=%d right=%d top=%d bottom=%d)", rect.lb.x, rect.rt.x, rect.rt.y, rect.lb.y);
      info->sticky->setRect(rect);
      // new_rect.rt.y = rect.rt.y + height + 1;
   }
}

void cwWindow::onChar(cwCmdChar& IGN(cmd))
{
   #if defined __Trace_Win_Calls__ && __ECL_DEBUG__ > 0

      static const char *vk_names[] = {
         "vkUndef", "vkF1", "vkF2", "vkF3", "vkF4", "vkF5", "vkF6", "vkF7", "vkF8", "vkF9", "vkF10", "vkF11", "vkF12",
         "vkBreak", "vkShift", "vkControl", "vkAlt", "vkAltGraf", "vkEsc", "vkBackspace",
         "vkReturn", "vkTab", "vkBackTab", "vkPause", "vkSpace",
         "vkPgUp", "vkPgDown", "vkEnd", "vkHome", "vkLeft", "vkRight", "vkUp", "vkDown",
         "vkPrintScrn", "vkInsert", "vkDelete", "vkScrlLock", "vkCapsLock",
         "vkNumLock", "vkNumDiv", "vkNumMul", "vkNumSub", "vkNumAdd", "vkNumEnter", "vkNumDec",
         "vkNum0", "vkNum1", "vkNum2", "vkNum3", "vkNum4", "vkNum5", "vkNum6", "vkNum7", "vkNum8", "vkNum9"
      };

      if ( cmd.isVirt() ) {
         TRACEWIN(("onChar(Key%s, %s)", cmd.isKeyUp() ? "Up" : "Down", vk_names[cmd.getVirt()]));
      } else {
         TRACEWIN(("onChar(Key%s, '%c')", cmd.isKeyUp() ? "Up" : "Down", cmd.getChar()));
      }

   #endif
}

bool cwWindow::onMouseClick(const cwCmdMouse& IGN(cmd))
{
   #if defined __Trace_Win_Calls__ && __ECL_DEBUG__ > 0

      static const char *button_names[] = { "<none>", "Left", "Right", "Middle" };
      static const char *click_names[] = { "<none>", "Down", "Up", "DblClick" };

      TRACEWIN(("onMouseClick(%s, %s, Pos=(%d,%d), Holds%s%s%s)",
         button_names[cmd.getButtonNo()],
         click_names[cmd.getClickStyle()],
         cmd.getPosX(), cmd.getPosY(),
         cmd.holdsShift() ? " SHIFT" : "",
         cmd.holdsCtrl()  ? " CTRL"  : "",
         cmd.holdsAlt()   ? " ALT"   : ""));

   #endif

   return false;
}

bool cwWindow::onMouseMove(const cwCmdMouse& /*cmd*/)
{
   return false;
}

bool cwWindow::onCommand(const cwCmdEvt& IGN(cmd))
{
   TRACEWIN(("onCommand(%d)", cmd.getId()));
   return false;
}

bool cwWindow::onCommandUI(cwCmdUI& /*cmd*/)
{
   // TRACEWIN(("onCommandUI(%d)", cmd.getId()));
   // cmd.setEnable(true);
   return false;
}

bool cwWindow::onContextMenu(const cwCmdPosition& cmd)
{
   TRACEWIN(("onContextMenu(Pos=(%d,%d))", cmd.getPosX(), cmd.getPosY()));

   // Erstmal ermitteln, ob das Window einem View zugeordnet ist.
   // In diesem Fall muss die Selektion des Views benutzt werden,
   // ebenso sind die Menu-Kommandos an den View zu schicken.

   cwWindow *parent = getParent();
   cwWindow *cmd_target =  parent != 0 && parent->getFlags(wflIsAView) ?
      parent : this;

   cEloSelection private_sel;
   cEloSelection *sel = getWindowElemSelection();
   if ( sel == 0 )
      sel = &private_sel;

   updateWindowElemSelection(*sel);

   // Aktionsbeschreibung ermitteln

   cEloActionDescription *ad = getWindowActionDescription(sel);
   int ad_object_count = 0;

   if ( ad != 0 && (ad_object_count = ad->getObjectCount()) > 0 ) {

      // Selektion fuer das aktuelle Fenster ('this') vorbereiten (wird spaeter evtl. benoetigt)
      cEloSelection this_selection;
      this_selection.addElement(this);

      // Kontextmenu aufbauen (gemaess Action Description)
      cwPopupMenu *menu = new cwPopupMenu();
      menu->create();

      bool default_set = false;     // Wurde das Default-Menu bereits vergeben?
      bool included_one = false;    // Wurde seit dem letzten Break ein Menueintrag eingefuegt?
      bool break_before = false;    // Soll vor dem naechsten Menueintrag ein Break erfolgen?

      for ( int i = 0 ; i < ad_object_count ; i++ ) {

         break_before = break_before || ad->hasBreakBefore(i);

         if ( ad->isOperation(i) ) {
            cEloOperation *op = ad->getOperation(i);
            cString sig = op->getSignature();
            int ad_obj_id = ad->getObjectID(i);

            // Standard-Kommando-IDs in ihre betriebssystem-spezifische Form bringen...
            if ( ad_obj_id > cwCmdEvt::cmdStandardFirst && ad_obj_id < cwCmdEvt::cmdStandardLast )
               ad_obj_id = cwCmdEvt::convID(cwCmdEvt::STDCMDS(ad_obj_id));

            // Die Operation wird zur Auswahl angeboten, wenn eine der folgenden Bedingungen zutrifft:
            //  - Die Operation wird von der aktuellen Selektion unterstuetzt
            //  - Die Selektion ist leer und die Operation wird vom aktuellen Fenster unterstuetzt
            //  - Die Operation ist statisch
            cEloSelection *local_sel = sel->getElementCount() == 0 ? &this_selection : sel;
            bool include_op = op->isStatic() && op->isEnabled() && op->isVisible()
                           || local_sel->supportsOperation(sig) && op->isEnabled(local_sel) && op->isVisible(local_sel);


            if ( include_op ) {
               if ( break_before && included_one ) {
                  break_before = false;
                  menu->addSeparator();
               }
               included_one = true;
               if ( op->hasSubOperations(local_sel) ) {
                  cwSubMenu sub_menu;
                  sub_menu.create();
                  int count = op->getSubOperationCount(local_sel);
                  for ( int sub = 0 ; sub < count ; sub++ ) {
                     sub_menu.addItem(op->getMenuText(local_sel, sub), ad_obj_id + sub + 1);
                  }
                  menu->addItem(op->getMenuText(local_sel), ad_obj_id, &sub_menu);
               } else {
                  menu->addItem(op->getMenuText(local_sel), ad_obj_id);
               }
               if ( ad->isDefault(i) && !default_set ) {
                  menu->setDefault(cwMID(ad_obj_id));
                  default_set = true; // Nur erstes Default zaehlt!
               }
               if ( op->isCheckable(local_sel) ) {
                  menu->setCheck(cwMID(ad_obj_id), op->isChecked(local_sel));
               }
            }
         } else if ( ad->isSubDescription(i) ) {
            // ...
         }

         break_before = break_before || ad->hasBreakAfter(i);

      }

      // Menu anzeigen, Kommandos gehen zum View, falls
      // das Window einem solchen zugeordnet ist.

      setMenu(menu);
      return menu->showMenu(cmd_target, cmd);

   }

   return false;
}

void cwWindow::onScroll(const cwCmdScroll& IGN(cmd))
{
   #if defined __Trace_Win_Calls__ && __ECL_DEBUG__ > 0

      static const char *actions[] = {
         "scrlLeft", "scrlLeftLine", "scrlLeftPage",
         "scrlRight", "scrlRightLine", "scrlRightPage",
         "scrlTop", "scrlUpLine", "scrlupPage",
         "scrlBottom", "scrlDownLine", "scrlDownPage",
         "scrlEnd", "scrlBoxTracking", "scrlBoxReleased"
      };

      TRACEWIN(("onScroll(%s,%s)",
         cmd.fromHorzScrollBar() ? "Horz" : "Vert",
         actions[cmd.getAction()]));

   #endif
}

void cwWindow::onGainFocus()
{
   TRACEWIN(("onGainFocus()"));
}

void cwWindow::onLoseFocus()
{
   TRACEWIN(("onLoseFocus()"));
}

bool cwWindow::onDispatchChar(const cwCmdChar& /*cmd*/)
{
   // Diese Funktion wird aufgerufen, bevor das cwCmdChar-Kommando 'cmd'
   // an die entsprechende Bearbeitungsstelle verteilt wird. Das Fenster
   // kann jetzt entscheiden, ob die Verteilung erfolgen soll (true) oder
   // nicht (false).

   return true;
}

bool cwWindow::onDispatchMouseClick(const cwCmdMouse& /*cmd*/)
{
   // Diese Funktion wird aufgerufen, bevor das cwCmdMouse-Kommando 'cmd'
   // an die entsprechende Bearbeitungsstelle verteilt wird. Das Fenster
   // kann jetzt entscheiden, ob die Verteilung erfolgen soll (true) oder
   // nicht (false).

   return true;
}

void cwWindow::onChildActivated(cwWindow *win)
{
   TRACEWIN(("onChildActivated(%x,%s)", win, (win != 0 ? win->getClassName() : "")));

   // Aktives Kindfenster merken...
   info->active = win;
   // ... und evtl. an Parent weitergeben
   if ( info->parent )
      info->parent->onChildActivated(this);
}

bool cwWindow::onRefresh()
{
   TRACEWIN(("onRefresh()"));
   return true;
}

bool cwWindow::onStore()
{
   TRACEWIN(("onStore()"));
   return true;
}

bool cwWindow::onDiscard()
{
   TRACEWIN(("onDiscard()"));
   return true;
}

void cwWindow::onResumeClose()
{
   TRACEWIN(("onResumeClose()"));
}

bool cwWindow::onAllowTurn()
{
   TRACEWIN(("onAllowTurn()"));
   return true;
}

bool cwWindow::onAllowStore()
{
   TRACEWIN(("onAllowStore()"));
   return true;
}

bool cwWindow::onAllowDiscard()
{
   TRACEWIN(("onAllowDiscard()"));
   return true;
}

bool cwWindow::onAllowClose(cwWindow * /*notify*/)
{
   TRACEWIN(("onAllowClose()"));
   return true;
}

bool cwWindow::onTimer(int IGN(id))
{
   TRACEWIN(("onTimer(%d)", id));
   return false;
}

bool cwWindow::onDragEnter(cwCmdDrag& /*cmd*/)
{
   return false;
}

bool cwWindow::onDragOver(cwCmdDrag& /*cmd*/)
{
   return false;
}

bool cwWindow::onDragScroll(cwCmdDrag& /*cmd*/)
{
   return false;
}

bool cwWindow::onDragLeave()
{
   return false;
}

bool cwWindow::onDrop(cwCmdDrop& /*cmd*/)
{
   return false;
}

void cwWindow::onPresParamChanged(PPARAMS pp)
{
   if ( pp == ppFont ) {
      cString value; getPresParam(ppFont, value);
      cdFont font; font.create(value);
      if ( isCreated() ) {
         #if defined __ECL_W32__
            ((WCWnd*)_wnd)->SetFont((CFont*)ccdFont::getFont(font));
            ((WCWnd*)_wnd)->Invalidate();
            //((WCWnd*)_wnd)->UpdateWindow();
         #else
         #endif
      }
   } else {
      if ( isCreated() ) {
         #if defined __ECL_W32__
            ((WCWnd*)_wnd)->Invalidate();
            //((WCWnd*)_wnd)->UpdateWindow();
         #else
         #endif
      }
   }
}

void cwWindow::onPresParamRemoved(PPARAMS /*pp*/)
{
   if ( isCreated() ) {
      #if defined __ECL_W32__
         ((WCWnd*)_wnd)->Invalidate();
         //((WCWnd*)_wnd)->UpdateWindow();
      #else
      #endif
   }
}

bool cwWindow::onHasWindowElemSelection() const
{
   // Keine Trace-Ausgabe, das dies staendig von onIdle aufgerufen wird:
   // TRACEWIN(("onHasWindowElemSelection()"));
   return false;
}

bool cwWindow::onUpdateWindowElemSelection(cEloSelection& /*selection*/) const
{
   TRACEWIN(("onUpdateWindowElemSelection()"));
   return false;
}

cEloSelection * cwWindow::onGetWindowElemSelection()
{
   TRACEWIN(("onGetWindowElemSelection()"));
   return 0;
}

cEloActionDescription * cwWindow::onGetWindowActionDescription(const cEloSelection * /*selection*/) const
{
   // Keine Trace-Ausgabe, das dies staendig von onIdle aufgerufen wird:
   // TRACEWIN(("onGetWindowActionDescription"));
   return 0;
}


// Verzoegerte Ausfuehrung
// =======================

void cwWindow::execDelayed(int id, void *data, int ms_delay)
{
   #if defined __ECL_W32__

      // Realisierung unter Win32: Hat 'ms_delay' den Defaultwert (<= 0), dann
      // wird die Ausfuehrung um eine "Meldungsschleife" verzoegert (realisiert
      // durch PostMessage). Hat 'ms_delay' einen Wert > 0, wird ein entspr.
      // Timer aufgesetzt.

      // Delays mit Zeitangabe und 'data'-Zeiger momentan nicht unterstuetzt!
      __ECL_ASSERT1__(ms_delay <= 0 || data == 0);

      if ( _wnd != 0 && ((WCWnd*)_wnd)->m_hWnd != 0 ) {
         if ( ms_delay > 0 ) {
            // Timer-IDs von 10000 bis 19999 kennzeichnen execDelayed-Events!
            startTimer(10000+id, ms_delay);
         } else {
            ((WCWnd*)_wnd)->PostMessage(WM_ECL_EXEC_DELAYED, (WPARAM)id, (LPARAM)data);
         }
      } else {
         onExecDelayed(id, data);
      }

   #else

      onExecDelayed(id, data);

   #endif
}

void cwWindow::onExecDelayed(int IGN(id), void * /*data*/)
{
   TRACEWIN(("onExecDelayed(%d)", id));
}


// ECL/win Internas
// ================

void cwWindow::__disconnect()
{
   _wnd = 0;

   if ( getFlags(wflAutoDelete) ) {
      TRACEWIN(("Auto deleting this = %08x", this));
      delete this;
   }
}

void * cwWindow::__getWnd()
{
   return _wnd;
}

const void * cwWindow::__getWnd() const
{
   return _wnd;
}

void * cwWindow::__getWnd(cwWindow *window)
{
   return window ? window->_wnd : 0;
}

const void * cwWindow::__getWnd(const cwWindow *window)
{
   return window ? window->_wnd : 0;
}

