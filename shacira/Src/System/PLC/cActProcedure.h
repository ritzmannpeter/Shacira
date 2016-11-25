//## begin module%3F3CC0B9001F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3CC0B9001F.cm

//## begin module%3F3CC0B9001F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3CC0B9001F.cp

//## Module: cActProcedure%3F3CC0B9001F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cActProcedure.h

#ifndef cActProcedure_h
#define cActProcedure_h 1

//## begin module%3F3CC0B9001F.includes preserve=yes
//## end module%3F3CC0B9001F.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cActProgram;
class __DLL_EXPORT__ cActLine;
class __DLL_EXPORT__ cProcedureLine;
class __DLL_EXPORT__ cControlProcedure;

//## begin module%3F3CC0B9001F.additionalDeclarations preserve=yes
//## end module%3F3CC0B9001F.additionalDeclarations


//## begin cActProcedure%3F3CC0B9001F.preface preserve=yes
//## end cActProcedure%3F3CC0B9001F.preface

//## Class: cActProcedure%3F3CC0B9001F
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F3D1CDF00BB;cProcedureLine { -> F}

class __DLL_EXPORT__ cActProcedure 
{
  //## begin cActProcedure%3F3CC0B9001F.initialDeclarations preserve=yes
public:
  //## end cActProcedure%3F3CC0B9001F.initialDeclarations

    //## Constructors (generated)
      cActProcedure();

      cActProcedure(const cActProcedure &right);

    //## Constructors (specified)
      //## Operation: cActProcedure%1060946837
      cActProcedure (cContext *context, cControlProcedure *procedure, cActProgram *act_program);

    //## Destructor (generated)
      virtual ~cActProcedure();


    //## Other Operations (specified)
      //## Operation: Context%1060946838
      cContext * Context ();

      //## Operation: Procedure%1060960058
      cControlProcedure * Procedure ();

      //## Operation: Execute%1060965459
      INT_T Execute ();

  public:
    // Additional Public Declarations
      //## begin cActProcedure%3F3CC0B9001F.public preserve=yes
      //## end cActProcedure%3F3CC0B9001F.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F3CC22B0186
      //## Role: cActProcedure::Procedure%3F3CC22C002E
      //## begin cActProcedure::Procedure%3F3CC22C002E.role preserve=no  public: cControlProcedure { -> 1RFHN}
      cControlProcedure *_Procedure;
      //## end cActProcedure::Procedure%3F3CC22C002E.role

      //## Association: System::PLC::<unnamed>%3F3CC1240399
      //## Role: cActProcedure::ActProgram%3F3CC12502FE
      //## begin cActProcedure::ActProgram%3F3CC12502FE.role preserve=no  public: cActProgram {0..1 -> 1RFHN}
      cActProgram *_ActProgram;
      //## end cActProcedure::ActProgram%3F3CC12502FE.role

      //## Association: System::PLC::<unnamed>%3F3CC18402EE
      //## Role: cActProcedure::ActLine%3F3CC186000F
      //## begin cActProcedure::ActLine%3F3CC186000F.role preserve=no  public: cActLine {1 -> 0..1RFHN}
      cActLine *_ActLine;
      //## end cActProcedure::ActLine%3F3CC186000F.role

      //## Association: System::PLC::<unnamed>%3F3CC0DB0232
      //## Role: cActProcedure::Context%3F3CC0DC0222
      //## begin cActProcedure::Context%3F3CC0DC0222.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cActProcedure::Context%3F3CC0DC0222.role

    // Additional Protected Declarations
      //## begin cActProcedure%3F3CC0B9001F.protected preserve=yes
      //## end cActProcedure%3F3CC0B9001F.protected

  private:
    // Additional Private Declarations
      //## begin cActProcedure%3F3CC0B9001F.private preserve=yes
      //## end cActProcedure%3F3CC0B9001F.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cActProcedure%3F3CC0B9001F.implementation preserve=yes
      //## end cActProcedure%3F3CC0B9001F.implementation

};

//## begin cActProcedure%3F3CC0B9001F.postscript preserve=yes
//## end cActProcedure%3F3CC0B9001F.postscript

// Class cActProcedure 

//## begin module%3F3CC0B9001F.epilog preserve=yes
//## end module%3F3CC0B9001F.epilog


#endif
