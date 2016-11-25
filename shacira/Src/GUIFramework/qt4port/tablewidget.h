
#ifndef _tablewidget_h_
#define _tablewidget_h_

#define USE_DELEGATES

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qtablewidget.h>
#include "headerview.h"

class TableWidget;
class TableWidgetItem;

#ifdef QT4
#include "qt4port.h"
#include "pluginfactory.h"
#else
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : warning: "
#define NOT_PORTED(msg)
#define _CWIDGET_EXPORT_
#endif

class TableWidget;

class _CWIDGET_EXPORT_ TableWidget : public QTableWidget
{
   Q_OBJECT

public:
   TableWidget(QWidget * parent = NULL, const char * name = NULL, Qt::WindowFlags flags = 0);
   virtual ~TableWidget();
   int numRows() const;
   void setNumRows(int value);
   int numCols() const;
   void setNumCols(int value);
   HeaderView * horizontalHeader() const;
   HeaderView * verticalHeader() const;
   void updateCell(int row, int column);
   QString text(int row, int column);
   void setText(int row, int column, const QString & text);
   void setColumnLabels(const QStringList & labels);
   void setHorizontalHeaderLabel(int column, const QString & label);
   void setVerticalHeaderLabel(int row, const QString & label);
   virtual void clearCellWidget(int row, int column);
   virtual void setColumnMovingEnabled(bool value);
   virtual void setRowMovingEnabled(bool value);
   virtual void setSorting(bool value);
   virtual void insertRows(int row, int count = 1);
   virtual void setColumnReadOnly(int column, bool value);
   virtual void setRowReadOnly(int row, bool value);
   virtual void swapRows(int row1, int row2, bool swapHeader = false);
   bool isRowReadOnly(int row) const;
   bool isColumnReadOnly(int column) const;
   void setRowLabels(const QStringList & labels);
   void updateContents();
   void setColumnStretchable(int column, bool state);
   void adjustColumn(int column);
   void setItem(int row, int column, TableWidgetItem * item);
   TableWidgetItem * item(int row, int column);

   virtual void mouseMoveEvent(QMouseEvent * e)
   {
      QTableWidget::mouseMoveEvent(e);
   };
   virtual void moveEvent(QMoveEvent * e)
   {
      QTableWidget::moveEvent(e);
   };
   virtual void paintEvent(QPaintEvent * e)
   {
      QTableWidget::paintEvent(e);
   };
//   virtual bool qwsEvent(QWSEvent * e)
//   {
//      QTableWidget::qwsEvent(e);
//   };
   virtual void resizeEvent(QResizeEvent * e)
   {
      QTableWidget::resizeEvent(e);
   };
   virtual void showEvent(QShowEvent * e)
   {
      QTableWidget::showEvent(e);
   };
   virtual void tabletEvent(QTabletEvent * e)
   {
      QTableWidget::tabletEvent(e);
   };
   virtual void wheelEvent(QWheelEvent * e)
   {
      QTableWidget::wheelEvent(e);
   };
protected:
   virtual void activateNextCell();
   virtual void endEdit(int row, int column, bool accept, bool replace);
   int currEditRow() const;
   int currEditCol() const;
private:
   HeaderView * _horizontalHeader;
   HeaderView * _verticalHeader;
   // Qt 3 compatibility signals
signals:
   void clicked(int row, int col, int button, const QPoint & mousePos);
   void doubleClicked(int row, int col, int button, const QPoint & mousePos);
   void selectionChanged();
   void valueChanged(int row, int col);
   void contextMenuRequested(int row, int col, const QPoint & pos);
   void currentChanged(int row, int col);
protected slots:
   void slotCellClicked(int row, int column);
   void slotCellDoubleClicked(int row, int column);
   void slotItemSelectionChanged();
   void slotCellChanged(int row, int column);
protected:
   virtual void mouseDoubleClickEvent(QMouseEvent * e);
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
protected:
   bool _readOnly;
   inline void setReadOnly(bool value) {_readOnly = value;};
   inline bool readOnly() const {return _readOnly;};
   std::vector<bool> _columnReadOnly;
   std::vector<bool> _rowReadOnly;
};

#endif // _tablewidget_h_


