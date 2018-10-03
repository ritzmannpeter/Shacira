
#include "portingapplication.h"
#include "portingcontext.h"
#include <qtextstream.h>

PortingApplication::PortingApplication(PortingContext * context, const QString name)
   : _context(context), _name(name)
{
   _applicationDirectory = QDir(append(context->homeDirectory().absolutePath(), name));
   _sourceDirectory = QDir(append(applicationDirectory().absolutePath(), context->sourceQtVersion()));
   _destinationDirectory = QDir(append(applicationDirectory().absolutePath(), context->destinationQtVersion()));
}

PortingApplication::~PortingApplication()
{
}

void PortingApplication::collectFiles()
{
   collectFiles(sourceDirectory());
}

void PortingApplication::portFiles()
{
   FILE_MAP_T::const_iterator i = _fileMap.cbegin();
   while (i != _fileMap.cend()) {
      PortingFile * file = (*i).second;
      file->transformFile();;
      i++;
   }
}

void PortingApplication::generateResources()
{
}

void PortingApplication::addSourceFile(const QFileInfo & fileInfo)
{
   PortingFile * portingFile = new PortingFile(this, fileInfo);
   _fileMap[portingFile->sourcePath()] = portingFile;
}

PortingFile * PortingApplication::file(PortingApplication * application, const QFileInfo & fileInfo)
{
   PortingFile * file = NULL;
   QString name = fileInfo.baseName();
   FILE_MAP_T::const_iterator i = _fileMap.find(name);
   if (i == _fileMap.cend()) {
      file = new PortingFile(application, fileInfo);
      _fileMap[name] = file;
   } else {
      file = (*i).second;
   }
   return file;
}

void PortingApplication::collectFiles(const QDir & directory)
{
   QString directoryPath = directory.absolutePath();
   QStringList entryList = directory.entryList(_context->filePatterns(), QDir::Files);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = (*it);
      QFileInfo fileInfo(append(directoryPath, fileName));
      addSourceFile(fileInfo);
   }
   entryList = directory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString subDirectoryName = (*it);
      if (!subDirectoryName.isEmpty() &&
           subDirectoryName[0] != '.') {
         QDir subDirectory(append(directoryPath, subDirectoryName));
         QString directoryPath = subDirectory.absolutePath();
         collectFiles(subDirectory);
         int dummy = 0;
      }
   }
}

