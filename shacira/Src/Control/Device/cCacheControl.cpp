//## begin module%3FD5A20402AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FD5A20402AF.cm

//## begin module%3FD5A20402AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FD5A20402AF.cp

//## Module: cCacheControl%3FD5A20402AF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cCacheControl.cpp

//## begin module%3FD5A20402AF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FD5A20402AF.additionalIncludes

//## begin module%3FD5A20402AF.includes preserve=yes
//## end module%3FD5A20402AF.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
// cDevice
#include "Control/Device/cDevice.h"
// cCacheControl
#include "Control/Device/cCacheControl.h"
// cCache
#include "Control/Device/cCache.h"
//## begin module%3FD5A20402AF.additionalDeclarations preserve=yes
//## end module%3FD5A20402AF.additionalDeclarations


// Class cCacheControl 



cCacheControl::cCacheControl()
  //## begin cCacheControl::cCacheControl%.hasinit preserve=no
      : _Device(NULL)
  //## end cCacheControl::cCacheControl%.hasinit
  //## begin cCacheControl::cCacheControl%.initialization preserve=yes
  //## end cCacheControl::cCacheControl%.initialization
{
  //## begin cCacheControl::cCacheControl%.body preserve=yes
_ASSERT_UNCOND
  //## end cCacheControl::cCacheControl%.body
}

cCacheControl::cCacheControl(const cCacheControl &right)
  //## begin cCacheControl::cCacheControl%copy.hasinit preserve=no
      : _Device(NULL)
  //## end cCacheControl::cCacheControl%copy.hasinit
  //## begin cCacheControl::cCacheControl%copy.initialization preserve=yes
  //## end cCacheControl::cCacheControl%copy.initialization
{
  //## begin cCacheControl::cCacheControl%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCacheControl::cCacheControl%copy.body
}

cCacheControl::cCacheControl (cDevice *device)
  //## begin cCacheControl::cCacheControl%1070963657.hasinit preserve=no
      : _Device(NULL)
  //## end cCacheControl::cCacheControl%1070963657.hasinit
  //## begin cCacheControl::cCacheControl%1070963657.initialization preserve=yes
  //## end cCacheControl::cCacheControl%1070963657.initialization
{
  //## begin cCacheControl::cCacheControl%1070963657.body preserve=yes
   _Device = device;
   _Name = device->get_Name();
   _IdleTime = 0;
  //## end cCacheControl::cCacheControl%1070963657.body
}


cCacheControl::~cCacheControl()
{
  //## begin cCacheControl::~cCacheControl%.body preserve=yes
  //## end cCacheControl::~cCacheControl%.body
}



//## Other Operations (implementation)
void cCacheControl::SetCache (cCache *cache)
{
  //## begin cCacheControl::SetCache%1070963658.body preserve=yes
   if (cache != NULL) {
      STRING_T cache_name = cache->get_Name();
      _Caches[cache_name.c_str()] = cache;
   } else {
      ErrorPrintf("null cahche supplied to cache control\n");
   }
  //## end cCacheControl::SetCache%1070963658.body
}

INT_T cCacheControl::ControlFunc ()
{
  //## begin cCacheControl::ControlFunc%1070963659.body preserve=yes
CONTROLFUNC_PROLOG(_Name.c_str())
   if (_IdleTime == 0) {
      _IdleTime = MinIdleTime();
   }
   cObjectLock __lock__(&(_Device->_LockMutex));
   std::map<STRING_T,cCache*>::const_iterator i = _Caches.cbegin();
   while (i != _Caches.cend()) {
      cCache * cache = (*i).second;
      cache->Save(_IdleTime);
      i++;
   }
CONTROLFUNC_EPILOG
   return 0;
  //## end cCacheControl::ControlFunc%1070963659.body
}

ULONG_T cCacheControl::MinIdleTime ()
{
  //## begin cCacheControl::MinIdleTime%1084967064.body preserve=yes
   ULONG_T min = 10000;
   std::map<STRING_T,cCache*>::const_iterator i = _Caches.cbegin();
   while (i != _Caches.cend()) {
      cCache * cache = (*i).second;
      ULONG_T min_idle_time = cache->MinIdleTime();
      if (min_idle_time < min) {
         min = min_idle_time;
      }
      i++;
   }
   return min;
  //## end cCacheControl::MinIdleTime%1084967064.body
}

// Additional Declarations
  //## begin cCacheControl%3FD5A20402AF.declarations preserve=yes
  //## end cCacheControl%3FD5A20402AF.declarations

//## begin module%3FD5A20402AF.epilog preserve=yes
//## end module%3FD5A20402AF.epilog
