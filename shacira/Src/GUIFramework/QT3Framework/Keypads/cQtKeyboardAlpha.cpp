
/// PR 06.10.04 added methods setEchoMode and setLayout
/// PR 19.01.05 added error support

#include "cQtKeyboardAlpha.h"
#include "cQtPropertyWidget.h"
#include "qt4port.h"

cQtKeyboardAlpha::cQtKeyboardAlpha(QWidget* parent, const char* name, bool modal, WFlags fl) :
   cQtKeyboardAlphaBase(parent, name, modal, fl ? fl : Qt::WStyle_Customize|Qt::WStyle_NormalBorder|Qt::WStyle_Title),
   _keyboard_input(this)
{
   setMultiline(true);

   // Signale im Fehlerfall verbinden
   connect( &_keyboard_input, SIGNAL( finalValidationFailed(const QString &) ),
            this, SLOT( slotValidationFailed(const QString &) ) );
   connect( &_keyboard_input, SIGNAL( clearValidationError() ),
            this, SLOT( slotClearValidationError() ) );

   // if base-class name and base caption are equal, then clear base caption
   if (cQtKeyboardAlphaBase::caption().isEmpty() == false) {
      if (strcmp(CONST_STRING(cQtKeyboardAlphaBase::name()), CONST_STRING(cQtKeyboardAlphaBase::caption())) == 0) {
         setCaption("");
      }
   } else {
      setCaption("");
   }
}

void cQtKeyboardAlpha::setMultiline(bool multi)
{
   cQtPropertyWidget qp(this);
   if (multi) {
      _keyboard_input.setEchoWidget(_text_edit);
      qp.SetProperty("_text_edit.shown",true);
      qp.SetProperty("_line_edit.shown",false);
   } else {
      _keyboard_input.setEchoWidget(_line_edit);
      qp.SetProperty("_line_edit.shown",true);
      qp.SetProperty("_text_edit.shown",false);
   }
   adjustSize();
}

void cQtKeyboardAlpha::setEchoMode(QLineEdit::EchoMode mode)
{
   _line_edit->setEchoMode(mode);
}

void cQtKeyboardAlpha::setLayout(cQtKeyboard::LAYOUT_TYPE layout)
{
   _keyboard->setLayout(layout);
   _keyboard_input.setWidget(this);

   // _keyboard-Font wird als Default für smallFont genommen, bigFont x1.3
   QFont f = _keyboard->font();
   _keyboard_input.setSmallFont(f);
   f.setPointSize(f.pointSize()*13 / 10);
   _keyboard_input.setBigFont(f);

   adjustSize();
}

void cQtKeyboardAlpha::setBigFont(const QFont &font)
{
   _keyboard_input.setBigFont(font);
}

QFont cQtKeyboardAlpha::getBigFont() const
{
   return _keyboard_input.getBigFont();
}

void cQtKeyboardAlpha::setSmallFont(const QFont &font)
{
   _keyboard_input.setSmallFont(font);
}

QFont cQtKeyboardAlpha::getSmallFont() const
{
   return _keyboard_input.getSmallFont();
}

void cQtKeyboardAlpha::setSyntaxValidator(QValidator *v)
{
   _keyboard_input.setSyntaxValidator(v);
}

void cQtKeyboardAlpha::setFinalValidator(iFinalValidator *v)
{
   _keyboard_input.setFinalValidator(v);
}

void cQtKeyboardAlpha::setCurrentValue(const QString &cv)
{
   _keyboard_input.setInput(cv);
}

QString cQtKeyboardAlpha::getNewValue() const
{
   return _keyboard_input.getInput();
}

int cQtKeyboardAlpha::exec()
{
   slotClearValidationError();
   _keyboard_input.initialize();
   QString saved_input = _keyboard_input.getInput();
   if (QDialog::exec() == QDialog::Rejected) {
      _keyboard_input.setInput(saved_input);
      return QDialog::Rejected;
   }

   return QDialog::Accepted;
}

void cQtKeyboardAlpha::slotValidationFailed(const QString &error)
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_error.shown", true);
   qp.SetProperty("_error.text", error);
   adjustSize();
//   _new->selectAll();
}

void cQtKeyboardAlpha::slotClearValidationError()
{
   cQtPropertyWidget qp(this);
   qp.SetProperty("_error.shown", false);
   adjustSize();
}


