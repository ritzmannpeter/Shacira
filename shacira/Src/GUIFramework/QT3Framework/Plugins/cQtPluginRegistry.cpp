// ==========================================================================
// qt_plugin_register.cpp
//
// cQtPluginRegister - Manager fuer automatisch registrierte Widgets
//
// ==========================================================================


#include "cQtPluginRegistry.h"


// Statische Variablen der Klasse
QStringList * cQtPluginRegistry::_key_list = 0;
QMap<QString, cQtPluginDescr*> * cQtPluginRegistry::_descr_map = 0;


// Evtl. notwendige Erweiterung: addWidget berücksichtigt einen Filter, dass
// bestimmte Widget-Gruppen *nicht* registriert werden. Beispiel: MosaicPlugin
// exportiert nicht die Widgets, die bereits in CWidget enthalten sind.
// ODER: MosaicPlugin ERSETZT CWidget-Plugin?

void cQtPluginRegistry::addWidget(cQtPluginDescr *plugin_descr)
{
   CREATE_KEY_LIST();
   CREATE_DESCR_MAP();
   QString key = plugin_descr->getKey(); 
   (*_key_list) << key;
   (*_descr_map)[key] = plugin_descr;
}


