
#ifndef __cexpparser_h__
#define __cexpparser_h__

#include "global_defs.h"
#include "cparser.h"
#include "cexpression.h"

class cExpParser : public cParser
{
public:
   cExpParser(cStreamTokenizer * tokenizer) :
      cParser(tokenizer)
   {
   };
   virtual ~cExpParser()
   {
   };
   virtual cExpression * Parse();
private:
   cExpression * Exp(int level);
   cExpression * Exp1(int level);
   cExpression * Predicate();
   int ParamList(cPredicate * pred);
   Operators Operator();
   static Operators OpValue(int token);
   static const char * OpText(int token);
   static SymbolTypes SymbolType(int token);
};

#endif

