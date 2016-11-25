
#include <qstring.h>
#include <qdir.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

class Definition
{
public:
   Definition(const QString & path, int lineNo)
      : _path(path), _lineNo(lineNo)
   {
   };
   QString _path;
   int _lineNo;
};

class ClassDefinition : public Definition
{
public:
   ClassDefinition(const QString & path, int lineNo)
      : Definition(path, lineNo)
   {
   };
};

class StructDefinition : public Definition
{
public:
   StructDefinition(const QString & path, int lineNo)
      : Definition(path, lineNo)
   {
   };
};

Definition * _definition = NULL;

void setClassDefinition(const QString & path, int lineNo)
{
   if (_definition != NULL) {
      delete _definition;
      _definition = NULL;
   }
   ClassDefinition * classDefinition = new ClassDefinition(path, lineNo);
   _definition = classDefinition;
}

void setStructDefinition(const QString & path, int lineNo)
{
   if (_definition != NULL) {
      delete _definition;
      _definition = NULL;
   }
   StructDefinition * structDefinition = new StructDefinition(path, lineNo);
   _definition = structDefinition;
}

inline QString append(const QString & head, const QString & tail, const QString & delimiter = "/")
{
   return head + delimiter + tail;
}

void analyze(const QString & path)
{
   cout << path.toStdString() << endl;
   QFile file(path);
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QString line;
      int lineNo = 0;
      while (!file.atEnd()) {
         line = file.readLine();
         lineNo++;
         int pos = line.indexOf("QString");
         if (pos >= 0) {
            int dummy = 0;
         }
         pos = line.indexOf("struct");
         if (pos >= 0) {
            setClassDefinition(path, lineNo);
         }
         pos = line.indexOf("class");
         if (pos >= 0) {
            setStructDefinition(path, lineNo);
         }
      }
   }
}

bool isExcluded(const QString & path, const QStringList & exclusions)
{
   QStringList::const_iterator i = exclusions.begin();
   while (i != exclusions.end()) {
      QString excluded = (*i);
      int pos = path.indexOf(excluded, 0, Qt::CaseInsensitive);
      if (pos >= 0) {
         return true;
      }
      i++;
   }
   return false;
}

void collectFiles(const QDir & directory, const QStringList & patterns, const QStringList & exclusions)
{
   QString directoryPath = directory.absolutePath();
   QStringList entryList = directory.entryList(patterns, QDir::Files);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = (*it);
      QFileInfo fileInfo(append(directoryPath, fileName));
      QString path = fileInfo.absoluteFilePath();
      analyze(path);
   }
   entryList = directory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString subDirectoryName = (*it);
      if (!subDirectoryName.isEmpty() &&
           subDirectoryName[0] != '.') {
         QDir subDirectory(append(directoryPath, subDirectoryName));
         QString directoryPath = subDirectory.absolutePath();
         if (!isExcluded(directoryPath, exclusions)) {
            collectFiles(subDirectory, patterns, exclusions);
         }
      }
   }
}

int main(int argc, char* argv[])
{
   QStringList patterns;
   patterns << "*.h";
   QStringList exclusions;
//   exclusions << "forms/generated";
   exclusions << "dialogs/generated";
   QDir directory;
   collectFiles(directory, patterns, exclusions);
   return 0;
}
