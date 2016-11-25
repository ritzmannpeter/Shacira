

#include "q4_testapp.h"
#include <QtGui/QApplication>
#include <qscrollbar.h>
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

int main(int argc, char *argv[])
{
   restrictToOneCore();
   QApplication a(argc, argv);
   q4_testapp w;
   w.show();
   return a.exec();
}

