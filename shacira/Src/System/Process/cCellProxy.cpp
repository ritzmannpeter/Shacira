//## begin module%3DCAA12E00EB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DCAA12E00EB.cm

//## begin module%3DCAA12E00EB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DCAA12E00EB.cp

//## Module: cCellProxy%3DCAA12E00EB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cCellProxy.cpp

//## begin module%3DCAA12E00EB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DCAA12E00EB.additionalIncludes

//## begin module%3DCAA12E00EB.includes preserve=yes
//## end module%3DCAA12E00EB.includes

// cCellProxy
#include "System/Process/cCellProxy.h"
// cContext
#include "System/Database/cContext.h"
// cBroker
#include "Orb/cBroker.h"
//## begin module%3DCAA12E00EB.additionalDeclarations preserve=yes
//## end module%3DCAA12E00EB.additionalDeclarations


// Class cCellProxy 






cCellProxy::cCellProxy()
  //## begin cCellProxy::cCellProxy%.hasinit preserve=no
      : _ClientId(0), _IFType(IF_PROPRIETARY)
  //## end cCellProxy::cCellProxy%.hasinit
  //## begin cCellProxy::cCellProxy%.initialization preserve=yes
  //## end cCellProxy::cCellProxy%.initialization
{
  //## begin cCellProxy::cCellProxy%.body preserve=yes
  //## end cCellProxy::cCellProxy%.body
}

cCellProxy::cCellProxy(const cCellProxy &right)
  //## begin cCellProxy::cCellProxy%copy.hasinit preserve=no
      : _ClientId(0), _IFType(IF_PROPRIETARY)
  //## end cCellProxy::cCellProxy%copy.hasinit
  //## begin cCellProxy::cCellProxy%copy.initialization preserve=yes
  //## end cCellProxy::cCellProxy%copy.initialization
{
  //## begin cCellProxy::cCellProxy%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCellProxy::cCellProxy%copy.body
}


cCellProxy::~cCellProxy()
{
  //## begin cCellProxy::~cCellProxy%.body preserve=yes
  //## end cCellProxy::~cCellProxy%.body
}



//## Other Operations (implementation)
void cCellProxy::SetValue (CONST_STRING_T var_name, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCellProxy::SetValue%1036694754.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cCellProxy::SetValue/2", "cCellProxy");
  //## end cCellProxy::SetValue%1036694754.body
}

void cCellProxy::SetParam (CONST_STRING_T param_name, LONG_T value)
{
  //## begin cCellProxy::SetParam%1078912343.body preserve=yes
  //## end cCellProxy::SetParam%1078912343.body
}

void cCellProxy::SetValue (LONG_T var_id, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCellProxy::SetValue%1078912358.body preserve=yes
  //## end cCellProxy::SetValue%1078912358.body
}

ULONG_T cCellProxy::GetObject (cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCellProxy::GetObject%1238436650.body preserve=yes
   return 0;
  //## end cCellProxy::GetObject%1238436650.body
}

void cCellProxy::SetObject (const cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCellProxy::SetObject%1238436651.body preserve=yes
  //## end cCellProxy::SetObject%1238436651.body
}

BOOL_T cCellProxy::Ping ()
{
  //## begin cCellProxy::Ping%1134227773.body preserve=yes
   return true;
  //## end cCellProxy::Ping%1134227773.body
}

STRING_T cCellProxy::Request (CONST_STRING_T request)
{
  //## begin cCellProxy::Request%1242995031.body preserve=yes
   return "?";
  //## end cCellProxy::Request%1242995031.body
}

STRING_T cCellProxy::GetRing (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cCellProxy::GetRing%1242995035.body preserve=yes
   return "?";
  //## end cCellProxy::GetRing%1242995035.body
}

void cCellProxy::ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async)
{
  //## begin cCellProxy::ExecuteJob%1244547097.body preserve=yes
  //## end cCellProxy::ExecuteJob%1244547097.body
}

//## Get and Set Operations for Class Attributes (implementation)

LONG_T cCellProxy::get_ClientId () const
{
  //## begin cCellProxy::get_ClientId%438767AE030C.get preserve=no
  return _ClientId;
  //## end cCellProxy::get_ClientId%438767AE030C.get
}

void cCellProxy::set_ClientId (LONG_T value)
{
  //## begin cCellProxy::set_ClientId%438767AE030C.set preserve=no
  _ClientId = value;
  //## end cCellProxy::set_ClientId%438767AE030C.set
}

LONG_T cCellProxy::get_IFType () const
{
  //## begin cCellProxy::get_IFType%438AD80C01CE.get preserve=no
  return _IFType;
  //## end cCellProxy::get_IFType%438AD80C01CE.get
}

void cCellProxy::set_IFType (LONG_T value)
{
  //## begin cCellProxy::set_IFType%438AD80C01CE.set preserve=no
  _IFType = value;
  //## end cCellProxy::set_IFType%438AD80C01CE.set
}

// Additional Declarations
  //## begin cCellProxy%3DCAA12E00EB.declarations preserve=yes
  //## end cCellProxy%3DCAA12E00EB.declarations

//## begin module%3DCAA12E00EB.epilog preserve=yes
//## end module%3DCAA12E00EB.epilog
