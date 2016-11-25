//## begin module%3F38BB7C03B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BB7C03B9.cm

//## begin module%3F38BB7C03B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BB7C03B9.cp

//## Module: cControlState%3F38BB7C03B9; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlState.h

#ifndef cControlState_h
#define cControlState_h 1

//## begin module%3F38BB7C03B9.includes preserve=yes
//## end module%3F38BB7C03B9.includes


class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cStateVariable;
class __DLL_EXPORT__ cControlCondition;

//## begin module%3F38BB7C03B9.additionalDeclarations preserve=yes
//## end module%3F38BB7C03B9.additionalDeclarations


//## begin cControlState%3F38BB7C03B9.preface preserve=yes
//## end cControlState%3F38BB7C03B9.preface

//## Class: cControlState%3F38BB7C03B9
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F38BC9601D4;cContext { -> F}
//## Uses: <unnamed>%3F3922A600AB;cStateVariable { -> F}

class __DLL_EXPORT__ cControlState 
{
  //## begin cControlState%3F38BB7C03B9.initialDeclarations preserve=yes
public:
  //## end cControlState%3F38BB7C03B9.initialDeclarations

    //## Constructors (generated)
      cControlState();

      cControlState(const cControlState &right);

    //## Constructors (specified)
      //## Operation: cControlState%1060691300
      cControlState (CONST_STRING_T name, cControlCondition *condition);

    //## Destructor (generated)
      virtual ~cControlState();


    //## Other Operations (specified)
      //## Operation: Eval%1060691308
      BOOL_T Eval ();

      //## Operation: VarDef%1060709189
      cVarDef * VarDef ();

    // Data Members for Class Attributes

      //## Attribute: StateName%3F38C1BA01C5
      //## begin cControlState::StateName%3F38C1BA01C5.attr preserve=no  public: STRING_T {U} 
      STRING_T _StateName;
      //## end cControlState::StateName%3F38C1BA01C5.attr

  public:
    // Additional Public Declarations
      //## begin cControlState%3F38BB7C03B9.public preserve=yes
      //## end cControlState%3F38BB7C03B9.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F38F9B901E4
      //## Role: cControlState::Condition%3F38F9BA0251
      //## begin cControlState::Condition%3F38F9BA0251.role preserve=no  public: cControlCondition { -> 1RFHN}
      cControlCondition *_Condition;
      //## end cControlState::Condition%3F38F9BA0251.role

      //## Association: System::PLC::<unnamed>%3F3924B70196
      //## Role: cControlState::VarDef%3F3924B703B9
      //## begin cControlState::VarDef%3F3924B703B9.role preserve=no  public: cVarDef { -> 0..1RFHN}
      cVarDef *_VarDef;
      //## end cControlState::VarDef%3F3924B703B9.role

    // Additional Protected Declarations
      //## begin cControlState%3F38BB7C03B9.protected preserve=yes
      //## end cControlState%3F38BB7C03B9.protected

  private:
    // Additional Private Declarations
      //## begin cControlState%3F38BB7C03B9.private preserve=yes
      //## end cControlState%3F38BB7C03B9.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CreateVar%1060709215
      void CreateVar ();

    // Additional Implementation Declarations
      //## begin cControlState%3F38BB7C03B9.implementation preserve=yes
      //## end cControlState%3F38BB7C03B9.implementation

};

//## begin cControlState%3F38BB7C03B9.postscript preserve=yes
//## end cControlState%3F38BB7C03B9.postscript

// Class cControlState 

//## begin module%3F38BB7C03B9.epilog preserve=yes
//## end module%3F38BB7C03B9.epilog


#endif
