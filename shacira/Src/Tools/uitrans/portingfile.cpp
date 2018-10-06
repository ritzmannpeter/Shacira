
#include "portingfile.h"
#include "portingapplication.h"
#include "portingcontext.h"
#include "uitrans.h"

PortingFile::PortingFile(PortingApplication * application, const QFileInfo & fileInfo)
      : _application(application), _fileInfo(fileInfo),
        _isPPFile(false),
        _isWidgetImplementation(false),
        _isWidgetHeader(false),
        _isProjectFile(false),
        _isProjectFilter(false)
{
   _baseName = _fileInfo.baseName();
   _sourcePath = fileInfo.absoluteFilePath();
   QString relPath = relativePath(_application->sourceDirectory().absolutePath(), _sourcePath);
   _destinationPath = append(_application->destinationDirectory().absolutePath(), relPath);
   QString fileName = fileInfo.baseName() + ".ui4";
   QFileInfo destinationInfo(_destinationPath);
   _intermediatePath = append(destinationInfo.absolutePath(), fileName);
   fileName = fileInfo.baseName() + ".err";
   _errorPath = append(destinationInfo.absolutePath(), fileName);
   fileName = fileInfo.baseName() + ".struct";
   _structPath = append(destinationInfo.absolutePath(), fileName);
   bool start = false;
   QStringList components = _destinationPath.split("/");
   QStringList::const_iterator i = components.constBegin();
   while (i != components.constEnd()) {
      if (start) {
         if (!_logicPath.isEmpty()) {
            _logicPath += "/";
         }
         _logicPath += (*i);
      } else {
         if ((*i) == "Qt4") {
            start = true;
         }
      }
      i++;
   }
   _extension = _fileInfo.suffix();
   if (_extension == "pp") {
      _isPPFile = true;
   } else if (_extension == "cpp") {
      int pos = _destinationPath.indexOf("widgets", 0, Qt::CaseInsensitive);
      if (pos >= 0) {
         _isWidgetImplementation = true;
      }
   } else if (_extension == "h") {
      int pos = _destinationPath.indexOf("widgets", 0, Qt::CaseInsensitive);
      if (pos >= 0) {
         _isWidgetHeader = true;
      }
   } else if (_extension == "vcxproj") {
      _isProjectFile = true;
   } else if (_extension == "filters") {
      _isProjectFilter = true;
   }
}

PortingFile::~PortingFile()
{
}

void PortingFile::transformFile()
{
   if (_uiTrans->transform(this)) {
      LogPrintf(logFileName(), "conversion of %s\n", sourcePath().toStdString().c_str());
   }
}

