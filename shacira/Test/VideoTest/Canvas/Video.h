
#ifndef _VIDEO_H
#define _VIDEO_H

#include <qapplication.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qcanvas.h>
#include <qframe.h>
#include <qtimer.h>
#include <qcanvas.h>
#include "base/eb_sema.hpp"
#include "Grabber.h"
#include "cCurve.h"

#define REFRESH   20
#define XSIZE     640
#define YSIZE     480
#define PIXSIZE   8
#define IMAGESIZE ((XSIZE * YSIZE) * (PIXSIZE / 8))

class ImageItem: public QCanvasItem
{
public:
    ImageItem(QCanvas * canvas);
    void SetImage(QImage * image);
    void draw(QPainter &);
    virtual QRect boundingRect() const {return _Rectangle;};
    bool collidesWith( const QCanvasItem* ) const {return false;};
    bool collidesWith( const QCanvasSprite*,
		       const QCanvasPolygonalItem*,
		       const QCanvasRectangle*,
		       const QCanvasEllipse*,
             const QCanvasText* ) const {return false;};
private:
    QPixmap * _Pixmap;
    QRect _Rectangle;
};

class PolylineItem: public QCanvasItem
{
public:
    PolylineItem(QCanvas * canvas, int offset);
    void SetPoints();
    void SetPoint(uint index, int x, int y);
    void draw(QPainter &);
    virtual QRect boundingRect() const {return _Rectangle;};
    bool collidesWith( const QCanvasItem* ) const {return false;};
    bool collidesWith( const QCanvasSprite*,
		       const QCanvasPolygonalItem*,
		       const QCanvasRectangle*,
		       const QCanvasEllipse*,
             const QCanvasText* ) const {return false;};
private:
   QRect _Rectangle;
   QPointArray _Points;
   int _Offset;
   cCurve * _Curve;
};

#define USE_CANVAS
#ifdef USE_CANVAS
class Video : public QCanvasView
#else
//class Video : public QWidget
#endif
{
   Q_OBJECT
public:
    Video(Grabber * grabber, cMutexSem * sync);
   ~Video();
   void ShowImage();
   void Show(int i, int n);
protected:
   void paintEvent( QPaintEvent * );
   void keyPressEvent( QKeyEvent * );
public slots:
   void updateImage();
   void updateGraphic();
private:
   Grabber * _Grabber;
   QCanvas * _Canvas;
   ImageItem * _ImageItem;
   PolylineItem * _PolylineItem;
   PolylineItem * _PolylineItem2;
   QTimer * _ImageTimer;
   QTimer * _GraphicTimer;
   int _Sequence;
   bool _Recording;
   cMutexSem * _Sync;
};

#endif
