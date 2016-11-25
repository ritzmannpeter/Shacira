
#include "wizard.h"

#include "wizard.h"

WizardBase::WizardBase(QWidget * parent, const char * name, bool modal, Qt::WindowFlags flags)
   : QWizard(parent, flags)
{
   if (name != NULL) {
      setObjectName(name);
   }
   setModal(modal);
   setWizardStyle(ClassicStyle);
}

WizardBase::~WizardBase()
{
}

void WizardBase::showPage(QWidget * page)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setBackEnabled(QWizardPage * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setBackEnabled(QWidget * page, bool state)
{
   setBackEnabled(static_cast<QWizardPage*>(page), state);
}

void WizardBase::setNextEnabled(QWizardPage * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setNextEnabled(QWidget * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setHelpEnabled(QWizardPage * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setHelpEnabled(QWidget * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setFinishEnabled(QWizardPage * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::setFinishEnabled(QWidget * page, bool state)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

QAbstractButton * WizardBase::backButton() const
{
   return QWizard::button(QWizard::BackButton);
}

QAbstractButton * WizardBase::nextButton() const
{
   return QWizard::button(QWizard::NextButton);
}

QAbstractButton * WizardBase::cancelButton() const
{
   return QWizard::button(QWizard::CancelButton);
}

QAbstractButton * WizardBase::finishButton() const
{
   return QWizard::button(QWizard::FinishButton);
}

QAbstractButton * WizardBase::helpButton() const
{
   return QWizard::button(QWizard::HelpButton);
}

int WizardBase::pageCount() const
{
   return pageIds().size();
}

bool WizardBase::appropriate(QWizardPage * page) const
{
   APPROPRIATE_MAP_T::const_iterator i = _appropriateMap.find(page);
   if (i != _appropriateMap.end()) {
      return (*i).second;
   } else {
      return false;
   }
}

void WizardBase::setAppropriate(QWizardPage * page, bool state)
{
   _appropriateMap[page] = state;
}
void WizardBase::setAppropriate(QWidget * page, bool state)

{
   setAppropriate(static_cast<QWizardPage*>(page), state);
}

void WizardBase::setTitle(QWizardPage * page, const QString & text)
{
   page->setTitle(text);
}

void WizardBase::layOutButtonRow(QHBoxLayout * layout)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

void WizardBase::layOutTitleRow(QHBoxLayout * layout, const QString & title)
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
}

int WizardBase::indexOf(QWidget * page) const
{
   #pragma message(__LOC__ "not ported yet")
   NOT_PORTED("not ported yet")
   return -1;
}

void WizardBase::cleanupPage(int id)
{
   QWizard::cleanupPage(id);
}

void WizardBase::initializePage(int id)
{
   QWizardPage * page = this->page(id);
   if (page != NULL) {
      QString subTitle = page->subTitle();
      if (subTitle.isEmpty()) {
//         page->setSubTitle(".");
      }
   }
   QWizard::initializePage(id);
}

#ifdef doku
void WizardBase::setupWizard()
{
   QList<int> pageList = pageIds();
   QList<int>::const_iterator i = pageList.begin();
   while (i != pageList.end()) {
      int id = (*i);
      QWizardPage * page = this->page(id);
      QString subTitle = page->subTitle();
      if (subTitle.isEmpty()) {
         page->setSubTitle(".");
      }
      i++;
   }
}
#endif
