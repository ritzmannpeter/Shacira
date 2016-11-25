// ==========================================================================
// qt_number_validator.h
//
// Deklaration cQtNumberValidator. Ein QValidator der den Berich und die
// Nachkommastellen einer als String vorliegenden Double-Zahl prueft.
// Arbeitet aehnlich wie (und unter Zuhilfenahme von) QDoubleValidator, die
// Bewertung ist aber strenger.
//
// cQtNumberValidator
//   |
//   +- QDoubleValidator
//        |
//        +- QValidator
//
// ==========================================================================

#ifndef _cqtnumbervalidator_h_
#define _cqtnumbervalidator_h_

#include <qvalidator.h>
#include "cQtKeyboardInput.h"

class cQtNumberValidator : public QDoubleValidator
{
public:
   // Konstruktoren (wie die von QDoubleValidator)
   cQtNumberValidator (QObject * parent, const char * name = 0);
   cQtNumberValidator (double bottom, double top, int decimals, QObject * parent, const char * name = 0);

   // Ueberschreibt QDoubleValidator::validate
   virtual QValidator::State validate(QString &input, int &pos) const;
};


#endif // QT_NUMBER_VALIDATOR_H
