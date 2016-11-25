
#ifndef _portingapplication_h_
#define _portingapplication_h_

#include "portingfile.h"
#include "forminformations.h"
#include <qimage.h>

class ImageInformations;

class InvalidProperty
{
public:
   InvalidProperty()
   {
   };
   InvalidProperty(const InvalidProperty & right)
      : _path(right._path), _propertyName(right._propertyName), _widgetName(right._widgetName)
   {
   };
   InvalidProperty(const QString & path, const QString & propertyName, const QString & widgetName)
      : _path(path), _propertyName(propertyName), _widgetName(widgetName)
   {
   };
   inline QString key() const {return _path + "::" + _widgetName;};
   inline QString path() const {return _path;};
   inline QString propertyName() const {return _propertyName;};
   inline QString widgetName() const {return _widgetName;};
private:
   QString _path;
   QString _propertyName;
   QString _widgetName;
};
typedef map<QString,InvalidProperty> INVALID_PROPERTY_MAP_T;

class PortingApplication
{
public:
   PortingApplication(PortingContext * context, const QString name);
   virtual ~PortingApplication();
   inline QString name() const {return _name;};
   inline QDir applicationDirectory() const {return _applicationDirectory;};
   inline QDir sourceDirectory() const {return _sourceDirectory;};
   inline QDir destinationDirectory() const {return _destinationDirectory;};
   inline ImageInformations * imageInformations() const {return _imageInformations;};
   FILE_MAP_T & fileMap() {return _fileMap;};
   void collectFiles();
   void portFiles();
   void generateResources();
   void printFormHeaderInformations();
   PortingFile * file(PortingApplication * application, const QFileInfo & fileInfo);
   void addSourceFile(const QFileInfo & fileInfo);
   void addFormInfo(PortingFile * file, const QString & formClass, const QString & baseClass, const QString & uiClassName, const QString & classCode);
   void addInvalidProperty(PortingFile * file, const QString & propertyName, const QString & widgetName);
   static bool removeDirectory(const QString & path);
protected:
   void collectFiles(const QDir & directory);
   void loadImageMapFromFilesystem(const QString & relativePath, const QString & path);
   void loadImageMapFromFilesystem();
   void printInvalidProperties();
protected:
   PortingContext * _context;
   QString _name;
   QDir _applicationDirectory;
   QDir _sourceDirectory;
   QDir _destinationDirectory;
   FILE_MAP_T _fileMap;
   ImageInformations * _imageInformations;
   FormInformations _formInformations;
   INVALID_PROPERTY_MAP_T _invalidPropertyMap;
};
typedef std::map<QString,PortingApplication*> APPLICATION_MAP_T;

#endif
