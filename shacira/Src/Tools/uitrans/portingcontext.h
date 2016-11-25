
#ifndef _portingcontext_h_
#define _portingcontext_h_

#include "portingapplication.h"

class PortingContext
{
public:
   PortingContext()
   {
   };
   virtual ~PortingContext()
   {
   };
   void clear()
   {
      _filePatterns.clear();
      _applicationMap.clear();
   };
   void collectFiles();
   void portFiles();
   void generateResources();
   void addApplication(const QString name)
   {
      APPLICATION_MAP_T::const_iterator i = _applicationMap.find(name);
      if (i == _applicationMap.end()) {
         PortingApplication * application = new PortingApplication(this, name);
         _applicationMap[name] = application;
      }
   };
   PortingApplication * application(const QString name)
   {
      PortingApplication * application = NULL;
      APPLICATION_MAP_T::const_iterator i = _applicationMap.find(name);
      if (i != _applicationMap.end()) {
         application = (*i).second;
      }
      return application;
   };
   inline QDir homeDirectory() const {return _homeDirectory;};
   inline void setHomeDirectory(const QDir & value) {_homeDirectory = value;};
   inline QString sourceQtVersion() const {return _sourceQtVersion;};
   inline void setSourceQtVersion(const QString & value) {_sourceQtVersion = value;};
   inline QString destinationQtVersion() const {return _destinationQtVersion;};
   inline void setDestinationQtVersion(const QString & value) {_destinationQtVersion = value;};
   inline QStringList filePatterns() const {return _filePatterns;};
   inline void addFilePattern(const QString & pattern) {_filePatterns << pattern;};
   APPLICATION_MAP_T & applicationMap() {return _applicationMap;};
private:
   QString _sourceQtVersion;
   QString _destinationQtVersion;
   QDir _homeDirectory;
   QStringList _filePatterns;
   APPLICATION_MAP_T _applicationMap;
};

#endif

