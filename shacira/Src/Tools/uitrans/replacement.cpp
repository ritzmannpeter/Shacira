
#include "replacement.h"
#include <qmap.h>

Replacement::Replacement(unsigned int categories, unsigned int flags, const QString & expression, const QString & replacement)
   : _categories(categories),
     _flags(flags),
     _expression(expression),
     _replacement(replacement),
     _sensitivity(Qt::CaseSensitive),
     _type(ExpressionReplacement)
{
   _parseList = parseListFromExpression(expression);
}

Replacement::Replacement(unsigned int categories, unsigned int flags, const QString & text, const QString & replacement, Qt::CaseSensitivity sensitivity)
   : _categories(categories),
     _flags(flags),
     _text(text),
     _replacement(replacement),
     _sensitivity(sensitivity),
     _type(TextReplacement)
{
}

Replacement::Replacement(unsigned int categories, unsigned int flags, const QString & text, Qt::CaseSensitivity sensitivity)
   : _categories(categories),
     _flags(flags),
     _text(text),
     _sensitivity(sensitivity),
     _type(LineReplacement)
{
}

void Replacement::addDelimiter(const QString & expression, const QString & delimiter, QMap<int,int> & positionMap) const
{
   int delimiterLength = delimiter.length();
   int pos = 0;
   pos = expression.indexOf(delimiter, pos);
   while (pos != -1) {
      positionMap[pos] = pos;
      positionMap[pos + delimiterLength] = pos + delimiterLength;
      pos = expression.indexOf(delimiter, pos + delimiterLength);
   }
}

QStringList Replacement::parseListFromExpression(const QString & expression) const
{
   QStringList list;
   QMap<int,int> positionMap;
   addDelimiter(expression, "(", positionMap);
   addDelimiter(expression, ")", positionMap);
   addDelimiter(expression, "[", positionMap);
   addDelimiter(expression, "]", positionMap);
   addDelimiter(expression, "{", positionMap);
   addDelimiter(expression, "}", positionMap);
   addDelimiter(expression, "<", positionMap);
   addDelimiter(expression, ">", positionMap);
   addDelimiter(expression, ",", positionMap);
   int start = 0;
   int end = 0;
   QMap<int,int>::const_iterator i = positionMap.begin();;
   while (i != positionMap.end()) {
      int end = *(i);
      int length = end - start;
      QString component = expression.mid(start, length);
      list << component;
      start = end;
      i++;
   }
   return list;
}

