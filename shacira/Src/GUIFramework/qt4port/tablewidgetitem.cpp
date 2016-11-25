
#include "tablewidgetitem.h"
#include <qpainter.h>

TableWidgetItem::TableWidgetItem(int type)
   : QTableWidgetItem(type)
{
}

TableWidgetItem::TableWidgetItem(TableWidget * table, EditType et, const QString & text )
   : QTableWidgetItem(type(et))
{
   setText(text);
}

TableWidgetItem::TableWidgetItem(TableWidget * table, EditType et, const QString & text, const QPixmap &p)
   : QTableWidgetItem(type(et))
{
   setText(text);
}

TableWidgetItem::TableWidgetItem(TableWidget * table, const QString & text)
{
   setText(text);
}

TableWidgetItem::~TableWidgetItem()
{
}

TableWidget * TableWidgetItem::table() const
{
   QTableWidget * tableWidget = this->tableWidget();
   TableWidget * table = dynamic_cast<TableWidget*>(tableWidget);
   return table;
}

void TableWidgetItem::setReplaceable(bool value)
{
}

int TableWidgetItem::row() const
{
   return QTableWidgetItem::row();
}

int TableWidgetItem::col() const
{
   return QTableWidgetItem::column();
}

int TableWidgetItem::rtti() const
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return 0;
}

void TableWidgetItem::setContentFromEditor(QWidget * w)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void TableWidgetItem::setChecked(bool value)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

int TableWidgetItem::type(EditType et) const
{
   return (int)et;
}
