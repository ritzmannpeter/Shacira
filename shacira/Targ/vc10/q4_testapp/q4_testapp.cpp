
#include "q4_testapp.h"
#include "widget.h"
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include "listview.h"

#define COLUMNS   10
#define CAPACITY  600
#define TIMER_VALUE 600

#define LView ListView
#define LViewItem ListViewItem
//#define LView ListView
//#define LViewItem ListViewItem

class C2ListViewItem : public ListViewItem
{
public:
   C2ListViewItem(ListView * listView)
      : ListViewItem(listView)
   {
   };
   C2ListViewItem(ListView * listView, C2ListViewItem * after)
      : ListViewItem(listView, after)
   {
   };
protected:
   virtual void paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
   {
      ListViewItem::paintCell(painter, option, index);
   };
};

class C7ListViewItem : public C2ListViewItem
{
public:
   C7ListViewItem(ListView * listView)
      : C2ListViewItem(listView)
   {
   };
   C7ListViewItem(ListView * listView, C7ListViewItem * after)
      : C2ListViewItem(listView, after)
   {
   };
protected:
   virtual void paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
   {
      ListViewItem::paintCell(painter, option, index);
   };
};

class C8ListViewItem : public C7ListViewItem
{
public:
   C8ListViewItem(ListView * listView)
      : C7ListViewItem(listView)
   {
      setHeight(60);
   };
   C8ListViewItem(ListView * listView, C8ListViewItem * after)
      : C7ListViewItem(listView, after)
   {
      setHeight(60);
   };
protected:
   virtual void paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
   {
      ListViewItem::paintCell(painter, option, index);
   };
};

static LView * _listView = NULL;

q4_testapp::q4_testapp(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
   ui.setupUi(this);
   QTimer * timer = new QTimer(this);
   timer->setInterval(TIMER_VALUE);
   timer->start();
   connect(timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
   QVBoxLayout * l = new QVBoxLayout(ui.frame);
   _listView = new LView(NULL);
   _listView->setUniformRowHeights(true);
   QPushButton * clearButton = new QPushButton(_listView);
   clearButton->setText("clear");
clearButton->hide();
   connect(clearButton, SIGNAL(clicked()), this, SLOT(slotClear()));
   l->addWidget(_listView);
   buildView();
}

q4_testapp::~q4_testapp()
{
}

class C4ListViewItem : public ListViewItem
{
public:
   C4ListViewItem(ListView * listView, const QString & label1 = QString(), const QString & label2 = QString(), const QString & label3 = QString(), const QString & label4 = QString(), const QString & label5 = QString(), const QString & label6 = QString(), const QString & label7 = QString(), const QString & label8 = QString());
   C4ListViewItem(ListView * listView)
      : ListViewItem(listView, NULL)
   {
   };
   C4ListViewItem(ListView * listView, C4ListViewItem * after)
      : ListViewItem(listView, after)
   {
   };
   C4ListViewItem(C4ListViewItem * listViewItem, const QString & label1 = QString(), const QString & label2 = QString(), const QString & label3 = QString(), const QString & label4 = QString(), const QString & label5 = QString(), const QString & label6 = QString(), const QString & label7 = QString(), const QString & label8 = QString());
   C4ListViewItem(C4ListViewItem * listViewItem, C4ListViewItem * after);
   virtual ~C4ListViewItem()
   {
   };
   void setImage(int column, const QImage & image);
protected:
   virtual void paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
   {
      ListViewItem::paintCell(painter, option, index);
   };
   virtual void initStyleOption(QStyleOptionViewItem * option, const QModelIndex & index) const
   {
   };
protected:
   std::map<int,QColor> _colorMap;
public:
   inline bool isColored(int column) const
   {
      std::map<int,QColor>::const_iterator i = _colorMap.find(column);
      if (i == _colorMap.end()) {
         return false;
      } else {
         return true;
      }
   };
   inline void clearColor(int column)
   {
      _colorMap.erase(column);
   }
   inline QColor getColor(int column) const
   {
      std::map<int,QColor>::const_iterator i = _colorMap.find(column);
      if (i == _colorMap.end()) {
         return QColor();
      } else {
         return (*i).second;;
      }
   }
   inline void setColor(int column, const QColor &color)
   {
      _colorMap[column] = color;
   }
public:
   virtual void setHeight(int height)
   {
   };
};

void q4_testapp::timerExpired()
{
return;
static int i = 0;
   int rows = _listView->childCount();
   if (rows >= CAPACITY) {
      LViewItem * lastItem = (LViewItem*)_listView->lastItem();
      if (lastItem != NULL) {
         delete lastItem;
      }
   }
//   LViewItem * item = new LViewItem(_listView, 0);
   C8ListViewItem * item = new C8ListViewItem(_listView, 0);
//   QPixmap pixmap1;
//   pixmap1.load(":/mosaic/images/Core/StartCondition/Imd_OpenMold.png");
//   item->setPixmap(3, pixmap1);
//   pixmap1 = pixmap1.scaled(QSize(100,100));
//   pixmap1 = pixmap1.scaled(QSize(20,20));
//   QPixmap pixmap2;
//   pixmap2.load(":/mosaic/images/Core/Other/Mtrx_Kern_Einltg+Abschluss.png");
//   item->setPixmap(4, pixmap2);
//   MyItem * item = new MyItem(_listView, 0); // works with ListView
//   ListViewItem * item = new ListViewItem(_listView, 0);
//   C4ListViewItem * item = new C4ListViewItem(_listView, 0);
//   C5ListViewItem * item = new C5ListViewItem(_listView, 0); // works with ListView
//   Q3ListViewItem * item = new Q3ListViewItem(_listView, 0);
   int col = 0;
   int fact = 1;
   for (col=0; col<COLUMNS; col++) {
      fact *= 10;
      QString text = QString::number(i + fact);
if ((rand() % 20) == 0) {
   text = "this is a very long text and used for testing purpose";
}
      item ->setText(col, text);
   }
   i++;
if (i > CAPACITY - 10) {
   int dummy = 0;
}
}

void q4_testapp::slotClear()
{
   int columns = _listView->columns();
   int column = 0;
   for (column=0; column<columns; column++) {
      _listView->setColumnWidth(column, 30);
   }
   return;
#ifdef lassma
   int itemCount = 20;
   LViewItem * lastItem = (LViewItem*)_listView->lastItem();
   while (lastItem != NULL && itemCount--) {
      delete lastItem;
      lastItem = (LViewItem*)_listView->lastItem();
   }
#else
   _listView->clear();
#endif
}

void q4_testapp::buildView()
{
   _listView->setSorting(-1, false);
   _listView->clear();
   int col = 0;
   for (col=0; col<COLUMNS; col++) {
      QString text = "column " + QString::number(col);
//      if ((col % 2) == 0) {
      if (false) {
         _listView->addColumn(text);
      } else {
         QPixmap pixmap;
         pixmap.load(":/mosaic/images/Core/StartCondition/Imd_OpenMold.png");
         pixmap = pixmap.scaled(150, 150);
         QImage image = pixmap.toImage();
//         _listView->header()->setPixmap(col, pixmap);
         _listView->addColumn(image, pixmap.size().width() + 20);
      }
   }
   for (col=0; col<COLUMNS; col++) {
      int s = _listView->header()->sectionSize(col);
      int dummy = 0;
   }
//   _listView->header()->adjustPixmaps();
   for (col=0; col<COLUMNS; col++) {
      int s = _listView->header()->sectionSize(col);
      int dummy = 0;
   }
   int i = 0;
   for (i=0; i<CAPACITY;i ++) {
      timerExpired();
   }
}

