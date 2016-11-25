// ==========================================================================
// qt_path_validator.h
//
//   cQtPathValidator
//      |
//      +- cQTStringValidator
//
// ==========================================================================

#ifndef QT_PATH_VALIDATOR_H
#define QT_PATH_VALIDATOR_H


#include "cQtStringValidator.h"
#include "cQtKeyboardInput.h"


class cQtPathValidator : public cQtStringValidator
{
public:
   // Konstruktoren (wie die von QDoubleValidator)
   cQtPathValidator (QObject * parent, const char * name = 0);
   cQtPathValidator (int length, QObject * parent, const char * name = 0);

   // Ueberschreibt QValidator::validate
   virtual QValidator::State validate(QString &input, int &pos) const;
private:
   inline bool IsValidPathCharacter(const QChar c) const
   {
      if (c == '\\' ||
          c == '/' ||
          c == ':' ||
          c == ',' ||
          c == ';') {
         return false;
      }
      return true;
   };
   inline bool IsDriveLetter(const QChar c) const
   {
      if (c == 'a' ||
          c == 'b' ||
          c == 'c' ||
          c == 'd' ||
          c == 'e' ||
          c == 'f' ||
          c == 'g' ||
          c == 'h' ||
          c == 'i' ||
          c == 'j' ||
          c == 'k' ||
          c == 'l' ||
          c == 'm' ||
          c == 'n' ||
          c == 'o' ||
          c == 'p' ||
          c == 'q' ||
          c == 'r' ||
          c == 's' ||
          c == 't' ||
          c == 'u' ||
          c == 'v' ||
          c == 'w' ||
          c == 'x' ||
          c == 'y' ||
          c == 'z' ||
          c == 'A' ||
          c == 'B' ||
          c == 'C' ||
          c == 'D' ||
          c == 'E' ||
          c == 'F' ||
          c == 'G' ||
          c == 'H' ||
          c == 'I' ||
          c == 'J' ||
          c == 'K' ||
          c == 'L' ||
          c == 'N' ||
          c == 'N' ||
          c == 'O' ||
          c == 'P' ||
          c == 'Q' ||
          c == 'R' ||
          c == 'S' ||
          c == 'T' ||
          c == 'U' ||
          c == 'V' ||
          c == 'W' ||
          c == 'X' ||
          c == 'Y' ||
          c == 'Z') {
         return true;
      }
      return false;
   };
   inline bool IsUNCPath(const QString & input) const
   {
      if (input.at(0) != '\\' ||
          input.at(1) != '\\') {
         return false;
      } else {
         return true;
      }
   };
};

#endif // QT_PATH_VALIDATOR_H
