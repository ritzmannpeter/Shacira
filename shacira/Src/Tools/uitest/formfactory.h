
#ifndef _formfactory_h_
#define _formfactory_h_

#include <map>
using namespace std;

#include <qstring.h>
#include <qwidget.h>
#include <qdialog.h>
#include <qwizard.h>
#include "CAppFrame.h"
#include "CPage.h"
#include "CActionDialog.h"

typedef map<QString,CAppFrame*> FrameMap;
typedef map<QString,CPage*> PageMap;
typedef map<QString,CActionDialog*> ActionDialogMap;
typedef map<QString,QDialog*> DialogMap;
typedef map<QString,QWizard*> WizardMap;

class FormFactory
{
public:
   FormFactory();
   virtual ~FormFactory();
   void create();
   FrameMap _frameMap;
   PageMap _pageMap;
   DialogMap _dialogMap;
   ActionDialogMap _actionDialogMap;
   WizardMap _wizardMap;
};

#endif

