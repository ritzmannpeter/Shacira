
#include "qt3synctestimpl.h"
#include <qlayout.h>
#include <qtimer.h>

#include <windows.h>
#include <iostream>
#include <assert.h>

DWORD WINAPI TestThread(LPVOID lpParameter)
{
   Qt3SyncTestImpl * testImpl = (Qt3SyncTestImpl*)lpParameter;
   while (42) {
      testImpl->newValue();
      Sleep(1);
   }
}

void createThread(int index, Qt3SyncTestImpl * testImpl)
{
	using namespace std;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, TestThread, testImpl, 0, &myThreadID);
}

Qt3SyncTestImpl::Qt3SyncTestImpl( QWidget* parent, const char* name, WFlags fl )
    : Qt3SyncTest( parent )
{
   extern int _threadCount;
   _mainThreadId = QThread::currentThreadId();
   QGridLayout * layout = new QGridLayout(this->_ui.frame4);
   layout->setSpacing(5);
   layout->setMargin(5);
   int i = 0;
   for (i=0; i<LABEL_COUNT; i++) {
      QString labelName = this->labelName(i);
      TestLabel * testLabel = new TestLabel(this->_ui.frame4, labelName.toStdString().c_str(), _mainThreadId);
      testLabel->showText(labelName);
      int row = i / 20;
      int col = i % 20;
      layout->addWidget(testLabel, row, col);
      _labelVector[i] = testLabel;
   }
   for (i=0; i<_threadCount; i++) {
      createThread(i, this);
   }
   QTimer * timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
   timer->start(1);
}

Qt3SyncTestImpl::~Qt3SyncTestImpl()
{
}

void Qt3SyncTestImpl::newValue()
{
   QMutexLocker __lock__(&_textMutex);
   int index = rand() % LABEL_COUNT;
   int ivalue = rand();
   QString labelName = this->labelName(index);
   QString value;
   value.sprintf("%d", ivalue);
   this->newValue(labelName, value);
}

void Qt3SyncTestImpl::newValue(const QString & labelName, const QString & value)
{
   const char * indexPos = labelName.toStdString().c_str();
   indexPos += 5;
   int index = atoi(indexPos);
   if (index >= 0 && index < LABEL_COUNT) {
      TestLabel * label = _labelVector[index];
      label->showText(value);
   }
}

QString Qt3SyncTestImpl::labelName(int index) const
{
   QString name;
   name.sprintf("label%d", index);
   return name;
}

void Qt3SyncTestImpl::timerExpired()
{
   newValue();
}

void TestLabel::showText(const QString & text)
{
   _text = text;
   if (_mainThreadId == QThread::currentThreadId()) {
      this->setText(_text);
   }
}
