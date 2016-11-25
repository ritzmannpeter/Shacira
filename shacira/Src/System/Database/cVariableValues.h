//## begin module%41139FF901B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41139FF901B5.cm

//## begin module%41139FF901B5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41139FF901B5.cp

//## Module: cVariableValues%41139FF901B5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVariableValues.h

#ifndef cVariableValues_h
#define cVariableValues_h 1

//## begin module%41139FF901B5.includes preserve=yes
//## end module%41139FF901B5.includes


class __DLL_EXPORT__ cVarDef;

//## begin module%41139FF901B5.additionalDeclarations preserve=yes
//## end module%41139FF901B5.additionalDeclarations


//## begin cVariableValues%41139FF901B5.preface preserve=yes
//## end cVariableValues%41139FF901B5.preface

//## Class: cVariableValues%41139FF901B5
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cVariableValues 
{
  //## begin cVariableValues%41139FF901B5.initialDeclarations preserve=yes
public:
  //## end cVariableValues%41139FF901B5.initialDeclarations

    //## Constructors (generated)
      cVariableValues();

      cVariableValues(const cVariableValues &right);

    //## Constructors (specified)
      //## Operation: cVariableValues%1091802229
      cVariableValues (cVarDef *var_def, ULONG_T size);

    //## Destructor (generated)
      virtual ~cVariableValues();


    //## Other Operations (specified)
      //## Operation: SetValue%1091802230
      void SetValue (ULONG_T pos, CONST_STRING_T value);

      //## Operation: GetValue%1091802231
      STRING_T GetValue (ULONG_T pos);

      //## Operation: Size%1091802233
      ULONG_T Size ();

  public:
    // Additional Public Declarations
      //## begin cVariableValues%41139FF901B5.public preserve=yes
      //## end cVariableValues%41139FF901B5.public

  protected:
    // Data Members for Associations

      //## Association: System::Database::<unnamed>%4113A02D000F
      //## Role: cVariableValues::VarDef%4113A02D030E
      //## begin cVariableValues::VarDef%4113A02D030E.role preserve=no  public: cVarDef {0..1 -> 1RFHN}
      cVarDef *_VarDef;
      //## end cVariableValues::VarDef%4113A02D030E.role

    // Additional Protected Declarations
      //## begin cVariableValues%41139FF901B5.protected preserve=yes
      //## end cVariableValues%41139FF901B5.protected

  private:
    // Additional Private Declarations
      //## begin cVariableValues%41139FF901B5.private preserve=yes
      //## end cVariableValues%41139FF901B5.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Values%4113A2340232
      //## begin cVariableValues::Values%4113A2340232.attr preserve=no  implementation: STRING_VECTOR_T {U} 
      STRING_VECTOR_T _Values;
      //## end cVariableValues::Values%4113A2340232.attr

    // Additional Implementation Declarations
      //## begin cVariableValues%41139FF901B5.implementation preserve=yes
      //## end cVariableValues%41139FF901B5.implementation

};

//## begin cVariableValues%41139FF901B5.postscript preserve=yes
//## end cVariableValues%41139FF901B5.postscript

// Class cVariableValues 

//## begin module%41139FF901B5.epilog preserve=yes
//## end module%41139FF901B5.epilog


#endif
