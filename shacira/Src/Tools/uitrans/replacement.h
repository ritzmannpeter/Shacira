
#ifndef _replacement_h_
#define _replacement_h_

#include <qstring.h>
#include <qstringlist.h>

#define WORD_ONLY          0x00000001
#define SKIP_NAMESPACE     0x00000002

class Replacement
{
public:
   enum ReplacementType {ExpressionReplacement, TextReplacement, LineReplacement};
public:
   Replacement(unsigned int categories, unsigned int flags, const QString & expression, const QString & replacement);
   Replacement(unsigned int categories, unsigned int flags, const QString & text, const QString & replacement, Qt::CaseSensitivity sensitivity);
   Replacement(unsigned int categories, unsigned int flags, const QString & text, Qt::CaseSensitivity sensitivity);
   inline QString replace(const QString & text, bool & changed) const
   {
      if (_type == ExpressionReplacement) {
         QString newText = replaceExpression(text, _parseList, _replacement);
         if (newText != text) {
            changed = true;
         }
         return newText;
      } else if (_type == TextReplacement) {
         QString newText = replaceAll(text, _text, _replacement, _sensitivity);
         if (newText != text) {
            changed = true;
         }
         return newText;
      } else if (_type == LineReplacement) {
         QString newText = removeLine(text, _text, _sensitivity);
         if (newText != text) {
            changed = true;
         }
         return newText;
      }
      return text;
   };
   inline ReplacementType type() const {return _type;};
   inline bool applicable(unsigned int categories)
   {
      if (_categories & categories) {
         return true;
      } else {
         return false;
      }
   };
private:
   inline QString replaceAll(const QString & text, const QString & s1, const QString & s2, Qt::CaseSensitivity sensitivity) const
   {
      int textLength = text.length();
      QString newValue = text;
      int pos = newValue.indexOf(s1, 0, sensitivity);
      while (pos >= 0) {
         if (_flags & WORD_ONLY) {
            char c1 = 0;
            char c2 = 0;
            if (pos > 0) {
               c1 = newValue[pos - 1].toLatin1();
            }
            if ((pos + s1.length()) < textLength) {
               c2 = newValue[pos + s1.length()].toLatin1();
            }
            if (!isalnum(c1)) {
               if (_flags & SKIP_NAMESPACE) {
                  if (c1 != ':') {
                     if (!isalnum(c2) &&
                         c2 != '_' &&
                         c2 != '.') {
                        newValue.replace(pos, s1.length(), s2);
                     }
                  }
               } else {
                  if (!isalnum(c2) &&
                      c2 != '_' &&
                      c2 != '.') {
                     newValue.replace(pos, s1.length(), s2);
                  }
               }
            }
         } else {
            newValue.replace(pos, s1.length(), s2);
         }
         pos = newValue.indexOf(s1, pos + s2.length(), sensitivity);
      }
      return newValue;
   };
   inline QString removeLine(const QString & line, const QString & word, Qt::CaseSensitivity sensitivity) const
   {
      int pos = line.indexOf(word, 0, sensitivity);
      if (pos >= 0) {
         return QString();
      } else {
         return line;
      }
   };
   inline char antagonist(char c) const
   {
      if (c == '(') {
         return ')';
      } else if (c == '[') {
         return ']';
      } else if (c == '{') {
         return '}';
      } else if (c == '<') {
         return '>';
      } else {
         return 0;
      }
   };
   inline bool parseExpression(const QString & text, const QStringList & parseList, QStringList & resultList, int & start, int & length) const
   {
      int textPos = 0;
      int expPos = -1;
      int expLength = 0;
      int textLength = text.length();
      QStringList::const_iterator i = parseList.begin();
      while (i != parseList.end()) {
         QString parseText = (*i);
         if (parseText[0] == '%') {
            char c1 = (*(i+1))[0].toLatin1();
            int paramStart = textPos;
            int depth = 0;
            int i = 0;
            for (i=paramStart; i<textLength; i++) {
               char c = text[i].toLatin1();
               if (c == c1 && depth == 0) {
                  QString param = text.mid(paramStart, i - paramStart);
                  resultList << param;
                  textPos += (i - paramStart);
                  break;
               } else if (c == ')' ||
                          c == ']' ||
                          c == '}' ||
                          c == '>') {
                  depth--;
               } else if (c == '(' ||
                          c == '[' ||
                          c == '{' ||
                          c == '<') {
                  depth++;
               }
            }
         } else {
//            int pos = text.indexOf(parseText, textPos);
            int pos = parse(text, parseText, textPos);
            if (pos == -1) {
               return false;
            } else {
               if (expPos == -1) {
                  expPos = pos;
               }
               textPos = pos + parseText.length();
            }
         }
         i++;
      }
      start = expPos;
      length = textPos - expPos;
      return true;
   };
   inline QString replaceExpression(const QString & text, const QStringList & parseList, const QString & substitution) const
   {
      QString newText = text;
      QStringList resultList;
      int start = 0;
      int length = 0;
      bool success = parseExpression(newText, parseList, resultList, start, length);
      if (success) {
         QString substText = substitution;
         int paramPos = 0;
         QStringList::const_iterator i = resultList.begin();
         while (i != resultList.end()) {
            substText = substText.replace("%" + QString::number(paramPos), (*i));
            i++;
            paramPos++;
         }
         return newText.replace(start, length, substText);
      } else {
         return text;
      }
   };
   void addDelimiter(const QString & expression, const QString & delimiter, QMap<int,int> & positionMap) const;
   QStringList parseListFromExpression(const QString & expression) const;
   inline int parse(const QString & text,const QString & parseText, int startPos) const
   {
      int pos = text.indexOf(parseText, startPos);
      if (pos == -1) {
         return pos;
      }
      if (parseText.length() == 1) {
         char c = parseText[0].toLatin1();
         if (!isalnum(c)) {
            return text.indexOf(parseText, startPos);
         }
      }
      char c0 = 0;
      char c1 = 0;
      if (pos > 0) {
         c0 = text[pos-1].toLatin1();
      }
      if (pos+parseText.length() < text.length()) {
         c1 = text[pos+parseText.length()].toLatin1();
      }
      if (isalnum(c0) || isalnum(c1)) {
         if (pos < text.length()) {
            return parse(text, parseText, pos+1);
         } else {
            return -1;
         }
      } else {
         return pos;
      }
   };
private:
   ReplacementType _type;
   QString _text;
   QString _expression;
   QStringList _parseList;
   QString _replacement;
   Qt::CaseSensitivity _sensitivity;
   unsigned int _categories;
   unsigned int _flags;
};

#endif

