

#include "ApplicationFilter.h"
#include "CWidgetBase.h"
#include "CAppFrame.h"

bool ApplicationFilter::eventFilter(QObject *o, QEvent *e)
{
#undef LOCK_TEST
#ifdef LOCK_TEST
   if (o->isWidgetType()) {
      QEvent::Type event_type = e->type();
      if (event_type == QEvent::MouseButtonRelease ||
          event_type == QEvent::MouseButtonPress ||
          event_type == QEvent::MouseButtonRelease ||
          event_type == QEvent::MouseButtonDblClick ||
          event_type == QEvent::KeyPress ||
          event_type == QEvent::KeyRelease) {
         QWidget * widget = (QWidget*)o;
         if (CWidgetBase::IsCustomWidget(widget)) {
            if (widget->inherits("CVirtualKeyboard")) {
               return TRUE;
            }
            if (widget->inherits("CToolButton")) {
               return TRUE;
            }
            if (widget->inherits("CPushButton")) {
               return TRUE;
            }
            if (widget->inherits("CReqValue")) {
               return TRUE;
            }
            if (widget->inherits("CTextEdit")) {
               return TRUE;
            }
         }
         return false;
      }
   }
#endif
   QEvent::Type event_type = e->type();
   if (event_type == QEvent::MouseButtonRelease) {
      QMouseEvent * m = (QMouseEvent*)e;
      CAppFrame * app_frame = CWidgetBase::_AppFrame;
      if (app_frame != NULL) {
         app_frame->ResyncLogoff();
      }
      return false;
   } else if (event_type == QEvent::PaletteChange) {
      QEvent pe(ParentPaletteChanged);
      // send event to all children 
      foreach(QObject * child, o->children()) {
         if (child->isWidgetType()) {
            QApplication::sendEvent(child, &pe);
         }
      }
      return false;
   } else if ((event_type == QEvent::Show) && _useApplicationStyleSheet) {
      QWidget * widget = dynamic_cast<QWidget*>(o);
      if (widget != NULL) {
         QString styleSheet = CWidgetBase::StyleSheet(widget);
         if (!styleSheet.isEmpty()) {
            widget->setStyleSheet(styleSheet);
         }
      }
      return false;
   } else {
      // standard event processing
      return false;
   }
}

