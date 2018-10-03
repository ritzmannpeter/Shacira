
#include "pluginfactory.h"
#include <qplugin.h>
#include "plugin_log.h"

class QDesignerFormEditorInterface;

QPixmap iconPixmap(const QString & iconSpecification)
{
   QString spec = ":/designer/designer-images/";
   spec += iconSpecification;
   spec += ".png";
   QPixmap pm = QPixmap(spec);
   if (pm.isNull()) {
      pm = QPixmap(":/designer/designer-images/unknown.png");
   }
   return pm;
}

static WidgetPluginFactory * _pluginFactory = NULL;
WidgetPluginFactory * pluginFactory()
{
   if (_pluginFactory == NULL) {
      QString factoryPrefix = FACTORY_PREFIX;
      _pluginFactory = new WidgetPluginFactory(factoryPrefix.toStdString().c_str());
      PluginPrintf("pluginFactory %s instantiated %p: qApp %p", factoryPrefix.toStdString().c_str(), _pluginFactory, qApp);
   }
   return _pluginFactory;
}

WidgetPluginFactory::WidgetPluginFactory(const char * pluginName)
   : _factoryPrefix(pluginName)
{
}

WidgetPluginFactory::~WidgetPluginFactory()
{
}

void WidgetPluginFactory::addPlugin(QDesignerCustomWidgetInterface * plugin)
{
   _pluginList << plugin;
   PluginPrintf("AddPlugin(%s,%s,%p)", plugin->name().toStdString().c_str(), plugin->group().toStdString().c_str(), plugin);
}

void WidgetPluginFactory::getPlugins(PLUGIN_LIST_T & plugin_list)
{
   PluginPrintf("GetPlugins ... %d", plugin_list.size());
   plugin_list = _pluginList;
   PLUGIN_LIST_T::const_iterator i = plugin_list.constBegin();
   while (i != plugin_list.constEnd()) {
      QDesignerCustomWidgetInterface * plugin = (*i);
      PluginPrintf("GetPlugins(%s,%s,%p)", plugin->name().toStdString().c_str(), plugin->group().toStdString().c_str(), plugin);
      i++;
   }
   PluginPrintf("GetPlugins %d done", plugin_list.size());
}

QList<QDesignerCustomWidgetInterface*> WidgetPlugins::customWidgets() const
{
   QList<QDesignerCustomWidgetInterface *> plugins;
   pluginFactory()->getPlugins(plugins);
   return plugins;
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN(WidgetPlugins)
#endif
