/*.SH.*/

/*
 *  Headerfile for module ew_buttonctls
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  ew_buttonctls.cpp on Friday March 08 2002  22:53:57
 */

#ifndef __ew_buttonctls__
#define __ew_buttonctls__


// Headerfiles
// ===========================================================================

#include "win/ew_controls.hpp"


// ===========================================================================
// Definition cwButtonCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwButtonCtl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwButtonCtl : public cwControl {
   ELO_DECLARE(cwButtonCtl,cwControl)
   friend class ccwButtonCtl;

public:

   // Konstruktor
   inline cwButtonCtl() : cwControl(0) { init(); }
   // Destruktor
   virtual ~cwButtonCtl();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwControl::wsUser,
      wsBtnAutoState    = wsStart << 0,   // Zustandsaenderung mit jedem Klick
      wsBtnMultiLine    = wsStart << 1,   // Mehrzeiliger Text moeglich
      wsBtnPlaceRight   = wsStart << 2,   // Knopf erscheint rechts vom Text
      wsBtnPushLike     = wsStart << 3,   // Alle Knoepfe wie Push-Buttons
      wsBtnFlat         = wsStart << 4,   // Flaches Aussehen (Kein 3D-Effekt)
      wsUser            = wsStart << 5    // Benutzerdefinierte Styles
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwControl::evtUser,
      evtButtonClicked,       // (EVFUNC) Button angeklickt
      evtButtonDblClicked,    // (EVFUNC) Button doppelt-angeklickt
      evtUser                 // Ab hier benutzerdefinierte Events
   };


   // States
   // ======

   // Moegliche Button-Zustaende
   enum STATE {
      chkUnchecked = 0,
      chkChecked   = 1,
      chkIndeter   = 2
   };

   // Button-Zustand setzen
   void setCheck(STATE state);
   // Button-Zustand erfragen
   STATE getCheck() const;

   // Highlight-Zustand setzen
   void setHilite(bool hi);
   // Highlight-Zustand erfragen
   bool getHilite() const;


   // Images
   // ======

   // Icon als Button-Image setzen
   void setImage(const cIcon& icon);
   // Bitmap als Button-Image setzen
   void setImage(const cBitmap& bitmap);


protected:

   // Zusaetzliche Events
   // ===================

   // Wird bei einfachem Klick aufgerufen
   virtual void onClick();
   // Wird bei Doppelklick aufgerufen
   virtual void onDblClick();

   // Wird aufgerufen, um den Button-Zustand setzen
   virtual void onSetCheck(STATE state);
   // Wird aufgerufen, um den Button-Zustand erfragen
   virtual STATE onGetCheck() const;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwButtonCtl(void *wnd);

private:

   // Initialisierung
   void init();

};


// ===========================================================================
// Definition cwPushButton
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwButtonCtl
//              +--cwPushButton
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwPushButton : public cwButtonCtl {
   ELO_DECLARE(cwPushButton,cwButtonCtl)

public:

   // Konstruktor
   inline cwPushButton() : cwButtonCtl(0) { init(); }
   // Destruktor
   virtual ~cwPushButton();


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, const cString& caption,
               int style = wsChild | wsVisible | wsTabStop,
               const cdRect& rect = cdRect());


   // States
   // ======

   // Default-Zustand setzen
   void setDefault(bool def);
   // Default-Zustand erfragen
   bool getDefault() const;


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwPushButton(void *wnd);


private:

   // Initialisierung
   void init();

};


// ===========================================================================
// Definition cwRadioButton
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwButtonCtl
//              +--cwRadioButton
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwRadioButton : public cwButtonCtl {
   ELO_DECLARE(cwRadioButton,cwButtonCtl)

public:

   // Konstruktor
   inline cwRadioButton() : cwButtonCtl(0) { init(); }
   // Destruktor
   virtual ~cwRadioButton();


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, const cString& caption,
               csStorage *store = 0, const cString& value = 0,
               int style = wsBtnAutoState | wsChild | wsVisible | wsTabStop,
               const cdRect& rect = cdRect());
   // Mit bestehendem Control verknuepfen
   void attach(cwWindow *parent, int id, csStorage *store = 0, const cString& value = 0);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird bei einfachem Klick aufgerufen
   void onClick();

   // Daten des Controls refreshen
   bool onRefreshCtl(csStorage *store);
   // Daten des Controls pruefen
   DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   DATAERR onStoreCtl(csStorage *store);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwRadioButton(void *wnd);


private:

   // Zugeordneter Wert
   cString value;

   // Initialisierung
   void init();

};


// ===========================================================================
// Definition cwCheckButton
// ---------------------------------------------------------------------------
//
// Dieses Control unterstuetzt die Anzeige eines "ererbten Werten", der ueber
// die SetInheritedValue()-Methode gesetzt werden kann.
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwButtonCtl
//              +--cwCheckButton
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwCheckButton : public cwButtonCtl {
   ELO_DECLARE(cwCheckButton,cwButtonCtl)

public:

   // Konstruktor
   inline cwCheckButton() : cwButtonCtl(0) { init(); }
   // Destruktor
   virtual ~cwCheckButton();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwButtonCtl::wsUser,
      wsBtn3State       = wsStart << 0,   // Check-Button mit 3 Zustaenden
      wsUser            = wsStart << 1    // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, const cString& caption, csStorage *store = 0,
               const cString& vchkd = 0, const cString& vunchkd = 0, const cString& vindet = 0,
               int style = wsBtnAutoState | wsChild | wsVisible | wsTabStop,
               const cdRect& rect = cdRect());
   // Mit bestehendem Control verknuepfen
   void attach(cwWindow *parent, int id, csStorage *store = 0,
               const cString& vchkd = 0, const cString& vunchkd = 0, const cString& vindet = 0);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird bei einfachem Klick aufgerufen
   void onClick();

   // Daten des Controls refreshen
   bool onRefreshCtl(csStorage *store);
   // Daten des Controls pruefen
   DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   DATAERR onStoreCtl(csStorage *store);

   // Wird aufgerufen, um den aktuellen ererbten Wert anzuzeigen
   void onShowInheritedVal();
   // Wird aufgerufen, um die Anzeige des ererbten Wertes zu beenden
   void onHideInheritedVal();
   // Wird aufgerufen um festzustellen, ob das Control einen ueberschriebenen Wert hat
   bool onIsInheritedValOverridden();

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwCheckButton(void *wnd);


private:

   // Zugeordnete Werte
   cString vchkd, vunchkd, vindet;

   // Initialisierung
   void init();

};


#endif

/*.EH.*/