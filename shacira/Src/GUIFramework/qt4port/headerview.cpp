
#include "headerview.h"
#include <qevent.h>

HeaderView::HeaderView(Qt::Orientation orientation, QWidget * parent)
   : QHeaderView(orientation, parent), _initialized(false), _mouseIsPressed(false), 
     _columnWidthManuelChanged(false)
{
    QSize headerViewSize = QHeaderView::sizeHint();
    _height = headerViewSize.isValid() ? headerViewSize.height() : 0;
}

HeaderView::~HeaderView()
{
}

void HeaderView::setClickEnabled(bool state)
{
#ifdef QT5
   QHeaderView::setSectionsClickable(state);
#else
   QHeaderView::setClickable(state);
#endif
}

void HeaderView::setMovingEnabled(bool state)
{
#ifdef QT5
   QHeaderView::setSectionsMovable(state);
#else
   QHeaderView::setMovable(state);
#endif
}

void HeaderView::setResizeEnabled(bool state, int column)
{
   if (state == false) {
      if (column == -1) {
#ifdef QT5
         setSectionResizeMode(QHeaderView::Fixed);
#else
         setResizeMode(QHeaderView::Fixed);
#endif
      } else {
#ifdef QT5
         setSectionResizeMode(column, QHeaderView::Fixed);
#else
         setResizeMode(column, QHeaderView::Fixed);
#endif
      }
   }
}

int HeaderView::headerWidth() const
{
   int width = 0;
   int sectionCount = this->count();
   int i = 0;
   for (i=0; i<sectionCount; i++) {
      width += sectionSize(i);
   }
   return width;
}

void HeaderView::setClickEnabled(bool state, int column)
{
#ifdef QT5
   setSectionsClickable(state);
#else
   setClickable(state);
#endif
}

bool HeaderView::isResizeEnabled(int column) const
{
#ifdef QT5
   QHeaderView::ResizeMode mode = sectionResizeMode(column);
#else
   QHeaderView::ResizeMode mode = resizeMode(column);
#endif
   if (mode == QHeaderView::Fixed) {
      return false;
   } else {
      return true;
   }
}

QString HeaderView::label(int column) const
{
   QAbstractItemModel * model = this->model();
   QString label = model->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
   return label;
}

QIcon HeaderView::iconSet(int column) const
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
   QAbstractItemModel * model = this->model();
   QVariant headerData = model->headerData(column, Qt::Horizontal, Qt::DisplayRole);
   return QIcon();
}

int HeaderView::sectionPos(int column) const
{
   return QHeaderView::sectionPosition(column);
}

void HeaderView::setStretchEnabled(bool b, int section)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

void HeaderView::setPixmap(int logicalIndex, const QPixmap & pixmap)
{
   if (logicalIndex >= _headerPixmaps.size()) {
      if (!pixmap.isNull()) {
         _headerPixmaps.resize(logicalIndex+1);
#ifdef QT5
         setSectionResizeMode(QHeaderView::Fixed);
#else
         setResizeMode(QHeaderView::Fixed);
#endif
         QSize pixmapSize = pixmap.size();
#ifdef QT5
         setSectionResizeMode(QHeaderView::Fixed);
#else
         setResizeMode(QHeaderView::Fixed);
#endif
         resizeSection(logicalIndex, pixmapSize.width());
         if (_height < pixmapSize.height()) {
            _height = pixmapSize.height();
         }
      }
   }
   _headerPixmaps[logicalIndex] = pixmap;
   _initialized = false;
}

QSize HeaderView::sizeHint() const
{
   QSize baseHint = QHeaderView::sizeHint();
   if (_height > baseHint.height()) {
      return QSize(baseHint.width(), _height + 5);
   } else {
      return baseHint;
   }
}

void HeaderView::paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const
{
   if (logicalIndex < _headerPixmaps.size()) {
      QPixmap pixmap = _headerPixmaps[logicalIndex];
      if (!pixmap.isNull()) {
         painter->drawPixmap(rect.x(), rect.y(), pixmap);
         return;
      }
   }
   return QHeaderView::paintSection(painter, rect, logicalIndex);
}

bool HeaderView::event(QEvent * e)
{
   if (e->type() == QEvent::Show) {
      if (!_initialized) {
         adjustPixmaps();
         _initialized = true;
      }
   }
   return QHeaderView::event(e);
}

void HeaderView::mousePressEvent(QMouseEvent * e)
{
   _mouseIsPressed = true;
   QHeaderView::mousePressEvent(e);
}

void HeaderView::mouseReleaseEvent(QMouseEvent *e)
{
    _mouseIsPressed = false;
    QHeaderView::mouseReleaseEvent(e);
}

void HeaderView::setSectionResized(int logicalIndex, int oldSize, int newSize)
{
   if (_mouseIsPressed)
      _columnWidthManuelChanged = true;
}

void HeaderView::adjustPixmaps()
{
   int columnCount = count();
   int column = 0;
   for (column=0; column<columnCount; column++) {
      int width = sectionSize(column);
      int height = sizeHint().height();
      if (column < _headerPixmaps.size()) {
         QPixmap pixmap = _headerPixmaps[column];
         if (!pixmap.isNull()) {
            QSize pixmapSize = pixmap.size();
            width = pixmapSize.width();
            height = pixmapSize.height();
#ifdef QT5
            setSectionResizeMode(QHeaderView::Fixed);
#else
            setResizeMode(QHeaderView::Fixed);
#endif
            resizeSection(column, pixmapSize.width());
         }
      }
   }
}

