
#ifndef _csignalmanager_h_
#define _csignalmanager_h_

class CWidgetBase;

#include "System/Memory/cPtrList.h"
#include <qstring.h>

typedef std::map<QString,cPtrList*> MANAGER_MAP_T;;

class cSignalManager
{
public:
   cSignalManager();
   virtual ~cSignalManager();
   void ListenTo(const QString & name, CWidgetBase * sender);
   void Signal(ULONG_T signal, const QString & sender_name, CWidgetBase * sender);
private:
   MANAGER_MAP_T _Listeners;
private:
   cPtrList * Listeners(const QString & name);
};


#endif


