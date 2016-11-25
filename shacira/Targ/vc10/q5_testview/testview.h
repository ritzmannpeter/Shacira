
#ifndef _testview_h_
#define _testview_h_

#include <qtreewidget.h>
#include <qheaderview.h>
#include <qlayout.h>
#include <qscrollbar.h>
#include <qsizegrip.h>
#include <qpainter.h>
#include "listview.h"
#include "listviewitem.h"

class TestView;

class TestViewItem : public ListViewItem
{
public:
   TestViewItem(TestView * testView, int i = -1, int j = -1, int k = -1);
   TestViewItem(TestViewItem * testViewItem, int i = -1, int j = -1, int k = -1);
   virtual ~TestViewItem();
protected:
   virtual void paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index);
private:
   int _i;
   int _j;
   int _k;
   QString _text;
   void setText();
};

class TestView : public ListView
{
   Q_OBJECT
public slots:
   void refresh();
public:
   TestView(QWidget * parent);
   virtual ~TestView();
protected slots:
   virtual void slotItemClicked(QTreeWidgetItem * item, int column);
};

#endif
