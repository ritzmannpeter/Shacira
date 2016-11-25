
#ifndef QT4

#pragma message(__LOC__ "this file should never be inluded qt 3")

#else

#ifndef _keyboardalpha_h_
#define _keyboardalpha_h_

#include "qt4port.h"
#include "ui_KeyboardAlpha.h"

class cQtKeyboardAlphaBase : public QDialog
{
   Q_OBJECT
public:
   cQtKeyboardAlphaBase(QWidget* parent = 0, const char* name = 0, bool modal = false, WIDGET_FLAGS_TYPE fl = 0);
   ~cQtKeyboardAlphaBase();
   QTextEdit* _text_edit;
   QLineEdit* _line_edit;
   cQtKeyboard* _keyboard;
protected:
   QVBoxLayout * cQtKeyboardAlphaBaseLayout;
   Ui::cQtKeyboardAlphaBase _ui;
};

#endif // _keyboardalpha_h_

#endif // QT4
