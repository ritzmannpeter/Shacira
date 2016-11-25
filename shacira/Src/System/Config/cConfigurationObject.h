//## begin module%3A530768030F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A530768030F.cm

//## begin module%3A530768030F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A530768030F.cp

//## Module: cConfigurationObject%3A530768030F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cConfigurationObject.h

#ifndef cConfigurationObject_h
#define cConfigurationObject_h 1

//## begin module%3A530768030F.includes preserve=yes
//## end module%3A530768030F.includes

// cProperty
#include "System/Config/cProperty.h"

class __DLL_EXPORT__ cTypeFactory;
class __DLL_EXPORT__ cTypeDef;
class __DLL_EXPORT__ cConfiguration;

//## begin module%3A530768030F.additionalDeclarations preserve=yes

#define NULL_OBJECT ((cConfigurationObject*)NULL)

//## end module%3A530768030F.additionalDeclarations


//## begin cConfigurationObject%3A530768030F.preface preserve=yes
#define _CHECK_CONFIG_OBJECT_(object) \
if (object == NULL) { \
   throw cError(CONFIG_NO_OBJECT); \
}
//## end cConfigurationObject%3A530768030F.preface

//## Class: cConfigurationObject%3A530768030F
//## Category: System::Config%3A5307460270
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C44676D02AD;cProperty { -> }

class __DLL_EXPORT__ cConfigurationObject 
{
  //## begin cConfigurationObject%3A530768030F.initialDeclarations preserve=yes
public:
  //## end cConfigurationObject%3A530768030F.initialDeclarations

    //## Constructors (generated)
      cConfigurationObject();

      cConfigurationObject(const cConfigurationObject &right);

    //## Constructors (specified)
      //## Operation: cConfigurationObject%978518090
      cConfigurationObject (cConfiguration *configuration, CONST_STRING_T name, CONST_STRING_T type_name, CONST_STRING_T source);

    //## Destructor (generated)
      virtual ~cConfigurationObject();


    //## Other Operations (specified)
      //## Operation: Configuration%1011095977
      cConfiguration * Configuration () const;

      //## Operation: TypeDef%1011095988
      cTypeDef * TypeDef ();

      //## Operation: IsRoot%1011204314
      BOOL_T IsRoot ();

      //## Operation: SetProperty%1011095975
      void SetProperty (cProperty *property);

      //## Operation: Resolve%1011095993
      void Resolve ();

      //## Operation: Save%1011186742
      void Save ();

      //## Operation: Property%978594336
      cProperty * Property (CONST_STRING_T name) const;

      //## Operation: PropertyList%980778564
      ULONG_T PropertyList (STRING_LIST_T &property_list);

      //## Operation: PropertyValue%980256062
      DOUBLE_T PropertyValue (CONST_STRING_T name, DOUBLE_T default_value, BOOL_T mandatory = false);

      //## Operation: PropertyValue%1011095974
      LONG_T PropertyValue (CONST_STRING_T name, LONG_T default_value, BOOL_T mandatory = false);

      //## Operation: PropertyValue%1011276241
      ULONG_T PropertyValue (CONST_STRING_T name, ULONG_T default_value, BOOL_T mandatory = false);

      //## Operation: PropertyValue%980256064
      BOOL_T PropertyValue (CONST_STRING_T name, BOOL_T default_value, BOOL_T mandatory = false);

      //## Operation: PropertyValue%980256065
      STRING_T PropertyValue (CONST_STRING_T name, CONST_STRING_T default_value, BOOL_T mandatory = false);

      //## Operation: PropertyValue%981360505
      cConfigurationObject * PropertyValue (CONST_STRING_T name, cConfigurationObject *default_value, BOOL_T mandatory = false);

      //## Operation: PropertyValue%1011114948
      INT_T PropertyValue (CONST_STRING_T name, STRING_VECTOR_T &vec, BOOL_T mandatory = false);

      //## Operation: PropertyValue%1011114949
      INT_T PropertyValue (CONST_STRING_T name, NUMERIC_VECTOR_T &vec, BOOL_T mandatory = false);

      //## Operation: PropertyValue%1011114950
      INT_T PropertyValue (CONST_STRING_T name, CONFOBJ_VECTOR_T &vec, BOOL_T mandatory = false);

      //## Operation: SetPropertyValue%1011186740
      void SetPropertyValue (CONST_STRING_T name, CONST_STRING_T value, ULONG_T index = 0);

      //## Operation: SetPropertyValue%1011186752
      void SetPropertyValue (CONST_STRING_T name, DOUBLE_T value, ULONG_T index = 0);

      //## Operation: SetPropertyValue%1011186755
      void SetPropertyValue (CONST_STRING_T name, LONG_T value, ULONG_T index = 0);

      //## Operation: SetPropertyValue%1011276242
      void SetPropertyValue (CONST_STRING_T name, ULONG_T value, ULONG_T index = 0);

      //## Operation: SetPropertyValue%1011186753
      void SetPropertyValue (CONST_STRING_T name, cConfigurationObject *value, ULONG_T index = 0);

      //## Operation: SetPropertyValue%1011186754
      void SetPropertyValue (CONST_STRING_T name, BOOL_T value, ULONG_T index = 0);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%3A5307CA019D
      STRING_T get_Name () const;

      //## Attribute: TypeName%3C45D6A101BF
      STRING_T get_TypeName () const;

      //## Attribute: Source%3A542F2600F0
      STRING_T get_Source () const;
      void set_Source (STRING_T value);

      //## Attribute: HasChildren%3C45C6EE02E2
      BOOL_T get_HasChildren () const;
      void set_HasChildren (BOOL_T value);

      //## Attribute: Referenced%3C45D4EC029D
      BOOL_T get_Referenced () const;
      void set_Referenced (BOOL_T value);

  public:
    // Additional Public Declarations
      //## begin cConfigurationObject%3A530768030F.public preserve=yes
      //## end cConfigurationObject%3A530768030F.public

  protected:
    // Data Members for Class Attributes

      //## begin cConfigurationObject::Name%3A5307CA019D.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cConfigurationObject::Name%3A5307CA019D.attr

      //## begin cConfigurationObject::TypeName%3C45D6A101BF.attr preserve=no  public: STRING_T {U} 
      STRING_T _TypeName;
      //## end cConfigurationObject::TypeName%3C45D6A101BF.attr

      //## begin cConfigurationObject::Source%3A542F2600F0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Source;
      //## end cConfigurationObject::Source%3A542F2600F0.attr

      //## begin cConfigurationObject::HasChildren%3C45C6EE02E2.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _HasChildren;
      //## end cConfigurationObject::HasChildren%3C45C6EE02E2.attr

      //## begin cConfigurationObject::Referenced%3C45D4EC029D.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Referenced;
      //## end cConfigurationObject::Referenced%3C45D4EC029D.attr

    // Data Members for Associations

      //## Association: System::Config::<unnamed>%3A5433760274
      //## Role: cConfigurationObject::Configuration%3A5433770261
      //## begin cConfigurationObject::Configuration%3A5433770261.role preserve=no  public: cConfiguration {0..n -> 1RFHN}
      cConfiguration *_Configuration;
      //## end cConfigurationObject::Configuration%3A5433770261.role

      //## Association: System::Config::<unnamed>%3A5371610321
      //## Role: cConfigurationObject::Properties%3A5371700336
      //## Qualifier: name%3A53756E01E1; STRING_T
      //## begin cConfigurationObject::Properties%3A5371700336.role preserve=no  public: cProperty {1 -> 0..nRFHN}
      std::map<STRING_T, cProperty*> _Properties;
      //## end cConfigurationObject::Properties%3A5371700336.role

      //## Association: System::Config::<unnamed>%3C4419BF0031
      //## Role: cConfigurationObject::TypeDef%3C4419BF03D5
      //## begin cConfigurationObject::TypeDef%3C4419BF03D5.role preserve=no  public: cTypeDef { -> 1RFHN}
      cTypeDef *_TypeDef;
      //## end cConfigurationObject::TypeDef%3C4419BF03D5.role

      //## Association: System::Config::<unnamed>%3C44269E017A
      //## Role: cConfigurationObject::TypeFactory%3C4426A001F5
      //## begin cConfigurationObject::TypeFactory%3C4426A001F5.role preserve=no  public: cTypeFactory { -> 1RFHN}
      cTypeFactory *_TypeFactory;
      //## end cConfigurationObject::TypeFactory%3C4426A001F5.role

    // Additional Protected Declarations
      //## begin cConfigurationObject%3A530768030F.protected preserve=yes
      //## end cConfigurationObject%3A530768030F.protected

  private:
    // Additional Private Declarations
      //## begin cConfigurationObject%3A530768030F.private preserve=yes
      //## end cConfigurationObject%3A530768030F.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Property%980256069
      cProperty * Property (CONST_STRING_T name, BOOL_T mandatory);

    // Additional Implementation Declarations
      //## begin cConfigurationObject%3A530768030F.implementation preserve=yes
      //## end cConfigurationObject%3A530768030F.implementation

};

//## begin cConfigurationObject%3A530768030F.postscript preserve=yes
//## end cConfigurationObject%3A530768030F.postscript

// Class cConfigurationObject 

//## begin module%3A530768030F.epilog preserve=yes
//## end module%3A530768030F.epilog


#endif
