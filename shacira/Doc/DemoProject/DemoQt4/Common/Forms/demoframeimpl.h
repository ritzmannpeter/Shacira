
#ifndef DemoFrameImpl_H
#define DemoFrameImpl_H

#include "CAppFrame.h"
#include "ui_demoframe.h"
class DemoFrameImpl : public CAppFrame
{
    Q_OBJECT
public:
   DemoFrameImpl(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   virtual ~DemoFrameImpl();
   virtual void * GetPageGroups();
   virtual PageList * CreatePageList(QWidget * parent);
   virtual int GetSoftKeyCount();
   virtual CFrame * GetNodeContainer();
   virtual CFrame * GetGroupContainer();
   virtual CFrame * GetPageContainer();
   virtual CFrame * GetSoftkeyContainer();
   virtual CFixText * GetPageHeader();
   virtual CFixText * GetStatusBar();
   virtual void Object(TRANSIENT_OBJECT_PTR object);
   virtual void Message(BOOL_T async,
                        CONST_STRING_T message,
                        CONST_STRING_T details = NULL,
                        CONST_STRING_T param1 = NULL,
                        CONST_STRING_T param2 = NULL,
                        CONST_STRING_T param3 = NULL,
                        CONST_STRING_T param4 = NULL);
   virtual void Message(BOOL_T async,
                        ERROR_REF_T error);
   CStartupForm * CreateStartupForm();

protected slots:
    virtual void languageChange();
private:
   Ui::DemoFrame _ui;
};

#endif


