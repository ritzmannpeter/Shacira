//## begin module%43A6B4F80119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A6B4F80119.cm

//## begin module%43A6B4F80119.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A6B4F80119.cp

//## Module: cCyclicCondition%43A6B4F80119; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cCyclicCondition.h

#ifndef cCyclicCondition_h
#define cCyclicCondition_h 1

//## begin module%43A6B4F80119.includes preserve=yes
//## end module%43A6B4F80119.includes

// cCondition
#include "Control/Device/EM63/cCondition.h"

class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;

//## begin module%43A6B4F80119.additionalDeclarations preserve=yes
//## end module%43A6B4F80119.additionalDeclarations


//## begin cCyclicCondition%43A6B4F80119.preface preserve=yes
//## end cCyclicCondition%43A6B4F80119.preface

//## Class: cCyclicCondition%43A6B4F80119
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%43A6D23203DF;cContext { -> F}
//## Uses: <unnamed>%43A6D5BE02C8;cVarRef { -> F}

class __DLL_EXPORT__ cCyclicCondition : public cCondition  //## Inherits: <unnamed>%43A6B521034C
{
  //## begin cCyclicCondition%43A6B4F80119.initialDeclarations preserve=yes
public:
  //## end cCyclicCondition%43A6B4F80119.initialDeclarations

    //## Constructors (generated)
      cCyclicCondition();

      cCyclicCondition(const cCyclicCondition &right);

    //## Constructors (specified)
      //## Operation: cCyclicCondition%1134992985
      cCyclicCondition (int shot, CONST_STRING_T shot_param_id);

    //## Destructor (generated)
      virtual ~cCyclicCondition();


    //## Other Operations (specified)
      //## Operation: Condition%1134992983
      virtual BOOL_T Condition ();

      //## Operation: Process%1134992984
      virtual BOOL_T Process (cContext *context);

  public:
    // Additional Public Declarations
      //## begin cCyclicCondition%43A6B4F80119.public preserve=yes
      //## end cCyclicCondition%43A6B4F80119.public

  protected:
    // Additional Protected Declarations
      //## begin cCyclicCondition%43A6B4F80119.protected preserve=yes
      //## end cCyclicCondition%43A6B4F80119.protected

  private:
    // Additional Private Declarations
      //## begin cCyclicCondition%43A6B4F80119.private preserve=yes
      //## end cCyclicCondition%43A6B4F80119.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: RefreshShot%1134992995
      void RefreshShot ();

    // Data Members for Class Attributes

      //## Attribute: ShotParamId%43AABCF702FD
      //## begin cCyclicCondition::ShotParamId%43AABCF702FD.attr preserve=no  implementation: STRING_T {U} "ActCntMachAdd"
      STRING_T _ShotParamId;
      //## end cCyclicCondition::ShotParamId%43AABCF702FD.attr

      //## Attribute: Shot%43A6B8B8038A
      //## begin cCyclicCondition::Shot%43A6B8B8038A.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _Shot;
      //## end cCyclicCondition::Shot%43A6B8B8038A.attr

      //## Attribute: ActShot%43A6D31D0131
      //## begin cCyclicCondition::ActShot%43A6D31D0131.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _ActShot;
      //## end cCyclicCondition::ActShot%43A6D31D0131.attr

      //## Attribute: PrevShot%43A6D330024A
      //## begin cCyclicCondition::PrevShot%43A6D330024A.attr preserve=no  implementation: LONG_T {U} 0
      LONG_T _PrevShot;
      //## end cCyclicCondition::PrevShot%43A6D330024A.attr

    // Additional Implementation Declarations
      //## begin cCyclicCondition%43A6B4F80119.implementation preserve=yes
      //## end cCyclicCondition%43A6B4F80119.implementation

};

//## begin cCyclicCondition%43A6B4F80119.postscript preserve=yes
//## end cCyclicCondition%43A6B4F80119.postscript

// Class cCyclicCondition 

//## begin module%43A6B4F80119.epilog preserve=yes
//## end module%43A6B4F80119.epilog


#endif
