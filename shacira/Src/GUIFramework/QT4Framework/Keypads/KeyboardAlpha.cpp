
#ifndef QT4

#pragma message(__LOC__ "this file should never build under qt 3")

#else

#include "KeyboardAlpha.h"

cQtKeyboardAlphaBase::cQtKeyboardAlphaBase( QWidget* parent, const char* name, bool modal, WIDGET_FLAGS_TYPE fl )
   : QDialog(parent, fl)
{
   setModal(modal);
   _ui.setupUi(this);
}

cQtKeyboardAlphaBase::~cQtKeyboardAlphaBase()
{
}

#endif

