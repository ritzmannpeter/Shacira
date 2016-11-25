
#include "listviewitemdelegate.h"

ListViewItemDelegate::ListViewItemDelegate(ListView * listView)
   : _listView(listView)
{
}

QString ListViewItemDelegate::displayText(const QVariant & value, const QLocale & locale) const
{
   return QStyledItemDelegate::displayText(value, locale);
}


QWidget * ListViewItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   return QStyledItemDelegate::createEditor(parent, option, index);
}

void ListViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QRect itemRect = option.rect;
   if (itemRect.width() <= 0 || itemRect.height() <= 0) {
      /// sometimes at most width is less than zero
      return;
   }
   ListViewItem * listViewItem = listView()->itemAt(QPoint(itemRect.x() + 1, itemRect.y() + 1));
   if (listViewItem != NULL) {
      listViewItem->paintCell(painter, option, index);
   } else {
      return;
      /// no assertion dont paint it
      /// Q_ASSERT(listViewItem != NULL);
   }
   ///QStyledItemDelegate::paint(painter, option, index);
}

void ListViewItemDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
   QStyledItemDelegate::setEditorData(editor, index);
}

void ListViewItemDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
   QStyledItemDelegate::setModelData(editor, model, index);
}

QSize ListViewItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   return QStyledItemDelegate::sizeHint(option, index);
}

void ListViewItemDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

