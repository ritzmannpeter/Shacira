#ifndef Q4_TESTAPP_H
#define Q4_TESTAPP_H

#include <QtGui/QMainWindow>
#include "ui_q4_testapp.h"
#include "listview.h"

class q4_testapp : public QMainWindow
{
    Q_OBJECT

public:
    q4_testapp(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~q4_testapp();
    inline ListView * listView() const {return _listView;};

public slots:
   void timerExpired();

private:
    Ui::q4_testappClass ui;
    ListView * _listView;
};

#endif // Q4_TESTAPP_H
