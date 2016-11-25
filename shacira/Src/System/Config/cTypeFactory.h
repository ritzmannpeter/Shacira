//## begin module%3C42C8DA0041.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C42C8DA0041.cm

//## begin module%3C42C8DA0041.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C42C8DA0041.cp

//## Module: cTypeFactory%3C42C8DA0041; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cTypeFactory.h

#ifndef cTypeFactory_h
#define cTypeFactory_h 1

//## begin module%3C42C8DA0041.includes preserve=yes
//## end module%3C42C8DA0041.includes

// cError
#include "System/cError.h"

class __DLL_EXPORT__ cTokenizer;
class __DLL_EXPORT__ cIniFile;
class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cTypeDef;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3C42C8DA0041.additionalDeclarations preserve=yes
//## end module%3C42C8DA0041.additionalDeclarations


//## begin cTypeFactory%3C42C8DA0041.preface preserve=yes
//## end cTypeFactory%3C42C8DA0041.preface

//## Class: cTypeFactory%3C42C8DA0041
//## Category: System::Config%3A5307460270
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C42D4FB0321;cError { -> }
//## Uses: <unnamed>%3C442FAA01AC;cTokenizer { -> F}
//## Uses: <unnamed>%3DCA4EA2028B;cStringUtils { -> F}
//## Uses: <unnamed>%3DD0D31401AF;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3DD0E6080152;cIniFile { -> F}

class __DLL_EXPORT__ cTypeFactory 
{
  //## begin cTypeFactory%3C42C8DA0041.initialDeclarations preserve=yes
public:
  //## end cTypeFactory%3C42C8DA0041.initialDeclarations

    //## Constructors (generated)
      cTypeFactory();

      cTypeFactory(const cTypeFactory &right);

    //## Constructors (specified)
      //## Operation: cTypeFactory%1011171075
      cTypeFactory (CONST_STRING_T def_file, STRING_VECTOR_T path);

    //## Destructor (generated)
      virtual ~cTypeFactory();


    //## Other Operations (specified)
      //## Operation: BaseType%1011013290
      BaseTypes BaseType (CONST_STRING_T name);

      //## Operation: Definition%1011013292
      cTypeDef * Definition (CONST_STRING_T name);

      //## Operation: ParseList%1011095979
      static BOOL_T ParseList (CONST_STRING_T buffer, STRING_LIST_T &string_list);

      //## Operation: ParseList%1011095980
      static BOOL_T ParseList (CONST_STRING_T buffer, DOUBLE_LIST_T &real_list);

      //## Operation: ParseRange%1011095981
      static BOOL_T ParseRange (CONST_STRING_T buffer, DOUBLE_T &min, DOUBLE_T &max);

      //## Operation: ParseType%1011095982
      void ParseType (CONST_STRING_T buffer, STRING_T &type_name, BOOL_T &is_vector);

  public:
    // Additional Public Declarations
      //## begin cTypeFactory%3C42C8DA0041.public preserve=yes
      //## end cTypeFactory%3C42C8DA0041.public

  protected:
    // Data Members for Associations

      //## Association: System::Config::<unnamed>%3C44772B0276
      //## Role: cTypeFactory::TypeDefs%3C44772C02DB
      //## Qualifier: name%3C44778C0058; STRING_T
      //## begin cTypeFactory::TypeDefs%3C44772C02DB.role preserve=no  public: cTypeDef {1 -> 0..nRFHN}
      std::map<STRING_T, cTypeDef*> _TypeDefs;
      //## end cTypeFactory::TypeDefs%3C44772C02DB.role

    // Additional Protected Declarations
      //## begin cTypeFactory%3C42C8DA0041.protected preserve=yes
      //## end cTypeFactory%3C42C8DA0041.protected

  private:
    // Additional Private Declarations
      //## begin cTypeFactory%3C42C8DA0041.private preserve=yes
      //## end cTypeFactory%3C42C8DA0041.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Load%1011013289
      void Load (CONST_STRING_T def_file_name, STRING_VECTOR_T &path);

      //## Operation: LoadFile%1037089035
      BOOL_T LoadFile (CONST_STRING_T def_file);

      //## Operation: AddBasicTypes%1011021295
      void AddBasicTypes ();

    // Data Members for Class Attributes

      //## Attribute: Text%3C431EC201CB
      //## begin cTypeFactory::Text%3C431EC201CB.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Text;
      //## end cTypeFactory::Text%3C431EC201CB.attr

      //## Attribute: DefFile%3CA35A060080
      //## begin cTypeFactory::DefFile%3CA35A060080.attr preserve=no  implementation: STRING_T {U} "Shacira.def"
      STRING_T _DefFile;
      //## end cTypeFactory::DefFile%3CA35A060080.attr

    // Additional Implementation Declarations
      //## begin cTypeFactory%3C42C8DA0041.implementation preserve=yes
      //## end cTypeFactory%3C42C8DA0041.implementation

};

//## begin cTypeFactory%3C42C8DA0041.postscript preserve=yes
//## end cTypeFactory%3C42C8DA0041.postscript

// Class cTypeFactory 

//## begin module%3C42C8DA0041.epilog preserve=yes
//## end module%3C42C8DA0041.epilog


#endif
