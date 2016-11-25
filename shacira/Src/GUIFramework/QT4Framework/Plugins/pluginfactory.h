
#ifndef _pluginfactory_h_
#define _pluginfactory_h_

#include "qt4port.h"

#ifdef _CWIDGET_PLUGIN_
   #define _CWIDGET_EXPORT_      Q_DECL_EXPORT
   #define FACTORY_PREFIX        "SHACIRA"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_CWIDGET_PLUGIN_
         #define _CWIDGET_EXPORT_   Q_DECL_IMPORT
      #else
         #define _CWIDGET_EXPORT_
      #endif
   #else
      #define _CWIDGET_EXPORT_
   #endif
#endif

#ifdef _KEYPAD_PLUGIN_
   #define _KEYPAD_EXPORT_       Q_DECL_EXPORT
   #define FACTORY_PREFIX        "Keypad"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_KEYPAD_PLUGIN_
         #define _KEYPAD_EXPORT_    Q_DECL_IMPORT
      #else
         #define _KEYPAD_EXPORT_
      #endif
   #else
      #define _KEYPAD_EXPORT_
   #endif
#endif

#ifdef _KBDLAYOUT_PLUGIN_
   #define _KBDLAYOUT_EXPORT_     Q_DECL_EXPORT
   #define FACTORY_PREFIX        "Keyboard Layout"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_KBDLAYOUT_PLUGIN_
         #define _KBDLAYOUT_EXPORT_  Q_DECL_IMPORT
      #else
         #define _KBDLAYOUT_EXPORT_
      #endif
   #else
      #define _KBDLAYOUT_EXPORT_
   #endif
#endif

#ifdef _DWIDGET_PLUGIN_
   #define _DWIDGET_EXPORT_      Q_DECL_EXPORT
   #define FACTORY_PREFIX        "Demo"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_DWIDGET_PLUGIN_
         #define _DWIDGET_EXPORT_   Q_DECL_IMPORT
      #else
         #define _DWIDGET_EXPORT_
      #endif
   #else
      #define _DWIDGET_EXPORT_
   #endif
#endif

#ifdef _MOSAICWIDGET_PLUGIN_
   #define _MOSAICWIDGET_EXPORT_      Q_DECL_EXPORT
   #define FACTORY_PREFIX        "Mosaic"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_MOSAICWIDGET_PLUGIN_
         #define _MOSAICWIDGET_EXPORT_   Q_DECL_IMPORT
      #else
         #define _MOSAICWIDGET_EXPORT_
      #endif
   #else
      #define _MOSAICWIDGET_EXPORT_
   #endif
#endif

#ifdef _NWIDGET_PLUGIN_
   #define _NWIDGET_EXPORT_      Q_DECL_EXPORT
   #define FACTORY_PREFIX        "Nela"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_NWIDGET_PLUGIN_
         #define _NWIDGET_EXPORT_   Q_DECL_IMPORT
      #else
         #define _NWIDGET_EXPORT_
      #endif
   #else
      #define _NWIDGET_EXPORT_
   #endif
#endif

#ifdef _PFWIDGET_PLUGIN_
   #define _PFWIDGET_EXPORT_      Q_DECL_EXPORT
   #define FACTORY_PREFIX        "Plateflow"
#else
   #ifdef QT_PLUGIN
      #ifdef _USE_PFWIDGET_PLUGIN_
         #define _PFWIDGET_EXPORT_   Q_DECL_IMPORT
      #else
         #define _PFWIDGET_EXPORT_
      #endif
   #else
      #define _PFWIDGET_EXPORT_
   #endif
#endif

#ifdef QT_PLUGIN

#if QT_VERSION >= 0x050500
   #include <QtUiPlugin/QDesignerExportWidget>
   #include <QtUiPlugin/QDesignerCustomWidgetInterface>
#else
   #include <QtDesigner/QDesignerExportWidget>
   #include <QtDesigner/QDesignerCustomWidgetInterface>
#endif

#include <QtDesigner/QDesignerContainerExtension>
#include <QtCore/qplugin.h>
#include <QApplication>
#include <QtGui/QIcon>
#include "plugin_log.h"

QPixmap iconPixmap(const QString & iconSpecification);

typedef QList<QDesignerCustomWidgetInterface*> PLUGIN_LIST_T;
class WidgetPluginFactory
{
public:
   WidgetPluginFactory(const char * factoryPrefix);
   virtual ~WidgetPluginFactory();
   void addPlugin(QDesignerCustomWidgetInterface * plugin);
   void getPlugins(PLUGIN_LIST_T & plugin_list);
   inline QString factoryPrefix() const {return _factoryPrefix;};
private:
   QString _factoryPrefix;
   PLUGIN_LIST_T _pluginList;
};
WidgetPluginFactory * pluginFactory();

class WidgetPlugins : public QObject, public QDesignerCustomWidgetCollectionInterface
{
   Q_OBJECT
   Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "designer_plugin.json")
#endif
public:
   QList<QDesignerCustomWidgetInterface*> customWidgets() const;
};

#include <map>
using namespace std;
class cDomXML
{
public:
   class Property
   {
      public:
         Property()
            : _disableTranslation(true)
         {
         };
         Property(const Property & right)
            : _disableTranslation(true)
         {
            _name = right._name;
            _defaultValue = right._defaultValue;
            _disableTranslation = right._disableTranslation;
         };
         Property(const QString & name, const QString & defaultValue, bool disableTranslation)
            : _name(name), _defaultValue(defaultValue), _disableTranslation(disableTranslation)
         {
         };
         QString _name;
         QString _defaultValue;
         bool _disableTranslation;
   };
   cDomXML(const QString & className)
      : _className(className)
   {
   };
   void add(const QString & propertyName, const QString & propertyDefaultValue = "", bool disableTranslation = true)
   {
      _propertyMap[propertyName] = Property(propertyName, propertyDefaultValue, disableTranslation);
   };
   void standard()
   {
   };
   QString xml()
   {
      QString xml;
      xml += "<widget class=\"" + _className + "\" name=\"" + _className.toLower() + "\">\n";
      map<QString,Property>::const_iterator i = _propertyMap.begin();
      while (i != _propertyMap.end()) {
         Property p = (*i).second;
         xml += "   <property name=\"" + p._name + "\">\n";
         if (p._disableTranslation) {
            xml += "      <string notr=\"true\"></string>\n";
         }
         xml += "   </property>\n";
         i++;
      }
      xml += "</widget>\n";
      return xml;
   };
private:
   QString _className;
   map<QString,Property> _propertyMap;
};

#include <qstring.h>
#include <qbytearray.h>
#include <qicon.h>

#define ICON_SET(name)     name

// widget group names
#define DisplayWidget      1
#define ContainerWidget    2
#define InputWidget        3
#define ButtonWidget       4
#define ViewWidget         5
#define FormWidget         6
#define AdditionalWidget   7

inline QString groupName(int widgetType, const QString & factoryPrefix)
{
   QString group = factoryPrefix;
   group += ' ';
   switch (widgetType) {
   case DisplayWidget:
      group += "Display Widgets";
      break;
   case ContainerWidget:
      group += "Containers";
      break;
   case InputWidget:
      group += "Input Widgets";
      break;
   case ButtonWidget:
      group += "Button Widgets";
      break;
   case ViewWidget:
      group += "Views";
      break;
   case FormWidget:
      group += "Forms";
      break;
   case AdditionalWidget:
      group += "Additional Widgets";
      break;
   default:
      group += "unknow widget type ";
      group += QString::number(widgetType);
      break;
   }
   return group;
}

inline bool typeIsContainer(int widgetType)
{
   if (widgetType == FormWidget) {
      return true;
   }
   if (widgetType == ContainerWidget) {
      return true;
   }
   return false;
}

#define SH_PLUGIN_REGISTER(wtype,wclass,iconSpec,description) \
class  Plugin##wclass : public QDesignerCustomWidgetInterface \
{ \
   Q_INTERFACES(QDesignerCustomWidgetInterface) \
public: \
   Plugin##wclass() : _initialized(false), _widgetType(0) {initialize(NULL);} \
   bool isContainer() const {return typeIsContainer(_widgetType);} \
   bool isInitialized() const {return _initialized;} \
   QIcon icon() const \
   { \
      return iconPixmap(iconSpec); \
   } \
   QString codeTemplate() const {return QString();} \
   QString whatsThis() const {return QString(description);} \
   QString toolTip() const {return QString(description);} \
   QString group() const {return _groupName;} \
   void initialize(QDesignerFormEditorInterface *) { \
      PluginPrintf("initialize plugin %s qApp %p", description, qApp); \
      if (_initialized) { \
         return; \
      } \
      _widgetType = wtype; \
      _className = #wclass; \
      _groupName = groupName(_widgetType, pluginFactory()->factoryPrefix()); \
      _initialized = true; \
      pluginFactory()->addPlugin(this); \
   } \
   QString name() const {return #wclass;} \
   QString includeFile() const {QString ifile = QString(#wclass) + QString(".h"); return ifile.toLower();} \
   QWidget * createWidget(QWidget *parent) { \
      wclass * widget = new wclass(parent); \
      return widget; \
   } \
   QString domXml() const \
   { \
      cDomXML dom(#wclass); \
      return dom.xml(); \
   }; \
private: \
   int _widgetType; \
   bool _initialized; \
   QString _className; \
   QString _groupName; \
}; \
Plugin##wclass _VariablePlugin##wclass;

#define DEFAULT_ICON    "default"
#define QT_PLUGIN_REGISTER(wclass,include_file,iconSpec,group_name,tool_tip,whats_this,is_container) \
class  Plugin##wclass : public QDesignerCustomWidgetInterface \
{ \
   Q_INTERFACES(QDesignerCustomWidgetInterface) \
public: \
   Plugin##wclass() : _initialized(false), _widgetType(0) {initialize(NULL);} \
   bool isContainer() const {return is_container;} \
   bool isInitialized() const {return _initialized;} \
   QIcon icon() const \
   { \
      return iconPixmap(iconSpec); \
   } \
   QString codeTemplate() const {return QString();} \
   QString whatsThis() const {return (whats_this == NULL) ? "?" : whats_this;} \
   QString toolTip() const {return (tool_tip == NULL) ? "?" : tool_tip;}; \
   QString group() const {return group_name;} \
   void initialize(QDesignerFormEditorInterface *) { \
      PluginPrintf("initialize plugin %s qApp %p", #wclass, qApp); \
      if (_initialized) { \
         return; \
      } \
      _widgetType = AdditionalWidget; \
      _className = #wclass; \
      _groupName = groupName(_widgetType, pluginFactory()->factoryPrefix()); \
      _initialized = true; \
      pluginFactory()->addPlugin(this); \
   } \
   QString name() const {return #wclass;} \
   QString includeFile() const {QString ifile = QString(#wclass) + QString(".h"); return ifile.toLower();} \
   QWidget * createWidget(QWidget *parent) { \
      wclass * widget = new wclass(parent); \
      return widget; \
   } \
   QString domXml() const \
   { \
      cDomXML dom(#wclass); \
      return dom.xml(); \
   }; \
private: \
   int _widgetType; \
   bool _initialized; \
   QString _className; \
   QString _groupName; \
}; \
Plugin##wclass _VariablePlugin##wclass;

#else

#define SH_PLUGIN_REGISTER(wtype,wclass,img,description)
#define QT_PLUGIN_REGISTER(wclass,include_file,icon_set,group_name,tool_tip,whats_this,is_container)

#endif // QT_PLUGIN

#endif // _pluginfactory_h_



