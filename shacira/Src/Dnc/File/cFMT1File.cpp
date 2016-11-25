//## begin module%3B9C9DEE028D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9DEE028D.cm

//## begin module%3B9C9DEE028D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9DEE028D.cp

//## Module: cFMT1File%3B9C9DEE028D; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT1File.cpp

//## begin module%3B9C9DEE028D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9C9DEE028D.additionalIncludes

//## begin module%3B9C9DEE028D.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "fmt1.h"

//## end module%3B9C9DEE028D.includes

// cFMT1File
#include "Dnc/File/cFMT1File.h"
//## begin module%3B9C9DEE028D.additionalDeclarations preserve=yes
//## end module%3B9C9DEE028D.additionalDeclarations


// Class cFMT1File 

cFMT1File::cFMT1File()
  //## begin cFMT1File::cFMT1File%.hasinit preserve=no
  //## end cFMT1File::cFMT1File%.hasinit
  //## begin cFMT1File::cFMT1File%.initialization preserve=yes
  //## end cFMT1File::cFMT1File%.initialization
{
  //## begin cFMT1File::cFMT1File%.body preserve=yes
   _FileFormat = FMT_FMT1;
   _FileVersion = VERS_FMT1_FM;
  //## end cFMT1File::cFMT1File%.body
}

cFMT1File::cFMT1File(const cFMT1File &right)
  //## begin cFMT1File::cFMT1File%copy.hasinit preserve=no
  //## end cFMT1File::cFMT1File%copy.hasinit
  //## begin cFMT1File::cFMT1File%copy.initialization preserve=yes
  //## end cFMT1File::cFMT1File%copy.initialization
{
  //## begin cFMT1File::cFMT1File%copy.body preserve=yes
  //## end cFMT1File::cFMT1File%copy.body
}

cFMT1File::cFMT1File (CONST_STRING_T name, cFileSystem *file_system)
  //## begin cFMT1File::cFMT1File%1000119070.hasinit preserve=no
  //## end cFMT1File::cFMT1File%1000119070.hasinit
  //## begin cFMT1File::cFMT1File%1000119070.initialization preserve=yes
   : cFile(name, file_system)
  //## end cFMT1File::cFMT1File%1000119070.initialization
{
  //## begin cFMT1File::cFMT1File%1000119070.body preserve=yes
   _FileFormat = FMT_FMT1;
   _FileVersion = VERS_FMT1_FM;
  //## end cFMT1File::cFMT1File%1000119070.body
}


cFMT1File::~cFMT1File()
{
  //## begin cFMT1File::~cFMT1File%.body preserve=yes
  //## end cFMT1File::~cFMT1File%.body
}



//## Other Operations (implementation)
void cFMT1File::Save (cToolFileSystem *file_system)
{
  //## begin cFMT1File::Save%1062507900.body preserve=yes
  //## end cFMT1File::Save%1062507900.body
}

LONG_T cFMT1File::ComputeAddress (CONST_STRING_T spec)
{
  //## begin cFMT1File::ComputeAddress%1001057892.body preserve=yes
   long i_value = atoi(spec);
   int header_size = sizeof(OLD_FMT1_DISK_SUB_HEADER);
   long address = i_value * 2;
   return address;
  //## end cFMT1File::ComputeAddress%1001057892.body
}

// Additional Declarations
  //## begin cFMT1File%3B9C9DEE028D.declarations preserve=yes
  //## end cFMT1File%3B9C9DEE028D.declarations

//## begin module%3B9C9DEE028D.epilog preserve=yes
//## end module%3B9C9DEE028D.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cFMT1File::GetVariableValue%1000119059.body preserve=no
   int err = 0;
   if (_Size > 0) {
      OLD_FMT1_DISK_SUB_HEADER * sub_header = (OLD_FMT1_DISK_SUB_HEADER*)_FileBuffer->Memory();
      if (strcmp(name, "TOOL_NO") == 0) {
         long tool_no = sub_header->ToolNr;
         char _tool_no[32] = {0};
         ltoa(tool_no, _tool_no, 10);
         value = _tool_no;
         return 0;
      } else if (strcmp(name, "MATERIAL_NO") == 0) {
         long material_no = sub_header->MatNr;
         char _material_no[32] = {0};
         ltoa(material_no, _material_no, 10);
         value = _material_no;
         return 0;
      } else if (strcmp(name, "MACHINE_TYPE") == 0) {
         char _machine_type[64] = {0};
         sprintf(_machine_type, "FMT1");
         value = _machine_type;
         return 0;
      } else if (strcmp(name, "ARTICLE_NO") == 0) {
         return 0;
      } else {
         long address = ComputeAddress(name);
         if (address == -1) {
            return FILE_INVALID_VARIABLE;
         } else {
            char * ptr = (char*)_FileBuffer->Memory();
            ptr = &(ptr[address]);
            long l_value = *(unsigned short*)ptr;
            char c_value[32] = {0};
            ltoa(l_value, c_value, 10);
            value = c_value;
            return 0;
         }
      }
   } else {
      return FILE_EMPTY;
   }
//## end cFMT1File::GetVariableValue%1000119059.body

//## begin cFMT1File::GetTime%1000308654.body preserve=no
   cTimeObject time(0L);
   if (_Size > 0) {
      OLD_FMT1_DISK_SUB_HEADER * sub_header = (OLD_FMT1_DISK_SUB_HEADER*)_FileBuffer->Memory();
      unsigned int year = FMT1_GET_YEAR(sub_header->Date) + 1900;
      unsigned int month = FMT1_GET_MONTH(sub_header->Date);
      unsigned int day = FMT1_GET_DAY(sub_header->Date);
      unsigned int hour = FMT1_GET_HOUR(sub_header->Date);
      unsigned int minute = FMT1_GET_MIN(sub_header->Date);
      unsigned int second = 0;
      time.Set(cTimeObject::YEAR, year);
      time.Set(cTimeObject::MONTH, month);
      time.Set(cTimeObject::DAY, day);
      time.Set(cTimeObject::HOUR, hour);
      time.Set(cTimeObject::MINUTE, minute);
      time.Set(cTimeObject::SECOND, second);
   }
   return time;
//## end cFMT1File::GetTime%1000308654.body

#endif
