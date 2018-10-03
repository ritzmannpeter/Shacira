
#include "generator.h"

#include <qlabel.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qspinbox.h>
#include <qframe.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qtabwidget.h>
#include <qgroupbox.h>
#include <qlcdnumber.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlistview.h>
#include <qbuttongroup.h>

#include "CGroupSelectButton.h"
#include "CWidget.h"
#include "CWidgetStack.h"
#include "CComposedStack.h"
#include "CTabWidget.h"
#include "CFrame.h"
#include "CFixTExt.h"
#include "CInfoLabel.h"
#include "cProtocolWindow.h"
#include "CGroupBox.h"
#include "CButtonGroup.h"
#include "CActValue.h"
#include "CListView.h"
#include "CReqValue.h"
#include "CToolButton.h"
#include "CPushButton.h"
#include "CStateButton.h"
#include "CRadioButton.h"
#include "CCheckBox.h"
#include "CComboBox.h"
#include "CProcGraphic.h"
#include "CRingGraphic.h"
#include "CCoordSystem.h"
#include "CVideo.h"
#include "CAlarmWidget.h"
#include "CTextEdit.h"
#include "CTable.h"
#include "CScrollBar.h"
#include "CSlider.h"
#include "CSpinBox.h"
#include "CProgressBar.h"
#include "CTime.h"
#include "CDate.h"
#include "CDateTime.h"
#include "CVirtualKeyboard.h"
#include "CAppFrame.h"

cGenerator::cGenerator()
{
}

cGenerator::~cGenerator()
{
}

QWidget * cGenerator::convert(const QString & fileName)
{
   QWidget * widget = loadFromUiFile(fileName);
   if (widget != NULL) {
      QDomDocument document;
      QDomElement root = document.createElement("ui");
      root.setAttribute("version", "4.0");
      document.appendChild(root);
      QDomElement form = document.createElement("class");
      setNodeValue(document, form, "Form");
      root.appendChild(form);
      QObject * object = static_cast<QWidget*>(widget);
      if (generate(document, root, object)) {
         QString outputFileName = "e:\\temp\\" + fileName;
         QFile file(outputFileName);
         file.open(IO_WriteOnly);
         if (file.isOpen()) {
            QString preamble = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            QString xml = document.toString();
            file.writeBlock(preamble, preamble.length());
            file.writeBlock(xml, xml.length());
            file.close();
            return widget;
         }
      }
   }
   return NULL;
}

QWidget * cGenerator::loadFromUiFile(const QString & fileName) const
{
   QWidget * widget = QWidgetFactory::create(fileName);
   return widget;
}

bool cGenerator::generate(QDomDocument & document, QDomElement & parent, QObject * object)
{
   bool success = false;
   if (object->isWidgetType()) {
       QWidget * widget = static_cast<QWidget*>(object);
       QString name = widget->name();
       success = generateWidget(document, parent, widget);
   } else {
       if (object->inherits("QVBoxLayout")) {
         QVBoxLayout * vboxLayout = static_cast<QVBoxLayout*>(object);
         success = generateLayout(document, parent, *vboxLayout);
       } else if (object->inherits("QHBoxLayout")) {
         QHBoxLayout * hboxLayout = static_cast<QHBoxLayout*>(object);
         success = generateLayout(document, parent, *hboxLayout);
       } else if (object->inherits("QGridLayout")) {
         QGridLayout * gridLayout = static_cast<QGridLayout*>(object);
         success = generateLayout(document, parent, *gridLayout);
       } else if (object->inherits("QLayout")) {
         QLayout * layout = static_cast<QLayout*>(object);
         success = generateLayout(document, parent, layout);
       } else {
          success = true;
       }
   }
   return success;
}

void cGenerator::processObjectList(QDomDocument & document, QDomElement & parent, QObject * object)
{
   const QObjectList * children = object->children();
   if (children != NULL) {
      QObjectList::const_iterator i = children->constBegin();
      while (i != children->constEnd()) {
         QObject * child = (*i);
         bool success = generate(document, parent, child);
         if (!success) {
            int dummy = 0;
         }
         i++;
      }
   }
}

bool cGenerator::generateWidget(QDomDocument & document, QDomElement & parent, QWidget * widget)
{
   QString className = widget->className();
   QString targetClassName = this->targetClassName(className);
   if (targetClassName.isEmpty()) {
      return false;
   } else {
      QDomElement element = document.createElement("widget");
      if (generateWidget(document, element, widget, targetClassName)) {
         parent.appendChild(element);
         processObjectList(document, element, widget);
         return true;
      } else {
         return false;
      }
   }
}

bool cGenerator::generateWidget(QDomDocument & document, QDomElement & element, QWidget * widget, const QString targetClassName)
{
   element.setAttribute("class", targetClassName);
   element.setAttribute("name", widget->name());
   addProperties(document, element, widget);
   return true;
}

bool cGenerator::generateLayout(QDomDocument & document, QDomElement & parent, QVBoxLayout & layout)
{
// not supported
return true;
   QDomElement layoutElement = document.createElement("layout");
   layoutElement.setAttribute("class", "VBoxLayout");
   parent.appendChild(layoutElement);
   QLayoutIterator it = layout.iterator();
   QLayoutItem * child = NULL;
   while ((child = it.current()) != NULL ) {
      QDomElement itemElement = document.createElement("item");
      layoutElement.appendChild(itemElement);
      QWidget * widget = child->widget();
      QSpacerItem * spacerItem = child->spacerItem();
      QLayout * subLayout = child->layout();
      if (widget != NULL) {
         generateWidget(document, itemElement, widget);
      }
      if (spacerItem != NULL) {
         generateSpacer(document, itemElement, spacerItem);
      }
      if (subLayout != NULL) {
         generateLayout(document, itemElement, subLayout);
      }
      ++it;
   }
   return true;
}

bool cGenerator::generateLayout(QDomDocument & document, QDomElement & parent, QHBoxLayout & layout)
{
// not supported
return true;
   QDomElement layoutElement = document.createElement("layout");
   layoutElement.setAttribute("class", "HBoxLayout");
   parent.appendChild(layoutElement);
   QLayoutIterator it = layout.iterator();
   QLayoutItem * child = NULL;
   while ((child = it.current()) != NULL ) {
      QDomElement itemElement = document.createElement("item");
      layoutElement.appendChild(itemElement);
      QWidget * widget = child->widget();
      QSpacerItem * spacerItem = child->spacerItem();
      QLayout * subLayout = child->layout();
      if (widget != NULL) {
         generateWidget(document, itemElement, widget);
      }
      if (spacerItem != NULL) {
//         generateSpacer(document, itemElement, spacerItem);
      }
      if (subLayout != NULL) {
         generateLayout(document, itemElement, subLayout);
      }
      ++it;
   }
   return true;
}

bool cGenerator::generateLayout(QDomDocument & document, QDomElement & parent, QGridLayout & layout)
{
   return true;
}

bool cGenerator::generateLayout(QDomDocument & document, QDomElement & parent, QLayout * layout)
{
   return true;
}

bool cGenerator::generateSpacer(QDomDocument & document, QDomElement & parent, QSpacerItem * spacerItem)
{
   return true;
}

void addStringProperty(QDomDocument & document, QDomElement & element, const QString & name, const QString & value, bool translate)
{
   QDomElement propertyNode = document.createElement("property");
   propertyNode.setAttribute("name", name);
   QDomElement stringNode;
   if (translate) {
      stringNode = document.createElement("string");
   } else {
      stringNode = document.createElement("cstring");
   }
   propertyNode.appendChild(stringNode);
   QDomText textNode = document.createTextNode(value);
   stringNode.appendChild(textNode);
   element.appendChild(propertyNode);
}

void cGenerator::setNodeValue(QDomDocument & document, QDomElement & parent, int intValue)
{
   QString value;
   value.setNum(intValue);
   QDomText textNode = document.createTextNode(value);
   parent.appendChild(textNode);
}

void cGenerator::setNodeValue(QDomDocument & document, QDomElement & parent, const QString & value)
{
   QDomText textNode = document.createTextNode(value);
   parent.appendChild(textNode);
}

void cGenerator::setGeometry(QDomDocument & document, QDomElement & parent, const QRect & geometry)
{
   QDomElement element = document.createElement("property");
   element.setAttribute("name", "geometry");
   QDomElement rect = document.createElement("rect");
   QDomElement x = document.createElement("x");
   setNodeValue(document, x, geometry.x());
   QDomElement y = document.createElement("y");
   setNodeValue(document, y, geometry.y());
   QDomElement width = document.createElement("width");
   setNodeValue(document, width, geometry.width());
   QDomElement height = document.createElement("height");
   setNodeValue(document, height, geometry.height());
   rect.appendChild(x);
   rect.appendChild(y);
   rect.appendChild(width);
   rect.appendChild(height);
   element.appendChild(rect);
   parent.appendChild(element);
}

void cGenerator::addStringProperty(QDomDocument & document, QDomElement & element, const QString & name, const QString & value, bool translate)
{
   QDomElement propertyNode = document.createElement("property");
   propertyNode.setAttribute("name", name);
   QDomElement stringNode;
   if (translate) {
      stringNode = document.createElement("string");
   } else {
      stringNode = document.createElement("cstring");
   }
   propertyNode.appendChild(stringNode);
   QDomText textNode = document.createTextNode(value);
   stringNode.appendChild(textNode);
   element.appendChild(propertyNode);
}

QString cGenerator::targetClassName(const QString & sourceClassName) const
{
   if (sourceClassName == "QLabel") {
      return "CFixText";
   } else if (sourceClassName == "QPushButton") {
      return "CPushButton";
   } else if (sourceClassName == "QButtonGroup") {
      return "CButtonGroup";
   } else if (sourceClassName == "QToolButton") {
      return "CToolButton";
   } else if (sourceClassName == "QSpinBox") {
      return "CSpinBox";
   } else if (sourceClassName == "QComboBox") {
      return "CComboBox";
   } else if (sourceClassName == "QListView") {
      return "CListView";
   } else if (sourceClassName == "QLineEdit") {
      return "CLineEdit";
   } else if (sourceClassName == "QTextEdit") {
      return "CTextEdit";
   } else if (sourceClassName == "QGroupBox") {
      return "CGroupBox";
   } else if (sourceClassName == "QCheckBox") {
      return "CCheckBox";
   } else if (sourceClassName == "QLCDNumber") {
      return "QLCDNumber";
   } else if (sourceClassName == "QTabWidget") {
      return "CTabWidget";
   } else if (sourceClassName == "QFrame") {
      return "CFrame";
   } else if (sourceClassName == "QWidgetStack") {
      return "CWidgetStack";
   }
   return sourceClassName;
}

void cGenerator::addPropertyNames(QMetaObject * metaObject, QStringList & nameList)
{
   QStrList propertyNameList = metaObject->propertyNames();
   for (QStrList::Iterator it = propertyNameList.begin(); it != propertyNameList.end(); ++it) {
      QString propertyName = *it;
      nameList.push_back(propertyName);
   }
   QMetaObject * superClass = metaObject->superClass();
   if (superClass != NULL) {
      addPropertyNames(superClass, nameList);
   }
}

QStringList cGenerator::propertyNameList(QWidget * widget)
{
   QStringList propertyNameList;
   QObject * object = static_cast<QObject*>(widget);
   QMetaObject * metaObject = object->metaObject();
   addPropertyNames(metaObject, propertyNameList);
   return propertyNameList;
}

void cGenerator::addProperty(QDomDocument & document, QDomElement & parent, const QString propertyName, const QVariant & propertyValue)
{
   if (!propertyValue.isValid()) {
      int dummy = 0;
   } else {
      QDomElement propertyNode = document.createElement("property");
      propertyNode.setAttribute("name", propertyName);
      QString text = propertyValue.toString();
      if (!text.isEmpty()) {
         propertyNode.setAttribute("value", propertyValue.toString());
      }
      parent.appendChild(propertyNode);
   }
}

void cGenerator::addProperties(QDomDocument & document, QDomElement & parent, QWidget * widget)
{
   QObject * object = static_cast<QObject*>(widget);
   QStringList nameList = propertyNameList(widget);
   for (QStringList::Iterator it = nameList.begin(); it != nameList.end(); ++it) {
      bool handled = true;
      QString propertyName = *it;
      QVariant value = object->property(propertyName);
      QVariant::Type type = value.type();
      if (!value.isNull()) {
         switch (type) {
         case QVariant::Invalid:
            break;
         case QVariant::BitArray:
            {
               handled = false;
            }
            break;
         case QVariant::ByteArray:
            {
               handled = false;
            }
            break;
         case QVariant::Bitmap:
            {
               handled = false;
            }
            break;
         case QVariant::Bool:
            {
               handled = false;
            }
            break;
         case QVariant::Brush:
            {
               handled = false;
            }
            break;
         case QVariant::Color:
            {
               handled = false;
            }
            break;
         case QVariant::ColorGroup:
            {
               handled = false;
            }
            break;
         case QVariant::Cursor:
            {
               handled = false;
            }
            break;
         case QVariant::Date:
            {
               handled = false;
            }
            break;
         case QVariant::DateTime:
            {
               handled = false;
            }
            break;
         case QVariant::Double:
            {
               handled = false;
            }
            break;
         case QVariant::Font:
            {
               handled = false;
            }
            break;
         case QVariant::IconSet:
            {
               QIconSet iconSet = value.toIconSet();
//               addProperty(document, parent, propertyName, iconSet);
            }
            break;
         case QVariant::Image:
            {
               QImage image = value.toImage();
//               addProperty(document, parent, propertyName, image);
            }
            break;
         case QVariant::Int:
            {
            }
            break;
         case QVariant::KeySequence:
            {
               handled = false;
            }
            break;
         case QVariant::List:
            {
               handled = false;
            }
            break;
         case QVariant::LongLong:
            {
               handled = false;
            }
            break;
         case QVariant::ULongLong:
            {
               handled = false;
            }
            break;
         case QVariant::Map:
            {
               handled = false;
            }
            break;
         case QVariant::Palette:
            {
               QPalette palette = value.toPalette();
//               addProperty(document, parent, propertyName, palette);
            }
            break;
         case QVariant::Pen:
            {
               handled = false;
            }
            break;
         case QVariant::Pixmap:
            {
               QPixmap pixmap = value.toPixmap();
               addProperty(document, parent, propertyName, pixmap);
            }
            break;
         case QVariant::Point:
            {
               QPoint point = value.toPoint();
//               addProperty(document, parent, propertyName, point);
            }
            break;
         case QVariant::PointArray:
            {
               handled = false;
            }
            break;
         case QVariant::Rect:
            {
               QRect rectangle = value.toRect();
               if (propertyName == "geometry") {
                  setGeometry(document, parent, rectangle);
               } else {
//                  addProperty(document, parent, propertyName, rectangle);
               }
            }
            break;
         case QVariant::Region:
            {
               QRegion region = value.toRegion();
//               addProperty(document, parent, propertyName, region);
            }
            break;
         case QVariant::Size:
            {
               handled = false;
            }
            break;
         case QVariant::SizePolicy:
            {
            }
            break;
         case QVariant::String:
            {
               QString text = value.toString();
               addStringProperty(document, parent, propertyName, text, true);
//               addProperty(document, parent, propertyName, text);
            }
            break;
         case QVariant::CString:
            {
               QCString text = value.toCString();
               addStringProperty(document, parent, propertyName, text, false);
//               addProperty(document, parent, propertyName, text);
            }
            break;
         case QVariant::StringList:
            {
               handled = false;
            }
            break;
         case QVariant::Time:
            {
               handled = false;
            }
            break;
         case QVariant::UInt:
            {
               handled = false;
            }
            break;
         }
         if (!handled) {
//            addProperty(document, parent, propertyName, value);
         }
      }
   }
}

