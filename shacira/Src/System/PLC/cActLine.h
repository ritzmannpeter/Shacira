//## begin module%3F3BA40902DE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3BA40902DE.cm

//## begin module%3F3BA40902DE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3BA40902DE.cp

//## Module: cActLine%3F3BA40902DE; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cActLine.h

#ifndef cActLine_h
#define cActLine_h 1

//## begin module%3F3BA40902DE.includes preserve=yes
//## end module%3F3BA40902DE.includes


class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cActProcedure;
class __DLL_EXPORT__ cProcedureLine;
class __DLL_EXPORT__ cControlCondition;

//## begin module%3F3BA40902DE.additionalDeclarations preserve=yes
//## end module%3F3BA40902DE.additionalDeclarations


//## begin cActLine%3F3BA40902DE.preface preserve=yes
//## end cActLine%3F3BA40902DE.preface

//## Class: cActLine%3F3BA40902DE
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F3D11EF02FD;cVarRef { -> F}
//## Uses: <unnamed>%3F3D121B031C;cVarDef { -> F}
//## Uses: <unnamed>%3F3D12BF0222;cControlCondition { -> F}

class __DLL_EXPORT__ cActLine 
{
  //## begin cActLine%3F3BA40902DE.initialDeclarations preserve=yes
public:
  //## end cActLine%3F3BA40902DE.initialDeclarations

    //## Constructors (generated)
      cActLine();

      cActLine(const cActLine &right);

    //## Constructors (specified)
      //## Operation: cActLine%1060849356
      cActLine (cContext *context, cProcedureLine *line, cActProcedure *act_procedure);

    //## Destructor (generated)
      virtual ~cActLine();


    //## Other Operations (specified)
      //## Operation: Execute%1060849357
      INT_T Execute ();

      //## Operation: Line%1060849358
      void Line (cProcedureLine *line);

      //## Operation: Line%1060849359
      cProcedureLine * Line ();

      //## Operation: Context%1060946834
      cContext * Context ();

  public:
    // Additional Public Declarations
      //## begin cActLine%3F3BA40902DE.public preserve=yes
      //## end cActLine%3F3BA40902DE.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F3CC18402EE
      //## Role: cActLine::ActProcedure%3F3CC1860010
      //## begin cActLine::ActProcedure%3F3CC1860010.role preserve=no  public: cActProcedure {0..1 -> 1RFHN}
      cActProcedure *_ActProcedure;
      //## end cActLine::ActProcedure%3F3CC1860010.role

      //## Association: System::PLC::<unnamed>%3F3BA52002DE
      //## Role: cActLine::\rLine%3F3BA5210290
      //## begin cActLine::\rLine%3F3BA5210290.role preserve=no  public: cProcedureLine { -> 0..1RFHN}
      cProcedureLine *_Line;
      //## end cActLine::\rLine%3F3BA5210290.role

      //## Association: System::PLC::<unnamed>%3F3CC0FF02FD
      //## Role: cActLine::Context%3F3CC10100AB
      //## begin cActLine::Context%3F3CC10100AB.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cActLine::Context%3F3CC10100AB.role

    // Additional Protected Declarations
      //## begin cActLine%3F3BA40902DE.protected preserve=yes
      //## end cActLine%3F3BA40902DE.protected

  private:
    // Additional Private Declarations
      //## begin cActLine%3F3BA40902DE.private preserve=yes
      //## end cActLine%3F3BA40902DE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cActLine%3F3BA40902DE.implementation preserve=yes
      //## end cActLine%3F3BA40902DE.implementation

};

//## begin cActLine%3F3BA40902DE.postscript preserve=yes
//## end cActLine%3F3BA40902DE.postscript

// Class cActLine 

//## begin module%3F3BA40902DE.epilog preserve=yes
//## end module%3F3BA40902DE.epilog


#endif
