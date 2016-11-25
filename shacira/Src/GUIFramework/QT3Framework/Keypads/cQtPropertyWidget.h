
// ==========================================================================
// qt_property_widget.h
//
// Deklaration cQtProperty und davon abgeleiteten Klassen:
// - cQtPropertyWidget
//
// <Kurze Beschreibung was die Klasse so macht>
//
// cQtPropertyWidget
//   |
//   +- cQtProperty
//        |
//        +- iProperty
//
// ==========================================================================

#ifndef _cqtpropertywidget_h_
#define _cqtpropertywidget_h_


// System includes
#include <qwidget.h>

// Library includes (shared)

// Project includes
#include "iProperty.h"


// Forward declaration (instead of include)
class QObject;
class QWidget;
//class QLineEdit;


class cQtProperty : public iProperty
{
public:
   // Konstruktion/Destruktion
   cQtProperty(QObject *object) { _object = object; }
   virtual ~cQtProperty() { }

   // Reimplementierungen der Basisklasse
   virtual bool SetProperty(const QString & prop_name, int value);
   virtual bool GetProperty(const QString & prop_name, int &value);

   virtual bool SetProperty(const QString & prop_name, unsigned int value);
   virtual bool GetProperty(const QString & prop_name, unsigned int &value);

   virtual bool SetProperty(const QString & prop_name, bool value);
   virtual bool GetProperty(const QString & prop_name, bool &value);

   // Zusaetzliche Qt-spezifische Datentypen:
   virtual bool SetProperty(const QString & prop_name, const QString &value);
   virtual bool GetProperty(const QString & prop_name, QString &value);

protected:
   QObject *getObject() const { return _object; }

private:
   // Attribute
   QObject *_object;
};



class cQtPropertyWidget : public cQtProperty
{
public:
   // Konstruktion/Destruktion
   cQtPropertyWidget(QWidget *widget) : cQtProperty(widget) { }
   virtual ~cQtPropertyWidget() { }

   // Reimplementierung der virtuellen Funktionen der Basisklasse(n)
   virtual bool SetProperty(const QString & prop_name, int value);
   virtual bool GetProperty(const QString & prop_name, int &value);
   //virtual bool SetProperty(const QString & prop_name, unsigned int value);
   //virtual bool GetProperty(const QString & prop_name, unsigned int &value);
   virtual bool SetProperty(const QString & prop_name, bool value);
   virtual bool GetProperty(const QString & prop_name, bool &value);
   virtual bool SetProperty(const QString & prop_name, const QString &value);
   virtual bool GetProperty(const QString & prop_name, QString &value);

protected:
   //QWidget *getWidget() const { return (QWidget*)getObject(); }


private:
   // Hilfsfunktionen: Widget mit bestimmtem Namen im Widget suchen
   bool findChild(const QString &prop_name, QObject **child, QString &child_prop);
};


/*
class cQtPropertyLabel : public cQtProperty
{
public:
   // Konstruktion/Destruktion
   cQtPropertyLabel(QLabel *widget) { _widget = widget; }
   virtual ~cQtPropertyLabel() { }

   // bool Properties:
   // "shown" - Widget wird angezeigt oder nicht
   virtual bool setProperty(const QString & prop_name, bool value);

   // QString Properties:
   // "text" (oder "") - Angezeigter Text
   virtual bool setProperty(const QString & prop_name, const QString &value);

private:
   // Attribute
   QLabel *_widget;
};



class cQtPropertyLineEdit : public cQtProperty
{
public:
   // Konstruktion/Destruktion
   cQtPropertyLineEdit(QLineEdit *widget) { _widget = widget; }
   virtual ~cQtPropertyLineEdit() { }

private:
   // Attribute
   QLineEdit *_widget;
};
*/

#endif // qt_property_widget_h_included
