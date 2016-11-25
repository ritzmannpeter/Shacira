/**
 * @file  qt_plugin_register.h
 *
 * @brief Automatische Widget-Registrierung in einem Qt Designer Plugin.
 */

// ===========================================================================
// qt_plugin_register.h
//
// Automatische Registrierung von Widgets in einem Plugin fuer den Qt Designer.
//
// cQtPluginDescr - Beschreibung eines Widgets (Name der Klassen, Include-
//    Datei, Icon, Widget-Gruppe etc.)
//
// cQtPluginRegistry - Manager der die Widget-Beschreibungen verwaltet (und
//    dann der von QWidgetPlugin abgeleiteten Klasse zur Verfuegung stellt)
//
// QT_PLUGIN_REGISTER - Macro um eine Widget-Beschreibung quick and easy
//    zu erstellen und zu automatisch zu registrieren.
//
// ===========================================================================

#ifndef _cqtpluginregistry_h_
#define _cqtpluginregistry_h_

#ifdef QT_PLUGIN
#define SH_QT_WIDGET_PLUGIN_EXPORT __declspec(dllexport)
#else
///#define SH_QT_WIDGET_PLUGIN_EXPORT __declspec(dllimport)
#define SH_QT_WIDGET_PLUGIN_EXPORT
#endif

// Nur wenn das Qt Designer Plugin uebersetzt wird
#ifdef QT_PLUGIN

#include <qiconset.h>
#include <qstringlist.h>
#include <qmap.h>
#include "default_icon.h"

// Notwendigen Forwaertsbezug aufloesen
class cQtPluginDescr;

#define CREATE_KEY_LIST() \
   if (_key_list == 0) { \
      _key_list = new QStringList; \
   }

#define CREATE_DESCR_MAP() \
   if (_descr_map == 0) { \
      _descr_map = new QMap<QString, cQtPluginDescr*>; \
   }

/**
 * @class cQtPluginRegistry
 * 
 * @brief Manager der die Widget-Beschreibungen verwaltet.
 *
 * Alle Methoden und Attribute dieser Klasse sind statisch, es ist eine sehr
 * primitive Implemntierung eines Singletons.
 * Die vom Manager gesammelten Daten (Registrierte Widget-Beschreibungen)
 * werden dann vom Plugin-Interface abgefragt.
 */
class cQtPluginRegistry
{
public:
   /// Widget-Beschreibung hinzufuegen
   static void addWidget(cQtPluginDescr *plugin_descr);

   /// Liste der Widget-Namen
   static QStringList getKeys()
   { 
      CREATE_KEY_LIST();
      return *_key_list; 
   }

   /// Widget-Beschreibung zu einem Widget-Namen
   static cQtPluginDescr *getDescr(const QString &key) 
   { 
      CREATE_DESCR_MAP();
      return (*_descr_map)[key]; 
   }

private:
   // Widget-Namensliste
   static QStringList * _key_list;
   // Map mit Widget-Beschreibungen zu den Widget-Namen
   static QMap<QString, cQtPluginDescr*> * _descr_map;
};




/**
 * @class cQtPluginDescr
 * 
 * @brief Beschreibung eines Widgets.
 *
 * Dieses Objekt hält alle Informationen, die vom Plugin-Interface zu einem
 * einzelnen Widget benötigt werden.
 */
enum WidgetTypes {
                  BaseWidget, 
                  InputWidget, 
                  ButtonWidget,
                  DisplayWidget,
                  ViewWidget,
                  ContainerWidget,
                  FormWidget,
                  AdditionalWidget
                 };
class cQtPluginDescr 
{
public:
   /** Die Konstruktion erfolgt mit allen Informationen, die vom Plugin-Interface
    *  benötigt werden:
    *  - Widget-Name (Klassenname, Key)
    *  - Include-Datei
    *  - Icon
    *  - Widget-Gruppe im Designer
    *  - Tool-Tip
    *  - What's this?
    *  - Container-Widget Flag
    *
    * Das konstruierte Objekt registriert sich automatisch bei der Klasse
    * cQtPluginRegistry.
    */
   cQtPluginDescr(const char *key, 
                  const char *include_file,
                  QIconSet icon_set, 
                  const char *group, 
                  const char *tool_tip,
                  const char *whats_this,
                  bool is_container) :
      _key(key),
      _include_file(include_file),
      _icon_set(icon_set),
      _group(group),
      _tool_tip(tool_tip),
      _whats_this(whats_this),
      _is_container(is_container)
   {
      if (_whats_this == NULL) {
         _whats_this = _tool_tip;
      }
      cQtPluginRegistry::addWidget(this);
   }
   cQtPluginDescr(WidgetTypes type,
                  const char * key, 
                  const char * icon_name, 
                  const char * tool_tip) :
      _key(key),
///      _icon_set(icon_set),
      _icon_name(icon_name),
      _tool_tip(tool_tip)
   {
      if (_whats_this == NULL) {
         _whats_this = _tool_tip;
      }
      _include_file = key;
      _include_file += ".h";
      _is_container = false;
      _group = "SHACIRA ";
      if (type == BaseWidget) {
         _group = "";
      } else if (type == InputWidget) {
         _group += "Input";
      } else if (type == ButtonWidget) {
         _group += "Buttons";
      } else if (type == DisplayWidget) {
         _group += "Display";
      } else if (type == ViewWidget) {
         _group += "Views";
      } else if (type == ContainerWidget) {
         _group += "Containers";
         _is_container = true;
      } else if (type == FormWidget) {
         _group = "";
         _is_container = true;
      } else if (type == AdditionalWidget) {
         _group += "Additional";
      }
      cQtPluginRegistry::addWidget(this);
   }

   /// Factory-Methode für QWidgetPlugin::create(). Die
   /// Implementierung erfolgt im Macro QT_PLUGIN_REGISTER.
   virtual QWidget *factory(QWidget *parent, const char *name) = 0;

   /// Widget-Name (Klassenname).
   QString getKey() const { return _key; }
   /// Include-Datei.
   QString getIncludeFile() const { return _include_file; }
   /// Icon
   QIconSet getIconSet() const { return _icon_set; }
   /// Icon-Name
   QString getIconName() const { return _icon_name; }
   /// Zugehörigkeit zu einer Widget-Gruppe im Designer.
   QString getGroup() const { return _group; }
   /// Tool-Tip
   QString getToolTip() const { return _tool_tip; }
   /// What's this?
   QString getWhatsThis() const { return _whats_this; }
   /// Ist es ein Container-Widget?
   bool isContainer() const { return _is_container; }

private:
   // Im Konstruktor gesetzte Attribute
   QString _key;
   QString _include_file;
   QIconSet _icon_set;
   QString _icon_name;
   QString _group;
   QString _tool_tip;
   QString _whats_this;
   bool _is_container;
};

/**
 * QT_PLUGIN_REGISTER ist ein Macro um eine Ableitung von cQtPluginDescr (incl. der
 * virtuellen Funktion) zu implementieren, gleichzeitig wird eine statische
 * Variable instanziiert (und damit die Widget-Beschreibung in cQtPluginRegistry registriert):
 *
 * @param class_name [char*] Klassenname (Wichtig: NICHT als String in Anfuehrungszeichen)
 *
 * @param include_file [char*] Zugehoerende Include-Datei, ggf. mit Pfad (noch auszuprobieren: wie
 *    reagiert der Designer, wenn keine Include-Datei angegeben ist???)    
 *
 * @param icon_set [QIconSet*] Hier kann ein Icon definiert werden. Entweder eine
 *    statische Variable oder (besser) eine statische Methode der Widget-
 *    Klasse, z.B. static QIconSet *cQtMyButton::getPluginIcon().
 *    TBD: Spezifikation fuer NOICON und DEFAULTICON???
 *
 * @param group [char*] Zugeordnete Widget-Gruppe im Designer, 0 wird durch eine
 *    Default-Gruppe ersetzt.
 *
 * @param tool_tip [char*] blabla, 0 wird durch den Klassennamen ersetzt.
 *
 * @param whats_this [char*] blabla, 0 wird durch den Tool-Tip ersetzt.
 *
 * @param is_container [bool] true bei einem Container-Widget
 *
 * Beispiel: QT_DESIGNER_PLUGIN( cQtMyButton, "my_buttob.h", 0, "User Button", 0, 0, false)
 */

// TBD: ggf. verschiedene Macros mit div. Defaultwerten definieren???

#if defined(__GNUC__)

#define QT_PLUGIN_REGISTER( class_name, include_file , icon_set , group , tool_tip , whats_this , is_container ) \
   static class cQtPluginDescr_##class_name : public cQtPluginDescr {\
   public: \
      cQtPluginDescr_##class_name() : cQtPluginDescr( #class_name , include_file , \
         icon_set , group , tool_tip , whats_this , is_container ) {  } \
      QWidget *factory(QWidget *parent, const char *name) \
         { return new class_name(parent,name); } \
   } __qt_plugin_descr_##class_name##__;

#define SH_PLUGIN_REGISTER(type, class_name, icon_set , tool_tip  ) \
   static class cQtPluginDescr_##class_name : public cQtPluginDescr {\
   public: \
      cQtPluginDescr_##class_name() : \
         cQtPluginDescr( type, #class_name, icon_set, tool_tip) {  } \
      QWidget *factory(QWidget *parent, const char *name) \
         { return new class_name(parent,name); } \
   } __qt_plugin_descr_##class_name##__;

#define SH2_PLUGIN_REGISTER(type, class_name, icon_set , tool_tip  ) \
   static class cQtPluginDescr_##class_name : public cQtPluginDescr {\
   public: \
      cQtPluginDescr_##class_name() : \
         cQtPluginDescr(type, #class_name, icon_set, tool_tip) {  } \
      QWidget *factory(QWidget *parent, const char *name) \
         { return new class_name(true, parent,name); } \
   } __qt_plugin_descr_##class_name##__;

#else

#define QT_PLUGIN_REGISTER( class_name, include_file , icon_set , group , tool_tip , whats_this , is_container ) \
   static class cQtPluginDescr_##class_name : public cQtPluginDescr {\
   public: \
      cQtPluginDescr_##class_name() : cQtPluginDescr( #class_name , include_file , \
         icon_set , group , tool_tip , whats_this , is_container ) {  } \
      QWidget *factory(QWidget *parent, const char *name) \
         { return new class_name##(parent,name); } \
   } __qt_plugin_descr_##class_name##__;

#define SH_PLUGIN_REGISTER(type, class_name, icon_set , tool_tip  ) \
   static class cQtPluginDescr_##class_name : public cQtPluginDescr {\
   public: \
      cQtPluginDescr_##class_name() : \
         cQtPluginDescr( type, #class_name, icon_set, tool_tip) {  } \
      QWidget *factory(QWidget *parent, const char *name) \
         { return new class_name##(parent,name); } \
   } __qt_plugin_descr_##class_name##__;

#define SH2_PLUGIN_REGISTER(type, class_name, icon_set , tool_tip  ) \
   static class cQtPluginDescr_##class_name : public cQtPluginDescr {\
   public: \
      cQtPluginDescr_##class_name() : \
         cQtPluginDescr(type, #class_name, icon_set, tool_tip) {  } \
      QWidget *factory(QWidget *parent, const char *name) \
         { return new class_name##(true, parent,name); } \
   } __qt_plugin_descr_##class_name##__;

#endif

#else // QT_PLUGIN

// All die tollen Klassen gibt's nur im Qt Designer Plugin. Das Macro laeuft
// ins Leere, wenn es in der eigentlichen Anwendung benutzt wird.
#define QT_PLUGIN_REGISTER(class_name, include_file, icon_set, group, tool_tip, whats_this, is_container)

#endif // QT_PLUGIN




#endif // QT_PLUGIN_REGISTER_H

