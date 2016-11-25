
#ifndef _cformbuilder_h_
#define _cformbuilder_h_

#include <qapplication.h>
#include <QWidget>

#if QT_VERSION >= QT_VERSION_CHECK(5,5,0)
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#else
#include <QtDesigner/QDesignerCustomWidgetInterface>
#endif

#include <QFile>
#include <QStringList>
#include <QtUiTools/QUiLoader>
#include <QtDesigner/QFormBuilder>
#include <map>
using namespace std;

class WidgetInfo
{
public:
   WidgetInfo()
      : widget(NULL),
        metaObject(NULL),
        widgetInterface(NULL),
        isContainer(false)
   {
   };
   WidgetInfo(const WidgetInfo & right)
      : widget(right.widget),
        metaObject(right.metaObject),
        widgetInterface(right.widgetInterface),
        isContainer(right.isContainer)
   {
   };
   QWidget * widget;
   const QMetaObject * metaObject;
   const QDesignerCustomWidgetInterface* widgetInterface;
   bool isContainer;
   QString className;
   QString superClassName;
};
typedef map<QString,WidgetInfo> WIDGET_INFO_MAP_T;

class cFormBuilder : public QFormBuilder
{
public:
   cFormBuilder();
   virtual ~cFormBuilder();
   bool isCustomWidget(const QString & className);
   bool isContainer(const QString & className);
   QString baseClass(const QString & className);
   QWidget * createWidget(const QString & className);
   void initialize();
protected:
   WIDGET_INFO_MAP_T _widgetInfoMap;
   QUiLoader _uiLoader;
};

#endif // _cformbuilder_h_
