// ===========================================================================
// ew_views.cpp                                                 ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwWindow
//        |
//        +-cwView                  - View
//
// ===========================================================================

#include "win/ew_views.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
   #include "win/system/mfc/eclres.h"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_docview.hpp"
#include "win/ew_windows.hpp"
#include "win/ew_context.hpp"

#endif /*__INTERFACE__*/




// ===========================================================================
// Lokale Klassen cwViewOperationXXXX
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloOperation
//      +--cwViewOperationXXXX
//
// ===========================================================================

static class cwViewOperationZoomIn : public cEloOperation {
   ELO_DECLARE(cwViewOperationZoomIn,cEloOperation)

   void onExecOperation(cEloSelection *selection, int, cEloElement *)
   {
      for ( int i = 0 ; i < selection->getElementCount() ; i++ ) {
         cwZoomView *view = ELO_CAST(cwZoomView, selection->getElement(i));
         if ( view ) view->zoom((view->getZoomLevel() * 13) / 10);
      }
   }

   cString onGetHelpText(const cEloSelection *, int) const
      { return "Ansicht vergrößern"; }
   cString onGetMenuText(const cEloSelection *, int) const
      { return "Vergrößern"; }
   cString onGetSignature() const
      { return "OP_ZOOM_IN"; }

} ViewOperationZoomIn;

static class cwViewOperationZoomOut : public cEloOperation {
   ELO_DECLARE(cwViewOperationZoomOut,cEloOperation)

   void onExecOperation(cEloSelection *selection, int, cEloElement *)
   {
      for ( int i = 0 ; i < selection->getElementCount() ; i++ ) {
         cwZoomView *view = ELO_CAST(cwZoomView, selection->getElement(i));
         if ( view ) view->zoom((view->getZoomLevel() * 10) / 13);
      }
   }

   cString onGetHelpText(const cEloSelection *, int) const
      { return "Ansicht verkleinern"; }
   cString onGetMenuText(const cEloSelection *, int) const
      { return "Verkleinern"; }
   cString onGetSignature() const
      { return "OP_ZOOM_OUT"; }

} ViewOperationZoomOut;

static class cwViewOperationZoomWindow : public cEloOperation {
   ELO_DECLARE(cwViewOperationZoomWindow,cEloOperation)

   void onExecOperation(cEloSelection *selection, int, cEloElement *)
   {
      for ( int i = 0 ; i < selection->getElementCount() ; i++ ) {
         cwZoomView *view = ELO_CAST(cwZoomView, selection->getElement(i));
         if ( view ) view->zoom();
      }
   }

   cString onGetHelpText(const cEloSelection *, int) const
      { return "Zoomen auf Fenstergröße"; }
   cString onGetMenuText(const cEloSelection *, int) const
      { return "Fenstergröße"; }
   cString onGetSignature() const
      { return "OP_ZOOM_WINDOW"; }

} ViewOperationZoomWindow;

static class cwViewOperationZoom100 : public cEloOperation {
   ELO_DECLARE(cwViewOperationZoom100,cEloOperation)

   void onExecOperation(cEloSelection *selection, int, cEloElement *)
   {
      for ( int i = 0 ; i < selection->getElementCount() ; i++ ) {
         cwZoomView *view = ELO_CAST(cwZoomView, selection->getElement(i));
         if ( view ) view->zoom(100);
      }
   }

   cString onGetHelpText(const cEloSelection *, int) const
      { return "Zoomen auf 100%"; }
   cString onGetMenuText(const cEloSelection *, int) const
      { return "100%"; }
   cString onGetSignature() const
      { return "OP_ZOOM_100"; }

} ViewOperationZoom100;




// ===========================================================================
// Lokale Klasse cwViewOperationManager
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloManager
//      +--cEloOperationManager
//          +--cwViewOperationManager
//
// ===========================================================================

static class cwViewOperationManager : public cEloOperationManager {
   ELO_DECLARE(cwViewOperationManager,cEloOperationManager)

public:

   cwViewOperationManager() : cEloOperationManager(false)
      { }

protected:

   void onInitialize()
   {
      addOperation(&ViewOperationZoomIn);
      addOperation(&ViewOperationZoomOut);
      addOperation(&ViewOperationZoomWindow);
      addOperation(&ViewOperationZoom100);
   }

   cString onGetSignature() const
      { return "cwViewOperationManager"; }

} ViewOperationManager;




// ===========================================================================
// Lokale Klasse cwViewDefaultDescription
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloDescription
//      +--cEloElementDescription
//          +--cwViewDefaultDescription
//
// ===========================================================================

static class cwViewDefaultDescription : public cEloElementDescription {
   ELO_DECLARE(cwViewDefaultDescription,cEloElementDescription)

   void onInitialize()
      { }

   cString onGetSignature() const
      { return "cwViewDefaultDescription"; }

} ViewDefaultDescription;




// ===========================================================================
// Lokale Klasse cwZoomViewDefaultDescription
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloDescription
//      +--cEloElementDescription
//          +--cwZoomViewDefaultDescription
//
// ===========================================================================

static class cwZoomViewDefaultDescription : public cEloElementDescription {
   ELO_DECLARE(cwZoomViewDefaultDescription,cEloElementDescription)

   void onInitialize()
   {
      inheritFrom(&ViewDefaultDescription);
      registerOperation(&ViewOperationManager, "OP_ZOOM_IN");
      registerOperation(&ViewOperationManager, "OP_ZOOM_OUT");
      registerOperation(&ViewOperationManager, "OP_ZOOM_WINDOW");
      registerOperation(&ViewOperationManager, "OP_ZOOM_100");
   }

   cString onGetSignature() const
      { return "cwZoomViewDefaultDescription"; }

} ZoomViewDefaultDescription;




// ===========================================================================
// Definition cwZoomViewActionDescriptioniption
// ---------------------------------------------------------------------------
//
// cEloBase
//  +--cEloDescription
//      +--cEloActionDescription
//          +--cwZoomViewActionDescription
//
// ===========================================================================

static class cwZoomViewActionDescription : public cEloActionDescription {

   void onInitialize()
   {
      addObject(cwView::getOperationManager()->getOperation("OP_ZOOM_IN"), ECL_ID_VIEW_ZOOM_IN);
      addObject(cwView::getOperationManager()->getOperation("OP_ZOOM_OUT"), ECL_ID_VIEW_ZOOM_OUT);
      addObject(cwView::getOperationManager()->getOperation("OP_ZOOM_WINDOW"), ECL_ID_VIEW_ZOOM_WINDOW);
      addObject(cwView::getOperationManager()->getOperation("OP_ZOOM_100"), ECL_ID_VIEW_ZOOM_100);
   }

} ZoomViewActionDescription;




#ifdef __INTERFACE__

// ===========================================================================
// cwView
// ---------------------------------------------------------------------------
//
// Um den Inhalt des Views zu zeichnen, muss der Anwender die virtuelle
// Methode onDraw() ableiten und die Zeichenoperationen innerhalb dieser
// Funktion ausfuehren.
//
// cBase
//  +--cwWindow
//      +--cwView
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwView : public cwWindow, public cEloView {
   ELO_DECLARE(cwView,cwWindow)
   friend class ccwView;

public:

   // Konstruktor ueber Elementbeschreibung (direkt)
   inline cwView(const cEloElementDescription *elem_descr = 0) :
      cwWindow(0) { init(elem_descr); }
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   inline cwView(const cEloDescriptionManager *descr_manager, cString descr_sig) :
      cwWindow(0) { init(descr_manager, descr_sig); }
   // Destruktor
   virtual ~cwView();


   // window-Flags
   // ============

   // Flags
   enum FLAGS { wflFirst = cwWindow::wflUser,
      wflViewIsTabbed      = wflFirst << 0,  // Kennzeichnet Tabbed-Views
      wflUser              = wflFirst << 1   // Offset fuer benutzerdef. Flags
   };


   // Allgemeines
   // ===========

   // Standard Elementbeschreibung ermitteln
   static const cEloElementDescription *getDefaultDescription();
   // Operation Manager fuer Standard-View-Operationen ermitteln
   static const cEloOperationManager *getOperationManager();

   // Client-Fenster setzen
   void setClient(cwWindow *win);
   // Client-Fenster erfragen
   inline cwWindow *getClient() const
      { return client; }


protected:

   // Zusaetzliche Events
   // ===================

   // Eindeutige Kennung der View-Klasse ermitteln
   virtual int onGetViewType() const
      { return 0; }

   // Wird bei der Initialisierung des Views aufgerufen
   virtual void onInit();
   // Wird aufgerufen, wenn der View angezeigt wird
   virtual void onShowView();
   // Wird aufgerufen, wenn der View verborgen wird
   virtual void onHideView();

   struct DRAW_INFO {         // ALT, NICHT MEHR VERWENDEN!!!
      cdRect redraw_area;     // Ungueltiger Bereich (in Geraetekoordinaten)
      bool erase_bkgnd;       // Muss der Hintergrund geloescht werden?
   };

   // Wird aufgerufen, um den Anzeigebereich des Views zu zeichnen
   virtual void onDraw(cwContext *ctxt);
   // ALT, NICHT MEHR VERWENDEN!!! Wird aufgerufen, um den Anzeigebereich des Views zu zeichnen
   virtual void onDraw(void *ctxt);
   // ALT, NICHT MEHR VERWENDEN!!! Wird aufgerufen, um den Anzeigebereich des Views zu zeichnen (inkl. Draw-Informationen)
   virtual void onDrawEx(void *ctxt, const DRAW_INFO& draw_info);


   // Ueberschriebene Events
   // ======================

   // Fenster wird erzeugt
   // rc: true -> Erzeugen OK; false -> Nicht erzeugen
   bool onCreate();
   // Groesse geaendert
   void onSize(int cx, int cy);
   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   // rc: true -> Meldung bearbeitet; false -> Default ausfuehren
   bool onCommandUI(cwCmdUI& cmd);

   // Wird aufgerufen, wenn das Dokument vom View "entkoppelt" wird
   void onDocumentRemoved();
   // Wird aufgerufen, um den Zeiger auf ein aktuelles Selektionsobjekt zu ermitteln
   cEloSelection *onGetWindowElemSelection();
   // Wird aufgerufen, um die aktuelle Element-Selektion zu ermitteln
   bool onUpdateWindowElemSelection(cEloSelection& selection) const;

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return "cwView"; }


protected:

   // Interner Konstruktor ohne Elementbeschreibung
   cwView(void *wnd);
   // Interner Konstruktor ueber Elementbeschreibung (direkt)
   cwView(void *wnd, const cEloElementDescription *elem_descr);
   // Interner Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cwView(void *wnd, const cEloDescriptionManager *descr_manager, cString descr_sig);


private:

   // Initialisierung (Elementbeschreibung direkt)
   void init(const cEloElementDescription *elem_descr);
   // Initialisierung (Elementbeschreibung ueber Signatur)
   void init(const cEloDescriptionManager *descr_manager, cString descr_sig);

   // Client-Fenster (fuer Variante mit einem Client)
   cwWindow *client;

};

#endif /*__INTERFACE__*/


// Implementierung cwView
// ===========================================================================

cwView::cwView(void *wnd)
   : cwWindow(wnd)
{
   init(0);
}

cwView::cwView(void *wnd, const cEloElementDescription *elem_descr) :
   cwWindow(wnd)
{
   init(elem_descr);
}

cwView::cwView(void *wnd, const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cwWindow(wnd)
{
   init(descr_manager, descr_sig);
}

cwView::~cwView()
{
}

void cwView::init(const cEloElementDescription *elem_descr)
{
   client = 0;
   setFlags(wflIsAView);
   setElemDescr(elem_descr == 0 ? getDefaultDescription() : elem_descr);
}

void cwView::init(const cEloDescriptionManager *descr_manager, cString descr_sig)
{
   client = 0;
   setFlags(wflIsAView);
   setElemDescr(descr_manager, descr_sig);
}


// Allgemeines
// ===========

const cEloElementDescription * cwView::getDefaultDescription()
{
   return &ViewDefaultDescription;
}

const cEloOperationManager * cwView::getOperationManager()
{
   return &ViewOperationManager;
}

void cwView::setClient(cwWindow *win)
{
   client = win;

   if ( client != 0 && _wnd != 0 ) {
      if ( getFlags(wflViewIsTabbed) ) {
         WCWnd *mfc_client = (WCWnd*)__getWnd(client);
         WCTabView *mfc_view = (WCTabView*)_wnd;
	      mfc_view->SetHasInternalScrollBars(
            mfc_client->IsKindOf(RUNTIME_CLASS(CEdit))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CEditView))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CListBox))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CTreeCtrl))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CTreeView))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CListCtrl))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CListView))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CRichEditView)));
	      mfc_view->SetNeedsInternalRedrawing(
            mfc_client->IsKindOf(RUNTIME_CLASS(CEdit))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CEditView))
		   || mfc_client->IsKindOf(RUNTIME_CLASS(CListBox)));
      }
      client->setParent(this);
      cdRect pos = getClientPos();
      client->setPos(pos);
   }
}


// Zusaetzliche Events
// ===================

void cwView::onInit()
{
}

void cwView::onShowView()
{
}

void cwView::onHideView()
{
}

void cwView::onDraw(cwContext *ctxt)
{
   // Kompatiblitaet ueber alles: Das alte onDraw aufrufen:
   onDraw(ccdContext::getContext(ctxt));
}

void cwView::onDraw(void *ctxt)
{
   if ( client == 0 ) {

      DRAW_INFO draw_info;

      #if defined __ECL_W32__
         CPaintDC *pdc = (CPaintDC*)ctxt;
         RECT &rcp = pdc->m_ps.rcPaint;
         draw_info.redraw_area = cdRect(rcp.left, rcp.bottom, rcp.right, rcp.top);
         draw_info.erase_bkgnd = !!pdc->m_ps.fErase;
      #else
         memset(&di, 0, sizeof di);
      #endif

      onDrawEx(ctxt, draw_info);
   }
}

void cwView::onDrawEx(void *ctxt, const DRAW_INFO& /*draw_info*/)
{
   #if defined __ECL_W32__
      CDC *dc = (CDC*)ctxt;
      CRect rect;
      if ( getFlags(wflViewIsTabbed) ) {
         WCTabView *view = (WCTabView*)_wnd;
         view->GetClientRect(rect);
      } else {
         WCView *view = (WCView*)_wnd;
         CRect rect; view->GetClientRect(rect);
      }
      dc->DrawText("Empty View", -1, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

bool cwView::onCreate()
{
   if ( !cwWindow::onCreate() )
      return false;

   if ( client != 0 && _wnd != 0 ) {
      client->setParent(this);
      cdRect pos = getClientPos();
      client->setPos(pos);
   }

   // Einmalig updateWindowElemSelection(), damit der View als Element
   // in der Selektion eingetragen ist (wg. Operationen auf View)

   updateWindowElemSelection();

   // onInit() aufrufen

   onInit();

   return true;
}

void cwView::onSize(int cx, int cy)
{
   cwWindow::onSize(cx, cy);

   if ( client != 0 ) {
      cdRect pos = getClientPos();
      client->setPos(pos);
   }
}

bool cwView::onCommand(const cwCmdEvt& cmd)
{
   cEloSelection *sel = getSelection();

   // Aktuelle Selektion ermitteln

   for ( cwWindow *win = this ; win != 0 ; win = win->getActiveChild() ) {
      if ( win->hasWindowElemSelection() ) {
         if ( (sel = win->getWindowElemSelection()) == 0 ) {
            sel = getSelection();
            win->updateWindowElemSelection(*sel);
         }
         break;
      }
   }

   // Selektion fuer das aktuelle Fenster ('this') vorbereiten
   cEloSelection this_selection;
   this_selection.addElement(this);

   cEloActionDescription *ad = getWindowActionDescription(sel);

   if ( ad != 0 ) {
      cEloOperation *op = ad->getOperation(cmd.getId(), true);
      if ( op != 0 ) {
         cString sig = op->getSignature();
         int sub_id = ad->getOperationSubId(cmd.getId(), true);
         if ( sel != 0 && sel->supportsOperation(sig) && op->isEnabled(sel) ) {
            sel->execOperation(sig, sub_id, this);
            return true;
         } else if ( this_selection.supportsOperation(sig) && op->isEnabled(&this_selection) ) {
            this_selection.execOperation(sig, sub_id, this);
            return true;
         } else if ( op->isStatic() && op->isEnabled() ) {
            op->execOperation();
            return true;
         }
      }
   }

   return false;
}

bool cwView::onCommandUI(cwCmdUI& cmd)
{
   cEloSelection *sel = getSelection();

   // Aktuelle Selektion ermitteln
   //    TBD: Kann das nicht "weg"-optimiert werden? Voraussetzung, dass die sowieso vorhandene Selektion
   //    des Views schon up-to-date ist: Diese einfach benutzen!

   for ( cwWindow *win = this ; win != 0 ; win = win->getActiveChild() ) {
      if ( win->hasWindowElemSelection() ) {
         if ( (sel = win->getWindowElemSelection()) == 0 ) {
            sel = getSelection();
            win->updateWindowElemSelection(*sel);
         }
         break;
      }
   }

   // Selektion fuer das aktuelle Fenster ('this') vorbereiten
   cEloSelection this_selection;
   this_selection.addElement(this);

   // Operation enabled?

   cEloActionDescription *ad = getWindowActionDescription(sel);

   if ( ad != 0 ) {
      cEloOperation *op = ad->getOperation(cmd.getId(), true);
      if ( op != 0 ) {
         cString sig = op->getSignature();
         if ( op->isStatic() && op->isEnabled()
           || sel->supportsOperation(sig) && op->isEnabled(sel)
           || this_selection.supportsOperation(sig) && op->isEnabled(&this_selection) )
         {
            cmd.setEnable(true);
         } else {
            cmd.setEnable(false);
         }
         if ( op->isCheckable(sel) )
            cmd.setCheck(op->isChecked(sel));
         return true;
      } else {
         #undef __Disable_Cmd_If_Not_Connected_To_Operation__
         #if __Disable_Cmd_If_Not_Connected_To_Operation__
            cmd.setEnable(false);
            return true;
         #endif
      }
   }

   // Keine passende Operation gefunden, Default ausfuehren

   return cwWindow::onCommandUI(cmd);
}


// Ueberschriebene Events
// ======================

void cwView::onDocumentRemoved()
{
   #ifdef __ECL_W32__
      if ( getFlags(wflViewIsTabbed) ) {
         WCTabView *view = (WCTabView*)_wnd;
         view->Invalidate(TRUE);
      } else {
         WCView *view = (WCView*)_wnd;
         view->Invalidate(TRUE);
      }
   #else
      // ...
   #endif
}

cEloSelection * cwView::onGetWindowElemSelection()
{
   return getSelection();
}

bool cwView::onUpdateWindowElemSelection(cEloSelection& selection) const
{
   // Die Default-Implementierung nimmt den View selbst als Element in die
   // Selektion auf. So koennen die Operationen des Views ausgefuehrt werden.

   selection.clearSelection();
   selection.addElement((cwView*)this);
   return true;
}




#ifdef __INTERFACE__

// ===========================================================================
// cwZoomView
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwView
//          +--cwZoomView
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwZoomView : public cwView {
   ELO_DECLARE(cwZoomView,cwView)
   friend class ccwView;

public:

   // Konstruktor ohne Elementbeschreibung
   inline cwZoomView() :
      cwView((void*)0, getDefaultDescription()) { init(); }
   // Konstruktor ueber Elementbeschreibung (direkt)
   inline cwZoomView(const cEloElementDescription *elem_descr) :
      cwView((void*)0, elem_descr) { init(); }
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   inline cwZoomView(const cEloDescriptionManager *descr_manager, cString descr_sig) :
      cwView((void*)0, descr_manager, descr_sig) { init(); }
   // Destruktor
   virtual ~cwZoomView();


   // Allgemeines
   // ===========

   // Standard Elementbeschreibung ermitteln
   static const cEloElementDescription *getDefaultDescription();

   // Arbeitsbereich einstellen (Basis fuer Scrollbars)
   void setWorld(const cdRect& log_area);
   // Massleisten anzeigen / verbergen
   void showRulers(bool show = true);
   // Massleisten kalibrieren (1 = m, 100 = cm, 1000 = mm)
   void calibrateRulers(int factor);
   // Massleisten mit letztem Wert neu kalibrieren
   void calibrateRulers();
   // Werden die Massleisten momentan angezeigt?
   bool areRulersShown() const;
   // Aktuellen Kalibrierfaktor erfragen
   int getRulerCalibration() const;


   // Zoom
   // ====

   // Zoomlevel einstellen, Zentrieren auf Bildmitte
   void zoom(int level);
   // Zoomlevel einstellen, Zentrieren auf 'center' (log. Koord.)
   void zoom(int level, const cdPoint& center);

   // Zoom auf aktuelle Fenstergroesse (keine Rollbalken sichtbar)
   void zoom();
   // Zoom auf Rechteck (in log. Koord.)
   void zoom(const cdRect& rect, int pixborder = 10);

   // Aktuellen Zoomlevel erfragen
   int getZoomLevel() const
      { return zoom_level; }


   // Koordinatentransformation
   // =========================
   // Diese Funktionen beruecksichtigen die aktuelle Scrollposition
   // und den aktuellen Zoomlevel

   // LOGICAL -> DEVICE Transformation eines Punktes
   cdPoint convLogToDev(const cdPoint& p) const;
   // LOGICAL -> DEVICE Transformation einer Groesse
   cdSize convLogToDev(const cdSize& s) const;
   // LOGICAL -> DEVICE Transformation eines Rechtecks
   cdRect convLogToDev(const cdRect& r) const;

   // DEVICE -> LOGICAL Transformation eines Punktes
   cdPoint convDevToLog(const cdPoint& p) const;
   // DEVICE -> LOGICAL Transformation einer Groesse
   cdSize convDevToLog(const cdSize& s) const;
   // DEVICE -> LOGICAL Transformation eines Rechtecks
   cdRect convDevToLog(const cdRect& r) const;


protected:

   // Ueberschriebene Events
   // ======================

   // Eindeutige Kennung der View-Klasse ermitteln
   int onGetViewType() const
      { return 1; }
   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return "cwZoomView"; }

   // Wird aufgerufen, um zu erfragen, ob eine Element-Selektion moeglich ist
   bool onHasWindowElemSelection() const;
   // Wird aufgerufen, um den Zeiger auf die ELO-Aktionsbeschreibung zu ermitteln
   cEloActionDescription *onGetWindowActionDescription(const cEloSelection *selection) const;

protected:

   // Interner Konstruktor ohne Elementbeschreibung
   cwZoomView(void *wnd);
   // Interner Konstruktor ueber Elementbeschreibung (direkt)
   cwZoomView(void *wnd, const cEloElementDescription *elem_descr);
   // Interner Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cwZoomView(void *wnd, const cEloDescriptionManager *descr_manager, cString descr_sig);


private:

   // Aktueller Zoom-Level (von 1% bis 1000%)
   int zoom_level;
   // Aktueller Kalibrierungs-Faktor der Massleisten
   int ruler_factor;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwZoomView
// ===========================================================================

cwZoomView::cwZoomView(void *wnd)
   : cwView(wnd, getDefaultDescription())
{
   init();
}

cwZoomView::cwZoomView(void *wnd, const cEloElementDescription *elem_descr) :
   cwView(wnd, elem_descr)
{
   init();
}

cwZoomView::cwZoomView(void *wnd, const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cwView(wnd, descr_manager, descr_sig)
{
   init();
}

cwZoomView::~cwZoomView()
{
}

void cwZoomView::init()
{
   zoom_level = 100;
   ruler_factor = 100;
}


// Allgemeines
// ===========

const cEloElementDescription * cwZoomView::getDefaultDescription()
{
   return &ZoomViewDefaultDescription;
}

void cwZoomView::setWorld(const cdRect& log_area)
{
   #ifdef __ECL_W32__
      CRect mfc_rect(CPoint(log_area.lb.x, log_area.rt.y), CPoint(log_area.rt.x, log_area.lb.y));
      ((WCZoomView*)_wnd)->SetDeviceScrollSizesRelative(MM_LOMETRIC, mfc_rect); // TBD: metric einstellen
      //((WCZoomView*)_wnd)->SetAlignToBottom(TRUE);
      ((WCZoomView*)_wnd)->SetZoomAlign(WCZoomView::ZV_CENTER);
   #else
      // ...
   #endif

   calibrateRulers();
}

void cwZoomView::showRulers(bool show)
{
   #ifdef __ECL_W32__
      if ( _wnd != 0 && ((WCZoomView*)_wnd)->m_hWnd != 0 ) {
         ((WCZoomView*)_wnd)->GetRulerOrganizer()->SetShowHorzRulerBar(show);
         ((WCZoomView*)_wnd)->GetRulerOrganizer()->SetShowVertRulerBar(show);
      }
   #else
      // ...
   #endif
}

void cwZoomView::calibrateRulers(int factor)
{
   ruler_factor = factor;

   #ifdef __ECL_W32__
      if ( _wnd != 0 && ((WCZoomView*)_wnd)->m_hWnd != 0 ) {
         factor = int(double(factor) * 2.54);
         ((WCZoomView*)_wnd)->GetRulerOrganizer()->CalibrateRuler(factor, FALSE);
         ((WCZoomView*)_wnd)->GetRulerOrganizer()->CalibrateRuler(factor, TRUE);
      }
   #else
      // ...
   #endif
}

void cwZoomView::calibrateRulers()
{
   calibrateRulers(ruler_factor);
}

bool cwZoomView::areRulersShown() const
{
   bool shown = false;

   #ifdef __ECL_W32__
      if ( _wnd != 0 && ((WCZoomView*)_wnd)->m_hWnd != 0 ) {
         shown =
            ((WCZoomView*)_wnd)->GetRulerOrganizer()->GetShowHorzRulerBar()
         && ((WCZoomView*)_wnd)->GetRulerOrganizer()->GetShowVertRulerBar();
      }
   #else
      // ...
   #endif

   return shown;
}

int cwZoomView::getRulerCalibration() const
{
   int factor = 0;

   #ifdef __ECL_W32__
      if ( _wnd != 0 && ((WCZoomView*)_wnd)->m_hWnd != 0 ) {
         double dbl_factor = ((WCZoomView*)_wnd)->GetRulerOrganizer()->GetRulerCalibrate(TRUE);
         factor = int(dbl_factor / 2.54);
      }
   #else
      // ...
   #endif

   return factor;
}


// Zoom
// ====

void cwZoomView::zoom(int level)
{
   if ( __ECL_ASSERT1__(level >= 10 && level <= 1000) ) {
      #ifdef __ECL_W32__
         if ( getFlags(wflViewIsTabbed) ) {
      	   ((WCTabZoomView*)_wnd)->SetZoomLevel(level, WCTabZoomView::ZV_CENTER);
            zoom_level = ((WCTabZoomView*)_wnd)->GetZoomLevel();
         } else {
      	   ((WCZoomView*)_wnd)->SetZoomLevel(level, WCZoomView::ZV_CENTER);
            zoom_level = ((WCZoomView*)_wnd)->GetZoomLevel();
         }
      #else
         // ...
      #endif
   }
}

void cwZoomView::zoom(int level, const cdPoint& /*center*/)
{
   if ( __ECL_ASSERT1__(level >= 10 && level <= 1000) ) {
      #ifdef __ECL_W32__
         if ( getFlags(wflViewIsTabbed) ) {
            // TBD: ...
      	   ((WCTabZoomView*)_wnd)->ZoomToWindow();
            zoom_level = ((WCTabZoomView*)_wnd)->GetZoomLevel();
         } else {
            // TBD: ...
      	   ((WCZoomView*)_wnd)->ZoomToWindow();
            zoom_level = ((WCZoomView*)_wnd)->GetZoomLevel();
         }
      #else
         // ...
      #endif
   }
}

void cwZoomView::zoom()
{
   #ifdef __ECL_W32__
      if ( getFlags(wflViewIsTabbed) ) {
         ((WCTabZoomView*)_wnd)->ZoomToWindow();
         zoom_level = ((WCTabZoomView*)_wnd)->GetZoomLevel();
      } else {
         ((WCZoomView*)_wnd)->ZoomToWindow();
         zoom_level = ((WCZoomView*)_wnd)->GetZoomLevel();
      }
   #else
      // ...
   #endif
}

void cwZoomView::zoom(const cdRect& rect, int pixborder)
{
   #ifdef __ECL_W32__
      CRect mfc_rect;
      if ( 1 /* LOMETRIC */ ) {
         mfc_rect = CRect(CPoint(rect.lb.x, rect.rt.y), CPoint(rect.rt.x, rect.lb.y));
      } else {
         mfc_rect = CRect(CPoint(rect.lb.x, rect.lb.y), CPoint(rect.rt.x, rect.rt.y));
      }
      if ( getFlags(wflViewIsTabbed) ) {
         WCTabZoomView *mfc_wnd = (WCTabZoomView*)_wnd;
         mfc_wnd->LPtoDP(mfc_rect);
         mfc_rect.InflateRect(pixborder, pixborder);
         mfc_wnd->ZoomToRectangle(mfc_rect, WCTabZoomView::ZV_CENTER);
         zoom_level = mfc_wnd->GetZoomLevel();
      } else {
         WCZoomView *mfc_wnd = (WCZoomView*)_wnd;
         mfc_wnd->LPtoDP(mfc_rect);
         mfc_rect.InflateRect(pixborder, pixborder);
         mfc_wnd->ZoomToRectangle(mfc_rect, WCZoomView::ZV_CENTER);
         zoom_level = mfc_wnd->GetZoomLevel();
      }
   #else
      // ...
   #endif
}


// Koordinatentransformation
// =========================

cdPoint cwZoomView::convLogToDev(const cdPoint& p) const
{
   #ifdef __ECL_W32__
      CRect mfc_rect(p.x, p.y, p.x, p.y);
      ((WCZoomView*)_wnd)->LPtoDP(&mfc_rect);
      return cdPoint(mfc_rect.left, mfc_rect.top);
   #else
      // ...
   #endif
}

cdSize cwZoomView::convLogToDev(const cdSize& s) const
{
   #ifdef __ECL_W32__
      CRect mfc_rect(0, 0, s.cx, s.cy);
      ((WCZoomView*)_wnd)->LPtoDP(&mfc_rect);
      return cdSize(mfc_rect.Width(), mfc_rect.Height());
   #else
      // ...
   #endif
}

cdRect cwZoomView::convLogToDev(const cdRect& r) const
{
   #ifdef __ECL_W32__
      // TBD: Richtig so ???
      CRect mfc_rect(CPoint(r.lb.x, r.rt.y), CPoint(r.rt.x, r.lb.y));
      ((WCZoomView*)_wnd)->LPtoDP(&mfc_rect);
      return cdRect(mfc_rect.left, mfc_rect.bottom, mfc_rect.right, mfc_rect.top);
   #else
      // ...
   #endif
}

cdPoint cwZoomView::convDevToLog(const cdPoint& p) const
{
   #ifdef __ECL_W32__
      CRect mfc_rect(p.x, p.y, p.x, p.y);
      ((WCZoomView*)_wnd)->DPtoLP(&mfc_rect);
      return cdPoint(mfc_rect.left, mfc_rect.top);
   #else
      // ...
   #endif
}

cdSize cwZoomView::convDevToLog(const cdSize& s) const
{
   #ifdef __ECL_W32__
      CRect mfc_rect(0, 0, s.cx, s.cy);
      ((WCZoomView*)_wnd)->DPtoLP(&mfc_rect);
      return cdSize(mfc_rect.Width(), mfc_rect.Height());
   #else
      // ...
   #endif
}

cdRect cwZoomView::convDevToLog(const cdRect& r) const
{
   #ifdef __ECL_W32__
      // TBD: Richtig so ???
      CRect mfc_rect(CPoint(r.lb.x, r.rt.y), CPoint(r.rt.x, r.lb.y));
      ((WCZoomView*)_wnd)->DPtoLP(&mfc_rect);
      return cdRect(mfc_rect.left, mfc_rect.bottom, mfc_rect.right, mfc_rect.top);
   #else
      // ...
   #endif
}


// Ueberschriebene Events
// ======================

bool cwZoomView::onHasWindowElemSelection() const
{
   return true;
}

cEloActionDescription * cwZoomView::onGetWindowActionDescription(const cEloSelection * /*selection*/) const
{
   return &ZoomViewActionDescription;
}

