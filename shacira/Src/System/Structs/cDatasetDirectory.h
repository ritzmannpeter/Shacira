//## begin module%412062FB0280.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412062FB0280.cm

//## begin module%412062FB0280.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412062FB0280.cp

//## Module: cDatasetDirectory%412062FB0280; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cDatasetDirectory.h

#ifndef cDatasetDirectory_h
#define cDatasetDirectory_h 1

//## begin module%412062FB0280.includes preserve=yes
//## end module%412062FB0280.includes


class __DLL_EXPORT__ cDataset;

//## begin module%412062FB0280.additionalDeclarations preserve=yes
//## end module%412062FB0280.additionalDeclarations


//## begin cDatasetDirectory%412062FB0280.preface preserve=yes
//## end cDatasetDirectory%412062FB0280.preface

//## Class: cDatasetDirectory%412062FB0280
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cDatasetDirectory 
{
  //## begin cDatasetDirectory%412062FB0280.initialDeclarations preserve=yes
public:
  //## end cDatasetDirectory%412062FB0280.initialDeclarations

    //## Constructors (generated)
      cDatasetDirectory();

      cDatasetDirectory(const cDatasetDirectory &right);

    //## Constructors (specified)
      //## Operation: cDatasetDirectory%1092642065
      cDatasetDirectory (CONST_STRING_T path, CONST_STRING_T pattern);

    //## Destructor (generated)
      virtual ~cDatasetDirectory();


    //## Other Operations (specified)
      //## Operation: NewFileName%1092642066
      virtual CONST_STRING_T NewFileName ();

  public:
    // Additional Public Declarations
      //## begin cDatasetDirectory%412062FB0280.public preserve=yes
      //## end cDatasetDirectory%412062FB0280.public

  protected:
    // Data Members for Associations

      //## Association: System::Structs::<unnamed>%41206387036B
      //## Role: cDatasetDirectory::Datasets%412063880251
      //## Qualifier: name%412063CD001F; STRING_T
      //## begin cDatasetDirectory::Datasets%412063880251.role preserve=no  public: cDataset {1 -> 0..nRFHN}
      std::map<STRING_T, cDataset*> _Datasets;
      //## end cDatasetDirectory::Datasets%412063880251.role

    // Additional Protected Declarations
      //## begin cDatasetDirectory%412062FB0280.protected preserve=yes
      //## end cDatasetDirectory%412062FB0280.protected

  private:
    // Additional Private Declarations
      //## begin cDatasetDirectory%412062FB0280.private preserve=yes
      //## end cDatasetDirectory%412062FB0280.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Path%4120644D01C5
      //## begin cDatasetDirectory::Path%4120644D01C5.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Path;
      //## end cDatasetDirectory::Path%4120644D01C5.attr

      //## Attribute: Pattern%4120646D0213
      //## begin cDatasetDirectory::Pattern%4120646D0213.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Pattern;
      //## end cDatasetDirectory::Pattern%4120646D0213.attr

    // Additional Implementation Declarations
      //## begin cDatasetDirectory%412062FB0280.implementation preserve=yes
      //## end cDatasetDirectory%412062FB0280.implementation

};

//## begin cDatasetDirectory%412062FB0280.postscript preserve=yes
//## end cDatasetDirectory%412062FB0280.postscript

// Class cDatasetDirectory 

//## begin module%412062FB0280.epilog preserve=yes
//## end module%412062FB0280.epilog


#endif
