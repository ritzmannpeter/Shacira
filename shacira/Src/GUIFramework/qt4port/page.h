
#ifndef _page_h_
#define _page_h_

#include <qwidget.h>
#include "CPage.h"

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
template <class TClass> class Page : public CPage
{
public:
   inline Page(QWidget * parent = 0, const char * name = NULL, Qt::WindowFlags flags = 0)
      : CPage(parent, name, flags)
   {
      _ui.setupUi(this);
   };
   virtual ~Page()
   {
   };
protected:
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   inline virtual void changeEvent(QEvent * event )
   {
      if (event->type() == QEvent::LanguageChange) {
         languageChange();
      }
      CPage::changeEvent(event);
   };
#endif

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

#endif // _page_h_


