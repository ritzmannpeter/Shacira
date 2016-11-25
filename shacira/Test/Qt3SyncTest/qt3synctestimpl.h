
#ifndef _qt3synctestimpl_h_
#define _qt3synctestimpl_h_

#include "qt3synctest.h"
#include <qvector.h>
#include <qlabel.h>
#include <qthread.h>
#include <qmutex.h>

#define LABEL_COUNT     100
class TestLabel : public QLabel
{
public:
   TestLabel(QWidget * parent, const char * name, Qt::HANDLE mainThreadId)
      : QLabel(parent), _mainThreadId(mainThreadId)
   {
   };
   void showText(const QString & text)
   {
      QMutexLocker __lock__(&_textMutex);
      _text = text;
      if (_mainThreadId == QThread::currentThread()) {
         this->setText(_text);
      }
   };
protected:
   QString _text;
   QMutex _textMutex;
   Qt::HANDLE _mainThreadId;
};

class Qt3SyncTestImpl : public Qt3SyncTest
{
   Q_OBJECT

public:
   Qt3SyncTestImpl( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
   ~Qt3SyncTestImpl();
   void newValue();
   void newValue(const QString & labelName, const QString & value);
   QString labelName(int index) const;
protected slots:
   void timerExpired();
   void testStringThreadSafety();
protected:
   TestLabel* _labelVector[LABEL_COUNT];
   Qt::HANDLE _mainThreadId;
};

#endif // _qt3synctestimpl_h_
