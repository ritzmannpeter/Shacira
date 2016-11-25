//---------------------------------------------------------------------------
#ifndef cParseH
#define cParseH
//---------------------------------------------------------------------------

#include <string>
#include <list>
using namespace std;
#include "cVariables.h"

typedef enum {T_UNDEF,
              T_EOF,
              T_BEGIN_LIST,
              T_END_LIST,
              T_NEXT_ELEMENT,
              T_IDENTIFIER,
              T_PRECISION,
              T_CONSTTEXT,
              T_INTVAL,
              T_REGVAR,
              T_IREGVAR,
              T_HEATVAR,
              T_TEXTVAR,
              T_HEADERVAR,
              T_FUNCTION} TToken;

class cNode
{
public:
   enum TNodeType {T_UNDEF,
                   T_CONSTTEXT,
                   T_INTVAL,
                   T_FUNCTION};
private:
   string _FuncName;
   list<cNode*> _Params;
   string _ConstText;
   int _IntVal;
   TNodeType _Type;
   int CallFunction(cVariable * variable, const char * name, int argc, int * argi);
public:
   cNode();
   cNode(int intval);
   cNode(const char * consttext);
   cNode(cNode * node);
   virtual ~cNode();
   void SetName(const char * name);
   void AddParam(cNode * param);
   int IntVal(cVariable * variable = NULL);
   string ConstText();
   string FuncName();
};

class cParse
{
private:
   int _Line;
   cVariables * _Variables;
   cVariable * _Variable;
public:
   cParse(cVariables * variables, const char * & text, int line);
   virtual ~cParse();
   bool Parse(const char * & text);
   cRegvar * ScanRegvar(const char * & text);
   cRegvar * ScanIRegvar(const char * & text);
   cTextvar * ScanTextvar(const char * & text);
   cHeatvar * ScanHeatvar(const char * & text);
   cHeadervar * ScanHeadervar(const char * & text);
   cNode * ScanFunc(const char * & text);
   cNode * ScanFunc(const char * func_name, const char * & text);
   cNode * ScanValue(const char * & text);
   cVariable * Variable();
   const char * TokenName(TToken token);
   TToken KeyWord(const char * token_val);
   bool IsIntVal(const char * token_val);
   TToken AnalyzeIdentifier(const char * token_val);
   TToken GetConsttext(const char * & text, string & token);
   TToken GetToken(const char * & text, string & token);
};

#endif
