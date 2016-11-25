//## begin module%4CA9FA0D01C5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4CA9FA0D01C5.cm

//## begin module%4CA9FA0D01C5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4CA9FA0D01C5.cp

//## Module: cXmlService%4CA9FA0D01C5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\XMLService\cXmlService.h

#ifndef cXmlService_h
#define cXmlService_h 1

//## begin module%4CA9FA0D01C5.includes preserve=yes
//## end module%4CA9FA0D01C5.includes

// eb_thread
#include "base/eb_thread.hpp"

class __DLL_EXPORT__ cContext;

//## begin module%4CA9FA0D01C5.additionalDeclarations preserve=yes
//## end module%4CA9FA0D01C5.additionalDeclarations


//## begin cXmlService%4CA9FA0D01C5.preface preserve=yes
//## end cXmlService%4CA9FA0D01C5.preface

//## Class: cXmlService%4CA9FA0D01C5
//## Category: System::ClientServer::XMLService%4CA9F9CD00FA
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cXmlService : public cThread  //## Inherits: <unnamed>%4CA9FBAD0196
{
  //## begin cXmlService%4CA9FA0D01C5.initialDeclarations preserve=yes
public:
  //## end cXmlService%4CA9FA0D01C5.initialDeclarations

    //## Constructors (generated)
      cXmlService();

      cXmlService(const cXmlService &right);

    //## Constructors (specified)
      //## Operation: cXmlService%1286209113
      cXmlService (cContext *context, USHORT_T listener_port = 11333);

    //## Destructor (generated)
      virtual ~cXmlService();


    //## Other Operations (specified)
      //## Operation: onMain%1286209114
      virtual INT_T onMain (void *extra);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Port%4CAA03C7003E
      short get_Port () const;
      void set_Port (short value);

  public:
    // Additional Public Declarations
      //## begin cXmlService%4CA9FA0D01C5.public preserve=yes
      //## end cXmlService%4CA9FA0D01C5.public

  protected:
    // Data Members for Class Attributes

      //## begin cXmlService::Port%4CAA03C7003E.attr preserve=no  public: short {U} 11333
      short _Port;
      //## end cXmlService::Port%4CAA03C7003E.attr

    // Data Members for Associations

      //## Association: System::ClientServer::XMLService::<unnamed>%4CA9FD3F033C
      //## Role: cXmlService::Context%4CA9FD4100EA
      //## begin cXmlService::Context%4CA9FD4100EA.role preserve=no  implementation: cContext { -> RFHN}
      cContext *_Context;
      //## end cXmlService::Context%4CA9FD4100EA.role

    // Additional Protected Declarations
      //## begin cXmlService%4CA9FA0D01C5.protected preserve=yes
      //## end cXmlService%4CA9FA0D01C5.protected

  private:
    // Additional Private Declarations
      //## begin cXmlService%4CA9FA0D01C5.private preserve=yes
      //## end cXmlService%4CA9FA0D01C5.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cXmlService%4CA9FA0D01C5.implementation preserve=yes
      //## end cXmlService%4CA9FA0D01C5.implementation

};

//## begin cXmlService%4CA9FA0D01C5.postscript preserve=yes
//## end cXmlService%4CA9FA0D01C5.postscript

// Class cXmlService 

//## begin module%4CA9FA0D01C5.epilog preserve=yes
//## end module%4CA9FA0D01C5.epilog


#endif
