//## begin module%3BA5B69C028A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA5B69C028A.cm

//## begin module%3BA5B69C028A.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA5B69C028A.cp

//## Module: cCarrierBase%3BA5B69C028A; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\Carrier\cCarrierBase.h

#ifndef cCarrierBase_h
#define cCarrierBase_h 1

//## begin module%3BA5B69C028A.includes preserve=yes
//## end module%3BA5B69C028A.includes

//## begin module%3BA5B69C028A.additionalDeclarations preserve=yes
//## end module%3BA5B69C028A.additionalDeclarations


//## begin cCarrierBase%3BA5B69C028A.preface preserve=yes
//## end cCarrierBase%3BA5B69C028A.preface

//## Class: cCarrierBase%3BA5B69C028A
//## Category: Dnc::Carrier%3B97BB340195
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class cCarrierBase 
{
  //## begin cCarrierBase%3BA5B69C028A.initialDeclarations preserve=yes
  //## end cCarrierBase%3BA5B69C028A.initialDeclarations

  public:
    //## Constructors (generated)
      cCarrierBase();

      cCarrierBase(const cCarrierBase &right);

    //## Destructor (generated)
      virtual ~cCarrierBase();


    //## Other Operations (specified)
      //## Operation: Read%1000716050
      virtual LONG_T Read (void *buffer, ULONG_T address, LONG_T amount) = 0;

      //## Operation: Write%1000716051
      virtual LONG_T Write (void *buffer, ULONG_T address, LONG_T amount) = 0;

      //## Operation: Size%1000716052
      virtual LONG_T Size () = 0;

    // Additional Public Declarations
      //## begin cCarrierBase%3BA5B69C028A.public preserve=yes
      //## end cCarrierBase%3BA5B69C028A.public

  protected:
    // Additional Protected Declarations
      //## begin cCarrierBase%3BA5B69C028A.protected preserve=yes
      //## end cCarrierBase%3BA5B69C028A.protected

  private:
    // Additional Private Declarations
      //## begin cCarrierBase%3BA5B69C028A.private preserve=yes
      //## end cCarrierBase%3BA5B69C028A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCarrierBase%3BA5B69C028A.implementation preserve=yes
      //## end cCarrierBase%3BA5B69C028A.implementation

};

//## begin cCarrierBase%3BA5B69C028A.postscript preserve=yes
//## end cCarrierBase%3BA5B69C028A.postscript

// Class cCarrierBase 

//## begin module%3BA5B69C028A.epilog preserve=yes
//## end module%3BA5B69C028A.epilog


#endif
