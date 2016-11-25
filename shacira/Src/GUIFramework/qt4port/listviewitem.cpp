
#include "listviewitem.h"
#include "listviewitemdelegate.h"
#include <qpainter.h>

#ifndef QT_PLUGIN
#include "CWidgetBase.h"
#endif

ListViewItem::ListViewItem(ListView * listView, const QString & label1, const QString & label2, const QString & label3, const QString & label4, const QString & label5, const QString & label6, const QString & label7, const QString & label8)
   : QTreeWidgetItem(listView, QStringList() << label1 << label2 << label3 << label4 << label5 << label6 << label7 << label8),
     _isSelectable(true)
{
   setColumnAlignments();
}

ListViewItem::ListViewItem(ListView * listView, ListViewItem * after)
   : QTreeWidgetItem(listView, after),
     _isSelectable(true)
{
   setColumnAlignments();
}

ListViewItem::ListViewItem(ListViewItem * listViewItem, const QString & label1, const QString & label2, const QString & label3, const QString & label4, const QString & label5, const QString & label6, const QString & label7, const QString & label8)
   : QTreeWidgetItem(listViewItem, QStringList() << label1 << label2 << label3 << label4 << label5 << label6 << label7 << label8),
     _isSelectable(true)
{
   setColumnAlignments();
}

ListViewItem::ListViewItem(ListViewItem * listViewItem, ListViewItem * after)
   : QTreeWidgetItem(listViewItem, after),
     _isSelectable(true)
{
   setColumnAlignments();
}

ListViewItem::~ListViewItem()
{
}

ListViewItem * ListViewItem::parent() const
{
   QTreeWidgetItem * item = QTreeWidgetItem::parent();
   return static_cast<ListViewItem*>(item);
}

ListViewItem * ListViewItem::firstChild() const
{
   int itemCount = childCount();
   if (itemCount > 0) {
      return static_cast<ListViewItem*>(child(0));
   } else {
      return NULL;
   }
}

ListViewItem * ListViewItem::nextSibling() const
{
   ListViewItem * parent = this->parent();
   if (parent == NULL) {
      ListView * listView = this->listView();
      if (listView != NULL) {
         int itemCount = listView->topLevelItemCount();
         int i = 0;
         for (i=0; i<itemCount; i++) {
            ListViewItem * item = static_cast<ListViewItem*>(listView->topLevelItem(i));
            if (item == this) {
               if (i != itemCount - 1) {
                  ListViewItem * sibling = static_cast<ListViewItem*>(listView->topLevelItem(i + 1));
                  return sibling;
               }
            }
         }
      }
   } else {
      int itemCount = parent->childCount();
      int i = 0;
      for (i=0; i<itemCount; i++) {
         ListViewItem * item = static_cast<ListViewItem*>(parent->child(i));
         if (item == this) {
            if (i != itemCount - 1) {
               ListViewItem * sibling = static_cast<ListViewItem*>(parent->child(i + 1));
               return sibling;
            }
         }
      }
   }
   return NULL;
}

ListView * ListViewItem::listView() const
{
   return static_cast<ListView*>(treeWidget());
}

ListViewItem * ListViewItem::itemBelow() const
{
   QTreeWidget * treeWidget = this->treeWidget();
   QTreeWidgetItem * item = treeWidget->itemBelow(this);
   return static_cast<ListViewItem*>(item);
}

ListViewItem * ListViewItem::itemAbove() const
{
   QTreeWidget * treeWidget = this->treeWidget();
   QTreeWidgetItem * item = treeWidget->itemAbove(this);
   return static_cast<ListViewItem*>(item);
}

void ListViewItem::setPixmap(int column, const QPixmap & pixmap)
{
   setData(column, Qt::DecorationRole, QVariant(pixmap));
}

const QPixmap ListViewItem::pixmap(int column)
{
   return data(column, Qt::DecorationRole).value<QPixmap>();
}

void ListViewItem::setImage(int column, const QImage & image)
{
   setData(column, Qt::DecorationRole, QVariant(QPixmap::fromImage(image)));
}

int ListViewItem::itemPos()
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return 0;
}

void ListViewItem::setOpen(bool state)
{
   setExpanded(state);
}

void ListViewItem::setExpandable(bool state)
{
   if (state) {
//      setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicatorWhenChildless);
      if (childCount() > 0) {
         setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
      }
   } else {
      setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
   }
#ifdef doku
enum QTreeWidgetItem::ChildIndicatorPolicy
Constant	Value	Description
QTreeWidgetItem::ShowIndicator	0	The controls for expanding and collapsing will be shown for this item even if there are no children.
QTreeWidgetItem::DontShowIndicator	1	The controls for expanding and collapsing will never be shown even if there are children. If the node is forced open the user will not be able to expand or collapse the item.
QTreeWidgetItem::DontShowIndicatorWhenChildless	2	The controls for expanding and collapsing will be shown if the item contains children.
This enum was introduced or modified in Qt 4.3.
#endif

}

void ListViewItem::setSelectable(bool state)
{
   _isSelectable = state;
}

void ListViewItem::widthChanged(int column)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
//   setHeight(50);
}

int ListViewItem::depth() const
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return 0;
}

void ListViewItem::invalidateHeight()
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void ListViewItem::setHeight(int height)
{
   QSize sizeHint = this->sizeHint(0);
   if (sizeHint.width() == -1) {
      QFontMetrics fontMetrics = QFontMetrics(this->font(0));
      int width = this->width(fontMetrics, NULL, 0) + 6;
      QPixmap pixmap = this->pixmap(0);
      if (pixmap.isNull() == false) {
          width += pixmap.size().width();
      }
      sizeHint.setWidth(width);
   }

   sizeHint.setHeight(height);
   setSizeHint(0, sizeHint);
}

void ListViewItem::repaint()
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void ListViewItem::setup()
{
   widthChanged();
}

int ListViewItem::compare(ListViewItem * item, int col, bool ascending) const
{
   QString leftText = this->text(col);
   QString rightText = item->text(col);
   if (leftText == rightText) {
      return 0;
   } else if (leftText < rightText) {
      return -1;
   } else {
      return 1;
   }
}

int ListViewItem::height() const
{
   return listView()->visualItemRect(this).height();
}

int ListViewItem::width() const
{
   return listView()->visualItemRect(this).width();
}

int ListViewItem::width(const QFontMetrics & fontMetrics, ListView * listView, int column) const
{
   QString text = this->text(column);
   QRect	rect = fontMetrics.boundingRect(text);
   return rect.width();
}

bool ListViewItem::isSelectable() const
{
   return _isSelectable;
}

void ListViewItem::paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
{
   if (listView()->hasCustomDelegate()) {
      QAbstractItemDelegate * d = listView()->itemDelegate();
      ListViewItemDelegate * itemDelegate = dynamic_cast<ListViewItemDelegate*>(d);
      if (itemDelegate != NULL) {
         QStyleOptionViewItemV4 adjustedOption = option;
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#ifndef QT_PLUGIN
         if (CWidgetBase::Flag(USE_GESTURE)) {
            adjustedOption.state &= ~QStyle::State_MouseOver;
         }
#endif
#endif
         itemDelegate->QStyledItemDelegate::paint(painter, adjustedOption, index);
      }
   }
}

void ListViewItem::initStyleOption(QStyleOptionViewItem * option, const QModelIndex & index) const
{
   if (listView()->hasCustomDelegate()) {
      QAbstractItemDelegate * d = listView()->itemDelegate();
      ListViewItemDelegate * itemDelegate = dynamic_cast<ListViewItemDelegate*>(d);
      if (itemDelegate != NULL) {
         itemDelegate->initStyleOption(option, index);
      }
   }
}

void ListViewItem::setForegroundColor(QModelIndex index, QColor color)
{
   QVariant oldData = data(index.column(), Qt::ForegroundRole);
   QColor oldColor = oldData.value<QColor>();
   if (color != oldColor) {
      setData(index.column(), Qt::ForegroundRole, QVariant(color));
      listView()->viewport()->update();
   }
}

void ListViewItem::setBackgroundColor(QModelIndex index, QColor color)
{
   QVariant oldData = data(index.column(), Qt::BackgroundRole);
   QColor oldColor = oldData.value<QColor>();
   if (color != oldColor) {
      setData(index.column(), Qt::BackgroundRole, QVariant(color));
      listView()->viewport()->update();
   }
}

void ListViewItem::setAlignment(QModelIndex index, Qt::Alignment alignment)
{
   QVariant oldData = data(index.column(), Qt::TextAlignmentRole);
   Qt::Alignment oldAlignment = oldData.toInt();
   if (alignment != oldAlignment) {
      setData(index.column(), Qt::TextAlignmentRole, QVariant(alignment));
      listView()->viewport()->update();
   }
}

QSize ListViewItem::cellSizeHint(const QModelIndex & index)
{
   QSize size;
   if (listView()->hasCustomDelegate()) {
      QAbstractItemDelegate * d = listView()->itemDelegate();
      ListViewItemDelegate * itemDelegate = dynamic_cast<ListViewItemDelegate*>(d);
      if (itemDelegate != NULL) {
         QStyleOptionViewItemV4 option;
         initStyleOption(&option, index);
         size = itemDelegate->sizeHint(option, index);
      }
   }
   return size;
}

void ListViewItem::setColumnAlignments()
{
   ListView * listView = this->listView();
   if (listView == NULL) {
      return;
   }
   int columns = listView->columnCount();
   int column = 0;
   for (column=0; column<columns; column++) {
      Qt::Alignment alignment = (Qt::Alignment)listView->columnAlignment(column);
      setTextAlignment(column, alignment);
   }
}

void ListViewItem::setVisible(bool state)
{
	setHidden(!state);
}


