
#include "ContextExplorer.h"
#include <qtimer.h>

class cContext;
class cSHProcess;

class ContextExplorerDialog : public ContextExplorer
{
   Q_OBJECT

public:
   ContextExplorerDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0);
   virtual ~ContextExplorerDialog();
   void SetProcess(cSHProcess * process);
   cContext * GetContext();
   bool Execute();

public slots:
   void ListContexts();
   void Choice();

private:
   cContext * _Context;
   cSHProcess * _Process;
   QTimer * _RefreshTimer;
};


