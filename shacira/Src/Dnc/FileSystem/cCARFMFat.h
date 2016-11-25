//## begin module%3F4F500A006D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4F500A006D.cm

//## begin module%3F4F500A006D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4F500A006D.cp

//## Module: cCARFMFat%3F4F500A006D; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCARFMFat.h

#ifndef cCARFMFat_h
#define cCARFMFat_h 1

//## begin module%3F4F500A006D.includes preserve=yes
//## end module%3F4F500A006D.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cCarrier;

//## begin module%3F4F500A006D.additionalDeclarations preserve=yes
//## end module%3F4F500A006D.additionalDeclarations


//## begin cCARFMFat%3F4F500A006D.preface preserve=yes
//## end cCARFMFat%3F4F500A006D.preface

//## Class: cCARFMFat%3F4F500A006D
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCARFMFat : public cToolFileSystem  //## Inherits: <unnamed>%3F4F5050036B
{
  //## begin cCARFMFat%3F4F500A006D.initialDeclarations preserve=yes
  //## end cCARFMFat%3F4F500A006D.initialDeclarations

    //## Constructors (generated)
      cCARFMFat();

      cCARFMFat(const cCARFMFat &right);

    //## Constructors (specified)
      //## Operation: cCARFMFat%1062162389
      cCARFMFat (CONST_STRING_T path, cCarrier *carrier);

    //## Destructor (generated)
      virtual ~cCARFMFat();


    //## Other Operations (specified)
      //## Operation: Directory%1062162390
      virtual void Directory (FILE_INFO_T * &file_info, ULONG_T file_count) = 0;

      //## Operation: Format%1062162391
      virtual void Format () = 0;

      //## Operation: Delete%1062162392
      virtual void Delete (CONST_STRING_T file_name) = 0;

      //## Operation: Add%1062162393
      virtual void Add (CONST_STRING_T file_name, void *buf, ULONG_T buf_size) = 0;

  public:
    // Additional Public Declarations
      //## begin cCARFMFat%3F4F500A006D.public preserve=yes
      //## end cCARFMFat%3F4F500A006D.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3F4F50CA007D
      //## Role: cCARFMFat::Carrier%3F4F50CA02CE
      //## begin cCARFMFat::Carrier%3F4F50CA02CE.role preserve=no  public: cCarrier { -> 1RFHN}
      cCarrier *_Carrier;
      //## end cCARFMFat::Carrier%3F4F50CA02CE.role

    // Additional Protected Declarations
      //## begin cCARFMFat%3F4F500A006D.protected preserve=yes
      //## end cCARFMFat%3F4F500A006D.protected

  private:
    // Additional Private Declarations
      //## begin cCARFMFat%3F4F500A006D.private preserve=yes
      //## end cCARFMFat%3F4F500A006D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCARFMFat%3F4F500A006D.implementation preserve=yes
      //## end cCARFMFat%3F4F500A006D.implementation

};

//## begin cCARFMFat%3F4F500A006D.postscript preserve=yes
//## end cCARFMFat%3F4F500A006D.postscript

// Class cCARFMFat 

//## begin module%3F4F500A006D.epilog preserve=yes
//## end module%3F4F500A006D.epilog


#endif
