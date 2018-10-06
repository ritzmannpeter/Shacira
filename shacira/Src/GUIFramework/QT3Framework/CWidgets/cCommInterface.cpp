
#include "cCommInterface.h"
#include "CWidgetBase.h"
#include "CAppFrame.h"
#include "cGuiEvents.h"

cCommInterface::cCommInterface()
{
}

cCommInterface::~cCommInterface()
{
}

void cCommInterface::GUIEvent(QEvent * e)
{
   if (e->type() == QEvent::User) {
WMETHOD_PROLOG
      cCommEvent * comm_event = (cCommEvent*)e;
      ULONG_T event_code = comm_event->EventCode();
      CWidgetBase * widget = comm_event->Target();
      if (widget != NULL) {
         if (event_code == NEW_VALUE) {
            cNewValueEvent * event = (cNewValueEvent*)e;
            widget->CCSNewValue((const char *)event->Value(),
                                event->Id(),
                                event->TimeOffset(),
                                event->DataType(),
                                event->Size());
         } else if (event_code == NEW_BUF) {
            cNewBufEvent * event = (cNewBufEvent*)e;
            widget->CCSNewValue(event->Buf(),
                                event->Id(),
                                event->TimeOffset(),
                                event->DataType(),
                                event->Size());
         } else if (event_code == NEW_OBJECT) {
            cNewObjectEvent * event = (cNewObjectEvent*)e;
            TRANSIENT_OBJECT_PTR object = event->Object();
            UCHAR_T object_type = object->get_Type();
            int event_filter = widget->EventFilter();
            if ((event_filter == ALL_EVENTS) ||
                (event_filter == object_type)) {
               ULONG_T rc = widget->ExecuteEventFilterFunc(widget->_EventFilterFuncRef, object);
               if (rc == 0) {
                  widget->CCSEvent(object);
               }
            }
            object->Release();
         } else if (event_code == LANGUAGE_CHANGE) {
            CAppFrame * frame = (CAppFrame*)widget;
            frame->DelayedLanguageChange();
            frame->Refresh(TEXT_REFRESH, true);
         } else if (event_code == REFRESH_DATA) {
            CAppFrame * frame = (CAppFrame*)widget;
            frame->Refresh(DATA_REFRESH);
         } else if (event_code == REFRESH_BG_DATA) {
            CAppFrame * frame = (CAppFrame*)widget;
            frame->Refresh(BG_DATA_REFRESH);
         } else if (event_code == MESSAGE_BOX) {
            cMessageBoxEvent * event = (cMessageBoxEvent*)e;
            QString caption = event->_Caption;
            QString text = event->_Text;
            QMessageBox::Icon icon = event->_Icon;
            int button0 = event->_Button0;
            int button1 = event->_Button1;
            int button2 = event->_Button2;
            QMessageBox mb(caption,
                           text, icon, button0, button1, button2);
            QFont font = event->_Font;
            mb.setFont(font);
            mb.exec();
         } else {
            widget->ExecuteNotification(event_code);
         }
      }
WMETHOD_VOID_EPILOG
   }
}

