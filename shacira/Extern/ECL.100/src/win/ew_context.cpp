// ===========================================================================
// ew_context.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cEclObject
//     |
//     +--cdContext
//         |
//         +--cwContext       - Kontext fuer Zeichenoperationen auf dem
//         |                    Client-Bereich eines Fensters
//         |
//         +--cwInfoContext   - Anfrage-Kontext fuer Zeichenoperationen auf
//                              dem Bildschirm
//
// ===========================================================================

#include "win/ew_context.hpp"

#if defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
   #include "win/system/mfc/mfc_d.hpp"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "draw/ed_context.hpp"
#include "win/ew_windows.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwContext
// ---------------------------------------------------------------------------
//
// Kontext fuer Zeichenoperationen auf dem Client-Bereich eines Fensters.
//
//  cEclObject
//   +--cdContext
//       +--cwContext
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwContext : public cdContext {
   ECL_DECLARE(cwContext, cdContext)
   friend class ccwView;

public:

   // Draw-Kontext fuer den Client-Bereich von 'win' erzeugen
   inline cwContext(cwWindow *win) { init(win); }
   // Destruktor
   ~cwContext();


private:

   // Konstruktor fuer ccwView
   inline cwContext(void *ctxt);
   // Initialisierung
   void init(cwWindow *win);

};

#endif /*__INTERFACE__*/


// Implementierung cwContext
// ===========================================================================

cwContext::cwContext(void *ctxt)
{
   #if defined __ECL_W32__
      CPaintDC *pdc = (CPaintDC*)ctxt;
      RECT &rcp = pdc->m_ps.rcPaint;
      setContext(ctxt, false);
      setRedrawArea(cdRect(rcp.left, rcp.bottom, rcp.right, rcp.top));
      setEraseBkgnd(!!pdc->m_ps.fErase);
   #endif
}

cwContext::~cwContext()
{
}

void cwContext::init(cwWindow *win)
{
   setRedrawArea(cdRect(cdPoint(0,0), win->getClientSize()));
   setEraseBkgnd(false);

   if ( win != 0 && ccwWindow::__getWnd(win) != 0 ) {
      #if defined __ECL_W32__
         setContext(new CClientDC((CWnd*)ccwWindow::__getWnd(win)), true);
      #endif
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cwInfoContext
// ---------------------------------------------------------------------------
//
// Kontext fuer Anfragen ueber Zeichenoperationen auf Bildschirm-Fenstern.
//
//  cEclObject
//   +--cdContext
//       +--cwInfoContext
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwInfoContext : public cdContext {
   ECL_DECLARE(cwInfoContext, cdContext)

public:

   // Anfrage-Kontext fuer Zeichenoperation auf dem Bildschirm erzeugen
   inline cwInfoContext() { init(); }
   // Destruktor
   ~cwInfoContext();


private:

   // Initialisierung
   void init();

};

#endif /*__INTERFACE__*/


// Implementierung cwInfoContext
// ===========================================================================

void cwInfoContext::init()
{
   #if defined __ECL_W32__
      CDC *dc = new CDC;
      dc->CreateIC(TEXT("DISPLAY"), NULL, NULL, NULL);
      setContext(dc, true);
   #endif
}

cwInfoContext::~cwInfoContext()
{
}

