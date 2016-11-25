
#ifndef _framework_plugin_h_
#define _framework_plugin_h_

#include <qwidgetplugin.h>
#include "plugin_log.h"

class FrameworkPlugin : public QWidgetPlugin
{
public:
   FrameworkPlugin();
   virtual QStringList keys() const;
   virtual QWidget* create( const QString &classname, QWidget* parent = 0, const char* name = 0 );
   virtual QString group( const QString& ) const;
   virtual QIconSet iconSet( const QString& ) const;
   virtual QString includeFile( const QString& ) const;
   virtual QString toolTip( const QString& ) const;
   virtual QString whatsThis( const QString& ) const;
   virtual bool isContainer( const QString& ) const;
protected:
   void Instantiated();
};

extern const char * _PluginName;

#endif

