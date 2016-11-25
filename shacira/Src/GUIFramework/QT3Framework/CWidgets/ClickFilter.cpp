

#include "ClickFilter.h"
#include "CWidgetBase.h"
#include "CAppFrame.h"

bool ClickFilter::eventFilter(QObject *o, QEvent *e)
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
            QString name = widget->name();
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
   } else {
      // standard event processing
      return false;
   }
}

