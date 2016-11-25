//## begin module%440803760014.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440803760014.cm

//## begin module%440803760014.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440803760014.cp

//## Module: cBufferedFile%440803760014; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cBufferedFile.h

#ifndef cBufferedFile_h
#define cBufferedFile_h 1

//## begin module%440803760014.includes preserve=yes
//## end module%440803760014.includes

//## begin module%440803760014.additionalDeclarations preserve=yes
//## end module%440803760014.additionalDeclarations


//## begin cBufferedFile%440803760014.preface preserve=yes
//## end cBufferedFile%440803760014.preface

//## Class: cBufferedFile%440803760014
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cBufferedFile 
{
  //## begin cBufferedFile%440803760014.initialDeclarations preserve=yes
public:
  //## end cBufferedFile%440803760014.initialDeclarations

    //## Constructors (generated)
      cBufferedFile();

      cBufferedFile(const cBufferedFile &right);

    //## Destructor (generated)
      virtual ~cBufferedFile();


    //## Other Operations (specified)
      //## Operation: Buffer%1141375553
      STRING_T Buffer ();

      //## Operation: Printf%1141375554
      BOOL_T Printf (CONST_STRING_T fmt_str, ... );

  public:
    // Additional Public Declarations
      //## begin cBufferedFile%440803760014.public preserve=yes
      //## end cBufferedFile%440803760014.public

  protected:
    // Additional Protected Declarations
      //## begin cBufferedFile%440803760014.protected preserve=yes
      //## end cBufferedFile%440803760014.protected

  private:
    // Additional Private Declarations
      //## begin cBufferedFile%440803760014.private preserve=yes
      //## end cBufferedFile%440803760014.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cBufferedFile%440803760014.implementation preserve=yes
      //## end cBufferedFile%440803760014.implementation

};

//## begin cBufferedFile%440803760014.postscript preserve=yes
//## end cBufferedFile%440803760014.postscript

// Class cBufferedFile 

//## begin module%440803760014.epilog preserve=yes
//## end module%440803760014.epilog


#endif
