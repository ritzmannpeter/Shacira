
#include "FirstHeader.h"
#include "qapplication.h"
#include "memviewimpl.h"

int main(int argc, char* argv[])
{
   QApplication * app = new QApplication(argc, argv);
   MemView * form = new MemViewImpl;
   app->setMainWidget(form);
   form->show();
   return app->exec();
}
