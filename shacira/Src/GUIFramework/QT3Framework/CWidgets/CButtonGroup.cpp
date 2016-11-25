
#include "CButtonGroup.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ContainerWidget,
                   CButtonGroup, \
                   ICON_SET("designer_buttongroup"), \
                   "button group widget")
#endif


CButtonGroup::CButtonGroup(QWidget * parent, const char * name)
   : QButtonGroup(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
}

CButtonGroup::~CButtonGroup() 
{
}

void CButtonGroup::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QButtonGroup::mousePressEvent(e);
   }
}

void CButtonGroup::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QButtonGroup::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CButtonGroup::View()
{
}

// CCS related virtual methods

void CButtonGroup::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CButtonGroup::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
}

void CButtonGroup::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
}

void CButtonGroup::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}


