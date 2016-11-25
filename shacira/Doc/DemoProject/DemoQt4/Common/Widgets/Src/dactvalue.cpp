
#include "dactvalue.h"

#ifdef _DWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   DActValue, \
                   ICON_SET("dactvalue"), \
                   "Demo Display Widget")
#endif

DActValue::DActValue(QWidget* parent, const char* name, Qt::WindowFlags f)
   : CActValue(parent, name)
{
   _AlarmColorValue = paletteBackgroundColor();
   _NotAlarmColorValue = paletteBackgroundColor();
}

DActValue::~DActValue()
{
}

// GUI related virtual methods

void DActValue::View()
{
   CActValue::View();
}

#ifdef actually_not_reimplemented

void DActValue::Notification(ULONG_T event_code)
{
}

void DActValue::RefreshData()
{
}

void DActValue::GUIEvent(ULONG_T signal, QWidget * sender)
{
}

#endif

// CCS related virtual methods

void DActValue::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CActValue::CCSSetContext(node, context);
WMETHOD_VOID_EPILOG
#endif
}

void DActValue::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CActValue::CCSNewValue(value, id, time_offset, data_type, size);
   FLOAT_T v = atof(value);
#ifdef QT4
   if (v > 10) {
      setPaletteBackgroundColor(_AlarmColorValue);
   } else {
      setPaletteBackgroundColor(_NotAlarmColorValue);
   }
#else
   if (v > 10) {
      setBackgroundColor(_AlarmColorValue);
   } else {
      setBackgroundColor(_NotAlarmColorValue);
   }
#endif
   WMETHOD_VOID_EPILOG
#endif
}

void DActValue::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
}

void DActValue::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
  try {  
      ULONG_T object_type = object->get_Type();
      if (object_type == OT_JOB_ENTRY) {    // process trend data
         cJobEntry * entry = (cJobEntry*)object;
      } else if (object_type == OT_DATA_CHANGE) {  // process data change
         cDataChange * cdcData = (cDataChange*)object;
         Beep(50,50);
      } else if (object_type == OT_ALARM) {
         cAlarm * alarm = (cAlarm*)object;
      }
   } catch(cError & e) {
      ErrorPrintf("%s while processing event in\n", e.ErrMsg().c_str());
   } catch(...) {
      ErrorPrintf("unhandled exception while processing event in\n");
   }
WMETHOD_VOID_EPILOG
#endif
}

