
#include "FrameworkPlugin.h"
#include "cQtPluginRegistry.h"
#include "embedded_images.h"

FrameworkPlugin::FrameworkPlugin()
{
}

QStringList FrameworkPlugin::keys() const
{
   PluginPrintf("%s: get keys\n", (const char *)_PluginName);
   QStringList list = cQtPluginRegistry::getKeys();
   PluginPrintf("%s: returned %d keys\n", (const char *)_PluginName, (int)list.size());
   return list;
}

QWidget* FrameworkPlugin::create(const QString &feature, QWidget* parent, const char* name)
{
   QWidget * widget = cQtPluginRegistry::getDescr(feature)->factory(parent, name);
   PluginPrintf("%s: created widget %s\n",
                (const char *)_PluginName, 
                (const char *)feature);
   return widget;
}

QString FrameworkPlugin::group(const QString& feature) const
{
   QString widget_group = cQtPluginRegistry::getDescr(feature)->getGroup();
   PluginPrintf("%s: group of %s is %s \n",
                (const char *)_PluginName, 
                (const char *)feature,
                (const char *)widget_group);
   return widget_group;
}

QIconSet FrameworkPlugin::iconSet(const QString& feature) const
{
   QIconSet icon_set = cQtPluginRegistry::getDescr(feature)->getIconSet();
   if (icon_set.isNull()) {
      QString icon_name = cQtPluginRegistry::getDescr(feature)->getIconName();
      if (icon_name.length() > 0) {
         icon_set = QIconSet(qembed_findImage(icon_name));
      }
   }
   if (icon_set.isNull()) {
      icon_set = QIconSet(default_icon_pixmap);
   }
   return icon_set;
}

QString FrameworkPlugin::includeFile(const QString& feature) const
{
   QString include_file = cQtPluginRegistry::getDescr(feature)->getIncludeFile();
   return include_file;
}

QString FrameworkPlugin::toolTip(const QString& feature) const
{
   QString tip = cQtPluginRegistry::getDescr(feature)->getToolTip();
   if (tip.isNull()) {
      tip = feature;
   }
   return tip;
}

QString FrameworkPlugin::whatsThis(const QString& feature) const
{
   return toolTip(feature);
}

bool FrameworkPlugin::isContainer(const QString& feature) const
{
   bool is_container = cQtPluginRegistry::getDescr(feature)->isContainer();
   return is_container;
}

void FrameworkPlugin::Instantiated()
{
   PluginPrintf("%s: instantiated\n", (const char *)_PluginName);
}

#if defined(_WIN32x)

#include <windows.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
   char dll_name[0x100] = {0};
   sprintf(dll_name, "unknown");
   char reason[0x100] = {0};
   switch (ul_reason_for_call) {
   case DLL_PROCESS_ATTACH:
      sprintf(reason, "process_attach");
      break;
   case DLL_THREAD_ATTACH:
      sprintf(reason, "thread_attach");
      break;
   case DLL_THREAD_DETACH:
      sprintf(reason, "thread_detach");
      break;
   case DLL_PROCESS_DETACH:
      sprintf(reason, "process_detach");
      break;
   }
   PluginPrintf("%s: dll %s\n", _PluginName, reason);
   return TRUE;
}

#endif

