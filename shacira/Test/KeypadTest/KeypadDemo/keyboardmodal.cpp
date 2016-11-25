

#include "keyboardmodal.h"
#include "keypads/qt_keyboard.h"

#include <qtextedit.h>
#include <qlineedit.h>


cQtKeyboardModal::cQtKeyboardModal(QWidget* parent, const char* name, bool modal, WFlags fl) :
   cQtKeyboardModalBase(parent, name, modal, fl ),
   _keyboard_input(this)
{
   _keyboard_input.setEchoWidget(_text);

   connect( _keyboard, SIGNAL( acceptInput() ), 
            this, SLOT( slotAcceptInput() ) );
   connect( _keyboard, SIGNAL( rejectInput() ), 
            this, SLOT( slotRejectInput() ) );
}

void cQtKeyboardModal::setText(const QString &text)
{
   _keyboard_input.setInput(text); 
   _text_saved = text;
   showStatus("Text in Eingabemodul und Backupvariable initialisiert");
}


void cQtKeyboardModal::slotAcceptInput()
{
   _text_saved = _keyboard_input.getInput();

   showStatus("OK: Text in Backupvariable übernommen, andere Aktionen nach Gusto");
}

void cQtKeyboardModal::slotRejectInput()
{
   _keyboard_input.setInput(_text_saved);

   showStatus("CANCEL: Änderungen wurden rückgängig gemacht, andere Aktionen nach Gusto");
}


void cQtKeyboardModal::showStatus(const QString &line)
{
   _line->setText(line);
}
