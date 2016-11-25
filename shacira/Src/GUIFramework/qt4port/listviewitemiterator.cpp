
#include "listview.h"
#include "listviewitem.h"

ListViewItemIterator::ListViewItemIterator(ListView * listView)
   : _nativeIterator(listView)
{
}

ListViewItemIterator::ListViewItemIterator(ListViewItem * listViewItem)
   : _nativeIterator(listViewItem)
{
}

ListViewItemIterator::~ListViewItemIterator()
{
}

ListViewItem * ListViewItemIterator::current() const
{
   QTreeWidgetItem * item = *_nativeIterator;
   return static_cast<ListViewItem*>(item);
}

ListViewItem * ListViewItemIterator::operator*()
{
   QTreeWidgetItem * item = *_nativeIterator;
   return static_cast<ListViewItem*>(item);
}

ListViewItemIterator & ListViewItemIterator::operator++()
{
   _nativeIterator++;
   return (*this);
}

const ListViewItemIterator ListViewItemIterator::operator++(int)
{
   _nativeIterator++;
   return (*this);
}

ListViewItemIterator & ListViewItemIterator::operator+=(int j)
{
   _nativeIterator += j;
   return (*this);
}

ListViewItemIterator & ListViewItemIterator::operator--()
{
   _nativeIterator--;
   return (*this);
}

const ListViewItemIterator	ListViewItemIterator::operator--(int)
{
   _nativeIterator--;
   return (*this);
}

ListViewItemIterator & ListViewItemIterator::operator-=(int j)
{
   _nativeIterator -= j;
   return (*this);
}

ListViewItemIterator & ListViewItemIterator::operator=(const ListViewItemIterator & it)
{
   _nativeIterator = it._nativeIterator;
   return (*this);
}

