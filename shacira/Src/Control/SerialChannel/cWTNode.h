//## begin module%3CBBD3CA001E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CBBD3CA001E.cm

//## begin module%3CBBD3CA001E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CBBD3CA001E.cp

//## Module: cWTNode%3CBBD3CA001E; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cWTNode.h

#ifndef cWTNode_h
#define cWTNode_h 1

//## begin module%3CBBD3CA001E.includes preserve=yes

#ifdef __linux__
typedef sockaddr_in SOCKADDR_IN;
#endif

//## end module%3CBBD3CA001E.includes

// cError
#include "System/cError.h"
//## begin module%3CBBD3CA001E.additionalDeclarations preserve=yes
//## end module%3CBBD3CA001E.additionalDeclarations


//## begin cWTNode%3CBBD3CA001E.preface preserve=yes
#include "System/Sys/cSockets.h"
//## end cWTNode%3CBBD3CA001E.preface

//## Class: cWTNode%3CBBD3CA001E
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CBBD3EA0147;cError { -> }

class __DLL_EXPORT__ cWTNode 
{
  //## begin cWTNode%3CBBD3CA001E.initialDeclarations preserve=yes
public:
  //## end cWTNode%3CBBD3CA001E.initialDeclarations

    //## Constructors (generated)
      cWTNode();

      cWTNode(const cWTNode &right);

    //## Constructors (specified)
      //## Operation: cWTNode%1018942491
      cWTNode (CONST_STRING_T ip_address);

    //## Destructor (generated)
      virtual ~cWTNode();


    //## Other Operations (specified)
      //## Operation: Reachable%1018942492
      BOOL_T Reachable ();

      //## Operation: Refresh%1018942494
      void Refresh ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IPAddress%3CBBD987036A
      STRING_T get_IPAddress () const;
      void set_IPAddress (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cWTNode%3CBBD3CA001E.public preserve=yes
      //## end cWTNode%3CBBD3CA001E.public

  protected:
    // Data Members for Class Attributes

      //## begin cWTNode::IPAddress%3CBBD987036A.attr preserve=no  public: STRING_T {U} 
      STRING_T _IPAddress;
      //## end cWTNode::IPAddress%3CBBD987036A.attr

    // Additional Protected Declarations
      //## begin cWTNode%3CBBD3CA001E.protected preserve=yes
      //## end cWTNode%3CBBD3CA001E.protected

  private:
    // Additional Private Declarations
      //## begin cWTNode%3CBBD3CA001E.private preserve=yes
      //## end cWTNode%3CBBD3CA001E.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Ping%1018942497
      BOOL_T Ping (CONST_STRING_T address);

      //## Operation: Ping%1018942496
      BOOL_T Ping (SOCKADDR_IN *address);

    // Data Members for Class Attributes

      //## Attribute: Address%3CBBDC8202EF
      //## begin cWTNode::Address%3CBBDC8202EF.attr preserve=no  implementation: SOCKADDR_IN {U} 
      SOCKADDR_IN _Address;
      //## end cWTNode::Address%3CBBDC8202EF.attr

      //## Attribute: State%3CBBDCF8010E
      //## begin cWTNode::State%3CBBDCF8010E.attr preserve=no  implementation: INT_T {U} -1
      INT_T _State;
      //## end cWTNode::State%3CBBDCF8010E.attr

    // Additional Implementation Declarations
      //## begin cWTNode%3CBBD3CA001E.implementation preserve=yes
      //## end cWTNode%3CBBD3CA001E.implementation

};

//## begin cWTNode%3CBBD3CA001E.postscript preserve=yes
//## end cWTNode%3CBBD3CA001E.postscript

// Class cWTNode 

//## begin module%3CBBD3CA001E.epilog preserve=yes
//## end module%3CBBD3CA001E.epilog


#endif
