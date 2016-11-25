//## begin module%4380809B026C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380809B026C.cm

//## begin module%4380809B026C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380809B026C.cp

//## Module: cUploadCmd%4380809B026C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cUploadCmd.cpp

//## begin module%4380809B026C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380809B026C.additionalIncludes

//## begin module%4380809B026C.includes preserve=yes
//## end module%4380809B026C.includes

// cUploadCmd
#include "Control/Device/EM63/cUploadCmd.h"
// cCondition
#include "Control/Device/EM63/cCondition.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%4380809B026C.additionalDeclarations preserve=yes
//## end module%4380809B026C.additionalDeclarations


// Class cUploadCmd 





cUploadCmd::cUploadCmd()
  //## begin cUploadCmd::cUploadCmd%.hasinit preserve=no
      : _ActiveSource(false), _StartCondition(NULL)
  //## end cUploadCmd::cUploadCmd%.hasinit
  //## begin cUploadCmd::cUploadCmd%.initialization preserve=yes
  //## end cUploadCmd::cUploadCmd%.initialization
{
  //## begin cUploadCmd::cUploadCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cUploadCmd::cUploadCmd%.body
}

cUploadCmd::cUploadCmd(const cUploadCmd &right)
  //## begin cUploadCmd::cUploadCmd%copy.hasinit preserve=no
      : _ActiveSource(false), _StartCondition(NULL)
  //## end cUploadCmd::cUploadCmd%copy.hasinit
  //## begin cUploadCmd::cUploadCmd%copy.initialization preserve=yes
  //## end cUploadCmd::cUploadCmd%copy.initialization
{
  //## begin cUploadCmd::cUploadCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cUploadCmd::cUploadCmd%copy.body
}

cUploadCmd::cUploadCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cUploadCmd::cUploadCmd%1136548770.hasinit preserve=no
      : _ActiveSource(false), _StartCondition(NULL)
  //## end cUploadCmd::cUploadCmd%1136548770.hasinit
  //## begin cUploadCmd::cUploadCmd%1136548770.initialization preserve=yes
  , cPresentationCmd(job, command_name)
  //## end cUploadCmd::cUploadCmd%1136548770.initialization
{
  //## begin cUploadCmd::cUploadCmd%1136548770.body preserve=yes
   _CommandType = EM63_UPLOAD_COMMAND;
   INCREMENT_OBJECT_COUNT()
   //## end cUploadCmd::cUploadCmd%1136548770.body
}


cUploadCmd::~cUploadCmd()
{
  //## begin cUploadCmd::~cUploadCmd%.body preserve=yes
   if (_StartCondition != NULL) {
      delete _StartCondition;
   }
   DECREMENT_OBJECT_COUNT()
   //## end cUploadCmd::~cUploadCmd%.body
}



//## Other Operations (implementation)
void cUploadCmd::SetStartCondition (cCondition *condition)
{
  //## begin cUploadCmd::SetStartCondition%1135947269.body preserve=yes
   _StartCondition = condition;
  //## end cUploadCmd::SetStartCondition%1135947269.body
}

BOOL_T cUploadCmd::Start ()
{
  //## begin cUploadCmd::Start%1135947271.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsStarted()) {
      if (_StartCondition == NULL) {
         Started();
         Upload();
         Terminated();
         return true;
      } else {
         if (_StartCondition->Eval()) {
            Started();
            Upload();
            Terminated();
            return true;
         } else {
            return false;
         }
      }
   } else {
      return false;
   }
  //## end cUploadCmd::Start%1135947271.body
}

BOOL_T cUploadCmd::Upload ()
{
  //## begin cUploadCmd::Upload%1135947273.body preserve=yes
   STRING_T dataset_param_id;
   STRING_T dataset;
   if (_ActiveSource) {
      dataset_param_id = _Interface->DatasetId("ACTIVE");
   } else if (_Keyword.size() > 0) {
      dataset_param_id = _Interface->DatasetId(_Keyword.c_str());
   } else if (_AvSource.size() > 0) {
      dataset_param_id = _Interface->DatasetId(_AvSource.c_str());
      Failed(UPLCMD_INVALID_SYNTAX);
      return false;
   }
   if (dataset_param_id.size() == 0) {
      Failed(UNKNOWN_ERROR, "need parameter id for datasets is zero");
      return false;
   }
   int err = _Interface->GetParamValue(dataset_param_id.c_str(), dataset);
   if (err != 0) {
      if (err == E63_ACCESS_DENIED) {
         Failed(UPLOAD_DENIED);
      } else {
         int err_code = _Interface->ParamError(err);
         Failed(err_code, dataset_param_id.c_str());
      }
      return false;
   } else {
#ifdef EM63_LOGGING_INTERFACE
      int rc = _Session->Interface()->Put(CAT_SYNC, _OutputFile.c_str(), dataset.c_str(), 0);
      if (rc < 0) {
         Failed(CREATE_UPLOAD_FILE, _OutputFile.c_str());
         return false;
      } else {
         return true;
      }
#else
      cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
      if (file_system != NULL) {
         if (!file_system->Put(_OutputFile.c_str(), dataset.c_str(), 0)) {
            return true;
         } else {
            Failed(CREATE_UPLOAD_FILE, _OutputFile.c_str());
            return false;
         }
      } else {
         return false;
      }
#endif
   }
  //## end cUploadCmd::Upload%1135947273.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cUploadCmd::get_ActiveSource () const
{
  //## begin cUploadCmd::get_ActiveSource%43B54C390290.get preserve=no
  return _ActiveSource;
  //## end cUploadCmd::get_ActiveSource%43B54C390290.get
}

void cUploadCmd::set_ActiveSource (BOOL_T value)
{
  //## begin cUploadCmd::set_ActiveSource%43B54C390290.set preserve=no
  _ActiveSource = value;
  //## end cUploadCmd::set_ActiveSource%43B54C390290.set
}

STRING_T cUploadCmd::get_AvSource () const
{
  //## begin cUploadCmd::get_AvSource%43B54C39029F.get preserve=no
  return _AvSource;
  //## end cUploadCmd::get_AvSource%43B54C39029F.get
}

void cUploadCmd::set_AvSource (STRING_T value)
{
  //## begin cUploadCmd::set_AvSource%43B54C39029F.set preserve=no
  _AvSource = value;
  //## end cUploadCmd::set_AvSource%43B54C39029F.set
}

STRING_T cUploadCmd::get_Keyword () const
{
  //## begin cUploadCmd::get_Keyword%43B54C3902A0.get preserve=no
  return _Keyword;
  //## end cUploadCmd::get_Keyword%43B54C3902A0.get
}

void cUploadCmd::set_Keyword (STRING_T value)
{
  //## begin cUploadCmd::set_Keyword%43B54C3902A0.set preserve=no
  _Keyword = value;
  //## end cUploadCmd::set_Keyword%43B54C3902A0.set
}

cCondition * cUploadCmd::get_StartCondition () const
{
  //## begin cUploadCmd::get_StartCondition%43B54C7C0270.get preserve=no
  return _StartCondition;
  //## end cUploadCmd::get_StartCondition%43B54C7C0270.get
}

void cUploadCmd::set_StartCondition (cCondition * value)
{
  //## begin cUploadCmd::set_StartCondition%43B54C7C0270.set preserve=no
  _StartCondition = value;
  //## end cUploadCmd::set_StartCondition%43B54C7C0270.set
}

// Additional Declarations
  //## begin cUploadCmd%4380809B026C.declarations preserve=yes
  //## end cUploadCmd%4380809B026C.declarations

//## begin module%4380809B026C.epilog preserve=yes
//## end module%4380809B026C.epilog
