// ==========================================================================
// qt_number_validator.cpp
//
// Implementierung fuer cQtNumberValidator
// ==========================================================================

#include <math.h>
#include <stdlib.h>
#include "cQTNumberValidator.h"
#include "qt4port.h"

cQtNumberValidator::cQtNumberValidator (QObject * parent, const char * name)
#ifdef QT4
   : QDoubleValidator(parent)
#else
   : QDoubleValidator(parent, name)
#endif
{
#ifdef QT4
   setObjectName(name);
#endif
}

cQtNumberValidator::cQtNumberValidator (double bottom, double top, int decimals, QObject * parent, const char * name)
#ifdef QT4
   : QDoubleValidator(bottom, top, decimals, parent)
#else
   : QDoubleValidator(bottom, top, decimals, parent, name)
#endif
{
#ifdef QT4
   setObjectName(name);
#endif
}


QValidator::State cQtNumberValidator::validate(QString &input, int &pos) const
{
   State state = QDoubleValidator::validate(input, pos);
   
   if (state == QValidator::Intermediate) {
      double d = fabs(strtod(CONST_STRING(input),0));
#ifdef QT4
      int dot = input.indexOf('.');
#else
      int dot = input.find('.');
#endif
      if (d > fabs(bottom()) && d > fabs(top())) {
         state = QValidator::Invalid;
      } else if (bottom() >= 0 && input.left(1) == "-") {
         state = QValidator::Invalid;
      } else if (decimals() <= 0 && dot != -1) {
         state = QValidator::Invalid;
      } else if (dot >= 0 && input.mid(dot+1).length() > (uint)decimals()) {
         state = QValidator::Invalid;
      }
   }

   return state;
}

