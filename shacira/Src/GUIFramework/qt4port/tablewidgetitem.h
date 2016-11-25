
#ifndef _tablewidgetitem_h_
#define _tablewidgetitem_h_

#include <qwidget.h>
#include <qstring.h>
#include <qtablewidget.h>
#include <qfontmetrics.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include "tablewidget.h"
#include "tablewidgetitem.h"

class TableWidget;

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

#ifdef doku
Q3TableItem::WhenCurrent	2	The cell looks editable only when it has keyboard focus (see Q3Table::setCurrentCell()).
Q3TableItem::OnTyping	1	The cell looks editable only when the user types in it or double-clicks it. It resembles the WhenCurrent
#endif

class _CWIDGET_EXPORT_ TableWidgetItem : public QTableWidgetItem
{
public:
   enum EditType {WhenCurrent, OnTyping};
 public:
   friend class TableWidget; 
public:
   TableWidgetItem(int type = Type);
	TableWidgetItem(TableWidget * table, EditType et, const QString & text = QString());
	TableWidgetItem(TableWidget * table, EditType et, const QString & text, const QPixmap & pixmap);
	TableWidgetItem(TableWidget * table, const QString & text);
   virtual ~TableWidgetItem();
   TableWidget * table() const;
   void setReplaceable(bool value);
   int row() const;
   int col() const;
   virtual int rtti() const;
   virtual void setContentFromEditor(QWidget * w);
   virtual void setChecked(bool value);
protected:
   int type(EditType et) const;
};

template <class TClass> class TypedTableItem : public TableWidgetItem
{
public:
   TypedTableItem(int type = Type)
      : TableWidgetItem(type)
   {
   };
	TypedTableItem(TableWidget * table, EditType et, const QString & text = QStri)
      : TableWidgetItem(table, et, text)
   {
   };
	TypedTableItem(TableWidget * table, EditType et, const QString & text, const QPixmap & pixmap)
      : TableWidgetItem(table, et, text, pixmap)
   {
   };
	TypedTableItem(TableWidget * table, const QString & text)
      : TableWidgetItem(table, text)
   {
   };
   virtual ~TypedTableItem()
   {
   };
};

typedef TypedTableItem<QCheckBox> CheckTableItem;
typedef TypedTableItem<QComboBox> ComboTableItem;

#endif // _tablewidgetitem_h_


