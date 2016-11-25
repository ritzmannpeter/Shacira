// ===========================================================================
// ew_buttonctls.cpp                                            ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwControl
//           |
//           +-cwButtonCtl       - Basisklasse fuer alle ECL-Buttons
//              |
//              +--cwPushButton  - Push-Buttons
//              |
//              +--cwRadioButton - Radio-Buttons
//              |
//              +--cwCheckButton - Check-Buttons
//
// ===========================================================================

#include "win/ew_buttonctls.hpp"

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

#include "win/ew_controls.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwButtonCtl
// ===========================================================================

cwButtonCtl::cwButtonCtl(void *wnd) :
   cwControl(wnd)
{
}

cwButtonCtl::~cwButtonCtl()
{
}

void cwButtonCtl::init()
{
   #if defined __ECL_W32__
      _wnd = new WCButton(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// States
// ======

void cwButtonCtl::setCheck(STATE state)
{
   __ECL_ASSERT1__(_wnd != 0);
   onSetCheck(state);
}

cwButtonCtl::STATE cwButtonCtl::getCheck() const
{
   __ECL_ASSERT1__(_wnd != 0);
   return onGetCheck();
}

void cwButtonCtl::setHilite(bool hi)
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      ((WCButton*)_wnd)->SetState(hi);
   #elif defined __ECL_OS2__
      SendMsg(BM_SETHILITE, MPFROMSHORT(hi));
   #endif
}

bool cwButtonCtl::getHilite() const
{
   __ECL_ASSERT1__(_wnd != 0);

   #if defined __ECL_W32__
      return !!(((WCButton*)_wnd)->GetState() & 0x0004);
   #elif defined __ECL_OS2__
      return (BOOL)SendMsg(BM_QUERYHILITE);
   #endif
}


// Zusaetzliche Events
// ===================

void cwButtonCtl::onClick()
{
   cBase::DbgTrcWin("cwButtonCtl::onClick()");
   callEvent(evtButtonClicked);
}

void cwButtonCtl::onDblClick()
{
   cBase::DbgTrcWin("cwButtonCtl::onDblClick()");
   callEvent(evtButtonDblClicked);
}

void cwButtonCtl::onSetCheck(STATE state)
{
   #if defined __ECL_W32__

      int win_state = 0;

      switch ( state ) {
      case chkUnchecked:   win_state = 0; break;
      case chkChecked:     win_state = 1; break;
      case chkIndeter:     win_state = 2; break;
      }

      ((WCButton*)_wnd)->SetCheck(win_state);

   #elif defined __ECL_OS2__

      int pm_state = 0;

      switch ( state ) {
      case chkUnchecked:   pm_state = 0; break;
      case chkChecked:     pm_state = 1; break;
      case chkIndeter:     pm_state = 2; break;
      }

      SendMsg(BM_SETCHECK, MPFROMSHORT(pm_state));

   #endif

}

cwButtonCtl::STATE cwButtonCtl::onGetCheck() const
{
   #if defined __ECL_W32__

      switch ( ((WCButton*)_wnd)->GetCheck() ) {
      case 0:     return chkUnchecked;
      case 1:     return chkChecked;
      default:    return chkIndeter;
      }

   #elif defined __ECL_OS2__

      switch ( SHORT1FROMMR(SendMsg(BM_QUERYCHECK)) ) {
      case 0:     return chkUnchecked;
      case 1:     return chkChecked;
      default:    return chkIndeter;
      }

   #endif
}


// Images
// ======

void cwButtonCtl::setImage(const cIcon& icon)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCButton *mfc_ctrl = (WCButton*)_wnd;
         if ( __ECL_ASSERT1__(mfc_ctrl->m_hWnd != NULL) ) {
            HICON hIcon = (HICON)ccwHandle::getHandle(icon);
            mfc_ctrl->ModifyStyle(BS_BITMAP, BS_ICON);
            mfc_ctrl->SetIcon(hIcon);
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

void cwButtonCtl::setImage(const cBitmap& bitmap)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCButton *mfc_ctrl = (WCButton*)_wnd;
         if ( __ECL_ASSERT1__(mfc_ctrl->m_hWnd != NULL) ) {
            HBITMAP hBitmap = (HBITMAP)ccwHandle::getHandle(bitmap);
            mfc_ctrl->ModifyStyle(BS_ICON, BS_BITMAP);
            mfc_ctrl->SetBitmap(hBitmap);
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}


// Ueberschriebene Events
// ======================

int cwButtonCtl::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();

      if ( (mask & wsBtnMultiLine) && (style & BS_MULTILINE) )
         rc |= wsBtnMultiLine;
      if ( (mask & wsBtnPlaceRight) && (style & BS_LEFTTEXT) )
         rc |= wsBtnPlaceRight;
      if ( (mask & wsBtnPushLike) && (style & BS_PUSHLIKE) )
         rc |= wsBtnPushLike;
      if ( (mask & wsBtnFlat) && (style & BS_FLAT) )
         rc |= wsBtnFlat;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwControl::onGetStyles(mask);
}

void cwButtonCtl::onMakeStyles(int styles, int os_styles[]) const
{
   cwControl::onMakeStyles(styles, os_styles);

   #if defined __ECL_W32__

      if ( styles & wsBtnMultiLine )
         os_styles[0] |= BS_MULTILINE;
      if ( styles & wsBtnPlaceRight )
         os_styles[0] |= BS_LEFTTEXT;
      if ( styles & wsBtnPushLike )
         os_styles[0] |= BS_PUSHLIKE;
      if ( styles & wsBtnFlat )
         os_styles[0] |= BS_FLAT;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwButtonCtl::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsBtnMultiLine )
         os_add[0] |= BS_MULTILINE;
      if ( add & wsBtnPlaceRight )
         os_add[0] |= BS_LEFTTEXT;
      if ( add & wsBtnPushLike )
         os_add[0] |= BS_PUSHLIKE;
      if ( add & wsBtnFlat )
         os_add[0] |= BS_FLAT;

      if ( remove & wsBtnMultiLine )
         os_remove[0] |= BS_MULTILINE;
      if ( remove & wsBtnPlaceRight )
         os_remove[0] |= BS_LEFTTEXT;
      if ( remove & wsBtnPushLike )
         os_remove[0] |= BS_PUSHLIKE;
      if ( remove & wsBtnFlat )
         os_remove[0] |= BS_FLAT;

   #elif defined __ECL_OS2__

      // ...

   #endif

   cwControl::onModifyStyles(add, remove, os_add, os_remove);
}




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwPushButton
// ===========================================================================

cwPushButton::cwPushButton(void *wnd) :
   cwButtonCtl(wnd)
{
}

cwPushButton::~cwPushButton()
{
}

void cwPushButton::init()
{
   #if defined __ECL_W32__
      _wnd = new WCButton(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwPushButton::create(cwWindow *parent, int id, const cString& caption,
                          int style, const cdRect& rect)
{
   cwButtonCtl::create(parent, id);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= BS_PUSHBUTTON;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCButton*)_wnd)->Create(caption, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create button control"));

   #else
      // ...
   #endif
}


// States
// ======

void cwPushButton::setDefault(bool def)
{
   #if defined __ECL_W32__
      UINT new_style = BS_PUSHBUTTON | (def ? BS_DEFPUSHBUTTON : 0);
      ((WCButton*)_wnd)->SetButtonStyle(new_style);
   #elif defined __ECL_OS2__
   #endif
}

bool cwPushButton::getDefault() const
{
   #if defined __ECL_W32__
      return !!(((WCButton*)_wnd)->GetButtonStyle() & BS_DEFPUSHBUTTON);
   #elif defined __ECL_OS2__
   #endif
}


// Ueberschriebene Events
// ======================

int cwPushButton::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__
      // ...
   #elif defined __ECL_OS2__
      // ...
   #endif

   return rc | cwButtonCtl::onGetStyles(mask);
}

void cwPushButton::onMakeStyles(int styles, int os_styles[]) const
{
   cwButtonCtl::onMakeStyles(styles, os_styles);

   #if defined __ECL_W32__
      // ...
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwPushButton::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__
      // ...
   #elif defined __ECL_OS2__
      // ...
   #endif

   cwButtonCtl::onModifyStyles(add, remove, os_add, os_remove);
}




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwRadioButton
// ===========================================================================

cwRadioButton::cwRadioButton(void *wnd) :
   cwButtonCtl(wnd)
{
}

cwRadioButton::~cwRadioButton()
{
}

void cwRadioButton::init()
{
   #if defined __ECL_W32__
      _wnd = new WCButton(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwRadioButton::create(cwWindow *parent, int id, const cString& caption, csStorage *store,
                           const cString& value, int style, const cdRect& rect)
{
   cwRadioButton::value = value;
   cwButtonCtl::create(parent, id, store);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCButton*)_wnd)->Create(caption, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create button control"));

   #else
      // ...
   #endif
}

void cwRadioButton::attach(cwWindow *parent, int id, csStorage *store, const cString& value)
{
   cwRadioButton::value = value;
   cwButtonCtl::attach(parent, id, store);
}


// Ueberschriebene Events
// ======================

void cwRadioButton::onClick()
{
   if ( hasStorage() && !isStorageReadOnly() && value.getLength() > 0 )
      getStorage()->put(value);
   cwButtonCtl::onClick();
}

bool cwRadioButton::onRefreshCtl(csStorage *store)
{
   if ( value.getLength() > 0 ) {
      cString buf;
      if ( store->get(buf) && value == buf )
         setCheck(chkChecked);
   }
   return cwButtonCtl::onRefreshCtl(store);
}

cwControl::DATAERR cwRadioButton::onCheckCtl(csStorage *store)
{
   return cwButtonCtl::onCheckCtl(store);
}

cwControl::DATAERR cwRadioButton::onStoreCtl(csStorage *store)
{
   if ( !isStorageReadOnly() && value.getLength() > 0 && getCheck() == chkChecked ) {
      if ( !store->put(value) )
         return store->isNull() && !store->isNullable() ? derrNotNull : derrFormat;
   }
   return cwButtonCtl::onStoreCtl(store);
}

int cwRadioButton::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__
      DWORD style = ((WCWnd*)_wnd)->GetStyle();
      if ( (mask & wsBtnAutoState) && (style & BS_AUTORADIOBUTTON) )
         rc |= wsBtnAutoState;
   #elif defined __ECL_OS2__
      // ...
   #endif

   return rc | cwButtonCtl::onGetStyles(mask);
}

void cwRadioButton::onMakeStyles(int styles, int os_styles[]) const
{
   cwButtonCtl::onMakeStyles(styles, os_styles);

   #if defined __ECL_W32__
      if ( styles & wsBtnAutoState ) {
         os_styles[0] |= BS_AUTORADIOBUTTON;
      } else {
         os_styles[0] |= BS_RADIOBUTTON;
      }
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwRadioButton::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__
      if ( add & wsBtnAutoState ) {
         os_add[0] |= BS_AUTORADIOBUTTON;
         os_remove[0] |= BS_RADIOBUTTON;
      } else if ( remove & wsBtnAutoState ) {
         os_add[0] |= BS_RADIOBUTTON;
         os_remove[0] |= BS_AUTORADIOBUTTON;
      }
   #elif defined __ECL_OS2__
      // ...
   #endif

   cwButtonCtl::onModifyStyles(add, remove, os_add, os_remove);
}




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/


// Implementierung cwCheckButton
// ===========================================================================

cwCheckButton::cwCheckButton(void *wnd) :
   cwButtonCtl(wnd)
{
}

cwCheckButton::~cwCheckButton()
{
}

void cwCheckButton::init()
{
   #if defined __ECL_W32__
      _wnd = new WCButton(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwCheckButton::create(cwWindow *parent, int id, const cString& caption, csStorage *store,
                           const cString& vchkd, const cString& vunchkd, const cString& vindet,
                           int style, const cdRect& rect)
{
   cwCheckButton::vchkd = vchkd;
   cwCheckButton::vunchkd = vunchkd;
   cwCheckButton::vindet = vindet;
   cwButtonCtl::create(parent, id, store);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[2]; onMakeStyles(style, mfc_style);

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCButton*)_wnd)->Create(caption, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create button control"));

   #else
      // ...
   #endif
}

void cwCheckButton::attach(cwWindow *parent, int id, csStorage *store,
                           const cString& vchkd, const cString& vunchkd, const cString& vindet)
{
   cwCheckButton::vchkd = vchkd;
   cwCheckButton::vunchkd = vunchkd;
   cwCheckButton::vindet = vindet;
   cwButtonCtl::attach(parent, id, store);
}


// Ueberschriebene Events
// ======================

void cwCheckButton::onClick()
{
   if ( hasStorage() && !isStorageReadOnly() ) {
      switch ( getCheck() ) {
      case chkChecked:
         if ( vchkd.isEmpty() ) {
            setStorageNull();
         } else {
            putStorageVal(vchkd);
         }
         break;
      case chkUnchecked:
         if ( vunchkd.isEmpty() ) {
            setStorageNull();
         } else {
            putStorageVal(vunchkd);
         }
         break;
      default:
         if ( vindet.isEmpty() ) {
            setStorageNull();
         } else {
            putStorageVal(vindet);
         }
         break;
      }
   }

   cwButtonCtl::onClick();
}

bool cwCheckButton::onRefreshCtl(csStorage *store)
{
   refreshInheritedValue(true);

   cString value;

   if ( getStorageVal(value) && !value.isEmpty() ) {
      if ( value == vchkd ) {
         setCheck(chkChecked);
      } else if ( value == vunchkd ) {
         setCheck(chkUnchecked);
      } else if ( !isMarkedAsInheritedValue() ) {
         setCheck(chkIndeter);
      }
   } else {
      // Reihenfolge wichtig!
      if ( vunchkd.isEmpty() ) {
         setCheck(chkUnchecked);
      } else if ( vchkd.isEmpty() ) {
         setCheck(chkChecked);
      } else {
         setCheck(chkIndeter);
      }
   }

   return cwButtonCtl::onRefreshCtl(store);
}

cwControl::DATAERR cwCheckButton::onCheckCtl(csStorage *store)
{
   return cwButtonCtl::onCheckCtl(store);
}

cwControl::DATAERR cwCheckButton::onStoreCtl(csStorage *store)
{
   refreshInheritedValue();

   if ( isStorageNull() && !store->isNotNull() )
      return cwButtonCtl::onStoreCtl(store);

   if ( !isStorageReadOnly() ) {
      bool ok = true;
      switch ( getCheck() ) {
      case chkChecked:
         if ( vchkd.isEmpty() ) {
            setStorageNull();
         } else {
            ok = putStorageVal(vchkd);
         }
         break;
      case chkUnchecked:
         if ( vunchkd.isEmpty() ) {
            setStorageNull();
         } else {
            ok = putStorageVal(vunchkd);
         }
         break;
      default:
         if ( vindet.isEmpty() ) {
            setStorageNull();
         } else {
            ok = putStorageVal(vindet);
         }
         break;
      }

      if ( !ok )
         return isStorageNull() && store->isNotNull() ? derrNotNull : derrFormat;
   }

   return cwButtonCtl::onStoreCtl(store);
}

void cwCheckButton::onShowInheritedVal()
{
   cString value = getInheritedValue();

   if ( value == vchkd ) {
      setCheck(chkChecked);
   } else if ( value == vunchkd ) {
      setCheck(chkUnchecked);
   } else {
      setCheck(chkIndeter);
   }
}

void cwCheckButton::onHideInheritedVal()
{
   cString value;
   getStorageVal(value);

   if ( value == vchkd ) {
      setCheck(chkChecked);
   } else if ( value == vunchkd ) {
      setCheck(chkUnchecked);
   } else {
      setCheck(chkIndeter);
   }
}

bool cwCheckButton::onIsInheritedValOverridden()
{
   cString value;
   getStorageVal(value);
   return !(value.isEmpty() || value == vindet);
}

int cwCheckButton::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__
      DWORD style = ((WCWnd*)_wnd)->GetStyle();
      if ( (mask & wsBtnAutoState) && ((style & 0xf) == BS_AUTOCHECKBOX || (style & 0xf) == BS_AUTO3STATE) )
         rc |= wsBtnAutoState;
      if ( (mask & wsBtn3State) && ((style & 0xf) == BS_3STATE || (style & 0xf) == BS_AUTO3STATE) )
         rc |= wsBtn3State;
   #elif defined __ECL_OS2__
      // ...
   #endif

   return rc | cwButtonCtl::onGetStyles(mask);
}

void cwCheckButton::onMakeStyles(int styles, int os_styles[]) const
{
   cwButtonCtl::onMakeStyles(styles, os_styles);

   #if defined __ECL_W32__
      if ( styles & wsBtnAutoState ) {
         if ( styles & wsBtn3State ) {
            os_styles[0] = (os_styles[0] & 0xf) | BS_AUTO3STATE;
         } else {
            os_styles[0] = (os_styles[0] & 0xf) | BS_AUTOCHECKBOX;
         }
      } else {
         if ( styles & wsBtn3State ) {
            os_styles[0] = (os_styles[0] & 0xf) | BS_3STATE;
         } else {
            os_styles[0] = (os_styles[0] & 0xf) | BS_CHECKBOX;
         }
      }
   #elif defined __ECL_OS2__
      // ...
   #endif
}

void cwCheckButton::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      int ctl_style = getStyles(wsBtnAutoState|wsBtn3State);
      ctl_style |= (add & wsBtnAutoState|wsBtn3State);
      if ( remove & wsBtnAutoState ) ctl_style &= ~wsBtnAutoState;
      if ( remove & wsBtn3State ) ctl_style &= ~wsBtn3State;

      if ( ctl_style & wsBtnAutoState ) {
         if ( ctl_style & wsBtn3State ) {
            ((WCButton*)_wnd)->SetButtonStyle(BS_AUTO3STATE);
         } else {
            ((WCButton*)_wnd)->SetButtonStyle(BS_AUTOCHECKBOX);
         }
      } else {
         if ( ctl_style & wsBtn3State ) {
            ((WCButton*)_wnd)->SetButtonStyle(BS_3STATE);
         } else {
            ((WCButton*)_wnd)->SetButtonStyle(BS_CHECKBOX);
         }
      }

   #elif defined __ECL_OS2__

      // ...

   #endif

   cwButtonCtl::onModifyStyles(add, remove, os_add, os_remove);
}

