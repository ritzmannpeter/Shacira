//## begin module%3F38BC14031C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F38BC14031C.cm

//## begin module%3F38BC14031C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F38BC14031C.cp

//## Module: cControlProcedure%3F38BC14031C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cControlProcedure.h

#ifndef cControlProcedure_h
#define cControlProcedure_h 1

//## begin module%3F38BC14031C.includes preserve=yes
//## end module%3F38BC14031C.includes


class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cActLine;
class __DLL_EXPORT__ cProcedureLine;

//## begin module%3F38BC14031C.additionalDeclarations preserve=yes

typedef std::vector<cProcedureLine*> LINE_VECTOR_T;

//## end module%3F38BC14031C.additionalDeclarations


//## begin cControlProcedure%3F38BC14031C.preface preserve=yes
//## end cControlProcedure%3F38BC14031C.preface

//## Class: cControlProcedure%3F38BC14031C
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F38BCA8038A;cContext { -> F}
//## Uses: <unnamed>%3F3A36E5007D;cProcedureLine { -> F}
//## Uses: <unnamed>%3F3BA848033C;cActLine { -> F}

class __DLL_EXPORT__ cControlProcedure 
{
  //## begin cControlProcedure%3F38BC14031C.initialDeclarations preserve=yes
public:
  //## end cControlProcedure%3F38BC14031C.initialDeclarations

    //## Constructors (generated)
      cControlProcedure();

      cControlProcedure(const cControlProcedure &right);

    //## Constructors (specified)
      //## Operation: cControlProcedure%1060779895
      cControlProcedure (CONST_STRING_T name);

    //## Destructor (generated)
      virtual ~cControlProcedure();


    //## Other Operations (specified)
      //## Operation: Name%1060960060
      STRING_T Name ();

      //## Operation: AddLine%1060779896
      void AddLine (cProcedureLine *line);

      //## Operation: Execute%1060849351
      INT_T Execute (cContext *context);

      //## Operation: PrintLines%1060960062
      void PrintLines ();

      //## Operation: FirstLine%1060965468
      cProcedureLine * FirstLine ();

    // Data Members for Class Attributes

      //## Attribute: SourceFile%3F3A369E0177
      //## begin cControlProcedure::SourceFile%3F3A369E0177.attr preserve=no  public: STRING_T {U} 
      STRING_T _SourceFile;
      //## end cControlProcedure::SourceFile%3F3A369E0177.attr

  public:
    // Additional Public Declarations
      //## begin cControlProcedure%3F38BC14031C.public preserve=yes
      //## end cControlProcedure%3F38BC14031C.public

  protected:
    // Additional Protected Declarations
      //## begin cControlProcedure%3F38BC14031C.protected preserve=yes
      //## end cControlProcedure%3F38BC14031C.protected

  private:
    // Additional Private Declarations
      //## begin cControlProcedure%3F38BC14031C.private preserve=yes
      //## end cControlProcedure%3F38BC14031C.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Name%3F38C1FC034B
      //## begin cControlProcedure::Name%3F38C1FC034B.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Name;
      //## end cControlProcedure::Name%3F38C1FC034B.attr

      //## Attribute: Lines%3F3A36C502FD
      //## begin cControlProcedure::Lines%3F3A36C502FD.attr preserve=no  implementation: LINE_VECTOR_T {U} 
      LINE_VECTOR_T _Lines;
      //## end cControlProcedure::Lines%3F3A36C502FD.attr

    // Additional Implementation Declarations
      //## begin cControlProcedure%3F38BC14031C.implementation preserve=yes
      //## end cControlProcedure%3F38BC14031C.implementation

};

//## begin cControlProcedure%3F38BC14031C.postscript preserve=yes
//## end cControlProcedure%3F38BC14031C.postscript

// Class cControlProcedure 

//## begin module%3F38BC14031C.epilog preserve=yes
//## end module%3F38BC14031C.epilog


#endif
