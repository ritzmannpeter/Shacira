// ===========================================================================
// ew_frames.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//     |  |
//     |  +-cwFrame                 - Frame-Window
//     |     |
//     |     +--cwMultiDocFrame     - Multiple-Document-Frame-Window
//     |     |
//     |     +--cwMultiDocChild     - Multiple-Document-Child-Window
//     |
//     +-cwDockable                 - Dockbare Fenster
//        |
//        +-cwMiniFrame             - Mini-Frame-Window
//
// ===========================================================================

#include "win/ew_frames.hpp"
#include "win/ew_views.hpp"
#include "win/ew_application.hpp"
#include "base/eb_err.hpp"
#include "base/eb_list.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/utool/OX3DTabView.h"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/ew_windows.hpp"

class cwView;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cwFrame
// ---------------------------------------------------------------------------
//
// Anlegen eines Frames mit einem assoziierten View:
//
//    cwFrame frame;
//    cwMyView1 view1;
//    frame.setView(&view);
//    frame.create(res_id, 0);
//
// Anlegen eines Frames mit mehreren assoziierten Views:
//
//    cwFrame frame;
//    cwMyViewA view1;
//    cwMyViewB view2, view3;
//    frame.setView(&view1);
//    frame.addView(&view2, cwFrame::vpLeft, 250 /*pix*/);
//    frame.addView(&view3, cwFrame::vpBottom);
//    frame.create(res_id, 0);
//
// cBase
//  +--cwWindow
//      +--cwFrame
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwFrame : public cwWindow {
   ELO_DECLARE(cwFrame,cwWindow)
   friend class ccwFrame;

public:

   // Konstruktor
   inline cwFrame() : cwWindow(0) { init(); }
   // Destruktor
   virtual ~cwFrame();


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwWindow::wsUser,
      wsCaption         = wsStart << 0,   // Fenster hat Titelzeile
      wsSysMenu         = wsStart << 1,   // Fenster hat Systemmenue
      wsMinimize        = wsStart << 2,   // Fenster hat Minimize-Knopf
      wsMaximize        = wsStart << 3,   // Fenster hat Maximize-Knopf
      wsUser            = wsStart << 4,   // Benutzerdefinierte Styles
      //
      // Kombinationen:
      wsMinMax          = wsMinimize|wsMaximize,      // Minimize- und Maximize-Knopf
      wsFrameCaption    = wsCaption|wsSysMenu,        // Titelzeile und Systemmenue
      wsFrameTitle      = wsFrameCaption|wsMinMax,    // Komplette Titelzeile
      wsFrameWindow     = wsBorderSize|wsFrameTitle,  // Normales Frame-Window
      //
      // Alte Namen (Kompatibilitaet):
      fsDockNone        = wsDockNone,
      fsDockLeft        = wsDockLeft,
      fsDockRight       = wsDockRight,
      fsDockTop         = wsDockTop,
      fsDockBottom      = wsDockBottom,
      fsDockAny         = wsDockAny
   };


   // Allgemeines
   // ===========

   // Erzeugen eines Frame-Windows
   void create(cwWindow *parent, int style, cString text, const cdRect& rect = cdRect());
   // Erzeugen eines Top-Level-Frame-Windows
   void create(int style, cString text, const cdRect& rect = cdRect());

   // Erzeugen eines Frame-Windows aus einer Resource
   void create(cwWindow *parent, const cResource& res, int style);
   // Erzeugen eines Top-Level-Frame-Windows aus einer Resource
   void create(const cResource& res, int style);

   // Layout neuberechnen (z.B. nach Hinzufuegen/Entfernen von Docking-Fenstern)
   void recalcLayout(bool notify = true);

   // Erlaubt das Frame irgendwo Andockfenster?
   inline bool isDockable() const
      { return !!(dock_style & wsDockAny); }


   // Views
   // =====

   // Hinweis: Split-Views und Tabbed-Views nicht mischbar!

   enum POSITION {
      vpMain,        // Kennung fuer Haupt-View
      vpSame,        // Tabbing:   Neuer View hinter dem Hauptview
      vpLeft,        // Splitting: Neuer View links vom Hauptview
      vpRight,       // Splitting: Neuer View rechts vom Hauptview
      vpTop,         // Splitting: Neuer View ueber dem Hauptview
      vpBottom       // Splitting: Neuer View unter dem Hauptview
   };

   // Primaeren View setzen (muss VOR cwFrame::create aufgerufen werden!!)
   void setView(cwView *view);
   // Zusaetzliche Split-Views einfuegen (muss VOR cwFrame::create aufgerufen werden!!)
   void addView(cwView *view, POSITION pos, int size);

   // Primaeren Tab-View setzen (muss VOR cwFrame::create aufgerufen werden!!)
   void setTabView(cwView *view, cString name, bool is_tab3d = true);
   // Zusaetzliche Tab-Views einfuegen (muss VOR cwFrame::create aufgerufen werden!!)
   void addTabView(cwView *view, cString name);

   // Anzahl Views ermitteln (incl. primaerer View)
   int getViewCount() const;
   // Views ueber Index erfragen (incl. primaerer View)
   cwView *getView(int index) const;
   // Zeiger auf primaeren View erfragen (oder 0, falls nicht definiert)
   cwView *getMainView() const;

   // Zeiger auf aktiven View ermitteln
   cwView *getActiveView() const;
   // Index des aktiven Views ermitteln
   int getActiveViewIndex() const;
   // Aktiven View ueber cwView-Objekt setzen
   void setActiveView(cwView *view);

   // Titel des Views erfragen
   cString getViewTitle(const cwView *view) const;
   // Titel des Views setzen
   void setViewTitle(cwView *view, cString title);


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um die Frame-Views zu erzeugen
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   virtual bool onCreateViews(void *add_info);
   // Wird aufgerufen, um die Andockseiten zu setzen
   virtual void onSetDockSides(int sides, int os_sides);
   // Wird aufgerufen, um den Wechsel des aktuellen Views anzukuendigen (true = zulassen)
   virtual bool onViewChanging(cwView *cur_view);
   // Wird aufgerufen, um den Wechsel des aktuellen Views bekanntzugeben
   virtual void onViewChanged(cwView *prev_view, cwView *new_view);


   // Ueberschriebene Events
   // ======================

   // Fenster wird erzeugt
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onCreate();
   // Fenstererzeugung wird vorbereitet
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onPreCreate(void *add_data);

   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommandUI(cwCmdUI& cmd);

   // Wird aufgerufen, wenn ein Kindfenster den Focus erhaelt
   void onChildActivated(cwWindow *win);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Dock-Style-Flags des Fensters
   int dock_style;

   // Interner Konstruktor
   cwFrame(void *wnd);


private:

   struct FRAMEINFO;
   FRAMEINFO *info;

   // Initialisierung
   void init();

   // Split-Views erzeugen
   bool createSplitViews(int view_count, void *add_info);
   // Tabbed-Views erzeugen
   bool createTabbedViews(int view_count, void *add_info);

   // Intern: Wird von ccwFrame aufgerufen, um den Wechsel des aktuellen Views anzukuendigen
   bool onViewChanging();
   // Intern: Wird von ccwFrame aufgerufen, um den Wechsel des aktuellen Views bekanntzugeben
   void onViewChanged();

};

#endif /*__INTERFACE__*/


// Implementierung cwFrame
// ===========================================================================

#if defined __ECL_W32__

   class WCTabViewContainer : public COXTabViewContainer {
      cwFrame *frame;
   public:
      WCTabViewContainer(cwFrame *frame)
         { WCTabViewContainer::frame = frame; }
   protected:
      BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
      {
         switch ( message ) {
         case WM_NOTIFY:
            switch ( ((NMHDR*)lParam)->code ) {
            case TCN_SELCHANGING: if ( ccwFrame::onViewChanging(frame) ) return TRUE; break;
            case TCN_SELCHANGE:   ccwFrame::onViewChanged(frame); break;
            }
            break;
         }
         return COXTabViewContainer::OnChildNotify(message, wParam, lParam, pLResult);
      }
   };

   class WC3DTabViewContainer : public COX3DTabViewContainer {
      cwFrame *frame;
   public:
      WC3DTabViewContainer(cwFrame *frame)
         { WC3DTabViewContainer::frame = frame; }
   protected:
      BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
      {
         switch ( message ) {
         case WM_NOTIFY:
            switch ( ((NMHDR*)lParam)->code ) {
            case TCN_SELCHANGING: if ( ccwFrame::onViewChanging(frame) ) return TRUE; break;
            case TCN_SELCHANGE:   ccwFrame::onViewChanged(frame); break;
            }
            break;
         }
         return COX3DTabViewContainer::OnChildNotify(message, wParam, lParam, pLResult);
      }
   };

#endif

struct VIEWINFO {
   cwView *view;
   cwFrame::POSITION pos;
   int size;
   cString name;
   #if defined __ECL_W32__
      CSplitterWnd *splitter;
      int spp_x, spp_y;
   #endif
};

struct cwFrame::FRAMEINFO {
   cList<VIEWINFO,const VIEWINFO&> views;
   cwView *current_view;
   enum { MAIN, SPLIT, TAB } type;
   #if defined __ECL_W32__
      WCTabViewContainer *tab_cnr;
      WC3DTabViewContainer *tab3d_cnr;
   #endif
   FRAMEINFO();
   ~FRAMEINFO();
};

cwFrame::cwFrame(void *wnd)
   : cwWindow(wnd)
{
   init();
}

cwFrame::~cwFrame()
{
   delete info;
}

cwFrame::FRAMEINFO::FRAMEINFO()
{
   current_view = 0;
}

cwFrame::FRAMEINFO::~FRAMEINFO()
{
   IPOSITION pos = views.getHeadPosition();

   while ( pos != 0 ) {
      VIEWINFO& vwi = views.getNext(pos);
      #if defined __ECL_W32__
         if ( vwi.size >= 0 )
            delete vwi.splitter;
      #endif
   }

   #if defined __ECL_W32__
      delete tab_cnr;
      delete tab3d_cnr;
   #endif
}

void cwFrame::init()
{
   dock_style = 0;
   info = 0;
}


// Allgemeines
// ===========

void cwFrame::create(cwWindow *parent, int style, cString text, const cdRect& rect)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   cwFrame::dock_style = style & wsDockAny;

   if ( (style & ~wsDockAny) == 0 )
      style |= wsFrameWindow;

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      if ( text.isEmpty() ) mfc_style[0] |= FWS_ADDTOTITLE;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      CCreateContext cc;
      cc.m_pNewViewClass = getMainView() != 0 ?
          ccwView::__getRuntimeClass(getMainView())
        : cc.m_pNewViewClass = RUNTIME_CLASS(WCView);

      if ( isDockable() ) {
         _wnd = new WCFrameDockWnd(this);
         if ( !((WCFrameDockWnd*)_wnd)->Create(NULL, _T(text), mfc_style[0], mfc_rect, mfc_parent, 0, mfc_style[1], &cc) ) {
            __ECL_ASSERT2__(0, ("Could not create frame window"));
         } else {
            modifyStyles(dock_style, 0);
         }
      } else {
         _wnd = new WCFrameWnd(this);
         if ( !((WCFrameWnd*)_wnd)->Create(NULL, _T(text), mfc_style[0], mfc_rect, mfc_parent, 0, mfc_style[1], &cc) )
            __ECL_ASSERT2__(0, ("Could not create frame window"));
      }

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwFrame::create(int style, cString text, const cdRect& rect)
{
   create(0, style & ~wsChild, text, rect);
}

void cwFrame::create(cwWindow *parent, const cResource& res, int style)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   cwFrame::dock_style = style & wsDockAny;

   if ( (style & ~wsDockAny) == 0 )
      style |= wsFrameWindow;

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= FWS_ADDTOTITLE;

      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      CCreateContext cc;
      cc.m_pNewViewClass = getMainView() != 0 ?
          ccwView::__getRuntimeClass(getMainView())
        : cc.m_pNewViewClass = RUNTIME_CLASS(WCView);

      if ( isDockable() ) {
         _wnd = new WCFrameDockWnd(this);
         if ( !((WCFrameDockWnd*)_wnd)->LoadFrame(res.getID(), mfc_style[0], mfc_parent, &cc) ) {
            __ECL_ASSERT2__(0, ("Could not load SDI frame with id = %d", res.getID()));
         } else {
            modifyStyles(dock_style, 0);
         }
      } else {
         _wnd = new WCFrameWnd(this);
         if ( !((WCFrameWnd*)_wnd)->LoadFrame(res.getID(), mfc_style[0], mfc_parent, &cc) )
            __ECL_ASSERT2__(0, ("Could not load SDI frame with id = %d", res.getID()));
      }

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwFrame::create(const cResource& res, int style)
{
   create(0, res, style & ~wsChild);
}

void cwFrame::recalcLayout(bool notify)
{
   #if defined __ECL_W32__
      if ( isDockable() ) {
         ((WCFrameDockWnd*)_wnd)->RecalcLayout(notify);
      } else {
         ((WCFrameWnd*)_wnd)->RecalcLayout(notify);
      }
   #else
      // ...
   #endif
}


// Views
// =====

void cwFrame::setView(cwView *view)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   if ( __ECL_ASSERT1__(view != 0 && info == 0) ) {

      info = new FRAMEINFO;
      info->type = FRAMEINFO::MAIN;
      view->setParent(this);

      #if defined __ECL_W32__
         info->tab_cnr = 0;
         info->tab3d_cnr = 0;
      #endif

      if ( __ECL_ASSERT1__(info->views.getCount() == 0) ) {
         VIEWINFO vwi;
         vwi.view = view;
         vwi.size = -1;
         vwi.pos  = vpMain;
         vwi.name = "Main";
         #if defined __ECL_W32__
            vwi.splitter = 0;
            vwi.spp_x    = 0;
            vwi.spp_y    = 0;
         #endif
         info->views.addTail(vwi);
      }

   }
}

void cwFrame::addView(cwView *view, POSITION pos, int size)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   if ( __ECL_ASSERT1__(view != 0)
     && __ECL_ASSERT1__(size >= 0)
     && __ECL_ASSERT1__(pos != vpMain && pos != vpSame) )
   {

      view->setParent(this);

      if ( __ECL_ASSERT1__(info != 0)
        && __ECL_ASSERT1__(info->type != FRAMEINFO::TAB)
        && __ECL_ASSERT1__(info->views.getCount() > 0) )
      {
         info->type = FRAMEINFO::SPLIT;
         VIEWINFO vwi;
         vwi.view = view;
         vwi.pos  = pos;
         vwi.size = size;
         #if defined __ECL_W32__
            vwi.splitter = 0;
            vwi.spp_x    = 0;
            vwi.spp_y    = 0;
         #endif
         info->views.addTail(vwi);
      }

   }
}

void cwFrame::setTabView(cwView *view, cString name, bool is_tab3d)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   if ( __ECL_ASSERT1__(view != 0 && info == 0) ) {

      info = new FRAMEINFO;
      info->type = FRAMEINFO::TAB;
      view->setParent(this);

      if ( is_tab3d ) {
         #if defined __ECL_W32__
            info->tab_cnr = 0;
            info->tab3d_cnr = new WC3DTabViewContainer(this);
         #endif
      } else {
         view->setFlags(cwView::wflViewIsTabbed);
         #if defined __ECL_W32__
            info->tab_cnr = new WCTabViewContainer(this);
            info->tab3d_cnr = 0;
         #endif
      }

      if ( __ECL_ASSERT1__(info->views.getCount() == 0) ) {
         VIEWINFO vwi;
         vwi.view = view;
         vwi.size = -1;
         vwi.pos  = vpMain;
         vwi.name = name;
         #if defined __ECL_W32__
            vwi.splitter = 0;
            vwi.spp_x    = 0;
            vwi.spp_y    = 0;
         #endif
         info->views.addTail(vwi);
      }

   }
}

void cwFrame::addTabView(cwView *view, cString name)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   if ( __ECL_ASSERT1__(view != 0)
     && __ECL_ASSERT1__(!name.isEmpty()) )
   {

      view->setParent(this);

      if ( __ECL_ASSERT1__(info != 0)
        && __ECL_ASSERT1__(info->type == FRAMEINFO::TAB)
        && __ECL_ASSERT1__(info->views.getCount() > 0) )
      {
         VIEWINFO vwi;
         vwi.view = view;
         vwi.pos  = vpSame;
         vwi.size = 0;
         vwi.name = name;
         #if defined __ECL_W32__
            vwi.splitter = 0;
            vwi.spp_x    = 0;
            vwi.spp_y    = 0;
            if ( info->tab_cnr != 0 )
               view->setFlags(cwView::wflViewIsTabbed);
         #endif
         info->views.addTail(vwi);
      }

   }
}

int cwFrame::getViewCount() const
{
   return info != 0 ?
      info->views.getCount()
    : 0;
}

cwView * cwFrame::getView(int index) const
{
   if ( __ECL_ASSERT1__(info != 0) ) {
      IPOSITION view_pos = info->views.findIndex(index);
      if ( view_pos != 0 ) {
         VIEWINFO& vwi = info->views.getAt(view_pos);
         return vwi.view;
      }
   }

   return 0;
}

cwView * cwFrame::getMainView() const
{
   return getViewCount() > 0 ?
      getView(0)
    : 0;
}

cwView * cwFrame::getActiveView() const
{
   if ( info->type == FRAMEINFO::TAB ) {
      int index = getActiveViewIndex();
      if ( __ECL_ASSERT1__(index >= 0 && index < getViewCount()) ) {
         IPOSITION view_pos = info->views.findIndex(index);
         VIEWINFO& vwi = info->views.getAt(view_pos);
         return vwi.view;
      }
   } else {
      cwWindow *active_child = getActiveChild();
      if ( active_child != 0 && active_child->getFlags(wflIsAView) )
         return (cwView*)active_child;
   }

   return 0;
}

int cwFrame::getActiveViewIndex() const
{
   int index = -1;

   if ( __ECL_ASSERT1__(info != 0) ) {
      if ( info->type == FRAMEINFO::TAB ) {
         #if defined __ECL_W32__
            if ( info->tab_cnr != 0 ) {
               index = info->tab_cnr->GetActivePageIndex();
            } else if ( info->tab3d_cnr != 0 ) {
               index = info->tab3d_cnr->GetActivePageIndex();
            }
         #endif
      } else {
         cwWindow *active_child = getActiveChild();
         if ( active_child != 0 && active_child->getFlags(wflIsAView) ) {
            int view_count = getViewCount();
            for ( int i = 0 ; i < view_count ; i++ ) {
               IPOSITION view_pos = info->views.findIndex(i);
               VIEWINFO& vwi = info->views.getAt(view_pos);
               if ( vwi.view == active_child )
                  return i;
            }
         }
      }
   }

   return index;
}

void cwFrame::setActiveView(cwView *view)
{
   if ( view == 0 ) {

      #if defined __ECL_W32__
         ((CFrameWnd*)_wnd)->SetActiveView(0);
      #endif
      onViewChanged();

   } else if ( __ECL_ASSERT1__(info != 0) ) {

      int view_count = getViewCount();

      for ( int i = 0 ; i < view_count ; i++ ) {
         IPOSITION view_pos = info->views.findIndex(i);
         VIEWINFO& vwi = info->views.getAt(view_pos);
         if ( vwi.view == view ) {
            if ( info->type == FRAMEINFO::TAB ) {
               #if defined __ECL_W32__
                  if ( info->tab_cnr != 0 ) {
                     info->tab_cnr->SetActivePageIndex(i);
                  } else if ( info->tab3d_cnr != 0 ) {
                     info->tab3d_cnr->SetActivePageIndex(i);
                  }
               #endif
            } else {
               #if defined __ECL_W32__
                  ((CFrameWnd*)_wnd)->SetActiveView((CView*)__getWnd(view));
               #endif
            }
            onViewChanged();
            return;
         }
      }

   }
}

cString cwFrame::getViewTitle(const cwView *view) const
{
   if ( __ECL_ASSERT1__(info != 0) ) {

      int view_count = getViewCount();

      for ( int i = 0 ; i < view_count ; i++ ) {
         IPOSITION view_pos = info->views.findIndex(i);
         VIEWINFO& vwi = info->views.getAt(view_pos);
         if ( vwi.view == view ) {
            if ( info->type == FRAMEINFO::TAB ) {
               #if defined __ECL_W32__
                  if ( info->tab_cnr != 0 ) {
                     return (const char *)info->tab_cnr->GetPageTitle(i);
                  } else if ( info->tab3d_cnr != 0 ) {
                     return (const char *)info->tab3d_cnr->GetPageTitle(i);
                  }
               #endif
            } else {
               // TBD: ...
            }
         }
      }

   }

   return 0;
}

void cwFrame::setViewTitle(cwView *view, cString title)
{
   if ( __ECL_ASSERT1__(info != 0) ) {

      int view_count = getViewCount();

      for ( int i = 0 ; i < view_count ; i++ ) {
         IPOSITION view_pos = info->views.findIndex(i);
         VIEWINFO& vwi = info->views.getAt(view_pos);
         if ( vwi.view == view ) {
            if ( info->type == FRAMEINFO::TAB ) {
               #if defined __ECL_W32__
                  if ( info->tab_cnr != 0 ) {
                     info->tab_cnr->SetPageTitle(i, title);
                  } else if ( info->tab3d_cnr != 0 ) {
                     info->tab3d_cnr->SetPageTitle(i, title);
                  }
                  return;
               #endif
            } else {
               // TBD: ...
            }
         }
      }

   }
}


// Hinzugefuegte Events
// ====================

bool cwFrame::onCreateViews(void *add_info)
{
   if ( info != 0 ) {
      if ( info->type == FRAMEINFO::TAB ) {
         // Nur falls TAB-View erkannt (d.h. mindestens 2 Views)
         return createTabbedViews(info->views.getCount(), add_info);
      } else {
         // Mehrere Split-Views oder ein einzelner View
         return createSplitViews(info->views.getCount(), add_info);
      }
   }

   return false;
}

void cwFrame::onSetDockSides(int /*sides*/, int os_sides)
{
   #if defined __ECL_W32__
      ((WCFrameDockWnd*)_wnd)->EnableDocking(os_sides);
   #else
      // ...
   #endif
}

bool cwFrame::onViewChanging(cwView * /*cur_view*/)
{
   return true;
}

void cwFrame::onViewChanged(cwView *prev_view, cwView *new_view)
{
   if ( prev_view != 0 )
      ccwView::onHideView(prev_view);
   if ( new_view != 0 ) {
      ccwView::onShowView(new_view);
      if ( !new_view->getFlags(wflWasRefreshed) )
         new_view->refresh();
   }
}

bool cwFrame::onViewChanging()
{
   // Intern: Aufruf nur durch ccwFrame!!
   return onViewChanging(info != 0 ? info->current_view : 0);
}

void cwFrame::onViewChanged()
{
   // Intern: Aufruf nur durch ccwFrame!!
   cwView *prev_view = 0, *new_view = 0;
   if ( info != 0 ) {
      prev_view = info->current_view;
      int index = 0;
      if ( info->type == FRAMEINFO::TAB ) {
         #if defined __ECL_W32__
            if ( info->tab_cnr != 0 ) {
               index = info->tab_cnr->GetActivePageIndex();
            } else if ( info->tab3d_cnr != 0 ) {
               index = info->tab3d_cnr->GetCurSel();
            }
         #endif
      } else {
         index = getActiveViewIndex();
      }
      info->current_view = new_view = getView(index);
   }
   if ( prev_view != new_view )
      onViewChanged(prev_view, new_view);
}

// ---

bool cwFrame::createSplitViews(int view_count, void *add_info)
{
   for ( int i = 1 ; i < view_count ; i++ ) {
      VIEWINFO& vwi0 = info->views.getAt(info->views.findIndex(0));
      VIEWINFO& vwi  = info->views.getAt(info->views.findIndex(i));

      #if defined __ECL_W32__

         int x  = 0; // x-Position des aktuellen Views im Splitter
         int y  = 0; // y-Position des aktuellen Views im Splitter
         int x0 = 0; // x-Position des Haupt-Views im Splitter
         int y0 = 0; // y-Position des Haupt-Views im Splitter
         int dx = 0; // Anzahl Spalten im Splitter
         int dy = 0; // Anzahl Zeilen im Splitter

         switch ( vwi.pos ) {
         case vpLeft:   x = 0; y = 0; x0 = 1; y0 = 0; dx = 2; dy = 1; break;
         case vpRight:  x = 1; y = 0; x0 = 0; y0 = 0; dx = 2; dy = 1; break;
         case vpTop:    x = 0; y = 0; x0 = 0; y0 = 1; dx = 1; dy = 2; break;
         case vpBottom: x = 0; y = 1; x0 = 0; y0 = 0; dx = 1; dy = 2; break;
         }

         if ( vwi0.splitter == 0 ) {
            vwi.splitter = new CSplitterWnd;
            vwi.splitter->CreateStatic((CWnd*)_wnd, dy, dx);
         } else {
            vwi.splitter = new CSplitterWnd;
            vwi.splitter->CreateStatic(vwi0.splitter, dy, dx, WS_CHILD|WS_VISIBLE,
               vwi0.splitter->IdFromRowCol(vwi0.spp_y, vwi0.spp_x));
         }

         vwi0.splitter = vwi.splitter;
         vwi0.spp_x = x0; vwi0.spp_y = y0;

         vwi.spp_x = x; vwi.spp_y = y;

         ccwView::srv_beeing_created = vwi.view;
         vwi.splitter->CreateView(y, x,
            ccwView::__getRuntimeClass(vwi.view),
            CSize((dx-1)*vwi.size, (dy-1)*vwi.size),
            (CCreateContext*)add_info);
         ccwView::srv_beeing_created = 0;

      #else
         // ...
      #endif

   }

   if ( view_count == 1 ) {
      VIEWINFO& vwi0 = info->views.getAt(info->views.findIndex(0));

      #if defined __ECL_W32__
         ccwView::srv_beeing_created = vwi0.view;
         ((CFrameWnd*)_wnd)->CreateView((CCreateContext*)add_info);
         ccwView::srv_beeing_created = 0;
      #endif

      setActiveView(vwi0.view);

   } else if ( view_count > 1 ) {
      VIEWINFO& vwi0 = info->views.getAt(info->views.findIndex(0));

      #if defined __ECL_W32__
         ccwView::srv_beeing_created = vwi0.view;
         vwi0.splitter->CreateView(vwi0.spp_y, vwi0.spp_x,
            ccwView::__getRuntimeClass(vwi0.view),
            CSize(0, 0), (CCreateContext*)add_info);
         ccwView::srv_beeing_created = 0;
      #endif

      setActiveView(vwi0.view);

   } else {

      return false;

   }

   return true;
}

bool cwFrame::createTabbedViews(int view_count, void *add_info)
{
   #if defined __ECL_W32__

      if ( info->tab_cnr != 0 ) {

         if ( __ECL_ASSERT1__(info->tab_cnr->Create((CWnd*)_wnd)) ) {

            for ( int i = 0 ; i < view_count ; i++ ) {
               VIEWINFO& vwi  = info->views.getAt(info->views.findIndex(i));

               ccwView::srv_beeing_created = vwi.view;
	            info->tab_cnr->AddPage(
                  ccwView::__getRuntimeClass(vwi.view),
                  (CCreateContext*)add_info,
                  _T((const char *)vwi.name));
               ccwView::srv_beeing_created = 0;
            }

            VIEWINFO& vwi0 = info->views.getAt(info->views.findIndex(0));
            setActiveView(vwi0.view);

         } else {

            return false;

         }

      } else if ( info->tab3d_cnr != 0 ) {

         if ( __ECL_ASSERT1__(info->tab3d_cnr->Create((CWnd*)_wnd)) ) {
            info->tab3d_cnr->ModifyStyleEx(WS_EX_CLIENTEDGE,0);

            info->tab3d_cnr->SetOffsetInternal(/*TBD:*/1);
            info->tab3d_cnr->SetOffsetExternal(/*TBD:*/1);

            for ( int i = 0 ; i < view_count ; i++ ) {
               VIEWINFO& vwi  = info->views.getAt(info->views.findIndex(i));

               ccwView::srv_beeing_created = vwi.view;
	            info->tab3d_cnr->AddPage(
                  ccwView::__getRuntimeClass(vwi.view),
                  (CCreateContext*)add_info,
                  _T((const char *)vwi.name), -1, 0);
               ccwView::srv_beeing_created = 0;
            }

            VIEWINFO& vwi0 = info->views.getAt(info->views.findIndex(0));
            setActiveView(vwi0.view);

         } else {

            return false;

         }


      }

   #endif

   return true;
}


// Ueberschriebene Events
// ======================

bool cwFrame::onCreate()
{
   return true;
}

bool cwFrame::onPreCreate(void *add_data)
{
   #if defined __ECL_W32__
      CREATESTRUCT *cs = (CREATESTRUCT*)add_data;
      cs->style |= WS_VISIBLE;
      cs->dwExStyle &= ~WS_EX_CLIENTEDGE;

      #define __Flicker_Free_Redrawing__
      #ifdef __Flicker_Free_Redrawing__
         if ( cs->lpszClass == NULL || *cs->lpszClass == '\0' ) {
            cs->lpszClass = AfxRegisterWndClass(
               0,          // no redraw
               NULL,       // no cursor (use default)
               NULL,       // no background brush
               NULL);      // no app icon (use default)
         }
      #endif

   #else
   #endif

   return true;
}

bool cwFrame::onCommand(const cwCmdEvt& cmd)
{
   #ifdef __Route_Command_To_Active_View__
      // Kommando weiterleiten an aktiven View
      cwView *view = getActiveView();
      if ( view != 0 && ccwWindow::onCommand(view, cmd) )
         return true;
   #else
      // Kommando weiterleiten an aktives Kindfenster
      cwWindow *child = getActiveChild();
      if ( child != 0 && ccwWindow::onCommand(child, cmd) )
         return true;
   #endif

   // Wenn nicht bearbeitet, weiterleiten an Applikation
   return ccwApplication::__onFrameCommand(cwApplication::getTheApp(), this, cmd);
}

bool cwFrame::onCommandUI(cwCmdUI& cmd)
{
   // UI-Aktualisierung weiterleiten an aktives Kindfenster
   cwWindow *child = getActiveChild();
   if ( child != 0 )
      return ccwWindow::onCommandUI(child, cmd);

   return false;
}

void cwFrame::onChildActivated(cwWindow *win)
{
   cwWindow::onChildActivated(win);
   if ( win->getFlags(wflIsAView) ) {
      setActiveView((cwView*)win);
   } else {
      setActiveView(0);
   }
}

int cwFrame::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCWnd*)_wnd)->GetStyle();

      if ( (mask & wsCaption) && (style & WS_CAPTION) )
         rc |= wsCaption;
      if ( (mask & wsSysMenu) && (style & WS_SYSMENU) )
         rc |= wsSysMenu;
      if ( (mask & wsMinimize) && (style & WS_MINIMIZEBOX) )
         rc |= wsMinimize;
      if ( (mask & wsMaximize) && (style & WS_MAXIMIZEBOX) )
         rc |= wsMaximize;

      if ( (mask & wsDockLeft) && (dock_style & wsDockLeft) )
         rc |= wsDockLeft;
      if ( (mask & wsDockRight) && (dock_style & wsDockRight) )
         rc |= wsDockRight;
      if ( (mask & wsDockTop) && (dock_style & wsDockTop) )
         rc |= wsDockTop;
      if ( (mask & wsDockBottom) && (dock_style & wsDockBottom) )
         rc |= wsDockBottom;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwWindow::onGetStyles(mask);
}

void cwFrame::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      cwWindow::onMakeStyles(styles, os_styles);

      if ( styles & wsCaption )
         os_styles[0] |= WS_CAPTION;
      if ( styles & wsSysMenu )
         os_styles[0] |= WS_SYSMENU;
      if ( styles & wsMinimize )
         os_styles[0] |= WS_MINIMIZEBOX;
      if ( styles & wsMaximize )
         os_styles[0] |= WS_MAXIMIZEBOX;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwFrame::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsCaption )
         os_add[0] |= WS_CAPTION;
      if ( add & wsSysMenu )
         os_add[0] |= WS_SYSMENU;
      if ( add & wsMinimize )
         os_add[0] |= WS_MINIMIZEBOX;
      if ( add & wsMaximize )
         os_add[0] |= WS_MAXIMIZEBOX;

      if ( remove & wsCaption )
         os_remove[0] |= WS_CAPTION;
      if ( remove & wsSysMenu )
         os_remove[0] |= WS_SYSMENU;
      if ( remove & wsMinimize )
         os_remove[0] |= WS_MINIMIZEBOX;
      if ( remove & wsMaximize )
         os_remove[0] |= WS_MAXIMIZEBOX;

      if ( (add & wsDockAny) != 0 || (remove & wsDockAny) != 0 ) {

         dock_style |= (add & wsDockAny);
         dock_style &= ~(remove & wsDockAny);

         int mfc_dock = 0;
         if ( dock_style & wsDockLeft   ) mfc_dock |= CBRS_ALIGN_LEFT;
         if ( dock_style & wsDockRight  ) mfc_dock |= CBRS_ALIGN_RIGHT;
         if ( dock_style & wsDockTop    ) mfc_dock |= CBRS_ALIGN_TOP;
         if ( dock_style & wsDockBottom ) mfc_dock |= CBRS_ALIGN_BOTTOM;

         onSetDockSides(dock_style, mfc_dock);

      }

      cwWindow::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// cwMultiDocFrame
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwFrame
//          +--cwMultiDocFrame
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwMultiDocFrame : public cwFrame {
   ELO_DECLARE(cwMultiDocFrame,cwFrame)
   friend class ccwFrame;

public:

   // Konstruktor
   inline cwMultiDocFrame() : cwFrame(0) { init(); }
   // Destruktor
   virtual ~cwMultiDocFrame();


   // Allgemeines
   // ===========

   // Erzeugen eines Multiple-Document-Frame-Windows
   void create(int style, cString text, const cdRect& rect = cdRect());
   // Erzeugen eines Multiple-Document-Frame-Windows aus einer Resource
   void create(const cResource& res, int style);


   // Kindfenster
   // ===========

   enum TILE {
      tileHorz,      // Horizontale Anordnung
      tileVert       // Vertikale Anordnung
   };

   // Icon-Darstellung anordnen
   void arrange();
   // Kindfenster ueberlappend anordnen
   void cascade();
   // Kindfenster nebeneinander anordnen
   void tile(TILE tile);


protected:

   // Ueberschriebene Events
   // ======================

   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Wird aufgerufen, um die Andockseiten zu setzen
   void onSetDockSides(int sides, int os_sides);

protected:

   // Interner Konstruktor
   cwMultiDocFrame(void *wnd);


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwMultiDocFrame
// ===========================================================================

cwMultiDocFrame::cwMultiDocFrame(void *wnd)
   : cwFrame(wnd)
{
   init();
}

cwMultiDocFrame::~cwMultiDocFrame()
{
}

void cwMultiDocFrame::init()
{
}


// Allgemeines
// ===========

void cwMultiDocFrame::create(int style, cString text, const cdRect& rect)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   cwFrame::dock_style = style & wsDockAny;

   if ( (style & ~wsDockAny) == 0 )
      style |= wsFrameWindow;

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      if ( text.isEmpty() ) mfc_style[0] |= FWS_ADDTOTITLE;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( isDockable() ) {
         _wnd = new WCMDIFrameDockWnd(this);
         if ( !((WCMDIFrameDockWnd*)_wnd)->Create(NULL, _T(text), mfc_style[0], mfc_rect) ) {
            __ECL_ASSERT2__(0, ("Could not create frame window"));
         } else {
            modifyStyles(dock_style, 0);
         }
      } else {
         _wnd = new WCMDIFrameWnd(this);
         if ( !((WCMDIFrameWnd*)_wnd)->Create(NULL, _T(text), mfc_style[0], mfc_rect) )
            __ECL_ASSERT2__(0, ("Could not create frame window"));
      }

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwMultiDocFrame::create(const cResource& res, int style)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   cwFrame::dock_style = style & wsDockAny;

   #if defined __ECL_W32__

      if ( isDockable() ) {
         _wnd = new WCMDIFrameDockWnd(this);
         if ( !((WCMDIFrameDockWnd*)_wnd)->LoadFrame(res.getID()) ) {
            __ECL_ASSERT2__(0, ("Could not load MDI frame window"));
         } else {
            modifyStyles(dock_style, 0);
         }
      } else {
         _wnd = new WCMDIFrameWnd(this);
         if ( !((WCMDIFrameWnd*)_wnd)->LoadFrame(res.getID()) )
            __ECL_ASSERT2__(0, ("Could not load MDI frame window"));
      }

   #else
      // ...
   #endif

   __attachDelayed();
}


// Kindfenster
// ===========

void cwMultiDocFrame::arrange()
{
   #if defined __ECL_W32__
      if ( isDockable() ) {
         ((WCMDIFrameDockWnd*)_wnd)->MDIIconArrange();
      } else {
         ((WCMDIFrameWnd*)_wnd)->MDIIconArrange();
      }
   #else
      // ...
   #endif
}

void cwMultiDocFrame::cascade()
{
   #if defined __ECL_W32__
      if ( isDockable() ) {
         ((WCMDIFrameDockWnd*)_wnd)->MDICascade(MDITILE_SKIPDISABLED);
      } else {
         ((WCMDIFrameWnd*)_wnd)->MDICascade(MDITILE_SKIPDISABLED);
      }
   #else
      // ...
   #endif
}

void cwMultiDocFrame::tile(TILE tile)
{
   #if defined __ECL_W32__

      int opt = MDITILE_SKIPDISABLED;

      switch ( tile ) {
      case tileVert: opt |= MDITILE_VERTICAL; break;
      case tileHorz: opt |= MDITILE_HORIZONTAL; break;
      }

      if ( isDockable() ) {
         ((WCMDIFrameDockWnd*)_wnd)->MDICascade(opt);
      } else {
         ((WCMDIFrameWnd*)_wnd)->MDICascade(opt);
      }

   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

bool cwMultiDocFrame::onCommand(const cwCmdEvt& cmd)
{
   switch ( cmd.getId() ) {
   case cwCmdEvt::cmdWindowArrange:    arrange(); return true;
   case cwCmdEvt::cmdWindowCascade:    cascade(); return true;
   case cwCmdEvt::cmdWindowTileHorz:   tile(tileHorz); return true;
   case cwCmdEvt::cmdWindowTileVert:   tile(tileVert); return true;
   }

   return cwFrame::onCommand(cmd);
}

void cwMultiDocFrame::onSetDockSides(int /*sides*/, int os_sides)
{
   #if defined __ECL_W32__
      ((WCMDIFrameDockWnd*)_wnd)->EnableDocking(os_sides);
   #else
      // ...
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// cwMultiDocChild
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwFrame
//          +--cwMultiDocChild
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwMultiDocChild : public cwFrame {
   ELO_DECLARE(cwMultiDocChild,cwFrame)
   friend class ccwFrame;

public:

   // Konstruktor
   inline cwMultiDocChild() : cwFrame(0) { init(); }
   // Destruktor
   virtual ~cwMultiDocChild();


   // Allgemeines
   // ===========

   // Erzeugen eines Multiple-Document-Child-Windows
   void create(cwMultiDocFrame *parent, int style, cString text, const cdRect& rect = cdRect());
   // Erzeugen eines Multiple-Document-Child-Windows aus einer Resource
   void create(cwMultiDocFrame *parent, const cResource& res, int style);

   // Ist das zugehoerige Frame ein dockbares Frame-Fenster?
   inline bool isParentDockable() const
      { return parent != 0 ? parent->isDockable() : false; }


protected:

   // Ueberschriebene Events
   // ======================

   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);


protected:

   // Interner Konstruktor
   cwMultiDocChild(void *wnd);


private:

   // Zugehoeriges Multiple Document Frame Window
   cwMultiDocFrame *parent;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwMultiDocChild
// ===========================================================================

cwMultiDocChild::cwMultiDocChild(void *wnd)
   : cwFrame(wnd)
{
   init();
}

cwMultiDocChild::~cwMultiDocChild()
{
}

void cwMultiDocChild::init()
{
   parent = 0;
}


// Allgemeines
// ===========

void cwMultiDocChild::create(cwMultiDocFrame *parent, int style, cString text, const cdRect& rect)
{
   if ( _wnd != 0 || parent == 0 )
      throw cErrBase(cErrBase::errInit);

   cwFrame::dock_style = style & wsDockAny;
   cwMultiDocChild::parent = parent;

   if ( (dock_style & wsDockAny) != 0 && !isParentDockable() )
      throw cErrBase(cErrBase::errInvParam);

   if ( (style & ~wsDockAny) == 0 )
      style |= wsFrameWindow | wsChild | wsVisible;

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      if ( text.isEmpty() ) mfc_style[0] |= FWS_ADDTOTITLE;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      CCreateContext cc;
      cc.m_pNewViewClass = getMainView() != 0 ?
          ccwView::__getRuntimeClass(getMainView())
        : cc.m_pNewViewClass = RUNTIME_CLASS(WCView);

      if ( isDockable() ) {
         _wnd = new WCMDIChildDockWnd(this);
         CMDIFrameDockWnd *parent_wnd = (CMDIFrameDockWnd*)__getWnd(parent);
         if ( !((WCMDIChildDockWnd*)_wnd)->Create(NULL, _T(text), mfc_style[0], mfc_rect, parent_wnd, &cc) )
            __ECL_ASSERT2__(0, ("Could not load MDI child window"));
      } else {
         _wnd = new WCMDIChildWnd(this);
         CMDIFrameWnd *parent_wnd = (CMDIFrameWnd*)__getWnd(parent);
         if ( !((WCMDIChildWnd*)_wnd)->Create(NULL, _T(text), mfc_style[0], mfc_rect, parent_wnd, &cc) )
            __ECL_ASSERT2__(0, ("Could not load MDI child window"));
      }

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwMultiDocChild::create(cwMultiDocFrame *parent, const cResource& res, int style)
{
   if ( _wnd != 0 || parent == 0 )
      throw cErrBase(cErrBase::errInit);

   cwFrame::dock_style = style & wsDockAny;
   cwMultiDocChild::parent = parent;

   if ( (style & ~wsDockAny) == 0 )
      style |= wsFrameWindow | wsChild | wsVisible;

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= FWS_ADDTOTITLE;

      if ( isParentDockable() ) {
         _wnd = new WCMDIChildDockWnd(this);
         CMDIFrameDockWnd *parent_wnd = (CMDIFrameDockWnd*)__getWnd(parent);
         if ( !((WCMDIChildDockWnd*)_wnd)->LoadFrame(res.getID(), mfc_style[0], parent_wnd) )
            __ECL_ASSERT2__(0, ("Could not load MDI child with id = %d", res.getID()));
      } else {
         _wnd = new WCMDIChildWnd(this);
         CMDIFrameWnd *parent_wnd = (CMDIFrameWnd*)__getWnd(parent);
         if ( !((WCMDIChildWnd*)_wnd)->LoadFrame(res.getID(), mfc_style[0], parent_wnd) )
            __ECL_ASSERT2__(0, ("Could not load MDI child with id = %d", res.getID()));
      }

   #else
      // ...
   #endif

   __attachDelayed();
}


// Ueberschriebene Events
// ======================

bool cwMultiDocChild::onCommand(const cwCmdEvt& cmd)
{
   return cwFrame::onCommand(cmd);
}




#ifdef __INTERFACE__

// ===========================================================================
// cwDockable
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Fenster, die an ein Frame-Window "andockbar" sind.
//
// cBase
//  +--cwWindow
//      +--cwDockable
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDockable : public cwWindow {
   ELO_DECLARE(cwDockable,cwWindow)

public:

   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwWindow::wsUser,
      wsUser            = wsStart << 0,   // Benutzerdefinierte Styles
      //
      // Alte Namen (Kompatibilitaet):
      dksAlignNone      = wsDockNone,
      dksAlignLeft      = wsDockLeft,
      dksAlignRight     = wsDockRight,
      dksAlignTop       = wsDockTop,
      dksAlignBottom    = wsDockBottom,
      dksAlignMask      = wsDockAny,
      //
      dsNone            = wsDockNone,
      dsLeft            = wsDockLeft,
      dsRight           = wsDockRight,
      dsTop             = wsDockTop,
      dsBottom          = wsDockBottom,
      dsAny             = wsDockAny
   };


   // Seiten
   // ======

   // Andockseiten setzen
   void setDockSides(int sides);
   // Aktuelle Andockseiten ermitteln
   int getDockSides() const;


   // Zustand
   // =======

   // Hinweis: Der 'ratio'-Parameter von dockWindow() gibt an, wo und in
   // welchem Verhaeltnis zum Gesamtbereich der angegebenen Seite das Fenster
   // angedockt wird. Beispiele:
   //
   //  - (dpLeft,60) = Links unten, Hoehe = 60% der Gesamthoehe
   //  - (dpLeft,-30) = Links oben, Hoehe = 30% der Gesamthoehe
   //  - (dpTop,-70) = Oben links, Breite = 70% der Gesamtbreite

   enum DOCK_POSITION {          // Andockpositionen im Frame-Window:
      dpLeft,                    //  - Links andocken
      dpRight,                   //  - Rechts andocken
      dpTop,                     //  - Oben andocken
      dpBottom                   //  - Unten andocken
   };

   // Window an gespeicherter Position am Parent andocken
   void dockWindow();
   // Window an Seite 'pos' von Parent andocken
   void dockWindow(DOCK_POSITION pos, int ratio = 0);
   // Window in "Schwebezustand" an gespeicherte Position
   void floatWindow();
   // Window in "Schwebezustand" an Position 'pos'
   void floatWindow(const cdPoint& pos);

   // Ist das Fenster gerade angedockt?
   bool isDocked() const;
   // Ist das Fenster gerade schwebend?
   bool isFloating() const;


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, um die Andockseiten zu setzen
   virtual void onSetDockSides(int sides, int os_sides) = 0;


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um die OS-spezifischen Styles aus den ECL-Styles zu ermitteln
   void onMakeStyles(int styles, int os_styles[]) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Parent-Window
   cwFrame *_parent;

   // Interner Konstruktor
   cwDockable(void *wnd);
   // Destruktor
   virtual ~cwDockable();


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwDockable
// ===========================================================================

cwDockable::cwDockable(void *wnd)
   : cwWindow(wnd)
{
   init();
}

cwDockable::~cwDockable()
{
}

void cwDockable::init()
{
   _parent = 0;
}


// Seiten
// ======

void cwDockable::setDockSides(int sides)
{
   modifyStyles(sides & wsDockAny, (~sides) & wsDockAny);
}

int cwDockable::getDockSides() const
{
   return getStyles(wsDockAny);
}


// Zustand
// =======

void cwDockable::dockWindow()
{
   if ( __ECL_ASSERT1__(_wnd != 0 && _parent != 0) ) {
      #if defined __ECL_W32__
         //__ECL_ASSERT2__(0, ("dockWindow() not yet implemented"));
         CRect rect;
         CFrameWnd *parent_wnd = (CFrameWnd*)__getWnd(_parent);
         WCControlBar *ctrl_bar = (WCControlBar*)_wnd;
         CControlBarInfo info; ctrl_bar->GetBarInfo(&info);
         CDockBar *dock_bar = (CDockBar*)parent_wnd->GetControlBar(info.m_uMRUDockID);
         rect = info.m_rectMRUDockPos;
	      dock_bar->ClientToScreen(rect);
         parent_wnd->DockControlBar(ctrl_bar, info.m_uMRUDockID, rect);
         parent_wnd->RecalcLayout();
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

void cwDockable::dockWindow(DOCK_POSITION pos, int ratio)
{
   if ( __ECL_ASSERT1__(_wnd != 0 && _parent != 0) ) {

      #if defined __ECL_W32__
         int mfc_pos = 0;
         if ( !__ECL_ASSERT1__(ratio >= 0) ) ratio = -ratio;
         if ( !__ECL_ASSERT1__(ratio < 100) ) ratio = 80;
         switch ( pos ) {
         case dpLeft:   mfc_pos = AFX_IDW_DOCKBAR_LEFT; break;
         case dpRight:  mfc_pos = AFX_IDW_DOCKBAR_RIGHT; break;
         case dpTop:    mfc_pos = AFX_IDW_DOCKBAR_TOP; break;
         case dpBottom: mfc_pos = AFX_IDW_DOCKBAR_BOTTOM; break;
         }
         CFrameWnd *parent_wnd = (CFrameWnd*)__getWnd(_parent);
         WCControlBar *ctrl_bar = (WCControlBar*)_wnd;
         if ( ratio != 0 ) {
            // Position berechnen
            // TBD: Verbessern! Das funktioniert ja wohl noch nicht so richtig...
	         CRect rect;
      	   CDockBar *dock_bar = (CDockBar*)parent_wnd->GetControlBar(mfc_pos);
	         dock_bar->GetClientRect(rect);
	         dock_bar->ClientToScreen(rect);
            if ( pos == dpLeft || pos == dpRight ) {
               int dy = rect.Height()*(100-ratio)/100;
               rect.top += dy; // Falsch? rect.bottom -= dy;
            } else {
               int dx = rect.Width()*(100-ratio)/100;
               rect.left += dx; // Falsch? rect.right -= dx;
            }
            parent_wnd->DockControlBar(ctrl_bar, mfc_pos, rect);
         } else {
            parent_wnd->DockControlBar(ctrl_bar, mfc_pos);
         }
         parent_wnd->RecalcLayout();
      #elif defined __ECL_OS2__
         // ...
      #endif

   }
}

void cwDockable::floatWindow()
{
   if ( __ECL_ASSERT1__(_wnd != 0 && _parent != 0) ) {
      #if defined __ECL_W32__
         CPoint mfc_point = ((WCControlBar*)_wnd)->m_FloatingPosition;
         CFrameWnd *parent_wnd = (CFrameWnd*)__getWnd(_parent);
         parent_wnd->FloatControlBar((CControlBar*)_wnd, mfc_point);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

void cwDockable::floatWindow(const cdPoint& pos)
{
   if ( __ECL_ASSERT1__(_wnd != 0 && _parent != 0) ) {
      #if defined __ECL_W32__
         CPoint mfc_point(pos.x, pos.y);
         CFrameWnd *parent_wnd = (CFrameWnd*)__getWnd(_parent);
         parent_wnd->FloatControlBar((CControlBar*)_wnd, mfc_point);
      #elif defined __ECL_OS2__
         // ...
      #endif
   }
}

bool cwDockable::isDocked() const
{
   #if defined __ECL_W32__
      return __ECL_ASSERT1__(_wnd != 0) ?
         !((CControlBar*)_wnd)->IsFloating()
       : false;
   #elif defined __ECL_OS2__
      // ...
   #endif
}

bool cwDockable::isFloating() const
{
   #if defined __ECL_W32__
      return __ECL_ASSERT1__(_wnd != 0) ?
         !!((CControlBar*)_wnd)->IsFloating()
       : false;
   #elif defined __ECL_OS2__
      // ...
   #endif
}

int cwDockable::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD mfc_dockstyle = ((CControlBar*)_wnd)->m_dwDockStyle;

      if ( (mask & wsDockLeft) && (mfc_dockstyle & CBRS_ALIGN_LEFT) )
         rc |= wsDockLeft;
      if ( (mask & wsDockRight) && (mfc_dockstyle & CBRS_ALIGN_RIGHT) )
         rc |= wsDockRight;
      if ( (mask & wsDockTop) && (mfc_dockstyle & CBRS_ALIGN_TOP) )
         rc |= wsDockTop;
      if ( (mask & wsDockBottom) && (mfc_dockstyle & CBRS_ALIGN_BOTTOM) )
         rc |= wsDockBottom;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwWindow::onGetStyles(mask);
}

void cwDockable::onMakeStyles(int styles, int os_styles[]) const
{
   #if defined __ECL_W32__

      cwWindow::onMakeStyles(styles, os_styles);

      if ( styles & wsDockLeft )
         os_styles[0] |= /*CBRS_ALIGN_LEFT |*/ CBRS_BORDER_RIGHT;
      if ( styles & wsDockRight )
         os_styles[0] |= /*CBRS_ALIGN_RIGHT |*/ CBRS_BORDER_LEFT;
      if ( styles & wsDockTop )
         os_styles[0] |= /*CBRS_ALIGN_TOP |*/ CBRS_BORDER_BOTTOM;
      if ( styles & wsDockBottom )
         os_styles[0] |= /*CBRS_ALIGN_BOTTOM |*/ CBRS_BORDER_TOP;

   #elif defined __ECL_OS2__

      // ...

   #endif
}

void cwDockable::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( (add & wsDockAny) != 0 || (remove & wsDockAny) != 0 ) {

         int dock_style = getStyles(wsDockAny);
         dock_style |= (add & wsDockAny);
         dock_style &= ~(remove & wsDockAny);

         int mfc_dock = 0;
         if ( dock_style & wsDockLeft   ) mfc_dock |= CBRS_ALIGN_LEFT;
         if ( dock_style & wsDockRight  ) mfc_dock |= CBRS_ALIGN_RIGHT;
         if ( dock_style & wsDockTop    ) mfc_dock |= CBRS_ALIGN_TOP;
         if ( dock_style & wsDockBottom ) mfc_dock |= CBRS_ALIGN_BOTTOM;

         onSetDockSides(dock_style, mfc_dock);

      }

      cwWindow::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// cwMiniFrame
// ---------------------------------------------------------------------------
//
// Diese Fensterklasse nimmt ein beliebiges Client-Fenster auf (z.B. ein
// Control) und "verpackt" es in ein schwebendes (oder alternativ andockbares)
// Mini-Frame-Fenster.
//
// cBase
//  +--cwWindow
//      +--cwDockable
//          +--cwMiniFrame
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwMiniFrame : public cwDockable {
   ELO_DECLARE(cwMiniFrame,cwDockable)
   friend class ccwMiniFrame;

public:

   // Konstruktor
   inline cwMiniFrame() : cwDockable(0) { init(); }
   // Destruktor
   virtual ~cwMiniFrame();


   // Allgemeines
   // ===========

   // Erzeugen eines Floating-Windows (Variante 1)
   void create(cwFrame *parent, int style, cString text, const cdRect& rect = cdRect());
   // Erzeugen eines Floating-Windows aus einer Resource (Variante 2)
   void create(cwFrame *parent, const cResource& res, int style);

   // Client-Fenster setzen (nur bei Variante 1 erlaubt!)
   void setClient(cwWindow *win);
   // Client-Fenster erfragen (bei Variante 2 immer 0)
   inline cwWindow *getClient() const
      { return client; }


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, wenn sich die Groesse des Mini-Frames aendert
   virtual void onSizeOrStateChange(bool floating);


   // Ueberschriebene Events
   // ======================

   // Fenster wird erzeugt
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onCreate();
   // Fenstererzeugung wird vorbereitet
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onPreCreate(void *add_data);
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   bool onCommandUI(cwCmdUI& cmd);
   // Wird aufgerufen, um den Zeiger auf die ELO-Aktionsbeschreibung zu ermitteln
   cEloActionDescription *onGetWindowActionDescription(const cEloSelection *selection) const;

   // Wird aufgerufen, um die Andockseiten zu setzen
   void onSetDockSides(int sides, int os_sides);


protected:

   // Interner Konstruktor
   cwMiniFrame(void *wnd);


private:

   // Client-Fenster (fuer Variante mit einem Client);
   // fuer die Variante mit einem Dialog ist 'client' = 0
   cwWindow *client;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwMiniFrame
// ===========================================================================

cwMiniFrame::cwMiniFrame(void *wnd)
   : cwDockable(wnd)
{
   init();
}

cwMiniFrame::~cwMiniFrame()
{
}

void cwMiniFrame::init()
{
   client = 0;
}


// Allgemeines
// ===========

void cwMiniFrame::create(cwFrame *parent, int style, cString text, const cdRect& rect)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   cwDockable::_parent = parent;
   cwWindow::create(parent);

   if ( (style & ~wsDockAny) == 0 )
      style |= wsChild | wsVisible;

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= WS_CLIPCHILDREN;

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      CWnd *parent_wnd = (CWnd*)__getWnd(parent);

      _wnd = new WCControlBar(this);
      if ( !((WCControlBar*)_wnd)->Create(parent_wnd, _T(text), 1, mfc_style[0], mfc_rect) )
         __ECL_ASSERT2__(0, ("Could not create control bar window"));

      int mfc_dockstyle = 0;
      if ( style & wsDockLeft )
         mfc_dockstyle |= CBRS_ALIGN_LEFT;
      if ( style & wsDockRight )
         mfc_dockstyle |= CBRS_ALIGN_RIGHT;
      if ( style & wsDockTop )
         mfc_dockstyle |= CBRS_ALIGN_TOP;
      if ( style & wsDockBottom )
         mfc_dockstyle |= CBRS_ALIGN_BOTTOM;

      ((WCControlBar*)_wnd)->EnableDocking(mfc_dockstyle);
      ((WCControlBar*)_wnd)->SetSizeDockStyle(0);
      ((WCControlBar*)_wnd)->RecalcLayout();
      setDockSides(getDockSides());

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwMiniFrame::create(cwFrame *parent, const cResource& res, int style)
{
   if ( _wnd != 0 )
      throw cErrBase(cErrBase::errInit);

   cwDockable::_parent = parent;
   cwWindow::create(parent);

   #if defined __ECL_W32__

      int mfc_style[2]; onMakeStyles(style, mfc_style);
      mfc_style[0] |= CBRS_SIZE_FIXED;

      CWnd *parent_wnd = (CWnd*)__getWnd(parent);

      _wnd = new WCDialogBar2(this);
      if ( !((WCDialogBar2*)_wnd)->Create(parent_wnd, res.getID(), mfc_style[0], 2) )
         __ECL_ASSERT2__(0, ("Could not create dialog bar window"));

      //((WCDialogBar2*)_wnd)->SetSizeDockStyle(0);
      setDockSides(getDockSides());

   #else
      // ...
   #endif

   __attachDelayed();
}

void cwMiniFrame::setClient(cwWindow *win)
{
   client = win;

   if ( client != 0 && _wnd != 0 ) {

      #if defined __ECL_W32__
         CWnd *client_wnd = (CWnd*)__getWnd(client);
         if ( client_wnd != 0 ) {
            client_wnd->ModifyStyle(WS_POPUP, WS_CHILD);
            client_wnd->SetParent((CWnd*)_wnd);
         }
      #else
         // ...
      #endif

      cdRect pos = getClientPos();
      client->setPos(pos);
   }
}


// Zusaetzliche Events
// ===================

void cwMiniFrame::onSizeOrStateChange(bool /*floating*/)
{
   if ( client != 0 ) {
      cdRect pos = getClientPos();
      client->setPos(pos);
   }
}


// Ueberschriebene Events
// ======================

bool cwMiniFrame::onCreate()
{
   if ( client != 0 && _wnd != 0 ) {

      #if defined __ECL_W32__
         CWnd *client_wnd = (CWnd*)__getWnd(client);
         if ( client_wnd != 0 ) {
            client_wnd->ModifyStyle(WS_POPUP, WS_CHILD);
            client_wnd->SetParent((CWnd*)_wnd);
         }
      #else
         // ...
      #endif

      cdRect pos = getClientPos();
      client->setPos(pos);
   }

   return true;
}

bool cwMiniFrame::onPreCreate(void * /*add_data*/)
{
   #if defined __ECL_W32__
      //CREATESTRUCT *cs = (CREATESTRUCT*)add_data;
   #else
      // ...
   #endif

   return true;
}

bool cwMiniFrame::onCommand(const cwCmdEvt& cmd)
{
   // Kommando weiterleiten an aktives Kindfenster...

   cwWindow *child = getActiveChild();
   if ( child == 0 )
      child = client;
   if ( child != 0 && ccwWindow::onCommand(child, cmd) )
      return true;

   // ... oder an den aktiven View des zugeordneten Frame-Fensters,
   // falls sonst keiner etwas mit dem Kommando anfangen will...

   cwWindow *view = _parent != 0 ? _parent->getActiveView() : 0;
   if ( view != 0 && ccwWindow::onCommand(view, cmd) )
      return true;

   return cwDockable::onCommand(cmd);
}

bool cwMiniFrame::onCommandUI(cwCmdUI& cmd)
{
   // UI-Aktualisierung weiterleiten an aktives Kindfenster...

   cwWindow *child = getActiveChild();
   if ( child == 0 )
      child = client;
   if ( child != 0 && ccwWindow::onCommandUI(child, cmd) )
      return true;

   // ... und an den aktiven View des zugeordneten Frame-Fensters,
   // falls sonst keiner etwas mit dem Kommando anfangen will...

   cwWindow *view = _parent != 0 ? _parent->getActiveView() : 0;
   if ( view != 0 && ccwWindow::onCommandUI(view, cmd) )
      return true;

   return false;
}

cEloActionDescription * cwMiniFrame::onGetWindowActionDescription(const cEloSelection *sel) const
{
   // UI-Aktualisierung weiterleiten an aktives Kindfenster
   cwWindow *child = getActiveChild();
   if ( child == 0 )
      child = client;
   if ( child != 0 )
      return child->getWindowActionDescription(sel);

   return cwDockable::onGetWindowActionDescription(sel);
}

void cwMiniFrame::onSetDockSides(int /*sides*/, int os_sides)
{
   #if defined __ECL_W32__
      if ( client != 0 ) {
         ((WCControlBar*)_wnd)->EnableDocking(os_sides);
      } else {
         ((WCDialogBar2*)_wnd)->EnableDocking(os_sides);
      }
   #else
      // ...
   #endif
}


