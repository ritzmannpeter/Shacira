// ==========================================================================
// qt_string_validator.cpp
//
// Implementierung fuer cQtStringValidator
// ==========================================================================

#include <math.h>
#include <stdlib.h>

#include "cQtStringValidator.h"

cQtStringValidator::cQtStringValidator (QObject * parent, const char * name)
   : QValidator (parent, name)
{
   _Length = 0;
}

cQtStringValidator::cQtStringValidator (int length, QObject * parent, const char * name)
   : QValidator(parent, name )
{
   _Length = length;
}


QValidator::State cQtStringValidator::validate(QString &input, int &pos) const
{
   State state;
   /// PR 20.01.05 pos sometimes (every second call) contains uninitialized values
   /// MW 2005-01-24 hopefully fixed (one location found, pos = 0 added)
   int size = input.length();
   if (size > _Length) {
      state = QValidator::Invalid;
   } else {
      state = QValidator::Acceptable;
   }
   return state;
}

