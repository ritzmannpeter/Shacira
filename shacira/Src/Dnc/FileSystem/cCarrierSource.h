//## begin module%3B9D035D003D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9D035D003D.cm

//## begin module%3B9D035D003D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9D035D003D.cp

//## Module: cCarrierSource%3B9D035D003D; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCarrierSource.h

#ifndef cCarrierSource_h
#define cCarrierSource_h 1

//## begin module%3B9D035D003D.includes preserve=yes
//## end module%3B9D035D003D.includes

// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"

class __DLL_EXPORT__ cCarrier;
class __DLL_EXPORT__ cCARRIERFat;

//## begin module%3B9D035D003D.additionalDeclarations preserve=yes
//## end module%3B9D035D003D.additionalDeclarations


//## begin cCarrierSource%3B9D035D003D.preface preserve=yes
//## end cCarrierSource%3B9D035D003D.preface

//## Class: cCarrierSource%3B9D035D003D
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F4F532801C5;cCARRIERFat { -> F}

class __DLL_EXPORT__ cCarrierSource : public cToolFileSource  //## Inherits: <unnamed>%3B9D03730099
{
  //## begin cCarrierSource%3B9D035D003D.initialDeclarations preserve=yes
public:
  //## end cCarrierSource%3B9D035D003D.initialDeclarations

    //## Constructors (generated)
      cCarrierSource();

      cCarrierSource(const cCarrierSource &right);

    //## Constructors (specified)
      //## Operation: cCarrierSource%1062078709
      cCarrierSource (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cCarrierSource();


    //## Other Operations (specified)
      //## Operation: FileSystem%1062078710
      virtual cToolFileSystem * FileSystem ();

  public:
    // Additional Public Declarations
      //## begin cCarrierSource%3B9D035D003D.public preserve=yes
      //## end cCarrierSource%3B9D035D003D.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::Carrier::<unnamed>%3F4E1F090271
      //## Role: cCarrierSource::Carrier%3F4E1F0A0196
      //## begin cCarrierSource::Carrier%3F4E1F0A0196.role preserve=no  public: cCarrier { -> 1RFHN}
      cCarrier *_Carrier;
      //## end cCarrierSource::Carrier%3F4E1F0A0196.role

    // Additional Protected Declarations
      //## begin cCarrierSource%3B9D035D003D.protected preserve=yes
      //## end cCarrierSource%3B9D035D003D.protected

  private:
    // Additional Private Declarations
      //## begin cCarrierSource%3B9D035D003D.private preserve=yes
      //## end cCarrierSource%3B9D035D003D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCarrierSource%3B9D035D003D.implementation preserve=yes
      //## end cCarrierSource%3B9D035D003D.implementation

};

//## begin cCarrierSource%3B9D035D003D.postscript preserve=yes
//## end cCarrierSource%3B9D035D003D.postscript

// Class cCarrierSource 

//## begin module%3B9D035D003D.epilog preserve=yes
//## end module%3B9D035D003D.epilog


#endif
