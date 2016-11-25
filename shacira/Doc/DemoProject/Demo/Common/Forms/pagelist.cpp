
#include "CPage.h"
#include "cQTUserInterface.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "demoframeimpl.h"

CAppFrame * _AppFrame = NULL;
CAppFrame * CreateAppFrame()
{
   if (_AppFrame == NULL) {
      _AppFrame = new DemoFrameImpl;
      _AppFrame->Initialize();
      SHARE_APPFRAME_FUNC_T func = cCustomFunctions::ShareAppframeFuncAddress();
      if (func != NULL) {
         func(_AppFrame);
      }
   }

#ifdef doc
   QDialog* qdDirDialog = new Sys_DirDialogSub(_AppFrame);
   _AppFrame->RegisterDialog(qdDirDialog);

   Qt::WFlags wfFlags =  Qt::WStyle_Customize|Qt::WStyle_Title|Qt::WType_TopLevel|Qt::WStyle_Tool;
   Clp_EjectorWizard_Sub* EjectorWizard = new Clp_EjectorWizard_Sub(_AppFrame, 0, true, wfFlags);
   _AppFrame->RegisterDialog(EjectorWizard);

   Inj_SledWithStrokeTransWizard_Sub* SledWithStrokeTransWizard = new Inj_SledWithStrokeTransWizard_Sub(_AppFrame, 0, true, wfFlags);
   _AppFrame->RegisterDialog(SledWithStrokeTransWizard);

   Inj_VelocityMoldCavityWizard_Sub* VelocityMoldCavityWizard = new Inj_VelocityMoldCavityWizard_Sub(_AppFrame, 0, true, wfFlags);
   _AppFrame->RegisterDialog(VelocityMoldCavityWizard);
#endif
   return _AppFrame;
}

#ifdef OBSOLETE

typedef void (*SHAREFUNC)(void *); 
static void ShareAppFrame(CAppFrame * app_frame)
{
   cSharedLibrary * library = cSharedLibrary::Library("cstguifuncs");
   if (library != NULL) {
      library->Load();
      SHAREFUNC share_func = (SHAREFUNC)library->FunctionAddress("ShareAppFrame");
      if (share_func != NULL) {
         share_func(app_frame);
      }
   }
}

static CAppFrame * _AppFrame = NULL;
CAppFrame * CreateAppFrame()
{
   if (_AppFrame == NULL) {
      _AppFrame = new MosaicFrameImpl;
      _AppFrame->Initialize();
      ShareAppFrame(_AppFrame);
   }
   return _AppFrame;
}

#endif

#define INSERT_LIST(type,parent,list)  \
   page = new type(parent); \
   list->append (page);

static PageList * _CreatePageList(QWidget * parent)
{
   PageList * list = new PageList;
   CPage * page = NULL;
   INSERT_LIST(Page1,parent,list)
   INSERT_LIST(Page2,parent,list)
   INSERT_LIST(Page3,parent,list)
   INSERT_LIST(Page4,parent,list)
   return list;
}

void * DemoFrameImpl::GetPageGroups()
{
   return NULL;
}

PageList * DemoFrameImpl::CreatePageList(QWidget * parent)
{
   return _CreatePageList(parent);
}

