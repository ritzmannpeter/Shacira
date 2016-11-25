
#include "CComposedStack.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(ContainerWidget,
                   CComposedStack, \
                   ICON_SET("designer_widgetstack"), \
                   "widget stack")
#endif

#include <qobjectlist.h>

CComposedStack::CComposedStack(QWidget * parent, const char * name)
   : CFrame(parent, name)
{
   CONSTRUCT_WIDGET
   _Stack = NULL;
   _ActGraphic = NULL;
}

CComposedStack::~CComposedStack() 
{
}

void CComposedStack::CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
{
   // PR 29.03.05 must be checked and verified
   CheckAppearance(refresh_type, parent_state);
   if (PROPAGATE(refresh_type)) {
      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   } else {
      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
      // int dummy = 0
   }
}

void CComposedStack::RaiseWidget(int id)
{
   if (_Stack != NULL) {
      _Stack->raiseWidget(id);
   }
}

void CComposedStack::RaiseWidget(QWidget * widget)
{
   if (_Stack != NULL) {
      _Stack->raiseWidget(widget);
   }
}

void CComposedStack::PreWidgetShow(QWidget * widget)
{
   emit(AboutToShow(widget));
   CProcGraphic * graphic = SearchGraphic(widget);
   if (graphic != NULL) {
      _ActGraphic = graphic;
//      connect(graphic, SIGNAL(Refreshed(QWidget*)), this, SLOT(GraphicRefreshSlot(QWidget*)));
      emit GraphicRefreshSignal(graphic);
   }
}

void CComposedStack::GraphicRefreshSlot(QWidget * widget)
{
   if (widget == NULL) {
      return;
   }
   if (widget->inherits("CProcGraphic")) {
      if (_ActGraphic == NULL) {
         _ActGraphic = widget;
         emit GraphicRefreshSignal(widget);
      } else {
         if (widget = _ActGraphic) {
            emit GraphicRefreshSignal(widget);
         }
      }
   }
}

// GUI related virtual methods

void CComposedStack::View()
{
}

// CCS related virtual methods

void CComposedStack::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   _Stack = SearchStack(this);
   if (_Stack != NULL) {
      QWidget * widget = _Stack->visibleWidget();
      if (widget != NULL) {
         PreWidgetShow(widget);
      }
   }
   if (connect(_Stack, SIGNAL(aboutToShow(QWidget*)), this, SLOT(PreWidgetShow(QWidget*)))) {
   } else {
   }
   ConnectGraphicWidgets(this);
}

void CComposedStack::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                                 UCHAR_T data_type, ULONG_T size)
{
}

void CComposedStack::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                                 UCHAR_T data_type, ULONG_T size)
{
}

void CComposedStack::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

QWidgetStack * CComposedStack::SearchStack(QWidget * widget)
{
   const QObjectList * children = widget->children();
   if (children == NULL) {
      return NULL;
   }
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) {
      return NULL;
   }
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("QWidgetStack")) {
            return (QWidgetStack*)child;
         } else {
			   return SearchStack(child);
		   }
      }
      ++i;
   }
   return NULL;
}

CProcGraphic * CComposedStack::SearchGraphic(QWidget * widget)
{
   const QObjectList * children = widget->children();
   if (children == NULL) {
      return NULL;
   }
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) {
      return NULL;
   }
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("CProcGraphic")) {
            return (CProcGraphic*)child;
         } else {
			   return SearchGraphic(child);
		   }
      }
      ++i;
   }
   return NULL;
}

void CComposedStack::ConnectGraphicWidgets(QWidget * widget)
{
   const QObjectList * children = widget->children();
   if (children == NULL) {
      return;
   }
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) {
      return;
   }
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("CProcGraphic")) {
            CProcGraphic * graphic = (CProcGraphic*)child;
            connect(graphic, SIGNAL(Refreshed(QWidget*)), this, SLOT(GraphicRefreshSlot(QWidget*)));
         } else {
			   ConnectGraphicWidgets(child);
		   }
      }
      ++i;
   }
}



