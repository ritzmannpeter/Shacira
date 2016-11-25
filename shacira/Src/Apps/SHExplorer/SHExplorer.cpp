
#include "FirstHeader.h"
#include "System/Channel/cLocalChannel.h"
#include "System/Sys/cSysProcess.h"
#include "System/Sys/cSockets.h"
#include "Orb/cBroker.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Process/cResources.h"
#include "System/Process/cSHClientProcess.h"
#include "cserverlist.h"
#include "ExplorerForm.h"
#include "shexplorer_version.h"
#include <qgroupbox.h>
#include <qapplication.h>
#include <qlayout.h>


static ExplorerForm * _ExplorerForm = NULL;
int main(int argc, char* argv[])
{
   cResources::set_LogFileName("SHExplorer.log");
   cResources::set_UseDebugLog(false);
   cResources resources(argc, argv);

   char title[0x200] = {0};
   sprintf(title, "Shacira CCS Explorer %s , Shacira-Vers.: %d.%d.%d", STR_SHEXPLORER_VER, SHACIRA_MAJOR, SHACIRA_MINOR, SHACIRA_BUG_FIX);
   InfoPrintf("Start %s\n", title);

   cSockets::Initialize();
   cBroker::Initialize();
   cSHClientProcess process;
   process.AddProxyReceiver(21001);
   process.AddProxyReceiver(21002);
   process.AddProxyReceiver(21003);
   process.set_Path(argv[0]);
   process.Start();
   cResources::RegisterProcess(&process);
   QApplication app(argc, argv);
   QWidget * main_widget = new QWidget(NULL);
   QFont font("Arial", 11);
   main_widget->setFont(font);
   main_widget->setCaption(title);
   main_widget->setMinimumSize(600, 300);
   _ExplorerForm = new ExplorerForm(main_widget);
   _ExplorerForm->setMinimumSize(500, 100);
   QVBoxLayout * layout = new QVBoxLayout(main_widget);
   CServerList * server_list = new CServerList(main_widget, &process);
//   QObject::connect((const QObject*)_ExplorerForm->RefreshButton, SIGNAL(clicked()), server_list, SLOT(clear()));
   layout->addWidget(_ExplorerForm);
   layout->addWidget(server_list);
   app.setMainWidget(main_widget);
   main_widget->show();
   return app.exec();
}



