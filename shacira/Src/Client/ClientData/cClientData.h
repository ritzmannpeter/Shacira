//## begin module%42DD145A007D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42DD145A007D.cm

//## begin module%42DD145A007D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%42DD145A007D.cp

//## Module: cClientData%42DD145A007D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\ClientData\cClientData.h

#ifndef cClientData_h
#define cClientData_h 1

//## begin module%42DD145A007D.includes preserve=yes
//## end module%42DD145A007D.includes

// cTimeObject
#include "System/cTimeObject.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cUserInfo;
class __DLL_EXPORT__ cObjectQueue;

//## begin module%42DD145A007D.additionalDeclarations preserve=yes
//## end module%42DD145A007D.additionalDeclarations


//## begin cClientData%42DD145A007D.preface preserve=yes
//## end cClientData%42DD145A007D.preface

//## Class: cClientData%42DD145A007D
//## Category: Client::ClientData%42DD144803B9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42DE03DB0290;cTransientObject { -> F}
//## Uses: <unnamed>%42DE7999032C;cTimeObject { -> }

class __DLL_EXPORT__ cClientData 
{
  //## begin cClientData%42DD145A007D.initialDeclarations preserve=yes
public:
  //## end cClientData%42DD145A007D.initialDeclarations

    //## Constructors (generated)
      cClientData();

      cClientData(const cClientData &right);

    //## Destructor (generated)
      virtual ~cClientData();


    //## Other Operations (specified)
      //## Operation: AddObject%1121845389
      void AddObject (cTransientObject *object);

      //## Operation: GetEvent%1121785245
      STRING_T GetEvent ();

      //## Operation: GetDataEvent%1121785246
      STRING_T GetDataEvent ();

      //## Operation: TimedOut%1121876516
      BOOL_T TimedOut ();

      //## Operation: Resync%1121876517
      void Resync ();

      //## Operation: SetUserInfo%1141202707
      void SetUserInfo (cUserInfo *user_info);

      //## Operation: UserInfo%1141202706
      cUserInfo * UserInfo ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Id%42DD15120203
      ULONG_T get_Id () const;
      void set_Id (ULONG_T value);

      //## Attribute: IFType%44056A0D00C9
      ULONG_T get_IFType () const;
      void set_IFType (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cClientData%42DD145A007D.public preserve=yes
      //## end cClientData%42DD145A007D.public

  protected:
    // Data Members for Class Attributes

      //## begin cClientData::Id%42DD15120203.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Id;
      //## end cClientData::Id%42DD15120203.attr

      //## begin cClientData::IFType%44056A0D00C9.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _IFType;
      //## end cClientData::IFType%44056A0D00C9.attr

    // Data Members for Associations

      //## Association: Client::ClientData::<unnamed>%42DE026A009C
      //## Role: cClientData::Objects%42DE026B001F
      //## begin cClientData::Objects%42DE026B001F.role preserve=no  public: cObjectQueue { -> 1RFHN}
      cObjectQueue *_Objects;
      //## end cClientData::Objects%42DE026B001F.role

      //## Association: Client::ClientData::<unnamed>%440569A800C6
      //## Role: cClientData::UserInfo%440569A90097
      //## begin cClientData::UserInfo%440569A90097.role preserve=no  public: cUserInfo { -> 1RFHN}
      cUserInfo *_UserInfo;
      //## end cClientData::UserInfo%440569A90097.role

    // Additional Protected Declarations
      //## begin cClientData%42DD145A007D.protected preserve=yes
      //## end cClientData%42DD145A007D.protected

  private:
    // Additional Private Declarations
      //## begin cClientData%42DD145A007D.private preserve=yes
      //## end cClientData%42DD145A007D.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: LoginTime%42DF59040109
      //## begin cClientData::LoginTime%42DF59040109.attr preserve=no  private: cTimeObject {U} 
      cTimeObject _LoginTime;
      //## end cClientData::LoginTime%42DF59040109.attr

      //## Attribute: LastAccess%42DE79D90232
      //## begin cClientData::LastAccess%42DE79D90232.attr preserve=no  private: cTimeObject {U} 
      cTimeObject _LastAccess;
      //## end cClientData::LastAccess%42DE79D90232.attr

    // Additional Implementation Declarations
      //## begin cClientData%42DD145A007D.implementation preserve=yes
      //## end cClientData%42DD145A007D.implementation

};

//## begin cClientData%42DD145A007D.postscript preserve=yes
//## end cClientData%42DD145A007D.postscript

// Class cClientData 

//## begin module%42DD145A007D.epilog preserve=yes
//## end module%42DD145A007D.epilog


#endif
