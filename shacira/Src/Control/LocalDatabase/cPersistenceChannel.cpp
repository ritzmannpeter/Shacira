//## begin module%4039DEBE033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4039DEBE033C.cm

//## begin module%4039DEBE033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4039DEBE033C.cp

//## Module: cPersistenceChannel%4039DEBE033C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cPersistenceChannel.cpp

//## begin module%4039DEBE033C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4039DEBE033C.additionalIncludes

//## begin module%4039DEBE033C.includes preserve=yes
//## end module%4039DEBE033C.includes

// cContext
#include "System/Database/cContext.h"
// cPersistenceManager
#include "Control/LocalDatabase/cPersistenceManager.h"
// cPersistenceChannel
#include "Control/LocalDatabase/cPersistenceChannel.h"
//## begin module%4039DEBE033C.additionalDeclarations preserve=yes
//## end module%4039DEBE033C.additionalDeclarations


// Class cPersistenceChannel 




cPersistenceChannel::cPersistenceChannel()
  //## begin cPersistenceChannel::cPersistenceChannel%.hasinit preserve=no
      : _PersistenceManager(NULL)
  //## end cPersistenceChannel::cPersistenceChannel%.hasinit
  //## begin cPersistenceChannel::cPersistenceChannel%.initialization preserve=yes
  //## end cPersistenceChannel::cPersistenceChannel%.initialization
{
  //## begin cPersistenceChannel::cPersistenceChannel%.body preserve=yes
_ASSERT_UNCOND
  //## end cPersistenceChannel::cPersistenceChannel%.body
}

cPersistenceChannel::cPersistenceChannel(const cPersistenceChannel &right)
  //## begin cPersistenceChannel::cPersistenceChannel%copy.hasinit preserve=no
      : _PersistenceManager(NULL)
  //## end cPersistenceChannel::cPersistenceChannel%copy.hasinit
  //## begin cPersistenceChannel::cPersistenceChannel%copy.initialization preserve=yes
  //## end cPersistenceChannel::cPersistenceChannel%copy.initialization
{
  //## begin cPersistenceChannel::cPersistenceChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPersistenceChannel::cPersistenceChannel%copy.body
}

cPersistenceChannel::cPersistenceChannel (cContext *context)
  //## begin cPersistenceChannel::cPersistenceChannel%1077539617.hasinit preserve=no
      : _PersistenceManager(NULL)
  //## end cPersistenceChannel::cPersistenceChannel%1077539617.hasinit
  //## begin cPersistenceChannel::cPersistenceChannel%1077539617.initialization preserve=yes
  , cLocalChannel("PersistenceChannel")
  //## end cPersistenceChannel::cPersistenceChannel%1077539617.initialization
{
  //## begin cPersistenceChannel::cPersistenceChannel%1077539617.body preserve=yes
   STRING_T name = context->get_Name();
   name += ".";
   name += "PersistenceChannel";
   _Name = name;
   _PersistenceManager = new cPersistenceManager(context);
   Connect(_PersistenceManager);
  //## end cPersistenceChannel::cPersistenceChannel%1077539617.body
}


cPersistenceChannel::~cPersistenceChannel()
{
  //## begin cPersistenceChannel::~cPersistenceChannel%.body preserve=yes
   DELETE_OBJECT(cPersistenceManager, _PersistenceManager)
  //## end cPersistenceChannel::~cPersistenceChannel%.body
}



//## Other Operations (implementation)
BOOL_T cPersistenceChannel::DataInitialized ()
{
  //## begin cPersistenceChannel::DataInitialized%1085497636.body preserve=yes
   if (_PersistenceManager == 0) {
      return true;
   } else {
      return _PersistenceManager->get_DataInitialized();
   }
  //## end cPersistenceChannel::DataInitialized%1085497636.body
}

void cPersistenceChannel::Clear ()
{
   if (_PersistenceManager == NULL) {
      return;
   } else {
      _PersistenceManager->Clear();
   }
}

// Additional Declarations
  //## begin cPersistenceChannel%4039DEBE033C.declarations preserve=yes
  //## end cPersistenceChannel%4039DEBE033C.declarations

//## begin module%4039DEBE033C.epilog preserve=yes
//## end module%4039DEBE033C.epilog
