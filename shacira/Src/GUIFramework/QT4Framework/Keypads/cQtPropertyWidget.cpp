// ==========================================================================
// qt_property_widget.cpp
//
// Implementierung fuer cQtPropertyWidget
// ==========================================================================

// Interface
#include "cQtPropertyWidget.h"

// System includes
#include <qvariant.h>

// Library includes (shared)

// Project includes
#include "qt4port.h"

// --------------------------------------------------------------------------
// cQtProperty (generischer Zugriff auf Qt Properties von QObject)
// --------------------------------------------------------------------------

bool cQtProperty::SetProperty(const QString & prop_name, const QString &value)
{
   return _object->setProperty(CONST_STRING(prop_name), QVariant(value));
}

bool cQtProperty::GetProperty(const QString & prop_name, QString &value)
{ 
   QVariant variant = getObject()->property(CONST_STRING(prop_name));
   if (variant.type() == QVariant::String) {
#ifdef QT4
      value = variant.toString();
#else
      value = variant.asString();
#endif
      return true;
   }
   return false;
}


bool cQtProperty::SetProperty(const QString & prop_name, bool value)
{
   return _object->setProperty(CONST_STRING(prop_name), QVariant(value));
}

bool cQtProperty::GetProperty(const QString & prop_name, bool &value)
{ 
   QVariant variant = getObject()->property(CONST_STRING(prop_name));
   if (variant.type() == QVariant::Bool) {
#ifdef QT4
      value = variant.toBool();
#else
      value = variant.asBool();
#endif
      return true;
   }
   return false;
}


bool cQtProperty::SetProperty(const QString & prop_name, int value)
{
   return _object->setProperty(CONST_STRING(prop_name), QVariant(value));
}

bool cQtProperty::GetProperty(const QString & prop_name, int &value)
{ 
   QVariant variant = getObject()->property(CONST_STRING(prop_name));
   if (variant.type() == QVariant::Int) {
#ifdef QT4
      value = variant.toInt();
#else
      value = variant.asInt();
#endif
      return true;
   }
   return false;
}


bool cQtProperty::SetProperty(const QString & prop_name, unsigned int value)
{
   return _object->setProperty(CONST_STRING(prop_name), QVariant(value));
}

bool cQtProperty::GetProperty(const QString & prop_name, unsigned int &value)
{ 
   QVariant variant = getObject()->property(CONST_STRING(prop_name));
   if (variant.type() == QVariant::UInt) {
#ifdef QT4
      value = variant.toUInt();
#else
      value = variant.asUInt();
#endif
      return true;
   }
   return false;
}

// --------------------------------------------------------------------------
// cQtPropertyWidget (Propertyname mit Childname)
// --------------------------------------------------------------------------

bool cQtPropertyWidget::SetProperty(const QString & prop_name, int value)
{
   QObject *child;
   QString child_prop;
   if (findChild(prop_name, &child, child_prop)) {
      return cQtProperty(child).SetProperty(child_prop, value);
   }
   return cQtProperty::SetProperty(prop_name, value);
}

bool cQtPropertyWidget::GetProperty(const QString & prop_name, int &value)
{
   QObject *child;
   QString child_prop;
   if (findChild(prop_name, &child, child_prop)) {
      return cQtProperty(child).GetProperty(child_prop, value);
   }
   return cQtProperty::GetProperty(prop_name, value);
}

bool cQtPropertyWidget::SetProperty(const QString & prop_name, bool value)
{
   QObject *child;
   QString child_prop;
   if (findChild(prop_name, &child, child_prop)) {
      return cQtProperty(child).SetProperty(child_prop, value);
   }
   return cQtProperty::SetProperty(prop_name, value);
}

bool cQtPropertyWidget::GetProperty(const QString & prop_name, bool &value)
{
   QObject *child;
   QString child_prop;
   if (findChild(prop_name, &child, child_prop)) {
      return cQtProperty(child).GetProperty(child_prop, value);
   }
   return cQtProperty::GetProperty(prop_name, value);
}


bool cQtPropertyWidget::SetProperty(const QString & prop_name, const QString &value)
{
   QObject *child;
   QString child_prop;
   if (findChild(prop_name, &child, child_prop)) {
      return cQtProperty(child).SetProperty(child_prop, value);
   }
   return cQtProperty::SetProperty(prop_name, value);
}

bool cQtPropertyWidget::GetProperty(const QString & prop_name, QString &value)
{
   QObject *child;
   QString child_prop;
   if (findChild(prop_name, &child, child_prop)) {
      return cQtProperty(child).GetProperty(child_prop, value);
   }
   return cQtProperty::GetProperty(prop_name, value);
}



// Hilfsfunktionen: Widget mit bestimmtem Namen im Widget suchen
bool cQtPropertyWidget::findChild(const QString & prop_name, QObject **child, QString &child_prop)
{
   QString child_name = prop_name.section('.',0,0);
   child_prop = prop_name.section('.',1,1);
#ifdef QT4
   *child = this->child(getObject(), CONST_STRING(child_name));
#else
   *child = getObject()->child(child_name);
#endif
   return *child != 0;
}




/*
// --------------------------------------------------------------------------
// QLabel
// --------------------------------------------------------------------------

bool cQtPropertyLabel::setProperty(const QString & prop_name, bool value)
{
   if (prop_name == "shown") {
      _widget->setShown(value);
      return true;
   }
   return false;
}


bool cQtPropertyLabel::setProperty(const QString & prop_name, const QString &value)
{
   if (prop_name == "text" || prop_name.empty()) {
      _widget->setText(value);
      return true;
   }
   return false;
}
*/

#ifdef QT4

QObject * cQtPropertyWidget::child(QObject * object, const char * objName, const char * inheritsClass, bool recursiveSearch) const
{
   QObjectList objectList = object->children();
   QObjectList::const_iterator i = objectList.constBegin();
   while (i != objectList.constEnd()) {
      QObject * child = (*i);
      QObject * foundChild = NULL;
      if (inheritsClass != NULL) {
         if (child->inherits(inheritsClass)) {
            if (QString(objName) == child->objectName()) {
               foundChild = child;
            } else {
               if (recursiveSearch) {
                  foundChild = this->child(child, objName, inheritsClass, recursiveSearch);
               }
            }
         }
      } else {
         if (QString(objName) == child->objectName()) {
            foundChild = child;
         } else {
            if (recursiveSearch) {
               foundChild = this->child(child, objName, inheritsClass, recursiveSearch);
            }
         }
      }
      if (foundChild != NULL) {
         return foundChild;
      }
      i++;
   }
   return NULL;
}

#endif
