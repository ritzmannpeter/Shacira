
#include "$(appname)FrameImpl.h"
#include "$(appname)StartupImpl.h"
#include "System/Text/cText.h"

$(appname)FrameImpl::$(appname)FrameImpl(QWidget * parent, const char * name, WFlags f)
   : $(appname)Frame(parent, name)
{
   /*!
    * setup the help interface if used
    */
   //_HelpInterface = new ...;
}

$(appname)FrameImpl::~$(appname)FrameImpl()
{
   /*!
    * delete the help interface if one
    */
   if (_HelpInterface != NULL) {
      delete _HelpInterface;
   }
}

CFrame * $(appname)FrameImpl::GetPageContainer()
{
   return PageFrame;
}

CFixText * $(appname)FrameImpl::GetPageHeader()
{
   return PageHeader;
}

CFixText * $(appname)FrameImpl::GetStatusBar()
{
   /*!
    * this application uses no status bar.
    */
   return NULL;
}

void $(appname)FrameImpl::Object(TRANSIENT_OBJECT_PTR object)
{
}

void $(appname)FrameImpl::Message(BOOL_T async,
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

void $(appname)FrameImpl::Message(BOOL_T async, ERROR_REF_T error)
{
   /*!
    * use builtin standard message processing.
    */
   CAppFrame::Message(async, error);
}

CStartupForm * $(appname)FrameImpl::CreateStartupForm()
{
   /*!
    * instantiate and return form that comments application startup.
    */
   return new $(appname)StartupImpl();
}

void $(appname)FrameImpl::languageChange()
{
}

