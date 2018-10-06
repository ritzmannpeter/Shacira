#include "portingapplication.h"
#include "portingcontext.h"
#include "imageinformations.h"
#include <qtextstream.h>
#include <qbuffer.h>
#include <qimagewriter.h>
#include <iostream>

PortingApplication::PortingApplication(PortingContext * context, const QString name)
   : _context(context), _name(name)
{
   _applicationDirectory = QDir(append(context->homeDirectory().absolutePath(), name));
   _sourceDirectory = QDir(append(applicationDirectory().absolutePath(), context->sourceQtVersion()));
   _destinationDirectory = QDir(append(applicationDirectory().absolutePath(), context->destinationQtVersion()));
   _imageInformations = new ImageInformations(this);
   if (_imageInformations->hasImages()) {
      loadImageMapFromFilesystem();
   }
}

PortingApplication::~PortingApplication()
{
   delete _imageInformations;
}

void PortingApplication::collectFiles()
{
   collectFiles(sourceDirectory());
}

void PortingApplication::portFiles()
{
   FILE_MAP_T::const_iterator i = _fileMap.cbegin();
   while (i != _fileMap.cend()) {
      PortingFile * file = (*i).second;
      file->portFile();
      i++;
   }
}

void PortingApplication::generateResources()
{
   std::map<QString,QString> pathMap;
   QString resourceFileName = imageInformations()->resourceFileName();
   QString resourcesPath = imageInformations()->resourcesPath();
   QString imagesPath = imageInformations()->imagesPath();
   QString resourceFilePath = append(resourcesPath, resourceFileName);
   QFile resourceFile(resourceFilePath);
   resourceFile.open(QIODevice::WriteOnly);
   if (resourceFile.isOpen()) {
      QTextStream textStream(&resourceFile);
      textStream << "<RCC>" << endl;
      textStream << "   <qresource prefix=" << "\"/" << name() << "\">" << endl;
      if (_imageInformations->hasImages()) {
         const IMAGE_REFERENCE_MAP_T & imageReferenceMap = _imageInformations->imageRefrenceMap();
         IMAGE_REFERENCE_MAP_T::const_iterator i = imageReferenceMap.cbegin();
         while (i != imageReferenceMap.cend()) {
            const ImageReference * imageReference = (*i).second;
            QString resourceName = imageReference->resourceName();
            if (resourceName.isEmpty()) {
               int dummy = 0;
            } else {
               QString path = "images/" + resourceName;
               std::map<QString,QString>::const_iterator p = pathMap.find(path);
               if (p == pathMap.cend()) {
                  textStream << "      <file>";
                  textStream << path;
                  textStream << "</file>" << endl;
                  pathMap[path] = path;
               }
            }
            i++;
         }
      } else {
         const GENERATED_IMAGE_MAP_T & generatedImageMap = _imageInformations->generatedImageMap();
         GENERATED_IMAGE_MAP_T::const_iterator i = generatedImageMap.cbegin();
         while (i != generatedImageMap.cend()) {
            const GeneratedImage * generatedImage = (*i).second;
            QString resourceName = generatedImage->globalImageName();
            QString path = "images/" + resourceName;
            textStream << "      <file>";
            textStream << path;
            textStream << "</file>" << endl;
            i++;
         }
      }
      textStream << "   </qresource>" << endl;
      textStream << "</RCC>" << endl;
      resourceFile.close();
   }
#ifdef lassma
   // save image files
   QString content;
   QString imageTargetDirectory = IMAGES_DIRECTORY;
   if (imageInformations()->hasNamedImages()) {
      imageTargetDirectory = UNMATCHED_IMAGES_DIRECTORY;
   }
   int imageNumber = 0;
   i =  imageMap.begin();
   while (i != imageMap.cend()) {
      Image * image = (*i).second;
      QImage qImage = image->qImage();
      QString path = append(resourcesPath, image->imageFilePath());
      if (path.contains("img_")) {
         int pos = path.indexOf(IMAGES_DIRECTORY);
         if (pos >= 0) {
            path.replace(pos, strlen(IMAGES_DIRECTORY), imageTargetDirectory);
         }
         if (!qImage.isNull()) {
            if (qImage.save(path)) {
               int dummy = 0;
            } else {
               int dummy = 0;
            }
         } else {
            int dummy = 0;
         }
      } else {
         if (imageInformations()->hasNamedImages()) {
            if (!image->qt3UiImage().isNull()) {
               if (imageInformations()->hasNamedImages()) {
                  int pos = path.indexOf(IMAGES_DIRECTORY);
                  if (pos >= 0) {
                     path.replace(pos, strlen(IMAGES_DIRECTORY), MATCHED_IMAGES_DIRECTORY);
                  }
                  QString targetPath = append(resourcesPath, MATCHED_IMAGES_DIRECTORY);
                  QString numberSpec;
                  numberSpec.sprintf("%03d", imageNumber);
                  QString image1File = append(targetPath, "i_" + numberSpec + ".png");
                  QString image2File = append(targetPath, "i_" + numberSpec + "_.png");
                  if (!qImage.isNull()) {
                     if (qImage.save(image1File)) {
                        qImage = image->qt3UiImage();
                        if (qImage.save(image2File)) {
                           QString imageSpec = "i_" + numberSpec + ".png";
                           QString imagePath = append(image->path(), image->imageName() + ".png");
                           content += imageSpec;
                           content += " : ";
                           content += imagePath;
                           content += "\n";
                        } else {
                           int dummy = 0;
                        }
                     } else {
                        int dummy = 0;
                     }
                  } else {
                     int dummy = 0;
                  }
               }
            }
         }
         imageNumber++;
      }
      i++;
   }
   QString matchedCommentPath;
   if (imageInformations()->hasNamedImages()) {
      matchedCommentPath = imageInformations()->matchedImagesPath();
      matchedCommentPath = append(matchedCommentPath, "matchedimages.txt");
      QFile matchedCommentFile(matchedCommentPath);
      if (matchedCommentFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
         matchedCommentFile.write(content.toStdString().c_str(), content.length());
      } else {
         int dummy = 0;
      }
   }
#endif
   printInvalidProperties();
}

void PortingApplication::printFormHeaderInformations()
{
   QString path = destinationDirectory().absolutePath();
   _formInformations.printHeaderInformations(path);
}

void PortingApplication::addSourceFile(const QFileInfo & fileInfo)
{
   PortingFile * portingFile = new PortingFile(this, fileInfo);
//   _fileMap[portingFile->name()] = portingFile;
   // allows "ui overloading"
   _fileMap[portingFile->sourcePath()] = portingFile;
}

void PortingApplication::addFormInfo(PortingFile * file, const QString & formClass, const QString & baseClass, const QString & uiClassName, const QString & classCode)
{
   _formInformations.addFormInfo(file->destinationPath(), formClass, baseClass, uiClassName, classCode);
}

void PortingApplication::addInvalidProperty(PortingFile * file, const QString & propertyName, const QString & widgetName)
{
   QString path = file->destinationPath();
   InvalidProperty p(path, propertyName, widgetName);
   QString key = p.key();
   _invalidPropertyMap[key] = p;
}

PortingFile * PortingApplication::file(PortingApplication * application, const QFileInfo & fileInfo)
{
   PortingFile * file = NULL;
   QString name = fileInfo.baseName();
   FILE_MAP_T::const_iterator i = _fileMap.find(name);
   if (i == _fileMap.cend()) {
      file = new PortingFile(application, fileInfo);
      _fileMap[name] = file;
   } else {
      file = (*i).second;
   }
   return file;
}

bool PortingApplication::removeDirectory(const QString & path)
{
   QDir directory(path);
   QStringList entryList = directory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString directoryName = *it;
      if (directoryName[0] != '.') {
         QString subDirectoryPath = append(directory.absolutePath(), directoryName);
         if (!removeDirectory(subDirectoryPath)) {
            return false;
         } else {
            if (!directory.rmdir(directoryName)) {
               return false;
            }
         }
      }
   }
   entryList = directory.entryList(QDir::Files);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = *it;
      QString subDirectoryPath = append(directory.absolutePath(), fileName);
      if (!directory.remove(fileName)) {
         return false;
      }
   }
   return true;
}

void PortingApplication::collectFiles(const QDir & directory)
{
   QString directoryPath = directory.absolutePath();
   QStringList entryList = directory.entryList(_context->filePatterns(), QDir::Files);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString fileName = (*it);
      QFileInfo fileInfo(append(directoryPath, fileName));
      addSourceFile(fileInfo);
   }
   entryList = directory.entryList(QDir::Dirs);
   for (QStringList::Iterator it = entryList.begin(); it != entryList.end(); ++it) {
      QString subDirectoryName = (*it);
      if (!subDirectoryName.isEmpty() &&
           subDirectoryName[0] != '.') {
         QDir subDirectory(append(directoryPath, subDirectoryName));
         QString directoryPath = subDirectory.absolutePath();
         collectFiles(subDirectory);
         int dummy = 0;
      }
   }
}

#include <qdom.h>

static void setNodeValue(QDomDocument document, QDomNode node, const QString & value)
{
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   if (child_count == 0) {
      QDomText text = document.createTextNode(value);
      text.setNodeValue(value);
      node.appendChild(text);
   }
}

static QString getNodeValue(QDomDocument document, QDomNode node)
{
   QString value;
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   int i = 0;
   for (i=0; i<child_count; i++) {
      QDomNode node = children.item(i);
      QString nodeName = node.nodeName();
      if (nodeName == "#text") {
         value = node.nodeValue();
      } else if (nodeName == "#cdata-section") {
         value = node.nodeValue();
      }
   }
   return value;
}

void PortingApplication::loadImageMapFromFilesystem(const QString & relativePath, const QString & path)
{
   QDir directory(path);
   QStringList filePatterns;
   filePatterns << "*.png";
   filePatterns << "*.bmp";
   QFileInfoList fileInfoList = directory.entryInfoList(filePatterns);
   QFileInfoList::const_iterator i = fileInfoList.constBegin();
   while (i != fileInfoList.constEnd()) {
      QString imageFileName = (*i).fileName();
      QString imageFile = (*i).absoluteFilePath();
      QString extension = (*i).suffix();
      if (imageFileName.contains("img_")) {
         int dummy = 0;
      } else {
         _imageInformations->addStoredImage(imageFile, relativePath, imageFileName);
      }
      i++;
   }
   QFileInfoList subDirectoryList = directory.entryInfoList(QDir::Dirs);
   i = subDirectoryList.constBegin();
   while (i != subDirectoryList.end()) {
      bool ignore = false;
      QString directoryName = (*i).fileName();
      if (!directoryName.isEmpty() &&
          directoryName[0] == '.') {
         ignore = true;
      }
      if (!ignore) {
         QString subDirectoryPath = append(directory.absolutePath(), directoryName);
         loadImageMapFromFilesystem(append(relativePath, directoryName), subDirectoryPath);
      }
      i++;
   }
}

void PortingApplication::loadImageMapFromFilesystem()
{
   QString imagesPath = imageInformations()->imagesPath();
   cout << "loading image files from " << imagesPath.toStdString() << " ..." << endl; 
   loadImageMapFromFilesystem(QString(), imagesPath);
}

void PortingApplication::printInvalidProperties()
{
   QString invalidPropertiesPath = append(destinationDirectory().absolutePath(), "invalidproperties.txt");
   QFile invalidPropertyFile(invalidPropertiesPath);
   invalidPropertyFile.open(QIODevice::WriteOnly | QIODevice::Text);
   if (invalidPropertyFile.isOpen()) {
      INVALID_PROPERTY_MAP_T::const_iterator i = _invalidPropertyMap.cbegin();
      while (i != _invalidPropertyMap.cend()) {
         QTextStream stream(&invalidPropertyFile);
         stream << (*i).second.propertyName() << " in " <<  (*i).second.widgetName() << " in " << (*i).second.path() << endl;
         i++;
      }
      invalidPropertyFile.close();
   } else {
      int dummy = 0;
   }
}

