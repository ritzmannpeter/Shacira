
#include "uiupdate.h"
#include "CWidgetBase.h"
#include "GUIFramework/Interface/cCCSInterface.h"

static void ProcessEventQueue()
{
   QApplication * application = qApp;
   if (application != NULL) {
      if (CWidgetBase::CheckThread()) {
         application->processEvents();
      }
   }
}

UiUpdate::UiUpdate(bool syncFlag) : _syncFlag(syncFlag)
{
   if (_syncFlag) {
      cCCSInterface::SetUiUpdateFunction(ProcessEventQueue);
   }
}

UiUpdate::~UiUpdate()
{
   if (_syncFlag) {
      cCCSInterface::SetUiUpdateFunction(NULL);
   }
}



