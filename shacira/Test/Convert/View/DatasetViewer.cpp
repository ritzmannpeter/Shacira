
#include "FirstHeader.h"
#include <qapplication.h>
#include <qlayout.h>
#include <qlabel.h>
#include "Generated/DatasetViewerForm.h"
#include "View/csubfilelist.h"
#include "View/coutput.h"

static DatasetViewerForm * _Viewer = NULL;
static CSubfileList * _FileList = NULL;
static COutput * _Output = NULL;

void Out(const char * line)
{
   if (_Output != NULL) {
      _Output->AddLine(line);
   }
}

void ClearOutput()
{
   if (_Output != NULL) {
      _Output->Clear();
   }
}

void ClearList()
{
   if (_FileList != NULL) {
      _FileList->Clear();
   }
}

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   QWidget * main_widget = new QWidget(NULL);
   QFont font("Arial", 11);
   main_widget->setFont(font);
   main_widget->setCaption("FM Legacy Dataset Viewer");
   main_widget->setMinimumSize(800, 600);
   _Viewer = new DatasetViewerForm(main_widget);
   _Viewer->setMinimumSize(200, 100);
   QVBoxLayout * layout = new QVBoxLayout(main_widget);
   layout->addWidget(_Viewer);
   _FileList = new CSubfileList(main_widget, _Viewer);
   layout->addWidget(_FileList);
   _Output = new COutput(main_widget);
   _Output->setMaximumHeight(200);
   layout->addWidget(_Output);
   app.setMainWidget(main_widget);
   main_widget->show();
   QObject::connect((const QObject*)_Viewer->SelectFileButton, SIGNAL(clicked()), _FileList, SLOT(SelectFile()));
   QObject::connect((const QObject*)_Viewer->SelectTplButton, SIGNAL(clicked()), _FileList, SLOT(SelectTemplate()));
   QObject::connect((const QObject*)_Viewer->SelectRegtextButton, SIGNAL(clicked()), _FileList, SLOT(SelectRegtext()));
   return app.exec();
}



