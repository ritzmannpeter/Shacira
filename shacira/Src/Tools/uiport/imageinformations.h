
#ifndef _imageinformations_h_
#define _imageinformations_h_

#include "imagematcher.h"
#include "imageinformation.h"

class PortingApplication;
class PortingFile;

#define RESOURCES_DIRECTORY         "qresources"
#define IMAGES_DIRECTORY            "images"
#define MATCHED_IMAGES_DIRECTORY    "images.matched"
#define UNMATCHED_IMAGES_DIRECTORY  "images.unmatched"
#define UNMATCHED_PERSISTENT_IMAGES_DIRECTORY  "unmatched_images"

class ImageInformations
{
public:
   ImageInformations(PortingApplication * application);
   virtual ~ImageInformations();
   QString resourceFileName() const;
   QString resourceFileReference(PortingFile * portingFile) const;
   QString resourceString(const QString & formId, const QString & imageName) const;
   inline PortingApplication * application() const {return _application;};
   inline QString resourcesPath() const {return _resourcesPath;};
   inline QString imagesPath() const {return _imagesPath;};
   inline QString matchedImagesPath() const {return _matchedImagesPath;};
   inline QString unmatchedImagesPath() const {return _unmatchedImagesPath;};
   const STORED_IMAGE_MAP_T & storedImageMap() const {return _storedImageMap;};
   const IMAGE_REFERENCE_MAP_T & imageRefrenceMap() const {return _imageReferenceMap;};
   const GENERATED_IMAGE_MAP_T & generatedImageMap() const {return _generatedImageMap;};
   bool addImageReference(const QString & formId, const QString & imageName, const QString & imageData, const QString & imageFormat, int imageLength);
   bool addStoredImage(const QString & absolutePath, const QString & relativePath, const QString & imageFile);
   inline bool hasImages() const {return _hasImages;};
protected:
   void initialize();
   bool checkForPersistentImages(const QString & path) const;
   void loadPersistentUnmatchedImages(const QString & path);
   void savePersistentUnmatchedImages(const QString & path);
   bool match(const QString & path, const QImage & image, QString & resourceName, QImage & matchedImage) const;
   void storeUnmatchedImage(const QString & path, const QString & fileName, const QImage & image);
   QString generatedImageName(int number) const;
   bool isPersistentImage(const QString & imageName, int & number) const;
   QString newGlobalImageName(const QString & path) const;
   QString number(int n) const;
   QString imageReferenceKey(const QString & formId, const QString & imageName) const;
   QString storedImageKey(const QString & formId, const QString & imageName) const;
protected:
   QString _destinationPath;
   ImageMatcher _imageMatcher;
   PortingApplication * _application;
   QString _resourcesPath;
   QString _imagesPath;
   QString _matchedImagesPath;
   QString _unmatchedImagesPath;
   QString _unmatchedPersistentImagesPath;
   STORED_IMAGE_MAP_T _storedImageMap;
   IMAGE_REFERENCE_MAP_T _imageReferenceMap;
   GENERATED_IMAGE_MAP_T _generatedImageMap;
   bool _hasImages;
};

#endif // _imageinformations_h_
