
#ifndef _generation_h_
#define _generation_h_

#include <qstring.h>
#include <qfile.h>
#include <qobject.h>
#include <qobjectlist.h>
#include <qwidget.h>
#include <qdom.h>

void Generate(QDomDocument & document, QDomElement & element, QWidget * widget, const QString & className);
void Generate(QDomDocument & document, QDomElement & element, QWidget * widget);
void Generate(QDomDocument & document, QDomElement & element, QObject * object);
void Generate(QDomDocument & document, QDomElement & element, QObject * object);
void GenerateWidget(QWidget * widget, bool mainWidget);

#endif



