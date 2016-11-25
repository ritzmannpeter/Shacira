//## begin module%43A694880122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A694880122.cm

//## begin module%43A694880122.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A694880122.cp

//## Module: cParamCondition%43A694880122; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cParamCondition.h

#ifndef cParamCondition_h
#define cParamCondition_h 1

//## begin module%43A694880122.includes preserve=yes
//## end module%43A694880122.includes

// cCondition
#include "Control/Device/EM63/cCondition.h"

class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;

//## begin module%43A694880122.additionalDeclarations preserve=yes
//## end module%43A694880122.additionalDeclarations


//## begin cParamCondition%43A694880122.preface preserve=yes
//## end cParamCondition%43A694880122.preface

//## Class: cParamCondition%43A694880122
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A6A57D013E;cContext { -> F}
//## Uses: <unnamed>%43A6A58600D1;cVarRef { -> F}

class __DLL_EXPORT__ cParamCondition : public cCondition  //## Inherits: <unnamed>%43A694E200C4
{
  //## begin cParamCondition%43A694880122.initialDeclarations preserve=yes
public:
  //## end cParamCondition%43A694880122.initialDeclarations

    //## Constructors (generated)
      cParamCondition();

      cParamCondition(const cParamCondition &right);

    //## Constructors (specified)
      //## Operation: cParamCondition%1134980246
      cParamCondition (CONST_STRING_T param_id, int rel_op, CONST_STRING_T value);

      //## Operation: cParamCondition%1135258640
      cParamCondition (CONST_STRING_T param_id, int cond_type);

    //## Destructor (generated)
      virtual ~cParamCondition();


    //## Other Operations (specified)
      //## Operation: Condition%1134980244
      virtual BOOL_T Condition ();

      //## Operation: Process%1134992978
      virtual BOOL_T Process (cContext *context);

  public:
    // Additional Public Declarations
      //## begin cParamCondition%43A694880122.public preserve=yes
      //## end cParamCondition%43A694880122.public

  protected:
    // Additional Protected Declarations
      //## begin cParamCondition%43A694880122.protected preserve=yes
      //## end cParamCondition%43A694880122.protected

  private:
    // Additional Private Declarations
      //## begin cParamCondition%43A694880122.private preserve=yes
      //## end cParamCondition%43A694880122.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: RefreshValue%1134992976
      void RefreshValue ();

    // Data Members for Class Attributes

      //## Attribute: ParamId%43A696F200A3
      //## begin cParamCondition::ParamId%43A696F200A3.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ParamId;
      //## end cParamCondition::ParamId%43A696F200A3.attr

      //## Attribute: RelOp%43A6976C017C
      //## begin cParamCondition::RelOp%43A6976C017C.attr preserve=no  implementation: int {U} EM63_EQ
      int _RelOp;
      //## end cParamCondition::RelOp%43A6976C017C.attr

      //## Attribute: CmpValue%43A69906032D
      //## begin cParamCondition::CmpValue%43A69906032D.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _CmpValue;
      //## end cParamCondition::CmpValue%43A69906032D.attr

      //## Attribute: PrevValue%43A6971A01AC
      //## begin cParamCondition::PrevValue%43A6971A01AC.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _PrevValue;
      //## end cParamCondition::PrevValue%43A6971A01AC.attr

      //## Attribute: ActValue%43A6972D02D5
      //## begin cParamCondition::ActValue%43A6972D02D5.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ActValue;
      //## end cParamCondition::ActValue%43A6972D02D5.attr

      //## Attribute: ConditionType%43AAAF360265
      //## begin cParamCondition::ConditionType%43AAAF360265.attr preserve=no  implementation: int {U} EM63_CYCLE
      int _ConditionType;
      //## end cParamCondition::ConditionType%43AAAF360265.attr

    // Additional Implementation Declarations
      //## begin cParamCondition%43A694880122.implementation preserve=yes
      //## end cParamCondition%43A694880122.implementation

};

//## begin cParamCondition%43A694880122.postscript preserve=yes
//## end cParamCondition%43A694880122.postscript

// Class cParamCondition 

//## begin module%43A694880122.epilog preserve=yes
//## end module%43A694880122.epilog


#endif
