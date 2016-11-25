//## begin module%3DCAA0A700C9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DCAA0A700C9.cm

//## begin module%3DCAA0A700C9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DCAA0A700C9.cp

//## Module: cCosEventChannelProxy%3DCAA0A700C9; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Orb\cCosEventChannelProxy.h

#ifndef cCosEventChannelProxy_h
#define cCosEventChannelProxy_h 1

//## begin module%3DCAA0A700C9.includes preserve=yes

#include "CorbaDefinitions.h"
#include "CosEventChannelAdmin.hh"
#include "CosEventComm.hh"

//## end module%3DCAA0A700C9.includes

// cChannelProxy
#include "System/Channel/cChannelProxy.h"

class __DLL_EXPORT__ cBroker;

//## begin module%3DCAA0A700C9.additionalDeclarations preserve=yes

class PushSupplierImpl;
class PushConsumerImpl;

//## end module%3DCAA0A700C9.additionalDeclarations


//## begin cCosEventChannelProxy%3DCAA0A700C9.preface preserve=yes
//## end cCosEventChannelProxy%3DCAA0A700C9.preface

//## Class: cCosEventChannelProxy%3DCAA0A700C9
//## Category: Orb%3AC0838100CF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DCAA0A700CB;cBroker { -> F}

class __DLL_EXPORT__ cCosEventChannelProxy : public cChannelProxy  //## Inherits: <unnamed>%3DCAA1810217
{
  //## begin cCosEventChannelProxy%3DCAA0A700C9.initialDeclarations preserve=yes
   typedef std::list<PUSH_CALLBACK_T*> CALLBACK_LIST_T;
   private:
      CALLBACK_LIST_T _Callbacks;
      CosEventChannelAdmin::EventChannel_var * _Channel;
      // Supplier
      PushSupplierImpl * _Supplier;
      CosEventChannelAdmin::SupplierAdmin_var _ForSupplier;
      CosEventChannelAdmin::ProxyPushConsumer_var _ProxyPushConsumer;
      // Consumer
      PushConsumerImpl * _Consumer;
      CosEventChannelAdmin::ConsumerAdmin_var _ForConsumer;
      CosEventChannelAdmin::ProxyPushSupplier_var _ProxyPushSupplier;
public:
  //## end cCosEventChannelProxy%3DCAA0A700C9.initialDeclarations

    //## Constructors (generated)
      cCosEventChannelProxy();

      cCosEventChannelProxy(const cCosEventChannelProxy &right);

    //## Destructor (generated)
      virtual ~cCosEventChannelProxy();


    //## Other Operations (specified)
      //## Operation: Update%1054547851
      virtual void Update (cProxy *proxy);

      //## Operation: Send%1054547844
      virtual BOOL_T Send (cTransientObject *object);

      //## Operation: Listen%1054632833
      virtual BOOL_T Listen ();

      //## Operation: PushEvent%1054632841
      void PushEvent (const CORBA::Any  &any);

  public:
    // Additional Public Declarations
      //## begin cCosEventChannelProxy%3DCAA0A700C9.public preserve=yes
      //## end cCosEventChannelProxy%3DCAA0A700C9.public

  protected:
    // Additional Protected Declarations
      //## begin cCosEventChannelProxy%3DCAA0A700C9.protected preserve=yes
      //## end cCosEventChannelProxy%3DCAA0A700C9.protected

  private:
    // Additional Private Declarations
      //## begin cCosEventChannelProxy%3DCAA0A700C9.private preserve=yes
      //## end cCosEventChannelProxy%3DCAA0A700C9.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Use%1054632843
      virtual BOOL_T Use ();

      //## Operation: SetItf%1054632837
      void SetItf ();

      //## Operation: ReleaseItf%1054632838
      void ReleaseItf ();

    // Additional Implementation Declarations
      //## begin cCosEventChannelProxy%3DCAA0A700C9.implementation preserve=yes
      //## end cCosEventChannelProxy%3DCAA0A700C9.implementation

};

//## begin cCosEventChannelProxy%3DCAA0A700C9.postscript preserve=yes
//## end cCosEventChannelProxy%3DCAA0A700C9.postscript

// Class cCosEventChannelProxy 

//## begin module%3DCAA0A700C9.epilog preserve=yes
//## end module%3DCAA0A700C9.epilog


#endif
