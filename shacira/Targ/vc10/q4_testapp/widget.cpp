
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QTreeWidget(parent)
{
   QStringList labels;
   labels << "column1";
   labels << "column2";
   labels << "column3";
   labels << "column4";
   labels << "column5";
   setHeaderLabels(labels);
   int i = 0;
   for (i=0; i<50; i++) {
      QTreeWidgetItem * item = new QTreeWidgetItem(this);
      item ->setText(0, "column 1 " + QString::number(i));
      item ->setText(1, "column 2 " + QString::number(i));
      item ->setText(2, "column 3 " + QString::number(i));
      item ->setText(3, "column 4 " + QString::number(i));
   }
   QScrollBar * vscroll = verticalScrollBar();
   QScrollBar * hscroll = horizontalScrollBar();
   connect(hscroll, SIGNAL(valueChanged(int)), this, SLOT(horizontalScrollbarChanged(int)));
   connect(vscroll, SIGNAL(valueChanged(int)), this, SLOT(verticalScrollbarChanged(int)));
}
 
Widget::~Widget()
{  
}

void Widget::horizontalScrollbarChanged(int value)
{
   if (value < 0) {
      int dummy = 0;
   } else {
      int dummy = 1;
   }
}

void Widget::verticalScrollbarChanged(int value)
{
   if (value < 0) {
      int dummy = 0;
   } else {
      int dummy = 1;
   }
}

#include <qpainter.h>
void Widget::drawRow(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   int row = index.row();
   int column = index.column();
   if (column == 2) {
      painter->setBrush(QBrush(Qt::red));
   }
   QTreeView::drawRow(painter, option, index);
}


