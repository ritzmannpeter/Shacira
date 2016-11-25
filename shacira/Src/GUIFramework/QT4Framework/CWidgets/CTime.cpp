
#include "CTime.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CTime, \
                   ICON_SET("timeedit"), \
                   "time edit widget")
#endif

// poor mans union

class cDuration
{
public:
   cDuration(ULONG_T hours, ULONG_T minutes, ULONG_T seconds)
   {
      _Seconds = 0;
      Set(hours, minutes, seconds);
   };
   cDuration(ULONG_T seconds = 0)
   {
      _Seconds = seconds;
   };
   virtual ~cDuration() {};
   void AddSeconds(ULONG_T seconds)
   {
      _Seconds += seconds;
   };
   void AddMinutes(ULONG_T minutes)
   {
      _Seconds += (minutes * 60);
   };
   void AddHours(ULONG_T hours)
   {
      _Seconds += hours * (3600);
   };
   void Set(ULONG_T hours, ULONG_T minutes, ULONG_T seconds)
   {
      _Seconds = 0;
      AddHours(hours);
      AddMinutes(minutes);
      AddSeconds(seconds);
   };
   void Get(ULONG_T & hours, ULONG_T & minutes, ULONG_T & seconds)
   {
      ULONG_T v = _Seconds;
      hours = v / 3600;
      v = v % 3600;
      minutes = v / 60;
      v = v % 60;
      seconds = v;
   };
   ULONG_T Seconds()
   {
      return _Seconds;
   };
private:
   ULONG_T _Seconds;
};

CTime::CTime(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QTimeEdit(parent),
#else
   : QTimeEdit(parent, name),
#endif
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
#ifdef QT4
   connect(this,
           SIGNAL(timeChanged(const QTime &)),
           this,
           SLOT(SetTime(const QTime &)));
#else
   connect(this,
           SIGNAL(valueChanged(const QTime &)),
           this,
           SLOT(SetTime(const QTime &)));
#endif
}

CTime::~CTime() 
{
}

void CTime::SetTime(unsigned long time)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cDuration duration(time);
   ULONG_T hours = 0;
   ULONG_T minutes = 0;
   ULONG_T seconds = 0;
   duration.Get(hours, minutes, seconds);
   QTime qtime(hours, minutes, seconds);
   setTime(qtime);
WMETHOD_VOID_EPILOG
#endif
}

void CTime::SetTime(const QTime & time)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_VarRef != NULL) {
      ULONG_T hours = time.hour();
      ULONG_T minutes = time.minute();
      ULONG_T seconds = time.second();
      cDuration duration(hours, minutes, seconds);
      char value[0x40] = {0};
      SafePrintf(value, sizeof(value), "%d", duration.Seconds());
      CCSSetValue(_VarRef, value);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTime::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QTimeEdit::mousePressEvent(e);
   }
}

void CTime::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QTimeEdit::mouseReleaseEvent (e);
   }
}

void CTime::focusInEvent ( QFocusEvent * e)
{
   QTimeEdit::focusInEvent (e);
}

void CTime::focusOutEvent ( QFocusEvent * e)
{
   QTimeEdit::focusOutEvent (e);
}

void CTime::keyReleaseEvent ( QKeyEvent * e )
{
   QTimeEdit::keyReleaseEvent (e);
}

// GUI related virtual methods

void CTime::View()
{
}

// CCS related virtual methods

void CTime::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
WMETHOD_VOID_EPILOG
#endif
}

void CTime::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
   QString qValue = value;
   ULONG_T lval = qValue.toULong();
   SetTime(lval);
}

void CTime::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
}

void CTime::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

unsigned long CTime::GetTime()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T seconds = time().second();
   ULONG_T minutes = time().minute();
   ULONG_T hours = time().hour();
   cDuration duration(hours, minutes, seconds);
   return duration.Seconds();
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}


