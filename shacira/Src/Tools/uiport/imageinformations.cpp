
#include "imageinformations.h"
#include "portingapplication.h"
#include "portingfile.h"
#include <qtextstream.h>

ImageInformations::ImageInformations(PortingApplication * application)
   : _application(application), _hasImages(false)
{
   _destinationPath = application->destinationDirectory().absolutePath();
   initialize();
}

ImageInformations::~ImageInformations()
{
   if (hasImages()) {
      savePersistentUnmatchedImages(_unmatchedPersistentImagesPath);
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
   QStringList::const_iterator i = components.constBegin();
   while (i != components.constEnd()) {
      if (i != components.constBegin()) {
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
   QString key = imageReferenceKey(formId, imageName);
   IMAGE_REFERENCE_MAP_T::const_iterator i = _imageReferenceMap.find(key);
   if (i != _imageReferenceMap.cend()) {
      resourceString = ":/";
      resourceString += application()->name();
      resourceString += "/images";
      resourceString = append(resourceString, (*i).second->resourceName());
   } else {
      int dummy = 0;
   }
   return resourceString;
}

void ImageInformations::initialize()
{
   _resourcesPath = append(_destinationPath, RESOURCES_DIRECTORY);
   _imagesPath = append(_resourcesPath, IMAGES_DIRECTORY);
   _matchedImagesPath = append(_resourcesPath, MATCHED_IMAGES_DIRECTORY);
   _unmatchedImagesPath = append(_resourcesPath, UNMATCHED_IMAGES_DIRECTORY);
   _unmatchedPersistentImagesPath = append(_resourcesPath, UNMATCHED_PERSISTENT_IMAGES_DIRECTORY);
   QDir destinationDir(_destinationPath);
   destinationDir.mkpath(_imagesPath);
   _hasImages = checkForPersistentImages(_imagesPath);
   if (_hasImages) {
      destinationDir.mkpath(_unmatchedPersistentImagesPath);
      loadPersistentUnmatchedImages(_unmatchedPersistentImagesPath);
   }
}

bool ImageInformations::checkForPersistentImages(const QString & path) const
{
   // assume path has no persistent images
   QDir imageDirectory(path);
   QStringList entryList = imageDirectory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      if (directoryName[0] != '.') {
         // return true if a named directory exists
         return true;
      }
   }
   entryList = imageDirectory.entryList(QDir::Files);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = *it;
      int number = -1;
      if (this->isPersistentImage(fileName, number)) {
         // return true if a file exists that does not match the generated file pattern
         return true;
      }
   }
   // return false otherwise
   return false;
}

bool ImageInformations::addImageReference(const QString & formId, const QString & imageName, const QString & imageData, const QString & imageFormat, int imageLength)
{
   const STORED_IMAGE_MAP_T & si = _storedImageMap;
   const IMAGE_REFERENCE_MAP_T & ir = _imageReferenceMap;
   QString key = imageReferenceKey(formId, imageName);
   ImageReference * imageReference = NULL;
   IMAGE_REFERENCE_MAP_T::const_iterator i = _imageReferenceMap.find(key);
   if (i == _imageReferenceMap.cend()) {
      imageReference = new ImageReference(formId, imageName, imageData, imageFormat, imageLength);
      _imageReferenceMap[key] = imageReference;
   } else {
      imageReference = (*i).second;
   }
   STORED_IMAGE_MAP_T::const_iterator sit = _storedImageMap.begin();
   while (sit != _storedImageMap.cend()) {
      StoredImage * storedImage = (*sit).second;
      if (_imageMatcher.match(imageReference->image(), storedImage->image())) {
         imageReference->setResourceName(storedImage->resourceName());
         imageReference->setMatchedImage(storedImage->image());
         return true;
      }
      sit++;
   }
   QString resourceName;
   QImage matchedImage;
   if (match(_unmatchedPersistentImagesPath, imageReference->image(), resourceName, matchedImage)) {
      imageReference->setResourceName(resourceName);
      imageReference->setMatchedImage(matchedImage);
   } else {
      if (_hasImages) {
         storeUnmatchedImage(_unmatchedPersistentImagesPath, newGlobalImageName(_unmatchedPersistentImagesPath), imageReference->image());
      } else {
         // if ijmages directory ha no explicitly stored images, the resource name of the
         // image reference is the name of the generated image
         QString resourceName = newGlobalImageName(_imagesPath);
         storeUnmatchedImage(_imagesPath, resourceName, imageReference->image());
         imageReference->setResourceName(resourceName);
      }
   }
   return true;
}

bool ImageInformations::addStoredImage(const QString & absolutePath, const QString & relativePath, const QString & imageFile)
{
   const STORED_IMAGE_MAP_T & si = _storedImageMap;
   const IMAGE_REFERENCE_MAP_T & ir = _imageReferenceMap;
   QString key = storedImageKey(relativePath, imageFile);
   StoredImage * storedImage = NULL;
   STORED_IMAGE_MAP_T::const_iterator i = _storedImageMap.find(key);
   if (i == _storedImageMap.cend()) {
      storedImage = new StoredImage(absolutePath, relativePath, imageFile);
      _storedImageMap[key] = storedImage;
   } else {
      storedImage = (*i).second;
   }
   return true;
}

void ImageInformations::loadPersistentUnmatchedImages(const QString & path)
{
   QString resolvedImagesFile = path + "/" + "resolve.txt";
   QFile qFile(resolvedImagesFile);
   if (qFile.open(QIODevice::ReadOnly)) {
      QTextStream stream(&qFile);
      while (!stream.atEnd()) {
         QString line = stream.readLine();
         QStringList components = line.split(";", QString::KeepEmptyParts);
         QString globalImageName = components.first();
         QString resourceName = components.last();
         QString imageFile = path + "/" + globalImageName;
         QImage image;
         if (image.load(imageFile)) {
            QString key = imageFile;
            GeneratedImage * generatedImage = new GeneratedImage(path, image);
            generatedImage->setGlobalImageName(globalImageName);
            generatedImage->setResourceName(resourceName);
            _generatedImageMap[key] = generatedImage;
            QImage mappedImage;
            QString mappedImageFile = _imagesPath + "/" + resourceName;
            if (mappedImage.load(mappedImageFile)) {
               QSize s1 = image.size();
               QSize s2 = mappedImage.size();
               generatedImage->setMappedImage(mappedImage);
               int dummy = 0;
            } else {
               int dummy = 0;
            }
         } else {
            int dummy = 0;
         }
      }
      qFile.close();
   }
}

void ImageInformations::savePersistentUnmatchedImages(const QString & path)
{
   QString file = path + "/" + "resolve.txt";
   QFile qFile(file);
   if (qFile.open(QIODevice::WriteOnly)) {
      QTextStream stream(&qFile);
      GENERATED_IMAGE_MAP_T::const_iterator i = _generatedImageMap.cbegin();
      while (i != _generatedImageMap.cend()) {
         GeneratedImage * generatedImage = (*i).second;
         stream << generatedImage->globalImageName();
         stream << ";";
         QString resourceName = generatedImage->resourceName();
         if (resourceName.isEmpty()) {
            resourceName = generatedImage->globalImageName();
//            resourceName = "unmatched.png";
         }
         stream << resourceName;
         endl(stream);
         i++;
      }
      qFile.close();
   }
}

bool ImageInformations::match(const QString & path, const QImage & image, QString & resourceName, QImage & matchedImage) const
{
   GENERATED_IMAGE_MAP_T::const_iterator i = _generatedImageMap.cbegin();
   while (i != _generatedImageMap.cend()) {
      GeneratedImage * generatedImage = (*i).second;
      if (_imageMatcher.match(image, (*i).second->image())) {
         resourceName = (*i).second->resourceName();
         if (resourceName.isEmpty()) {
            if (!_hasImages) {
               resourceName = (*i).second->globalImageName();
               matchedImage = (*i).second->image();
            } else {
               int dummy = 0;
            }
         } else {
            matchedImage = (*i).second->mappedImage();
         }
         return true;
      }
      i++;
   }
   return false;
}

void ImageInformations::storeUnmatchedImage(const QString & path, const QString & fileName, const QImage & image)
{
   QString file = path + "/" + fileName + ".png";
   bool success = image.save(file);
   if (success) {
      GeneratedImage * generatedImage = new GeneratedImage(path, image);
      generatedImage->setGlobalImageName(fileName + ".png");
      _generatedImageMap[file] = generatedImage;
      int dummy = 0;
   } else {
      int dummy = 0;
   }
}

QString ImageInformations::generatedImageName(int number) const
{
   return "generated_" + this->number(number);
}

bool ImageInformations::isPersistentImage(const QString & imageName, int & number) const
{
   QString head = imageName.left(10);
   QString tail = imageName.right(8);
   tail = tail.left(4);
   if (head == "generated_") {
      number = tail.toInt();
      return false;
   }
   return true;
}

QString ImageInformations::newGlobalImageName(const QString & path) const
{
   int globalImageIndex = 0;
   GENERATED_IMAGE_MAP_T::const_iterator i = _generatedImageMap.cbegin();
   while (i != _generatedImageMap.cend()) {
      GeneratedImage * generatedImage = (*i).second;
      const QString & globalImageName = generatedImage->globalImageName();
      globalImageIndex++;
      i++;
   }
   return generatedImageName(globalImageIndex);
}

QString ImageInformations::number(int n) const
{
   QString number;
   number.sprintf("%04.04d", n);
   return number;
}

QString ImageInformations::imageReferenceKey(const QString & formId, const QString & imageName) const
{
   QString key = imageName + "@" + formId;
   return key;
}

QString ImageInformations::storedImageKey(const QString & path, const QString & imageFile) const
{
   QString key = path + "/" + imageFile;
   return key;
}

