
#ifndef _listviewitem_h_
#define _listviewitem_h_

#include <qwidget.h>
#include <qstring.h>
#include <qtreewidget.h>
#include <qfontmetrics.h>
#include "listview.h"
#include "listviewitem.h"
#include "listviewitemiterator.h"

class ListView;

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

class _CWIDGET_EXPORT_ ListViewItem : public QTreeWidgetItem
{
public:
   friend class ListView; 
   friend class ListViewItemDelegate; 
public:
   ListViewItem(ListView * listView, const QString & label1 = QString(), const QString & label2 = QString(), const QString & label3 = QString(), const QString & label4 = QString(), const QString & label5 = QString(), const QString & label6 = QString(), const QString & label7 = QString(), const QString & label8 = QString());
   ListViewItem(ListView * listView, ListViewItem * after);
   ListViewItem(ListViewItem * listViewItem, const QString & label1 = QString(), const QString & label2 = QString(), const QString & label3 = QString(), const QString & label4 = QString(), const QString & label5 = QString(), const QString & label6 = QString(), const QString & label7 = QString(), const QString & label8 = QString());
   ListViewItem(ListViewItem * listViewItem, ListViewItem * after);
   virtual ~ListViewItem();
   ListViewItem * parent() const;
   ListViewItem * firstChild() const;
   ListViewItem * nextSibling() const;
   virtual bool operator<(const QTreeWidgetItem & other) const
   {
      const ListViewItem * rightItem = static_cast<const ListViewItem*>(&other);
      int column = listView()->sortColumn();
      int rc = compare((ListViewItem*)rightItem, column, true);
      if (rc == -1) {
         return true;
      } else {
         return false;
      }
   };
   QTreeWidgetItem &	operator= ( const QTreeWidgetItem & other)
   {
      return *this;
   };
   ListView * listView() const;
public:
   ListViewItem * itemBelow() const;
   ListViewItem * itemAbove() const;
   virtual void setPixmap(int column, const QPixmap & pixmap);
   virtual const QPixmap pixmap(int column);
   void setImage(int column, const QImage & image);
   int itemPos();
   virtual void setOpen(bool state);
   void setExpandable(bool state);
   void setSelectable(bool state);
   void widthChanged(int column = -1);
   int depth() const;
   virtual void invalidateHeight();
   void setHeight(int height);
   void repaint();
   virtual void setup();
   virtual int compare(ListViewItem * item, int col, bool ascending) const;
   int height() const;
   int width() const;
   int width(const QFontMetrics & fontMetrics, ListView * listView, int column) const;
   bool isSelectable() const;
   QString key(int column, bool ascending) const {return text(column);};
protected:
// this method is no more supported with Qt 4
// and is substituted by the method below (regard the changed parameter list)
//
//   virtual void paintCell(QPainter* painter, const QColorGroup& colorGroup, int column, int width, int alignment);
//
   virtual void paintCell(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index);
// style option initialization for items: bridges to ListViewItemDelegate
   virtual void initStyleOption(QStyleOptionViewItem * option, const QModelIndex & index) const;
protected:
   std::map<int,QColor> _colorMap;
public:
   inline bool isColored(int column) const
   {
      std::map<int,QColor>::const_iterator i = _colorMap.find(column);
      if (i == _colorMap.end()) {
         return false;
      } else {
         return true;
      }
   };
   inline void clearColor(int column)
   {
      _colorMap.erase(column);
   }
   inline QColor getColor(int column) const
   {
      std::map<int,QColor>::const_iterator i = _colorMap.find(column);
      if (i == _colorMap.end()) {
         return QColor();
      } else {
         return (*i).second;;
      }
   }
   inline void setColor(int column, const QColor &color)
   {
      _colorMap[column] = color;
   }
public:
   void setForegroundColor(QModelIndex index, QColor color);
   void setBackgroundColor(QModelIndex index, QColor color);
   void setAlignment(QModelIndex index, Qt::Alignment alignment);
   QSize cellSizeHint(const QModelIndex & index);
protected:
   bool _isSelectable;
private:
   void setColumnAlignments();
public:
   void setVisible(bool state);
};

#endif // _listviewitem_h_


