
#include "CComposedStack.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ContainerWidget,
                   CComposedStack, \
                   ICON_SET("widgetstack"), \
                   "widget stack")
#endif

#ifndef QT4
#include <qobjectlist.h>
#endif

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
   emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
}

void CComposedStack::RaiseWidget(int id)
{
   if (_Stack != NULL) {
#ifdef QT4
      _Stack->setCurrentIndex(id);
#else
      _Stack->raiseWidget(id);
#endif
   }
}

void CComposedStack::RaiseWidget(QWidget * widget)
{
   if (_Stack != NULL) {
#ifdef QT4
      _Stack->setCurrentWidget(widget);
#else
      _Stack->raiseWidget(widget);
#endif
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

#ifdef QT4

void CComposedStack::PreWidgetShow(int index)
{
   QWidget * widget = _Stack->widget(index);
   emit(AboutToShow(widget));
   CProcGraphic * graphic = SearchGraphic(widget);
   if (graphic != NULL) {
      _ActGraphic = graphic;
//      connect(graphic, SIGNAL(Refreshed(QWidget*)), this, SLOT(GraphicRefreshSlot(QWidget*)));
      emit GraphicRefreshSignal(graphic);
   }
}

#endif

// GUI related virtual methods

void CComposedStack::View()
{
}

// CCS related virtual methods

void CComposedStack::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   _Stack = SearchStack(this);
   if (_Stack != NULL) {
#ifdef QT4
      QWidget * widget = _Stack->currentWidget();
#else
      QWidget * widget = _Stack->visibleWidget();
#endif
      if (widget != NULL) {
         PreWidgetShow(widget);
      }
   }
#ifdef QT4
   connect(_Stack, SIGNAL(currentChanged(int)), this, SLOT(PreWidgetShow(int)));
#else
   connect(_Stack, SIGNAL(aboutToShow(QWidget*)), this, SLOT(PreWidgetShow(QWidget*)));
#endif
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

#ifdef QT4
QStackedWidget * CComposedStack::SearchStack(QWidget * widget)
#else
QWidgetStack * CComposedStack::SearchStack(QWidget * widget)
#endif
{
#ifdef QT4
   const QObjectList children = widget->children();
   QList<QObject*>::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("QStackedWidget")) {
            return static_cast<QStackedWidget*>(child);
         } else {
			   return SearchStack(child);
		   }
      }
      ++i;
   }
#else
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
#endif
   return NULL;
}

CProcGraphic * CComposedStack::SearchGraphic(QWidget * widget)
{
#ifdef QT4
   const QObjectList children = widget->children();
   QList<QObject*>::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
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
#else
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
#endif
   return NULL;
}

void CComposedStack::ConnectGraphicWidgets(QWidget * widget)
{
#ifdef QT4
   const QObjectList children = widget->children();
   QList<QObject*>::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
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
#else
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
#endif
}



