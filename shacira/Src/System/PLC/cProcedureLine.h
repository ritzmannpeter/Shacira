//## begin module%3F3A35F501F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F3A35F501F4.cm

//## begin module%3F3A35F501F4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F3A35F501F4.cp

//## Module: cProcedureLine%3F3A35F501F4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\PLC\cProcedureLine.h

#ifndef cProcedureLine_h
#define cProcedureLine_h 1

//## begin module%3F3A35F501F4.includes preserve=yes
//## end module%3F3A35F501F4.includes

// cControlProcedure
#include "System/PLC/cControlProcedure.h"

class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFuncRef;
class __DLL_EXPORT__ cArgument;
class __DLL_EXPORT__ cActProcedure;
class __DLL_EXPORT__ cActLine;
class __DLL_EXPORT__ cControlCondition;

//## begin module%3F3A35F501F4.additionalDeclarations preserve=yes

typedef enum {UNDEF_STMT=0, EXEC_STMT, CALL_STMT, PARAM_ASSIGN_STMT,
              ARG_ASSIGN_STMT, IF_STMT, IF_ELSE_STMT, WHILE_STMT,
              END_LINE_STMT, RETURN_STMT} Statements;

//## end module%3F3A35F501F4.additionalDeclarations


//## begin cProcedureLine%3F3A35F501F4.preface preserve=yes
//## end cProcedureLine%3F3A35F501F4.preface

//## Class: cProcedureLine%3F3A35F501F4
//## Category: System::PLC%3F38BB400109
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F3BA7E5005D;cActLine { -> F}
//## Uses: <unnamed>%3F3C9F2C004E;cVarDef { -> F}
//## Uses: <unnamed>%3F3CC468004E;cControlProcedure { -> }
//## Uses: <unnamed>%3F3CC4960196;cContext { -> F}
//## Uses: <unnamed>%3F3D1C8003B9;cActProcedure { -> F}

class __DLL_EXPORT__ cProcedureLine 
{
  //## begin cProcedureLine%3F3A35F501F4.initialDeclarations preserve=yes
public:
  //## end cProcedureLine%3F3A35F501F4.initialDeclarations

    //## Constructors (generated)
      cProcedureLine();

      cProcedureLine(const cProcedureLine &right);

    //## Constructors (specified)
      //## Operation: cProcedureLine%1060779899
      cProcedureLine (Statements type, CONST_STRING_T proc_name, INT_T depth);

      //## Operation: cProcedureLine%1060779900
      cProcedureLine (Statements type, cFuncRef *func_ref, INT_T depth);

      //## Operation: cProcedureLine%1060779901
      cProcedureLine (Statements type, cVarRef *var_ref, cArgument *arg, INT_T depth);

      //## Operation: cProcedureLine%1060779902
      cProcedureLine (Statements type, cVarRef *var_ref, CONST_STRING_T param_name, INT_T depth);

      //## Operation: cProcedureLine%1060779903
      cProcedureLine (Statements type, cControlCondition *cond, INT_T depth);

      //## Operation: cProcedureLine%1090397995
      cProcedureLine (Statements type, INT_T depth);

    //## Destructor (generated)
      virtual ~cProcedureLine();


    //## Other Operations (specified)
      //## Operation: NextLine%1060779905
      void NextLine (cProcedureLine *line);

      //## Operation: NextLine%1060779909
      cProcedureLine * NextLine ();

      //## Operation: CondLine%1060779906
      void CondLine (cProcedureLine *line);

      //## Operation: CondLine%1060779911
      cProcedureLine * CondLine ();

      //## Operation: NotCondLine%1060779907
      void NotCondLine (cProcedureLine *line);

      //## Operation: NotCondLine%1060779912
      cProcedureLine * NotCondLine ();

      //## Operation: ParentLine%1060849352
      void ParentLine (cProcedureLine *line);

      //## Operation: ParentLine%1060849353
      cProcedureLine * ParentLine ();

      //## Operation: Resolve%1060849354
      void Resolve ();

      //## Operation: Execute%1060849350
      INT_T Execute (cActLine *act_line);

      //## Operation: Description%1060779904
      STRING_T Description ();

      //## Operation: TypeName%1060849355
      STRING_T TypeName ();

      //## Operation: Type%1060965461
      Statements Type ();

      //## Operation: ProcName%1060965462
      STRING_T ProcName ();

      //## Operation: ParamName%1060965463
      STRING_T ParamName ();

      //## Operation: Condition%1060965464
      cControlCondition * Condition ();

      //## Operation: VarRef%1060965465
      cVarRef * VarRef ();

      //## Operation: FuncRef%1060965466
      cFuncRef * FuncRef ();

      //## Operation: Argument%1060965467
      cArgument * Argument ();

    // Data Members for Class Attributes

      //## Attribute: SourceLine%3F3A3668038A
      //## begin cProcedureLine::SourceLine%3F3A3668038A.attr preserve=no  public: LONG_T {U} -1
      LONG_T _SourceLine;
      //## end cProcedureLine::SourceLine%3F3A3668038A.attr

      //## Attribute: Line%3F3B7F6F032C
      //## begin cProcedureLine::Line%3F3B7F6F032C.attr preserve=no  public: LONG_T {U} -1
      LONG_T _Line;
      //## end cProcedureLine::Line%3F3B7F6F032C.attr

  public:
    // Additional Public Declarations
      //## begin cProcedureLine%3F3A35F501F4.public preserve=yes
      //## end cProcedureLine%3F3A35F501F4.public

  protected:
    // Data Members for Associations

      //## Association: System::PLC::<unnamed>%3F3A70A9030D
      //## Role: cProcedureLine::FuncRef%3F3A70AA030D
      //## begin cProcedureLine::FuncRef%3F3A70AA030D.role preserve=no  public: cFuncRef { -> 1RFHN}
      cFuncRef *_FuncRef;
      //## end cProcedureLine::FuncRef%3F3A70AA030D.role

      //## Association: System::PLC::<unnamed>%3F3A808F038A
      //## Role: cProcedureLine::NextLine%3F3A809A01A5
      //## begin cProcedureLine::NextLine%3F3A809A01A5.role preserve=no  public: cProcedureLine { -> 1RFHN}
      cProcedureLine *_NextLine;
      //## end cProcedureLine::NextLine%3F3A809A01A5.role

      //## Association: System::PLC::<unnamed>%3F3A81090128
      //## Role: cProcedureLine::NotCondLine%3F3A81190149
      //## begin cProcedureLine::NotCondLine%3F3A81190149.role preserve=no  public: cProcedureLine {1 -> 1RFHN}
      cProcedureLine *_NotCondLine;
      //## end cProcedureLine::NotCondLine%3F3A81190149.role

      //## Association: System::PLC::<unnamed>%3F3A81090128
      //## Role: cProcedureLine::CondLine%3F3A81190148
      //## begin cProcedureLine::CondLine%3F3A81190148.role preserve=no  public: cProcedureLine {1 -> 1RFHN}
      cProcedureLine *_CondLine;
      //## end cProcedureLine::CondLine%3F3A81190148.role

      //## Association: System::PLC::<unnamed>%3F3B62D00109
      //## Role: cProcedureLine::ParentLine%3F3B62DA029F
      //## begin cProcedureLine::ParentLine%3F3B62DA029F.role preserve=no  public: cProcedureLine { -> 1RFHN}
      cProcedureLine *_ParentLine;
      //## end cProcedureLine::ParentLine%3F3B62DA029F.role

      //## Association: System::PLC::<unnamed>%3F3A71B803D8
      //## Role: cProcedureLine::Condition%3F3A71BA0251
      //## begin cProcedureLine::Condition%3F3A71BA0251.role preserve=no  public: cControlCondition { -> 1RFHN}
      cControlCondition *_Condition;
      //## end cProcedureLine::Condition%3F3A71BA0251.role

      //## Association: System::PLC::<unnamed>%3F3A708300FA
      //## Role: cProcedureLine::Argument%3F3A708303B9
      //## begin cProcedureLine::Argument%3F3A708303B9.role preserve=no  public: cArgument { -> 1RFHN}
      cArgument *_Argument;
      //## end cProcedureLine::Argument%3F3A708303B9.role

      //## Association: System::PLC::<unnamed>%3F3A7063036B
      //## Role: cProcedureLine::VarRef%3F3A70640196
      //## begin cProcedureLine::VarRef%3F3A70640196.role preserve=no  public: cVarRef { -> 1RFHN}
      cVarRef *_VarRef;
      //## end cProcedureLine::VarRef%3F3A70640196.role

    // Additional Protected Declarations
      //## begin cProcedureLine%3F3A35F501F4.protected preserve=yes
      //## end cProcedureLine%3F3A35F501F4.protected

  private:
    // Additional Private Declarations
      //## begin cProcedureLine%3F3A35F501F4.private preserve=yes
      //## end cProcedureLine%3F3A35F501F4.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Depth%3F3A794301E4
      //## begin cProcedureLine::Depth%3F3A794301E4.attr preserve=no  implementation: INT_T {U} -1
      INT_T _Depth;
      //## end cProcedureLine::Depth%3F3A794301E4.attr

      //## Attribute: Type%3F3A72B60232
      //## begin cProcedureLine::Type%3F3A72B60232.attr preserve=no  implementation: Statements {U} UNDEF_STMT
      Statements _Type;
      //## end cProcedureLine::Type%3F3A72B60232.attr

      //## Attribute: ProcName%3F3A72D403C8
      //## begin cProcedureLine::ProcName%3F3A72D403C8.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ProcName;
      //## end cProcedureLine::ProcName%3F3A72D403C8.attr

      //## Attribute: ParamName%3F3A733B0186
      //## begin cProcedureLine::ParamName%3F3A733B0186.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ParamName;
      //## end cProcedureLine::ParamName%3F3A733B0186.attr

    // Additional Implementation Declarations
      //## begin cProcedureLine%3F3A35F501F4.implementation preserve=yes
      //## end cProcedureLine%3F3A35F501F4.implementation

};

//## begin cProcedureLine%3F3A35F501F4.postscript preserve=yes
//## end cProcedureLine%3F3A35F501F4.postscript

// Class cProcedureLine 

//## begin module%3F3A35F501F4.epilog preserve=yes
//## end module%3F3A35F501F4.epilog


#endif
