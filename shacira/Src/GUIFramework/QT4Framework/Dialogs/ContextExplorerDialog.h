
#ifdef QT4
#include "ui_ContextExplorer.h"
#else
#include "ContextExplorer.h"
#endif
#include <qtimer.h>
#include "qt4port.h"

class cContext;
class cSHProcess;

#ifdef QT4
class ContextExplorerDialog : public QDialog
#else
class ContextExplorerDialog : public ContextExplorer
#endif
{
   Q_OBJECT

public:
   ContextExplorerDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WIDGET_FLAGS_TYPE fl = 0);
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
#ifdef QT4
   Ui::ContextExplorer _ui;
#endif
};


