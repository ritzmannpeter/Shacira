//## begin module%3C7E428400AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7E428400AB.cm

//## begin module%3C7E428400AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7E428400AB.cp

//## Module: cFuncRef%3C7E428400AB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFuncRef.h

#ifndef cFuncRef_h
#define cFuncRef_h 1

//## begin module%3C7E428400AB.includes preserve=yes

#include "System/Database/FuncSpecs.h"

typedef VOID_FUNC_T (*ADDRPROC)(UCHAR_T func_class, CONST_STRING_T func_name); 

#define IS_FREE_FUNCTION(fc)   (fc == SH_FREE)
#define IS_EMBED_FUNCTION(fc)  (fc == SH_EMBED)
#define IS_INPUT_FUNCTION(fc)  (fc == SH_PLAUS || \
                                fc == SH_USER)
#define IS_MODEL_FUNCTION(fc)  (fc == SH_FILTER || \
                                fc == SH_CONVERSION || \
                                fc == SH_EMBED  || \
                                fc == SH_LIMIT  || \
                                fc == SH_ACCESS || \
                                fc == SH_UNIT || \
                                fc == SH_DEVICE_STATE)
#define IS_TRANS_FUNCTION(fc)  (fc == SH_FILTER || \
                                fc == SH_CONVERSION || \
                                fc == SH_UNIT || \
                                fc == SH_ACCESS)
#define IS_GUI_FUNCTION(fc)    (fc == SH_BUTTON || \
                                fc == SH_PLAUS || \
                                fc == SH_USER || \
                                fc == SH_DARK || \
                                fc == SH_VIEW || \
                                fc == SH_VALUE || \
                                fc == SH_SIG_FILTER || \
                                fc == SH_SLOT || \
                                fc == SH_WINIT || \
                                fc == SH_EVENT_FILTER)

//## end module%3C7E428400AB.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"
// cArgument
#include "System/Database/cArgument.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cBlockBuffer;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cSHVariant;
class __DLL_EXPORT__ cFuncDecl;
class __DLL_EXPORT__ cSharedLibrary;

//## begin module%3C7E428400AB.additionalDeclarations preserve=yes

typedef void cAbstractWidget;

//## end module%3C7E428400AB.additionalDeclarations


//## begin cFuncRef%3C7E428400AB.preface preserve=yes
//## end cFuncRef%3C7E428400AB.preface

//## Class: cFuncRef%3C7E428400AB
//	This class realizes a function reference. A function
//	reference can be viewed as an instance of a function
//	call where the parameters of the call are fully
//	specified. Nevertheless a parameter can be specified as
//	another function reference or a variable reference. The
//	concrete parameter values are computed when a function
//	reference is "called". Calling a function reference is
//	done by retrieveing the function value of a reference or
//	by executing the call method in the case of a void type
//	function.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E073B3701E3;cArgument { -> }
//## Uses: <unnamed>%3E9EAA8803C8;cBlockBuffer { -> F}
//## Uses: <unnamed>%3EF4523B0128;cSHVariant { -> F}
//## Uses: <unnamed>%4198C4A302CE;cSharedLibrary { -> F}
//## Uses: <unnamed>%41E6AB1101F4;cCustomFunctions { -> }
//## Uses: <unnamed>%4280DA4900CB;cTransientObject { -> F}

class __DLL_EXPORT__ cFuncRef 
{
  //## begin cFuncRef%3C7E428400AB.initialDeclarations preserve=yes
public:
  //## end cFuncRef%3C7E428400AB.initialDeclarations

    //## Constructors (generated)
      cFuncRef();

      cFuncRef(const cFuncRef &right);

    //## Constructors (specified)
      //## Operation: cFuncRef%1040202772
      cFuncRef (cFuncDecl *func_decl, cContext *context);

    //## Destructor (generated)
      virtual ~cFuncRef();


    //## Other Operations (specified)
      //## Operation: DataType%1061798000
      UCHAR_T DataType ();

      //## Operation: FuncDecl%1061797998
      cFuncDecl * FuncDecl ();

      //## Operation: SetArg%1040202773
      //	Set Arg is used by the reference parser to set a
      //	function argument. This function should never be called
      //	by a function reference user.
      void SetArg (ULONG_T pos, cArgument *param);

      //## Operation: Args%1040202774
      //	Returns the number of Arguments of a function reference.
      ULONG_T Args ();

      //## Operation: CallFunc%1088693728
      void CallFunc ();

      //## Operation: CallFunc%1088693729
      void CallFunc (LONG_T &value);

      //## Operation: CallFunc%1088693730
      void CallFunc (ULONG_T &value);

      //## Operation: CallFunc%1088693731
      void CallFunc (FLOAT_T &value);

      //## Operation: CallFunc%1088693732
      void CallFunc (DOUBLE_T &value);

      //## Operation: CallFunc%1088693733
      void CallFunc (STRING_T &value);

      //## Operation: CallFunc%1088693734
      void CallFunc (WSTRING_T &value);

      //## Operation: CallFunc%1088693735
      void CallFunc (PTR_T &value);

      //## Operation: CallMDLFunc%1088693736
      void CallMDLFunc (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693737
      void CallMDLFunc (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693738
      void CallMDLFunc (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693739
      void CallMDLFunc (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693740
      void CallMDLFunc (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693741
      void CallMDLFunc (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693742
      void CallMDLFunc (LONG_T &value, LONG_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693743
      void CallMDLFunc (ULONG_T &value, ULONG_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693744
      void CallMDLFunc (FLOAT_T &value, FLOAT_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693745
      void CallMDLFunc (DOUBLE_T &value, DOUBLE_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693746
      void CallMDLFunc (STRING_T &value, CONST_STRING_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693747
      void CallMDLFunc (WSTRING_T &value, CONST_WSTRING_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallMDLFunc%1088693748
      void CallMDLFunc (PTR_T &value, PTR_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);
      void CallMDLFunc (PTR_T &value, PTR_T act_value, ULONG_T * size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);

      //## Operation: CallGUIFunc%1088693749
      void CallGUIFunc (cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693750
      void CallGUIFunc (LONG_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693751
      void CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693752
      void CallGUIFunc (FLOAT_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693753
      void CallGUIFunc (DOUBLE_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693754
      void CallGUIFunc (STRING_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693755
      void CallGUIFunc (WSTRING_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693756
      void CallGUIFunc (PTR_T &value, cAbstractWidget *abstract_widget);

      //## Operation: CallGUIFunc%1088693757
      void CallGUIFunc (cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693758
      void CallGUIFunc (LONG_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693759
      void CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693760
      void CallGUIFunc (FLOAT_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693761
      void CallGUIFunc (DOUBLE_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693762
      void CallGUIFunc (STRING_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693763
      void CallGUIFunc (WSTRING_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1088693764
      void CallGUIFunc (PTR_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input);

      //## Operation: CallGUIFunc%1089303819
      void CallGUIFunc (STRING_T &value, cAbstractWidget *abstract_widget, LONG_T index);

      //## Operation: CallGUIFunc%1089304423
      void CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget, ULONG_T signal, cAbstractWidget *sender);

      //## Operation: CallGUIFunc%1089316462
      void CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget, ULONG_T signal);

      //## Operation: CallGUIFunc%1089712048
      void CallGUIFunc (LONG_T &new_value, cAbstractWidget *abstract_widget, LONG_T value, ULONG_T flags);

      //## Operation: CallEventFilterFunc%1115740686
      void CallEventFilterFunc (ULONG_T &value, cAbstractWidget *abstract_widget, cTransientObject *object);

      //## Operation: CallUnitFunc%1109785971
      void CallUnitFunc (LONG_T &value, LONG_T act_value, ULONG_T flags, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: CallUnitFunc%1109785973
      void CallUnitFunc (FLOAT_T &value, FLOAT_T act_value, ULONG_T flags, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: CallUnitFunc%1109785974
      void CallUnitFunc (DOUBLE_T &value, DOUBLE_T act_value, ULONG_T flags, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      void CallDevStateFunc (int & value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

    // Data Members for Class Attributes

      //## Attribute: Name%3E00465B016F
      //	Name of the function denoted by this function reference.
      //## begin cFuncRef::Name%3E00465B016F.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cFuncRef::Name%3E00465B016F.attr

      //## Attribute: Spec%4024D0270280
      //## begin cFuncRef::Spec%4024D0270280.attr preserve=no  public: STRING_T {U} 
      STRING_T _Spec;
      //## end cFuncRef::Spec%4024D0270280.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E2595A4032B
      //## Role: cFuncRef::Context%3E2595A502DC
      //## begin cFuncRef::Context%3E2595A502DC.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cFuncRef::Context%3E2595A502DC.role

  public:
    // Additional Public Declarations
      //## begin cFuncRef%3C7E428400AB.public preserve=yes
      //## end cFuncRef%3C7E428400AB.public

  protected:
    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E9D8D4E0399
      //## Role: cFuncRef::FuncDecl%3E9D8D4F031C
      //## begin cFuncRef::FuncDecl%3E9D8D4F031C.role preserve=no  public: cFuncDecl { -> 1RFHN}
      cFuncDecl *_FuncDecl;
      //## end cFuncRef::FuncDecl%3E9D8D4F031C.role

    // Additional Protected Declarations
      //## begin cFuncRef%3C7E428400AB.protected preserve=yes
      //## end cFuncRef%3C7E428400AB.protected

  private:
    // Additional Private Declarations
      //## begin cFuncRef%3C7E428400AB.private preserve=yes
      //## end cFuncRef%3C7E428400AB.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetFuncAddress%1105976609
      VOID_FUNC_T GetFuncAddress (UCHAR_T func_class, CONST_STRING_T func_name);

    // Data Members for Class Attributes

      //## Attribute: ParamVec%3E0046A202BC
      //## begin cFuncRef::ParamVec%3E0046A202BC.attr preserve=no  implementation: ARG_VECTOR_T {U} 
      ARG_VECTOR_T _ParamVec;
      //## end cFuncRef::ParamVec%3E0046A202BC.attr

      //## Attribute: MdlFuncFactoryAddress%400FA6670281
      //## begin cFuncRef::MdlFuncFactoryAddress%400FA6670281.attr preserve=no  implementation: FUNC_FACTORY_T {U} NULL
      FUNC_FACTORY_T _MdlFuncFactoryAddress;
      //## end cFuncRef::MdlFuncFactoryAddress%400FA6670281.attr

      //## Attribute: GUIFuncFactoryAddress%4050CB8D002E
      //## begin cFuncRef::GUIFuncFactoryAddress%4050CB8D002E.attr preserve=no  implementation: FUNC_FACTORY_T {U} NULL
      FUNC_FACTORY_T _GUIFuncFactoryAddress;
      //## end cFuncRef::GUIFuncFactoryAddress%4050CB8D002E.attr

      //## Attribute: VoidFunc%40E4566701B5
      //## begin cFuncRef::VoidFunc%40E4566701B5.attr preserve=no  implementation: VOID_FUNC {U} NULL
      VOID_FUNC _VoidFunc;
      //## end cFuncRef::VoidFunc%40E4566701B5.attr

      //## Attribute: CharFunc%40EAA0DE038A
      //## begin cFuncRef::CharFunc%40EAA0DE038A.attr preserve=no  implementation: CHAR_FUNC {U} NULL
      CHAR_FUNC _CharFunc;
      //## end cFuncRef::CharFunc%40EAA0DE038A.attr

      //## Attribute: UCharFunc%40EAA0F4038A
      //## begin cFuncRef::UCharFunc%40EAA0F4038A.attr preserve=no  implementation: UCHAR_FUNC {U} NULL
      UCHAR_FUNC _UCharFunc;
      //## end cFuncRef::UCharFunc%40EAA0F4038A.attr

      //## Attribute: LongFunc%40E4566701C5
      //## begin cFuncRef::LongFunc%40E4566701C5.attr preserve=no  implementation: LONG_FUNC {U} NULL
      LONG_FUNC _LongFunc;
      //## end cFuncRef::LongFunc%40E4566701C5.attr

      //## Attribute: ULongFunc%40E4568D01F4
      //## begin cFuncRef::ULongFunc%40E4568D01F4.attr preserve=no  implementation: ULONG_FUNC {U} NULL
      ULONG_FUNC _ULongFunc;
      //## end cFuncRef::ULongFunc%40E4568D01F4.attr

      //## Attribute: FloatFunc%40E4566701D4
      //## begin cFuncRef::FloatFunc%40E4566701D4.attr preserve=no  implementation: FLOAT_FUNC {U} NULL
      FLOAT_FUNC _FloatFunc;
      //## end cFuncRef::FloatFunc%40E4566701D4.attr

      //## Attribute: DoubleFunc%40E4566701F4
      //## begin cFuncRef::DoubleFunc%40E4566701F4.attr preserve=no  implementation: DOUBLE_FUNC {U} NULL
      DOUBLE_FUNC _DoubleFunc;
      //## end cFuncRef::DoubleFunc%40E4566701F4.attr

      //## Attribute: StringFunc%40E456670203
      //## begin cFuncRef::StringFunc%40E456670203.attr preserve=no  implementation: STRING_FUNC {U} NULL
      STRING_FUNC _StringFunc;
      //## end cFuncRef::StringFunc%40E456670203.attr

      //## Attribute: WStringFunc%40E456670213
      //## begin cFuncRef::WStringFunc%40E456670213.attr preserve=no  implementation: WSTRING_FUNC {U} NULL
      WSTRING_FUNC _WStringFunc;
      //## end cFuncRef::WStringFunc%40E456670213.attr

      //## Attribute: PtrFunc%40E456670222
      //## begin cFuncRef::PtrFunc%40E456670222.attr preserve=no  implementation: PTR_FUNC {U} NULL
      PTR_FUNC _PtrFunc;
      //## end cFuncRef::PtrFunc%40E456670222.attr

      //## Attribute: ShortFunc%40EAA10D000F
      //## begin cFuncRef::ShortFunc%40EAA10D000F.attr preserve=no  implementation: SHORT_FUNC {U} NULL
      SHORT_FUNC _ShortFunc;
      //## end cFuncRef::ShortFunc%40EAA10D000F.attr

      //## Attribute: UShortFunc%40EAA12200BB
      //## begin cFuncRef::UShortFunc%40EAA12200BB.attr preserve=no  implementation: USHORT_FUNC {U} NULL
      USHORT_FUNC _UShortFunc;
      //## end cFuncRef::UShortFunc%40EAA12200BB.attr

    // Additional Implementation Declarations
      //## begin cFuncRef%3C7E428400AB.implementation preserve=yes
      //## end cFuncRef%3C7E428400AB.implementation

};

//## begin cFuncRef%3C7E428400AB.postscript preserve=yes
//## end cFuncRef%3C7E428400AB.postscript

// Class cFuncRef 

//## begin module%3C7E428400AB.epilog preserve=yes
//## end module%3C7E428400AB.epilog


#endif
