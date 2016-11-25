
#include "FirstHeader.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Process/cSHProcess.h"
#include "System/Process/cResources.h"
#include "qtgui"
#include "GUIFramework/Interface/cCCSInterface.h"
#include <qwindowsxpstyle.h>
#include "System/ApplicationInterface.h"

int main(int argc, char* argv[])
{
   InitializeApplicationInterface();
   cResources::set_UseDebugLog(false);
   cResources::set_LogFileName("Robot.log");
   cResources(argc, argv);
   BOOL_T disable_gui = false;
   cResources::GetOption("DisableGUI", disable_gui);
   if (disable_gui) {
      AllocConsole();
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
      cConsole * console = new cMemoryConsole;
      cResources::set_DefaultConsole(console);
      QApplication app(argc, argv);
      cQTUserInterface gui(&app, remote, "default", console);
      cCCSInterface itf(argc, argv);
      gui.Initialize(&itf, console);
      if (touch_screen) {
         app.setStyle(new cQtTouchStyle(2.0));
      } else {
         app.setStyle(new QWindowsStyle);
      }
      gui.Start(true);
   }
   return 0;
}
