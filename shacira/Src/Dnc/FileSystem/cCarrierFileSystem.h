//## begin module%3B98FC59007F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FC59007F.cm

//## begin module%3B98FC59007F.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98FC59007F.cp

//## Module: cCarrierFileSystem%3B98FC59007F; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCarrierFileSystem.h

#ifndef cCarrierFileSystem_h
#define cCarrierFileSystem_h 1

//## begin module%3B98FC59007F.includes preserve=yes
//## end module%3B98FC59007F.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cCarrierBase;
class __DLL_EXPORT__ cCarrierSource;

//## begin module%3B98FC59007F.additionalDeclarations preserve=yes
//## end module%3B98FC59007F.additionalDeclarations


//## begin cCarrierFileSystem%3B98FC59007F.preface preserve=yes
//## end cCarrierFileSystem%3B98FC59007F.preface

//## Class: cCarrierFileSystem%3B98FC59007F
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BAB6E9D0390;cCarrierSource { -> F}

class __DLL_EXPORT__ cCarrierFileSystem : public cToolFileSystem  //## Inherits: <unnamed>%3B98FC6A0250
{
  //## begin cCarrierFileSystem%3B98FC59007F.initialDeclarations preserve=yes
  //## end cCarrierFileSystem%3B98FC59007F.initialDeclarations

    //## Constructors (generated)
      cCarrierFileSystem();

      cCarrierFileSystem(const cCarrierFileSystem &right);

    //## Constructors (specified)
      //## Operation: cCarrierFileSystem%999877036
      cCarrierFileSystem (cCarrierSource *file_source, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cCarrierFileSystem();


    //## Other Operations (specified)
      //## Operation: Format%1000119088
      INT_T Format (INT_T format);

      //## Operation: Directory%1000119089
      INT_T Directory (STRING_LIST_T &file_names);

      //## Operation: Load%1000119090
      LONG_T Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: Save%1000119091
      LONG_T Save (CONST_STRING_T file_name, void *buf, ULONG_T size);

      //## Operation: Delete%1000119092
      INT_T Delete (CONST_STRING_T file_name);

      //## Operation: FileSize%1000386738
      LONG_T FileSize (CONST_STRING_T file_name);

      //## Operation: File%1000386739
      cFile * File (CONST_STRING_T file_name);

      //## Operation: GetTime%1000456417
      cTimeObject GetTime (CONST_STRING_T file_name);

  public:
    // Additional Public Declarations
      //## begin cCarrierFileSystem%3B98FC59007F.public preserve=yes
      //## end cCarrierFileSystem%3B98FC59007F.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3BA5BAC000C2
      //## Role: cCarrierFileSystem::Carrier%3BA5BAC103C6
      //## begin cCarrierFileSystem::Carrier%3BA5BAC103C6.role preserve=no  public: cCarrierBase { -> 1RFHN}
      cCarrierBase *_Carrier;
      //## end cCarrierFileSystem::Carrier%3BA5BAC103C6.role

    // Additional Protected Declarations
      //## begin cCarrierFileSystem%3B98FC59007F.protected preserve=yes
      //## end cCarrierFileSystem%3B98FC59007F.protected

  private:
    // Additional Private Declarations
      //## begin cCarrierFileSystem%3B98FC59007F.private preserve=yes
      //## end cCarrierFileSystem%3B98FC59007F.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCarrierFileSystem%3B98FC59007F.implementation preserve=yes
      //## end cCarrierFileSystem%3B98FC59007F.implementation

};

//## begin cCarrierFileSystem%3B98FC59007F.postscript preserve=yes
//## end cCarrierFileSystem%3B98FC59007F.postscript

// Class cCarrierFileSystem 

//## begin module%3B98FC59007F.epilog preserve=yes
//## end module%3B98FC59007F.epilog


#endif
