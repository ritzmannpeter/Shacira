// ===========================================================================
// mfc_m.cpp                                     ECL (ET's tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die Standard-Funktion WinMain zur Verfuegung.
//
// ===========================================================================

#include "win/ew_application.hpp"
#include "win/system/mfc/mfc_c.hpp"
#include "base/eb_cmdarg.hpp"

//void __stdcall AfxSetResourceHandle(void *hInstResource);

#define RC_INIT_RES_FAILED 1001
#define RC_INIT_APP_FAILED 1002

int __ECL_DLLEXPORT__ __stdcall WinMain(void * hInstance, void *, const char *lpCmdLine, int nShowCmd)
{
   cwApplication *the_app = cwApplication::getTheApp();

   ccwApplication::initApplication(nShowCmd);
   ccwApplication::setResourceHandle(hInstance);

   int rc;

   if ( __ECL_ASSERT1__(the_app != 0) ) {

      // Try not to waste too much stack, so put big structures into the heap

      cCmdOptions *options = new cCmdOptions((char *)lpCmdLine, (char *)(const char *)the_app->getAppName());
      ccwApplication::setCmdOptions(the_app, options);

      if ( ccwApplication::onInit(the_app) ) {
         rc = ccwApplication::onRun(the_app);
      } else {
         rc = RC_INIT_APP_FAILED;
      }

      // TBD: delete options;

   } else {
      rc = RC_INIT_RES_FAILED;
   }

   return rc;
}

