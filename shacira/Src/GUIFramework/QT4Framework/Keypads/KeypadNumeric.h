
#ifndef QT4

#pragma message(__LOC__ "this file should never be inluded qt 3")

#else

#ifndef _keypadnumeric_h_
#define _keypadnumeric_h_

#include "ui_KeypadNumeric.h"

class cQtKeypadNumericBase : public QDialog
{
    Q_OBJECT

public:
    cQtKeypadNumericBase( QWidget* parent = 0, const char* name = 0, bool modal = false, WIDGET_FLAGS_TYPE fl = 0 );
    ~cQtKeypadNumericBase();
protected:
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   inline virtual void changeEvent(QEvent * event)
   {
      if (event->type() == QEvent::LanguageChange) {
         languageChange();
      }
      QDialog::changeEvent(event);
   };
#endif

   inline virtual void languageChange()
   {
      _ui.retranslateUi(this);
   };

   Ui::cQtKeypadNumericBase _ui;
};

#endif // _keypadnumeric_h_

#endif // QT4
