
#include "wizard.h"
#include "Styles/cQtTouchStyle.h"
#include "cappframe.h"

WizardPageInfo::WizardPageInfo()
   : _id(-1),
     _page(NULL),
     _backEnabled(false),
     _nextEnabled(false),
     _helpEnabled(false),
     _finishEnabled(false),
     _appropriate(true),
     _isFinalPage(false),
     _isCommitPage(false),
     _isComplete(false)
{
}

WizardBase::WizardBase(QWidget * parent, const char * name, bool modal, Qt::WindowFlags flags)
   : QWizard(parent, flags),
     _nextPage(NULL), _customButtonSigSlotConnected(false)
{
   float xDisplayScale = 1.0f;
   float yDisplayScale = 1.0f;

   if (parent->inherits("CAppFrame")) {
      xDisplayScale = CAppFrame::xDisplayScale();
      yDisplayScale = CAppFrame::yDisplayScale();
   }

   if (name != NULL) {
      setObjectName(name);
   }
   setModal(modal);
   setStyle(new cWizardStyle(xDisplayScale, yDisplayScale));

   connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(updateButtons(int)));
//   setWizardStyle(ClassicStyle);
//   setOptions(options() | QWizard::HaveFinishButtonOnEarlyPages);
}

WizardBase::~WizardBase()
{
}

void WizardBase::initializeWizard()
{
   int minimumHeight = getScaledHeight(32);

   button(QWizard::BackButton)->setMinimumHeight(minimumHeight);
   button(QWizard::NextButton)->setMinimumHeight(minimumHeight);
   button(QWizard::FinishButton)->setMinimumHeight(minimumHeight);
   button(QWizard::CancelButton)->setMinimumHeight(minimumHeight);
   button(QWizard::HelpButton)->setMinimumHeight(minimumHeight);

   QList<int> pageList = pageIds();
   QList<int>::const_iterator i = pageList.constBegin();
   while (i != pageList.constEnd()) {
      int id = (*i);
      QWizardPage * page = this->page(id);
      WizardPageInfo * pageInfo = new WizardPageInfo;
      pageInfo->_id = id;
      pageInfo->_page = page;
      _pageInfoMap[id] = pageInfo;
      i++;
   }
}

int WizardBase::nextId() const
{
   int id = -1;
   if (_nextPage != NULL) {
      id = indexOf(_nextPage);
      return id;
   }
   id = this->currentId();
   for (id=id+1; id<pageCount(); id++) {
      QWizardPage * page = this->page(id);
      if (appropriate(page)) {
         break;
      }
   }
   if (id == pageCount()) {
      return -1;
   } else {
      return id;
   }
}

void WizardBase::showPage(QWidget * page)
{
   _nextPage = reinterpret_cast<QWizardPage*>(page);
   next();
   _nextPage = NULL;
}

void WizardBase::setBackEnabled(QWizardPage * page, bool state)
{
   int pageId = indexOf(page);
   setButtonState(pageId, QWizard::BackButton, state);
}

void WizardBase::setBackEnabled(QWidget * page, bool state)
{
   setBackEnabled(static_cast<QWizardPage*>(page), state);
}

void WizardBase::setNextEnabled(QWizardPage * page, bool state)
{
   int pageId = indexOf(page);
   setButtonState(pageId, QWizard::NextButton, state);
}

void WizardBase::setNextEnabled(QWidget * page, bool state)
{
   setNextEnabled(static_cast<QWizardPage*>(page), state);
}

void WizardBase::setHelpEnabled(QWizardPage * page, bool state)
{
   int pageId = indexOf(page);
   setButtonState(pageId, QWizard::HelpButton, state);
}

void WizardBase::setHelpEnabled(QWidget * page, bool state)
{
   setHelpEnabled(static_cast<QWizardPage*>(page), state);
}

void WizardBase::setHelpEnabledAll(bool state)
{
    short i;
    for (i=0; i < pageCount(); i++)
    {
        setHelpEnabled(page(i), state);
    }
}

void WizardBase::setFinishEnabled(QWizardPage * page, bool state)
{
   int pageId = indexOf(page);
   setButtonState(pageId, QWizard::FinishButton, state);
}

void WizardBase::setFinishEnabled(QWidget * page, bool state)
{
   setFinishEnabled(static_cast<QWizardPage*>(page), state);
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

bool WizardBase::appropriate(QWidget * page) const
{
   int id = indexOf(page);
   PAGEINFO_MAP_T::const_iterator i = _pageInfoMap.find(id);
   if (i != _pageInfoMap.cend()) {
      return (*i).second->_appropriate;
   } else {
      return true;
   }
}

void WizardBase::setAppropriate(QWidget * page, bool state)
{
   int id = indexOf(page);
   PAGEINFO_MAP_T::const_iterator i = _pageInfoMap.find(id);
   if (i != _pageInfoMap.cend()) {
      (*i).second->_appropriate = state;
   } else {
      int dummy = 0;
   }
}

void WizardBase::setTitle(QWizardPage * page, const QString & text)
{
   page->setTitle(text);
}

int WizardBase::indexOf(QWidget * page) const
{
   QList<int> pageList = pageIds();
   QList<int>::const_iterator i = pageList.constBegin();
   while (i != pageList.constEnd()) {
      int id = (*i);
      if (page == this->page(id)) {
         return id;
      }
      i++;
   }
   return -1;
}


// private members

unsigned int WizardBase::buttonStates(int id) const
{
   unsigned int buttonStates = 0;
   PAGEINFO_MAP_T::const_iterator i = _pageInfoMap.find(id);
   if (i != _pageInfoMap.cend()) {
      WizardPageInfo * pageInfo = (*i).second;
      unsigned int pattern = 0;
      if (pageInfo->_backEnabled) {
         pattern = (1 << (QWizard::BackButton));
         buttonStates |= pattern;
      }
      if (pageInfo->_nextEnabled) {
         pattern = (1 << (QWizard::NextButton));
         buttonStates |= pattern;
      }
      if (pageInfo->_helpEnabled) {
         pattern = (1 << (QWizard::HelpButton));
         buttonStates |= pattern;
      }
      if (pageInfo->_finishEnabled) {
         pattern = (1 << (QWizard::FinishButton));
         buttonStates |= pattern;
      }
      return buttonStates;
   } else {
      return 0;
   }
}

bool WizardBase::enabled(int id, WizardButton which) const
{
   unsigned int buttonStates = 0;
   PAGEINFO_MAP_T::const_iterator i = _pageInfoMap.find(id);
   if (i != _pageInfoMap.cend()) {
      WizardPageInfo * pageInfo = (*i).second;
      if (which == QWizard::BackButton) {
         return pageInfo->_backEnabled;
      } else if (which == QWizard::NextButton) {
         return pageInfo->_nextEnabled;
      } else if (which == QWizard::HelpButton) {
         return pageInfo->_helpEnabled;
      } else if (which == QWizard::FinishButton) {
         return pageInfo->_finishEnabled;
      } else if (which == QWizard::CancelButton) {
         return !(options() & QWizard::NoCancelButton);
      } else if (which == QWizard::CustomButton1) {
         return options() & QWizard::HaveCustomButton1;
      } else if (which == QWizard::CustomButton2) {
         return options() & QWizard::HaveCustomButton2;
      } else if (which == QWizard::CustomButton3) {
         return options() & QWizard::HaveCustomButton3;
      }
   }
   return false;
}

void WizardBase::setButtonState(int id, WizardButton which, bool state)
{
   PAGEINFO_MAP_T::const_iterator i = _pageInfoMap.find(id);
   if (i != _pageInfoMap.cend()) {
      WizardPageInfo * pageInfo = (*i).second;
      if (which == QWizard::BackButton) {
         pageInfo->_backEnabled = state;
         return;
      } else if (which == QWizard::NextButton) {
         pageInfo->_nextEnabled = state;
         return;
      } else if (which == QWizard::HelpButton) {
         pageInfo->_helpEnabled = state;
         return;
      } else if (which == QWizard::FinishButton) {
         pageInfo->_finishEnabled = state;
         return;
      }
   }
}

void WizardBase::updateButtons(int pageId)
{
   if (pageId == -1) // -1 : No page set
       return;

   int usedCustomButtons = 0;
   QList<QWizard::WizardButton> layout;
   layout << QWizard::Stretch;
   if (enabled(pageId, QWizard::CustomButton1)) {
      layout << QWizard::CustomButton1;
      usedCustomButtons++;
   }
   if (enabled(pageId, QWizard::CustomButton2)) {
      layout << QWizard::CustomButton2;
      usedCustomButtons++;
   }
   if (enabled(pageId, QWizard::CustomButton3)) {
      layout << QWizard::CustomButton3;
      usedCustomButtons++;
   }

//   if (enabled(pageId, QWizard::BackButton)) {
      layout << QWizard::BackButton;
//   }
   if (enabled(pageId, QWizard::NextButton)) {
      layout << QWizard::NextButton;
   }
   if (enabled(pageId, QWizard::HelpButton)) {
      layout << QWizard::HelpButton;
   }
   if (enabled(pageId, QWizard::FinishButton)) {
      layout << QWizard::FinishButton;
   }
   if (enabled(pageId, QWizard::CancelButton)) {
      layout << QWizard::CancelButton;
   }

   QWizardPage * page = this->page(pageId);
   if (!enabled(pageId, QWizard::BackButton) &&
       !enabled(pageId, QWizard::NextButton)) {
      page->setCommitPage(true);
   } else {
      page->setCommitPage(false);
   }
   if (enabled(pageId, QWizard::FinishButton)) {
      page->setFinalPage(true);
   } else {
      page->setFinalPage(false);
   }

   setButtonLayout(layout);

   int i;
   for(i = 0; i < usedCustomButtons; i++) {
      if (enabled(pageId, (WizardButton) (QWizard::CustomButton1 + i))) {
         button((WizardButton) (QWizard::CustomButton1 + i))->clearFocus();
      }
   }

   if (enabled(pageId, QWizard::NextButton)) {
       button(QWizard::NextButton)->setFocus();
   }
   else if (enabled(pageId, QWizard::CancelButton)) {
       button(QWizard::CancelButton)->setFocus();
   }
}

void WizardBase::setCustomButton(WizardOption option, bool state, const QString & objectName)
{
   int which = -1;
   if (option & HaveCustomButton1) {
       which = CustomButton1;
   }
   else if (option & HaveCustomButton2) {
       which = CustomButton2;
   }
   else if (option & HaveCustomButton3) {
       which = CustomButton3;
   }

   if (which != -1) {
      setOption(option, true);
      QAbstractButton *customButton1 = button((WizardButton) which);
      if (objectName.isEmpty()) {
         QString name = QString("WizardCustomButton%1").arg(which - CustomButton1 + 1);
         customButton1->setObjectName(name);
      }
      else {
         customButton1->setObjectName(objectName);
      }
      if (!_customButtonSigSlotConnected) {
         _customButtonSigSlotConnected = true;
         connect(this, SIGNAL(customButtonClicked(int)), this, SLOT(customButtonIsClicked(int)));
      }
   }
}

void WizardBase::setCustomButtonIcon(WizardButton which, const QString & normalIcon, const QString & activeIcon, const QString & styleSheet, const QSize iconSize)
{
   if ((which >= CustomButton1)  && (which <= CustomButton2)) {
      QIcon icon;
      icon.addFile(normalIcon, QSize(), QIcon::Normal, QIcon::Off);
      icon.addFile(activeIcon, QSize(), QIcon::Active, QIcon::Off);

      QAbstractButton *customButton = button(which);
      customButton->setIcon(icon);
      QSize customButtonIconSize = iconSize.isValid() ? iconSize : icon.actualSize(QSize(100, 100));
      customButton->setIconSize(customButtonIconSize);
      if (!styleSheet.isEmpty())
         customButton->setStyleSheet(styleSheet);
   }
}

void WizardBase::customButtonIsClicked(int which)
{
   if (which == CustomButton1) {
      customButton1Clicked();
   }
   else if (which == CustomButton2) {
      customButton2Clicked();
   }
   else if (which == CustomButton3) {
      customButton3Clicked();
   }
   
   button((WizardButton)which)->clearFocus();
}

void WizardBase::move(int x, int y)
{
    _positionExclusive = true;

    QWizard::move(x, y);
}

void WizardBase::move(const QPoint &point)
{
    _positionExclusive = true;

    QWizard::move(point);
}

int WizardBase::getScaledWidth(int baseValue) const
{
    int iScaledValue = baseValue;
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    if (parent()->inherits("CAppFrame")) {
        qreal displayScale = CAppFrame::xDisplayScale();
        if (displayScale != 1.0f) {
            qreal qScaledValue = qreal(baseValue) * displayScale;
            iScaledValue = qRound(qScaledValue);
        }
    }
#endif

    return iScaledValue;
}

int WizardBase::getScaledHeight(int baseValue) const
{
    int iScaledValue = baseValue;
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    if (parent()->inherits("CAppFrame")) {
        qreal displayScale = CAppFrame::yDisplayScale();
        if (displayScale != 1.0f) {
            qreal qScaledValue = qreal(baseValue) * displayScale;
            iScaledValue = qRound(qScaledValue);
        }
    }
#endif

    return iScaledValue;
}
