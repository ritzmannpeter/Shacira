//## begin module%3C4EA4E60266.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EA4E60266.cm

//## begin module%3C4EA4E60266.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EA4E60266.cp

//## Module: cBroker%3C4EA4E60266; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Orb\cBroker.h

#ifndef cBroker_h
#define cBroker_h 1

//## begin module%3C4EA4E60266.includes preserve=yes
//## end module%3C4EA4E60266.includes

// cControlThread
#include "System/Threads/cControlThread.h"
//## begin module%3C4EA4E60266.additionalDeclarations preserve=yes
#include "CorbaDefinitions.h"
//## end module%3C4EA4E60266.additionalDeclarations


//## begin cBroker%3C4EA4E60266.preface preserve=yes
//## end cBroker%3C4EA4E60266.preface

//## Class: cBroker%3C4EA4E60266
//## Category: Orb%3AC0838100CF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cBroker : public cControlThread  //## Inherits: <unnamed>%3C4EA50E00DD
{
  //## begin cBroker%3C4EA4E60266.initialDeclarations preserve=yes
public:
  //## end cBroker%3C4EA4E60266.initialDeclarations

    //## Constructors (generated)
      cBroker();

      cBroker(const cBroker &right);

    //## Constructors (specified)
      //## Operation: cBroker%1037211078
      cBroker (INT_T argc, CHAR_T **argv);

    //## Destructor (generated)
      virtual ~cBroker();


    //## Other Operations (specified)
      //## Operation: Initialize%1049215549
      static void Initialize (INT_T argc = 0, CHAR_T **argv = NULL);

      //## Operation: Cleanup%1111081373
      static void Cleanup ();

      //## Operation: MainFunc%1021469768
      virtual INT_T MainFunc (void *extra);

      //## Operation: Orb%1011787178
      static CORBA::ORB * Orb ();

      //## Operation: DecodeIOR%1124461687
      static void DecodeIOR (CONST_STRING_T ior, STRING_T &ip_addr, ULONG_T &port);

  public:
    // Additional Public Declarations
      //## begin cBroker%3C4EA4E60266.public preserve=yes
      static PortableServer::POA * Poa ();
      static void SetUseCorbaLoc(bool use_corba_loc);
      static bool GetUseCorbaLoc();
      static void SetORBTraceLevel(int level);
      static int GetORBTraceLevel();
      static void SetObjectDefaultPort(int port);
      static int GetObjectDefaultPort();
      static int ObjectDefaultPort();
      static bool IsCorbaLocURI(CONST_STRING_T ior, STRING_T &version, STRING_T &ip_addr, STRING_T &port, STRING_T &object_key);
      //## end cBroker%3C4EA4E60266.public

  protected:
    // Additional Protected Declarations
      //## begin cBroker%3C4EA4E60266.protected preserve=yes
      // the Portable Object Adapter (POA) is needed to implement a "CorbaLoc" addressing scheme
      // to enable address translation in (f. e. vpn)
      // the portable object adapter is compatible to the Basic Object Adapter (BOA)
      // therefore _Boa is not used anymore and should be cleared when the POA functionality is verified
      static PortableServer::POA_var cBroker::_Poa;
      static bool _UseCorbaLoc;
      static int _ObjectDefaultPort;
      static int _ORBTraceLevel;
      //## end cBroker%3C4EA4E60266.protected

  private:
    // Additional Private Declarations
      //## begin cBroker%3C4EA4E60266.private preserve=yes
      //## end cBroker%3C4EA4E60266.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: StartBroker%1037188598
      static void StartBroker (INT_T argc = 0, CHAR_T **argv = NULL);
      static void AddAdditionalParams(INT_T & argc, CHAR_T ** argv);

      //## Operation: StopBroker%1037188599
      static void StopBroker ();

    // Data Members for Class Attributes

      //## Attribute: RefCount%3DD2A43D0365
      //## begin cBroker::RefCount%3DD2A43D0365.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _RefCount;
      //## end cBroker::RefCount%3DD2A43D0365.attr

      //## Attribute: Mutex%3DD2A43D036F
      //## begin cBroker::Mutex%3DD2A43D036F.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _Mutex;
      //## end cBroker::Mutex%3DD2A43D036F.attr

      //## Attribute: Orb%3DD2A5C90116
      //## begin cBroker::Orb%3DD2A5C90116.attr preserve=no  implementation: static CORBA::ORB_var {U} NULL_ORB
      static CORBA::ORB_var _Orb;
      //## end cBroker::Orb%3DD2A5C90116.attr

      //## Attribute: ORBName%3DD2AB0E0198
      //## begin cBroker::ORBName%3DD2AB0E0198.attr preserve=no  implementation: static STRING_T {U} "Unknown"
      static STRING_T _ORBName;
      //## end cBroker::ORBName%3DD2AB0E0198.attr

      //## Attribute: Broker%3E89C19C0157
      //## begin cBroker::Broker%3E89C19C0157.attr preserve=no  implementation: static cBroker * {U} NULL
      static cBroker *_Broker;
      //## end cBroker::Broker%3E89C19C0157.attr

    // Additional Implementation Declarations
      //## begin cBroker%3C4EA4E60266.implementation preserve=yes
      //## end cBroker%3C4EA4E60266.implementation

};

//## begin cBroker%3C4EA4E60266.postscript preserve=yes
//## end cBroker%3C4EA4E60266.postscript

// Class cBroker 

//## begin module%3C4EA4E60266.epilog preserve=yes
//## end module%3C4EA4E60266.epilog


#endif
