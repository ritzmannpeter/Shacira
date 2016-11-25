

#include "cQtKeypadNumeric.h"
#include "cQtPropertyWidget.h"

/// PR 2005-03-10 - added methods to set lower and upper limits for input
/// MW 2005-04-05 - info widget removed (comment out)

#include <qlineedit.h>
#include <qwidgetstack.h>
#include "qt4port.h"

cQtKeypadNumeric::cQtKeypadNumeric(QWidget* parent, const char* name, bool modal, WFlags fl)
   : cQtKeypadNumericBase(parent, name, modal, fl ? fl : Qt::WStyle_Customize|Qt::WStyle_NormalBorder|Qt::WStyle_Title),
     _number_validator(1000,1000,3,0),
     _keyboard_input(this)
{
   // Dialog-Font wird als Default für Layout und damit Buttons genommen, bigFont x1.3
   QFont f = font();
   _keyboard_input.setSmallFont(f);
   f.setPointSize(f.pointSize()*13 / 10);
   _keyboard_input.setBigFont(f);

   _keyboard_input.setEchoWidget(_new);
   
   // Signale im Fehlerfall verbinden
   connect( &_keyboard_input, SIGNAL( finalValidationFailed(const QString &) ),
            this, SLOT( slotValidationFailed(const QString &) ) );
   connect( &_keyboard_input, SIGNAL( clearValidationError() ),
            this, SLOT( slotClearValidationError() ) );

   //cQtPropertyWidget qp(this);
   //qp.SetProperty("_info.shown", false);
   adjustSize();

   // if base-class name and base caption are equal, then clear base caption
   if (cQtKeypadNumericBase::caption().isEmpty() == false) {
      if (strcmp(CONST_STRING(cQtKeypadNumericBase::name()), CONST_STRING(cQtKeypadNumericBase::caption())) == 0) {
         setCaption("");
      }
   } else {
      setCaption("");
   }
}



void cQtKeypadNumeric::setBigFont(const QFont &font)
{
   _keyboard_input.setBigFont(font);
}

QFont cQtKeypadNumeric::getBigFont() const
{
   return _keyboard_input.getBigFont();
}

void cQtKeypadNumeric::setSmallFont(const QFont &font)
{
   _keyboard_input.setSmallFont(font);
}

QFont cQtKeypadNumeric::getSmallFont() const
{
   return _keyboard_input.getSmallFont();
}



void cQtKeypadNumeric::setSyntaxValidator(QValidator *v)
{
   _keyboard_input.setSyntaxValidator(v);
}

void cQtKeypadNumeric::setSyntaxValidator(double min_val, double max_val, int prec)
{
   _keyboard_input.setSyntaxValidator(&_number_validator);
   _number_validator.setBottom(min_val);
   _number_validator.setTop(max_val);
   _number_validator.setDecimals(prec);
}

void cQtKeypadNumeric::setFinalValidator(iFinalValidator *v)
{
   _keyboard_input.setFinalValidator(v);
}


//void cQtKeypadNumeric::setInfo(const QString &i)
//{
//   cQtPropertyWidget qp(this);
//   qp.SetProperty("_info.text", i);
//   qp.SetProperty("_info.shown", (i.length() > 0));
//   adjustSize();
//}

void cQtKeypadNumeric::setLowerLimit(const QString & text)
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_lower_limit.text", text);
}

void cQtKeypadNumeric::setUpperLimit(const QString & text)
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_upper_limit.text", text);
}

void cQtKeypadNumeric::setCurrentValue(const QString &cv)
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_current.text",cv);
   _keyboard_input.setInput(cv);
}

QString cQtKeypadNumeric::getNewValue() const
{
   return _keyboard_input.getInput();
}

int cQtKeypadNumeric::exec()
{
   _keyboard_input.initialize();
   slotClearValidationError();

   QString saved_input = _keyboard_input.getInput();
   if (QDialog::exec() == QDialog::Rejected) {
      _keyboard_input.setInput(saved_input);
      return QDialog::Rejected;
   }

   return QDialog::Accepted;
}


void cQtKeypadNumeric::slotValidationFailed(const QString &error)
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_error.shown", true);
   qp.SetProperty("_error.text", error);
   adjustSize();
   _new->selectAll();
}

void cQtKeypadNumeric::slotClearValidationError()
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_error.shown", false);
   adjustSize();
}

void cQtKeypadNumeric::setWidgetStacks(QString default_language)
{
   char stack_index = 0;
   if (_stricmp(CONST_STRING(default_language), "en-US") == 0) {
      stack_index = 1;
   }
   wStackLabelActual->raiseWidget(stack_index);
   wStackLabelNew->raiseWidget(stack_index);
   wStackMinLabel->raiseWidget(stack_index);
   wStackMaxLabel->raiseWidget(stack_index);
}



