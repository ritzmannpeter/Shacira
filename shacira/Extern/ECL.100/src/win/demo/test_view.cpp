// ===========================================================================
// test_view.cpp                                 ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//  cBase
//   |
//   +--cwApplication
//   |   |
//   |   +--cTestViewApp
//   |
//   +--cwWindow
//       |
//       +--cwFrame
//           |
//           +--cTestViewFrameWnd
//
// ===========================================================================

#include "win/demo/tw_direct_view.hpp"

#include "win/ew_application.hpp"
#include "win/ew_frames.hpp"
#include "win/ew_views.hpp"
#include "win/ew_toolbars.hpp"
#include "resource.h"




// ===========================================================================
// cTestViewFrameWnd
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwFrame
//          +--cTestViewFrameWnd
//
// ===========================================================================

class cTestViewFrameWnd : public cwFrame {

   cDirectView direct_view;
   cwToolBar toolbar;

public:

   cTestViewFrameWnd()
   {
      // View zuordnen und Fenster erzeugen
      setView(&direct_view);
      create(cResource(IDR_MAINFRAME), cwFrame::fsDockAny);

      toolbar.create(this, cResource(IDR_TOOLBAR), cwToolBar::dksAlignTop, "Werkzeugleiste");
      toolbar.dockWindow(cwToolBar::dpTop);
   }

   bool onCommand(const cwCmdEvt& cmd)
   {
      return cwFrame::onCommand(cmd);
   }

};




// ===========================================================================
// cTestViewApp
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwApplication
//      +--cTestViewApp
//
// ===========================================================================

class cTestViewApp : public cwApplication {

   cTestViewFrameWnd *frame;

public:

   cTestViewApp() :
      cwApplication("EclView", "2i Industrial Informatics")
   {
      // Nix zu tun...
   }

   bool onInit()
   {
      cBase::setDebugMask("ERROR ASSERT");

      // Wichtig: Haupt-Frame dynamisch erzeugen und dieses als
      // Applikations-Hauptfenster bekanntgeben

      frame = new0 cTestViewFrameWnd();
      setMainWindow(frame);

      return true;
   }

   int onExit()
   {
      // Wichtig: Frame loeschen, _bevor_ onExit beendet ist!

      delete frame;
      return 0;
   }

};




// ===========================================================================
// theApp
// ---------------------------------------------------------------------------
//
// ===========================================================================

cTestViewApp theApp;
