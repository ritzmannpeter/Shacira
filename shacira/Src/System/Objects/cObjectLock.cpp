//## begin module%3A4B09E700B1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A4B09E700B1.cm

//## begin module%3A4B09E700B1.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A4B09E700B1.cp

//## Module: cObjectLock%3A4B09E700B1; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cObjectLock.cpp

//## begin module%3A4B09E700B1.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A4B09E700B1.additionalIncludes

//## begin module%3A4B09E700B1.includes preserve=yes
//## end module%3A4B09E700B1.includes

// cObjectLock
#include "System/Objects/cObjectLock.h"
//## begin module%3A4B09E700B1.additionalDeclarations preserve=yes
//## end module%3A4B09E700B1.additionalDeclarations


// Class cObjectLock 


cObjectLock::cObjectLock()
  //## begin cObjectLock::cObjectLock%.hasinit preserve=no
      : _Mutex(NULL)
  //## end cObjectLock::cObjectLock%.hasinit
  //## begin cObjectLock::cObjectLock%.initialization preserve=yes
  //## end cObjectLock::cObjectLock%.initialization
{
  //## begin cObjectLock::cObjectLock%.body preserve=yes
  //## end cObjectLock::cObjectLock%.body
}

cObjectLock::cObjectLock(const cObjectLock &right)
  //## begin cObjectLock::cObjectLock%copy.hasinit preserve=no
      : _Mutex(NULL)
  //## end cObjectLock::cObjectLock%copy.hasinit
  //## begin cObjectLock::cObjectLock%copy.initialization preserve=yes
  //## end cObjectLock::cObjectLock%copy.initialization
{
  //## begin cObjectLock::cObjectLock%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cObjectLock::cObjectLock%copy.body
}

cObjectLock::cObjectLock (cMutexSem *mutex, CONST_STRING_T file, INT_T line)
  //## begin cObjectLock::cObjectLock%977993517.hasinit preserve=no
      : _Mutex(NULL)
  //## end cObjectLock::cObjectLock%977993517.hasinit
  //## begin cObjectLock::cObjectLock%977993517.initialization preserve=yes
  //## end cObjectLock::cObjectLock%977993517.initialization
{
  //## begin cObjectLock::cObjectLock%977993517.body preserve=yes
_ASSERT_COND(mutex != NULL)
   _Mutex = mutex;
   _Mutex->request();
  //## end cObjectLock::cObjectLock%977993517.body
}


cObjectLock::~cObjectLock()
{
  //## begin cObjectLock::~cObjectLock%.body preserve=yes
_ASSERT_COND(_Mutex != NULL)
   _Mutex->release();
  //## end cObjectLock::~cObjectLock%.body
}


// Additional Declarations
  //## begin cObjectLock%3A4B09E700B1.declarations preserve=yes
  //## end cObjectLock%3A4B09E700B1.declarations

//## begin module%3A4B09E700B1.epilog preserve=yes
//## end module%3A4B09E700B1.epilog
