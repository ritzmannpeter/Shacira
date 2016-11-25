// ===========================================================================
// ew_statctls.cpp                                              ______ /  ECL
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
//           +-cwStaticCtl       - Basisklasse fuer alle statischen Controls
//              |
//              +--cwText        - Statischer Text
//              |
//              +--cwIcon        - Icon
//              |
//              +--cwBitmap      - Bitmap
//
// ===========================================================================

#include "win/ew_statctls.hpp"

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
// Definition cwStaticCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwStaticCtl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwStaticCtl : public cwControl {
   ELO_DECLARE(cwStaticCtl,cwControl)
   friend class ccwStaticCtl;

public:

   // Konstruktor
   inline cwStaticCtl() : cwControl(0) { init(); }
   // Destruktor
   virtual ~cwStaticCtl();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwControl::wsUser,
      wsText            = wsStart << 0,   // Control zeigt Text an
      wsIcon            = wsStart << 1,   // Control zeigt Icon an
      wsBitmap          = wsStart << 2,   // Control zeigt Bitmap an
      wsCenter          = wsStart << 3,   // Element zentriert (horiz + vert)
      wsUser            = wsStart << 4    // Benutzerdefinierte Styles
   };


   // Images
   // ======

   // Icon als Image setzen
   void setImage(const cIcon& icon);
   // Bitmap als Image setzen
   void setImage(const cBitmap& bitmap);


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
   cwStaticCtl(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwStaticCtl
// ===========================================================================

cwStaticCtl::cwStaticCtl(void *wnd) :
   cwControl(wnd)
{
}

cwStaticCtl::~cwStaticCtl()
{
}

void cwStaticCtl::init()
{
   #if defined __ECL_W32__
      _wnd = new WCStatic(this);
   #elif defined __ECL_OS2__
   #endif
}


// Images
// ======

void cwStaticCtl::setImage(const cIcon& icon)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCStatic *mfc_ctrl = (WCStatic*)_wnd;
         if ( __ECL_ASSERT1__(mfc_ctrl->m_hWnd != NULL) ) {
            HICON hIcon = (HICON)ccwHandle::getHandle(icon);
            mfc_ctrl->ModifyStyle(SS_BITMAP, SS_ICON);
            mfc_ctrl->SetIcon(hIcon);
         }
      #elif defined __ECL_OS2__
      #endif
   }
}

void cwStaticCtl::setImage(const cBitmap& bitmap)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         WCStatic *mfc_ctrl = (WCStatic*)_wnd;
         if ( __ECL_ASSERT1__(mfc_ctrl->m_hWnd != NULL) ) {
            HBITMAP hBitmap = (HBITMAP)ccwHandle::getHandle(bitmap);
            mfc_ctrl->ModifyStyle(SS_ICON, SS_BITMAP);
            mfc_ctrl->SetBitmap(hBitmap);
         }
      #elif defined __ECL_OS2__
      #endif
   }
}


// Window-Styles
// =============

int cwStaticCtl::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();

      if ( (mask & wsText) && (style & SS_ICON|SS_BITMAP) == 0 )
         rc |= wsText;
      if ( (mask & wsIcon) && (style & SS_ICON) )
         rc |= wsIcon;
      if ( (mask & wsBitmap) && (style & SS_BITMAP) )
         rc |= wsBitmap;
      if ( (mask & wsCenter) && (style & SS_CENTERIMAGE) )
         rc |= wsCenter;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwWindow::onGetStyles(mask);
}

void cwStaticCtl::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      cwControl::onMakeStyles(styles, os_styles);

      if ( styles & wsText )
         os_styles[0] &= ~(SS_ICON|SS_BITMAP);
      if ( styles & wsIcon )
         os_styles[0] = (os_styles[0] & ~SS_BITMAP) | SS_ICON;
      if ( styles & wsBitmap )
         os_styles[0] = (os_styles[0] & ~SS_ICON) | SS_BITMAP;
      if ( styles & wsCenter )
         os_styles[0] |= SS_CENTERIMAGE;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwStaticCtl::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsText )
         os_remove[0] |= SS_ICON | SS_BITMAP;
      if ( add & wsCenter )
         os_add[0] |= SS_CENTERIMAGE;
      if ( add & wsIcon ) {
         os_add[0] |= SS_ICON;
         os_remove[0] |= SS_BITMAP;
      }
      if ( add & wsBitmap ) {
         os_add[0] |= SS_BITMAP;
         os_remove[0] |= SS_ICON;
      }

      if ( remove & wsCenter )
         os_remove[0] |= SS_CENTERIMAGE;
      if ( remove & wsIcon )
         os_remove[0] |= SS_ICON;
      if ( remove & wsBitmap )
         os_remove[0] |= SS_BITMAP;

      cwControl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwText
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwStaticCtl
//              +--cwText
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwText : public cwStaticCtl {
   ELO_DECLARE(cwText,cwStaticCtl)

public:

   // Konstruktor
   inline cwText() : cwStaticCtl(0) { init(); }
   // Destruktor
   virtual ~cwText();


   // Allgemeines
   // ===========

   // Erzeugen des Controls mit statischem Text
   void create(cwWindow *parent, int id, cString caption,
               int style = wsChild | wsVisible | wsBorder,
               const cdRect& rect = cdRect());
   // Erzeugen des Controls mit gebundener Storage
   void create(cwWindow *parent, int id, csStorage *store,
               int style = wsChild | wsVisible | wsBorder,
               const cdRect& rect = cdRect());


protected:

   // Ueberschriebene Events
   // ======================

   // Daten des Controls refreshen
   bool onRefreshCtl(csStorage *store);


protected:

   // Interner Konstruktor
   cwText(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwText
// ===========================================================================

cwText::cwText(void *wnd) :
   cwStaticCtl(wnd)
{
}

cwText::~cwText()
{
}

void cwText::init()
{
   #if defined __ECL_W32__
      _wnd = new WCStatic(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwText::create(cwWindow *parent, int id, cString caption,
                    int style, const cdRect& rect)
{
   cwStaticCtl::create(parent, id);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= SS_LEFT;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCStatic*)_wnd)->Create(caption, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create static control"));

      if ( mfc_style[1] != 0 )
         ((WCStatic*)_wnd)->ModifyStyleEx(0, mfc_style[1]);

   #else
      // ...
   #endif
}

void cwText::create(cwWindow *parent, int id, csStorage *store,
                    int style, const cdRect& rect)
{
   cwStaticCtl::create(parent, id, store);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= SS_LEFT;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCStatic*)_wnd)->Create("-", mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create static control"));

   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

bool cwText::onRefreshCtl(csStorage *store)
{
   cString value;

   if ( !getStorageVal(value) || isStorageNull() )
      value.clear();
   setText(value);

   return cwStaticCtl::onRefreshCtl(store);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwIcon
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwStaticCtl
//              +--cwIcon
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwIcon : public cwStaticCtl {
   ELO_DECLARE(cwIcon,cwStaticCtl)

public:

   // Konstruktor
   inline cwIcon() : cwStaticCtl(0) { init(); }
   // Destruktor
   virtual ~cwIcon();


   // Allgemeines
   // ===========

   // Erzeugen des Controls mit statischem Icon
   void create(cwWindow *parent, int id, cIcon icon,
               int style = wsChild | wsVisible,
               const cdRect& rect = cdRect());


protected:

   // Interner Konstruktor
   cwIcon(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwIcon
// ===========================================================================

cwIcon::cwIcon(void *wnd) :
   cwStaticCtl(wnd)
{
}

cwIcon::~cwIcon()
{
}

void cwIcon::init()
{
   #if defined __ECL_W32__
      _wnd = new WCStatic(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwIcon::create(cwWindow *parent, int id, cIcon icon,
                    int style, const cdRect& rect)
{
   cwStaticCtl::create(parent, id);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= SS_ICON;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCStatic*)_wnd)->Create(NULL, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create icon control"));

   #else
      // ...
   #endif

   setImage(icon);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwBitmap
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwStaticCtl
//              +--cwBitmap
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwBitmap : public cwStaticCtl {
   ELO_DECLARE(cwBitmap,cwStaticCtl)

public:

   // Konstruktor
   inline cwBitmap() : cwStaticCtl(0) { init(); }
   // Destruktor
   virtual ~cwBitmap();


   // Allgemeines
   // ===========

   // Erzeugen des Controls mit statischem Icon
   void create(cwWindow *parent, int id, cBitmap bmp,
               int style = wsChild | wsVisible, const cdRect& rect = cdRect());


protected:

   // Interner Konstruktor
   cwBitmap(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwBitmap
// ===========================================================================

cwBitmap::cwBitmap(void *wnd) :
   cwStaticCtl(wnd)
{
}

cwBitmap::~cwBitmap()
{
}

void cwBitmap::init()
{
   #if defined __ECL_W32__
      _wnd = new WCStatic(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwBitmap::create(cwWindow *parent, int id, cBitmap bmp,
                    int style, const cdRect& rect)
{
   cwStaticCtl::create(parent, id);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= SS_BITMAP;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCStatic*)_wnd)->Create(NULL, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create bitmap control"));

   #else
      // ...
   #endif

   setImage(bmp);
}


