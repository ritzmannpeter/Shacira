// clp_stackturnfeedzeroadjustwizard_sub.h: Schnittstelle für die Klasse Clp_StackTurnFeedZeroAdjustWizard_sub
//
//////////////////////////////////////////////////////////////////////
#include <qpushbutton.h>
#include <creqvalue.h>
#include <cactvalue.h>

#include "creqvalue.h"
#include "clp_stackturnfeedzeroadjustwizard_sub.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
Clp_StackTurnFeedZeroAdjustWizard_Sub::Clp_StackTurnFeedZeroAdjustWizard_Sub( QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl, cContext* Context)
    : Wizard<Ui_Clp_StackTurnFeedZeroAdjustWizard>(parent, name, modal, fl),
    _context(Context)
{
   setBackEnabled(ui().WizardPage, FALSE);
   setNextEnabled(ui().WizardPage, TRUE);
   setHelpEnabled(ui().WizardPage, FALSE);

   languageChangeButtonLine();

   setNextEnabled(ui().WizardPage_0, TRUE);
   setHelpEnabled(ui().WizardPage_0, FALSE);
   setFinishEnabled(ui().WizardPage_0, TRUE);
}


Clp_StackTurnFeedZeroAdjustWizard_Sub::~Clp_StackTurnFeedZeroAdjustWizard_Sub()
{
}


void Clp_StackTurnFeedZeroAdjustWizard_Sub::showPage( QWidget* page )
{
    if ( page == ui().WizardPage ) {
        nextButton()->setText( tr( "Next >" ) );
    }
    else if ( page == ui().WizardPage_0 ) {
        finishButton()->setText( tr( "Apply >" ) );
    } 

    Wizard::showPage(page);
}

void Clp_StackTurnFeedZeroAdjustWizard_Sub::languageChange()
{
//    Clp_StackTurnFeedZeroAdjustWizard::languageChange();
   ui().retranslateUi(this);
    languageChangeButtonLine();
}

void Clp_StackTurnFeedZeroAdjustWizard_Sub::languageChangeButtonLine()
{
    backButton()->setText( tr( "< Back" ) );
    nextButton()->setText( tr( "Next >" ) );
    cancelButton()->setText( tr( "Cancel" ) );
    finishButton()->setText( tr( "Finish" ) );
}

void Clp_StackTurnFeedZeroAdjustWizard_Sub::setInternalVarRef(cContext* context)
{
    _context = context;
}

void Clp_StackTurnFeedZeroAdjustWizard_Sub::setExternalVarRef()
{
    FLOAT_T StrAdjustWizard;
}

void Clp_StackTurnFeedZeroAdjustWizard_Sub::accept()
{
    QString wName = currentPage()->objectName();

    if (wName == "WizardPage_2") {
        FLOAT_T ActStr;
    }

    QWizard::accept();
}

//////////////////////////////////////////////////////////////////////
// Methodes
//////////////////////////////////////////////////////////////////////
