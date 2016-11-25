
// c2dArc::getBBox FEHLERHAFT! UEBERPRUEFEN!

// ===========================================================================
// eb_geo2d.cpp                                  ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    c2dVector               - Operationen auf Vektoren im 2D-Raum.
//
//    c2dPoint                - Operationen auf Punkten im 2D-Raum.
//
//    c2dSize
//
//    c2dBox                  - Operationen auf achsparallelen Rechtecken
//                              im 2D-Raum.
//
//    c2dLineSeg              - Operationen auf Geradensegmenten im 2D-Raum.
//
//    c2dLine                 - Operationen auf Geraden im 2D-Raum.
//
//    c2dArc                  - Operationen auf Kreisboegen im 2D-Raum.
//
//    c2dCircle               - Operationen auf Kreisen im 2D-Raum.
//
// Ausserdem werden folgende globalen Funktionen zur Verfuegung gestellt:
//
//    C2dIntersect            - Schnittpunktberechnung (Gerade, Kreis, usw.)
//
//    C2dAngleDiffCW,CCW      - Berechnung der Winkeldifferenz
//
// ===========================================================================

#include "base/eb_geo2d.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_array.hpp"
#include "base/eb_math.hpp"

#endif /*__INTERFACE__*/




// ===========================================================================
// Wichtige globale Funktionen
// ===========================================================================

// Winkeldifferenz
// ---------------

GLOBAL double __ECL_DLLEXPORT__ C2dAngleDiffCW(double s, double e)
{
   // Drehrichtung IM Uhrzeigersinn, Wertebereich 0 <= result < 360

   if ( s < e ) {
      return rad(360) - e + s;
   } else {
      return s - e;
   }
}

GLOBAL double __ECL_DLLEXPORT__ C2dAngleDiffCCW(double s, double e)
{
   // Drehrichtung GEGEN DEN Uhrzeigersinn, Wertebereich 0 <= result < 360

   if ( s > e ) {
      return rad(360) - s + e;
   } else {
      return e - s;
   }
}

GLOBAL double __ECL_DLLEXPORT__ C2dAngleDiff(double s, double e, int dir)
{
   // Drehrichtung in Richtung 'dir' (<0 = CCW, >0 = CW)

   if ( dir < 0 ) {
      return C2dAngleDiffCW(s, e);
   } else {
      return C2dAngleDiffCCW(s, e);
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dVector
// ---------------------------------------------------------------------------
//
//  c2dVector
//
// ===========================================================================

class c2dPoint;
class c2dSize;

class __ECL_DLLEXPORT__ c2dVector {

public:
   double x, y;

   c2dVector()
      { x = y = 0.0; }
   c2dVector(double x, double y)
      { c2dVector::x = x;
        c2dVector::y = y; }
   c2dVector(const c2dVector& v)
      { x = v.x;
        y = v.y; }

   // Konstruktion von Vektoren aus spaeter definierten Geometrie-Klassen
   c2dVector(const c2dSize& p);
   c2dVector(const c2dPoint& p);

   // Addition/Subtraktion (c2dVector x c2dVector) => c2dVector
   friend c2dVector operator+(const c2dVector& a, const c2dVector& b)
      { return c2dVector( a.x + b.x, a.y + b.y ); }
   friend c2dVector operator-(const c2dVector& a, const c2dVector& b)
      { return c2dVector( a.x - b.x, a.y - b.y ); }

   // Skalarprodukt (c2dVector * c2dVector) => double
   friend double  operator*(const c2dVector& a, const c2dVector& b)
      { return a.x*b.x + a.y*b.y; }

   // Multiplikation/Division mit Skalar (c2dVector x double) => c2dVector
   friend c2dVector operator*(const c2dVector& a, double r)
      { return c2dVector(a.x*r, a.y*r); }
   friend c2dVector operator/(const c2dVector& a, double r)
      { return c2dVector(a.x/r, a.y/r); }

   // Multiplikation/Division mit Skalar (double x c2dVector) => c2dVector
   friend c2dVector operator*(double r, const c2dVector& a)
      { return c2dVector(r*a.x, r*a.y); }
   friend c2dVector operator/(double r, const c2dVector& a)
      { return c2dVector(r/a.x, r/a.y); }

   // Vorzeichenaenderung
   friend c2dVector operator-(const c2dVector& a)
      { return c2dVector(-a.x, -a.y); }

   // Vergleich (c2dVector x c2dVector) => int
   friend bool operator==(const c2dVector& a, const c2dVector& b)
      { return is_zero(a.x - b.x) && is_zero(a.y - b.y); }
   friend bool operator!=(const c2dVector& a, const c2dVector& b)
      { return !is_zero(a.x - b.x) || !is_zero(a.y - b.y); }

   // Rotieren um -90 Grad
   void rotate()
      { double tmp = x; x = -y; y = tmp; }

   // Rotieren um beliebigen Winkel (um Ursprung)
   c2dVector rotate(double sin_a, double cos_a)
      { return c2dVector(x * cos_a - y * sin_a, x * sin_a + y * cos_a); }
   c2dVector rotate(double alpha)
      { return rotate(sin(alpha), cos(alpha)); }

   // Laenge des Vektors
   double getLengthSqr() const
      { return x*x + y*y; }
   double getLength() const
      { return sqrt(getLengthSqr()); }

   // Einheitsvektor |v0| = 1
   c2dVector getUnitV() const;

   // Normvektor n senkrecht auf v
   c2dVector getNormV() const
      { return c2dVector(-y, x); }
   c2dVector getNormUnitV() const
      { return getNormV().getUnitV(); }

   // Winkel (Bogenmass) zwischen zwei Vektoren
   double getAngle(const c2dVector& v) const;

};

#endif /*__INTERFACE__*/


// Implementierung c2dVector
// ===========================================================================

c2dVector::c2dVector(const c2dSize& s)
{
   x = s.cx; y = s.cy;
}

c2dVector::c2dVector(const c2dPoint& p)
{
   x = p.x; y = p.y;
}

c2dVector c2dVector::getUnitV() const
{
   double len = getLength();
   if ( is_zero(len) )
      return c2dVector(0.0, 0.0);
   return c2dVector(x/len, y/len);
}

static double CalcAngle(const c2dVector& v)
{
   // Liefert den Winkel zur positiven x-Achse
   double angle = 0.0;
   double len_sqr = v.getLengthSqr();

   if ( !is_zero(len_sqr) ) {
      double cos_angle = v.x / sqrt(len_sqr);
      if ( cos_angle < -1.0 ) cos_angle = -1.0;
      if ( cos_angle > 1.0 ) cos_angle = 1.0;
      angle = acos(cos_angle);
      if ( v.y < 0 )
         angle = rad(360.0) - angle;
   }

   return angle;
}

double c2dVector::getAngle(const c2dVector& v) const
{
#ifdef __grmpf__
   double cos_angle = 0.0;
   double len_prod = getLengthSqr() * v.getLengthSqr();

   if ( !is_zero(len_prod) ) {
      cos_angle = (x * v.x + y * v.y) / sqrt(len_prod);
      if ( cos_angle < -1.0 ) cos_angle = -1.0;
      if ( cos_angle > 1.0 ) cos_angle = 1.0;
   }

   return acos(cos_angle);
#else
   return CalcAngle(v) - CalcAngle(*this);
#endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dPoint
// ---------------------------------------------------------------------------
//
// Beschreibt einen Punkt im kartesischen 2D-Raum, gegeben durch ein Koordi-
// natenpaar (x/y).
//
//  c2dPoint
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dPoint {

public:
   double x, y;

   c2dPoint()
      { x = y = 0.0; }
   c2dPoint(double x, double y)
      { c2dPoint::x = x;
        c2dPoint::y = y; }
   c2dPoint(const c2dVector& v)
      { c2dPoint::x = v.x;
        c2dPoint::y = v.y; }
   ~c2dPoint()
      { }

   // Addition/Subtraktion (c2dPoint x c2dVector) => c2dPoint
   friend c2dPoint operator+(const c2dPoint& p, const c2dVector& v)
      { return c2dPoint(p.x + v.x, p.y + v.y); }
   friend c2dPoint operator-(const c2dPoint& p, const c2dVector& v)
      { return c2dPoint(p.x - v.x, p.y - v.y); }

   // Addition/Subtraktion, Zuweisung (c2dPoint x c2dVector) => c2dPoint
   c2dPoint& operator+=(const c2dVector& v)
      { x += v.x, y += v.y;
        return *this; }
   c2dPoint& operator-=(const c2dVector& v)
      { x -= v.x, y -= v.y;
        return *this; }

   // Differenz (c2dPoint - c2dPoint) => c2dVector
   friend c2dVector operator-(const c2dPoint& a, const c2dPoint& b)
      { return c2dVector(a.x - b.x, a.y - b.y); }

   // Rotieren um beliebigen Winkel (um Ursprung)
   c2dPoint rotate(double sin_a, double cos_a)
      { return c2dPoint(x * cos_a - y * sin_a, x * sin_a + y * cos_a); }
   c2dPoint rotate(double alpha)
      { return rotate(sin(alpha), cos(alpha)); }

   // Abstand (c2dPoint x c2dPoint) => double
   double getDistSqr(const c2dPoint& p) const
      { return sqr(x - p.x) + sqr(y - p.y); }
   double getDist(const c2dPoint& p) const
      { return sqrt(getDistSqr(p)); }

   // Vergleich (c2dPoint x c2dPoint) => int
   friend bool operator==(const c2dPoint& a, const c2dPoint& b)
      { return is_zero(a.x - b.x) && is_zero(a.y - b.y); }
   friend bool operator!=(const c2dPoint& a, const c2dPoint& b)
      { return !is_zero(a.x - b.x) || !is_zero(a.y - b.y); }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dSize
// ---------------------------------------------------------------------------
//
//  c2dSize
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dSize {

public:
   double cx, cy;

   c2dSize()
      { cx = cy = 0.0; }
   c2dSize(double cx, double cy)
      { c2dSize::cx = cx;
        c2dSize::cy = cy; }
   c2dSize(const c2dSize& s)
      { cx = s.cx;
        cy = s.cy; }
   c2dSize(const c2dVector& v)
      { cx = v.x;
        cy = v.y; }

   // Addition/Subtraktion (c2dSize x c2dSize) => c2dSize
   c2dSize operator+(const c2dSize& s) const
      { return c2dSize(cx + s.cx, cy + s.cy); }
   c2dSize operator-(const c2dSize& s) const
      { return c2dSize(cx - s.cx, cy - s.cy); }

   // Addition/Subtraktion, Zuweisung (c2dSize x c2dSize) => c2dSize
   c2dSize& operator+=(const c2dSize& s)
      { cx += s.cx;
        cy += s.cy;
        return *this; }
   c2dSize& operator-=(const c2dSize& s)
      { cx -= s.cx;
        cy -= s.cy;
        return *this; }

   // Multiplikation/Division mit Skalar (c2dSize x double) => c2dSize
   friend c2dSize operator*(const c2dSize& s, double r)
      { return c2dSize(s.cx*r, s.cy*r); }
   friend c2dSize operator/(const c2dSize& s, double r)
      { return c2dSize(s.cx/r, s.cy/r); }

   // Multiplikation/Division mit Skalar (double x c2dSize) => c2dSize
   friend c2dSize operator*(double r, const c2dSize& s)
      { return c2dSize(r*s.cx, r*s.cy); }
   friend c2dSize operator/(double r, const c2dSize& s)
      { return c2dSize(r/s.cx, r/s.cy); }

   // Vorzeichenaenderung
   friend c2dSize operator-(const c2dSize& s)
      { return c2dSize(-s.cx, -s.cy); }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dBox
// ---------------------------------------------------------------------------
//
//
//  c2dBox
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dBox {

public:
   c2dPoint lb, rt;

   c2dBox()
      { lb.x = lb.y = rt.x = rt.y = 0.0; }

   // Rechteck aus zwei gegenueberliegenden Eckpunkten
   c2dBox(double x1, double y1, double x2 = 0.0, double y2 = 0.0)
      { lb.x = min(x1,x2); lb.y = min(y1,y2); rt.x = max(x1,x2); rt.y = max(y1,y2); }
   c2dBox(const c2dPoint& p1, const c2dPoint& p2)
      { lb.x = min(p1.x,p2.x); lb.y = min(p1.y,p2.y); rt.x = max(p1.x,p2.x); rt.y = max(p1.y,p2.y); }

   // Rechteck aus Startpunkt (links unten) und Groesse
   c2dBox(const c2dPoint& l_bottom, const c2dVector& size_vec)
      { lb = l_bottom; rt = l_bottom + size_vec; }
   c2dBox(const c2dPoint& l_bottom, const c2dSize& size)
      { lb = l_bottom; rt = l_bottom + c2dVector(size); }

   // Addition (c2dBox x c2dBox) => c2dBox
   friend c2dBox operator+(const c2dBox& r, const c2dBox& s)
      { return c2dBox(min(r.lb.x, s.lb.x), min(r.lb.y, s.lb.y), max(r.rt.x, s.rt.x), max(r.rt.y, s.rt.y)); }

   // Addition, Zuweisung (c2dBox x c2dBox) => c2dBox
   c2dBox& operator+=(const c2dBox& r)
      { lb = c2dPoint(min(lb.x, r.lb.x), min(lb.y, r.lb.y));
        rt = c2dPoint(max(rt.x, r.rt.x), max(rt.y, r.rt.y));
        return *this; }

   // Multiplikation/Division mit Skalar (c2dBox x double) => c2dBox
   friend c2dBox operator*(const c2dBox& b, double r)
      { return c2dBox(c2dVector(b.lb)*r, c2dPoint(c2dVector(b.rt)*r)); }
   friend c2dBox operator/(const c2dBox& b, double r)
      { return c2dBox(c2dVector(b.lb)/r, c2dPoint(c2dVector(b.rt)/r)); }

   // Multiplikation/Division mit Skalar (double x c2dBox) => c2dBox
   friend c2dBox operator*(double r, const c2dBox& b)
      { return c2dBox(r*c2dVector(b.lb), c2dPoint(r*c2dVector(b.rt))); }
   friend c2dBox operator/(double r, const c2dBox& b)
      { return c2dBox(r/c2dVector(b.lb), c2dPoint(r/c2dVector(b.rt))); }

   // Rechteck vergroessern
   c2dBox inflate(const c2dSize& size) const
      { return c2dBox(lb - size, rt + size); }
   c2dBox inflate(const c2dVector& dlb, const c2dVector& drt) const
      { return c2dBox(lb - dlb, rt + drt); }
   c2dBox inflate(double x, double y) const
      { return inflate(c2dSize(x,y)); }
   c2dBox inflate(double l, double b, double r, double t) const
      { return inflate(c2dVector(l,b), c2dVector(r,t)); }

   // Groesse des Rechteckes
   c2dSize getSize() const
      { return c2dSize(rt - lb); }
   double getWidth() const
      { return rt.x - lb.x; }
   double getHeight() const
      { return rt.y - lb.y; }

   // Koordinaten der Seiten
   double getXLeft() const
      { return lb.x; }
   double getXRight() const
      { return rt.x; }
   double getYBottom() const
      { return lb.y; }
   double getYTop() const
      { return rt.y; }

   // Eckpunkte
   c2dPoint getBottomLeft() const
      { return lb; }
   c2dPoint getBottomRight() const
      { return c2dPoint(rt.x, lb.y); }
   c2dPoint getTopLeft() const
      { return c2dPoint(lb.x, rt.y); }
   c2dPoint getTopRight() const
      { return rt; }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dLineSeg
// ---------------------------------------------------------------------------
//
// Beschreibt ein Geradensegment im kartesischen 2D-Raum, gegeben durch den
// Startpunkt (s) und Endpunkt (e).
//
//  c2dLineSeg
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dLineSeg {

public:
   c2dPoint s, e;

   c2dLineSeg()
      { }
   c2dLineSeg(const c2dPoint& s, const c2dPoint& e)
      { c2dLineSeg::s = s;
        c2dLineSeg::e = e; }
   c2dLineSeg(double sx, double sy, double ex, double ey)
      { s = c2dPoint(sx, sy);
        e = c2dPoint(ex, ey); }
   c2dLineSeg(const c2dLineSeg& l, double off);

   // Vergleich (c2dLineSeg x c2dLineSeg) => int
   friend bool operator==(const c2dLineSeg& a, const c2dLineSeg& b)
      { return a.s == b.s && a.e == b.e; }
   friend bool operator!=(const c2dLineSeg& a, const c2dLineSeg& b)
      { return a.s != b.s || a.e != b.e; }

   // Koordinatentransformation (c2dLineSeg x c2dVector) => c2dLineSeg
   friend c2dLineSeg operator+(const c2dLineSeg& l, const c2dVector& v)
      { return c2dLineSeg(l.s + v, l.e + v); }
   friend c2dLineSeg operator-(const c2dLineSeg& l, const c2dVector& v)
      { return c2dLineSeg(l.s - v, l.e - v); }

   // Koordinatentransformation, Zuweisung (c2dLineSeg x c2dVector) => c2dLineSeg
   c2dLineSeg& operator+=(const c2dVector& v)
      { s += v; e += v;
        return *this; }
   c2dLineSeg& operator-=(const c2dVector& v)
      { s -= v; e -= v;
        return *this; }

   // Vorzeichenaenderung (Richtungsaenderung)
   friend c2dLineSeg operator-(const c2dLineSeg& l)
      { return c2dLineSeg(l.e, l.s); }

   // Rotieren um beliebigen Winkel (um Ursprung)
   c2dLineSeg rotate(double sin_a, double cos_a)
      { return c2dLineSeg(s.rotate(sin_a, cos_a), e.rotate(sin_a, cos_a)); }
   c2dLineSeg rotate(double alpha)
      { return rotate(sin(alpha), cos(alpha)); }

   // Delta X, Delta Y
   double dX() const
      { return e.x - s.x; }
   double dY() const
      { return e.y - s.y; }

   // Kleinstes umschliessendes Rechteck
   c2dBox getBBox() const
      { return c2dBox(s, e); }

   // Laenge des Geradensegmentes
   double getLengthSqr() const
      { return sqr(e.x - s.x) + sqr(e.y - s.y); }
   double getLength() const
      { return sqrt(getLengthSqr()); }

   // Richtungsvektor des Geradensegmentes
   c2dVector getDirV() const
      { return e - s; }
   c2dVector getDirUnitV() const
      { return getDirV().getUnitV(); }

   // Normvektor des Geradensegmentes (senkrecht auf Richtungsvektor)
   c2dVector getNormV() const
      { return getDirV().getNormV(); }
   c2dVector getNormUnitV() const
      { return getDirV().getNormUnitV(); }

   // Degenerierte Gerade (Laenge == 0)?
   bool isDegenerate() const
      { return is_zero(getLengthSqr()); }

   // Liegt Punkt p auf der Geraden durch (s,e) vor s?
   bool hasBefore(const c2dPoint& p) const;

   // Liegt Punkt p auf der Geraden durch (s,e) nach e?
   bool hasAfter(const c2dPoint& p) const;

   // Liegt Punkt p auf dem Geradensegment?
   bool hasOn(const c2dPoint& p) const;

};

#endif /*__INTERFACE__*/


// Implementierung c2dLineSeg
// ===========================================================================

c2dLineSeg::c2dLineSeg(const c2dLineSeg& l, double off)
{
   double dx = l.dX(), dy = l.dY();
   double nx, ny;

   if ( fabs(dx) < ZDELTA ) {
      nx = dy < 0 ? off : -off;
      ny = 0.0;
   } else if ( fabs(dy) < ZDELTA ) {
      nx = 0.0;
      ny = dx < 0 ? -off : off;
   } else {
      ny = off * dx / l.getLength();
      nx = - dy/dx * ny;
   }

   s.x = l.s.x + nx; e.x = l.e.x + nx;
   s.y = l.s.y + ny; e.y = l.e.y + ny;

// fprintf(stderr, "Parallelgerade zu [(%g/%g)..(%g/%g)]: [(%g/%g)..(%g/%g)]\n",
//    g.s.x, g.s.y, g.e.x, g.e.y, s.x, s.y, e.x, e.y);
}

bool c2dLineSeg::hasBefore(const c2dPoint& p) const
{
   // Noetige Tests:
   //  (a) P liegt auf Gerade durch S und E
   //  (b) SE zeigt in gleiche Richtung wie PS
   //
   //      |----->
   //            |-------->
   //   ---x-----x--------x---
   //      P     S        E

   if ( !c2dLine(*this).hasOn(p) )
      return false;
   return
      (e - s).getUnitV() == (s - p).getUnitV();
}

bool c2dLineSeg::hasAfter(const c2dPoint& p) const
{
   // Noetige Tests:
   //  (a) P liegt auf Gerade durch S und E
   //  (b) SE zeigt in gleiche Richtung wie EP
   //
   //               |--->
   //      |-------->
   //   ---x--------x-----x---
   //      S        E     P

   if ( !c2dLine(*this).hasOn(p) )
      return false;
   return
      (e - s).getUnitV() == (p - e).getUnitV();
}

bool c2dLineSeg::hasOn(const c2dPoint& p) const
{
   // Noetige Tests:
   //  (a) P == S   oder
   //  (b) P == E   oder
   //  (c1) P liegt auf Gerade durch S und E
   //  (c2) SP zeigt in gleiche Richtung wie PE
   //
   //          |---->
   //      |--->
   //   ---x---x----x---
   //      S   P    E

   if ( p == s || p == e )
      return true;
   if ( !c2dLine(*this).hasOn(p) )
      return false;
   return
      (p - s).getUnitV() == (e - p).getUnitV();
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dLine
// ---------------------------------------------------------------------------
//
// Beschreibt eine Gerade im kartesischen 2D-Raum, gegeben durch die Parameter
// A, B und C der allgemeinen Geradengleichung: A*x + B*y + C = 0. Die
// Richtung der Geraden wird durch die Parameter A und B gegeben, der
// Richtungsvektor ist (B/-A).
//
//  c2dLine
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dLine {

public:
   double a, b, c;

   c2dLine()
      { a = b = 1.0;
        c = 0.0; }
   c2dLine(double a, double b, double c)
      { c2dLine::a = a;
        c2dLine::b = b;
        c2dLine::c = c; }
   c2dLine(const c2dPoint& p, const c2dVector& dir)
      { a = - dir.y;
        b = dir.x;
        c = p.x*dir.y - p.y*dir.x; }
   c2dLine(const c2dPoint& p, const c2dPoint& q)
      { a = p.y - q.y;
        b = q.x - p.x;
        c = p.x*q.y - p.y*q.x; }
   c2dLine(const c2dLineSeg& l)
      { a = l.s.y - l.e.y;
        b = l.e.x - l.s.x;
        c = l.s.x*l.e.y - l.s.y*l.e.x; }
   c2dLine(const c2dLine& l)
      { a = l.a;
        b = l.b;
        c = l.c; }

   // Parallelgerade mit Abstand 'off'
   c2dLine(const c2dLine& l, double off);

   // Koordinatentransformation (c2dLine x c2dVector) => c2dLine
   friend c2dLine operator+(const c2dLine& l, const c2dVector& v)
      { c2dPoint p = l.getRandomPoint() + v;
        return c2dLine(l.a, l.b, -p.x*l.a - p.y*l.b); }
   friend c2dLine operator-(const c2dLine& l, const c2dVector& v)
      { c2dPoint p = l.getRandomPoint() - v;
        return c2dLine(l.a, l.b, -p.x*l.a - p.y*l.b); }

   // Koordinatentransformation, Zuweisung (c2dLine x c2dVector) => c2dLine
   c2dLine& operator+=(const c2dVector& v)
      { c2dPoint p = getRandomPoint() + v;
        c = p.x*b - p.y*a;
        return *this; }
   c2dLine& operator-=(const c2dVector& v)
      { c2dPoint p = getRandomPoint() + v;
        c = p.x*b - p.y*a;
        return *this; }

   // Vorzeichenaenderung (Richtungsaenderung)
   friend c2dLine operator-(const c2dLine& l)
      { return c2dLine(-l.a, -l.b, -l.c); }

   // Richtungsvektor der Geraden
   c2dVector getDirV() const
      { return c2dVector(b, -a); }
   c2dVector getDirUnitV() const
      { return getDirV().getUnitV(); }

   // Normvektor der Geraden (senkrecht auf Richtungsvektor)
   c2dVector getNormV() const
      { return c2dVector(a, b); }
   c2dVector getNormUnitV() const
      { return getNormV().getUnitV(); }

   // Winkel (Bogenmass) zwischen zwei Geraden
   double getAngle(const c2dLine& l) const
      { return getDirV().getAngle(l.getDirV()); }

   // Abstand zwischen Gerade und Punkt
   double getDist(const c2dPoint& p) const
      { return fabs((a*p.x + b*p.y + c) / sqrt(sqr(a) + sqr(b))); }

   // Liefert beliebigen Punkt auf der Geraden
   c2dPoint getRandomPoint() const;

   // Liefert Punkt auf der Geraden (gegeben: x- bzw. y-Koordinate)
   c2dPoint getPointFromX(double x) const;
   c2dPoint getPointFromY(double y) const;

   // Liegt Punkt p auf der Geraden?
   bool hasOn(const c2dPoint& p) const
      { return is_zero(a*p.x + b*p.y + c); }

};

#endif /*__INTERFACE__*/


// Implementierung c2dLine
// ===========================================================================

c2dLine::c2dLine(const c2dLine& l, double off)
{
   // Beliebigen Punkt auf Gerade l vektoriell verschieben um 'off'
   c2dPoint p = l.getRandomPoint() + l.getNormUnitV() * off;

   a = l.a;
   b = l.b;
   c = -p.x*a - p.y*b;
}

c2dPoint c2dLine::getRandomPoint() const
{
   if ( is_zero(a) ) {
      if ( is_zero(b) ) {
         return c2dPoint();
      } else {
         return c2dPoint(0, -c/b);
      }
   } else {
      return c2dPoint(-c/a, 0);
   }
}

c2dPoint c2dLine::getPointFromX(double x) const
{
   if ( is_zero(b) ) {
      if ( is_zero(a) ) {
         return c2dPoint();
      } else {
         return c2dPoint(-c/a, 0);
      }
   } else {
      return c2dPoint(x, -a/b*x - c/b);
   }
}

c2dPoint c2dLine::getPointFromY(double y) const
{
   if ( is_zero(a) ) {
      if ( is_zero(b) ) {
         return c2dPoint();
      } else {
         return c2dPoint(0, -c/b);
      }
   } else {
      return c2dPoint(-b/a*y - c/a, y);
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dArc
// ---------------------------------------------------------------------------
//
// Beschreibt einen Kreisbogen im kartesischen 2D-Raum. Der Kreisbogen ist
// gegeben durch: Startpunkt (s), Endpunkt (e), Mittelpunkt (m) und Orien-
// tierung (dir). Aus historischen Gruenden ist die Default-Orientierung < 0
// (im Uhrzeigersinn).
//
//    dir | Drehrichtung
//   -----+----------------------------------------------
//     >0 | mathmatisch positiv, gegen den Uhrzeigersinn
//     <0 | mathmatisch negativ, im Uhrzeigersinn
//
//  c2dArc
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dArc {

public:
   c2dPoint s, e, m;
   int dir;

   c2dArc()
      { dir = -1; }
   c2dArc(const c2dPoint& s, const c2dPoint& e, const c2dPoint& m, int dir = -1)
      { c2dArc::s = s;
        c2dArc::e = e;
        c2dArc::m = m;
        c2dArc::dir = dir; }

   // Vergleich (c2dCircle x c2dCircle) => int
   bool operator==(const c2dArc& a) const
      { return s == a.s && e == a.e && m == a.m && dir == a.dir; }
   bool operator!=(const c2dArc& a) const
      { return s != a.s || e != a.e || m != a.m || dir != a.dir; }

   // Koordinatentransformation (c2dArc x c2dVector) => c2dArc
   friend c2dArc operator+(const c2dArc& a, const c2dVector& v)
      { return c2dArc(a.s + v, a.e + v, a.m + v, a.dir); }
   friend c2dArc operator-(const c2dArc& a, const c2dVector& v)
      { return c2dArc(a.s - v, a.e - v, a.m - v, a.dir); }

   // Koordinatentransformation, Zuweisung (c2dArc x c2dVector) => c2dArc
   c2dArc& operator+=(const c2dVector& v)
      { s += v; e += v; m += v;
        return *this; }
   c2dArc& operator-=(const c2dVector& v)
      { s -= v; e -= v; m -= v;
        return *this; }

   // Vorzeichenaenderung (Richtungsaenderung)
   friend c2dArc operator-(const c2dArc& a)
      { return c2dArc(a.e, a.s, a.m, -a.dir); }

   // Rotieren um beliebigen Winkel (um Ursprung)
   c2dArc rotate(double sin_a, double cos_a)
      { return c2dArc(s.rotate(sin_a, cos_a), e.rotate(sin_a, cos_a), m.rotate(sin_a, cos_a), dir); }
   c2dArc rotate(double alpha)
      { return rotate(sin(alpha), cos(alpha)); }

   // Kleinstes umschliessendes Rechteck
   c2dBox getBBox() const;

   // Radius des Kreisbogens
   double getRadiusSqr() const
      { return (s - m).getLengthSqr(); }
   double getRadius() const
      { return sqrt(getRadiusSqr()); }

   // Laenge des Kreisbogens
   double getLengthSqr() const
      { return getAngleDiff() * getRadiusSqr(); }
   double getLength() const
      { return sqrt(getLengthSqr()); }

   // Winkel zwischen (m,p) und positiver x-Achse (Bogenmass)
   // Hinweis: Der Winkel waechst immer gegen der Uhrzeigersinn!
   double getAngle(const c2dPoint& p) const
      { double angle = atan2(p.y - m.y, p.x - m.x);
        return angle < 0.0 ? angle + rad(360.0) : angle; }

   // Winkel zwischen Startpunkt und positiver x-Achse
   double getStartAngle() const
      { return getAngle(s); }
   // Winkel zwischen Endpunkt und positiver x-Achse
   double getEndAngle() const
      { return getAngle(e); }
   // Winkeldifferenz zwischen Start- und Endpunkt
   double getAngleDiff() const
      { return C2dAngleDiff(getStartAngle(), getEndAngle(), dir); }

   // Liefert Punkt auf dem Kreisbogen (gegeben: Winkelposition)
   c2dPoint getPointFromAngle(double sin_a, double cos_a) const
      { return m + getRadius() * c2dVector(cos_a, sin_a); }
   c2dPoint getPointFromAngle(double alpha) const
      { return getPointFromAngle(sin(alpha), cos(alpha)); }

   // Richtungsvektor im Startpunkt
   c2dVector getStartDirV() const
      { return double(sign_of(dir)) * getStartNormV().getNormV(); }
   c2dVector getStartDirUnitV() const
      { return getStartDirV().getUnitV(); }

   // Richtungsvektor im Endpunkt
   c2dVector getEndDirV() const
      { return double(sign_of(dir)) * getEndNormV().getNormV(); }
   c2dVector getEndDirUnitV() const
      { return getEndDirV().getUnitV(); }

   // Normvektor im Startpunkt (senkrecht auf Richtungsvektor)
   c2dVector getStartNormV() const
      { return s - m; }
   c2dVector getStartNormUnitV() const
      { return getStartNormV().getUnitV(); }

   // Normvektor im Endpunkt (senkrecht auf Richtungsvektor)
   c2dVector getEndNormV() const
      { return e - m; }
   c2dVector getEndNormUnitV() const
      { return getEndNormV().getUnitV(); }

   // Liegt Punkt p auf dem Kreisbogen?
   bool hasOn(const c2dPoint& p) const;

};

#endif /*__INTERFACE__*/


// Implementierung c2dArc
// ===========================================================================

static int CalcQuad(c2dVector norm_v)
{
   //   2 | 1
   //  ---+---
   //   3 | 4

   if ( norm_v.y >= 0 ) {
      // Obere Haelfte
      return norm_v.x >= 0 ? 1 : 2;
   } else {
      // Untere Haelfte
      return norm_v.x < 0 ? 3 : 4;
   }
}

static c2dPoint CalcQuadStartPoint(const c2dArc& a, int quad)
{
   // Startpunkt des Quadranten fuer im Uhrzeigersinn drehendes 'a'

   switch ( quad ) {
    case 1:  return a.m + c2dVector(0, a.getRadius());
    case 2:  return a.m + c2dVector(-a.getRadius(), 0);
    case 3:  return a.m + c2dVector(0, -a.getRadius());
    case 4:  return a.m + c2dVector(a.getRadius(), 0);
    default: return a.m;
   }
}

static c2dPoint CalcQuadEndPoint(const c2dArc& a, int quad)
{
   // Endpunkt des Quadranten fuer im Uhrzeigersinn drehendes 'a'

   switch ( quad ) {
    case 1:  return a.m + c2dVector(a.getRadius(), 0);
    case 2:  return a.m + c2dVector(0, a.getRadius());
    case 3:  return a.m + c2dVector(-a.getRadius(), 0);
    case 4:  return a.m + c2dVector(0, -a.getRadius());
    default: return a.m;
   }
}

c2dBox c2dArc::getBBox() const
{
   // -------------------------------------------------------
   //  WICHTIG: Kreisboegen drehen immer IM Uhrzeigersinn!!!
   // -------------------------------------------------------

   if ( dir > 0 ) // Deshalb bei Drehrichtung CCW umdrehen!
      return c2dArc(e, s, m, -1).getBBox();

   // Berechnung des Quadranten, in dem Start-/Endpunkt liegt
   int qs = CalcQuad(getStartNormV());
   int qe = CalcQuad(getEndNormV());

   if ( qs == qe ) {
      // Start- und Endpunkt im gleichen Quadranten
      if ( getStartAngle() > getEndAngle() ) {
         // Kreisbogen komplett in einem Quadranten
         return c2dBox(s, e);
      } else {
         // Kreisbogen umfasst alle Quadranten
         return c2dCircle(*this).getBBox();
      }
   } else {
      // Start- und Endpunkt in unterschiedlichen Quadranten
      int quad = qs;
      c2dBox bb(s, CalcQuadEndPoint(*this, qs));
      do {
         if ( --quad < 1 )
            quad = 4;
         c2dPoint pe = (quad == qe) ? e : CalcQuadEndPoint(*this, quad);
         bb += c2dBox(CalcQuadStartPoint(*this, quad), pe);
      } while ( quad != qe );
      return bb;
   }
}

bool c2dArc::hasOn(const c2dPoint& p) const
{
   if ( !c2dCircle(*this).hasOn(p) )
      return false;

   double angle = getAngle(p);
   double sa = getStartAngle();
   return
      C2dAngleDiff(sa, angle, dir) <= C2dAngleDiff(sa, getEndAngle(), dir);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition c2dCircle
// ---------------------------------------------------------------------------
//
// Beschreibt einen Vollkreis im kartesischen 2D-Raum. Der Kreis ist gegeben
// durch: Mittelpunkt (m), Radius (r) und Orientierung (dir). Aus histori-
// schen Gruenden ist die Default-Orientierung < 0 (im Uhrzeigersinn).
//
//    dir | Drehrichtung
//   -----+----------------------------------------------
//     >0 | mathmatisch positiv, gegen den Uhrzeigersinn
//     <0 | mathmatisch negativ, im Uhrzeigersinn
//
//  c2dCircle
//
// ===========================================================================

class __ECL_DLLEXPORT__ c2dCircle {

public:
   c2dPoint m;
   double r;
   int dir;

   c2dCircle()
      { r = 0.0; dir = -1; }
   c2dCircle(const c2dPoint& m, double r, int dir = -1)
      { c2dCircle::m = m;
        c2dCircle::r = r;
        c2dCircle::dir = dir; }
   c2dCircle(const c2dPoint& p, const c2dPoint& m, int dir = -1)
      { c2dCircle::m = m;
        c2dCircle::r = (p - m).getLength();
        c2dCircle::dir = dir; }
   c2dCircle(const c2dArc& arc)
      { m = arc.m;
        r = (arc.s - arc.m).getLength();
        dir = arc.dir; }

   // Konzentrischer Kreis mit Abstand 'off'
   c2dCircle(const c2dCircle& c, double off)
      { m = c.m;
        r = c.r + off;
        dir = c.dir; }

   // Vergleich (c2dCircle x c2dCircle) => int
   bool operator==(const c2dCircle& c) const
      { return m == c.m && is_zero(r - c.r) && dir == c.dir; }
   bool operator!=(const c2dCircle& c) const
      { return m != c.m || !is_zero(r - c.r) || dir != c.dir; }

   // Vorzeichenaenderung (Richtungsaenderung)
   friend c2dCircle operator-(const c2dCircle& c)
      { return c2dCircle(c.m, c.r, -c.dir); }

   // Kleinstes umschliessendes Rechteck
   c2dBox getBBox() const
      { return c2dBox(m - c2dVector(r,r), m + c2dVector(r,r)); }

   // Richtungsvektor in Punkt p
   c2dVector getDirVAt(const c2dPoint& p) const
      { return double(sign_of(dir)) * getNormVAt(p).getNormV(); }
   c2dVector getDirUnitVAt(const c2dPoint& p) const
      { return getDirVAt(p).getUnitV(); }

   // Normvektor in Punkt p (senkrecht auf Richtungsvektor)
   c2dVector getNormVAt(const c2dPoint& p) const
      { return p - m; }
   c2dVector getNormUnitVAt(const c2dPoint& p) const
      { return getNormVAt(p).getUnitV(); }

   // Liegt Punkt p innerhalb des Kreises?
   bool hasInside(const c2dPoint& p) const
      { return m.getDistSqr(p) <= r - ZDELTA; }

   // Liegt Punkt p ausserhalb des Kreises?
   bool hasOutside(const c2dPoint& p) const
      { return m.getDistSqr(p) >= r + ZDELTA; }

   // Liegt Punkt p auf dem Kreis?
   bool hasOn(const c2dPoint& p) const
      { return is_zero(m.getDist(p) - r); }

   // Liefert beliebigen Punkt auf dem Kreis
   c2dPoint getRandomPoint() const
      { return m + c2dVector(0.0, r); }

   // Liefert Punkt auf dem Kreis (gegeben: Winkelposition)
   c2dPoint getPointFromAngle(double sin_a, double cos_a) const
      { return m + r * c2dVector(cos_a, sin_a); }
   c2dPoint getPointFromAngle(double alpha) const
      { return getPointFromAngle(sin(alpha), cos(alpha)); }

};

#endif /*__INTERFACE__*/




// ===========================================================================
// Routinen zum Berechnen von Schnittpunkten
// ===========================================================================


#ifdef __INTERFACE__

typedef cArray<c2dPoint,c2dPoint> c2dPoints;

#endif /*__INTERFACE__*/


// Schnittpunkt zweier Geraden
// ===========================

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoint& isp, const c2dLine& l1, const c2dLine& l2)
{
   double d = l1.a*l2.b - l2.a*l1.b;

   if ( is_zero(d) ) {
      isp = c2dPoint(0, 0);
      return false;
   } else {
      isp = c2dPoint((l1.b*l2.c - l2.b*l1.c) / d, (l1.c*l2.a - l2.c*l1.a) / d);
      return true;
   }
}


// Schnittpunkt zwischen Gerade und Geradensegment
// ===============================================

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoint& isp, const c2dLine& l, const c2dLineSeg& ls)
{
   return
      C2dIntersect(isp, l, c2dLine(ls))
   && ls.hasOn(isp);
}

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoint& isp, const c2dLineSeg& ls, const c2dLine& l)
{
   return C2dIntersect(isp, l, ls);
}


// Schnittpunkt zweier Geradensegmente
// ===================================

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoint& isp, const c2dLineSeg& ls1, const c2dLineSeg& ls2)
{
   return
      C2dIntersect(isp, c2dLine(ls1), c2dLine(ls2))
      && ls1.hasOn(isp) && ls2.hasOn(isp);
}


// Schnittpunkt(e) zwischen Gerade und Kreis
// =========================================

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoints& isp, const c2dCircle& c, const c2dLine& l)
{
   // Koordinatentransformation: Kreis in Nulllage
   c2dLine l1 = l - c2dVector(c.m);

   if ( is_zero(l.b) ) {

      // Sonderfall: Gerade || y-Achse
      double a = -l1.c/l1.a;
      double d = sqr(c.r) - sqr(a);

      if ( is_zero(d) ) {
         isp.setSize(1); // 1 ISP (Tangente)
         isp[0] = c.m + c2dVector(a, 0.0);
         return true;
      } else if ( d > 0 ) {
         isp.setSize(2); // 2 ISP (Sekante)
         double sqrt_d = sqrt(d);
         isp[0] = c.m + c2dVector(a, sqrt_d);
         isp[1] = c.m + c2dVector(a, -sqrt_d);
         return true;
      } else {
         isp.setSize(0); // 0 ISP (Passante)
         return false;
      }

   } else {

      double b = -l1.c/l1.b;
      double m = -l1.a/l1.b;
      double m1 = 1 / (sqr(m) + 1);
      double d = sqr(c.r) * (1 + sqr(m)) - sqr(b);

      if ( is_zero(d) ) {
         isp.setSize(1); // 1 ISP (Tangente)
         isp[0] = c.m + c2dPoint(-m*b*m1, b*m1);
         return true;
      } else if ( d > 0 ) {
         isp.setSize(2); // 2 ISP (Sekante)
         double sqrt_d = sqrt(d);
         isp[0] = c.m + c2dPoint(-m*b*m1 + m1*sqrt_d, b*m1 + m*m1*sqrt_d);
         isp[1] = c.m + c2dPoint(-m*b*m1 - m1*sqrt_d, b*m1 - m*m1*sqrt_d);
         return true;
      } else {
         isp.setSize(0); // 0 ISP (Passante)
         return false;
      }

   }
}

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoints& isp, const c2dLine& l, const c2dCircle& c)
{
   return C2dIntersect(isp, c, l);
}


// Schnittpunkt zwischen Gerade und Kreisbogen
// ===========================================

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoints& isp, const c2dLine& l, const c2dArc& a)
{
   if ( C2dIntersect(isp, l, c2dCircle(a)) ) {
      if ( isp.getSize() > 1 && !a.hasOn(isp[1]) )
         isp.removeAt(1);
      if ( !a.hasOn(isp[0]) )
         isp.removeAt(0);
      return isp.getSize() > 0;
   }

   return false;
}

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoints& isp, const c2dArc& a, const c2dLine& l)
{
   return C2dIntersect(isp, l, a);
}


// Schnittpunkt(e) zweier Kreise
// =============================
// Hinweis: Bei identischen Kreisen wird true geliefert, aber 0 Schnittpunkte

GLOBAL bool __ECL_DLLEXPORT__ C2dIntersect(c2dPoints& isp, const c2dCircle& c1, const c2dCircle& c2)
{
   // m Um c1.m verschobener Mittelpunkt von c2
   c2dPoint m = c2.m - c2dVector(c1.m);

   if ( is_zero(m.x) && is_zero(m.y) ) {
      // Konzentrische Kreise

      isp.setSize(0);
      // Sonderbehandlung: Liefert true bei identischen Kreisen
      return is_equal(c1.r, c2.r);

   } else if ( is_zero(m.x) ) {
      // Mittelpunkte beider Kreise auf Parallele zur y-Achse

      double k = sqr(c2.r) - sqr(c1.r) - sqr(m.y);
      double d = -0.25 * sqr(k) / sqr(m.y) + sqr(c1.r);

      if ( is_zero(d) ) {
         isp.setSize(1); // 1 ISP (beruehren)
         isp[0] = c1.m + c2dPoint(0, -0.5 * k/m.y);
         return true;
      } else if ( d > 0 ) {
         isp.setSize(2); // 2 ISP (schneiden)
         double sqrt_d = sqrt(d);
         isp[0] = c1.m + c2dPoint(sqrt_d, -0.5 * k/m.y);
         isp[1] = c1.m + c2dPoint(-sqrt_d, -0.5 * k/m.y);
         return true;
      } else {
         isp.setSize(0); // 0 ISP (meiden)
         return false;
      }

   } else if ( is_zero(m.y) ) {
      // Mittelpunkte beider Kreise auf Parallele zur x-Achse

      double k = sqr(c2.r) - sqr(c1.r) - sqr(m.x);
      double d = -0.25 * sqr(k) / sqr(m.x) + sqr(c1.r);

      if ( is_zero(d) ) {
         isp.setSize(1); // 1 ISP (beruehren)
         isp[0] = c1.m + c2dPoint(-0.5 * k/m.x, 0);
         return true;
      } else if ( d > 0 ) {
         isp.setSize(2); // 2 ISP (schneiden)
         double sqrt_d = sqrt(d);
         isp[0] = c1.m + c2dPoint(-0.5 * k/m.x, sqrt_d);
         isp[1] = c1.m + c2dPoint(-0.5 * k/m.x, -sqrt_d);
         return true;
      } else {
         isp.setSize(0); // 0 ISP (meiden)
         return false;
      }

   } else {

      double k = sqr(c1.r) - sqr(c2.r) + sqr(m.x) + sqr(m.y);
      double d = -sqr(k) + 4*sqr(c1.r) * (sqr(m.x) + sqr(m.y));

      double nx = 0.5 / (1 + sqr(m.x)/sqr(m.y));
      double ny = 0.5 / (1 + sqr(m.y)/sqr(m.x));

      if ( is_zero(d) ) {
         isp.setSize(1); // 1 ISP (beruehren)
         isp[0] = c1.m + c2dPoint(nx * m.x*k/sqr(m.y), ny * m.y*k/sqr(m.x));
         return true;
      } else if ( d > 0 ) {
         isp.setSize(2); // 2 ISP (schneiden)
         double sqrt_d = sqrt(d);
         isp[0] = c1.m + c2dPoint(nx * (m.x*k/sqr(m.y) + sqrt_d/m.y), ny * (m.y*k/sqr(m.x) - sqrt_d/m.x));
         isp[1] = c1.m + c2dPoint(nx * (m.x*k/sqr(m.y) - sqrt_d/m.y), ny * (m.y*k/sqr(m.x) + sqrt_d/m.x));
         return true;
      } else {
         isp.setSize(0); // 0 ISP (meiden)
         return false;
      }

   }

}



