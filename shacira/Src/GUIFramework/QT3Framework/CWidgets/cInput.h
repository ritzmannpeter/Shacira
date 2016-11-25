
#ifndef _cinput_h_
#define _cinput_h_

#include "CWidgetBase.h"
class iFinalValidator;
class cQtNumberValidator;
class cQtStringValidator;
#include <qvalidator.h>

class SH_QT_WIDGET_PLUGIN_EXPORT cInput
{
public:
   cInput();
   cInput(CWidgetBase * widget_base);
   virtual ~cInput();
public:
   void Set(VAR_REF_PTR var_ref, FUNC_REF_PTR plaus_func_ref, FUNC_REF_PTR user_func_ref);
   void SetVarRef(VAR_REF_PTR var_ref);
   void SetPlausFuncRef(FUNC_REF_PTR plaus_func_ref);
   void SetUserFuncRef(FUNC_REF_PTR user_func_ref);
   VAR_REF_PTR VarRef() {return _VarRef;};
   ULONG_T Update(const QString & value);
   ULONG_T Update(const QString & value, QString & message);
   QValidator * SyntaxValidator();
   iFinalValidator * FinalValidator();
   QString Minimum();
   QString Maximum();
   BOOL_T IsNumeric();
private:
   CWidgetBase * _BaseWidget;
   QString _Minimum;
   QString _Maximum;
   UCHAR_T _DataType;
   UCHAR_T _Precision;
   VAR_REF_PTR _VarRef;
   FUNC_REF_PTR _PlausFuncRef;
   FUNC_REF_PTR _UserFuncRef;
   cQtNumberValidator * _NumberValidator;
   cQtStringValidator * _StringValidator;
   BOOL_T _IsNumericInput;
private:
   void CheckMin(const QString & value);
   void CheckMax(const QString & value);
};

#endif


