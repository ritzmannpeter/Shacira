//## begin module%429C6DCA00EA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429C6DCA00EA.cm

//## begin module%429C6DCA00EA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429C6DCA00EA.cp

//## Module: cGateway%429C6DCA00EA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cGateway.h

#ifndef cGateway_h
#define cGateway_h 1

//## begin module%429C6DCA00EA.includes preserve=yes
//## end module%429C6DCA00EA.includes

// cProgram
#include "Control/Cell/cProgram.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cGatewayServer;

//## begin module%429C6DCA00EA.additionalDeclarations preserve=yes
//## end module%429C6DCA00EA.additionalDeclarations


//## begin cGateway%429C6DCA00EA.preface preserve=yes
//## end cGateway%429C6DCA00EA.preface

//## Class: cGateway%429C6DCA00EA
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42E6312E01A5;cContext { -> F}

class __DLL_EXPORT__ cGateway : public cProgram  //## Inherits: <unnamed>%429C6DDE000F
{
  //## begin cGateway%429C6DCA00EA.initialDeclarations preserve=yes
public:
  //## end cGateway%429C6DCA00EA.initialDeclarations

    //## Constructors (generated)
      cGateway();

      cGateway(const cGateway &right);

    //## Constructors (specified)
      //## Operation: cGateway%1117545273
      cGateway (cConfigurationObject *config_obj, cContext *context);

    //## Destructor (generated)
      virtual ~cGateway();


    //## Other Operations (specified)
      //## Operation: Start%1117548692
      virtual void Start ();

      //## Operation: Stop%1117548693
      virtual void Stop ();

      //## Operation: GetPage%1127152536
      virtual void GetPage (CONST_STRING_T page, STRING_T &page_text);

      //## Operation: Request%1135674615
      virtual void Request (CONST_STRING_T request, STRING_T &response);

  public:
    // Additional Public Declarations
      //## begin cGateway%429C6DCA00EA.public preserve=yes
      //## end cGateway%429C6DCA00EA.public

  protected:

    //## Other Operations (specified)
      //## Operation: ProcessEvent%1117548689
      virtual void ProcessEvent (cTransientObject *object);

      //## Operation: Cycle%1117548690
      virtual void Cycle ();

      //## Operation: Initialize%1117548691
      virtual void Initialize ();

    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%429C71AE038A
      //## Role: cGateway::Server%429C71AF029F
      //## begin cGateway::Server%429C71AF029F.role preserve=no  public: cGatewayServer {1 -> 1RFHN}
      cGatewayServer *_Server;
      //## end cGateway::Server%429C71AF029F.role

    // Additional Protected Declarations
      //## begin cGateway%429C6DCA00EA.protected preserve=yes
      //## end cGateway%429C6DCA00EA.protected

  private:
    // Additional Private Declarations
      //## begin cGateway%429C6DCA00EA.private preserve=yes
      //## end cGateway%429C6DCA00EA.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cGateway%429C6DCA00EA.implementation preserve=yes
      //## end cGateway%429C6DCA00EA.implementation

};

//## begin cGateway%429C6DCA00EA.postscript preserve=yes
//## end cGateway%429C6DCA00EA.postscript

// Class cGateway 

//## begin module%429C6DCA00EA.epilog preserve=yes
//## end module%429C6DCA00EA.epilog


#endif
