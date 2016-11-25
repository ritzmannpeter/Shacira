
#ifndef _uiupdate_h_
#define _uiupdate_h_

#include <qwidget.h>
#include <qapplication.h>

class UiUpdate
{
public:
   UiUpdate(bool syncFlag);
   virtual ~UiUpdate();
private:
   bool _syncFlag;
};

#endif
