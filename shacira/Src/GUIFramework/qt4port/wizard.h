
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


class WizardPageInfo
{
public:
   WizardPageInfo();
   virtual ~WizardPageInfo()
   {
   };
   int _id;
   QWizardPage * _page;
   bool _backEnabled;
   bool _nextEnabled;
   bool _helpEnabled;
   bool _finishEnabled;
   bool _appropriate;
   bool _isFinalPage;
   bool _isCommitPage;
   bool _isComplete;
};

typedef map<int,WizardPageInfo*> PAGEINFO_MAP_T;

class WizardBase : public QWizard
{
   Q_OBJECT

public:
   WizardBase(QWidget * parent, const char * name, bool modal, Qt::WindowFlags flags);
   virtual ~WizardBase();
   virtual void initializeWizard();
   virtual int nextId() const;
   void showPage(QWidget * page);
   void setBackEnabled(QWizardPage * page, bool state);
   void setBackEnabled(QWidget * page, bool state);
   void setNextEnabled(QWizardPage * page, bool state);
   void setNextEnabled(QWidget * page, bool state);
   void setHelpEnabled(QWizardPage * page, bool state);
   void setHelpEnabled(QWidget * page, bool state);
   void setHelpEnabledAll(bool state);
   void setFinishEnabled(QWizardPage * page, bool state);
   void setFinishEnabled(QWidget * page, bool state);
   QAbstractButton * backButton() const;
   QAbstractButton * nextButton() const;
   QAbstractButton * cancelButton() const;
   QAbstractButton * finishButton() const;
   QAbstractButton * helpButton() const;
   int  pageCount() const;
   virtual bool appropriate(QWidget * page) const;
   void setAppropriate(QWidget * page, bool state);
   void setTitle(QWizardPage * page, const QString & text);
   int indexOf(QWidget * page) const;
   virtual void setCustomButton(WizardOption option, bool state, const QString & objectName=QString());
   virtual void setCustomButtonIcon(WizardButton which, const QString & normalIcon, const QString & activeIcon, const QString &styleSheet = QString(), const QSize iconSize = QSize());
   virtual void customButton1Clicked() {};
   virtual void customButton2Clicked() {};
   virtual void customButton3Clicked() {};
   void move(int x, int y);
   void move(const QPoint &point);

   bool getPositionExclusive() const { return _positionExclusive; };
   void setPositionExclusive(bool posExclusive) { _positionExclusive = posExclusive; };

   int getScaledWidth(int baseValue) const;
   int getScaledHeight(int baseValue) const;

public slots:
    virtual void updateButtons(int pageId);
    void customButtonIsClicked(int which);

protected:
   bool enabled(int id, WizardButton which) const;

private:
   QWizardPage * _nextPage;
   PAGEINFO_MAP_T _pageInfoMap;
   bool _customButtonSigSlotConnected;
   bool _positionExclusive;

private:
   unsigned int buttonStates(int id) const;
   void setButtonState(int id, WizardButton which, bool state);
};

#include "CWidgetBase.h"
template <class TClass> class Wizard : public WizardBase
{
public:
   Wizard(QWidget * parent, const char * name, bool modal, Qt::WindowFlags flags)
      : WizardBase(parent, name, modal, flags)
   {
      _ui.setupUi(this);
      initializeWizard();
   };
   virtual ~Wizard()
   {
   };
protected:
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   inline virtual void changeEvent(QEvent * event )
   {
      if (event->type() == QEvent::LanguageChange) {
         languageChange();
      }
      WizardBase::changeEvent(event);
   };
#endif

   inline virtual void languageChange()
   {
      _ui.retranslateUi(this);
   };
protected:
   TClass _ui;
public:
   inline TClass & ui()
   {
      CWidgetBase::CheckThread();
      return _ui;
   };
};

#endif // _wizard_h_


