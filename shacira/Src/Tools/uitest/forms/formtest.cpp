
#include "formtest.h"
#include <qevent.h>

FormTest::FormTest(QStackedWidget * externalStack, QWidget * parent)
   : QMainWindow(parent), _externalStack(externalStack)
{
   _ui.setupUi(this);
   connect(_ui.forward, SIGNAL(triggered()), this, SLOT(slotNextPage()));
   connect(_ui.back, SIGNAL(triggered()), this, SLOT(slotPreviousPage()));
}

FormTest::~FormTest()
{
}

void FormTest::keyReleaseEvent(QKeyEvent * event)
{
   if (event->key() == Qt::Key_V) {
      slotNextPage();
   }
   if (event->key() == Qt::Key_Z) {
      slotPreviousPage();
   }
   QMainWindow::keyReleaseEvent(event);
}

void FormTest::addWidget(QWidget * widget)
{
   QStackedWidget * stack = this->stack();
   if (widget->inherits("CPage")) {
      int index = stack->addWidget(widget);
      stack->setCurrentWidget(widget);
   }
   if (widget->inherits("QWizard")) {
      int dummy = 0;
      return;
   }
   if (widget->inherits("CActionDialog")) {
      int dummy = 0;
      return;
   }
   if (widget->inherits("QDialog")) {
      int dummy = 0;
      return;
   }
}

void FormTest::slotNextPage()
{
   QStackedWidget * stack = this->stack();
   int currentIndex = stack->currentIndex();
   currentIndex++;
   if (currentIndex >= stack->count()) {
      currentIndex = 0;
   }
   stack->setCurrentIndex(currentIndex);
}

void FormTest::slotPreviousPage()
{
   QStackedWidget * stack = this->stack();
   int currentIndex = stack->currentIndex();
   currentIndex--;
   if (currentIndex < 0) {
      currentIndex = stack->count() - 1;
   }
   stack->setCurrentIndex(currentIndex);
}

QStackedWidget * FormTest::stack() const
{
   if (_externalStack != NULL) {
      return _externalStack;
   } else {
      return _ui.formTestStack;
   }
}

