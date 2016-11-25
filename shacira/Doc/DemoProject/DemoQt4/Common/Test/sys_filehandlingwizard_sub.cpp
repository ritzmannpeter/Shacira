// cor_prgwizard_sub.cpp: Schnittstelle für die Klasse Sys_FileHandlingWizard_Sub
//
//////////////////////////////////////////////////////////////////////

#include "sys_filehandlingwizard_sub.h"

#include <qdir.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include "cradiobutton.h"
#include "creqvalue.h"

extern cUserInfo user_info;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
Sys_FileHandlingWizard_Sub::Sys_FileHandlingWizard_Sub(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl, cContext* Context) :
    Wizard<Ui_Sys_FileHandlingWizard>(parent, name, modal, fl),
    _context(Context)
{
   _pMosaicFrame = reinterpret_cast<MosaicFrameImpl*>(parent);

    UCHAR_T pageIndex = 0;

    for (pageIndex = 0; pageIndex < 10; pageIndex++)
        pageTitleCustomTextID[pageIndex] = 0;

    setHelpEnabled(ui().WizardPage,     FALSE);
    setHelpEnabled(ui().WizardPage_0,   FALSE);
    setHelpEnabled(ui().WizardPage_2, FALSE);

    languageChange();

}


Sys_FileHandlingWizard_Sub::~Sys_FileHandlingWizard_Sub()
{
}


void Sys_FileHandlingWizard_Sub::languageChange()
{
//    Sys_FileHandlingWizard::languageChange();
   ui().retranslateUi(this);
    languageChangeButtonLine();

    UCHAR_T selection = 0;
    setTitle(2, selection);
}

void Sys_FileHandlingWizard_Sub::languageChangeButtonLine()
{
    backButton()->setText(tr("< Back"));
    nextButton()->setText(tr("Next >"));
    cancelButton()->setText(tr("Cancel"));
    finishButton()->setText(tr("Finish"));
}

void Sys_FileHandlingWizard_Sub::setInternalVarRef(cContext* context)
{
    _context = context;

    UCHAR_T pageIndex = 0;
    STRING_T default_Dir = "E:/";

    for (pageIndex = 0; pageIndex < 10; pageIndex++)
        pageTitleCustomTextID[pageIndex] = 0;

    UCHAR_T fileHandling = appropriate(page(0));
    if (fileHandling == 0) setTitle(2, 0);

    _qCheckDir = "";
    ui().CheckBoxReplaceExistFiles->show();
}

void Sys_FileHandlingWizard_Sub::setExternalVarRef()
{
    UCHAR_T pageIndex = 0;

    for (pageIndex = 0; pageIndex < 10; pageIndex++)
        pageTitleCustomTextID[pageIndex] = 0;
}

void Sys_FileHandlingWizard_Sub::accept()
{
    UCHAR_T selection = 0;
    BOOL_T bAccept = true;
    if ((selection == 2) || (selection == 4)) { // export/import dataset files
        BOOL_T bCreateMessage = false;
        STRING_T externalDir;
        if (externalDir == "") {
            bCreateMessage = true;
        }
        else {
        }

        if (bCreateMessage) {
            return;
        }
        else { // export files to file handling directory and check directory
            if ((selection == 0) && (_qCheckDir.isEmpty() == false)) {
	            QDir qDirExport(externalDir.c_str());

	            // check for existing package
	            qDirExport.setPath(externalDir.c_str());
	            if(qDirExport.cd(_qCheckDir)) {
                }
            }
        }
    }
    else if (selection == 8) { // question to delete all intern data set files
            bAccept = false;
    }

    if (bAccept == true)
        QDialog::accept();
}

void Sys_FileHandlingWizard_Sub::next()
{
    if (currentPage() == page(0)) {
        BOOL_T appropriatePage2 = true;
        BOOL_T appropriatePage3 = false;
        UCHAR_T selection = 0;
        if (selection == 1) { // load data group selection
            STRING_T fileName;
            if (fileName == "") {
                return;
            }

       }
        else if ((selection == 2) || (selection == 4)) {
            appropriatePage2 = false;
            appropriatePage3 = true;
            setTitle(2, selection);

             // check to removable and net drives
        }

        setAppropriate(page(1), appropriatePage2);
        setAppropriate(page(2), appropriatePage3);
    }

    QWizard::next();
}

void Sys_FileHandlingWizard_Sub::setTitle(UCHAR_T page_index, UCHAR_T selection)
{
    QString directoryDescription = "";

    if (selection == 0) {
        QString titleText = "";
        if (pageTitleCustomTextID[page_index])
        {
            titleText = CWidgetBase::Translate(cText::GetText(pageTitleCustomTextID[page_index]), "custom");
        }
        else {
            titleText = tr("Export files");
        }

        Wizard::setTitle(page(page_index), titleText);
        directoryDescription = tr("Export directory");
    }
    else if (selection == 2) {
        Wizard::setTitle(page(page_index), tr( "Import mulptiple mold data files" ));
        directoryDescription = tr("Import directory");
    }
    else if (selection == 4) {
        Wizard::setTitle(page(page_index), tr( "Export multiple mold data files" ));
        directoryDescription = tr("Export directory");
    }

}

void Sys_FileHandlingWizard_Sub::selectedDeleteAll(int state)
{
    BOOL_T nextEnable = (state == 2) ? false : true;
    BOOL_T finishEnable = (state == 2) ? true : false;
    
    setNextEnabled(ui().WizardPage, nextEnable);
    setFinishEnabled(ui().WizardPage, finishEnable);
}

void Sys_FileHandlingWizard_Sub::setTitleCustomTextID(UCHAR_T page_index, ULONG_T customText_TitleID)
{
    if (page_index < 10)
    {
        pageTitleCustomTextID[page_index] = customText_TitleID;

        QString titleText = CWidgetBase::Translate(cText::GetText(pageTitleCustomTextID[page_index]), "custom");
        Wizard::setTitle(page(page_index), titleText);
    }
}

//////////////////////////////////////////////////////////////////////
// Methodes
//////////////////////////////////////////////////////////////////////
