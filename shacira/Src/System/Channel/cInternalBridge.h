//## begin module%42DE0A72037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42DE0A72037A.cm

//## begin module%42DE0A72037A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%42DE0A72037A.cp

//## Module: cInternalBridge%42DE0A72037A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cInternalBridge.h

#ifndef cInternalBridge_h
#define cInternalBridge_h 1

//## begin module%42DE0A72037A.includes preserve=yes
//## end module%42DE0A72037A.includes

// cLocalChannel
#include "System/Channel/cLocalChannel.h"

class cMsgBox;
class __DLL_EXPORT__ cCellProxy;
class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cClients;

//## begin module%42DE0A72037A.additionalDeclarations preserve=yes
//## end module%42DE0A72037A.additionalDeclarations


//## begin cInternalBridge%42DE0A72037A.preface preserve=yes
//## end cInternalBridge%42DE0A72037A.preface

//## Class: cInternalBridge%42DE0A72037A
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42DE3F6203A9;cClients { -> F}
//## Uses: <unnamed>%42DE436E004E;cMsgBox { -> F}
//## Uses: <unnamed>%42F48232034B;cDataChange { -> F}

class __DLL_EXPORT__ cInternalBridge : public cLocalChannel  //## Inherits: <unnamed>%42DE3BF900BB
{
  //## begin cInternalBridge%42DE0A72037A.initialDeclarations preserve=yes
public:
  //## end cInternalBridge%42DE0A72037A.initialDeclarations

    //## Constructors (generated)
      cInternalBridge();

      cInternalBridge(const cInternalBridge &right);

    //## Constructors (specified)
      //## Operation: cInternalBridge%1121860894
      cInternalBridge (CONST_STRING_T name);

      //## Operation: cInternalBridge%1121845390
      cInternalBridge (cCellProxy *cell_proxy, ULONG_T client_id, CONST_STRING_T name);

    //## Destructor (generated)
      virtual ~cInternalBridge();


    //## Other Operations (specified)
      //## Operation: MainFunc%1121845391
      virtual INT_T MainFunc (void *extra);

      //## Operation: Deliver%1121845392
      //	Method to deliver an object to be sent over the internal
      //	bridge
      virtual void Deliver (cTransientObject *object);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ClientId%42DE0E5202AF
      ULONG_T get_ClientId () const;

      //## Attribute: UserName%42DF919F01F4
      STRING_T get_UserName () const;
      void set_UserName (STRING_T value);

      //## Attribute: Password%42DF919F0203
      STRING_T get_Password () const;
      void set_Password (STRING_T value);

      //## Attribute: IsService%42DE3C73004E
      BOOL_T get_IsService () const;

  public:
    // Additional Public Declarations
      //## begin cInternalBridge%42DE0A72037A.public preserve=yes
      //## end cInternalBridge%42DE0A72037A.public

  protected:
    // Data Members for Class Attributes

      //## begin cInternalBridge::ClientId%42DE0E5202AF.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ClientId;
      //## end cInternalBridge::ClientId%42DE0E5202AF.attr

      //## begin cInternalBridge::UserName%42DF919F01F4.attr preserve=no  public: STRING_T {U} 
      STRING_T _UserName;
      //## end cInternalBridge::UserName%42DF919F01F4.attr

      //## begin cInternalBridge::Password%42DF919F0203.attr preserve=no  public: STRING_T {U} 
      STRING_T _Password;
      //## end cInternalBridge::Password%42DF919F0203.attr

      //## begin cInternalBridge::IsService%42DE3C73004E.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsService;
      //## end cInternalBridge::IsService%42DE3C73004E.attr

    // Data Members for Associations

      //## Association: System::Channel::<unnamed>%42DE0BA802BF
      //## Role: cInternalBridge::CellProxy%42DE0BA90128
      //## begin cInternalBridge::CellProxy%42DE0BA90128.role preserve=no  public: cCellProxy { -> 0..1RFHN}
      cCellProxy *_CellProxy;
      //## end cInternalBridge::CellProxy%42DE0BA90128.role

    // Additional Protected Declarations
      //## begin cInternalBridge%42DE0A72037A.protected preserve=yes
      //## end cInternalBridge%42DE0A72037A.protected

  private:
    // Additional Private Declarations
      //## begin cInternalBridge%42DE0A72037A.private preserve=yes
      //## end cInternalBridge%42DE0A72037A.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ErrCount%42F481C60128
      //## begin cInternalBridge::ErrCount%42F481C60128.attr preserve=no  implementation: ULONG_T {U} 
      ULONG_T _ErrCount;
      //## end cInternalBridge::ErrCount%42F481C60128.attr

    // Additional Implementation Declarations
      //## begin cInternalBridge%42DE0A72037A.implementation preserve=yes
      //## end cInternalBridge%42DE0A72037A.implementation
private:
   BOOL_T _Synchronized;
private:
   void Synchronize();
};

//## begin cInternalBridge%42DE0A72037A.postscript preserve=yes
//## end cInternalBridge%42DE0A72037A.postscript

// Class cInternalBridge 

//## begin module%42DE0A72037A.epilog preserve=yes
//## end module%42DE0A72037A.epilog


#endif
