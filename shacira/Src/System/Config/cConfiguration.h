//## begin module%3A54333102CF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A54333102CF.cm

//## begin module%3A54333102CF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A54333102CF.cp

//## Module: cConfiguration%3A54333102CF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cConfiguration.h

#ifndef cConfiguration_h
#define cConfiguration_h 1

//## begin module%3A54333102CF.includes preserve=yes
//## end module%3A54333102CF.includes


class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cIniFile;
class __DLL_EXPORT__ cTypeFactory;
class __DLL_EXPORT__ cProperty;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3A54333102CF.additionalDeclarations preserve=yes
//## end module%3A54333102CF.additionalDeclarations


//## begin cConfiguration%3A54333102CF.preface preserve=yes
//## end cConfiguration%3A54333102CF.preface

//## Class: cConfiguration%3A54333102CF
//## Category: System::Config%3A5307460270
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A55D44E02AE;cTokenizer { -> F}
//## Uses: <unnamed>%3B8A7C740265;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3C4421C00038;cProperty { -> F}
//## Uses: <unnamed>%3DD0E5F402A7;cIniFile { -> F}

class __DLL_EXPORT__ cConfiguration 
{
  //## begin cConfiguration%3A54333102CF.initialDeclarations preserve=yes
public:
  //## end cConfiguration%3A54333102CF.initialDeclarations

    //## Constructors (generated)
      cConfiguration();

      cConfiguration(const cConfiguration &right);

    //## Constructors (specified)
      //## Operation: cConfiguration%1011095973
      cConfiguration (CONST_STRING_T config_file_name);

    //## Destructor (generated)
      virtual ~cConfiguration();


    //## Other Operations (specified)
      //## Operation: TypeFactory%1011095976
      cTypeFactory * TypeFactory () const;

      //## Operation: Object%978594334
      cConfigurationObject * Object (CONST_STRING_T name) const;

      //## Operation: ObjectList%1011204313
      ULONG_T ObjectList (STRING_LIST_T &object_list, CONST_STRING_T type_name = NULL);

      //## Operation: Resolve%1011095991
      void Resolve ();

      //## Operation: Save%978594328
      void Save ();

      //## Operation: DefaultConfigFile%1037033504
      static CONST_STRING_T DefaultConfigFile ();

  public:
    // Additional Public Declarations
      //## begin cConfiguration%3A54333102CF.public preserve=yes
      //## end cConfiguration%3A54333102CF.public

  protected:
    // Data Members for Associations

      //## Association: System::Config::<unnamed>%3C44195B018C
      //## Role: cConfiguration::TypeFactory%3C44195C038D
      //## begin cConfiguration::TypeFactory%3C44195C038D.role preserve=no  public: cTypeFactory { -> 1RFHN}
      cTypeFactory *_TypeFactory;
      //## end cConfiguration::TypeFactory%3C44195C038D.role

      //## Association: System::Config::<unnamed>%3A5433760274
      //## Role: cConfiguration::ConfigurationObjects%3A5433770262
      //## Qualifier: name%3A5434A90289; STRING_T
      //## begin cConfiguration::ConfigurationObjects%3A5433770262.role preserve=no  public: cConfigurationObject {1 -> 0..nRFHN}
      std::map<STRING_T, cConfigurationObject*> _ConfigurationObjects;
      //## end cConfiguration::ConfigurationObjects%3A5433770262.role

    // Additional Protected Declarations
      //## begin cConfiguration%3A54333102CF.protected preserve=yes
      //## end cConfiguration%3A54333102CF.protected

  private:
    // Additional Private Declarations
      //## begin cConfiguration%3A54333102CF.private preserve=yes
      //## end cConfiguration%3A54333102CF.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: AddPath%1037033505
      void AddPath (CONST_STRING_T path);

      //## Operation: Load%1037033506
      void Load (CONST_STRING_T config_file_name);

      //## Operation: LoadFile%1011171077
      BOOL_T LoadFile (CONST_STRING_T config_file);

    // Data Members for Class Attributes

      //## Attribute: Path%3DCFE2DA02C1
      //## begin cConfiguration::Path%3DCFE2DA02C1.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Path;
      //## end cConfiguration::Path%3DCFE2DA02C1.attr

    // Additional Implementation Declarations
      //## begin cConfiguration%3A54333102CF.implementation preserve=yes
      //## end cConfiguration%3A54333102CF.implementation

};

//## begin cConfiguration%3A54333102CF.postscript preserve=yes
//## end cConfiguration%3A54333102CF.postscript

// Class cConfiguration 

//## begin module%3A54333102CF.epilog preserve=yes
//## end module%3A54333102CF.epilog


#endif
