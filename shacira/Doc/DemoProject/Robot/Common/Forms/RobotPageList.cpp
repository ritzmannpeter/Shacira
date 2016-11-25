
#include "qtgui"
#include "RobotFrameImpl.h"
#include "RobotPage1.h"
#include "RobotPage2.h"
#include "RobotPage3.h"

CAppFrame * CreateAppFrame()
{
   CAppFrame * app_frame = new RobotFrameImpl;
   app_frame->Initialize();
   return app_frame;
}

PageList * __CreatePageList__(QWidget * parent)
{
   PageList * list = new PageList;
   CPage * page = NULL;
   /*!
    * add application pages here using macro SH_PAGE(...) for builtin pages
    * and macro SH_DYNAMIC_PAGE(...) for dynamically loaded pages at runtime
    *
    * SH_PAGE(page_class_name,parent) f. e.
    * SH_PAGE(TestPage,parent)  don't forget to include the declarations
    *
    * SH_DYNAMIC_PAGE(page_file_name,parent) f. e.
    * SH_DYNAMIC_PAGE("TestPage.ui",parent)
    */
   SH_PAGE(RobotPage1,list)
   SH_PAGE(RobotPage2,list)
   SH_PAGE(RobotPage3,list)
///   SH_DYNAMIC_PAGE("Pages/RobotPage1.ui",list)
   return list;
}

PageList * RobotFrameImpl::CreatePageList(QWidget * parent)
{
   return __CreatePageList__(parent);
}

