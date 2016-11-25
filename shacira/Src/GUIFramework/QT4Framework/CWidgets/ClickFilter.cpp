

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
   } else if (event_type == QEvent::PaletteChange) {
      QEvent pe(ParentPaletteChanged);
      // send event to all children 
      foreach(QObject * child, o->children()) {
         if (child->isWidgetType()) {
            QApplication::sendEvent(child, &pe);
         }
      }
      return false;
   } else if (event_type == QEvent::Show) {
      QWidget * widget = dynamic_cast<QWidget*>(o);
      if (widget != NULL) {
         if (widget->inherits("QCheckBox")) {
            widget->setStyleSheet("QCheckBox::indicator:checked {image: url(:/stylesheet/css/cb_checked.png);}QCheckBox::indicator:unchecked {image: url(:/stylesheet/css/cb_unchecked.png);}");
         } else if (widget->inherits("QRadioButton")) {
            widget->setStyleSheet("QRadioButton::indicator:checked {image: url(:/stylesheet/css/rb_checked.png);}QRadioButton::indicator:unchecked {image: url(:/stylesheet/css/rb_unchecked.png);}");
         } else if (widget->inherits("QScrollBar")) {
            widget->setStyleSheet("QScrollBar::add-line:vertical{image:url(:/stylesheet/css/sb_down.png);width:30px;height:30px;subcontrol-position:bottom;subcontrol-origin:margin;}\
                                   QScrollBar::sub-line:vertical{image: url(:/stylesheet/css/sb_up.png);width:30px;height:30px;subcontrol-position:top;subcontrol-origin:margin;}\
                                   QScrollBar::add-line:horizontal{image: url(:/stylesheet/css/sb_right.png);width:30px;height:30px;subcontrol-position:right;subcontrol-origin:margin;}\
                                   QScrollBar::sub-line:horizontal{image: url(:/stylesheet/css/sb_left.png);width:30px;height:30px;subcontrol-position:left;subcontrol-origin:margin;}\
                                   QScrollBar:horizontal{border: 2px solid grey;background: lightgrey;height: 30px;margin: 0px 30px 0 30px;}\
                                   QScrollBar::handle:horizontal{background: darkgrey;min-width: 30px;}\
                                   QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal{background: none;}\
                                   QScrollBar:vertical{border: 2px solid grey;background: lightgrey;width: 30px;margin: 30px 0 30px 0;}\
                                   QScrollBar::handle:vertical{background: darkgrey;min-height: 30px;}\
                                   QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{background: none;}");
         }
      }
      return false;
   } else {
      // standard event processing
      return false;
   }
}

