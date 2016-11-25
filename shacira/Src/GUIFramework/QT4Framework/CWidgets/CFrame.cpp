
#include "CFrame.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CFrame, \
                   ICON_SET("frame"), \
                   "frame widget")
#endif

#include <qimage.h>

CFrame::CFrame(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QFrame(parent, f),
#else
   : QFrame(parent, name, f),
#endif
     CWidgetBase(this) 
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
#else
   setFrameStyle(QFrame::Panel | QFrame::Raised);
#endif
   setLineWidth(1);
}

CFrame::~CFrame ( ) 
{
}

void CFrame::ShowPixmap(QPixmap pixmap)
{
#ifdef QT4
   QImage image = pixmap.toImage();
   int w = width();
   int h = height();
   image = image.scaled(w, h);
   QPalette palette;
   palette.setBrush(QPalette::Background, QBrush(image));
   setAutoFillBackground(true);
   this->setPalette(palette);
#else
   QImage image = pixmap.convertToImage();
   int w = width();
   int h = height();
   image = image.scale(w, h);
   setPaletteBackgroundPixmap(image);
#endif
}

void CFrame::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QFrame::mousePressEvent(e);
   }
}

void CFrame::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QFrame::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CFrame::View()
{
}

// CCS related virtual methods

void CFrame::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CFrame::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CFrame::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CFrame::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

