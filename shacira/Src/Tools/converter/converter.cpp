
#include "FirstHeader.h"
#include "generator.h"
#include <qapplication.h>

void convertUiFiles(int argc, char* argv[], QApplication * app);

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   convertUiFiles(argc, argv, &app);
   app.exec();
   return 0;
}

void convertUiFiles(int argc, char* argv[], QApplication * app)
{
   cGenerator generator;
   QDir qDirectory;
   QStringList entryList = qDirectory.entryList("*.ui");
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = *it;
      QWidget * widget = generator.convert(fileName);
      if (widget != NULL) {
         app->setMainWidget(widget);
         widget->show();
      }
   }
}

