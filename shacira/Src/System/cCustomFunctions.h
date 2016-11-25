//## begin module%41E6A80D000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41E6A80D000F.cm

//## begin module%41E6A80D000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41E6A80D000F.cp

//## Module: cCustomFunctions%41E6A80D000F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\cCustomFunctions.h

#ifndef cCustomFunctions_h
#define cCustomFunctions_h 1

//## begin module%41E6A80D000F.includes preserve=yes

#include "System/Database/FuncSpecs.h"

class cDevice;
class cProgram;
class cConfigurationObject;
class cCell;
class cContext;
class cLocalContext;
class CAppFrame;
class cTransientObject;
class cVarDef;

typedef cDevice * (*DEV_FACTORY_T)(cConfigurationObject * config_obj, cCell *cell);
typedef cProgram * (*PROG_FACTORY_T)(cConfigurationObject * config_obj, cContext *context);
typedef BOOL_T (*MDL_INIT_FUNC_T)(ULONG_T step, cLocalContext * context);
typedef BOOL_T (*GUI_INIT_FUNC_T)(ULONG_T step, cContext * context);
typedef VOID_FUNC_T (*FUNC_FACTORY_T)(UCHAR_T func_class, CONST_STRING_T func_name);
typedef CONST_STRING_T (*GET_CUSTOM_TEXT_FUNC_T)(ULONG_T text_id);
typedef void (*SHARE_APPFRAME_FUNC_T)(CAppFrame * app_frame);
typedef cTransientObject * (*OBJECT_FACTORY_T)(CONST_STRING_T serialized_obj);
typedef ULONG_T (*VARDEF_FILTER_T)(cContext * context, ULONG_T if_type, cVarDef * var_def);

extern "C" {
extern VOID_FUNC_T _GUIFuncAddr(UCHAR_T func_class, CONST_STRING_T func_name);
extern VOID_FUNC_T _MdlFuncAddr(UCHAR_T func_class, CONST_STRING_T func_name);
extern BOOL_T _MdlInit(ULONG_T step, cLocalContext * context);
extern BOOL_T _GUIInit(ULONG_T step, cContext * context);
extern cDevice * _CreateDevice(cConfigurationObject * config_obj, cCell * cell);
extern cProgram * _CreateProgram(cConfigurationObject * config_obj, cContext * context);
extern CONST_STRING_T _GetCustomText(ULONG_T text_id);
extern void _ShareAppframe(CAppFrame * app_frame);
extern cTransientObject * _ConstructObject(CONST_STRING_T serialized_obj);
extern ULONG_T _VarDefFilter(cContext * context, ULONG_T if_type, cVarDef * var_def);
}

//## end module%41E6A80D000F.includes

//## begin module%41E6A80D000F.additionalDeclarations preserve=yes
//## end module%41E6A80D000F.additionalDeclarations


//## begin cCustomFunctions%41E6A80D000F.preface preserve=yes
//## end cCustomFunctions%41E6A80D000F.preface

//## Class: cCustomFunctions%41E6A80D000F
//## Category: System%378A0C210153
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCustomFunctions 
{
  //## begin cCustomFunctions%41E6A80D000F.initialDeclarations preserve=yes
public:
  //## end cCustomFunctions%41E6A80D000F.initialDeclarations

    //## Constructors (generated)
      cCustomFunctions();

      cCustomFunctions(const cCustomFunctions &right);

    //## Destructor (generated)
      virtual ~cCustomFunctions();


    //## Other Operations (specified)
      //## Operation: GUIFuncFactoryAddress%1105635916
      static FUNC_FACTORY_T GUIFuncFactoryAddress ();

      //## Operation: GUIInitFuncAddress%1105635917
      static GUI_INIT_FUNC_T GUIInitFuncAddress ();

      //## Operation: MdlFuncFactoryAddress%1105635918
      static FUNC_FACTORY_T MdlFuncFactoryAddress ();

      //## Operation: MdlInitFuncAddress%1105635919
      static MDL_INIT_FUNC_T MdlInitFuncAddress ();

      //## Operation: GetCustomTextFuncAddress%1105635920
      static GET_CUSTOM_TEXT_FUNC_T GetCustomTextFuncAddress ();

      //## Operation: DeviceCreatorFuncAddress%1105635921
      static DEV_FACTORY_T DeviceCreatorFuncAddress ();

      //## Operation: ProgramCreatorFuncAddress%1105635922
      static PROG_FACTORY_T ProgramCreatorFuncAddress ();

      //## Operation: ShareAppframeFuncAddress%1106141849
      static SHARE_APPFRAME_FUNC_T ShareAppframeFuncAddress ();

      //## Operation: ConstructObjectFuncAddress%1125156841
      static OBJECT_FACTORY_T ConstructObjectFuncAddress ();

      //## Operation: VarDefFilterFuncAddress%1132945090
      static VARDEF_FILTER_T VarDefFilterFuncAddress ();

      //## Operation: GUIFuncFactoryAddress%1105635923
      static void GUIFuncFactoryAddress (FUNC_FACTORY_T address);

      //## Operation: GUIInitFuncAddress%1105635924
      static void GUIInitFuncAddress (GUI_INIT_FUNC_T address);

      //## Operation: MdlFuncFactoryAddress%1105635925
      static void MdlFuncFactoryAddress (FUNC_FACTORY_T address);

      //## Operation: MdlInitFuncAddress%1105635926
      static void MdlInitFuncAddress (MDL_INIT_FUNC_T address);

      //## Operation: GetCustomTextFuncAddress%1105635927
      static void GetCustomTextFuncAddress (GET_CUSTOM_TEXT_FUNC_T address);

      //## Operation: DeviceCreatorFuncAddress%1105635928
      static void DeviceCreatorFuncAddress (DEV_FACTORY_T address);

      //## Operation: ProgramCreatorFuncAddress%1105635929
      static void ProgramCreatorFuncAddress (PROG_FACTORY_T address);

      //## Operation: ShareAppframeFuncAddress%1106141850
      static void ShareAppframeFuncAddress (SHARE_APPFRAME_FUNC_T address);

      //## Operation: ConstructObjectFuncAddress%1125156842
      static void ConstructObjectFuncAddress (OBJECT_FACTORY_T address);

      //## Operation: VarDefFilterFuncAddress%1132945091
      static void VarDefFilterFuncAddress (VARDEF_FILTER_T address);

  public:
    // Additional Public Declarations
      //## begin cCustomFunctions%41E6A80D000F.public preserve=yes
      //## end cCustomFunctions%41E6A80D000F.public

  protected:
    // Additional Protected Declarations
      //## begin cCustomFunctions%41E6A80D000F.protected preserve=yes
      //## end cCustomFunctions%41E6A80D000F.protected

  private:
    // Additional Private Declarations
      //## begin cCustomFunctions%41E6A80D000F.private preserve=yes
      //## end cCustomFunctions%41E6A80D000F.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: GUIFuncFactoryAddress%41E6BACC01B5
      //## begin cCustomFunctions::GUIFuncFactoryAddress%41E6BACC01B5.attr preserve=no  implementation: static FUNC_FACTORY_T {U} NULL
      static FUNC_FACTORY_T _GUIFuncFactoryAddress;
      //## end cCustomFunctions::GUIFuncFactoryAddress%41E6BACC01B5.attr

      //## Attribute: GUIInitFuncAddress%41E6BB05004E
      //## begin cCustomFunctions::GUIInitFuncAddress%41E6BB05004E.attr preserve=no  implementation: static GUI_INIT_FUNC_T {U} NULL
      static GUI_INIT_FUNC_T _GUIInitFuncAddress;
      //## end cCustomFunctions::GUIInitFuncAddress%41E6BB05004E.attr

      //## Attribute: MdlFuncFactoryAddress%41E6BB17036B
      //## begin cCustomFunctions::MdlFuncFactoryAddress%41E6BB17036B.attr preserve=no  implementation: static FUNC_FACTORY_T {U} NULL
      static FUNC_FACTORY_T _MdlFuncFactoryAddress;
      //## end cCustomFunctions::MdlFuncFactoryAddress%41E6BB17036B.attr

      //## Attribute: MdlInitFuncAddress%41E6BB2A0196
      //## begin cCustomFunctions::MdlInitFuncAddress%41E6BB2A0196.attr preserve=no  implementation: static MDL_INIT_FUNC_T {U} NULL
      static MDL_INIT_FUNC_T _MdlInitFuncAddress;
      //## end cCustomFunctions::MdlInitFuncAddress%41E6BB2A0196.attr

      //## Attribute: GetCustomTextFuncAddress%41E6BB3F01D4
      //## begin cCustomFunctions::GetCustomTextFuncAddress%41E6BB3F01D4.attr preserve=no  implementation: static GET_CUSTOM_TEXT_FUNC_T {U} NULL
      static GET_CUSTOM_TEXT_FUNC_T _GetCustomTextFuncAddress;
      //## end cCustomFunctions::GetCustomTextFuncAddress%41E6BB3F01D4.attr

      //## Attribute: DeviceCreatorFuncAddress%41E6BB5601D4
      //## begin cCustomFunctions::DeviceCreatorFuncAddress%41E6BB5601D4.attr preserve=no  implementation: static DEV_FACTORY_T {U} NULL
      static DEV_FACTORY_T _DeviceCreatorFuncAddress;
      //## end cCustomFunctions::DeviceCreatorFuncAddress%41E6BB5601D4.attr

      //## Attribute: ProgramCreatorFuncAddress%41E6BB6C029F
      //## begin cCustomFunctions::ProgramCreatorFuncAddress%41E6BB6C029F.attr preserve=no  implementation: static PROG_FACTORY_T {U} NULL
      static PROG_FACTORY_T _ProgramCreatorFuncAddress;
      //## end cCustomFunctions::ProgramCreatorFuncAddress%41E6BB6C029F.attr

      //## Attribute: ShareAppframeFuncAddress%41EE621F03C8
      //## begin cCustomFunctions::ShareAppframeFuncAddress%41EE621F03C8.attr preserve=no  implementation: static SHARE_APPFRAME_FUNC_T {U} NULL
      static SHARE_APPFRAME_FUNC_T _ShareAppframeFuncAddress;
      //## end cCustomFunctions::ShareAppframeFuncAddress%41EE621F03C8.attr

      //## Attribute: ConstructObjectFuncAddress%43108B3B0216
      //## begin cCustomFunctions::ConstructObjectFuncAddress%43108B3B0216.attr preserve=no  implementation: static OBJECT_FACTORY_T {U} NULL
      static OBJECT_FACTORY_T _ConstructObjectFuncAddress;
      //## end cCustomFunctions::ConstructObjectFuncAddress%43108B3B0216.attr

      //## Attribute: VarDefFilterFuncAddress%43875E930025
      //## begin cCustomFunctions::VarDefFilterFuncAddress%43875E930025.attr preserve=no  implementation: static VARDEF_FILTER_T {U} NULL
      static VARDEF_FILTER_T _VarDefFilterFuncAddress;
      //## end cCustomFunctions::VarDefFilterFuncAddress%43875E930025.attr

    // Additional Implementation Declarations
      //## begin cCustomFunctions%41E6A80D000F.implementation preserve=yes
      //## end cCustomFunctions%41E6A80D000F.implementation

};

//## begin cCustomFunctions%41E6A80D000F.postscript preserve=yes
//## end cCustomFunctions%41E6A80D000F.postscript

// Class cCustomFunctions 

//## begin module%41E6A80D000F.epilog preserve=yes
//## end module%41E6A80D000F.epilog


#endif
