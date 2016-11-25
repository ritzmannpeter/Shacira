//## begin module%42DD145A007D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42DD145A007D.cm

//## begin module%42DD145A007D.cp preserve=no
//	Copyright © 2002 - 2016 by
//	2i Industrial Informatics GmbH
//## end module%42DD145A007D.cp

//## Module: cClientData%42DD145A007D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\ClientData\cClientData.cpp

//## begin module%42DD145A007D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%42DD145A007D.additionalIncludes

//## begin module%42DD145A007D.includes preserve=yes

/// PR 20.11.12 - disabled recording of events for opc and euromap 63 interfaces

//## end module%42DD145A007D.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cUserInfo
#include "System/Objects/cUserInfo.h"
// cObjectQueue
#include "System/Objects/cObjectQueue.h"
// cClientData
#include "Client/ClientData/cClientData.h"
//## begin module%42DD145A007D.additionalDeclarations preserve=yes

#define ACCESS_TIMEOUT     60

//## end module%42DD145A007D.additionalDeclarations


// Class cClientData 







cClientData::cClientData()
  //## begin cClientData::cClientData%.hasinit preserve=no
      : _Id(0), _IFType(0), _Objects(NULL), _UserInfo(NULL)
  //## end cClientData::cClientData%.hasinit
  //## begin cClientData::cClientData%.initialization preserve=yes
  //## end cClientData::cClientData%.initialization
{
  //## begin cClientData::cClientData%.body preserve=yes
   _Objects = new cObjectQueue(0x4000, QOverwrite);
   _LoginTime.Now();
   _Id = (ULONG_T)-1;
   // avoid identical client ids for different clients
   cSystemUtils::Suspend(2000);
   _LastAccess.Now();
  //## end cClientData::cClientData%.body
}

cClientData::cClientData(const cClientData &right)
  //## begin cClientData::cClientData%copy.hasinit preserve=no
      : _Id(0), _IFType(0), _Objects(NULL), _UserInfo(NULL)
  //## end cClientData::cClientData%copy.hasinit
  //## begin cClientData::cClientData%copy.initialization preserve=yes
  //## end cClientData::cClientData%copy.initialization
{
  //## begin cClientData::cClientData%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cClientData::cClientData%copy.body
}


cClientData::~cClientData()
{
  //## begin cClientData::~cClientData%.body preserve=yes
   cTransientObject * object = _Objects->GetNext();
   while (object != NULL) {
      object->Release();
      object = _Objects->GetNext();
   }
   DELETE_OBJECT(cObjectQueue,_Objects)
  //## end cClientData::~cClientData%.body
}



//## Other Operations (implementation)
void cClientData::AddObject (cTransientObject *object)
{
  //## begin cClientData::AddObject%1121845389.body preserve=yes
   if (_IFType == IF_OPC || _IFType == IF_EM63) {
      // ignore event recording
   } else {
      _Objects->Add(object);
   }
  //## end cClientData::AddObject%1121845389.body
}

STRING_T cClientData::GetEvent ()
{
  //## begin cClientData::GetEvent%1121785245.body preserve=yes
   cTransientObject * object = _Objects->GetNext();   
   if (object != NULL) {
      STRING_T ser_obj = object->Serialize();
      object->Release();
      return ser_obj;
   } else {
      // avoid server stress by waiting 50 mseconds when no object is available
      cSystemUtils::Suspend(50);
      return "";
   }
  //## end cClientData::GetEvent%1121785245.body
}

STRING_T cClientData::GetDataEvent ()
{
  //## begin cClientData::GetDataEvent%1121785246.body preserve=yes
   return "?";
  //## end cClientData::GetDataEvent%1121785246.body
}

BOOL_T cClientData::TimedOut ()
{
  //## begin cClientData::TimedOut%1121876516.body preserve=yes
   ULONG_T elapsed = _LastAccess.Elapsed();
   if (elapsed > ACCESS_TIMEOUT) {
      return true;
   } else {
      return false;
   }
  //## end cClientData::TimedOut%1121876516.body
}

void cClientData::Resync ()
{
  //## begin cClientData::Resync%1121876517.body preserve=yes
   _LastAccess.Now();
  //## end cClientData::Resync%1121876517.body
}

void cClientData::SetUserInfo (cUserInfo *user_info)
{
  //## begin cClientData::SetUserInfo%1141202707.body preserve=yes
   _UserInfo = user_info;
  //## end cClientData::SetUserInfo%1141202707.body
}

cUserInfo * cClientData::UserInfo ()
{
  //## begin cClientData::UserInfo%1141202706.body preserve=yes
   return _UserInfo;
  //## end cClientData::UserInfo%1141202706.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cClientData::get_Id () const
{
  //## begin cClientData::get_Id%42DD15120203.get preserve=no
  return _Id;
  //## end cClientData::get_Id%42DD15120203.get
}

void cClientData::set_Id (ULONG_T value)
{
  //## begin cClientData::set_Id%42DD15120203.set preserve=no
  _Id = value;
  //## end cClientData::set_Id%42DD15120203.set
}

ULONG_T cClientData::get_IFType () const
{
  //## begin cClientData::get_IFType%44056A0D00C9.get preserve=no
  return _IFType;
  //## end cClientData::get_IFType%44056A0D00C9.get
}

void cClientData::set_IFType (ULONG_T value)
{
  //## begin cClientData::set_IFType%44056A0D00C9.set preserve=no
  _IFType = value;
  //## end cClientData::set_IFType%44056A0D00C9.set
}

// Additional Declarations
  //## begin cClientData%42DD145A007D.declarations preserve=yes
  //## end cClientData%42DD145A007D.declarations

//## begin module%42DD145A007D.epilog preserve=yes
//## end module%42DD145A007D.epilog
