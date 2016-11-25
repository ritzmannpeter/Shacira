
#include "CSpinBox.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CSpinBox, \
                   ICON_SET("spinbox"), \
                   "spin box widget")
#endif

CSpinBox::CSpinBox(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QSpinBox(parent),
#else
   : QSpinBox(parent, name),
#endif
     CWidgetBase(this) 
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _MinRef = NULL;
   _MinView = NULL;
   _MaxRef = NULL;
   _MaxView = NULL;

   _SetFuncRef = NULL;

   _ConstMinValue = 0;
   _ConstMaxValue = 0;
   _MaxIsSizeValue  = false;
   
   _Value = 0;
   _MinValue = 0;
   _MaxValue = 0;
   _TargetSize = 0;

   connect(this, SIGNAL(valueChanged(int)), this, SLOT(ValueChanged(int)));
}

CSpinBox::~CSpinBox() 
{
}

void CSpinBox::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QSpinBox::mousePressEvent(e);
   }
}

void CSpinBox::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QSpinBox::mouseReleaseEvent(e);
   }
}

void CSpinBox::paintEvent (QPaintEvent * e)
{
   QSpinBox::paintEvent(e);
}

void CSpinBox::ValueChanged(int value)
{
   if (value != _Value) {
      SetValue(value);
   }
}

// GUI related virtual methods

void CSpinBox::View()
{
}

// CCS related virtual methods

void CSpinBox::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _MinValue = _ConstMinValue;
   _MaxValue = _ConstMaxValue;
#ifdef QT4
   setMinimum(_MinValue);
   setMaximum(_MaxValue);
#else
   setMinValue(_MinValue);
   setMaxValue(_MaxValue);
#endif
   CCSCreateFuncRef(_SetFuncSpec, _SetFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   CCSInitializeVarRef(_MinSpec, _MinRef, _MinView, 1);
   CCSInitializeVarRef(_MaxSpec, _MaxRef, _MaxView, 2);
WMETHOD_VOID_EPILOG
#endif
}

void CSpinBox::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                             UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   LONG_T lval = atol(value);
   switch (id) {
   case 0:
      _Value = lval;
      break;
   case 1:
      _MinValue = lval;
      _TargetSize = _MaxValue - _MinValue;
      break;
   case 2:
      if (_MaxIsSizeValue) {
         _MaxValue = lval - 1;
      } else {
         _MaxValue = lval;
      };
      _TargetSize = _MaxValue - _MinValue;
      break;
   }
#ifdef QT4
   setMinimum(_MinValue);
   setMaximum(_MaxValue);
#else
   setMinValue(_MinValue);
   setMaxValue(_MaxValue);
#endif
   setValue(_Value);
WMETHOD_VOID_EPILOG
#endif
}

void CSpinBox::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CSpinBox::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CSpinBox::NextLine()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef QT4
   if (_Value < maximum()) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)(_Value + 1));
      }
   }
#else
   if (_Value < maxValue()) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)(_Value + 1));
      }
   }
#endif
WMETHOD_VOID_EPILOG
#endif
}

void CSpinBox::PrevLine()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Value > _MinValue) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)(_Value - 1));
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CSpinBox::SetValue(int value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef QT4
   if (value >= minimum() &&
       _Value <= maximum()) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)value);
      }
   }
#else
   if (value >= minValue() &&
       _Value <= maxValue()) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)value);
      }
   }
#endif
WMETHOD_VOID_EPILOG
#endif
}
