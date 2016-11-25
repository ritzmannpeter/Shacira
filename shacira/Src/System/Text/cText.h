//## begin module%412B30D300FA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%412B30D300FA.cm

//## begin module%412B30D300FA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%412B30D300FA.cp

//## Module: cText%412B30D300FA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Text\cText.h

#ifndef cText_h
#define cText_h 1

//## begin module%412B30D300FA.includes preserve=yes

#include "System/Database/FuncSpecs.h"

//## end module%412B30D300FA.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"

class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cError;
class __DLL_EXPORT__ cSharedLibrary;
class __DLL_EXPORT__ cTextTable;

//## begin module%412B30D300FA.additionalDeclarations preserve=yes

typedef CONST_STRING_T (*CUSTOM_TEXT_FUNC)(ULONG_T text_id);

//## end module%412B30D300FA.additionalDeclarations


//## begin cText%412B30D300FA.preface preserve=yes
//## end cText%412B30D300FA.preface

//## Class: cText%412B30D300FA
//## Category: System::Text%412B30C4000F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%412B31A1008C;cTextTable { -> F}
//## Uses: <unnamed>%412B3CD70242;cSharedLibrary { -> F}
//## Uses: <unnamed>%412C56670000;cStringUtils { -> F}
//## Uses: <unnamed>%41EBFAED032C;cCustomFunctions { -> }
//## Uses: <unnamed>%42412B2101C5;cError { -> F}

class __DLL_EXPORT__ cText 
{
  //## begin cText%412B30D300FA.initialDeclarations preserve=yes
public:
  //## end cText%412B30D300FA.initialDeclarations

    //## Constructors (generated)
      cText();

      cText(const cText &right);

    //## Destructor (generated)
      virtual ~cText();


    //## Other Operations (specified)
      //## Operation: GetText%1093344845
      static CONST_STRING_T GetText (ULONG_T text_id);

      //## Operation: GetText%1096541411
      static STRING_T GetText (ULONG_T text_id, CONST_STRING_T text);

      //## Operation: GetText%1111566665
      static STRING_T GetText (cError &error);

      //## Operation: Context%1093424351
      static CONST_STRING_T Context (ULONG_T text_id);

    // Data Members for Class Attributes

      //## Attribute: SystemLanguage%42B025010399
      //## begin cText::SystemLanguage%42B025010399.attr preserve=no  public: static STRING_T {U} "de"
      static STRING_T _SystemLanguage;
      //## end cText::SystemLanguage%42B025010399.attr

  public:
    // Additional Public Declarations
      //## begin cText%412B30D300FA.public preserve=yes
      //## end cText%412B30D300FA.public

  protected:
    // Additional Protected Declarations
      //## begin cText%412B30D300FA.protected preserve=yes
      //## end cText%412B30D300FA.protected

  private:
    // Additional Private Declarations
      //## begin cText%412B30D300FA.private preserve=yes
      //## end cText%412B30D300FA.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: TextTable%412B316002BF
      //## begin cText::TextTable%412B316002BF.attr preserve=no  private: static cTextTable * {U} NULL
      static cTextTable *_TextTable;
      //## end cText::TextTable%412B316002BF.attr

      //## Attribute: GetCustomTextFuncAddress%412B39C6037A
      //## begin cText::GetCustomTextFuncAddress%412B39C6037A.attr preserve=no  private: static GET_CUSTOM_TEXT_FUNC_T {U} NULL
      static GET_CUSTOM_TEXT_FUNC_T _GetCustomTextFuncAddress;
      //## end cText::GetCustomTextFuncAddress%412B39C6037A.attr

    // Additional Implementation Declarations
      //## begin cText%412B30D300FA.implementation preserve=yes
      //## end cText%412B30D300FA.implementation

};

//## begin cText%412B30D300FA.postscript preserve=yes
//## end cText%412B30D300FA.postscript

// Class cText 

//## begin module%412B30D300FA.epilog preserve=yes
//## end module%412B30D300FA.epilog


#endif
