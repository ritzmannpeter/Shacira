// sys_filehandlingwizard_sub.h: Schnittstelle für die Klasse Sys_FileHandlingWizard_Sub
//
//////////////////////////////////////////////////////////////////////

#if !defined SYS_FILEHANDLINGWIZARD_SUB_INCLUDED
#define SYS_FILEHANDLINGWIZARD_SUB_INCLUDED

#include "wizard.h"
#include "ui_sys_filehandlingwizard.h"

class MosaicFrameImpl;
class cContext;

class Sys_FileHandlingWizard_Sub : public Wizard<Ui_Sys_FileHandlingWizard>
{
    Q_OBJECT

public:
    Sys_FileHandlingWizard_Sub(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WindowFlags fl = 0, cContext* Context=NULL);
    virtual ~Sys_FileHandlingWizard_Sub();

    void setContext(cContext* context) { _context = context; };
    void setInternalVarRef(cContext* context = NULL);
    void setExternalVarRef();
   void setTitleCustomTextID(UCHAR_T page_index, ULONG_T customText_TitleID);

protected:
    void languageChangeButtonLine();

    cContext* _context;

protected slots:
    void accept();
    void next();
    void selectedDeleteAll(int state);
    void languageChange();

private:
    void setTitle(UCHAR_T page_index, UCHAR_T selection);

    MosaicFrameImpl* _pMosaicFrame;
    QString _qCheckDir;
    ULONG_T pageTitleCustomTextID[10];
};

#endif
