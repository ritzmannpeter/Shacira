//## begin module%3B9C9E1602A9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9E1602A9.cm

//## begin module%3B9C9E1602A9.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9E1602A9.cp

//## Module: cFX25File%3B9C9E1602A9; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFX25File.cpp

//## begin module%3B9C9E1602A9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9C9E1602A9.additionalIncludes

//## begin module%3B9C9E1602A9.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "fx25.h"

//## end module%3B9C9E1602A9.includes

// cFX25File
#include "Dnc/File/cFX25File.h"
//## begin module%3B9C9E1602A9.additionalDeclarations preserve=yes
//## end module%3B9C9E1602A9.additionalDeclarations


// Class cFX25File 

cFX25File::cFX25File()
  //## begin cFX25File::cFX25File%.hasinit preserve=no
  //## end cFX25File::cFX25File%.hasinit
  //## begin cFX25File::cFX25File%.initialization preserve=yes
  //## end cFX25File::cFX25File%.initialization
{
  //## begin cFX25File::cFX25File%.body preserve=yes
   _FileFormat = FMT_FX25;
   _FileVersion = VERS_FX25_FX;
  //## end cFX25File::cFX25File%.body
}

cFX25File::cFX25File(const cFX25File &right)
  //## begin cFX25File::cFX25File%copy.hasinit preserve=no
  //## end cFX25File::cFX25File%copy.hasinit
  //## begin cFX25File::cFX25File%copy.initialization preserve=yes
  //## end cFX25File::cFX25File%copy.initialization
{
  //## begin cFX25File::cFX25File%copy.body preserve=yes
  //## end cFX25File::cFX25File%copy.body
}

cFX25File::cFX25File (CONST_STRING_T name, cFileSystem *file_system)
  //## begin cFX25File::cFX25File%1000119069.hasinit preserve=no
  //## end cFX25File::cFX25File%1000119069.hasinit
  //## begin cFX25File::cFX25File%1000119069.initialization preserve=yes
   : cFile(name, file_system)
  //## end cFX25File::cFX25File%1000119069.initialization
{
  //## begin cFX25File::cFX25File%1000119069.body preserve=yes
   _FileFormat = FMT_FX25;
   _FileVersion = VERS_FX25_FX;
  //## end cFX25File::cFX25File%1000119069.body
}


cFX25File::~cFX25File()
{
  //## begin cFX25File::~cFX25File%.body preserve=yes
  //## end cFX25File::~cFX25File%.body
}



//## Other Operations (implementation)
void cFX25File::Save (cToolFileSystem *file_system)
{
  //## begin cFX25File::Save%1062507899.body preserve=yes
  //## end cFX25File::Save%1062507899.body
}

LONG_T cFX25File::ComputeAddress (CONST_STRING_T spec)
{
  //## begin cFX25File::ComputeAddress%1001057896.body preserve=yes
   long i_value = atoi(spec);
   int header_size = sizeof(OLD_FX25_DISK_SUB_HEADER);
   long address = i_value * 2;
   return address;
  //## end cFX25File::ComputeAddress%1001057896.body
}

// Additional Declarations
  //## begin cFX25File%3B9C9E1602A9.declarations preserve=yes
  //## end cFX25File%3B9C9E1602A9.declarations

//## begin module%3B9C9E1602A9.epilog preserve=yes
//## end module%3B9C9E1602A9.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cFX25File::GetVariableValue%1000119057.body preserve=no
   int err = 0;
   if (_Size > 0) {
      OLD_FX25_DISK_SUB_HEADER * sub_header = (OLD_FX25_DISK_SUB_HEADER*)_FileBuffer->Memory();
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
         sprintf(_machine_type, "FX25");
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
//## end cFX25File::GetVariableValue%1000119057.body

//## begin cFX25File::GetTime%1000308651.body preserve=no
   cTimeObject time(0L);
   if (_Size > 0) {
      OLD_FX25_DISK_SUB_HEADER * sub_header = (OLD_FX25_DISK_SUB_HEADER*)_FileBuffer->Memory();
      unsigned int year = FX25_GET_YEAR(sub_header->Date) + 1900;
      unsigned int month = FX25_GET_MONTH(sub_header->Date);
      unsigned int day = FX25_GET_DAY(sub_header->Date);
      unsigned int hour = FX25_GET_HOUR(sub_header->Date);
      unsigned int minute = FX25_GET_MIN(sub_header->Date);
      unsigned int second = 0;
      time.Set(cTimeObject::YEAR, year);
      time.Set(cTimeObject::MONTH, month);
      time.Set(cTimeObject::DAY, day);
      time.Set(cTimeObject::HOUR, hour);
      time.Set(cTimeObject::MINUTE, minute);
      time.Set(cTimeObject::SECOND, second);
   }
   return time;
//## end cFX25File::GetTime%1000308651.body

#endif
