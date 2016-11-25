// ===========================================================================
// ed_device.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdDevice               - Basisklasse fuer grafische Ausgabegeraete
//         |
//         +--cdRetainedDevice   - Geraet mit Speicher fuer Grafikprimitiven
//             |
//             +--cdMemoryDevice - Reines Speichergeraet fuer Grafikprimitiven
//
// ===========================================================================

#include "draw/ed_device.hpp"
#include "draw/ed_font.hpp"
#include "base/eb_osver.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h> /* OS/2 include file      */
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
#else
   #error "Unsupported target for ECL module ed_device"
#endif




#if defined __ECL_OS2__

   //////////////////////////////////////////////////////////////////////////////
   ////                                                                      ////
   ////                      Anpassungen fuer OS/2                           ////
   ////                                                                      ////
   //////////////////////////////////////////////////////////////////////////////

   #define METRIC PU_LOMETRIC /*PU_HIMETRIC*/
   #if METRIC == PU_HIMETRIC
      #define METRIC_UNIT 100.0
   #elif METRIC == PU_LOMETRIC
      #define METRIC_UNIT 10.0
   #endif

   void DbgLastError(const char *str, ...)
   {
      va_list ap;
      va_start(ap, str);
      cBase::DbgVOut(cBase::dbgError, str, ap);
      va_end(ap);

      ULONG last_error = WinGetLastError(0);
      if ( last_error )
         cBase::DbgError(" *** Last PM error code: %08x ***", last_error);
   }

   class cPMFont {

   public:
      cPMFont(HPS hps)
         { pfm = NULL; num_fonts = 0;
           ReadFonts(hps); }
      cPMFont(const cPMFont& other)
         { pfm = NULL; memcpy(dev_font_res, other.dev_font_res, sizeof dev_font_res);
           if ( (num_fonts = other.num_fonts) > 0 ) {
              pfm = new FONTMETRICS[num_fonts];
              memcpy(pfm, other.pfm, num_fonts * sizeof(FONTMETRICS));
           }
         }
      ~cPMFont()
         { delete[] pfm; }

      void CreateFont(HPS hps, const char* face_name, const char* family, int lcid, int pointsize)
      {
         FATTRS fat;
         memset(&fat, 0, sizeof fat);
         fat.usRecordLength = sizeof fat;

         int found = FindBestFont(hps, face_name, family, pointsize);

         if ( found >= 0 ) {
            strncpy(fat.szFacename, pfm[found].szFacename, sizeof fat.szFacename);
            if ( pfm[found].fsDefn & FM_DEFN_OUTLINE ) {
               fat.lMaxBaselineExt = fat.lAveCharWidth   = 0;
               //   pfm[found].lEmHeight * pointsize * 10L / pfm[found].sNominalPointSize;
               // [pels] = [points] * [pels/m] * [m/point]
            } else {
               fat.lMaxBaselineExt = fat.lAveCharWidth   = pointsize;
            }
          //fat.idRegistry      = pfm[found].idRegistry;
            fat.lMatch          = pfm[found].lMatch;
         } else {
            strncpy(fat.szFacename, face_name, sizeof fat.szFacename);
            fat.lMaxBaselineExt =
            fat.lAveCharWidth   = pointsize;
         }

         if ( !GpiSetCharMode(hps, CM_MODE1) )
            DbgLastError("OS/2: GpiSetCharMode failed");
         if ( GpiCreateLogFont(hps, NULL, lcid, &fat) == GPI_ERROR )
            DbgLastError("OS/2: GpiCreateLogFont failed");

         SelectFont(hps, lcid, pointsize);
      }

      void SelectFont(HPS hps, int lcid, int pointsize)
      {
         double size = pointsize * 254.0 / 72.0;  // Umrechnen: Punkt -> 1/10 mm

         #undef __Exact_Point_Size_Conversion__
         #ifdef __Exact_Point_Size_Conversion__
            FIXED fsize = MAKEFIXED(int(size), long((size - floor(size)) * 65536.0));
         #else
            FIXED fsize = MAKEFIXED(int(size), 0);
         #endif
         SIZEF char_box = { fsize, fsize };

         cBase::DbgTrcApp("cPMFont::SelectFont(%08x,%d,%d,%g)", hps, lcid, pointsize, size);

         if ( !GpiSetCharMode(hps, CM_MODE1) )
            DbgLastError("OS/2: GpiSetCharMode failed");
         if ( !GpiSetCharSet(hps, lcid) )
            DbgLastError("OS/2: GpiSetCharSet failed");
         if ( !GpiSetCharBox(hps, &char_box) )
            DbgLastError("OS/2: GpiSetCharBox failed");
      }

      void DeleteFont(HPS hps, int lcid)
      {
         cBase::DbgTrcApp("cPMFont::DeleteFont(%d)", lcid);

         if ( !GpiDeleteSetId(hps, lcid) )
            DbgLastError("OS/2: GpiDeleteSetId failed");
      }

   private:
      LONG dev_font_res[2];
      FONTMETRICS *pfm;
      LONG num_fonts;

      void ReadFonts(HPS hps)
      {
         LONG lFontCnt = 0L;
         delete[] pfm; num_fonts = 0;

         DevQueryCaps(GpiQueryDevice(hps), CAPS_HORIZONTAL_FONT_RES, 2L, dev_font_res);
         num_fonts = GpiQueryFonts(hps, QF_PUBLIC, NULL, &lFontCnt, sizeof(FONTMETRICS), NULL);
         pfm = new FONTMETRICS[num_fonts];
         GpiQueryFonts(hps, QF_PUBLIC, NULL, &num_fonts, sizeof(FONTMETRICS), pfm);
      }

      int FindBestFont(HPS hps, const char *face_name, const char *family, int pointsize)
      {
         int cmp_len = -1;
         if ( !family )
            family = face_name;
         if ( !face_name )
            face_name = family;

         do {
            cBase::DbgTrcApp("\n\n---------cPMFont::FindFont %d.%s compare to %d", pointsize, face_name, cmp_len);
            for ( int i = 0; i < num_fonts; i++ ) {
               if ( (pfm[i].fsDefn & FM_DEFN_OUTLINE) ||
                     pfm[i].sXDeviceRes == dev_font_res[0] &&
                     pfm[i].sYDeviceRes == dev_font_res[1] )
               {
                  if ( cmp_len == -1 && 0==stricmp(face_name, pfm[i].szFacename)
                    || cmp_len ==  0 && 0==stricmp(family, pfm[i].szFamilyname)
                    || cmp_len  >  0 && 0==strnicmp(family, pfm[i].szFamilyname, cmp_len ) )
                  {
                     if ( pfm[i].fsDefn & FM_DEFN_OUTLINE) {
                        cBase::DbgTrcApp(" **outline font %s found**", pfm[i].szFacename );
                        return i;
                     } else if ( pfm[i].sNominalPointSize >= pointsize*10 ) {
                        cBase::DbgTrcApp(" %s **matched**\n", pfm[i].szFacename );
                        return i;
                     }
                  }
               }
            }

            switch ( cmp_len ) {
            case -1: cmp_len = 0; break;              // Suche nach exaktem face_name
            case 0:  cmp_len = strlen(family); break; // Suche nach family
            case 1:  return -1;                       // kein passender Font gefunden
            default: cmp_len /= 2; break;
            }
         } while ( true );
      }

   };

#elif defined __ECL_W32__

   void DbgLastError(const char *str, ...)
   {
      va_list ap;
      va_start(ap, str);
      cBase::DbgVOut(cBase::dbgError, str, ap);
      va_end(ap);

      //ULONG last_error = WinGetLastError(0);
      //if ( last_error )
      //   cBase::DbgError(" *** Last PM error code: %08x ***", last_error);
   }

   #include <math.h>

   void MyArcTo(CDC *dc, double x, double y, double r1, double r2, double a1, double a2)
   {
      // emulate arc, taken from g2 - graphics library
      double a, da;
      int N, i;
      N=(int)fabs(deg(a2-a1))+8;
      a=a1;
      da=((a2>a1)? (a2-a1):rad(360.)-(a1-a2))/(N-1);
      POINT *pt = new POINT[N];
      for (i=0;i<N;i++) {
         pt[i].x=(LONG)(x+r1*cos(a+i*da));
         pt[i].y=(LONG)(y+r2*sin(a+i*da));
      }
      dc->PolylineTo(pt, N);        // using poly_line
      delete[] pt;
   }

   void MyArcTo(CDC *dc, const c2dArc& a)
   {
      double r = a.getRadius();
      double a1 = a.getStartAngle();
      double a2 = a.getEndAngle();

      if ( a.dir < 0 ) { // CW
         MyArcTo(dc, a.m.x, a.m.y, r, r, a1+rad(360.), a2);
      } else { // CCW
         MyArcTo(dc, a.m.x, a.m.y, r, r, a1, a2);
      }
   }

   void MyArcTo(CDC *dc, int x1, int y1, int x2, int y2, int sx, int sy, int ex, int ey, int dir)
   {
      // Das den Bogen "umschliessende Rechteck" ist bei Win32 immer
      // ein Pixel groesser (Breite+1, Hoehe+1) als noetig, also x2,y2 korrigieren:

#undef __Correct_In_LOMETRIC__
#ifdef __Correct_In_LOMETRIC__
      x2++; y2--;
#else
      CPoint p2(x2,y2); dc->LPtoDP(&p2);
      p2.x++; p2.y++; dc->DPtoLP(&p2);
      x2 = p2.x; y2 = p2.y;
#endif

      // Der Aufruf der korrekten Arc-Funktion ist in hoechstem Masse
      // abhaengig vom verwendeten Betriebssystem... (So muss es sein!)

      if ( cOsVersion::getVersion() == 95 ) {
         // Win95: SetArcDirection unsupported, ArcTo unsupported
         if ( dir < 0 ) {
            dc->Arc(x1, y1, x2, y2, ex, ey, sx, sy);
         } else {
            dc->Arc(x1, y1, x2, y2, sx, sy, ex, ey);
         }
         dc->MoveTo(ex, ey);
      } else if ( cOsVersion::getVersion() <= 98 ) {
         // Win98: ArcTo unsupported
         dc->SetArcDirection(dir < 0 ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE);
         dc->Arc(x1, y1, x2, y2, sx, sy, ex, ey);
         dc->MoveTo(ex, ey);
      } else {
         // WinNT4, Win2000, XP: Nothing unsupported
         dc->SetArcDirection(dir < 0 ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE);
         //dc->MoveTo(sx, sy);
         dc->ArcTo(x1, y1, x2, y2, sx, sy, ex, ey);
         dc->LineTo(ex, ey);
      }
   }

   void MyArcTo(CDC *dc, bool in_path, int dir,
                const cdPoint& bl, const cdPoint& tr,
                const cdPoint& s, const cdPoint& e)
   {
      if ( cOsVersion::getVersion() <= 98 && in_path ) {
         // Win95/98: Arc in Paths unsupported
         c2dArc a(c2dPoint(s.x, s.y),
                  c2dPoint(e.x, e.y),
                  c2dPoint(double(bl.x+tr.x)/2.0, double(bl.y+tr.y)/2.0),
                  dir);
         MyArcTo(dc, a);
      } else {
         // WinNT4, Win2000, XP or not in_path
         MyArcTo(dc, bl.x, bl.y, tr.x, tr.y, s.x, s.y, e.x, e.y, dir);
      }
   }

   void MyArcTo(CDC *dc, bool in_path, int dir,
                const cdPoint& bl, const cdPoint& /*tr*/,
                const cdPoint& br, const cdPoint& tl,
                const cdPoint& s, const cdPoint& e)
   {
      // TBD: Provisorische Auswertung durch korrekte Ersetzen!
      // TBD: Wie soll ein "verbogenes Ei" gemalt werden??!?

      c2dPoint bl_2d(bl.x, bl.y);
      c2dVector b(c2dPoint(br.x, br.y) - bl_2d), l(c2dPoint(tl.x, tl.y) - bl_2d);
      c2dPoint c = bl_2d + b/2.0 + l/2.0;
      double r = b.getLength() / 2.0;

      if ( cOsVersion::getVersion() <= 98 && in_path ) {
         // Win95/98: Arc in Paths unsupported
         c2dArc a(c2dPoint(s.x, s.y), c2dPoint(e.x, e.y), c, dir);
         MyArcTo(dc, a);
      } else {
         // WinNT4, Win2000, XP or not in_path
         MyArcTo(dc, int(c.x-r), int(c.y-r), int(c.x+r), int(c.y+r),
                     int(s.x), int(c.y), int(e.x), int(e.y), dir);
      }
   }

#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"
#include "draw/ed_context.hpp"
#include "draw/ed_store.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdDevice
// ---------------------------------------------------------------------------
//
// Basisklasse fuer grafische Ausgabegeraete
//
// Definiert ein logisches Koordinatensystem (LOGICAL), das Operationen
// zur Darstellung von grafischen Objekten in logischen Koordinaten
// bietet.
//
//   ^    +----+                 +----------->                 +----------->
//   |    |    |                 |    +----+                   |    +----+
//   |    |    |                 |    |    |                   |    |    |
//   |    |    |                 |    |    |                   |    |    |
//   |    |    |    ==========>  |    |    |    ===========>   |    |    |
//   |    +----+                 |    |    |                   |    |    |
//   +----------->               V    +----+                   V    +----+
//
//   PAGE                        LOGICAL                       DEVICE
//   Transformierte              Logische                      Geraete-
//   Koordinaten                 Koordinaten                   Koordinaten
//
//   Physikalisch [mm]           Logisch [*?]                  Pixel
//   double                      long                          long
//   +x => rechts                +x => *?                      +x => rechts
//   +y => oben                  +y => *?                      +y => unten
//
// Anmerkungen:
//
//  - Die Bedeutung der Koordinaten und die Orientierung der Achsen im
//    LOGICAL-System sind abhaengig vom aktuelle Mapping-Mode (vgl. *?):
//
//                      | +x     | +y     | Einheit
//       ---------------+--------+--------+-----------
//        mmDirect      | rechts | unten  | Pixel
//        mmLoMetric    | rechts | oben   | 1/10 mm
//        mmHiMetric    | rechts | oben   | 1/100 mm
//        mmIsotropic   |  - benutzerspezifisch -
//        mmAnisotropic |  - benutzerspezifisch -
//
//  cBase
//   +--cdDevice
//
// ===========================================================================

class cdMemoryDevice;
class STOCK;
class CDC;

class __ECL_DLLEXPORT__ cdDevice : public cBase {

public:

   // Konstruktor
   inline cdDevice() { init(); }
   // Copy-Konstruktor
   inline cdDevice(const cdDevice& other) { init(other); }
   // Destruktor
   virtual ~cdDevice();


   // Allgemeines
   // ===========

   // Alle Einstellung auf Standardwerte zuruecksetzen
   virtual void reset();
   // Kontext an Ausgabegeraet binden
   virtual void bindContext(cdContext *ctxt);
   // Gebundenen Kontext erfragen
   inline void *getBoundContext() const
      { return context; }


   // Skalierung
   // ==========

   enum MAP_MODE {   // Abbildung zwischen logischen und Geraetekoordinaten:
      mmDirect,      //  - Direkte Abbildung auf Geraetekoordinaten
      mmLoMetric,    //  - Abbildung 1/10 mm -> Geraetekoordinaten
      mmHiMetric,    //  - Abbildung 1/100 mm -> Geraetekoordinaten
      mmIsotropic,   //  - Benutzerspezifische Abbildung (Seitenverhaeltnis 1:1)
      mmAnisotropic  //  - Benutzerspezifische Abbildung (freiers Seitenverhaeltnis)
   };

   // Abbildung zwischen logischen und Geraetekoordinaten einstellen
   void setMapMode(MAP_MODE mode);
   // Aktuelle Abbildung zwischen logischen und Geraetekoordinaten erfragen
   inline MAP_MODE getMapMode() const
      { return map_mode; }

   // Mit den folgenden Funktionen wird die Abbidlung zwischen logischen und Geraete-
   // koordinaten in den Mapping-Modi mmIsotropic und mmAnisotropic eingestellt:

   // Ursprung des logischen Koordinatensystems festlegen (in logischen Koordinaten)
   void setLogicalOrigin(int x, int y);
   // Ursprung des logischen Koordinatensystems ueber cdPoint festlegen (in logischen Koordinaten)
   void setLogicalOrigin(const cdPoint& origin);
   // Groesse des logischen Koordinatensystems festlegen (in logischen Koordinaten)
   void setLogicalExtend(int cx, int cy);
   // Groesse des logischen Koordinatensystems ueber cdSize festlegen (in logischen Koordinaten)
   void setLogicalExtend(const cdSize& size);

   // Ursprung des Geraetekoordinatensystems festlegen (in Geraetekoordinaten)
   void setDeviceOrigin(int x, int y);
   // Ursprung des Geraetekoordinatensystems ueber cdPoint festlegen (in Geraetekoordinaten)
   void setDeviceOrigin(const cdPoint& origin);
   // Groesse des Geraetekoordinatensystems festlegen (in Geraetekoordinaten)
   void setDeviceExtend(int cx, int cy);
   // Groesse des Geraetekoordinatensystems ueber cdSize festlegen (in Geraetekoordinaten)
   void setDeviceExtend(const cdSize& size);

   // Ursprung des logischen Koordinatensystems ermitteln
   cdPoint getLogicalOrigin() const;
   // Groesse des logischen Koordinatensystems ermitteln
   cdSize getLogicalExtend() const;
   // Ursprung des Geraetekoordinatensystems ermitteln
   cdPoint getDeviceOrigin() const;
   // Groesse des Geraetekoordinatensystems ermitteln
   cdSize getDeviceExtend() const;


   // Clipping
   // ========

   // Schnittmenge zwischen aktuellem Clip-Bereich und 'rect' bilden
   void intersectClipRect(const cdRect& rect);
   // Kleinstes umschliessendes Rechteck um aktuellen Clip-Bereich ermitteln
   cdRect getClipBox() const;
   // Liegt der Punkt 'point' innerhalb des aktuellen Clip-Bereichs?
   bool isVisible(const cdPoint& point);
   // Liegt irgend ein Teil von 'rect' innerhalb des aktuellen Clip-Bereichs?
   bool isVisible(const cdRect& rect);


   // Druckkontrolle
   // ==============

   // Seitenvorschub einfuegen
   virtual void newFrame();
   // Ausgabe in neues Dokument beginnen
   virtual void startDoc(const char *doc_name);
   // Ausgabe in Dokument beenden
   virtual long endDoc();
   // Ausgabe in Dokument abbrechen
   virtual void abortDoc();


   // Zeichenattribute (OS-spezifische Werte)
   // =======================================

   // Vordergrundfarbe setzen (erwartet OS-spezifische Werte)
   virtual void setColor(long color);
   // Hintergrundfarbe setzen (erwartet OS-spezifische Werte)
   virtual void setBackColor(long color);
   // Fuellfarbe setzen (erwartet OS-spezifische Werte)
   virtual void setFillColor(long fillcolor);
   // Fuellpattern setzen (erwartet OS-spezifische Werte)
   virtual void setFillPattern(char *pattern);
   // Linienstil setzen (erwartet OS-spezifische Werte)
   virtual void setLineStyle(long linestyle);
   // Linienbreite setzen (erwartet OS-spezifische Werte)
   virtual void setLineWidth(long linewidth);
   // Linienmuster setzen (erwartet OS-spezifische Werte)
   virtual void setPattern(long pattern);
   // Vordergrund-Mischmodus setzen (erwartet OS-spezifische Werte)
   virtual void setForeMix(long mix);
   // Hintergrund-Mischmodus setzen (erwartet OS-spezifische Werte)
   virtual void setBackMix(long mix);
   // Textausrichtung setzen (erwartet OS-spezifische Werte)
   virtual void setTextAlign(long horiz, long vert);
   // Zeichenwinkel fuer Texte setzen (erwartet OS-spezifische Werte)
   virtual void setTextAngle(long dir_x, long dir_y);


   // Zeichenattribute (ECL-spezifische Werte)
   // ========================================

   // Vordergrundfarbe setzen
   inline void setColor(const cdColor& color)
      { setColor(color.getOsVal()); }
   // Hintergrundfarbe setzen
   inline void setBackColor(const cdColor& color)
      { setBackColor(color.getOsVal()); }
   // Fuellfarbe setzen
   inline void setFillColor(const cdColor& fillcolor)
      { setFillColor(fillcolor.getOsVal()); }
   // Linienstil setzen
   inline void setLineStyle(const cdLineStyle& linestyle)
      { setLineStyle(linestyle.getOsVal()); }
   // Linienmuster setzen
   inline void setPattern(const cdPattern& pattern)
      { setPattern(pattern.getOsVal()); }
   // Vordergrund-Mischmodus setzen
   inline void setForeMix(const cdMix& mix)
      { setForeMix(mix.getOsVal()); }
   // Hintergrund-Mischmodus setzen
   inline void setBackMix(const cdMix& mix)
      { setBackMix(mix.getOsVal()); }
   // Textausrichtung setzen
   inline void setTextAlign(const cdAlign& horiz, const cdAlign& vert)
      { setTextAlign(horiz.getOsVal(), vert.getOsVal()); }


   // Schriftart erzeugen und ID ermitteln
   virtual long createFont(const char *facename, int pointsize);
   // Schriftart ueber ID auswaehlen
   virtual void selectFont(long font_id);
   // Schriftart freigeben
   virtual void deleteFont(long font_id);

   // Setze RECT fuer kuenftige Operationen auf 'bottom_left', 'top_right'
   virtual void setRect(const cdPoint& bottom_left, const cdPoint& top_right);
   // Setze XRECT fuer kuenftige Operationen auf 'bottom_right', 'top_left'
   virtual void setXRect(const cdPoint& bottom_right, const cdPoint& top_left);

   // Bewege CURSOR auf Position 'pos'
   virtual void moveTo(const cdPoint& pos);

   // Punkt an Position 'point' zeichnen
   virtual void drawPoint(const cdPoint& point);
   // Gerade von CURSOR bis 'line_end'
   virtual void drawLine(const cdPoint& line_end);
   // Kreis um 'center' mit 'radius'
   virtual void drawCircle(const cdPoint& center, long radius);
   // Ellipse innerhalb von RECT/XRECT
   virtual void drawEllipse();
   // Rechteck wie durch RECT/XRECT definiert
   virtual void drawRect();
   // Bogen im Uhrzeigersinn innerhalb RECT/XRECT von CURSOR bis 'arc_end'
   virtual void drawArcCW(const cdPoint& arc_end);
   // Bogen gegen Uhrzeigersinn innerhalb RECT/XRECT von CURSOR bis 'arc_end'
   virtual void drawArcCCW(const cdPoint& arc_end);
   // Text ab Cursor
   virtual void drawText(const char *txt, int length = -1);
   // Memory-Device an Position 'pos' einspielen
   virtual void drawFrom(const cdMemoryDevice *memory_device, const cdPoint& pos);

   // Beginn eines zu fuellenden Bereichs markieren
   virtual void beginArea(bool boundary);
   // Ende eines zu fuellenden Bereichs markieren
   virtual void endArea();

   // Durchschnittliche Zeichengroesse der aktuellen Schriftart erfragen
   void queryAvgCharSize(long& cx, long& cy) const;
   // Exakte Groesse des Strings 'txt' in der aktuellen Schriftart erfragen
   cdSize queryTextSize(const char *txt, int length = -1) const;
   // Exakte Breite des Strings 'txt' in der aktuellen Schriftart erfragen
   long queryTextWidth(const char *txt, int length = -1) const;
   // Exakte Hoehe des Strings 'txt' in der aktuellen Schriftart erfragen
   long queryTextHeight(const char *txt, int length = -1) const;

   // Bewege CURSOR auf Position 'x','y'
   inline void moveTo(int x, int y)
      { moveTo(cdPoint(x, y)); }
   // Punkt an Position 'x','y' zeichnen
   inline void drawPoint(int x, int y)
      { drawPoint(cdPoint(x, y)); }
   // Gerade von CURSOR bis 'x','y'
   inline void drawLine(int x, int y)
      { drawLine(cdPoint(x, y)); }
   // Kreis um 'x','y' mit 'radius'
   inline void drawCircle(int x, int y, long radius)
      { drawCircle(cdPoint(x, y), radius); }


   // Koordinatenumwandlung
   // =====================

   // PAGE -> LOGICAL Transformation eines Punktes
   cdPoint convPageToLog(const c2dPoint& p) const;
   // PAGE -> LOGICAL Transformation eines Vektors
   cdVector convPageToLog(const c2dVector& v) const;
   // PAGE -> LOGICAL Transformation eines Rechtecks
   cdRect convPageToLog(const c2dBox& b) const;

   // LOG -> PAGE Transformation eines Punktes
   c2dPoint convLogToPage(const cdPoint& p) const;
   // LOG -> PAGE Transformation eines Vektors
   c2dVector convLogToPage(const cdVector& v) const;
   // LOG -> PAGE Transformation eines Rechtecks
   c2dBox convLogToPage(const cdRect& r) const;

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

   // Einfacher Koordinatensatz (RECT = Achsparalleles Zeichenrechteck)
   cdPoint rect_bottom_left;     // - Unten links
   cdPoint rect_top_right;       // - Oben rechts
   // Erweiterter Koordinatensatz (XRECT = Nicht-achsparalleles Zeichenrechteck)
   cdPoint xrect_bottom_right;   // - Unten rechts
   cdPoint xrect_top_left;       // - Oben links

   // Ist XRECT aktiv?
   bool isXRect() const;

   #if defined __ECL_W32__
      void __setDC(CDC *dc);
      CDC *__getDC() const;
   #endif

private:

   #if defined __ECL_OS2__
      static unsigned long hab;
      unsigned long hdc;
      unsigned long hps;
      unsigned long font_ids;
      void *fonts;
      int font_sizes[32];
   #elif defined __ECL_W32__
      CDC *dc;
      STOCK *stock;
      cString font_names[32];
      int font_sizes[32];
   #endif

   // Intern: Initialisierung
   void init();
   // Intern: Initialisierung ueber anderes cdDevice
   void init(const cdDevice& other);

   // Aktuelle Abbildung zwischen logischen und Geraetekoordinaten
   MAP_MODE map_mode;
   // Zeiger auf aktuell an das Geraet gebundenen Kontext
   cdContext *context;

};

#endif /*__INTERFACE__*/


// Implementierung cdDevice
// ===========================================================================

#define __Trace_Device_Calls__
#if defined __Trace_Device_Calls__ && __ECL_DEBUG__ > 0
   #define TRACEDEVICE(p) DbgTrcApp p
#else
   #define TRACEDEVICE(p)
#endif

#if defined __ECL_OS2__

   unsigned long cdDevice::hab = 0;

#elif defined __ECL_W32__

   enum CHANGE_MASKS {
      // pen
      CM_PEN_STYLE      = 0x0001,
      CM_PEN_WIDTH      = 0x0002,
      CM_PEN_COLOR      = 0x0004,
      CM_PEN_ALL        = 0x0007,
      // brush
      CM_BRUSH_STYLE    = 0x0010,
      CM_BRUSH_COLOR    = 0x0020,
      CM_BRUSH_PATTERN  = 0x0040,
      CM_BRUSH_ALL      = 0x0070,
      // mix
      CM_MIX_FG         = 0x0100,
      CM_MIX_BK         = 0x0200,
      CM_MIX_ALL        = 0x0300,
      // others
      CM_FONT           = 0x1000,
      CM_BK_COLOR       = 0x2000,
      CM_TXT_ALIGN      = 0x4000
   };

   enum PATH_MASK {
      PM_PATH_ACTIVE    = 0x0001,   // Pfad aktiv (zwischen beginArea...endArea)
      PM_STROKE         = 0x0002,   // Rahmen zeichnen
      PM_FILL           = 0x0004,   // Fuellen
      PM_STROKE_FILL    = 0x0006    // Fuellen und Rahmen zeichnen
   };

   class STOCK {
   public:

      // change mask
      int change_mask;

      // path
      int path_mask;

      // pen
      long pen_style;
      long pen_width;
      long pen_color;
      CPen pen;
      void setPen(CDC *dc);
      void releasePen(CDC *dc);

      // brush
      long brush_style;
      long brush_color;
      char brush_pattern[8];
      CBitmap bmp;
      CBrush brush;
      void setBrush(CDC *dc);
      void releaseBrush(CDC *dc);

      // mix
      long mix_fg;
      long mix_bk;
      void setMix(CDC *dc);

      // font
      cString facename;
      int pointsize;
      cdFont font;
      void setFont(CDC *dc);
      void releaseFont(CDC *dc);

      // background color
      long bk_color;

      // text align
      long txt_align;
      void setTxtAlign(CDC *dc);

   };

   void STOCK::setPen(CDC *dc)
   {
      if ( change_mask & CM_PEN_ALL ) {
         releasePen(dc);
         pen.CreatePen(pen_style, pen_width, pen_color);
         dc->SelectObject(&pen);
         dc->SetTextColor(pen_color);
         change_mask &= ~CM_PEN_ALL;
      }
      if ( change_mask & CM_BK_COLOR ) {
         dc->SetBkColor(bk_color);
         change_mask &= ~CM_BK_COLOR;
      }
   }

   void STOCK::releasePen(CDC *dc)
   {
      dc->SelectStockObject(BLACK_PEN);
      pen.DeleteObject();
   }

   void STOCK::setBrush(CDC *dc)
   {
      if ( change_mask & CM_BRUSH_ALL ) {
         releaseBrush(dc);
         if ( change_mask & CM_BRUSH_PATTERN ) {
            WORD bits[8];
            for ( int i = 0 ; i < 8 ; i++ )
               bits[i] = (WORD)~brush_pattern[i];
            bmp.DeleteObject();
            bmp.CreateBitmap(8, 8, 1, 1, bits);
            brush.CreatePatternBrush(&bmp);
            dc->SelectObject(&brush);
            dc->SetTextColor(brush_color);
         } else if ( brush_style == -1 /*NULL*/ ) {
            dc->SelectStockObject(NULL_BRUSH);
         } else if ( brush_style == -2 /*BLANK*/ ) {
            dc->SelectStockObject(WHITE_BRUSH);
         } else if ( brush_style == -3 /*SOLID*/ ) {
            brush.CreateSolidBrush(brush_color);
            dc->SelectObject(&brush);
         } else {
            brush.CreateHatchBrush(brush_style, brush_color);
            dc->SelectObject(&brush);
         }
         change_mask &= ~CM_BRUSH_ALL;
      }
   }

   void STOCK::releaseBrush(CDC *dc)
   {
      dc->SelectStockObject(WHITE_BRUSH);
      brush.DeleteObject();
   }

   void STOCK::setFont(CDC *dc)
   {
      if ( change_mask & CM_FONT ) {
         dc->SelectStockObject(SYSTEM_FONT);
         font.create(facename, pointsize , 254./72.);
         dc->SelectObject(*(CFont*)ccdFont::getFont(font));
         change_mask &= ~CM_FONT;
      }
   }

   void STOCK::releaseFont(CDC *dc)
   {
      dc->SelectStockObject(SYSTEM_FONT);
      font.destroy();
   }

   void STOCK::setMix(CDC *dc)
   {
      if ( change_mask & CM_MIX_FG ) {
         dc->SetROP2(mix_fg);
         change_mask &= ~CM_MIX_FG;
      }
      if ( change_mask & CM_MIX_BK ) {
         dc->SetBkMode(mix_bk);
         change_mask &= ~CM_MIX_BK;
      }
   }

   void STOCK::setTxtAlign(CDC *dc)
   {
      if ( change_mask & CM_TXT_ALIGN ) {
         dc->SetTextAlign(txt_align);
         change_mask &= ~CM_TXT_ALIGN;
      }
   }

#endif

void cdDevice::init()
{
   map_mode = mmLoMetric;
   context = 0;

   #if defined __ECL_OS2__
      hdc = 0;
      hps = 0;
      font_ids = 0;
      fonts = NULL;
      for ( int i = 0 ; i < sizeof font_sizes / sizeof font_sizes[0] ; i++ )
         font_sizes[i] = 0;
   #elif defined __ECL_W32__
      dc = 0;
      stock = new STOCK;
      stock->change_mask = 0;
      stock->path_mask = 0;
      stock->pen_style = PS_SOLID;
      stock->pen_width = 1;
      stock->pen_color = RGB(0,0,0);
      stock->brush_style = -2;
      stock->brush_color = RGB(0,0,0);
      stock->mix_fg = R2_COPYPEN;
      stock->mix_bk = OPAQUE;
      stock->bk_color = RGB(255,255,255);
      stock->txt_align = TA_LEFT | TA_TOP | TA_NOUPDATECP;
      for ( int i = 0 ; i < sizeof font_sizes / sizeof font_sizes[0] ; i++ )
         font_sizes[i] = 0;
   #endif
}

void cdDevice::init(const cdDevice& other)
{
   map_mode = mmLoMetric;
   context = 0;

   #if defined __ECL_OS2__
      hdc = other.hdc;
      hps = other.hps;
      font_ids = other.font_ids;
      fonts = new cPMFont(*((cPMFont *)other.fonts));
      for ( int i = 0 ; i < sizeof font_sizes / sizeof font_sizes[0] ; i++ )
         font_sizes[i] = other.font_sizes[i];
   #elif defined __ECL_W32__
      dc = other.dc;
      stock = new STOCK;
      stock->pen_style = other.stock->pen_style;
      stock->pen_width = other.stock->pen_width;
      stock->pen_color = other.stock->pen_color;
      stock->brush_style = other.stock->brush_style;
      stock->brush_color = other.stock->brush_color;
      stock->mix_fg = other.stock->mix_fg;
      stock->mix_bk = other.stock->mix_bk;
      stock->bk_color = RGB(255,255,255);
      stock->txt_align = TA_LEFT | TA_TOP | TA_NOUPDATECP;
      stock->change_mask = CM_PEN_ALL
                         | CM_BRUSH_STYLE | CM_BRUSH_COLOR
                         | CM_MIX_ALL
                         | CM_FONT
                         | CM_BK_COLOR
                         | CM_TXT_ALIGN;
      stock->path_mask = 0;
      for ( int i = 0 ; i < sizeof font_sizes / sizeof font_sizes[0] ; i++ ) {
         font_sizes[i] = other.font_sizes[i];
         font_names[i] = other.font_names[i];
      }
   #endif
}

cdDevice::~cdDevice()
{
   #if defined __ECL_OS2__
      delete (cPMFont *)fonts;
   #elif defined __ECL_W32__
      delete stock;
   #endif
}


// Allgemeines
// ===========

void cdDevice::reset()
{
   TRACEDEVICE(("cdDevice::reset()"));

   map_mode = mmLoMetric;

   #if defined __ECL_OS2__
      if ( !GpiResetPS(hps, GRES_ALL) )
         DbgLastError("OS/2: GpiResetPS failed");
      GpiSetDrawingMode(hps, DM_DRAW);
      GpiSetColor(hps, CLR_BLACK);
   #elif defined __ECL_W32__
      if ( dc ) {
         dc->SetBkColor(RGB(255,255,255));
         dc->SetPolyFillMode(ALTERNATE);
         dc->SetROP2(R2_COPYPEN);
         dc->SetBkMode(OPAQUE);
         dc->SetTextColor(RGB(0,0,0));
      }
      // Init STOCK
      stock->facename = "Roman";
      stock->pointsize = 12;
      stock->pen_style = PS_SOLID;
      stock->pen_width = 1;
      stock->pen_color = RGB(0,0,0);
      stock->brush_style = -2;
      stock->brush_color = RGB(0,0,0);
      stock->mix_fg = R2_COPYPEN;
      stock->mix_bk = OPAQUE;
      stock->bk_color = RGB(255,255,255);
      stock->txt_align = TA_LEFT | TA_TOP | TA_NOUPDATECP;
      stock->change_mask |= CM_PEN_ALL
                         |  CM_BRUSH_STYLE | CM_BRUSH_COLOR
                         |  CM_MIX_ALL
                         |  CM_BK_COLOR
                         |  CM_FONT
                         |  CM_TXT_ALIGN;
   #endif
}

void cdDevice::bindContext(cdContext *ctxt)
{
   context = ctxt;

   #if defined __ECL_W32__
      __setDC(ctxt != 0 ? (CDC*)ccdContext::getContext(ctxt) : 0);
   #endif
}

#if defined __ECL_W32__

   void cdDevice::__setDC(CDC *new_dc)
   {
      if ( new_dc != dc ) {
         if ( dc != 0 ) {
            stock->releasePen(dc);
            stock->releaseBrush(dc);
            stock->releaseFont(dc);
         }
         dc = new_dc;
         if ( new_dc != 0 ) {
            reset();
         }
      }
   }

   CDC * cdDevice::__getDC() const
   {
      return dc;
   }

#endif


// Skalierung
// ==========

void cdDevice::setMapMode(MAP_MODE mode)
{
   TRACEDEVICE(("cdDevice::setMapMode(%d)", mode));

   map_mode = mode;

   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      switch ( mode ) {
      case mmDirect:       dc->SetMapMode(MM_TEXT); break;
      case mmLoMetric:     dc->SetMapMode(MM_LOMETRIC); break;
      case mmHiMetric:     dc->SetMapMode(MM_HIMETRIC); break;
      case mmIsotropic:    dc->SetMapMode(MM_ISOTROPIC); break;
      case mmAnisotropic:  dc->SetMapMode(MM_ANISOTROPIC); break;
      }
   #endif
}

void cdDevice::setLogicalOrigin(int x, int y)
{
   #if defined __ECL_W32__
      dc->SetWindowOrg(x, y);
   #endif
}

void cdDevice::setLogicalOrigin(const cdPoint& origin)
{
   setLogicalOrigin(origin.x, origin.y);
}

void cdDevice::setLogicalExtend(int cx, int cy)
{
   #if defined __ECL_W32__
      dc->SetWindowExt(cx, cy);
   #endif
}

void cdDevice::setLogicalExtend(const cdSize& size)
{
   setLogicalExtend(size.cx, size.cy);
}

void cdDevice::setDeviceOrigin(int x, int y)
{
   #if defined __ECL_W32__
      dc->SetViewportOrg(x, y);
   #endif
}

void cdDevice::setDeviceOrigin(const cdPoint& origin)
{
   setDeviceOrigin(origin.x, origin.y);
}

void cdDevice::setDeviceExtend(int cx, int cy)
{
   #if defined __ECL_W32__
      dc->SetViewportExt(cx, cy);
   #endif
}

void cdDevice::setDeviceExtend(const cdSize& size)
{
   setDeviceExtend(size.cx, size.cy);
}

cdPoint cdDevice::getLogicalOrigin() const
{
   #if defined __ECL_W32__
      CPoint origin = dc->GetWindowOrg();
      return cdPoint(origin.x, origin.y);
   #endif
}

cdSize cdDevice::getLogicalExtend() const
{
   #if defined __ECL_W32__
      CSize size = dc->GetWindowExt();
      return cdSize(size.cx, size.cy);
   #endif
}

cdPoint cdDevice::getDeviceOrigin() const
{
   #if defined __ECL_W32__
      CPoint origin = dc->GetViewportOrg();
      return cdPoint(origin.x, origin.y);
   #endif
}

cdSize cdDevice::getDeviceExtend() const
{
   #if defined __ECL_W32__
      CSize size = dc->GetViewportExt();
      return cdSize(size.cx, size.cy);
   #endif
}


// Clipping
// ========

void cdDevice::intersectClipRect(const cdRect& rect)
{
   #if defined __ECL_W32__
      dc->IntersectClipRect(rect.lb.x, rect.rt.y, rect.rt.x, rect.lb.y);
   #endif
}

cdRect cdDevice::getClipBox() const
{
   #if defined __ECL_W32__
      RECT mfc_rect;
      dc->GetClipBox(&mfc_rect);
      return cdRect(mfc_rect.left, mfc_rect.bottom, mfc_rect.right, mfc_rect.top);
   #endif
}

bool cdDevice::isVisible(const cdPoint& point)
{
   #if defined __ECL_W32__
      return !!dc->PtVisible(point.x, point.y);
   #endif
}

bool cdDevice::isVisible(const cdRect& rect)
{
   #if defined __ECL_W32__
      CRect mfc_rect(rect.lb.x, rect.rt.y, rect.rt.x, rect.lb.y);
      return !!dc->RectVisible(mfc_rect);
   #endif
}


// Druckkontrolle
// ==============

void cdDevice::newFrame()
{
   TRACEDEVICE(("cdDevice::newFrame()"));

   #if defined __ECL_OS2__
      LONG rc = DevEscape(hdc, DEVESC_NEWFRAME, 0, 0, 0, 0);
      switch ( rc ) {
      case DEVESC_ERROR:          DbgLastError("OS/2: DevEscape(NEWFRAME) failed"); break;
      case DEVESC_NOTIMPLEMENTED: /*DbgLastError("OS/2: DevEscape(NEWFRAME) not implemented");*/ break;
      }
   #elif defined __ECL_W32__
      if ( dc->IsPrinting() ) {
         __ECL_ASSERT1__(dc->EndPage() >= 0);
         __ECL_ASSERT1__(dc->StartPage() >= 0);
      }
   #endif
}

void cdDevice::startDoc(const char *doc_name)
{
   TRACEDEVICE(("cdDevice::startDoc(%s)", doc_name));

   #if defined __ECL_OS2__
      LONG rc = DevEscape(hdc, DEVESC_STARTDOC, strlen(doc_name), (PBYTE)doc_name, NULL, NULL);
      switch ( rc ) {
      case DEVESC_ERROR:          DbgLastError("OS/2: DevEscape(STARTDOC) failed"); break;
      case DEVESC_NOTIMPLEMENTED: DbgLastError("OS/2: DevEscape(STARTDOC) not implemented"); break;
      }
   #elif defined __ECL_W32__
      DOCINFO docinfo;
      memset(&docinfo, 0, sizeof(docinfo));
      docinfo.cbSize = sizeof(docinfo);
      docinfo.lpszDocName = _T(doc_name);
      __ECL_ASSERT1__(dc->StartDoc(&docinfo) >= 0);
      __ECL_ASSERT1__(dc->StartPage() >= 0);
   #endif
}

long cdDevice::endDoc()
{
   TRACEDEVICE(("cdDevice::endDoc()"));

   #if defined __ECL_OS2__
      USHORT job_id;
      LONG rc = DevEscape(hdc, DEVESC_ENDDOC, sizeof job_id, (PBYTE)&job_id, NULL, NULL);
      switch ( rc ) {
      case DEVESC_ERROR:          DbgLastError("OS/2: DevEscape(ENDDOC) failed"); break;
      case DEVESC_NOTIMPLEMENTED: DbgLastError("OS/2: DevEscape(ENDDOC) not implemented"); break;
      }
      return (long)job_id;
   #elif defined __ECL_W32__
      __ECL_ASSERT1__(dc->EndPage() >= 0);
      long id = dc->EndDoc();
      __ECL_ASSERT1__(id >= 0);
      return id;
   #endif
}

void cdDevice::abortDoc()
{
   TRACEDEVICE(("cdDevice::abortDoc()"));

   #if defined __ECL_OS2__
      LONG rc = DevEscape(hdc, DEVESC_ABORTDOC, 0, NULL, NULL, NULL);
      switch ( rc ) {
      case DEVESC_ERROR:          DbgLastError("OS/2: DevEscape(ENDDOC) failed"); break;
      case DEVESC_NOTIMPLEMENTED: DbgLastError("OS/2: DevEscape(ENDDOC) not implemented"); break;
      }
   #elif defined __ECL_W32__
      __ECL_ASSERT1__(dc->AbortDoc() >= 0);
   #endif
}


void cdDevice::setColor(long color)
{
   TRACEDEVICE(("cdDevice::setColor(%d)", color));

   #if defined __ECL_OS2__
      GpiSetColor(hps, color);
   #elif defined __ECL_W32__
      stock->pen_color = color;
      stock->change_mask |= CM_PEN_COLOR;
   #endif
}

void cdDevice::setBackColor(long color)
{
   TRACEDEVICE(("cdDevice::setBackColor(%d)", color));

   #if defined __ECL_OS2__
      // nyi
   #elif defined __ECL_W32__
      stock->bk_color = color;
      stock->change_mask |= CM_BK_COLOR;
   #endif
}

void cdDevice::setFillColor(long fillcolor)
{
   TRACEDEVICE(("cdDevice::setFillColor(%d)", fillcolor));

   #if defined __ECL_OS2__
      // nyi
   #elif defined __ECL_W32__
      stock->brush_color = fillcolor;
      stock->change_mask |= CM_BRUSH_COLOR;
   #endif
}

void cdDevice::setFillPattern(char *pattern)
{
   TRACEDEVICE(("cdDevice::setFillPattern()"));

   #if defined __ECL_OS2__
      // nyi
   #elif defined __ECL_W32__
      memcpy(stock->brush_pattern, pattern, 8);
      stock->change_mask |= CM_BRUSH_PATTERN;
   #endif
}

void cdDevice::setLineStyle(long linestyle)
{
   TRACEDEVICE(("cdDevice::setLineStyle(%d)", linestyle));

   #if defined __ECL_OS2__
      GpiSetLineType(hps, linestyle);
   #elif defined __ECL_W32__
      stock->pen_style = linestyle;
      stock->change_mask |= CM_PEN_STYLE;
   #endif
}

void cdDevice::setLineWidth(long linewidth)
{
   TRACEDEVICE(("cdDevice::setLineWidth(%d)", linewidth));

   #if defined __ECL_OS2__
      // nyi
   #elif defined __ECL_W32__
      CSize p(linewidth,0); dc->DPtoLP(&p);
      stock->pen_width = p.cx;
      stock->change_mask |= CM_PEN_WIDTH;
   #endif
}

void cdDevice::setPattern(long pattern)
{
   TRACEDEVICE(("cdDevice::setPattern(%d)", pattern));

   #if defined __ECL_OS2__
      GpiSetPattern(hps, pattern);
   #elif defined __ECL_W32__
      stock->brush_style = pattern;
      stock->change_mask |= CM_BRUSH_STYLE;
   #endif
}

void cdDevice::setForeMix(long mix)
{
   TRACEDEVICE(("cdDevice::setForeMix(%d)", mix));

   #if defined __ECL_OS2__
      GpiSetMix(hps, mix);
   #elif defined __ECL_W32__
      stock->mix_fg = mix;
      stock->change_mask |= CM_MIX_FG;
   #endif
}

void cdDevice::setBackMix(long mix)
{
   TRACEDEVICE(("cdDevice::setBackMix(%d)", mix));

   #if defined __ECL_OS2__
      GpiSetBackMix(hps, mix);
   #elif defined __ECL_W32__
      switch ( mix ) {
      case R2_COPYPEN: stock->mix_bk = OPAQUE; break;
      case R2_NOP:     stock->mix_bk = TRANSPARENT; break;
      default:         __ECL_ASSERT2__(0, ("Invalid back mix mode %d", mix)); break;
      }
      stock->change_mask |= CM_MIX_BK;
   #endif
}

void cdDevice::setTextAlign(long horiz, long vert)
{
   TRACEDEVICE(("cdDevice::setTextAlign(%d,%d)", horiz, vert));

   #if defined __ECL_OS2__
      GpiSetTextAlignment(hps, horiz, vert);
   #elif defined __ECL_W32__
      stock->txt_align = horiz | vert;
      stock->change_mask |= CM_TXT_ALIGN;
   #endif
}

void cdDevice::setTextAngle(long dir_x, long dir_y)
{
   TRACEDEVICE(("cdDevice::setTextAngle(%d,%d)", dir_x, dir_y));

   #if defined __ECL_OS2__
      GRADIENTL gradient = { dir_x, dir_y };
      GpiSetCharAngle(hps, &gradient);
   #elif defined __ECL_W32__
      // ...
   #endif
}

long cdDevice::createFont(const char *facename, int pointsize)
{
   TRACEDEVICE(("cdDevice::createFont(%s,%d)", facename, pointsize));

   #if defined __ECL_OS2__

      long font_id = 1;

      for ( ; font_id < 32 ; font_id++ ) {
         if ( !(font_ids & (1 << font_id)) ) {
            font_ids |= (1 << font_id);
            break;
         }
      }

      if ( font_id < 32 ) {
         if ( fonts == NULL )
            fonts = new cPMFont(hps);
         ((cPMFont *)fonts)->CreateFont(hps, facename, NULL, font_id, pointsize);
         font_sizes[font_id] = pointsize;
         return font_id;
      } else {
         return -1;
      }

   #elif defined __ECL_W32__

      long font_id = 1;

      for ( ; font_id < 32 ; font_id++ ) {
         if ( font_names[font_id].isEmpty() ) {
            font_names[font_id] = facename;
            font_sizes[font_id] = pointsize;
            return font_id;
         }
      }

      return -1;

   #endif
}

void cdDevice::selectFont(long font_id)
{
   TRACEDEVICE(("cdDevice::selectFont(%d)", font_id));

   #if defined __ECL_OS2__

      if ( font_id >= 0 && font_id < 32 && (font_ids & (1 << font_id)) ) {
         if ( fonts )
            ((cPMFont *)fonts)->SelectFont(hps, font_id, font_sizes[font_id]);
      }

   #elif defined __ECL_W32__

      if ( font_id >= 0 && font_id < 32 && !font_names[font_id].isEmpty() ) {
         if ( stock->facename != font_names[font_id]
           || stock->pointsize != font_sizes[font_id] )
         {
            stock->facename = font_names[font_id];
            stock->pointsize = font_sizes[font_id];
            stock->change_mask |= CM_FONT;
         }
      }

   #endif
}

void cdDevice::deleteFont(long font_id)
{
   TRACEDEVICE(("cdDevice::deleteFont(%d)", font_id));

   #if defined __ECL_OS2__

      if ( font_id >= 0 && font_id < 32 && (font_ids & (1 << font_id)) ) {
         font_ids &= ~(1 << font_id);
         if ( fonts )
            ((cPMFont *)fonts)->DeleteFont(hps, font_id);
      }

   #elif defined __ECL_W32__

      if ( font_id >= 0 && font_id < 32 ) {
         font_names[font_id].clear();
         font_sizes[font_id] = 0;
      }

   #endif
}

void cdDevice::beginArea(bool boundary)
{
   TRACEDEVICE(("cdDevice::beginArea(%d)", boundary));

   #if defined __ECL_OS2__
      if ( !GpiBeginArea(hps, (boundary ? BA_BOUNDARY : BA_NOBOUNDARY) | BA_ALTERNATE | BA_INCL) )
         DbgLastError("OS/2: GpiBeginArea failed");
   #elif defined __ECL_W32__
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      if ( !dc->BeginPath() ) {
         DbgLastError("Win32: BeginPath failed");
      } else {
         stock->path_mask = PM_PATH_ACTIVE | (boundary ? PM_STROKE_FILL : PM_FILL);
      }
   #endif
}

void cdDevice::endArea()
{
   TRACEDEVICE(("cdDevice::endArea()"));

   #if defined __ECL_OS2__
      if ( GpiEndArea(hps) == GPI_ERROR )
         DbgLastError("OS/2: GpiEndArea failed");
   #elif defined __ECL_W32__
      dc->CloseFigure();
      if ( !dc->EndPath() )
         DbgLastError("Win32: EndPath failed");
      if ( (stock->path_mask & PM_STROKE_FILL) == PM_STROKE_FILL ) {
         dc->StrokeAndFillPath();
      } else if ( stock->path_mask & PM_FILL ) {
         dc->FillPath();
      } else if ( stock->path_mask & PM_STROKE ) {
         dc->StrokePath();
      }
      stock->path_mask = 0;
   #endif
}

void cdDevice::setRect(const cdPoint& bottom_left, const cdPoint& top_right)
{
   TRACEDEVICE(("cdDevice::setRect(%d,%d,%d,%d)", bottom_left.x, bottom_left.y, top_right.x, top_right.y));

   rect_bottom_left = bottom_left;
   rect_top_right = top_right;
   xrect_bottom_right = cdPoint(top_right.x, bottom_left.y);
   xrect_top_left = cdPoint(bottom_left.x, top_right.y);
}

void cdDevice::setXRect(const cdPoint& bottom_right, const cdPoint& top_left)
{
   xrect_bottom_right = bottom_right;
   xrect_top_left = top_left;
}

bool cdDevice::isXRect() const
{
   cdVector v = rect_bottom_left - xrect_bottom_right;
   return v.x != 0 && v.y != 0;
}

void cdDevice::moveTo(const cdPoint& pos)
{
   TRACEDEVICE(("cdDevice::moveTo(%d,%d)", pos.x, pos.y));

   #if defined __ECL_OS2__
      POINTL p = { pos.x, pos.y };
      if ( !GpiMove(hps, &p) )
         DbgLastError("OS/2: GpiMove failed");
   #elif defined __ECL_W32__
      //int mm = dc->GetMapMode();
      dc->MoveTo(pos.x, pos.y);
      CPoint p(pos.x, pos.y);
      dc->LPtoDP(&p);
   #endif
}

void cdDevice::drawPoint(const cdPoint& point)
{
   TRACEDEVICE(("cdDevice::drawPoint(%d,%d)", point.x, point.y));

   #if defined __ECL_OS2__
      POINTL p = { xe, ye };
      if ( GpiPixel(hps, &p) == GPI_ERROR )
         DbgLastError("OS/2: GpiPixel failed");
   #elif defined __ECL_W32__
      dc->SetPixelV(point.x, point.y, stock->pen_color);
   #endif
}

void cdDevice::drawLine(const cdPoint& line_end)
{
   TRACEDEVICE(("cdDevice::drawLine(%d,%d)", line_end.x, line_end.y));

   #if defined __ECL_OS2__
      POINTL p = { xe, ye };
      if ( GpiLine(hps, &p) == GPI_ERROR )
         DbgLastError("OS/2: GpiLine failed");
   #elif defined __ECL_W32__
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      dc->LineTo(line_end.x, line_end.y);
   #endif
}

void cdDevice::drawCircle(const cdPoint& center, long radius)
{
   TRACEDEVICE(("cdDevice::drawCircle(%d,%d,%d)", center.x, center.y, radius));

   #if defined __ECL_OS2__
      ARCPARAMS ap;
      POINTL p;
      ap.lP = ap.lQ = radius;
      ap.lR = ap.lS = 0;
      p.x = center.x; p.y = center.y;
      GpiSetArcParams(hps, &ap);
      if ( GpiFullArc(hps, DRO_OUTLINE, MAKEFIXED(1,0)) == GPI_ERROR )
         DbgLastError("OS/2: GpiLine failed");
   #elif defined __ECL_W32__
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      dc->Ellipse(
         center.x-radius, center.y-radius,
         center.x+radius, center.y+radius
      );
   #endif
}

void cdDevice::drawEllipse()
{
   TRACEDEVICE(("cdDevice::drawEllipse()"));

   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      if ( isXRect() ) {
         // TBD: XRECT-Ellipsen!!!
         dc->Ellipse(
            rect_bottom_left.x, rect_bottom_left.y,
            rect_top_right.x, rect_top_right.y
         );
      } else {
         dc->Ellipse(
            rect_bottom_left.x, rect_bottom_left.y,
            rect_top_right.x, rect_top_right.y
         );
      }
   #endif
}

void cdDevice::drawRect()
{
   TRACEDEVICE(("cdDevice::drawRect()"));

   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      if ( isXRect() ) {
         dc->MoveTo(rect_bottom_left.x, rect_bottom_left.y);
         dc->BeginPath();
         dc->LineTo(xrect_top_left.x, xrect_top_left.y);
         dc->LineTo(rect_top_right.x, rect_top_right.y);
         dc->LineTo(xrect_bottom_right.x, xrect_bottom_right.y);
         dc->LineTo(rect_bottom_left.x, rect_bottom_left.y);
         dc->EndPath();
         dc->StrokeAndFillPath();
      } else {
         dc->Rectangle(
            rect_bottom_left.x, rect_bottom_left.y,
            rect_top_right.x, rect_top_right.y
         );
      }
   #endif
}

void cdDevice::drawArcCW(const cdPoint& arc_end)
{
   TRACEDEVICE(("cdDevice::drawArcCW(%d,%d)", arc_end.x, arc_end.y));

   #if defined __ECL_OS2__
      long x2 = xc;
      long xy = yc;
      ARCPARAMS ap;
      POINTL p[2];
      ap.lP = ap.lQ = 1;
      ap.lR = ap.lS = 0;
      p[0].x = x2; p[0].y = y2;
      p[1].x = xe; p[1].y = ye;
      GpiSetArcParams(hps, &ap);
      if ( GpiPointArc(hps, &p[0]) == GPI_ERROR )
         DbgLastError("OS/2: GpiPointArc failed");
   #elif defined __ECL_W32__
      CPoint curpos = dc->GetCurrentPosition();
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      if ( isXRect() ) {
         MyArcTo(dc, !!(stock->path_mask & PM_PATH_ACTIVE), -1,
                 rect_bottom_left, rect_top_right,
                 xrect_bottom_right, xrect_top_left,
                 cdPoint(curpos.x, curpos.y), arc_end);
      } else {
         MyArcTo(dc, !!(stock->path_mask & PM_PATH_ACTIVE), -1,
                 rect_bottom_left, rect_top_right,
                 cdPoint(curpos.x, curpos.y), arc_end);
      }
/*
      dc->SetArcDirection(AD_CLOCKWISE);
      if ( isXRect() ) {
         // TBD: XRECT-Kreisboegen!!!
         cdVector bottom(xrect_bottom_right - rect_bottom_left);
         cdVector left(xrect_top_left - rect_bottom_left);
         cdPoint center = rect_bottom_left + bottom/2 + left/2;
         int radius = int(bottom.getLength() / 2);
         dc->ArcTo(
            center.x - radius, center.y - radius,
            center.x + radius, center.y + radius,
            curpos.x, curpos.y,
            arc_end.x, arc_end.y
         );
      } else {
         dc->ArcTo(
            rect_bottom_left.x, rect_bottom_left.y,
            rect_top_right.x, rect_top_right.y,
            curpos.x, curpos.y,
            arc_end.x, arc_end.y
         );
      }
      //dc->MoveTo(arc_end.x, arc_end.y);
*/
   #endif
}

void cdDevice::drawArcCCW(const cdPoint& arc_end)
{
   TRACEDEVICE(("cdDevice::drawArcCCW(%d,%d)", arc_end.x, arc_end.y));

   #if defined __ECL_OS2__
      long x2 = xc;
      long xy = yc;
      ARCPARAMS ap;
      POINTL p[2];
      ap.lP = ap.lQ = 1;
      ap.lR = ap.lS = 0;
      p[0].x = x2; p[0].y = y2;
      p[1].x = xe; p[1].y = ye;
      GpiSetArcParams(hps, &ap);
      if ( GpiPointArc(hps, &p[0]) == GPI_ERROR )
         DbgLastError("OS/2: GpiPointArc failed");
   #elif defined __ECL_W32__
      CPoint curpos = dc->GetCurrentPosition();
      stock->setPen(dc);
      stock->setBrush(dc);
      stock->setMix(dc);
      if ( isXRect() ) {
         MyArcTo(dc, !!(stock->path_mask & PM_PATH_ACTIVE), 1,
                 rect_bottom_left, rect_top_right,
                 xrect_bottom_right, xrect_top_left,
                 cdPoint(curpos.x, curpos.y), arc_end);
      } else {
         MyArcTo(dc, !!(stock->path_mask & PM_PATH_ACTIVE), 1,
                 rect_bottom_left, rect_top_right,
                 cdPoint(curpos.x, curpos.y), arc_end);
      }
/*
      dc->SetArcDirection(AD_COUNTERCLOCKWISE);
      if ( isXRect() ) {
         // TBD: XRECT-Kreisboegen!!!
         cdVector bottom(xrect_bottom_right - rect_bottom_left);
         cdVector left(xrect_top_left - rect_bottom_left);
         cdPoint center = rect_bottom_left + bottom/2 + left/2;
         int radius = int(bottom.getLength() / 2);
         dc->ArcTo(
            center.x - radius, center.y - radius,
            center.x + radius, center.y + radius,
            curpos.x, curpos.y,
            arc_end.x, arc_end.y
         );
      } else {
         dc->ArcTo(
            rect_bottom_left.x, rect_bottom_left.y,
            rect_top_right.x, rect_top_right.y,
            curpos.x, curpos.y,
            arc_end.x, arc_end.y
         );
      }
      //dc->MoveTo(arc_end.x, arc_end.y);
*/
   #endif
}

void cdDevice::drawText(const char *txt, int length)
{
   #ifdef __Trace_Device_Calls__
      char buf[80]; strxcpy(buf, txt, sizeof buf);
      if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
      TRACEDEVICE(("cdDevice::drawText('%s',%d)", buf, length));
   #endif

   #if defined __ECL_OS2__
      length = length < 0 ? strlen(txt) : length;
      char *text = (char *)((void *)txt);
      if ( length && GpiCharString(hps, length, text) == GPI_ERROR ) {
         char buf[512] = ""; strxcpy(buf, text, min(sizeof buf, length));
         DbgLastError("OS/2: GpiCharString(%08x,%d,'%s') failed", hps, length, buf);
      }
   #elif defined __ECL_W32__
      CPoint curpos = dc->GetCurrentPosition();
      stock->setPen(dc);
      stock->setMix(dc);
      stock->setFont(dc);
      stock->setTxtAlign(dc);
      length = length < 0 ? strlen(txt) : length;
      if ( length ) {
         int curpos_y = curpos.y;
         if ( stock->txt_align & 0x0800 ) {
            // special case for: cdAlign::Half
            TEXTMETRIC tm; dc->GetTextMetrics(&tm);
            curpos_y += tm.tmAscent/2;
         }
         if ( !dc->TextOut(curpos.x, curpos_y, txt, length) ) {
            char buf[256] = ""; strxcpy(buf, txt, min(sizeof buf, length));
            DbgLastError("Win32: TextOut(%d,%d,%d,'%s') failed", curpos.x, curpos_y, length, buf);
         }
      }
   #endif
}

void cdDevice::drawFrom(const cdMemoryDevice *memory_device, const cdPoint& pos)
{
   TRACEDEVICE(("cdDevice::drawFrom(%08x,%d,%d)", memory_device, pos.x, pos.y));

   // Der Memory-Device soll jetzt seine Aufzeichnung einspielen. Dazu benutzt
   // er die normalen set- und draw-Routinen aus dem Device. D.h., der gesamte
   // Speicherinhalt des Memory-Devices landet durch die replayAt-Funktion im
   // Device. Deshalb kann der Memory-Device anschliessend geloescht werden,
   // wenn nicht mehr benoetigt.

   if ( memory_device )
      memory_device->replayAt(this, pos);
}

void cdDevice::queryAvgCharSize(long& cx, long& cy) const
{
   TRACEDEVICE(("cdDevice::queryAvgCharSize()"));

   #if defined __ECL_OS2__
      FONTMETRICS fm;
      if ( !GpiQueryFontMetrics(hps, sizeof fm, &fm) )
         DbgLastError("OS/2: GpiQueryFontMetrics failed");
      cx = fm.lAveCharWidth;
      cy = fm.lEmHeight;
   #elif defined __ECL_W32__
      stock->setPen(dc);
      stock->setFont(dc);
      TEXTMETRIC tm;
      if ( !dc->GetTextMetrics(&tm) )
         DbgLastError("Win32: GetTextMetrics() failed");
      cy = labs(tm.tmHeight);
      cx = labs(tm.tmAveCharWidth);
   #endif
}

cdSize cdDevice::queryTextSize(const char *txt, int length) const
{
   #ifdef __Trace_Device_Calls__
      char buf[80]; strxcpy(buf, txt, sizeof buf);
      if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
      TRACEDEVICE(("cdDevice::queryTextSize(%s)", buf));
   #endif

   #if defined __ECL_W32__
      stock->setPen(dc);
      stock->setFont(dc);
      length = length < 0 ? strlen(txt) : length;
      CSize size = dc->GetTextExtent(txt, length);
      return cdSize(size.cx, size.cy);
   #endif
}

long cdDevice::queryTextWidth(const char *txt, int length) const
{
   #if defined __ECL_OS2__
      #ifdef __Trace_Device_Calls__
         char buf[80]; strxcpy(buf, txt, sizeof buf);
         if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
         TRACEDEVICE(("cdDevice::queryTextWidth(%s)", buf));
      #endif
      POINTL txt_points[TXTBOX_COUNT];
      if ( !GpiQueryTextBox(hps, length < 0 ? strlen(txt) : length, (PCH)txt, TXTBOX_COUNT, txt_points) )
         DbgLastError("OS/2: GpiQueryTextBox failed");
      if ( txt_points[TXTBOX_BOTTOMLEFT].y == txt_points[TXTBOX_BOTTOMRIGHT].y ) {
         return txt_points[TXTBOX_BOTTOMRIGHT].x - txt_points[TXTBOX_BOTTOMLEFT].x;
      } else {
         // TBD: Breite korrekt berechnen...
         return txt_points[TXTBOX_BOTTOMRIGHT].x - txt_points[TXTBOX_BOTTOMLEFT].x;  // TBF: <- Dies ist nur ein Naehrungswert!!!!
      }
   #endif

   return labs(queryTextSize(txt, length).cx);
}

long cdDevice::queryTextHeight(const char *txt, int length) const
{
   #if defined __ECL_OS2__
      #ifdef __Trace_Device_Calls__
         char buf[80]; strxcpy(buf, txt, sizeof buf);
         if ( length >= 0 ) buf[min(length, int(sizeof buf-1))] = '\0';
         TRACEDEVICE(("cdDevice::queryTextHeight(%s)", buf));
      #endif
      POINTL txt_points[TXTBOX_COUNT];
      if ( !GpiQueryTextBox(hps, length < 0 ? strlen(txt) : length, (PCH)txt, TXTBOX_COUNT, txt_points) )
         DbgLastError("OS/2: GpiQueryTextBox failed");
      if ( txt_points[TXTBOX_BOTTOMLEFT].x == txt_points[TXTBOX_TOPLEFT].x ) {
         return txt_points[TXTBOX_TOPLEFT].y - txt_points[TXTBOX_BOTTOMLEFT].y;
      } else {
         // TBD: Hoehe korrekt berechnen...
         return txt_points[TXTBOX_TOPLEFT].y - txt_points[TXTBOX_BOTTOMLEFT].y;   // TBF: <- Dies ist nur ein Naehrungswert!!!!
      }
   #endif

   return labs(queryTextSize(txt, length).cx);
}

// long cdDevice::convWorld2Pel(long world) const
// {
//    #if defined __ECL_OS2__
//       POINTL ptl = { world, 0 };
//       GpiConvert(hps, CVTC_PAGE, CVTC_DEVICE, 1L, &ptl);
//       return ptl.x;
//    #elif defined __ECL_W32__
//       if ( __ECL_ASSERT1__(dc != 0) ) {
//          SIZE siz = { world , 0 };
//          dc->LPtoDP(&size);
//          return siz.cx;
//       } else {
//          return -1;
//       }
//    #endif
// }
//
// long cdDevice::convPel2World(long pel) const
// {
//    #if defined __ECL_OS2__
//       POINTL ptl = { pel , 0 };
//       GpiConvert(hps, CVTC_DEVICE, CVTC_PAGE, 1L, &ptl);
//       return ptl.x;
//    #elif defined __ECL_W32__
//       if ( __ECL_ASSERT1__(dc != 0) ) {
//          SIZE siz = { pel , 0 };
//          dc->DPtoLP(&size);
//          return siz.cx;
//       } else {
//          return -1;
//       }
//    #endif
// }



// Koordinatenumwandlung
// =====================

cdPoint cdDevice::convPageToLog(const c2dPoint& p) const
{
   switch ( map_mode ) {
   case mmDirect:       return cdPoint(long(p.x + .5), long(p.y + .5));
   case mmIsotropic:    return cdPoint(long(p.x + .5), long(p.y + .5));
   case mmAnisotropic:  return cdPoint(long(p.x + .5), long(p.y + .5));
   case mmLoMetric:     return cdPoint(long(p.x * 10. + .5), long(p.y * 10.0 + .5));
   case mmHiMetric:     return cdPoint(long(p.x * 100. + .5), long(p.y * 100.0 + .5));
   }

   return cdPoint(long(p.x + .5), long(p.y + .5));
}

cdVector cdDevice::convPageToLog(const c2dVector& v) const
{
   switch ( map_mode ) {
   case mmDirect:       return cdVector(long(v.x + .5), long(v.y + .5));
   case mmIsotropic:    return cdVector(long(v.x + .5), long(v.y + .5));
   case mmAnisotropic:  return cdVector(long(v.x + .5), long(v.y + .5));
   case mmLoMetric:     return cdVector(long(v.x * 10. + .5), long(v.y * 10. + .5));
   case mmHiMetric:     return cdVector(long(v.x * 100. + .5), long(v.y * 100. + .5));
   }

   return cdVector(long(v.x + .5), long(v.y + .5));
}

cdRect cdDevice::convPageToLog(const c2dBox& b) const
{
   return cdRect(convPageToLog(b.lb), convPageToLog(b.rt));
}

c2dPoint cdDevice::convLogToPage(const cdPoint& p) const
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      switch ( map_mode ) {
      case mmDirect:       return c2dPoint(double(p.x), double(p.y));
      case mmIsotropic:    return c2dPoint(double(p.x), double(p.y));
      case mmAnisotropic:  return c2dPoint(double(p.x), double(p.y));
      case mmLoMetric:     return c2dPoint(double(p.x) / 10.0, double(p.y) / 10.0);
      case mmHiMetric:     return c2dPoint(double(p.x) / 100.0, double(p.y) / 100.0);
      }
   #endif

   return c2dPoint(double(p.x), double(p.y));
}

c2dVector cdDevice::convLogToPage(const cdVector& v) const
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      switch ( map_mode ) {
      case mmDirect:       return c2dVector(double(v.x), double(v.y));
      case mmIsotropic:    return c2dVector(double(v.x), double(v.y));
      case mmAnisotropic:  return c2dVector(double(v.x), double(v.y));
      case mmLoMetric:     return c2dVector(double(v.x) / 10.0, double(v.y) / 10.0);
      case mmHiMetric:     return c2dVector(double(v.x) / 100.0, double(v.y) / 100.0);
      }
   #endif

   return c2dVector(double(v.x), double(v.y));
}

c2dBox cdDevice::convLogToPage(const cdRect& r) const
{
   return c2dBox(convLogToPage(r.lb), convLogToPage(r.rt));
}

cdPoint cdDevice::convLogToDev(const cdPoint& p) const
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      if ( __ECL_ASSERT1__(dc != 0) ) {
         POINT w32_p = { p.x, p.y };
         dc->LPtoDP(&w32_p);
         return cdPoint(w32_p.x, w32_p.y);
      } else {
         return p;
      }
   #endif
}

cdSize cdDevice::convLogToDev(const cdSize& s) const
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      if ( __ECL_ASSERT1__(dc != 0) ) {
         SIZE w32_s = { s.cx, s.cy };
         dc->LPtoDP(&w32_s);
         return cdSize(w32_s.cx, w32_s.cy);
      } else {
         return s;
      }
   #endif
}

cdRect cdDevice::convLogToDev(const cdRect& r) const
{
   // TBD: Ist das ueberhaupt richtig??? Beachte Unterschiede MM_TEXT / MM_xxMETRIC!!!!!!!!!!!!!!!!!
   return cdRect(convLogToDev(r.lb), convLogToDev(r.rt));
}

cdPoint  cdDevice::convDevToLog(const cdPoint& p) const
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      if ( __ECL_ASSERT1__(dc != 0) ) {
         POINT w32_p = { p.x, p.y };
         dc->DPtoLP(&w32_p);
         return cdPoint(w32_p.x, w32_p.y);
      } else {
         return p;
      }
   #endif
}

cdSize cdDevice::convDevToLog(const cdSize& s) const
{
   #if defined __ECL_OS2__
      // ...
   #elif defined __ECL_W32__
      if ( __ECL_ASSERT1__(dc != 0) ) {
         SIZE w32_s = { s.cx, s.cy };
         dc->DPtoLP(&w32_s);
         return cdSize(w32_s.cx, w32_s.cy);
      } else {
         return s;
      }
   #endif
}

cdRect cdDevice::convDevToLog(const cdRect& r) const
{
   // TBD: Ist das ueberhaupt richtig??? Beachte Unterschiede MM_TEXT / MM_xxMETRIC!!!!!!!!!!!!!!!!!
   return cdRect(convDevToLog(r.lb), convDevToLog(r.rt));
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdRetainedDevice
// ---------------------------------------------------------------------------
//
// Geraet mit Speicher fuer Grafikprimitiven. Innerhalb einer beginDrawing/
// endDrawing-Klammer werden alle Operationen in ein cdStorage-Objekt aufge-
// zeichnet und koennen anschliessend ueber paintAt beliebig oft wieder abge-
// spielt werden. Ausserhalb einer beginDrawing/endDrawing-Klammer werden
// alle Operationen direkt an Methoden der Parent-Klasse weitergegeben.
//
//  cBase
//   +--cdDevice
//       +--cdRetainedDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdRetainedDevice : public cdDevice {

public:
   inline cdRetainedDevice() { init(); }
   inline cdRetainedDevice(const cdDevice& other) : cdDevice(other) { init(); }
   inline cdRetainedDevice(const cdRetainedDevice& other) : cdDevice(other) { init(); }
   ~cdRetainedDevice();

   // Der Aufrufer von endDrawing ist fuer das Freigeben des cdStorage-
   // Objektes verantwortlich!
   void beginDrawing();
   cdDeviceStore *endDrawing();

   virtual void paintAt(cdDeviceStore *elems, const cdPoint& pos);

   // Vordergrundfarbe setzen
   inline void setColor(const cdColor& color)
      { setColor(color.getOsVal()); }
   // Hintergrundfarbe setzen
   inline void setBackColor(const cdColor& color)
      { setBackColor(color.getOsVal()); }
   // Fuellfarbe setzen
   inline void setFillColor(const cdColor& fillcolor)
      { setFillColor(fillcolor.getOsVal()); }
   // Linienstil setzen
   inline void setLineStyle(const cdLineStyle& linestyle)
      { setLineStyle(linestyle.getOsVal()); }
   // Linienmuster setzen
   inline void setPattern(const cdPattern& pattern)
      { setPattern(pattern.getOsVal()); }
   // Vordergrund-Mischmodus setzen
   inline void setForeMix(const cdMix& mix)
      { setForeMix(mix.getOsVal()); }
   // Hintergrund-Mischmodus setzen
   inline void setBackMix(const cdMix& mix)
      { setBackMix(mix.getOsVal()); }
   // Textausrichtung setzen
   inline void setTextAlign(const cdAlign& horiz, const cdAlign& vert)
      { setTextAlign(horiz.getOsVal(), vert.getOsVal()); }

   void setColor(long color);
   void setBackColor(long color);
   void setFillColor(long fillcolor);
   void setFillPattern(char *pattern);
   void setLineStyle(long linestyle);
   void setLineWidth(long linewidth);
   void setPattern(long pattern);
   void setForeMix(long mix);
   void setBackMix(long mix);

   void setTextAlign(long horiz, long vert);
   void setTextAngle(long dir_x, long dir_y);

   void selectFont(long font_id);
   void deleteFont(long font_id);

   // Setze RECT fuer kuenftige Operationen auf 'bottom_left', 'top_right'
   void setRect(const cdPoint& bottom_left, const cdPoint& top_right);
   // Setze XRECT fuer kuenftige Operationen auf 'bottom_right', 'top_left'
   void setXRect(const cdPoint& bottom_right, const cdPoint& top_left);

   // Bewege CURSOR auf 'p'
   void moveTo(const cdPoint& p);

   // Gerade von CURSOR bis 'line_end'
   void drawLine(const cdPoint& line_end);
   // Kreis um 'center' mit 'radius'
   void drawCircle(const cdPoint& center, long radius);
   // Ellipse innerhalb von RECT/XRECT
   void drawEllipse();
   // Rechteck wie durch RECT/XRECT definiert
   void drawRect();
   // Bogen im Uhrzeigersinn innerhalb RECT/XRECT von CURSOR bis 'arc_end'
   void drawArcCW(const cdPoint& arc_end);
   // Bogen gegen Uhrzeigersinn innerhalb RECT/XRECT von CURSOR bis 'arc_end'
   void drawArcCCW(const cdPoint& arc_end);
   // Text ab Cursor
   void drawText(const char *txt, int length);

   void beginArea(bool boundary);
   void endArea();

private:
   cdDeviceStore *cur_storage;
   cdDeviceStore::ELEM *newElem() const
      { return cur_storage->newElem(); }

   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cdRetainedDevice
// ===========================================================================

void cdRetainedDevice::init()
{
   cur_storage = NULL;
}

cdRetainedDevice::~cdRetainedDevice()
{
   delete cur_storage;
}

void cdRetainedDevice::beginDrawing()
{
   delete cur_storage;
   cur_storage = new cdDeviceStore();
}

cdDeviceStore * cdRetainedDevice::endDrawing()
{
   cdDeviceStore *ret_val = cur_storage;
   cur_storage = NULL;
   return ret_val;
}

void cdRetainedDevice::paintAt(cdDeviceStore *elems, const cdPoint& pos)
{
   if ( elems == NULL )
      return;

   cdDevice::reset();
   cdDeviceStore::ELEM *elem = elems->firstElem();

   while ( elem ) {

      bool dont_increm = false;

      switch ( elem->cmd ) {

       case cdDeviceStore::ecLast:
         elem = NULL; dont_increm = true; break;
       case cdDeviceStore::ecNext:
         elem = elem->next; dont_increm = true; break;

       case cdDeviceStore::ecSetColor:
         cdDevice::setColor(elem->val1); break;
       case cdDeviceStore::ecSetBackColor:
         cdDevice::setBackColor(elem->val1); break;
       case cdDeviceStore::ecSetFillColor:
         cdDevice::setFillColor(elem->val1); break;
       case cdDeviceStore::ecSetFillPattern:
         cdDevice::setFillPattern(elem->text); break;
       case cdDeviceStore::ecSetLineStyle:
         cdDevice::setLineStyle(elem->val1); break;
       case cdDeviceStore::ecSetLineWidth:
         cdDevice::setLineWidth(elem->val1); break;
       case cdDeviceStore::ecSetPattern:
         cdDevice::setPattern(elem->val1); break;
       case cdDeviceStore::ecSetForeMix:
         cdDevice::setForeMix(elem->val1); break;
       case cdDeviceStore::ecSetBackMix:
         cdDevice::setBackMix(elem->val1); break;

       case cdDeviceStore::ecSetTextAlign:
         cdDevice::setTextAlign(elem->val1, elem->val2); break;
       case cdDeviceStore::ecSetTextAngle:
         cdDevice::setTextAngle(elem->val1, elem->val2); break;

       case cdDeviceStore::ecSelectFont:
         cdDevice::selectFont(elem->val1); break;
       case cdDeviceStore::ecDeleteFont:
         cdDevice::deleteFont(elem->val1); break;

       case cdDeviceStore::ecSetRect:
         cdDevice::setRect(pos + cdPoint(elem->x, elem->y), pos + cdPoint(elem->x2, elem->y2)); break;
       case cdDeviceStore::ecSetXRect:
         cdDevice::setXRect(pos + cdPoint(elem->x, elem->y), pos + cdPoint(elem->x2, elem->y2)); break;

       case cdDeviceStore::ecMoveTo:
         cdDevice::moveTo(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecBeginArea:
         cdDevice::beginArea(!!elem->val1); break;
       case cdDeviceStore::ecEndArea:
         cdDevice::endArea(); break;

       case cdDeviceStore::ecDrawLine:
         cdDevice::drawLine(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecDrawCircle:
         cdDevice::drawCircle(pos + cdPoint(elem->x, elem->y), elem->val3); break;
       case cdDeviceStore::ecDrawEllipse:
         cdDevice::drawEllipse(); break;
       case cdDeviceStore::ecDrawRect:
         cdDevice::drawRect(); break;
       case cdDeviceStore::ecDrawArcCW:
         cdDevice::drawArcCW(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecDrawArcCCW:
         cdDevice::drawArcCCW(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecDrawText:
         cdDevice::drawText(elem->text, elem->val2); break;

      }

      if ( !dont_increm )
         elem++;

   }
}

void cdRetainedDevice::setColor(long color)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetColor;
      elem->val1 = color;
   } else {
      cdDevice::setColor(color);
   }
}

void cdRetainedDevice::setBackColor(long color)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetBackColor;
      elem->val1 = color;
   } else {
      cdDevice::setBackColor(color);
   }
}

void cdRetainedDevice::setFillColor(long fillcolor)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetFillColor;
      elem->val1 = fillcolor;
   } else {
      cdDevice::setFillColor(fillcolor);
   }
}

void cdRetainedDevice::setFillPattern(char *pattern)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetFillPattern;
      if ( (elem->text = new (char[8])) != NULL ) {
         elem->flags = cdDeviceStore::efFreeText;
         memcpy(elem->text, pattern, 8);
         elem->val2 = 8;
      } else {
         elem->cmd = cdDeviceStore::ecNop;
         DbgError("cdRetainedDevice: Alloc pattern failed");
      }
   } else {
      cdDevice::setFillPattern(pattern);
   }
}

void cdRetainedDevice::setLineStyle(long linestyle)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetLineStyle;
      elem->val1 = linestyle;
   } else {
      cdDevice::setLineStyle(linestyle);
   }
}

void cdRetainedDevice::setLineWidth(long linewidth)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetLineWidth;
      elem->val1 = linewidth;
   } else {
      cdDevice::setLineWidth(linewidth);
   }
}

void cdRetainedDevice::setPattern(long pattern)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetPattern;
      elem->val1 = pattern;
   } else {
      cdDevice::setPattern(pattern);
   }
}

void cdRetainedDevice::setForeMix(long mix)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetForeMix;
      elem->val1 = mix;
   } else {
      cdDevice::setForeMix(mix);
   }
}

void cdRetainedDevice::setBackMix(long mix)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetBackMix;
      elem->val1 = mix;
   } else {
      cdDevice::setBackMix(mix);
   }
}

void cdRetainedDevice::setTextAlign(long horiz, long vert)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetTextAlign;
      elem->val1 = horiz;
      elem->val2 = vert;
   } else {
      cdDevice::setTextAlign(horiz, vert);
   }
}

void cdRetainedDevice::setTextAngle(long dir_x, long dir_y)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetTextAngle;
      elem->val1 = dir_x;
      elem->val2 = dir_y;
   }

   // Muss auf jeden Fall ausgefuehrt werden, damit die Abfrage
   // von Zeichen- und Text-Groessen klappen kann
   cdDevice::setTextAngle(dir_x, dir_y);
}

void cdRetainedDevice::selectFont(long font_id)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSelectFont;
      elem->val1 = font_id;
   }

   // Muss auf jeden Fall ausgefuehrt werden, damit die Abfrage
   // von Zeichen- und Text-Groessen klappen kann
   cdDevice::selectFont(font_id);
}

void cdRetainedDevice::deleteFont(long font_id)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDeleteFont;
      elem->val1 = font_id;
   } else {
      cdDevice::deleteFont(font_id);
   }
}

void cdRetainedDevice::setRect(const cdPoint& bottom_left, const cdPoint& top_right)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetRect;
      elem->x  = bottom_left.x;
      elem->y  = bottom_left.y;
      elem->x2 = top_right.x;
      elem->y2 = top_right.y;
   } else {
      cdDevice::setRect(bottom_left, top_right);
   }
}

void cdRetainedDevice::setXRect(const cdPoint& bottom_right, const cdPoint& top_left)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecSetXRect;
      elem->x  = bottom_right.x;
      elem->y  = bottom_right.y;
      elem->x2 = top_left.x;
      elem->y2 = top_left.y;
   } else {
      cdDevice::setXRect(bottom_right, top_left);
   }
}

void cdRetainedDevice::moveTo(const cdPoint& p)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecMoveTo;
      elem->x = p.x;
      elem->y = p.y;
   } else {
      cdDevice::moveTo(p);
   }
}

void cdRetainedDevice::drawLine(const cdPoint& line_end)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDrawLine;
      elem->x = line_end.x;
      elem->y = line_end.y;
   } else {
      cdDevice::drawLine(line_end);
   }
}

void cdRetainedDevice::drawCircle(const cdPoint& center, long radius)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDrawCircle;
      elem->x = center.x;
      elem->y = center.y;
      elem->val3 = radius;
   } else {
      cdDevice::drawCircle(center, radius);
   }
}

void cdRetainedDevice::drawEllipse()
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDrawEllipse;
   } else {
      cdDevice::drawEllipse();
   }
}

void cdRetainedDevice::drawRect()
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDrawRect;
   } else {
      cdDevice::drawRect();
   }
}

void cdRetainedDevice::drawArcCW(const cdPoint& arc_end)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDrawArcCW;
      elem->x = arc_end.x;
      elem->y = arc_end.y;
   } else {
      cdDevice::drawArcCW(arc_end);
   }
}

void cdRetainedDevice::drawArcCCW(const cdPoint& arc_end)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecDrawArcCCW;
      elem->x = arc_end.x;
      elem->y = arc_end.y;
   } else {
      cdDevice::drawArcCCW(arc_end);
   }
}

void cdRetainedDevice::drawText(const char *txt, int length)
{
   if ( txt != NULL ) {
      if ( cur_storage ) {
         cdDeviceStore::ELEM *elem = newElem();
         elem->cmd = cdDeviceStore::ecDrawText;
         if ( (elem->text = new (char[strlen(txt)+1])) != NULL ) {
            elem->flags = cdDeviceStore::efFreeText;
            strcpy(elem->text, txt);
            elem->val2 = length;
         } else {
            elem->cmd = cdDeviceStore::ecNop;
            DbgError("cdRetainedDevice: Alloc text failed");
         }
      } else {
         cdDevice::drawText(txt, length);
      }
   }
}

void cdRetainedDevice::beginArea(bool boundary)
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecBeginArea;
      elem->val1 = boundary;
   } else {
      cdDevice::beginArea(boundary);
   }
}

void cdRetainedDevice::endArea()
{
   if ( cur_storage ) {
      cdDeviceStore::ELEM *elem = newElem();
      elem->cmd = cdDeviceStore::ecEndArea;
   } else {
      cdDevice::endArea();
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdMemoryDevice
// ---------------------------------------------------------------------------
//
// Ein Memory-Device kann nur basierend auf einem realen (retained) Device
// angelegt werden und ist immer zu diesem kompatibel. Es merkt sich auto-
// matisch alle Ausgaben und kann diese in ein Retained-Device zurueckspielen.
//
// Alle Koordinaten sind Memory-Device-relativ.
//
//  cBase
//   +--cdDevice
//       +--cdRetainedDevice
//           +--cdMemoryDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdMemoryDevice : public cdRetainedDevice {
   friend class cdDevice;

public:
   inline cdMemoryDevice(cdDevice *compatible_device) : cdRetainedDevice(*compatible_device) { init(); }
   ~cdMemoryDevice();

   void beginDrawing();
   void endDrawing();

private:
   cdDeviceStore *elems;

   void init();

   // Zeichen der gespeicherten Ausgaben auf 'device'
   void replayAt(cdDevice *device, const cdPoint& pos) const;

   // paintAt-Funktion sinnlos, daher deaktiviert
   void paintAt(cdDeviceStore *, const cdPoint&)
      { }

};

#endif /*__INTERFACE__*/


// Implementierung cdMemoryDevice
// ===========================================================================

void cdMemoryDevice::init()
{
   // Zwangsweise wird beginDrawing aufgerufen. Fuer den Anwender von
   // cdMemoryDevice hat dies die Konsequenz, dass er den Aufruf nicht
   // selbst machen muss (aber durchaus machen kann, was die gleichen
   // Auswirkungen hat...)
   elems = NULL;
   beginDrawing();
}

cdMemoryDevice::~cdMemoryDevice()
{
   delete elems;
}

void cdMemoryDevice::beginDrawing()
{
   cdRetainedDevice::beginDrawing();
}

void cdMemoryDevice::endDrawing()
{
   // Zeichnet der Benutzer mehrere Sequenzen auf, merkt sich das
   // Memory-Device jeweils nur die letzte Sequenz.
   delete elems;
   elems = cdRetainedDevice::endDrawing();
}

void cdMemoryDevice::replayAt(cdDevice *device, const cdPoint& pos) const
{
   if ( elems == NULL )
      return;

   cdDeviceStore::ELEM *elem = elems->firstElem();

   while ( elem ) {

      bool dont_increm = false;

      switch ( elem->cmd ) {

       case cdDeviceStore::ecLast:
         elem = NULL; dont_increm = true; break;
       case cdDeviceStore::ecNext:
         elem = elem->next; dont_increm = true; break;

       case cdDeviceStore::ecSetColor:
         device->setColor(elem->val1); break;
       case cdDeviceStore::ecSetBackColor:
         device->setBackColor(elem->val1); break;
       case cdDeviceStore::ecSetFillColor:
         device->setFillColor(elem->val1); break;
       case cdDeviceStore::ecSetFillPattern:
         device->setFillPattern(elem->text); break;
       case cdDeviceStore::ecSetLineStyle:
         device->setLineStyle(elem->val1); break;
       case cdDeviceStore::ecSetLineWidth:
         device->setLineWidth(elem->val1); break;
       case cdDeviceStore::ecSetPattern:
         device->setPattern(elem->val1); break;
       case cdDeviceStore::ecSetForeMix:
         device->setForeMix(elem->val1); break;
       case cdDeviceStore::ecSetBackMix:
         device->setBackMix(elem->val1); break;

       case cdDeviceStore::ecSetTextAlign:
         device->setTextAlign(elem->val1, elem->val2); break;
       case cdDeviceStore::ecSetTextAngle:
         device->setTextAngle(elem->val1, elem->val2); break;

       case cdDeviceStore::ecSelectFont:
         device->selectFont(elem->val1); break;
       case cdDeviceStore::ecDeleteFont:
         device->deleteFont(elem->val1); break;

       case cdDeviceStore::ecSetRect:
         device->setRect(pos + cdPoint(elem->x, elem->y), pos + cdPoint(elem->x2, elem->y2)); break;
       case cdDeviceStore::ecSetXRect:
         device->setXRect(pos + cdPoint(elem->x, elem->y), pos + cdPoint(elem->x2, elem->y2)); break;

       case cdDeviceStore::ecMoveTo:
         device->moveTo(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecBeginArea:
         device->beginArea(!!elem->val1); break;
       case cdDeviceStore::ecEndArea:
         device->endArea(); break;

       case cdDeviceStore::ecDrawLine:
         device->drawLine(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecDrawCircle:
         device->drawCircle(pos + cdPoint(elem->x, elem->y), elem->val3); break;
       case cdDeviceStore::ecDrawEllipse:
         device->drawEllipse(); break;
       case cdDeviceStore::ecDrawRect:
         device->drawRect(); break;
       case cdDeviceStore::ecDrawArcCW:
         device->drawArcCW(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecDrawArcCCW:
         device->drawArcCCW(pos + cdPoint(elem->x, elem->y)); break;
       case cdDeviceStore::ecDrawText:
         device->drawText(elem->text, elem->val2); break;

      }

      if ( !dont_increm )
         elem++;

   }
}

