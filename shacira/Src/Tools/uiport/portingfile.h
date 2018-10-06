
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
class UiPort;

void LogPrintf(const string & logFile, const char * fmt_str, ...);
int exec(const QString & fileName, const QString & command, QString & result);
extern QString imagePrefix;
extern QString qtDir;
extern QString qtBinDir;
extern QString qtPluginDir;
extern QString uic3Path;
extern QString uicPath;
extern QString rccPath;
extern QString inputDir;
extern QString outputDir;
extern UiPort * uiPort;

class PortingFile
{
public:
   PortingFile(PortingApplication * application, const QFileInfo & fileInfo);
   virtual ~PortingFile();
   void portFile();
   inline QString name() const {return _sourceFileInfo.baseName();};
   inline PortingApplication * application() const {return _application;};
   inline QString relPath() const {return _relPath;};
   inline QString sourcePath() const {return _sourcePath;};
   inline QString sourceDirectory() const {return _sourceDirectory.absolutePath();};
   inline QString destinationPath() const {return _destinationPath;};
   inline QString destinationDirectory() const {return _destinationDirectory.absolutePath();};
   inline QString intermediatePath() const {return _intermediatePath;};
   inline QString errorPath() const {return _errorPath;};
   inline QString structPath() const {return _structPath;};
   inline QString logicPath() const {return _logicPath;};
private:
   QFileInfo _sourceFileInfo;
   QFileInfo _destinationFileInfo;
   PortingApplication * _application;
   QString _relPath;
   QString _sourcePath;
   QDir _sourceDirectory;
   QString _destinationPath;
   QDir _destinationDirectory;
   QString _intermediatePath;
   QString _errorPath;
   QString _structPath;
   QString _logicPath;
};
typedef std::map<QString,PortingFile*> FILE_MAP_T;

inline QString append(const QString & head, const QString & tail, const QString & delimiter = "/")
{
   if (head.isEmpty()) {
      return tail;
   } else {
      if (tail.isEmpty()) {
         return head;
      } else {
         return head + delimiter + tail;
      }
   }
}

inline QString relativePath(const QString & basePath, const QString & path)
{
   QString relativePath;
   QStringList baseComponents = basePath.split("/");
   QStringList pathComponents = path.split("/");
   if (baseComponents.length() > pathComponents.length()) {
      return QString();
   }
   QStringList::const_iterator baseIterator = baseComponents.constBegin();
   QStringList::const_iterator pathIterator = pathComponents.constBegin();
   while (baseIterator != baseComponents.constEnd()) {
      QString baseComponent = (*baseIterator);
      QString pathComponent = (*pathIterator);
      if (pathComponent.compare(baseComponent, Qt::CaseInsensitive) != 0) {
         return QString();
      }
      baseIterator++;
      pathIterator++;
   }
   while (pathIterator != pathComponents.constEnd()) {
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
