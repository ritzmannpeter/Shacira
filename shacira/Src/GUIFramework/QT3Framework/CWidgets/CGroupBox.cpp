
#include "CGroupBox.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CGroupBox, \
                   ICON_SET("designer_groupbox"), \
                   "group box widget")
#endif

CGroupBox::CGroupBox ( QWidget * parent, const char * name, WFlags f)
   : QGroupBox(parent, name) ,
     CWidgetBase(this) 
{
   CONSTRUCT_WIDGET

   setFrameStyle(QGroupBox::Panel | QGroupBox::Raised);
   setLineWidth(1);
}


CGroupBox::~CGroupBox() 
{
}

void CGroupBox::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QGroupBox::mousePressEvent(e);
   }
}

void CGroupBox::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QGroupBox::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CGroupBox::View()
{
}

// CCS related virtual methods

void CGroupBox::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CGroupBox::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CGroupBox::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CGroupBox::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}


