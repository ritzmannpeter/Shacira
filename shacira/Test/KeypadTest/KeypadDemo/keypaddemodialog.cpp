// ==========================================================================
// keypaddemodialog.cpp
// ==========================================================================

#include "keypaddemodialog.h"

#include "keypads/qt_keypadnumeric.h"
#include "keypads/qt_keyboardalpha.h"
#include "keypads/qt_keyboard.h"

#include "keypads/qt_number_validator.h"

#include "keyboardmodal.h"


#include <qlineedit.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qfontdialog.h>
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <qtextedit.h>
#include <qiconset.h>

#include <stdlib.h>



// --------------------------------------------------------------------------
// Syntax-Validatorn
// --------------------------------------------------------------------------

class cQtPeterValidator : public QValidator
{
public:
   cQtPeterValidator(const char *peter, QObject *parent, const char *name = 0) : 
      QValidator(parent, name), _peter(peter) {}
      virtual State validate ( QString & input, int & pos ) const {
         if (input == _peter) {
            return QValidator::Acceptable;
         } else if (input == _peter.left(input.length())) {
            return QValidator::Intermediate;
         } else {
            return QValidator::Invalid;
         }
      }
private:
   QString _peter;
};

cQtPeterValidator peter_validator("Peter",0);

cQtNumberValidator number_validator(-9999, 9999, 3, 0);

//cQtTimeValidator time_validator(0);


// --------------------------------------------------------------------------
// Benutzerdefinierter Final Validator
// --------------------------------------------------------------------------

class cApocalypseValidator : public iFinalValidator
{
public:
   virtual bool check(const QString &line, QString &error) const {
      if (QMessageBox::information(0, "FinalValidation", "Besteht die Finale Validierung?", QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes) {
         return true;
      } else {
         error = "Die Finale Validierung ist fehlgeschlagen weil jemand auf 'No' gedrueckt hat";
         return false;
      }
   }
};

cApocalypseValidator apocalypse_now;


// --------------------------------------------------------------------------
// Implementierung cQtKeypadDemoDialog
// --------------------------------------------------------------------------

cQtKeypadDemoDialog::cQtKeypadDemoDialog( QWidget* parent, const char* name, bool modal, WFlags f ) :
	cQtKeypadDemoDialogBase( parent, name, modal, f ),
   _keyboard_dialog(0),
   _is_num_validator(false)
{
   // Voreinstellungen vom Designer uebernehmen
   slotSetDialog(_combo_dialog->currentText());
   slotSetValidator(_combo_validator->currentText());
   slotSetFinalValidator(_combo_final_validator->currentText());
}



void cQtKeypadDemoDialog::slotSetDialog(const QString &dialog)
{
   delete _keyboard_dialog;
   _keyboard_dialog = 0;

   if (dialog == "cQtKeyboardAlpha") {
      cQtKeyboardAlpha *dlg = new cQtKeyboardAlpha(this);
      dlg->_keyboard->setLayout((cQtKeyboard::LAYOUT_TYPE)strtol(_combo_layout->currentText(),0,0));
      dlg->_keyboard_input.setWidget(dlg->_keyboard);
      _keyboard_dialog = dlg;
   } else if (dialog == "cQtKeypadNumeric") {
      _keyboard_dialog = new cQtKeypadNumeric(this);
   }
}

void cQtKeypadDemoDialog::slotSetLayout(const QString &layout)
{
   slotSetDialog(_combo_dialog->currentText());
}


void cQtKeypadDemoDialog::slotSetBigFont()
{
   if (_keyboard_dialog != 0 && _keyboard_dialog->inherits("cQtKeypadNumericBase")) {
      
      cQtKeypadNumeric *pad = (cQtKeypadNumeric*)_keyboard_dialog;
      bool ok;
      QFont font = QFontDialog::getFont(&ok, pad->getBigFont(), this);
      if (ok) {
         pad->setBigFont(font);
      }

   } else if (_keyboard_dialog != 0 && _keyboard_dialog->inherits("cQtKeyboardAlphaBase")) {
      
      cQtKeyboardAlpha *pad = (cQtKeyboardAlpha*)_keyboard_dialog;
      bool ok;
      QFont font = QFontDialog::getFont(&ok, pad->getBigFont(), this);
      if (ok) {
         pad->setBigFont(font);
      }
   }
}

void cQtKeypadDemoDialog::slotSetSmallFont()
{
   if (_keyboard_dialog != 0 && _keyboard_dialog->inherits("cQtKeypadNumericBase")) {
      
      cQtKeypadNumeric *pad = (cQtKeypadNumeric*)_keyboard_dialog;
      bool ok;
      QFont font = QFontDialog::getFont(&ok, pad->getSmallFont(), this);
      if (ok) {
         pad->setSmallFont(font);
      }

   } else if (_keyboard_dialog != 0 && _keyboard_dialog->inherits("cQtKeyboardAlphaBase")) {
      
      cQtKeyboardAlpha *pad = (cQtKeyboardAlpha*)_keyboard_dialog;
      bool ok;
      QFont font = QFontDialog::getFont(&ok, pad->getSmallFont(), this);
      if (ok) {
         pad->setSmallFont(font);
      }
   }
}



void cQtKeypadDemoDialog::slotSetValidator(const QString &validator)
{
   _is_num_validator = (validator == "cQtNumberValidator");
   if (_is_num_validator) {
      slotUpdateValidator();
   } else if (validator == "cQtTimeValidator") {
      _syntax_validator = 0;
   } else if (validator == "PeterValidator") {
      _syntax_validator = &peter_validator;
   } else {
      _syntax_validator = 0;
   }
}


void cQtKeypadDemoDialog::slotSetFinalValidator(const QString &validator)
{
   if (validator == "cApocalypseValidator") {
      _final_validator = &apocalypse_now;
   } else {
      _final_validator = 0;
   }
}


void cQtKeypadDemoDialog::slotUpdateValidator()
{
   if (_is_num_validator) {
      int min_val = _spin_min_2->value();
      int max_val = _spin_max_2->value();
      int prec = _spin_prec_2->value();
      number_validator.setBottom(min_val);
      number_validator.setTop(max_val);
      number_validator.setDecimals(prec);
      _syntax_validator = &number_validator;
   }
}


void cQtKeypadDemoDialog::slotGetInput()
{
   if (_keyboard_dialog != 0 && _keyboard_dialog->inherits("cQtKeypadNumericBase")) {
      
      cQtKeypadNumeric *pad = (cQtKeypadNumeric*)_keyboard_dialog;
      pad->setCaption(_caption_edit->text());
      //pad->setInfo(_info_edit->text());
      pad->setFinalValidator(_final_validator);
      pad->setSyntaxValidator(_syntax_validator);
      pad->setCurrentValue(_edit_input->text());
      if (pad->exec() == QDialog::Accepted) {
         _edit_input->setText(pad->getNewValue());
      }

   } else if (_keyboard_dialog != 0 && _keyboard_dialog->inherits("cQtKeyboardAlphaBase")) {
      
      cQtKeyboardAlpha *pad = (cQtKeyboardAlpha*)_keyboard_dialog;
      pad->setCaption(_caption_edit->text());
      pad->setMultiline(_combo_echo_widget->currentText() == "QTextEdit");
      pad->setFinalValidator(_final_validator);
      pad->setSyntaxValidator(_syntax_validator);
      pad->setCurrentValue(_edit_input->text());
      if (pad->exec() == QDialog::Accepted) {
         _edit_input->setText(pad->getNewValue());
      }
   }

}


void cQtKeypadDemoDialog::slotShowModal()
{
   cQtKeyboardModal *dlg = new cQtKeyboardModal(this, 0, false, Qt::WDestructiveClose);
   dlg->setText(_edit_input->text());
   dlg->show();
}



cQtKeyboardAlpha *_static_alpha = 0;

void cQtKeypadDemoDialog::slotShowStatic()
{
   cQtKeyboard::LAYOUT_TYPE must_language = (cQtKeyboard::LAYOUT_TYPE)strtol(_combo_layout->currentText(),0,0);
   cQtKeyboard::LAYOUT_TYPE is_language = _static_alpha ? _static_alpha->_keyboard->getLayout() : cQtKeyboard::layoutUndefined;

   if (_static_alpha == 0 || must_language != is_language) {
      delete _static_alpha;
      _static_alpha = new cQtKeyboardAlpha(this);
   }

   _static_alpha->_keyboard->setLayout(must_language);
   _static_alpha->_keyboard_input.setWidget(_static_alpha/*->_keyboard*/);

   _static_alpha->setCaption(_caption_edit->text());
   _static_alpha->setMultiline(_combo_echo_widget->currentText() == "QTextEdit");
   _static_alpha->setFinalValidator(_final_validator);
   _static_alpha->setSyntaxValidator(_syntax_validator);
   _static_alpha->setCurrentValue(_edit_input->text());
   if (_static_alpha->exec() == QDialog::Accepted) {
      _edit_input->setText(_static_alpha->getNewValue());
   }

}