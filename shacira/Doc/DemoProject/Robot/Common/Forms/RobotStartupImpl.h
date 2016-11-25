
#ifndef RobotStartupImpl_H
#define RobotStartupImpl_H

#include "RobotStartup.h"
#include <qtimer.h>

class RobotStartupImpl : public RobotStartup
{
   Q_OBJECT
public slots:
   void showConsole();
public:
   RobotStartupImpl(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   virtual ~RobotStartupImpl();
   virtual void Info(const char * info, int type);
   virtual void Info(const char * info, unsigned int index, BOOL_T refresh);
private:
   QTimer * _RefreshTimer;

protected slots:
    virtual void languageChange();
};

#endif


