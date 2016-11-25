//## begin module%4167FEE2030D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4167FEE2030D.cm

//## begin module%4167FEE2030D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4167FEE2030D.cp

//## Module: cContextChooser%4167FEE2030D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\Interface\cContextChooser.h

#ifndef cContextChooser_h
#define cContextChooser_h 1

//## begin module%4167FEE2030D.includes preserve=yes
//## end module%4167FEE2030D.includes


class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cContext;

//## begin module%4167FEE2030D.additionalDeclarations preserve=yes
//## end module%4167FEE2030D.additionalDeclarations


//## begin cContextChooser%4167FEE2030D.preface preserve=yes
//## end cContextChooser%4167FEE2030D.preface

//## Class: cContextChooser%4167FEE2030D
//## Category: GUIFramework::Interface%4005268A008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4167FFAD03C8;cContext { -> F}

class __DLL_EXPORT__ cContextChooser 
{
  //## begin cContextChooser%4167FEE2030D.initialDeclarations preserve=yes
public:
  //## end cContextChooser%4167FEE2030D.initialDeclarations

    //## Constructors (generated)
      cContextChooser();

      cContextChooser(const cContextChooser &right);

    //## Destructor (generated)
      virtual ~cContextChooser();


    //## Other Operations (specified)
      //## Operation: SetProcess%1097333010
      void SetProcess (cSHProcess *process);

      //## Operation: GetContext%1097333008
      virtual cContext * GetContext ();

  public:
    // Additional Public Declarations
      //## begin cContextChooser%4167FEE2030D.public preserve=yes
      //## end cContextChooser%4167FEE2030D.public

  protected:
    // Data Members for Associations

      //## Association: GUIFramework::Interface::<unnamed>%4168005C02AF
      //## Role: cContextChooser::Process%4168005D033C
      //## begin cContextChooser::Process%4168005D033C.role preserve=no  public: cSHProcess { -> 1RFHN}
      cSHProcess *_Process;
      //## end cContextChooser::Process%4168005D033C.role

    // Additional Protected Declarations
      //## begin cContextChooser%4167FEE2030D.protected preserve=yes
      //## end cContextChooser%4167FEE2030D.protected

  private:
    // Additional Private Declarations
      //## begin cContextChooser%4167FEE2030D.private preserve=yes
      //## end cContextChooser%4167FEE2030D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cContextChooser%4167FEE2030D.implementation preserve=yes
      //## end cContextChooser%4167FEE2030D.implementation

};

//## begin cContextChooser%4167FEE2030D.postscript preserve=yes
//## end cContextChooser%4167FEE2030D.postscript

// Class cContextChooser 

//## begin module%4167FEE2030D.epilog preserve=yes
//## end module%4167FEE2030D.epilog


#endif
