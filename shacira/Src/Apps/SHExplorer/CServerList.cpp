
#include "FirstHeader.h"
#include "cserverlist.h"
#include "System/Process/cSHProcess.h"
#include "System/Database/cContext.h"
#include "System/Database/cVarDef.h"
#include "System/Objects/cProxy.h"
#include "System/Threads/cControlThread.h"
#include "System/cTimeObject.h"
#include <qapplication.h>
#include <qdatetime.h>

class CContextItem;
typedef std::map<STRING_T, CContextItem*> ITEM_MAP_T;
class CContextItem : public QListViewItem
{
public:
   CContextItem(QListView * parent, cContext * context)
      : QListViewItem(parent)
   {
      _VarCount = 0;
      _IsNew = true;
      _IsConnected = false;
      _Context = context;
      _ContextName = _Context->get_Name();
      _ContextItems[_ContextName.c_str()] = this;
   };
   ~CContextItem()
   {
      _ContextItems.erase(_ContextName.c_str());
   };
   cContext * Context()
   {
      return _Context;
   };
   STRING_T ContextName()
   {
      return _ContextName;
   };
   static CContextItem * Item(cContext * context)
   {
      STRING_T context_name = context->get_Name();
      ITEM_MAP_T::const_iterator i = _ContextItems.find(context_name.c_str());
      if (i == _ContextItems.end()) {
         return NULL;
      } else {
         return (*i).second;
      }
   };
   BOOL_T IsConnected()
   {
      return _IsConnected;
   };
private:
   cContext * _Context;
   STRING_T _ContextName;
public:
   static ITEM_MAP_T _ContextItems;
   BOOL_T _IsConnected;
   BOOL_T _IsNew;
   ULONG_T _VarCount;
};
ITEM_MAP_T CContextItem::_ContextItems;

class cContextController : public cControlThread
{
public:
   cContextController(ITEM_MAP_T * items)
   {
      _Items = items;
      _Name = "ContextController";
   };
   ~cContextController()
   {
   };
   virtual INT_T MainFunc(void *extra)
   {
MAINFUNC_PROLOG(_Name.c_str())
   while (!(_Terminated || _Terminating)) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      try {
ULONG_T t0 = cSystemUtils::RealtimeOffset();
         STRING_T name = "no name";
         ITEM_MAP_T::const_iterator i = _Items->begin();
         while (i != _Items->end()) {
            try {
               name = (*i).first;
               InfoPrintf("test %s\n", name.c_str());
               CContextItem * item = (*i).second;
               cContext * context = item->Context();
               if (context != NULL) {
                  if (context->Ping()) {
                     InfoPrintf("%s reached\n", name.c_str());
                     if (item->_IsNew) {
                        item->_IsNew = false;
                        ULONG_T var_count = 0;
                        InfoPrintf("connect to %s\n", name.c_str());
                        context->Connect();
                        InfoPrintf("connected to %s\n", name.c_str());
                        STRING_LIST_T var_names;
                        context->VariableNames(var_names);
                        STRING_LIST_T::const_iterator vn = var_names.begin();
                        while (vn != var_names.end()) {
                           cVarDef * var_def = context->VarDef((*vn).c_str());
                           if (var_def->_SystemFlags != 0) {
                              var_count++;
                           }
                           vn++;
                        }
                        item->_VarCount = var_count;
                        InfoPrintf("context %s reachable, %d variables\n", name.c_str(), var_count);
                     } else {
                        if (!item->_IsConnected) {
                           InfoPrintf("%s reachable again\n", name.c_str());
                        }
                     }
                     item->_IsConnected = true;
                  } else {
                     if (item->_IsConnected) {
                        InfoPrintf("%s no more reachable\n", name.c_str());
                     } else {
                        InfoPrintf("%s not reachable\n", name.c_str());
                     }
                     item->_IsConnected = false;
                  }
               }
            } catch (cError & e) {
               InfoPrintf("error accessing %s: %s\n", name.c_str(), (const char *)e);
            } catch (...) {
               InfoPrintf("unknown error accessing %s\n", name.c_str());
            }
            i++;
            cSystemUtils::Suspend(100);
         }
ULONG_T t1 = cSystemUtils::RealtimeOffset() - t0;
InfoPrintf("cycle: %d ms\n", t1);
         cSystemUtils::Suspend(100);
      } catch (cError & e) {
         InfoPrintf("error testing contexts: %s\n", (const char *)e);
      } catch (...) {
         InfoPrintf("unknown error testing contexts\n");
      }
MAINFUNC_LOOP_EPILOG
		if (!_Terminated) cSystemUtils::Suspend(_IdleTime);
   }
   return 0;
MAINFUNC_EPILOG
   };
private:
   ITEM_MAP_T * _Items;
};

CServerList::CServerList(QWidget * parent, cSHProcess * process)
 : QListView(parent)
{
   _Process = process;
   addColumn("Zeit                                                  ");
   addColumn("Context");
   addColumn("Computer");
   addColumn("IP-Addresse");
   addColumn("Port");
   addColumn("Verbindung");
   addColumn("Variablen");
   setSorting(0, false);
   _Timer = new QTimer(this);
   connect(_Timer, SIGNAL(timeout()), SLOT(Refresh()));
   _Timer->start(1000);
   _ContextController = new cContextController(&CContextItem::_ContextItems);
   _ContextController->Start();
}

CServerList::~CServerList()
{
}

void CServerList::Refresh()
{
   if (_Process != NULL) {
      STRING_LIST_T context_names;
      _Process->ContextNames(context_names, REMOTE_CONTEXTS);
      STRING_LIST_T::const_iterator i = context_names.begin();
      while (i != context_names.end()) {
         STRING_T context_name = (*i);
         cContext * context = _Process->Context(context_name.c_str(), REMOTE_CONTEXTS);
         AddContext(context);
         i++;
      }
   }
}

void CServerList::AddContext(cContext * context)
{
   if (context != NULL) {
      STRING_T context_name = context->get_Name();
try {
      cProxy * proxy = _Process->Proxy(context_name.c_str());
      STRING_T ip_addr = "?";
      STRING_T computer_name = "?";
      if (proxy != NULL) {
         ip_addr = proxy->get_IPAddress();
         computer_name = proxy->get_Computer();
         if (_stricmp(ip_addr.c_str(), "127.0.0.1") == 0) {
            InfoPrintf("local address %s for context %s on computer %s: skipped\n",
                       ip_addr.c_str(), context_name.c_str(), computer_name.c_str());
            return;
         }
      } else {
         InfoPrintf("null proxy for context %s: skipped\n", context_name.c_str());
         return;
      }
      QDateTime time = QDateTime::currentDateTime();
      CContextItem * item = CContextItem::Item(context);
      if (item == NULL) {
         InfoPrintf("new context %s\n", context_name.c_str());
         char _port[32] = "?";
         if (proxy != NULL) {
            cTimeObject time_stamp = proxy->get_TimeStamp();
            ULONG_T secs = time_stamp;
            int sec = time_stamp.Get(cTimeObject::SECOND);
            int minute = time_stamp.Get(cTimeObject::MINUTE);
            int hour = time_stamp.Get(cTimeObject::HOUR);
            int day = time_stamp.Get(cTimeObject::DAY);
            int month = time_stamp.Get(cTimeObject::MONTH);
            int year = time_stamp.Get(cTimeObject::YEAR);
            time.setTime_t(secs);
            ip_addr = proxy->get_IPAddress();
            computer_name = proxy->get_Computer();
            ULONG_T port = proxy->get_Port();
            sprintf(_port, "%d", port);
         }
         item = new CContextItem(this, context);
         item->setText(0, time.toString());
         item->setText(1, context->get_Name().c_str());
         item->setText(2, computer_name.c_str());
         item->setText(3, ip_addr.c_str());
         item->setText(4, _port);
      } else {
         STRING_T ip_addr = "?";
         STRING_T computer_name = "?";
         char _port[32] = "?";
         if (proxy != NULL) {
            cTimeObject time_stamp = proxy->get_TimeStamp();
            ULONG_T secs = time_stamp;
            int sec = time_stamp.Get(cTimeObject::SECOND);
            int minute = time_stamp.Get(cTimeObject::MINUTE);
            int hour = time_stamp.Get(cTimeObject::HOUR);
            int day = time_stamp.Get(cTimeObject::DAY);
            int month = time_stamp.Get(cTimeObject::MONTH);
            int year = time_stamp.Get(cTimeObject::YEAR);
            time.setTime_t(secs);
            ip_addr = proxy->get_IPAddress();
            computer_name = proxy->get_Computer();
            ULONG_T port = proxy->get_Port();
            sprintf(_port, "%d", port);
         }
         item->setText(0, time.toString());
         item->setText(1, context_name.c_str());
         item->setText(2, computer_name.c_str());
         item->setText(3, ip_addr.c_str());
         item->setText(4, _port);
      }
      BOOL_T is_connected = item->IsConnected();
      if (is_connected) {
         item->setText(5, "verbunden");
      } else {
         item->setText(5, "getrennt");
      }
      ULONG_T var_count = item->_VarCount;
      char text[0x50] = {0};
      sprintf(text, "%d", var_count);
      item->setText(6, text);
} catch (...) {
   InfoPrintf("failed to add context %s\n", context_name.c_str());
}
   }
}
   
