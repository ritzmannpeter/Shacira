#ifndef Q4_TESTAPP_H
#define Q4_TESTAPP_H

#include <QtGui/QMainWindow>
#include <qtimer.h>
#include "ui_q4_testview.h"
#include "listview.h"
#include "testview.h"

class q4_testview : public QMainWindow
{
    Q_OBJECT

public:
    q4_testview(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~q4_testview();
    inline TestView * testView() const {return _testView;};

public slots:
   void timerExpired();

public:
    Ui::q4_testviewClass ui;
    TestView * _testView;
protected:
   QTimer * _refreshTimer;
   TestViewItem * _coloredItem;
   int _coloredColumn;
};

#endif // Q4_TESTAPP_H
