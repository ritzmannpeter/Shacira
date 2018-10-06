
#include <qstring.h>
#include <qapplication.h>
#include <qfile.h>
#include <qdir.h>
#include <qprocess.h>
#include <qtextstream.h>
#include <iostream>
#include <fstream>
#include "uiport.h"
#include "options.h"
#include <qwidget.h>
#include "cformbuilder.h"
#include "portingfile.h"
#include "portingapplication.h"
#include "portingcontext.h"
#include "imageinformations.h"

static char _Text[0x2000] = {0};

string logFileName()
{
   return "q4_uiport.log";
}

string errorFileName()
{
   return "q4_uiport.err";
}

void LogPrintf(const string & logFile, const char * fmt_str, ...)
{
   va_list ap;
   va_start(ap, fmt_str);
   try {
      vsprintf(_Text, fmt_str, ap);
      FILE * stream = fopen(logFile.c_str(), "a");
      if (stream != NULL) {
//         cout << _Text;
         fprintf(stream, "%s", _Text);
         fclose(stream);
      }
   } catch (...) {
   }
   va_end(ap);
}

QString imagePrefix = "Images/";
QString qtDir;
QString qtBinDir;
QString qtPluginDir;
QString uic3Path;
QString uicPath;
QString rccPath;
QString inputDir = "./";
QString outputDir;
UiPort * uiPort = NULL;

int exec(const QString & fileName, const QString & command, QString & result)
{
   result.clear();
   QStringList arguments = command.split(" ");
   QString program = *arguments.begin();
   arguments.erase(arguments.begin());
   QProcess process;
   process.start(program, arguments);
   if (!process.waitForStarted()) {
      return -1;
   }
   if (!process.waitForFinished()) {
      return -1;
   }
   result = process.readAllStandardError();
   if (result.isEmpty()) {
      return 0;
   } else {
//      return -1;
      return 0;
   }
}

static void removeGeneratedFiles(QDir & directory, const QStringList & filePatterns)
{
   QFileInfoList fileInfoList = directory.entryInfoList(filePatterns);
   QFileInfoList::const_iterator i = fileInfoList.constBegin();
   while (i != fileInfoList.constEnd()) {
      QString fileName = (*i).fileName();
      directory.remove(fileName);
      i++;
   }
   QFileInfoList subDirectoryList = directory.entryInfoList(QDir::Dirs);
   i = subDirectoryList.constBegin();
   while (i != subDirectoryList.constEnd()) {
      bool ignore = false;
      QString directoryName = (*i).fileName();
      if (!directoryName.isEmpty() &&
          directoryName[0] == '.') {
         ignore = true;
      }
      if (directoryName.compare("qt3", Qt::CaseInsensitive) == 0) {
         ignore = true;
      }
      if (!ignore) {
         QString subDirectoryPath = append(directory.absolutePath(), directoryName);
         QDir subDirectory(subDirectoryPath);
         removeGeneratedFiles(subDirectory, filePatterns);
      }
      i++;
   }
}

static void removeGeneratedFiles()
{
   QStringList generatedFilePatterns;
   generatedFilePatterns << "*.err";
   generatedFilePatterns << "*.log";
   generatedFilePatterns << "*.struct";
//   generatedFilePatterns << "*.ui4";
//   generatedFilePatterns << "*.qrc";
//   generatedFilePatterns << "*.ui";
   removeGeneratedFiles(QDir::current(), generatedFilePatterns);
}

static QString appendDirectory(const QString & text, const QString & tail)
{
   return text + "/" +tail;
}

static bool removeFiles(const QDir & baseDirectory, const QString & filePattern)
{
   return false;
}

static bool removeDirectory(const QString & path)
{
   QDir directory(path);
   QStringList entryList = directory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      if (directoryName[0] != '.') {
         QString subDirectoryPath = appendDirectory(directory.absolutePath(), directoryName);
         if (!removeDirectory(subDirectoryPath)) {
            return false;
         } else {
            if (!directory.rmdir(directoryName)) {
               return false;
            }
         }
      }
   }
   entryList = directory.entryList(QDir::Files);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = *it;
      QString subDirectoryPath = appendDirectory(directory.absolutePath(), fileName);
      if (!directory.remove(fileName)) {
         return false;
      }
   }
   return true;
}

static bool removeDirectories(const QDir & baseDirectory, const QString & directoryPattern)
{
   QString basePath = baseDirectory.absolutePath();
   QStringList entryList = baseDirectory.entryList(QStringList() << directoryPattern, QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      QString path = appendDirectory(basePath, directoryName);
      if (!removeDirectory(path)) {
         return false;
      }
   }
   entryList = baseDirectory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      if (directoryName[0] != '.') {
         QDir newDirectory(appendDirectory(baseDirectory.absolutePath(), directoryName));
         if (!removeDirectories(newDirectory, directoryPattern)) {
            return false;
         }
      }
   }
   return true;
}

int main(int argc, char* argv[])
{
   QApplication qApplication(argc, argv);

   QDir currentDirectory = QDir::current();
   removeGeneratedFiles();
//   removeDirectories(currentDirectory, "Qt4");

   options().addOption("files", "-f", "files included", "file pattern");
   options().addOption("clean", "-c", "clean project", "clean project");
   if (!options().parseArgs(argc, argv)) {
      cout << options().usage();
      return -1;
   }
   QString filePattern = options().parameter("files").c_str();
   if (filePattern.isEmpty()) {
      filePattern = "*.ui";
   }
   if (options().isSet("clean")) {
      return 0;
   }
   uiPort = new UiPort;
#define BUFFER_SIZE     500
   char * buffer = NULL;
   size_t bufferSize = 0;
   int err = _dupenv_s(&buffer, &bufferSize, "QTDIR");
   if (err == 0) {
      qtDir = buffer;
   } else {
      cout << "failed to get QTDIR" << endl;
      return -1;
   }
   qtBinDir = qtDir + "/bin";
   qtPluginDir = qtDir + "/plugins/designer";
   uic3Path = "uic3.exe";
   uicPath = "uic.exe";
   rccPath = "rcc.exe";
   uiPort->formBuilder().addPluginPath(qtPluginDir);

   PortingContext portingContext;
   portingContext.addFilePattern(filePattern);
   portingContext.setSourceQtVersion("Qt3");
   portingContext.setDestinationQtVersion("Qt4");
   portingContext.setHomeDirectory(currentDirectory);
   QStringList entryList = currentDirectory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      if (!directoryName.isEmpty() &&
          directoryName[0] != '.' &&
          directoryName != IMAGES_DIRECTORY) {
         portingContext.addApplication(directoryName);
      }
   }
   portingContext.collectFiles();
   portingContext.portFiles();
   portingContext.generateResources();
   portingContext.printFormHeaderInformations();
   delete uiPort;
   QStringList generatedFilePatterns;
   generatedFilePatterns << "*.ui4";
   removeGeneratedFiles(QDir::current(), generatedFilePatterns);
   return 0;
}

