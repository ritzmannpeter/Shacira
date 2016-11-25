//## begin module%3E8469730242.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E8469730242.cm

//## begin module%3E8469730242.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E8469730242.cp

//## Module: cNodeContext%3E8469730242; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Namespace\cNodeContext.h

#ifndef cNodeContext_h
#define cNodeContext_h 1

//## begin module%3E8469730242.includes preserve=yes
//## end module%3E8469730242.includes


class __DLL_EXPORT__ cTree;

//## begin module%3E8469730242.additionalDeclarations preserve=yes
//## end module%3E8469730242.additionalDeclarations


//## begin cNodeContext%3E8469730242.preface preserve=yes
//## end cNodeContext%3E8469730242.preface

//## Class: cNodeContext%3E8469730242
//## Category: System::Namespace%3DFF203A0098
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cNodeContext 
{
  //## begin cNodeContext%3E8469730242.initialDeclarations preserve=yes
public:
  //## end cNodeContext%3E8469730242.initialDeclarations

    //## Constructors (generated)
      cNodeContext();

      cNodeContext(const cNodeContext &right);

    //## Destructor (generated)
      virtual ~cNodeContext();

  public:
    // Additional Public Declarations
      //## begin cNodeContext%3E8469730242.public preserve=yes
      //## end cNodeContext%3E8469730242.public

  protected:
    // Data Members for Associations

      //## Association: System::Namespace::<unnamed>%3E846AC901D4
      //## Role: cNodeContext::Tree%3E846ACA01B5
      //## begin cNodeContext::Tree%3E846ACA01B5.role preserve=no  public: cTree {0..1 -> 0..1RFHN}
      cTree *_Tree;
      //## end cNodeContext::Tree%3E846ACA01B5.role

    // Additional Protected Declarations
      //## begin cNodeContext%3E8469730242.protected preserve=yes
      //## end cNodeContext%3E8469730242.protected

  private:
    // Additional Private Declarations
      //## begin cNodeContext%3E8469730242.private preserve=yes
      //## end cNodeContext%3E8469730242.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cNodeContext%3E8469730242.implementation preserve=yes
      //## end cNodeContext%3E8469730242.implementation

};

//## begin cNodeContext%3E8469730242.postscript preserve=yes
//## end cNodeContext%3E8469730242.postscript

// Class cNodeContext 

//## begin module%3E8469730242.epilog preserve=yes
//## end module%3E8469730242.epilog


#endif
