
#include "q4_testapp.h"
#include <QtGui/QApplication>
#include <qscrollbar.h>
#include <qtimer.h>
#include <qheaderview.h>
#include "listview.h"

void updateHeader(ListView * listView);
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   q4_testapp w;
   ListView * listView = w.listView();
   QStringList labels;
   labels << "column1";
   labels << "column2";
   labels << "column3";
   labels << "column4";
   labels << "column5";
   listView->setHeaderLabels(labels);
   int i = 0;
   for (i=0; i<100; i++) {
      ListViewItem * item = new ListViewItem(listView);
      item ->setText(0, "column 1 " + QString::number(i));
      item ->setText(1, "column 2 " + QString::number(i));
      item ->setText(2, "column 3 " + QString::number(i));
      item ->setText(3, "column 4 " + QString::number(i));
   }
//   listView->setColor(0, 0, ListView::WindowText, Qt::red);
//   listView->setColor(1, 1, ListView::WindowText, Qt::yellow);
//   listView->setColor(2, 2, ListView::WindowText, Qt::green);
//   listView->setColor(3, 3, ListView::Window, Qt::black);
//   listView->setColor(3, 3, ListView::WindowText, Qt::white);
   listView->resizeColumnToContents(0);
   listView->resizeColumnToContents(1);
   listView->resizeColumnToContents(2);
   listView->resizeColumnToContents(3);
   listView->resizeColumnToContents(4);
   listView->resizeColumnToContents(5);
   QScrollBar * vscroll = listView->verticalScrollBar();
   QScrollBar * hscroll = listView->horizontalScrollBar();
   listView->connect(hscroll, SIGNAL(valueChanged(int)), listView, SLOT(horizontalScrollbarChanged(int)));
   listView->connect(vscroll, SIGNAL(valueChanged(int)), listView, SLOT(verticalScrollbarChanged(int)));
   QTimer * timer = new QTimer(&w);
   timer->setInterval(200);
   timer->start();
   w.connect(timer, SIGNAL(timeout()), &w, SLOT(timerExpired()));
   updateHeader(listView);
   w.show();
   return a.exec();
}

#include <qstandarditemmodel.h>

class HeaderModel : public QStandardItemModel
{
public:
   HeaderModel(ListView * listView)
      : _listView(listView)
   {
   };
   virtual int columnCount(const QModelIndex & parent = QModelIndex()) const
   {
      return _listView->columnCount();
   };
   virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const
   {
      QVariant data = QStandardItemModel::data(index, role);
      return data;
   };
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
   {
      if (role == Qt::DisplayRole) {
         QString headerText = "column " + QString::number(section);
         return QVariant(headerText);
      } else if (role == Qt::DecorationRole) {
         QPixmap pixmap(QString::fromUtf8(":/mosaic/images/img_166.png"));
         return QVariant(pixmap);
      } else if (role == Qt::FontRole) {
         QFont font("Arial", 20);
         return QVariant(font);
      } else if (role == Qt::TextAlignmentRole) {
         return QVariant(Qt::AlignRight);
      }
      return QVariant();
   };
private:
   ListView * _listView;
};

void updateHeader(ListView * listView)
{
   int count = listView->header()->count();
   QHeaderView * headerView = listView->header();
   HeaderModel * headerModel = new HeaderModel(listView);
   headerView->setModel(headerModel);
   int dummy = 0;
}
