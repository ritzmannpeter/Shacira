
#include "cexptokenizer.h"
#include "cexpparser.h"
#include <stdio.h>

/// Exp1 ::= "!" Exp1
/// Exp1 ::= "(" Exp ")"
/// Exp1 ::= Pred Value
/// Exp1 ::= Pred ( ParamList )
/// Exp1 ::= Value
/// Exp ::= Exp1 Operator ExpList
/// ExpList ::= Exp Operator ExpList |
///             empty
/// ParamList ::= Param "," ParamList |
///               Param
/// Param ::= Value
/// Value ::= Identifier |
///           Number

cExpression * cExpParser::Parse()
{
   return Exp(0);
}

cExpression * cExpParser::Exp(int level)
{
   cExpression * local_exp = NULL;
   Operators op = nil;
   Operators prev_op = nil;
   cExpression * prev_exp = NULL;
   cExpression * exp = Exp1(level);
   while (exp != NULL) {
#ifdef SHOW_PROCESS
      STRING_T text = exp->Text();
      printf("%d: ", level);
      int i = 0;
      for (i = 0; i<level; i++) {
         printf("  ");
      }
      printf("%s ", op == nil ? "" : cExpression::OpText(op));
      printf("%s\n", text.c_str());
#endif
      if (local_exp == NULL) {
         local_exp = exp;
      } else {
         cExpression * new_exp = new cExpression(op, local_exp, exp);
         local_exp = new_exp;
      }
      int lookup = _Tokenizer->Lookup();
      if (OP_TOKEN(lookup)) {
         prev_op = op;
         prev_exp = exp;
         op = Operator();
         exp = Exp1(level);
      } else {
         return local_exp;
      }
   }
   return local_exp;
}

cExpression * cExpParser::Exp1(int level)
{
   Operators op = nil;
   Operators list_op = nil;
   cExpression * local_exp = NULL;
   cExpression * exp = NULL;
   cExpression * right = NULL;
   int token = EMPTY_TOKEN;
   const char * token_value = NULL;
   int lookup = _Tokenizer->Lookup();

   if (lookup == TOK_LOGOP_NOT) {
/// Exp1 ::= "!" Exp1
      token = _Tokenizer->GetNextToken(token_value);     /// remove "!"
      exp = Exp1(level + 1);
      if (exp != NULL) {
         local_exp = new cExpression(l_not, exp);
         return local_exp;
      }
   } else if (lookup == TOK_BRACKET_OPEN) {
/// Exp1 ::= "(" Exp ")"
      token = _Tokenizer->GetNextToken(token_value);     /// remove "("
      exp = Exp(level + 1);
      if (exp != NULL) {
         local_exp = new cExpression(ident, exp);
         token = _Tokenizer->GetNextToken(token_value);  /// remove ")"
         return local_exp;
      }
   } else if (PREDICATE_TOKEN(lookup)) {
      const char * pred_name = NULL;
      const char * param = NULL;
      token = _Tokenizer->GetNextToken(pred_name);
      token = _Tokenizer->GetNextToken(param);
      if (token == TOK_BRACKET_OPEN) {
/// Exp1 ::= Pred ( ParamList )
         cPredicate * pred = new cPredicate(pred_name);
         int params = ParamList(pred);
         token = _Tokenizer->GetNextToken(token_value);  /// remove ")"
         local_exp = new cExpression(pred);
         return local_exp;
      } else if (VALUE_TOKEN(token)) {
/// Exp1 ::= Pred Value
         cPredicate * pred = new cPredicate(pred_name);
         pred->AddParam(param);
         local_exp = new cExpression(pred);
         return local_exp;
      }
   } else if (VALUE_TOKEN(lookup)) {
/// Exp1 ::= Value
      token = _Tokenizer->GetNextToken(token_value);
      cSymbol * symbol = new cSymbol(token_value, SymbolType(token));
      local_exp = new cExpression(symbol);
      return local_exp;
   }
   return NULL;
}

int cExpParser::ParamList(cPredicate * pred)
{
   const char * token_value = NULL;
   int token = EMPTY_TOKEN;
   int lookup = _Tokenizer->Lookup();
   if (lookup == TOK_COMMA) {
/// ParamList ::= Param "," ParamList
      token = _Tokenizer->GetNextToken(token_value);  
      token = _Tokenizer->GetNextToken(token_value);
      pred->AddParam(token_value);
      return ParamList(pred);
   } else if (VALUE_TOKEN(lookup)) {
/// ParamList ::= Param
      token = _Tokenizer->GetNextToken(token_value);
      pred->AddParam(token_value);
      return ParamList(pred);
   } else {
      return pred->ParamCount();
   }
}

Operators cExpParser::Operator()
{
   const char * token_value = NULL;
   int token = _Tokenizer->GetNextToken(token_value);
   if (OP_TOKEN(token)) {
      return OpValue(token);;
   } else {
      return nil;
   }
}

Operators cExpParser::OpValue(int token)
{
   Operators op = ident;
   switch (token) {
   case EMPTY_TOKEN:
   case TOK_IDENTIFIER:
   case TOK_HEX_NUMBER:
   case TOK_DEC_NUMBER:
   case TOK_REAL_NUMBER:
   case TOK_RELOP_EQ:
      op = r_eq;
      break;
   case TOK_RELOP_GT:
      op = r_gt;
      break;
   case TOK_RELOP_LT:
      op = r_lt;
      break;
   case TOK_RELOP_GE:
      op = r_ge;
      break;
   case TOK_RELOP_LE:
      op = r_le;
      break;
   case TOK_RELOP_NE:
      op = r_ne;
      break;
   case TOK_AROP_OR:
      op = a_or;
      break;
   case TOK_AROP_AND:
      op = a_and;
      break;
   case TOK_AROP_DIV:
      op = a_div;
      break;
   case TOK_AROP_MULT:
      op = a_mult;
      break;
   case TOK_AROP_ADD:
      op = a_add;
      break;
   case TOK_AROP_SUB:
      op = a_sub;
      break;
   case TOK_AROP_NOT:
      op = a_not;
      break;
   case TOK_AROP_XOR:
      op = a_xor;
      break;
   case TOK_AROP_LSHIFT:
      op = a_lshift;
      break;
   case TOK_AROP_RSHIFT:
      op = a_rshift;
      break;
   case TOK_LOGOP_OR:
      op = l_or;
      break;
   case TOK_LOGOP_AND:
      op = l_and;
      break;
   case TOK_LOGOP_NOT:
      op = l_not;
      break;
   case TOK_BRACKET_OPEN:
   case TOK_BRACKET_CLOSE:
   case TOK_DEFINED:
      break;
   }
   return op;
}

const char * cExpParser::OpText(int token)
{
   Operators op = OpValue(token);
   return cExpression::OpText(op);
}

SymbolTypes cExpParser::SymbolType(int token)
{
   switch (token) {
   case TOK_IDENTIFIER: return identifier;
   case TOK_HEX_NUMBER: return const_hex;
   case TOK_DEC_NUMBER: return const_dec;
   case TOK_REAL_NUMBER: return const_real;
   case TOK_CONST_STRING: return const_string;
   case TOK_CONST_WSTRING: return const_string;
   }
   return identifier;
}


