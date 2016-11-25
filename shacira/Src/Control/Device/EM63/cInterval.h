//## begin module%43A694AB0122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A694AB0122.cm

//## begin module%43A694AB0122.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A694AB0122.cp

//## Module: cInterval%43A694AB0122; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cInterval.h

#ifndef cInterval_h
#define cInterval_h 1

//## begin module%43A694AB0122.includes preserve=yes
//## end module%43A694AB0122.includes

// cCondition
#include "Control/Device/EM63/cCondition.h"
//## begin module%43A694AB0122.additionalDeclarations preserve=yes
//## end module%43A694AB0122.additionalDeclarations


//## begin cInterval%43A694AB0122.preface preserve=yes
//## end cInterval%43A694AB0122.preface

//## Class: cInterval%43A694AB0122
//## Category: Control::Device::EM63%43807DD301F2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cInterval : public cCondition  //## Inherits: <unnamed>%43A694E50112
{
  //## begin cInterval%43A694AB0122.initialDeclarations preserve=yes
public:
  //## end cInterval%43A694AB0122.initialDeclarations

    //## Constructors (generated)
      cInterval();

      cInterval(const cInterval &right);

    //## Constructors (specified)
      //## Operation: cInterval%1134980245
      cInterval (int interval);

      //## Operation: cInterval%1134980248
      cInterval (int hours, int minutes, int seconds);

    //## Destructor (generated)
      virtual ~cInterval();


    //## Other Operations (specified)
      //## Operation: Condition%1134980243
      virtual BOOL_T Condition ();

  public:
    // Additional Public Declarations
      //## begin cInterval%43A694AB0122.public preserve=yes
      //## end cInterval%43A694AB0122.public

  protected:
    // Additional Protected Declarations
      //## begin cInterval%43A694AB0122.protected preserve=yes
      //## end cInterval%43A694AB0122.protected

  private:
    // Additional Private Declarations
      //## begin cInterval%43A694AB0122.private preserve=yes
      //## end cInterval%43A694AB0122.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Interval%43A69B39035D
      //## begin cInterval::Interval%43A69B39035D.attr preserve=no  implementation: int {U} 0
      int _Interval;
      //## end cInterval::Interval%43A69B39035D.attr

      //## Attribute: Remaining%43A69B5C017A
      //## begin cInterval::Remaining%43A69B5C017A.attr preserve=no  implementation: int {U} 0
      int _Remaining;
      //## end cInterval::Remaining%43A69B5C017A.attr

      //## Attribute: LastCheck%43A97D1301B1
      //## begin cInterval::LastCheck%43A97D1301B1.attr preserve=no  implementation: int {U} 0
      int _LastCheck;
      //## end cInterval::LastCheck%43A97D1301B1.attr

    // Additional Implementation Declarations
      //## begin cInterval%43A694AB0122.implementation preserve=yes
      //## end cInterval%43A694AB0122.implementation

};

//## begin cInterval%43A694AB0122.postscript preserve=yes
//## end cInterval%43A694AB0122.postscript

// Class cInterval 

//## begin module%43A694AB0122.epilog preserve=yes
//## end module%43A694AB0122.epilog


#endif
