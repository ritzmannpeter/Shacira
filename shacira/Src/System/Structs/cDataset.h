//## begin module%411DF3E3036B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%411DF3E3036B.cm

//## begin module%411DF3E3036B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%411DF3E3036B.cp

//## Module: cDataset%411DF3E3036B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cDataset.h

#ifndef cDataset_h
#define cDataset_h 1

//## begin module%411DF3E3036B.includes preserve=yes
//## end module%411DF3E3036B.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFileContext;
class __DLL_EXPORT__ cSHFile;
class __DLL_EXPORT__ cDatasetDirectory;
class __DLL_EXPORT__ cStyxParser;

//## begin module%411DF3E3036B.additionalDeclarations preserve=yes
//## end module%411DF3E3036B.additionalDeclarations


//## begin cDataset%411DF3E3036B.preface preserve=yes
//## end cDataset%411DF3E3036B.preface

//## Class: cDataset%411DF3E3036B
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%411DF5FA01B5;cStyxParser { -> F}
//## Uses: <unnamed>%411DF67900AB;cSHFile { -> F}
//## Uses: <unnamed>%411DFB3103C8;cFileContext { -> F}

class __DLL_EXPORT__ cDataset 
{
  //## begin cDataset%411DF3E3036B.initialDeclarations preserve=yes
public:
  //## end cDataset%411DF3E3036B.initialDeclarations

    //## Constructors (generated)
      cDataset();

      cDataset(const cDataset &right);

    //## Constructors (specified)
      //## Operation: cDataset%1092480803
      cDataset (CONST_STRING_T source, BOOL_T file_name = true);

    //## Destructor (generated)
      virtual ~cDataset();


    //## Other Operations (specified)
      //## Operation: Load%1092480804
      BOOL_T Load ();

      //## Operation: IsValid%1092480805
      BOOL_T IsValid ();

      //## Operation: GetContext%1092480806
      cContext * GetContext ();

  public:
    // Additional Public Declarations
      //## begin cDataset%411DF3E3036B.public preserve=yes
      //## end cDataset%411DF3E3036B.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: Buf%411DFAB70138
      //## begin cDataset::Buf%411DFAB70138.attr preserve=no  protected: STRING_T {U} 
      STRING_T _Buf;
      //## end cDataset::Buf%411DFAB70138.attr

    // Data Members for Associations

      //## Association: System::Structs::<unnamed>%41206387036B
      //## Role: cDataset::Directory%412063880261
      //## begin cDataset::Directory%412063880261.role preserve=no  public: cDatasetDirectory {0..n -> 1RFHN}
      cDatasetDirectory *_Directory;
      //## end cDataset::Directory%412063880261.role

      //## Association: System::Structs::<unnamed>%411DF55601B5
      //## Role: cDataset::Context%411DF5570290
      //## begin cDataset::Context%411DF5570290.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cDataset::Context%411DF5570290.role

    // Additional Protected Declarations
      //## begin cDataset%411DF3E3036B.protected preserve=yes
      //## end cDataset%411DF3E3036B.protected

  private:
    // Additional Private Declarations
      //## begin cDataset%411DF3E3036B.private preserve=yes
      //## end cDataset%411DF3E3036B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDataset%411DF3E3036B.implementation preserve=yes
      //## end cDataset%411DF3E3036B.implementation

};

//## begin cDataset%411DF3E3036B.postscript preserve=yes
//## end cDataset%411DF3E3036B.postscript

// Class cDataset 

//## begin module%411DF3E3036B.epilog preserve=yes
//## end module%411DF3E3036B.epilog


#endif
