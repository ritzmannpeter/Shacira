
#ifndef _cProcessWrapper_h
#define _cProcessWrapper_h

class cSHClientProcess;
class cContext;

class cProcessWrapper
{
public:
   cProcessWrapper();
   virtual ~cProcessWrapper();
   static void Start();
   static void Stop();
   static int cProcessWrapper::_Argc;
   static char ** cProcessWrapper::_Argv;
   static cProcessWrapper * instance() {return _ProcessWrapper;};
   bool Eval(const char * text, STRING_T & value);
   bool GetImage(const char * text, unsigned char * & buf, int & buf_size);
private:
   STRING_T SetContext(const char * context_name);
   STRING_T ActiveContext();
   STRING_T ListVariables();
   BOOL_T SetVarCmd(const char * line, STRING_T & var_spec, STRING_T & var_value);
   BOOL_T GetVarCmd(const char * line, STRING_T & var_spec);
   STRING_T SetVar(const char * var_spec, const char * value);
   STRING_T GetVar(const char * var_spec);
   BOOL_T IsEmpty(const char * text);
   BOOL_T ContextIsNull();

private:
   static cProcessWrapper * _ProcessWrapper;
   cSHClientProcess * _Process;
   cContext * _ActiveContext;
   STRING_T _ActiveContextName;
};

#define PWrapper() cProcessWrapper::instance()

#endif
