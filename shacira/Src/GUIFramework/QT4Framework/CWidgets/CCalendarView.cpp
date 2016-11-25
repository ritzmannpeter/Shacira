
#include "CCalendarView.h"
#include "CAppFrame.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CCalendarView, \
                   ICON_SET("calendarwidget"), \
                   "widget to display and pick date values")
#endif

CCalendarView::CCalendarView(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
   : QCalendarWidget(parent),
     CWidgetBase(this)
{
   setObjectName(name);
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;
}

CCalendarView::~CCalendarView( ) 
{
}

void CCalendarView::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QCalendarWidget::mousePressEvent(e);
   }
}

void CCalendarView::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QCalendarWidget::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CCalendarView::View()
{
}

// CCS related virtual methods

void CCalendarView::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
}

void CCalendarView::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void CCalendarView::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CCalendarView::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CCalendarView::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

