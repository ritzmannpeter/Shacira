//## begin module%3B9C9E450148.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9E450148.cm

//## begin module%3B9C9E450148.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9E450148.cp

//## Module: cFMT2File%3B9C9E450148; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT2File.cpp

//## begin module%3B9C9E450148.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9C9E450148.additionalIncludes

//## begin module%3B9C9E450148.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "fmt2.h"

//## end module%3B9C9E450148.includes

// cFMT2File
#include "Dnc/File/cFMT2File.h"
//## begin module%3B9C9E450148.additionalDeclarations preserve=yes
//## end module%3B9C9E450148.additionalDeclarations


// Class cFMT2File 

cFMT2File::cFMT2File()
  //## begin cFMT2File::cFMT2File%.hasinit preserve=no
  //## end cFMT2File::cFMT2File%.hasinit
  //## begin cFMT2File::cFMT2File%.initialization preserve=yes
  //## end cFMT2File::cFMT2File%.initialization
{
  //## begin cFMT2File::cFMT2File%.body preserve=yes
   _FileFormat = FMT_FMT2;
   _FileVersion = VERS_FMT2_FM;
  //## end cFMT2File::cFMT2File%.body
}

cFMT2File::cFMT2File(const cFMT2File &right)
  //## begin cFMT2File::cFMT2File%copy.hasinit preserve=no
  //## end cFMT2File::cFMT2File%copy.hasinit
  //## begin cFMT2File::cFMT2File%copy.initialization preserve=yes
  //## end cFMT2File::cFMT2File%copy.initialization
{
  //## begin cFMT2File::cFMT2File%copy.body preserve=yes
  //## end cFMT2File::cFMT2File%copy.body
}

cFMT2File::cFMT2File (CONST_STRING_T name, cFileSystem *file_system)
  //## begin cFMT2File::cFMT2File%1000119068.hasinit preserve=no
  //## end cFMT2File::cFMT2File%1000119068.hasinit
  //## begin cFMT2File::cFMT2File%1000119068.initialization preserve=yes
   : cFile(name, file_system)
  //## end cFMT2File::cFMT2File%1000119068.initialization
{
  //## begin cFMT2File::cFMT2File%1000119068.body preserve=yes
   _FileFormat = FMT_FMT2;
   _FileVersion = VERS_FMT2_FM;
  //## end cFMT2File::cFMT2File%1000119068.body
}


cFMT2File::~cFMT2File()
{
  //## begin cFMT2File::~cFMT2File%.body preserve=yes
  //## end cFMT2File::~cFMT2File%.body
}



//## Other Operations (implementation)
void cFMT2File::Save (cToolFileSystem *file_system)
{
  //## begin cFMT2File::Save%1062507898.body preserve=yes
  //## end cFMT2File::Save%1062507898.body
}

LONG_T cFMT2File::DINT2Long (LONG_T value)
{
  //## begin cFMT2File::DINT2Long%1000724934.body preserve=yes
   return (value >> 16) * 10000L + (value & 0x0000ffffL);
  //## end cFMT2File::DINT2Long%1000724934.body
}

LONG_T cFMT2File::ComputeAddress (CONST_STRING_T spec)
{
  //## begin cFMT2File::ComputeAddress%1001057895.body preserve=yes
   long i_value = atoi(spec);
   int header_size = (sizeof(OLD_DISK_HEADER) + sizeof(OLD_DISK_SUB_HEADER));
   long address = ((i_value-1) * 2) + header_size;
   return address;
  //## end cFMT2File::ComputeAddress%1001057895.body
}

// Additional Declarations
  //## begin cFMT2File%3B9C9E450148.declarations preserve=yes
  //## end cFMT2File%3B9C9E450148.declarations

//## begin module%3B9C9E450148.epilog preserve=yes
//## end module%3B9C9E450148.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cFMT2File::GetVariableValue%1000119055.body preserve=no
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
//## end cFMT2File::GetVariableValue%1000119055.body

//## begin cFMT2File::SetVariableValue%1000119056.body preserve=no
   return true;
//## end cFMT2File::SetVariableValue%1000119056.body

//## begin cFMT2File::GetTime%1000308648.body preserve=no
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
//## end cFMT2File::GetTime%1000308648.body

#endif
