//## begin module%3C4EE4B900CF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EE4B900CF.cm

//## begin module%3C4EE4B900CF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EE4B900CF.cp

//## Module: cProxyTable%3C4EE4B900CF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyTable.cpp

//## begin module%3C4EE4B900CF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C4EE4B900CF.additionalIncludes

//## begin module%3C4EE4B900CF.includes preserve=yes
//## end module%3C4EE4B900CF.includes

// cCellProxy
#include "System/Process/cCellProxy.h"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cProxy
#include "System/Objects/cProxy.h"
// cProxyTable
#include "System/Comm/cProxyTable.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
// cChannelProxy
#include "System/Channel/cChannelProxy.h"
//## begin module%3C4EE4B900CF.additionalDeclarations preserve=yes
//## end module%3C4EE4B900CF.additionalDeclarations


// Class cProxyTable 



cProxyTable::cProxyTable()
  //## begin cProxyTable::cProxyTable%.hasinit preserve=no
  //## end cProxyTable::cProxyTable%.hasinit
  //## begin cProxyTable::cProxyTable%.initialization preserve=yes
  //## end cProxyTable::cProxyTable%.initialization
{
  //## begin cProxyTable::cProxyTable%.body preserve=yes
  //## end cProxyTable::cProxyTable%.body
}

cProxyTable::cProxyTable(const cProxyTable &right)
  //## begin cProxyTable::cProxyTable%copy.hasinit preserve=no
  //## end cProxyTable::cProxyTable%copy.hasinit
  //## begin cProxyTable::cProxyTable%copy.initialization preserve=yes
  //## end cProxyTable::cProxyTable%copy.initialization
{
  //## begin cProxyTable::cProxyTable%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProxyTable::cProxyTable%copy.body
}


cProxyTable::~cProxyTable()
{
  //## begin cProxyTable::~cProxyTable%.body preserve=yes

// Das Zerstoeren der Proxy-Objekte fuehrt zum Zerstoeren der eigenen
// CORBA-Objekt-Referenzen was zu Exceptions fuehrt.
// Bis dieses Problem geloest ist werden beim Zerstoeren der Proxy-Tabelle
// keine Proxy-Objekte mehr zerstoert.

//   std::map<STRING_T,cProxyObject*>::const_iterator i = _Proxies.cbegin();
//   while (i != _Proxies.cend()) {
//      cProxyObject * proxy_object = (*i).second;
//	     DELETE_OBJECT(cProxyObject, proxy_object)
//	     i++;
//   }

  //## end cProxyTable::~cProxyTable%.body
}



//## Other Operations (implementation)
cProxy * cProxyTable::Proxy (CONST_STRING_T name)
{
  //## begin cProxyTable::Proxy%1011794629.body preserve=yes
   cObjectLock __lock__(&_TableMutex);
   if (_Proxies.size() > 0) {
      std::map<STRING_T,cProxy*>::const_iterator i = _Proxies.find(name);
      if (i != _Proxies.cend()) {
         cProxy * proxy = (*i).second;
         return proxy;
      } else {
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cProxyTable::Proxy%1011794629.body
}

cCellProxy * cProxyTable::CellProxy (CONST_STRING_T name)
{
  //## begin cProxyTable::CellProxy%1011861108.body preserve=yes
   cObjectLock __lock__(&_TableMutex);
   cProxy * proxy = Proxy(name);
   if (proxy != NULL) {
      int object_type = proxy->get_Type();
      if (object_type == OT_LOCAL_CELL_PROXY ||
          object_type == OT_CORBA_CELL_PROXY) {
         return (cCellProxy*)proxy;
      } else {
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cProxyTable::CellProxy%1011861108.body
}

cChannelProxy * cProxyTable::ChannelProxy (CONST_STRING_T name)
{
  //## begin cProxyTable::ChannelProxy%1011948773.body preserve=yes
   cObjectLock __lock__(&_TableMutex);
   cProxy * proxy = Proxy(name);
   if (proxy != NULL) {
      int object_type = proxy->get_Type();
      if (object_type == OT_COS_EVENTCHANNEL_PROXY) {
         return (cChannelProxy*)proxy;
      } else {
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cProxyTable::ChannelProxy%1011948773.body
}

void cProxyTable::SetProxy (cProxy *proxy)
{
  //## begin cProxyTable::SetProxy%1011794627.body preserve=yes
   cObjectLock __lock__(&_TableMutex);
   STRING_T name = proxy->get_ProxyName();
   cProxy * _proxy = Proxy(name.c_str());
   if (_proxy == NULL) {
      proxy->AddRef();
      _Proxies[name.c_str()] = proxy;
   } else {
      _proxy->Update(proxy);
   }
  //## end cProxyTable::SetProxy%1011794627.body
}

// Additional Declarations
  //## begin cProxyTable%3C4EE4B900CF.declarations preserve=yes
  //## end cProxyTable%3C4EE4B900CF.declarations

//## begin module%3C4EE4B900CF.epilog preserve=yes
//## end module%3C4EE4B900CF.epilog
