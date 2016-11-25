
#include "Demo2StartupImpl.h"
#include "Demo2Startup.h"
#include "CFixText.h"
#include <qtextedit.h>

Demo2StartupImpl::Demo2StartupImpl(QWidget * parent, const char * name, WFlags f)
   : Demo2Startup(parent, name)

{
   _RefreshTimer = NULL;
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(showConsole()));
   _RefreshTimer->start(20);
}

Demo2StartupImpl::~Demo2StartupImpl()
{
}

void Demo2StartupImpl::Info(const char * info, int type)
{
   Step->setText(info);
}

void Demo2StartupImpl::Info(const char * info, unsigned int index, BOOL_T refresh)
{
   Step->setText(info);
}

void Demo2StartupImpl::showConsole()
{
   char buffer[1024] = {0};
   if (_Console != NULL) {
      int nread = _Console->Read(buffer, sizeof(buffer)-1);
      if (nread > 0) {
         QString text = Console->text();
         Console->append(buffer);
         text = Console->text();
      }
   }
}

void Demo2StartupImpl::languageChange()
{
    Demo2Startup::languageChange();
}
