#ifndef _qt3synctest_h_
#define _qt3synctest_h_
#include "ui_qt3synctest.h"
class Qt3SyncTest : public QWidget
{
public:
   inline Qt3SyncTest(QWidget* parent = 0, const char* name = 0)
      : QWidget(parent)
   {
      _ui.setupUi(this);
   };
   virtual ~Qt3SyncTest()
   {
   };
   Ui::Qt3SyncTest _ui;
};
#endif
