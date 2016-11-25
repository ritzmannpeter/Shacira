//## begin module%3C4EE65F00FE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EE65F00FE.cm

//## begin module%3C4EE65F00FE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EE65F00FE.cp

//## Module: cProxy%3C4EE65F00FE; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cProxy.cpp

//## begin module%3C4EE65F00FE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C4EE65F00FE.additionalIncludes

//## begin module%3C4EE65F00FE.includes preserve=yes
//## end module%3C4EE65F00FE.includes

// eb_sema
#include "base/eb_sema.hpp"
// cProxy
#include "System/Objects/cProxy.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
//## begin module%3C4EE65F00FE.additionalDeclarations preserve=yes
//## end module%3C4EE65F00FE.additionalDeclarations


// Class cProxy 













cProxy::cProxy()
  //## begin cProxy::cProxy%.hasinit preserve=no
      : _Object(NULL), _Port(0), _ProcessId(0), _Connected(true), _Synchronized(false)
  //## end cProxy::cProxy%.hasinit
  //## begin cProxy::cProxy%.initialization preserve=yes
  //## end cProxy::cProxy%.initialization
{
  //## begin cProxy::cProxy%.body preserve=yes
  //## end cProxy::cProxy%.body
}

cProxy::cProxy(const cProxy &right)
  //## begin cProxy::cProxy%copy.hasinit preserve=no
      : _Object(NULL), _Port(0), _ProcessId(0), _Connected(true), _Synchronized(false)
  //## end cProxy::cProxy%copy.hasinit
  //## begin cProxy::cProxy%copy.initialization preserve=yes
  //## end cProxy::cProxy%copy.initialization
{
  //## begin cProxy::cProxy%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProxy::cProxy%copy.body
}


cProxy::~cProxy()
{
  //## begin cProxy::~cProxy%.body preserve=yes
  //## end cProxy::~cProxy%.body
}



//## Other Operations (implementation)
STRING_T cProxy::Serialize ()
{
  //## begin cProxy::Serialize%1023781002.body preserve=yes
#ifdef as_it_should
   cTransferObject obj;
   SerializeBase(obj);
   // proxy attributes
   obj.AddAttribute(0, _ProxyName.c_str(), ObjectBody);
   obj.AddAttribute(1, _Computer.c_str(), ObjectBody);
   obj.AddAttribute(2, _Host.c_str(), ObjectBody);
   obj.AddAttribute(3, _IPAddress.c_str(), ObjectBody);
   obj.AddAttribute(4, _Port, ObjectBody);
   obj.AddAttribute(5, _ProcessId, ObjectBody);
   obj.AddAttribute(6, _ProcessName.c_str(), ObjectBody);
   return obj.Serialize().c_str();
#else
   cTransferObject obj;
   SerializeBase(obj);
   // proxy attributes
   obj.AddAttribute(0, _IOR.c_str(), ObjectBody);
   obj.AddAttribute(1, _ProxyName.c_str(), ObjectBody);
   obj.AddAttribute(2, _Computer.c_str(), ObjectBody);
   obj.AddAttribute(3, _Host.c_str(), ObjectBody);
   obj.AddAttribute(4, _IPAddress.c_str(), ObjectBody);
   obj.AddAttribute(5, _Port, ObjectBody);
   obj.AddAttribute(6, _ProcessId, ObjectBody);
   obj.AddAttribute(7, _Object, ObjectBody);
   obj.AddAttribute(8, _ProcessName.c_str(), ObjectBody);
   return obj.Serialize().c_str();
#endif
  //## end cProxy::Serialize%1023781002.body
}

BOOL_T cProxy::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cProxy::Construct%1023781003.body preserve=yes
#ifdef as_it_should
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   // proxy attributes
   obj.GetAttribute(0, _ProxyName, ObjectBody);
   obj.GetAttribute(1, _Computer, ObjectBody);
   obj.GetAttribute(2, _Host, ObjectBody);
   obj.GetAttribute(3, _IPAddress, ObjectBody);
   obj.GetAttribute(4, _Port, ObjectBody);
   obj.GetAttribute(5, _ProcessId, ObjectBody);
   obj.GetAttribute(6, _ProcessName, ObjectBody);
   return true;
#else
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   // proxy attributes
   obj.GetAttribute(0, _IOR, ObjectBody);
   obj.GetAttribute(1, _ProxyName, ObjectBody);
   obj.GetAttribute(2, _Computer, ObjectBody);
   obj.GetAttribute(3, _Host, ObjectBody);
   obj.GetAttribute(4, _IPAddress, ObjectBody);
   obj.GetAttribute(5, _Port, ObjectBody);
   obj.GetAttribute(6, _ProcessId, ObjectBody);
   obj.GetAttribute(7, _Object, ObjectBody);
   obj.GetAttribute(8, _ProcessName, ObjectBody);
   return true;
#endif
  //## end cProxy::Construct%1023781003.body
}

//## Get and Set Operations for Class Attributes (implementation)

void * cProxy::get_Object () const
{
  //## begin cProxy::get_Object%3EDF69DE007D.get preserve=no
  return _Object;
  //## end cProxy::get_Object%3EDF69DE007D.get
}

void cProxy::set_Object (void * value)
{
  //## begin cProxy::set_Object%3EDF69DE007D.set preserve=no
  _Object = value;
  //## end cProxy::set_Object%3EDF69DE007D.set
}

STRING_T cProxy::get_IOR () const
{
  //## begin cProxy::get_IOR%3EDF68AE0251.get preserve=no
  return _IOR;
  //## end cProxy::get_IOR%3EDF68AE0251.get
}

void cProxy::set_IOR (STRING_T value)
{
  //## begin cProxy::set_IOR%3EDF68AE0251.set preserve=no
  _IOR = value;
  //## end cProxy::set_IOR%3EDF68AE0251.set
}

STRING_T cProxy::get_ProxyName () const
{
  //## begin cProxy::get_ProxyName%3EA68F330000.get preserve=no
  return _ProxyName;
  //## end cProxy::get_ProxyName%3EA68F330000.get
}

void cProxy::set_ProxyName (STRING_T value)
{
  //## begin cProxy::set_ProxyName%3EA68F330000.set preserve=no
  _ProxyName = value;
  //## end cProxy::set_ProxyName%3EA68F330000.set
}

STRING_T cProxy::get_Computer () const
{
  //## begin cProxy::get_Computer%3C5523F20339.get preserve=no
  return _Computer;
  //## end cProxy::get_Computer%3C5523F20339.get
}

void cProxy::set_Computer (STRING_T value)
{
  //## begin cProxy::set_Computer%3C5523F20339.set preserve=no
  _Computer = value;
  //## end cProxy::set_Computer%3C5523F20339.set
}

STRING_T cProxy::get_Host () const
{
  //## begin cProxy::get_Host%4305E9B00119.get preserve=no
  return _Host;
  //## end cProxy::get_Host%4305E9B00119.get
}

void cProxy::set_Host (STRING_T value)
{
  //## begin cProxy::set_Host%4305E9B00119.set preserve=no
  _Host = value;
  //## end cProxy::set_Host%4305E9B00119.set
}

STRING_T cProxy::get_IPAddress () const
{
  //## begin cProxy::get_IPAddress%3C552401020E.get preserve=no
  return _IPAddress;
  //## end cProxy::get_IPAddress%3C552401020E.get
}

void cProxy::set_IPAddress (STRING_T value)
{
  //## begin cProxy::set_IPAddress%3C552401020E.set preserve=no
  _IPAddress = value;
  //## end cProxy::set_IPAddress%3C552401020E.set
}

ULONG_T cProxy::get_Port () const
{
  //## begin cProxy::get_Port%3EA68EA00203.get preserve=no
  return _Port;
  //## end cProxy::get_Port%3EA68EA00203.get
}

void cProxy::set_Port (ULONG_T value)
{
  //## begin cProxy::set_Port%3EA68EA00203.set preserve=no
  _Port = value;
  //## end cProxy::set_Port%3EA68EA00203.set
}

ULONG_T cProxy::get_ProcessId () const
{
  //## begin cProxy::get_ProcessId%3C55241E015C.get preserve=no
  return _ProcessId;
  //## end cProxy::get_ProcessId%3C55241E015C.get
}

void cProxy::set_ProcessId (ULONG_T value)
{
  //## begin cProxy::set_ProcessId%3C55241E015C.set preserve=no
  _ProcessId = value;
  //## end cProxy::set_ProcessId%3C55241E015C.set
}

STRING_T cProxy::get_ProcessName () const
{
  //## begin cProxy::get_ProcessName%3EA68EED02EE.get preserve=no
  return _ProcessName;
  //## end cProxy::get_ProcessName%3EA68EED02EE.get
}

void cProxy::set_ProcessName (STRING_T value)
{
  //## begin cProxy::set_ProcessName%3EA68EED02EE.set preserve=no
  _ProcessName = value;
  //## end cProxy::set_ProcessName%3EA68EED02EE.set
}

BOOL_T cProxy::get_Connected () const
{
  //## begin cProxy::get_Connected%4399B93B015F.get preserve=no
  return _Connected;
  //## end cProxy::get_Connected%4399B93B015F.get
}

void cProxy::set_Connected (BOOL_T value)
{
  //## begin cProxy::set_Connected%4399B93B015F.set preserve=no
  _Connected = value;
  //## end cProxy::set_Connected%4399B93B015F.set
}

BOOL_T cProxy::get_Synchronized () const
{
  //## begin cProxy::get_Synchronized%49381C0700C4.get preserve=no
  return _Synchronized;
  //## end cProxy::get_Synchronized%49381C0700C4.get
}

void cProxy::set_Synchronized (BOOL_T value)
{
  //## begin cProxy::set_Synchronized%49381C0700C4.set preserve=no
  _Synchronized = value;
  //## end cProxy::set_Synchronized%49381C0700C4.set
}

// Additional Declarations
  //## begin cProxy%3C4EE65F00FE.declarations preserve=yes
  //## end cProxy%3C4EE65F00FE.declarations

//## begin module%3C4EE65F00FE.epilog preserve=yes
//## end module%3C4EE65F00FE.epilog
