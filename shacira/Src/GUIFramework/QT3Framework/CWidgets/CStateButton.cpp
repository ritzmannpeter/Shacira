
/// PR 12.05.05 - determining new value to set before button function is executed

#include "CStateButton.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ButtonWidget, \
                   CStateButton, \
                   ICON_SET("designer_toolbutton"), \
                   "tool button widget, that can reflect state")
#endif

#include "CAppFrame.h"

CStateButton::CStateButton(QWidget * parent, const char * name)
   : QToolButton(parent, name),
     CWidgetBase(this),
     _Input(this), _ActIndex(0), _PrevIndex(0)
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _ButtonFuncRef = NULL;
   _ValueFuncRef = NULL;
   _ModeValue = ShowNext;
   _StateCountValue = 2;
   _State0ValueValue = 0;
   _State1ValueValue = 0;
   _State2ValueValue = 0;
   _State3ValueValue = 0;
   _State4ValueValue = 0;
   _ButtonStyleValue = QtSpecific;
   _ExecModeValue = Sync;
   _PreExecFuncRef = NULL;
   _ShowVarRef = NULL;
   _ShowVarView = NULL;
   _Show2VarRef = NULL;
   _Show2VarView = NULL;
   _ActShowVarRefValue = 0;
   _ActShow2VarRefValue = 0;
   _MouseKeyEnableValue = true;
   _DisableParentValue = false;

   setUsesBigPixmap(true);
}

CStateButton::~CStateButton() 
{
}

void CStateButton::mousePressEvent(QMouseEvent * e)
{
   if (!_MouseKeyEnableValue) 
      return;

   if (!HelpActive()) {
      if (!Flag(NON_STANDARD_BUTTONS)) {
         if (_ButtonStyleValue == QtSpecific) {
            QToolButton::mousePressEvent(e);
         }
      }
   }
}

void CStateButton::mouseReleaseEvent(QMouseEvent * e)
{
   if (!_MouseKeyEnableValue) 
      return;

   if (HelpActive()) {
      SetHelpIds();
   } else {
      if (!Flag(NON_STANDARD_BUTTONS)) {
         if (_ButtonStyleValue == QtSpecific) {
            QToolButton::mouseReleaseEvent(e);
         }
      }
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      EmitGUISignal(SIG_BUTTON_CLICKED);
      BOOL_T sync = (_ExecModeValue == Sync) ? true : false;
      QWidget * parent = NULL;
      if (_DisableParentValue && sync) {
         parent = parentWidget();
         if (parent->inherits("CPage")) {
            ErrorPrintf("Property DisableParent for parent CPage not possible (Widget %s)\n", CONST_STRING(this->name()));
            parent = NULL;
         }
         else {
            parent->setEnabled(false);
            qApp->processEvents();
         }
      }

      QString new_value = NewValue();
      ULONG_T rc = ExecuteButtonFuncs(_PreExecFuncRef, _ButtonFuncRef, sync, _ActionDialogValue, 0);
      if ( rc == actionProceed) {
         if (_VarRef == NULL) {
            ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_STATE_CHANGED);
            EmitGUISignal(new_signal);
            emit stateChanged(new_value.toInt());
         } else {
            if (_Input.Update(new_value) == actionProceed) {
               ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_STATE_CHANGED);
               EmitGUISignal(new_signal);
               emit stateChanged(new_value.toInt());
            } else {
               ResetValue();
            }
         }
      } else {
         ResetValue();
      }
      emit ButtonFunctionExecuted(rc); // HA210605

      if (_DisableParentValue && sync && parent) {
         qApp->processEvents();
         parent->setEnabled(true);
      }
WMETHOD_VOID_EPILOG
#endif
   }
}

void CStateButton::keyReleaseEvent(QKeyEvent * e)
{
   if (!_MouseKeyEnableValue) 
      return;

   int key = e->key();
   e->ignore();
   QToolButton::keyReleaseEvent (e);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (key == Qt::Key_Return || key == Qt::Key_Enter) {
      EmitGUISignal(SIG_BUTTON_CLICKED);
      BOOL_T sync = (_ExecModeValue == Sync) ? true : false;
      QWidget * parent = NULL;
      if (_DisableParentValue && sync) {
         parent = parentWidget();
         if (parent->inherits("CPage")) {
            ErrorPrintf("Property DisableParent for parent CPage not possible (Widget %s)\n", CONST_STRING(this->name()));
            parent = NULL;
         }
         else {
            parent->setEnabled(false);
            qApp->processEvents();
         }
      }

      QString new_value = NewValue();
      ULONG_T rc = ExecuteButtonFuncs(_PreExecFuncRef, _ButtonFuncRef, sync, _ActionDialogValue, 0);
      if (rc == actionProceed) {
         if (_VarRef == NULL) {
            ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_STATE_CHANGED);
            EmitGUISignal(new_signal);
            emit stateChanged(new_value.toInt());
         }  else {
            if (_Input.Update(new_value) == actionProceed) {
               ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, SIG_STATE_CHANGED);
               EmitGUISignal(new_signal);
               emit stateChanged(new_value.toInt());
            } else {
               ResetValue();
            }
         }
      } else {
         ResetValue();
      }

      if (_DisableParentValue && sync && parent) {
         qApp->processEvents();
         parent->setEnabled(true);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CStateButton::drawButton(QPainter * painter)
{
   if (_ButtonStyleValue == NoBorders) {
      drawButtonLabel(painter);
   } else {
      QToolButton::drawButton(painter);
   }  
}

// GUI related virtual methods

void CStateButton::View()
{
}

// CCS related virtual methods

void CStateButton::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_ButtonFuncSpec, _ButtonFuncRef);
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSCreateFuncRef(_ValueFuncSpec, _ValueFuncRef);
   CCSCreateFuncRef(_PreExecFuncSpec, _PreExecFuncRef);

   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   CCSInitializeVarRef(_ShowVarSpec, _ShowVarRef, _ShowVarView, 1);
   CCSInitializeVarRef(_Show2VarSpec, _Show2VarRef, _Show2VarView, 2);
   
   _Input.Set(_VarRef, _PlausFuncRef, _UserFuncRef);
WMETHOD_VOID_EPILOG
#endif
}

void CStateButton::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 0:
      SetValue(value);
      break;
   case 1:
      _ActShowVarRefValue = atol(value);
      if (_ActShowVarRefValue > (_StateCountValue-1)) {
         ErrorPrintf("CStateButton ShowVarRef '%s' (Value %d) higher StateCount (%d)\n", 
                     _ShowVarRef->_Name.c_str(), _ActShowVarRefValue, _StateCountValue);
         _ActShowVarRefValue = _StateCountValue - 1;
      }
      ShowState();
      break;
   case 2:
      _ActShow2VarRefValue = atol(value);
      if (_ActShow2VarRefValue > (_StateCountValue-1)) {
         ErrorPrintf("CStateButton Show2VarRef '%s' (Value %d) higher StateCount (%d)\n", 
                     _Show2VarRef->_Name.c_str(), _ActShow2VarRefValue, _StateCountValue);
         _ActShow2VarRefValue = _StateCountValue - 1;
      }
      ShowState();
      break;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CStateButton::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
}

void CStateButton::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CStateButton::SetIcon(const QPixmap & pixmap, QIconSet::Size size)
{
   QIconSet icon_set;
   icon_set.setPixmap(pixmap, size, QIconSet::Normal);
   icon_set.setPixmap(pixmap, size, QIconSet::Active);
   icon_set.setPixmap(pixmap, size, QIconSet::Disabled);
   setIconSet(icon_set);
}

void CStateButton::SaveValue()
{
   _PrevIndex = _ActIndex;
}

void CStateButton::ResetValue()
{
   _ActIndex = _PrevIndex;
   SetState(StateValue(_ActIndex));
}

QString CStateButton::NewValue()
{
   QString qValue = "";

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T next_index = NextStateIndex(_ActIndex);
   qValue = qValue.setNum(StateValue(next_index));

WMETHOD_RC_EPILOG(qValue)
#endif
   return qValue;
}

void CStateButton::SetValue(const QString & value)
{
   ULONG_T state = value.toInt();
   SetState(state);
   SaveValue();
}

ULONG_T CStateButton::NextStateIndex(ULONG_T act_index)
{
   return (act_index == (ULONG_T)_StateCountValue - 1) ? 0 : act_index + 1;
}

void CStateButton::SetState(ULONG_T state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T next_index = 0;
   if (state == StateValue(0)) {
      _ActIndex = 0;
   } else if (state == StateValue(1)) {
      _ActIndex = 1;
   } else if (_StateCountValue > 2 && state == StateValue(2)) {
      _ActIndex = 2;
   } else if (_StateCountValue > 3 && state == StateValue(3)) {
      _ActIndex = 3;
   } else if (_StateCountValue > 4 && state == StateValue(4)) {
      _ActIndex = 4;
   } else {
      _ActIndex = 0;
      return;
   }
   
   ShowState();
WMETHOD_VOID_EPILOG
#endif
}

ULONG_T CStateButton::StateValue(ULONG_T index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (index) {
   case 0: return _State0ValueValue;
   case 1: return _State1ValueValue;
   case 2: return _State2ValueValue;
   case 3: return _State3ValueValue;
   case 4: return _State4ValueValue;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

QString CStateButton::StateText(ULONG_T index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (index) {
   case 0: return _State0TextValue;
   case 1: return _State1TextValue;
   case 2: return _State2TextValue;
   case 3: return _State3TextValue;
   case 4: return _State4TextValue;
   }
WMETHOD_RC_EPILOG("")
#endif
   return "?";
}

QPixmap & CStateButton::StatePixmap(ULONG_T index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (index) {
   case 0: return _State0PixmapValue;
   case 1: return _State1PixmapValue;
   case 2: return _State2PixmapValue;
   case 3: return _State3PixmapValue;
   case 4: return _State4PixmapValue;
   }
WMETHOD_RC_EPILOG(_State0PixmapValue)
#endif
   return _State0PixmapValue;
}

void CStateButton::ShowState()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   long index;
   long ActInd;
   if ((_ShowVarRef == NULL) && (_Show2VarRef == NULL)) {
      index  = _ActIndex;
      ActInd = index;
   }
   else if (_ShowVarRef && (_Show2VarRef == NULL)) {
      index  = _ActShowVarRefValue;
      ActInd = index;
   }
   else  {
       long Bit1 = _ActShowVarRefValue && 0x00000001;
       long Bit2 = (_ActShow2VarRefValue && 0x00000001) << 1;
       index = Bit1 | Bit2;
       ActInd = index;
   }

   if (_ModeValue == ShowNext) {
      index = NextStateIndex(ActInd);
   }

   if (!StateText(index).isEmpty()) {
      setText(StateText(index));
   }
   if (StatePixmap(index).width() > 0) {
      SetIcon(StatePixmap(index));
   }
WMETHOD_VOID_EPILOG
#endif
}

ULONG_T CStateButton::GetActStateValue()
{
    return StateValue(_ActIndex);
}
