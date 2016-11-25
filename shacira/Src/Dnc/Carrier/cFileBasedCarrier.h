//## begin module%3BA5B72D01AC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA5B72D01AC.cm

//## begin module%3BA5B72D01AC.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA5B72D01AC.cp

//## Module: cFileBasedCarrier%3BA5B72D01AC; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\Carrier\cFileBasedCarrier.h

#ifndef cFileBasedCarrier_h
#define cFileBasedCarrier_h 1

//## begin module%3BA5B72D01AC.includes preserve=yes
//## end module%3BA5B72D01AC.includes

// cCarrierBase
#include "Dnc/Carrier/cCarrierBase.h"

class cFileSystemUtils;

//## begin module%3BA5B72D01AC.additionalDeclarations preserve=yes
//## end module%3BA5B72D01AC.additionalDeclarations


//## begin cFileBasedCarrier%3BA5B72D01AC.preface preserve=yes
//## end cFileBasedCarrier%3BA5B72D01AC.preface

//## Class: cFileBasedCarrier%3BA5B72D01AC
//## Category: Dnc::Carrier%3B97BB340195
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA5BCFB0267;cFileSystemUtils { -> F}

class cFileBasedCarrier : public cCarrierBase  //## Inherits: <unnamed>%3BA5B74F02E2
{
  //## begin cFileBasedCarrier%3BA5B72D01AC.initialDeclarations preserve=yes
  //## end cFileBasedCarrier%3BA5B72D01AC.initialDeclarations

  public:
    //## Constructors (generated)
      cFileBasedCarrier();

      cFileBasedCarrier(const cFileBasedCarrier &right);

    //## Constructors (specified)
      //## Operation: cFileBasedCarrier%1000716056
      cFileBasedCarrier (INT_T size);

    //## Destructor (generated)
      virtual ~cFileBasedCarrier();


    //## Other Operations (specified)
      //## Operation: Read%1000716053
      LONG_T Read (void *buffer, ULONG_T address, LONG_T amount);

      //## Operation: Write%1000716054
      LONG_T Write (void *buffer, ULONG_T address, LONG_T amount);

      //## Operation: Size%1000716055
      LONG_T Size ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Size%3BA5BE8400F0
      INT_T get_Size () const;

      //## Attribute: FileName%3BA5BCD20023
      STRING_T get_FileName () const;

      //## Attribute: Path%3BA5C01F006F
      STRING_T get_Path () const;

    // Additional Public Declarations
      //## begin cFileBasedCarrier%3BA5B72D01AC.public preserve=yes
      //## end cFileBasedCarrier%3BA5B72D01AC.public

  protected:
    // Data Members for Class Attributes

      //## begin cFileBasedCarrier::Size%3BA5BE8400F0.attr preserve=no  public: INT_T {U} -1
      INT_T _Size;
      //## end cFileBasedCarrier::Size%3BA5BE8400F0.attr

      //## begin cFileBasedCarrier::FileName%3BA5BCD20023.attr preserve=no  public: STRING_T {U} 
      STRING_T _FileName;
      //## end cFileBasedCarrier::FileName%3BA5BCD20023.attr

      //## begin cFileBasedCarrier::Path%3BA5C01F006F.attr preserve=no  public: STRING_T {U} 
      STRING_T _Path;
      //## end cFileBasedCarrier::Path%3BA5C01F006F.attr

    // Additional Protected Declarations
      //## begin cFileBasedCarrier%3BA5B72D01AC.protected preserve=yes
      //## end cFileBasedCarrier%3BA5B72D01AC.protected

  private:
    // Additional Private Declarations
      //## begin cFileBasedCarrier%3BA5B72D01AC.private preserve=yes
      //## end cFileBasedCarrier%3BA5B72D01AC.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Seek%1000716059
      LONG_T Seek (HANDLE handle, ULONG_T address);

      //## Operation: CreateDump%1000716058
      void CreateDump ();

    // Additional Implementation Declarations
      //## begin cFileBasedCarrier%3BA5B72D01AC.implementation preserve=yes
      //## end cFileBasedCarrier%3BA5B72D01AC.implementation

};

//## begin cFileBasedCarrier%3BA5B72D01AC.postscript preserve=yes
//## end cFileBasedCarrier%3BA5B72D01AC.postscript

// Class cFileBasedCarrier 

//## begin module%3BA5B72D01AC.epilog preserve=yes
//## end module%3BA5B72D01AC.epilog


#endif
