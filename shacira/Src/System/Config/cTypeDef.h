//## begin module%3C42C87A0274.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C42C87A0274.cm

//## begin module%3C42C87A0274.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C42C87A0274.cp

//## Module: cTypeDef%3C42C87A0274; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cTypeDef.h

#ifndef cTypeDef_h
#define cTypeDef_h 1

//## begin module%3C42C87A0274.includes preserve=yes
//## end module%3C42C87A0274.includes


class __DLL_EXPORT__ cTypeFactory;
class __DLL_EXPORT__ cPropertyDef;
class __DLL_EXPORT__ cConvUtils;

//## begin module%3C42C87A0274.additionalDeclarations preserve=yes
//## end module%3C42C87A0274.additionalDeclarations


//## begin cTypeDef%3C42C87A0274.preface preserve=yes
//## end cTypeDef%3C42C87A0274.preface

//## Class: cTypeDef%3C42C87A0274
//## Category: System::Config%3A5307460270
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DCA39A60037;cConvUtils { -> F}

class __DLL_EXPORT__ cTypeDef 
{
  //## begin cTypeDef%3C42C87A0274.initialDeclarations preserve=yes
public:
  //## end cTypeDef%3C42C87A0274.initialDeclarations

    //## Constructors (generated)
      cTypeDef();

      cTypeDef(const cTypeDef &right);

    //## Constructors (specified)
      //## Operation: cTypeDef%1011013293
      cTypeDef (CONST_STRING_T name, cTypeFactory *factory);

    //## Destructor (generated)
      virtual ~cTypeDef();


    //## Other Operations (specified)
      //## Operation: SetBaseType%1011018902
      void SetBaseType (BaseTypes base_type);

      //## Operation: SetRangeType%1011021296
      void SetRangeType (RangeTypes range_type);

      //## Operation: SetDefName%1011021281
      void SetDefName (CONST_STRING_T typedef_name);

      //## Operation: SetRange%1011021287
      void SetRange (CONST_STRING_T spec);

      //## Operation: SetPropertyDef%1011021291
      void SetPropertyDef (CONST_STRING_T property_name, CONST_STRING_T property_spec);

      //## Operation: IsValid%1011021283
      BOOL_T IsValid (CONST_STRING_T value);

      //## Operation: Resolve%1011021284
      void Resolve ();

      //## Operation: PropertyDef%1011021292
      cPropertyDef * PropertyDef (CONST_STRING_T name);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%3C42CA3702EC
      STRING_T get_Name () const;
      void set_Name (STRING_T value);

      //## Attribute: BaseType%3C42C9E9007D
      BaseTypes get_BaseType () const;

      //## Attribute: RangeType%3C42EC020039
      RangeTypes get_RangeType () const;

      //## Attribute: StringEnumeration%3C42E9010141
      STRING_LIST_T get_StringEnumeration () const;

      //## Attribute: NumericEnumeration%3C42EB330095
      DOUBLE_LIST_T get_NumericEnumeration () const;

      //## Attribute: Min%3C42EE0102A0
      DOUBLE_T get_Min () const;

      //## Attribute: Max%3C42EE120164
      DOUBLE_T get_Max () const;

  public:
    // Additional Public Declarations
      //## begin cTypeDef%3C42C87A0274.public preserve=yes
      //## end cTypeDef%3C42C87A0274.public

  protected:
    // Data Members for Class Attributes

      //## begin cTypeDef::Name%3C42CA3702EC.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cTypeDef::Name%3C42CA3702EC.attr

      //## begin cTypeDef::BaseType%3C42C9E9007D.attr preserve=no  public: BaseTypes {U} UndefinedBaseType
      BaseTypes _BaseType;
      //## end cTypeDef::BaseType%3C42C9E9007D.attr

      //## begin cTypeDef::RangeType%3C42EC020039.attr preserve=no  public: RangeTypes {U} UndefinedRangeType
      RangeTypes _RangeType;
      //## end cTypeDef::RangeType%3C42EC020039.attr

      //## begin cTypeDef::StringEnumeration%3C42E9010141.attr preserve=no  public: STRING_LIST_T {U} 
      STRING_LIST_T _StringEnumeration;
      //## end cTypeDef::StringEnumeration%3C42E9010141.attr

      //## begin cTypeDef::NumericEnumeration%3C42EB330095.attr preserve=no  public: DOUBLE_LIST_T {U} 
      DOUBLE_LIST_T _NumericEnumeration;
      //## end cTypeDef::NumericEnumeration%3C42EB330095.attr

      //## begin cTypeDef::Min%3C42EE0102A0.attr preserve=no  public: DOUBLE_T {U} 0
      DOUBLE_T _Min;
      //## end cTypeDef::Min%3C42EE0102A0.attr

      //## begin cTypeDef::Max%3C42EE120164.attr preserve=no  public: DOUBLE_T {U} 0
      DOUBLE_T _Max;
      //## end cTypeDef::Max%3C42EE120164.attr

    // Data Members for Associations

      //## Association: System::Config::<unnamed>%3C4477B403B3
      //## Role: cTypeDef::PropertyDefs%3C4477B502BA
      //## Qualifier: name%3C4478000037; STRING_T
      //## begin cTypeDef::PropertyDefs%3C4477B502BA.role preserve=no  public: cPropertyDef {1 -> 0..nRFHN}
      std::map<STRING_T, cPropertyDef*> _PropertyDefs;
      //## end cTypeDef::PropertyDefs%3C4477B502BA.role

      //## Association: System::Config::<unnamed>%3C44772B0276
      //## Role: cTypeDef::TypeFactory%3C44772C02E5
      //## begin cTypeDef::TypeFactory%3C44772C02E5.role preserve=no  public: cTypeFactory {0..n -> 1RFHN}
      cTypeFactory *_TypeFactory;
      //## end cTypeDef::TypeFactory%3C44772C02E5.role

      //## Association: System::Config::<unnamed>%3C447812023C
      //## Role: cTypeDef::TypeDef%3C4478250172
      //## begin cTypeDef::TypeDef%3C4478250172.role preserve=no  public: cTypeDef { -> 1RFHN}
      cTypeDef *_TypeDef;
      //## end cTypeDef::TypeDef%3C4478250172.role

    // Additional Protected Declarations
      //## begin cTypeDef%3C42C87A0274.protected preserve=yes
      //## end cTypeDef%3C42C87A0274.protected

  private:
    // Additional Private Declarations
      //## begin cTypeDef%3C42C87A0274.private preserve=yes
      //## end cTypeDef%3C42C87A0274.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetRange%1011018900
      void SetRange (DOUBLE_T min, DOUBLE_T max);

      //## Operation: SetRange%1011018899
      void SetRange (DOUBLE_LIST_T &enumeration);

      //## Operation: SetRange%1011018901
      void SetRange (STRING_LIST_T &enumeration);

      //## Operation: SetStringRange%1011021288
      void SetStringRange (CONST_STRING_T spec);

      //## Operation: SetNumericRange%1011021289
      void SetNumericRange (CONST_STRING_T spec);

    // Data Members for Class Attributes

      //## Attribute: DefName%3C42F596012F
      //## begin cTypeDef::DefName%3C42F596012F.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _DefName;
      //## end cTypeDef::DefName%3C42F596012F.attr

      //## Attribute: Text%3C431EDF0385
      //## begin cTypeDef::Text%3C431EDF0385.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Text;
      //## end cTypeDef::Text%3C431EDF0385.attr

    // Additional Implementation Declarations
      //## begin cTypeDef%3C42C87A0274.implementation preserve=yes
      //## end cTypeDef%3C42C87A0274.implementation

};

//## begin cTypeDef%3C42C87A0274.postscript preserve=yes
//## end cTypeDef%3C42C87A0274.postscript

// Class cTypeDef 

//## begin module%3C42C87A0274.epilog preserve=yes
//## end module%3C42C87A0274.epilog


#endif
