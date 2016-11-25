//## begin module%3A542AD30289.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A542AD30289.cm

//## begin module%3A542AD30289.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A542AD30289.cp

//## Module: cProperty%3A542AD30289; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cProperty.h

#ifndef cProperty_h
#define cProperty_h 1

//## begin module%3A542AD30289.includes preserve=yes
//## end module%3A542AD30289.includes


class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cIniFile;
class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cTypeFactory;
class __DLL_EXPORT__ cPropertyDef;
class __DLL_EXPORT__ cTypeDef;
class __DLL_EXPORT__ cConfiguration;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cConvUtils;

//## begin module%3A542AD30289.additionalDeclarations preserve=yes

typedef std::vector<double> NUMERIC_VECTOR_T;
typedef std::vector<cConfigurationObject*> CONFOBJ_VECTOR_T;

//## end module%3A542AD30289.additionalDeclarations


//## begin cProperty%3A542AD30289.preface preserve=yes
//## end cProperty%3A542AD30289.preface

//## Class: cProperty%3A542AD30289
//## Category: System::Config%3A5307460270
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AE4668E005A;cTokenizer { -> F}
//## Uses: <unnamed>%3DCA391E03C1;cConvUtils { -> F}
//## Uses: <unnamed>%3DCA4E1000E6;cStringUtils { -> F}
//## Uses: <unnamed>%3DD0E61302E8;cIniFile { -> F}

class __DLL_EXPORT__ cProperty 
{
  //## begin cProperty%3A542AD30289.initialDeclarations preserve=yes
public:
  //## end cProperty%3A542AD30289.initialDeclarations

    //## Constructors (generated)
      cProperty();

      cProperty(const cProperty &right);

    //## Constructors (specified)
      //## Operation: cProperty%978594326
      cProperty (cConfigurationObject *config_object, CONST_STRING_T name, CONST_STRING_T buffer);

    //## Destructor (generated)
      virtual ~cProperty();


    //## Other Operations (specified)
      //## Operation: PropertyDef%1011204315
      cPropertyDef * PropertyDef ();

      //## Operation: Save%1011186741
      void Save ();

      //## Operation: Resolve%1011095992
      void Resolve ();

      //## Operation: Value%1011114940
      DOUBLE_T Value (DOUBLE_T default_value);

      //## Operation: Value%1011114941
      LONG_T Value (LONG_T default_value);

      //## Operation: Value%1011276243
      ULONG_T Value (ULONG_T default_value);

      //## Operation: Value%1011114942
      BOOL_T Value (BOOL_T default_value);

      //## Operation: Value%1011114943
      STRING_T Value (CONST_STRING_T default_value);

      //## Operation: Value%1011114944
      cConfigurationObject * Value (cConfigurationObject *default_value);

      //## Operation: Value%1011114945
      INT_T Value (STRING_VECTOR_T &vec);

      //## Operation: Value%1011114946
      INT_T Value (NUMERIC_VECTOR_T &vec);

      //## Operation: Value%1011114947
      INT_T Value (CONFOBJ_VECTOR_T &vec);

      //## Operation: SetValue%1011186739
      void SetValue (CONST_STRING_T value, ULONG_T index = 0);

      //## Operation: SetValue%1011186748
      void SetValue (DOUBLE_T value, ULONG_T index = 0);

      //## Operation: SetValue%1011186751
      void SetValue (LONG_T value, ULONG_T index = 0);

      //## Operation: SetValue%1011276244
      void SetValue (ULONG_T value, ULONG_T index = 0);

      //## Operation: SetValue%1011186749
      void SetValue (cConfigurationObject *value, ULONG_T index = 0);

      //## Operation: SetValue%1011186750
      void SetValue (BOOL_T value, ULONG_T index = 0);

      //## Operation: IsInteger%1083004730
      BOOL_T IsInteger ();

      //## Operation: IsReal%1083004731
      BOOL_T IsReal ();

      //## Operation: IsString%1083004732
      BOOL_T IsString ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%3A542B0902E0
      STRING_T get_Name () const;

  public:
    // Additional Public Declarations
      //## begin cProperty%3A542AD30289.public preserve=yes
      //## end cProperty%3A542AD30289.public

  protected:
    // Data Members for Class Attributes

      //## begin cProperty::Name%3A542B0902E0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cProperty::Name%3A542B0902E0.attr

    // Data Members for Associations

      //## Association: System::Config::<unnamed>%3C443D960201
      //## Role: cProperty::PropertyDef%3C443D97023F
      //## begin cProperty::PropertyDef%3C443D97023F.role preserve=no  public: cPropertyDef { -> 1RFHN}
      cPropertyDef *_PropertyDef;
      //## end cProperty::PropertyDef%3C443D97023F.role

      //## Association: System::Config::<unnamed>%3C44358F009E
      //## Role: cProperty::Configuration%3C4435910141
      //## begin cProperty::Configuration%3C4435910141.role preserve=no  public: cConfiguration { -> 1RFHN}
      cConfiguration *_Configuration;
      //## end cProperty::Configuration%3C4435910141.role

      //## Association: System::Config::<unnamed>%3C44792A016C
      //## Role: cProperty::TypeDef%3C44792D0170
      //## begin cProperty::TypeDef%3C44792D0170.role preserve=no  public: cTypeDef { -> 1RFHN}
      cTypeDef *_TypeDef;
      //## end cProperty::TypeDef%3C44792D0170.role

      //## Association: System::Config::<unnamed>%3C4426C9017C
      //## Role: cProperty::TypeFactory%3C4426CB017F
      //## begin cProperty::TypeFactory%3C4426CB017F.role preserve=no  public: cTypeFactory { -> 1RFHN}
      cTypeFactory *_TypeFactory;
      //## end cProperty::TypeFactory%3C4426CB017F.role

      //## Association: System::Config::<unnamed>%3A5371610321
      //## Role: cProperty::ConfigurationObject%3A5371700340
      //## begin cProperty::ConfigurationObject%3A5371700340.role preserve=no  public: cConfigurationObject {0..n -> 1RFHN}
      cConfigurationObject *_ConfigurationObject;
      //## end cProperty::ConfigurationObject%3A5371700340.role

    // Additional Protected Declarations
      //## begin cProperty%3A542AD30289.protected preserve=yes
      //## end cProperty%3A542AD30289.protected

  private:
    // Additional Private Declarations
      //## begin cProperty%3A542AD30289.private preserve=yes
      //## end cProperty%3A542AD30289.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ConstructValue%1011186743
      STRING_T ConstructValue ();

      //## Operation: ParseValue%1011095978
      void ParseValue (CONST_STRING_T buffer);

      //## Operation: ParseString%1011361700
      void ParseString (CONST_STRING_T buffer, STRING_T &value);

      //## Operation: ParseNumeric%1011361701
      void ParseNumeric (CONST_STRING_T buffer, DOUBLE_T &value);

      //## Operation: ParseVector%1011095989
      BOOL_T ParseVector (CONST_STRING_T buffer, STRING_VECTOR_T &vec);

      //## Operation: ParseVector%1011095990
      BOOL_T ParseVector (CONST_STRING_T buffer, NUMERIC_VECTOR_T &vec);

      //## Operation: BoolValue%1011114951
      BOOL_T BoolValue (CONST_STRING_T value);

      //## Operation: StringList%1011186744
      STRING_T StringList (STRING_VECTOR_T &vec);

      //## Operation: StringList%1011186745
      STRING_T StringList (NUMERIC_VECTOR_T &vec);

      //## Operation: StringList%1011186746
      STRING_T StringList (CONFOBJ_VECTOR_T &vec);

      //## Operation: IsNumeric%1011361702
      BOOL_T IsNumeric (CONST_STRING_T value);

    // Data Members for Class Attributes

      //## Attribute: StringVector%3C4433D9012A
      //## begin cProperty::StringVector%3C4433D9012A.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _StringVector;
      //## end cProperty::StringVector%3C4433D9012A.attr

      //## Attribute: NumericVector%3C4433FA0005
      //## begin cProperty::NumericVector%3C4433FA0005.attr preserve=no  implementation: NUMERIC_VECTOR_T {U} 
      NUMERIC_VECTOR_T _NumericVector;
      //## end cProperty::NumericVector%3C4433FA0005.attr

      //## Attribute: ObjectVector%3C4433FB027D
      //## begin cProperty::ObjectVector%3C4433FB027D.attr preserve=no  implementation: CONFOBJ_VECTOR_T {U} 
      CONFOBJ_VECTOR_T _ObjectVector;
      //## end cProperty::ObjectVector%3C4433FB027D.attr

      //## Attribute: Dirty%3C457BA200E2
      //## begin cProperty::Dirty%3C457BA200E2.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Dirty;
      //## end cProperty::Dirty%3C457BA200E2.attr

    // Additional Implementation Declarations
      //## begin cProperty%3A542AD30289.implementation preserve=yes
      //## end cProperty%3A542AD30289.implementation

};

//## begin cProperty%3A542AD30289.postscript preserve=yes
//## end cProperty%3A542AD30289.postscript

// Class cProperty 

//## begin module%3A542AD30289.epilog preserve=yes
//## end module%3A542AD30289.epilog


#endif
