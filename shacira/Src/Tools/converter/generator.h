
#ifndef _generator_h_
#define _generator_h_

#include <qstring.h>
#include <qfile.h>
#include <qobject.h>
#include <qobjectlist.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qdom.h>
#include <qmetaobject.h>
#include <qvariant.h>
#include <qdir.h>
#include <qstringlist.h>
#include <qwidgetfactory.h>

class cGenerator
{
public:
   cGenerator();
   virtual ~cGenerator();
   QWidget * convert(const QString & fileName);
public:
   QWidget * loadFromUiFile(const QString & fileName) const;
protected:
   void processObjectList(QDomDocument & document, QDomElement & parent, QObject * object);
   bool generate(QDomDocument & document, QDomElement & parent, QObject * object);
   bool generateWidget(QDomDocument & document, QDomElement & parent, QWidget * widget);
   bool generateWidget(QDomDocument & document, QDomElement & element, QWidget * widget, const QString targetClassName);
   bool generateLayout(QDomDocument & document, QDomElement & parent, QVBoxLayout & layout);
   bool generateLayout(QDomDocument & document, QDomElement & parent, QHBoxLayout & layout);
   bool generateLayout(QDomDocument & document, QDomElement & parent, QGridLayout & layout);
   bool generateLayout(QDomDocument & document, QDomElement & parent, QLayout * layout);
   bool generateSpacer(QDomDocument & document, QDomElement & parent, QSpacerItem * spacerItem);

   void addStringProperty(QDomDocument & document, QDomElement & element, const QString & name, const QString & value, bool translate);
   void setNodeValue(QDomDocument & document, QDomElement & parent, int intValue);
   void setNodeValue(QDomDocument & document, QDomElement & parent, const QString & value);
   void setGeometry(QDomDocument & document, QDomElement & parent, const QRect & geometry);
   QString targetClassName(const QString & sourceClassName) const;
   void addPropertyNames(QMetaObject * metaObject, QStringList & nameList);
   QStringList propertyNameList(QWidget * widget);
   void addProperty(QDomDocument & document, QDomElement & parent, const QString propertyName, const QVariant & propertyValue);
   void addProperties(QDomDocument & document, QDomElement & parent, QWidget * widget);
};

#endif



