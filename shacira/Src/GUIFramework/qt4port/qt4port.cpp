
#include "qt4port.h"

#ifdef QT4

QObject * child(QObject * object, const char * objName, const char * inheritsClass, bool recursiveSearch)
{
   if (object == NULL) {
      return NULL;
   }
   QObjectList objects = object->children();
   QObjectList::const_iterator i = objects.constBegin();
   while (i != objects.constEnd()) {
      QObject * child = (*i);
      QString objectName = child->objectName();
      if (objectName == objName) {
         if (inheritsClass == NULL) {
            return child;
         } else {
            if (child->inherits(inheritsClass)) {
               return child;
            }
         }
      }
      i++;
   }
   if (recursiveSearch) {
      i = objects.constBegin();
      while (i != objects.constEnd()) {
         QObject * object_Iter = (*i);
         QObject * foundChild = child(object_Iter, objName, inheritsClass, recursiveSearch);
         if (foundChild != NULL) {
            return foundChild;
         }
         i++;
      }
   }
   return NULL;
}

QObject * child(QObject * object, const std::string & objName, const char * inheritsClass, bool recursiveSearch)
{
   return child(object, objName.c_str(), inheritsClass, recursiveSearch);
}

QObject * child(QObject * object, const QString & objName, const char * inheritsClass, bool recursiveSearch)
{
   return child(object, objName.toStdString().c_str(), inheritsClass, recursiveSearch);
}

QObject * parent(QObject * object, const char * objName, const char * inheritsClass, bool recursiveSearch)
{
   if (object == NULL) {
      return NULL;
   }
   QObject * parentPtr = object->parent();
   if (parentPtr == NULL) {
      return NULL;
   }
   if (objName == NULL && inheritsClass == NULL) {
      // no search specification return parent of this object
      return parentPtr;
   }
   if (objName != NULL) {
      if (inheritsClass != NULL) {
         if (parentPtr->inherits(inheritsClass) &&
             objName == parentPtr->objectName()) {
            return parentPtr;
         }
      } else {
         if (parentPtr->inherits(inheritsClass)) {
            return parentPtr;
         }
      }
   } else {
      if (inheritsClass != NULL) {
         if (parentPtr->inherits(inheritsClass)) {
            return parentPtr;
         }
      }
   }
   if (recursiveSearch) {
      return parent(parentPtr, objName, inheritsClass, recursiveSearch);
   }
   return NULL;
}

void unsetPalette(QWidget * widget)
{
   widget->setPalette(QPalette());
}

void queryListHelper(QObjectList & objectList, QObject * object, const char * inheritsClass, const char * objName, bool regexpMatch, bool recursiveSearch)
{
   if (object == NULL) {
      return;
   }
   bool matchName = false;
   bool matchClass = false;
   if (objName == NULL) {
      matchName = true;
   } else {
      QString objectName = object->objectName();
      if (objectName == objName) {
         matchName = true;
      } else {
         matchName = false;
      }
   }
   if (inheritsClass == NULL) {
      matchClass = true;
   } else {
      if (object->inherits(inheritsClass)) {
         matchClass = true;
      } else {
         matchClass = false;
      }
   }
   if (matchName & matchClass) {
      objectList.push_back(object);
   }
   if (recursiveSearch) {
      QObjectList objects = object->children();
      QObjectList::const_iterator i = objects.constBegin();
      i = objects.constBegin();
      while (i != objects.constEnd()) {
         QObject * child = (*i);
         queryListHelper(objectList, child, inheritsClass, objName, regexpMatch, recursiveSearch);
         i++;
      }
   }
}

QObjectList queryList(QObject * object, const char * inheritsClass, const char * objName, bool regexpMatch, bool recursiveSearch)
{
   QObjectList objectList;
   if (object == NULL) {
      return objectList;
   }
   queryListHelper(objectList, object, inheritsClass, objName, regexpMatch, recursiveSearch);
   return objectList;
}

void setEncoding(EncodingTypes encoding)
{
}

#include <qwizard.h>
int indexOf(QWizard * wizard, QWidget * page)
{
   QList<int> pageList = wizard->pageIds();
   QList<int>::const_iterator i = pageList.constBegin();
   while (i != pageList.constEnd()) {
      int id = (*i);
      if (page == wizard->page(id)) {
         return id;
      }
      i++;
   }
   return -1;
}

bool isA(QObject * object, const char * className)
{
   const QMetaObject * metaObject = object->metaObject();
   if (metaObject == NULL) {
      return false;
   }
   QString objectClassName = metaObject->className();
   if (objectClassName == className) {
      return true;
   } else {
      return false;
   }
}

QString append(const QString & head, const QString & tail, const QString & delimiter)
{
   return head + delimiter + tail;
}

#include <qtextstream.h>
#include <qfileinfo.h>
const QString _logDirectory = "Log";
const QString _logFile = "qt4port.log";
static bool _initialized = false;
static QString logFilePath()
{
   QString path;
   QFileInfo fileInfo(_logDirectory);
   if (fileInfo.exists()) {
      path = append(_logDirectory, _logFile, "/");
      if (!_initialized) {
         QFile file(path);
         file.remove();
         _initialized = true;
      }
   }
   return path;
}
void notPorted(const QString & location, const QString & message)
{
   QString path = logFilePath();
   if (!path.isEmpty()) {
      QFile file(path);
      if (file.open(QIODevice::Append|QIODevice::Text)) {
         QTextStream stream(&file);
         stream << location << message << endl;
         file.close();
      }
   }
}

#endif

