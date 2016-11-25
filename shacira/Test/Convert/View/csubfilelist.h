
#ifndef _CSubfileList_h_
#define _CSubfileList_h_

#include <qlistview.h>
#include <qtimer.h>
#include "FirstHeader.h"
#include "Generated/DatasetViewerForm.h"

class cSubfile;
class cContext;

class CSubfileList : public QListView
{
   Q_OBJECT
public:
   CSubfileList(QWidget * parent, DatasetViewerForm * widget);
   virtual ~ CSubfileList();
public slots:
   virtual void Clear();
   virtual void SelectFile();
   virtual void SelectTemplate();
   virtual void SelectRegtext();
private:
   cContext * _Context;
   DatasetViewerForm * _Viewer;
};

#endif
