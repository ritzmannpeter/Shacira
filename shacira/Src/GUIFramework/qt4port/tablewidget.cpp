
#include "tablewidget.h"
#include "tablewidgetitem.h"
#include "headerview.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qevent.h>
#include <qpainter.h>
#include <qstyleoption.h>

TableWidget::TableWidget(QWidget * parent, const char * name, Qt::WindowFlags flags)
   : QTableWidget(parent), _horizontalHeader(NULL), _verticalHeader(NULL), _readOnly(false)
{
   if (name != NULL) {
      setObjectName(name);
   }
   _horizontalHeader = new HeaderView(Qt::Horizontal);
   setHorizontalHeader(_horizontalHeader);
   _verticalHeader = new HeaderView(Qt::Vertical);
   setVerticalHeader(_verticalHeader);
   setRowCount(0);
   setColumnCount(0);
   connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(slotCellClicked(int,int)));
   connect(this, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(slotCellDoubleClicked(int,int)));
   connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(slotItemSelectionChanged()));
   connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotCellChanged(int,int)));
   setAlternatingRowColors(true);
}

TableWidget::~TableWidget() 
{
}

int TableWidget::numRows() const
{
   return rowCount();
}

void TableWidget::setNumRows(int value)
{
   setRowCount(value);
}

int TableWidget::numCols() const
{
   return columnCount();
}

void TableWidget::setNumCols(int value)
{
   setColumnCount(value);
}

HeaderView * TableWidget::horizontalHeader() const
{
   return _horizontalHeader;
}

HeaderView * TableWidget::verticalHeader() const
{
   return _verticalHeader;
}

void TableWidget::updateCell(int row, int column)
{
   TableWidgetItem * item = this->item(row, column);
   if (item != NULL) {
//      item->update();
   }
}

QString TableWidget::text(int row, int column)
{
   QString text = "?";
   TableWidgetItem * item = this->item(row, column);
   if (item != NULL) {
      text = item->text();
   }
   return text;
}

void TableWidget::setText(int row, int column, const QString & text)
{
   TableWidgetItem * item = this->item(row, column);
   if (item != NULL) {
      item->setText(text);
   }
}

void TableWidget::setColumnLabels(const QStringList & labels)
{
   setHorizontalHeaderLabels(labels);
}

void TableWidget::setHorizontalHeaderLabel(int column, const QString & label)
{
   QTableWidgetItem * headerItem = this->horizontalHeaderItem(column);
   if (headerItem == NULL) {
      headerItem = new QTableWidgetItem(label);
      this->setHorizontalHeaderItem(column, headerItem);
   } else {
      headerItem->setText(label);
   }
}

void TableWidget::setVerticalHeaderLabel(int row, const QString & label)
{
   QTableWidgetItem * headerItem = this->verticalHeaderItem(row);
   if (headerItem == NULL) {
      headerItem = new QTableWidgetItem(label);
      this->setVerticalHeaderItem(row, headerItem);
   } else {
      headerItem->setText(label);
   }
}

void TableWidget::clearCellWidget(int row, int column)
{
   removeCellWidget(row, column);
}

void TableWidget::setColumnMovingEnabled(bool value)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void TableWidget::setRowMovingEnabled(bool value)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void TableWidget::setSorting(bool value)
{
   setSortingEnabled(value);
}

void TableWidget::insertRows(int row, int count)
{
   int i = 0;
   for (i=0; i<count; i++) {
      insertRow(row + i);
   }
}

void TableWidget::setColumnReadOnly(int column, bool value)
{
   if (_columnReadOnly.size() <= column) {
      _columnReadOnly.resize(column + 1);
   }
   _columnReadOnly[column] = value;
}

void TableWidget::setRowReadOnly(int row, bool value)
{
   if (_rowReadOnly.size() <= row) {
      _rowReadOnly.resize(row + 1);
   }
   _rowReadOnly[row] = value;
}

void TableWidget::swapRows(int row1, int row2, bool swapHeader)
{
   int columnCount = this->columnCount();
   int column = 0;
   for (column= 0; column<columnCount; column++) {
      TableWidgetItem * item1 = dynamic_cast<TableWidgetItem*>(takeItem(row1, column));
      TableWidgetItem * item2 = dynamic_cast<TableWidgetItem*>(takeItem(row2, column));
      this->setItem(row1, column, item2);
      this->setItem(row2, column, item1);
   }
}

bool TableWidget::isRowReadOnly(int row) const
{
   if (_rowReadOnly.size() <= row) {
      return false;
   } else {
      return _rowReadOnly[row];
   }
}

bool TableWidget::isColumnReadOnly(int column) const
{
   if (_columnReadOnly.size() <= column) {
      return false;
   } else {
      return _columnReadOnly[column];
   }
}

void TableWidget::setRowLabels(const QStringList & labels)
{
   setVerticalHeaderLabels(labels);
}

void TableWidget::updateContents()
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void TableWidget::setColumnStretchable(int column, bool state)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void TableWidget::adjustColumn(int column)
{
   resizeColumnToContents(column);
}

void TableWidget::setItem(int row, int column, TableWidgetItem * item)
{
   int flags = item->flags();
   if (_readOnly || isColumnReadOnly(column)) {
      flags &= (~Qt::ItemIsEnabled);
   } else {
      flags |= (Qt::ItemIsEnabled);
   }
   item->setFlags((Qt::ItemFlags)flags);
   QTableWidget::setItem(row, column, item);
}

TableWidgetItem * TableWidget::item(int row, int column)
{
   QTableWidgetItem * item = QTableWidget::item(row, column);
   TableWidgetItem * tableWidgetItem = dynamic_cast<TableWidgetItem*>(item);
   if (tableWidgetItem == NULL) {
      tableWidgetItem = new TableWidgetItem();
      // edit operations may create an iten of type
      // QTableWidgetItem. as a consequence tableWidgetItem is NULL
      // in this case
	  if (item != NULL)	{
		   tableWidgetItem->setText(item->text());
      }
      setItem(row, column, tableWidgetItem);
      item = QTableWidget::item(row, column);
   }
   return tableWidgetItem;
}

void TableWidget::activateNextCell()
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void TableWidget::endEdit(int row, int column, bool accept, bool replace)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

int TableWidget::currEditRow() const
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return 0;
}

int TableWidget::currEditCol() const
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return 0;
}

// Qt 3 compatibility signals

void TableWidget::slotCellClicked(int row, int column)
{
   QPoint pos;
   int button = Qt::LeftButton;
   emit clicked(row, column, button, pos);
}

void TableWidget::slotCellDoubleClicked(int row, int column)
{
   QPoint pos;
   int button = Qt::LeftButton;
   emit doubleClicked(row, column, button, pos);
}

void TableWidget::slotItemSelectionChanged()
{
   emit selectionChanged();
}

void TableWidget::slotCellChanged(int row, int column)
{
   emit valueChanged(row, column);
}

void TableWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
   QTableWidget::mouseDoubleClickEvent(e);
}

void TableWidget::mousePressEvent(QMouseEvent * e)
{
   Qt::MouseButton button = e->button();
   if (button == Qt::RightButton) {
      int row = 0;
      int column = 0;
      QPoint pos = e->pos();
      QTableWidgetItem * item = itemAt(pos);
      if (item != NULL) {
         row = item->row();
         column = item->column();
         setCurrentItem(item);
         pos = mapToGlobal(pos);
         emit contextMenuRequested(row, column, pos);
      }
      e->accept();
   } else {
      QTableWidget::mousePressEvent(e);
   }
}

void TableWidget::mouseReleaseEvent(QMouseEvent * e)
{
   QTableWidget::mouseReleaseEvent(e);
}


