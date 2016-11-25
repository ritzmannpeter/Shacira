
#include "CFixText.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CFixText, \
                   ICON_SET("label"), \
                   "static text widget")
#endif

#include <qimage.h>

CFixText::CFixText(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
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
   _IndexValue = -1;
   setMinimumHeight(getScaledHeight(this, 25));
#ifndef QT_PLUGIN
   if (Flag(CHG_TXTWIDGET_BGROUNDCOLOR)) {
      setProperty("chgTxtWidgetBackgroundColor", true);
   }
#endif
}

CFixText::~CFixText ( ) 
{
}

void CFixText::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QLabel::mousePressEvent(e);
   }
}

void CFixText::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QLabel::mouseReleaseEvent(e);
   }
}

void CFixText::ShowPixmap(QPixmap pixmap)
{
#ifdef QT4
   QImage image = pixmap.toImage();
   int w = width();
   int h = height();
   image = image.scaled(w, h);
   QPixmap scaledPixmap = QPixmap::fromImage(image);
   setPixmap(scaledPixmap);
#else
   QImage image = pixmap.convertToImage();
   int w = width();
   int h = height();
   image = image.scale(w, h);
   setPixmap(image);
#endif
}

void CFixText::ValueChange(QString value, int index)
{
   if (index == -1 ||
       index == _IndexValue) {
      setText(value);
   }
}

// GUI related virtual methods

void CFixText::View()
{
#ifndef QT_PLUGIN
#endif
}

// CCS related virtual methods

void CFixText::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CFixText::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
}

void CFixText::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CFixText::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
#endif
}

