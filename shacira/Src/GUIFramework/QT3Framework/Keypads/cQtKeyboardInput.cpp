
/// PR 10.03.05 - implemented identical behaviour of capslock and shift buton
/// PR 15.11.05 - removed my own caps lock patch
/// PR 08.06.06 - handle new line (enter) like input termination
///               in case of single line widgets

#include "cQtKeyboardInput.h"
#include "cQtKeyboardLayout.h"
#include "cQtKeyboardButton.h"
#include "safefunctions.h"
#include "qt4port.h"

#include <qdialog.h>
#include <qobjectlist.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qvalidator.h>

#include <stdlib.h>

// ---------------------------------------------------------------------------
// Implementierung cQtKeyboardInput
// ---------------------------------------------------------------------------

cQtKeyboardInput::cQtKeyboardInput(QWidget *parent) :
   _parent_widget(0),
   _keyboard_layout(0),
   _final_validator(0),
   _syntax_validator(0),
   _echo_widget(0)
{
   setWidget(parent);
   setEchoWidget(0);
   initialize();
   _multi_line = true;
}


cQtKeyboardInput::~cQtKeyboardInput()
{
   delete _echo_widget;
}


void cQtKeyboardInput::initialize()
{
   if (_keyboard_layout != 0) 
      _keyboard_layout->initialize();

   _shift_state = shiftNone;
   _shift_lock = false;
   _caps_lock = false;
   _shift_button = 0;
   _first_button = true;
   _error_emitted = false;
   _mark_text = false;

   if (_keyboard_layout != 0) {
      if (_keyboard_layout->getQuickOverwrite() == true) {
         _echo_widget->markAll();
      } else {
         _echo_widget->markNothing();
      }
   }
}



// Dialog (und damit eingebettetes Layout) festlegen
bool cQtKeyboardInput::setWidget(QWidget *parent)
{
   _parent_widget = parent;
   if (parent == 0) return false;

   QObjectList *layouts = _parent_widget->queryList("cQtKeyboardLayout");
   _keyboard_layout = (layouts->count() > 0) ? (cQtKeyboardLayout*)layouts->first() : 0;
   delete layouts;

   if (_keyboard_layout != 0) {
      connect( _keyboard_layout, SIGNAL( clicked(cQtKeyboardButton*) ),      
               this, SLOT( slotClicked(cQtKeyboardButton*) ) );
      connect( _keyboard_layout, SIGNAL( toggled(cQtKeyboardButton*,bool) ), 
               this, SLOT( slotToggled(cQtKeyboardButton*,bool) ) );
   }

   // Idee: automatisch mit einem einzelnen QLineEdit oder QTextEdit verbinden
   // QObjectList *lineedits = _dialog->queryList("QLineEdit");
   // QObjectList *textedits = _dialog->queryList("QTextEdit");
   // if (lineedits->count() == 1 && textedits->count() == 0) {
   //    setEchoWidget( (QLineEdit*)lineedits->first() );
   // } else if (lineedits->count() == 0 && textedits->count() == 1) {
   //    setEchoWidget( (QTextEdit*)textedits->first() );
   // }
   // delete lineedits;
   // delete textedits;

   return _keyboard_layout != 0;
}




// ---------------------------------------------------------------------------
// Validatoren


void cQtKeyboardInput::setSyntaxValidator(QValidator *v) 
{ 
   _syntax_validator = v;
   _echo_widget->setValidator(v);
}

// Falls definiert, den Syntax-Validator aufrufen
int cQtKeyboardInput::callSyntaxValidator(const QString &line) const
{
   if (_syntax_validator == 0) {
      return QValidator::Acceptable;
   } else {
      int pos = 0;
      QString temp = line;
      return _syntax_validator->validate(temp,pos);
   }
}

// Falls definiert, den Final-Validator aufrufen
bool cQtKeyboardInput::callFinalValidator(const QString &line, QString &error) const
{
   if (_final_validator == 0) {
      error = QString();
      return true;
   } else {
      return _final_validator->check(line, error);
   }
}


// ---------------------------------------------------------------------------
// Local helper: replace standard C escape sequences like "\n" by chars '\n'
// (Code taken from ecl::cString)

static char *replaceEscape(char *str)
{
   const char *esc = "ntvbrfa\\?'\"";
   const char *asc = "\n\t\v\b\r\f\a\\?'\"";

   char *from = str;
   char *to = str;

   while (*from) {
      if (*from != '\\') {
         *to++ = *from++;
      } else {
         const char *chr = strchr(esc, *++from);
         if (chr != 0) {
            *to++ = asc[chr-esc];
            from++;
         } else if (*from >= '0' && *from <= '7') {
            int val = *from++ - '0';
            if (*from >= '0' && *from <= '7') {
               val = (val<<3) + *from++ - '0';
               if (*from >= '0' && *from <= '7') {
                  val = (val<<3) + *from++ - '0';
               }
            }
            *to++ = (char)val;
         } else if (*from == 'x') {
            char *endp;
            long val = strtoul(++from, &endp, 16);
            if (from < endp) *to++ = (char)val;
            from = endp;
         } else {
            *to++ = *from++;
         }
      }
   }
   
   *to = *from;
   return str;
}



// ---------------------------------------------------------------------------
// Im Layout definierte Standard-Fonts

void cQtKeyboardInput::setBigFont(const QFont &font)
{
   if (_keyboard_layout != 0) {
      _keyboard_layout->setBigFont(font);
   }
}

QFont cQtKeyboardInput::getBigFont() const
{
   if (_keyboard_layout!= 0) {
      return _keyboard_layout->getBigFont();
   } else {
      return QFont();
   }
}

void cQtKeyboardInput::setSmallFont(const QFont &font)
{
   if (_keyboard_layout != 0) {
      _keyboard_layout->setSmallFont(font);
   }
}

QFont cQtKeyboardInput::getSmallFont() const
{
   if (_keyboard_layout != 0) {
      return _keyboard_layout->getSmallFont();
   } else {
      return QFont();
   }
}




// ---------------------------------------------------------------------------
// Eingabe verwursten

void cQtKeyboardInput::inputChanged(const QString &input)
{
   if (_keyboard_layout != 0) 
      _keyboard_layout->setInput(input);
}

// Eingabewert validieren und sichern (Bei Vorinitialisierung und
// waehrend der Eingabe), im Fehlerfall Signal ausloessen
bool cQtKeyboardInput::setInput(const QString &input)
{
   int result = callSyntaxValidator(input);
   if (result != QValidator::Invalid) {
      _echo_widget->setText(input);
      inputChanged(input);
      return true;
   } else {
      _echo_widget->setText("");
      inputChanged("");
   }
   return false;
}

// Eingabe Rueckgabewert
QString cQtKeyboardInput::getInput() const
{
   return _echo_widget->getText();
}



// ---------------------------------------------------------------------------
// Normale Click-Buttons bearbeiten

void cQtKeyboardInput::slotClicked(cQtKeyboardButton *button)
{
   bool changed = false;

   switch (button->getKeyType()) {
   case cQtKeyboardButton::typeNormal:
      {
         QString value;

         switch(_shift_state) {
         case shiftUpper:
            value = button->getKeyValueShift();
            break;
         case shiftAlt:
            value = button->getKeyValueAlt();
            break;
         case shiftNone:
         default:
            value = button->getKeyValue();
            break;
         }
         // Escape-Sequenzen in Strings mit "..." ersetzen
         if (value.length() > 2 && value.left(1) == "\"" && value.right(1) == "\"") {
            value = value.mid(1,value.length()-2);
            char buf[16] = {0};
            char *str = (value.length()<16) ? buf : new char[value.length()+1];
            size_t dest_size = (str != buf) ? value.length()+1 : sizeof(buf);
            SafeStrCpy(str, CONST_STRING(value), dest_size);
            value = replaceEscape(str);
            if (str != buf) 
               delete[] str;
         }
         // Caps-Lock
         if (_caps_lock == true) {
            value = value.upper();
         }

         if (_shift_button != 0) {
            _shift_button->setOn(false);
            _shift_button = 0;
         }
         _shift_state = _shift_lock ? shiftUpper : shiftNone;
         if (value.length() > 0) {
            if (_first_button == true && _keyboard_layout->getQuickOverwrite() == true) {
               _echo_widget->delAll();
               _echo_widget->insert(value);
            } else {
               _echo_widget->insert(value);
            }
            changed = true;
         }
      }
      break;

   case cQtKeyboardButton::typeAction:
      // Die Action-Buttons werden
      // a) im Moment nicht mehr benutzt
      // b) erlauben momentan keine Änderung der Eingabe mehr
      // c) können daher bei Bedarf jederzeit ein Redesign erfahren
      emit actionButtonClicked(button);
      return;
   
   case cQtKeyboardButton::typeOk:
      {
         QString line = _echo_widget->getText();
         // ACHTUNG: bei Ok wird nur der Finale Validator aufgerufen!!!
         if (true || callSyntaxValidator(line) == QValidator::Acceptable) {
            QString error;
            if (callFinalValidator(line, error) == false) {
               emit finalValidationFailed(error);
               _error_emitted = true;
            } else {
               _keyboard_layout->slotAcceptInput();
            }
         }
      }
      return;
   
   case cQtKeyboardButton::typeCancel:
      _keyboard_layout->slotRejectInput();
      return;
   
   case cQtKeyboardButton::typeBackspace:
      _echo_widget->delLeft();
      changed = true;
      break;

   case cQtKeyboardButton::typeDelete:
      _echo_widget->delRight();
      changed = true;
      break;

   case cQtKeyboardButton::typeClear:
      _echo_widget->delAll();
      changed = true;
      break;

   // Cursorbewegung ggf. mit markieren
   case cQtKeyboardButton::typeLeft:
   case cQtKeyboardButton::typeRight:
   case cQtKeyboardButton::typeUp:
   case cQtKeyboardButton::typeDown:
   case cQtKeyboardButton::typeLineStart:
   case cQtKeyboardButton::typeLineEnd:
   case cQtKeyboardButton::typePgUp:
   case cQtKeyboardButton::typePgDown:
      {
         if ( (_shift_state == shiftUpper || _shift_lock == true || _caps_lock == true) 
              && _mark_text == false ) {
            _echo_widget->markStart();
            _mark_text = true;
         }
         switch(button->getKeyType()) {
         case cQtKeyboardButton::typeLeft:
            _echo_widget->moveLeft();
            break;

         case cQtKeyboardButton::typeRight:
            _echo_widget->moveRight();
            break;

         case cQtKeyboardButton::typeUp:
            _echo_widget->moveUp();
            break;

         case cQtKeyboardButton::typeDown:
            _echo_widget->moveDown();
            break;

         case cQtKeyboardButton::typeLineStart:
            _echo_widget->moveLineStart();
            break;

         case cQtKeyboardButton::typeLineEnd:
            _echo_widget->moveLineEnd();
            break;
         case cQtKeyboardButton::typePgUp:
            _echo_widget->movePgUp();
            break;

         case cQtKeyboardButton::typePgDown:
            _echo_widget->movePgDown();
            break;

         }
         if (_mark_text == true) {
            _echo_widget->markEnd();
         }
      }
      break;

   // Sonderfunktion: Vorzeichenwechsel
   case cQtKeyboardButton::typeSign:
      _echo_widget->changeSign();
      changed = true;
      break;

   // Sonderfunktion: Zeilenwechsel
   case cQtKeyboardButton::typeNewLine:
      if (_multi_line) {
         _echo_widget->insert("\n");
         changed = true;
      } else {
         {
            QString line = _echo_widget->getText();
            // ACHTUNG: bei Ok wird nur der Finale Validator aufgerufen!!!
            if (true || callSyntaxValidator(line) == QValidator::Acceptable) {
               QString error;
               if (callFinalValidator(line, error) == false) {
                  emit finalValidationFailed(error);
                  _error_emitted = true;
               } else {
                  _keyboard_layout->slotAcceptInput();
               }
            }
         }
         return;
      }
      break;

   default:
      return;
   }

   if (callSyntaxValidator(_echo_widget->getText()) == QValidator::Invalid) {
      _echo_widget->undo();
      inputChanged(_echo_widget->getText());
   } else {
      if (_error_emitted == true) {
         emit clearValidationError();
         _error_emitted = false;
      }
      if (changed) {
         inputChanged(_echo_widget->getText());
      }
   }
   _first_button = false;
}


// ---------------------------------------------------------------------------
// Umschalttasten bzw. Toggle-Buttons bearbeiten
void cQtKeyboardInput::slotToggled(cQtKeyboardButton *button, bool on)
{
   switch (button->getKeyType()) {
   case cQtKeyboardButton::typeShiftLock:
      _shift_lock = on;
      if (on) {
         _shift_state = shiftUpper;
      } else {
         _shift_state = shiftNone;
         if (_shift_button != 0) {
            _shift_button->setOn(false);
            _shift_button = 0;
         }
      }
      break;

   case cQtKeyboardButton::typeCapsLock:
      _caps_lock = on;
      break;

   case cQtKeyboardButton::typeShift:
      if (on) {
         if (_shift_button != 0) {
            _shift_button->setOn(false);
         }
         _shift_button = button;
         _shift_state = shiftUpper;
      } else {
         _shift_button = 0;
         _shift_state = _shift_lock ? shiftUpper : shiftNone;
         _mark_text = false;
      }
      break;

   case cQtKeyboardButton::typeAlt:
      if (on) {
         if (_shift_button != 0) {
            _shift_button->setOn(false);
         }
         _shift_state = shiftAlt;
         _shift_button = button;
      } else {
         _shift_button = 0;
         _shift_state = _shift_lock ? shiftUpper : shiftNone;
      }
      break;

   case cQtKeyboardButton::typeAction:
      emit actionButtonToggled(button, on);
      break;

   default:
      break;
   }
   
   if (_error_emitted == true) {
      emit clearValidationError();
      _error_emitted = false;
   }
}


// Dialog ausfuehren
int cQtKeyboardInput::exec()
{
   if (_parent_widget == 0 || _keyboard_layout == 0 || 
       _parent_widget->inherits("QDialog") == false) {
      return execError;
   }

   _first_button = true;
   _error_emitted = false;

   QString saved_input = _echo_widget->getText();
   if (((QDialog*)_parent_widget)->exec() == QDialog::Rejected) {
      _echo_widget->setText(saved_input);
      inputChanged(saved_input);
      return execRejected;
   }

   return execAccepted;
}


// Echo-Widget setzen (mit dem jeweilis passenden Interface)
void cQtKeyboardInput::setEchoWidget(QWidget *widget)
{
   delete _echo_widget;
   
   if (widget == 0) {
      _echo_widget = new cEchoNoWidget();
      _multi_line = true;
   } else if (widget->inherits("QLineEdit") == true) {
      _echo_widget = new cEchoLineEdit((QLineEdit*)widget);
      _multi_line = false;
   } else if (widget->inherits("QTextEdit") == true) {
      _echo_widget = new cEchoTextEdit((QTextEdit*)widget);
      _multi_line = true;
   } else {
      // Widget nicht unterstützt
      _echo_widget = new cEchoNoWidget();
      _multi_line = true;
   }
}




// ---------------------------------------------------------------------------
// Implementierung cQtKeyboardInput::cEchoNoWidget
// ---------------------------------------------------------------------------

void cQtKeyboardInput::cEchoNoWidget::setText(const QString &text)
{
   _undo_line = _line;
   _line = text;
}

QString cQtKeyboardInput::cEchoNoWidget::getText() const
{
   return _line;
}

void cQtKeyboardInput::cEchoNoWidget::insert(const QString &key)
{
   _undo_line = _line;
   _line += key;
}

void cQtKeyboardInput::cEchoNoWidget::changeSign()
{
   _undo_line = _line;
   if (_line.left(1) == "-") {
      _line = _line.mid(1);
   } else {
      _line = "-" + _line;
   }
}

void cQtKeyboardInput::cEchoNoWidget::delLeft()
{
   _undo_line = _line;
   if (_line.length() > 0) {
      _line = _line.left(_line.length()-1);
   }
}

void cQtKeyboardInput::cEchoNoWidget::delAll()
{
   _undo_line = _line;
   _line = "";
}

void cQtKeyboardInput::cEchoNoWidget::undo()
{
   _line = _undo_line;
}




// ---------------------------------------------------------------------------
// Implementierung cQtKeyboardInput::cEchoLineEdit
// ---------------------------------------------------------------------------

void cQtKeyboardInput::cEchoLineEdit::setText(const QString &text)
{
   _widget->setText(text);
   _widget->setFocus();
}

QString cQtKeyboardInput::cEchoLineEdit::getText() const
{
   return _widget->text();
}

void cQtKeyboardInput::cEchoLineEdit::insert(const QString &key)
{
   //int pos = _widget->cursorPosition();
   //_widget->setText(_widget->text());
   //_widget->setCursorPosition(pos);
   _widget->insert(key);
   _mark = false;
}

void cQtKeyboardInput::cEchoLineEdit::setValidator(QValidator *v)
{
   _widget->setValidator(v);
}

void cQtKeyboardInput::cEchoLineEdit::changeSign()
{
   int pos = _widget->cursorPosition();
   _widget->setText(_widget->text());
   _widget->setCursorPosition(0);
   if (_widget->text().left(1) == "-") {
      _widget->del();
      _widget->setCursorPosition(pos-1);
   } else {
      _widget->insert("-");
      _widget->setCursorPosition(pos+1);
   }
}

void cQtKeyboardInput::cEchoLineEdit::delLeft()
{
   _widget->backspace();
   _mark = false;
}

void cQtKeyboardInput::cEchoLineEdit::delRight()
{
   _widget->del();
   _mark = false;
}

void cQtKeyboardInput::cEchoLineEdit::delAll()
{
   _widget->setText("");
   _mark = false;
}

void cQtKeyboardInput::cEchoLineEdit::moveLeft()
{
   _widget->cursorBackward(_mark);
}

void cQtKeyboardInput::cEchoLineEdit::moveRight()
{
   _widget->cursorForward(_mark);
}

void cQtKeyboardInput::cEchoLineEdit::undo()
{
   _widget->undo();
   _mark = false;
}

void cQtKeyboardInput::cEchoLineEdit::markStart()
{
   _mark = true;
}

void cQtKeyboardInput::cEchoLineEdit::markEnd()
{
}

void cQtKeyboardInput::cEchoLineEdit::markAll()
{
   _widget->selectAll();
}

void cQtKeyboardInput::cEchoLineEdit::markNothing()
{
   _widget->deselect();
}



// ---------------------------------------------------------------------------
// Implementierung cQtKeyboardInput::cEchoTextEdit
// ---------------------------------------------------------------------------

void cQtKeyboardInput::cEchoTextEdit::setText(const QString &text)
{
   _widget->setText(text);
   _widget->setFocus();
}

QString cQtKeyboardInput::cEchoTextEdit::getText() const
{
   return _widget->text();
}

void cQtKeyboardInput::cEchoTextEdit::insert(const QString &key)
{
   _widget->insert(key);
}

void cQtKeyboardInput::cEchoTextEdit::delLeft()
{
   if (_widget->hasSelectedText()) {
      _widget->del();
   } else {
      _widget->doKeyboardAction(QTextEdit::ActionBackspace);
   }
}

void cQtKeyboardInput::cEchoTextEdit::delRight()
{
   _widget->del();
}

void cQtKeyboardInput::cEchoTextEdit::delAll()
{
   _widget->clear();
}

void cQtKeyboardInput::cEchoTextEdit::moveLeft()
{
   _widget->moveCursor(QTextEdit::MoveBackward, false);
}

void cQtKeyboardInput::cEchoTextEdit::moveRight()
{
   _widget->moveCursor(QTextEdit::MoveForward, false);
}

void cQtKeyboardInput::cEchoTextEdit::moveUp()
{
   _widget->moveCursor(QTextEdit::MoveUp, false);
}

void cQtKeyboardInput::cEchoTextEdit::moveDown()
{
   _widget->moveCursor(QTextEdit::MoveDown, false);
}

void cQtKeyboardInput::cEchoTextEdit::moveLineStart()
{
   _widget->moveCursor(QTextEdit::MoveLineStart, false);
}

void cQtKeyboardInput::cEchoTextEdit::moveLineEnd()
{
   _widget->moveCursor(QTextEdit::MoveLineEnd, false);
}

void cQtKeyboardInput::cEchoTextEdit::movePgUp()
{
   _widget->moveCursor(QTextEdit::MovePgUp, false);
}

void cQtKeyboardInput::cEchoTextEdit::movePgDown()
{
   _widget->moveCursor(QTextEdit::MovePgDown, false);
}

void cQtKeyboardInput::cEchoTextEdit::undo()
{
   _widget->undo();
}


void cQtKeyboardInput::cEchoTextEdit::markStart()
{
   _widget->getCursorPosition(&_paraFrom, &_indexFrom);
}

void cQtKeyboardInput::cEchoTextEdit::markEnd()
{
   int paraTo,indexTo;
   _widget->getCursorPosition(&paraTo, &indexTo);
   _widget->setSelection(_paraFrom, _indexFrom, paraTo, indexTo);
}

void cQtKeyboardInput::cEchoTextEdit::markAll()
{
}

void cQtKeyboardInput::cEchoTextEdit::markNothing()
{
}

