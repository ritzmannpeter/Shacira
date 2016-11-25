
#include "stylecontrol.h"
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <qwidget.h>
#include <qapplication.h>

cStyleControl::cStyleControl(const QString & styleSheetPath, QObject * parent)
   : QTimer(parent), _styleSheetPath(styleSheetPath)
{
   setInterval(1000);
   connect(this, SIGNAL(timeout()), this, SLOT(slotControlStyleSheet()));
}

cStyleControl::~cStyleControl()
{
}

void cStyleControl::slotControlStyleSheet()
{
   QFileInfo fileInfo(_styleSheetPath);
   QDateTime lastModified = fileInfo.lastModified();
   if (lastModified != _lastModification) {
      updateStyle();
   }
   _lastModification = lastModified;
}

void cStyleControl::updateStyle()
{
   QApplication * application = qApp;
   if (application != NULL) {
      QString styleSheet = loadStyleSheet(_styleSheetPath);
      application->setStyleSheet(styleSheet);
#ifdef UPDATE_ALL_WIDGETS
      QWidgetList widgetList = QApplication::allWidgets();
      foreach (QWidget *widget, widgetList) {
         widget->update();
      }
#endif
   }
}

QString cStyleControl::loadStyleSheet(const QString & styleSheetPath)
{
   QFile file(styleSheetPath);
   if (!file.open( QIODevice::ReadOnly | QIODevice::Text )) {
      return "";
   }
   QTextStream in(&file);
   return in.readAll();
}
