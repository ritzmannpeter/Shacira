
#ifndef _actiondialog_h_
#define _actiondialog_h_

#include <qwidget.h>
#include "CActionDialog.h"

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
template <class TClass> class ActionDialog : public CActionDialog
{
public:
   inline ActionDialog(QWidget * parent = NULL, const char * name = NULL, Qt::WindowFlags flags = 0)
      : CActionDialog(parent, name, flags)
   {
      _ui.setupUi(this);
   };
   virtual ~ActionDialog()
   {
   };
protected:
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   inline virtual void changeEvent(QEvent * event )
   {
      if (event->type() == QEvent::LanguageChange) {
         languageChange();
      }
      CActionDialog::changeEvent(event);
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

#endif // _actiondialog_h_


