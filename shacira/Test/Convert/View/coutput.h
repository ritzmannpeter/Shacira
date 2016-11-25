
#ifndef _COutput_h_
#define _COutput_h_

#include <qlistview.h>

class cSubfile;

class COutput : public QListView
{
   Q_OBJECT
public:
   COutput(QWidget * parent);
   virtual ~ COutput();
   void AddLine(const char * line);
public slots:
   void Clear();
private:
   QListViewItem * _LastLine;
};

#endif
