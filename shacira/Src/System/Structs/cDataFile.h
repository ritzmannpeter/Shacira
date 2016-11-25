//## begin module%411DF3E3036B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%411DF3E3036B.cm

//## begin module%411DF3E3036B.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%411DF3E3036B.cp

//## Module: cDataFile%411DF3E3036B; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\System\Structs\cDataFile.h

#ifndef cDataFile_h
#define cDataFile_h 1

//## begin module%411DF3E3036B.includes preserve=yes
//## end module%411DF3E3036B.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFileContext;
class __DLL_EXPORT__ cSHFile;
class __DLL_EXPORT__ cStyxParser;

//## begin module%411DF3E3036B.additionalDeclarations preserve=yes
//## end module%411DF3E3036B.additionalDeclarations


//## begin cDataFile%411DF3E3036B.preface preserve=yes
//## end cDataFile%411DF3E3036B.preface

//## Class: cDataFile%411DF3E3036B
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%411DF5FA01B5;cStyxParser { -> F}
//## Uses: <unnamed>%411DF67900AB;cSHFile { -> F}
//## Uses: <unnamed>%411DFB3103C8;cFileContext { -> F}

class __DLL_EXPORT__ cDataFile 
{
  //## begin cDataFile%411DF3E3036B.initialDeclarations preserve=yes
public:
  //## end cDataFile%411DF3E3036B.initialDeclarations

    //## Constructors (generated)
      cDataFile();

      cDataFile(const cDataFile &right);

    //## Constructors (specified)
      //## Operation: cDataFile%1092480803
      cDataFile (CONST_STRING_T source, BOOL_T file_name = true);

    //## Destructor (generated)
      virtual ~cDataFile();


    //## Other Operations (specified)
      //## Operation: Load%1092480804
      BOOL_T Load ();

      //## Operation: IsValid%1092480805
      BOOL_T IsValid ();

      //## Operation: GetContext%1092480806
      cContext * GetContext ();

  public:
    // Additional Public Declarations
      //## begin cDataFile%411DF3E3036B.public preserve=yes
      //## end cDataFile%411DF3E3036B.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: Buf%411DFAB70138
      //## begin cDataFile::Buf%411DFAB70138.attr preserve=no  protected: STRING_T {U} 
      STRING_T _Buf;
      //## end cDataFile::Buf%411DFAB70138.attr

    // Data Members for Associations

      //## Association: System::Structs::<unnamed>%411DF55601B5
      //## Role: cDataFile::Context%411DF5570290
      //## begin cDataFile::Context%411DF5570290.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cDataFile::Context%411DF5570290.role

    // Additional Protected Declarations
      //## begin cDataFile%411DF3E3036B.protected preserve=yes
      //## end cDataFile%411DF3E3036B.protected

  private:
    // Additional Private Declarations
      //## begin cDataFile%411DF3E3036B.private preserve=yes
      //## end cDataFile%411DF3E3036B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDataFile%411DF3E3036B.implementation preserve=yes
      //## end cDataFile%411DF3E3036B.implementation

};

//## begin cDataFile%411DF3E3036B.postscript preserve=yes
//## end cDataFile%411DF3E3036B.postscript

// Class cDataFile 

//## begin module%411DF3E3036B.epilog preserve=yes
//## end module%411DF3E3036B.epilog


#endif
