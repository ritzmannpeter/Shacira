
#include "listview.h"
#include "listviewitem.h"
#include "listviewitemiterator.h"
#include "listviewitemdelegate.h"
#include "headerview.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qevent.h>
#include <qpainter.h>
#include <qstyleoption.h>
#ifdef QT4
#ifndef QT_PLUGIN
#include "CWidgetBase.h"
#include "FirstHeader.h"
#include "shacira.h"
#endif
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <qscroller.h>
#endif

ListView::ListView(QWidget * parent, const char * name, Qt::WindowFlags flags)
   : QTreeWidget(parent),
     _treeStepSize(0),
     _resizeMode(AllColumns),
     _appearanceStyle(RESIZE_COLUMNS_TO_CONTENTS),
     _shown(false),
     _autoAdjustColumnSizeValue(true), _optimizeAppearanceAfterEventShowValue(true)
{
   if (name != NULL) {
      setObjectName(name);
   }
   setColumnCount(0);
   setHeader(new HeaderView(Qt::Horizontal, parent));
   this->header()->setDefaultSectionSize(152);
   this->header()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
   connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), SLOT(slotCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
   connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)), SLOT(slotItemActivated(QTreeWidgetItem*, int)));
   connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slotItemClicked(QTreeWidgetItem*, int)));
   connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem*)), SLOT(slotItemCollapsed(QTreeWidgetItem*)));
   connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)), SLOT(slotItemExpanded(QTreeWidgetItem*)));
   connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SLOT(slotItemDoubleClicked(QTreeWidgetItem*, int)));
   connect(this, SIGNAL(itemSelectionChanged(void)), SLOT(slotItemSelectionChanged(void)));
   connect(this->header(), SIGNAL(sectionCountChanged(int,int)), SLOT(slotSectionCountChanged(int,int)));
#ifdef USE_DELEGATES
   setItemDelegate(new ListViewItemDelegate(this));
#endif
   _columnWidthTimer = new QTimer(this);
   _columnWidthTimer->setInterval(600);
   connect(_columnWidthTimer, SIGNAL(timeout()), this, SLOT(slotAdjustColumnWidths()));
   _columnWidthTimer->start();

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#ifndef QT_PLUGIN
   if (CWidgetBase::Flag(USE_GESTURE)) {
      setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
      QScroller::grabGesture(this->viewport(), QScroller::TouchGesture);
      connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(expandCollapseItem(const QModelIndex &)));
   }
#endif
#endif
}

ListView::~ListView() 
{
}

bool ListView::hasCustomDelegate() const
{
#ifdef USE_DELEGATES
   return true;
#else
   return false;
#endif
}

HeaderView * ListView::header() const
{
   QHeaderView * header = QTreeWidget::header();
   HeaderView * headerView = dynamic_cast<HeaderView*>(header);
   if (headerView == NULL) {
      Q_ASSERT(headerView != NULL);
   }
   return headerView;
}

void ListView::expandCollapseItem(const QModelIndex & index)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#ifndef QT_PLUGIN
   if (CWidgetBase::Flag(USE_GESTURE)) {
      setExpanded(index, !isExpanded(index));
   }
#endif
#endif
}

ListViewItem * ListView::item(int row) const
{
   QTreeWidgetItem * item = QTreeWidget::topLevelItem(row);
   ListViewItem * listViewItem = dynamic_cast<ListViewItem*>(item);
   if (listViewItem == NULL) {
      Q_ASSERT(listViewItem != NULL);
   }
   return listViewItem;
}

ListViewItem * ListView::currentItem() const
{
   return static_cast<ListViewItem*>(QTreeWidget::currentItem());
}

ListViewItem * ListView::firstChild() const
{
   int itemCount = topLevelItemCount();
   if (itemCount > 0) {
      return static_cast<ListViewItem*>(topLevelItem(0));
   } else {
      return NULL;
   }
}

ListViewItem * ListView::selectedItem() const
{
   return static_cast<ListViewItem*>(currentItem());
}

void ListView::setSelected(ListViewItem * item, bool state)
{
   if (state) {
      setCurrentItem(item);
   }
}

void ListView::sort()
{
   QHeaderView * header = QTreeWidget::header();
   sortItems (sortColumn(), header->sortIndicatorOrder());
}

int ListView::childCount() const
{
   return topLevelItemCount();
}

void ListView::setSelectionAnchor(ListViewItem * item)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void ListView::setContentsPos(int x, int y)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

int ListView::addColumn(const QString & text, int width)
{
   int column = addColumn();
   model()->setHeaderData(column, Qt::Horizontal, QVariant(text), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
   if (width != -1) {
      setColumnWidth(column, width);
   }
   return column;
}

int ListView::addColumn(const QIcon & icon, const QString & text, int width)
{
   int column = addColumn();
   model()->setHeaderData(column, Qt::Horizontal, QVariant(text), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
   model()->setHeaderData(column, Qt::Horizontal, QVariant(icon), Qt::DecorationRole);
   if (width != -1) {
      setColumnWidth(column, width);
   }
   return column;
}

int ListView::addColumn(const QPixmap & pixmap, const QString & text, int width)
{
   int column = addColumn();
   model()->setHeaderData(column, Qt::Horizontal, QVariant(text), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
   model()->setHeaderData(column, Qt::Horizontal, QVariant(pixmap), Qt::DecorationRole);
   if (width != -1) {
      setColumnWidth(column, width);
   }
   return column;
}

int ListView::addColumn(const QImage & image, const QString & text, int width)
{
   int column = addColumn();
   model()->setHeaderData(column, Qt::Horizontal, QVariant(text), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
   model()->setHeaderData(column, Qt::Horizontal, QVariant(image), Qt::DecorationRole);
   if (width != -1) {
      setColumnWidth(column, width);
   }
   return column;
}

int ListView::addColumn(const QPixmap & pixmap, int width)
{
   int column = addColumn();
   header()->setPixmap(column, pixmap);
   if (width != -1) {
      setColumnWidth(column, width);
   }
   return column;
}

int ListView::addColumn(const QImage & image, int width)
{
   return addColumn(QPixmap::fromImage(image), width);
}

int ListView::columns() const
{
   return columnCount();
}

void ListView::setHorizontalHeaderLabel(int column, const QString & label)
{
   model()->setHeaderData(column, Qt::Horizontal, QVariant(label), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
}

void ListView::setHeaderLabel(int column, const QString & text)
{
   model()->setHeaderData(column, Qt::Horizontal, QVariant(text), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
}

void ListView::setHeaderLabel(int column, const QIcon & icon, const QString & text)
{
   model()->setHeaderData(column, Qt::Horizontal, QVariant(text), Qt::DisplayRole);
   model()->setHeaderData(column, Qt::Horizontal, QVariant(header()->font()), Qt::FontRole); 
   model()->setHeaderData(column, Qt::Horizontal, QVariant(icon), Qt::DecorationRole);
}

QString ListView::headerLabel(int column) const
{
   return model()->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
}

ListViewItem * ListView::lastItem() const
{
   int itemCount = topLevelItemCount();
   if (itemCount > 0) {
      QTreeWidgetItem * lastTopLevelItem = topLevelItem(itemCount - 1);
      return static_cast<ListViewItem*>(getLastLevelItem(lastTopLevelItem));
   } else {
      return NULL;
   }
}

QTreeWidgetItem * ListView::getLastLevelItem(QTreeWidgetItem* lastLevelItem) const
{
   int childSize = lastLevelItem->childCount();
   if (childSize > 0) {
       QTreeWidgetItem * childLastItem = lastLevelItem->child(childSize-1);
       if (childLastItem->childCount() > 0) {
          return getLastLevelItem(childLastItem);
       }
       else {
          return childLastItem;
       }
   }
   else {
       return lastLevelItem;
   }
}

void ListView::triggerUpdate()
{
   viewport()->update();
}

QPoint ListView::contentsToViewport(const QPoint & point) const
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return point;
}

ListViewItem * ListView::itemAt(const QPoint & point) const
{
   QTreeWidgetItem * item = QTreeWidget::itemAt(point);
   return static_cast<ListViewItem*>(item);
}

int ListView::treeStepSize() const
{
   return _treeStepSize;
}

void ListView::setTreeStepSize(int stepSize)
{
   _treeStepSize = stepSize;
}

bool ListView::isOpen(ListViewItem * item)
{
   return item->isExpanded();
}

void ListView::setOpen(ListViewItem * item, bool state)
{
   item->setOpen(state);
}

int ListView::itemMargin() const
{
   // this is the default margin for list view items under Qt3
   return 1;
}

QRect ListView::itemRect(ListViewItem * item) const
{
   QRect itemRect;
   QTreeWidgetItem * treeWidgetItem = dynamic_cast<QTreeWidgetItem*>(item);
   if (treeWidgetItem != NULL) {
      itemRect = visualItemRect(treeWidgetItem);
   }
   return itemRect;
}

void ListView::ensureItemVisible(ListViewItem * item)
{
   scrollToItem(item, QAbstractItemView::EnsureVisible);
}

int ListView::visibleWidth() const
{
   return this->width();
}

int ListView::contentsWidth() const
{
   return width();
}

void ListView::setColumnWidthMode(int column, ColumnWidthMode mode)
{
   if (mode == Manual) {
#ifdef QT5
      header()->setSectionResizeMode(column, QHeaderView::Interactive);
#else
      header()->setResizeMode(column, QHeaderView::Interactive);
#endif
   } else if (mode == Maximum) {
#ifdef QT5
      header()->setSectionResizeMode(column, QHeaderView::ResizeToContents);
#else
      header()->setResizeMode(column, QHeaderView::ResizeToContents);
#endif
   } else {
#ifdef QT5
      header()->setSectionResizeMode(column, QHeaderView::ResizeToContents);
#else
      header()->setResizeMode(column, QHeaderView::ResizeToContents);
#endif
   }
#ifdef doku
QHeaderView::Stretch	1	QHeaderView will automatically resize the section to fill the available space. The size cannot be changed by the user or programmatically.
QHeaderView::ResizeToContents	3	QHeaderView will automatically resize the section to its optimal size based on the contents of the entire column or row. The size cannot be changed by the user or programmatically. (This value was introduced in 4.2)
#endif
   _columnWidthMode[column] = mode;
}

bool ListView::isSelected(ListViewItem * item) const
{
   if (item == currentItem()) {
      return true;
   } else {
      return false;
   }
}

void ListView::setResizeMode(ResizeMode mode)
{
   _resizeMode = mode;
}

ListView::ResizeMode ListView::resizeMode() const
{
   return _resizeMode;
}

void ListView::setItemHeight(int height)
{
}

// QT3 compatibility methods
void ListView::setColumnText(int column, const QString & label)
{
   ListView::setHeaderLabel(column, label);
}

void ListView::setColumnText(int column, const QIcon & icon, const QString & label)
{
   ListView::setHeaderLabel(column, icon, label);
}

QString ListView::columnText(int column) const
{
   return headerLabel(column);
}

void ListView::setColumnWidth(int column, int width)
{
   if (width == 0) {
      header()->hideSection(column);
   } else {
      header()->showSection(column);
      QTreeWidget::setColumnWidth(column, width);
      _columnWidth[column] = width;
   }
}

int ListView::columnWidth(int column) const
{
   return QTreeWidget::columnWidth(column);
}

void ListView::setColumnAlignment(int column, int align)
{
   _columnAlignment[column] = (Qt::Alignment)align;
}

int ListView::columnAlignment(int column) const
{
   // returns the alignment set for aspecific column
   QMap<int,Qt::Alignment>::const_iterator i = _columnAlignment.find(column);
   if (i == _columnAlignment.constEnd()) {
      return Qt::AlignLeft | Qt::AlignVCenter;
   } else {
      return i.value();
   }
}

void ListView::setSorting(int column, bool ascending)
{
   Qt::SortOrder sortOrder;
   if (ascending) {
      sortOrder = Qt::AscendingOrder;
   } else {
      sortOrder = Qt::DescendingOrder;
   }
   sortItems(column, sortOrder);
}

void ListView::adjustColumn(int column, int width)
{
   int columns = columnCount();
   if (columns == 1) {
      // only one column: fit to available space
      header()->setStretchLastSection(true);
   } else {
      unsigned int style = appearanceStyle();
      if (style & STRETCH_LAST_SECTION) {
          header()->setStretchLastSection(true);
      } else {
         // if last section not stretched
         header()->setStretchLastSection(false);
         if (style & RESIZE_COLUMNS_TO_CONTENTS) {
            if (width != -1) {
               setColumnWidth(column, width);
            } else {
#ifdef QT5
               if (header()->sectionResizeMode(column) != QHeaderView::Fixed) {
#else
               if (header()->resizeMode(column) != QHeaderView::Fixed) {
#endif
                  resizeColumnToContents(column);
               }
            }
         }
      }
   }
}

unsigned int ListView::appearanceStyle() const
{
   return _appearanceStyle;
}

void ListView::setAppearanceStyle(unsigned int style)
{
   _appearanceStyle = style;
}

void ListView::optimizeAppearance(unsigned int style)
{
   int columns = columnCount();
   if (columns == 1) {
      // only one column: fit to available space
#ifdef QT5
      if (header()->sectionResizeMode(0) == QHeaderView::Fixed) {
#else
      if (header()->resizeMode(0) == QHeaderView::Fixed) {
#endif
         return;
      }
      header()->setStretchLastSection(true);
   } else {
      int column = 0;
      for (column=0; column<columns;column++) {
         if (column == columns - 1) {
            if (style & STRETCH_LAST_SECTION) {
               header()->setStretchLastSection(true);
            } else {
               // if last section not stretched
               header()->setStretchLastSection(false);
               if (style & RESIZE_COLUMNS_TO_CONTENTS) {
                  adjustColumn(column);
                  QMap<int,int>::const_iterator i = _columnWidth.find(column);
                  if (i != _columnWidth.constEnd()) {
                     QTreeWidget::setColumnWidth(column, i.value());
                  }
               }
            }
         } else {
            adjustColumn(column);
            QMap<int,int>::const_iterator i = _columnWidth.find(column);
            if (i != _columnWidth.constEnd()) {
               QTreeWidget::setColumnWidth(column, i.value());
            }
         }
      }
   }
}

// reimplemented virtual protected methods

bool ListView::viewportEvent(QEvent *event)
{
#ifndef QT_PLUGIN
   if (CWidgetBase::Flag(CURSOR_DISABLED)) {
      switch (event->type()) {
      case QEvent::HoverEnter:
      case QEvent::HoverLeave:
      case QEvent::HoverMove:
         return true;
      }
   }
#endif
   return QTreeWidget::viewportEvent(event);
}

bool ListView::event(QEvent * event)
{
   switch (event->type()) {
   case QEvent::Show:
      if (_optimizeAppearanceAfterEventShowValue) {
         optimizeAppearance(_appearanceStyle);
      }
      _shown = true;
      break;
   case QEvent::Hide:
      _shown = false;
      break;
   }

   return QTreeWidget::event(event);
}

void ListView::mousePressEvent(QMouseEvent * mouseEvent)
{
   if (mouseEvent->button() == Qt::RightButton) {
      ListViewItem * item = reinterpret_cast<ListViewItem*>(currentItem());
      emit(contextMenuRequested(item, QCursor::pos()));
   }
   contentsMousePressEvent(mouseEvent);
   QTreeWidget::mousePressEvent(mouseEvent);
}

void ListView::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
   ListViewItem * item = reinterpret_cast<ListViewItem*>(currentItem());
   if (mouseEvent->button() == Qt::RightButton) {
      // optimization test case (activated through right mouse button click in the list view viewport)
      optimizeAppearance(_appearanceStyle);
      emit(rightButtonClicked(item, QCursor::pos()));
   }
   emit(clicked(item));
   QTreeWidget::mouseReleaseEvent(mouseEvent);
}

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
void ListView::mouseMoveEvent(QMouseEvent * mouseEvent)
{
#ifndef QT_PLUGIN
   if (CWidgetBase::Flag(USE_GESTURE)) {
      // ignoring these events keeps the items from being selected while touch scrolling or dragging
      mouseEvent->ignore();
   }
   else {
      QTreeWidget::mouseMoveEvent(mouseEvent);
   }
#endif
}
#endif

void ListView::contentsMousePressEvent(QMouseEvent * mouseEvent)
{
   QTreeWidget::mousePressEvent(mouseEvent);
}

void ListView::contentsMouseReleaseEvent(QMouseEvent * mouseEvent)
{
   QTreeWidget::mouseReleaseEvent(mouseEvent);
}

void ListView::drawBranches(QPainter * painter, const QRect & rect, const QModelIndex & index) const
{
   QTreeView::drawBranches(painter, rect, index);
}

void ListView::drawRow(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
   QTreeWidget::drawRow(painter, option, index);
#ifndef USE_DELEGATES
   int row = index.row();
   for (int column = 0; column < columnCount(); column++) {
      QModelIndex itemIndex = index.sibling(row, column);
      if (itemIndex.isValid()) {
         QRect itemRect = visualRect(itemIndex);
         QStyleOptionViewItemV4 newOption = qstyleoption_cast<QStyleOptionViewItemV4>(option);
         newOption.rect = itemRect;
         ListViewItem * listViewItem = this->item(itemIndex.row());
         if (listViewItem != NULL) {
            listViewItem->paintCell(painter, newOption, itemIndex);
            drawChildren(listViewItem, painter, newOption);
         }
      }
   }
#endif
}

void ListView::drawChildren(ListViewItem * listViewItem, QPainter * painter, const QStyleOptionViewItem & option) const
{
#ifndef USE_DELEGATES
   int childCount = listViewItem->childCount();
   int i = 0;
   for (i=0; i<childCount; i++) {
      QTreeWidgetItem * item = listViewItem->child(i);
      ListViewItem * listViewItem = NULL;
      if (item != NULL) {
         QRect itemRect = visualItemRect(item);
         if (!itemRect.isNull()) {
            listViewItem = dynamic_cast<ListViewItem*>(item);
            if (listViewItem != NULL) {
               drawChildren(listViewItem, painter, option);
               int columnCount = this->columnCount();
               int column = 0;
               for (column=0; column<columnCount; column++) {
                  QModelIndex index = indexAt(QPoint(itemRect.x(), itemRect.y()));
                  QModelIndex itemIndex = index.sibling(index.row(), column);
                  itemRect = visualRect(itemIndex);
                  QStyleOptionViewItemV4 newOption = qstyleoption_cast<QStyleOptionViewItemV4>(option);
                  newOption.rect = itemRect;
                  listViewItem->paintCell(painter, newOption, itemIndex);
               }
            } else {
              int dummy = 0;
            }
         } else {
            int dummy = 0;
         }
      } else {
         int dummy = 0;
      }
   }
#endif
}

void ListView::dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
   QTreeView::dataChanged(topLeft, bottomRight);
}

int ListView::sizeHintForColumn(int column) const
{
   return QTreeView::sizeHintForColumn(column);
}

void ListView::slotCurrentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
   emit(selectionChanged(reinterpret_cast<ListViewItem*>(current)));
}

void ListView::slotItemActivated(QTreeWidgetItem * item, int column)
{
   emit(selectionChanged(reinterpret_cast<ListViewItem*>(item)));
}

void ListView::slotItemClicked(QTreeWidgetItem * item, int column)
{
   emit(clicked(reinterpret_cast<ListViewItem*>(item)));
}

void ListView::slotItemDoubleClicked(QTreeWidgetItem * item, int column)
{
   emit(doubleClicked(reinterpret_cast<ListViewItem*>(item)));
   emit(doubleClicked(reinterpret_cast<ListViewItem*>(item), QCursor::pos()));
}

void ListView::slotItemCollapsed(QTreeWidgetItem * item)
{
   optimizeAppearance(_appearanceStyle);
   emit(collapsed(reinterpret_cast<ListViewItem*>(item)));
}

void ListView::slotItemExpanded(QTreeWidgetItem * item)
{
   optimizeAppearance(_appearanceStyle);
   emit(expanded(reinterpret_cast<ListViewItem*>(item)));
}

void ListView::slotItemSelectionChanged()
{
   emit(selectionChanged());
}

void ListView::slotSectionCountChanged(int oldCount, int newCount)
{
   if (oldCount != newCount) {
      optimizeAppearance(_appearanceStyle);
   }
}

// private members

int ListView::addColumn()
{
   int column = columnCount();
   setColumnCount(column + 1);
   optimizeAppearance(_appearanceStyle);
   return column;
}

ListView::ColumnWidthMode ListView::columnWidthMode(int column) const
{
   // returns the set column width mode (Qt3) of a column
   QMap<int,ColumnWidthMode>::const_iterator i = _columnWidthMode.find(column);
   if (i == _columnWidthMode.constEnd()) {
      return Manual;
   } else {
      return i.value();
   }
}

void ListView::slotAdjustColumnWidths()
{
   if (!_autoAdjustColumnSizeValue || !_shown || (columnCount() < 2)) {
      return;
   }

   adjustColumnWidths();
}

int ListView::maxColumnWidth(QTreeWidgetItem * item, int column, int itemIndentation, int &recursivLevel)
{
   int max = 0;
   QModelIndex	index = this->indexFromItem(item, column);
#define USE_STYLE_DELEGATE_
#ifdef USE_STYLE_DELEGATE
   QSize cellSize = itemChild->cellSizeHint(index);
   columnWidth = cellSize.width();
#else
   QString text = this->model()->data(index).toString();
   QPixmap pixmap = this->model()->data(index, Qt::DecorationRole).value<QPixmap>();
   int pixmapWidth = pixmap.width();
   QFontMetrics fontMetrics(this->font());
   int spacingWidth = pixmapWidth ? 10 : 0;
   int columnWidthOffset = (column == 0) ? recursivLevel * itemIndentation : 0;
   max = fontMetrics.width(text) + 6 + pixmapWidth + spacingWidth + columnWidthOffset;
#endif
   // recurse to leaf
   int itemChildCount = item->childCount();
   if (itemChildCount > 0) {
      int itemIndentationLocal = item->isExpanded() ? indentation() : 0;
      recursivLevel++;
      for(int i=0; i<itemChildCount; i++) {
         QTreeWidgetItem * child = item->child(i);
         int width = maxColumnWidth(child, column, itemIndentationLocal, recursivLevel);
         if (width > max) {
            max = width;
         }
      }
   }
   return max;
}

void ListView::adjustColumnWidths()
{
   QVector<int> columnWidths;
   int columns = this->columns();
   columnWidths.resize(columns);
   int column = 0;
   for (column=0; column<columns; column++) {
      columnWidths[column] = this->columnWidth(column);
   }
   int rows = this->childCount();
   int row = 0;
   for (row=0; row<rows; row++) {
      ListViewItem * item = this->item(row);
      int itemIndentation = item->isExpanded() ? indentation() : 0;
      for (column=0; column<columns;column++) {
         int recursivLevel = 1;
         int columnWidth = maxColumnWidth(item, column, itemIndentation, recursivLevel);
         if (columnWidth > columnWidths[column]) {
            columnWidths[column] = columnWidth;
         }
      }
   }
   for (column=0; column<columns;column++) {
      if (columnWidths[column] > this->columnWidth(column)) {
         this->adjustColumn(column, columnWidths[column]);
      }
   }
}

#ifdef old_version

void ListView::adjustColumnWidths()
{
   QVector<int> columnWidths;
   int columns = this->columns();
   columnWidths.resize(columns);
   int column = 0;
   for (column=0; column<columns; column++) {
      columnWidths[column] = this->columnWidth(column);
   }

   QRect viewportRect = viewport()->rect();
   int rows = this->childCount();
   int row = 0;
   for (row=0; row<rows; row++) {
      ListViewItem * item = this->item(row);
      if (item != NULL) {
         QRect itemRect = visualItemRect(item);
         if (viewportRect.contains(itemRect)) {
            for (column=0; column<columns; column++) {
               QModelIndex	index = this->indexFromItem(item, column);
               int columnWidth = 0;
#define USE_STYLE_DELEGATE_
#ifdef USE_STYLE_DELEGATE
               QSize cellSize = item->cellSizeHint(index);
               columnWidth = cellSize.width();
#else
               QString text = this->model()->data(index).toString();
               QPixmap pixmap = this->model()->data(index, Qt::DecorationRole).value<QPixmap>();
               int pixmapWidth = pixmap.width();
               QFontMetrics fontMetrics(this->font());
               int spacingWidth = pixmapWidth ? 10 : 0;            
               columnWidth = fontMetrics.width(text) + 6 + pixmapWidth + spacingWidth;
#endif
               if (columnWidth > columnWidths[column]) {
                  columnWidths[column] = columnWidth;
               }
            }
         }
      }
   }

   for (column=0; column<columns;column++) {
      if (columnWidths[column] > this->columnWidth(column)) {
         this->adjustColumn(column, columnWidths[column]);
      }
   }
}

#endif