
#include "FirstHeader.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Process/cSHProcess.h"
#include "System/Process/cResources.h"
#include "GUIFramework/Interface/cCCSInterface.h"
#include "GUIFramework/cNodeList.h"
#include "GUIFramework/cNode.h"
#include "cQTUserInterface.h"
#include "cwidgetbase.h"
#include <qwindowsxpstyle.h>
#include "../CustomBase/configure_app.h"
#include <qtooltip.h>

// Ctrl + x handler
BOOL WINAPI CtrlHandler(DWORD dwCtrlType)
{
   switch (dwCtrlType) {
   case CTRL_C_EVENT:
      InfoPrintf("CTRL+C\n");
      cResources::ShutDown();
      break;
   case CTRL_BREAK_EVENT:
      InfoPrintf("CTRL+BREAK\n");
      break;
   case CTRL_CLOSE_EVENT:
      InfoPrintf("CTRL+CLOSE\n");
      break;
   case CTRL_LOGOFF_EVENT:
      InfoPrintf("CTRL+LOGOFF\n");
      break;
   case CTRL_SHUTDOWN_EVENT:
      InfoPrintf("CTRL+SHUTDOWN\n");
      cResources::ShutDown();
      break;
   }
   return true;
}

int main(int argc, char* argv[])
{
   ConfigureApp();
   cResources::set_UseDebugLog(false);
   cResources::set_LogFileName("Demo.log");
   cResources(argc, argv);
   BOOL_T disable_gui = false;
   cResources::GetOption("DisableGUI", disable_gui);
   if (disable_gui) {
      AllocConsole();
      SetConsoleCtrlHandler(CtrlHandler, true);
      printf("console started\n");
      cCCSInterface itf(argc, argv);
      itf.Load();
      itf.Start();
      printf("process started\n");
      while (!cResources::ProcessTerminated()) {
         Sleep(500);
      }
   } else {
      BOOL_T touch_screen = false;
      cResources::GetOption("TouchScreen", touch_screen);
      if (touch_screen) {
         CWidgetBase::SetFlag(TOUCH_SCREEN);
      }
      BOOL_T full_screen = false;
      cResources::GetOption("FullScreen", full_screen);
      if (full_screen) {
         CWidgetBase::SetFlag(FULL_SCREEN);
      }
      BOOL_T cursor_disabled = false;
      cResources::GetOption("CursorDisabled", cursor_disabled);
      if (cursor_disabled) {
         CWidgetBase::SetFlag(CURSOR_DISABLED);
      }
      CWidgetBase::SetFlag(SHOW_REFERENCES);
      BOOL_T non_standard_buttons = false;
      cResources::GetOption("NonStandardButtons", non_standard_buttons);
      if (non_standard_buttons) {
         CWidgetBase::SetFlag(NON_STANDARD_BUTTONS);
      }
      BOOL_T control_widget_access = false;
      cResources::GetOption("ControlWidgetAccess", control_widget_access);
      if (control_widget_access) {
         CWidgetBase::SetGUIThreadId();
      }
      LONG_T DefaultGroupID = 0;
      cResources::GetOption("DefaultGroupID", DefaultGroupID);
      if (DefaultGroupID) {
         CWidgetBase::SetDefaultGroupId(DefaultGroupID);
      }
      BOOL_T remote = false;
      cResources::GetOption("Remote", remote);
      BOOL_T enable_gui_log = false;
      cResources::GetOption("EnableGUILog", enable_gui_log);
      if (enable_gui_log) {
         CWidgetBase::LogInitialize(VARIABLE_INIT |
                                    FUNCTION_INIT |
                                    CONTEXT_SETTINGS |
                                    CONNECTION_HIERARCHY |
                                    CONNECTIONS);
      }
      cConsole * console = new cMemoryConsole;
      cResources::set_DefaultConsole(console);
      QApplication app(argc, argv);
      cQTUserInterface gui(&app, remote, "default", console);
      cCCSInterface itf(argc, argv);
      gui.Initialize(&itf, console);
      if (touch_screen) {
//         app.setStyle(new cQtTouchStyle(2.0));
      } else {
         app.setStyle(new QWindowsStyle);
      }
      QFont f("arial", 11);
      app.setFont(f, "QTabWidget");
      QToolTip::setFont(f);
      gui.Start(true);
   }
   return 0;
}
