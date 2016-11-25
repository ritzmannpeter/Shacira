// ===========================================================================
// ew_draw.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdDevice
//     |   |
//     |   +--cdRetainedDevice
//     |       |
//     |       +--cwDrawDevice         -
//     |
//     +--cdSpace
//     |   |
//     |   +--cwDrawSpace              -
//     |
//     +--cwWindow
//         |
//         +--cwView
//             |
//             +--cwZoomView
//                 |
//                 +--cwDrawView       -
//
//    cEloBase
//     |
//     +--cEloElement
//         |
//         +--cEloDocument             -
//             |
//             +--cwDrawDocument       -
//
// ===========================================================================

#include "win/ew_draw.hpp"
#include "base/eb_err.hpp"
#include "base/eb_list.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>

#if defined(__ECL_OS2__)
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined(__ECL_W32__)
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

#include "base/eb_collect.hpp"
#include "draw/ed_space.hpp"
#include "win/ew_views.hpp"

#endif /*__INTERFACE__*/




// Lokale Funktionen
// ===========================================================================

#if defined(__ECL_OS2__)

   #define METRIC PU_LOMETRIC /*PU_HIMETRIC*/

   #if METRIC == PU_HIMETRIC
      #define METRIC_UNIT 100.0
   #elif METRIC == PU_LOMETRIC
      #define METRIC_UNIT 10.0
   #endif

#elif defined(__ECL_W32__)

   #define METRIC MM_LOMETRIC /*MM_HIMETRIC*/

   #if METRIC == MM_HIMETRIC
      #define METRIC_UNIT 100.0
   #elif METRIC == MM_LOMETRIC
      #define METRIC_UNIT 10.0
   #elif METRIC == MM_TEXT
      #define METRIC_UNIT 1.0
   #endif

#endif




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDrawDevice
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdDevice
//       +--cdRetainedDevice
//           +--cwDrawDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDrawDevice : public cdRetainedDevice {

public:

   inline cwDrawDevice(cwWindow *win = 0, void *ctxt = 0)
      { init(win, ctxt); }
   ~cwDrawDevice();

   void paintAt(cdDeviceStore *elems, const cdPoint& pos);
   void forceRefresh();

   void assocWindow(cwWindow *win);
   void assocContext(void *ctxt);

   cwWindow *getAssocWindow() const;
   void *getAssocContext() const;

private:
   struct DEVICE_INFO;
   DEVICE_INFO *dev_info;

   void init(cwWindow *win, void *ctxt);

};

#endif /*__INTERFACE__*/


// Implementierung cwDrawDevice
// ===========================================================================

struct cwDrawDevice::DEVICE_INFO {
   cwWindow *win;       // Assoziiertes Fenster
   #ifdef __ECL_W32__
      CDC *dc;          // Assoziierter Geraetekontext (DC)
      CDC info_dc;      // Informationskontext (IC)
   #else
      void *ctxt;       // Assoziierter Geraetekontext
   #endif
};

void cwDrawDevice::init(cwWindow *win, void *ctxt)
{
   dev_info = new DEVICE_INFO;
   dev_info->win = win;

   #if defined(__OS2__)
      // Setup HDC with 0.01 mm units
      SIZEL pagesize = { 0, 0 };
      ULONG psflags = GPIA_ASSOC | METRIC | GPIT_NORMAL | GPIF_LONG;
      if ( (hdc = WinOpenWindowDC(win->GetHandle())) == NULLHANDLE )
         DbgError("WinOpenWindowDC failed");
      if ( (hps = GpiCreatePS(win->GetHab(), hdc, &pagesize, psflags)) == NULLHANDLE )
         DbgError("GpiCreatePS failed");
      cwDrawDevice::ctxt = ctxt;
   #elif defined(__ECL_W32__)
      dev_info->info_dc.CreateIC(TEXT("DISPLAY"), NULL, NULL, NULL);
      dev_info->dc = (CDC*)ctxt;
      __setDC(&dev_info->info_dc);
   #endif

   reset();
}

cwDrawDevice::~cwDrawDevice()
{
   #if defined(__OS2__)
      if ( !GpiAssociate(hps, NULLHANDLE) )
         DbgError("GpiAssociate failed");
      if ( !GpiDestroyPS(hps) )
         DbgError("GpiDestroyPS failed");
   #elif defined(__ECL_W32__)
      // Nichts spezielles zu tun...
      __setDC(0);
   #endif

   delete dev_info;
}

void cwDrawDevice::assocWindow(cwWindow *win)
{
   dev_info->win = win;
}

void cwDrawDevice::assocContext(void *ctxt)
{
   #if defined(__ECL_W32__)
      dev_info->dc = (CDC*)ctxt;
      __setDC(ctxt == 0 ? &dev_info->info_dc : (CDC*)ctxt);
   #else
      cwDrawDevice::ctxt = ctxt;
   #endif
}

cwWindow * cwDrawDevice::getAssocWindow() const
{
   return dev_info->win;
}

void * cwDrawDevice::getAssocContext() const
{
   #if defined(__ECL_W32__)
      return dev_info->dc;
   #else
      return dev_info->ctxt;
   #endif
}

void cwDrawDevice::paintAt(cdDeviceStore *elems, const cdPoint& pos)
{
   #if defined(__OS2__)
      HPS saved_hps = hps;
      MATRIXLF tmat;
      double scale = 1.0;
      long start_x = 0;
      long start_y = 0;
      FIXED fscale = MAKEFIXED(int(scale), long((scale - floor(scale)) * 65536.0));

      tmat.fxM11 = fscale;         tmat.fxM12 = MAKEFIXED(0,0); tmat.lM13  = 0;
      tmat.fxM21 = MAKEFIXED(0,0); tmat.fxM22 = fscale;         tmat.lM23  = 0;
      tmat.lM31  = -start_x;       tmat.lM32  = -start_y;       tmat.lM33  = 1;

      if ( (hps = WinBeginPaint(win->GetHandle(), saved_hps, NULL)) != NULLHANDLE ) {
         GpiErase(hps);
         GpiSetDefaultViewMatrix(hps, 9, &tmat, TRANSFORM_REPLACE);
      } else {
         DbgError("WinBeginPaint failed");
      }
   #elif defined(__ECL_W32__)
      CWnd *wnd = (CWnd*)ccwWindow::__getWnd(dev_info->win);
      CRect rect; wnd->GetClientRect(&rect);
      bool own_dc = false;
      if ( dev_info->dc == 0 ) {
         dev_info->dc = new CClientDC(wnd);
         own_dc = true;
      }
      //dc->SetMapMode(METRIC);
      //dc->SetViewportOrg(rect.Width()/2, -rect.Height()/2);
   #endif

   cdRetainedDevice::paintAt(elems, pos);

   #if defined(__OS2__)
      WinEndPaint(hps);
      hps = saved_hps;
   #elif defined(__ECL_W32__)
      if ( own_dc ) {
         delete dev_info->dc;
         dev_info->dc = &dev_info->info_dc;
      }
   #endif
}

void cwDrawDevice::forceRefresh()
{
   #if defined(__OS2__)
      WinInvalidateRect(win->GetHandle(), NULL, false);
   #elif defined(__ECL_W32__)
      CWnd *wnd = (CWnd*)ccwWindow::__getWnd(dev_info->win);
      if ( __ECL_ASSERT1__(wnd != 0) )
         wnd->Invalidate(true);
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDrawSpace
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdSpace
//       +--cwDrawSpace
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDrawSpace : public cdSpace {

public:
   inline cwDrawSpace(cwDrawDevice *dev) : cdSpace(dev)
      { init(dev); }
   ~cwDrawSpace();

   void beginDrawing();
   cdDeviceStore *endDrawing();

protected:

   // Konvertiere physikalische in logische Koordinaten
   long onConvPhys2Log(double phys) const;
   // Konvertiere logische in physikalische Koordinaten
   double onConvLog2Phys(long log) const;

private:
   cwDrawDevice *win_dev;   // Zugeordnetes Windows-Device
   void init(cwDrawDevice *dev);

};

#endif /*__INTERFACE__*/


// Implementierung cwDrawSpace
// ===========================================================================

void cwDrawSpace::init(cwDrawDevice *dev)
{
   cwDrawSpace::win_dev = dev;
}

cwDrawSpace::~cwDrawSpace()
{
}

void cwDrawSpace::beginDrawing()
{
   cdSpace::beginDrawing();
   win_dev->beginDrawing();
}

cdDeviceStore * cwDrawSpace::endDrawing()
{
   cdDeviceStore *elems = win_dev->endDrawing();
   cdSpace::endDrawing();
   return elems;
}

long cwDrawSpace::onConvPhys2Log(double /*mm*/) const
{
   throw cErrBase(cErrBase::errSorry);
   // return (long)(mm * METRIC_UNIT /*+0.5*/);
}

double cwDrawSpace::onConvLog2Phys(long /*w*/) const
{
   throw cErrBase(cErrBase::errSorry);
   // return (double)w / METRIC_UNIT;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDrawDocument
// ---------------------------------------------------------------------------
//
// Basisklasse fuer Draw-Dokumente. Unterstuetzt eine Liste von Zeigern auf
// Draw-Objekte (Basisklasse cdObject), die vom View erfragt und zur Anzeige
// gebracht werden kann.
//
// cEloBase
//  +--cEloElement
//      +--cwDrawDocument
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDrawDocument : public cEloDocument {
   ELO_DECLARE(cwDrawDocument,cEloDocument)

public:

   // Konstruktor ohne Elementbeschreibung
   cwDrawDocument();
   // Konstruktor ueber Elementbeschreibung (direkt)
   cwDrawDocument(const cEloElementDescription *elem_descr);
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cwDrawDocument(const cEloDescriptionManager *descr_manager, cString descr_sig);
   // Destruktor
   virtual ~cwDrawDocument();


   // Allgemeines
   // ===========

   // Zeichenbereich in physikalischen Koordinaten (mm) ermitteln
   inline c2dBox getDrawArea() const
      { return onGetDrawArea(); }


   // Objektliste
   // ===========

   // Startposition der Objekt-Iteration ermitteln
   inline IPOSITION getStartPosition() const
      { return onGetStartPosition(); }
   // Naechstes Objekt der Iteration ermitteln
   inline cdObject *getNextObject(IPOSITION& pos) const
      { return onGetNextObject(pos); }


protected:

   // Objektliste loeschen
   void clearObjects();
   // Objekt an Objektliste anhaengen
   void addObject(cdObject *obj);


protected:

   // Hinzugefuegte Events
   // ====================

   // Wird aufgerufen, um den Zeichenbereich zu ermitteln
   virtual c2dBox onGetDrawArea() const;
   // Wird aufgerufen, um die Objektliste zu loeschen
   virtual void onClearObjects();
   // Wird aufgerufen, um die Objektliste zu loeschen
   virtual void onAddObject(cdObject *obj);
   // Wird aufgerufen, um die Startposition der Objekt-Iteration zu ermitteln
   virtual IPOSITION onGetStartPosition() const;
   // Wird aufgerufen, um das naechste Objekt der Iteration zu ermitteln
   virtual cdObject *onGetNextObject(IPOSITION& pos) const;


private:

   // Zeiger auf die geordnete Objektliste (oder 0)
   struct OBJECTS;
   OBJECTS *objects;

};

#endif /*__INTERFACE__*/


// Implementierung cwDrawDocument
// ===========================================================================

struct cwDrawDocument::OBJECTS {
   cList<cdObject*,cdObject*> list;
};

static class cwDrawDocumentDescription : public cEloElementDescription {
   void onInitialize() { }
   cString onGetSignature() const { return "cwDrawDocumentDescription"; }
   cString onGetName() const { return onGetSignature(); }
} DrawDocumentDescription;

cwDrawDocument::cwDrawDocument() :
   cEloDocument(&DrawDocumentDescription)
{
   objects = 0;
}

cwDrawDocument::cwDrawDocument(const cEloElementDescription *elem_descr) :
   cEloDocument(elem_descr)
{
   objects = 0;
}

cwDrawDocument::cwDrawDocument(const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cEloDocument(descr_manager, descr_sig)
{
   objects = 0;
}

cwDrawDocument::~cwDrawDocument()
{
   delete objects;
}


// Objektliste
// ===========

void cwDrawDocument::clearObjects()
{
   onClearObjects();
}

void cwDrawDocument::addObject(cdObject *obj)
{
   onAddObject(obj);
}


// Hinzugefuegte Events
// ====================

c2dBox cwDrawDocument::onGetDrawArea() const
{
   // TBD: Ermitteln aus BBox aller cdObjects!!!
   return c2dBox();
}

void cwDrawDocument::onClearObjects()
{
   if ( objects != 0 )
      objects->list.removeAll();
}

void cwDrawDocument::onAddObject(cdObject *obj)
{
   if ( __ECL_ASSERT1__(obj != 0) ) {
      if ( objects == 0 )
         objects = new OBJECTS;
      objects->list.addTail(obj);
   }
}

IPOSITION cwDrawDocument::onGetStartPosition() const
{
   return objects != 0 ?
      objects->list.getHeadPosition()
    : 0;
}

cdObject * cwDrawDocument::onGetNextObject(IPOSITION& pos) const
{
   return objects != 0 ?
      objects->list.getNext(pos)
    : 0;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwDrawView
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cwWindow
//       +--cwView
//           +--cwZoomView
//               +--cwDrawView
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwDrawView : public cwZoomView {
   ELO_DECLARE(cwDrawView,cwZoomView)

public:

   // Konstruktor ohne Elementbeschreibung
   inline cwDrawView() :
      cwZoomView((void*)0) { init(); }
   // Konstruktor ueber Elementbeschreibung (direkt)
   inline cwDrawView(const cEloElementDescription *elem_descr) :
      cwZoomView((void*)0, elem_descr) { init(); }
   // Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   inline cwDrawView(const cEloDescriptionManager *descr_manager, cString descr_sig) :
      cwZoomView((void*)0, descr_manager, descr_sig) { init(); }
   // Destruktor
   virtual ~cwDrawView();

   // Refresh des Fensters durchfuehren
   void refresh();

   // Zeichenbereich (Welt) auf Dokumentgroesse einstellen
   void setDrawArea();
   // Zeichenbereich (Welt) einrichten
   void setDrawArea(const c2dBox& draw_area);

   // Zoomen auf Dokumentgroesse
   void zoomToDoc();
   // Zoomen auf Bereich (Weltkoordinaten)
   void zoomToArea(const c2dBox& area);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird bei der Initialisierung des Views aufgerufen
   void onInit();
   // Wird aufgerufen, um den Anzeigebereich des Views zu zeichnen
   void onDraw(void *ctxt);

   // Wird aufgerufen, um das Update des zugeordneten Dokumentes zu signalisieren
   void onUpdate(cEloView *from_view, cEloElement *elem, long hint);
   // Wird aufgerufen, wenn ein Dokument an den View "angehaengt" wird
   void onDocumentAdded();

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const
      { return "cwDrawView"; }


protected:

   // Interner Konstruktor ohne Elementbeschreibung
   cwDrawView(void *wnd);
   // Interner Konstruktor ueber Elementbeschreibung (direkt)
   cwDrawView(void *wnd, const cEloElementDescription *elem_descr);
   // Interner Konstruktor ueber Elementbeschreibung (indirekt ueber Signatur)
   cwDrawView(void *wnd, const cEloDescriptionManager *descr_manager, cString descr_sig);

   cwDrawDevice device;
   cdViewport vport;


private:

   // Gespeicherte Device-Elemente fuer onDraw()
   cdDeviceStore *elems;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwDrawView
// ===========================================================================

cwDrawView::cwDrawView(void *wnd)
   : cwZoomView(wnd)
{
   init();
}

cwDrawView::cwDrawView(void *wnd, const cEloElementDescription *elem_descr) :
   cwZoomView(wnd, elem_descr)
{
   init();
}

cwDrawView::cwDrawView(void *wnd, const cEloDescriptionManager *descr_manager, cString descr_sig) :
   cwZoomView(wnd, descr_manager, descr_sig)
{
   init();
}

cwDrawView::~cwDrawView()
{
   device.assocWindow(0);
   delete elems;
}

void cwDrawView::init()
{
   elems = 0;
   device.assocWindow(this);
}

void cwDrawView::setDrawArea()
{
   cwDrawDocument *doc = (cwDrawDocument*)getDocument();

   if ( doc != 0 ) {
      // Dokumentgroesse uebernehmen
      setDrawArea(doc->getDrawArea());
   } else {
      // Default-Wert einstellen
      setDrawArea(c2dBox(c2dPoint(-500,-500), c2dSize(1000,1000)));
   }
}

void cwDrawView::setDrawArea(const c2dBox& draw_area)
{
   cwDrawSpace space(&device);
   cdRect log_area = device.convPageToLog(draw_area);
   setWorld(log_area);
}

void cwDrawView::zoomToDoc()
{
   cwDrawDocument *doc = (cwDrawDocument*)getDocument();

   if ( doc != 0 ) {
      // Dokumentgroesse uebernehmen
      zoomToArea(doc->getDrawArea());
   } else {
      // Default-Wert einstellen
      zoomToArea(c2dBox(c2dPoint(-500,-500), c2dSize(1000,1000)));
   }
}

void cwDrawView::zoomToArea(const c2dBox& area)
{
   cwDrawSpace space(&device);
   cdRect log_area = device.convPageToLog(area);
   zoom(log_area);
}

void cwDrawView::refresh()
{
   device.forceRefresh();
   cwZoomView::refresh();
}

/*
bool cwDrawView::MouseMoveEvt(const cCmdMouse& cmd)
{
   if ( in_scroll ) {
      int dx = cmd.getPosX() - scroll_start_x;
      int dy = cmd.getPosY() - scroll_start_y;

      c2dVector delta(space.convPel2Unit(dx), space.convPel2Unit(dy));
      c2dVector delta2(vport.start - scroll_start - delta);

      vport.start = scroll_start + delta;
      space.setViewport(vport);

      WinScrollWindow(GetHandle(),
         -space.convUnit2Pel(delta2.x), -space.convUnit2Pel(delta2.y),
         NULL, NULL, NULLHANDLE, NULL, SW_INVALIDATERGN);
      WinUpdateWindow(GetHandle());

      //refresh();
   }

   return cClient::MouseMoveEvt(cmd);
}

bool cwDrawView::MouseButtonMotionStartEvt(const cCmdMouseButton& cmd)
{
   if ( cmd.getButtonNo() == 1 && cmd.holdsCtrl() ) {
      in_scroll = true;
      CaptureMouse(true);

      //SetFocus(); //SetActive();
      scroll_start = vport.start;
      scroll_start_x = cmd.getPosX();
      scroll_start_y = cmd.getPosY();

      return true;
   }

   return cClient::MouseButtonMotionStartEvt(cmd);
}

bool cwDrawView::MouseButtonMotionEndEvt(const cCmdMouseButton& cmd)
{
   if ( in_scroll ) {
      int dx = cmd.getPosX() - scroll_start_x;
      int dy = cmd.getPosY() - scroll_start_y;

      c2dVector delta(space.convPel2Unit(dx), space.convPel2Unit(dy));
      c2dVector delta2(vport.start - scroll_start - delta);

      vport.start = scroll_start - delta;
      space.setViewport(vport);

      //WinScrollWindow(GetHandle(),
      //   -space.convUnit2Pel(delta2.x), -space.convUnit2Pel(delta2.y),
      //   NULL, NULL, NULLHANDLE, NULL, SW_INVALIDATERGN);
      //WinUpdateWindow(GetHandle());

      refresh();

      CaptureMouse(false);
      in_scroll = false;

      return true;
   }

   return cClient::MouseButtonMotionEndEvt(cmd);
}

bool cwDrawView::NormalKeyEvt(const cCmd& cmd, USHORT flags, USHORT& ch)
{
   switch ( ch ) {
    case '+':  zoom(1.5); break;
    case '-':  zoom(1/1.5); break;
    //case '*':  zoom(c2dSize(2000,2000)); break;
   }

   return false;
}
*/

/*
void cwDrawView::zoom(double delta)
{
   if ( !is_zero(delta) ) {
      // Bisherigen Zeichenbereich merken
      c2dSize old_size = getDrawingAreaSize();
      // Skalierung im Viewport durchfuehren
      vport.scale *= delta;
      space.setViewport(vport);
      // Korrektur des Viewport-Starts mit neuem Zeichenbereich
      vport.start += c2dVector(old_size - getDrawingAreaSize()) / 2.0;
      space.setViewport(vport);
   }

   refresh();
}

void cwDrawView::zoom(double delta, const c2dPoint& center)
{
   if ( vport.scale > 0.01 ) {
      double old_width = space.convPel2Unit(GetWidth());
      double old_height = space.convPel2Unit(GetHeight());
      vport.scale /= 1.5;
      space.setViewport(vport);
      double new_width = space.convPel2Unit(GetWidth());
      double new_height = space.convPel2Unit(GetHeight());
      vport.start -= c2dVector((old_width - new_width) / 2, (old_height - new_height) / 2);
      space.setViewport(vport);
   }
   refresh();
}

static double CalcScale(const c2dSize& disp_size, const c2dSize& box_size)
{
   double scale_x = box_size.cx > 0.0 ? disp_size.cx / box_size.cx : 1.0;
   double scale_y = box_size.cy > 0.0 ? disp_size.cy / box_size.cy : 1.0;
   double scale = min(scale_x, scale_y);
   return is_zero(scale) ? 1.0 : scale;
}

void cwDrawView::zoom(const c2dBox& box, int pixborder)
{
   vport.scale = 1.0; // Erstmal klare Verhaeltnisse schaffen...
   space.setViewport(vport);

   // Staerke des Zwangsrahmens in 1:1.0-Skalierung berechnen
   double border_size = space.convPel2Unit(pixborder);
   // Groesse des Fensters in Weltkoordinaten
   c2dSize display = getDrawingAreaSize() - 2 * c2dSize(border_size, border_size);
   // Skalierung berechnen
   double scale = CalcScale(display, box.getSize());
   // Distanz vom Display-Startpunkt zum 'box'-Startpunkt in Weltkoordinaten
   c2dVector start_rel = (display / scale - box.getSize()) / 2.0;
   // Absoluter Display-Startpunkt in Weltkoordinaten
   c2dPoint start_abs = box.lb - start_rel;

   // Skalierung einschalten, damit Zwangsrahmen berechnet werden kann
   vport.scale = scale;
   space.setViewport(vport);

   // Staerke des Zwangsrahmens in neuer Skalierung berechnen
   border_size = space.convPel2Unit(pixborder);

   // Skalierung einschalten (Zwangsrahmen beruecksichtigen!)
   vport.start = start_abs - c2dVector(border_size, border_size);
   space.setViewport(vport);

   // Und alles neu malen...
   refresh();
}
*/

void cwDrawView::onInit()
{
   setDrawArea();
   zoomToDoc();
}

void cwDrawView::onDraw(void *ctxt)
{
   if ( elems != 0 ) {
      device.assocContext(ctxt);
      device.paintAt(elems, cdPoint());
      device.assocContext(0);
   }
}

void cwDrawView::onUpdate(cEloView * /*from_view*/, cEloElement * /*elem*/, long hint)
{
   if ( hint == 0 ) { // Initiales Update

      cwDrawSpace space(&device);
      cwDrawDocument *doc = (cwDrawDocument*)getDocument();

      space.beginDrawing();

      IPOSITION pos = doc->getStartPosition();
      while ( pos != 0 ) {
         cdObject *obj = doc->getNextObject(pos);
         obj->draw(&space);
      }

      delete elems;
      elems = space.endDrawing();

   }

   refresh();
}

void cwDrawView::onDocumentAdded()
{
   setDrawArea();
   zoomToDoc();
}

//
// Es war einmal...
//
// c2dBox cwDrawView::getDrawingArea() const
// {
//    return c2dBox(c2dPoint(0,0), getDrawingAreaSize());
// }
//
// c2dSize cwDrawView::getDrawingAreaSize() const
// {
//    return c2dSize(0,0); //space.convPel2Unit(1000/*TBD: getWidth()*/), space.convPel2Unit(1000 /*TBD: getHeight()*/));
// }


