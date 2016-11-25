#include "dplugin.h"
#include "images/embedded_images.h"
#include "dactvalue.h"
#include "dframe.h"

DemoWidgetPlugin::DemoWidgetPlugin()
{
}

QStringList DemoWidgetPlugin::keys() const
{
   QStringList list;

   list << "DActValue";
   list << "DFrame";

   return list;
}

QWidget* DemoWidgetPlugin::create( const QString &key, QWidget* parent, const char* name )
{
   if (key == "DActValue") {
      return new DActValue(parent, name);
   } else if (key == "DFrame") {
      return new DFrame(parent, name);
   } else {
      return NULL;
   }
}

QString DemoWidgetPlugin::group( const QString& feature ) const
{
   return "DemoWidgets";
}

QIconSet DemoWidgetPlugin::iconSet( const QString& feature) const
{
   return QIconSet(QPixmap(default_icon_pixmap));
   if (feature == "DActValue") {
      return QIconSet(QPixmap(qembed_findImage("dactvalue")));
   } else if (feature == "DFrame") {
       return QIconSet (QPixmap(qembed_findImage("dframe")));
   } else {
      return QIconSet(QPixmap(qembed_findImage ("cunknown")));
   }
}

QString DemoWidgetPlugin::includeFile( const QString& feature ) const
{
   if  (feature == "DActValue") {
      return "dactvalue.h";
   } else if (feature == "DFrame") {
      return "dframe.h";
   } else {
      return QString::null;
   }
}

QString DemoWidgetPlugin::toolTip(const QString& feature) const
{
   if (feature == "DActValue") {
      return "Act value widget for denmonstration purposes";
   } else if (feature == "MFrame") {
      return "Act value widget for denmonstration purposes";
   } else {
      return QString::null;
   }
}

QString DemoWidgetPlugin::whatsThis( const QString& feature ) const
{
   return toolTip(feature);
}

bool DemoWidgetPlugin::isContainer( const QString& feature ) const
{
   if  (feature == "DFrame") {
      return true;
   } else {
      return false;
   }
}

Q_EXPORT_PLUGIN(DemoWidgetPlugin)

