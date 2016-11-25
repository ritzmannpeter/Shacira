
#include "image.h"

#ifdef document_format
Constant	Value	Description
QImage::Format_Invalid	0	The image is invalid.
QImage::Format_Mono	1	The image is stored using 1-bit per pixel. Bytes are packed with the most significant bit (MSB) first.
QImage::Format_MonoLSB	2	The image is stored using 1-bit per pixel. Bytes are packed with the less significant bit (LSB) first.
QImage::Format_Indexed8	3	The image is stored using 8-bit indexes into a colormap.
QImage::Format_RGB32	4	The image is stored using a 32-bit RGB format (0xffRRGGBB).
QImage::Format_ARGB32	5	The image is stored using a 32-bit ARGB format (0xAARRGGBB).
QImage::Format_ARGB32_Premultiplied	6	The image is stored using a premultiplied 32-bit ARGB format (0xAARRGGBB), i.e. the red, green, and blue channels are multiplied by the alpha component divided by 255. (If RR, GG, or BB has a higher value than the alpha channel, the results are undefined.) Certain operations (such as image composition using alpha blending) are faster using premultiplied ARGB32 than with plain ARGB32.
QImage::Format_RGB16	7	The image is stored using a 16-bit RGB format (5-6-5).
QImage::Format_ARGB8565_Premultiplied	8	The image is stored using a premultiplied 24-bit ARGB format (8-5-6-5).
QImage::Format_RGB666	9	The image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero.
QImage::Format_ARGB6666_Premultiplied	10	The image is stored using a premultiplied 24-bit ARGB format (6-6-6-6).
QImage::Format_RGB555	11	The image is stored using a 16-bit RGB format (5-5-5). The unused most significant bit is always zero.
QImage::Format_ARGB8555_Premultiplied	12	The image is stored using a premultiplied 24-bit ARGB format (8-5-5-5).
QImage::Format_RGB888	13	The image is stored using a 24-bit RGB format (8-8-8).
QImage::Format_RGB444	14	The image is stored using a 16-bit RGB format (4-4-4). The unused bits are always zero.
QImage::Format_ARGB4444_Premultiplied	15	The image is stored using a premultiplied 16-bit ARGB format (4-4-4-4).
Note: Drawing into a QImage with QImage::Format_Indexed8 is not supported.
Note: Do not render into ARGB32 images using QPainter. Using QImage::Format_ARGB32_Premultiplied is significantly faster.
See also format() and convertToFormat().
#endif

static QImage invalidImage(int w, int h)
{
   QImage image(w, h, QImage::Format_RGB32);
   image.fill(Qt::red);
   return image;
}

QImage Image::image(int w, int h, int depth, int numColors, Endian bitOrder)
{
   QImage::Format format = QImage::Format_Indexed8;
   QImage image(w, h, format);
 // For 8 bit images the default number of colors is 256. If
 // another number of colors is required it can be specified
 // using the setColorCount() function.
    image.setColorCount(numColors);
    return image;
}

QImage Image::image(const QSize & size, int depth, int numColors, Endian bitOrder)
{
return invalidImage(size.width(), size.height());
}

QImage Image::image(const QString & fileName, const char * format)
{
return QImage();
}

QImage Image::image(const char * const xpm[])
{
return QImage();
}

QImage Image::image(const QByteArray & array)
{
return QImage();
}

QImage Image::image(uchar * data, int w, int h, int depth, QRgb * colortable, int numColors, Endian bitOrder)
{
   QVector<QRgb> new_colortable;
   new_colortable.resize(numColors);
   int i = 0;
   for (i=0; i<numColors; i++) {
      new_colortable[i] = colortable[i];
   }
   QImage::Format format = QImage::Format_Indexed8;
   QImage image(data, w, h, format);
   image.setColorTable(new_colortable);
   return image;
}

QImage Image::image(uchar * yourdata, int w, int h, int depth, int bpl, QRgb * colortable, int numColors, Endian bitOrder)
{
return invalidImage(w, h);
}




