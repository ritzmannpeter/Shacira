
#include "Demo2FrameImpl.h"
#include "Demo2StartupImpl.h"
#include "System/Text/cText.h"

Demo2FrameImpl::Demo2FrameImpl(QWidget * parent, const char * name, WFlags f)
   : Demo2Frame(parent, name)
{
   /*!
    * setup the help interface if used
    */
   //_HelpInterface = new ...;
}

Demo2FrameImpl::~Demo2FrameImpl()
{
   /*!
    * delete the help interface if one
    */
   if (_HelpInterface != NULL) {
      delete _HelpInterface;
   }
}

CFrame * Demo2FrameImpl::GetPageContainer()
{
   return PageFrame;
}

CFixText * Demo2FrameImpl::GetPageHeader()
{
   return PageHeader;
}

CFixText * Demo2FrameImpl::GetStatusBar()
{
   /*!
    * this application uses no status bar.
    */
   return NULL;
}

void Demo2FrameImpl::Object(TRANSIENT_OBJECT_PTR object)
{
}

void Demo2FrameImpl::Message(BOOL_T async,
                                  CONST_STRING_T message,
                                  CONST_STRING_T details,
                                  CONST_STRING_T param1,
                                  CONST_STRING_T param2,
                                  CONST_STRING_T param3,
                                  CONST_STRING_T param4)
{
   /*!
    * use builtin standard message processing.
    */
   CAppFrame::Message(async,
                      message,
                      details,
                      param1,
                      param2,
                      param3,
                      param4);
}

void Demo2FrameImpl::Message(BOOL_T async, ERROR_REF_T error)
{
   /*!
    * use builtin standard message processing.
    */
   CAppFrame::Message(async, error);
}

CStartupForm * Demo2FrameImpl::CreateStartupForm()
{
   /*!
    * instantiate and return form that comments application startup.
    */
   return new Demo2StartupImpl();
}

void Demo2FrameImpl::languageChange()
{
}

