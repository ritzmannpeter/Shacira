//## begin module%3F38DCC301A5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38DCC301A5.cm

//## begin module%3F38DCC301A5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38DCC301A5.cp

//## Module: cControlCondition%3F38DCC301A5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlCondition.h

#ifndef cControlCondition_h
#define cControlCondition_h 1

//## begin module%3F38DCC301A5.includes preserve=yes
//## end module%3F38DCC301A5.includes


class __DLL_EXPORT__ cAtomicCondition;
class __DLL_EXPORT__ cControlState;

//## begin module%3F38DCC301A5.additionalDeclarations preserve=yes

typedef enum {LOGOP_UNDEF=0, LOGOP_OR, LOGOP_AND, LOGOP_NOT} LogOps;

//## end module%3F38DCC301A5.additionalDeclarations


//## begin cControlCondition%3F38DCC301A5.preface preserve=yes
//## end cControlCondition%3F38DCC301A5.preface

//## Class: cControlCondition%3F38DCC301A5
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cControlCondition 
{
  //## begin cControlCondition%3F38DCC301A5.initialDeclarations preserve=yes
public:
  //## end cControlCondition%3F38DCC301A5.initialDeclarations

    //## Constructors (generated)
      cControlCondition();

      cControlCondition(const cControlCondition &right);

    //## Constructors (specified)
      //## Operation: cControlCondition%1060691303
      cControlCondition (cAtomicCondition *atomic_condition);

      //## Operation: cControlCondition%1060691304
      cControlCondition (cControlCondition *left, cControlCondition *right, LogOps log_op);

      //## Operation: cControlCondition%1060767922
      cControlCondition (cControlCondition *cond);

      //## Operation: cControlCondition%1060691305
      cControlCondition (cControlState *state);

    //## Destructor (generated)
      virtual ~cControlCondition();


    //## Other Operations (specified)
      //## Operation: Eval%1060691310
      BOOL_T Eval ();

  public:
    // Additional Public Declarations
      //## begin cControlCondition%3F38DCC301A5.public preserve=yes
      //## end cControlCondition%3F38DCC301A5.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F38FA0B006D
      //## Role: cControlCondition::Left%3F38FA1601F4
      //## begin cControlCondition::Left%3F38FA1601F4.role preserve=no  public: cControlCondition { -> 1RFHN}
      cControlCondition *_Left;
      //## end cControlCondition::Left%3F38FA1601F4.role

      //## Association: System::PLC::<unnamed>%3F38FA490213
      //## Role: cControlCondition::Right%3F38FA5400EA
      //## begin cControlCondition::Right%3F38FA5400EA.role preserve=no  public: cControlCondition { -> 1RFHN}
      cControlCondition *_Right;
      //## end cControlCondition::Right%3F38FA5400EA.role

      //## Association: System::PLC::<unnamed>%3F38FB730000
      //## Role: cControlCondition::State%3F38FB73032C
      //## begin cControlCondition::State%3F38FB73032C.role preserve=no  public: cControlState { -> 1RFHN}
      cControlState *_State;
      //## end cControlCondition::State%3F38FB73032C.role

      //## Association: System::PLC::<unnamed>%3F38FA7D008C
      //## Role: cControlCondition::AtomicCondition%3F38FA7E01A5
      //## begin cControlCondition::AtomicCondition%3F38FA7E01A5.role preserve=no  public: cAtomicCondition { -> 1RFHN}
      cAtomicCondition *_AtomicCondition;
      //## end cControlCondition::AtomicCondition%3F38FA7E01A5.role

    // Additional Protected Declarations
      //## begin cControlCondition%3F38DCC301A5.protected preserve=yes
      //## end cControlCondition%3F38DCC301A5.protected

  private:
    // Additional Private Declarations
      //## begin cControlCondition%3F38DCC301A5.private preserve=yes
      //## end cControlCondition%3F38DCC301A5.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: LogOp%3F38FC81033C
      //## begin cControlCondition::LogOp%3F38FC81033C.attr preserve=no  implementation: LogOps {U} LOGOP_UNDEF
      LogOps _LogOp;
      //## end cControlCondition::LogOp%3F38FC81033C.attr

    // Additional Implementation Declarations
      //## begin cControlCondition%3F38DCC301A5.implementation preserve=yes
      //## end cControlCondition%3F38DCC301A5.implementation

};

//## begin cControlCondition%3F38DCC301A5.postscript preserve=yes
//## end cControlCondition%3F38DCC301A5.postscript

// Class cControlCondition 

//## begin module%3F38DCC301A5.epilog preserve=yes
//## end module%3F38DCC301A5.epilog


#endif
