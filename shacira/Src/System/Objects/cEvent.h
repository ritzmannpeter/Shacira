//## begin module%3D05B0870231.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D05B0870231.cm

//## begin module%3D05B0870231.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D05B0870231.cp

//## Module: cEvent%3D05B0870231; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cEvent.h

#ifndef cEvent_h
#define cEvent_h 1

//## begin module%3D05B0870231.includes preserve=yes
//## end module%3D05B0870231.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

//## begin module%3D05B0870231.additionalDeclarations preserve=yes
//## end module%3D05B0870231.additionalDeclarations


//## begin cEvent%3D05B0870231.preface preserve=yes
//## end cEvent%3D05B0870231.preface

//## Class: cEvent%3D05B0870231
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A57DD02EC;cTransferObject { -> F}

class __DLL_EXPORT__ cEvent : public cTransientObject  //## Inherits: <unnamed>%3D05B157035C
{
  //## begin cEvent%3D05B0870231.initialDeclarations preserve=yes
public:
  //## end cEvent%3D05B0870231.initialDeclarations

    //## Constructors (generated)
      cEvent();

      cEvent(const cEvent &right);

    //## Constructors (specified)
      //## Operation: cEvent%1023780997
      cEvent (cStaticObject *source, INT_T event_code);

    //## Destructor (generated)
      virtual ~cEvent();


    //## Other Operations (specified)
      //## Operation: Serialize%1023780998
      virtual STRING_T Serialize ();

      //## Operation: Construct%1023780999
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

  public:
    // Additional Public Declarations
      //## begin cEvent%3D05B0870231.public preserve=yes
      //## end cEvent%3D05B0870231.public

  protected:
    // Additional Protected Declarations
      //## begin cEvent%3D05B0870231.protected preserve=yes
      //## end cEvent%3D05B0870231.protected

  private:
    // Additional Private Declarations
      //## begin cEvent%3D05B0870231.private preserve=yes
      //## end cEvent%3D05B0870231.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cEvent%3D05B0870231.implementation preserve=yes
      //## end cEvent%3D05B0870231.implementation

};

//## begin cEvent%3D05B0870231.postscript preserve=yes
//## end cEvent%3D05B0870231.postscript

// Class cEvent 

//## begin module%3D05B0870231.epilog preserve=yes
//## end module%3D05B0870231.epilog


#endif
