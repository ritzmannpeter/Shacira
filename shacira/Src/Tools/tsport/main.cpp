
#include <qstring.h>
#include <qapplication.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qdir.h>
#include <qprocess.h>
#include <qtextstream.h>
#include "tsport.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
   QString path;
   if (argc != 2) {
      return -1;
   } else {
      path = argv[1];
   }
   QApplication qApplication(argc, argv);
   QFile inputFile(path);
   if (inputFile.exists()) {
      TSPort tsPort;
      QFileInfo fileInfo(path);
      path = fileInfo.absoluteFilePath();
      tsPort.analyze(path);
      tsPort.generate("heinz.ts");
//      tsPort.generate();
   }
   return 0;
}

