
#include "CWidget.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CWidget, \
                   ICON_SET("widget"), \
                   "basic widget")
#endif

CWidget::CWidget(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QWidget(parent, f),
#else
   : QWidget(parent, name, f),
#endif
     CWidgetBase(this)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
}

CWidget::~CWidget ( ) 
{
}

void CWidget::showEvent(QShowEvent * e)
{
   QWidget::showEvent(e);
}

void CWidget::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QWidget::mousePressEvent(e);
   }
}

void CWidget::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QWidget::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CWidget::View()
{
}

// CCS related virtual methods

void CWidget::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
#endif
}

void CWidget::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CWidget::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CWidget::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}
