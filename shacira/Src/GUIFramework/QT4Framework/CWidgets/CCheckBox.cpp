
#include "CCheckBox.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget,
                   CCheckBox, \
                   ICON_SET("checkbox"), \
                   "check box widget")
#endif

CCheckBox::CCheckBox(QWidget * parent, const char * name)
#ifdef QT4
   : QCheckBox(parent),
#else
   : QCheckBox(parent, name),
#endif
     CWidgetBase(this),
     _Input(this)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _ButtonFuncRef = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _ValueFuncRef = 0;

   _BitPosValue = 0;
   _CheckedValueValue = 1;
   _UncheckedValueValue = 0;
   _ModeValue = SetNumericValue;

   _PrevValue = 0;
}

CCheckBox::~CCheckBox() 
{
}

void CCheckBox::keyReleaseEvent(QKeyEvent * e)
{
   if (HelpActive()) {
      return;
   }
   int key = e->key();
   e->ignore();
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (key == Qt::Key_Return || key == Qt::Key_Enter) {
      if (ExecuteButtonFunc(_ButtonFuncRef) == actionProceed) {
         QString new_value = NewValue();
         if (_Input.Update(new_value) == actionProceed) {
            ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_LIST_SELECTED);
            EmitGUISignal(new_signal);
         } else {
            ResetValue();
         }
      } else {
         ResetValue();
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CCheckBox::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
   }
}

void CCheckBox::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
      return;
   }
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (ExecuteButtonFunc(_ButtonFuncRef) == actionProceed) {
      QString new_value = NewValue();
      if (_Input.Update(new_value) == actionProceed) {
         ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_LIST_SELECTED);
         EmitGUISignal(new_signal);
      } else {
         ResetValue();
      }
   } else {
      ResetValue();
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CCheckBox::View()
{
}

// CCS related virtual methods

void CCheckBox::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_ButtonFuncSpec, _ButtonFuncRef);
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSCreateFuncRef(_ValueFuncSpec, _ValueFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   _Input.Set(_VarRef, _PlausFuncRef, _UserFuncRef);
WMETHOD_VOID_EPILOG
#endif
}

void CCheckBox::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString qValue = value;
   ULONG_T lval = qValue.toULong();
   SetValue(lval);
WMETHOD_VOID_EPILOG
#endif
}

void CCheckBox::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CCheckBox::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CCheckBox::ResetValue()
{
   SetValue(_PrevValue);
}

QString CCheckBox::NewValue()
{
   QString qValue = "";

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   LONG_T lval = _PrevValue;
   if (_ModeValue == SetNumericValue) {
      BOOL_T checked = (lval == _CheckedValueValue);
      if (checked) {
         // uncheck
         lval = _UncheckedValueValue;
      } else {
         // check
         lval = _CheckedValueValue;
      }
   } else if (_ModeValue == SetPattern) {
      BOOL_T checked = (lval & (1 << _BitPosValue));
      if (checked) {
         // uncheck
         lval = (lval & (~(1 << _BitPosValue)));
      } else {
         // check
         lval = (lval | (1 << _BitPosValue));
      }
   }

   qValue = qValue.setNum(lval);

WMETHOD_RC_EPILOG(qValue)
#endif
   return qValue;
}

void CCheckBox::SetValue(ULONG_T value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_ModeValue == SetNumericValue) {
      BOOL_T checked = ((LONG_T)value == _CheckedValueValue) ? true : false;
      if (checked) {
         setChecked(true);
      } else {
         setChecked(false);
      }
   } else if (_ModeValue == SetPattern) {
      BOOL_T checked = value & (1 << _BitPosValue);
      if (checked) {
         setChecked(true);
      } else {
         setChecked(false);
      }
   }
   _PrevValue = value;
WMETHOD_VOID_EPILOG
#endif
}



