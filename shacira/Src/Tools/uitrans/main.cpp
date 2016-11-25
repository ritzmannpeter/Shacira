
#include <qstring.h>
#include <qapplication.h>
#include <qfile.h>
#include <qdir.h>
#include <qprocess.h>
#include <qtextstream.h>
#include <iostream>
#include <fstream>
#include "uitrans.h"
#include "options.h"
#include <qwidget.h>
#include "portingfile.h"
#include "portingapplication.h"
#include "portingcontext.h"
#include "replacement.h"

static char _Text[0x2000] = {0};

string logFileName()
{
   return "q4_uitrans.log";
}

string errorFileName()
{
   return "q4_uitrans.err";
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
   if (!process.waitForFinished(120000)) {
      return -1;
   }
   result = process.readAllStandardError();
   if (result.isEmpty()) {
      return 0;
   } else {
      return 0;
   }
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

static void invalidUsage()
{
   fprintf(stderr, "invalid usage\n");
   fprintf(stderr, "q4_trans <options>\n");
   fprintf(stderr, "  option cpp: convert c++ source code (.cpp,.h,.pp)\n");
   fprintf(stderr, "  option pro: convert project files (.vcxproj,.filters)\n");
   fprintf(stderr, "  option ui: convert forms (.ui)\n");
   fprintf(stderr, "\n\n");
}

UiTrans * _uiTrans = NULL;

// suspicious string usage

bool compareString(const char * s_ptr, const QString & s)
{
   if (strcmp(s_ptr, s.toStdString().c_str()) == 0) {
      return true;
   } else {
      return false;
   }
}

void testStrings()
{
   QString s = "heinz";
   string stdString = s.toStdString();
   const char * s_ptr1 = stdString.c_str();
   const char * s_ptr2 = s.toStdString().c_str();
   const char * s_ptr3 = s.toAscii();
   bool rc = false;
   rc = compareString(s.toStdString().c_str(), s); // okay
   rc = compareString(s.toAscii(), s);             // okay
   rc = compareString(s_ptr1, s);                  // okay
   rc = compareString(s_ptr2, s);                  // not okay
   rc = compareString(s_ptr3, s);                  // not okay
   int dummy = 0;
}

int main(int argc, char* argv[])
{
   bool convertUiFiles = false;
   bool convertProjectFiles = false;
   bool convertSourcecode = false;
   int i = 0;
   for (i=1; i<argc; i++) {
      const char * option = argv[i];
      if (_stricmp(option, "pro") == 0) {
         convertProjectFiles = true;
      } else if (_stricmp(option, "cpp") == 0) {
         convertSourcecode = true;
      } else if (_stricmp(option, "ui") == 0) {
         convertUiFiles = true;
      } else {
         invalidUsage();
         return -1;
      }
   }

   QApplication qApplication(argc, argv);
   QDir currentDirectory = QDir::current();
//   removeDirectories(currentDirectory, "Qt4");

   _uiTrans = new UiTrans;;
   PortingContext portingContext;
   if (convertProjectFiles) {
      portingContext.clear();
      cout << "converting project and filter files from " << currentDirectory.absolutePath().toStdString().c_str() << " ..." << endl;
      portingContext.addFilePattern("*.vcxproj");
      portingContext.addFilePattern("*.filters");
      portingContext.setSourceQtVersion("Qt3");
      portingContext.setDestinationQtVersion("Qt4");
      portingContext.setHomeDirectory(currentDirectory);
      QStringList entryList = currentDirectory.entryList(QDir::Dirs);
      for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
         QString directoryName = *it;
         if (!directoryName.isEmpty() &&
             directoryName[0] != '.' &&
             directoryName != "images") {
            portingContext.addApplication(directoryName);
         }
      }
      portingContext.collectFiles();
      portingContext.portFiles();
      cout << "successfully converted project and filter files" << endl;
   }
   if (convertSourcecode) {
      cout << "converting cpp,h and pp files from " << currentDirectory.absolutePath().toStdString().c_str() << " ..." << endl;
      portingContext.clear();
#ifdef _DEBUGx
      portingContext.addFilePattern("mproctrendgraphic.cpp");
#else
      portingContext.addFilePattern("*.cpp");
      portingContext.addFilePattern("*.h");
      portingContext.addFilePattern("*.pp");
#endif
      portingContext.setSourceQtVersion("Qt3");
      portingContext.setDestinationQtVersion("Qt4");
      portingContext.setHomeDirectory(currentDirectory);
      QStringList entryList = currentDirectory.entryList(QDir::Dirs);
      for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
         QString directoryName = *it;
         if (!directoryName.isEmpty() &&
             directoryName[0] != '.' &&
             directoryName != "images") {
            portingContext.addApplication(directoryName);
         }
      }
      portingContext.collectFiles();
      portingContext.portFiles();
      cout << "successfully converted cpp,h and pp files" << endl;
   }
   if (convertUiFiles) {
      cout << "converting ui files from " << currentDirectory.absolutePath().toStdString().c_str() << " ..." << endl;
      QString result;
      int rc = exec("q4_uiport.exe", "q4_uiport.exe", result);
      if (rc == 0) {
         cout << result.toStdString().c_str() << endl;
         cout << "successfully converted ui files" << endl;
         cout << "cleaning up generated files ..." << endl;
         rc = exec("q4_uiport.exe", "q4_uiport.exe -c", result);
         if (rc == 0) {
            cout << "successfully cleaned up generated files" << endl;
         } else {
            cout << "failed to cleanup generated files" << endl;
            return -1;
         }
      } else {
         cout << "failed to convert ui files" << endl;
         return -1;
      }
      removeFiles(currentDirectory, "*.ui4");
   }
   return 0;
}

