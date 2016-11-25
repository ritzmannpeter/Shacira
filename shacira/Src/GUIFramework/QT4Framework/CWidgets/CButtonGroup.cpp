
#include "CButtonGroup.h"

#ifdef QT4
#include <QLayout>
#endif

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ContainerWidget,
                   CButtonGroup, \
                   ICON_SET("groupbox"), \
                   "button group widget")
#endif

CButtonGroup::CButtonGroup(QWidget * parent, const char * name)
#ifdef QT4
   : BUTTONGROUP_BASE_CLASS(parent),
     CWidgetBase(this)
#else
   : BUTTONGROUP_BASE_CLASS(parent, name),
     CWidgetBase(this)
#endif
{
   CONSTRUCT_WIDGET
}

CButtonGroup::~CButtonGroup() 
{
}

void CButtonGroup::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      BUTTONGROUP_BASE_CLASS::mousePressEvent(e);
   }
}

void CButtonGroup::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      BUTTONGROUP_BASE_CLASS::mouseReleaseEvent(e);
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

#ifdef QT4

int CButtonGroup::insideMargin() const
{
   QLayout * layout = this->layout();
   int left = 0;
   
   if (layout) {
      int top;
      int right; 
      int bottom;
      layout->getContentsMargins(&left, &top, &right, &bottom);
   }

   return left;
}

int CButtonGroup::insideSpacing() const
{
   QLayout * layout = this->layout();

   return layout ? layout->spacing() : 0;
}

#endif

