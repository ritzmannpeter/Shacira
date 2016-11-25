//## begin module%3C4EE65F00FE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EE65F00FE.cm

//## begin module%3C4EE65F00FE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EE65F00FE.cp

//## Module: cProxy%3C4EE65F00FE; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cProxy.h

#ifndef cProxy_h
#define cProxy_h 1

//## begin module%3C4EE65F00FE.includes preserve=yes
//## end module%3C4EE65F00FE.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class cMutexSem;
class __DLL_EXPORT__ cTransferObject;

//## begin module%3C4EE65F00FE.additionalDeclarations preserve=yes
//## end module%3C4EE65F00FE.additionalDeclarations


//## begin cProxy%3C4EE65F00FE.preface preserve=yes
//## end cProxy%3C4EE65F00FE.preface

//## Class: cProxy%3C4EE65F00FE
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A57B7032D;cTransferObject { -> F}
//## Uses: <unnamed>%4167E9F102EE;cMutexSem { -> F}

class __DLL_EXPORT__ cProxy : public cTransientObject  //## Inherits: <unnamed>%3D23383D03E0
{
  //## begin cProxy%3C4EE65F00FE.initialDeclarations preserve=yes
public:
  //## end cProxy%3C4EE65F00FE.initialDeclarations

    //## Constructors (generated)
      cProxy();

      cProxy(const cProxy &right);

    //## Destructor (generated)
      virtual ~cProxy();


    //## Other Operations (specified)
      //## Operation: Update%1054547850
      virtual void Update (cProxy *proxy) = 0;

      //## Operation: Serialize%1023781002
      virtual STRING_T Serialize ();

      //## Operation: Construct%1023781003
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Object%3EDF69DE007D
      void * get_Object () const;
      void set_Object (void * value);

      //## Attribute: IOR%3EDF68AE0251
      STRING_T get_IOR () const;
      void set_IOR (STRING_T value);

      //## Attribute: ProxyName%3EA68F330000
      STRING_T get_ProxyName () const;
      void set_ProxyName (STRING_T value);

      //## Attribute: Computer%3C5523F20339
      STRING_T get_Computer () const;
      void set_Computer (STRING_T value);

      //## Attribute: Host%4305E9B00119
      STRING_T get_Host () const;
      void set_Host (STRING_T value);

      //## Attribute: IPAddress%3C552401020E
      STRING_T get_IPAddress () const;
      void set_IPAddress (STRING_T value);

      //## Attribute: Port%3EA68EA00203
      ULONG_T get_Port () const;
      void set_Port (ULONG_T value);

      //## Attribute: ProcessId%3C55241E015C
      ULONG_T get_ProcessId () const;
      void set_ProcessId (ULONG_T value);

      //## Attribute: ProcessName%3EA68EED02EE
      STRING_T get_ProcessName () const;
      void set_ProcessName (STRING_T value);

      //## Attribute: Connected%4399B93B015F
      BOOL_T get_Connected () const;
      void set_Connected (BOOL_T value);

      BOOL_T get_Synchronized () const;
      void set_Synchronized (BOOL_T value);

  public:
    // Additional Public Declarations
      //## begin cProxy%3C4EE65F00FE.public preserve=yes
      //## end cProxy%3C4EE65F00FE.public

  protected:
    // Data Members for Class Attributes

      //## begin cProxy::Object%3EDF69DE007D.attr preserve=no  public: void * {U} NULL
      void *_Object;
      //## end cProxy::Object%3EDF69DE007D.attr

      //## begin cProxy::IOR%3EDF68AE0251.attr preserve=no  public: STRING_T {U} 
      STRING_T _IOR;
      //## end cProxy::IOR%3EDF68AE0251.attr

      //## begin cProxy::ProxyName%3EA68F330000.attr preserve=no  public: STRING_T {U} 
      STRING_T _ProxyName;
      //## end cProxy::ProxyName%3EA68F330000.attr

      //## begin cProxy::Computer%3C5523F20339.attr preserve=no  public: STRING_T {U} 
      STRING_T _Computer;
      //## end cProxy::Computer%3C5523F20339.attr

      //## begin cProxy::Host%4305E9B00119.attr preserve=no  public: STRING_T {U} 
      STRING_T _Host;
      //## end cProxy::Host%4305E9B00119.attr

      //## begin cProxy::IPAddress%3C552401020E.attr preserve=no  public: STRING_T {U} 
      STRING_T _IPAddress;
      //## end cProxy::IPAddress%3C552401020E.attr

      //## begin cProxy::Port%3EA68EA00203.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Port;
      //## end cProxy::Port%3EA68EA00203.attr

      //## begin cProxy::ProcessId%3C55241E015C.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ProcessId;
      //## end cProxy::ProcessId%3C55241E015C.attr

      //## begin cProxy::ProcessName%3EA68EED02EE.attr preserve=no  public: STRING_T {U} 
      STRING_T _ProcessName;
      //## end cProxy::ProcessName%3EA68EED02EE.attr

      //## begin cProxy::Connected%4399B93B015F.attr preserve=no  public: BOOL_T {U} true
      BOOL_T _Connected;
      //## end cProxy::Connected%4399B93B015F.attr

      //## Attribute: ProxyMutex%3D25802B01C8
      //## begin cProxy::ProxyMutex%3D25802B01C8.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _ProxyMutex;
      //## end cProxy::ProxyMutex%3D25802B01C8.attr

      BOOL_T _Synchronized;

    // Additional Protected Declarations
      //## begin cProxy%3C4EE65F00FE.protected preserve=yes
      //## end cProxy%3C4EE65F00FE.protected

  private:
    // Additional Private Declarations
      //## begin cProxy%3C4EE65F00FE.private preserve=yes
      //## end cProxy%3C4EE65F00FE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cProxy%3C4EE65F00FE.implementation preserve=yes
      //## end cProxy%3C4EE65F00FE.implementation

};

//## begin cProxy%3C4EE65F00FE.postscript preserve=yes
//## end cProxy%3C4EE65F00FE.postscript

// Class cProxy 

//## begin module%3C4EE65F00FE.epilog preserve=yes
//## end module%3C4EE65F00FE.epilog


#endif
