//## begin module%43B1044B015D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43B1044B015D.cm

//## begin module%43B1044B015D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43B1044B015D.cp

//## Module: cEM63Requester%43B1044B015D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cEM63Requester.h

#ifndef cEM63Requester_h
#define cEM63Requester_h 1

//## begin module%43B1044B015D.includes preserve=yes
//## end module%43B1044B015D.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cUserInfo;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cEM63Program;
class __DLL_EXPORT__ cEM63Session;
class __DLL_EXPORT__ cEM63Interface;
class __DLL_EXPORT__ cEM63Job;
class __DLL_EXPORT__ cEM63StyxParser;

//## begin module%43B1044B015D.additionalDeclarations preserve=yes
//## end module%43B1044B015D.additionalDeclarations


//## begin cEM63Requester%43B1044B015D.preface preserve=yes
//## end cEM63Requester%43B1044B015D.preface

//## Class: cEM63Requester%43B1044B015D
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43B107CC0250;cEM63Session { -> F}
//## Uses: <unnamed>%43B107D5029F;cEM63Job { -> F}
//## Uses: <unnamed>%43B10D1F02C9;cFileSystemUtils { -> F}
//## Uses: <unnamed>%43B10FB80069;cEM63StyxParser { -> F}
//## Uses: <unnamed>%43E9E6D502ED;cUserInfo { -> F}

class __DLL_EXPORT__ cEM63Requester : public cControlThread  //## Inherits: <unnamed>%43B1048203D4
{
  //## begin cEM63Requester%43B1044B015D.initialDeclarations preserve=yes
public:
  //## end cEM63Requester%43B1044B015D.initialDeclarations

    //## Constructors (generated)
      cEM63Requester();

      cEM63Requester(const cEM63Requester &right);

    //## Constructors (specified)
      //## Operation: cEM63Requester%1135674629
      cEM63Requester (cEM63Program *program);

    //## Destructor (generated)
      virtual ~cEM63Requester();


    //## Other Operations (specified)
      //## Operation: ControlFunc%1135674619
      virtual INT_T ControlFunc ();

  public:
    // Additional Public Declarations
      //## begin cEM63Requester%43B1044B015D.public preserve=yes
      //## end cEM63Requester%43B1044B015D.public

  protected:
    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%43B104A800FA
      //## Role: cEM63Requester::Program%43B104AA035C
      //## begin cEM63Requester::Program%43B104AA035C.role preserve=no  public: cEM63Program {1 -> 1RFHN}
      cEM63Program *_Program;
      //## end cEM63Requester::Program%43B104AA035C.role

      //## Association: Control::Cell::<unnamed>%43B10DC10009
      //## Role: cEM63Requester::Interface%43B10DC1025B
      //## begin cEM63Requester::Interface%43B10DC1025B.role preserve=no  public: cEM63Interface { -> 1RFHN}
      cEM63Interface *_Interface;
      //## end cEM63Requester::Interface%43B10DC1025B.role

    // Additional Protected Declarations
      //## begin cEM63Requester%43B1044B015D.protected preserve=yes
      //## end cEM63Requester%43B1044B015D.protected

  private:
    // Additional Private Declarations
      //## begin cEM63Requester%43B1044B015D.private preserve=yes
      //## end cEM63Requester%43B1044B015D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ParseSessionRequest%1135674621
      BOOL_T ParseSessionRequest (cEM63Session *session, CONST_STRING_T file);

      //## Operation: CheckRequest%1135674625
      void CheckRequest (CONST_STRING_T directory);

      //## Operation: HandleSession%1135674626
      void HandleSession (CONST_STRING_T source);

    // Additional Implementation Declarations
      //## begin cEM63Requester%43B1044B015D.implementation preserve=yes
      bool _sessionDirectoryPresent;
      //## end cEM63Requester%43B1044B015D.implementation

    friend class __DLL_EXPORT__ cEM63Program;
};

//## begin cEM63Requester%43B1044B015D.postscript preserve=yes
//## end cEM63Requester%43B1044B015D.postscript

// Class cEM63Requester 

//## begin module%43B1044B015D.epilog preserve=yes
//## end module%43B1044B015D.epilog


#endif
