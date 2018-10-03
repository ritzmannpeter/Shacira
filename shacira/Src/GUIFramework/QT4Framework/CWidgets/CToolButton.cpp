
#include "CToolButton.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ButtonWidget, \
                   CToolButton, \
                   ICON_SET("toolbutton"), \
                   "tool button widget")
#endif

#include "CAppFrame.h"
#include "CActionDialog.h"
#ifndef QT4
#include <qobjectlist.h>
#endif

CToolButton::CToolButton(QWidget * parent, const char * name)
#ifdef QT4
   : QToolButton(parent), _usesBigPixmap(false),
#else
   : QToolButton(parent, name),
#endif
     CWidgetBase(this)
{
#ifdef QT4
   setObjectName(name);
#endif
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
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   if (CWidgetBase::Flag(USE_GESTURE)) {
      setAttribute(Qt::WA_AcceptTouchEvents);
   }
#endif
}

CToolButton::~CToolButton() 
{
}

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
bool CToolButton::event(QEvent * e)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CWidgetBase::Flag(USE_GESTURE)) {
      // give visual feedback of button press
      // the normal mouse press doesn't happen until the touch is released (or moved)
      QEvent::Type event_type = e->type();
      if ((event_type == QEvent::TouchBegin) && isEnabled())
         setDown(true);
   }
WMETHOD_RC_EPILOG(TRUE)
#endif
   return QToolButton::event(e);
}
#endif


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

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   if (CWidgetBase::Flag(USE_GESTURE)) {
      setDown(false); // in case of right-click via touch-and-hold the button would get stuck down
   }
#endif
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

#ifdef QT4

void CToolButton::paintEvent(QPaintEvent * e)
{
   if (_ButtonStyleValue != QtSpecific) {
      QPainter painter(this);
      painter.drawPixmap(0, 0, _pixmap);
   } else {
      QToolButton::paintEvent(e);
   }
}

void CToolButton::showEvent(QShowEvent * e)
{
   if (_ButtonStyleValue != QtSpecific) {
      SetAppearance();
   }
   QToolButton::showEvent(e);
}

void CToolButton::hideEvent(QHideEvent * e)
{
   QToolButton::hideEvent(e);
}

void CToolButton::setButtonStyle(const ButtonStyles &value)
{ 
   _ButtonStyleValue = value;

   if (_ButtonStyleValue != QtSpecific) {
      setAutoRaise(true);
      setAutoFillBackground(true);
   }

   setProperty("buttonNoBorders", (_ButtonStyleValue ==  NoBorders) ? true : false);
   PropertyChanged();
}

#else

void CToolButton::drawButton(QPainter * painter)
{
   if (_ButtonStyleValue == NoBorders) {
      drawButtonLabel(painter);
   } else {
      QToolButton::drawButton(painter);
   }  
}

#endif

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

#ifdef QT4

void CToolButton::SetIcon(const QPixmap & pixmap)
{
   QIcon icon(pixmap);
   setIconSize(QSize(width(), height()));
   setIcon(icon);
}

#else

void CToolButton::SetIcon(const QPixmap & pixmap, QIconSet::Size size)
{
   QIconSet icon_set;
   icon_set.setPixmap(pixmap, size, QIconSet::Normal);
   icon_set.setPixmap(pixmap, size, QIconSet::Active);
   icon_set.setPixmap(pixmap, size, QIconSet::Disabled);
   setIconSet(icon_set);
}

#endif

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
#ifdef QT4
   if (!pixmap.isNull()) {
      QImage image = pixmap.toImage();
      int w = width();
      int h = height();
      image = image.scaled(w, h);
      QPalette palette = this->palette();
      palette.setBrush(QPalette::Button, QBrush(image));
      setPalette(palette);
      _pixmap = pixmap;
      return true;
   } else {
      return false;
   }
#else
   if (!pixmap.isNull()) {
      setPixmap(pixmap);
      return true;
   } else {
      return false;
   }
#endif
}

void CToolButton::ResetContainer()
{
   QWidget * container = GetNextContainer();
   if (container == NULL) return;
#ifdef QT4
   const QObjectList children = container->children();
   QObjectList::const_iterator i = children.constBegin();
   while (i != children.constEnd()) {
      QObject * object = (*i);
      if (object && object->isWidgetType()) {
         QWidget * child = static_cast<QWidget*>(object);
         if (child && child->inherits("CToolButton")) {
            CToolButton * button = (CToolButton*)child;
            if (button != this) {
               button->SetActive(false);
            }
         } else {
            ResetContainer(child);
         }
      }
      i++;
   }
#else
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
#endif
}

void CToolButton::ResetContainer(QWidget * widget)
{
   if (!getContainerSensitive()) {
      return;
   }
#ifdef QT4
   const QObjectList children = widget->children();
   QObjectList::const_iterator i = children.constBegin();
   while (i != children.constEnd()) {
      QObject * object = (*i);
      if (object && object->isWidgetType()) {
         QWidget * child = static_cast<QWidget*>(object);
         if (child && child->inherits("CToolButton")) {
            CToolButton * button = (CToolButton*)child;
            if (button != this) {
               button->SetActive(false);
            }
         } else {
            ResetContainer(child);
   	   }
      }
      i++;
   }
#else
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
#endif
}

QWidget * CToolButton::GetNextContainer()
{
   QObject * parent = ((QObject*)this)->parent();
   while (parent != NULL) {
      if (parent->isWidgetType()) {
         QWidget * widget = (QWidget*)parent;
#ifdef QT4
         if (widget->inherits("CAppFrame")) {
            return widget;
         }
#else
         if (widget->inherits("CButtonGroup") ||
             widget->inherits("CAppFrame")) {
            return widget;
         }
#endif
         parent = parent->parent();
      }
   }
   return NULL;
}

