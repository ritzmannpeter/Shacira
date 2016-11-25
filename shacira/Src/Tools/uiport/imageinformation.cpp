
#include "imageinformation.h"

ImageReference::ImageReference()
   : _imageLength(0)
{
}

ImageReference::ImageReference(const ImageReference & right)
   : _formId(right._formId), _imageName(right._imageName), _imageData(right._imageData), _imageFormat(right._imageFormat), _imageLength(right._imageLength), _image(right._image)
{
}

ImageReference::ImageReference(const QString & formId, const QString & imageName, const QString & imageData, const QString & imageFormat, int imageLength)
   : _formId(formId), _imageName(imageName), _imageData(imageData), _imageFormat(imageFormat), _imageLength(imageLength)
{
   QImage image = imageFromData(imageData, imageFormat);
   int l = imageData.length();
   QSize s = image.size();
   if (l != _imageLength*2 && _imageFormat != "XPM.GZ") {
      int dummy = 0;
   }
   if (image.isNull()) {
      int dummy = 0;
   }
   _image = image;
}

// from qt 3 designer source qt/tools/designer/designer/resource.cpp
QImage ImageReference::imageFromData(const QString & data, const QString & format)
{  
const int lengthOffset = 4;
   QImage img;
   int baSize = data.length() / 2 + lengthOffset;
   uchar *ba = new uchar[baSize];
   for (int i = lengthOffset; i < baSize; ++i) {
      char h = data[ 2 * (i-lengthOffset) ].toLatin1();
	   char l = data[ 2 * (i-lengthOffset) + 1 ].toLatin1();
	   uchar r = 0;
	   if ( h <= '9' ) {
         r += h - '0';
      } else {
	      r += h - 'a' + 10;
      }
	   r = r << 4;
	   if (l <= '9') {
	      r += l - '0';
      } else {
	      r += l - 'a' + 10;
      }
	   ba[i] = r;
   }
   if (format == "XPM.GZ" || format == "XBM.GZ") {
      int dataLength = data.length() * 5;
      // qUncompress() expects the first 4 bytes to be the expected length of
      // the uncompressed data
      ba[0] = (dataLength & 0xff000000) >> 24;
      ba[1] = (dataLength & 0x00ff0000) >> 16;
      ba[2] = (dataLength & 0x0000ff00) >> 8;
      ba[3] = (dataLength & 0x000000ff);
      QByteArray baunzip = qUncompress(ba, baSize);
      img.loadFromData((const uchar*)baunzip.data(), baunzip.size(), format.left(format.indexOf('.')).toStdString().c_str());
   } else {
      img.loadFromData( (const uchar*)ba+lengthOffset, baSize-lengthOffset, format.toStdString().c_str());
   }
   delete [] ba;
   return img;
}


StoredImage::StoredImage()
{
}

StoredImage::StoredImage(const StoredImage & right)
   : _absolutePath(right._absolutePath), _imageFile(right._imageFile), _image(right._image)
{
}

StoredImage::StoredImage(const QString & absolutePath, const QString & relativePath, const QString & imageFile)
   : _absolutePath(absolutePath), _relativePath(relativePath), _imageFile(imageFile)
{
   QImage image;
   if (!relativePath.isEmpty()) {
      int dummy = 0;
   }
   if (image.load(_absolutePath, NULL)) {
      QSize s = image.size();
      _image = image;
   } else {
      int dummy = 0;
   }
}

QString StoredImage::resourceName() const
{
   if (_relativePath.isEmpty()) {
      return _imageFile;
   } else {
      return _relativePath + "/" + _imageFile;
   }
}


GeneratedImage::GeneratedImage()
{
}

GeneratedImage::GeneratedImage(const GeneratedImage & right)
   : _path(right._path), _image(right._image)
{
}

GeneratedImage::GeneratedImage(const QString & path, const QImage & image)
   : _path(path), _image(image)
{
}

