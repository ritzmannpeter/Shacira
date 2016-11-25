
#include "CStartupForm.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CStartupForm, \
                   ICON_SET("designer_form"), \
                   "application startup form, use File->New... to create")
#endif

#include <qapplication.h>

CStartupForm::CStartupForm(QWidget * parent, const char * name, WFlags flags)
   : CWidget(parent, name)
{
   CONSTRUCT_WIDGET

   _EventAdapter = NULL;
   _EventSink = NULL;
   _Console = NULL;
   _RefreshTimer = NULL;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(TimerExpired()));
   _RefreshTimer->start(20);
WMETHOD_VOID_EPILOG
#endif
}

CStartupForm::~CStartupForm ( ) 
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_EventAdapter != NULL) {
      if (_EventSink) {
         _EventAdapter->UnRegisterControl(_EventSink);
         delete _EventSink;
      }
   }
   _RefreshTimer->stop();
   disconnect(_RefreshTimer, SIGNAL(timeout()), 0, 0);
   delete _RefreshTimer;
   _RefreshTimer = NULL;
WMETHOD_VOID_EPILOG
#endif
}

void CStartupForm::Refresh()
{
}

void CStartupForm::CreateEventSink(EVENT_ADAPTER_PTR adapter)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _EventAdapter = adapter;
   _EventSink = new cEventSink(this);
   _EventAdapter->RegisterControl(_EventSink);
WMETHOD_VOID_EPILOG
#endif
}

void CStartupForm::Object(TRANSIENT_OBJECT_PTR object)
{
}

void CStartupForm::TimerExpired()
{
   qApp->processEvents();
   Refresh();
}

void CStartupForm::SetConsole(CONSOLE_PTR console)
{
   _Console = console;
}

void CStartupForm::Info(const QString & info, unsigned int index, BOOL_T refresh)
{
   if (index < INFO_MESSAGES) {
      _Infos[index] = info;
      if (refresh) {
         Refresh();
      }
   }
}

#ifndef QT_PLUGIN

cEventSink::cEventSink(CStartupForm * form)
{
   _Form = form;
}

cEventSink::~cEventSink()
{
}

void cEventSink::Object(TRANSIENT_OBJECT_PTR object)
{
   if (_Form != NULL) {
      _Form->Object(object);
   }
}

#endif

