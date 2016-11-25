//## begin module%3B9CF6E3010D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CF6E3010D.cm

//## begin module%3B9CF6E3010D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CF6E3010D.cp

//## Module: cSimpleFileSystem%3B9CF6E3010D; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cSimpleFileSystem.cpp

//## begin module%3B9CF6E3010D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9CF6E3010D.additionalIncludes

//## begin module%3B9CF6E3010D.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

#include "syntax.h"
#include "errcode.h"
#include "iqtdev.h"
#include "devdisk.h"
#include "fmt1.h"
#include "fmt2.h"
#include "fx25.h"

//## end module%3B9CF6E3010D.includes

// cCarrierBase
#include "Dnc/Carrier/cCarrierBase.h"
// cCarrierSource
#include "Dnc/FileSystem/cCarrierSource.h"
// cSimpleFileSystem
#include "Dnc/FileSystem/cSimpleFileSystem.h"
//## begin module%3B9CF6E3010D.additionalDeclarations preserve=yes

#define MAX_FMT2_2F_FILES  1
#define MAX_FMT2_3F_FILES  1
#define MAX_FMT2_FILES     3
#define MAX_FMT1_FILES     3
#define MAX_FX25_FILES     3

//## end module%3B9CF6E3010D.additionalDeclarations


// Class cSimpleFileSystem 


cSimpleFileSystem::cSimpleFileSystem()
  //## begin cSimpleFileSystem::cSimpleFileSystem%.hasinit preserve=no
      : _Carrier(NULL)
  //## end cSimpleFileSystem::cSimpleFileSystem%.hasinit
  //## begin cSimpleFileSystem::cSimpleFileSystem%.initialization preserve=yes
  //## end cSimpleFileSystem::cSimpleFileSystem%.initialization
{
  //## begin cSimpleFileSystem::cSimpleFileSystem%.body preserve=yes
  //## end cSimpleFileSystem::cSimpleFileSystem%.body
}

cSimpleFileSystem::cSimpleFileSystem(const cSimpleFileSystem &right)
  //## begin cSimpleFileSystem::cSimpleFileSystem%copy.hasinit preserve=no
      : _Carrier(NULL)
  //## end cSimpleFileSystem::cSimpleFileSystem%copy.hasinit
  //## begin cSimpleFileSystem::cSimpleFileSystem%copy.initialization preserve=yes
  //## end cSimpleFileSystem::cSimpleFileSystem%copy.initialization
{
  //## begin cSimpleFileSystem::cSimpleFileSystem%copy.body preserve=yes
  //## end cSimpleFileSystem::cSimpleFileSystem%copy.body
}

cSimpleFileSystem::cSimpleFileSystem (cCarrierSource *file_source, CONST_STRING_T path)
  //## begin cSimpleFileSystem::cSimpleFileSystem%1000119103.hasinit preserve=no
      : _Carrier(NULL)
  //## end cSimpleFileSystem::cSimpleFileSystem%1000119103.hasinit
  //## begin cSimpleFileSystem::cSimpleFileSystem%1000119103.initialization preserve=yes
   , cFileSystem(path)
  //## end cSimpleFileSystem::cSimpleFileSystem%1000119103.initialization
{
  //## begin cSimpleFileSystem::cSimpleFileSystem%1000119103.body preserve=yes
   _Carrier = file_source->Carrier();
  //## end cSimpleFileSystem::cSimpleFileSystem%1000119103.body
}


cSimpleFileSystem::~cSimpleFileSystem()
{
  //## begin cSimpleFileSystem::~cSimpleFileSystem%.body preserve=yes
  //## end cSimpleFileSystem::~cSimpleFileSystem%.body
}



//## Other Operations (implementation)
INT_T cSimpleFileSystem::Format (INT_T format)
{
  //## begin cSimpleFileSystem::Format%1000119104.body preserve=yes
   _Format = FORMAT_UNKNOWN;
   switch (format) {
   case FMT_FMT2: return FMT2_Format();
   case FMT_FMT2_2F: return FMT2_2F_Format();
   case FMT_FMT2_3F: return FMT2_3F_Format();
//   case FMT_GRAPHIC_3F: return FMT2Graphic_Format();
   case FMT_FMT1: return FMT1_Format();
   case FMT_FX25: return FX25_Format();
   case FORMAT_UNKNOWN: return FSYS_UNKNOWN_FORMAT;
   default: return FSYS_INVALID_FORMAT;
   }
  //## end cSimpleFileSystem::Format%1000119104.body
}

INT_T cSimpleFileSystem::Directory (STRING_LIST_T &file_names)
{
  //## begin cSimpleFileSystem::Directory%1000119105.body preserve=yes
   _Format = FORMAT_UNKNOWN;
   if (FMT2_TestChecksum()) return FMT2_Directory(file_names);
   if (FMT2_2F_TestChecksum()) return FMT2_2F_Directory(file_names);
   if (FMT2_3F_TestChecksum()) return FMT2_3F_Directory(file_names);
   if (FMT1_TestChecksum()) return FMT1_Directory(file_names);
   if (FX25_TestChecksum()) return FX25_Directory(file_names);
   return _Format;
  //## end cSimpleFileSystem::Directory%1000119105.body
}

LONG_T cSimpleFileSystem::Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::Load%1000119106.body preserve=yes
   switch (_Format) {
   case FMT_FMT2: return FMT2_Load(file_name, buf, buf_size);
   case FMT_FMT2_2F: return FMT2_2F_Load(file_name, buf, buf_size);
   case FMT_FMT2_3F: return FMT2_3F_Load(file_name, buf, buf_size);
//   case FMT_GRAPHIC_3F: return FMT2Graphic_Load(file_name, buf, buf_size);
   case FMT_FMT1: return FMT1_Load(file_name, buf, buf_size);
   case FMT_FX25: return FX25_Load(file_name, buf, buf_size);
   case FORMAT_UNKNOWN: return FSYS_UNKNOWN_FORMAT;
   default: return FSYS_INVALID_FORMAT;
   }
  //## end cSimpleFileSystem::Load%1000119106.body
}

LONG_T cSimpleFileSystem::Save (CONST_STRING_T file_name, void *buf, ULONG_T size)
{
  //## begin cSimpleFileSystem::Save%1000119107.body preserve=yes
   switch (_Format) {
   case FMT_FMT2: return FMT2_Save(file_name, buf, size);
   case FMT_FMT2_2F: return FMT2_2F_Save(file_name, buf, size);
   case FMT_FMT2_3F: return FMT2_3F_Save(file_name, buf, size);
//   case FMT_FMT2_GRAPHIC: return FMT2Graphic_Save(file_name, buf, size);
   case FMT_FMT1: return FMT1_Save(file_name, buf, size);
   case FMT_FX25: return FX25_Save(file_name, buf, size);
   case FORMAT_UNKNOWN: return FSYS_UNKNOWN_FORMAT;
   default: return FSYS_INVALID_FORMAT;
   }
  //## end cSimpleFileSystem::Save%1000119107.body
}

INT_T cSimpleFileSystem::Delete (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::Delete%1000119108.body preserve=yes
   switch (_Format) {
   case FMT_FMT2: return FMT2_Delete(file_name);
   case FMT_FMT2_2F: return FMT2_2F_Delete(file_name);
   case FMT_FMT2_3F: return FMT2_3F_Delete(file_name);
//   case FMT_FMT2_GRAPHIC: return FMT2Graphic_Delete(file_name);
   case FMT_FMT1: return FMT1_Delete(file_name);
   case FMT_FX25: return FX25_Delete(file_name);
   case FORMAT_UNKNOWN: return FSYS_UNKNOWN_FORMAT;
   default: return FSYS_INVALID_FORMAT;
   }
  //## end cSimpleFileSystem::Delete%1000119108.body
}

LONG_T cSimpleFileSystem::FileSize (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FileSize%1000386734.body preserve=yes
   switch (_Format) {
   case FMT_FMT2: return FMT2_FileSize(file_name);
   case FMT_FMT2_2F: return FMT2_2F_FileSize(file_name);
   case FMT_FMT2_3F: return FMT2_3F_FileSize(file_name);
//   case FMT_FMT2_GRAPHIC: return FMT2Graphic_FileSize(file_name);
   case FMT_FMT1: return FMT1_FileSize(file_name);
   case FMT_FX25: return FX25_FileSize(file_name);
   case FORMAT_UNKNOWN: return FSYS_UNKNOWN_FORMAT;
   default: return FSYS_INVALID_FORMAT;
   }
  //## end cSimpleFileSystem::FileSize%1000386734.body
}

cFile * cSimpleFileSystem::File (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::File%1000386735.body preserve=yes
   switch (_Format) {
   case FMT_FMT2: return new cFMT2File(file_name, this);
   case FMT_FMT2_2F: return new cFMT2_2FFile(file_name, this);
   case FMT_FMT2_3F: return new cFMT2_3FFile(file_name, this);
//   case FMT_FMT2_GRAPHIC: return new cFMT2GraphicFile(file_name, this);
   case FMT_FMT1: return new cFMT1File(file_name, this);
   case FMT_FX25: return new cFX25File(file_name, this);
   case FORMAT_UNKNOWN: return NULL;
   default: return NULL;
   }
  //## end cSimpleFileSystem::File%1000386735.body
}

cTimeObject cSimpleFileSystem::GetTime (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::GetTime%1000456415.body preserve=yes
   cTimeObject time(0L);
   switch (_Format) {
   case FMT_FMT2: return FMT2_GetTime(file_name);
   case FMT_FMT2_2F: return FMT2_2F_GetTime(file_name);
   case FMT_FMT2_3F: return FMT2_3F_GetTime(file_name);
//   case FMT_FMT2_GRAPHIC: return FMT2Graphic_GetTime(file_name);
   case FMT_FMT1: return FMT1_GetTime(file_name);
   case FMT_FX25: return FX25_GetTime(file_name);
   }
   return time;
  //## end cSimpleFileSystem::GetTime%1000456415.body
}

INT_T cSimpleFileSystem::Read (ULONG_T address, ULONG_T bytes, void *buffer)
{
  //## begin cSimpleFileSystem::Read%1000195348.body preserve=yes
   if (_Carrier == NULL) return FSYS_NO_CARRIER;
   int nread = _Carrier->Read(buffer, address, bytes);
   if (nread == bytes) {
      return 0;
   } else {
      return nread;
   }
  //## end cSimpleFileSystem::Read%1000195348.body
}

INT_T cSimpleFileSystem::Write (ULONG_T address, ULONG_T bytes, void *buffer)
{
  //## begin cSimpleFileSystem::Write%1000195349.body preserve=yes
   if (_Carrier == NULL) return FSYS_NO_CARRIER;
   int nwrite = _Carrier->Write(buffer, address, bytes);
   if (nwrite == bytes) {
      return 0;
   } else {
      return nwrite;
   }
  //## end cSimpleFileSystem::Write%1000195349.body
}

UCHAR_T cSimpleFileSystem::Checksum (const UCHAR_T *buffer, ULONG_T address, ULONG_T offset)
{
  //## begin cSimpleFileSystem::Checksum%1000195350.body preserve=yes
   unsigned val;
   unsigned char checksum;
   long i;
   checksum = 0;
   for (i=address; i<address+offset; i++) {
      val = buffer[i];
      checksum ^= val;
   }
   return checksum;
  //## end cSimpleFileSystem::Checksum%1000195350.body
}

BOOL_T cSimpleFileSystem::FMT2_TestChecksum ()
{
  //## begin cSimpleFileSystem::FMT2_TestChecksum%1000195345.body preserve=yes
   int err = 0;
   char temp_buf[4096] = {0};
   unsigned char checksum1 = 0, checksum2 = 0, checksum3 = 0, checksum = 0;
   if ((err = Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return false;
   if ((err = Read(ADR_LIST_1, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, DATA_SIZE);
   if (checksum1 != checksum) return false;
   if ((err = Read(0x3f, 1, &checksum2)) != USR_NO_ERROR) return false;
   if ((err = Read(ADR_LIST_2, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, DATA_SIZE);
   if (checksum2 != checksum) return false;
   if ((err = Read(0x57, 1, &checksum3)) != USR_NO_ERROR) return false;
   if ((err = Read(ADR_LIST_3, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, DATA_SIZE);
   if (checksum3 != checksum) return false;
   return true;
  //## end cSimpleFileSystem::FMT2_TestChecksum%1000195345.body
}

BOOL_T cSimpleFileSystem::FMT2_2F_TestChecksum ()
{
  //## begin cSimpleFileSystem::FMT2_2F_TestChecksum%1000195346.body preserve=yes
   int err;
   char temp_buf[4096] = {0};
   unsigned char checksum1 = 0, checksum = 0;
   if ((err = Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return false;
   if ((err = Read(ADR_LIST_2F, DATA_SIZE_2F, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, DATA_SIZE_2F);
   if (checksum1 != checksum) return false;
   return true;
  //## end cSimpleFileSystem::FMT2_2F_TestChecksum%1000195346.body
}

BOOL_T cSimpleFileSystem::FMT2_3F_TestChecksum ()
{
  //## begin cSimpleFileSystem::FMT2_3F_TestChecksum%1000195347.body preserve=yes
   int err;
   char temp_buf[4096] = {0};
   unsigned char checksum1 = 0, checksum = 0;
   if ((err = Read(0x27, 1, &checksum1)) != USR_NO_ERROR) return false;
   if ((err = Read(ADR_LIST_3F, DATA_SIZE_3F, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, DATA_SIZE_3F);
   if (checksum1 != checksum) return false;
   return true;
  //## end cSimpleFileSystem::FMT2_3F_TestChecksum%1000195347.body
}

BOOL_T cSimpleFileSystem::FMT1_TestChecksum ()
{
  //## begin cSimpleFileSystem::FMT1_TestChecksum%1000195351.body preserve=yes
   int err = 0;
   char temp_buf[4096] = {0};
   unsigned char checksum1 = 0, checksum2 = 0, checksum3 = 0, checksum = 0;
   if ((err = Read(64, 960, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, 960);
   if ((err = Read(0x01d, 1, &checksum1)) != USR_NO_ERROR) return false;
   if (checksum1 != checksum) return false;
   if ((err = Read(0x41d, 1, &checksum1)) != USR_NO_ERROR) return false;
   if (checksum1 != checksum) return false;
   if ((err = Read(0x81d, 1, &checksum1)) != USR_NO_ERROR) return false;
   if (checksum1 != checksum) return false;
   if ((err = Read(64 + 0x400, 960, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, 960);
   if ((err = Read(0x01c, 1, &checksum2)) != USR_NO_ERROR) return false;
   if (checksum2 != checksum) return false;
   if ((err = Read(0x41c, 1, &checksum2)) != USR_NO_ERROR) return false;
   if (checksum2 != checksum) return false;
   if ((err = Read(0x81c, 1, &checksum2)) != USR_NO_ERROR) return false;
   if (checksum2 != checksum) return false;
   if ((err = Read(64 + 0x800, 960, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, 960);
   if ((err = Read(0x01e, 1, &checksum3)) != USR_NO_ERROR) return false;
   if (checksum3 != checksum) return false;
   if ((err = Read(0x41e, 1, &checksum3)) != USR_NO_ERROR) return false;
   if (checksum3 != checksum) return false;
   if ((err = Read(0x81e, 1, &checksum3)) != USR_NO_ERROR) return false;
   if (checksum3 != checksum) return false;
   return true;
  //## end cSimpleFileSystem::FMT1_TestChecksum%1000195351.body
}

BOOL_T cSimpleFileSystem::FX25_TestChecksum ()
{
  //## begin cSimpleFileSystem::FX25_TestChecksum%1000195352.body preserve=yes
   int err = 0;
   char temp_buf[4096] = {0};
   unsigned char checksum1 = 0, checksum2 = 0, checksum3 = 0, checksum = 0;
   if ((err = Read(64, 960, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, 960);
   checksum--;
   if ((err = Read(0x01d, 1, &checksum1)) != USR_NO_ERROR) return false;
   if (checksum1 != checksum) return false;
   if ((err = Read(0x41d, 1, &checksum1)) != USR_NO_ERROR) return false;
   if (checksum1 != checksum) return false;
   if ((err = Read(0x81d, 1, &checksum1)) != USR_NO_ERROR) return false;
   if (checksum1 != checksum) return false;
   if ((err = Read(64 + 0x400, 960, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, 960);
   checksum--;
   if ((err = Read(0x01c, 1, &checksum2)) != USR_NO_ERROR) return false;
   if (checksum2 != checksum) return false;
   if ((err = Read(0x41c, 1, &checksum2)) != USR_NO_ERROR) return false;
   if (checksum2 != checksum) return false;
   if ((err = Read(0x81c, 1, &checksum2)) != USR_NO_ERROR) return false;
   if (checksum2 != checksum) return false;
   if ((err = Read(64 + 0x800, 960, temp_buf)) != USR_NO_ERROR) return false;
   checksum = Checksum(temp_buf, 0, 960);
   checksum--;
   if ((err = Read(0x01e, 1, &checksum3)) != USR_NO_ERROR) return false;
   if (checksum3 != checksum) return false;
   if ((err = Read(0x41e, 1, &checksum3)) != USR_NO_ERROR) return false;
   if (checksum3 != checksum) return false;
   if ((err = Read(0x81e, 1, &checksum3)) != USR_NO_ERROR) return false;
   if (checksum3 != checksum) return false;
   return true;
  //## end cSimpleFileSystem::FX25_TestChecksum%1000195352.body
}

INT_T cSimpleFileSystem::FMT2_Directory (STRING_LIST_T &file_names)
{
  //## begin cSimpleFileSystem::FMT2_Directory%1000195353.body preserve=yes
   _Format = FMT_FMT2;
   int i, err;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER sub_header;
   if ((err = Read((long)ADR_HEADER, sizeof(header), &header)) != USR_NO_ERROR) return err;
   for (i=0; i<MAX_FMT2_FILES; i++) {
      long carrierpos = FMT2_CarrierPos(i + 1, ID_SUBHEADER);
      if ((err = Read(carrierpos, sizeof(sub_header), &sub_header)) != USR_NO_ERROR) return err;
//      if (sub_header.Date[1] != 0) {
      if (true) {
         char file_name[128] = {0};
         MakeFileName(file_name, i + 1);
         file_names.push_back(file_name);
      }
   }
   return _Format;
  //## end cSimpleFileSystem::FMT2_Directory%1000195353.body
}

INT_T cSimpleFileSystem::FMT2_2F_Directory (STRING_LIST_T &file_names)
{
  //## begin cSimpleFileSystem::FMT2_2F_Directory%1000195354.body preserve=yes
   _Format = FMT_FMT2_2F;
   char file_name[128] = {0};
   MakeFileName(file_name, 1);
   file_names.push_back(file_name);
   return _Format;
  //## end cSimpleFileSystem::FMT2_2F_Directory%1000195354.body
}

INT_T cSimpleFileSystem::FMT2_3F_Directory (STRING_LIST_T &file_names)
{
  //## begin cSimpleFileSystem::FMT2_3F_Directory%1000195355.body preserve=yes
   _Format = FMT_FMT2_3F;
   char file_name[128] = {0};
   MakeFileName(file_name, 1);
   file_names.push_back(file_name);
   return _Format;
  //## end cSimpleFileSystem::FMT2_3F_Directory%1000195355.body
}

INT_T cSimpleFileSystem::FMT1_Directory (STRING_LIST_T &file_names)
{
  //## begin cSimpleFileSystem::FMT1_Directory%1000195356.body preserve=yes
   _Format = FMT_FMT1;
   int err = 0;
   for (int i=0; i<MAX_FMT1_FILES; i++) {
      char file_name[128] = {0};
      MakeFileName(file_name, i + 1);
      file_names.push_back(file_name);
   }
   return _Format;
  //## end cSimpleFileSystem::FMT1_Directory%1000195356.body
}

INT_T cSimpleFileSystem::FX25_Directory (STRING_LIST_T &file_names)
{
  //## begin cSimpleFileSystem::FX25_Directory%1000195357.body preserve=yes
   _Format = FMT_FX25;
   int err = 0;
   for (int i=0; i<MAX_FX25_FILES; i++) {
      char file_name[128] = {0};
      MakeFileName(file_name, i + 1);
      file_names.push_back(file_name);
   }
   return _Format;
  //## end cSimpleFileSystem::FX25_Directory%1000195357.body
}

LONG_T cSimpleFileSystem::FMT2_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT2_Load%1000195359.body preserve=yes
   unsigned long file_size = 0L;
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   int err = 0;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER sub_header;
   long carrierpos;
   long size;
   char * buf_ptr = (char*)buf;
   carrierpos = (long)ADR_HEADER;
   file_size += size = sizeof(header);
   if (file_size > buf_size) return FSYS_BUF_SIZE;
   if ((err = Read(carrierpos, size, &header)) != USR_NO_ERROR) return err;
   memcpy(buf_ptr, &header, size);
   buf_ptr += size;
   carrierpos = FMT2_CarrierPos(file_no, ID_SUBHEADER);
   file_size += size = sizeof(sub_header);
   if (file_size > buf_size) return FSYS_BUF_SIZE;
   if ((err = Read(carrierpos, size, &sub_header)) != USR_NO_ERROR) return err;
   memcpy(buf_ptr, &sub_header, size);
   buf_ptr += size;
   carrierpos = FMT2_CarrierPos(file_no, ID_LIST);
   file_size += size = DATA_SIZE;
   if (file_size > buf_size) return FSYS_BUF_SIZE;
   if ((err = Read(carrierpos, size, buf_ptr)) != USR_NO_ERROR) return err;
   buf_ptr += size;
   carrierpos = (long)ADR_TEXT;
   file_size += size = header.TextLength;
   if (file_size > buf_size) return FSYS_BUF_SIZE;
   if ((err = Read(carrierpos, size, buf_ptr)) != USR_NO_ERROR) return err;
   return file_size;
  //## end cSimpleFileSystem::FMT2_Load%1000195359.body
}

LONG_T cSimpleFileSystem::FMT2_2F_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT2_2F_Load%1000195360.body preserve=yes
   OLD_DISK_HEADER header;
   SUB_HEADER_2F sub_header;
   char * buffer_ptr = (char*)buf;
   long carrierpos = (long)ADR_HEADER;
   long file_size = 0;
   long size = sizeof(header);
   int err = 0;
   if ((err = Read(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &header, size);
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_SUBHEADER_2F;
   size = sizeof(sub_header);
   if ((err = Read(carrierpos, size, (char*)&sub_header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &sub_header, size);
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_LIST_2F;
   size = DATA_SIZE_2F;
   if ((err = Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   file_size += size;
   return file_size;
  //## end cSimpleFileSystem::FMT2_2F_Load%1000195360.body
}

LONG_T cSimpleFileSystem::FMT2_3F_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT2_3F_Load%1000195361.body preserve=yes
   OLD_DISK_HEADER header;
   SUB_HEADER_3F sub_header;
   char * buffer_ptr = (char*)buf;
   long carrierpos = (long)ADR_HEADER;
   long file_size = 0;
   long size = sizeof(header);
   int err = 0;
   if ((err = Read(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &header, size);
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_SUBHEADER_3F;
   size = sizeof(sub_header);
   if ((err = Read(carrierpos, size, (char*)&sub_header)) != USR_NO_ERROR) return err;
   memcpy(buffer_ptr, &sub_header, size);
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_LIST_3F;
   size = DATA_SIZE_3F;
   if ((err = Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = Read(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   file_size += size;
   return file_size;
  //## end cSimpleFileSystem::FMT2_3F_Load%1000195361.body
}

LONG_T cSimpleFileSystem::FMT1_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT1_Load%1000195362.body preserve=yes
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   int err = 0;
   long carrierpos = FMT1_CarrierPos(file_no, 0);
   long file_size = OLD_SIZE_FMT1;
   if ((err = Read(carrierpos, file_size, buf)) != USR_NO_ERROR) return err;
   return file_size;
  //## end cSimpleFileSystem::FMT1_Load%1000195362.body
}

LONG_T cSimpleFileSystem::FX25_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FX25_Load%1000195363.body preserve=yes
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   int err = 0;
   long carrierpos = FX25_CarrierPos(file_no, 0);
   long file_size = OLD_SIZE_FX;
   if ((err = Read(carrierpos, file_size, buf)) != USR_NO_ERROR) return err;
   return file_size;
  //## end cSimpleFileSystem::FX25_Load%1000195363.body
}

LONG_T cSimpleFileSystem::FMT2_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT2_Save%1000195364.body preserve=yes
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   int err = 0;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER sub_header;
   long file_size = 0;
   char * buffer_ptr = (char*)buf;
   long carrierpos = (long)ADR_HEADER;
   long size = sizeof(header);
   memcpy(&header, buffer_ptr, size);
   if (header.TextLength > MAX_TEXT_LEN) header.TextLength = MAX_TEXT_LEN;
   if ((err = Write(carrierpos, size, &header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = FMT2_CarrierPos(file_no, ID_SUBHEADER);
   size = sizeof(sub_header);
   memcpy(&sub_header, buffer_ptr, size);
   if ((err = Write(carrierpos, size, &sub_header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = FMT2_CarrierPos(file_no, ID_LIST);
   size = DATA_SIZE;
   if ((err = Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   file_size += size;
   if ((err = FMT2_MakeChecksum(file_no)) != USR_NO_ERROR) {
      return err;
   } else {
      return file_size;
   }
  //## end cSimpleFileSystem::FMT2_Save%1000195364.body
}

LONG_T cSimpleFileSystem::FMT2_2F_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT2_2F_Save%1000195365.body preserve=yes
   int err = 0;
   OLD_DISK_HEADER header;
   SUB_HEADER_2F sub_header;
   char * buffer_ptr = (char*)buf;
   long file_size = 0;
   long carrierpos = (long)ADR_HEADER;
   long size = sizeof(header);
   memcpy(&header, buffer_ptr, size);
   if (header.TextLength > MAX_TEXT_LEN) header.TextLength = MAX_TEXT_LEN;
   if ((err = Write(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_SUBHEADER_2F;
   size = sizeof(sub_header);
   memcpy(&sub_header, buffer_ptr, size);
   if ((err = Write(carrierpos, size, (char*)&sub_header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_LIST_2F;
   size = DATA_SIZE_2F;
   if ((err = Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   file_size += size;
   if ((err = FMT2_2F_MakeChecksum(0)) != USR_NO_ERROR) {
      return err;
   } else {
      return file_size;
   }
  //## end cSimpleFileSystem::FMT2_2F_Save%1000195365.body
}

LONG_T cSimpleFileSystem::FMT2_3F_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT2_3F_Save%1000195366.body preserve=yes
   int err = 0;
   OLD_DISK_HEADER header;
   SUB_HEADER_3F sub_header;
   char * buffer_ptr = (char*)buf;
   long file_size = 0;
   long carrierpos = (long)ADR_HEADER;
   long size = sizeof(header);
   memcpy(&header, buffer_ptr, size);
   if (header.TextLength > MAX_TEXT_LEN) header.TextLength = MAX_TEXT_LEN;
   if ((err = Write(carrierpos, size, (char*)&header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_SUBHEADER_3F;
   size = sizeof(sub_header);
   memcpy(&sub_header, buffer_ptr, size);
   if ((err = Write(carrierpos, size, (char*)&sub_header)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   file_size += size;
   carrierpos = ADR_LIST_3F;
   size = DATA_SIZE_3F;
   if ((err = Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   buffer_ptr += size;
   carrierpos = (long)ADR_TEXT;
   size = header.TextLength;
   if ((err = Write(carrierpos, size, buffer_ptr)) != USR_NO_ERROR) return err;
   file_size += size;
   if ((err = FMT2_3F_MakeChecksum(0)) != USR_NO_ERROR) {
      return err;
   } else {
      return file_size;
   }
  //## end cSimpleFileSystem::FMT2_3F_Save%1000195366.body
}

LONG_T cSimpleFileSystem::FMT1_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FMT1_Save%1000195367.body preserve=yes
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   char * buf_ptr = (char*)buf;
   long carrierpos = FMT1_CarrierPos(file_no, 0);
   long file_size = OLD_SIZE_FMT1;
   int err = 0;
   if ((err = Write(carrierpos, file_size, buf_ptr)) != USR_NO_ERROR) return err;
   if ((err = FMT1_MakeChecksum(1)) != USR_NO_ERROR) return err;
   if ((err = FMT1_MakeChecksum(2)) != USR_NO_ERROR) return err;
   if ((err = FMT1_MakeChecksum(3)) != USR_NO_ERROR) return err;
   return file_size;
  //## end cSimpleFileSystem::FMT1_Save%1000195367.body
}

LONG_T cSimpleFileSystem::FX25_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cSimpleFileSystem::FX25_Save%1000195368.body preserve=yes
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   char * buf_ptr = (char*)buf;
   long carrierpos = FX25_CarrierPos(file_no, 0);
   long file_size = OLD_SIZE_FX;
   int err = 0;
   if ((err = Write(carrierpos, file_size, buf_ptr)) != USR_NO_ERROR) return err;
   if ((err = FX25_MakeChecksum(1)) != USR_NO_ERROR) return err;
   if ((err = FX25_MakeChecksum(2)) != USR_NO_ERROR) return err;
   if ((err = FX25_MakeChecksum(3)) != USR_NO_ERROR) return err;
   return file_size;
  //## end cSimpleFileSystem::FX25_Save%1000195368.body
}

INT_T cSimpleFileSystem::FMT2_Delete (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_Delete%1000195369.body preserve=yes
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   OLD_DISK_SUB_HEADER sub_header;
   memset(&sub_header, 0, sizeof(sub_header));
   long carrierpos = FMT2_CarrierPos(file_no, ID_SUBHEADER);
   int err = 0;
   if ((err = Write(carrierpos, sizeof(sub_header), &sub_header)) != USR_NO_ERROR) return err;
   if ((err = FMT2_MakeChecksum(file_no)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT2_Delete%1000195369.body
}

INT_T cSimpleFileSystem::FMT2_2F_Delete (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_2F_Delete%1000195370.body preserve=yes
   SUB_HEADER_2F sub_header;
   memset(&sub_header, 0, sizeof(sub_header));
   long carrierpos = ADR_SUBHEADER_2F;
   int err = 0;
   if ((err = Write(carrierpos, sizeof(sub_header),
                   (char*)&sub_header)) != USR_NO_ERROR) return err;
   if ((err = FMT2_2F_MakeChecksum(0)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT2_2F_Delete%1000195370.body
}

INT_T cSimpleFileSystem::FMT2_3F_Delete (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_3F_Delete%1000195371.body preserve=yes
   SUB_HEADER_3F sub_header;
   memset(&sub_header, 0, sizeof(sub_header));
   long carrierpos = ADR_SUBHEADER_3F;
   int err = 0;
   if ((err = Write(carrierpos, sizeof(sub_header),
                   (char*)&sub_header)) != USR_NO_ERROR) return err;
   if ((err = FMT2_3F_MakeChecksum(0)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT2_3F_Delete%1000195371.body
}

INT_T cSimpleFileSystem::FMT1_Delete (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT1_Delete%1000195372.body preserve=yes
   char temp_buf[4096] = {0};
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   OLD_FMT1_DISK_SUB_HEADER sub_header;
   long size = OLD_SIZE_FMT1;
   memset(&sub_header, 0, sizeof(sub_header));
   sub_header.LenHeader = 32;
   memcpy(temp_buf, &sub_header, sizeof(sub_header));
   long carrierpos = FMT1_CarrierPos(file_no, 0);
   int err = 0;
   if ((err = Write(carrierpos, size, temp_buf)) != USR_NO_ERROR) return err;
   if ((err = FMT1_MakeChecksum(1)) != USR_NO_ERROR) return err;
   if ((err = FMT1_MakeChecksum(2)) != USR_NO_ERROR) return err;
   if ((err = FMT1_MakeChecksum(3)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT1_Delete%1000195372.body
}

INT_T cSimpleFileSystem::FX25_Delete (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FX25_Delete%1000195373.body preserve=yes
   char temp_buf[4096] = {0};
   int file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   OLD_FX25_DISK_SUB_HEADER sub_header;
   long size = OLD_SIZE_FX;
   memset(&sub_header, 0, sizeof(sub_header));
   sub_header.LenHeader = 32;
   memcpy(temp_buf, &sub_header, sizeof(sub_header));
   long carrierpos = FX25_CarrierPos(file_no, 0);
   int err = 0;
   if ((err = Write(carrierpos, size, temp_buf)) != USR_NO_ERROR) return err;
   if ((err = FX25_MakeChecksum(1)) != USR_NO_ERROR) return err;
   if ((err = FX25_MakeChecksum(2)) != USR_NO_ERROR) return err;
   if ((err = FX25_MakeChecksum(3)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FX25_Delete%1000195373.body
}

LONG_T cSimpleFileSystem::DINT2Long (LONG_T value)
{
  //## begin cSimpleFileSystem::DINT2Long%1000195374.body preserve=yes
   return (value >> 16) * 10000L + (value & 0x0000ffffL);
  //## end cSimpleFileSystem::DINT2Long%1000195374.body
}

INT_T cSimpleFileSystem::FileNo (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FileNo%1000195375.body preserve=yes
   int file_no = -1;
   char comp_file_name[256] = {0};
   sprintf(comp_file_name, "%s", file_name);
   strupr(comp_file_name);
   if (sscanf(comp_file_name, "OLDCAR.%d", &file_no) == 1) {
      return file_no;
   } else {
      return -1;
   }
  //## end cSimpleFileSystem::FileNo%1000195375.body
}

CONST_STRING_T cSimpleFileSystem::MakeFileName (CHAR_T *buffer, INT_T file_no)
{
  //## begin cSimpleFileSystem::MakeFileName%1000195378.body preserve=yes
   sprintf(buffer, "OLDCAR.%03d", file_no);
   return buffer;
  //## end cSimpleFileSystem::MakeFileName%1000195378.body
}

INT_T cSimpleFileSystem::FMT2_MakeChecksum (INT_T file_no)
{
  //## begin cSimpleFileSystem::FMT2_MakeChecksum%1000724910.body preserve=yes
   unsigned char checksum = 0;
   int err = 0;
   char temp_buf[4096] = {0};
   switch (file_no) {
   case 1:
      if ((err = Read(ADR_LIST_1, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, DATA_SIZE);
      if ((err = Write(0x27, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   case 2:
      if ((err = Read(ADR_LIST_2, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, DATA_SIZE);
      if ((err = Write(0x3f, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   case 3:
      if ((err = Read(ADR_LIST_3, DATA_SIZE, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, DATA_SIZE);
      if ((err = Write(0x57, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   }
   return 0;
  //## end cSimpleFileSystem::FMT2_MakeChecksum%1000724910.body
}

INT_T cSimpleFileSystem::FMT2_2F_MakeChecksum (INT_T file_no)
{
  //## begin cSimpleFileSystem::FMT2_2F_MakeChecksum%1000724911.body preserve=yes
   char temp_buf[4096] = {0};
   unsigned char checksum = 0;
   int err = 0;
   if ((err = Read(ADR_LIST_2F, DATA_SIZE_2F, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE_2F);
   if ((err = Write(0x27, 1, &checksum)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT2_2F_MakeChecksum%1000724911.body
}

INT_T cSimpleFileSystem::FMT2_3F_MakeChecksum (INT_T file_no)
{
  //## begin cSimpleFileSystem::FMT2_3F_MakeChecksum%1000724912.body preserve=yes
   char temp_buf[4096] = {0};
   unsigned char checksum = 0;
   int err = 0;
   if ((err = Read(ADR_LIST_3F, DATA_SIZE_3F, temp_buf)) != USR_NO_ERROR) return err;
   checksum = Checksum(temp_buf, 0, DATA_SIZE_3F);
   if ((err = Write(0x27, 1, &checksum)) != USR_NO_ERROR) return err;
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT2_3F_MakeChecksum%1000724912.body
}

INT_T cSimpleFileSystem::FMT1_MakeChecksum (INT_T file_no)
{
  //## begin cSimpleFileSystem::FMT1_MakeChecksum%1000724913.body preserve=yes
   char temp_buf[4096] = {0};
   unsigned char checksum = 0;
   int err = 0;
   unsigned short prog_len;
   switch (file_no) {
   case 1:
      if ((err = Read(64, 960, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, 960);
      if ((err = Write(0x01d, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x41d, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x81d, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   case 2:
      if ((err = Read(64 + 0x400, 960, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, 960);
      if ((err = Write(0x01c, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x41c, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x81c, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   case 3:
      if ((err = Read(64 + 0x800, 960, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, 960);
      if ((err = Write(0x01e, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x41e, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x81e, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   }
   if ((err = Read(14, 2, temp_buf)) != USR_NO_ERROR) return err;
   prog_len = (((unsigned int)temp_buf[1])<<8) | ((unsigned int)temp_buf[0]);
   if ((prog_len > 0) && (prog_len < 32)) {
      if ((err = Read(0, prog_len, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, prog_len);
      if ((err = Write(31, 1, &checksum)) != USR_NO_ERROR) return err;
   }
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT1_MakeChecksum%1000724913.body
}

INT_T cSimpleFileSystem::FX25_MakeChecksum (INT_T file_no)
{
  //## begin cSimpleFileSystem::FX25_MakeChecksum%1000724914.body preserve=yes
   char temp_buf[4096] = {0};
   unsigned char checksum = 0;
   unsigned short prog_len;
   int err = 0;
   switch (file_no) {
   case 1:
      if ((err = Read(64, 960, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, 960);
      checksum--;
      if ((err = Write(0x01d, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x41d, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x81d, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   case 2:
      if ((err = Read(64 + 0x400, 960, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, 960);
      checksum--;
      if ((err = Write(0x01c, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x41c, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x81c, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   case 3:
      if ((err = Read(64 + 0x800, 960, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, 960);
      checksum--;
      if ((err = Write(0x01e, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x41e, 1, &checksum)) != USR_NO_ERROR) return err;
      if ((err = Write(0x81e, 1, &checksum)) != USR_NO_ERROR) return err;
      break;
   }
   if ((err = Read(14, 2, temp_buf)) != USR_NO_ERROR) return err;
   prog_len = (((unsigned int)temp_buf[1])<<8) | ((unsigned int)temp_buf[0]);
   if ((prog_len > 0) && (prog_len < 32)) {
      if ((err = Read(0, prog_len, temp_buf)) != USR_NO_ERROR) return err;
      checksum = Checksum(temp_buf, 0, prog_len);
      if ((err = Write(31, 1, &checksum)) != USR_NO_ERROR) return err;
   }
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FX25_MakeChecksum%1000724914.body
}

INT_T cSimpleFileSystem::FMT2_Format ()
{
  //## begin cSimpleFileSystem::FMT2_Format%1000724915.body preserve=yes
   int i, err = 0;
   OLD_DISK_HEADER header;
   OLD_DISK_SUB_HEADER sub_header;
   long carrierpos;
   memset(&header, 0, sizeof(header));
   header.TextLength = 8;
   header.ProcNr = 1001;
   header.CarrierNr = 0;
   header.CarrierLength = 0;
   header.Id = 1;
   header.CheckSum = 0;
   memset(&sub_header, 0, sizeof(sub_header));
   if ((err = Write((long)ADR_HEADER, sizeof(header), &header)) != USR_NO_ERROR) return err;
   for (i=0; i<MAX_FMT2_FILES; i++) {
      carrierpos = FMT2_CarrierPos(i + 1, ID_SUBHEADER);
      if ((err = Write(carrierpos, sizeof(sub_header), &sub_header)) != USR_NO_ERROR) return err;
      if ((err = FMT2_MakeChecksum(i + 1)) != USR_NO_ERROR) return err;
   }
   _Format = FMT_FMT2;
   return _Format;
  //## end cSimpleFileSystem::FMT2_Format%1000724915.body
}

INT_T cSimpleFileSystem::FMT2_2F_Format ()
{
  //## begin cSimpleFileSystem::FMT2_2F_Format%1000724916.body preserve=yes
   _Format = FORMAT_UNKNOWN;
   int err = 0;
   OLD_DISK_HEADER header = {{0}};
   SUB_HEADER_2F sub_header = {{0}};
   header.TextLength = 8;
   header.ProcNr = 2001;
   header.CarrierNr = 0;
   header.CarrierLength = 0;
   header.Id = 1;
   header.CheckSum = 0;
   long carrierpos = (long)ADR_HEADER;
   if ((err = Write(carrierpos, sizeof(header), (char*)&header)) != USR_NO_ERROR) return err;
   carrierpos = ADR_SUBHEADER_2F;
   if ((err = Write(carrierpos, sizeof(sub_header), (char*)&sub_header)) != USR_NO_ERROR) return err;
   if ((err = FMT2_2F_MakeChecksum(1)) != USR_NO_ERROR) return err;
   _Format = FMT_FMT2;
   return _Format;
  //## end cSimpleFileSystem::FMT2_2F_Format%1000724916.body
}

INT_T cSimpleFileSystem::FMT2_3F_Format ()
{
  //## begin cSimpleFileSystem::FMT2_3F_Format%1000724917.body preserve=yes
   _Format = FORMAT_UNKNOWN;
   int err = 0;
   OLD_DISK_HEADER header = {{0}};
   SUB_HEADER_3F sub_header = {{0}};
   header.TextLength = 8;
   header.ProcNr = 2001;
   header.CarrierNr = 0;
   header.CarrierLength = 0;
   header.Id = 1;
   header.CheckSum = 0;
   long carrierpos = (long)ADR_HEADER;
   if ((err = Write(carrierpos, sizeof(header), (char*)&header)) != USR_NO_ERROR) return err;
   carrierpos = ADR_SUBHEADER_3F;
   if ((err = Write(carrierpos, sizeof(sub_header), (char*)&sub_header)) != USR_NO_ERROR) return err;
   if ((err = FMT2_3F_MakeChecksum(1)) != USR_NO_ERROR) return err;
   _Format = FMT_FMT2;
   return _Format;
  //## end cSimpleFileSystem::FMT2_3F_Format%1000724917.body
}

INT_T cSimpleFileSystem::FMT1_Format ()
{
  //## begin cSimpleFileSystem::FMT1_Format%1000724918.body preserve=yes
   int err = 0;
   if ((err = FMT1_Delete("OLDCAR.001")) != USR_NO_ERROR) return err;
   if ((err = FMT1_Delete("OLDCAR.002")) != USR_NO_ERROR) return err;
   if ((err = FMT1_Delete("OLDCAR.003")) != USR_NO_ERROR) return err;
   FMT1_MakeChecksum(1);
   FMT1_MakeChecksum(2);
   FMT1_MakeChecksum(3);
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FMT1_Format%1000724918.body
}

INT_T cSimpleFileSystem::FX25_Format ()
{
  //## begin cSimpleFileSystem::FX25_Format%1000724919.body preserve=yes
   int err = 0;
   if ((err = FX25_Delete("OLDCAR.001")) != USR_NO_ERROR) return err;
   if ((err = FX25_Delete("OLDCAR.002")) != USR_NO_ERROR) return err;
   if ((err = FX25_Delete("OLDCAR.003")) != USR_NO_ERROR) return err;
   FX25_MakeChecksum(1);
   FX25_MakeChecksum(2);
   FX25_MakeChecksum(3);
   return USR_NO_ERROR;
  //## end cSimpleFileSystem::FX25_Format%1000724919.body
}

LONG_T cSimpleFileSystem::FMT2_FileSize (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_FileSize%1000724920.body preserve=yes
   unsigned long file_size = 0L;
   int file_no = 0;
   file_no = FileNo(file_name);
   if (file_no < 1 || file_no > 3) return FSYS_INVALID_FILE_NAME;
   int err = 0;
   OLD_DISK_HEADER header;
   long size = sizeof(header);
   file_size += size;
   if ((err = Read(ADR_HEADER, size, &header)) != USR_NO_ERROR) return err;
   file_size += size = sizeof(OLD_DISK_SUB_HEADER);
   file_size += DATA_SIZE;
   file_size += size = header.TextLength;
   return file_size;
  //## end cSimpleFileSystem::FMT2_FileSize%1000724920.body
}

LONG_T cSimpleFileSystem::FMT2_2F_FileSize (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_2F_FileSize%1000724921.body preserve=yes
   int err = 0;
   OLD_DISK_HEADER header;
   long size = sizeof(OLD_DISK_HEADER) +
               sizeof(SUB_HEADER_2F) +
               DATA_SIZE_2F;
   if ((err = Read((long)ADR_HEADER, sizeof(header),
                   (char*)&header)) != USR_NO_ERROR) return err;
   size += header.TextLength;
   return size;
  //## end cSimpleFileSystem::FMT2_2F_FileSize%1000724921.body
}

LONG_T cSimpleFileSystem::FMT2_3F_FileSize (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_3F_FileSize%1000724922.body preserve=yes
   int err = 0;
   OLD_DISK_HEADER header;
   long size = sizeof(OLD_DISK_HEADER) +
               sizeof(SUB_HEADER_3F) +
               DATA_SIZE_3F;
   if ((err = Read((long)ADR_HEADER, sizeof(header),
                   (char*)&header)) != USR_NO_ERROR) return err;
   size += header.TextLength;
   return size;
  //## end cSimpleFileSystem::FMT2_3F_FileSize%1000724922.body
}

LONG_T cSimpleFileSystem::FMT1_FileSize (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT1_FileSize%1000724923.body preserve=yes
   return OLD_SIZE_FMT1;
  //## end cSimpleFileSystem::FMT1_FileSize%1000724923.body
}

LONG_T cSimpleFileSystem::FX25_FileSize (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FX25_FileSize%1000724924.body preserve=yes
   return OLD_SIZE_FX;
  //## end cSimpleFileSystem::FX25_FileSize%1000724924.body
}

cTimeObject cSimpleFileSystem::FMT2_GetTime (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_GetTime%1000724925.body preserve=yes
   return cTimeObject(0L);
  //## end cSimpleFileSystem::FMT2_GetTime%1000724925.body
}

cTimeObject cSimpleFileSystem::FMT2_2F_GetTime (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_2F_GetTime%1000724926.body preserve=yes
   return cTimeObject(0L);
  //## end cSimpleFileSystem::FMT2_2F_GetTime%1000724926.body
}

cTimeObject cSimpleFileSystem::FMT2_3F_GetTime (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT2_3F_GetTime%1000724927.body preserve=yes
   return cTimeObject(0L);
  //## end cSimpleFileSystem::FMT2_3F_GetTime%1000724927.body
}

cTimeObject cSimpleFileSystem::FMT1_GetTime (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FMT1_GetTime%1000724928.body preserve=yes
   return cTimeObject(0L);
  //## end cSimpleFileSystem::FMT1_GetTime%1000724928.body
}

cTimeObject cSimpleFileSystem::FX25_GetTime (CONST_STRING_T file_name)
{
  //## begin cSimpleFileSystem::FX25_GetTime%1000724929.body preserve=yes
   return cTimeObject(0L);
  //## end cSimpleFileSystem::FX25_GetTime%1000724929.body
}

LONG_T cSimpleFileSystem::FMT2_CarrierPos (INT_T file_no, INT_T area)
{
  //## begin cSimpleFileSystem::FMT2_CarrierPos%1000195358.body preserve=yes
   switch (area) {
   case ID_SUBHEADER:
      switch (file_no) {
      case 1: return ADR_SUBHEADER_1;
      case 2: return ADR_SUBHEADER_2;
      case 3: return ADR_SUBHEADER_3;
      }
   case ID_LIST:
      switch (file_no) {
      case 1: return ADR_LIST_1;
      case 2: return ADR_LIST_2;
      case 3: return ADR_LIST_3;
      }
   }
   return -42L;
  //## end cSimpleFileSystem::FMT2_CarrierPos%1000195358.body
}

LONG_T cSimpleFileSystem::FMT2_2F_CarrierPos (INT_T file_no, INT_T area)
{
  //## begin cSimpleFileSystem::FMT2_2F_CarrierPos%1000724930.body preserve=yes
   return FSYS_NOT_IMPLEMENTED;
  //## end cSimpleFileSystem::FMT2_2F_CarrierPos%1000724930.body
}

LONG_T cSimpleFileSystem::FMT2_3F_CarrierPos (INT_T file_no, INT_T area)
{
  //## begin cSimpleFileSystem::FMT2_3F_CarrierPos%1000724931.body preserve=yes
   return FSYS_NOT_IMPLEMENTED;
  //## end cSimpleFileSystem::FMT2_3F_CarrierPos%1000724931.body
}

LONG_T cSimpleFileSystem::FMT1_CarrierPos (INT_T file_no, INT_T area)
{
  //## begin cSimpleFileSystem::FMT1_CarrierPos%1000724932.body preserve=yes
   switch (file_no) {
   case 1: return 0L;
   case 2: return 1024L;
   case 3: return 2048L;
   }
   return -42L;
  //## end cSimpleFileSystem::FMT1_CarrierPos%1000724932.body
}

LONG_T cSimpleFileSystem::FX25_CarrierPos (INT_T file_no, INT_T area)
{
  //## begin cSimpleFileSystem::FX25_CarrierPos%1000724933.body preserve=yes
   switch (file_no) {
   case 1: return 0L;
   case 2: return 1024L;
   case 3: return 2048L;
   }
   return -42L;
  //## end cSimpleFileSystem::FX25_CarrierPos%1000724933.body
}

// Additional Declarations
  //## begin cSimpleFileSystem%3B9CF6E3010D.declarations preserve=yes
  //## end cSimpleFileSystem%3B9CF6E3010D.declarations

//## begin module%3B9CF6E3010D.epilog preserve=yes
//## end module%3B9CF6E3010D.epilog
