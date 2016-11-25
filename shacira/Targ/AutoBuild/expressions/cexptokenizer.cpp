
#include "cexptokenizer.h"
#include "global_defs.h"
#include <stdio.h>
#include <ctype.h>

#define ST_INIT         0
#define ST_NUMBER       1
#define ST_HEX_NUMBER   2
#define ST_REAL_NUMBER  3
#define ST_IDENTIFIER   4
#define ST_STRING_CONST 5
#define ST_WSTRING_CONST 7

cExpTokenizer::cExpTokenizer(const char * file, int line, unsigned long chunk_size) :
   cStreamTokenizer(file, line, chunk_size)
{
}

cExpTokenizer::~cExpTokenizer()
{
}

void cExpTokenizer::Scan(const char * text)
{
   const char * tail = text;
   const char * token_value = NULL;
   int token = GetToken(tail, token_value, tail);
   while (token != EMPTY_TOKEN) {
      AddToken(token, token_value);
      token = GetToken(tail, token_value, tail);
   }
}

static void RaiseError(const char * file, int line, const char * text, int i, char c, const char * token_value)
{
   Printf(M_ERROR, "syntax error in\n%s\n", text);
}

static char _TokenValue[0x1000] = {0};
#define ADD_CHAR() \
   _TokenValue[dst_index] = c; \
   dst_index++; \
   _TokenValue[dst_index] = 0; \
   i++;

#define SYNTAX_ERROR() \
   RaiseError(_File, _Line, text, i, c, _TokenValue); \
   token = EMPTY_TOKEN; \
   error = 1; \
   break;

int cExpTokenizer::GetToken(const char * text, const char * & token_value, const char * & tail)
{
   int error = 0;
   int state = ST_INIT;
   int token = EMPTY_TOKEN;
   int len = strlen(text);
   int i = 0, dst_index = 0;
   int token_pos = 0;
   char c = 0;
   while (42) {
      c = text[i];
      if (c == '\0') {
         break;
      }
      if (c == '"') {
         if (state == ST_STRING_CONST) {
            token = TOK_CONST_STRING;
            i++;
            break;
         } else if (state == ST_WSTRING_CONST) {
            token = TOK_CONST_WSTRING;
            i++;
            break;
         } else {
            if (state == ST_INIT) {
               state = ST_STRING_CONST;
               i++;
            } else if (state == ST_IDENTIFIER) {
               if (_TokenValue[0] == 'L' &&
                   _TokenValue[1] == 0) {
                  dst_index = 0;
                  state = ST_STRING_CONST;
                  i++;
               } else {
                  SYNTAX_ERROR();
               }
            } else {
               SYNTAX_ERROR();
            }
         }
      } else if (state == ST_STRING_CONST ||
                 state == ST_WSTRING_CONST) {
         ADD_CHAR();
      } else if (c == '(') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_BRACKET_OPEN;
         ADD_CHAR();
         break;
      } else if (c == ')') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_BRACKET_CLOSE;
         ADD_CHAR();
         break;
      } else if (c == ',') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_COMMA;
         ADD_CHAR();
         break;
      } else if (c == '.') {
         if (state == ST_NUMBER) {
            state = ST_REAL_NUMBER;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_DECIMAL_POINT;
            ADD_CHAR();
            break;
         }
         ADD_CHAR();
      } else if (c == '=') {
         if (text[i+1] == '=') {
            token = TOK_RELOP_EQ;
            ADD_CHAR();
            c = text[i];
            ADD_CHAR();
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_ASSIGNMENT;
            ADD_CHAR();
            break;
         }
      } else if (c == '<') {
         if (text[i+1] == '=') {
            token = TOK_RELOP_LE;
            ADD_CHAR();
            c = text[i];
            ADD_CHAR();
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_RELOP_LT;
            ADD_CHAR();
            break;
         }
      } else if (c == '>') {
         if (text[i+1] == '=') {
            token = TOK_RELOP_GE;
            ADD_CHAR();
            c = text[i];
            ADD_CHAR();
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_RELOP_GT;
            ADD_CHAR();
            break;
         }
      } else if (c == '!') {
         if (text[i+1] == '=') {
            token = TOK_RELOP_NE;
            ADD_CHAR();
            c = text[i];
            ADD_CHAR();
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_LOGOP_NOT;
            ADD_CHAR();
            break;
         }
      } else if (c == '|') {
         if (text[i+1] == '|') {
            token = TOK_LOGOP_OR;
            ADD_CHAR();
            c = text[i];
            ADD_CHAR();
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_AROP_OR;
            ADD_CHAR();
            break;
         }
      } else if (c == '&') {
         if (text[i+1] == '&') {
            token = TOK_LOGOP_AND;
            ADD_CHAR();
            c = text[i];
            ADD_CHAR();
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_AROP_AND;
            ADD_CHAR();
            break;
         }
      } else if (c == '/') {
         if (text[i+1] == '/' ||
             text[i+1] == '*') {
            break;
         } else {
            if (state != ST_INIT) {
               break;
            }
            token = TOK_AROP_DIV;
            ADD_CHAR();
            break;
         }
      } else if (c == '*') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_AROP_MULT;
         ADD_CHAR();
         break;
      } else if (c == '+') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_AROP_ADD;
         ADD_CHAR();
         break;
      } else if (c == '-') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_AROP_SUB;
         ADD_CHAR();
         break;
      } else if (c == '~') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_AROP_NOT;
         ADD_CHAR();
         break;
      } else if (c == '^') {
         if (state != ST_INIT) {
            break;
         }
         token = TOK_AROP_XOR;
         ADD_CHAR();
         break;
      } else if (isdigit(c)) {
         if (state == ST_INIT) {
            state = ST_NUMBER;
         }
         ADD_CHAR();
      } else if (isalpha(c) ||
                 c == '_') {
         if (state == ST_INIT) {
            state = ST_IDENTIFIER;
         } else if (state == ST_NUMBER) {
            if (c == 'x' ||
                c == 'X') {
               state = ST_HEX_NUMBER;
            } else if (c == 'L') {
            } else if (c == 'U') {
               /// consume it
            } else {
               SYNTAX_ERROR();
            }
         } else if (state == ST_HEX_NUMBER) {
            if (c == 'a' ||
                c == 'b' ||
                c == 'c' ||
                c == 'd' ||
                c == 'e' ||
                c == 'f' ||
                c == 'A' ||
                c == 'B' ||
                c == 'C' ||
                c == 'D' ||
                c == 'E' ||
                c == 'F') {
            } else {
            }
         } else if (state == ST_IDENTIFIER) {
         } else {
            if (state == ST_REAL_NUMBER &&
                (c == 'e' || c == 'E')) {
            } else {
               SYNTAX_ERROR();
            }
         }
         ADD_CHAR()
      } else {
         if (state == ST_INIT) {
            i++;
         } else {
            break;
         }
      }
   }
   if (error == 0) {
      if (token == EMPTY_TOKEN) {
         switch (state) {
         case ST_NUMBER: token = TOK_DEC_NUMBER; break;
         case ST_HEX_NUMBER: token = TOK_HEX_NUMBER; break;
         case ST_REAL_NUMBER: token = TOK_REAL_NUMBER; break;
         case ST_IDENTIFIER:
            if (strcmp(_TokenValue, "defined") == 0) {
               token = TOK_DEFINED;
            } else if (strcmp(_TokenValue, "sizeof") == 0) {
               token = TOK_SIZEOF;
            } else {
               token = TOK_IDENTIFIER;
            }
            break;
         }
      }
   }
   if (token == EMPTY_TOKEN) {
      token_value = NULL;
   } else {
      token_value = AllocTokenValue(_TokenValue);
   }
   tail = &text[i];
   return token;
}

const char * cExpTokenizer::TokenText(int token)
{
   switch (token) {
   case EMPTY_TOKEN: return "empty";
   case TOK_IDENTIFIER: return "identifier";
   case TOK_HEX_NUMBER: return "hex";
   case TOK_DEC_NUMBER: return "dec";
   case TOK_REAL_NUMBER: return "real";
   case TOK_RELOP_EQ: return "==";
   case TOK_RELOP_GT: return ">";
   case TOK_RELOP_LT: return "<";
   case TOK_RELOP_GE: return ">=";
   case TOK_RELOP_LE: return "<=";
   case TOK_RELOP_NE: return "!=";
   case TOK_AROP_OR: return "|";
   case TOK_AROP_AND: return "&";
   case TOK_AROP_DIV: return "/";
   case TOK_AROP_MULT: return "*";
   case TOK_AROP_ADD: return "&";
   case TOK_AROP_SUB: return "-";
   case TOK_AROP_NOT: return "~";
   case TOK_AROP_XOR: return "^";
   case TOK_AROP_LSHIFT: return "<<";
   case TOK_AROP_RSHIFT: return ">>";
   case TOK_LOGOP_OR: return "||";
   case TOK_LOGOP_AND: return "&&";
   case TOK_LOGOP_NOT: return "!";
   case TOK_BRACKET_OPEN: return "(";
   case TOK_BRACKET_CLOSE: return ")";
   case TOK_DEFINED: return "defined";
   case TOK_SIZEOF: return "sizeof";
   }
   return "?";
}

