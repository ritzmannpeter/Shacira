
#ifndef _portingapplication_h_
#define _portingapplication_h_

#include "portingfile.h"

class PortingApplication
{
public:
   PortingApplication(PortingContext * context, const QString name);
   virtual ~PortingApplication();
   inline QString name() const {return _name;};
   inline QDir applicationDirectory() const {return _applicationDirectory;};
   inline QDir sourceDirectory() const {return _sourceDirectory;};
   inline QDir destinationDirectory() const {return _destinationDirectory;};
   FILE_MAP_T & fileMap() {return _fileMap;};
   void collectFiles();
   void portFiles();
   void generateResources();
   PortingFile * file(PortingApplication * application, const QFileInfo & fileInfo);
   void addSourceFile(const QFileInfo & fileInfo);
protected:
   void collectFiles(const QDir & directory);
protected:
   PortingContext * _context;
   QString _name;
   QDir _applicationDirectory;
   QDir _sourceDirectory;
   QDir _destinationDirectory;
   FILE_MAP_T _fileMap;
};
typedef std::map<QString,PortingApplication*> APPLICATION_MAP_T;

#endif
