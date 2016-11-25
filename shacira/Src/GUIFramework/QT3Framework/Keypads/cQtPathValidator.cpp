// ==========================================================================
// cQtPathValidator.cpp
//
// Implementation of cQtPathValidator
// ==========================================================================

#include <math.h>
#include <stdlib.h>

#include "cQtPathValidator.h"


cQtPathValidator::cQtPathValidator (QObject * parent, const char * name) :
   cQtStringValidator(parent, name)
{
   _Length = 0;
}

cQtPathValidator::cQtPathValidator (int length, QObject * parent, const char * name) :
   cQtStringValidator(length, parent, name)
{
}


QValidator::State cQtPathValidator::validate(QString &input, int &pos) const
{
   if (input.isEmpty()) return QValidator::Acceptable;

   State state = cQtStringValidator::validate(input, pos);
   if (state == QValidator::Invalid) {
      return state;
   }

   uint input_length = input.length();
   bool is_drive_path = false;
   bool is_unc_path = false;
   bool first_slash = true;
   const QChar inputChar0 = input.at(0);

   if (input_length > 1) {
      is_unc_path = IsUNCPath(input);
      const QChar inputChar1 = input.at(1);
      if (inputChar1 == ':') {
         if (IsDriveLetter(inputChar0)) {
            is_drive_path = true;
         } else {
            return QValidator::Invalid;
         }
      }
      if (inputChar0 == '\\') {
         if (inputChar1 == '\\' ||
             IsValidPathCharacter(inputChar1) ) {
         } else {
            return QValidator::Invalid;
         }
      }
      if (inputChar0 == '/') {
         if (IsValidPathCharacter(inputChar1) ) {
         } else {
            return QValidator::Invalid;
         }
      }
   } else {
      if (inputChar0 == '\\' ||
          inputChar0 == '/' ||
          IsValidPathCharacter(inputChar0)) {
         return QValidator::Acceptable;
      } else {
         return QValidator::Invalid;
      }
   }

   if (!(is_drive_path || is_unc_path)) {
      if (!IsValidPathCharacter(inputChar0) ||
          !IsValidPathCharacter(input.at(1))) {
         return QValidator::Invalid;
      }
   }

   uint i = 0;
   for (i=2; i<input_length; i++) {
      const QChar c = input.at(i);
      if (c == '/' ||
          c == '\\') {
         if (c == '/' &&
             is_unc_path &&
             first_slash) {
            return QValidator::Invalid;
         } else {
            if (c == '\\') {
               first_slash = false;
            }
            if (i == 2 &&
                input.at(1) == ':') {
            } else if (!IsValidPathCharacter(input.at(i-1))) {
               return QValidator::Invalid;
            }
         }
      } else if (!IsValidPathCharacter(c)) {
         return QValidator::Invalid;
      }
   }
   return QValidator::Acceptable;

#ifdef lassma
   uint position = input.length()-1;
   if (pos == 0 && position != 0) {
      return QValidator::Intermediate;
   } else {
      position = pos;
   }
   QChar c  = input.at(position);
   if (c == '\\') {
      if (position == 0) {
      } else if (position == 1) {
         if (input.at(0) == '\\' ||
             IsValidPathCharacter(input.at(0))) {
            // UNC path or relative path
         } else {
            state = QValidator::Invalid;
         }
      } else if (position == 2) {
         if (input.at(1) == ':' ||
             IsValidPathCharacter(input.at(1))) {
            // drive notation or relative path
         } else {
            state = QValidator::Invalid;
         }
      } else {
         if (IsValidPathCharacter(input.at(position-1))) {
         } else {
            state = QValidator::Invalid;
         }
      }
   } else if (c == '/') {
      if (position == 0) {
      } else {
         if (IsValidPathCharacter(input.at(position-1))) {
         } else {
            if (position == 2 &&
                input.at(1) == ':') {
               // drive notation
            } else {
               state = QValidator::Invalid;
            }
         }
      }
   } else if (IsValidPathCharacter(c)) {
      if (position == 0) {
         if (IsDriveLetter(c)) {
            // drive letter
         } else {
            state = QValidator::Invalid;
         }
      } else if (position == 1) {
         if (input.at(0) == '\\' ||
             input.at(0) == '/' ||
             IsValidPathCharacter(input.at(0))) {
         } else {
            state = QValidator::Invalid;
         }
      } else {
      }
   } else if (c == ':') {
      if (position == 1) {
      } else {
         state = QValidator::Invalid;
      }
   } else {
      state = QValidator::Invalid;
   }
   return state;
#endif
}

