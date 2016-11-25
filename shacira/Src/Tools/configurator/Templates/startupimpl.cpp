
#include "demostartupimpl.h"
#include "demostartup.h"
#include "qtextedit.h"
#include "cfixtext.h"

DemoStartupImpl::DemoStartupImpl(QWidget * parent, const char * name, WFlags f)
   : DemoStartup(parent, name)

{
   _RefreshTimer = NULL;
#ifndef QT_PLUGIN
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(showConsole()));
   _RefreshTimer->start(20);
#endif
}

DemoStartupImpl::~DemoStartupImpl()
{
}

void DemoStartupImpl::Info(const char * info, int type)
{
   Step->setText(info);
}

void DemoStartupImpl::Info(const char * info, unsigned int index, BOOL_T refresh)
{
   Step->setText(info);
}

void DemoStartupImpl::showConsole()
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

void DemoStartupImpl::languageChange()
{
    DemoStartup::languageChange();
}
