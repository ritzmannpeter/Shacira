//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>
#include "cParse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static char _Text[4096];
static int DebugPrintf(char * fmtstr, ...)
{
   va_list args;
   FILE * stream;

   va_start(args, fmtstr);
   vsprintf(_Text, fmtstr, args);
   va_end(args);
   stream = fopen("parse.txt", "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _Text);
      fclose(stream);
   }
   return 0;
}

#define MAX_FUNC_PARAMS    10
typedef int (*FUNCTION_T)(cVariable * variable, int argc, int * argi);

typedef struct
{  const char * func_name;
   FUNCTION_T func_addr;
}  FUNCTION_ENTRY_T;

static int Multiply(cVariable * variable, int argc, int * argi)
{
   int val = argi[0] * argi[1];
   return val;
}

static int Divide(cVariable * variable, int argc, int * argi)
{
   int val = argi[0] / argi[1];
   return val;
}

static int Value(cVariable * variable, int argc, int * argi)
{
   int val = 0;
   switch (argi[0]) {
   case 0: val = variable->Value(); break;
   default: break;
   }
   return val;
}

const FUNCTION_ENTRY_T Functions[] =
{
   {"Value", Value},
   {"$", Value},
   {"Multiply", Multiply},
   {"Divide", Divide}
};
#define FUNCTION_COUNT     (sizeof(Functions)/sizeof(FUNCTION_ENTRY_T))

static FUNCTION_T FindFunction(const char * name)
{
   for (int i=0; i<FUNCTION_COUNT; i++) {
      if (strnicmp(name, Functions[i].func_name, strlen(name)) == 0) {
         return Functions[i].func_addr;
      }
   }
   return NULL;
}

cNode::cNode() :
   _Type(T_UNDEF)
{
}

cNode::cNode(int intval) :
   _Type(T_INTVAL), _IntVal(intval)
{
}

cNode::cNode(const char * consttext) :
   _Type(T_CONSTTEXT), _ConstText(consttext)
{
}

cNode::cNode(cNode * node) :
   _Type(T_FUNCTION)
{
}

cNode::~cNode()
{
}

int cNode::CallFunction(cVariable * variable, const char * name, int argc, int * argi)
{
   FUNCTION_T func = FindFunction(name);
   if (func == NULL) {
      return -997;
   } else {
      func(variable, argc, argi);
   }
}

void cNode::SetName(const char * name)
{
   _Type = T_FUNCTION;
   _FuncName = name;
}

void cNode::AddParam(cNode * param)
{
   _Params.push_back(param);
}

int cNode::IntVal(cVariable * variable)
{
   if (_Type == T_UNDEF) {
      return -1;
   } else if (_Type == T_INTVAL) {
      return _IntVal;
   } else if (_Type == T_FUNCTION) {
   /* Funktionsaufruf absetzen
    */
      int argc = _Params.size();
      if (argc >= MAX_FUNC_PARAMS) return -998;
      int argi[MAX_FUNC_PARAMS] = {0};
      if (argc > 0) {
         list<cNode*>::iterator p = _Params.begin();
         int i = 0;
         while (p != _Params.end()) {
            argi[i] = (*p)->IntVal(variable);
            p++;
            i++;
         }
      }
      return CallFunction(variable, _FuncName.c_str(),argc,argi);
   } else {
      return -999;
   }
}

string cNode::ConstText()
{
   if (_Type == T_UNDEF) {
      return string("T_UNDEF");
   } else if (_Type == T_CONSTTEXT) {
      return _ConstText;
   } else {
      return string("NO CONST TEXT");
   }
}

string cNode::FuncName()
{
   if (_Type == T_FUNCTION) {
      return _FuncName;
   } else {
      return string("NO FUNC");
   }
}

cParse::cParse(cVariables * variables, const char * & text, int line) :
   _Variable(NULL), _Variables(variables), _Line(line)
{
   Parse(text);
}

cParse::~cParse()
{
}

bool cParse::Parse(const char * & text)
{
   cVariable * variable = NULL;
   cNode * prec = NULL;
   cNode * func = NULL;
   string token_value;
   TToken token;
   while ((token = GetToken(text, token_value)) != T_EOF) {
      DebugPrintf("Token %d:%s value %s\n", token, TokenName(token), token_value.c_str());
      switch (token) {
      case T_NEXT_ELEMENT:;
         break;
      case T_REGVAR:
         if (variable != NULL) {
            return false;
         } else {
            if ((variable = ScanRegvar(text)) == NULL) return false;
         }
         break;
      case T_IREGVAR:
         if (variable != NULL) {
            return false;
         } else {
            if ((variable = ScanIRegvar(text)) == NULL) return false;
         }
         break;
      case T_TEXTVAR:
         if (variable != NULL) {
            return false;
         } else {
            if ((variable = ScanTextvar(text)) == NULL) return false;
         }
         break;
      case T_HEATVAR:
         if (variable != NULL) {
            return false;
         } else {
            if ((variable = ScanHeatvar(text)) == NULL) return false;
         }
         break;
      case T_PRECISION:
         if (prec != NULL) {
            return false;
         } else {
            if ((prec = ScanValue(text)) == NULL) return false;
         }
         break;
      case T_CONSTTEXT:
         break;
      case T_INTVAL:
         break;
      case T_FUNCTION:
         if (func != NULL) {
            return false;
         } else {
            if ((func = ScanFunc(token_value.c_str(), text)) == NULL) return false;
         }
         break;
         break;
      default: return false;
      }
   }
   if (variable == NULL) {
      return false;
   } else {
      variable->SetPrec(prec);
      variable->SetFunc(func);
      _Variable = variable;
      return true;
   }
}

cRegvar * cParse::ScanRegvar(const char * & text)
{
   string token_val;
   TToken token;

   if ((token = GetToken(text, token_val)) != T_BEGIN_LIST) return NULL;

   cNode * reg_no = ScanFunc(text);
   if (reg_no == NULL) return NULL;

   if ((token = GetToken(text, token_val)) != T_END_LIST) return NULL;

   cRegvar * regvar = new cRegvar(_Variables, reg_no);
   return regvar;
}

cRegvar * cParse::ScanIRegvar(const char * & text)
{
   string token_val;
   TToken token;

   if ((token = GetToken(text, token_val)) != T_BEGIN_LIST) return NULL;

   cNode * reg_no = ScanFunc(text);
   if (reg_no == NULL) return NULL;
   if ((token = GetToken(text, token_val)) != T_NEXT_ELEMENT) return NULL;
   cNode * index = ScanFunc(text);
   if (index == NULL) return NULL;

   if ((token = GetToken(text, token_val)) != T_END_LIST) return NULL;

   cRegvar * regvar = new cRegvar(_Variables, reg_no, index);
   return regvar;
}

cTextvar * cParse::ScanTextvar(const char * & text)
{
   string token_val;
   TToken token;

   if ((token = GetToken(text, token_val)) != T_BEGIN_LIST) return NULL;

   cNode * text_id = ScanFunc(text);
   if (text_id == NULL) return NULL;
   if ((token = GetToken(text, token_val)) != T_NEXT_ELEMENT) return NULL;
   cNode * row = ScanFunc(text);
   if (row == NULL) return NULL;

   if ((token = GetToken(text, token_val)) != T_END_LIST) return NULL;

   cTextvar * textvar = new cTextvar(_Variables, text_id, row);
   return textvar;
}

cHeatvar * cParse::ScanHeatvar(const char * & text)
{
   string token_val;
   TToken token;

   if ((token = GetToken(text, token_val)) != T_BEGIN_LIST) return NULL;

   cNode * group = ScanFunc(text);
   if (group == NULL) return NULL;
   if ((token = GetToken(text, token_val)) != T_NEXT_ELEMENT) return NULL;
   cNode * zone = ScanFunc(text);
   if (zone == NULL) return NULL;
   if ((token = GetToken(text, token_val)) != T_NEXT_ELEMENT) return NULL;
   cNode * unit = ScanFunc(text);
   if (unit == NULL) return NULL;
   if ((token = GetToken(text, token_val)) != T_NEXT_ELEMENT) return NULL;
   cNode * param = ScanFunc(text);
   if (param == NULL) return NULL;

   if ((token = GetToken(text, token_val)) != T_END_LIST) return NULL;

   cHeatvar * heatvar = new cHeatvar(_Variables, group, zone, unit, param);
   return heatvar;
}

cNode * cParse::ScanValue(const char * & text)
{
   cNode * node = NULL;
   TToken token;
   string token_value;
   if ((token = GetToken(text, token_value)) != T_BEGIN_LIST) return NULL;
   if ((node = ScanFunc(text)) == NULL) return NULL;
   if ((token = GetToken(text, token_value)) != T_END_LIST) return NULL;
   return node;
}

cNode * cParse::ScanFunc(const char * & text)
{
   string token_val;
   TToken token = GetToken(text, token_val);
   if (token == T_INTVAL) {
      int intval = atoi(token_val.c_str());
      cNode * node = new cNode(intval);
      return node;
   } else if (token == T_CONSTTEXT) {
      cNode * node = new cNode(token_val.c_str());
      return node;
   } else if (token == T_FUNCTION){
      cNode * func = new cNode();
      func->SetName(token_val.c_str());
      if ((token = GetToken(text, token_val)) == T_BEGIN_LIST) {
         while (true) {
            cNode * node = ScanFunc(text);
            if (node == NULL) {
               return NULL;
            } else {
               func->AddParam(node);
            }
            token = GetToken(text, token_val);
            if (token == T_END_LIST) {
               return func;
            } else if (token == T_NEXT_ELEMENT) {
               // get next list variable (token)
            } else {
               return NULL;
            }
         }
      }
   }
   return NULL;
}

cNode * cParse::ScanFunc(const char * func_name, const char * & text)
{
   string token_val;
   TToken token;
   cNode * func = new cNode();
   func->SetName(func_name);
   if ((token = GetToken(text, token_val)) != T_BEGIN_LIST) return NULL;
   while (true) {
      cNode * node = ScanFunc(text);
      if (node == NULL) {
         return NULL;
      } else {
         func->AddParam(node);
      }
      token = GetToken(text, token_val);
      if (token == T_END_LIST) {
         return func;
      } else if (token == T_NEXT_ELEMENT) {
         // get next list variable (token)
      } else {
         return NULL;
      }
   }
   return NULL;
}

cVariable * cParse::Variable()
{
   return _Variable;
}

const char * cParse::TokenName(TToken token)
{
   switch (token) {
   case T_UNDEF: return "T_UNDEF";
   case T_EOF: return "T_EOF";
   case T_BEGIN_LIST: return "T_BEGIN_LIST";
   case T_END_LIST: return "T_END_LIST";
   case T_NEXT_ELEMENT: return "T_NEXT_ELEMENT";
   case T_IDENTIFIER: return "T_IDENTIFIER";
   case T_PRECISION: return "T_PRECISION";
   case T_CONSTTEXT: return "T_CONSTTEXT";
   case T_INTVAL: return "T_INTVAL";
   case T_REGVAR: return "T_REGVAR";
   case T_IREGVAR: return "T_IREGVAR";
   case T_HEATVAR: return "T_HEATVAR";
   case T_TEXTVAR: return "T_TEXTVAR";
   case T_HEADERVAR: return "T_HEADERVAR";
   case T_FUNCTION: return "T_FUNCTION";
   default: return "T_UNKNOWN";
   }
}

TToken cParse::KeyWord(const char * token_val)
{
   if (strnicmp(token_val, "PREC", strlen("PREC")) == 0) return T_PRECISION;
   if (strnicmp(token_val, "REGVAR", strlen("REGVAR")) == 0) return T_REGVAR;
   if (strnicmp(token_val, "IREGVAR", strlen("IREGVAR")) == 0) return T_IREGVAR;
   if (strnicmp(token_val, "TEXTVAR", strlen("TEXTVAR")) == 0) return T_TEXTVAR;
   if (strnicmp(token_val, "HEATVAR", strlen("HEATVAR")) == 0) return T_HEATVAR;
   if (strnicmp(token_val, "HEADERVAR", strlen("HEADERVAR")) == 0) return T_HEADERVAR;
   FUNCTION_T func = FindFunction(token_val);
   if (func == NULL) {
      DebugPrintf("Unknown function %s in line %d\n", token_val, _Line);
   }
   return T_FUNCTION;
}

bool cParse::IsIntVal(const char * token_val)
{
   int len = strlen(token_val);
   for (int i=0; i<len; i++) {
      if (!isdigit(token_val[i])) return false;
   }
   return true;
}

TToken cParse::AnalyzeIdentifier(const char * token_val)
{
   if (IsIntVal(token_val)) return T_INTVAL;
   return KeyWord(token_val);
}

TToken cParse::GetConsttext(const char * & text, string & token)
{
   const char * text_ptr = text;
   char c_token[1024] = {0};
   char * dst_ptr = c_token;
   int i = 0;
   while (*text_ptr != 0) {
      if (*text_ptr == '"') {
         text = text_ptr + 1;
         token = c_token;
         return T_CONSTTEXT;
      }
      *dst_ptr = *text_ptr;
      dst_ptr++;
      text_ptr++;
      i++;
      if (i >= 1024) return T_UNDEF;
   }
   return T_UNDEF;
}

TToken cParse::GetToken(const char * & text, string & token)
{
   char c_token[1024] = {0};
   int token_size = 0;
   const char * ptr = text;
   char * dst_ptr = c_token;
   while (true) {
      switch (*ptr) {
      case ')':
         if (token_size > 0) {
            text = ptr;
            token = c_token;
            return AnalyzeIdentifier(c_token);
         } else {
            text = ptr + 1;
            token = ")";
            return T_END_LIST;
         }
      case '(':
         if (token_size > 0) {
            text = ptr;
            token = c_token;
            return AnalyzeIdentifier(c_token);
         } else {
            text = ptr + 1;
            token = "(";
            return T_BEGIN_LIST;
         }
      case ',':
         if (token_size > 0) {
            text = ptr;
            token = c_token;
            return AnalyzeIdentifier(c_token);
         } else {
            text = ptr + 1;
            token = ",";
            return T_NEXT_ELEMENT;
         }
      case '"':
         if (token_size > 0) {
            text = ptr;
            token = c_token;
            return T_UNDEF;
         } else {
            text = ptr + 1;
            return GetConsttext(text, token);
         }
      case ' ':
      case '\0':
         if (token_size > 0) {
            text = ptr + 1;
            token = c_token;
            return AnalyzeIdentifier(c_token);
         } else {
            if (*ptr == '\0') return T_EOF;
            ptr++;
         }
         break;
      default:
         *dst_ptr = *ptr;
         token_size++;
         ptr++;
         dst_ptr++;
         break;
      }
   }
}



