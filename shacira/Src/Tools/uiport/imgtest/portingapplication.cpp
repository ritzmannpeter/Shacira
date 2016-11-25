
#include "portingapplication.h"
#include "portingcontext.h"
#include "imageinformations.h"
#include <qtextstream.h>
#include <qbuffer.h>
#include <qimagewriter.h>
#include <iostream>

static void test()
{
return;
   bool success = false;
   QImage img1;
   success = img1.load("e:/temp/ctest4/i1.png");
   QImage img2;
   success = img2.load("e:/temp/ctest4/i2.png");
   ImageMatcher matcher;
   success = matcher.match(img1, img2);
   int dummy = 0;
   exit(0);
}

PortingApplication::PortingApplication(PortingContext * context, const QString name)
   : _context(context), _name(name)
{
   test();
   _applicationDirectory = QDir(append(context->homeDirectory().absolutePath(), name));
   _sourceDirectory = QDir(append(applicationDirectory().absolutePath(), context->sourceQtVersion()));
   _destinationDirectory = QDir(append(applicationDirectory().absolutePath(), context->destinationQtVersion()));
   _imageInformations = new ImageInformations(this);
   if (_imageInformations->hasNamedImages()) {
      loadImageMapFromFilesystem();
   } else {
      loadImageMap();
      loadImageInformationMap();
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
   FILE_MAP_T::const_iterator i = _fileMap.begin();
   while (i != _fileMap.end()) {
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
   // generate resource file
   IMAGE_MAP_T imageMap = _imageInformations->imageMap();
   IMAGE_MAP_T::const_iterator i;
   resourceFile.open(QIODevice::WriteOnly);
   if (resourceFile.isOpen()) {
      QTextStream textStream(&resourceFile);
      textStream << "<RCC>" << endl;
      textStream << "   <qresource prefix=" << "\"/" << name() << "\">" << endl;
      i = imageMap.begin();
      while (i != imageMap.end()) {
         Image * image = (*i).second;
         QString filePath = image->imageFilePath();
         std::map<QString,QString>::const_iterator p = pathMap.find(filePath);
         if (p == pathMap.end()) {
            textStream << "      <file>";
            textStream << filePath;
            textStream << "</file>" << endl;
            pathMap[filePath] = filePath;
         }
         i++;
      }
      textStream << "   </qresource>" << endl;
      textStream << "</RCC>" << endl;
      resourceFile.close();
   }
   // save image files
   QString content;
   QString imageTargetDirectory = IMAGES_DIRECTORY;
   if (imageInformations()->hasNamedImages()) {
      imageTargetDirectory = UNMATCHED_IMAGES_DIRECTORY;
   }
   int imageNumber = 0;
   i =  imageMap.begin();
   while (i != imageMap.end()) {
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
   // save image informations
   saveImageMap();
   saveImageInformationMap();
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
   if (i == _fileMap.end()) {
      file = new PortingFile(application, fileInfo);
      _fileMap[name] = file;
   } else {
      file = (*i).second;
   }
   return file;
}

// from qt 3 designer source qt/tools/designer/designer/resource.cpp
QImage PortingApplication::loadImageData(const QString & data, const QString & format)
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

// from qt 3 designer source qt/tools/designer/designer/resource.cpp
// adapted to Qt 4
int PortingApplication::imageData(const QImage & image, QString & imageData, QString & format)
{
   imageData.clear();
   int indent = 5;
   QByteArray ba;
   QBuffer buf(&ba);
   buf.open(QIODevice::WriteOnly /*| QIODevice::Translate*/);
   bool compress = false;
   if (image.hasAlphaChannel()) {
      format = "PNG";
   } else {
      format = image.depth() > 1 ? "XPM" : "XBM";
      compress = true;
   }
   QImageWriter iio(&buf, format.toStdString().c_str());
   iio.write(image);
   buf.close();
   QByteArray bazip = ba;
   int i = 0;
   if (compress) {
      bazip = qCompress(ba);
      format += ".GZ";
      // The first 4 bytes in qCompress() are the length of the unzipped
	   // format. The XPM.GZ format does not use these.
	   i = 4;
   }
   ulong len = bazip.size();
   static const char hexchars[] = "0123456789abcdef";
   for (; i < (int)len; ++i ) {
      uchar s = (uchar) bazip[i];
	   imageData += hexchars[s >> 4];
	   imageData += hexchars[s & 0x0f];
   }
   int length = imageData.length();
   return length;
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
   QFileInfoList::const_iterator i = fileInfoList.begin();
   while (i != fileInfoList.end()) {
      QString imageFileName = (*i).fileName();
      QString imageFile = (*i).absoluteFilePath();
      QString extension = (*i).suffix();
#ifdef lassma
      if (imageFileName.contains("img_")) {
         int dummy = 0;
      } else {
#endif
         if (extension.compare(extension, "png", Qt::CaseInsensitive) == 0) {
            QString imageName = (*i).baseName();
            QString formatSpecifier;
            QImage qImage;
            if (qImage.load(imageFile)) {
               cout <<  imageFile.toStdString() << " ..." << endl; 
               QString imageData;
               int length = this->imageData(qImage, imageData, formatSpecifier);
               Image * image = new Image(_imageInformations, imageName, imageData, formatSpecifier, relativePath);
               _imageInformations->addImage(image);
               int dummy = 0;
            } else {
               int dummy = 0;
            }
         } else if (extension.compare(extension, "bmp", Qt::CaseInsensitive) == 0) {
            int dummy = 0;
         } else if (extension.compare(extension, "xpm", Qt::CaseInsensitive) == 0) {
            int dummy = 0;
         }
#ifdef lassma
      }
#endif
      i++;
   }
   QFileInfoList subDirectoryList = directory.entryInfoList(QDir::Dirs);
   i = subDirectoryList.begin();
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
   imagesPath = imageInformations()->unmatchedImagesPath();
   cout << "loading image files from " << imagesPath.toStdString() << " ..." << endl; 
   loadImageMapFromFilesystem(QString(), imagesPath);
}

void PortingApplication::loadImageMap()
{
   QString resourcesPath = imageInformations()->resourcesPath();
   QString mapFilePath = append(resourcesPath, "imagemap.xml");
   QFile mapFile(mapFilePath);
   mapFile.open(QIODevice::ReadOnly);
   if (mapFile.isOpen()) {
      QDomDocument document;
      QString errorMessage;
      int errorLine = 0;
      int errorColumn = 0;
      if (document.setContent(&mapFile, &errorMessage, & errorLine, & errorColumn)) {
         QDomElement documentElement = document.documentElement();
         QDomNodeList children = documentElement.childNodes();
         int child_count = children.count();
         int i = 0;
         for (i=0; i<child_count; i++) {
            QDomNode node = children.item(i);
            QDomNode::NodeType nodeType = node.nodeType();
            if (nodeType = QDomNode::ElementNode) {
               QDomElement imageElement = node.toElement();
               QString tagName = imageElement.tagName();
               if (tagName == "Image") {
                  QString imageName = imageElement.attribute("imageName");
                  QString formatSpecifier = imageElement.attribute("formatSpecifier");
                  int size = imageElement.attribute("size").toInt();
                  QString imageData = getNodeValue(document, imageElement);
                  QString path = imageElement.attribute("path");
                  Image * image = new Image(_imageInformations, imageName, imageData, formatSpecifier, path);
                  imageInformations()->addImage(image);
               }
            }
         }
      }
      mapFile.close();
   }
}

void PortingApplication::saveImageMap()
{
   QString resourcesPath = append(destinationDirectory().absolutePath(), "qresources");
   QString mapFilePath = append(resourcesPath, "imagemap.xml");
   QDomDocument document("ImageMap");
   QDomProcessingInstruction processingInstruction = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
   document.appendChild(processingInstruction);
   QDomElement documentElement = document.createElement("Images");
   document.appendChild(documentElement);
   const IMAGE_MAP_T & imageMap = _imageInformations->imageMap();
   IMAGE_MAP_T::const_iterator i = imageMap.begin();
   while (i != imageMap.end()) {
      QDomElement imageElement = document.createElement("Image");
      QString key = (*i).first;
      Image * image = (*i).second;
      QStringList keyComponents = key.split(":");
      QString formName = keyComponents.first();
      QString imageName = keyComponents.last();
      QString formatSpecifier = image->formatSpecifier();
      int binarySize = image->binarySize();
      QString path = image->path();
      QString imageData = image->imageData();
      imageElement.setAttribute("imageName", imageName);
      imageElement.setAttribute("formatSpecifier", formatSpecifier);
      imageElement.setAttribute("size", binarySize);
      imageElement.setAttribute("path", path);
      setNodeValue(document, imageElement, imageData);
      documentElement.appendChild(imageElement);
      i++;
   }
   QByteArray xmlData = document.toByteArray();
   QFile mapFile(mapFilePath);
   mapFile.open(QIODevice::WriteOnly);
   if (mapFile.isOpen()) {
      QDataStream stream(&mapFile);
      int size = xmlData.length();
      const char * data = xmlData;
      int nwrite = stream.writeRawData(data, size);
      mapFile.close();
      if (nwrite == size) {
         int dummy = 0;
      } else {
         int dummy = 0;
      }
   } else {
      int dummy = 0;
   }
}

void PortingApplication::loadImageInformationMap()
{
   QString resourcesPath = append(destinationDirectory().absolutePath(), "qresources");
   QString mapFilePath = append(resourcesPath, "imageinformationmap.xml");
   QFile mapFile(mapFilePath);
   mapFile.open(QIODevice::ReadOnly);
   if (mapFile.isOpen()) {
      QDomDocument document;
      QString errorMessage;
      int errorLine = 0;
      int errorColumn = 0;
      if (document.setContent(&mapFile, &errorMessage, & errorLine, & errorColumn)) {
         QDomElement documentElement = document.documentElement();
         QDomNodeList children = documentElement.childNodes();
         int child_count = children.count();
         int i = 0;
         for (i=0; i<child_count; i++) {
            QDomNode node = children.item(i);
            QDomNode::NodeType nodeType = node.nodeType();
            if (nodeType = QDomNode::ElementNode) {
               QDomElement imageElement = node.toElement();
               QString tagName = imageElement.tagName();
               if (tagName == "ImageReference") {
                  QString formId = imageElement.attribute("formId");
                  QString imageName = imageElement.attribute("imageName");
                  QString globalImageName = imageElement.attribute("globalImageName");
                  _imageInformations->addImageInformation(formId, imageName, globalImageName);
               }
            }
         }
      }
      mapFile.close();
   }
}

void PortingApplication::saveImageInformationMap()
{
   QString resourcesPath = append(destinationDirectory().absolutePath(), "qresources");
   QString mapFilePath = append(resourcesPath, "imageinformationmap.xml");
   QDomDocument document("ImageInformationMap");
   QDomProcessingInstruction processingInstruction = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
   document.appendChild(processingInstruction);
   QDomElement documentElement = document.createElement("ImageReferences");
   document.appendChild(documentElement);
   const IMAGE_INFORMATION_MAP_T & imageInformationMap = _imageInformations->imageInformationMap();
   IMAGE_INFORMATION_MAP_T::const_iterator i = imageInformationMap.begin();
   while (i != imageInformationMap.end()) {
      QDomElement imageElement = document.createElement("ImageReference");
      QString key = (*i).first;
      ImageInformation * imageInfo = (*i).second;
      QString formId = imageInfo->formId();
      QString imageName = imageInfo->imageName();
      QString globalImageName = imageInfo->globalImageName();
      QString imageData = imageInfo->imageData();
      imageElement.setAttribute("formId", formId);
      imageElement.setAttribute("imageName", imageName);
      imageElement.setAttribute("globalImageName", globalImageName);
      documentElement.appendChild(imageElement);
      i++;
   }
   QByteArray xmlData = document.toByteArray();
   QFile mapFile(mapFilePath);
   mapFile.open(QIODevice::WriteOnly);
   if (mapFile.isOpen()) {
      QDataStream stream(&mapFile);
      int size = xmlData.length();
      const char * data = xmlData;
      int nwrite = stream.writeRawData(data, size);
      mapFile.close();
      if (nwrite == size) {
         int dummy = 0;
      } else {
         int dummy = 0;
      }
   } else {
      int dummy = 0;
   }
}

void PortingApplication::printInvalidProperties()
{
   QString invalidPropertiesPath = append(destinationDirectory().absolutePath(), "invalidproperties.txt");
   QFile invalidPropertyFile(invalidPropertiesPath);
   invalidPropertyFile.open(QIODevice::WriteOnly | QIODevice::Text);
   if (invalidPropertyFile.isOpen()) {
      INVALID_PROPERTY_MAP_T::const_iterator i = _invalidPropertyMap.begin();
      while (i != _invalidPropertyMap.end()) {
         QTextStream stream(&invalidPropertyFile);
         stream << (*i).second.propertyName() << " in " <<  (*i).second.widgetName() << " in " << (*i).second.path() << endl;
         i++;
      }
      invalidPropertyFile.close();
   } else {
      int dummy = 0;
   }
}

