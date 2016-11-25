// ===========================================================================
// ed_font.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdFont             - Schriftart
//
// ===========================================================================

#include "draw/ed_font.hpp"
#include "base/eb_prof.hpp"
#include "win/ew_windows.hpp"

#if defined __ECL_W32__
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

#include "base/eb_str.hpp"

class cProfile;
class cwWindow;

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdFont
// ---------------------------------------------------------------------------
//
// 'font_name' besteht aus einem Namen (nnnn) und einem optionalen Beschrei-
// bungsteil. Name und Beschreibungsteil sind durch ein "|"-Zeichen vonein-
// ander abgetrennt. Der Beschreibungsteil ist nicht interoperabel, zu seiner
// Kennzeichnung beginnt er jedoch mit der Kennung des Ursprungssystems (sss).
//
//    Schreibweise 1: "nnnn"
//    Schreibweise 2: "nnnn|sss:a,b,c,d,e"
//
//  cBase
//   +--cdDevice
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdFont : public cBase {
   friend class ccdFont;

public:

   // Konstruktor
   inline cdFont() { init(); }
   // Destruktor
   ~cdFont();

   // Schriftart ueber Namen (inkl. evtl. Beschreibungsteil) erzeugen
   bool create(cString font_name, int point_size = -1, double factor = 0.0);
   // Freigeben der Schriftart
   void destroy();

   // Name (inkl. evtl. Beschreibungsteil) der Schriftart erfragen
   cString getFontName() const;
   // Beschreibung der Schriftart (Name + Stil) erfragen
   cString getFontDescr() const;
   // Punktgroesse erfragen
   int getPointSize() const;

   // Auswahldialog anzeigen
   bool showDialog(cwWindow *parent = 0);

   // Schriftart aus Profile laden bzw. ueber Auswahldialog
   bool load(cProfile *prf, cString app, cString key, cwWindow *parent = 0, bool show_dlg = false);
   // Sichern der Schriftart im Profile
   void save(cProfile *prf, cString app, cString key) const;


private:

   // Zeiger auf Font-Objekt
   void *font;

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cdFont
// ===========================================================================

cdFont::~cdFont()
{
   #if defined __ECL_W32__
      delete (CFont*)font;
   #else
      // ...
   #endif
}

void cdFont::init()
{
   #if defined __ECL_W32__
      font = new CFont;
   #else
      font = 0;
   #endif
}

bool cdFont::create(cString font_name, int point_size, double factor)
{
   destroy();

   #if defined __ECL_W32__

      // Format von 'font_name' unter Win32:
      //
      // name=W32:szFaceName,nHeight,nWidth,nEscapement,nOrientation,nWeight,
      //          bItalic,bUnderline,cStrikeOut,nCharSet,nOutPrecision,
      //          nClipPrecision,nQuality,nPitchAndFamily

      if ( font_name.isEmpty() ) {
         // no font (yet)
         return true;
      }

      int pos = font_name.getPos(";");

      if ( pos > 0 ) {
         cString descr_name = font_name.getSubstr(0, pos-1);
         int pos2 = font_name.getPos(";", pos+1);
         if ( __ECL_ASSERT1__(pos2 > 0 && font_name.getSubstr(pos, pos2) == ";W32;") ) {
            cString params = font_name.getMid(pos2 + 1);
            LOGFONT lf;
            int height = params.getPart(1).getLong();
            int width  = params.getPart(2).getLong();
            if ( factor > 0.0 ) {
               HDC hDC = ::GetDC(NULL);
               int lpy = ::GetDeviceCaps(hDC, LOGPIXELSY);
               int ps = (labs(height) * 72 + 36) / lpy;
               ::ReleaseDC(NULL, hDC);
               height = - int(double(ps) * factor);
            }
            lf.lfHeight          = height;
            lf.lfWidth           = width;
            lf.lfEscapement      = params.getPart(3).getLong();
            lf.lfOrientation     = params.getPart(4).getLong();
            lf.lfWeight          = params.getPart(5).getLong();
            lf.lfItalic          = (unsigned char)params.getPart(6).getLong();
            lf.lfUnderline       = (unsigned char)params.getPart(7).getLong();
            lf.lfStrikeOut       = (unsigned char)params.getPart(8).getLong();
            lf.lfCharSet         = (unsigned char)params.getPart(9).getLong();
            lf.lfOutPrecision    = (unsigned char)params.getPart(10).getLong();
            lf.lfClipPrecision   = (unsigned char)params.getPart(11).getLong();
            lf.lfQuality         = (unsigned char)params.getPart(12).getLong();
            lf.lfPitchAndFamily  = (unsigned char)params.getPart(13).getLong();
            strxcpy(lf.lfFaceName, params.getPart(0), LF_FACESIZE);
            int rc = ((CFont*)font)->CreateFontIndirect(&lf);
            return __ECL_ASSERT1__(rc != 0);
         }
      } else {
         if ( __ECL_ASSERT1__(point_size > 0) ) {
            int rc = ((CFont*)font)->CreatePointFont(point_size, font_name);
            return __ECL_ASSERT1__(rc != 0);
         }
      }

      return false;

   #else
   #endif
}

void cdFont::destroy()
{
   #if defined __ECL_W32__
      if ( (HFONT)*((CFont*)font) != NULL )
         ((CFont*)font)->DeleteObject();
   #else
      // ...
   #endif
}

cString cdFont::getFontName() const
{
   #if defined __ECL_W32__

      if ( (HFONT)*((CFont*)font) != NULL ) {
         LOGFONT lf;
         if ( __ECL_ASSERT1__(((CFont*)font)->GetLogFont(&lf)) ) {
            return cStringf("%s;W32;%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                            (const char *)getFontDescr(),
                            lf.lfFaceName, lf.lfHeight, lf.lfWidth, lf.lfEscapement,
                            lf.lfOrientation, lf.lfWeight, lf.lfItalic, lf.lfUnderline,
                            lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision,
                            lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily);
         }
      }

   #else
      // ...
   #endif

   return getFontDescr();
}

cString cdFont::getFontDescr() const
{
   #if defined __ECL_W32__

      if ( (HFONT)*((CFont*)font) == NULL ) {
         return 0;
      } else {
         LOGFONT lf;
         if ( __ECL_ASSERT1__(((CFont*)font)->GetLogFont(&lf)) ) {
            cString descr = lf.lfFaceName;
            if ( lf.lfWeight > 500 )
               descr += " Bold";
            if ( lf.lfItalic )
               descr += " Italic";
            return descr;
         } else {
            return "Arial";
         }
      }

   #else
      // ...
   #endif
}

int cdFont::getPointSize() const
{
   #if defined __ECL_W32__

      if ( (HFONT)*((CFont*)font) == NULL ) {
         return 0;
      } else {
         LOGFONT lf;
         if ( __ECL_ASSERT1__(((CFont*)font)->GetLogFont(&lf)) ) {
            HDC hDC = ::GetDC(NULL);
            int lpy = ::GetDeviceCaps(hDC, LOGPIXELSY);
            int ps = (labs(lf.lfHeight) * 72 + 36) / lpy;
            ::ReleaseDC(NULL, hDC);
            return ps;
         } else {
            return -1;
         }
      }

   #else
      // ...
   #endif
}

bool cdFont::showDialog(cwWindow *parent)
{
   #if defined __ECL_W32__

      LOGFONT lf;
      bool ok = false;
      CWnd *mfc_parent = (CWnd*)ccwWindow::__getWnd(parent);

      if ( (HFONT)*((CFont*)font) == NULL ) {
         CFontDialog fd(NULL, CF_EFFECTS|CF_SCREENFONTS, NULL, mfc_parent);
         ok = fd.DoModal() == IDOK;
         if ( ok )
            fd.GetCurrentFont(&lf);
      } else {
         if ( __ECL_ASSERT1__(((CFont*)font)->GetLogFont(&lf)) ) {
            CFontDialog fd(&lf, CF_EFFECTS|CF_SCREENFONTS, NULL, mfc_parent);
            ok = fd.DoModal() == IDOK;
            if ( ok ) {
               fd.GetCurrentFont(&lf);
               ((CFont*)font)->DeleteObject();
            }
         }
      }

      if ( ok && __ECL_ASSERT1__(((CFont*)font)->CreateFontIndirect(&lf)) )
         return true;

   #else
      // ...
   #endif

   return false;
}

bool cdFont::load(cProfile *prf, cString app, cString key, cwWindow *parent, bool show_dlg)
{
   bool ok = false;

   cString font_name = prf->read(app, key);

   if ( !font_name.isEmpty() )
      ok = create(font_name);

   return show_dlg ? showDialog(parent) : ok;
}

void cdFont::save(cProfile *prf, cString app, cString key) const
{
   prf->write(app, key, getFontName());
}

