
#include <CWidgetStack.h>
#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CWidgetStack, \
                   ICON_SET("designer_widgetstack"), \
                   "basic widget stack")
#endif


CWidgetStack::CWidgetStack(QWidget * parent, const char * name)
   : QWidgetStack(parent, name),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET
}

CWidgetStack::~CWidgetStack() 
{
}

void CWidgetStack::CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
{
   CheckAppearance(refresh_type, parent_state);
   if (PROPAGATE(refresh_type)) {
      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   } else {
      int dummy = 0;
   }
}

// GUI related virtual methods

void CWidgetStack::View()
{
}

// CCS related virtual methods

void CWidgetStack::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CWidgetStack::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CWidgetStack::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CWidgetStack::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}



