
// PR 31.03.05 set focus policy to no focus

#include "CPushButton.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ButtonWidget, \
                   CPushButton, \
                   ICON_SET("pushbutton"), \
                   "push button widget")
#endif

#include "CAppFrame.h"
#include "CActionDialog.h"

CPushButton::CPushButton(QWidget * parent, const char * name)
#ifdef QT4
   : QPushButton(parent),
#else
   : QPushButton(parent, name),
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
   _DisableParentValue = false;
   _ButtonStyleValue = QtSpecific;
#ifdef QT4
   setFocusPolicy(Qt::NoFocus);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   if (CWidgetBase::Flag(USE_GESTURE)) {
      setAttribute(Qt::WA_AcceptTouchEvents);
   }
#endif
#else
   setFocusPolicy(QWidget::NoFocus);
#endif
}

CPushButton::~CPushButton() 
{
}

#ifdef QT4

void CPushButton::paintEvent(QPaintEvent * e)
{
#ifndef ALTERNATE_CASE_ERASES_BUTTON_CONTENTS
   QPushButton::paintEvent(e);
#else
   if (_ButtonStyleValue != QtSpecific) {
      QPainter painter(this);
      painter.drawPixmap(0, 0, _pixmap);
   } else {
      QPushButton::paintEvent(e);
   }
#endif
}

void CPushButton::showEvent(QShowEvent * e)
{
   QPushButton::showEvent(e);
}

void CPushButton::hideEvent(QHideEvent * e)
{
   QPushButton::hideEvent(e);
}

void CPushButton::setButtonStyle(const ButtonStyles &value)
{ 
   _ButtonStyleValue = value;

   setProperty("buttonNoBorders", (_ButtonStyleValue ==  NoBorders) ? true : false);
   PropertyChanged(); 
}

#else

void CPushButton::drawButton(QPainter * painter)
{
   if (_ButtonStyleValue == NoBorders) {
      drawButtonLabel(painter);
   } else {
      QPushButton::drawButton(painter);
   }  
}

#endif

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
bool CPushButton::event(QEvent * e)
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
   return QPushButton::event(e);
}
#endif

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

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   if (CWidgetBase::Flag(USE_GESTURE)) {
      setDown(false); // in case of right-click via touch-and-hold the button would get stuck down
   }
#endif
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

#ifdef QT4

void CPushButton::SetIcon(const QPixmap & pixmap)
{
   _pixmap = pixmap;

   QIcon icon;
   icon.addPixmap(pixmap, QIcon::Normal);
   icon.addPixmap(pixmap, QIcon::Active);
   icon.addPixmap(pixmap, QIcon::Disabled);

   setIconSize(QSize(width()-2, height()-2));
   setIcon(icon);
}

void CPushButton::setPixmap(const QPixmap & pixmap)
{
   if (!pixmap.isNull()) {
      QImage image = pixmap.toImage();
      int w = width();
      int h = height();
      image = image.scaled(w, h);
      QPalette palette = this->palette();
      palette.setBrush(QPalette::Button, QBrush(image));
      setPalette(palette);
      _pixmap = pixmap;
   }
}

#else

void CPushButton::SetIcon(const QPixmap & pixmap, QIconSet::Size size)
{
   QIconSet icon_set;
   icon_set.setPixmap(pixmap, QIconSet::Small, QIconSet::Normal);
   icon_set.setPixmap(pixmap, QIconSet::Small, QIconSet::Active);
   icon_set.setPixmap(pixmap, QIconSet::Small, QIconSet::Disabled);
   setIconSet(icon_set);
}

#endif

