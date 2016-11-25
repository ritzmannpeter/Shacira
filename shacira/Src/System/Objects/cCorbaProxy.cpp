//## begin module%3EDB31F402EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EDB31F402EE.cm

//## begin module%3EDB31F402EE.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3EDB31F402EE.cp

//## Module: cCorbaProxy%3EDB31F402EE; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\System\Objects\cCorbaProxy.cpp

//## begin module%3EDB31F402EE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3EDB31F402EE.additionalIncludes

//## begin module%3EDB31F402EE.includes preserve=yes
//## end module%3EDB31F402EE.includes

// cCorbaProxy
#include "System/Objects/cCorbaProxy.h"
//## begin module%3EDB31F402EE.additionalDeclarations preserve=yes
//## end module%3EDB31F402EE.additionalDeclarations


// Class cCorbaProxy 


cCorbaProxy::cCorbaProxy()
  //## begin cCorbaProxy::cCorbaProxy%.hasinit preserve=no
  //## end cCorbaProxy::cCorbaProxy%.hasinit
  //## begin cCorbaProxy::cCorbaProxy%.initialization preserve=yes
  //## end cCorbaProxy::cCorbaProxy%.initialization
{
  //## begin cCorbaProxy::cCorbaProxy%.body preserve=yes
  //## end cCorbaProxy::cCorbaProxy%.body
}

cCorbaProxy::cCorbaProxy(const cCorbaProxy &right)
  //## begin cCorbaProxy::cCorbaProxy%copy.hasinit preserve=no
  //## end cCorbaProxy::cCorbaProxy%copy.hasinit
  //## begin cCorbaProxy::cCorbaProxy%copy.initialization preserve=yes
  //## end cCorbaProxy::cCorbaProxy%copy.initialization
{
  //## begin cCorbaProxy::cCorbaProxy%copy.body preserve=yes
  //## end cCorbaProxy::cCorbaProxy%copy.body
}


cCorbaProxy::~cCorbaProxy()
{
  //## begin cCorbaProxy::~cCorbaProxy%.body preserve=yes
  //## end cCorbaProxy::~cCorbaProxy%.body
}



//## Other Operations (implementation)
STRING_T cCorbaProxy::Serialize ()
{
  //## begin cCorbaProxy::Serialize%1054547840.body preserve=yes
   return false;
  //## end cCorbaProxy::Serialize%1054547840.body
}

BOOL_T cCorbaProxy::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cCorbaProxy::Construct%1054547841.body preserve=yes
   return false;
  //## end cCorbaProxy::Construct%1054547841.body
}

void cCorbaProxy::SetItf ()
{
  //## begin cCorbaProxy::SetItf%1054547842.body preserve=yes
  //## end cCorbaProxy::SetItf%1054547842.body
}

void cCorbaProxy::ReleaseItf ()
{
  //## begin cCorbaProxy::ReleaseItf%1054547843.body preserve=yes
  //## end cCorbaProxy::ReleaseItf%1054547843.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cCorbaProxy::get_IOR () const
{
  //## begin cCorbaProxy::get_IOR%3EDB325600BB.get preserve=no
  return _IOR;
  //## end cCorbaProxy::get_IOR%3EDB325600BB.get
}

void cCorbaProxy::set_IOR (STRING_T value)
{
  //## begin cCorbaProxy::set_IOR%3EDB325600BB.set preserve=no
  _IOR = value;
  //## end cCorbaProxy::set_IOR%3EDB325600BB.set
}

// Additional Declarations
  //## begin cCorbaProxy%3EDB31F402EE.declarations preserve=yes
  //## end cCorbaProxy%3EDB31F402EE.declarations

//## begin module%3EDB31F402EE.epilog preserve=yes
//## end module%3EDB31F402EE.epilog
