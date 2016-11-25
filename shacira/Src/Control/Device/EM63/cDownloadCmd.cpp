//## begin module%438080AF024D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%438080AF024D.cm

//## begin module%438080AF024D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%438080AF024D.cp

//## Module: cDownloadCmd%438080AF024D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cDownloadCmd.cpp

//## begin module%438080AF024D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%438080AF024D.additionalIncludes

//## begin module%438080AF024D.includes preserve=yes
//## end module%438080AF024D.includes

// cDownloadCmd
#include "Control/Device/EM63/cDownloadCmd.h"
// cCondition
#include "Control/Device/EM63/cCondition.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%438080AF024D.additionalDeclarations preserve=yes
//## end module%438080AF024D.additionalDeclarations


// Class cDownloadCmd 





cDownloadCmd::cDownloadCmd()
  //## begin cDownloadCmd::cDownloadCmd%.hasinit preserve=no
      : _ActiveSource(false), _StartCondition(NULL)
  //## end cDownloadCmd::cDownloadCmd%.hasinit
  //## begin cDownloadCmd::cDownloadCmd%.initialization preserve=yes
  //## end cDownloadCmd::cDownloadCmd%.initialization
{
  //## begin cDownloadCmd::cDownloadCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cDownloadCmd::cDownloadCmd%.body
}

cDownloadCmd::cDownloadCmd(const cDownloadCmd &right)
  //## begin cDownloadCmd::cDownloadCmd%copy.hasinit preserve=no
      : _ActiveSource(false), _StartCondition(NULL)
  //## end cDownloadCmd::cDownloadCmd%copy.hasinit
  //## begin cDownloadCmd::cDownloadCmd%copy.initialization preserve=yes
  //## end cDownloadCmd::cDownloadCmd%copy.initialization
{
  //## begin cDownloadCmd::cDownloadCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDownloadCmd::cDownloadCmd%copy.body
}

cDownloadCmd::cDownloadCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cDownloadCmd::cDownloadCmd%1136548769.hasinit preserve=no
      : _ActiveSource(false), _StartCondition(NULL)
  //## end cDownloadCmd::cDownloadCmd%1136548769.hasinit
  //## begin cDownloadCmd::cDownloadCmd%1136548769.initialization preserve=yes
  , cPresentationCmd(job, command_name)
  //## end cDownloadCmd::cDownloadCmd%1136548769.initialization
{
  //## begin cDownloadCmd::cDownloadCmd%1136548769.body preserve=yes
   _CommandType = EM63_DOWNLOAD_COMMAND;
   INCREMENT_OBJECT_COUNT()
   //## end cDownloadCmd::cDownloadCmd%1136548769.body
}


cDownloadCmd::~cDownloadCmd()
{
  //## begin cDownloadCmd::~cDownloadCmd%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cDownloadCmd::~cDownloadCmd%.body
}



//## Other Operations (implementation)
void cDownloadCmd::SetStartCondition (cCondition *condition)
{
  //## begin cDownloadCmd::SetStartCondition%1135947268.body preserve=yes
   _StartCondition = condition;
  //## end cDownloadCmd::SetStartCondition%1135947268.body
}

BOOL_T cDownloadCmd::Start ()
{
  //## begin cDownloadCmd::Start%1135947270.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsStarted()) {
      if (_StartCondition == NULL) {
         Started();
         Download();
         Terminated();
         return true;
      } else {
         if (_StartCondition->Eval()) {
            Started();
            Download();
            Terminated();
            return true;
         } else {
            return false;
         }
      }
   } else {
      return false;
   }
  //## end cDownloadCmd::Start%1135947270.body
}

BOOL_T cDownloadCmd::Download ()
{
  //## begin cDownloadCmd::Download%1135947272.body preserve=yes
   STRING_T dataset_param_id;
   if (_ActiveSource) {
      dataset_param_id = _Interface->DatasetId("ACTIVE");
   } else if (_Keyword.size() > 0) {
      dataset_param_id = _Interface->DatasetId(_Keyword.c_str());
   } else if (_AvSource.size() > 0) {
      dataset_param_id = _Interface->DatasetId(_AvSource.c_str());
   } else {
      Failed(DWNCMD_INVALID_SYNTAX);
      return false;
   }
   if (dataset_param_id.size() == 0) {
      Failed(UNKNOWN_ERROR, "needed parameter id for datasets is zero");
      return false;
   }
   if (!_Interface->ParamExists(dataset_param_id.c_str())) {
      char msg[0x100] = {0};
      SafePrintf(msg, sizeof(msg), "needed parameter id %s is unknown", dataset_param_id.c_str());
      Failed(UNKNOWN_ERROR, msg);
      return false;
   }
   STRING_T dataset;
#ifdef EM63_LOGGING_INTERFACE
   if (_Session->Interface()->Get(CAT_SYNC, _OutputFile.c_str(), dataset, 0) != 0) {
      Failed(OPEN_DOWNLOAD_FILE, _OutputFile.c_str());
      return false;
   } else {
      int err = _Interface->SetParamValue(dataset_param_id.c_str(), dataset.c_str());
      if (err == 0) {
         return true;
      } else {
         if (err == E63_ACCESS_DENIED) {
            Failed(DOWNLOAD_DENIED);
         } else {
            int err_code = _Interface->ParamError(err);
            Failed(err_code);
         }
         return false;
      }
   }
#else
   cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
   if (file_system != NULL) {
      if (file_system->Get(_OutputFile.c_str(), dataset, 0) != 0) {
         Failed(OPEN_DOWNLOAD_FILE, _OutputFile.c_str());
         return false;
      } else {
         int err = _Interface->SetParamValue(dataset_param_id.c_str(), dataset.c_str());
         if (err == 0) {
            return true;
         } else {
            if (err == E63_ACCESS_DENIED) {
               Failed(DOWNLOAD_DENIED);
            } else {
               int err_code = _Interface->ParamError(err);
               Failed(err_code);
            }
            return false;
         }
      }
   } else {
      return false;
   }
#endif
  //## end cDownloadCmd::Download%1135947272.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cDownloadCmd::get_ActiveSource () const
{
  //## begin cDownloadCmd::get_ActiveSource%43B54BD50252.get preserve=no
  return _ActiveSource;
  //## end cDownloadCmd::get_ActiveSource%43B54BD50252.get
}

void cDownloadCmd::set_ActiveSource (BOOL_T value)
{
  //## begin cDownloadCmd::set_ActiveSource%43B54BD50252.set preserve=no
  _ActiveSource = value;
  //## end cDownloadCmd::set_ActiveSource%43B54BD50252.set
}

STRING_T cDownloadCmd::get_AvSource () const
{
  //## begin cDownloadCmd::get_AvSource%43B54C020167.get preserve=no
  return _AvSource;
  //## end cDownloadCmd::get_AvSource%43B54C020167.get
}

void cDownloadCmd::set_AvSource (STRING_T value)
{
  //## begin cDownloadCmd::set_AvSource%43B54C020167.set preserve=no
  _AvSource = value;
  //## end cDownloadCmd::set_AvSource%43B54C020167.set
}

STRING_T cDownloadCmd::get_Keyword () const
{
  //## begin cDownloadCmd::get_Keyword%43B54C19009C.get preserve=no
  return _Keyword;
  //## end cDownloadCmd::get_Keyword%43B54C19009C.get
}

void cDownloadCmd::set_Keyword (STRING_T value)
{
  //## begin cDownloadCmd::set_Keyword%43B54C19009C.set preserve=no
  _Keyword = value;
  //## end cDownloadCmd::set_Keyword%43B54C19009C.set
}

cCondition * cDownloadCmd::get_StartCondition () const
{
  //## begin cDownloadCmd::get_StartCondition%43B54C760176.get preserve=no
  return _StartCondition;
  //## end cDownloadCmd::get_StartCondition%43B54C760176.get
}

void cDownloadCmd::set_StartCondition (cCondition * value)
{
  //## begin cDownloadCmd::set_StartCondition%43B54C760176.set preserve=no
  _StartCondition = value;
  //## end cDownloadCmd::set_StartCondition%43B54C760176.set
}

// Additional Declarations
  //## begin cDownloadCmd%438080AF024D.declarations preserve=yes
  //## end cDownloadCmd%438080AF024D.declarations

//## begin module%438080AF024D.epilog preserve=yes
//## end module%438080AF024D.epilog
