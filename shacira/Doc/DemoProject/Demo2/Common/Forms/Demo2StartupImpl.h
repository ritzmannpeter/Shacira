
#ifndef Demo2StartupImpl_H
#define Demo2StartupImpl_H

#include "Demo2Startup.h"
#include <qtimer.h>

class Demo2StartupImpl : public Demo2Startup
{
   Q_OBJECT
public slots:
   void showConsole();
public:
   Demo2StartupImpl(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   virtual ~Demo2StartupImpl();
   virtual void Info(const char * info, int type);
   virtual void Info(const char * info, unsigned int index, BOOL_T refresh);
private:
   QTimer * _RefreshTimer;

protected slots:
    virtual void languageChange();
};

#endif


