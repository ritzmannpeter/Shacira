// ===========================================================================
// ed_space.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdSpace                - Basisklasse fuer Anzeigebereiche
//         |
//         +--cdMemorySpace      - Anzeigebereich mit Speicherfunktion
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>

#include "draw/ed_space.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_geo2d.hpp"
#include "draw/ed_object.hpp"
#include "draw/ed_matrix.hpp"
#include "draw/ed_device.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdSpace
// ---------------------------------------------------------------------------
//
// Definiert ein physikalisches Koordinatensystem (WORLD), das Operationen
// zur Darstellung von grafischen Objekten in phyiskalischen Koordinaten
// bietet. Diese werden ueber eine 3x3-Matrix in ein PAGE-System konvertiert,
// das anschliessend in geraeteabhaengige Koordinaten umgesetzt wird:
//
//   ^                             ^    +----+                 +----------->
//   |               | a b 0 |     |    |    |                 |    +----+
//   |  +-----+      | c d 0 |     |    |    |                 |    |    |
//   |  |     |      | x y 1 |     |    |    |                 |    |    |
//   |  +-----+     ===========>   |    |    |    ==========>  |    |    |
//   |                             |    +----+                 |    |    |
//   +----------->                 +----------->               V    +----+
//
//   WORLD                         PAGE                        LOGICAL
//   Physikalische                 Transformierte              Logische
//   Koordinaten                   Koordinaten                 Koordinaten
//
//   Physikalisch [mm]             Physikalisch [mm]           Logisch [*?]
//   double                        double                      long
//   +x => rechts                  +x => rechts                +x => *?
//   +y => oben                    +y => oben                  +y => *?
//
// Anmerkungen:
//
//  - Die Bedeutung der Koordinaten und die Orientierung der Achsen im
//    LOGICAL-System sind abhaengig vom aktuelle Mapping-Mode (vgl. *?):
//
//                   | +x     | +y     | Einheit
//       ------------+--------+--------+-----------
//        mmDirect   | rechts | unten  | Pixel
//        mmLoMetric | rechts | oben   | 1/10 mm
//        mmHiMetric | rechts | oben   | 1/100 mm
//
//  - Wird keine oder die identische Transformation gesetzt, sind die
//    Koordinatensystem WORLD und PAGE identisch
//
//  - Momentan wird als einzige physikalische Koordinateneinheit nur
//    Millimeter unterstuetzt, was sich zukuenftig aber aendern koennte.
//
//  cBase
//   +--cdSpace
//
// ===========================================================================

class cdMemorySpace;

class __ECL_DLLEXPORT__ cdSpace : public cBase {
   friend class cdMemorySpace;

public:

   // Konstruktor ueber Device
   inline cdSpace(cdDevice *dev) { init(dev); }
   // Copy-Konstruktor
   inline cdSpace(const cdSpace& other) { init(other); }
   // Destruktor
   virtual ~cdSpace();


   // Transformation
   // ==============

   // Transformationmatrix setzen
   cdMatrix setTransform(const cdMatrix& new_tmat);
   // Ruecksetzen der Transformationsmatrix auf Einheitsmatrix
   cdMatrix resetTransform();
   // Transformationmatrix erfragen
   const cdMatrix& getTransform() const;

   // Die folgenden Operationen werden mit der aktuellen
   // Transformationsmatrix verknuepft:

   // Gleichmaessige Skalierung durchfuehren
   void scale(double scale);
   // Unabhaengige Skalierung durchfuehren
   void scale(double scale_x, double scale_y);
   // Translation ueber Koordinatenpaar durchfuehren
   void translate(double dx, double dy);
   // Translation ueber Vektor durchfuehren
   void translate(const c2dVector& new_offset);
   // Rotation ueber Winkel (Bogenmass) durchfuehren
   void rotate(double angle);
   // Rotation ueber sin/cos-Werte des Winkels durchfuehren
   void rotate(double sin_angle, double cos_angle);


   // Koordinatenumwandlung
   // =====================

   // WORLD -> PAGE Transformation von Koordinaten
   inline void convWorldToPage(double& x, double& y)
      { tmat.trans(x, y); }
   // WORLD -> PAGE Transformation eines Punktes
   inline c2dPoint convWorldToPage(const c2dPoint& p)
      { return tmat.trans(p); }
   // WORLD -> PAGE Transformation eines Vektors
   inline c2dVector convWorldToPage(const c2dVector& v)
      { return tmat.trans(v); }


   // Position
   // ========

   // Aktuelle WORLD-Position erfragen
   const c2dPoint& getWorldPos() const
      { return pos; }


   virtual void beginDrawing();
   virtual cdDeviceStore *endDrawing();

   virtual void setColor(cdColor color);
   virtual void setBackColor(cdColor color);
   virtual void setFillColor(cdColor fillcolor);
   virtual void setFillPattern(char *pattern);
   virtual void setLineStyle(cdLineStyle linestyle);
   virtual void setLineWidth(long linewidth);
   virtual void setPattern(cdPattern pattern);
   virtual void setForeMix(cdMix mix);
   virtual void setBackMix(cdMix mix);

   virtual void setTextAlign(cdAlign horiz, cdAlign vert);
   virtual void setTextAngle(const c2dVector& dir);

   // Font erzeugen, auswaehlen und loeschen (mehrere Fonts moeglich!)
   virtual long createFont(const char *facename, int pointsize);
   virtual void selectFont(long font_id);
   virtual void deleteFont(long font_id);

   virtual void newFrame();
   virtual void moveTo(const c2dPoint& p);

   virtual void beginArea(bool boundary = true);
   virtual void endArea();

   virtual void draw(const cdObject* obj);
   virtual void draw(const cdObject& obj);
   virtual void draw(const cdMemorySpace *memory_space);
   virtual void draw(const c2dLine& l);
   virtual void draw(const c2dLineSeg& ls);
   virtual void draw(const c2dCircle& c);
   virtual void draw(const c2dArc& a);
   virtual void draw(const c2dBox& a);
   virtual void draw(const char *txt, int length = -1);

   // Zeichen- und Textgroessen erfragen (in mm)
   double queryAvgCharWidth() const;
   double queryAvgCharHeight() const;
   void queryAvgCharSize(double& width, double& height) const;
   double queryTextWidth(const char *text, int length = -1) const;
   double queryTextHeight(const char *text, int length = -1) const;

   cdDevice *getDevice() const
      { return dev; }


private:
   cdDevice *dev;       // Zugeordnetes Device
   cdMatrix tmat;       // Transformationsmatrix

   c2dPoint pos;        // Aktuelle Position in WORLD-Koordinaten
   bool newPos(const c2dPoint& p);
   void init(cdDevice *dev);
   void init(const cdSpace& other);

   long                    cur_fontid;       // Font
   cdColor                 cur_color;        // Farbe
   cdColor                 cur_backcolor;    // Hintergrundfarbe
   cdColor                 cur_fillcolor;    // Fuellfarbe
   long                    cur_linewidth;    // Linienbreite
   cdLineStyle::LINESTYLE  cur_linestyle;    // Linienstil
   cdPattern::PATTERN      cur_pattern;      // Pattern
   cdMix::MIX              cur_foremix;      // Fordergrund-Mix
   cdMix::MIX              cur_backmix;      // Hintergrund-Mix
   cdAlign::ALIGN          cur_halign;       // Horizontales Alignment
   cdAlign::ALIGN          cur_valign;       // Vertikales Alignment

};

#endif /*__INTERFACE__*/


// Implementierung cdSpace
// ===========================================================================

#define __Trace_Space_Calls__
#if defined __Trace_Space_Calls__ && __ECL_DEBUG__ > 0
   #define TRACESPACE(p) DbgTrcApp p
#else
   #define TRACESPACE(p)
#endif

const c2dPoint OuterSpace = c2dPoint(1e42, 1e42);

void cdSpace::init(cdDevice *dev)
{
   pos = OuterSpace;
   cdSpace::dev = dev;

   cur_fontid = -1;
   cur_linewidth = -1;
   cur_linestyle = (cdLineStyle::LINESTYLE)-1;
   cur_pattern = (cdPattern::PATTERN)-1;
   cur_foremix = cur_backmix = (cdMix::MIX)-1;
   cur_halign = cur_valign = (cdAlign::ALIGN)-1;
}

void cdSpace::init(const cdSpace& other)
{
   tmat = other.tmat;
   pos = other.pos;
   dev = other.dev;

   cur_fontid = -1;
   cur_linewidth = -1;
   cur_linestyle = (cdLineStyle::LINESTYLE)-1;
   cur_pattern = (cdPattern::PATTERN)-1;
   cur_foremix = cur_backmix = (cdMix::MIX)-1;
   cur_halign = cur_valign = (cdAlign::ALIGN)-1;
}

cdSpace::~cdSpace()
{
   // ...
}


// Transformation
// ==============

cdMatrix cdSpace::setTransform(const cdMatrix& new_tmat)
{
   cdMatrix old_tmat = tmat;
   tmat = new_tmat;
   return old_tmat;
}

cdMatrix cdSpace::resetTransform()
{
   cdMatrix old_tmat = tmat;
   tmat.makeIdent();
   return old_tmat;
}

const cdMatrix& cdSpace::getTransform() const
{
   return tmat;
}

void cdSpace::scale(double new_scale)
{
   tmat *= cdMatrixScale(new_scale);
}

void cdSpace::scale(double scale_x, double scale_y)
{
   tmat *= cdMatrixScale(scale_x, scale_y);
}

void cdSpace::translate(double dx, double dy)
{
   tmat *= cdMatrixTransl(dx, dy);
}

void cdSpace::translate(const c2dVector& new_offset)
{
   tmat *= cdMatrixTransl(new_offset);
}

void cdSpace::rotate(double angle)
{
   tmat *= cdMatrixRot(angle);
}

void cdSpace::rotate(double sin_angle, double cos_angle)
{
   tmat *= cdMatrixRot(sin_angle, cos_angle);
}


void cdSpace::beginDrawing()
{
   TRACESPACE(("cdSpace::beginDrawing()"));
   pos = OuterSpace;

   cur_fontid = -1;
   cur_linewidth = -1;
   cur_color = cdColor();
   cur_backcolor = cdColor();
   cur_fillcolor = cdColor();
   cur_linestyle = (cdLineStyle::LINESTYLE)-1;
   cur_pattern = (cdPattern::PATTERN)-1;
   cur_foremix = cur_backmix = (cdMix::MIX)-1;
   cur_halign = cur_valign = (cdAlign::ALIGN)-1;
}

cdDeviceStore * cdSpace::endDrawing()
{
   TRACESPACE(("cdSpace::endDrawing()"));

   cur_fontid = -1;
   cur_linewidth = -1;
   cur_color = cdColor();
   cur_backcolor = cdColor();
   cur_fillcolor = cdColor();
   cur_linestyle = (cdLineStyle::LINESTYLE)-1;
   cur_pattern = (cdPattern::PATTERN)-1;
   cur_foremix = cur_backmix = (cdMix::MIX)-1;
   cur_halign = cur_valign = (cdAlign::ALIGN)-1;

   return 0;
}

void cdSpace::setColor(cdColor color)
{
   if ( cur_color != color ) {
      TRACESPACE(("cdSpace::setColor(%d)", color.getOsVal()));
      dev->setColor(color.getOsVal());
      cur_color = color;
   }
}

void cdSpace::setBackColor(cdColor color)
{
   if ( cur_backcolor != color ) {
      TRACESPACE(("cdSpace::setBackColor(%d)", color.getOsVal()));
      dev->setBackColor(color.getOsVal());
      cur_backcolor = color;
   }
}

void cdSpace::setFillColor(cdColor fillcolor)
{
   if ( cur_fillcolor != fillcolor ) {
      TRACESPACE(("cdSpace::setFillColor(%d)", fillcolor.getOsVal()));
      dev->setFillColor(fillcolor.getOsVal());
      cur_fillcolor = fillcolor;
   }
}

void cdSpace::setFillPattern(char *pattern)
{
   TRACESPACE(("cdSpace::setFillPattern()"));
   dev->setFillPattern(pattern);
}

void cdSpace::setLineStyle(cdLineStyle linestyle)
{
   if ( cur_linestyle != linestyle ) {
      TRACESPACE(("cdSpace::setLineStyle(%d)", linestyle.getOsVal()));
      dev->setLineStyle(linestyle.getOsVal());
      cur_linestyle = linestyle;
   }
}

void cdSpace::setLineWidth(long linewidth)
{
   if ( cur_linewidth != linewidth ) {
      TRACESPACE(("cdSpace::setLineWidth(%d)", linewidth));
      dev->setLineWidth(linewidth);
      cur_linewidth = linewidth;
   }
}

void cdSpace::setPattern(cdPattern pattern)
{
   if ( cur_pattern != pattern ) {
      TRACESPACE(("cdSpace::setPattern(%d)", pattern.getOsVal()));
      dev->setPattern(pattern.getOsVal());
      cur_pattern = pattern;
   }
}

void cdSpace::setForeMix(cdMix mix)
{
   if ( cur_foremix != mix ) {
      TRACESPACE(("cdSpace::setForeMix(%d)", mix.getOsVal()));
      dev->setForeMix(mix.getOsVal());
      cur_foremix = mix;
   }
}

void cdSpace::setBackMix(cdMix mix)
{
   if ( cur_backmix != mix ) {
      TRACESPACE(("cdSpace::setBackMix(%d)", mix.getOsVal()));
      dev->setBackMix(mix.getOsVal());
      cur_backmix = mix;
   }
}

void cdSpace::setTextAlign(cdAlign horiz, cdAlign vert)
{
   if ( cur_halign != horiz || cur_valign != vert ) {
      TRACESPACE(("cdSpace::setTextAlign(%d,%d)", horiz.getOsVal(), vert.getOsVal()));
      dev->setTextAlign(horiz.getOsVal(), vert.getOsVal());
      cur_halign = horiz;
      cur_valign = vert;
   }
}

void cdSpace::setTextAngle(const c2dVector& dir)
{
   TRACESPACE(("cdSpace::setTextAngle(%g,%g)", dir.x, dir.y));
   c2dVector unit_dir = dir.getUnitV();
   // TBF: Momentan nur 90 Grad Schritte moeglich!!!!
   dev->setTextAngle(long(unit_dir.x), long(unit_dir.y));
}

long cdSpace::createFont(const char *facename, int pointsize)
{
   TRACESPACE(("cdSpace::createFont(%s,%d)", facename, pointsize));
   return dev->createFont(facename, pointsize);
}

void cdSpace::selectFont(long font_id)
{
   if ( cur_fontid != font_id ) {
      TRACESPACE(("cdSpace::selectFont(%d)", font_id));
      dev->selectFont(font_id);
      cur_fontid = font_id;
   }
}

void cdSpace::deleteFont(long font_id)
{
   TRACESPACE(("cdSpace::deleteFont(%d)", font_id));
   dev->deleteFont(font_id);
}

void cdSpace::beginArea(bool boundary)
{
   TRACESPACE(("cdSpace::beginArea(%d)", boundary));
   pos = OuterSpace;
   dev->beginArea(boundary);
}

void cdSpace::endArea()
{
   TRACESPACE(("cdSpace::endArea()"));
   dev->endArea();
}

void cdSpace::newFrame()
{
   TRACESPACE(("cdSpace::newFrame()"));
   dev->newFrame();

   cur_fontid = -1;
   cur_linewidth = -1;
   cur_color = cdColor();
   cur_backcolor = cdColor();
   cur_fillcolor = cdColor();
   cur_linestyle = (cdLineStyle::LINESTYLE)-1;
   cur_pattern = (cdPattern::PATTERN)-1;
   cur_foremix = cur_backmix = (cdMix::MIX)-1;
   cur_halign = cur_valign = (cdAlign::ALIGN)-1;
}

void cdSpace::moveTo(const c2dPoint& p)
{
   if ( newPos(p) ) {
      TRACESPACE(("cdSpace::moveTo(%g,%g)", p.x, p.y));
      c2dPoint p1 = convWorldToPage(p);
      dev->moveTo(dev->convPageToLog(p1));
   }
}

bool cdSpace::newPos(const c2dPoint& p)
{
   if ( pos != p ) {
      pos = p;
      return true;
   }

   return false;
}

void cdSpace::draw(const cdObject* obj)
{
   if ( obj )
      draw(*obj);
}

void cdSpace::draw(const cdObject& obj)
{
   TRACESPACE(("cdSpace::draw(cdObject())"));

   //?? cdMatrix old = getTransform();
   //?? translate(-pos);
   //?? pos = OuterSpace;
   //?? moveTo(c2dPoint(0,0));
   obj.draw(this);
   //?? setTransform(old);
   //?? pos = OuterSpace;
}

void cdSpace::draw(const cdMemorySpace *memory_space)
{
   TRACESPACE(("cdSpace::draw(cdMemorySpace())"));

   if ( memory_space ) {
      // Einspielen des Inhalts von memory_space an der
      // aktuellen Cursorposition
      memory_space->replayAt(this, pos);
      pos = OuterSpace;
   }
}

void cdSpace::draw(const c2dLine& l)
{
   // Die aktuelle Position 'pos' wird weder benutzt noch veraendert!
   // Deshalb kein Aufruf von cdSpace-Methoden wie moveTo oder newPos!

   c2dPoint p1, q1;

   TRACESPACE(("cdSpace::draw(c2dLine(%g,%g,%g))", l.a, l.b, l.c));

   if ( is_zero(l.getDirV().x) ) {
      p1 = convWorldToPage(l.getPointFromY(-5000));
      q1 = convWorldToPage(l.getPointFromY(5000));
   } else {
      p1 = convWorldToPage(l.getPointFromX(-5000));
      q1 = convWorldToPage(l.getPointFromX(5000));
   }

   dev->moveTo(dev->convPageToLog(p1));
   dev->drawLine(dev->convPageToLog(q1));
}

void cdSpace::draw(const c2dLineSeg& ls)
{
   moveTo(ls.s);
   TRACESPACE(("cdSpace::draw(c2dLineSeg(s(%g,%g), e(%g,%g)))", ls.s.x, ls.s.y, ls.e.x, ls.e.y));

   c2dPoint e1 = convWorldToPage(ls.e);
   dev->drawLine(dev->convPageToLog(e1));

   newPos(ls.e);
}

void cdSpace::draw(const c2dCircle& c)
{
   moveTo(c.m);
   TRACESPACE(("cdSpace::draw(c2dCircle(m(%g,%g), %g))", c.m.x, c.m.y, c.r));

   c2dPoint top_lft = convWorldToPage(c.m + c2dVector(-c.r, c.r));
   c2dPoint top_rgt = convWorldToPage(c.m + c2dVector( c.r, c.r));
   c2dPoint bot_lft = convWorldToPage(c.m + c2dVector(-c.r,-c.r));
   c2dPoint bot_rgt = convWorldToPage(c.m + c2dVector( c.r,-c.r));

   dev->setRect(dev->convPageToLog(bot_lft), dev->convPageToLog(top_rgt));
   dev->setXRect(dev->convPageToLog(bot_rgt), dev->convPageToLog(top_lft));
   dev->drawEllipse();
}

void cdSpace::draw(const c2dArc& a)
{
   moveTo(a.s);
   TRACESPACE(("cdSpace::draw(c2dArc(s(%g,%g), e(%g,%g), m(%g,%g)))", a.s.x, a.s.y, a.e.x, a.e.y, a.m.x, a.m.y));

   double r = a.getRadius();
   c2dPoint top_lft = convWorldToPage(a.m + c2dVector(-r, r));
   c2dPoint top_rgt = convWorldToPage(a.m + c2dVector( r, r));
   c2dPoint bot_lft = convWorldToPage(a.m + c2dVector(-r,-r));
   c2dPoint bot_rgt = convWorldToPage(a.m + c2dVector( r,-r));
   c2dPoint e1 = convWorldToPage(a.e);

   dev->setRect(dev->convPageToLog(bot_lft), dev->convPageToLog(top_rgt));
   dev->setXRect(dev->convPageToLog(bot_rgt), dev->convPageToLog(top_lft));

   if ( a.dir < 0 ) {
      dev->drawArcCW(dev->convPageToLog(e1));
   } else {
      dev->drawArcCCW(dev->convPageToLog(e1));
   }

   newPos(a.e);
}

void cdSpace::draw(const c2dBox& b)
{
   moveTo(b.lb);
   TRACESPACE(("cdSpace::draw(c2dBox(lb(%g,%g), rt(%g,%g)))", b.lb.x, b.lb.y, b.rt.x, b.rt.y));

   c2dPoint top_lft = convWorldToPage(b.getTopLeft());
   c2dPoint top_rgt = convWorldToPage(b.getTopRight());
   c2dPoint bot_lft = convWorldToPage(b.getBottomLeft());
   c2dPoint bot_rgt = convWorldToPage(b.getBottomRight());

   dev->setRect(dev->convPageToLog(bot_lft), dev->convPageToLog(top_rgt));
   dev->setXRect(dev->convPageToLog(bot_rgt), dev->convPageToLog(top_lft));
   dev->drawRect();
}

void cdSpace::draw(const char *text, int length)
{
   if ( text != 0 && length != 0 ) {
      #ifdef __Trace_Space_Calls__
         char buf[80]; strxcpy(buf, text, sizeof buf);
         if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
         TRACESPACE(("cdSpace::draw(text(pos(%g,%g), '%s')", pos.x, pos.y, buf));
      #endif

      dev->drawText(text, length);
      pos = OuterSpace;
   }
}

double cdSpace::queryAvgCharWidth() const
{
   TRACESPACE(("cdSpace::queryAvgCharWidth()"));
   double width, height;
   queryAvgCharSize(width, height);
   return width;
}

double cdSpace::queryAvgCharHeight() const
{
   TRACESPACE(("cdSpace::queryAvgCharHeight()"));
   double width, height;
   queryAvgCharSize(width, height);
   return height;
}

void cdSpace::queryAvgCharSize(double& width, double& height) const
{
   TRACESPACE(("cdSpace::queryAvgCharSize()"));

   long cx, cy;
   dev->queryAvgCharSize(cx, cy);
   cdVector v_device(cx, cy);
   c2dVector v_page = dev->convLogToPage(v_device);
   width = v_page.x;
   height = v_page.y;
}

double cdSpace::queryTextWidth(const char *text, int length) const
{
   if ( text != 0 && length != 0 ) {
      #ifdef __Trace_Space_Calls__
         char buf[80]; strxcpy(buf, text, sizeof buf);
         if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
         TRACESPACE(("cdSpace::queryTextWidth(%s,%d)", buf, length));
      #endif

      cdVector v_device(dev->queryTextWidth(text, length), 0);
      c2dVector v_page = dev->convLogToPage(v_device);
      return v_page.x;
   } else {
      return 0.0;
   }
}

double cdSpace::queryTextHeight(const char *text, int length) const
{
   if ( text != 0 && length != 0 ) {
      #ifdef __Trace_Space_Calls__
         char buf[80]; strxcpy(buf, text, sizeof buf);
         if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
         TRACESPACE(("cdSpace::queryTextHeight(%s,%d)", buf, length));
      #endif

      cdVector v_device(0, dev->queryTextHeight(text, length));
      c2dVector v_page = dev->convLogToPage(v_device);
      return v_page.y;
   } else {
      return 0.0;
   }
}


/*
// Umwandlung von Koordinaten
// ==========================

cdPoint cdSpace::conv(const c2dPoint& phys)
{
   c2dPoint p = t(phys);
   return cdPoint(p2l(p.x), p2l(p.y));
}

cdSize cdSpace::conv(const c2dSize& phys)
{
   return cdSize(p2l(phys.cx * vp.scale), p2l(phys.cy * vp.scale));
}

cdRect cdSpace::conv(const c2dBox& phys)
{
   return cdRect(conv(phys.lb), conv(phys.getSize()));
}

c2dPoint cdSpace::conv(const cdPoint& *log*)
{
   __ECL_ASSERT1__(0); // TBD: ........
   return c2dPoint();
}

c2dSize cdSpace::conv(const cdSize& log)
{
   return c2dSize(l2p(log.cx), l2p(log.cy));
}

c2dBox cdSpace::conv(const cdRect& log)
{
   return c2dBox(conv(log.lb), conv(log.rt));
}
*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMemorySpace
// ---------------------------------------------------------------------------
//
//  cBase
//   +--cdSpace
//       +--cdMemorySpace
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMemorySpace : public cdSpace {
   friend class cdSpace;

public:
   inline cdMemorySpace() : cdSpace(0) { init(); }
   ~cdMemorySpace();

   cdMatrix setTransform(const cdMatrix& new_tmat);
   cdMatrix resetTransform();
   void scale(double scale);
   void scale(double scale_x, double scale_y);
   void translate(double dx, double dy);
   void translate(const c2dVector& new_offset);
   void rotate(double angle);
   void rotate(double sin_angle, double cos_angle);

   void beginDrawing();
   cdDeviceStore *endDrawing();

   void setColor(cdColor color);
   void setBackColor(cdColor color);
   void setFillColor(cdColor fillcolor);
   void setFillPattern(char *pattern);
   void setLineStyle(cdLineStyle linestyle);
   void setLineWidth(long linewidth);
   void setPattern(cdPattern pattern);
   void setForeMix(cdMix mix);
   void setBackMix(cdMix mix);

   void setTextAlign(cdAlign horiz, cdAlign vert);
   void setTextAngle(const c2dVector& dir);

   void selectFont(long font_id);
   void deleteFont(long font_id);

   void moveTo(const c2dPoint& p);

   void beginArea(bool boundary = true);
   void endArea();

   void draw(const c2dLine& l);
   void draw(const c2dLineSeg& ls);
   void draw(const c2dCircle& c);
   void draw(const c2dArc& a);
   void draw(const c2dBox& a);
   void draw(const char *txt, int length = -1);
   void draw(cdObject*obj)
      { cdSpace::draw(obj); }

private:
   cdSpaceStore *cur_storage;
   cdSpaceStore::ELEM *newElem() const
      { return cur_storage->newElem(); }

   void init();
   void replayAt(cdSpace *space, const c2dPoint& pos) const;

   // Konvertierung wird nicht benoetigt fuer Memory-Spaces
   virtual long onConvPhys2Log(double /*mm*/) const
      { return 0; }
   virtual double onConvLog2Phys(long /*w*/) const
      { return 0; }

   // Folgende Funktion deaktiviert, da sinnlos
   void draw(const cdMemorySpace *)
      { }

};

#endif /*__INTERFACE__*/


// Implementierung cdMemorySpace
// ===========================================================================

void cdMemorySpace::init()
{
   // Zwangsweise wird beginDrawing aufgerufen. Fuer den Anwender von
   // cdMemorySpace hat dies die Konsequenz, dass er den Aufruf nicht
   // selbst machen muss (aber durchaus machen kann, was die gleichen
   // Auswirkungen hat...)
   cur_storage = NULL;
   beginDrawing();
}

cdMemorySpace::~cdMemorySpace()
{
   delete cur_storage;
}

cdMatrix cdMemorySpace::setTransform(const cdMatrix& new_tmat)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformSet;
      if ( (elem->tmat = new0 cdMatrix) != NULL ) {
         elem->flags = cdSpaceStore::efFreeTMat;
         *elem->tmat = new_tmat;
      } else {
         elem->cmd = cdSpaceStore::ecNop;
         DbgError("cdMemorySpace: Alloc tmat failed");
      }
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   return cdSpace::setTransform(new_tmat);
}

cdMatrix cdMemorySpace::resetTransform()
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformReset;
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   return cdSpace::resetTransform();
}

void cdMemorySpace::scale(double scale)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformScale;
      elem->x1 = scale;
      elem->y1 = scale;
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   cdSpace::scale(scale);
}

void cdMemorySpace::scale(double scale_x, double scale_y)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformScale;
      elem->x1 = scale_x;
      elem->y1 = scale_y;
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   cdSpace::scale(scale_x, scale_y);
}

void cdMemorySpace::translate(double dx, double dy)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformTransl;
      elem->x1 = dx;
      elem->y1 = dy;
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   cdSpace::translate(dx, dy);
}

void cdMemorySpace::translate(const c2dVector& new_offset)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformTransl;
      elem->x1 = new_offset.x;
      elem->y1 = new_offset.y;
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   cdSpace::translate(new_offset);
}

void cdMemorySpace::rotate(double angle)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformRotate;
      elem->x1 = sin(angle);
      elem->y1 = cos(angle);
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   cdSpace::rotate(angle);
}

void cdMemorySpace::rotate(double sin_angle, double cos_angle)
{
   #ifdef __Save_Transform_In_MemSpace__
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecTransformRotate;
      elem->x1 = sin_angle;
      elem->y1 = cos_angle;
   #endif

   // Original aufrufen, damit Trafo-Matrix gueltig
   cdSpace::rotate(sin_angle, cos_angle);
}

void cdMemorySpace::beginDrawing()
{
   cdSpace::beginDrawing();
   delete cur_storage;
   cur_storage = new0 cdSpaceStore();
}

cdDeviceStore * cdMemorySpace::endDrawing()
{
   cdSpace::endDrawing();
   return 0;
}

void cdMemorySpace::replayAt(cdSpace *space, const c2dPoint& pos) const
{
   c2dPoint draw_pos = pos;

   if ( cur_storage == NULL || space == NULL )
      return;

   cdSpaceStore::ELEM *elem = cur_storage->firstElem();

   while ( elem ) {

      bool dont_increm = false;

      switch ( elem->cmd ) {

       case cdSpaceStore::ecLast:
         elem = NULL; dont_increm = true; break;
       case cdSpaceStore::ecNext:
         elem = elem->next; dont_increm = true; break;

       case cdSpaceStore::ecTransformSet:
         space->setTransform(*elem->tmat); break;
       case cdSpaceStore::ecTransformReset:
         space->resetTransform(); break;
       case cdSpaceStore::ecTransformScale:
         space->scale(elem->x1, elem->y1); break;
       case cdSpaceStore::ecTransformTransl:
         space->translate(elem->x1, elem->y1); break;
       case cdSpaceStore::ecTransformRotate:
         space->rotate(elem->x1, elem->y1); break;

       case cdSpaceStore::ecSetColor:
         space->setColor(cdColor::fromOsVal(elem->col)); break;
       case cdSpaceStore::ecSetBackColor:
         space->setBackColor(cdColor::fromOsVal(elem->col)); break;
       case cdSpaceStore::ecSetFillColor:
         space->setFillColor(cdColor::fromOsVal(elem->col)); break;
       case cdSpaceStore::ecSetFillPattern:
         space->setFillPattern(elem->text); break;
       case cdSpaceStore::ecSetLineStyle:
         space->setLineStyle(elem->ls); break;
       case cdSpaceStore::ecSetLineWidth:
         space->setLineWidth(elem->val1); break;
       case cdSpaceStore::ecSetPattern:
         space->setPattern(elem->pat); break;
       case cdSpaceStore::ecSetForeMix:
         space->setForeMix(elem->mix); break;
       case cdSpaceStore::ecSetBackMix:
         space->setBackMix(elem->mix); break;

       case cdSpaceStore::ecSetTextAlign:
         space->setTextAlign(elem->align1, elem->align2); break;
       case cdSpaceStore::ecSetTextAngle:
         space->setTextAngle(c2dVector(elem->x1, elem->y1)); break;

       case cdSpaceStore::ecSelectFont:
         space->selectFont(elem->val1); break;
       case cdSpaceStore::ecDeleteFont:
         space->deleteFont(elem->val1); break;

       case cdSpaceStore::ecMoveTo:
         space->moveTo(draw_pos + c2dPoint(elem->x1, elem->y1)); break;
       case cdSpaceStore::ecBeginArea:
         space->beginArea(!!elem->val1); break;
       case cdSpaceStore::ecEndArea:
         space->endArea(); break;

       case cdSpaceStore::ecDrawLine:
         space->draw(c2dLine(elem->x1, elem->y1, elem->x2)); break;
       case cdSpaceStore::ecDrawLineSeg:
         space->draw(c2dLineSeg(draw_pos + c2dPoint(elem->x1, elem->y1),
                                draw_pos + c2dPoint(elem->x2, elem->y2))); break;
       case cdSpaceStore::ecDrawCircle:
         space->draw(c2dCircle(draw_pos + c2dPoint(elem->x1, elem->y1), elem->x2)); break;
       case cdSpaceStore::ecDrawArc:
         space->draw(c2dArc(draw_pos + c2dPoint(elem->dbl[0], elem->dbl[1]),
                            draw_pos + c2dPoint(elem->dbl[2], elem->dbl[3]),
                            draw_pos + c2dPoint(elem->x2, elem->y2),
                            (elem->flags & cdSpaceStore::efArcCW) ? -1 : 1)); break;
       case cdSpaceStore::ecDrawBox:
         space->draw(c2dBox(draw_pos + c2dPoint(elem->x1, elem->y1),
                            draw_pos + c2dPoint(elem->x2, elem->y2))); break;
       case cdSpaceStore::ecDrawText:
         space->draw(elem->text, elem->val2); break;

      }

      if ( !dont_increm )
         elem++;

   }
}

void cdMemorySpace::setColor(cdColor color)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetColor;
   elem->col = color.getOsVal();
}

void cdMemorySpace::setBackColor(cdColor color)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetBackColor;
   elem->col = color.getOsVal();
}

void cdMemorySpace::setFillColor(cdColor fillcolor)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetFillColor;
   elem->col = fillcolor.getOsVal();
}

void cdMemorySpace::setFillPattern(char *pattern)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetFillPattern;
   if ( (elem->text = new0 (char[8])) != NULL ) {
      elem->flags = cdSpaceStore::efFreeText;
      memcpy(elem->text, pattern, 8);
      elem->val2 = 8;
   } else {
      elem->cmd = cdSpaceStore::ecNop;
      DbgError("cdMemorySpace: Alloc pattern failed");
   }
}

void cdMemorySpace::setLineStyle(cdLineStyle linestyle)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetLineStyle;
   elem->ls = linestyle;
}

void cdMemorySpace::setLineWidth(long linewidth)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetLineWidth;
   elem->val1 = linewidth;
}

void cdMemorySpace::setPattern(cdPattern pattern)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetPattern;
   elem->pat = pattern;
}

void cdMemorySpace::setForeMix(cdMix mix)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetForeMix;
   elem->mix = mix;
}

void cdMemorySpace::setBackMix(cdMix mix)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetBackMix;
   elem->mix = mix;
}

void cdMemorySpace::setTextAlign(cdAlign horiz, cdAlign vert)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetTextAlign;
   elem->align1 = horiz;
   elem->align2 = vert;
}

void cdMemorySpace::setTextAngle(const c2dVector& dir)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSetTextAngle;
   elem->x1 = dir.x;
   elem->y1 = dir.y;
}

void cdMemorySpace::selectFont(long font_id)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecSelectFont;
   elem->val1 = font_id;
}

void cdMemorySpace::deleteFont(long font_id)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecDeleteFont;
   elem->val1 = font_id;
}

void cdMemorySpace::beginArea(bool boundary)
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecBeginArea;
   elem->val1 = boundary;
}

void cdMemorySpace::endArea()
{
   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecEndArea;
}

void cdMemorySpace::moveTo(const c2dPoint& p)
{
   c2dPoint p0 = convWorldToPage(p);

   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecMoveTo;
   elem->x1 = p0.x;
   elem->y1 = p0.y;
}

void cdMemorySpace::draw(const c2dLine& l)
{
   c2dPoint p, q;

   if ( is_zero(l.getDirV().x) ) {
      p = l.getPointFromY(-5000);
      q = l.getPointFromY(5000);
   } else {
      p = l.getPointFromX(-5000);
      q = l.getPointFromX(5000);
   }

   p = convWorldToPage(p);
   q = convWorldToPage(q);

   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecDrawLineSeg;
   elem->x1 = p.x;
   elem->y1 = p.y;
   elem->x2 = q.x;
   elem->y2 = q.y;
}

void cdMemorySpace::draw(const c2dLineSeg& ls)
{
   c2dPoint s = convWorldToPage(ls.s);
   c2dPoint e = convWorldToPage(ls.e);

   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecDrawLineSeg;
   elem->x1 = s.x;
   elem->y1 = s.y;
   elem->x2 = e.x;
   elem->y2 = e.y;
}

void cdMemorySpace::draw(const c2dCircle& c)
{
   c2dPoint m = convWorldToPage(c.m);
   c2dPoint n = convWorldToPage(c2dPoint(0,0));
   c2dPoint v = convWorldToPage(c2dPoint(c.r,0));

   // TBD: Transformierten Kreis als Ellipse speichern!!!
   // TBD: Dazu c2dEllipse anlegen!!!

   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecDrawCircle;
   elem->x1 = m.x;
   elem->y1 = m.y;
   elem->x2 = (v - n).getLength();
}

void cdMemorySpace::draw(const c2dArc& a)
{
   c2dPoint m = convWorldToPage(a.m);
   c2dPoint s = convWorldToPage(a.s);
   c2dPoint e = convWorldToPage(a.e);

   // TBD: Transformierten Kreisbogen als Ellipsenbogen speichern!!!
   // TBD: Dazu c2dEliArc anlegen!!!

   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecDrawArc;
   elem->x2 = m.x;
   elem->y2 = m.y;

   if ( (elem->dbl = new0 (double[4])) != NULL ) {
      elem->flags = cdSpaceStore::efFreeDbl;
      if ( a.dir < 0 ) elem->flags |= cdSpaceStore::efArcCW;
      #ifdef __ECL_OS2__
         elem->dbl[0] = dir < 0 ? s.x : e.x;
         elem->dbl[1] = dir < 0 ? s.y : e.y;
         elem->dbl[2] = dir < 0 ? e.x : s.x;
         elem->dbl[3] = dir < 0 ? e.y : s.y;
      #else
         elem->dbl[0] = s.x;
         elem->dbl[1] = s.y;
         elem->dbl[2] = e.x;
         elem->dbl[3] = e.y;
      #endif
   } else {
      elem->cmd = cdSpaceStore::ecNop;
      DbgError("cdMemorySpace: Alloc double array failed");
   }
}

void cdMemorySpace::draw(const c2dBox& b)
{
   c2dPoint lb = convWorldToPage(b.lb);
   c2dPoint rt = convWorldToPage(b.rt);

   cdSpaceStore::ELEM *elem = newElem();
   elem->cmd = cdSpaceStore::ecDrawBox;
   elem->x1 = lb.x;
   elem->y1 = lb.y;
   elem->x2 = rt.x;
   elem->y2 = rt.y;
}

void cdMemorySpace::draw(const char *txt, int length)
{
   if ( txt != NULL ) {
      cdSpaceStore::ELEM *elem = newElem();
      elem->cmd = cdSpaceStore::ecDrawText;
      if ( (elem->text = new0 (char[strlen(txt)+1])) != NULL ) {
         elem->flags = cdSpaceStore::efFreeText;
         strcpy(elem->text, txt);
         elem->val2 = length;
      } else {
         elem->cmd = cdSpaceStore::ecNop;
         DbgError("cdMemorySpace: Alloc text failed");
      }
   }
}


