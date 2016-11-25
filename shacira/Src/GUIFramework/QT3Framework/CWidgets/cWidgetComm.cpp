// ===========================================================================
// cwidgetcomm.cpp
// ===========================================================================
// vollstaendig aus Markus Wuertzens cWidgetComm.h uebernommen
// weil ich dort im laufenden System keine umfangreichen Aenderungen
// machen wollte


// Interface
#include "cwidgetcomm.h"

// System
#include <qapplication.h>

cWidgetComm::cWidgetComm() :
   _redirector(new cWidgetCommRedirector(this))
{
}

cWidgetComm::~cWidgetComm()
{
   delete _redirector;
}

void cWidgetComm::Notify(QEvent * event)
{
   QApplication::postEvent((QObject*)_redirector, event);
}



cWidgetCommRedirector::cWidgetCommRedirector(cWidgetComm *target) :
   _target(target)
{
}

bool cWidgetCommRedirector::event(QEvent *e)
{
   if (e->type() == QEvent::User) {
      _target->GUIEvent(e);
      return true;
   } else {
      // alle anderen Events weitergeben
      return QObject::event(e);
   }
}

