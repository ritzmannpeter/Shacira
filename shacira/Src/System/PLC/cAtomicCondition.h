//## begin module%3F38E3390222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38E3390222.cm

//## begin module%3F38E3390222.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38E3390222.cp

//## Module: cAtomicCondition%3F38E3390222; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cAtomicCondition.h

#ifndef cAtomicCondition_h
#define cAtomicCondition_h 1

//## begin module%3F38E3390222.includes preserve=yes
//## end module%3F38E3390222.includes


class __DLL_EXPORT__ cArgument;

//## begin module%3F38E3390222.additionalDeclarations preserve=yes

typedef enum {RELOP_UNDEF=0, RELOP_LT, RELOP_LE,  RELOP_GT, RELOP_GE, RELOP_EQ, RELOP_NE} RelOps;

//## end module%3F38E3390222.additionalDeclarations


//## begin cAtomicCondition%3F38E3390222.preface preserve=yes
//## end cAtomicCondition%3F38E3390222.preface

//## Class: cAtomicCondition%3F38E3390222
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cAtomicCondition 
{
  //## begin cAtomicCondition%3F38E3390222.initialDeclarations preserve=yes
public:
  //## end cAtomicCondition%3F38E3390222.initialDeclarations

    //## Constructors (generated)
      cAtomicCondition();

      cAtomicCondition(const cAtomicCondition &right);

    //## Constructors (specified)
      //## Operation: cAtomicCondition%1060691306
      cAtomicCondition (cArgument *argument1, RelOps rel_op, cArgument *argument2);

    //## Destructor (generated)
      virtual ~cAtomicCondition();


    //## Other Operations (specified)
      //## Operation: Eval%1060691309
      BOOL_T Eval ();

  public:
    // Additional Public Declarations
      //## begin cAtomicCondition%3F38E3390222.public preserve=yes
      //## end cAtomicCondition%3F38E3390222.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F38E8EA03A9
      //## Role: cAtomicCondition::Argument2%3F38E8EB030D
      //## begin cAtomicCondition::Argument2%3F38E8EB030D.role preserve=no  public: cArgument { -> 1RFHN}
      cArgument *_Argument2;
      //## end cAtomicCondition::Argument2%3F38E8EB030D.role

      //## Association: System::PLC::<unnamed>%3F49C3940242
      //## Role: cAtomicCondition::Argument1%3F49C3950290
      //## begin cAtomicCondition::Argument1%3F49C3950290.role preserve=no  public: cArgument { -> 1RFHN}
      cArgument *_Argument1;
      //## end cAtomicCondition::Argument1%3F49C3950290.role

    // Additional Protected Declarations
      //## begin cAtomicCondition%3F38E3390222.protected preserve=yes
      //## end cAtomicCondition%3F38E3390222.protected

  private:
    // Additional Private Declarations
      //## begin cAtomicCondition%3F38E3390222.private preserve=yes
      //## end cAtomicCondition%3F38E3390222.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: RelOp%3F38E98300EA
      //## begin cAtomicCondition::RelOp%3F38E98300EA.attr preserve=no  implementation: RelOps {U} RELOP_UNDEF
      RelOps _RelOp;
      //## end cAtomicCondition::RelOp%3F38E98300EA.attr

    // Additional Implementation Declarations
      //## begin cAtomicCondition%3F38E3390222.implementation preserve=yes
      //## end cAtomicCondition%3F38E3390222.implementation

};

//## begin cAtomicCondition%3F38E3390222.postscript preserve=yes
//## end cAtomicCondition%3F38E3390222.postscript

// Class cAtomicCondition 

//## begin module%3F38E3390222.epilog preserve=yes
//## end module%3F38E3390222.epilog


#endif
