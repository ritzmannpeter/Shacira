//## begin module%3E154E8A0100.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E154E8A0100.cm

//## begin module%3E154E8A0100.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3E154E8A0100.cp

//## Module: cProgramFactory%3E154E8A0100; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cProgramFactory.h

#ifndef cProgramFactory_h
#define cProgramFactory_h 1

//## begin module%3E154E8A0100.includes preserve=yes
//## end module%3E154E8A0100.includes


class cUSSProgram;
class cStandardProgram;
class cAirbagProgram;
class cProgram;

//## begin module%3E154E8A0100.additionalDeclarations preserve=yes
//## end module%3E154E8A0100.additionalDeclarations


//## begin cProgramFactory%3E154E8A0100.preface preserve=yes
//## end cProgramFactory%3E154E8A0100.preface

//## Class: cProgramFactory%3E154E8A0100
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E154F550365;cStandardProgram { -> F}
//## Uses: <unnamed>%3E154F63009E;cAirbagProgram { -> F}
//## Uses: <unnamed>%3E154F6C0227;cUSSProgram { -> F}
//## Uses: <unnamed>%3E154F9E00FD;cProgram { -> F}

class cProgramFactory 
{
  //## begin cProgramFactory%3E154E8A0100.initialDeclarations preserve=yes
  //## end cProgramFactory%3E154E8A0100.initialDeclarations

  public:
    //## Constructors (generated)
      cProgramFactory();

      cProgramFactory(const cProgramFactory &right);

    //## Destructor (generated)
      virtual ~cProgramFactory();


    //## Other Operations (specified)
      //## Operation: TypeCode%1041583344
      static INT_T TypeCode (CONST_STRING_T type_name);

      //## Operation: TypeName%1041583345
      static CONST_STRING_T TypeName (INT_T type_code);

      //## Operation: CreateProgram%1041583346
      static cProgram * CreateProgram (cConfigurationObject *config_obj, cCell *cell);

    // Additional Public Declarations
      //## begin cProgramFactory%3E154E8A0100.public preserve=yes
      //## end cProgramFactory%3E154E8A0100.public

  protected:
    // Additional Protected Declarations
      //## begin cProgramFactory%3E154E8A0100.protected preserve=yes
      //## end cProgramFactory%3E154E8A0100.protected

  private:
    // Additional Private Declarations
      //## begin cProgramFactory%3E154E8A0100.private preserve=yes
      //## end cProgramFactory%3E154E8A0100.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cProgramFactory%3E154E8A0100.implementation preserve=yes
      //## end cProgramFactory%3E154E8A0100.implementation

};

//## begin cProgramFactory%3E154E8A0100.postscript preserve=yes
//## end cProgramFactory%3E154E8A0100.postscript

// Class cProgramFactory 

//## begin module%3E154E8A0100.epilog preserve=yes
//## end module%3E154E8A0100.epilog


#endif
