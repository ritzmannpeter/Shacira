
#ifndef _cApplicationGuard_h
#define _cApplicationGuard_h

#include <qwidget.h>
#include <qapplication.h>

class cApplicationGuard : public QWidget
{
   Q_OBJECT

public:
   cApplicationGuard();
   virtual ~ cApplicationGuard();
public slots:
   virtual void Shutdown();
};

#endif
