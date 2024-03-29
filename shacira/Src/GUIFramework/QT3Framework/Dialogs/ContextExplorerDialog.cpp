
#include "FirstHeader.h"
#include "ContextExplorerDialog.h"
#include "System/Process/cSHProcess.h"
#include "System/Database/cContext.h"
#include "System/Objects/cProxy.h"
#include <qlistview.h>
#include "qt4port.h"

ContextExplorerDialog::ContextExplorerDialog(QWidget* parent, const char* name, bool modal, WFlags fl) :
   ContextExplorer(parent, name, modal, fl ? fl : Qt::WStyle_Customize|Qt::WStyle_NormalBorder|Qt::WStyle_Title)
{
   _Context = NULL;
   _Process = NULL;
   connect((QObject*)CancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
   connect((QObject*)ChoiceBtn, SIGNAL(clicked()), this, SLOT(Choice()));
   connect((QObject*)RefreshBtn, SIGNAL(clicked()), this, SLOT(ListContexts()));
   _RefreshTimer = new QTimer(this);
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(ListContexts()));
//   _RefreshTimer->start(3000);
}

ContextExplorerDialog::~ContextExplorerDialog()
{
}

void ContextExplorerDialog::SetProcess(cSHProcess * process)
{
   _Process = process;
}

cContext * ContextExplorerDialog::GetContext()
{
   return _Context;
}

bool ContextExplorerDialog::Execute()
{
   cSystemUtils::Suspend(2000);
   ListContexts();
   DialogCode result = (DialogCode)exec();
   if (result == Accepted) {
      return true;
   } else {
      return false;
   }
}

void ContextExplorerDialog::ListContexts()
{
   listView1->clear();
   if (_Process != NULL) {
      STRING_LIST_T context_names;
      _Process->ContextNames(context_names, REMOTE_CONTEXTS);
      if (context_names.size() > 0) {
         STRING_LIST_T::const_iterator i = context_names.cbegin();
         while (i != context_names.cend()) {
            STRING_T context_name = (*i);
            cProxy * proxy = _Process->Proxy(context_name.c_str());
            if (proxy != NULL) {
               QListViewItem * item = new QListViewItem(listView1);
               item->setText(0, context_name.c_str());
               item->setText(1, proxy->get_Computer().c_str());
               item->setText(2, proxy->get_IPAddress().c_str());
               char _port[32] = {0};
               ULONG_T port = proxy->get_Port();
               SafePrintf(_port, sizeof(_port), "%d", port);
               item->setText(3, _port);
            } else {
               cContext * context = _Process->Context(context_name.c_str(), REMOTE_CONTEXTS);
               if (context != NULL) {
                  QListViewItem * item = new QListViewItem(listView1);
                  item->setText(0, context_name.c_str());
#ifdef lassma
                  item->setText(1, proxy->get_Computer().c_str());
                  item->setText(2, proxy->get_IPAddress().c_str());
                  char _port[32] = {0};
                  ULONG_T port = proxy->get_Port();
                  SafePrintf(_port, sizeof(_port), "%d", port);
                  item->setText(3, _port);
#endif
               }
            }
            i++;
         }
         QListViewItem * first = listView1->firstChild();
         if (first != NULL) {
            listView1->setCurrentItem(first);
            listView1->setSelected(first,TRUE);
         }
      } else {
      }
   } else {
   }
}

void ContextExplorerDialog::Choice()
{
   QListViewItem * selected = listView1->selectedItem();
   if (selected != NULL) {
      QString context_name = selected->text(0);
      if (_Process != NULL) {
         _Context = _Process->Context(CONST_STRING(context_name), REMOTE_CONTEXTS);
         if (_Context != NULL) {
            accept();
         }
      }
   }
}
