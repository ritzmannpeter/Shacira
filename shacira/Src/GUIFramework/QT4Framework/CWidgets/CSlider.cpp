
#include "CSlider.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CSlider, \
                   ICON_SET("slider"), \
                   "slider widget")
#endif

CSlider::CSlider(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QSlider(parent),
#else
   : QSlider(parent, name),
#endif
     CWidgetBase(this) 
{
#ifdef QT4
   setObjectName(name);
   setWindowFlags(f);
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
   _sliderValueChangedDelay = 0;
   _sliderActive = false;

   connect(this, SIGNAL(valueChanged(int)), this, SLOT(ValueChanged(int)));
   connect(this, SIGNAL(sliderPressed()), this, SLOT(SliderPressed()));
   connect(this, SIGNAL(sliderReleased()), this, SLOT(SliderReleased()));
}

CSlider::~CSlider() 
{
}

void CSlider::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QSlider::mousePressEvent(e);
   }
}

void CSlider::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QSlider::mouseReleaseEvent(e);
   }
}

void CSlider::paintEvent (QPaintEvent * e)
{
   QSlider::paintEvent(e);
}

void CSlider::ValueChanged(int value)
{ 
   int maxDiff10 = maximum() / 10;

   if (maxDiff10)
      _sliderValueChangedDelay++;

   if (_sliderActive && (_sliderValueChangedDelay < maxDiff10))
       return;

   if (value != _Value) {
      _sliderValueChangedDelay = 0;
      SetValue(value);
   }
}

void CSlider::SliderPressed()
{
   _sliderActive = true;
}

void CSlider::SliderReleased()
{
   _sliderActive = false;
   ValueChanged(value());
}

// GUI related virtual methods

void CSlider::View()
{
}

void CSlider::Setup()
{
    emit SetupSignal(reinterpret_cast<QWidget*>(this));
}


// CCS related virtual methods

void CSlider::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
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

void CSlider::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                             UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   LONG_T lval = atol(value);
   switch (id) {
   case 0:
      _Value = lval;
      setValue(_Value);
      break;
   case 1:
      _MinValue = lval;
      _TargetSize = _MaxValue - _MinValue;
#ifdef QT4
      setMinimum(_MinValue);
#else
      setMinValue(_MinValue);
#endif
      break;
   case 2:
      if (_MaxIsSizeValue) {
         _MaxValue = lval - 1;
      } else {
         _MaxValue = lval;
      };
      _TargetSize = _MaxValue - _MinValue;
#ifdef QT4
      setMaximum(_MaxValue);
#else
      setMaxValue(_MaxValue);
#endif
      break;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CSlider::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CSlider::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CSlider::SetValue(int value)
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
