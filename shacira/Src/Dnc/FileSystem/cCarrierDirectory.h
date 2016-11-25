//## begin module%3B98FC59007F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FC59007F.cm

//## begin module%3B98FC59007F.cp preserve=no
//## end module%3B98FC59007F.cp

//## Module: cCarrierDirectory%3B98FC59007F; Pseudo Package specification
//## Source file: d:\usr\prj\ls2i\src\Dnc\FileSystem\cCarrierDirectory.h

#ifndef cCarrierDirectory_h
#define cCarrierDirectory_h 1

//## begin module%3B98FC59007F.additionalIncludes preserve=no
//## end module%3B98FC59007F.additionalIncludes

//## begin module%3B98FC59007F.includes preserve=yes
//## end module%3B98FC59007F.includes

// cError
#include "System\cError.h"
// GlobalDefinitions
#include "System\GlobalDefinitions.h"
// cDirectory
#include "Dnc\FileSystem\cDirectory.h"

class cCarrier;

//## begin module%3B98FC59007F.additionalDeclarations preserve=yes
//## end module%3B98FC59007F.additionalDeclarations


//## begin cCarrierDirectory%3B98FC59007F.preface preserve=yes
//## end cCarrierDirectory%3B98FC59007F.preface

//## Class: cCarrierDirectory%3B98FC59007F
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B98FC8C02E5;GlobalDefinitions { -> }
//## Uses: <unnamed>%3B9C7B6E01ED;cError { -> }

class cCarrierDirectory : public cDirectory  //## Inherits: <unnamed>%3B98FC6A0250
{
  //## begin cCarrierDirectory%3B98FC59007F.initialDeclarations preserve=yes
  //## end cCarrierDirectory%3B98FC59007F.initialDeclarations

  public:
    //## Constructors (generated)
      cCarrierDirectory();

      cCarrierDirectory(const cCarrierDirectory &right);

    //## Constructors (specified)
      //## Operation: cCarrierDirectory%999877036
      cCarrierDirectory (cFileSystem *file_system, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cCarrierDirectory();


    //## Other Operations (specified)
      //## Operation: Refresh%999877039
      int Refresh ();

      //## Operation: FMFatRefresh%1000119061
      int FMFatRefresh ();

      //## Operation: FMT2Refresh%1000119062
      int FMT2Refresh ();

      //## Operation: FMT1Refresh%1000119063
      int FMT1Refresh ();

      //## Operation: FX25Refresh%1000119064
      int FX25Refresh ();

    // Additional Public Declarations
      //## begin cCarrierDirectory%3B98FC59007F.public preserve=yes
      //## end cCarrierDirectory%3B98FC59007F.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3B99059C0042
      //## Role: cCarrierDirectory::Carrier%3B99059E038E
      //## begin cCarrierDirectory::Carrier%3B99059E038E.role preserve=no  public: cCarrier { -> 1RFHN}
      cCarrier *_Carrier;
      //## end cCarrierDirectory::Carrier%3B99059E038E.role

    // Additional Protected Declarations
      //## begin cCarrierDirectory%3B98FC59007F.protected preserve=yes
      //## end cCarrierDirectory%3B98FC59007F.protected

  private:
    // Additional Private Declarations
      //## begin cCarrierDirectory%3B98FC59007F.private preserve=yes
      //## end cCarrierDirectory%3B98FC59007F.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCarrierDirectory%3B98FC59007F.implementation preserve=yes
      //## end cCarrierDirectory%3B98FC59007F.implementation

};

//## begin cCarrierDirectory%3B98FC59007F.postscript preserve=yes
//## end cCarrierDirectory%3B98FC59007F.postscript

// Class cCarrierDirectory 

//## begin module%3B98FC59007F.epilog preserve=yes
//## end module%3B98FC59007F.epilog


#endif
