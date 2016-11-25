//## begin module%419856D6000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%419856D6000F.cm

//## begin module%419856D6000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%419856D6000F.cp

//## Module: cUserInfo%419856D6000F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cUserInfo.h

#ifndef cUserInfo_h
#define cUserInfo_h 1

//## begin module%419856D6000F.includes preserve=yes
//## end module%419856D6000F.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

//## begin module%419856D6000F.additionalDeclarations preserve=yes
//## end module%419856D6000F.additionalDeclarations


//## begin cUserInfo%419856D6000F.preface preserve=yes
//## end cUserInfo%419856D6000F.preface

//## Class: cUserInfo%419856D6000F
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%41985B500399;cTransferObject { -> F}

class __DLL_EXPORT__ cUserInfo : public cTransientObject  //## Inherits: <unnamed>%419856EB02EE
{
  //## begin cUserInfo%419856D6000F.initialDeclarations preserve=yes
public:
  //## end cUserInfo%419856D6000F.initialDeclarations

    //## Constructors (generated)
      cUserInfo();

      cUserInfo(const cUserInfo &right);

    //## Constructors (specified)
      //## Operation: cUserInfo%1100502934
      cUserInfo (cStaticObject *source, ULONG_T user_id, CONST_STRING_T user_name);

    //## Destructor (generated)
      virtual ~cUserInfo();


    //## Other Operations (specified)
      //## Operation: Serialize%1100502935
      virtual STRING_T Serialize ();

      //## Operation: Construct%1100502936
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: UserId%4198572202BF
      ULONG_T get_UserId () const;
      void set_UserId (ULONG_T value);

      //## Attribute: UserName%4198574B0290
      STRING_T get_UserName () const;
      void set_UserName (STRING_T value);

      //## Attribute: GroupId%41985F59033C
      ULONG_T get_GroupId () const;
      void set_GroupId (ULONG_T value);

      //## Attribute: DataSet%41985F6F01D4
      ULONG_T get_DataSet () const;
      void set_DataSet (ULONG_T value);

      //## Attribute: LogoffInterval%41AEDD3302DE
      ULONG_T get_LogoffInterval () const;
      void set_LogoffInterval (ULONG_T value);

      //## Attribute: ClientId%4417DB44030A
      ULONG_T get_ClientId () const;
      void set_ClientId (ULONG_T value);

      //## Attribute: IFType%4417DB5B002A
      ULONG_T get_IFType () const;
      void set_IFType (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cUserInfo%419856D6000F.public preserve=yes
      //## end cUserInfo%419856D6000F.public

  protected:
    // Data Members for Class Attributes

      //## begin cUserInfo::UserId%4198572202BF.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _UserId;
      //## end cUserInfo::UserId%4198572202BF.attr

      //## begin cUserInfo::UserName%4198574B0290.attr preserve=no  public: STRING_T {U} 
      STRING_T _UserName;
      //## end cUserInfo::UserName%4198574B0290.attr

      //## begin cUserInfo::GroupId%41985F59033C.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _GroupId;
      //## end cUserInfo::GroupId%41985F59033C.attr

      //## begin cUserInfo::DataSet%41985F6F01D4.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _DataSet;
      //## end cUserInfo::DataSet%41985F6F01D4.attr

      //## begin cUserInfo::LogoffInterval%41AEDD3302DE.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _LogoffInterval;
      //## end cUserInfo::LogoffInterval%41AEDD3302DE.attr

      //## begin cUserInfo::ClientId%4417DB44030A.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ClientId;
      //## end cUserInfo::ClientId%4417DB44030A.attr

      //## begin cUserInfo::IFType%4417DB5B002A.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _IFType;
      //## end cUserInfo::IFType%4417DB5B002A.attr

    // Additional Protected Declarations
      //## begin cUserInfo%419856D6000F.protected preserve=yes
      //## end cUserInfo%419856D6000F.protected

  private:
    // Additional Private Declarations
      //## begin cUserInfo%419856D6000F.private preserve=yes
      //## end cUserInfo%419856D6000F.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cUserInfo%419856D6000F.implementation preserve=yes
      //## end cUserInfo%419856D6000F.implementation

};

//## begin cUserInfo%419856D6000F.postscript preserve=yes
//## end cUserInfo%419856D6000F.postscript

// Class cUserInfo 

//## begin module%419856D6000F.epilog preserve=yes
//## end module%419856D6000F.epilog


#endif
