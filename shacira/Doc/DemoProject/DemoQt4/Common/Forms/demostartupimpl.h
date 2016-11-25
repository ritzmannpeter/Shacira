
#ifndef DemoStartupImpl_H
#define DemoStartupImpl_H

#include <qtimer.h>

#ifdef QT4
#include "CStartupForm.h"
#include "ui_demostartup.h"
class DemoStartupImpl : public CStartupForm
#else
#include "demostartup.h"
class DemoStartupImpl : public DemoStartup
#endif
{
   Q_OBJECT
public slots:
   void showConsole();
public:
   DemoStartupImpl(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   virtual ~DemoStartupImpl();
   virtual void Info(const char * info, int type);
   virtual void Info(const char * info, unsigned int index, BOOL_T refresh);
private:
   QTimer * _RefreshTimer;

protected slots:
    virtual void languageChange();

#ifdef QT4
private:
   Ui::DemoStartup _ui;
#endif

};

#endif


