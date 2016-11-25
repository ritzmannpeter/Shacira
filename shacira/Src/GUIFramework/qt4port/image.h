
#ifndef _image_h_
#define _image_h_

#include <qimage.h>

class Image
{
public:
   typedef enum Endian {IgnoreEndian, BigEndian};
public:
   static QImage image(int w, int h, int depth, int numColors = 0, Endian bitOrder = IgnoreEndian);
   static QImage image(const QSize & size, int depth, int numColors = 0, Endian bitOrder = IgnoreEndian);
   static QImage image(const QString & fileName, const char * format = 0);
   static QImage image(const char * const xpm[]);
   static QImage image(const QByteArray & array);
   static QImage image(uchar * yourdata, int w, int h, int depth, QRgb * colortable, int numColors, Endian bitOrder);
   static QImage image(uchar * yourdata, int w, int h, int depth, int bpl, QRgb * colortable, int numColors, Endian bitOrder);
};

#endif // _image_h_


