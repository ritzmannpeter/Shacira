//## begin module%3E0032230357.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0032230357.cm

//## begin module%3E0032230357.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0032230357.cp

//## Module: cVarDef%3E0032230357; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVarDef.h

#ifndef cVarDef_h
#define cVarDef_h 1

//## begin module%3E0032230357.includes preserve=yes
//## end module%3E0032230357.includes


class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cVariable;
class __DLL_EXPORT__ cVariableValues;
class __DLL_EXPORT__ cSHVariant;
class __DLL_EXPORT__ cMapping;
class __DLL_EXPORT__ cFuncRef;
class __DLL_EXPORT__ cArgument;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cLocalVariable;
class __DLL_EXPORT__ cStringBuffer;

//## begin module%3E0032230357.additionalDeclarations preserve=yes

#define MAX_DIMENSIONS     4

#define IGN_VALUES             0x00000001
#define IGN_DESCRIPTION        0x00000002
#define IGN_TEXT               0x00000004
#define IGN_DIM1_TEXT          0x00000008
#define IGN_DIM2_TEXT          0x00000010
#define IGN_DIM3_TEXT          0x00000020
#define IGN_DIM4_TEXT          0x00000040
#define IGN_UNIT_TEXT          0x00000080
#define USE_DATASET_PRECISION  0x00000100
#define USE_EXPORT_FORMAT      0x00000200

//## end module%3E0032230357.additionalDeclarations


//## begin cVarDef%3E0032230357.preface preserve=yes
//## end cVarDef%3E0032230357.preface

//## Class: cVarDef%3E0032230357
//	This class implements a vriable definition. The variable
//	definition is the static description of a variable. A
//	variable definition can be parsed from a model file or
//	constructed dynamically.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EF8987F0000;cSHVariant { -> F}
//## Uses: <unnamed>%40E1C4EE0242;cArgument { -> F}
//## Uses: <unnamed>%4117C9F0004E;cLocalVariable { -> F}
//## Uses: <unnamed>%420C80D70290;cStringUtils { -> F}

class __DLL_EXPORT__ cVarDef 
{
  //## begin cVarDef%3E0032230357.initialDeclarations preserve=yes
public:
  //## end cVarDef%3E0032230357.initialDeclarations

    //## Constructors (generated)
      cVarDef();

      cVarDef(const cVarDef &right);

    //## Constructors (specified)
      //## Operation: cVarDef%1040992373
      //	A variable definition must be constructed with a the
      //	name of the variable, a data type a length and a
      //	precision. The argument dynamic signals if this
      //	definition will be parsed or constructed dynamically.
      cVarDef (CONST_STRING_T var_name, UCHAR_T data_type, ULONG_T length, UCHAR_T precision, BOOL_T dynamic = false);

    //## Destructor (generated)
      virtual ~cVarDef();


    //## Other Operations (specified)
      //## Operation: DataType%1061805340
      //	Queries the data type of the variable.
      UCHAR_T DataType ();

      //## Operation: GetPos%1040202763
      //	GetPos calculates a position (flat 1 dimension) from
      //	aout of supplied indices. The position calculation is
      //	the same  as in the C programming language.
      ULONG_T GetPos (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: GetIndices%1040202764
      //	GetIndices calculates the indices to a given position.
      //	Its the inverse function to GetPos.
      void GetIndices (ULONG_T pos, LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4);

      //## Operation: AddDim%1040209222
      //	Adds the description of a dimension to the variable
      //	definition.
      void AddDim (ULONG_T pos, ULONG_T dim_size);

      //## Operation: ClearDims%1130341402
      //	Clear dimension information of variable definition
      void ClearDims ();

      //## Operation: SetFilter%1040209223
      //	Sets filter function reference.
      void SetFilter (cFuncRef *func_ref);

      //## Operation: SetAccess%1132940253
      //	Sets access function reference.
      void SetAccess (cFuncRef *func_ref);

      //## Operation: SetMinSpec%1088537822
      //	Sets min function specification. The min function
      //	specification is of type cArgument * to enable the usage
      //	of constants, variable references and function
      //	references.
      void SetMinSpec (cArgument *min_spec);

      //## Operation: SetMaxSpec%1088537823
      //	Sets max function specification. The max function
      //	specification is of type cArgument * to enable the usage
      //	of constants, variable references and function
      //	references.
      void SetMaxSpec (cArgument *max_spec);

      //## Operation: SetMapping%1040209224
      //	Sets the mapping description of the variable definition.
      void SetMapping (cMapping *mapping);

      //## Operation: SetValues%1091802232
      //	Set the initialization vector (vector of initialization
      //	values) of the variable definition.
      void SetValues (cVariableValues *values);

      //## Operation: Dims%1040209225
      //	 Queries the dimensio count of the variable definition.
      ULONG_T Dims ();

      //## Operation: DimSize%1040209226
      //	 Queries the dimension size at pos of the variable
      //	definition.
      ULONG_T DimSize (ULONG_T pos);

      //## Operation: SetDimSize%1133013902
      //	 Queries the dimension size at pos of the variable
      //	definition.
      void SetDimSize (ULONG_T pos, ULONG_T new_size);

      //## Operation: Elements%1040209227
      //	 Queries the no of elements (items) of a variable
      //	definition.
      ULONG_T Elements ();

      //## Operation: ElementSize%1042559818
      //	 Queries the size in byte of one data item.
      ULONG_T ElementSize ();

      //## Operation: Serialize_Obsolete%1049277232
      STRING_T Serialize_Obsolete ();

      //## Operation: Construct_Obsolete%1049277233
      void Construct_Obsolete (CONST_STRING_T serialized_obj);

      //## Operation: Unparse%1092077355
      //	This method creates an ascii representation of the
      //	variable definition (comparable to the Serialize method
      //	of transient objects)
      void Unparse(STRING_T &buf, ULONG_T ctrl, CONST_STRING_T separator="");
      //	This method writes an ascii representation of the
      //	variable definition into a cStringBuffer
      void Unparse(cStringBuffer &buf, ULONG_T ctrl, CONST_STRING_T separator="");

      //## Operation: IsDynamic%1090073692
      //	 Returns true if this is a dyynamic constructed variable
      //	definition.
      BOOL_T IsDynamic ();

      //## Operation: TypeSpec%1092077359
      STRING_T TypeSpec (ULONG_T ctrl=0);

      BOOL_T EnableMapping(BOOL_T state, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
      BOOL_T EnableCompleteMapping(ULONG_T state);
      BOOL_T MappingEnabled(LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

    // Data Members for Class Attributes

      //## Attribute: DatabaseName%41160D5C0251
      //## begin cVarDef::DatabaseName%41160D5C0251.attr preserve=no  public: STRING_T {U} 
      STRING_T _DatabaseName;
      //## end cVarDef::DatabaseName%41160D5C0251.attr

      //## Attribute: DeviceName%3FD97A6701F4
      //## begin cVarDef::DeviceName%3FD97A6701F4.attr preserve=no  public: STRING_T {U} 
      STRING_T _DeviceName;
      //## end cVarDef::DeviceName%3FD97A6701F4.attr

      //## Attribute: VarName%3E00545502FB
      //## begin cVarDef::VarName%3E00545502FB.attr preserve=no  public: STRING_T {U} 
      STRING_T _VarName;
      //## end cVarDef::VarName%3E00545502FB.attr

      //## Attribute: DataType%3E00540B01BE
      //## begin cVarDef::DataType%3E00540B01BE.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cVarDef::DataType%3E00540B01BE.attr

      //## Attribute: Length%3E0CA3FC0070
      //## begin cVarDef::Length%3E0CA3FC0070.attr preserve=no  public: ULONG_T {U} 1
      ULONG_T _Length;
      //## end cVarDef::Length%3E0CA3FC0070.attr

      //## Attribute: Precision%3E0CA4180175
      //## begin cVarDef::Precision%3E0CA4180175.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _Precision;
      //## end cVarDef::Precision%3E0CA4180175.attr

      //## Attribute: VarType%3E101AFC0034
      //## begin cVarDef::VarType%3E101AFC0034.attr preserve=no  public: UCHAR_T {U} SH_VAR_VOLATILE
      UCHAR_T _VarType;
      //## end cVarDef::VarType%3E101AFC0034.attr

      //## Attribute: PersistenceType%3EAFEBA30261
      //## begin cVarDef::PersistenceType%3EAFEBA30261.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _PersistenceType;
      //## end cVarDef::PersistenceType%3EAFEBA30261.attr

      //## Attribute: FileName%41120375007D
      //## begin cVarDef::FileName%41120375007D.attr preserve=no  public: STRING_T {U} 
      STRING_T _FileName;
      //## end cVarDef::FileName%41120375007D.attr

      //## Attribute: Description%3EAFEB8B006D
      //## begin cVarDef::Description%3EAFEB8B006D.attr preserve=no  public: STRING_T {U} 
      STRING_T _Description;
      //## end cVarDef::Description%3EAFEB8B006D.attr

      //## Attribute: MinSpec%40E1C4AB0399
      //## begin cVarDef::MinSpec%40E1C4AB0399.attr preserve=no  public: cArgument * {U} NULL
      cArgument *_MinSpec;
      //## end cVarDef::MinSpec%40E1C4AB0399.attr

      //## Attribute: MaxSpec%40E1C4C2007D
      //## begin cVarDef::MaxSpec%40E1C4C2007D.attr preserve=no  public: cArgument * {U} NULL
      cArgument *_MaxSpec;
      //## end cVarDef::MaxSpec%40E1C4C2007D.attr

      //## Attribute: RefreshType%3EAFF030009C
      //## begin cVarDef::RefreshType%3EAFF030009C.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _RefreshType;
      //## end cVarDef::RefreshType%3EAFF030009C.attr

      //## Attribute: RefreshValue%3EAFF0440222
      //## begin cVarDef::RefreshValue%3EAFF0440222.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _RefreshValue;
      //## end cVarDef::RefreshValue%3EAFF0440222.attr

      //## Attribute: BackgroundVar%419B06BC0186
      //## begin cVarDef::BackgroundVar%419B06BC0186.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _BackgroundVar;
      //## end cVarDef::BackgroundVar%419B06BC0186.attr

      //## Attribute: Text%420C70D7000F
      //## begin cVarDef::Text%420C70D7000F.attr preserve=no  public: STRING_T {U} 
      STRING_T _Text;
      //## end cVarDef::Text%420C70D7000F.attr

      //## Attribute: Dim1Text%420C70E30138
      //## begin cVarDef::Dim1Text%420C70E30138.attr preserve=no  public: STRING_T {U} 
      STRING_T _Dim1Text;
      //## end cVarDef::Dim1Text%420C70E30138.attr

      //## Attribute: Dim2Text%420C70ED0000
      //## begin cVarDef::Dim2Text%420C70ED0000.attr preserve=no  public: STRING_T {U} 
      STRING_T _Dim2Text;
      //## end cVarDef::Dim2Text%420C70ED0000.attr

      //## Attribute: Dim3Text%420C70F90157
      //## begin cVarDef::Dim3Text%420C70F90157.attr preserve=no  public: STRING_T {U} 
      STRING_T _Dim3Text;
      //## end cVarDef::Dim3Text%420C70F90157.attr

      //## Attribute: Dim4Text%420C7103035B
      //## begin cVarDef::Dim4Text%420C7103035B.attr preserve=no  public: STRING_T {U} 
      STRING_T _Dim4Text;
      //## end cVarDef::Dim4Text%420C7103035B.attr

      //## Attribute: Flags%420C71100138
      //## begin cVarDef::Flags%420C71100138.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Flags;
      //## end cVarDef::Flags%420C71100138.attr

      //## Attribute: UnitText%42257FED00DA
      //## begin cVarDef::UnitText%42257FED00DA.attr preserve=no  public: STRING_T {U} 
      STRING_T _UnitText;
      //## end cVarDef::UnitText%42257FED00DA.attr

      //## Attribute: SystemFlags%43187187012A
      //## begin cVarDef::SystemFlags%43187187012A.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _SystemFlags;
      //## end cVarDef::SystemFlags%43187187012A.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E0032500226
      //## Role: cVarDef::Variable%3E0032510083
      //## begin cVarDef::Variable%3E0032510083.role preserve=no  public: cVariable {1 -> 1RFHN}
      cVariable *_Variable;
      //## end cVarDef::Variable%3E0032510083.role

      //## Association: System::Database::<unnamed>%3E07379A01A6
      //## Role: cVarDef::Context%3E07379B0144
      //## begin cVarDef::Context%3E07379B0144.role preserve=no  public: cContext {0..n -> 1RFHN}
      cContext *_Context;
      //## end cVarDef::Context%3E07379B0144.role

      //## Association: System::Database::<unnamed>%3E0054F60049
      //## Role: cVarDef::Mapping%3E0054F6032E
      //## begin cVarDef::Mapping%3E0054F6032E.role preserve=no  public: cMapping { -> 0..1RFHN}
      cMapping *_Mapping;
      //## end cVarDef::Mapping%3E0054F6032E.role

      //## Association: System::Database::<unnamed>%3E0054EC02E4
      //## Role: cVarDef::Filter%3E0054ED0322
      //## begin cVarDef::Filter%3E0054ED0322.role preserve=no  public: cFuncRef { -> 0..1RFHN}
      cFuncRef *_Filter;
      //## end cVarDef::Filter%3E0054ED0322.role

      //## Association: System::Database::<unnamed>%42257F89005D
      //## Role: cVarDef::UnitDef%42257F8902EE
      //## begin cVarDef::UnitDef%42257F8902EE.role preserve=no  public: cUnitDef { -> 0..1RFHN}
public:
      void set_UnitDef(cUnitDef * unit_def);
      inline cUnitDef * get_UnitDef() const {return _UnitDef;};
//protected:
public: // preliminary
      cUnitDef * _UnitDef;
public:
      //## end cVarDef::UnitDef%42257F8902EE.role

      //## Association: System::Database::<unnamed>%4113A02D000F
      //## Role: cVarDef::Values%4113A02D030D
      //## begin cVarDef::Values%4113A02D030D.role preserve=no  public: cVariableValues {1 -> 0..1RFHN}
      cVariableValues *_Values;
      //## end cVarDef::Values%4113A02D030D.role

      //## Association: System::Database::<unnamed>%43874B68021F
      //## Role: cVarDef::Access%43874B69024E
      //## begin cVarDef::Access%43874B69024E.role preserve=no  public: cFuncRef { -> 0..1RFHN}
      cFuncRef *_Access;
      //## end cVarDef::Access%43874B69024E.role

  public:
    // Additional Public Declarations
      //## begin cVarDef%3E0032230357.public preserve=yes
      //## end cVarDef%3E0032230357.public

  protected:
    // Additional Protected Declarations
      //## begin cVarDef%3E0032230357.protected preserve=yes
      //## end cVarDef%3E0032230357.protected

  private:
    // Additional Private Declarations
      //## begin cVarDef%3E0032230357.private preserve=yes
      //## end cVarDef%3E0032230357.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: PrintDims%1092077356
      ULONG_T PrintDims (STRING_T &buf);

      //## Operation: PrintType%1092077357
      ULONG_T PrintType (STRING_T &buf, ULONG_T ctrl=0);

      //## Operation: PrintDescription%1092126572
      ULONG_T PrintDescription (STRING_T &buf);

      //## Operation: PrintValues%1092077358
      ULONG_T PrintValues(STRING_T &buf, cLocalVariable *variable);
      ULONG_T PrintValues(cStringBuffer &buf, cLocalVariable *variable);
      ULONG_T PrintUnitSensitiveValues(STRING_T &buf, cLocalVariable *variable);

      //## Operation: PrintText%1108111655
      ULONG_T PrintText (STRING_T &buf);

      //## Operation: PrintDim1Text%1108111656
      ULONG_T PrintDim1Text (STRING_T &buf);

      //## Operation: PrintDim2Text%1108111657
      ULONG_T PrintDim2Text (STRING_T &buf);

      //## Operation: PrintDim3Text%1108111658
      ULONG_T PrintDim3Text (STRING_T &buf);

      //## Operation: PrintDim4Text%1108111659
      ULONG_T PrintDim4Text (STRING_T &buf);

      //## Operation: PrintSystemFlags%1125676427
      ULONG_T PrintSystemFlags (STRING_T &buf);

      //## Operation: PrintFlags%1108111660
      ULONG_T PrintFlags (STRING_T &buf);

      //## Operation: PrintUnitText%1145513553
      ULONG_T PrintUnitText (STRING_T &buf);

      //## Operation: DefaultValue%1092122757
      STRING_T DefaultValue (UCHAR_T data_type);

    // Data Members for Class Attributes

      //## Attribute: Dims%3E005437029E
      //## begin cVarDef::Dims%3E005437029E.attr preserve=no  implementation: ULONG_VECTOR_T {U} 
      ULONG_VECTOR_T _Dims;
      //## end cVarDef::Dims%3E005437029E.attr

      //## Attribute: Dynamic%40F94C62007D
      //## begin cVarDef::Dynamic%40F94C62007D.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Dynamic;
      //## end cVarDef::Dynamic%40F94C62007D.attr

    // Additional Implementation Declarations
      //## begin cVarDef%3E0032230357.implementation preserve=yes
      //## end cVarDef%3E0032230357.implementation

private:
   int _Option;
public:
   int get_Option() const {return _Option;};
   void set_Option(int value) {_Option = value;};
};

//## begin cVarDef%3E0032230357.postscript preserve=yes
//## end cVarDef%3E0032230357.postscript

// Class cVarDef 

//## begin module%3E0032230357.epilog preserve=yes
//## end module%3E0032230357.epilog


#endif
