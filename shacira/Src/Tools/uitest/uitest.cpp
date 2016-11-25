
#include <qapplication.h>
#include <qwidget.h>
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>

#include <qapplication.h>
#include "forms/formtest.h"
#include "formfactory.h"

#include "CDirectory.h"
#include "CDirectoryView.h"
#include "MListViewProc.h"
#include "CReqValue.h"

QWidget * widgetByName(QObject * object, const QString & name);

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
#define SINGLE_TESTx
#ifndef SINGLE_TEST
   CAppFrame * mosaicFrame = NULL;
   FormFactory formFactory;
   formFactory.create();
   FrameMap::const_iterator f = formFactory._frameMap.begin();
   while (f != formFactory._frameMap.end()) {
      CAppFrame * frame = (*f).second;
      QString name = frame->name();
      if (frame->name() == "MosaicFrame") {
         mosaicFrame = frame;
      }
      f++;
   }
   QStackedWidget * stack = NULL;
   if (mosaicFrame != NULL) {
      QWidget * stackParent = widgetByName(mosaicFrame, "CFramePage");
      QVBoxLayout * layout = new QVBoxLayout(stackParent);
      stack = new QStackedWidget;
      layout->addWidget(stack);
   }
   FormTest * formTest = new FormTest(stack);
   formTest->setCentralWidget(mosaicFrame);
   PageMap::const_iterator p = formFactory._pageMap.begin();
   while (p != formFactory._pageMap.end()) {
      CPage * page = (*p).second;
      formTest->addWidget(page);
      p++;
   }
   DialogMap::const_iterator d = formFactory._dialogMap.begin();
   while (d != formFactory._dialogMap.end()) {
      QDialog * dialog = (*d).second;
      formTest->addWidget(dialog);
      d++;
   }
   ActionDialogMap::const_iterator ad = formFactory._actionDialogMap.begin();
   while (ad != formFactory._actionDialogMap.end()) {
      CActionDialog * dialog = (*ad).second;
      formTest->addWidget(dialog);
      ad++;
   }
   WizardMap::const_iterator w = formFactory._wizardMap.begin();
   while (w != formFactory._wizardMap.end()) {
      QWizard * wizard = (*w).second;
      formTest->addWidget(wizard);
      w++;
   }
#else
   FormTest * formTest = new FormTest(NULL);
//   CDirectoryView * directory = new CDirectoryView;
//   formTest->layout()->addWidget(directory);
   CDirectory * directory = new CDirectory;
   formTest->layout()->addWidget(directory);
#endif
   formTest->show();
   app.exec();
   return 0;
}

QWidget * widgetByName(QObject * object, const QString & name)
{
   if (object->objectName() == name) {
      QWidget * widget = dynamic_cast<QWidget*>(object);
      if (widget != NULL) {
         return widget;
      }
   }
   QObjectList children = object->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * child = (*i);
      QWidget * widget = widgetByName(child, name);
      if (widget != NULL) {
         return widget;
      }
      i++;
   }
   return NULL;
}

