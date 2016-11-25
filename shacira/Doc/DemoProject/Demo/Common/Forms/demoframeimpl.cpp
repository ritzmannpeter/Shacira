
#include "demoframeimpl.h"
#include "demostartupimpl.h"
#include "System/Text/cText.h"
#include <qmessagebox.h>

DemoFrameImpl::DemoFrameImpl(QWidget * parent, const char * name, WFlags f)
   : DemoFrame(parent, name)
{
//   _HelpInterface = new cDemoHelpInterface(this);
   _HelpInterface = NULL;
}

DemoFrameImpl::~DemoFrameImpl()
{
}

int DemoFrameImpl::GetSoftKeyCount()
{
   return 0;
}

CFrame * DemoFrameImpl::GetNodeContainer()
{
   return NULL;
}

CFrame * DemoFrameImpl::GetGroupContainer()
{
   // return CFramePageSelect;
	return NULL;
}

CFrame * DemoFrameImpl::GetPageContainer()
{
   return CFramePage;
}

CFrame * DemoFrameImpl::GetSoftkeyContainer()
{
   return NULL;
}

CFixText * DemoFrameImpl::GetPageHeader()
{
   return Header;
}

CFixText * DemoFrameImpl::GetStatusBar()
{
   return NULL;
}

void DemoFrameImpl::Object(TRANSIENT_OBJECT_PTR object)
{
}

#include "cinfolabel.h"
void DemoFrameImpl::Message(BOOL_T async,
                              CONST_STRING_T message,
                              CONST_STRING_T details,
                              CONST_STRING_T param1,
                              CONST_STRING_T param2,
                              CONST_STRING_T param3,
                              CONST_STRING_T param4)
{
   InfoLine->setText(message);
   return;
   STRING_T message_text = cConvUtils::SubstParams(message, param1, param2, param3, param4);
   STRING_T detail_text = cConvUtils::SubstParams(message, param1, param2, param3, param4);
   if (async) {
#ifdef lassma
      CFixText * status = Status;
      Beep(100, 100);
      status->setText(message_text.c_str());
#endif
   } else {
      Beep(100, 100);
      QString text = CWidgetBase::Translate(message,
                                            "custom",
                                            param1,
                                            param2, // HA210105
                                            param3, // HA210105
                                            param4); // HA210105

      QMessageBox mb("Demo",
                     text, // HA210105
                     QMessageBox::Information,
                     QMessageBox::Ok | QMessageBox::Default,
                     QMessageBox::NoButton,
                     QMessageBox::NoButton);
	  QFont qFont("Arial", 11);
      mb.setFont(qFont);
      mb.exec();
   }
}

void DemoFrameImpl::Message(BOOL_T async,
                              ERROR_REF_T error)
{
}

CStartupForm * DemoFrameImpl::CreateStartupForm()
{
  return new DemoStartupImpl();
}

void DemoFrameImpl::languageChange()
{
    DemoFrame::languageChange();
}
