//## begin module%43A694350009.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A694350009.cm

//## begin module%43A694350009.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A694350009.cp

//## Module: cCondition%43A694350009; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cCondition.h

#ifndef cCondition_h
#define cCondition_h 1

//## begin module%43A694350009.includes preserve=yes
//## end module%43A694350009.includes

// cTimeObject
#include "System/cTimeObject.h"
// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"

class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;

//## begin module%43A694350009.additionalDeclarations preserve=yes

#define EM63_UNDEFINED_CONDITION    0
#define EM63_TIME_CONDITION         1
#define EM63_PARAM_CONDITION        2
#define EM63_INTERVAL_CONDITION     3

//## end module%43A694350009.additionalDeclarations


//## begin cCondition%43A694350009.preface preserve=yes
//## end cCondition%43A694350009.preface

//## Class: cCondition%43A694350009
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A696B601DC;cTimeObject { -> }
//## Uses: <unnamed>%43A697F701C9;cPresentationCmd { -> }

class __DLL_EXPORT__ cCondition 
{
  //## begin cCondition%43A694350009.initialDeclarations preserve=yes
public:
  //## end cCondition%43A694350009.initialDeclarations

    //## Constructors (generated)
      cCondition();

      cCondition(const cCondition &right);

    //## Destructor (generated)
      virtual ~cCondition();


    //## Other Operations (specified)
      //## Operation: Eval%1134992989
      BOOL_T Eval ();

      //## Operation: Condition%1134980242
      virtual BOOL_T Condition () = 0;

      //## Operation: Process%1134992977
      virtual BOOL_T Process (cContext *context);

      //## Operation: SetLogOp%1134992987
      virtual void SetLogOp (int log_op);

  public:
    // Additional Public Declarations
      //## begin cCondition%43A694350009.public preserve=yes
      //## end cCondition%43A694350009.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: LogOp%43A6986902B2
      //## begin cCondition::LogOp%43A6986902B2.attr preserve=no  protected: int {U} EM63_ID
      int _LogOp;
      //## end cCondition::LogOp%43A6986902B2.attr

    // Data Members for Associations

      //## Association: Control::Device::EM63::<unnamed>%43A6A3450268
      //## Role: cCondition::Context%43A6A346012F
      //## begin cCondition::Context%43A6A346012F.role preserve=no  public: cContext { -> 0..1RFHN}
      cContext *_Context;
      //## end cCondition::Context%43A6A346012F.role

      //## Association: Control::Device::EM63::<unnamed>%43A6A37E0287
      //## Role: cCondition::VarRef%43A6A37F0277
      //## begin cCondition::VarRef%43A6A37F0277.role preserve=no  public: cVarRef { -> 0..1RFHN}
      cVarRef *_VarRef;
      //## end cCondition::VarRef%43A6A37F0277.role

    // Additional Protected Declarations
      //## begin cCondition%43A694350009.protected preserve=yes
      //## end cCondition%43A694350009.protected

  private:
    // Additional Private Declarations
      //## begin cCondition%43A694350009.private preserve=yes
      //## end cCondition%43A694350009.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ConditionType%43A6954B0103
      //## begin cCondition::ConditionType%43A6954B0103.attr preserve=no  implementation: int {U} EM63_UNDEFINED_CONDITION
      int _ConditionType;
      //## end cCondition::ConditionType%43A6954B0103.attr

    // Additional Implementation Declarations
      //## begin cCondition%43A694350009.implementation preserve=yes
      //## end cCondition%43A694350009.implementation

};

//## begin cCondition%43A694350009.postscript preserve=yes
//## end cCondition%43A694350009.postscript

// Class cCondition 

//## begin module%43A694350009.epilog preserve=yes
//## end module%43A694350009.epilog


#endif
