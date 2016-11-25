
#include "portingfile.h"
#include "portingapplication.h"
#include "portingcontext.h"
#include "uiport.h"

PortingFile::PortingFile(PortingApplication * application, const QFileInfo & fileInfo)
      : _application(application), _sourceFileInfo(fileInfo)
{
   _sourcePath = fileInfo.absoluteFilePath();
   _sourceDirectory = _sourceFileInfo.dir();
   _relPath = relativePath(_application->sourceDirectory().absolutePath(), _sourcePath);
   _destinationPath = append(_application->destinationDirectory().absolutePath(), _relPath);
   _destinationFileInfo = QFileInfo(_destinationPath);
   _destinationDirectory = _destinationFileInfo.dir();
   QString fileName = fileInfo.baseName() + ".ui4";
   _intermediatePath = append(_destinationFileInfo.absolutePath(), fileName);
   fileName = fileInfo.baseName() + ".err";
   _errorPath = append(_destinationFileInfo.absolutePath(), fileName);
   fileName = fileInfo.baseName() + ".struct";
   _structPath = append(_destinationFileInfo.absolutePath(), fileName);
   bool start = false;
   QStringList components = _destinationPath.split("/");
   QStringList::const_iterator i = components.begin();
   while (i != components.end()) {
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
}

PortingFile::~PortingFile()
{
}

void PortingFile::portFile()
{
   QString result;
   QString command;
   command = uic3Path;
   command += " -convert ";
   command += sourcePath();
   command += " -o ";
   command += intermediatePath();
   QFileInfo fileInfo(intermediatePath());
   QDir directory = fileInfo.absoluteDir();
   QString directoryPath = directory.absolutePath();
   directory.mkpath(directoryPath);
   if (exec(uic3Path, command, result) == 0) {
      if (!result.isEmpty()) {
         LogPrintf(errorPath().toStdString(), "%s\n", result.toStdString().c_str());
         LogPrintf(errorFileName(), "%s\n", sourcePath().toStdString().c_str());
         LogPrintf(errorFileName(), "%s\n", result.toStdString().c_str());
      }
      QString inputFile = sourcePath();
      QString outputFile = intermediatePath();
      if (uiPort->port(this)) {
         LogPrintf(logFileName(), "conversion of %s\n", sourcePath().toStdString().c_str());
      }
   } else {
      LogPrintf(errorPath().toStdString(), "conversion of %s\n", sourcePath().toStdString().c_str());
      LogPrintf(logFileName(), "conversion of %s\n", sourcePath().toStdString().c_str());
   }
}

