// ===========================================================================
// ew_toolbars.cpp                                              ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwToolWin               - Fenster zur Aufnahme von Buttons, usw.
//        |
//        +-cwDockable
//           |
//           +--cwToolBar           - Typischer Toolbar mit Buttons
//           |
//           +--cwDialogBar         - Bar fuer komplexere Dialoge
//           |
//           +--cwStatusBar         - Bar fuer Statusinformationen
//
// ===========================================================================

#include "win/ew_toolbars.hpp"
#include "base/eb_err.hpp"
#include "base/eb_array.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
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

#include "base/eb_elo.hpp"
#include "win/ew_frames.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cwToolWin
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwToolWin
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwToolWin : public cwWindow {
   ELO_DECLARE(cwToolWin,cwWindow)
   friend class ccwToolWin;

public:

   // Konstruktor
   inline cwToolWin() : cwWindow(0) { init(); }
   // Destruktor
   virtual ~cwToolWin();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwWindow::wsUser,
      wsAlignTop        = wsStart << 0,   // Oben im Client-Bereich des Parents
      wsAlignBottom     = wsStart << 1,   // Unten im Client-Bereich des Parents
      wsFlatBtns        = wsStart << 2,   // Flache Buttons benutzen
      wsTextBtns        = wsStart << 3,   // Buttons mit Text benutzen
      wsUser            = wsStart << 4    // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen eines Toolbar-Windows
   void create(cwWindow *parent, int id,
               int style = wsChild | wsVisible | wsAlignTop | wsFlatBtns,
               const cdRect& rect = cdRect());
   // Erzeugen eines Toolbar-Windows ueber eine Toolbar-Resource
   void create(cwWindow *parent, int id, const cResource& res,
               int style = wsChild | wsVisible | wsAlignTop | wsFlatBtns,
               const cdRect& rect = cdRect());

/*
   // Button-Styles
   // =============

   // Hinweis: Falls ueber eine 'index_or_id' eine ID spezifiziert wird
   // (by_id = true), wird eine nach ECL-Konventionen kodierte ID erwartet,
   // also z.B. cwCmdCmds::cmdFileOpen fuer eine Standard-CMD-ID.

   enum BUTTON_STYLE {
      bsPushButton,     // Button verhaelt sich wie Push-Button (Default)
      bsCheckButton     // Button verhaelt sich wie Check-Button
   };

   // Button-Style fuer Button 'index_or_id' setzen
   void setButtonStyle(int index_or_id, BUTTON_STYLE bs, bool by_id = false);
   // Button-Style fuer Button 'index_or_id' erfragen
   BUTTON_STYLE getButtonStyle(int index_or_id, bool by_id = false) const;
*/


protected:

   // Hinzugefuegte Events
   // ====================

   enum DD_RESULT {     // Rueckgabewerte fuer onDropDown:
      ddrNotHandled,    //  - Event wurde nicht behandelt (Default)
      ddrHandled,       //  - Knopf wurde als Drop-Down behandelt
      ddrNormalBtn      //  - Knopf wurde als normaler Knopf behandelt
   };

   // Wird aufgerufen, wenn ein DropDown-Knopf gedrueckt wird
   virtual DD_RESULT onDropDown(int btn_id);


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
   cwToolWin(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwToolWin
// ===========================================================================

cwToolWin::cwToolWin(void *wnd)
   : cwWindow(wnd)
{
   init();
}

cwToolWin::~cwToolWin()
{
}

void cwToolWin::init()
{
   #if defined __ECL_W32__
      _wnd = new WCToolBarCtrl(this);
   #elif defined __ECL_OS2__
   #endif
}


// Allgemeines
// ===========

void cwToolWin::create(cwWindow *parent, int id, int style, const cdRect& rect)
{
   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[4]; onMakeStyles(style, mfc_style);

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCToolBarCtrl*)_wnd)->Create(mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create toolbar window"));

      //((WCToolBarCtrl*)_wnd)->SetStyle(mfc_style[2]);

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwToolWin::create(cwWindow *parent, int id, const cResource& res, int style, const cdRect& rect)
{
   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[4]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_NORESIZE;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCToolBarCtrl*)_wnd)->Create(mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Could not create toolbar window"));

      //((WCToolBarCtrl*)_wnd)->SetStyle(mfc_style[2]);
      ((WCToolBarCtrl*)_wnd)->LoadToolBar(MAKEINTRESOURCE(res.getID()));

   #else
      // ...
   #endif

   __attachDelayed();
}


// Hinzugefuegte Events
// ====================

cwToolWin::DD_RESULT cwToolWin::onDropDown(int /*btn_id*/)
{
   return ddrNotHandled;
}


// Ueberschriebene Events
// ======================

int cwToolWin::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();
      DWORD tbstyle = ((WCToolBarCtrl*)_wnd)->GetStyle();

      if ( (mask & wsAlignTop) && (style & CCS_TOP) )
         rc |= wsAlignTop;
      if ( (mask & wsAlignBottom) && (style & CCS_BOTTOM) )
         rc |= wsAlignBottom;

      if ( (mask & wsFlatBtns) && (tbstyle & TBSTYLE_FLAT) )
         rc |= wsFlatBtns;
      if ( (mask & wsTextBtns) && (tbstyle & TBSTYLE_LIST) )
         rc |= wsTextBtns;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwWindow::onGetStyles(mask);
}

void cwToolWin::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      // Die Implementierung von onMakeStyles fuer cwToolWin's
      // benutzt insgesamt 4 int's:
      //
      //    os_styles[0] - Standard-Window-Styles
      //    os_styles[1] - Extended-Window-Styles
      //    os_styles[2] - Standard-ToolbarCtrl-Styles
      //    os_styles[3] - Extended-ToolbarCtrl-Styles

      cwWindow::onMakeStyles(styles, os_styles);
      os_styles[2] = os_styles[3] = 0;

      if ( styles & wsAlignTop )
         os_styles[0] |= CCS_TOP;
      if ( styles & wsAlignBottom )
         os_styles[0] |= CCS_BOTTOM;
      if ( styles & wsFlatBtns )
         os_styles[0] |= TBSTYLE_FLAT;
      if ( styles & wsTextBtns )
         os_styles[0] |= TBSTYLE_LIST;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwToolWin::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      // Die Implementierung von onModifyStyles fuer cwToolWin's
      // benutzt insgesamt 4 int's:
      //
      //    os_add/remove[0]     -  Standard-Window-Styles
      //    os_add/remove[1]     - Extended-Window-Styles
      //    add/remove_tbstyle   - Standard-ToolbarCtrl-Styles
      //    add/remove_tbexstyle - Extended-ToolbarCtrl-Styles

      int add_tbstyle = 0, remove_tbstyle = 0;
      //int add_tbexstyle = 0, remove_tbexstyle = 0;

      if ( add & wsAlignTop )
         os_add[0] |= CCS_TOP;
      if ( add & wsAlignBottom )
         os_add[0] |= CCS_BOTTOM;
      if ( add & wsFlatBtns )
         os_add[0] |= TBSTYLE_FLAT;
      if ( add & wsTextBtns )
         os_add[0] |= TBSTYLE_LIST;

      if ( remove & wsAlignTop )
         os_remove[0] |= CCS_TOP;
      if ( remove & wsAlignBottom )
         os_remove[0] |= CCS_BOTTOM;
      if ( remove & wsFlatBtns )
         os_remove[0] |= TBSTYLE_FLAT;
      if ( remove & wsTextBtns )
         os_remove[0] |= TBSTYLE_LIST;

      cwWindow::onModifyStyles(add, remove, os_add, os_remove);

      if ( add_tbstyle != 0 || remove_tbstyle != 0 ) {
         DWORD tbstyle = ((WCToolBarCtrl*)_wnd)->GetStyle();
         ((WCToolBarCtrl*)_wnd)->SetStyle((tbstyle & ~remove_tbstyle) | add_tbstyle);
      }

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// cwToolBar
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwDockable
//          +--cwToolBar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwToolBar : public cwDockable {
   ELO_DECLARE(cwToolBar,cwDockable)
   friend class ccwToolBar;

public:

   // Konstruktor
   inline cwToolBar() : cwDockable(0) { init(); }
   // Destruktor
   virtual ~cwToolBar();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwWindow::wsUser,
      wsAlignTop        = wsStart << 0,   // Oben im Client-Bereich des Parents
      wsAlignBottom     = wsStart << 1,   // Unten im Client-Bereich des Parents
      wsFlatBtns        = wsStart << 2,   // Flache Buttons benutzen
      wsTextBtns        = wsStart << 3,   // Buttons mit Text benutzen
      wsUser            = wsStart << 4    // Benutzerdefinierte Styles
   };


   // Allgemeines
   // ===========

   // Erzeugen eines Toolbar-Windows
   void create(cwFrame *parent, int id,
               int style = wsChild | wsVisible | wsAlignTop | wsFlatBtns,
               const cString& text = 0, const cdRect& rect = cdRect());
   // Erzeugen eines Toolbar-Windows aus einer Resource
   void create(cwFrame *parent, const cResource& res,
               int style = wsChild | wsVisible | wsAlignTop | wsFlatBtns,
               const cString& text = 0, const cdRect& rect = cdRect());


   // ToolBar einrichten
   // =====================

   enum BUTTON_STYLE {
      bsDefault,        // Button hat Default-Form (= bsPushButton)
      bsSeparator,      // Button ist ein Separator
      bsPushButton,     // Button verhaelt sich wie Push-Button (Default)
      bsCheckButton,    // Button verhaelt sich wie Check-Button
      bsMenuButton      // Button verhaelt sich wie ein Dropdown-Menu
   };

   enum BUTTON_FLAGS {
      bflGroup       = 0x01,  // Beginn einer Gruppe von Buttons
      bflAutosize    = 0x02   // Button passt Groesse automatisch an Text an
   };

   // Button 'index' einrichten (Default-Werte fuer Parameter = Keine Aenderung)
   void setupButton(int index, BUTTON_STYLE bs = bsDefault,
                    int flags = -1, int id = -1, int icon = -1, const char *text = 0);
   // Button 'index' einrichten (Nur Text, Alternative zu oben)
   void setupButton(int index, const char *text);
   // Konfiguration des ToolBars uebernehmen
   void setupConfig();


   // ToolBar verwalten
   // ====================

   // Hinweis: Falls ueber eine 'index_or_id' eine ID spezifiziert wird
   // (by_id = true), wird eine nach ECL-Konventionen kodierte ID erwartet,
   // also z.B. cwCmdCmds::cmdFileOpen fuer eine Standard-CMD-ID.

   // Button-Style fuer Button 'index_or_id' setzen
   void setButtonStyle(int index_or_id, BUTTON_STYLE bs, bool by_id = false);
   // Button-Style fuer Button 'index_or_id' erfragen
   BUTTON_STYLE getButtonStyle(int index_or_id, bool by_id = false) const;

   // Button-Flags fuer Button 'index_or_id' setzen
   void setButtonFlags(int index_or_id, int flags, bool by_id = false);
   // Button-Flags fuer Button 'index_or_id' erfragen
   int getButtonFlags(int index_or_id, bool by_id = false) const;

   // Text des Buttons 'index_or_id' setzen
   void setButtonText(int index_or_id, const cString& text, bool by_id = false);
   // Text des Buttons 'index_or_id' erfragen
   cString getButtonText(int index_or_id, bool by_id = false) const;


protected:

   // Hinzugefuegte Events
   // ====================

   enum DD_RESULT {     // Rueckgabewerte fuer onDropDown:
      ddrNotHandled,    //  - Event wurde nicht behandelt (Default)
      ddrHandled,       //  - Knopf wurde als Drop-Down behandelt
      ddrNormalBtn      //  - Knopf wurde als normaler Knopf behandelt
   };

   // Wird aufgerufen, wenn ein DropDown-Knopf gedrueckt wird
   virtual DD_RESULT onDropDown(int btn_id);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Andockseiten zu setzen
   void onSetDockSides(int sides, int os_sides);
   // Update Benutzerschnittstelle
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommandUI(cwCmdUI& cmd);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwToolBar(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwToolBar
// ===========================================================================

cwToolBar::cwToolBar(void *wnd)
   : cwDockable(wnd)
{
   init();
}

cwToolBar::~cwToolBar()
{
}

void cwToolBar::init()
{
}


// Allgemeines
// ===========

void cwToolBar::create(cwFrame *parent, int id, int style, const cString& text, const cdRect& rect)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   if ( (style & ~dksAlignMask) == 0 )
      style |= wsChild | wsVisible | wsAlignTop | wsFlatBtns;
   if ( (style & (wsAlignBottom|wsAlignTop)) == 0 )
      style |= wsAlignTop;

   cwDockable::_parent = parent;

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_id = id > 0 ? id : AFX_IDW_TOOLBAR;
      int mfc_style[4]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= CBRS_TOOLTIPS | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_FLYBY;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CRect(0,0,0,0);

      _wnd = new WCToolBar(this);
      if ( ((WCToolBar*)_wnd)->CreateEx(mfc_parent, mfc_style[3], mfc_style[0], mfc_rect, mfc_id) )
         __ECL_ASSERT2__(0, ("Could not create toolbar window"));
      //((WCToolBar*)_wnd)->SendMessage(TB_SETPADDING, 0, MAKELPARAM(3, 6)); // empirisch ermittelt
      ((WCToolBar*)_wnd)->EnableDocking(mfc_style[2] & CBRS_ALIGN_ANY);

   #else
      // ...
   #endif

   setDockSides(getDockSides());
   setText(text);

   __attachDelayed();
}

void cwToolBar::create(cwFrame *parent, const cResource& res, int style, const cString& text, const cdRect& rect)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   if ( (style & ~dksAlignMask) == 0 )
      style |= wsChild | wsVisible | wsAlignTop | wsFlatBtns;
   if ( (style & (wsAlignBottom|wsAlignTop)) == 0 )
      style |= wsAlignTop;

   cwDockable::_parent = parent;

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[4]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= CBRS_TOOLTIPS | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_FLYBY;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CRect(0,0,0,0);

      _wnd = new WCToolBar(this);
      if ( !((WCToolBar*)_wnd)->CreateEx(mfc_parent, mfc_style[3], mfc_style[0], mfc_rect) )
         __ECL_ASSERT2__(0, ("Could not create toolbar window"));

      //((WCToolBar*)_wnd)->SendMessage(TB_SETPADDING, 0, MAKELPARAM(3, 6)); // empirisch ermittelt
      ((WCToolBar*)_wnd)->EnableDocking(mfc_style[2] & CBRS_ALIGN_ANY);
      ((WCToolBar*)_wnd)->LoadToolBar(MAKEINTRESOURCE(res.getID()));

   #else
      // ...
   #endif

   setDockSides(getDockSides());
   setText(text);

   __attachDelayed();
}


// ToolBar einrichten
// =====================

void cwToolBar::setupButton(int index, BUTTON_STYLE bs, int flags, int id, int icon, const char *text)
{
   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0 && index >= 0) ) {

         UINT mfc_id, mfc_style; int mfc_image;
         mfc_wnd->GetButtonInfo(index, mfc_id, mfc_style, mfc_image);

         if ( bs != bsDefault ) {
            mfc_style &= ~(TBBS_BUTTON|TBBS_CHECKBOX|TBBS_DROPDOWN|TBBS_SEPARATOR);
            switch ( bs ) {
            case bsPushButton:   mfc_style |= TBBS_BUTTON; break;
            case bsCheckButton:  mfc_style |= TBBS_CHECKBOX; break;
            case bsMenuButton:   mfc_style |= TBBS_DROPDOWN; break;
            case bsSeparator:    mfc_style |= TBBS_SEPARATOR; break;
            }
         }

         if ( flags >= 0 ) {
            mfc_style &= ~(TBBS_GROUP|TBBS_AUTOSIZE);
            if ( flags & bflGroup )
               mfc_style |= TBBS_GROUP;
            if ( flags & bflAutosize )
               mfc_style |= TBBS_AUTOSIZE;
         }

         if ( id >= 0 )
            mfc_id = id;
         if ( icon >= 0 && (mfc_style & TBBS_SEPARATOR) == 0 )
            mfc_image = icon;

         mfc_wnd->SetButtonInfo(index, mfc_id, mfc_style, mfc_image);

         if ( text != 0 ) {
            mfc_wnd->SetButtonText(index, text);
            mfc_wnd->GetToolBarCtrl().AutoSize();
         }

      }
   #else
      // ...
   #endif
}

void cwToolBar::setupButton(int index, const char *text)
{
   setupButton(index, cwToolBar::bsDefault, -1, -1, -1, text);
}

void cwToolBar::setupConfig()
{
   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int count = mfc_wnd->GetToolBarCtrl().GetButtonCount();
         for ( int i = 0 ; i < count ; i++ ) {
            int mfc_style = mfc_wnd->GetButtonStyle(i);
            if ( !(mfc_style & TBBS_SEPARATOR) )
               mfc_style |= TBBS_AUTOSIZE;
            mfc_wnd->SetButtonStyle(i, mfc_style);
         }
         CRect temp;
         mfc_wnd->GetItemRect(0, &temp);
         mfc_wnd->SetSizes(CSize(temp.Width(), temp.Height()), CSize(16,15));
         mfc_wnd->GetToolBarCtrl().AutoSize();
         _parent->recalcLayout();
      }
   #else
      // ...
   #endif
}


// ToolBar verwalten
// ====================

void cwToolBar::setButtonStyle(int index_or_id, BUTTON_STYLE bs, bool by_id)
{
   if ( by_id
     && index_or_id > cwCmdCmds::cmdStandardFirst
     && index_or_id < cwCmdCmds::cmdStandardLast )
   {
      index_or_id = cwCmdCmds::convID(cwCmdCmds::STDCMDS(index_or_id));
   }

   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int mfc_index = by_id ? mfc_wnd->CommandToIndex(index_or_id) : index_or_id;
         int mfc_style;
         switch ( bs ) {
         case bsPushButton:   mfc_style = TBBS_BUTTON; break;
         case bsCheckButton:  mfc_style = TBBS_CHECKBOX; break;
         case bsMenuButton:   mfc_style = TBBS_DROPDOWN; break;
         case bsSeparator:    mfc_style = TBBS_SEPARATOR; break;
         default:             mfc_style = TBBS_BUTTON; break;
         }
         if ( __ECL_ASSERT1__(mfc_index >= 0) ) {
            mfc_wnd->SetButtonStyle(mfc_index, mfc_style);
         }
      }
   #else
      // ...
   #endif
}

cwToolBar::BUTTON_STYLE cwToolBar::getButtonStyle(int index_or_id, bool by_id) const
{
   if ( by_id
     && index_or_id > cwCmdCmds::cmdStandardFirst
     && index_or_id < cwCmdCmds::cmdStandardLast )
   {
      index_or_id = cwCmdCmds::convID(cwCmdCmds::STDCMDS(index_or_id));
   }

   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int mfc_index = by_id ? mfc_wnd->CommandToIndex(index_or_id) : index_or_id;
         if ( __ECL_ASSERT1__(mfc_index >= 0) ) {
            int mfc_style = mfc_wnd->GetButtonStyle(mfc_index);
            if ( mfc_style & TBBS_SEPARATOR )
               return bsSeparator;
            if ( mfc_style & TBBS_DROPDOWN )
               return bsMenuButton;
            if ( mfc_style & TBBS_CHECKBOX )
               return bsCheckButton;
            if ( mfc_style & TBBS_BUTTON )
               return bsPushButton;
         }
      }
   #else
      // ...
   #endif

   return bsDefault;
}

void cwToolBar::setButtonFlags(int index_or_id, int flags, bool by_id)
{
   if ( by_id
     && index_or_id > cwCmdCmds::cmdStandardFirst
     && index_or_id < cwCmdCmds::cmdStandardLast )
   {
      index_or_id = cwCmdCmds::convID(cwCmdCmds::STDCMDS(index_or_id));
   }

   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int mfc_index = by_id ? mfc_wnd->CommandToIndex(index_or_id) : index_or_id;
         if ( __ECL_ASSERT1__(mfc_index >= 0) ) {
            int mfc_style = mfc_wnd->GetButtonStyle(mfc_index);
            mfc_style &= ~(TBBS_AUTOSIZE|TBBS_GROUP);
            if ( flags & bflGroup )
               mfc_style |= TBBS_GROUP;
            if ( flags & bflAutosize )
               mfc_style |= TBBS_AUTOSIZE;
            mfc_wnd->SetButtonStyle(mfc_index, mfc_style);
         }
      }
   #else
      // ...
   #endif
}

int cwToolBar::getButtonFlags(int index_or_id, bool by_id) const
{
   if ( by_id
     && index_or_id > cwCmdCmds::cmdStandardFirst
     && index_or_id < cwCmdCmds::cmdStandardLast )
   {
      index_or_id = cwCmdCmds::convID(cwCmdCmds::STDCMDS(index_or_id));
   }

   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int mfc_index = by_id ? mfc_wnd->CommandToIndex(index_or_id) : index_or_id;
         if ( __ECL_ASSERT1__(mfc_index >= 0) ) {
            int mfc_style = mfc_wnd->GetButtonStyle(mfc_index);
            int ecl_style = 0;
            if ( mfc_style & TBBS_GROUP )
               ecl_style |= bflGroup;
            if ( mfc_style & TBBS_AUTOSIZE )
               ecl_style |= bflAutosize;
            return ecl_style;
         }
      }
   #else
      // ...
   #endif

   return 0;
}

void cwToolBar::setButtonText(int index_or_id, const cString& text, bool by_id)
{
   if ( by_id
     && index_or_id > cwCmdCmds::cmdStandardFirst
     && index_or_id < cwCmdCmds::cmdStandardLast )
   {
      index_or_id = cwCmdCmds::convID(cwCmdCmds::STDCMDS(index_or_id));
   }

   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int mfc_index = by_id ? mfc_wnd->CommandToIndex(index_or_id) : index_or_id;
         if ( __ECL_ASSERT1__(mfc_index >= 0) ) {
            mfc_wnd->SetButtonText(mfc_index, text);
         }
      }
   #else
      // ...
   #endif
}

cString cwToolBar::getButtonText(int index_or_id, bool by_id) const
{
   if ( by_id
     && index_or_id > cwCmdCmds::cmdStandardFirst
     && index_or_id < cwCmdCmds::cmdStandardLast )
   {
      index_or_id = cwCmdCmds::convID(cwCmdCmds::STDCMDS(index_or_id));
   }

   #if defined __ECL_W32__
      WCToolBar *mfc_wnd = (WCToolBar*)_wnd;
      if ( __ECL_ASSERT1__(mfc_wnd != 0) ) {
         int mfc_index = by_id ? mfc_wnd->CommandToIndex(index_or_id) : index_or_id;
         if ( __ECL_ASSERT1__(mfc_index >= 0) ) {
            CString text = mfc_wnd->GetButtonText(mfc_index);
            return (const char *)text;
         }
      }
   #else
      // ...
   #endif

   return 0;
}


// Hinzugefuegte Events
// ====================

cwToolBar::DD_RESULT cwToolBar::onDropDown(int /*btn_id*/)
{
   return ddrNotHandled;
}


// Ueberschriebene Events
// ======================

void cwToolBar::onSetDockSides(int /*sides*/, int os_sides)
{
   #if defined __ECL_W32__
      ((WCToolBar*)_wnd)->EnableDocking(os_sides);
   #else
      // ...
   #endif
}

bool cwToolBar::onCommandUI(cwCmdUI& /*cmd*/)
{
/*
   cEloSelection private_sel, *sel = &private_sel;

   for ( cwWindow *win = _parent ; win != 0 ; win = win->getActiveChild() ) {
      if ( win->hasWindowElemSelection() ) {
         if ( (sel = win->getWindowElemSelection()) == 0 ) {
            win->updateWindowElemSelection(private_sel);
            sel = &private_sel;
         }
         break;
      }
   }

   cmd.setEnable(isOperationEnabled(cmd.getId(), sel));
   return true;
*/
   return false;
}

int cwToolBar::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();
      DWORD tbstyle = ((WCToolBarCtrl*)_wnd)->GetStyle();

      if ( (mask & wsAlignTop) && (style & CCS_TOP) )
         rc |= wsAlignTop;
      if ( (mask & wsAlignBottom) && (style & CCS_BOTTOM) )
         rc |= wsAlignBottom;

      if ( (mask & wsFlatBtns) && (tbstyle & TBSTYLE_FLAT) )
         rc |= wsFlatBtns;
      if ( (mask & wsTextBtns) && (tbstyle & TBSTYLE_LIST) )
         rc |= wsTextBtns;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwDockable::onGetStyles(mask);
}

void cwToolBar::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      // Die Implementierung von onMakeStyles fuer cwToolWin's
      // benutzt insgesamt 4 int's:
      //
      //    os_styles[0] - Standard-Window-Styles
      //    os_styles[1] - Extended-Window-Styles
      //    os_styles[2] - Standard-ToolbarCtrl-Styles
      //    os_styles[3] - Extended-ToolbarCtrl-Styles

      cwDockable::onMakeStyles(styles, os_styles);
      os_styles[2] = os_styles[3] = 0;

      if ( styles & wsAlignTop )
         os_styles[0] |= CCS_TOP | CBRS_ALIGN_TOP;
      if ( styles & wsAlignBottom )
         os_styles[0] |= CCS_BOTTOM | CBRS_ALIGN_BOTTOM;

      if ( styles & wsTextBtns )
         os_styles[3] |= TBSTYLE_LIST;
      if ( styles & wsFlatBtns )
         os_styles[3] |= TBSTYLE_FLAT;

      if ( styles & wsDockLeft )
         os_styles[2] |= CBRS_LEFT;
      if ( styles & wsDockRight )
         os_styles[2] |= CBRS_RIGHT;
      if ( styles & wsDockTop )
         os_styles[2] |= CBRS_TOP;
      if ( styles & wsDockBottom )
         os_styles[2] |= CBRS_BOTTOM;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwToolBar::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      // Die Implementierung von onModifyStyles fuer cwToolWin's
      // benutzt insgesamt 4 int's:
      //
      //    os_add/remove[0]     -  Standard-Window-Styles
      //    os_add/remove[1]     - Extended-Window-Styles
      //    add/remove_tbstyle   - Standard-ToolbarCtrl-Styles
      //    add/remove_tbexstyle - Extended-ToolbarCtrl-Styles

      int add_tbstyle = 0, remove_tbstyle = 0;
      //int add_tbexstyle = 0, remove_tbexstyle = 0;

      if ( add & wsAlignTop )
         os_add[0] |= CCS_TOP;
      if ( add & wsAlignBottom )
         os_add[0] |= CCS_BOTTOM;

      if ( add & wsTextBtns )
         add_tbstyle |= TBSTYLE_LIST;
      if ( add & wsFlatBtns )
         add_tbstyle |= TBSTYLE_FLAT;

      if ( remove & wsTextBtns )
         remove_tbstyle |= TBSTYLE_LIST;
      if ( remove & wsFlatBtns )
         remove_tbstyle |= TBSTYLE_FLAT;

      if ( remove & wsAlignTop )
         os_remove[0] |= CCS_TOP;
      if ( remove & wsAlignBottom )
         os_remove[0] |= CCS_BOTTOM;
      if ( remove & wsFlatBtns )
         os_remove[0] |= TBSTYLE_FLAT;
      if ( remove & wsTextBtns )
         os_remove[0] |= TBSTYLE_LIST;

      cwDockable::onModifyStyles(add, remove, os_add, os_remove);

      if ( add_tbstyle != 0 || remove_tbstyle != 0 ) {
         DWORD tbstyle = ((WCToolBarCtrl*)_wnd)->GetStyle();
         ((WCToolBarCtrl*)_wnd)->SetStyle((tbstyle & ~remove_tbstyle) | add_tbstyle);
      }

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// cwDialogBar
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwDockable
//          +--cwDialogBar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDialogBar : public cwDockable {
   ELO_DECLARE(cwDialogBar,cwDockable)
   friend class ccwDialogBar;

public:

   // Konstruktor
   inline cwDialogBar() : cwDockable(0) { init(); }
   // Destruktor
   virtual ~cwDialogBar();


   // Allgemeines
   // ===========

   // Erzeugen eines Dialogbar-Windows aus einer Resource
   void create(cwFrame *parent, const cResource& res, int style = 0, int id = 0);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Andockseiten zu setzen
   void onSetDockSides(int sides, int os_sides);


protected:

   // Interner Konstruktor
   cwDialogBar(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwDialogBar
// ===========================================================================

cwDialogBar::cwDialogBar(void *wnd)
   : cwDockable(wnd)
{
   init();
}

cwDialogBar::~cwDialogBar()
{
}

void cwDialogBar::init()
{
}


// Allgemeines
// ===========

void cwDialogBar::create(cwFrame *parent, const cResource& res, int style, int id)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   //cwDockable::style = style;
   cwDockable::_parent = parent;

   #if defined __ECL_W32__

      int mfc_style = CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER;
      switch ( style & dksAlignMask ) {
      case dksAlignNone:   mfc_style |= CBRS_NOALIGN; break;
      case dksAlignLeft:   mfc_style |= CBRS_LEFT; break;
      case dksAlignRight:  mfc_style |= CBRS_RIGHT; break;
      case dksAlignTop:    mfc_style |= CBRS_TOP; break;
      case dksAlignBottom: mfc_style |= CBRS_BOTTOM; break;
      }

      CWnd *parent_wnd = (CWnd*)__getWnd(parent);
      int mfc_id = id > 0 ? id : res.getID();

      _wnd = new WCDialogBar(this);
      if ( !((WCDialogBar*)_wnd)->Create(parent_wnd, res.getID(), mfc_style, mfc_id) )
         __ECL_ASSERT2__(0, ("Could not create dialogbar window"));

      setDockSides(getDockSides());

   #else
      // ...
   #endif

   __attachDelayed();
}


// Ueberschriebene Events
// ======================

void cwDialogBar::onSetDockSides(int /*sides*/, int os_sides)
{
   #if defined __ECL_W32__
      ((WCDialogBar*)_wnd)->EnableDocking(os_sides);
   #else
      // ...
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// cwStatusBar
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwDockable
//          +--cwStatusBar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwStatusBar : public cwDockable {
   ELO_DECLARE(cwStatusBar,cwDockable)
   friend class ccwStatusBar;

public:

   // Konstruktor
   inline cwStatusBar() : cwDockable(0) { init(); }
   // Destruktor
   virtual ~cwStatusBar();


   // Allgemeines
   // ===========

   // Erzeugen eines Statusbar-Windows
   void create(cwFrame *parent, int style = 0, int id = 0);


   // Status-Bar einrichten
   // =====================

   // Pane 'pane' einrichten (Muss fuer jedes Pane einmal aufgerufen werden!)
   void setupPane(int pane, const cResource& text_id, bool enabled = true);
   // Pane 'pane' ueber Breite einrichten (Alternative zu oben)
   void setupPane(int pane, int width, const char *def_text = 0, bool enabled = true);
   // Konfiguration des Status-Bars uebernehmen
   void setupConfig();


   // Status-Bar verwalten
   // ====================

   // Neuen Text fuer Pane 'pane' setzen
   void setPaneText(int pane, const char *text);
   // Aktuellen Text von Pane 'pane' erfragen
   cString getPaneText(int pane) const;

   // Neuen Breite fuer Pane 'pane' setzen
   void setPaneWidth(int pane, int width);
   // Aktuelle Breite von Pane 'pane' erfragen
   int getPaneWidth(int pane) const;

   // Enabled-Status fuer Pane 'pane' setzen
   void setPaneEnabled(int pane, bool enable = true);
   // Ist die Pane 'pane' aktiv?
   bool isPaneEnabled(int pane) const;


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Andockseiten zu setzen
   void onSetDockSides(int sides, int os_sides);


protected:

   // Interner Konstruktor
   cwStatusBar(void *wnd);


private:

   // Initialisierung
   void init();

   struct ADD_INFO;
   ADD_INFO *info;

};

#endif /*__INTERFACE__*/


// Implementierung cwStatusBar
// ===========================================================================

   struct SB_PANE {
      SB_PANE() : text_id(0) { width = 0; enabled = false; }
      SB_PANE(const cResource& t, bool e) : text_id(t) { width = 0; enabled = e; }
      SB_PANE(const char *t, int w, bool e) : text_id(0) { def_text = t; width = w; enabled = e; }
      cResource text_id;
      cString def_text;
      int width;
      bool enabled;
   };

   struct cwStatusBar::ADD_INFO {
      cArray<SB_PANE,const SB_PANE&> panes;
   };

cwStatusBar::cwStatusBar(void *wnd)
   : cwDockable(wnd)
{
   init();
}

cwStatusBar::~cwStatusBar()
{
   delete info;
}

void cwStatusBar::init()
{
   info = new ADD_INFO;
}


// Allgemeines
// ===========

void cwStatusBar::create(cwFrame *parent, int style, int id)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   //cwDockable::style = style;
   cwDockable::_parent = parent;

   #if defined __ECL_W32__

      int mfc_style = WS_CHILD | WS_VISIBLE;
      switch ( style & dksAlignMask ) {
      case dksAlignNone:   mfc_style |= CBRS_NOALIGN; break;
      case dksAlignTop:    mfc_style |= CBRS_TOP; break;
      case dksAlignBottom: mfc_style |= CBRS_BOTTOM; break;
      }

      CWnd *parent_wnd = (CWnd*)__getWnd(parent);
      int mfc_id = id > 0 ? id : AFX_IDW_STATUS_BAR;

      _wnd = new WCStatusBar(this);
      if ( !((WCStatusBar*)_wnd)->CreateEx(parent_wnd, SBARS_SIZEGRIP, mfc_style, mfc_id) )
         __ECL_ASSERT2__(0, ("Could not create statusbar window"));

      // setDockSides(getDockSides());
      //UINT ind[] = { AFX_IDS_IDLEMESSAGE, 201, 202 };
      //((WCStatusBar*)_wnd)->SetIndicators(ind, 3);
      //((WCStatusBar*)_wnd)->SetPaneStyle(0, SBPS_NOBORDERS|SBPS_STRETCH);

   #else
      // ...
   #endif

   __attachDelayed();
}


// Status-Bar einrichten
// =====================

void cwStatusBar::setupPane(int pane, const cResource& text_id, bool enabled)
{
   if ( __ECL_ASSERT1__(pane >= 0 && pane < 100) )
      info->panes.setAtGrow(pane, SB_PANE(text_id, enabled));
}

void cwStatusBar::setupPane(int pane, int width, const char *def_text, bool enabled)
{
   if ( __ECL_ASSERT1__(pane >= 0 && pane < 100) )
      info->panes.setAtGrow(pane, SB_PANE(def_text, width, enabled));
}

void cwStatusBar::setupConfig()
{
   int pane_count = info->panes.getSize();

   #if defined __ECL_W32__

      UINT *inds = new UINT[pane_count];

      for ( int p = 0 ; p < pane_count ; p++ )
         inds[p] = info->panes[p].text_id.getID();

      ((WCStatusBar*)_wnd)->SetIndicators(inds, pane_count);
      ((WCStatusBar*)_wnd)->SetPaneStyle(0, SBPS_NOBORDERS|SBPS_STRETCH);

      delete inds;

   #else
      // ...
   #endif

   for ( int i = 0 ; i < pane_count ; i++ ) {
      if ( !info->panes[i].def_text.isEmpty() )
         setPaneText(i, info->panes[i].def_text);
      if ( info->panes[i].width > 0 )
         setPaneWidth(i, info->panes[i].width);
      setPaneEnabled(i, info->panes[i].enabled);
   }

}


// Status-Bar verwalten
// ====================

void cwStatusBar::setPaneText(int pane, const char *text)
{
   #if defined __ECL_W32__
      ((WCStatusBar*)_wnd)->SetPaneText(pane, text);
   #else
      // ...
   #endif
}

cString cwStatusBar::getPaneText(int pane) const
{
   #if defined __ECL_W32__
      return (const char *)((WCStatusBar*)_wnd)->GetPaneText(pane);
   #else
      // ...
   #endif
}

void cwStatusBar::setPaneWidth(int pane, int width)
{
   #if defined __ECL_W32__
      UINT id, style; int old_width;
      ((WCStatusBar*)_wnd)->GetPaneInfo(pane, id, style, old_width);
      if ( old_width != width )
         ((WCStatusBar*)_wnd)->SetPaneInfo(pane, id, style, width);
   #else
      // ...
   #endif
}

int cwStatusBar::getPaneWidth(int pane) const
{
   #if defined __ECL_W32__
      UINT id, style; int width;
      ((WCStatusBar*)_wnd)->GetPaneInfo(pane, id, style, width);
      return width;
   #else
      // ...
   #endif
}

void cwStatusBar::setPaneEnabled(int pane, bool enable)
{
   #if defined __ECL_W32__
      int mfc_style = ((WCStatusBar*)_wnd)->GetPaneStyle(pane) & ~SBPS_DISABLED;
      if ( !enable ) mfc_style |= SBPS_DISABLED;
      ((WCStatusBar*)_wnd)->SetPaneStyle(pane, mfc_style);
   #else
      // ...
   #endif
}

bool cwStatusBar::isPaneEnabled(int pane) const
{
   #if defined __ECL_W32__
      return !(((WCStatusBar*)_wnd)->GetPaneStyle(pane) & ~SBPS_DISABLED);
   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

void cwStatusBar::onSetDockSides(int /*sides*/, int /*os_sides*/)
{
   #if defined __ECL_W32__
      // Always docked!!! ((WCStatusBar*)_wnd)->EnableDocking(os_sides);
   #else
      // ...
   #endif
}


