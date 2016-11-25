
#ifndef _cwidgetfactory_h_
#define _cwidgetfactory_h_

#include <qwidgetfactory.h>

class CPage;

class CWidgetFactory : public QWidgetFactory
{
public:
   CWidgetFactory();
   virtual ~CWidgetFactory();
   virtual QWidget * createWidget(const QString & class_name, QWidget * parent, const char *name) const;
   static CPage * LoadPage(const char * ui_file, QWidget * parent);
};

#endif

