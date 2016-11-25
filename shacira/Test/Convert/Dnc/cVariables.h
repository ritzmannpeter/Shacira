//---------------------------------------------------------------------------
#ifndef cVariablesH
#define cVariablesH
//---------------------------------------------------------------------------

#include <string>
#include <map>
using namespace std;

class cNode;
class cVariables;

class cVariable
{
public:
   enum TVariableType {T_TEXT, T_REGVAR, T_HEATVAR, T_HEADER};
protected:
   TVariableType _Type;
   cVariables * _Variables;
   string _Name;
   string _Unit;
   cNode * _Prec;
   cNode * _Func;
   long _Value;
public:
	cVariable(cVariables * variables);
	virtual ~cVariable();
   virtual int GetValue(string & value) = 0;
   long Value();
   string Name();
   string Unit();
   void SetPrec(cNode * prec);
   void SetFunc(cNode * prec);
   void SetUnit(const char * unit);
   void SetName(const char * name);
};

class cTextvar : public cVariable
{
private:
   cNode * _TextId;
   cNode * _Row;
public:
	cTextvar(cVariables * variables, cNode * text_id, cNode * row);
	virtual ~cTextvar();
   int GetValue(string & value);
};

class cRegvar : public cVariable
{
private:
   cNode * _RegNo;
   cNode * _Index;
public:
	cRegvar(cVariables * variables, cNode * reg_no);
	cRegvar(cVariables * variables, cNode * reg_no, cNode * index);
	virtual ~cRegvar();
   int GetValue(string & value);
};

class cHeatvar : public cVariable
{
private:
   cNode * _Group;
   cNode * _Zone;
   cNode * _Unit;
   cNode * _Param;
public:
	cHeatvar(cVariables * variables,
            cNode * group,
            cNode * zone,
            cNode * unit,
            cNode * param);
	virtual ~cHeatvar();
   int GetValue(string & value);
};

class cHeadervar : public cVariable
{
public:
	cHeadervar(cVariables * variables);
	virtual ~cHeadervar();
   int GetValue(string & value);
};

typedef map<string, cVariable*> VARIABLE_MAP_T;

class cVariables
{
private:
   VARIABLE_MAP_T _VariableMap;
   void * _Buffer;
public:
   cVariables(const char * file, void * buffer = NULL);
	virtual ~cVariables();
   void AddVariable(cVariable * variable);
   VARIABLE_MAP_T & VariableMap();
   int VariableCount();
   cVariable * Variable(const char * name);
   void SetBuffer(void * buffer);
   void * Buffer();
   int GetValue(const char * name, string & value);
};

#endif
