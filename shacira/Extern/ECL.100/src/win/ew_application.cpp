// ===========================================================================
// ew_application.cpp                                           ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cwApplication
//
// ===========================================================================

#include "win/ew_application.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #include <os2.h>
   #include "win/system/pm/pm.hpp"
#elif defined __ECL_W32__
   #include "win/system/mfc/mfc.hpp"
/*
   #ifdef _DEBUG
      #define new DEBUG_NEW
      #undef THIS_FILE
      static char THIS_FILE[] = __FILE__;
   #endif
*/
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"
#include "base/eb_prof.hpp"
#include "base/eb_cmdarg.hpp"
#include "win/ew_base.hpp"
#include "win/ew_commands.hpp"

class cwWindow;

#endif /*__INTERFACE__*/




// Lokale Variablen und Funktionen
// ===========================================================================

static void DbgTrace(char *buf, int len)
{
   #if defined __ECL_VCPP__
      while ( len > 512 ) {
         char save = buf[512];
         buf[512] = '\0';
         TRACE0(buf);
         buf[512] = save;
         buf = &buf[512];
         len -= 512;
      }
      if ( len > 0 )
         TRACE0(buf);
   #endif
}

static int DbgPrintf(const char *fmt, ...)
{
   int num;
   va_list ap;
   char buf[2048];

   va_start(ap, fmt);
   num = vsprintf(buf, fmt, ap);
   va_end(ap);

   DbgTrace(buf, num);
   return num;
}

#if defined __ECL_W32__

   // - m_pszAppName im Konstruktor von cwApplication setzen
   // - 'srv'-Komponente im Konstruktor von cwApplication setzen
   // - InitInstance von TWCWinApp fuehrt nur intere Initialisierungen aus
   // - Neue exportierte Funktion "runApplication":
   //    - ruft cwApplication::onInit auf
   //    - Fuehrt Hauptschleife aus
   //    - Muss von WinMain im Hauptprogramm aufgerufen werden

   WCWinApp theApp(0, "APP");

   BOOL AFXAPI EclOleInit()
   {
      _AFX_THREAD_STATE* pState = AfxGetThreadState();
      ASSERT(!pState->m_bNeedTerm);    // calling it twice?

      cBase::setPrintFunc(DbgPrintf);

      // Special case DLL context to assume that the calling app initializes OLE.
      // For DLLs where this is not the case, those DLLs will need to initialize
      // OLE for themselves via OleInitialize.  This is done since MFC cannot provide
      // automatic uninitialize for DLLs because it is not valid to shutdown OLE
      // during a DLL_PROCESS_DETACH.
      //if (afxContextIsDLL)
      //{
      // pState->m_bNeedTerm = -1;  // -1 is a special flag
      // return TRUE;
      //}

      // first, initialize OLE
      SCODE sc = ::OleInitialize(NULL);
      if (FAILED(sc))
      {
         // warn about non-NULL success codes
         TRACE1("Warning: OleInitialize returned scode = %s.\n",
            AfxGetFullScodeString(sc));
         goto InitFailed;
      }
      // termination required when OleInitialize does not fail
      pState->m_bNeedTerm = TRUE;

      // hook idle time and exit time for required OLE cleanup
      CWinThread* pThread; pThread = AfxGetThread();
      pThread->m_lpfnOleTermOrFreeLib = AfxOleTermOrFreeLib;

      // allocate and initialize default message filter
      if (pThread->m_pMessageFilter == NULL)
      {
         pThread->m_pMessageFilter = new COleMessageFilter;
         ASSERT(AfxOleGetMessageFilter() != NULL);
         AfxOleGetMessageFilter()->Register();
      }
      return TRUE;

   InitFailed:
      AfxOleTerm();
      return FALSE;
   }

   void AFXAPI EclOleTerm(BOOL bJustRevoke)
   {
   	// release clipboard ownership
   	COleDataSource::FlushClipboard();

   	// revoke all class factories
   	COleObjectFactory::RevokeAll();

   #ifndef _AFX_NO_OCC_SUPPORT
   	AfxOleUnlockAllControls();
   #endif

   	if (!bJustRevoke)
   	{
   		CWinThread* pThread = AfxGetThread();
   		if (pThread != NULL)
   		{
   			// destroy message filter (may be derived class)
   			delete pThread->m_pMessageFilter;
   			pThread->m_pMessageFilter = NULL;
   		}

   		// terminate OLE last
   		_AFX_THREAD_STATE* pState = AfxGetThreadState();
   		// -1 is special case, so need to compare against TRUE
   		if (pState->m_bNeedTerm == TRUE)
   		{
   			CoFreeUnusedLibraries();
   			::OleUninitialize();
   			pState->m_bNeedTerm = FALSE;
   		}
   	}
   }

#endif




#ifdef __INTERFACE__

// ===========================================================================
// cwApplication
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwApplication
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwApplication : public cBase {
   friend class ccwApplication;

public:

   // Konstruktor
   cwApplication(cString app_name, cString company_name = 0);
   // Destruktor
   virtual ~cwApplication();

   // Zeiger auf _DAS_ Applikationsobjekt ermitteln
   static cwApplication *getTheApp();

   // Name der Applikation erfragen (vgl. cwApplication-Konstruktor)
   static cString getAppName();
   // Pfadname der ausfuehrbaren Datei der Applikation erfragen
   static cString getAppPathName();
   // Name der Herstellerfirma erfragen
   static cString getCompanyName();

   // Zeiger auf das Profile-Objekt der Anwendung ermitteln
   static cProfile *getProfile();
   // Zeiger auf das CmdOptions-Objekt der Kommandozeile ermitteln
   static cCmdOptions *getOptions();
   // Zeiger auf das Hauptfenster der Anwendeung erfragen
   static cwWindow *getMainWindow();

   // Hauptfenster der Anwendung bekanntmachen
   void setMainWindow(cwWindow *main_window);


protected:

   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, um die Applikationsinstanz zu initialisieren
   virtual bool onInit() = 0;
   // Wird aufgerufen, um die Hauptschleife der Applikation auszufuehren
   virtual int onRun();
   // Wird aufgerufen, um die Applikationsinstanz zu deinitialisieren
   virtual int onExit();

   // Wird zur Behandlung von cmdAppAbout aufgerufen...
   virtual void onAppAbout();
   // Wird zur Behandlung von cmdAppExit aufgerufen...
   virtual void onAppExit();
   // Wird zur Behandlung von cmdFileNew aufgerufen...
   virtual void onFileNew();
   // Wird zur Behandlung von cmdFileOpen aufgerufen...
   virtual void onFileOpen();
   // Wird zur Behandlung von cmdFilePrintSetup aufgerufen...
   virtual void onFilePrintSetup();
   // Wird zur Behandlung von cmdHelpContext aufgerufen...
   virtual void onHelpContext();
   // Wird zur Behandlung von cmdHelp aufgerufen...
   virtual void onHelp();
   // Wird zur Behandlung von cmdHelpIndex aufgerufen...
   virtual void onHelpIndex();
   // Wird zur Behandlung von cmdHelpFinder aufgerufen...
   virtual void onHelpFinder();
   // Wird zur Behandlung von cmdHelpUsing aufgerufen...
   virtual void onHelpUsing();


protected:

   void *_app;       // Zeiger auf Wrapper-Objekt


   // ECL/win Internas
   // ================

   // Trennen vom Wrapper
   void __disconnect();
   // Eigenen Zeiger auf Wrapper-Objekt ermitteln
   void *__getApp();
   const void *__getApp() const;
   // Zeiger auf Wrapper-Objekt ermitteln (statische Variante)
   static void *__getApp(cwApplication *application);
   static const void *__getApp(const cwApplication *application);

   // Standard-Befehl von Main-Window ausfuehren
   // rc: true -> Meldung bearbeitet; false -> Meldung nicht bearbeitet
   bool __onFrameCommand(cwWindow *win, const cwCmdEvt& cmd);
   // Wird VOR onInit() aufgerufen
   void __onPreInit();
   // Wird NACH onExit() aufgerufen
   void __onPostExit();


private:

   // Zeiger auf die (einzige) Applikations-Struktur
   static cwApplication *the_app;
   // Name der Applikation
   cString app_name;
   // Name der Herstellerfirma
   cString company_name;
   // Zeiger auf das aktuelle Main-Window
   cwWindow *main_window;
   // Zeiger auf das aktuelle CmdOptions-Objekt
   cCmdOptions *options;
   // Das aktuelle Profile-Objekt
   cProfile profile;

};

#endif /*__INTERFACE__*/


// Implementierung cwApplication
// ===========================================================================

cwApplication * cwApplication::the_app = 0;

cwApplication::cwApplication(cString the_app_name, cString the_company_name) :
   app_name(the_app_name), company_name(the_company_name),
   profile(":USR:" + (the_company_name.isEmpty() ? 0 : (the_company_name + "/")) + the_app_name)
{
   __ECL_ASSERT1__(the_app == 0);
   main_window = 0;
   options = 0;

   #if defined __ECL_W32__
      _app = &theApp; // new WCWinApp(this, app_name);
      theApp.SetSrv(this);
      the_app = this;
   #else
      _app = 0;
      // ???
   #endif
}

cwApplication::~cwApplication()
{
   #if defined __ECL_W32__
      // ...
   #else
      delete _app;
   #endif
}


cwApplication * cwApplication::getTheApp()
{
   return the_app;
}

cString cwApplication::getAppName()
{
   return the_app->app_name;
}

cString cwApplication::getCompanyName()
{
   return the_app->company_name;
}

cString cwApplication::getAppPathName()
{
   #if defined __ECL_W32__
      LPTSTR cmdline = GetCommandLine();
      cString cl = cmdline;
      return cl.getPart(0, "\"", " ");
   #else
      // ...
   #endif
}

cwWindow * cwApplication::getMainWindow()
{
   return the_app->main_window;
}

cProfile * cwApplication::getProfile()
{
   return &the_app->profile;
}

cCmdOptions * cwApplication::getOptions()
{
   return the_app->options;
}

void cwApplication::setMainWindow(cwWindow *main_window)
{
   if ( __ECL_ASSERT1__(main_window != 0) ) {
      cwApplication::main_window = main_window;
      #if defined __ECL_W32__
         theApp.m_pMainWnd = (CWnd*)ccwWindow::__getWnd(main_window);
      #else
         // ...
      #endif
   }
}

int cwApplication::onExit()
{
   return 0;
}

int cwApplication::onRun()
{
   #if defined __ECL_W32__
      return theApp.Run();
   #else
      // ...
   #endif
}

void cwApplication::onAppExit()
{
   #if defined __ECL_W32__
      //if ( main_window->allowClose(0) )
      AfxPostQuitMessage(0);
   #else
      // ...
   #endif
}

void cwApplication::onAppAbout()
   { }
void cwApplication::onFileNew()
   { }
void cwApplication::onFileOpen()
   { }
void cwApplication::onFilePrintSetup()
   { }
void cwApplication::onHelpContext()
   { }
void cwApplication::onHelp()
   { }
void cwApplication::onHelpIndex()
   { }
void cwApplication::onHelpFinder()
   { }
void cwApplication::onHelpUsing()
   { }


// ECL/win Internas
// ================

void cwApplication::__disconnect()
{
   _app = 0;
}

void * cwApplication::__getApp()
{
   return _app;
}

const void * cwApplication::__getApp() const
{
   return _app;
}

void * cwApplication::__getApp(cwApplication *application)
{
   return application ? application->_app : 0;
}

const void * cwApplication::__getApp(const cwApplication *application)
{
   return application ? application->_app : 0;
}

bool cwApplication::__onFrameCommand(cwWindow *win, const cwCmdEvt& cmd)
{
   if ( win == main_window ) { // Nur beim Hauptfenster ausfuehren!

      switch ( cmd.getId() ) {
      case cwCmdEvt::cmdAppAbout:         onAppAbout();        return true;
      case cwCmdEvt::cmdAppExit:          onAppExit();         return true;
      case cwCmdEvt::cmdSysClose:         onAppExit();         return true;
      case cwCmdEvt::cmdFileNew:          onFileNew();         return true;
      case cwCmdEvt::cmdFileOpen:         onFileOpen();        return true;
      case cwCmdEvt::cmdFilePrintSetup:   onFilePrintSetup();  return true;
      case cwCmdEvt::cmdHelpContext:      onHelpContext();     return true;
      case cwCmdEvt::cmdHelp:             onHelp();            return true;
      case cwCmdEvt::cmdHelpIndex:        onHelpIndex();       return true;
      case cwCmdEvt::cmdHelpFinder:       onHelpFinder();      return true;
      case cwCmdEvt::cmdHelpUsing:        onHelpUsing();       return true;
      }

   }

   return false;
}

void cwApplication::__onPreInit()
{
   #if defined __ECL_W32__
      EclOleInit();
   #endif
}

void cwApplication::__onPostExit()
{
   #if defined __ECL_W32__
      EclOleTerm(false);
   #endif
}


