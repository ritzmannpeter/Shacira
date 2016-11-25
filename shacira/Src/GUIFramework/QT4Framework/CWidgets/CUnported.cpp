
#include "CUnported.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(AdditionalWidget, \
                   CUnported, \
                   ICON_SET("unported"), \
                   "widget to show unported widgets")
#endif

CUnported::CUnported(QWidget * parent)
   : QWidget(parent),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
}

CUnported::~CUnported ( ) 
{
}

void CUnported::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QWidget::mousePressEvent(e);
   }
}

void CUnported::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QWidget::mouseReleaseEvent(e);
   }
}

void CUnported::paintEvent(QPaintEvent * e)
{
   QWidget::paintEvent(e);
   QPainter painter(this);
   QRect boundingRect = geometry();
   boundingRect.setWidth(boundingRect.width()-1);
   boundingRect.setHeight(boundingRect.height()-1);
   QColor boundingColor = Qt::blue;
   QColor fillColor = boundingColor.lighter();
   painter.setPen(QPen(boundingColor, 2));
   painter.setBrush(fillColor);
   painter.drawRect(geometry());
}

// GUI related virtual methods

void CUnported::View()
{
}

// CCS related virtual methods

void CUnported::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
#endif
}

void CUnported::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CUnported::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CUnported::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

