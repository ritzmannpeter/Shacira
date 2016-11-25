//## begin module%3F4F500A006D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4F500A006D.cm

//## begin module%3F4F500A006D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4F500A006D.cp

//## Module: cCARRIERFat%3F4F500A006D; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCARRIERFat.h

#ifndef cCARRIERFat_h
#define cCARRIERFat_h 1

//## begin module%3F4F500A006D.includes preserve=yes
//## end module%3F4F500A006D.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cCarrier;
class __DLL_EXPORT__ cFMFatFile;
class __DLL_EXPORT__ cToolFile;

//## begin module%3F4F500A006D.additionalDeclarations preserve=yes
//## end module%3F4F500A006D.additionalDeclarations


//## begin cCARRIERFat%3F4F500A006D.preface preserve=yes
//## end cCARRIERFat%3F4F500A006D.preface

//## Class: cCARRIERFat%3F4F500A006D
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F5497F30128;cToolFile { -> F}
//## Uses: <unnamed>%3F54B20803B9;cFMFatFile { -> F}

class __DLL_EXPORT__ cCARRIERFat : public cToolFileSystem  //## Inherits: <unnamed>%3F4F5050036B
{
  //## begin cCARRIERFat%3F4F500A006D.initialDeclarations preserve=yes
public:
  //## end cCARRIERFat%3F4F500A006D.initialDeclarations

    //## Constructors (generated)
      cCARRIERFat();

      cCARRIERFat(const cCARRIERFat &right);

    //## Constructors (specified)
      //## Operation: cCARRIERFat%1062162389
      cCARRIERFat (CONST_STRING_T path, cCarrier *carrier);

    //## Destructor (generated)
      virtual ~cCARRIERFat();


    //## Other Operations (specified)
      //## Operation: Directory%1062162390
      virtual void Directory (TOOLFILE_HEADER_T * &file_header, ULONG_T &file_count);

      //## Operation: Format%1062162391
      virtual void Format ();

      //## Operation: Delete%1062162392
      virtual void Delete (CONST_STRING_T file_name);

      //## Operation: ReadFile%1062507901
      virtual ULONG_T ReadFile (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: WriteFile%1062507902
      virtual void WriteFile (CONST_STRING_T file_name, void *buf, ULONG_T amount);

      //## Operation: ToolFile%1062507904
      virtual cToolFile * ToolFile (TOOLFILE_HEADER_T *file_header);

  public:
    // Additional Public Declarations
      //## begin cCARRIERFat%3F4F500A006D.public preserve=yes
      //## end cCARRIERFat%3F4F500A006D.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3F4F50CA007D
      //## Role: cCARRIERFat::Carrier%3F4F50CA02CE
      //## begin cCARRIERFat::Carrier%3F4F50CA02CE.role preserve=no  public: cCarrier { -> 1RFHN}
      cCarrier *_Carrier;
      //## end cCARRIERFat::Carrier%3F4F50CA02CE.role

    // Additional Protected Declarations
      //## begin cCARRIERFat%3F4F500A006D.protected preserve=yes
      //## end cCARRIERFat%3F4F500A006D.protected

  private:
    // Additional Private Declarations
      //## begin cCARRIERFat%3F4F500A006D.private preserve=yes
      //## end cCARRIERFat%3F4F500A006D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetSize%1062162399
      ULONG_T GetSize (USR_HANDLE hnd);

      //## Operation: OpenRead%1062162400
      USR_HANDLE OpenRead (CONST_STRING_T file_name);

      //## Operation: OpenWrite%1062162401
      USR_HANDLE OpenWrite (CONST_STRING_T file_name);

      //## Operation: Read%1062162402
      void Read (USR_HANDLE hnd, void *buf, ULONG_T amount);

      //## Operation: Write%1062162403
      void Write (USR_HANDLE hnd, void *buf, ULONG_T amount);

    // Additional Implementation Declarations
      //## begin cCARRIERFat%3F4F500A006D.implementation preserve=yes
      //## end cCARRIERFat%3F4F500A006D.implementation

};

//## begin cCARRIERFat%3F4F500A006D.postscript preserve=yes
//## end cCARRIERFat%3F4F500A006D.postscript

// Class cCARRIERFat 

//## begin module%3F4F500A006D.epilog preserve=yes
//## end module%3F4F500A006D.epilog


#endif
