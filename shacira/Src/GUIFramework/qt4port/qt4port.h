
#ifndef _qt4port_h_
#define _qt4port_h_

#include <qglobal.h>
#include <string>
class QWizard;

#if (QT_VERSION >= 0x050000)
#ifndef QT5
   #define QT5
#endif
#ifndef QT4
   #define QT4
#endif
#else
#if (QT_VERSION >= 0x040000)
#ifndef QT4
   #define QT4
#endif
#else
#endif
   #define QT3
#endif

#ifdef QT5
// causes compile time error messages in qdatetime.h 
#define NOMINMAX
#endif

#ifdef QT4
#include <qevent.h>
#define WIDGET_FLAGS_TYPE     Qt::WindowFlags
#define QPointArray           QPolygon
#else
#define WIDGET_FLAGS_TYPE     QWidget::WFlags
#endif

#ifdef QT4
#include <qframe.h>
#include <qlabel.h>
#define BUTTONGROUP_BASE_CLASS			QLabel
#else
#include <qbuttongroup.h>
#define BUTTONGROUP_BASE_CLASS			QButtonGroup
#endif

#ifdef QT4
#include <qscrollarea.h>
#define CSCROLLVIEW_BASE_CLASS			QScrollArea
#else
#include <qscrollview.h>
#define CSCROLLVIEW_BASE_CLASS			QScrollView
#endif

#ifdef QT4
#define UI() (&_ui)
#define UI_CLASS(type) type _ui
#else
#define UI() this
#define UI_CLASS(type)
#endif

#ifdef QT4
   #ifdef does_not_work
      inline const char * constStringPtr(const QString & s)
      {
         return s.toStdString().c_str();
      }
      inline const char * constStringPtr(const QByteArray & s)
      {
         return s.constData();
      }
      #define CONST_STRING(s) constStringPtr(s)
   #else
      #define CONST_STRING(s) (s.toStdString().c_str())
   #endif
#else
   #define CONST_STRING(s) ((const char *)s)
#endif

#ifdef QT4
QObject * child(QObject * object, const char * objName, const char * inheritsClass = 0, bool recursiveSearch = true);
QObject * child(QObject * object, const std::string & objName, const char * inheritsClass = 0, bool recursiveSearch = true);
QObject * child(QObject * object, const QString & objName, const char * inheritsClass = 0, bool recursiveSearch = true);
QObject * parent(QObject * object, const char * objName = NULL, const char * inheritsClass = NULL, bool recursiveSearch = true);
void unsetPalette(QWidget * widget);
static void queryListHelper(QObjectList & objectList, QObject * object, const char * inheritsClass = 0, const char * objName = 0, bool regexpMatch = true, bool recursiveSearch = true);
QObjectList queryList(QObject * object, const char * inheritsClass = 0, const char * objName = 0, bool regexpMatch = true, bool recursiveSearch = true);
enum EncodingTypes {Latin1};
void setEncoding(EncodingTypes encoding);
int indexOf(QWizard * wizard, QWidget * page);
enum ToggleState {ToggleStateOff, ToggleStateNoChange, ToggleStateOn};
bool isA(QObject * object, const char * className);
QString append(const QString & head, const QString & tail, const QString & delimiter = "/");
void notPorted(const QString & location, const QString & message = "not ported yet");

#define NOT_PORTED(message) \
   notPorted(__LOC__, message);
#endif

#include "comp_def.h"

#endif // _qt4port_h_


