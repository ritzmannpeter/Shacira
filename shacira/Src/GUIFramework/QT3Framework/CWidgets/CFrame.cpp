
#include "CFrame.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CFrame, \
                   ICON_SET("designer_frame"), \
                   "frame widget")
#endif

#include <qimage.h>

CFrame::CFrame(QWidget * parent, const char * name, WFlags f)
   : QFrame(parent, name, f),
     CWidgetBase(this) 
{
   CONSTRUCT_WIDGET

   setFrameStyle(QFrame::Panel | QFrame::Raised);
   setLineWidth(1);
}

CFrame::~CFrame ( ) 
{
}

void CFrame::ShowPixmap(QPixmap pixmap)
{
   QImage image = pixmap.convertToImage();
   int w = width();
   int h = height();
   image = image.scale(w, h);
   setPaletteBackgroundPixmap(image);
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

