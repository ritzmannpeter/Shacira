//## begin module%3E072E3F00DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E072E3F00DA.cm

//## begin module%3E072E3F00DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E072E3F00DA.cp

//## Module: cSDDLParser%3E072E3F00DA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Language\cSDDLParser.h

#ifndef cSDDLParser_h
#define cSDDLParser_h 1

//## begin module%3E072E3F00DA.includes preserve=yes
//## end module%3E072E3F00DA.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cMapping
#include "System/Database/cMapping.h"
// cFuncRefArg
#include "System/Database/cFuncRefArg.h"
// cVarRefArg
#include "System/Database/cVarRefArg.h"
// cConstReal
#include "System/Database/cConstReal.h"
// cConstInt
#include "System/Database/cConstInt.h"
// cConstString
#include "System/Database/cConstString.h"
// cFuncDecl
#include "System/Database/cFuncDecl.h"
// cFuncRef
#include "System/Database/cFuncRef.h"

class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cFileSystemUtils;

//## begin module%3E072E3F00DA.additionalDeclarations preserve=yes
//## end module%3E072E3F00DA.additionalDeclarations


//## begin cSDDLParser%3E072E3F00DA.preface preserve=yes
//## end cSDDLParser%3E072E3F00DA.preface

//## Class: cSDDLParser%3E072E3F00DA
//## Category: Language%3E0C4A4402CD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E072FB60256;cVarRef { -> }
//## Uses: <unnamed>%3E072FDF02EB;cFuncDecl { -> }
//## Uses: <unnamed>%3E072FFF01F7;cFuncRef { -> }
//## Uses: <unnamed>%3E0749960124;cContext { -> }
//## Uses: <unnamed>%3E0753390140;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3E0753460365;cConvUtils { -> F}
//## Uses: <unnamed>%3E0C92E802C2;cConstString { -> }
//## Uses: <unnamed>%3E0C92EB035D;cConstInt { -> }
//## Uses: <unnamed>%3E0C92EF00B0;cVarRefArg { -> }
//## Uses: <unnamed>%3E0C92F10384;cFuncRefArg { -> }
//## Uses: <unnamed>%3E0C942E0357;cConstReal { -> }
//## Uses: <unnamed>%3E0C9BAE03C6;cVarDef { -> }
//## Uses: <unnamed>%3E100C73039B;cMapping { -> }

class __DLL_EXPORT__ cSDDLParser 
{
  //## begin cSDDLParser%3E072E3F00DA.initialDeclarations preserve=yes
public:
  //## end cSDDLParser%3E072E3F00DA.initialDeclarations

    //## Constructors (generated)
      cSDDLParser();

      cSDDLParser(const cSDDLParser &right);

    //## Destructor (generated)
      virtual ~cSDDLParser();


    //## Other Operations (specified)
      //## Operation: ParseDatabaseFromFile%1041261880
      virtual BOOL_T ParseDatabaseFromFile (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false) = 0;

      //## Operation: ParseDatabaseFromString%1041261881
      virtual BOOL_T ParseDatabaseFromString (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false) = 0;

      //## Operation: ParseDBLiteFromString%1102338846
      virtual BOOL_T ParseDBLiteFromString (cContext *context, CONST_STRING_T source) = 0;

      //## Operation: FuncRef%1040992338
      virtual cFuncRef * FuncRef (cContext *context, CONST_STRING_T source, UCHAR_T requested_data_type = UNDEFINED, UCHAR_T requested_class = UNDEFINED) = 0;

      //## Operation: VarRef%1040992339
      virtual cVarRef * VarRef (cContext *context, CONST_STRING_T source, UCHAR_T requested_data_type = UNDEFINED) = 0;

      //## Operation: ParseProgramFromFile%1060622591
      virtual void ParseProgramFromFile (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false) = 0;

      //## Operation: ParseProgramFromString%1060622592
      virtual void ParseProgramFromString (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false) = 0;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IgnoreMapping%3E0C59F701DB
      BOOL_T get_IgnoreMapping () const;
      void set_IgnoreMapping (BOOL_T value);

      //## Attribute: IgnoreDataDefinitions%40EE4F390213
      BOOL_T get_IgnoreDataDefinitions () const;
      void set_IgnoreDataDefinitions (BOOL_T value);

      //## Attribute: IDEActive%420CD01503B9
      BOOL_T get_IDEActive () const;
      void set_IDEActive (BOOL_T value);

      //## Attribute: Steps%434D2D220027
      int get_Steps () const;
      void set_Steps (int value);

      //## Attribute: File%43A7EF0D02E0
      STRING_T get_File () const;

      //## Attribute: Line%43A7EF0D02E1
      int get_Line () const;

      //## Attribute: Column%43A7EF0D02EF
      int get_Column () const;

      //## Attribute: ErrorText%43A7EF0D02F0
      STRING_T get_ErrorText () const;

  public:
    // Additional Public Declarations
      //## begin cSDDLParser%3E072E3F00DA.public preserve=yes
      //## end cSDDLParser%3E072E3F00DA.public

  protected:

    //## Other Operations (specified)
      //## Operation: NewMapItem%1072085856
      MAP_ITEM_T * NewMapItem (MAP_ITEM_T *base_item = NULL);

      //## Operation: CopyName%1075748781
      CONST_STRING_T CopyName (STRING_T name);

    // Data Members for Class Attributes

      //## begin cSDDLParser::IgnoreMapping%3E0C59F701DB.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IgnoreMapping;
      //## end cSDDLParser::IgnoreMapping%3E0C59F701DB.attr

      //## begin cSDDLParser::IgnoreDataDefinitions%40EE4F390213.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IgnoreDataDefinitions;
      //## end cSDDLParser::IgnoreDataDefinitions%40EE4F390213.attr

      //## begin cSDDLParser::IDEActive%420CD01503B9.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IDEActive;
      //## end cSDDLParser::IDEActive%420CD01503B9.attr

      //## begin cSDDLParser::Steps%434D2D220027.attr preserve=no  public: int {U} 0
      int _Steps;
      //## end cSDDLParser::Steps%434D2D220027.attr

      //## Attribute: ActDatabaseName%3FE6F9220261
      //## begin cSDDLParser::ActDatabaseName%3FE6F9220261.attr preserve=no  protected: CONST_STRING_T {U} NULL
      STRING_T _ActDatabaseName;
      //## end cSDDLParser::ActDatabaseName%3FE6F9220261.attr

      //## Attribute: ActDeviceName%41160BF30232
      //## begin cSDDLParser::ActDeviceName%41160BF30232.attr preserve=no  protected: CONST_STRING_T {U} NULL
      STRING_T _ActDeviceName;
      //## end cSDDLParser::ActDeviceName%41160BF30232.attr

      //## Attribute: Dynamic%40F94B9B0251
      //## begin cSDDLParser::Dynamic%40F94B9B0251.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Dynamic;
      //## end cSDDLParser::Dynamic%40F94B9B0251.attr

      //## Attribute: Optimized%4134BC0F0251
      //## begin cSDDLParser::Optimized%4134BC0F0251.attr preserve=no  protected: static BOOL_T {U} true
      static BOOL_T _Optimized;
      //## end cSDDLParser::Optimized%4134BC0F0251.attr

      //## Attribute: Step%434D2D7B01E9
      //## begin cSDDLParser::Step%434D2D7B01E9.attr preserve=no  protected: int {U} 0
      int _Step;
      //## end cSDDLParser::Step%434D2D7B01E9.attr

      //## begin cSDDLParser::File%43A7EF0D02E0.attr preserve=no  public: STRING_T {U} 
      STRING_T _File;
      //## end cSDDLParser::File%43A7EF0D02E0.attr

      //## begin cSDDLParser::Line%43A7EF0D02E1.attr preserve=no  public: int {U} -1
      int _Line;
      //## end cSDDLParser::Line%43A7EF0D02E1.attr

      //## begin cSDDLParser::Column%43A7EF0D02EF.attr preserve=no  public: int {U} -1
      int _Column;
      //## end cSDDLParser::Column%43A7EF0D02EF.attr

      //## begin cSDDLParser::ErrorText%43A7EF0D02F0.attr preserve=no  public: STRING_T {U} 
      STRING_T _ErrorText;
      //## end cSDDLParser::ErrorText%43A7EF0D02F0.attr

    // Additional Protected Declarations
      //## begin cSDDLParser%3E072E3F00DA.protected preserve=yes
      //## end cSDDLParser%3E072E3F00DA.protected

  private:
    // Additional Private Declarations
      //## begin cSDDLParser%3E072E3F00DA.private preserve=yes
      //## end cSDDLParser%3E072E3F00DA.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSDDLParser%3E072E3F00DA.implementation preserve=yes
      //## end cSDDLParser%3E072E3F00DA.implementation

};

//## begin cSDDLParser%3E072E3F00DA.postscript preserve=yes
//## end cSDDLParser%3E072E3F00DA.postscript

// Class cSDDLParser 

//## begin module%3E072E3F00DA.epilog preserve=yes
//## end module%3E072E3F00DA.epilog


#endif
