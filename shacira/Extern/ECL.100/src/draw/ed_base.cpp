// ===========================================================================
// ed_base.cpp                                   ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cdColor                    - Farben
//
//    cdLineStyle                - Linienstile
//
//    cdPattern                  - Fuellmuster
//
//    cdMix                      - Mischarten
//
//    cdAlign                    - Ausrichtung
//
//    cdViewport                 - Beschreibung eines Sichtrechteckes
//
// ===========================================================================

#include "draw/ed_base.hpp"

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <stddef.h>
#include <stdarg.h>
#include <math.h>

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#else
   #error "Unsupported target for ECL module ed_base"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_geo2d.hpp"

class cdVector;
class cdPoint;
class cdSize;
class cdRect;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdColor
// ---------------------------------------------------------------------------
//
//  cdColor
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdColor {

public:
   enum COLOR {
      None, Black, Blue, Red, Pink, Green, Cyan, Yellow, Gray,
      DarkGray, DarkBlue, DarkRed, DarkPink, DarkGreen, DarkCyan, Brown, White,
      Background, Foreground, Undef
   };

   cdColor(COLOR c = None)
      { makeRGBC(color, c); }
   cdColor(unsigned char r, unsigned char g, unsigned char b)
      { makeRGBC(color, r, g, b); }

   operator COLOR() const
      { return COLOR(color.c); }

   bool operator==(const cdColor& other) const;
   bool operator!=(const cdColor& other) const
      { return !(*this == other); }

   // make cdColor object from OS specific code
   static cdColor fromOsVal(long os_val);

   // convert to OS specific code
   static long getOsVal(COLOR c);
   static long getOsVal(unsigned char r, unsigned char g, unsigned char b);
   long getOsVal() const;
   long getOsValRGB() const;

private:
   struct RGBC { unsigned char r, g, b, c; };
   RGBC color;

   static void makeRGBC(RGBC& rgbc, COLOR c);
   static void makeRGBC(RGBC& rgbc, unsigned char r, unsigned char g, unsigned char b);

};

#endif /*__INTERFACE__*/


// Implementierung cdColor
// ===========================================================================

bool cdColor::operator==(const cdColor& other) const
{
   if ( color.c == None ) {
      return other.color.c == None;
   } else if ( other.color.c == None ) {
      return false;
   }

   return color.r == other.color.r
       && color.g == other.color.g
       && color.b == other.color.b;
}

void cdColor::makeRGBC(RGBC& rgbc, COLOR c)
{
   rgbc.c = (unsigned char)c;

   switch ( c ) {
    case Black:       rgbc.r =   0; rgbc.g =   0; rgbc.b =   0; break;
    case Blue:        rgbc.r =   0; rgbc.g =   0; rgbc.b = 255; break;
    case Red:         rgbc.r = 255; rgbc.g =   0; rgbc.b =   0; break;
    case Pink:        rgbc.r = 255; rgbc.g =   0; rgbc.b = 255; break;
    case Green:       rgbc.r =   0; rgbc.g = 255; rgbc.b =   0; break;
    case Cyan:        rgbc.r =   0; rgbc.g = 255; rgbc.b = 255; break;
    case Yellow:      rgbc.r = 255; rgbc.g = 255; rgbc.b =   0; break;
    case Gray:        rgbc.r = 191; rgbc.g = 191; rgbc.b = 191; break;
    case DarkGray:    rgbc.r = 127; rgbc.g = 127; rgbc.b = 127; break;
    case DarkBlue:    rgbc.r =   0; rgbc.g =   0; rgbc.b = 127; break;
    case DarkRed:     rgbc.r = 127; rgbc.g =   0; rgbc.b =   0; break;
    case DarkPink:    rgbc.r = 127; rgbc.g =   0; rgbc.b = 127; break;
    case DarkGreen:   rgbc.r =   0; rgbc.g = 127; rgbc.b =   0; break;
    case DarkCyan:    rgbc.r =   0; rgbc.g = 127; rgbc.b = 127; break;
    case Brown:       rgbc.r = 127; rgbc.g = 127; rgbc.b =   0; break;
    case White:       rgbc.r = 255; rgbc.g = 255; rgbc.b = 255; break;
    case Background:  rgbc.r = 255; rgbc.g = 255; rgbc.b = 255; break;
    default:          rgbc.r =   0; rgbc.g =   0; rgbc.b =   0; break;
   }
}

void cdColor::makeRGBC(RGBC& rgbc, unsigned char r, unsigned char g, unsigned char b)
{
   rgbc.r = r; rgbc.g = g; rgbc.b = b;
   rgbc.c = (unsigned char)Undef;
}

cdColor cdColor::fromOsVal(long os_val)
{
   #if defined __ECL_OS2__
      switch ( c ) {
       case CLR_BLACK:      return Black;
       case CLR_BLUE:       return Blue;
       case CLR_RED:        return Red;
       case CLR_PINK:       return Pink;
       case CLR_GREEN:      return Green;
       case CLR_CYAN:       return Cyan;
       case CLR_YELLOW:     return Yellow;
       case CLR_PALEGRAY:   return Gray;
       case CLR_DARKGRAY:   return DarkGray;
       case CLR_DARKBLUE:   return DarkBlue;
       case CLR_DARKRED:    return DarkRed;
       case CLR_DARKPINK:   return DarkPink;
       case CLR_DARKGREEN:  return DarkGreen;
       case CLR_DARKCYAN:   return DarkCyan;
       case CLR_BROWN:      return Brown;
       case CLR_WHITE:      return White;
       case CLR_BACKGROUND: return Background;
       default:             return Undef;
      }
   #elif defined __ECL_W32__
      if ( os_val == -1 ) {
         return cdColor();
      } else {
         return cdColor(GetRValue(os_val), GetGValue(os_val), GetBValue(os_val));
      }
   #endif
}

long cdColor::getOsVal(COLOR c)
{
   #if defined __ECL_OS2__
      switch ( c ) {
       case Black:       return CLR_BLACK;
       case Blue:        return CLR_BLUE;
       case Red:         return CLR_RED;
       case Pink:        return CLR_PINK;
       case Green:       return CLR_GREEN;
       case Cyan:        return CLR_CYAN;
       case Yellow:      return CLR_YELLOW;
       case Gray:        return CLR_PALEGRAY;
       case DarkGray:    return CLR_DARKGRAY;
       case DarkBlue:    return CLR_DARKBLUE;
       case DarkRed:     return CLR_DARKRED;
       case DarkPink:    return CLR_DARKPINK;
       case DarkGreen:   return CLR_DARKGREEN;
       case DarkCyan:    return CLR_DARKCYAN;
       case Brown:       return CLR_BROWN;
       case White:       return CLR_WHITE;
       case Background:  return CLR_BACKGROUND;
       default:          return CLR_DEFAULT;
      }
   #elif defined __ECL_W32__
      if ( c == None ) {
         return -1;
      } else {
         RGBC rgbc; makeRGBC(rgbc, c);
         return getOsVal(rgbc.r, rgbc.g, rgbc.b);
      }
   #endif
}

long cdColor::getOsVal(unsigned char r, unsigned char g, unsigned char b)
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      return long(RGB(r, g, b));
   #endif
}

long cdColor::getOsVal() const
{
   #if defined __ECL_OS2__
      return getOsVal(COLOR(color.c));
   #elif defined __ECL_W32__
      return color.c == None ? -1 : long(RGB(color.r, color.g, color.b));
   #endif
}

long cdColor::getOsValRGB() const
{
   return getOsVal(color.r, color.g, color.b);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdLineStyle
// ---------------------------------------------------------------------------
//
//  cdLineStyle
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdLineStyle {

public:
   enum LINESTYLE {
      Null,       // Keine Linie
      Solid,      // Durchgezogene Linie
      Dot,        // [ ------- ]
      Dash,       // [ ....... ]
      DashDot     // [ _._._._ ]
   };

   cdLineStyle(LINESTYLE ls = Solid)
      { linestyle = ls; }
   operator LINESTYLE() const
      { return linestyle; }

   // convert to OS specific code
   static long getOsVal(LINESTYLE ls);
   long getOsVal() const
      { return getOsVal(linestyle); }

private:
   LINESTYLE linestyle;

};

#endif /*__INTERFACE__*/


// Implementierung cdLineStyle
// ===========================================================================

long cdLineStyle::getOsVal(LINESTYLE ls)
{
   #if defined __ECL_OS2__
      switch ( ls ) {
       case Null:    return 0;
       case Dot:     return LINETYPE_DOT;
       case Dash:    return LINETYPE_LONGDASH;
       case DashDot: return LINETYPE_DASHDOT;
       default:      return LINETYPE_SOLID;
      }
   #elif defined __ECL_W32__
      switch ( ls ) {
       case Null:    return PS_NULL;
       case Dot:     return PS_DOT;
       case Dash:    return PS_DASH;
       case DashDot: return PS_DASHDOT;
       default:      return PS_SOLID;
      }
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdPattern
// ---------------------------------------------------------------------------
//
//  cdPattern
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdPattern {

public:
   enum PATTERN {
      Null,       // Nicht gefuellt (Hintergrund scheint durch)
      Blank,      // Mit Papierfarbe gefuellt
      Solid,      // Mit Fuellfarbe gefuellt
      Cross,      // [ +++++ ]
      Hatch,      // [ xxxxx ]
      Vert,       // [ ||||| ]
      Horiz,      // [ ----- ]
      Diag1,      // [ \\\\\ ]
      Diag2       // [ ///// ]
   };

   cdPattern(PATTERN pat = Solid)
      { pattern = pat; }
   operator PATTERN() const
      { return pattern; }

   // convert to OS specific code
   static long getOsVal(PATTERN pat);
   long getOsVal() const
      { return getOsVal(pattern); }

private:
   PATTERN pattern;

};

#endif /*__INTERFACE__*/


// Implementierung cdPattern
// ===========================================================================

long cdPattern::getOsVal(PATTERN pat)
{
   #if defined __ECL_OS2__
      switch ( pat ) {
       case Null:    return PATSYM_BLANK;    // ???
       case Blank:   return PATSYM_BLANK;
       case Cross:   return PATSYM_HATCH;    // ???
       case Hatch:   return PATSYM_HATCH;
       case Vert:    return PATSYM_VERT;
       case Horiz:   return PATSYM_HORIZ;
       case Diag1:   return PATSYM_DIAG3;
       case Diag2:   return PATSYM_DIAG2;
       default:      return PATSYM_SOLID;
      }
   #elif defined __ECL_W32__
      switch ( pat ) {
       case Null:    return -1;              // NULL
       case Blank:   return -2;              // BLANK
       case Cross:   return HS_CROSS;        // [ +++++ ]
       case Hatch:   return HS_DIAGCROSS;    // [ xxxxx ]
       case Vert:    return HS_VERTICAL;     // [ ||||| ]
       case Horiz:   return HS_HORIZONTAL;   // [ ----- ]
       case Diag1:   return HS_FDIAGONAL;    // [ \\\\\ ]
       case Diag2:   return HS_BDIAGONAL;    // [ ///// ]
       default:      return -3;              // SOLID
      }
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMix
// ---------------------------------------------------------------------------
//
//  cdMix
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMix {

public:
   enum MIX {
      Overpaint, Leavealone, And, Or, Xor
   };

   cdMix(MIX mix = Overpaint)
      { cdMix::mix = mix; }
   operator MIX() const
      { return mix; }

   // convert to OS specific code
   static long getOsVal(MIX mix);
   long getOsVal() const
      { return getOsVal(mix); }

private:
   MIX mix;

};

#endif /*__INTERFACE__*/


// Implementierung cdMix
// ===========================================================================

long cdMix::getOsVal(MIX mix)
{
   #if defined __ECL_OS2__
      switch ( mix ) {
       case Overpaint:  return BM_OVERPAINT;
       case And:        return BM_AND;
       case Or:         return BM_OR;
       case Xor:        return BM_XOR;
       default:         return BM_LEAVEALONE;
      }
   #elif defined __ECL_W32__
      switch ( mix ) {
       case Overpaint:  return R2_COPYPEN;
       case And:        return R2_MASKPEN;
       case Or:         return R2_MERGEPEN;
       case Xor:        return R2_XORPEN;
       default:         return R2_NOP;
      }
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdAlign
// ---------------------------------------------------------------------------
//
//  cdAlign
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdAlign {

public:
   enum ALIGN {
      Left, Center, Right,       // horizontal alignment
      Top, Half, Base, Bottom    // vertical alignment
   };

   cdAlign(ALIGN a = Left)
      { align = a; }
   operator ALIGN() const
      { return align; }

   // convert to OS specific code
   static long getOsVal(ALIGN a);
   long getOsVal() const
      { return getOsVal(align); }

private:
   ALIGN align;

};

#endif /*__INTERFACE__*/


// Implementierung cdAlign
// ===========================================================================

long cdAlign::getOsVal(ALIGN a)
{
   #if defined __ECL_OS2__
      switch ( a ) {
       case Left:    return TA_LEFT;
       case Center:  return TA_CENTER;
       case Right:   return TA_RIGHT;
       case Top:     return TA_TOP;
       case Half:    return TA_HALF;
       case Base:    return TA_BASE;
       case Bottom:  return TA_BOTTOM;
       default:      return TA_LEFT;
      }
   #elif defined __ECL_W32__
      switch ( a ) {
       case Left:    return TA_LEFT;
       case Center:  return TA_CENTER;
       case Right:   return TA_RIGHT;
       case Top:     return TA_TOP;
       case Half:    return 0x0800; // special marker bit, see ed_device.cpp
       case Base:    return TA_BASELINE;
       case Bottom:  return TA_BOTTOM;
       default:      return TA_LEFT;
      }
   #endif
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdVector
// ---------------------------------------------------------------------------
//
//  cdVector
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdVector {

public:
   int x, y;

   // Konstruktoren
   cdVector()
      { x = y = 0; }
   cdVector(int x, int y)
      { cdVector::x = x;
        cdVector::y = y; }
   cdVector(const cdVector& v)
      { x = v.x;
        y = v.y; }

   // Konstruktion von Vektoren aus spaeter definierten Klassen
   cdVector(const cdSize& p);
   cdVector(const cdPoint& p);

   // Addition/Subtraktion (cdVector x cdVector) => cdVector
   friend cdVector operator+(const cdVector& a, const cdVector& b)
      { return cdVector( a.x + b.x, a.y + b.y ); }
   friend cdVector operator-(const cdVector& a, const cdVector& b)
      { return cdVector( a.x - b.x, a.y - b.y ); }

   // Skalarprodukt (cdVector * cdVector) => int
   friend int operator*(const cdVector& a, const cdVector& b)
      { return a.x*b.x + a.y*b.y; }

   // Multiplikation/Division mit Skalar (cdVector x double) => cdVector
   friend cdVector operator*(const cdVector& a, double r)
      { return cdVector(int(a.x*r), int(a.y*r)); }
   friend cdVector operator/(const cdVector& a, double r)
      { return cdVector(int(a.x/r), int(a.y/r)); }

   // Multiplikation/Division mit Skalar (double x cdVector) => cdVector
   friend cdVector operator*(double r, const cdVector& a)
      { return cdVector(int(r*a.x), int(r*a.y)); }
   friend cdVector operator/(double r, const cdVector& a)
      { return cdVector(int(r/a.x), int(r/a.y)); }

   // Vorzeichenaenderung
   friend cdVector operator-(const cdVector& a)
      { return cdVector(-a.x, -a.y); }

   // Vergleich (cdVector x cdVector) => int
   friend bool operator==(const cdVector& a, const cdVector& b)
      { return a.x == b.x && a.y == b.y; }
   friend bool operator!=(const cdVector& a, const cdVector& b)
      { return a.x != b.x || a.y != b.y; }

   // Rotieren um -90 Grad
   void rotate()
      { int tmp = x; x = -y; y = tmp; }

   // Laenge des Vektors
   int getLengthSqr() const
      { return x*x + y*y; }
   double getLength() const
      { return sqrt(getLengthSqr()); }

   // Winkel (Bogenmass) zwischen zwei Vektoren
   double getAngle(const cdVector& v) const;

};

#endif /*__INTERFACE__*/


// Implementierung cdVector
// ===========================================================================

cdVector::cdVector(const cdSize& s)
{
   x = s.cx; y = s.cy;
}

cdVector::cdVector(const cdPoint& p)
{
   x = p.x; y = p.y;
}

static double CalcAngle(const cdVector& v)
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

double cdVector::getAngle(const cdVector& v) const
{
   return CalcAngle(v) - CalcAngle(*this);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdPoint
// ---------------------------------------------------------------------------
//
//  cdPoint
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdPoint {

public:
   int x, y;

   // Konstruktoren
   cdPoint()
      { x = y = 0; }
   cdPoint(int x, int y)
      { cdPoint::x = x;
        cdPoint::y = y; }
   cdPoint(const cdPoint& p)
      { x = p.x;
        y = p.y; }
   cdPoint(const cdVector& v)
      { x = v.x;
        y = v.y; }

   // Addition/Subtraktion (cdPoint x cdVector) => cdPoint
   friend cdPoint operator+(const cdPoint& p, const cdVector& v)
      { return cdPoint(p.x + v.x, p.y + v.y); }
   friend cdPoint operator-(const cdPoint& p, const cdVector& v)
      { return cdPoint(p.x - v.x, p.y - v.y); }

   // Addition/Subtraktion, Zuweisung (cdPoint x cdVector) => cdPoint
   cdPoint& operator+=(const cdVector& v)
      { x += v.x, y += v.y;
        return *this; }
   cdPoint& operator-=(const cdVector& v)
      { x -= v.x, y -= v.y;
        return *this; }

   // Differenz (cdPoint - cdPoint) => cdVector
   friend cdVector operator-(const cdPoint& a, const cdPoint& b)
      { return cdVector(a.x - b.x, a.y - b.y); }

   // Abstand (cdPoint x cdPoint) => double
   int getDistSqr(const cdPoint& p) const
      { return sqr(x - p.x) + sqr(y - p.y); }
   double getDist(const cdPoint& p) const
      { return sqrt(getDistSqr(p)); }

   // Vergleich (cdPoint x cdPoint) => int
   friend bool operator==(const cdPoint& a, const cdPoint& b)
      { return a.x == b.x && a.y == b.y; }
   friend bool operator!=(const cdPoint& a, const cdPoint& b)
      { return a.x != b.x || a.y != b.y; }

   bool isOrigin() const
      { return x == 0 && y == 0; }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdSize
// ---------------------------------------------------------------------------
//
//  cdSize
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdSize {

public:
   int cx, cy;

   // Konstruktoren
   cdSize()
      { cx = cy = 0; }
   cdSize(int cx, int cy)
      { cdSize::cx = cx;
        cdSize::cy = cy; }
   cdSize(const cdSize& s)
      { cx = s.cx;
        cy = s.cy; }
   cdSize(const cdVector& v)
      { cx = v.x;
        cy = v.y; }

   // Addition/Subtraktion (cdSize x cdSize) => cdSize
   cdSize operator+(const cdSize& s) const
      { return cdSize(cx + s.cx, cy + s.cy); }
   cdSize operator-(const cdSize& s) const
      { return cdSize(cx - s.cx, cy - s.cy); }

   // Addition/Subtraktion, Zuweisung (cdSize x cdSize) => cdSize
   cdSize& operator+=(const cdSize& s)
      { cx += s.cx;
        cy += s.cy;
        return *this; }
   cdSize& operator-=(const cdSize& s)
      { cx -= s.cx;
        cy -= s.cy;
        return *this; }

   // Multiplikation/Division mit Skalar (cdSize x double) => cdSize
   friend cdSize operator*(const cdSize& s, double r)
      { return cdSize(int(s.cx*r), int(s.cy*r)); }
   friend cdSize operator/(const cdSize& s, double r)
      { return cdSize(int(s.cx/r), int(s.cy/r)); }

   // Multiplikation/Division mit Skalar (double x cdSize) => cdSize
   friend cdSize operator*(double r, const cdSize& s)
      { return cdSize(int(r*s.cx), int(r*s.cy)); }
   friend cdSize operator/(double r, const cdSize& s)
      { return cdSize(int(r/s.cx), int(r/s.cy)); }

   // Vorzeichenaenderung
   friend cdSize operator-(const cdSize& s)
      { return cdSize(-s.cx, -s.cy); }

   bool isNull() const
      { return cx == 0 && cy == 0; }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdRect
// ---------------------------------------------------------------------------
//
// Rechteck, gegeben durch zwei gegenueberliegende Punkte LB = links unten und
// RT = rechts oben). Zwei Koordinatensysteme werden automatisch unterschieden:
//
//    isMathCoord()    isWindowCoord()
//
//    ^                +------------>
//    |                |
//    |   +-----+RT    |   +-----+RT
//    |   |     |      |   |     |
//    | LB+-----+      | LB+-----+
//    |                |
//    +------------>   V
//
//  cdRect
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdRect {

public:
   cdPoint lb, rt;

   cdRect()
      { lb.x = lb.y = rt.x = rt.y = 0; }

   // Rechteck aus Eckpunkten links unten und rechts oben
   cdRect(int x_left, int y_bottom, int x_right = 0, int y_top = 0)
      { lb.x = x_left; lb.y = y_bottom; rt.x = x_right; rt.y = y_top; }
   cdRect(const cdPoint& l_bottom, const cdPoint& r_top)
      { lb = l_bottom; rt = r_top; }

   // Rechteck aus Startpunkt (links unten) und Groesse
   cdRect(const cdPoint& l_bottom, const cdVector& size_vec);
   cdRect(const cdPoint& l_bottom, const cdSize& size, bool math_coord = true);

   // Addition (cdRect x cdRect) => cdRect
   friend cdRect operator+(const cdRect& r, const cdRect& s);

   // Addition, Zuweisung (cdRect x cdRect) => cdRect
   cdRect& operator+=(const cdRect& r);

   // Groesse des Rechteckes
   cdSize getSize() const;
   int getWidth() const;
   int getHeight() const;

   // Koordinaten der Seiten
   int getXLeft() const
      { return lb.x; }
   int getXRight() const
      { return rt.x; }
   int getYBottom() const
      { return lb.y; }
   int getYTop() const
      { return rt.y; }

   // Eckpunkte
   cdPoint getBottomLeft() const
      { return lb; }
   cdPoint getBottomRight() const
      { return cdPoint(rt.x, lb.y); }
   cdPoint getTopLeft() const
      { return cdPoint(lb.x, rt.y); }
   cdPoint getTopRight() const
      { return rt; }

   bool isEmpty() const
      { return lb == cdPoint() && rt == cdPoint(); }
   bool isMathCoord() const
      { return lb.y <= rt.y; }
   bool isWindowCoord() const
      { return lb.y >= rt.y; }

   void makeMathCoord();
   void makeWindowCoord();

};

#endif /*__INTERFACE__*/


// Implementierung cdRect
// ===========================================================================

cdRect::cdRect(const cdPoint& l_bottom, const cdVector& size_vec)
{
   lb = l_bottom;
   rt = l_bottom + size_vec;
}

cdRect::cdRect(const cdPoint& l_bottom, const cdSize& size, bool math_coord)
{
   lb = l_bottom;

   if ( math_coord ) {
      rt = l_bottom + cdVector(size);
   } else {
      rt = l_bottom + cdVector(size.cx, -size.cy);
   }
}

cdRect operator+(const cdRect& r, const cdRect& s)
{
   int x_left = min(r.lb.x, s.lb.x);
   int x_right = max(r.rt.x, s.rt.x);

   return r.isMathCoord() ?
        cdRect(x_left, min(r.lb.y, s.lb.y), x_right, max(r.rt.y, s.rt.y))
      : cdRect(x_left, max(r.lb.y, s.lb.y), x_right, min(r.rt.y, s.rt.y));
}

cdRect& cdRect::operator+=(const cdRect& r)
{
   lb.x = min(lb.x, r.lb.x);
   rt.x = max(rt.x, r.rt.x);

   if ( isMathCoord() ) {
      lb.y = min(lb.y, r.lb.y);
      rt.y = max(rt.y, r.rt.y);
   } else {
      lb.y = max(lb.y, r.lb.y);
      rt.y = min(rt.y, r.rt.y);
   }

   return *this;
}

cdSize cdRect::getSize() const
{
   return isMathCoord() ?
      cdSize(rt - lb)
    : cdSize(rt.x - lb.x, lb.y - rt.y);
}

int cdRect::getWidth() const
{
   return rt.x - lb.x;
}

int cdRect::getHeight() const
{
   return isMathCoord() ?
      rt.y - lb.y
    : lb.y - rt.y;
}

void cdRect::makeMathCoord()
{
   if ( isWindowCoord() ) {
      int tmp = rt.y;
      rt.y = lb.y;
      lb.y = tmp;
   }
}

void cdRect::makeWindowCoord()
{
   if ( isMathCoord() ) {
      int tmp = rt.y;
      rt.y = lb.y;
      lb.y = tmp;
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdViewport
// ---------------------------------------------------------------------------
//
// Beschreibung eines Sichtrechtecks auf       y ^
// eine 2D-Szene, gegeben durch den Start-       |
// punkt (start) und einen Skalierungs-          |     +--------+
// faktor (scale). Der Startpunkt liegt          |     |        |
// bezueglich des Sichtrechteckes in der         |     |        |
// linken unteren Ecke.                          |     |        |
//                                               |     |        |
//                                               |     X--------+
//                                               |  start
//                                               |
//                                               +--------------------->
//                                             0/0                     x
//
//  cdViewport
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdViewport {

public:
   c2dPoint start;
   double scale;

   cdViewport(const c2dPoint& start = c2dPoint(0,0), double scale = 1.0)
      { cdViewport::start = start; cdViewport::scale = scale; }

   // Translation (cdViewport x c2dVector) => cdViewport
   friend cdViewport operator+(const cdViewport& vp, const c2dVector& v)
      { return cdViewport(vp.start + v, vp.scale); }
   friend cdViewport operator-(const cdViewport& vp, const c2dVector& v)
      { return cdViewport(vp.start - v, vp.scale); }

   // Translation, Zuweisung (cdViewport x c2dVector) => cdViewport
   cdViewport& operator+=(const c2dVector& v)
      { start += v;
        return *this; }
   cdViewport& operator-=(const c2dVector& v)
      { start -= v;
        return *this; }

};

#endif /*__INTERFACE__*/


