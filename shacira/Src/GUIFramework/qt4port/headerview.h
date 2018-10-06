
#ifndef _headerview_h_
#define _headerview_h_

#include <qwidget.h>
#include <qstring.h>
#include <qtreewidget.h>
#include <qheaderview.h>
#include <qpainter.h>

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

class _CWIDGET_EXPORT_ HeaderView : public QHeaderView
{
public:
   HeaderView(Qt::Orientation orientation, QWidget * parent = 0);
   virtual ~HeaderView();
   void setClickEnabled(bool state);
   void setMovingEnabled(bool state);
   void setResizeEnabled(bool state, int column = -1);
   int headerWidth() const;
   void setClickEnabled(bool state, int column);
   bool isResizeEnabled(int column) const;
   QString label(int column) const;
   QIcon iconSet(int column) const;
   int sectionPos(int column) const;
   virtual void setStretchEnabled(bool b, int section = -1);
   void setPixmap(int logicalIndex, const QPixmap & pixmap);
   virtual QSize sizeHint() const;
   void setSectionResized(int logicalIndex, int oldSize, int newSize);
   bool getColumnWidthManuelChanged() { return _columnWidthManuelChanged; };

protected:
   void paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const;
   bool event(QEvent * event);
   void mousePressEvent(QMouseEvent * e);
   void mouseReleaseEvent(QMouseEvent *e);
   void adjustPixmaps();

private:
   QVector<QPixmap> _headerPixmaps;
   int _height;
   bool _initialized;
   bool _mouseIsPressed;
   bool _columnWidthManuelChanged;
};

#endif // _headerview_h_


