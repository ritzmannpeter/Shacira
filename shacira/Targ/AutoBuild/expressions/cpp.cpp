
#include "cpp.h"
#include "cexptokenizer.h"
#include "cexpparser.h"
#include "global_defs.h"
#include <stdio.h>

#define STATE(ss,level) (level > 0 ? ss->Get(level) : true)
#define SET_STATE(ss,level,state) SetState(ss, level, state);

static void SetState(cStateStack * ss, int level, bool state)
{
   ss->Set(level, state);
}

static bool Eval(const char * file, int line, const char * text, cSymbolTable * symbol_table)
{
   bool result = false;
   cExpTokenizer tokenizer(file, line);
   cExpParser parser(&tokenizer);
   tokenizer.Scan(text);
   cExpression * exp = parser.Parse();
   if (exp != NULL) {
      result = exp->Eval(symbol_table);
      if (!result) {
      }
   } else {
      Printf(M_ERROR, "failed to interprete:\n%s\n", text);
   }
   return result;
}

bool _ifndef(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   level++;
   bool super_state = STATE(state_stack,level-1);
   if (super_state) {
      bool state = !Eval(file, line, text, symbol_table);
      SET_STATE(state_stack,level,state);
   }
   return true;
}

bool _if(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   level++;
   bool super_state = STATE(state_stack,level-1);
   if (super_state) {
      bool state = Eval(file, line, text, symbol_table);
      SET_STATE(state_stack,level,state);
   } else {
   }
   return true;
}

bool _ifdef(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   level++;
   bool super_state = STATE(state_stack,level-1);
   if (super_state) {
      bool state = Eval(file, line, text, symbol_table);
      SET_STATE(state_stack,level,state);
   } else {
   }
   return true;
}

bool _elif(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   bool super_state = STATE(state_stack,level-1);
   if (super_state) {
      bool state = Eval(file, line, text, symbol_table);
      SET_STATE(state_stack,level,state);
   } else {
   }
   return true;
}

bool _else(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   bool super_state = STATE(state_stack,level-1);
   if (super_state) {
      bool state = STATE(state_stack,level);
      state = !state;
      SET_STATE(state_stack,level,state);
   } else {
   }
   return true;
}

bool _endif(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   bool super_state = STATE(state_stack,level-2);
   if (super_state) {
      SET_STATE(state_stack,level, STATE(state_stack,level-1));
   } else {
   }
   level--;
   return true;
}

bool _define(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   bool super_state = STATE(state_stack,level-1);
   bool state = STATE(state_stack,level);
   if (super_state && state) {
      cExpTokenizer tokenizer(file, line);
      tokenizer.Scan(text);
      const char * symbol = NULL;
      const char * symbol_value = NULL;
      int token = tokenizer.GetNextToken(symbol);
      if (VALUE_TOKEN(token)) {
         token = tokenizer.GetNextToken(symbol_value);
         double value = 0;
         if (token == TOK_IDENTIFIER) {
            value = symbol_table->SymbolValue(symbol_value);
         } else if (token == TOK_DEC_NUMBER) {
            value = (double)atol(symbol_value);
         } else if (token == TOK_HEX_NUMBER) {
            unsigned long hex_value = 0;
            sscanf(symbol_value, "%x", &hex_value);
            value = hex_value;
         } else if (token == TOK_REAL_NUMBER) {
            sscanf(symbol_value, "%lf", &value);
         } else {
            value = 1;
         }
         symbol_table->Define(symbol, value);
      }
   } else {
   }
   return true;
}

bool _undef(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   bool super_state = STATE(state_stack,level-1);
   bool state = STATE(state_stack,level);
   if (super_state && state) {
      cExpTokenizer tokenizer(file, line);
      tokenizer.Scan(text);
      const char * symbol = NULL;
      int token = tokenizer.GetNextToken(symbol);
      if (VALUE_TOKEN(token)) {
         symbol_table->Undef(symbol);
      }
   } else {
   }
   return true;
}

bool _include(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack)
{
   return _accept(level, state_stack);
}

bool _accept(int level, cStateStack * state_stack)
{
   bool super_state = STATE(state_stack,level-1);
   bool state = STATE(state_stack,level);
   if (super_state && state) {
      return true;
   } else {
      return false;
   }
   return true;
}

bool CheckCondition(int & level, const char * file, int line, const char * text, bool state,
                    cSymbolTable * symbol_table, cStateStack * state_stack)
{
   bool success = true;
   int params = 0;
   if (strnicmp(text, "#ifndef", 7) == 0) {
      success = _ifndef(file, line, &text[7], level, symbol_table, state_stack);
   } else if (strnicmp(text, "#ifdef", 6) == 0) {
      success = _ifdef(file, line, &text[6], level,  symbol_table, state_stack);
   } else if (strnicmp(text, "#if", 3) == 0) {
      success = _if(file, line, &text[3], level,  symbol_table, state_stack);
   } else if (strnicmp(text, "#elif", 5) == 0) {
      success = _elif(file, line, &text[5], level, symbol_table, state_stack);
   } else if (strnicmp(text, "#else", 5) == 0) {
      success = _else(file, line, &text[6], level, symbol_table, state_stack);
   } else if (strnicmp(text, "#endif", 6) == 0) {
      success = _endif(file, line, &text[6], level, symbol_table, state_stack);
   } else if (strnicmp(text, "#define", 7) == 0) {
      if (state) {
         success = _define(file, line, &text[7], level, symbol_table, state_stack);
      }
   } else if (strnicmp(text, "#undef", 6) == 0) {
      if (state) {
         success = _undef(file, line, &text[6], level, symbol_table, state_stack);
      }
   } else if (strnicmp(text, "#include", 8) == 0) {
      if (state) {
      }
   }
   return _accept(level, state_stack);
}

