
/// PR 13.05.05 - selected exception propagation in CCSSetValue
/// PR 28.06.05 - input number validation can be switched off now
/// PR 30.06.05 - removed bug when getting min and max values
///               when input number validation is switched off
/// PR 23.01.06 - removed initial setting of minimum and maximum

#include "cInput.h"

#ifndef QT_PLUGIN
#include "cQtKeyboardInput.h"
#include "cQtNumberValidator.h"
#include "cQtStringValidator.h"

class cFinalValidator : public iFinalValidator
{
public:
   cFinalValidator(cInput * input) {_Input = input;};
   virtual ~cFinalValidator() {};
private:
   cInput * _Input;
   virtual bool check(const QString &input, QString &error) const
   {
      return (_Input->Update(input, error) == actionProceed);
   };
};

#else

class cFinalValidator;

#endif


cInput::cInput()
{
   _BaseWidget = NULL;
   _VarRef = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _DataType = 0;
   _IsNumericInput = false;
   _Precision = 0;
   _NumberValidator = NULL;
   _StringValidator = NULL;
}

cInput::cInput(CWidgetBase * base_widget)
{
   _BaseWidget = base_widget;
   _VarRef = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _DataType = 0;
   _IsNumericInput = false;
   _Precision = 0;
   _NumberValidator = NULL;
   _StringValidator = NULL;
}

cInput::~cInput()
{
#ifndef QT_PLUGIN
   if (_NumberValidator != NULL) {
      delete _NumberValidator;
   }
   if (_StringValidator != NULL) {
      delete _StringValidator;
   }
#endif
}

void cInput::SetVarRef(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
   _VarRef = var_ref;
   if (_VarRef == NULL) {
      _Minimum = "";
      _Maximum = "";
      _DataType = 0;
      _IsNumericInput = false;
      _Precision = 0;
   } else {
      _DataType = _VarRef->DataType();
      if (IS_NUMBER(_DataType)) {
         _IsNumericInput = true;
      }
      _Precision = _VarRef->Precision();
   }
#endif
}

void cInput::Set(VAR_REF_PTR var_ref, FUNC_REF_PTR plaus_func_ref, FUNC_REF_PTR user_func_ref)
{
#ifndef QT_PLUGIN
   SetVarRef(var_ref);
   SetPlausFuncRef(plaus_func_ref);
   SetUserFuncRef(user_func_ref);
#endif
}

void cInput::SetPlausFuncRef(FUNC_REF_PTR plaus_func_ref)
{
   _PlausFuncRef = plaus_func_ref;
}

void cInput::SetUserFuncRef(FUNC_REF_PTR user_func_ref)
{
   _UserFuncRef = user_func_ref;
}

ULONG_T cInput::Update(const QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_BaseWidget == NULL) {
      _BaseWidget->DisplayError("base widget not initialized in input");
      return actionReject;
   }
   if (_VarRef == NULL) {
      _BaseWidget->DisplayError("variable reference not initialized in input");
      return actionReject;
   }
   try {
      CheckMin(value);
      CheckMax(value);
      ULONG_T rc = _BaseWidget->ExecutePlausFunc(_PlausFuncRef, value);
      if (rc == actionProceed) {
         rc = _BaseWidget->ExecuteUserFunc(_UserFuncRef, value);
         if (rc == actionProceed) {
            /// PR 13.05.05 now exception propagation is selected 
            QString set_value = value;
            if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
               if (!_IsNumericInput) {
                  set_value = value.utf8();
               }
            }
            if (_BaseWidget->CCSSetValue(_VarRef, CONST_STRING(set_value), true)) {
               STRING_T read_value;
               if (_BaseWidget->CCSGetValue(_VarRef, read_value)) {
                  return actionProceed;
               } else {
                  return actionReject;
               }
            }
         } else if (rc == actionIgnore) {
            return actionProceed;
         } else {
            return actionReject;
         }
      } else if (rc == actionIgnore) {
         return actionProceed;
      } else {
         return actionReject;
      }
   } catch (cError & e) {
      //_BaseWidget->DisplayError(e.ErrMsg().c_str()); // 210305 HA
      _BaseWidget->DisplayError(cText::GetText(e).c_str(), e.get_Param1().c_str(),
                                e.get_Param2().c_str(), e.get_Param3().c_str(), e.get_Param4().c_str());
   } catch (...) {
      _BaseWidget->DisplayError("nicht behandelte Ausnahme");
   }
   return actionReject;
WMETHOD_RC_EPILOG(actionReject)
#endif
   return actionReject;
}

ULONG_T cInput::Update(const QString & value, QString & message)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_BaseWidget == NULL) {
      message = "base widget not initialized in input";
      return actionReject;
   }
   if (_VarRef == NULL) {
      message = "variable reference not initialized in input";
      return actionReject;
   }
   try {
      CheckMin(value);
      CheckMax(value);
      ULONG_T rc = _BaseWidget->ExecutePlausFunc(_PlausFuncRef, value);
      if (rc == actionProceed) {
         rc = _BaseWidget->ExecuteUserFunc(_UserFuncRef, value);
         if (rc == actionProceed) {
            /// PR 13.05.05 now exception propagation is selected 
            QString set_value = value;
            if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
               if (!_IsNumericInput) {
                  set_value = value.utf8();
               }
            }
            if (_BaseWidget->CCSSetValue(_VarRef, CONST_STRING(set_value), true)) {
               STRING_T read_value;
               if (_BaseWidget->CCSGetValue(_VarRef, read_value)) {
                  return actionProceed;
               } else {
                  return actionReject;
               }
            }
         } else if (rc == actionIgnore) {
            return actionProceed;
         } else {
            return actionReject;
         }
      } else if (rc == actionIgnore) {
         return actionProceed;
      } else {
         return actionReject;
      }
   } catch (cError & e) {
      message = CWidgetBase::Translate(cText::GetText(e).c_str(),
                                       cText::Context(-(e.get_ErrCode ())),
                                       e.get_Param1().c_str(),
                                       e.get_Param2().c_str(),
                                       e.get_Param3().c_str(),
                                       e.get_Param4().c_str());
      //message = e.ErrMsg().c_str(); 210305 HA
   } catch (...) {
      message = "nicht behandelte Ausnahme";
   }
WMETHOD_RC_EPILOG(actionReject)
#endif
   return actionReject;
}

QValidator * cInput::SyntaxValidator()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_DataType == SH_BYTE ||
       _DataType == SH_OBJECT) {
      return NULL;
   } else if (_DataType == SH_STRING ||
              _DataType == SH_WSTRING) {
      if (_StringValidator == NULL) {
         ULONG_T len = _VarRef->ValueSize();
         _StringValidator = new cQtStringValidator(len, NULL);
      }
      return _StringValidator;
   } else {
      if (_VarRef == NULL) {
         return NULL;
      } else {
         try {
            if (CWidgetBase::Flag(IGNORE_NUMBER_VALIDATION)) {
               return NULL;
            } else {
               if (_NumberValidator == NULL) {
                  if (CWidgetBase::Flag(IGNORE_NUMBER_VALIDATION)) {
                     return NULL;
                  }
                  STRING_T minimum;
                  STRING_T maximum;
                  _VarRef->GetMinimum(minimum);
                  _VarRef->GetMaximum(maximum);
                  _Precision = _VarRef->Precision();
                  _Minimum = minimum.c_str();
                  _Maximum = maximum.c_str();
                  DOUBLE_T min = _Minimum.toDouble();
                  DOUBLE_T max = _Maximum.toDouble();
                  _NumberValidator = new cQtNumberValidator(min, max, _Precision, NULL);
               }
               return _NumberValidator;
            }
         } catch (cError & e) {
            _BaseWidget->DisplayError(e.ErrMsg().c_str());
            return NULL;
         } catch (...) {
            _BaseWidget->DisplayError("unhandled exception ");
            return NULL;
         }
      }
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

iFinalValidator * cInput::FinalValidator()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
if (_VarRef == NULL) {
   return NULL;
} else {
   return new cFinalValidator(this);
}
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

QString cInput::Minimum()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_DataType == SH_BYTE ||
       _DataType == SH_OBJECT ||
       _DataType == SH_STRING ||
       _DataType == SH_WSTRING ||
       _VarRef == NULL) {
      return "";
   }   
   STRING_T minimum;
   _VarRef->GetMinimum(minimum);
   _Minimum = minimum.c_str();
   return _Minimum;
WMETHOD_RC_EPILOG("")
#endif
   return "";
};

QString cInput::Maximum()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_DataType == SH_BYTE ||
       _DataType == SH_OBJECT ||
       _DataType == SH_STRING ||
       _DataType == SH_WSTRING ||
       _VarRef == NULL) {
      return "";
   }
   STRING_T maximum;
   _VarRef->GetMaximum(maximum);
   _Maximum = maximum.c_str();
   return _Maximum;
WMETHOD_RC_EPILOG("")
#endif
   return "";
};

void cInput::CheckMin(const QString & value)
{
#ifndef QT_PLUGIN
   if (_DataType == SH_BYTE ||
       _DataType == SH_OBJECT ||
       _DataType == SH_STRING ||
       _DataType == SH_WSTRING ||
       _VarRef == NULL) {
      return;
   }   
   STRING_T minimum;
   _VarRef->GetMinimum(minimum);
   _Minimum = minimum.c_str();
   if (_Minimum.length() > 0) {
      DOUBLE_T min = _Minimum.toDouble();
      _Precision = _VarRef->Precision();
      if (_NumberValidator != NULL) {
         _NumberValidator->setBottom(min);
         _NumberValidator->setDecimals(_Precision);
      }
      DOUBLE_T val = value.toDouble();
      if (val < min) {
         throw cError(ERR_MIN_VALUE, 0, CONST_STRING(_Minimum));
      }
   }
#endif
}

void cInput::CheckMax(const QString & value)
{
#ifndef QT_PLUGIN
   if (_DataType == SH_BYTE ||
       _DataType == SH_OBJECT ||
       _DataType == SH_STRING ||
       _DataType == SH_WSTRING ||
       _VarRef == NULL) {
      return;
   }   
   STRING_T maximum;
   _VarRef->GetMaximum(maximum);
   _Maximum = maximum.c_str();
   if (_Maximum.length() > 0) {
      DOUBLE_T max = _Maximum.toDouble();
      _Precision = _VarRef->Precision();
      if (_NumberValidator != NULL) {
         _NumberValidator->setTop(max);
         _NumberValidator->setDecimals(_Precision);
      }
      DOUBLE_T val = atof(CONST_STRING(value));
      if (val > max) {
         throw cError(ERR_MAX_VALUE, 0, CONST_STRING(_Maximum));
      }
   }
#endif
}

BOOL_T cInput::IsNumeric()
{
   return _IsNumericInput;
}
