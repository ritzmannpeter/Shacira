

#include "generation.h"
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
#ifdef lassma
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#include ".h"
#endif

#define USE_PLUGIN

QString widgetName(const QString & name)
{
   return name;
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

void setNodeValue(QDomDocument & document, QDomElement & parent, int intValue)
{
   QString value;
   value.setNum(intValue);
   QDomText textNode = document.createTextNode(value);
   parent.appendChild(textNode);
}

void setNodeValue(QDomDocument & document, QDomElement & parent, const QString & value)
{
   QDomText textNode = document.createTextNode(value);
   parent.appendChild(textNode);
}

void setGeometry(QDomDocument & document, QDomElement & parent, const QRect & geometry)
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

void copyProperties(QDomDocument & document, QDomElement & element, QWidget * widget)
{
   QRect geometry = widget->geometry();
   setGeometry(document, element, geometry);
}

void addStandardProperties(QDomDocument & document, QDomElement & element, QWidget * widget)
{
return;
   addStringProperty(document, element, "comment", "", false);
   addStringProperty(document, element, "darkFuncRef", "", false);
   addStringProperty(document, element, "helpId1", "", false);
   addStringProperty(document, element, "helpId2", "", false);
   addStringProperty(document, element, "initFuncRef", "", false);
}

#include <qwidget.h>
#include <qmetaobject.h>
#include <qvariant.h>
#include <qdir.h>
#include <qfile.h>
#include <qstringlist.h>
#include <qwidgetfactory.h>
#include "generation.h"

void addPropertyNames(QMetaObject * metaObject, QStringList & nameList)
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

QStringList propertyNameList(QWidget * widget)
{
   QStringList propertyNameList;
   QObject * object = static_cast<QObject*>(widget);
   QMetaObject * metaObject = object->metaObject();
   addPropertyNames(metaObject, propertyNameList);
   return propertyNameList;
}

void addProperty(QDomDocument & document, QDomElement & parent, const QString propertyName, const QVariant & propertyValue)
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

void addProperties(QDomDocument & document, QDomElement & parent, QWidget * widget)
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

void Generate(QDomDocument & document, QDomElement & element, QWidget * widget, const QString & className)
{
   element.setAttribute("class", className);
   element.setAttribute("name", widgetName(widget->name()));
   addProperties(document, element, widget);
}

void Generate(QDomDocument & document, QDomElement & element, const QTabWidget & w)
{
   int tabCount = w.count();
   int i = 0;
   for (i=0; i<tabCount; i++) {
      QWidget * parent = (QWidget*)w.parent();
      QString parentName;
      if (parent != NULL) {
         parentName = parent->name();
      }
      QWidget * page = w.page(i);
      GenerateWidget(page, false);
      int dummy = 0;
   }
}

void Generate(QDomDocument & document, QDomElement & element, const QComboBox & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CComboBox");
#else
   element.setAttribute("class", "QComboBox");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QListView & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CListView");
#else
   element.setAttribute("class", "QTreeWidget");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QLineEdit & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CLineEdit");
#else
   element.setAttribute("class", "QLineEdit");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QTextEdit & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CTextEdit");
#else
   element.setAttribute("class", "QTextEdit");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QGroupBox & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CGroupBox");
#else
   element.setAttribute("class", "QGroupBox");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStringProperty(document, element, "title", w.title(), true);
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QCheckBox & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CCheckBox");
#else
   element.setAttribute("class", "QCheckBox");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStringProperty(document, element, "text", w.text(), true);
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QLabel & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CLabel");
#else
   element.setAttribute("class", "QLabel");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStringProperty(document, element, "text", w.text(), true);
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QPushButton & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CPushButton");
#else
   element.setAttribute("class", "QPushButton");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStringProperty(document, element, "text", w.text(), true);
   addStandardProperties(document, element, (QWidget*)&w);
   addStringProperty(document, element, "buttonFuncRef", "", false);
}

void Generate(QDomDocument & document, QDomElement & element, const QToolButton & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CToolButton");
#else
   element.setAttribute("class", "QToolButton");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStringProperty(document, element, "text", w.text(), true);
   addStandardProperties(document, element, (QWidget*)&w);
   addStringProperty(document, element, "buttonFuncRef", "", false);
}

void Generate(QDomDocument & document, QDomElement & element, const QSpinBox & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CSpinBox");
#else
   element.setAttribute("class", "QSpinBox");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QLCDNumber & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CLCDNumber");
#else
   element.setAttribute("class", "QLCDNumber");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QFrame & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CFrame");
#else
   element.setAttribute("class", "QFrame");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

void Generate(QDomDocument & document, QDomElement & element, const QButtonGroup & w)
{
#ifdef USE_PLUGIN
   element.setAttribute("class", "CButtonGroup");
#else
   element.setAttribute("class", "QButtonGroup");
#endif
   element.setAttribute("name", widgetName(w.name()));
   addStandardProperties(document, element, (QWidget*)&w);
}

#define INIT_WIDGET(type,widget) \
   type * w = static_cast<type*>(widget); \
   Generate(document, element, w, widget->className());

void Generate(QDomDocument & document, QDomElement & parent, QWidget * widget)
{
   QCString className = widget->className();
   if (className == "CVarDimension") {
      return;
   }
   if (className == "MHeatAct") {
      return;
   }
   if (className == "CInfoLabel") {
      return;
   }
   if (className == "MIndText") {
      return;
   }
   bool ignore = false;
   QDomElement element = document.createElement("widget");
   if (widget->inherits("CAppFrame")) {
      INIT_WIDGET(CAppFrame,widget)
   } else if (widget->inherits("CWidgetStack")) {
      INIT_WIDGET(CWidgetStack,widget)
   } else if (widget->inherits("CComposedStack")) {
      INIT_WIDGET(CComposedStack,widget)
   } else if (widget->inherits("CTabWidget")) {
      INIT_WIDGET(CTabWidget,widget)
   } else if (widget->inherits("CFrame")) {
      INIT_WIDGET(CFrame,widget)
   } else if (widget->inherits("CFixText")) {
      INIT_WIDGET(CFixText,widget)
   } else if (widget->inherits("CInfoLabel")) {
      INIT_WIDGET(CInfoLabel,widget)
   } else if (widget->inherits("CProtocolWindow")) {
      INIT_WIDGET(CProtocolWindow,widget)
   } else if (widget->inherits("CGroupBox")) {
      INIT_WIDGET(CGroupBox,widget)
   } else if (widget->inherits("CButtonGroup")) {
      INIT_WIDGET(CButtonGroup,widget)
   } else if (widget->inherits("CActValue")) {
      INIT_WIDGET(CActValue,widget)
   } else if (widget->inherits("CListView")) {
      INIT_WIDGET(CListView,widget)
   } else if (widget->inherits("CReqValue")) {
      INIT_WIDGET(CReqValue,widget)
   } else if (widget->inherits("CGroupSelectButton")) {
      INIT_WIDGET(CGroupSelectButton,widget)
   } else if (widget->inherits("CToolButton")) {
      INIT_WIDGET(CToolButton,widget)
   } else if (widget->inherits("CPushButton")) {
      INIT_WIDGET(CPushButton,widget)
   } else if (widget->inherits("CStateButton")) {
      INIT_WIDGET(CStateButton,widget)
   } else if (widget->inherits("CRadioButton")) {
      INIT_WIDGET(CRadioButton,widget)
   } else if (widget->inherits("CCheckBox")) {
      INIT_WIDGET(CCheckBox,widget)
   } else if (widget->inherits("CComboBox")) {
      INIT_WIDGET(CComboBox,widget)
   } else if (widget->inherits("CTable")) {
      INIT_WIDGET(CTable,widget)
   } else if (widget->inherits("CProcGraphic")) {
      INIT_WIDGET(CProcGraphic,widget)
   } else if (widget->inherits("CRingGraphic")) {
      INIT_WIDGET(CRingGraphic,widget)
   } else if (widget->inherits("CCoordSystem")) {
      INIT_WIDGET(CCoordSystem,widget)
   } else if (widget->inherits("CVideo")) {
      INIT_WIDGET(CVideo,widget)
   } else if (widget->inherits("CAlarmWidget")) {
      INIT_WIDGET(CAlarmWidget,widget)
   } else if (widget->inherits("CTextEdit")) {
      INIT_WIDGET(CTextEdit,widget)
   } else if (widget->inherits("CScrollBar")) {
      INIT_WIDGET(CScrollBar,widget)
   } else if (widget->inherits("CSlider")) {
      INIT_WIDGET(CSlider,widget)
   } else if (widget->inherits("CSpinBox")) {
      INIT_WIDGET(CSpinBox,widget)
   } else if (widget->inherits("CProgressBar")) {
      INIT_WIDGET(CProgressBar,widget)
   } else if (widget->inherits("CTime")) {
      INIT_WIDGET(CTime,widget)
   } else if (widget->inherits("CDate")) {
      INIT_WIDGET(CDate,widget)
   } else if (widget->inherits("CDateTime")) {
      INIT_WIDGET(CDateTime,widget)
   } else if (widget->inherits("CVirtualKeyboard")) {
      INIT_WIDGET(CVirtualKeyboard,widget)
   } else if (widget->inherits("CWidget")) {
      INIT_WIDGET(CWidget,widget)
   } else {
      if (widget->inherits("QLabel")) {
         INIT_WIDGET(QLabel,widget)
      } else if (widget->inherits("QPushButton")) {
         INIT_WIDGET(QPushButton,widget)
      } else if (widget->inherits("QButtonGroup")) {
         INIT_WIDGET(QButtonGroup,widget)
      } else if (widget->inherits("QToolButton")) {
         INIT_WIDGET(QToolButton,widget)
      } else if (widget->inherits("QSpinBox")) {
         INIT_WIDGET(QSpinBox,widget)
      } else if (widget->inherits("QComboBox")) {
         INIT_WIDGET(QComboBox,widget)
      } else if (widget->inherits("QListView")) {
         INIT_WIDGET(QListView,widget)
      } else if (widget->inherits("QLineEdit")) {
         INIT_WIDGET(QLineEdit,widget)
      } else if (widget->inherits("QTextEdit")) {
         INIT_WIDGET(QTextEdit,widget)
      } else if (widget->inherits("QGroupBox")) {
         INIT_WIDGET(QGroupBox,widget)
      } else if (widget->inherits("QCheckBox")) {
         INIT_WIDGET(QCheckBox,widget)
      } else if (widget->inherits("QLCDNumber")) {
         INIT_WIDGET(QLCDNumber,widget)
      } else if (widget->inherits("QTabWidget")) {
         INIT_WIDGET(QTabWidget,widget)
      } else if (widget->inherits("QFrame")) {
         INIT_WIDGET(QFrame,widget)
      } else {
         QString classname = widget->className();
         QString widgetname = widgetName(widget->name());
         element.setAttribute("class", "QWidget");
         element.setAttribute("name", (const char*)widgetName);
      }
   }
//   copyProperties(document, element, widget);
   parent.appendChild(element);
   if (!ignore) {
      const QObjectList * children = widget->children();
      if (children != NULL) {
         QObjectList::const_iterator i = children->begin();
         while (i != children->end()) {
            QObject * child = (*i);
            Generate(document, element, child);
            i++;
         }
      } else {
         int dummy = 0;
      }
   }
}

void Generate(QDomDocument & document, QDomElement & parent, QObject * object)
{
   if (object == NULL) {
      return;
   } else {
      if (object->isWidgetType()) {
         QWidget * widget = static_cast<QWidget*>(object);
         QString name = widget->name();
         const char * widgetName = name;
         if (strncmp(widgetName, "qt_", 3) == 0) {
            int dummy = 0;
         } else {
            Generate(document, parent, widget);
         }
      } else {
         if (object->inherits("QLayout")) {
            int dummy = 0;
         }
      }
   }
}

#include <string>
using namespace std;
QString toWindows(const QString & text)
{
   QString windowsText;
   int textLen = text.length();
   int i = 0;
   for (i=0; i<textLen; i++) {
      char c = text[i];
      if (c == 0xa) {
         windowsText += ' ';
         windowsText += 0xd;
         windowsText += c;
      } else {
         windowsText += c;
      }
   }
   windowsText = windowsText.utf8();
   return windowsText;
}

void createNames(QWidget * widget, QString & groupId, QString & pageId, QString & stackId, QString & fileName, QString & pageName, bool mainWidget)
{
   QString missing;
   QString widgetName = widget->name();
   if (!mainWidget) {
      QString parentName;
      if (widget->parent() != NULL) {
         parentName = widget->parent()->name();
         widgetName = QString("T") + parentName + "_" + widgetName;
      }
   }
   groupId;
   pageId;
   stackId = "main";
   if (widgetName == "Base_HFenster") {
      groupId = "vis";
      pageId = "main";
   } else if (widgetName == "Base_Konfig_Fenster") {
      groupId = "conf";
      pageId = "main";
   } else if (widgetName == "Base_BV_Fenster") {
      groupId = "vis";
      pageId = "camera";
   } else if (widgetName == "Base_ScreenEdit") {
      groupId = "vis";
      pageId = "edit";
   } else if (widgetName == "Base_expert") {
      groupId = "vis";
      pageId = "expert";
   } else if (widgetName == "machine off") {
      groupId = "plc";
      pageId = "machine";
   } else if (widgetName == "plc_adjust") {
      groupId = "plc";
      pageId = "adjust";
   } else if (widgetName == "Base_Test_Fenster") {
      groupId = "plc";
      pageId = "test";
   } else if (widgetName == "Base_Statistik_Fenster") {
      groupId = "stat";
      pageId = "general";
   } else if (widgetName == "0") {
      groupId = "stat";
      pageId = "camera";
   } else if (widgetName == "bv_adjust") {
      groupId = "vis";
      pageId = "camadjust";
   } else if (widgetName == "TBase_Konfig_Fenster_tab") {
      groupId = "conf";
      pageId = "general";
   } else if (widgetName == "TBase_Konfig_Fenster_tab_2") {
      groupId = "conf";
      pageId = "user";
   } else if (widgetName == "TBase_Konfig_Fenster_tab_3") {
      groupId = "conf";
      pageId = "machine";
   } else if (widgetName == "TBase_Konfig_Fenster_tab_4") {
      groupId = "conf";
      pageId = "io";
   } else if (widgetName == "TBase_Konfig_Fenster_TabPage") {
      groupId = "conf";
      pageId = "scripts";
   } else if (widgetName == "TBase_Konfig_Fenster_TabPage_2") {
      groupId = "conf";
      pageId = "library";
   } else if (widgetName == "TBase_Konfig_Fenster_TabPage_3") {
      groupId = "conf";
      pageId = "misc";
   } else if (widgetName == "TStat_gbox2_0") {
      groupId = "stat";
      pageId = "camera";
   } else if (widgetName == "TStat_gbox2_tab2") {
      groupId = "stat";
      pageId = "camera1";
   } else if (widgetName == "TStat_gbox2_tab3") {
      groupId = "stat";
      pageId = "camera2";
   } else if (widgetName == "TStat_gbox2_tab4") {
      groupId = "stat";
      pageId = "camera3";
   } else if (widgetName == "Tbv_adjust_tab1") {
      groupId = "vis";
      pageId = "cam1adjust";
   } else if (widgetName == "Tbv_adjust_tab2") {
      groupId = "vis";
      pageId = "cam2adjust";
   } else if (widgetName == "Tbv_adjust_tab3") {
      groupId = "vis";
      pageId = "cam3adjust";
   } else {
      groupId = "missing";
      pageId = widgetName;
      missing += widgetName;
   }
   widgetName = pageName = groupId + "_" + pageId;
   fileName = widgetName + ".ui";
   if (missing.length() > 0) {
      const char * wn = widgetName;
      const char * m = missing;
      FILE * stream = fopen("e:/temp/missing", "a");
      if (stream != NULL) {
         fprintf(stream, "%s,\n", (const char *)missing);
         fclose(stream);
      }
   }
}

void GenerateWidget(QWidget * widget, bool mainWidget)
{
   QString groupId;
   QString pageId;
   QString stackId;
   QString pageName;
   QString fileName;
   QString widgetName = widget->name();
   createNames(widget, groupId, pageId, stackId, fileName, pageName, mainWidget);

   QDomDocument document;
   QDomElement root = document.createElement("ui");
   root.setAttribute("version", "4.0");
   document.appendChild(root);

   QDomElement form = document.createElement("class");
//   setNodeValue(document, form, fileName);
   setNodeValue(document, form, "Form");
   root.appendChild(form);

#ifdef lassma
   QDomElement rootWidget = document.createElement("widget");
   rootWidget.setAttribute("class", "CPage");
   rootWidget.setAttribute("name", widgetName);
   QRect geometry;
   geometry.setHeight(720);
   geometry.setWidth(1024);
   setGeometry(document, rootWidget, geometry);
   addStringProperty(document, rootWidget, "groupId", groupId, false);
   addStringProperty(document, rootWidget, "pageId", pageId, false);
   addStringProperty(document, rootWidget, "stackId", stackId, false);
   root.appendChild(rootWidget);

   QDomElement layout = document.createElement("layout");
   layout.setAttribute("class", "QVBoxLayout");
   layout.setAttribute("name", "rootLayout");
   rootWidget.appendChild(layout);

   QDomElement layoutItem = document.createElement("item");
   layout.appendChild(layoutItem);
#endif

   Generate(document, root, (QObject*)widget);
   fileName = "e:\\temp\\" + fileName;
   QFile file(fileName);
   file.open(IO_WriteOnly);
   if (file.isOpen()) {
      QString preamble = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
      QString xml = document.toString();
      xml = toWindows(xml);
      file.writeBlock(preamble, preamble.length());
      file.writeBlock(xml, xml.length());
      file.close();
   }
}


