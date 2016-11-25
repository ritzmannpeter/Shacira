

#include "CWidgetFactory.h"
#include "CFrame.h"
#include "CWidgetStack.h"
#include "CComposedStack.h"
#include "CTabWidget.h"
#include "CAppFrame.h"
#include "CStartupForm.h"
#include "CPage.h"
#include "CFixText.h"
#include "CInfoLabel.h"
#include "CToolButton.h"
#include "CGroupSelectButton.h"
#include "CPushButton.h"
#include "CStateButton.h"
#include "CReqValue.h"
#include "CIndReqValue.h"
#include "CActValue.h"
#include "CListView.h"
#include "CCompListView.h"
#include "CGroupBox.h"
#include "CSimpleGraphic.h"
#include "CGraphic.h"
#include "CProcGraphic.h"
#include "CRingGraphic.h"
#include "CVideo.h"
#include "CRadioButton.h"
#include "CCheckBox.h"
#include "CButtonGroup.h"
#include "CComboBox.h"
#if !defined(QT_NO_TABLE)
#include "CTable.h"
#endif
#include "CAlarmWidget.h"
#include "CTextEdit.h"
#include "CScrollBar.h"
#include "CVirtualKeyboard.h"
#include "CCoordSystem.h"
#include "CDirectory.h"
#include "CVarDimension.h"
#include "CSlider.h"
#include "CSpinBox.h"
#include "CProgressBar.h"
#include "CActionDialog.h"
#include "CTime.h"
#include "CDate.h"
#include "CDateTime.h"

CWidgetFactory::CWidgetFactory()
{
}

CWidgetFactory::~CWidgetFactory()
{
}

QWidget * CWidgetFactory::createWidget(const QString & class_name, QWidget * parent, const char * name) const
{
   if (class_name == "CFrame")
      return new CFrame(parent, name);
   else if (class_name == "CWidgetStack")
      return new CWidgetStack(parent, name);
   else if (class_name == "CComposedStack")
      return new CComposedStack(parent, name);
   else if (class_name == "CGroupBox")
      return new CGroupBox(parent, name);
   else if (class_name == "CTabWidget")
	   return new CTabWidget(parent, name);
   else if (class_name == "CAppFrame")
	   return new CAppFrame(parent, name);
   else if (class_name == "CStartupForm")
	   return new CStartupForm(parent, name);
   else if (class_name == "CPage")
	   return new CPage(parent, name);
   else if (class_name == "CActionDialog")
      return new CActionDialog(parent, name);
   else if (class_name == "CFixText")
	   return new CFixText(parent, name);
   else if (class_name == "CVarDimension")
      return new CVarDimension(parent, name);
   else if (class_name == "CInfoLabel")
	   return new CInfoLabel(parent, name);
   else if (class_name == "CToolButton")
      return new CToolButton(parent, name);
   else if (class_name == "CGroupSelectButton")
	   return new CGroupSelectButton(parent, name);
   else if (class_name == "CPushButton")
	   return new CPushButton(parent, name);
   else if (class_name == "CStateButton")
	   return new CStateButton(parent, name);
   else if (class_name == "CRadioButton")
      return new CRadioButton(parent, name);
   else if (class_name == "CButtonGroup")
	   return new CButtonGroup(parent, name);
   else if (class_name == "CCheckBox")
	   return new CCheckBox(parent, name);
   else if (class_name == "CReqValue")
	   return new CReqValue(parent, name);
   else if (class_name == "CIndReqValue")
	   return new CIndReqValue(parent, name);
   else if (class_name == "CActValue")
	   return new CActValue(parent, name);
   else if (class_name == "CListView")
	   return new CListView(parent, name);
   else if (class_name == "CCompListView")
	   return new CCompListView(parent, name);
   else if (class_name == "CSimpleGraphic")
	   return new CSimpleGraphic(parent, name);
   else if (class_name == "CGraphic")
	   return new CGraphic(parent, name);
   else if (class_name == "CProcGraphic")
	   return new CProcGraphic(parent, name);
   else if (class_name == "CRingGraphic")
	   return new CRingGraphic(parent, name);
   else if (class_name == "CVideo")
	   return new CVideo(parent, name);
   else if (class_name == "CComboBox")
	   return new CComboBox(TRUE, parent, name);
#if !defined(QT_NO_TABLE)
   else if (class_name == "CTable")
	   return new CTable(parent, name);
#endif
   else if (class_name == "CAlarmWidget")
	   return new CAlarmWidget(parent, name);
   else if (class_name == "CTextEdit")
	   return new CTextEdit(parent, name);
   else if (class_name == "CScrollBar")
	   return new CScrollBar(parent, name);
   else if (class_name == "CVirtualKeyboard")
	   return new CVirtualKeyboard(parent, name);
   else if (class_name == "CCoordSystem")
	   return new CCoordSystem(parent, name);
   else if (class_name == "CDirectory")
	   return new CDirectory(parent, name);
   else if (class_name == "CSlider")
      return new CSlider(parent, name);
   else if (class_name == "CSpinBox")
	   return new CSpinBox(parent, name);
   else if (class_name == "CProgressBar")
	   return new CProgressBar(parent, name);
   else if (class_name == "CTime")
	   return new CTime(parent, name);
   else if (class_name == "CDate")
	   return new CDate(parent, name);
   else if (class_name == "CDateTime")
	   return new CDateTime(parent, name);
   return NULL;
}

CPage * CWidgetFactory::LoadPage(const char * ui_file, QWidget * parent)
{
   try {
      CPage * page = (CPage*)QWidgetFactory::create(ui_file, NULL, parent);
      return page;
   } catch (...) {
   }
   return NULL;
}


