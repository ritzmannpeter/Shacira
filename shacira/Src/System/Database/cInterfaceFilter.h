//## begin module%440482DD039C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440482DD039C.cm

//## begin module%440482DD039C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440482DD039C.cp

//## Module: cInterfaceFilter%440482DD039C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cInterfaceFilter.h

#ifndef cInterfaceFilter_h
#define cInterfaceFilter_h 1

//## begin module%440482DD039C.includes preserve=yes
//## end module%440482DD039C.includes


class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;

//## begin module%440482DD039C.additionalDeclarations preserve=yes

#define EM63_SIGNATURE     0x00000001

//## end module%440482DD039C.additionalDeclarations


//## begin cInterfaceFilter%440482DD039C.preface preserve=yes
//## end cInterfaceFilter%440482DD039C.preface

//## Class: cInterfaceFilter%440482DD039C
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%44054B4801D7;cContext { -> F}
//## Uses: <unnamed>%4405DD220141;cVarRef { -> F}

class __DLL_EXPORT__ cInterfaceFilter 
{
  //## begin cInterfaceFilter%440482DD039C.initialDeclarations preserve=yes
public:
  //## end cInterfaceFilter%440482DD039C.initialDeclarations

    //## Constructors (generated)
      cInterfaceFilter();

      cInterfaceFilter(const cInterfaceFilter &right);

    //## Destructor (generated)
      virtual ~cInterfaceFilter();


    //## Other Operations (specified)
      //## Operation: DefFilter%1141208303
      virtual void DefFilter (cContext *context, ULONG_T if_type, cVarDef *var_def);

      //## Operation: RefFilter%1141208302
      virtual void RefFilter (STRING_T &var_name, LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4);

      //## Operation: FilteredVarRef%1141230224
      virtual cVarRef * FilteredVarRef (cContext *context, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: ParamId%1141665072
      virtual STRING_T ParamId (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

  public:
    // Additional Public Declarations
      //## begin cInterfaceFilter%440482DD039C.public preserve=yes
      //## end cInterfaceFilter%440482DD039C.public

  protected:
    // Data Members for Class Attributes

      //## begin cInterfaceFilter::Flags%440575020086.attr preserve=no  private: ULONG_T {U} 0
      ULONG_T _Flags;
      //## end cInterfaceFilter::Flags%440575020086.attr

    // Additional Protected Declarations
      //## begin cInterfaceFilter%440482DD039C.protected preserve=yes
      //## end cInterfaceFilter%440482DD039C.protected

  private:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Flags%440575020086
      ULONG_T get_Flags () const;
      void set_Flags (ULONG_T value);

    // Additional Private Declarations
      //## begin cInterfaceFilter%440482DD039C.private preserve=yes
      //## end cInterfaceFilter%440482DD039C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cInterfaceFilter%440482DD039C.implementation preserve=yes
      //## end cInterfaceFilter%440482DD039C.implementation

};

//## begin cInterfaceFilter%440482DD039C.postscript preserve=yes
//## end cInterfaceFilter%440482DD039C.postscript

// Class cInterfaceFilter 

//## begin module%440482DD039C.epilog preserve=yes
//## end module%440482DD039C.epilog


#endif
