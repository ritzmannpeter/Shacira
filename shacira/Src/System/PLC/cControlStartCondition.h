//## begin module%3F38BC3A0232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BC3A0232.cm

//## begin module%3F38BC3A0232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BC3A0232.cp

//## Module: cControlStartCondition%3F38BC3A0232; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlStartCondition.h

#ifndef cControlStartCondition_h
#define cControlStartCondition_h 1

//## begin module%3F38BC3A0232.includes preserve=yes
//## end module%3F38BC3A0232.includes


class __DLL_EXPORT__ cContext;

//## begin module%3F38BC3A0232.additionalDeclarations preserve=yes
//## end module%3F38BC3A0232.additionalDeclarations


//## begin cControlStartCondition%3F38BC3A0232.preface preserve=yes
//## end cControlStartCondition%3F38BC3A0232.preface

//## Class: cControlStartCondition%3F38BC3A0232
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F38BCB00138;cContext { -> F}

class __DLL_EXPORT__ cControlStartCondition 
{
  //## begin cControlStartCondition%3F38BC3A0232.initialDeclarations preserve=yes
public:
  //## end cControlStartCondition%3F38BC3A0232.initialDeclarations

    //## Constructors (generated)
      cControlStartCondition();

      cControlStartCondition(const cControlStartCondition &right);

    //## Destructor (generated)
      virtual ~cControlStartCondition();

    // Data Members for Class Attributes

      //## Attribute: ConditionName%3F38C20F00AB
      //## begin cControlStartCondition::ConditionName%3F38C20F00AB.attr preserve=no  public: STRING_T {U} 
      STRING_T _ConditionName;
      //## end cControlStartCondition::ConditionName%3F38C20F00AB.attr

  public:
    // Additional Public Declarations
      //## begin cControlStartCondition%3F38BC3A0232.public preserve=yes
      //## end cControlStartCondition%3F38BC3A0232.public

  protected:
    // Additional Protected Declarations
      //## begin cControlStartCondition%3F38BC3A0232.protected preserve=yes
      //## end cControlStartCondition%3F38BC3A0232.protected

  private:
    // Additional Private Declarations
      //## begin cControlStartCondition%3F38BC3A0232.private preserve=yes
      //## end cControlStartCondition%3F38BC3A0232.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cControlStartCondition%3F38BC3A0232.implementation preserve=yes
      //## end cControlStartCondition%3F38BC3A0232.implementation

};

//## begin cControlStartCondition%3F38BC3A0232.postscript preserve=yes
//## end cControlStartCondition%3F38BC3A0232.postscript

// Class cControlStartCondition 

//## begin module%3F38BC3A0232.epilog preserve=yes
//## end module%3F38BC3A0232.epilog


#endif
