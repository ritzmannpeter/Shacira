
#ifndef _wizard_h_
#define _wizard_h_

#include <qwidget.h>
#include <qstring.h>
#include <qwizard.h>
#include <qlayout.h>
#include <qabstractbutton.h>

#ifdef QT4
#include "qt4port.h"
#include "pluginfactory.h"
#else
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : warning: "
#define NOT_PORTED(msg)
#define _CWIDGET_EXPORT_
#endif

#include <map>
using namespace std;
typedef map<QWizardPage*,bool> APPROPRIATE_MAP_T;

class WizardBase : public QWizard
{
public:
   WizardBase(QWidget * parent, const char * name, bool modal, Qt::WindowFlags flags);
   virtual ~WizardBase();
   void showPage(QWidget * page);
   void setBackEnabled(QWizardPage * page, bool state);
   void setBackEnabled(QWidget * page, bool state);
   void setNextEnabled(QWizardPage * page, bool state);
   void setNextEnabled(QWidget * page, bool state);
   void setHelpEnabled(QWizardPage * page, bool state);
   void setHelpEnabled(QWidget * page, bool state);
   void setFinishEnabled(QWizardPage * page, bool state);
   void setFinishEnabled(QWidget * page, bool state);
   QAbstractButton * backButton() const;
   QAbstractButton * nextButton() const;
   QAbstractButton * cancelButton() const;
   QAbstractButton * finishButton() const;
   QAbstractButton * helpButton() const;
   int  pageCount() const;
   bool appropriate(QWizardPage * page) const;
   void setAppropriate(QWizardPage * page, bool state);
   void setAppropriate(QWidget * page, bool state);
   void setTitle(QWizardPage * page, const QString & text);
   virtual void layOutButtonRow(QHBoxLayout * layout);
   virtual void layOutTitleRow(QHBoxLayout * layout, const QString & title);
   int indexOf(QWidget * page) const;
protected:
   APPROPRIATE_MAP_T _appropriateMap;
protected:
   virtual void cleanupPage(int id);
   virtual void initializePage(int id);
};

template <class TClass> class Wizard : public WizardBase
{
public:
   Wizard(QWidget * parent, const char * name, bool modal, Qt::WindowFlags flags)
      : WizardBase(parent, name, modal, flags)
   {
      _ui.setupUi(this);
   };
   virtual ~Wizard()
   {
   };
protected:
   virtual void languageChange()
   {
      _ui.retranslateUi(this);
   };
protected:
   TClass _ui;
public:
   TClass & ui() {return _ui;};
};

#endif // _wizard_h_


