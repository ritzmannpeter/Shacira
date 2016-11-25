
#include "q4_testview.h"
#include <QtGui/QApplication>
#include <qscrollbar.h>
#include <qtimer.h>
#include <qheaderview.h>
#include "testview.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qwindowsxpstyle.h>
#include <qwindowsvistastyle.h>
#include <qmotifstyle.h>

static QString loadStyleSheet(const QString & styleSheetPath)
{
   QFile file(styleSheetPath);
   if (!file.open( QIODevice::ReadOnly | QIODevice::Text )) {
      return "";
   }
   QTextStream in(&file);
   return in.readAll();
}

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QString styleSheet = loadStyleSheet("e:/temp/fmstyle.css");
   if (!styleSheet.isEmpty()) {
 //     a.setStyleSheet(styleSheet);
   }
//   a.setStyle(new QWindowsXPStyle);
//   a.setStyle(new QCommonStyle);
//   a.setStyle(new QMotifStyle);
   a.setStyle(new QWindowsVistaStyle);
   q4_testview w;
   TestView * testView = w.testView();
   int columnCount = 5;
   int i = 0;
   int j = 0;
   int k = 0;
   QString text;
   int iconSize = 48;
   for (i=0; i<columnCount; i++) {
      text = "column ";
      text += QString::number(i);
      if (i == 1) {
         QPixmap pixmap(QString::fromUtf8(":/mosaic/images/img_219.png"));
         pixmap = pixmap.scaled(QSize(iconSize, iconSize));
         testView->addColumn(pixmap, text, iconSize);
      } else if (i == 2) {
         QImage image(QString::fromUtf8(":/mosaic/images/img_219.png"));
         image = image.scaled(QSize(iconSize, iconSize));
         testView->addColumn(image, text, iconSize);
      } else if (i == 3) {
         QIcon icon(QString::fromUtf8(":/mosaic/images/img_219.png"));
         testView->addColumn(icon, text, iconSize);
      } else {
         testView->addColumn(text);
      }
      testView->setColumnText(i, "heinz");
      testView->setColumnWidth(i, 200);
   }
   int depth = 3;
   for (i=0; i<depth; i++) {
      TestViewItem * item = new TestViewItem(testView, i);
#ifdef lassma
      for (j=0; j<depth; j++) {
         TestViewItem * child = new TestViewItem(item, i, j);
         for (k=0; k<depth; k++) {
            TestViewItem * subChild = new TestViewItem(child, i, j, k);
         }
      }
#endif
   }
   QObject::connect(w.ui.refreshButton, SIGNAL(clicked()), testView, SLOT(refresh()));
   w.show();
   return a.exec();
}


