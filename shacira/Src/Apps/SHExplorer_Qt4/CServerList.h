
#ifndef _CServerList_h_
#define _CServerList_h_

#ifdef QT4
#include "listview.h"
#include "qt4port.h"
#define CSERVERLIST_BASE_CLASS      ListView
#else
#include <qlistview.h>
#define CSERVERLIST_BASE_CLASS      QListView
#endif


class cSHProcess;
class cContext;
class cContextController;
class qtimer;

class CServerList : public CSERVERLIST_BASE_CLASS
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
