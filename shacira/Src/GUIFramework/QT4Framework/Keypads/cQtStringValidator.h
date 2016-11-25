// ==========================================================================
// qt_string_validator.h
//
// Deklaration cQtStringValidator. Ein QValidator der den Berich und die
// Nachkommastellen einer als String vorliegenden Double-Zahl prueft.
// Arbeitet aehnlich wie (und unter Zuhilfenahme von) QDoubleValidator, die
// Bewertung ist aber strenger.
//
//   cQtStringValidator
//      |
//      +- QValidator
//
// ==========================================================================

#ifndef _cqtstringvalidator_h_
#define _cqtstringvalidator_h_

#include <qvalidator.h>
#include "cQtKeyboardInput.h"

class cQtStringValidator : public QValidator
{
public:
   // Konstruktoren (wie die von QDoubleValidator)
   cQtStringValidator (QObject * parent, const char * name = 0);
   cQtStringValidator (int length, QObject * parent, const char * name = 0);

   // Ueberschreibt QValidator::validate
   virtual QValidator::State validate(QString &input, int &pos) const;
protected:
   int _Length;
};


#endif // QT_STRING_VALIDATOR_H
