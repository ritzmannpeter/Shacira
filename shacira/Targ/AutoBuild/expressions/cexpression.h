
#ifndef __cexpression_h___
#define __cexpression_h___

#include "global_defs.h"
#include "csymboltable.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define MAX_PARAMS 0x10

typedef enum {noop, integer, real, string, wstring} OperandTypes;

class cPredicate
{
public:
   cPredicate(const char * name) :
      _Name(name), _ParamCount(0)
   {
      memset(_Params, 0, sizeof(_Params));
   };
   virtual ~cPredicate()
   {
   };
   void AddParam(const char * param)
   {
      if (_ParamCount < MAX_PARAMS) {
         _Params[_ParamCount] = param;
         _ParamCount++;
      } else {
         /// hm
      }
   };
   const char * Param(unsigned long pos)
   {
      if (pos < _ParamCount) {
         return _Params[pos];
      } else {
         return "?";
      }
   };
   unsigned long ParamCount()
   {
      return _ParamCount;
   };
   inline double Evaluate(cSymbolTable * symbol_table)
   {
      if (strcmp(_Name, "defined") == 0) {
         return symbol_table->Defined(_Params[0]);
      } else if (strcmp(_Name, "sizeof") == 0) {
         return 2;
      }
      return 0;
   }
   STRING_T Text()
   {
      STRING_T text;
      text += _Name;
      text += "(";
      unsigned long i = 0;
      for (i=0; i<_ParamCount; i++) {
         if (i > 0) {
            text += ",";
         }
         text += _Params[i];
      }
      text += ")";
      return text;
   };
   inline OperandTypes OperandType()
   {
      return integer;
   };
   inline STRING_T StringValue(cSymbolTable * symbol_table)
   {
      return "???";
   };
protected:
   const char * _Name;
   unsigned long _ParamCount;
   const char * _Params[MAX_PARAMS];
};

typedef enum {identifier, const_string, const_dec, const_hex, const_real} SymbolTypes;

class cSymbol
{
public:
   cSymbol(const char * value, SymbolTypes symbol_type) :
      _Value(value), _SymbolType(symbol_type)
   {
   };
   virtual ~cSymbol()
   {
   };
   inline SymbolTypes SymbolType()
   {
      return _SymbolType;
   };
   inline double Evaluate(cSymbolTable * symbol_table)
   {
      double value = 0;
      if (_SymbolType == identifier) {
         value = symbol_table->SymbolValue(_Value);
      } else if (_SymbolType == const_string) {
         value = 0;
      } else if (_SymbolType == const_dec) {
         value = (double)atol(_Value);
      } else if (_SymbolType == const_hex) {
         unsigned long hex_value = 0;
         sscanf(_Value, "%x", &hex_value);
         value = hex_value;
      } else if (_SymbolType == const_real) {
         sscanf(_Value, "%lf", &value);
      }
      return value;
   };
   STRING_T Text()
   {
      return _Value;
   };
   inline OperandTypes OperandType()
   {
      OperandTypes operand_type = noop;
      if (_SymbolType == identifier) {
         operand_type = noop;
      } else if (_SymbolType == const_string) {
         operand_type = string;
      } else if (_SymbolType == const_dec) {
         operand_type = integer;
      } else if (_SymbolType == const_hex) {
         operand_type = integer;
      } else if (_SymbolType == const_real) {
         operand_type = real;
      }
      return operand_type;
   }
   inline STRING_T StringValue(cSymbolTable * symbol_table)
   {
      if (_SymbolType == identifier) {
         return symbol_table->SymbolString(_Value);
      } else if (_SymbolType == const_string) {
         return _Value;
      } else if (_SymbolType == const_dec) {
         return _Value;
      } else if (_SymbolType == const_hex) {
         char dec_value[0x40] = {0};
         unsigned long hex_value = 0;
         sscanf(_Value, "%x", &hex_value);
         sprintf(dec_value, "%d", hex_value);
         return dec_value;
      } else if (_SymbolType == const_real) {
         return _Value;
      }
      return "????";
   };
protected:
   const char * _Value;
   SymbolTypes _SymbolType;
};

typedef enum {relational, logical, arithmetic, functional} OperatorTypes;
typedef enum {nil, ident, predicate,
              r_eq, r_ne, r_lt, r_le, r_gt, r_ge,        /// relational operators
              l_not, l_and, l_or,                        /// logical operators
              a_not, a_and, a_or, a_div, a_mult, a_add,
              a_sub, a_xor, a_lshift, a_rshift           /// arithmetic operators
} Operators;

class cExpression;
class cExpression {
public:
   cExpression(cPredicate * pred) :
      _Predicate(pred), _Symbol(NULL), _Operator(nil), _Left(NULL), _Right(NULL)
   {
   };
   cExpression(cSymbol * symbol) :
      _Predicate(NULL), _Symbol(symbol), _Operator(nil), _Left(NULL), _Right(NULL)
   {
   };
   cExpression(Operators op, cExpression * left, cExpression * right) :
      _Predicate(NULL), _Symbol(NULL), _Operator(op), _Left(left), _Right(right)
   {
   };
   cExpression(Operators op, cExpression * exp) :
      _Predicate(NULL), _Symbol(NULL), _Operator(op), _Left(exp), _Right(NULL)
   {
   };
   virtual ~cExpression()
   {
//#ifdef only_for_tests
      if (_Left != NULL) {
         delete _Left;
      }
      if (_Right != NULL) {
         delete _Right;
      }
//#endif
   };
   inline Operators Operator()
   {
      return _Operator;
   };
   inline int IntValue(const char * value)
   {
      int ivalue = atoi(value);
      if (ivalue != -1) {
         return ivalue;
      }
      return 0;
   };
   inline bool Eval(cSymbolTable * symbol_table)
   {
      return (Evaluate(symbol_table) != 0);
   }
   inline double Evaluate(STRING_T & svalue, cSymbolTable * symbol_table)
   {
      STRING_T lval, rval;
      double value = 0;
      if (_Symbol != NULL) {
         svalue = _Symbol->StringValue(symbol_table);
      } else if (_Predicate != NULL) {
         svalue = _Predicate->StringValue(symbol_table);
      } else {
         switch (_Operator) {
         case nil:
            break;
         case ident:
            value = _Left->Evaluate(symbol_table);
            break;
         case r_eq:
            value = _Left->Evaluate(lval, symbol_table);
            value = _Right->Evaluate(rval, symbol_table);
            if (strcmp(lval.c_str(), rval.c_str()) == 0) {
               value = 1;
            } else {
               value = 0;
            }
            break;
         case r_ne:
            value = _Left->Evaluate(lval, symbol_table);
            value = _Right->Evaluate(rval, symbol_table);
            if (strcmp(lval.c_str(), rval.c_str()) != 0) {
               value = 1;
            } else {
               value = 0;
            }
            break;
         case r_lt:
         case r_le:
         case r_gt:
         case r_ge:
         case l_not:
         case l_or:
         case l_and:
         case a_not:
         case a_or:
         case a_and:
         case a_mult:
         case a_div:
         case a_add:
         case a_sub:
         case a_xor:
         case a_lshift:
         case a_rshift:
            value = Evaluate(symbol_table);
         }
      }
      return value;
   };
   inline double Evaluate(cSymbolTable * symbol_table)
   {
      OperandTypes operand_type = OperandType();
      if (operand_type == string) {
         STRING_T sval;
         return Evaluate(sval, symbol_table);
      }
      double value = 0;
      if (_Symbol != NULL) {
         value = _Symbol->Evaluate(symbol_table);
      } else if (_Predicate != NULL) {
         value = _Predicate->Evaluate(symbol_table);
      } else {
         switch (_Operator) {
         case nil:
            value = 0;
            break;
         case ident:
            value = _Left->Evaluate(symbol_table);
            break;
         case r_eq:
            value = (_Left->Evaluate(symbol_table) == _Right->Evaluate(symbol_table));
            break;
         case r_ne:
            value = (_Left->Evaluate(symbol_table) != _Right->Evaluate(symbol_table));
            break;
         case r_lt:
            value = (_Left->Evaluate(symbol_table) < _Right->Evaluate(symbol_table));
            break;
         case r_le:
            value = (_Left->Evaluate(symbol_table) <= _Right->Evaluate(symbol_table));
            break;
         case r_gt:
            value = (_Left->Evaluate(symbol_table) > _Right->Evaluate(symbol_table));
            break;
         case r_ge:
            value = (_Left->Evaluate(symbol_table) >= _Right->Evaluate(symbol_table));
            break;
         case l_not:
            value = (_Left->Evaluate(symbol_table) == 0);
            break;
         case l_or:
            value = ((_Left->Evaluate(symbol_table) != 0) || (_Right->Evaluate(symbol_table) != 0));
            break;
         case l_and:
            value = ((_Left->Evaluate(symbol_table) != 0) && (_Right->Evaluate(symbol_table) != 0));
            break;
         case a_not:
            value = (~((unsigned long)_Left->Evaluate(symbol_table)));
            break;
         case a_or:
            value = (((unsigned long)_Left->Evaluate(symbol_table)) | ((unsigned long)_Right->Evaluate(symbol_table)));
            break;
         case a_and:
            value = (((unsigned long)_Left->Evaluate(symbol_table))  & ((unsigned long)_Right->Evaluate(symbol_table)));
            break;
         case a_mult:
            value = (_Left->Evaluate(symbol_table) * _Right->Evaluate(symbol_table));
            break;
         case a_div:
            value = (_Left->Evaluate(symbol_table) / _Right->Evaluate(symbol_table));
            break;
         case a_add:
            value = (_Left->Evaluate(symbol_table) + _Right->Evaluate(symbol_table));
            break;
         case a_sub:
            value = (_Left->Evaluate(symbol_table) - _Right->Evaluate(symbol_table));
            break;
         case a_xor:
            value = (((unsigned long)_Left->Evaluate(symbol_table)) ^ ((unsigned long)_Right->Evaluate(symbol_table)));
            break;
         case a_lshift:
            value = (((unsigned long)_Left->Evaluate(symbol_table))  << ((unsigned long)_Right->Evaluate(symbol_table)));
            break;
         case a_rshift:
            value = (((unsigned long)_Left->Evaluate(symbol_table))  >> ((unsigned long)_Right->Evaluate(symbol_table)));
            break;
         }
      }
      return value;
   }
   STRING_T Text()
   {
      STRING_T text;
      if (_Symbol != NULL) {
         return _Symbol->Text();
      } else if (_Predicate != NULL) {
         return _Predicate->Text();
      } else if (_Left != NULL &&
                 _Right != NULL) {
         text += "(";
         text += _Left->Text().c_str();
         text += " ";
         text += OpText(_Operator);
         text += " ";
         text += _Right->Text().c_str();
         text += ")";
      } else if (_Operator == ident) {
//         text += "(";
         text += _Left->Text().c_str();
//         text += ")";
      } else {
         text += OpText(_Operator);
         text += "(";
         if (_Left != NULL) {
            text += _Left->Text().c_str();
         }
         text += ")";
      }
      return text;
   };
protected:
   Operators _Operator;
   cExpression * _Left;
   cExpression * _Right;
   cPredicate * _Predicate;
   cSymbol * _Symbol;
public:
   static inline bool Superseeds(Operators op1, Operators op2)
   {
      OperatorTypes type1 = OpType(op1);
      OperatorTypes type2 = OpType(op2);
      if (op1 == l_and ||
          type1 == relational ||
          type1 == arithmetic) {
         return true;
      } else {
         return false;
      }
   };
   static inline bool Precedes(Operators op1, Operators op2)
   {
      OperatorTypes type1 = OpType(op1);
      OperatorTypes type2 = OpType(op2);
      if (op1 == l_and ||
          type1 == relational ||
          type1 == arithmetic) {
         return true;
      } else {
         return false;
      }
   };
   static inline const char * OpText(Operators op)
   {
      switch (op) {
      case nil: return "nil";
      case ident: return "ident";
      case r_eq: return "==";
      case r_ne: return "!=";
      case r_lt: return "<";
      case r_le: return "<=";
      case r_gt: return ">";
      case r_ge: return ">=";
      case l_not: return "!";
      case l_or: return "||";
      case l_and: return "&&";
      case a_not: return "~";
      case a_or: return "|";
      case a_and: return "&";
      case a_mult: return "*";
      case a_div: return "/";
      case a_add: return "+";
      case a_sub: return "-";
      case a_xor: return "^";
      case a_lshift: return "<<";
      case a_rshift: return ">>";
      }
      return "?";
   };
   static inline OperatorTypes OpType(Operators op)
   {
      switch (op) {
      case nil: return logical;
      case ident: return logical;
      case r_eq: return relational;
      case r_ne: return relational;
      case r_lt: return relational;
      case r_le: return relational;
      case r_gt: return relational;
      case r_ge: return relational;
      case l_not: return logical;
      case l_or: return logical;
      case l_and: return logical;
      case a_not: return arithmetic;
      case a_or: return arithmetic;
      case a_and: return arithmetic;
      case a_mult: return arithmetic;
      case a_div: return arithmetic;
      case a_add: return arithmetic;
      case a_sub: return arithmetic;
      case a_xor: return arithmetic;
      case a_lshift: return arithmetic;
      case a_rshift: return arithmetic;
      }
      return arithmetic;
   };
   inline OperandTypes MergeOperands(OperandTypes left, OperandTypes right)
   {
      if (left == right) {
         return left;
      } else if (left == noop) {
         return right;
      } else if (right == noop) {
         return left;
      }
      OperandTypes operand_type = noop;
      switch (left) {
      case integer:
         switch (right) {
         case string:
printf("operand conflict (%d,%d)");
operand_type = right;
            break;
         case real:
printf("operand conflict (%d,%d)");
operand_type = right;
            break;
         }
         break;
      case string:
         switch (right) {
         case integer:
printf("operand conflict (%d,%d)");
operand_type = right;
            break;
         case real:
printf("operand conflict (%d,%d)");
operand_type = right;
            break;
         }
         break;
      case real:
         switch (right) {
         case integer:
printf("operand conflict (%d,%d)");
operand_type = right;
            break;
         case string:
printf("operand conflict (%d,%d)");
operand_type = right;
            break;
         }
         break;
      }
      return operand_type;
   };
   inline OperandTypes OperandType()
   {
      OperandTypes operand_type = noop;
      if (_Symbol != NULL) {
         operand_type = _Symbol->OperandType();
      } else if (_Predicate != NULL) {
         operand_type = _Predicate->OperandType();
      } else if (_Left != NULL &&
                 _Right != NULL) {
         operand_type = MergeOperands(_Left->OperandType(), _Right->OperandType());
      } else if (_Left != NULL) {
         operand_type = _Left->OperandType();
      }
      return operand_type;
#ifdef lassma
      switch (_Operator) {
      case nil:
      case ident:
         return noop;
         break;
      case r_eq:
      case r_ne:
      case r_lt:
      case r_le:
      case r_gt:
      case r_ge:
         operand_type = MergeOperands(_Left->OperandType(), _Right->OperandType());
         break;
      case l_not:
         operand_type = _Left->OperandType();
         break;
      case l_or:
      case l_and:
         operand_type = MergeOperands(_Left->OperandType(), _Right->OperandType());
         break;
      case a_not:
      case a_or:
      case a_and:
      case a_mult:
      case a_div:
      case a_add:
      case a_sub:
      case a_xor:
      case a_lshift:
      case a_rshift:
         operand_type = MergeOperands(_Left->OperandType(), _Right->OperandType());
         break;
      }
#endif
   };
};

#endif
