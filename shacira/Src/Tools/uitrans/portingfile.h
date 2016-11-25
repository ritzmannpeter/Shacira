
#ifndef _portingfile_h_
#define _portingfile_h_

#include <qstring.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qdir.h>
#include <map>
using namespace std;

class PortingContext;
class PortingApplication;
class PortingFile;
class UiTrans;

void LogPrintf(const string & logFile, const char * fmt_str, ...);
extern UiTrans * _uiTrans;

class PortingFile
{
public:
   PortingFile(PortingApplication * application, const QFileInfo & fileInfo);
   virtual ~PortingFile();
   void transformFile();
   inline QString name() const {return _fileInfo.baseName();};
   inline PortingApplication * application() const {return _application;};
   inline QString baseName() const {return _baseName;};
   inline QString sourcePath() const {return _sourcePath;};
   inline QString intermediatePath() const {return _intermediatePath;};
   inline QString destinationPath() const {return _destinationPath;};
   inline QString errorPath() const {return _errorPath;};
   inline QString structPath() const {return _structPath;};
   inline QString logicPath() const {return _logicPath;};
   inline QString extension() const {return _extension;};
   inline bool isCppCode() const
   {
      if (_extension == "pp" ||
          _extension == "cpp" ||
          _extension == "h") {
         return true;
      } else {
         return false;
      }
   };
   inline bool isPPFile() const {return _isPPFile;};
   inline bool isWidgetImplementation() const {return _isWidgetImplementation;};
   inline bool isWidgetHeader() const {return _isWidgetHeader;};
   inline bool isProjectFile() const {return _isProjectFile;};
   inline bool isProjectFilter() const {return _isProjectFilter;};
private:
   QFileInfo _fileInfo;
   PortingApplication * _application;
   QString _baseName;
   QString _sourcePath;
   QString _intermediatePath;
   QString _destinationPath;
   QString _errorPath;
   QString _structPath;
   QString _logicPath;
   QString _extension;
   bool _isPPFile;
   bool _isWidgetImplementation;
   bool _isWidgetHeader;
   bool _isProjectFile;
   bool _isProjectFilter;
};
typedef std::map<QString,PortingFile*> FILE_MAP_T;

inline QString append(const QString & head, const QString & tail, const QString & delimiter = "/")
{
   return head + delimiter + tail;
}

inline QString relativePath(const QString & basePath, const QString & path)
{
   QString relativePath;
   QStringList baseComponents = basePath.split("/");
   QStringList pathComponents = path.split("/");
   if (baseComponents.length() > pathComponents.length()) {
      return QString();
   }
   QStringList::const_iterator baseIterator = baseComponents.begin();
   QStringList::const_iterator pathIterator = pathComponents.begin();
   while (baseIterator != baseComponents.end()) {
      QString baseComponent = (*baseIterator);
      QString pathComponent = (*pathIterator);
      if (pathComponent.compare(baseComponent, Qt::CaseInsensitive) != 0) {
         return QString();
      }
      baseIterator++;
      pathIterator++;
   }
   while (pathIterator != pathComponents.end()) {
      QString pathComponent = (*pathIterator);
      if (relativePath.isEmpty()) {
         relativePath = pathComponent;
      } else {
         relativePath = append(relativePath, pathComponent);
      }
      pathIterator++;
   }
   return relativePath;
}

#endif
