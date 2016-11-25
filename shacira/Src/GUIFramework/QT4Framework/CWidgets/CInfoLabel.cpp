
#include "CInfoLabel.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CInfoLabel, \
                   ICON_SET("label"), \
                   "text label widget, that displays text of cInfo events")
#endif

#ifndef QT_PLUGIN
#include "System/Objects/cInfo.h"
#include "CAppFrame.h"
#include <qapplication.h>
#endif


CInfoLabel::CInfoLabel(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QLabel(parent, f),
#else
   : QLabel(parent, name, f),
#endif
     CWidgetBase(this)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET

   _Info = NULL;
   _InfoTypeFilterValue = 1;
   setMinimumHeight(getScaledHeight(this, 25));
#ifndef QT_PLUGIN
   hide();
#endif
}

CInfoLabel::~CInfoLabel ( ) 
{
}

void CInfoLabel::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Info != NULL) {
      INFO_PTR info = _Info;
      LONG_T info_type = info->get_InfoType();
      QString text;
      if (info_type == IT_USER_INFO) {
         STRING_T _text = cText::GetText(info->get_InfoTextId(), info->get_InfoText().c_str());
         if (_text.size() > 0) {
            text = Translate(_text.c_str(), cText::Context(info->get_InfoTextId()),
                             info->get_Param1().c_str(), info->get_Param2().c_str(),
                             info->get_Param3().c_str(), info->get_Param4().c_str());
         }
      } else if (info_type == IT_ALARM_INFO) {
         text = GetTranslatedAlarmText(info);
      }
      SetText(text);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CInfoLabel::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QLabel::mousePressEvent(e);
   }
}

void CInfoLabel::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QLabel::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CInfoLabel::View()
{
#ifndef QT_PLUGIN
    DelayedLanguageChange(); //HA09022006
#endif
}

// CCS related virtual methods

void CInfoLabel::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_EventFilter == NoEvents) {
      show();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CInfoLabel::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
}

void CInfoLabel::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CInfoLabel::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   UCHAR_T object_type = object->get_Type();
   if (object_type == OT_INFO) {
      cInfo * info = (cInfo*)object;
      LONG_T info_type = info->get_InfoType();
      if (_InfoTypeFilterValue == UNDEFINED ||
          _InfoTypeFilterValue == info_type) {
         if (info_type == IT_USER_INFO) {
            STRING_T _text = cText::GetText(info->get_InfoTextId(), info->get_InfoText().c_str());
            if (_text.size() > 0) {
               QString text = Translate(_text.c_str(), cText::Context(info->get_InfoTextId()),
                                        info->get_Param1().c_str(), info->get_Param2().c_str(),
                                        info->get_Param3().c_str(), info->get_Param4().c_str());
               show();
               SetText(text);
               SetInfo(info);
            } else {
               hide();
               SetText("");
               SetInfo(NULL);
            }
         } else if (info_type == IT_ALARM_INFO) {
            STRING_T _text = cText::GetText(info->get_InfoTextId(), info->get_InfoText().c_str());
            if (_text.size() > 0) {
               QString text = GetTranslatedAlarmText(info);
               show();
               SetText(text);
               SetInfo(info);
            } else {
               hide();
               SetText("");
               SetInfo(NULL);
            }
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CInfoLabel::SetText(QString text)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString utf8_text = text;
   if (CWidgetBase::Flag(UTF8_ENCODED_INPUT)) {
      utf8_text = FromUtf8(text);
      //utf8_text = QString::fromUtf8(CONST_STRING(text));
   }
   setText(utf8_text);
WMETHOD_VOID_EPILOG
#endif
}

void CInfoLabel::SetInfo(INFO_PTR info)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Info != NULL) {
      _Info->Release();
      _Info = NULL;
   }
   if (info != NULL) {
      info->AddRef();
      _Info = info;
   }
WMETHOD_VOID_EPILOG
#endif
}

QString CInfoLabel::GetTranslatedAlarmText(INFO_PTR info)
{
   QString translated_text = "";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   STRING_T text;
   CAppFrame * app_frame = CWidgetBase::_AppFrame;
   if (app_frame != NULL) {
      ULONG_T text_id = info->get_InfoTextId();
      ULONG_T id = info->get_InfoId();
      
      text = cText::GetText(text_id, info->get_InfoText().c_str());
      if (!app_frame->GetTranslation(translated_text, app_frame->GetLanguage(),
                                     id, text.c_str(),
                                     info->get_Param1().c_str(), info->get_Param2().c_str(),
                                     info->get_Param3().c_str(), info->get_Param4().c_str())) {
         if (text.size() > 0) {
            CONST_STRING_T text_context =  cText::Context(text_id);

            if (cResources::FlagSet(PF_NONSTANDARD_CONTEXT)) {
                text_context = text_id ? cText::Context(text_id) : "AlarmText";
            }

            translated_text = Translate(text.c_str(), text_context,
                                        info->get_Param1().c_str(), info->get_Param2().c_str(),
                                        info->get_Param3().c_str(), info->get_Param4().c_str());
         }
      }
   }
WMETHOD_RC_EPILOG(translated_text)
#endif
    return translated_text;
}


