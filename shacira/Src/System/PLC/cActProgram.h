//## begin module%3F3CC04F0109.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3CC04F0109.cm

//## begin module%3F3CC04F0109.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3CC04F0109.cp

//## Module: cActProgram%3F3CC04F0109; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cActProgram.h

#ifndef cActProgram_h
#define cActProgram_h 1

//## begin module%3F3CC04F0109.includes preserve=yes
//## end module%3F3CC04F0109.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cActProcedure;
class __DLL_EXPORT__ cControlProgram;

//## begin module%3F3CC04F0109.additionalDeclarations preserve=yes
//## end module%3F3CC04F0109.additionalDeclarations


//## begin cActProgram%3F3CC04F0109.preface preserve=yes
//## end cActProgram%3F3CC04F0109.preface

//## Class: cActProgram%3F3CC04F0109
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cActProgram 
{
  //## begin cActProgram%3F3CC04F0109.initialDeclarations preserve=yes
public:
  //## end cActProgram%3F3CC04F0109.initialDeclarations

    //## Constructors (generated)
      cActProgram();

      cActProgram(const cActProgram &right);

    //## Constructors (specified)
      //## Operation: cActProgram%1060946835
      cActProgram (cContext *context, cControlProgram *program);

    //## Destructor (generated)
      virtual ~cActProgram();


    //## Other Operations (specified)
      //## Operation: Context%1060946836
      cContext * Context ();

      //## Operation: Program%1060960059
      cControlProgram * Program ();

  public:
    // Additional Public Declarations
      //## begin cActProgram%3F3CC04F0109.public preserve=yes
      //## end cActProgram%3F3CC04F0109.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F3CC26B032C
      //## Role: cActProgram::Program%3F3CC26C02CE
      //## begin cActProgram::Program%3F3CC26C02CE.role preserve=no  public: cControlProgram { -> 1RFHN}
      cControlProgram *_Program;
      //## end cActProgram::Program%3F3CC26C02CE.role

      //## Association: System::PLC::<unnamed>%3F3CC1240399
      //## Role: cActProgram::ActProcedure%3F3CC12502FD
      //## begin cActProgram::ActProcedure%3F3CC12502FD.role preserve=no  public: cActProcedure {1 -> 0..1RFHN}
      cActProcedure *_ActProcedure;
      //## end cActProgram::ActProcedure%3F3CC12502FD.role

      //## Association: System::PLC::<unnamed>%3F3CC09002CE
      //## Role: cActProgram::Context%3F3CC09102AF
      //## begin cActProgram::Context%3F3CC09102AF.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cActProgram::Context%3F3CC09102AF.role

    // Additional Protected Declarations
      //## begin cActProgram%3F3CC04F0109.protected preserve=yes
      //## end cActProgram%3F3CC04F0109.protected

  private:
    // Additional Private Declarations
      //## begin cActProgram%3F3CC04F0109.private preserve=yes
      //## end cActProgram%3F3CC04F0109.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cActProgram%3F3CC04F0109.implementation preserve=yes
      //## end cActProgram%3F3CC04F0109.implementation

};

//## begin cActProgram%3F3CC04F0109.postscript preserve=yes
//## end cActProgram%3F3CC04F0109.postscript

// Class cActProgram 

//## begin module%3F3CC04F0109.epilog preserve=yes
//## end module%3F3CC04F0109.epilog


#endif
