
#include "cVariables.h"
#include "cParse.h"
#include "cChapter.hpp"
#include "FMFATFile.h"

/* Variable
 */

cVariable::cVariable(cVariables * variables) :
   _Variables(variables), _Prec(NULL), _Func(NULL)
{
}

cVariable::~cVariable()
{
}

void cVariable::SetName(const char * name)
{
   _Name = name;
}

string cVariable::Name()
{
   return _Name;
}

void cVariable::SetPrec(cNode * prec)
{
   _Prec = prec;
}

void cVariable::SetFunc(cNode * func)
{
   _Func = func;
}

void cVariable::SetUnit(const char * unit)
{
   _Unit = unit;
}

long cVariable::Value()
{
   return _Value;
}

/* Regvar
 */

cRegvar::cRegvar(cVariables * variables, cNode * reg_no) :
   cVariable(variables), _RegNo(reg_no), _Index(NULL)
{
}

cRegvar::cRegvar(cVariables * variables, cNode * reg_no, cNode * index) :
   cVariable(variables), _RegNo(reg_no), _Index(index)
{
}

cRegvar::~cRegvar()
{
}

static void InsertDecimalPoint(char * value, int precision, int bufsize)
{
   int len = strlen(value);
   int pos = (len - precision);
   int right_shift;
   if (pos > 0) {
      right_shift = 1;
      if (right_shift >= (bufsize - len - 1)) {
         strcpy(value, "E_PRECISION");
         return;
      }
      for (int i=len; i>=pos; i--) {
         value[i+1] = value[i];
      }
      value[pos] = '.';
   } else {
      right_shift = -(pos) + 2;
      if (right_shift >= (bufsize - len - 1)) {
         strcpy(value, "E_PRECISION");
         return;
      }
      for (int i=len; i>=0; i--) {
         value[i+right_shift] = value[i];
      }
      value[0] = '0';
      value[1] = '.';
      for (int i=2; i<right_shift; i++) {
         value[i] = '0';
      }
   }
}

int cRegvar::GetValue(string & value)
{
   FMFAT_BUFFER_T * fmfat_buf = (FMFAT_BUFFER_T*)_Variables->Buffer();
   if (fmfat_buf != NULL) {
      int err;
      long l_value = 0;
      if (_Index == 0) {
         err = fmfat_buf->GetRegVal(fmfat_buf, _RegNo->IntVal(), &l_value);
      } else {
         err = fmfat_buf->GetRegValI(fmfat_buf, _RegNo->IntVal(), _Index->IntVal(), &l_value);
      }
      _Value = l_value;
      if (_Func != NULL) {
         l_value = _Value = _Func->IntVal(this);
      }
      char _value[32] = {0};
      if (err == 0) {
         if (_Prec != NULL) {
            int precision = _Prec->IntVal();
            ltoa(l_value, _value, 10);
            if (precision > 0) {
               InsertDecimalPoint(_value, precision, sizeof(_value));
            }
         } else {
            ltoa(l_value, _value, 10);
         }
         value = _value;
         return 0;
      } else {
         ltoa(err, _value, 10);
         value = "error ";
         value += _value;
         return err;
      }
   }
   value = "unknown";
   return 0;
}


/* Textvar
 */

cTextvar::cTextvar(cVariables * variables, cNode * text_id, cNode * row) :
   cVariable(variables), _TextId(text_id), _Row(row)
{
}

cTextvar::~cTextvar()
{
}

int cTextvar::GetValue(string & value)
{
   FMFAT_BUFFER_T * fmfat_buf = (FMFAT_BUFFER_T*)_Variables->Buffer();
   if (fmfat_buf != NULL) {
      int err;
      char buffer[256] = {0};
      err = fmfat_buf->GetTextRow(fmfat_buf, _TextId->IntVal(), _Row->IntVal(),
                                  buffer, sizeof(buffer));
      char _value[32] = {0};
      if (err > 0) {
         value = buffer;
         return 0;
      } else {
         ltoa(err, _value, 10);
         value = "error ";
         value += _value;
         return err;
      }
   }
   value = "unknown";
   return 0;
}

/* Heatvar
 */

cHeatvar::cHeatvar(cVariables * variables,
            cNode * group,
            cNode * zone,
            cNode * unit,
            cNode * param) :
   cVariable(variables), _Group(group), _Zone(zone), _Unit(unit), _Param(param)
{
}

cHeatvar::~cHeatvar()
{
}

int cHeatvar::GetValue(string & value)
{
   FMFAT_BUFFER_T * fmfat_buf = (FMFAT_BUFFER_T*)_Variables->Buffer();
   if (fmfat_buf != NULL) {
      int err;
      long l_value;
      err = fmfat_buf->GetHeatParam(fmfat_buf,
                                    _Group->IntVal(),
                                    _Zone->IntVal(),
                                    _Unit->IntVal(),
                                    _Param->IntVal(),
                                    &l_value);
      _Value = l_value;
      if (_Func != NULL) {
         l_value = _Value = _Func->IntVal(this);
      }
      char _value[32] = {0};
      if (err == 0) {
         if (_Prec != NULL) {
            int precision = _Prec->IntVal();
            ltoa(l_value, _value, 10);
            if (precision > 0) {
               InsertDecimalPoint(_value, precision, sizeof(_value));
            }
         } else {
            ltoa(l_value, _value, 10);
         }
         value = _value;
         return 0;
      } else {
         ltoa(err, _value, 10);
         value = "error ";
         value += _value;
         return err;
      }
   }
   value = "unknown";
   return 0;
}

/* Variables
 */

cVariables::cVariables(const char * file, void * buffer) :
   _Buffer(buffer)
{
   int line = 0;
   cChapter config(file, "system");
   cChapter * variables = config.getChapter("variables");
   cChapter::ITERATOR variable_iterator;
   if (variables != NULL) {
      variables->resetKeyList(variable_iterator);
      const char * key;
      while ((key = variables->getNextKey(variable_iterator)) != NULL) {
         string spec = variables->getStringValue(key, "");
         char text[4096] = {0};
         strcpy(text, spec.c_str());
         cParse entry = cParse(this, text, line);
         cVariable * variable = entry.Variable();
         if (variable != NULL) {
            variable->SetName(key);
            AddVariable(variable);
         }
      }
      line++;
   }
}

cVariables::~cVariables()
{
   VARIABLE_MAP_T::iterator i = _VariableMap.begin();
   while (i != _VariableMap.end()) {
      cVariable * variable = (*i).second;
      delete variable;
      i++;
   }
}

void cVariables::AddVariable(cVariable * variable)
{
   string name = variable->Name();
   _VariableMap[name] = variable;
}

VARIABLE_MAP_T & cVariables::VariableMap()
{
   return _VariableMap;
}

cVariable * cVariables::Variable(const char * name)
{
   return _VariableMap[name];   
}

int cVariables::VariableCount()
{
   return _VariableMap.size();
}

void cVariables::SetBuffer(void * buffer)
{
   _Buffer = buffer;
}

void * cVariables::Buffer()
{
   return _Buffer;
}

int cVariables::GetValue(const char * name, string & value)
{
   value = "unknown variable";
   cVariable * variable = _VariableMap[name];
   if (variable != NULL) {
      return variable->GetValue(value);
   }
   return 0;
}



