
#ifndef _formtest_h_
#define _formtest_h_

#include <qmainwindow.h>
#include "ui_formtest.h" 

class FormTest : public QMainWindow
{
   Q_OBJECT
public:
   FormTest(QStackedWidget * externalStack, QWidget* parent = 0);
   virtual ~FormTest();
   void addWidget(QWidget * widget);
protected:
   void keyReleaseEvent(QKeyEvent * event);
   QStackedWidget * stack() const;
public slots:
   void slotNextPage();
   void slotPreviousPage();
private:
   Ui::FormTest _ui;
   QStackedWidget * _externalStack;
};

#endif

