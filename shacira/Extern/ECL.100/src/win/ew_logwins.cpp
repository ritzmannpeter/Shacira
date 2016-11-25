// ===========================================================================
// ew_logwins.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwLogWin       - Fenster fuer Protokollausgaben
//
// ===========================================================================

#include "win/ew_logwins.hpp"
#include "draw/ed_font.hpp"

#if defined __ECL_OS2__
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_time.hpp"
#include "win/ew_windows.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwLogWin
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwLogWin
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwLogWin : public cwWindow {
   ELO_DECLARE(cwLogWin,cwWindow)

public:

   // Konstruktor
   inline cwLogWin() : cwWindow(0) { init(); }
   // Destruktor
   virtual ~cwLogWin();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwWindow::wsUser,
      wsHasDate         = wsStart << 0,   // Datumsfeld wird angezeigt
      wsHasTime         = wsStart << 1,   // Zeitfeld wird angezeigt
      wsUser            = wsStart << 2,   // Benutzerdefinierte Styles
      //
      // Kombinationen:
      wsHasTimestamp    = wsHasDate|wsHasTime      // Datums- und Zeitfeld
   };


   // Allgemeines
   // ===========

   // Erzeugen des Dialogs
   void create(cwWindow *parent, int id,
               int style = wsChild | wsVisible,
               const cdRect& rect = cdRect());

   // Protokoll loeschen
   void clear();
   // Zeile Hinzufuegen
   void addLine(const cString& text, const cDateTime& tstamp = cDateTime());


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);

   // Wird aufgerufen, wenn sich der Presentation-Parameter 'pp' geaendert hat
   void onPresParamChanged(PPARAMS pp);
   // Wird aufgerufen, wenn der Presentation-Parameter 'pp' entfernt wurde
   void onPresParamRemoved(PPARAMS pp);


protected:

   // Interner Konstruktor
   cwLogWin(void *wnd);


private:

   // Styles
   int own_styles;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwLogWin
// ===========================================================================

cwLogWin::cwLogWin(void *wnd) :
   cwWindow(wnd)
{
   own_styles = 0;
}

cwLogWin::~cwLogWin()
{
}

void cwLogWin::init()
{
   own_styles = 0;

   #if defined __ECL_W32__
      _wnd = new WCHistoryCtrl(this);
   #elif defined __ECL_OS2__
   #endif
}

void cwLogWin::create(cwWindow *parent, int id, int style, const cdRect& rect)
{
   cwWindow::create(parent);

   #if defined __ECL_W32__

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);
      int mfc_style[3]; onMakeStyles(style, mfc_style);
      own_styles = mfc_style[2];

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( !((WCHistoryCtrl*)_wnd)->Create(NULL, NULL, mfc_style[0], mfc_rect, mfc_parent, id) )
         __ECL_ASSERT2__(0, ("Unable to create history control window"));
	   ((WCHistoryCtrl*)_wnd)->SetSmoothScrolling(FALSE);
	   ((WCHistoryCtrl*)_wnd)->SetDisplayContextMenu(FALSE);
      ((WCHistoryCtrl*)_wnd)->SetMaxNumEntries(1000);

   #elif defined __ECL_OS2__
      // ...
   #endif

   __attachDelayed();
}

void cwLogWin::clear()
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((WCHistoryCtrl*)_wnd)->ClearHistory();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

void cwLogWin::addLine(const cString& text, const cDateTime& tstamp)
{
   cString line;

   if ( (own_styles & wsHasTimestamp) == wsHasTimestamp ) {
      line = tstamp.getStr() + " " + text;
   } else if ( own_styles & wsHasDate ) {
      line = tstamp.getDate().getStr() + " " + text;
   } else if ( own_styles & wsHasTime ) {
      line = tstamp.getTime().getStr() + " " + text;
   } else {
      line = text;
   }

   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         ((WCHistoryCtrl*)_wnd)->AddLine((const char *)line, FALSE);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}


// Ueberschriebene Events
// ======================

int cwLogWin::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      if ( (mask & wsHasDate) && (own_styles & wsHasDate) )
         rc |= wsHasDate;
      if ( (mask & wsHasTime) && (own_styles & wsHasTime) )
         rc |= wsHasTime;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwWindow::onGetStyles(mask);
}

void cwLogWin::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      cwWindow::onMakeStyles(styles, os_styles);
      os_styles[2] = 0;

      if ( styles & wsHasDate )
         os_styles[2] |= wsHasDate;
      if ( styles & wsHasTime )
         os_styles[2] |= wsHasTime;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwLogWin::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsHasDate )
         own_styles |= wsHasDate;
      if ( add & wsHasTime )
         own_styles |= wsHasTime;

      if ( remove & wsHasDate )
         own_styles &= ~wsHasDate;
      if ( remove & wsHasTime )
         own_styles &= ~wsHasTime;

      cwWindow::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwLogWin::onPresParamChanged(PPARAMS pp)
{
   if ( __ECL_ASSERT1__(_wnd != 0) ) {
      #if defined __ECL_W32__
         if ( pp == ppFgndColor ) {
            cdColor color; getPresParam(ppFgndColor, color);
            ((WCHistoryCtrl*)_wnd)->SetTextColor(color.getOsVal());
            return;
         } else if ( pp == ppBkgndColor ) {
            cdColor color; getPresParam(ppBkgndColor, color);
            ((WCHistoryCtrl*)_wnd)->SetBackColor(color.getOsVal());
            return;
         } else if ( pp == ppFont ) {
            cString fontname; getPresParam(ppFont, fontname);
            cdFont font; font.create(fontname);
            ((WCHistoryCtrl*)_wnd)->SetFont((CFont*)ccdFont::getFont(font));
            return;
         }
      #elif defined __ECL_OS2__
         // ...
      #endif
   }

   cwWindow::onPresParamChanged(pp);
}

void cwLogWin::onPresParamRemoved(PPARAMS pp)
{
   cwWindow::onPresParamRemoved(pp);
}

