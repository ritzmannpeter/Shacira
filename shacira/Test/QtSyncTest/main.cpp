
#include <qapplication.h>
#include <qlabel.h>
#include <qthread.h>
#include <qtimer.h>
#include <qmutex.h>
#include <qevent.h>
#include <stdlib.h>
#include <windows.h>
#include "timer.h"
#include <string>
#include <string.h>
#include <stdio.h>

static int _threadCount = 0;
static bool _restrictToOneCore = false;
static bool _testQStrings = false;
static bool _enableThreadedAccess = false;

#ifdef QT3
//static QMutex _valueMutex(true);
static QMutex _valueMutex;
#else
//static QMutex _valueMutex(QMutex::Recursive);
static QMutex _valueMutex;
#endif
static Qt::HANDLE _mainThreadId = QThread::currentThread();

class Label;
void showText(Label * label);

class Label : public QLabel
{
public:
   Label(QWidget * parent = 0)
      : QLabel(parent), _value("heinz"), _svalue("fuzzy")
   {
   };
   QString _value;
   std::string _svalue;
};

void showText(Label * label)
{
#ifdef QT3
   Qt::HANDLE threadId = QThread::currentThread();
#else
   Qt::HANDLE threadId = QThread::currentThreadId();
#endif
   int number = rand();
   char temp[0x255] = {0};
   _snprintf(temp, sizeof(temp), "%d", number);
   if (_testQStrings) {
      label->_value = temp;
   } else {
      label->_svalue = temp;
   }
   QMutexLocker __lock__(&_valueMutex);
   if (_mainThreadId == threadId) {
      if (label->_value.isEmpty() || label->_value == "heinz") {
         label->setText(label->_svalue.c_str());
      } else {
         label->setText(label->_value);
      }
      label->resize(50 + (rand() % 20), 20 + (rand() % 5));
   }
}

DWORD WINAPI TestThread(LPVOID lpParameter)
{
   Label * label = (Label*)lpParameter;
   QWidget * widget = NULL;
   QObject * object = label->parent();
   if (object != NULL) {
      if (object->isWidgetType()) {
         widget = dynamic_cast<QWidget*>(object);
      }
   }
   while (42) {
      if (_enableThreadedAccess) {
         showText(label);
      }
      int  milliSeconds = rand() % 20;
      if (milliSeconds > 10) {
         Sleep(milliSeconds);
      } else {
         Sleep(0);
      }
   }
}

void createThread(int index, QLabel * label)
{
   using namespace std;
   DWORD myThreadID;
   HANDLE myHandle = CreateThread(0, 0, TestThread, label, 0, &myThreadID);
}

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

int main(int argc, char* argv[])
{
   int arg = 0;
   for (arg=1; arg<argc; arg++) {
      if (stricmp(argv[arg], "qstrings") == 0) {
         _testQStrings = true;
      } else if (stricmp(argv[arg], "restrict") == 0) {
         _restrictToOneCore = true;
      } else {
         int v = atoi(argv[arg]);
         if (v >= 0) {
            _threadCount = v;
         }
      }
   }
   if (_restrictToOneCore) {
      restrictToOneCore();
   }
#ifdef QT3
   _mainThreadId = QThread::currentThread();
#else
   _mainThreadId = QThread::currentThreadId();
#endif
   QApplication * app = new QApplication(argc, argv);
   QWidget * widget = new QWidget;
   Label * label = new Label(widget);
   label->resize(60, 20);
   widget->show();
#ifdef QT3
   app->setMainWidget(widget);
#endif
   for (int i=0; i< _threadCount; i++) {
      createThread(i, label);
   }
   Timer * timer = new Timer(label);
#ifdef QT3
   timer->start(1);
#else
   timer->setInterval(1);
   timer->start();
#endif
   QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(expired()));
   _enableThreadedAccess = true;
   return app->exec();
}
