//## begin module%4380804702CB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380804702CB.cm

//## begin module%4380804702CB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380804702CB.cp

//## Module: cGetIdCmd%4380804702CB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cGetIdCmd.cpp

//## begin module%4380804702CB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380804702CB.additionalIncludes

//## begin module%4380804702CB.includes preserve=yes
//## end module%4380804702CB.includes

// cGetIdCmd
#include "Control/Device/EM63/cGetIdCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%4380804702CB.additionalDeclarations preserve=yes
//## end module%4380804702CB.additionalDeclarations


// Class cGetIdCmd 

cGetIdCmd::cGetIdCmd()
  //## begin cGetIdCmd::cGetIdCmd%.hasinit preserve=no
  //## end cGetIdCmd::cGetIdCmd%.hasinit
  //## begin cGetIdCmd::cGetIdCmd%.initialization preserve=yes
  //## end cGetIdCmd::cGetIdCmd%.initialization
{
  //## begin cGetIdCmd::cGetIdCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cGetIdCmd::cGetIdCmd%.body
}

cGetIdCmd::cGetIdCmd(const cGetIdCmd &right)
  //## begin cGetIdCmd::cGetIdCmd%copy.hasinit preserve=no
  //## end cGetIdCmd::cGetIdCmd%copy.hasinit
  //## begin cGetIdCmd::cGetIdCmd%copy.initialization preserve=yes
  //## end cGetIdCmd::cGetIdCmd%copy.initialization
{
  //## begin cGetIdCmd::cGetIdCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGetIdCmd::cGetIdCmd%copy.body
}

cGetIdCmd::cGetIdCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cGetIdCmd::cGetIdCmd%1136548773.hasinit preserve=no
  //## end cGetIdCmd::cGetIdCmd%1136548773.hasinit
  //## begin cGetIdCmd::cGetIdCmd%1136548773.initialization preserve=yes
  : cPresentationCmd(job, command_name)
  //## end cGetIdCmd::cGetIdCmd%1136548773.initialization
{
  //## begin cGetIdCmd::cGetIdCmd%1136548773.body preserve=yes
   _CommandType = EM63_GETID_COMMAND;
   INCREMENT_OBJECT_COUNT()
   //## end cGetIdCmd::cGetIdCmd%1136548773.body
}


cGetIdCmd::~cGetIdCmd()
{
  //## begin cGetIdCmd::~cGetIdCmd%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cGetIdCmd::~cGetIdCmd%.body
}



//## Other Operations (implementation)
BOOL_T cGetIdCmd::Process (cContext *context)
{
  //## begin cGetIdCmd::Process%1135761101.body preserve=yes
   return true;
  //## end cGetIdCmd::Process%1135761101.body
}

BOOL_T cGetIdCmd::Start ()
{
  //## begin cGetIdCmd::Start%1135761102.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsStarted()) {
      Started();
      STRING_T ld = _Interface->LD();
//      ld += "\t";
      char value[0x20] = {0};
      STRING_T ids;
      PARAM_SPEC_MAP_T param_specs;
      _Interface->GetParamSpecs(param_specs);
      PARAM_SPEC_MAP_T::const_iterator i = param_specs.begin();
      while (i != param_specs.end()) {
         PARAM_SPEC_T * param_spec = (*i).second;
         ids += param_spec->param_id;
         ids += ld.c_str();
         SafePrintf(value, sizeof(value),  "%c", param_spec->data_type);
         ids += value;
         ids += ld.c_str();
         SafePrintf(value, sizeof(value),  "%d", (param_spec->length - param_spec->precision));
         ids += value;
         ids += ld.c_str();
         SafePrintf(value, sizeof(value),  "%d", param_spec->precision);
         ids += value;
         ids += ld.c_str();
         SafePrintf(value, sizeof(value),  "%d", param_spec->access_rights);
         ids += value;
         ids += ld.c_str();
         ids += "\"";
         if (strlen(param_spec->unit)) {
            ids += cStringUtils::Trim(param_spec->unit, '"');
         }
         else {
            ids += "-";
         }
         ids += "\"";
         ids += ld.c_str();
         ids += "\"";
         if (_Interface->GetVarCommentType() == "text") {
            if (!_Interface->VariableText(ids, param_spec)) {
               ids += param_spec->comment;
               if (param_spec->i1 != -1) {
                  ids += " ";
                  ids += param_spec->dim1Text;
                  SafePrintf(value, sizeof(value),  " %d", param_spec->i1);
                  ids += value;
               }
               if (param_spec->i2!= -1) {
                  ids += " ";
                  ids += param_spec->dim2Text;
                  SafePrintf(value, sizeof(value),  " %d", param_spec->i2);
                  ids += value;
               }         
               if (param_spec->i3 != -1) {
                  ids += " ";
                  ids += param_spec->dim3Text;
                  SafePrintf(value, sizeof(value),  " %d", param_spec->i3);
                  ids += value;
               }
               if (param_spec->i4 != -1) {
                  ids += " ";
                  ids += param_spec->dim4Text;
                  SafePrintf(value, sizeof(value),  " %d", param_spec->i4);
                  ids += value;
               }
            }
         }
         ids += "\"";
         ids += ";\n";
         i++;
      }
#ifdef EM63_LOGGING_INTERFACE
      int rc = _Interface->Put(CAT_SYNC, _OutputFile.c_str(), ids.c_str(), 0);
      if (rc < 0) {
         Failed(CREATE_DESTINATION_FILE, _OutputFile.c_str());
         Terminated();
         return false;
      }
#else
      cAbstractFileSystem * file_system = _Interface->FileSystem();
      if (file_system != NULL) {
         file_system->Put(_OutputFile.c_str(), ids.c_str(), 0);
      } else {
      }
#endif
      Terminated();
      return true;
   } else {
      return false;
   }
  //## end cGetIdCmd::Start%1135761102.body
}

void cGetIdCmd::Stop ()
{
  //## begin cGetIdCmd::Stop%1135761103.body preserve=yes
  //## end cGetIdCmd::Stop%1135761103.body
}

// Additional Declarations
  //## begin cGetIdCmd%4380804702CB.declarations preserve=yes
  //## end cGetIdCmd%4380804702CB.declarations

//## begin module%4380804702CB.epilog preserve=yes
//## end module%4380804702CB.epilog
