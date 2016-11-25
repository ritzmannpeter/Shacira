//## begin module%3F4F500A006D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4F500A006D.cm

//## begin module%3F4F500A006D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4F500A006D.cp

//## Module: cCARRIERFat%3F4F500A006D; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCARRIERFat.cpp

//## begin module%3F4F500A006D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F4F500A006D.additionalIncludes

//## begin module%3F4F500A006D.includes preserve=yes

#include "legacy.h"
#include "Dnc/ToolFiles.h"

//## end module%3F4F500A006D.includes

// cCarrier
#include "Dnc/Carrier/cCarrier.h"
// cCARRIERFat
#include "Dnc/FileSystem/cCARRIERFat.h"
// cFMFatFile
#include "Dnc/File/cFMFatFile.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3F4F500A006D.additionalDeclarations preserve=yes
//## end module%3F4F500A006D.additionalDeclarations


// Class cCARRIERFat 


cCARRIERFat::cCARRIERFat()
  //## begin cCARRIERFat::cCARRIERFat%.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCARRIERFat::cCARRIERFat%.hasinit
  //## begin cCARRIERFat::cCARRIERFat%.initialization preserve=yes
  //## end cCARRIERFat::cCARRIERFat%.initialization
{
  //## begin cCARRIERFat::cCARRIERFat%.body preserve=yes
_ASSERT_UNCOND
  //## end cCARRIERFat::cCARRIERFat%.body
}

cCARRIERFat::cCARRIERFat(const cCARRIERFat &right)
  //## begin cCARRIERFat::cCARRIERFat%copy.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCARRIERFat::cCARRIERFat%copy.hasinit
  //## begin cCARRIERFat::cCARRIERFat%copy.initialization preserve=yes
  //## end cCARRIERFat::cCARRIERFat%copy.initialization
{
  //## begin cCARRIERFat::cCARRIERFat%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCARRIERFat::cCARRIERFat%copy.body
}

cCARRIERFat::cCARRIERFat (CONST_STRING_T path, cCarrier *carrier)
  //## begin cCARRIERFat::cCARRIERFat%1062162389.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCARRIERFat::cCARRIERFat%1062162389.hasinit
  //## begin cCARRIERFat::cCARRIERFat%1062162389.initialization preserve=yes
  //## end cCARRIERFat::cCARRIERFat%1062162389.initialization
{
  //## begin cCARRIERFat::cCARRIERFat%1062162389.body preserve=yes
   _Carrier = carrier;
   DISK_INIT_BLOCK disk_init_block;
   disk_init_block.DebugMask = 0;
   DevInit(DEV_MAIN, NULL);
   DevInit(DEV_DISK, &disk_init_block);
  //## end cCARRIERFat::cCARRIERFat%1062162389.body
}


cCARRIERFat::~cCARRIERFat()
{
  //## begin cCARRIERFat::~cCARRIERFat%.body preserve=yes
  //## end cCARRIERFat::~cCARRIERFat%.body
}



//## Other Operations (implementation)
void cCARRIERFat::Directory (TOOLFILE_HEADER_T * &file_header, ULONG_T &file_count)
{
  //## begin cCARRIERFat::Directory%1062162390.body preserve=yes
   file_header = NULL;
   INT_T err, i;
   INT_T dir_entries = 0;
   DISK_PARAM_BLOCK param;
   USR_HANDLE hnd = 0;
   DISK_DIR_STRUCT * dev_dir;
   param.Drive = (PARAMETER)DRIVE_NO;
   param.Mode = DISK_OP_READ;
   param.FileName = NULL;
   PARAMETER size = 0L;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) != USR_NO_ERROR) {
      int device_error = DeviceError(hnd);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   }
   if ((err = DevGetParam(hnd, DISK_ID_SIZE, &size)) != USR_NO_ERROR) {
      int device_error = DeviceError(hnd);
      DevClose(hnd);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
	}
   if (size == 0L) {
      DevClose(hnd);
      return;
	}
   dir_entries = (USR_WORD)(size / sizeof(DISK_DIR_STRUCT));
   dev_dir = (DISK_DIR_STRUCT*)cSystemUtils::Alloc(size);
   if (dev_dir == NULL) {
      DevClose(hnd);
      int device_error = ERR_DRAM_ALLOC;
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   } else {
      memset(dev_dir, 0, size);
   }
   if ((err = DevRead(hnd, (char*)dev_dir, (int)size, NULL, (TIME)0)) != USR_NO_ERROR) {
      int device_error = DeviceError(hnd);
      cSystemUtils::Free(dev_dir);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   } else {
      DevClose(hnd);
   }
   file_header = AllocHeader(dir_entries);
   for (i=0; i<dir_entries; i++) {
      STRING_T file_name = dev_dir[i].FileName;
      strcpy(file_header[i].file_name, file_name.c_str());
      hnd = OpenRead(file_header[i].file_name);
      file_header[i].file_info.size = GetSize(hnd);
      DevClose(hnd);
   }
   file_count = dir_entries;
   cSystemUtils::Free(dev_dir);
  //## end cCARRIERFat::Directory%1062162390.body
}

void cCARRIERFat::Format ()
{
  //## begin cCARRIERFat::Format%1062162391.body preserve=yes
  //## end cCARRIERFat::Format%1062162391.body
}

void cCARRIERFat::Delete (CONST_STRING_T file_name)
{
  //## begin cCARRIERFat::Delete%1062162392.body preserve=yes
  //## end cCARRIERFat::Delete%1062162392.body
}

ULONG_T cCARRIERFat::ReadFile (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cCARRIERFat::ReadFile%1062507901.body preserve=yes
return 0;
  //## end cCARRIERFat::ReadFile%1062507901.body
}

void cCARRIERFat::WriteFile (CONST_STRING_T file_name, void *buf, ULONG_T amount)
{
  //## begin cCARRIERFat::WriteFile%1062507902.body preserve=yes
  //## end cCARRIERFat::WriteFile%1062507902.body
}

cToolFile * cCARRIERFat::ToolFile (TOOLFILE_HEADER_T *file_header)
{
  //## begin cCARRIERFat::ToolFile%1062507904.body preserve=yes
   USR_HANDLE hnd = OpenRead(file_header->file_name);
   ULONG_T size = file_header->file_info.size;
   CHAR_T * buf = (CHAR_T*)cSystemUtils::Alloc(size);
   Read(hnd, buf, size);
   DevClose(hnd);
   cToolFile * file = new cFMFatFile(file_header, this); 
   return file;
  //## end cCARRIERFat::ToolFile%1062507904.body
}

ULONG_T cCARRIERFat::GetSize (USR_HANDLE hnd)
{
  //## begin cCARRIERFat::GetSize%1062162399.body preserve=yes
   INT_T err;
   PARAMETER file_size = 0;
   if ((err = DevGetParam(hnd, DISK_ID_SIZE, (PARAMETER*)&file_size)) != USR_NO_ERROR) {
      INT_T device_error = DeviceError(err);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   } else {
      return (long)file_size;
   }
  //## end cCARRIERFat::GetSize%1062162399.body
}

USR_HANDLE cCARRIERFat::OpenRead (CONST_STRING_T file_name)
{
  //## begin cCARRIERFat::OpenRead%1062162400.body preserve=yes
   USR_HANDLE hnd = 0;
   INT_T err = 0;
   PARAMETER dev_mode = (PARAMETER)DISK_OP_READ;
   DISK_PARAM_BLOCK  param;
//   param.Date = (PARAMETER) DiskGetTimeDate();
   param.Drive = (PARAMETER) DRIVE_NO;
   param.Mode = dev_mode;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) {
      INT_T device_error = DeviceError(err);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   } else {
      return hnd;
   }
  //## end cCARRIERFat::OpenRead%1062162400.body
}

USR_HANDLE cCARRIERFat::OpenWrite (CONST_STRING_T file_name)
{
  //## begin cCARRIERFat::OpenWrite%1062162401.body preserve=yes
   USR_HANDLE hnd = 0;
   INT_T err = 0;
   PARAMETER dev_mode = (PARAMETER)DISK_OP_WRITE | (PARAMETER)DISK_OP_CREATE;
   DISK_PARAM_BLOCK  param;
//   param.Date = (PARAMETER) DiskGetTimeDate();
param.Date = (PARAMETER) 0;
   param.Drive = (PARAMETER) DRIVE_NO;
   param.Mode = dev_mode;
   param.FileName = (char*)file_name;
   if ((err = DevOpen(&hnd, DEV_DISK, &param)) == DEV_ERROR) {
      INT_T device_error = DeviceError(err);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   } else {
      return hnd;
   }
  //## end cCARRIERFat::OpenWrite%1062162401.body
}

void cCARRIERFat::Read (USR_HANDLE hnd, void *buf, ULONG_T amount)
{
  //## begin cCARRIERFat::Read%1062162402.body preserve=yes
   INT_T err = DevRead(hnd, (char*)buf, amount, NULL, 0);
   if (err != USR_NO_ERROR) {
      INT_T device_error = DeviceError(err);
      throw cError(CARRIER_DEVICE_ACCESS, device_error);
   }
  //## end cCARRIERFat::Read%1062162402.body
}

void cCARRIERFat::Write (USR_HANDLE hnd, void *buf, ULONG_T amount)
{
  //## begin cCARRIERFat::Write%1062162403.body preserve=yes
  //## end cCARRIERFat::Write%1062162403.body
}

// Additional Declarations
  //## begin cCARRIERFat%3F4F500A006D.declarations preserve=yes
  //## end cCARRIERFat%3F4F500A006D.declarations

//## begin module%3F4F500A006D.epilog preserve=yes
//## end module%3F4F500A006D.epilog
