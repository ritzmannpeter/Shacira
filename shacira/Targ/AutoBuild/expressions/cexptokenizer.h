
#ifndef __cexptokenizer_h__
#define __cexptokenizer_h__

#include "global_defs.h"
#include "cstreamtokenizer.h"

#define TOK_IDENTIFIER     1
#define TOK_HEX_NUMBER     3
#define TOK_DEC_NUMBER     4
#define TOK_REAL_NUMBER    5
#define TOK_CONST_STRING   6
#define TOK_CONST_WSTRING  7
#define TOK_RELOP_EQ       10
#define TOK_RELOP_GT       11
#define TOK_RELOP_LT       12
#define TOK_RELOP_GE       13
#define TOK_RELOP_LE       14
#define TOK_RELOP_NE       15
#define TOK_AROP_OR        20
#define TOK_AROP_AND       21
#define TOK_AROP_DIV       22
#define TOK_AROP_MULT      23
#define TOK_AROP_ADD       24
#define TOK_AROP_SUB       25
#define TOK_AROP_NOT       26
#define TOK_AROP_XOR       27
#define TOK_AROP_LSHIFT    28
#define TOK_AROP_RSHIFT    29
#define TOK_LOGOP_OR       30
#define TOK_LOGOP_AND      31
#define TOK_LOGOP_NOT      32
#define TOK_BRACKET_OPEN   40
#define TOK_BRACKET_CLOSE  41
#define TOK_DEFINED        50
#define TOK_SIZEOF         51
#define TOK_COMMA          60
#define TOK_ASSIGNMENT     61
#define TOK_DECIMAL_POINT  62

#define VALUE_TOKEN(token) \
   (token == TOK_IDENTIFIER || \
    token == TOK_DEC_NUMBER || \
    token == TOK_HEX_NUMBER || \
    token == TOK_REAL_NUMBER || \
    token == TOK_CONST_STRING || \
    token == TOK_CONST_WSTRING)

#define RELOP_TOKEN(token) \
   (token == TOK_RELOP_EQ || \
    token == TOK_RELOP_GT || \
    token == TOK_RELOP_LT || \
    token == TOK_RELOP_GE || \
    token == TOK_RELOP_LE || \
    token == TOK_RELOP_NE || \
    token == TOK_RELOP_GT)

#define LOGOP_TOKEN(token) \
   (token == TOK_LOGOP_NOT || \
    token == TOK_LOGOP_OR || \
    token == TOK_LOGOP_AND)

#define AROP_TOKEN(token) \
   (token ==TOK_AROP_OR || \
    token ==TOK_AROP_AND || \
    token ==TOK_AROP_DIV || \
    token ==TOK_AROP_MULT || \
    token ==TOK_AROP_ADD || \
    token ==TOK_AROP_SUB || \
    token ==TOK_AROP_NOT || \
    token ==TOK_AROP_XOR || \
    token ==TOK_AROP_LSHIFT || \
    token ==TOK_AROP_RSHIFT)

#define OP_TOKEN(token) (RELOP_TOKEN(token) || LOGOP_TOKEN(token) || AROP_TOKEN(token))

#define PREDICATE_TOKEN(token) \
   (token == TOK_DEFINED || \
    token == TOK_SIZEOF)

class cExpTokenizer : public cStreamTokenizer
{
public:
   cExpTokenizer(const char * file, int line, unsigned long chunk_size = 20);
   virtual ~cExpTokenizer();
   virtual void Scan(const char * text);
   virtual int GetToken(const char * text, const char * & token_value, const char * & tail);
   virtual const char * TokenText(int token);
protected:
   virtual int Push()
   {
      return 0;
   };
   virtual void Pop(int pos)
   {
   };
};

#endif

