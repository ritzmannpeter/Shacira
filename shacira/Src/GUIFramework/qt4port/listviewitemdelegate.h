
#ifndef _listviewitemdelegate_h_
#define _listviewitemdelegate_h_

#include <qwidget.h>
#include <qstring.h>
#include <qtreewidget.h>
#include <qstyleditemdelegate.h>

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

#include "listview.h"

class _CWIDGET_EXPORT_ ListViewItemDelegate : public QStyledItemDelegate
{
public:
   friend class ListViewItem;
public:
   ListViewItemDelegate(ListView * listView);
   virtual QString displayText(const QVariant & value, const QLocale & locale) const;
   virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
   virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
   virtual void setEditorData(QWidget * editor, const QModelIndex & index) const;
   virtual void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
   virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
   virtual void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;
   inline ListView * listView() const {return _listView;};
protected:
   ListView * _listView;
};

#endif // _listviewitemdelegate_h_


