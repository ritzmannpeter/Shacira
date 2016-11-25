
#ifndef _imageinformation_h_
#define _imageinformation_h_

#include <qstring.h>
#include <qimage.h>
#include <map>
using namespace std;

class ImageReference
{
public:
   ImageReference();
   ImageReference(const ImageReference & right);
   ImageReference(const QString & formId, const QString & imageName, const QString & imageData, const QString & imageFormat, int imageLength);
   inline const QImage & image() const {return _image;};
   inline const QImage & matchedImage() const {return _matchedImage;};
   inline void setMatchedImage(const QImage & image) {_matchedImage = image;};
   inline const QString & resourceName() const {return _resourceName;};
   inline void setResourceName(const QString & name) {_resourceName = name;};
   static QImage imageFromData(const QString & imageData, const QString & imageFormat);
protected:
   QString _formId;
   QString _imageName;
   QString _imageData;
   QString _imageFormat;
   int _imageLength;
   QImage _image;
   QImage _matchedImage;
   QString _resourceName;
};
typedef map<QString,ImageReference*> IMAGE_REFERENCE_MAP_T;

class StoredImage
{
public:
   StoredImage();
   StoredImage(const StoredImage & right);
   StoredImage(const QString & absolutePath, const QString & relativePath, const QString & imageFile);
   inline const QImage & image() const {return _image;};
   QString resourceName() const;
protected:
   QString _absolutePath;
   QString _relativePath;
   QString _imageFile;
   QImage _image;
};
typedef map<QString,StoredImage*> STORED_IMAGE_MAP_T;

class GeneratedImage
{
public:
   GeneratedImage();
   GeneratedImage(const GeneratedImage & right);
   GeneratedImage(const QString & path, const QImage & image);
   inline const QString & globalImageName() const {return _globalImageName;};
   inline void setGlobalImageName(const QString & name) {_globalImageName = name;};
   inline const QString & path() const {return _path;};
   inline const QImage & image() const {return _image;};
   inline const QString & resourceName() const {return _resourceName;};
   inline void setResourceName(const QString & name) {_resourceName = name;};
   inline const QImage & mappedImage() const {return _mappedImage;};
   inline void setMappedImage(const QImage & image) {_mappedImage = image;};
protected:
   QString _globalImageName;
   QString _path;
   QImage _image;
   QImage _mappedImage;
   QString _resourceName;
};
typedef map<QString,GeneratedImage*> GENERATED_IMAGE_MAP_T;

#endif // _imageinformation_h_
