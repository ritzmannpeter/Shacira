
#include "q4_testview.h"
#include "testview.h"

q4_testview::q4_testview(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), _coloredItem(NULL), _coloredColumn(-1)
{
   ui.setupUi(this);
   QVBoxLayout * l = new QVBoxLayout(ui.frame);
   _testView = new TestView(NULL);
   _testView->setSortingEnabled(true);
   l->addWidget(_testView);
   _refreshTimer = new QTimer;
   _refreshTimer->setInterval(1000);
   _refreshTimer->start();
   connect(_refreshTimer, SIGNAL(timeout()), this, SLOT(timerExpired()));
}

q4_testview::~q4_testview()
{
}

void q4_testview::timerExpired()
{
static int initialized = false;
   if (initialized) {
//      return;
   } else {
      initialized = true;
      _testView->expandAll();
   }
   _testView->viewport()->update();
   if (_coloredItem != NULL) {
      _coloredItem->clearColor(_coloredColumn);
      _coloredItem = NULL;
   } else {
      TestViewItem * testViewItem = NULL;
      QModelIndex itemIndex;
      int column = -1;
      int row = -1;
      while (testViewItem == NULL) {
         int x = rand() % width();
         int y = rand() % height();
         QPoint p(x, y);
         itemIndex = _testView->indexAt(p);
         column = itemIndex.column();
         row = itemIndex.row();
         testViewItem = dynamic_cast<TestViewItem*>(_testView->itemAt(p));
      }
      testViewItem->setColor(column, Qt::yellow);
      _coloredItem = testViewItem;
      _coloredColumn = column;
      _testView->viewport()->update();
   }
}
