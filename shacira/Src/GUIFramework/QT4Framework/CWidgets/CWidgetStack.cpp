
#include <CWidgetStack.h>
#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ContainerWidget, \
                   CWidgetStack, \
                   "widgetstack", \
                   "basic widget stack")
#endif


CWidgetStack::CWidgetStack(QWidget * parent, const char * name)
#ifdef QT4
   : CWIDGETSTACK_BASE_CLASS(parent),
     CWidgetBase(this),
     _PreventFromPropagation(false)
#else
   : CWIDGETSTACK_BASE_CLASS(parent, name),
     CWidgetBase(this)
#endif
{
   CONSTRUCT_WIDGET
}

CWidgetStack::~CWidgetStack() 
{
}

void CWidgetStack::CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
{
   CheckAppearance(refresh_type, parent_state);
   if (_PreventFromPropagation) {
      if (PROPAGATE(refresh_type)) {
         emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
      } else {
         int dummy = 0;
      }
   } else {
      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
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


#ifdef QT4
void CWidgetStack::raiseWidget(int index)
{
   this->setCurrentIndex(index);
}

void CWidgetStack::raiseWidget(QWidget * widget)
{
   this->setCurrentWidget(widget);
}

QWidget * CWidgetStack::visibleWidget() const
{
   return this->currentWidget();
}

#endif

