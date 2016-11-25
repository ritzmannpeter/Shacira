//## begin module%3C5ED32D01D2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5ED32D01D2.cm

//## begin module%3C5ED32D01D2.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C5ED32D01D2.cp

//## Module: cProxySender%3C5ED32D01D2; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxySender.h

#ifndef cProxySender_h
#define cProxySender_h 1

//## begin module%3C5ED32D01D2.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%3C5ED32D01D2.includes

// cStaticObject
#include "System/Objects/cStaticObject.h"

class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cConfigurationObject;

//## begin module%3C5ED32D01D2.additionalDeclarations preserve=yes
//## end module%3C5ED32D01D2.additionalDeclarations


//## begin cProxySender%3C5ED32D01D2.preface preserve=yes
//## end cProxySender%3C5ED32D01D2.preface

//## Class: cProxySender%3C5ED32D01D2
//## Category: System::Comm%3A8CE33700FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EDB2C0A038A;cConfigurationObject { -> F}
//## Uses: <unnamed>%3EDB2C4600FA;cProxy { -> F}

class __DLL_EXPORT__ cProxySender : public cStaticObject  //## Inherits: <unnamed>%3EDB2AFE0196
{
  //## begin cProxySender%3C5ED32D01D2.initialDeclarations preserve=yes
public:
  //## end cProxySender%3C5ED32D01D2.initialDeclarations

    //## Constructors (generated)
      cProxySender();

      cProxySender(const cProxySender &right);

    //## Constructors (specified)
      //## Operation: cProxySender%1012812258
      cProxySender (CONST_STRING_T ip_addr, ULONG_T port);

      //## Operation: cProxySender%1012812259
      cProxySender (cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cProxySender();


    //## Other Operations (specified)
      //## Operation: Send%1054547837
      BOOL_T Send (cProxy *proxy);

      //## Operation: Send%1054632819
      ULONG_T Send (CONST_STRING_T serialized_proxy);

      //## Operation: SenderName%1134385869
      static STRING_T SenderName (CONST_STRING_T addr, USHORT_T port);

  public:
    // Additional Public Declarations
      //## begin cProxySender%3C5ED32D01D2.public preserve=yes
      //## end cProxySender%3C5ED32D01D2.public

  protected:
    // Additional Protected Declarations
      //## begin cProxySender%3C5ED32D01D2.protected preserve=yes
      //## end cProxySender%3C5ED32D01D2.protected

  private:
    // Additional Private Declarations
      //## begin cProxySender%3C5ED32D01D2.private preserve=yes
      //## end cProxySender%3C5ED32D01D2.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetSockets%1054547838
      void SetSockets ();

      //## Operation: CloseSockets%1054547839
      void CloseSockets ();

    // Data Members for Class Attributes

      //## Attribute: IPAddress%3EDB29AA0000
      //## begin cProxySender::IPAddress%3EDB29AA0000.attr preserve=no  implementation: STRING_T {U} "127.0.0.1"
      STRING_T _IPAddress;
      //## end cProxySender::IPAddress%3EDB29AA0000.attr

      //## Attribute: Port%3EDB29AA000F
      //## begin cProxySender::Port%3EDB29AA000F.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _Port;
      //## end cProxySender::Port%3EDB29AA000F.attr

      //## Attribute: Socket%3EDB29AA001F
      //## begin cProxySender::Socket%3EDB29AA001F.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cProxySender::Socket%3EDB29AA001F.attr

    // Additional Implementation Declarations
      //## begin cProxySender%3C5ED32D01D2.implementation preserve=yes
      //## end cProxySender%3C5ED32D01D2.implementation

};

//## begin cProxySender%3C5ED32D01D2.postscript preserve=yes
//## end cProxySender%3C5ED32D01D2.postscript

// Class cProxySender 

//## begin module%3C5ED32D01D2.epilog preserve=yes
//## end module%3C5ED32D01D2.epilog


#endif
