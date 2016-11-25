//## begin module%3E846A7A00BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E846A7A00BB.cm

//## begin module%3E846A7A00BB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E846A7A00BB.cp

//## Module: cNodeObject%3E846A7A00BB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNodeObject.h

#ifndef cNodeObject_h
#define cNodeObject_h 1

//## begin module%3E846A7A00BB.includes preserve=yes
//## end module%3E846A7A00BB.includes


class __DLL_EXPORT__ cTree;

//## begin module%3E846A7A00BB.additionalDeclarations preserve=yes
//## end module%3E846A7A00BB.additionalDeclarations


//## begin cNodeObject%3E846A7A00BB.preface preserve=yes
//## end cNodeObject%3E846A7A00BB.preface

//## Class: cNodeObject%3E846A7A00BB
//## Category: System::Namespace%3DFF203A0098
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cNodeObject 
{
  //## begin cNodeObject%3E846A7A00BB.initialDeclarations preserve=yes
public:
  //## end cNodeObject%3E846A7A00BB.initialDeclarations

    //## Constructors (generated)
      cNodeObject();

      cNodeObject(const cNodeObject &right);

    //## Destructor (generated)
      virtual ~cNodeObject();

  public:
    // Additional Public Declarations
      //## begin cNodeObject%3E846A7A00BB.public preserve=yes
      //## end cNodeObject%3E846A7A00BB.public

  protected:
    // Data Members for Associations

      //## Association: System::Namespace::<unnamed>%3E846AC5037A
      //## Role: cNodeObject::Tree%3E846AC7004F
      //## begin cNodeObject::Tree%3E846AC7004F.role preserve=no  public: cTree {0..1 -> 0..1RFHN}
      cTree *_Tree;
      //## end cNodeObject::Tree%3E846AC7004F.role

    // Additional Protected Declarations
      //## begin cNodeObject%3E846A7A00BB.protected preserve=yes
      //## end cNodeObject%3E846A7A00BB.protected

  private:
    // Additional Private Declarations
      //## begin cNodeObject%3E846A7A00BB.private preserve=yes
      //## end cNodeObject%3E846A7A00BB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cNodeObject%3E846A7A00BB.implementation preserve=yes
      //## end cNodeObject%3E846A7A00BB.implementation

};

//## begin cNodeObject%3E846A7A00BB.postscript preserve=yes
//## end cNodeObject%3E846A7A00BB.postscript

// Class cNodeObject 

//## begin module%3E846A7A00BB.epilog preserve=yes
//## end module%3E846A7A00BB.epilog


#endif
