//## begin module%3C4305A10207.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4305A10207.cm

//## begin module%3C4305A10207.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4305A10207.cp

//## Module: cPropertyDef%3C4305A10207; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cPropertyDef.h

#ifndef cPropertyDef_h
#define cPropertyDef_h 1

//## begin module%3C4305A10207.includes preserve=yes
//## end module%3C4305A10207.includes


class __DLL_EXPORT__ cTypeFactory;
class __DLL_EXPORT__ cTypeDef;

//## begin module%3C4305A10207.additionalDeclarations preserve=yes
//## end module%3C4305A10207.additionalDeclarations


//## begin cPropertyDef%3C4305A10207.preface preserve=yes
//## end cPropertyDef%3C4305A10207.preface

//## Class: cPropertyDef%3C4305A10207
//## Category: System::Config%3A5307460270
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPropertyDef 
{
  //## begin cPropertyDef%3C4305A10207.initialDeclarations preserve=yes
public:
  //## end cPropertyDef%3C4305A10207.initialDeclarations

    //## Constructors (generated)
      cPropertyDef();

      cPropertyDef(const cPropertyDef &right);

    //## Constructors (specified)
      //## Operation: cPropertyDef%1011021290
      cPropertyDef (CONST_STRING_T name, CONST_STRING_T type_spec, cTypeFactory *type_factory);

    //## Destructor (generated)
      virtual ~cPropertyDef();


    //## Other Operations (specified)
      //## Operation: TypeDef%1011095987
      cTypeDef * TypeDef ();

      //## Operation: Resolve%1011021293
      void Resolve ();

      //## Operation: operator CONST_STRING_T%1011021297
      virtual operator CONST_STRING_T ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%3C4306600251
      STRING_T get_Name () const;

      //## Attribute: IsVector%3C43085F0397
      BOOL_T get_IsVector () const;

      //## Attribute: DefName%3C430C1D0091
      STRING_T get_DefName () const;

  public:
    // Additional Public Declarations
      //## begin cPropertyDef%3C4305A10207.public preserve=yes
      //## end cPropertyDef%3C4305A10207.public

  protected:
    // Data Members for Class Attributes

      //## begin cPropertyDef::Name%3C4306600251.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cPropertyDef::Name%3C4306600251.attr

      //## begin cPropertyDef::IsVector%3C43085F0397.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsVector;
      //## end cPropertyDef::IsVector%3C43085F0397.attr

      //## begin cPropertyDef::DefName%3C430C1D0091.attr preserve=no  public: STRING_T {U} 
      STRING_T _DefName;
      //## end cPropertyDef::DefName%3C430C1D0091.attr

    // Data Members for Associations

      //## Association: System::Config::<unnamed>%3C4477B403B3
      //## Role: cPropertyDef::TypeDef%3C4477B502BB
      //## begin cPropertyDef::TypeDef%3C4477B502BB.role preserve=no  public: cTypeDef {0..n -> 1RFHN}
      cTypeDef *_TypeDef;
      //## end cPropertyDef::TypeDef%3C4477B502BB.role

      //## Association: System::Config::<unnamed>%3C4476E40242
      //## Role: cPropertyDef::TypeFactory%3C4476E600B5
      //## begin cPropertyDef::TypeFactory%3C4476E600B5.role preserve=no  public: cTypeFactory { -> 1RFHN}
      cTypeFactory *_TypeFactory;
      //## end cPropertyDef::TypeFactory%3C4476E600B5.role

    // Additional Protected Declarations
      //## begin cPropertyDef%3C4305A10207.protected preserve=yes
      //## end cPropertyDef%3C4305A10207.protected

  private:
    // Additional Private Declarations
      //## begin cPropertyDef%3C4305A10207.private preserve=yes
      //## end cPropertyDef%3C4305A10207.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ParseTypeSpec%1011021294
      void ParseTypeSpec (CONST_STRING_T type_spec);

    // Data Members for Class Attributes

      //## Attribute: Text%3C431EE60259
      //## begin cPropertyDef::Text%3C431EE60259.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _Text;
      //## end cPropertyDef::Text%3C431EE60259.attr

    // Additional Implementation Declarations
      //## begin cPropertyDef%3C4305A10207.implementation preserve=yes
      //## end cPropertyDef%3C4305A10207.implementation

};

//## begin cPropertyDef%3C4305A10207.postscript preserve=yes
//## end cPropertyDef%3C4305A10207.postscript

// Class cPropertyDef 

//## begin module%3C4305A10207.epilog preserve=yes
//## end module%3C4305A10207.epilog


#endif
