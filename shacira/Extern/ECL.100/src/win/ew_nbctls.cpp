// ===========================================================================
// ew_nbctls.cpp                                                ______ /  ECL
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
//           +-cwNotebookCtl
//
// ===========================================================================

#include "win/ew_nbctls.hpp"
#include "base/eb_array.hpp"

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
// Definition cwNotebookCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwNotebookCtl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwNotebookCtl : public cwControl {
   ELO_DECLARE(cwNotebookCtl,cwControl)
   friend class ccwNotebookCtl;

public:

   // Konstruktor
   inline cwNotebookCtl() : cwControl(0) { init(); }
   // Destruktor
   virtual ~cwNotebookCtl();


   // window-Flags
   // ============

   enum FLAGS { wflStart = cwControl::wflUser,
      wflAutoDeletePages   = wflStart << 0,  // Eingefuegte Seiten loeschen
      wflUser              = wflStart << 1   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwControl::wsUser,
      wsSingleLine      = wsStart << 0,   // Tabs einzeilig, evtl. mit Scroller
      wsMultiLine       = wsStart << 1,   // Tabs bei Bedarf mehrzeilig
      wsUser            = wsStart << 2    // Benutzerdefinierte Styles
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwControl::evtUser,
      evtPageAdded,           // (EVFUNC_PI) Seite wurde eingefuegt
      evtPageRemoved,         // (EVFUNC_PI) Seite wird entfernt
      evtPageChanging,        // (EVFUNC_I)  Seite wird gewechselt
      evtPageChanged,         // (EVFUNC_II) Seite wurde gewechselt
      evtUser                 // Ab hier benutzerdefinierte Events
   };


   // Allgemeines
   // ===========

   // Erzeugen des Controls
   void create(cwWindow *parent, int id, int style = 0, const cdRect& rect = cdRect());
   // Liste zugeordneter Icons initialisieren
   void setIconList(const cwIconList& ilist);

   // Seite einfuegen, Titel-Text ueber Resource (liefert Index zurueck)
   int addPage(cwWindow *page, cResource title, int bmp_idx = 0, int before_idx = -1);
   // Seite einfuegen, Titel-Text als cString (liefert Index zurueck)
   int addPage(cwWindow *page, cString title, int bmp_idx = 0, int before_idx = -1);
   // Seite entfernen (ueber Seiten-Index)
   void removePage(int page_idx);
   // Seite anzeigen
   void gotoPage(int page_idx);

   // Index der aktuellen Seite ermitteln
   int getCurrentPage() const;
   // Liefert den Index der Notebook-Seite 'page' (oder 0)
   int findPage(cwWindow *page) const;
   // Liefert das zur Seite 'page_idx' gehoerende Fenster
   cwWindow *getPage(int page_idx) const;
   // Liefert die Anzahl eingefuegter Seiten
   int getPageCount() const;


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, nachdem eine Seite eingefuegt wurde
   virtual void onPageAdded(int page_idx, cwWindow *page);
   // Wird aufgerufen, befor eine Seite entfernt wird
   virtual void onPageRemoved(int page_idx, cwWindow *page);

   // Wird aufgerufen, um den Wechsel der aktuellen Seite anzukuendigen (true = prevent)
   virtual bool onPageChanging(int cur_page_idx);
   // Wird aufgerufen, um den Wechsel der aktuellen Seite bekanntzugeben
   virtual void onPageChanged(int prev_page_idx, int new_page_idx);


   // Ueberschriebene Events
   // ======================

   // Groesse geaendert
   void onSize(int cx, int cy);
   // Inhalt refreshen (false -> Abbruch)
   bool onRefresh();
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommandUI(cwCmdUI& cmd);
   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


protected:

   // Interner Konstruktor
   cwNotebookCtl(void *wnd);


private:

   // Initialisierung
   void init();

   // Zusaetzliche Informationen
   struct ADD_INFO;
   ADD_INFO *info;

   // Intern: Wird aufgerufen, um den Seitenwechsel anzukuendigen
   bool onPageChanging();
   // Intern: Wird aufgerufen, um den Seitenwechsel bekanntzugeben
   void onPageChanged();

};

#endif /*__INTERFACE__*/


// Implementierung cwNotebookCtl
// ===========================================================================

typedef cArray<cwWindow*,cwWindow*> PAGE_ARRAY;

struct cwNotebookCtl::ADD_INFO {
   int cur_page_idx;
   PAGE_ARRAY page_array;    // Array eingefuegter Seiten
   #if defined __ECL_W32__
      CFont nb_font;
   #endif
};

cwNotebookCtl::cwNotebookCtl(void *wnd) :
   cwControl(wnd)
{
   info = new ADD_INFO;
   info->cur_page_idx = -1;
}

cwNotebookCtl::~cwNotebookCtl()
{
   if ( getFlags(wflAutoDeletePages) ) {
      for ( int page_idx = 0 ; page_idx < getPageCount() ; page_idx++ ) {
         cwWindow *page = info->page_array[page_idx];
         delete page;
      }
   }

   delete info;
}

void cwNotebookCtl::init()
{
   info = new ADD_INFO;
   info->cur_page_idx = -1;

   #if defined __ECL_W32__
      _wnd = new WCTabCtrl(this);
   #elif defined __ECL_OS2__
      // ...
   #endif
}


// Allgemeines
// ===========

void cwNotebookCtl::create(cwWindow *parent, int id, int style, const cdRect& rect)
{
   setParent(parent);

   #if defined __ECL_W32__

      int mfc_style = TCS_TABS | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
      if ( style & wsMultiLine ) mfc_style |= TCS_MULTILINE;
      if ( style & wsSingleLine ) mfc_style &= ~TCS_MULTILINE;

      WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
      CWnd *mfc_parent = (CWnd*)__getWnd(parent);

      CRect mfc_rect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      if ( rect.isEmpty() ) mfc_rect = CFrameWnd::rectDefault;

      if ( __ECL_ASSERT1__(mfc_ctrl->Create(mfc_style, mfc_rect, mfc_parent, id)) ) {
         LOGFONT lf;
         if ( SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof lf, &lf, 0) ) {
            info->nb_font.CreateFontIndirect(&lf);
            mfc_ctrl->SetFont(&info->nb_font);
         }
      }

   #elif defined __ECL_OS2__
   #endif
}

void cwNotebookCtl::setIconList(const cwIconList& ilist)
{
   #if defined __ECL_W32__
      WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
      CImageList *mfc_ilist = (CImageList*)ccwIconList::__getIList(&ilist);
      mfc_ctrl->SetImageList(mfc_ilist);
   #else
      // ...
   #endif
}

int cwNotebookCtl::addPage(cwWindow *page, cResource title, int bmp_idx, int before_idx)
{
   #if defined __ECL_W32__
      CString mfc_title; mfc_title.LoadString(title.getID());
      return addPage(page, (const char *)mfc_title, bmp_idx, before_idx);
   #else
   #endif
}

int cwNotebookCtl::addPage(cwWindow *page, cString title, int bmp_idx, int before_idx)
{
   int page_idx = before_idx;
   if ( page_idx < 0 || page_idx > getPageCount() )
      page_idx = getPageCount();

   #if defined __ECL_W32__

      WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
      TCITEM item; memset(&item, 0, sizeof item);
      char text[100]; strxcpy(text, title, sizeof text);

      item.mask = TCIF_PARAM;
      if ( bmp_idx >= 0 && ((WCTabCtrl*)_wnd)->GetImageList() != NULL )
         item.mask |= TCIF_IMAGE;
      if ( !title.isEmpty() )
         item.mask |= TCIF_TEXT;

      item.iImage = bmp_idx;
      item.pszText = text;
      item.lParam = (long)page;

      page_idx = mfc_ctrl->InsertItem(page_idx, &item);

   #elif defined __ECL_OS2__
   #endif

   if ( __ECL_ASSERT1__(page_idx >= 0) ) {

      page->setFlags(wflInNotebook);
      page->setParent(this);

      info->page_array.insertAt(page_idx, page);
      onPageAdded(page_idx, page);

      // Erste eingefuegte Seite?
      // Initialen Seitenwechsel ausfuehren!
      if ( getPageCount() == 1 )
         onPageChanged();

   }

   return page_idx;
}

void cwNotebookCtl::removePage(int page_idx)
{
   if ( __ECL_ASSERT1__(page_idx >= 0 && page_idx < getPageCount()) ) {

      cwWindow *page = info->page_array[page_idx];

      page->setFlags(wflInNotebook, false);
      page->setParent(0);

      info->page_array.removeAt(page_idx);
      onPageRemoved(page_idx, page);

      #if defined __ECL_W32__
         WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
         __ECL_ASSERT1__(mfc_ctrl->DeleteItem(page_idx));
      #elif defined __ECL_OS2__
      #endif

   }
}

void cwNotebookCtl::gotoPage(int page_idx)
{
   if ( __ECL_ASSERT1__(page_idx >= 0 && page_idx < getPageCount()) ) {
      #if defined __ECL_W32__
         WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
         int prev_page_idx = mfc_ctrl->SetCurSel(page_idx);
         if ( __ECL_ASSERT1__(prev_page_idx >= 0) )
            onPageChanged();
      #elif defined __ECL_OS2__
      #endif
   }
}

int cwNotebookCtl::getCurrentPage() const
{
   #if defined __ECL_W32__
      WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
      return mfc_ctrl->GetCurSel();
   #elif defined __ECL_OS2__
   #endif
}

int cwNotebookCtl::findPage(cwWindow *page) const
{
   for ( int page_idx = 0 ; page_idx < getPageCount() ; page_idx++ ) {
      if ( info->page_array[page_idx] == page )
         return page_idx;
   }

   return -1;
}

cwWindow * cwNotebookCtl::getPage(int page_idx) const
{
   return page_idx >= 0 && __ECL_ASSERT1__(page_idx < getPageCount()) ?
      info->page_array[page_idx]
    : 0;
}

int cwNotebookCtl::getPageCount() const
{
   return info->page_array.getSize();
}


// Zusaetzliche Events
// ===================

void cwNotebookCtl::onPageAdded(int page_idx, cwWindow *page)
{
   cBase::DbgTrcWin("cwNotebookCtl::onPageAdded(%d)", page_idx);
   callEvent(evtPageAdded, (void*)page, page_idx);
}

void cwNotebookCtl::onPageRemoved(int page_idx, cwWindow *page)
{
   cBase::DbgTrcWin("cwNotebookCtl::onPageRemoved(%d)", page_idx);
   callEvent(evtPageRemoved, (void*)page, page_idx);
}

bool cwNotebookCtl::onPageChanging(int cur_page_idx)
{
   cBase::DbgTrcWin("cwNotebookCtl::onPageChanging(%d)", cur_page_idx);
   callEvent(evtPageChanging, cur_page_idx);
   return true;
}

void cwNotebookCtl::onPageChanged(int prev_page_idx, int new_page_idx)
{
   cBase::DbgTrcWin("cwNotebookCtl::onPageChanged(from %d to %d)", prev_page_idx, new_page_idx);
   callEvent(evtPageChanged, prev_page_idx, new_page_idx);
}

bool cwNotebookCtl::onPageChanging()
{
   return onPageChanging(info->cur_page_idx);
}

void cwNotebookCtl::onPageChanged()
{
   int prev_page_idx = info->cur_page_idx;
   int new_page_idx = getCurrentPage();

   if ( prev_page_idx != new_page_idx ) {
      cwWindow *prev_page = getPage(prev_page_idx);
      cwWindow *new_page = getPage(new_page_idx);
      if ( prev_page != 0 )
         prev_page->hide();
      if ( new_page != 0 ) {
         new_page->show();
         if ( isShowing() && !new_page->getFlags(wflWasRefreshed) )
            new_page->refresh();
      }
      onSize(0, 0);
      onPageChanged(prev_page_idx, new_page_idx);
      info->cur_page_idx = new_page_idx;
   }
}


// Ueberschriebene Events
// ======================

void cwNotebookCtl::onSize(int cx, int cy)
{
   cwControl::onSize(cx, cy);

   cwWindow *page = getPage(getCurrentPage());

   if ( page != 0 ) {
      #if defined __ECL_W32__
         WCTabCtrl *mfc_ctrl = (WCTabCtrl*)_wnd;
         WCWnd *mfc_page = (WCWnd*)__getWnd(page);
         if ( mfc_page != 0
           && mfc_page->m_hWnd != NULL
           && mfc_ctrl->m_hWnd != NULL )
         {
            CRect rect;
            mfc_ctrl->GetClientRect(rect);
            if ( !rect.IsRectEmpty() ) {
               mfc_ctrl->AdjustRect(FALSE, rect);
               mfc_page->MoveWindow(rect, TRUE);
               mfc_page->ShowWindow(SW_SHOWNOACTIVATE);
            }
         }
      #elif defined __ECL_OS2__
      #endif
   }
}

bool cwNotebookCtl::onRefresh()
{
   // Optimierung fuer Notebook-Controls: Hier nur die jeweils aktive Seite
   // aktualisieren (die anderen werden beim Anblaettern aktualisiert!)

   cwWindow *child = getPage(getCurrentPage());
   if ( child != 0 )
      child->refresh();

   return false;
}

bool cwNotebookCtl::onCommand(const cwCmdEvt& cmd)
{
   // Kommando weiterleiten an aktives Kindfenster
   cwWindow *child = getActiveChild();
   if ( child == 0 )
      child = getPage(getCurrentPage());
   if ( child != 0 && ccwWindow::onCommand(child, cmd) )
      return true;

   cwWindow *parent = getParent();
   if ( parent != 0 && parent->ECL_ISKINDOF(cwDialog) ) {
      switch ( cmd.getId() ) {
      case IDOK:
      case IDCANCEL:
         // Das duerfte den NB-Parent mehr interessieren,
         // z.B. fuer Dialogbox-Ende o.ae.

         /* ??? Verursacht laufend "Stack Overflow":
          * TBD: Wieso???
         getParent()->sendCommand(cmd);
          */
         break;
      }
   }

   return cwControl::onCommand(cmd);
}

bool cwNotebookCtl::onCommandUI(cwCmdUI& cmd)
{
   // UI-Aktualisierung weiterleiten an aktives Kindfenster
   cwWindow *child = getActiveChild();
   if ( child == 0 )
      child = getPage(getCurrentPage());
   if ( child != 0 )
      return ccwWindow::onCommandUI(child, cmd);

   return false;
}

int cwNotebookCtl::onGetStyles(int mask) const
{
   int rc = 0;

   #if defined __ECL_W32__

      DWORD style = ((WCTabCtrl*)_wnd)->GetStyle();

      if ( (mask & wsMultiLine) && (style & TCS_MULTILINE) )
         rc |= wsMultiLine;
      if ( (mask & wsSingleLine) && !(style & TCS_MULTILINE) )
         rc |= wsSingleLine;

   #elif defined __ECL_OS2__

      // ...

   #endif

   return rc | cwControl::onGetStyles(mask);
}

void cwNotebookCtl::onModifyStyles(int add, int remove, int os_add[], int os_remove[])
{
   #if defined __ECL_W32__

      if ( add & wsMultiLine )
         os_add[0] |= TCS_MULTILINE;
      if ( add & wsSingleLine )
         os_add[0] &= ~TCS_MULTILINE;

      if ( remove & wsMultiLine )
         os_remove[0] &= ~TCS_MULTILINE;
      if ( remove & wsSingleLine )
         os_remove[0] |= TCS_MULTILINE;

      cwControl::onModifyStyles(add, remove, os_add, os_remove);

   #elif defined __ECL_OS2__

      // ...

   #endif
}


