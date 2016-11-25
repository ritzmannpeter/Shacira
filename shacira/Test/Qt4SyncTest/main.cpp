
#include "qapplication.h"
#include "qt3synctestimpl.h"
#include <stdlib.h>
#include <windows.h>

void restrictToOneCore()
{
   HANDLE phnd = GetCurrentProcess();
   DWORD process_mask = 0;
   DWORD system_mask = 0;
   BOOL success = GetProcessAffinityMask(phnd, &process_mask, &system_mask);
   if (success) {
      if (process_mask != 0x00000001) {
         /// more than one logical processor available for the process
         /// f.e. hyperthreading capable and enabled processors
         /// f.e. SMP board with more than one processor
         success = SetProcessAffinityMask(phnd, 0x00000001);
         if (success) {
            /// use only one processor to execute threads
         } else {
            int err = GetLastError();
         }
      }
      /// only one logical processor available
   } else {
      int err = GetLastError();
   }
}

int _threadCount = 10;
int main(int argc, char* argv[])
{
//   restrictToOneCore();
   if (argc > 1) {
      _threadCount = atoi(argv[1]);
   }
   QApplication * app = new QApplication(argc, argv);
   Qt3SyncTest * form = new Qt3SyncTestImpl;
//   app->setMainWidget(form);
   form->show();
   return app->exec();
}
