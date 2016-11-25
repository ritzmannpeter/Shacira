
#ifndef _CServerList_h_
#define _CServerList_h_

#include <qlistview.h>
#include <qtimer.h>

class cSHProcess;
class cContext;
class cContextController;

class CServerList : public QListView
{
   Q_OBJECT
public:
   CServerList(QWidget * parent, cSHProcess * process);
   virtual ~ CServerList();
public slots:
   virtual void Refresh();
public:

public:
   virtual void AddContext(cContext * context);
private:
private:
   QTimer * _Timer;
   cSHProcess * _Process;
   cContextController * _ContextController;
};

#endif
