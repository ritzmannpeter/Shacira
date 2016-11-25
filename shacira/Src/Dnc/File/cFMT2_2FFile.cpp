//## begin module%3B9CE6040134.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CE6040134.cm

//## begin module%3B9CE6040134.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CE6040134.cp

//## Module: cFMT2_2FFile%3B9CE6040134; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT2_2FFile.cpp

//## begin module%3B9CE6040134.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9CE6040134.additionalIncludes

//## begin module%3B9CE6040134.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "fmt2.h"

//## end module%3B9CE6040134.includes

// cFMT2_2FFile
#include "Dnc/File/cFMT2_2FFile.h"
//## begin module%3B9CE6040134.additionalDeclarations preserve=yes
//## end module%3B9CE6040134.additionalDeclarations


// Class cFMT2_2FFile 

cFMT2_2FFile::cFMT2_2FFile()
  //## begin cFMT2_2FFile::cFMT2_2FFile%.hasinit preserve=no
  //## end cFMT2_2FFile::cFMT2_2FFile%.hasinit
  //## begin cFMT2_2FFile::cFMT2_2FFile%.initialization preserve=yes
  //## end cFMT2_2FFile::cFMT2_2FFile%.initialization
{
  //## begin cFMT2_2FFile::cFMT2_2FFile%.body preserve=yes
   _FileFormat = FMT_FMT2_2F;
   _FileVersion = VERS_FMT2_FM_2F;
  //## end cFMT2_2FFile::cFMT2_2FFile%.body
}

cFMT2_2FFile::cFMT2_2FFile(const cFMT2_2FFile &right)
  //## begin cFMT2_2FFile::cFMT2_2FFile%copy.hasinit preserve=no
  //## end cFMT2_2FFile::cFMT2_2FFile%copy.hasinit
  //## begin cFMT2_2FFile::cFMT2_2FFile%copy.initialization preserve=yes
  //## end cFMT2_2FFile::cFMT2_2FFile%copy.initialization
{
  //## begin cFMT2_2FFile::cFMT2_2FFile%copy.body preserve=yes
  //## end cFMT2_2FFile::cFMT2_2FFile%copy.body
}

cFMT2_2FFile::cFMT2_2FFile (CONST_STRING_T name, cFileSystem *file_system)
  //## begin cFMT2_2FFile::cFMT2_2FFile%1000119074.hasinit preserve=no
  //## end cFMT2_2FFile::cFMT2_2FFile%1000119074.hasinit
  //## begin cFMT2_2FFile::cFMT2_2FFile%1000119074.initialization preserve=yes
   : cFile(name, file_system)
  //## end cFMT2_2FFile::cFMT2_2FFile%1000119074.initialization
{
  //## begin cFMT2_2FFile::cFMT2_2FFile%1000119074.body preserve=yes
   _FileFormat = FMT_FMT2_2F;
   _FileVersion = VERS_FMT2_FM_2F;
  //## end cFMT2_2FFile::cFMT2_2FFile%1000119074.body
}


cFMT2_2FFile::~cFMT2_2FFile()
{
  //## begin cFMT2_2FFile::~cFMT2_2FFile%.body preserve=yes
  //## end cFMT2_2FFile::~cFMT2_2FFile%.body
}



//## Other Operations (implementation)
void cFMT2_2FFile::Save (cToolFileSystem *file_system)
{
  //## begin cFMT2_2FFile::Save%1062507897.body preserve=yes
  //## end cFMT2_2FFile::Save%1062507897.body
}

LONG_T cFMT2_2FFile::DINT2Long (LONG_T value)
{
  //## begin cFMT2_2FFile::DINT2Long%1000724936.body preserve=yes
   return (value >> 16) * 10000L + (value & 0x0000ffffL);
  //## end cFMT2_2FFile::DINT2Long%1000724936.body
}

LONG_T cFMT2_2FFile::ComputeAddress (CONST_STRING_T spec)
{
  //## begin cFMT2_2FFile::ComputeAddress%1001057894.body preserve=yes
  //## end cFMT2_2FFile::ComputeAddress%1001057894.body
}

// Additional Declarations
  //## begin cFMT2_2FFile%3B9CE6040134.declarations preserve=yes
  //## end cFMT2_2FFile%3B9CE6040134.declarations

//## begin module%3B9CE6040134.epilog preserve=yes
//## end module%3B9CE6040134.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cFMT2_2FFile::GetVariableValue%1000119075.body preserve=no
   int err = 0;
   if (_Size > 0) {
      OLD_DISK_SUB_HEADER * sub_header =
         (OLD_DISK_SUB_HEADER*)&((char*)_FileBuffer->Memory())[sizeof(OLD_DISK_HEADER)];
      if (strcmp(name, "TOOL_NO") == 0) {
         long tool_no = DINT2Long(sub_header->ToolNr);
         char _tool_no[32] = {0};
         ltoa(tool_no, _tool_no, 10);
         value = _tool_no;
         return 0;
      } else if (strcmp(name, "MATERIAL_NO") == 0) {
         long material_no = DINT2Long(sub_header->MatNr);
         char _material_no[32] = {0};
         ltoa(material_no, _material_no, 10);
         value = _material_no;
         return 0;
      } else if (strcmp(name, "MACHINE_TYPE") == 0) {
         char _machine_type[64] = {0};
         sprintf(_machine_type, "FM%ld", sub_header->MashSize);
         value = _machine_type;
         return 0;
      } else if (strcmp(name, "ARTICLE_NO") == 0) {
          return FILE_NO_INFO;
      } else {
         return FILE_INVALID_VARIABLE;
      }
   } else {
      return FILE_EMPTY;
   }
//## end cFMT2_2FFile::GetVariableValue%1000119075.body

//## begin cFMT2_2FFile::GetTime%1000308645.body preserve=no
   cTimeObject time(0L);
   if (_Size > 0) {
      OLD_DISK_SUB_HEADER * sub_header =
         (OLD_DISK_SUB_HEADER*)&((char*)_FileBuffer->Memory())[sizeof(OLD_DISK_HEADER)];
      unsigned int year = FMT2_GET_YEAR(sub_header->Date) + 1900;
      unsigned int month = FMT2_GET_MONTH(sub_header->Date);
      unsigned int day = FMT2_GET_DAY(sub_header->Date);
      unsigned int hour = FMT2_GET_HOUR(sub_header->Date);
      unsigned int minute = FMT2_GET_MIN(sub_header->Date);
      unsigned int second = 0;
      time.Set(cTimeObject::YEAR, year);
      time.Set(cTimeObject::MONTH, month);
      time.Set(cTimeObject::DAY, day);
      time.Set(cTimeObject::HOUR, hour);
      time.Set(cTimeObject::MINUTE, minute);
      time.Set(cTimeObject::SECOND, second);
   }
   return time;
//## end cFMT2_2FFile::GetTime%1000308645.body

#endif
