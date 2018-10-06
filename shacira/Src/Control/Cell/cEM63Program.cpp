//## begin module%43B103A502AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43B103A502AB.cm

//## begin module%43B103A502AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43B103A502AB.cp

//## Module: cEM63Program%43B103A502AB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cEM63Program.cpp

//## begin module%43B103A502AB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43B103A502AB.additionalIncludes

//## begin module%43B103A502AB.includes preserve=yes

#include "Control/Device/EM63/cEM63LogInfo.h"

//## end module%43B103A502AB.includes

// cUserInfo
#include "System/Objects/cUserInfo.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cEM63Requester
#include "Control/Cell/cEM63Requester.h"
// cEM63Program
#include "Control/Cell/cEM63Program.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"
// cStyxParser
#include "Language/cStyxParser.h"

#include "Client/ClientData/cClients.h"
//## begin module%43B103A502AB.additionalDeclarations preserve=yes
//## end module%43B103A502AB.additionalDeclarations


// Class cEM63Program 





cEM63Program::cEM63Program()
  //## begin cEM63Program::cEM63Program%.hasinit preserve=no
      : _Active(true), _UserInfo(NULL), _Requester(NULL), _Interface(NULL), _Options(0)
  //## end cEM63Program::cEM63Program%.hasinit
  //## begin cEM63Program::cEM63Program%.initialization preserve=yes
  //## end cEM63Program::cEM63Program%.initialization
{
  //## begin cEM63Program::cEM63Program%.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Program::cEM63Program%.body
}

cEM63Program::cEM63Program(const cEM63Program &right)
  //## begin cEM63Program::cEM63Program%copy.hasinit preserve=no
      : _Active(true), _UserInfo(NULL), _Requester(NULL), _Interface(NULL), _Options(0)
  //## end cEM63Program::cEM63Program%copy.hasinit
  //## begin cEM63Program::cEM63Program%copy.initialization preserve=yes
  //## end cEM63Program::cEM63Program%copy.initialization
{
  //## begin cEM63Program::cEM63Program%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Program::cEM63Program%copy.body
}

cEM63Program::cEM63Program (cConfigurationObject *config_obj, cContext *context)
  //## begin cEM63Program::cEM63Program%1135674623.hasinit preserve=no
      : _Active(true), _UserInfo(NULL), _Requester(NULL), _Interface(NULL), _Options(0)
  //## end cEM63Program::cEM63Program%1135674623.hasinit
  //## begin cEM63Program::cEM63Program%1135674623.initialization preserve=yes
      , cProgram(config_obj, context)
  //## end cEM63Program::cEM63Program%1135674623.initialization
{
  //## begin cEM63Program::cEM63Program%1135674623.body preserve=yes
   _IFType = IF_EM63;

   _UserInfo = new cUserInfo;
   _UserInfo->set_UserName(cClients::UserName(_IFType));
   _UserInfo->set_IFType(_IFType);
   _UserInfo->set_ClientId(_IFType);
   _Interface = new cEM63Interface(this);
   _Requester = new cEM63Requester(this);
  //## end cEM63Program::cEM63Program%1135674623.body
}


cEM63Program::~cEM63Program()
{
  //## begin cEM63Program::~cEM63Program%.body preserve=yes
   if (_Requester != NULL) {
      _Requester->Stop();
      DELETE_OBJECT(cEM63Requester, _Requester)
   }
   if (_Interface != NULL) {
      DELETE_OBJECT(cEM63Interface, _Interface)
   }
  //## end cEM63Program::~cEM63Program%.body
}



//## Other Operations (implementation)
void cEM63Program::Start ()
{
  //## begin cEM63Program::Start%1135674627.body preserve=yes
   cProgram::Start();
  //## end cEM63Program::Start%1135674627.body
}

void cEM63Program::Stop ()
{
  //## begin cEM63Program::Stop%1135674628.body preserve=yes
   if (_Requester != NULL) {
      _Requester->Stop();
   }
   cProgram::Stop();
  //## end cEM63Program::Stop%1135674628.body
}

void cEM63Program::ProcessEvent (cTransientObject *object)
{
  //## begin cEM63Program::ProcessEvent%1135674616.body preserve=yes
  //## end cEM63Program::ProcessEvent%1135674616.body
}

void cEM63Program::Cycle ()
{
  //## begin cEM63Program::Cycle%1135674617.body preserve=yes
   cObjectLock __lock__(_Interface->SessionMutex());
   if (cSystemUtils::GetThreadData() == NULL) {
      cSystemUtils::SetThreadData(_UserInfo);
      CreateInterfaceContext();
      if (_Requester != NULL) {
         _Requester->Start();
      }
   }
   if (get_Active()) {
      if (_Interface != NULL) {
         _Interface->Start();
         _Interface->Control();
         _Interface->Stop();
         _Interface->CleanUp();
      }
   }
  //## end cEM63Program::Cycle%1135674617.body
}

void cEM63Program::Initialize ()
{
  //## begin cEM63Program::Initialize%1135674618.body preserve=yes
  //## end cEM63Program::Initialize%1135674618.body
}

void cEM63Program::SetRoot (CONST_STRING_T root_directory)
{
  //## begin cEM63Program::SetRoot%1135674624.body preserve=yes
   if (_Interface != NULL) {
   }
  //## end cEM63Program::SetRoot%1135674624.body
}

void cEM63Program::CreateInterfaceContext ()
{
  //## begin cEM63Program::CreateInterfaceContext%1135674630.body preserve=yes
   if (_Interface == NULL) {
      return;
   }
   BOOL_T parsed = false;
   STRING_T var_defs;
   cContext * context = NULL;

   if (_Context->GetVarDefs(var_defs, _IFType) > 0) {
      context = new cContext;

      cStyxParser parser;
      parsed = parser.ParseDatabaseFromString(context, var_defs.c_str());
   }
   if (parsed) {
      STRING_LIST_T var_names;
      context->VariableNames(var_names);
      STRING_LIST_T::const_iterator i = var_names.cbegin();
      while (i != var_names.cend()) {
         STRING_T var_name = (*i);
         cVarDef * var_def = context->VarDef(var_name.c_str());
         if (var_def != NULL) {
            UCHAR_T data_type = 0;
            ULONG_T length = 0;
            UCHAR_T precision = 0;
            UCHAR_T access_rights = 0;
            STRING_T unit;
            STRING_T description;
            STRING_T text;
            STRING_T dim1Text;
            STRING_T dim2Text;
            STRING_T dim3Text;
            STRING_T dim4Text;
            ULONG_T system_flags = var_def->_SystemFlags;
            if (VarSpec(var_def, data_type, length, precision, access_rights,
                        unit, description, text, dim1Text, dim2Text, dim3Text, dim4Text)) {
               ULONG_T elements = var_def->Elements();
               for (ULONG_T pos=0; pos<elements; pos++) {
                  long i1 = -1, i2 = -1, i3 = -1, i4 = -1;
                  var_def->GetIndices(pos, i1, i2, i3, i4);
                  cVarRef * var_ref = NULL;
                  try {
                     var_ref = _Context->FilteredVarRef(_IFType, var_name.c_str(), i1, i2, i3, i4);
                  } catch (...) {
                  }
                  if (var_ref != NULL) {
                     char at[2] = {0};
                     if (!(system_flags & EM63_VARIABLE)) {
                        at[0] = '@';
                     }
                     int inc1 = (var_def->_Flags & DIM0_DECREMENT) ? 0 : 1;
                     int inc2 = (var_def->_Flags & DIM1_DECREMENT) ? 0 : 1;
                     int inc3 = (var_def->_Flags & DIM2_DECREMENT) ? 0 : 1;
                     int inc4 = (var_def->_Flags & DIM3_DECREMENT) ? 0 : 1;
                     char param_id[0x100] = {0};
                     if (i4 != -1) {
                        SafePrintf(param_id, sizeof(param_id), "%s%s[%d,%d,%d,%d]",
                                at, var_name.c_str(),
                                i1+inc1, i2+inc2, i3+inc3, i4+inc4);
                     } else if (i3 != -1) {
                        SafePrintf(param_id, sizeof(param_id), "%s%s[%d,%d,%d]",
                                at, var_name.c_str(),
                                i1+inc1, i2+inc2, i3+inc3);
                     } else if (i2 != -1) {
                        SafePrintf(param_id, sizeof(param_id), "%s%s[%d,%d]",
                                at, var_name.c_str(),
                                i1+inc1, i2+inc2);
                     } else if (i1 != -1) {
                        SafePrintf(param_id, sizeof(param_id), "%s%s[%d]",
                                at, var_name.c_str(),
                                i1+inc1);
                     } else {
                        SafePrintf(param_id, sizeof(param_id), "%s%s", at, var_name.c_str());
                     }
                     STRING_T varComment = GetVarCommentType();
                     STRING_T varCommentText = "";
                     if (strcmp(varComment.c_str(), "description") == 0) {
                         varCommentText = description;
                     }
                     else if (strcmp(varComment.c_str(), "text") == 0) {
                         varCommentText = text;
                     }

                     _Interface->AddParamSpec(var_ref, param_id, data_type, length, precision, access_rights,
                                              unit.c_str(), varCommentText.c_str(), dim1Text.c_str(),
                                              dim2Text.c_str(), dim3Text.c_str(), dim4Text.c_str(),
                                              (i1 != -1)?i1+inc1:i1,(i2 != -1)?i2+inc2:i2,(i3 != -1)?i3+inc3:i3,(i4 != -1)?i4+inc4:i4);
                  }
               }
            }
         }
         i++;
      }
   }
  //## end cEM63Program::CreateInterfaceContext%1135674630.body
}

BOOL_T cEM63Program::VarSpec (cVarDef *var_def, UCHAR_T &data_type, ULONG_T &length, UCHAR_T &precision, UCHAR_T &access_rights, STRING_T &unit, STRING_T &description, STRING_T &text, STRING_T &dim1_text, STRING_T &dim2_text, STRING_T &dim3_text, STRING_T &dim4_text)
{
  //## begin cEM63Program::VarSpec%1135674631.body preserve=yes
   ULONG_T system_flags = var_def->_SystemFlags;
   if (!(system_flags & HOST_READ ||
         system_flags & HOST_WRITE)) {
      return false;
   }
   UCHAR_T vartype = var_def->_VarType;
   if (vartype == SH_VAR_ACT) {
      access_rights = EM63_READONLY;
   } else {
      if (system_flags & HOST_WRITE) {
         access_rights = EM63_WRITEABLE;
      } else {
         access_rights = EM63_READONLY;
      }
   }
   data_type = 'N';
   switch (var_def->_DataType) {
   case SH_CHAR:
   case SH_UCHAR:
   case SH_SHORT:
   case SH_USHORT:
   case SH_LONG:
   case SH_ULONG:
   case SH_BIT_8:
   case SH_BIT_16:
   case SH_BIT_32:
   case SH_FLOAT:
   case SH_DOUBLE:
      length = DigitCount(var_def->_DataType);
      data_type = 'N';
      break;
   case SH_STRING:
   case SH_WSTRING:
      length = var_def->_Length;
      data_type = 'A';
      break;
   default:
      data_type = 'N';
      break;
   }

   precision = var_def->_Precision;

   STRING_T var_name = var_def->_VarName;
   cVarDef * varDef = _Context->VarDef(var_name.c_str());
   if (varDef != NULL) {
      cUnitDef *unitDef = varDef->get_UnitDef();
      if (unitDef != NULL) {
         precision = unitDef->Precision();
      }
   }
   unit = var_def->_UnitText;
   description = var_def->_Description;
   text = var_def->_Text;
   dim1_text = var_def->_Dim1Text;
   dim2_text = var_def->_Dim2Text;
   dim3_text = var_def->_Dim3Text;
   dim4_text = var_def->_Dim4Text;
   return true;
  //## end cEM63Program::VarSpec%1135674631.body
}

ULONG_T cEM63Program::DigitCount (UCHAR_T data_type)
{
  //## begin cEM63Program::DigitCount%1135674632.body preserve=yes
   switch (data_type) {
   case SH_VOID: 
      return 0;
   case SH_CHAR:
   case SH_UCHAR: 
      return 3;
   case SH_SHORT:;
   case SH_USHORT: 
      return 5;
   case SH_LONG:
   case SH_ULONG: 
      return 10;
   case SH_BIT_8:  
      return 3;
   case SH_BIT_16: 
      return 5;
   case SH_BIT_32:
   case SH_FLOAT:  
      return 10;
   case SH_DOUBLE: 
      return 20;
   default: return 20;
   }
  //## end cEM63Program::DigitCount%1135674632.body
}

STRING_T cEM63Program::RootDirectory ()
{
  //## begin cEM63Program::RootDirectory%1136631587.body preserve=yes
   return SessionDirectory();
  //## end cEM63Program::RootDirectory%1136631587.body
}

STRING_T cEM63Program::SessionDirectory ()
{
  //## begin cEM63Program::SessionDirectory%1136631588.body preserve=yes
   return "\\\\wilma\\user\\EM63";
  //## end cEM63Program::SessionDirectory%1136631588.body
}

STRING_T cEM63Program::LD ()
{
  //## begin cEM63Program::LD%1136631589.body preserve=yes
   return ",";
  //## end cEM63Program::LD%1136631589.body
}

STRING_T cEM63Program::DatasetId (CONST_STRING_T keyword)
{
  //## begin cEM63Program::DatasetId%1136191744.body preserve=yes
   return "";
  //## end cEM63Program::DatasetId%1136191744.body
}

STRING_T cEM63Program::ShotCounterId ()
{
  //## begin cEM63Program::ShotCounterId%1136631621.body preserve=yes
   return "unknown";
  //## end cEM63Program::ShotCounterId%1136631621.body
}

LONG_T cEM63Program::ShotCounterValue ()
{
  //## begin cEM63Program::ShotCounterValue%1136191748.body preserve=yes
   return 0;
  //## end cEM63Program::ShotCounterValue%1136191748.body
}

ULONG_T cEM63Program::InjUnitNbrValue ()
{
  //## begin cEM63Program::InjUnitNbrValue%1136199172.body preserve=yes
   return 1;
  //## end cEM63Program::InjUnitNbrValue%1136199172.body
}

STRING_T cEM63Program::MoldNbrValue ()
{
  //## begin cEM63Program::MoldNbrValue%1136199174.body preserve=yes
   return "";
  //## end cEM63Program::MoldNbrValue%1136199174.body
}

STRING_T cEM63Program::MachNbrValue ()
{
  //## begin cEM63Program::MachNbrValue%1136631617.body preserve=yes
   return "unknown";
  //## end cEM63Program::MachNbrValue%1136631617.body
}

STRING_T cEM63Program::MaterialNbrValue ()
{
  //## begin cEM63Program::MaterialNbrValue%1136199173.body preserve=yes
   return "";
  //## end cEM63Program::MaterialNbrValue%1136199173.body
}

STRING_T cEM63Program::MachVendor ()
{
  //## begin cEM63Program::MachVendor%1136631590.body preserve=yes
   return "";
  //## end cEM63Program::MachVendor%1136631590.body
}

STRING_T cEM63Program::MachDesc ()
{
  //## begin cEM63Program::MachDesc%1136631591.body preserve=yes
   return "euromap 63 test machine";
  //## end cEM63Program::MachDesc%1136631591.body
}

STRING_T cEM63Program::ContrType ()
{
  //## begin cEM63Program::ContrType%1136631592.body preserve=yes
   return "";
  //## end cEM63Program::ContrType%1136631592.body
}

STRING_T cEM63Program::ContrVersion ()
{
  //## begin cEM63Program::ContrVersion%1136631593.body preserve=yes
   return "";
  //## end cEM63Program::ContrVersion%1136631593.body
}

ULONG_T cEM63Program::MaxJobs ()
{
  //## begin cEM63Program::MaxJobs%1136631594.body preserve=yes
   return 20;
  //## end cEM63Program::MaxJobs%1136631594.body
}

ULONG_T cEM63Program::MaxChanges ()
{
  //## begin cEM63Program::MaxChanges%1136631595.body preserve=yes
   return 1;
  //## end cEM63Program::MaxChanges%1136631595.body
}

ULONG_T cEM63Program::MaxAlarms ()
{
  //## begin cEM63Program::MaxAlarms%1136631596.body preserve=yes
   return 1;
  //## end cEM63Program::MaxAlarms%1136631596.body
}

ULONG_T cEM63Program::MaxCurrentAlarms ()
{
  //## begin cEM63Program::MaxCurrentAlarms%1136631597.body preserve=yes
   return 1;
  //## end cEM63Program::MaxCurrentAlarms%1136631597.body
}

ULONG_T cEM63Program::MaxReports ()
{
  //## begin cEM63Program::MaxReports%1136631598.body preserve=yes
   return 5;
  //## end cEM63Program::MaxReports%1136631598.body
}

ULONG_T cEM63Program::MaxArchives ()
{
  //## begin cEM63Program::MaxArchives%1136631599.body preserve=yes
   return 1;
  //## end cEM63Program::MaxArchives%1136631599.body
}

ULONG_T cEM63Program::MaxSessions ()
{
  //## begin cEM63Program::MaxSessions%1136631600.body preserve=yes
   return 60;
  //## end cEM63Program::MaxSessions%1136631600.body
}

STRING_T cEM63Program::CharDef ()
{
  //## begin cEM63Program::CharDef%1136631601.body preserve=yes
   return "850";
  //## end cEM63Program::CharDef%1136631601.body
}

STRING_T cEM63Program::Version ()
{
  //## begin cEM63Program::Version%1136631619.body preserve=yes
   return EM63_VERSION; // HA060206
  //## end cEM63Program::Version%1136631619.body
}

STRING_T cEM63Program::GetAlarmText (cAlarm *alarm)
{
  //## begin cEM63Program::GetAlarmText%1139403383.body preserve=yes
   return alarm->get_Text1();
  //## end cEM63Program::GetAlarmText%1139403383.body
}

STRING_T cEM63Program::GetCustomAlarmId (cAlarm *alarm)
{
   char buffer[20];
   _ultoa(alarm->get_Ident(), buffer, 10);
   return buffer;
}

STRING_T cEM63Program::GetVarCommentType ()
{
  //## begin cEM63Program::GetVarCommentType%1151500988.body preserve=yes
   return "description";
  //## end cEM63Program::GetVarCommentType%1151500988.body
}

BOOL_T cEM63Program::VariableText(STRING_T &ids_text, PARAM_SPEC_T * param_spec)
{
    return false;
}

void cEM63Program::Log (cEM63LogInfo *log_info)
{
  //## begin cEM63Program::Log%1166083886.body preserve=yes
   STRING_T log_file = cFileSystemUtils::AppendPath(cResources::LogPath().c_str(), "em63.log");
   FILE * stream = fopen(log_file.c_str(), "a");
   if (stream != NULL) {
      ULONG_T operation = log_info->Operation();
      int error_code = log_info->ErrCode();
      STRING_T param1 = log_info->Param1();
      STRING_T param2 = log_info->Param2();
      STRING_T param3 = log_info->Param3();
      if (error_code != 0) {
         fprintf(stream, "%s %s %s failed: %d\n",
                 param1.c_str(),
                 param2.c_str(),
                 param3.c_str(),
                 error_code);
      } else {
         fprintf(stream, "%s %s %s\n",
                 param1.c_str(),
                 param2.c_str(),
                 param3.c_str());
      }
      fclose(stream);
   }
   log_info->Release();
  //## end cEM63Program::Log%1166083886.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cEM63Program::get_Active () const
{
  //## begin cEM63Program::get_Active%43BF9B6601C0.get preserve=no
  return _Active;
  //## end cEM63Program::get_Active%43BF9B6601C0.get
}

void cEM63Program::set_Active (BOOL_T value)
{
  //## begin cEM63Program::set_Active%43BF9B6601C0.set preserve=no
  _Active = value;
  //## end cEM63Program::set_Active%43BF9B6601C0.set
}

ULONG_T cEM63Program::Options ()
{
   return _Options;
}

void cEM63Program::SetOption (ULONG_T option)
{
   _Options = _Options | option;
}

void cEM63Program::ResetOption (ULONG_T option)
{
   _Options = _Options & (~option);
}

// Additional Declarations
  //## begin cEM63Program%43B103A502AB.declarations preserve=yes
  //## end cEM63Program%43B103A502AB.declarations

//## begin module%43B103A502AB.epilog preserve=yes
//## end module%43B103A502AB.epilog
