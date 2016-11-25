
// PR 31.03.05 set focus policy to no focus

#include "CPushButton.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ButtonWidget, \
                   CPushButton, \
                   ICON_SET("designer_pushbutton"), \
                   "push button widget")
#endif

#include "CAppFrame.h"
#include "CActionDialog.h"

CPushButton::CPushButton(QWidget * parent, const char * name)
   : QPushButton(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET

   _VarRef = NULL;
   _VarView = NULL;
   _ExecModeValue = Sync;
   _PreExecFuncRef = NULL;
   _ButtonFuncRef = NULL;
   _DisableParentValue = false;
   _ButtonStyleValue = QtSpecific;
   setFocusPolicy(QWidget::NoFocus);
}

CPushButton::~CPushButton() 
{
}

void CPushButton::drawButton(QPainter * painter)
{
   if (_ButtonStyleValue == NoBorders) {
      drawButtonLabel(painter);
   } else {
      QPushButton::drawButton(painter);
   }  
}

void CPushButton::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      if (!Flag(NON_STANDARD_BUTTONS)) {
         QPushButton::mousePressEvent(e);
      }
   }
}

void CPushButton::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      if (!Flag(NON_STANDARD_BUTTONS)) {
         QPushButton::mouseReleaseEvent(e);
      }
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      EmitGUISignal(SIG_BUTTON_CLICKED);
      BOOL_T sync = (_ExecModeValue == Sync) ? true : false;
      QWidget * parent = NULL;
      if (_DisableParentValue && sync) {
         parent = parentWidget();
         parent->setEnabled(false);
         qApp->processEvents();
      }
      ULONG_T rc = ExecuteButtonFuncs(_PreExecFuncRef, _ButtonFuncRef, sync, _ActionDialogValue, 0);
      if (_DisableParentValue && sync) {
         qApp->processEvents();
         if (parent == NULL)
            parent = parentWidget();
         parent->setEnabled(true);
      }

      emit ButtonFunctionExecuted(rc); // HA210605
WMETHOD_VOID_EPILOG
#endif
   }
}

void CPushButton::keyReleaseEvent(QKeyEvent * e)
{
   if (HelpActive()) {
      return;
   }
   int key = e->key();
   e->ignore();
   QPushButton::keyReleaseEvent(e);
   if (key == Qt::Key_Return || key == Qt::Key_Enter) {
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      EmitGUISignal(SIG_BUTTON_CLICKED);
      BOOL_T sync = (_ExecModeValue == Sync) ? true : false;
      QWidget * parent = NULL;
      if (_DisableParentValue && sync) {
         parent = parentWidget();
         parent->setEnabled(false);
         qApp->processEvents();
      }
      ULONG_T rc = ExecuteButtonFuncs(_PreExecFuncRef, _ButtonFuncRef, sync, _ActionDialogValue, 0);
      if (_DisableParentValue && sync) {
         qApp->processEvents();
         if (parent == NULL)
            parent = parentWidget();
         parent->setEnabled(true);
      }
      emit ButtonFunctionExecuted(rc);
WMETHOD_VOID_EPILOG
#endif
   }
}

// GUI related virtual methods

void CPushButton::View()
{
}

// CCS related virtual methods

void CPushButton::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   CCSCreateFuncRef(_PreExecFuncSpec, _PreExecFuncRef);
   CCSCreateFuncRef(_ButtonFuncSpec, _ButtonFuncRef);
WMETHOD_VOID_EPILOG
#endif
}

void CPushButton::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CPushButton::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CPushButton::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CPushButton::SetIcon(const QPixmap & pixmap, QIconSet::Size size)
{
   QIconSet icon_set;
   icon_set.setPixmap(pixmap, QIconSet::Small, QIconSet::Normal);
   icon_set.setPixmap(pixmap, QIconSet::Small, QIconSet::Active);
   icon_set.setPixmap(pixmap, QIconSet::Small, QIconSet::Disabled);
   setIconSet(icon_set);
}
