
#ifndef _listviewitemiterator_h_
#define _listviewitemiterator_h_

#include <qwidget.h>
#include <qstring.h>
#include <qtreewidget.h>
#include <qheaderview.h>

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
#include "listviewitem.h"

class _CWIDGET_EXPORT_ ListViewItemIterator
{
public:
   ListViewItemIterator(ListView * listView);
   ListViewItemIterator(ListViewItem * listViewItem);
   virtual ~ListViewItemIterator();
   ListViewItem * current() const;
   ListViewItem *	operator*();
   ListViewItemIterator & operator++();
   const ListViewItemIterator operator++(int);
   ListViewItemIterator & operator+=(int j);
   ListViewItemIterator & operator--();
   const ListViewItemIterator	operator--(int);
   ListViewItemIterator & operator-=(int j);
   ListViewItemIterator & operator=(const ListViewItemIterator & it);
private:
   QTreeWidgetItemIterator _nativeIterator;
};

#endif // _listviewitemiterator_h_


