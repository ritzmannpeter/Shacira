//## begin module%43A6945802B8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A6945802B8.cm

//## begin module%43A6945802B8.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A6945802B8.cp

//## Module: cTimeCondition%43A6945802B8; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cTimeCondition.h

#ifndef cTimeCondition_h
#define cTimeCondition_h 1

//## begin module%43A6945802B8.includes preserve=yes
//## end module%43A6945802B8.includes

// cCondition
#include "Control/Device/EM63/cCondition.h"
//## begin module%43A6945802B8.additionalDeclarations preserve=yes
//## end module%43A6945802B8.additionalDeclarations


//## begin cTimeCondition%43A6945802B8.preface preserve=yes
//## end cTimeCondition%43A6945802B8.preface

//## Class: cTimeCondition%43A6945802B8
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cTimeCondition : public cCondition  //## Inherits: <unnamed>%43A694DF0151
{
  //## begin cTimeCondition%43A6945802B8.initialDeclarations preserve=yes
public:
  //## end cTimeCondition%43A6945802B8.initialDeclarations

    //## Constructors (generated)
      cTimeCondition();

      cTimeCondition(const cTimeCondition &right);

    //## Constructors (specified)
      //## Operation: cTimeCondition%1134980240
      cTimeCondition (int rel_op, int time);

    //## Destructor (generated)
      virtual ~cTimeCondition();


    //## Other Operations (specified)
      //## Operation: Condition%1134980241
      virtual BOOL_T Condition ();

  public:
    // Additional Public Declarations
      //## begin cTimeCondition%43A6945802B8.public preserve=yes
      //## end cTimeCondition%43A6945802B8.public

  protected:
    // Additional Protected Declarations
      //## begin cTimeCondition%43A6945802B8.protected preserve=yes
      //## end cTimeCondition%43A6945802B8.protected

  private:
    // Additional Private Declarations
      //## begin cTimeCondition%43A6945802B8.private preserve=yes
      //## end cTimeCondition%43A6945802B8.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: RelOp%43A699D500AB
      //## begin cTimeCondition::RelOp%43A699D500AB.attr preserve=no  implementation: int {U} EM63_GT
      int _RelOp;
      //## end cTimeCondition::RelOp%43A699D500AB.attr

      //## Attribute: Time%43A6969102B8
      //## begin cTimeCondition::Time%43A6969102B8.attr preserve=no  implementation: cTimeObject {U} 
      cTimeObject _Time;
      //## end cTimeCondition::Time%43A6969102B8.attr

    // Additional Implementation Declarations
      //## begin cTimeCondition%43A6945802B8.implementation preserve=yes
      //## end cTimeCondition%43A6945802B8.implementation

};

//## begin cTimeCondition%43A6945802B8.postscript preserve=yes
//## end cTimeCondition%43A6945802B8.postscript

// Class cTimeCondition 

//## begin module%43A6945802B8.epilog preserve=yes
//## end module%43A6945802B8.epilog


#endif
