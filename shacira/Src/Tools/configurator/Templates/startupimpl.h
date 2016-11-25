
#ifndef DemoStartupImpl_H
#define DemoStartupImpl_H

#include "demostartup.h"
#include <qtimer.h>

class DemoStartupImpl : public DemoStartup
{
   Q_OBJECT
public slots:
   void showConsole();
public:
   DemoStartupImpl(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   virtual ~DemoStartupImpl();
   virtual void Info(const char * info, int type);
   virtual void Info(const char * info, unsigned int index, BOOL_T refresh);
private:
   QTimer * _RefreshTimer;

protected slots:
    virtual void languageChange();
};

#endif


