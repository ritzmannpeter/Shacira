
#include "qtgui"
#include "Demo2FrameImpl.h"
#include "Demo2Page1.h"
#include "Demo2Page2.h"
#include "Demo2Page3.h"

CAppFrame * CreateAppFrame()
{
   CAppFrame * app_frame = new Demo2FrameImpl;
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
   SH_PAGE(Demo2Page1,list)
   SH_PAGE(Demo2Page2,list)
   SH_PAGE(Demo2Page3,list)
///   SH_DYNAMIC_PAGE("Pages/Demo2Page1.ui",list)
   return list;
}

PageList * Demo2FrameImpl::CreatePageList(QWidget * parent)
{
   return __CreatePageList__(parent);
}

