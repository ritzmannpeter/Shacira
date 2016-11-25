
#include "CToolButton.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ButtonWidget, \
                   CToolButton, \
                   ICON_SET("designer_toolbutton"), \
                   "tool button widget")
#endif

#include <qobjectlist.h>
#include "CAppFrame.h"
#include "CActionDialog.h"

CToolButton::CToolButton(QWidget * parent, const char * name)
   : QToolButton(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _ExecModeValue = Sync;
   _PreExecFuncRef = NULL;
   _ButtonFuncRef = NULL;
   _Active = false;
   _Mouse = false;
   _Pressed = false;
   _ContainerSensitiveValue = false;
   _ButtonStyleValue = QtSpecific;
}

CToolButton::~CToolButton() 
{
}

void CToolButton::mousePressEvent(QMouseEvent * e)
{
   _Pressed = true;
   SetAppearance();
   if (!HelpActive()) {
      if (!Flag(NON_STANDARD_BUTTONS)) {
         if (_ButtonStyleValue == QtSpecific) {
            QToolButton::mousePressEvent(e);
         }
      }
   }
}

void CToolButton::mouseReleaseEvent(QMouseEvent * e)
{
   _Pressed = false;
   SetAppearance();
   if (HelpActive()) {
      SetHelpIds();
   } else {
      if (!Flag(NON_STANDARD_BUTTONS)) {
         if (_ButtonStyleValue ==QtSpecific) {
            QToolButton::mouseReleaseEvent(e);
         }
      }
      SetActive(true);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      EmitGUISignal(SIG_BUTTON_CLICKED);
      BOOL_T sync = (_ExecModeValue == Sync) ? true : false;
      ULONG_T rc = ExecuteButtonFuncs(_PreExecFuncRef, _ButtonFuncRef, sync, _ActionDialogValue, 0);
      emit ButtonFunctionExecuted(rc); // HA210605
WMETHOD_VOID_EPILOG
#endif
   }
}

void CToolButton::keyReleaseEvent ( QKeyEvent * e )
{
   if (HelpActive()) {
      return;
   }
   int key = e->key();
   e->ignore();
   QToolButton::keyReleaseEvent (e);
   if (key == Qt::Key_Return || key == Qt::Key_Enter) {
      SetActive(true);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      EmitGUISignal(SIG_BUTTON_CLICKED);
      BOOL_T sync = (_ExecModeValue == Sync) ? true : false;
      ULONG_T rc = ExecuteButtonFuncs(_PreExecFuncRef, _ButtonFuncRef, sync, _ActionDialogValue, 0);
      emit ButtonFunctionExecuted(rc);
WMETHOD_VOID_EPILOG
#endif
   }
}

void CToolButton::enterEvent(QEvent * e)
{
   if (_ButtonStyleValue == QtSpecific) {
      QToolButton::enterEvent(e);
   }
   SetMouse(true);
};

void CToolButton::leaveEvent(QEvent * e)
{
   if (_ButtonStyleValue == QtSpecific) {
      QToolButton::leaveEvent(e);
   }
   SetMouse(false);
};


void CToolButton::drawButton(QPainter * painter)
{
   if (_ButtonStyleValue == NoBorders) {
      drawButtonLabel(painter);
   } else {
      QToolButton::drawButton(painter);
   }  
}

// GUI related virtual methods

void CToolButton::View()
{
}

// CCS related virtual methods

void CToolButton::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   CCSCreateFuncRef(_PreExecFuncSpec, _PreExecFuncRef);
   CCSCreateFuncRef(_ButtonFuncSpec, _ButtonFuncRef);
WMETHOD_VOID_EPILOG
#endif
}

void CToolButton::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                              UCHAR_T data_type, ULONG_T size)
{
}

void CToolButton::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                              UCHAR_T data_type, ULONG_T size)
{
}

void CToolButton::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CToolButton::SetIcon(const QPixmap & pixmap, QIconSet::Size size)
{
   QIconSet icon_set;
   icon_set.setPixmap(pixmap, size, QIconSet::Normal);
   icon_set.setPixmap(pixmap, size, QIconSet::Active);
   icon_set.setPixmap(pixmap, size, QIconSet::Disabled);
   setIconSet(icon_set);
}

void CToolButton::SetActive(bool state)
{
   if (state) {
      ResetContainer();
   }
   _Active = state;
   SetAppearance();
}

void CToolButton::SetMouse(bool state)
{
   _Mouse = state;
   if (_Mouse) {
      if (!_ActiveMousePixmapValue.isNull()) {
         SetAppearance();
      }
   } else {
      if (!_InactiveMousePixmapValue.isNull()) {
         SetAppearance();
      }
   }
}

void CToolButton::SetAppearance()
{
   if (_Pressed) {
      if (SetPixmap(_PressedPixmapValue)) {
         return;
      }
   }
   if (_Active) {
      if (_Mouse) {
         if (!SetPixmap(_ActiveMousePixmapValue)) {
            SetPixmap(_ActivePixmapValue);
            emit GroupSelected(_ActivePixmapValue);
         }
      } else {
         SetPixmap(_ActivePixmapValue);
         emit GroupSelected(_ActivePixmapValue);
      }
   } else {
      if (_Mouse) {
         if (!SetPixmap(_InactiveMousePixmapValue)) {
            SetPixmap(_InactivePixmapValue);
         }
      } else {
         SetPixmap(_InactivePixmapValue);
      }
   }
}

bool CToolButton::SetPixmap(QPixmap & pixmap)
{
   if (!pixmap.isNull()) {
      setPixmap(pixmap);
      return true;
   } else {
      return false;
   }
}

void CToolButton::ResetContainer()
{
   QWidget * container = GetNextContainer();
   if (container == NULL) return;
   const QObjectList * children = container->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("CToolButton")) {
            CToolButton * button = (CToolButton*)child;
            if (button != this) {
               button->SetActive(false);
            }
         } else {
            ResetContainer(child);
         }
      }
      ++i;
   }
}

void CToolButton::ResetContainer(QWidget * widget)
{
   if (!getContainerSensitive()) {
      return;
   }
   const QObjectList * children = widget->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("CToolButton")) {
            CToolButton * button = (CToolButton*)child;
            if (button != this) {
               button->SetActive(false);
            }
         } else {
            ResetContainer(child);
   	   }
      }
      ++i;
   }
}

QWidget * CToolButton::GetNextContainer()
{
   QObject * parent = ((QObject*)this)->parent();
   while (parent != NULL) {
      if (parent->isWidgetType()) {
         QWidget * widget = (QWidget*)parent;
         if (widget->inherits("CButtonGroup") ||
             widget->inherits("CAppFrame")) {
            return widget;
         }
         parent = parent->parent();
      }
   }
   return NULL;
}

