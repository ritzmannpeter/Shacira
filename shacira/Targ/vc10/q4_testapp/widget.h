
#ifndef _widget_h_
#define _widget_h_

#include <qtreewidget.h>
#include <qheaderview.h>
#include <qlayout.h>
#include <qscrollbar.h>
#include <qsizegrip.h>

class Widget : public QTreeWidget
{
   Q_OBJECT
public:
   Widget(QWidget * parent);
   virtual ~Widget();

public slots:
   void horizontalScrollbarChanged(int value);
   void verticalScrollbarChanged(int value);
protected:
   virtual void drawRow(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif
