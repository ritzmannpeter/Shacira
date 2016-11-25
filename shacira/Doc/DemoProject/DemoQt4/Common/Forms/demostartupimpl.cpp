
#include "demostartupimpl.h"
#include "qtextedit.h"
#include "cfixtext.h"

DemoStartupImpl::DemoStartupImpl(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
   : CStartupForm(parent, name)

{
   _RefreshTimer = NULL;
#ifndef QT_PLUGIN
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(showConsole()));
   _RefreshTimer->start(20);
#endif
   _ui.setupUi(this);
}

DemoStartupImpl::~DemoStartupImpl()
{
}

void DemoStartupImpl::Info(const char * info, int type)
{
   _ui.Step->setText(info);
}

void DemoStartupImpl::Info(const char * info, unsigned int index, BOOL_T refresh)
{
   _ui.Step->setText(info);
}

void DemoStartupImpl::showConsole()
{
   char buffer[1024] = {0};
   if (_Console != NULL) {
      int nread = _Console->Read(buffer, sizeof(buffer)-1);
      if (nread > 0) {
#ifdef QT4
         QString text = _ui.Console->toPlainText();
#else
         QString text = _ui.Console->text();
#endif
         _ui.Console->append(buffer);
#ifdef QT4
         text = _ui.Console->toPlainText();
#else
         text = _ui.Console->text();
#endif
      }
   }
}

void DemoStartupImpl::languageChange()
{
   _ui.retranslateUi(this);
}
