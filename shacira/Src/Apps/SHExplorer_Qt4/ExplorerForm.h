#ifndef _explorerform_h_
#define _explorerform_h_
#include "page.h"
#include "Generated/ui_ExplorerForm.h"
class ExplorerForm : public Page<Ui_ExplorerForm>
{
public:
   inline ExplorerForm(QWidget* parent = 0, const char* name = 0)
      : Page(parent, name)
   {
   };
   virtual ~ExplorerForm()
   {
   };
};
#endif
