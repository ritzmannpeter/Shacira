//## begin module%4326CBDB01E4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4326CBDB01E4.cm

//## begin module%4326CBDB01E4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4326CBDB01E4.cp

//## Module: cRequest%4326CBDB01E4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cRequest.h

#ifndef cRequest_h
#define cRequest_h 1

//## begin module%4326CBDB01E4.includes preserve=yes
//## end module%4326CBDB01E4.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
//## begin module%4326CBDB01E4.additionalDeclarations preserve=yes
//## end module%4326CBDB01E4.additionalDeclarations


//## begin cRequest%4326CBDB01E4.preface preserve=yes
//## end cRequest%4326CBDB01E4.preface

//## Class: cRequest%4326CBDB01E4
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cRequest : public cTransientObject  //## Inherits: <unnamed>%4326CCAA00C8
{
  //## begin cRequest%4326CBDB01E4.initialDeclarations preserve=yes
public:
  //## end cRequest%4326CBDB01E4.initialDeclarations

    //## Constructors (generated)
      cRequest();

      cRequest(const cRequest &right);

    //## Constructors (specified)
      //## Operation: cRequest%1126616256
      cRequest (cStaticObject *source, INT_T event_code);

    //## Destructor (generated)
      virtual ~cRequest();


    //## Other Operations (specified)
      //## Operation: Serialize%1126616257
      virtual STRING_T Serialize ();

      //## Operation: Construct%1126616258
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

  public:
    // Additional Public Declarations
      //## begin cRequest%4326CBDB01E4.public preserve=yes
      //## end cRequest%4326CBDB01E4.public

  protected:
    // Additional Protected Declarations
      //## begin cRequest%4326CBDB01E4.protected preserve=yes
      //## end cRequest%4326CBDB01E4.protected

  private:
    // Additional Private Declarations
      //## begin cRequest%4326CBDB01E4.private preserve=yes
      //## end cRequest%4326CBDB01E4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cRequest%4326CBDB01E4.implementation preserve=yes
      //## end cRequest%4326CBDB01E4.implementation

};

//## begin cRequest%4326CBDB01E4.postscript preserve=yes
//## end cRequest%4326CBDB01E4.postscript

// Class cRequest 

//## begin module%4326CBDB01E4.epilog preserve=yes
//## end module%4326CBDB01E4.epilog


#endif
