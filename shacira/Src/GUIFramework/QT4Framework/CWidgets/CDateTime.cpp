
#include "CDateTime.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CDateTime, \
                   ICON_SET("datetimeedit"), \
                   "date / time edit widget")
#endif


#ifndef QT_PLUGIN
#include "System/cTimeObject.h"
#endif

CDateTime::CDateTime(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QDateTimeEdit(parent),
#else
   : QDateTimeEdit(parent, name),
#endif
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
   _PlausFuncRef = NULL;
   _UserFuncRef = NULL;
}

CDateTime::~CDateTime() 
{
}

void CDateTime::SetTime(unsigned long lval)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cTimeObject t(lval);
   int year = t.Get(cTimeObject::YEAR);
   int month = t.Get(cTimeObject::MONTH);
   int day = t.Get(cTimeObject::DAY);
   int hour = t.Get(cTimeObject::HOUR);
   int minute = t.Get(cTimeObject::MINUTE);
   int second = t.Get(cTimeObject::SECOND);
   QTime qtime(hour, minute, second);
   QDate qdate(year, month, day);
   QDateTime qdatetime(qdate, qtime);
   setDateTime(qdatetime);
WMETHOD_VOID_EPILOG
#endif
}

void CDateTime::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QDateTimeEdit::mousePressEvent(e);
   }
}

void CDateTime::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QDateTimeEdit::mouseReleaseEvent (e);
   }
}

void CDateTime::focusInEvent ( QFocusEvent * e)
{
   QDateTimeEdit::focusInEvent (e);
}

void CDateTime::focusOutEvent ( QFocusEvent * e)
{
   QDateTimeEdit::focusOutEvent (e);
}

void CDateTime::keyReleaseEvent ( QKeyEvent * e )
{
   QDateTimeEdit::keyReleaseEvent (e);
}

// GUI related virtual methods

void CDateTime::View()
{
}

// CCS related virtual methods

void CDateTime::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSCreateFuncRef(_PlausFuncSpec, _PlausFuncRef);
   CCSCreateFuncRef(_UserFuncSpec, _UserFuncRef);
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
WMETHOD_VOID_EPILOG
#endif
}

void CDateTime::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
   QString qValue = value;
   ULONG_T lval = qValue.toULong();
   SetTime(lval);
}

void CDateTime::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CDateTime::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

unsigned long CDateTime::GetTime()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG

WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}


