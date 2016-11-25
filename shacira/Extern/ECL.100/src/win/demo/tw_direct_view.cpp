// ===========================================================================
// tw_direct_view.cpp                            ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Demonstriert das direkte Zeichnen in einen View ueber den Device-Mapping-
// Mode "mmDirect" sowie die Verwendung von Scrollbalken mit einem View
// dieses Typs.
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//  cBase
//   |
//   +--cwWindow
//       |
//       +--cwView
//           |
//           +--cDirectView
//
// ===========================================================================

#include "win/demo/tw_direct_view.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "win/ew_views.hpp"
#include "win/ew_device.hpp"

#endif /*__INTERFACE__*/




// Lokale Variablen
// ===========================================================================

const int RANGE_FROM = -1256;    // Anzeigebereich (Minimum)
const int RANGE_TO   =  1256;    // Anzeigebereich (Maximum)
const int INC_LINE   =  1;       // Pixel-Inkrement fuer "LINE"-Operationen
const int INC_PAGE   =  128;     // Pixel-Inkrement fuer "PAGE"-Operationen




#ifdef __INTERFACE__

// ===========================================================================
// Definition cDirectView
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cwWindow
//       +--cwView
//           +--cDirectView
//
// ===========================================================================

class cDirectView : public cwView {

public:

   // Konstruktor
   cDirectView();
   // Destruktor
   ~cDirectView();

   // Zoom-Faktor einstellen
   void setZoom(int zoom_factor);


protected:

   // Ueberschriebene Events
   // ======================

   // Wird bei der Initialisierung des Views aufgerufen
   void onInit();
   // Wird aufgerufen, um den Anzeigebereich des Views zu zeichnen
   void onDraw(cwContext *ctxt);
   // Groesse geaendert
   void onSize(int cx, int cy);
   // Wird aufgerufen, wenn eine Aktion an einem Scrollbar ausgeloest wurde
   void onScroll(const cwCmdScroll& cmd);
   // Taste gedrueckt
   void onChar(cwCmdChar& cmd);


private:

   // Zu verwendendes Device (wird mit dem View assoziiert)
   cwDevice device;
   int cur_pos;
   int zoom;

   // (Neu-)zeichnen der Kurve
   void redraw(const cdRect& redraw_area);
   // Auswertung der Tastendruecke fuers Scrollen
   bool scroll(const cwCmdChar& cmd);

};

#endif /*__INTERFACE__*/


// Implementierung cDirectView
// ===========================================================================

cDirectView::cDirectView()
{
   // Nix zu tun...
}

cDirectView::~cDirectView()
{
   // Nix zu tun...
}


void cDirectView::setZoom(int zoom_factor)
{
   if ( zoom_factor != zoom
     && zoom_factor > 0
     && zoom_factor < 20 )
   {
      zoom = zoom_factor;
      setScrollPageSize(barHorz, this->getSize().cx/zoom);
      invalidate();
   }
}


// Ueberschriebene Events
// ======================

void cDirectView::onInit()
{
   cur_pos = 0;
   zoom = 1;

   // Hintergrundfarbe einstellen
   setPresParam(ppBkgndColor, cdColor(64,64,64));

   // Horizontalen Scrollbar einrichten
   setScrollBarInfo(barHorz, 0, RANGE_FROM, RANGE_TO);
   showScrollBar(barHorz);
}

void cDirectView::onDraw(cwContext *ctxt)
{
   // Kontext mit Device assoziieren
   device.bindContext(ctxt);

   // Kurve zeichnen
   redraw(ctxt->getRedrawArea());

   // WICHTIG! Assoziation wieder rueckgaengig machen
   device.bindContext(0);
}

void cDirectView::onSize(int cx, int /*cy*/)
{
   // Bei Groessenaenderung des Fensters die Groesse
   // der Scroll-Box proportional mit aendern
   setScrollPageSize(barHorz, cx/zoom);
}

void cDirectView::onScroll(const cwCmdScroll& cmd)
{
   int inc = 0;

   if ( cmd.fromHorzScrollBar() ) {

      // Abhaengig von der Scrollbar-Aktion ein Bewegungs-
      // Inkrement berechnen

      switch ( cmd.getAction() ) {
      case cwCmdScroll::scrlBoxTracking:   inc = getScrollTrackPos(barHorz) - cur_pos; break;
      case cwCmdScroll::scrlLeft:          inc = RANGE_FROM - cur_pos; break;
      case cwCmdScroll::scrlLeftLine:      inc = -INC_LINE; break;
      case cwCmdScroll::scrlLeftPage:      inc = -INC_PAGE; break;
      case cwCmdScroll::scrlRight:         inc = RANGE_TO - cur_pos; break;
      case cwCmdScroll::scrlRightLine:     inc = INC_LINE; break;
      case cwCmdScroll::scrlRightPage:     inc = INC_PAGE;
      }

      // Dieses Inkrement mit der aktuellen Position verrechnen
      // und auf den Scrollbar anwenden. Neuen aktuellen Wert
      // zuruecklesen.

      setScrollPos(barHorz, cur_pos + inc);
      int new_pos = getScrollPos(barHorz);

      // Hat sich die Position geaendert? Dann muss das Fenster
      // gescrollt werden!

      if ( cur_pos != new_pos ) {
         scrollWindow(cur_pos - new_pos, 0);
         cur_pos = new_pos;
      }
   }
}

void cDirectView::onChar(cwCmdChar& cmd)
{
   // Tastendruecke auf entsprechende cwCmdScroll-Kommandos umleiten

   if ( !scroll(cmd) ) {
      if ( cmd.isKeyDown() && cmd.isVirt() ) {
         switch ( cmd.getVirt() ) {
         case cwCmdChar::vkNumAdd:  setZoom(zoom+1); break;
         case cwCmdChar::vkNumSub:  setZoom(zoom-1); break;
         }
      }
   }

   cwView::onChar(cmd);
}


// (Neu-)Zeichnen der Kurve
// ========================

void cDirectView::redraw(const cdRect& redraw_area)
{
   // Mapping-Mode "mmDirect" einstellen. Jetzt entspricht eine
   // logische Koordinate einer Geraetekoordinaten (d.h. einem Pixel)

   device.setMapMode(cdDevice::mmDirect);

   // Zu zeichnenden Bereich ueber die 'redraw_area' berechnen.
   // Auf diese Weise werden nur genau die Kurvenpunkte berechnet
   // und neu gezeichnet, die eben noch verdeckt waren.

   int x_off   = getScrollPos(barHorz);
   int x_start = redraw_area.getXLeft();
   int x_end   = redraw_area.getXRight();

   int x, y;
   int y_base  = getSize().cy / 2;

   // Gitter zeichnen

   device.setColor(cdColor(cdColor::DarkGray));

   for ( y = 50 ; y < y_base ; y += 50 ) {
      device.moveTo(cdPoint(x_start, y_base + y));
      device.drawLine(cdPoint(x_end, y_base + y));
      device.moveTo(cdPoint(x_start, y_base - y));
      device.drawLine(cdPoint(x_end, y_base - y));
   }

   for ( x = x_start ; x <= x_end ; x++ ) {
      if ( (x+x_off) % (50*zoom) == 0 ) {
         device.moveTo(cdPoint(x, 0));
         device.drawLine(cdPoint(x, getSize().cy - 1));
      }
   }

   // Achse zeichnen

   device.setColor(cdColor(cdColor::Gray));
   device.moveTo(cdPoint(x_start, y_base));
   device.drawLine(cdPoint(x_end, y_base));

   for ( x = x_start ; x <= x_end ; x++ ) {
      if ( (x+x_off) % (10*zoom) == 0 ) {
         device.moveTo(cdPoint(x, y_base-6));
         device.drawLine(cdPoint(x, y_base+6));
      } else if ( (x+x_off) % (5*zoom) == 0 ) {
         device.moveTo(cdPoint(x, y_base-3));
         device.drawLine(cdPoint(x, y_base+4));
      }
   }

   // Beschriftung zeichnen

   device.setBackMix(cdMix(cdMix::Leavealone));
   device.setTextAlign(cdAlign(cdAlign::Center), cdAlign(cdAlign::Top));
   int ts = 100 * zoom;

   for ( x = ((x_start+x_off)/ts - 1) * ts ; x <= ((x_end+x_off)/ts + 1) * ts ; x += ts ) {
      device.moveTo(cdPoint(x - x_off, y_base+8));
      device.drawText(Str(x/double(ts)), -1);
   }

   // Kurve zeichnen

   device.setColor(cdColor(cdColor::Yellow));

   y = y_base - int(sin(double(x_start + x_off)/ts) * 100);
   device.moveTo(cdPoint(x_start, y));

   for ( x = x_start+1 ; x <= x_end ; x++ ) {
      y = y_base - int(sin(double(x + x_off)/ts) * 100);
      device.drawLine(cdPoint(x, y));
   }
}

bool cDirectView::scroll(const cwCmdChar& cmd)
{
   if ( !cmd.isKeyDown() || !cmd.isVirt() )
      return false;

   cwCmdScroll::BAR bar;
   cwCmdScroll::ACTION action;

   switch ( cmd.getVirt() ) {
   case cwCmdChar::vkHome:       bar = cwCmdScroll::barHorz; action = cwCmdScroll::scrlLeft; break;
   case cwCmdChar::vkLeft:       bar = cwCmdScroll::barHorz; action = cwCmdScroll::scrlLeftLine; break;
   case cwCmdChar::vkPageUp:     bar = cwCmdScroll::barHorz; action = cwCmdScroll::scrlLeftPage; break;
   case cwCmdChar::vkEnd:        bar = cwCmdScroll::barHorz; action = cwCmdScroll::scrlRight; break;
   case cwCmdChar::vkRight:      bar = cwCmdScroll::barHorz; action = cwCmdScroll::scrlRightLine; break;
   case cwCmdChar::vkPageDown:   bar = cwCmdScroll::barHorz; action = cwCmdScroll::scrlRightPage; break;
   default:                      return false;
   }

   onScroll(cwCmdScroll(bar, action));
   return true;
}


