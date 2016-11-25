// ===========================================================================
// cwidgetcomm.h
// ===========================================================================
// vollstaendig aus Markus Wuertzens qtpostupdate.h uebernommen
// weil ich dort im laufenden System keine umfangreichen Aenderungen
// machen wollte

#ifndef __cwidgetcomm__
#define __cwidgetcomm__

#include <qobject.h>

class cWidgetCommRedirector;

class cWidgetComm
{ 
public:
   // Default-Konstruktor
   cWidgetComm();
   virtual ~cWidgetComm();
   void Notify(QEvent * event);
   // Diese Methode wird dann im Kontext des Qt-Thread aufgerufen
   virtual void GUIEvent(QEvent * event)  = 0;
private:
   cWidgetCommRedirector *_redirector;
};


class cWidgetCommRedirector : public QObject
{
   Q_OBJECT
public:
   cWidgetCommRedirector(cWidgetComm *target);
   virtual bool event(QEvent *e);
private:
   cWidgetComm *_target;
}; 

#endif

