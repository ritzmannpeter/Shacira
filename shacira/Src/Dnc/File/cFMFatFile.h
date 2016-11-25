//## begin module%3B9C9CC3008F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9CC3008F.cm

//## begin module%3B9C9CC3008F.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9CC3008F.cp

//## Module: cFMFatFile%3B9C9CC3008F; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMFatFile.h

#ifndef cFMFatFile_h
#define cFMFatFile_h 1

//## begin module%3B9C9CC3008F.includes preserve=yes

#include "devdisk.h"
#include "fmfat.h"

//## end module%3B9C9CC3008F.includes

// cError
#include "System/cError.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9C9CC3008F.additionalDeclarations preserve=yes
//## end module%3B9C9CC3008F.additionalDeclarations


//## begin cFMFatFile%3B9C9CC3008F.preface preserve=yes
//## end cFMFatFile%3B9C9CC3008F.preface

//## Class: cFMFatFile%3B9C9CC3008F
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B9CA14E005F;cError { -> }

class __DLL_EXPORT__ cFMFatFile : public cToolFile  //## Inherits: <unnamed>%3B9C9D6000EF
{
  //## begin cFMFatFile%3B9C9CC3008F.initialDeclarations preserve=yes
public:
   //## end cFMFatFile%3B9C9CC3008F.initialDeclarations

    //## Constructors (generated)
      cFMFatFile();

      cFMFatFile(const cFMFatFile &right);

    //## Constructors (specified)
      //## Operation: cFMFatFile%1000119065
      cFMFatFile (TOOLFILE_HEADER_T *file_header, cToolFileSystem *file_system);

    //## Destructor (generated)
      virtual ~cFMFatFile();


    //## Other Operations (specified)
      //## Operation: Save%1062507891
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cFMFatFile%3B9C9CC3008F.public preserve=yes
      //## end cFMFatFile%3B9C9CC3008F.public

  protected:
    // Additional Protected Declarations
      //## begin cFMFatFile%3B9C9CC3008F.protected preserve=yes
      //## end cFMFatFile%3B9C9CC3008F.protected

  private:
    // Additional Private Declarations
      //## begin cFMFatFile%3B9C9CC3008F.private preserve=yes
      //## end cFMFatFile%3B9C9CC3008F.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: FBuf%3B9FA72C008D
      //## begin cFMFatFile::FBuf%3B9FA72C008D.attr preserve=no  implementation: FILE_BUFFER_T * {U} NULL
      FILE_BUFFER_T *_FBuf;
      //## end cFMFatFile::FBuf%3B9FA72C008D.attr

      //## Attribute: FATBuf%3B9FA75E007B
      //## begin cFMFatFile::FATBuf%3B9FA75E007B.attr preserve=no  implementation: FMFAT_BUFFER_T * {U} NULL
      FMFAT_BUFFER_T *_FATBuf;
      //## end cFMFatFile::FATBuf%3B9FA75E007B.attr

    // Additional Implementation Declarations
      //## begin cFMFatFile%3B9C9CC3008F.implementation preserve=yes
      //## end cFMFatFile%3B9C9CC3008F.implementation

};

//## begin cFMFatFile%3B9C9CC3008F.postscript preserve=yes
//## end cFMFatFile%3B9C9CC3008F.postscript

// Class cFMFatFile 

//## begin module%3B9C9CC3008F.epilog preserve=yes
//## end module%3B9C9CC3008F.epilog


#endif
