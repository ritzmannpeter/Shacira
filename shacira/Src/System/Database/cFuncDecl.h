//## begin module%3E0042BA0033.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0042BA0033.cm

//## begin module%3E0042BA0033.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0042BA0033.cp

//## Module: cFuncDecl%3E0042BA0033; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFuncDecl.h

#ifndef cFuncDecl_h
#define cFuncDecl_h 1

//## begin module%3E0042BA0033.includes preserve=yes
//## end module%3E0042BA0033.includes


class __DLL_EXPORT__ cContext;

//## begin module%3E0042BA0033.additionalDeclarations preserve=yes
//## end module%3E0042BA0033.additionalDeclarations


//## begin cFuncDecl%3E0042BA0033.preface preserve=yes
//## end cFuncDecl%3E0042BA0033.preface

//## Class: cFuncDecl%3E0042BA0033
//	Implements the description of a user function (function
//	declaration).
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cFuncDecl 
{
  //## begin cFuncDecl%3E0042BA0033.initialDeclarations preserve=yes
public:
  //## end cFuncDecl%3E0042BA0033.initialDeclarations

    //## Constructors (generated)
      cFuncDecl();

      cFuncDecl(const cFuncDecl &right);

    //## Constructors (specified)
      //## Operation: cFuncDecl%1040992356
      cFuncDecl (CONST_STRING_T func_name, UCHAR_T func_type, UCHAR_T func_class);

    //## Destructor (generated)
      virtual ~cFuncDecl();


    //## Other Operations (specified)
      //## Operation: FuncClass%1061805343
      UCHAR_T FuncClass ();

      //## Operation: DataType%1061805341
      UCHAR_T DataType ();

      //## Operation: AddParam%1040992357
      void AddParam (INT_T param_type, CONST_STRING_T param_name);

      //## Operation: Params%1040658555
      ULONG_T Params ();

      //## Operation: ParamType%1040658556
      INT_T ParamType (ULONG_T pos);

      //## Operation: ParamName%1074795683
      STRING_T ParamName (ULONG_T pos);

      //## Operation: ClassName%1061805344
      static STRING_T ClassName (UCHAR_T class_code);

    // Data Members for Class Attributes

      //## Attribute: FuncName%3E07399902EC
      //## begin cFuncDecl::FuncName%3E07399902EC.attr preserve=no  public: STRING_T {U} 
      STRING_T _FuncName;
      //## end cFuncDecl::FuncName%3E07399902EC.attr

      //## Attribute: FuncClass%3E9E594202DE
      //## begin cFuncDecl::FuncClass%3E9E594202DE.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _FuncClass;
      //## end cFuncDecl::FuncClass%3E9E594202DE.attr

      //## Attribute: DataType%3E07399902F6
      //## begin cFuncDecl::DataType%3E07399902F6.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cFuncDecl::DataType%3E07399902F6.attr

  public:
    // Additional Public Declarations
      //## begin cFuncDecl%3E0042BA0033.public preserve=yes
      //## end cFuncDecl%3E0042BA0033.public

  protected:
    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E0737AD02F8
      //## Role: cFuncDecl::Context%3E0737AE03AF
      //## begin cFuncDecl::Context%3E0737AE03AF.role preserve=no  public: cContext {0..n -> 1RFHN}
      cContext *_Context;
      //## end cFuncDecl::Context%3E0737AE03AF.role

    // Additional Protected Declarations
      //## begin cFuncDecl%3E0042BA0033.protected preserve=yes
      //## end cFuncDecl%3E0042BA0033.protected

  private:
    // Additional Private Declarations
      //## begin cFuncDecl%3E0042BA0033.private preserve=yes
      //## end cFuncDecl%3E0042BA0033.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ParamTypes%3E0739F4024C
      //## begin cFuncDecl::ParamTypes%3E0739F4024C.attr preserve=no  implementation: INT_VECTOR_T {U} 
      INT_VECTOR_T _ParamTypes;
      //## end cFuncDecl::ParamTypes%3E0739F4024C.attr

      //## Attribute: ParamNames%401014640157
      //## begin cFuncDecl::ParamNames%401014640157.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _ParamNames;
      //## end cFuncDecl::ParamNames%401014640157.attr

    // Additional Implementation Declarations
      //## begin cFuncDecl%3E0042BA0033.implementation preserve=yes
      //## end cFuncDecl%3E0042BA0033.implementation

};

//## begin cFuncDecl%3E0042BA0033.postscript preserve=yes
//## end cFuncDecl%3E0042BA0033.postscript

// Class cFuncDecl 

//## begin module%3E0042BA0033.epilog preserve=yes
//## end module%3E0042BA0033.epilog


#endif
