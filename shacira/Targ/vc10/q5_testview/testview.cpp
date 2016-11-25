
#include "testview.h"

TestViewItem::TestViewItem(TestView * testView, int i, int j, int k)
   : ListViewItem(reinterpret_cast<ListView*>(testView)), _i(i), _j(j), _k(k)
{
   setText();
}

TestViewItem::TestViewItem(TestViewItem * testViewItem, int i, int j, int k)
   : ListViewItem(reinterpret_cast<ListViewItem*>(testViewItem)), _i(i), _j(j), _k(k)
{
   setText();
}

TestViewItem::~TestViewItem()
{
}

void TestViewItem::setText()
{
   _text = "item";
   if (_i != -1) {
      _text += " ";
      _text += QString::number(_i);
   }
   if (_j != -1) {
      _text += " ";
      _text += QString::number(_j);
   }
   if (_k != -1) {
      _text += " ";
      _text += QString::number(_k);
   }
   int column = 0;
   for (column=0; column<columnCount(); column++) {
      ListViewItem::setText(column, _text);
   }
}

#include <qapplication.h>
void TestViewItem::paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
{
   if (listView()->hasCustomDelegate()) {
      int column = index.column();
      if (column == (listView()->columnCount() - 1)) {
         painter->save();
         painter->setPen(Qt::green);
         painter->setBrush(QBrush(Qt::blue));
         painter->drawRect(option.rect);
         int i = 0;
         for (i=0; i<5; i++) {
            int size = option.rect.width() / 5;
            int x = option.rect.x() + (((i+1) * size));
            int y0 = option.rect.top();
            int y1 = option.rect.bottom();
            if (i < 4) {
               painter->drawLine(x, y0, x, y1);
            }
         }
         painter->restore();
      } else {
         if (isColored(column)) {
            painter->save();
            painter->setPen(Qt::red);
            painter->drawText(option.rect, text(column));
            painter->restore();
            return;
            QStyleOptionViewItemV4 newOption(option);
            initStyleOption(&newOption, index);
//            newOption.backgroundBrush = Qt::red;
//            newOption.palette.setColor(QPalette::Text, Qt::white);
            newOption.palette.setColor(QPalette::Text, getColor(column));
///            painter->save();
//            const QStyle * style = newOption.widget ? newOption.widget->style() : QApplication::style();
//            const QWidget * widget = newOption.widget;
///            painter->save();
///            style->drawPrimitive(QStyle::PE_PanelItemViewItem, &newOption, painter, widget);
///            painter->restore();
//            style->drawControl(QStyle::CE_ItemViewItem, &newOption, painter, widget);
///            painter->restore();
//            setAlignment(index, Qt::AlignRight);
            ListViewItem::paintCell(painter, newOption, index);
         } else {
//            setAlignment(index, Qt::AlignLeft);
            ListViewItem::paintCell(painter, option, index);
         }
      }
   } else {
      int column = index.column();
      if (column == (listView()->columnCount() - 1)) {
         painter->save();
         painter->setPen(Qt::green);
         painter->setBrush(QBrush(Qt::blue));
         painter->drawRect(option.rect);
         int i = 0;
         for (i=0; i<5; i++) {
            int size = option.rect.width() / 5;
            int x = option.rect.x() + (((i+1) * size));
            int y0 = option.rect.top();
            int y1 = option.rect.bottom();
            if (i < 4) {
               painter->drawLine(x, y0, x, y1);
            }
         }
         painter->restore();
      } else {
         if (isColored(column)) {
      //      setForegroundColor(index, Qt::red);
            setBackgroundColor(index, Qt::red);
            setAlignment(index, Qt::AlignRight);
         } else {
      //      setForegroundColor(index, listView()->palette().color(QPalette::WindowText));
            setBackgroundColor(index, listView()->palette().color(QPalette::Window));
            setAlignment(index, Qt::AlignLeft);
         }
      }
      ListViewItem::paintCell(painter, option, index);
   }
}

TestView::TestView(QWidget *parent)
    : ListView(parent)
{
}
 
TestView::~TestView()
{  
}

#include "wizard.h"
#include "ui_testwizard.h"

void TestView::refresh()
{
   Wizard<Ui_TestWizard> wizard(this, "heinz", true, 0);
   wizard.exec();
#ifdef lassma
   int width = viewport()->width();
   int height = viewport()->height();
   repaint(0, 0, width, height);
#ifdef lassma
   QPainter painter;
   QRect rect = viewport()->geometry();
   QRegion region(rect);
   drawTree(&painter, region);
#endif
#endif
}

void TestView::slotItemClicked(QTreeWidgetItem * item, int column)
{
return;
   TestViewItem * testViewItem = dynamic_cast<TestViewItem*>(item);
   if (testViewItem->isColored(column)) {
      testViewItem->clearColor(column);
   } else {
      testViewItem->setColor(column, Qt::blue);
   }
}
