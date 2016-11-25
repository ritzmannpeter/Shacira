
#include "RobotStartupImpl.h"
#include "RobotStartup.h"
#include "CFixText.h"
#include <qtextedit.h>

RobotStartupImpl::RobotStartupImpl(QWidget * parent, const char * name, WFlags f)
   : RobotStartup(parent, name)

{
   _RefreshTimer = NULL;
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(showConsole()));
   _RefreshTimer->start(20);
}

RobotStartupImpl::~RobotStartupImpl()
{
}

void RobotStartupImpl::Info(const char * info, int type)
{
   Step->setText(info);
}

void RobotStartupImpl::Info(const char * info, unsigned int index, BOOL_T refresh)
{
   Step->setText(info);
}

void RobotStartupImpl::showConsole()
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

void RobotStartupImpl::languageChange()
{
    RobotStartup::languageChange();
}
