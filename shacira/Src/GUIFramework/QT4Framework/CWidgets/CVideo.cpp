
/// PR 20.10.05 - improved visualization and control of invalid and empty images
///               (hint from GH, Nela)

#include "CVideo.h"
#ifdef QT4
#include "image.h"
#endif

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ViewWidget, \
                   CVideo, \
                   ICON_SET("image"), \
                   "widget to display images")
#endif

#include <qpixmap.h>
#include <qimage.h>
#include <qpainter.h>

#ifndef QT_PLUGIN
#include "System/Database/cImage.h"
#endif

#define COLOR_COUNT  256
static QRgb ColorTable[COLOR_COUNT] = {0};
static void FillTable()
{
   for (int i=0; i<COLOR_COUNT; i++) {
      int r = i;
      int g = i/2;
      int b = i%2;
      QColor color(r, g, b);
      color = color.light(600);
      ColorTable[i] = qGray(color.red(), color.green(), color.blue());
   }
}

static int Scale(int value, int sx0, int sx1, int dx0, int dx1)
{
   double d0 = sx1 - sx0;
   if (d0 != 0) {
      double d1 = dx1 - dx0;
      int scaled = (int)((value - sx0) * (d1 / d0));
      return scaled;
   }
   return value;
}

static const QRgb _GrayTable[] = 
{
   0xff000000,0xff010101,0xff020202,0xff030303,0xff040404,0xff050505,0xff060606,0xff070707,0xff080808,0xff090909,0xff0a0a0a,0xff0b0b0b,0xff0c0c0c,0xff0d0d0d,0xff0e0e0e,0xff0f0f0f,
	0xff101010,0xff111111,0xff121212,0xff131313,0xff141414,0xff151515,0xff161616,0xff171717,0xff181818,0xff191919,0xff1a1a1a,0xff1b1b1b,0xff1c1c1c,0xff1d1d1d,0xff1e1e1e,0xff1f1f1f,
	0xff202020,0xff212121,0xff222222,0xff232323,0xff242424,0xff252525,0xff262626,0xff272727,0xff282828,0xff292929,0xff2a2a2a,0xff2b2b2b,0xff2c2c2c,0xff2d2d2d,0xff2e2e2e,0xff2f2f2f,
	0xff303030,0xff313131,0xff323232,0xff333333,0xff343434,0xff353535,0xff363636,0xff373737,0xff383838,0xff393939,0xff3a3a3a,0xff3b3b3b,0xff3c3c3c,0xff3d3d3d,0xff3e3e3e,0xff3f3f3f,
	0xff404040,0xff414141,0xff424242,0xff434343,0xff444444,0xff454545,0xff464646,0xff474747,0xff484848,0xff494949,0xff4a4a4a,0xff4b4b4b,0xff4c4c4c,0xff4d4d4d,0xff4e4e4e,0xff4f4f4f,
	0xff505050,0xff515151,0xff525252,0xff535353,0xff545454,0xff555555,0xff565656,0xff575757,0xff585858,0xff595959,0xff5a5a5a,0xff5b5b5b,0xff5c5c5c,0xff5d5d5d,0xff5e5e5e,0xff5f5f5f,
	0xff606060,0xff616161,0xff626262,0xff636363,0xff646464,0xff656565,0xff666666,0xff676767,0xff686868,0xff696969,0xff6a6a6a,0xff6b6b6b,0xff6c6c6c,0xff6d6d6d,0xff6e6e6e,0xff6f6f6f,
	0xff707070,0xff717171,0xff727272,0xff737373,0xff747474,0xff757575,0xff767676,0xff777777,0xff787878,0xff797979,0xff7a7a7a,0xff7b7b7b,0xff7c7c7c,0xff7d7d7d,0xff7e7e7e,0xff7f7f7f,
	0xff808080,0xff818181,0xff828282,0xff838383,0xff848484,0xff858585,0xff868686,0xff878787,0xff888888,0xff898989,0xff8a8a8a,0xff8b8b8b,0xff8c8c8c,0xff8d8d8d,0xff8e8e8e,0xff8f8f8f,
	0xff909090,0xff919191,0xff929292,0xff939393,0xff949494,0xff959595,0xff969696,0xff979797,0xff989898,0xff999999,0xff9a9a9a,0xff9b9b9b,0xff9c9c9c,0xff9d9d9d,0xff9e9e9e,0xff9f9f9f,
	0xffa0a0a0,0xffa1a1a1,0xffa2a2a2,0xffa3a3a3,0xffa4a4a4,0xffa5a5a5,0xffa6a6a6,0xffa7a7a7,0xffa8a8a8,0xffa9a9a9,0xffaaaaaa,0xffababab,0xffacacac,0xffadadad,0xffaeaeae,0xffafafaf,
	0xffb0b0b0,0xffb1b1b1,0xffb2b2b2,0xffb3b3b3,0xffb4b4b4,0xffb5b5b5,0xffb6b6b6,0xffb7b7b7,0xffb8b8b8,0xffb9b9b9,0xffbababa,0xffbbbbbb,0xffbcbcbc,0xffbdbdbd,0xffbebebe,0xffbfbfbf,
	0xffc0c0c0,0xffc1c1c1,0xffc2c2c2,0xffc3c3c3,0xffc4c4c4,0xffc5c5c5,0xffc6c6c6,0xffc7c7c7,0xffc8c8c8,0xffc9c9c9,0xffcacaca,0xffcbcbcb,0xffcccccc,0xffcdcdcd,0xffcecece,0xffcfcfcf,
	0xffd0d0d0,0xffd1d1d1,0xffd2d2d2,0xffd3d3d3,0xffd4d4d4,0xffd5d5d5,0xffd6d6d6,0xffd7d7d7,0xffd8d8d8,0xffd9d9d9,0xffdadada,0xffdbdbdb,0xffdcdcdc,0xffdddddd,0xffdedede,0xffdfdfdf,
	0xffe0e0e0,0xffe1e1e1,0xffe2e2e2,0xffe3e3e3,0xffe4e4e4,0xffe5e5e5,0xffe6e6e6,0xffe7e7e7,0xffe8e8e8,0xffe9e9e9,0xffeaeaea,0xffebebeb,0xffececec,0xffededed,0xffeeeeee,0xffefefef,
	0xfff0f0f0,0xfff1f1f1,0xfff2f2f2,0xfff3f3f3,0xfff4f4f4,0xfff5f5f5,0xfff6f6f6,0xfff7f7f7,0xfff8f8f8,0xfff9f9f9,0xfffafafa,0xfffbfbfb,0xfffcfcfc,0xfffdfdfd,0xfffefefe,0xffffffff
};

CVideo::CVideo(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QLabel(parent, f),
#else
   : QLabel(parent, name, f),
#endif
     CWidgetBase(this),
     _RubberBand(this)
{
   CONSTRUCT_WIDGET

   _VarRef = NULL;
   _VarView = NULL;
   _Left1Ref = NULL;
   _Left1View = NULL;
   _Top1Ref = NULL;
   _Top1View = NULL;
   _Left2Ref = NULL;
   _Left2View = NULL;
   _Top2Ref = NULL;
   _Top2View = NULL;

   setFrameStyle(QFrame::Panel | QFrame::Raised );
   _Buffer = NULL;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   FillTable();
   _ColorTable = ColorTable;
   _ColorCount = sizeof(_GrayTable) / sizeof(QRgb);
   _ImagePresent = false;
WMETHOD_VOID_EPILOG
#endif
   QColor bg_color;
   setPaletteBackgroundColor(bg_color);
   _Cursor = cursor();
}

void CVideo::paintEvent(QPaintEvent *)
{
   ShowImage();
}

void CVideo::mousePressEvent(QMouseEvent * e)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!HelpActive()) {
      _RubberBand.Grip(e->x(), e->y());
   }
WMETHOD_VOID_EPILOG
#endif
};

void CVideo::mouseMoveEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
#ifdef QT4
      Qt::MouseButtons buttons = e->buttons();
      if (buttons & Qt::LeftButton) {
         _RubberBand.UpdateRegion();
         _RubberBand.UpdateRegion(e->pos());
      }
#else
      if (e->state() & Qt::LeftButton) {
         _RubberBand.UpdateRegion();
         _RubberBand.UpdateRegion(e->pos());
      }
#endif
   }
}

void CVideo::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QLabel::mouseReleaseEvent(e);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
      _RubberBand.Ungrip(e->x(), e->y());
      SaveRectangle();
WMETHOD_VOID_EPILOG
#endif
   }
};

CVideo::~CVideo ( ) 
{
}

// GUI related virtual methods

void CVideo::View()
{
}

// CCS related virtual methods

void CVideo::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
   CCSInitializeVarRef(_Left1Spec, _Left1Ref, _Left1View, 1);
   CCSInitializeVarRef(_Top1Spec, _Top1Ref, _Top1View, 2);
   CCSInitializeVarRef(_Left2Spec, _Left2Ref, _Left2View, 3);
   CCSInitializeVarRef(_Top2Spec, _Top2Ref, _Top2View, 4);
WMETHOD_VOID_EPILOG
#endif
}

void CVideo::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (id > 0 && id < 5) {
      int x_size = 0;
      int y_size = 0;
      int cx_size = 0;
      int cy_size = 0;
      if (_Buffer != NULL) {
         cImage ccs_image(_Buffer);
         if (!ccs_image.IsEmpty()) {
            x_size = this->width();
            y_size = this->height();
            cImage image;
            cx_size = ccs_image.GetXSize();
            cy_size = ccs_image.GetYSize();
            _RubberBand.SetScale(x_size, y_size, cx_size, cy_size);
         }
      }
      switch (id) {
      case 1:
         _RubberBand.SetLeft(atol(value));
         break;
      case 2:
         _RubberBand.SetTop(atol(value));
         break;
      case 3:
         _RubberBand.SetRight(atol(value));
         break;
      case 4:
         _RubberBand.SetBottom(atol(value));
         break;
      }
      repaint();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CVideo::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (id != 0) return;
   _Buffer = buf;
   repaint();
WMETHOD_VOID_EPILOG
#endif
}

void CVideo::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CVideo::ShowImage()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Buffer != NULL) {
      cImage ccs_image(_Buffer);
      if (!ccs_image.IsEmpty()) {
         if (!_ImagePresent) {
#ifdef QT4
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
#else
            setBackgroundMode(Qt::NoBackground);
#endif
            _ImagePresent = true;
         }
         ULONG_T x_size = ccs_image.GetXSize();
         ULONG_T y_size = ccs_image.GetYSize();
         ULONG_T pix_size = ccs_image.GetPixSize();
         ULONG_T color_count = ccs_image.GetColorCount();
         if (y_size > 1920 || x_size > 2560) {
            QPainter painter(this);
		      painter.setPen(Qt::blue);
		      painter.eraseRect(rect());
            char text[0x100] = {0};
            SafePrintf(text, sizeof(text), "invalid image (%d,%d)", x_size, y_size);
            painter.drawText(rect(), Qt::AlignCenter, text);
         } else {
#ifdef QT4
            QImage image = Image::image(ccs_image.GetImageData(),
                                  x_size,
                                  y_size,
	                               pix_size,
                                  (unsigned int *)_GrayTable,
                                  color_count,
                                  Image::BigEndian);
#else
            QImage image = QImage(ccs_image.GetImageData(),
                                  x_size,
                                  y_size,
	                               pix_size,
                                  (unsigned int *)_GrayTable,
                                  color_count,
                                  QImage::BigEndian);
#endif
            int height = this->height();
            int width = this->width();
#ifdef QT4
            image = image.scaled(width, height);
#else
            image = image.scale(width, height);
#endif
            QPainter painter(this);
            painter.drawImage(0, 0, image);
         }
      } else {
         QPainter painter(this);
         painter.setPen(Qt::blue);
         painter.eraseRect(rect());
         painter.drawText(rect(), Qt::AlignCenter, "no image");
      }
   }
   if (_RubberBand.IsActive()) {
      QPainter painter(this);
      _RubberBand.Paint(painter);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CVideo::SaveRectangle()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Left1Ref == NULL ||
       _Top1Ref == NULL ||
       _Left2Ref == NULL ||
       _Top2Ref == NULL) {
      return;
   }
   int left = 0;
   int top = 0;
   int right = 0;
   int bottom = 0;
   try {
      _RubberBand.GetRectangle(left, top, right, bottom);
      _Left1Ref->SetValue((ULONG_T)left);
      _Top1Ref->SetValue((ULONG_T)top);
      _Left2Ref->SetValue((ULONG_T)right);
      _Top2Ref->SetValue((ULONG_T)bottom);
   } catch (...) {
   }
WMETHOD_VOID_EPILOG
#endif
}
