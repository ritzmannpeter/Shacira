
#include "uiport.h"
#include "options.h"
#include <qdatastream.h>
#include <iostream>
#include "cformbuilder.h"
#include "portingfile.h"
#include "portingapplication.h"
#include "imageinformations.h"

class Colors
{
public:
   Colors()
      : _widget(NULL)
   {
   };
   inline void setWidget(QWidget * widget) {_widget = widget;};
   inline QColor foregroundColor() const {return _foregroundColor;};
   inline QColor backgroundColor() const {return _backgroundColor;};
   inline void setForegroundColor(const QColor & value) {_foregroundColor = value;};
   inline void setBackgroundColor(const QColor & value) {_backgroundColor = value;};
   inline bool isEmpty() const {return !(_backgroundColor.isValid() || _foregroundColor.isValid());};
   inline QPalette::ColorRole foregroundRole() const
   {
      if (_widget->inherits("QLineEdit") || 
          _widget->inherits("QTextEdit") ||
          _widget->inherits("QComboBox")) {
         return QPalette::Text;
      } else {
         return QPalette::WindowText;
      }
   };
   inline QPalette::ColorRole backgroundRole() const
   {
      if (_widget->inherits("QLineEdit") || 
          _widget->inherits("QTextEdit") ||
          _widget->inherits("QComboBox")) {
         return QPalette::Base;
      } else {
         return QPalette::Window;
      }
   };
   static QString roleText(QPalette::ColorRole role)
   {
      QString text = "?";
      switch (role) {
      case QPalette::Text:
         text = "Text";
         break;
      case QPalette::WindowText:
         text = "WindowText";
         break;
      case QPalette::Base:
         text = "Base";
         break;
      case QPalette::Window:
         text = "Window";
         break;
      }
      return text;
   };
private:
   QColor _foregroundColor;
   QColor _backgroundColor;
   QWidget * _widget;
};

bool UiPort::port(PortingFile * file)
{
   Colors * colors = NULL;
   _formBuilder.initialize();
   _currentFormId = file->logicPath();
   _spacerNameIndex = 0;
   _widgetNameIndex = 0;
   _wizardPageIndex = 1;
   clearClassMap();
   clearNameMap();
   QString inputFile = file->intermediatePath();
   QString outputFile = file->destinationPath();
   QString formId = file->logicPath();
   cout << file->name().toStdString() << " ..." << endl;
   LogPrintf(logFileName(), "porting from %s to %s\n", inputFile.toStdString().c_str(), outputFile.toStdString().c_str());
   QFile qFile(inputFile);
   QDomDocument document;
   QString errorMsg;
   int errorLine = 0;
   int errorColumn = 0;
   bool success = document.setContent(&qFile, false, &errorMsg, &errorLine, &errorColumn);
   if (success) {
      _steps = 1;
      _step = UI4Transformation;
      QDomElement documentElement = document.documentElement();
      if (collectImages(document, documentElement, formId, file)) {
         if (evaluate(document, documentElement, file, QString(), QString(), NULL, colors)) {
            addCustomWidgetRefs(document, documentElement, "ui");
// no more used HA 07.01.2014
//            addIncludes(document, documentElement, "ui");
            addResources(document, documentElement, file->application()->imageInformations()->resourceFileReference(file));
            _updateList.update();
            _updateList.clear();
            if (_steps == 2) {
               _spacerNameIndex = 0;
               _widgetNameIndex = 0;
               _wizardPageIndex = 1;
               clearClassMap();
               clearNameMap();
               _step = PartialTransformation;
               evaluate(document, documentElement, file, QString(), QString(), NULL, colors);
               _updateList.update();
               _updateList.clear();
            }
            if (printDocument(document, outputFile)) {
               LogPrintf(logFileName(), "generated %s\n", outputFile.toStdString().c_str());
               addFormHeader(document, file);
               return true;
            } else {
               LogPrintf(logFileName(), "failed to generate %s\n", outputFile.toStdString().c_str());
               return false;
            }
         } else {
            LogPrintf(logFileName(), "failed to evaluate %s\n", inputFile.toStdString().c_str());
            return false;
         }
      } else {
         LogPrintf(logFileName(), "failed to collect images of %s\n", inputFile.toStdString().c_str());
         return false;
      }
   } else {
      LogPrintf(logFileName(), "failed to parse contents of %s\n", inputFile.toStdString().c_str());
      return false;
   }
}

bool UiPort::printDocument(QDomDocument document, const QString & outputFile)
{
   QFileInfo fileInfo(outputFile);
   QDir directory = fileInfo.absoluteDir();
   QString directoryPath = directory.absolutePath();
   directory.mkpath(directoryPath);
   QByteArray xmlData = document.toByteArray();
   QFile qFile(outputFile);
   qFile.open(QIODevice::WriteOnly);
   if (qFile.isOpen()) {
      QDataStream stream(&qFile);
      int size = xmlData.length();
      const char * data = xmlData;
      int nwrite = stream.writeRawData (data, size);
      qFile.close();
      if (nwrite == size) {
         return true;
      } else {
         LogPrintf(logFileName(), "failed to generate document %s\n", outputFile.toStdString().c_str());
         return false;
      }
   } else {
      LogPrintf(logFileName(), "failed to open document file %s\n", outputFile.toStdString().c_str());
      return false;
   }
}

QString UiPort::handleGroupBoxes(QDomDocument document, QDomNode node, const QString & widgetClass)
{
   QString targetClass;
   bool isGroupBox = false;
   if (widgetClass == "CGroupBox") {
      isGroupBox = true;
   }
   if (widgetClass == "Q3GroupBox") {
      isGroupBox = true;
   }
   if (isGroupBox) {
      bool replaceByFrame = false;
      QDomElement shapeElement = this->propertyElement(document, node, "frameShape");
      if (!shapeElement.isNull()) {
         QString value = propertyValue(shapeElement).toString();
         if (value.indexOf("NoFrame") != -1) {
            replaceByFrame = true;
         }
      }
      if (replaceByFrame) {
         if (widgetClass == "CGroupBox") {
            targetClass = "CFrame";
         }
         if (widgetClass == "Q3GroupBox") {
            targetClass = "QFrame";
         }
         if (!shapeElement.isNull()) {
            removeNode(document, node, shapeElement, true);
         }
         addProperty(document, node, "frameShape", "enum", "NoFrame");
         QDomElement shadowElement = this->propertyElement(document, node, "frameShadow");
         if (!shadowElement.isNull()) {
            removeNode(document, node, shadowElement, true);
         }
/* no shadow specified in case of no frame
         addProperty(document, node, "frameShadow", "enum", "QFrame::Plain");
         QDomElement titleElement = this->propertyElement(document, node, "title");
         if (!titleElement.isNull()) {
            removeNode(document, node, titleElement, true);
         }
*/
      }
   }
   return targetClass;
}

#ifdef doku
 <class>Tmp_Overview</class>
 <widget class="CPage" name="Tmp_Overview">
#include "dialog.h"
#include "ui_diag_adjustmentpowerlinkinfodialog.h"
class Diag_AdjustmentPowerLinkInfoDialog : public Dialog<Ui_Diag_AdjustmentPowerLinkInfoDialog>
{
   inline Diag_AdjustmentPowerLinkInfoDialog(QWidget* parent = 0, const char* name = 0)
      : Dialog(parent, name)
   {
   };
   virtual ~Diag_AdjustmentPowerLinkInfoDialog()
   {
   };
}
#endif

#define CLASS_TEMPLATE1 \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
   inline cname(QWidget* parent = 0, const char* name = 0)\r\n\
      : bname(parent, name)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define PAGE_TEMPLATE \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
   inline cname(QWidget* parent = 0, const char* name = 0)\r\n\
      : bname(parent, name)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define APPFRAME_TEMPLATE \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
   inline cname(QWidget* parent = 0, const char* name = 0)\r\n\
      : bname(parent, name)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define STARTUPFORM_TEMPLATE \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
   inline cname(QWidget* parent = 0, const char* name = 0)\r\n\
      : bname(parent, name)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define DIALOG_TEMPLATE \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
inline cname(QWidget* parent = 0, const char* name = 0, bool modal = true, Qt::WindowFlags flags = 0)\r\n\
      : bname(parent, name, modal, flags)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define ACTIONDIALOG_TEMPLATE \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
   inline cname(QWidget* parent = 0, const char* name = 0)\r\n\
      : bname(parent, name)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define WIZARD_TEMPLATE \
"class cname : public bname<uiname>\r\n\
{\r\n\
public:\r\n\
inline cname(QWidget* parent = 0, const char* name = 0, bool modal = true, Qt::WindowFlags flags = 0)\r\n\
      : bname(parent, name, modal, flags)\r\n\
   {\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

#define GENERAL_TEMPLATE \
"class cname : public bname\r\n\
{\r\n\
public:\r\n\
   inline cname(QWidget* parent = 0, const char* name = 0)\r\n\
      : bname(parent)\r\n\
   {\r\n\
      if (name) {\r\n\
         setObjectName(name);\r\n\
      }\r\n\
   };\r\n\
   virtual ~cname()\r\n\
   {\r\n\
   };\r\n\
};\r\n"

void UiPort::addFormHeader(QDomDocument document, PortingFile * file)
{
   QString formClass;
   QString widgetClass;
   QDomElement documentElement = document.documentElement();
   QDomNodeList nodeList = documentElement.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      QString tagName = "node";
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         tagName = child.tagName();
         if (tagName == "class") {
            formClass = getNodeValue(child);
         } else if (tagName == "widget") {
            widgetClass = child.attribute("class");
         }
      }
   }
   QString classCode = CLASS_TEMPLATE1;
   QString baseClass;
   if (widgetClass == "QWizard") {
      classCode = WIZARD_TEMPLATE;
      baseClass = "Wizard";
   } else if (widgetClass == "QDialog") {
      classCode = DIALOG_TEMPLATE;
      baseClass = "Dialog";
   } else if (widgetClass == "CPage") {
      classCode = PAGE_TEMPLATE;
      baseClass = "Page";
   } else if (widgetClass == "CActionDialog") {
      classCode = ACTIONDIALOG_TEMPLATE;
      baseClass = "ActionDialog";
   } else if (widgetClass == "CAppFrame") {
      classCode = APPFRAME_TEMPLATE;
      baseClass = "AppFrame";
   } else if (widgetClass == "CStartupForm") {
      classCode = STARTUPFORM_TEMPLATE;
      baseClass = "StartupForm";
   } else {
      classCode = GENERAL_TEMPLATE;
      baseClass = widgetClass;
   }
   QString destinationDirectory = file->destinationDirectory();
   QString uiName = "Ui_" + formClass;
   QString includeStatement = "#include \"" + uiName.toLower() + ".h\"\r\n";
   classCode = replaceAll(classCode, "cname", formClass);
   classCode = replaceAll(classCode, "bname", baseClass);
   classCode = replaceAll(classCode, "uiname", uiName);
   classCode = includeStatement + classCode;
   file->application()->addFormInfo(file, formClass, baseClass, uiName, classCode);
}

void UiPort::registerWidgetClass(const QString & widgetClass)
{
   _widgetClassMap[widgetClass] = widgetClass;
   QString superClass = pluginSuperClass(widgetClass);
   if (!superClass.isEmpty() && superClass[0] != 'Q') {
      registerWidgetClass(superClass);
   }
}

bool UiPort::evaluate(QDomDocument document, QDomNode parentNode, PortingFile * file, const QString & targetWidgetClass, const QString & parentWidgetClass, QWidget * widget, Colors * colors)
{
   bool isWidgetNode = false;
   PortingApplication * application = file->application();
   ImageInformations * imageInformations = application->imageInformations();
   QString formId = file->logicPath();
   QString targetClass = targetWidgetClass;
   QString parentClass = targetWidgetClass;
   QWidget * targetWidget = widget;
   QDomNodeList nodeList = parentNode.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   bool nodeRemoved = false;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      QString tagName = "node";
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         tagName = child.tagName();
         if (tagName == "class") {
         } else if (tagName == "widget") {
            isWidgetNode = true;
            colors = new Colors;
            QString widgetClass = child.attribute("class");
            QString widgetName = child.attribute("name");
            if (strnicmp(widgetName.toStdString().c_str(), "WizardPage", 10) == 0) {
               widgetName = "WizardPage";
               if (_wizardPageIndex > 1) {
                  widgetName += "_";
                  widgetName += QString::number(_wizardPageIndex);
               }
               _wizardPageIndex++;
               child.setAttribute("name", widgetName);
            } else {
               if (widgetNameExists(widgetName)) {
                  widgetName += "_";
                  widgetName += QString::number(_widgetNameIndex++);
                  child.setAttribute("name", widgetName);
               }
            }
            targetClass = handleGroupBoxes(document, child, widgetClass);
            if (targetClass.isEmpty()) {
               targetClass = this->targetClass(parentClass, widgetClass, file);
            }
            _widgetNameMap[widgetName] = targetClass;
            child.setAttribute("class", targetClass);
            registerWidgetClass(targetClass);
            if (targetClass == "CUnported") {
               addProperty(document, child, "originalClass", "cstring", widgetClass);
            }
            if (targetClass == "QWizard") {
               _steps = 2;
               addProperty(document, child, "wizardStyle", "enum", "ClassicStyle");
               adjustWidgetGeometry(document, child, -1, -1, 10, 35);
            }
            if (targetClass == "QWizardPage") {
               adjustWizardPage(document, parentNode, child);
            }
            if (widgetClass == "CPage") {
               addProperty(document, node, "autoFillBackground", "bool", "true");
            }
            targetWidget = _formBuilder.createWidget(targetClass);
            if (targetWidget != NULL) {
               targetWidget->setObjectName(widgetName.toStdString().c_str());
            }
         } else if (tagName == "property") {
            handleProperty(document, parentNode, child, parentClass, targetClass, targetWidget, file, colors);
         } else if (tagName == "QString") {
         } else if (tagName == "string") {
         } else if (tagName == "cstring") {
         } else if (tagName == "size") {
         } else if (tagName == "x") {
         } else if (tagName == "y") {
         } else if (tagName == "width") {
         } else if (tagName == "height") {
         } else if (tagName == "hsizetype") {
         } else if (tagName == "sizepolicy") {
         } else if (tagName == "vsizetype") {
         } else if (tagName == "horstretch") {
         } else if (tagName == "verstretch") {
         } else if (tagName == "color") {
         } else if (tagName == "red") {
         } else if (tagName == "green") {
         } else if (tagName == "blue") {
         } else if (tagName == "rect") {
         } else if (tagName == "images") {
         } else if (tagName == "image") {
         } else if (tagName == "connections") {
         } else if (tagName == "connection") {
            adjustConnection(document, child);
         } else if (tagName == "layoutdefaults") {
         } else if (tagName == "includehints") {
         } else if (tagName == "includehint") {
         } else if (tagName == "enum") {
         } else if (tagName == "set") {
         } else if (tagName == "data") {
         } else if (tagName == "pixmap") {
            QString imageName = getNodeValue(child);
            QDomElement propertyElement = parentNode.toElement();
            if (!propertyElement.isNull()) {
               if (propertyElement.attribute("name") != "paletteBackgroundPixmap") {
                  QString resourceFileName = imageInformations->resourceFileReference(file);
                  QString resourceString = imageInformations->resourceString(formId, imageName);
                  child.setAttribute("resource", resourceFileName);
                  setNodeValue(document, child, resourceString);
               } else {
                  // paletteBackgroundPixmap is handled in property evaluation
                  int dummy = 0;
               }
            }
         } else if (tagName == "bool") {
         } else if (tagName == "font") {
         } else if (tagName == "family") {
         } else if (tagName == "pointsize") {
         } else if (tagName == "palette") {
         } else if (tagName == "active") {
         } else if (tagName == "inactive") {
         } else if (tagName == "disabled") {
         } else if (tagName == "number") {
         } else if (tagName == "hbox") {
         } else if (tagName == "vbox") {
         } else if (tagName == "attribute") {
            if (targetWidgetClass == "QWizardPage") {
               child.setTagName("property");
            }
         } else if (tagName == "iconset") {
         } else if (tagName == "signal") {
         } else if (tagName == "slot") {
         } else if (tagName == "sender") {
         } else if (tagName == "receiver") {
         } else if (tagName == "grid") {
         } else if (tagName == "spacer") {
         } else if (tagName == "item") {
         } else if (tagName == "author") {
         } else if (tagName == "comment") {
         } else if (tagName == "exportmacro") {
         } else if (tagName == "layout") {
            adjustLayout(document, child, targetClass);
         } else if (tagName == "layoutdefault") {
         } else if (tagName == "includes") {
         } else if (tagName == "include") {
         } else if (tagName == "bold") {
         } else if (tagName == "customwidgets") {
         } else if (tagName == "customwidget") {
         } else if (tagName == "extends") {
         } else if (tagName == "tabstops") {
         } else if (tagName == "tabstop") {
         } else if (tagName == "double") {
         } else if (tagName == "cursor") {
         } else if (tagName == "stringlist") {
         } else if (tagName == "pixmapfunction") {
         } else if (tagName == "column") {
         } else if (tagName == "includes") {
         } else if (tagName == "ui") {
         } else {
            if (_step == UI4Transformation) {
               // this code is already transformed by uiport
               // ignore unknown tags
               LogPrintf(file->errorPath().toStdString(), "error: unknown tag %s\n", tagName.toStdString().c_str());
               LogPrintf(logFileName(), "error: unknown tag %s in %s\n", tagName.toStdString().c_str(), formId.toStdString().c_str());
            }
         }
      }
      if (nodeFilter(document, parentNode, node, tagName)) {
         if (removeNode(document, parentNode, node)) {
            QString parentName = parentNode.nodeName();
            QString nodeName = node.nodeName();
            int dummy = 0;
         }
      }
      bool success = evaluate(document, node, file, targetClass, parentClass, targetWidget, colors);
      if (isWidgetNode) {
         if (colors != NULL) {
            if (!colors->isEmpty()) {
               // add palette
               addPaletteElement(document, node, colors);
            }
            delete colors;
            colors = NULL;
         }
      }
   }
   return true;
}

QString UiPort::targetClass(const QString & parentClass, const QString & widgetClass, PortingFile * file)
{
   QString formName = file->name();
   QString application = file->application()->name();
   QString customClass;
   if (parentClass == "QWizard") {
      // all direct children of QWizard are assumed to be QWizardPage s
      if (widgetClass == "QWidget") {
         return "QWizardPage";
      } else {
         return "QWizardPage";
      }
   }
   if (widgetClass == "CButtonGroup") {
      // this holds for CButtonGroup s not Q3ButtonGroup anb not QButtonGroup
      return "CGroupBox";
   }
   if (widgetClass[0] == 'Q') {
      if (widgetClass[1] == '3') {
         if (widgetClass == "Q3ButtonGroup") {
            return "CButtonGroup";
         }
         if (widgetClass == "Q3Wizard") {
            return "QWizard";
         }
         if (widgetClass == "Q3TextBrowser") {
            return "QTextBrowser";
         }
         if (widgetClass == "Q3WidgetStack") {
            return "QStackedWidget";
         }
         if (application.compare("shacira", Qt::CaseInsensitive) == 0) {
            if (formName.compare("contextexplorer", Qt::CaseInsensitive) == 0) {
               return 'C' + widgetClass.right(widgetClass.length() - 2);
            } else {
               // matches keypad and keyboard forms that should not depend on CWidgets
               if (widgetClass.compare("Q3WidgetStack", Qt::CaseInsensitive) == 0) {
                  return "QStackedWidget";
               } else {
                  return 'Q' + widgetClass.right(widgetClass.length() - 2);
               }
            }
         } else {
            // general substitution by compatible CWidgets
//            return 'C' + widgetClass.right(widgetClass.length() - 2);
            return 'Q' + widgetClass.right(widgetClass.length() - 2);
         }
      } else {
         return widgetClass;
      }
   } else {
      customClass = widgetClass;
   } 
   if (_formBuilder.isCustomWidget(customClass)) {
      return customClass;
   } else {
      if (widgetClass == "Line") {
         return "QFrame";
      } else {
         return "CUnported";
      }
   }
}

QString UiPort::getNodeValue(const QDomNode node) const
{
   QString value;
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   if (child_count > 0) {
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
   }
   return value;
}

QString UiPort::getData(const QDomNode node)
{
   QString data;
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   if (child_count == 0) {
      return data;
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         QDomNode node = children.item(i);
         QString nodeName = node.nodeName();
         if (nodeName == "#cdata-section") {
            data += node.nodeValue();
         }
      }
   }
   return data;
}

bool UiPort::getImageData(QDomDocument document, QDomNode node, const QString & name, QString & imageData, QString & imageFormat, int & length)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   bool success = false;
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "data") {
            QString format = child.attribute("format");
            QString lengthSpec = child.attribute("length");
            QString data = getNodeValue(child);
            imageData = data;
            imageFormat = format;
            length = lengthSpec.toInt();
            return true;
         }
      }
   }
   return false;
}

bool UiPort::collectImages(QDomDocument document, const QDomNode parentNode, const QString & formId, PortingFile * file)
{
   PortingApplication * application = file->application();
   ImageInformations * imageInformations = application->imageInformations();
   QDomNodeList nodeList = parentNode.childNodes();
   int nodeCount = nodeList.count();
   bool success = false;
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "image") {
            QString imageName = child.attribute("name");
            QString imageData;
            QString imageFormat;
            int length = 0;
            if (getImageData(document, child, imageName, imageData, imageFormat, length)) {
#ifndef OBSOLETE_IMAGE_MARCHING
               bool success = imageInformations->addImageReference(formId, imageName, imageData, imageFormat, length);
               if (success) {
                  int dummy = 0;
               } else {
                  int dummy = 0;
               }
#else
               ImageInformation * imageInformation = imageInformations->imageInformation(formId, imageName, imageData, imageFormat, length);
               Image * image = imageInformations->image(imageData, imageFormat);
               if (image == NULL) {
                  LogPrintf(logFileName(), "image %s not found in %s\n", imageName.toStdString().c_str(), file->sourcePath().toStdString().c_str());
               } else {
                  QString newImageName;
                  if (imageInformations->resolveUnmatchedImage(QString(), imageName,formId, newImageName)) {
                  }
                  QString globalImageName = image->imageName();
                  if (globalImageName.contains("img_")) {
                     if (!imageInformations->resolveUnmatchedImage(globalImageName, imageName, formId, newImageName)) {
                        LogPrintf(logFileName(), "image %s not matched in %s\n", imageName.toStdString().c_str(), file->sourcePath().toStdString().c_str());
                     }
                  }
                  if (!newImageName.isEmpty()) {
                     QString name;
                     QString path;
                     QStringList components = newImageName.split("/");
                     int size = components.size();
                     int i = 0;
                     QStringList::const_iterator c = components.begin();
                     while (c != components.end()) {
                        if (i < (size - 1)) {
                           path = append(path, (*c));
                        } else {
                           name = (*c);
                        }
                        c++;
                        i++;
                     }
                     image->setImageName(name);
                     image->setPath(path);
                  }
               }
#endif
               int dummy = 0;
            } else {
               int dummy = 0;
            }
         }
      }
      collectImages(document, node, formId, file);
   }
   return true;
}

QDomElement UiPort::propertyElement(QDomDocument document, QDomNode node, const QString & propertyName) const
{
   QDomElement propertyElement;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   bool success = false;
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "property") {
            QString pName = child.attribute("name");
            if (pName == propertyName) {
               propertyElement = child;
            } else {
               int dummy = 0;
            }
         }
      }
   }
   return propertyElement;
}

bool UiPort::setNodeValue(QDomDocument document, QDomNode node, const QString & value)
{
   QDomNodeList children = node.childNodes();
   int child_count = children.count();
   if (child_count == 0) {
      QDomText text = document.createTextNode(value);
      _updateList.add(node, text);
      return true;
   } else {
      int i = 0;
      for (i=0; i<child_count; i++) {
         QDomNode node = children.item(i);
         QString nodeName = node.nodeName();
         if (nodeName ==  "#text") {
            node.setNodeValue(value);
            return true;
         } else if (nodeName ==  "#cdata-section") {
            node.setNodeValue(value);
            return true;
         }
      }
   }
   return false;
}

bool UiPort::removeNode(QDomDocument document, QDomNode parent, const QDomNode child, bool immediate)
{
   if (immediate) {
      parent.removeChild(child);
   } else {
      try {
         _updateList.remove(parent, child);
      } catch (...) {
         return false;
      }
   }
   return true;
}

void UiPort::addProperty(QDomDocument document, QDomNode node, const QString & propertyName, const QString & propertyType, const QString & propertyValue)
{
   if (_step == PartialTransformation) {
      // this code is already transformed by uiport
      return;
   }
   QDomElement propertyElement = document.createElement("property");
   _updateList.add(node, propertyElement);
   propertyElement.setAttribute("name", propertyName);
   QDomElement valueElement = document.createElement(propertyType);
   _updateList.add(propertyElement, valueElement);
   setNodeValue(document, valueElement, propertyValue);
}

void UiPort::addIconSet(QDomDocument document, QDomNode node, const QString & resourceFileName, const QString & resourceName)
{
   QDomElement iconSetElement0 = document.createElement("iconSet");
   _updateList.add(node, iconSetElement0);
   iconSetElement0.setAttribute("stdset", "0");
   QDomElement iconSetElement1 = document.createElement("iconset");
   _updateList.add(iconSetElement0, iconSetElement1);
   iconSetElement1.setAttribute("resource", resourceFileName);
   QDomElement resourceElement = document.createElement("normaloff");
   _updateList.add(iconSetElement1, resourceElement);
   setNodeValue(document, resourceElement, resourceName);
}

void UiPort::addIncludes(QDomDocument document, QDomNode node, const QString & nodeName)
{
   QDomElement uiElement = node.toElement();
   QDomElement includesElement = document.createElement("includes");
   _updateList.add(uiElement, includesElement);
   QDomElement includeElement = document.createElement("include");
   includeElement.setAttribute("location", "local");
   QString includeStatement = "qt4port.h";
   setNodeValue(document, includeElement, includeStatement);
   _updateList.add(includesElement, includeElement);
   map<QString,QString>::const_iterator i = _widgetClassMap.begin();
   while (i != _widgetClassMap.end()) {
      QString widgetClass = (*i).second;
      if (widgetClass[0] != 'Q') {
         QDomElement includeElement = document.createElement("include");
         includeElement.setAttribute("location", "local");
         QString includeStatement = widgetClass + ".h";
         setNodeValue(document, includeElement, includeStatement);
         _updateList.add(includesElement, includeElement);
      }
      i++;
   }
}

void UiPort::addCustomWidgetRefs(QDomDocument document, QDomNode node, const QString & nodeName)
{
   QDomElement uiElement = node.toElement();
   QDomElement customWidgetsElement = document.createElement("customwidgets");
   _updateList.add(uiElement, customWidgetsElement);
   map<QString,QString>::const_iterator i = _widgetClassMap.begin();
   while (i != _widgetClassMap.end()) {
      QString widgetClass = (*i).second;
      if (widgetClass[0] != 'Q') {
         bool isContainer = _formBuilder.isContainer(widgetClass);
         QDomElement customWidgetElement = document.createElement("customwidget");
         _updateList.add(customWidgetsElement, customWidgetElement);
         QDomElement classElement = document.createElement("class");
         _updateList.add(customWidgetElement, classElement);
         QDomElement extendsElement = document.createElement("extends");
         _updateList.add(customWidgetElement, extendsElement);
         QDomElement headerElement = document.createElement("header");
         _updateList.add(customWidgetElement, headerElement);
         QString header = widgetClass + ".h";
         QString extends = pluginSuperClass(widgetClass);
         setNodeValue(document, classElement, widgetClass);
         setNodeValue(document, extendsElement, extends);
         setNodeValue(document, headerElement, header);
         if (isContainer) {
            QDomElement containerElement = document.createElement("container");
            _updateList.add(customWidgetElement, containerElement);
            setNodeValue(document, containerElement, "1");
         }
      }
      i++;
   }
}

void UiPort::addResources(QDomDocument document, QDomNode node, const QString & resourceFile)
{
   QDomElement resourcesElement = document.createElement("resources");
   _updateList.add(node, resourcesElement);
   QDomElement includeElement = document.createElement("include");
   _updateList.add(resourcesElement, includeElement);
   includeElement.setAttribute("location", resourceFile);
}

void UiPort::addPaletteElement(QDomDocument document, QDomNode node, Colors * colors)
{
   QPalette::ColorRole f = colors->foregroundRole();
   QPalette::ColorRole b = colors->backgroundRole();
   QString foregroundRole = Colors::roleText(f);
   QString backgroundRole = Colors::roleText(b);
   QColor foregroundColor = colors->foregroundColor();
   QColor backgroundColor = colors->backgroundColor();
   QDomElement propertyElement = document.createElement("property");
   _updateList.add(node, propertyElement);
   propertyElement.setAttribute("name", "palette");
   QDomElement paletteElement = document.createElement("palette");
   _updateList.add(propertyElement, paletteElement);
   QDomElement activeElement = document.createElement("active");
   _updateList.add(paletteElement, activeElement);
   if (foregroundColor.isValid()) {
      QDomElement fgElement = document.createElement("colorrole");
      fgElement.setAttribute("role", foregroundRole);
      _updateList.add(activeElement, fgElement);
      addColor(document, fgElement, foregroundColor);
   }
   if (backgroundColor.isValid()) {
      QDomElement bgElement = document.createElement("colorrole");
      bgElement.setAttribute("role", backgroundRole);
      _updateList.add(activeElement, bgElement);
      addColor(document, bgElement, backgroundColor);
   }
   QDomElement inactiveElement = document.createElement("inactive");
   _updateList.add(paletteElement, inactiveElement);
   if (foregroundColor.isValid()) {
      QDomElement fgElement = document.createElement("colorrole");
      fgElement.setAttribute("role", foregroundRole);
      _updateList.add(inactiveElement, fgElement);
      addColor(document, fgElement, foregroundColor);
   }
   if (backgroundColor.isValid()) {
      QDomElement bgElement = document.createElement("colorrole");
      bgElement.setAttribute("role", backgroundRole);
      _updateList.add(inactiveElement, bgElement);
      addColor(document, bgElement, backgroundColor);
   }
   QDomElement disabledElement = document.createElement("disabled");
   _updateList.add(paletteElement, disabledElement);
   if (foregroundColor.isValid()) {
      QDomElement fgElement = document.createElement("colorrole");
      fgElement.setAttribute("role", foregroundRole);
      _updateList.add(disabledElement, fgElement);
      addColor(document, fgElement, foregroundColor);
   }
   if (backgroundColor.isValid()) {
      QDomElement bgElement = document.createElement("colorrole");
      bgElement.setAttribute("role", backgroundRole);
      _updateList.add(disabledElement, bgElement);
      addColor(document, bgElement, backgroundColor);
   }
}

void UiPort::addPaletteElement(QDomDocument document, QDomNode node, QPalette palette, const QString targetClass)
{
   QDomElement propertyElement = document.createElement("property");
   _updateList.add(node, propertyElement);
   propertyElement.setAttribute("name", "palette");
   QDomElement paletteElement = document.createElement("palette");
   _updateList.add(propertyElement, paletteElement);
   QList<QPalette::ColorGroup> colorGroupList;
   colorGroupList << QPalette::Active;
   colorGroupList << QPalette::Inactive;
   colorGroupList << QPalette::Disabled;
   QList<QPalette::ColorRole> colorRoleList;
   colorRoleList << QPalette::Window;
   colorRoleList << QPalette::WindowText;
   if (targetClass.contains("button", Qt::CaseInsensitive)) {
      colorRoleList << QPalette::Button;
   }
   addColorGroups(document, paletteElement, palette, colorGroupList, colorRoleList);
}

void UiPort::addColorGroups(QDomDocument document, QDomNode node, QPalette palette, QList<QPalette::ColorGroup> colorGroupList, QList<QPalette::ColorRole> colorRoleList)
{
   QList<QPalette::ColorGroup>::const_iterator i = colorGroupList.begin();
   while (i != colorGroupList.end()) {
      QString groupName;
      if ((*i) == QPalette::Active) {
         groupName = "active";
      } else if ((*i) == QPalette::Inactive) {
         groupName = "inactive";
      } else if ((*i) == QPalette::Disabled) {
         groupName = "disabled";
      }
      QDomElement groupElement = document.createElement(groupName);
      _updateList.add(node, groupElement);
      addColorRoles(document, groupElement, palette, (*i), colorRoleList);
      i++;
   }
}

void UiPort::addColorRoles(QDomDocument document, QDomNode node, QPalette palette, QPalette::ColorGroup colorGroup, QList<QPalette::ColorRole> colorRoleList)
{
   QList<QPalette::ColorRole>::const_iterator i = colorRoleList.begin();
   while (i != colorRoleList.end()) {
      QString roleName;
      if ((*i) == QPalette::Window) {
         roleName = "Window";
      } else if ((*i) == QPalette::WindowText) {
         roleName = "WindowText";
      } else if ((*i) == QPalette::Button) {
         roleName = "Button";
      }
      QDomElement roleElement = document.createElement("colorrole");
      _updateList.add(node, roleElement);
      roleElement.setAttribute("role", roleName);
      QColor color = palette.color(colorGroup, (*i));
      addColor(document, roleElement, color);
      i++;
   }
}

void UiPort::addColor(QDomDocument document, QDomNode node, QColor color)
{
   QDomElement brushElement = document.createElement("brush");
   _updateList.add(node, brushElement);
//   brushElement.setAttribute("brushstyle", "Qt::SolidPattern");
   brushElement.setAttribute("brushstyle", "SolidPattern");
   QDomElement colorElement = document.createElement("color");
   _updateList.add(brushElement, colorElement);
   colorElement.setAttribute("alpha", QString::number(color.alpha()));
   QDomElement redElement = document.createElement("red");
   _updateList.add(colorElement, redElement);
   setNodeValue(document, redElement, QString::number(color.red()));
   QDomElement greenElement = document.createElement("green");
   _updateList.add(colorElement, greenElement);
   setNodeValue(document, greenElement, QString::number(color.green()));
   QDomElement blueElement = document.createElement("blue");
   _updateList.add(colorElement, blueElement);
   setNodeValue(document, blueElement, QString::number(color.blue()));
}

void UiPort::addSpacerItem(QDomDocument document, QDomNode node, bool vertical, int width, int height)
{
   QDomElement itemElement = document.createElement("item");
   _updateList.add(node, itemElement);
   addSpacer(document, itemElement, vertical, width, height);
}

void UiPort::addSpacer(QDomDocument document, QDomNode node, bool vertical, int width, int height)
{
   QString spacerName = vertical ? "verticalSpacer" : "horizontalSpacer";
   spacerName += QString::number(_spacerNameIndex++);
   QString orientation = vertical ? "Qt::Vertical" : "Qt::Horizontal";
   QDomElement spacerElement = document.createElement("spacer");
   _updateList.add(node, spacerElement);
   spacerElement.setAttribute("name", spacerName);
   QDomElement orientationElement = document.createElement("property");
   _updateList.add(spacerElement, orientationElement);
   orientationElement.setAttribute("name", "orientation");
   QDomElement enumElement = document.createElement("enum");
   _updateList.add(orientationElement, enumElement);
   setNodeValue(document, enumElement, "Qt::Vertical");
   addSizeHint(document, spacerElement, width, height);
}

void UiPort::addSizeHint(QDomDocument document, QDomNode node, int width, int height)
{
   QDomElement sizeHintElement = document.createElement("property");
   _updateList.add(node, sizeHintElement);
   sizeHintElement.setAttribute("name", "sizeHint");
   sizeHintElement.setAttribute("stdset", "0");
   addSizeElement(document, sizeHintElement, width, height);
}


void UiPort::addSizeElement(QDomDocument document, QDomNode node, int width, int height)
{
   QString widthText = QString::number(width);
   QString heightText = QString::number(height);
   QDomElement sizeElement = document.createElement("size");
   _updateList.add(node, sizeElement);
   QDomElement widthElement = document.createElement("width");
   _updateList.add(sizeElement, widthElement);
   setNodeValue(document, widthElement, widthText);
   QDomElement heightElement = document.createElement("height");
   _updateList.add(sizeElement, heightElement);
   setNodeValue(document, heightElement, heightText);
}

void UiPort::addPixmap(QDomDocument document, QDomNode node, const QString & resourceFileName, const QString & resourceString, const QString & targetClass)
{
   QDomElement pixmapProperty = document.createElement("property");
   _updateList.add(node, pixmapProperty);
   pixmapProperty.setAttribute("name", "pixmap");
   QDomElement pixmapElement = document.createElement("pixmap");
   _updateList.add(pixmapProperty, pixmapElement);
   pixmapElement.setAttribute("resource", resourceFileName);
   setNodeValue(document, pixmapElement, resourceString);
}

void UiPort::addLineWrapMode(QDomDocument document, QDomNode node, const QString & enumValue)
{
   QDomElement lineWrapModeProperty = document.createElement("property");
   _updateList.add(node, lineWrapModeProperty);
   lineWrapModeProperty.setAttribute("name", "lineWrapMode");
   QDomElement modeElement = document.createElement("enum");
   _updateList.add(lineWrapModeProperty, modeElement);
   setNodeValue(document, modeElement, enumValue);
}

void UiPort::addAlignment(QDomDocument document, QDomNode node, const QString & alignmentValue)
{
   QDomElement lineWrapModeProperty = document.createElement("property");
   _updateList.add(node, lineWrapModeProperty);
   lineWrapModeProperty.setAttribute("name", "alignment");
   QDomElement modeElement = document.createElement("set");
   _updateList.add(lineWrapModeProperty, modeElement);
   setNodeValue(document, modeElement, alignmentValue);
}

void UiPort::addIcon(QDomDocument document, QDomNode node, const QString & resourceFileName, const QString & resourceString, const QString & targetClass)
{
#ifdef doku
        <property name="icon">
         <iconset resource="../../qresources/mosaic.qrc">
          <normaloff>:/mosaic/images/Erste-Hilfe_Koffer.png</normaloff>:/mosaic/images/Erste-Hilfe_Koffer.png</iconset>
        </property>
#endif
   //   icons are configured in the same way as in qt designer
   QDomElement iconProperty = document.createElement("property");
   _updateList.add(node, iconProperty);
   iconProperty.setAttribute("name", "icon");
   QDomElement iconSetElement = document.createElement("iconset");
   _updateList.add(iconProperty, iconSetElement);
   iconSetElement.setAttribute("resource", resourceFileName);
   addIconState(document, iconSetElement, "normaloff", resourceString);
   if (!setNodeValue(document, iconSetElement, resourceString)) {
      int dummy = 0;
   }
   addIconSize(document, node, 48, 48);
#ifdef previous_settings
   addIconState(document, iconSetElement, "normalon", resourceString);
   addIconState(document, iconSetElement, "disabledoff", resourceString);
   addIconState(document, iconSetElement, "disabledon", resourceString);
   addIconState(document, iconSetElement, "activeoff", resourceString);
   addIconState(document, iconSetElement, "activeon", resourceString);
   addIconState(document, iconSetElement, "selectedoff", resourceString);
   addIconState(document, iconSetElement, "selectedon", resourceString);
#endif
}

void UiPort::addIconState(QDomDocument document, QDomNode node, const QString & stateName, const QString & resourceString)
{
   QDomElement stateElement = document.createElement(stateName);
   _updateList.add(node, stateElement);
   setNodeValue(document, stateElement, resourceString);
}

void UiPort::addIconSize(QDomDocument document, QDomNode node, int width, int height)
{
   QDomElement iconSizeProperty = document.createElement("property");
   _updateList.add(node, iconSizeProperty);
   iconSizeProperty.setAttribute("name", "iconSize");
   QDomElement iconSizeElement = document.createElement("size");
   _updateList.add(iconSizeProperty, iconSizeElement);
   QDomElement widthElement = document.createElement("width");
   setNodeValue(document, widthElement, QString::number(width));
   _updateList.add(iconSizeElement, widthElement);
   QDomElement heightElement = document.createElement("height");
   setNodeValue(document, heightElement, QString::number(height));
   _updateList.add(iconSizeElement, heightElement);
}

bool UiPort::nodeFilter(QDomDocument document, QDomNode parent, const QDomNode child, const QString & tagName)
{
   if (tagName == "images") {
      // images are extracted and managed over the Qt4 resource system
      return true;
   } else if (tagName == "customwidgets") {
      return true;
   } else if (tagName == "includehints") {
      return true;
   } else if (tagName == "includes") {
      // includes are restricted to really used classes
      return true;
   } else if (tagName == "pixmapfunction") {
      // this leads to includes on <Qt3Support/Q3MimesourceFactory> in uic generated form files
      return true;
   }
   return false;
}

QString UiPort::filterWordBreak(const QString & value)
{
   int valueLen = value.length();
   QString newValue;
   QString head;
   QString tail = value;
   int pos = tail.indexOf("|");
   while (pos > 0) {
      head = tail.left(pos);
      tail = tail.right(tail.length() - (pos +1));
      if (head != "WordBreak") {
         if (!newValue.isEmpty()) {
            newValue += "|";
         }
         newValue += head;
      }
      pos = tail.indexOf("|");
   }
   head = tail;
   if (head != "WordBreak") {
      if (!newValue.isEmpty()) {
         newValue += "|";
      }
      newValue += head;
   }
   return newValue;
}

QString UiPort::filterShape(const QString & value)
{
   return value;
}

bool UiPort::adjustPalette(QDomDocument document, QDomNode node, QColor color, bool foreground, const QString targetClass)
{
   QPalette palette;
   QPalette::ColorGroup colorGroup = QPalette::Active;
   QPalette::ColorRole colorRole = (foreground) ? QPalette::WindowText : QPalette::Window;
   QBrush brush(color, Qt::SolidPattern);
   palette.setBrush(colorGroup, colorRole, brush);
   QBrush buttonBrush(color, Qt::SolidPattern);
   palette.setBrush(colorGroup, QPalette::Button, brush);
   addPaletteElement(document, node, palette, targetClass);
   return true;
}

bool UiPort::adjustLayout(QDomDocument document, QDomNode node, const QString & targetClass)
{
   QString name = node.toElement().attribute("name");
   QString className = node.toElement().attribute("class");
   if (className == "QVBoxLayout" &&
       targetClass == "CButtonGroup") {
      addSpacerItem(document, node, true, 23, 44);
   }
   return true;
}

#ifdef doku
    <connection>
      <sender>CurrentDataFileButton</sender>
      <signal>FileActive(int)</signal>
      <receiver>mDataSetDescGroupBox</receiver>
      <slot>raiseWidget(int)</slot>
    </connection>
#endif
bool UiPort::adjustConnection(QDomDocument document, QDomNode node)
{
   QString sender;
   QString signal;
   QString receiver;
   QString slot;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode child = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      QString tagName = "node";
      if (nodeType == QDomNode::ElementNode) {
         QDomElement element = child.toElement();
         tagName = element.tagName();
         if (tagName == "sender") {
            sender = getNodeValue(child);
         } else if (tagName == "signal") {
            signal = getNodeValue(child);
            adjustSignal(document, element, signal, sender);
         } else if (tagName == "receiver") {
            receiver = getNodeValue(child);
         } else if (tagName == "slot") {
            slot = getNodeValue(child);
            adjustSlot(document, element, slot, receiver);
         } else {
            int dummy = 0;
         }
      }
   }
   return true;
}

void UiPort::adjustSignal(QDomDocument document, QDomElement element, const QString & signal, const QString & sender)
{
   bool altered = false;
   QString newValue = signal;
   int pos = newValue.indexOf("Q3CString");
   if (pos >= 0) {
      altered = true;
      newValue = replaceAll(newValue, "Q3CString", "QString");
   }
   pos = newValue.indexOf("aboutToShow(int)");
   if (pos >= 0) {
      altered = true;
      newValue = replaceAll(newValue, "aboutToShow(int)", "currentChanged(int)");
   }
   pos = newValue.indexOf("aboutToShow(QWidget*)");
   if (pos >= 0) {
      altered = true;
      newValue = replaceAll(newValue, "aboutToShow(QWidget*)", "currentChanged(QWidget*)");
   }
   pos = newValue.indexOf("aboutToShow");
   if (pos >= 0) {
      int dummy = 0;
   }
   if (altered) {
      setNodeValue(document, element, newValue);
   }
}

void UiPort::adjustSlot(QDomDocument document, QDomElement element, const QString & slot, const QString & receiver)
{
   bool altered = false;
   QString newValue = slot;
   int pos = newValue.indexOf("Q3CString");
   if (pos >= 0) {
      altered = true;
      newValue = replaceAll(newValue, "Q3CString", "QString");
   }
   pos = newValue.indexOf("setShown");
   if (pos >= 0) {
      altered = true;
      newValue = replaceAll(newValue, "setShown", "setVisible");
   }
   if (widgetClass(receiver) != "MDataSetDescGroupBox") {
      pos = newValue.indexOf("raiseWidget(int)");
      if (pos >= 0) {
         altered = true;
         newValue = replaceAll(newValue, "raiseWidget(int)", "setCurrentIndex(int)");
      }
      pos = newValue.indexOf("raiseWidget(QWidget*)");
      if (pos >= 0) {
         altered = true;
         newValue = replaceAll(newValue, "raiseWidget(QWidget*)", "setCurrentWidget(QWidget*)");
      }
      pos = newValue.indexOf("raiseWidget");
      if (pos >= 0) {
         int dummy = 0;
      }
   }
   if (altered) {
      setNodeValue(document, element, newValue);
   }
}

void UiPort::splitEnumValue(const QString & enumValue, QString & nameSpace, QString & value)
{
   QStringList componentList = enumValue.split("::");
   QStringList::const_iterator c = componentList.begin();
   if (componentList.size() == 1) {
      value = (*componentList.begin());
   } else if (componentList.size() == 2) {
      nameSpace = (*componentList.begin());
      value = (*(componentList.begin() + 1));
   } else {
      int dummy = 0;
   }
}

QString UiPort::filterEnumValue(const QString & enumValue, QWidget * widget, const QString & newNameSpace)
{
   QString nameSpace;
   QString value;
   splitEnumValue(enumValue, nameSpace, value);
   if (!nameSpace.isEmpty()) {
      if (nameSpace[1] == '3') {
         nameSpace.clear();
      }
   }
   QString newValue = value;
   if (value == "GroupBoxPanel") {
      newValue = "StyledPanel";
   }
   if (value == "LineEditPanel") {
      newValue = "StyledPanel";
   }
   if (value == "WordBreak") {
      newValue.clear();
   }
   if (!newValue.isEmpty()) {
      if (!nameSpace.isEmpty()) {
         newValue = nameSpace + "::" + newValue;
      } else if (!newNameSpace.isEmpty()) {
         newValue = newNameSpace + "::" + newValue;
      }
   }
   return newValue;
}

QString UiPort::filterSetValue(const QString & setValue, QWidget * widget, const QString & newNameSpace)
{
   QString newValueList;
   QStringList valueList = setValue.split("|");
   QStringList::const_iterator v = valueList.begin();
   while (v != valueList.end()) {
      QString newValue = filterEnumValue(*v, widget, newNameSpace);
      if (!newValue.isEmpty()) {
         if (!newValueList.isEmpty()) {
            newValueList += "|";
         }
         newValueList += newValue;
      }
      v++;
   }
   return newValueList;
}

bool UiPort::filterProperty(const QString & propertyName, const QString & targetClass) const
{
   if (targetClass == "CUnported") {
      if (propertyName == "originalClass") {
         return false;
      } else {
         return true;
      }
   }
   if (targetClass == "CFrame") {
      if (propertyName == "autoMask") {
         return true;
      }
   }
   if (targetClass == "CButtonGroup") {
      if (propertyName == "flat") {
         return true;
      }
      if (propertyName == "title") {
         return true;
      }
   }
   return false;
}

bool UiPort::propertySet(QDomNode node, const QString & propertyName, const QString & propertyType, const QString & attributeName, const QString & attributeValue) const
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "property") {
            QString name = child.attribute("name");
            if (name.compare(propertyName, Qt::CaseInsensitive) == 0) {
               if (propertyType.isEmpty()) {
                  return true;
               } 
               QDomNodeList typeList = child.elementsByTagName(propertyType);
               int typeNodeCount = typeList.count();
               if (typeNodeCount == 1) {
                  QDomElement typeElement = typeList.item(0).toElement();
                  if (attributeName.isEmpty()) {
                     QString value = getNodeValue(typeElement);
                     if (value.isEmpty()) {
                        return false;
                     } else {
                        return true;
                     }
                  }
                  if (typeElement.hasAttribute(attributeName)) {
                     if (!attributeValue.isEmpty()) {
                        QString value = typeElement.attribute(attributeName);
                        if (value == attributeValue) {
                           return true;
                        }
                     } else {
                        return true;
                     }
                  }
               }
            }
         }
      }
   }
   return false;
}

QVariant UiPort::propertyValue(QDomNode node) const
{
   QVariant value;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "color") {
            value = colorValue(child);
         } else if (tagName == "string") {
            value = stringValue(child);
         } else if (tagName == "bool") {
            value = boolValue(child);
         } else if (tagName == "iconset") {
            value = stringValue(child);
         } else if (tagName == "pixmap") {
            value = stringValue(child);
         } else if (tagName == "palette") {
            value = paletteValue(child);
         } else if (tagName == "enum") {
            value = stringValue(child);
         } else if (tagName == "set") {
            value = stringValue(child);
         } else if (tagName == "number") {
            value = stringValue(child);
         } else {
            int dummy = 0;
         }
      }
   }
   return value;
}

QPalette UiPort::paletteValue(QDomNode node) const
{
   QPalette palette;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         QDomNodeList colorList = child.childNodes();
         int colorCount = colorList.count();
         int j = 0;
         for (i=0; i<nodeCount; i++) {
            QDomNode node = colorList.item(i);
            QDomNode::NodeType nodeType = node.nodeType();
            if (nodeType == QDomNode::ElementNode) {
               QDomElement colorElement = node.toElement();
               QColor color = colorValue(colorElement);
               QPalette::ColorGroup colorGroup = QPalette::Active;
               if (tagName == "active") {
                  colorGroup = QPalette::Active;
               } else if (tagName == "inactive") {
                  colorGroup = QPalette::Inactive;
               } else if (tagName == "disabled") {
                  colorGroup = QPalette::Disabled;
               }
               QPalette::ColorRole colorRole = QPalette::Window;
               QBrush brush(color, Qt::SolidPattern);
               palette.setBrush(colorGroup, colorRole, brush);
//               palette.setColor(colorGroup, colorRole, color);
            }
         }
      }
   }
   return palette;
}

QColor UiPort::colorValue(QDomNode node) const
{
   int red = 0x01234;
   int green = 0x01234;
   int blue = 0x01234;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   if (nodeCount != 3) {
      int dummy = 0;
   }
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "red") {
            red = getNodeValue(child).toInt();
         } else if (tagName == "green") {
            green = getNodeValue(child).toInt();
         } else if (tagName == "blue") {
            blue = getNodeValue(child).toInt();
         } else {
            int dummy = 0;
         }
      }
   }
   return QColor(red, green, blue);
}

QString UiPort::stringValue(QDomNode node) const
{
   QString value = getNodeValue(node);
   return value;
}

bool UiPort::boolValue(QDomNode node) const
{
   bool value = false;
   if (getNodeValue(node) == "true") {
      value = true;
   }
   return value;
}

QString UiPort::tagName(QDomNode node) const
{
   return node.nodeName();
}

QString UiPort::nodeName(QDomNode node) const
{
   QString name;
   if (node.nodeType() == QDomNode::ElementNode) {
      name = node.toElement().attribute("name");
   }
   return name;
}

QString UiPort::className(QDomNode node) const
{
   QString name;
   if (node.nodeType() == QDomNode::ElementNode) {
      name = node.toElement().attribute("class");
   }
   return name;
}

void UiPort::adjustWizardPage(QDomDocument document, const QDomNode parentNode, const QDomNode pageNode)
{
   if (_step == PartialTransformation) {
      // this code is already transformed by uiport
      return;
   }
   QDomElement propertyElement = document.createElement("property");
   _updateList.add(pageNode, propertyElement);
   propertyElement.setAttribute("name", "subTitle");
   QDomElement valueElement = document.createElement("string");
   valueElement.setAttribute("notr", "true");
   valueElement.setAttribute("extracomment", "dummy subTitle");
   _updateList.add(propertyElement, valueElement);
   setNodeValue(document, valueElement, "<html><head/><body><p/></body></html>");
}

void UiPort::handleProperty(QDomDocument document, QDomNode parentNode, const QDomElement propertyElement, const QString parentClass, const QString targetClass, QWidget * targetWidget, PortingFile * file, Colors * colors)
{
   if (_step == PartialTransformation) {
      // this code is already transformed by uiport
      return;
   }
   QString formId = file->logicPath();
   PortingApplication * application = file->application();
   ImageInformations * imageInformations = application->imageInformations();
   QString propertyName = propertyElement.attribute("name");
   if (false) {
      string pName = propertyName.toStdString();
      const char * name = pName.c_str();
      QVariant p = targetWidget->property(name);
      if (p.isValid()) {
         int dummy = 0;
      } else {
         if (strcmp(name, "display") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else if (strcmp(name, "hScrollBarMode") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else if (strcmp(name, "selectionMode") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else if (strcmp(name, "sortEnabled") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else if (strcmp(name, "margin") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else if (strcmp(name, "textFormat") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else if (strcmp(name, "exclusive") == 0) {
            _updateList.remove(parentNode, propertyElement);
         } else {
#define INVALID_PROPS_FILE "invalid_props.txt"
            FILE * stream = fopen(INVALID_PROPS_FILE, "a");
            if (stream != NULL) {
               fprintf(stream, "%s: %s in %s\n", formId.toStdString().c_str(), name, targetClass.toStdString().c_str()); 
               fclose(stream);
            }
         }
      }
   }
   if (!propertyAllowed(targetWidget, propertyName)) {
      if (targetClass != "CUnported") {
//         cerr << "property " << propertyName.toStdString() << " not allowed for " << targetClass.toStdString() << endl;
//         LogPrintf(errorFileName(), "property %s not allowed in widget class %s\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
      }
//      _updateList.remove(parentNode, propertyElement);
//      return;
   }
   if (targetClass == "CUnported") {
      _updateList.remove(parentNode, propertyElement);
      return;
   }
   if (filterProperty(propertyName, targetClass)) {
      if (removeNode(document, parentNode, propertyElement)) {
      }
   } else {
      QVariant propertyValue;
      if (propertyName == "paletteBackgroundPixmap") {
         propertyValue = this->propertyValue(propertyElement);
         QString imageName = propertyValue.toString();
         QString resourceFileName = imageInformations->resourceFileReference(file);
         QString resourceString = imageInformations->resourceString(formId, imageName);
         addPixmap(document, parentNode, resourceFileName, resourceString, targetClass);
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "paletteBackgroundColor") {
          propertyValue = this->propertyValue(propertyElement);
          QColor color = propertyValue.value<QColor>();
          _updateList.remove(parentNode, propertyElement);
          colors->setWidget(targetWidget);
          colors->setBackgroundColor(color);
//          adjustPalette(document, parentNode, color, false, targetClass, "paletteBackgroundColor");
      } else if (propertyName == "paletteForegroundColor") {
          propertyValue = this->propertyValue(propertyElement);
          QColor color = propertyValue.value<QColor>();
          _updateList.remove(parentNode, propertyElement);
          colors->setWidget(targetWidget);
          colors->setForegroundColor(color);
//          adjustPalette(document, parentNode, color, true, targetClass, "paletteForegroundColor");
      } else if (propertyName == "pixmap") {
         if (inherits(targetWidget, "QLabel")) {
            // this is okay
         } else if (inherits(targetWidget, "QToolButton") ||
                    inherits(targetWidget, "QPushButton")) {
            propertyValue = this->propertyValue(propertyElement);
            QString imageName = propertyValue.toString();
            QString resourceFileName = imageInformations->resourceFileReference(file);
            QString resourceString = imageInformations->resourceString(formId, imageName);
            addIcon(document, parentNode, resourceFileName, resourceString, targetClass);
            _updateList.remove(parentNode, propertyElement);
         } else {
            LogPrintf(errorFileName(), "property %s not compatible with widget class %s\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
         }
      } else if (propertyName == "iconSet") {
         if (inherits(targetWidget, "CToolButton")) {
            if (propertySet(parentNode, "GeneralPixmap", "pixmap") ||
                propertySet(parentNode, "InactivePixmap", "pixmap") ||
                propertySet(parentNode, "ActiveMousePixmap", "pixmap") ||
                propertySet(parentNode, "InactiveMousePixmap", "pixmap") ||
                propertySet(parentNode, "PressedPixmap", "pixmap")) {
            } else {
               propertyValue = this->propertyValue(propertyElement);
               QString imageName = propertyValue.toString();
               QString resourceFileName = imageInformations->resourceFileReference(file);
               QString resourceString = imageInformations->resourceString(formId, imageName);
               addIcon(document, parentNode, resourceFileName, resourceString, targetClass);
            }
         } else if (inherits(targetWidget, "QToolButton")) {
            propertyValue = this->propertyValue(propertyElement);
            QString imageName = propertyValue.toString();
            QString resourceFileName = imageInformations->resourceFileReference(file);
            QString resourceString = imageInformations->resourceString(formId, imageName);
            addIcon(document, parentNode, resourceFileName, resourceString, targetClass);
         } else if (inherits(targetWidget, "QPushButton")) {
            propertyValue = this->propertyValue(propertyElement);
            QString imageName = propertyValue.toString();
            QString resourceFileName = imageInformations->resourceFileReference(file);
            QString resourceString = imageInformations->resourceString(formId, imageName);
            addIcon(document, parentNode, resourceFileName, resourceString, targetClass);
         } else {
            LogPrintf(errorFileName(), "property %s not compatible with widget class %s\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
         }
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "icon") {
         if (inherits(targetWidget, "CToolButton")) {
            if (propertySet(parentNode, "GeneralPixmap", "pixmap") ||
                propertySet(parentNode, "InactivePixmap", "pixmap") ||
                propertySet(parentNode, "ActiveMousePixmap", "pixmap") ||
                propertySet(parentNode, "InactiveMousePixmap", "pixmap") ||
                propertySet(parentNode, "PressedPixmap", "pixmap")) {
            }
         } else if (inherits(targetWidget, "QToolButton")) {
            propertyValue = this->propertyValue(propertyElement);
            QString imageName = propertyValue.toString();
            if (imageName.isEmpty()) {
               propertyValue = this->propertyValue(propertyElement);
               imageName = propertyValue.toString();
            }
            QString resourceFileName = imageInformations->resourceFileReference(file);
            QString resourceString = imageInformations->resourceString(formId, imageName);
            addIcon(document, parentNode, resourceFileName, resourceString, targetClass);
            _updateList.remove(parentNode, propertyElement);
         } else if (inherits(targetWidget, "QPushButton")) {
            propertyValue = this->propertyValue(propertyElement);
            QString imageName = propertyValue.toString();
            QString resourceFileName = imageInformations->resourceFileReference(file);
            QString resourceString = imageInformations->resourceString(formId, imageName);
            addIcon(document, parentNode, resourceFileName, resourceString, targetClass);
            _updateList.remove(parentNode, propertyElement);
         } else {
            LogPrintf(errorFileName(), "property %s not compatible with widget class %s\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
         }
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "usesBigPixmap") {
         propertyValue = this->propertyValue(propertyElement);
         bool value = propertyValue.toBool();
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "usesTextLabel") {
         propertyValue = this->propertyValue(propertyElement);
         bool value = propertyValue.toBool();
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "textLabel") {
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         if (!value.isEmpty()) {
            addProperty(document, parentNode, "text", "string", value);
         }
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "palette") {
         propertyValue = this->propertyValue(propertyElement);
         QPalette palette = propertyValue.value<QPalette>();
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "wordWrap") {
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         if (value == "false") {
            _updateList.remove(parentNode, propertyElement);
         } else {
            if (inherits(targetWidget, "QTextEdit")) {
               // this may never happen !!
               QString nameSpace;
               QString enumValue;
               splitEnumValue(value, nameSpace, enumValue);
               addLineWrapMode(document, parentNode, enumValue);
               _updateList.remove(parentNode, propertyElement);
            } else if (inherits(targetWidget, "QLabel")) {
            } else {
            }
         }
      } else if (propertyName == "caption") {
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         addProperty(document, parentNode, "windowTitle", "string", value);
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "sizeLimit") {
         if (inherits(targetWidget, "QComboBox")) {
            propertyValue = this->propertyValue(propertyElement);
            QString value = propertyValue.toString();
            addProperty(document, parentNode, "maxVisibleItems", "number", value);
            _updateList.remove(parentNode, propertyElement);
         }
      } else if (propertyName == "alignment") {
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         if (value == "AlignAuto") {
            _updateList.remove(parentNode, propertyElement);
         } else {
            QString newValue = filterWordBreak(value);
            if (newValue != value) {
               _updateList.remove(parentNode, propertyElement);
               addAlignment(document, parentNode, newValue);
               addProperty(document, parentNode, "wordWrap", "bool", "true");
            }
         }
      } else if (propertyName == "frameShadow") {
         if (!propertyAllowed(targetWidget, propertyName)) {
            if (targetClass != "CUnported") {
               cerr << "property " << propertyName.toStdString() << " not allowed for " << targetClass.toStdString() << " property removed" << endl;
               LogPrintf(errorFileName(), "property %s not allowed in widget class %s property removed\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
            }
            _updateList.remove(parentNode, propertyElement);
            return;
         }
         // check shape value for "NoFrame"
         QDomElement shapeElement = this->propertyElement(document, parentNode, "frameShape");
         if (!shapeElement.isNull()) {
            QString shapeValue = this->propertyValue(shapeElement).toString();
            if (shapeValue.contains("NoFrame")) {
               // remove shadow element
               _updateList.remove(parentNode, propertyElement);
               return;
            }
         }
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         QString newValue = filterEnumValue(value, targetWidget);
         _updateList.remove(parentNode, propertyElement);
         if (!newValue.isEmpty()) {
            addProperty(document, parentNode, propertyName, "enum", newValue);
         }
      } else if (propertyName == "frameShape") {
         if (!propertyAllowed(targetWidget, propertyName)) {
            if (targetClass != "CUnported") {
               cerr << "property " << propertyName.toStdString() << " not allowed for " << targetClass.toStdString() << " property removed" << endl;
               LogPrintf(errorFileName(), "property %s not allowed in widget class %s property removed\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
            }
            _updateList.remove(parentNode, propertyElement);
            return;
         }
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         // preliminary control of frame shape values
         if (targetClass == "CFixText") {
            if (value.contains("StyledPanel")) {
               // 4.
               _updateList.remove(parentNode, propertyElement);
               addProperty(document, parentNode, propertyName, "enum", "Panel");
               return;
            }
         } else if (targetClass == "CActValue") {
            if (value.contains("StyledPanel")) {
               // 5.
               _updateList.remove(parentNode, propertyElement);
               return;
            }
         } else if (targetClass == "QLineEdit") {
            if (value.contains("NoFrame")) {
               // 10.
               // not detected because uic3 removes frameShape and frameShadow
               ;
            }
         } else {
            // 8.
            if (value.contains("NoFrame")) {
               QDomElement shadowElement = this->propertyElement(document, parentNode, "frameShadow");
               if (!shadowElement.isNull()) {
                  _updateList.remove(parentNode, shadowElement);
                  return;
               }
            }
         }

         QString newValue = filterEnumValue(value, targetWidget);
         _updateList.remove(parentNode, propertyElement);
         if (!newValue.isEmpty()) {
            addProperty(document, parentNode, propertyName, "enum", newValue);
         }
      } else if (propertyName == "lineWidth") {
         if (!propertyAllowed(targetWidget, propertyName)) {
            if (targetClass != "CUnported") {
               cerr << "property " << propertyName.toStdString() << " not allowed for " << targetClass.toStdString() << " property removed" << endl;
               LogPrintf(errorFileName(), "property %s not allowed in widget class %s property removed\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
            }
            _updateList.remove(parentNode, propertyElement);
            return;
         }
      } else if (propertyName == "backgroundOrigin") {
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "showSortIndicator") {
         _updateList.remove(parentNode, propertyElement);
#pragma message("todo: add property sortEnabled for this column: test it")
         addProperty(document, parentNode, "sortEnabled", "bool", "true");
      } else if (propertyName == "textPosition") {
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "insertionPolicy") {
         _updateList.remove(parentNode, propertyElement);
      } else if (propertyName == "autoFormatting") {
         if (!propertyAllowed(targetWidget, propertyName)) {
            if (targetClass != "CUnported") {
               cerr << "property " << propertyName.toStdString() << " not allowed for " << targetClass.toStdString() << " property removed" << endl;
               LogPrintf(errorFileName(), "property %s not allowed in widget class %s property removed\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
            }
            _updateList.remove(parentNode, propertyElement);
            return;
         }
         propertyValue = this->propertyValue(propertyElement);
         QString setValue = propertyValue.toString();
         QString newValue = filterSetValue(setValue, targetWidget, "QTextEdit");
         _updateList.remove(parentNode, propertyElement);
         if (!newValue.isEmpty()) {
            addProperty(document, parentNode, propertyName, "set", newValue);
         }
      } else if (propertyName == "toggleButton") {
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         _updateList.remove(parentNode, propertyElement);
         addProperty(document, parentNode, "checkable", "bool", value);
      } else if (propertyName == "on") {
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         _updateList.remove(parentNode, propertyElement);
         addProperty(document, parentNode, "checked", "bool", value);
      } else if (propertyName == "resizeMode") {
         if (inherits(targetWidget, "ListView")) {
            _updateList.remove(parentNode, propertyElement);
         }
      } else if (propertyName == "margin") {
         if (inherits(targetWidget, "ListView")) {
            _updateList.remove(parentNode, propertyElement);
         }
      } else if (propertyName == "itemMargin") {
         if (inherits(targetWidget, "ListView")) {
            _updateList.remove(parentNode, propertyElement);
         }
      } else if (propertyName == "Orientation") {
         // custom type mosaic mscale, ...
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         QStringList components = value.split("::");
         QString nameSpace = components.first();
         QString valueName = components.last();
         QString newValue = targetClass + "::" + valueName;
         _updateList.remove(parentNode, propertyElement);
         addProperty(document, parentNode, "Orientation", "enum", newValue);
      } else if (propertyName == "title") {
         if (inherits(targetWidget, "QGroupBox")) {
            propertyValue = this->propertyValue(propertyElement);
            QString value = propertyValue.toString();
            _updateList.remove(parentNode, propertyElement);
            addProperty(document, parentNode, "title", "string", value);
         } else {
            QString parentClass = className(parentNode);
            if (parentClass != "CGroupBox" &&
                parentClass != "QWizardPage") {
               propertyValue = this->propertyValue(propertyElement);
               QString value = propertyValue.toString();
               _updateList.remove(parentNode, propertyElement);
               addProperty(document, parentNode, "windowTitle", "string", value);
            }
         }
      } else if (propertyName == "text") {
         // empty text properties cause translation problems
         // they will be erased in retranslateUi
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         if (value.isEmpty()) {
            _updateList.remove(parentNode, propertyElement);
         }
      } else if (propertyName == "treeStepSize") {
#ifdef doku
     <property name="indentation">
      <number>30</number>
     </property>
#endif
         propertyValue = this->propertyValue(propertyElement);
         QString value = propertyValue.toString();
         _updateList.remove(parentNode, propertyElement);
         if (value.toInt() != 20) {
            // 20 is default
            addProperty(document, parentNode, "indentation", "number", value);
         }
      } else {
         if (!propertyAllowed(targetWidget, propertyName)) {
            if (targetClass != "CUnported") {
               cerr << "property " << propertyName.toStdString() << " not allowed for " << targetClass.toStdString() << " property removed" << endl;
               LogPrintf(errorFileName(), "property %s not allowed in widget class %s property removed\n", propertyName.toStdString().c_str(), targetClass.toStdString().c_str());
            }
            _updateList.remove(parentNode, propertyElement);
            return;
         }
         if (targetWidget != NULL) {
            QString widgetName = targetWidget->objectName();
            QVariant value = targetWidget->property(propertyName.toStdString().c_str());
            if (value.isValid()) {
               int dummy = 0;
            } else {
               PortingApplication * application = file->application();
               if (propertyName == "orientation" ||
                   propertyName == "spacing" ||
                   propertyName == "sizeType") {
                  // ignore it
               } else {
                  application->addInvalidProperty(file, propertyName, widgetName);
               }
            }
         }
      }
   }
}

QString UiPort::replaceAll(const QString & s, const QString &s1, const QString & s2) const
{
   QString newValue = s;
   int position = newValue.indexOf(s1);
   while (position >= 0) {
      newValue.replace(position, s1.length(), s2);
      position = newValue.indexOf(s1);
   }
   return newValue;
}

QString UiPort::pluginSuperClass(const QString & className)
{
   // this method adjusts inheritance of widgets inheriting from unpublished base widgets
   if (className[0] == 'Q') {
      return QString();
   }
   QString baseClass = _formBuilder.baseClass(className);
   if (baseClass == "ListView") {
      return "QTreeWidget";
   }
   if (baseClass == "TableWidget") {
      return "QTableWidget";
   }
   bool isCustomWidget = _formBuilder.isCustomWidget(baseClass);
   if (isCustomWidget || baseClass[0] == 'Q') {
      return baseClass;
   } else {
      if (baseClass == "MNavigationListView") {
         return "CListView";
      } else {
         baseClass = "UnsupportedSuperClass";
      }
      return baseClass;
   }
}

QRect UiPort::rectangle(QDomNode node) const
{
   QRect rect;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   bool success = false;
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "property") {
            QString propertyName = child.attribute("name");
            if (propertyName == "geometry") {
               rect = geometry(child);
               int dummy = 0;
            }
         }
      }
   }
   return rect;
}

QRect UiPort::geometry(QDomNode node) const
{
   QRect rect;
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   bool success = false;
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "rect") {
            rect.setX(geometryValue(child, "x"));
            rect.setY(geometryValue(child, "y"));
            rect.setWidth(geometryValue(child, "width"));
            rect.setHeight(geometryValue(child, "height"));
         }
      }
   }
   return rect;
}

int UiPort::geometryValue(QDomNode node, const QString & valueName) const
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   bool success = false;
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == valueName) {
            QString value = getNodeValue(child);
            int integerValue = value.toInt();
            return integerValue;
         }
      }
   }
   return -1;
}

QDomElement UiPort::createWidgetElement(QDomDocument document, const QString & widgetClass, const QRect & rect, QDomElement & element)
{
   QDomElement layoutElement = document.createElement("layout");
   layoutElement.setAttribute("class", "QVBoxLayout");
   layoutElement.setAttribute("name", "verticalLayout");
   QDomElement itemElement = document.createElement("item");
   layoutElement.appendChild(itemElement);
   QDomElement widgetElement = document.createElement("widget");
   itemElement.appendChild(widgetElement);
   widgetElement.setAttribute("class", widgetClass);
//   QDomElement propertyElement = createGeometryElement(document, rect);
   QDomElement propertyElement = createMinSizeElement(document, rect);
   widgetElement.appendChild(propertyElement);
   element = widgetElement;
   return layoutElement;
}

QDomElement UiPort::createGeometryElement(QDomDocument document, const QRect & rect)
{
   QDomElement propertyElement = document.createElement("property");
   propertyElement.setAttribute("name", "geometry");
   QDomElement rectElement = document.createElement("rect");
   propertyElement.appendChild(rectElement);
   QDomElement xElement = document.createElement("x");
   setNodeValue(document, xElement, QString::number(rect.x()));
   rectElement.appendChild(xElement);
   QDomElement yElement = document.createElement("y");
   setNodeValue(document, yElement, QString::number(rect.y()));
   rectElement.appendChild(yElement);
   QDomElement widthElement = document.createElement("width");
   setNodeValue(document, widthElement, QString::number(rect.width()));
   rectElement.appendChild(widthElement);
   QDomElement heightElement = document.createElement("height");
   setNodeValue(document, heightElement, QString::number(rect.height()));
   rectElement.appendChild(heightElement);
   return propertyElement;
}

QDomElement UiPort::createMinSizeElement(QDomDocument document, const QRect & rect)
{
   QDomElement propertyElement = document.createElement("property");
   propertyElement.setAttribute("name", "minimumSize");
   QDomElement sizeElement = document.createElement("size");
   propertyElement.appendChild(sizeElement);
   QDomElement widthElement = document.createElement("width");
   setNodeValue(document, widthElement, QString::number(rect.width()));
   sizeElement.appendChild(widthElement);
   QDomElement heightElement = document.createElement("height");
   setNodeValue(document, heightElement, QString::number(rect.height()));
   sizeElement.appendChild(heightElement);
   return propertyElement;
}

#ifdef doku
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>578</width>
    <height>533</height>
   </rect>
  </property>
#endif

void UiPort::adjustWidgetGeometry(QDomDocument document, QDomNode & node, int x, int y, int width, int height)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "property") {
            QString propertyName = child.attribute("name");
            if (propertyName == "geometry") {
               adjustGeometry(document, child, x, y, width, height);
            }
         }
      }
   }
}

void UiPort::adjustGeometry(QDomDocument document, QDomNode & node, int x, int y, int width, int height)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "rect") {
            adjustRectangle(document, child, x, y, width, height);
         }
      }
   }
}

void UiPort::adjustRectangle(QDomDocument document, QDomNode & node, int x, int y, int width, int height)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "x") {
            if (x != -1) {
               QString nodeValue = getNodeValue(child);
               int newX = nodeValue.toInt();
               newX += x;
               setNodeValue(document, child, QString::number(newX));
            }
         } else if (tagName == "y") {
            if (y != -1) {
               QString nodeValue = getNodeValue(child);
               int newY = nodeValue.toInt();
               newY += y;
               setNodeValue(document, child, QString::number(newY));
            }
         } else if (tagName == "width") {
            if (width != -1) {
               QString nodeValue = getNodeValue(child);
               int newWidth = nodeValue.toInt();
               newWidth += width;
               setNodeValue(document, child, QString::number(newWidth));
            }
         } else if (tagName == "height") {
            if (height != -1) {
               QString nodeValue = getNodeValue(child);
               int newHeight = nodeValue.toInt();
               newHeight += height;
               setNodeValue(document, child, QString::number(newHeight));
            }
         }
      }
   }
}

void UiPort::updateWidgetGeometry(QDomDocument document, QDomNode & node, int yOffset)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "property") {
            QString propertyName = child.attribute("name");
            if (propertyName == "geometry") {
               updateGeometry(document, child, yOffset);
            }
         }
      }
   }
}

void UiPort::updateGeometry(QDomDocument document, QDomNode & node, int yOffset)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "rect") {
            updateY(document, child, yOffset);
         }
      }
   }
}

void UiPort::updateY(QDomDocument document, QDomNode & node, int yOffset)
{
   QDomNodeList nodeList = node.childNodes();
   int nodeCount = nodeList.count();
   int i = 0;
   for (i=0; i<nodeCount; i++) {
      QDomNode node = nodeList.item(i);
      QDomNode::NodeType nodeType = node.nodeType();
      if (nodeType == QDomNode::ElementNode) {
         QDomElement child = node.toElement();
         QString tagName = child.tagName();
         if (tagName == "y") {
            QString nodeValue = getNodeValue(child);
            int y = nodeValue.toInt();
            y += yOffset;
            setNodeValue(document, child, QString::number(y));
         }
      }
   }
}

#ifdef doku
      <widget class="QFrame" name="frame_2">
       <property name="geometry">
        <rect>
         <x>0</x>
         <y>0</y>
         <width>581</width>
         <height>16</height>
        </rect>
       </property>
       <property name="frameShape">
        <enum>QFrame::HLine</enum>
       </property>
       <property name="frameShadow">
        <enum>QFrame::Plain</enum>
       </property>
      </widget>
#endif
QDomNode UiPort::horizontalLine(QDomDocument document, int frameWidth)
{
   QDomElement widgetElement = document.createElement("widget");
   widgetElement.setAttribute("class", "QFrame");
   widgetElement.setAttribute("name", "hline");
   QDomElement geometryElement = document.createElement("property");
   widgetElement.appendChild(geometryElement);
   geometryElement.setAttribute("name", "geometry");
   QDomElement rectElement = document.createElement("rect");
   geometryElement.appendChild(rectElement);
   QDomElement xElement = document.createElement("x");
   setNodeValue(document, xElement, "0");
   rectElement.appendChild(xElement);
   QDomElement yElement = document.createElement("y");
   setNodeValue(document, yElement, "0");
   rectElement.appendChild(yElement);
   QDomElement widthElement = document.createElement("width");
   setNodeValue(document, widthElement, QString::number(frameWidth));
   rectElement.appendChild(widthElement);
   QDomElement heightElement = document.createElement("height");
   setNodeValue(document, heightElement, "4");
   rectElement.appendChild(heightElement);
   QDomElement shapeElement = document.createElement("property");
   widgetElement.appendChild(shapeElement);
   shapeElement.setAttribute("name", "frameShape");
   QDomElement enumElement = document.createElement("enum");
   shapeElement.appendChild(enumElement);
   setNodeValue(document, enumElement, "QFrame::HLine");
   QDomElement shadowElement = document.createElement("property");
   widgetElement.appendChild(shadowElement);
   shadowElement.setAttribute("name", "frameShadow");
   enumElement = document.createElement("enum");
   shadowElement.appendChild(enumElement);
   setNodeValue(document, enumElement, "QFrame::Plain");
   return widgetElement;
}

QDomNode UiPort::cloneNode(QDomNode sourceNode)
{
   return sourceNode;
}

