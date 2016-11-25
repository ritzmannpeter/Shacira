
#ifndef _startuppage_h_
#define _startuppage_h_

#include <qwidget.h>
#include "CStartupForm.h"

#ifdef QT4
#include "qt4port.h"
#else
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : warning: "
#define NOT_PORTED(msg)
#define _CWIDGET_EXPORT_
#endif

#include "CWidgetBase.h"
template <class TClass> class StartupForm : public CStartupForm
{
public:
   inline StartupForm(QWidget * parent = NULL, const char * name = NULL, Qt::WindowFlags flags = 0)
      : CStartupForm(parent, name, flags)
   {
      _ui.setupUi(this);
   };
   virtual ~StartupForm()
   {
   };
protected:
   inline virtual void languageChange()
   {
      _ui.retranslateUi(this);
   };
protected:
   TClass _ui;
public:
   inline TClass & ui()
   {
      CWidgetBase::CheckThread();
      return _ui;
   };
};

#endif // _startuppage_h_


