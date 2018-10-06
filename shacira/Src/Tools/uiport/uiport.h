
#ifndef _uiport_h_
#define _uiport_h_

#include <qfile.h>
#include <qstring.h>
#include <qdom.h>
#include <qvariant.h>
#include <qpalette.h>
#include <qcolor.h>
#include "cformbuilder.h"
#include "portingfile.h"
#include "forminformations.h"

class Colors;

enum UpdateOperations {NullOperation, AddNode, RemoveNode};

// UI4Transformation     : code is uic3 generated code
// PartialTransformation : code is uiport transformed code
//                         this parsestep is executed only for wizards
enum ParseSteps {UI4Transformation = 0, PartialTransformation = 1};

class UpdateEntry
{
public:
   UpdateEntry()
      : _updateOperation(NullOperation)
   {
   };
   UpdateEntry(const UpdateEntry & right)
      : _updateOperation(right._updateOperation), _parent(right._parent), _child(right._child)
   {
   };
   UpdateEntry(UpdateOperations updateOperation, QDomNode parent, QDomNode child)
      : _updateOperation(updateOperation), _parent(parent), _child(child)
   {
   };
   virtual ~UpdateEntry() {};
   inline UpdateOperations updateOperation() const {return _updateOperation;};
   inline QDomNode & parent() {return _parent;};
   inline const QDomNode & child() const {return _child;};
private:
   UpdateOperations _updateOperation;
   QDomNode _parent;
   QDomNode _child;
};
typedef list<UpdateEntry> UPDATE_LIST_T;

class UpdateList
{
public:
   UpdateList() {};
   virtual ~UpdateList() {};
   void clear()
   {
      _updateList.clear();
   };
   void update()
   {
      UPDATE_LIST_T::iterator i = _updateList.begin();
      while (i != _updateList.end()) {
         QDomNode & parent = (*i).parent();
         const QDomNode & child = (*i).child();
         UpdateOperations updateOperation = (*i).updateOperation();
         if (updateOperation == AddNode) {
            parent.appendChild(child);
         }
         i++;
      }
      i = _updateList.begin();
      while (i != _updateList.end()) {
         QDomNode & parent = (*i).parent();
         const QDomNode & child = (*i).child();
         UpdateOperations updateOperation = (*i).updateOperation();
         if (updateOperation == RemoveNode) {
            parent.removeChild(child);
         }
         i++;
      }
   };
   void add(QDomNode parent, QDomNode child)
   {
      UpdateEntry entry(AddNode, parent, child);
      _updateList.push_back(entry);
   };
   void remove(QDomNode parent, QDomNode child)
   {
      UpdateEntry entry(RemoveNode, parent, child);
      _updateList.push_back(entry);
   };
private:
   UPDATE_LIST_T _updateList;
};

class UiPort
{
public:
   UiPort()
      : _spacerNameIndex(0),
        _widgetNameIndex(0),
        _wizardPageIndex(1),
        _steps(1),
        _step(UI4Transformation)
   {
   };
   bool port(PortingFile * file);
   inline cFormBuilder & formBuilder() {return _formBuilder;};
protected:
   bool printDocument(QDomDocument document, const QString & outputFile);
   void addFormHeader(QDomDocument document, PortingFile * file);
   QString handleGroupBoxes(QDomDocument document, QDomNode node, const QString & widgetClass);

   // dom evaluation
   void registerWidgetClass(const QString & widgetClass);
   bool evaluate(QDomDocument document, QDomNode parentNode, PortingFile * file, const QString & targetWidgetClass, const QString & parentWidgetClass, QWidget * widget, Colors * colors);
   QString targetClass(const QString & parentClass, const QString & widgetClass, PortingFile * file);
   QString getNodeValue(const QDomNode node) const;
   QString getData(const QDomNode node);

   // resource management
   bool getImageData(QDomDocument document, QDomNode node, const QString & name, QString & imageData, QString & imageFormat, int & length);
   bool collectImages(QDomDocument document, const QDomNode parentNode, const QString & formId, PortingFile * file);
   void printUnmatchedImage(const QString & formId, const QString & imageName);
   void loadUnmatchedImageSpecifications(const QString & imagePath);

   // dom information
   QDomElement propertyElement(QDomDocument document, QDomNode node, const QString & propertyName) const;

   // dom manipulation
   bool setNodeValue(QDomDocument document, QDomNode node, const QString & value);
   bool removeNode(QDomDocument document, QDomNode parent, const QDomNode child, bool immediate = false);
   void addProperty(QDomDocument document, QDomNode node, const QString & propertyName, const QString & propertyType, const QString & propertyValue);
   void addIconSet(QDomDocument document, QDomNode node, const QString & resourceFileName, const QString & resourceName);
   void addCustomWidgetRefs(QDomDocument document, QDomNode node, const QString & nodeName);
   void addIncludes(QDomDocument document, QDomNode node, const QString & nodeName);
   void addResources(QDomDocument document, QDomNode node, const QString & resourceFile);
   void addPaletteElement(QDomDocument document, QDomNode node, Colors * colors);
   void addPaletteElement(QDomDocument document, QDomNode node, QPalette palette, const QString targetClass);
   void addColorGroups(QDomDocument document, QDomNode node, QPalette palette, QList<QPalette::ColorGroup> colorGroupList, QList<QPalette::ColorRole> colorRoleList);
   void addColorRoles(QDomDocument document, QDomNode node, QPalette palette, QPalette::ColorGroup colorGroup, QList<QPalette::ColorRole> colorRoleList);
   void addColor(QDomDocument document, QDomNode node, QColor color);
   void addSpacerItem(QDomDocument document, QDomNode node, bool vertical = true, int width = 20, int height = 20);
   void addSpacer(QDomDocument document, QDomNode node, bool vertical, int width, int height);
   void addSizeHint(QDomDocument document, QDomNode node, int width, int height);
   void addSizeElement(QDomDocument document, QDomNode node, int width, int height);
   void addPixmap(QDomDocument document, QDomNode node, const QString & resourceFileName, const QString & resourceString, const QString & targetClass);
   void addLineWrapMode(QDomDocument document, QDomNode node, const QString & enumValue);
   void addAlignment(QDomDocument document, QDomNode node, const QString & alignmentValue);
   void addIcon(QDomDocument document, QDomNode node, const QString & resourceFileName, const QString & resourceString, const QString & targetClass);
   void addIconState(QDomDocument document, QDomNode node, const QString & stateName, const QString & resourceString);
   void addIconSize(QDomDocument document, QDomNode node, int width, int height);

   // filters and adjustments
   bool nodeFilter(QDomDocument document, QDomNode parent, const QDomNode child, const QString & tagName);
   QString filterWordBreak(const QString & value);
   QString filterShape(const QString & value);
   bool adjustPalette(QDomDocument document, QDomNode node, QColor color, bool foreground, const QString targetClass);
   bool adjustLayout(QDomDocument document, QDomNode node, const QString & targetClass);
   bool adjustConnection(QDomDocument document, QDomNode node);
   void adjustSignal(QDomDocument document, QDomElement element, const QString & signal, const QString & sender);
   void adjustSlot(QDomDocument document, QDomElement element, const QString & slot, const QString & receiver);
   void splitEnumValue(const QString & enumValue, QString & nameSpace, QString & value);
   QString filterEnumValue(const QString & enumValue, QWidget * widget, const QString & newNameSpace = QString());
   QString filterSetValue(const QString & setValue, QWidget * widget, const QString & newNameSpace = QString());
   bool filterProperty(const QString & propertyName, const QString & targetClass) const;
   bool propertySet(QDomNode node, const QString & propertyName, const QString & propertyType = QString(), const QString & attributeName = QString(), const QString & attributeValue = QString()) const;
   QVariant propertyValue(QDomNode node) const;
   QPalette paletteValue(QDomNode node) const;
   QColor colorValue(QDomNode node) const;
   QString stringValue(QDomNode node) const;
   bool boolValue(QDomNode node) const;
   QString tagName(QDomNode node) const;
   QString nodeName(QDomNode node) const;
   QString className(QDomNode node) const;

   // wizards
   void adjustWizardPage(QDomDocument document, const QDomNode parentNode, const QDomNode element);
   void handleProperty(QDomDocument document, QDomNode parentNode, const QDomElement propertyElement, const QString parentClass, const QString targetClass, QWidget * targetWidget, PortingFile * file, Colors * colors);
   QString replaceAll(const QString & s, const QString &s1, const QString & s2) const;

private:
   cFormBuilder _formBuilder;
   map<QString,QString> _widgetClassMap;
   map<QString,QString> _widgetNameMap;
   int _spacerNameIndex;
   int _widgetNameIndex;
   int _wizardPageIndex;
   UpdateList _updateList;
   QString _currentFormId;
private:
   QString pluginSuperClass(const QString & className);
   inline void clearClassMap() {_widgetClassMap.clear();};
   inline void clearNameMap() {_widgetNameMap.clear();};
   inline bool widgetNameExists(const QString & widgetName) const
   {
      map<QString,QString>::const_iterator i = _widgetNameMap.find(widgetName);
      if (i == _widgetNameMap.cend()) {
         return false;
      } else {
         return true;
      }
   };
   inline QString widgetClass(const QString & widgetName) const
   {
      map<QString,QString>::const_iterator i = _widgetNameMap.find(widgetName);
      if (i == _widgetNameMap.cend()) {
         return "unknown";
      } else {
         return (*i).second;
      }
   };
   inline bool inherits(QWidget * widget, const QString & className) const
   {
      if (widget == NULL) {
         return false;
      } else {
         return  widget->inherits(className.toStdString().c_str());
      }
   };
   inline bool inherits(QWidget * widget, const QStringList & classList) const
   {
      QStringList::const_iterator i = classList.constBegin();
      while (i != classList.constEnd()) {
         if (inherits(widget, (*i)) ) {
            return true;
         }
         i++;
      }
      return false;
   };
   inline QStringList allowedClasses(const QString & propertyName) const
   {
      QStringList allowedClasses;
      if (propertyName == "frameShadow" ||
          propertyName == "frameShape") {
         allowedClasses << "QFrame";
      } else if (propertyName == "lineWidth") {
         allowedClasses << "QFrame";
      } else if (propertyName == "alignment") {
         allowedClasses << "QGroupBox";
         allowedClasses << "QLabel";
         allowedClasses << "QLineEdit";
         allowedClasses << "QProgressBar";
         allowedClasses << "QScrollArea";
      } else if (propertyName == "pixmap") {
         allowedClasses << "QLabel";
         allowedClasses << "QWizard";
      } else if (propertyName == "autoFormatting") {
         allowedClasses << "QTextEdit";
      } else {
         allowedClasses << "QWidget";
      }
      return allowedClasses;
   };
   inline bool propertyAllowed(QWidget * widget, const QString & propertyName) const
   {
      QStringList classList = allowedClasses(propertyName);
      return inherits(widget, classList);
   };
protected:
   int _steps;
   ParseSteps _step;
protected:
   QRect rectangle(QDomNode node) const;
   QRect geometry(QDomNode node) const;
   int geometryValue(QDomNode node, const QString & valueName) const;
   QDomElement createWidgetElement(QDomDocument document, const QString & widgetClass, const QRect & rect, QDomElement & element);
   QDomElement createGeometryElement(QDomDocument document, const QRect & rect);
   QDomElement createMinSizeElement(QDomDocument document, const QRect & rect);
   void adjustWidgetGeometry(QDomDocument document, QDomNode & node, int x, int y, int width, int height);
   void adjustGeometry(QDomDocument document, QDomNode & node, int x, int y, int width, int height);
   void adjustRectangle(QDomDocument document, QDomNode & node, int x, int y, int width, int height);
   void updateWidgetGeometry(QDomDocument document, QDomNode & node, int yOffset);
   void updateGeometry(QDomDocument document, QDomNode & node, int yOffset);
   void updateY(QDomDocument document, QDomNode & node, int yOffset);
   QDomNode horizontalLine(QDomDocument document, int frameWidth);
   QDomNode cloneNode(QDomNode sourceNode);
};

string logFileName();
string errorFileName();
void LogPrintf(const string & logFile, const char * fmt_str, ...);

#endif // _uiport_h_
