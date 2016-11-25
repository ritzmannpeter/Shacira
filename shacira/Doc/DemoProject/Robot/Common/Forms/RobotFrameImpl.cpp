
#include "RobotFrameImpl.h"
#include "RobotStartupImpl.h"
#include "System/Text/cText.h"

RobotFrameImpl::RobotFrameImpl(QWidget * parent, const char * name, WFlags f)
   : RobotFrame(parent, name)
{
   /*!
    * setup the help interface if used
    */
   //_HelpInterface = new ...;
}

RobotFrameImpl::~RobotFrameImpl()
{
   /*!
    * delete the help interface if one
    */
   if (_HelpInterface != NULL) {
      delete _HelpInterface;
   }
}

CFrame * RobotFrameImpl::GetPageContainer()
{
   return PageFrame;
}

CFixText * RobotFrameImpl::GetPageHeader()
{
   return PageHeader;
}

CFixText * RobotFrameImpl::GetStatusBar()
{
   /*!
    * this application uses no status bar.
    */
   return NULL;
}

void RobotFrameImpl::Object(TRANSIENT_OBJECT_PTR object)
{
}

void RobotFrameImpl::Message(BOOL_T async,
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

void RobotFrameImpl::Message(BOOL_T async, ERROR_REF_T error)
{
   /*!
    * use builtin standard message processing.
    */
   CAppFrame::Message(async, error);
}

CStartupForm * RobotFrameImpl::CreateStartupForm()
{
   /*!
    * instantiate and return form that comments application startup.
    */
   return new RobotStartupImpl();
}

void RobotFrameImpl::languageChange()
{
}

