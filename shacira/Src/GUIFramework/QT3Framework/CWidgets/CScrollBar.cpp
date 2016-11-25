
#include "CScrollBar.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ViewWidget, \
                   CScrollBar, \
                   ICON_SET("designer_scrollbar"), \
                   "scroll bar widget")
#endif

CScrollBar::CScrollBar(QWidget * parent, const char * name, WFlags f)
   : QScrollBar(parent, name),
     CWidgetBase(this) 
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _MinRef = NULL;
   _MinView = NULL;
   _MaxRef = NULL;
   _MaxView = NULL;

   _UpFuncRef = NULL;
   _DownFuncRef = NULL;
   _SetFuncRef = NULL;

   _ContainerSizeValue = 0;
   _ConstMinValue = 0;
   _ConstMaxValue = 0;
   _MaxIsSizeValue  = false;

   _Value = 0;
   _MinValue = 0;
   _MaxValue = 0;
   _TargetSize = -1;

   connect(this, SIGNAL(nextLine()), this, SLOT(NextLineRequested()));
   connect(this, SIGNAL(prevLine()), this, SLOT(PrevLineRequested()));
   connect(this, SIGNAL(valueChanged(int)), this, SLOT(ValueChanged(int)));
}

CScrollBar::~CScrollBar() 
{
}

void CScrollBar::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QScrollBar::mousePressEvent(e);
   }
}

void CScrollBar::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QScrollBar::mouseReleaseEvent(e);
   }
}

void CScrollBar::paintEvent (QPaintEvent * e)
{
   QScrollBar::paintEvent(e);
}

void CScrollBar::ValueChanged(int value)
{
   if (value != _Value) {
      SetValue(value);
   }
}

// GUI related virtual methods

void CScrollBar::View()
{
   if (_TargetSize > 0) { // min/max new values are received
       if (_TargetSize > _ContainerSizeValue) {
          show();
       } else {
          hide();
       }
   }
}

// CCS related virtual methods

void CScrollBar::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _MinValue = _ConstMinValue;
   _MaxValue = _ConstMaxValue;
   setMinValue(_MinValue);
   setMaxValue((_MaxValue < _ContainerSizeValue) ? _MaxValue : _MaxValue - _ContainerSizeValue);
   setValue(_Value);
   CCSCreateFuncRef(_UpFuncSpec, _UpFuncRef);
   CCSCreateFuncRef(_DownFuncSpec, _DownFuncRef);
   CCSCreateFuncRef(_SetFuncSpec, _SetFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   CCSInitializeVarRef(_MinSpec, _MinRef, _MinView, 1);
   CCSInitializeVarRef(_MaxSpec, _MaxRef, _MaxView, 2);
WMETHOD_VOID_EPILOG
#endif
}

void CScrollBar::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
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
      setMinValue(_MinValue);
      View();
      break;
   case 2:
      if (_MaxIsSizeValue) {
         _MaxValue = lval - 1;
      } else {
         _MaxValue = lval;
      };
      _TargetSize = _MaxValue - _MinValue;
      LONG_T maxValue = _MaxValue;
      
      if (_MaxValue >= _ContainerSizeValue) {
          LONG_T containerSize = (_TargetSize < _ContainerSizeValue) ? _TargetSize : _ContainerSizeValue;
          maxValue = _MaxValue - containerSize;
      }

      setMaxValue(maxValue);
      View();
      break;
   }

WMETHOD_VOID_EPILOG
#endif
}

void CScrollBar::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CScrollBar::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CScrollBar::NextLine()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Value < maxValue()) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)(_Value + 1));
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CScrollBar::PrevLine()
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

void CScrollBar::SetValue(int value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (value >= minValue() &&
       _Value <= maxValue()) {
      if (_VarRef != NULL) {
         _VarRef->SetValue((LONG_T)value);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}
