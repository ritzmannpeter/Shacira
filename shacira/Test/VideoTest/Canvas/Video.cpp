
#include "FirstHeader.h"
#include "Video.h"
#include "System/Objects/cObjectLock.h"
#include "math.h"

#define CANVAS_X     800
#define CANVAS_Y     600

ImageItem::ImageItem(QCanvas *canvas ): QCanvasItem(canvas)
{
   _Rectangle = QRect(0, 0, CANVAS_X-1, CANVAS_Y-1);
   _Pixmap = new QPixmap;
}

void ImageItem::SetImage(QImage * image)
{
   (*_Pixmap).convertFromImage(*image, OrderedAlphaDither);
}

void ImageItem::draw(QPainter &p)
{
   if (_Pixmap != NULL) p.drawPixmap(0, 0, *_Pixmap);
//   update();
}


PolylineItem::PolylineItem(QCanvas *canvas, int offset ): QCanvasItem(canvas)
{
   _Rectangle = QRect(0, 0, CANVAS_X-1, CANVAS_Y-1);
   _Offset = offset;
   _Curve = new cCurve(500, true);
   _Curve->SetXScale(0, CANVAS_X, 0, 0);
}

void PolylineItem::SetPoints()
{
   SetPoint(0, cSystemUtils::RealtimeOffset(), rand()%2);
}

void PolylineItem::SetPoint(uint index, int x, int y)
{
   _Curve->SetPoint(x, y);
}

extern unsigned long NanoSeconds(unsigned long);
void PolylineItem::draw(QPainter &p)
{
//   p.setPen(QPen(QColor(_Offset%32*8, _Offset%32*8, _Offset%32*8),3));
   unsigned long base = cSystemUtils::RealtimeOffset();
   unsigned long begin = base;
   unsigned long end = begin - NanoSeconds(1);
   _Curve->SetXScale(0, CANVAS_X, end, begin);
   _Curve->FillPointArray(_Points, begin, end);
   QColor color;
//   color = QColor(255, 255, 255);
   unsigned long size = _Points.size();
   for (unsigned long i=0; i<size; i++) {
      QPoint point = _Points.point(i);
      double x = point.x();
      double y = point.y();
      printf("(%f/%f)\n", x, y);
   }
   printf("paint\n");
   p.setWindow(0, -2, CANVAS_X, 5);
   p.setPen(QPen(color,2));
   p.drawPolyline(_Points);
   update();
}

#define COLOR_COUNT  256
static QRgb _ColorTable[COLOR_COUNT] = {0};
static void FillTable()
{
   for (int i=0; i<COLOR_COUNT; i++) {
      int r = i;
      int g = i/2;
      int b = i%2;
      QColor color(r, g, b);
      color = color.light(600);
      _ColorTable[i] = qGray(color.red(), color.green(), color.blue());
   }
}

Video::Video(Grabber * grabber, cMutexSem * sync)
   : _Canvas(NULL), _ImageItem(NULL), _PolylineItem(NULL),
     _Grabber(NULL), _ImageTimer(NULL), _GraphicTimer(NULL), _Sequence(0), _Sync(NULL)
{
   _Canvas = new QCanvas(CANVAS_X, CANVAS_Y);
   setCanvas(_Canvas);
   _Canvas->setUpdatePeriod(50);
#ifdef USE_CANVAS
  _ImageItem = new ImageItem(_Canvas);
  _ImageItem->show();
//  _PolylineItem = new PolylineItem(_Canvas, 225);
//  _PolylineItem->show();
  _PolylineItem2 = new PolylineItem(_Canvas, 96);
  _PolylineItem2->show();
#endif
  FillTable();
   setBackgroundMode(Qt::NoBackground);
   _Grabber = grabber;
   _Sync = sync;
   _ImageTimer = new QTimer(this);
   connect(_ImageTimer, SIGNAL(timeout()), SLOT(updateImage()));
   _ImageTimer->start(REFRESH);
   _GraphicTimer = new QTimer(this);
   connect(_GraphicTimer, SIGNAL(timeout()), SLOT(updateGraphic()));
  _GraphicTimer->start(2000);
}

Video::~Video()
{
}

void Video::paintEvent(QPaintEvent * e)
{
}

extern void SetVideoChannel(int channel);
void Video::keyPressEvent( QKeyEvent *k )
{
   switch ( tolower(k->ascii()) ) {
   case 'q':
      QApplication::exit();
      break;
   case 'v':
      _PolylineItem->SetPoints();
      break;
   case '0':
      SetVideoChannel(0);
      break;
   case '1':
      SetVideoChannel(1);
      break;
   case '2':
      SetVideoChannel(2);
      break;
   case '3':
      SetVideoChannel(3);
      break;
   }
}

void Video::ShowImage()
{
}

void Video::Show(int i, int n)
{
}

void Video::updateImage()
{
return;
   cObjectLock __lock__(_Sync);
   BUF_T buf = _Grabber->Buffer();
   if (buf != NULL) {
      QImage image = QImage(buf,
                            XSIZE,
                            YSIZE,
		                      PIXSIZE,
                            (unsigned int *)_ColorTable,
                            256,
                            QImage::BigEndian);
      int height = this->height();
      int width = this->width();
      image = image.scale(this->width(), this->height());
      _ImageItem->SetImage(&image);
   }
}

void Video::updateGraphic()
{
   _PolylineItem2->SetPoints();
//   _PolylineItem->SetPoints();
}
