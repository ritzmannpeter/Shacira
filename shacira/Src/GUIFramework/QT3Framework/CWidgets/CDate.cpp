
#include "CDate.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(InputWidget,
                   CDate, \
                   ICON_SET("designer_dateedit"), \
                   "date edit widget")
#endif

#define INT_DATE(date, year, month, day) \
   date += year * 10000; \
   date += month * 100; \
   date += day;
#define GET_DATE(date, year, month, day) \
   year = date / 10000; \
   month = (date % 10000) / 100; \
   day = date % 100

CDate::CDate(QWidget * parent, const char * name, WFlags f) 
   : QDateEdit(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
   _Date = QDate::currentDate();
   setDate(_Date);
	connect(this,
           SIGNAL(valueChanged(const QDate &)),
           this,
           SLOT(SetDate(const QDate &)));
}

CDate::~CDate() 
{
}

void CDate::SetDate(const QDate & date)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Date = date;
   if (_VarRef != NULL) {
      ULONG_T year = _Date.year();
      ULONG_T month = _Date.month();
      ULONG_T day = _Date.day();
      ULONG_T date = 0;
      INT_DATE(date, year, month, day);
      char value[0x40] = {0};
      SafePrintf(value, sizeof(value), "%d", date);
      CCSSetValue(_VarRef, value);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CDate::SetDate(unsigned long date)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T year = 0;
   ULONG_T month = 0;
   ULONG_T day = 0;
   GET_DATE(date, year, month, day);
   QDate qdate(year, month, day);
   setDate(qdate);
WMETHOD_VOID_EPILOG
#endif
}

void CDate::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QDateEdit::mousePressEvent(e);
   }
}

void CDate::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QDateEdit::mouseReleaseEvent (e);
   }
}

void CDate::focusInEvent ( QFocusEvent * e)
{
   QDateEdit::focusInEvent (e);
}

void CDate::focusOutEvent ( QFocusEvent * e)
{
   QDateEdit::focusOutEvent (e);
}

void CDate::keyReleaseEvent ( QKeyEvent * e )
{
   QDateEdit::keyReleaseEvent (e);
}

// GUI related virtual methods

void CDate::View()
{
}

// CCS related virtual methods

void CDate::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
WMETHOD_VOID_EPILOG
#endif
}

void CDate::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
   QString qValue = value;
   ULONG_T lval = qValue.toULong();
   ULONG_T year = 0;
   ULONG_T month = 0;
   ULONG_T day = 0;
   GET_DATE(lval, year, month, day);
   if (year != 0) {
      _Date = QDate(year, month, day);
      setDate(_Date);
   }
}

void CDate::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CDate::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

unsigned long CDate::GetDate()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T date = 0;
   INT_DATE(date, _Date.year(), _Date.month(), _Date.day());
   return date;
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

