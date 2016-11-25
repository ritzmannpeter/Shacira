
#include "imageinformations.h"
#include "portingapplication.h"
#include "portingfile.h"
#include <qtextstream.h>

ImageInformations::ImageInformations(PortingApplication * application)
   : _application(application), _currentImageIndex(0), _hasNamedImages(false)
{
   _destinationPath = application->destinationDirectory().absolutePath();
   initialize();
   if (hasNamedImages()) {
      if (loadResolvedImages()) {
         int dummy = 0;
      } else {
         int dummy = 0;
      }
   }
}

ImageInformations::~ImageInformations()
{
   if (hasNamedImages()) {
      if (saveResolvedImages()) {
         if (saveUnmatchedImages()) {
         } else {
            int dummy = 0;
         }
      } else {
         int dummy = 0;
      }
   }
}

QString ImageInformations::resourceFileName() const
{
   QString resourceFileName = application()->name() + ".qrc";
   return resourceFileName;
}

QString ImageInformations::resourceFileReference(PortingFile * portingFile) const
{
   QString resourceFileReference;
   QString path = portingFile->logicPath();
   QStringList components = path.split("/");
   QStringList::const_iterator i = components.begin();
   while (i != components.end()) {
      if (i != components.begin()) {
         resourceFileReference += "../";
      }
      i++;
   }
   resourceFileReference += "qresources/";
   resourceFileReference += application()->name();
   resourceFileReference += ".qrc";
   // adapt resources path to project management
   int length = resourceFileReference.length() - 3;
   resourceFileReference = resourceFileReference.mid(3, length);
   //
   return resourceFileReference;
}

QString ImageInformations::resourceString(const QString & formId, const QString & imageName) const
{
   if (imageName.isEmpty()) {
      return "?1";
   }
   if (imageName[0] == ':') {
      // image reference already resolved
      return imageName;
   }
   QString resourceString = "?2";
   QString key = this->key(formId, imageName);
   IMAGE_INFORMATION_MAP_T::const_iterator i = _imageInformationMap.find(key);
   if (i != _imageInformationMap.end()) {
      ImageInformation * info = (*i).second;
      resourceString = ":/";
      resourceString += application()->name();
      resourceString = append(resourceString, info->imageFilePath());
   }
   return resourceString;
}

ImageFormats ImageInformations::formatFromSpecifier(const QString & specifier) const
{
   ImageFormats format = PNG;
   if (specifier.compare("PNG", Qt::CaseInsensitive) == 0) {
      format = PNG;
   } else if (specifier.compare("XPM.GZ", Qt::CaseInsensitive) == 0) {
      format = XPM;
   }
   return format;
}

QString ImageInformations::formatSpecifier(ImageFormats format) const
{
   QString specifier = "PNG";
   if (format == XPM) {
      specifier = "XPM.GZ";
   }
   return specifier;
}

void ImageInformations::initialize()
{
   _resourcesPath = append(_destinationPath, RESOURCES_DIRECTORY);
   _imagesPath = append(_resourcesPath, IMAGES_DIRECTORY);
   _matchedImagesPath = append(_resourcesPath, MATCHED_IMAGES_DIRECTORY);
   _unmatchedImagesPath = append(_resourcesPath, UNMATCHED_IMAGES_DIRECTORY);
   QDir destinationDir(_destinationPath);
   destinationDir.mkpath(_imagesPath);
   QDir imagesDir(_imagesPath);
   QStringList entryList = imagesDir.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      if (directoryName[0] != '.') {
         _hasNamedImages = true;
      }
   }
   QStringList filter;
   filter << "*.png";
   entryList = imagesDir.entryList(filter, QDir::Files);
   if (entryList.length() > 0) {
      _hasNamedImages = true;
   }
   application()->removeDirectory(_matchedImagesPath);
//   application()->removeDirectory(_unmatchedImagesPath);
   if (hasNamedImages()) {
      destinationDir.mkpath(_matchedImagesPath);
      destinationDir.mkpath(_unmatchedImagesPath);
   }
}
   
Image * ImageInformations::matchedImage(const QImage & image) const
{
   IMAGE_MAP_T::const_iterator i = _imageMap.begin();
   while (i != _imageMap.end()) {
      Image * compareImage = (*i).second;
      if (_imageMatcher.match(image, compareImage->qImage())) {
         return compareImage;
      }
      i++;
   }
   return NULL;
}

Image * ImageInformations::image(const QString & imageData, const QString & imageFormat)
{
   QImage qImage = PortingApplication::loadImageData(imageData, imageFormat);
   if (qImage.isNull()) {
      return NULL;
   }
   Image * image = matchedImage(qImage);
   if (image == NULL) {
      QString imageName = nextImageName();
      image = new Image(this, imageName, imageData, imageFormat);
      _imageMap[imageName] = image;
   } else {
      image->setQt3UiImage(qImage);
      if (imageData != image->imageData()) {
         int dummy = 0;
      }
      if (imageFormat != image->formatSpecifier()) {
         int dummy = 0;
      }
   }
   return image;
}

Image * ImageInformations::image(const QString & imageName)
{
   Image * image = NULL;
   IMAGE_MAP_T::const_iterator i = _imageMap.find(imageName);
   if (i != _imageMap.end()) {
      image = (*i).second;
   } else {
      int dummy = 0;
   }
   return image;
}

ImageInformation * ImageInformations::imageInformation(const QString & formId, const QString & imageName, const QString & imageData, const QString & imageFormat, int length)
{
   ImageInformation * imageInfo = NULL;
   QString key = this->key(formId, imageName);
   IMAGE_INFORMATION_MAP_T::const_iterator i = _imageInformationMap.find(key);
   if (i != _imageInformationMap.end()) {
      imageInfo = (*i).second;
   } else {
      ImageInformation * imageInformation = new ImageInformation(this, formId, imageName, imageData, imageFormat, length);
      _imageInformationMap[key] = imageInformation;
   }
   return imageInfo;
}

void ImageInformations::addImage(Image * image)
{
   QString imageName = image->imageName();
   QString key = append(image->path(), imageName);
   _imageMap[key] = image;
   setCurrentImageIndex(imageName);
}

void ImageInformations::addImageInformation(const QString & formId, const QString & imageName, const QString & globalImageName)
{
   ImageInformation * imageInformation = new ImageInformation(this, formId, imageName, globalImageName);
   QString key = this->key(formId, imageName);
   _imageInformationMap[key] = imageInformation;
}

bool ImageInformations::resolveUnmatchedImage(const QString & globalName, const QString & imageName, const QString & formId, QString & newImageName)
{
   QString reason;
   bool matched = false;
   QString key = unmatchedKey(imageName, formId);
   UNMATCHED_IMAGE_MAP_T::const_iterator i = _resolvedImageMap.find(key);
   if (i != _resolvedImageMap.end()) {
      newImageName = (*i).second._newImageName;
      if (newImageName.isEmpty()) {
         matched = false;
         reason = "specification is empty";
      } else {
         QDir resourcesDirectory(_resourcesPath);
         QString imageFile = append(_imagesPath, newImageName);
         imageFile += ".png";
         QFile file(imageFile);
         if (file.exists()) {
            matched = true;
         } else {
            matched = false;
            reason = imageFile + " not found";
         }
      }
   } else {
      matched = false;
      reason = "not specified";
   }
   if (matched || globalName.isEmpty()) {
      int dummy = 0;
   } else {
      struct UnmatchedImage unmatchedImage;
      unmatchedImage._imageName = imageName;
      unmatchedImage._formId = formId;
      unmatchedImage._globalName = globalName;
      unmatchedImage._reason = reason;
      _unmatchedImageMap[key] = unmatchedImage;
      _resolvedImageMap[key] = unmatchedImage;
   }
   return matched;
}

void ImageInformations::setCurrentImageIndex(const QString & imageName)
{
   QStringList nameParts = imageName.split("_");
   if (nameParts.size() == 2) {
      int index = nameParts.last().toInt();
      if (index > _currentImageIndex) {
         _currentImageIndex = index;
      }
   } else {
      int dummy = 0;
   }
}

QString ImageInformations::key(const QString & p1, const QString & p2) const
{
   return p1 + ":" + p2;
}

QString ImageInformations::nextImageName()
{
   _currentImageIndex++;
   QString imageName;
   imageName = "img_" + imageName.sprintf("%03d", _currentImageIndex);
   return imageName;
}

bool ImageInformations::loadResolvedImages()
{
   QDir resourcesDirectory(_resourcesPath);
   QString imageFile = append(_imagesPath, "resolvedimages.txt");
   QFile file(imageFile);
   if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
      while (!file.atEnd()) {
         UnmatchedImage unmatchedImage;
         QString line = file.readLine();
         int startPos = 0;
         int endPos = 0;
         endPos = line.indexOf(";", startPos);
         int column = 0;
         while (endPos >= 0) {
            QString value = line.mid(startPos, endPos - startPos);
            switch (column) {
            case 0:
//               unmatchedImage._globalName = value;
               break;
            case 1:
               unmatchedImage._imageName = value;
               break;
            case 2:
               unmatchedImage._formId = value;
               break;
            case 3:
               unmatchedImage._newImageName = value;
               break;
            default:
               break;
            }
            startPos = endPos + 1;
            endPos = line.indexOf(";", startPos);
            column++;
         }
         QString key = unmatchedKey(unmatchedImage._imageName, unmatchedImage._formId);
//         _resolvedImageMap[key] = unmatchedImage;
      }
      file.close();
   }
   return true;
}

bool ImageInformations::saveResolvedImages()
{
   QDir resourcesDirectory(_resourcesPath);
   QString imageFile = append(_imagesPath, "resolvedimages.txt");
   QFile file(imageFile);
   if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {
      QTextStream stream(&file);
      UNMATCHED_IMAGE_MAP_T::const_iterator i = _resolvedImageMap.begin();
      while (i != _resolvedImageMap.end()) {
         if ((*i).second._globalName.isEmpty()) {
            stream << "matched;";
            stream << (*i).second._imageName << ";";
            stream << (*i).second._formId << ";";
            stream << (*i).second._newImageName << ";" << endl;
         }
         i++;
      }
      i = _resolvedImageMap.begin();
      while (i != _resolvedImageMap.end()) {
         if (!(*i).second._globalName.isEmpty()) {
            stream << (*i).second._globalName << ";";
            stream << (*i).second._imageName << ";";
            stream << (*i).second._formId << ";";
            stream << (*i).second._newImageName << ";" << endl;
         }
         i++;
      }
      file.close();
   }
   return true;
}

bool ImageInformations::saveUnmatchedImages()
{
   QDir resourcesDirectory(_resourcesPath);
   QString imageFile = append(_unmatchedImagesPath, "unmatchedimages.txt");
   QFile file(imageFile);
   if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {
      QTextStream stream(&file);
      UNMATCHED_IMAGE_MAP_T::const_iterator i = _unmatchedImageMap.begin();
      while (i != _unmatchedImageMap.end()) {
         stream << (*i).second._globalName << ";";
         stream << (*i).second._imageName << ";";
         stream << (*i).second._formId << ";";
         stream << (*i).second._newImageName << ";\t\t// " ;
         stream << (*i).second._reason << endl;
         i++;
      }
      file.close();
   }
   return true;
}

