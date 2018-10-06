
#include "cformbuilder.h"
#include <QDir>
#include <QResource>

cFormBuilder::cFormBuilder()
{
}

cFormBuilder::~cFormBuilder()
{
}

bool cFormBuilder::isCustomWidget(const QString & className)
{
   initialize();
   WIDGET_INFO_MAP_T::const_iterator i = _widgetInfoMap.find(className);
   if (i != _widgetInfoMap.cend()) {
      return true;
   } else {
      return false;
   }
}

bool cFormBuilder::isContainer(const QString & className)
{
   initialize();
   WIDGET_INFO_MAP_T::const_iterator i = _widgetInfoMap.find(className);
   if (i != _widgetInfoMap.cend()) {
      return (*i).second.isContainer;
   } else {
      return false;
   }
}

QString cFormBuilder::baseClass(const QString & className)
{
   initialize();
   WIDGET_INFO_MAP_T::const_iterator i = _widgetInfoMap.find(className);
   if (i != _widgetInfoMap.cend()) {
      return (*i).second.superClassName;
   } else {
      return QString();
   }
}

QWidget * cFormBuilder::createWidget(const QString & className)
{
   QWidget * widget = _uiLoader.createWidget(className);
   return widget;
#ifdef lassma
   // does not return instances o Qt widgets
   initialize();
   WIDGET_INFO_MAP_T::const_iterator i = _widgetInfoMap.find(className);
   if (i != _widgetInfoMap.cend()) {
      return (*i).second.widget;
   } else {
      return NULL;
   }
#endif
}

void cFormBuilder::initialize()
{
   if (_widgetInfoMap.empty()) {
      QList<QDesignerCustomWidgetInterface*> customWidgetList = customWidgets();
      QList<QDesignerCustomWidgetInterface*>::const_iterator cw = customWidgetList.constBegin();
      while (cw != customWidgetList.constEnd()) {
         QDesignerCustomWidgetInterface* widgetInterface = (*cw);
         WidgetInfo widgetInfo;
         QString className = widgetInterface->name();
         widgetInfo.className = className;
         widgetInfo.widgetInterface = widgetInterface;
         QWidget * widget = _uiLoader.createWidget(className);
         if (widget != NULL) {
            widgetInfo.widget = widget;
            QObject * object = static_cast<QWidget*>(widget);
            const QMetaObject * metaObject = object->metaObject();
            if (metaObject != NULL) {
               widgetInfo.metaObject = metaObject;
               const QMetaObject * superClass = metaObject->superClass();
               if (superClass != NULL) {
                  widgetInfo.superClassName = superClass->className();
               }
               widgetInfo.isContainer = widgetInterface->isContainer();
               _widgetInfoMap[className] = widgetInfo;
            } else {
               int dummy = 0;
            }
         } else {
            int dummy = 0;
         }
         cw++;
      }
   }
}

