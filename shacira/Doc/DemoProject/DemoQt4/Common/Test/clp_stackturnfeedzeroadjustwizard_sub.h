// clp_stackturnfeedzeroadjustwizard_sub.h: Schnittstelle für die Klasse Clp_StackTurnFeedZeroAdjustWizard_sub
//
//////////////////////////////////////////////////////////////////////

#if !defined CLP_STACKTURNFEEDZEROADJUSTWIZARD_SUB_INCLUDED
#define CLP_STACKTURNFEEDZEROADJUSTWIZARD_SUB_INCLUDED

#include "wizard.h"
#include "ui_clp_stackturnfeedzeroadjustwizard.h"

class QWidget;
class cContext;

class Clp_StackTurnFeedZeroAdjustWizard_Sub : public Wizard<Ui_Clp_StackTurnFeedZeroAdjustWizard>
{
    Q_OBJECT

public:
   Clp_StackTurnFeedZeroAdjustWizard_Sub( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WindowFlags fl = 0, cContext* Context=NULL);
   virtual ~Clp_StackTurnFeedZeroAdjustWizard_Sub();

   void showPage(QWidget* page);
   void setContext(cContext* context) { _context = context; };
   void setInternalVarRef(cContext* context = NULL);
   void setExternalVarRef();

protected:
   cContext* _context;

   void languageChange_WizardPage( QWidget* page );
   void languageChangeButtonLine();

protected slots:
   void languageChange();
   void accept();
};

#endif
